#include "dnf/monster_behavior.hpp"
#include <limits>
#include <map>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
void block(MonsterActionRoute &route, const std::string &kind, Json details = Json::object()) {
    route.ok = false;
    details["kind"] = kind;
    details["severity"] = "error";
    route.diagnostics.push_back(std::move(details));
}
SourceRef origin(const Pvf &pvf, const Script &script, size_t offset, size_t length,
                 size_t ordinal, const std::string &scope) {
    if (offset > script.rawBytes.size() || length > script.rawBytes.size() - offset)
        throw std::runtime_error("MOB source reference outside member bytes");
    SourceRef result;
    result.packageIdentity = script.source.value("package_identity", pvf.identity());
    result.memberPath = script.path;
    result.memberSha256 = sha256(script.rawBytes);
    result.literalPath = script.source.value("literal_path", script.path);
    result.byteOffset = offset;
    result.byteLength = length;
    result.ordinal = ordinal;
    result.scope = scope;
    return result;
}
bool offsetOf(const Json &token, size_t &offset) {
    if (!token.is_object() || !token.contains("offset") || !token["offset"].is_number_integer() ||
        token["offset"] < 0 || token["offset"] > std::numeric_limits<size_t>::max()) return false;
    offset = token["offset"].get<size_t>();
    return true;
}
struct FieldOperands {
    Json tokens = Json::array();
    std::vector<Json> operands;
};
// Preserve operand positions as decoded by Pvf::script: type-9 translation
// selectors are tokens, not values. Path fields cannot substitute a translated
// token with a different string while claiming that token as their origin.
FieldOperands operands(const Script &script, size_t ordinal) {
    const auto &field = script.fields.at(ordinal);
    const auto end = ordinal + 1 < script.fields.size() ? script.fields[ordinal + 1].offset : script.rawBytes.size();
    if (!field.values.is_array() || field.offset < 2 || (field.offset - 2) % 5 ||
        field.offset >= end || end > script.rawBytes.size() || (end - field.offset) % 5)
        throw std::runtime_error("Invalid MOB field byte range or value array");
    FieldOperands result;
    size_t expected = field.offset;
    for (const auto &token : script.tokens) {
        size_t offset = 0;
        if (!offsetOf(token, offset)) throw std::runtime_error("Invalid MOB token offset");
        if (offset < field.offset || offset >= end) continue;
        if (offset != expected || !token.contains("type") || !token["type"].is_number_integer() ||
            !token.contains("value") || token["type"] < 0 || token["type"] > 255 ||
            offset + 5 > script.rawBytes.size() || script.rawBytes[offset] != token["type"].get<uint8_t>())
            throw std::runtime_error("MOB token sequence or byte kind disagrees with its field");
        if (!token.contains("raw") || !token["raw"].is_number_integer() ||
            token["raw"] < std::numeric_limits<int32_t>::min() || token["raw"] > std::numeric_limits<int32_t>::max())
            throw std::runtime_error("Invalid MOB token raw operand");
        int32_t raw = 0;
        std::memcpy(&raw, script.rawBytes.data() + offset + 1, 4);
        if (raw != token["raw"].get<int32_t>()) throw std::runtime_error("MOB token raw operand disagrees with source bytes");
        const int type = token["type"].get<int>();
        if (offset == field.offset) {
            if (type != 5 || !token["value"].is_string() || token["value"].get<std::string>() != field.tag)
                throw std::runtime_error("MOB field tag disagrees with its source token");
        } else if (type != 9) {
            const size_t index = result.operands.size();
            if (type == 5 || index >= field.values.size() || token["value"] != field.values[index])
                throw std::runtime_error("MOB field values disagree with complete operand order");
            result.operands.push_back(token);
        }
        result.tokens.push_back(token);
        expected += 5;
    }
    if (expected != end || result.operands.size() != field.values.size())
        throw std::runtime_error("MOB field tokens are missing or contain unrepresented operands");
    return result;
}
using Scopes = std::vector<std::vector<std::string>>;
Scopes scopesOf(const Script &script) {
    Scopes result(script.fields.size());
    // Only paired delimiters introduce a scope. Ordinary MOB tags are fields,
    // and unknown tags inside a recognized block still retain that block.
    std::vector<std::string> active;
    for (size_t i = 0; i < script.fields.size(); ++i) {
        const auto tag = normalize(script.fields[i].tag);
        result[i] = active;
        if (tag.rfind("[/", 0) == 0) {
            const auto open = "[" + tag.substr(2);
            if (!active.empty() && active.back() == open) active.pop_back();
            continue;
        }
        if (tag.size() < 3 || tag.front() != '[' || tag.back() != ']') continue;
        const auto close = "[/" + tag.substr(1);
        bool paired = false;
        for (size_t j = i + 1; j < script.fields.size(); ++j)
            if (normalize(script.fields[j].tag) == close) { paired = true; break; }
        if (paired) active.push_back(tag);
    }
    return result;
}
bool pairedTag(const std::string &tag) {
    return tag == "[cooltime]" || tag == "[attack info]" || tag == "[pattern]" ||
        tag == "[ai pattern]" || tag == "[int data]" || tag == "[float data]" ||
        tag.find("ai pattern") != std::string::npos;
}
Json fieldRecord(const Pvf &pvf, const Script &script, size_t ordinal, const Scopes &scopes) {
    const auto &field = script.fields[ordinal];
    const auto end = ordinal + 1 < script.fields.size() ? script.fields[ordinal + 1].offset : script.rawBytes.size();
    if (end < field.offset) throw std::runtime_error("Unordered MOB fields");
    return {{"tag", field.tag}, {"values", field.values}, {"offset", field.offset},
        {"field_ordinal", ordinal}, {"scopes", scopes[ordinal]},
        {"source", origin(pvf, script, field.offset, end - field.offset, ordinal, "monster_behavior/paired_field").json()}};
}
bool safeLiteral(const std::string &value) {
    return !value.empty() && value.front() != '/' && value.front() != '\\' &&
        value.find(':') == std::string::npos && value.find('\0') == std::string::npos;
}
std::optional<std::string> canonical(const std::string &value) {
    if (!safeLiteral(value)) return std::nullopt;
    const auto path = normalize(value);
    if (path.empty() || path == "." || path == ".." || path.rfind("../", 0) == 0 ||
        path.front() == '/' || path.front() == '\\') return std::nullopt;
    return path;
}
std::set<std::string> resolve(const Pvf &pvf, const std::string &parent, const std::string &literal) {
    std::set<std::string> result;
    if (!safeLiteral(literal)) return result;
    auto slashParent = parent;
    std::replace(slashParent.begin(), slashParent.end(), '\\', '/');
    const auto slash = slashParent.find_last_of('/');
    const auto directory = slash == std::string::npos ? std::string() : slashParent.substr(0, slash + 1);
    for (const auto &candidate : {directory + literal, literal, "monster/" + literal}) {
        const auto path = canonical(candidate);
        if (path && pvf.has(*path)) result.insert(*path);
    }
    return result;
}
bool extension(const std::string &value, const std::string &suffix) {
    auto text = value;
    for (auto &c : text) if (c >= 'A' && c <= 'Z') c += 32;
    return text.size() >= suffix.size() && text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}
} // namespace

