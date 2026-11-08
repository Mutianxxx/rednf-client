#include "dnf/monster_behavior.hpp"
#include "dnf/monster_spawn.hpp"
#include "dnf/session.hpp"
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
Script routeFixture(const Pvf &pvf, std::vector<Field> fields,
                    const std::string &path = "monster/newmonsters/heaven/jena/fixture.mob") {
    Script script;
    script.path = path;
    script.source = {{"package_identity", pvf.identity()}, {"literal_path", path}};
    script.rawBytes = {0xb0, 0xd0};
    auto token = [&](int type, const Json &value) {
        const auto offset = script.rawBytes.size();
        int32_t raw = value.is_number_integer() && value >= std::numeric_limits<int32_t>::min() &&
            value <= std::numeric_limits<int32_t>::max() ? value.get<int32_t>() : 0;
        if (type == 4 && value.is_number()) {
            const auto number = value.get<float>();
            std::memcpy(&raw, &number, 4);
        }
        script.rawBytes.resize(offset + 5);
        script.rawBytes[offset] = uint8_t(type);
        std::memcpy(script.rawBytes.data() + offset + 1, &raw, 4);
        script.tokens.push_back({{"offset", offset}, {"type", type}, {"raw", raw}, {"value", value}});
    };
    for (auto &field : fields) {
        field.offset = script.rawBytes.size();
        token(5, field.tag);
        for (const auto &value : field.values) token(value.is_number_float() ? 4 : value.is_string() ? 7 : 2, value);
        script.fields.push_back(std::move(field));
    }
    return script;
}
bool diagnostic(const MonsterActionRoute &route, const std::string &kind) {
    for (const auto &value : route.diagnostics) if (value.value("kind", std::string()) == kind) return true;
    return false;
}
Json eventsJson(const std::vector<Event> &events) {
    Json result = Json::array();
    for (const auto &event : events) result.push_back({event.tick, event.kind, event.name, event.source, event.target, event.value});
    return result;
}
Json actorsJson(const World &world) {
    Json result = Json::array();
    for (const auto &actor : world.monsters) result.push_back(saveActor(actor, world.nowMs()));
    return result;
}
} // namespace

