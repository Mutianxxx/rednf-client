#pragma once
#include "combat.hpp"
#include "region.hpp"
#include "demo_settings.hpp"
#include "monster_level_policy.hpp"
#include "dungeon_difficulty.hpp"
namespace dnf {
// Application session is separate from immutable MAP/DGN and character progression.
class RegionSession {
    // Raw snapshot metadata retains unknown root/run/room fields on a normal
    // load/save round trip. Known runtime state is overlaid when serializing.
    Json preserved_ = Json::object();
  public:
    DungeonRun run;
    std::vector<Json> roomStates;
    Json objects = Json::object(), drops = Json::object();
    DemoBalance balance;
    MonsterLevelPolicy monsterLevelPolicy;
    // Frozen for the whole run, including rooms not visited before a reload.
    // Missing legacy snapshot fields select the historical demo policy.
    std::string monsterStatPolicy = "legacy-demo-v1";
    std::string monsterCombatPolicy = "legacy-snapshot-damage-v1";
    // Frozen selection survives room changes and reload; absent old field stays exact easy.
    int dungeonDifficulty = 0;
    std::string difficultyPolicy = "legacy-exact-easy-v1";
    std::string monsterAiDifficulty() const {
        if(difficultyPolicy=="legacy-exact-easy-v1")return "easy";
        if(difficultyPolicy!=dungeonDifficultyPolicy)throw std::runtime_error("Unavailable dungeon difficulty policy");
        return dungeonDifficultyRequest(dungeonDifficulty);
    }
    bool active() const { return !run.rooms.empty(); }
    void begin(const RegionCatalog &, int dungeon, uint64_t seed, DemoBalance balance = {},
               std::string monsterPolicy = "legacy-demo-v1",
               std::string combatPolicy = "legacy-snapshot-damage-v1",
               MonsterLevelPolicy levelPolicy = {}, int difficulty = 0);
    void remember(const World &);
    bool restore(World &) const;
    Json save(const World &, const std::string &location) const;
    bool load(const Json &, const RegionCatalog &);
    void clear();
};
Json saveActor(const Actor &, int64_t now);
// Resource-free decode rebases saved ages to now. A dead monster's serialized
// motion is only an identity descriptor until World::restoreMonsterVisuals is
// called; RegionSession::restore performs that second step before publishing it.
Actor loadActor(const Json &, int64_t now);
// Decode/validate privately, then restore the session-owned player fields.
// Current World identity, source limits and entity handle remain authority.
// Transient living actions are cancelled; death phase ages are rebased intact.
// Invalid snapshots throw before changing the live actor or controller.
void restoreSessionPlayer(World &, const Json &);
} // namespace dnf
