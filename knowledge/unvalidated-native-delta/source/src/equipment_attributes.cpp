#include "dnf/equipment_attributes.hpp"
#include "dnf/character_controller.hpp"
#include "dnf/progression.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *policyId = "inferred-equipment-resource-flat-rate-v1";
constexpr const char *evaluationMarker = "equipment_resource_evaluation";
void issue(EquipmentResourceAttributes &out, const char *kind, const char *severity,
           Json details = Json::object()) {
    details["kind"] = kind; details["severity"] = severity;
    out.diagnostics.push_back(details);
    out.adjusted.diagnostics.push_back(std::move(details));
}
bool hasError(const Json &diagnostics, size_t begin = 0) {
    for (size_t i = begin; i < diagnostics.size(); ++i)
        if (diagnostics[i].value("severity",std::string()) == "error") return true;
    return false;
}
bool i32(const Json &value, int &number) {
    if (!value.is_number_integer() ||
        (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(std::numeric_limits<int32_t>::max()))) return false;
    const auto raw = value.get<int64_t>();
    if (raw < std::numeric_limits<int32_t>::min() || raw > std::numeric_limits<int32_t>::max()) return false;
    number = int(raw); return true;
}
float add32(float a, float b) { volatile float result = a + b; return result; }
float divide32(float a, float b) { volatile float result = a / b; return result; }
float multiply32(float a, float b) { volatile float result = a * b; return result; }
std::string metadata(const Json &source, const char *key, const std::string &fallback = {}) {
    return source.is_object() && source.contains(key) && source.at(key).is_string() ?
        source.at(key).get<std::string>() : fallback;
}
bool resourceTag(const std::string &tag) {
    return tag == "[hp max]" || tag == "[mp max]" || tag == "[mp max rate]";
}
bool relatedResource(std::string value) {
    value = normalize(std::move(value));
    std::replace(value.begin(),value.end(),'_',' ');
    return value.find("hp max") != std::string::npos || value.find("mp max") != std::string::npos;
}
SourceRef fieldRef(const EquippedAttributeSource &item, size_t ordinal) {
    const auto &field = item.source.fields.at(ordinal);
    const auto end = ordinal + 1 < item.source.fields.size() ? item.source.fields[ordinal+1].offset : item.source.rawBytes.size();
    SourceRef ref;
    ref.packageIdentity = metadata(item.source.source,"package_identity");
    ref.memberPath = normalize(item.source.path); ref.literalPath = metadata(item.source.source,"literal_path",item.source.path);
    ref.memberSha256 = sha256(item.source.rawBytes);
    ref.byteOffset = field.offset; ref.byteLength = end >= field.offset ? end - field.offset : 0; ref.ordinal = ordinal;
    ref.scope = "equipment-resource:instance=" + std::to_string(item.instanceUid) + ":slot=" + item.equippedSlot;
    return ref;
}
Json candidates(const EquippedAttributeSource &item, const std::string &tag) {
    Json result = Json::array();
    for (size_t i = 0; i < item.source.fields.size(); ++i) if (normalize(item.source.fields[i].tag) == tag)
        result.push_back({{"values",item.source.fields[i].values},{"source",fieldRef(item,i).json()}});
    return result;
}
struct Scalar { bool valid = true, present = false; float value = 0; Json selection = Json::array(); };
Scalar scalar(EquipmentResourceAttributes &out, const EquippedAttributeSource &item, const std::string &tag,
              bool integerOnly) {
    Scalar result; result.selection = candidates(item,tag);
    if (result.selection.empty()) return result;
    result.present = true;
    if (result.selection.size() != 1) result.valid = false;
    else {
        const auto &values = result.selection[0].at("values");
        if (!values.is_array() || values.size() != 1 || !values[0].is_number()) result.valid = false;
        else {
            int number = 0; const auto &source = values[0];
            if ((integerOnly || source.is_number_integer()) && !i32(source,number)) result.valid = false;
            const auto number64 = source.get<double>();
            if (!std::isfinite(number64) || std::abs(number64) > std::numeric_limits<float>::max()) result.valid = false;
            if (result.valid) result.value = float(number64);
        }
    }
    if (!result.valid) issue(out,"invalid_equipment_resource_scalar","error",{
        {"instance_uid",item.instanceUid},{"tag",tag},{"integer_required",integerOnly},{"candidates",result.selection}});
    return result;
}
int qualificationScalar(EquipmentResourceAttributes &out, const EquippedAttributeSource &item,
                        const std::string &tag, int fallback) {
    const auto values = candidates(item,tag);
    if (values.empty()) return fallback;
    int number = 0;
    if (values.size() != 1 || !values[0]["values"].is_array() || values[0]["values"].size() != 1 ||
        !i32(values[0]["values"][0],number) || number < 0) {
        issue(out,"invalid_equipment_resource_qualification_scalar","error",{
            {"instance_uid",item.instanceUid},{"tag",tag},{"candidates",values}});
        return -1;
    }
    return number;
}
void validateSource(EquipmentResourceAttributes &out, const EquippedAttributeSource &item,
                    const std::string &package) {
    const auto &script = item.source; const auto path = normalize(script.path);
    if (path.rfind("equipment/",0) != 0 || path.size() < 4 || path.substr(path.size()-4) != ".equ" ||
        !script.source.is_object() || script.rawBytes.size() < 2 || (script.rawBytes.size()-2)%5)
        issue(out,"invalid_equipment_resource_source","error",{{"instance_uid",item.instanceUid},{"path",script.path}});
    for (const char *key : {"package_identity","literal_path","member_sha256"})
        if (script.source.is_object() && script.source.contains(key) && !script.source.at(key).is_string())
            issue(out,"invalid_equipment_resource_source_identity","error",{{"instance_uid",item.instanceUid},{"field",key}});
    const auto itemPackage = metadata(script.source,"package_identity");
    if (package.empty() || itemPackage.empty() || itemPackage != package)
        issue(out,"equipment_resource_package_mismatch","error",{{"instance_uid",item.instanceUid},
            {"base_package",package},{"equipment_package",itemPackage}});
    const auto authoredHash = metadata(script.source,"member_sha256");
    if (script.source.is_object() && script.source.contains("member_sha256") &&
        script.source.at("member_sha256").is_string() && authoredHash != sha256(script.rawBytes))
        issue(out,"equipment_resource_member_hash_mismatch","error",{{"instance_uid",item.instanceUid}});
    size_t previous = 0; bool conditional = false;
    for (size_t i = 0; i < script.fields.size(); ++i) {
        const auto &field = script.fields[i]; const auto tag = normalize(field.tag);
        if (!field.values.is_array()) issue(out,"invalid_equipment_resource_field_payload","error",{
            {"instance_uid",item.instanceUid},{"ordinal",i},{"tag",field.tag},{"values",field.values}});
        if (field.offset < 2 || (field.offset-2)%5 || field.offset <= previous ||
            field.offset > script.rawBytes.size() || script.rawBytes.size()-field.offset < 5)
            issue(out,"invalid_equipment_resource_field_span","error",{{"instance_uid",item.instanceUid},{"ordinal",i},{"offset",field.offset}});
        previous = field.offset;
        if (tag == "[if]" || tag == "[then]" || tag.find("[change status") == 0 ||
            tag == "[equipment option]" || tag == "[ability]" || tag == "[special effect]" ||
            tag == "[set ability]" || tag == "[avatar select ability]") conditional = true;
        if (conditional && resourceTag(tag)) issue(out,"conditional_equipment_resource_unresolved","error",{
            {"instance_uid",item.instanceUid},{"tag",field.tag},{"ordinal",i}});
        if (!resourceTag(tag) && relatedResource(tag)) issue(out,"unsupported_equipment_resource_field","error",{
            {"instance_uid",item.instanceUid},{"tag",field.tag},{"values",field.values},{"ordinal",i}});
        if (tag.find("[usable ") == 0 && tag != "[usable job]")
            issue(out,"unsupported_equipment_resource_qualification","error",{
                {"instance_uid",item.instanceUid},{"tag",field.tag},{"values",field.values},{"ordinal",i}});
        if (tag == "[set item master]") {
            int master = 0;
            if (!field.values.is_array() || field.values.size() != 1 || !i32(field.values[0],master) || master != -1)
                issue(out,"equipment_resource_set_unresolved","error",{
                    {"instance_uid",item.instanceUid},{"tag",field.tag},{"values",field.values},{"ordinal",i}});
        } else if (tag == "[set name]" || tag == "[set item]" || tag == "[set ability]")
            issue(out,"equipment_resource_set_unresolved","error",{
                {"instance_uid",item.instanceUid},{"tag",field.tag},{"values",field.values},{"ordinal",i}});
        // HP/MP operands nested in generic modifiers, selected avatar options
        // or conditional instructions cannot be promoted to permanent flats.
        if (field.values.is_array() && (conditional || tag == "[item aura]" || tag == "[stat]" || tag == "[stat by condition]"))
            for (const auto &value : field.values) if (value.is_string() && relatedResource(value.get<std::string>()))
                issue(out,"equipment_resource_operand_unresolved","error",{
                    {"instance_uid",item.instanceUid},{"tag",field.tag},{"values",field.values},{"ordinal",i}});
    }
}
std::string hex(const Bytes &bytes) {
    static constexpr char digits[] = "0123456789abcdef";
    std::string result; result.reserve(bytes.size()*2);
    for (auto value : bytes) { result += digits[value>>4]; result += digits[value&15]; }
    return result;
}
bool resourceValueUsable(const CharacterAttributeValue &value, ChrAttribute attribute) {
    const bool hp = attribute == ChrAttribute::HpMax;
    return value.usable() && value.unit == (hp ? "hp_points" : "mp_points") && std::isfinite(value.value) &&
        value.value >= (hp ? 1.0f : 0.0f) && double(value.value) <= double(std::numeric_limits<int32_t>::max());
}
} // namespace

