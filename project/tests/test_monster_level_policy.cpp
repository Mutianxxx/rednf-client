#include "dnf/monster_spawn.hpp"
#include "dnf/monster_attributes.hpp"
#include "dnf/session.hpp"
#include "dnf/scene.hpp"
#include <stdexcept>

namespace dnf {
Json runMonsterLevelPolicyTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::array();
    const auto check=[&](bool okay,const char *name){if(!okay)throw std::runtime_error(name);checks.push_back(name);};
    const auto rejects=[](auto action){try{action();}catch(const std::exception&){return true;}return false;};
    check(!MonsterLevelPolicy::fromJson(Json()).adapted(),"Absent legacy level policy preserves source MAP level");
    for(const int level:{1,23,99}) {
        auto policy=MonsterLevelPolicy::playerLevel(level);auto saved=policy.json();saved["future_policy_metadata"]="keep";
        const auto restored=MonsterLevelPolicy::fromJson(saved);
        check(restored.adapted() && restored.frozenLevel()==level && restored.json()==saved,
            "Frozen player level and unknown metadata survive exact JSON roundtrip");
    }
    for(const auto &invalid:std::vector<Json>{Json::array(),{{"id","unknown"}},
        {{"id","user-player-level-v1"},{"frozen_player_level",0}},
        {{"id","user-player-level-v1"},{"frozen_player_level",100}},
        {{"id","user-player-level-v1"},{"frozen_player_level",1.5}},
        {{"id","source-map-v1"},{"frozen_player_level",3}}})
        check(rejects([&]{MonsterLevelPolicy::fromJson(invalid);}),"Malformed policy rejects instead of silently choosing a different monster level");
    RegionCatalog regions(pvf,assets,RegionPreparation::OnDemand);regions.prepareDungeon(1);
    Scene scene;scene.load(pvf,assets,"map/lorien/s0.map","level-test","0");
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    const WalkGeometryView geometry{scene.width,scene.walkRects,scene.blockedRects};
    const auto before=world.snapshot(),rng=world.randomStreams().snapshot(),ids=world.idSources().snapshot();
    const auto original=scene.script.rawBytes;
    const auto source=prepareSourceMonsterSpawns(world,regions,scene.script,1,1,scene.bg,
        MonsterHpPolicy::inferredMobTableHpV1().id,MonsterCombatAttributePolicy::inferredMobCombatTableV1().id,
        {},nullptr,&geometry);
    for(const int level:{1,10,25,50}) {
        RegionSession session;session.begin(regions,1,7200+level,{},MonsterHpPolicy::inferredMobTableHpV1().id,
            MonsterCombatAttributePolicy::inferredMobCombatTableV1().id,MonsterLevelPolicy::playerLevel(level));
        world.characterLevel=99; // Runtime debug/level changes do not edit a frozen run.
        const auto actors=prepareSourceMonsterSpawns(world,regions,scene.script,1,1,scene.bg,
            session.monsterStatPolicy,session.monsterCombatPolicy,session.balance,nullptr,&geometry,session.monsterLevelPolicy);
        check(actors.size()==source.size(),"Player level adaptation preserves every authored source spawn");
        for(size_t i=0;i<actors.size();++i) {
            const auto &actor=actors[i];const auto &spawn=actor.sourceStats.at("spawn");
            check(actor.sourceId==source[i].sourceId && actor.monsterPath==source[i].monsterPath &&
                spawn.at("raw")==source[i].sourceStats.at("spawn").at("raw") && spawn.at("basis_level")==1 &&
                spawn.at("source_resolved_level")==source[i].sourceStats.at("level") && spawn.at("effective_level")==level,
                "Adaptation retains source identity, raw placement, basis and original resolved level");
            const auto expected=evaluateMonsterHp(readMonsterAttributeSource(pvf,actor.monsterPath,actor.boss),level,actor.boss,MonsterHpPolicy::inferredMobTableHpV1());
            check(expected.usable() && actor.maxHp==*expected.hp && actor.hp==actor.maxHp &&
                actor.sourceStats.at("level")==level && actor.combatAttributes && actor.combatAttributes->level==level,
                "Effective level drives actual source HP and combat growth, not only UI labels");
        }
        auto snapshot=session.save(world,"dungeon");snapshot["monster_level_policy"]["future"]="preserved";
        RegionSession restored;check(restored.load(snapshot,regions) && restored.monsterLevelPolicy.frozenLevel()==level,
            "Dungeon checkpoint restores the same frozen level for all later rooms");
        const auto again=restored.save(world,"dungeon");
        check(again.at("monster_level_policy")==snapshot.at("monster_level_policy"),"Level policy including unknown fields is saved with the run generation");
        snapshot.erase("monster_level_policy");RegionSession legacy;legacy.load(snapshot,regions);
        check(!legacy.monsterLevelPolicy.adapted(),"Existing source-level sessions migrate explicitly without silently adopting current player level");
        const auto frozen=restored.save(world,"dungeon");snapshot["monster_level_policy"]={{"id","user-player-level-v1"},{"frozen_player_level",1.5}};
        check(rejects([&]{restored.load(snapshot,regions);}) && restored.save(world,"dungeon")==frozen,
            "Bad frozen-level restore leaves the complete previous run intact");
        restored.clear();check(!restored.monsterLevelPolicy.adapted() && !restored.save(world,"town").contains("monster_level_policy"),
            "Leaving the run clears its level override from the town session");
        samples.push_back({{"level",level},{"actors",actors.size()},{"first_stats",actors.front().sourceStats}});
    }
    world.characterLevel=1;
    check(world.snapshot()==before && world.randomStreams().snapshot()==rng && world.idSources().snapshot()==ids && scene.script.rawBytes==original,
        "All level preparations preserve live actors, RNG, entity IDs and original MAP bytes");
    // The reported fatal dungeon must prepare at the selected player level;
    // unsupported original high-level columns are not zeroed or discarded.
    regions.prepareDungeon(1500);const auto &dungeon=regions.dungeons.at(1500);
    RegionSession run;run.begin(regions,1500,8033,{},MonsterHpPolicy::inferredMobTableHpV1().id,
        MonsterCombatAttributePolicy::inferredMobCombatTableV1().id,MonsterLevelPolicy::playerLevel(1));
    Scene vilmark;vilmark.load(pvf,assets,run.run.room().path,run.run.token,"0");
    const WalkGeometryView vilmarkGeometry{vilmark.width,vilmark.walkRects,vilmark.blockedRects};
    const auto fixed=prepareSourceMonsterSpawns(world,regions,vilmark.script,1500,dungeon.basisLevel,vilmark.bg,
        run.monsterStatPolicy,run.monsterCombatPolicy,run.balance,nullptr,&vilmarkGeometry,run.monsterLevelPolicy);
    check(!fixed.empty() && std::all_of(fixed.begin(),fixed.end(),[](const Actor &a){return a.sourceStats.at("level")==1;}),
        "Reported Vilmark entry uses actual source monsters at frozen player level without the original high-level crash");
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","User-requested effective monster level through actual source factory/session; all dungeon mechanics not certified"}};
}
} // namespace dnf
