#pragma once
#include "combat_attributes.hpp"
#include "monster_combat_attributes.hpp"
#include "simulation.hpp"
#include <optional>

namespace dnf {
enum class DamageAttackType { Physical, Magical, IgnoreDefense, Weapon };
const char *damageAttackTypeName(DamageAttackType type);
enum class DamageTargetCategory { Unknown, Human, Fort, Monster };
const char *damageTargetCategoryName(DamageTargetCategory category);

// Dungeon selection only. Enum tags may be separate type-5 fields in the PVF;
// [damage] after [damage reaction] is not the numeric base damage operand.
struct AttackDamageDefinition {
    Script source;
    std::optional<DamageAttackType> type;
    float baseDamage = 0, absoluteDamage = 0, bonusPercent = 0;
    bool weaponDamageApply = false, ignoreDefense = false;
    int element = 4; // fire/water/dark/light/no element
    float criticalBonusPercent = 0, missDeltaPercent = 0;
    // Percentage operands: human armor, fort armor, and no armor category.
    // They survive skill coefficient replacement and retain ATK provenance.
    std::array<float,3> targetCategoryPercent{{100,100,100}};
    Json trace = Json::array(), diagnostics = Json::array();
    bool usable() const;
    Json snapshot(bool includeSource = false) const;
};
// Opt-in requires the caller to actually execute the named status service in
// the same HP/RNG transaction. The default pure-damage reader still rejects
// authored non-neutral statuses rather than silently dropping their behavior.
enum class AttackStatusConsumer { None, StunHostV1 };
AttackDamageDefinition readAttackDamage(const Script &source,
    AttackStatusConsumer statusConsumer = AttackStatusConsumer::None);

struct DamageResolutionPolicy {
    std::string id = "disabled";
    Script damageConstants;
    bool randomVariation = true, rollCritical = true, rollHit = true;
    // Explicit rednf cross-version inference, not unexplained PVF defaults.
    float baseCriticalPercent = 3, criticalMultiplier = 1.5f;
    float minimumDefenseMultiplier = 0.01f, ignoreDefenseRandomRate = 0.07f;
    static DamageResolutionPolicy inferredPveDamageV1(const Script &constants);
    Json describe() const;
};

// Immutable inputs for one attacker/target pair. HP ownership stays in World.
// Primary stats, equipment attack and final defense are deliberately distinct.
enum class DamageContactRange { Unknown, Melee, Ranged };
const char *damageContactRangeName(DamageContactRange);
struct DamageCombatant {
    std::string packageIdentity, adapter;
    int level = 0;
    DamageTargetCategory targetCategory = DamageTargetCategory::Unknown;
    float strength = 0, intelligence = 0;
    float physicalAttack = 0, magicalAttack = 0;
    float physicalDefense = 0, magicalDefense = 0;
    float independentAttack = 0, independentRate = 1;
    float physicalAbsoluteDamage = 0, magicalAbsoluteDamage = 0;
    float physicalAbsoluteDefensePercent = 0, magicalAbsoluteDefensePercent = 0;
    float physicalCriticalBonusPercent = 0, magicalCriticalBonusPercent = 0;
    float attackMissDeltaPercent = 0, evasionPercent = 0;
    std::array<float,2> damageMissBonusPercent{}; // target melee,ranged defense
    Json damageMissBonusSource = Json::object();
    std::array<float,4> elementalAttack{}, elementalResistance{};
    int weaponElement = 4;
    Json sources = Json::object(), trace = Json::array(), diagnostics = Json::array();
    bool usable() const;
    Json snapshot() const;
};
DamageCombatant makeDamageCombatant(const CombatAttributeSnapshot &attributes);
DamageCombatant makeDamageCombatant(const MonsterCombatAttributes &attributes,
    const DamageResolutionPolicy &policy);
// Species [human] is not [human armor]. An explicitly unknown/conflicting
// armor class stays Unknown and blocks nonneutral target-category rates.
// The adapter fallback is used only when no armor class is authored.
void bindDamageTargetCategory(DamageCombatant &target,const Script &source,
    DamageTargetCategory inferredFallback);

struct DamageSkillModifiers {
    // ((ATK base + eligible equipment attack * attackMultiplier) * percent/100
    //  + (fixedDamage + independentAttack * independentPercent/100) * independentRate)
    // then ATK bonus and primary-stat amplification. Mapping SKL columns into
    // these units is the controller's separately evidenced responsibility.
    float percent = 100, fixedDamage = 0, independentPercent = 0;
    float attackMultiplier = 1, primaryStatBonus = 0, totalMultiplier = 1;
    // Applies only after an actual successful critical roll, never to normal
    // hits. A skill buff must not increase damage before critical selection.
    float criticalMultiplier = 1;
    // Explicit controller setAttackInfo-style replacement: omit ATK base and
    // bonus, use the selected skill percent/fixed once. Type, absolute damage,
    // weapon application and elements still come from ATK. False composes the
    // source ATK with the supplied multipliers, including ordinary attacks.
    bool replacesAttackCoefficients = false;
    Json sources = Json::array();
    Json snapshot() const;
};
struct DamageRequest {
    EntityHandle attacker, target;
    uint64_t attackInstance = 0;
    uint32_t hitIndex = 0;
    DamageCombatant attackerStats, targetStats;
    AttackDamageDefinition attack;
    DamageSkillModifiers skill;
    // Required only when ATK authors [weapon]. Must come from the controller's
    // qualified weapon source; there is no inferred universal physical default.
    std::optional<DamageAttackType> weaponType;
    DamageContactRange contactRange = DamageContactRange::Unknown;
    Json contactRangeSource = Json::object();
};
// Reads only explicit passive-object category [melee]/[bullet]. Conflicting,
// missing or malformed categories keep Unknown; physical/magical is independent.
void bindDamageContactRange(DamageRequest &,const Script &object);
struct DamageResolution {
    std::string policy;
    EntityHandle attacker, target;
    uint64_t attackInstance = 0;
    uint32_t hitIndex = 0;
    std::optional<int> hpDamage; // present zero is an accepted miss
    bool missed = false, critical = false;
    Json trace = Json::array(), diagnostics = Json::array(), sources = Json::object();
    bool usable() const { return hpDamage.has_value(); }
    Json snapshot() const;
};

// Side-effect free except for successful RNG publication. Invalid inputs or
// arithmetic overflow leave the supplied stream unchanged. An accepted miss
// commits its hit roll. Attack-cycle/target deduplication and protection belong
// to World; this service neither rewrites HP nor claims those capabilities.
DamageResolution resolveDamage(const DamageRequest &request,
    const DamageResolutionPolicy &policy = {}, Pcg32 *combatRandom = nullptr);
} // namespace dnf
