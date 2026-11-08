#include "dnf/combat.hpp"
#include "dnf/female_gunner_world.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/squirrel_action_service.hpp"
#include "dnf/monster_behavior.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
World::~World() = default;
void World::configureSourceActions(std::string staticIdentity,bool speech) {
    if(actHost_) throw std::logic_error("World source-action service is already configured");
    actHost_=std::make_unique<ActWorldHost>(*this,pvf_,assets_,std::move(staticIdentity),ActWorldHostOptions{speech,1200});
}
void World::requestSourceMonsterAction(EntityHandle owner,std::string state,int index) {
    if(!actHost_ || !owner || index<0 || state.empty()) throw std::invalid_argument("Source action needs a configured service and explicit owner/state/index");
    if(mapExplorationActive_) {
        const auto *actor=static_cast<const World *>(this)->resolveActor(owner);
        if(!actor || !explorationAllowsSourceActions(*actor)) {
            actServiceDiagnostics_.push_back({{"kind","source_action_blocked"},{"tick",tick},{"owner",owner.json()},
                {"reason","exploration_source_action_consumer_unavailable"}});
            return;
        }
    }
    if(sourceActionRequests_.size()>=1024) throw std::overflow_error("Source action boundary queue is full");
    sourceActionRequests_.push_back({owner,std::move(state),index});
}
void World::cancelSourceActions(const std::string &reason) {
    if(actHost_) {
        const auto result=actHost_->cancelAll(reason);
        if(!result.ok) throw std::runtime_error("ACT cancellation failed: "+result.error);
    }
    sourceActionRequests_.clear();sourceActionActors_.clear();sourceActionVisited_.clear();sourceActionCooldowns_.clear();
    monsterSourceMovements_.clear();
    legacyMonsterMovementPlans_.clear();
}
void World::prepareSourceActionBoundary() {
    if(!actHost_) return;
    synchronizeEntityHandles();
    prepareNormalMonsterEventAiBoundary();
    // Collect handles only. Host publication swaps actor storage and is never
    // performed while an Actor reference from this loop remains in use.
    for(const auto &actor:monsters) if(!actor.dead && actor.life==ActorLife::Alive && actor.handle &&
        actor.sourceStats.contains("spawn") && explorationAllowsSourceActions(actor) && sourceActionVisited_.insert(actor.handle).second) {
        const auto source=pvf_.script(actor.monsterPath);
        const auto route=selectMonsterAction(pvf_,source,"stay");
        const bool sourceAct=std::any_of(source.fields.begin(),source.fields.end(),[](const Field &field) {
            const auto tag=normalize(field.tag);
            return tag=="[basic action]" || tag=="[waiting action]" || tag=="[action list]" || tag=="[attack action]";
        });
        if(route.engine==MonsterActionEngine::Act || sourceAct) {
            sourceActionActors_.insert(actor.handle);
            requestSourceMonsterAction(actor.handle,"stay");
        }
    }
    if(freezeAi || (debugOverrides_.enabled && debugOverrides_.pauseAi)) return;
    prepareMonsterActionAiBoundary();
    auto requests=std::move(sourceActionRequests_);sourceActionRequests_.clear();
    for(auto request:requests) {
        const auto *actor=static_cast<const World *>(this)->resolveActor(request.owner);
        if(!actor || actor==&player || actor->dead || actor->life!=ActorLife::Alive || !explorationAllowsSourceActions(*actor)) continue;
        if(statusStunned(request.owner) || actor->hitStopped || actor->capturedBy>=0 ||
           actor->recovery!=0 || nowMs()<actor->stunUntil) {
            if(request.state!="_source_think") sourceActionRequests_.push_back(std::move(request));
            continue;
        }
        if(request.state=="_source_think") {
            auto decision=prepareMonsterActionAiDecision(request.owner);
            if(!decision) continue;
            request=std::move(*decision);
        }
        const auto actorId=actor->id;
        const auto route=selectMonsterAction(pvf_,pvf_.script(actor->monsterPath),request.state,request.index);
        const auto blocked=[&](const std::string &why,const Json &extra=Json::object()) {
            actServiceDiagnostics_.push_back({{"kind","source_action_blocked"},{"tick",tick},{"owner",request.owner.json()},
                {"route",route.json()},{"reason",why},{"details",extra}});
            events.push_back({tick,"act_blocked",why,actorId});
        };
        if(!route.ok || route.engine!=MonsterActionEngine::Act) {blocked("source_route_unavailable");continue;}
        const auto key=std::make_pair(request.owner,request.index);
        if(request.state=="attack" && sourceActionCooldowns_.count(key) && sourceActionCooldowns_.at(key)>nowMs()) {
            blocked("source_action_cooldown");continue;
        }
        const auto program=actHost_->compile(route.resolvedPath);
        if(!program.ok) {blocked("source_action_dependencies",program.json());continue;}
        if(request.state=="attack" && route.cooldownMs && *route.cooldownMs>INT64_MAX-nowMs()) {
            blocked("source_action_cooldown_overflow");continue;
        }
        // New identities and the source-action random stream stay private until
        // bind has accepted its complete replacement batch, including OnSet.
        auto instances=sourceActionInstanceIds_;auto actionIds=ids_.actions;auto random=random_;
        if(request.aiRandom) random.stream(RandomDomain::Ai,0)=*request.aiRandom;
        auto aiDiagnostics=monsterActionAiDiagnostics_;
        if(request.aiRandom) {
            request.aiTrace["result"]="source_action_bound";
            aiDiagnostics.push_back(std::move(request.aiTrace));
            if(aiDiagnostics.size()>256) aiDiagnostics.erase(aiDiagnostics.begin(),aiDiagnostics.begin()+std::ptrdiff_t(aiDiagnostics.size()-256));
        }
        ActBindRequest binding;binding.owner=request.owner;binding.tick=uint64_t(tick);binding.simulationMs=uint64_t(nowMs());
        binding.instanceId=instances.next();binding.actionId=actionIds.next();
        auto &stream=random.stream(RandomDomain::Ai,binding.instanceId);
        binding.randomSeed=uint64_t(stream.next())<<32;binding.randomSeed|=stream.next();
        binding.randomSequence=binding.instanceId;
        binding.clockMode=ActClockMode::ExternalAnimationDelta;
        ActEntityRelations relations;relations.target=player.handle;
        const auto result=actHost_->bind(program.program,binding,relations,true,&route);
        if(!result.ok) {blocked("source_action_bind",result.diagnostics);continue;}
        sourceActionInstanceIds_=std::move(instances);random_=std::move(random);
        monsterActionAiDiagnostics_=std::move(aiDiagnostics);
        sourceActionActors_.insert(request.owner);
        if(request.state=="attack" && route.cooldownMs) {
            sourceActionCooldowns_[key]=nowMs()+*route.cooldownMs;
        }
        actServiceDiagnostics_.push_back({{"kind","source_action_bound"},{"tick",tick},{"owner",request.owner.json()},
            {"route",route.json()},{"instance",binding.instanceId},{"action",binding.actionId},
            {"policy","inferred-source-action-next-boundary-v1"},{"whole_monster_complete",false}});
        events.push_back({tick,"source_action",route.resolvedPath,actorId,request.index});
    }
    if(actServiceDiagnostics_.size()>256) actServiceDiagnostics_.erase(actServiceDiagnostics_.begin(),
        actServiceDiagnostics_.begin()+std::ptrdiff_t(actServiceDiagnostics_.size()-256));
}
void World::advanceSourceActions(const SimulationStep &step) {
    if(!actHost_) return;
    std::map<uint64_t,uint64_t> deltas;
    for(const auto &[id,instance]:actHost_->instances()) if(instance.status==ActInstanceStatus::Running &&
        instance.clockMode==ActClockMode::ExternalAnimationDelta) {
        const auto *actor=static_cast<const World *>(this)->resolveActor(instance.owner);
        deltas[id]=actor && explorationAllowsSourceActions(*actor) && !actor->hitStopped && !statusStunned(instance.owner) &&
            !freezeAi && !(debugOverrides_.enabled && debugOverrides_.pauseAi)?uint64_t(step.deltaMilliseconds)*1000:0;
    }
    const auto result=actHost_->advance(step,deltas);
    if(!result.ok) throw std::runtime_error("Fixed-tick ACT service failed: "+result.error);
}
} // namespace dnf
