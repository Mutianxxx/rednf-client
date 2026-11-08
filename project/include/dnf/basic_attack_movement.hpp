#pragma once
#include "dnf/axis_motion.hpp"
#include "dnf/resources.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <optional>
#include <stdexcept>

namespace dnf {
// User-requested beta behavior, not a recovered common native dash setter.
// The current ATMage NUT supplies one 450/-500 example; it does not establish
// universal per-job acceleration. Keep the candidate constants in one policy.
struct BasicAttackMovementPolicy {
    bool enabled = true;
    double dashBoost = 1.5;
    int32_t maximumGlideMs = 300;
    Json json() const {
        return {{"id",enabled?"inferred-user-basic-attack-movement-v1":"legacy-stationary-basic-attack-v1"},
            {"classification","user_requested_beta_with_inferred_parameters"},{"dash_boost",dashBoost},
            {"maximum_glide_ms",maximumGlideMs},{"duration","minimum of effective source clip and policy cap"},
            {"air_control","direction input at effective source walk speed; ordinary aerial attacks only"},
            {"native_shared_acceleration_verified",false},{"arithmetic","1031 advanceAxisMotion with explicit stop-at-zero policy"}};
    }
};
struct BasicAttackGlide {
    AxisMotion x,y;
    int32_t remainingMs = 0;
    static BasicAttackGlide begin(double vx,double vy,uint64_t sourceMs,const BasicAttackMovementPolicy &policy) {
        if(!std::isfinite(vx)||!std::isfinite(vy)||std::abs(vx)>1000000||std::abs(vy)>1000000||
           !std::isfinite(policy.dashBoost)||policy.dashBoost<1||policy.dashBoost>4||
           policy.maximumGlideMs<1||policy.maximumGlideMs>2000)
            throw std::invalid_argument("Unsupported basic attack movement candidate");
        BasicAttackGlide out;
        if(!policy.enabled||!sourceMs)return out;
        out.remainingMs=int32_t(std::min<uint64_t>(sourceMs,uint64_t(policy.maximumGlideMs)));
        const auto axis=[&](double v) {
            const double initial=v*policy.dashBoost;
            const double acceleration=std::ceil(std::abs(initial)*1000.0/out.remainingMs);
            if(acceleration>INT32_MAX)throw std::overflow_error("Basic attack glide acceleration overflow");
            return AxisMotion{float(initial),initial>0?-int32_t(acceleration):initial<0?int32_t(acceleration):0,-1};
        };
        out.x=axis(vx);out.y=axis(vy);return out;
    }
    std::array<double,2> advance(int32_t elapsedMs) {
        if(elapsedMs<0)throw std::invalid_argument("Negative basic attack movement time");
        const auto dt=std::min(elapsedMs,remainingMs);
        const auto axis=[&](AxisMotion &v) {
            if(!dt||!v.velocity)return 0.0;
            const auto original=v.velocity;
            const auto displacement=advanceAxisMotion(v,dt);
            if(v.velocity*original<=0)v.velocity=0;
            // Integer acceleration may overshoot a sub-millisecond residual
            // speed. The user policy stops at zero instead of reversing.
            return double(original>0?std::max(0.0f,displacement):std::min(0.0f,displacement));
        };
        const std::array<double,2> displacement{axis(x),axis(y)};
        remainingMs-=dt;
        if(!remainingMs)x.velocity=y.velocity=0;
        return displacement;
    }
    void blockX() noexcept { x.velocity=0; }
    void blockY() noexcept { y.velocity=0; }
    Json json() const { return {{"remaining_ms",remainingMs},{"velocity",{x.velocity,y.velocity}},{"acceleration",{x.acceleration,y.acceleration}}}; }
};
inline uint64_t basicAttackMovementClipMs(const Animation &clip,double attackPerMille,
                                        std::optional<ani_clock::ClockPolicy> clock) {
    if(clock) {
        float rate=100;
        if(*clock==ani_clock::ClockPolicy::Inferred60UsPercentDeadlines) {
            if(!std::isfinite(attackPerMille)||attackPerMille<1||attackPerMille>INT32_MAX)
                throw std::invalid_argument("Invalid basic attack movement speed stat");
            rate=ani_clock::resolveRate(int32_t(attackPerMille),ani_clock::RatePath::Installation);
        } else if(*clock!=ani_clock::ClockPolicy::SourceDelay100)
            throw std::invalid_argument("Unknown basic attack movement clock");
        std::vector<int32_t> delays;delays.reserve(clip.frames.size());
        for(const auto &frame:clip.frames)delays.push_back(frame.duration);
        return ani_clock::deadlineCycle({delays.data(),delays.size(),false},rate,*clock);
    }
    const double attackRate=attackPerMille/1000.0;
    if(!std::isfinite(attackRate)||attackRate<0)throw std::invalid_argument("Invalid basic attack movement rate");
    if(!attackRate||clip.duration<=0)return 0;
    return uint64_t(std::ceil(double(clip.duration)/attackRate));
}
} // namespace dnf
