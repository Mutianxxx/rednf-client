#pragma once
#include "speed_attributes.hpp"

namespace dnf {
// Reuses the same owned instance/source representation as speed evaluation;
// this evaluator does not infer HP/MP eligibility from a usable speed result.
using EquippedAttributeSource = EquippedSpeedSource;

struct EquipmentResourcePolicy {
    std::string id = "disabled";
    static EquipmentResourcePolicy inferredFlatAndRateV1();
};

struct EquipmentResourceAttributes {
    // A private copy of the pure CHR input, with only HP/MP max replaced.
    // Errors are also appended to adjusted.diagnostics so this copy cannot
    // bypass a rejected wrapper through CharacterBaseAttributes::usable().
    CharacterBaseAttributes adjusted;
    int qualificationLevel = 0;
    std::string policy;
    std::vector<EquippedAttributeSource> equipmentSources;
    Json trace = Json::array(), diagnostics = Json::array();
    bool usable() const;
    Json snapshot(bool includeSource = false) const;
};

// Explicit inferred beta rule: CHR HP/MP + signed integer EQU flat deltas,
// followed by MP * (1 + sum(EQU MP MAX rate) / 100). Every arithmetic stage
// stores float32; integer conversion occurs only at the existing consumer.
// UID ordering is deterministic. Sources, unknowns, repetitions and scopes
// remain owned and traceable. The input must be a pure CHR rebuild; passing
// an already adjusted result is rejected instead of stacking equipment.
//
// Unresolved qualification, resource conditions, sets, avatar choices and
// unknown resource groups fail closed. Broken durable items are inactive;
// a zero source durability is nondurable. This does not derive STR/INT,
// apply the four CHR attack/defense coefficients, grant skills or heal.
EquipmentResourceAttributes evaluateEquipmentResourceAttributes(
    const CharacterBaseAttributes &base, const CharacterDefinition &character,
    const std::vector<EquippedAttributeSource> &equipment, int qualificationLevel,
    const EquipmentResourcePolicy &policy = {});

// Normal level, exact equipped inventory UID and source EQU ownership come
// from progression; base.level may be a separate debug effective level.
EquipmentResourceAttributes evaluateEquipmentResourceAttributes(
    const CharacterBaseAttributes &base, const Progression &progression,
    const CharacterDefinition &character, const EquipmentResourcePolicy &policy = {});
} // namespace dnf
