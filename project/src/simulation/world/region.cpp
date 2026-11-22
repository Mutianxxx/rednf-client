#include "dnf/region.hpp"
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
namespace dnf {
namespace {
std::string relative(const std::string &parent, const std::string &child) {
    return normalize((std::filesystem::u8path(parent).parent_path() / std::filesystem::u8path(child)).generic_u8string());
}
std::map<int, std::string> registry(Pvf &p, const std::string &path) {
    std::map<int, std::string> result;
    const auto tokens = p.script(path).tokens;
    for (size_t i = 0; i + 1 < tokens.size(); ++i)
        if (tokens[i]["value"].is_number_integer() && tokens[i + 1]["value"].is_string()) {
            result[tokens[i]["value"].get<int>()] = relative(path, tokens[i + 1]["value"].get<std::string>());
            ++i;
        }
    return result;
}
std::vector<int> masks(const std::string &s) {
    std::vector<int> values;
    // This client's greed strings use doubled A..P glyphs. Preserve raw strings in Script.
    for (size_t i = 0; i < s.size(); ++i)
        if (s[i] >= 'A' && s[i] <= 'P') {
            values.push_back(s[i] - 'A');
            if (i + 1 < s.size() && s[i + 1] == s[i]) ++i;
        }
    return values;
}
std::vector<std::array<int, 2>> coordinates(const Json &v) {
    std::vector<std::array<int, 2>> result;
    for (size_t i = 0; i + 1 < v.size(); i += 2) result.push_back({v[i].get<int>(), v[i + 1].get<int>()});
    return result;
}
}
std::vector<int> sourceMapDoorMasks(const Script &source) {
    std::vector<int> result;
    for (const auto &field : source.fields) if (normalize(field.tag) == "[greed]")
        for (const auto &value : field.values) if (value.is_string()) {
            const auto alternatives = masks(value.get<std::string>());
            result.insert(result.end(), alternatives.begin(), alternatives.end());
        }
    return result;
}
Direction opposite(Direction d) {
    return d == Direction::Left ? Direction::Right : d == Direction::Right ? Direction::Left :
           d == Direction::Up ? Direction::Down : Direction::Up;
}
int directionBit(Direction d) {
    return d == Direction::Left ? 4 : d == Direction::Right ? 1 : d == Direction::Up ? 2 : 8;
}
std::vector<MonsterSpawn> parseMonsterSpawns(const Json &v) {
    std::vector<MonsterSpawn> result;
    size_t i = 0;
    auto fail = [&]() { throw std::runtime_error("Malformed variable-length MAP monster record at value " + std::to_string(i)); };
    while (i < v.size()) {
        size_t begin = i;
        if (i + 9 >= v.size()) fail();
        for (size_t j = 0; j < 8; ++j) if (!v[i + j].is_number()) fail();
        MonsterSpawn m;
        m.id = v[i++]; m.autoLevel = v[i++].get<int>() != 0; m.level = v[i++];
        m.x = v[i++]; m.y = v[i++]; m.z = v[i++]; m.randomDrops = v[i++]; m.specifiedDrops = v[i++];
        if (!v[i].is_string()) fail();
        m.copyType = v[i++];
        if (i < v.size() && v[i] == "[NPC]") {
            if (i + 2 >= v.size() || !v[i + 1].is_number_integer()) fail();
            m.npcOnDeath = v[i + 1]; i += 2;
        }
        if (i >= v.size() || !v[i].is_string()) fail();
        m.type = v[i++];
        if (m.type == "[champion]" || m.type == "[super champion]") {
            if (i >= v.size() || !v[i].is_number_integer()) fail();
            int count = v[i++];
            if (count < 0 || size_t(count) > v.size() - i) fail();
            for (int k = 0; k < count; ++k) m.traits.push_back(v[i++]);
        } else if (m.type != "[normal]" && m.type != "[boss]") fail();
        for (size_t j = begin; j < i; ++j) m.raw.push_back(v[j]);
        result.push_back(std::move(m));
    }
    return result;
}
RegionCatalog::RegionCatalog(Pvf &p, Assets &,RegionPreparation preparation) : pvf_(p) {
    const auto dungeonPaths = registry(p, "dungeon/dungeon.lst");
    const auto mapPaths = registry(p, "map/map.lst");
    const auto monsterPaths = registry(p, "monster/monster.lst");
    monsterPaths_=monsterPaths;
    const auto npcPaths = registry(p, "npc/npc.lst");
    const auto shopPaths = registry(p, "itemshop/itemshop.lst");
    const auto questPaths = registry(p, "n_quest/quest.lst");
    itemPaths_ = registry(p, "equipment/equipment.lst");
    const auto stackables = registry(p, "stackable/stackable.lst");
    itemPaths_.insert(stackables.begin(), stackables.end());
    town = p.script("town/elvengard.twn");
    worldmap = p.script("worldmap/lorien.wdm");
    experienceTable = p.script("character/exptable.tbl");
    for (const auto &t : experienceTable.tokens) if (t["value"].is_number_integer()) experienceThresholds.push_back(t["value"].get<int64_t>());
    for (const auto &f : town.fields) if (f.tag == "[area]" && f.values.size() >= 2) {
        TownArea a; a.id = f.values[0]; a.path = relative("map/map.lst", f.values[1]); a.raw = f.values;
        a.resolvedPath = a.path;
        if (!p.has(a.path) && a.path == "map/elvengard/gate.map" && p.has("map/elvengard/(r)gate.map")) {
            a.resolvedPath = "map/elvengard/(r)gate.map";
            issues.push_back({{"kind", "missing TWN map resolved by explicit client alias"},
                {"town", town.path}, {"area", a.id}, {"source_path", a.path}, {"resolved_path", a.resolvedPath}});
        }
        for (size_t i = 2; i < f.values.size(); ++i) {
            if (f.values[i] == "[normal]") a.kind = "normal";
            if (f.values[i] == "[gate]") {
                a.kind = "gate";
                if (i + 2 < f.values.size()) { a.spawnX = f.values[i + 1]; a.spawnY = f.values[i + 2]; }
            }
            if (f.values[i] == "[dungeon gate]") { a.kind = "dungeon gate"; if (i + 1 < f.values.size()) a.worldmap = f.values[i + 1]; }
        }
        townAreas.push_back(a);
    }
    const auto entries = worldmap.values("[dungeon]");
    for (size_t i = 0; i + 1 < entries.size(); i += 2) {
        DungeonDefinition d; d.id = entries[i]; d.worldQuest = entries[i + 1];
        d.path = dungeonPaths.at(d.id); d.source = p.script(d.path); d.name = d.source.text("[name]");
        d.minimumLevel = int(d.source.number("[minimum required level]", 1));
        d.basisLevel = int(d.source.number("[basis level]", d.minimumLevel));
        d.enabled = d.id == 1 || d.id == 2;
        if (!d.enabled) d.lockedReason = "本版本未开放；原等级/关联任务/入场材料保留在来源中";
        auto slot = d.source.values("[worldmap pattern info]");
        if (slot.size() >= 4) { d.slotImage = normalize(slot[2]); d.slotFrame = slot[3]; }
        for (const auto &v : d.source.values("[pathgate object]")) d.pathgateObjects.push_back(v.get<int>());
        MazeDefinition *maze = nullptr;
        for (const auto &f : d.source.fields) {
            if (f.tag == "[maze info]") { d.mazes.emplace_back(); maze = &d.mazes.back(); }
            if (!maze) continue;
            maze->sourceFields.push_back({{"tag", f.tag}, {"values", f.values}, {"offset", f.offset}});
            if (f.tag == "[size]" && f.values.size() >= 2) { maze->width = f.values[0]; maze->height = f.values[1]; }
            if (f.tag == "[greed]" && !f.values.empty()) maze->doorMasks = masks(f.values[0]);
            if (f.tag == "[start map]") maze->starts = coordinates(f.values);
            if (f.tag == "[boss map]") maze->bosses = coordinates(f.values);
            if ((f.tag == "[map specification]" || f.tag == "[boss map specification]") && f.values.size() >= 3) {
                int index = f.values[1].get<int>() * maze->width + f.values[0].get<int>();
                auto &target = f.tag == "[map specification]" ? maze->specifiedMaps[index] : maze->specifiedBossMaps[index];
                for (size_t k = 2; k < f.values.size(); ++k) target.push_back(f.values[k].get<int>());
            }
        }
        dungeons[d.id] = std::move(d);
    }
    auto ui = p.script("worldmap/ui/lorien.ui");
    for (const auto &f : ui.fields) if (f.tag == "[ui controls]" && f.values.size() >= 10 && f.values[0] == "[balloon]") {
        int id = f.values.back();
        auto d = dungeons.find(id);
        if (d != dungeons.end()) { d->second.worldX = f.values[2]; d->second.worldY = f.values[3]; d->second.worldPattern = f.values[8]; }
    }
    if(preparation==RegionPreparation::InitialRegion) {
    std::set<int> usedMonsters;
    for (const auto &[id, path] : mapPaths) {
        if (path.rfind("map/lorien/", 0) != 0 && path.rfind("map/lorieninside/", 0) != 0) continue;
        MapDefinition m; m.id = id; m.path = path; m.source = p.script(path);
        auto dg = m.source.values("[dungeon]");
        if (dg.empty() || !dg.front().is_number_integer()) continue;
        m.dungeon = dg.front();
        if (m.dungeon != 1 && m.dungeon != 2) continue;
        m.boss = m.source.text("[type]") == "[boss]";
        const auto stem = std::filesystem::u8path(path).stem().u8string();
        m.start = !stem.empty() && stem[0] == 's';
        auto g = masks(m.source.text("[greed]")); m.acceptedDoorMasks = sourceMapDoorMasks(m.source); m.special = g.empty();
        if (!g.empty()) { m.allowedDoors = g[0]; m.requiredDoors = g.size() > 1 ? g[1] : g[0]; }
        m.monsters = parseMonsterSpawns(m.source.values("[monster]"));
        for (const auto &spawn : m.monsters) usedMonsters.insert(spawn.id);
        dungeons.at(m.dungeon).mapIds.push_back(id);
        maps[id] = std::move(m);
    }
    usedMonsters.insert(10); // Referenced by the regional destructible boxes.
    for (int id : usedMonsters) if (monsterPaths.count(id)) monsters[id] = p.script(monsterPaths.at(id));
    }
    std::vector<int> businessNpcs{1, 2, 8, 22, 32, 74, 205, 1000};
    // The user's direct advancement policy is hosted by the actual registered
    // GSD. Resolve it from this PVF rather than assuming a numeric NPC ID.
    for(const auto &[id,path]:npcPaths)if(normalize(path)=="npc/gsd.npc"&&
        std::find(businessNpcs.begin(),businessNpcs.end(),id)==businessNpcs.end())businessNpcs.push_back(id);
    for (int id : businessNpcs) if (npcPaths.count(id)) {
        NpcDefinition n; n.id = id; n.path = npcPaths.at(id); n.source = p.script(n.path);
        n.name = n.source.text("[name]"); n.clearOnly = n.source.number("[visible on dungeon clear]", 0) != 0;
        auto roles = n.source.values("[role]");
        for (size_t k = 0; k + 1 < roles.size(); ++k) if (roles[k] == "[item shop]") n.shop = roles[k + 1];
        if (std::find(roles.begin(), roles.end(), Json("[item storage]")) != roles.end()) {
            n.name = "金库"; n.serviceName = "金库"; n.unavailableReason = "金库保管功能在本测试版尚未开放。";
        } else if (std::find(roles.begin(), roles.end(), Json("[post box]")) != roles.end()) {
            n.serviceName = "邮件"; n.unavailableReason = "本地离线测试版尚未开放邮件收发。";
        } else if (id == 205 || id == 74) {
            n.serviceName = "活动商店"; n.unavailableReason = "此 NPC 的活动系统在本测试版尚未开放。";
        } else if (id == 8) {
            n.serviceName = "袖珍罐商店"; n.unavailableReason = "袖珍罐开启和随机奖励尚未接入，当前不出售袖珍罐。";
        }
        if (n.shop >= 0 && shopPaths.count(n.shop)) {
            ShopDefinition shop; shop.id = n.shop; shop.npc = id; shop.path = shopPaths.at(n.shop); shop.source = p.script(shop.path);
            shop.enabled = n.unavailableReason.empty(); shop.lockedReason = n.unavailableReason;
            for (const auto &v : shop.source.values("[sell item]")) if (v.is_number_integer() && v.get<int>() >= 0) shop.items.push_back(v.get<int>());
            shops[shop.id] = std::move(shop);
        }
        npcs[id] = std::move(n);
    }
    for (int id : {101, 102, 103, 4301, 1016, 104, 428, 4340}) if (questPaths.count(id)) quests[id] = p.script(questPaths.at(id));
    issues.push_back({{"kind", "reconstructed maze selection policy"}, {"detail", "connected source DGN reciprocal edges; v2 matches ordered MAP greed alternatives; legacy first/second allowed/required behavior retained only for v1 and historical snapshots"}});
    issues.push_back({{"kind", "special quest room retained"}, {"path", "map/lorien/5.map"}, {"detail", "no greed; excluded from ordinary random pool; original quest NPC/object source remains available"}});
}
const TownArea *RegionCatalog::townArea(int id) const {
    for (const auto &area : townAreas) if (area.id == id) return &area;
    return nullptr;
}
const Script *RegionCatalog::item(int id) const {
    auto path = itemPaths_.find(id); if (path == itemPaths_.end()) return nullptr;
    auto it = itemScripts_.find(id);
    if (it == itemScripts_.end()) it = itemScripts_.emplace(id, pvf_.script(path->second)).first;
    return &it->second;
}
std::string RegionCatalog::monsterPath(int id) const {
    const auto it=monsterPaths_.find(id);return it==monsterPaths_.end()?"":it->second;
}
std::vector<int> dungeonRoomCandidates(const RegionCatalog &catalog, int dungeon, const MazeDefinition &maze,
                                     int cell, int doors, bool isBoss, const std::string &version) {
    std::vector<int> result;
    const bool sourceTopology=version=="pcg32-source-topology-v2";
    const auto &specified = isBoss && maze.specifiedBossMaps.count(cell) ? maze.specifiedBossMaps : maze.specifiedMaps;
    const auto explicitList=specified.find(cell);
    bool explicitRoleAvailable=false;
    if(sourceTopology&&explicitList!=specified.end())for(int mapId:explicitList->second){const auto found=catalog.maps.find(mapId);if(found!=catalog.maps.end()&&found->second.boss==isBoss)explicitRoleAvailable=true;}
    for (int mapId : catalog.dungeons.at(dungeon).mapIds) {
        const auto &m = catalog.maps.at(mapId);
        auto spec = specified.find(cell);
        const bool explicitMap=spec!=specified.end()&&std::find(spec->second.begin(),spec->second.end(),mapId)!=spec->second.end();
        if(spec!=specified.end()&&!explicitMap)continue;
        // Only an explicit source DGN cell may give a no-greed special MAP its
        // topology. If an explicit list has no MAP with the selected DGN role,
        // v2 treats the DGN cell role as authority (inferred source conflict
        // adapter); matching-role lists retain the documented role filter.
        const bool explicitRole=sourceTopology&&explicitMap&&!explicitRoleAvailable;
        if(m.special&&!(sourceTopology&&explicitMap))continue;
        if(m.boss!=isBoss&&!explicitRole)continue;
        if(!m.special&&!(sourceTopology&&maze.width==1&&maze.height==1&&doors==0)) {
            // MAP greed lists accepted grid alternatives. It is not an
            // allowed/required pair (e.g. source Trombe JJ LL).
            if(sourceTopology) {
                if(std::find(m.acceptedDoorMasks.begin(),m.acceptedDoorMasks.end(),doors)==m.acceptedDoorMasks.end())continue;
            } else if((doors&~m.allowedDoors)||(doors&m.requiredDoors)!=m.requiredDoors)continue;
        }
        result.push_back(mapId);
    }
    return result;
}
DungeonRun DungeonRun::generate(const RegionCatalog &catalog, int id, uint64_t seed_, const std::string &generatorVersion) {
    if(generatorVersion=="pcg32-source-topology-v2")return generateSourceDungeon(catalog,id,seed_);
    const auto &d = catalog.dungeons.at(id);
    if (!d.enabled) throw std::runtime_error("Dungeon disabled by this version's scope");
    if(generatorVersion!="pcg32-world-v1"&&generatorVersion!="legacy-mt19937_64-v1")
        throw std::runtime_error("Unsupported dungeon generator: "+generatorVersion);
    std::mt19937_64 legacyRandom(seed_);
    RandomStreams streams(seed_);
    auto &worldRandom=streams.stream(RandomDomain::WorldGeneration);
    auto pick=[&](uint64_t bound){return generatorVersion=="legacy-mt19937_64-v1"?legacyRandom()%bound:worldRandom.bounded64(bound);};
    struct Choice { size_t maze; int start, boss; uint64_t edges; };
    std::vector<Choice> choices;
    auto candidates = [&](const MazeDefinition &maze, int cell, int doors, bool isBoss) {
        return dungeonRoomCandidates(catalog, id, maze, cell, doors, isBoss);
    };
    auto edgeList = [](const MazeDefinition &maze) {
        std::vector<std::array<int, 4>> edges;
        for (int y = 0; y < maze.height; ++y) for (int x = 0; x < maze.width; ++x) {
            int cell = y * maze.width + x;
            if (x + 1 < maze.width && (maze.doorMasks.at(cell) & 1) && (maze.doorMasks.at(cell + 1) & 4)) edges.push_back({cell, cell + 1, 1, 4});
            if (y + 1 < maze.height && (maze.doorMasks.at(cell) & 8) && (maze.doorMasks.at(cell + maze.width) & 2)) edges.push_back({cell, cell + maze.width, 8, 2});
        }
        return edges;
    };
    for (size_t mi = 0; mi < d.mazes.size(); ++mi) {
        const auto &maze = d.mazes[mi];
        if (maze.doorMasks.size() != size_t(maze.width * maze.height)) throw std::runtime_error("Unsupported DGN greed dimensions");
        const auto edges = edgeList(maze);
        if (edges.size() > 20) throw std::runtime_error("Maze subset budget exceeded; explicit generator required");
        for (const auto &s : maze.starts) for (const auto &b : maze.bosses) {
            const int startCell = s[1] * maze.width + s[0], bossCell = b[1] * maze.width + b[0];
            for (uint64_t subset = 1; subset < (uint64_t(1) << edges.size()); ++subset) {
                std::vector<int> door(maze.width * maze.height, 0);
                for (size_t e = 0; e < edges.size(); ++e) if (subset & (uint64_t(1) << e)) { door[edges[e][0]] |= edges[e][2]; door[edges[e][1]] |= edges[e][3]; }
                std::set<int> reached{startCell}; std::queue<int> queue; queue.push(startCell);
                while (!queue.empty()) {
                    int cell = queue.front(); queue.pop();
                    for (const auto &edge : edges) if ((door[edge[0]] & edge[2]) && (edge[0] == cell || edge[1] == cell)) {
                        int other = edge[0] == cell ? edge[1] : edge[0]; if (reached.insert(other).second) queue.push(other);
                    }
                }
                if (!reached.count(bossCell) || reached.size() < 2) continue;
                bool valid = true;
                for (int cell : reached) if (candidates(maze, cell, door[cell], cell == bossCell).empty()) { valid = false; break; }
                // Do not retain disconnected fragments from a subset as invisible rooms.
                for (size_t cell = 0; cell < door.size(); ++cell) if (door[cell] && !reached.count(int(cell))) valid = false;
                if (valid) choices.push_back({mi, startCell, bossCell, subset});
            }
        }
    }
    if (choices.empty()) throw std::runtime_error("No source-compatible dungeon topology");
    const auto choice = choices[pick(choices.size())]; const auto &maze = d.mazes[choice.maze]; const auto edges = edgeList(maze);
    std::vector<int> door(maze.width * maze.height, 0);
    for (size_t e = 0; e < edges.size(); ++e) if (choice.edges & (uint64_t(1) << e)) { door[edges[e][0]] |= edges[e][2]; door[edges[e][1]] |= edges[e][3]; }
    DungeonRun run; run.dungeonId = id; run.seed = seed_; run.width = maze.width; run.height = maze.height;
    run.generatorVersion=generatorVersion;
    run.token = std::to_string(id) + ":" + std::to_string(seed_);
    for (int cell = 0; cell < int(door.size()); ++cell) if (door[cell]) {
        RunRoom room; room.x = cell % maze.width; room.y = cell / maze.width; room.doors = door[cell]; room.boss = cell == choice.boss;
        room.candidates = candidates(maze, cell, room.doors, room.boss); room.mapId = room.candidates[pick(room.candidates.size())]; room.path = catalog.maps.at(room.mapId).path;
        if (cell == choice.start) run.start = run.current = int(run.rooms.size());
        if (cell == choice.boss) run.boss = int(run.rooms.size());
        run.rooms.push_back(std::move(room));
    }
    run.room().visited = true;
    run.randomState=generatorVersion=="pcg32-world-v1"?streams.snapshot():Json{{"algorithm","legacy-mt19937_64-v1"},{"seed",seed_}};
    return run;
}
int DungeonRun::destination(Direction direction) const {
    const auto &r = room(); if (!(r.doors & directionBit(direction))) return -1;
    int x = r.x + (direction == Direction::Right ? 1 : direction == Direction::Left ? -1 : 0);
    int y = r.y + (direction == Direction::Down ? 1 : direction == Direction::Up ? -1 : 0);
    for (size_t i = 0; i < rooms.size(); ++i) if (rooms[i].x == x && rooms[i].y == y && (rooms[i].doors & directionBit(opposite(direction)))) return int(i);
    return -1;
}
bool DungeonRun::move(Direction direction) {
    if (!room().cleared) return false;
    int target = destination(direction); if (target < 0) return false;
    current = target; room().visited = true; return true;
}
bool DungeonRun::complete() const { return !rooms.empty() && rooms.at(boss).cleared; }
Json DungeonRun::describe() const {
    Json result = {{"dungeon", dungeonId}, {"seed", seed}, {"start", start}, {"boss", boss},
        {"width",width},{"height",height},{"token",token},{"generator_version",generatorVersion},
        {"random_state",randomState},{"rooms", Json::array()}};
    for (const auto &r : rooms) result["rooms"].push_back({{"map", r.mapId}, {"path", r.path}, {"x", r.x}, {"y", r.y}, {"doors", r.doors}, {"boss", r.boss}, {"candidates", r.candidates}});
    return result;
}
} // namespace dnf
