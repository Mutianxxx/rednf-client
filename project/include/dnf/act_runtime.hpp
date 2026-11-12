#pragma once
#include "dnf/content_profile.hpp"
#include "dnf/simulation.hpp"
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <variant>

namespace dnf {
// Staged P06 implementation. World must atomically consume prepared commands
// before publishActStep. This module does not mutate HP, spawn entities or play
// audio. Emitting a command is not proof that its World consumer is implemented.
enum class ActResourceKind { Animation, Particle, PassiveObject, Sound, AttackInfo,
                             Action, Monster };
const char *actResourceKindName(ActResourceKind);
struct ActDiagnostic {
    std::string code, message;
    SourceRef source;
    bool blocking = true;
    Json json() const;
};
struct ActResourceRequest {
    ActResourceKind kind = ActResourceKind::Animation;
    SourceRef origin;
    std::string literal;
    int index = -1;
};
struct ActDependency {
    ActResourceRequest request;
    SourceRef resolved;
    bool found = false, runtimeSupported = false;
    std::string diagnostic;
    Json json() const;
};
struct ActResolvedResource {
    bool found = false, runtimeSupported = false;
    SourceRef source;
    std::string diagnostic;
    std::vector<int64_t> frameDurationsMs;
    bool animationLoops = false;
    // A composite resource resolver must enumerate the transitive ACT/ANI/ALS/
    // ATK/PTL/audio/etc. requirements. All kinds except a resolved Sound leaf
    // require this flag. Empty closure is meaningful only when explicitly known.
    bool transitiveClosureKnown = false;
    std::vector<ActDependency> transitive;
};
class ActResourceResolver {
  public:
    virtual ~ActResourceResolver() = default;
    virtual ActResolvedResource resolve(const ActResourceRequest &) const = 0;
};

enum class ActFrameEvaluation { OncePerRangeVisit, EverySimulationStep };
enum class ActClockMode { SourceMilliseconds, ExternalAnimationDelta };
struct ActSemanticPolicy {
    // Defaults, frame checks, ordering and scheduling are explicit inference,
    // not recovered EXE semantics. Persist this ID and the complete policy.
    std::string id = "inferred-act-host-v1";
    uint64_t defaultLimit = 1; // Explicit source LIMIT 0 remains unlimited.
    bool defaultEnabled = true;
    uint64_t defaultCheckTimeMs = 0;
    ActFrameEvaluation frameEvaluation = ActFrameEvaluation::OncePerRangeVisit;
    // Normal/PROC calls run in declaration order in the current prepared batch;
    // DIRECT calls are separately typed, with the same current-batch policy.
    uint64_t maximumInstructions = 4096, maximumCommands = 1024;
    uint64_t maximumPending = 1024, maximumRememberedEvents = 4096;
    uint64_t maximumFrameBoundaries = 4096;
    Json json() const;
};
enum class ActSelectorKind {
    Me, Target, LastAttacker, LastAttackSuccess, LastAttackSuccesses,
    SummonMaster, Character, Monster, Passive, AllOurTeam, AllEnemy,
    CreatedObject, DestroyedObject, SavedTarget
};
struct ActSelector {
    ActSelectorKind kind = ActSelectorKind::Me;
    uint32_t savedSlot = 0;
};
enum class ActTargetOrder { StableIdentity, Random, DistanceLow, DistanceHigh,
                            HpLow, HpHigh, MpLow, MpHigh, LevelLow, LevelHigh };
struct ActTargetQuery {
    ActSelector which;
    size_t count = 0; // Zero means keep the full set.
    ActTargetOrder order = ActTargetOrder::StableIdentity;
};
enum class ActEventKind { SetAction, RemoveAction, Damage, AttackSuccess,
                          CreateObject, DestroyObject, DestroyMe, MoveCollision };
enum class ActCallKind { Normal, Direct, Proc, Delayed };
enum class ActRecipientKind { Me, CheckupObject, DropoutObject, Target,
                              LastAttacker, LastAttackSuccess, SummonMaster,
                              LastAttackSuccesses, SavedTarget };
struct ActBehaviorCall {
    ActCallKind kind = ActCallKind::Normal;
    ActRecipientKind recipient = ActRecipientKind::Me;
    uint32_t savedSlot = 0;
    size_t behavior = 0;
    uint64_t delayMs = 0;
    SourceRef source;
};
struct ActFrameRange { size_t first = 0, last = 0; };
struct ActProbability { uint32_t numerator = 1, denominator = 1; };
struct ActTrigger {
    SourceRef source;
    uint64_t limit = 1, checkTimeMs = 0;
    bool enabled = true;
    std::optional<ActFrameRange> frames;
    std::optional<ActEventKind> event;
    std::optional<bool> stuck;
    ActProbability probability;
    ActTargetQuery query;
    std::vector<ActBehaviorCall> calls;
};

struct ActVec3 { double x = 0, y = 0, z = 0; };
enum class ActDirectionBasis { Target, Owner, Ignore };
struct ActSetSpeed {
    std::optional<double> x, y, z;
    ActDirectionBasis direction = ActDirectionBasis::Target;
};
struct ActCoordinates {
    ActVec3 value;
    bool useOwnerBase = false, useMapPosition = false, useOwnerDirection = false;
};
struct ActSpawn {
    int objectIndex = -1, level = 0;
    std::string particle;
    ActCoordinates position;
    bool followingTarget = false, movablePositionOnly = false, noEffect = false;
    // 1031 PVF [WARNING MARK] carries 2 or 4 integer operands. The operands are
    // retained as source facts; the visual warning decal has no World consumer
    // yet, so the compiler emits an explicit non-blocking diagnostic.
    std::vector<int64_t> warningMark;
};
struct ActParticle { std::string path; ActVec3 offset; };
struct ActTeleport { ActCoordinates position; bool moveOwner = false; };
enum class ActDirectionKind { Left, Right, ToTarget, Random, Reverse,
                              Owner, OppositeOwner, CurrentOwner };
struct ActSetDirection { ActDirectionKind value = ActDirectionKind::ToTarget; };
struct ActDestroy { bool force = false; };
struct ActSound { std::string tag; };
struct ActSpeech { std::string text; };
enum class ActAttackRectMode { Reset, On, Off };
struct ActAttackRect { ActAttackRectMode mode = ActAttackRectMode::Reset; };
struct ActChangeAttackInfo { std::string path; bool useDefault = false; };
enum class ActTriggerMode { On, Off, Reset };
struct ActTriggerControl { size_t trigger = 0; ActTriggerMode mode = ActTriggerMode::On; };
struct ActDeferredCall { ActBehaviorCall call; bool targetProgram = true; };
struct ActCleanup { std::string reason; };
struct ActSetDamageCheck { bool enabled=false; uint64_t intervalMs=0; };
using ActCommandPayload = std::variant<ActSetSpeed, ActSpawn, ActParticle,
    ActTeleport, ActSetDirection, ActDestroy, ActSound, ActSpeech,
    ActAttackRect, ActChangeAttackInfo, ActTriggerControl, ActDeferredCall, ActCleanup, ActSetDamageCheck>;
struct ActInstruction { SourceRef source; ActCommandPayload payload; };
struct ActBehavior { SourceRef source; std::vector<ActInstruction> instructions; };
struct ActMotionTrack { SourceRef source; std::string path; size_t frame = 0;
                        int layer = 0; double x = 0, y = 0; };
struct ActMotionEvent { SourceRef source; size_t frame = 0;
                        ActProbability probability; ActCommandPayload payload; };
struct ActMotion {
    SourceRef source;
    std::string base;
    std::vector<int64_t> frameDurationsMs;
    bool loop = false;
    std::vector<ActMotionTrack> tracks;
    std::vector<ActMotionEvent> events;
};
struct ActProgram {
    SourceRef source;
    Script original; // Original raw bytes, ordered tokens, fields and unknowns.
    ActSemanticPolicy policy;
    std::optional<ActMotion> motion;
    std::string defaultAttackInfo;
    std::vector<ActTrigger> triggers;
    std::vector<ActBehavior> behaviors;
    std::vector<ActDependency> dependencies;
    std::vector<ActDiagnostic> diagnostics;
    bool syntaxComplete = false, sourceReady = false, runtimeReady = false;
    bool executable() const { return syntaxComplete && sourceReady && runtimeReady; }
};
struct ActCompileContext {
    std::string packageIdentity;
    ActSemanticPolicy policy;
    const ActResourceResolver *resources = nullptr;
    // Required for every emitted command kind (e.g. set_speed, sound, particle,
    // spawn_passive_object, cleanup_owned). Missing consumer blocks runtimeReady.
    std::function<bool(const std::string &)> hasCommandConsumer;
};
struct ActCompileResult {
    std::shared_ptr<const ActProgram> program;
    bool ok = false;
    Json json() const;
};
ActCompileResult compileActProgram(const Script &, const ActCompileContext &);

enum class ActEntityKind { Character, Monster, Passive };
struct ActEntityView {
    EntityHandle handle, target, lastAttacker, lastAttackSuccess, summonMaster;
    std::vector<EntityHandle> lastAttackSuccesses;
    ActEntityKind kind = ActEntityKind::Monster;
    ActVec3 position;
    int team = 0, direction = 1, hp = 0, mp = 0, level = 1;
    bool alive = true;
};
class ActWorldView {
  public:
    virtual ~ActWorldView() = default;
    virtual std::optional<ActEntityView> entity(EntityHandle) const = 0;
    virtual std::vector<EntityHandle> entities() const = 0;
};
struct ActEventContext {
    uint64_t eventId = 0;
    ActEventKind kind = ActEventKind::SetAction;
    EntityHandle subject, other;
    bool stuck = false;
    // Destroy notifications may retain the last valid subject snapshot. Queries
    // never treat it as a live handle; consumers must still validate generation.
    std::optional<ActEntityView> subjectSnapshot;
    Json metadata = Json::object();
};
// These are portable safety limits for receipt codec v1, not native content
// constants. Keep the old fingerprint recipe byte-for-byte: IDs and receipt
// version/unknown fields are outside the hashed payload.
struct ActEventReceiptBudget {
    static constexpr size_t maximumReceiptBytes = 65536;
    static constexpr size_t maximumInstanceBytes = 4194304;
    static constexpr size_t maximumJsonDepth = 32;
    static constexpr size_t maximumSnapshotSuccesses = 1024;
};
struct ActAcceptedEventReceipt {
    ActEventContext event;
    Json unknown = Json::object();
};
Json actEventIdentityJson(const ActEventContext &);
std::string actEventFingerprint(const ActEventContext &);
Json snapshotActEventReceipt(const ActAcceptedEventReceipt &);
// Strict, bounded decode. Unknown receipt-root fields survive; unknown typed
// payload fields and newer codecs reject. Metadata stays opaque and exact.
ActAcceptedEventReceipt restoreActEventReceipt(const Json &);
// Shared typed-reference rules for the core and World host continuation. The
// complete mapping and prepared roster are validated before any field changes.
// This helper never registers aliases and never scans arbitrary JSON by shape.
class ActEntityHandleRemapper {
    const EntityRegistry &saved_, &prepared_;
    const std::map<EntityHandle, EntityHandle> &mapping_;
    const ActWorldView &view_;
    uint64_t savedNext_ = 0;
  public:
    ActEntityHandleRemapper(const EntityRegistry &, const std::map<EntityHandle, EntityHandle> &,
                           const EntityRegistry &, const ActWorldView &);
    EntityHandle handle(EntityHandle, bool requiredLive = false) const;
    void entity(ActEntityView &) const;
    void event(ActEventContext &) const;
};
struct ActEmittedCommand {
    uint64_t instanceId = 0, actionId = 0, sequence = 0;
    EntityHandle owner, recipient;
    SourceRef source;
    ActCommandPayload payload;
    // Capture the coordinate bases at scheduling time. The World consumer uses
    // payload flags and rechecks handle validity before committing any mutation.
    std::optional<ActEntityView> ownerSnapshot, recipientSnapshot;
    std::string stableKey() const;
    Json json() const;
};
struct ActTriggerState {
    bool enabled = true;
    uint64_t fires = 0, nextCheckMs = 0;
    std::optional<uint64_t> lastRangeVisit;
};
struct ActPendingCall {
    uint64_t sequence = 0, dueMs = 0;
    uint64_t expectedActionId = 0;
    ActBehaviorCall call;
    std::vector<EntityHandle> recipients;
};
enum class ActInstanceStatus { Running, Cancelled, Faulted };
struct ActInstanceState {
    std::shared_ptr<const ActProgram> program;
    uint64_t instanceId = 0, actionId = 0, revision = 0;
    EntityHandle owner;
    ActClockMode clockMode = ActClockMode::SourceMilliseconds;
    ActInstanceStatus status = ActInstanceStatus::Running;
    uint64_t lastTick = 0, lastSimulationMs = 0, elapsedMs = 0, animationUs = 0;
    bool firstAdvance = true;
    MonotonicIds commandIds{1}, pendingIds{1};
    Pcg32 random{0, 1};
    std::vector<ActTriggerState> triggers;
    std::vector<ActPendingCall> pending;
    std::map<uint32_t, EntityHandle> savedTargets;
    std::map<uint64_t, std::string> rememberedEvents;
    std::map<uint64_t, ActAcceptedEventReceipt> acceptedEventReceipts;
    size_t acceptedEventReceiptBytes = 0;
    // Schema-1 imports retain their digest ledger for diagnosis/same-handle
    // compatibility. They can never claim complete remappable provenance.
    bool eventReceiptsComplete = true;
    Json variables = Json::object(), unknown = Json::object();
};
struct ActBindRequest {
    uint64_t instanceId = 0, actionId = 0;
    EntityHandle owner;
    uint64_t tick = 0, simulationMs = 0, randomSeed = 0, randomSequence = 1;
    ActClockMode clockMode = ActClockMode::SourceMilliseconds;
};
struct ActBindResult {
    bool ok = false;
    std::string error;
    ActInstanceState state;
    Json diagnostics = Json::array();
};
ActBindResult bindActProgram(std::shared_ptr<const ActProgram>, const ActBindRequest &,
                            const ActWorldView &);
struct ActAdvanceInput {
    SimulationStep step;
    // Required only in ExternalAnimationDelta mode; forbidden in source mode.
    // The caller supplies a single already-scaled delta, never a second rate.
    std::optional<uint64_t> animationDeltaUs;
};
struct ActPreparedStep {
    bool ok = false, faulted = false, replayed = false;
    uint64_t expectedRevision = 0, expectedInstanceId = 0;
    std::string error;
    std::optional<SourceRef> failureSource;
    ActInstanceState candidate;
    std::vector<ActEmittedCommand> commands;
    std::vector<ActDiagnostic> diagnostics;
};
ActPreparedStep prepareActAdvance(const ActInstanceState &, const ActAdvanceInput &,
                                 const ActWorldView &);
ActPreparedStep prepareActEvent(const ActInstanceState &, const ActEventContext &,
                               const ActWorldView &);
ActPreparedStep prepareActCancel(const ActInstanceState &, const std::string &reason);
// Publish only AFTER the World has successfully committed the complete command
// batch (or the explicit fault cleanup batch). A rejected step cannot publish.
bool publishActStep(ActInstanceState &, const ActPreparedStep &);
Json snapshotActInstance(const ActInstanceState &, uint64_t commitGeneration);
ActBindResult restoreActInstance(std::shared_ptr<const ActProgram>, const Json &,
                                const ActWorldView &, uint64_t expectedCommitGeneration);
// Pure import helper; it does not mutate World, registries or the saved JSON.
// The caller privately prepares the COMPLETE live entity mapping and fresh
// registry first, including merging its live allocation watermark. This helper
// verifies original hashes before remapping known typed references and hashing
// them again. It never installs old-handle aliases or interprets opaque JSON.
ActBindResult restoreRemappedActInstance(std::shared_ptr<const ActProgram>, const Json &,
    const EntityRegistry &savedRegistry, const std::map<EntityHandle, EntityHandle> &savedToNew,
    const EntityRegistry &preparedRegistry, const ActWorldView &preparedWorld,
    uint64_t expectedCommitGeneration);
Json runActRuntimeTests(Pvf &, Assets &);
} // namespace dnf
