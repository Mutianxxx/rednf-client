#include "dnf/map_exploration.hpp"
#include "dnf/scene_tiles.hpp"
#include "dnf/monster_spawn.hpp"
#include "dnf/monster_attributes.hpp"
#include "dnf/monster_effects.hpp"
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
void issue(PreparedMapExploration &out, const std::string &kind, Json details = Json::object()) {
    details["kind"] = kind;
    details["severity"] = "diagnostic";
    out.diagnostics.push_back(std::move(details));
}
std::string relative(const std::string &parent, const std::string &child) {
    if (child.empty() || child.front() == '/' || child.front() == '\\' || child.find(':') != std::string::npos || child.find('\0') != std::string::npos)
        throw std::runtime_error("Invalid absolute or empty source resource literal");
    const auto result = normalize((std::filesystem::u8path(parent).parent_path() / std::filesystem::u8path(child)).generic_u8string());
    if (result == ".." || result.rfind("../", 0) == 0 || result.empty()) throw std::runtime_error("Source resource escapes package root");
    return result;
}
double number(const Json &value) {
    if (!value.is_number()) throw std::runtime_error("Expected numeric source operand");
    const auto result = value.get<double>();
    if (!std::isfinite(result) || std::abs(result) > 10000000) throw std::runtime_error("Nonfinite or excessive source coordinate");
    return result;
}
int integer(const Json &value) {
    if (!value.is_number_integer() || value < INT32_MIN || value > INT32_MAX) throw std::runtime_error("Expected int32 source operand");
    return value.get<int>();
}
Json rawFields(const Script &script) {
    Json result = Json::array();
    for (size_t i = 0; i < script.fields.size(); ++i)
        result.push_back({{"ordinal", i}, {"tag", script.fields[i].tag}, {"offset", script.fields[i].offset}, {"values", script.fields[i].values}});
    return result;
}
Json fieldSource(const Pvf &pvf, const Script &script, size_t ordinal) {
    const auto begin = script.fields.at(ordinal).offset;
    const auto end = ordinal + 1 < script.fields.size() ? script.fields[ordinal + 1].offset : script.rawBytes.size();
    return makeSourceRef(pvf, script.path, begin, end - begin, ordinal, "map_exploration/record").json();
}
Json placement(const Pvf &pvf, const Script &script, size_t ordinal, size_t index, const Json &raw) {
    return {{"source", fieldSource(pvf, script, ordinal)}, {"value_index", index}, {"raw", raw}};
}
Json slice(const Json &values, size_t start, size_t count) {
    Json raw = Json::array();
    for (size_t i = start; i < values.size() && i - start < count; ++i) raw.push_back(values[i]);
    return raw;
}
std::shared_ptr<Animation> preflightAnimation(Assets &assets, const std::string &path) {
    const auto animation = assets.animation(path);
    if (animation->frames.empty()) throw std::runtime_error("Empty source animation");
    if (animation->frames.size() > 10000) throw std::runtime_error("Exploration animation frame budget exceeded");
    std::set<std::pair<std::string, int>> images;
    for (const auto &frame : animation->frames) if (!frame.image.empty() && images.emplace(frame.image, frame.imageFrame).second)
        assets.pixels(frame.image, frame.imageFrame);
    return animation;
}
std::map<int, std::vector<std::string>> npcRegistry(Pvf &pvf) {
    const auto script = pvf.script("npc/npc.lst");
    std::map<int, std::vector<std::string>> result;
    for (size_t i = 0; i + 1 < script.tokens.size(); i += 2) {
        const auto &id = script.tokens[i]["value"], &literal = script.tokens[i + 1]["value"];
        if (!literal.is_string()) throw std::runtime_error("Malformed NPC registry path");
        result[integer(id)].push_back(relative(script.path, literal.get<std::string>()));
    }
    return result;
}
} // namespace

Json PreparedMapExploration::json() const {
    return {{"ok", ok}, {"test_mode", testMode}, {"complete", complete}, {"geometry_available", geometryAvailable},
        {"map", scene.path}, {"width", scene.width}, {"background_origin", scene.bg}, {"player_spawn", playerSpawn},
        {"monsters", monsters.size()}, {"tiles", scene.tiles.size()}, {"walk_rects", scene.walkRects.size()},
        {"npcs", scene.npcs.size()}, {"objects", scene.objects.size()}, {"layers", scene.layers.size()},
        {"source", source}, {"diagnostics", diagnostics}, {"records", records}, {"classification", townTraversal ? "source-town-traversal-incomplete-business" : "incomplete-source-test-exploration"}};
}

