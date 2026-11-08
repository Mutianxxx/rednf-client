#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/female_gunner_entities.hpp"
#include "dnf/storage.hpp"
#include "female_gunner_test_weapon.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr int contactHp=100000000;
void contactFloor(World &world,int direction=1) {
    world.releaseInputs();world.idle();world.combat=true;world.freezeAi=true;world.freeCd=true;
    world.mapWidth=6000;world.walkRects={{0,185,6000,600}};
    auto &a=world.player;a.x=a.px=2500;a.y=a.py=400;a.z=a.pz=0;a.dir=direction;
    a.mp=INT32_MAX;a.hp=a.maxHp=contactHp;a.dead=false;a.life=ActorLife::Alive;
    a.recovery=0;a.stunUntil=0;a.hitStopTicks=0;a.hitStopped=false;a.vx=a.vy=a.vz=0;
}
void contactTargets(World &world,int direction=1,bool single=false) {
    const double positions[]={20,55,100,180,300,500,850};
    for(const auto offset:positions) {
        if(single && !world.monsters.empty())break;
        Actor a;a.id=int(world.monsters.size()+1);a.sourceId=10;a.monsterPath="monster/goblin/goblin.mob";
        a.x=a.px=world.player.x+direction*offset;a.y=a.py=world.player.y;a.dir=-direction;
        world.initializeMonsterAttributes(a,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
        // HP alone is a diagnostic longevity fixture. Defense, hurt boxes,
        // status resistance and reactions remain actual source consumers.
        a.hp=a.maxHp=contactHp;world.monsters.push_back(std::move(a));
    }
    world.synchronizeEntityHandles();
}
void contactConfigure(World &world,SkillKey key) {
    auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
    runtime.configuration()=ExperimentalSkillConfiguration(plan);
    runtime.configuration().configureFemaleGunnerSourceSkill(key,1,plan);runtime.configuration().assignSlot(0,key,plan);
}
int contactBudget(const ExperimentalCharacterPlan &plan,const FemaleGunnerSkillDescriptor &descriptor,
    const FemaleGunnerSkillCommand &command) {
    int64_t sourceMs=0;auto timedCommand=command;
    for(const auto &stage:descriptor.stages)if(const auto *motion=plan.motion(stage.motionTag,stage.motionSlot)) {
        const auto timing=buildFemaleGunnerStageTiming(timedCommand,stage,*plan.animations.at(motion->source.memberPath));
        applyFemaleGunnerStageTiming(timedCommand,timing);
        sourceMs+=std::max(timing.runtimeDurationMs,timing.completionAfterMs)*std::max(2,stage.repeat);
    }
    return int(std::min<int64_t>(30000,(sourceMs+timedCommand.lifetimeMs+4000)*60/1000+100));
}
bool nestedSourcePath(const Json &,const std::string &);
bool receiptUsesSkill(const Json &receipt,const std::string &path) {
    if(!receipt.is_object() || !receipt.value("usable",false) || !receipt.contains("sources"))return false;
    return nestedSourcePath(receipt.at("sources").at("skill"),path);
}
bool nestedSourcePath(const Json &value,const std::string &path) {
    if(value.is_object() && value.value("member_path",std::string())==path)return true;
    if(value.is_structured())for(const auto &child:value)if(nestedSourcePath(child,path))return true;
    return false;
}
int ammoRemaining(const Json &diagnostics,int skill) {
    for(const auto &buff:diagnostics.at("buffs"))if(buff.at("command").at("key").at("skill_id")==skill)
        return buff.at("command").at("count");
    return 0;
}
} // namespace