EquipmentResourcePolicy EquipmentResourcePolicy::inferredFlatAndRateV1() { return {policyId}; }
bool EquipmentResourceAttributes::usable() const {
    if (policy != policyId || qualificationLevel < 1 || qualificationLevel > 99 || hasError(diagnostics) || !adjusted.usable()) return false;
    for (const auto attribute : {ChrAttribute::HpMax,ChrAttribute::MpMax}) {
        const auto found = adjusted.attributes.find(attribute);
        if (found == adjusted.attributes.end() || !resourceValueUsable(found->second,attribute)) return false;
    }
    return true;
}
Json EquipmentResourceAttributes::snapshot(bool includeSource) const {
    Json sources = Json::array();
    for (const auto &item : equipmentSources) {
        Json fields = Json::array();
        for (size_t i = 0; i < item.source.fields.size(); ++i) {
            const auto &field = item.source.fields[i];
            fields.push_back({{"tag",field.tag},{"offset",field.offset},{"ordinal",i},{"values",field.values}});
        }
        Json source = {{"instance_uid",item.instanceUid},{"equipped_slot",item.equippedSlot},{"current_durability",item.currentDurability},
            {"path",item.source.path},{"member_sha256",sha256(item.source.rawBytes)},
            {"provenance",item.source.source},{"fields",fields}};
        if (includeSource) { source["raw_bytes_hex"] = hex(item.source.rawBytes); source["ordered_tokens"] = item.source.tokens; }
        sources.push_back(std::move(source));
    }
    return {{"usable",usable()},{"policy",policy},{"classification","inferred equipment resource groups; native final grouping unproven"},
        {"qualification_level",qualificationLevel},{"adjusted",adjusted.snapshot()},{"equipment_sources",sources},
        {"trace",trace},{"diagnostics",diagnostics},{"consumers",{{"changes_current_hp_mp",false},
            {"chr_attack_defense_conversion_applied",false},{"skills_or_passives_granted",false}}}};
}

