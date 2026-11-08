#pragma once
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

// C++17 clock adapter, with no renderer, wall clock, source mutation or native
// object layout. Arithmetic basis is releases/20261020-01/analysis/combat_motion
// and combat_timeline. 1031 reuse is inference. Ordered frame visits are a
// reconstruction contract, not proof of the original large-step callbacks.
// The selected arithmetic follows the frozen Python model: binary32 rate
// stores and binary64 intermediate expressions. The 46 captured deadline
// vectors match at both archived x87 precisions, but do not prove all inputs
// equivalent to x87. In particular, division followed by multiplication can
// truncate a nominal-rate precision edge (delay29/rate100) to28 here. Do not
// simplify that expression or claim this adapter recovers the client's actual
// control word. SourceDelay100 bypasses percent arithmetic and preserves29.
namespace dnf::ani_clock {
static_assert(sizeof(float) == 4 && std::numeric_limits<float>::is_iec559 &&
    std::numeric_limits<float>::digits == 24, "ANI clock requires IEEE binary32 rates");
static_assert(sizeof(double) == 8 && std::numeric_limits<double>::is_iec559 &&
    std::numeric_limits<double>::digits == 53, "ANI clock requires binary64 intermediate arithmetic");
inline constexpr const char *arithmeticProfileName() noexcept {
    return "binary32-rate-stores-binary64-intermediates";
}
enum class ClockPolicy { SourceDelay100, Inferred60UsPercentDeadlines };
enum class RatePath { Installation, Refresh, ExplicitPercent };
inline constexpr const char *policyName(ClockPolicy policy) noexcept {
    return policy == ClockPolicy::SourceDelay100 ? "source-delay-rate100" : "inferred60us-percent-deadlines";
}
inline float storedFloat(double value) {
    if (!std::isfinite(value) || std::abs(value) > std::numeric_limits<float>::max())
        throw std::invalid_argument("ANI rate must be finite binary32");
    volatile float stored = static_cast<float>(value);
    return stored;
}
inline float positiveRate(double value) {
    const float rate = storedFloat(value);
    if (!(rate > 0)) throw std::invalid_argument("ANI playback requires a positive finite rate");
    return rate;
}
// Exposed separately for native-helper comparisons; normal playback rejects 0.
inline float nativeZeroRate(double value) {
    const float rate = storedFloat(value);
    if (rate < 0) throw std::invalid_argument("Negative ANI rate is outside this adapter");
    return rate == 0 ? 1.0f : rate;
}
inline float resolveRate(double input, RatePath path, double globalInstallFactor = 100.0) {
    if (path == RatePath::ExplicitPercent) return positiveRate(input);
    if (!std::isfinite(input) || input != std::trunc(input) || input < 0 ||
            input > std::numeric_limits<int32_t>::max())
        throw std::invalid_argument("ANI speed input requires a nonnegative int32 stat");
    if (path == RatePath::Refresh)
        return positiveRate(input * static_cast<double>(0.1f));
    if (path != RatePath::Installation) throw std::invalid_argument("Unknown ANI rate path");
    // Preserve the distinct constants and only the recovered memory stores.
    return positiveRate(static_cast<double>(storedFloat(input)) * positiveRate(globalInstallFactor) *
                        static_cast<double>(0.001f));
}
inline int32_t frameDuration(int32_t decodedDelay, float rate) {
    if (decodedDelay < 0) throw std::invalid_argument("Negative decoded ANI delay");
    positiveRate(rate);
    const double negative = std::trunc(static_cast<double>(decodedDelay) / rate * -100.0f);
    if (!std::isfinite(negative) || negative < -double(std::numeric_limits<int32_t>::max()))
        throw std::overflow_error("ANI frame deadline exceeds supported int32 arithmetic");
    return static_cast<int32_t>(-negative);
}
inline uint64_t addChecked(uint64_t a, uint64_t b) {
    if (b > std::numeric_limits<uint64_t>::max() - a) throw std::overflow_error("ANI clock overflow");
    return a + b;
}
inline uint64_t multiplyChecked(uint64_t a, uint64_t b) {
    if (b && a > std::numeric_limits<uint64_t>::max() / b) throw std::overflow_error("ANI clock overflow");
    return a * b;
}
struct ClipView {
    const int32_t *delays = nullptr;
    size_t count = 0;
    bool loop = false;
    // Optional decoded body delays override only min(body, child) entries.
    // Both arrays are borrowed immutable content owned by the host adapter.
    const int32_t *sharedDelays = nullptr;
    size_t sharedCount = 0;
    int32_t delay(size_t frame) const {
        if (!delays || frame >= count || (sharedCount && !sharedDelays))
            throw std::invalid_argument("Invalid ANI clip view");
        const auto value = sharedDelays && frame < sharedCount ? sharedDelays[frame] : delays[frame];
        if (value < 0) throw std::invalid_argument("Negative decoded ANI delay");
        return value;
    }
};
inline int32_t frameSpan(ClipView clip, size_t frame, float rate, ClockPolicy policy) {
    if (policy == ClockPolicy::SourceDelay100) {
        if (rate != 100.0f) throw std::invalid_argument("Source-delay clock accepts rate100 only");
        return clip.delay(frame);
    }
    if (policy != ClockPolicy::Inferred60UsPercentDeadlines) throw std::invalid_argument("Unknown ANI clock policy");
    return frameDuration(clip.delay(frame), rate);
}
inline uint64_t deadlineCycle(ClipView clip, float rate, ClockPolicy policy) {
    if (!clip.count) throw std::invalid_argument("Empty ANI clip");
    uint64_t total = 0;
    for (size_t i = 0; i < clip.count; ++i) total = addChecked(total, uint64_t(frameSpan(clip, i, rate, policy)));
    if (!total) throw std::invalid_argument("ANI clip has no advancing deadline");
    return total;
}
// Native duration helper has its own reciprocal/multiplication order. Do not
// substitute this value for the cycle of per-frame playback deadlines.
inline uint64_t totalDuration(ClipView clip, float rate) {
    positiveRate(rate);
    if (!clip.count) throw std::invalid_argument("Empty ANI clip");
    const double reciprocal = 1.0 / rate;
    uint64_t total = 0;
    for (size_t i = 0; i < clip.count; ++i) {
        const double value = std::trunc(clip.delay(i) * reciprocal * 100.0f);
        if (!std::isfinite(value) || value > double(std::numeric_limits<int32_t>::max()))
            throw std::overflow_error("ANI total-duration term exceeds int32");
        total = addChecked(total, uint64_t(value));
    }
    return total;
}
inline uint64_t rescaleElapsed(uint64_t elapsed, float oldRate, float newRate) {
    positiveRate(oldRate); positiveRate(newRate);
    if (elapsed > uint64_t(std::numeric_limits<int32_t>::max()))
        throw std::overflow_error("ANI rate change exceeds native signed elapsed domain");
    const double value = std::trunc(static_cast<double>(elapsed) / newRate * oldRate);
    if (!std::isfinite(value) || value > double(std::numeric_limits<int32_t>::max()))
        throw std::overflow_error("ANI rescaled elapsed exceeds int32");
    return uint64_t(value);
}
inline uint64_t millisecondsAtTick(uint64_t tick) {
    return addChecked(multiplyChecked(tick / 60, 1000), (tick % 60) * 1000 / 60);
}
struct TickInput {
    uint64_t tick = 0;
    uint32_t deltaMilliseconds = 0;
    bool paused = false;
};
struct Snapshot {
    ClockPolicy policy = ClockPolicy::SourceDelay100;
    size_t frame = 0, nextFrame = 0;
    uint64_t lastTick = 0, elapsedMs = 0, frameStartMs = 0, nextDeadlineMs = 0;
    uint64_t localMs = 0, spanMs = 0, visit = 1, loopCount = 0, rateRevision = 1;
    float ratePercent = 100;
    bool ended = false, loop = false, paused = false;
};
struct FrameVisit {
    size_t frame = 0;
    uint64_t visit = 0, loopCount = 0, startMs = 0, deadlineMs = 0;
};
struct Advance {
    Snapshot snapshot;
    std::vector<FrameVisit> visits;
};
inline void completeSnapshot(Snapshot &state, ClipView clip) {
    state.nextFrame = state.frame + 1 < clip.count ? state.frame + 1 : clip.loop ? 0 : state.frame;
    state.localMs = state.elapsedMs - state.frameStartMs;
    state.spanMs = state.nextDeadlineMs - state.frameStartMs;
}
// Stateless projection has no event side effects. It is suitable for a child
// ANI sharing root elapsed/rate. It does not independently consume a tick.
inline Snapshot followRoot(ClipView child, const Snapshot &root, size_t budget = 4096) {
    const auto cycle = deadlineCycle(child, root.ratePercent, root.policy);
    if (!budget) throw std::invalid_argument("ANI projection requires a frame budget");
    Snapshot out = root;
    out.frame = 0; out.ended = false; out.loop = child.loop; out.loopCount = 0; out.visit = 1;
    out.frameStartMs = 0;
    if (child.loop && child.count > 1) {
        out.loopCount = root.elapsedMs / cycle;
        out.frameStartMs = multiplyChecked(out.loopCount, cycle);
        out.visit = addChecked(multiplyChecked(out.loopCount, uint64_t(child.count)), 1);
    }
    out.nextDeadlineMs = addChecked(out.frameStartMs, uint64_t(frameSpan(child, 0, out.ratePercent, out.policy)));
    size_t entered = 1;
    while (out.elapsedMs >= out.nextDeadlineMs) {
        if (out.frame + 1 == child.count) {
            if (!child.loop) out.ended = true;
            // Native one-frame loops retain their single installed frame.
            break;
        }
        if (entered == budget) throw std::length_error("ANI projection frame budget exhausted");
        ++entered; ++out.frame;
        out.visit = addChecked(out.visit, 1);
        out.frameStartMs = out.nextDeadlineMs;
        out.nextDeadlineMs = addChecked(out.frameStartMs, uint64_t(frameSpan(child, out.frame, out.ratePercent, out.policy)));
    }
    completeSnapshot(out, child);
    return out;
}
class Cursor {
    ClipView clip_;
    Snapshot state_;
    bool installed_ = false;

