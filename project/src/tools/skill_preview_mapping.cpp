#include "dnf/skill_preview_mapping.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/resources.hpp"
#include "dnf/skill_preview_motion_pool.hpp"
#include "dnf/skill_exe_bindings.hpp"
#include <algorithm>
#include <cctype>
#include <climits>
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
// PVP variants are a separate branch of the same motion; the preview plays the
// PVE release, so those files are never part of a chain.
bool isPvpVariant(const std::string &path) {
    return path.find("[pvp]") != std::string::npos;
}
// The swordman and demonicswordman CHRs share one folder: the demonic flavour of
// each motion is the *_ds twin (ashenforksub_ds.ani, animation/ashenfork_ds/...).
// Claim only this CHR's flavour, otherwise a demonic skill borrows the plain
// motion and vice versa.
bool belongsToChr(const std::string &path, const std::string &chrStem) {
    const bool demonic = chrStem == "demonicswordman";
    bool dsTwin = false;
    const auto stem = stemOf(path);
    if (stem.size() > 3 && stem.compare(stem.size() - 3, 3, "_ds") == 0) dsTwin = true;
    if (path.find("_ds/") != std::string::npos) dsTwin = true;
    return dsTwin == demonic;
}
// A skill can legitimately declare many effect animations (TripleSlash lists
// seven in common.nut); the old cap of six silently dropped the tail. The cap
// now only exists to bound memory: a family such as HundredSword owns 36 files
// (ready, slash, swordair1/2, light1-3, tail1-4, ...) and dropping any of them
// also dropped the one animation that carried the attack volume.
constexpr size_t kEffectLimit = 48;

// Per-skill Squirrel scripts create their own visuals:
//   obj.sq_CreateCNRDAnimation("Effect/Animation/.../x.ani")
//   sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("..."), 0, 0)
//   obj.sq_LoadSkillEffectAni(skillIndex, "...")
// Only string literals ending in .ani are taken. Computed names and passive
// object ids need runtime data flow and stay unrecovered.
std::vector<std::string> scriptAnimationLiterals(const std::string &source) {
    std::vector<std::string> output;
    size_t quote = 0;
    while ((quote = source.find('"', quote)) != std::string::npos) {
        const auto close = source.find('"', quote + 1);
        if (close == std::string::npos) break;
        const auto literal = source.substr(quote + 1, close - quote - 1);
        const size_t headStart = quote > 240 ? quote - 240 : 0;
        const auto head = source.substr(headStart, quote - headStart);
        const bool isAnimation = literal.size() > 4 &&
            normalize(literal.substr(literal.size() - 4)) == ".ani";
        const bool created = head.find("sq_CreateCNRDAnimation") != std::string::npos ||
                             head.find("sq_createCNRDAnimation") != std::string::npos ||
                             head.find("sq_LoadSkillEffectAni") != std::string::npos;
        if (isAnimation && created) output.push_back(literal);
        quote = close + 1;
    }
    return output;
}

