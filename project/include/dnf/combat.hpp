#pragma once
#include "resources.hpp"
#include "dnf/basic_attack_movement.hpp"
#include "dnf/monster_action_ai.hpp"
#include "character.hpp"
#include "skill_data.hpp"
#include "skill_cost.hpp"
#include "skill_input_policy.hpp"
#include "attributes.hpp"
#include "speed_attributes.hpp"
#include "equipment_attributes.hpp"
#include "combat_attributes.hpp"
#include "damage_resolution.hpp"
#include "combat_pipeline.hpp"
#include "attack_status.hpp"
#include "skill_learning.hpp"
#include "character_controller.hpp"
#include "experimental_character.hpp"
#include "female_gunner_skill_layers.hpp"
#include "appearance.hpp"
#include "animation_events.hpp"
#include "monster_effects.hpp"
#include "monster_attributes.hpp"
#include "monster_combat_attributes.hpp"
#include "monster_event_ai.hpp"
#include "dnf/monster_damage_check.hpp"
#include "simulation.hpp"
#include "debug_types.hpp"
#include <array>
#include <deque>
#include <map>
#include <set>
#include <functional>
namespace dnf {
class CharacterAdvancementCatalog;
class PreparedCharacterAdvancement;
class ActWorldHost;
class SquirrelActionService;
class FemaleGunnerWorld;
class Progression;
struct Operation;
struct CombatBox;
class PreparedSkillRuntime {
    struct Data;
    std::unique_ptr<Data> data_;
    explicit PreparedSkillRuntime(std::unique_ptr<Data>);
    friend class World;
  public:
    ~PreparedSkillRuntime();
    PreparedSkillRuntime(PreparedSkillRuntime &&) noexcept;
    PreparedSkillRuntime &operator=(PreparedSkillRuntime &&) noexcept;
    PreparedSkillRuntime(const PreparedSkillRuntime &) = delete;
    Json writeCharacter(Json character) const;
};
// Preparation-only references. They are consumed synchronously and never
// retained in a durable pending generation. The prepared object owns copies.
struct SkillRuntimeProjectionContext {
    int normalLevel = 1, effectiveLevel = 1;
    bool testLearning = false, previewEnabled = false, restoring = false;
    int64_t nowMs = -1;
    const ExperimentalCharacterRuntime *runtime = nullptr;
    const CharacterAppearance *appearance = nullptr;
    const ExperimentalSkillConfiguration *normalPreferences = nullptr;
    const ExperimentalSkillConfiguration *testPreferences = nullptr;
    const ExperimentalSkillConfiguration *previewPreferences = nullptr;
};

struct ObjectDefinition;
struct ObjectInstance;
struct EffectEventPlan;
class SkillMappingTable;
enum class MovementPolicy { Locked, AirControl };
enum class WorldRules { LegacyDemoV1, BetaFoundationV1 };
enum class AttributeRebuildReason { EquipmentChange, NormalLevelUp, CharacterRestore, DebugLevelOverride };
enum class ActorLife { Alive, Dying, DeathEffect, Removed };
// Controller calibration, separate from immutable ANI frame delays.
struct MotionProfile {
    int accelerationMs = 90, decelerationMs = 110;
    double distance(double elapsedMs, double durationMs, double peakSpeed) const;
    double velocity(double elapsedMs, double durationMs, double peakSpeed) const;
};
struct Stage {
    std::string animation;
    double moveSpeed = 0;
    bool armor = false, invincible = false;
    int duration = 0;
    MovementPolicy movement = MovementPolicy::Locked;
    MotionProfile motion;
};
struct Skill {
    int jobId = 0;
    int level = 1, maxLevel = 1;
    int id = 0;
    std::string key, name, source;
    std::vector<Stage> stages;
    int cooldown = 0, mp = 0, casting = 0;
    Json levelInfo = Json::array(), command = Json::array();
    std::shared_ptr<const SkillSourceData> sourceData;
    double parameter(int col) const;
    std::string effect;
    bool continuation = false, airOnly = false;
    // This branch of the constructor registers the skill's visuals by hand, so
    // the shared mapping layer must not add the same effect a second time.
    bool manualVisuals = false;
    std::string evidence = "controller reconstruction; PC parity pending";
    SkillKey identity() const { return {jobId, id}; }
};
struct Input {
    int64_t ns = 0;
    int key = 0;
    bool down = false;
};
struct MonsterProjectileDefinition;
// Simulation-owned 40JP reaction state. Velocities remain in Actor; these
// coefficients/timers survive a room save without redrawing reaction RNG.
struct MonsterHitReaction {
    int state = 0; // 0 none, 3 standing hurt, 4 flight/bounce
    int substate = 0; // 0 first flight, 1 ground bounce
    int direction = 1;
    int32_t accelerationX = 0, accelerationRemainingMs = 0;
    int32_t gravity = -1500;
    int64_t remainingMs = 0;
    double peakHeight = 0, launchHeight = 0, pushSpeed = 0, weight = 45000;
};
struct Actor {
    int id = 0;
    EntityHandle handle;
    double x = 300, y = 260, z = 0, px = 300, py = 260, pz = 0, vz = 0;
    int dir = 1, hp = 180, maxHp = 180, mp = 140, maxMp = 140;
    int poseFrame = -1;
    std::optional<ani_clock::Snapshot> animationClock;
    std::string animationClockSource;
    // Action-local controller timing; immutable source ANI delays stay intact.
    // This transient view must be shared by equipment/ALS root projections.
    std::shared_ptr<const std::vector<int32_t>> animationControllerDelays;
    std::vector<FemaleGunnerSkillLayer> skillAnimationLayers;
    std::string animation = "stay";
    int64_t animStart = 0, stunUntil = 0;
    // Actor-local hit pause; input, cooldowns and the world clock continue.
    int hitStopTicks = 0;
    bool hitStopped = false;
    SkillFailureFeedback skillFailureFeedback;
    SourceSkillCameraFeedback sourceSkillCameraFeedback;
    bool boss = false, dead = false;
    int capturedBy = -1;
    std::string monsterPath;
    // Immutable initialization receipt. Old session actors keep an empty
    // receipt and their saved HP; restoring a room never recalculates it.
    Json sourceStats = Json::object();
    std::optional<MonsterCombatAttributes> combatAttributes;
    std::shared_ptr<const MonsterProjectileDefinition> projectileDefinition;
    int64_t nextAttack = 0;
    bool attackHit = false;
    int recovery = 0; // 0 active, 1 airborne knockdown, 2 down, 3 getting up
    double vx = 0, vy = 0;
    MonsterHitReaction hitReaction;
    ActorLife life = ActorLife::Alive;
    int64_t deathStart = 0, lifeStart = 0, deathPoseTime = 0, hitFlashUntil = 0;
    std::string animationPath; // optional original MOB motion selected by controller
    int sourceId = 0, attackVariant = 0, attackSerial = 0;
    // Immutable lethal pose and source-bound death plan, separate from living
    // motion clocks and from the shared resource/animation cache.
    std::shared_ptr<const MonsterMotion> deathMotion;
    MonsterDeathProfile deathProfile;
    DeathImpulse lastImpact;
    std::vector<MonsterFragment> deathFragments;
    std::array<double, 4> deathBounds{};
    double deathAnchorX = 0, deathAnchorY = 0, deathHeight = 0;
    int deathDuration = 500;
    bool deathLoop = false, independentDeath = false;
    std::string deathRoute;
};
// Source-bound projectile preparation. This is a named beta inference for a
// MOB particle throw with a registered OBJ template, not proof of native PC
// object-type dispatch. Owned documents preserve bytes, ordered tokens and
// unknown fields; usable() covers launch/contact, not destroy-particle display.
struct MonsterProjectileDefinition {
    std::string policy = "inferred-mob-particle-object-projectile-v1";
    int objectId = 0, level = 0, attackVariant = 0, projectileCount = 0;
    int objectType = -1, power = 0, attackNumber = 0, throwFrame = -1;
    int lifetimeMs = 0;
    double offsetX = 0, offsetY = 0, offsetZ = 0, speed = 0;
    std::string animation, throwAnimation, throwSound, attackPath, landingType;
    bool loop = false;
    std::array<int, 2> width{};
    int floatingHeight = 0, piercingPower = 0;
    std::string layer, passType;
    Script monster, registry, object, motionParticle, destroyParticle;
    Bytes projectileAnimationBytes, throwAnimationBytes;
    AttackDamageDefinition attack;
    std::shared_ptr<const Animation> projectileMotion, throwMotion;
    Json sources = Json::object(), trace = Json::array(), diagnostics = Json::array();
    bool usable() const;
    Json snapshot(bool includeSource = false) const;
};
struct Effect {
    int id = 0, skill = 0;
    std::string animation;
    double x = 0, y = 0, z = 0, px = 0, py = 0;
    // A newly created effect without an explicitly sampled previous Z starts
    // at its current height, rather than interpolating from world ground.
    std::optional<double> pz;
    double imageScale = 1, autoLayerScale = 1;
    std::string sourceTreePolicy;
    bool alsFollowParent=false;
    std::array<double,3> alsFollowOffset{};
    double speed = 0;
    int dir = 1;
    int64_t born = 0, expires = 0;
    int interval = 0;
    bool attached = false;
    bool hostile = false;
    int hostileOwner = -1;
    std::string hostileAttack;
    EntityHandle hostileOwnerHandle;
    std::optional<DamageCombatant> hostileStats;
    uint64_t attackInstance = 0;
    Json projectileSource = Json::object();
    int pulses = 0, maxPulses = 0;
    int firstPulse = 0, pulseWindow = 0;
    double offsetX = 0, offsetY = 0;
    std::map<int, int64_t> hits;
    std::map<int, int> counts;
    bool loop = false, damageEnabled = true;
    // A source layer is local draw order, never a world-Y/ground sentinel.
    int layer = 1, parentId = -1;
    bool groundRender = false;
    // Persistent skill entity (Spiral Nen orb, lotus field, hanging sword).
    // The position is recomputed from the owner every tick, so the entity orbits
    // the caster instead of sitting at its spawn point.
    double orbitRadius = 0, orbitSpeedDeg = 0, orbitPhaseDeg = 0;
    double orbitCenterY = 0;
    std::string phase;
    int64_t animationOffset = 0;
    double trajectoryStartX = 0;
    double vz = 0, gravity = 0;
    int trajectoryMs = 0; // straight-line PTL active interval, then keep last value
    std::string sourceObject, resourceSource;
    size_t sourceOffset = 0;
    // Independent source clock; follow-position and pause are separate host
    // bindings. No unknown source rate-inheritance flag is invented here.
    AnimationPlayback playback;
    std::optional<ani_clock::Snapshot> animationClock;
    bool clockBound = false, pauseWithPlayer = false, clockOffsetFallback = false;
    std::string clockSource;
    int alsParentId = -1, alsDepth = 0;
    std::string alsInstance;
    std::shared_ptr<const EffectEventPlan> frameEvents;
    // Invisible hosts consume the actual body's/equipment's published clock;
    // they never advance that clock or draw the same character a second time.
    bool drawSelf = true, actorAnimationHost = false;
    std::string actorHostKey;
    std::optional<uint64_t> actorActionSequence;
    std::optional<ani_clock::Snapshot> actorHostRootClock, actorHostClock;
    uint64_t actorHostFirstVisit = 1;
};
struct AttackVolume {
    uint64_t serial = 0;
    double x = 0, y = 0, z = 0;
    int direction = 1, damage = 1;
    Box box{};
    uint64_t pulse = 0;
    int skillId = 0, skillPhase = 0;
    std::optional<AttackDamageDefinition> sourceAttack;
    std::optional<DamageSkillModifiers> sourceModifiers;
    std::optional<DamageAttackType> sourceWeaponType;
    std::string sourceMotionTag, sourceAttackFamily;
    std::optional<DamageSkillModifiers> sourceFortModifiers;
};
struct AttackResponse {
    std::string source, sound;
    double push = 0, lift = 0;
    bool knockDown = false, noReaction = false;
    int reactionIndex = 0;
    std::string hitEffect;
    // Literal mode-selected ATK operands. The hit-effect family and angle are
    // shared presentation policy adapted from 40JP, never equipment subtype.
    std::string attackType, element, attackDirection;
    double hitPause = 0, hitDelayRate = 1;
    Json hitInfo = Json::array(); // Includes uninterpreted version-specific components.
};
// Shared PVF AttackInfo response reader used by the legacy controller and
// source-driven job/projectile adapters. It parses source fields without
// asserting that every operand has a recovered native 1031 caller.
AttackResponse readAttackResponse(const Script &source);
struct Event {
    int64_t tick = 0;
    std::string kind, name;
    int source = 0, target = 0, value = 0;
};
// Nonpersistent, handle-bound runtime consumer receipt for test exploration.
// Numerical source input, autonomous controller and ACT service are separate.
struct ExplorationMonsterConsumers {
    bool incomingDamage = false, legacyAutonomousController = false, sourceActions = false, captureAllowed = false;
    int sourceId = 0;
    std::string memberPath;
    Json combatSources = Json::object(), receipt = Json::object();
};
class World {
    friend class ActWorldHost;
    friend class ExperimentalWorldAdapter;
    friend class FemaleGunnerWorld;
    friend class SquirrelWorldBridge;
    friend Json runActCollisionTests(Pvf &,Assets &);
    friend Json runMonsterEffectsTests(Pvf &,Assets &);
    friend Json runWaterCannonRuntimeTests(Pvf &,Assets &);
    friend Json runCombatFeedbackTests(Pvf &,Assets &);
    friend Json runFighterNativeGrabTests(Pvf &,Assets &);
    bool experimentalEnabled_ = false;
    std::unique_ptr<ExperimentalCharacterRuntime> experimentalRuntime_;
    std::unique_ptr<ExperimentalWorldAdapter> experimentalAdapter_;
    std::unique_ptr<FemaleGunnerWorld> femaleGunnerWorld_;
    Json experimentalDiagnostics_ = Json::array();
    std::vector<Skill> swordmanSkills_, swordmanPassives_;
    Pvf &pvf_;
    Assets &assets_;
    CharacterCatalog characters_;
    CharacterControllerRegistry controllers_;
    std::unique_ptr<CharacterController> controller_;
    CharacterIdentity identity_;
    WorldRules rules_ = WorldRules::LegacyDemoV1;
    std::optional<CharacterBaseAttributes> baseAttributes_;
    std::optional<CharacterSpeeds> speedAttributes_;
    std::optional<EquipmentResourceAttributes> equipmentResources_;
    std::optional<CombatAttributeSnapshot> combatAttributes_;
    mutable std::unique_ptr<SkillLearningService> skillLearningService_;
    SkillLearningTestOverlay skillTestOverlay_;
    bool experimentalSkillPreviewEnabled_ = false;
    uint64_t skillProjectionRevision_ = 0;
    std::optional<ExperimentalSkillConfiguration> normalSkillConfiguration_;
    std::optional<ExperimentalSkillConfiguration> testSkillConfiguration_;
    std::optional<ExperimentalSkillConfiguration> previewSkillConfiguration_;
    SkillRuntimeProjectionContext currentSkillProjectionContext(bool test, int normalLevel, int effectiveLevel) const;
    void enforceLearnedSkillProjection();
    Json lastSkillLearningTrace_ = Json::object();
    Json lastDamageTrace_ = Json::object();
    // Runtime journal for the 40JP structural adapter.  It is diagnostic
    // state only; HP, status and random publication remain owned by World.
    CombatPipelineTrace lastCombatPipelineTrace_;
    mutable std::shared_ptr<const CharacterAdvancementCatalog> advancementCatalog_;
    CharacterControllerServices controllerServices();
    struct PreparedPlayerReaction {
        std::optional<ExperimentalCharacterRuntime> runtime,movingDeathRuntime;
        std::optional<std::vector<Effect>> movingDeathEffects,movingDeathPendingEffects;
        CharacterSkillState skills;
        SequencedCommandQueue<Input> inputs;
        std::vector<Effect> effects,pendingEffects;
        std::shared_ptr<FemaleGunnerWorld> femaleDeath;
        Json receipt=Json::object();
    };
    struct PreparedPlayerDefense {
        DamageRequest request;
        bool immune=false;
        bool superArmor=false; // reaction suppression only; HP/status still resolve
        Json receipt=Json::object();
    };
    std::string neutralPlayerReactionGate(const Actor &) const;
    PreparedPlayerDefense preparePlayerDefense(DamageRequest) const;
    PreparedPlayerReaction prepareNeutralPlayerReaction(const Actor &) const;
    void publishNeutralPlayerReaction(PreparedPlayerReaction &) noexcept;
    void projectSkillLevels();
    double basicLocalAge_ = 0;
    int64_t basicClockMs_ = 0;
    std::optional<ani_clock::ClockPolicy> animationClockPolicy_;
    ani_render::RenderProfile renderProfile_ = ani_render::RenderProfile::Legacy1031;
    AnimationPlayback basicPlayback_;
    BasicAttackMovementPolicy basicMovementPolicy_;
    std::optional<BasicAttackGlide> dashAttackGlide_;
    AnimationPlayback locomotionPlayback_;
    std::string locomotionClockSource_;
    int64_t locomotionClockStart_ = -1;
    std::vector<ani_clock::FrameVisit> basicFrameVisits_;
    int32_t basicSpeedStat_ = 1000;
    void installBasicPlayback();
    void advanceBasicPlayback(bool paused);
    void clearBasicPlayback();
    void advanceLocomotionPlayback();
    struct PickupActionState {
        std::string path;
        AnimationPlayback playback;
        Json source = Json::object();
    };
    std::optional<PickupActionState> pickupAction_;
    Json lastPickupActionTrace_ = Json::object();
    void advancePickupAction();
    void clearPickupAction() noexcept;
    std::map<std::string,std::shared_ptr<const EffectEventPlan>> effectEventPlans_;
    void advanceEffectClocks();
    void synchronizeCharacterEffectHosts();
    uint64_t attributeRevision_ = 0;
    Json lastAttributeChange_ = Json::object();
    Json lastEquipmentChange_ = Json::object();
    std::optional<CharacterAppearance> equippedAppearance_;
    mutable std::map<int, CharacterAppearance> diagnosticAppearances_;
    SequencedCommandQueue<Input> inputs_;
    std::array<bool, 512> held_{};
    FixedStepClock clock_;
    MonotonicIds effectIds_;
    SimulationIdSources ids_;
    RandomStreams random_;
    EntityRegistry entities_;
    StatusHost statuses_;
    std::unique_ptr<ActWorldHost> actHost_;
    std::unique_ptr<SquirrelActionService> squirrelActions_;
    MonotonicIds sourceActionInstanceIds_;
    std::map<std::pair<EntityHandle,int>,int64_t> sourceActionCooldowns_;
    struct SourceActionRequest {
        EntityHandle owner; std::string state; int index = 0;
        std::optional<Pcg32> aiRandom;
        Json aiTrace = Json::object();
    };
    std::vector<SourceActionRequest> sourceActionRequests_;
    std::set<EntityHandle> sourceActionActors_, sourceActionVisited_;
    std::map<EntityHandle,MonsterSourceMovement> monsterSourceMovements_;
    // Immutable per-World source conversion; never reparse/hash MOB movement
    // fields on every render or simulation frame.
    std::map<std::pair<std::string,int>,MonsterSourceMovement> legacyMonsterMovementPlans_;
    Json actServiceDiagnostics_ = Json::array();
    struct MonsterEventAiBinding {
        int sourceId = 0;
        std::string memberPath;
        MonsterEventAiRoute route;
        std::shared_ptr<const MonsterEventAiProgram> program;
        uint64_t randomStreamKey=0;
    };
    struct PendingMonsterEventHit {
        EntityHandle target;
        uint64_t acceptedTick = 0;
        MonsterAcceptedHit hit;
    };
    struct PreparedMonsterEventHit {
        bool ready = true, required = false;
        std::string error;
        MonotonicIds events;
        std::vector<PendingMonsterEventHit> pending;
        std::map<EntityHandle,MonsterDamageWindow> windows;
        EntityHandle target;
        uint64_t eventId=0;
    };
    struct MonsterEventRoomRestore {
        std::map<EntityHandle,MonsterEventAiBinding> bindings;
        std::map<EntityHandle,MonsterDamageWindow> windows;
        std::vector<PendingMonsterEventHit> pending;
        std::set<EntityHandle> actors;
    };
    MonsterEventRoomRestore prepareMonsterEventRoomRestore(const std::vector<Actor> &,const Json &) const;
    std::map<EntityHandle,MonsterEventAiBinding> monsterEventAiBindings_;
    std::vector<PendingMonsterEventHit> monsterEventAiPending_;
    std::map<EntityHandle,MonsterDamageWindow> monsterDamageWindows_;
    Json monsterEventAiDiagnostics_ = Json::array();
    // Registrations and exact Event.ai-created action IDs owned by the F7
    // test policy. Explicit non-test registrations/actions are never cleared.
    std::set<EntityHandle> monsterEventAiTestOwners_;
    std::map<EntityHandle,uint64_t> monsterEventAiTestInstances_;
    std::string monsterEventAiTestSignature_, monsterEventAiTestSelection_;
    Json monsterEventAiTestReceipt_ = Json::object();
    // Ordinary source-think discovery owns only an attempt cache, never an
    // external/F7/restored binding. Scene changes clear this transient cache.
    struct MonsterEventAiNormalAttempt {
        int sourceId=-1;
        std::string memberPath,difficulty,boundDifficulty;
        bool bound=false;
    };
    std::map<EntityHandle,MonsterEventAiNormalAttempt> monsterEventAiNormalAttempts_;
    Json monsterEventAiNormalDiagnostics_ = Json::array();
    void prepareNormalMonsterEventAiBoundary();
    PreparedMonsterEventHit prepareMonsterAcceptedHit(const Actor &,const std::string &cause) const;
    void publishMonsterAcceptedHit(PreparedMonsterEventHit &&,int actualHpLoss) noexcept;
    void prepareMonsterEventAiBoundary();
    void clearMonsterEventAi(const std::string &);
    bool mapExplorationActive_ = false, mapExplorationGeometryAvailable_ = false;
    std::map<EntityHandle, ExplorationMonsterConsumers> explorationConsumers_;
    bool explorationConsumerBound(const Actor &) const;
    bool explorationAllowsIncoming(const Actor &) const;
    bool explorationAllowsLegacyAi(const Actor &) const;
    bool explorationAllowsSourceActions(const Actor &) const;
    std::string explorationMonsterSound(const Actor &, bool dead) const;
    void prepareSourceActionBoundary();
    void advanceSourceActions(const SimulationStep &);
    void cancelSourceActions(const std::string &);
    void advanceMonsterSourceMovement(Actor &,int64_t deltaMs);
    DamageResolution resolveActorContact(const DamageRequest &,const StatusResistanceSnapshot &,const SkillStatusApplication * = nullptr);
    void advanceStatusEffects();
    void interruptStatusTarget(Actor &);
    uint64_t objectAttackSerial_ = 0;
    uint64_t actionInstance_ = 0;
    CharacterSkillState skillState_;
    std::function<void(World &)> objectTick_;
    std::function<void(World &)> beforeTick_;
    DebugOverrides debugOverrides_;
    int normalCharacterLevel_ = 1;
    int active_ = -1, stage_ = 0;
    // Shared with the previewer: keeps the live game from hand-registering the
    // same skill visuals a second time. Built lazily on the first cast.
    std::shared_ptr<SkillMappingTable> skillVisuals_;
    int bufferedSkill_ = -1;
    bool bufferedSkillCommand_ = false;
    int activeCooldownMs_ = 0;
    Json lastSkillCostTrace_ = Json::object();
    struct CachedSkillCost {
        std::shared_ptr<const SkillSourceData> source;
        int level = 0;
        std::string equipmentKey;
        SkillCostResult result;
    };
    mutable std::map<std::pair<int,bool>, CachedSkillCost> skillCostCache_;
    int64_t bufferedSkillUntil_ = 0;
    struct BufferedDefaultSkill { SkillKey skill; uint64_t ownerAction = 0; bool basic = false; };
    std::optional<BufferedDefaultSkill> bufferedDefaultSkill_;
    bool ownsDefaultSkillBuffer() const;
    void finishPlayerAction();
    void requestSkill(int index,bool command,bool afterCurrentAction);
    void rejectSkillFeedback(const std::string &,std::optional<SkillKey> = {});
    bool queued_ = false;
    int64_t stageStart_ = 0;
    int lastAttackFrame_ = -1;
    std::map<int, int> hits_;
    std::map<int, int> hitCounts_;
    std::set<int> hopFinalHits_;
    int64_t lastLeft_ = -100000, lastRight_ = -100000;
    bool running_ = false;
    int combo_ = 0;
    int captured_ = -1;
    double skillPeakHeight_ = 0, hopStartX_ = 0, hopTravel_ = 50, hopHeight_ = 50;
    int hopHeldMs_ = 0;
    int goreCrossPhase_ = 0, goreCrossEventEffect_ = -1;
    int64_t goreCrossPhaseTick_ = -1;
    AnimationEventCursor goreCrossEvents_;
    int64_t guardUntil_ = 0;
    std::deque<std::pair<int64_t, int>> commandHistory_;
    Json inputLog_ = Json::array();
    std::vector<Effect> pendingEffects_;
    mutable std::map<std::string, std::shared_ptr<const MonsterMotion>> monsterMotions_;
    std::map<std::pair<std::string,bool>, MonsterAttributeSource> monsterAttributeSources_;
    std::shared_ptr<const MonsterMotion> monsterMotion(const Actor &actor, const std::string &state) const;
    void input(const Input &in);
    void applyInput(const Input &in);
    void tickOnce();
    void simulateTick();
    void startStage(int n);
    void attackFrames(int64_t from, int64_t to);
    void strike(const Box &box, int index);
    bool damage(Actor &m, int value, double launch = 0, const std::string &cause = "",
                int responseSkill = -1, int phase = 0, int direction = 0,
                const ImpactContext &impact = {}, bool meleeContact = false,
                uint64_t attackInstance = 0, uint32_t hitIndex = 0, const CombatBox *contact = nullptr);
    void applyResponse(Actor &target, const AttackResponse &response, int direction);
    bool advanceMonsterHitReaction(Actor &target, int64_t movementMs);
    // Shared simulation-owned hurt pose. Uses the saved MonsterHurt stream;
    // renderers never choose a pose or advance gameplay randomness.
    void applyMonsterHurtMotion(Actor &target, const AttackResponse &response, double launch = 0);
    // Shared accepted-hit presentation boundary. Damage, HP/status commits,
    // reaction ownership and source-specific entity lifetimes stay with their
    // callers; this consumer only publishes monster feedback after those
    // commits succeed. The legacy weapon fallback is restricted to the old
    // Swordman path and is never borrowed by projectile/job adapters.
    void publishMonsterHitFeedback(Actor &target, const AttackResponse &response,
        int direction, int value, bool allowLegacyWeaponFallback, const CombatBox *contact = nullptr,
        bool critical = false);
    bool basicAttacking() const;
    void requestHitStop(Actor &actor, double milliseconds, const std::string &source);
    void advanceHitStop(Actor &actor);
    AttackResponse attackResponse(int skill, int phase = 0) const;
    // Owner CHR/EQU hit-info inheritance before a character-owned hit commits.
    // A cosmetic default weapon never supplies a real equipped subtype.
    AttackResponse characterAttackResponse(const Script &attack) const;
    void beginDeath(Actor &actor);
    void advanceLife(Actor &actor);
    void airMovement();
    std::string monsterAnimation(const Actor &actor, const std::string &tag) const;
    void addEffect(const std::string &path, int skill, double x, double y, int duration, double speed = 0);
    void stageEffects(int frame);
    // Builds the skill's effect layers and persistent entities from the shared
    // skill->visual mapping table (the same one the standalone previewer audits).
    void spawnSkillVisuals(const struct Skill &skill);
    void updateGoreCross(int bodyFrame);
    void expandEffectLayers(size_t first);
    bool matchCommand(int key);
    void hurtPlayer(int value, int direction, const Actor *attacker = nullptr, const std::string &attackPath = {},
        const DamageCombatant *frozenAttacker = nullptr, EntityHandle frozenOwner = {}, uint64_t attackInstance = 0);
    std::string monsterAttackPath(const Actor &actor) const;
    DamageSkillModifiers damageSkillModifiers(int id, int phase) const;
    int legacySkillDamage(int id, int phase) const;
    int skillDamage(int id, int phase = 0) const;
    bool overlaps(const Actor &a, const Box &b, const Actor &target, CombatBox *contact = nullptr) const;
    int nextEffectId();
    // Cancel transient state without allocating/publishing an incarnation.
    void clearSceneTransients();

