#pragma once
#include "character.hpp"
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <set>

namespace dnf {

// Executable availability, automated validation and native fidelity are separate.
// Complete, explained reconstructions may execute as beta implementations;
// NativeChainClosed retains the stricter confirmed evidence contract. Only the
// already shipped Swordman may use ExistingPartialCandidate.
enum class ControllerReadiness {
    Unavailable, ExistingPartialCandidate, NativeChainClosed, DeferredByUser, ReconstructedBeta,
    ExperimentalUserTest, UserAdvancementPartial
};
enum class CharacterAction { Move, Jump, BasicAttack, DashAttack, JumpAttack, CommandInput, Skill };
enum class ControllerCancelReason { Death, RoomChange, CharacterChange, Reload, ExplicitReset };

struct CharacterActionRequest {
    CharacterAction action = CharacterAction::BasicAttack;
    std::optional<SkillKey> skill;
    int inputKey = -1;
    bool inputDown = false;
    int horizontal = 0, vertical = 0;
    bool continuation = false;
    int64_t simulationMs = 0;
};
struct NativeEvidenceRef {
    std::string classification = "unknown";
    std::string report, anchor, finding;
    // Required for inferred runtime evidence; explicitly state "none" if no
    // further conditions remain. Source facts must not be relabelled confirmed.
    std::string basis, unverifiedConditions, impact;
    bool confirmed() const;
    bool explainedForRuntime() const;
    Json snapshot() const;
};
// The historical Native prefix describes the shared evidence record, not a
// claim that every link has been recovered from the original executable.
struct NativeControllerChain {
    NativeEvidenceRef releaseQualification, inputRequest, stateCommit, actionAndAttack;
    NativeEvidenceRef contactAndEffects, continuation, exitCleanup;
    bool nativeConfirmed() const;
    bool runtimeComplete() const;
};
enum class ControllerCheckStatus { Pending, Passed, Failed };
struct ControllerCheckEvidence {
    ControllerCheckStatus status = ControllerCheckStatus::Pending;
    std::string report, anchor, finding;
    bool passed() const;
    Json snapshot() const;
};
struct CharacterControllerInfo {
    CharacterIdentity identity;
    std::string name, implementation, limitation;
    ControllerReadiness readiness = ControllerReadiness::Unavailable;
    std::string exeSha256, pvfSha256;
    std::map<CharacterAction, NativeControllerChain> actionEvidence;
    std::map<SkillKey, NativeControllerChain> skillEvidence;
    std::set<SkillKey> requiredRuntimeSkills;
    ControllerCheckEvidence automatedRuntimeEvidence;
    // User checks remain independent of reconstructed beta admission. Their
    // confirmed evidence is required only by NativeChainClosed.
    NativeEvidenceRef normalInputEvidence, originalClientComparisonEvidence;
    bool runtimeComplete() const;
    bool nativeConfirmed() const;
    bool executable() const;
    Json snapshot() const;
};

// Host callbacks adapt the existing World without granting shared Swordman
// behavior to a different job. Future factories can ignore these callbacks and
// own their distinct class state. No SDL, render clock, or fixed controller count.
struct CharacterControllerServices {
    std::function<bool(const CharacterActionRequest &)> request;
    std::function<void(int64_t)> tick;
    std::function<void(ControllerCancelReason)> cancel;
};
class CharacterController {
  public:
    virtual ~CharacterController() = default;
    virtual CharacterIdentity identity() const = 0;
    virtual bool request(const CharacterActionRequest &request) = 0;
    virtual void tick(int64_t simulationMs) = 0;
    virtual void cancel(ControllerCancelReason reason) = 0;
};
using CharacterControllerFactory = std::function<std::unique_ptr<CharacterController>(CharacterControllerServices)>;

class CharacterControllerRegistry {
    struct Entry { CharacterControllerInfo info; CharacterControllerFactory factory; };
    std::map<CharacterIdentity, Entry> entries_;
    // Source-declared user deferrals cover the whole job, including branches.
    // Replacing an unavailable record cannot accidentally revoke a deferral.
    std::set<int> deferredJobs_;
  public:
    // Builds disabled source entries for every registered base character and
    // an explicit compatibility factory for the current partial Swordman.
    static CharacterControllerRegistry currentCandidate(const CharacterCatalog &catalog);
    void registerController(CharacterControllerInfo info, CharacterControllerFactory factory = {});
    const CharacterControllerInfo *find(CharacterIdentity identity) const;
    bool supports(CharacterIdentity identity) const;
    std::unique_ptr<CharacterController> create(CharacterIdentity identity, CharacterControllerServices services) const;
    Json snapshot() const;
};

// Exact CHR source order, slots, repetitions and empty values are retained.
// This does not infer EQU/LAY membership, layer sort order, collision union or
// clock sharing from a similar filename. Each actual body/weapon/effect clock
// stays in the class controller or the existing animation instance system.
struct OrderedCharacterBinding {
    size_t sourceOrdinal = 0, occurrence = 0;
    CharacterResource resource;
};
std::vector<OrderedCharacterBinding> orderedCharacterBindings(const CharacterDefinition &definition);

enum class EquipmentJobGate { Allowed, Excluded, Unresolved };
struct EquipmentJobRestriction {
    EquipmentJobGate gate = EquipmentJobGate::Unresolved;
    std::string sourceJob;
    std::vector<Field> fields;
};
// Evaluates only the explicit EQU usable-job restriction against the actual
// CHR job tag. Level, equipment slot, advancement, weapon renderer and other
// requirements remain independent. Missing/repeated/malformed fields fail shut.
EquipmentJobRestriction equipmentJobRestriction(const CharacterDefinition &character, const Script &equipment);
bool equipmentAllowsJob(const CharacterDefinition &character, const Script &equipment);

enum class SkillGate {
    Accepted, WrongCharacter, MissingImplementation, UnknownKind, PassiveHasNoConsumer,
    SourceLearningUnresolved, SourceLearningExcluded, LearningNotQualified, InvalidLevel, NotLearned, PassiveCannotActivate,
    Dead, StateBlocked, Cooldown, InsufficientMp
};
std::string skillGateName(SkillGate gate);
struct RuntimeSkillPolicy {
    SkillKey key;
    SkillSourceKind kind = SkillSourceKind::Unknown;
    bool implemented = false, passiveConsumerBound = false;
    int maximumLevel = 0;
};
struct SkillLearningAuthorization {
    CharacterIdentity identity;
    SourceLearningState source = SourceLearningState::Unresolved;
    // The caller must close character level, branch, prerequisite and cost
    // checks. A parsed SKL learning candidate alone never grants learning.
    bool qualificationPassed = false;
};
struct SkillUseContext {
    CharacterIdentity identity;
    int64_t nowMs = 0;
    bool alive = true, stateAllowsUse = true, ignoreCooldown = false, ignoreMpGate = false;
    int mpCost = 0, cooldownMs = 0;
    // Some class controllers start CD on exit or a later event. This flag is
    // provided by that controller, never guessed from SKL [cool time].
    bool startCooldown = true;
};
struct LearnedSkillState {
    int level = 0;
    int64_t cooldownUntilMs = 0;
    Json preserved = Json::object();
};

// Per-character normal learned/cost ledger, indexed by (job, skill).
// Swordman uses this ledger's generic MP/CD transaction methods. Experimental
// actual release keeps its existing runtime MP/CD authority and persists that
// relative clock separately in the same character generation; the learning
// bridge must never call commitUse/startCooldown for that runtime a second time.
// Source loading and passive attribute consumers remain outside this ledger.
class CharacterSkillState {
    CharacterIdentity identity_;
    std::map<SkillKey, LearnedSkillState> states_;
    Json preserved_ = Json::object();
    SkillGate policyGate(const RuntimeSkillPolicy &policy) const;
  public:
    explicit CharacterSkillState(CharacterIdentity identity = {});
    CharacterIdentity identity() const { return identity_; }
    int learnedLevel(SkillKey key) const;
    // Value comparison without serializing or allocating during publication.
    bool sameRuntimeState(const CharacterSkillState &) const;
    // Explicit restoration/import boundary, not the player learning service.
    // Retains level zero and unknown keys; it does not authorize execution.
    void setLearnedLevel(SkillKey key, int level);
    SkillGate checkLearning(const RuntimeSkillPolicy &policy, int targetLevel,
                            const SkillLearningAuthorization &authorization) const;
    SkillGate learn(const RuntimeSkillPolicy &policy, int targetLevel,
                    const SkillLearningAuthorization &authorization);
    int64_t remainingCooldown(SkillKey key, int64_t nowMs) const;
    void startCooldown(SkillKey key, int64_t nowMs, int64_t durationMs);
    void clearCooldowns();
    SkillGate checkUse(const RuntimeSkillPolicy &policy, const SkillUseContext &context, int availableMp) const;
    // Rechecks current level, identity, state, MP and CD immediately before
    // mutation. A request accepted earlier is never a reusable spend ticket.
    SkillGate commitUse(const RuntimeSkillPolicy &policy, const SkillUseContext &context, int &availableMp);
    // Relative simulation times; restore is atomic and rejects ambiguous
    // duplicate keys. Unknown root/per-skill fields survive a round trip.
    Json snapshot(int64_t nowMs) const;
    void restore(const Json &value, int64_t nowMs);
};

} // namespace dnf
