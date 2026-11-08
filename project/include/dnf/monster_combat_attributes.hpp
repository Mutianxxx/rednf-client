#pragma once
#include "monster_attributes.hpp"
#include <array>

namespace dnf {
struct MonsterCombatAttributePolicy {
    std::string id = "disabled";
    static MonsterCombatAttributePolicy inferredMobCombatTableV1();
    Json describe() const;
};

struct MonsterCombatAttributeValues {
    // Raw columns 1/2/3/4 map to attack/magicAttack/defense/magicDefense.
    // They are kept separate from equipment values: the annotated sample
    // describes PHYSICAL_ATTACK/DEFENSE as STR/VIT, MAGICAL as INT/SPR.
    // Converting these coefficients into final damage remains a separate rule.
    int physicalAttackCoefficient = 0, magicalAttackCoefficient = 0;
    int physicalDefenseCoefficient = 0, magicalDefenseCoefficient = 0;
    // Raw columns 7/9/8/10. EQUIPMENT_* categories modify this group only.
    int equipmentPhysicalAttack = 0, equipmentMagicalAttack = 0;
    int equipmentPhysicalDefense = 0, equipmentMagicalDefense = 0;
    // Fixed source order: fire, water, dark, light. Signed resistances survive.
    std::array<int, 4> elementalAttack{}, elementalResistance{};
    // slow, freeze, poison, stun, curse, blind, lightning, stone, sleep,
    // burn, weapon break, bleeding, piercing, stuck, confuse, hold, armor break.
    std::array<int, 17> statusResistance{};
    // Neutral defaults are explicit beta policy. Authored nonzero fields whose
    // units/consumers are unresolved reject evaluation instead of being erased.
    double physicalCriticalRate = 0, magicalCriticalRate = 0;
    double hitRateBonus = 0, evasionRateBonus = 0;
    // Distinct from hit/evasion and target stuckbonus: current source raw11
    // grows the attacker's miss percentage under a named inferred policy.
    float tableAttackMissDeltaPercent = 0;
    Json tableAttackMissSource = Json::object();
    double absoluteDamage = 0, flatDamageReduction = 0, absoluteDefenseRate = 0;
    double absoluteDamageResistanceRate = 0, absoluteDefenseIgnoreRate = 0;
    std::array<double,2> damageMissBonusPercent{}; // melee,ranged percentage points
    Json damageMissBonusSource = Json::object();
    Json preserved = Json::object();
    Json snapshot() const;
};

struct MonsterCombatAttributes {
    std::string policy;
    int level = 0;
    bool boss = false;
    std::optional<MonsterCombatAttributeValues> attributes;
    // Owned immutable-source copy retains raw bytes/tokens/unknowns. Default
    // receipts contain references; full source inclusion is opt-in for export.
    MonsterAttributeSource source;
    Json sources = Json::object(), trace = Json::array(), diagnostics = Json::array();
    Json preserved = Json::object();
    bool usable() const { return attributes.has_value(); }
    Json snapshot(bool includeSource = false) const;
};

// Reuses HP evaluator source/24-column/exact-level validation without mutating
// any live HP, returning HP or changing the independent HP policy/authority.
// Each combat group consumes optional own MOB endpoints then ordered category
// modifiers, with binary64 arithmetic and truncation at integer consumers.
// Unsupported material damage inputs fail closed with their source references.
// AI, hit response, motion, difficulty/party/champion and final damage are
// separate capabilities; a usable result does not make the monster complete.
MonsterCombatAttributes evaluateMonsterCombatAttributes(const MonsterAttributeSource &source,
    int level, bool boss, const MonsterCombatAttributePolicy &policy = {});

// Decode a frozen, usable receipt without rerunning endpoint/category/HP
// arithmetic. Validate all typed ranges and current source paths/package/hash;
// reject the whole receipt before a caller publishes any live actor state.
// Trace and unknown metadata survive round trips. Historical actors without a
// combat receipt require their explicit legacy path, never source recomputation.
MonsterCombatAttributes restoreMonsterCombatAttributes(const Json &snapshot,
    const MonsterAttributeSource &expectedSource);
} // namespace dnf
