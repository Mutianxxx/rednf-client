#include "dnf/particle_motion.hpp"
#include <cstring>
#include <stdexcept>

namespace dnf {
namespace {
// Preserve the source's binary32 operation boundaries even on backends that
// permit excess intermediate precision. Do not build this file with fast-math.
float f32(float value) { volatile float result = value; return result; }
int32_t wrappedProduct(int32_t a, int32_t b) {
    const uint32_t bits = uint32_t(a) * uint32_t(b);
    int32_t result;
    std::memcpy(&result, &bits, sizeof result);
    return result;
}
} // namespace

float particleStraightKeepLast(int32_t startVelocity, int32_t endVelocity,
                               int32_t changingTermMs, int32_t elapsedMs) {
    if (changingTermMs < 0 || elapsedMs < 0)
        throw std::invalid_argument("Unsupported negative particle time");
    constexpr float scale = 0.001f; // Native VA 1565E18, bits 3A83126F.
    if (changingTermMs == 0)
        return f32(f32(float(wrappedProduct(startVelocity, elapsedMs))) * scale);
    const float start = f32(float(startVelocity)), end = f32(float(endVelocity));
    const float elapsed = f32(float(elapsedMs)), term = f32(float(changingTermMs));
    float distance;
    if (elapsedMs < changingTermMs) {
        distance = f32(end - start);
        distance = f32(distance * elapsed);
        distance = f32(distance / term);
        distance = f32(distance + start);
        distance = f32(distance + start);
        distance = f32(distance * 0.5f);
        distance = f32(distance * elapsed);
        return f32(distance * scale);
    }
    distance = f32(start + end);
    distance = f32(distance * 0.5f);
    distance = f32(distance * term);
    distance = f32(distance * scale);
    // Signed subtraction cannot overflow for nonnegative t >= T.
    float tail = f32(f32(float(elapsedMs - changingTermMs)) * end);
    tail = f32(tail * scale);
    return f32(distance + tail);
}
} // namespace dnf
