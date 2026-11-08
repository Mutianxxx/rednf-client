#include "dnf/experimental_character.hpp"
#include "dnf/simulation.hpp"
#include <cmath>
#include <stdexcept>

namespace dnf {
Json runFemaleGunnerSourceTests(Pvf &pvf,Assets &assets) {
    CharacterCatalog catalog(pvf);auto plan=std::make_shared<ExperimentalCharacterPlan>(
        loadExperimentalCharacterPlan(pvf,assets,catalog,{5,0,0}));
    Json checks=Json::array(),failures=Json::array(),rows=Json::array();
    const auto check=[&](bool ok,const std::string &message){checks.push_back({{"passed",ok},{"message",message}});if(!ok)failures.push_back(message);};
    check(plan->skills.size()==167,"All current1031 female Gunner source registrations remain present");
    check(plan->femaleGunnerSkills.size()==167,"Every source registration has a classified descriptor, including passive/profession rows");
    ExperimentalSkillConfiguration configuration(*plan);size_t active=0,passive=0;
    for(const auto &entry:plan->skills) {
        Json row={{"key",entry.first.json()},{"source",entry.second.source.json()},{"name",entry.second.name},
            {"normal_learning_or_original_comparison_passed",false}};
        try {
            const auto &descriptor=plan->femaleGunnerSkills.at(entry.first);row["descriptor"]=descriptor.snapshot();
            check(descriptor.source.json()==entry.second.source.json(),"Descriptor retains exact source identity: "+entry.second.name);
            auto command=evaluateFemaleGunnerSkill(descriptor,*entry.second.data,1,0);row["level_one_command"]=command.snapshot();
            check(command.rawTables.at("level_info")==entry.second.data->values("[level info]"),"Evaluated command retains selected source mode table: "+entry.second.name);
            configuration.configureFemaleGunnerSourceSkill(entry.first,1,*plan);
            if(entry.second.kind==SkillSourceKind::Passive) {
                ++passive;check(configuration.femaleGunnerPassiveLevel(entry.first)==1,"Passive uses isolated experiment level overlay: "+entry.second.name);
                row["runtime_consumer_status"]="parameter_read_only_until_world_passive_consumer_verified";
            } else {
                ++active;check(descriptor.dedicatedRuntime&&!descriptor.stages.empty(),"Active has dedicated source stages: "+entry.second.name);
                const auto *binding=configuration.binding(entry.first);
                check(binding&&!binding->unknown.contains("user_requested_temporary_template")&&binding->unknown.contains("female_gunner_source_controller"),
                    "Source controller never labels a universal basic template as the skill: "+entry.second.name);
                ExperimentalCharacterRuntime runtime(plan);runtime.configuration().configureFemaleGunnerSourceSkill(entry.first,1,*plan);
                runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
                CharacterActionRequest request;request.action=CharacterAction::Skill;request.skill=entry.first;request.inputDown=true;
                check(runtime.request(request),"Actual source runtime accepts dedicated active request: "+entry.second.name);
                if(entry.first.skillId==13){CharacterActionRequest held;held.action=CharacterAction::BasicAttack;held.inputKey=4;held.inputDown=true;runtime.request(held);}
                ExperimentalActorState actor;actor.x=400;actor.y=300;actor.mp=INT32_MAX;
                // This controller-only source fixture supplies the real gate's
                // handcannon subtype. World/contact tests equip the owned EQU.
                actor.weaponSubtype=entry.first.skillId==73?3:0;actor.noCooldown=true;
                row["actor_weapon_subtype"]=actor.weaponSubtype;
                size_t preflight=0,actual=0,attacks=0;bool started=false,ended=false,allFramesFrozen=true;std::set<std::string> sourceMotions;
                int64_t sourceDuration=0;auto budgetCommand=command;Json budgetStages=Json::array();
                for(const auto &stage:descriptor.stages) {
                    const auto *motion=plan->motion(stage.motionTag,stage.motionSlot);
                    if(motion) {
                        const auto timing=buildFemaleGunnerStageTiming(budgetCommand,stage,*plan->animations.at(motion->source.memberPath));
                        applyFemaleGunnerStageTiming(budgetCommand,timing);
                        // Controller-owned phases can intentionally outlast a
                        // short looping body ANI (G0LockOn430ms vs source7s).
                        // Budget the real stage contract, not pre-controller
                        // command.lifetime, while retaining the completion gate.
                        sourceDuration+=std::max(timing.runtimeDurationMs,timing.completionAfterMs)*std::max(stage.repeat,2);
                        budgetStages.push_back(timing.snapshot());
                    }
                }
                const auto budget=uint64_t((sourceDuration+std::max<int64_t>(0,budgetCommand.lifetimeMs)+2000)*60/1000+8);
                row["runtime_budget_ticks"]=budget;row["runtime_stage_timing_contracts"]=budgetStages;
                for(uint64_t tick=1;tick<=budget;++tick) {
                    const auto result=runtime.advance(tick,actor,[](double,double){return true;});actor=result.actor;
                    for(const auto &e:result.femaleGunnerCommands)if(e.preflightOnly)++preflight;else ++actual;
                    for(const auto &a:result.attacks){++attacks;sourceMotions.insert(a.motion.source.memberPath);
                        allFramesFrozen&=a.femaleGunnerCommand&&a.femaleGunnerCommand->key==entry.first&&
                            a.femaleGunnerCommand->actionSequence==a.actionSequence&&a.femaleGunnerCommand->motionSource&&
                            a.femaleGunnerCommand->motionSource->json()==a.motion.source.json()&&
                            a.femaleGunnerCommand->family==a.sourceFamily;
                    }
                    started|=runtime.attacking();
                    if(started&&!runtime.attacking()){ended=true;break;}
                    for(const auto &diag:result.diagnostics)if(diag.value("skill_failure",false))row["runtime_failure"]=diag;
                }
                check(started&&ended,"Dedicated source stages finish and release movement: "+entry.second.name);
                check(preflight==1,"All required entity sources preflight exactly once before release: "+entry.second.name);
                bool requiresCommand=false;for(const auto &stage:descriptor.stages)requiresCommand|=stage.emitCommand;
                check(!requiresCommand||actual>0,"Dedicated emit stage produces an actual World command: "+entry.second.name);
                check(attacks>0,"Dedicated body frames have actual ANI visit consumers: "+entry.second.name);
                check(allFramesFrozen,"Every source body frame retains its released source/TP command for status consumers: "+entry.second.name);
                runtime.cancel(ControllerCancelReason::RoomChange);
                const auto cancelled=runtime.advance(budget+1,actor,[](double,double){return true;});
                check(!runtime.attacking()&&cancelled.femaleGunnerCommands.empty(),"Cancel clears deferred source emissions: "+entry.second.name);
                row["runtime_source_motions"]=sourceMotions;row["preflight_commands"]=preflight;row["actual_commands"]=actual;
                row["body_frame_samples"]=attacks;row["runtime_stage_completed"]=started&&ended;
                row["runtime_consumer_status"]="source-stage-and-command-runtime; actual-world-damage-effects-passive-tests-separate";
            }
        }catch(const std::exception &e){check(false,"Source execution blocked for "+entry.second.name+": "+e.what());row["blocked"]=e.what();}
        rows.push_back(std::move(row));
    }
    check(active==72&&passive==95,"Source classification preserves 72 active and 95 passive registrations");
    const auto actor=[] {ExperimentalActorState a;a.x=400;a.y=300;a.mp=1000000;a.weaponSubtype=0;return a;};
    const auto requestSkill=[](int id) {CharacterActionRequest r;r.action=CharacterAction::Skill;r.skill=SkillKey{5,id};r.inputDown=true;return r;};
    for(const int id:{35,101,169}) {
        ExperimentalCharacterRuntime runtime(plan);runtime.configuration().configureFemaleGunnerSourceSkill({5,id},1,*plan);
        runtime.request(requestSkill(id));auto initial=actor();const auto moved=runtime.advance(1,initial,[](double,double){return true;});
        check(id==169?moved.actor.x<initial.x&&moved.actor.z>0:moved.actor.x>initial.x,
            "Source movement skill changes actual actor coordinates: "+std::to_string(id));
        ExperimentalCharacterRuntime wallRuntime(plan);wallRuntime.configuration().configureFemaleGunnerSourceSkill({5,id},1,*plan);
        wallRuntime.request(requestSkill(id));const auto blocked=wallRuntime.advance(1,initial,[](double,double){return false;});
        check(wallRuntime.attacking()&&blocked.actor.x==initial.x&&blocked.actor.y==initial.y,"An admitted skill movement respects actual geometry: "+std::to_string(id));
    }
    {
        CharacterActionRequest jump;jump.action=CharacterAction::Jump;jump.inputDown=true;
        ExperimentalCharacterRuntime ordinary(plan),leap(plan);ordinary.request(jump);leap.request(jump);
        auto initial=actor(),buffed=initial;buffed.femaleGunnerBuffs.push_back(evaluateFemaleGunnerSkill(
            plan->femaleGunnerSkills.at({5,175}),*plan->skills.at({5,175}).data,1,0));
        const auto before=ordinary.advance(1,initial,[](double,double){return true;});
        const auto after=leap.advance(1,buffed,[](double,double){return true;});
        check(std::abs((after.actor.vz-before.actor.vz)-88)<.001&&after.actor.z>before.actor.z,
            "Leap source explain20percent and static200 imply +200/1000 of CHR440, increasing initial velocity by88");
    }
    {
        ExperimentalCharacterRuntime runtime(plan);runtime.configuration().configureFemaleGunnerSourceSkill({5,30},10,*plan);
        runtime.configuration().configureFemaleGunnerSourceSkill({5,49},5,*plan);
        runtime.configuration().configureFemaleGunnerSourceSkill({5,151},2,*plan);
        runtime.request(requestSkill(30));auto state=actor();bool actual=false;
        const auto base=evaluateFemaleGunnerSkill(plan->femaleGunnerSkills.at({5,30}),*plan->skills.at({5,30}).data,10,0);
        for(uint64_t tick=1;tick<100;++tick) {
            const auto out=runtime.advance(tick,state,[](double,double){return true;});state=out.actor;
            for(const auto &c:out.femaleGunnerCommands)if(!c.preflightOnly&&c.kind==FemaleGunnerCommandKind::Buff)
                actual|=c.count==base.count+20&&c.rawTables.contains("ammo_capacity_modifier");
            if(actual)break;
        }
        check(actual,"Actual SilverBullet release Buff consumes legal level5 magazine source10 plus TP151 extra10 charges");
    }
    for(const int mode:{15,100}) {
        ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
        auto state=actor();state.femaleGunnerBuffs.push_back(evaluateFemaleGunnerSkill(plan->femaleGunnerSkills.at({5,mode}),*plan->skills.at({5,mode}).data,1,0));
        CharacterActionRequest input;input.action=CharacterAction::BasicAttack;input.inputDown=true;runtime.request(input);
        const auto shot=runtime.advance(1,state,[](double,double){return true;});
        check(!shot.femaleGunnerCommands.empty()&&shot.femaleGunnerCommands.front().kind==FemaleGunnerCommandKind::Launch,
            "A live source mode X input emits a real projectile command: "+std::to_string(mode));
        const auto expected=plan->motion("[etc motion]",mode==15?28:77);
        check(expected&&shot.animationPath==expected->source.memberPath,"A source mode X input selects the exact CHR shoot ANI: "+std::to_string(mode));
        if(mode==100) {
            runtime.cancel(ControllerCancelReason::RoomChange);input.inputKey=6;runtime.request(input);
            const auto blade=runtime.advance(1,state,[](double,double){return true;});
            check(blade.animationPath==plan->motion("[etc motion]",68)->source.memberPath&&!blade.attacks.empty()&&blade.attacks.front().attack&&
                blade.attacks.front().attack->source.memberPath==plan->attack("[etc attack info]",10)->source.memberPath,
                "Twin Gunblade source Z replaces body ANI and actual ATK with blade source slots");
            check(blade.femaleGunnerCommands.empty(),"Twin Gunblade blade contact does not emit an unrelated normal bullet");
        }else {
            runtime.cancel(ControllerCancelReason::RoomChange);input.action=CharacterAction::Jump;input.inputKey=-1;runtime.request(input);
            const auto ended=runtime.advance(1,state,[](double,double){return true;});
            bool cleared=false;for(const auto &c:ended.femaleGunnerCommands)cleared|=c.kind==FemaleGunnerCommandKind::Clear&&c.effectRole=="end_mode"&&c.key==SkillKey{5,15};
            check(cleared&&ended.actor.z>0,"Mobile Shooting source Jump ends the mode and executes an actual jump");
        }
    }
    for(const int id:{3,6,7,100}) {
        ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
        runtime.configuration().configureFemaleGunnerSourceSkill({5,id},1,*plan);
        auto state=actor();const auto mode=evaluateFemaleGunnerSkill(plan->femaleGunnerSkills.at({5,100}),*plan->skills.at({5,100}).data,1,0);
        state.femaleGunnerBuffs.push_back(mode);
        CharacterActionRequest shot;shot.action=CharacterAction::BasicAttack;shot.inputDown=true;runtime.request(shot);
        auto first=runtime.advance(1,state,[](double,double){return true;});state=first.actor;
        runtime.request(requestSkill(id));const auto started=runtime.advance(2,state,[](double,double){return true;});state=started.actor;
        const size_t firstSlot=id==3?86:id==6?88:id==7?90:91;
        check(started.animationPath==plan->motion("[etc motion]",firstSlot)->source.memberPath,
            "Live Twin Gunblade can cancel its basic attack into exact alternate skill CHR motion: "+std::to_string(id));
        if(id==100)check(state.mp==first.actor.mp,"Repeated Twin Gunblade finisher does not recharge full activation MP");
        else {
            const auto column=id==3?2:id==6?3:4;
            check(runtime.remainingCooldown({5,id},int64_t(FixedStepClock::millisecondsAtTick(2)))==mode.rawTables.at("static_data").at(column).get<int64_t>(),
                "Alternate mode skill consumes actual source100 special cooldown: "+std::to_string(id));
        }
        std::set<std::string> motions;bool finished=false,cleared=false,gunhawk=false;size_t body=0;
        const auto observe=[&](const ExperimentalTickResult &tick) {
            motions.insert(tick.animationPath);
            for(const auto &a:tick.attacks)if(a.attack) {
                ++body;check(!a.sourceFamily.empty()&&a.sourceFamily.rfind("twingunblade_",0)==0,
                    "Alternate body ATK carries its family, preventing ordinary Punisher capture semantics");
            }
            for(const auto &c:tick.femaleGunnerCommands) {
                cleared|=!c.preflightOnly&&c.kind==FemaleGunnerCommandKind::Clear&&c.effectRole=="end_mode"&&c.key==SkillKey{5,100};
                gunhawk|=!c.preflightOnly&&c.kind==FemaleGunnerCommandKind::Launch&&c.objectSource&&
                    c.objectSource->memberPath=="passiveobject/character/gunner/twingunbladegunhawk.obj";
            }
        };
        observe(started);
        for(uint64_t tick=3;tick<=900;++tick) {
            auto step=runtime.advance(tick,state,[](double,double){return true;});state=step.actor;observe(step);
            if(!runtime.attacking()){finished=true;break;}
        }
        check(finished,"Alternate source mode skill finishes, preserving future input: "+std::to_string(id));
        if(id==3)check(motions.count(plan->motion("[etc motion]",87)->source.memberPath)&&body>0,"Source100 names UpperSpinningKick/Windmill3, distinct from AerialKnee4, and consumes both Somersault source stages");
        if(id==6)check(motions.count(plan->motion("[etc motion]",89)->source.memberPath)&&body>0,"Chain Cut consumes separate cut and pull stages with real source ATK");
        if(id==7)check(gunhawk,"Spinning Blade publishes its own exact source Gunhawk object");
        if(id==100)check(cleared&&motions.count(plan->motion("[etc motion]",92)->source.memberPath)&&motions.count(plan->motion("[etc motion]",93)->source.memberPath)&&body>0,
            "Twin Gunblade finisher plays rapid/final source stages and emits selective mode termination");
    }
    const auto saved=configuration.snapshot();ExperimentalSkillConfiguration restored(*plan);
    try {restored.restore(saved,*plan);check(restored.snapshot()==saved&&restored.femaleGunnerLevels()==configuration.femaleGunnerLevels(),
        "All active/passive isolated source levels survive exact-source snapshot restore");}
    catch(const std::exception &e){check(false,std::string("Source configuration restore blocked: ")+e.what());}
    Json result={{"schema",1},{"passed",failures.empty()},{"check_count",checks.size()},{"failures",failures},{"checks",checks},
        {"skills",rows},{"active_count",active},{"passive_count",passive},{"pvf_identity",pvf.identity()},
        {"native_confirmed",false},{"original_comparison","pending_user"},{"world_combat_verification","separate-required"}};
    if(!failures.empty()) {
        writeJson("reports/knowledge-base-audit/female-gunner-source-tests-failed.json",result);
        throw std::runtime_error("Female Gunner source/runtime failures: "+std::to_string(failures.size()));
    }
    return result;
}
} // namespace dnf
