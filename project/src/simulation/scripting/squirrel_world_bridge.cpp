#include "dnf/squirrel_world_bridge.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <type_traits>

namespace dnf {
namespace {
bool equal(const SourceRef &a,const SourceRef &b) { return a.json()==b.json(); }
bool allocated(uint64_t id,uint64_t next) noexcept { return id && (!next || id<next); }
bool notRewound(uint64_t next,uint64_t prior) noexcept { return !next || (prior && next>=prior); }
AttackResponse response(const Script &source) {
    auto out=readAttackResponse(source);
    // This internal script bridge has no qualified weapon-inheritance receipt.
    // Keep its existing explicit rejection; do not turn -1 into zero timing.
    if(!out.hitInfo.empty() && (out.hitInfo[2].get<double>()<0 || out.hitInfo[3].get<double>()<0))
        throw std::invalid_argument("ATK requires unresolved weapon hit-pause inheritance");
    return out;
}
} // namespace

struct SquirrelWorldBridge::SoundBatch final : squirrel_stage::PreparedSoundBatch {
    SquirrelWorldBridge *bridge = nullptr;
    int64_t tick = 0;
    size_t priorEventCount = 0;
    uint64_t priorSequence = 0;
    uint64_t lastSequence = 0;
    std::vector<Event> events;
    Json receipts = Json::array();
};
SquirrelWorldBridge::SquirrelWorldBridge(World &world,Pvf &pvf,Assets &assets,std::string staticIdentity,
    SquirrelInvocationContext context):world_(world),pvf_(pvf),assets_(assets),resources_(pvf,assets,std::move(staticIdentity)),
    context_(std::move(context)),character_(world.identity()),thread_(std::this_thread::get_id()) {
    if(&pvf_!=&world_.pvf_||&assets_!=&world_.assets_)
        throw std::invalid_argument("Squirrel bridge must use its World's Pvf and Assets providers");
    if(!context_.instanceId||!context_.actionId||!valid(context_.owner)||context_.owner!=world.player.handle)
        throw std::invalid_argument("Squirrel context requires an existing live player instance/action/handle");
    if(!world.usesSourceGrowth())throw std::invalid_argument("Squirrel source bridge requires source-growth World rules");
    requestWatermark_=world_.ids_.requests.nextValue();actionWatermark_=world_.ids_.actions.nextValue();
    attackWatermark_=world_.ids_.attacks.nextValue();
    if(!allocated(context_.instanceId,requestWatermark_)||!allocated(context_.actionId,actionWatermark_))
        throw std::invalid_argument("Squirrel context IDs must already be issued by World request/action sources");
    if(context_.buffSkill) {
        if(context_.buffSkill->jobId!=character_.jobId)throw std::invalid_argument("Squirrel Buff event skill belongs to another job");
        const auto &skill=world.characterCatalog().skillDefinition(*context_.buffSkill);
        buffSkillSource_=makeSourceRef(pvf,skill.source.script.path);
        if(sha256(skill.source.script.rawBytes)!=buffSkillSource_->memberSha256)
            throw std::invalid_argument("Buff event SKL source changed during admission");
    }
}
void SquirrelWorldBridge::requireContext() const {
    if(thread_!=std::this_thread::get_id()||closed_||!(world_.identity()==character_)||!valid(context_.owner)||
       !notRewound(world_.ids_.requests.nextValue(),requestWatermark_)||
       !notRewound(world_.ids_.actions.nextValue(),actionWatermark_)||
       !notRewound(world_.ids_.attacks.nextValue(),attackWatermark_)||
       !allocated(context_.instanceId,world_.ids_.requests.nextValue())||
       !allocated(context_.actionId,world_.ids_.actions.nextValue()))
        throw std::invalid_argument("Squirrel context is closed, stale or on another simulation thread");
}
bool SquirrelWorldBridge::valid(EntityHandle handle) const noexcept {
    if(thread_!=std::this_thread::get_id()||closed_||world_.player.handle!=context_.owner||!(world_.identity()==character_))return false;
    const auto *actor=static_cast<const World &>(world_).resolveActor(handle);
    return actor&&!actor->dead&&actor->life==ActorLife::Alive;
}
squirrel_stage::SourceUnit SquirrelWorldBridge::source(const std::string &member) {
    requireContext();const auto path=normalize(member);
    if(path.rfind("sqr/",0)!=0||path.size()<4||path.substr(path.size()-4)!=".nut")throw std::invalid_argument("Expected a PVF Squirrel member");
    const auto prior=sources_.find(path);if(prior!=sources_.end())return prior->second;
    squirrel_stage::SourceUnit unit;unit.source=makeSourceRef(pvf_,path);unit.original=pvf_.read(path);
    if(sha256(unit.original)!=unit.source.memberSha256)throw std::invalid_argument("Squirrel source changed during admission");
    sources_.emplace(path,unit);return unit;
}
bool SquirrelWorldBridge::admittedScript(const SourceRef &source) const {
    const auto found=sources_.find(source.memberPath);return found!=sources_.end()&&equal(source,found->second.source);
}
SourceRef SquirrelWorldBridge::attackSource(const std::string &tag,size_t slot,size_t occurrence) {
    requireContext();const auto path=world_.characterSource().attackInfo(tag,slot,occurrence);
    if(path.empty())throw std::invalid_argument("No own-character CHR attack-info binding");
    auto source=makeSourceRef(pvf_,path);auto document=pvf_.script(path);
    if(sha256(document.rawBytes)!=source.memberSha256)throw std::invalid_argument("CHR ATK source changed during admission");
    const auto prior=attacks_.find(source.memberPath);
    if(prior!=attacks_.end()) {
        if(!equal(prior->second.source,source))throw std::invalid_argument("CHR ATK identity changed after admission");
        return prior->second.source;
    }
    attacks_.emplace(source.memberPath,AdmittedAttack{source,std::move(document)});return source;
}
bool SquirrelWorldBridge::admittedAttack(const SourceRef &source) const {
    const auto found=attacks_.find(source.memberPath);
    return found!=attacks_.end()&&equal(source,found->second.source);
}
int SquirrelWorldBridge::buffSkillIndex(EntityHandle owner) const {
    requireContext();if(owner!=context_.owner||!context_.buffSkill||!buffSkillSource_)
        throw std::invalid_argument("No same-owner source Buff event context");return context_.buffSkill->skillId;
}
std::optional<SourceRef> SquirrelWorldBridge::resolveSound(const std::string &tag,const SourceRef &origin) const {
    requireContext();if(!admittedScript(origin))throw std::invalid_argument("Sound origin was not admitted from this PVF");
    const auto resolved=resources_.resolve({ActResourceKind::Sound,origin,tag,-1});
    if(!resolved.found||!resolved.runtimeSupported||!resolved.transitiveClosureKnown)return std::nullopt;
    resolvedSounds_[{origin.memberPath,tag}]=resolved;return resolved.source;
}
std::unique_ptr<squirrel_stage::PreparedSoundBatch> SquirrelWorldBridge::prepare(const std::vector<squirrel_stage::SoundCommand> &commands) {
    requireContext();auto batch=std::make_unique<SoundBatch>();batch->bridge=this;batch->tick=world_.tick;
    batch->priorEventCount=world_.events.size();batch->priorSequence=lastSoundSequence_;
    batch->events=world_.events;batch->receipts=soundReceipts_;batch->lastSequence=lastSoundSequence_;
    for(const auto &command:commands) {
        if(command.instanceId!=context_.instanceId||command.actionId!=context_.actionId||command.owner!=context_.owner||
           !valid(command.owner)||!admittedScript(command.scriptSource)||command.sequence<=batch->lastSequence)
            throw std::invalid_argument("Squirrel sound command instance/action/source/sequence mismatch");
        const auto sound=resolvedSounds_.find({command.scriptSource.memberPath,command.tag});
        if(sound==resolvedSounds_.end())throw std::invalid_argument("Squirrel sound has no prior typed resolver receipt");
        const auto &resolved=sound->second;
        if(!resolved.found||!resolved.runtimeSupported||!resolved.transitiveClosureKnown||!equal(resolved.source,command.soundSource))
            throw std::invalid_argument("Squirrel sound dependency receipt differs");
        Json dependencies=Json::array();for(const auto &dependency:resolved.transitive)dependencies.push_back(dependency.json());
        batch->events.push_back({world_.tick,"sound",command.tag,world_.player.id});
        batch->receipts.push_back({{"instance_id",command.instanceId},{"action_id",command.actionId},{"sequence",command.sequence},
            {"owner",command.owner.json()},{"script_source",command.scriptSource.json()},{"sound_source",command.soundSource.json()},
            {"dependencies",std::move(dependencies)},{"consumer","World Event.sound -> existing main Audio::play"},
            {"vm_policy",squirrel_stage::vmPolicyId},{"native_dynamic_comparison","pending user"}});
        batch->lastSequence=command.sequence;
    }
    return batch;
}
void SquirrelWorldBridge::commit(std::unique_ptr<squirrel_stage::PreparedSoundBatch> prepared) noexcept {
    // Host prepare/commit are consecutive on one simulation thread. Reject
    // foreign/stale external misuse without publishing a partial batch.
    auto *batch=dynamic_cast<SoundBatch *>(prepared.get());
    if(!batch||batch->bridge!=this||closed_||thread_!=std::this_thread::get_id()||batch->tick!=world_.tick||
       batch->priorEventCount!=world_.events.size()||batch->priorSequence!=lastSoundSequence_||!valid(context_.owner)||
       !notRewound(world_.ids_.requests.nextValue(),requestWatermark_)||
       !notRewound(world_.ids_.actions.nextValue(),actionWatermark_)||
       !notRewound(world_.ids_.attacks.nextValue(),attackWatermark_))return;
    world_.events.swap(batch->events);soundReceipts_.swap(batch->receipts);lastSoundSequence_=batch->lastSequence;
}
void SquirrelWorldBridge::cleanup(uint64_t instance,const std::string &) noexcept {
    if(instance!=context_.instanceId||closed_)return;closed_=true;++cleanupCount_;
    attackIdentities_.clear();contacts_.clear();resolvedSounds_.clear();
    // Immediate consumers only. Never retract committed HP/rewards/sounds.
    // No persistent factory is registered. Future factories must implement
    // instance-owned cancellation here before their APIs can be admitted.
}
SquirrelContactResult SquirrelWorldBridge::applySourceContacts(const std::vector<SquirrelSourceContact> &commands) {
    SquirrelContactResult result;
    try {
        requireContext();if(commands.empty()){result.ok=true;return result;}
        if(commands.size()>64||!world_.combat||!world_.combatAttributes_)
            throw std::invalid_argument("Source contact needs combat, prepared attributes and a bounded batch");
        World candidate(pvf_,assets_,world_.rules_); // No external callbacks/ACT host.
        candidate.identity_=world_.identity_;candidate.player=world_.player;candidate.monsters=world_.monsters;
        candidate.events=world_.events;candidate.clock_=world_.clock_;candidate.tick=world_.tick;
        candidate.entities_=world_.entities_;candidate.ids_=world_.ids_;candidate.random_=world_.random_;candidate.statuses_=world_.statuses_;
        candidate.effectIds_=world_.effectIds_;candidate.pendingEffects_=world_.pendingEffects_;
        candidate.combatAttributes_=world_.combatAttributes_;candidate.lastDamageTrace_=world_.lastDamageTrace_;
        // Keep source-motion fallback and incoming admission identical to the
        // live exploration policy. These are value receipts, not services.
        candidate.combat=world_.combat;candidate.mapWidth=world_.mapWidth;
        candidate.walkRects=world_.walkRects;candidate.blockedRects=world_.blockedRects;
        candidate.mapExplorationActive_=world_.mapExplorationActive_;
        candidate.mapExplorationGeometryAvailable_=world_.mapExplorationGeometryAvailable_;
        candidate.explorationConsumers_=world_.explorationConsumers_;
        candidate.monsterEventAiBindings_=world_.monsterEventAiBindings_;
        candidate.monsterEventAiPending_=world_.monsterEventAiPending_;
        candidate.monsterDamageWindows_=world_.monsterDamageWindows_;
        auto identities=attackIdentities_;auto contacts=contacts_;auto receipts=contactReceipts_;
        for(const auto &entry:identities)if(!allocated(entry.second.worldId,candidate.ids_.attacks.nextValue()))
            throw std::invalid_argument("Existing Squirrel attack identity exceeds the current World attack watermark");
        for(const auto &command:commands) {
            if(command.instanceId!=context_.instanceId||command.actionId!=context_.actionId||command.owner!=context_.owner||
               !command.attackOrdinal||!admittedScript(command.scriptSource)||!admittedAttack(command.attackSource))
                throw std::invalid_argument("Source contact has a foreign action/script or unadmitted CHR ATK");
            if(command.weaponTypePolicy!="blocked"&&command.weaponTypePolicy!="physical"&&command.weaponTypePolicy!="magical")
                throw std::invalid_argument("Unknown source contact weapon-type policy");
            auto found=identities.find(command.attackOrdinal);
            if(found!=identities.end()&&(!equal(found->second.source,command.attackSource)||found->second.weaponTypePolicy!=command.weaponTypePolicy))
                throw std::invalid_argument("One attack identity cannot change its ATK or weapon policy");
            const ContactIdentity contact{command.attackOrdinal,command.hitIndex,command.target};
            const auto *live=static_cast<const World &>(world_).resolveActor(command.target);
            auto *target=const_cast<Actor *>(static_cast<const World &>(candidate).resolveActor(command.target));
            if(!live||!target||target==&candidate.player||!target->combatAttributes||
               !world_.explorationAllowsIncoming(*live)||!candidate.explorationAllowsIncoming(*target))
                throw std::invalid_argument("Target is stale or lacks an incoming source consumer");
            // A still-registered dying actor can acknowledge its accepted
            // lethal pulse. Retired/removed handles cannot pass this branch.
            if(contacts.count(contact)){++result.duplicates;continue;}
            if(target->dead||target->life!=ActorLife::Alive)throw std::invalid_argument("A new pulse cannot damage a dead target");
            if(found==identities.end())found=identities.emplace(command.attackOrdinal,AttackIdentity{candidate.ids_.attacks.next(),command.attackSource,command.weaponTypePolicy}).first;
            const auto &source=attacks_.at(command.attackSource.memberPath).document;const auto reaction=response(source);
            if(!reaction.sound.empty()) {
                const auto sound=resources_.resolve({ActResourceKind::Sound,command.attackSource,reaction.sound,-1});
                if(!sound.found||!sound.runtimeSupported)throw std::invalid_argument("ATK hit sound has no executable audio consumer");
            }
            const auto policy=DamageResolutionPolicy::inferredPveDamageV1(candidate.combatAttributes_->damageConstants);
            DamageRequest request;request.attacker=context_.owner;request.target=target->handle;request.attackInstance=found->second.worldId;
            request.hitIndex=command.hitIndex;request.attackerStats=makeDamageCombatant(*candidate.combatAttributes_);
            request.targetStats=makeDamageCombatant(*target->combatAttributes,policy);request.attack=readAttackDamage(source,AttackStatusConsumer::StunHostV1);
            if(command.weaponTypePolicy!="blocked")request.weaponType=command.weaponTypePolicy=="physical"?DamageAttackType::Physical:DamageAttackType::Magical;
            request.skill.sources.push_back({{"policy","inferred-squirrel-bridge-source-atk-only-v1"},{"classification","inferred"},
                {"basis","Own CHR ATK operands use unified World damage with neutral skill coefficients"},
                {"unverified_conditions","Native callback routing, SKL coefficients, passives and PO packet chains unresolved"},
                {"impact","No skill coefficients or learning are granted by this internal C++ contact interface"},
                {"script_source",command.scriptSource.json()},{"weapon_type_policy",command.weaponTypePolicy}});
            auto accepted=candidate.prepareMonsterAcceptedHit(*target,"squirrel_source_contact");
            if(!accepted.ready)throw std::invalid_argument("Accepted-hit preparation blocked: "+accepted.error);
            const auto outcome=candidate.resolveActorContact(request,makeMonsterStatusResistances(*target->combatAttributes));
            if(!outcome.usable())throw std::invalid_argument("Damage/status transaction blocked: "+outcome.snapshot().dump());
            candidate.lastDamageTrace_=outcome.snapshot();contacts.insert(contact);++result.accepted;
            if(outcome.missed)candidate.events.push_back({candidate.tick,"miss",source.path,0,target->id});
            else {
                const int amount=*outcome.hpDamage,acceptedHpLoss=std::min(target->hp,amount);
                target->hp=std::max(0,target->hp-amount);
                target->lastImpact=monsterDeathImpulse(target->x-candidate.player.x,target->y-candidate.player.y,candidate.player.dir,
                    std::hypot(candidate.player.vx,candidate.player.vy),amount,target->maxHp,reaction.push,reaction.lift);
                target->hitFlashUntil=candidate.nowMs()+80;if(!target->hp)candidate.beginDeath(*target);
                candidate.requestHitStop(*target,reaction.hitPause,source.path);
                candidate.requestHitStop(candidate.player,reaction.hitPause,source.path);
                if(!target->dead) {
                    if(!reaction.noReaction) {
                        candidate.applyResponse(*target,reaction,candidate.player.dir);
                        candidate.applyMonsterHurtMotion(*target,reaction);
                    }
                    candidate.interruptStatusTarget(*target);
                }
                candidate.events.push_back({candidate.tick,"hit","squirrel_source_contact",0,target->id,amount});
                candidate.publishMonsterHitFeedback(*target,reaction,candidate.player.dir,amount,false,nullptr,outcome.critical);
                candidate.publishMonsterAcceptedHit(std::move(accepted),acceptedHpLoss);
            }
            Json receipt={{"instance_id",context_.instanceId},{"action_id",context_.actionId},{"attack_ordinal",command.attackOrdinal},
                {"hit_index",command.hitIndex},{"target",command.target.json()},{"script_source",command.scriptSource.json()},
                {"attack_source",command.attackSource.json()},{"outcome",outcome.snapshot()},{"native_callback_chain_complete",false}};
            result.receipts.push_back(receipt);receipts.push_back(std::move(receipt));
        }
        static_assert(std::is_nothrow_swappable<Actor>::value&&std::is_nothrow_swappable<StatusHost>::value&&
            std::is_nothrow_swappable<RandomStreams>::value&&std::is_nothrow_swappable<SimulationIdSources>::value&&
            std::is_nothrow_swappable<MonotonicIds>::value,"Contact publication must not throw");
        using std::swap;swap(world_.player,candidate.player);world_.monsters.swap(candidate.monsters);world_.events.swap(candidate.events);
        swap(world_.statuses_,candidate.statuses_);swap(world_.random_,candidate.random_);swap(world_.ids_.attacks,candidate.ids_.attacks);
        swap(world_.ids_.events,candidate.ids_.events);
        world_.monsterEventAiPending_.swap(candidate.monsterEventAiPending_);
        world_.monsterDamageWindows_.swap(candidate.monsterDamageWindows_);
        swap(world_.effectIds_,candidate.effectIds_);world_.pendingEffects_.swap(candidate.pendingEffects_);
        world_.lastDamageTrace_.swap(candidate.lastDamageTrace_);attackIdentities_.swap(identities);contacts_.swap(contacts);contactReceipts_.swap(receipts);
        attackWatermark_=world_.ids_.attacks.nextValue();
        result.ok=true;
    }catch(const std::exception &error){result.ok=false;result.accepted=result.duplicates=0;result.receipts=Json::array();
        result.diagnostics.push_back({{"code","squirrel_world_contact_batch_rejected"},{"message",error.what()}});}
    return result;
}
Json SquirrelWorldBridge::diagnostics() const {
    return {{"vm_policy",squirrel_stage::vmPolicyId},{"closed",closed_},{"cleanup_count",cleanupCount_},
        {"instance_id",context_.instanceId},{"action_id",context_.actionId},{"owner",context_.owner.json()},
        {"buff_skill",context_.buffSkill?context_.buffSkill->json():Json()},{"buff_skill_source",buffSkillSource_?buffSkillSource_->json():Json()},
        {"sound_receipts",soundReceipts_},{"contact_receipts",contactReceipts_},{"source_damage_native_api_registered",false},
        {"persistent_entity_factory_registered",false},{"runtime_complete",false},{"native_dynamic_comparison","pending user"}};
}
} // namespace dnf
