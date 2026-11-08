#pragma once
#include "region.hpp"
#include "appearance.hpp"
#include "equipment_skill_requirement.hpp"
namespace dnf {
struct CharacterDefinition;
struct ItemDefinition {
    int id = 0, minimumLevel = 1, price = 0, value = 0, repairPrice = 0, durability = 0;
    int rarity = 0, stackLimit = 1, weapon = -1, cooldown = 0, hp = 0, mp = 0;
    int physicalAttack = 0, physicalDefense = 0;
    std::string path, name, slot, icon, fieldImage;
    int iconFrame = 0, fieldFrame = 0;
    bool equipment = false, swordman = false, avatar = false;
    Script source;
    EquipmentSkillRequirement requiredSkill;
};
struct Operation {
    bool ok = false;
    std::string message;
    int hp = 0, mp = 0;
    explicit operator bool() const { return ok; }
};
// Current 1031 basic MOB [item] fields are sibling lists, including empty
// lists. Retain every block/row/offset in source order; never merge arbitrary
// nested reward scopes or change Script::values' first-field contract.
Json decodeBasicMonsterItems(const Script &source);
// Platform-neutral persistent state; World integration is owned by the application.
class Progression {
    const RegionCatalog &catalog_;
    mutable std::map<int, ItemDefinition> definitions_;
    bool rebaseCooldowns_ = false;
    bool grant(int id, int quantity);
    void rewardQuest(int id);
  public:
    Json state = Json::object();
    static constexpr int inventoryCapacity = 48;
    explicit Progression(const RegionCatalog &catalog);
    void initialize(int level = 1, int legacyWeapon = 0);
    void load(const Json &saved, int level = 1, int legacyWeapon = 0);
    // Publish a fully prepared restore without repeating source reads. Both
    // instances must share the same immutable catalog; the swaps cannot fail.
    void commitPrepared(Progression &&candidate);
    const ItemDefinition *item(int id) const;
    int level() const;
    int gold() const;
    int quantity(int id) const;
    int equippedWeapon() const;
    int equippedIndex(const std::string &slot) const;
    bool equipped(int inventoryIndex) const;
    CharacterAppearance appearance(Pvf &pvf) const;
    CharacterAppearance appearance(Pvf &pvf, const CharacterCatalog &characters,
                                   CharacterIdentity identity) const;
    int attackBonus() const;
    int defenseBonus() const;
    int experienceToNextLevel() const;
    void addExperience(int amount);
    Operation buy(int shop, int item, int quantity = 1);
    Operation sell(int inventoryIndex, int quantity = 1);
    Operation equip(int inventoryIndex);
    Operation equip(int inventoryIndex, const CharacterDefinition &character);
    Operation equip(int inventoryIndex, const CharacterDefinition &character, const EquipmentSkillContext &normalSkills);
    bool itemUsableBy(int itemId, const CharacterDefinition &character) const;
    Operation unequip(int inventoryIndex);
    Operation repair(int inventoryIndex = -1);
    int repairCost(int inventoryIndex = -1) const;
    void wear(int points = 1);
    Operation usePotion(int inventoryIndex, int64_t nowMs, int currentHp, int maxHp, int currentMp, int maxMp);
    bool questCompleted(int id) const;
    bool questActive(int id) const;
    bool questAvailable(int id) const;
    bool questReady(int id) const;
    Operation acceptQuest(int id, int npc);
    Operation turnInQuest(int id, int npc);
    Operation talkNpc(int npc);
    // Event keys must be stable across room revisits/reloads. Returns false for duplicate events.
    bool recordKill(int dungeon, int monster, int monsterLevel, const std::string &eventKey, uint64_t seed,
                    RandomStreams *randomStreams = nullptr);
    Operation claimDrop(const std::string &eventKey);
    // A duplicate returns false only for the same dungeon/room receipt.
    // Invalid source, corrupted counters/receipt or token reuse throws before
    // publication. Legacy {dungeon,rooms} receipts remain valid and unchanged.
    bool clearDungeon(int dungeon, const std::string &runToken, int roomsCleared);
    bool dungeonClearRecorded(int dungeon, const std::string &runToken, int roomsCleared) const;
    Json availableQuests(int npc) const;
    Json questSummary() const;
    const RegionCatalog &catalog() const { return catalog_; }
};
} // namespace dnf
