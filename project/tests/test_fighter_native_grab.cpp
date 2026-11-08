#include "dnf/collision.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/monster_effects.hpp"
#include "dnf/progression.hpp"
#include "dnf/character_attack.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <chrono>
#include <stdexcept>

namespace dnf {
namespace {
constexpr SkillKey suplex{1,9};
constexpr const char *grabbableMob="monster/goblin/goblin.mob";
constexpr const char *ungrabbableMob="monster/act8/chiefmong/chiefmong.mob";

void grabCheck(bool passed,const std::string &message) {
    if(!passed)throw std::runtime_error("40JP Fighter source grab: "+message);
}

void prepareWorld(World &world,RegionCatalog &regions) {
    world.enableExperimentalCharacters();
    // Use the same source starter/appearance transaction as a newly created
    // Fighter. Progression::initialize alone grants a legacy Swordman weapon.
    const auto directory=std::filesystem::path("cache/fighter-native-grab-runtime")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    CharacterStore store(directory,"40jp-fighter-grab-test");
    store.data={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    store.data["characters"][0]={{"name","NativeFighterGrab"},{"class","fighter"},
        {"identity",CharacterIdentity{1,0,0}.json()},{"level",1},{"weapon",0},{"skill_initialization","source-v1"}};
    Progression progression(regions);store.apply(0,world,progression);
    DebugOverrides debug;debug.enabled=true;
    world.applyDebugOverrides(debug,1);
    const auto preview=world.setExperimentalSkillPreviewEnabled(true);
    if(!preview.ok)throw std::runtime_error("Could not enter isolated Fighter test preview: "+preview.message);
    world.configureAnimationClock(ani_clock::ClockPolicy::SourceDelay100);
    auto &runtime=*world.experimentalRuntime();
    const auto &plan=runtime.plan();
    runtime.configuration().configureSourceSkillAction(suplex,1,plan);
    runtime.configuration().assignSlot(0,suplex,plan);
    world.combat=true;world.freezeAi=true;world.freeCd=true;
    world.mapWidth=3000;world.walkRects={{0,0,3000,1200}};world.blockedRects.clear();
    world.player.x=world.player.px=500;world.player.y=world.player.py=344;
    world.player.z=world.player.pz=world.player.vx=world.player.vy=world.player.vz=0;
    world.player.dir=1;world.player.dead=false;world.player.life=ActorLife::Alive;
    world.player.hp=world.player.maxHp;world.player.mp=world.player.maxMp;
    world.randomStreams()=RandomStreams(67);
}

Actor addMob(World &world,int id,const std::string &path) {
    Actor actor;actor.id=id;actor.sourceId=10;actor.monsterPath=path;
    actor.x=actor.px=700;actor.y=actor.py=344;actor.dir=-1;
    world.initializeMonsterAttributes(actor,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    actor.hp=actor.maxHp=100000000;actor.life=ActorLife::Alive;actor.dead=false;
    world.monsters.push_back(actor);world.synchronizeEntityHandles();
    return world.monsters.back();
}

void alignTrySourceBoxes(Pvf &pvf,Assets &assets,World &world,Actor &target) {
    const auto &descriptor=world.experimentalRuntime()->plan().sourceSkillActions.at(suplex);
    if(!descriptor.nativeGrab||descriptor.nativeStages.empty())throw std::runtime_error("Suplex source grab descriptor unavailable");
    const auto &stage=descriptor.nativeStages.at(descriptor.nativeGrab->tryStage);
    const auto source=readCharacterAttackMotion(assets,world.characterAppearance(),stage.motion.memberPath);
    if(!source.body)throw std::runtime_error("Suplex body source geometry unavailable");
    size_t overlaps=0,attackCount=0,hurtCount=0;double bestX=target.x,bestY=target.y,bestZ=0,bestVolume=-1;
    size_t bestHurtFrame=0;std::string bestState;std::shared_ptr<const MonsterMotion> bestVictim;
    for(size_t sourceFrame=0;sourceFrame<source.body->frames.size();++sourceFrame) {
        const auto attackBoxes=source.boxesAt(sourceFrame);
        for(const auto *state:{"stay","damage1","damage2","down","sit"}) {
          const auto victim=compileMonsterMotion(pvf,assets,target.monsterPath,state);
          if(!victim->valid())continue;
          for(size_t victimFrame=0;victimFrame<victim->base->frames.size();++victimFrame) {
            for(const auto &attack:attackBoxes)if(attack.type==15&&attack.w>0&&attack.h>0&&attack.d>0)
                for(const auto &hurt:victim->base->frames[victimFrame].boxes)if(hurt.type==14&&hurt.w>0&&hurt.h>0&&hurt.d>0) {
                    ++hurtCount; ++attackCount;
                    const auto a=combatBox(attack,world.player.x,world.player.y,world.player.z,world.player.dir);
                    const auto base=combatBox(hurt,0,0,0,-world.player.dir);
                    const double candidateX=a.x+a.w*.5-base.x-base.w*.5;
                    const double candidateY=a.y+a.h*.5-base.y-base.h*.5;
                    const double candidateZ=a.z+a.d*.5-base.z-base.d*.5;
                    const auto b=combatBox(hurt,candidateX,candidateY,candidateZ,-world.player.dir);
                    CombatBox overlap{};
                    if(intersectCombatBoxes(a,b,&overlap)) {
                        ++overlaps;const double volume=overlap.w*overlap.h*overlap.d;
                        if(volume>bestVolume){bestVolume=volume;bestX=candidateX;bestY=candidateY;bestZ=candidateZ;bestHurtFrame=victimFrame;bestState=state;bestVictim=victim;}
                    }
                }
          }
        }
    }
    if(!overlaps)throw std::runtime_error("Real source try type15 geometry has no overlap placement against target type14 geometry (pairs="+
        std::to_string(attackCount)+", hurt="+std::to_string(hurtCount)+", source="+stage.motion.memberPath+", target="+target.monsterPath+")");
    target.x=target.px=bestX;target.y=target.py=bestY;target.z=target.pz=bestZ;
    target.animation=bestState;target.animationPath=bestVictim->base->path;target.animStart=world.nowMs();
    ani_clock::Snapshot pose;pose.frame=bestHurtFrame;target.animationClock=pose;target.animationClockSource=target.animationPath;
    target.stunUntil=world.nowMs()+10000;
    target.handle=world.monsters.back().handle;
}

void castFromWorldInput(World &world) {
    world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
    world.enqueue({world.simulationNanoseconds(),20,false});world.advanceSingleTick();
}

bool acceptedGrabDiagnostic(const World &world,EntityHandle target) {
    const auto rows=world.experimentalDiagnostics().value("world",Json::array());
    return std::any_of(rows.begin(),rows.end(),[&](const Json &row){
        return row.value("code",std::string())=="source_fighter_grab_accepted"&&row.value("target",Json())==target.json();
    });
}

bool damageTraceTargets(const World &world,EntityHandle target) {
    const auto damage=world.statReport().value("last_damage",Json::object());
    return damage.is_object()&&damage.value("target",Json())==target.json();
}

bool captureWithSourceInput(Pvf &pvf,Assets &assets,World &world,Actor &target) {
    alignTrySourceBoxes(pvf,assets,world,target);castFromWorldInput(world);
    for(int tick=0;tick<40&&target.capturedBy<0;++tick)world.advanceSingleTick();
    return target.capturedBy==0&&world.experimentalRuntime()->sourceGrabState()&&
        world.experimentalRuntime()->sourceGrabState()->holding;
}
}

Json runFighterNativeGrabTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool passed,const std::string &message) {
        checks.push_back({{"passed",passed},{"message",message}});
        grabCheck(passed,message);
    };
    RegionCatalog regions(pvf,assets);
    const auto pvfIdentity=pvf.identity();
    check(pvfIdentity=="d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d",
        "Fixture is the fingerprinted 1031 source PVF");

