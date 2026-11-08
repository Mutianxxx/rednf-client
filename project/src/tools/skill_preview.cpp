#include "dnf/appearance.hpp"
#include "dnf/character.hpp"
#include "dnf/content_profile.hpp"
#include "dnf/entry.hpp"
#include "dnf/renderer.hpp"
#include <SDL.h>
#include <algorithm>
#include <atomic>
#include <cctype>
#include <chrono>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <optional>
#include <thread>
#include <tuple>

using namespace dnf;
namespace fs = std::filesystem;

namespace {
constexpr const char *expectedPvfSha256 = "d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d";
constexpr int uiWidth = 1280;
constexpr int uiHeight = 720;

struct MotionCandidate {
    std::string path, kind, sourcePath, sourceTag, match, sha256;
    size_t offset = 0, valueIndex = 0;
};
struct PreviewSkill {
    SkillKey key;
    std::string name, type, path, sha256;
    std::vector<MotionCandidate> motions;
    Json directReferences = Json::array();
    Json squirrelEffectReferences = Json::array();
    std::vector<Json> repEvents;
};
struct PreviewJob {
    int id = -1;
    std::string key, name, chrPath, chrSha256;
    const CharacterDefinition *definition = nullptr;
    std::vector<PreviewSkill> skills;
};
struct LoadState {
    std::atomic<int> stage{0};
    std::atomic<bool> finished{false};
    std::mutex messageMutex;
    std::string message = "Preparing 1031 PVF";
    std::string error;
    std::unique_ptr<Pvf> pvf;
    std::unique_ptr<Assets> assets;
    std::unique_ptr<CharacterCatalog> characters;
    std::vector<PreviewJob> jobs;
    Json mapping;
};

std::string stem(const std::string &path) { return normalize(fs::u8path(path).stem().u8string()); }
std::string ext(const std::string &path) { return normalize(fs::u8path(path).extension().u8string()); }
std::string firstString(const Script &script, const std::string &tag, const std::string &fallback) {
    const auto values = script.values(tag);
    return !values.empty() && values[0].is_string() ? values[0].get<std::string>() : fallback;
}
std::string kindOf(const CharacterSkillDefinition &skill) {
    if (skill.kind == SkillSourceKind::Active) return "active";
    if (skill.kind == SkillSourceKind::Passive) return "passive";
    return "unknown";
}
bool supportedReference(const std::string &path) {
    const auto suffix = ext(path);
    return suffix == ".ani" || suffix == ".act" || suffix == ".als" || suffix == ".nut" ||
           suffix == ".ptl" || suffix == ".atk" || suffix == ".obj" || suffix == ".img";
}
bool motionTag(const std::string &tag) { return normalize(tag).find("motion") != std::string::npos; }
bool relatedStem(const std::string &skillStem, const std::string &resourceStem, std::string &match) {
    if (skillStem.size() < 5 || resourceStem.size() < 5) return false;
    if (skillStem == resourceStem) { match = "exact-basename"; return true; }
    if (resourceStem.rfind(skillStem, 0) == 0) { match = "skill-name-prefix"; return true; }
    return false;
}
void setStage(LoadState &state, int stage, const std::string &message) {
    { std::lock_guard<std::mutex> lock(state.messageMutex); state.message = message; }
    state.stage.store(stage, std::memory_order_release);
}
void addMotionJson(Json &json, const MotionCandidate &motion) {
    json.push_back({{"path", motion.path}, {"kind", motion.kind}, {"source_path", motion.sourcePath},
        {"source_tag", motion.sourceTag}, {"field_offset", motion.offset},
        {"value_index", motion.valueIndex}, {"match", motion.match}, {"pvf_member_sha256", motion.sha256}});
}
bool hasMotion(const PreviewSkill &skill, const std::string &path, const std::string &kind) {
    return std::any_of(skill.motions.begin(), skill.motions.end(), [&](const auto &item) {
        return item.path == path && item.kind == kind;
    });
}

bool identifierChar(char ch) {
    const auto value = static_cast<unsigned char>(ch);
    return std::isalnum(value) != 0 || ch == '_';
}

std::string skillEffectLoaderName(const std::string &jobKey) {
    std::string output = "sq_LoadSkillEffect_";
    bool upper = true;
    for (char ch : jobKey) {
        if (ch == '[' || ch == ']') continue;
        if (!identifierChar(ch)) { upper = true; continue; }
        const auto value = static_cast<unsigned char>(ch);
        output += upper ? static_cast<char>(std::toupper(value)) : ch;
        upper = false;
    }
    return output;
}

std::map<std::string, int> skillConstants(const std::string &source) {
    std::map<std::string, int> result;
    size_t lineStart = 0;
    while (lineStart < source.size()) {
        const auto lineEnd = source.find_first_of("\r\n", lineStart);
        const auto end = lineEnd == std::string::npos ? source.size() : lineEnd;
        size_t cursor = lineStart;
        while (cursor < end && std::isspace(static_cast<unsigned char>(source[cursor]))) ++cursor;
        if (source.compare(cursor, 6, "SKILL_") == 0) {
            const size_t nameStart = cursor;
            while (cursor < end && identifierChar(source[cursor])) ++cursor;
            const auto name = source.substr(nameStart, cursor - nameStart);
            while (cursor < end && std::isspace(static_cast<unsigned char>(source[cursor]))) ++cursor;
            if (source.compare(cursor, 2, "<-") == 0) {
                cursor += 2;
                while (cursor < end && std::isspace(static_cast<unsigned char>(source[cursor]))) ++cursor;
                const size_t numberStart = cursor;
                while (cursor < end && std::isdigit(static_cast<unsigned char>(source[cursor]))) ++cursor;
                if (cursor > numberStart) {
                    try { result[name] = std::stoi(source.substr(numberStart, cursor - numberStart)); }
                    catch (const std::exception &) { }
                }
            }
        }
        lineStart = lineEnd == std::string::npos ? source.size() : lineEnd + 1;
        if (lineEnd != std::string::npos && source[lineEnd] == '\r' && lineStart < source.size() && source[lineStart] == '\n')
            ++lineStart;
    }
    return result;
}

size_t matchingBrace(const std::string &source, size_t open) {
    int depth = 0;
    bool lineComment = false, blockComment = false, escaped = false;
    char quote = 0;
    for (size_t i = open; i < source.size(); ++i) {
        const char ch = source[i], next = i + 1 < source.size() ? source[i + 1] : 0;
        if (lineComment) {
            if (ch == '\n' || ch == '\r') lineComment = false;
            continue;
        }
        if (blockComment) {
            if (ch == '*' && next == '/') { blockComment = false; ++i; }
            continue;
        }
        if (quote) {
            if (escaped) escaped = false;
            else if (ch == '\\') escaped = true;
            else if (ch == quote) quote = 0;
            continue;
        }
        if (ch == '/' && next == '/') { lineComment = true; ++i; continue; }
        if (ch == '/' && next == '*') { blockComment = true; ++i; continue; }
        if (ch == '"' || ch == '\'') { quote = ch; continue; }
        if (ch == '{') ++depth;
        else if (ch == '}' && --depth == 0) return i;
    }
    return std::string::npos;
}

std::optional<std::pair<size_t, size_t>> functionBody(const std::string &source, const std::string &name) {
    const auto signature = "function " + name;
    size_t search = 0;
    while ((search = source.find(signature, search)) != std::string::npos) {
        if (search > 0 && identifierChar(source[search - 1])) { search += signature.size(); continue; }
        const auto open = source.find('{', search + signature.size());
        if (open == std::string::npos) return std::nullopt;
        const auto close = matchingBrace(source, open);
        if (close == std::string::npos) return std::nullopt;
        return std::make_pair(open, close);
    }
    return std::nullopt;
}

bool branchMatchesSkill(const std::string &source, size_t token) {
    size_t cursor = token;
    while (cursor > 0 && std::isspace(static_cast<unsigned char>(source[cursor - 1]))) --cursor;
    if (cursor < 2 || source.compare(cursor - 2, 2, "==") != 0) return false;
    cursor -= 2;
    while (cursor > 0 && std::isspace(static_cast<unsigned char>(source[cursor - 1]))) --cursor;
    const size_t end = cursor;
    while (cursor > 0 && identifierChar(source[cursor - 1])) --cursor;
    return source.compare(cursor, end - cursor, "skillIndex") == 0;
}

std::string stringArgumentAfterComma(const std::string &source, size_t open, size_t limit, size_t &end) {
    const auto comma = source.find(',', open + 1);
    if (comma == std::string::npos || comma >= limit) return {};
    size_t cursor = comma + 1;
    while (cursor < limit && std::isspace(static_cast<unsigned char>(source[cursor]))) ++cursor;
    if (cursor >= limit || source[cursor] != '"') return {};
    ++cursor;
    std::string output;
    bool escaped = false;
    for (; cursor < limit; ++cursor) {
        const char ch = source[cursor];
        if (escaped) { output += ch; escaped = false; }
        else if (ch == '\\') escaped = true;
        else if (ch == '"') { end = cursor + 1; return output; }
        else output += ch;
    }
    return {};
}

struct SquirrelLoader {
    std::string path, hash, function, source;
    size_t begin = 0, end = 0;
    std::map<std::string, int> constants;
};

std::map<int, std::vector<SquirrelLoader>> indexSquirrelLoaders(Pvf &pvf, const std::vector<PreviewJob> &jobs,
                                                                 size_t &nutFileCount) {
    std::map<int, std::vector<SquirrelLoader>> output;
    const auto paths = pvf.paths("sqr/", ".nut");
    nutFileCount = paths.size();
    for (const auto &path : paths) {
        const auto raw = pvf.read(path);
        std::string source(raw.begin(), raw.end());
        for (const auto &job : jobs) {
            const auto function = skillEffectLoaderName(job.key);
            const auto body = functionBody(source, function);
            if (!body) continue;
            output[job.id].push_back({path, sha256(raw), function, source, body->first, body->second,
                                      skillConstants(source)});
        }
    }
    return output;
}

std::string resolveSquirrelAnimationPath(Pvf &pvf, const PreviewJob &job, const std::string &literal) {
    auto path = normalize(literal);
    if (pvf.has(path)) return path;
    if (job.definition) {
        const auto root = fs::u8path(job.definition->source.script.path).parent_path().u8string();
        const auto relative = normalize(root + "/" + literal);
        if (pvf.has(relative)) return relative;
        return relative;
    }
    return path;
}

void appendSquirrelAnimationCandidates(Pvf &pvf, const PreviewJob &job, PreviewSkill &skill,
                                      const std::vector<SquirrelLoader> &loaders, size_t &declaredCalls,
                                      size_t &resolvedCalls) {
    for (const auto &loader : loaders) {
        for (const auto &constant : loader.constants) {
            if (constant.second != skill.key.skillId) continue;
            size_t search = loader.begin + 1;
            while ((search = loader.source.find(constant.first, search)) != std::string::npos && search < loader.end) {
                if (!branchMatchesSkill(loader.source, search)) { search += constant.first.size(); continue; }
                const auto open = loader.source.find('{', search + constant.first.size());
                if (open == std::string::npos || open >= loader.end) break;
                const auto close = matchingBrace(loader.source, open);
                if (close == std::string::npos || close > loader.end) break;
                size_t callSearch = open + 1, callIndex = 0;
                while ((callSearch = loader.source.find("sq_LoadSkillEffectAni", callSearch)) != std::string::npos && callSearch < close) {
                    const auto callOpen = loader.source.find('(', callSearch + std::string("sq_LoadSkillEffectAni").size());
                    if (callOpen == std::string::npos || callOpen >= close) break;
                    size_t callEnd = callOpen + 1;
                    const auto literal = stringArgumentAfterComma(loader.source, callOpen, close, callEnd);
                    if (!literal.empty() && ext(literal) == ".ani") {
                        ++declaredCalls;
                        const auto path = resolveSquirrelAnimationPath(pvf, job, literal);
                        const bool exists = pvf.has(path);
                        const auto memberHash = exists ? sha256(pvf.read(path)) : std::string();
                        Json reference = { {"kind", "sqr-declared-effect-animation"}, {"path", path},
                            {"raw_literal", literal}, {"resolved", exists}, {"source_path", loader.path},
                            {"source_sha256", loader.hash}, {"source_offset", callSearch},
                            {"branch_offset", open}, {"call_index", callIndex},
                            {"loader_function", loader.function}, {"skill_constant", constant.first},
                            {"skill_constant_value", constant.second}, {"source_tag", "sq_LoadSkillEffectAni"},
                            {"pvf_member_sha256", memberHash},
                            {"semantics", "script declaration candidate; native dispatch and effect timing unverified"} };
                        skill.squirrelEffectReferences.push_back(reference);
                        if (exists) {
                            ++resolvedCalls;
                            if (!hasMotion(skill, path, "sqr-declared-effect-animation-candidate"))
                                skill.motions.push_back({path, "sqr-declared-effect-animation-candidate", loader.path,
                                    "sq_LoadSkillEffectAni", "script-declared; native dispatch unverified", memberHash,
                                    callSearch, callIndex});
                        }
                    }
                    ++callIndex;
                    callSearch = std::max(callSearch + 1, callEnd);
                }
                search = close + 1;
            }
        }
    }
}

Json buildMapping(Pvf &pvf, CharacterCatalog &catalog, std::vector<PreviewJob> &jobs) {
    Json output = {{"schema", 1},
        {"purpose", "1031 PVF preview mapping; source candidates are not native execution proof"},
        {"source", {{"pvf_path", pvf.path().u8string()}, {"pvf_sha256", pvf.identity()},
                     {"client", "Qingfeng 1031"}}},
        {"rep", {{"files", 0}, {"skill_key_records", 0}, {"mapped_records", 0},
                  {"unmapped_slots", 0}, {"zero_skill_key_files", 0}}},
        {"squirrel", {{"nut_files_examined", 0}, {"loader_functions_found", 0},
                       {"declared_animation_calls", 0}, {"resolved_animation_candidates", 0}}},
        {"jobs", Json::array()}, {"mapping_diagnostics", Json::array()}};
    std::map<SkillKey, std::pair<size_t, size_t>> skillIndices;
    size_t registeredSkillRows = 0;

    for (const auto &definition : catalog.definitions) {
        if (definition.registration.id < 0 || definition.runtimeDeferredByUser) continue;
        PreviewJob job;
        job.id = definition.registration.id;
        job.key = definition.job;
        job.name = definition.growtypeNames.empty() || !definition.growtypeNames[0].is_string()
            ? definition.job : definition.growtypeNames[0].get<std::string>();
        job.chrPath = definition.source.script.path;
        job.chrSha256 = definition.source.script.source.value("member_sha256", "");
        job.definition = &definition;

        for (const auto &registration : definition.skills.entries) {
            ++registeredSkillRows;
            if (!registration.exists || !definition.skills.unique(registration.id)) {
                output["mapping_diagnostics"].push_back({{"kind", registration.exists ? "duplicate_skill_id" : "missing_registered_skill"},
                    {"job_id", job.id}, {"skill_id", registration.id}, {"path", registration.path}});
                continue;
            }
            try {
                const auto &source = catalog.skillDefinition({job.id, registration.id});
                PreviewSkill skill;
                skill.key = {job.id, registration.id};
                skill.name = firstString(source.source.script, "[name]", fs::u8path(registration.path).stem().u8string());
                skill.type = kindOf(source);
                skill.path = registration.path;
                skill.sha256 = source.source.script.source.value("member_sha256", "");
                const auto skillStem = stem(skill.path);

                for (const auto &field : source.source.script.fields) {
                    for (size_t index = 0; index < field.values.size(); ++index) {
                        if (!field.values[index].is_string()) continue;
                        const auto value = field.values[index].get<std::string>();
                        if (!supportedReference(value)) continue;
                        const auto path = normalize(value);
                        const bool exists = pvf.has(path);
                        const auto hash = exists ? sha256(pvf.read(path)) : std::string();
                        skill.directReferences.push_back({{"field", field.tag}, {"offset", field.offset},
                            {"value_index", index}, {"path", path}, {"exists", exists}, {"pvf_member_sha256", hash}});
                        if (ext(path) == ".ani" && exists && !hasMotion(skill, path, "direct-skl-animation"))
                            skill.motions.push_back({path, "direct-skl-animation", skill.path, field.tag,
                                "direct-reference", hash, field.offset, index});
                    }
                }

                for (const auto &resource : definition.resources) {
                    const auto suffix = ext(resource.path);
                    const bool animation = motionTag(resource.tag) && suffix == ".ani";
                    const bool attack = normalize(resource.tag).find("attack info") != std::string::npos && suffix == ".atk";
                    if (!resource.exists || (!animation && !attack)) continue;
                    std::string match;
                    if (!relatedStem(skillStem, stem(resource.path), match)) continue;
                    const auto hash = sha256(pvf.read(resource.path));
                    if (animation && !hasMotion(skill, resource.path, "chr-motion-candidate"))
                        skill.motions.push_back({resource.path, "chr-motion-candidate", job.chrPath,
                            resource.tag, match, hash, resource.fieldOffset, resource.valueIndex});
                    if (attack) skill.directReferences.push_back({{"field", resource.tag},
                        {"offset", resource.fieldOffset}, {"value_index", resource.valueIndex},
                        {"path", resource.path}, {"exists", true}, {"match", match},
                        {"pvf_member_sha256", hash}});
                }
                skillIndices[skill.key] = {jobs.size(), job.skills.size()};
                job.skills.push_back(std::move(skill));
            } catch (const std::exception &error) {
                output["mapping_diagnostics"].push_back({{"kind", "skill_source_parse_failed"},
                    {"job_id", job.id}, {"skill_id", registration.id}, {"path", registration.path},
                    {"reason", error.what()}});
            }
        }
        jobs.push_back(std::move(job));
    }

    size_t nutFileCount = 0, declaredAnimationCalls = 0, resolvedAnimationCandidates = 0;
    const auto squirrelLoaders = indexSquirrelLoaders(pvf, jobs, nutFileCount);
    size_t loaderFunctionCount = 0;
    for (const auto &entry : squirrelLoaders) loaderFunctionCount += entry.second.size();
    for (auto &job : jobs) {
        const auto found = squirrelLoaders.find(job.id);
        if (found == squirrelLoaders.end()) continue;
        for (auto &skill : job.skills)
            appendSquirrelAnimationCandidates(pvf, job, skill, found->second, declaredAnimationCalls,
                                               resolvedAnimationCandidates);
    }
    output["squirrel"] = {{"nut_files_examined", nutFileCount}, {"loader_functions_found", loaderFunctionCount},
        {"declared_animation_calls", declaredAnimationCalls},
        {"resolved_animation_candidates", resolvedAnimationCandidates},
        {"semantics", "Literal animation declarations in job skill-effect loader branches; original dispatch and runtime timing are not proven"}};

    auto jobIdFor = [&](const std::string &folder) {
        const auto target = normalize(folder + "skill");
        for (const auto &entry : catalog.skillLists.entries)
            if (entry.exists && stem(entry.path) == target) return entry.id;
        return -1;
    };
    std::vector<std::string> replayPaths = pvf.paths("etc/pvppracticecombo/replay/", ".rep");
    const auto linksystem = pvf.paths("etc/linksystem/striker/", ".rep");
    replayPaths.insert(replayPaths.end(), linksystem.begin(), linksystem.end());
    std::sort(replayPaths.begin(), replayPaths.end());
    for (const auto &path : replayPaths) {
        const auto folder = fs::u8path(path).parent_path().filename().u8string();
        const int jobId = jobIdFor(folder);
        const auto replay = pvf.script(path);
        auto valuesFor = [&](const std::string &tag) {
            for (const auto &field : replay.fields)
                if (normalize(field.tag) == normalize(tag)) return field.values;
            return Json::array();
        };
        std::map<int, std::pair<int, std::string>> slots;
        for (const auto *tag : {"[quick skill]", "[quick skill expend]"}) {
            const auto values = valuesFor(tag);
            if (values.size() % 4) continue;
            for (size_t i = 0; i + 3 < values.size(); i += 4) {
                if (values[i].is_number_integer() && values[i + 1].is_number_integer())
                    slots[values[i].get<int>()] = {values[i + 1].get<int>(), tag};
            }
        }
        const auto records = valuesFor("[skill key]");
        if (records.empty() || !records[0].is_number_integer()) continue;
        const auto count = records[0].get<int>();
        if (count < 0 || records.size() != size_t(1 + count * 8)) continue;
        output["rep"]["files"] = output["rep"]["files"].get<int>() + 1;
        if (!count) output["rep"]["zero_skill_key_files"] = output["rep"]["zero_skill_key_files"].get<int>() + 1;
        const auto repHash = replay.source.value("member_sha256", "");
        for (int ordinal = 0; ordinal < count; ++ordinal) {
            const size_t at = 1 + size_t(ordinal) * 8;
            if (!records[at + 1].is_number_integer()) continue;
            const int slot = records[at + 1].get<int>();
            const auto binding = slots.find(slot);
            Json event = {{"rep_path", path}, {"rep_sha256", repHash}, {"ordinal", ordinal},
                {"raw_record", Json::array()}, {"slot_code", slot},
                {"semantics", "shortcut input candidate; release success and timing unverified"}};
            for (size_t i = 0; i < 8; ++i) event["raw_record"].push_back(records[at + i]);
            output["rep"]["skill_key_records"] = output["rep"]["skill_key_records"].get<int>() + 1;
            if (binding == slots.end() || jobId < 0) {
                output["rep"]["unmapped_slots"] = output["rep"]["unmapped_slots"].get<int>() + 1;
                continue;
            }
            const SkillKey key{jobId, binding->second.first};
            const auto index = skillIndices.find(key);
            if (index == skillIndices.end()) {
                output["rep"]["unmapped_slots"] = output["rep"]["unmapped_slots"].get<int>() + 1;
                continue;
            }
            auto &skill = jobs[index->second.first].skills[index->second.second];
            event["binding"] = {{"job_id", jobId}, {"skill_id", key.skillId},
                {"section", binding->second.second}, {"skill_path", skill.path}, {"skill_name", skill.name}};
            skill.repEvents.push_back(std::move(event));
            output["rep"]["mapped_records"] = output["rep"]["mapped_records"].get<int>() + 1;
        }
    }

    for (const auto &job : jobs) {
        Json jobJson = {{"job_id", job.id}, {"job_key", job.key}, {"display_name", job.name},
            {"chr_path", job.chrPath}, {"chr_sha256", job.chrSha256}, {"skills", Json::array()}};
        for (const auto &skill : job.skills) {
            const bool hasResolvedSquirrelAnimation = std::any_of(skill.squirrelEffectReferences.begin(),
                skill.squirrelEffectReferences.end(), [](const auto &reference) { return reference.value("resolved", false); });
            const bool hasCharacterAnimation = std::any_of(skill.motions.begin(), skill.motions.end(),
                [](const auto &motion) { return motion.kind == "chr-motion-candidate"; });
            Json item = {{"skill_id", skill.key.skillId}, {"name", skill.name}, {"type", skill.type},
                {"skl_path", skill.path}, {"skl_sha256", skill.sha256},
                {"mapping_state", hasResolvedSquirrelAnimation ? "script-declared-animation-candidate" :
                    hasCharacterAnimation ? "inferred-by-resource-name" : "no-animation-candidate"},
                {"native_controller", "not proven by this preview"}, {"direct_references", skill.directReferences},
                {"squirrel_effect_references", skill.squirrelEffectReferences},
                {"motions", Json::array()}, {"rep_events", Json::array()}};
            for (const auto &motion : skill.motions) addMotionJson(item["motions"], motion);
            for (const auto &event : skill.repEvents) item["rep_events"].push_back(event);
            jobJson["skills"].push_back(std::move(item));
        }
        output["jobs"].push_back(std::move(jobJson));
    }
    output["job_count"] = jobs.size();
    output["registered_skill_rows"] = registeredSkillRows;
    output["skill_count"] = 0;
    output["animation_candidate_count"] = 0;
    for (const auto &job : output["jobs"]) for (const auto &skill : job["skills"]) {
        output["skill_count"] = output["skill_count"].get<int>() + 1;
        output["animation_candidate_count"] = output["animation_candidate_count"].get<int>() + int(skill["motions"].size());
    }
    output["verification"] = {{"pvf_sha256_matched_expected", pvf.identity() == expectedPvfSha256},
        {"rep_skill_key_records_match_prior_audit", output["rep"]["files"] == 484 &&
            output["rep"]["skill_key_records"] == 1817 && output["rep"]["unmapped_slots"] == 0},
        {"semantics", "Resource-name matches are inferred candidates; native SQR/NUT execution, state transitions and hit judgment remain unverified"}};
    return output;
}

void loadSources(const ContentProfile &profile, const fs::path &outputDirectory, LoadState &state) {
    try {
        setStage(state, 0, "Verifying 1031 PVF and parsing registry");
        state.pvf = std::make_unique<Pvf>(profile.pvfPath, expectedPvfSha256);
        setStage(state, 1, "Indexing static NPK resources");
        state.assets = std::make_unique<Assets>(profile.resourceRoots, *state.pvf);
        setStage(state, 2, "Loading job CHR and registered SKL files");
        state.characters = std::make_unique<CharacterCatalog>(*state.pvf);
        setStage(state, 3, "Mapping current PVF REP input records");
        state.mapping = buildMapping(*state.pvf, *state.characters, state.jobs);
        fs::create_directories(outputDirectory);
        writeJson(outputDirectory / "skill-preview-map.json", state.mapping);
        setStage(state, 4, "Mapping complete; opening preview");
    } catch (const std::exception &error) {
        state.error = error.what();
    }
    state.finished.store(true, std::memory_order_release);
}

class LoadingSplash {
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
  public:
    LoadingSplash() {
        window_ = SDL_CreateWindow("1031 PVF 技能映射 | 初始化", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   700, 260, SDL_WINDOW_SHOWN);
        if (!window_) throw std::runtime_error(SDL_GetError());
        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer_) renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
        if (!renderer_) throw std::runtime_error(SDL_GetError());
    }
    ~LoadingSplash() {
        if (renderer_) SDL_DestroyRenderer(renderer_);
        if (window_) SDL_DestroyWindow(window_);
    }
    void draw(int stage, const std::string &message, uint32_t tick) {
        SDL_SetWindowTitle(window_, ("1031 PVF 技能映射 | " + message).c_str());
        SDL_SetRenderDrawColor(renderer_, 18, 24, 30, 255);
        SDL_RenderClear(renderer_);
        SDL_Rect bar{54, 132, 592, 22};
        SDL_SetRenderDrawColor(renderer_, 43, 57, 62, 255);
        SDL_RenderFillRect(renderer_, &bar);
        for (int i = 0; i < 4; ++i) {
            SDL_Rect segment{bar.x + i * 148, bar.y, 144, bar.h};
            SDL_SetRenderDrawColor(renderer_, i < stage ? 46 : 59, i < stage ? 157 : 70, i < stage ? 125 : 76, 255);
            SDL_RenderFillRect(renderer_, &segment);
        }
        SDL_Rect moving{bar.x + int((tick / 8) % 560), bar.y + 3, 32, 16};
        SDL_SetRenderDrawColor(renderer_, 228, 190, 96, 255);
        SDL_RenderFillRect(renderer_, &moving);
        SDL_RenderPresent(renderer_);
    }
    void close() {
        if (renderer_) { SDL_DestroyRenderer(renderer_); renderer_ = nullptr; }
        if (window_) { SDL_DestroyWindow(window_); window_ = nullptr; }
    }
};

