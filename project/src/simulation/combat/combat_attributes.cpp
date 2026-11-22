#include "dnf/combat_attributes.hpp"
#include "dnf/attack_status.hpp"
#include "dnf/character_controller.hpp"
#include "dnf/progression.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *policyId = "inferred-equipment-combat-stat-v1";
bool errors(const Json &list, size_t begin = 0) {
    for (size_t i=begin;i<list.size();++i)
        if (list[i].value("severity",std::string())=="error") return true;
    return false;
}
void issue(CombatAttributeSnapshot &out, const char *kind, const char *severity, Json details=Json::object()) {
    details["kind"]=kind; details["severity"]=severity; out.diagnostics.push_back(std::move(details));
}
bool integer(const Json &value, int &out) {
    if (!value.is_number_integer() || (value.is_number_unsigned() && value.get<uint64_t>()>uint64_t(std::numeric_limits<int32_t>::max()))) return false;
    const auto n=value.get<int64_t>();
    if (n<std::numeric_limits<int32_t>::min() || n>std::numeric_limits<int32_t>::max()) return false;
    out=int(n); return true;
}
bool real(const Json &value, bool intOnly, float &out) {
    if (!value.is_number()) return false;
    int unused=0;
    if ((intOnly || value.is_number_integer()) && !integer(value,unused)) return false;
    const auto n=value.get<double>();
    if (!std::isfinite(n) || std::abs(n)>double(std::numeric_limits<float>::max())) return false;
    out=float(n); return true;
}
float add32(float a,float b) { volatile float r=a+b; return r; }
float mul32(float a,float b) { volatile float r=a*b; return r; }
std::string meta(const Json &j,const char *key,const std::string &fallback={}) {
    return j.is_object() && j.contains(key) && j.at(key).is_string()?j.at(key).get<std::string>():fallback;
}
std::string hex(const Bytes &bytes) {
    static constexpr char digits[]="0123456789abcdef";
    std::string result; result.reserve(bytes.size()*2);
    for (const auto n:bytes) { result+=digits[n>>4]; result+=digits[n&15]; }
    return result;
}
SourceRef reference(const Script &source,size_t ordinal,const std::string &scope) {
    const auto &field=source.fields.at(ordinal);
    const auto end=ordinal+1<source.fields.size()?source.fields[ordinal+1].offset:source.rawBytes.size();
    SourceRef ref;
    ref.packageIdentity=meta(source.source,"package_identity"); ref.memberPath=normalize(source.path);
    ref.literalPath=meta(source.source,"literal_path",source.path); ref.memberSha256=sha256(source.rawBytes);
    ref.byteOffset=field.offset; ref.byteLength=end>=field.offset?end-field.offset:0; ref.ordinal=ordinal; ref.scope=scope;
    return ref;
}
Json ref(const EquippedAttributeSource &item,size_t ordinal) {
    return reference(item.source,ordinal,"equipment-combat:uid="+std::to_string(item.instanceUid)+":slot="+item.equippedSlot).json();
}
Json candidates(const EquippedAttributeSource &item,const std::string &tag) {
    Json result=Json::array();
    for (size_t i=0;i<item.source.fields.size();++i) if (normalize(item.source.fields[i].tag)==tag)
        result.push_back({{"source",ref(item,i)},{"values",item.source.fields[i].values}});
    return result;
}
struct Operand { bool present=false,valid=true; float selected=0; Json values=Json::array(), sources=Json::array(); };
Operand operand(CombatAttributeSnapshot &out,const EquippedAttributeSource &item,const std::string &tag,
                bool pair=false,bool integerOnly=true) {
    Operand r; r.sources=candidates(item,tag); r.present=!r.sources.empty();
    if (!r.present) return r;
    if (r.sources.size()!=1) r.valid=false;
    else {
        r.values=r.sources[0]["values"];
        if (!r.values.is_array() || r.values.size()!=(pair?2u:1u)) r.valid=false;
        else for (size_t i=0;i<r.values.size();++i) {
            float value=0;
            if (!real(r.values[i],integerOnly,value)) r.valid=false;
            else if (i==0) r.selected=value;
        }
    }
    if (!r.valid) issue(out,"invalid_combat_equipment_operand","error",{{"instance_uid",item.instanceUid},
        {"tag",tag},{"arity",pair?2:1},{"integer_required",integerOnly},{"candidates",r.sources}});
    if (r.valid && tag=="[separate rate]" && r.selected<=0) {
        r.valid=false;
        issue(out,"invalid_combat_independent_rate","error",{{"instance_uid",item.instanceUid},{"candidates",r.sources}});
    }
    return r;
}
int qualification(CombatAttributeSnapshot &out,const EquippedAttributeSource &item,const char *tag,int fallback) {
    const auto rows=candidates(item,tag); int n=0;
    if (rows.empty()) return fallback;
    if (rows.size()!=1 || !rows[0]["values"].is_array() || rows[0]["values"].size()!=1 ||
        !integer(rows[0]["values"][0],n) || n<0) {
        issue(out,"invalid_combat_equipment_qualification","error",{{"instance_uid",item.instanceUid},{"tag",tag},{"candidates",rows}});
        return -1;
    }
    return n;
}
struct Target { const char *tag,*name,*unit; float *value; bool pair=false,integerOnly=true,multiply=false; };
std::vector<Target> targets(CombatAttributeSnapshot &out) {
    std::vector<Target> result={
        {"[physical attack]","strength","primary_stat_points",&out.strength},
        {"[physical defense]","vitality","primary_stat_points",&out.vitality},
        {"[magical attack]","intelligence","primary_stat_points",&out.intelligence},
        {"[magical defense]","spirit","primary_stat_points",&out.spirit},
        {"[equipment physical attack]","physical_attack","equipment_attack_points",&out.physicalAttack,true},
        {"[equipment magical attack]","magical_attack","equipment_attack_points",&out.magicalAttack,true},
        {"[equipment physical defense]","equipment_physical_defense","equipment_defense_points",&out.equipmentPhysicalDefense,true},
        {"[equipment magical defense]","equipment_magical_defense","equipment_defense_points",&out.equipmentMagicalDefense,true},
        {"[separate attack]","independent_attack","independent_attack_points",&out.independentAttack,true},
        {"[separate rate]","independent_rate","dimensionless_factor",&out.independentRate,true,false,true},
        {"[physical absolute damage]","physical_absolute_damage","damage_points",&out.physicalAbsoluteDamage},
        {"[magical absolute damage]","magical_absolute_damage","damage_points",&out.magicalAbsoluteDamage},
        {"[physical absolute defense]","physical_absolute_defense_percent","percentage_points",&out.physicalAbsoluteDefensePercent,false,false},
        {"[magical absolute defense]","magical_absolute_defense_percent","percentage_points",&out.magicalAbsoluteDefensePercent,false,false},
        {"[physical critical hit]","physical_critical_bonus_percent","percentage_points",&out.physicalCriticalBonusPercent,false,false},
        {"[magical critical hit]","magical_critical_bonus_percent","percentage_points",&out.magicalCriticalBonusPercent,false,false},
        {"[stuck]","attack_miss_delta_percent","percentage_points",&out.attackMissDeltaPercent,false,false},
        {"[stuck resistance]","evasion_per_mille","per_mille_points",&out.evasionPerMille,false,false}
    };
    static const char *attack[]={"[fire attack]","[water attack]","[dark attack]","[light attack]"};
    static const char *resist[]={"[fire resistance]","[water resistance]","[dark resistance]","[light resistance]"};
    static const char *attackName[]={"fire_attack","water_attack","dark_attack","light_attack"};
    static const char *resistName[]={"fire_resistance","water_resistance","dark_resistance","light_resistance"};
    for (size_t i=0;i<4;++i) {
        result.push_back({attack[i],attackName[i],"element_points",&out.elementalAttack[i]});
        result.push_back({resist[i],resistName[i],"element_points",&out.elementalResistance[i]});
    }
    return result;
}
bool delegated(const std::string &tag) {
    static const std::set<std::string> tags={"[hp max]","[mp max]","[mp max rate]","[attack speed]","[cast speed]",
        "[move speed]","[x move dash speed]","[y move dash speed]","[weight]","[inventory limit]","[cool time]"};
    if(tags.count(tag)!=0 || tag=="[all activestatus resistance]") return true;
    for(const auto name:statusResistanceOrder()) if(tag=="["+std::string(name)+" resistance]") return true;
    return false;
}
bool combatRelated(std::string tag) {
    tag=normalize(std::move(tag)); std::replace(tag.begin(),tag.end(),'_',' ');
    for (const auto *word:{"attack","defense","damage","critical","element","resistance","stuck","skill","status",
        "hit recovery","rigidity","push aside","lift up","drain","separate","aura","stat ","ability","super armor",
        "invincible","protect","poison","bleed","burn","freeze","stun","curse","blind","stone","sleep","confuse","hold"})
        if (tag.find(word)!=std::string::npos) return true;
    return false;
}
bool allZero(const Json &values) {
    if (!values.is_array() || values.empty()) return false;
    for (const auto &v:values) { float n=0; if (!real(v,false,n) || n!=0) return false; }
    return true;
}
void validateScript(CombatAttributeSnapshot &out,const Script &script,const std::string &package,const std::string &scope) {
    if (!script.source.is_object() || script.rawBytes.size()<2 || (script.rawBytes.size()-2)%5)
        issue(out,"invalid_combat_source","error",{{"path",script.path},{"scope",scope}});
    for (const auto *key:{"package_identity","literal_path","member_sha256"})
        if (script.source.is_object() && script.source.contains(key) && !script.source.at(key).is_string())
            issue(out,"invalid_combat_source_identity","error",{{"path",script.path},{"key",key}});
    if (package.empty() || meta(script.source,"package_identity")!=package)
        issue(out,"combat_source_package_mismatch","error",{{"path",script.path},{"expected",package},{"actual",meta(script.source,"package_identity")}});
    if (script.source.is_object() && script.source.contains("member_sha256") &&
        meta(script.source,"member_sha256")!=sha256(script.rawBytes))
        issue(out,"combat_source_member_hash_mismatch","error",{{"path",script.path}});
    size_t previous=0;
    for (size_t i=0;i<script.fields.size();++i) {
        const auto &field=script.fields[i];
        if (!field.values.is_array()) issue(out,"invalid_combat_source_payload","error",{{"path",script.path},{"ordinal",i}});
        if (field.offset<2 || (field.offset-2)%5 || field.offset<=previous || field.offset>script.rawBytes.size() ||
            script.rawBytes.size()-field.offset<5)
            issue(out,"invalid_combat_source_span","error",{{"path",script.path},{"ordinal",i},{"offset",field.offset}});
        previous=field.offset;
    }
}
void skillLevels(CombatAttributeSnapshot &out,const EquippedAttributeSource &item,const CharacterDefinition &character,size_t ordinal) {
    const auto &values=item.source.fields[ordinal].values;
    bool valid=values.is_array() && values.size()%3==0; bool applies=false;
    Json rows=Json::array();
    if (valid) for (size_t i=0;i<values.size();i+=3) {
        int skill=0,delta=0;
        if (!values[i].is_string() || !integer(values[i+1],skill) || skill<0 || !integer(values[i+2],delta)) { valid=false; break; }
        const auto job=normalize(values[i].get<std::string>());
        const bool matched=job==normalize(character.job) || job=="[all]";
        applies=applies || (matched && delta!=0);
        rows.push_back({{"job",job},{"skill",skill},{"delta",delta},{"matches_current_job",matched}});
    }
    if (!valid || applies) issue(out,valid?"combat_equipment_skill_level_consumer_required":"malformed_combat_equipment_skill_levels",
        "error",{{"instance_uid",item.instanceUid},{"source",ref(item,ordinal)},{"values",values},{"rows",rows}});
    out.trace.push_back({{"stage","equipment_skill_level_scope"},{"instance_uid",item.instanceUid},{"source",ref(item,ordinal)},
        {"valid",valid},{"matches_current_job",applies},{"rows",rows},{"consumer","nonzero current-job bonuses require skill-ledger adapter"}});
}
void checkEffects(CombatAttributeSnapshot &out,const EquippedAttributeSource &item,const CharacterDefinition &character) {
    std::set<std::string> consumed={"[all elemental resistance]","[elemental property]","[skill levelup]"};
    for (const auto &target:targets(out)) consumed.insert(target.tag);
    bool conditional=false;
    for (size_t i=0;i<item.source.fields.size();++i) {
        const auto &field=item.source.fields[i]; const auto tag=normalize(field.tag);
        if (tag.find("[usable ")==0 && tag!="[usable job]")
            issue(out,"unsupported_combat_equipment_qualification","error",{{"instance_uid",item.instanceUid},{"source",ref(item,i)},{"tag",tag},{"values",field.values}});
        if (tag=="[set item master]") {
            int master=0;
            if (!field.values.is_array() || field.values.size()!=1 || !integer(field.values[0],master) || master!=-1)
                issue(out,"combat_equipment_set_unresolved","error",{{"source",ref(item,i)},{"values",field.values}});
        } else if (tag=="[set item]" || tag=="[set name]" || tag=="[set ability]")
            issue(out,"combat_equipment_set_unresolved","error",{{"source",ref(item,i)},{"tag",tag},{"values",field.values}});
        if (tag=="[if]" || tag=="[then]" || tag=="[multiple then]" || tag=="[stat]" || tag=="[stat by condition]" ||
            tag=="[item aura]" || tag=="[avatar select ability]" || tag=="[level linear ability]" || tag=="[all skill item]" ||
            tag=="[equipment option]" || tag=="[ability]" || tag=="[special effect]" || tag.find("[change status")==0) {
            conditional=true;
            issue(out,"combat_equipment_effect_consumer_required","error",{{"source",ref(item,i)},{"tag",tag},{"values",field.values}});
        }
        if (conditional && consumed.count(tag)) issue(out,"conditional_combat_equipment_operand","error",{{"source",ref(item,i)},{"tag",tag}});
        if (tag=="[skill levelup]") skillLevels(out,item,character,i);
        if (!tag.empty() && tag.rfind("[/",0)==0) continue;
        // This empty EQU marker controls a reinforcement-service option; it
        // does not grant actor protection or combat invincibility.
        if (tag=="[possible kiri protect]") continue;
        // Maximum durability is already validated by qualification() and
        // compared with instance currentDurability before this scan; broken
        // durable items disable every combat group below. Keep this exact
        // metadata tag out of the broad "ability" effect-name matcher.
        if (tag=="[durability]") {
            out.trace.push_back({{"stage","consumed_equipment_metadata"},{"source",ref(item,i)},
                {"instance_uid",item.instanceUid},{"tag",tag},{"values",field.values},{"current_durability",item.currentDurability},
                {"consumer","combat durability qualification and broken-item activation"}});
            continue;
        }
        if (delegated(tag)) {
            out.trace.push_back({{"stage","delegated_equipment_field"},{"source",ref(item,i)},{"tag",tag},{"values",field.values},
                {"consumer",tag=="[weight]" || tag=="[inventory limit]"?"inventory burden service":tag=="[cool time]"?"equip transaction":"resource/speed evaluator"}});
        } else if (!consumed.count(tag) && combatRelated(tag)) {
            static const std::set<std::string> neutralDeltas={"[physical damage reduce]","[magical damage reduce]",
                "[hit recovery]","[rigidity]","[push aside]","[lift up]"};
            const bool neutral=neutralDeltas.count(tag) && allZero(field.values);
            issue(out,neutral?"neutral_unconsumed_combat_field":"unsupported_combat_equipment_field",neutral?"info":"error",
                {{"source",ref(item,i)},{"tag",tag},{"values",field.values},{"zero_effect_only",neutral}});
        }
    }
}
void add(CombatAttributeSnapshot &out,float &target,float delta,const Json &context) {
    const float computed=add32(target,delta);
    if (!std::isfinite(computed)) issue(out,"combat_attribute_arithmetic_overflow","error",context);
    else target=computed;
}
void defenseFactors(CombatAttributeSnapshot &out,const CombatAttributePolicy &policy,const std::string &package) {
    out.policyDetails["derive_primary_defense"]=policy.derivePrimaryDefense;
    if (!policy.derivePrimaryDefense) {
        out.trace.push_back({{"stage","primary_defense_conversion"},{"enabled",false},{"operation","equipment defense only"},
            {"classification","explicit policy exclusion; does not establish native primary-defense behavior"}});
        return;
    }
    validateScript(out,policy.damageConstants,package,"primary-defense-constant-candidate");
    if (normalize(policy.damageConstants.path)!="etc/etcparameter.etc")
        issue(out,"unexpected_combat_constant_path","error",{{"path",policy.damageConstants.path}});
    std::vector<size_t> found;
    for (size_t i=0;i<policy.damageConstants.fields.size();++i)
        if (normalize(policy.damageConstants.fields[i].tag)=="[damage fomula constant]") found.push_back(i);
    float physical=0,magical=0;
    if (found.size()!=1) { issue(out,"ambiguous_combat_defense_constants","error",{{"count",found.size()}}); return; }
    const auto &values=policy.damageConstants.fields[found[0]].values;
    if (!values.is_array() || values.size()!=27 || !real(values[22],false,physical) || !real(values[23],false,magical) || physical<0 || magical<0) {
        issue(out,"invalid_combat_defense_constants","error",{{"source",reference(policy.damageConstants,found[0],"primary-defense-constant-candidate").json()},
            {"expected_count",27},{"values",values}}); return;
    }
    out.vitalityDefenseFactor=physical; out.spiritDefenseFactor=magical;
    out.policyDetails["primary_defense_conversion"]={{"classification","inferred"},{"physical_position",22},{"magical_position",23},
        {"physical_factor",physical},{"magical_factor",magical},{"source",reference(policy.damageConstants,found[0],"primary-defense-constant-candidate").json()},
        {"candidate_mapping","rednf importEtcParameterScriptForServer; native PC consumer unverified"},{"unconsumed_tail",values[26]}};
}
} // namespace

