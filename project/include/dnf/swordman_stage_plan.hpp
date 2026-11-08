#pragma once
#include "content_profile.hpp"
#include "skill_data.hpp"
#include <optional>

namespace dnf {
// Explicit source-plan selection; FiveSlash does not grant its admission gate.
enum class SwordmanStageVariant { OrdinaryGhostSlash, TripleSlash, FiveSlash };

struct SwordmanBoundResource {
    std::string path, chrTag;
    size_t chrSlot = 0;
    SourceRef source, declaration;
    Bytes rawBytes;
    // ATK retains its original ordered script. ANI retains an ordered binary
    // token stream with byte spans, including repeated/unknown decoded nodes.
    Script script;
    Json binaryTokens = Json::array();
    std::shared_ptr<const Animation> animation;
    Json snapshot(bool includeRaw = false) const;
};
struct SwordmanStageVisual {
    SwordmanBoundResource resource;
    int attachKey = 0, offsetX = 0, offsetY = 0, offsetZ = 0;
    bool mirrorOffsetX = true, followActor = true;
    bool independentClock = true, inheritActorRate = true;
    // Replacement of both IMAGE RATE components, never a multiplier or box
    // scale. Raw ANI and the decoded source animation remain unchanged.
    std::optional<float> imageRateOverride;
    std::optional<SourceRef> imageRateSource;
    Json snapshot(bool includeRaw = false) const;
};
struct SwordmanSkillStage {
    size_t index = 0;
    SwordmanBoundResource body, attack;
    // Null for the final segment. Gate is a source animation frame index.
    std::optional<size_t> nextInputFrame;
    int percentColumn = 0, fixedColumn = 1;
    // The native getter returns zero for an absent fixed column. This named
    // cross-version policy is separate from a valid, authored numeric zero.
    bool fixedColumnZeroWhenAbsent = true;
    std::vector<SwordmanStageVisual> visuals; // ascending attachKey draw order
    std::vector<std::string> sounds;
    Json snapshot(bool includeRaw = false) const;
};
struct SwordmanStagePlan {
    SkillKey key;
    SwordmanStageVariant variant = SwordmanStageVariant::OrdinaryGhostSlash;
    std::string mode = "dungeon", classification = "cross-version-inference-60us-to-current-pvf";
    CharacterScript characterSource;
    SkillSourceData skillSource;
    std::vector<SwordmanSkillStage> stages;
    // Skill8 static[0]/static[1] are movement setter inputs, not duration or
    // a proved displacement equation. World owns integration and collisions.
    std::optional<double> movementSpeed, movementAcceleration;
    Json diagnostics = Json::array(), evidence = Json::object();
    bool usable() const;
    Json snapshot(bool includeRaw = false) const;
};

// Pure preparation: no World, MP/CD, qualifications, mastery, clocks, actors,
// transaction or save mutation. OrdinaryGhostSlash requires the caller to
// enforce the uncharged branch. FiveSlash requires caller-proved admission.
SwordmanStagePlan loadSwordmanStagePlan(Pvf &, Assets &, const CharacterCatalog &,
    SwordmanStageVariant, const std::string &mode = "dungeon");
// Valid requests: job0/skill5/1, job0/skill8/3 and job0/skill8/5. Invalid
// requests return an unusable plan with diagnostics rather than a fallback.
SwordmanStagePlan loadSwordmanStagePlan(Pvf &, Assets &, const CharacterCatalog &,
    SkillKey, int segments, const std::string &mode = "dungeon");
} // namespace dnf
