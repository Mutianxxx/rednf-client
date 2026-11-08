#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/progression.hpp"
#include <cmath>
#include <stdexcept>

namespace dnf {
Json runBasicAttackMovementTests(Pvf &pvf,Assets &assets) {
    Json out={{"status","running"},{"checks",Json::array()},{"jobs",Json::array()}};
    const auto check=[&](bool okay,const std::string &message) {
        out["checks"].push_back({{"passed",okay},{"message",message}});
        if(!okay)throw std::runtime_error("Basic attack movement: "+message);
    };
    try {
    RegionCatalog regions(pvf,assets);
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines})
    for(const int job:{0,1,2,3,4,5,8}) {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        world.selectCharacter({job,0,0});world.configureAnimationClock(clock);
        Progression progression(regions);progression.state["inventory"]=Json::array();progression.state["equipped"]=Json::object();
        world.applyEquipment(progression);
        const auto floor=[&] {
            world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
            world.combat=true;world.freezeAi=true;world.mapWidth=4000;world.walkRects={{0,185,4000,800}};world.blockedRects.clear();
            auto &p=world.player;p.x=p.px=1200;p.y=p.py=500;p.z=p.pz=0;p.vz=0;p.dir=1;
            p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.mp=p.maxMp;p.recovery=0;p.stunUntil=0;p.hitStopped=false;p.hitStopTicks=0;
        };
        const auto input=[&](int key,bool down) {world.enqueue({world.simulationNanoseconds(),key,down});};
        const auto step=[&] {world.advanceSingleTick();};
        const auto attacking=[&] {return world.experimentalRuntime()?world.experimentalRuntime()->attacking():world.player.animation=="dashattack";};
        const auto dash=[&] {
            input(1,true);step();input(1,false);step();input(1,true);step();
            const auto speed=world.player.vx;input(4,true);step();input(4,false);return speed;
        };
        floor();world.configureBasicAttackMovement(true);
        const auto sourceMove=world.basicAttackMovementReport();
        const double runVelocity=dash(),firstVelocity=world.player.vx,firstX=world.player.x;
        check(attacking()&&firstVelocity>runVelocity&&runVelocity>0,"Actual double tap then X boosts source run speed for job "+std::to_string(job));
        input(1,false);
        double previousVelocity=firstVelocity,previousX=firstX;size_t activeSteps=0;
        for(int tick=0;tick<24;++tick) {
            step();if(!attacking())break;++activeSteps;
            check(world.player.x>=previousX&&world.player.vx>=0&&world.player.vx<=previousVelocity,
                "Dash attack coasts forward after direction release and decelerates without reversing");
            previousVelocity=world.player.vx;previousX=world.player.x;
        }
        check(activeSteps>0&&previousX>firstX,"Each source dash has real motion after its first tick");
        if(attacking())check(world.player.vx==0,"A long source dash hold cannot create an unbounded glide");
        // A wall stops the relevant axis permanently for this action. Removing
        // the wall later cannot resurrect the old velocity.
        floor();dash();const auto wallX=world.player.x;world.blockedRects={{wallX+1,185,1000,800}};step();
        check(world.player.vx==0&&world.player.x==wallX,"Dash collision stops the source glide at the world obstacle");
        world.blockedRects.clear();input(1,false);step();
        check(world.player.x==wallX,"Removing a wall does not revive canceled glide velocity");
        floor();dash();const auto pausedX=world.player.x;world.player.hitStopTicks=3;step();
        check(world.player.x==pausedX,"Hitstop freezes ordinary dash movement");
        world.changeScene();world.releaseInputs();const auto sceneX=world.player.x;step();
        check(world.player.x==sceneX,"Scene cancellation discards dash movement and physical inputs");

        floor();input(5,true);step();input(5,false);for(int tick=0;tick<4;++tick)step();
        input(4,true);step();input(4,false);input(1,true);input(2,true);
        const auto airX=world.player.x,airY=world.player.y;
        const auto airDir=world.player.dir;
        step();const auto airVx=world.player.vx,airVy=world.player.vy;
        check(world.player.z>0&&world.player.x>airX&&world.player.y<airY&&airVx>0&&airVy<0,
            "Actual jump X accepts horizontal and lane input during its ordinary aerial source pose");
        check(world.player.dir==airDir,"Aerial direction control preserves the attack facing");
        input(1,false);input(2,false);input(0,true);step();
        check(world.player.vx<0&&world.player.vy==0,"Air attack can change travel direction without replaying the action");
        world.player.hitStopTicks=3;const auto airPauseX=world.player.x;step();
        check(world.player.x==airPauseX,"Hitstop freezes aerial attack direction movement");
        world.changeScene();world.releaseInputs();world.idle();
        // The legacy strategy is independently selectable at idle boundaries.
        floor();world.configureBasicAttackMovement(false);dash();
        check(world.player.vx==0,"Legacy candidate retains stationary dash attack for comparison");
        bool rejected=false;
        try {world.configureBasicAttackMovement(true);}catch(const std::logic_error &){rejected=true;}
        check(rejected&&world.basicAttackMovementReport().at("id")=="legacy-stationary-basic-attack-v1",
            "Changing a movement candidate during an active action rejects without changing policy");
        out["jobs"].push_back({{"job",job},{"clock",ani_clock::policyName(clock)},{"run_velocity",runVelocity},
            {"dash_first_velocity",firstVelocity},{"air_velocity",{airVx,airVy}},{"movement_policy",sourceMove}});

        Json reference;
        for(const int fps:{60,30,144,240,0}) {
            World replay(pvf,assets,WorldRules::BetaFoundationV1);replay.enableExperimentalCharacters();
            replay.selectCharacter({job,0,0});replay.configureAnimationClock(clock);replay.applyEquipment(progression);
            replay.changeScene();replay.monsters.clear();replay.events.clear();replay.releaseInputs();replay.idle();
            replay.combat=true;replay.freezeAi=true;replay.mapWidth=4000;replay.walkRects={{0,185,4000,800}};replay.blockedRects.clear();
            replay.player.x=replay.player.px=1200;replay.player.y=replay.player.py=500;
            replay.player.z=replay.player.pz=replay.player.vz=0;replay.player.dir=1;
            replay.configureBasicAttackMovement(true);
            // Events are stamped once in simulation time. Render scheduling
            // cannot move an edge to a different tick, including catch-up.
            for(const auto &event:std::vector<Input>{{0,1,true},{20000000,1,false},{40000000,1,true},
                {60000000,4,true},{70000000,4,false},{90000000,1,false},
                {700000000,5,true},{720000000,5,false},{800000000,4,true},{820000000,4,false},
                {830000000,0,true},{830000000,2,true},{960000000,0,false},{960000000,2,false}})
                replay.enqueue(event);
            Json trace=Json::array();
            replay.setObjectTick([&](World &w) {
                const auto &p=w.player;
                trace.push_back({w.tick,p.x,p.y,p.z,p.vx,p.vy,p.vz,p.dir,p.animation,p.animationPath,p.poseFrame,
                    w.experimentalRuntime()?w.experimentalRuntime()->snapshotDiagnostics():Json()});
            });
            if(fps) {
                int64_t previous=0;
                for(int frame=1;frame<=fps*2;++frame) {
                    const auto end=int64_t(frame)*2000000000ll/(fps*2);
                    replay.advance(end-previous);previous=end;
                }
            } else {
                replay.advance(2000000000ll,3);
                check(replay.pendingTicks()>0,"Budgeted render catch-up retains unfinished movement ticks");
                while(replay.pendingTicks())replay.advance(0,3);
            }
            check(trace.size()==120,"Two simulation seconds produce exactly 120 actual movement samples");
            const Json result={{"trajectory",trace},{"random",replay.randomStreams().snapshot()},
                {"simulation",replay.simulationCheckpoint()}};
            if(reference.is_null())reference=result;
            check(result==reference,"Every actual actor pose, XYZ, velocity, input/ID and RNG agrees at 30/60/144/240 FPS and catch-up");
        }
    }
    out["status"]="passed";out["count"]=out["checks"].size();
    out["native_dynamic_comparison"]="pending_user";out["classification"]="user_requested_with_inferred_shared_policy";
    writeJson("reports/seven-job-world/basic-attack-movement-tests.json",out);return out;
    } catch(const std::exception &error) {
        out["status"]="failed";out["error"]=error.what();out["count"]=out["checks"].size();
        writeJson("reports/seven-job-world/basic-attack-movement-tests.json",out);throw;
    }
}
} // namespace dnf