CombatAttributePolicy CombatAttributePolicy::inferredEquipmentCombatStatV1(const Script &constants) {
    CombatAttributePolicy result; result.id=policyId; result.damageConstants=constants; return result;
}
bool CombatAttributeSnapshot::usable() const {
    if (policy!=policyId || level<1 || level>99 || qualificationLevel<1 || qualificationLevel>99 || !pureChr.usable() || errors(diagnostics)) return false;
    for (const auto value:{strength,vitality,intelligence,spirit,physicalAttack,magicalAttack,equipmentPhysicalDefense,equipmentMagicalDefense,
        physicalDefense,magicalDefense,independentAttack,independentRate,physicalAbsoluteDamage,magicalAbsoluteDamage,
        physicalAbsoluteDefensePercent,magicalAbsoluteDefensePercent,physicalCriticalBonusPercent,magicalCriticalBonusPercent,
        attackMissDeltaPercent,evasionPerMille,vitalityDefenseFactor,spiritDefenseFactor})
        if (!std::isfinite(value)) return false;
    for (size_t i=0;i<4;++i) if (!std::isfinite(elementalAttack[i]) || !std::isfinite(elementalResistance[i])) return false;
    return strength>=0 && vitality>=0 && intelligence>=0 && spirit>=0 && physicalAttack>=0 && magicalAttack>=0 &&
        physicalDefense>=0 && magicalDefense>=0 && independentAttack>=0 && independentRate>0 &&
        physicalAbsoluteDamage>=0 && magicalAbsoluteDamage>=0 &&
        physicalAbsoluteDefensePercent>=0 && physicalAbsoluteDefensePercent<=100 &&
        magicalAbsoluteDefensePercent>=0 && magicalAbsoluteDefensePercent<=100 && weaponElement>=0 && weaponElement<=4;
}
Json CombatAttributeSnapshot::snapshot(bool includeSource) const {
    Json sources=Json::array();
    for (const auto &item:equipmentSources) {
        Json fields=Json::array();
        for (size_t i=0;i<item.source.fields.size();++i) fields.push_back({{"ordinal",i},{"offset",item.source.fields[i].offset},
            {"tag",item.source.fields[i].tag},{"values",item.source.fields[i].values}});
        Json source={{"instance_uid",item.instanceUid},{"equipped_slot",item.equippedSlot},{"current_durability",item.currentDurability},
            {"path",item.source.path},{"member_sha256",sha256(item.source.rawBytes)},{"provenance",item.source.source},{"fields",fields}};
        if (includeSource) { source["raw_bytes_hex"]=hex(item.source.rawBytes); source["ordered_tokens"]=item.source.tokens; }
        sources.push_back(std::move(source));
    }
    Json constants={{"path",damageConstants.path},{"provenance",damageConstants.source},{"member_sha256",sha256(damageConstants.rawBytes)},
        {"fields",Json::array()}};
    for (size_t i=0;i<damageConstants.fields.size();++i)
        if (includeSource || normalize(damageConstants.fields[i].tag)=="[damage fomula constant]")
            constants["fields"].push_back({{"ordinal",i},{"offset",damageConstants.fields[i].offset},
                {"tag",damageConstants.fields[i].tag},{"values",damageConstants.fields[i].values}});
    if (includeSource) { constants["raw_bytes_hex"]=hex(damageConstants.rawBytes); constants["ordered_tokens"]=damageConstants.tokens; }
    return {{"usable",usable()},{"policy",policy},{"classification","inferred combat attributes; native final damage unproven"},
        {"identity",identity.json()},{"effective_level",level},{"qualification_level",qualificationLevel},{"pure_chr",pureChr.snapshot()},
        {"strength",strength},{"vitality",vitality},{"intelligence",intelligence},{"spirit",spirit},
        {"physical_attack",physicalAttack},{"magical_attack",magicalAttack},{"equipment_physical_defense",equipmentPhysicalDefense},
        {"equipment_magical_defense",equipmentMagicalDefense},{"physical_defense",physicalDefense},{"magical_defense",magicalDefense},
        {"independent_attack",independentAttack},{"independent_rate",independentRate},{"physical_absolute_damage",physicalAbsoluteDamage},
        {"magical_absolute_damage",magicalAbsoluteDamage},{"physical_absolute_defense_percent",physicalAbsoluteDefensePercent},
        {"magical_absolute_defense_percent",magicalAbsoluteDefensePercent},{"physical_critical_bonus_percent",physicalCriticalBonusPercent},
        {"magical_critical_bonus_percent",magicalCriticalBonusPercent},{"attack_miss_delta_percent",attackMissDeltaPercent},{"evasion_per_mille",evasionPerMille},
        {"elemental_attack",elementalAttack},{"elemental_resistance",elementalResistance},{"weapon_element",weaponElement},
        {"policy_details",policyDetails},{"damage_constants",constants},{"equipment_sources",sources},{"trace",trace},{"diagnostics",diagnostics},
        {"scope","attribute inputs only; skill/passive/status modifiers and hit/damage consumers are separate"}};
}

