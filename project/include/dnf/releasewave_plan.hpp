#pragma once
#include "content_profile.hpp"
#include "simulation.hpp"
#include "skill_data.hpp"
#include <array>

namespace dnf {
// A bounded 1031 adapter, not a complete class controller. Script sources keep
// raw bytes, ordered tokens/fields and provenance. ANI sources keep raw bytes
// and ordered byte spans; decoded frames are immutable and never gain an image.
struct ReleaseWaveResource {
    SourceRef source;
    Bytes raw;
    Script script;
    std::shared_ptr<const Animation> animation;
    Json byteSpans = Json::array();
    Json snapshot(bool includeRaw = false) const;
};
struct ReleaseWaveSourceContract {
    std::string packageIdentity;
    SkillKey skill{0,32};
    SkillSourceData skillData;
    ReleaseWaveResource characterSource, objectRegistry, objectSource, attackInfo;
    CharacterRegistration objectRegistration;
    std::array<ReleaseWaveResource,2> phaseMotions, visuals;
    ReleaseWaveResource attackAnimation;
    std::array<SourceRef,2> phaseBindings;
    SourceRef objectMotionBinding, objectAttackBinding;
    int floatingHeight = 0; // Authored OBJ metadata, not an actor Z increment.
    Json diagnostics = Json::array();
    std::vector<Box> attackBoxesAt(size_t frame) const;
    Json snapshot(bool includeRaw = false) const;
};
// Throws on missing/ambiguous/unsupported bindings before World commits costs.
// Reads only; all paths come from the registry/CHR/OBJ except two explicitly
// registered controller visual literals from the versioned 60US evidence.
ReleaseWaveSourceContract readReleaseWaveSourceContract(Pvf &, const CharacterCatalog &,
                                                       const std::string &mode = "dungeon");
struct ReleaseWaveQualification {
    bool ok = false;
    std::string reason;
    Json trace = Json::array();
    Json json() const;
};
// Source qualification only. The host supplies its normal ledger (or isolated
// overlay) and must still check controller readiness, MP/CD and action gates.
ReleaseWaveQualification evaluateReleaseWaveQualification(const ReleaseWaveSourceContract &,
    CharacterIdentity, int learnedLevel, int characterLevel);

enum class ReleaseWaveOwnerPolicy { InferredLiveLocalOwnerV1 };
enum class ReleaseWaveScalarPolicy { InferredUnmodifiedSourceColumn0V1 };
enum class ReleaseWaveDurationPolicy {
    InferredZeroThenSourceStaticV1, InferredSourceMotionDurationsV1
};
struct ReleaseWavePolicies {
    ReleaseWaveOwnerPolicy owner = ReleaseWaveOwnerPolicy::InferredLiveLocalOwnerV1;
    ReleaseWaveScalarPolicy scalar = ReleaseWaveScalarPolicy::InferredUnmodifiedSourceColumn0V1;
    ReleaseWaveDurationPolicy duration = ReleaseWaveDurationPolicy::InferredZeroThenSourceStaticV1;
    Json json() const;
};
struct ReleaseWaveActivationRequest {
    int phase = 0;
    CharacterIdentity identity;
    int learnedLevel = 0, characterLevel = 1;
    EntityHandle owner, localOwner;
    bool ownerLive = false;
    uint64_t actionId = 0, attackId = 0;
    std::array<float,3> position{0,0,0};
    int direction = 1;
};
enum class ReleaseWaveSpawnKind { Visual, AttackEntity };
struct ReleaseWaveSpawn {
    ReleaseWaveSpawnKind kind = ReleaseWaveSpawnKind::Visual;
    SourceRef source, attackInfoSource;
    std::shared_ptr<const Animation> animation;
    EntityHandle owner;
    uint64_t actionId = 0, attackId = 0;
    std::array<float,3> position{0,0,0};
    int direction = 1, signedAttachmentArgument = 0, objectId = -1;
    float speed = 0, scalar = 0;
    // Visuals follow actor position but own a clock. Attack remains at spawn
    // XYZ; the host removes it at its own ANI end, independently of cast phase.
    bool followsOwnerPosition = false, removeOnAnimationEnd = true;
    Json json() const;
};
struct ReleaseWaveActivationPlan {
    bool ok = false, ownerGatePassed = false;
    std::string reason;
    int phase = 0;
    std::array<int,2> phaseDurationMs{0,0};
    // Ordered phase0 operations: visual1(+1), visual2(-1), conditional attack.
    // Phase1 has no spawns. The host deduplicates phase application by action.
    std::vector<ReleaseWaveSpawn> spawns;
    Json trace = Json::array(), diagnostics = Json::array();
    Json json() const;
};
// Pure value plan: no ID allocation, live-owner lookup, costs, effects append,
// RNG, collision/damage, persistence, or render calls. Invalid source/runtime
// inputs reject the whole plan; a valid-but-failed owner gate keeps two visuals.
ReleaseWaveActivationPlan planReleaseWavePhaseEvent(const ReleaseWaveSourceContract &,
    const ReleaseWaveActivationRequest &, const ReleaseWavePolicies & = {});
} // namespace dnf