std::vector<std::string> wrapUtf8(Renderer &renderer, const std::string &text, int maxWidth, int size) {
    std::vector<std::string> lines;
    std::string line;
    for (size_t i = 0; i < text.size();) {
        const uint8_t first = uint8_t(text[i]);
        const size_t bytes = first < 0x80 ? 1 : first < 0xe0 ? 2 : first < 0xf0 ? 3 : 4;
        const auto part = text.substr(i, bytes);
        if (!line.empty() && renderer.textWidth(line + part, size) > maxWidth) {
            lines.push_back(line);
            line.clear();
        }
        line += part;
        i += bytes;
    }
    if (!line.empty()) lines.push_back(line);
    return lines;
}
int drawWrapped(Renderer &renderer, const std::string &text, int x, int y, int width, int size,
                SDL_Color color, int maxLines = 8) {
    const auto lines = wrapUtf8(renderer, text, width, size);
    const auto count = std::min<int>(int(lines.size()), maxLines);
    for (int i = 0; i < count; ++i) renderer.text(lines[size_t(i)], float(x), float(y + i * (size + 4)), size, color);
    if (int(lines.size()) > maxLines) renderer.text("...", float(x), float(y + count * (size + 4)), size, color);
    return (count + (int(lines.size()) > maxLines ? 1 : 0)) * (size + 4);
}
void archiveHashes(const Assets &assets, Json &output) {
    std::map<std::string, Json> unique;
    for (const auto &entry : assets.reads().items()) {
        if (!entry.value().contains("archive")) continue;
        const auto path = entry.value().at("archive").get<std::string>();
        if (!unique.count(path)) unique[path] = {{"path", path}, {"sha256", sha256File(fs::u8path(path))}};
    }
    output = Json::array();
    for (const auto &entry : unique) output.push_back(entry.second);
}
void writeRunReport(const fs::path &path, const Pvf &pvf, const Assets &assets,
                    const Renderer &renderer, const Json &mapping, const std::string &lastMotion) {
    Json archives;
    archiveHashes(assets, archives);
    const auto mapBytes = mapping.dump();
    writeJson(path, {{"pvf_sha256", pvf.identity()}, {"preview_map_sha256", sha256(Bytes(mapBytes.begin(), mapBytes.end()))},
        {"last_motion", lastMotion}, {"consumed_static_archives", archives},
        {"asset_errors", assets.errors}, {"render_errors", renderer.errors},
        {"unsupported_render_data", renderer.unsupported}, {"ani_render_policy",renderer.renderProfileReport()},
        {"evidence_boundary", "visual preview only; no native skill controller, attack acceptance or damage claim"}});
}

