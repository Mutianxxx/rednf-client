#pragma once
#include "dnf/map_access.hpp"
#include "dnf/scene.hpp"
#include "dnf/combat.hpp"
#include "dnf/region.hpp"
#include "dnf/monster_level_policy.hpp"

namespace dnf {
// Source-preserving test exploration is not normal gameplay admission. Failed
// individual dependencies are retained in records/diagnostics, never counted
// as completed mechanics. The caller publishes only after successful prepare.
struct PreparedMapExploration {
    bool ok = false, testMode = false, complete = false, geometryAvailable = false, townTraversal = false;
    Scene scene;
    std::vector<Actor> monsters;
    std::array<double, 2> playerSpawn{0, 0};
    Json diagnostics = Json::array(), records = Json::array(), source = Json::object();
    std::vector<Event> preparedEvents;
    Json json() const;
};
PreparedMapExploration prepareMapExploration(Pvf &, Assets &, World &, const RegionCatalog &,
    const MapAccessEntry &, bool testMode, const MonsterLevelPolicy &levelPolicy = {});
// Town traversal prepares source scenery/geometry/NPCs/exits without monster or reward admission.
PreparedMapExploration prepareTownMapTraversal(Pvf &, Assets &, World &, const RegionCatalog &,
    const MapAccessEntry &);
Json runMapExplorationTests(Pvf &, Assets &);
} // namespace dnf
