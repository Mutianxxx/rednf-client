#include "dnf/damage_resolution.hpp"
#include "dnf/attack_status.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *policyId = "inferred-pve-damage-v1";
constexpr const char *collisionHash = "e98605adfbd2be502406ce89942990d10bc47e99aef80809ad52b9bc02cd2ec8";
constexpr const char *defenseHash = "0681c8c9174aff4ae4d3f3ea227eafdb09e560011fec84437e8bbbcae35b8e93";
constexpr const char *damageHash = "7aa43cd79b5ba396d67d0437e4640c6a23fed19166619d6268cec8c0541056bb";
float add32(float a,float b) { volatile float r=a+b; return r; }
float sub32(float a,float b) { volatile float r=a-b; return r; }
float mul32(float a,float b) { volatile float r=a*b; return r; }
float div32(float a,float b) { volatile float r=a/b; return r; }
bool errors(const Json &list) {
    for (const auto &entry:list) if (entry.value("severity",std::string())=="error") return true;
    return false;
}
template<class T> void issue(T &out,const char *kind,Json details=Json::object(),const char *severity="error") {
    details["kind"]=kind; details["severity"]=severity; out.diagnostics.push_back(std::move(details));
}
std::string meta(const Json &value,const char *key) {
    return value.is_object() && value.contains(key) && value.at(key).is_string()?value.at(key).get<std::string>():std::string();
}
bool number(const Json &value,float &out) {
    if (!value.is_number()) return false;
    if (value.is_number_unsigned() && value.get<uint64_t>()>uint64_t(INT32_MAX)) return false;
    if (value.is_number_integer()) {
        const auto n=value.get<int64_t>(); if (n<INT32_MIN || n>INT32_MAX) return false;
    }
    const auto n=value.get<double>();
    if (!std::isfinite(n) || std::abs(n)>double(std::numeric_limits<float>::max())) return false;
    out=float(n); return true;
}
Json reference(const Script &source,size_t ordinal,const std::string &scope) {
    const auto &field=source.fields.at(ordinal);
    const auto end=ordinal+1<source.fields.size()?source.fields[ordinal+1].offset:source.rawBytes.size();
    SourceRef ref; ref.packageIdentity=meta(source.source,"package_identity"); ref.memberPath=normalize(source.path);
    ref.literalPath=meta(source.source,"literal_path"); if (ref.literalPath.empty()) ref.literalPath=source.path;
    ref.memberSha256=sha256(source.rawBytes); ref.ordinal=ordinal; ref.byteOffset=field.offset;
    ref.byteLength=end>=field.offset?end-field.offset:0; ref.scope=scope; return ref.json();
}
std::string hex(const Bytes &bytes) {
    static const char digits[]="0123456789abcdef"; std::string result; result.reserve(bytes.size()*2);
    for (const auto n:bytes) { result+=digits[n>>4]; result+=digits[n&15]; } return result;
}
Json sourceSnapshot(const Script &source,bool full) {
    Json result={{"path",source.path},{"member_sha256",sha256(source.rawBytes)},{"provenance",source.source},{"fields",Json::array()}};
    for (size_t i=0;i<source.fields.size();++i) result["fields"].push_back({{"source",reference(source,i,"damage-source")},
        {"tag",source.fields[i].tag},{"values",source.fields[i].values}});
    if (full) { result["raw_bytes_hex"]=hex(source.rawBytes); result["ordered_tokens"]=source.tokens; } return result;
}
template<class T> void validateScript(T &out,const Script &source,const std::string &package) {
    if (!source.source.is_object() || source.rawBytes.size()<2 || (source.rawBytes.size()-2)%5 || source.path.empty())
        issue(out,"invalid_damage_source",{{"path",source.path}});
    for (const auto *key:{"package_identity","literal_path","member_sha256"})
        if (source.source.is_object() && source.source.contains(key) && !source.source.at(key).is_string())
            issue(out,"invalid_damage_source_identity",{{"path",source.path},{"key",key}});
    if (package.empty() || meta(source.source,"package_identity")!=package)
        issue(out,"damage_source_package_mismatch",{{"path",source.path},{"expected",package},{"actual",meta(source.source,"package_identity")}});
    if (source.source.is_object() && source.source.contains("member_sha256") &&
        meta(source.source,"member_sha256")!=sha256(source.rawBytes)) issue(out,"damage_source_hash_mismatch",{{"path",source.path}});
    size_t previous=0;
    for (size_t i=0;i<source.fields.size();++i) {
        const auto &field=source.fields[i];
        if (!field.values.is_array() || field.offset<2 || (field.offset-2)%5 || field.offset<=previous ||
            field.offset>source.rawBytes.size() || source.rawBytes.size()-field.offset<5)
            issue(out,"invalid_damage_source_span",{{"path",source.path},{"ordinal",i},{"offset",field.offset}});
        previous=field.offset;
    }
}
template<class T> std::optional<std::array<float,27>> constants(T &out,const DamageResolutionPolicy &policy,const std::string &package) {
    validateScript(out,policy.damageConstants,package);
    if (normalize(policy.damageConstants.path)!="etc/etcparameter.etc") issue(out,"unexpected_damage_constant_path",{{"path",policy.damageConstants.path}});
    std::vector<size_t> found;
    for (size_t i=0;i<policy.damageConstants.fields.size();++i)
        if (normalize(policy.damageConstants.fields[i].tag)=="[damage fomula constant]") found.push_back(i);
    if (found.size()!=1) { issue(out,"ambiguous_damage_constants",{{"count",found.size()}}); return std::nullopt; }
    const auto &values=policy.damageConstants.fields[found[0]].values; std::array<float,27> c{};
    bool valid=values.is_array() && values.size()==c.size();
    if (valid) for (size_t i=0;i<c.size();++i) if (!number(values[i],c[i])) valid=false;
    if (!valid || c[0]<=0 || c[6]<=0 || c[2]<=0 || c[8]<=0 || c[4]<0 || c[5]<0 || c[10]<0 || c[11]<0 || c[12]<0 || c[13]<0 || c[22]<0 || c[23]<0) {
        issue(out,"invalid_damage_constants",{{"source",reference(policy.damageConstants,found[0],"damage-constant-candidate")},
            {"expected_count",27},{"values",values}}); return std::nullopt;
    }
    out.trace.push_back({{"stage","damage_constant_candidate"},{"classification","inferred cross-version positional mapping"},
        {"source",reference(policy.damageConstants,found[0],"damage-constant-candidate")},{"values",values},
        {"available_position_mapping",{0,2,4,5,6,8,10,11,12,13,22,23}},
        {"unconsumed_tail",values[26]},{"native_pc_packet_constructor","unrecovered"}});
    return c;
}
bool finiteNonnegative(float value) { return std::isfinite(value) && value>=0; }
bool validType(DamageAttackType type) { return type==DamageAttackType::Physical || type==DamageAttackType::Magical || type==DamageAttackType::IgnoreDefense || type==DamageAttackType::Weapon; }
} // namespace

