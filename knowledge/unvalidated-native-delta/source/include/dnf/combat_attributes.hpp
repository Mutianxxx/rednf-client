#pragma once
#include "equipment_skill_requirement.hpp"
#include "equipment_attributes.hpp"
#include <array>

namespace dnf {
struct CombatAttributePolicy {
    std::string id = "disabled";
    // Explicit inferred VIT/SPR conversion. The factors are selected from
    // positions 22/23 of this source's [damage fomula constant], not literals.
    // This does not claim that the PC consumer of those positions is known.
    bool derivePrimaryDefense = true;
    Script damageConstants;
    static CombatAttributePolicy inferredEquipmentCombatStatV1(const Script &damageConstants);
};

struct CombatAttributeSnapshot {
    CharacterIdentity identity;
    int level = 0, qualificationLevel = 0;
    std::string policy;
    // The owned input remains a pure CHR result; no coefficient is rewritten.
    CharacterBaseAttributes pureChr;
    Script damageConstants;
    float strength = 0, vitality = 0, intelligence = 0, spirit = 0;
    // Equipment base attack, before main-stat/skill/mastery amplification.
    float physicalAttack = 0, magicalAttack = 0;
    float equipmentPhysicalDefense = 0, equipmentMagicalDefense = 0;
    float physicalDefense = 0, magicalDefense = 0;
    float vitalityDefenseFactor = 0, spiritDefenseFactor = 0;
    float independentAttack = 0, independentRate = 1;
    float physicalAbsoluteDamage = 0, magicalAbsoluteDamage = 0;
    float physicalAbsoluteDefensePercent = 0, magicalAbsoluteDefensePercent = 0;
    // Equipment increments only. A rule's base critical chance is separate.
    float physicalCriticalBonusPercent = 0, magicalCriticalBonusPercent = 0;
    // EQU [stuck] +1 increases attack miss by one percentage point; it is
    // neither defense evasion nor a per-mille value.
    float attackMissDeltaPercent = 0, evasionPerMille = 0;
    // Fire, water, dark, light. CHR resistance and eligible EQU are separate
    // from the later damage rule's effective-element conversion.
    std::array<float,4> elementalAttack{}, elementalResistance{};
    // 4 means no element; different authored weapon elements are rejected.
    int weaponElement = 4;
    std::vector<EquippedAttributeSource> equipmentSources;
    Json trace = Json::array(), diagnostics = Json::array(), policyDetails = Json::object();
    bool usable() const;
    Json snapshot(bool includeSource = false) const;
};

// Named beta inference, not a native final damage formula. UID-ordered EQU
// integer flats add to inferred CHR primary-stat units; all four equipment
// attack/defense pairs select PvE index 0 while preserving index 1. Each
// arithmetic stage stores float32. Sets, unresolved qualifications, conditional
// combat effects and unconsumed material combat groups block publication.
// HP/MP and speed tags remain delegated to their existing typed evaluators.
CombatAttributeSnapshot evaluateCombatAttributes(const CharacterBaseAttributes &base,
    const CharacterDefinition &character, const std::vector<EquippedAttributeSource> &equipment,
    int qualificationLevel, const CombatAttributePolicy &policy = {}, const EquipmentSkillContext *normalSkills = nullptr);
CombatAttributeSnapshot evaluateCombatAttributes(const CharacterBaseAttributes &base,
    const Progression &progression, const CharacterDefinition &character,
    const CombatAttributePolicy &policy = {}, const EquipmentSkillContext *normalSkills = nullptr);
} // namespace dnf
