#include "dnf/speed_attributes.hpp"
#include "dnf/progression.hpp"
#include "dnf/character_controller.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
void issue(CharacterSpeeds &out, const char *kind, const char *severity, Json details = Json::object()) {
    details["kind"] = kind; details["severity"] = severity; out.diagnostics.push_back(std::move(details));
}
float add32(float a, float b) { volatile float result = a + b; return result; }
bool i32(const Json &value, int &number) {
    if (!value.is_number_integer() ||
        (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(std::numeric_limits<int32_t>::max()))) return false;
    const int64_t raw = value.get<int64_t>();
    if (raw < std::numeric_limits<int32_t>::min() || raw > std::numeric_limits<int32_t>::max()) return false;
    number = int(raw); return true;
}
bool speedTag(const std::string &tag) {
    return tag == "[attack speed]" || tag == "[cast speed]" || tag == "[move speed]" ||
           tag == "[x move dash speed]" || tag == "[y move dash speed]";
}
bool relatedSpeedTag(const std::string &tag) {
    return tag.find("attack speed") != std::string::npos || tag.find("cast speed") != std::string::npos ||
           tag.find("move speed") != std::string::npos || tag.find("move dash speed") != std::string::npos;
}
SourceRef fieldRef(const EquippedSpeedSource &item, size_t ordinal) {
    const auto &field = item.source.fields.at(ordinal);
    const auto end = ordinal + 1 < item.source.fields.size() ? item.source.fields[ordinal+1].offset : item.source.rawBytes.size();
    SourceRef ref;
    const auto text = [&](const char *key, const std::string &fallback) {
        return item.source.source.is_object() && item.source.source.contains(key) && item.source.source.at(key).is_string() ?
            item.source.source.at(key).get<std::string>() : fallback;
    };
    ref.packageIdentity = text("package_identity",{});
    ref.memberPath = item.source.path; ref.memberSha256 = sha256(item.source.rawBytes);
    ref.literalPath = text("literal_path",item.source.path);
    ref.byteOffset = field.offset; ref.byteLength = end >= field.offset ? end - field.offset : 0;
    ref.ordinal = ordinal; ref.scope = "equipment:instance=" + std::to_string(item.instanceUid) + ":slot=" + item.equippedSlot;
    return ref;
}
Json candidates(const EquippedSpeedSource &item, const std::string &tag) {
    Json result = Json::array();
    for (size_t i = 0; i < item.source.fields.size(); ++i) if (normalize(item.source.fields[i].tag) == tag)
        result.push_back({{"values",item.source.fields[i].values},{"source",fieldRef(item,i).json()}});
    return result;
}
struct Scalar { bool valid = true, present = false; float value = 0; Json selection; };
Scalar scalar(CharacterSpeeds &out, const EquippedSpeedSource &item, const std::string &tag) {
    Scalar result; result.selection = candidates(item,tag);
    if (result.selection.empty()) return result;
    result.present = true;
    if (result.selection.size() != 1) result.valid = false;
    else {
        const auto &values = result.selection[0].at("values");
        if (!values.is_array() || values.size() != 1 || !values[0].is_number()) result.valid = false;
        else {
            const auto &value = values[0]; int unused = 0;
            if (value.is_number_integer() && !i32(value,unused)) result.valid = false;
            const double number = value.get<double>();
            if (!std::isfinite(number) || std::abs(number) > std::numeric_limits<float>::max()) result.valid = false;
            if (result.valid) result.value = float(number);
        }
    }
    if (!result.valid) issue(out,"invalid_equipment_speed_scalar","error",{
        {"instance_uid",item.instanceUid},{"path",item.source.path},{"tag",tag},{"candidates",result.selection}});
    return result;
}
int integerField(CharacterSpeeds &out, const EquippedSpeedSource &item, const std::string &tag, int fallback) {
    const auto values = candidates(item,tag);
    if (values.empty()) return fallback;
    int number = 0;
    if (values.size() != 1 || !values[0]["values"].is_array() || values[0]["values"].size() != 1 ||
        !i32(values[0]["values"][0],number) || number < 0) {
        issue(out,"invalid_equipment_qualification_scalar","error",{{"instance_uid",item.instanceUid},{"tag",tag},{"candidates",values}});
        return -1;
    }
    return number;
}
void validateSource(CharacterSpeeds &out, const EquippedSpeedSource &item) {
    const auto &script = item.source;
    if (script.path.empty() || !script.source.is_object() || script.rawBytes.size() < 2 || (script.rawBytes.size()-2)%5) {
        issue(out,"invalid_equipment_source","error",{{"instance_uid",item.instanceUid},{"path",script.path}});
        return;
    }
    for (const char *key : {"package_identity","literal_path","member_sha256"})
        if (script.source.contains(key) && !script.source.at(key).is_string())
            issue(out,"invalid_equipment_source_identity","error",{{"instance_uid",item.instanceUid},{"field",key}});
    if (script.source.contains("member_sha256") && script.source.at("member_sha256").is_string() &&
        script.source.at("member_sha256") != sha256(script.rawBytes))
        issue(out,"equipment_speed_member_hash_mismatch","error",{{"instance_uid",item.instanceUid}});
    size_t previous = 0;
    bool conditional = false;
    for (size_t i = 0; i < script.fields.size(); ++i) {
        const auto &field = script.fields[i]; const auto tag = normalize(field.tag);
        if (!field.values.is_array()) issue(out,"invalid_equipment_field_payload","error",{
            {"instance_uid",item.instanceUid},{"ordinal",i},{"tag",field.tag},{"values",field.values}});
        if (field.offset < 2 || (field.offset-2)%5 || field.offset <= previous ||
            field.offset > script.rawBytes.size() || script.rawBytes.size()-field.offset < 5)
            issue(out,"invalid_equipment_field_span","error",{{"instance_uid",item.instanceUid},{"ordinal",i},{"offset",field.offset}});
        previous = field.offset;
        // Explicit conditional sections are not interpreted as permanent
        // modifiers. Remaining scopes stay unknown instead of guessed open/
        // close semantics; later recognized speed fields fail closed.
        if (tag == "[if]" || tag == "[then]" || tag.find("[change status") == 0 ||
            tag == "[equipment option]" || tag == "[ability]" || tag == "[special effect]") conditional = true;
        if (conditional && speedTag(tag)) issue(out,"conditional_equipment_speed_unresolved","error",{
            {"instance_uid",item.instanceUid},{"tag",field.tag},{"ordinal",i}});
        if (!speedTag(tag) && relatedSpeedTag(tag)) issue(out,"unsupported_equipment_speed_field","error",{
            {"instance_uid",item.instanceUid},{"tag",field.tag},{"values",field.values},{"ordinal",i}});
        if (tag.find("[usable ") == 0 && tag != "[usable job]")
            issue(out,"unsupported_equipment_qualification","error",{
                {"instance_uid",item.instanceUid},{"tag",field.tag},{"values",field.values},{"ordinal",i}});
        if (conditional && field.values.is_array()) for (const auto &value : field.values)
            if (value.is_string() && relatedSpeedTag(normalize(value.get<std::string>())))
                issue(out,"conditional_equipment_speed_operand_unresolved","error",{
                    {"instance_uid",item.instanceUid},{"tag",field.tag},{"values",field.values},{"ordinal",i}});
    }
}
std::string hex(const Bytes &bytes) {
    static constexpr char digits[] = "0123456789abcdef";
    std::string result; result.reserve(bytes.size()*2);
    for (const auto byte : bytes) { result += digits[byte>>4]; result += digits[byte&15]; }
    return result;
}
} // namespace