  public:
    Actor player;
    std::vector<Actor> monsters;
    std::vector<Effect> effects;
    std::vector<Skill> skills;
    std::vector<Skill> passives;
    int characterLevel = 1;
    int normalCharacterLevel() const { return usesSourceGrowth()?normalCharacterLevel_:characterLevel; }
    std::array<int, 13> bindings{};
    std::vector<Event> events;
    std::vector<AttackVolume> attackVolumes;
    int64_t tick = 0;
    double walkSpeed = 180, runSpeed = 300;
    int weapon = 0;
    int equipmentAttack = 0, equipmentDefense = 0;
    int bloodVigorousLevel = 0; // Advanced passive, never granted to an unadvanced character.
    bool combat = false, god = false, freeCd = false, freezeAi = false;
    int mapWidth = 1200;
    std::vector<std::array<double, 4>> walkRects;
    std::vector<std::array<double, 4>> blockedRects;
    explicit World(Pvf &p, Assets &a, WorldRules rules = WorldRules::LegacyDemoV1);
    ~World();
    // New instances only; legacy is nullopt. Configuring cancels transients at
    // this explicit boundary rather than charging/replaying a current action.
    void configureAnimationClock(std::optional<ani_clock::ClockPolicy>);
    std::optional<ani_clock::ClockPolicy> animationClockPolicy() const { return animationClockPolicy_; }
    Json animationClockReport() const;
    // Same explicit presentation strategy supplied to Renderer at startup.
    // Published projectiles retain their spawn receipt and must retire before
    // switching profile; source cache entries remain independently keyed.
    void configureRenderProfile(ani_render::RenderProfile);
    ani_render::RenderProfile renderProfile() const { return renderProfile_; }
    void configureBasicAttackMovement(bool enabled);
    Json basicAttackMovementReport() const { return basicMovementPolicy_.json(); }
    // Main supplies the fingerprinted static manifest identity. Core logic
    // never derives a content identity from an absolute resource directory.
    void configureSourceActions(std::string staticIdentity, bool speechPresentation = false);
    void configureSquirrelActions(std::string staticIdentity);
    std::unique_ptr<PreparedExperimentalSkillAction> prepareSquirrelAction(const ExperimentalSkillActionRequest &);
    void observeSquirrelAction(std::optional<uint64_t>) noexcept;
    void cancelSquirrelActions(const std::string &) noexcept;
    Json squirrelActionDiagnostics() const;
    ActWorldHost *actHost() { return actHost_.get(); }
    const ActWorldHost *actHost() const { return actHost_.get(); }
    void requestSourceMonsterAction(EntityHandle, std::string state, int index = 0);
    Json sourceActionDiagnostics() const { return actServiceDiagnostics_; }
    void configureMonsterActionAi(std::string difficulty);
    Json monsterActionAiState() const;
    void validateMonsterActionAiCheckpoint(const Json &) const;
    Json sourceMonsterCooldownCheckpoint(EntityHandle) const;
    std::map<int,int64_t> prepareSourceMonsterCooldownRestore(const Actor &,const Json &,int64_t) const;
    std::optional<MonsterSourceMovement> prepareSourceMonsterMovementRestore(const Actor &,const Json &) const;
    // Explicit authored difficulty and inference policy. Installation performs
    // source/grammar preflight only; real accepted damage creates hit records.
    bool configureMonsterEventAi(EntityHandle,std::string difficulty,const MonsterEventAiPolicy &);
    Json monsterEventAiState() const;
    Json monsterEventActorCheckpoint(EntityHandle,uint64_t generation=1) const;
    void validateMonsterEventActorCheckpoint(const Actor &,const Json &,uint64_t nowMs,uint64_t expectedGeneration) const;
    void refreshExplorationMonsterEventAiTestPolicy();
    Json monsterEventAiTestPolicy() const;
    void enqueue(Input in);
    void advance(int64_t ns, size_t maxTicks = std::numeric_limits<size_t>::max());
    // One fixed tick while the application's world pause is active. Existing
    // catch-up debt is retained; no wall-clock time is submitted by the UI.
    void advanceSingleTick();
    uint64_t pendingTicks() const { return clock_.pendingTicks(); }
    // Called once after every fixed simulation tick, including catch-up ticks.
    // The application owns Scene; World never stores a platform renderer.
    void setObjectTick(std::function<void(World &)> tick) { objectTick_ = std::move(tick); }
    void setBeforeTick(std::function<void(World &)> tick) { beforeTick_ = std::move(tick); }
    double alpha() const { return clock_.alpha(); }
    int64_t nowMs() const;
    // Total elapsed time submitted to this simulation, including preserved
    // catch-up backlog and fractional tick time. SDL timestamps use this base
    // after resume; using only the completed tick would backdate new input.
    int64_t simulationNanoseconds() const;
    Json simulationCheckpoint() const;
    // Character selection consumes one identity before the saved simulation
    // is applied. Check both allocations against the live non-rewindable
    // entity watermark before cancelling any live character state.
    void validateCharacterRestoreCapacity(const Json &simulation = Json()) const;
    // Private allocator dry run: one new player and count new room actors.
    // Call before persisting/leaving the old scene, then changeScene/publish.
    void validateSceneActorCapacity(size_t count) const;
    // Install once after publishing prepared actors/geometry and synchronizing
    // handles. Expected content failures become per-actor diagnostics. No save,
    // reward, task or whole-map capability is granted by this test service.
    void setMapExplorationPolicy(bool geometryAvailable);
    bool mapExplorationActive() const { return mapExplorationActive_; }
    Json mapExplorationPolicy() const;
    void restoreSimulationCheckpoint(const Json &checkpoint);
    void synchronizeEntityHandles();
    Actor *resolveActor(EntityHandle handle);
    const Actor *resolveActor(EntityHandle handle) const;
    RandomStreams &randomStreams() { return random_; }
    const RandomStreams &randomStreams() const { return random_; }
    bool statusStunned(EntityHandle target) const { return statuses_.controlled(target,uint64_t(nowMs())); }
    Json statusEffects(EntityHandle target) const { return statuses_.activeEffects(target,uint64_t(nowMs())); }
    Json statusCheckpoint(EntityHandle target,uint64_t generation = 1) const;
    void restoreStatusCheckpoint(const Json &,EntityHandle oldTarget,EntityHandle newTarget,uint64_t generation);
    void clearRestoredPlayerStatus();
    void validateStatusCheckpoint(const Json &,EntityHandle oldTarget,uint64_t generation,
        uint64_t restoreMs = UINT64_MAX) const;
    void restoreRoomActors(std::vector<Actor> actors,const Json &savedActors);
    SimulationIdSources &idSources() { return ids_; }
    void activate(int index, bool command = false);
    const SkillCostResult &skillCosts(int index, bool command = false) const;
    void reset();
    void changeScene();
    // Reconstructed host policy: only explicit live action interruption
    // may preserve experimental physical movement. Defaults and lifecycle
    // boundaries still perform the existing full experimental reset.
    void idle(bool preserveExperimentalMovement = false);
    void normalAttack();
    // The caller prechecks a claim, then consumes X only if this source action
    // is accepted. Claim failure can cancel it explicitly without an attack.
    bool tryPickupAction();
    bool pickupActionActive() const { return pickupAction_.has_value(); }
    void cancelPickupAction() { if(pickupAction_)idle(); }
    const Json &pickupActionTrace() const { return lastPickupActionTrace_; }
    // Isolated --combat-effects-fixture entry. Never used by normal gameplay.
    void diagnosticHit(int targetId, int value, int responseSkill, int phase,
                       int direction, const ImpactContext &impact);
    void restoreMonsterVisuals(Actor &actor);
    // Creation only, before publication to monsters/entity handles. Failed
    // source evaluation leaves the supplied actor untouched. Restores use saved
    // HP and sourceStats instead, including historical legacy sessions.
    // Optional frozen policy belongs to the run. An old legacy run may enter a
    // previously unvisited room under a beta World without adopting source HP.
    void initializeMonsterAttributes(Actor &actor, int resolvedLevel, const std::string &frozenPolicy = {},
        const std::string &combatPolicy = "inferred-mob-combat-table-v1");
    void restoreMonsterAttributes(Actor &actor);
    // Read-only source preflight; routine absent/unsupported content returns
    // precise diagnostics without publishing effects, IDs, RNG or actor state.
    MonsterProjectileDefinition prepareMonsterProjectile(const Actor &actor) const;
    DamageResolution resolveObjectContact(const AttackVolume &attack, const ObjectInstance &object);
    bool canWalk(double x, double y) const;
    std::array<double, 2> nearestWalkable(double x, double y) const;
    void recoverPosition(Actor &actor);
    void resetBindings();
    void createController();
    // Explicit application opt-in. Does not change currentCandidate defaults
    // or count these unfinished source experiments as reconstructed beta.
    void enableExperimentalCharacters();
    const CharacterAdvancementCatalog &advancementCatalog() const;
    std::unique_ptr<PreparedCharacterAdvancement> prepareCharacterAdvancement(CharacterIdentity, const Progression &);
    void publishCharacterAdvancement(PreparedCharacterAdvancement &);
    bool isExperimentalCharacter() const;
    ExperimentalCharacterRuntime *experimentalRuntime();
    const ExperimentalCharacterRuntime *experimentalRuntime() const;
    ExperimentalSkillConfiguration prepareExperimentalSkillConfiguration(CharacterIdentity, const Json &) const;
    const std::vector<Skill> &compatibilitySkillView(CharacterIdentity, bool passive = false) const;
    Json experimentalDiagnostics() const;
    Json femaleGunnerDiagnostics() const;
    std::map<SkillKey,int64_t> prepareExperimentalCooldownRestore(CharacterIdentity,const Json &,int64_t restoredNowMs) const;
    void releaseInputs();
    CharacterIdentity identity() const { return identity_; }
    CharacterSkillState &skillState() { return skillState_; }
    const CharacterSkillState &skillState() const { return skillState_; }
    const SkillLearningService &skillLearning() const;
    bool hasLearningLedger() const;
    RuntimeSkillPolicy runtimeSkillPolicy(SkillKey key) const;
    void publishSkillLedger(CharacterSkillState state);
    std::vector<SkillKey> learningSkillKeys() const;
    Json skillLearningConsumerMetadata(SkillKey) const;
    SkillLearningBudget skillLearningBudget(bool testLearning, int normalLevel) const;
    SkillLearningBatch quoteSkillLearningBatch(bool testLearning, int normalLevel) const;
    std::unique_ptr<PreparedSkillRuntime> prepareSkillRuntime(CharacterSkillState,
        SkillLearningTestOverlay, SkillRuntimeProjectionContext) const;
    std::unique_ptr<PreparedSkillRuntime> prepareSkillLedger(CharacterSkillState) const;
    void publishPreparedSkillRuntime(PreparedSkillRuntime &);
    Operation assignLearnedSkillSlot(size_t, std::optional<SkillKey>);
    bool experimentalSkillPreviewEnabled() const { return experimentalSkillPreviewEnabled_; }
    uint64_t skillRuntimeProjectionRevision() const noexcept { return skillProjectionRevision_; }
    bool skillLearningProjectionReady() const noexcept;
    Operation setExperimentalSkillPreviewEnabled(bool);
    Json normalSkillConfigurationSnapshot() const;
    Json testSkillConfigurationSnapshot() const;
    Json manualSkillPreviewSnapshot() const;
    std::map<SkillKey,int> effectiveFemaleGunnerLevels() const;
    SkillLearningQuote quoteSkillLearning(SkillKey key, int normalLevel) const;
    SkillLearningQuote quoteTestSkillLearning(SkillKey key) const;
    Operation learnTestSkill(const SkillLearningRequest &request);
    void resetTestSkillLearning();
    const SkillLearningTestOverlay &skillTestOverlay() const { return skillTestOverlay_; }
    void restoreSkillTestOverlay(SkillLearningTestOverlay overlay);
    SkillLearningUseEligibility skillUseEligibility(SkillKey key) const;
    Skill effectivePassive(const Skill &skill) const;
    // Source availability is not permission to instantiate an unimplemented
    // controller. Reject before touching the current character's live state.
    bool supportsCharacter(CharacterIdentity identity) const { return controllers_.supports(identity); }
    Json controllerCoverage() const { return controllers_.snapshot(); }
    void selectCharacter(CharacterIdentity identity);
    void selectCharacter(CharacterIdentity, std::unique_ptr<ExperimentalCharacterRuntime>);
    std::unique_ptr<ExperimentalCharacterRuntime> prepareExperimentalRuntime(CharacterIdentity, const Json &) const;
    int activeSkill() const { return active_; }
    int stage() const { return stage_; }
    bool armor() const;
    bool invincible() const;
    int remainingCd(int index) const;
    // Only the existing Swordman controller is playable. Other definitions
    // remain source models until their native controllers are restored.
    const CharacterDefinition &characterSource() const { return characters_.at(identity_.jobId); }
    const CharacterCatalog &characterCatalog() const { return characters_; }
    const CharacterAppearance &characterAppearance() const;
    // Resource loading can fail. Prepare on private progression state before
    // a character restore cancels the currently active controller.
    CharacterAppearance prepareEquipmentAppearance(const Progression &progression, CharacterIdentity identity) const;
    bool usesSourceGrowth() const { return rules_ == WorldRules::BetaFoundationV1; }
    CharacterBaseAttributes prepareBaseAttributes(CharacterIdentity identity, int level) const;
    void applyBaseAttributes(CharacterBaseAttributes attributes, AttributeRebuildReason reason);
    CharacterSpeeds prepareCharacterSpeeds(const CharacterBaseAttributes &attributes, const Progression &progression) const;
    void applyCharacterSpeeds(CharacterSpeeds speeds);
    EquipmentResourceAttributes prepareEquipmentResources(const CharacterBaseAttributes &base, const Progression &progression) const;
    void applyEquipmentResources(EquipmentResourceAttributes attributes, AttributeRebuildReason reason);
    CombatAttributeSnapshot prepareCombatAttributes(const CharacterBaseAttributes &base, const Progression &progression) const;
    void applyCombatAttributes(CombatAttributeSnapshot attributes);
    const std::optional<CombatAttributeSnapshot> &combatAttributes() const { return combatAttributes_; }
    void applyDebugOverrides(const DebugOverrides &overrides, int normalLevel);
    const DebugOverrides &debugOverrides() const { return debugOverrides_; }
    void setCharacterAppearance(CharacterAppearance appearance);
    void applyEquipment(const Progression &progression);
    // Prepare inventory, source attributes/speeds and appearance together;
    // rejected changes preserve live progression and combat state.
    Operation changeEquipment(Progression &progression, int inventoryIndex, bool unequip = false);
    void useDiagnosticAppearance() { equippedAppearance_.reset(); skillCostCache_.clear(); }
    std::string actorAni() const;
    Json inputs() const { return inputLog_; }
    Json skillInputDiagnostics() const;
    bool hasBufferedDefaultSkill() const noexcept { return bool(bufferedDefaultSkill_); }
    void clearSkillInputTransients() noexcept;
    Json snapshot() const;
    Json eventLog() const;
    Json statReport() const;
  private:
    bool monsterActionAiEnabled_ = false;
    std::string monsterActionAiDifficulty_;
    std::map<std::string,MonsterActionAiBinding> monsterActionAiSources_;
    Json monsterActionAiDiagnostics_ = Json::array();
    void prepareMonsterActionAiBoundary();
    std::optional<SourceActionRequest> prepareMonsterActionAiDecision(EntityHandle);
    Json monsterActionAiCheckpoint() const;
    MonsterActionAiRestore prepareMonsterActionAiRestore(const Json &) const;
    void publishMonsterActionAiRestore(MonsterActionAiRestore &&) noexcept;

};
} // namespace dnf
