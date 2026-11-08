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

struct SkillVisualMapping {
    SkillKey key{};
    std::string skillPath, name;
    std::string bodyAni;      // full PVF path, empty when unresolved
    std::string bodySlotTag;  // CHR slot that supplied bodyAni
    // Every stage of the release, in order, when the client names more than one
    // (multiheadshotready -> multiheadshotshoot1..4 -> multiheadshotfinish).
    // Empty when only a single motion exists; bodyAni then is that motion.
    std::vector<std::string> bodyChain;
    std::vector<int> chainStages;   // parallel to bodyChain: the stage order
    std::string chainEvidence;      // human-readable "a -> b -> c"
    std::vector<std::string> effects;
    std::vector<std::string> particles;
    AttackBoxSource attackSource = AttackBoxSource::None;
    bool hasAttackBox = false;
    // Volumes rebuilt from a cited constant rather than read out of the .ani.
    // Frames are [first,last] into the body animation; an empty range means the
    // volume applies to every frame.
    std::vector<Box> reconstructedBoxes;
    std::vector<std::pair<size_t, size_t>> reconstructedFrames;
    int hitStopMs = 0; // 0 = not recovered from source; never invented
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
        std::map<std::string, std::vector<CharacterResource>> motions;  // stem -> slots
        std::map<std::string, std::string> animation;                   // stem -> animation/<stem>.ani
        std::vector<std::string> effectPaths;                           // effect/animation/*.ani
        std::vector<std::string> particlePaths;                         // particle/*.ptl
    };
    const SkillVisualMapping &resolve(int jobId, const CharacterRegistration &);
    const JobIndex &index(int jobId);
    std::string jobDirectory(int jobId) const;

    Pvf &pvf_;
    Assets &assets_;
    CharacterCatalog &catalog_;
    std::map<int, JobIndex> indices_;
    std::map<SkillKey, SkillVisualMapping> mappings_;
    std::map<int, std::vector<SkillRow>> rows_;
    mutable std::vector<SkillJobInfo> jobs_;
    std::map<std::string, bool> attackBoxCache_;
};
} // namespace dnf
