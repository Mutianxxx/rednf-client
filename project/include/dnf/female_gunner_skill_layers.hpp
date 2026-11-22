#pragma once
#include "female_gunner.hpp"

namespace dnf {
enum class SourceSkillVisualTrigger { StageLayer, AcceptedHit };
enum class SourceSkillVisualScalePolicy { Fixed, HeldTargetWidth };

// Controller-created skill visuals are separate from authored ALS. The legacy
// alias remains for existing callers while source bindings use this shared
// contract across jobs.
struct SourceSkillVisualCue {
    SourceRef source;
    std::string bodyPath;
    int layer = 0; // negative: behind actor; nonnegative: in front of actor
    std::array<double,3> offset{}; // actor-local XYZ; X mirrors, Z projects upward
    bool synchronizedToBody = false;
    // Authored ALS attachment: own frame delays with the owner's live rate.
    // Default stays false for existing inferred controller-created layers.
    bool inheritBodyRate = false;
    bool loop = false; // authored ANI global0; never inferred from a preload
    SourceSkillVisualTrigger trigger = SourceSkillVisualTrigger::StageLayer;
    std::vector<int> controllerSubstates;
    int controllerStyle = -1;
    SourceSkillVisualScalePolicy scalePolicy = SourceSkillVisualScalePolicy::Fixed;
    double scaleX = 1, scaleY = 1;
    // Native command scripts schedule a stage's effects at fixed steps, so a
    // cue can be born after its stage entry. Zero keeps the historical
    // "publish with the stage" behaviour for every existing caller.
    int delayMs = 0;
    // Nonzero declares a native independent effect instance: it is born
    // delayMs into the owning stage and then runs its own clip to completion,
    // outliving a stage boundary instead of restarting with the next body
    // motion. Zero keeps the stage-bound layer the rest of the tree uses.
    int durationMs = 0;
    // Runtime presentation instance, excluded from immutable source snapshot.
    // Prepared by the action owner; renderer cannot advance or retire it.
    std::optional<ani_clock::Snapshot> instanceClock;
    Json evidence = Json::array();
    Json snapshot() const;
};
using FemaleGunnerSkillLayer = SourceSkillVisualCue;

bool sourceSkillVisualCueMatches(const SourceSkillVisualCue &, int controllerSubstate,
                                 int controllerStyle) noexcept;
double heldTargetWidthVisualScale(double sourceWidth) noexcept;
// Run while building an immutable character plan, never from a render frame.
// Only a selected skill plus its actual current CHR motion authorizes a layer.
// Exact matching frame delays permit borrowing body controller delays. Other
// clips keep their own authored delay sequence and loop flag.
std::vector<FemaleGunnerSkillLayer> buildFemaleGunnerSkillLayers(
    Pvf &, Assets &, const FemaleGunnerSkillDescriptor &, const std::string &bodyPath);
Json runFemaleGunnerSkillLayerTests(Pvf &, Assets &);
} // namespace dnf
