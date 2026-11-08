#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/progression.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <stdexcept>

namespace dnf {
namespace {
struct MovementReactionWorld {
    World world;
    Progression progression;
    MovementReactionWorld(Pvf &pvf,Assets &assets,const RegionCatalog &regions,
                          const std::filesystem::path &directory,int job,
                          ani_clock::ClockPolicy clock)
        :world(pvf,assets,WorldRules::BetaFoundationV1),progression(regions) {
        static const char *classes[]={"swordman","fighter","gunner","mage","priest","atgunner"};
        world.enableExperimentalCharacters();
        CharacterStore store(directory,"experimental-movement-reaction-test");
        store.data["characters"][0]={{"name","NormalMovementReaction"},{"class",classes[job]},
            {"identity",CharacterIdentity{job,0,0}.json()},{"level",1},{"weapon",0},
            {"skill_initialization","source-v1"}};
        store.apply(0,world,progression);world.configureAnimationClock(clock);
        // Isolated collision floor/starting placement only. HP/MP, equipment,
        // skills, damage, AI and source boxes remain their actual normal values.
        world.combat=true;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};
        world.player.x=world.player.px=560;world.player.y=world.player.py=344;world.player.dir=-1;
        world.synchronizeEntityHandles();
    }
};
size_t reactionEvents(const World &world,const std::string &kind) {
    return size_t(std::count_if(world.events.begin(),world.events.end(),
        [&](const Event &event){return event.kind==kind;}));
}
void reactionInput(World &world,int key,bool down) {
    world.enqueue({world.simulationNanoseconds(),key,down});
}
void reactionGoblin(World &world) {
    Actor actor;actor.id=1;actor.sourceId=1;actor.monsterPath="monster/goblin/goblin.mob";
    actor.x=actor.px=world.player.x+45;actor.y=actor.py=world.player.y;actor.dir=-1;
    world.initializeMonsterAttributes(actor,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    world.monsters.push_back(std::move(actor));world.synchronizeEntityHandles();
}
bool reactionAwaitWindup(World &world,int maximum=240) {
    for(int i=0;i<maximum;++i) {
        world.advanceSingleTick();
        if(!world.monsters.empty()&&world.monsters.front().animation=="attack1"&&!world.monsters.front().attackHit)
            return true;
        if(world.player.dead)return false;
    }
    return false;
}
bool reactionAwaitHit(World &world,size_t before,int maximum=120) {
    for(int i=0;i<maximum;++i) {
        world.advanceSingleTick();
        if(reactionEvents(world,"player_hit")>before)return true;
        if(world.player.dead)return false;
    }
    return false;
}
Json reactionObservation(const World &world) {
    return {{"tick",world.tick},{"x",world.player.x},{"y",world.player.y},
        {"hp",world.player.hp},{"mp",world.player.mp},{"animation",world.player.animation},
        {"attacking",world.experimentalRuntime()->attacking()},{"inputs",world.inputs()},
        {"events",world.eventLog()},{"last_damage",world.statReport().at("last_damage")}};
}
} // namespace

Json runExperimentalMovementReactionTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool okay,const std::string &message){
        if(!okay)throw std::runtime_error("Experimental movement reaction: "+message);
        checks.push_back(message);
    };
    RegionCatalog regions(pvf,assets);
    const auto root=std::filesystem::absolute(std::filesystem::path("cache/experimental-movement-reaction")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        const std::string policy=ani_clock::policyName(clock);
        {
            MovementReactionWorld fixture(pvf,assets,regions,root/(policy+"-incoming"),1,clock);auto &world=fixture.world;
            check(!world.experimentalSkillPreviewEnabled()&&!world.debugOverrides().enabled&&
                !world.god&&!world.freeCd&&!world.freezeAi,"Female Fighter fixture uses normal source-v1 state and live AI: "+policy);
            world.randomStreams()=RandomStreams(1);reactionGoblin(world);
            check(reactionAwaitWindup(world),"Real source goblin AI begins its own attack windup: "+policy);
            const int hp=world.player.hp,mp=world.player.mp;
            const auto hitBefore=reactionEvents(world,"player_hit");
            // Both requests are actual queued input. The own empty swing faces
            // away from the goblin, keeping the actor rooted during its windup.
            // There is exactly one right DOWN until the later explicit KEYUP.
            reactionInput(world,1,true);reactionInput(world,4,true);world.advanceSingleTick();
            check(world.experimentalRuntime()->attacking()&&world.player.dir==-1,
                "Own source attack starts before locomotion and faces away from the incoming goblin: "+policy);
            reactionInput(world,4,false);world.advanceSingleTick();reactionInput(world,4,true);
            check(reactionAwaitHit(world,hitBefore),"Actual MOB ANI-box contact reaches ordinary hurtPlayer: "+policy);
            const auto hit=reactionObservation(world);const double hitX=world.player.x;
            check(world.player.hp>0&&world.player.hp<hp&&!world.player.dead&&world.player.life==ActorLife::Alive&&
                world.player.animation=="damage1"&&!world.experimentalRuntime()->attacking()&&world.player.mp==mp,
                "Nonlethal accepted contact cancels the active/queued basic action without changing MP: "+policy);
            for(int i=0;i<60;++i)world.advanceSingleTick();
            const auto recovered=reactionObservation(world);
            check(world.player.x>hitX+20,
                "A physically held right key resumes actual movement after ordinary hit recovery without another DOWN: "+policy+
                "; hit_x="+std::to_string(hitX)+" recovered_x="+std::to_string(world.player.x));
            check(!world.experimentalRuntime()->attacking()&&world.player.mp==mp&&world.attackVolumes.empty(),
                "Held attack and queued combo do not replay after ordinary interruption: "+policy);
            reactionInput(world,1,false);reactionInput(world,4,false);world.advanceSingleTick();
            const double stoppedX=world.player.x;for(int i=0;i<12;++i)world.advanceSingleTick();
            check(std::abs(world.player.x-stoppedX)<1e-7,"A real movement KEYUP stops the recovered held movement: "+policy);
            samples[policy+"_incoming"]={{"accepted_hit",hit},{"recovered",recovered},{"stopped_x",stoppedX}};
        }
        {
            MovementReactionWorld fixture(pvf,assets,regions,root/(policy+"-focus"),1,clock);auto &world=fixture.world;
            const double start=world.player.x;reactionInput(world,1,true);world.advanceSingleTick();
            const double firstStep=world.player.x-start;
            check(firstStep>0,"First normal direction press moves through the actual locomotion consumer: "+policy);
            // SDL focus loss calls this existing public boundary. Reacquiring
            // focus and pressing quickly must not reuse pre-focus double-tap.
            world.releaseInputs();const double focusX=world.player.x;
            for(int i=0;i<2;++i)world.advanceSingleTick();
            check(std::abs(world.player.x-focusX)<1e-7,"Explicit focus/input release stops physical movement: "+policy);
            reactionInput(world,1,true);const double before=world.player.x;world.advanceSingleTick();
            const double resumedStep=world.player.x-before;
            check(resumedStep>0&&resumedStep<=firstStep*1.001,
                "A short-interval direction press after focus release walks instead of triggering stale double-tap run: "+policy+
                "; first_step="+std::to_string(firstStep)+" resumed_step="+std::to_string(resumedStep));
            world.changeScene();const double sceneX=world.player.x;
            for(int i=0;i<12;++i)world.advanceSingleTick();
            check(std::abs(world.player.x-sceneX)<1e-7,"Scene change keeps its explicit physical-input reset: "+policy);
            samples[policy+"_focus"]={{"first_step",firstStep},{"resumed_step",resumedStep},{"scene_x",sceneX}};
        }
        {
            MovementReactionWorld fixture(pvf,assets,regions,root/(policy+"-normal-cost"),2,clock);auto &world=fixture.world;
            const SkillKey knee{2,4};auto &runtime=*world.experimentalRuntime();
            // Learned slots are configured at the actual normal town boundary.
            world.combat=false;
            check(world.skillState().learnedLevel(knee)==1&&!world.experimentalSkillPreviewEnabled()&&
                world.assignLearnedSkillSlot(0,knee).ok,"Own normal initial Knee1 is assigned without preview grants: "+policy);
            world.combat=true;
            world.randomStreams()=RandomStreams(1);reactionGoblin(world);
            check(reactionAwaitWindup(world),"Normal MP/CD case also uses actual source goblin AI: "+policy);
            // Wait within the actual enemy windup, before its first source
            // attack box. Starting Knee immediately can interrupt this enemy
            // before the fixture ever receives its intended incoming contact.
            const auto &enemy=world.monsters.front();
            const auto enemyMotion=assets.animation(enemy.animationPath.empty()?
                (std::filesystem::path(enemy.monsterPath).parent_path()/pvf.script(enemy.monsterPath).text("[attack motion]")).generic_string():enemy.animationPath);
            int64_t strikeMs=0;bool strikeFound=false;
            for(const auto &frame:enemyMotion->frames) {
                if(std::any_of(frame.boxes.begin(),frame.boxes.end(),[](const Box &box){return box.type==15;})){strikeFound=true;break;}
                strikeMs+=frame.duration;
            }
            check(strikeFound&&strikeMs>=100,"Incoming paid-skill fixture has an authored enemy strike boundary: "+policy);
            const auto beforeWindupHits=reactionEvents(world,"player_hit");
            while(world.nowMs()-world.monsters.front().animStart<strikeMs-50)world.advanceSingleTick();
            check(reactionEvents(world,"player_hit")==beforeWindupHits&&world.monsters.front().animation=="attack1"&&
                !world.monsters.front().attackHit,"Paid skill starts before source enemy contact without a previous hit: "+policy);
            const int mp=world.player.mp;const auto hits=reactionEvents(world,"player_hit");
            reactionInput(world,1,true);reactionInput(world,20,true);world.advanceSingleTick();
            const int paidMp=world.player.mp;const auto deadline=world.nowMs()+runtime.remainingCooldown(knee,world.nowMs());
            check(runtime.attacking()&&paidMp<mp&&deadline>world.nowMs(),"Normal learned-slot cast pays its actual source MP and starts CD once: "+policy);
            reactionInput(world,20,false);
            check(reactionAwaitHit(world,hits),"Normal paid skill receives a real accepted source enemy hit: "+policy);
            check(world.player.hp>0&&world.player.mp==paidMp&&
                world.nowMs()+runtime.remainingCooldown(knee,world.nowMs())==deadline,
                "Accepted skill MP and absolute cooldown survive real incoming contact without refund or recharge: "+policy);
            const auto received=reactionObservation(world);reactionInput(world,1,false);
            for(int i=0;i<90;++i)world.advanceSingleTick();
            check(world.player.mp==paidMp&&!runtime.attacking()&&world.attackVolumes.empty(),
                "Paid skill retires without automatic retry or duplicate resource consumption: "+policy);
            samples[policy+"_normal_cost"]={{"mp_before",mp},{"mp_paid",paidMp},{"cooldown_deadline",deadline},{"received",received}};
        }
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","Actual World normal source-v1 creation, queued input, goblin AI/ANI-box accepted damage, movement recovery/KEYUP, combo cancellation, focus release/repress, scene reset and normal learned Knee MP/CD. Isolated floor/placement; no ordinary dungeon or native-client parity claim. No new implementation API or diagnostic held-field dependency."}};
}
} // namespace dnf
