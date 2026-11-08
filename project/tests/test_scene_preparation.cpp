#include "dnf/monster_spawn.hpp"
#include "dnf/scene.hpp"
#include <stdexcept>
namespace dnf {
Json runScenePreparationTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool ok,const char *name){if(!ok)throw std::runtime_error(name);checks.push_back(name);};
    RegionCatalog catalog(pvf,assets,RegionPreparation::OnDemand);
    const auto prepared=catalog.prepareDungeon(1);
    check(prepared.at("status")=="prepared","Initial dungeon dependency pool prepares from an empty scene cache");
    Scene scene;scene.load(pvf,assets,"map/lorien/s0.map","prepare-test","0");
    const WalkGeometryView next{scene.width,scene.walkRects,scene.blockedRects};
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    world.mapWidth=120;world.walkRects={{12,10000,96,50}};world.blockedRects={{30,10010,20,20}};
    world.setMapExplorationPolicy(false);
    const auto before=world.snapshot();const auto random=world.randomStreams().snapshot();
    const auto ids=world.idSources().snapshot();
    std::vector<Event> events;
    const auto actors=prepareSourceMonsterSpawns(world,catalog,scene.script,1,catalog.dungeons.at(1).basisLevel,
        scene.bg,MonsterHpPolicy::inferredMobTableHpV1().id,MonsterCombatAttributePolicy::inferredMobCombatTableV1().id,
        DemoBalance{},&events,&next);
    check(actors.size()==3,"Next scene prepares all three actual source monsters");
    for(const auto &actor:actors) {
        check(next.canWalk(actor.x,actor.y),"Prepared actor uses next-room ground and obstacles");
        check(!world.canWalk(actor.x,actor.y),"Closed live exploration geometry is never borrowed for the next-room spawn");
        check(!actor.handle,"Private spawn preparation allocates no live entity handle");
    }
    check(world.snapshot()==before&&world.randomStreams().snapshot()==random&&world.idSources().snapshot()==ids,
          "Successful preparation preserves live world, geometry, RNG, events and ids");
    auto malformed=scene.script;
    for(const auto &field:scene.script.fields)if(normalize(field.tag)=="[monster]"){malformed.fields.push_back(field);break;}
    bool rejected=false;const auto eventCount=events.size();
    try {prepareSourceMonsterSpawns(world,catalog,malformed,1,1,scene.bg,
        MonsterHpPolicy::inferredMobTableHpV1().id,MonsterCombatAttributePolicy::inferredMobCombatTableV1().id,
        DemoBalance{},&events,&next);}catch(const std::exception&){rejected=true;}
    check(rejected&&events.size()==eventCount,"Malformed next-room source rejects without appending recovery events");
    check(world.snapshot()==before&&world.randomStreams().snapshot()==random&&world.idSources().snapshot()==ids,
          "Failed preparation preserves live scene state and random streams");
    return {{"status","passed"},{"checks",checks},{"count",checks.size()}};
}
}
