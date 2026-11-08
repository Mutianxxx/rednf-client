#pragma once
#include <cstdint>

namespace dnf {
// Arithmetic subset of 1031 movement-unit 8B1C40. Collision, provider values,
// state transitions and the caller's clock are separate contracts.
struct AxisMotion {
    float velocity = 0;
    int32_t acceleration = 0;
    int32_t accelerationRemainingMs = -1; // -1: acceleration has no stop timer
};

// Updates velocity/remaining acceleration and returns a displacement, clamped
// to +/-2000 before the caller applies its own collision/landing policy.
// elapsedMs >= 0 and remaining >= -1 are portable API constraints. The native
// x87 control word has not been captured; bit-for-bit FPU parity is not claimed.
float advanceAxisMotion(AxisMotion &motion, int32_t elapsedMs);
} // namespace dnf
