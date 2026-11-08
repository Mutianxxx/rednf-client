#include "dnf/monster_spawn.hpp"
#include "dnf/monster_attributes.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
std::vector<Actor> prepareSourceMonsterSpawns(World &world, const RegionCatalog &catalog,
    const Script &map, int sourceDungeon, int basisLevel, double backgroundOrigin,
    const std::string &hpPolicy, const std::string &combatPolicy, const DemoBalance &balance,
    std::vector<Event> *preparedEvents, const WalkGeometryView *geometry, const MonsterLevelPolicy &levelPolicy) {
    if (preparedEvents == &world.events)
        throw std::invalid_argument("Monster preparation cannot publish directly to World.events");
    if (!std::isfinite(backgroundOrigin)) throw std::invalid_argument("Nonfinite MAP background origin");
    const Field *monsterField = nullptr;
    for (const auto &field : map.fields) if (normalize(field.tag) == "[monster]") {
        if (monsterField) throw std::runtime_error("Repeated MAP monster fields require an explicit source policy");
        monsterField = &field;
    }
    const auto spawns = monsterField ? parseMonsterSpawns(monsterField->values) : std::vector<MonsterSpawn>();
    if (spawns.size() > size_t(std::numeric_limits<int>::max())) throw std::overflow_error("MAP actor ID overflow");
    std::vector<Actor> actors;
    std::vector<Event> events;
    const auto canWalk=[&](double x,double y){return geometry?geometry->canWalk(x,y):world.canWalk(x,y);};
    const auto nearestWalkable=[&](double x,double y){return geometry?geometry->nearestWalkable(x,y):world.nearestWalkable(x,y);};
    actors.reserve(spawns.size());
    const auto selectedHpPolicy = hpPolicy.empty() ?
        (world.usesSourceGrowth() ? MonsterHpPolicy::inferredMobTableHpV1().id : "legacy-demo-v1") : hpPolicy;
    for (size_t i = 0; i < spawns.size(); ++i) {
        const auto &spawn = spawns[i];
        if (!std::isfinite(spawn.x) || !std::isfinite(spawn.y) || !std::isfinite(spawn.z) ||
            !std::isfinite(spawn.y + backgroundOrigin)) throw std::invalid_argument("Nonfinite MAP monster position");
        Actor actor;
        actor.id = int(i) + 1;
        actor.sourceId = spawn.id;
        actor.x = actor.px = spawn.x;
        actor.y = actor.py = spawn.y + backgroundOrigin;
        actor.z = actor.pz = spawn.z;
        actor.boss = spawn.type == "[boss]";
        if (selectedHpPolicy == "legacy-demo-v1") actor.hp = actor.maxHp = balance.monsterHp(actor.boss);
        actor.monsterPath = catalog.monsterPath(spawn.id);
        if (actor.monsterPath.empty()) throw std::runtime_error("MAP monster id has no unambiguous MOB registration: " + std::to_string(spawn.id));
        Json sourceLevel=nullptr,sourceLevelError=nullptr;
        try { sourceLevel=resolveMonsterLevel(spawn,basisLevel); }
        catch(const std::exception &error) {
            if(!levelPolicy.adapted())throw;
            sourceLevelError=error.what();
        }
        const int effectiveLevel=levelPolicy.adapted()?levelPolicy.frozenLevel():sourceLevel.get<int>();
        world.initializeMonsterAttributes(actor,effectiveLevel,selectedHpPolicy,combatPolicy);
        actor.sourceStats["spawn"] = {{"map", map.path}, {"map_provenance", map.source},
            {"ordinal", i}, {"dungeon", sourceDungeon}, {"basis_level", basisLevel}, {"raw", spawn.raw},
            {"source_resolved_level",sourceLevel},{"source_level_error",sourceLevelError},
            {"effective_level",effectiveLevel},{"level_policy",levelPolicy.json()}};
        actor.animStart = world.nowMs();
        if (!canWalk(actor.x, actor.y)) {
            const auto position = nearestWalkable(actor.x, actor.y);
            const auto distance = std::hypot(position[0] - actor.x, position[1] - actor.y);
            if (!std::isfinite(distance) || distance > std::numeric_limits<int>::max() ||
                !canWalk(position[0], position[1]))
                throw std::runtime_error("MAP monster has no representable walkable recovery position");
            events.push_back({world.tick, "position_recovery", "nearest source walk cell", actor.id, 0, int(std::lround(distance))});
            actor.x = actor.px = position[0];
            actor.y = actor.py = position[1];
        }
        actors.push_back(std::move(actor));
    }
    if (preparedEvents) {
        auto merged = *preparedEvents;
        merged.insert(merged.end(), events.begin(), events.end());
        preparedEvents->swap(merged);
    }
    return actors;
}
} // namespace dnf
