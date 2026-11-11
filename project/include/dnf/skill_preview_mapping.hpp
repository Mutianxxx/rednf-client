#pragma once
#include "character.hpp"
#include "resources.hpp"
#include "skill_data.hpp"
#include <map>
#include <set>
#include <string>
#include <vector>

namespace dnf {
class Assets;

// Evidence boundary for one skills-table row.
//
// 1031's .skl never names an animation, so "which ANI plays this skill" is not
// data the client publishes. Every mapping therefore carries the rule that
// produced it, and a row with no rule stays empty instead of borrowing a
// similarly named file. That is the difference between a viewer and a guess.
enum class MappingConfidence {
    None,        // no rule matched; body/effects intentionally empty
    AutoExact,   // CHR motion slot stem equals the SKL file stem
    AutoPrefix,  // slot stem is the skill stem plus a numeric/word suffix
    AutoEffect,  // only effect ANIs matched, no body motion
    // Exact file stem inside character/<job>/animation/. The CHR slot table does
    // not register every skill motion, but the job's own animation directory
    // still names it after the SKL file. Rule-based, not slot-based.
    AutoDirectory,
    // Stages named after the skill, ordered by release stage (windup -> strike
    // -> recovery). More than one entry means the action is a chain; the order
    // comes from the stage vocabulary, which no client file publishes.
    AutoChain,
    Manual,      // registered by hand with a cited source line
    Reconstructed // geometry rebuilt from a cited constant, not from source data
};

// Where the attack volume comes from. 40JP reads it straight out of the .ani
// frame; 1031 sometimes has no box at all, in which case the viewer marks the
// volume as reconstructed rather than presenting a guess as source data.
enum class AttackBoxSource { None, AniBody, AniWeapon, Reconstructed40Jp };

// A = body + effects + a real attack volume. B = body only (or no volume).
// C = effects only. D = nothing playable.
enum class SkillGrade { A = 0, B = 1, C = 2, D = 3 };

// One animated effect layer with the instant it appears on the action clock.
// The instant is source data when the parent ANI carries an .als sidecar:
// the base-client native evidence (rep-player-1031-pvf/docs/native-evidence/
// animation-render.json:176-178,328-337) confirms [add] is a parent FRAME
// INDEX. The mapping compiles it, plus the matching [remove], into absolute
// action-clock ms from the nominal sum of preceding [DELAY]s, so consumers
// that cannot visit frames (the native world) still honour the source order.
// This is a NOMINAL boundary: the 1031 ratePercent scaling and the
// delayed-add net birth-offset policy are unrecovered (:36, :130, :518), so
// no runtime-clock equivalence is claimed. Layers without a sidecar use the
// release-stage word in the file stem and the row says so.
struct EffectLayerPlan {
    std::string path;
    int stage = 0;             // stageOrder() of the file stem; higher = later
    // Where the layer starts, as a fraction of the action duration. Only used
    // for reconstructed (stem-order) timing; ALS layers use birthMs instead.
    double birthRatio = 0.0;
    // Absolute ms on the action clock. birthMs >= 0 means source ALS timing;
    // -1 means the consumer should fall back to birthRatio * actionDuration.
    // endMs is the matching [remove]; -1 means no source end, so the layer
    // lives for its own animation duration (or until the action ends if LOOP).
    double birthMs = -1.0, endMs = -1.0;
    int bodyStage = 0;         // index into bodyChain whose .als declared it
    // True when birthMs came from a same-stem body-stage binding rather than
    // an ALS [add]. Both are reconstructions of the nominal action clock; only
    // `timed` claims a recovered source command.
    bool stageBound = false;
    double lifeMs = 0.0;
    bool loop = false;
    bool timed = false;        // true = the ALS sidecar supplies the instant
    int alsFrame = -1;
    int alsLayer = 0;
    // ALS draw-only objects carry an explicit source XYZ; plain [add] commands
    // attach at the parent origin, so both stay zero there.
    double offsetX = 0, offsetY = 0, offsetZ = 0;
    std::string instance;      // ALS uniqueName, empty for a stem-matched layer
    std::string source;        // "als" / "family" / "object" / "prefix" / "script"
    std::string evidence;
    // Passive-object layers carry their own type-15 attack boxes. The source
    // body ANI holds only type-14 hurt boxes, so an effect that is skipped as
    // "visual only" also loses the hit. attackInfo is the object's
    // [attack info] .atk path (damage reaction, not the box).
    bool attack = false;
    std::string attackInfo;
};

// One slot of a release chain. A chain is a STATE MACHINE, not one tape:
// 1031's exe setState tables name the entry motion of each state, while the
// CHR motion pool holds the sub-motions a state plays on player input. Some
// states are input waits -- guard.ani is two frames at 10000ms each, so its
// duration is a hold sentinel, not 20 seconds of animation. Such stages are
// kept as external slots and do not advance the automatic action clock; their
// real length is driven by input and is deliberately left unquantified here.
enum class ChainSlotRole { Entry, Triggered, Finish, Plain, ExternalHold };
struct ChainSlot {
    std::string path;
    ChainSlotRole role = ChainSlotRole::Plain;
    double startMs = 0;       // action-clock start; -1 for an external slot
    double durationMs = 0;    // sum of the source ANI [DELAY] table
    int frameCount = 0;
    std::string evidence;
};

// A skill entity that outlives the cast: the nen orbs orbiting the fighter, the
// lotus flowers planted on the ground, the swords hanging in the air. The client
// creates these from a passive object the caster's state handler spawns, so the
// animation lives in passiveobject/ but the position/rotation does not exist in
// any file. Kind and count come from the object's motion table; the motion
// itself (orbit radius, spin) is reconstructed and labelled as such.
enum class PersistentKind { Orbit, GroundField, AirSword };
struct PersistentPlan {
    std::string path;        // animation played by the entity
    std::string object;      // passiveobject .obj it belongs to
    PersistentKind kind = PersistentKind::GroundField;
    int count = 1;
    double radius = 0;             // orbit radius in source pixels
    double angularDegPerSec = 0;   // orbit spin, positive = clockwise on screen
    double phaseDeg = 0;           // first instance's start angle
    double offsetX = 0, offsetY = 0; // anchor relative to the caster's feet
    double lifeMs = 0;             // 0 = stays until the skill ends
    bool loop = true;
    std::string evidence;
};

// Exe-sourced judgment (attack launch) evidence. A skill's setState handler in
// the 1031 exe calls the ATK selector thunk 0x70213F; its first immediate is the
// attack index into the skill's .atk resource. This is the exe -> PVF dispatch
// link: it proves *which* attack volume a state launches and *when* (call-site
// address). The .atk geometry is still read from PVF. Provenance is the static
// scan in tools/skill-bindings/evidence/judgment-events.json; the selector sits
// in a Themida VM region so the immediate is recorded but not yet name-mapped.
struct ExeJudgment {
    int state = 0;
    int atkIndex = -1;            // -1 = selector called with no immediate
    std::string at;               // call-site address, e.g. 0x00ccf619
    bool sharedHandler = false;   // handler also serves other skills; runtime
                                  // skill_id (vtable +0x804) picks the concrete .atk
    std::string evidence;
};

// The skill's input command (操作指令), e.g. "↑↑↓↓ + Z". Source is the .skl
// [command] / [command key explain] block in 1031 Script.pvf. That is PVF data
// the exe input dispatcher parses to register the key listener; the exe-side
// parser is not yet decoded, so this is labelled source data, not exe runtime.
struct SkillCommand {
    std::string tokens;    // rendered token list, e.g. "↑↑↓↓ + Z"
    std::string explain;   // [command key explain] verbatim (Chinese)
    std::string evidence;
};


struct SkillVisualMapping {
    SkillKey key{};
    std::string skillPath, name;
    std::string bodyAni;      // full PVF path, empty when unresolved
    std::string bodySlotTag;  // CHR slot that supplied bodyAni
    // Stand-in pose drawn when the skill has no motion of its own (the CHR's
    // generic buff pose). It is never bodyAni: the grade still reports the row
    // as body-less, the viewport just is not empty.
    std::string fallbackPose;
    // Every stage of the release, in order, when the client names more than one
    // (multiheadshotready -> multiheadshotshoot1..4 -> multiheadshotfinish).
    // Empty when only a single motion exists; bodyAni then is that motion.
    std::vector<std::string> bodyChain;
    std::vector<int> chainStages;   // parallel to bodyChain: the stage order
    std::string chainEvidence;      // human-readable "a -> b -> c"
    // Playback slots of the normalised chain (input-wait stages removed), and
    // the state-machine waits the automatic clock cannot time. Both the
    // previewer and the native world read these, so they cannot disagree on
    // which action clock a layer's birthMs belongs to.
    std::vector<ChainSlot> chainSlots;
    std::vector<ChainSlot> externalSlots;
    double nominalActionMs = 0;   // sum of playback slot [DELAY]s; no input waits
    std::vector<std::string> effects;
    std::vector<std::string> particles;
    // effects, with the attach instant and the order they should be drawn in.
    // Same paths as `effects`, so a consumer can use either.
    std::vector<EffectLayerPlan> effectLayers;
    // Entities that persist after the cast (nen orb, lotus field, air swords).
    std::vector<PersistentPlan> persistents;
    AttackBoxSource attackSource = AttackBoxSource::None;
    bool hasAttackBox = false;
    // Volumes rebuilt from a cited constant rather than read out of the .ani.
    // Frames are [first,last] into the body animation; an empty range means the
    // volume applies to every frame.
    std::vector<Box> reconstructedBoxes;
    std::vector<std::pair<size_t, size_t>> reconstructedFrames;
    int hitStopMs = 0; // 0 = not recovered from source; never invented
    // Exe-sourced attack-launch evidence per state (judgment-events.json), joined
    // by skill stem. Empty when the skill's handler made no ATK-selector call.
    std::vector<ExeJudgment> exeJudgments;
    // Input command from the .skl [command] block; empty when the skill has none.
    SkillCommand command;
    bool passive = false;
    SkillGrade grade = SkillGrade::D;
    MappingConfidence confidence = MappingConfidence::None;
    std::string iconPath;
    int iconFrame = -1;
    std::string evidence; // why this mapping exists
    std::string missing;  // what a D/C row lacks, in words
    Json audit() const;
};

// One list row. Kept small so 1734 of them stay cheap to hold and draw.
struct SkillRow {
    SkillKey key{};
    std::string name;
    std::string skillPath;
    std::string iconPath;
    int iconFrame = -1;
    SkillGrade grade = SkillGrade::D;
    std::string missing;
};

struct SkillJobInfo {
    int jobId = -1;
    std::string name;
    std::string chrPath;
    int skillCount = 0;
    int gradeA = 0, gradeB = 0, gradeC = 0, gradeD = 0;
};

class SkillMappingTable {
  public:
    SkillMappingTable(Pvf &, Assets &, CharacterCatalog &);
    // Lazy: only the selected job is resolved. Called again on job switch.
    void ensureJob(int jobId);
    const std::vector<SkillRow> &rows(int jobId) const;
    const std::vector<SkillJobInfo> &jobs() const; // resolved lazily after ensureJob
    const SkillVisualMapping *mapping(const SkillKey &) const;
    int gradeCount(int jobId, SkillGrade) const;
    Json auditJson(const std::vector<int> &jobIds) const;
    // Attack-volume probe for one ANI, cached per path.
    bool animationHasAttackBox(const std::string &path);

