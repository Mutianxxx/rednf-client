#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <string_view>

// Portable numeric adapter. No EXE addresses, protected layouts, content IDs,
// source mutation, renderer dependency or allocation belongs in this header.
// Basis: immutable releases/20261020-01/analysis/combat_render/{transform,
// interpolation}/README.md and interpolation/native-vectors.json. Applying
// those 60US contracts to 1031 remains a cross-version inference.
namespace dnf::ani_render {
enum class RenderProfile { Legacy1031, Inferred60Us1031 };
inline constexpr const char *profileName(RenderProfile profile) noexcept {
    return profile == RenderProfile::Inferred60Us1031 ? "inferred60us1031" : "legacy1031";
}
inline constexpr const char *profileEvidence(RenderProfile profile) noexcept {
    return profile == RenderProfile::Inferred60Us1031 ? "cross-version-inference-from-60US" : "existing-1031-reconstruction";
}

struct Pose {
    std::array<double, 2> position{0, 0};
    std::array<double, 2> rate{1, 1};
    double angle = 0; // Authored radians; full revolutions must remain intact.
    std::array<double, 4> rgba{255, 255, 255, 255};
};
// The owner selects the discrete source/target frame and its clock. IMAGE,
// GRAPHIC EFFECT, boxes and events deliberately do not occur in numeric Pose.
struct SampleContext {
    double elapsed = 0, span = 0; // Integral source-DELAY clock units.
    bool enabled = true, requested = true, frozen = false, ended = false, hasNext = true;
};
struct Sample {
    Pose pose;
    bool active = false;
    double ratio = 0;
};
inline uint8_t colorByte(double value) noexcept {
    if (!std::isfinite(value)) return 0;
    double wrapped = std::fmod(std::trunc(value), 256.0);
    if (wrapped < 0) wrapped += 256;
    return static_cast<uint8_t>(wrapped);
}
inline double float32(double value) noexcept { return static_cast<double>(static_cast<float>(value)); }
inline double nativeLinear(double a, double b, double elapsed, double span) noexcept {
    a = float32(a);
    b = float32(b);
    // Preserve the native branch order, including endpoints.
    if (elapsed >= span) return b;
    if (elapsed <= 0) return a;
    return a + (b - a) * elapsed / span;
}
inline Sample samplePose(const Pose &from, const Pose &to, const SampleContext &context,
                         RenderProfile profile = RenderProfile::Legacy1031) noexcept {
    Sample out{from};
    const bool inferred = profile == RenderProfile::Inferred60Us1031;
    if (inferred) {
        for (int i = 0; i < 2; ++i) out.pose.rate[i] = float32(from.rate[i]);
        out.pose.angle = float32(from.angle);
        for (int i = 0; i < 4; ++i) out.pose.rgba[i] = colorByte(from.rgba[i]);
    }
    const double elapsed = inferred ? std::trunc(context.elapsed) : context.elapsed;
    const double span = context.span;
    out.active = context.enabled && context.requested && !context.frozen && !context.ended &&
                 context.hasNext && std::isfinite(elapsed) && std::isfinite(span) && span > 0;
    if (!out.active) return out;
    out.ratio = std::clamp(elapsed / span, 0.0, 1.0);
    const auto linear = [&](double a, double b) {
        return inferred ? nativeLinear(a, b, elapsed, span) : a + (b - a) * out.ratio;
    };
    for (int i = 0; i < 2; ++i) {
        out.pose.position[i] = linear(from.position[i], to.position[i]);
        out.pose.rate[i] = linear(from.rate[i], to.rate[i]);
        if (inferred) {
            out.pose.position[i] = std::trunc(out.pose.position[i]);
            out.pose.rate[i] = float32(out.pose.rate[i]);
        }
    }
    out.pose.angle = linear(from.angle, to.angle);
    if (inferred) out.pose.angle = float32(out.pose.angle);
    for (int i = 0; i < 4; ++i) {
        out.pose.rgba[i] = linear(inferred ? colorByte(from.rgba[i]) : from.rgba[i],
                                  inferred ? colorByte(to.rgba[i]) : to.rgba[i]);
        if (inferred) out.pose.rgba[i] = colorByte(out.pose.rgba[i]);
    }
    return out;
}

struct Point { double x = 0, y = 0; };
struct QuadInput {
    Pose pose;
    double actorX = 0, actorY = 0, actorZ = 0;
    double cropX = 0, cropY = 0, width = 0, height = 0;
    int direction = 1; // Adapter convention: -1 left, +1 right.
};
struct Quad { std::array<Point, 4> vertices; }; // TL, TR, BR, BL; UV order unchanged.
inline Quad makeQuad(const QuadInput &input,
                     RenderProfile profile = RenderProfile::Legacy1031) noexcept {
    const bool inferred = profile == RenderProfile::Inferred60Us1031;
    const double angle = inferred ? -input.pose.angle : input.pose.angle;
    const double c = std::cos(angle), s = std::sin(angle);
    const Point uv[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    Quad out;
    for (int i = 0; i < 4; ++i) {
        double x = input.pose.position[0] + input.cropX + uv[i].x * input.width;
        double y = input.pose.position[1] + input.cropY + uv[i].y * input.height;
        double rx, ry;
        if (inferred) {
            // Normal pivot: T(actorX,actorY-Z) * S(output axes) * R(-angle)
            // * T(IMAGEPOS) * crop. Facing is the sign of output rateX.
            rx = (x * c - y * s) * input.pose.rate[0];
            ry = (x * s + y * c) * input.pose.rate[1];
        } else {
            x *= input.pose.rate[0];
            y *= input.pose.rate[1];
            rx = x * c - y * s;
            ry = x * s + y * c;
        }
        out.vertices[i] = {input.actorX + input.direction * rx, input.actorY - input.actorZ + ry};
    }
    return out;
}

enum class BlendMode { Normal, LinearDodge, Unsupported };
// These are adapter-level ANI effect values, not transferred object offsets.
inline constexpr BlendMode classifyBlend(int effect) noexcept {
    return effect == 0 ? BlendMode::Normal : effect == 2 ? BlendMode::LinearDodge : BlendMode::Unsupported;
}
inline constexpr BlendMode classifyBlend(std::string_view effect) noexcept {
    return effect == "NONE" ? BlendMode::Normal : effect == "LINEARDODGE" ? BlendMode::LinearDodge : BlendMode::Unsupported;
}
inline std::array<double, 4> textureModulate(const std::array<double, 4> &texture,
                                           const std::array<double, 4> &frame) noexcept {
    std::array<double, 4> out{};
    for (int i = 0; i < 4; ++i) out[i] = texture[i] * frame[i] / 255.0;
    return out; // Frame alpha participates exactly once.
}
inline std::array<double, 3> blendRgb(const std::array<double, 3> &source,
                                    const std::array<double, 3> &destination,
                                    double effectiveAlpha, BlendMode mode) noexcept {
    if (mode == BlendMode::Unsupported) return destination;
    const double alpha = std::clamp(effectiveAlpha / 255.0, 0.0, 1.0);
    std::array<double, 3> out{};
    for (int i = 0; i < 3; ++i)
        out[i] = std::clamp(source[i] * alpha + destination[i] *
            (mode == BlendMode::LinearDodge ? 1.0 : 1.0 - alpha), 0.0, 255.0);
    return out;
}
} // namespace dnf::ani_render
