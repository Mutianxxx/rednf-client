#include "dnf/skill_preview_timeline.hpp"
#include <cmath>

namespace dnf {
std::vector<FrameSpan> frameSpans(const Animation &animation) {
    std::vector<FrameSpan> spans;
    spans.reserve(animation.frames.size());
    double cursor = 0;
    for (size_t i = 0; i < animation.frames.size(); ++i) {
        // A zero-length frame would make the window unreachable for a
        // boundary-based visit, so treat it as the smallest real duration.
        const double span = std::max(1, animation.frames[i].duration);
        spans.push_back({i, cursor, cursor + span});
        cursor += span;
    }
    return spans;
}

double animationDurationMs(const Animation &animation) {
    double total = 0;
    for (const auto &frame : animation.frames) total += std::max(1, frame.duration);
    return total;
}

void visitFrames(const Animation &animation, double fromMs, double toMs,
                 const std::function<void(const FrameSpan &)> &visit) {
    if (toMs <= fromMs) return;
    const auto spans = frameSpans(animation);
    for (const auto &span : spans) {
        if (span.endMs <= fromMs) continue;
        if (span.startMs >= toMs) break;
        visit(span);
    }
}

size_t frameIndexAt(const Animation &animation, double ms) {
    if (animation.frames.empty()) return 0;
    if (!(ms > 0)) return 0;
    double cursor = 0;
    for (size_t i = 0; i < animation.frames.size(); ++i) {
        cursor += std::max(1, animation.frames[i].duration);
        if (ms < cursor) return i;
    }
    // 40JP holds the last frame when the tail is reached without [LOOP]
    // (anim_parser.cpp:1561-1564).
    return animation.frames.size() - 1;
}

std::optional<FrameSpan> spanAt(const Animation &animation, double ms) {
    const auto spans = frameSpans(animation);
    if (spans.empty()) return std::nullopt;
    for (const auto &span : spans)
        if (ms < span.endMs) return span;
    return spans.back();
}

void PreviewTimeline::reset() {
    ageMs = 0;
    ended = false;
    looped = false;
    body.reset();
    for (auto &layer : layers) layer.clock.reset();
    for (auto &entity : persistents) entity.clock.reset();
}

void PreviewTimeline::advance(double realMs, double speed) {
    // 40JP accumulates whatever the idle loop reports; a stall advances the
    // action by the stalled amount instead of being clipped per frame.
    if (paused || !(realMs > 0) || !(speed > 0)) return;
    looped = false;
    const double dt = realMs * speed;
    ageMs += dt;
    body.advance(dt);
    for (auto &layer : layers) {
        // A layer only starts its clock once the action reaches its birth time,
        // so staggered effect timings stay in step with the body.
        if (ageMs < layer.birthMs) continue;
        layer.clock.advance(dt);
    }
    if (durationMs <= 0) return;
    const double total = std::max(body.ageMs, ageMs);
    if (total < durationMs) return;
    if (!loop) {
        body.ageMs = durationMs;
        ageMs = durationMs;
        ended = true;
        return;
    }
    // Replay: keep the overshoot so repeated passes do not drift slower than
    // wall clock, and let the host rebuild per-pass layers and hits.
    double carry = total - durationMs;
    if (carry >= durationMs) carry = std::fmod(carry, durationMs);
    body.reset();
    body.ageMs = carry;
    ageMs = carry;
    for (auto &layer : layers)
        layer.clock.ageMs = std::max(0.0, carry - layer.birthMs);
    ended = false;
    looped = true;
}
} // namespace dnf
