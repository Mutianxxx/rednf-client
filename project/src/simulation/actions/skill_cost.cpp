#include "dnf/skill_cost.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
const char *skillCostAbsencePolicyName(SkillCostAbsencePolicy policy) {
    switch (policy) {
    case SkillCostAbsencePolicy::Strict: return "strict";
    case SkillCostAbsencePolicy::Inferred1031OptionalFieldsV1: return "1031-optional-cost-fields-v1";
    }
    throw std::runtime_error("Invalid skill cost absence policy");
}
const char *skillNumericStateName(SkillNumericState state) {
    switch (state) {
    case SkillNumericState::Absent: return "Absent";
    case SkillNumericState::ExplicitEmpty: return "ExplicitEmpty";
    case SkillNumericState::Value: return "Value";
    case SkillNumericState::Ambiguous: return "Ambiguous";
    case SkillNumericState::Malformed: return "Malformed";
    }
    throw std::runtime_error("Invalid skill numeric state");
}
Json SkillNumericResult::json() const {
    return {{"state", skillNumericStateName(state)}, {"value", value ? Json(*value) : Json()},
        {"trace", trace}, {"diagnostics", diagnostics}};
}
std::optional<int> SkillCostResult::consumeMp() const {
    if (!mp.usable() || !std::isfinite(*mp.value) || *mp.value < 0 ||
        *mp.value != std::trunc(*mp.value) || *mp.value > double(std::numeric_limits<int>::max())) return {};
    return int(*mp.value);
}
std::optional<double> SkillCostResult::cooldownMs() const {
    return cooldown.usable() && std::isfinite(*cooldown.value) && *cooldown.value >= 0 ? cooldown.value : std::nullopt;
}
Json SkillCostResult::json() const {
    return {{"key", key.json()}, {"effective_level", effectiveLevel}, {"mp", mp.json()}, {"cooldown_ms", cooldown.json()},
        {"absence_policy", skillCostAbsencePolicyName(absencePolicy)},
        {"consumer_diagnostics", consumerDiagnostics},
        {"adapter", "skl-maximum-level-endpoints-v1"}, {"classification", "inferred_beta"},
        {"limitations", "Numeric endpoint evaluation only; callers supply actual weapon/command/state modifiers and transaction timing"}};
}
namespace {
SourceRef documentRef(const SkillSourceData &data) {
    const auto &source = data.definition.source;
    SourceRef result;
    result.packageIdentity = source.provenance.value("package_identity", std::string());
    result.memberPath = source.script.path;
    result.memberSha256 = source.provenance.value("member_sha256", std::string());
    if (result.memberSha256.empty()) result.memberSha256 = sha256(source.bytes);
    result.literalPath = source.provenance.value("literal_path", source.script.path);
    result.byteLength = source.bytes.size(); result.scope = "document";
    return result;
}
SourceRef fieldRef(const SkillSourceData &data, const SkillDataField &field) {
    const auto &source = data.definition.source;
    SourceRef result;
    result.packageIdentity = source.provenance.value("package_identity", std::string());
    result.memberPath = source.script.path;
    result.memberSha256 = source.provenance.value("member_sha256", std::string());
    if (result.memberSha256.empty()) result.memberSha256 = sha256(source.bytes);
    result.byteOffset = field.field.offset; result.ordinal = field.ordinal; result.scope = field.scope;
    result.literalPath = source.provenance.value("literal_path", source.script.path);
    // The next authored field bounds this field; retain all unknown fields in
    // the original definition instead of counting only selected parameters.
    size_t end = source.bytes.size();
    for (const auto &candidate : data.definition.fields)
        if (candidate.field.offset > field.field.offset) end = std::min(end, candidate.field.offset);
    result.byteLength = end > result.byteOffset ? end - result.byteOffset : 0;
    return result;
}
Json endpointEvidence() {
    return Json::array({
        {{"kind", "user_supplied_sample"}, {"path", "pvf官方文档/sample(官方注释)/skillsample.skl"},
         {"sha256", "7fdee848bf585a7a638f204c16dd6da4d5efc63f79f8087371e4ba41dd78e9e1"},
         {"lines", Json::array({36,37,58,85,86})}, {"encoding", "CP949"},
         {"meaning", "maximum level is highest by all means; growtype maximum is purchase ceiling; MP/CD are Lv1/highest endpoints, CD in ms"}},
        {{"kind", "user_supplied_sample"}, {"path", "pvf官方文档/sample(官方注释)/charactersample.chr"},
         {"sha256", "1424287bf56c2fa6465c7e9ca0388303f34117ab28cfb173162811de9e349cfb"},
         {"lines", Json::array({349,350,351,352,353,354,355,356})}, {"encoding", "CP949"},
         {"meaning", "[weapon skill info] rows contain physical MP, physical CD, magical MP and magical CD ratios by subtype"}},
        {{"kind", "user_supplied_sample"}, {"path", "pvf官方文档/sample(官方注释)/skillsample.skl"},
         {"sha256", "7fdee848bf585a7a638f204c16dd6da4d5efc63f79f8087371e4ba41dd78e9e1"},
         {"lines", Json::array({110})}, {"encoding", "CP949"},
         {"meaning", "[skill command advantage] values are cooldown and MP reductions in 0.1 percent units"}},
        {{"kind", "inferred_beta_policy"}, {"path", "dnf-native-build-plan/appendices/recommended-decisions.md"},
         {"decisions", Json::array({"D03", "D04"})},
         {"meaning", "Linear endpoint interpolation/clamp; ordered modifiers; final positive MP truncation; preserve cooldown milliseconds"}}
    });
}
Json absencePolicyTrace(const SkillSourceData &source, const std::string &tag,
                       const std::string &scope, const Json &replacement, SkillCostAbsencePolicy policy) {
    return {{"stage", "optional_field_absence_policy"}, {"policy", skillCostAbsencePolicyName(policy)},
        {"classification", "inferred_beta"}, {"native_default_confirmed", false},
        {"absent_tag", tag}, {"selected_scope", scope}, {"source_state", "Absent"},
        {"field_was_present", false}, {"replacement", replacement},
        {"source_ref_kind", "document"}, {"source", documentRef(source).json()},
        {"evidence", Json::array({
            {{"kind", "current_source_corpus"},
             {"reference_pvf_sha256", "d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d"},
             {"observations", Json::array({
                 {{"member_path", "skill/swordman/jumpattackmulti.skl"}, {"absent", "[cool time]"},
                  {"present", Json::array({"[consume MP]", "[weapon effect type]"})}},
                 {{"member_path", "skill/swordman/khazan.skl"}, {"absent", "[weapon effect type]"},
                  {"present", Json::array({"[consume MP]", "[cool time]"})}},
                 {{"member_path", "skill/swordman/guard.skl"}, {"absent", "[weapon effect type]"},
                  {"present", Json::array({"[consume MP]", "[cool time]"})}}
             })}},
            {{"kind", "user_supplied_sample"}, {"path", "pvf官方文档/sample(官方注释)/skillsample.skl"},
             {"sha256", "7fdee848bf585a7a638f204c16dd6da4d5efc63f79f8087371e4ba41dd78e9e1"},
             {"lines", Json::array({85,86,93})}, {"encoding", "CP949"},
             {"meaning", "Documents cooldown endpoints and none/physical/magical choices; does not prove an absent-field native default"}},
            {{"kind", "inferred_beta_policy"},
             {"meaning", "Current 1031 optional absence only: no cooldown or no weapon scaling; MP stays required. Empty, repeated and malformed fields remain blocked"},
             {"unverified", "Native absence consumers are not recovered; revalidate this opt-in policy when changing content versions"}}
        })}};
}
SkillNumericState inspect(const SkillSourceData &source, const std::string &tag, const SkillDataField *&field) {
    const auto key = normalize(tag); field = nullptr;
    if (source.ambiguousFields.count(key)) return SkillNumericState::Ambiguous;
    auto found = source.selected.find(key);
    if (found == source.selected.end()) return SkillNumericState::Absent;
    field = &found->second;
    return field->field.values.empty() ? SkillNumericState::ExplicitEmpty : SkillNumericState::Value;
}
SkillNumericResult evaluate(const SkillSourceData &source, const std::string &tag, int level,
                           const std::vector<SkillCostModifier> &modifiers, bool integerMp, bool finalizeMp = true,
                           SkillCostAbsencePolicy absencePolicy = SkillCostAbsencePolicy::Strict) {
    SkillNumericResult result;
    const SkillDataField *field = nullptr;
    result.state = inspect(source, tag, field);
    if (field) result.trace.push_back({{"stage", "source_endpoints"}, {"tag", tag},
        {"source", fieldRef(source, *field).json()}, {"values", field->field.values}});
    auto malformed = [&](const std::string &reason) {
        result.state = SkillNumericState::Malformed; result.value.reset();
        result.diagnostics.push_back({{"kind", "numeric_adapter_blocked"}, {"tag", tag}, {"reason", reason}});
    };
    double value = 0;
    if (result.state != SkillNumericState::Value) {
        result.diagnostics.push_back({{"kind", "source_field_unavailable"}, {"tag", tag},
            {"state", skillNumericStateName(result.state)}});
        if (result.state != SkillNumericState::Absent || tag != "[cool time]" ||
            absencePolicy != SkillCostAbsencePolicy::Inferred1031OptionalFieldsV1) return result;
        if (level < 1) { malformed("Effective skill level is unlearned or invalid"); return result; }
        result.state = SkillNumericState::Value;
        result.trace.push_back(absencePolicyTrace(source, tag, source.mode, 0, absencePolicy));
    } else {
    const auto &values = field->field.values;
    if (values.size() != 2 || !values[0].is_number() || !values[1].is_number()) {
        malformed("Expected exactly two numeric authored endpoints"); return result;
    }
    const double low = values[0].get<double>(), high = values[1].get<double>();
    if (!std::isfinite(low) || !std::isfinite(high) || low < 0 || high < 0) {
        malformed("Endpoint costs must be finite and nonnegative"); return result;
    }
    const SkillDataField *maximum = nullptr;
    const auto maximumState = inspect(source, "[maximum level]", maximum);
    if (maximumState != SkillNumericState::Value) {
        malformed("Endpoint range N is " + std::string(skillNumericStateName(maximumState)) +
            "; an explicit source-field adapter is required; purchase ceiling/table length is not a fallback");
        return result;
    }
    const auto &maximumValues = maximum->field.values;
    if (maximum->scope != "common" || maximumValues.size() != 1 || !maximumValues[0].is_number_integer() ||
        (maximumValues[0].is_number_unsigned() && maximumValues[0].get<uint64_t>() > uint64_t(std::numeric_limits<int>::max()))) {
        malformed("Endpoint range requires one common integral [maximum level]"); return result;
    }
    const auto last = maximumValues[0].get<int64_t>();
    if (last < 1 || last > std::numeric_limits<int>::max()) {
        malformed("Endpoint range [maximum level] must be positive and representable"); return result;
    }
    result.trace.push_back({{"stage", "endpoint_range_adapter"}, {"adapter", "skl-maximum-level-endpoints-v1"},
        {"classification", "inferred_beta"}, {"first_level", 1}, {"last_level", last},
        {"source", fieldRef(source, *maximum).json()}, {"evidence", endpointEvidence()}});
    if (level < 1) { malformed("Effective skill level is unlearned or invalid"); return result; }
    const int bounded = std::min(level, int(last));
    const double ratio = last == 1 ? 0 : double(bounded - 1) / double(last - 1);
    value = low + (high - low) * ratio;
    result.trace.push_back({{"stage", "linear_endpoints"}, {"effective_level", level}, {"bounded_level", bounded},
        {"ratio", ratio}, {"low", low}, {"high", high}, {"result", value}});
    if (level > last) result.diagnostics.push_back({{"kind", "level_clamped_to_source_endpoint_range"},
        {"effective_level", level}, {"source_maximum", last}});
    if (last == 1 && low != high) result.diagnostics.push_back({{"kind", "single_level_conflicting_endpoints"},
        {"selected", "first_endpoint"}, {"discarded_high_for_evaluation", high}});
    }
    for (const auto &modifier : modifiers) {
        if (modifier.id.empty() || modifier.evidence.empty() || !std::isfinite(modifier.multiply) ||
            !std::isfinite(modifier.add) || modifier.multiply < 0) {
            malformed("Modifier requires stable identity, evidence, finite nonnegative multiplier and finite additive value"); return result;
        }
        const double before = value;
        value = value * modifier.multiply + modifier.add;
        result.trace.push_back({{"stage", "modifier"}, {"id", modifier.id}, {"classification", "inferred_beta"},
            {"before", before}, {"multiply", modifier.multiply}, {"add", modifier.add}, {"result", value},
            {"source", modifier.source.json()}, {"evidence", modifier.evidence}});
        if (!std::isfinite(value)) { malformed("Modifier overflowed the finite numeric domain"); return result; }
    }
    const double modifiedValue = value;
    const double positive = finalizeMp ? std::max(0.0, modifiedValue) : modifiedValue;
    if (integerMp && finalizeMp) {
        if (std::trunc(positive) > double(std::numeric_limits<int>::max())) { malformed("Final MP exceeds the integer consumer range"); return result; }
        value = std::trunc(positive);
    } else value = positive;
    result.trace.push_back({{"stage", integerMp ? (finalizeMp ? "positive_truncate_final_mp" : "defer_final_mp_rounding") : "preserve_source_milliseconds"},
        {"before", modifiedValue}, {"nonnegative_input", positive}, {"result", value}, {"unit", integerMp ? "MP" : "ms"}});
    result.value = value;
    return result;
}
}
SkillCostResult evaluateSkillCosts(const SkillSourceData &source, int effectiveLevel,
    const std::vector<SkillCostModifier> &mpModifiers, const std::vector<SkillCostModifier> &cooldownModifiers,
    SkillCostAbsencePolicy absencePolicy) {
    SkillCostResult result; result.key = source.definition.key; result.effectiveLevel = effectiveLevel;
    result.absencePolicy = absencePolicy;
    result.mp = evaluate(source, "[consume MP]", effectiveLevel, mpModifiers, true);
    result.cooldown = evaluate(source, "[cool time]", effectiveLevel, cooldownModifiers, false, true, absencePolicy);
    return result;
}
namespace {
struct CharacterFieldSelection { SkillNumericState state = SkillNumericState::Absent; const Field *field = nullptr; size_t ordinal = 0; };
CharacterFieldSelection characterField(const CharacterScript &source, const std::string &tag) {
    CharacterFieldSelection out; const auto key = normalize(tag);
    for (size_t i = 0; i < source.script.fields.size(); ++i) {
        const auto &field = source.script.fields[i]; if (normalize(field.tag) != key) continue;
        if (out.field) { out.state = SkillNumericState::Ambiguous; out.field = nullptr; return out; }
        out.field = &field; out.ordinal = i;
        out.state = field.values.empty() ? SkillNumericState::ExplicitEmpty : SkillNumericState::Value;
    }
    return out;
}
CharacterFieldSelection commonSkillField(const SkillSourceData &source, const std::string &tag) {
    const auto fields = source.definition.fieldsInScope(tag, "common");
    if (fields.empty()) return {};
    if (fields.size() > 1) return {SkillNumericState::Ambiguous, nullptr, 0};
    return {fields.front()->field.values.empty() ? SkillNumericState::ExplicitEmpty : SkillNumericState::Value,
        &fields.front()->field, fields.front()->ordinal};
}
SourceRef characterFieldRef(const CharacterScript &source, const Field &field, size_t ordinal) {
    SourceRef out; out.packageIdentity = source.provenance.value("package_identity", std::string());
    out.memberPath = source.script.path; out.memberSha256 = source.provenance.value("member_sha256", std::string());
    if (out.memberSha256.empty()) out.memberSha256 = sha256(source.bytes);
    out.byteOffset = field.offset; out.ordinal = ordinal; out.literalPath = source.provenance.value("literal_path", source.script.path);
    size_t end = source.bytes.size(); for (const auto &candidate : source.script.fields)
        if (candidate.offset > field.offset) end = std::min(end, candidate.offset);
    out.byteLength = end > out.byteOffset ? end - out.byteOffset : 0; return out;
}
void blockNumeric(SkillNumericResult &result, SkillNumericState state, const std::string &tag, const std::string &reason) {
    result.state = state; result.value.reset();
    result.diagnostics.push_back({{"kind", "consumer_field_unavailable"}, {"tag", tag},
        {"state", skillNumericStateName(state)}, {"reason", reason}});
}
}
SkillCostResult evaluateCharacterSkillCosts(const SkillSourceData &source, int effectiveLevel,
    const CharacterDefinition &character, int weaponSubtype, bool command,
    const std::vector<SkillCostModifier> &additionalMpModifiers,
    const std::vector<SkillCostModifier> &additionalCooldownModifiers, SkillCostAbsencePolicy absencePolicy) {
    SkillCostResult out;
    out.key = source.definition.key; out.effectiveLevel = effectiveLevel;
    out.absencePolicy = absencePolicy;
    out.mp = evaluate(source, "[consume MP]", effectiveLevel, {}, true, false);
    out.cooldown = evaluate(source, "[cool time]", effectiveLevel, {}, false, false, absencePolicy);
    const auto effect = commonSkillField(source, "[weapon effect type]");
    std::string effectType;
    if (effect.state == SkillNumericState::Value && effect.field->values.size() == 1 && effect.field->values[0].is_string())
        effectType = normalize(effect.field->values[0].get<std::string>());
    else if (effect.state == SkillNumericState::Absent && absencePolicy == SkillCostAbsencePolicy::Inferred1031OptionalFieldsV1) {
        effectType = "[none]";
        const auto trace = absencePolicyTrace(source, "[weapon effect type]", "common", effectType, absencePolicy);
        out.mp.trace.push_back(trace); out.cooldown.trace.push_back(trace);
        auto diagnostic = trace; diagnostic["kind"] = "weapon_effect_type_absent_policy";
        out.consumerDiagnostics.push_back(std::move(diagnostic));
    }
    else out.consumerDiagnostics.push_back({{"kind", "weapon_effect_type_unavailable"},
        {"state", skillNumericStateName(effect.state)}, {"reason", "Cannot select CHR multiplier from skill name/presentation state"}});
    if (effectType != "[none]" && effectType != "[physical]" && effectType != "[magical]") {
        const auto state = effect.state == SkillNumericState::Value ? SkillNumericState::Malformed : effect.state;
        if (out.mp.state == SkillNumericState::Value) blockNumeric(out.mp, state, "[weapon effect type]", "No unique supported weapon effect type");
        if (out.cooldown.state == SkillNumericState::Value) blockNumeric(out.cooldown, state, "[weapon effect type]", "No unique supported weapon effect type");
        return out;
    }
    if (effect.field) {
        auto effectRef = characterFieldRef(source.definition.source, *effect.field, effect.ordinal); effectRef.scope = "common";
        out.consumerDiagnostics.push_back({{"kind", "selected_weapon_effect_type"}, {"value", effectType},
            {"classification", "source_field_selection"}, {"source", effectRef.json()},
            {"meaning", "Selects the corresponding CHR MP/CD multiplier pair; does not imply damage type"}});
    }
    if (effectType == "[none]") {
        out.consumerDiagnostics.push_back({{"kind", "weapon_multiplier_not_applied"},
            {"reason", effect.field ? "SKL source explicitly selects [none]" : "Explicit opt-in 1031 absence policy selects [none]"}});
    } else {
    const auto table = characterField(character.source, "[weapon skill info]");
    if (table.state != SkillNumericState::Value || table.field->values.size() % 4 || weaponSubtype < 0 ||
        size_t(weaponSubtype) >= table.field->values.size() / 4) {
        out.consumerDiagnostics.push_back({{"kind", "weapon_skill_info_unavailable"}, {"state", skillNumericStateName(table.state)},
            {"subtype", weaponSubtype}, {"value_count", table.field ? table.field->values.size() : 0},
            {"reason", "Raw EQU subtype must select one complete four-value CHR row"}});
        const auto state = table.state == SkillNumericState::Value ? SkillNumericState::Malformed : table.state;
        if (out.mp.state == SkillNumericState::Value) blockNumeric(out.mp, state, "[weapon skill info]", "CHR multiplier row unavailable");
        if (out.cooldown.state == SkillNumericState::Value) blockNumeric(out.cooldown, state, "[weapon skill info]", "CHR multiplier row unavailable");
        return out;
    }
    const size_t base = size_t(weaponSubtype) * 4, mpColumn = effectType == "[magical]" ? 2 : 0,
        cdColumn = effectType == "[magical]" ? 3 : 1;
    const auto &values = table.field->values;
    if (!values[base+mpColumn].is_number() || !values[base+cdColumn].is_number() ||
        !std::isfinite(values[base+mpColumn].get<double>()) || !std::isfinite(values[base+cdColumn].get<double>()) ||
        values[base+mpColumn].get<double>() < 0 || values[base+cdColumn].get<double>() < 0) {
        out.consumerDiagnostics.push_back({{"kind", "weapon_skill_info_row_malformed"}, {"subtype", weaponSubtype}});
        if (out.mp.state == SkillNumericState::Value) blockNumeric(out.mp, SkillNumericState::Malformed, "[weapon skill info]", "Selected CHR row is malformed");
        if (out.cooldown.state == SkillNumericState::Value) blockNumeric(out.cooldown, SkillNumericState::Malformed, "[weapon skill info]", "Selected CHR row is malformed");
        return out;
    }
    const SourceRef tableRef = characterFieldRef(character.source, *table.field, table.ordinal);
    auto applyRate = [&](SkillNumericResult &numeric, double rate, const char *kind) {
        if (numeric.state != SkillNumericState::Value || !numeric.value) return;
        const double before = *numeric.value; *numeric.value *= rate;
        if (!std::isfinite(*numeric.value)) { blockNumeric(numeric, SkillNumericState::Malformed, "[weapon skill info]", "Multiplier overflow"); return; }
        numeric.trace.push_back({{"stage", "weapon_skill_multiplier"}, {"kind", kind}, {"subtype", weaponSubtype},
            {"effect_type", effectType}, {"rate", rate}, {"selected_row", Json::array({values[base],values[base+1],values[base+2],values[base+3]})},
            {"before", before}, {"result", *numeric.value},
            {"source", tableRef.json()}, {"evidence", endpointEvidence()}});
    };
    applyRate(out.mp, values[base+mpColumn].get<double>(), "mp");
    applyRate(out.cooldown, values[base+cdColumn].get<double>(), "cooldown");
    }
    if (command) {
        const auto advantage = commonSkillField(source, "[skill command advantage]");
        if (advantage.state == SkillNumericState::Absent) {
            out.consumerDiagnostics.push_back({{"kind", "command_advantage_absent"}, {"state", "Absent"},
                {"classification", "inferred_beta"}, {"reason", "Optional source modifier is absent; apply no command reduction"}});
        } else if (advantage.state != SkillNumericState::Value || advantage.field->values.size() != 2 ||
            !advantage.field->values[0].is_number() || !advantage.field->values[1].is_number() ||
            advantage.field->values[0].get<double>() < 0 || advantage.field->values[1].get<double>() < 0 ||
            !std::isfinite(advantage.field->values[0].get<double>()) || !std::isfinite(advantage.field->values[1].get<double>())) {
            out.consumerDiagnostics.push_back({{"kind", "command_advantage_unavailable"}, {"state", skillNumericStateName(advantage.state)},
                {"reason", "Expected two finite nonnegative values in 0.1% units"}});
            const auto state = advantage.state == SkillNumericState::Value ? SkillNumericState::Malformed : advantage.state;
            if (out.mp.state == SkillNumericState::Value) blockNumeric(out.mp, state, "[skill command advantage]", "MP command reduction unavailable");
            if (out.cooldown.state == SkillNumericState::Value) blockNumeric(out.cooldown, state, "[skill command advantage]", "CD command reduction unavailable");
        } else {
            auto advantageRef = characterFieldRef(source.definition.source, *advantage.field, advantage.ordinal); advantageRef.scope = "common";
            const double cdReduction = advantage.field->values[0].get<double>() / 1000.0;
            const double mpReduction = advantage.field->values[1].get<double>() / 1000.0;
            auto commandRate = [&](SkillNumericResult &numeric, double reduction, const char *kind) {
                if (numeric.state != SkillNumericState::Value || !numeric.value) return;
                const double before = *numeric.value; *numeric.value *= std::max(0.0, 1.0 - reduction);
                numeric.trace.push_back({{"stage", "command_advantage"}, {"kind", kind}, {"reduction_0_1_percent", reduction*1000.0},
                    {"before", before}, {"result", *numeric.value}, {"source", advantageRef.json()}, {"evidence", endpointEvidence()}});
            };
            commandRate(out.mp, mpReduction, "mp"); commandRate(out.cooldown, cdReduction, "cooldown");
            out.consumerDiagnostics.push_back({{"kind", "selected_command_advantage"},
                {"authored_values", advantage.field->values}, {"units", "0.1_percent"},
                {"source", advantageRef.json()}, {"evidence", endpointEvidence()}});
        }
    }
    // Weapon, command and externally supplied state/equipment modifiers are
    // evaluated in this explicit order. No integer conversion occurs here.
    auto applyAdditional = [&](SkillNumericResult &numeric, const std::vector<SkillCostModifier> &modifiers) {
        if (!numeric.usable()) return;
        for (const auto &modifier : modifiers) {
            if (modifier.id.empty() || modifier.evidence.empty() || !std::isfinite(modifier.multiply) ||
                !std::isfinite(modifier.add) || modifier.multiply < 0) {
                blockNumeric(numeric, SkillNumericState::Malformed, "modifier", "Modifier requires identity, evidence and finite valid operands");
                return;
            }
            const double before = *numeric.value;
            *numeric.value = before * modifier.multiply + modifier.add;
            numeric.trace.push_back({{"stage", "modifier"}, {"id", modifier.id}, {"classification", "inferred_beta"},
                {"before", before}, {"multiply", modifier.multiply}, {"add", modifier.add}, {"result", *numeric.value},
                {"source", modifier.source.json()}, {"evidence", modifier.evidence}});
            if (!std::isfinite(*numeric.value)) {
                blockNumeric(numeric, SkillNumericState::Malformed, "modifier", "Modifier overflowed finite domain"); return;
            }
        }
    };
    applyAdditional(out.mp, additionalMpModifiers);
    applyAdditional(out.cooldown, additionalCooldownModifiers);
    if (out.mp.usable() && out.mp.value) {
        const double before = *out.mp.value;
        const double positive = std::max(0.0, before);
        if (std::trunc(positive) > double(std::numeric_limits<int>::max())) {
            blockNumeric(out.mp, SkillNumericState::Malformed, "[consume MP]", "Final MP exceeds the integer consumer range");
        } else {
            *out.mp.value = std::trunc(positive);
            out.mp.trace.push_back({{"stage", "positive_truncate_final_mp"}, {"before", before},
                {"nonnegative_input", positive}, {"result", *out.mp.value}, {"classification", "inferred_beta"}});
        }
    }
    if (out.cooldown.usable()) {
        const double before = *out.cooldown.value; *out.cooldown.value = std::max(0.0, before);
        out.cooldown.trace.push_back({{"stage", "preserve_source_milliseconds"}, {"before", before},
            {"result", *out.cooldown.value}, {"unit", "ms"}});
    }
    return out;
}
} // namespace dnf
