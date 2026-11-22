#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/storage.hpp"
#include "dnf/female_gunner_entities.hpp"
#include "dnf/female_gunner_world.hpp"
#include "female_gunner_test_weapon.hpp"
#include <stdexcept>
#include <iostream>

namespace dnf {
Json runFemaleGunnerWorldTests(Pvf &pvf,Assets &assets) {
    RegionCatalog regions(pvf,assets);Progression progression(regions);
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
    const auto fixture=std::filesystem::absolute("cache/female-gunner-world-fixtures");
    CharacterStore store(fixture);
    store.data["characters"][0]={{"name","FemaleGunnerSourceWorldRegression"},{"class","atgunner"},
        {"identity",CharacterIdentity{5,0,0}.json()},{"level",1},{"skill_initialization","source-v1"}};
    store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);
    world.configureAnimationClock(ani_clock::ClockPolicy::SourceDelay100);
    const auto &plan=world.experimentalRuntime()->plan();
    Json rows=Json::array(),checks=Json::array(),failures=Json::array();
    const auto check=[&](bool value,const std::string &text){checks.push_back({{"passed",value},{"message",text}});if(!value)failures.push_back(text);};
    for(const auto &[key,skill]:plan.skills)if(skill.kind==SkillSourceKind::Active) {
        std::cerr<<"Female Gunner World "<<key.skillId<<" "<<skill.name<<"\n";
        Json row={{"key",key.json()},{"name",skill.name}};
        std::unique_ptr<FemaleGunnerHandcannonTestFixture> sourceWeapon;
        try {
            world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
            world.combat=true;world.freezeAi=true;world.freeCd=true;
            world.mapWidth=2400;world.walkRects={{0,185,2400,500}};
            world.player.x=world.player.px=500;world.player.y=world.player.py=300;world.player.z=world.player.pz=0;
            world.player.mp=INT32_MAX;world.player.dead=false;world.player.life=ActorLife::Alive;
            world.player.recovery=0;world.player.stunUntil=0;world.player.hitStopTicks=0;world.player.hitStopped=false;
            if(key.skillId==73){sourceWeapon=std::make_unique<FemaleGunnerHandcannonTestFixture>(world,progression,plan.characterDefinition);row["source_weapon_fixture"]=sourceWeapon->source();}
            auto &runtime=*world.experimentalRuntime();
            runtime.configuration()=ExperimentalSkillConfiguration(plan);
            if(key.skillId==80||key.skillId==81) {
                runtime.configuration().configureFemaleGunnerSourceSkill({5,79},1,plan);runtime.configuration().assignSlot(0,SkillKey{5,79},plan);
                world.enqueue({world.simulationNanoseconds(),20,true});
                bool baseStarted=false;
                for(int step=0;step<600;++step){world.advanceSingleTick();baseStarted|=runtime.attacking();if(baseStarted&&!runtime.attacking())break;}
                check(world.femaleGunnerDiagnostics().at("g_group").at("skill")==79,"G-2/G-3 fixture creates its real required G-1 source group");
            }
            runtime.configuration().configureFemaleGunnerSourceSkill(key,1,plan);runtime.configuration().assignSlot(0,key,plan);
            const auto diagnosticsBefore=world.experimentalDiagnostics().at("world").size();
            const auto normal=world.skillState().snapshot(world.nowMs());
            const auto before=world.player.mp;
            world.enqueue({world.simulationNanoseconds(),20,true});
            if(key.skillId==13)world.enqueue({world.simulationNanoseconds(),4,true});
            bool started=false,ended=false,rejected=false;size_t phaseEntities=0,buffs=0;
            const auto command=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at(key),*skill.data,1,0);
            auto timedCommand=command;Json stageTimings=Json::array();
            int64_t sourceDuration=0;
            for(const auto &stage:plan.femaleGunnerSkills.at(key).stages)if(const auto *m=plan.motion(stage.motionTag,stage.motionSlot)) {
                const auto timing=buildFemaleGunnerStageTiming(timedCommand,stage,*plan.animations.at(m->source.memberPath));
                applyFemaleGunnerStageTiming(timedCommand,timing);stageTimings.push_back(timing.snapshot());
                sourceDuration+=std::max(timing.runtimeDurationMs,timing.completionAfterMs)*std::max(2,stage.repeat);
            }
            const int budget=int(std::min<int64_t>(30000,(sourceDuration+timedCommand.lifetimeMs+4000)*60/1000+100));
            row["runtime_budget_ticks"]=budget;row["runtime_stage_timing_contracts"]=stageTimings;
            for(int tick=0;tick<budget;++tick) {
                world.advance(16666667);
                started|=runtime.attacking();
                const auto diagnostics=world.femaleGunnerDiagnostics();
                if(diagnostics.is_object()) {phaseEntities=std::max(phaseEntities,diagnostics.at("entities").size());buffs=std::max(buffs,diagnostics.at("buffs").size());}
                if(started&&!runtime.attacking()){ended=true;break;}
                if(!started&&tick>4)break;
            }
            const auto diagnostics=world.experimentalDiagnostics().at("world");
            for(size_t i=std::min(diagnosticsBefore,diagnostics.size());i<diagnostics.size();++i)
                if(diagnostics[i].value("current_action_rejected",false)||diagnostics[i].value("skill_failure",false))rejected=true;
            row["diagnostics"]=world.experimentalDiagnostics();row["started"]=started;row["ended"]=ended;
            row["maximum_entities"]=phaseEntities;row["maximum_buffs"]=buffs;row["mp_before"]=before;row["mp_after"]=world.player.mp;
            check(started&&ended&&!rejected,"Actual World accepts, plays and finishes empty release: "+skill.name);
            check(world.player.mp<=before&&world.skillState().snapshot(world.nowMs())==normal,"Source release leaves normal learning ledger unchanged: "+skill.name);
            if(command.kind==FemaleGunnerCommandKind::Buff)check(buffs>0,"Buff reaches actual World service: "+skill.name);
            world.changeScene();
            const auto cleared=world.femaleGunnerDiagnostics();
            check(cleared.at("entities").empty()&&cleared.at("buffs").empty(),"Scene cancellation clears source entities and buffs: "+skill.name);
        }catch(const std::exception &error){row["error"]=error.what();check(false,"Actual World exception for "+skill.name+": "+error.what());}
        if(sourceWeapon)check(sourceWeapon->restore(),"Source handcannon fixture restores prior owned weapon after CannonBall empty release");
        rows.push_back(std::move(row));
    }
    try {
        world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
        FemaleGunnerWorld service(world);ExperimentalActorState actor;actor.x=500;actor.y=300;actor.mp=INT32_MAX;actor.weaponSubtype=0;
        auto flame=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,13}),*plan.skills.at({5,13}).data,1,0);
        auto otherAction=flame;flame.actionSequence=700;otherAction.actionSequence=701;
        auto otherSkill=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,36}),*plan.skills.at({5,36}).data,1,0);otherSkill.actionSequence=700;
        auto prepared=service.prepare({flame,otherAction,otherSkill},actor,0);service.publish(std::move(prepared));
        const auto before=service.snapshot();const auto visualCount=world.effects.size();
        const auto stop=stopFemaleGunnerChannel(flame,"attack_released");
        prepared=service.prepare({stop},actor,0);
        check(service.snapshot()==before&&world.effects.size()==visualCount,
            "Preparing an exact channel exit keeps live entity/visual state untouched until transaction publication");
        service.publish(std::move(prepared));const auto after=service.snapshot();
        bool exactRemoved=true,otherActionKept=false,otherSkillKept=false;
        for(const auto &entity:after.at("entities")) {
            const auto &c=entity.at("command");const auto skill=c.at("key").at("skill_id").get<int>();const auto action=c.at("action").get<uint64_t>();
            if(skill==13&&action==700&&c.at("role")!="channel_visual_end")exactRemoved=false;
            otherActionKept|=skill==13&&action==701;otherSkillKept|=skill==36&&action==700;
        }
        check(exactRemoved&&otherActionKept&&otherSkillKept,
            "M3 release removes only its exact action's sustained damage/visuals while preserving other actions and skills");
        check(after.at("buffs")==before.at("buffs"),"Channel exit never deletes unrelated source buffs");
        const auto onceVisualCount=world.effects.size();
        prepared=service.prepare({stop,stop},actor,0);service.publish(std::move(prepared));
        check(service.snapshot()==after&&world.effects.size()==onceVisualCount,
            "Repeated exact channel stop never respawns a tail, repeats cleanup or changes the committed receipt");
        const auto afterVisualCount=world.effects.size();bool invalidRejected=false;
        try{auto invalid=stop;invalid.actionSequence=0;auto rejected=service.prepare({invalid},actor,0);(void)rejected;}
        catch(const std::invalid_argument &){invalidRejected=true;}
        check(invalidRejected&&service.snapshot()==after&&world.effects.size()==afterVisualCount,
            "Invalid unowned channel exit rejects the complete batch without partial entity or visual publication");
        auto gatling=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,12}),*plan.skills.at({5,12}).data,1,0);
        gatling.actionSequence=800;prepared=service.prepare({gatling},actor,0);service.publish(std::move(prepared));
        const auto scheduledState=service.snapshot();size_t scheduled=0;for(const auto &entity:scheduledState.at("entities"))
            if(entity.at("command").at("key")==gatling.key.json()&&entity.at("command").at("action")==800)++scheduled;
        world.advanceSingleTick();service.advance();
        prepared=service.prepare({stopFemaleGunnerChannel(gatling,"jump_pressed")},actor,0);service.publish(std::move(prepared));
        const auto stoppedState=service.snapshot();size_t fired=0;for(const auto &entity:stoppedState.at("entities"))
            if(entity.at("command").at("key")==gatling.key.json()&&entity.at("command").at("action")==800)++fired;
        check(scheduled>1&&fired==1,"Gatling stop retires future scheduled rounds and preserves the already-fired detached bullet");
        rows.push_back({{"scope","actual_channel_stop_transaction"},{"before",before},{"after",after}});
    }catch(const std::exception &error){check(false,std::string("Channel stop World transaction exception: ")+error.what());}
    const auto result=Json{{"passed",failures.empty()},{"check_count",checks.size()},{"checks",checks},{"failures",failures},
        {"skills",rows},{"classification","actual-production-world-empty-release-and-cleanup"},{"original_comparison","pending_user"}};
    if(!failures.empty()){writeJson("reports/knowledge-base/female-gunner-world-failed.json",result);throw std::runtime_error("Female Gunner World failures: "+std::to_string(failures.size()));}
    return result;
}
}
