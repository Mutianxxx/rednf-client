#include "dnf/attributes.hpp"
#include <cmath>
#include <cstring>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
struct AttributeSpec {
    ChrAttribute id;
    const char *name, *tag, *unit;
    bool requiredInitial = false, allowNegative = false;
};
const AttributeSpec specs[] = {
    {ChrAttribute::HpMax,"hp_max","[hp max]","hp_points",true},
    {ChrAttribute::MpMax,"mp_max","[mp max]","mp_points",true},
    {ChrAttribute::PhysicalAttack,"chr_physical_attack","[physical attack]","chr_base_coefficient",true},
    {ChrAttribute::PhysicalDefense,"chr_physical_defense","[physical defense]","chr_base_coefficient",true},
    {ChrAttribute::MagicalAttack,"chr_magical_attack","[magical attack]","chr_base_coefficient",true},
    {ChrAttribute::MagicalDefense,"chr_magical_defense","[magical defense]","chr_base_coefficient",true},
    {ChrAttribute::HpRegenSpeed,"hp_regen_speed","[hp regen speed]","source_regen_unit_unresolved"},
    {ChrAttribute::MpRegenSpeed,"mp_regen_speed","[mp regen speed]","source_regen_unit_unresolved"},
    {ChrAttribute::MoveSpeed,"move_speed","[move speed]","chr_per_mille_base_1000"},
    {ChrAttribute::AttackSpeed,"attack_speed","[attack speed]","chr_per_mille_base_1000"},
    {ChrAttribute::CastSpeed,"cast_speed","[cast speed]","chr_per_mille_base_1000"},
    {ChrAttribute::HitRecovery,"hit_recovery","[hit recovery]","source_recovery_unit_unresolved"},
    {ChrAttribute::JumpPower,"jump_power","[jump power]","source_jump_power_unit_unresolved"},
    {ChrAttribute::JumpSpeed,"jump_speed","[jump speed]","source_jump_speed_unit_unresolved"},
    {ChrAttribute::InventoryLimit,"inventory_limit","[inventory limit]","source_inventory_unit_unresolved"},
    {ChrAttribute::Weight,"weight","[weight]","source_weight_unit_unresolved"},
    {ChrAttribute::FireResistance,"fire_resistance","[fire resistance]","source_resistance_points",false,true},
    {ChrAttribute::WaterResistance,"water_resistance","[water resistance]","source_resistance_points",false,true},
    {ChrAttribute::DarkResistance,"dark_resistance","[dark resistance]","source_resistance_points",false,true},
    {ChrAttribute::LightResistance,"light_resistance","[light resistance]","source_resistance_points",false,true}
};
const AttributeSpec &spec(ChrAttribute id) {
    for (const auto &value : specs) if (value.id == id) return value;
    throw std::invalid_argument("Unknown CHR attribute");
}
const char *stateName(CharacterAttributeState state) {
    switch (state) {
    case CharacterAttributeState::Value: return "value";
    case CharacterAttributeState::Absent: return "absent";
    case CharacterAttributeState::ExplicitEmpty: return "explicit_empty";
    case CharacterAttributeState::Ambiguous: return "ambiguous";
    case CharacterAttributeState::Malformed: return "malformed";
    }
    return "malformed";
}
uint32_t bits(float value) {
    static_assert(sizeof(float) == 4 && std::numeric_limits<float>::is_iec559, "CHR growth requires IEEE binary32");
    uint32_t result;
    std::memcpy(&result, &value, sizeof(result));
    return result;
}
float add32(float a, float b) {
    // Store every level result. Do not replace this by a multiply or retain
    // excess x87 precision; the chosen policy intentionally differs at edges.
    volatile float result = a + b;
    return result;
}
void diagnostic(CharacterBaseAttributes &result, const char *kind, const char *severity, Json details = Json::object()) {
    details["kind"] = kind;
    details["severity"] = severity;
    result.diagnostics.push_back(std::move(details));
}
Json blockJson(const CharacterStatBlock &block) {
    Json fields = Json::array();
    for (size_t ordinal = 0; ordinal < block.fields.size(); ++ordinal) {
        const auto &field = block.fields[ordinal];
        fields.push_back({{"tag",field.tag},{"offset",field.offset},{"ordinal",ordinal},{"values",field.values}});
    }
    return {{"tag",block.tag},{"source_growtype",block.growtype},{"awakening",block.awakening},
            {"offset",block.offset},{"end_offset",block.endOffset},{"fields",fields}};
}
void validateBlockSpan(const CharacterDefinition &definition, CharacterBaseAttributes &result,
                       const CharacterStatBlock &block) {
    const size_t memberSize = definition.source.bytes.size();
    const auto aligned = [](size_t offset) { return offset >= 2 && (offset - 2) % 5 == 0; };
    if (!aligned(block.offset) || !aligned(block.endOffset) || block.offset >= block.endOffset ||
        block.endOffset > memberSize) {
        diagnostic(result,"malformed_stat_block_span","error",{{"tag",block.tag},
            {"offset",block.offset},{"end_offset",block.endOffset},{"member_size",memberSize}});
    }
    size_t previous = block.offset;
    for (size_t ordinal = 0; ordinal < block.fields.size(); ++ordinal) {
        const auto &field = block.fields[ordinal];
        // Keep the malformed candidates for diagnosis. Never sanitize an
        // offset or reorder fields to manufacture a valid source span.
        if (!aligned(field.offset) || field.offset <= previous || field.offset >= block.endOffset ||
            field.offset > memberSize || memberSize - field.offset < 5) {
            diagnostic(result,"malformed_stat_field_span","error",{{"tag",block.tag},
                {"field_tag",field.tag},{"ordinal",ordinal},{"offset",field.offset},
                {"previous_offset",previous},{"end_offset",block.endOffset},{"member_size",memberSize}});
        }
        previous = field.offset;
    }
}
void validateDisjointBlocks(CharacterBaseAttributes &result, const CharacterStatBlock &a,
                            const CharacterStatBlock &b) {
    if (a.offset < b.endOffset && b.offset < a.endOffset)
        diagnostic(result,"overlapping_stat_block_spans","error",{
            {"first",{{"tag",a.tag},{"offset",a.offset},{"end_offset",a.endOffset}}},
            {"second",{{"tag",b.tag},{"offset",b.offset},{"end_offset",b.endOffset}}}});
}
const CharacterStatBlock *selectBlock(const CharacterDefinition &definition, CharacterBaseAttributes &result,
                                     const std::string &tag, int sourceGrowtype, int awakening) {
    const CharacterStatBlock *selected = nullptr;
    size_t count = 0;
    for (const auto &block : definition.stats)
        if (normalize(block.tag) == tag && block.growtype == sourceGrowtype && block.awakening == awakening) {
            ++count;
            selected = &block;
            result.selectedBlocks.push_back(blockJson(block));
            validateBlockSpan(definition,result,block);
        }
    if (count != 1) {
        diagnostic(result, count ? "ambiguous_stat_block" : "missing_stat_block", "error",
            {{"tag",tag},{"source_growtype",sourceGrowtype},{"awakening",awakening},{"candidate_count",count}});
        return nullptr;
    }
    if (selected->fields.empty()) diagnostic(result,"empty_stat_block","warning",{{"tag",tag},{"offset",selected->offset}});
    return selected;
}
SourceRef fieldSource(const CharacterDefinition &definition, const CharacterBaseAttributes &result,
                      const CharacterStatBlock &block, size_t ordinal) {
    const auto &field = block.fields[ordinal];
    const uint64_t end = ordinal + 1 < block.fields.size() ? block.fields[ordinal+1].offset : block.endOffset;
    SourceRef ref;
    ref.packageIdentity = definition.source.provenance.value("package_identity", std::string());
    ref.memberPath = definition.source.script.path;
    ref.memberSha256 = result.source.at("member_sha256").get<std::string>();
    ref.literalPath = definition.source.provenance.value("literal_path", definition.source.script.path);
    ref.textEncoding = "CP936";
    ref.byteOffset = field.offset;
    ref.byteLength = end >= field.offset ? end - field.offset : 0;
    ref.ordinal = ordinal;
    ref.scope = normalize(block.tag) + ":source-growtype=" + std::to_string(block.growtype) + ":awakening=" + std::to_string(block.awakening);
    return ref;
}
struct Scalar {
    CharacterAttributeState state = CharacterAttributeState::Absent;
    float value = 0;
    Json trace = Json::object();
};
Scalar readScalar(const CharacterDefinition &definition, const CharacterBaseAttributes &result,
                  const CharacterStatBlock &block, const AttributeSpec &attribute) {
    Scalar scalar;
    scalar.trace = {{"block",normalize(block.tag)},{"source_growtype",block.growtype},{"awakening",block.awakening},
                    {"tag",attribute.tag},{"candidates",Json::array()}};
    const Field *selected = nullptr;
    for (size_t ordinal = 0; ordinal < block.fields.size(); ++ordinal) if (normalize(block.fields[ordinal].tag) == attribute.tag) {
        const auto &field = block.fields[ordinal];
        scalar.trace["candidates"].push_back({{"values",field.values},{"source",fieldSource(definition,result,block,ordinal).json()}});
        selected = &field;
    }
    if (!selected) return scalar;
    if (scalar.trace["candidates"].size() != 1) { scalar.state = CharacterAttributeState::Ambiguous; return scalar; }
    if (selected->values.is_array() && selected->values.empty()) { scalar.state = CharacterAttributeState::ExplicitEmpty; return scalar; }
    if (!selected->values.is_array() || selected->values.size() != 1 || !selected->values[0].is_number()) {
        scalar.state = CharacterAttributeState::Malformed;
        return scalar;
    }
    const auto &sourceValue = selected->values[0];
    // PVF integer tokens are signed i32. A synthetic or corrupted source
    // cannot bypass that boundary through a JSON i64/u64 conversion.
    if ((sourceValue.is_number_unsigned() && sourceValue.get<uint64_t>() > uint64_t(std::numeric_limits<int32_t>::max())) ||
        (!sourceValue.is_number_unsigned() && sourceValue.is_number_integer() &&
         (sourceValue.get<int64_t>() < int64_t(std::numeric_limits<int32_t>::min()) ||
          sourceValue.get<int64_t>() > int64_t(std::numeric_limits<int32_t>::max())))) {
        scalar.state = CharacterAttributeState::Malformed;
        return scalar;
    }
    const double number = sourceValue.get<double>();
    if (!std::isfinite(number) || std::abs(number) > std::numeric_limits<float>::max() ||
        (!attribute.allowNegative && number < 0)) {
        scalar.state = CharacterAttributeState::Malformed;
        return scalar;
    }
    scalar.value = static_cast<float>(number);
    scalar.state = CharacterAttributeState::Value;
    scalar.trace["float32"] = scalar.value;
    scalar.trace["float32_bits"] = bits(scalar.value);
    return scalar;
}
bool invalid(const Scalar &value) {
    return value.state != CharacterAttributeState::Value && value.state != CharacterAttributeState::Absent;
}
} // namespace