Json runMonsterBehaviorTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool value, const std::string &name) {
        if (!value) throw std::runtime_error("Monster source behavior: " + name);
        checks.push_back(name);
    };
    auto rejects = [&](auto operation, const std::string &name) {
        bool failed = false;
        try { operation(); } catch (const std::exception &) { failed = true; }
        check(failed, name);
    };
    const auto jena = pvf.script("monster/newmonsters/heaven/jena/jena.mob");
    const auto nagor = pvf.script("monster/newmonsters/dimensiongate/bakal/dark_dragon_nagor/dark_dragon_nagor.mob");
    const auto goblin = pvf.script("monster/goblin/goblin.mob");
    const auto beforeJena = jena.rawBytes;
    const auto dash = selectMonsterAction(pvf, jena, "attack", 4);
    check(dash.ok && dash.engine == MonsterActionEngine::Act && dash.sourceActionIndex == 4 &&
        dash.selectedTag == "[action list]" && dash.literalPath == "Action/Dash.act" &&
        dash.resolvedPath == "monster/newmonsters/heaven/jena/action/dash.act",
        "Actual Jena authored index4 selects Dash through MOB instead of a hardcoded controller path");
    check(dash.source.packageIdentity == pvf.identity() && dash.source.memberPath == jena.path &&
        dash.source.memberSha256 == "94ce957f65f431c367f01997277e3f535bf45006a6e1c32374bbf0850308228c" &&
        dash.source.byteOffset == 732 && dash.source.byteLength == 5 && dash.source.ordinal == 49 &&
        dash.fieldSource.byteOffset == 707 && dash.fieldSource.byteLength == 5 &&
        dash.resolvedSource.memberSha256 == "9f6c90d8085fdfb1dccd4e2c86bf2b08cec5060fb267df846ffc6cbe1dc41b0f",
        "Actual route retains MOB identity, field ordinal and exact operand offset plus independent target identity");
    check(dash.cooldownMs == 10000 && dash.cooldownSource && dash.cooldownSource->byteOffset == 802 &&
        dash.attackInfoLiteral && dash.attackInfoLiteral->empty() && dash.attackInfoSource &&
        dash.attackInfoSource->byteOffset == 767 && dash.attackInfoResolvedPath.empty(),
        "Actual Jena index4 retains its10000ms cooldown and explicitly empty ATK slot without shifting indices");
    const auto light = selectMonsterAction(pvf, jena, "attack", 1);
    check(light.ok && light.cooldownMs == 5000 && light.attackInfoLiteral == "AttackInfo/LightAttack.atk" &&
        light.attackInfoResolvedPath == "monster/newmonsters/heaven/jena/attackinfo/lightattack.atk" &&
        light.attackInfoSource && light.attackInfoSource->byteOffset == 752,
        "Actual Jena index1 pairs its own LightAttack ATK and cooldown");
    bool aiHero = false, leakedDifficultyHero = false, closedAi = false;
    for (const auto &field : dash.pairedSourceFields) {
        if (field["tag"] == "[hero]" && field["offset"] == 982 && field["scopes"] == Json::array({"[ai pattern]"})) aiHero = true;
        if (field["tag"] == "[hero]" && field["offset"] == 1082) leakedDifficultyHero = true;
        if (field["tag"] == "[/ai pattern]") closedAi = true;
    }
    check(aiHero && closedAi && !leakedDifficultyHero && dash.allValues.size() == 5 && dash.fieldTokens.size() == 6 && jena.rawBytes == beforeJena,
        "Complete authored action values, raw tokens and nested AI fields survive without merging later difficulty scopes");
    const auto waiting = selectMonsterAction(pvf, nagor, "stay");
    check(waiting.ok && waiting.engine == MonsterActionEngine::Act &&
        waiting.resolvedPath == "monster/newmonsters/dimensiongate/bakal/dark_dragon_nagor/action/stay.act" &&
        waiting.source.memberSha256 == "c4b86b9bac737d9da78da7b3bac278c9bdf83a433d4eac7f2a21fc2b57843567",
        "Actual Nagor waiting ACT resolves from its current source MOB");
    const auto old = selectMonsterAction(pvf, goblin, "stay");
    check(old.ok && old.engine == MonsterActionEngine::LegacyAni && old.selectedTag == "[waiting motion]" &&
        old.resolvedPath == "monster/goblin/animation_goblin2/stay.ani" && old.source.byteOffset == 507,
        "Actual legacy Goblin selects ANI and never fabricates an ACT definition");
    const std::string act = "Action/Dash.act", ani = "Animation_Goblin2/Stay.ani";
    auto fixture = [&](std::vector<Field> fields) { return routeFixture(pvf, std::move(fields)); };
    const auto holes = fixture({{"[action list]", Json::array({act, "", act})},
        {"[attack info]", Json::array({"", "", ""})}, {"[cooltime]", Json::array({100, 200, 300})}});
    const auto empty = selectMonsterAction(pvf, holes, "attack", 1), later = selectMonsterAction(pvf, holes, "attack", 2);
    check(!empty.ok && diagnostic(empty, "empty_or_invalid_authored_action_slot"), "Authored empty slot rejects only that request");
    check(later.ok && later.sourceActionIndex == 2 && later.cooldownMs == 300 && later.source.byteOffset == 17 &&
        later.cooldownSource && later.cooldownSource->byteOffset == 57,
        "Later action and cooldown retain authored index2 across the empty slot");
    check(!selectMonsterAction(pvf, holes, "attack", -1).ok && !selectMonsterAction(pvf, holes, "attack", 3).ok &&
        !selectMonsterAction(pvf, holes, "unknown", 0).ok, "Negative, out-of-range and unknown requests do not mutate or fall back");
    const auto basic = fixture({{"[basic action]", Json::array({act})}, {"[waiting action]", Json::array({"Action/Stay.act"})}});
    check(selectMonsterAction(pvf, basic, "stay").literalPath == act && selectMonsterAction(pvf, basic, "move").literalPath == act,
        "Explicit basic action supersedes both singleton stay and move");
    const auto badBasic = fixture({{"[basic action]", Json::array({ani})}, {"[waiting action]", Json::array({act})},
        {"[waiting motion]", Json::array({ani})}});
    check(!selectMonsterAction(pvf, badBasic, "stay").ok, "Malformed explicit basic action blocks despite valid waiting alternatives");
    check(diagnostic(selectMonsterAction(pvf, fixture({{"[action list]", Json::array({act})},
        {"[attack action]", Json::array({act})}}), "attack"), "ambiguous_attack_action_spellings"),
        "Both attack spellings remain ambiguous without a version policy");
    check(diagnostic(selectMonsterAction(pvf, fixture({{"[waiting action]", Json::array({act})},
        {"[waiting action]", Json::array({act})}}), "stay"), "repeated_action_field_ambiguous"),
        "Repeated identical action fields reject rather than choosing first or last");
    for (const auto &values : {Json::array(), Json::array({act, act}), Json::array({7}), Json::array({""})})
        check(!selectMonsterAction(pvf, fixture({{"[waiting action]", values}}), "stay").ok,
            "Malformed singleton arity or operand rejects: " + values.dump());
    check(!selectMonsterAction(pvf, basic, "stay", 1).ok, "Singleton states cannot accept list indices");
    check(!selectMonsterAction(pvf, fixture({{"[action list]", Json::array({act})},
        {"[cooltime]", Json::array({1, 2})}}), "attack").ok,
        "Mismatched paired cooldown count blocks an otherwise resolvable action");
    for (const auto &values : {Json::array({-1}), Json::array({1.5}), Json::array({"pattern"}),
            Json::array({uint64_t(std::numeric_limits<uint64_t>::max())})})
        check(!selectMonsterAction(pvf, fixture({{"[action list]", Json::array({act})},
            {"[cooltime]", values}}), "attack").ok, "Invalid cooldown operand blocks without narrowing: " + values.dump());
    check(!selectMonsterAction(pvf, fixture({{"[action list]", Json::array({act, act})},
        {"[cooltime]", Json::array({1, "pattern"})}}), "attack", 0).ok,
        "A complex cooldown array cannot pass merely because its selected operand is numeric");
    const auto scoped = selectMonsterAction(pvf, fixture({{"[action list]", Json::array({act})},
        {"[pattern]", Json::array()}, {"[unknown nested condition]", Json::array({42})},
        {"[cooltime]", Json::array({1})}, {"[/pattern]", Json::array()}}), "attack");
    bool unknownPreserved = false;
    for (const auto &field : scoped.pairedSourceFields) if (field["tag"] == "[unknown nested condition]" && field["values"] == Json::array({42})) unknownPreserved = true;
    check(!scoped.ok && unknownPreserved, "Nested cooldown semantics block while preserving unknown complete pattern fields");
    check(!selectMonsterAction(pvf, fixture({{"[action list]", Json::array({act})},
        {"[attack info]", Json::array({"Action/Dash.act"})}}), "attack").ok,
        "Paired ATK cannot accept an ACT resource even when the file exists");
    for (const auto &path : {"/monster/newmonsters/heaven/jena/action/dash.act", "C:/dash.act", "../../../../../../dash.act", "missing.act"})
        check(!selectMonsterAction(pvf, fixture({{"[waiting action]", Json::array({path})}}), "stay").ok,
            "Absolute, escaping or missing action resource blocks: " + std::string(path));
    auto corrupt = holes; corrupt.tokens[1]["offset"] = 8;
    check(!selectMonsterAction(pvf, corrupt, "attack", 2).ok, "Misaligned literal tokens cannot claim a precise source reference");
    corrupt = holes; corrupt.rawBytes[7] = 2;
    check(!selectMonsterAction(pvf, corrupt, "attack", 2).ok, "Raw token byte kind must match ordered decoded tokens");
    corrupt = holes; corrupt.fields[0].values[0] = "Action/Stay.act";
    check(!selectMonsterAction(pvf, corrupt, "attack", 2).ok, "Changed decoded operands cannot reuse the old source bytes");
    corrupt = holes; corrupt.source["package_identity"] = "another-pvf";
    check(!selectMonsterAction(pvf, corrupt, "attack", 2).ok, "MOB and resource resolution must share one PVF identity");

    RegionCatalog catalog(pvf, assets);
    const auto cachedDungeonCount = catalog.dungeons.size(), cachedMonsterCount = catalog.monsters.size();
    check(catalog.monsterPath(56721) == nagor.path && catalog.monsterPath(56503) == jena.path &&
        catalog.dungeons.size() == cachedDungeonCount && catalog.monsters.size() == cachedMonsterCount,
        "Cross-region MOB registry lookup does not require opening either dungeon");
    World world(pvf, assets, WorldRules::BetaFoundationV1);
    world.walkRects = {{12, 0, 1176, 1000}};
    world.events.push_back({0, "fixture", "preserve", 0, 0, 0});
    Actor sentinel; sentinel.id = 77; world.monsters.push_back(sentinel);
    const auto beforeActors = actorsJson(world), beforeEvents = eventsJson(world.events), beforeSimulation = world.simulationCheckpoint();
    const auto nagorMap = pvf.script("map/bakalcastle/15076nagor.map");
    const auto jenaMap = pvf.script("map/gentsouthgate/(4,0)normal.map");
    std::vector<Event> prepared;
    const auto nagorActors = prepareSourceMonsterSpawns(world, catalog, nagorMap, 65, 70, 80,
        "legacy-demo-v1", "legacy-snapshot-damage-v1", DemoBalance{}, &prepared);
    check(nagorActors.size() == 1 && nagorActors[0].sourceId == 56721 && nagorActors[0].monsterPath == nagor.path &&
        nagorActors[0].x == 519 && nagorActors[0].y == 338 && !nagorActors[0].handle &&
        selectMonsterAction(pvf, pvf.script(nagorActors[0].monsterPath), "stay").resolvedPath == waiting.resolvedPath,
        "Normal factory consumes the actual Nagor MAP row and produces a source-routable detached actor");
    const auto jenaActors = prepareSourceMonsterSpawns(world, catalog, jenaMap, 82, 60, 80,
        "legacy-demo-v1", "legacy-snapshot-damage-v1", DemoBalance{}, &prepared);
    size_t foundJena = 0;
    for (size_t i = 0; i < jenaActors.size(); ++i) if (jenaActors[i].sourceId == 56503) {
        ++foundJena;
        const auto &actor = jenaActors[i];
        check(i == 7 && actor.id == 8 && actor.x == 651 && actor.y == 331 && actor.z == 0 &&
            actor.sourceStats["spawn"] == Json({{"map", jenaMap.path}, {"map_provenance", jenaMap.source},
                {"ordinal", 7}, {"dungeon", 82}, {"basis_level", 60},
                {"raw", Json::array({56503, 1, 0, 651, 251, 0, 1, 1, "[fixed]", "[normal]"})},
                {"source_resolved_level", 60}, {"source_level_error", nullptr},
                {"effective_level", 60}, {"level_policy", MonsterLevelPolicy{}.json()}}),
            "Actual Jena keeps MAP ordinal7, source row, provenance and background-origin adjustment");
    }
    check(foundJena == 1 && actorsJson(world) == beforeActors && eventsJson(world.events) == beforeEvents &&
        world.simulationCheckpoint() == beforeSimulation,
        "Successful cross-region preparation leaves published actors, events, clock, IDs and RNG unchanged");
    Script map;
    map.path = "fixture/source-spawn.map";
    map.source = {{"package_identity", pvf.identity()}, {"unknown_future_metadata", Json::array({7, 7})}};
    map.fields = {{"[monster]", Json::array({1, 1, 0, 200, 200, 0, 1, 1, "[fixed]", "[normal]"})}};
    const auto sourceActors = prepareSourceMonsterSpawns(world, catalog, map, 1, 1, 0, "",
        "inferred-mob-combat-table-v1", DemoBalance{});
    check(sourceActors.size() == 1 && sourceActors[0].hp == 35 && sourceActors[0].maxHp == 35 &&
        sourceActors[0].sourceStats["policy"] == "inferred-mob-table-hp-v1" && sourceActors[0].combatAttributes &&
        sourceActors[0].sourceStats["spawn"]["map_provenance"] == map.source,
        "Empty policy under beta World consumes actual MOB/table HP and combat attributes with unchanged spawn provenance");
    auto recovery = map;
    recovery.fields[0].values[3] = -100;
    const auto repaired = prepareSourceMonsterSpawns(world, catalog, recovery, 1, 1, 0,
        "legacy-demo-v1", "legacy-snapshot-damage-v1", DemoBalance{4, 5}, &prepared);
    check(repaired[0].hp == 260 && world.canWalk(repaired[0].x, repaired[0].y) && repaired[0].x == repaired[0].px &&
        prepared.size() == 1 && prepared[0].kind == "position_recovery" && eventsJson(world.events) == beforeEvents,
        "Legacy balance and nearest-walkable recovery prepare their actor and deferred event without publishing");
    auto bossMap = map; bossMap.fields[0].values[9] = "[boss]";
    const auto bosses = prepareSourceMonsterSpawns(world, catalog, bossMap, 1, 1, 0,
        "legacy-demo-v1", "legacy-snapshot-damage-v1", DemoBalance{4, 5});
    check(bosses[0].boss && bosses[0].hp == 1200, "MAP boss role retains the caller-frozen legacy boss policy");
    const auto beforePrepared = eventsJson(prepared);
    auto failure = recovery;
    for (const auto &value : Json::array({std::numeric_limits<int>::max(), 1, 0, 200, 200, 0, 1, 1, "[fixed]", "[normal]"}))
        failure.fields[0].values.push_back(value);
    rejects([&] { prepareSourceMonsterSpawns(world, catalog, failure, 1, 1, 0,
        "legacy-demo-v1", "legacy-snapshot-damage-v1", DemoBalance{}, &prepared); },
        "A later unregistered MOB rejects the complete prepared batch");
    check(eventsJson(prepared) == beforePrepared && actorsJson(world) == beforeActors &&
        eventsJson(world.events) == beforeEvents && world.simulationCheckpoint() == beforeSimulation,
        "Failed batch preserves caller events and all published World/identity/random state");
    rejects([&] { prepareSourceMonsterSpawns(world, catalog, map, 1, 1, 0, "legacy-demo-v1",
        "legacy-snapshot-damage-v1", DemoBalance{}, &world.events); },
        "Preparation rejects direct World.events publication");
    auto repeatedMap = map; repeatedMap.fields.push_back(map.fields[0]);
    rejects([&] { prepareSourceMonsterSpawns(world, catalog, repeatedMap, 1, 1, 0, "legacy-demo-v1",
        "legacy-snapshot-damage-v1", DemoBalance{}); }, "Repeated MAP monster fields cannot silently lose spawns");
    rejects([&] { prepareSourceMonsterSpawns(world, catalog, map, 1, 1, std::numeric_limits<double>::infinity(),
        "legacy-demo-v1", "legacy-snapshot-damage-v1", DemoBalance{}); }, "Nonfinite background origin rejects before actor preparation");
    return {{"status", "pass"}, {"checks", checks}, {"source_examples", Json::array({dash.json(), waiting.json(), old.json()})},
        {"scope", "source routes and normal MAP preparation; ACT execution, AI, complete MOB/region capability and original-client parity remain separate"}};
}
} // namespace dnf
