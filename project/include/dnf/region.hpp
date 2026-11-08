#pragma once
#include "resources.hpp"
#include "simulation.hpp"
#include <array>
#include <map>
#include <optional>
#include <random>
#include <set>
namespace dnf {
// Ordered alternatives from every MAP [greed] value, including repeated tags.
// Legacy v1 allowed/required masks keep their original first-value contract.
std::vector<int> sourceMapDoorMasks(const Script &);
enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };
Direction opposite(Direction direction);
int directionBit(Direction direction);
struct MonsterSpawn {
    int id = 0, level = 0, randomDrops = 0, specifiedDrops = 0, npcOnDeath = -1;
    bool autoLevel = true;
    double x = 0, y = 0, z = 0;
    std::string copyType, type;
    Json traits = Json::array(), raw = Json::array();
};
// Explicitly rejects truncated/unknown records. Champion extensions and NPC-on-death are variable length.
std::vector<MonsterSpawn> parseMonsterSpawns(const Json &values);
struct MapDefinition {
    int id = 0, dungeon = 0, allowedDoors = 0, requiredDoors = 0;
    bool boss = false, start = false, special = false;
    std::string path;
    Script source;
    // Ordered MAP [greed] alternatives for v2. The legacy first/second
    // fields above remain solely for v1 generation and saved layouts.
    std::vector<int> acceptedDoorMasks;
    std::vector<MonsterSpawn> monsters;
};
struct MazeDefinition {
    int width = 0, height = 0;
    std::vector<int> doorMasks;
    std::vector<std::array<int, 2>> starts, bosses;
    std::map<int, std::vector<int>> specifiedMaps, specifiedBossMaps;
    Json sourceFields = Json::array();
};
struct DungeonDefinition {
    int id = 0, minimumLevel = 1, basisLevel = 1, worldQuest = -1;
    bool enabled = false;
    std::string path, name, slotImage, lockedReason;
    int slotFrame = 0, worldX = 0, worldY = 0, worldPattern = 0;
    std::vector<int> mapIds, pathgateObjects;
    std::vector<MazeDefinition> mazes;
    Script source;
};
struct TownArea {
    int id = 0, worldmap = -1;
    std::string path, kind, resolvedPath;
    double spawnX = 0, spawnY = 0;
    Json raw;
};
struct NpcDefinition {
    int id = 0, shop = -1;
    bool clearOnly = false;
    std::string path, name, serviceName, unavailableReason;
    Script source;
};
struct ShopDefinition {
    int id = 0, npc = 0;
    bool enabled = true;
    std::string path, lockedReason;
    std::vector<int> items;
    Script source;
};
enum class RegionPreparation { InitialRegion, OnDemand };
class RegionCatalog {
    Pvf &pvf_;
    std::map<int, std::string> itemPaths_;
    std::map<int, std::string> monsterPaths_;
    mutable std::map<int, Script> itemScripts_;
  public:
    std::map<int, DungeonDefinition> dungeons;
    std::map<int, MapDefinition> maps;
    std::map<int, Script> monsters;
    std::map<int, NpcDefinition> npcs;
    std::map<int, ShopDefinition> shops;
    std::map<int, Script> quests;
    std::vector<TownArea> townAreas;
    Script town, worldmap;
    Script experienceTable;
    std::vector<int64_t> experienceThresholds;
    Json issues = Json::array();
    explicit RegionCatalog(Pvf &pvf, Assets &assets,
                           RegionPreparation preparation = RegionPreparation::InitialRegion);
    void prepareWorldDungeonIndex();
    Json prepareWorldmap(const std::string &path);
    Json prepareDungeonMetadata(int dungeonId);
    Json prepareDungeon(int dungeonId);
    const Script *item(int id) const;
    const TownArea *townArea(int id) const;
    std::string monsterPath(int id) const;
  private:
    bool worldDungeonIndexReady_ = false;
    bool worldMapMembershipReady_ = false;
    std::map<int,std::string> worldRegisteredMaps_;
    std::map<int,std::vector<std::pair<int,std::string>>> worldMapPaths_;
    std::set<int> preparedDungeonMetadata_;
    std::set<int> preparedWorldDungeons_;
    void prepareMapMembershipIndex();
};
// The generator and restore validator share the exact source-filtered ordered
// candidate closure. This function performs no random draw.
std::vector<int> dungeonRoomCandidates(const RegionCatalog &, int dungeon,
    const MazeDefinition &, int cell, int doors, bool boss,
    const std::string &version = "pcg32-world-v1");
struct RunRoom {
    int x = 0, y = 0, mapId = 0, doors = 0;
    bool boss = false, visited = false, cleared = false;
    std::string path;
    // All source candidates for this selected topology, not only the chosen variant.
    std::vector<int> candidates;
};
class DungeonRun {
  public:
    int dungeonId = 0, current = 0, start = 0, boss = 0, width = 0, height = 0;
    uint64_t seed = 0;
    std::vector<RunRoom> rooms;
    std::string token;
    std::string generatorVersion = "pcg32-world-v1";
    Json randomState = Json::object();
    static DungeonRun generate(const RegionCatalog &catalog, int dungeon, uint64_t seed,
                               const std::string &generatorVersion = "pcg32-world-v1");
    RunRoom &room() { return rooms.at(current); }
    const RunRoom &room() const { return rooms.at(current); }
    int destination(Direction direction) const;
    bool move(Direction direction);
    bool complete() const;
    Json describe() const;
};
DungeonRun generateSourceDungeon(const RegionCatalog &,int dungeon,uint64_t seed);
} // namespace dnf