// Effect literals in the scripts are written against the job root:
// "Effect/Animation/ATAttack/fire/x.ani" resolves to
// character/mage/effect/animation/atattack/fire/x.ani for the atmage CHR.
std::string resolveScriptAnimationPath(Pvf &pvf, const std::string &literal,
                                       const std::string &baseJob) {
    std::string candidate = normalize(literal);
    if (candidate.rfind("./", 0) == 0) candidate = candidate.substr(2);
    if (pvf.has(candidate)) return candidate;
    if (baseJob.empty()) return candidate;
    const auto jobRoot = "character/" + baseJob + "/" + candidate;
    if (pvf.has(jobRoot)) return jobRoot;
    if (candidate.rfind("effect/", 0) == 0) {
        const auto passive = "passiveobject/character/" + baseJob + "/" + candidate;
        if (pvf.has(passive)) return passive;
        const auto passiveAnimation =
            "passiveobject/character/" + baseJob + "/animation/" + candidate.substr(7);
        if (pvf.has(passiveAnimation)) return passiveAnimation;
    }
    return jobRoot;
}
// A passive object addresses its visuals relative to its own folder:
//   passiveobject/character/gunner/flamebulletfireexplosion.obj
//   [basic motion] "../../Common/Animation/FireExplosion.ani"
//   [string data]  "../../Common/Particle/FireExplosionParticle1.ptl"
// The job folder is the base every relative path is written against.
std::string resolveObjectRelative(const std::string &baseJob, const std::string &reference) {
    if (baseJob.empty() || reference.empty()) return {};
    const auto base = "passiveobject/character/" + baseJob + "/";
    const auto joined = fs::u8path(base) / fs::u8path(normalize(reference));
    return normalize(joined.lexically_normal().generic_u8string());
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
    // Weapon and form variants: weaponcomboshort1 .. weaponcombolight3 are all
    // stages of the same skill, picked by the equipped weapon type.
    {"short", 60},   {"light", 62},   {"heavy", 64},   {"blunt", 66}, {"blade", 68},
    {"spear", 70},   {"claw", 72},    {"pick", 74},    {"shoulder", 76},
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
// The tail may be several stage words plus a serial (multiheadshotshoot4,
// hundredswordmoveready2, weaponcomboshort1). Every token has to be a known
// stage word, so an unrelated suffix still fails the match.
int stageOrder(const std::string &tail) {
    if (tail.empty()) return 0; // exact stem
    size_t pos = 0;
    int order = 0;
    bool matchedAny = false;
    while (pos < tail.size()) {
        bool matched = false;
        // Longest word first: "standby" must win over "stand".
        const StageWord *best = nullptr;
        for (const auto &entry : kStageWords) {
            const std::string word(entry.word);
            if (tail.compare(pos, word.size(), word) != 0) continue;
            if (best && std::string(best->word).size() >= word.size()) continue;
            best = &entry;
        }
        if (best) {
            pos += std::string(best->word).size();
            order = std::max(order, best->order);
            matchedAny = true;
            continue;
        }
        const size_t start = pos;
        while (pos < tail.size() && tail[pos] >= '0' && tail[pos] <= '9') ++pos;
        if (pos > start) {
            order += std::min<int>(9, std::atoi(tail.substr(start, pos - start).c_str()));
            matchedAny = true;
            continue;
        }
        return -1;
    }
    return matchedAny ? order : -1;
}

// Release order of an effect file stem. Unlike stageOrder() this does not
// require the whole tail to be stage words: effect files are descriptive
// (bloom1, exp_0_dodge, swordair2, finishtail1, end_cir_01_dodge), so the word
// is searched for anywhere in the stem. A trailing serial is kept as a tie
// break so bloom1 < bloom2 and _00_ < _01_.
int effectStageOrder(const std::string &stem) {
    static const StageWord kEffectWords[] = {
        {"ready", 10},  {"prepare", 12}, {"start", 20},  {"appear", 22},
        {"cast", 24},   {"charge", 26},  {"create", 28}, {"throw", 30},
        {"move", 40},   {"air", 45},     {"stay", 48},   {"loop", 50},
        {"attack", 60}, {"slash", 62},   {"swing", 62},  {"shoot", 64},
        {"hit", 66},    {"strike", 66},  {"blast", 70},  {"exp", 72},
        {"explosion", 72}, {"ground", 74}, {"field", 74}, {"line", 76},
        {"tile", 78},   {"flash", 80},   {"light", 82},  {"glow", 84},
        {"particle", 86}, {"dust", 88},  {"tail", 92},   {"finish", 95},
        {"end", 96},    {"disappear", 98},
    };
    int best = -1;
    for (const auto &entry : kEffectWords) {
        const std::string word(entry.word);
        if (stem.find(word) == std::string::npos) continue;
        best = std::max(best, entry.order);
    }
    if (best < 0) best = 55; // unlabelled effect: treat it as the strike body
    // A serial only orders files inside the same stage word.
    int serial = 0;
    for (size_t i = stem.size(); i > 0; --i) {
        if (stem[i - 1] < '0' || stem[i - 1] > '9') {
            if (i < stem.size()) serial = std::atoi(stem.c_str() + i);
            break;
        }
        if (i == 1) serial = std::atoi(stem.c_str());
    }
    return best * 100 + std::min(99, serial);
}

// Upgrade words a skill can append to a motion base name: flowmind + powerup.
bool isVariantTail(const std::string &tail) {    static const char *const kWords[] = {"powerup", "poweron", "power", "up",   "ex",
                                         "exp",     "full",    "charge"};
    for (const char *word : kWords)
        if (tail == word) return true;
    return false;
}

// Does this animation stem name a stage of the given skill? Returns its order.
int chainOrder(const std::string &slotStem, const std::string &skillStem) {
    if (slotStem.size() >= skillStem.size()) {
        std::string tail;
        if (slotStem.compare(0, skillStem.size(), skillStem) == 0) {
            tail = slotStem.substr(skillStem.size());
        } else if (slotStem.compare(slotStem.size() - skillStem.size(), skillStem.size(),
                                   skillStem) == 0) {
            // Stage word in front of the skill stem: stay + sacrifice = StaySacrifice.
            const auto head = slotStem.substr(0, slotStem.size() - skillStem.size());
            const int headOrder = stageOrder(head);
            if (headOrder >= 0) return headOrder;
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
            if (stripped && head.size() >= skillStem.size() &&
                head.compare(0, skillStem.size(), skillStem) == 0)
                tail = head.substr(skillStem.size());
        }
        if (!tail.empty()) {
            if (std::all_of(tail.begin(), tail.end(), [](char c) { return c >= '0' && c <= '9'; }))
                // A bare serial (tripleslash1) carries no stage meaning; treat it
                // as the strike so it stays playable rather than being dropped.
                return 100 + std::min<int>(9, std::atoi(tail.c_str()));
            const int order = stageOrder(tail);
            if (order >= 0) return order;
        }
    }
    // The motion carries the base name and the skill appends an upgrade word, or
    // the two differ by a stage on either side: flowmindstart vs flowmindpowerup.
    // Both tails have to parse, so a chance substring overlap still fails.
    for (int cut = int(std::min(slotStem.size(), skillStem.size())); cut >= 5; --cut) {
        if (slotStem.compare(0, size_t(cut), skillStem, 0, size_t(cut)) != 0) continue;
        const auto slotTail = slotStem.substr(size_t(cut));
        const auto skillTail = skillStem.substr(size_t(cut));
        if (slotTail.empty()) continue;
        const int slotOrder = stageOrder(slotTail);
        if (slotOrder < 0) continue;
        if (!skillTail.empty() && !isVariantTail(skillTail)) continue;
        return slotOrder;
    }
    return -1;
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
               {"genericBody", !fallbackPose.empty()}, {"standInPose", fallbackPose},
               {"evidence", evidence}, {"missing", missing}};
    Json layers = Json::array();
    for (const auto &layer : effectLayers) {
        layers.push_back({{"path", layer.path}, {"stage", layer.stage},
                          {"timed", layer.timed}, {"alsFrame", layer.alsFrame},
                          {"alsLayer", layer.alsLayer}, {"instance", layer.instance},
                          {"birthRatio", layer.birthRatio}, {"lifeMs", layer.lifeMs},
                          {"loop", layer.loop}, {"source", layer.source},
                          {"offsetX", layer.offsetX}, {"offsetY", layer.offsetY},
                          {"offsetZ", layer.offsetZ}, {"evidence", layer.evidence}});
    }
    value["effectLayers"] = layers;
    Json persistentJson = Json::array();
    for (const auto &entity : persistents) {
        const char *kind = entity.kind == PersistentKind::Orbit ? "orbit"
                           : entity.kind == PersistentKind::AirSword ? "air_sword" : "ground_field";
        persistentJson.push_back({{"path", entity.path}, {"object", entity.object}, {"kind", kind},
                                  {"count", entity.count}, {"radius", entity.radius},
                                  {"angularDegPerSec", entity.angularDegPerSec},
                                  {"phaseDeg", entity.phaseDeg}, {"offsetX", entity.offsetX},
                                  {"offsetY", entity.offsetY}, {"loop", entity.loop},
                                  {"evidence", entity.evidence}});
    }
    value["persistents"] = persistentJson;
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
        const auto chrPath = normalize(catalog_.at(jobId).registration.path);
        built.chrStem = stemOf(chrPath);
        built.baseJob = normalize(fs::u8path(parentOf(chrPath)).filename().u8string());
        for (const auto &resource : catalog_.at(jobId).resources) {
            const auto tag = normalize(resource.tag);
            if (tag.find("motion") == std::string::npos) continue;
            if (!resource.exists || resource.path.empty()) continue;
            built.motions[stemOf(resource.path)].push_back(resource);
            // Keep the named single-slot motions reachable by tag: [buff motion]
            // is the generic cast pose, [back motion]/[jump motion] are the
            // skills of the same name.
            if (built.baseMotions.find(tag) == built.baseMotions.end())
                built.baseMotions.emplace(tag, normalize(resource.path));
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
        // Skill entities share the base job folder: character/swordman owns both
        // the swordman and the demonicswordman CHR, and the demonic flavour is
        // the *_ds twin of each object. Claim only this CHR's flavour so the
        // two classes do not borrow each other's visuals.
        if (!built.baseJob.empty()) {
            const auto entityRoot = "passiveobject/character/" + built.baseJob;
            const bool demonic = built.chrStem == "demonicswordman";
            for (const auto &path : pvf_.paths(entityRoot + "/", ".obj")) {
                if (parentOf(path) != entityRoot) continue;
                auto stem = stemOf(path);
                const bool ds = stem.size() > 3 && stem.compare(stem.size() - 3, 3, "_ds") == 0;
                if (ds != demonic) continue;
                if (ds) stem = stem.substr(0, stem.size() - 3);
                built.passiveObjects.emplace(stem, path);
            }
            built.passiveAnimations = pvf_.paths(entityRoot + "/animation/", ".ani");
        }
        // The swordman and demonicswordman CHRs share character/swordman. The
        // demonic flavour of a file is its *_ds twin, but a demonic-only skill
        // (杀意波动 dotarea) has no twin at all and ships only under the plain
        // name. Prefer the twin when it exists, fall back to the plain file
        // otherwise, and never let a demonic file reach the plain CHR.
        if (built.chrStem == "swordman" || built.chrStem == "demonicswordman") {
            const bool demonic = built.chrStem == "demonicswordman";
            const auto isTwin = [](const std::string &path) {
                const auto stem = stemOf(path);
                return (stem.size() > 3 && stem.compare(stem.size() - 3, 3, "_ds") == 0) ||
                       path.find("_ds/") != std::string::npos;
            };
            const auto baseStem = [](const std::string &path) {
                auto stem = stemOf(path);
                if (stem.size() > 3 && stem.compare(stem.size() - 3, 3, "_ds") == 0)
                    stem = stem.substr(0, stem.size() - 3);
                return stem;
            };
            const auto filterFlavour = [&](std::vector<std::string> &list) {
                std::set<std::string> twinBases;
                if (demonic)
                    for (const auto &path : list)
                        if (isTwin(path)) twinBases.insert(baseStem(path));
                std::vector<std::string> kept;
                kept.reserve(list.size());
                for (const auto &path : list) {
                    if (!demonic) {
                        if (!isTwin(path)) kept.push_back(path);
                    } else if (isTwin(path) || twinBases.find(baseStem(path)) == twinBases.end()) {
                        kept.push_back(path);
                    }
                }
                list = std::move(kept);
            };
            filterFlavour(built.effectPaths);
            filterFlavour(built.passiveAnimations);
        }
        // Group every effect ANI into the family directory it belongs to. A
        // family is the first path segment below the animation root
        // (aticesword/01_light_dodge.ani -> aticesword); a file sitting directly
        // in the root is its own family (tripleslash.ani -> tripleslash).
        {
            const auto addFamily = [&built](const std::string &root, const std::string &path) {
                if (path.rfind(root, 0) != 0) return;
                const auto relative = path.substr(root.size());
                const auto slash = relative.find('/');
                const auto family =
                    slash == std::string::npos ? stemOf(path) : relative.substr(0, slash);
                if (family.empty()) return;
                built.effectFamilies[family].push_back(path);
            };
            if (!built.directory.empty())
                for (const auto &path : built.effectPaths)
                    addFamily(built.directory + "/effect/animation/", path);
            if (!built.baseJob.empty()) {
                const auto entityRoot = "passiveobject/character/" + built.baseJob;
                for (const auto &path : built.passiveAnimations)
                    addFamily(entityRoot + "/animation/", path);
            }
            for (auto &[family, files] : built.effectFamilies) {
                (void)family;
                std::sort(files.begin(), files.end());
                files.erase(std::unique(files.begin(), files.end()), files.end());
            }
        }
        // Per-skill scripts live beside the CHR's own script directory:
        //   sqr/character/atmage/firepillar/firepillar.nut  (nested)
        //   sqr/character/priest/avengerattack.nut          (flat)
        // A nested folder belongs to the skill of the same name, and every nut
        // inside it (including po_* passive-object scripts) is part of that
        // skill's visual chain. Flat *_header.nut files carry the CUSTOM_ANI
        // constants that index the CHR [etc motion] table.
        if (!built.chrStem.empty()) {
            const auto scriptRoot = "sqr/character/" + built.chrStem + "/";
            for (const auto &path : pvf_.paths(scriptRoot, ".nut")) {
                if (path.rfind(scriptRoot, 0) != 0) continue;
                const auto relative = path.substr(scriptRoot.size());
                const auto slash = relative.find('/');
                const auto stem = stemOf(path);
                if (slash == std::string::npos) {
                    if (stem.size() > 7 && stem.compare(stem.size() - 7, 7, "_header") == 0) {
                        try {
                            const auto raw = pvf_.read(path);
                            const std::string text(raw.begin(), raw.end());
                            size_t at = 0;
                            while ((at = text.find("CUSTOM_ANI_", at)) != std::string::npos) {
                                size_t cursor = at;
                                while (cursor < text.size() &&
                                       (std::isalnum(static_cast<unsigned char>(text[cursor])) || text[cursor] == '_'))
                                    ++cursor;
                                const auto name = text.substr(at, cursor - at);
                                while (cursor < text.size() && std::isspace(static_cast<unsigned char>(text[cursor])))
                                    ++cursor;
                                if (text.compare(cursor, 2, "<-") == 0) {
                                    cursor += 2;
                                    while (cursor < text.size() &&
                                           std::isspace(static_cast<unsigned char>(text[cursor])))
                                        ++cursor;
                                    const size_t start = cursor;
                                    while (cursor < text.size() &&
                                           std::isdigit(static_cast<unsigned char>(text[cursor])))
                                        ++cursor;
                                    if (cursor > start)
                                        built.customAnimations[name] =
                                            std::stoi(text.substr(start, cursor - start));
                                }
                                at = cursor > at ? cursor : at + 1;
                            }
                        } catch (const std::exception &) {
                        }
                        continue;
                    }
                    if (stem == built.chrStem) continue;
                    built.skillScripts[stem].push_back(path);
                } else {
                    const auto skill = normalize(relative.substr(0, slash));
                    if (!skill.empty() && skill != built.chrStem)
                        built.skillScripts[skill].push_back(path);
                }
            }
        }
        // [etc motion] is the table CUSTOM_ANI_<X> indexes into. Sort by the
        // field offset and value index so table positions survive.
        std::vector<CharacterResource> etcMotions;
        for (const auto &resource : catalog_.at(jobId).resources)
            if (normalize(resource.tag) == "[etc motion]" && resource.exists && !resource.path.empty())
                etcMotions.push_back(resource);
        std::sort(etcMotions.begin(), etcMotions.end(), [](const auto &a, const auto &b) {
            return a.fieldOffset != b.fieldOffset ? a.fieldOffset < b.fieldOffset
                                                  : a.valueIndex < b.valueIndex;
        });
        for (const auto &resource : etcMotions) built.etcMotions.push_back(resource.path);
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
    // An EX upgrade is the same skill with stronger numbers, and 1031 authors
    // its visuals under the base name: grabexplosionex.skl -> grabexplosion1.ani,
    // suplexcycloneex.skl -> suplexcyclone/. The base stem is a weaker key, never
    // stronger, so an exact family still wins.
    std::string baseStem;
    if (skillStem.size() > 4 && skillStem.compare(skillStem.size() - 2, 2, "ex") == 0)
        baseStem = skillStem.substr(0, skillStem.size() - 2);

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
        if (isPvpVariant(path) || !belongsToChr(path, jobIndex.chrStem)) return;
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

    // --- body motion declared by the skill script ---------------------------
    // sq_SetCurrentAnimation(CUSTOM_ANI_X) is how atmage/priest scripts select
    // a motion: the job header maps the constant to an index and the CHR
    // [etc motion] table maps that index to the .ani. This is the authoritative
    // body chain for those jobs; name matching stays the fallback.
    std::vector<std::string> scriptBody;
    if (const auto scripts = jobIndex.skillScripts.find(skillStem);
        scripts != jobIndex.skillScripts.end() && !jobIndex.etcMotions.empty()) {
        for (const auto &path : scripts->second) {
            try {
                const auto raw = pvf_.read(path);
                const std::string source(raw.begin(), raw.end());
                size_t at = 0;
                while ((at = source.find("sq_SetCurrentAnimation", at)) != std::string::npos) {
                    const auto open = source.find('(', at);
                    if (open == std::string::npos) break;
                    const auto close = source.find(')', open);
                    if (close == std::string::npos) break;
                    std::string argument = source.substr(open + 1, close - open - 1);
                    while (!argument.empty() && std::isspace(static_cast<unsigned char>(argument.front())))
                        argument.erase(argument.begin());
                    while (!argument.empty() && std::isspace(static_cast<unsigned char>(argument.back())))
                        argument.pop_back();
                    if (const auto constant = jobIndex.customAnimations.find(argument);
                        constant != jobIndex.customAnimations.end()) {
                        const int index = constant->second;
                        if (index >= 0 && static_cast<size_t>(index) < jobIndex.etcMotions.size()) {
                            const auto &animation = jobIndex.etcMotions[static_cast<size_t>(index)];
                            if (std::find(scriptBody.begin(), scriptBody.end(), animation) == scriptBody.end())
                                scriptBody.push_back(animation);
                        }
                    }
                    at = close + 1;
                }
            } catch (const std::exception &) {
            }
        }
    }
    if (!scriptBody.empty() && mapping.confidence != MappingConfidence::Manual) {
        mapping.bodyChain = scriptBody;
        mapping.chainStages.clear();
        for (size_t i = 0; i < scriptBody.size(); ++i)
            mapping.chainStages.push_back(100 + static_cast<int>(i));
        mapping.bodyAni = scriptBody.front();
        mapping.bodySlotTag = "sqr-custom-ani";
        if (mapping.confidence == MappingConfidence::None) mapping.confidence = MappingConfidence::AutoChain;
        std::string joined;
        for (const auto &animation : scriptBody) {
            if (!joined.empty()) joined += " -> ";
            joined += stemOf(animation);
        }
        mapping.chainEvidence = joined;
        mapping.evidence += "; body: sqr CUSTOM_ANI declaration";
    }

    // --- effect animations --------------------------------------------------
    // Three sources, strongest first:
    //   1. sqr/common.nut through the exe binding (swordman / demonicswordman)
    //   2. per-skill scripts under sqr/character/<chrStem>/ (atmage, priest, ...)
    //   3. file-name prefix under character/<job>/effect/animation (fallback)
    // Mixing them produced wrong chains: HardAttack declares two effects in
    // common.nut while the prefix scan added four unrelated *_ds/_fullcharge
    // animations to the same skill.
    std::vector<std::string> prefixEffects;
    for (const auto &candidate : {skillStem, baseStem}) {
        if (candidate.empty()) continue;
        for (const auto &path : jobIndex.effectPaths) {
            if (isPvpVariant(path)) continue;
            const auto effectStem = stemOf(path);
            if (effectStem.size() < 5) continue;
            if (effectStem.rfind(candidate, 0) != 0) continue;
            // Only the skill's own family counts: either the file sits directly
            // in effect/animation (upperswing.ani) or in a folder named after
            // the skill (rapidmoveslash/slash1.ani). A same-named file under
            // another skill's folder is a different branch
            // (chillingpowder/upperswing1).
            const auto parentStem = stemOf(parentOf(path));
            if (parentStem != candidate && parentStem != "animation") continue;
            if (std::find(prefixEffects.begin(), prefixEffects.end(), path) !=
                prefixEffects.end())
                continue;
            if (prefixEffects.size() >= kEffectLimit) break;
            prefixEffects.push_back(path);
        }
    }
    if (!jobIndex.particlePaths.empty()) {
        for (const auto &path : jobIndex.particlePaths) {
            const auto particleStem = stemOf(path);
            if (particleStem.empty() || particleStem.rfind(skillStem, 0) != 0) continue;
            mapping.particles.push_back(path);
        }
    }

    // --- effect family directory -------------------------------------------
    // 1031 groups a skill's visuals in a directory named after it and the file
    // stems inside are descriptive, not prefixed: aticesword/01_light_dodge,
    // nenshield/bloom1, atlightningdragon/exp_0_dodge. Matching the directory
    // is the only rule that reaches them. Male subclasses (atmage, atfighter)
    // prefix the family with "at"; the prefix is kept in the score so a plain
    // CHR prefers its own family over the male variant.
    constexpr size_t kFamilyEffectLimit = 48;
    std::vector<std::string> familyEffects;
    {
        const bool atClass = jobIndex.chrStem.rfind("at", 0) == 0;
        const auto familyScore = [&](const std::string &family, const std::string &stem,
                                     int penalty) {
            std::string normalized = family;
            bool at = false;
            if (normalized.size() > 2 && normalized.compare(0, 2, "at") == 0) {
                normalized = normalized.substr(2);
                at = true;
            }
            if (normalized == stem) return penalty + (at ? (atClass ? 0 : 3) : 0);
            if (normalized.size() > stem.size() &&
                normalized.compare(0, stem.size(), stem) == 0) {
                const auto tail = normalized.substr(stem.size());
                if (stageOrder(tail) >= 0) return penalty + (at ? 2 : 1);
            }
            return -1;
        };
        // A family whose name never repeats the skill stem: Nen Guard's shield
        // is authored as nenshield while the skill file is nenguard.skl, and
        // Spiral Nen as atspiralnen while the skill file is kikouken.skl.
        static const struct {
            const char *skill;
            const char *family;
        } kFamilyAliases[] = {
            {"nenguard", "nenshield"},   {"sajahu", "roarstun"},
            {"sajahuex", "roarstunex"},  {"kikouken", "atspiralnen"},
            {"nenmonsterwhitetiger", "nenmonster"}, {"pushout", "atpush"},
        };
        int bestScore = -1;
        std::string bestFamily;
        for (const auto &[family, files] : jobIndex.effectFamilies) {
            (void)files;
            int score = familyScore(family, skillStem, 0);
            if (score < 0 && !baseStem.empty()) score = familyScore(family, baseStem, 4);
            for (const auto &alias : kFamilyAliases)
                if (skillStem == alias.skill && family == alias.family) score = 0;
            if (score < 0) continue;
            if (bestScore < 0 || score < bestScore) {
                bestScore = score;
                bestFamily = family;
            }
        }
        if (!bestFamily.empty()) {
            // A phase directory (atnenflower/start_line_dodge, end_dodge, tiger)
            // holds many files; taking one round per subdirectory keeps every
            // phase represented instead of playing the first folder 12 times.
            std::map<std::string, std::vector<std::string>> groups;
            const auto marker = "/" + bestFamily + "/";
            for (const auto &path : jobIndex.effectFamilies.at(bestFamily)) {
                std::string relative;
                const auto at = path.find(marker);
                if (at != std::string::npos) relative = path.substr(at + marker.size());
                const auto slash = relative.find('/');
                groups[slash == std::string::npos ? std::string() : relative.substr(0, slash)]
                    .push_back(path);
            }
            for (size_t round = 0; familyEffects.size() < kFamilyEffectLimit; ++round) {
                bool added = false;
                for (auto &[group, files] : groups) {
                    (void)group;
                    // Inside one phase folder the release order is the stage word
                    // in the file stem: ready before slash before disappear. The
                    // client never lists them in order, so this sort is the only
                    // thing that keeps a round from replaying the folder in
                    // alphabetical (01_, 02_) order.
                    std::stable_sort(files.begin(), files.end(),
                                     [](const std::string &a, const std::string &b) {
                                         const int left = effectStageOrder(stemOf(a));
                                         const int right = effectStageOrder(stemOf(b));
                                         if (left != right) return left < right;
                                         return a < b;
                                     });
                    if (round >= files.size()) continue;
                    if (familyEffects.size() >= kFamilyEffectLimit) break;
                    familyEffects.push_back(files[round]);
                    added = true;
                }
                if (!added) break;
            }
        }
    }

    // --- skill entity visuals (passive objects) -----------------------------
    // A large share of the high-level skills are rendered by a passive object
    // rather than by effect animations: Khazan's summoned ghost, Saya's ice
    // field, TombStoneRain's stones, Blache's swamp. The object lives at
    // passiveobject/character/<job>/<skill>.obj and carries its own [etc motion]
    // list, so the skill's real visuals were never reachable through
    // character/<job>/effect/animation.
    std::vector<std::string> entityEffects;
    {
        // Candidates in order of confidence: the exact object first, then every
        // object whose stem prefixes the skill (tombstonerainex -> tombstonerain
        // -> tombstone). An object that carries no [etc motion] is not the
        // skill's visual body, so the next candidate still gets a turn.
        std::vector<std::string> candidates;
        if (const auto exact = jobIndex.passiveObjects.find(skillStem);
            exact != jobIndex.passiveObjects.end())
            candidates.push_back(exact->second);
        // Male subclasses name their objects with the same "at" prefix as their
        // effect families: atwatercannon.obj renders the watercannon skill.
        if (jobIndex.chrStem.rfind("at", 0) == 0) {
            if (const auto exact = jobIndex.passiveObjects.find("at" + skillStem);
                exact != jobIndex.passiveObjects.end())
                candidates.push_back(exact->second);
        }
        std::vector<std::pair<size_t, std::string>> prefixes;
        std::vector<std::pair<size_t, std::string>> reversePrefixes;
        for (const auto &[stem, path] : jobIndex.passiveObjects) {
            auto normalized = stem;
            if (normalized.size() > 3 && normalized.compare(0, 2, "at") == 0)
                normalized = normalized.substr(2);
            if (normalized.size() < 4) continue;
            // Two directions: an upgraded skill reuses the base object
            // (tombstonerainex -> tombstonerain), while a base skill's object
            // carries a role suffix (flamebullet -> flamebulletfireexplosion).
            if (skillStem.size() > normalized.size() && skillStem.rfind(normalized, 0) == 0)
                prefixes.emplace_back(normalized.size(), path);
            else if (normalized.size() > skillStem.size() &&
                     normalized.rfind(skillStem, 0) == 0)
                reversePrefixes.emplace_back(normalized.size() - skillStem.size(), path);
        }
        std::sort(prefixes.begin(), prefixes.end(),
                  [](const auto &a, const auto &b) { return a.first > b.first; });
        std::sort(reversePrefixes.begin(), reversePrefixes.end(),
                  [](const auto &a, const auto &b) { return a.first < b.first; });
        for (const auto &entry : prefixes) candidates.push_back(entry.second);
        for (const auto &entry : reversePrefixes) candidates.push_back(entry.second);

        for (const auto &entityObject : candidates) {
            try {
                const auto view =
                    pvf_.fieldView(entityObject, {"[etc motion]", "[basic motion]", "[string data]"});
                const auto pushEntity = [&](const std::string &path) {
                    if (path.empty() || !pvf_.has(path)) return;
                    if (std::find(entityEffects.begin(), entityEffects.end(), path) !=
                        entityEffects.end())
                        return;
                    if (entityEffects.size() >= kEffectLimit) return;
                    entityEffects.push_back(path);
                };
                for (const auto &value : view.values("[etc motion]")) {
                    if (!value.is_string()) continue;
                    auto name = normalize(value.get<std::string>());
                    if (name.size() < 5 || name.compare(name.size() - 4, 4, ".ani") != 0) continue;
                    pushEntity("passiveobject/character/" + jobIndex.baseJob + "/" + name);
                }
                // Objects that are a projectile/explosion rather than a caster
                // keep one [basic motion] instead of an [etc motion] table.
                for (const auto &value : view.values("[basic motion]")) {
                    if (!value.is_string()) continue;
                    const auto name = normalize(value.get<std::string>());
                    if (name.size() < 5 || name.compare(name.size() - 4, 4, ".ani") != 0) continue;
                    pushEntity(resolveObjectRelative(jobIndex.baseJob, name));
                }
                // [string data] lists the particle programs the object emits;
                // gunner bullets carry their entire visible burst this way.
                for (const auto &value : view.values("[string data]")) {
                    if (!value.is_string()) continue;
                    const auto name = normalize(value.get<std::string>());
                    if (name.size() < 4 || name.compare(name.size() - 4, 4, ".ptl") != 0) continue;
                    const auto path = resolveObjectRelative(jobIndex.baseJob, name);
                    if (path.empty() || !pvf_.has(path)) continue;
                    if (std::find(mapping.particles.begin(), mapping.particles.end(), path) !=
                        mapping.particles.end())
                        continue;
                    mapping.particles.push_back(path);
                }
            } catch (const std::exception &) {
                // An unreadable object adds nothing; the row keeps its own gap.
            }
        }
        // Some objects keep their animations beside the object tree instead.
        if (entityEffects.empty()) {
            for (const auto &path : jobIndex.passiveAnimations) {
                if (isPvpVariant(path)) continue;
                const auto stem = stemOf(path);
                if (stem.size() < 5 || stem.rfind(skillStem, 0) != 0) continue;
                if (stemOf(parentOf(path)) == "animation" && stem.size() <= skillStem.size())
                    continue;
                if (std::find(entityEffects.begin(), entityEffects.end(), path) !=
                    entityEffects.end())
                    continue;
                if (entityEffects.size() >= kEffectLimit) break;
                entityEffects.push_back(path);
            }
        }
    }

    // --- exe binding override (1031 DNF.exe skill setState tables) ----------
    // Extracted from the plaintext setState dispatch tables: each entry's
    // handler selects body motions through vtable+0x49C immediates, and the
    // effect chains come from sqr/common.nut sq_LoadSkillEffect branches.
    // Authoritative where present, so it replaces the name-inferred chain.
    std::vector<std::string> exeEffects;
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
                // The exe entry lists the entry motion of the release state; the
                // later stages are named after the skill in the CHR and only the
                // name scan reaches them (HundredSwordMoveSlash2..5, KallaFinish1..3).
                // Those are the same skill by name, so they extend the chain
                // instead of being dropped by the override.
                for (const auto &entry : staged) {
                    if (std::find(mapping.bodyChain.begin(), mapping.bodyChain.end(),
                                  entry.second.first) != mapping.bodyChain.end())
                        continue;
                    if (mapping.bodyChain.size() > 12) break;
                    mapping.bodyChain.push_back(entry.second.first);
                }
                mapping.chainStages.clear();
                for (size_t i = 0; i < mapping.bodyChain.size(); ++i)
                    mapping.chainStages.push_back(100 + static_cast<int>(i));
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
                for (size_t i = 0; i < exe->effectCount && exeEffects.size() < kEffectLimit; ++i) {
                    const std::string effect(exe->effects[i]);
                    if (std::find(exeEffects.begin(), exeEffects.end(), effect) == exeEffects.end())
                        exeEffects.push_back(effect);
                }
            }
        }
    }

    // --- per-skill script declarations -------------------------------------
    // checkExecutableSkill / onSetState call sq_CreateCNRDAnimation and
    // sq_AddStateLayerAnimation with animation literals; these create the
    // visuals that common.nut never lists for non-swordman jobs.
    std::vector<std::string> scriptEffects;
    if (const auto found = jobIndex.skillScripts.find(skillStem); found != jobIndex.skillScripts.end()) {
        for (const auto &path : found->second) {
            try {
                const auto raw = pvf_.read(path);
                const std::string source(raw.begin(), raw.end());
                for (const auto &literal : scriptAnimationLiterals(source)) {
                    const auto resolved = resolveScriptAnimationPath(pvf_, literal, jobIndex.baseJob);
                    if (!pvf_.has(resolved)) continue;
                    if (std::find(scriptEffects.begin(), scriptEffects.end(), resolved) != scriptEffects.end())
                        continue;
                    if (scriptEffects.size() >= kEffectLimit) break;
                    scriptEffects.push_back(resolved);
                }
            } catch (const std::exception &) {
                // An unreadable script contributes no effects; the row keeps its
                // own missing reason instead of borrowing another skill's files.
            }
        }
    }

    if (!exeEffects.empty()) {
        mapping.effects = exeEffects;
        mapping.evidence += "; effects: sqr/common.nut declaration";
        for (const auto *supplement : {&scriptEffects, &familyEffects}) {
            for (const auto &effect : *supplement) {
                if (mapping.effects.size() >= kEffectLimit) break;
                if (std::find(mapping.effects.begin(), mapping.effects.end(), effect) ==
                    mapping.effects.end())
                    mapping.effects.push_back(effect);
            }
        }
    } else if (!scriptEffects.empty() || !familyEffects.empty()) {
        mapping.effects = scriptEffects;
        for (const auto &effect : familyEffects) {
            if (mapping.effects.size() >= kEffectLimit) break;
            if (std::find(mapping.effects.begin(), mapping.effects.end(), effect) ==
                mapping.effects.end())
                mapping.effects.push_back(effect);
        }
        mapping.evidence += scriptEffects.empty() ? "; effects: skill effect family directory"
                                                  : "; effects: per-skill sqr script + family directory";
    } else {
        mapping.effects = prefixEffects;
    }
    // The entity supplement comes last: it is the skill's own on-screen body and
    // stays whatever the declared effect chain already covers.
    if (!entityEffects.empty()) {
        for (const auto &effect : entityEffects) {
            if (mapping.effects.size() >= kEffectLimit) break;
            if (std::find(mapping.effects.begin(), mapping.effects.end(), effect) !=
                mapping.effects.end())
                continue;
            mapping.effects.push_back(effect);
        }
        mapping.evidence += "; effects: passive object motion table";
    }

    // --- CHR base motion fallback ------------------------------------------
    // A handful of skills ship under a different motion name than the SKL file.
    // Reckless is the Berserker "Frenzy": the CHR reserves Frenzy1..4 for it and
    // no other skill claims them, so the alias is the only owner of those slots.
    if (mapping.bodyChain.empty() && mapping.bodyAni.empty() && !mapping.passive) {
        static const struct {
            const char *skill;
            const char *motion;
        } kMotionAliases[] = {
            {"reckless", "frenzy"},
        };
        for (const auto &alias : kMotionAliases) {
            if (skillStem != alias.skill) continue;
            std::vector<std::string> chain;
            for (const auto &[stem, resources] : jobIndex.motions) {
                if (stem.rfind(alias.motion, 0) != 0 || resources.empty()) continue;
                chain.push_back(resources.front().path);
            }
            if (chain.empty()) continue;
            mapping.bodyChain = chain;
            mapping.chainStages.clear();
            for (size_t i = 0; i < chain.size(); ++i)
                mapping.chainStages.push_back(100 + static_cast<int>(i));
            mapping.bodyAni = chain.front();
            mapping.bodySlotTag = "chr-motion-alias";
            mapping.confidence = MappingConfidence::Reconstructed;
            mapping.chainEvidence = stemOf(chain.front());
            mapping.evidence += "; body: named CHR motion alias (inferred)";
            break;
        }
    }
    // BackStep *is* the CHR's [back motion], JumpPowerUp its [jump motion]; a
    // buff skill has no dedicated motion at all and the client plays the generic
    // cast pose. The slot semantics are the only evidence here, so the row is
    // reported as reconstructed rather than as an exe-derived chain.
    if (mapping.bodyChain.empty() && mapping.bodyAni.empty() && !mapping.passive) {
        static const struct {
            const char *needle;
            const char *tag;
        } kBaseAliases[] = {
            {"backstep", "[back motion]"}, {"stepback", "[back motion]"},
            {"jump", "[jump motion]"},     {"leap", "[jump motion]"},
            {"dashattack", "[dashattack motion]"}, {"sit", "[sit motion]"},
        };
        std::string baseMotion;
        for (const auto &alias : kBaseAliases) {
            if (skillStem.find(alias.needle) == std::string::npos) continue;
            const auto found = jobIndex.baseMotions.find(alias.tag);
            if (found == jobIndex.baseMotions.end()) continue;
            baseMotion = found->second;
            break;
        }
        // Buff skills: nothing else resolved for them, so the generic cast pose
        // is what the characters actually show. It is a stand-in pose, not the
        // skill motion, so it never becomes bodyAni and never changes the grade.
        if (baseMotion.empty() && mapping.effects.empty()) {
            const auto found = jobIndex.baseMotions.find("[buff motion]");
            if (found != jobIndex.baseMotions.end()) baseMotion = found->second;
        }
        if (!baseMotion.empty()) {
            mapping.bodyAni = baseMotion;
            mapping.bodyChain = {baseMotion};
            mapping.chainStages = {100};
            mapping.bodySlotTag = "chr-base-motion";
            mapping.confidence = MappingConfidence::Reconstructed;
            mapping.chainEvidence = stemOf(baseMotion);
            mapping.evidence += "; body: CHR base motion slot (slot semantics, inferred)";
        }
    }

    // --- effect layer timing ------------------------------------------------
    // When a layer appears is source data only while the body ANI carries an
    // .als sidecar: [add] <frame> <layer> <uniqueName> names a parent frame and
    // the frame table turns that frame into milliseconds. 1031 ships sidecars
    // for the male subclasses and for most passive objects, but not for the
    // female fighter or the plain swordman, so those rows fall back to the
    // release-stage word in each file stem and say so.
    {
        const auto durationOf = [&](const std::string &path) {
            try {
                const auto animation = assets_.animation(path);
                double total = 0;
                for (const auto &frame : animation->frames) total += std::max(1, frame.duration);
                return total;
            } catch (const std::exception &) {
                return 0.0;
            }
        };
        const auto loops = [&](const std::string &path) {
            try {
                return assets_.animation(path)->globals.value("0", false);
            } catch (const std::exception &) {
                return false;
            }
        };
        std::vector<EffectLayerPlan> layers;
        if (!mapping.bodyAni.empty()) {
            try {
                const auto plan = animationEffectEvents(pvf_, assets_, mapping.bodyAni);
                for (const auto &event : plan.events) {
                    if (event.kind == EffectEventKind::Remove) continue;
                    EffectLayerPlan layer;
                    layer.path = event.animation;
                    layer.stage = effectStageOrder(stemOf(event.animation));
                    layer.lifeMs = durationOf(event.animation);
                    layer.loop = loops(event.animation);
                    layer.timed = true;
                    layer.alsFrame = event.frame;
                    layer.alsLayer = event.layer;
                    layer.instance = event.instance;
                    layer.offsetX = event.offsetX;
                    layer.offsetY = event.offsetY;
                    layer.offsetZ = event.offsetZ;
                    layer.source = "als";
                    layer.evidence = "ALS [add] frame " + std::to_string(event.frame) +
                                     " layer " + std::to_string(event.layer);
                    layers.push_back(std::move(layer));
                }
            } catch (const std::exception &) {
                // A malformed sidecar leaves every layer untimed rather than
                // fabricating an instant for it.
            }
        }
        std::vector<std::string> untimed;
        for (const auto &effect : mapping.effects) {
            const bool covered = std::any_of(layers.begin(), layers.end(),
                                             [&](const EffectLayerPlan &layer) {
                                                 return layer.path == effect;
                                             });
            if (!covered) untimed.push_back(effect);
        }
        std::stable_sort(untimed.begin(), untimed.end(),
                         [](const std::string &a, const std::string &b) {
                             const int left = effectStageOrder(stemOf(a));
                             const int right = effectStageOrder(stemOf(b));
                             if (left != right) return left < right;
                             return a < b;
                         });
        // The release chain already publishes the beats: ready -> slash1..5 ->
        // finish. Untimed layers spread over those beats in stem order, which
        // is the closest the files themselves get to a schedule. The spread is
        // normalised on the stage value, not on the list index, so a family with
        // 48 files still puts "ready" at the start and "finish" at the end.
        const size_t beats = std::max<size_t>(1, mapping.bodyChain.size());
        int minStage = INT_MAX, maxStage = INT_MIN;
        for (const auto &path : untimed) {
            const int stage = effectStageOrder(stemOf(path));
            minStage = std::min(minStage, stage);
            maxStage = std::max(maxStage, stage);
        }
        if (minStage == INT_MAX) minStage = maxStage = 0;
        for (size_t index = 0; index < untimed.size(); ++index) {
            EffectLayerPlan layer;
            layer.path = untimed[index];
            layer.stage = effectStageOrder(stemOf(untimed[index]));
            layer.lifeMs = durationOf(untimed[index]);
            layer.loop = loops(untimed[index]);
            if (maxStage > minStage && beats > 1) {
                // Chain beats win when they exist: they are the client's own
                // stage list, and the stage value only orders files inside a beat.
                const double beat = beats > 1
                    ? double(std::min(index, beats - 1)) / double(beats) : 0.0;
                const double within = double(layer.stage - minStage) / double(maxStage - minStage);
                layer.birthRatio = 0.85 * (beat + within / double(beats));
            } else if (maxStage > minStage) {
                layer.birthRatio = 0.85 * double(layer.stage - minStage) /
                                   double(maxStage - minStage);
            } else {
                layer.birthRatio = untimed.size() > 1
                    ? 0.75 * double(index) / double(untimed.size() - 1) : 0.0;
            }
            layer.source = untimed[index].rfind("passiveobject/", 0) == 0 ? "object" : "family";
            layer.evidence = "no ALS sidecar; release-stage order in file stem";
            layers.push_back(std::move(layer));
        }
        mapping.effectLayers = std::move(layers);
    }

    // --- persistent skill entities ------------------------------------------
    // A skill that keeps something on screen after the cast -- the nen orbs
    // orbiting the fighter, the lotus field, the swords hanging over the stage
    // -- is a passive object that loops a long animation, or an effect family
    // member with a 60-second loop (HundredSword/swordair1). The object names
    // the loop and its own folder names the attachments (SpiralNenTail1..4 are
    // the four orbs of the male fighter). Radius and spin exist in no file, so
    // they are reconstructed and labelled.
    {
        const bool atClass = jobIndex.chrStem.rfind("at", 0) == 0;
        const auto durationOf = [&](const std::string &path) {
            try {
                double total = 0;
                for (const auto &frame : assets_.animation(path)->frames)
                    total += std::max(1, frame.duration);
                return total;
            } catch (const std::exception &) {
                return 0.0;
            }
        };
        std::vector<std::string> candidates;
        const auto pushCandidate = [&](const std::string &stem) {
            const auto found = jobIndex.passiveObjects.find(stem);
            if (found == jobIndex.passiveObjects.end()) return;
            // The male subclasses share the base job folder and prefix their
            // objects with "at" (atspiralnen.obj). A female-fighter skill must
            // not borrow the male object just because the stems overlap.
            if (!atClass && stem.rfind("at", 0) == 0) return;
            if (std::find(candidates.begin(), candidates.end(), found->second) != candidates.end())
                return;
            candidates.push_back(found->second);
        };
        pushCandidate(skillStem);
        pushCandidate("at" + skillStem);
        for (const auto &[stem, path] : jobIndex.passiveObjects) {
            auto normalized = stem;
            if (normalized.size() > 3 && normalized.compare(0, 2, "at") == 0)
                normalized = normalized.substr(2);
            if (normalized.size() < 5) continue;
            if (skillStem == normalized || skillStem.rfind(normalized, 0) == 0 ||
                normalized.rfind(skillStem, 0) == 0)
                pushCandidate(stem);
        }
        const auto alreadyHas = [&](const std::string &path) {
            return std::any_of(mapping.persistents.begin(), mapping.persistents.end(),
                               [&](const PersistentPlan &plan) { return plan.path == path; });
        };
        // Variant names that differ only by the male "at" prefix or a trailing
        // serial are the same visual: spiralnen / atspiralnen, swordair1 /
        // swordair2. Playing both would double the orb or the sword array.
        const auto visualKey = [](std::string stem) {
            if (stem.size() > 2 && stem.compare(0, 2, "at") == 0) stem = stem.substr(2);
            while (!stem.empty() && std::isdigit(static_cast<unsigned char>(stem.back())))
                stem.pop_back();
            return stem;
        };
        const auto sameVisual = [&](const std::string &path) {
            const auto key = visualKey(stemOf(path));
            return std::any_of(mapping.persistents.begin(), mapping.persistents.end(),
                               [&](const PersistentPlan &plan) {
                                   return visualKey(stemOf(plan.path)) == key;
                               });
        };
        const auto consider = [&](const std::string &object, const std::string &motion) {
            if (motion.empty() || !pvf_.has(motion) || alreadyHas(motion)) return;
            double life = 0;
            bool loop = false;
            int topY = 0;
            size_t frameCount = 0;
            try {
                const auto animation = assets_.animation(motion);
                frameCount = animation->frames.size();
                for (const auto &frame : animation->frames) life += std::max(1, frame.duration);
                for (const auto &frame : animation->frames) topY = std::min(topY, frame.y);
                loop = animation->globals.value("0", false);
            } catch (const std::exception &) {
                return;
            }
            const auto stem = stemOf(motion);
            const bool namesOrb = stem.find("spiralnen") != std::string::npos ||
                                  object.find("spiralnen") != std::string::npos;
            const bool namesAir = stem.find("air") != std::string::npos ||
                                  stem.find("sword") != std::string::npos;
            const bool namesGround = stem.find("ground") != std::string::npos ||
                                     stem.find("field") != std::string::npos ||
                                     stem.find("area") != std::string::npos ||
                                     stem.find("stay") != std::string::npos;
            // A 60-second loop is how the client writes "keep this here".
            const bool longLoop = loop && (life >= 5000 || stem.find("loop") != std::string::npos);
            // A one-frame ground decal (NenFlower/Ground.ani) is a placed object,
            // not an impact: it has no loop bit because it never animates at all.
            const bool staticDecal = frameCount <= 1 && namesGround;
            PersistentPlan plan;
            plan.path = motion;
            plan.object = object;
            plan.loop = true;
            plan.lifeMs = 0; // stays until the skill action ends
            if (namesOrb) {
                plan.kind = PersistentKind::Orbit;
                // The male fighter keeps four orbs, the base job two. The tail
                // animations exist for both jobs, so the count is the job rule,
                // not the file count.
                plan.count = atClass ? 4 : 2;
                plan.radius = 62;
                plan.angularDegPerSec = 72;
                plan.phaseDeg = 180.0 / std::max(1, plan.count);
                plan.offsetY = -78;
                plan.evidence = "looping orb animation on a passive object; count from job "
                                "(male four, base two); radius/spin reconstructed";
            } else if (namesAir && longLoop) {
                plan.kind = PersistentKind::AirSword;
                // The release chain reserves one "move" stage per hanging
                // sword: HundredSwordMoveReady1..5 means five swords in the air,
                // and the caster then swings them one at a time.
                int stages = 0;
                for (const auto &[motionStem, resources] : jobIndex.motions) {
                    (void)resources;
                    if (motionStem.rfind(skillStem + "moveready", 0) == 0) ++stages;
                }
                plan.count = std::max(1, stages);
                plan.offsetY = std::min(-120.0, double(topY));
                plan.evidence = "looping air animation (" + std::to_string(int(life)) +
                                "ms); count from move stages; height from frame offset";
            } else if (longLoop || staticDecal) {
                plan.kind = PersistentKind::GroundField;
                plan.count = 1;
                plan.offsetY = 0;
                plan.evidence = staticDecal ? "single-frame ground decal placed for the skill duration"
                                            : "looping ground object motion kept for the skill duration";
            } else {
                return; // one-shot impact: already an effect layer
            }
            // Keep the flavour that belongs to this CHR: a male subclass wants
            // the at* twin, the base job wants the plain one.
            if (sameVisual(motion)) {
                if (plan.kind != PersistentKind::Orbit) return;
                const bool existingAt = [&]() {
                    for (const auto &other : mapping.persistents)
                        if (visualKey(stemOf(other.path)) == visualKey(stem))
                            return stemOf(other.path).rfind("at", 0) == 0;
                    return false;
                }();
                if (atClass == existingAt) return;
                mapping.persistents.erase(
                    std::remove_if(mapping.persistents.begin(), mapping.persistents.end(),
                                   [&](const PersistentPlan &other) {
                                       return visualKey(stemOf(other.path)) == visualKey(stem);
                                   }),
                    mapping.persistents.end());
            }
            mapping.persistents.push_back(std::move(plan));
        };
        for (const auto &object : candidates) {
            try {
                const auto view = pvf_.fieldView(object, {"[basic motion]", "[etc motion]"});
                for (const auto &value : view.values("[basic motion]")) {
                    if (!value.is_string()) continue;
                    const auto name = normalize(value.get<std::string>());
                    if (name.size() < 5 || name.compare(name.size() - 4, 4, ".ani") != 0) continue;
                    consider(object, resolveObjectRelative(jobIndex.baseJob, name));
                }
                // [etc motion] holds the placed parts of the same object: the
                // lotus field lies in NenFlowerBlast.obj's ground/line entries.
                for (const auto &value : view.values("[etc motion]")) {
                    if (!value.is_string()) continue;
                    const auto name = normalize(value.get<std::string>());
                    if (name.size() < 5 || name.compare(name.size() - 4, 4, ".ani") != 0) continue;
                    consider(object, resolveObjectRelative(jobIndex.baseJob, name));
                }
            } catch (const std::exception &) {
                continue;
            }
        }
        // The sword array of HundredSword is not an object motion: the caster's
        // state handler plays effect-family members directly and keeps the two
        // 60-second loops alive for the whole action.
        for (const auto &layer : mapping.effectLayers) {
            if (!layer.loop || layer.lifeMs < 5000 || alreadyHas(layer.path)) continue;
            if (sameVisual(layer.path)) continue;
            PersistentPlan plan;
            plan.path = layer.path;
            plan.kind = PersistentKind::AirSword;
            // One move stage per hanging sword (HundredSwordMoveReady1..5).
            int stages = 0;
            for (const auto &[motionStem, resources] : jobIndex.motions) {
                (void)resources;
                if (motionStem.rfind(skillStem + "moveready", 0) == 0) ++stages;
            }
            plan.count = std::max(1, stages);
            plan.loop = true;
            plan.offsetY = -160;
            plan.evidence = "effect-family loop longer than the action (" +
                            std::to_string(int(layer.lifeMs)) + "ms); held as a persistent layer";
            mapping.persistents.push_back(std::move(plan));
        }
    }

    // --- stand-in pose for a body-less row ----------------------------------
    if (mapping.bodyAni.empty() && !mapping.passive) {
        const auto found = jobIndex.baseMotions.find("[buff motion]");
        if (found != jobIndex.baseMotions.end()) {
            mapping.fallbackPose = found->second;
            mapping.evidence += "; pose: generic CHR buff pose (stand-in only, not graded)";
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
    // A row whose only motion is the generic buff pose still shows a character,
    // so it keeps its B grade, but the audit marks it as a stand-in pose.
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
