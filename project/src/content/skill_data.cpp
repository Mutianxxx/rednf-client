#include "dnf/skill_data.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
bool supportedMode(const std::string &mode) {
    return mode == "common" || mode == "dungeon" || mode == "pvp" ||
        mode == "warroom" || mode == "death tower";
}
std::optional<int> nonnegativeInteger(const Json &value) {
    if (!value.is_number_integer() || (value.is_number_unsigned() &&
        value.get<uint64_t>() > uint64_t(std::numeric_limits<int>::max()))) return {};
    const auto number = value.get<int64_t>();
    if (number < 0 || number > std::numeric_limits<int>::max()) return {};
    return int(number);
}
} // namespace

SkillSourceData readSkillSourceData(const CharacterSkillDefinition &definition, const std::string &mode) {
    SkillSourceData result;
    result.definition = definition;
    result.mode = normalize(mode);
    if (!supportedMode(result.mode)) throw std::invalid_argument("Unknown skill data mode: " + mode);
    auto select = [&](const std::string &tag, bool modeOverride) {
        const ScopedSkillField *field = nullptr;
        auto find = [&](const std::string &scope) {
            const auto matches = definition.fieldsInScope(tag, scope);
            if (matches.size() > 1) {
                result.ambiguousFields.insert(normalize(tag));
                Json candidates = Json::array();
                for (const auto *match : matches)
                    candidates.push_back({{"ordinal", match->ordinal}, {"offset", match->field.offset},
                        {"values", match->field.values}});
                result.issues.push_back({{"kind", "repeated_selected_skill_field"}, {"tag", tag},
                    {"scope", scope}, {"candidates", candidates}});
                return false;
            }
            if (!matches.empty()) field = matches.front();
            return true;
        };
        if (modeOverride && result.mode != "common" && !find(result.mode)) return;
        if (!field && !find("common")) return;
        if (field) result.selected.emplace(normalize(tag), SkillDataField{field->field, field->scope, field->ordinal});
    };
    for (const auto *tag : {"[name]", "[type]", "[command]", "[maximum level]", "[growtype maximum level]",
             "[required level]", "[required level range]", "[skill fitness growtype]"}) select(tag, false);
    // These fields are explicitly mode-dependent in the supplied SKL module
    // separation sample. Unknown fields remain lossless in definition.source.
    for (const auto *tag : {"[consume MP]", "[cool time]", "[casting time]", "[static data]",
             "[level info]", "[start cool time]"}) select(tag, true);
    return result;
}
Json SkillSourceData::values(const std::string &tag) const {
    if (ambiguousFields.count(normalize(tag))) return Json::array();
    const auto found = selected.find(normalize(tag));
    return found == selected.end() ? Json::array() : found->second.field.values;
}
std::string SkillSourceData::name() const {
    const auto value = values("[name]");
    if (value.size() != 1 || !value[0].is_string()) return {};
    return value[0].get<std::string>();
}
std::optional<double> SkillSourceData::firstNumber(const std::string &tag) const {
    if (ambiguousFields.count(normalize(tag))) return {};
    const auto value = values(tag);
    if (value.empty() || !value[0].is_number()) return {};
    const double number = value[0].get<double>();
    return std::isfinite(number) ? std::optional<double>(number) : std::nullopt;
}
std::optional<int> SkillSourceData::purchaseMaximum(int growtype) const {
    if (ambiguousFields.count("[growtype maximum level]")) return {};
    const auto values = this->values("[growtype maximum level]");
    if (growtype < 0 || size_t(growtype) >= values.size()) return {};
    return nonnegativeInteger(values[size_t(growtype)]);
}
Json SkillSourceData::snapshot(bool includeSource) const {
    Json fields = Json::array();
    for (const auto &entry : selected) fields.push_back({{"tag", entry.second.field.tag},
        {"scope", entry.second.scope}, {"offset", entry.second.field.offset},
        {"ordinal", entry.second.ordinal}, {"values", entry.second.field.values}});
    return {{"source", definition.snapshot(includeSource)}, {"mode", mode}, {"selected_fields", fields},
        {"ambiguous_fields", ambiguousFields}, {"issues", issues},
        {"scope", "Source selection only; initial endpoints are not final consumption, cooldown or damage formulas"}};
}
std::optional<double> skillLevelValue(const Json &table, int level, int column) {
    if (level <= 0 || column < 0 || !table.is_array() || table.empty()) return {};
    const auto width = nonnegativeInteger(table[0]);
    if (!width || *width == 0 || column >= *width) return {};
    const size_t columns = size_t(*width), cells = table.size() - 1;
    if (cells % columns || size_t(level) > cells / columns) return {};
    const auto &value = table[1 + (size_t(level) - 1) * columns + size_t(column)];
    if (!value.is_number()) return {};
    const double number = value.get<double>();
    return std::isfinite(number) ? std::optional<double>(number) : std::nullopt;
}
} // namespace dnf
