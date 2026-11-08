#include "dnf/act_world_host.hpp"
#include "dnf/progression.hpp"
#include "dnf/session.hpp"
#include "dnf/storage.hpp"
#include "dnf/female_gunner_world.hpp"
#include "explicit_skill_preview_fixture.hpp"
#include <algorithm>
#include <chrono>
#include <stdexcept>
namespace dnf {
namespace {
constexpr const char *mob="monster/act8/wooden_doll_nomnal/wooden_doll_nomnal.mob";
constexpr uint64_t generation=53;
struct CollisionFixture {
 World world;ActWorldHost host;
 std::function<void(World&)> beforeContact;
 std::function<uint64_t(uint64_t)> externalDelta;
 CollisionFixture(Pvf &pvf,Assets &assets,const RegionCatalog &catalog,double dx=50,int direction=1,int level=1,int job=0)
 :world(pvf,assets,WorldRules::BetaFoundationV1),host(world,pvf,assets,"collision-test:"+sha256(assets.staticBytes("audio.xml"))) {
  Progression p(catalog);
  if(job) {
   static const char *classes[]={"swordman","fighter","gunner","mage","priest","atgunner","thief","atfighter","atmage"};
   world.enableExperimentalCharacters();CharacterStore store(std::filesystem::absolute("reaction-fixture-"+std::to_string(job)));
   store.data["characters"][0]={{"name","PreparedReaction"},{"class",classes[job]},{"identity",CharacterIdentity{job,0,0}.json()},
    {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,p);
  } else world.applyEquipment(p);
  world.freezeAi=true;world.combat=false;
  world.mapWidth=2000;world.walkRects={{0,185,2000,1200}};world.blockedRects.clear();world.monsters.clear();
  world.player.x=world.player.px=500+direction*dx;world.player.y=world.player.py=344;world.player.dir=-direction;
  Actor a;a.id=1;a.monsterPath=mob;a.x=a.px=500;a.y=a.py=344;a.dir=direction;
  world.initializeMonsterAttributes(a,level,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
  world.monsters.push_back(std::move(a));world.synchronizeEntityHandles();world.randomStreams()=RandomStreams(67);
  world.setObjectTick([this](World &w){
   if(beforeContact)beforeContact(w);
   SimulationStep step{uint64_t(w.tick),uint64_t(w.nowMs()),uint32_t(w.nowMs()-FixedStepClock::millisecondsAtTick(w.tick-1))};
   std::map<uint64_t,uint64_t> deltas;
   for(const auto &[id,instance]:host.instances())if(instance.status==ActInstanceStatus::Running&&instance.clockMode==ActClockMode::ExternalAnimationDelta)
    deltas[id]=externalDelta?externalDelta(id):(w.monsters.front().hitStopped?0:uint64_t(step.deltaMilliseconds)*1000);
   const auto result=host.advance(step,deltas);if(!result.ok)throw std::runtime_error(result.error);
  });
 }
 void bind(Pvf &pvf,uint64_t id=40,size_t ownerIndex=0) {
  const auto route=selectMonsterAction(pvf,pvf.script(mob),"attack",0);
  const auto compiled=host.compile(route.resolvedPath);if(!compiled.ok)throw std::runtime_error(compiled.json().dump());
  ActBindRequest request;request.owner=world.monsters.at(ownerIndex).handle;request.instanceId=id;request.actionId=id+100;
  request.tick=uint64_t(world.tick);request.simulationMs=uint64_t(world.nowMs());request.randomSeed=7;request.randomSequence=9;
  request.clockMode=ActClockMode::ExternalAnimationDelta;
  const auto result=host.bind(compiled.program,request,{},false,&route);if(!result.ok)throw std::runtime_error(result.error);
 }
 void ticks(int n){while(n-->0)world.advanceSingleTick();}
 size_t hits()const{return size_t(std::count_if(world.events.begin(),world.events.end(),[](const Event&e){return e.kind=="player_hit"&&e.name=="act_source";}));}
 Json observed()const{return {{"hp",world.player.hp},{"random",world.randomStreams().snapshot()},
  {"host",host.snapshot(generation)},{"simulation",world.simulationCheckpoint()},{"events",world.eventLog()}};}
};
}
Json runActCollisionTests(Pvf &pvf,Assets &assets) {
 const auto root=std::filesystem::u8path("reports/seven-job-world/act-collision");
 Json out={{"status","running"},{"checks",Json::array()},{"samples",Json::object()},{"pvf_sha256",pvf.identity()},
  {"scope","Actual 1031 wooden doll MOB slot0/ACT root ANI type15 versus current Swordman CHR type14; source default level65 actual contact plus explicit diagnostic level1 geometry placement on isolated plane; same MOB source attributes"},
  {"classification","inferred beta, fixed-tick endpoint sampling; source timing and geometry retained"},{"whole_monster_complete",false}};
 const auto check=[&](bool okay,const std::string &message){if(!okay)throw std::runtime_error(message);out["checks"].push_back(message);};
 try {
  RegionCatalog catalog(pvf,assets);
  const auto route=selectMonsterAction(pvf,pvf.script(mob),"attack",0);const auto attack=readActCollisionAttack(pvf.script(route.attackInfoResolvedPath));
  check(route.ok&&attack.sourceReady&&attack.reactionReady&&attack.pauseMs==50&&attack.delayRate==1,"Real wooden doll paired ATK has source damage/reaction/hit-pause tuple and no unresolved push/lift");
  const auto sourceLevel=evaluateMonsterCombatAttributes(readMonsterAttributeSource(pvf,mob,false),65,false,MonsterCombatAttributePolicy::inferredMobCombatTableV1());
  check(sourceLevel.usable()&&sourceLevel.attributes->tableAttackMissSource.at("level")==65,
   "Source MOB level65 now consumes raw11 via its real attacker MISS receipt; no attribute gate was erased");
  out["samples"]["source_level65_attributes"]=sourceLevel.snapshot();
  // Own Knee, Priest Upper and female Upper input/body/equipment against unchanged wooden-doll root ANI/ATK.
  // Source phase and geometry placement are diagnostic only: the external ACT
  // clock is held until the desired player pose, then samples that exact ANI.
  // No synthetic damage, armor enum, box or source coefficient is substituted.
  for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines})
  for(const SkillKey sourceSkill:{SkillKey{2,4},SkillKey{4,1},SkillKey{1,5},SkillKey{3,12}})
  for(const std::string mode:{"armored","unarmored","lethal","guard","miss","fault_armored","fault_unarmored","stun_armored","missing_reaction","double_control","double_fault"}) {
   // Mage's own Upper has no authored armor. Its four narrow samples add
   // real hostile ACT transactions while a physically requested side-slide is
   // live; all prior jobs/modes and assertions remain unchanged.
   const bool mageSidestep=sourceSkill==SkillKey{3,12};
   if(mageSidestep&&mode!="unarmored"&&mode!="lethal"&&mode!="stun_armored"&&mode!="missing_reaction")continue;
   // Upper's own ANI remains armored through every frame. Preserve Knee's
   // unarmored tests instead of fabricating an unarmored Upper source pose.
   if(sourceSkill.jobId==4&&(mode=="unarmored"||mode=="fault_unarmored"))continue;
   // The real source-level65 raw11 term is nonzero; level1 is exactly zero.
   // Use that unchanged MOB level for MISS rather than invent a miss chance.
   CollisionFixture f(pvf,assets,catalog,500,1,mode=="miss"?65:1,sourceSkill.jobId);auto &w=f.world;
   w.configureAnimationClock(clock);
   auto &runtime=*w.experimentalRuntime();const SkillKey knee=sourceSkill;
   check(w.assignLearnedSkillSlot(0,knee).ok&&!w.experimentalSkillPreviewEnabled()&&!w.debugOverrides().enabled&&
     w.runtimeSkillPolicy(knee).implemented&&w.skillState().learnedLevel(knee)==1&&
     runtime.configuration().binding(knee)&&runtime.configuration().binding(knee)->level==1&&
     (sourceSkill.jobId==1?runtime.plan().sourceSkillActions.at(knee).castSound=="FT_UPPER_READY":
      runtime.configuration().sourceActionAudioPolicy()==(sourceSkill.jobId==2?"inferred-current1031-knee-cast-audio-v1":"disabled")),
    "ACT active-body fixture uses the real initial grant and canonical learned source slot/audio without preview or debug");
   const bool fault=mode.rfind("fault_",0)==0,unarmored=mageSidestep||mode=="unarmored"||mode=="fault_unarmored";
   const bool doubleContact=mode=="double_control"||mode=="double_fault";
   const bool control=mode=="stun_armored"||mode=="double_control";
   bool ready=false,attempted=false;Json before=Json::object();int64_t cooldownDeadline=0;
   if(doubleContact) {
    auto second=w.monsters[0];second.id=2;second.handle={};w.monsters.push_back(std::move(second));w.synchronizeEntityHandles();
   }
   f.externalDelta=[&](uint64_t){return ready?uint64_t(1):uint64_t(0);};f.bind(pvf);
   if(doubleContact)f.bind(pvf,41,1);
   const auto damagePolicy=DamageResolutionPolicy::inferredPveDamageV1(w.combatAttributes_->damageConstants);
   DamageRequest probe;probe.attacker=w.monsters[0].handle;probe.target=w.player.handle;
   probe.attackInstance=f.host.collisions().at(40).attackInstance;
   probe.attackerStats=makeDamageCombatant(*w.monsters[0].combatAttributes,damagePolicy);
   probe.targetStats=makeDamageCombatant(*w.combatAttributes_);
   probe.attack=control?readActCollisionAttack(pvf.script("monster/newmonsters/queen_rosi/attackinfo/attack1.atk")).damage:attack.damage;
   probe.contactRange=DamageContactRange::Melee;
   const auto resistance=evaluateCharacterStatusResistances(w.combatAttributes_->pureChr,w.characterSource(),
       w.combatAttributes_->equipmentSources,w.combatAttributes_->qualificationLevel);
   bool selectedSeed=false;Json expectedFirst,expectedSecond,randomAfterFirst,randomAfterSecond;
   for(uint64_t seed=0;seed<(mode=="miss"?65536u:4096u)&&!selectedSeed;++seed) {
    RandomStreams random(seed);auto statuses=w.statuses_;
    // Normal accepted Knee cast emits its own voice before the hostile
    // contact. Include that independent, saved draw in expected bank state;
    // Combat values still come from the unchanged source damage preparation.
    if(sourceSkill.jobId==2)(void)random.stream(RandomDomain::Audio,0).bounded(100);
    auto prepared=prepareDamageContact(probe,damagePolicy,resistance,statuses,random,uint64_t(w.nowMs()));
    if(prepared.ready()&&prepared.resolution.missed==(mode=="miss")&&prepared.resolution.hpDamage&&
       (mode=="miss"||*prepared.resolution.hpDamage>0)) {
     expectedFirst=prepared.resolution.snapshot();
     publishDamageContact(std::move(prepared),statuses,random);randomAfterFirst=random.snapshot();
     if(doubleContact) {
      auto second=probe;second.attacker=w.monsters[1].handle;second.attackInstance=f.host.collisions().at(41).attackInstance;
      second.attackerStats=makeDamageCombatant(*w.monsters[1].combatAttributes,damagePolicy);second.attack=attack.damage;
      auto next=prepareDamageContact(second,damagePolicy,resistance,statuses,random,uint64_t(w.nowMs()));
      if(!next.ready()||next.resolution.missed||!next.resolution.hpDamage||*next.resolution.hpDamage<=0)continue;
      expectedSecond=next.resolution.snapshot();publishDamageContact(std::move(next),statuses,random);randomAfterSecond=random.snapshot();
     }
     w.randomStreams()=RandomStreams(seed);selectedSeed=true;
    }
   }
   check(selectedSeed,"Private source-damage preparations select one diagnostic seed; only that seed is installed, no contact/HP/status is published");
   if(control) {
    const std::string stun="monster/newmonsters/queen_rosi/attackinfo/attack1.atk";
    const auto source=readActCollisionAttack(pvf.script(stun));
    check(source.sourceReady&&source.reactionReady&&readAttackStatuses(source.original).entries.at(0).chancePercent==100,
     "Active-body control test labels an unchanged100% stun ATK as explicit cross-source diagnostic pairing");
    f.host.state_.collisions.at(40).currentAttack=stun;
   }
   if(fault||mode=="double_fault") {
    auto &instance=f.host.state_.instances.at(mode=="double_fault"?41:40);auto program=std::make_shared<ActProgram>(*instance.program);
    ActBehavior behavior;behavior.source=program->source;behavior.instructions.push_back({program->source,ActSpawn{}});
    const auto index=program->behaviors.size();program->behaviors.push_back(behavior);
    ActTrigger trigger;trigger.source=program->source;trigger.event=ActEventKind::AttackSuccess;
    ActBehaviorCall call;call.behavior=index;call.source=program->source;trigger.calls.push_back(call);program->triggers.push_back(trigger);
    instance.triggers.resize(program->triggers.size());instance.program=program;
   }
   if(mode=="missing_reaction") {
    check(bool(w.equippedAppearance_),"Missing-reaction fixture begins with a real equipped appearance");
    auto &motions=w.equippedAppearance_->bodyMotions;const auto path=w.characterSource().motion("[down motion]");
    const auto count=motions.size();motions.erase(std::remove_if(motions.begin(),motions.end(),[&](const auto &m){return m.resource.path==path;}),motions.end());
    check(motions.size()+1==count,"Explicit missing-resource injection removes exactly the required lethal CHR appearance binding");
   }
   f.beforeContact=[&](World &world) {
    if(attempted||!runtime.sourceBodyReactionReady()||world.armor()==unarmored)return;
    if(sourceSkill.jobId==4) {
     if(!world.player.animationClock||world.player.skillAnimationLayers.empty())return;
     const auto own=assets.animation(world.player.animationPath);
     const auto &boxes=own->frames.at(world.player.animationClock->frame).boxes;
     if(std::none_of(boxes.begin(),boxes.end(),[](const Box &box){return box.type==14&&box.w>0&&box.h>0&&box.d>0;}))return;
    }
    if(mageSidestep) {
     const auto diagnostic=runtime.snapshotDiagnostics();const auto &steps=diagnostic.at("source_body_sidesteps");
     if(steps.size()!=1||steps[0].at("state").at("extent").get<double>()<=0)return;
     // Wait until the real queued direction KEYUP has been consumed. The
     // accepted action retains its latched direction, so reaction continuation
     // cannot be confused with later ordinary movement from a held input.
     const auto queue=world.simulationCheckpoint().at("inputs");
     if(std::any_of(queue.at("pending").begin(),queue.at("pending").end(),[](const Json &entry){
        return entry.at("payload").at("key")==3;
     }))return;
     const auto &step=steps[0].at("state");const auto &policy=*runtime.plan().sourceSkillActions.at(knee).bodySidestep;
     if(step.at("source_ms").get<double>()>=policy.turnSourceMs)return;
     check(step.at("direction")==1&&world.player.y>step.at("origin_y").get<double>()&&
        !world.armor()&&!world.invincible()&&world.player.animationPath==runtime.plan().sourceSkillActions.at(knee).motion.memberPath,
      "Mage hostile ACT samples an actual nonzero outward side-slide after physical KEYUP, using own unprotected Upper pose");
    }
    check(world.neutralPlayerReactionGate(world.player).empty(),"Ground own BodyAttack reaches the prepared active-action gate: "+mode);
    for(int boundary=0;boundary<3;++boundary) {
     auto excluded=world.player;
     if(boundary==0)excluded.z=1;
     if(boundary==1)excluded.recovery=1;
     if(boundary==2)excluded.capturedBy=99;
     check(!world.neutralPlayerReactionGate(excluded).empty(),"Ground source-body admission retains exact air/recovery/capture gates");
    }
    check(world.player.animationClock&&world.player.animationClockSource==runtime.plan().sourceSkillActions.at(knee).motion.memberPath,
     "Active contact observes the actual own source clock and frame: "+mode);
    const auto target=assets.animation(world.player.animationPath);const auto frame=world.player.animationClock->frame;
    auto &collision=f.host.state_.collisions.at(40);const auto motion=assets.animation(collision.baseAnimation);
    bool aligned=false;uint64_t phase=0;
    for(size_t index=0;index<motion->frames.size()&&!aligned;++index) {
     for(const auto &attackBox:motion->frames[index].boxes)if(attackBox.type==15)
      for(const auto &hurt:target->frames.at(frame).boxes)if(hurt.type==14&&!aligned&&
       attackBox.z+attackBox.d>=hurt.z&&hurt.z+hurt.d>=attackBox.z) {
       const double hx=world.player.x+(world.player.dir>0?hurt.x:-double(hurt.x)-hurt.w)+hurt.w*.5;
       auto &owner=world.monsters[0];owner.dir=1;owner.x=owner.px=hx-attackBox.x-attackBox.w*.5;
       owner.y=owner.py=world.player.y+hurt.y+hurt.h*.5-attackBox.y-attackBox.h*.5;
       auto &instance=f.host.state_.instances.at(40);instance.animationUs=phase;instance.firstAdvance=false;aligned=true;
      }
     if(!aligned)phase+=uint64_t(motion->frames[index].duration)*1000;
    }
    check(aligned,"Diagnostic source-phase placement finds real XYZ-overlapping type15/type14, without replacing geometry: "+mode);
    if(doubleContact) {
     // The second owner samples the first contact's private Actor result in
     // this very advance call. Control-first must therefore align against the
     // exact own damage1 frame0; ordinary armored-first retains the live pose.
     const auto nextTarget=mode=="double_control"?assets.animation(world.characterSource().motion("[damage motion 1]")):target;
     const auto nextFrame=mode=="double_control"?size_t(0):size_t(frame);
     auto &secondCollision=f.host.state_.collisions.at(41);const auto nextMotion=assets.animation(secondCollision.baseAnimation);
     bool nextAligned=false;uint64_t nextPhase=0;
     for(size_t index=0;index<nextMotion->frames.size()&&!nextAligned;++index) {
      for(const auto &box:nextMotion->frames[index].boxes)if(box.type==15)
       for(const auto &hurt:nextTarget->frames.at(nextFrame).boxes)if(hurt.type==14&&!nextAligned&&
          box.z+box.d>=hurt.z&&hurt.z+hurt.d>=box.z) {
        const double hx=world.player.x+(world.player.dir>0?hurt.x:-double(hurt.x)-hurt.w)+hurt.w*.5;
        auto &owner=world.monsters[1];owner.dir=1;owner.x=owner.px=hx-box.x-box.w*.5;
        owner.y=owner.py=world.player.y+hurt.y+hurt.h*.5-box.y-box.h*.5;
        auto &instance=f.host.state_.instances.at(41);instance.animationUs=nextPhase;instance.firstAdvance=false;nextAligned=true;
       }
      if(!nextAligned)nextPhase+=uint64_t(nextMotion->frames[index].duration)*1000;
     }
     check(nextAligned&&world.monsters[0].handle!=world.monsters[1].handle&&
        f.host.collisions().at(40).attackInstance!=f.host.collisions().at(41).attackInstance,
      "Two actual owners/attack identities use source XYZ boxes, including the exact private post-control damage pose");
    }
    world.player.hp=mode=="lethal"?1:1000000;world.player.maxHp=std::max(world.player.maxHp,world.player.hp);
    if(mode=="guard")world.guardUntil_=world.nowMs()+500;
    world.player.sourceSkillCameraFeedback={world.nowMs(),2,2000,*runtime.activeActionSequence()};
    const auto &visual=runtime.plan().sourceSkillActions.at(knee).bodyLayers.front().source.memberPath;
    Effect attached;attached.id=1900000000;attached.animation=visual;attached.attached=true;attached.damageEnabled=false;
    attached.born=world.nowMs();attached.expires=world.nowMs()+5000;world.effects.push_back(attached);
    auto child=attached;child.id=1900000001;child.attached=false;child.alsParentId=attached.id;world.effects.push_back(child);
    world.enqueue({world.simulationNanoseconds()+20000000000LL,20,true});
    world.enqueue({world.simulationNanoseconds()+21000000000LL,20,false});
    cooldownDeadline=world.nowMs()+runtime.remainingCooldown(knee,world.nowMs());
    before={{"hp",world.player.hp},{"mp",world.player.mp},{"random",world.randomStreams().snapshot()},
     {"runtime",runtime.snapshotDiagnostics()},{"cooldown",runtime.cooldownSnapshot(world.nowMs())},
     {"skills",world.skillState().snapshot(world.nowMs())},{"inputs",world.simulationCheckpoint().at("inputs")},
     {"body_clock",world.player.animationClock->frame},{"layers",world.player.skillAnimationLayers.size()},
     {"effect_count",world.effects.size()},{"status_ids",world.statuses_.instanceWatermark()},
     {"act_phase_us",phase},{"source_attack",collision.currentAttack}};
    if(mageSidestep) {
     before["player_y"]=world.player.y;
     before["sidestep"]=runtime.snapshotDiagnostics().at("source_body_sidesteps");
    }
    ready=attempted=true;
   };
   if(mageSidestep) {
    w.enqueue({w.simulationNanoseconds(),3,true});
    w.enqueue({w.simulationNanoseconds()+16666667LL,3,false});
   }
   const int originalMp=w.player.mp;w.enqueue({w.simulationNanoseconds(),20,true});
   for(int i=0;i<180&&!attempted;++i)f.ticks(1);
   check(attempted&&w.player.mp<originalMp&&cooldownDeadline>w.nowMs(),"Real own source input paid MP/CD before the active ACT transaction: "+mode);
   const auto after=w.statReport().at("last_damage");
   const bool rejected=fault||mode=="missing_reaction",guard=mode=="guard";
   const auto activeSample="active_body_"+std::to_string(sourceSkill.jobId)+"_"+std::string(ani_clock::policyName(clock))+"_"+mode;
   out["samples"][activeSample]={{"before",before},{"after",after},
    {"observed",f.observed()},{"runtime",runtime.snapshotDiagnostics()},{"diagnostics",f.host.diagnostics()},
    {"expected_first_damage",expectedFirst},{"expected_second_damage",expectedSecond}};
   check(w.player.mp==before.at("mp")&&runtime.cooldownSnapshot(w.nowMs())==before.at("cooldown")&&
      w.skillState().snapshot(w.nowMs())==before.at("skills"),
    "Active ACT never refunds/recharges MP, restarts CD or changes normal learning: "+mode);
   check(runtime.snapshotDiagnostics().at("action_sequence")==before.at("runtime").at("action_sequence")&&
      runtime.snapshotDiagnostics().at("source_nut_entity_sequence")==before.at("runtime").at("source_nut_entity_sequence")&&
      runtime.snapshotDiagnostics().at("last_cost")==before.at("runtime").at("last_cost"),
    "Prepared cancellation retains paid cost and monotonic source action/entity counters: "+mode);
   if(doubleContact) {
    const bool interrupted=mode=="double_control";
    const int firstDamage=expectedFirst.at("hp_damage").get<int>();
    const int secondDamage=interrupted?expectedSecond.at("hp_damage").get<int>():0;
    check(f.hits()==(interrupted?2:1)&&w.player.hp==before.at("hp").get<int>()-firstDamage-secondDamage&&
       w.randomStreams().snapshot()==(interrupted?randomAfterSecond:randomAfterFirst)&&
       f.host.collisions().at(40).acceptedTargets.size()==1,
     "Two-owner batch preserves exactly each successful contact HP/RNG receipt; later fault never rolls back earlier success: "+mode);
    check(after.at("player_reaction_outcome").at("interrupted")==interrupted&&
       after.at("player_defense").at("source_body_protection").at("super_armor")==!interrupted,
     "Private prior interruption removes stale live armor from subsequent contact: "+mode);
    if(interrupted) {
     check(f.host.instances().at(40).status==ActInstanceStatus::Running&&f.host.instances().at(41).status==ActInstanceStatus::Running&&
        f.host.collisions().at(41).acceptedTargets.size()==1&&
        after.at("player_defense").at("prior_contact_interrupted_action")==true&&
        after.at("player_reaction_outcome").at("control_status_interrupt")==true&&
        !runtime.attacking()&&!w.armor()&&w.statusStunned(w.player.handle)&&w.player.animation=="damage1"&&
        w.player.animationPath==w.characterSource().motion("[damage motion 1]"),
      "First-owner control interrupts armor; second owner samples own valid damage1 and resolves ordinary reaction in the same batch");
     const auto queue=w.simulationCheckpoint().at("inputs");
     check(w.player.skillAnimationLayers.empty()&&!w.player.animationClock&&w.player.sourceSkillCameraFeedback.ownerAction==0&&
        std::none_of(w.effects.begin(),w.effects.end(),[](const Effect &e){return e.id==1900000000||e.id==1900000001;})&&
        w.attackVolumes.empty()&&queue.at("sequences")==before.at("inputs").at("sequences")&&
        queue.at("pending").size()==1&&!queue.at("pending")[0].at("payload").at("down").get<bool>(),
      "Two-owner successful batch publishes one prepared action/clock/layer/camera/effect/queue cleanup and preserves KEYUP watermark");
    } else {
     check(f.host.instances().at(40).status==ActInstanceStatus::Running&&f.host.instances().at(41).status==ActInstanceStatus::Faulted&&
        !f.host.collisions().count(41)&&f.host.diagnostics().dump().find("ACT attack-success consumer fault")!=std::string::npos&&
        runtime.snapshotDiagnostics()==before.at("runtime")&&runtime.attacking()&&w.armor()&&!w.invincible()&&w.player.hitStopped&&
        w.player.animationClock&&w.player.animationClock->frame==before.at("body_clock")&&
        w.player.skillAnimationLayers.size()==before.at("layers")&&w.effects.size()==before.at("effect_count")&&
        w.simulationCheckpoint().at("inputs")==before.at("inputs")&&w.player.sourceSkillCameraFeedback.ownerAction!=0&&
        w.statuses_.instanceWatermark()==before.at("status_ids"),
      "Second-owner late fault discards only its contact/RNG and cleanup candidate; first armored HP/hitstop/ledger survives with live action visuals");
    }
   } else if(rejected||guard) {
    check(f.hits()==0&&w.player.hp==before.at("hp")&&w.randomStreams().snapshot()==before.at("random")&&
       w.simulationCheckpoint().at("inputs")==before.at("inputs")&&runtime.snapshotDiagnostics()==before.at("runtime")&&
       w.player.animationClock&&w.player.animationClock->frame==before.at("body_clock")&&
       w.player.skillAnimationLayers.size()==before.at("layers")&&w.effects.size()==before.at("effect_count")&&
       w.statuses_.instanceWatermark()==before.at("status_ids")&&w.player.sourceSkillCameraFeedback.ownerAction!=0,
     "Fault/missing reaction or real invincibility leaves action/HP/MP/CD/RNG/status/queue/visuals intact: "+mode);
    if(rejected)check(f.host.instances().at(40).status==ActInstanceStatus::Faulted&&
       f.host.diagnostics().dump().find(mode=="missing_reaction"?"Player reaction lacks exact CHR/appearance binding":"ACT attack-success consumer fault")!=std::string::npos,
     "Rejected active contact reaches its exact late/preflight fault and discards contact acceptance: "+mode);
    else check(f.host.collisions().at(40).acceptedTargets.empty()&&w.invincible(),"Published guard immunity consumes no ACT target identity or damage random");
   } else if(mode=="miss") {
    check(f.hits()==0&&w.player.hp==before.at("hp")&&after.at("missed")==true&&
       !f.host.collisions().at(40).acceptedTargets.empty()&&
       runtime.snapshotDiagnostics()==before.at("runtime")&&w.simulationCheckpoint().at("inputs")==before.at("inputs")&&
       w.player.skillAnimationLayers.size()==before.at("layers")&&w.effects.size()==before.at("effect_count")&&
       !w.player.hitStopped&&w.player.sourceSkillCameraFeedback.ownerAction!=0&&
       w.statuses_.instanceWatermark()==before.at("status_ids")&&w.randomStreams().snapshot()!=before.at("random"),
     "Actual source MISS publishes its one contact/random receipt while discarding cancellation and preserving live action/visuals/HP/status");
   } else {
    check(f.hits()==1&&w.player.hp==std::max(0,before.at("hp").get<int>()-after.at("hp_damage").get<int>())&&
       !after.at("missed").get<bool>(),"Actual accepted source contact publishes exact HP once while own BodyAttack is active: "+mode);
    const bool interrupted=unarmored||mode=="lethal"||mode=="stun_armored";
    check(after.at("player_reaction_outcome").at("interrupted")==interrupted&&
       after.at("player_defense").at("source_body_protection").at("super_armor")==!unarmored,
     "Accepted source-frame protection is distinct from invincibility and reports the actual interruption decision: "+mode);
    if(interrupted) {
     check(!runtime.attacking()&&!w.armor()&&runtime.snapshotDiagnostics().at("source_body_actions")==0&&
        w.player.skillAnimationLayers.empty()&&!w.player.animationClock&&w.player.sourceSkillCameraFeedback.ownerAction==0&&
        std::none_of(w.effects.begin(),w.effects.end(),[](const Effect &e){return e.id==1900000000||e.id==1900000001;})&&
        w.attackVolumes.empty(),"Prepared active interruption retires body clock/protection/layer/camera/attached descendants and attack volumes together: "+mode);
     const auto queue=w.simulationCheckpoint().at("inputs");
     check(queue.at("sequences")==before.at("inputs").at("sequences")&&queue.at("pending").size()==1&&
        !queue.at("pending")[0].at("payload").at("down").get<bool>(),
      "Active interruption preserves physical KEYUP and monotonic queue watermark while discarding future action DOWN");
     check(w.player.dead==(mode=="lethal")&&(mode!="lethal"||w.player.animation=="down")&&
        (mode!="stun_armored"||(w.statusStunned(w.player.handle)&&w.player.animation=="damage1"&&
          w.player.animationPath==w.characterSource().motion("[damage motion 1]"))),
      "Lethal and control-status outcomes interrupt armor and publish a valid own CHR pose without inventing immunity: "+mode);
    } else {
     check(runtime.attacking()&&w.armor()&&!w.invincible()&&w.player.hitStopped&&w.player.animationClock&&
        w.player.animationClock->frame==before.at("body_clock")&&w.player.skillAnimationLayers.size()==before.at("layers")&&
        w.effects.size()==before.at("effect_count")&&w.simulationCheckpoint().at("inputs")==before.at("inputs"),
      "Nonlethal ordinary ACT hit deducts HP and applies hitstop while preserving live armor action/clock/layers/queue");
    }
   }
   if(mageSidestep) {
    check(before.at("sidestep").size()==1&&before.at("sidestep")[0].at("state").at("extent").get<double>()>0&&
       w.player.y==before.at("player_y").get<double>(),
     "Mage ACT acceptance/rejection preserves actual contact-plane Y; canceled return never snaps the actor to its origin");
    if(rejected) {
     check(runtime.attacking()&&runtime.snapshotDiagnostics().at("source_body_sidesteps")==before.at("sidestep")&&
        f.host.instances().at(40).status==ActInstanceStatus::Faulted&&f.hits()==0&&
        f.host.diagnostics().dump().find("Player reaction lacks exact CHR/appearance binding")!=std::string::npos,
      "Missing real reaction binding rejects the ACT transaction and preserves exact live sidestep alongside existing HP/MP/CD/RNG/status/queue/visual assertions");
    } else {
     check(after.at("player_reaction_outcome").at("interrupted")==true&&
        after.at("player_defense").at("source_body_protection").at("super_armor")==false&&
        runtime.snapshotDiagnostics().at("source_body_sidesteps").empty(),
      "Real nonlethal/lethal/source-control ACT commits own unprotected Mage action and side-return cancellation atomically");
    }
   }
   if(!rejected&&!guard&&mode!="miss"&&after.at("player_reaction_outcome").at("interrupted").get<bool>()) {
    check(f.host.cancelAll("active body cleanup continuation diagnostic").ok,"Continuation retires only diagnostic ACT attackers after interruption assertions");
    f.ticks(3);
    if(mageSidestep)check(runtime.snapshotDiagnostics().at("source_body_sidesteps").empty()&&
       w.player.y==before.at("player_y").get<double>(),
     "Post-transaction Mage ticks cannot revive the canceled side-slide or move toward its old origin");
    out["samples"][activeSample]["continuation"]={
     {"runtime",runtime.snapshotDiagnostics()},{"attacking",runtime.attacking()},{"armor",w.armor()},
     {"actor_animation",w.player.animation},{"actor_path",w.player.animationPath},
     {"actor_clock_source",w.player.animationClockSource},{"has_clock",bool(w.player.animationClock)},
     {"layers",w.player.skillAnimationLayers.size()},{"camera_owner",w.player.sourceSkillCameraFeedback.ownerAction},
     {"owned_effects_remaining",std::count_if(w.effects.begin(),w.effects.end(),[](const Effect &e){return e.id==1900000000||e.id==1900000001;})}};
    check(!runtime.attacking()&&!w.armor()&&runtime.snapshotDiagnostics().at("source_body_actions")==0&&
       runtime.snapshotDiagnostics().at("source_nut_entities")==0&&w.player.skillAnimationLayers.empty()&&
       (!w.player.animationClock||(w.player.animation=="damage1"&&
          w.player.animationClockSource==w.player.animationPath&&
          w.player.animationClockSource==w.characterSource().motion("[damage motion 1]")&&
          w.player.animationClockSource!=runtime.plan().sourceSkillActions.at(knee).motion.memberPath))&&
       w.player.sourceSkillCameraFeedback.ownerAction==0&&w.attackVolumes.empty()&&
       std::none_of(w.effects.begin(),w.effects.end(),[](const Effect &e){return e.id==1900000000||e.id==1900000001;}),
     "Following fixed ticks may rebuild own damage clock but cannot resurrect retired skill/action, armor, entity, layers or descendants: "+mode);
   }
  }
  // The same actual source attacker must consume each admitted character's
  // own damage/down presentation and its value-owned controller candidate.
  for(const int job:{0,1,2,3,4,5,8}) {
   CollisionFixture f(pvf,assets,catalog,50,1,1,job);auto &w=f.world;
   w.configureAnimationClock(ani_clock::ClockPolicy::Inferred60UsPercentDeadlines);
   std::optional<SkillKey> cooldownKey;
   int64_t cooldownDeadline=0;
   if(auto *runtime=w.experimentalRuntime()) {
    for(const auto &[key,skill]:runtime->plan().skills)if(skill.kind==SkillSourceKind::Active) {cooldownKey=key;break;}
    if(!cooldownKey)throw std::runtime_error("Prepared reaction fixture has no actual active skill");
    auto saved=runtime->cooldownSnapshot(w.nowMs());
    saved["skills"].push_back({{"key",cooldownKey->json()},{"skill_source",runtime->plan().skills.at(*cooldownKey).source.json()},{"remaining_ms",9000}});
    runtime->publishCooldownRestore(ExperimentalCharacterRuntime::prepareCooldownRestore(saved,runtime->plan(),w.nowMs()));
    cooldownDeadline=w.nowMs()+9000;
   }
   const auto learned=w.skillState().snapshot(w.nowMs());const auto normalMp=w.player.mp;
   w.enqueue({w.simulationNanoseconds()+20000000000LL,20,true});
   w.enqueue({w.simulationNanoseconds()+21000000000LL,20,false});
   const auto inputSequence=w.simulationCheckpoint().at("inputs").at("sequences");
   const auto hp=w.player.hp;f.bind(pvf);
   for(int i=0;i<180&&!f.hits();++i)f.ticks(1);
   const auto receipt=w.statReport().at("last_damage");
   out["samples"]["prepared_attempt_"+std::to_string(job)]={{"observed",f.observed()},{"diagnostics",f.host.diagnostics()},{"last_damage",receipt}};
   check(f.hits()==1&&w.player.hp==hp-receipt.at("hp_damage").get<int>()&&
    receipt.contains("player_reaction")&&receipt.at("player_reaction").at("identity")==w.identity().json(),
    "Seven-job actual source ACT HP/reaction consumer publishes once for job "+std::to_string(job));
   check(w.player.animation=="damage1"&&w.player.animationPath==w.characterSource().motion("[damage motion 1]")&&w.player.hitStopped,
    "Accepted reaction uses this job's exact CHR damage binding and source hit pause: "+std::to_string(job));
   auto expectedSkills=learned;expectedSkills["captured_ms"]=w.nowMs();
   // Snapshot carries only relative skill deadlines; no learned purchase/MP
   // mutation is part of neutral interruption, nor an unearned CD reset.
   check(w.player.mp==normalMp&&w.skillState().snapshot(w.nowMs()).at("skills")==learned.at("skills"),
    "Neutral ACT interruption preserves accepted MP and normal learning/CD ledger: "+std::to_string(job));
   if(cooldownKey)check(w.experimentalRuntime()->remainingCooldown(*cooldownKey,w.nowMs())>0&&
      w.nowMs()+w.experimentalRuntime()->remainingCooldown(*cooldownKey,w.nowMs())==cooldownDeadline,
    "Typed source-bound nonzero diagnostic runtime cooldown retains its absolute deadline through neutral reaction: "+std::to_string(job));
   const auto queue=w.simulationCheckpoint().at("inputs");
   check(queue.at("sequences")==inputSequence&&queue.at("pending").size()==1&&!queue.at("pending")[0].at("payload").at("down").get<bool>(),
    "Prepared queue removes future action DOWN, retains KEYUP and exact sequence watermark: "+std::to_string(job));
   check(f.host.cancelAll("reaction_resume_check").ok,"Accepted source ACT closes without replay before recovery check");
   const auto start=w.player.x;w.enqueue({w.simulationNanoseconds(),1,true});f.ticks(55);
   check(!w.player.dead&&w.player.x>start&&w.player.animation=="move",
    "Normal physical movement resumes after actual hit pause/hard stun without replacement input: "+std::to_string(job));
   w.enqueue({w.simulationNanoseconds(),1,false});f.ticks(2);const auto stopped=w.player.x;f.ticks(8);
   check(w.player.x==stopped&&w.player.animation=="stay","Preserved KEYUP stops restored movement normally: "+std::to_string(job));
   out["samples"]["prepared_job_"+std::to_string(job)]=receipt;
  }
  // Pickup is an owned nonattacking pose. Source ACT contact must replace it
  // only when the complete damage/reaction transaction is accepted.
  for(const int job:{0,1,2,3,4,5,8})for(const bool fault:{false,true}) {
   CollisionFixture f(pvf,assets,catalog,50,1,1,job);auto &w=f.world;f.bind(pvf);
   if(fault) {
    auto &instance=f.host.state_.instances.at(40);auto program=std::make_shared<ActProgram>(*instance.program);
    ActBehavior behavior;behavior.source=program->source;behavior.instructions.push_back({program->source,ActSpawn{}});
    const auto index=program->behaviors.size();program->behaviors.push_back(behavior);
    ActTrigger trigger;trigger.source=program->source;trigger.event=ActEventKind::AttackSuccess;
    ActBehaviorCall call;call.behavior=index;call.source=program->source;trigger.calls.push_back(call);program->triggers.push_back(trigger);
    instance.triggers.resize(program->triggers.size());instance.program=program;
   }
   bool pickupObserved=false;
   f.beforeContact=[&](World &world) {
    if(!world.pickupActionActive())check(world.tryPickupAction(),"Own-source pickup can prepare before ACT contact: "+std::to_string(job));
    pickupObserved|=world.pickupActionActive();
   };
   const auto hp=w.player.hp,mp=w.player.mp;const auto rng=w.randomStreams().snapshot();
   for(int i=0;i<180&&!f.hits()&&f.host.instances().at(40).status==ActInstanceStatus::Running;++i)f.ticks(1);
   check(pickupObserved&&(fault?
      (f.hits()==0&&f.host.instances().at(40).status==ActInstanceStatus::Faulted&&w.pickupActionActive()&&
       w.player.hp==hp&&w.player.mp==mp&&w.randomStreams().snapshot()==rng&&w.player.animation=="getitem"):
      (f.hits()==1&&!w.pickupActionActive()&&w.player.hp<hp&&w.player.mp==mp&&w.player.animation=="damage1")),
      std::string(fault?"Rejected ACT leaves the live pickup pose/HP/MP/RNG intact: ":
       "Accepted ACT replaces pickup with own damage pose in the same commit: ")+std::to_string(job));
  }
  // Diagnostic setup uses actual source SKL commands and the actual staged
  // female service, without claiming a complete release/cast qualification.
  const auto sourceBuff=[&](World &w,int skill) {
   if(!w.femaleGunnerWorld_)w.femaleGunnerWorld_=std::make_unique<FemaleGunnerWorld>(w);
   const auto &plan=w.experimentalRuntime()->plan();
   auto command=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,skill}),*plan.skills.at({5,skill}).data,1,0);
   command.actionSequence=1;command.pulseId=1;
   ExperimentalActorState actor;actor.x=w.player.x;actor.y=w.player.y;actor.direction=w.player.dir;actor.mp=w.player.mp;
   w.femaleGunnerWorld_->publish(w.femaleGunnerWorld_->prepare({command},actor,0));
   return command;
  };
  {
   CollisionFixture f(pvf,assets,catalog,50,1,1,5);auto &w=f.world;
   const auto command=sourceBuff(w,43);const auto buffs=w.femaleGunnerDiagnostics();
   const auto policy=DamageResolutionPolicy::inferredPveDamageV1(w.combatAttributes_->damageConstants);
   DamageRequest request;request.attacker=w.monsters[0].handle;request.target=w.player.handle;request.attackInstance=1;
   request.attackerStats=makeDamageCombatant(*w.monsters[0].combatAttributes,policy);
   request.targetStats=makeDamageCombatant(*w.combatAttributes_);request.attack=attack.damage;
   auto expected=request;w.femaleGunnerWorld_->applyDefense(expected);
   auto prepared=w.preparePlayerDefense(request);
   check(!prepared.immune&&prepared.request.targetStats.snapshot()==expected.targetStats.snapshot()&&
      prepared.request.skill.snapshot()==expected.skill.snapshot()&&w.femaleGunnerDiagnostics()==buffs&&
      (expected.targetStats.physicalDefense!=request.targetStats.physicalDefense||expected.targetStats.evasionPercent!=request.targetStats.evasionPercent||expected.skill.totalMultiplier!=request.skill.totalMultiplier),
    "Actual source43 defensive modifiers prepare privately and consume nonzero source operands");
   f.bind(pvf);for(int i=0;i<180&&f.host.instances().at(40).status==ActInstanceStatus::Running&&!f.hits();++i)f.ticks(1);
   const auto receipt=w.statReport().at("last_damage");
   out["samples"]["female_defense"]={{"source_command",command.skillSource.json()},{"receipt",receipt},{"observed",f.observed()}};
   check(receipt.contains("player_defense")&&receipt.at("sources").at("target")==expected.targetStats.snapshot()&&
      receipt.at("sources").at("skill")==expected.skill.snapshot(),
    "Actual ACT contact resolves with the privately prepared female source-defense operands");
   auto death=w.femaleGunnerWorld_->prepareNeutralDeath();
   check(!death->snapshot().at("buffs").size()&&w.femaleGunnerDiagnostics().at("buffs").size()==1,
    "Neutral female death preparation retires buffs only on a private service candidate");
  }
  {
   CollisionFixture f(pvf,assets,catalog,50,1,1,5);auto &w=f.world;sourceBuff(w,190);
   const auto hp=w.player.hp,mp=w.player.mp;const auto rng=w.randomStreams().snapshot();
   f.bind(pvf);
   // Source190 lasts longer than this actual attack; no random defense roll
   // or contact acceptance may run while its actual immunity consumer holds.
   f.ticks(35);
   out["samples"]["female_quickstanding"]={{"observed",f.observed()},{"diagnostics",f.host.diagnostics()},{"service",w.femaleGunnerDiagnostics()}};
   bool noAccepted=true;for(const auto &[id,collision]:f.host.collisions())noAccepted&=collision.acceptedTargets.empty();
   check(w.femaleGunnerWorld_->invulnerable()&&f.hits()==0&&w.player.hp==hp&&w.player.mp==mp&&w.randomStreams().snapshot()==rng&&noAccepted&&
      f.host.diagnostics().dump().find("act_player_source_quick_standing_immunity")!=std::string::npos,
    "Actual source190 immunity rejects actual ACT HP/MP/RNG/contact before combat publication");
  }
  {
   CollisionFixture f(pvf,assets,catalog,50,1,1,5);auto &w=f.world;sourceBuff(w,43);w.player.hp=1;f.bind(pvf);
   // A different fixed diagnostic seed exercises successful impact despite
   // actual camouflage evasion; the previous test retained its real MISS.
   w.randomStreams()=RandomStreams(123);
   for(int i=0;i<180&&!f.hits();++i)f.ticks(1);
   check(f.hits()==1&&w.player.dead&&w.femaleGunnerDiagnostics().at("buffs").empty()&&
      w.statReport().at("last_damage").at("player_reaction").contains("female_buff_death_cleanup"),
    "Lethal ACT contact publishes prepared female buff retirement with player death in the same commit");
  }
  {
   CollisionFixture f(pvf,assets,catalog,50,1,1,1);auto &w=f.world;f.ticks(1);
   // Enter through the real command/controller path so its physical key owner
   // can later deliver the corresponding KEYUP to the prepared runtime.
   w.enqueue({w.simulationNanoseconds(),1,true});f.ticks(1);
   Effect attached;attached.id=9001;attached.attached=true;attached.expires=INT64_MAX;attached.animation=w.actorAni();
   Effect child=attached;child.id=9002;child.attached=false;child.alsParentId=9001;
   Effect unrelated=child;unrelated.id=9003;unrelated.alsParentId=-1;
   w.effects={attached,child,unrelated};w.pendingEffects_={child};
   const auto before=w.experimentalDiagnostics(),random=w.randomStreams().snapshot();
   auto prepared=w.prepareNeutralPlayerReaction(w.player);
   check(w.effects.size()==3&&w.pendingEffects_.size()==1&&w.experimentalDiagnostics()==before&&w.randomStreams().snapshot()==random,
    "Reaction preparation allocates privately without publishing runtime/effects/RNG");
   check(prepared.effects.size()==1&&prepared.effects[0].id==9003&&prepared.pendingEffects.empty(),
    "Private attached effect graph retires owned ALS descendants and preserves unrelated detached effects");
   w.publishNeutralPlayerReaction(prepared);const auto x=w.player.x;f.ticks(2);
   check(w.player.x>x,"Publishing prepared neutral runtime preserves pre-existing movement ownership");
   w.enqueue({w.simulationNanoseconds(),1,false});f.ticks(2);const auto x2=w.player.x;f.ticks(2);
   check(w.player.x==x2,"Normal KEYUP releases movement retained through prepared runtime cancellation");
  }
  for(const int kind:{0,1}) {
   CollisionFixture f(pvf,assets,catalog,50,1,1,3);auto &w=f.world;f.ticks(1);
   const auto hp=w.player.hp,mp=w.player.mp;const auto random=w.randomStreams().snapshot();
   const auto state=w.skillState().snapshot(w.nowMs());f.bind(pvf);
   if(kind==0) {
    // Deliberate isolated CHR source-view corruption, never a PVF edit. The
    // required down resource is now missing even for a nonlethal reaction.
    auto &definition=const_cast<CharacterDefinition&>(w.characterSource());
    for(auto &resource:definition.resources)if(resource.tag=="[down motion]")resource.path="missing/diagnostic-player-down.ani";
   } else {
    // Inject after the normal experimental adapter has published its frame,
    // immediately before the actual host contact consumer reads that frame.
    f.beforeContact=[](World &world){world.player.animationClock=ani_clock::Snapshot{};
     world.player.animationClock->frame=SIZE_MAX;world.player.animationClockSource=world.actorAni();};
   }
   for(int i=0;i<100&&f.host.instances().at(40).status==ActInstanceStatus::Running;++i)f.ticks(1);
   check(f.host.instances().at(40).status==ActInstanceStatus::Faulted&&f.hits()==0&&w.player.hp==hp&&w.player.mp==mp&&
    w.randomStreams().snapshot()==random&&w.skillState().snapshot(w.nowMs()).at("skills")==state.at("skills"),
    "Diagnostic reaction-resource/current-frame fault rejects HP/status/RNG/MP/CD/contact together: "+std::to_string(kind));
  }
  for(const bool lethal:{false,true}) {
   CollisionFixture f(pvf,assets,catalog,50,1,1,3);auto &w=f.world;
   StatusRequest status;status.attacker=w.monsters[0].handle;status.attackerLevel=1;status.target.handle=w.player.handle;
   status.target.resistance=evaluateCharacterStatusResistances(w.combatAttributes_->pureChr,w.characterSource(),
      w.combatAttributes_->equipmentSources,w.combatAttributes_->qualificationLevel);
   status.attack=readAttackStatuses(pvf.script("monster/tau/attackinfo/heading.atk"));
   status.attackInstance=w.ids_.attacks.next();bool installed=false;
   // Diagnostic prerequisite: select an isolated fixture stream which accepts
   // the unchanged actual source30%/1000ms stun. No combat RNG reroll occurs.
   for(int seed=1;seed<64&&!installed;++seed) {
    auto candidate=w.statuses_;Pcg32 diagnosticRandom(seed,13);auto prepared=candidate.prepare(status,uint64_t(w.nowMs()),diagnosticRandom);
    if(!prepared.ready())throw std::runtime_error("Actual status prerequisite is unusable: "+prepared.receipt.dump());
    candidate.publish(std::move(prepared),diagnosticRandom);
    if(candidate.stunned(w.player.handle,uint64_t(w.nowMs()))){w.statuses_=std::move(candidate);installed=true;}
   }
   check(installed,"Diagnostic source Tau status prerequisite retains authored30%/1000ms and uses an isolated RNG stream");
   const auto *before=w.statuses_.instance(w.player.handle,uint64_t(w.nowMs()));const auto statusId=before->id,expires=before->expiresMs;
   w.player.hp=lethal?1:w.player.hp;w.randomStreams()=RandomStreams(123);f.bind(pvf);
   for(int i=0;i<60&&!f.hits();++i)f.ticks(1);
   out["samples"][lethal?"lethal_status":"nonlethal_status"]={{"observed",f.observed()},{"diagnostics",f.host.diagnostics()},
      {"statuses",w.statuses_.snapshot(uint64_t(w.nowMs()),generation)}};
   const auto *after=w.statuses_.instance(w.player.handle,uint64_t(w.nowMs()));
   check(f.hits()==1&&(lethal?(w.player.dead&&!after):(!w.player.dead&&after&&after->id==statusId&&after->expiresMs==expires)),
    lethal?"Actual experimental lethal ACT clears pre-existing source status in the same death commit":
      "Actual experimental nonlethal ACT retains existing source status identity/deadline without refresh or reroll");
  }
  for(const bool fault:{false,true}) {
   CollisionFixture f(pvf,assets,catalog,50,1,1,8);auto &w=f.world;
   // Explicit cross-source diagnostic fixture: wooden-doll ACT geometry and
   // source attributes consume an unchanged current-PVF Queen Rosi ATK with
   // actual100% stun. This does not claim an authored doll/Queen pairing.
   const std::string statusAttack="monster/newmonsters/queen_rosi/attackinfo/attack1.atk";
   const auto actual=readActCollisionAttack(pvf.script(statusAttack));
   check(actual.sourceReady&&actual.reactionReady&&readAttackStatuses(actual.original).entries.at(0).chancePercent==100,
    "Diagnostic cross-source ACT status test selects unchanged actual100% source stun and retains its SourceRefs");
   w.player.hp=w.player.maxHp=1000000;f.bind(pvf);f.host.state_.collisions.at(40).currentAttack=statusAttack;
   if(fault) {
    auto &instance=f.host.state_.instances.at(40);auto program=std::make_shared<ActProgram>(*instance.program);
    ActBehavior behavior;behavior.source=program->source;behavior.instructions.push_back({program->source,ActSpawn{}});
    const auto index=program->behaviors.size();program->behaviors.push_back(behavior);
    ActTrigger trigger;trigger.source=program->source;trigger.event=ActEventKind::AttackSuccess;
    ActBehaviorCall call;call.behavior=index;call.source=program->source;trigger.calls.push_back(call);program->triggers.push_back(trigger);
    instance.triggers.resize(program->triggers.size());instance.program=program;
   }
   w.enqueue({w.simulationNanoseconds()+20000000000LL,20,true});
   const auto hp=w.player.hp,mp=w.player.mp;const auto rng=w.randomStreams().snapshot();const auto queue=w.simulationCheckpoint().at("inputs");
   const auto statusIds=w.statuses_.instanceWatermark();
   for(int i=0;i<100&&f.host.instances().at(40).status==ActInstanceStatus::Running&&!f.hits();++i)f.ticks(1);
   out["samples"][fault?"cross_source_status_fault":"cross_source_status_accepted"]={{"fixture","explicit diagnostic cross-source pairing"},
      {"observed",f.observed()},{"statuses",w.statuses_.snapshot(uint64_t(w.nowMs()),generation)},{"diagnostics",f.host.diagnostics()}};
   check(fault?(f.host.instances().at(40).status==ActInstanceStatus::Faulted&&f.hits()==0&&w.player.hp==hp&&w.player.mp==mp&&
      w.randomStreams().snapshot()==rng&&w.simulationCheckpoint().at("inputs")==queue&&
      !w.statuses_.stunned(w.player.handle,uint64_t(w.nowMs()))&&w.statuses_.instanceWatermark()==statusIds):
      (f.hits()==1&&w.player.hp<hp&&w.statuses_.stunned(w.player.handle,uint64_t(w.nowMs()))&&
       w.statReport().at("last_damage").contains("player_reaction")),
    fault?"Post-contact fault discards actual source stun/IDs with prepared experimental reaction, HP/MP/RNG/queue":
      "Actual source stun, HP and prepared experimental reaction publish in one accepted ACT contact");
  }
  {
   CollisionFixture f(pvf,assets,catalog,50,1,1,8);auto &w=f.world;f.bind(pvf);
   auto &instance=f.host.state_.instances.at(40);auto program=std::make_shared<ActProgram>(*instance.program);
   ActBehavior behavior;behavior.source=program->source;behavior.instructions.push_back({program->source,ActSpawn{}});
   const auto index=program->behaviors.size();program->behaviors.push_back(behavior);
   ActTrigger trigger;trigger.source=program->source;trigger.event=ActEventKind::AttackSuccess;
   ActBehaviorCall call;call.behavior=index;call.source=program->source;trigger.calls.push_back(call);program->triggers.push_back(trigger);
   instance.triggers.resize(program->triggers.size());instance.program=program;
   w.enqueue({w.simulationNanoseconds()+20000000000LL,20,true});const auto queue=w.simulationCheckpoint().at("inputs");
   const auto hp=w.player.hp,mp=w.player.mp;const auto rng=w.randomStreams().snapshot();
   for(int i=0;i<120&&f.host.instances().at(40).status==ActInstanceStatus::Running;++i)f.ticks(1);
   check(f.host.instances().at(40).status==ActInstanceStatus::Faulted&&f.hits()==0&&w.player.hp==hp&&w.player.mp==mp&&
    w.randomStreams().snapshot()==rng&&w.simulationCheckpoint().at("inputs")==queue&&w.player.animation!="damage1",
    "Post-contact diagnostic AttackSuccess fault discards experimental reaction/controller/queue with HP/status/RNG/ledger");
  }
  for(const int job:{0,1,2,3,4,5,8}) {
   CollisionFixture f(pvf,assets,catalog,50,1,1,job);auto &w=f.world;w.player.hp=1;f.bind(pvf);
   for(int i=0;i<120&&!f.hits();++i)f.ticks(1);
   check(f.hits()==1&&w.player.dead&&w.player.hp==0&&w.player.life==ActorLife::Dying&&w.player.animation=="down"&&
    w.player.animationPath==w.characterSource().motion("[down motion]")&&!w.player.hitStopped,
    "Seven-job lethal ACT publishes exact job down pose/lifecycle/status cleanup atomically: "+std::to_string(job));
  }
  for(const int job:{1,2,3,4,5,8}) {
   CollisionFixture f(pvf,assets,catalog,50,1,1,job);auto &w=f.world;f.bind(pvf);
   DebugOverrides overrides;overrides.enabled=true;overrides.hpLock=true;w.applyDebugOverrides(overrides,1);
   const auto hp=w.player.hp;for(int i=0;i<180&&!f.hits();++i)f.ticks(1);
   check(f.hits()==1&&w.player.hp==hp&&w.player.animation=="damage1"&&w.statReport().at("last_damage").contains("player_reaction"),
    "Experimental HP lock preserves actual source reaction and damage receipt: "+std::to_string(job));
   // Remove source hit stop to isolate the already published protection
   // deadline; this is an explicit diagnostic reset, not new combat logic.
   check(f.host.cancelAll("protection diagnostic").ok,"Protection test closes first accepted attack");
   w.player.hitStopTicks=0;w.player.hitStopped=false;w.monsters[0].hitStopTicks=0;w.monsters[0].hitStopped=false;
   const auto random=w.randomStreams().snapshot();const auto hits=f.hits();w.guardUntil_=w.nowMs()+300;
   f.bind(pvf,41);f.ticks(10);
   check(f.hits()==hits&&w.player.hp==hp&&w.randomStreams().snapshot()==random,
    "Experimental published player protection blocks duplicate ACT HP and RNG: "+std::to_string(job));
  }
  {
   CollisionFixture f(pvf,assets,catalog);
   // This additional saved legacy-HP target isolates already-supported player
   // accepted-hit/window publication from the real source-stat ACT attacker.
   // It does not claim Botti's still-gated source combat attributes are usable.
   Actor target;target.id=2;target.sourceId=56503;target.monsterPath="monster/act8/botticelli/botticelli.mob";
   target.x=target.px=630;target.y=target.py=344;target.dir=-1;target.hp=target.maxHp=1000000;
   f.world.monsters.push_back(target);f.world.synchronizeEntityHandles();const auto targetOwner=f.world.monsters[1].handle;
   f.world.configureSourceActions("collision-window:"+sha256(assets.staticBytes("audio.xml")));
   check(f.world.configureMonsterEventAi(targetOwner,"easy",MonsterEventAiPolicy::inferredIntegralChanceV1()),
    "Integration installs the actual Botti source interval/query beside a source-stat wooden doll ACT attacker without unblocking its combat gate");
   f.world.player.dir=1;f.world.normalAttack();
   for(int i=0;i<180&&f.world.monsterEventAiState().at("pending").empty();++i)f.ticks(1);
   const auto accepted=f.world.monsterEventAiState();const auto targetHp=f.world.monsters[1].hp;
   check(accepted.at("pending").size()==1&&accepted.at("pending")[0].at("actual_hp_loss")==1000000-targetHp&&
    accepted.at("damage_windows")[0].at("window").at("samples").size()==1,
    "Existing real player normal contact publishes precise HP loss and pending before the ACT host is bound");
   f.world.idle();f.world.releaseInputs();f.world.player.x=f.world.player.px=550;f.world.player.y=f.world.player.py=344;
   const auto playerHp=f.world.player.hp;f.bind(pvf);
   for(int i=0;i<180&&!f.hits();++i)f.ticks(1);
   check(f.hits()==1&&f.world.player.hp<playerHp&&f.world.monsters[1].hp==targetHp&&f.world.monsterEventAiState()==accepted,
    "Actual source ACT collision commits player HP/RNG/ledger while preserving every unrelated monster window/pending receipt and does not mislabel monster attack as player damage");
   const auto random=f.world.randomStreams().snapshot(),windows=f.world.monsterEventAiState();
   const auto hostSaved=f.host.snapshot(generation);
   check(f.host.restore(hostSaved,generation).ok&&f.world.randomStreams().snapshot()==random&&f.world.monsterEventAiState()==windows,
    "Same-generation collision host restore neither clears nor reissues the existing accepted monster window event");
   check(f.host.cancelAll("integration_room_restore").ok,"Integration retires the external diagnostic ACT before room restoration");
   Json actorRows=Json::array();std::vector<Actor> restored;
   for(const auto &actor:f.world.monsters) {
    auto saved=saveActor(actor,f.world.nowMs());const auto event=f.world.monsterEventActorCheckpoint(actor.handle,generation);
    if(!event.is_null())saved["monster_event_ai_state"]=event;
    actorRows.push_back(saved);restored.push_back(loadActor(saved,f.world.nowMs()));
   }
   f.world.restoreRoomActors(std::move(restored),actorRows);const auto pending=f.world.monsterEventAiState().at("pending");
   check(pending.size()==1&&pending[0].at("event_id")==accepted.at("pending")[0].at("event_id")&&
    f.world.monsters[1].hp==targetHp&&f.world.randomStreams().snapshot()==random,
    "Merged collision/window room restore remaps the pending owner once with exact HP/event/random state and no contact replay");
   f.world.freezeAi=false;for(int i=0;i<360&&!f.world.monsterEventAiState().at("pending").empty();++i)f.ticks(1);
   check(f.world.monsterEventAiState().at("pending").empty()&&f.world.monsters[1].hp==targetHp,
    "Merged restored pending reaches its authored threshold-false terminal branch without reapplying accepted damage");
   out["samples"]["collision_preserves_window_pending"]={{"before",accepted},{"after",f.world.monsterEventAiState()}};
  }
  {
   CollisionFixture f(pvf,assets,catalog,50,1,65);const int hp=f.world.player.hp;f.bind(pvf);
   for(int i=0;i<120&&!f.world.statReport().at("last_damage").contains("act_collision");++i)f.ticks(1);
   const auto receipt=f.world.statReport().at("last_damage");
   check(receipt.at("usable")==true&&receipt.contains("act_collision")&&
     receipt.at("sources").at("attacker").at("attack_miss_delta_percent").get<float>()==sourceLevel.attributes->tableAttackMissDeltaPercent,
     "Source-level65 actual ACT contact consumes the precise frozen raw11 attacker term");
   check(f.world.player.hp==std::max(0,hp-receipt.at("hp_damage").get<int>()),
     "Source-level65 ACT publishes exactly the accepted source damage or MISS to live HP");
   out["samples"]["source_level65_contact"]=f.observed();
  }
  check(attack.original.tokens==pvf.script(route.attackInfoResolvedPath).tokens,"Collision definition retains exact ordered source tokens and bytes");
  for(int direction:{1,-1}) {
   CollisionFixture f(pvf,assets,catalog,50,direction);const int hp=f.world.player.hp;f.bind(pvf);
   for(int i=0;i<120&&!f.hits();++i)f.ticks(1);
   out["samples"][direction==1?"forward":"reverse"]=f.observed();
   check(f.hits()==1,"Actual source attack boxes hit the hostile CHR hurt boxes in the owner facing direction");
   const auto receipt=f.world.statReport().at("last_damage");
   check(receipt.at("usable")==true&&receipt.contains("act_collision")&&receipt.at("sources").at("attack").at("source").at("path")==route.attackInfoResolvedPath,
    "Accepted real contact publishes the source ATK unified damage trace");
   check(f.world.player.hp==hp-receipt.at("hp_damage").get<int>(),"Live player HP consumes exactly the prepared damage rather than demonstration five/fourteen damage");
   check(f.world.player.animation=="damage1"&&f.world.player.hitStopped,"Neutral player publishes source reaction animation and authored hit pause");
   const auto saved=f.host.snapshot(generation);const auto rng=f.world.randomStreams().snapshot();
   check(f.host.restore(saved,generation).ok&&f.world.randomStreams().snapshot()==rng,"Same-generation host continuation validates without rerolling combat RNG");
   const auto stable=f.observed();
   for(int kind=0;kind<6;++kind) {
    auto bad=saved;
    if(kind==0)bad["collisions"]=Json::array();
    if(kind==1)bad.erase("collisions");
    if(kind==2)bad["collisions"][0]["current_attack"]="character/swordman/attackinfo/attack1.atk";
    if(kind==3)bad["collision_player_guard_until"]=0;
    if(kind==4)bad["collision_random_receipt"]=Json::object();
    if(kind==5)bad["collisions"][0]["accepted_targets"][0]["receipt"]["damage"]["attack_instance"]=999999;
    check(!f.host.restore(bad,generation).ok&&f.observed()==stable,"Malformed source/ledger/RNG/protection continuation rejects without publishing world state");
   }
   {
    const auto graph=f.host.liveGraph(generation);auto player=graph.player;auto monsters=graph.monsters;
    auto entities=graph.entities;entities.retireAll();std::map<EntityHandle,EntityHandle> mapping;
    for(const auto old:graph.entities.active())mapping.emplace(old,entities.create());
    player.handle=mapping.at(player.handle);for(auto &a:monsters)a.handle=mapping.at(a.handle);
    auto status=graph.statusReceipt;
    for(auto &active:status.at("active"))active["target"]=mapping.at(EntityHandle::fromJson(active.at("target"))).json();
    for(auto &contact:status.at("contacts"))contact["identity"]["target"]=mapping.at(EntityHandle::fromJson(contact.at("identity").at("target"))).json();
    StatusHost statuses(pvf.identity(),StunStatusPolicy::inferredFlatChanceStunV1());
    statuses.restore(status,uint64_t(f.world.nowMs()),generation,[&](const std::string &path){return pvf.script(path);},[&](EntityHandle h){return entities.valid(h);});
    ActWorldRestoreGraph remapped{player,monsters,entities,graph.worldIds,statuses.snapshot(uint64_t(f.world.nowMs()),generation),
      graph.tick,graph.characterLevel,graph.combatRandom,graph.playerGuardUntil};
    const auto prepared=f.host.prepareRemappedRestore(saved,generation,graph,remapped,mapping);
    out["samples"]["remap_error"]=prepared.error;
    check(prepared.ready()&&f.observed()==stable,"Typed fresh-generation contact remap prepares without changing the live World, RNG or HP");
    const auto &row=prepared.snapshot().at("collisions")[0].at("accepted_targets")[0];
    check(row.at("target")==player.handle.json()&&row.at("receipt").at("target")==player.handle.json()&&
      row.at("receipt").at("damage")==saved.at("collisions")[0].at("accepted_targets")[0].at("receipt").at("damage"),
      "Collision remap updates both typed target fields while frozen damage handles and outcomes remain historical evidence");
   }
   f.ticks(100);check(f.hits()==1,"Overlapping root frames and hit-stop cannot repeat a target within one source attack instance");
   check(f.host.collisions().empty(),"Source animation completion retires owned collision state");
  }
  for(int kind=0;kind<3;++kind) {
   CollisionFixture f(pvf,assets,catalog,kind==0?500:50);f.bind(pvf);
   if(kind==1)f.world.player.y+=150;if(kind==2)f.world.monsters[0].z=300;
   const auto hp=f.world.player.hp;const auto random=f.world.randomStreams().snapshot();f.ticks(120);
   check(f.hits()==0&&f.world.player.hp==hp&&f.world.randomStreams().snapshot()==random,"Separated X/Y/Z source geometry produces no HP, RNG or accepted contact");
  }
  {
   CollisionFixture f(pvf,assets,catalog);f.bind(pvf);DebugOverrides overrides;overrides.enabled=true;overrides.hpLock=true;
   f.world.applyDebugOverrides(overrides,1);const int hp=f.world.player.hp;
   for(int i=0;i<120&&!f.hits();++i)f.ticks(1);
   check(f.hits()==1&&f.world.player.hp==hp,"Debug HP lock preserves HP while source contact/reaction and damage receipt remain real");
  }
  {
   CollisionFixture f(pvf,assets,catalog);f.bind(pvf);f.world.player.hp=1;
   for(int i=0;i<120&&!f.hits();++i)f.ticks(1);
   check(f.hits()==1&&f.world.player.hp==0&&f.world.player.dead&&f.world.player.life==ActorLife::Dying,"Actual lethal source damage publishes player death and clears protection");
  }
  {
   CollisionFixture f(pvf,assets,catalog);f.bind(pvf);const auto hp=f.world.player.hp;const auto random=f.world.randomStreams().snapshot();
   f.world.player.dir=1;f.world.normalAttack();f.ticks(12);
   out["samples"]["active_basic_gate"]=f.observed();
   check(f.hits()==0&&f.world.player.hp==hp&&f.world.randomStreams().snapshot()==random&&
    f.host.diagnostics().dump().find("act_player_prepared_action_interruption_consumer_missing")!=std::string::npos,
    "Active basic attack blocks incomplete prepared player interruption before HP/RNG/contact acceptance");
  }
  {
   CollisionFixture f(pvf,assets,catalog);f.bind(pvf);for(int i=0;i<120&&!f.hits();++i)f.ticks(1);
   check(f.hits()==1&&!f.host.collisions().at(40).acceptedTargets.empty(),"Diagnostic command-consumer fixture begins with one actual accepted source contact");
   const auto issue=[&](ActCommandPayload payload) {
    // Explicit test-only program injection. The unmodified source route and
    // contact above are real; these events test the same private command
    // transaction without claiming this simple source authored the commands.
    auto &instance=f.host.state_.instances.at(40);auto program=std::make_shared<ActProgram>(*instance.program);
    ActBehavior behavior;behavior.source=program->source;behavior.instructions.push_back({program->source,std::move(payload)});
    const auto index=program->behaviors.size();program->behaviors.push_back(std::move(behavior));
    ActTrigger trigger;trigger.source=program->source;trigger.event=ActEventKind::Damage;
    ActBehaviorCall call;call.behavior=index;call.source=program->source;trigger.calls.push_back(call);program->triggers.push_back(trigger);
    // Runtime trigger state is source-shaped; newly injected triggers need
    // explicit state, rather than indexing beyond an original instance.
    instance.triggers.resize(program->triggers.size());instance.program=program;
    ActEventContext event;event.eventId=f.world.idSources().events.next();event.kind=ActEventKind::Damage;
    event.subject=instance.owner;event.other=f.world.player.handle;
    const auto result=f.host.dispatch(40,event);if(!result.ok)throw std::runtime_error(result.error);
   };
   issue(ActAttackRect{ActAttackRectMode::Off});
   check(!f.host.collisions().at(40).enabled&&f.host.collisions().at(40).acceptedTargets.size()==1,
    "Actual ATTACKRECT OFF command consumer disables collision while preserving accepted-target receipt");
   issue(ActAttackRect{ActAttackRectMode::On});
   check(f.host.collisions().at(40).enabled&&f.host.collisions().at(40).acceptedTargets.size()==1,
    "Actual ATTACKRECT ON does not silently reset a prior accepted target");
   issue(ActAttackRect{ActAttackRectMode::Reset});
   check(f.host.collisions().at(40).hitIndex==1&&f.host.collisions().at(40).acceptedTargets.empty(),
    "Actual ATTACKRECT RESET advances hit-cycle identity and clears its target ledger in one host commit");
   issue(ActChangeAttackInfo{"character/swordman/attackinfo/attack1.atk",false});
   check(f.host.collisions().at(40).currentAttack=="character/swordman/attackinfo/attack1.atk"&&f.host.collisions().at(40).hitIndex==1,
    "CHANGE ATTACKINFO resolves the exact current source path without implicitly starting another hit cycle");
   issue(ActChangeAttackInfo{"",true});
   check(f.host.collisions().at(40).currentAttack==route.attackInfoResolvedPath,
    "DEFAULT restores the originally verified MOB paired ATK rather than a guessed character attack");
  }
  {
   CollisionFixture f(pvf,assets,catalog);f.bind(pvf);f.host.state_.collisions.at(40).currentAttack="missing/test-fault.atk";
   const int hp=f.world.player.hp;const auto random=f.world.randomStreams().snapshot();f.ticks(1);
   check(f.host.instances().at(40).status==ActInstanceStatus::Faulted&&f.host.collisions().empty()&&f.world.player.hp==hp&&f.world.randomStreams().snapshot()==random,
    "Diagnostic missing-source fault discards private contact and publishes precise instance cleanup rather than poisoning World ticks");
   f.ticks(3);check(f.world.tick==4,"World simulation continues after isolated contact consumer fault");
  }
  {
   CollisionFixture f(pvf,assets,catalog);f.bind(pvf);
   auto &instance=f.host.state_.instances.at(40);auto program=std::make_shared<ActProgram>(*instance.program);
   ActBehavior behavior;behavior.source=program->source;
   // Explicit diagnostic sequence: window configure precedes the intentionally
   // unsupported spawn, so fault rollback must discard it with HP/RNG/events.
   behavior.instructions.push_back({program->source,ActSetDamageCheck{true,2000}});
   behavior.instructions.push_back({program->source,ActSpawn{}});
   const auto index=program->behaviors.size();program->behaviors.push_back(behavior);
   ActTrigger trigger;trigger.source=program->source;trigger.event=ActEventKind::AttackSuccess;
   ActBehaviorCall call;call.behavior=index;call.source=program->source;trigger.calls.push_back(call);program->triggers.push_back(trigger);
   instance.triggers.resize(program->triggers.size());instance.program=program;
   const int hp=f.world.player.hp;const auto random=f.world.randomStreams().snapshot();const auto windows=f.world.monsterEventAiState();f.ticks(12);
   check(f.host.instances().at(40).status==ActInstanceStatus::Faulted&&f.host.collisions().empty()&&
    f.hits()==0&&f.world.player.hp==hp&&f.world.randomStreams().snapshot()==random&&f.world.monsterEventAiState()==windows&&
    std::none_of(f.world.events.begin(),f.world.events.end(),[](const Event&e){return e.kind=="act_damage_check";}),
    "Diagnostic AttackSuccess failure after private damage/window preparation discards HP/status/RNG/ledger/events/window together and cleans ownership");
  }
  for(const int job:{0,3,5}) {
   Json reference;
   for(int fps:{30,60,144,240}) {
    CollisionFixture f(pvf,assets,catalog,50,1,1,job);f.bind(pvf);
    for(int frame=1;frame<=fps*2;++frame) {
     const auto target=int64_t(frame)*2000000000/(fps*2);const auto previous=int64_t(frame-1)*2000000000/(fps*2);
     f.world.advance(target-previous,size_t(3));
    }
    while(f.world.tick<120)f.world.advance(0,size_t(3));
    auto value=f.observed();value["experimental_runtime"]=f.world.experimentalDiagnostics();
    value["normal_skill_ledger"]=f.world.skillState().snapshot(f.world.nowMs());
    const auto &player=f.world.player;
    value["reaction_player"]={{"xyz",{player.x,player.y,player.z}},{"animation",player.animation},{"animation_path",player.animationPath},
      {"stun_until",player.stunUntil},{"hit_stop",player.hitStopTicks},{"hit_stopped",player.hitStopped},{"dead",player.dead},{"mp",player.mp}};
    if(reference.is_null())reference=value;
    check(value==reference,"Render FPS and bounded catch-up deliver identical 120-tick source damage, events, collision lifecycle and RNG for job "+std::to_string(job));
   }
  }
  out["status"]="passed";out["count"]=out["checks"].size();writeJson(root/"act-collision.json",out);return out;
 }catch(const std::exception&e){out["status"]="failed";out["error"]=e.what();writeJson(root/"act-collision-failed.json",out);
  writeJson(root/("act-collision-failed-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".json"),out);throw;}
}
}
