#include "dnf/combat.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
uint64_t num(const Json &v,uint64_t high=UINT64_MAX) {
    if(!v.is_number_integer()||(!v.is_number_unsigned()&&v.get<int64_t>()<0)||v.get<uint64_t>()>high)
        throw std::invalid_argument("Invalid saved monster Event.ai integer");return v.get<uint64_t>();
}
void validateIdentity(const Pvf &pvf,const Actor &actor,const Json &saved,uint64_t ms,uint64_t generation) {
    if(!saved.is_object()||saved.dump().size()>4194304||saved.at("schema")!=1||saved.at("policy")!=monsterDamageWindowPolicy||
       num(saved.at("commit_generation"))!=generation||!generation||
       saved.at("source_id")!=actor.sourceId||saved.at("actor_id")!=actor.id||
       saved.at("monster_source")!=makeSourceRef(pvf,actor.monsterPath).json()||
       !EntityHandle::fromJson(saved.at("owner"))||!EntityHandle::fromJson(saved.at("player_owner"))||!saved.at("binding").is_boolean()||
       !saved.at("pending").is_array()||saved.at("pending").size()>1024||
       num(saved.at("saved_ms"))!=FixedStepClock::millisecondsAtTick(num(saved.at("saved_tick")))||num(saved.at("saved_ms"))>ms)
        throw std::invalid_argument("Invalid monster Event.ai actor/source/generation/clock binding");
    if(actor.dead||actor.life!=ActorLife::Alive||actor.hp<=0)
        throw std::invalid_argument("Dead or retired actor cannot resume monster Event.ai");
    MonotonicIds entityIds;entityIds.restore(saved.at("entity_ids"));
    for(const auto &key:{"owner","player_owner"}) {
        const auto owner=EntityHandle::fromJson(saved.at(key));
        if(entityIds.nextValue()&&owner.id>=entityIds.nextValue())throw std::invalid_argument("Monster Event.ai entity beyond saved allocation watermark");
    }
}
}
Json World::monsterEventActorCheckpoint(EntityHandle owner,uint64_t generation) const {
    const auto *actor=resolveActor(owner);if(!actor||actor==&player||actor->dead||actor->life!=ActorLife::Alive)return Json();
    const auto binding=monsterEventAiBindings_.find(owner),end=monsterEventAiBindings_.end();
    const auto window=monsterDamageWindows_.find(owner);
    if(binding==end&&window==monsterDamageWindows_.end())return Json();
    if(!generation||window==monsterDamageWindows_.end())throw std::invalid_argument("Monster Event.ai lacks persistent source window");
    Json rows=Json::array();
    for(const auto &pending:monsterEventAiPending_)if(pending.target==owner) {
        if(pending.hit.attacker!=player.handle)throw std::invalid_argument("Only explicit player-origin monster Event.ai continuation is supported");
        rows.push_back({{"event_id",pending.hit.eventId},{"accepted_tick",pending.acceptedTick},
            {"attacker_role","player"},{"attacker",pending.hit.attacker.json()},{"actual_hp_loss",pending.hit.actualHpLoss},
            {"window_amount",pending.hit.damageWindowAmount},{"damage_check_enabled",pending.hit.damageCheckEnabled},{"window_configuration",pending.hit.damageWindowConfiguration}});
    }
    Json out={{"schema",1},{"policy",monsterDamageWindowPolicy},{"commit_generation",generation},
        {"owner",owner.json()},{"player_owner",player.handle.json()},{"source_id",actor->sourceId},{"actor_id",actor->id},{"monster_source",makeSourceRef(pvf_,actor->monsterPath).json()},
        {"saved_tick",tick},{"saved_ms",nowMs()},{"binding",binding!=end},{"window",window->second.snapshot()},
        {"entity_ids",entities_.snapshot().at("ids")},
        {"pending",rows},{"restoration","typed owner/player remap; restore pending only; never replay HP damage or rewards"}};
    if(binding!=end) {
        out["difficulty"]=binding->second.route.difficulty;out["ai_source"]=binding->second.program->source().json();
        out["ai_policy"]=MonsterEventAiPolicy::inferredIntegralChanceV1().json();out["random_stream_key"]=binding->second.randomStreamKey;
    }
    return out;
}
void World::validateMonsterEventActorCheckpoint(const Actor &actor,const Json &saved,uint64_t ms,uint64_t generation) const {
    validateIdentity(pvf_,actor,saved,ms,generation);
    const auto window=restoreMonsterDamageWindow(pvf_,pvf_.script(actor.monsterPath),saved.at("window"),num(saved.at("saved_ms")));
    if(saved.at("binding")==true) {
        if(!actHost_||!num(saved.at("random_stream_key"))||saved.at("ai_policy")!=MonsterEventAiPolicy::inferredIntegralChanceV1().json())
            throw std::invalid_argument("Saved monster Event.ai policy/consumer/key unavailable");
        MonotonicIds entityIds;entityIds.restore(saved.at("entity_ids"));
        if(entityIds.nextValue()&&num(saved.at("random_stream_key"))>=entityIds.nextValue())
            throw std::invalid_argument("Saved monster Event.ai random key beyond allocation watermark");
        const auto route=selectMonsterEventAi(pvf_,pvf_.script(actor.monsterPath),saved.at("difficulty").get<std::string>());
        if(!route.ok)throw std::invalid_argument("Saved monster Event.ai route changed");
        const auto compiled=compileMonsterEventAi(pvf_,pvf_.script(route.resolvedPath),MonsterEventAiPolicy::inferredIntegralChanceV1());
        if(!compiled.ok||compiled.program->source().json()!=saved.at("ai_source"))throw std::invalid_argument("Saved monster Event.ai source changed");
    } else if(!saved.at("pending").empty())throw std::invalid_argument("Monster Event.ai pending without source binding");
    uint64_t previous=0;
    for(const auto &row:saved.at("pending")) {
        const auto event=num(row.at("event_id")),accepted=num(row.at("accepted_tick"));
        if(!event||event<=previous||accepted>num(saved.at("saved_tick"))||row.at("attacker_role")!="player"||
           row.at("attacker")!=saved.at("player_owner")||!row.at("damage_check_enabled").is_boolean())
            throw std::invalid_argument("Monster Event.ai pending identity/order/clock invalid");
        const auto loss=num(row.at("actual_hp_loss"),INT32_MAX),amount=num(row.at("window_amount"),uint64_t(INT32_MAX)*1024);
        const auto stamp=restoreMonsterDamageWindow(pvf_,pvf_.script(actor.monsterPath),row.at("window_configuration"),FixedStepClock::millisecondsAtTick(accepted));
        if(!stamp.samples.empty()||stamp.enabled!=row.at("damage_check_enabled").get<bool>()||
           (stamp.enabled&&amount<loss)||(!stamp.enabled&&amount!=0))
            throw std::invalid_argument("Monster Event.ai pending damage/configuration receipt disagrees");
        previous=event;
    }
}
World::MonsterEventRoomRestore World::prepareMonsterEventRoomRestore(const std::vector<Actor> &actors,const Json &savedActors) const {
    MonsterEventRoomRestore out;std::set<uint64_t> keys;std::set<EntityHandle> savedOwners;
    std::map<uint64_t,EntityHandle> eventOwners;size_t count=0;uint64_t generation=0;Json roomReceipt;
    for(size_t i=0;i<actors.size();++i) {
        const auto &actor=actors[i];
        const auto &savedActor=savedActors[i];if(!savedActor.contains("monster_event_ai_state")) {
            if(!actor.dead&&actor.life==ActorLife::Alive&&!actor.monsterPath.empty()) {
                const auto initial=initialMonsterDamageWindow(pvf_,pvf_.script(actor.monsterPath),uint64_t(nowMs()));
                if(initial.enabled)throw std::invalid_argument("Authored damage window lacks restorable actor receipt");
            }
            continue;
        }
        const auto &saved=savedActor.at("monster_event_ai_state");
        if(!generation)generation=num(saved.at("commit_generation"));
        if(num(saved.at("commit_generation"))!=generation)throw std::invalid_argument("Room monster Event.ai bundles belong to different generations");
        const auto receipt=Json::array({saved.at("saved_tick"),saved.at("saved_ms"),saved.at("entity_ids"),saved.at("player_owner")});
        if(roomReceipt.is_null())roomReceipt=receipt;
        if(receipt!=roomReceipt)throw std::invalid_argument("Room monster Event.ai bundles disagree on saved clock/player/allocation receipt");
        validateMonsterEventActorCheckpoint(actor,saved,uint64_t(nowMs()),num(saved.at("commit_generation")));
        if(EntityHandle::fromJson(savedActor.at("entity_handle"))!=EntityHandle::fromJson(saved.at("owner"))||!actor.handle)
            throw std::invalid_argument("Monster Event.ai owner remap differs from actor receipt");
        if(!savedOwners.insert(EntityHandle::fromJson(saved.at("owner"))).second||out.windows.size()>=1024)
            throw std::invalid_argument("Monster Event.ai repeated saved owner or window budget exceeded");
        const auto claimEvent=[&](uint64_t event) {
            const auto claim=eventOwners.emplace(event,actor.handle);
            if(!claim.second&&claim.first->second!=actor.handle)
                throw std::invalid_argument("Monster damage-window/pending event reused by another actor");
        };
        auto window=restoreMonsterDamageWindow(pvf_,pvf_.script(actor.monsterPath),saved.at("window"),uint64_t(nowMs()));
        for(const auto &sample:window.samples) {
            if(ids_.events.nextValue()&&sample.eventId>=ids_.events.nextValue())throw std::invalid_argument("Monster damage-window event beyond same-generation allocation watermark");
            claimEvent(sample.eventId);
        }
        if(saved.at("binding")==true) {
            MonsterEventAiBinding binding;binding.sourceId=actor.sourceId;binding.memberPath=normalize(actor.monsterPath);
            binding.randomStreamKey=num(saved.at("random_stream_key"));if(!keys.insert(binding.randomStreamKey).second)
                throw std::invalid_argument("Monster Event.ai random key collision");
            binding.route=selectMonsterEventAi(pvf_,pvf_.script(actor.monsterPath),saved.at("difficulty").get<std::string>());
            binding.program=compileMonsterEventAi(pvf_,pvf_.script(binding.route.resolvedPath),MonsterEventAiPolicy::inferredIntegralChanceV1()).program;
            out.bindings.emplace(actor.handle,std::move(binding));out.actors.insert(actor.handle);
        }
        for(const auto &row:saved.at("pending")) {
            if(++count>1024)throw std::invalid_argument("Restored monster Event.ai pending budget exceeded");
            const auto id=num(row.at("event_id"));
            if(ids_.events.nextValue()&&id>=ids_.events.nextValue())throw std::invalid_argument("Monster Event.ai event beyond same-generation allocation watermark");
            claimEvent(id);
            MonsterAcceptedHit hit;hit.eventId=id;hit.attacker=player.handle;hit.actualHpLoss=int(num(row.at("actual_hp_loss"),INT32_MAX));
            hit.damageWindowAmount=int64_t(num(row.at("window_amount"),uint64_t(INT32_MAX)*1024));hit.damageCheckEnabled=row.at("damage_check_enabled").get<bool>();hit.damageWindowConfiguration=row.at("window_configuration");
            out.pending.push_back({actor.handle,num(row.at("accepted_tick")),hit});
        }
        out.windows.emplace(actor.handle,std::move(window));
    }
    std::sort(out.pending.begin(),out.pending.end(),[](const auto &a,const auto &b){return a.hit.eventId<b.hit.eventId;});
    for(size_t i=1;i<out.pending.size();++i)if(out.pending[i-1].hit.eventId==out.pending[i].hit.eventId)
        throw std::invalid_argument("Monster Event.ai pending event reused by another owner");
    return out;
}
} // namespace dnf
