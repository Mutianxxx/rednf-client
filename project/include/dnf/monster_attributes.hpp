#pragma once
#include "content_profile.hpp"
#include <optional>

namespace dnf {
struct MonsterSpawn;
// MAP [monster] auto-level stores a signed basis-level adjustment. Fixed level
// records store an absolute level. Reject overflow/zero before narrowing.
int resolveMonsterLevel(const MonsterSpawn &spawn, int dungeonBasisLevel);

struct MonsterHpPolicy {
    std::string id = "disabled";
    static MonsterHpPolicy inferredMobTableHpV1();
    Json describe() const;
};

// Immutable source documents retain decrypted bytes, ordered tokens, repeated
// fields and unknowns. An Actor stores only the evaluated receipt; source
// documents remain content-bound and must not be reconstructed from that receipt.
struct MonsterAttributeSource {
    Script monster, table;
    std::string tableSelection;
    Json diagnostics = Json::array();
};
struct MonsterHpResult {
    std::string policy;
    int level = 0;
    bool boss = false;
    std::optional<int> hp;
    Json sources = Json::object(), trace = Json::array(), diagnostics = Json::array();
    bool usable() const { return hp.has_value(); }
    Json snapshot() const;
};

// Normal/boss comes from the MAP spawn role, never a resource filename. Source
// [ability table] 1 selects summon unless the explicit boss role selects boss;
// 2 is outside this PvE adapter. [base table] is an explicit source override.
MonsterAttributeSource readMonsterAttributeSource(const Pvf &pvf,
    const std::string &monsterPath, bool boss);

// Named beta inference: source 24-integer table (level, four combat columns,
// HP in column 5), optional MOB HP endpoint override, then ordered HP category
// modifiers. Table levels require an exact match; endpoint interpolation clamps
// only the endpoint range. Positive HP truncates at each integer consumer.
// Difficulty/party/named/champion selection and native PC final parity remain
// separate capabilities. This adapter does not invent their multipliers.
MonsterHpResult evaluateMonsterHp(const MonsterAttributeSource &source,
    int level, bool boss, const MonsterHpPolicy &policy = {});
} // namespace dnf