    // The 40JP ShoulderTackleHit ANI is an accepted-contact effect, not an
    // action-start attachment. Exercise the real World contact consumer with
    // the current PVF ANI/ATK and an already-qualified overlap region.
    {
        constexpr SkillKey shoulderTackle{1,54};
        World cueWorld(pvf,assets,WorldRules::BetaFoundationV1);prepareWorld(cueWorld,regions);
        auto &runtime=*cueWorld.experimentalRuntime();const auto &plan=runtime.plan();
        const auto &action=plan.sourceSkillActions.at(shoulderTackle);
        const auto &stage=action.nativeStages.front();
        runtime.configuration().configureSourceSkillAction(shoulderTackle,1,plan);
        runtime.configuration().assignSlot(0,shoulderTackle,plan);
        addMob(cueWorld,80,grabbableMob);
        Actor &target=cueWorld.monsters.back();
        ExperimentalAttackFrame frame;frame.skill=shoulderTackle;frame.sourceFrame=2;frame.pulseId=1;
        frame.motion={stage.motionTag,size_t(std::max(0,stage.motionSlot)),0,stage.motion};
        frame.attack=ExperimentalSourceBinding{stage.attackTag,size_t(std::max(0,stage.attackSlot)),0,stage.attack};
        frame.contactEffects=stage.contactEffects;
        const CombatBox overlap{580,334,12,40,20,36};
        auto &adapter=*cueWorld.experimentalAdapter_;adapter.attackId_=1;
        const bool resolved=adapter.contact(target,frame,action.attackDefinition,&overlap);
        const bool missed=cueWorld.lastDamageTrace_.value("missed",false);
        std::vector<const Effect *> hitEffects;
        for(const auto &effect:cueWorld.effects)
            if(effect.phase=="source_skill_accepted_hit")hitEffects.push_back(&effect);
        check(resolved&&!missed&&hitEffects.size()==1,
            "Accepted 40JP ShoulderTackle contact publishes exactly one conditional hit ANI");
        check(hitEffects.front()->animation=="character/fighter/effect/animation/shouldertacklehit.ani"&&
              hitEffects.front()->x==overlap.x+overlap.w*.5&&hitEffects.front()->y==overlap.y+overlap.h*.5&&
              hitEffects.front()->z==overlap.z+overlap.d*.5&&hitEffects.front()->expires>cueWorld.nowMs(),
            "ShoulderTackleHit uses the accepted overlap center and the source ANI lifetime");
        evidence.push_back({{"case","shoulder_tackle_accepted_hit_effect"},{"damage_trace",cueWorld.lastDamageTrace_},
            {"effect",{{"animation",hitEffects.front()->animation},{"position",{hitEffects.front()->x,hitEffects.front()->y,hitEffects.front()->z}},
                {"expires",hitEffects.front()->expires}}}});
    }

