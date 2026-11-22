#pragma once
#include "character.hpp"
#include "content_profile.hpp"
#include <map>

namespace dnf {
// These names refer to CHR source fields. In particular, the four attack and
// defense coefficients are not final damage/defense or a proven STR/INT map.
enum class ChrAttribute {
    HpMax, MpMax, PhysicalAttack, PhysicalDefense, MagicalAttack, MagicalDefense,
    HpRegenSpeed, MpRegenSpeed, MoveSpeed, AttackSpeed, CastSpeed, HitRecovery,
    JumpPower, JumpSpeed, InventoryLimit, Weight,
    FireResistance, WaterResistance, DarkResistance, LightResistance
};
const char *chrAttributeName(ChrAttribute attribute);
const char *chrAttributeTag(ChrAttribute attribute);

enum class CharacterAttributeState { Value, Absent, ExplicitEmpty, Ambiguous, Malformed };
struct CharacterAttributeValue {
    CharacterAttributeState state = CharacterAttributeState::Absent;
    float value = 0;
    std::string unit;
    // Complete source candidates, selection decisions and float32 additions.
    Json trace = Json::array();
    bool usable() const { return state == CharacterAttributeState::Value; }
    // The consumer boundary only: no per-level integer truncation. Rejects
    // nonfinite/out-of-range values instead of overflowing or clamping.
    int integer() const;
    Json snapshot() const;
};

struct CharacterGrowthPolicy {
    // Default construction deliberately does not opt normal gameplay in.
    std::string id = "disabled";
    static CharacterGrowthPolicy inferredChrGrowthV1();
};

struct CharacterBaseAttributes {
    CharacterIdentity identity;
    int level = 0;
    std::string policy;
    std::map<ChrAttribute, CharacterAttributeValue> attributes;
    Json source = Json::object(), selectedBlocks = Json::array(), diagnostics = Json::array();
    bool usable() const;
    const CharacterAttributeValue &at(ChrAttribute attribute) const;
    float value(ChrAttribute attribute) const;
    int integer(ChrAttribute attribute) const;
    Json snapshot() const;
};

// Explicit beta policy, not the native final stat formula:
//  * exact-1031 identity g -> authored [growtype g+1], separate initial block;
//  * selected branch delta applies retroactively for levels 2..level;
//  * awakening fields replace branch deltas, absent fields inherit branch;
//  * absent branch deltas are zero, explicit empty/duplicate/bad fields block;
//  * each level adds in float32; integer conversion occurs only at a consumer.
// This does not authorize an advancement/awakening, grant skills, apply EQU,
// derive STR/INT/VIT/SPR, convert speed to motion, or calculate final damage.
CharacterBaseAttributes buildCharacterBaseAttributes(const CharacterDefinition &definition,
    CharacterIdentity identity, int level, const CharacterGrowthPolicy &policy = {});
} // namespace dnf