CombatAttributeSnapshot evaluateCombatAttributes(const CharacterBaseAttributes &base,const CharacterDefinition &character,
    const std::vector<EquippedAttributeSource> &equipment,int qualificationLevel,const CombatAttributePolicy &policy) {
    CombatAttributeSnapshot out; out.identity=base.identity; out.level=base.level; out.qualificationLevel=qualificationLevel;
    out.policy=policy.id; out.pureChr=base; out.equipmentSources=equipment; out.damageConstants=policy.damageConstants;
    if (policy.id!=policyId) { issue(out,"combat_attribute_policy_not_enabled","error"); return out; }
    if (!base.usable() || base.identity.jobId!=character.registration.id || !base.source.is_object() ||
        base.source.contains("equipment_resource_evaluation") || base.source.contains("combat_attribute_evaluation")) {
        issue(out,"combat_attributes_require_pure_chr","error"); return out;
    }
    if (qualificationLevel<1 || qualificationLevel>99) issue(out,"invalid_combat_qualification_level","error");
    const auto package=base.source.contains("provenance")?meta(base.source["provenance"],"package_identity"):std::string();
    if (package.empty()) issue(out,"missing_combat_base_package","error");
    const std::pair<ChrAttribute,float *> primary[]={
        {ChrAttribute::PhysicalAttack,&out.strength},{ChrAttribute::PhysicalDefense,&out.vitality},
        {ChrAttribute::MagicalAttack,&out.intelligence},{ChrAttribute::MagicalDefense,&out.spirit}};
    for (const auto &[attribute,destination]:primary) {
        const auto found=base.attributes.find(attribute);
        if (found==base.attributes.end() || !found->second.usable() || found->second.unit!="chr_base_coefficient" || !std::isfinite(found->second.value))
            issue(out,"invalid_combat_primary_coefficient","error",{{"attribute",chrAttributeName(attribute)}});
        else {
            *destination=found->second.value;
            out.trace.push_back({{"stage","inferred_chr_primary_mapping"},{"attribute",chrAttributeName(attribute)},
                {"value",*destination},{"source_trace",found->second.trace},{"unit","primary_stat_points"},{"classification","inferred"}});
        }
    }
    const ChrAttribute resist[]={ChrAttribute::FireResistance,ChrAttribute::WaterResistance,ChrAttribute::DarkResistance,ChrAttribute::LightResistance};
    for (size_t i=0;i<4;++i) {
        const auto found=base.attributes.find(resist[i]);
        if (found!=base.attributes.end()) {
            if (!found->second.usable() || found->second.unit!="source_resistance_points" || !std::isfinite(found->second.value))
                issue(out,"invalid_combat_base_resistance","error",{{"element",i}});
            else out.elementalResistance[i]=found->second.value;
        }
    }
    out.policyDetails={{"primary_mapping","CHR four coefficients -> strength/vitality/intelligence/spirit; source unchanged"},
        {"basis","equipmentsample.equ:159-166,237-239; CP949"},{"sample_sha256","9c0620fadb3c06cbc211ac21b2adbe3480288c7adbc3f99fae8e76ad43cf6b17"},
        {"mode","dungeon"},{"mode_index",0},{"arithmetic","UID-ordered float32 stored after each addition/multiplication"},
        {"independent_rate_group","multiply selected source factors, separately from independent attack flats; inferred"},
        {"broken_item_policy","positive max durability and current zero contributes no combat modifiers"},
        {"missing_minimum_level_default",1},{"missing_durability_default",0}};
    defenseFactors(out,policy,package);
    std::set<int64_t> uids; std::set<std::string> slots;
    auto sorted=equipment;
    std::stable_sort(sorted.begin(),sorted.end(),[](const auto &a,const auto &b){return a.instanceUid<b.instanceUid;});
    for (const auto &item:sorted) {
        const size_t start=out.diagnostics.size();
        if (item.instanceUid<=0 || !uids.insert(item.instanceUid).second || item.equippedSlot.empty() || !slots.insert(item.equippedSlot).second)
            issue(out,"invalid_combat_equipment_ownership","error",{{"instance_uid",item.instanceUid},{"slot",item.equippedSlot}});
        const auto path=normalize(item.source.path);
        if (path.rfind("equipment/",0)!=0 || path.size()<4 || path.substr(path.size()-4)!=".equ" ||
            path.find("/../")!=std::string::npos || path.find("/./")!=std::string::npos || path.find(':')!=std::string::npos)
            issue(out,"invalid_combat_equipment_path","error",{{"path",item.source.path}});
        validateScript(out,item.source,package,"equipped-combat-source");
        const auto types=candidates(item,"[equipment type]"), jobs=candidates(item,"[usable job]");
        if (types.size()!=1 || !types[0]["values"].is_array() || types[0]["values"].empty() || types[0]["values"][0]!=item.equippedSlot)
            issue(out,"combat_equipment_slot_mismatch","error",{{"instance_uid",item.instanceUid},{"candidates",types}});
        if (jobs.size()!=1 || !jobs[0]["values"].is_array() || equipmentJobRestriction(character,item.source).gate!=EquipmentJobGate::Allowed)
            issue(out,"combat_equipment_job_not_qualified","error",{{"instance_uid",item.instanceUid},{"candidates",jobs}});
        const int minimum=qualification(out,item,"[minimum level]",1), maximum=qualification(out,item,"[durability]",0);
        if (minimum<1 || qualificationLevel<minimum) issue(out,"combat_equipment_level_not_qualified","error",{{"instance_uid",item.instanceUid},
            {"minimum_level",minimum},{"qualification_level",qualificationLevel}});
        if (maximum<0 || item.currentDurability<0 || item.currentDurability>maximum)
            issue(out,"invalid_combat_equipment_durability","error",{{"instance_uid",item.instanceUid},{"current",item.currentDurability},{"maximum",maximum}});
        const bool broken=maximum>0 && item.currentDurability==0;
        if (broken) issue(out,"broken_combat_equipment_inactive","info",{{"instance_uid",item.instanceUid}});
        checkEffects(out,item,character);
        // Parse every recognized field before applying any part of this item.
        const auto fields=targets(out); std::vector<Operand> values;
        for (const auto &field:fields) values.push_back(operand(out,item,field.tag,field.pair,field.integerOnly));
        const auto allResistance=operand(out,item,"[all elemental resistance]");
        const auto elements=candidates(item,"[elemental property]"); int element=4;
        if (!elements.empty()) {
            static const std::vector<std::string> names={"[fire element]","[water element]","[dark element]","[light element]","[no element]"};
            if (elements.size()!=1 || !elements[0]["values"].is_array() || elements[0]["values"].size()!=1 || !elements[0]["values"][0].is_string())
                issue(out,"invalid_combat_weapon_element","error",{{"instance_uid",item.instanceUid},{"candidates",elements}});
            else {
                const auto literal=normalize(elements[0]["values"][0].get<std::string>());
                const auto found=std::find(names.begin(),names.end(),literal);
                if (found==names.end()) issue(out,"invalid_combat_weapon_element","error",{{"instance_uid",item.instanceUid},{"candidates",elements}});
                else element=int(found-names.begin());
                if (item.equippedSlot!="[weapon]" && element!=4)
                    issue(out,"nonweapon_combat_element_consumer_required","error",{{"instance_uid",item.instanceUid},{"candidates",elements}});
            }
        }
        const bool active=!broken && qualificationLevel>=1 && qualificationLevel<=99 && !errors(out.diagnostics,start);
        for (size_t i=0;i<fields.size();++i) {
            const auto &field=fields[i]; const auto &value=values[i]; const float before=*field.value;
            if (active && value.present && value.valid) {
                const float after=field.multiply?mul32(before,value.selected):add32(before,value.selected);
                if (!std::isfinite(after)) issue(out,"combat_attribute_arithmetic_overflow","error",{{"instance_uid",item.instanceUid},{"tag",field.tag}});
                else *field.value=after;
            }
            if (value.present) out.trace.push_back({{"stage","equipment_combat_group"},{"instance_uid",item.instanceUid},{"tag",field.tag},
                {"attribute",field.name},{"unit",field.unit},{"operation",field.multiply?"multiply":"add"},{"mode_index",field.pair?Json(0):Json()},
                {"active",active},{"valid",value.valid},{"before",before},{"operand",value.selected},{"after",*field.value},
                {"source_values",value.values},{"candidates",value.sources}});
        }
        if (allResistance.present) {
            for (size_t i=0;i<4;++i) {
                const float before=out.elementalResistance[i];
                if (active && allResistance.valid) add(out,out.elementalResistance[i],allResistance.selected,{{"element",i}});
                out.trace.push_back({{"stage","all_elemental_resistance"},{"instance_uid",item.instanceUid},{"element",i},{"active",active},
                    {"before",before},{"operand",allResistance.selected},{"after",out.elementalResistance[i]},{"candidates",allResistance.sources}});
            }
        }
        if (!elements.empty()) {
            const int before=out.weaponElement;
            if (active && element!=4) {
                if (out.weaponElement!=4 && out.weaponElement!=element) issue(out,"conflicting_combat_weapon_elements","error");
                else out.weaponElement=element;
            }
            out.trace.push_back({{"stage","weapon_element_selection"},{"instance_uid",item.instanceUid},{"active",active},
                {"before",before},{"selected",element},{"after",out.weaponElement},{"candidates",elements}});
        }
    }
    const float physicalPrimary=mul32(out.vitality,out.vitalityDefenseFactor), magicalPrimary=mul32(out.spirit,out.spiritDefenseFactor);
    out.physicalDefense=add32(out.equipmentPhysicalDefense,physicalPrimary);
    out.magicalDefense=add32(out.equipmentMagicalDefense,magicalPrimary);
    out.trace.push_back({{"stage","primary_defense_conversion"},{"classification","inferred"},{"enabled",policy.derivePrimaryDefense},
        {"vitality",out.vitality},{"spirit",out.spirit},{"vitality_factor",out.vitalityDefenseFactor},{"spirit_factor",out.spiritDefenseFactor},
        {"physical_primary_defense",physicalPrimary},{"magical_primary_defense",magicalPrimary},
        {"physical_defense",out.physicalDefense},{"magical_defense",out.magicalDefense}});
    if (!errors(out.diagnostics) && !out.usable()) issue(out,"invalid_final_combat_attribute_domain","error");
    return out;
}

