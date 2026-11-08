#include "dnf/skill_data.hpp"
#include "dnf/combat.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <chrono>
#include <limits>
#include <stdexcept>

namespace dnf {
Json runSkillDataTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool passed, const std::string &name) {
        if (!passed) throw std::runtime_error("Skill data: " + name);
        checks.push_back(name);
    };
    CharacterScript source;
    source.script.path = "synthetic/updated-skill.skl";
    source.bytes = {0xb0, 0xd0};
    source.provenance = {{"fixture", "mode selection"}};
    source.script.tokens = {{{"offset", 2}, {"type", 5}, {"value", "[name]"}}};
    source.script.fields = {
        {"[name]", Json::array({"Resource name"}), 2},
        {"[type]", Json::array({"[active]"}), 12},
        {"[growtype maximum level]", Json::array({4, 7, 0}), 22},
        {"[consume MP]", Json::array({1, 9}), 42},
        {"[cool time]", Json::array({100, 900}), 57},
        {"[level info]", Json::array({2, 10, 11, 20, 21}), 72},
        {"[unknown future field]", Json::array({"keep", 3}), 102},
        {"[dungeon]", Json::array(), 117},
        {"[consume MP]", Json::array({3, 8}), 122},
        {"[static data]", Json::array(), 137},
        {"[/dungeon]", Json::array(), 142},
        {"[pvp]", Json::array(), 147},
        {"[consume MP]", Json::array({5, 12}), 152},
        {"[level info]", Json::array({2, 30, 31, 40, 41}), 167},
        {"[/pvp]", Json::array(), 197}
    };
    const auto definition = parseCharacterSkillSource({5, 64}, {}, source);
    const auto dungeon = readSkillSourceData(definition);
    const auto pvp = readSkillSourceData(definition, "pvp");
    check(dungeon.definition.key == SkillKey{5,64} && dungeon.name() == "Resource name" &&
          dungeon.values("[consume MP]") == Json::array({3,8}) &&
          dungeon.selected.at("[consume mp]").scope == "dungeon" &&
          dungeon.selected.at("[consume mp]").field.offset == 122 &&
          dungeon.selected.at("[consume mp]").ordinal == 8,
          "Dungeon overrides retain exact job-local key, both endpoints, scope, ordinal and source offset");
    check(dungeon.values("[cool time]") == Json::array({100,900}) &&
          dungeon.values("[level info]") == Json::array({2,10,11,20,21}) &&
          dungeon.selected.at("[level info]").scope == "common" &&
          pvp.values("[consume MP]") == Json::array({5,12}) &&
          pvp.values("[level info]") == Json::array({2,30,31,40,41}),
          "Absent dungeon override uses common data without leaking later PvP values");
    check(dungeon.values("[static data]").empty() && dungeon.selected.at("[static data]").scope == "dungeon" &&
          !dungeon.firstNumber("[static data]") && dungeon.firstNumber("[consume MP]") == 3 &&
          dungeon.purchaseMaximum(0) == 4 && dungeon.purchaseMaximum(1) == 7 &&
          dungeon.purchaseMaximum(2) == 0 && !dungeon.purchaseMaximum(3),
          "Empty override, absent number and explicit zero purchase ceiling stay distinct");
    check(dungeon.definition.source.bytes == source.bytes && dungeon.definition.source.script.tokens == source.script.tokens &&
          dungeon.definition.source.script.fields[6].tag == "[unknown future field]" &&
          dungeon.snapshot(true).at("source").at("source").at("bytes").get<Bytes>() == source.bytes,
          "All unknown source fields, original tokens, bytes and provenance remain available to ports");
    auto updated = source;
    updated.script.fields[0].values = Json::array({"Updated PVF name"});
    updated.script.fields[8].values = Json::array({17,19});
    const auto changed = readSkillSourceData(parseCharacterSkillSource({5,64}, {}, updated));
    check(changed.name() == "Updated PVF name" && changed.firstNumber("[consume MP]") == 17 &&
          dungeon.name() == "Resource name" && dungeon.firstNumber("[consume MP]") == 3,
          "Updated source changes names and parameters through the same loader without changing controller code");
    auto duplicate = source;
    duplicate.script.fields.insert(duplicate.script.fields.begin() + 9,
        Field{"[consume MP]", Json::array({20,21}), 132});
    const auto duplicateData = readSkillSourceData(parseCharacterSkillSource({5,64}, {}, duplicate));
    check(duplicateData.ambiguousFields.count("[consume mp]") == 1 &&
          !duplicateData.selected.count("[consume mp]") &&
          duplicateData.issues.back().at("candidates").size() == 2,
          "Repeated selected mode fields retain all candidates and reject a winner");
    bool rejected = false;
    try { readSkillSourceData(definition, "arena-guess"); } catch (const std::exception &) { rejected = true; }
    check(rejected, "Unknown mode cannot silently become dungeon or common");
    check(skillLevelValue(Json::array({2,10,11,20,21}),1,0) == 10 &&
          skillLevelValue(Json::array({2,10,11,20,21}),2,1) == 21 &&
          !skillLevelValue(Json::array({2,10,11,20,21}),0,0) &&
          !skillLevelValue(Json::array({2,10,11,20,21}),-1,0) &&
          !skillLevelValue(Json::array({2,10,11,20,21}),3,0) &&
          !skillLevelValue(Json::array({2,10,11,20,21}),1,-1),
          "Exact level/column lookup rejects unlearned, negative and out-of-range levels");
    for (const auto &table : {Json::array(), Json::array({0,7}), Json::array({2,10,11,20}),
             Json::array({-1,5}), Json::array({1,"unknown"}),
             Json::array({uint64_t(std::numeric_limits<uint64_t>::max()),7})})
        check(!skillLevelValue(table,1,0), "Malformed or incomplete level-info table is not executable: " + table.dump());

    CharacterCatalog catalog(pvf);
    Json jobs = Json::array();
    for (int job = 0; job < 10; ++job) {
        size_t activeSources = 0, passiveSources = 0;
        for (const auto &entry : catalog.at(job).skills.entries) {
            const auto &registered = catalog.skillDefinition({job,entry.id});
            if (registered.kind == SkillSourceKind::Unknown) continue;
            const auto data = readSkillSourceData(registered);
            check(data.definition.key == SkillKey{job,entry.id} && data.definition.source.bytes == pvf.read(entry.path),
                "Registered source uses shared loader with exact key and bytes: " + std::to_string(job) + ":" + std::to_string(entry.id));
            if (registered.kind == SkillSourceKind::Active) ++activeSources;
            if (registered.kind == SkillSourceKind::Passive) ++passiveSources;
            if (activeSources && passiveSources) break;
        }
        check(activeSources > 0 && passiveSources > 0,
              "Current registered job has active and passive source data probes: " + std::to_string(job));
        jobs.push_back({{"job_id",job},{"active_probes",activeSources},{"passive_probes",passiveSources}});
    }
    World world(pvf, assets);
    for (const auto *skills : {&world.skills, &world.passives}) for (const auto &skill : *skills) {
        const auto &registered = catalog.skillDefinition(skill.identity());
        const auto data = readSkillSourceData(registered);
        check(skill.sourceData && skill.sourceData->definition.key == skill.identity() &&
              skill.name == data.name() && skill.source == registered.source.script.path &&
              skill.levelInfo == data.values("[level info]") && skill.command == data.values("[command]") &&
              skill.maxLevel == data.purchaseMaximum(world.identity().growtype),
              "Playable source fields are loaded through the shared job-local SKL path: " + skill.key);
    }
    auto firstAttackVolume = [&](World &candidate) {
        candidate.freezeAi = true;
        candidate.combat = true;
        candidate.player.x = candidate.player.px = 500;
        candidate.player.y = candidate.player.py = 260;
        Actor target;
        target.id = 1;
        target.x = target.px = 580;
        target.y = target.py = 260;
        target.hp = target.maxHp = 100000;
        target.monsterPath = "monster/goblin/goblin.mob";
        candidate.monsters.push_back(target);
        candidate.normalAttack();
        int maximum = 0;
        for (int tick = 0; tick < 40; ++tick) {
            candidate.advance(16666667);
            for (const auto &volume : candidate.attackVolumes) maximum = std::max(maximum, volume.damage);
        }
        return maximum;
    };
    World learnedMastery(pvf, assets), unlearnedMastery(pvf, assets);
    learnedMastery.passives.at(1).level = learnedMastery.passives.at(1).maxLevel;
    unlearnedMastery.passives.at(1).level = 0;
    const int learnedDamage = firstAttackVolume(learnedMastery);
    const int unlearnedDamage = firstAttackVolume(unlearnedMastery);
    check(learnedMastery.passives.at(1).parameter(0) > 0 &&
          unlearnedMastery.passives.at(1).parameter(0) == 0 && learnedDamage > unlearnedDamage,
          "Source mastery changes basic-attack volume damage (learned=" + std::to_string(learnedDamage) +
              ", unlearned=" + std::to_string(unlearnedDamage) + ")");
    const auto directory = std::filesystem::path("reports/test-saves/skill-data") /
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    CharacterStore store(directory);
    store.data["characters"][0] = {{"name","Skill source fixture"},{"class","swordman"},
        {"passives",{{world.passives.at(1).key,0},{"future_passive",{{"keep",7}}}}}};
    store.apply(0,world);
    check(world.passives.at(1).level == 0 && world.passives.at(1).parameter(0) == 0,
          "Explicitly unlearned source passive remains inactive on initial load");
    store.capture(0,world); store.save();
    store.close();
    CharacterStore restored(directory);
    restored.apply(0,world);
    check(world.passives.at(1).level == 0 && world.passives.at(1).parameter(0) == 0 &&
          restored.data["characters"][0]["passives"]["future_passive"]["keep"] == 7,
          "Explicit zero passive level survives durable reload and unknown passive fields remain intact");
    return {{"status","pass"},{"checks",checks},{"source_jobs",jobs},
        {"scope","Shared source loading and parameter consumers; no endpoint interpolation, final native formulas or new playable controllers"}};
}
} // namespace dnf
