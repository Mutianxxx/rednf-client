#include "dnf/static_motion.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
// Keep the recovered SSE operation boundaries, including int32 -> binary32.
// Native MXCSR was not captured; nearest-even host defaults are the reference.
float f32(float value) { volatile float stored = value; return stored; }

int32_t cvttss2si(float value) {
    // x86 indefinite integer result, including INT_MAX rounded to 2^31.
    if (!std::isfinite(value) || value >= 2147483648.0f || value < -2147483648.0f)
        return std::numeric_limits<int32_t>::min();
    return static_cast<int32_t>(value);
}

void validate(const AxisMotion &motion) {
    if (!std::isfinite(motion.velocity) || motion.accelerationRemainingMs < -1)
        throw std::invalid_argument("Unsupported static axis state");
}
} // namespace

StaticAxisOperands staticAxisOperands(int32_t normalSpeed, int32_t alternateSpeed,
                                     int32_t acceleration, int32_t direction,
                                     bool useAlternate, int32_t scale) {
    float factor = direction == 0 || direction == 2 ? -1.0f :
                   direction == 1 || direction == 3 ? 1.0f : 0.0f;
    if (scale != 1000) {
        factor = f32(f32(f32(static_cast<float>(scale)) * factor) * 0.001f);
    }
    const int32_t speed = useAlternate ? alternateSpeed : normalSpeed;
    return {f32(f32(static_cast<float>(speed)) * factor),
            cvttss2si(f32(f32(static_cast<float>(acceleration)) * factor))};
}

bool calculateAxisDecelerationDuration(AxisMotion &motion) {
    validate(motion);
    const float acceleration = f32(static_cast<float>(motion.acceleration));
    if (!(f32(acceleration * motion.velocity) < 0.0f)) return false;
    const float duration = f32(f32(motion.velocity * -1000.0f) / acceleration);
    // Native CVTTSS2SI can yield INT_MIN. Such a duration is outside the
    // existing portable integrator's supported -1/nonnegative time domain.
    if (!std::isfinite(duration) || duration < 0 || duration >= 2147483648.0f)
        throw std::invalid_argument("Unsupported static axis stop duration");
    motion.accelerationRemainingMs = cvttss2si(duration);
    return true;
}

void applyStaticAxisOperands(AxisMotion &motion, StaticAxisOperands operands,
                             AxisWritePath path, bool calculateStopDuration) {
    validate(motion);
    if (!std::isfinite(operands.velocity) ||
        (path != AxisWritePath::Checked && path != AxisWritePath::Direct))
        throw std::invalid_argument("Unsupported static axis operands/write path");
    AxisMotion next = motion;
    if (path == AxisWritePath::Direct) {
        next.velocity = operands.velocity;
        next.acceleration = operands.acceleration;
        next.accelerationRemainingMs = -1;
    } else {
        // 8B13D0 stores the difference as float64 before comparing it with
        // abs(current velocity)*2^-23; it uses no absolute-speed deadzone.
        const double difference = std::abs(double(next.velocity) - operands.velocity);
        if (difference > std::abs(double(next.velocity)) * 0x1p-23)
            next.velocity = operands.velocity;
        // 8B2660 calls the -1 duration setter only when acceleration changes.
        if (next.acceleration != operands.acceleration) {
            next.acceleration = operands.acceleration;
            next.accelerationRemainingMs = -1;
        }
    }
    if (calculateStopDuration) calculateAxisDecelerationDuration(next);
    motion = next;
}
} // namespace dnf
