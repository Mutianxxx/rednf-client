#include "dnf/map_exploration.hpp"
#include "dnf/session.hpp"
#include <stdexcept>

namespace dnf {
namespace {
Json eventState(const World &world) {
    Json value = Json::array();
    for (const auto &event : world.events) value.push_back({event.tick, event.kind, event.name, event.source, event.target, event.value});
    return value;
}
Json actorState(const World &world) {
    Json value = Json::array();
    for (const auto &actor : world.monsters) value.push_back(saveActor(actor, world.nowMs()));
    return value;
}
bool hasIssue(const PreparedMapExploration &value, const std::string &kind) {
    for (const auto &issue : value.diagnostics) if (issue.value("kind", std::string()) == kind) return true;
    return false;
}
size_t recordCount(const PreparedMapExploration &value, const std::string &kind) {
    size_t count = 0;
    for (const auto &record : value.records) if (record.value("kind", std::string()) == kind) ++count;
    return count;
}
} // namespace

Json runMapExplorationTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), examples = Json::array();
    auto check = [&](bool ok, const std::string &name) {
        if (!ok) throw std::runtime_error("Map exploration: " + name);
        checks.push_back(name);
    };
    MapAccessCatalog maps(pvf);
    RegionCatalog region(pvf, assets);
    World live(pvf, assets, WorldRules::BetaFoundationV1);
    live.tick = 120;
    live.mapWidth = 222;
    live.walkRects = {{12, 900, 150, 12}};
    live.blockedRects = {{20, 900, 10, 10}};
    Actor sentinel; sentinel.id = 19; sentinel.hp = 17; live.monsters.push_back(sentinel);
    live.events.push_back({live.tick, "fixture", "preserve-live-world", 19});
    const auto beforeSimulation = live.simulationCheckpoint(), beforeActors = actorState(live), beforeEvents = eventState(live);
    const auto beforePlayer = saveActor(live.player, live.nowMs());
    auto unchanged = [&] {
        return live.simulationCheckpoint() == beforeSimulation && actorState(live) == beforeActors && eventState(live) == beforeEvents &&
            saveActor(live.player, live.nowMs()) == beforePlayer && live.mapWidth == 222 &&
            live.walkRects == std::vector<std::array<double, 4>>{{12, 900, 150, 12}} &&
            live.blockedRects == std::vector<std::array<double, 4>>{{20, 900, 10, 10}};
    };
    auto entryFor = [&](const std::string &path) {
        const auto indices = maps.findByPath(path);
        if (indices.empty()) throw std::runtime_error("Missing exploration test MAP source: " + path);
        return maps.at(indices.front());
    };
    const auto forestEntry = entryFor("map/lorien/s0.map");
    const auto disabled = prepareMapExploration(pvf, assets, live, region, forestEntry, false);
    check(!disabled.ok && !disabled.complete && hasIssue(disabled, "incomplete_map_requires_explicit_test_exploration") && unchanged(),
        "Test exploration cannot grant normal gameplay admission or mutate a live room");
    auto wrongIdentity = forestEntry; wrongIdentity.source.memberSha256 = std::string(64, '0');
    const auto wrong = prepareMapExploration(pvf, assets, live, region, wrongIdentity, true);
    check(!wrong.ok && hasIssue(wrong, "map_exploration_preparation_failed") && unchanged(),
        "A stale/foreign selected MAP identity rejects before publication");
    auto unreadable = forestEntry; unreadable.readable = false;
    const auto missing = prepareMapExploration(pvf, assets, live, region, unreadable, true);
    check(!missing.ok && hasIssue(missing, "map_access_entry_unreadable") && unchanged(),
        "Unreadable catalog entries keep an explicit diagnostic without substituting another map");

    const auto forest = prepareMapExploration(pvf, assets, live, region, forestEntry, true);
    check(forest.ok && forest.testMode && !forest.complete && forest.geometryAvailable && forest.scene.path == forestEntry.path &&
        forest.scene.script.rawBytes == pvf.read(forestEntry.path) && recordCount(forest, "tile") == 5,
        "Actual forest preparation retains its original script bytes and every authored tile record");
    check(!forest.scene.walkRects.empty() && forest.scene.bg == 80 && forest.scene.width > 800 && !forest.scene.tiles.empty() &&
        forest.source["package_identity"] == pvf.identity() && forest.source["member_sha256"] == forestEntry.source.memberSha256,
        "Source-backed forest geometry, presentation origin and independent MAP identity are available");
    World projected(pvf, assets, WorldRules::BetaFoundationV1);
    projected.mapWidth = forest.scene.width; projected.walkRects = forest.scene.walkRects; projected.blockedRects = forest.scene.blockedRects;
    check(projected.canWalk(forest.playerSpawn[0], forest.playerSpawn[1]) && unchanged(),
        "Player spawn is recovered against the prepared source union without borrowing or replacing live geometry");
    check(recordCount(forest, "monster") == parseMonsterSpawns(forest.scene.script.values("[monster]")).size() &&
        recordCount(forest, "map_document") == 1 && forest.records[0].contains("tokens") && forest.records[0].contains("ordered_fields"),
        "All monster rows and ordered unknown MAP fields/tokens remain represented even when an actor is unavailable");
    for (const auto &actor : forest.monsters)
        check(!actor.handle && actor.monsterPath == region.monsterPath(actor.sourceId) && actor.hp == actor.maxHp && actor.combatAttributes &&
            actor.sourceStats["policy"] == "inferred-mob-table-hp-v1" && actor.sourceStats["test_exploration"]["combat_capability"] == false,
            "Prepared forest actor uses its own source HP/combat attributes and carries an incomplete exploration receipt");
    auto forestSummary = forest.json(); forestSummary.erase("records"); examples.push_back(std::move(forestSummary));

    for (const auto &path : {"map/bakalcastle/15076nagor.map", "map/gentsouthgate/(4,0)normal.map"}) {
        const auto entry = entryFor(path);
        const auto value = prepareMapExploration(pvf, assets, live, region, entry, true);
        const auto source = pvf.script(path);
        size_t expectedTiles = 0;
        for (const auto &field : source.fields) if (normalize(field.tag) == "[tile]") expectedTiles += field.values.size();
        check(value.ok && !value.complete && value.geometryAvailable && value.scene.script.rawBytes == source.rawBytes &&
            recordCount(value, "tile") == expectedTiles && hasIssue(value, "tile_grid_world_footprint_inferred"),
            "Non-Lorien MAP retains all tile slots and explicitly identifies inferred world footprint: " + std::string(path));
        check(recordCount(value, "monster") == parseMonsterSpawns(source.values("[monster]")).size() && unchanged(),
            "Cross-region MAP preserves every actor row without mutating the live World: " + std::string(path));
        for (const auto &actor : value.monsters)
            check(!actor.handle && actor.monsterPath == region.monsterPath(actor.sourceId) && actor.combatAttributes &&
                actor.sourceStats["spawn"]["map"] == path && actor.sourceStats["policy"] == "inferred-mob-table-hp-v1",
                "Cross-region actors never borrow Goblin identity or legacy/demo HP: " + std::string(path));
        auto summary = value.json(); summary.erase("records"); examples.push_back(std::move(summary));
    }
    const auto brokenEntry = entryFor("map/gbl_breeding/sample_(0,1)de2402.map");
    const auto partial = prepareMapExploration(pvf, assets, live, region, brokenEntry, true);
    check(partial.ok && !partial.complete && hasIssue(partial, "tile_dependency_or_placement_unavailable") &&
        partial.scene.script.rawBytes == pvf.read(brokenEntry.path) && recordCount(partial, "tile") > 0 && unchanged(),
        "A real MAP with missing source TIL records remains inspectable with independent diagnostics and original bytes");
    if (!partial.geometryAvailable)
        check(hasIssue(partial, "no_usable_source_walk_geometry") && partial.monsters.empty(),
            "Missing source geometry exposes no fake floor or guessed actor placements");
    const auto unknownLevel = [&] { auto value = forestEntry; value.basisLevelKnown = false; return value; }();
    const auto unknown = prepareMapExploration(pvf, assets, live, region, unknownLevel, true);
    check(unknown.ok && unknown.geometryAvailable && hasIssue(unknown, "monster_record_unavailable") &&
        recordCount(unknown, "monster") == recordCount(forest, "monster") && unknown.monsters.empty() && unchanged(),
        "Unknown DGN basis level diagnoses every auto-level monster while retaining the rest of the source map");
    return {{"status", "pass"}, {"checks", checks}, {"examples", examples},
        {"scope", "test-only private MAP preparation; no region/gameplay completion, normal admission, UI/feel/audio or original-client parity grant"}};
}
} // namespace dnf
