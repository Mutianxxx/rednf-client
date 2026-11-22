#include "dnf/progression.hpp"
#include "dnf/character_controller.hpp"
#include "dnf/source_weapon_qualification.hpp"
#include <climits>
#include <cmath>
#include <chrono>
#include <set>
#include <type_traits>
namespace dnf {
namespace {
Operation success(std::string message) { return {true, std::move(message), 0, 0}; }
Operation failure(std::string message) { return {false, std::move(message), 0, 0}; }
int integer(const Json &j, const char *key, int fallback = 0) {
    auto it = j.find(key); return it != j.end() && it->is_number_integer() ? it->get<int>() : fallback;
}
bool supportedQuest(int id) { return id == 101 || id == 102 || id == 103 || id == 4301 || id == 1016; }
std::string qkey(int id) { return std::to_string(id); }
int completionNpc(const Script &q) {
    int id = int(q.number("[complete npc index]", -1));
    return id < 0 ? int(q.number("[npc index]", -1)) : id;
}
int64_t threshold(const RegionCatalog &catalog, int level) {
    if (level <= 1) return 0;
    size_t index = size_t(level - 2);
    if (index < catalog.experienceThresholds.size()) return catalog.experienceThresholds[index];
    return INT64_MAX;
}
void applyExperience(Json &state, const RegionCatalog &catalog, int64_t amount) {
    if (amount <= 0) return;
    const auto &value = state.at("xp");
    if (!value.is_number_integer() || (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(INT64_MAX)))
        throw std::runtime_error("Invalid progression experience");
    const auto previous = value.get<int64_t>();
    if (previous < 0 || previous > INT64_MAX - amount) throw std::overflow_error("Progression experience overflow");
    const int64_t xp = previous + amount;
    int level = integer(state, "level", 1);
    while (level < 99 && xp >= threshold(catalog, level + 1)) ++level;
    state["xp"] = xp;
    state["level"] = level;
}
int rewardSourceInteger(const Json &value, const Script &source, const char *tag) {
    if (!value.is_number_integer() ||
        (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(INT_MAX)) ||
        (!value.is_number_unsigned() && (value.get<int64_t>() < INT_MIN || value.get<int64_t>() > INT_MAX)))
        throw std::runtime_error("Invalid reward integer in " + source.path + " " + tag);
    return value.get<int>();
}
int clearCounter(const Json &value, const char *name) {
    if (!value.is_number_integer() ||
        (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(INT_MAX)) ||
        (!value.is_number_unsigned() && (value.get<int64_t>() < 0 || value.get<int64_t>() > INT_MAX)))
        throw std::runtime_error(std::string("Invalid dungeon clear counter: ") + name);
    return value.get<int>();
}
const DungeonDefinition &clearSourceDungeon(const RegionCatalog &catalog, int dungeon) {
    const auto found = catalog.dungeons.find(dungeon);
    if (found == catalog.dungeons.end())
        throw std::runtime_error("Dungeon clear source ID not registered: " + std::to_string(dungeon));
    const auto &definition = found->second;
    if (!definition.enabled || definition.id != dungeon || definition.path.empty() ||
        normalize(definition.source.path) != normalize(definition.path) ||
        !definition.source.source.is_object() || definition.source.source.empty() ||
        definition.source.rawBytes.empty() || definition.mazes.empty() || definition.mapIds.empty())
        throw std::runtime_error("Dungeon clear source not prepared/enabled: " + definition.path);
    const auto packageIdentity = definition.source.source.value("package_identity", std::string());
    if (packageIdentity.empty()) throw std::runtime_error("Dungeon clear package identity missing: " + definition.path);
    if (definition.basisLevel <= 0)
        throw std::runtime_error("Invalid dungeon clear basis level: " + definition.path);
    const auto basis = definition.source.values("[basis level]");
    if (!basis.empty() && rewardSourceInteger(basis.at(0), definition.source, "[basis level]") != definition.basisLevel)
        throw std::runtime_error("Dungeon clear basis metadata/source mismatch: " + definition.path);
    // Initial-region catalogs and OnDemand preparation publish the same MAP/
    // MOB closure. Do not equate metadata-only, an empty pool or an unavailable
    // dependency with an eligible clear. Shared MAPs may serve several DGNs.
    for (int mapId : definition.mapIds) {
        const auto map = catalog.maps.find(mapId);
        if (map == catalog.maps.end() || map->second.path.empty() ||
            normalize(map->second.source.path) != normalize(map->second.path) ||
            map->second.source.rawBytes.empty() || !map->second.source.source.is_object() ||
            map->second.source.source.value("package_identity", std::string()) != packageIdentity)
            throw std::runtime_error("Dungeon clear MAP source unavailable: " + definition.path + " MAP " + std::to_string(mapId));
        for (const auto &spawn : map->second.monsters) {
            const auto monster = catalog.monsters.find(spawn.id);
            if (monster == catalog.monsters.end() || monster->second.path.empty() || monster->second.rawBytes.empty() ||
                normalize(monster->second.path) != catalog.monsterPath(spawn.id) || !monster->second.source.is_object() ||
                monster->second.source.value("package_identity", std::string()) != packageIdentity)
                throw std::runtime_error("Dungeon clear MOB source unavailable: " + definition.path + " MOB " + std::to_string(spawn.id));
        }
    }
    return definition;
}
int64_t wallMilliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
}
Json decodeBasicMonsterItems(const Script &source) {
    Json result = {{"policy", "1031-basic-mob-sibling-item-fields-v1"}, {"path", source.path},
                   {"source", source.source}, {"blocks", Json::array()}, {"rows", Json::array()}};
    std::set<std::string> explicitlyClosed;
    for (const auto &field : source.fields) {
        const auto tag = normalize(field.tag);
        if (tag.size() > 3 && tag.rfind("[/", 0) == 0)
            explicitlyClosed.insert("[" + tag.substr(2));
    }
    std::vector<std::string> scopes;
    size_t block = 0;
    for (const auto &field : source.fields) {
        const auto tag = normalize(field.tag);
        if (tag.size() > 3 && tag.rfind("[/", 0) == 0) {
            const auto opened = "[" + tag.substr(2);
            if (!scopes.empty() && scopes.back() == opened) scopes.pop_back();
            else if (opened == "[item]")
                throw std::runtime_error("Unmatched basic reward item scope in " + source.path);
            continue;
        }
        if (tag == "[item]") {
            if (!scopes.empty())
                throw std::runtime_error("Unsupported nested basic reward item scope in " + source.path + " under " + scopes.back());
            if (!field.values.is_array() || field.values.size() % 2 != 0)
                throw std::runtime_error("Truncated reward rows in " + source.path + " [item]");
            result["blocks"].push_back({{"index", block}, {"offset", field.offset}, {"values", field.values}});
            for (size_t i = 0; i < field.values.size(); i += 2) {
                const int item = rewardSourceInteger(field.values.at(i), source, "[item] id");
                const int weight = rewardSourceInteger(field.values.at(i + 1), source, "[item] weight");
                if (item <= 0) throw std::runtime_error("Invalid basic reward item ID in " + source.path);
                result["rows"].push_back({{"item", item}, {"weight", std::max(0, weight)}, {"source_weight", weight},
                    {"block", block}, {"field_offset", field.offset}, {"value_index", i}});
            }
            ++block;
        }
        if (explicitlyClosed.count(tag)) scopes.push_back(tag);
    }
    if (std::find(scopes.begin(), scopes.end(), "[item]") != scopes.end())
        throw std::runtime_error("Unterminated basic reward item scope in " + source.path);
    return result;
}
Progression::Progression(const RegionCatalog &catalog) : catalog_(catalog) { initialize(); }
void Progression::initialize(int level_, int legacyWeapon) {
    level_ = std::clamp(level_, 1, 99);
    state = {{"version", 1}, {"level", level_}, {"xp", threshold(catalog_, level_)}, {"gold", 0},
             {"inventory", Json::array()}, {"equipped", Json::object()}, {"quests", Json::object()},
             {"events", Json::object()}, {"drops", Json::object()}, {"clears", Json::object()}, {"cooldowns", Json::object()},
             {"cooldown_wall", Json::object()}, {"next_uid", 1}, {"legacy_weapon_appearance", legacyWeapon},
             {"policy", "native-lorien-reconstruction-v1"}};
    rebaseCooldowns_ = false;
    // Explicit migration/new-character starter, sourced PC definition; not a claim about PC login gifts.
    grant(27118, 1);
    if (!state["inventory"].empty()) state["equipped"]["[weapon]"] = state["inventory"][0]["uid"];
}
void Progression::load(const Json &saved, int level_, int legacyWeapon) {
    initialize(level_, legacyWeapon);
    if (!saved.is_object()) return;
    // Merge instead of recreating so future fields survive a round trip.
    for (auto it = saved.begin(); it != saved.end(); ++it) state[it.key()] = it.value();
    for (const char *name : {"equipped", "quests", "events", "drops", "clears", "cooldowns", "cooldown_wall"})
        if (!state[name].is_object()) throw std::runtime_error(std::string("Invalid progression object: ") + name);
    if (!state["inventory"].is_array() || state["inventory"].size() > inventoryCapacity)
        throw std::runtime_error("Invalid progression inventory");
    if (!state["level"].is_number_integer() || level() < 1 || level() > 99 ||
        !state["gold"].is_number_integer() || gold() < 0 || !state["xp"].is_number_integer() || state["xp"].get<int64_t>() < 0)
        throw std::runtime_error("Invalid progression counters");
    std::set<int> uids; int maximum = 0;
    for (const auto &entry : state["inventory"]) {
        if (!entry.is_object() || integer(entry, "uid", -1) <= 0 || integer(entry, "id", -1) <= 0 || integer(entry, "count", -1) <= 0 ||
            !uids.insert(integer(entry, "uid")).second) throw std::runtime_error("Invalid progression inventory entry");
        maximum = std::max(maximum, integer(entry, "uid"));
        const auto *definition = item(integer(entry, "id"));
        if (definition && (integer(entry, "count") > definition->stackLimit ||
            (definition->equipment && (integer(entry, "count") != 1 || integer(entry, "durability", -1) < 0 || integer(entry, "durability") > definition->durability))))
            throw std::runtime_error("Invalid item stack or durability");
    }
    for (auto it = state["equipped"].begin(); it != state["equipped"].end(); ++it)
        if (!it.value().is_number_integer() || !uids.count(it.value().get<int>())) throw std::runtime_error("Equipped item UID missing");
    state["next_uid"] = std::max(maximum + 1, integer(state, "next_uid", 1));
    // Monotonic simulation timestamps restart on process launch. Do not persist an infinite cooldown.
    state["cooldowns"] = Json::object();
    rebaseCooldowns_ = true;
}
void Progression::commitPrepared(Progression &&candidate) {
    if (&catalog_ != &candidate.catalog_)
        throw std::invalid_argument("Prepared progression belongs to another content catalog");
    static_assert(noexcept(state.swap(candidate.state)), "Prepared JSON publication must not throw");
    static_assert(noexcept(definitions_.swap(candidate.definitions_)), "Prepared definition publication must not throw");
    state.swap(candidate.state);
    definitions_.swap(candidate.definitions_);
    std::swap(rebaseCooldowns_, candidate.rebaseCooldowns_);
}
const ItemDefinition *Progression::item(int id) const {
    auto cached = definitions_.find(id); if (cached != definitions_.end()) return &cached->second;
    const auto *script = catalog_.item(id); if (!script) return nullptr;
    ItemDefinition d; d.id = id; d.source = *script; d.path = script->path; d.name = script->text("[name]", d.path);
    d.minimumLevel = int(script->number("[minimum level]", 1)); d.price = int(script->number("[price]"));
    d.value = int(script->number("[value]")); d.repairPrice = int(script->number("[repair price]"));
    d.durability = int(script->number("[durability]")); d.rarity = int(script->number("[rarity]"));
    d.equipment = d.path.rfind("equipment/", 0) == 0;
    d.stackLimit = d.equipment ? 1 : std::max(1, int(script->number("[stack limit]", 1000)));
    d.slot = script->text("[equipment type]");
    d.avatar = d.slot.size() >= 8 && d.slot.find(" avatar]") != std::string::npos;
    auto jobs = script->values("[usable job]");
    d.swordman = std::find(jobs.begin(), jobs.end(), Json("[swordman]")) != jobs.end() ||
                 std::find(jobs.begin(), jobs.end(), Json("[all]")) != jobs.end();
    if (d.slot == "[weapon]") {
        int subtype = int(script->number("[sub type]", -1));
        d.weapon = subtype == 0 ? 0 : subtype == 1 ? 1 : subtype == 3 ? 2 : subtype == 2 ? 3 : -1;
    }
    d.cooldown = int(script->number("[cool time]"));
    auto recovery = [&](const char *tag) {
        auto values = script->values(tag);
        return values.size() >= 2 && values[0] == "+" && values[1].is_number() ? int(values[1].get<double>()) : 0;
    };
    d.hp = recovery("[hp recovery]"); d.mp = recovery("[mp recovery]");
    d.physicalAttack = int(script->number("[equipment physical attack]"));
    d.physicalDefense = int(script->number("[equipment physical defense]"));
    auto icon = script->values("[icon]"); if (icon.size() >= 2) { d.icon = normalize(icon[0]); d.iconFrame = icon[1]; }
    auto field = script->values("[field image]"); if (field.size() >= 2) { d.fieldImage = normalize(field[0]); d.fieldFrame = field[1]; }
    return &definitions_.emplace(id, std::move(d)).first->second;
}
bool Progression::grant(int id, int count) {
    const auto *d = item(id); if (!d || count <= 0) return false;
    auto &inventory = state["inventory"];
    int remaining = count;
    if (!d->equipment) for (auto &entry : inventory) if (entry["id"] == id) {
        int added = std::min(remaining, d->stackLimit - integer(entry, "count"));
        remaining -= added;
    }
    int needed = (remaining + d->stackLimit - 1) / d->stackLimit;
    if (inventory.size() + size_t(needed) > inventoryCapacity) return false;
    remaining = count;
    if (!d->equipment) for (auto &entry : inventory) if (entry["id"] == id) {
        int added = std::min(remaining, d->stackLimit - integer(entry, "count"));
        entry["count"] = integer(entry, "count") + added; remaining -= added;
    }
    while (remaining > 0) {
        int amount = std::min(remaining, d->stackLimit), uid = integer(state, "next_uid", 1);
        inventory.push_back({{"uid", uid}, {"id", id}, {"count", amount}, {"durability", d->durability}});
        state["next_uid"] = uid + 1; remaining -= amount;
    }
    return true;
}
int Progression::level() const { return integer(state, "level", 1); }
int Progression::gold() const { return integer(state, "gold"); }
int Progression::quantity(int id) const {
    int result = 0; for (const auto &entry : state["inventory"]) if (entry["id"] == id) result += integer(entry, "count"); return result;
}
int Progression::equippedWeapon() const {
    int uid = integer(state["equipped"], "[weapon]", -1);
    for (const auto &entry : state["inventory"]) if (entry["uid"] == uid) {
        const auto *d = item(integer(entry, "id")); if (d && d->weapon >= 0) return d->weapon;
    }
    return 0;
}
int Progression::equippedIndex(const std::string &slot) const {
    int uid = integer(state["equipped"], slot.c_str(), -1);
    const auto &inventory = state["inventory"];
    for (size_t i = 0; i < inventory.size(); ++i)
        if (integer(inventory[i], "uid") == uid) return int(i);
    return -1;
}
bool Progression::equipped(int index) const {
    const auto &inventory = state["inventory"];
    if (index < 0 || size_t(index) >= inventory.size()) return false;
    int uid = integer(inventory[index], "uid");
    for (const auto &equippedUid : state["equipped"]) if (equippedUid == uid) return true;
    return false;
}
CharacterAppearance Progression::appearance(Pvf &pvf) const {
    const CharacterCatalog characters(pvf);
    return appearance(pvf, characters, {});
}
CharacterAppearance Progression::appearance(Pvf &pvf, const CharacterCatalog &characters,
                                          CharacterIdentity identity) const {
    auto result = defaultCharacterAppearance(pvf, characters, identity);
    const auto &character = characters.at(identity.jobId);
    for (const auto &entry : state["inventory"]) {
        const auto *definition = item(integer(entry, "id"));
        if (!definition || !state["equipped"].contains(definition->slot) ||
            state["equipped"][definition->slot] != entry["uid"]) continue;
        if (!equipmentAllowsJob(character, definition->source)) {
            result.issues.push_back({{"kind", "equipped_item_job_not_qualified"}, {"path", definition->source.path}});
            continue;
        }
        applyEquipmentAppearance(result, definition->source, character.job);
    }
    bindEquipmentMotions(pvf, result);
    return result;
}
int Progression::attackBonus() const {
    int uid = integer(state["equipped"], "[weapon]", -1);
    for (const auto &entry : state["inventory"]) if (entry["uid"] == uid && integer(entry, "durability") > 0) {
        const auto *d = item(integer(entry, "id")); if (d) return d->physicalAttack;
    }
    return 0;
}
int Progression::defenseBonus() const {
    int result = 0;
    for (const auto &entry : state["inventory"]) {
        const auto *d = item(integer(entry, "id"));
        if (d && d->slot != "[weapon]" && state["equipped"].contains(d->slot) &&
            state["equipped"][d->slot] == entry["uid"] && integer(entry, "durability") > 0) result += d->physicalDefense;
    }
    return result;
}
int Progression::experienceToNextLevel() const {
    if (level() >= 99) return 0;
    int64_t next = threshold(catalog_, level() + 1) - state["xp"].get<int64_t>();
    return int(std::clamp<int64_t>(next, 0, INT_MAX));
}
void Progression::addExperience(int amount) {
    applyExperience(state, catalog_, amount);
}
Operation Progression::buy(int shopId, int id, int count) {
    auto shop = catalog_.shops.find(shopId); const auto *d = item(id);
    if (shop != catalog_.shops.end() && !shop->second.enabled) return failure(shop->second.lockedReason);
    if (shop == catalog_.shops.end() || !d || std::find(shop->second.items.begin(), shop->second.items.end(), id) == shop->second.items.end()) return failure("商店未出售此物品");
    if (count <= 0 || count > 999 || d->price <= 0) return failure("购买数量或价格无效");
    int64_t price = int64_t(count) * d->price;
    if (price > gold()) return failure("金币不足");
    if (!grant(id, count)) return failure("背包空间不足");
    state["gold"] = gold() - int(price); return success("购买了" + d->name);
}
Operation Progression::sell(int index, int count) {
    auto &inventory = state["inventory"];
    if (index < 0 || size_t(index) >= inventory.size() || count <= 0 || count > integer(inventory[index], "count")) return failure("出售数量无效");
    const auto *d = item(integer(inventory[index], "id")); if (!d) return failure("未识别物品不能出售");
    for (const auto &uid : state["equipped"]) if (uid == inventory[index]["uid"]) return failure("请先替换已穿戴装备");
    // Source value is the reconstructed sale unit value; absent values use price/10, documented policy.
    int value = d->value > 0 ? d->value : d->price / 10;
    int64_t total = int64_t(gold()) + int64_t(value) * count;
    if (total > INT_MAX) return failure("金币上限");
    state["gold"] = int(total);
    inventory[index]["count"] = integer(inventory[index], "count") - count;
    if (inventory[index]["count"] == 0) inventory.erase(inventory.begin() + index);
    return success("出售了" + d->name);
}
Operation Progression::equip(int index) {
    auto &inventory = state["inventory"];
    if (index < 0 || size_t(index) >= inventory.size()) return failure("未选择装备");
    const auto *d = item(integer(inventory[index], "id"));
    if (!d || !d->equipment || d->slot.empty()) return failure("此物品不能穿戴");
    if (!d->swordman || (d->slot == "[weapon]" && d->weapon < 0)) return failure("职业或武器外观未支持");
    if (level() < d->minimumLevel) return failure("角色等级不足");
    state["equipped"][d->slot] = inventory[index]["uid"]; return success("装备了" + d->name);
}
bool Progression::itemUsableBy(int id, const CharacterDefinition &character) const {
    const auto *definition = item(id);
    return definition && (!definition->equipment || equipmentAllowsJob(character, definition->source));
}
Operation Progression::equip(int index, const CharacterDefinition &character) {
    auto &inventory = state["inventory"];
    if (index < 0 || size_t(index) >= inventory.size()) return failure("未选择装备");
    const auto *definition = item(integer(inventory[index], "id"));
    if (!definition || !definition->equipment || definition->slot.empty()) return failure("此物品不能穿戴");
    const auto restriction = equipmentJobRestriction(character, definition->source);
    if (restriction.gate != EquipmentJobGate::Allowed || (definition->slot == "[weapon]" &&
        !characterWeaponSourceSupported(character,definition->source,definition->weapon)))
        return failure("职业或武器外观未支持");
    if (level() < definition->minimumLevel) return failure("角色等级不足");
    state["equipped"][definition->slot] = inventory[index]["uid"];
    return success("装备了" + definition->name);
}
Operation Progression::unequip(int index) {
    const auto &inventory = state["inventory"];
    if (index < 0 || size_t(index) >= inventory.size()) return failure("未选择装备");
    const auto *definition = item(integer(inventory[index], "id"));
    if (!definition || !equipped(index)) return failure("此物品尚未穿戴");
    state["equipped"].erase(definition->slot);
    return success("卸下了" + definition->name);
}
int Progression::repairCost(int index) const {
    int64_t cost = 0; const auto &inventory = state["inventory"];
    if (index >= int(inventory.size())) return 0;
    for (size_t i = 0; i < inventory.size(); ++i) if (index < 0 || i == size_t(index)) {
        const auto *d = item(integer(inventory[i], "id"));
        if (d && d->equipment && d->durability > 0) {
            int missing = std::max(0, d->durability - integer(inventory[i], "durability"));
            cost += (int64_t(std::max(1, d->repairPrice)) * missing + d->durability - 1) / d->durability;
        }
    }
    return int(std::min<int64_t>(cost, INT_MAX));
}
Operation Progression::repair(int index) {
    int cost = repairCost(index); if (cost == 0) return failure("没有需要修理的装备");
    if (gold() < cost) return failure("修理所需金币不足");
    auto &inventory = state["inventory"];
    for (size_t i = 0; i < inventory.size(); ++i) if (index < 0 || i == size_t(index)) {
        const auto *d = item(integer(inventory[i], "id")); if (d && d->equipment) inventory[i]["durability"] = d->durability;
    }
    state["gold"] = gold() - cost; return success("修理完成，花费" + std::to_string(cost) + "金币");
}
void Progression::wear(int points) {
    if (points <= 0) return;
    for (auto &entry : state["inventory"]) for (const auto &uid : state["equipped"]) if (uid == entry["uid"])
        entry["durability"] = std::max(0, integer(entry, "durability") - points);
}
Operation Progression::usePotion(int index, int64_t now, int hp, int maxHp, int mp, int maxMp) {
    auto &inventory = state["inventory"];
    if (index < 0 || size_t(index) >= inventory.size()) return failure("未选择药剂");
    const auto *d = item(integer(inventory[index], "id"));
    if (!d || (!d->hp && !d->mp)) return failure("此物品不是可用恢复药剂");
    if (level() < d->minimumLevel) return failure("角色等级不足");
    if ((d->hp == 0 || hp >= maxHp) && (d->mp == 0 || mp >= maxMp)) return failure("当前无需恢复");
    if (rebaseCooldowns_) {
        int64_t wall = wallMilliseconds();
        for (auto it = state["cooldown_wall"].begin(); it != state["cooldown_wall"].end(); ++it)
            if (it.value().is_number_integer()) state["cooldowns"][it.key()] = now + std::clamp<int64_t>(it.value().get<int64_t>() - wall, 0, 600000);
        rebaseCooldowns_ = false;
    }
    const auto group = d->source.number("[cooltime group]", -1);
    std::string key = group < 0 ? "item:" + std::to_string(d->id) : "group:" + std::to_string(int(group));
    if (state["cooldowns"].contains(key) && state["cooldowns"][key].get<int64_t>() > now) return failure("药剂冷却中");
    state["cooldowns"][key] = now + d->cooldown;
    state["cooldown_wall"][key] = wallMilliseconds() + d->cooldown;
    inventory[index]["count"] = integer(inventory[index], "count") - 1;
    if (inventory[index]["count"] == 0) inventory.erase(inventory.begin() + index);
    Operation result = success("使用了" + d->name); result.hp = std::min(d->hp, std::max(0, maxHp - hp)); result.mp = std::min(d->mp, std::max(0, maxMp - mp)); return result;
}
bool Progression::questCompleted(int id) const {
    auto it = state["quests"].find(qkey(id)); return it != state["quests"].end() && it->value("status", "") == "complete";
}
bool Progression::questActive(int id) const {
    auto it = state["quests"].find(qkey(id)); return it != state["quests"].end() && it->value("status", "") == "active";
}
bool Progression::questAvailable(int id) const {
    if (!supportedQuest(id) || questActive(id) || questCompleted(id)) return false;
    const auto it = catalog_.quests.find(id); if (it == catalog_.quests.end()) return false;
    const auto &q = it->second; auto levels = q.values("[level]");
    if (!levels.empty() && level() < levels[0].get<int>()) return false;
    for (const auto &f : q.fields) if (f.tag == "[pre required quest]")
        for (const auto &v : f.values) if (v.is_number_integer() && v.get<int>() > 0 && !questCompleted(v.get<int>())) return false;
    return true;
}
bool Progression::questReady(int id) const {
    if (!questActive(id)) return false;
    const auto &q = catalog_.quests.at(id); const auto &s = state["quests"][qkey(id)];
    const auto values = q.values("[int data]"); const auto type = q.text("[type]");
    if (type == "[meet npc]") return s.value("met", false);
    if (type == "[condition under clear]") return integer(s, "progress") >= 1;
    if (type == "[hunt monster]" && values.size() >= 4) return integer(s, "progress") >= values[3].get<int>();
    return false;
}
Operation Progression::acceptQuest(int id, int npc) {
    if (!questAvailable(id)) return failure("任务条件未满足");
    const auto &q = catalog_.quests.at(id);
    if (int(q.number("[npc index]", -1)) != npc) return failure("请前往委托人处");
    auto data = q.values("[int data]");
    state["quests"][qkey(id)] = {{"status", "active"}, {"progress", 0},
        {"met", q.text("[type]") == "[meet npc]" && !data.empty() && data[0] == npc}};
    return success("接受任务：" + q.text("[name]"));
}
void Progression::rewardQuest(int id) {
    const auto &q = catalog_.quests.at(id); const auto rewards = q.values("[reward int data]");
    for (size_t i = 0; i + 1 < rewards.size();) {
        if (!rewards[i].is_number_integer()) throw std::runtime_error("Unsupported quest reward record");
        int itemId = rewards[i++], count = 0;
        if (rewards[i] == "[job]") {
            if (i + 3 >= rewards.size()) throw std::runtime_error("Truncated quest job reward");
            int job = rewards[i + 1]; count = job == 0 ? rewards[i + 3].get<int>() : 0; i += 4;
        } else count = rewards[i++].get<int>();
        if (count <= 0) continue;
        if (itemId == 0) state["gold"] = gold() + count;
        else if (!grant(itemId, count)) throw std::runtime_error("背包空间不足，任务奖励未领取");
    }
    addExperience(250); // Explicit reconstruction; PC quest XP consumer is not yet verified.
}
Operation Progression::turnInQuest(int id, int npc) {
    if (!questReady(id)) return failure("任务尚未完成");
    if (completionNpc(catalog_.quests.at(id)) != npc) return failure("请前往交付人处");
    Json before = state;
    try { rewardQuest(id); state["quests"][qkey(id)]["status"] = "complete"; }
    catch (const std::exception &e) { state = std::move(before); return failure(e.what()); }
    return success("完成任务：" + catalog_.quests.at(id).text("[name]"));
}
Operation Progression::talkNpc(int npc) {
    for (const auto &[id, q] : catalog_.quests) if (questActive(id) && q.text("[type]") == "[meet npc]") {
        auto target = q.values("[int data]"); if (!target.empty() && target[0] == npc) state["quests"][qkey(id)]["met"] = true;
    }
    auto it = catalog_.npcs.find(npc); return success(it == catalog_.npcs.end() ? "交谈" : it->second.name);
}
bool Progression::recordKill(int dungeon, int monster, int monsterLevel, const std::string &eventKey, uint64_t seed,
                             RandomStreams *randomStreams) {
    if (eventKey.empty()) return false;
    if (!state.at("events").is_object()) throw std::runtime_error("Invalid progression event ledger");
    if (state.at("events").contains(eventKey)) return false;
    const auto &definition = clearSourceDungeon(catalog_, dungeon);
    const auto packageIdentity = definition.source.source.at("package_identity");
    const auto sourceMonster = catalog_.monsters.find(monster);
    if (sourceMonster == catalog_.monsters.end() || sourceMonster->second.rawBytes.empty() ||
        sourceMonster->second.path.empty() || normalize(sourceMonster->second.path) != catalog_.monsterPath(monster) ||
        !sourceMonster->second.source.is_object() ||
        sourceMonster->second.source.value("package_identity", Json()) != packageIdentity)
        throw std::runtime_error("Kill reward MOB source unavailable or mismatched: " + std::to_string(monster));
    // Prepare the complete reward against private state. A source error, RNG
    // exhaustion or allocation failure must leave both ledgers and the live
    // random bank untouched, so this event can be retried without a reroll.
    Json next = state;
    next["events"][eventKey] = {{"dungeon", dungeon}, {"monster", monster}};
    for (const auto &[id, q] : catalog_.quests) if (questActive(id) && q.text("[type]") == "[hunt monster]") {
        auto target = q.values("[int data]");
        if (target.size() >= 4 && target[0] == dungeon && target[2] == monster) {
            const auto limit = rewardSourceInteger(target[3], q, "[int data]");
            const auto progress = int64_t(integer(state.at("quests").at(qkey(id)), "progress"));
            next["quests"][qkey(id)]["progress"] = int(std::min<int64_t>(limit, progress + 1));
        }
    }
    monsterLevel = std::clamp(monsterLevel, 1, 99);
    applyExperience(next, catalog_, 100 * monsterLevel);
    Json drop = {{"monster", monster}, {"seed", seed}, {"gold", 20 + 5 * monsterLevel}, {"items", Json::array()}, {"claimed", false}};
    // Stable FNV event hash, independent of the implementation-defined std::hash.
    uint64_t hash = 1469598103934665603ull; for (unsigned char ch : eventKey) hash = (hash ^ ch) * 1099511628211ull;
    RandomStreams prepared = randomStreams ? *randomStreams : RandomStreams(seed ^ hash);
    auto &random = prepared.stream(RandomDomain::Loot, hash ^ seed);
    drop["random_policy"]="pcg32-loot-legacy-reward-selection-v1";
    drop["random_before"]=random.snapshot();
    auto mob = catalog_.monsters.find(monster);
    std::vector<std::pair<int, uint64_t>> weightedItems;
    uint64_t total = 0;
    if (mob != catalog_.monsters.end()) {
        auto decoded = decodeBasicMonsterItems(mob->second);
        // Validate every source row before drawing. Invalid rows cannot be
        // hidden by the 50% item gate or by an earlier selected item.
        for (const auto &row : decoded.at("rows")) {
            const int item = row.at("item").get<int>();
            const auto *itemSource = catalog_.item(item);
            if (!itemSource || itemSource->path.empty() || itemSource->rawBytes.empty() ||
                !itemSource->source.is_object() || itemSource->source.value("package_identity", Json()) != packageIdentity)
                throw std::runtime_error("Kill reward item source unavailable: " + std::to_string(item) + " in " + mob->second.path);
            const auto weight = uint64_t(row.at("weight").get<int>());
            if (total > UINT64_MAX - weight) throw std::overflow_error("Reward weight total overflow: " + mob->second.path);
            total += weight;
            weightedItems.emplace_back(item, weight);
        }
        drop["item_source"] = std::move(decoded);
    }
    if (mob != catalog_.monsters.end() && random.bounded(2) == 0) {
        if (total > 0) {
            uint64_t roll = random.bounded64(total);
            for (const auto &[item, weight] : weightedItems) {
                if (roll < weight) { drop["items"].push_back({{"id", item}, {"count", 1}}); break; }
                roll -= weight;
            }
        }
    }
    // Region equipment selection is a visible reconstructed policy, not inferred PC rarity odds.
    if (random.bounded(10) == 0) {
        const int equipment[] = {27118, 27601, 16400, 100260012}; int id = equipment[random.bounded(4)];
        drop["items"].push_back({{"id", id}, {"count", 1}});
    }
    drop["random_after"]=random.snapshot();
    next["drops"][eventKey] = std::move(drop);
    // Stream insertion has the map's strong exception guarantee. Once it
    // succeeds, PCG assignment and JSON swap do not throw. Update only this
    // stream so references to other named streams stay valid.
    static_assert(std::is_nothrow_copy_assignable<Pcg32>::value, "Reward RNG commit must not throw");
    if (randomStreams) randomStreams->stream(RandomDomain::Loot, hash ^ seed) = random;
    state.swap(next);
    return true;
}
Operation Progression::claimDrop(const std::string &eventKey) {
    auto drop = state["drops"].find(eventKey);
    if (drop == state["drops"].end() || drop->value("claimed", false)) return failure("掉落已领取或不存在");
    Json before = state;
    for (const auto &entry : (*drop)["items"]) if (!grant(integer(entry, "id"), integer(entry, "count"))) {
        state = std::move(before); return failure("背包空间不足或物品尚未支持，掉落保留");
    }
    int64_t amount = int64_t(gold()) + integer(*drop, "gold");
    if (amount > INT_MAX) { state = std::move(before); return failure("金币上限，掉落保留"); }
    state["gold"] = int(amount); state["drops"][eventKey]["claimed"] = true;
    return success("拾取成功");
}
bool Progression::clearDungeon(int dungeon, const std::string &runToken, int rooms) {
    if (runToken.empty()) return false;
    if (rooms <= 0) throw std::invalid_argument("Dungeon clear requires a positive cleared-room count");
    if (dungeonClearRecorded(dungeon, runToken, rooms)) return false;
    const auto &definition = clearSourceDungeon(catalog_, dungeon);
    if (!state.at("quests").is_object()) throw std::runtime_error("Invalid progression quest ledger at dungeon clear");
    const int previousGold = clearCounter(state.at("gold"), "gold");
    const int previousLevel = clearCounter(state.at("level"), "level");
    if (previousLevel < 1 || previousLevel > 99)
        throw std::runtime_error("Invalid progression level at dungeon clear");
    // These coefficients preserve the existing beta policy; they are not
    // verified PC reward arithmetic. Keep source basis100 instead of clamp99.
    const int64_t experience = int64_t(500) * definition.basisLevel;
    const int64_t goldReward = int64_t(200) * definition.basisLevel;
    if (goldReward > INT_MAX || int64_t(previousGold) > INT_MAX - goldReward)
        throw std::overflow_error("Dungeon clear gold overflow: " + definition.path);
    Json next = state;
    applyExperience(next, catalog_, experience);
    for (const auto &[id, q] : catalog_.quests) if (questActive(id) && q.text("[type]") == "[condition under clear]") {
        const auto target = q.values("[int data]");
        if (target.empty()) throw std::runtime_error("Dungeon clear quest target missing: " + q.path);
        if (rewardSourceInteger(target.at(0), q, "[int data] dungeon") == dungeon)
            next["quests"][qkey(id)]["progress"] = 1;
    }
    next["gold"] = int(int64_t(previousGold) + goldReward);
    next["clears"][runToken] = {{"dungeon", dungeon}, {"rooms", rooms},
        {"policy", "beta-basic-dungeon-clear-legacy-coefficients-v1"}, {"basis_level", definition.basisLevel},
        {"experience", experience}, {"gold", goldReward}, {"source_path", definition.path}, {"source", definition.source.source}};
    static_assert(noexcept(state.swap(next)), "Dungeon clear JSON publication must not throw");
    state.swap(next);
    return true;
}
bool Progression::dungeonClearRecorded(int dungeon, const std::string &runToken, int rooms) const {
    const auto &clears = state.at("clears");
    if (!clears.is_object()) throw std::runtime_error("Invalid progression dungeon clear ledger");
    if (runToken.empty()) return false;
    const auto receipt = clears.find(runToken);
    if (receipt == clears.end()) return false;
    if (!receipt->is_object() || !receipt->contains("dungeon") || !receipt->contains("rooms") || rooms <= 0 ||
        clearCounter(receipt->at("dungeon"), "receipt dungeon") != dungeon ||
        clearCounter(receipt->at("rooms"), "receipt rooms") != rooms)
        throw std::runtime_error("Dungeon clear receipt conflicts with run token: " + runToken);
    return true;
}
Json Progression::availableQuests(int npc) const {
    Json result = Json::array();
    for (const auto &[id, q] : catalog_.quests) {
        if (!supportedQuest(id)) continue;
        int giver = int(q.number("[npc index]", -1));
        if ((questAvailable(id) && giver == npc) || (questActive(id) && (giver == npc || completionNpc(q) == npc)))
            result.push_back({{"id", id}, {"name", q.text("[name]")}, {"available", questAvailable(id)}, {"active", questActive(id)},
                {"ready", questReady(id)}, {"description", q.text("[condition message]")}, {"giver", giver}, {"complete_npc", completionNpc(q)}});
    }
    return result;
}
Json Progression::questSummary() const {
    Json result = Json::array();
    for (const auto &[id, q] : catalog_.quests) if (supportedQuest(id) && (questActive(id) || questCompleted(id)))
        result.push_back({{"id", id}, {"name", q.text("[name]")}, {"status", state["quests"][qkey(id)]["status"]},
            {"progress", state["quests"][qkey(id)].value("progress", 0)}, {"ready", questReady(id)}, {"description", q.text("[condition message]")}});
    return result;
}
} // namespace dnf
