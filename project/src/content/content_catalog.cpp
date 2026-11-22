#include "dnf/content_catalog.hpp"
#include "dnf/objects.hpp"
#include "dnf/region.hpp"
#include <limits>
#include <queue>
#include <stdexcept>

namespace dnf {
const char *capabilityStateName(CapabilityState state) {
    switch (state) {
    case CapabilityState::Supported: return "Playable";
    case CapabilityState::Inferred: return "PlayableWithInference";
    case CapabilityState::Blocked: return "Blocked";
    }
    throw std::runtime_error("Invalid capability state");
}
const char *dependencyUseName(DependencyUse use) {
    switch (use) {
    case DependencyUse::Required: return "required_gameplay";
    case DependencyUse::OptionalPresentation: return "optional_presentation";
    case DependencyUse::Preload: return "preload_only";
    case DependencyUse::Metadata: return "metadata_only";
    }
    throw std::runtime_error("Invalid dependency use");
}
Json DependencyEdge::json() const {
    return {{"from", from}, {"to", to}, {"kind", kind}, {"use", dependencyUseName(use)},
            {"source", source.json()}, {"condition", condition}, {"compiler_capability", compilerCapability}};
}
Json CapabilityReport::json() const {
    return {{"target", target}, {"mode", mode}, {"status", capabilityStateName(state)},
            {"causes", causes}, {"warnings", warnings}};
}
void CapabilityGraph::define(CapabilityNode node) {
    if (node.key.empty()) throw std::runtime_error("Empty capability node key");
    capabilityStateName(node.state);
    if (node.state != CapabilityState::Supported && node.reason.empty())
        throw std::runtime_error("Unsupported/inferred capability requires a reason: " + node.key);
    if (!nodes_.emplace(node.key, std::move(node)).second)
        throw std::runtime_error("Duplicate capability node");
}
void CapabilityGraph::depend(DependencyEdge edge) {
    if (edge.from.empty() || edge.to.empty() || edge.kind.empty())
        throw std::runtime_error("Dependency requires from, to and kind");
    dependencyUseName(edge.use);
    edges_.push_back(std::move(edge));
}
CapabilityReport CapabilityGraph::evaluate(const std::string &target, const CapabilityContext &context) const {
    CapabilityReport result; result.target = target; result.mode = context.mode;
    auto condition = [&](const DependencyEdge &edge) {
        if (edge.condition.empty()) return 1;
        auto found = context.conditions.find(edge.condition);
        return found == context.conditions.end() ? -1 : (found->second ? 1 : 0);
    };
    std::map<std::string, CapabilityState> states;
    std::map<std::string, std::vector<std::string>> parents;
    std::map<std::string, std::vector<size_t>> outgoing;
    for (const auto &[key, node] : nodes_) states[key] = node.state;
    auto stateAt = [&](const std::string &key) {
        auto found = states.find(key);
        return found == states.end() ? CapabilityState::Blocked : found->second;
    };
    for (size_t i = 0; i < edges_.size(); ++i) {
        const auto &edge = edges_[i]; outgoing[edge.from].push_back(i);
        if (edge.use != DependencyUse::Required || condition(edge) == 0 || !states.count(edge.from)) continue;
        if (condition(edge) < 0) { states[edge.from] = CapabilityState::Blocked; continue; }
        for (const auto &dependency : {edge.to, edge.compilerCapability}) if (!dependency.empty()) {
            parents[dependency].push_back(edge.from);
            if (!states.count(dependency)) states[edge.from] = CapabilityState::Blocked;
        }
    }
    std::queue<std::string> pending;
    for (const auto &[key, state] : states) if (state != CapabilityState::Supported) pending.push(key);
    while (!pending.empty()) {
        const auto child = pending.front(); pending.pop();
        const auto found = parents.find(child);
        if (found == parents.end()) continue;
        for (const auto &parent : found->second) if (states[parent] < states[child]) {
            states[parent] = states[child]; pending.push(parent);
        }
    }
    result.state = stateAt(target);
    // The first path to each cause is deterministic and shortest. Cycles and
    // diamonds retain graph edges in snapshot without duplicating diagnostics.
    struct Visit { std::string key; Json path; };
    auto collect = [&](const std::string &start, Json prefix, Json &output) {
        std::queue<Visit> queue; queue.push({start, std::move(prefix)});
        std::set<std::string> seen;
        while (!queue.empty()) {
            auto visit = std::move(queue.front()); queue.pop();
            if (!seen.insert(visit.key).second) continue;
            auto local = nodes_.find(visit.key);
            if (local == nodes_.end() || local->second.state != CapabilityState::Supported) {
                Json cause = {{"node", visit.key}, {"path", visit.path},
                    {"status", capabilityStateName(local == nodes_.end() ? CapabilityState::Blocked : local->second.state)},
                    {"reason", local == nodes_.end() ? "Missing dependency node" : local->second.reason}};
                if (local != nodes_.end()) {
                    cause["source"] = local->second.source.json(); cause["evidence"] = local->second.evidence;
                }
                output.push_back(std::move(cause));
            }
            auto children = outgoing.find(visit.key);
            if (children == outgoing.end()) continue;
            for (size_t index : children->second) {
                const auto &edge = edges_[index];
                if (edge.use != DependencyUse::Required || condition(edge) == 0) continue;
                auto path = visit.path; path.push_back(edge.json());
                if (condition(edge) < 0) {
                    output.push_back({{"node", edge.from}, {"status", "Blocked"},
                        {"reason", "Unresolved dependency condition: " + edge.condition}, {"path", path}});
                    continue;
                }
                queue.push({edge.to, path});
                if (!edge.compilerCapability.empty()) {
                    auto compilerPath = visit.path;
                    auto compilerEdge = edge.json(); compilerEdge["to"] = edge.compilerCapability;
                    compilerEdge["kind"] = "semantic_compiler_for:" + edge.kind;
                    compilerPath.push_back(compilerEdge);
                    queue.push({edge.compilerCapability, std::move(compilerPath)});
                }
            }
        }
    };
    collect(target, Json::array(), result.causes);
    // Nonrequired branches can produce diagnostics, never downgrade playability.
    std::queue<Visit> warningQueue; warningQueue.push({target, Json::array()});
    std::set<std::string> warningSeen;
    while (!warningQueue.empty()) {
        auto visit = std::move(warningQueue.front()); warningQueue.pop();
        if (!warningSeen.insert(visit.key).second) continue;
        auto found = outgoing.find(visit.key); if (found == outgoing.end()) continue;
        for (size_t index : found->second) {
            const auto &edge = edges_[index]; if (condition(edge) == 0) continue;
            auto path = visit.path; path.push_back(edge.json());
            if (edge.use == DependencyUse::Required) {
                if (condition(edge) > 0) {
                    warningQueue.push({edge.to, path});
                    if (!edge.compilerCapability.empty()) {
                        auto compilerPath = visit.path; auto compilerEdge = edge.json();
                        compilerEdge["to"] = edge.compilerCapability;
                        compilerEdge["kind"] = "semantic_compiler_for:" + edge.kind;
                        compilerPath.push_back(compilerEdge);
                        warningQueue.push({edge.compilerCapability, std::move(compilerPath)});
                    }
                }
            } else if (edge.use != DependencyUse::Metadata) {
                if (condition(edge) < 0) result.warnings.push_back({{"node", edge.from},
                    {"reason", "Unresolved nonrequired dependency condition: " + edge.condition}, {"path", path}});
                else {
                    collect(edge.to, path, result.warnings);
                    if (!edge.compilerCapability.empty()) {
                        auto compilerPath = visit.path; auto compilerEdge = edge.json();
                        compilerEdge["to"] = edge.compilerCapability;
                        compilerEdge["kind"] = "semantic_compiler_for:" + edge.kind;
                        compilerPath.push_back(compilerEdge);
                        collect(edge.compilerCapability, std::move(compilerPath), result.warnings);
                    }
                }
            }
        }
    }
    return result;
}
Json CapabilityGraph::snapshot() const {
    // Local registrations can describe an available input or one consumer
    // while required dependencies still block the final target. Only evaluate
    // produces the public aggregate Playable/PlayableWithInference status.
    auto localStateName = [](CapabilityState state) {
        switch (state) {
        case CapabilityState::Supported: return "Supported";
        case CapabilityState::Inferred: return "Inferred";
        case CapabilityState::Blocked: return "Blocked";
        }
        throw std::runtime_error("Invalid capability local state");
    };
    Json value = {{"nodes", Json::array()}, {"edges", Json::array()},
        {"aggregate_evaluation_required", true},
        {"scope", "Local registrations and dependency edges; no aggregate playability claim. Use evaluate(target, context)"}};
    for (const auto &[key, node] : nodes_) value["nodes"].push_back({{"key", key},
        {"local_state", localStateName(node.state)}, {"aggregate_evaluation_required", true}, {"reason", node.reason},
        {"source", node.source.json()}, {"evidence", node.evidence}});
    for (const auto &edge : edges_) value["edges"].push_back(edge.json());
    return value;
}
Json SemanticAdapter::json() const {
    return {{"id", id}, {"version", version}, {"format", format}, {"content_identity", contentIdentity},
        {"behavior", behavior}, {"source_selection", sourceSelection}, {"invalidation", invalidation},
        {"status", capabilityStateName(state)}, {"priority", priority},
        {"evidence", evidence}, {"limitations", limitations}};
}
Json AdapterResolution::json() const {
    return {{"selected", adapter ? adapter->json() : Json()}, {"reason", reason}, {"candidates", candidates}};
}
void SemanticAdapterRegistry::add(SemanticAdapter adapter) {
    if (adapter.id.empty() || adapter.version.empty() || adapter.format.empty() || adapter.behavior.empty() ||
        adapter.sourceSelection.empty() || adapter.invalidation.empty() || adapter.evidence.empty())
        throw std::runtime_error("Semantic adapter requires identity/version, scope, selection, evidence and invalidation");
    capabilityStateName(adapter.state);
    for (const auto &existing : adapters_) if (existing.id == adapter.id && existing.version == adapter.version)
        throw std::runtime_error("Duplicate semantic adapter identity/version");
    adapters_.push_back(std::move(adapter));
}
AdapterResolution SemanticAdapterRegistry::resolve(const std::string &format, const std::string &identity) const {
    AdapterResolution result; int best = std::numeric_limits<int>::min();
    for (const auto &adapter : adapters_) {
        if (adapter.format != format || (!adapter.contentIdentity.empty() && adapter.contentIdentity != identity)) continue;
        if (adapter.priority < best) continue;
        if (adapter.priority > best) { result.candidates.clear(); result.adapter = nullptr; best = adapter.priority; }
        result.candidates.push_back(adapter.id + "@" + adapter.version); result.adapter = &adapter;
    }
    if (result.candidates.empty()) result.reason = "No matching semantic adapter";
    else if (result.candidates.size() > 1) {
        result.adapter = nullptr; result.reason = "Ambiguous semantic adapters at equal priority";
    } else result.reason = "Unique highest explicit priority";
    return result;
}
Json SemanticAdapterRegistry::snapshot() const {
    Json result = Json::array(); for (const auto &adapter : adapters_) result.push_back(adapter.json()); return result;
}
Json CatalogDocument::json(bool includeBytes) const {
    Json result = {{"source", source.json()}, {"byte_count", bytes.size()}, {"token5", token5},
        {"diagnostics", diagnostics}, {"tokens", script.tokens}, {"fields", Json::array()}};
    for (const auto &field : script.fields) result["fields"].push_back({{"tag", field.tag},
        {"values", field.values}, {"offset", field.offset}});
    if (includeBytes) result["bytes"] = bytes;
    return result;
}
Json CatalogRegistry::json(bool includeSource) const {
    Json result = {{"kind", kind}, {"source", source.json()}, {"entries", Json::array()}, {"issues", list.issues}};
    for (const auto &entry : list.entries) result["entries"].push_back({{"id", entry.id}, {"ordinal", entry.ordinal},
        {"offset", entry.offset}, {"path_offset", entry.pathOffset}, {"literal", entry.literal},
        {"path", entry.path}, {"exists", entry.exists}});
    if (includeSource) {
        result["bytes"] = list.source.bytes; result["tokens"] = list.source.script.tokens;
        result["fields"] = Json::array();
        for (const auto &field : list.source.script.fields) result["fields"].push_back({
            {"tag", field.tag}, {"values", field.values}, {"offset", field.offset}});
    }
    return result;
}
void ContentCatalog::addRegistry(const std::string &path, const std::string &kind, const std::string &base) {
    if (registries_.count(normalize(path)) || !pvf_.has(path)) return;
    try {
        CatalogRegistry registry; registry.kind = kind;
        registry.list = loadCharacterList(pvf_, path, base);
        registry.source = makeSourceRef(pvf_, path);
        registries_.emplace(normalize(path), std::move(registry));
    } catch (const std::exception &error) {
        diagnostics_.push_back({{"kind", "registry_parse_failed"}, {"path", path}, {"reason", error.what()}});
    }
}
ContentCatalog::ContentCatalog(Pvf &pvf) : pvf_(pvf) {
    for (const auto &path : pvf.paths("")) {
        auto format = normalize(std::filesystem::u8path(path).extension().u8string());
        members_.push_back({path, format.empty() ? "unknown" : format.substr(1)});
    }
    // These are format-specific registry locations/bases, not gameplay IDs.
    // Unlisted registries remain indexed and readable without guessed semantics.
    for (const auto &root : {"character", "equipment", "stackable", "monster", "passiveobject",
             "object", "map", "town", "worldmap", "dungeon", "npc"})
        addRegistry(std::string(root) + "/" + root + ".lst", root, root);
    addRegistry("itemshop/itemshop.lst", "shop", "itemshop");
    addRegistry("n_quest/quest.lst", "quest", "n_quest");
    addRegistry("skill/skilllist.lst", "job_skill_list", "skill");
    const auto lists = registries_.find("skill/skilllist.lst");
    if (lists != registries_.end()) {
        // Copy paths before adding entries to avoid coupling traversal to mutation.
        std::vector<std::string> children;
        for (const auto &row : lists->second.list.entries) if (row.exists) children.push_back(row.path);
        for (const auto &path : children) addRegistry(path, "skill", "skill");
    }
}
const CatalogMember *ContentCatalog::member(const std::string &literal) const {
    const auto path = normalize(literal);
    const auto found = std::lower_bound(members_.begin(), members_.end(), path,
        [](const CatalogMember &entry, const std::string &key) { return entry.path < key; });
    return found != members_.end() && found->path == path ? &*found : nullptr;
}
CatalogDocument ContentCatalog::loadDocument(const std::string &path) const {
    CatalogDocument result; result.bytes = pvf_.read(path); result.source = makeSourceRef(pvf_, path);
    result.script.path = normalize(path);
    try { result.script = pvf_.script(path); result.token5 = true; }
    catch (const std::exception &error) {
        result.diagnostics.push_back({{"kind", "not_decoded_as_token5"}, {"reason", error.what()}});
    }
    return result;
}
const CharacterRegistration *ContentCatalog::registration(const std::string &path, int id) const {
    auto found = registries_.find(normalize(path));
    return found == registries_.end() ? nullptr : found->second.list.unique(id);
}
Json ContentCatalog::snapshot(bool includeMembers, bool includeSource) const {
    Json formats = Json::object(), registries = Json::object(); size_t rows = 0;
    for (const auto &member : members_) formats[member.format] = formats.value(member.format, size_t(0)) + 1;
    for (const auto &[path, registry] : registries_) { registries[path] = registry.json(includeSource); rows += registry.list.entries.size(); }
    Json result = {{"purpose", "Lossless source discovery; registration is not executable capability"},
        {"member_count", members_.size()}, {"formats", formats}, {"registration_row_count", rows},
        {"registries", registries}, {"diagnostics", diagnostics_},
        {"semantic_closure", "Not claimed; runtime consumers must declare capability nodes and required edges"}};
    if (includeMembers) {
        result["members"] = Json::array();
        for (const auto &member : members_) result["members"].push_back({{"path", member.path}, {"format", member.format}});
    }
    return result;
}
CapabilityGraph buildRegionCapabilityGraph(Pvf &pvf, const RegionCatalog &region) {
    CapabilityGraph graph;
    auto source = [&](const Script &script, size_t offset = 0, size_t ordinal = 0) {
        if (pvf.has(script.path)) return makeSourceRef(pvf, script.path, offset, 0, ordinal);
        SourceRef missing; missing.memberPath = script.path; missing.literalPath = script.path; return missing;
    };
    auto define = [&](const std::string &key, CapabilityState state, const std::string &reason,
                      SourceRef ref = {}, Json evidence = Json::array()) {
        if (!graph.nodes().count(key)) graph.define({key, state, reason, std::move(ref), std::move(evidence)});
    };
    auto depend = [&](const std::string &from, const std::string &to, const std::string &kind, const SourceRef &ref) {
        graph.depend({from, to, kind, DependencyUse::Required, ref, "", ""});
    };
    define("region.full-world-closure", CapabilityState::Blocked,
        "RegionCatalog still loads one town/worldmap and selected source folders; full registered-world semantic closure is incomplete", {},
        Json::array({"src/region.cpp: RegionCatalog constructor"}));
    define("monster.complete-behavior", CapabilityState::Blocked,
        "Monster motion composition and legacy combat AI do not execute the full source ACT/AI behavior chain", {},
        Json::array({"src/combat.cpp: World monster update", "include/dnf/monster_effects.hpp: ACT MOTION-only contract"}));
    define("object.complete-behavior", CapabilityState::Blocked,
        "Object action/sound/PTL and one-shot payload consumers are incomplete for the full beta gate", {},
        Json::array({"include/dnf/objects.hpp: ObjectDefinition actions/particleReferences/sounds", "CURRENT_TASK.md: object unresolved consumers"}));
    define("dungeon.complete-progression", CapabilityState::Blocked,
        "Source-driven attributes, normal monster HP, rewards and required quest variants have not reached the complete beta contract", {},
        Json::array({"CURRENT_TASK.md: actual playable scope", "dnf-native-build-plan/05-stats-equipment-and-combat.md"}));
    define("beta.world", CapabilityState::Supported, "Complete world beta target");
    depend("beta.world", "region.full-world-closure", "required_region_closure", {});
    for (const auto &[id, map] : region.maps) {
        const auto key = "map:" + std::to_string(id); const auto ref = source(map.source);
        define(key, CapabilityState::Supported, "Loaded MAP source definition", ref);
        for (size_t index = 0; index < map.monsters.size(); ++index) {
            const auto &spawn = map.monsters[index]; const auto monsterKey = "monster:" + std::to_string(spawn.id);
            auto monster = region.monsters.find(spawn.id);
            if (monster == region.monsters.end()) define(monsterKey, CapabilityState::Blocked,
                "MAP monster registration was not resolved by the runtime RegionCatalog", ref);
            else {
                define(monsterKey, CapabilityState::Supported, "Loaded MOB source definition", source(monster->second));
                depend(monsterKey, "monster.complete-behavior", "required_monster_consumer", source(monster->second));
            }
            depend(key, monsterKey, "map_monster_spawn", ref);
            if (spawn.npcOnDeath >= 0) {
                const auto npcKey = "npc-on-death:" + std::to_string(spawn.npcOnDeath);
                define(npcKey, CapabilityState::Blocked, "MAP NPC-on-death behavior has no complete runtime consumer", ref);
                depend(key, npcKey, "map_monster_npc_on_death", ref);
            }
        }
        Json diagnostics = Json::array();
        const auto placements = objectPlacements(map.source, "capability-audit", key, 0, &diagnostics);
        for (const auto &placement : placements) {
            auto placementRef = source(map.source, placement.identity.fieldOffset, size_t(placement.identity.recordOrdinal));
            const auto objectKey = key + ":object:" + std::to_string(placement.identity.recordOrdinal);
            define(objectKey, CapabilityState::Supported, "Parsed MAP object placement", placementRef);
            depend(key, objectKey, "map_object_placement", placementRef);
            depend(objectKey, "object.complete-behavior", "required_object_consumer", placementRef);
        }
        if (!diagnostics.empty()) {
            const auto invalid = key + ":object-parse";
            define(invalid, CapabilityState::Blocked, "MAP object records contain unsupported or truncated required data", ref, diagnostics);
            depend(key, invalid, "map_object_parse", ref);
        }
    }
    for (const auto &[id, dungeon] : region.dungeons) {
        const auto key = "beta.dungeon:" + std::to_string(id); const auto ref = source(dungeon.source);
        define(key, CapabilityState::Supported, "Loaded DGN source definition; complete beta eligibility is checked below", ref);
        depend("beta.world", key, "world_dungeon", ref);
        depend(key, "dungeon.complete-progression", "required_normal_gameplay", ref);
        std::set<int> candidates;
        for (int mapId : dungeon.mapIds) {
            auto map = region.maps.find(mapId);
            // Special quest rooms have a different entrance condition. Only
            // include them below when an explicit DGN candidate references one.
            if (map == region.maps.end() || !map->second.special) candidates.insert(mapId);
        }
        for (const auto &maze : dungeon.mazes) {
            for (const auto *groups : {&maze.specifiedMaps, &maze.specifiedBossMaps})
                for (const auto &[cell, maps] : *groups) for (int mapId : maps) candidates.insert(mapId);
        }
        if (candidates.empty()) {
            const auto empty = key + ":no-candidate-maps";
            define(empty, CapabilityState::Blocked, "DGN has no loaded legal candidate MAPs", ref);
            depend(key, empty, "all_legal_candidate_rooms", ref);
        }
        for (int mapId : candidates) {
            const auto mapKey = "map:" + std::to_string(mapId);
            if (!region.maps.count(mapId)) define(mapKey, CapabilityState::Blocked,
                "DGN candidate MAP is absent from the runtime RegionCatalog", ref);
            depend(key, mapKey, "all_legal_candidate_rooms", ref);
        }
    }
    return graph;
}
} // namespace dnf
