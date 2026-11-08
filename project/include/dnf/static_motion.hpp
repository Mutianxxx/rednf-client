#pragma once
#include "dnf/axis_motion.hpp"

namespace dnf {
// Effective protected actor values supplied by the caller, not base CHR/SKL
// values. 8328A0 selects a normal/alternate speed, then applies direction and
// the independent 1000-based actor multiplier to speed and acceleration.
struct StaticAxisOperands {
    float velocity = 0;
    int32_t acceleration = 0;
};

StaticAxisOperands staticAxisOperands(int32_t normalSpeed, int32_t alternateSpeed,
                                     int32_t acceleration, int32_t direction,
                                     bool useAlternate, int32_t scale);

enum class AxisWritePath { Checked, Direct };

// The caller must already have passed the native owner/authority gates.
// Checked reproduces the bounded 8B13D0/8B2660 storage semantics; Direct
// reproduces 8328A0's unconditional writes and resets the duration to -1.
// This does not dispatch protected storage, callbacks or dirty notifications.
void applyStaticAxisOperands(AxisMotion &motion, StaticAxisOperands operands,
                             AxisWritePath path, bool calculateStopDuration);

// 8B0600: only opposite-sign float32 velocity*acceleration replaces the
// acceleration duration with trunc((velocity * -1000.f) / float(acceleration)).
// This is not a velocity clamp. Unsupported nonfinite/overflow durations are
// rejected before mutation as a portable API boundary.
bool calculateAxisDecelerationDuration(AxisMotion &motion);
} // namespace dnf
