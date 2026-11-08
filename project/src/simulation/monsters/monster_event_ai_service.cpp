#include "dnf/combat.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/monster_behavior.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
constexpr size_t pendingLimit=1024,diagnosticLimit=256;
void appendOutcome(Json &rows,Json row) {
    rows.push_back(std::move(row));
    if(rows.size()>diagnosticLimit)
        rows.erase(rows.begin(),rows.begin()+std::ptrdiff_t(rows.size()-diagnosticLimit));
}
} // namespace

bool World::configureMonsterEventAi(EntityHandle owner,std::string difficulty,const MonsterEventAiPolicy &policy) {
    Json diagnostic={{"kind","monster_event_ai_install"},{"owner",owner.json()},{"tick",tick},
        {"policy",policy.json()},{"whole_monster_complete",false}};
    try {
        const auto *actor=static_cast<const World *>(this)->resolveActor(owner);
        if(!actHost_ || !actor || actor==&player || actor->dead || actor->life!=ActorLife::Alive ||
           !explorationAllowsSourceActions(*actor))
            throw std::invalid_argument("Event.ai needs a live synchronized source monster and configured ACT consumer");
        if(monsterEventAiBindings_.count(owner))
            throw std::invalid_argument("Event.ai is already installed for this actor incarnation");
        if(monsterEventAiBindings_.size()>=pendingLimit)
            throw std::overflow_error("Event.ai source binding budget exceeded");
        const auto source=pvf_.script(actor->monsterPath);
        const auto route=selectMonsterEventAi(pvf_,source,difficulty);
        diagnostic["route"]=route.json();
        if(!route.ok) throw std::runtime_error("Source MOB Event.ai difficulty route is unavailable");
        const auto compiled=compileMonsterEventAi(pvf_,pvf_.script(route.resolvedPath),policy);
        diagnostic["compilation"]=compiled.json();
        if(!compiled.ok || !compiled.program) throw std::runtime_error("Source Event.ai grammar is unsupported");
        MonsterEventAiBinding binding;
        binding.sourceId=actor->sourceId;binding.memberPath=normalize(actor->monsterPath);binding.randomStreamKey=owner.id;
        for(const auto &[other,registered]:monsterEventAiBindings_)if(registered.randomStreamKey==binding.randomStreamKey)
            throw std::invalid_argument("Event.ai random stream key collides with another live owner");
        auto windows=monsterDamageWindows_;
        if(!windows.count(owner)) {
            if(windows.size()>=pendingLimit)throw std::overflow_error("Event.ai damage-window owner budget exceeded");
            windows.emplace(owner,initialMonsterDamageWindow(pvf_,source,uint64_t(nowMs())));
        }
        binding.route=route;binding.program=compiled.program;
        // Complete allocations before publishing the registration. No live
        // actor reference may survive a later ACT bind's storage replacement.
        auto bindings=monsterEventAiBindings_;bindings.emplace(owner,std::move(binding));
        auto actors=sourceActionActors_;actors.insert(owner);
        auto diagnostics=monsterEventAiDiagnostics_;diagnostic["ok"]=true;
        appendOutcome(diagnostics,std::move(diagnostic));
        monsterEventAiBindings_=std::move(bindings);monsterDamageWindows_=std::move(windows);sourceActionActors_=std::move(actors);
        monsterEventAiDiagnostics_=std::move(diagnostics);
        return true;
    } catch(const std::exception &error) {
        diagnostic["ok"]=false;diagnostic["reason"]=error.what();
        appendOutcome(monsterEventAiDiagnostics_,std::move(diagnostic));return false;
    }
}