static Json runFemaleGunnerContactWorldClockTests(Pvf &pvf,Assets &assets,ani_clock::ClockPolicy clockPolicy) {
    RegionCatalog regions(pvf,assets);Progression progression(regions);
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
    CharacterStore store(std::filesystem::absolute("cache/female-gunner-contact-world-fixtures"));
    store.data["characters"][0]={{"name","FemaleGunnerContactWorldRegression"},{"class","atgunner"},
        {"identity",CharacterIdentity{5,0,0}.json()},{"level",1},{"skill_initialization","source-v1"}};
    store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clockPolicy);
    const auto &plan=world.experimentalRuntime()->plan();Json rows=Json::array(),checks=Json::array(),failures=Json::array();
    const auto check=[&](bool ok,const std::string &message) {
        checks.push_back({{"passed",ok},{"message",message}});if(!ok)failures.push_back(message);
    };
    const auto castSetup=[&](int id) {
        const auto &descriptor=plan.femaleGunnerSkills.at({5,id});
        const auto command=evaluateFemaleGunnerSkill(descriptor,*plan.skills.at({5,id}).data,1,0);
        contactConfigure(world,{5,id});world.enqueue({world.simulationNanoseconds(),20,true});bool started=false,ended=false;
        for(int step=0;step<contactBudget(plan,descriptor,command);++step) {
            world.advance(16666667);started|=world.experimentalRuntime()->attacking();
            if(started&&!world.experimentalRuntime()->attacking()){ended=true;break;}
        }
        world.releaseInputs();
        if(!started||!ended)throw std::runtime_error("Prerequisite source release did not finish: "+std::to_string(id));
    };
    for(const auto &[key,skill]:plan.skills)if(skill.kind==SkillSourceKind::Active) {
        std::cerr<<"Female Gunner contact "<<key.skillId<<" "<<skill.name<<"\n";
        Json row={{"key",key.json()},{"name",skill.name}};
        std::unique_ptr<FemaleGunnerHandcannonTestFixture> sourceWeapon;
        try {
            world.changeScene();world.monsters.clear();world.events.clear();contactFloor(world);
            if(key.skillId==73){sourceWeapon=std::make_unique<FemaleGunnerHandcannonTestFixture>(world,progression,plan.characterDefinition);row["source_weapon_fixture"]=sourceWeapon->source();}
            const auto &descriptor=plan.femaleGunnerSkills.at(key);
            const auto command=evaluateFemaleGunnerSkill(descriptor,*skill.data,1,0);
            const bool nonDamage=command.kind==FemaleGunnerCommandKind::Buff||command.kind==FemaleGunnerCommandKind::Clear;
            const bool grab=descriptor.family=="grab_ground_shoot"||descriptor.family=="grab_aerial_gatling";
            if(key.skillId==80||key.skillId==81) {
                castSetup(79);
                check(world.femaleGunnerDiagnostics().at("g_group").at("skill")==79,"G transform has actual live G-1 prerequisite: "+skill.name);
                world.events.clear();
            }
            contactTargets(world,key.skillId==20?-1:1,grab);contactConfigure(world,key);
            const auto ledger=world.skillState().snapshot(world.nowMs()),random=world.randomStreams().snapshot();
            const auto mp=world.player.mp;const auto eventStart=world.events.size();
            world.enqueue({world.simulationNanoseconds(),20,true});
            if(key.skillId==13)world.enqueue({world.simulationNanoseconds(),4,true});
            bool started=false,ended=false,buffSeen=false;size_t maxCaptured=0,maxEntities=0;Json receipt;
            int steps=0;std::set<int> targets;size_t eventCursor=eventStart;
            for(;steps<contactBudget(plan,descriptor,command);++steps) {
                world.advance(16666667);started|=world.experimentalRuntime()->attacking();
                ended|=started&&!world.experimentalRuntime()->attacking();
                const auto diagnostics=world.femaleGunnerDiagnostics();maxEntities=std::max(maxEntities,diagnostics.at("entities").size());
                for(const auto &buff:diagnostics.at("buffs"))if(buff.at("command").at("key")==key.json())buffSeen=true;
                size_t captured=0;for(const auto &target:world.monsters)if(target.capturedBy>=0)++captured;
                maxCaptured=std::max(maxCaptured,captured);bool newHit=false;
                while(eventCursor<world.events.size()) {
                    const auto &event=world.events[eventCursor++];
                    if(event.kind=="hit" && event.value>0){targets.insert(event.target);newHit=true;}
                }
                if(newHit) {
                    const auto last=world.statReport().at("last_damage");
                    if(receiptUsesSkill(last,skill.data->definition.source.script.path))receipt=last;
                }
                if(ended && (nonDamage || !receipt.is_null()))break;
                if(ended && diagnostics.at("entities").empty())break;
                if(!started&&steps>4)break;
            }
            check(started&&ended,"Normal skill-slot input starts and finishes source contact release: "+skill.name);
            if(nonDamage) {
                check(std::all_of(world.monsters.begin(),world.monsters.end(),[](const Actor &a){return a.hp==contactHp;}),
                    "Buff/clear release does not invent attack HP damage: "+skill.name);
                if(command.kind==FemaleGunnerCommandKind::Buff)check(buffSeen,"Buff reaches actual World service in contact scenario: "+skill.name);
                if(command.kind==FemaleGunnerCommandKind::Clear) {
                    const auto service=world.femaleGunnerDiagnostics();bool clear=false;for(const auto &trace:service.at("trace"))
                        if(trace.value("event",std::string())=="robot_detonation" && trace.at("skill")==key.json())clear=true;
                    check(clear,"Clear reaches actual detonation consumer without an invented damage projectile: "+skill.name);
                }
                check(world.randomStreams().snapshot()==random,"Nondamaging source release leaves combat RNG unchanged: "+skill.name);
            } else {
                check(!receipt.is_null() && !targets.empty() && std::any_of(world.monsters.begin(),world.monsters.end(),[](const Actor &a){return a.hp<contactHp;}),
                    "Real source attack geometry and matching skill receipt reduce actual target HP: "+skill.name);
                check(world.randomStreams().snapshot()!=random,"Accepted source damage publishes its owned combat random stream: "+skill.name);
            }
            if(grab)check(maxCaptured==1,"Source grab binds exactly one target for its follow-up chain: "+skill.name);
            check(world.player.mp>=0&&world.player.mp<=mp&&world.skillState().snapshot(world.nowMs())==ledger,
                "Source release consumes its isolated resources without modifying normal learning ledger: "+skill.name);
            row["family"]=descriptor.family;row["command_kind"]=femaleGunnerCommandKindName(command.kind);row["ticks"]=steps;
            row["started"]=started;row["ended"]=ended;row["damaged_targets"]=targets;row["max_captured"]=maxCaptured;
            row["maximum_entities"]=maxEntities;row["buff_seen"]=buffSeen;row["mp_before"]=mp;row["mp_after"]=world.player.mp;
            row["last_matching_damage"]=receipt;row["service"]=world.femaleGunnerDiagnostics();
            world.changeScene();const auto cleared=world.femaleGunnerDiagnostics();
            check(cleared.at("entities").empty()&&cleared.at("buffs").empty()&&cleared.at("g_group").at("skill")==0,
                "Scene cancellation clears source entities, buffs and G-group: "+skill.name);
        } catch(const std::exception &error) {
            row["error"]=error.what();row["service"]=world.femaleGunnerDiagnostics();
            check(false,"Actual source contact exception for "+skill.name+": "+error.what());
        }
        if(sourceWeapon)check(sourceWeapon->restore(),"Source handcannon fixture restores prior owned weapon after CannonBall contact release");
        rows.push_back(std::move(row));
    }
    const auto shootOnce=[&]() {
        world.events.clear();world.enqueue({world.simulationNanoseconds(),4,true});bool started=false,ended=false;
        size_t hits=0,feedbacks=0,cursor=0;
        for(int tick=0;tick<1800;++tick) {
            world.advance(16666667);started|=world.experimentalRuntime()->attacking();
            while(cursor<world.events.size()) {
                const auto &event=world.events[cursor++];if(event.kind=="hit"&&event.target==world.monsters.front().id)++hits;
                if(event.kind=="hit_feedback"&&event.target==world.monsters.front().id)++feedbacks;
            }
            ended|=started&&!world.experimentalRuntime()->attacking();
            if(ended&&world.femaleGunnerDiagnostics().at("entities").empty())break;
        }
        return Json{{"started",started},{"ended",ended},{"hits",hits},{"feedbacks",feedbacks},{"target_hp",world.monsters.front().hp}};
    };
    Json shots=Json::array();
    for(const int direction:{1,-1})try {
        world.changeScene();world.monsters.clear();world.events.clear();contactFloor(world,direction);contactTargets(world,direction,true);
        world.monsters.front().x=world.monsters.front().px=world.player.x+direction*100;
        world.experimentalRuntime()->configuration()=ExperimentalSkillConfiguration(plan);
        const auto ordinary=shootOnce();
        check(ordinary.at("started")==true&&ordinary.at("ended")==true&&ordinary.at("hits")==1&&ordinary.at("feedbacks")==1,
            "One ordinary source shooting action accepts exactly one contact per target: "+std::to_string(direction));
        world.changeScene();world.monsters.clear();contactFloor(world,direction);contactTargets(world,direction,true);
        world.monsters.front().x=world.monsters.front().px=world.player.x+direction*100;
        contactConfigure(world,{5,1});castSetup(1);const auto ammo=ammoRemaining(world.femaleGunnerDiagnostics(),1);
        const auto enchanted=shootOnce();const auto hitCount=enchanted.at("hits").get<size_t>(),feedbackCount=enchanted.at("feedbacks").get<size_t>();
        const auto remaining=ammoRemaining(world.femaleGunnerDiagnostics(),1);
        check(enchanted.at("started")==true&&enchanted.at("ended")==true&&world.monsters.front().hp<contactHp,
            "Ordinary source shooting and attached ammo reach a mirrored actual target: "+std::to_string(direction));
        check(hitCount>1&&feedbackCount==hitCount,
            "Source ammo adds actual accepted attack effects to the separately verified single ordinary contact: "+std::to_string(direction));
        check(ammo>0&&remaining==ammo-1,"Source ammo is consumed once per ordinary shooting action: "+std::to_string(direction));
        shots.push_back({{"direction",direction},{"ordinary",ordinary},{"hits",hitCount},{"feedbacks",feedbackCount},{"ammo_before",ammo},{"ammo_after",remaining},
            {"service",world.femaleGunnerDiagnostics()},{"target_hp",world.monsters.front().hp}});
    }catch(const std::exception &error){check(false,"Mirrored ordinary/ammo actual World exception: "+std::string(error.what()));}
    check(shots.size()==2&&shots[0].at("hits")==shots[1].at("hits")&&shots[0].at("ammo_after")==shots[1].at("ammo_after"),
        "Mirrored shooting preserves contact count and ammunition consumption");
    Json transformed=Json::array();
    struct ModeCase {const char *name;int input,skill;const char *family;};
    for(const auto test:{ModeCase{"X shooting",4,0,"twingunblade_basic_shoot"},
                        ModeCase{"Z blade",6,0,"twingunblade_basic_blade"},
                        ModeCase{"Somersault source3",20,3,"twingunblade_somersault"},
                        ModeCase{"Chain Cut source6",20,6,"twingunblade_chain_cut"},
                        ModeCase{"Spinning Blade source7 via logical7",7,7,"twingunblade_spinning_blade"},
                        ModeCase{"Recast source100 finisher",20,100,"twingunblade_finisher"}})try {
        world.changeScene();world.monsters.clear();world.events.clear();contactFloor(world);castSetup(100);
        check(ammoRemaining(world.femaleGunnerDiagnostics(),100)>0,"Actual source100 activation establishes a live transformation: "+std::string(test.name));
        contactTargets(world);world.events.clear();
        if(test.skill) {
            contactConfigure(world,{5,test.skill});
            if(test.input==7)world.experimentalRuntime()->configuration().assignSlot(12,SkillKey{5,test.skill},plan);
        }
        const auto mp=world.player.mp;const auto ledger=world.skillState().snapshot(world.nowMs());
        world.enqueue({world.simulationNanoseconds(),test.input,true});
        bool started=false,ended=false,sourceFamily=false;size_t maxCaptured=0,eventCursor=0;Json receipt;
        for(int tick=0;tick<1800;++tick) {
            world.advance(16666667);started|=world.experimentalRuntime()->attacking();ended|=started&&!world.experimentalRuntime()->attacking();
            size_t captured=0;for(const auto &target:world.monsters)if(target.capturedBy>=0)++captured;
            maxCaptured=std::max(maxCaptured,captured);
            const auto diagnostics=world.femaleGunnerDiagnostics();
            for(const auto &entity:diagnostics.at("entities"))sourceFamily|=entity.at("command").value("family",std::string())==test.family;
            while(eventCursor<world.events.size()) {
                const auto &event=world.events[eventCursor++];
                if(event.kind=="hit"&&event.value>0) {
                    const auto last=world.statReport().at("last_damage");
                    if(last.value("usable",false)&&nestedSourcePath(last.at("sources").at("skill"),plan.skills.at({5,100}).source.memberPath))receipt=last;
                }
            }
            if(ended&&diagnostics.at("entities").empty())break;
        }
        world.releaseInputs();
        check(started&&ended,"Live source100 normal input starts and finishes its actual alternate action: "+std::string(test.name));
        check(!receipt.is_null(),"Live source100 alternate action applies actual HP damage with its mode-source modifier: "+std::string(test.name));
        check(maxCaptured==0,"Transformed source6 and other mode attacks never acquire ordinary Punisher grab capture: "+std::string(test.name));
        check(world.skillState().snapshot(world.nowMs())==ledger,"Mode input preserves normal learning ledger: "+std::string(test.name));
        if(test.skill==100)check(ammoRemaining(world.femaleGunnerDiagnostics(),100)==0&&world.player.mp==mp,
            "Source100 finisher consumes the mode and does not charge activation MP twice");
        else check(ammoRemaining(world.femaleGunnerDiagnostics(),100)>0,"Alternate attack leaves source100 live for its remaining duration: "+std::string(test.name));
        transformed.push_back({{"name",test.name},{"input",test.input},{"skill",test.skill},{"family",test.family},{"entity_family_seen",sourceFamily},
            {"started",started},{"ended",ended},{"maximum_captured",maxCaptured},{"matching_mode_damage",receipt},{"service",world.femaleGunnerDiagnostics()}});
    }catch(const std::exception &error){check(false,"Actual transformed World exception for "+std::string(test.name)+": "+error.what());}
    Json mixedFlame=Json::array();
    for(const bool insectNear:{false,true})for(const bool observeInsect:{false,true})try {
        world.changeScene();world.monsters.clear();world.events.clear();contactFloor(world);castSetup(1);world.events.clear();
        for(const bool insect:{!observeInsect,observeInsect}) {
            Actor actor;actor.id=int(world.monsters.size()+1);actor.sourceId=insect?900:10;
            actor.monsterPath=insect?"monster/newmonsters/bloodbutterfly/antnamed/ammute.mob":"monster/goblin/goblin.mob";
            actor.x=actor.px=world.player.x+((insect==insectNear)?100:120);actor.y=actor.py=world.player.y;actor.dir=-1;
            // Isolate category selection at a supported resolved room level.
            // Original MOB level endpoints/category/hurtboxes stay intact;
            // level60 currently rejects unresolved global-table statBase27.
            world.initializeMonsterAttributes(actor,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
            actor.hp=actor.maxHp=contactHp;world.monsters.push_back(std::move(actor));
        }
        world.synchronizeEntityHandles();const auto target=world.monsters.back().handle;
        auto authored=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,1}),*plan.skills.at({5,1}).data,1,0);authored.family="enchanted_bullet";
        const auto phases=femaleGunnerFlameImpactCommands(pvf,assets,authored,observeInsect?std::vector<std::string>{"[insect]"}:std::vector<std::string>{});
        world.enqueue({world.simulationNanoseconds(),4,true});Json receipt;
        for(int tick=0;tick<1200;++tick) {
            world.advance(16666667);const auto last=world.statReport().at("last_damage");
            if(last.value("usable",false)&&!last.value("missed",false)&&last.at("target")==target.json()&&
               last.at("sources").at("attack").at("source").value("path",std::string())=="passiveobject/character/gunner/attackinfo/flamebulletfireexplosion.atk") {
                const auto &modifier=last.at("sources").at("skill");bool expected=false;
                for(const auto &phase:phases)expected|=modifier.at("percent")==phase.damage.percent&&
                    modifier.at("fixed_damage")==phase.damage.fixedDamage&&modifier.at("independent_percent")==phase.damage.independentPercent;
                check(expected,"Each mixed-target flame AOE chooses that target's own source category coefficients: insectNear="+
                    std::to_string(insectNear)+" observedInsect="+std::to_string(observeInsect));receipt=last;break;
            }
        }
        check(!receipt.is_null(),"Mixed real goblin/insect source targets receive an inspectable actual flame AOE contact after position/vector swaps");
        mixedFlame.push_back({{"insect_near",insectNear},{"observed_insect",observeInsect},{"resolved_room_level",1},
            {"original_insect_level_range",pvf.script("monster/newmonsters/bloodbutterfly/antnamed/ammute.mob").values("[level]")},{"receipt",receipt}});world.releaseInputs();
    }catch(const std::exception &error){check(false,"Actual mixed-category flame World exception: "+std::string(error.what()));}
    Json musket;
    try {
        world.changeScene();world.monsters.clear();world.events.clear();world.experimentalRuntime()->configuration()=ExperimentalSkillConfiguration(plan);
        const auto equipment=loadCharacterList(pvf,"equipment/equipment.lst","equipment");const ItemDefinition *chosen=nullptr;
        for(const auto &registration:equipment.entries)if(registration.exists&&normalize(registration.path).find("/musket/")!=std::string::npos) {
            const auto *item=progression.item(registration.id);if(item&&item->slot=="[weapon]"&&item->minimumLevel<=progression.level()&&
                item->source.number("[sub type]",-1)==2&&progression.itemUsableBy(registration.id,plan.characterDefinition)) {chosen=item;break;}
        }
        check(chosen!=nullptr,"Current registered equipment supplies a usable level-one source musket fixture");
        if(chosen) {
            const auto chosenId=chosen->id;const auto chosenPath=chosen->path;
            const auto inventoryIndex=int(progression.state.at("inventory").size());
            const int uid=progression.state.at("next_uid");progression.state["next_uid"]=uid+1;
            progression.state["inventory"].push_back({{"uid",uid},{"id",chosen->id},{"count",1},{"durability",chosen->durability}});
            const auto equipped=world.changeEquipment(progression,inventoryIndex);
            check(equipped.ok,"Source musket enters actual equipment qualification, appearance and combat-attribute consumers");
            if(equipped) {
                contactFloor(world);contactTargets(world,1,true);world.monsters.front().x=world.monsters.front().px=world.player.x+100;
                const auto ordinary=shootOnce();world.changeScene();world.monsters.clear();contactFloor(world);contactTargets(world,1,true);
                world.monsters.front().x=world.monsters.front().px=world.player.x+100;
                world.experimentalRuntime()->configuration().configureFemaleGunnerSourceSkill({5,110},1,plan);
                const auto boosted=shootOnce();
                check(ordinary.at("hits")==1&&boosted.at("hits")==4&&boosted.at("feedbacks")==4,
                    "Source110 mastery adds exactly three real musket projectiles to the separately verified one-shot ordinary input");
                musket={{"equipment",{{"id",chosenId},{"path",chosenPath}}},{"ordinary",ordinary},{"mastery110_level1",boosted},
                    {"service",world.femaleGunnerDiagnostics()}};
            }
        }
    }catch(const std::exception &error){check(false,"Actual source musket additional-projectile World exception: "+std::string(error.what()));}
    Json result={{"passed",failures.empty()},{"check_count",checks.size()},{"checks",checks},{"failures",failures},{"skills",rows},{"shots",shots},{"transformed",transformed},{"mixed_flame",mixedFlame},{"musket",musket},
        {"animation_clock",ani_clock::policyName(clockPolicy)},
        {"classification","actual-production-world-normal-slot-input-contact"},
        {"diagnostic_fixture","target/player HP longevity, frozen AI, free cooldown, manual source skill selection and resolved room level1; original MOB level endpoints remain source-bound"},
        {"scope","All active caster releases plus at least one matching-source damage contact or explicit non-damage consumer; detached remaining phases and native dynamic parity separately pending"},
        {"original_comparison","pending_user"}};
    if(!failures.empty()) {writeJson(std::string("reports/knowledge-base/female-gunner-contact-world-")+ani_clock::policyName(clockPolicy)+"-failed.json",result);
        throw std::runtime_error("Female Gunner contact World failures: "+std::to_string(failures.size()));}
    return result;
}
Json runFemaleGunnerContactWorldTests(Pvf &pvf,Assets &assets) {
    return runFemaleGunnerContactWorldClockTests(pvf,assets,ani_clock::ClockPolicy::SourceDelay100);
}
Json runFemaleGunnerContactWorldInferredClockTests(Pvf &pvf,Assets &assets) {
    return runFemaleGunnerContactWorldClockTests(pvf,assets,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines);
}
} // namespace dnf
