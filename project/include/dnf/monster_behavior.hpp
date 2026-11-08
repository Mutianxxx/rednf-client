#pragma once
#include "content_profile.hpp"
#include <optional>

namespace dnf {
// Resolving an authored route is separate from compiling/executing its complete
// ACT/ANI dependency closure. An ok route never grants whole-MOB capability.
enum class MonsterActionEngine { None, Act, LegacyAni };
const char *monsterActionEngineName(MonsterActionEngine engine);
struct MonsterActionRoute {
    bool ok = false;
    MonsterActionEngine engine = MonsterActionEngine::None;
    std::string state, selectedTag, literalPath, resolvedPath;
    int sourceActionIndex = 0;
    // source is the exact 5-byte path operand; fieldSource is its 5-byte tag.
    // SourceRef.ordinal is the authored field ordinal for these references.
    SourceRef source, fieldSource, resolvedSource;
    Json allValues = Json::array(), fieldTokens = Json::array();
    // Full fields, including repeated/nested/unknown AI/pattern data, survive
    // even when the simple paired-slot adapter rejects their semantics.
    Json pairedSourceFields = Json::array(), diagnostics = Json::array();
    std::optional<int64_t> cooldownMs;
    std::optional<SourceRef> cooldownSource, attackInfoSource;
    // nullopt = field absent; "" = explicitly authored empty attack-info slot.
    std::optional<std::string> attackInfoLiteral;
    std::string attackInfoResolvedPath;
    Json json() const;
};
// Requests: stay/move/damage1/damage2/down/sit/overturn/jump/death/proc/
// come_in/attack/etc. List indices count every authored value, including empty
// ones. Explicit malformed ACT fields never fall back to legacy ANI.
MonsterActionRoute selectMonsterAction(const Pvf &pvf, const Script &monster,
    const std::string &state, int index = 0);
} // namespace dnf
