#include "dnf/female_gunner_timing.hpp"
#include "dnf/experimental_character.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
Json runFemaleGunnerTimingTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),failures=Json::array(),sources=Json::array();
    const auto check=[&](bool passed,const std::string &message) {
        checks.push_back({{"passed",passed},{"message",message}});if(!passed)failures.push_back(message);
    };
    const auto rejects=[&](const auto &work,const char *message) {
        bool rejected=false;try{work();}catch(const std::invalid_argument &){rejected=true;}check(rejected,message);
    };
    CharacterCatalog catalog(pvf);const auto plan=loadExperimentalCharacterPlan(pvf,assets,catalog,{5,0,0});
    const auto build=[&](int id,size_t stageIndex,uint32_t presses=0) {
        const auto &d=plan.femaleGunnerSkills.at({5,id});
        auto c=evaluateFemaleGunnerSkill(d,*plan.skills.at({5,id}).data,1,0);
        const auto &s=d.stages.at(stageIndex);const auto *m=plan.motion(s.motionTag,s.motionSlot);
        if(!m)throw std::logic_error("Source timing test has no stage motion");
        const auto animation=plan.animations.at(m->source.memberPath);
        auto t=buildFemaleGunnerStageTiming(c,s,*animation,presses);
        applyFemaleGunnerStageTiming(c,t);return std::make_pair(std::move(c),std::move(t));
    };
    const auto wait=build(9,0),normal=build(9,1),accelerated=build(9,1,10);
    check(wait.second.sourceDurationMs==50&&!wait.second.controlled&&wait.second.runtimeDelays==wait.second.sourceDelays,
        "RandomShoot Wait remains the exact authored 50ms, never 50 seconds");
    check(wait.first.count==12&&wait.first.intervalMs==250&&wait.first.lifetimeMs==3000,
        "Initial Wait already resolves source minimum12 and static250ms to one 3000ms command");
    check(normal.second.sourceDurationMs==62400&&normal.second.sourceDelays.size()==20,
        "Current1031 RandomShoot really contains20 frames and four15000ms controller holds");
    check(normal.second.controlled&&!normal.second.repeatAnimation&&normal.second.runtimeDurationMs==3000,
        "RandomShoot has a finite full-frame controller schedule independent of its62400ms raw span");
    check(normal.first.count==12&&normal.first.intervalMs==250&&normal.first.lifetimeMs==3000,
        "Body and entity schedule share minimum count and interval; bleeding4000ms does not become action duration");
    check(accelerated.first.count==20&&accelerated.first.intervalMs==63&&accelerated.first.lifetimeMs==1260,
        "Ten source-defined distinct Attack presses reach source maximum20 with inferred300percent acceleration");
    check(accelerated.second.runtimeDelays.size()==20,
        "Accelerated RandomShoot still retains all20 source frame identities");
    const auto capped=build(9,1,UINT32_MAX);
    check(capped.first.count==accelerated.first.count&&capped.first.intervalMs==accelerated.first.intervalMs,
        "Press count saturates at source threshold without integer wrap");
    const auto &d=plan.femaleGunnerSkills.at({5,9});const auto *motion=plan.motion(d.stages[1].motionTag,d.stages[1].motionSlot);
    const auto source=plan.animations.at(motion->source.memberPath);
    check(source->duration==62400&&source->frames.at(4).duration==15000&&source->frames.at(19).duration==15000,
        "Building and applying controller timelines leaves original ANI frame bytes/delays immutable");
    for(const auto policy:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        const auto &delays=normal.second.runtimeDelays;ani_clock::Cursor cursor;
        auto first=cursor.install({delays.data(),delays.size(),false},100,policy,0);
        std::set<size_t> visits;for(const auto &v:first.visits)visits.insert(v.frame);
        uint64_t tick=0;int64_t elapsed=0;
        while(!cursor.snapshot().ended&&tick<250) {
            ++tick;const uint32_t dt=uint32_t(tick*1000/60-(tick-1)*1000/60);
            elapsed+=dt;auto step=cursor.advance({tick,dt,false});for(const auto &v:step.visits)visits.insert(v.frame);
        }
        check(cursor.snapshot().ended&&tick<=181&&visits.size()==20,
            "Both clock policies visit every RandomShoot source frame and finish in source pulse deadline");
        check(!femaleGunnerStageTimingComplete(normal.second,10,false)&&femaleGunnerStageTimingComplete(normal.second,elapsed,true),
            "Finite controller stage waits for complete cursor, not first long hold or unrelated elapsed threshold");
    }
    for(const int id:{10,12,13,36,96,97,107}) {
        const auto &descriptor=plan.femaleGunnerSkills.at({5,id});
        size_t hold=0;for(size_t i=0;i<descriptor.stages.size();++i)if(descriptor.stages[i].holdForCommandLifetime)hold=i;
        const auto phase=build(id,hold);sources.push_back({{"skill",id},{"timing",phase.second.snapshot()}});
        check(phase.second.controlled&&phase.second.repeatAnimation&&phase.second.completionAfterMs==phase.first.lifetimeMs&&phase.first.lifetimeMs>0,
            "Channel/guard phase has one exact command lifetime and independent visual cycle: "+std::to_string(id));
        check(!femaleGunnerStageTimingComplete(phase.second,phase.first.lifetimeMs-1,true)&&
              femaleGunnerStageTimingComplete(phase.second,phase.first.lifetimeMs,false),
            "Source ANI ended cannot end channel early; command deadline ends a looping ANI: "+std::to_string(id));
        const auto &delays=phase.second.runtimeDelays;ani_clock::Cursor cursor;
        cursor.install({delays.data(),delays.size(),true},100,ani_clock::ClockPolicy::SourceDelay100,0);
        auto before=cursor.snapshot();cursor.advance({1,16,true});
        check(cursor.snapshot().elapsedMs==before.elapsedMs,
            "Hitstop/pause does not consume channel animation time: "+std::to_string(id));
    }
    for(const int id:{5,20,47}) {
        const auto phase=build(id,0);
        check(phase.second.controlled&&phase.second.runtimeDelays.back()==0&&phase.second.sourceDelays.back()>=9999&&
              phase.second.runtimeDurationMs<1000&&phase.second.runtimeDelays.size()==phase.second.sourceDelays.size(),
            "Named basic-motion bullet skill retains full frame sequence and exits its tail controller hold: "+std::to_string(id));
    }
    const auto punisher=build(6,1),buster=build(109,1),ordinary=build(35,0);
    check(punisher.second.controlled&&punisher.first.lifetimeMs==punisher.second.runtimeDurationMs&&punisher.second.runtimeDurationMs<30000,
        "Punisher body held frames and evaluated shot entity use one finite timeline");
    check(buster.second.controlled&&buster.second.sourceDurationMs==11020&&buster.second.runtimeDurationMs==1080,
        "ChargeBuster visits all18 authored frames without waiting in its10000ms control pose");
    check(!ordinary.second.controlled&&ordinary.second.sourceDelays==ordinary.second.runtimeDelays,
        "Ordinary finite skill ANI is unchanged by controller policies");
    auto malformed=normal.first;malformed.rawTables["static_data"][0]=0;
    rejects([&]{buildFemaleGunnerStageTiming(malformed,d.stages[1],*source);},"Zero source shot interval is rejected before release");
    malformed=normal.first;malformed.parameters=Json::array();
    rejects([&]{buildFemaleGunnerStageTiming(malformed,d.stages[1],*source);},"Missing exact source count operands cannot silently become20 or80ms");
    rejects([&]{femaleGunnerStageTimingComplete(normal.second,-1,false);},"Negative controller elapsed time is rejected");
    auto reapplied=normal.first;applyFemaleGunnerStageTiming(reapplied,normal.second);const auto one=reapplied.snapshot();
    applyFemaleGunnerStageTiming(reapplied,normal.second);
    check(reapplied.snapshot()==one,"Retry/stage timing application replaces its receipt and never adds a duplicate command/effect");
    {
        const auto flame=build(13,1),gatling=build(12,1);
        const auto hold=femaleGunnerChannelContract(flame.first),press=femaleGunnerChannelContract(gatling.first);
        check(hold.mode==FemaleGunnerChannelInputMode::HoldAttack&&hold.maximumMs==2500,
            "M3 exact source establishes ATTACK hold/release with source2500ms maximum");
        auto state=beginFemaleGunnerChannel(hold);
        advanceFemaleGunnerChannel(hold,state,100,true,false,false);
        check(!state.stopped,"Holding ATTACK retains an active M3 channel without recharging or republishing it");
        advanceFemaleGunnerChannel(hold,state,150,false,false,false);
        check(state.stopped&&state.reason=="attack_released","ATTACK KEYUP ends M3 before its maximum");
        advanceFemaleGunnerChannel(hold,state,160,true,true,false);
        check(state.stopped,"A stopped M3 channel never resurrects on a later ATTACK DOWN");
        state=beginFemaleGunnerChannel(hold);advanceFemaleGunnerChannel(hold,state,2500,true,false,false);
        check(state.stopped&&state.reason=="source_maximum","Holding ATTACK cannot exceed M3's exact source maximum");
        check(femaleGunnerChannelRecoveryMs(hold,0)==400&&femaleGunnerChannelRecoveryMs(hold,1250)==600&&
              femaleGunnerChannelRecoveryMs(hold,2500)==800&&femaleGunnerChannelRecoveryMs(hold,INT32_MAX)==800,
            "Explicit inferred M3 recovery consumes source400..800 bounds and actual spray span without overflow");
        check(press.mode==FemaleGunnerChannelInputMode::PressAttackToExtend&&press.initialMs==700&&press.jumpStops,
            "Gatling source repeated-ATTACK/JUMP contract is separate from M3 hold; unnamed static1 renewal window is inferred");
        state=beginFemaleGunnerChannel(press);advanceFemaleGunnerChannel(press,state,300,true,false,false);
        check(state.deadlineMs==700,"A held key without a distinct DOWN never extends Gatling's input window");
        advanceFemaleGunnerChannel(press,state,500,true,true,false);
        check(state.deadlineMs==1200&&!state.stopped,"Distinct ATTACK DOWN renews Gatling to elapsed plus source-derived700ms");
        advanceFemaleGunnerChannel(press,state,1100,true,true,false);
        advanceFemaleGunnerChannel(press,state,1700,true,true,false);
        check(state.deadlineMs==press.maximumMs,"Rapid presses cannot extend Gatling beyond its authored maximum");
        advanceFemaleGunnerChannel(press,state,1750,true,false,true);
        check(state.stopped&&state.reason=="jump_pressed","Source JUMP input ends Gatling immediately");
        state=beginFemaleGunnerChannel(press);advanceFemaleGunnerChannel(press,state,700,true,true,false);
        check(state.stopped&&state.reason=="input_window_expired","A late press cannot revive an already-expired Gatling window");
        for(const int id:{36,107}) {
            const auto userHold=femaleGunnerChannelContract(build(id,1).first);
            check(userHold.mode==FemaleGunnerChannelInputMode::HoldReleaseKey&&!userHold.evidence.empty(),
                "Explicit user strategy holds the actual initiating key for focus/ice without changing M3 ATTACK: "+std::to_string(id));
        }
        auto command=flame.first;command.actionSequence=73;
        const auto stopped=stopFemaleGunnerChannel(command,"attack_released");
        check(stopped.kind==FemaleGunnerCommandKind::Clear&&stopped.effectRole=="stop_channel"&&stopped.actionSequence==73&&
              stopped.key==command.key&&!stopped.animationSource&&!stopped.attackSource&&!stopped.box&&!stopped.preflightOnly,
            "Channel exit publishes one nondamaging exact-action Clear rather than a new launch");
        rejects([&]{auto invalid=command;invalid.actionSequence=0;stopFemaleGunnerChannel(invalid,"released");},
            "Unowned channel cancellation is rejected before publication");
        rejects([&]{femaleGunnerChannelRecoveryMs(hold,-1);},"Negative channel recovery time is rejected");
        sources.push_back({{"skill",13},{"channel_input",hold.snapshot()}});
        sources.push_back({{"skill",12},{"channel_input",press.snapshot()}});
    }
    for(const auto policy:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        const auto sharedPlan=std::make_shared<ExperimentalCharacterPlan>(plan);
        const auto input=[](int key,bool down) {CharacterActionRequest r;r.inputKey=key;r.inputDown=down;
            r.action=key==5?CharacterAction::Jump:CharacterAction::BasicAttack;return r;};
        const auto configure=[&](ExperimentalCharacterRuntime &runtime,int id) {
            runtime.setAnimationClockPolicy(policy);runtime.configuration().configureFemaleGunnerSourceSkill({5,id},1,plan);
            runtime.configuration().assignSlot(0,SkillKey{5,id},plan);
            auto skill=input(20,true);skill.action=CharacterAction::Skill;skill.skill=SkillKey{5,id};runtime.request(skill);
        };
        {
            ExperimentalCharacterRuntime runtime(sharedPlan);configure(runtime,13);runtime.request(input(4,true));
            ExperimentalActorState actor;actor.x=400;actor.y=300;actor.mp=1000000;actor.weaponSubtype=0;actor.noCooldown=true;
            uint64_t tick=0,launchAction=0;size_t launches=0,stops=0;bool entered=false;double age=0;
            const auto advance=[&]() {
                auto out=runtime.advance(++tick,actor,[](double,double){return true;});actor=out.actor;
                for(const auto &c:out.femaleGunnerCommands)if(!c.preflightOnly) {
                    if(c.kind==FemaleGunnerCommandKind::Clear&&c.effectRole=="stop_channel")++stops;
                    else if(c.kind==FemaleGunnerCommandKind::Launch){++launches;launchAction=c.actionSequence;}
                }
                return out;
            };
            for(int i=0;i<200&&!entered;++i){auto out=advance();entered=runtime.snapshotDiagnostics().at("channel_input").at("contract").is_object();age=out.animationAgeMs;}
            check(entered&&launches==1&&launchAction>0,"Actual runtime enters M3 held phase and emits exactly one owned channel launch");
            for(int i=0;i<6;++i){auto out=advance();age=out.animationAgeMs;}
            const auto mp=actor.mp;actor.hitStopped=true;runtime.request(input(4,false));
            bool pausedClean=true;
            for(int i=0;i<3;++i){const auto out=advance();pausedClean&=out.animationAgeMs==age&&out.femaleGunnerCommands.empty();}
            check(pausedClean&&stops==0,"Actual hitstop keeps M3 phase/clock fixed and defers a queued ATTACK release until resume");
            actor.hitStopped=false;const auto stopped=advance();uint64_t stoppedAction=0;
            for(const auto &c:stopped.femaleGunnerCommands)if(c.effectRole=="stop_channel")stoppedAction=c.actionSequence;
            check(stops==1&&stoppedAction==launchAction&&stopped.state=="female_gunner_channel_recovery"&&stopped.attacks.empty(),
                "Resumed ATTACK release atomically cancels the exact launched M3 action and enters nondamaging recovery");
            const auto recovery=runtime.snapshotDiagnostics().at("channel_input").at("recovery_remaining_ms").get<int64_t>();
            actor.hitStopped=true;const auto pausedRecovery=advance();
            check(runtime.snapshotDiagnostics().at("channel_input").at("recovery_remaining_ms")==recovery&&pausedRecovery.attacks.empty(),
                "Actual M3 recovery also pauses under hitstop without replaying damage");
            actor.hitStopped=false;runtime.request(input(4,true));runtime.request(input(4,false));
            bool recoveryClean=true;
            for(int i=0;i<100&&runtime.attacking();++i){const auto out=advance();recoveryClean&=out.attacks.empty();}
            check(!runtime.attacking()&&recoveryClean&&launches==1&&stops==1&&actor.mp==mp,
                "Finite source-based M3 recovery ends without queued key restart, another launch, another stop or repeated MP charge");
            runtime.cancel(ControllerCancelReason::RoomChange);const auto cancelled=advance();
            check(cancelled.femaleGunnerCommands.empty()&&runtime.snapshotDiagnostics().at("channel_input").at("contract").is_null(),
                "Room cancellation discards transient channel input/recovery and cannot emit a future tail command");
        }
        {
            ExperimentalCharacterRuntime runtime(sharedPlan);configure(runtime,12);
            ExperimentalActorState actor;actor.x=400;actor.y=300;actor.mp=1000000;actor.weaponSubtype=0;actor.noCooldown=true;
            uint64_t tick=0;size_t launches=0,stops=0;bool entered=false;
            const auto advance=[&]() {
                auto out=runtime.advance(++tick,actor,[](double,double){return true;});actor=out.actor;
                for(const auto &c:out.femaleGunnerCommands)if(!c.preflightOnly) {
                    if(c.effectRole=="stop_channel")++stops;else if(c.kind==FemaleGunnerCommandKind::Launch)++launches;
                }
                return out;
            };
            for(int i=0;i<200&&!entered;++i){advance();entered=runtime.snapshotDiagnostics().at("channel_input").at("contract").is_object();}
            check(entered&&launches==1,"Actual runtime starts Gatling using a repeat-press input contract");
            for(int i=0;i<4;++i)advance();runtime.request(input(4,true));advance();
            const auto renewed=runtime.snapshotDiagnostics().at("channel_input").at("deadline_ms").get<int64_t>();
            for(int i=0;i<5;++i){runtime.request(input(4,true));advance();}
            check(renewed>700&&runtime.snapshotDiagnostics().at("channel_input").at("deadline_ms")==renewed,
                "Actual held/OS-repeat ATTACK DOWN is filtered and cannot repeatedly renew Gatling");
            runtime.request(input(4,false));runtime.request(input(4,true));advance();
            check(runtime.snapshotDiagnostics().at("channel_input").at("deadline_ms").get<int64_t>()>renewed,
                "An actual UP followed by a distinct DOWN renews Gatling in the controller");
            runtime.request(input(5,true));const auto stopped=advance();bool jumpReason=false;
            for(const auto &c:stopped.femaleGunnerCommands)if(c.effectRole=="stop_channel")
                jumpReason=c.rawTables.at("channel_stop").at("reason")=="jump_pressed";
            check(stops==1&&jumpReason&&!runtime.attacking()&&launches==1,
                "Actual JUMP edge cancels Gatling once, without restarting it as a normal attack");
        }
        {
            ExperimentalCharacterRuntime runtime(sharedPlan);configure(runtime,13);
            runtime.request(input(4,true));runtime.request(input(4,false));
            ExperimentalActorState actor;actor.x=400;actor.y=300;actor.mp=1000000;actor.weaponSubtype=0;actor.noCooldown=true;
            size_t stops=0;bool started=false,finished=false;
            for(uint64_t tick=1;tick<250;++tick) {
                const auto out=runtime.advance(tick,actor,[](double,double){return true;});actor=out.actor;
                for(const auto &c:out.femaleGunnerCommands)if(c.effectRole=="stop_channel")++stops;
                started|=runtime.attacking();if(started&&!runtime.attacking()){finished=true;break;}
            }
            check(started&&finished&&stops==1,"An ATTACK DOWN+UP in one host batch cannot latch or restart a M3 channel");
        }
    }
    for(const int id:{9,13,96}) {
        ExperimentalCharacterRuntime runtime(std::make_shared<ExperimentalCharacterPlan>(plan));
        runtime.configuration().configureFemaleGunnerSourceSkill({5,id},1,plan);
        runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
        CharacterActionRequest request;request.action=CharacterAction::Skill;request.skill=SkillKey{5,id};request.inputDown=true;
        runtime.request(request);
        if(id==13){CharacterActionRequest held;held.action=CharacterAction::BasicAttack;held.inputKey=4;held.inputDown=true;runtime.request(held);}
        ExperimentalActorState actor;actor.x=400;actor.y=300;actor.mp=1000000;actor.weaponSubtype=0;
        size_t preflights=0,emissions=0;bool began=false,finished=false;
        int64_t expectedDuration=0;const auto &descriptor=plan.femaleGunnerSkills.at({5,id});
        for(size_t stage=0;stage<descriptor.stages.size();++stage) {
            const auto phase=build(id,stage);
            expectedDuration+=std::max(phase.second.runtimeDurationMs,phase.second.completionAfterMs);
        }
        const auto budget=uint64_t((expectedDuration+2000)*60/1000+8);
        for(uint64_t tick=1;tick<=budget;++tick) {
            const auto step=runtime.advance(tick,actor,[](double,double){return true;});actor=step.actor;
            for(const auto &command:step.femaleGunnerCommands)if(command.preflightOnly)++preflights;
                else if(command.kind!=FemaleGunnerCommandKind::Clear)++emissions;
            began|=runtime.attacking();if(began&&!runtime.attacking()){finished=true;break;}
        }
        check(began&&finished&&preflights==1&&emissions==1,
            "Actual runtime releases and completes one attack command across body frame/channel loops: "+std::to_string(id));
    }
    return {{"status",failures.empty()?"passed":"failed"},{"checks",checks},{"failures",failures},{"source_channels",sources},
        {"scope","source timing and controller schedule checks; World emission, normal input and original dynamic comparison are separate"}};
}
} // namespace dnf
