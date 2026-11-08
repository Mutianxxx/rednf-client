#pragma once
#include "resources.hpp"
namespace dnf {
// Immutable resource declarations compiled into bounded visual instances.
// Scheduling is a reconstruction; unknown/negative-frame rules stay diagnostic.
struct EffectTrack {
    std::string animation, source, instance;
    size_t sourceOffset = 0;
    int begin = 0, end = 0, layer = 0;
    bool primary = false;
};
struct EffectPlan {
    std::vector<EffectTrack> tracks;
    Json diagnostics = Json::array();
};
enum class EffectEventKind { Add, Remove, DrawOnly, DrawOnlyFollowParent };
// Direct ALS commands for one parent animation. No DELAY/time conversion or
// recursive child expansion occurs here. The host dispatches matching frame
// visits in sourceOrder, and owns visit deduplication and instance lifetimes.
struct EffectFrameEvent {
    EffectEventKind kind = EffectEventKind::Add;
    int frame = 0, layer = 0;
    size_t sourceOrder = 0, sourceOffset = 0, declarationOffset = 0;
    std::string animation, instance, source, sourceHash;
    int offsetX = 0, offsetY = 0, offsetZ = 0;
};
struct EffectEventPlan {
    std::string animation;
    size_t frameCount = 0;
    Script alsSource; // Exact raw bytes, ordered fields/tokens and source identity.
    std::vector<EffectFrameEvent> events;
    Json diagnostics = Json::array();
};
// instance is an exact, case-sensitive ALS uniqueName, not a normalized path.
// Unsupported commands/payloads/bindings remain in alsSource and diagnostics;
// Accepted direct add/remove and ordinary draw-only commands enter events.
// Special layer sentinels, random and follow-parent creation remain explicit
// diagnostics until their lifecycle/render contract is recovered.
EffectEventPlan animationEffectEvents(Pvf &pvf, Assets &assets, const std::string &animation, const std::string &sourceTreePolicy = {});
EffectPlan animationEffectPlan(Pvf &pvf, Assets &assets, const std::string &animation, const std::string &sourceTreePolicy = {});
EffectPlan objectEffectPlan(Pvf &pvf, Assets &assets, const std::string &object);
std::string effectResource(Pvf &pvf, const std::string &source, const std::string &child);
} // namespace dnf
