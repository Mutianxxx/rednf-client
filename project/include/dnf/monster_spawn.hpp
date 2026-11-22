#pragma once
#include "combat.hpp"
#include "demo_settings.hpp"
#include "region.hpp"
#include "walk_geometry.hpp"
#include "monster_level_policy.hpp"

namespace dnf {
// Normal MAP factory shared by main and logic checks. Prepares all actors
// privately: no entity IDs, World.monsters/events, RNG, clock or host mutation.
// World may populate its immutable content cache during source evaluation.
// Optional position-recovery events are appended only after every spawn passes;
// the caller publishes actors/events and attaches source behavior outside loops.
std::vector<Actor> prepareSourceMonsterSpawns(World &world, const RegionCatalog &catalog,
    const Script &map, int sourceDungeon, int basisLevel, double backgroundOrigin,
    const std::string &hpPolicy, const std::string &combatPolicy, const DemoBalance &balance,
    std::vector<Event> *preparedEvents = nullptr, const WalkGeometryView *geometry = nullptr,
    const MonsterLevelPolicy &levelPolicy = {});
} // namespace dnf
