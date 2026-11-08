#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/storage.hpp"
#include "dnf/skill_input_policy.hpp"
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
Json runGunnerBasicRuntimeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();RegionCatalog regions(pvf,assets);
    const auto check=[&](bool pass,const std::string &message) {
        checks.push_back({{"passed",pass},{"message",message}});
        if(!pass)throw std::runtime_error("Source Gunner: "+message);
    };
    try {
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("gunner-basic-fixture-"+std::string(ani_clock::policyName(clock))));
        store.data["characters"][0]={{"name","GunnerBasic"},{"class","gunner"},{"identity",CharacterIdentity{2,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};
        store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clock);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        const auto floor=[&]() {
            world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
            world.combat=true;world.freezeAi=true;world.freeCd=true;world.mapWidth=4000;world.walkRects={{0,185,4000,800}};
            world.blockedRects.clear();auto &p=world.player;p.x=p.px=1400;p.y=p.py=400;p.z=p.pz=p.vz=0;p.dir=1;
            p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.mp=p.maxMp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;
        };
        const auto press=[&](int key,bool down){world.enqueue({world.simulationNanoseconds(),key,down});};
        const auto bullets=[&]() {
            Json rows=Json::array();for(const auto &fx:world.effects)if(fx.phase=="female-gunner:ordinary_bullet")
                rows.push_back({{"id",fx.id},{"born",fx.born},{"expires",fx.expires},{"x",fx.x},{"y",fx.y},{"z",fx.z},{"source",fx.projectileSource}});
            return rows;
        };
        const Field *table=nullptr;
        for(const auto &field:plan.characterDefinition.settings.script.fields)if(field.tag=="[key value index]"&&!field.values.empty()&&
            (field.values[0]=="weaponSubTypeIndex"||field.values[0]=="defaultWeaponBySubType"))table=&field;
        check(table!=nullptr,"Current male settings retain the actual starter equipment by subtype table");
        check(plan.gunnerBasicSources.size()==5,"All five distinct source GunInfo integer blocks are loaded");
        for(int subtype=0;subtype<5;++subtype) {
            floor();int equipment=-1;
            for(size_t i=2;i+1<table->values.size();i+=2)if(table->values[i]==subtype)equipment=table->values[i+1].get<int>();
            const auto *item=progression.item(equipment);check(item!=nullptr,"Source male default equipment exists");
            while(progression.level()<item->minimumLevel)progression.addExperience(progression.experienceToNextLevel());
            const auto uid=progression.state.at("next_uid").get<int>();const auto index=int(progression.state.at("inventory").size());
            progression.state["next_uid"]=uid+1;progression.state["inventory"].push_back({{"uid",uid},{"id",equipment},{"count",1},{"durability",item->durability}});
            const auto equipped=world.changeEquipment(progression,index);check(equipped.ok,"Actual male EQU/LAY transaction equips subtype "+std::to_string(subtype));
            for(int direction:{-1,1}) {
                floor();world.player.dir=direction;const auto normal=world.skillState().snapshot(world.nowMs());const int mp=world.player.mp;
                const auto maximum=plan.gunnerBasicSources.at(subtype).values[0];
                std::set<uint64_t> shotIds;std::set<std::string> motions;Json shots=Json::array();Json previousGround;
                bool earlyBullet=false,sawReload=false,sawFinalRaise=false,sawFinalShoot=false;
                bool exactShotTicks=true,exactRaiseBoundary=true;Json transitions=Json::array();
                press(4,true);world.advanceSingleTick();press(4,false);
                check(bullets().empty(),"Initial raise creates no immediate male projectile");
                for(int tick=0;tick<600;++tick) {
                    auto diagnostics=runtime.snapshotDiagnostics();const auto ground=diagnostics.at("gunner_ground");
                    if(!ground.is_null()&&ground.at("phase")==1&&ground.at("emitted")==true) {
                        // Distinct X events; OS repeats remain one held press.
                        if(previousGround.is_null()||previousGround.at("action")!=diagnostics.at("action_sequence")) {
                            press(4,true);press(4,true);press(4,false);
                            previousGround={{"action",diagnostics.at("action_sequence")}};
                        }
                    }
                    const auto beforeTick=world.tick,beforeMs=world.nowMs();
                    world.advanceSingleTick();motions.insert(world.player.animationPath);
                    sawFinalRaise|=world.player.animationPath=="character/gunner/animation/attack2.ani";
                    sawFinalShoot|=world.player.animationPath=="character/gunner/animation/attack2shootup.ani";
                    sawReload|=world.player.animationPath=="character/gunner/animation/reload.ani";
                    const auto current=runtime.snapshotDiagnostics().at("gunner_ground");
                    size_t bornThisTick=0;
                    for(const auto &row:bullets())if(shotIds.insert(row.at("id").get<uint64_t>()).second) {
                        ++bornThisTick;exactShotTicks&=row.at("born")==world.nowMs();
                        shots.push_back(row);const auto &source=row.at("source");
                        earlyBullet|=source.at("coordinate_trace").at("body").at("member_path").get<std::string>().find("shootup.ani")==std::string::npos;
                        const auto &motion=source.at("basic_particle_motion");
                        check(row.at("expires").get<int64_t>()-row.at("born").get<int64_t>()==motion.at("lifetime_ms"),"Published male bullet expires at actual source PTL lifetime");
                        check(source.at("key").at("job_id")==2,"Published basic projectile retains actual male identity");
                    }
                    if(!ground.is_null()) {
                        const int phase=ground.at("phase");const auto elapsed=ground.at("elapsed_ms").get<int64_t>()+world.nowMs()-beforeMs;
                        const bool expectedShot=(phase==1||phase==3)&&!ground.at("emitted").get<bool>()&&
                            elapsed>=ground.at("deadlines").at("shot_ms").get<int64_t>();
                        exactShotTicks&=bornThisTick==size_t(expectedShot);
                        const bool changed=current.is_null()||current.at("phase")!=phase;
                        if(phase==0||phase==2) {
                            const auto *raise=plan.motion("[attack motion]",phase==0?0:1);
                            const auto &source=*plan.animations.at(raise->source.memberPath);
                            const bool last=world.player.animationClock&&world.player.animationClock->frame==source.frames.size()-1;
                            exactRaiseBoundary&=world.player.animationPath==raise->source.memberPath&&changed==last&&bornThisTick==0;
                        }
                        if(changed||bornThisTick)transitions.push_back({{"tick_before",beforeTick},{"tick",world.tick},
                            {"ms",world.nowMs()},{"delta_ms",world.nowMs()-beforeMs},{"before",ground},{"after",current},
                            {"expected_shot",expectedShot},{"birth_count",bornThisTick},{"body_source",world.player.animationPath},
                            {"frame",world.player.animationClock?Json(world.player.animationClock->frame):Json()}});
                    }
                    if(sawReload&&!runtime.attacking())break;
                }
                evidence.push_back({{"clock",ani_clock::policyName(clock)},{"subtype",subtype},{"direction",direction},
                    {"maximum",maximum},{"shots",shots},{"motions",motions},{"transitions",transitions},{"diagnostics",runtime.snapshotDiagnostics()}});
                check(exactShotTicks,"Source scheduledShot births exactly on the first fixed tick crossing its deadline; no Raise or recovery tick emits");
                check(exactRaiseBoundary,"Source phase0/2 advance on entering the final source frame on that exact tick without waiting its held DELAY");
                check(shotIds.size()==size_t(maximum),"Distinct source-gated X chain reaches every scheduled shot including third/final");
                check(!earlyBullet,"Only actual shoot phase owns male projectile birth");
                check((maximum==1||sawFinalRaise)&&sawFinalShoot&&sawReload&&!runtime.attacking(),"Source shot budget reaches final Shoot and finite Reload; multi-shot chains include final Raise");
                check(world.player.mp==mp&&world.skillState().snapshot(world.nowMs())==normal,"Male ordinary source stages preserve MP and normal learning ledger");
                // A single press with arbitrary OS repeats never makes a chain.
                floor();press(4,true);std::set<int> repeatedShots;
                for(int tick=0;tick<90;++tick) {press(4,true);world.advanceSingleTick();for(const auto &row:bullets())repeatedShots.insert(row.at("id").get<int>());}
                check(repeatedShots.size()==1&&!runtime.attacking(),"OS key repeat cannot queue extra male shots or prevent finite recovery");
                press(4,false);
            }
            // Follow an actual published entity, not only a parser output.
            floor();press(4,true);world.advanceSingleTick();press(4,false);Json flight;
            for(int tick=0;tick<90&&flight.is_null();++tick) {
                world.advanceSingleTick();const auto live=bullets();if(!live.empty())flight=live.front();
            }
            check(!flight.is_null(),"Source scheduledShot has a live independently timed projectile");
            const auto sourcePath=flight.at("source").at("basic_particle_motion").at("source").at("member_path").get<std::string>();
            const auto particle=readGunnerBasicParticle(pvf,pvf.script(sourcePath));
            const auto startAge=world.nowMs()-flight.at("born").get<int64_t>();
            const double startX=flight.at("x");
            for(int tick=0;tick<6;++tick)world.advanceSingleTick();
            Json followed;for(const auto &row:bullets())if(row.at("id")==flight.at("id"))followed=row;
            const auto endAge=world.nowMs()-flight.at("born").get<int64_t>();
            const auto startDelta=particle.displacement(int32_t(startAge)),endDelta=particle.displacement(int32_t(endAge));
            check(!followed.is_null()&&std::abs(followed.at("x").get<double>()-startX-(endDelta[0]-startDelta[0]))<.001,
                "Actual entity displacement consumes source PTL float32 integral instead of fixed1200");
            check(subtype!=3||particle.axisVelocity==std::array<int32_t,3>{},"Handcannon without straight-line axes remains a separate stationary source entity");
            evidence.push_back({{"phase","actual_ptl_flight"},{"subtype",subtype},{"first",flight},{"later",followed},{"particle",particle.snapshot()}});
            if(subtype==0)for(const int direction:{-1,1})for(const double distance:{100.,200.,300.})for(const bool airborne:{false,true}) {
                floor();world.player.dir=direction;
                Actor target;target.id=1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
                target.x=target.px=world.player.x+direction*distance;target.y=target.py=world.player.y;target.dir=-direction;
                world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
                if(airborne){target.z=target.pz=80;target.hitStopTicks=1000000;}
                target.hp=target.maxHp=100000000;world.monsters.push_back(std::move(target));
                world.synchronizeEntityHandles();press(4,true);world.advanceSingleTick();press(4,false);
                for(int tick=0;tick<90;++tick)world.advanceSingleTick();
                size_t hits=0;for(const auto &target:world.monsters)hits+=target.hp<target.maxHp;
                evidence.push_back({{"phase","actual_male_ground_goblin_aim"},{"direction",direction},{"distance",distance},
                    {"airborne",airborne},{"air_fixture","Initial z80 with actual hitpause to freeze physical flight; no changed source geometry"},
                    {"hp",world.monsters.front().hp},{"world",world.femaleGunnerDiagnostics()}});
                check(hits==1,"Source male projectile with classified aim reaches an unchanged "+std::string(airborne?"airborne":"ground")+" Goblin type14 box at distance "+std::to_string(int(distance)));
                size_t contacts=0;for(const auto &event:world.events)contacts+=event.kind=="hit_feedback";
                check(contacts==1,"One male source attack instance accepts at most one contact on its aimed target");
            }
        }
        // The recovered 60Hz integer-ms clock has three distinct 16/17ms
        // phases. Compare exact replays within each phase, and independently
        // require the source frame at the exact local elapsed time at every
        // phase. Cross-phase bit equality would contradict that clock contract.
        const auto *jumpMotion=plan.motion("[jump motion]");
        check(jumpMotion!=nullptr,"Male jump retains its actual CHR source binding");
        const auto &jumpAnimation=*plan.animations.at(jumpMotion->source.memberPath);
        std::map<int,Json> jumpReference;
        for(int entryPhase:{0,1,2,0,1,2}) {
            floor();for(int tick=0;tick<7+entryPhase;++tick)world.advanceSingleTick();
            while((world.tick+1)%3!=entryPhase)world.advanceSingleTick();
            press(5,true);world.advanceSingleTick();press(5,false);
            const auto entryTick=world.tick,entryMs=world.nowMs();Json frames=Json::array();
            for(int tick=0;tick<20;++tick) {
                const auto jump=runtime.snapshotDiagnostics().at("jump_locomotion_clock");
                const auto elapsed=world.nowMs()-entryMs;
                frames.push_back({world.player.z,jump});
                evidence.push_back({{"phase","jump_entry_clock"},{"clock",ani_clock::policyName(clock)},
                    {"entry_tick",entryTick},{"entry_clock_phase",entryPhase},{"tick",world.tick},
                    {"local_elapsed_ms",elapsed},{"source",jumpMotion->source.json()},{"sample",frames.back()}});
                check(!jump.is_null()&&jump.at("elapsed_ms")==elapsed&&
                    jump.at("frame")==jumpAnimation.frameAt(elapsed,false),
                    "Jump clock exactly consumes local elapsed milliseconds and the unmodified source frame at every integer-clock phase");
                check(world.player.animationPath==jumpMotion->source.memberPath&&world.player.animationClock&&
                    world.player.animationClockSource==jumpMotion->source.memberPath&&
                    world.player.animationClock->elapsedMs==uint64_t(elapsed)&&
                    world.player.animationClock->frame==jumpAnimation.frameAt(elapsed,false),
                    "Actual body and equipment receive the same exact local jump source snapshot");
                world.advanceSingleTick();
            }
            if(!jumpReference.count(entryPhase))jumpReference[entryPhase]=frames;
            else check(frames==jumpReference.at(entryPhase),
                "Jump frames and height replay bit-exactly at different absolute entry ticks with the same recovered millisecond phase");
        }
        floor();press(5,true);world.advanceSingleTick();press(5,false);world.advanceSingleTick();
        const auto pausedJump=runtime.snapshotDiagnostics().at("jump_locomotion_clock");const auto pausedHeight=world.player.z;
        world.player.hitStopTicks=4;
        for(int tick=0;tick<3;++tick) {
            world.advanceSingleTick();
            check(world.player.z==pausedHeight&&runtime.snapshotDiagnostics().at("jump_locomotion_clock")==pausedJump,
                "Hitstop preserves exact jump height and source frame/elapsed snapshot");
        }
        for(const char *cancel:{"scene","dead","interrupted"}) {
            floor();press(4,true);world.advanceSingleTick();press(4,false);
            if(std::string(cancel)=="scene")world.changeScene();
            else if(std::string(cancel)=="dead"){world.player.dead=true;world.player.life=ActorLife::Dying;}
            else world.player.recovery=10;
            for(int tick=0;tick<90;++tick)world.advanceSingleTick();
            check(bullets().empty(),std::string("No delayed scheduled male shot survives ")+cancel);
        }
        floor();const auto goodAppearance=world.characterAppearance();auto broken=goodAppearance;broken.bodyMotions.clear();
        world.setCharacterAppearance(std::move(broken));const auto rngBefore=world.randomStreams().snapshot();const int mpBefore=world.player.mp;
        const auto sequenceBefore=runtime.snapshotDiagnostics().at("action_sequence");press(4,true);world.advanceSingleTick();press(4,false);
        check(!runtime.attacking()&&bullets().empty()&&world.player.mp==mpBefore&&world.randomStreams().snapshot()==rngBefore&&
            runtime.snapshotDiagnostics().at("action_sequence")==sequenceBefore,"Failed actual body source preflight publishes no male action, bullet, MP or RNG");
        world.setCharacterAppearance(goodAppearance);press(4,true);world.advanceSingleTick();press(4,false);
        check(runtime.attacking(),"A new explicit male request recovers after appearance source repair");
        std::optional<SkillKey> defaultZ;
        for(const auto &[key,row]:plan.skills)if(row.data&&sourceBaseDefaultSkillCommand(*row.data,0)) {
            if(defaultZ)throw std::runtime_error("Ambiguous male default Z fixture");defaultZ=key;
        }
        check(bool(defaultZ),"Actual male SKL defines a unique default Z skill");
        floor();runtime.configuration().configureBasicAttackTemplate(*defaultZ,1,plan);const int zMp=world.player.mp;
        press(4,true);world.advanceSingleTick();press(4,false);press(6,true);world.advanceSingleTick();press(6,false);
        bool zConsumed=false;for(int tick=0;tick<150;++tick){world.advanceSingleTick();zConsumed|=world.player.mp<zMp;}
        check(zConsumed,"Buffered source default Z survives internal Raise-to-Shoot stage identity and releases on recovery");

        floor();runtime.setGunnerTargetAimEnabled(false);press(4,true);world.advanceSingleTick();press(4,false);
        Json detached;
        for(int tick=0;tick<90&&detached.is_null();++tick){world.advanceSingleTick();const auto live=bullets();if(!live.empty())detached=live.front();}
        check(!detached.is_null()&&detached.at("source").at("basic_aim").at("target").is_null(),
            "Source-centerline strategy remains directly selectable and retains target-free projectile receipt");
        const auto detachedParticle=readGunnerBasicParticle(pvf,pvf.script(detached.at("source").at("basic_particle_motion").at("source").at("member_path").get<std::string>()));
        const auto originAge=int32_t(world.nowMs()-detached.at("born").get<int64_t>());const auto originDelta=detachedParticle.displacement(originAge);
        const double playerOrigin=world.player.x;bool fixedOrigin=true,moved=false;press(1,true);
        for(int tick=0;tick<60;++tick) {
            world.advanceSingleTick();moved|=world.player.x!=playerOrigin;
            for(const auto &row:bullets())if(row.at("id")==detached.at("id")) {
                const auto delta=detachedParticle.displacement(int32_t(world.nowMs()-row.at("born").get<int64_t>()));
                fixedOrigin&=std::abs(row.at("x").get<double>()-detached.at("x").get<double>()-(delta[0]-originDelta[0]))<.001;
            }
        }
        check(moved&&fixedOrigin,"Actual player direction input resumes after recovery without dragging the independently moving source projectile");
        press(1,false);floor();runtime.setGunnerTargetAimEnabled(true);

        Json scheduleReference;
        for(int fps:{60,30,144,0}) {
            World replay(pvf,assets,WorldRules::BetaFoundationV1);replay.enableExperimentalCharacters();Progression replayProgression(regions);
            CharacterStore replayStore(std::filesystem::absolute("gunner-schedule-"+std::string(ani_clock::policyName(clock))+"-"+std::to_string(fps)));
            replayStore.data["characters"][0]={{"name","GunnerSchedule"},{"class","gunner"},{"identity",CharacterIdentity{2,0,0}.json()},
                {"level",1},{"skill_initialization","source-v1"}};replayStore.apply(0,replay,replayProgression);dnf::enterExplicitSkillPreviewFixture(replay);replay.configureAnimationClock(clock);
            replay.changeScene();replay.monsters.clear();replay.events.clear();replay.releaseInputs();replay.idle();
            replay.combat=true;replay.freezeAi=true;replay.mapWidth=4000;replay.walkRects={{0,185,4000,800}};
            replay.player.x=replay.player.px=1400;replay.player.y=replay.player.py=400;replay.player.z=replay.player.pz=replay.player.vz=0;
            replay.player.dir=1;
            for(int index=0;index<8;++index) {
                replay.enqueue({int64_t(index)*200000000,4,true});replay.enqueue({int64_t(index)*200000000+20000000,4,false});
            }
            replay.enqueue({1800000000,5,true});replay.enqueue({1820000000,5,false});
            Json trace=Json::array();replay.setObjectTick([&](World &w) {
                Json effects=Json::array();for(const auto &fx:w.effects)effects.push_back({fx.id,fx.animation,fx.born,fx.expires,fx.x,fx.y,fx.z});
                auto diagnostics=w.experimentalRuntime()->snapshotDiagnostics();diagnostics.erase("source_diagnostics");
                trace.push_back({{"tick",w.tick},{"pose",{w.player.animationPath,w.player.poseFrame}},{"xyz",{w.player.x,w.player.y,w.player.z}},
                    {"effects",effects},{"runtime",std::move(diagnostics)},
                    {"ids",w.simulationCheckpoint().at("ids")},{"rng",w.randomStreams().snapshot()}});
            });
            if(fps==0) {replay.advance(3000000000,8);while(replay.pendingTicks())replay.advance(0,8);}
            else for(int frame=0;frame<fps*3;++frame)replay.advance(3000000000LL*(frame+1)/(fps*3)-3000000000LL*frame/(fps*3));
            if(scheduleReference.is_null())scheduleReference=trace;
            else check(trace==scheduleReference,"Male source phases/shot timing/PTL and jump tick trace agree for render FPS "+std::to_string(fps));
        }
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"classification","1031 source default GunInfo and phase schedule with inferred input/Reload exit/centerline host"},
        {"original_dynamic_comparison","pending_user"}};
    }catch(const std::exception &error) {writeJson("gunner-basic-runtime-failed.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence}});throw;}
}
}