const char *chrAttributeName(ChrAttribute attribute) { return spec(attribute).name; }
const char *chrAttributeTag(ChrAttribute attribute) { return spec(attribute).tag; }
int CharacterAttributeValue::integer() const {
    if (!usable() || !std::isfinite(value) || double(value) < double(std::numeric_limits<int>::min()) ||
        double(value) > double(std::numeric_limits<int>::max()))
        throw std::runtime_error("CHR attribute is unavailable or outside the integer consumer range");
    return static_cast<int>(value);
}
Json CharacterAttributeValue::snapshot() const {
    Json result = {{"state",stateName(state)},{"unit",unit},{"trace",trace}};
    if (usable()) {
        result["float32"] = value;
        result["float32_bits"] = bits(value);
        if (std::isfinite(value) && double(value) >= double(std::numeric_limits<int>::min()) &&
            double(value) <= double(std::numeric_limits<int>::max())) result["integer_consumer"] = integer();
    }
    return result;
}
CharacterGrowthPolicy CharacterGrowthPolicy::inferredChrGrowthV1() { return {"inferred-chr-growth-v1"}; }
bool CharacterBaseAttributes::usable() const {
    for (const auto &entry : diagnostics) if (entry.value("severity",std::string()) == "error") return false;
    for (const auto &attribute : specs) if (attribute.requiredInitial) {
        const auto found = attributes.find(attribute.id);
        if (found == attributes.end() || !found->second.usable()) return false;
    }
    return true;
}
const CharacterAttributeValue &CharacterBaseAttributes::at(ChrAttribute attribute) const { return attributes.at(attribute); }
float CharacterBaseAttributes::value(ChrAttribute attribute) const {
    const auto &result = at(attribute);
    if (!usable() || !result.usable()) throw std::runtime_error("CHR base attributes are unavailable");
    return result.value;
}
int CharacterBaseAttributes::integer(ChrAttribute attribute) const {
    if (!usable()) throw std::runtime_error("CHR base attributes are unavailable");
    return at(attribute).integer();
}
Json CharacterBaseAttributes::snapshot() const {
    Json values = Json::object();
    for (const auto &[id,value] : attributes) values[chrAttributeName(id)] = value.snapshot();
    return {{"usable",usable()},{"identity",identity.json()},{"level",level},{"policy",policy},
            {"classification","inferred beta CHR base growth; not final combat attributes"},
            {"arithmetic","float32 addition once per level; truncate only at integer consumer"},
            {"identity_authorization",false},{"source",source},{"selected_blocks",selectedBlocks},
            {"attributes",values},{"diagnostics",diagnostics}};
}
CharacterBaseAttributes buildCharacterBaseAttributes(const CharacterDefinition &definition,
    CharacterIdentity identity, int level, const CharacterGrowthPolicy &policy) {
    CharacterBaseAttributes result;
    result.identity = identity; result.level = level; result.policy = policy.id;
    result.source = {{"path",definition.source.script.path},{"provenance",definition.source.provenance},
                     {"member_sha256",sha256(definition.source.bytes)}};
    if (policy.id != "inferred-chr-growth-v1") {
        diagnostic(result,"growth_policy_not_enabled","error",{{"requested_policy",policy.id}});
        return result;
    }
    if (level < 1 || level > 99) {
        diagnostic(result,"level_outside_policy_range","error",{{"minimum",1},{"maximum",99},{"requested",level}});
        return result;
    }
    if (identity.jobId != definition.registration.id || identity.growtype < 0 || identity.growtype >= 6 ||
        identity.awakening < 0 || identity.awakening > 2) {
        diagnostic(result,"invalid_source_identity","error");
        return result;
    }
    diagnostic(result,"growth_scope_adapter","info",{
        {"classification","confirmed mapping for archived exact-1031 consumer; source selection adapter"},
        {"evidence","reports/combat-native-reverse/advancement/README.md:49-57"},
        {"native_loader","12A716B..12A71C8; awakening destinations CHR+4F0+40*g"},
        {"native_name_consumer","85426D..85427B; CHR+4D0+20*(2*g+a)"},
        {"runtime_growtype",identity.growtype},{"source_growth_block",identity.growtype+1}});
    diagnostic(result,"growth_curve_policy","info",{
        {"classification","inferred"},{"retroactive_selected_branch",true},{"awakening_replaces_delta",true},
        {"basis","charactersample.chr:7-13 initial values; 69-75 pre-advancement increments; 110-116 branch parameters"},
        {"unverified","native final stat inheritance, advancement-level history and STR/INT/VIT/SPR conversion"}});
    if (identity.awakening == 2) diagnostic(result,"second_awakening_source_only","warning",{
        {"reason","Source block evaluation does not authorize a playable identity; archived 854256 name path rejects a>=2"}});
    const auto initial = selectBlock(definition,result,"[initial value]",0,0);
    const auto growth = selectBlock(definition,result,"[growtype "+std::to_string(identity.growtype+1)+"]",identity.growtype+1,0);
    const CharacterStatBlock *awakening = nullptr;
    if (identity.awakening) awakening = selectBlock(definition,result,"[awakening "+std::to_string(identity.awakening)+"]",identity.growtype+1,identity.awakening);
    if (!initial || !growth || (identity.awakening && !awakening)) return result;
    validateDisjointBlocks(result,*initial,*growth);
    if (awakening) {
        validateDisjointBlocks(result,*initial,*awakening);
        validateDisjointBlocks(result,*growth,*awakening);
    }
    for (const auto &attribute : specs) {
        CharacterAttributeValue value;
        value.unit = attribute.unit;
        const auto base = readScalar(definition,result,*initial,attribute);
        const auto branch = readScalar(definition,result,*growth,attribute);
        Scalar rate = branch;
        value.trace.push_back({{"stage","initial"},{"selection",base.trace},{"state",stateName(base.state)}});
        value.trace.push_back({{"stage","branch_delta"},{"selection",branch.trace},{"state",stateName(branch.state)}});
        bool failed = invalid(base) || invalid(branch) || (attribute.requiredInitial && base.state == CharacterAttributeState::Absent);
        CharacterAttributeState failure = invalid(base) ? base.state : invalid(branch) ? branch.state : CharacterAttributeState::Absent;
        if (awakening) {
            const auto awakened = readScalar(definition,result,*awakening,attribute);
            value.trace.push_back({{"stage","awakening_delta"},{"selection",awakened.trace},{"state",stateName(awakened.state)},
                                   {"operation",awakened.state == CharacterAttributeState::Absent ? "inherit_selected_branch_delta" : "replace_selected_branch_delta"},
                                   {"classification","inferred"}});
            if (invalid(awakened)) { failed = true; failure = awakened.state; }
            if (awakened.state == CharacterAttributeState::Value) rate = awakened;
        }
        if (failed) {
            value.state = failure;
            diagnostic(result,"attribute_source_unavailable","error",{{"attribute",attribute.name},{"state",stateName(failure)}});
            result.attributes.emplace(attribute.id,std::move(value));
            continue;
        }
        value.value = base.state == CharacterAttributeState::Value ? base.value : 0;
        if (base.state == CharacterAttributeState::Absent) value.trace.push_back({{"stage","absent_initial_default"},{"value",0},{"classification","inferred default; no authored field"}});
        const float delta = rate.state == CharacterAttributeState::Value ? rate.value : 0;
        if (rate.state == CharacterAttributeState::Absent) value.trace.push_back({{"stage","absent_growth_delta"},{"value",0},{"classification","inferred zero increment"}});
        Json steps = Json::array();
        for (int currentLevel = 2; currentLevel <= level; ++currentLevel) {
            const float before = value.value;
            value.value = add32(before,delta);
            if (!std::isfinite(value.value)) {
                value.state = CharacterAttributeState::Malformed;
                diagnostic(result,"attribute_arithmetic_overflow","error",{{"attribute",attribute.name},{"level",currentLevel}});
                break;
            }
            steps.push_back({{"level",currentLevel},{"before",before},{"delta",delta},{"after",value.value},{"float32_bits",bits(value.value)}});
        }
        value.trace.push_back({{"stage","per_level_growth"},{"operation","repeated_float32_add"},{"count",level-1},{"steps",steps},{"classification","inferred"}});
        if (std::isfinite(value.value) && ((attribute.id != ChrAttribute::HpMax && attribute.id != ChrAttribute::MpMax) || value.value > 0))
            value.state = CharacterAttributeState::Value;
        else {
            value.state = CharacterAttributeState::Malformed;
            diagnostic(result,"invalid_base_resource_maximum","error",{{"attribute",attribute.name}});
        }
        result.attributes.emplace(attribute.id,std::move(value));
    }
    return result;
}
} // namespace dnf