CombatAttributeSnapshot evaluateCombatAttributes(const CharacterBaseAttributes &base,const Progression &progression,
    const CharacterDefinition &character,const CombatAttributePolicy &policy) {
    std::vector<EquippedAttributeSource> inputs; int level=0;
    try {
        if (!integer(progression.state.at("level"),level) || level<1 || level>99) throw std::runtime_error("Invalid normal qualification level");
        const auto &inventory=progression.state.at("inventory"), &equipped=progression.state.at("equipped");
        if (!inventory.is_array() || !equipped.is_object()) throw std::runtime_error("Invalid equipped ownership containers");
        for (auto slot=equipped.begin();slot!=equipped.end();++slot) {
            int uid=0;
            if (!integer(slot.value(),uid) || uid<=0) throw std::runtime_error("Invalid equipped UID");
            const Json *selected=nullptr;
            for (const auto &entry:inventory) {
                int candidate=0;
                if (!entry.is_object() || !entry.contains("uid") || !integer(entry.at("uid"),candidate) || candidate<=0)
                    throw std::runtime_error("Invalid inventory UID");
                if (candidate==uid) { if (selected) throw std::runtime_error("Ambiguous equipped UID"); selected=&entry; }
            }
            int id=0,durability=0,count=0;
            if (!selected || !integer(selected->at("id"),id) || id<=0 || !integer(selected->at("durability"),durability) ||
                !integer(selected->at("count"),count) || count!=1) throw std::runtime_error("Invalid equipped instance");
            // Instance combat extensions must have their own consumer; keeping
            // them in preserved JSON does not authorize ignoring their effect.
            for (auto field=selected->begin();field!=selected->end();++field)
                if (field.key()!="uid" && field.key()!="id" && field.key()!="count" && field.key()!="durability" &&
                    (combatRelated(field.key()) || field.key().find("upgrade")!=std::string::npos || field.key().find("reinforce")!=std::string::npos ||
                     field.key().find("enchant")!=std::string::npos || field.key().find("roll")!=std::string::npos || field.key().find("quality")!=std::string::npos ||
                     field.key().find("amplif")!=std::string::npos || field.key().find("forge")!=std::string::npos))
                    throw std::runtime_error("Equipped instance combat extension needs a consumer: "+field.key());
            const auto *definition=progression.item(id);
            if (!definition || !definition->equipment) throw std::runtime_error("Missing EQU definition");
            inputs.push_back({uid,slot.key(),durability,definition->source});
        }
    } catch (const std::exception &error) {
        auto out=evaluateCombatAttributes(base,character,inputs,level,policy);
        issue(out,"equipped_combat_collection_failed","error",{{"reason",error.what()}}); return out;
    }
    return evaluateCombatAttributes(base,character,inputs,level,policy);
}
} // namespace dnf