int run(int argc, char **argv) {
    fs::path profilePath, outputDirectory = "reports/skill-preview-1031";
    bool auditOnly = false;
    auto aniRenderProfile = ani_render::RenderProfile::Legacy1031;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--content-profile" && i + 1 < argc) profilePath = fs::u8path(argv[++i]);
        else if (arg == "--output" && i + 1 < argc) outputDirectory = fs::u8path(argv[++i]);
        else if (arg == "--audit") auditOnly = true;
        else if (arg == "--ani-render-profile" && i + 1 < argc) {
            const std::string value = argv[++i];
            if (value == "legacy1031") aniRenderProfile = ani_render::RenderProfile::Legacy1031;
            else if (value == "inferred60us1031") aniRenderProfile = ani_render::RenderProfile::Inferred60Us1031;
            else throw std::runtime_error("Unknown ANI render profile: " + value);
        }
        else throw std::runtime_error("Unknown argument: " + arg);
    }
    if (profilePath.empty()) profilePath = fs::absolute("content-profile.json");
    else profilePath = fs::absolute(profilePath);
    if (!outputDirectory.is_absolute()) outputDirectory = fs::absolute(outputDirectory);
    const auto profile = resolveContentProfile(profilePath, profilePath.parent_path());
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) throw std::runtime_error(SDL_GetError());
    try {
        LoadingSplash splash;
        LoadState loaded;
        std::thread worker(loadSources, std::cref(profile), std::cref(outputDirectory), std::ref(loaded));
        const uint32_t started = SDL_GetTicks();
        while (!loaded.finished.load(std::memory_order_acquire)) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) { (void)event; }
            std::string message;
            { std::lock_guard<std::mutex> lock(loaded.messageMutex); message = loaded.message; }
            splash.draw(loaded.stage.load(std::memory_order_acquire), message, SDL_GetTicks() - started);
            SDL_Delay(16);
        }
        worker.join();
        if (!loaded.error.empty()) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "1031 PVF 技能映射失败", loaded.error.c_str(), nullptr);
            throw std::runtime_error(loaded.error);
        }
        if (auditOnly) {
            std::cout << loaded.mapping.dump(2) << '\n';
            splash.close();
            SDL_Quit();
            return 0;
        }

        splash.close();
        Renderer renderer(*loaded.assets, RendererOptions{"1031 PVF 技能预览映射", uiWidth, uiHeight, true, true, true});
        renderer.setRenderProfile(aniRenderProfile);
        int jobIndex = 0, skillIndex = 0, scroll = 0, motionIndex = 0, appearanceJob = -1;
        bool playing = false, running = true;
        uint32_t stageStart = SDL_GetTicks();
        std::string lastMotion;
        std::optional<CharacterAppearance> appearance;
        if (!loaded.jobs.empty()) {
            const auto &skills = loaded.jobs.front().skills;
            const auto found = std::find_if(skills.begin(), skills.end(), [](const auto &skill) {
                return skill.key.skillId == 79;
            });
            if (found != skills.end()) skillIndex = int(found - skills.begin());
        }
        auto selectJob = [&](int delta) {
            if (loaded.jobs.empty()) return;
            jobIndex = (jobIndex + delta + int(loaded.jobs.size())) % int(loaded.jobs.size());
            skillIndex = scroll = motionIndex = 0; playing = false; appearance.reset(); appearanceJob = -1;
        };
        auto currentSkill = [&]() -> PreviewSkill * {
            if (loaded.jobs.empty()) return nullptr;
            auto &job = loaded.jobs[size_t(jobIndex)];
            return job.skills.empty() ? nullptr : &job.skills[size_t(std::clamp(skillIndex, 0, int(job.skills.size()) - 1))];
        };
        while (running) {
            int mx = 0, my = 0;
            SDL_GetMouseState(&mx, &my);
            renderer.mouse(mx, my, uiWidth, uiHeight);
            bool click = false;
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
                else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) click = true;
                else if (event.type == SDL_MOUSEWHEEL) {
                    const auto count = int(loaded.jobs[size_t(jobIndex)].skills.size());
                    scroll = std::clamp(scroll - event.wheel.y, 0, std::max(0, count - 12));
                } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) running = false;
            }
            renderer.ui(uiWidth, uiHeight);
            renderer.begin();
            renderer.rect(0, 0, uiWidth, 62, {25, 33, 38, 255});
            renderer.text("1031 PVF 技能预览映射", 24, 16, 24, {238, 224, 185, 255});
            renderer.text("PVF " + loaded.pvf->path().filename().u8string() + " | " + loaded.pvf->identity().substr(0, 12),
                          610, 22, 15, {148, 204, 182, 255});
            renderer.rect(12, 76, 328, 632, {27, 34, 39, 255});
            renderer.rect(352, 76, 594, 632, {22, 31, 36, 255});
            renderer.rect(958, 76, 310, 632, {31, 35, 38, 255});

            if (!loaded.jobs.empty()) {
                const auto prev = renderer.button("<", 22, 85, 38, 34, mx, my, click);
                const auto next = renderer.button(">", 293, 85, 38, 34, mx, my, click);
                if (prev) selectJob(-1);
                if (next) selectJob(1);
                const auto &job = loaded.jobs[size_t(jobIndex)];
                renderer.text(job.name + "  " + job.key, 70, 93, 17, {227, 230, 211, 255});
                renderer.text("PVF 注册技能", 24, 130, 15, {143, 198, 179, 255});
                for (int row = 0; row < 12; ++row) {
                    const int index = scroll + row;
                    if (index >= int(job.skills.size())) break;
                    const int y = 158 + row * 39;
                    const auto &item = job.skills[size_t(index)];
                    if (renderer.button(std::to_string(item.key.skillId) + "  " + item.name,
                                        20, y, 312, 34, mx, my, click)) {
                        skillIndex = index; motionIndex = 0; playing = false;
                    }
                    if (index == skillIndex) renderer.rect(20, y, 3, 34, {216, 174, 84, 255});
                }
                if (auto *skill = currentSkill()) {
                    if (skill->motions.empty()) {
                        renderer.text("没有按资源名匹配到动作 ANI", 372, 112, 17, {228, 186, 99, 255});
                        renderer.text("不以其他技能动作代填。", 372, 141, 15, {185, 187, 179, 255});
                    } else {
                        renderer.text("动作与特效候选", 372, 104, 17, {143, 198, 179, 255});
                        const int firstVisible = (motionIndex / 4) * 4;
                        if (renderer.button("<", 844, 99, 32, 29, mx, my, click)) {
                            motionIndex = std::max(0, motionIndex - 4); playing = false; stageStart = SDL_GetTicks();
                        }
                        if (renderer.button(">", 882, 99, 32, 29, mx, my, click)) {
                            motionIndex = std::min(int(skill->motions.size()) - 1, motionIndex + 4);
                            playing = false; stageStart = SDL_GetTicks();
                        }
                        const int shown = std::min<int>(4, int(skill->motions.size()) - firstVisible);
                        for (int row = 0; row < shown; ++row) {
                            const int y = 136 + row * 35;
                            const int candidateIndex = firstVisible + row;
                            const auto &candidate = skill->motions[size_t(candidateIndex)];
                            const auto prefix = candidate.kind == "chr-motion-candidate" ? "CHR  " : "NUT  ";
                            const auto label = prefix + fs::u8path(candidate.path).filename().u8string();
                            if (renderer.button(label, 372, y, 548, 29, mx, my, click)) {
                                motionIndex = candidateIndex; playing = false; stageStart = SDL_GetTicks();
                            }
                            if (candidateIndex == motionIndex) renderer.rect(372, y, 3, 29, {216, 174, 84, 255});
                        }
                        if (renderer.button("播放候选序列", 730, 292, 190, 36, mx, my, click)) {
                            motionIndex = 0; playing = true; stageStart = SDL_GetTicks();
                        }
                        motionIndex = std::clamp(motionIndex, 0, int(skill->motions.size()) - 1);
                        auto *active = &skill->motions[size_t(motionIndex)];
                        const auto animation = loaded.assets->animation(active->path);
                        const uint32_t now = SDL_GetTicks();
                        const int64_t elapsed = playing ? int64_t(now - stageStart) : 0;
                        if (playing && animation->duration > 0 && elapsed >= animation->duration) {
                            if (motionIndex + 1 < int(skill->motions.size())) {
                                ++motionIndex; stageStart = now; active = &skill->motions[size_t(motionIndex)];
                            } else playing = false;
                        }
                        renderer.rect(382, 352, 534, 240, {18, 24, 28, 255});
                        renderer.rect(390, 556, 520, 1, {99, 110, 111, 255});
                        lastMotion = active->path;
                        if (active->kind == "chr-motion-candidate") {
                            const auto &selectedJob = loaded.jobs[size_t(jobIndex)];
                            if (!appearance || appearanceJob != selectedJob.id) {
                                appearance = defaultCharacterAppearance(*loaded.pvf, *loaded.characters,
                                    CharacterIdentity{selectedJob.id, 0, 0});
                                bindEquipmentMotions(*loaded.pvf, *appearance);
                                appearanceJob = selectedJob.id;
                            }
                            Actor actor;
                            actor.x = actor.px = 650; actor.y = actor.py = 552; actor.dir = 1;
                            actor.animation = fs::u8path(active->path).stem().u8string();
                            actor.animStart = playing ? int64_t(stageStart) : int64_t(now);
                            renderer.player(actor, now, 1.0, *appearance, 0, 0, active->path);
                        } else {
                            renderer.animation(active->path, double(playing ? SDL_GetTicks() - stageStart : 0), 650, 500, 1, false);
                        }
                        const auto sourceKind = active->kind == "chr-motion-candidate" ? "CHR 角色动作候选" :
                            active->kind == "sqr-declared-effect-animation-candidate" ? "SQR/NUT 脚本声明特效候选" : "SKL 直接引用候选";
                        renderer.text(sourceKind + std::string("  ") + std::to_string(motionIndex + 1) + "/" +
                                      std::to_string(skill->motions.size()), 386, 605, 15, {208, 210, 194, 255});
                        renderer.text("此播放顺序是预览编排，未证明原生状态机顺序。", 386, 632, 14, {228, 186, 99, 255});
                    }

                    renderer.text(skill->name, 976, 96, 20, {238, 224, 185, 255});
                    renderer.text("ID " + std::to_string(skill->key.skillId) + "  " + skill->type, 976, 130, 14, {143, 198, 179, 255});
                    const auto resolvedSquirrelCount = std::count_if(skill->squirrelEffectReferences.begin(),
                        skill->squirrelEffectReferences.end(), [](const auto &reference) { return reference.value("resolved", false); });
                    const bool hasCharacterMotion = std::any_of(skill->motions.begin(), skill->motions.end(),
                        [](const auto &motion) { return motion.kind == "chr-motion-candidate"; });
                    const std::string mappingLabel = resolvedSquirrelCount > 0 ? "脚本声明候选" :
                        hasCharacterMotion ? "资源名推定" : "未匹配";
                    renderer.text(std::string("映射: ") + mappingLabel, 976, 158, 15,
                                  skill->motions.empty() ? SDL_Color{190, 190, 184, 255} : SDL_Color{228, 186, 99, 255});
                    renderer.text("SKL", 976, 190, 13, {143, 198, 179, 255});
                    int detailY = 211;
                    detailY += drawWrapped(renderer, skill->path, 976, detailY, 270, 12, {201, 205, 195, 255}, 3);
                    renderer.text("SHA256 " + skill->sha256.substr(0, 16) + "...", 976, detailY + 3, 12, {153, 169, 162, 255});
                    detailY += 30;
                    renderer.text("ATK / direct resource refs", 976, detailY, 13, {143, 198, 179, 255});
                    detailY += 22;
                    for (const auto &reference : skill->directReferences) {
                        if (detailY > 494) break;
                        detailY += drawWrapped(renderer, reference.value("path", std::string()), 976, detailY,
                                               270, 11, {184, 190, 184, 255}, 2) + 5;
                    }
                    renderer.text("1031 REP 输入关联: " + std::to_string(skill->repEvents.size()), 976, 518, 13, {204, 213, 199, 255});
                    drawWrapped(renderer, "SQR/NUT 脚本声明 ANI: " + std::to_string(resolvedSquirrelCount) +
                        " (原生执行未确认)", 976, 545, 275, 12, {228, 186, 99, 255}, 2);
                    renderer.text("攻击框与命中因果: 未确认", 976, 571, 13, {228, 186, 99, 255});
                    renderer.text("完整映射和源哈希见报告。", 976, 612, 12, {153, 169, 162, 255});
                }
            }
            renderer.present();
        }
        writeRunReport(outputDirectory / "preview-run.json", *loaded.pvf, *loaded.assets,
                       renderer, loaded.mapping, lastMotion);
    } catch (...) {
        SDL_Quit();
        throw;
    }
    SDL_Quit();
    return 0;
}

int entry(int argc, char **argv) {
    try { return run(argc, argv); }
    catch (const std::exception &error) {
        std::cerr << "1031 skill preview: " << error.what() << '\n';
        return 1;
    }
}
} // namespace

DNF_ENTRY(entry)
