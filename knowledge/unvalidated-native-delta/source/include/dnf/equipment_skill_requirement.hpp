#pragma once
#include "character.hpp"

namespace dnf {
class SkillLearningService;
class CharacterSkillState;
// Explicit normal learning authority. Never supply an effective overlay,
// equipment-added level or a manual preview configuration here. The service
// validates the complete normal ledger before accepting a required skill.
struct EquipmentSkillContext {
    const SkillLearningService *learning = nullptr;
    const CharacterSkillState *normal = nullptr;
    int64_t nowMs = 0;
};
struct EquipmentSkillRequirement {
    bool present = false, valid = true;
    int skillId = -1;
    size_t fieldOffset = 0;
    std::string error;
    Json trace = Json::array();
    Json json() const;
};
// Current EQU [required skill] is one exact int32, not an ID/level pair.
// Absent or -1 means no additional permission. Repetitions, nested/mode
// scopes and malformed values fail closed without altering Script/raw data.
EquipmentSkillRequirement parseEquipmentSkillRequirement(const Script &);
// Throws a detailed, source-bound diagnostic before the caller publishes.
// Empty context can accept an unconditioned EQU, never a restricted one.
Json requireEquipmentSkillQualification(const Script &, CharacterIdentity,
    int normalCharacterLevel, const EquipmentSkillContext *context = nullptr);
} // namespace dnf