    // Empty release traverses the input/controller/runtime path and the real
    // try ATK. It cannot become a damage contact without a qualifying victim.
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);prepareWorld(world,regions);
        const auto before=world.player.hp;castFromWorldInput(world);
        for(int tick=0;tick<100&&world.experimentalRuntime()->attacking();++tick)world.advanceSingleTick();
        check(!world.experimentalRuntime()->attacking()&&world.player.hp==before,
            "Empty Suplex consumes its real input/action and ends without a target capture or synthetic self/monster damage");
        evidence.push_back({{"case","empty_input_release"},{"world",world.experimentalDiagnostics()}});
    }

    World world(pvf,assets,WorldRules::BetaFoundationV1);prepareWorld(world,regions);
    world.monsters.reserve(2);
    auto target=addMob(world,1,grabbableMob);
    const auto targetHandle=target.handle;
    const int hpBeforeTry=world.monsters.front().hp;
    check(captureWithSourceInput(pvf,assets,world,world.monsters.front()),
        "Real Suplex try source frame overlaps the Goblin hurtbox and binds a live held target");
    const int hpAtCapture=world.monsters.front().hp;
    check(acceptedGrabDiagnostic(world,targetHandle)&&world.monsters.front().hp==hpBeforeTry&&hpAtCapture==hpBeforeTry&&
        world.experimentalRuntime()->sourceGrabState()->ownerAction!=0,
        "Try frame accepts the generation-qualified owner without applying damage");
    bool targetDamaged=false;
    for(int tick=0;tick<100&&!targetDamaged;++tick) {
        world.advanceSingleTick();
        targetDamaged=world.monsters.front().hp<hpAtCapture&&damageTraceTargets(world,targetHandle);
    }
    check(targetDamaged&&world.monsters.front().capturedBy<0,
        "40JP held-object frame callback resolves the real Suplex ATK against exactly the captured handle and releases it");
    evidence.push_back({{"case","accepted_direct_held_hit"},{"target",targetHandle.json()},
        {"damage_trace",world.lastDamageTrace_},{"events",world.eventLog()}});

    // MOB explicitly declares [is grabable] 0 in this 1031 PVF. Debug skill
    // freedom must not erase that authored target rule.
    world.changeScene();world.monsters.clear();world.synchronizeEntityHandles();world.player.dead=false;
    world.player.life=ActorLife::Alive;world.player.hp=world.player.maxHp;world.player.x=world.player.px=500;
    world.player.y=world.player.py=344;world.player.z=world.player.vz=0;
    addMob(world,2,ungrabbableMob);auto &ungrabbable=world.monsters.front();
    const auto hpBeforeReject=ungrabbable.hp;castFromWorldInput(world);
    const auto activeGrab=world.experimentalRuntime()->sourceGrabState();
    check(activeGrab&&!activeGrab->holding,"World input reaches the source try stage before target qualification");
    ExperimentalAttackFrame qualification;qualification.skill=suplex;qualification.sourceGrabOwner=activeGrab->ownerAction;
    qualification.sourceGrabTry=true;
    check(!world.experimentalAdapter_->trySourceGrab(ungrabbable,qualification,*world.experimentalRuntime())&&
        ungrabbable.capturedBy<0&&ungrabbable.hp==hpBeforeReject&&!acceptedGrabDiagnostic(world,ungrabbable.handle),
        "Current [is grabable] 0 MOB is rejected by the real source qualification gate even when a valid try-stage owner is presented");
    for(int tick=0;tick<40&&world.experimentalRuntime()->attacking();++tick)world.advanceSingleTick();
    check(ungrabbable.capturedBy<0&&ungrabbable.hp==hpBeforeReject&&!acceptedGrabDiagnostic(world,ungrabbable.handle),
        "World input never captures or damages the source ungrabbable MOB");
    evidence.push_back({{"case","source_ungrabbable"},{"mob",ungrabbableMob},{"handle",ungrabbable.handle.json()}});

    // A successful source capture must be retired by each real lifecycle
    // boundary. No helper injects a capture or bypasses source-frame overlap.
    world.changeScene();world.monsters.clear();world.synchronizeEntityHandles();world.player.dead=false;
    world.player.life=ActorLife::Alive;world.player.hp=world.player.maxHp;world.player.x=world.player.px=500;
    world.player.y=world.player.py=344;world.player.z=world.player.vz=0;
    addMob(world,3,grabbableMob);auto &cancelTarget=world.monsters.front();
    check(captureWithSourceInput(pvf,assets,world,cancelTarget),"World input reaches a real source capture before cancel test");
    world.idle();world.advanceSingleTick();
    check(cancelTarget.capturedBy<0&&!world.experimentalRuntime()->sourceGrabState(),
        "Explicit action cancel releases the held target and clears transient owner state");

    // Room/character entity IDs are renewed. Reusing the actor's visible ID
    // and source path cannot transfer an old capture to the replacement.
    world.idle();world.player.dead=false;world.player.life=ActorLife::Alive;world.player.hp=world.player.maxHp;
    world.player.x=world.player.px=500;world.player.y=world.player.py=344;world.player.z=world.player.vz=0;
    check(captureWithSourceInput(pvf,assets,world,cancelTarget),"A second actual source contact starts a new hold after cancellation");
    const auto oldHandle=world.monsters.front().handle;
    Actor replacement;replacement.id=cancelTarget.id;replacement.sourceId=cancelTarget.sourceId;replacement.monsterPath=grabbableMob;
    replacement.x=replacement.px=cancelTarget.x;replacement.y=replacement.py=cancelTarget.y;
    world.initializeMonsterAttributes(replacement,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    replacement.hp=replacement.maxHp=100000000;world.monsters.front()=std::move(replacement);world.synchronizeEntityHandles();
    const auto newHandle=world.monsters.front().handle;world.advanceSingleTick();
    check(oldHandle!=newHandle&&world.monsters.front().capturedBy<0,
        "Replacing a captured actor with the same public id/path renews its handle and never rebinds the old hold");
    evidence.push_back({{"case","same_id_replacement"},{"old_handle",oldHandle.json()},{"new_handle",newHandle.json()}});

    world.changeScene();world.monsters.clear();world.synchronizeEntityHandles();world.player.dead=false;
    world.player.life=ActorLife::Alive;world.player.hp=world.player.maxHp;world.player.x=world.player.px=500;
    world.player.y=world.player.py=344;world.player.z=world.player.vz=0;
    addMob(world,4,grabbableMob);auto &sceneTarget=world.monsters.front();
    check(captureWithSourceInput(pvf,assets,world,sceneTarget),"World input reaches a real source capture before scene test");
    world.changeScene();
    check(sceneTarget.capturedBy<0&&world.player.handle!=EntityHandle{}&&
        !world.experimentalRuntime()->sourceGrabState(),
        "Scene transition renews owner identity and clears unsaved target capture");

    world.monsters.clear();world.synchronizeEntityHandles();world.player.dead=false;world.player.life=ActorLife::Alive;
    world.player.hp=world.player.maxHp;world.player.x=world.player.px=500;world.player.y=world.player.py=344;
    addMob(world,5,grabbableMob);auto &deathTarget=world.monsters.front();
    check(captureWithSourceInput(pvf,assets,world,deathTarget),"World input reaches a real source capture before death test");
    world.beginDeath(world.player);world.advanceSingleTick();
    check(deathTarget.capturedBy<0&&!world.experimentalRuntime()->sourceGrabState(),
        "Owner death runs normal death transition and releases its unsaved captured target");
    evidence.push_back({{"case","owner_death"},{"target",deathTarget.handle.json()},{"dead",world.player.dead}});

    return {{"status","passed"},{"checks",checks},{"evidence",evidence},{"pvf_sha256",pvfIdentity},
        {"source","40JP CNFighter sub_5E78C0 held-object frame callback; current 1031 CHR/ANI/ATK/MOB"},
        {"not_covered",{"passiveobject/21001 Suplex impact visual","other native Fighter grab families",
            "release placement search parity","original client timing and effects"}},
        {"runtime_executed_here",true}};
}
} // namespace dnf
