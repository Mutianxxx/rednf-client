#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/storage.hpp"
#include "dnf/character_attack.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace dnf {
Json runMageThrustRuntimeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message){checks.push_back({{"passed",pass},{"message",message}});
        if(!pass)throw std::runtime_error(message);};
    try {
    RegionCatalog regions(pvf,assets);const SkillKey key{3,4};
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("mage-thrust-"+std::string(ani_clock::policyName(clock))));
        store.data["characters"][0]={{"name","SourceMage"},{"class","mage"},{"identity",CharacterIdentity{3,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clock);
        auto &r=*world.experimentalRuntime();const auto &plan=r.plan();
        evidence.push_back({{"phase","source_plan"},{"diagnostics",plan.diagnostics}});
        check(plan.sourceSkillActions.size()==2&&plan.sourceSkillActions.count(key)&&plan.sourceSkillActions.count({3,12}),"Own Mage Thrust and Upper remain independently registered once");
        const auto &d=plan.sourceSkillActions.at(key);const auto body=assets.animation(d.motion.memberPath);
        check(d.inferredNativeBody&&d.kind==SourceSkillActionKind::BodyAttack&&d.motionSlot==1&&d.attackSlot==0&&d.state==-1,
            "Current list skill4 and CHR motion1/ATK0 bind without inventing a missing Mage state enum");
        check(d.callback.memberPath.empty()&&d.registration.memberPath.empty()&&d.objectId==-1,
            "Mage source reconstruction claims neither own NUT nor a passive object");
        check(d.requiresEquippedAttackVolume&&d.bodyLayers.size()==2&&d.recoveryMs==0&&body->duration==660,
            "Thrust owns exact source timeline and two explicit inferred visuals, with no invented recovery");
        bool bodyAttack=false;for(const auto &f:body->frames)for(const auto &b:f.boxes)bodyAttack|=b.type==15;
        check(!bodyAttack,"Original Mage body remains type14-only; no invented body attack box");
        const auto composed=readCharacterAttackMotion(assets,world.characterAppearance(),d.motion.memberPath);
        std::optional<Box> first;for(size_t f=0;f<body->frames.size();++f)for(const auto &b:composed.boxesAt(f))if(!first)first=b;
        check(!composed.weapons.empty()&&first.has_value(),"Actual saved starter EQU/LAY supplies real weapon type15");
        evidence.push_back({{"phase","actual_equipment"},{"composition",composed.json()}});
        for(int level:{1,10,50}) {
            const auto table=plan.skills.at(key).data->values("[level info]");const auto o=evaluateSourceSkillAction(d,*plan.skills.at(key).data,level);
            check(o.damage.percent==float(*skillLevelValue(table,level,0))&&o.damage.independentPercent==float(*skillLevelValue(table,level,2))&&o.damage.fixedDamage==0,
                "Thrust source percent/independent operands remain separate from flat damage at level "+std::to_string(level));
            check(o.attackSpeedBonusPermille==*skillLevelValue(table,level,1)&&o.evidence.contains("source_speed_tenth_percent"),
                "Thrust speed column is tenths of percent converted to permille, preserving its source UI scaling");
        }
        const auto floor=[&](){world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();r.publishCooldownRestore({});
            world.combat=true;world.freezeAi=true;world.freeCd=false;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};world.blockedRects.clear();
            auto &p=world.player;p.x=p.px=600;p.y=p.py=300;p.z=p.pz=0;p.vx=p.vy=p.vz=0;p.mp=100000;p.dead=false;p.life=ActorLife::Alive;
            p.hp=p.maxHp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;};
        const auto config=[&](int level){r.configuration().configureBasicAttackTemplate(key,level,plan);r.configuration().assignSlot(0,key,plan);};
        const auto press=[&](bool down){world.enqueue({world.simulationNanoseconds(),20,down});};
        for(int level:{1,10})for(int dir:{-1,1})for(bool hit:{false,true}) {
            floor();config(level);world.player.dir=dir;const auto normal=world.skillState().snapshot(world.nowMs());
            const auto binding=r.configuration().binding(key);
            check(binding->unknown.contains("source_body_action_controller")&&!binding->unknown.contains("user_requested_temporary_template"),
                "Test slot uses real Thrust consumer rather than a basic attack preview template");
            auto saved=r.configuration().snapshot();saved["future_mage_unknown"]=17;ExperimentalSkillConfiguration roundtrip(plan);roundtrip.restore(saved,plan);
            check(roundtrip.snapshot()==saved,"Thrust source dispatch and future unknown fields round trip exactly");
            auto tampered=saved;tampered["skill_bindings"][0]["source_body_action_controller"]["motion_slot"]=0;
            bool rejected=false;try{ExperimentalSkillConfiguration invalid(plan);invalid.restore(tampered,plan);}catch(...){rejected=true;}
            check(rejected,"Tampered native-body source binding is rejected");
            if(hit)for(int i=0;i<3;++i){Actor target;target.id=i+1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
                target.x=target.px=600+dir*(first->x+first->w*.5);target.y=target.py=300+first->y+first->h*.5;target.dir=-dir;
                world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");target.hp=target.maxHp=100000000;world.monsters.push_back(std::move(target));}
            world.synchronizeEntityHandles();const auto mp=world.player.mp;press(true);world.advanceSingleTick();press(false);
            const auto cost=r.snapshotDiagnostics().at("last_cost");
            check(mp-world.player.mp==cost.at("mp").at("value").get<int>()&&r.remainingCooldown(key,world.nowMs())==int64_t(std::ceil(cost.at("cooldown_ms").at("value").get<double>())),
                "Actual release commits exact current MP/CD with actual equipped subtype modifiers");
            bool volume=false,pose=false,layers=false,response=false;Json sample;
            for(int tick=0;tick<80;++tick){pose|=world.player.animationPath==d.motion.memberPath;
                layers|=world.player.skillAnimationLayers.size()==2;
                for(const auto &v:world.attackVolumes)if(v.skillId==4){volume=true;
                    check(v.sourceAttack&&v.sourceAttack->source.path==d.attack.memberPath&&v.sourceModifiers&&
                        v.sourceModifiers->percent==float(*skillLevelValue(plan.skills.at(key).data->values("[level info]"),level,0))&&
                        v.sourceModifiers->independentPercent==float(*skillLevelValue(plan.skills.at(key).data->values("[level info]"),level,2))&&v.sourceModifiers->fixedDamage==0,
                        "Real EQU volume carries exact Thrust ATK and both skill coefficients");if(sample.is_null())sample=v.sourceModifiers->snapshot();}
                for(const auto &target:world.monsters)response|=target.animation=="damage1"||target.animation=="damage2"||target.z>0;
                world.advanceSingleTick();}
            size_t contacts=0;for(const auto &event:world.events)if((event.kind=="hit"&&event.name=="experimental_source_skill")||event.kind=="miss")++contacts;
            check(pose&&volume&&layers,"Source Thrust body, weapon contact and both visual consumers actually run");
            check(contacts==(hit?3:0)&&(!hit||response),"Multiple weapon boxes deduplicate real targets and publish real monster response");
            check(!r.attacking()&&world.player.skillAnimationLayers.empty()&&r.snapshotDiagnostics().at("source_body_actions")==0,
                "Normal ANI completion retires Thrust action and owned effects");
            check(world.skillState().snapshot(world.nowMs())==normal,"Experimental Thrust does not change normal learned/advancement ledgers");
            if(hit){const auto damage=world.statReport().at("last_damage");check(damage.at("usable").get<bool>()&&damage.at("sources").at("skill").at("fixed_damage")==0,
                "Real accepted Thrust contact enters unified source damage trace");}
            evidence.push_back({{"phase","world_cast"},{"clock",ani_clock::policyName(clock)},{"level",level},{"direction",dir},{"targets",hit},
                {"contacts",contacts},{"modifiers",sample},{"last_damage",world.statReport().at("last_damage")}});
        }
        // A valid actor with no source weapon must roll back before MP/CD.
        floor();config(1);auto &appearance=const_cast<CharacterAppearance &>(world.characterAppearance());
        auto weapon=appearance.parts.extract("[weapon]");check(!weapon.empty(),"Missing-weapon fault fixture removes an actual equipped layer");
        auto before=world.player.mp;const auto missingWeaponRng=world.randomStreams().snapshot();
        auto missingWeaponIds=world.idSources().snapshot();missingWeaponIds.erase("requests");
        press(true);world.advanceSingleTick();press(false);
        auto afterMissingWeaponIds=world.idSources().snapshot();afterMissingWeaponIds.erase("requests");
        check(world.player.mp==before&&r.remainingCooldown(key,world.nowMs())==0&&!r.attacking()&&
            world.randomStreams().snapshot()==missingWeaponRng&&missingWeaponIds==afterMissingWeaponIds&&world.player.skillAnimationLayers.empty(),
            "Missing real equipped volume rejects costs, action, effects, combat IDs and RNG");
        check(world.experimentalDiagnostics().at("world").back().at("code")=="experimental_attack_source_preflight_rejected",
            "Missing equipped geometry reaches the actual preflight rejection diagnostic");
        appearance.parts.insert(std::move(weapon));
        for(const auto *fault:{"malformed_response","missing_visual"}) {
            floor();auto badPlan=std::make_shared<ExperimentalCharacterPlan>(plan);auto &bad=badPlan->sourceSkillActions.at(key);
            if(std::string(fault)=="malformed_response") {
                for(auto &field:bad.attackDefinition.source.fields)if(normalize(field.tag)=="[hit wav]")field.values=Json::array({42});
            } else bad.bodyLayers.front().source.memberPath="character/mage/effect/animation/__synthetic_missing_thrust.ani";
            ExperimentalCharacterRuntime injected(badPlan);injected.setAnimationClockPolicy(clock);
            injected.configuration().configureBasicAttackTemplate(key,1,*badPlan);injected.configuration().assignSlot(0,key,*badPlan);
            const auto mp=world.player.mp;const auto rng=world.randomStreams().snapshot();auto ids=world.idSources().snapshot();ids.erase("requests");
            CharacterActionRequest request;request.inputKey=20;request.inputDown=true;injected.request(request);
            ExperimentalWorldAdapter adapter(world);adapter.advance(injected,uint64_t(world.tick)+1);
            auto afterIds=world.idSources().snapshot();afterIds.erase("requests");
            check(world.player.mp==mp&&injected.remainingCooldown(key,world.nowMs())==0&&!injected.attacking()&&
                world.randomStreams().snapshot()==rng&&ids==afterIds&&world.player.skillAnimationLayers.empty(),
                std::string("Source preflight fault rolls back Thrust MP/CD/action/visuals/combat IDs/RNG: ")+fault);
            check(world.experimentalDiagnostics().at("world").back().at("code")=="experimental_attack_source_preflight_rejected",
                std::string("Injected Thrust fault reaches source preflight: ")+fault);
            evidence.push_back({{"phase","fault_rollback"},{"fault",fault},{"runtime",injected.snapshotDiagnostics()},
                {"rejection",world.experimentalDiagnostics().at("world").back()}});
        }
        for(const auto *reason:{"cancel","scene","death","blocked"}){
            floor();config(1);press(true);world.advanceSingleTick();press(false);world.advanceSingleTick();
            check(r.attacking(),"Cleanup fixture has a live Thrust action");
            if(std::string(reason)=="cancel")world.idle();else if(std::string(reason)=="scene")world.changeScene();
            else if(std::string(reason)=="blocked")world.player.stunUntil=world.nowMs()+1000;else {world.player.dead=true;world.player.life=ActorLife::Dying;}
            world.advanceSingleTick();check(!r.attacking()&&world.player.skillAnimationLayers.empty()&&r.snapshotDiagnostics().at("source_body_actions")==0,
                std::string("No Thrust body or layers survive ")+reason);}
        floor();config(1);world.player.z=100;before=world.player.mp;press(true);world.advanceSingleTick();press(false);
        check(world.player.mp==before&&!r.attacking(),"Inferred ground admission rejects an airborne Thrust before costs");
        floor();config(1);world.player.mp=0;press(true);world.advanceSingleTick();press(false);
        check(!r.attacking()&&r.remainingCooldown(key,world.nowMs())==0,"MP rejection cannot publish Thrust action");
        auto shared=std::make_shared<ExperimentalCharacterPlan>(plan);ExperimentalCharacterRuntime isolated(shared);isolated.setAnimationClockPolicy(clock);
        isolated.configuration().configureBasicAttackTemplate(key,10,*shared);isolated.configuration().assignSlot(0,key,*shared);
        ExperimentalActorState actor;actor.x=600;actor.y=300;actor.mp=10000;actor.attackPerMille=1700;actor.weaponSubtype=2;
        CharacterActionRequest request;request.action=CharacterAction::CommandInput;request.inputKey=20;request.inputDown=true;isolated.request(request);
        auto out=isolated.advance(1,actor,[](double,double){return true;});actor=out.actor;
        check(out.animationClock&&std::abs(out.animationClock->ratePercent-(clock==ani_clock::ClockPolicy::SourceDelay100?100.:179.3))<.0001,
            "Actual selected Mage action clock consumes tenths-percent speed instead of multiplying it by ten");
        const auto elapsed=out.animationClock->elapsedMs;actor.hitStopped=true;out=isolated.advance(2,actor,[](double,double){return true;});
        check(out.animationClock&&out.animationClock->elapsedMs==elapsed,"Hitstop freezes actual Thrust clock and owned visual time");
        const auto schedule=[&](int fps,bool budgeted){Progression p(regions);World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();
            CharacterStore c(std::filesystem::absolute("mage-schedule-"+std::string(ani_clock::policyName(clock))+"-"+std::to_string(fps)));
            c.data["characters"][0]={{"name","ReplayMage"},{"class","mage"},{"identity",CharacterIdentity{3,0,0}.json()},{"level",1},{"skill_initialization","source-v1"}};
            c.apply(0,w,p);dnf::enterExplicitSkillPreviewFixture(w);w.configureAnimationClock(clock);auto &runtime=*w.experimentalRuntime();runtime.configuration().configureBasicAttackTemplate(key,10,runtime.plan());runtime.configuration().assignSlot(0,key,runtime.plan());
            w.monsters.clear();w.events.clear();w.combat=true;w.freezeAi=true;w.mapWidth=3000;w.walkRects={{0,185,3000,600}};w.player.x=w.player.px=600;w.player.y=w.player.py=300;w.player.mp=10000;w.randomStreams()=RandomStreams(0x1031);
            Actor t;t.id=1;t.sourceId=10;t.monsterPath="monster/goblin/goblin.mob";t.x=t.px=670;t.y=t.py=300;w.initializeMonsterAttributes(t,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");t.hp=t.maxHp=100000000;w.monsters.push_back(std::move(t));w.synchronizeEntityHandles();
            w.enqueue({0,20,true});w.enqueue({16666667,20,false});Json frames=Json::array();w.setObjectTick([&](World &v){frames.push_back({{"tick",v.tick},{"mp",v.player.mp},{"diagnostic",runtime.snapshotDiagnostics()},
                {"hp",v.monsters[0].hp},{"position",{v.monsters[0].x,v.monsters[0].y,v.monsters[0].z}},{"animation",v.monsters[0].animationPath},{"events",v.eventLog()},{"rng",v.randomStreams().snapshot()}});});
            constexpr int64_t total=2000000000;int64_t prev=0;if(budgeted){w.advance(total,8);while(w.pendingTicks())w.advance(0,8);}
            else for(int f=1;f<=fps*2;++f){auto now=total*f/(fps*2);w.advance(now-prev);prev=now;}
            check(w.tick==120&&w.pendingTicks()==0,"Every fixed Thrust tick completes under render pump");return frames;};
        const auto reference=schedule(60,false);for(int fps:{30,144})check(schedule(fps,false)==reference,"Source Thrust fixed results agree at FPS "+std::to_string(fps));
        check(schedule(1,true)==reference,"Budget8 catchup preserves every Thrust contact/cost/response/cleanup tick");
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},{"full_skill_complete",false},{"normal_learning_consumer_bound",false},{"native_dynamic_parity",false}};
    }catch(const std::exception &error){writeJson("mage-thrust-exception.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence}});throw;}
}
}