const char *damageAttackTypeName(DamageAttackType type) {
    switch (type) {
    case DamageAttackType::Physical:return "physical"; case DamageAttackType::Magical:return "magical";
    case DamageAttackType::IgnoreDefense:return "ignore_defense"; case DamageAttackType::Weapon:return "weapon";
    } return "invalid";
}
const char *damageTargetCategoryName(DamageTargetCategory category) {
    switch(category) {case DamageTargetCategory::Unknown:return "unknown";case DamageTargetCategory::Human:return "human";
    case DamageTargetCategory::Fort:return "fort";case DamageTargetCategory::Monster:return "monster";}
    return "invalid";
}
bool AttackDamageDefinition::usable() const {
    for(const auto percent:targetCategoryPercent) if(!finiteNonnegative(percent)) return false;
    return type && validType(*type) && !errors(diagnostics) && !meta(source.source,"package_identity").empty() &&
        finiteNonnegative(baseDamage) && finiteNonnegative(absoluteDamage) && std::isfinite(bonusPercent) && bonusPercent>=-100 &&
        std::isfinite(criticalBonusPercent) && std::isfinite(missDeltaPercent) && element>=0 && element<=4;
}
Json AttackDamageDefinition::snapshot(bool full) const {
    return {{"usable",usable()},{"type",type?Json(damageAttackTypeName(*type)):Json()},
        {"base_damage",baseDamage},{"absolute_damage",absoluteDamage},{"bonus_percent",bonusPercent},
        {"weapon_damage_apply",weaponDamageApply},{"ignore_defense",ignoreDefense},{"element",element},
        {"critical_bonus_percent",criticalBonusPercent},{"miss_delta_percent",missDeltaPercent},
        {"target_category_percent",{{"human",targetCategoryPercent[0]},{"fort",targetCategoryPercent[1]},{"monster",targetCategoryPercent[2]}}},
        {"source",sourceSnapshot(source,full)},{"trace",trace},{"diagnostics",diagnostics}};
}
AttackDamageDefinition readAttackDamage(const Script &source,AttackStatusConsumer statusConsumer) {
    AttackDamageDefinition out; out.source=source;
    validateScript(out,source,meta(source.source,"package_identity"));
    const auto path=normalize(source.path);
    if (path.size()<4 || path.substr(path.size()-4)!=".atk") issue(out,"unexpected_attack_damage_path",{{"path",source.path}});
    std::map<std::string,std::vector<size_t>> selected; std::set<size_t> enums; bool pvp=false;
    for (size_t i=0;i<source.fields.size();++i) {
        const auto &field=source.fields[i]; const auto tag=normalize(field.tag);
        if (tag=="[pvp]") { if (pvp) issue(out,"nested_attack_pvp_scope",{{"source",reference(source,i,"pvp")}}); pvp=true; continue; }
        if (tag=="[/pvp]") { if (!pvp) issue(out,"unmatched_attack_pvp_scope",{{"source",reference(source,i,"pvp")}}); pvp=false; continue; }
        if (pvp) { out.trace.push_back({{"stage","excluded_pvp_field"},{"source",reference(source,i,"pvp")},{"tag",tag},{"values",field.values}}); continue; }
        if (enums.count(i)) continue;
        if (tag=="[attack type]" || tag=="[elemental property]" || tag=="[damage reaction]" || tag=="[attack direction]") {
            selected[tag].push_back(i); std::string value; Json refs=Json::array({reference(source,i,"dungeon")});
            if (field.values.is_array() && field.values.size()==1 && field.values[0].is_string()) value=normalize(field.values[0].get<std::string>());
            else if (field.values.empty() && i+1<source.fields.size() && source.fields[i+1].values.empty()) {
                value=normalize(source.fields[i+1].tag); enums.insert(i+1); refs.push_back(reference(source,i+1,"dungeon-enum"));
            }
            if (tag=="[attack type]") {
                if (value=="[physic]") out.type=DamageAttackType::Physical;
                else if (value=="[magic]") out.type=DamageAttackType::Magical;
                else if (value=="[ignore defense]") out.type=DamageAttackType::IgnoreDefense;
                else if (value=="[weapon]") out.type=DamageAttackType::Weapon;
                else issue(out,"invalid_attack_damage_type",{{"sources",refs},{"value",value}});
            } else if (tag=="[elemental property]") {
                static const std::map<std::string,int> elements={{"[fire element]",0},{"[water element]",1},{"[dark element]",2},{"[light element]",3},{"[no element]",4}};
                const auto found=elements.find(value);
                if (found==elements.end()) issue(out,"invalid_attack_element",{{"sources",refs},{"value",value}}); else out.element=found->second;
            } else if (value.empty()) issue(out,"malformed_attack_context_enum",{{"sources",refs},{"tag",tag}});
            out.trace.push_back({{"stage","attack_context_enum"},{"tag",tag},{"selected",value},{"sources",refs}}); continue;
        }
        selected[tag].push_back(i);
    }
    if (pvp) issue(out,"unterminated_attack_pvp_scope");
    if (!out.type) issue(out,"missing_attack_damage_type");
    for (const auto &[tag,ordinals]:selected) if (ordinals.size()!=1 &&
        (tag=="[damage]" || tag=="[absolute damage]" || tag=="[damage bonus]" || tag=="[attack type]" || tag=="[elemental property]" ||
         tag=="[weapon damage apply]" || tag=="[ignore defense]" || tag=="[critical hit]" || tag=="[stuck]"))
        issue(out,"ambiguous_attack_damage_field",{{"tag",tag},{"ordinals",ordinals}});
    const auto scalar=[&](const char *tag,float fallback,bool integerOnly=false) {
        const auto found=selected.find(tag); if (found==selected.end()) return fallback;
        const auto ordinal=found->second.front(); const auto &values=source.fields[ordinal].values; float value=0;
        if (found->second.size()!=1 || !values.is_array() || values.size()!=1 || !number(values[0],value) || (integerOnly && !values[0].is_number_integer())) {
            issue(out,"invalid_attack_damage_operand",{{"tag",tag},{"source",reference(source,ordinal,"dungeon")},{"values",values}}); return fallback;
        }
        out.trace.push_back({{"stage","attack_numeric_operand"},{"tag",tag},{"value",value},{"source",reference(source,ordinal,"dungeon")}}); return value;
    };
    out.baseDamage=scalar("[damage]",0,true); out.absoluteDamage=scalar("[absolute damage]",0,true);
    out.bonusPercent=scalar("[damage bonus]",0); out.criticalBonusPercent=scalar("[critical hit]",0); out.missDeltaPercent=scalar("[stuck]",0);
    out.targetCategoryPercent={{scalar("[human damage rate]",100),scalar("[fort damage rate]",100),scalar("[monster damage rate]",100)}};
    const float weapon=scalar("[weapon damage apply]",0,true),ignore=scalar("[ignore defense]",0,true);
    if ((weapon!=0 && weapon!=1) || (ignore!=0 && ignore!=1)) issue(out,"invalid_attack_damage_switch");
    out.weaponDamageApply=weapon==1; out.ignoreDefense=ignore==1;
    for (const auto &[tag,ordinals]:selected) {
        for (const auto ordinal:ordinals) {
            const auto &values=source.fields[ordinal].values;
            if (tag=="[active status]") {
                const bool none=(values.is_array() && !values.empty() && values[0].is_string() && normalize(values[0].get<std::string>())=="[none]") ||
                    (values.empty() && ordinal+1<source.fields.size() && normalize(source.fields[ordinal+1].tag)=="[none]");
                if (!none) {
                    const auto statuses=readAttackStatuses(source);
                    if(statusConsumer!=AttackStatusConsumer::StunHostV1 || !statuses.usable())
                        issue(out,"attack_status_consumer_required",{{"source",reference(source,ordinal,"dungeon")},
                            {"values",values},{"status_diagnostics",statuses.diagnostics}});
                    else out.trace.push_back({{"stage","delegated_attack_status"},{"consumer","stun-host-v1"},
                        {"source",reference(source,ordinal,"dungeon")},{"statuses",statuses.snapshot()}});
                }
            }
            if (tag=="[mana burn]" || (tag=="[hit info]" && std::find(values.begin(),values.end(),Json("[mana burn]"))!=values.end()))
                issue(out,"attack_mp_damage_consumer_required",{{"source",reference(source,ordinal,"dungeon")}});
            const bool neutralDelta=tag=="[hp drain]" || tag=="[mp drain]" || tag=="[weakness]" || tag=="[stuck prob increase]";
            const bool categoryRate=tag=="[human damage rate]" || tag=="[fort damage rate]" || tag=="[monster damage rate]";
            if (neutralDelta) {
                bool neutral=values.is_array() && !values.empty();
                for (const auto &v:values) { float n=0; if (!number(v,n) || n!=(categoryRate?100.0f:0.0f)) neutral=false; }
                if (!neutral) issue(out,"unconsumed_attack_damage_effect",{{"tag",tag},{"source",reference(source,ordinal,"dungeon")},{"values",values}});
            }
            static const std::set<std::string> known={"[damage]","[absolute damage]","[damage bonus]","[critical hit]","[stuck]",
                "[weapon damage apply]","[ignore defense]","[attack type]","[elemental property]","[damage reaction]","[attack direction]"};
            static const std::set<std::string> delegated={"[hit info]","[hit wav]","[hit direction]","[hit lift up]","[hit horizon]",
                "[hit horizontal]","[hit down]","[horizontal]","[is hit number increasing]","[max target hit number]",
                "[damage except human]"};
            const bool numericCombat=tag.find("damage")!=std::string::npos || tag.find("critical")!=std::string::npos ||
                tag.find("stuck")!=std::string::npos || tag.find("element")!=std::string::npos;
            if (!known.count(tag) && !neutralDelta && !categoryRate && !delegated.count(tag) && numericCombat)
                issue(out,"unknown_attack_damage_field",{{"tag",tag},{"source",reference(source,ordinal,"dungeon")},{"values",values}});
        }
    }
    if (!finiteNonnegative(out.baseDamage) || !finiteNonnegative(out.absoluteDamage) || out.bonusPercent<-100 ||
        std::any_of(out.targetCategoryPercent.begin(),out.targetCategoryPercent.end(),[](float p){return !finiteNonnegative(p);}))
        issue(out,"attack_damage_operand_out_of_range");
    out.trace.push_back({{"stage","attack_damage_defaults"},{"base_damage",0},{"absolute_damage",0},{"bonus_percent",0},{"weapon_damage_apply",false},
        {"element",4},{"basis","official attackinfosample.atk lines 3-12; absent base/absolute/bonus use explicit neutral beta defaults"},
        {"delegation","reaction, target relation, geometry, armor/protection and sounds remain hit-lifecycle capabilities"}});
    return out;
}

