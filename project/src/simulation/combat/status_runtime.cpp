#include "dnf/combat.hpp"
#include "dnf/damage_contact.hpp"
#include "dnf/female_gunner_world.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
DamageResolution World::resolveActorContact(const DamageRequest &request,const StatusResistanceSnapshot &resistance,
    const SkillStatusApplication *skill) {
    if(!combatAttributes_) throw std::runtime_error("Damage/status transaction needs prepared character attributes");
    const auto policy=DamageResolutionPolicy::inferredPveDamageV1(combatAttributes_->damageConstants);
    auto damageRequest=request;
    if(femaleGunnerWorld_ && request.target==player.handle && identity_.jobId==5) {
        if(femaleGunnerWorld_->invulnerable()) {
            DamageResolution immune;immune.policy="inferred-source-quick-standing-invulnerability-v1";
            immune.attacker=request.attacker;immune.target=request.target;immune.attackInstance=request.attackInstance;immune.hitIndex=request.hitIndex;
            immune.hpDamage=0;immune.missed=true;immune.trace.push_back({{"stage","source_quick_standing_invulnerability"},
                {"classification","inferred"},{"result","immune; no HP/status/random publication"}});return immune;
        }
        femaleGunnerWorld_->applyDefense(damageRequest);
    }
    auto prepared=prepareDamageContact(damageRequest,policy,resistance,statuses_,random_,uint64_t(nowMs()),skill);
    const auto result=prepared.resolution;
    if(prepared.ready())publishDamageContact(std::move(prepared),statuses_,random_);
    return result;
}
void World::interruptStatusTarget(Actor &actor) {
    const auto remaining=statuses_.controlRemaining(actor.handle,uint64_t(nowMs()));
    if(!remaining || actor.dead) return;
    // Named stun policy cancels voluntary actions; source status duration is
    // independent of ordinary ATK reaction and actor-local hit pause.
    if(&actor==&player) {
        // World::idle additionally checks positive HP, !dead and exact
        // Alive lifecycle before retaining physical movement ownership.
        idle(true);
        commandHistory_.clear();
        bufferedSkill_=-1;
    } else {
        actor.animation="stay";actor.animationPath.clear();actor.animStart=nowMs();
        actor.poseFrame=-1;actor.attackHit=true;
    }
    actor.vx=actor.vy=0;
    events.push_back({tick,statuses_.frozen(actor.handle,uint64_t(nowMs()))?"status_freeze":"status_stun",
        "inferred-1031-active-status-v1",0,actor.id,int(std::min<uint64_t>(remaining,uint64_t(INT32_MAX)))});
}
void World::advanceStatusEffects() {
    if(!statuses_.needsEffectAdvance(uint64_t(nowMs()))) {statuses_.expire(uint64_t(nowMs()));return;}
    auto candidate=statuses_.prepareAdvance(uint64_t(nowMs()));
    if(!candidate.ready() || !statuses_.canPublish(candidate))
        throw std::runtime_error("Status effect advance failed: "+candidate.receipt.dump());
    std::map<EntityHandle,int64_t> totals;
    for(const auto &damage:candidate.receipt.at("damages")) {
        const auto handle=EntityHandle::fromJson(damage.at("target"));const auto *target=resolveActor(handle);
        if(!target || target->dead || target->life!=ActorLife::Alive) continue;
        auto &amount=totals[handle];amount+=damage.at("amount").get<int>();
        if(amount>INT32_MAX) throw std::overflow_error("Status effect due damage overflow");
    }
    const auto receipt=candidate.receipt;statuses_.publish(std::move(candidate));
    for(const auto &[handle,amount]:totals) {
        auto *target=resolveActor(handle);if(!target || target->dead || !amount) continue;
        target->hp=std::max(0,target->hp-int(std::min<int64_t>(amount,INT32_MAX)));
        events.push_back({tick,"status_damage","inferred-1031-active-status-v1",0,target->id,int(amount)});
        if(!target->hp) beginDeath(*target);
    }
}
Json World::statusCheckpoint(EntityHandle target,uint64_t generation) const {
    return statuses_.snapshotTarget(target,uint64_t(nowMs()),generation);
}
void World::validateStatusCheckpoint(const Json &saved,EntityHandle oldTarget,uint64_t generation,uint64_t restoreMs) const {
    if(!oldTarget) throw std::invalid_argument("Saved status owner needs an explicit entity handle");
    StatusHost prepared(pvf_.identity(),StunStatusPolicy::inferredFlatChanceStunV1());
    prepared.mergeTarget(saved,oldTarget,oldTarget,restoreMs==UINT64_MAX?uint64_t(nowMs()):restoreMs,generation,
        [this](const std::string &path){return pvf_.script(path);},
        [oldTarget](EntityHandle target){return target==oldTarget;});
}
void World::restoreStatusCheckpoint(const Json &saved,EntityHandle oldTarget,EntityHandle newTarget,uint64_t generation) {
    statuses_.mergeTarget(saved,oldTarget,newTarget,uint64_t(nowMs()),generation,
        [this](const std::string &path){return pvf_.script(path);},
        [this](EntityHandle target){const auto *actor=static_cast<const World *>(this)->resolveActor(target);return actor && !actor->dead;});
}
void World::clearRestoredPlayerStatus() {
    if(!player.handle) return;
    // Replacing a player's saved state also replaces its accepted-contact
    // ledger. StatusHost retires this target through a private candidate,
    // pruning only unused sources and retaining the global ID watermark.
    // A live cleanse instead uses clearTarget, which keeps deduplication.
    statuses_.retireTarget(player.handle,uint64_t(nowMs()),"player_restore_without_status");
}
void World::restoreRoomActors(std::vector<Actor> actors,const Json &savedActors) {
    if(!savedActors.is_array() || actors.size()!=savedActors.size())
        throw std::invalid_argument("Room actor/status candidate sizes differ");
    auto registry=entities_;
    auto statuses=statuses_;
    for(const auto &actor:monsters) if(actor.handle) {
        statuses.retireTarget(actor.handle,uint64_t(nowMs()),"room_restore");registry.retire(actor.handle);
    }
    std::set<EntityHandle> targets;
    if(player.handle && !player.dead) targets.insert(player.handle);
    for(auto &actor:actors) {
        // The serialized handle is evidence for the explicit remap only. New
        // room incarnations receive new identities from the staged registry.
        actor.handle=actor.life==ActorLife::Removed?EntityHandle{}:registry.create();
        if(actor.handle && !actor.dead) targets.insert(actor.handle);
    }
    for(size_t i=0;i<actors.size();++i) if(savedActors[i].contains("status_state")) {
        const auto &bundle=savedActors[i].at("status_state");
        if(actors[i].dead || actors[i].life!=ActorLife::Alive || actors[i].hp==0 || !actors[i].handle)
            throw std::invalid_argument("Dead/removed room actor cannot restore a status bundle");
        statuses.mergeTarget(bundle,EntityHandle::fromJson(savedActors[i].at("entity_handle")),actors[i].handle,
            uint64_t(nowMs()),bundle.at("commit_generation").get<uint64_t>(),
            [this](const std::string &path){return pvf_.script(path);},
            [&targets](EntityHandle target){return targets.count(target)!=0;});
    }
    std::map<std::pair<EntityHandle,int>,int64_t> cooldowns;
    std::map<EntityHandle,MonsterSourceMovement> movements;
    auto sourceActors=sourceActionActors_,visited=sourceActionVisited_;
    for(size_t i=0;i<actors.size();++i) {
        const auto rows=prepareSourceMonsterCooldownRestore(actors[i],savedActors[i].value("source_action_cooldowns",Json()),nowMs());
        for(const auto &[index,until]:rows)cooldowns.emplace(std::make_pair(actors[i].handle,index),until);
        if(auto plan=prepareSourceMonsterMovementRestore(actors[i],savedActors[i].value("source_action_cooldowns",Json())))
            movements.emplace(actors[i].handle,std::move(*plan));
        if(monsterActionAiEnabled_&&actors[i].handle&&!actors[i].dead) {
            const auto source=pvf_.script(actors[i].monsterPath);
            const bool sourceAct=std::any_of(source.fields.begin(),source.fields.end(),[](const Field &field) {
                const auto tag=normalize(field.tag);
                return tag=="[basic action]"||tag=="[waiting action]"||tag=="[action list]"||tag=="[attack action]";
            });
            if(sourceAct){sourceActors.insert(actors[i].handle);visited.insert(actors[i].handle);}
        }
    }
    auto eventRestore=prepareMonsterEventRoomRestore(actors,savedActors);
    sourceActors.insert(eventRestore.actors.begin(),eventRestore.actors.end());
    entities_=std::move(registry);statuses_=std::move(statuses);monsters.swap(actors);
    monsterEventAiBindings_=std::move(eventRestore.bindings);monsterDamageWindows_=std::move(eventRestore.windows);
    monsterEventAiPending_=std::move(eventRestore.pending);
    sourceActionCooldowns_=std::move(cooldowns);sourceActionActors_=std::move(sourceActors);sourceActionVisited_=std::move(visited);
    monsterSourceMovements_=std::move(movements);
}
} // namespace dnf