World::PreparedMonsterEventHit World::prepareMonsterAcceptedHit(const Actor &actor,const std::string &cause) const {
    PreparedMonsterEventHit prepared;
    if(cause=="diagnostic-fixture") return prepared;
    const auto found=monsterEventAiBindings_.find(actor.handle);
    if(found==monsterEventAiBindings_.end() && !monsterDamageWindows_.count(actor.handle)) return prepared;
    prepared.required=true;
    try {
        if(found!=monsterEventAiBindings_.end()) {const auto &binding=found->second;
        if(!actor.handle || static_cast<const World *>(this)->resolveActor(actor.handle)!=&actor ||
           normalize(actor.monsterPath)!=binding.memberPath || actor.sourceId!=binding.sourceId ||
           binding.route.monsterSource.packageIdentity!=pvf_.identity() ||
           sha256(pvf_.read(binding.memberPath))!=binding.route.monsterSource.memberSha256)
            throw std::runtime_error("monster_event_ai_source_identity_changed");}
        if(tick<0 || !player.handle || static_cast<const World *>(this)->resolveActor(player.handle)!=&player)
            throw std::runtime_error("monster_event_ai_accepted_hit_identity_unavailable");
        if(monsterEventAiPending_.size()>=pendingLimit) throw std::runtime_error("monster_event_ai_accepted_hit_queue_full");
        // This must run before damage/status RNG or HP publication. Misses,
        // blocked contacts and diagnostic fixtures never publish this copy.
        prepared.events=ids_.events;
        const auto event=prepared.events.next();
        prepared.pending=monsterEventAiPending_;
        if(found!=monsterEventAiBindings_.end())prepared.pending.push_back({actor.handle,uint64_t(tick),{event,player.handle}});
        prepared.target=actor.handle;prepared.eventId=event;prepared.windows=monsterDamageWindows_;
        if(auto window=prepared.windows.find(actor.handle);window!=prepared.windows.end()) {
            if(window->second.monsterSource.json()!=makeSourceRef(pvf_,actor.monsterPath).json())throw std::runtime_error("monster_damage_window_source_changed");
            window->second.prune(uint64_t(nowMs()));
            if(window->second.enabled) {
                if(window->second.samples.size()>=pendingLimit)throw std::runtime_error("monster_damage_window_sample_budget");
                window->second.samples.push_back({event,uint64_t(nowMs()),0});
            }
            if(!prepared.pending.empty()&&prepared.pending.back().hit.eventId==event) {
                auto stamp=window->second.snapshot();stamp["samples"]=Json::array();
                prepared.pending.back().hit.damageWindowConfiguration=std::move(stamp);
            }
        }
    } catch(const std::exception &error) {
        prepared.ready=false;prepared.error=error.what();
    }
    return prepared;
}
void World::publishMonsterAcceptedHit(PreparedMonsterEventHit &&prepared,int actualHpLoss) noexcept {
    if(!prepared.required) return;
    // Damage and its response currently allocate no global event identities.
    // Their separately scoped attack/effect/status IDs remain untouched here.
    const auto window=prepared.windows.find(prepared.target);
    if(window!=prepared.windows.end() && window->second.enabled && !window->second.samples.empty())
        window->second.samples.back().actualHpLoss=actualHpLoss;
    if(!prepared.pending.empty()&&prepared.pending.back().hit.eventId==prepared.eventId) {
        auto &hit=prepared.pending.back().hit;hit.actualHpLoss=actualHpLoss;
        if(window!=prepared.windows.end()) {
            hit.damageCheckEnabled=window->second.enabled;
            // Proven nonthrowing here: prepare validated the same fixed tick.
            hit.damageWindowAmount=window->second.amount(uint64_t(nowMs()));
        }
    }
    monsterDamageWindows_=std::move(prepared.windows);
    ids_.events=std::move(prepared.events);
    monsterEventAiPending_=std::move(prepared.pending);
}