DamageResolutionPolicy DamageResolutionPolicy::inferredPveDamageV1(const Script &source) {
    DamageResolutionPolicy result; result.id=policyId; result.damageConstants=source; return result;
}
Json DamageResolutionPolicy::describe() const {
    return {{"id",id},{"classification","inferred; PC attribute-to-packet mapping unrecovered"},{"arithmetic","binary32 stored at every named operation; differs from source x87 extended temporaries"},
        {"random_variation",randomVariation},{"roll_critical",rollCritical},{"roll_hit",rollHit},
        {"base_critical_percent",baseCriticalPercent},{"critical_multiplier",criticalMultiplier},
        {"minimum_defense_multiplier",minimumDefenseMultiplier},{"ignore_defense_random_rate",ignoreDefenseRandomRate},
        {"random_policy","PCG32 beta stream, uniform rejection sampling; not native SDC RNG"},
        {"evidence",{{"collision_source_sha256",collisionHash},{"defense_source_sha256",defenseHash},{"complete_damage_source_sha256",damageHash},
            {"server_source_root","dnf-result/imports/rednf/remake/source/DNFServer/GameServer/Game"},
            {"atk_sample",{{"path","pvf官方文档/sample(官方注释)/attackinfosample.atk"},
                {"sha256","ffd0d2541f7598962a59ed5c5415bdd00e28945838bbae3373bd65ff4aefd675"},{"lines",{3,4,5,6,7,12,28,29}}}},
            {"atk_tool_sample",{{"path","pvf官方文档/sample(官方注释)/attackinfosamplebytool.atk"},
                {"sha256","7bcf60b5f269509fd89a5eb3b0c231d98ab87ccda9e2cb5557e8f36185201954"},{"lines",{14,15,16,19,20,21,22,24,28,29}}}}}},
        {"neutral_semantics",{{"additive",0},{"factor",1},{"final_percent",100},{"packet_ctor_used",false}}},
        {"scope","one accepted contact; normal/dungeon only; no HP writes, status, grabs or protection mutation"}};
}
const char *damageContactRangeName(DamageContactRange range) {
    switch(range){case DamageContactRange::Unknown:return "unknown";case DamageContactRange::Melee:return "melee";case DamageContactRange::Ranged:return "ranged";}
    return "invalid";
}
void bindDamageContactRange(DamageRequest &request,const Script &source) {
    bool inside=false,closed=true,malformed=false;size_t blocks=0;std::set<DamageContactRange> ranges;
    Json categories=Json::array(),refs=Json::array();
    const auto accept=[&](const Json &value) {
        categories.push_back(value);if(!value.is_string()){malformed=true;return;}
        const auto tag=normalize(value.get<std::string>());
        if(tag=="[melee]")ranges.insert(DamageContactRange::Melee);
        if(tag=="[bullet]")ranges.insert(DamageContactRange::Ranged);
    };
    for(size_t ordinal=0;ordinal<source.fields.size();++ordinal) {
        const auto &field=source.fields[ordinal];
        const auto tag=normalize(field.tag);
        if(tag=="[category]"){refs.push_back(reference(source,ordinal,"damage_contact_range"));if(inside)malformed=true;++blocks;inside=true;closed=false;for(const auto &value:field.values)accept(value);}
        else if(inside&&tag=="[/category]"){refs.push_back(reference(source,ordinal,"damage_contact_range"));inside=false;closed=true;if(!field.values.empty())malformed=true;}
        else if(inside){refs.push_back(reference(source,ordinal,"damage_contact_range"));accept(tag);if(!field.values.empty())malformed=true;}
    }
    request.contactRange=!malformed&&closed&&blocks==1&&ranges.size()==1?*ranges.begin():DamageContactRange::Unknown;
    request.contactRangeSource={{"policy","inferred-source-contact-range-v1"},{"classification","inferred_beta"},
        {"sources",refs},{"categories",categories},{"selected",damageContactRangeName(request.contactRange)},
        {"basis","Explicit passiveobject type category only; physical/magical and AI range combat do not select attack distance"}};
}
bool DamageCombatant::usable() const {
    if (packageIdentity.empty() || adapter.empty() || level<1 || level>99 || errors(diagnostics)) return false;
    if(targetCategory!=DamageTargetCategory::Unknown && targetCategory!=DamageTargetCategory::Human &&
       targetCategory!=DamageTargetCategory::Fort && targetCategory!=DamageTargetCategory::Monster) return false;
    for (const auto n:{strength,intelligence,physicalAttack,magicalAttack,physicalDefense,magicalDefense,independentAttack,
        independentRate,physicalAbsoluteDamage,magicalAbsoluteDamage,physicalAbsoluteDefensePercent,magicalAbsoluteDefensePercent})
        if (!finiteNonnegative(n)) return false;
    for (const auto n:{physicalCriticalBonusPercent,magicalCriticalBonusPercent,attackMissDeltaPercent,evasionPercent}) if (!std::isfinite(n)) return false;
    for (size_t i=0;i<4;++i) if (!std::isfinite(elementalAttack[i]) || !std::isfinite(elementalResistance[i])) return false;
    for(const auto value:damageMissBonusPercent)if(!std::isfinite(value)||value<0||value>100)return false;
    return independentRate>0 && physicalAbsoluteDefensePercent<=100 && magicalAbsoluteDefensePercent<=100 && weaponElement>=0 && weaponElement<=4;
}
Json DamageCombatant::snapshot() const {
    return {{"usable",usable()},{"package_identity",packageIdentity},{"adapter",adapter},{"level",level},
        {"target_category",damageTargetCategoryName(targetCategory)},
        {"strength",strength},{"intelligence",intelligence},{"physical_attack",physicalAttack},{"magical_attack",magicalAttack},
        {"physical_defense",physicalDefense},{"magical_defense",magicalDefense},{"independent_attack",independentAttack},{"independent_rate",independentRate},
        {"physical_absolute_damage",physicalAbsoluteDamage},{"magical_absolute_damage",magicalAbsoluteDamage},
        {"physical_absolute_defense_percent",physicalAbsoluteDefensePercent},{"magical_absolute_defense_percent",magicalAbsoluteDefensePercent},
        {"physical_critical_bonus_percent",physicalCriticalBonusPercent},{"magical_critical_bonus_percent",magicalCriticalBonusPercent},
        {"attack_miss_delta_percent",attackMissDeltaPercent},{"evasion_percent",evasionPercent},
        {"damage_miss_bonus_percent",damageMissBonusPercent},{"damage_miss_bonus_source",damageMissBonusSource},{"elemental_attack",elementalAttack},
        {"elemental_resistance",elementalResistance},{"weapon_element",weaponElement},{"sources",sources},{"trace",trace},{"diagnostics",diagnostics}};
}
DamageCombatant makeDamageCombatant(const CombatAttributeSnapshot &a) {
    DamageCombatant out; out.adapter="inferred-character-damage-input-v1"; out.level=a.level;
    out.targetCategory=DamageTargetCategory::Human;
    out.packageIdentity=a.pureChr.source.is_object() && a.pureChr.source.contains("provenance")?meta(a.pureChr.source["provenance"],"package_identity"):std::string();
    out.diagnostics=a.diagnostics;
    if (!a.usable()) issue(out,"unusable_character_damage_attributes");
    out.strength=a.strength; out.intelligence=a.intelligence; out.physicalAttack=a.physicalAttack; out.magicalAttack=a.magicalAttack;
    out.physicalDefense=a.physicalDefense; out.magicalDefense=a.magicalDefense; out.independentAttack=a.independentAttack; out.independentRate=a.independentRate;
    out.physicalAbsoluteDamage=a.physicalAbsoluteDamage; out.magicalAbsoluteDamage=a.magicalAbsoluteDamage;
    out.physicalAbsoluteDefensePercent=a.physicalAbsoluteDefensePercent; out.magicalAbsoluteDefensePercent=a.magicalAbsoluteDefensePercent;
    out.physicalCriticalBonusPercent=a.physicalCriticalBonusPercent; out.magicalCriticalBonusPercent=a.magicalCriticalBonusPercent;
    out.attackMissDeltaPercent=a.attackMissDeltaPercent; out.evasionPercent=div32(a.evasionPerMille,10);
    out.elementalAttack=a.elementalAttack; out.elementalResistance=a.elementalResistance; out.weaponElement=a.weaponElement;
    out.sources=a.snapshot(); out.trace.push_back({{"stage","character_damage_input"},{"source_policy",a.policy},
        {"attack","equipment base, not STR/INT"},{"defense","already resolved by combat attribute policy; no second VIT/SPR addition"},
        {"evasion_conversion","per_mille / 10 = percentage points"},
        {"target_category","human"},{"category_classification","inferred typed character adapter; current CHR has no armor override"}}); return out;
}
DamageCombatant makeDamageCombatant(const MonsterCombatAttributes &a,const DamageResolutionPolicy &policy) {
    DamageCombatant out; out.adapter="inferred-monster-damage-input-v1"; out.level=a.level;
    out.packageIdentity=meta(a.source.monster.source,"package_identity"); out.diagnostics=a.diagnostics; out.sources=a.snapshot();
    if (policy.id!=policyId) issue(out,"damage_policy_not_enabled");
    if (!a.usable()) { issue(out,"unusable_monster_damage_attributes"); return out; }
    bindDamageTargetCategory(out,a.source.monster,DamageTargetCategory::Monster);
    const auto c=constants(out,policy,out.packageIdentity); const auto &v=*a.attributes;
    out.strength=float(v.physicalAttackCoefficient); out.intelligence=float(v.magicalAttackCoefficient);
    out.physicalAttack=float(v.equipmentPhysicalAttack); out.magicalAttack=float(v.equipmentMagicalAttack);
    if (c) {
        out.physicalDefense=add32(float(v.equipmentPhysicalDefense),mul32(float(v.physicalDefenseCoefficient),(*c)[22]));
        out.magicalDefense=add32(float(v.equipmentMagicalDefense),mul32(float(v.magicalDefenseCoefficient),(*c)[23]));
    }
    for (size_t i=0;i<4;++i) { out.elementalAttack[i]=float(v.elementalAttack[i]); out.elementalResistance[i]=float(v.elementalResistance[i]); }
    for(size_t i=0;i<2;++i)out.damageMissBonusPercent[i]=float(v.damageMissBonusPercent[i]);
    out.damageMissBonusSource=v.damageMissBonusSource;
    out.attackMissDeltaPercent=v.tableAttackMissDeltaPercent;
    out.trace.push_back({{"stage","monster_table_attack_miss_delta"},{"selected_percent",out.attackMissDeltaPercent},
        {"receipt",v.tableAttackMissSource},{"classification","inferred_beta attacker raw11 delta; full native miss formula pending"}});
    // The upstream adapter currently permits only explicit zero for these
    // unresolved authored units. Do not reinterpret a future nonzero receipt.
    for (const auto &[name,value]:std::vector<std::pair<const char *,double>>{{"physical_critical_rate",v.physicalCriticalRate},
        {"magical_critical_rate",v.magicalCriticalRate},{"hit_rate_bonus",v.hitRateBonus},{"evasion_rate_bonus",v.evasionRateBonus},
        {"absolute_damage",v.absoluteDamage},{"flat_damage_reduction",v.flatDamageReduction},{"absolute_defense_rate",v.absoluteDefenseRate},
        {"absolute_damage_resistance_rate",v.absoluteDamageResistanceRate},{"absolute_defense_ignore_rate",v.absoluteDefenseIgnoreRate}})
        if (value!=0 || !std::isfinite(value)) issue(out,"unresolved_monster_damage_input",{{"field",name},{"value",value}});
    out.trace.push_back({{"stage","monster_damage_input"},{"classification","inferred primary-stat mapping"},{"source_policy",a.policy},
        {"primary_columns",{1,2,3,4}},{"equipment_attack_columns",{7,9}},{"equipment_defense_columns",{8,10}},
        {"defense_operation","equipment + coefficient * current source positions 22/23"}});
    if (!out.usable() && !errors(out.diagnostics)) issue(out,"monster_damage_input_out_of_range"); return out;
}
void bindDamageTargetCategory(DamageCombatant &out,const Script &source,DamageTargetCategory fallback) {
    Json categories=Json::array(),refs=Json::array();size_t blocks=0;bool inside=false,closed=true,malformed=false;
    for(size_t i=0;i<source.fields.size();++i) {
        const auto &field=source.fields[i];const auto tag=normalize(field.tag);
        if(tag=="[category]") {
            ++blocks;if(inside) malformed=true;inside=true;closed=false;
            refs.push_back(reference(source,i,"damage_target_category"));
            for(const auto &value:field.values) categories.push_back(value);
        } else if(inside && tag=="[/category]") {
            inside=false;closed=true;refs.push_back(reference(source,i,"damage_target_category"));
            if(!field.values.empty())malformed=true;
        } else if(inside) {
            refs.push_back(reference(source,i,"damage_target_category"));categories.push_back(tag);
            if(!field.values.empty())malformed=true;
        }
    }
    std::set<DamageTargetCategory> armor;Json unknown=Json::array();
    for(const auto &value:categories) {
        if(!value.is_string()){malformed=true;continue;}const auto tag=normalize(value.get<std::string>());
        if(tag=="[human armor]")armor.insert(DamageTargetCategory::Human);
        else if(tag=="[fort armor]" || tag=="[fort]")armor.insert(DamageTargetCategory::Fort);
        else if(tag.find("armor")!=std::string::npos && tag!="[full-superarmor]")unknown.push_back(value);
    }
    out.targetCategory=DamageTargetCategory::Unknown;
    if(!malformed && closed && blocks<=1 && unknown.empty() && armor.size()<=1)
        out.targetCategory=armor.empty()?fallback:*armor.begin();
    if(out.targetCategory==DamageTargetCategory::Unknown)
        issue(out,"unresolved_damage_target_category",{{"categories",categories},{"unknown_armor",unknown},{"sources",refs},
            {"blocks",blocks},{"malformed",malformed || !closed}},"warning");
    out.trace.push_back({{"stage","source_damage_target_category"},{"classification","inferred source-category adapter"},
        {"source_path",source.path},{"member_sha256",sha256(source.rawBytes)},{"sources",refs},{"categories",categories},
        {"selected",damageTargetCategoryName(out.targetCategory)},{"fallback",damageTargetCategoryName(fallback)},
        {"basis","attackinfosample.atk lines23-26; monster rate targets zero armor categories, species human is separate"},
        {"unknown_policy","nonneutral category rates require a known target class; no guessed fallback for explicit unresolved armor"}});
}
Json DamageSkillModifiers::snapshot() const {
    return {{"percent",percent},{"fixed_damage",fixedDamage},{"independent_percent",independentPercent},{"attack_multiplier",attackMultiplier},
        {"primary_stat_bonus",primaryStatBonus},{"total_multiplier",totalMultiplier},{"critical_multiplier",criticalMultiplier},{"replaces_attack_coefficients",replacesAttackCoefficients},{"sources",sources}};
}
Json DamageResolution::snapshot() const {
    return {{"usable",usable()},{"policy",policy},{"attacker",attacker.json()},{"target",target.json()},
        {"attack_instance",attackInstance},{"hit_index",hitIndex},{"hp_damage",hpDamage?Json(*hpDamage):Json()},
        {"missed",missed},{"critical",critical},{"sources",sources},{"trace",trace},{"diagnostics",diagnostics}};
}

