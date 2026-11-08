#include "dnf/region.hpp"
#include "dnf/progression.hpp"
#include "dnf/storage.hpp"
#include <chrono>
#include <climits>
#include <set>
#include <queue>
#include <stdexcept>
namespace dnf {
namespace {
// Prepared regressions, deliberately not executed in the staging handoff.
// Source-backed API coverage is distinct from normal combat/input acceptance.
Json basicDungeonClearRegressions(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    const auto check = [&](bool condition, const char *name) {
        if (!condition) throw std::runtime_error(std::string("Basic dungeon settlement: ") + name);
        checks.push_back(name);
    };
    const auto rejects = [](auto action) {
        try { action(); } catch (const std::exception &) { return true; }
        return false;
    };
    RegionCatalog catalog(pvf, assets, RegionPreparation::OnDemand);
    catalog.prepareWorldDungeonIndex();
    int dungeon = -1;
    for (const auto &[id, definition] : catalog.dungeons)
        if (definition.path == "dungeon/act2/draconiantower.dgn") dungeon = id;
    check(dungeon > 2, "The real Sky Tower fixture is registered outside the old Lorien whitelist");
    Progression progression(catalog);
    const auto pristine = progression.state;
    check(rejects([&] { progression.clearDungeon(dungeon, "not-prepared", 1); }) && progression.state == pristine,
        "Directory-only DGN cannot issue a clear receipt or rewards");
    check(catalog.prepareDungeonMetadata(dungeon).at("status") == "prepared" &&
        rejects([&] { progression.clearDungeon(dungeon, "metadata-only", 1); }) && progression.state == pristine,
        "DGN metadata alone does not replace prepared MAP and MOB dependencies");
    const auto preparation = catalog.prepareDungeon(dungeon);
    check(preparation.at("status") == "prepared" && !catalog.dungeons.at(dungeon).mapIds.empty(),
        "OnDemand prepares the entire source Sky Tower MAP and MOB closure");
    const auto &definition = catalog.dungeons.at(dungeon);
    progression.state["future_clear_data"] = {{"kept", 31}};
    check(progression.clearDungeon(dungeon, "sky-clear", 1) &&
        progression.state.at("xp") == int64_t(500) * definition.basisLevel &&
        progression.gold() == 200 * definition.basisLevel &&
        progression.state.at("clears").at("sky-clear").at("source") == definition.source.source &&
        progression.state.at("future_clear_data").at("kept") == 31,
        "A prepared non-Lorien DGN grants one named legacy-policy reward with exact source identity and unknown fields");
    const auto committed = progression.state;
    check(progression.dungeonClearRecorded(dungeon, "sky-clear", 1) &&
        !progression.clearDungeon(dungeon, "sky-clear", 1) && progression.state == committed,
        "Matching clear receipt is idempotent without issuing experience or gold again");
    check(rejects([&] { progression.clearDungeon(1, "sky-clear", 1); }) && progression.state == committed &&
        rejects([&] { progression.clearDungeon(dungeon, "sky-clear", 2); }) && progression.state == committed,
        "A reused run token with conflicting dungeon or room evidence rejects without modifying the receipt");
    Progression legacy(catalog);
    legacy.state["clears"]["legacy-clear"] = {{"dungeon", dungeon}, {"rooms", 2}, {"future", 41}};
    const auto legacyState = legacy.state;
    check(legacy.dungeonClearRecorded(dungeon, "legacy-clear", 2) &&
        !legacy.clearDungeon(dungeon, "legacy-clear", 2) && legacy.state == legacyState,
        "Old dungeon/rooms-only clear receipts and unknown nested fields remain unchanged and cannot regrant");
    Progression invalid(catalog);
    const auto invalidBase = invalid.state;
    const auto unchangedRejection = [&](const char *token) {
        const auto before = invalid.state;
        return rejects([&] { invalid.clearDungeon(dungeon, token, 1); }) && invalid.state == before;
    };
    invalid.state["gold"] = INT_MAX;
    check(unchangedRejection("gold-overflow"), "Gold overflow leaves XP, quests and the clear ledger byte-for-byte unchanged");
    invalid.state = invalidBase; invalid.state["xp"] = INT64_MAX;
    check(unchangedRejection("xp-overflow"), "Experience overflow cannot consume a run token or add gold");
    invalid.state = invalidBase; invalid.state["gold"] = UINT64_MAX;
    check(unchangedRejection("unsigned-gold"), "Oversized unsigned counters cannot narrow to apparently valid gold");
    invalid.state = invalidBase; invalid.state["level"] = 0;
    check(unchangedRejection("bad-level"), "Malformed normal progression level rejects before reward publication");
    invalid.state = invalidBase; invalid.state["clears"] = Json::array();
    check(unchangedRejection("bad-ledger"), "Malformed clear ledger rejects without silently recreating it");
    invalid.state = invalidBase; invalid.state["clears"]["broken-receipt"] = {{"dungeon", dungeon}, {"rooms", "bad"}};
    check(unchangedRejection("broken-receipt"), "Malformed existing receipt rejects without regranting");
    invalid.state = invalidBase;
    check(!invalid.clearDungeon(dungeon, "", 1) && invalid.state == invalidBase &&
        rejects([&] { invalid.clearDungeon(dungeon, "zero-room", 0); }) && invalid.state == invalidBase &&
        rejects([&] { invalid.clearDungeon(INT_MAX, "unknown", 1); }) && invalid.state == invalidBase,
        "Empty token, zero cleared rooms and an unregistered DGN cannot create a clear fact");
    const int mapId = definition.mapIds.front();
    auto missingMap = catalog.maps.extract(mapId);
    check(unchangedRejection("missing-map"), "Missing prepared MAP produces a specific source rejection without rewards");
    catalog.maps.insert(std::move(missingMap));
    int monsterId = -1;
    for (int id : definition.mapIds) for (const auto &spawn : catalog.maps.at(id).monsters) monsterId = spawn.id;
    check(monsterId > 0, "Prepared Sky Tower source contains an actual registered monster dependency");
    auto missingMonster = catalog.monsters.extract(monsterId);
    check(unchangedRejection("missing-mob"), "Missing prepared MOB cannot turn a source failure into a rewarded empty dungeon");
    catalog.monsters.insert(std::move(missingMonster));
    auto &quest = catalog.quests.at(102);
    quest.fields.insert(quest.fields.begin(), Field{"[int data]", Json::array({"bad-dungeon"}), 0});
    invalid.state["quests"]["102"] = {{"status", "active"}, {"progress", 0}, {"future", 51}};
    check(unchangedRejection("bad-clear-quest"), "Malformed active clear quest rejects its entire private reward candidate");
    quest.fields.erase(quest.fields.begin());
    Progression retryReference(catalog); retryReference.state = invalid.state;
    check(invalid.clearDungeon(dungeon, "bad-clear-quest", 1) &&
        retryReference.clearDungeon(dungeon, "bad-clear-quest", 1) && invalid.state == retryReference.state,
        "Correcting a source error retries the same token exactly like a clean first attempt");
    auto savedDefinition = catalog.dungeons.at(dungeon);
    auto &level100 = catalog.dungeons.at(dungeon);
    level100.basisLevel = 100;
    level100.source.fields.insert(level100.source.fields.begin(), Field{"[basis level]", Json::array({100}), 0});
    Progression hundred(catalog);
    check(hundred.clearDungeon(dungeon, "basis-100-local-model", 1) && hundred.gold() == 20000 &&
        hundred.state.at("xp") == 50000 && hundred.state.at("clears").at("basis-100-local-model").at("basis_level") == 100,
        "Local decoded-model boundary retains legitimate basis100 reward arithmetic without clamp99");
    level100 = std::move(savedDefinition);

    const auto actualItems = pvf.script("monster/newmonsters/heaven/nife_claese/nife_claese.mob");
    const auto decoded = decodeBasicMonsterItems(actualItems);
    check(actualItems.values("[item]").empty() && decoded.at("blocks").size() == 2 && decoded.at("rows").size() == 1 &&
        decoded.at("rows").at(0).at("item") == 3227 && decoded.at("rows").at(0).at("weight") == 800 &&
        decoded.at("rows").at(0).at("field_offset") == 787 && decoded.at("blocks").at(0).at("offset") == 667,
        "Real MOB56713 retains both sibling blocks and consumes second-block item3227/800 with exact source offsets");
    catalog.monsters[56713] = actualItems;
    Progression consumer(catalog); RandomStreams loot(19);
    check(consumer.recordKill(dungeon, 56713, 1, "second-item-api-fixture", 42, &loot) &&
        consumer.state.at("drops").at("second-item-api-fixture").at("item_source") == decoded,
        "Production recordKill consumes the repeated-item decoder and persists its ordered source trace even when the item gate is closed");
    Script fixture;
    fixture.path = "test/basic-item-siblings.mob";
    fixture.fields = {{"[item]",Json::array({3227,10}),2},{"[/item]",Json::array(),17},
        {"[item]",Json::array({3227,20,1106,-3}),22},{"[/item]",Json::array(),47}};
    const auto siblings = decodeBasicMonsterItems(fixture);
    check(siblings.at("rows").size() == 3 && siblings.at("rows").at(0).at("weight") == 10 &&
        siblings.at("rows").at(1).at("weight") == 20 && siblings.at("rows").at(2).at("weight") == 0 &&
        siblings.at("rows").at(2).at("source_weight") == -3,
        "Repeated item IDs retain row order and weights; legacy negative-weight clamp keeps its original source value");
    const auto validFields = fixture.fields;
    fixture.fields.insert(fixture.fields.begin(), Field{"[special rewards]",Json::array(),0});
    fixture.fields.push_back(Field{"[/special rewards]",Json::array(),52});
    check(rejects([&] { decodeBasicMonsterItems(fixture); }), "Unknown nested item scope is not merged into basic sibling rewards");
    fixture.fields = validFields; fixture.fields[2].values.push_back(17);
    check(rejects([&] { decodeBasicMonsterItems(fixture); }), "A malformed later sibling cannot hide behind an earlier valid item list");
    fixture.fields = validFields; fixture.fields[2].values[1] = UINT64_MAX;
    check(rejects([&] { decodeBasicMonsterItems(fixture); }), "A later oversized source weight rejects before any random draw");
    fixture.fields.clear();
    check(decodeBasicMonsterItems(fixture).at("rows").empty(), "A source monster with no item field remains a legitimate empty basic item list");

    // Reuse the production source-growth preflight pattern used by main.
    // This tests source failure before publishing candidate clear rewards.
    World world(pvf, assets, WorldRules::BetaFoundationV1);
    Progression live(catalog); world.applyEquipment(live);
    auto candidate = live;
    const int avatarUid = candidate.state.at("next_uid").get<int>();
    const auto *avatar = candidate.item(39180);
    check(avatar != nullptr, "Source qualification failure fixture uses the real unsupported limited-period avatar");
    candidate.state["inventory"].push_back({{"uid",avatarUid},{"id",39180},{"count",1},{"durability",avatar->durability}});
    candidate.state["next_uid"] = avatarUid+1; candidate.state["equipped"][avatar->slot] = avatarUid;
    const auto beforeLive = live.state, beforeWorld = world.snapshot(), beforeSimulation = world.simulationCheckpoint();
    check(candidate.clearDungeon(dungeon,"source-preflight-fails",1) &&
        rejects([&] { world.applyEquipment(candidate); }) && live.state == beforeLive &&
        world.snapshot() == beforeWorld && world.simulationCheckpoint() == beforeSimulation,
        "Failed equipment/growth preflight leaves live clear receipts, world attributes, clock and RNG unchanged");
    auto prepared = live;
    check(prepared.clearDungeon(dungeon,"prepared-clear",1), "A private source-ready clear candidate can be prepared after a rejected candidate");
    world.applyEquipment(prepared); live.commitPrepared(std::move(prepared));
    check(live.dungeonClearRecorded(dungeon,"prepared-clear",1) && world.characterLevel == live.level(),
        "Successful source preflight publishes matching world level and exactly one progression receipt");
    const auto directory = std::filesystem::absolute(std::filesystem::path("cache/basic-dungeon-clear-tests") /
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    CharacterStore store(directory, "basic-dungeon-clear-regression");
    store.data["characters"][0] = {{"name","Clear regression"},{"class","swordman"},{"identity",CharacterIdentity{}.json()}};
    store.capture(0,world,live); store.checkpoint();
    auto more = live; more.clearDungeon(dungeon,"next-clear",1);world.applyEquipment(more);live.commitPrepared(std::move(more));
    store.capture(0,world,live);
    const auto expected = live.state, expectedRandom = world.randomStreams().snapshot();
    const auto beforeGeneration = store.generation();
    store.setFailureInjector([](SaveFailurePoint point) { if(point==SaveFailurePoint::BeforePublish) throw std::runtime_error("Injected clear checkpoint publication failure"); });
    check(rejects([&] { store.checkpoint(); }) && store.hasPendingCommit() && store.generation()==beforeGeneration,
        "A failed clear checkpoint retains its exact pending generation instead of claiming durable success");
    store.setFailureInjector({});store.retryPending();
    check(store.generation()==beforeGeneration+1, "Retry publishes one frozen generation without executing clearDungeon again");
    store.close();
    CharacterStore recovered(directory,"basic-dungeon-clear-regression");
    World resumed(pvf,assets,WorldRules::BetaFoundationV1); Progression restored(catalog);
    recovered.apply(0,resumed,restored);
    check(restored.state==expected && resumed.randomStreams().snapshot()==expectedRandom &&
        !restored.clearDungeon(dungeon,"next-clear",1) && restored.state==expected,
        "Reload after checkpoint retry preserves the exact clear ledger, reward amounts and RNG and refuses duplicate rewards");
    recovered.close();
    return {{"checks",checks},{"check_count",checks.size()},{"source_preparation",preparation},
        {"scope","source-backed settlement API, decoded-model fault fixtures and isolated storage; no normal combat/input or full-DGN acceptance"}};
}
}
Json runRegionProgressionTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto require = [&](bool condition, const char *name) {
        if (!condition) throw std::runtime_error(std::string("Region/progression: ") + name);
        checks.push_back(name);
    };
    RegionCatalog catalog(pvf, assets);
    require(catalog.townAreas.size() == 3 && catalog.townAreas[2].worldmap == 1 &&
            catalog.dungeons.size() == 4 && catalog.dungeons.at(1).enabled && !catalog.dungeons.at(1500).enabled,
            "TWN/worldmap original IDs and disabled ancient dungeons");
    require(catalog.maps.size() == 35 && catalog.dungeons.at(1).mapIds.size() == 16 &&
            catalog.dungeons.at(2).mapIds.size() == 19 && catalog.maps.at(16).special &&
            catalog.maps.at(16).path == "map/lorien/5.map", "All 35 source MAPs retained; special quest map excluded from normal pool");
    require(catalog.npcs.at(1).shop == 2 && catalog.npcs.at(2).shop == 15 &&
            catalog.npcs.at(1000).shop == 1000 && catalog.npcs.at(1000).clearOnly &&
            catalog.shops.at(1000).path == "itemshop/equipmentshop_dungeon1.shp", "NPC/shop source registration and clear merchant");
    auto spawns = parseMonsterSpawns(Json::array({71,1,15,173,28,0,2,2,"[half]","[champion]",2,10,12,
        63024,1,0,523,268,0,1,1,"[fixed]","[NPC]",1020,"[boss]",3,0,15,188,57,0,1,1,"[ratio]","[normal]"}));
    require(spawns.size() == 3 && spawns[0].traits.size() == 2 && spawns[1].npcOnDeath == 1020 &&
            spawns[1].type == "[boss]" && spawns[2].id == 3, "Variable-length champion and NPC-death records do not shift next monster");
    bool rejected = false;
    try { parseMonsterSpawns(Json::array({1,1,0,0,0,0,1,1,"[fixed]","[champion]",2,4})); } catch (...) { rejected = true; }
    require(rejected, "Truncated champion traits rejected explicitly");
    std::set<int> selected, candidateSources; std::set<int> directions;
    Json cases = Json::array();
    for (int dungeon : {1, 2}) {
        for (uint64_t seed = 1; seed <= 96; ++seed) {
            auto run = DungeonRun::generate(catalog, dungeon, seed);
            auto repeat = DungeonRun::generate(catalog, dungeon, seed);
            if (run.describe() != repeat.describe()) throw std::runtime_error("Dungeon seed is not reproducible");
            if (run.rooms.empty() || run.start == run.boss) throw std::runtime_error("Invalid run endpoints");
            std::set<int> reached{run.start}; std::queue<int> queue; queue.push(run.start);
            while (!queue.empty()) {
                int index = queue.front(); queue.pop(); run.current = index;
                const auto &room = run.room(); const auto &map = catalog.maps.at(room.mapId);
                if (map.special || (room.doors & ~map.allowedDoors) || (room.doors & map.requiredDoors) != map.requiredDoors || map.boss != room.boss)
                    throw std::runtime_error("Run selected incompatible source MAP");
                selected.insert(room.mapId); candidateSources.insert(room.candidates.begin(), room.candidates.end());
                for (int d = 0; d < 4; ++d) {
                    Direction direction = Direction(d); int next = run.destination(direction);
                    if (!(room.doors & directionBit(direction))) {
                        if (next != -1) throw std::runtime_error("Nonexistent room edge permitted");
                        continue;
                    }
                    if (next < 0) throw std::runtime_error("Open door without reciprocal room");
                    directions.insert(d); run.current = next;
                    if (run.destination(opposite(direction)) != index) throw std::runtime_error("Non-reciprocal dungeon edge");
                    run.current = index;
                    if (reached.insert(next).second) queue.push(next);
                }
            }
            if (reached.size() != run.rooms.size() || !reached.count(run.boss)) throw std::runtime_error("Disconnected dungeon");
            run.current = run.start;
            for (int d = 0; d < 4; ++d) if (run.move(Direction(d))) throw std::runtime_error("Uncleared room movement accepted");
            run.room().cleared = true;
            bool moved = false;
            for (int d = 0; d < 4; ++d) if (run.destination(Direction(d)) >= 0) { moved = run.move(Direction(d)); break; }
            if (!moved || !run.room().visited) throw std::runtime_error("Cleared room did not open reciprocal transition");
            run.rooms.at(run.boss).cleared = true;
            if (!run.complete()) throw std::runtime_error("Boss clear not recognized");
            if (seed == 1) cases.push_back(run.describe());
        }
    }
    require(directions.size() == 4, "192 reproducible seeded runs: source compatibility, connected graph, all four directions and room clear gates");
    Json unavailable = Json::array();
    for (const auto &[id, map] : catalog.maps) if (!candidateSources.count(id)) unavailable.push_back({{"id", id}, {"path", map.path},
        {"reason", map.special ? "special quest source has no greed" : "not reached by sampled strict source topology; not silently inserted"}});
    Progression p(catalog);
    require(p.level() == 1 && p.gold() == 0 && p.quantity(27118) == 1 && p.attackBonus() == 5 &&
            p.experienceToNextLevel() == 1000, "Original starter definition and PC XP threshold, explicit new-character policy");
    require(!p.buy(2,1106).ok && !p.buy(999,1106).ok, "Shop availability and insufficient funds enforced");
    require(p.acceptQuest(101,2).ok && !p.turnInQuest(101,1).ok && p.talkNpc(1).ok && p.turnInQuest(101,1).ok &&
            !p.turnInQuest(101,1).ok && p.gold() == 100, "Meet NPC task, correct giver/receiver and exactly-once quest reward");
    require(p.acceptQuest(102,1).ok && p.clearDungeon(1,"test-run-one",3) && !p.clearDungeon(1,"test-run-one",3) &&
            p.turnInQuest(102,1).ok && p.level() == 2 && p.quantity(16400) == 1, "Lorien clear task, duplicate result guard, source belt and XP promotion");
    require(p.acceptQuest(103,1).ok, "Deep Lorien task unlocks at source level and prerequisite");
    for (int n = 0; n < 10; ++n) {
        std::string key = "test-deep:" + std::to_string(n);
        if (!p.recordKill(2,1,2,key,42) || p.recordKill(2,1,2,key,42)) throw std::runtime_error("Duplicate kill processed");
    }
    require(p.questReady(103) && p.turnInQuest(103,1).ok && p.quantity(1106) == 5 && p.quantity(1112) == 5 &&
            p.quantity(27601) == 1 && p.quantity(29901) == 0, "Ten source-specific kills across events; swordman-only original reward branch");
    require(p.acceptQuest(4301,1).ok && !p.turnInQuest(4301,1).ok && p.talkNpc(2).ok && p.turnInQuest(4301,2).ok &&
            !p.questAvailable(104), "Quest chain 101/102/103/4301 completes; outside-region 104 remains unavailable");
    int beforeGold = p.gold();
    require(p.state["drops"].size() == 10 && p.claimDrop("test-deep:0").ok && !p.claimDrop("test-deep:0").ok &&
            p.gold() == beforeGold + 30, "Kill creates persistent ground drop; explicit pickup grants once");
    int katana = -1, hpPotion = -1;
    for (size_t i = 0; i < p.state["inventory"].size(); ++i) {
        if (p.state["inventory"][i]["id"] == 27601) katana = int(i);
        if (p.state["inventory"][i]["id"] == 1106) hpPotion = int(i);
    }
    require(katana >= 0 && hpPotion >= 0 && p.equip(katana).ok && p.equippedWeapon() == 1 && p.attackBonus() == 27 &&
            !p.sell(katana).ok, "Source katana level/appearance/stats equipped; equipped item cannot be sold");
    Json before = p.state;
    p.state["level"] = 1;
    require(!p.equip(katana).ok, "Equipment minimum level enforced"); p.state = before;
    p.wear(3); int repair = p.repairCost(katana); p.state["gold"] = 0; before = p.state;
    require(repair > 0 && !p.repair(katana).ok && p.state == before, "Repair cannot mutate durability with insufficient funds");
    p.state["gold"] = repair;
    require(p.repair(katana).ok && p.gold() == 0 && p.state["inventory"][katana]["durability"] == 35,
            "Repair applies documented proportional source-price policy atomically");
    int quantity = p.quantity(1106); auto potion = p.usePotion(hpPotion,100,10,180,10,140);
    require(potion.ok && potion.hp == 70 && p.quantity(1106) == quantity - 1 &&
            !p.usePotion(hpPotion,101,10,180,10,140).ok && p.usePotion(hpPotion,10100,10,180,10,140).ok,
            "Source potion recovery amount and cooldown group charge a stack once");
    p.state["gold"] = 1000; p.state["future_progression"] = {{"kept", 17}};
    Json saved = p.state; Progression reload(catalog); reload.load(saved);
    require(reload.state["future_progression"] == saved["future_progression"] && reload.questCompleted(4301) &&
            !reload.recordKill(2,1,2,"test-deep:0",42) && !reload.clearDungeon(1,"test-run-one",3) &&
            !reload.claimDrop("test-deep:0").ok, "Progression reload preserves future fields and kill/clear/pickup reward ledgers");
    // Fill independent equipment instances; failed shop/pickup must leave counters and stacks untouched.
    Progression full(catalog); full.state["gold"] = 10000;
    auto entry = full.state["inventory"][0];
    while (full.state["inventory"].size() < Progression::inventoryCapacity) {
        entry["uid"] = int(full.state["inventory"].size()) + 1; full.state["inventory"].push_back(entry);
    }
    full.state["next_uid"] = 49; before = full.state;
    require(!full.buy(2,1106).ok && full.state == before, "Full inventory purchase rolls back gold and contents");
    full.state["drops"]["full-test"] = {{"gold", 30}, {"items", Json::array({{{"id",1106},{"count",1}}})}, {"claimed", false}};
    before = full.state;
    require(!full.claimDrop("full-test").ok && full.state == before, "Full inventory ground drop remains available without partial reward");
    const auto directory = std::filesystem::path("reports/test-saves/region") / std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    CharacterStore store(directory); World world(pvf,assets);
    store.data["schema"] = 2;
    store.data["future_root"] = 31;
    store.data["characters"][0] = {{"name","Region"},{"class","swordman"},{"level",2},{"weapon",2},{"future_character",19}};
    store.apply(0,world,reload); reload.load(saved); world.characterLevel = reload.level();
    store.capture(0,world,reload); store.save(); store.save();
    store.close();
    CharacterStore durable(directory); Progression restored(catalog); durable.apply(0,world,restored);
    require(durable.data["schema"] == 5 && durable.data["characters"].size() == 20 && durable.data["future_root"] == 31 &&
            durable.data["characters"][0]["future_character"] == 19 && restored.questCompleted(4301) &&
            durable.data["characters"][0]["level"] == restored.level(), "Schema2 to5 with 20 slots, identity, level capture, inventory and unknown fields preserved");
    durable.close();
    writeJson(directory / "characters.json", {{"damaged",true}});
    CharacterStore backup(directory); backup.apply(0,world,restored);
    require(restored.questCompleted(4301) && !backup.warnings.empty(), "Schema3 progression survives corrupt-primary backup recovery");
    const auto basicSettlement = basicDungeonClearRegressions(pvf,assets);
    return {{"status","pass"},{"checks",checks},{"basic_dungeon_settlement",basicSettlement},{"seeded_runs",192},{"selected_maps",selected},{"candidate_sources",candidateSources},
            {"unselected_sources",unavailable},{"examples",cases},{"scope","core content/persistence; visual and physical input acceptance separate"}};
}
} // namespace dnf