CharacterSpeedPolicy CharacterSpeedPolicy::inferredFlatEquipmentV1() { return {"inferred-flat-equipment-speed-v1"}; }
bool CharacterSpeeds::usable() const {
    if (policy != "inferred-flat-equipment-speed-v1") return false;
    for (const auto &entry : diagnostics) if (entry.value("severity",std::string()) == "error") return false;
    for (const float value : {attackPerMille,castPerMille,movePerMille,dashXRatio,dashYRatio})
        if (!std::isfinite(value) || value <= 0) return false;
    return true;
}
Json CharacterSpeeds::snapshot(bool includeSource) const {
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
    return {{"usable",usable()},{"identity",identity.json()},{"level",level},
        {"qualification_level",qualificationLevel},{"policy",policy},
        {"classification","inferred CHR + EQU speed groups; final native object-speed production is not proven"},
        {"attack_per_mille",attackPerMille},{"cast_per_mille",castPerMille},{"move_per_mille",movePerMille},
        {"dash_x_ratio",dashXRatio},{"dash_y_ratio",dashYRatio},{"base_source",baseSource},
        {"equipment_sources",sources},{"trace",trace},{"diagnostics",diagnostics},
        {"consumers",{{"ani_percent_conversion_applied",false},{"pixels_per_second_conversion_applied",false},
                      {"str_int_conversion_applied",false},{"playable_identity_authorized",false}}}};
}
CharacterSpeeds evaluateCharacterSpeeds(const CharacterBaseAttributes &base,
    const CharacterDefinition &character, const std::vector<EquippedSpeedSource> &equipment,
    const CharacterSpeedPolicy &policy) {
    return evaluateCharacterSpeeds(base,character,equipment,base.level,policy);
}
CharacterSpeeds evaluateCharacterSpeeds(const CharacterBaseAttributes &base,
    const CharacterDefinition &character, const std::vector<EquippedSpeedSource> &equipment,
    int qualificationLevel, const CharacterSpeedPolicy &policy) {
    CharacterSpeeds out; out.identity = base.identity; out.level = base.level;
    out.qualificationLevel = qualificationLevel; out.policy = policy.id;
    out.baseSource = base.source; out.equipmentSources = equipment;
    if (policy.id != "inferred-flat-equipment-speed-v1") {
        issue(out,"speed_policy_not_enabled","error"); return out;
    }
    if (!base.usable() || base.identity.jobId != character.registration.id) {
        issue(out,"unavailable_character_speed_base","error"); return out;
    }
    const bool qualificationLevelValid = qualificationLevel >= 1 && qualificationLevel <= 99;
    if (!qualificationLevelValid)
        issue(out,"invalid_equipment_qualification_level","error",{{"qualification_level",qualificationLevel}});
    const std::pair<ChrAttribute,float *> bases[] = {{ChrAttribute::AttackSpeed,&out.attackPerMille},
        {ChrAttribute::CastSpeed,&out.castPerMille},{ChrAttribute::MoveSpeed,&out.movePerMille}};
    for (const auto &[attribute,destination] : bases) {
        const auto found = base.attributes.find(attribute);
        if (found == base.attributes.end() || !found->second.usable() || found->second.unit != "chr_per_mille_base_1000" ||
            !std::isfinite(found->second.value) || found->second.value <= 0) {
            issue(out,"invalid_character_speed_base","error",{{"attribute",chrAttributeName(attribute)}});
        } else {
            *destination = found->second.value;
            out.trace.push_back({{"stage","chr_base"},{"attribute",chrAttributeName(attribute)},
                {"unit",found->second.unit},{"value",*destination},{"source_trace",found->second.trace}});
        }
    }
    issue(out,"speed_group_policy","info",{{"classification","inferred"},
        {"flat_operation","CHR absolute per-mille + sum equipped flat per-mille points"},
        {"dash_operation","independent x/y ratio = 1 + sum equipped ratio deltas"},
        {"arithmetic","float32 additions in ascending persistent instance UID, then source field order"},
        {"units_basis","charactersample.chr:44-46; equipmentsample.equ:219-223 (CP949)"},
        {"unverified","current-1031 final grouping/order; broken-item speed effects; dash cross-item stacking"},
        {"missing_minimum_level_default",1},{"missing_durability_default",0},
        {"base_level",base.level},{"equipment_qualification_level",qualificationLevel}});
    std::set<int64_t> uids; std::set<std::string> slots;
    auto sorted = equipment;
    std::stable_sort(sorted.begin(),sorted.end(),[](const auto &a,const auto &b){return a.instanceUid < b.instanceUid;});
    for (const auto &item : sorted) {
        const size_t previousDiagnostics = out.diagnostics.size();
        if (item.instanceUid <= 0 || !uids.insert(item.instanceUid).second || item.equippedSlot.empty() || !slots.insert(item.equippedSlot).second)
            issue(out,"invalid_equipped_speed_ownership","error",{{"instance_uid",item.instanceUid},{"slot",item.equippedSlot}});
        validateSource(out,item);
        if (base.source.is_object() && base.source.contains("provenance") && base.source.at("provenance").is_object()) {
            const auto &provenance = base.source.at("provenance");
            if (provenance.contains("package_identity") && provenance.at("package_identity").is_string() &&
                (!item.source.source.is_object() || !item.source.source.contains("package_identity") ||
                 item.source.source.at("package_identity") != provenance.at("package_identity")))
                issue(out,"equipment_speed_package_mismatch","error",{{"instance_uid",item.instanceUid}});
        }
        const auto type = candidates(item,"[equipment type]");
        if (type.size() != 1 || !type[0]["values"].is_array() || type[0]["values"].empty() ||
            !type[0]["values"][0].is_string() || type[0]["values"][0] != item.equippedSlot)
            issue(out,"equipment_speed_slot_mismatch","error",{{"instance_uid",item.instanceUid},{"slot",item.equippedSlot},{"candidates",type}});
        const auto restriction = equipmentJobRestriction(character,item.source);
        if (restriction.gate != EquipmentJobGate::Allowed)
            issue(out,"equipment_speed_job_not_qualified","error",{{"instance_uid",item.instanceUid},{"path",item.source.path}});
        const int minimumLevel = integerField(out,item,"[minimum level]",1);
        if (minimumLevel < 1 || qualificationLevel < minimumLevel)
            issue(out,"equipment_speed_level_not_qualified","error",{{"instance_uid",item.instanceUid},
                {"minimum_level",minimumLevel},{"qualification_level",qualificationLevel}});
        const int maximumDurability = integerField(out,item,"[durability]",0);
        if (item.currentDurability < 0 || maximumDurability < 0 || item.currentDurability > maximumDurability)
            issue(out,"invalid_equipment_speed_durability","error",{{"instance_uid",item.instanceUid},{"current",item.currentDurability},{"maximum",maximumDurability}});
        const bool broken = maximumDurability > 0 && item.currentDurability == 0;
        if (broken) issue(out,"broken_equipment_speed_inactive","info",{{"instance_uid",item.instanceUid},{"classification","inferred broken-item stat policy"}});
        bool active = !broken && qualificationLevelValid;
        for (size_t i = previousDiagnostics; i < out.diagnostics.size(); ++i)
            if (out.diagnostics[i].value("severity",std::string()) == "error") active = false;
        for (const auto &[tag,destination] : std::vector<std::pair<std::string,float *>>{
                {"[attack speed]",&out.attackPerMille},{"[cast speed]",&out.castPerMille},{"[move speed]",&out.movePerMille},
                {"[x move dash speed]",&out.dashXRatio},{"[y move dash speed]",&out.dashYRatio}}) {
            const auto value = scalar(out,item,tag);
            const float before = *destination;
            bool applied = value.valid && active;
            if (applied) {
                const float after = add32(before,value.value);
                if (std::isfinite(after)) *destination = after;
                else {
                    applied = false;
                    issue(out,"equipment_speed_arithmetic_overflow","error",{{"instance_uid",item.instanceUid},
                        {"tag",tag},{"before",before},{"operand",value.value}});
                }
            }
            out.trace.push_back({{"stage","equipment_flat_group"},{"instance_uid",item.instanceUid},{"tag",tag},
                {"unit",tag.find("dash") == std::string::npos ? "per_mille_points" : "dimensionless_ratio_delta"},
                {"present",value.present},{"valid",value.valid},{"active",active},{"applied",applied},{"before",before},
                {"operand",value.value},{"after",*destination},{"candidates",value.selection},{"classification","inferred additive group"}});
        }
    }
    for (const auto &[name,value] : std::vector<std::pair<const char *,float>>{
            {"attack_per_mille",out.attackPerMille},{"cast_per_mille",out.castPerMille},{"move_per_mille",out.movePerMille},
            {"dash_x_ratio",out.dashXRatio},{"dash_y_ratio",out.dashYRatio}})
        if (!std::isfinite(value) || value <= 0) issue(out,"invalid_final_character_speed","error",{{"attribute",name}});
    return out;
}
CharacterSpeeds evaluateCharacterSpeeds(const CharacterBaseAttributes &base,
    const Progression &progression, const CharacterDefinition &character, const CharacterSpeedPolicy &policy) {
    std::vector<EquippedSpeedSource> inputs;
    try {
        const auto &inventory = progression.state.at("inventory"), &equipped = progression.state.at("equipped");
        if (!inventory.is_array() || !equipped.is_object()) throw std::runtime_error("Invalid equipment inventory/slot map");
        for (auto slot = equipped.begin(); slot != equipped.end(); ++slot) {
            int uid = 0;
            if (!i32(slot.value(),uid) || uid <= 0) throw std::runtime_error("Invalid equipped inventory UID");
            const Json *selected = nullptr;
            for (const auto &entry : inventory) {
                int candidate = 0;
                if (!entry.is_object() || !entry.contains("uid") || !i32(entry.at("uid"),candidate)) throw std::runtime_error("Invalid inventory UID");
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
        auto out = evaluateCharacterSpeeds(base,character,inputs,progression.level(),policy);
        issue(out,"equipped_speed_collection_failed","error",{{"reason",error.what()}});
        return out;
    }
    return evaluateCharacterSpeeds(base,character,inputs,progression.level(),policy);
}
} // namespace dnf