DamageResolution resolveDamage(const DamageRequest &request,const DamageResolutionPolicy &policy,Pcg32 *combatRandom) {
    DamageResolution out; out.policy=policy.id; out.attacker=request.attacker; out.target=request.target;
    out.attackInstance=request.attackInstance; out.hitIndex=request.hitIndex;
    if (policy.id!=policyId) { issue(out,"damage_policy_not_enabled"); return out; }
    if (!request.attacker || !request.target || !request.attackInstance) issue(out,"invalid_damage_identity");
    const auto &a=request.attackerStats; const auto &d=request.targetStats; const auto &atk=request.attack; const auto &s=request.skill;
    out.sources={{"attacker",a.snapshot()},{"target",d.snapshot()},{"attack",atk.snapshot()},{"skill",s.snapshot()},{"policy",policy.describe()}};
    out.sources["contact_range"]={{"selection",damageContactRangeName(request.contactRange)},{"evidence",request.contactRangeSource}};
    if(request.contactRange!=DamageContactRange::Unknown&&request.contactRange!=DamageContactRange::Melee&&request.contactRange!=DamageContactRange::Ranged)
        issue(out,"invalid_damage_contact_range");
    if(request.contactRange==DamageContactRange::Unknown&&d.damageMissBonusPercent[0]!=d.damageMissBonusPercent[1])
        issue(out,"damage_contact_range_required",{{"melee_ranged_bonus",d.damageMissBonusPercent},{"source",d.damageMissBonusSource}});
    if (!a.usable()) issue(out,"unusable_damage_attacker",{{"diagnostics",a.diagnostics}});
    if (!d.usable()) issue(out,"unusable_damage_target",{{"diagnostics",d.diagnostics}});
    if (!atk.usable()) issue(out,"unusable_attack_damage_definition",{{"diagnostics",atk.diagnostics}});
    const bool categoryNeutral=std::all_of(atk.targetCategoryPercent.begin(),atk.targetCategoryPercent.end(),[](float p){return p==100;});
    if(!categoryNeutral && d.targetCategory==DamageTargetCategory::Unknown)
        issue(out,"damage_target_category_required",{{"rates",atk.targetCategoryPercent},{"target_category",damageTargetCategoryName(d.targetCategory)}});
    if (a.packageIdentity!=d.packageIdentity || a.packageIdentity!=meta(atk.source.source,"package_identity")) issue(out,"damage_combatant_package_mismatch");
    validateScript(out,atk.source,a.packageIdentity);
    const auto c=constants(out,policy,a.packageIdentity);
    for (const auto n:{s.percent,s.fixedDamage,s.independentPercent,s.attackMultiplier,s.totalMultiplier,s.criticalMultiplier}) if (!finiteNonnegative(n)) issue(out,"invalid_damage_skill_modifier");
    if (!std::isfinite(s.primaryStatBonus)) issue(out,"invalid_damage_primary_stat_bonus");
    if (!std::isfinite(policy.baseCriticalPercent) || policy.baseCriticalPercent<0 || policy.baseCriticalPercent>100 ||
        !finiteNonnegative(policy.criticalMultiplier) || !finiteNonnegative(policy.ignoreDefenseRandomRate) ||
        !std::isfinite(policy.minimumDefenseMultiplier) || policy.minimumDefenseMultiplier<0 || policy.minimumDefenseMultiplier>1)
        issue(out,"invalid_damage_policy_parameters");
    const bool needsRandom=policy.randomVariation || policy.rollCritical || policy.rollHit;
    if (needsRandom && !combatRandom) issue(out,"damage_random_stream_required");
    auto type=atk.type.value_or(DamageAttackType::Physical);
    if (type==DamageAttackType::Weapon) {
        if (!request.weaponType || (*request.weaponType!=DamageAttackType::Physical && *request.weaponType!=DamageAttackType::Magical))
            issue(out,"attack_weapon_type_source_required");
        else type=*request.weaponType;
    }
    const bool magical=type==DamageAttackType::Magical,ignore=type==DamageAttackType::IgnoreDefense || atk.ignoreDefense;
    const auto offset=magical?6u:0u;
    const float primary=add32(magical?a.intelligence:a.strength,s.primaryStatBonus);
    if (!finiteNonnegative(primary)) issue(out,"invalid_damage_effective_primary_stat");
    if (errors(out.diagnostics) || !c) return out;
    auto staged=combatRandom?*combatRandom:Pcg32(); const auto drawsBefore=staged.draws();
    const auto draw=[&](uint32_t bound)->std::optional<uint32_t> {
        try { return staged.bounded(bound); }
        catch (const std::overflow_error &) { issue(out,"damage_random_stream_exhausted"); return std::nullopt; }
    };
    const auto finite=[&](const char *stage,std::initializer_list<float> values) {
        for (const auto value:values) if (!std::isfinite(value)) {
            issue(out,"damage_arithmetic_overflow",{{"stage",stage}}); return false;
        }
        return true;
    };
    const auto finish=[&](int value) {
        out.hpDamage=value;
        out.trace.push_back({{"stage","random_publication"},{"draws_before",drawsBefore},{"draws_after",staged.draws()},{"committed",needsRandom}});
        if (needsRandom) *combatRandom=staged;
    };
    const float targetBonus=d.damageMissBonusPercent[request.contactRange==DamageContactRange::Ranged?1:0];
    const float rawMissPercent=add32(add32(add32(a.attackMissDeltaPercent,atk.missDeltaPercent),d.evasionPercent),targetBonus);
    out.trace.push_back({{"stage","target_stuckbonus_on_damage"},{"contact_range",damageContactRangeName(request.contactRange)},
        {"target_melee_ranged_percent",d.damageMissBonusPercent},{"selected_percent",targetBonus},{"source",d.damageMissBonusSource},
        {"classification","inferred additive target miss bonus; source ranged/melee operand meaning annotated"}});
    if (!finite("hit_probability",{rawMissPercent})) return out;
    const float missPercent=std::clamp(rawMissPercent,0.0f,100.0f);
    if (policy.rollHit) {
        const auto rolled=draw(10000); if (!rolled) return out; const auto roll=*rolled;
        out.missed=float(roll)<mul32(missPercent,100);
        out.trace.push_back({{"stage","hit_roll"},{"classification","inferred additive miss/evasion percentage policy; no native hit formula claim"},
            {"miss_percent",missPercent},{"roll_0_9999",roll},{"missed",out.missed}});
        if (out.missed) { finish(0); return out; }
    }
    const float weapon=atk.weaponDamageApply?mul32(magical?a.magicalAttack:a.physicalAttack,s.attackMultiplier):0;
    const float atkBase=s.replacesAttackCoefficients?0:atk.baseDamage;
    const float bonus=s.replacesAttackCoefficients?0:atk.bonusPercent;
    const float bonusFactor=add32(1,div32(bonus,100));
    const float scaledWeapon=mul32(add32(atkBase,weapon),div32(s.percent,100));
    const float independent=mul32(a.independentAttack,div32(s.independentPercent,100));
    const float fixed=mul32(add32(s.fixedDamage,independent),a.independentRate);
    const float primaryFactor=type==DamageAttackType::IgnoreDefense?1:add32(1,div32(primary,(*c)[offset]));
    float damage=mul32(mul32(add32(scaledWeapon,fixed),bonusFactor),primaryFactor);
    if (!finite("attack_and_skill",{weapon,bonusFactor,scaledWeapon,independent,fixed,primaryFactor,damage})) return out;
    out.trace.push_back({{"stage","attack_and_skill"},{"type",damageAttackTypeName(type)},{"weapon_base",weapon},{"atk_base",atkBase},
        {"percent",s.percent},{"scaled_base_and_weapon",scaledWeapon},{"fixed_group",fixed},{"independent_component",independent},
        {"coefficient_mode",s.replacesAttackCoefficients?"skill replaces ATK base/bonus":"compose ATK and skill"},
        {"authored_atk_base",atk.baseDamage},{"authored_atk_bonus",atk.bonusPercent},{"effective_bonus_factor",bonusFactor},
        {"primary_stat",primary},{"primary_divisor",(*c)[offset]},{"primary_factor",primaryFactor},{"damage",damage}});
    int element=atk.element;
    if (element==4 && atk.weaponDamageApply) element=a.weaponElement;
    if (element!=4) {
        const float difference=sub32(a.elementalAttack[size_t(element)],d.elementalResistance[size_t(element)]);
        const float rawFactor=div32(add32((*c)[12],mul32(difference,(*c)[13])),100);
        if (!finite("element",{difference,rawFactor})) return out;
        const float factor=std::max(0.0f,rawFactor);
        damage=mul32(damage,factor);
        if (!finite("element_damage",{damage})) return out;
        out.trace.push_back({{"stage","element"},{"classification","inferred one effective element; source base includes 105, no second 1.05"},
            {"element",element},{"attack_minus_resistance",difference},{"base_constant",(*c)[12]},{"rate_constant",(*c)[13]},{"factor",factor},{"damage",damage}});
    }
    if (policy.randomVariation) {
        const float randomBase=type==DamageAttackType::IgnoreDefense?mul32(damage,policy.ignoreDefenseRandomRate):add32((*c)[offset+4],mul32(float(a.level),(*c)[offset+5]));
        const auto rolled=draw(1000); if (!rolled) return out; const auto roll=*rolled;
        const float variation=add32(-randomBase,mul32(mul32(randomBase,2),div32(float(roll),999)));
        damage=add32(damage,variation);
        if (!finite("random_variation",{randomBase,variation,damage})) return out;
        out.trace.push_back({{"stage","random_variation"},{"random_base",randomBase},{"roll_0_999",roll},{"variation",variation},{"damage",damage}});
    }
    const float defense=magical?d.magicalDefense:d.physicalDefense;
    const float rawDenominator=ignore?1:add32(mul32(float(a.level),(*c)[offset+2]),defense);
    if (!finite("defense_denominator",{rawDenominator})) return out;
    const float denominator=std::max(1.0f,rawDenominator);
    const float defenseRate=ignore?0:div32(defense,denominator);
    const float defenseMultiplier=ignore?1:std::max(policy.minimumDefenseMultiplier,sub32(1,defenseRate));
    damage=mul32(damage,defenseMultiplier);
    if (!finite("target_defense",{defenseRate,defenseMultiplier,damage})) return out;
    out.trace.push_back({{"stage","target_defense"},{"target_level",d.level},{"attacker_basis_level",a.level},{"defense",defense},
        {"level_constant",(*c)[offset+2]},{"denominator",denominator},{"rate",defenseRate},{"multiplier",defenseMultiplier},{"ignored",ignore},{"damage",damage}});
    const float equipmentAbsolute=atk.weaponDamageApply?(magical?a.magicalAbsoluteDamage:a.physicalAbsoluteDamage):0;
    const float absolute=mul32(add32(atk.absoluteDamage,equipmentAbsolute),bonusFactor);
    damage=add32(damage,absolute);
    const float absoluteDefense=magical?d.magicalAbsoluteDefensePercent:d.physicalAbsoluteDefensePercent;
    if (!finite("absolute_damage",{absolute,damage})) return out;
    damage=mul32(damage,sub32(1,div32(absoluteDefense,100)));
    if (!finite("absolute_defense",{damage})) return out;
    damage=std::max(0.0f,damage);
    out.trace.push_back({{"stage","absolute_damage_and_reduction"},{"atk_absolute",atk.absoluteDamage},{"equipment_absolute",equipmentAbsolute},
        {"absolute_damage",absolute},{"absolute_defense_percent",absoluteDefense},{"classification","absolute bypasses ratio defense; absolute-defense percentage applies afterwards"},{"damage",damage}});
    if (policy.rollCritical) {
        const float rawChance=add32(add32(policy.baseCriticalPercent,atk.criticalBonusPercent),magical?a.magicalCriticalBonusPercent:a.physicalCriticalBonusPercent);
        if (!finite("critical_probability",{rawChance})) return out;
        const float chance=std::clamp(rawChance,0.0f,100.0f);
        const auto rolled=draw(10000); if (!rolled) return out; const auto roll=*rolled;
        out.critical=float(roll)<mul32(chance,100);
        if (out.critical) { damage=mul32(damage,policy.criticalMultiplier); damage=mul32(damage,s.criticalMultiplier); }
        out.trace.push_back({{"stage","critical"},{"chance_percent",chance},{"roll_0_9999",roll},{"critical",out.critical},{"multiplier",policy.criticalMultiplier},{"skill_critical_multiplier",s.criticalMultiplier},{"damage",damage}});
    }
    damage=mul32(damage,s.totalMultiplier);
    const size_t categoryIndex=d.targetCategory==DamageTargetCategory::Human?0:d.targetCategory==DamageTargetCategory::Fort?1:2;
    const float categoryPercent=categoryNeutral?100:atk.targetCategoryPercent[categoryIndex];
    damage=mul32(damage,div32(categoryPercent,100));
    out.trace.push_back({{"stage","target_category_rate"},{"classification","inferred final multiplier before integer storage"},
        {"target_category",damageTargetCategoryName(d.targetCategory)},{"percent",categoryPercent},
        {"source_rates",atk.targetCategoryPercent},{"neutral_all_categories",categoryNeutral},{"damage",std::isfinite(damage)?Json(damage):Json()}});
    if (!std::isfinite(damage) || double(damage)>=2147483648.0) {
        issue(out,"damage_arithmetic_overflow",{{"stage","final_damage"},{"value",std::isfinite(damage)?Json(damage):Json()}}); return out;
    }
    const int result=categoryPercent==0?0:int32_t(std::max(1.0f,damage));
    out.trace.push_back({{"stage","final_damage"},{"total_multiplier",s.totalMultiplier},{"stored_float32",damage},
        {"minimum",categoryPercent==0?0:1},{"integer_conversion","truncate toward zero after finite signed-i32 range check"},{"hp_damage",result}});
    finish(result); return out;
}
} // namespace dnf
