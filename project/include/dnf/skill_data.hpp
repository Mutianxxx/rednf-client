#pragma once
#include "character.hpp"
#include <optional>
#include <set>

namespace dnf {
// A selected field remains a reference to its exact source scope/offset. An
// explicit empty mode override is different from an absent override.
struct SkillDataField {
    Field field;
    std::string scope;
    size_t ordinal = 0;
};
struct SkillSourceData {
    CharacterSkillDefinition definition;
    std::string mode;
    std::map<std::string, SkillDataField> selected;
    std::set<std::string> ambiguousFields;
    Json issues = Json::array();
    Json values(const std::string &tag) const;
    std::string name() const;
    // Preserves both authored endpoints. This accessor is deliberately only
    // the first numeric value, not interpolation or final MP/CD calculation.
    std::optional<double> firstNumber(const std::string &tag) const;
    std::optional<int> purchaseMaximum(int growtype) const;
    Json snapshot(bool includeSource = false) const;
};
// Mode-specific SKL parameter fields override common only when present. Other
// metadata remains common. Repeated selected fields fail instead of choosing
// the first value; full source data remains in CharacterCatalog.
SkillSourceData readSkillSourceData(const CharacterSkillDefinition &definition,
                                   const std::string &mode = "dungeon");
// Exact level-info table lookup. Level 0 is unlearned; malformed dimensions,
// truncated rows, out-of-range levels/columns and nonnumeric cells have no value.
// No modifier chain, column meaning or native final formula is inferred.
std::optional<double> skillLevelValue(const Json &table, int level, int column);
} // namespace dnf
