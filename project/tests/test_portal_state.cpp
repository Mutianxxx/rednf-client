#include "dnf/portal_visuals.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
Json runPortalStateTests(Pvf &pvf,Assets &assets) {
    int checks=0;Json samples=Json::array();
    auto check=[&](bool good,const std::string &message){++checks;if(!good)throw std::runtime_error("Portal state: "+message);};
    std::set<std::string> seen;size_t loops=0,nonloops=0;
    const auto objects=pvf.paths("passiveobject/mapobject/pathgate/",".obj");
    for(const auto &object:objects)for(bool open:{false,true}) {
        std::optional<PortalVisualPlan> plan;
        try {plan=portalVisuals(pvf,object,open);}catch(const std::exception&){continue;}
        for(const auto &track:plan->tracks)if(seen.insert(track.animation).second) {
            const auto animation=assets.animation(track.animation);
            const auto flag=animation->globals.find("0");
            const bool expected=flag!=animation->globals.end()&&flag->is_boolean()&&flag->get<bool>();
            check((flag==animation->globals.end()||flag->is_boolean())&&portalAnimationLoops(*animation)==expected,
                "Source binary LOOP matches the real pathgate ANI and is not inferred from state/filename");
            expected?++loops:++nonloops;
        }
    }
    check(objects.size()==639&&seen.size()==782&&loops==278&&nonloops==504,"Current1031 all639OBJ/782ANI LOOP classification is retained");
    const auto door=assets.animation("passiveobject/mapobject/pathgate/act1/animation/granflorisleftopendoor.ani");
    const auto light=assets.animation("passiveobject/mapobject/pathgate/act1/animation/granflorisleftlight.ani");
    check(door->duration==1100&&door->frames.size()==2&&!portalAnimationLoops(*door)&&portalAnimationLoops(*light),
        "The real open door is nonloop while its source light loops");
    for(auto profile:{ani_render::RenderProfile::Legacy1031,ani_render::RenderProfile::Inferred60Us1031}) {
        for(int64_t ms:{0,499,500,1099,1100,1600,2200,10000}) {
            const auto pose=door->samplePose(double(ms),portalAnimationLoops(*door),-1,profile);
            check(pose.frame==size_t(ms<500?0:1)&&(ms<500?pose.rgba[3]>=0&&pose.rgba[3]<=255:pose.rgba[3]==0)&&
                (ms!=0||pose.rgba[3]==255),
                "Actual source open-door alpha stays transparent after its terminal frame in either rendering profile at "+std::to_string(ms)+"; frame="+std::to_string(pose.frame)+" alpha="+std::to_string(pose.rgba[3]));
            samples.push_back({{"time",ms},{"profile",int(profile)},{"frame",pose.frame},{"alpha",pose.rgba[3]}});
        }
        check(door->samplePose(1100,true,-1,profile).rgba[3]==255,
            "The previous forced-loop policy reproduces visible door reappearance at1100ms");
    }
    for(int64_t ms:{0,41,1000,10000})
        check(light->frameAt(ms,portalAnimationLoops(*light))==light->frameAt(ms%light->duration,false),
            "Source LOOP light keeps its own source period");
    PortalPlaybackClock clock;
    auto t=clock.sample("scene1","left","left.obj",5000,false);
    check(t.reset&&!t.changed&&t.commonMs==0&&t.stateMs==0,"Each real portal starts at its own installation time");
    t=clock.sample("scene1","left","left.obj",5300,false);
    check(!t.reset&&!t.changed&&t.commonMs==300&&t.stateMs==300,"Unchanged state advances only simulation elapsed time");
    const auto frozen=clock.snapshot();t=clock.sample("scene1","left","left.obj",5300,false);
    check(clock.snapshot()==frozen&&t.stateMs==300,"Redrawing a simulation instant cannot restart or advance the clock");
    t=clock.sample("scene1","left","left.obj",5500,true);
    check(t.changed&&!t.reset&&t.stateMs==0&&t.commonMs==500,"Opening rewinds only state tracks while common tracks continue");
    t=clock.sample("scene1","right","right-boss.obj",5500,true);
    check(t.reset&&t.commonMs==0&&t.stateMs==0,"The right boss and left normal instance clocks remain independent");
    t=clock.sample("scene1","left","left.obj",6000,true);
    check(!t.reset&&!t.changed&&t.stateMs==500&&t.commonMs==1000,"Another instance does not reset an existing door");
    t=clock.sample("scene1","left","left.obj",6100,false);
    check(t.changed&&t.stateMs==0&&t.commonMs==1100,"Closing also restarts its selected state tracks");
    t=clock.sample("scene1","left","another.obj",6200,false);
    check(t.reset&&t.stateMs==0&&t.commonMs==0,"Changing the actual source OBJ creates a fresh binding");
    t=clock.sample("scene1","left","another.obj",6000,false);
    check(t.reset&&t.stateMs==0&&t.commonMs==0,"Simulation rewind cancels stale transient elapsed time");
    t=clock.sample("scene2","left","another.obj",6000,false);
    check(t.reset&&clock.snapshot().at("instances").size()==1,"A fresh room identity removes the previous scene clocks");
    clock.clear();check(clock.snapshot().at("instances").empty(),"Explicit runtime reset clears all transient door clocks");
    bool invalid=false;try{clock.sample("","x","y",1,false);}catch(const std::invalid_argument&){invalid=true;}
    check(invalid,"Invalid simulation instance identity is diagnosed");
    Animation bad;bad.path="diagnostic-invalid-loop";bad.globals["0"]=1;invalid=false;
    try{portalAnimationLoops(bad);}catch(const std::invalid_argument&){invalid=true;}
    check(invalid,"A wrong typed binary LOOP operand is diagnosed rather than converted silently");
    Json cadence=Json::array();
    for(int fps:{30,60,144,240}) {
        PortalPlaybackClock renderClock;Json selected=Json::array();int64_t simulated=0;
        // Real fixed tick schedule: lower render rates catch up multiple ticks;
        // higher rates render the same tick repeatedly. State is published at tick30.
        for(int renderFrame=0;simulated<120;++renderFrame) {
            const int64_t target=std::min<int64_t>(120,int64_t(renderFrame)*60/fps);
            while(simulated<target) {
                ++simulated;
                auto time=renderClock.sample("cadence","left","left.obj",simulated*1000/60,simulated>=30);
                if(simulated==30||simulated==60||simulated==90||simulated==120)
                    selected.push_back({{"tick",simulated},{"state_ms",time.stateMs},{"common_ms",time.commonMs},
                        {"alpha",door->samplePose(double(time.stateMs),false).rgba[3]}});
            }
            (void)renderClock.sample("cadence","left","left.obj",simulated*1000/60,simulated>=30);
        }
        cadence.push_back({{"fps",fps},{"samples",selected}});
    }
    for(size_t i=1;i<cadence.size();++i)check(cadence[i].at("samples")==cadence[0].at("samples"),
        "30/60/144/240 renders and catch-up ticks produce identical simulation-time door states");
    return {{"status","pass"},{"checks",checks},{"objects",objects.size()},{"animations",seen.size()},
        {"loop",loops},{"nonloop",nonloops},{"source_samples",samples},{"cadence",cadence},
        {"scope","Current1031 source LOOP and explicit inferred per-instance simulation transition policy; native controller parity pending user comparison"}};
}
}