static PreparedMapExploration prepareSourceMap(Pvf &pvf, Assets &assets, World &world, const RegionCatalog &catalog,
    const MapAccessEntry &entry, bool testMode, bool townTraversal, const MonsterLevelPolicy &levelPolicy = {}) {
    PreparedMapExploration out;
    out.testMode = testMode; out.townTraversal = townTraversal;
    try {
        if (!testMode && !townTraversal) {
            issue(out, "incomplete_map_requires_explicit_test_exploration", {{"path", entry.path}});
            return out;
        }
        if (!entry.readable || entry.path.empty()) {
            issue(out, "map_access_entry_unreadable", {{"entry", entry.json()}}); return out;
        }
        out.source = makeSourceRef(pvf, entry.path).json();
        if (entry.source.packageIdentity != pvf.identity() || entry.source.memberPath != normalize(entry.path) ||
            entry.source.memberSha256 != out.source["member_sha256"])
            throw std::runtime_error("Map access entry does not match current PVF member identity");
        auto &scene = out.scene;
        scene.path = normalize(entry.path); scene.script = pvf.script(scene.path);
        scene.name = scene.script.text("[map name]", scene.path); scene.width = 0; scene.bg = 0;
        out.records.push_back({{"kind", "map_document"}, {"source", out.source}, {"ordered_fields", rawFields(scene.script)}, {"tokens", scene.script.tokens}});
        const auto ownBg = scene.script.values("[background pos]");
        if (!ownBg.empty()) {
            if (ownBg.size() != 1) throw std::runtime_error("MAP background origin has unexpected operands");
            const auto bg = number(ownBg[0]);
            if (std::floor(bg) != bg || bg < INT32_MIN || bg > INT32_MAX) throw std::runtime_error("MAP background origin cannot fit current Scene API");
            scene.bg = int(bg);
        } else if (entry.backgroundOriginKnown) {
            if (!std::isfinite(entry.backgroundOrigin) || std::floor(entry.backgroundOrigin) != entry.backgroundOrigin ||
                entry.backgroundOrigin < INT32_MIN || entry.backgroundOrigin > INT32_MAX)
                throw std::runtime_error("DGN background origin cannot fit current Scene API");
            scene.bg = int(entry.backgroundOrigin);
        } else issue(out, "background_origin_unknown_test_zero_presentation", {{"policy", "test-preview-zero-origin-v1"}});
        auto tileReceipt=loadSceneSourceTiles(pvf,assets,scene);
        const bool cursorKnown=tileReceipt.columnsResolved;
        for(auto &record:tileReceipt.records)out.records.push_back(std::move(record));
        for(auto &diagnostic:tileReceipt.diagnostics)out.diagnostics.push_back(std::move(diagnostic));
        if(!tileReceipt.complete)issue(out,"source_tile_geometry_or_placement_incomplete",{{"map",scene.path}});
        bool explicitWalk = false;
        for (size_t f = 0; f < scene.script.fields.size(); ++f) if (normalize(scene.script.fields[f].tag) == "[virtual movable area]") {
            const auto &values = scene.script.fields[f].values;
            if (!explicitWalk) { scene.walkRects.clear(); explicitWalk = true; }
            for (size_t i = 0; i < values.size(); i += 4) {
                auto record = placement(pvf, scene.script, f, i, slice(values, i, 4)); record["kind"] = "virtual_movable_area";
                try {
                    if (i + 4 > values.size()) throw std::runtime_error("Truncated source virtual rectangle");
                    const std::array<double, 4> rect{number(values[i]), number(values[i + 1]) + scene.bg, number(values[i + 2]), number(values[i + 3])};
                    if (rect[2] <= 0 || rect[3] <= 0) throw std::runtime_error("Empty source virtual rectangle");
                    scene.walkRects.push_back(rect); record["rect"] = rect;
                } catch (const std::exception &error) { record["error"] = error.what(); issue(out, "virtual_movable_record_unavailable", record); }
                out.records.push_back(std::move(record));
            }
        }
        // Source animations are independent records and preflight every frame,
        // so one missing image does not abort the rest of the map or fail later
        // only when the renderer reaches that frame.
        for (size_t f = 0; f < scene.script.fields.size(); ++f) if (normalize(scene.script.fields[f].tag) == "[animation]") {
            const auto &values = scene.script.fields[f].values;
            for (size_t i = 0; i < values.size(); i += 5) {
                auto record = placement(pvf, scene.script, f, i, slice(values, i, 5)); record["kind"] = "animation";
                try {
                    if (i + 5 > values.size() || !values[i].is_string() || !values[i + 1].is_string()) throw std::runtime_error("Malformed MAP animation tuple");
                    MapLayer layer; layer.animation = relative(scene.path, values[i].get<std::string>());
                    layer.sourceLayer = values[i + 1].get<std::string>(); layer.order = mapLayerOrder(layer.sourceLayer);
                    layer.x = number(values[i + 2]); layer.depthY = number(values[i + 3]) + scene.bg;
                    layer.y = layer.depthY - number(values[i + 4]);
                    preflightAnimation(assets, layer.animation); scene.layers.push_back(std::move(layer));
                } catch (const std::exception &error) { record["error"] = error.what(); issue(out, "animation_record_unavailable", record); }
                out.records.push_back(std::move(record));
            }
        }
        for (size_t f = 0; f < scene.script.fields.size(); ++f) if (normalize(scene.script.fields[f].tag) == "[ani info]") {
            auto record = placement(pvf, scene.script, f, 0, Json::array()); record["kind"] = "background_animation";
            try {
                MapLayer layer; layer.background = true; layer.y = scene.bg;
                bool closed = false;
                for (size_t j = f + 1; j < scene.script.fields.size(); ++j) {
                    const auto &field = scene.script.fields[j]; const auto tag = normalize(field.tag);
                    if (tag == "[/ani info]") { closed = true; break; }
                    if (tag == "[ani info]") throw std::runtime_error("Nested background ANI block");
                    record["raw"].push_back({{"tag", field.tag}, {"values", field.values}, {"offset", field.offset}});
                    if (tag == "[filename]" && field.values.size() == 1 && field.values[0].is_string()) layer.animation = relative(scene.path, field.values[0].get<std::string>());
                    else if (tag == "[layer]" && field.values.size() == 1 && field.values[0].is_string()) layer.sourceLayer = field.values[0].get<std::string>();
                    else if (tag == "[order]" && field.values.size() == 1 && field.values[0].is_string()) layer.sourceOrder = field.values[0].get<std::string>();
                    else if (tag == "[loop y axis]" && field.values.size() == 1) layer.loopY = integer(field.values[0]) == 1;
                    else if (tag == "[screen pos]" && field.values.size() == 2) {
                        layer.screenPosition = true; layer.x = number(field.values[0]); layer.y = number(field.values[1]);
                    } else throw std::runtime_error("Unsupported background ANI field/shape: " + field.tag);
                }
                if (!closed || layer.animation.empty()) throw std::runtime_error("Incomplete source background ANI block");
                configureMapBackground(layer, scene.script);
                const auto animation = preflightAnimation(assets, layer.animation);
                const auto &first = animation->frames.front();
                if (first.image.empty()) throw std::runtime_error("Background repeating dimensions unavailable");
                const auto pixels = assets.pixels(first.image, first.imageFrame);
                layer.repeatWidth = pixels.logicalWidth; layer.repeatHeight = pixels.logicalHeight;
                if (layer.repeatWidth <= 0) throw std::runtime_error("Invalid background repeat width");
                scene.layers.push_back(std::move(layer));
            } catch (const std::exception &error) { record["error"] = error.what(); issue(out, "background_record_unavailable", record); }
            out.records.push_back(std::move(record));
        }
        if (townTraversal) for (size_t f = 0; f < scene.script.fields.size(); ++f)
            if (normalize(scene.script.fields[f].tag) == "[town movable area]") {
                const auto &field = scene.script.fields[f];
                for (size_t i = 0; i < field.values.size(); i += 6) {
                    auto record = placement(pvf, scene.script, f, i, slice(field.values, i, 6)); record["kind"] = "town_exit";
                    try {
                        if (i + 6 > field.values.size()) throw std::runtime_error("Truncated source town exit");
                        TownExit exit; exit.x = number(field.values[i]); exit.y = number(field.values[i+1]) + scene.bg;
                        exit.width = number(field.values[i+2]); exit.height = number(field.values[i+3]);
                        exit.town = integer(field.values[i+4]); exit.area = integer(field.values[i+5]);
                        exit.offset = field.offset; exit.raw = slice(field.values, i, 6);
                        if (exit.width <= 0 || exit.height <= 0) throw std::runtime_error("Empty source town exit");
                        scene.townExits.push_back(std::move(exit));
                    } catch (const std::exception &error) { record["error"] = error.what(); issue(out, "town_exit_record_unavailable", record); }
                    out.records.push_back(std::move(record));
                }
            }
        std::map<int, std::vector<std::string>> npcPaths;
        try { npcPaths = npcRegistry(pvf); }
        catch (const std::exception &error) { issue(out, "npc_registry_unavailable", {{"error", error.what()}}); }
        for (size_t f = 0; f < scene.script.fields.size(); ++f) if (normalize(scene.script.fields[f].tag) == "[npc]") {
            const auto &values = scene.script.fields[f].values;
            for (size_t i = 0; i < values.size(); i += 5) {
                auto record = placement(pvf, scene.script, f, i, slice(values, i, 5)); record["kind"] = "npc";
                try {
                    if (i + 5 > values.size() || !values[i + 1].is_string()) throw std::runtime_error("Malformed source NPC tuple");
                    MapNpc npc; npc.id = integer(values[i]);
                    if (values[i + 1] != "[left]" && values[i + 1] != "[right]") throw std::runtime_error("Unknown source NPC direction");
                    npc.direction = values[i + 1] == "[left]" ? -1 : 1;
                    npc.x = number(values[i + 2]); npc.y = number(values[i + 3]) + scene.bg; npc.z = number(values[i + 4]);
                    npc.sourcePosition = {npc.x, npc.y - scene.bg, npc.z};
                    const auto found = npcPaths.find(npc.id);
                    if (found == npcPaths.end() || found->second.size() != 1) throw std::runtime_error("NPC registration absent or repeated");
                    npc.source = found->second.front(); const auto source = pvf.script(npc.source);
                    record["npc_source"] = makeSourceRef(pvf, npc.source).json(); record["npc_fields"] = rawFields(source);
                    npc.name = source.text("[field name]", source.text("[name]")); npc.voice = source.text("[field wav]");
                    npc.visibleOnDungeonClear = source.number("[visible on dungeon clear]", 0) != 0; npc.visible = !npc.visibleOnDungeonClear;
                    const auto literal = source.text("[field animation]");
                    if (!literal.empty()) { npc.animation = relative(npc.source, literal); preflightAnimation(assets, npc.animation); }
                    else issue(out, "npc_has_no_field_animation", {{"id", npc.id}, {"source", npc.source}});
                    scene.npcs.push_back(std::move(npc));
                } catch (const std::exception &error) { record["error"] = error.what(); issue(out, "npc_record_unavailable", record); }
                out.records.push_back(std::move(record));
            }
        }
        try {
            ObjectCatalog objects(pvf, assets);
            for (size_t f = 0; f < scene.script.fields.size(); ++f) {
                const auto &field = scene.script.fields[f]; const auto tag = normalize(field.tag);
                if (tag != "[passive object]" && tag != "[special passive object]") continue;
                Script projection = scene.script;
                // Retain every original field offset so the final object's
                // byte span stops at the following field, not end-of-MAP.
                for (size_t j = 0; j < projection.fields.size(); ++j) if (j != f) {
                    const auto other = normalize(projection.fields[j].tag);
                    if (other == "[passive object]" || other == "[special passive object]")
                        projection.fields[j].tag = "[exploration nonselected placement field]";
                }
                try {
                    Json parsing = Json::array();
                    const auto placements = objectPlacements(projection, "test-map:" + entry.key, entry.key, scene.bg, &parsing, &scene.script.rawBytes);
                    for (const auto &diagnostic : parsing) issue(out, "object_placement_unavailable", diagnostic);
                    for (auto value : placements) {
                        auto record = placement(pvf, scene.script, f, size_t(value.identity.recordOrdinal), value.raw); record["kind"] = "object";
                        try {
                            const auto definition = objects.definition(value.id);
                            record["object_source"] = makeSourceRef(pvf, definition->source).json(); record["object_fields"] = rawFields(definition->script);
                            for (const auto &motion : definition->motions) if (motion.animation) preflightAnimation(assets, motion.path);
                            for (const auto &diagnostic : definition->diagnostics) issue(out, "object_definition_partial", diagnostic);
                            scene.objectSystem.add(std::move(value), definition, currentObjectBehavior(*definition));
                        } catch (const std::exception &error) { record["error"] = error.what(); issue(out, "object_record_unavailable", record); }
                        out.records.push_back(std::move(record));
                    }
                } catch (const std::exception &error) { issue(out, "object_field_unavailable", {{"source", fieldSource(pvf, scene.script, f)}, {"error", error.what()}}); }
            }
            scene.refreshObjectViews();
            for (const auto &obstacle : scene.objectSystem.activeObstacles()) scene.blockedRects.push_back({obstacle.x, obstacle.y, obstacle.width, obstacle.height});
        } catch (const std::exception &error) { issue(out, "object_catalog_unavailable", {{"error", error.what()}}); }
        for (const auto &rect : scene.walkRects) if (explicitWalk || !cursorKnown) {
            const auto edge = std::ceil(rect[0] + rect[2] + 12);
            if (edge > 24 && edge <= INT32_MAX) scene.width = std::max(scene.width, int(edge));
        }
        std::stable_sort(scene.layers.begin(), scene.layers.end(), [](const MapLayer &a, const MapLayer &b) { return a.order < b.order; });
        // Private World owns preparation geometry/caches. Never borrow the live
        // world's previous room bounds or default185..340 walk rectangle.
        World candidate(pvf, assets, WorldRules::BetaFoundationV1);
        candidate.tick = world.tick; candidate.mapWidth = scene.width;
        candidate.walkRects = scene.walkRects; candidate.blockedRects = scene.blockedRects;
        out.geometryAvailable = !scene.walkRects.empty() && scene.width > 24;
        std::array<double, 2> requested{0, double(scene.bg)};
        bool sourceSpawn = false;
        for (const auto &field : scene.script.fields) if (normalize(field.tag) == "[player 1]") {
            try {
                if (field.values.size() != 3) throw std::runtime_error("Malformed player1 source spawn");
                requested = {number(field.values[0]), number(field.values[1]) + scene.bg}; sourceSpawn = true;
                issue(out, "source_player_spawn_z_retained_current_xy_entry", {{"z", number(field.values[2])}});
            } catch (const std::exception &error) { issue(out, "player_source_spawn_unavailable", {{"error", error.what()}}); }
            break;
        }
        if (!sourceSpawn) {
            const auto start = scene.script.values("[dungeon start area]");
            try {
                if (start.size() == 4) {
                    requested = {number(start[0]) + number(start[2]) / 2, number(start[1]) + scene.bg + number(start[3]) / 2}; sourceSpawn = true;
                }
            } catch (const std::exception &error) { issue(out, "dungeon_start_area_unavailable", {{"error", error.what()}}); }
        }
        if (out.geometryAvailable) {
            if (!sourceSpawn) {
                const auto &rect = scene.walkRects.front(); requested = {rect[0] + rect[2] / 2, rect[1] + rect[3] / 2};
                issue(out, "test_spawn_selected_from_first_source_walk_cell", {{"policy", "inferred-test-preview-first-source-cell-v1"}});
            }
            out.playerSpawn = candidate.nearestWalkable(requested[0], requested[1]);
            if (!candidate.canWalk(out.playerSpawn[0], out.playerSpawn[1])) out.geometryAvailable = false;
            else if (out.playerSpawn != requested) issue(out, "test_spawn_recovered_to_source_walk_union", {{"requested", requested}, {"resolved", out.playerSpawn}});
        }
        if (!out.geometryAvailable) {
            out.playerSpawn = requested;
            issue(out, "no_usable_source_walk_geometry", {{"test_free_movement_requires_separate_platform_policy", true}, {"source_geometry_fabricated", false}});
        }
        size_t spawnOrdinal = 0;
        for (size_t f = 0; f < scene.script.fields.size(); ++f) if (!townTraversal && normalize(scene.script.fields[f].tag) == "[monster]") {
            const auto &field = scene.script.fields[f];
            try {
                const auto spawns = parseMonsterSpawns(field.values);
                size_t valueIndex = 0;
                for (const auto &spawn : spawns) {
                    auto record = placement(pvf, scene.script, f, valueIndex, spawn.raw); record["kind"] = "monster"; record["spawn_ordinal"] = spawnOrdinal;
                    try {
                        if (!out.geometryAvailable) throw std::runtime_error("Actor position cannot be validated without source walk geometry");
                        if (!levelPolicy.adapted() && spawn.autoLevel && !entry.basisLevelKnown) throw std::runtime_error("DGN basis level unknown; no substitute monster level");
                        Script projection = scene.script; projection.fields = {{"[monster]", spawn.raw, field.offset}};
                        std::vector<Event> actorEvents;
                        auto actors = prepareSourceMonsterSpawns(candidate, catalog, projection, entry.dungeonId,
                            entry.basisLevelKnown ? entry.basisLevel : 0, scene.bg,
                            MonsterHpPolicy::inferredMobTableHpV1().id, "inferred-mob-combat-table-v1", DemoBalance{}, &actorEvents, nullptr, levelPolicy);
                        if (spawnOrdinal >= size_t(INT32_MAX)) throw std::runtime_error("Exploration actor ordinal overflow");
                        auto actor = std::move(actors.at(0)); actor.id = int(spawnOrdinal) + 1; actor.sourceStats["spawn"]["ordinal"] = spawnOrdinal;
                        // Keep exact source actor resources; never substitute a
                        // Goblin motion/attribute when this actor is unknown.
                        const auto motion = compileMonsterMotion(pvf, assets, actor.monsterPath, "stay");
                        if (!motion->valid()) throw std::runtime_error("Source actor stay motion unavailable: " + motion->error);
                        preflightAnimation(assets, motion->base->path);
                        for (const auto &track : motion->tracks) if (track.animation) preflightAnimation(assets, track.animation->path);
                        record["motion_references"] = motion->references; record["motion_issues"] = motion->issues;
                        actor.sourceStats["test_exploration"] = {{"combat_capability", false}, {"map_complete", false},
                            {"policy", "source-attributes-test-exploration-v1"}};
                        issue(out, "source_monster_preview_requires_ai_and_combat_capability", {{"monster", actor.monsterPath}, {"ordinal", spawnOrdinal}});
                        record["source_stats"] = actor.sourceStats;
                        for (auto &event : actorEvents) event.source = actor.id;
                        out.preparedEvents.insert(out.preparedEvents.end(), actorEvents.begin(), actorEvents.end());
                        out.monsters.push_back(std::move(actor));
                    } catch (const std::exception &error) { record["error"] = error.what(); issue(out, "monster_record_unavailable", record); }
                    valueIndex += spawn.raw.size(); ++spawnOrdinal; out.records.push_back(std::move(record));
                }
            } catch (const std::exception &error) { issue(out, "monster_field_unavailable", {{"source", fieldSource(pvf, scene.script, f)}, {"error", error.what()}, {"raw", field.values}}); }
        }
        if (townTraversal) issue(out, "source_town_traversal_business_capability_separate",
            {{"monster_admission", false}, {"completion_reward", false}, {"special_services_require_capability", true}});
        else issue(out, "test_exploration_has_no_gameplay_completion_grant", {{"topology_tasks_ai_mechanics", "not certified by map loading"},
            {"transitions", "source fields retained; exploration does not authorize town/dungeon gate activation"},
            {"source_entry", entry.json()}});
        scene.issues = out.diagnostics;
        out.ok = true;
    } catch (const std::exception &error) {
        issue(out, "map_exploration_preparation_failed", {{"path", entry.path}, {"error", error.what()}});
        out.ok = false;
    }
    return out;
}
PreparedMapExploration prepareMapExploration(Pvf &p, Assets &a, World &w, const RegionCatalog &c,
    const MapAccessEntry &entry, bool testMode, const MonsterLevelPolicy &levelPolicy) {
    return prepareSourceMap(p, a, w, c, entry, testMode, false, levelPolicy);
}
PreparedMapExploration prepareTownMapTraversal(Pvf &p, Assets &a, World &w, const RegionCatalog &c,
    const MapAccessEntry &entry) {
    return prepareSourceMap(p, a, w, c, entry, false, true);
}
} // namespace dnf