void World::prepareMonsterEventAiBoundary() {
    if(!actHost_ || freezeAi || (debugOverrides_.enabled && debugOverrides_.pauseAi)) return;
    size_t index=0;
    while(index<monsterEventAiPending_.size()) {
        const auto pending=monsterEventAiPending_[index];
        // Boundary tick N prepares N+1, after all accepted contacts of tick N.
        if(pending.acceptedTick>uint64_t(tick)) {++index;continue;}
        Json outcome={{"kind","monster_event_ai_outcome"},{"owner",pending.target.json()},
            {"accepted_event",pending.hit.eventId},{"attacker",pending.hit.attacker.json()},
            {"accepted_tick",pending.acceptedTick},{"evaluation_tick",tick},{"boundary_tick",uint64_t(tick)+1},
            {"classification","inferred_beta"},{"whole_monster_complete",false}};
        const auto consumeBlocked=[&](const std::string &reason,const Json &details=Json::object()) {
            outcome["ok"]=false;outcome["result"]="blocked";outcome["reason"]=reason;outcome["details"]=details;
            outcome.erase("instance");outcome.erase("action");
            auto diagnostics=monsterEventAiDiagnostics_;appendOutcome(diagnostics,outcome);
            // Terminal failure consumes the event once, without a live random
            // draw or action/instance allocation and without retry rerolls.
            monsterEventAiDiagnostics_=std::move(diagnostics);
            monsterEventAiPending_.erase(monsterEventAiPending_.begin()+std::ptrdiff_t(index));
        };
        try {
            const auto found=monsterEventAiBindings_.find(pending.target);
            const auto *actor=static_cast<const World *>(this)->resolveActor(pending.target);
            if(found==monsterEventAiBindings_.end() || !actor || actor->dead || actor->life!=ActorLife::Alive) {
                consumeBlocked("owner_lifecycle_exit");continue;
            }
            const auto &installed=found->second;
            if(normalize(actor->monsterPath)!=installed.memberPath || actor->sourceId!=installed.sourceId ||
               !explorationAllowsSourceActions(*actor) ||
               sha256(pvf_.read(installed.memberPath))!=installed.route.monsterSource.memberSha256 ||
               sha256(pvf_.read(installed.route.resolvedPath))!=installed.program->source().memberSha256) {
                consumeBlocked("source_binding_changed");continue;
            }
            if(actor->hitStopped || actor->capturedBy>=0 || actor->recovery!=0 || nowMs()<actor->stunUntil ||
               statusStunned(pending.target)) {++index;continue;}
            const auto monster=pvf_.script(installed.memberPath);
            const auto program=installed.program;
            outcome["route"]=installed.route.json();
            auto random=random_;
            auto &stream=random.stream(RandomDomain::MonsterEventAi,installed.randomStreamKey);
            MonsterEventAiContext context;context.owner=pending.target;context.tick=uint64_t(tick);
            context.acceptedHit=pending.hit;
            const auto evaluate=evaluateMonsterEventAi(*program,context,stream,[&](EntityHandle owner,int slot)->std::optional<bool> {
                if(owner!=pending.target) return std::nullopt;
                const auto route=selectMonsterAction(pvf_,monster,"attack",slot);
                if(!route.ok || route.engine!=MonsterActionEngine::Act || !route.cooldownMs) return std::nullopt;
                const auto key=std::make_pair(owner,slot);
                const auto foundCd=sourceActionCooldowns_.find(key);
                return foundCd!=sourceActionCooldowns_.end() && foundCd->second>nowMs();
            });
            outcome["evaluation"]=evaluate.json();
            if(!evaluate.ok || !evaluate.returnedActionIndex || !evaluate.candidateRandom) {
                consumeBlocked("event_ai_evaluation_rejected",evaluate.diagnostics);continue;
            }
            stream=*evaluate.candidateRandom;
            const auto selected=*evaluate.returnedActionIndex;
            if(selected==-1) {
                outcome["ok"]=true;outcome["result"]="authored_no_action";
                auto diagnostics=monsterEventAiDiagnostics_;appendOutcome(diagnostics,outcome);
                random_=std::move(random);monsterEventAiDiagnostics_=std::move(diagnostics);
                monsterEventAiPending_.erase(monsterEventAiPending_.begin()+std::ptrdiff_t(index));
                continue;
            }
            const auto route=selectMonsterAction(pvf_,monster,"attack",selected);
            outcome["action_route"]=route.json();
            if(!route.ok || route.engine!=MonsterActionEngine::Act) {consumeBlocked("event_return_action_route_unavailable");continue;}
            const auto key=std::make_pair(pending.target,selected);
            const auto foundCd=sourceActionCooldowns_.find(key);
            if(foundCd!=sourceActionCooldowns_.end() && foundCd->second>nowMs()) {
                consumeBlocked("event_return_action_in_cooldown");continue;
            }
            if(route.cooldownMs && *route.cooldownMs>INT64_MAX-nowMs()) {
                consumeBlocked("event_return_cooldown_overflow");continue;
            }
            const auto compiled=actHost_->compile(route.resolvedPath);
            if(!compiled.ok) {consumeBlocked("event_return_action_dependencies",compiled.json());continue;}
            auto instances=sourceActionInstanceIds_;auto actionIds=ids_.actions;
            ActBindRequest binding;binding.owner=pending.target;binding.tick=uint64_t(tick);
            binding.simulationMs=uint64_t(nowMs());binding.instanceId=instances.next();binding.actionId=actionIds.next();
            auto &actionStream=random.stream(RandomDomain::Ai,binding.instanceId);
            binding.randomSeed=uint64_t(actionStream.next())<<32;binding.randomSeed|=actionStream.next();
            binding.randomSequence=binding.instanceId;binding.clockMode=ActClockMode::ExternalAnimationDelta;
            auto actors=sourceActionActors_;actors.insert(pending.target);
            auto cooldowns=sourceActionCooldowns_;
            if(route.cooldownMs) cooldowns[key]=nowMs()+*route.cooldownMs;
            outcome["ok"]=true;outcome["result"]="source_action_bound";
            outcome["instance"]=binding.instanceId;outcome["action"]=binding.actionId;
            outcome["action_policy"]="inferred-mob-ai-return-to-authored-action-slot-v1";
            auto diagnostics=monsterEventAiDiagnostics_;appendOutcome(diagnostics,outcome);
            auto testInstances=monsterEventAiTestInstances_;
            if(monsterEventAiTestOwners_.count(pending.target)) testInstances[pending.target]=binding.instanceId;
            ActEntityRelations relations;relations.target=player.handle;relations.lastAttacker=pending.hit.attacker;
            // Host bind owns its complete actor/ID/OnSet transaction. Keep only
            // handles/copies above: successful publication swaps actor storage.
            const auto bound=actHost_->bind(compiled.program,binding,relations,true,&route);
            if(!bound.ok) {consumeBlocked("event_return_action_bind",bound.diagnostics);continue;}
            sourceActionInstanceIds_=std::move(instances);random_=std::move(random);
            sourceActionActors_=std::move(actors);sourceActionCooldowns_=std::move(cooldowns);
            monsterEventAiDiagnostics_=std::move(diagnostics);
            monsterEventAiTestInstances_=std::move(testInstances);
            monsterEventAiPending_.erase(monsterEventAiPending_.begin()+std::ptrdiff_t(index));
            // The ACT host already records source OnSet outputs. Avoid a new
            // allocation after publishing its batch merely for an extra event.
        } catch(const std::exception &error) {
            consumeBlocked("event_ai_boundary_fault",{{"reason",error.what()}});
        }
    }
}

