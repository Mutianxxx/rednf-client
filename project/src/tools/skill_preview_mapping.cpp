#include "dnf/skill_preview_mapping.hpp"
#include "dnf/resources.hpp"
#include "dnf/skill_preview_motion_pool.hpp"
#include "dnf/skill_exe_bindings.hpp"
#include <algorithm>
#include <cstdlib>
#include <filesystem>

namespace dnf {
namespace {
namespace fs = std::filesystem;

std::string stemOf(const std::string &path) {
    return normalize(fs::u8path(path).stem().u8string());
}
std::string parentOf(const std::string &path) {
    return normalize(fs::u8path(path).parent_path().generic_u8string());
}
// A slot stem that is the skill stem plus a numeric tail, e.g. tripleslash1 for
// skill tripleslash. Non-numeric tails are a different animation, not a stage.

// ---------------------------------------------------------------------------
// Release-chain matching.
//
// The client names a skill's motion after the skill, then suffixes the release
// stage: windmill.skl -> windmillstand / windmillroll, headshot.skl ->
// multiheadshotready / multiheadshotshoot1..4. Counting every stem under
// character/swordman/animation (161) and character/gunner/animation (107) gives
// the stage vocabulary actually in use: ready 12, attack 7, shoot 6, finish 5,
// stay 4, slash 4, ex 3, charge 3, move 3, front 3, cast 3, start 2, after 2,
// stand 1, roll 1, end 1. The order below is release order, not alphabetical:
// a windup runs before the strike, and the recovery runs after it.
//
// The order itself is a naming convention, not a field the client publishes —
// no .skl, .sd or .chr stores it — so every chain built here is reported with
// confidence AutoChain and the row says which stages it joined.
// ---------------------------------------------------------------------------
namespace {
struct StageWord {
    const char *word;
    int order;
};
// Larger order = later in the release. 100 is the strike itself.
constexpr StageWord kStageWords[] = {
    {"ready", 10},   {"standby", 12}, {"prepare", 14}, {"prep", 14}, {"wait", 16},
    {"charge", 20},  {"cast", 30},    {"start", 40},   {"begin", 40}, {"appear", 45},
    {"stand", 100},  {"attack", 100}, {"shoot", 100},  {"shot", 100}, {"slash", 100},
    {"strike", 100}, {"swing", 100},  {"hit", 100},    {"stab", 100}, {"kick", 100},
    {"throw", 100},  {"roll", 105},   {"move", 110},   {"stay", 115}, {"loop", 120},
    {"up", 130},     {"down", 130},   {"front", 130},  {"back", 130}, {"left", 130},
    {"right", 130},  {"ex", 140},     {"extract", 145},{"finish", 150},{"end", 155},
    {"after", 160},  {"success", 165},{"fail", 165},   {"cancel", 165},{"disappear", 170},
};
// Variant prefixes: an EX/awakening version of the same skill keeps the base
// stem, so multiheadshot is still headshot's motion, not a different skill.
constexpr const char *kVariantPrefixes[] = {"multi", "ex", "power", "super", "ultimate",
                                            "awaken", "second", "double", "triple", "rapid",
                                            "max",    "advanced"};
} // namespace

// Order of the stage a stem carries, or -1 when the tail is not a stage word.
// The tail may also carry a serial number (multiheadshotshoot4).
int stageOrder(const std::string &tail) {
    if (tail.empty()) return 0; // exact stem
    for (const auto &entry : kStageWords) {
        const std::string word(entry.word);
        if (tail.size() < word.size()) continue;
        if (tail.compare(0, word.size(), word) != 0) continue;
        const std::string rest = tail.substr(word.size());
        if (!std::all_of(rest.begin(), rest.end(),
                         [](char c) { return c >= '0' && c <= '9'; }))
            continue;
        return entry.order + (rest.empty() ? 0 : std::min<int>(9, std::atoi(rest.c_str())));
    }
    return -1;
}

// Does this animation stem name a stage of the given skill? Returns its order.
int chainOrder(const std::string &slotStem, const std::string &skillStem) {
    if (slotStem.size() < skillStem.size()) return -1;
    std::string tail;
    if (slotStem.compare(0, skillStem.size(), skillStem) == 0) {
        tail = slotStem.substr(skillStem.size());
    } else {
        // Variant prefix in front of the skill stem (multi + headshot + shoot1).
        std::string head = slotStem;
        bool stripped = false;
        for (const char *prefix : kVariantPrefixes) {
            const std::string p(prefix);
            if (head.size() > p.size() && head.compare(0, p.size(), p) == 0) {
                head = head.substr(p.size());
                stripped = true;
                break;
            }
        }
        if (!stripped) return -1;
        if (head.size() < skillStem.size()) return -1;
        if (head.compare(0, skillStem.size(), skillStem) != 0) return -1;
        tail = head.substr(skillStem.size());
    }
    if (tail.empty()) return 0;
    if (std::all_of(tail.begin(), tail.end(), [](char c) { return c >= '0' && c <= '9'; }))
        // A bare serial (tripleslash1) carries no stage meaning; treat it as the
        // strike so it stays playable rather than being dropped.
        return 100 + std::min<int>(9, std::atoi(tail.c_str()));
    return stageOrder(tail);
}
const char *gradeName(SkillGrade grade) {
    switch (grade) {
        case SkillGrade::A: return "A";
        case SkillGrade::B: return "B";
        case SkillGrade::C: return "C";
        default: return "D";
    }
}
const char *confidenceName(MappingConfidence value) {
    switch (value) {
        case MappingConfidence::AutoExact: return "auto_exact";
        case MappingConfidence::AutoPrefix: return "auto_prefix";
        case MappingConfidence::AutoEffect: return "auto_effect";
        case MappingConfidence::AutoChain: return "auto_chain";
        case MappingConfidence::AutoDirectory: return "auto_directory";
        case MappingConfidence::Manual: return "manual";
        case MappingConfidence::Reconstructed: return "reconstructed";
        default: return "none";
    }
}
const char *attackName(AttackBoxSource value) {
    switch (value) {
        case AttackBoxSource::AniBody: return "ani_body";
        case AttackBoxSource::AniWeapon: return "ani_weapon";
        case AttackBoxSource::Reconstructed40Jp: return "reconstructed_40jp";
        default: return "none";
    }
}

// Volumes this client has no source ANI box for. Each entry is copied from the
// constant the legacy controller already uses, with the line it came from, so
// the viewer can show geometry without pretending the .ani contained it.
struct ManualVolume {
    int jobId, skillId;
    size_t firstFrame, lastFrame;
    int x, y, z, w, h, d;
    const char *evidence;
};
constexpr ManualVolume kManualVolumes[] = {
    {0, 5, 3, 5, -20, -20, 0, 160, 40, 110, "combat.cpp:1846 native-controller volume"},
    {0, 8, 1, 2, -25, -25, 20, 130, 40, 70, "combat.cpp:1848 native-controller volume stage 1"},
    {0, 17, 2, 3, 13, -13, -11, 88, 26, 167, "combat.cpp:1850 native-controller volume"},
};
} // namespace

Json SkillVisualMapping::audit() const {
    Json value{{"jobId", key.jobId}, {"skillId", key.skillId}, {"name", name},
               {"skillPath", skillPath}, {"bodyAni", bodyAni}, {"bodySlot", bodySlotTag},
               {"effects", effects}, {"particles", particles},
               {"attackSource", attackName(attackSource)}, {"hasAttackBox", hasAttackBox},
               {"reconstructedBoxes", reconstructedBoxes.size()},
               {"bodyChain", bodyChain}, {"chainStages", chainStages},
               {"chainEvidence", chainEvidence},
               {"passive", passive}, {"grade", gradeName(grade)},
               {"confidence", confidenceName(confidence)},
               {"icon", iconPath}, {"iconFrame", iconFrame},
               {"evidence", evidence}, {"missing", missing}};
    return value;
}

SkillMappingTable::SkillMappingTable(Pvf &pvf, Assets &assets, CharacterCatalog &catalog)
    : pvf_(pvf), assets_(assets), catalog_(catalog) {}

std::string SkillMappingTable::jobDirectory(int jobId) const {
    try {
        return parentOf(catalog_.at(jobId).registration.path);
    } catch (const std::exception &) {
        return {};
    }
}

const SkillMappingTable::JobIndex &SkillMappingTable::index(int jobId) {
    if (const auto found = indices_.find(jobId); found != indices_.end()) return found->second;
    JobIndex built;
    // One pass per job: the CHR motion pool and the effect directory are shared
    // by all its skills, so resolving 175 rows costs one index build, not 175.
    built.directory = jobDirectory(jobId);
    try {
        for (const auto &resource : catalog_.at(jobId).resources) {
            const auto tag = normalize(resource.tag);
            if (tag.find("motion") == std::string::npos) continue;
            if (!resource.exists || resource.path.empty()) continue;
            built.motions[stemOf(resource.path)].push_back(resource);
        }
        if (!built.directory.empty()) {
            built.effectPaths = pvf_.paths(built.directory + "/effect/animation/", ".ani");
            built.particlePaths = pvf_.paths(built.directory + "/particle/", ".ptl");
            // The CHR motion table does not register every release animation,
            // but the job's own animation directory is named after the skill.
            // Only files directly inside it are indexed, never subdirectories.
            const auto animationDirectory = built.directory + "/animation";
            for (const auto &path : pvf_.paths(animationDirectory + "/", ".ani"))
                if (parentOf(path) == animationDirectory)
                    built.animation.emplace(stemOf(path), path);
        }
    } catch (const std::exception &) {
        // An unreadable CHR leaves the job with no automatic mapping; every row
        // then reports its own missing reason instead of borrowing a name.
    }
    return indices_.emplace(jobId, std::move(built)).first->second;
}

bool SkillMappingTable::animationHasAttackBox(const std::string &path) {
    if (path.empty()) return false;
    if (const auto found = attackBoxCache_.find(path); found != attackBoxCache_.end())
        return found->second;
    bool has = false;
    try {
        const auto animation = assets_.animation(path);
        for (const auto &frame : animation->frames)
            for (const auto &box : frame.boxes)
                // 15 = [ATTACK BOX] in this client's ANI node encoding.
                if (box.type == 15 && box.w > 0 && box.h > 0) { has = true; break; }
    } catch (const std::exception &) {
        has = false;
    }
    attackBoxCache_.emplace(path, has);
    return has;
}

const SkillVisualMapping &SkillMappingTable::resolve(int jobId, const CharacterRegistration &registration) {
    const SkillKey key{jobId, registration.id};
    if (const auto found = mappings_.find(key); found != mappings_.end()) return found->second;

    SkillVisualMapping mapping;
    mapping.key = key;
    mapping.skillPath = registration.path;
    const std::string skillStem = stemOf(registration.path);

    // --- SKL: name, passive flag, icon -------------------------------------
    try {
        const auto &parsed = catalog_.skillDefinition(key);
        const auto data = readSkillSourceData(parsed);
        mapping.name = data.name();
        mapping.passive = parsed.kind == SkillSourceKind::Passive;
        // [icon] is not part of the selected skill-data set, so read it from the
        // parsed field list: its two values are "img path, frame index".
        if (const auto iconFields = parsed.fieldsInScope("[icon]", "common"); !iconFields.empty()) {
            const auto &values = iconFields.front()->field.values;
            if (values.is_array() && values.size() >= 2 && values[0].is_string()) {
                mapping.iconPath = normalize(values[0].get<std::string>());
                if (values[1].is_number_integer()) mapping.iconFrame = values[1].get<int>();
            }
        }
    } catch (const std::exception &error) {
        mapping.missing = std::string("SKL 不可读: ") + error.what();
    }
    if (mapping.name.empty()) mapping.name = skillStem;

    // --- body motion from the CHR slot pool --------------------------------
    const auto &jobIndex = index(jobId);
    const auto exact = jobIndex.motions.find(skillStem);
    if (exact != jobIndex.motions.end() && !exact->second.empty()) {
        mapping.bodyAni = exact->second.front().path;
        mapping.bodySlotTag = exact->second.front().tag;
        mapping.confidence = MappingConfidence::AutoExact;
        mapping.evidence = "CHR motion slot name equals the SKL file stem";
    }
    // --- release chain: every stage named after the skill, in release order -
    // CHR slots and the job's own animation directory are merged, because each
    // one registers a different half of the motions.
    std::vector<std::pair<int, std::pair<std::string, std::string>>> staged;
    const auto consider = [&](const std::string &stem, const std::string &path,
                              const std::string &tag) {
        const int order = chainOrder(stem, skillStem);
        if (order >= 0) staged.push_back({order, {path, tag}});
    };
    for (const auto &[slotStem, resources] : jobIndex.motions)
        if (!resources.empty()) consider(slotStem, resources.front().path, resources.front().tag);
    for (const auto &[animStem, path] : jobIndex.animation) consider(animStem, path, "animation-dir");
    // Same file registered twice (CHR slot and directory) collapses to one.
    // The client's own motion list is the authority on order; a stage word is
    // only used to place a motion the client does not list.
    const std::string jobName = jobIndex.directory.empty()
                                    ? std::string()
                                    : jobIndex.directory.substr(jobIndex.directory.rfind('/') + 1);
    std::sort(staged.begin(), staged.end(), [&](const auto &a, const auto &b) {
        const int pa = motion_pool::positionOf(jobName, stemOf(a.second.first));
        const int pb = motion_pool::positionOf(jobName, stemOf(b.second.first));
        if (pa >= 0 && pb >= 0) return pa < pb;
        if (pa >= 0) return true;
        if (pb >= 0) return false;
        if (a.first != b.first) return a.first < b.first;
        return a.second.first < b.second.first;
    });
    staged.erase(std::unique(staged.begin(), staged.end(),
                             [](const auto &a, const auto &b) {
                                 return a.second.first == b.second.first;
                             }),
                 staged.end());

    if (mapping.bodyAni.empty() && !staged.empty()) {
        // The strike is the stage that carries the skill, so it is preferred
        // over a bare windup or recovery when both are present.
        const auto strike = std::find_if(staged.begin(), staged.end(),
                                         [](const auto &e) { return e.first >= 100 && e.first < 130; });
        const auto &picked = strike != staged.end() ? *strike : staged.front();
        mapping.bodyAni = picked.second.first;
        mapping.bodySlotTag = picked.second.second;
        mapping.confidence = MappingConfidence::AutoChain;
        mapping.evidence = "阶段词匹配: " + stemOf(picked.second.first);
    }
    // A chain is only worth playing when it has more than one stage; a single
    // stage is just the body animation under a longer name.
    if (staged.size() > 1) {
        for (const auto &entry : staged) mapping.bodyChain.push_back(entry.second.first);
        mapping.chainStages.reserve(staged.size());
        for (const auto &entry : staged) mapping.chainStages.push_back(entry.first);
        if (mapping.bodyAni.empty()) {
            mapping.bodyAni = staged.front().second.first;
            mapping.bodySlotTag = staged.front().second.second;
            mapping.confidence = MappingConfidence::AutoChain;
        }
        if (!mapping.bodyChain.empty() && mapping.bodyChain.size() > 1) {
            std::string joined;
            for (const auto &path : mapping.bodyChain) {
                if (!joined.empty()) joined += " -> ";
                joined += stemOf(path);
            }
            mapping.chainEvidence = joined;
            if (mapping.confidence == MappingConfidence::AutoChain)
                mapping.evidence = "release 链: " + joined;
        }
    }

    // --- effect animations: same directory, stem prefix --------------------
    if (!jobIndex.effectPaths.empty()) {
        for (const auto &path : jobIndex.effectPaths) {
            const auto effectStem = stemOf(path);
            if (effectStem.size() < 5) continue;
            if (effectStem.rfind(skillStem, 0) != 0) continue;
            if (mapping.effects.size() >= 6) break;
            mapping.effects.push_back(path);
        }
    }
    if (!jobIndex.particlePaths.empty()) {
        for (const auto &path : jobIndex.particlePaths) {
            const auto particleStem = stemOf(path);
            if (particleStem.empty() || particleStem.rfind(skillStem, 0) != 0) continue;
            mapping.particles.push_back(path);
        }
    }

    // --- exe binding override (1031 DNF.exe skill setState tables) ----------
    // Extracted from the plaintext setState dispatch tables: each entry's
    // handler selects body motions through vtable+0x49C immediates, and the
    // effect chains come from sqr/common.nut sq_LoadSkillEffect branches.
    // Authoritative where present, so it replaces the name-inferred chain.
    {
        std::string chrPath;
        try {
            chrPath = catalog_.at(jobId).registration.path;
        } catch (const std::exception &) {
        }
        if (!chrPath.empty()) {
            auto slash = chrPath.find_last_of("/\\");
            std::string file = slash == std::string::npos ? chrPath : chrPath.substr(slash + 1);
            auto dot = file.rfind('.');
            std::string chrStem = dot == std::string::npos ? file : file.substr(0, dot);
            if (const auto *exe = exe_bindings::find(chrStem.c_str(), registration.id)) {
                mapping.bodyChain.clear();
                mapping.chainStages.clear();
                for (size_t i = 0; i < exe->motionCount; ++i) {
                    mapping.bodyChain.push_back(exe->motions[i]);
                    mapping.chainStages.push_back(100 + static_cast<int>(i));
                }
                mapping.bodyAni = exe->motions[0];
                mapping.bodySlotTag = "exe-setstate";
                mapping.confidence = MappingConfidence::Manual;
                mapping.evidence = std::string(exe->evidence);
                std::string joined;
                for (const auto &path : mapping.bodyChain) {
                    if (!joined.empty()) joined += " -> ";
                    joined += stemOf(path);
                }
                mapping.chainEvidence = joined;
                for (size_t i = 0; i < exe->effectCount && mapping.effects.size() < 6; ++i) {
                    const std::string effect(exe->effects[i]);
                    if (std::find(mapping.effects.begin(), mapping.effects.end(), effect)
                        == mapping.effects.end())
                        mapping.effects.push_back(effect);
                }
            }
        }
    }

    // --- attack volume: source ANI only ------------------------------------
    if (!mapping.bodyAni.empty()) {
        mapping.hasAttackBox = animationHasAttackBox(mapping.bodyAni);
        if (mapping.hasAttackBox) mapping.attackSource = AttackBoxSource::AniBody;
    }
    // Effects can carry their own volume in 40JP, so check them too before
    // concluding a skill has no geometry at all.
    if (mapping.attackSource == AttackBoxSource::None) {
        for (const auto &effect : mapping.effects) {
            if (!animationHasAttackBox(effect)) continue;
            mapping.hasAttackBox = true;
            mapping.attackSource = AttackBoxSource::AniBody;
            mapping.evidence += "; attack volume comes from an effect ANI";
            break;
        }
    }

    // --- manual reconstructed volumes ---------------------------------------
    for (const auto &entry : kManualVolumes) {
        if (entry.jobId != jobId || entry.skillId != registration.id) continue;
        mapping.reconstructedBoxes.push_back(
            Box{15, entry.x, entry.y, entry.z, entry.w, entry.h, entry.d});
        mapping.reconstructedFrames.emplace_back(entry.firstFrame, entry.lastFrame);
        if (mapping.attackSource == AttackBoxSource::None)
            mapping.attackSource = AttackBoxSource::Reconstructed40Jp;
        mapping.hasAttackBox = true;
        mapping.evidence += std::string("; ") + entry.evidence;
    }

    // --- grade --------------------------------------------------------------
    const bool hasBody = !mapping.bodyAni.empty();
    const bool hasEffect = !mapping.effects.empty();
    if (mapping.passive) {
        mapping.grade = SkillGrade::D;
        mapping.missing = mapping.missing.empty() ? "被动技能，没有释放动作" : mapping.missing;
    } else if (hasBody && hasEffect && mapping.hasAttackBox) {
        mapping.grade = SkillGrade::A;
    } else if (hasBody) {
        mapping.grade = SkillGrade::B;
        if (mapping.missing.empty()) {
            if (!hasEffect && !mapping.hasAttackBox) mapping.missing = "缺特效 ANI、缺攻击框";
            else if (!hasEffect) mapping.missing = "缺特效 ANI";
            else mapping.missing = "该动作 ANI 内没有攻击框";
        }
    } else if (hasEffect) {
        mapping.grade = SkillGrade::C;
        if (mapping.missing.empty()) mapping.missing = "缺身体动作 ANI（CHR 槽未命中）";
    } else {
        mapping.grade = SkillGrade::D;
        if (mapping.missing.empty()) mapping.missing = "缺身体动作 ANI、缺特效 ANI";
    }
    if (mapping.confidence == MappingConfidence::None && hasEffect)
        mapping.confidence = MappingConfidence::AutoEffect;

    return mappings_.emplace(key, std::move(mapping)).first->second;
}

void SkillMappingTable::ensureJob(int jobId) {
    if (rows_.count(jobId)) return;
    std::vector<SkillRow> rows;
    try {
        for (const auto &registration : catalog_.at(jobId).skills.entries) {
            if (registration.id < 0) continue;
            const auto &mapping = resolve(jobId, registration);
            SkillRow row;
            row.key = mapping.key;
            row.name = mapping.name;
            row.skillPath = mapping.skillPath;
            row.iconPath = mapping.iconPath;
            row.iconFrame = mapping.iconFrame;
            row.grade = mapping.grade;
            row.missing = mapping.missing;
            rows.push_back(std::move(row));
        }
    } catch (const std::exception &) {
        // A job with no readable CHR yields an empty list; the caller reports
        // the job as unavailable instead of showing invented rows.
    }
    rows_.emplace(jobId, std::move(rows));

    // Refresh the job list so the UI shows grade counts for resolved jobs and
    // a neutral zero line for the ones not visited yet.
    jobs_.clear();
    for (const auto &definition : catalog_.definitions) {
        if (definition.registration.id < 0) continue;
        SkillJobInfo info;
        info.jobId = definition.registration.id;
        info.chrPath = definition.registration.path;
        info.name = definition.growtypeNames.is_array() && !definition.growtypeNames.empty() &&
                    definition.growtypeNames[0].is_string()
            ? definition.growtypeNames[0].get<std::string>()
            : definition.job;
        if (const auto found = rows_.find(info.jobId); found != rows_.end()) {
            info.skillCount = int(found->second.size());
            for (const auto &row : found->second) {
                switch (row.grade) {
                    case SkillGrade::A: ++info.gradeA; break;
                    case SkillGrade::B: ++info.gradeB; break;
                    case SkillGrade::C: ++info.gradeC; break;
                    default: ++info.gradeD; break;
                }
            }
        }
        jobs_.push_back(std::move(info));
    }
}

const std::vector<SkillJobInfo> &SkillMappingTable::jobs() const {
    return jobs_;
}

const std::vector<SkillRow> &SkillMappingTable::rows(int jobId) const {
    static const std::vector<SkillRow> empty;
    const auto found = rows_.find(jobId);
    return found == rows_.end() ? empty : found->second;
}

const SkillVisualMapping *SkillMappingTable::mapping(const SkillKey &key) const {
    const auto found = mappings_.find(key);
    return found == mappings_.end() ? nullptr : &found->second;
}

int SkillMappingTable::gradeCount(int jobId, SkillGrade grade) const {
    int count = 0;
    for (const auto &row : rows(jobId)) if (row.grade == grade) ++count;
    return count;
}

Json SkillMappingTable::auditJson(const std::vector<int> &jobIds) const {
    Json result{{"jobs", Json::array()}};
    Json totals{{"A", 0}, {"B", 0}, {"C", 0}, {"D", 0}};
    for (int jobId : jobIds) {
        Json jobJson{{"jobId", jobId}, {"skills", Json::array()}};
        Json counts{{"A", 0}, {"B", 0}, {"C", 0}, {"D", 0}};
        const auto &jobRows = rows(jobId);
        for (const auto &row : jobRows) {
            const auto *value = mapping(row.key);
            if (!value) continue;
            jobJson["skills"].push_back(value->audit());
            const auto name = std::string(gradeName(row.grade));
            counts[name] = counts[name].get<int>() + 1;
            totals[name] = totals[name].get<int>() + 1;
        }
        jobJson["counts"] = counts;
        jobJson["total"] = int(jobRows.size());
        result["jobs"].push_back(jobJson);
    }
    result["totals"] = totals;
    return result;
}
} // namespace dnf
