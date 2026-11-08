#pragma once
#include "collision.hpp"
#include "resources.hpp"
#include "skill_preview_mapping.hpp"
#include "skill_preview_timeline.hpp"
#include <array>
#include <string>
#include <vector>

namespace dnf {
class Assets;

// One attack volume the skill can produce, in action-local time.
//
// 40JP reads these straight out of the .ani frame table: +56..71 holds the
// [ATTACK BOX] vector of six floats (x y z w h d), the box is mirrored as
// x = -x - w when the actor faces left, then the actor's world position is
// added (hiteff_monster.cpp:4903-4915). Nothing here is inferred except the
// reconstructed volumes the mapping table already cites.
struct PreviewVolume {
    Box box;
    size_t frame = 0;
    double startMs = 0, endMs = 0;
    std::array<double, 3> offset{}; // actor-local X/Y/Z of the owning layer
    AttackBoxSource source = AttackBoxSource::AniBody;
    std::string owner; // empty for the body animation
    std::string evidence;
};

// A stationary target. Its hurt volume comes from the body animation's
// [DAMAGE BOX] (type 14) so the demo never invents a monster.
struct PreviewDummy {
    int index = 0;
    double x = 0, y = 0;
    CombatBox hurt;
    bool sourced = false;
};

struct PreviewHit {
    double ms = 0;
    size_t volume = 0;
    int dummy = 0;
    CombatBox overlap;
};

// Every attack volume of the skill: body frames, effect-layer frames (shifted by
// the layer's birth time), plus the mapping's cited reconstructed volumes.
std::vector<PreviewVolume> collectVolumes(Assets &, const SkillVisualMapping &,
                                          const Animation *body, double bodyDurationMs,
                                          const std::vector<PreviewLayer> &layers);

// World-space volume of one attack box for the given facing.
CombatBox worldVolume(const PreviewVolume &, double stageX, double stageY, int facing);

// Dummies stand in front of the actor. count is 0, 1 or 3 (H cycles it).
std::vector<PreviewDummy> buildDummies(const Animation *body, double stageX, double stageY,
                                       int facing, int count);

// True when the volume is live anywhere inside [fromMs,toMs).
bool volumeLiveIn(const PreviewVolume &, double fromMs, double toMs);

// Separating-axis test with the preview's 2D depth rule: the stage is drawn on
// one plane, so a box whose d is 0 is given the smallest depth instead of
// failing every test. Recorded as inference in docs/SKILL-DEMO-40JP-SPEC.md.
bool previewOverlap(const CombatBox &attack, const CombatBox &hurt, CombatBox *overlap = nullptr);
} // namespace dnf
