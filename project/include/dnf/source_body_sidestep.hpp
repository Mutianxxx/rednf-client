#pragma once
#include "resources.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <stdexcept>

namespace dnf {
// A reviewed per-descriptor host policy. Current source explains the motion,
// but does not author its amplitude, turn point or native coordinate setter.
struct SourceBodySidestepPolicy {
    int returnFrame=-1;
    double turnSourceMs=0,returnSourceMs=0,distance=0;
    const char *id="inferred-current1031-mage-upper-side-return-v1";
    Json snapshot() const {
        return {{"policy",id},{"classification","inferred_beta"},{"native_verified",false},
            {"return_frame",returnFrame},{"turn_source_ms",turnSourceMs},{"return_source_ms",returnSourceMs},
            {"distance_pixels",distance},{"path","up/down sampled on accepted action; linear outward and back"},
            {"collision","swept at most one logical pixel per probe; blocked return never teleports"}};
    }
};
struct SourceBodySidestepState {
    double originY=0;
    int direction=0;
    double extent=0,lastSourceMs=0;
    bool outwardBlocked=false,returnBlocked=false;
    Json snapshot() const {
        return {{"origin_y",originY},{"direction",direction},{"extent",extent},{"source_ms",lastSourceMs},
            {"outward_blocked",outwardBlocked},{"return_blocked",returnBlocked}};
    }
};
// Translate runtime frame-local progress into immutable source ANI time. This
// does not advance a second clock or replace the selected arithmetic contract.
inline double sourceBodyElapsedMs(const Animation &body,const ani_clock::Snapshot &clock) {
    if(clock.ended)return double(body.duration);
    if(clock.frame>=body.frames.size())throw std::invalid_argument("Sidestep body frame outside source");
    double source=0;
    for(size_t i=0;i<clock.frame;++i)source+=body.frames[i].duration;
    const auto fraction=clock.spanMs?std::clamp(double(clock.localMs)/double(clock.spanMs),0.0,1.0):0.0;
    return source+fraction*body.frames[clock.frame].duration;
}
inline double advanceSourceBodySidestep(const SourceBodySidestepPolicy &policy,SourceBodySidestepState &state,
    double sourceMs,double x,double y,const std::function<bool(double,double)> &canWalk) {
    if(!std::isfinite(sourceMs)||!std::isfinite(y)||!std::isfinite(x)||policy.distance<0||
       !(policy.turnSourceMs>0)||!(policy.returnSourceMs>policy.turnSourceMs))
        throw std::invalid_argument("Invalid reviewed body sidestep policy/progress");
    sourceMs=std::max(state.lastSourceMs,sourceMs);
    const auto previous=state.lastSourceMs;state.lastSourceMs=sourceMs;
    if(!state.direction)return y;
    const auto sweep=[&](double target,bool outward) {
        while(std::abs(target-y)>1e-9) {
            const auto next=y+std::clamp(target-y,-1.0,1.0);
            if(!canWalk(x,next)) {
                if(outward)state.outwardBlocked=true;else state.returnBlocked=true;
                break;
            }
            y=next;
        }
        if(outward)state.extent=std::max(state.extent,std::abs(y-state.originY));
    };
    // Consume a crossed turn boundary even when a fast clock visits multiple
    // source frames in one tick; collision still observes the entire path.
    if(previous<policy.turnSourceMs&&!state.outwardBlocked)
        sweep(state.originY+state.direction*policy.distance*std::min(sourceMs,policy.turnSourceMs)/policy.turnSourceMs,true);
    if(sourceMs>policy.turnSourceMs) {
        // Return only the distance actually accepted by ground collision.
        const auto remaining=std::clamp((policy.returnSourceMs-sourceMs)/
            (policy.returnSourceMs-policy.turnSourceMs),0.0,1.0);
        sweep(state.originY+state.direction*state.extent*remaining,false);
    }
    return y;
}
} // namespace dnf