EquipmentResourceAttributes evaluateEquipmentResourceAttributes(const CharacterBaseAttributes &base,
    const CharacterDefinition &character, const std::vector<EquippedAttributeSource> &equipment,
    int qualificationLevel, const EquipmentResourcePolicy &policy, const EquipmentSkillContext *normalSkills) {
    EquipmentResourceAttributes out; out.adjusted = base; out.equipmentSources = equipment;
    out.qualificationLevel = qualificationLevel; out.policy = policy.id;
    if (policy.id != policyId) { issue(out,"equipment_resource_policy_not_enabled","error"); return out; }
    if (!base.usable() || base.identity.jobId != character.registration.id || !base.source.is_object()) {
        issue(out,"unavailable_equipment_resource_base","error"); return out;
    }
    if (base.source.contains(evaluationMarker)) {
        issue(out,"equipment_resource_already_applied","error"); return out;
    }
    out.adjusted.source[evaluationMarker] = {{"policy",policy.id},{"qualification_level",qualificationLevel},
        {"input_kind","pure_chr_base"}};
    const bool qualificationValid = qualificationLevel >= 1 && qualificationLevel <= 99;
    if (!qualificationValid) issue(out,"invalid_equipment_resource_qualification_level","error",{{"qualification_level",qualificationLevel}});
    bool baseValid = true;
    for (const auto attribute : {ChrAttribute::HpMax,ChrAttribute::MpMax}) {
        const auto found = base.attributes.find(attribute);
        if (found == base.attributes.end() || !resourceValueUsable(found->second,attribute)) {
            baseValid = false;
            issue(out,"invalid_equipment_resource_base_value","error",{{"attribute",chrAttributeName(attribute)}});
        }
    }
    if (!baseValid) return out;
    const auto package = base.source.contains("provenance") ? metadata(base.source.at("provenance"),"package_identity") : std::string();
    float hp = base.value(ChrAttribute::HpMax), mp = base.value(ChrAttribute::MpMax), mpRate = 0;
    issue(out,"equipment_resource_group_policy","info",{
        {"classification","inferred"},{"flat_operation","CHR resource max + sum eligible equipped signed integer point deltas"},
        {"mp_rate_operation","(CHR MP max + flat group) * (1 + sum MP MAX rate / 100)"},
        {"arithmetic","float32 stored after each UID-ordered addition, percent division, factor addition and multiplication"},
        {"flat_basis","equipmentsample.equ:156-158 (CP949)"},{"rate_basis","creaturesample.equ:33 (CP949)"},
        {"sample_sha256",{{"equipmentsample.equ","9c0620fadb3c06cbc211ac21b2adbe3480288c7adbc3f99fae8e76ad43cf6b17"},
            {"creaturesample.equ","48e9f7b309b05751e06a3d9a2f53823fc61acffc76db6cb76213cac487c1cee2"}}},
        {"unverified","native grouping/order; broken-item resource effects; cross-item percentage stacking"},
        {"missing_minimum_level_default",1},{"missing_durability_default",0},{"base_level",base.level},
        {"equipment_qualification_level",qualificationLevel}});
    std::set<int64_t> uids; std::set<std::string> slots;
    auto sorted = equipment;
    std::stable_sort(sorted.begin(),sorted.end(),[](const auto &a,const auto &b){return a.instanceUid < b.instanceUid;});
    for (const auto &item : sorted) {
        const auto diagnosticsBefore = out.diagnostics.size();
        if (item.instanceUid <= 0 || !uids.insert(item.instanceUid).second || item.equippedSlot.empty() || !slots.insert(item.equippedSlot).second)
            issue(out,"invalid_equipment_resource_ownership","error",{{"instance_uid",item.instanceUid},{"slot",item.equippedSlot}});
        validateSource(out,item,package);
        try {
            auto permission=requireEquipmentSkillQualification(item.source,base.identity,qualificationLevel,normalSkills);
            if(permission.at("required_skill").at("present").get<bool>())out.trace.push_back(std::move(permission));
        }
        catch (const std::exception &error) {
            issue(out,"equipment_required_skill_rejected","error",{{"instance_uid",item.instanceUid},
                {"path",item.source.path},{"reason",error.what()}});
        }
        const auto types = candidates(item,"[equipment type]");
        if (types.size() != 1 || !types[0]["values"].is_array() || types[0]["values"].empty() ||
            !types[0]["values"][0].is_string() || types[0]["values"][0] != item.equippedSlot)
            issue(out,"equipment_resource_slot_mismatch","error",{{"instance_uid",item.instanceUid},{"candidates",types}});
        const auto jobs = candidates(item,"[usable job]");
        bool jobAllowed = false;
        if (jobs.size() == 1 && jobs[0]["values"].is_array())
            jobAllowed = equipmentJobRestriction(character,item.source).gate == EquipmentJobGate::Allowed;
        if (!jobAllowed) issue(out,"equipment_resource_job_not_qualified","error",{{"instance_uid",item.instanceUid},{"candidates",jobs}});
        const auto minimum = qualificationScalar(out,item,"[minimum level]",1);
        if (minimum < 1 || qualificationLevel < minimum) issue(out,"equipment_resource_level_not_qualified","error",{
            {"instance_uid",item.instanceUid},{"minimum_level",minimum},{"qualification_level",qualificationLevel}});
        const auto maximumDurability = qualificationScalar(out,item,"[durability]",0);
        if (maximumDurability < 0 || item.currentDurability < 0 || item.currentDurability > maximumDurability)
            issue(out,"invalid_equipment_resource_durability","error",{{"instance_uid",item.instanceUid},
                {"current",item.currentDurability},{"maximum",maximumDurability}});
        const bool broken = maximumDurability > 0 && item.currentDurability == 0;
        if (broken) issue(out,"broken_equipment_resource_inactive","info",{{"instance_uid",item.instanceUid},{"classification","inferred broken-item policy"}});
        const auto hpFlat = scalar(out,item,"[hp max]",true), mpFlat = scalar(out,item,"[mp max]",true),
                   rate = scalar(out,item,"[mp max rate]",false);
        const bool active = qualificationValid && !broken && !hasError(out.diagnostics,diagnosticsBefore);
        const Scalar values[] = {hpFlat,mpFlat,rate};
        const std::pair<const char *,float *> destinations[] = {{"[hp max]",&hp},{"[mp max]",&mp},{"[mp max rate]",&mpRate}};
        for (size_t i = 0; i < 3; ++i) {
            const auto &[tag,destination] = destinations[i]; const auto &value = values[i];
            const auto before = *destination; bool applied = active && value.valid && value.present;
            if (applied) {
                const auto after = add32(before,value.value);
                if (std::isfinite(after)) *destination = after;
                else {
                    applied = false;
                    issue(out,"equipment_resource_arithmetic_overflow","error",{
                        {"instance_uid",item.instanceUid},{"tag",tag},{"before",before},{"operand",value.value}});
                }
            }
            out.trace.push_back({{"stage",i == 2 ? "equipment_mp_rate_group" : "equipment_resource_flat_group"},
                {"instance_uid",item.instanceUid},{"tag",tag},{"unit",i == 2 ? "percentage_points" : "resource_points"},
                {"present",value.present},{"valid",value.valid},{"active",active},{"applied",applied},
                {"before",before},{"operand",value.value},{"after",*destination},{"candidates",value.selection}});
        }
    }
    const float fraction = divide32(mpRate,100.0f), factor = add32(1.0f,fraction);
    const float finalMp = multiply32(mp,factor);
    if (!std::isfinite(fraction) || !std::isfinite(factor) || !std::isfinite(finalMp) || factor <= 0)
        issue(out,"invalid_equipment_resource_rate_result","error",{{"mp_before",mp},{"rate_percent",mpRate}});
    else {
        out.trace.push_back({{"stage","equipment_resource_percent_application"},{"attribute","mp_max"},
            {"before",mp},{"rate_percent",mpRate},{"fraction",fraction},{"factor",factor},{"after",finalMp}});
        mp = finalMp;
    }
    const std::pair<ChrAttribute,float> resources[] = {{ChrAttribute::HpMax,hp},{ChrAttribute::MpMax,mp}};
    for (const auto &[attribute,value] : resources) {
        auto &destination = out.adjusted.attributes.at(attribute);
        destination.value = value;
        destination.trace.push_back({{"stage","equipment_resource_evaluation"},{"policy",policy.id},
            {"qualification_level",qualificationLevel},{"before",base.value(attribute)},{"after",value},
            {"classification","inferred"},{"evaluation_trace",out.trace}});
        if (!resourceValueUsable(destination,attribute)) issue(out,"invalid_equipment_resource_final_value","error",{
            {"attribute",chrAttributeName(attribute)},{"minimum",attribute == ChrAttribute::HpMax ? 1 : 0}});
    }
    return out;
}