  private:
    // Per-job index: built once, reused by every skill of that job.
    struct JobIndex {
        std::string directory;                                         // character/swordman
        std::string chrStem;                                           // swordman / atmage
        std::string baseJob;                                           // character/<baseJob>/ is the
                                                                       // root of effect literals
        std::map<std::string, std::vector<CharacterResource>> motions;  // stem -> slots
        // Named CHR motion slots that are not part of the release animation
        // library: [buff motion], [back motion], [jump motion], ... Skills such
        // as BackStep or JumpPowerUp *are* one of these slots under a skill name,
        // and buff skills borrow the generic cast pose because the client never
        // gives them a dedicated motion.
        std::map<std::string, std::string> baseMotions;                 // "[buff motion]" -> path
        std::map<std::string, std::string> animation;                   // stem -> animation/<stem>.ani
        // skill stem -> every per-skill script under sqr/character/<chrStem>/.
        // Those scripts (checkExecutableSkill / onSetState) create the visuals
        // that common.nut does not declare for non-swordman jobs.
        std::map<std::string, std::vector<std::string>> skillScripts;
        // sq_SetCurrentAnimation(CUSTOM_ANI_X) is how the scripts pick a body
        // motion: the header defines the constant, the CHR [etc motion] list
        // resolves the index. Both tables are per job.
        std::map<std::string, int> customAnimations;                    // CUSTOM_ANI_X -> index
        std::vector<std::string> etcMotions;                            // index -> .ani
        std::vector<std::string> effectPaths;                           // effect/animation/*.ani
        std::vector<std::string> particlePaths;                         // particle/*.ptl
        // Effect families: a directory under effect/animation (or under the
        // passive-object animation tree) named after the skill. 1031 puts the
        // whole visual in there — aticesword/01_light_dodge.ani, nenshield/
        // bloom1.ani, atlightningdragon/exp_0_dodge.ani — and the file stems
        // never repeat the skill name, so a stem-prefix scan found nothing.
        std::map<std::string, std::vector<std::string>> effectFamilies;  // family -> .ani list
        // Skill entities: passiveobject/character/<chrStem>/<skill>.obj. The
        // object's [etc motion] list is the on-screen body of the skill — the
        // summoned ghost, the ice field, the falling tombstones. Those motions
        // live under passiveobject/, not under the CHR's own animation folder,
        // so name matching against character/<job>/animation never found them.
        std::map<std::string, std::string> passiveObjects;              // stem -> .obj path
        std::vector<std::string> passiveAnimations;                     // passiveobject/.../animation/*.ani
    };
    const SkillVisualMapping &resolve(int jobId, const CharacterRegistration &);
    const JobIndex &index(int jobId);
    std::string jobDirectory(int jobId) const;
    // Lazily loads tools/skill-bindings/evidence/{judgment-events,skill-commands}.json
    // and folds them into a resolved mapping by skill stem. Guarded: a missing
    // file simply leaves the fields empty; it never fails resolution.
    void loadEvidence();
    void applyEvidence(SkillVisualMapping &) const;

    Pvf &pvf_;
    Assets &assets_;
    CharacterCatalog &catalog_;
    std::map<int, JobIndex> indices_;
    std::map<SkillKey, SkillVisualMapping> mappings_;
    std::map<int, std::vector<SkillRow>> rows_;
    mutable std::vector<SkillJobInfo> jobs_;
    std::map<std::string, bool> attackBoxCache_;
    bool evidenceLoaded_ = false;
    std::map<std::string, SkillCommand> commandByStem_;
    std::map<std::string, std::vector<ExeJudgment>> judgmentByStem_;
};
} // namespace dnf
