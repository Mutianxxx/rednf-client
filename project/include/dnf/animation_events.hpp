#pragma once
#include "resources.hpp"
namespace dnf {
// Native ANI prop23 -> keyframe+BE -> instance+1E8. The immutable property
// keeps its original int32; this playback cursor uses the native low word.
// See reports/combat-native-reverse/animation-events/README.md.
class AnimationEventCursor {
    int lastFrame_ = -1;
    uint16_t pending_ = 0xffff;
  public:
    void reset() { lastFrame_ = -1; pending_ = 0xffff; }
    void update(const Animation &animation, int frame, bool suppressed = false);
    int lastFrame() const { return lastFrame_; }
    uint16_t pending() const { return pending_; }
    bool matches(uint16_t value) const { return pending_ == value; }
    bool consume(uint16_t value) {
        if (!matches(value)) return false;
        pending_ = 0xffff;
        return true;
    }
};
} // namespace dnf
