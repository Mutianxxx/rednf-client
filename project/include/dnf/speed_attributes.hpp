#pragma once
#include "attributes.hpp"

namespace dnf {
class Progression;
struct EquippedSpeedSource {
    int64_t instanceUid = 0;
    std::string equippedSlot;
    int currentDurability = 0;
    // Owned immutable source copy, including raw bytes, tokens and unknowns.
    Script source;
};
struct CharacterSpeedPolicy {
    std::string id = "disabled";
    static CharacterSpeedPolicy inferredFlatEquipmentV1();
};
struct CharacterSpeeds {
    CharacterIdentity identity;
    int level = 0;
    // Effective level used for the CHR base and the normal progression level
    // used for EQU qualification may differ during an isolated debug override.
    int qualificationLevel = 0;
    std::string policy;
    // Absolute 1000-based values. EQU 20 is +20 points (2 percentage
    // points), not *1.20. Combining this group with CHR is inferred.
    float attackPerMille = 0, castPerMille = 0, movePerMille = 0;
    // Independent dimensionless dash factors. Normal is 1, source +0.5
    // yields 1.5. They are not included again in movePerMille.
    float dashXRatio = 1, dashYRatio = 1;
    std::vector<EquippedSpeedSource> equipmentSources;
    Json baseSource = Json::object(), trace = Json::array(), diagnostics = Json::array();
    bool usable() const;
    Json snapshot(bool includeSource = false) const;
};
// All candidates are preserved. Ambiguous/empty/malformed recognized fields,
// invalid instance ownership/qualification and unsupported speed semantics
// block the result. Broken durable items contribute no speed under this
// named inferred policy; zero-max-durability items are not treated as broken.
// This does not choose action speed, convert to pixels/sec or ANI percent,
// mutate animation delays, infer STR/INT, or register a playable controller.
CharacterSpeeds evaluateCharacterSpeeds(const CharacterBaseAttributes &base,
    const CharacterDefinition &character, const std::vector<EquippedSpeedSource> &equipment,
    const CharacterSpeedPolicy &policy = {});
// Explicitly separates the level used to evaluate base attributes from the
// normal level ledger used to qualify equipment. This is for test/debug
// overlays and must not mutate normal progression or skill ledgers.
CharacterSpeeds evaluateCharacterSpeeds(const CharacterBaseAttributes &base,
    const CharacterDefinition &character, const std::vector<EquippedSpeedSource> &equipment,
    int qualificationLevel, const CharacterSpeedPolicy &policy);
// Resolves equipped slots by exact inventory UID, with no appearance/default
// costume lookup. Unknown definitions and malformed ownership fail closed.
CharacterSpeeds evaluateCharacterSpeeds(const CharacterBaseAttributes &base,
    const Progression &progression, const CharacterDefinition &character,
    const CharacterSpeedPolicy &policy = {});
} // namespace dnf
