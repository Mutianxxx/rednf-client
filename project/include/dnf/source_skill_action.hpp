#pragma once
#include "content_profile.hpp"
#include "damage_resolution.hpp"
#include "skill_data.hpp"
#include "female_gunner_skill_layers.hpp"
#include "source_body_sidestep.hpp"
#include <set>

namespace dnf {
// A deliberately bounded source-semantic adapter, not a general NUT VM.
// Numeric job/skill/state/CHR slots/PO IDs/offsets/columns come from this
// session's source bytes. Only a reviewed callback program is admitted.
enum class SourceSkillActionKind { FlaggedPassiveObject, BodyAttack, MovingImpactObject };
// Native controller entry data is separate from immutable 1031 ANI/ATK data.
// A shared executor owns stages, hit ledgers and conditional grab transitions.
struct SourceNativeStage {
    std::string motionTag="[etc motion]", attackTag="[etc attack info]";
    int motionSlot=-1, attackSlot=-1;
    int controllerSubstate=-1, controllerStyle=-1;
    SourceRef motion, attack;
    int percentColumn=-1, independentColumn=-1;
    int repeat=1, repeatColumn=-1, repeatStatic=-1;
    // Only classified controller-held poses are overridden. Raw ANI survives.
    std::vector<int32_t> runtimeDelays;
    std::vector<FemaleGunnerSkillLayer> layers;
    std::vector<SourceSkillVisualCue> contactEffects;
    std::string sound;
    bool suppressBodyDamage=false;
    int movementStartMs=-1, speedStatic=-1, accelerationStatic=-1;
    double speed=0, acceleration=0;
    Json snapshot() const;
};
struct SourceNativeGrab {
    size_t tryStage=0, releaseStage=1;
    std::array<double,3> holdOffset{35,0,45};
    // Native held-target callback, distinct from ANI type15 collision.
    // A nonnegative source frame fires once on the release stage.
    int directHitFrame=-1;
};
struct SourceNativeProjectile {
    int birthFrame=0, speedColumn=-1, rangeStatic=-1;
    double speed=0, range=0;
    bool loop=false;
};
struct SourceMovingImpactAction {
    SourceRef impactCallback, impactObject, impactAnimation, impactAttack;
    std::shared_ptr<const Animation> impactClip;
    AttackDamageDefinition impactAttackDefinition;
    int impactObjectId=-1, sizeColumn=-1, speedStatic=-1, distanceStatic=-1;
    std::array<int,4> recoilStatics{};
    int travelTimeNumerator=0, impactSizeSubtract=0;
    bool anySourceFlag=false;
    std::array<double,3> impactOffset{};
    const char *visualPolicy="inferred-current1031-watercannon-tree-v1";
    Json snapshot() const;
};
// Transient presentation only. NUT gives intensity and duration; mapping the
// intensity to horizontal pixels and 20ms square-wave phases is inferred.
struct SourceSkillCameraFeedback {
    int64_t startedMs=-1;
    int amplitude=0, durationMs=0;
    uint64_t ownerAction=0;
    double offsetX(int64_t ms) const {
        if(startedMs<0||ms<startedMs||uint64_t(ms)-uint64_t(startedMs)>=uint64_t(durationMs))return 0;
        return ((uint64_t(ms)-uint64_t(startedMs))/20)%2?-amplitude:amplitude;
    }
};
struct SourceSkillAction {
    SourceSkillActionKind kind=SourceSkillActionKind::FlaggedPassiveObject;
    int attackSlot=-1, shakeAmplitude=0, shakeDurationMs=0;
    // Native-body source reconstruction: no callback program is invented.
    // Defaults preserve existing reviewed NUT descriptors and snapshots.
    bool inferredNativeBody=false;
    bool native40Jp=false;
    std::string nativeFamily;
    std::vector<SourceNativeStage> nativeStages;
    std::optional<SourceNativeGrab> nativeGrab;
    std::optional<SourceNativeProjectile> nativeProjectile;
    int independentColumn=-1, speedColumn=-1, recoveryColumn=-1, recoveryMs=0;
    // Source level-property UI scales differ per reviewed body controller.
    // LowKick uses percent; Mage Thrust uses tenths of a percent.
    double speedToPermille=10;
    // Explicit absent SKL speed-column contract. Only this reviewed adapter
    // uses real actor/equipment speed with zero per-skill bonus.
    bool actorAttackSpeedOnly=false;
    // Negative preserves historical action-start layers. Nonnegative is the
    // first actual default EQU/LAY attack frame; current equipment preflights
    // the same birth boundary. Instance clocks never mutate source ANI.
    int bodyLayerBirthFrame=-1;
    bool requiresEquippedAttackVolume=false;
    // Optional reviewed body policy. Not a global ANI damage-type enum.
    bool sourceFrameSuperArmor=false;
    std::optional<SourceBodySidestepPolicy> bodySidestep;
    const char *controllerKey() const {
        return inferredNativeBody?"source_body_action_controller":"source_nut_action_controller";
    }
    std::optional<SourceMovingImpactAction> movingImpact;
    std::string castSound;
    // Optional reviewed body cue at the first source body type15 frame. The
    // adapter preflights it with castSound before accepting the action cost.
    std::string attackSound;
    SourceRef layersSource;
    std::vector<FemaleGunnerSkillLayer> bodyLayers;
    SkillKey key;
    SourceRef registration, header, callback, passiveCallback;
    SourceRef skill, motion, objectRegistry, object, animation, attack;
    int state = -1, motionSlot = -1, objectId = -1;
    int standState = -1, dashState = -1, attackState = -1, jumpState = -1;
    std::set<int> executableStates;
    int percentColumn = -1, fixedColumn = -1, liftColumn = -1;
    uint16_t flag = 0xffff;
    std::array<double,3> offset{};
    std::shared_ptr<const Animation> objectAnimation;
    AttackDamageDefinition attackDefinition;
    Json evidence = Json::object();
    Json snapshot() const;
};
struct SourceMovingImpactOperands {
    int sizePercent=0, speed=0, distance=0, travelMs=0;
    int recoilVelocity=0,recoilAcceleration=0,alternateRecoilVelocity=0,alternateRecoilAcceleration=0;
};
struct SourceSkillOperands {
    std::optional<SourceMovingImpactOperands> movingImpact;
    DamageSkillModifiers damage;
    double lift = 0, attackSpeedBonusPermille = 0;
    int recoveryMs = 0;
    std::optional<double> bodyLift; // unset preserves existing ATK response
    Json evidence = Json::object();
};
std::map<SkillKey,SourceSkillAction> loadSourceSkillActions(Pvf &, Assets &, const CharacterCatalog &, CharacterIdentity, Json &diagnostics);
void appendSourceMageUpperAction(Pvf &,Assets &,const CharacterCatalog &,CharacterIdentity,std::map<SkillKey,SourceSkillAction> &,Json &);
void appendSourceWaterCannonAction(Pvf &,Assets &,const CharacterCatalog &,CharacterIdentity,std::map<SkillKey,SourceSkillAction> &,Json &);
SourceSkillOperands evaluateSourceSkillAction(const SourceSkillAction &, const SkillSourceData &, int level);
// Exact reviewed source relationship only; this does not grant learning,
// ownership or cancellation. Each call rebuilds from the immutable base row.
SourceSkillOperands evaluateSourceSkillActionTp(const SourceSkillAction &, const SkillSourceData &base, int baseLevel,
    SkillKey passive, const SourceRef &passiveSource, const SkillSourceData &tp, int tpLevel);
} // namespace dnf
