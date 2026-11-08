#include "dnf/experimental_character.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/combat.hpp"
#include "dnf/character_attack.hpp"
#include "dnf/collision.hpp"
#include "dnf/female_gunner_world.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/audio_catalog.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace dnf {
namespace {
Json selectedValues(const Script &source,const std::string &wanted) {
    bool pvp=false;Json selected=Json::array();size_t count=0;
    for(const auto &field:source.fields) {
        const auto tag=normalize(field.tag);
        if(tag=="[pvp]"){pvp=true;continue;}if(tag=="[/pvp]"){pvp=false;continue;}
        if(!pvp&&tag==wanted){selected=field.values;++count;}
    }
    if(count>1)throw std::invalid_argument("Ambiguous experimental ATK response: "+wanted);
    return selected;
}
DamageSkillModifiers sourceModifiers(const ExperimentalAttackFrame &frame) {
    if (frame.skillModifiers) return *frame.skillModifiers;
    DamageSkillModifiers out;
    out.sources.push_back({{"policy","inferred-experimental-source-atk-100-percent-v1"},{"classification","inferred"},
        {"basis","ATK numeric operands are executable; SKL level-info column semantics require a job-specific controller"},
        {"unverified_conditions","Native skill coefficients, projectile/OBJ creation, repeat-hit and passive chains unresolved"},
        {"impact","Apply this job's selected source ATK once per action/target at 100 percent; no borrowed skill formula"},
        {"motion",frame.motion.json()},{"attack",frame.attack?frame.attack->json():Json()},
        {"skill",frame.skill?frame.skill->json():Json()}});
    return out;
}
}
void World::enableExperimentalCharacters() {
    if(experimentalEnabled_)return;
    auto candidate=controllers_;registerExperimentalControllers(candidate,characters_,pvf_.identity());
    registerSourceAdvancementAdapters(candidate,characters_,advancementCatalog(),pvf_.identity());
    controllers_=std::move(candidate);experimentalEnabled_=true;
}
bool World::isExperimentalCharacter() const {return bool(experimentalRuntime_);}
ExperimentalCharacterRuntime *World::experimentalRuntime(){return experimentalRuntime_.get();}
const ExperimentalCharacterRuntime *World::experimentalRuntime() const{return experimentalRuntime_.get();}
Json World::experimentalDiagnostics() const {
    return {{"enabled",experimentalEnabled_},{"active",isExperimentalCharacter()},
        {"runtime",experimentalRuntime_?experimentalRuntime_->snapshotDiagnostics():Json()},
        {"world",experimentalDiagnostics_},{"squirrel_actions",squirrelActionDiagnostics()},
        {"female_gunner",femaleGunnerDiagnostics()}};
}
const std::vector<Skill> &World::compatibilitySkillView(CharacterIdentity identity,bool passive) const {
    static const std::vector<Skill> empty;
    if(identity.jobId!=0)return empty;
    return passive?swordmanPassives_:swordmanSkills_;
}
std::unique_ptr<ExperimentalCharacterRuntime> World::prepareExperimentalRuntime(CharacterIdentity identity,const Json &saved) const {
    if(!experimentalEnabled_||identity.jobId==0||!supportsCharacter(identity))
        throw std::invalid_argument("Prepared runtime requires an explicitly admitted experimental identity");
    auto plan=std::make_shared<ExperimentalCharacterPlan>(loadExperimentalCharacterPlan(pvf_,assets_,characters_,identity,&advancementCatalog()));
    auto runtime=std::make_unique<ExperimentalCharacterRuntime>(std::move(plan));
    runtime->setAnimationClockPolicy(animationClockPolicy_);
    runtime->setBasicAttackMovementEnabled(basicMovementPolicy_.enabled);
    if(!saved.is_null())runtime->configuration().restore(saved,runtime->plan());
    return runtime;
}
ExperimentalSkillConfiguration World::prepareExperimentalSkillConfiguration(CharacterIdentity identity,const Json &saved) const {
    if(!experimentalEnabled_||identity.jobId==0||!supportsCharacter(identity))
        throw std::invalid_argument("Experimental saved configuration needs an explicitly enabled supported experimental identity");
    const auto plan=loadExperimentalCharacterPlan(pvf_,assets_,characters_,identity,&advancementCatalog());
    ExperimentalSkillConfiguration candidate(plan);if(!saved.is_null())candidate.restore(saved,plan);return candidate;
}
std::map<SkillKey,int64_t> World::prepareExperimentalCooldownRestore(CharacterIdentity identity,const Json &saved,int64_t restoredNowMs) const {
    if(!experimentalEnabled_||identity.jobId==0||!supportsCharacter(identity))
        throw std::invalid_argument("Experimental cooldown restore needs an explicitly enabled supported experimental identity");
    const auto plan=loadExperimentalCharacterPlan(pvf_,assets_,characters_,identity,&advancementCatalog());
    return ExperimentalCharacterRuntime::prepareCooldownRestore(saved,plan,restoredNowMs);
}
ExperimentalWorldAdapter::ExperimentalWorldAdapter(World &world):world_(world){}
void ExperimentalWorldAdapter::clearSourceGrab(bool releasedByHit) noexcept {
    if(!sourceCapture_)return;
    const auto capture=*sourceCapture_;
    sourceCapture_.reset();
    // Renewed room/character handles cannot release a later incarnation. A
    // different capture owner must likewise retain its own actor state.
    auto *target=const_cast<Actor *>(static_cast<const World &>(world_).resolveActor(capture.target));
    if(!target||target==&world_.player||target->capturedBy!=0)return;
    target->capturedBy=-1;
    if(target->dead||target->life!=ActorLife::Alive||releasedByHit)return;
    target->vx=target->vy=target->vz=0;
    target->hitReaction={};
    // Cancelled holds drop through the shared source hurt/down lifecycle;
    // there is no synthetic attack, HP write or delayed damage on cleanup.
    target->recovery=target->z>0?1:0;
}
bool ExperimentalWorldAdapter::updateCapturedPose(Actor &target) {
    if(!sourceCapture_||sourceCapture_->target!=target.handle)return false;
    const auto *runtime=world_.experimentalRuntime_.get();
    const auto grab=runtime?runtime->sourceGrabState():std::nullopt;
    if(!runtime||!grab||!grab->holding||grab->ownerAction!=sourceCapture_->ownerAction||
       !(grab->key==sourceCapture_->key)||world_.player.handle!=sourceCapture_->owner||
       world_.player.dead||world_.player.hp<=0||world_.player.life!=ActorLife::Alive||
       target.dead||target.life!=ActorLife::Alive||target.capturedBy!=0) {
        clearSourceGrab();return false;
    }
    const auto &player=world_.player;
    const double x=player.x+player.dir*grab->offset[0],y=player.y+grab->offset[1];
    // Native Fighter has placement/fallback queries rather than teleporting
    // a held victim through a wall. This host uses the existing walk geometry.
    if(world_.canWalk(x,y)){target.x=x;target.y=y;}
    else {target.x=player.x;target.y=player.y;}
    target.z=std::max(0.0,player.z+grab->offset[2]);
    target.dir=-player.dir;target.vx=target.vy=target.vz=0;
    return true;
}
bool ExperimentalWorldAdapter::trySourceGrab(Actor &target,const ExperimentalAttackFrame &frame,ExperimentalCharacterRuntime &runtime) {
    auto &world=world_;
    if(!frame.sourceGrabTry||!frame.sourceGrabOwner||!frame.skill||frame.sourceEntity||sourceCapture_||
       target.dead||target.hp<=0||target.life!=ActorLife::Alive||target.capturedBy>=0||
       !target.handle||static_cast<const World &>(world).resolveActor(target.handle)!=&target||!world.explorationAllowsIncoming(target))return false;
    const auto grab=runtime.sourceGrabState();
    if(!grab||grab->holding||grab->ownerAction!=frame.sourceGrabOwner||!(grab->key==*frame.skill))return false;
    try {
        if(world.mapExplorationActive_) {
            const auto cap=world.explorationConsumers_.find(target.handle);
            if(cap==world.explorationConsumers_.end()||!cap->second.captureAllowed)return false;
        } else {
            // The same explicit MOB gate applies outside the all-map preview.
            // Absent old-MOB flag follows its recorded legacy-absent policy;
            // malformed or explicit false never becomes a debug bypass.
            const auto flag=selectedValues(world.pvf_.script(target.monsterPath),"[is grabable]");
            if(!flag.empty()&&(flag.size()!=1||!flag[0].is_number_integer()||flag[0]!=1))return false;
        }
        Actor held=target;
        const auto pose=world.monsterMotion(held,"damage2");
        if(!pose->valid())throw std::invalid_argument("Source capture victim has no authored hurt pose");
        held.animation="damage2";held.animationPath=pose->base->path;held.animStart=world.nowMs();held.poseFrame=-1;
        held.animationClock.reset();held.animationClockSource.clear();held.animationControllerDelays.reset();
        held.capturedBy=0;held.vx=held.vy=held.vz=0;held.recovery=0;held.hitReaction={};
        const double x=world.player.x+world.player.dir*grab->offset[0],y=world.player.y+grab->offset[1];
        if(world.canWalk(x,y)){held.x=x;held.y=y;}
        else {held.x=world.player.x;held.y=world.player.y;}
        held.z=std::max(0.0,world.player.z+grab->offset[2]);held.dir=-world.player.dir;
        const SourceCapture capture{target.handle,world.player.handle,*frame.skill,frame.sourceGrabOwner};
        Json diagnostics=world.experimentalDiagnostics_;
        if(diagnostics.size()>=256)diagnostics.erase(diagnostics.begin());
        diagnostics.push_back({{"code","source_fighter_grab_accepted"},{"skill",frame.skill->json()},
            {"owner_action",frame.sourceGrabOwner},{"target",target.handle.json()},
            {"policy","40jp-fighter-grab-owner-source-box-v1"},{"try_deals_damage",false},
            {"capture_persisted",false},{"tick",world.tick},{"runtime_complete",false}});
        // Preparing the source pose precedes runtime acceptance. The following
        // publications cannot throw or consume damage/status/AI random draws.
        if(!runtime.acceptSourceGrabHit(frame.sourceGrabOwner))return false;
        static_assert(std::is_nothrow_swappable<Actor>::value,"Source capture actor publication must not throw");
        using std::swap;swap(target,held);sourceCapture_=capture;
        world.experimentalDiagnostics_.swap(diagnostics);
        return true;
    } catch(const std::exception &error) {
        record({{"code","source_fighter_grab_rejected"},{"target",target.handle.json()},{"message",error.what()}});
        return false;
    }
}
bool ExperimentalWorldAdapter::movingReactionReady(const ExperimentalCharacterRuntime &runtime) const noexcept {
    if(sourceCapture_||!runtime.sourceMovingReactionReady())return false;
    for(const auto &entry:sourceContactLedgers_)if(!runtime.sourceSkillEntityLive(entry.first))return false;
    return true;
}
void ExperimentalWorldAdapter::record(Json diagnostic) {
    auto &rows=world_.experimentalDiagnostics_;if(rows.size()>=256)rows.erase(rows.begin());
    diagnostic["tick"]=world_.tick;diagnostic["runtime_complete"]=false;rows.push_back(std::move(diagnostic));
}
bool ExperimentalWorldAdapter::contact(Actor &target,const ExperimentalAttackFrame &frame,const AttackDamageDefinition &attack,const CombatBox *intersection) {
    auto &world=world_;if(target.dead||target.life!=ActorLife::Alive)return false;
    if(!world.explorationAllowsIncoming(target)) {
        record({{"code","experimental_exploration_incoming_consumer_unavailable"},{"target",target.id}});
        return false;
    }
    if(!world.combatAttributes_||!target.combatAttributes) {
        record({{"code","experimental_source_damage_inputs_required"},{"target",target.id},{"attack",attack.source.path}});return false;
    }
    if(frame.sourceFrame>UINT32_MAX)throw std::overflow_error("Experimental source frame exceeds contact identity range");
    AttackResponse response;
    try{response=world.characterAttackResponse(attack.source);}catch(const std::exception &error){record({{"code","experimental_response_blocked"},{"message",error.what()}});return false;}
    Actor origin;
    origin.x=frame.sourceEntity?frame.sourceOrigin[0]:world.player.x;
    origin.y=frame.sourceEntity?frame.sourceOrigin[1]:world.player.y;
    origin.z=frame.sourceEntity?frame.sourceOrigin[2]:world.player.z;
    origin.dir=frame.sourceEntity?frame.sourceDirection:world.player.dir;
    if(frame.sourceLift)response.lift=*frame.sourceLift;
    auto &targets=frame.sourceEntity?sourceContactLedgers_.at(frame.sourceEntityInstance).targets:hitTargets_;
    const auto attackInstance=frame.sourceEntity?sourceContactLedgers_.at(frame.sourceEntityInstance).attackId:attackId_;
    const auto policy=DamageResolutionPolicy::inferredPveDamageV1(world.combatAttributes_->damageConstants);
    DamageRequest request;request.attacker=world.player.handle;request.target=target.handle;
    request.attackInstance=attackInstance;request.hitIndex=frame.pulseId;
    if(frame.sourceEntity && frame.skill) {
        const auto &descriptor=world.experimentalRuntime_->plan().sourceSkillActions.at(*frame.skill);
        bindDamageContactRange(request,world.pvf_.script(frame.sourceImpact?descriptor.movingImpact->impactObject.memberPath:descriptor.object.memberPath));
    } else {
        request.contactRange=DamageContactRange::Melee;
        request.contactRangeSource={{"policy","inferred-body-attack-contact-range-v1"},{"classification","inferred_beta"},
            {"basis","Experimental root-body type15 contact; spawned skill entities use separate object classification"},{"motion",frame.motion.source.json()}};
    }
    request.attackerStats=makeDamageCombatant(*world.combatAttributes_);
    request.targetStats=makeDamageCombatant(*target.combatAttributes,policy);request.attack=attack;request.skill=sourceModifiers(frame);
    if(frame.sourceGrabDirectHit)request.skill.sources.push_back({
        {"policy","40jp-fighter-held-target-frame-callback-v1"},{"classification","40jp-native-structure-with-current1031-resources"},
        {"basis","CNFighter native grab strike targets its accepted held object directly; no ANI type15 volume is invented"},
        {"source_frame",frame.sourceFrame},{"motion",frame.motion.source.json()},
        {"owner_action",frame.sourceGrabOwner},{"target",target.handle.json()},
        {"descriptor",world.experimentalRuntime_->plan().sourceSkillActions.at(*frame.skill).evidence}});
    if(frame.skill)if(const auto *binding=world.experimentalRuntime_->configuration().binding(*frame.skill))
        if(binding->unknown.contains("user_requested_temporary_template"))
            request.skill.sources.push_back(binding->unknown.at("user_requested_temporary_template"));
    const auto typePolicy=world.experimentalRuntime_->configuration().weaponTypePolicy();
    if(typePolicy!="blocked")request.weaponType=typePolicy=="magical"?DamageAttackType::Magical:DamageAttackType::Physical;
    request.skill.sources.push_back({{"policy","inferred-experimental-weapon-type-choice-v1"},{"classification","inferred"},
        {"selection",typePolicy},{"basis","Explicit configurable experimental selector for unresolved source ATK [weapon] dispatch"},
        {"unverified_conditions","Native qualified-weapon damage-type consumer remains unresolved"},
        {"impact","Only ATK [weapon] dispatch uses this physical/magical choice; normal CHR/EQU attack inputs and explicit ATK types are preserved"}});
    auto acceptedEvent=world.prepareMonsterAcceptedHit(target,"experimental_source_contact");
    if(!acceptedEvent.ready) {
        record({{"code","experimental_accepted_hit_queue_blocked"},{"reason",acceptedEvent.error},{"target",target.id}});
        return false;
    }
    std::vector<Effect> preparedHitEffects;
    auto preparedEffectIds=world.effectIds_;
    if(!frame.contactEffects.empty()) {
        try {
            if(!intersection)throw std::invalid_argument("Hit effect cue has no accepted overlap region");
            for(const auto &cue:frame.contactEffects) {
                if(cue.trigger!=SourceSkillVisualTrigger::AcceptedHit)continue;
                const auto clip=world.assets_.animation(cue.source.memberPath);
                if(clip->frames.empty()||clip->duration<=0)throw std::invalid_argument("Empty accepted-hit effect ANI");
                for(const auto &sourceFrame:clip->frames)
                    if(!sourceFrame.image.empty())world.assets_.pixels(sourceFrame.image,sourceFrame.imageFrame);
                Effect effect;const auto effectId=preparedEffectIds.next();
                if(effectId==0||effectId>uint64_t(INT32_MAX))throw std::overflow_error("Accepted-hit effect identity exhausted");
                effect.id=int(effectId);
                effect.skill=frame.skill?frame.skill->skillId:0;effect.animation=cue.source.memberPath;
                effect.x=effect.px=intersection->x+intersection->w*.5;
                effect.y=effect.py=intersection->y+intersection->h*.5;
                effect.z=intersection->z+intersection->d*.5;effect.pz=effect.z;
                effect.dir=origin.dir;effect.born=world.nowMs();effect.expires=effect.born+clip->duration;
                effect.imageScale=cue.scaleX;effect.loop=false;effect.layer=cue.layer;
                effect.phase="source_skill_accepted_hit";effect.resourceSource=cue.source.memberPath;
                effect.sourceTreePolicy.clear();
                preparedHitEffects.push_back(std::move(effect));
            }
            if(!preparedHitEffects.empty())world.effects.reserve(world.effects.size()+preparedHitEffects.size());
        } catch(const std::exception &error) {
            preparedHitEffects.clear();
            record({{"code","source_skill_hit_visual_unavailable"},{"skill",frame.skill?frame.skill->json():Json()},
                {"motion",frame.motion.source.json()},{"error",error.what()},{"damage_policy","visual failure does not reject a qualified contact"}});
        }
    }
    std::optional<SkillStatusApplication> skillStatus;
    if(world.identity().jobId==5) {
        if(world.femaleGunnerWorld_)world.femaleGunnerWorld_->applyAttack(request,frame.skill,frame.motion.tag,frame.sourceFamily);
        if(frame.femaleGunnerCommand)skillStatus=readFemaleGunnerSkillAttackStatuses(*frame.femaleGunnerCommand,world.experimentalRuntime_->plan());
    }
    const auto result=world.resolveActorContact(request,makeMonsterStatusResistances(*target.combatAttributes),skillStatus?&*skillStatus:nullptr);
    world.lastDamageTrace_=result.snapshot();
    if(!result.usable()) {record({{"code","experimental_damage_blocked"},{"result",result.snapshot()}});return false;}
    targets.insert(target.handle);
    if(result.missed){world.events.push_back({world.tick,"miss",attack.source.path,0,target.id});return true;}
    const int value=*result.hpDamage,acceptedHpLoss=std::min(target.hp,value);target.hp=std::max(0,target.hp-value);
    target.lastImpact=monsterDeathImpulse(target.x-origin.x,target.y-origin.y,origin.dir,
        std::hypot(world.player.vx,world.player.vy),value,target.maxHp,response.push,response.lift);
    target.hitFlashUntil=world.nowMs()+80;
    if(!target.hp)world.beginDeath(target);
    if(!target.dead&&frame.skill&&world.femaleGunnerWorld_&&
        (frame.sourceFamily=="grab_ground_shoot"||frame.sourceFamily=="grab_aerial_gatling"))world.femaleGunnerWorld_->capture(target,*frame.skill);
    world.requestHitStop(target,response.hitPause,response.source);
    if(!frame.sourceEntity)world.requestHitStop(world.player,response.hitPause,response.source);
    if(!target.dead&&!response.noReaction) {
        world.applyResponse(target,response,origin.dir);
        world.applyMonsterHurtMotion(target,response);
        world.interruptStatusTarget(target);
    }
    world.events.push_back({world.tick,"hit",frame.sourceEntity?"source_nut_passive_object":frame.skill?"experimental_source_skill":"experimental_source_attack",0,target.id,value});
    world.publishMonsterHitFeedback(target,response,origin.dir,value,false,intersection,result.critical);
    if(!preparedHitEffects.empty()) {
        static_assert(std::is_nothrow_move_constructible<Effect>::value,"Prepared source hit effects must publish without allocation failure");
        for(auto &effect:preparedHitEffects)world.effects.push_back(std::move(effect));
        world.effectIds_=std::move(preparedEffectIds);
    }
    world.publishMonsterAcceptedHit(std::move(acceptedEvent),acceptedHpLoss);
    return true;
}
bool ExperimentalWorldAdapter::contactMoving(Actor &target,const ExperimentalAttackFrame &frame,
    const AttackDamageDefinition &attack,ExperimentalCharacterRuntime &runtime,const CombatBox &intersection) {
    auto &world=world_;
    if(!frame.skill||!runtime.sourceSkillEntityLive(frame.sourceEntityInstance))return false;
    try {
        const auto &descriptor=runtime.plan().sourceSkillActions.at(*frame.skill);
        const auto &program=*descriptor.movingImpact;
        const bool flight=runtime.sourceEntityIsMovingFlight(frame.sourceEntityInstance);
        std::optional<ExperimentalCharacterRuntime> impactRuntime;
        auto impactIds=world.ids_.attacks,impactEffectIds=world.effectIds_;
        std::vector<Effect> impactEffects;
        std::map<uint64_t,SourceContactLedger> impactLedgers;
        if(flight) {
        // Prepare the complete impact, including images and allocator failures,
        // before resolving even the original flight's damage/status randomness.
        std::set<std::string> visited;
        const auto validate=[&](const auto &self,const std::string &path,size_t depth)->void {
            if(depth>12||visited.size()>=4096)throw std::length_error("Moving impact visual closure budget");
            if(!visited.insert(path).second)return;
            const auto ani=world.assets_.animation(path);if(ani->frames.empty())throw std::invalid_argument("Empty moving impact ANI");
            for(const auto &f:ani->frames)if(!f.image.empty())world.assets_.pixels(f.image,f.imageFrame);
            const auto events=animationEffectEvents(world.pvf_,world.assets_,path,program.visualPolicy);
            if(!events.diagnostics.empty())throw std::invalid_argument("Moving impact ALS closure blocked: "+events.diagnostics.dump());
            for(const auto &event:events.events)if(event.kind!=EffectEventKind::Remove)self(self,event.animation,depth+1);
        };
        validate(validate,program.impactAnimation.memberPath,0);readAttackResponse(program.impactAttackDefinition.source);
        impactRuntime=runtime;const auto spawn=impactRuntime->acceptSourceMovingHit(frame.sourceEntityInstance,uint64_t(world.tick));
        SourceContactLedger impactLedger;impactLedger.attackId=impactIds.next();
        const auto effectId=impactEffectIds.next();if(effectId>INT32_MAX)throw std::overflow_error("Moving impact effect identity exhausted");
        impactLedger.effectId=int(effectId);impactLedger.targets.insert(target.handle);
        Effect impact;impact.id=int(effectId);impact.skill=spawn.key.skillId;impact.animation=program.impactAnimation.memberPath;
        impact.sourceObject=program.impactObject.memberPath;impact.sourceTreePolicy=program.visualPolicy;
        impact.x=impact.px=spawn.position[0];impact.y=impact.py=spawn.position[1];impact.z=spawn.position[2];impact.pz=impact.z;impact.dir=spawn.direction;
        impact.born=world.nowMs();if(spawn.lifetimeMs>INT64_MAX-impact.born)throw std::overflow_error("Moving impact lifetime overflow");
        impact.expires=impact.born+spawn.lifetimeMs;impact.damageEnabled=false;impact.loop=false;
        impact.imageScale=spawn.imageScale;impact.autoLayerScale=spawn.autoLayerScale;
        impact.phase="source-nut:watercannon-impact";impact.resourceSource=program.impactCallback.memberPath;
        impact.projectileSource={{"descriptor",descriptor.snapshot()},{"entity",spawn.entity},{"action_sequence",spawn.actionSequence},
            {"operands",spawn.evidence},{"excluded_target",target.handle.json()},
            {"contact_policy","inferred-first-accepted-nonmiss-contact-spawn-impact-v1"}};
        if(world.effects.size()>=2048||sourceContactLedgers_.size()>=128)throw std::length_error("Moving impact instance budget exhausted");
        impactEffects=world.effects;impactLedgers=sourceContactLedgers_;
        const auto old=impactLedgers.find(frame.sourceEntityInstance);if(old==impactLedgers.end())throw std::invalid_argument("Stale moving contact ledger");
        std::set<int> retired{old->second.effectId};bool more=true;
        while(more){more=false;for(const auto &fx:impactEffects)if(retired.count(fx.alsParentId))more|=retired.insert(fx.id).second;}
        for(auto &fx:impactEffects)if(retired.count(fx.id))fx.expires=std::min(fx.expires,world.nowMs());
        impactLedgers.erase(old);if(!impactLedgers.emplace(spawn.entity,std::move(impactLedger)).second)throw std::invalid_argument("Replayed moving impact identity");
        impactEffects.push_back(std::move(impact));
        }

        // No live service, callback or actor storage is moved into this world.
        // The ordinary contact path consumes private actors and prepared hit
        // windows/queues, preserving its existing source ATK/response behavior.
        World candidate(world.pvf_,world.assets_,world.rules_);
        candidate.identity_=world.identity_;candidate.player=world.player;candidate.monsters=world.monsters;
        candidate.events=world.events;candidate.clock_=world.clock_;candidate.tick=world.tick;
        candidate.entities_=world.entities_;candidate.ids_=world.ids_;candidate.random_=world.random_;candidate.statuses_=world.statuses_;
        candidate.effectIds_=impactEffectIds;candidate.pendingEffects_=world.pendingEffects_;
        candidate.combatAttributes_=world.combatAttributes_;candidate.lastDamageTrace_=world.lastDamageTrace_;
        candidate.combat=world.combat;candidate.mapWidth=world.mapWidth;candidate.walkRects=world.walkRects;candidate.blockedRects=world.blockedRects;
        candidate.mapExplorationActive_=world.mapExplorationActive_;candidate.mapExplorationGeometryAvailable_=world.mapExplorationGeometryAvailable_;
        candidate.explorationConsumers_=world.explorationConsumers_;
        candidate.monsterEventAiBindings_=world.monsterEventAiBindings_;candidate.monsterEventAiPending_=world.monsterEventAiPending_;
        candidate.monsterDamageWindows_=world.monsterDamageWindows_;
        candidate.experimentalRuntime_=std::make_unique<ExperimentalCharacterRuntime>(runtime);
        ExperimentalWorldAdapter adapter(candidate);adapter.sourceContactLedgers_=sourceContactLedgers_;
        auto *privateTarget=const_cast<Actor *>(static_cast<const World &>(candidate).resolveActor(target.handle));
        if(!privateTarget||privateTarget==&candidate.player)throw std::invalid_argument("Moving contact target handle changed");
        if(!adapter.contact(*privateTarget,frame,attack,&intersection))throw std::invalid_argument("Moving contact private damage/accepted-event preparation rejected");
        const bool missed=candidate.lastDamageTrace_.value("missed",false);
        // All allocations, response animation preparation and callbacks above
        // completed privately. Publishing one target keeps the outer monster
        // vector/reference stable; earlier successful contacts remain committed.
        static_assert(std::is_nothrow_swappable<Actor>::value&&std::is_nothrow_swappable<StatusHost>::value&&
            std::is_nothrow_swappable<RandomStreams>::value&&std::is_nothrow_move_assignable<ExperimentalCharacterRuntime>::value,
            "Moving contact publication must not throw");
        using std::swap;swap(target,*privateTarget);swap(world.player,candidate.player);world.events.swap(candidate.events);
        swap(world.statuses_,candidate.statuses_);swap(world.random_,candidate.random_);world.lastDamageTrace_.swap(candidate.lastDamageTrace_);
        world.monsterEventAiPending_.swap(candidate.monsterEventAiPending_);world.monsterDamageWindows_.swap(candidate.monsterDamageWindows_);
        swap(world.ids_.events,candidate.ids_.events);
        if(!missed)world.pendingEffects_.swap(candidate.pendingEffects_);
        if(missed||!flight)sourceContactLedgers_.swap(adapter.sourceContactLedgers_);
        else {
            runtime=std::move(*impactRuntime);world.effects.swap(impactEffects);sourceContactLedgers_.swap(impactLedgers);
            world.ids_.attacks=std::move(impactIds);world.effectIds_=std::move(candidate.effectIds_);
        }
        if(!missed&&!flight)world.effectIds_=std::move(candidate.effectIds_);
        return true;
    } catch(const std::exception &error) {
        record({{"code","source_moving_contact_rejected"},{"message",error.what()},
            {"policy","private-current-contact-impact-commit-v1"},{"target",target.handle.json()},{"no_current_hp_rng_or_entity_publication",true}});
        return false;
    }
}
void ExperimentalWorldAdapter::advance(ExperimentalCharacterRuntime &runtime,uint64_t fixedTick) {
    // Restore the immutable learned view before ANY female passive/stat
    // consumer. A stale raw binding cannot gain attributes before skillGate.
    world_.enforceLearnedSkillProjection();
    auto &world=world_;auto &player=world.player;
    std::optional<double> heldTargetScale;
    if(sourceCapture_) {
        if(auto *held=const_cast<Actor *>(static_cast<const World &>(world).resolveActor(sourceCapture_->target))) {
            updateCapturedPose(*held);
            if(!held->monsterPath.empty())try {
                const auto key=std::make_pair(normalize(held->monsterPath),held->boss);
                auto source=world.monsterAttributeSources_.find(key);
                if(source==world.monsterAttributeSources_.end())
                    source=world.monsterAttributeSources_.emplace(key,readMonsterAttributeSource(world.pvf_,key.first,key.second)).first;
                const double width=source->second.monster.number("[width]",-1);
                if(width>0&&std::isfinite(width)) {
                    heldTargetScale=heldTargetWidthVisualScale(width);
                } else {
                    const bool reported=std::any_of(world.experimentalDiagnostics_.begin(),world.experimentalDiagnostics_.end(),[&](const Json &row) {
                        return row.value("code","")=="fighter40jp_held_target_width_unavailable"&&
                            row.value("target",Json())==held->handle.json();
                    });
                    if(!reported)record({{"code","fighter40jp_held_target_width_unavailable"},{"target",held->handle.json()},
                        {"mob",key.first},{"field","[width]"},{"fallback_scale",1.0},
                        {"classification","inferred_current1031_proxy_absent"}});
                }
            } catch(const std::exception &error) {
                record({{"code","fighter40jp_held_target_width_read_failed"},{"target",held->handle.json()},
                    {"mob",held->monsterPath},{"message",error.what()},{"fallback_scale",1.0}});
            }
        } else clearSourceGrab();
    }
    // Scene reset clears visual instances and the runtime's owned entities.
    // Their corresponding contact ledger must not survive or grow unbounded.
    for(auto i=sourceContactLedgers_.begin();i!=sourceContactLedgers_.end();) {
        const auto effect=std::find_if(world.effects.begin(),world.effects.end(),[&](const Effect &fx){return fx.id==i->second.effectId;});
        if(player.dead||player.life!=ActorLife::Alive||!runtime.sourceSkillEntityLive(i->first)||effect==world.effects.end()) {
            if(effect!=world.effects.end())effect->expires=std::min(effect->expires,world.nowMs());
            i=sourceContactLedgers_.erase(i);
        } else ++i;
    }
    ExperimentalActorState state;state.x=player.x;state.y=player.y;state.z=player.z;state.vx=player.vx;state.vy=player.vy;state.vz=player.vz;
    state.direction=player.dir;state.mp=player.mp;state.alive=!player.dead&&player.life==ActorLife::Alive;
    state.blocked=world.pickupActionActive()||player.recovery!=0||world.nowMs()<player.stunUntil||world.statusStunned(player.handle);state.hitStopped=player.hitStopped;
    state.noCooldown=world.freeCd;
    state.fighter40JpTestFreedom=world.debugOverrides_.enabled&&world.experimentalSkillPreviewEnabled()&&world.identity().jobId==1;
    // Only real equipped attributes can supply a weapon subtype. The separate
    // appearance fallback may carry a source default weapon for display and
    // must never grant that inventory/weapon modifier to a naked experiment.
    if(world.combatAttributes_)for(const auto &equipped:world.combatAttributes_->equipmentSources)if(normalize(equipped.equippedSlot)=="[weapon]") {
        const auto values=selectedValues(equipped.source,"[sub type]");
        if(values.size()==1&&values[0].is_number_integer()&&values[0].get<int64_t>()>=0&&values[0].get<int64_t>()<=INT32_MAX)
            state.weaponSubtype=values[0].get<int>();
    }
    if(world.speedAttributes_){state.movePerMille=world.speedAttributes_->movePerMille;state.attackPerMille=world.speedAttributes_->attackPerMille;
        state.dashXRatio=world.speedAttributes_->dashXRatio;state.dashYRatio=world.speedAttributes_->dashYRatio;}
    else if(world.baseAttributes_){state.movePerMille=world.baseAttributes_->value(ChrAttribute::MoveSpeed);state.attackPerMille=world.baseAttributes_->value(ChrAttribute::AttackSpeed);}
    if ((world.identity().jobId == 5||world.identity().jobId == 2) && !world.femaleGunnerWorld_)
        world.femaleGunnerWorld_ = std::make_unique<FemaleGunnerWorld>(world);
    if(world.identity().jobId==2&&runtime.gunnerTargetAimEnabled()) {
        double best=std::numeric_limits<double>::infinity();
        double bodyCenter=player.z;
        if(const auto *waiting=runtime.plan().motion("[waiting motion]"))for(const auto &box:runtime.plan().animations.at(waiting->source.memberPath)->frames.front().boxes)
            if(box.type==14)bodyCenter=std::max(bodyCenter,player.z+box.z+box.d*.5);
        for(const auto &target:world.monsters) {
            if(target.dead||target.life!=ActorLife::Alive||!world.explorationAllowsIncoming(target))continue;
            const double forward=(target.x-player.x)*player.dir;if(forward<=0||forward>=best)continue;
            try {
            const auto motion=world.monsterMotion(target,target.animation);if(!motion->valid())continue;
            const auto age=monsterMotionTime(*motion,world.nowMs()-target.animStart,target.animation=="stay"||target.animation=="move");
            const auto frame=target.animationClock&&target.animationClockSource==motion->base->path?target.animationClock->frame:motion->base->frameAt(int64_t(age),false);
            for(const auto &box:motion->base->frames.at(frame).boxes)if(box.type==14&&box.w>0&&box.h>0&&box.d>0) {
                const auto volume=combatBox(box,target.x,target.y,target.z,target.dir);
                if(player.y<volume.y||player.y>volume.y+volume.h)continue;
                best=forward;
                state.gunnerAimTarget={{"handle",target.handle.json()},{"center",{volume.x+volume.w*.5,player.y,volume.z+volume.d*.5}},
                    {"prefer_down",volume.z+volume.d*.5<bodyCenter},{"motion",makeSourceRef(world.pvf_,motion->base->path).json()},
                    {"frame",frame},{"source_box",{box.x,box.y,box.z,box.w,box.h,box.d}},
                    {"policy","inferred-nearest-forward-source-hurtbox-aim-v1"},{"native_BF9060_equality",false}};
            }
            } catch(const std::exception &error) {
                record({{"code","gunner_source_aim_target_blocked"},{"target",target.handle.json()},
                    {"source",target.monsterPath},{"message",error.what()},{"fallback","source-centerline; no target geometry substitution"}});
            }
        }
    }
    if(world.femaleGunnerWorld_&&world.identity().jobId==5)world.femaleGunnerWorld_->applyActor(state);
    // Runtime owns only value configuration/state and shared immutable plan
    // references; it has no self pointers or stored callbacks. Keep MP/CD,
    // action sequence, animation age and sounds private until every selected
    // CHR/EQU/LAY sample has passed source preflight.
    auto candidate=runtime;
    const auto out=candidate.advance(fixedTick,state,[&](double x,double y){return world.canWalk(x,y);},
        [&](const ExperimentalSkillActionRequest &request){
            // Manual all-branch release is an explicit isolated mode. Normal
            // and test learning always require their actual effective ledger.
            if(!world.experimentalSkillPreviewEnabled()) {
                const auto policy=world.runtimeSkillPolicy(request.key);
                if(!policy.implemented||policy.kind!=SkillSourceKind::Active)
                    throw std::invalid_argument("Normal skill has no reviewed active consumer");
                const auto *binding=runtime.configuration().binding(request.key);
                const auto gate=world.skillUseEligibility(request.key);
                if(!world.hasLearningLedger()||!gate.allowed()||!binding||binding->level!=gate.learnedLevel)
                    throw std::invalid_argument("Normal learned skill gate: "+gate.error);
            }
            return world.prepareSquirrelAction(request);
        });
    std::unique_ptr<FemaleGunnerWorld> preparedFemaleGunner;
    struct PreparedAttack { CharacterAttackMotion motion; std::vector<Box> boxes; };
    std::vector<PreparedAttack> preparedAttacks;
    auto preparedSourceLedgers=sourceContactLedgers_;
    std::optional<std::vector<Effect>> preparedSourceEffects;
    auto preparedSourceEffectIds=world.effectIds_,preparedSourceAttackIds=world.ids_.attacks;
    bool sourceIdsAllocated=false;
    std::optional<RandomStreams> preparedAudioRandom;
    std::vector<std::string> preparedAudioEvents;
    Json preparedAudioReceipts=Json::array();
    try {
        preparedAttacks.reserve(out.attacks.size());
        for(const auto &frame:out.attacks) {
            if(frame.sourceEntity) {
                preparedAttacks.push_back({{},frame.boxes});
                continue;
            }
            auto motion=readCharacterAttackMotion(world.assets_,world.characterAppearance(),frame.motion.source.memberPath);
            auto boxes=frame.animationClock?motion.boxesAt(*frame.animationClock,frame.animationControllerDelays.get()):motion.boxesAt(frame.sourceFrame);
            preparedAttacks.push_back({std::move(motion),std::move(boxes)});
            if(frame.femaleGunnerCommand) {
                const auto status=readFemaleGunnerSkillAttackStatuses(*frame.femaleGunnerCommand,runtime.plan());
                if(!status.usable())throw std::invalid_argument("Female Gunner body status source preflight failed: "+status.snapshot().dump());
            }
        }
        // Validate each required allocation on a private watermark. The live
        // source remains untouched until the accepted samples publish below.
        auto candidateAttackIds=world.ids_.attacks;auto previousAction=action_;auto previousPulse=contactPulse_;
        size_t requiredBodyAttacks=0;
        for(const auto &frame:out.attacks)if(!frame.sourceEntity&&(!frame.suppressBodyDamage||frame.sourceGrabDirectHit)&&(frame.actionSequence!=previousAction || frame.pulseId!=previousPulse)) {
            candidateAttackIds.next();previousAction=frame.actionSequence;previousPulse=frame.pulseId;++requiredBodyAttacks;
        }
        std::set<std::string> validatedSourceVisuals,sourceVisualSounds;
        const auto preflightSourceVisual=[&](const auto &self,const std::string &path,size_t depth,const std::string &treePolicy)->void {
            if(depth>12||validatedSourceVisuals.size()>=4096)throw std::length_error("Source NUT visual closure budget exhausted");
            if(!validatedSourceVisuals.insert(treePolicy+":"+path).second)return;
            const auto animation=world.assets_.animation(path);
            for(const auto &frame:animation->frames) {
                if(!frame.image.empty())world.assets_.pixels(frame.image,frame.imageFrame);
                if(frame.properties.contains("16")&&frame.properties.at("16").is_string())sourceVisualSounds.insert(frame.properties.at("16").get<std::string>());
            }
            const auto events=animationEffectEvents(world.pvf_,world.assets_,path,treePolicy);
            if(!treePolicy.empty()&&!events.diagnostics.empty())throw std::invalid_argument("Reviewed source-tree ALS preflight failed: "+events.diagnostics.dump());
            for(const auto &event:events.events)if(event.kind!=EffectEventKind::Remove)self(self,event.animation,depth+1,treePolicy);
        };
        for(const auto &command:out.sourceSkillVisuals) {
            const auto &descriptor=runtime.plan().sourceSkillActions.at(command.key);
            if(command.kind==ExperimentalSourceVisual::Kind::Retire)continue;
            if(command.kind==ExperimentalSourceVisual::Kind::Update) {
                const auto found=preparedSourceLedgers.find(command.entity);
                if(found==preparedSourceLedgers.end())throw std::invalid_argument("Source position update has no live entity ledger");
                if(!preparedSourceEffects)preparedSourceEffects=world.effects;
                const auto fx=std::find_if(preparedSourceEffects->begin(),preparedSourceEffects->end(),[&](const auto &e){return e.id==found->second.effectId;});
                if(fx==preparedSourceEffects->end())throw std::invalid_argument("Source position update has no live visual");
                fx->x=command.position[0];fx->y=command.position[1];fx->z=command.position[2];fx->dir=command.direction;continue;
            }
            if(descriptor.native40Jp&&command.kind==ExperimentalSourceVisual::Kind::Preflight) {
                std::set<std::string> responses;
                for(const auto &stage:descriptor.nativeStages) {
                    for(const auto &layer:stage.layers)preflightSourceVisual(preflightSourceVisual,layer.source.memberPath,0,{});
                    if(stage.attackSlot<0||stage.attack.memberPath.empty()||!responses.insert(stage.attack.memberPath).second)continue;
                    const auto definition=runtime.plan().attackDefinitions.find(stage.attack.memberPath);
                    if(definition==runtime.plan().attackDefinitions.end())
                        throw std::invalid_argument("Native source stage ATK was not loaded: "+stage.attack.memberPath);
                    // TryGrab has a real non-damage ATK. Parse its response
                    // without treating .usable() as a damage requirement.
                    readAttackResponse(definition->second.source);
                }
            }
            if(descriptor.kind==SourceSkillActionKind::BodyAttack&&!descriptor.nativeProjectile) {
                if(command.kind!=ExperimentalSourceVisual::Kind::Preflight)throw std::invalid_argument("Source body action cannot spawn a passive entity");
                if(descriptor.requiresEquippedAttackVolume) {
                    const auto composed=readCharacterAttackMotion(world.assets_,world.characterAppearance(),descriptor.motion.memberPath);
                    bool hasVolume=false;int firstAttackFrame=-1;
                    for(size_t frame=0;frame<composed.body->frames.size();++frame)
                        for(const auto &box:composed.boxesAt(frame))if(box.w>0&&box.h>0&&box.d>0) {
                            hasVolume=true;if(firstAttackFrame<0)firstAttackFrame=int(frame);
                        }
                    if(descriptor.bodyLayerBirthFrame>=0&&firstAttackFrame!=descriptor.bodyLayerBirthFrame)
                        throw std::invalid_argument("Source timed body layer requires the reviewed actual equipped first attack frame");
                    if(descriptor.bodySidestep&&firstAttackFrame!=descriptor.bodySidestep->returnFrame)
                        throw std::invalid_argument("Source sidestep return requires the reviewed actual equipped attack boundary");
                    if(!hasVolume)throw std::invalid_argument("Source body skill requires a real equipped attack volume before cost publication");
                }
                // Exact reviewed consumer only: native none-effect kind5 is
                // retained in each layer receipt; generic parser stays blocked.
                for(const auto &layer:descriptor.bodyLayers)preflightSourceVisual(preflightSourceVisual,layer.source.memberPath,0,{});
                if(!descriptor.native40Jp&&!descriptor.attackDefinition.source.path.empty())readAttackResponse(descriptor.attackDefinition.source);
                if(command.key==SkillKey{4,1}) {
                    const auto raw=world.assets_.staticBytes("audio.xml");
                    if(sha256(raw)!="ddf99ac1924c189fdb0d8ecb429501e0530e47c85417d9bc474d0f6d5306095a")
                        throw std::invalid_argument("Reviewed Priest Upper audio catalog changed");
                    AudioCatalog audio(raw,"audio.xml");const auto declarations=audio.find(descriptor.castSound);
                    if(descriptor.castSound!="PR_ANTIAIR"||declarations.size()!=1||declarations.front()->kind!=AudioKind::Effect||
                       normalize(declarations.front()->file)!="sounds/char/priest/pr_antiair.ogg")
                        throw std::invalid_argument("Priest Upper exact source cast sound declaration unavailable");
                    const auto path=normalize(declarations.front()->file);
                    const auto bytes=world.assets_.has(path)?world.assets_.blob(path):world.assets_.staticBytes(std::filesystem::u8path(path));
                    if(bytes.size()<4||std::memcmp(bytes.data(),"OggS",4))throw std::invalid_argument("Priest Upper source OGG unavailable");
                }
                if(command.key==SkillKey{1,5}) {
                    // Both concrete assets are prepared before the cast fee is
                    // published. This association/timing is explicitly inferred;
                    // these deterministic EFFECTs do not consume Audio RNG.
                    if(descriptor.castSound!="FT_UPPER_READY"||descriptor.attackSound!="FT_UPPER_SWING")
                        throw std::invalid_argument("Reviewed female Upper audio association changed");
                    const auto raw=world.assets_.staticBytes("audio.xml");
                    if(sha256(raw)!="ddf99ac1924c189fdb0d8ecb429501e0530e47c85417d9bc474d0f6d5306095a")
                        throw std::invalid_argument("Reviewed female Upper audio catalog version changed");
                    AudioCatalog catalog(raw,"audio.xml");Json resources=Json::array();
                    for(const auto &cue:std::array<std::pair<std::string,std::string>,2>{{
                        {descriptor.castSound,"sounds/char/fighter/ft_upper1.ogg"},
                        {descriptor.attackSound,"sounds/char/fighter/ft_upper2.ogg"}}}) {
                        const auto declarations=catalog.find(cue.first);
                        if(declarations.size()!=1||declarations.front()->kind!=AudioKind::Effect||
                           normalize(declarations.front()->file)!=cue.second)
                            throw std::invalid_argument("Female Upper audio needs its exact EFFECT declaration: "+cue.first);
                        const auto &declaration=*declarations.front();
                        const auto bytes=world.assets_.has(cue.second)?world.assets_.blob(cue.second):
                            world.assets_.staticBytes(std::filesystem::u8path(cue.second));
                        if(bytes.size()<4||std::memcmp(bytes.data(),"OggS",4)!=0)
                            throw std::invalid_argument("Female Upper audio source container unavailable: "+cue.second);
                        resources.push_back({{"id",cue.first},{"file",cue.second},{"sha256",sha256(bytes)},
                            {"declaration_offset",declaration.offset},{"declaration_end",declaration.endOffset}});
                    }
                    preparedAudioReceipts.push_back({{"policy","inferred-current1031-fighter-upper-two-phase-audio-v1"},
                        {"classification","inferred_beta"},{"skill",command.key.json()},{"action_sequence",command.actionSequence},
                        {"audio_catalog_sha256",sha256(raw)},{"resources",resources},{"random_consumed",false},
                        {"timing","READY accepted cast; SWING first actual body type15 frame; each once/action; canceled action cannot emit a later swing"},
                        {"native_caller_and_phase_verified",false},{"device_decode_and_user_hearing_verified",false}});
                }
                if(command.key==SkillKey{2,4}&&candidate.configuration().sourceActionAudioPolicy()=="inferred-current1031-knee-cast-audio-v1") {
                    // Catalog locates assets; association and cast timing are
                    // explicit comparison, not a recovered native caller.
                    const auto raw=world.assets_.staticBytes("audio.xml");
                    if(sha256(raw)!="ddf99ac1924c189fdb0d8ecb429501e0530e47c85417d9bc474d0f6d5306095a")
                        throw std::invalid_argument("Reviewed Knee audio catalog version changed");
                    AudioCatalog catalog(raw,"audio.xml");
                    const auto unique=[&](const std::string &id,AudioKind kind)->const AudioDeclaration & {
                        const auto declarations=catalog.find(id);
                        if(declarations.size()!=1||declarations.front()->kind!=kind)
                            throw std::invalid_argument("Knee audio needs one exact declaration: "+id);
                        return *declarations.front();
                    };
                    const auto &group=unique("R_GN_JACKSPIKE",AudioKind::Random);
                    if(group.items.size()!=2||group.items[0].id!="GN_JACKSPIKE_01"||group.items[1].id!="GN_JACKSPIKE_02"||
                       group.items[0].weight!=50||group.items[1].weight!=50)
                        throw std::invalid_argument("Reviewed Knee voice weights/items changed");
                    Json resources=Json::array();
                    for(const auto &id:{group.items[0].id,group.items[1].id,std::string("JACKSPIKE_SWING")}) {
                        const auto &declaration=unique(id,AudioKind::Effect);const auto path=normalize(declaration.file);
                        const auto bytes=world.assets_.has(path)?world.assets_.blob(path):world.assets_.staticBytes(std::filesystem::u8path(path));
                        if(bytes.size()<4||std::memcmp(bytes.data(),"OggS",4)!=0)
                            throw std::invalid_argument("Knee audio source container unavailable: "+path);
                        resources.push_back({{"id",id},{"file",path},{"sha256",sha256(bytes)},
                            {"declaration_offset",declaration.offset},{"declaration_end",declaration.endOffset}});
                    }
                    if(!preparedAudioRandom)preparedAudioRandom=world.random_;
                    // Single-player cast choice must survive entity retirement
                    // during save/character restore. Handle IDs deliberately
                    // change there; stable run-local Audio instance0 does not.
                    auto &random=preparedAudioRandom->stream(RandomDomain::Audio,0);
                    const auto before=random.snapshot();const auto roll=random.bounded(100);const auto voice=group.items[roll<50?0:1].id;
                    preparedAudioEvents.push_back(voice);preparedAudioEvents.push_back("JACKSPIKE_SWING");
                    preparedAudioReceipts.push_back({{"policy",candidate.configuration().sourceActionAudioPolicy()},
                        {"classification","inferred_beta"},{"skill",command.key.json()},{"action_sequence",command.actionSequence},
                        {"audio_catalog_sha256",sha256(raw)},{"group_offset",group.offset},{"resources",resources},
                        {"audio_stream_instance",0},{"audio_stream_policy","stable-single-player-run-audio-v1"},
                        {"random_before",before},{"random_after",random.snapshot()},{"roll_0_99",roll},{"resolved_voice",voice},
                        {"timing","once at accepted cast including empty cast; native phase unverified"},
                        {"device_decode_and_user_hearing_verified",false}});
                }
                continue;
            }
            const std::string treePolicy=descriptor.movingImpact?descriptor.movingImpact->visualPolicy:"";
            preflightSourceVisual(preflightSourceVisual,descriptor.animation.memberPath,0,treePolicy);
            if(descriptor.movingImpact) {
                for(const auto &layer:descriptor.bodyLayers)preflightSourceVisual(preflightSourceVisual,layer.source.memberPath,0,{});
                preflightSourceVisual(preflightSourceVisual,descriptor.movingImpact->impactAnimation.memberPath,0,treePolicy);
                readAttackResponse(descriptor.movingImpact->impactAttackDefinition.source);
                const auto raw=world.assets_.staticBytes("audio.xml");
                if(sha256(raw)!="ddf99ac1924c189fdb0d8ecb429501e0530e47c85417d9bc474d0f6d5306095a")throw std::invalid_argument("Reviewed moving sound catalog changed");
                AudioCatalog audio(raw,"audio.xml");
                sourceVisualSounds.insert(descriptor.castSound);sourceVisualSounds.insert(readAttackResponse(descriptor.attackDefinition.source).sound);
                for(const auto &frame:world.assets_.animation(descriptor.motion.memberPath)->frames)
                    if(frame.properties.contains("16")&&frame.properties.at("16").is_string())sourceVisualSounds.insert(frame.properties.at("16").get<std::string>());
                for(const auto &id:sourceVisualSounds) {
                    const auto declarations=audio.find(id);
                    if(declarations.size()!=1||declarations[0]->kind!=AudioKind::Effect)throw std::invalid_argument("Moving source sound declaration unavailable: "+id);
                    const auto path=normalize(declarations[0]->file);
                    const auto bytes=world.assets_.has(path)?world.assets_.blob(path):world.assets_.staticBytes(std::filesystem::u8path(path));
                    if(bytes.size()<4||std::memcmp(bytes.data(),"OggS",4))throw std::invalid_argument("Moving source sound resource unavailable: "+path);
                }
            }
            readAttackResponse(descriptor.attackDefinition.source);
            if(!preparedSourceEffects)preparedSourceEffects=world.effects;
            if(preparedSourceEffects->size()>=2048||preparedSourceLedgers.size()>=128)
                throw std::length_error("Source NUT PO/effect budget exhausted before skill publication");
            if(command.kind==ExperimentalSourceVisual::Kind::Preflight) {
                auto attacks=candidateAttackIds,effects=preparedSourceEffectIds;attacks.next();
                if(effects.next()>INT32_MAX)throw std::overflow_error("Source NUT visual ID budget exhausted");
                if(descriptor.movingImpact) {attacks.next();if(effects.next()>INT32_MAX)throw std::overflow_error("Source impact visual ID budget exhausted");}
                continue;
            }
            if(requiredBodyAttacks)throw std::invalid_argument("Source NUT spawn concurrent with a new body attack is outside this reviewed program contract");
            if(preparedSourceLedgers.count(command.entity))throw std::invalid_argument("Replayed source NUT PO spawn");
            Effect fx;const auto effectId=preparedSourceEffectIds.next();
            if(effectId>INT32_MAX)throw std::overflow_error("Source NUT visual ID exceeds int32");fx.id=int(effectId);
            fx.skill=command.key.skillId;fx.animation=descriptor.animation.memberPath;fx.sourceObject=descriptor.object.memberPath;
            fx.x=fx.px=command.position[0];fx.y=fx.py=command.position[1];fx.z=command.position[2];fx.pz=fx.z;fx.dir=command.direction;
            fx.born=world.nowMs();
            if(descriptor.objectAnimation->duration>INT64_MAX-fx.born)throw std::overflow_error("Source NUT PO lifetime overflow");
            const auto lifetime=command.lifetimeMs>0?command.lifetimeMs:descriptor.objectAnimation->duration;
            if(lifetime>INT64_MAX-fx.born)throw std::overflow_error("Source moving PO lifetime overflow");
            fx.expires=fx.born+lifetime;fx.damageEnabled=false;fx.loop=command.loop;
            fx.imageScale=command.imageScale;fx.autoLayerScale=command.autoLayerScale;fx.sourceTreePolicy=treePolicy;
            fx.phase="source-nut:passive-object";fx.resourceSource=descriptor.callback.memberPath;
            fx.projectileSource={{"descriptor",descriptor.snapshot()},{"entity",command.entity},{"action_sequence",command.actionSequence},{"operands",command.evidence}};
            SourceContactLedger ledger;ledger.attackId=preparedSourceAttackIds.next();ledger.effectId=fx.id;
            preparedSourceLedgers.emplace(command.entity,std::move(ledger));preparedSourceEffects->push_back(std::move(fx));sourceIdsAllocated=true;
        }
        const bool startsBasic=std::any_of(out.attacks.begin(),out.attacks.end(),[&](const ExperimentalAttackFrame &f){return !f.skill&&f.actionSequence!=action_;});
        const bool maleScheduled=world.identity().jobId==2&&std::any_of(out.attacks.begin(),out.attacks.end(),
            [](const auto &frame){return frame.gunnerScheduledShot;});
        if (world.femaleGunnerWorld_ && ((world.identity().jobId==5&&(!out.femaleGunnerCommands.empty()||startsBasic))||maleScheduled))
            preparedFemaleGunner=world.femaleGunnerWorld_->prepare(out.femaleGunnerCommands,out.actor,requiredBodyAttacks,out.attacks);
    } catch(const std::exception &error) {
        // Reject this action explicitly, while maintaining the fixed-tick
        // contract. The normal blocked transition discards pending action
        // requests but preserves unrelated held movement input. It charges no
        // MP/CD or source sounds. A prepared script may burn monotonic request/action
        // IDs; no attack identity or gameplay RNG is published on rejection.
        world.cancelSquirrelActions("source_motion_preflight_rejected");
        auto rejected=state;rejected.blocked=true;
        runtime.advance(fixedTick,rejected,[&](double x,double y){return world.canWalk(x,y);});
        clearSourceGrab();
        player.animationClock.reset();player.animationClockSource.clear();player.animationControllerDelays.reset();player.skillAnimationLayers.clear();
        Json sourcePrograms=Json::array();std::set<SkillKey> sourceKeys;
        for(const auto &command:out.sourceSkillVisuals)if(sourceKeys.insert(command.key).second)
            sourcePrograms.push_back(runtime.plan().sourceSkillActions.at(command.key).callback.json());
        record({{"code","experimental_attack_source_preflight_rejected"},{"message",error.what()},{"source_nut_programs",sourcePrograms},
            {"policy","reject-current-action-before-resource-publication-v1"},
            {"current_action_rejected",true},{"held_movement_preserved",true}});
        world.rejectSkillFeedback("experimental_attack_source_preflight_rejected");
        if (world.femaleGunnerWorld_) world.femaleGunnerWorld_->advance();
        return;
    }
    static_assert(std::is_nothrow_move_assignable<ExperimentalCharacterRuntime>::value,
        "Experimental runtime publication must not throw");
    runtime=std::move(candidate);
    if(preparedAudioRandom)world.random_.publishPreparedAudio(std::move(*preparedAudioRandom));
    sourceContactLedgers_.swap(preparedSourceLedgers);
    if(preparedSourceEffects)world.effects.swap(*preparedSourceEffects);
    if(sourceIdsAllocated){world.ids_.attacks=std::move(preparedSourceAttackIds);world.effectIds_=std::move(preparedSourceEffectIds);}
    if (preparedFemaleGunner) world.femaleGunnerWorld_->publish(std::move(preparedFemaleGunner));
    player.x=out.actor.x;player.y=out.actor.y;player.z=out.actor.z;player.vx=out.actor.vx;player.vy=out.actor.vy;player.vz=out.actor.vz;
    player.dir=out.actor.direction;player.mp=out.actor.mp;
    if(out.preparedSkillAction)out.preparedSkillAction->publish();
    world.observeSquirrelAction(runtime.activeActionSequence());
    for(const auto &sound:out.sounds)world.events.push_back({world.tick,"sound",sound});
    for(const auto &sound:preparedAudioEvents)world.events.push_back({world.tick,"sound",sound});
    for(const auto &receipt:preparedAudioReceipts)record(receipt);
    if(!state.alive||state.blocked)player.sourceSkillCameraFeedback={};
    for(auto shake:out.sourceCameraShakes) {
        shake.startedMs=world.nowMs();player.sourceSkillCameraFeedback=shake;
        world.events.push_back({world.tick,"camera_shake","reviewed_nut_body_flag",0,0,shake.amplitude});
    }
    for(const auto &diagnostic:out.diagnostics) {
        record(diagnostic);
        if(diagnostic.value("skill_failure",false))world.rejectSkillFeedback(diagnostic.value("code",std::string("experimental_skill_rejected")));
    }
    // The existing lifecycle owns dead poses; temporary damage/recovery states
    // retain their source animation until that lifecycle releases them.
    if(!state.alive||state.blocked){player.animationClock.reset();player.animationClockSource.clear();player.animationControllerDelays.reset();player.skillAnimationLayers.clear();}
    if(!state.alive){clearSourceGrab();if(world.femaleGunnerWorld_)world.femaleGunnerWorld_->advance();return;}
    if(!state.blocked){player.animation=out.state;player.animationPath=out.animationPath;player.poseFrame=out.poseFrame;
        player.animationClock=out.animationClock;player.animationClockSource=out.animationClock?out.animationPath:std::string();
        player.animationControllerDelays=out.animationControllerDelays;
        player.skillAnimationLayers=out.skillAnimationLayers;
        if(heldTargetScale)for(auto &cue:player.skillAnimationLayers)
            if(cue.scalePolicy==SourceSkillVisualScalePolicy::HeldTargetWidth)
                cue.scaleX=cue.scaleY=*heldTargetScale;
        player.animStart=world.nowMs()-int64_t(std::min(out.animationAgeMs,double(INT64_MAX)));}
    world.synchronizeEntityHandles();
    // A final action may clear its runtime state while still returning the
    // last visited strike frame. Keep its handle-owned hold until that batch
    // has been consumed, then clean up the null state below.
    if(sourceCapture_&&runtime.sourceGrabState())
        if(auto *held=const_cast<Actor *>(static_cast<const World &>(world).resolveActor(sourceCapture_->target)))updateCapturedPose(*held);
    for(size_t sample=0;sample<out.attacks.size();++sample) {
        const auto &frame=out.attacks[sample];const auto &sourceMotion=preparedAttacks[sample].motion;
        const bool movingFrame=frame.sourceEntity&&frame.skill&&bool(runtime.plan().sourceSkillActions.at(*frame.skill).movingImpact);
        if(frame.sourceGrabTry) {
            // A grab attempt owns only source overlap/qualification. It does
            // not allocate an attack ID, register a hit window, roll damage,
            // emit hit effects or charge another cooldown.
            Actor origin;origin.x=player.x;origin.y=player.y;origin.z=player.z;origin.dir=player.dir;
            for(const auto &box:preparedAttacks[sample].boxes) {
                if(sourceCapture_)break;
                if(box.w<=0||box.h<=0||box.d<=0)continue;
                for(auto &target:world.monsters) {
                    if(sourceCapture_)break;
                    if(target.dead||target.hp<=0||target.life!=ActorLife::Alive||target.capturedBy>=0)continue;
                    if(!world.overlaps(origin,box,target))continue;
                    trySourceGrab(target,frame,runtime);
                }
            }
            continue;
        }
        if(frame.sourceGrabDirectHit) {
            // 40JP Suplex is a held-object callback at a particular source
            // frame. It must not be rejected merely because that ANI has no
            // type15 box, nor may it hit a replacement at the old vector slot.
            if(!frame.skill||!frame.attack||!sourceCapture_||sourceCapture_->ownerAction!=frame.sourceGrabOwner||
               !(sourceCapture_->key==*frame.skill)||sourceCapture_->owner!=player.handle)continue;
            auto *target=const_cast<Actor *>(static_cast<const World &>(world).resolveActor(sourceCapture_->target));
            if(!target||target->dead||target->life!=ActorLife::Alive||target->capturedBy!=0){clearSourceGrab();continue;}
            if(frame.actionSequence!=action_||frame.pulseId!=contactPulse_) {
                action_=frame.actionSequence;contactPulse_=frame.pulseId;attackId_=world.ids_.attacks.next();hitTargets_.clear();
            }
            const auto definition=runtime.plan().attackDefinitions.find(frame.attack->source.memberPath);
            bool accepted=false;
            if(definition!=runtime.plan().attackDefinitions.end()&&definition->second.usable()&&!hitTargets_.count(target->handle))
                accepted=contact(*target,frame,definition->second,nullptr)&&!world.lastDamageTrace_.value("missed",false);
            else record({{"code","source_fighter_held_strike_attack_unavailable"},{"attack",frame.attack->json()},
                {"target",target->handle.json()},{"source_frame",frame.sourceFrame}});
            if(frame.sourceGrabRelease)clearSourceGrab(accepted);
            continue;
        }
        if(frame.suppressBodyDamage||(movingFrame&&!runtime.sourceSkillEntityLive(frame.sourceEntityInstance)))continue;
        if(frame.sourceGrabOwner&&(!sourceCapture_||sourceCapture_->ownerAction!=frame.sourceGrabOwner||
           !frame.skill||!(sourceCapture_->key==*frame.skill)||sourceCapture_->owner!=player.handle))continue;
        if(!frame.sourceEntity&&(frame.actionSequence!=action_ || frame.pulseId!=contactPulse_)){action_=frame.actionSequence;contactPulse_=frame.pulseId;
            attackId_=world.ids_.attacks.next();hitTargets_.clear();
            record({{"code","shared_swordman_attack_reader"},{"motion",sourceMotion.json()}});}
        if(!frame.attack){record({{"code","experimental_atk_binding_missing"},{"motion",frame.motion.json()}});continue;}
        const auto definition=runtime.plan().attackDefinitions.find(frame.attack->source.memberPath);
        if(definition==runtime.plan().attackDefinitions.end()||!definition->second.usable()) {
            record({{"code","experimental_atk_unsupported"},{"attack",frame.attack->json()}});continue;
        }
        const auto modifiers=sourceModifiers(frame);
        // Gun Dance's authored CHR geometry is consumed by its scheduled
        // radial pulse entity. A second body contact would add an extra hit.
        if(frame.skill&&world.identity().jobId==5&&frame.sourceFamily=="radial_multishot")continue;
        if(!frame.skill&&world.identity().jobId==5&&
            (normalize(frame.motion.tag)=="[attack motion]"||normalize(frame.motion.tag)=="[jumpattack motion]"||
             frame.sourceFamily=="female_gunner_basic_jump_shoot"||frame.sourceFamily=="female_gunner_basic_jump_pose"))continue;
        bool grabStrikeFrame=false,grabAcceptedDamage=false;
        for(const auto &box:preparedAttacks[sample].boxes) {
            if(box.w<=0||box.h<=0||box.d<=0)continue;
            grabStrikeFrame=true;
            if(movingFrame&&!runtime.sourceSkillEntityLive(frame.sourceEntityInstance))break;
            Actor origin;origin.x=frame.sourceEntity?frame.sourceOrigin[0]:player.x;
            origin.y=frame.sourceEntity?frame.sourceOrigin[1]:player.y;origin.z=frame.sourceEntity?frame.sourceOrigin[2]:player.z;
            origin.dir=frame.sourceEntity?frame.sourceDirection:player.dir;
            AttackVolume volume;volume.serial=frame.sourceEntity?sourceContactLedgers_.at(frame.sourceEntityInstance).attackId:attackId_;
            volume.x=origin.x;volume.y=origin.y;volume.z=origin.z;volume.direction=origin.dir;
            volume.box=box;volume.pulse=frame.pulseId;volume.skillId=frame.skill?frame.skill->skillId:0;volume.sourceAttack=definition->second;volume.sourceModifiers=modifiers;
            volume.sourceMotionTag=frame.motion.tag;
            volume.sourceAttackFamily=frame.sourceFamily;
            const auto typePolicy=runtime.configuration().weaponTypePolicy();
            if(typePolicy!="blocked")volume.sourceWeaponType=typePolicy=="magical"?DamageAttackType::Magical:DamageAttackType::Physical;
            world.attackVolumes.push_back(std::move(volume));
            for(auto &target:world.monsters) {
                if(movingFrame&&!runtime.sourceSkillEntityLive(frame.sourceEntityInstance))break;
                if(frame.sourceGrabOwner&&(!sourceCapture_||target.handle!=sourceCapture_->target))continue;
                const auto &targets=frame.sourceEntity?sourceContactLedgers_.at(frame.sourceEntityInstance).targets:hitTargets_;
                CombatBox intersection;
                if(target.dead||targets.count(target.handle)||!world.overlaps(origin,box,target,&intersection))continue;
                if(frame.sourceEntity&&frame.skill&&runtime.plan().sourceSkillActions.at(*frame.skill).movingImpact)contactMoving(target,frame,definition->second,runtime,intersection);
                else {
                    const bool accepted=contact(target,frame,definition->second,&intersection);
                    if(frame.sourceGrabOwner&&accepted&&!world.lastDamageTrace_.value("missed",false))grabAcceptedDamage=true;
                }
            }
        }
        // releaseStage begins before some ANIs reach their authored strike;
        // retain the victim through those opening visual frames. The first
        // actual final attack volume ends the hold even when it misses.
        if(frame.sourceGrabRelease&&grabStrikeFrame&&sourceCapture_&&sourceCapture_->ownerAction==frame.sourceGrabOwner)
            clearSourceGrab(grabAcceptedDamage);
    }
    if(sourceCapture_) {
        if(auto *held=const_cast<Actor *>(static_cast<const World &>(world).resolveActor(sourceCapture_->target)))updateCapturedPose(*held);
        else clearSourceGrab();
    }
    for(const auto &command:out.sourceSkillVisuals)if(command.kind==ExperimentalSourceVisual::Kind::Retire) {
        const auto found=sourceContactLedgers_.find(command.entity);
        if(found!=sourceContactLedgers_.end()) {
            for(auto &effect:world.effects)if(effect.id==found->second.effectId)effect.expires=std::min(effect.expires,world.nowMs());
            sourceContactLedgers_.erase(found);
        }
    }
    if (world.femaleGunnerWorld_) world.femaleGunnerWorld_->advance();
}
} // namespace dnf
