#pragma once
#include "character_controller.hpp"
#include "dnf/basic_attack_movement.hpp"
#include "content_profile.hpp"
#include "damage_resolution.hpp"
#include "skill_data.hpp"
#include "skill_cost.hpp"
#include "source_skill_action.hpp"
#include "gunner_basic.hpp"
#include "female_gunner.hpp"
#include "female_gunner_timing.hpp"
#include "female_gunner_skill_layers.hpp"
#include "../../../reverse-60us/integration/include/dnf_ani_clock.hpp"
#include <array>
#include <optional>
#include <set>
#include <stdexcept>

namespace dnf {
class CharacterAdvancementCatalog;
class SkillLearningService;
// Opt-in user experiment. Source bindings are real; assigning an ANI/ATK to a
// skill is user configuration, not a restored native skill controller.
struct ExperimentalSourceBinding {
    std::string tag;
    size_t slot = 0, occurrence = 0;
    SourceRef source;
    Json json() const;
};
struct ExperimentalSkillRow {
    SkillKey key;
    SkillSourceKind kind = SkillSourceKind::Unknown;
    std::string name;
    SourceRef source;
    std::shared_ptr<const SkillSourceData> data;
    Json diagnostics = Json::array();
    Json json() const;
};
struct ExperimentalCharacterPlan {
    CharacterIdentity identity;
    SourceRef characterSource;
    CharacterDefinition characterDefinition;
    std::string pvfIdentity, job;
    std::vector<ExperimentalSourceBinding> motions, attacks;
    std::map<SkillKey, ExperimentalSkillRow> skills;
    std::map<std::string, std::shared_ptr<const Animation>> animations;
    std::map<std::string, AttackDamageDefinition> attackDefinitions;
    std::map<SkillKey,SourceSkillAction> sourceSkillActions;
    std::map<int,GunnerBasicSource> gunnerBasicSources;
    std::map<SkillKey, FemaleGunnerSkillDescriptor> femaleGunnerSkills;
    std::map<SkillKey,std::map<std::string,std::vector<FemaleGunnerSkillLayer>>> femaleGunnerSkillLayers;
    Json diagnostics = Json::array();
    const ExperimentalSourceBinding *motion(const std::string &tag, size_t slot = 0, size_t occurrence = 0) const;
    const ExperimentalSourceBinding *attack(const std::string &tag, size_t slot = 0, size_t occurrence = 0) const;
    Json snapshot() const;
};
ExperimentalCharacterPlan loadExperimentalCharacterPlan(Pvf &, Assets &, const CharacterCatalog &, CharacterIdentity,
    const CharacterAdvancementCatalog *explicitAdvancementAdmission = nullptr);

struct ExperimentalSkillBinding {
    SkillKey key;
    SourceRef skillSource;
    int level = 1;
    ExperimentalSourceBinding motion;
    std::optional<ExperimentalSourceBinding> attack;
    Json unknown = Json::object();
};
class ExperimentalSkillConfiguration {
    CharacterIdentity identity_;
    std::string pvfIdentity_;
    std::string weaponTypePolicy_ = "physical";
    std::array<std::optional<SkillKey>, 13> slots_{};
    std::map<SkillKey, ExperimentalSkillBinding> bindings_;
    Json unknown_ = Json::object();
  public:
    static const std::array<const char *, 13> &slotLabels();
    explicit ExperimentalSkillConfiguration(const ExperimentalCharacterPlan &);
    CharacterIdentity identity() const { return identity_; }
    const std::string &weaponTypePolicy() const { return weaponTypePolicy_; }
    void setWeaponTypePolicy(const std::string &);
    const std::array<std::optional<SkillKey>, 13> &slots() const { return slots_; }
    const ExperimentalSkillBinding *binding(SkillKey) const;
    void assignSlot(size_t slot, std::optional<SkillKey>, const ExperimentalCharacterPlan &);
    // Same-job CHR source choices only. Passive/internal/unknown mechanisms are
    // shown in the source list but cannot masquerade as an active controller.
    void configureSkill(SkillKey, const ExperimentalSourceBinding &motion,
                        std::optional<ExperimentalSourceBinding> attack, int level,
                        const ExperimentalCharacterPlan &);
    // User-authorized temporary release template. Uses this job's exact basic
    // CHR motion/ATK, the shared Swordman frame reader and source skill MP/CD.
    void configureBasicAttackTemplate(SkillKey, int level, const ExperimentalCharacterPlan &);
    void configureFemaleGunnerSourceSkill(SkillKey, int level, const ExperimentalCharacterPlan &);
    void configureSourceSkillAction(SkillKey, int level, const ExperimentalCharacterPlan &);
    void configureSourceActionPassive(SkillKey, int level, const ExperimentalCharacterPlan &);
    int sourceActionPassiveLevel(SkillKey) const;
    // Explicit comparison until caller/timing is reviewed for normal admission.
    void setSourceActionAudioPolicy(const std::string &, const ExperimentalCharacterPlan &);
    std::string sourceActionAudioPolicy() const;
    // Explicit test comparison policy; normal character saves are unaffected.
    void setSourceBodyRecoveryPolicy(const std::string &);
    std::string sourceBodyRecoveryPolicy() const;
    int femaleGunnerPassiveLevel(SkillKey) const;
    std::map<SkillKey,int> femaleGunnerLevels() const;
    void clearSkillBinding(SkillKey);
    Json snapshot() const;
    bool sameConfiguration(const ExperimentalSkillConfiguration &) const;
    void restore(const Json &, const ExperimentalCharacterPlan &);
    Json rows(const ExperimentalCharacterPlan &) const;
};

struct ExperimentalActorState {
    std::vector<FemaleGunnerSkillCommand> femaleGunnerBuffs;
    double x = 0, y = 0, z = 0, vx = 0, vy = 0, vz = 0;
    int direction = 1, mp = 0;
    int weaponSubtype = -1;
    Json gunnerAimTarget;
    bool alive = true, blocked = false, hitStopped = false;
    bool noCooldown = false;
    double movePerMille = 1000, attackPerMille = 1000;
    double dashXRatio = 1, dashYRatio = 1;
};
struct ExperimentalMovementPolicy {
    std::string id = "inferred-experimental-motion-v1";
    double walkSpeed = 180, runSpeed = 300, verticalRatio = 0.65;
    double jumpVelocity = 430, gravity = 980;
    int64_t doubleTapMs = 230;
};
struct ExperimentalAttackFrame {
    // Detached source PO geometry bypasses character equipment composition.
    bool sourceEntity = false, suppressBodyDamage = false, sourceImpact = false;
    uint64_t sourceEntityInstance = 0;
    std::array<double,3> sourceOrigin{};
    int sourceDirection = 1;
    std::optional<double> sourceLift;
    std::string sourceFamily;
    std::optional<FemaleGunnerSkillCommand> femaleGunnerCommand;
    uint64_t actionSequence = 0;
    size_t sourceFrame = 0;
    std::shared_ptr<const std::vector<int32_t>> animationControllerDelays;
    std::optional<ani_clock::Snapshot> animationClock;
    std::optional<SkillKey> skill;
    ExperimentalSourceBinding motion;
    std::optional<ExperimentalSourceBinding> attack;
    std::vector<Box> boxes;
    std::optional<DamageSkillModifiers> skillModifiers;
    uint32_t pulseId = 0;
    bool gunnerScheduledShot = false;
    bool gunnerDownShot = false;
};
// A transaction prepared at the actual skill start boundary. Preparation may
// throw to reject before MP/CD/motion publication. The runtime publishes only
// after begin succeeds; destruction before publication discards staged work.
struct ExperimentalSkillActionRequest {
    SkillKey key;
    SourceRef skillSource, motionSource;
    uint64_t fixedTick = 0, actionSequence = 0, attemptSequence = 0;
};
class PreparedExperimentalSkillAction {
  public:
    virtual ~PreparedExperimentalSkillAction() = default;
    virtual void publish() noexcept = 0;
};
using ExperimentalSkillActionGate = std::function<std::unique_ptr<PreparedExperimentalSkillAction>(const ExperimentalSkillActionRequest &)>;
struct ExperimentalSourceVisual {
    enum class Kind { Preflight, Spawn, Update, Retire } kind = Kind::Preflight;
    SkillKey key;
    uint64_t entity = 0, actionSequence = 0;
    bool impact = false, loop = false;
    int lifetimeMs = 0;
    double imageScale = 1, autoLayerScale = 1;
    std::array<double,3> position{};
    int direction = 1;
    Json evidence = Json::object();
};
struct ExperimentalTickResult {
    // Kept private until World adapter's CHR/EQU/LAY preflight also succeeds.
    // Destroying a rejected candidate result discards it without publication.
    std::unique_ptr<PreparedExperimentalSkillAction> preparedSkillAction;
    ExperimentalActorState actor;
    std::string animationPath, state = "stay";
    double animationAgeMs = 0;
    std::vector<FemaleGunnerSkillLayer> skillAnimationLayers;
    std::shared_ptr<const std::vector<int32_t>> animationControllerDelays;
    std::optional<ani_clock::Snapshot> animationClock;
    int poseFrame = -1;
    std::vector<ExperimentalAttackFrame> attacks;
    std::vector<std::string> sounds;
    std::vector<FemaleGunnerSkillCommand> femaleGunnerCommands;
    std::vector<ExperimentalSourceVisual> sourceSkillVisuals;
    std::vector<SourceSkillCameraFeedback> sourceCameraShakes;
    Json diagnostics = Json::array();
};
class ExperimentalCharacterRuntime {
    std::shared_ptr<const ExperimentalCharacterPlan> plan_;
    ExperimentalSkillConfiguration configuration_;
    ExperimentalMovementPolicy policy_;
    BasicAttackMovementPolicy basicMovementPolicy_;
    std::optional<BasicAttackGlide> dashAttackGlide_;
    std::array<bool, 4> held_{};
    // Transient physical release ownership, independent of slot rebinding.
    // Negative key denotes an explicit command request with matching KEYUP.
    std::set<int> heldSkillKeys_;
    int requestedReleaseKey_ = -1, activeReleaseKey_ = -1;
    bool attackHeld_ = false, jumpHeld_ = false, attackEdge_ = false, jumpEdge_ = false;
    bool jumpRequested_ = false, attackRequested_ = false, running_ = false, comboQueued_ = false;
    std::optional<SkillKey> skillRequested_, activeSkill_;
    struct BufferedDefaultSkill { SkillKey skill; uint64_t ownerActionSequence = 0; };
    std::optional<BufferedDefaultSkill> defaultSkillRequested_, bufferedDefaultSkill_;
    std::optional<ExperimentalSourceBinding> activeMotion_, activeAttack_;
    std::map<SkillKey, int64_t> cooldowns_;
    int64_t lastLeft_ = -100000, lastRight_ = -100000, lastMs_ = -1;
    uint64_t lastTick_ = 0, actionSequence_ = 0, skillAttemptSequence_ = 0;
    size_t combo_ = 0;
    // Source CHR jump ready/shoot/end stages. -1 means no ordinary air shot.
    int femaleGunnerBasicJumpStage_ = -1;
    std::optional<AnimationPlayback> jumpLocomotion_;
    struct GunnerGroundState {int subtype=-1,phase=0;uint32_t shots=0;int64_t elapsed=0;bool emitted=false;GunnerBasicDeadlines deadlines;bool down=false;};
    std::optional<GunnerGroundState> gunnerGround_;
    bool gunnerTargetAimEnabled_=true;
    void beginGunnerGroundPhase(int phase,int subtype,uint64_t fixedTick,double attackSpeed,bool down);
    double age_ = 0;
    int lastFrame_ = -1;
    // The requested policy is applied only when a new action is installed.
    // Candidates share immutable owned delays, so Cursor's borrowed pointers
    // survive runtime copies/moves and private World preflight publication.
    std::optional<ani_clock::ClockPolicy> animationClockPolicy_;
    std::shared_ptr<const std::vector<int32_t>> animationDelays_;
    std::optional<ani_clock::Cursor> animationCursor_;
    std::vector<ani_clock::FrameVisit> initialClockVisits_;
    int32_t animationSpeedStat_ = 0;
    std::optional<FemaleGunnerStageTiming> actionTiming_;
    Json pendingDiagnostics_ = Json::array();
    Json lastCost_ = Json::object();
    size_t femaleGunnerStage_ = 0;
    int femaleGunnerRepeat_ = 0;
    bool femaleGunnerEmissionPending_ = false;
    std::optional<FemaleGunnerSkillCommand> femaleGunnerAction_;
    int64_t femaleGunnerStageElapsedMs_ = 0;
    std::optional<FemaleGunnerChannelContract> channelContract_;
    std::optional<FemaleGunnerChannelState> channelState_;
    int64_t channelRecoveryRemainingMs_ = 0;
    bool femaleGunnerModeAttack_ = false, femaleGunnerModeBlade_ = false;
    // Authored alternate CHR actions used only while source skill100 is live.
    std::vector<FemaleGunnerStage> femaleGunnerOverrideStages_;
    std::vector<int> femaleGunnerOverrideDamageColumns_;
    bool femaleGunnerFinishMode_ = false;
    struct SourceActionState {
        SkillKey key;SourceSkillOperands operands;bool emitted=false;
        int64_t unpausedMs=0;
        int64_t layerBirthUnpausedMs=-1;
        std::string recoveryPolicy="after_animation";
        bool attackSoundEmitted=false;
        std::optional<SourceBodySidestepState> sidestep;
    };
    int64_t sourceBodyRecoveryRemainingMs_=0;
    std::map<uint64_t,SourceActionState> sourceActions_;
    struct SourceEntity {
        uint64_t instance=0,actionSequence=0;
        SkillKey key;SourceSkillOperands operands;
        std::array<double,3> position{},origin{};int direction=1;
        bool impact=false;
        AnimationPlayback playback;
        std::vector<ani_clock::FrameVisit> initialVisits;
    };
    std::optional<AxisMotion> sourceRecoil_;
    uint64_t sourceEntitySequence_ = 0;
    std::vector<SourceEntity> sourceEntities_;
    void publishSourceSkillEntities(ExperimentalTickResult &,uint64_t fixedTick);
    bool begin(const ExperimentalSourceBinding &, std::optional<ExperimentalSourceBinding>, std::optional<SkillKey>,
               uint64_t lastClockTick, double attackPerMille, const FemaleGunnerStageTiming *timing = nullptr);
  public:
    explicit ExperimentalCharacterRuntime(std::shared_ptr<const ExperimentalCharacterPlan>, ExperimentalMovementPolicy = {});
    const ExperimentalCharacterPlan &plan() const { return *plan_; }
    ExperimentalSkillConfiguration &configuration() { return configuration_; }
    const ExperimentalSkillConfiguration &configuration() const { return configuration_; }
    void setAnimationClockPolicy(std::optional<ani_clock::ClockPolicy>);
    void setBasicAttackMovementEnabled(bool);
    bool request(const CharacterActionRequest &);
    ExperimentalTickResult advance(uint64_t fixedTick, const ExperimentalActorState &,
                                  const std::function<bool(double,double)> &canWalk,
                                  const ExperimentalSkillActionGate &skillGate = {});
    void cancel(ControllerCancelReason);
    // Reconstructed host input-ownership policy, not a proven native rule.
    // Live voluntary-action interruption retains only physical movement;
    // action requests, release keys, combo and double-tap history are reset.
    // The World caller must exclude dead/zero-HP/non-Alive actors.
    void interruptActionPreservingMovement();
    bool neutralReactionReady() const noexcept;
    ExperimentalCharacterRuntime prepareNeutralReaction() const;
    // Only one source BodyAttack with no spawned entity/channel/air action.
    // World additionally owns the grounded/recovery/capture qualification.
    bool sourceBodyReactionReady() const noexcept;
    bool sourceMovingReactionReady() const noexcept;
    ExperimentalCharacterRuntime prepareSourceMovingReaction(bool death=false) const;
    ExperimentalCharacterRuntime prepareSourceBodyReaction() const;
    void releaseInputs();
    bool attacking() const { return bool(activeMotion_); }
    bool sourceFrameSuperArmor() const;
    bool gunnerTargetAimEnabled() const noexcept { return gunnerTargetAimEnabled_; }
    void setGunnerTargetAimEnabled(bool enabled) {
        if(attacking())throw std::logic_error("Gunner aim policy changes require idle");
        gunnerTargetAimEnabled_=enabled;
    }
    bool sourceEntityIsMovingFlight(uint64_t id) const;
    // Caller mutates a private runtime copy; publishing the returned
    // impact and retiring its original entity must share the hit commit.
    ExperimentalSourceVisual acceptSourceMovingHit(uint64_t id,uint64_t fixedTick);
    bool sourceSkillEntityLive(uint64_t id) const {for(const auto &entity:sourceEntities_)if(entity.instance==id)return true;return false;}
    std::optional<uint64_t> activeActionSequence() const { return activeMotion_?std::optional<uint64_t>(actionSequence_):std::nullopt; }
    int64_t remainingCooldown(SkillKey, int64_t nowMs) const;
    Json cooldownSnapshot(int64_t nowMs) const;
    static std::map<SkillKey,int64_t> prepareCooldownRestore(
        const Json &, const ExperimentalCharacterPlan &, int64_t restoredNowMs);
    void publishCooldownRestore(std::map<SkillKey,int64_t> deadlines) noexcept { cooldowns_.swap(deadlines); }
    ExperimentalCharacterRuntime rebasedForIdentity(std::shared_ptr<const ExperimentalCharacterPlan>,
        const SkillLearningService &, int normalLevel) const;
    Json snapshotDiagnostics() const;
};

// Experimental factory calls only the explicitly supplied World callbacks.
// World must branch those callbacks to the runtime above, never applyInput.
void registerExperimentalControllers(CharacterControllerRegistry &, const CharacterCatalog &, const std::string &pvfIdentity);

class World;
struct Actor;
class ExperimentalWorldAdapter {
    World &world_;
    uint64_t action_ = 0, attackId_ = 0;
    uint64_t contactPulse_ = 0;
    std::set<EntityHandle> hitTargets_;
    struct SourceContactLedger {uint64_t attackId=0;int effectId=-1;std::set<EntityHandle> targets;};
    std::map<uint64_t,SourceContactLedger> sourceContactLedgers_;
    void record(Json);
    bool contact(Actor &, const ExperimentalAttackFrame &, const AttackDamageDefinition &);
    bool contactMoving(Actor &,const ExperimentalAttackFrame &,const AttackDamageDefinition &,ExperimentalCharacterRuntime &);
  public:
    explicit ExperimentalWorldAdapter(World &);
    bool movingReactionReady(const ExperimentalCharacterRuntime &) const noexcept;
    void publishMovingDeathReaction() noexcept {sourceContactLedgers_.clear();publishNeutralReaction();}
    bool neutralReactionReady() const noexcept { return sourceContactLedgers_.empty(); }
    void publishNeutralReaction() noexcept { action_=attackId_=contactPulse_=0;hitTargets_.clear(); }
    void advance(ExperimentalCharacterRuntime &, uint64_t fixedTick);
};
Json runExperimentalCharacterTests(Pvf &, Assets &);
} // namespace dnf
