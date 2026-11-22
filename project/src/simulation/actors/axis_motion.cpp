#include "dnf/axis_motion.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdexcept>

namespace dnf {
namespace {
int32_t wrappedProduct(int32_t a, int32_t b) {
    const uint32_t bits = uint32_t(a) * uint32_t(b);
    int32_t result;
    std::memcpy(&result, &bits, sizeof result);
    return result;
}
} // namespace

float advanceAxisMotion(AxisMotion &motion, int32_t elapsedMs) {
    if (elapsedMs < 0 || motion.accelerationRemainingMs < -1 || !std::isfinite(motion.velocity))
        throw std::invalid_argument("Unsupported axis motion time/velocity");
    if (!elapsedMs) {
        // The native stop==dt branch still retires an already expired
        // acceleration, even when no clock time has elapsed.
        if (motion.accelerationRemainingMs == 0) motion.acceleration = 0;
        return 0;
    }
    constexpr float millisecondsToSeconds = 0.001f; // 每毫秒 0.001 秒的换算常量
    float averageVelocity = motion.velocity;
    if (motion.acceleration) {
        const float oldVelocity = motion.velocity;
        const int32_t activeMs = motion.accelerationRemainingMs == -1 ? elapsedMs :
            std::min(elapsedMs, motion.accelerationRemainingMs);
        // Signed IMUL keeps the low 32 bits, then the x87
        // computation stores the new velocity as float32 through virtual +0C.
        motion.velocity = float(static_cast<long double>(oldVelocity) +
            static_cast<long double>(wrappedProduct(motion.acceleration, activeMs)) * millisecondsToSeconds);
        averageVelocity = float((static_cast<long double>(oldVelocity) + motion.velocity) * 0.5f);
        if (activeMs < elapsedMs) {
            // Accelerate until the timer expires, then keep
            // the terminal velocity for the rest of this same time interval.
            averageVelocity = float((static_cast<long double>(motion.velocity) * (elapsedMs - activeMs) +
                static_cast<long double>(activeMs) * averageVelocity) / elapsedMs);
        }
        if (motion.accelerationRemainingMs >= 0) {
            motion.accelerationRemainingMs -= activeMs;
            if (motion.accelerationRemainingMs == 0) motion.acceleration = 0;
        }
    }
    // Two float32 multiplications and a displacement clamp.
    const float scaled = float(elapsedMs) * averageVelocity;
    const float displacement = scaled * millisecondsToSeconds;
    return std::clamp(displacement, -2000.0f, 2000.0f);
}
} // namespace dnf