void World::clearMonsterEventAi(const std::string &reason) {
    for(const auto &pending:monsterEventAiPending_) appendOutcome(monsterEventAiDiagnostics_,
        {{"kind","monster_event_ai_outcome"},{"owner",pending.target.json()},{"accepted_event",pending.hit.eventId},
         {"accepted_tick",pending.acceptedTick},{"evaluation_tick",tick},{"ok",false},{"reason",reason},
         {"classification","transient_cancel"},{"whole_monster_complete",false}});
    monsterEventAiPending_.clear();monsterEventAiBindings_.clear();monsterDamageWindows_.clear();
    monsterEventAiNormalAttempts_.clear();monsterEventAiNormalDiagnostics_=Json::array();
    monsterEventAiTestOwners_.clear();monsterEventAiTestInstances_.clear();
    monsterEventAiTestSignature_.clear();monsterEventAiTestSelection_.clear();monsterEventAiTestReceipt_=Json::object();
}
Json World::monsterEventAiState() const {
    Json bindings=Json::array(),pending=Json::array(),windows=Json::array();
    for(const auto &[owner,window]:monsterDamageWindows_)windows.push_back({{"owner",owner.json()},{"window",window.snapshot()}});
    for(const auto &[owner,binding]:monsterEventAiBindings_) bindings.push_back(
        {{"owner",owner.json()},{"source_id",binding.sourceId},{"route",binding.route.json()},
         {"program",binding.program->json()},{"random_stream_key",binding.randomStreamKey}});
    for(const auto &event:monsterEventAiPending_) pending.push_back(
        {{"owner",event.target.json()},{"accepted_tick",event.acceptedTick},{"event_id",event.hit.eventId},
         {"attacker",event.hit.attacker.json()},{"actual_hp_loss",event.hit.actualHpLoss},{"window_amount",event.hit.damageWindowAmount},{"damage_check_enabled",event.hit.damageCheckEnabled},{"window_configuration",event.hit.damageWindowConfiguration}});
    return {{"policy","inferred-accepted-hit-event-ai-next-boundary-v1"},{"bindings",bindings},
        {"pending",pending},{"damage_windows",windows},{"damage_window_policy",monsterDamageWindowPolicy},{"diagnostics",monsterEventAiDiagnostics_},
        {"normal_auto_install",{{"policy","inferred-normal-source-monster-event-ai-install-v1"},{"classification","inferred_beta"},
            {"enabled",bool(actHost_)&&monsterActionAiEnabled_&&combat&&!mapExplorationActive_},
            {"requested_difficulty",monsterActionAiDifficulty_},{"cached_owners",monsterEventAiNormalAttempts_.size()},
            {"diagnostics",monsterEventAiNormalDiagnostics_},{"whole_ai_complete",false}}},
        {"restore_policy","cancel-transient-actions-input-and-effect-instances-v1"},
        {"persistent_continuation",false},{"room_actor_continuation",true},
        {"room_restore_policy",monsterDamageWindowPolicy},{"whole_monster_complete",false}};
}
} // namespace dnf
