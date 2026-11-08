#pragma once
#include "combat.hpp"
#include <cmath>

namespace dnf {
class Renderer;

// Portable display state. These hold/fade durations are reconstruction settings,
// separate from real HP and source UI pixels, pending original-video calibration.
struct TargetHealthState {
    int target = -1, hp = 0, maximum = 1;
    double trailFrom = 0;
    int64_t hitAt = 0, visibleUntil = 0;
    static constexpr int trailHoldMs = 180, trailShrinkMs = 420;
    static constexpr int deathHoldMs = 700, inactivityMs = 5000, fadeMs = 180;
    double ratio() const { return std::clamp(double(hp) / std::max(1, maximum), 0.0, 1.0); }
    double trail(int64_t now) const {
        double t = std::clamp(double(now - hitAt - trailHoldMs) / trailShrinkMs, 0.0, 1.0);
        return std::max(ratio(), trailFrom + (ratio() - trailFrom) * t);
    }
    double opacity(int64_t now) const {
        return target < 0 ? 0 : std::clamp(double(visibleUntil - now) / fadeMs, 0.0, 1.0);
    }
    void reset() { *this = {}; }
    void hit(int id, int current, int maxHp, int previous, int64_t now) {
        double old = target == id ? trail(now) : double(previous) / std::max(1, maxHp);
        target = id; hp = std::max(0, current); maximum = std::max(1, maxHp);
        trailFrom = std::clamp(std::max(old, double(previous) / maximum), ratio(), 1.0);
        hitAt = now;
        visibleUntil = now + (hp == 0 ? deathHoldMs : inactivityMs);
    }
};

// Display-only reconstruction policy. Never changes actor HP, damage or rewards.
// Native per-bar HP quantum remains unproven for this source version.
struct BossHealthGeometry {
    // User-requested rectangle. Source texture is 545x8; slice its 2px borders
    // and expand its center to a 30px area matching the authored face region.
    static constexpr float x=127,y=61,width=538,height=26;
    static constexpr float insetX=3,insetY=2,outerWidth=545,outerHeight=30;
};
struct BossHealthLayerView {
    int remaining=0,total=1,frame=2,behindFrame=2,capacity=1000;
    double ratio=0;
    static BossHealthLayerView split(int hp,int maximum,int capacity=1000) {
        BossHealthLayerView result;maximum=std::max(1,maximum);capacity=std::clamp(capacity,1,maximum);result.capacity=capacity;
        hp=std::clamp(hp,0,maximum);
        result.total=int((int64_t(maximum)+capacity-1)/capacity);
        result.remaining=hp>0?int((int64_t(hp)+capacity-1)/capacity):0;
        result.ratio=hp>0?double((int64_t(hp)-1)%capacity+1)/capacity:0;
        result.frame=2+std::max(0,result.remaining-1)%6;
        result.behindFrame=2+std::max(0,result.remaining-2)%6;return result;
    }
};

class TargetHud {
    std::string monsterPath_;
    std::string cachedPath_, cachedName_, cachedFace_, cachedCategory_;
    EntityHandle targetHandle_;
    int cachedFaceFrame_ = 0;
    bool boss_ = false;
  public:
    TargetHealthState state;
    void reset() { state.reset(); monsterPath_.clear(); boss_ = false; targetHandle_={}; }
    // Call for each hit event, including lethal hits; previous=hp+event.value
    // reconstructs the pre-hit display when the event supplies actual damage.
    void hit(const Actor &actor, int64_t now, int previous = -1) {
        state.hit(actor.id, actor.hp, actor.maxHp, previous < 0 ? actor.maxHp : previous, now);
        monsterPath_ = actor.monsterPath; boss_ = actor.boss;
        targetHandle_=actor.handle;
    }
    // Observe the real target each frame, independent of how many accepted
    // contacts share a tick. Renderer never reconstructs HP from damage sums.
    void observe(const std::vector<Actor> &actors, int64_t now) {
        for(const auto &actor:actors)if(actor.id==state.target) {
            if(actor.handle!=targetHandle_){reset();return;}
            if(actor.hp!=state.hp||actor.maxHp!=state.maximum)
                state.hit(actor.id,actor.hp,actor.maxHp,state.hp,now);
            return;
        }
    }
    void draw(Renderer &renderer, Pvf &pvf, int64_t now, int referenceMaximumHp = 0);
};
} // namespace dnf
