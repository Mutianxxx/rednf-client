#pragma once
#include "content_profile.hpp"
#include "skill_data.hpp"

namespace dnf {
enum class SkillNumericState { Absent, ExplicitEmpty, Value, Ambiguous, Malformed };
const char *skillNumericStateName(SkillNumericState state);
// The library remains strict unless a caller explicitly selects this current
// 1031 corpus policy. Absence is distinct from authored empty/invalid fields.
enum class SkillCostAbsencePolicy { Strict, Inferred1031OptionalFieldsV1 };
const char *skillCostAbsencePolicyName(SkillCostAbsencePolicy policy);
constexpr SkillCostAbsencePolicy inferred1031SkillCostAbsencePolicy() {
    return SkillCostAbsencePolicy::Inferred1031OptionalFieldsV1;
}
struct SkillCostModifier {
    std::string id;
    double multiply = 1, add = 0;
    SourceRef source;
    Json evidence = Json::array();
};
struct SkillNumericResult {
    SkillNumericState state = SkillNumericState::Absent;
    std::optional<double> value;
    Json trace = Json::array(), diagnostics = Json::array();
    bool usable() const { return state == SkillNumericState::Value && value.has_value(); }
    Json json() const;
};
struct SkillCostResult {
    SkillKey key;
    int effectiveLevel = 0;
    SkillCostAbsencePolicy absencePolicy = SkillCostAbsencePolicy::Strict;
    SkillNumericResult mp, cooldown;
    std::optional<int> consumeMp() const;
    // Source cooldown unit is already milliseconds. No second unit conversion
    // or integer rounding is applied by this evaluator.
    std::optional<double> cooldownMs() const;
    Json consumerDiagnostics = Json::array();
    Json json() const;
};
// Explicit beta adapter: the supplied SKL sample identifies common [maximum
// level] as the highest level by all means and MP/CD endpoints as Lv1/highest.
// Linear interpolation/clamping and final MP truncation are D03/D04 inference,
// not a claim that the native full modifier/rounding consumer is recovered.
// Missing/ambiguous/empty/malformed N blocks; purchase ceilings and level-info
// row counts never supply it. Level <= 0 cannot release. Levels above N clamp
// with a trace. For N=1 the first endpoint wins and a conflict is diagnosed.
SkillCostResult evaluateSkillCosts(const SkillSourceData &source, int effectiveLevel,
    const std::vector<SkillCostModifier> &mpModifiers = {},
    const std::vector<SkillCostModifier> &cooldownModifiers = {},
    SkillCostAbsencePolicy absencePolicy = SkillCostAbsencePolicy::Strict);
// Consumes common SKL [weapon effect type], CHR [weapon skill info], and the
// source weapon's numeric subtype. Table layout (four values per subtype) is a
// current-content semantic adapter backed by the supplied CHR sample; it is
// not inferred from skill names, job IDs, or `Skill::magic` presentation state.
// `weaponSubtype` must be the raw EQU [sub type], not a legacy appearance slot.
// Command advantage follows sample units: value/1000 is the reduction ratio.
// Strict policy blocks missing effect/cooldown fields. The explicit inferred
// 1031 policy treats only absent effect as [none] and absent cooldown as zero;
// it never supplies MP, repairs empty/ambiguous/malformed fields, or claims a
// confirmed native default. The source definition stays unchanged.
SkillCostResult evaluateCharacterSkillCosts(const SkillSourceData &source, int effectiveLevel,
    const CharacterDefinition &character, int weaponSubtype, bool command = false,
    const std::vector<SkillCostModifier> &additionalMpModifiers = {},
    const std::vector<SkillCostModifier> &additionalCooldownModifiers = {},
    SkillCostAbsencePolicy absencePolicy = SkillCostAbsencePolicy::Strict);
Json runSkillCostTests(Pvf &pvf);
} // namespace dnf
