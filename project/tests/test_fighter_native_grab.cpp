#include "dnf/collision.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/monster_effects.hpp"
#include "dnf/progression.hpp"
#include "dnf/character_attack.hpp"
#include "dnf/storage.hpp"
#include "dnf/skill_learning_transaction.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
constexpr SkillKey suplex{1,9};
constexpr const char *grabbableMob="monster/goblin/goblin.mob";
constexpr const char *ungrabbableMob="monster/act8/chiefmong/chiefmong.mob";

void grabCheck(bool passed,const std::string &message) {
    if(!passed)throw std::runtime_error("reference Fighter source grab: "+message);
}

void prepareWorld(World &world,RegionCatalog &regions) {
    world.enableExperimentalCharacters();
    // Use the same source starter/appearance transaction as a newly created
    // Fighter. Progression::initialize alone grants a legacy Swordman weapon.
    const auto directory=std::filesystem::path("cache/fighter-native-grab-runtime")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    CharacterStore store(directory,"reference-fighter-grab-test");
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

void alignTrySourceBoxes(Pvf &pvf,Assets &assets,World &world,Actor &target,SkillKey skill=suplex) {
    const auto &descriptor=world.experimentalRuntime()->plan().sourceSkillActions.at(skill);
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
    for(int direction:{-1,1}) {
        Actor owner,held;owner.dir=direction;
        owner.px=100;owner.x=117;owner.py=200;owner.y=203;owner.pz=5;owner.z=12;
        held.x=-500;held.px=-700;
        for(const auto offset:{std::array<double,3>{60,-1,20},std::array<double,3>{35,-1,45},std::array<double,3>{-45,-1,0}}) {
            held.attachTo(owner,offset,-0.785);
            for(double alpha:{0.0,0.5,1.0})
                grabCheck(std::abs((held.px+(held.x-held.px)*alpha)-(owner.px+(owner.x-owner.px)*alpha)-direction*offset[0])<1e-8,
                    "Moving owner and snapped local grip share interpolation in either facing");
        }
        check(held.captureRotationRadians==-0.785&&held.vx==0&&held.vy==0&&held.vz==0,
            "Shared attachment keeps a discrete local pose while interpolating owner translation, facing "+std::to_string(direction));
    }
    RegionCatalog regions(pvf,assets);
    const auto pvfIdentity=pvf.identity();
    check(pvfIdentity=="d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d",
        "Fixture is the fingerprinted 1031 source PVF");

    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::InferredReferencePercentDeadlines})
    for(int direction:{-1,1}) {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        const auto directory=std::filesystem::path("cache/fighter-native-grab-runtime")/
            ("normal-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        CharacterStore store(directory,"fighter-normal-base-test");
        store.data={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
        store.data["characters"][0]={{"name","NormalFighterBase"},{"class","fighter"},
            {"identity",CharacterIdentity{1,0,0}.json()},{"level",15},{"weapon",0},{"skill_initialization","source-v1"}};
        Progression progress(regions);store.apply(0,world,progress);world.configureAnimationClock(clock);
        for(const auto key:{suplex,SkillKey{1,12},SkillKey{1,46}}) {
            check(world.runtimeSkillPolicy(key).implemented,"已恢复基础动作进入正常学习消费者");
            evidence.push_back({{"case","normal_fighter_source_permission"},{"key",key.json()},
                {"descriptor",world.experimentalRuntime()->plan().sourceSkillActions.at(key).snapshot()}});
            if(direction==-1&&clock==ani_clock::ClockPolicy::SourceDelay100) {
                const auto original=std::make_shared<ExperimentalCharacterPlan>(world.experimentalRuntime()->plan());
                auto rejectMutation=[&](const char *label,const std::function<void(ExperimentalCharacterPlan &)> &mutate) {
                    auto changed=std::make_shared<ExperimentalCharacterPlan>(*original);mutate(*changed);
                    auto saved=std::move(world.experimentalRuntime_);
                    world.experimentalRuntime_=std::make_unique<ExperimentalCharacterRuntime>(changed);
                    const bool rejected=!world.runtimeSkillPolicy(key).implemented;
                    world.experimentalRuntime_=std::move(saved);
                    check(rejected,std::string("精确来源变异拒绝：")+label);
                };
                rejectMutation("PVF",[](auto &plan){plan.pvfIdentity="changed";});
                for(auto member:{&SourceSkillAction::skill,&SourceSkillAction::motion,&SourceSkillAction::attack})
                    rejectMutation("SKL/body/ATK",[&](auto &plan){(plan.sourceSkillActions.at(key).*member).memberSha256="changed";});
                if(key.skillId!=46) {
                    for(auto member:{&SourceSkillAction::objectRegistry,&SourceSkillAction::object,&SourceSkillAction::animation})
                        rejectMutation("OBJ注册/OBJ/ANI",[&](auto &plan){(plan.sourceSkillActions.at(key).*member).memberSha256="changed";});
                    rejectMutation("末阶段body",[&](auto &plan){plan.sourceSkillActions.at(key).nativeStages.back().motion.memberSha256="changed";});
                    if(key.skillId==9)for(size_t stage=0;stage<2;++stage)
                        rejectMutation("阶段ATK",[&](auto &plan){plan.sourceSkillActions.at(key).nativeStages[stage].attack.memberSha256="changed";});
                }
                check(world.runtimeSkillPolicy(key).implemented,"变异回归后原始来源仍允许正常学习");
            }
            if(world.skillState().learnedLevel(key)==0) {
                const auto quote=world.quoteSkillLearning(key,15);SkillLearningTransaction transaction;
                check(quote.accepted(),"基础技能来源学习资格："+quote.json().dump());
                const auto learned=transaction.submit(store,0,world,progress,
                    {"normal-base-"+std::to_string(key.skillId),key,quote.revision,quote.targetLevel},Json::object());
                check(learned.ok,"真实SP学习事务发布基础动作且不依赖预览或赠送："+learned.json().dump());
            }
        }
        check(world.assignLearnedSkillSlot(0,suplex).ok&&!world.experimentalSkillPreviewEnabled()&&!world.debugOverrides().enabled,
            "背摔使用正常已学快捷栏且测试覆盖关闭");
        world.combat=true;world.freezeAi=true;world.mapWidth=3000;world.walkRects={{0,0,3000,1200}};world.blockedRects.clear();
        world.player.x=world.player.px=500;world.player.y=world.player.py=344;world.player.dir=direction;
        world.player.mp=world.player.maxMp;world.randomStreams()=RandomStreams(67);
        addMob(world,900,grabbableMob);auto &target=world.monsters.back();
        const int hp=target.hp,mp=world.player.mp;
        check(captureWithSourceInput(pvf,assets,world,target),"正常背摔双朝向真实输入接受抓取");
        const auto cost=world.experimentalRuntime()->snapshotDiagnostics().at("last_cost");
        check(mp-world.player.mp==cost.at("mp").at("value").get<int>()&&
            world.experimentalRuntime()->remainingCooldown(suplex,world.nowMs())>0,
            "正常背摔只支付一次来源MP并启动来源CD");
        for(int tick=0;tick<150;++tick)world.advanceSingleTick();
        check(target.hp<hp&&target.capturedBy<0&&!world.experimentalRuntime()->attacking()&&
            !world.experimentalRuntime()->sourceGrabState(),"正常背摔实际伤害并完成释放与收势清理");
        check(world.skillState().learnedLevel(suplex)>0&&world.skillState().learnedLevel({1,12})>0,
            "战斗保持正常已学账本且不产生临时预览资格");
        world.releaseInputs();world.changeScene();world.monsters.clear();world.idle();world.combat=false;
        world.player.recovery=0;world.player.stunUntil=0;world.player.hitStopTicks=0;world.player.hitStopped=false;
        world.player.z=world.player.pz=world.player.vz=world.player.vx=world.player.vy=0;
        check(world.assignLearnedSkillSlot(0,SkillKey{1,12}).ok,"正常念气波进入已学快捷栏");
        world.combat=true;world.player.x=world.player.px=1000;world.player.y=world.player.py=344;
        world.player.mp=world.player.maxMp;world.events.clear();world.randomStreams()=RandomStreams(67);
        addMob(world,901,grabbableMob);auto &nenTarget=world.monsters.back();
        nenTarget.x=nenTarget.px=1000+direction*70;nenTarget.y=nenTarget.py=344;
        const int nenHp=nenTarget.hp,nenMp=world.player.mp;
        castFromWorldInput(world);
        const auto nenCost=world.experimentalRuntime()->snapshotDiagnostics().at("last_cost");
        check(nenMp-world.player.mp==nenCost.at("mp").at("value").get<int>()&&
            world.experimentalRuntime()->remainingCooldown({1,12},world.nowMs())>0,"正常念气波单次MP/CD生效");
        for(int tick=0;tick<180;++tick)world.advanceSingleTick();
        check(nenTarget.hp<nenHp&&!world.experimentalRuntime()->attacking()&&
            world.experimentalRuntime()->snapshotDiagnostics().at("source_nut_entities")==0,
            "正常念气波双朝向双时钟独立实体命中并清理");
        world.releaseInputs();world.changeScene();world.monsters.clear();world.idle();world.combat=false;
        world.player.recovery=0;world.player.stunUntil=0;world.player.hitStopTicks=0;world.player.hitStopped=false;
        world.player.z=world.player.pz=world.player.vz=world.player.vx=world.player.vy=0;
        const SkillKey kick{1,46};
        check(world.assignLearnedSkillSlot(0,kick).ok&&!world.experimentalSkillPreviewEnabled()&&!world.debugOverrides().enabled,
            "正常前踢使用来源已学快捷栏且不依赖预览覆盖");
        world.combat=true;world.player.x=world.player.px=1000;world.player.y=world.player.py=344;
        world.player.mp=world.player.maxMp;world.events.clear();world.randomStreams()=RandomStreams(67);
        addMob(world,902,grabbableMob);auto &kickTarget=world.monsters.back();
        kickTarget.x=kickTarget.px=1000+direction*55;kickTarget.y=kickTarget.py=344;
        const int kickHp=kickTarget.hp,kickMp=world.player.mp;
        const auto &descriptor=world.experimentalRuntime()->plan().sourceSkillActions.at(kick);
        evidence.push_back({{"case","normal_singlekick_sources"},{"direction",direction},
            {"skill",descriptor.skill.json()},{"motion",descriptor.motion.json()},{"attack",descriptor.attack.json()}});
        castFromWorldInput(world);
        const auto kickCost=world.experimentalRuntime()->snapshotDiagnostics().at("last_cost");
        check(kickMp-world.player.mp==kickCost.at("mp").at("value").get<int>()&&
            world.experimentalRuntime()->remainingCooldown(kick,world.nowMs())>0,"正常前踢单次来源MP/CD生效");
        for(int tick=0;tick<150;++tick)world.advanceSingleTick();
        check(kickTarget.hp<kickHp&&!world.experimentalRuntime()->attacking(),"正常前踢双朝向双时钟真实命中并退出");
        check(world.skillState().learnedLevel(kick)>0,"前踢保留正常已学账本");
        store.close();
    }

    // The reference ShoulderTackleHit ANI is an accepted-contact effect, not an
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
            "Accepted reference ShoulderTackle contact publishes exactly one conditional hit ANI");
        check(hitEffects.front()->animation=="character/fighter/effect/animation/shouldertacklehit.ani"&&
              hitEffects.front()->x==overlap.x+overlap.w*.5&&hitEffects.front()->y==overlap.y+overlap.h*.5&&
              hitEffects.front()->z==overlap.z+overlap.d*.5&&hitEffects.front()->expires>cueWorld.nowMs(),
            "ShoulderTackleHit uses the accepted overlap center and the source ANI lifetime");
        evidence.push_back({{"case","shoulder_tackle_accepted_hit_effect"},{"damage_trace",cueWorld.lastDamageTrace_},
            {"effect",{{"animation",hitEffects.front()->animation},{"position",{hitEffects.front()->x,hitEffects.front()->y,hitEffects.front()->z}},
                {"expires",hitEffects.front()->expires}}}});
    }

    // Fling uses the native CNThrownEnemy forward/overhead anchors, sharing
    // capture ownership and height measurement with Suplex.
    for(const int direction:{-1,1}) {
        World flingWorld(pvf,assets,WorldRules::BetaFoundationV1);prepareWorld(flingWorld,regions);
        flingWorld.monsters.reserve(3);
        auto &runtime=*flingWorld.experimentalRuntime();
        const SkillKey fling{1,49};
        const auto &action=runtime.plan().sourceSkillActions.at(fling);
        runtime.configuration().configureSourceSkillAction(fling,1,runtime.plan());
        runtime.configuration().assignSlot(0,fling,runtime.plan());flingWorld.player.dir=direction;
        addMob(flingWorld,91,grabbableMob);auto &target=flingWorld.monsters.front();
        alignTrySourceBoxes(pvf,assets,flingWorld,target,fling);
        flingWorld.enqueue({flingWorld.simulationNanoseconds(),20,true});flingWorld.advanceSingleTick();
        flingWorld.enqueue({flingWorld.simulationNanoseconds(),20,false});
        for(int tick=0;tick<40&&target.capturedBy<0;++tick)flingWorld.advanceSingleTick();
        check(action.nativeGrab->thrownEnemyStagePose&&target.capturedBy==0&&
            (target.x-flingWorld.player.x)*direction==60&&target.y==flingWorld.player.y-1&&target.px==target.x,
            "Fling acquisition snaps to native forward grip in either facing");
        bool heldForward=false,overhead=false,launched=false,flightContact=false;
        for(int tick=0;tick<120&&runtime.attacking();++tick) {
            flingWorld.advanceSingleTick();const auto grab=runtime.sourceGrabState();
            if(grab&&grab->holding&&grab->stage==1) {
                heldForward=true;
                check((target.x-flingWorld.player.x)*direction==60&&target.y==flingWorld.player.y-1&&
                    target.animation=="damage1"&&target.captureRotationRadians==0,
                    "1031 native hold style0 stays in the hands throughout local hold stage1 in either facing");
            }
            if(grab&&grab->holding&&grab->release&&target.capturedBy==0) {
                overhead=true;
                check(target.x==flingWorld.player.x&&target.y==flingWorld.player.y+1&&
                    target.z>=flingWorld.player.z+40&&target.animation=="damage1"&&target.captureRotationRadians==0,
                    "1031 native throw style1 raises the victim only during local release stage2");
            }
            if(!launched&&target.capturedBy<0&&target.hitReaction.state==4) {
                launched=true;
                check(target.vx*direction>0&&target.vz>0&&target.animation=="down",
                    "Fling release enters native weighted flight and authored down pose in either facing");
                check(action.boundBody&&flingWorld.experimentalAdapter_->boundBodies_.size()==1&&
                    flingWorld.experimentalAdapter_->boundBodies_.front().flight.targets.count(target.handle),
                    "Native launched body owns separate flight/impact ledgers and excludes its own victim from flight damage");
                addMob(flingWorld,92,grabbableMob);auto &nearby=flingWorld.monsters.back();
                nearby.x=nearby.px=target.x;nearby.y=nearby.py=target.y;nearby.z=nearby.pz=target.z;
                nearby.dir=target.dir;nearby.animation=target.animation;nearby.animationPath=target.animationPath;
                nearby.animationClock=target.animationClock;nearby.animationClockSource=target.animationClockSource;
                nearby.animStart=target.animStart;
                const int before=nearby.hp,heldBefore=target.hp;
                flingWorld.experimentalAdapter_->advanceBoundBodies();
                const auto after=nearby.hp;
                flingWorld.experimentalAdapter_->advanceBoundBodies();
                flightContact=after<before&&nearby.hp==after&&target.hp==heldBefore;
                check(flightContact,"Moving victim's authored hurt boxes damage another monster once while never self-hitting in flight");
                const auto &volume=flingWorld.attackVolumes.back();
                check(volume.sourceAttack&&volume.sourceAttack->source.path=="passiveobject/common/attackinfo/bodyhit.atk"&&
                    volume.sourceModifiers&&volume.sourceModifiers->percent==0&&volume.sourceModifiers->independentPercent==429,
                    "BodyHit collision uses current flight SKL column2 with its own physical ATK and no borrowed body coefficient");
            }
        }
        const auto diagnostics=flingWorld.experimentalDiagnostics().value("world",Json::array());
        const auto releases=std::count_if(diagnostics.begin(),diagnostics.end(),[](const auto &row){
            return row.value("code",std::string())=="source_native_grab_launch";});
        check(heldForward&&overhead&&launched&&releases==1&&target.capturedBy<0,
            "Fling releases once at its native frame gate, without waiting for the action to finish");
        bool floorEffects=false;
        for(int tick=0;tick<240;++tick) {
            flingWorld.advanceSingleTick();
            const auto count=std::count_if(flingWorld.effects.begin(),flingWorld.effects.end(),[](const auto &effect){return effect.phase=="source_bound_body_floor";});
            floorEffects|=count==3;
        }
        const auto impacts=flingWorld.experimentalDiagnostics().value("world",Json::array());
        const auto floorHits=std::count_if(impacts.begin(),impacts.end(),[](const auto &row){
            return row.value("code",std::string())=="source_bound_body_impact"&&row.value("impact",std::string())=="floor";});
        const auto victimHits=std::count_if(flingWorld.events.begin(),flingWorld.events.end(),[](const auto &event){return event.kind=="hit"&&event.target==91;});
        check(flightContact&&floorEffects&&floorHits==1&&victimHits==1&&target.hp<target.maxHp&&flingWorld.experimentalAdapter_->boundBodies_.empty(),
            "Fling floor contact applies one final damage hit with three native landing effects and retires its independent body controller");
        check(target.recovery==0&&target.z==0&&target.animation=="stay",
            "Fling cancellation/release enters shared landing and stand recovery without another hit");
    }
    // Empty release traverses the input/controller/runtime path and the real
    // try ATK. It cannot become a damage contact without a qualifying victim.
    for(const auto boundary:{"wall","scene","replacement","owner-death","cancel"}) {
        World launchedWorld(pvf,assets,WorldRules::BetaFoundationV1);prepareWorld(launchedWorld,regions);
        auto &runtime=*launchedWorld.experimentalRuntime();const SkillKey fling{1,49};
        runtime.configuration().configureSourceSkillAction(fling,1,runtime.plan());
        runtime.configuration().assignSlot(0,fling,runtime.plan());
        addMob(launchedWorld,94,grabbableMob);auto &victim=launchedWorld.monsters.back();
        alignTrySourceBoxes(pvf,assets,launchedWorld,victim,fling);castFromWorldInput(launchedWorld);
        for(int tick=0;tick<100&&launchedWorld.experimentalAdapter_->boundBodies_.empty();++tick)launchedWorld.advanceSingleTick();
        check(launchedWorld.experimentalAdapter_->boundBodies_.size()==1,"Real Fling release creates body controller before lifecycle check");
        if(std::string(boundary)=="wall") {
            const int hp=victim.hp;bool wallEffects=false;
            launchedWorld.blockedRects.push_back({victim.x+1,victim.y-20,30,40});
            for(int tick=0;tick<100;++tick) {
                launchedWorld.advanceSingleTick();
                wallEffects|=std::count_if(launchedWorld.effects.begin(),launchedWorld.effects.end(),[](const auto &effect){return effect.phase=="source_bound_body_wall";})==3;
            }
            const auto rows=launchedWorld.experimentalDiagnostics().value("world",Json::array());
            check(victim.hp<hp&&wallEffects&&std::count_if(rows.begin(),rows.end(),[](const auto &row){
                return row.value("code",std::string())=="source_bound_body_impact"&&row.value("impact",std::string())=="wall";})==1&&
                launchedWorld.experimentalAdapter_->boundBodies_.empty(),
                "Actual walk-geometry collision triggers one wall impact with native effects and no later floor duplicate");
        } else if(std::string(boundary)=="cancel") {
            launchedWorld.idle();launchedWorld.experimentalAdapter_->publishNeutralReaction();
            check(launchedWorld.experimentalAdapter_->boundBodies_.size()==1,
                "Independent thrown victim survives caster action cancellation after release");
            for(int tick=0;tick<240;++tick)launchedWorld.advanceSingleTick();
            check(victim.hp<victim.maxHp&&launchedWorld.experimentalAdapter_->boundBodies_.empty(),
                "Cancelled caster's already-thrown victim still receives its one landing impact");
        } else {
            const auto hits=std::count_if(launchedWorld.events.begin(),launchedWorld.events.end(),[](const auto &event){return event.kind=="hit";});
            if(std::string(boundary)=="scene")launchedWorld.changeScene();
            else if(std::string(boundary)=="owner-death")launchedWorld.beginDeath(launchedWorld.player);
            else {
                Actor replacement;replacement.id=victim.id;replacement.monsterPath=grabbableMob;
                replacement.x=victim.x;replacement.y=victim.y;
                launchedWorld.initializeMonsterAttributes(replacement,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
                replacement.hp=replacement.maxHp=100000000;victim=std::move(replacement);launchedWorld.synchronizeEntityHandles();
            }
            launchedWorld.experimentalAdapter_->advanceBoundBodies();
            check(launchedWorld.experimentalAdapter_->boundBodies_.empty(),std::string("Launched body retires at ")+boundary+" without rebinding a visible monster ID");
            check(std::count_if(launchedWorld.events.begin(),launchedWorld.events.end(),[](const auto &event){return event.kind=="hit";})<=hits,
                "Retired target-bound object publishes no stale impact damage");
        }
    }
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
    const auto &acquired=world.monsters.front();
    check((acquired.x-world.player.x)*world.player.dir==60&&acquired.y==world.player.y-1&&
        acquired.px==acquired.x&&acquired.py==acquired.y&&acquired.pz==acquired.z,
        "Acquisition snaps directly to native Suplex frame-zero grip with no old-position interpolation or generic intermediate offset");
    const int hpAtCapture=world.monsters.front().hp;
    check(acceptedGrabDiagnostic(world,targetHandle)&&world.monsters.front().hp==hpBeforeTry&&hpAtCapture==hpBeforeTry&&
        world.experimentalRuntime()->sourceGrabState()->ownerAction!=0,
        "Try frame accepts the generation-qualified owner without applying damage");
    bool targetDamaged=false,sawLift=false,sawShoulder=false;
    Json heldPoses=Json::array();
    for(int tick=0;tick<100&&!targetDamaged;++tick) {
        world.advanceSingleTick();
        const auto grab=world.experimentalRuntime()->sourceGrabState();
        const auto &held=world.monsters.front();
        if(grab&&grab->holding&&grab->suplexOwnerFramePose&&held.capturedBy==0) {
            const double localX=(held.x-world.player.x)*world.player.dir;
            if(grab->ownerFrame<2)sawLift=localX==60&&held.y==world.player.y-1;
            if(grab->ownerFrame==3)sawShoulder=localX>0&&localX<=55&&held.z>=world.player.z+25&&
                held.captureRotationRadians<-.78&&held.animation=="damage1";
            for(double alpha:{0.0,0.25,0.5,0.75,1.0}) {
                const double ownerX=world.player.px+(world.player.x-world.player.px)*alpha;
                const double ownerY=world.player.py+(world.player.y-world.player.py)*alpha;
                const double heldX=held.px+(held.x-held.px)*alpha;
                const double heldY=held.py+(held.y-held.py)*alpha;
                grabCheck(std::abs(heldX-ownerX-world.player.dir*localX)<1e-8&&std::abs(heldY-ownerY+1)<1e-8&&
                    std::abs(held.pz-world.player.pz-held.z+world.player.z)<1e-8,
                    "Every render fraction retains the current owner-frame grip and rotation together");
            }
            heldPoses.push_back({{"frame",grab->ownerFrame},{"local_x",localX},{"z",held.z},
                {"rotation",held.captureRotationRadians},{"animation",held.animation}});
        }
        targetDamaged=world.monsters.front().hp<hpAtCapture&&damageTraceTargets(world,targetHandle);
    }
    check(!heldPoses.empty(),"Rendered attachment endpoints retain the current grip through all sampled native frames");
    check(sawLift&&sawShoulder,
        "Held victim follows source owner frames through forward lift and rotated shoulder pose instead of a fixed offset");
    check(targetDamaged&&world.monsters.front().capturedBy<0,
        "reference held-object frame callback resolves the real Suplex ATK against exactly the captured handle and releases it");
    check(world.monsters.front().x<world.player.x&&world.monsters.front().captureRotationRadians==0,
        "Suplex impact places victim behind the owner and clears the transient capture rotation on release");
    check(world.monsters.front().recovery!=0||world.monsters.front().hitReaction.state!=0,
        "Suplex impact exits capture before entering shared source hit response");
    check(std::any_of(world.effects.begin(),world.effects.end(),[](const auto &effect){
        return effect.phase=="source_native_object_birth"&&effect.animation=="character/fighter/effect/animation/suplexdust.ani";
    }),"Suplex independent impact object creates its native dust visual at the release event");
    for(int tick=0;tick<240;++tick)world.advanceSingleTick();
    check(world.monsters.front().recovery==0&&world.monsters.front().hitReaction.state==0&&
        world.monsters.front().animation=="stay"&&world.monsters.front().z==0,
        "Suplex victim stands up autonomously with AI frozen and no further player input");
    evidence.push_back({{"case","accepted_direct_held_hit"},{"target",targetHandle.json()},
        {"damage_trace",world.lastDamageTrace_},{"events",world.eventLog()},{"held_poses",heldPoses}});

    for(int direction:{-1,1}) {
        World splash(pvf,assets,WorldRules::BetaFoundationV1);prepareWorld(splash,regions);
        splash.player.dir=direction;splash.monsters.reserve(2);
        addMob(splash,101,grabbableMob);
        check(captureWithSourceInput(pvf,assets,splash,splash.monsters.front()),"Splash test acquires a real source victim");
        addMob(splash,102,grabbableMob);
        auto &nearby=splash.monsters.back();
        nearby.x=nearby.px=splash.player.x-direction*95;nearby.y=nearby.py=splash.player.y;
        nearby.stunUntil=splash.nowMs()+10000;
        const int hp=nearby.hp;bool wave=false,dust=false;std::set<uint64_t> ids;
        for(int tick=0;tick<150;++tick) {
            splash.advanceSingleTick();
            for(const auto &volume:splash.attackVolumes)if(volume.sourceAttack&&
                volume.sourceAttack->source.path=="passiveobject/character/fighter/attackinfo/suplexsub.atk") {
                wave=true;ids.insert(volume.serial);
            }
            for(const auto &effect:splash.effects)if(effect.phase=="source_native_object_birth") {
                dust|=effect.x==splash.player.x-direction*47&&effect.y==splash.player.y&&effect.z==splash.player.z;
            }
        }
        int direct=0,duplicate=0;
        for(const auto &event:splash.events)if(event.kind=="hit"&&event.target==101) {
            direct+=event.name=="experimental_source_skill";
            duplicate+=event.name=="source_nut_passive_object";
        }
        check(wave&&ids.size()==1&&!ids.count(splash.experimentalAdapter_->attackId_)&&dust&&nearby.hp<hp,
            "Suplex publishes one world-positioned shockwave ledger and dust, damaging a nearby non-held victim in either facing");
        check(direct==1&&duplicate==0,
            "Native shockwave pre-registers its captured victim and cannot apply a second damage hit to that victim");
        evidence.push_back({{"case","suplex_independent_splash"},{"direction",direction},{"events",splash.eventLog()}});
    }

    // Interrupted/legacy airborne state can already be grounded with zero
    // velocity. It must still enter landing instead of waiting for another hit.
    {
        World grounded(pvf,assets,WorldRules::BetaFoundationV1);prepareWorld(grounded,regions);
        addMob(grounded,92,grabbableMob);auto &victim=grounded.monsters.front();
        victim.recovery=1;victim.animation="down";victim.z=victim.vz=0;victim.hitReaction={};
        for(int tick=0;tick<120;++tick)grounded.advanceSingleTick();
        check(victim.recovery==0&&victim.animation=="stay",
            "Already-grounded airborne recovery completes without AI or a new attack");
    }

    {
        World mirror(pvf,assets,WorldRules::BetaFoundationV1);prepareWorld(mirror,regions);
        mirror.player.dir=-1;addMob(mirror,91,grabbableMob);
        check(captureWithSourceInput(pvf,assets,mirror,mirror.monsters.front()),
            "Left-facing real source contact acquires a separate held victim");
        bool lifted=false,overShoulder=false;
        for(int tick=0;tick<100&&mirror.experimentalRuntime()->attacking();++tick) {
            mirror.advanceSingleTick();const auto grab=mirror.experimentalRuntime()->sourceGrabState();
            const auto &held=mirror.monsters.front();
            if(!grab||!grab->holding||!grab->suplexOwnerFramePose||held.capturedBy!=0)continue;
            const auto localX=(held.x-mirror.player.x)*mirror.player.dir;
            grabCheck(std::abs(held.px-mirror.player.px-held.x+mirror.player.x)<1e-8&&
                std::abs(held.py-mirror.player.py-held.y+mirror.player.y)<1e-8&&
                std::abs(held.pz-mirror.player.pz-held.z+mirror.player.z)<1e-8,
                "Mirrored capture never interpolates the old grip under the current rotation");
            if(grab->ownerFrame<2)lifted=localX==60;
            if(grab->ownerFrame==3)overShoulder=localX>0&&localX<=55&&held.z>=25;
        }
        check(lifted&&overShoulder&&mirror.monsters.front().capturedBy<0&&
            mirror.monsters.front().captureRotationRadians==0,
            "Left-facing owner mirrors the source held trajectory and retires the pose after release");
    }

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
        {"source","reference CNFighter held-object frame callback; current 1031 CHR/ANI/ATK/MOB"},
        {"not_covered",{"enhanced Suplex skill22","other native Fighter grab families","BodyHit native wall rebound and directional throws",
            "release placement search parity","original client timing and effects"}},
        {"runtime_executed_here",true}};
}
} // namespace dnf