EquipmentResourceAttributes evaluateEquipmentResourceAttributes(const CharacterBaseAttributes &base,
    const Progression &progression, const CharacterDefinition &character, const EquipmentResourcePolicy &policy, const EquipmentSkillContext *normalSkills) {
    std::vector<EquippedAttributeSource> inputs; int qualificationLevel = 0;
    try {
        if (!i32(progression.state.at("level"),qualificationLevel) || qualificationLevel < 1 || qualificationLevel > 99)
            throw std::runtime_error("Invalid normal equipment qualification level");
        const auto &inventory = progression.state.at("inventory"), &equipped = progression.state.at("equipped");
        if (!inventory.is_array() || !equipped.is_object()) throw std::runtime_error("Invalid inventory or equipment slot map");
        for (auto slot = equipped.begin(); slot != equipped.end(); ++slot) {
            int uid = 0;
            if (!i32(slot.value(),uid) || uid <= 0) throw std::runtime_error("Invalid equipped inventory UID");
            const Json *selected = nullptr;
            for (const auto &entry : inventory) {
                int candidate = 0;
                if (!entry.is_object() || !entry.contains("uid") || !i32(entry.at("uid"),candidate) || candidate <= 0)
                    throw std::runtime_error("Invalid inventory UID");
                if (candidate == uid) {
                    if (selected) throw std::runtime_error("Ambiguous equipped inventory UID");
                    selected = &entry;
                }
            }
            int id = 0, durability = 0, count = 0;
            if (!selected || !i32(selected->at("id"),id) || id <= 0 || !i32(selected->at("durability"),durability) ||
                !i32(selected->at("count"),count) || count != 1) throw std::runtime_error("Invalid equipped item instance");
            const auto *definition = progression.item(id);
            if (!definition || !definition->equipment) throw std::runtime_error("Missing equipped EQU definition");
            inputs.push_back({uid,slot.key(),durability,definition->source});
        }
    } catch (const std::exception &error) {
        auto out = evaluateEquipmentResourceAttributes(base,character,inputs,qualificationLevel,policy,normalSkills);
        issue(out,"equipped_resource_collection_failed","error",{{"reason",error.what()}});
        return out;
    }
    return evaluateEquipmentResourceAttributes(base,character,inputs,qualificationLevel,policy,normalSkills);
}
} // namespace dnf
