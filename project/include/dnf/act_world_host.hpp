#pragma once
#include "dnf/act_runtime.hpp"
#include "dnf/act_collision.hpp"
#include "dnf/audio_catalog.hpp"
#include "dnf/combat.hpp"
#include <memory>

namespace dnf {
// Production source resolver. PVF references retain PVF identity; IMG/audio
// leaves retain their own byte hash and the caller's static-content identity.
// No passive-object/PTL/ATK factory is claimed by this first World adapter.
class ActWorldResources final : public ActResourceResolver {
    Pvf &pvf_;
    Assets &assets_;
    std::string staticIdentity_;
    AudioCatalog audio_;
    SourceRef audioSource_;
    std::map<int, std::string> objects_;
    mutable std::map<std::string, ActResolvedResource> cache_;
    std::string path(const std::string &parent, const std::string &literal) const;
    SourceRef staticSource(const std::string &, const Bytes &) const;
    void sound(const std::string &, std::set<std::string> &, std::vector<ActDependency> &) const;
    void animation(const std::string &, std::set<std::string> &, std::vector<ActDependency> &, size_t) const;
  public:
    ActWorldResources(Pvf &, Assets &, std::string staticIdentity);
    const std::string &staticIdentity() const { return staticIdentity_; }
    ActResolvedResource resolve(const ActResourceRequest &) const override;
};

struct ActEntityRelations {
    EntityHandle target, lastAttacker, lastAttackSuccess, summonMaster;
    std::vector<EntityHandle> lastAttackSuccesses;
};
class ActWorldActorView final : public ActWorldView {
    const World &world_;
    const std::map<EntityHandle, ActEntityRelations> &relations_;
  public:
    ActWorldActorView(const World &, const std::map<EntityHandle, ActEntityRelations> &);
    std::optional<ActEntityView> entity(EntityHandle) const override;
    std::vector<EntityHandle> entities() const override;
};
struct ActSpeechBubble {
    uint64_t instanceId = 0, expiresMs = 0;
    EntityHandle speaker;
    std::string text, eventKey;
    Json json() const;
};
struct ActWorldHostResult {
    bool ok = false;
    std::string error;
    Json diagnostics = Json::array();
};
struct ActWorldHostOptions {
    // Set true only after the renderer actually consumes speechBubbles().
    // SPEECH is localized display text; it must never be sent to audio.play.
    bool enableSpeechPresentation = false;
    uint64_t speechDurationMs = 1200; // Explicit inferred presentation policy.
};
// Read-only view of an independently prepared outer graph. The actor records,
// registry, logical IDs and full status receipt must be supplied by the SAME
// CharacterStore root/generation. Candidate actor/status queries use this graph;
// the live World is read only for origin guards and allocation/revision floors.
// The caller retains these objects only through preparation; PreparedRestore
// owns all retained host data and serialized receipts afterwards.
struct ActWorldRestoreGraph {
    const Actor &player;
    const std::vector<Actor> &monsters;
    const EntityRegistry &entities;
    Json worldIds, statusReceipt;
    uint64_t tick = 0;
    int characterLevel = 1;
    Json combatRandom = Json();
    int64_t playerGuardUntil = 0;
};
struct ActWorldRestoreBudget {
    static constexpr size_t maximumSnapshotBytes = 33554432;
    static constexpr size_t maximumEventReceiptBytes = 16777216;
    static constexpr size_t maximumJsonDepth = 64;
};

// Requires `friend class ActWorldHost;` in World. This adapter is a single-writer
// simulation service. Every batch copies actor/entity/status/host state, validates it,
// applies real side effects on the copies, then publishes via no-throw swaps.
// Root must skip legacy AI/motion for ownsActor()/controlsMovement() and call
// advance once per World fixed tick. No renderer/wall clock advances this host.
class ActWorldHost {
    struct Velocity {
        uint64_t instanceId = 0;
        ActVec3 value;
    };
    struct Presentation {
        std::string animation, animationPath;
        int64_t animStart = 0;
        int poseFrame = -1;
    };
    struct State {
        uint64_t lastTick = 0, instanceWatermark = 0;
        std::map<uint64_t, ActInstanceState> instances;
        std::map<EntityHandle, Velocity> velocities;
        std::map<EntityHandle, ActEntityRelations> relations;
        std::map<uint64_t, Presentation> presentation;
        std::vector<ActSpeechBubble> speech;
        std::map<uint64_t,ActCollisionState> collisions;
        Json diagnostics = Json::array(), unknown = Json::object();
    };
    struct Batch;
    World &world_;
    Pvf &pvf_;
    Assets &assets_;
    ActWorldResources resources_;
    ActWorldHostOptions options_;
    State state_;
    // Process-local publication identity. Never serialized or restored; saved
    // logical IDs/revisions may repeat, this epoch cannot repeat.
    uint64_t publicationEpoch_ = 0;
    ActWorldRestoreGraph liveGraph(uint64_t generation) const;
    Json snapshotState(const State &, const ActWorldRestoreGraph &, uint64_t) const;
    State prepareState(const Json &, const ActWorldRestoreGraph &, uint64_t) const;
    void validateGraph(const ActWorldRestoreGraph &, uint64_t) const;
    static size_t eventReceiptBytes(const State &);
    void apply(Batch &, uint64_t, const ActPreparedStep &);
    void applyCommands(Batch &, uint64_t, const ActPreparedStep &, SourceRef *failureLocation);
    void cleanup(Batch &, uint64_t);
    void bindCollision(Batch &,uint64_t,const MonsterActionRoute *);
    void collide(Batch &,uint64_t,uint64_t,bool);
    void interruptNeutralPlayer(Batch &);
    Json collisionSnapshot(const State &) const;
    void restoreCollisions(State &,const Json &,const ActWorldRestoreGraph &) const;
    void commit(Batch &) noexcept;
    ActWorldHostResult failure(const std::exception &) const;
  public:
    class PreparedRestore {
        friend class ActWorldHost;
        std::unique_ptr<State> state_;
        const ActWorldHost *origin_ = nullptr;
        uint64_t expectedEpoch_ = 0, generation_ = 0;
        Json originReceipt_, candidateReceipt_;
      public:
        std::string error;
        Json diagnostics = Json::array();
        PreparedRestore() = default;
        PreparedRestore(PreparedRestore &&) noexcept = default;
        PreparedRestore &operator=(PreparedRestore &&) noexcept = default;
        PreparedRestore(const PreparedRestore &) = delete;
        PreparedRestore &operator=(const PreparedRestore &) = delete;
        bool ready() const { return bool(state_); }
        const Json &snapshot() const { return candidateReceipt_; }
    };
    ActWorldHost(World &, Pvf &, Assets &, std::string staticIdentity,
                 ActWorldHostOptions = {});
    bool hasCommandConsumer(const std::string &) const;
    ActCompileResult compile(const std::string &, ActSemanticPolicy = {}) const;
    ActWorldHostResult bind(std::shared_ptr<const ActProgram>, const ActBindRequest &,
                            ActEntityRelations = {}, bool replaceOwner = false,
                            const MonsterActionRoute *attackRoute = nullptr);
    ActWorldHostResult advance(const SimulationStep &,
        // Hit-stop or scaled controllers must select ExternalAnimationDelta
        // at bind and supply one already-scaled delta (including zero) per tick.
        const std::map<uint64_t, uint64_t> &externalAnimationDeltas = {});
    ActWorldHostResult dispatch(uint64_t instanceId, const ActEventContext &);
    ActWorldHostResult cancel(uint64_t instanceId, const std::string &reason);
    ActWorldHostResult cancelAll(const std::string &reason);
    // Explicit transient-restore policy only: running actions must have been
    // cancelled. Continued actions require the separate same-generation import.
    void resetCancelledClock();
    bool ownsActor(EntityHandle) const;
    bool controlsMovement(EntityHandle) const;
    const std::map<uint64_t, ActInstanceState> &instances() const { return state_.instances; }
    const std::vector<ActSpeechBubble> &speechBubbles() const { return state_.speech; }
    Json diagnostics() const { return state_.diagnostics; }
    const std::map<uint64_t,ActCollisionState> &collisions() const { return state_.collisions; }
    // The outer envelope must capture actors, registry, World clock and this
    // state in the SAME generation. Restore checks exact live actor/status
    // receipts, including hit-stop; it does not rewind the World/StatusHost,
    // change World handles or replace the legacy restore contract.
    Json snapshot(uint64_t commitGeneration) const;
    ActWorldHostResult restore(const Json &, uint64_t commitGeneration);
    // Preparation is pure, including recompilation, receipt verification and
    // typed remapping. Legacy host-v2/digest-only data cannot enter remapping.
    PreparedRestore prepareRestore(const Json &, uint64_t, const ActWorldRestoreGraph &) const;
    PreparedRestore prepareRemappedRestore(const Json &, uint64_t,
        const ActWorldRestoreGraph &saved, const ActWorldRestoreGraph &prepared,
        const std::map<EntityHandle, EntityHandle> &savedToNew) const;
    bool canPublish(const PreparedRestore &) const;
    // Standalone publication requires that World ALREADY exactly matches the
    // candidate graph. This call never restores actors/status/clock itself.
    ActWorldHostResult publish(PreparedRestore &&);
  private:
    friend class CharacterStore;
    friend Json runActWorldHostTests(Pvf &, Assets &);
    friend Json runActCollisionTests(Pvf &, Assets &);
    friend Json runWaterCannonRuntimeTests(Pvf &,Assets &);
    // Outer same-generation coordinator only: check canPublish BEFORE its first
    // mutation, then publish World/status/scene/progression and this host with
    // verified no-throw swaps in one single-writer section. Do not call public
    // publish() after World mutation: that API checks the pre-restore guard.
    void publishAfterOuterCommit(PreparedRestore &&) noexcept;
};
Json runActWorldHostTests(Pvf &, Assets &);
} // namespace dnf