const char *monsterActionEngineName(MonsterActionEngine engine) {
    switch (engine) {
    case MonsterActionEngine::Act: return "act";
    case MonsterActionEngine::LegacyAni: return "legacy_ani";
    default: return "none";
    }
}
Json MonsterActionRoute::json() const {
    Json result = {{"ok", ok}, {"engine", monsterActionEngineName(engine)}, {"state", state},
        {"selected_tag", selectedTag}, {"source_action_index", sourceActionIndex},
        {"literal", literalPath}, {"resolved", resolvedPath}, {"source", source.json()},
        {"field_source", fieldSource.json()}, {"resolved_source", resolvedSource.json()},
        {"all_values", allValues}, {"field_tokens", fieldTokens},
        {"paired_source_fields", pairedSourceFields}, {"diagnostics", diagnostics},
        {"classification", "source_route_only"}, {"whole_monster_capability", false}};
    result["cooldown_ms"] = cooldownMs ? Json(*cooldownMs) : Json();
    result["cooldown_source"] = cooldownSource ? cooldownSource->json() : Json();
    result["attack_info_literal"] = attackInfoLiteral ? Json(*attackInfoLiteral) : Json();
    result["attack_info_source"] = attackInfoSource ? attackInfoSource->json() : Json();
    result["attack_info_resolved"] = attackInfoResolvedPath;
    return result;
}