    void seek(uint64_t elapsed, std::vector<FrameVisit> &visits, size_t budget) {
        state_.elapsedMs = elapsed;
        while (!state_.ended && elapsed >= state_.nextDeadlineMs) {
            if (state_.frame + 1 == clip_.count) {
                if (!clip_.loop) { state_.ended = true; break; }
                if (clip_.count == 1) break;
            }
            if (visits.size() == budget) throw std::length_error("ANI frame-visit budget exhausted");
            if (++state_.frame == clip_.count) {
                state_.frame = 0;
                state_.loopCount = addChecked(state_.loopCount, 1);
            }
            state_.visit = addChecked(state_.visit, 1);
            state_.frameStartMs = state_.nextDeadlineMs;
            state_.nextDeadlineMs = addChecked(state_.frameStartMs,
                uint64_t(frameSpan(clip_, state_.frame, state_.ratePercent, state_.policy)));
            visits.push_back({state_.frame, state_.visit, state_.loopCount, state_.frameStartMs, state_.nextDeadlineMs});
        }
        completeSnapshot(state_, clip_);
    }
  public:
    // Return initial frame visits, including zero-delay prefixes, exactly once.
    Advance install(ClipView clip, float rate = 100,
                    ClockPolicy policy = ClockPolicy::SourceDelay100,
                    uint64_t lastTick = 0, size_t budget = 4096) {
        positiveRate(rate);
        deadlineCycle(clip, rate, policy);
        millisecondsAtTick(lastTick);
        if (!budget) throw std::invalid_argument("ANI installation requires a frame budget");
        Cursor next;
        next.clip_ = clip; next.installed_ = true;
        next.state_.policy = policy; next.state_.lastTick = lastTick;
        next.state_.loop = clip.loop; next.state_.ratePercent = rate;
        next.state_.nextDeadlineMs = uint64_t(frameSpan(clip, 0, rate, policy));
        Advance result;
        result.visits.push_back({0, 1, 0, 0, next.state_.nextDeadlineMs});
        next.seek(0, result.visits, budget);
        result.snapshot = next.state_;
        *this = next;
        return result;
    }
    const Snapshot &snapshot() const {
        if (!installed_) throw std::logic_error("ANI cursor is not installed");
        return state_;
    }
    Advance advance(TickInput input, size_t budget = 4096) {
        snapshot();
        if (state_.lastTick == std::numeric_limits<uint64_t>::max() || input.tick != state_.lastTick + 1 ||
                input.deltaMilliseconds != millisecondsAtTick(input.tick) - millisecondsAtTick(input.tick - 1))
            throw std::invalid_argument("ANI cursor requires one consecutive 60 Hz tick");
        if (!budget) throw std::invalid_argument("ANI advance requires a frame budget");
        Cursor next = *this;
        next.state_.lastTick = input.tick; next.state_.paused = input.paused;
        Advance result;
        next.seek(addChecked(state_.elapsedMs, input.paused ? 0 : input.deltaMilliseconds), result.visits, budget);
        result.snapshot = next.state_;
        *this = next;
        return result;
    }
    // Native rate changes reset/reproject the tree. The adapter emits no old
    // visits on reprojection, so the host's existing event ledger cannot replay.
    Snapshot setRate(float rate, size_t budget = 4096) {
        snapshot(); positiveRate(rate);
        if (state_.policy == ClockPolicy::SourceDelay100 && rate != 100)
            throw std::invalid_argument("Source-delay clock cannot be scaled twice");
        if (rate == state_.ratePercent) return state_;
        Snapshot root = state_;
        root.elapsedMs = rescaleElapsed(state_.elapsedMs, state_.ratePercent, rate);
        root.ratePercent = rate;
        root.rateRevision = addChecked(state_.rateRevision, 1);
        auto next = followRoot(clip_, root, budget);
        next.visit = state_.visit;
        state_ = next;
        return state_;
    }
};
} // namespace dnf::ani_clock
