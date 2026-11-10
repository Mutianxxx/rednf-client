#pragma once
#include "resources.hpp"
#include <algorithm>
#include <array>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace dnf {
class Assets;

// 40JP keeps every animation's progress as an accumulated millisecond value and
// freezes it per object when a hit lands (PauseClock, time_system.h:40-51). The
// viewer mirrors that: one clock per drawn layer, no fixed tick, no frame count.
struct PreviewClock {
    double ageMs = 0;
    double freezeRemainingMs = 0;

    void reset() { ageMs = 0; freezeRemainingMs = 0; }
    bool frozen() const { return freezeRemainingMs > 0; }
    void freezeFor(double ms) { if (ms > 0) freezeRemainingMs = std::max(freezeRemainingMs, ms); }
    // A frozen clock stops advancing its own age but still burns the freeze, so
    // the body holds its pose while the effect layers keep running — the same
    // split 40JP gets from per-object clocks.
    void advance(double dtMs) {
        if (!(dtMs > 0)) return;
        if (freezeRemainingMs > 0) {
            const double burned = std::min(dtMs, freezeRemainingMs);
            freezeRemainingMs -= burned;
            dtMs -= burned;
        }
        if (dtMs > 0) ageMs += dtMs;
    }
};

enum class PreviewLayerKind { Particle, EffectBack, EffectFront, HitEffect };

struct PreviewLayer {
    PreviewLayerKind kind = PreviewLayerKind::EffectFront;
    std::string path;
    // 40JP draws sub-chain entries with a negative index behind the body and a
    // non-negative one in front (anim_parser.cpp:1748-1788).
    int order = 0;
    std::array<double, 3> offset{}; // actor-local X/Y/Z, X mirrored by facing
    bool loop = false;
    double birthMs = 0;   // local time inside the skill action when it appears
    double lifeMs = 0;    // 0 = the ANI's own duration
    PreviewClock clock;
    // Exact ALS uniqueName for add/remove pairing; empty for one-shot layers.
    std::string instance;
    std::string evidence;
    // Nothing before its birth, nothing after its own duration has run out. A
    // layer whose clock kept at zero because it had not been born yet used to
    // draw from the first frame, which made a 48-layer family look like one
    // white flash.
    bool visible(double actionMs) const {
        if (actionMs < birthMs) return false;
        return lifeMs <= 0 || actionMs - birthMs < lifeMs;
    }
};

struct FrameSpan {
    size_t index = 0;
    double startMs = 0, endMs = 0;
};

// A skill entity that outlives the cast. The animation comes from the PVF; the
// placement rule (orbit radius, ground anchor, air height) is reconstructed and
// the mapping row carries the matching evidence string.
enum class PreviewPersistentKind { Orbit, GroundField, AirSword };

struct PreviewPersistent {
    std::string path;
    PreviewPersistentKind kind = PreviewPersistentKind::GroundField;
    int count = 1;
    double radius = 0;           // orbit radius, source pixels
    double angularDegPerSec = 0; // orbit spin
    double phaseDeg = 0;         // first instance's angle
    std::array<double, 2> offset{};
    double birthMs = 0;
    std::string evidence;
    PreviewClock clock;
    // Looping entities stop with the action, so the clock is the only state.
    bool visible(double ageMs) const { return ageMs >= birthMs; }
};

// Frame windows of one ANI. 40JP's frame deadline is the running sum of each
// frame's [DELAY] at rate 100 (anim_parser.cpp:1707), which is what
// AniFrame::duration already holds.
std::vector<FrameSpan> frameSpans(const Animation &);
double animationDurationMs(const Animation &);
// Visits every frame window overlapping [fromMs,toMs). Attack windows are often
// one or two frames wide, so sampling only the endpoints would miss them both at
// high frame rates and after a stall.
void visitFrames(const Animation &, double fromMs, double toMs,
                 const std::function<void(const FrameSpan &)> &);
// The frame that owns this instant. 40JP resolves the pose from a running sum,
// not from a tick counter, so a seek can land on any millisecond.
size_t frameIndexAt(const Animation &, double ms);
std::optional<FrameSpan> spanAt(const Animation &, double ms);

// One stage of a chained release. The client's own motion list (see
// skill_preview_motion_pool.hpp) names a multi-stage skill as several ANIs —
// TripleSlash1..5, HundredSwordMoveSlash1..5 — and plays them back to back.
// Playing only the first one shows a fragment, not the skill.
struct PreviewBodyStage {
    std::string path;
    double startMs = 0;    // action-local time when this stage begins
    double durationMs = 0;
};

struct PreviewTimeline {
    double ageMs = 0;      // action-local elapsed time
    double durationMs = 0; // body duration, 0 when there is no body ANI
    std::string bodyPath;
    // Chained stages in release order. Empty for a single-stage action, in
    // which case bodyPath and durationMs describe the whole thing.
    std::vector<PreviewBodyStage> stages;
    PreviewClock body;
    std::vector<PreviewLayer> layers;
    // Entities that stay on the field for the whole action (orbs, lotus field,
    // hanging swords). They are not layers: their position depends on time.
    std::vector<PreviewPersistent> persistents;
    bool paused = false, ended = false;

    // The stage that owns this instant, or nullptr when there is no body.
    const PreviewBodyStage *stageAt(double ms) const {
        if (stages.empty()) return nullptr;
        for (const auto &stage : stages)
            if (ms >= stage.startMs && ms < stage.startMs + stage.durationMs) return &stage;
        return &stages.back(); // a seek past the end holds the last pose
    }
    // Time inside that stage.
    double stageLocalMs(double ms) const {
        const auto *stage = stageAt(ms);
        if (!stage) return ms;
        return std::max(0.0, std::min(ms - stage->startMs, stage->durationMs));
    }
    // 40JP has no notion of "the animation stopped"; the viewer replays so a
    // single click keeps demonstrating. The host clears per-pass state when
    // looped is raised.
    bool loop = true, looped = false;

    void reset();
    // Real elapsed milliseconds; speed is applied here so every clock shares it.
    void advance(double realMs, double speed);
    bool bodyVisible() const { return !bodyPath.empty(); }
};
} // namespace dnf