MonsterActionRoute selectMonsterAction(const Pvf &pvf, const Script &monster, const std::string &state, int index) {
    MonsterActionRoute route;
    route.state = state;
    route.sourceActionIndex = index;
    try {
        const std::map<std::string, std::string> single = {{"stay", "[waiting action]"}, {"move", "[move action]"},
            {"damage1", "[damage action 1]"}, {"damage2", "[damage action 2]"}, {"down", "[down action]"},
            {"sit", "[sit action]"}, {"overturn", "[overturn action]"}, {"jump", "[jump action]"},
            {"death", "[last action]"}, {"proc", "[proc action]"}, {"come_in", "[come in action]"}};
        const std::map<std::string, std::string> legacy = {{"stay", "[waiting motion]"}, {"move", "[move motion]"},
            {"damage1", "[damage motion 1]"}, {"damage2", "[damage motion 2]"}, {"down", "[down motion]"},
            {"sit", "[sit motion]"}, {"overturn", "[overturn motion]"}, {"jump", "[jump motion]"}, {"attack", "[attack motion]"}};
        if (index < 0) { block(route, "negative_source_action_index"); return route; }
        if (!single.count(state) && state != "attack" && state != "etc") {
            block(route, "unsupported_source_route_state"); return route;
        }
        if (monster.path.empty() || !monster.source.is_object() || !monster.tokens.is_array() ||
            monster.rawBytes.size() < 2 || (monster.rawBytes.size() - 2) % 5 ||
            monster.source.value("package_identity", pvf.identity()) != pvf.identity()) {
            block(route, "invalid_or_foreign_monster_route_source"); return route;
        }
        std::map<std::string, std::vector<size_t>> fields;
        for (size_t i = 0; i < monster.fields.size(); ++i) fields[normalize(monster.fields[i].tag)].push_back(i);
        const auto scopes = scopesOf(monster);
        for (size_t i = 0; i < monster.fields.size(); ++i) {
            bool keep = pairedTag(normalize(monster.fields[i].tag));
            for (const auto &scope : scopes[i]) if (pairedTag(scope)) keep = true;
            if (keep) route.pairedSourceFields.push_back(fieldRecord(pvf, monster, i, scopes));
        }
        if ((state == "stay" || state == "move") && fields.count("[basic action]")) route.selectedTag = "[basic action]";
        else if (state == "attack") {
            if (fields.count("[action list]") && fields.count("[attack action]")) {
                Json competing = Json::array();
                for (const auto &tag : {"[action list]", "[attack action]"})
                    for (const auto ordinal : fields.at(tag)) competing.push_back(fieldRecord(pvf, monster, ordinal, scopes));
                block(route, "ambiguous_attack_action_spellings", {{"competing_fields", competing}});
                return route;
            }
            route.selectedTag = fields.count("[action list]") ? "[action list]" : "[attack action]";
        } else if (state == "etc") route.selectedTag = "[etc action]";
        else route.selectedTag = single.at(state);
        route.engine = MonsterActionEngine::Act;
        if (!fields.count(route.selectedTag)) {
            const auto fallback = legacy.find(state);
            if (fallback == legacy.end() || !fields.count(fallback->second)) {
                block(route, "source_action_and_legacy_motion_absent"); return route;
            }
            route.selectedTag = fallback->second;
            route.engine = MonsterActionEngine::LegacyAni;
        }
        const auto &candidates = fields.at(route.selectedTag);
        if (candidates.size() != 1) {
            Json competing = Json::array();
            for (const auto ordinal : candidates) competing.push_back(fieldRecord(pvf, monster, ordinal, scopes));
            block(route, "repeated_action_field_ambiguous", {{"competing_fields", competing}}); return route;
        }
        const auto ordinal = candidates[0];
        const auto &field = monster.fields[ordinal];
        route.allValues = field.values;
        route.fieldSource = origin(pvf, monster, field.offset, 5, ordinal, "monster_behavior/action_field");
        if (!scopes[ordinal].empty()) {
            block(route, "scoped_action_requires_version_policy", {{"scopes", scopes[ordinal]}}); return route;
        }
        if (!field.values.is_array() || ((state != "attack" && state != "etc") && (index != 0 || field.values.size() != 1))) {
            block(route, "singleton_route_has_unexpected_slot_or_operands"); return route;
        }
        if (size_t(index) >= field.values.size()) { block(route, "action_index_outside_authored_list"); return route; }
        const auto &literal = field.values[size_t(index)];
        if (!literal.is_string() || literal.get_ref<const std::string &>().empty()) {
            block(route, "empty_or_invalid_authored_action_slot"); return route;
        }
        route.literalPath = literal.get<std::string>();
        if (!extension(route.literalPath, route.engine == MonsterActionEngine::Act ? ".act" : ".ani")) {
            block(route, "authored_resource_kind_differs_from_route_engine"); return route;
        }
        const auto sourceOperands = operands(monster, ordinal);
        route.fieldTokens = sourceOperands.tokens;
        const auto &token = sourceOperands.operands.at(size_t(index));
        const auto tokenType = token["type"].get<int>();
        if (tokenType != 6 && tokenType != 7 && tokenType != 8 && tokenType != 10) {
            block(route, "action_path_requires_string_token"); return route;
        }
        route.source = origin(pvf, monster, token["offset"].get<size_t>(), 5, ordinal,
            "monster_behavior/" + state + "/" + std::to_string(index));
        const auto paths = resolve(pvf, monster.path, route.literalPath);
        if (paths.size() != 1) {
            block(route, "source_action_path_missing_or_ambiguous", {{"candidates", paths}}); return route;
        }
        route.resolvedPath = *paths.begin();
        route.resolvedSource = makeSourceRef(pvf, route.resolvedPath);
        // Pair only attacks. A stay action must not reject an unrelated attack
        // list, and legacy ANI state execution remains a separate consumer.
        if (state == "attack") for (const auto &tag : {"[cooltime]", "[attack info]"}) {
            if (!fields.count(tag)) continue;
            const auto &paired = fields.at(tag);
            if (paired.size() != 1 || !scopes[paired.front()].empty()) {
                block(route, "paired_action_field_ambiguous_or_scoped", {{"tag", tag}}); return route;
            }
            const auto pairOrdinal = paired.front();
            const auto &pair = monster.fields[pairOrdinal];
            if (!pair.values.is_array() || pair.values.size() != field.values.size()) {
                block(route, "paired_action_array_shape_requires_version_policy", {{"tag", tag}, {"values", pair.values}}); return route;
            }
            const auto pairOperands = operands(monster, pairOrdinal);
            for (size_t k = 0; k < pair.values.size(); ++k) {
                const auto &entry = pair.values[k];
                const auto kind = pairOperands.operands[k]["type"].get<int>();
                if (std::string(tag) == "[cooltime]" ?
                    (!entry.is_number_integer() || entry < 0 || entry > std::numeric_limits<int64_t>::max() || kind != 2) :
                    (!entry.is_string() || (kind != 6 && kind != 7 && kind != 8 && kind != 10))) {
                    block(route, "paired_action_array_is_not_simple", {{"tag", tag}, {"slot", k}, {"value", entry}});
                    return route;
                }
            }
            const auto &value = pair.values[size_t(index)];
            const auto &pairToken = pairOperands.operands.at(size_t(index));
            const auto pairRef = origin(pvf, monster, pairToken["offset"].get<size_t>(), 5, pairOrdinal,
                "monster_behavior/attack/" + std::to_string(index) + "/" + tag);
            if (std::string(tag) == "[cooltime]") {
                if (!value.is_number_integer() || value < 0 || value > std::numeric_limits<int64_t>::max() || pairToken["type"] != 2) {
                    block(route, "invalid_paired_action_cooldown", {{"value", value}, {"source", pairRef.json()}}); return route;
                }
                route.cooldownMs = value.get<int64_t>();
                route.cooldownSource = pairRef;
            } else {
                if (!value.is_string()) { block(route, "invalid_paired_attack_info_slot"); return route; }
                route.attackInfoLiteral = value.get<std::string>();
                route.attackInfoSource = pairRef;
                if (route.attackInfoLiteral->empty()) continue;
                if (!extension(*route.attackInfoLiteral, ".atk")) { block(route, "invalid_paired_attack_info_resource_kind"); return route; }
                const auto attacks = resolve(pvf, monster.path, *route.attackInfoLiteral);
                if (attacks.size() != 1) {
                    block(route, "paired_attack_info_path_missing_or_ambiguous", {{"candidates", attacks}}); return route;
                }
                route.attackInfoResolvedPath = *attacks.begin();
            }
        }
        route.ok = true;
    } catch (const std::exception &error) {
        block(route, "invalid_monster_action_source", {{"reason", error.what()}});
    }
    return route;
}
} // namespace dnf
