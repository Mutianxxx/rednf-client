#pragma once
#include <cstdint>

namespace dnf {
// 1031 E581E0, movement=straight-line, changing=keep-last-value. The caller
// must supply its final, already modified velocities. This API only returns
// an unprojected axis displacement: no mirror, rotation, gravity or lifetime.
// Nonnegative int32 times are a portable boundary, not native time clamping.
float particleStraightKeepLast(int32_t startVelocity, int32_t endVelocity,
                               int32_t changingTermMs, int32_t elapsedMs);
} // namespace dnf
