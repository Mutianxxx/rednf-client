#include "dnf/monster_combat_attributes.hpp"
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
void diagnostic(Json &values, const char *kind, const char *severity, Json details = Json::object()) {
    details["kind"] = kind; details["severity"] = severity;
    values.push_back(std::move(details));
}
bool errors(const Json &values) {
    for (const auto &value : values) if (value.value("severity",std::string())=="error") return true;
    return false;
}
Json ref(const Script &script, size_t offset = 0, size_t length = 0, size_t ordinal = 0) {
    SourceRef source;
    source.packageIdentity=script.source.value("package_identity",std::string());
    source.memberPath=script.path; source.memberSha256=sha256(script.rawBytes);
    source.literalPath=script.source.value("literal_path",script.path);
    source.byteOffset=offset;
    source.byteLength=length?length:script.rawBytes.size()-std::min(offset,script.rawBytes.size());
    source.ordinal=ordinal; source.scope="monster_combat_attributes";
    return source.json();
}
float tableAttackMissDelta(int raw) {
    // 1031 0x12BBDF1..0x12BBE4F: int -> float32, multiply literal
    // 0x1565CC0. Keep the two conversions explicit, independent of FMA.
    volatile float value=float(raw), scale=0.01f;
    volatile float result=value*scale;return result;
}
Json tableAttackMissReceipt(const Script &table,size_t row,int level,int raw) {
    return {{"policy","inferred-1031-table-attack-miss-v1"},{"classification","inferred_beta"},
        {"source",ref(table,2+(row+11)*5,5,row+11)},{"level",level},{"raw_column",11},{"raw_value",raw},
        {"evaluated_attack_miss_delta_percent",tableAttackMissDelta(raw)},
        {"operation","float32(raw column11) * float32(0.01); positive attacker miss delta; no target evasion alias"},
        {"native_exe_sha256","246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264"},
        {"native_producer","0x12BBDF1..0x12BBE4F -> attribute+0x4F8"},
        {"native_reader","0x875F99..0x875FDA attacker getter; 0x876066..0x8760B6 additive roll"},
        {"pending","protected continuation and complete original miss arithmetic/phase; beta roll policy remains inferred"}};
}
Json fieldRef(const Script &script, size_t ordinal) {
    const auto &field=script.fields.at(ordinal);
    const size_t end=ordinal+1<script.fields.size()?script.fields[ordinal+1].offset:script.rawBytes.size();
    return ref(script,field.offset,end>=field.offset?end-field.offset:0,ordinal);
}
// Mirror the HP model's PvE scope boundary, including type-5 category keys.
std::vector<size_t> candidates(const Script &script,const std::string &wanted) {
    std::vector<size_t> result;
    bool category=false,traits=false,excluded=false;
    for(size_t i=0;i<script.fields.size();++i) {
        const auto tag=normalize(script.fields[i].tag);
        if(tag=="[/ability category]") {category=false;continue;}
        if(tag=="[/category]") {traits=false;continue;}
        if(tag=="[/pvp]" || tag=="[/warroom]" || tag=="[/death tower]") {excluded=false;continue;}
        if(!category && !traits && !excluded && tag==wanted) result.push_back(i);
        if(tag=="[ability category]") category=true;
        if(tag=="[category]") traits=true;
        if(tag=="[pvp]" || tag=="[warroom]" || tag=="[death tower]") excluded=true;
    }
    return result;
}
std::optional<size_t> selected(const Script &script,const std::string &tag,Json &diagnostics) {
    const auto found=candidates(script,tag);
    if(found.size()==1) return found.front();
    if(found.size()>1) {
        Json fields=Json::array();
        for(const auto i:found) fields.push_back({{"source",fieldRef(script,i)},{"values",script.fields[i].values}});
        diagnostic(diagnostics,"ambiguous_monster_combat_field","error",{{"tag",tag},{"candidates",fields}});
    }
    return std::nullopt;
}
bool number(const Json &value,double &out) {
    if(!value.is_number()) return false;
    out=value.get<double>();return std::isfinite(out);
}
bool integer(double value,int &out,bool signedValue=false) {
    if(!std::isfinite(value) || value<(signedValue?double(std::numeric_limits<int>::min()):0.0) ||
        value>double(std::numeric_limits<int>::max())) return false;
    out=int(value);return true;
}
Json categoryValues(const Script &script,size_t ordinal) {
    if(script.tokens.empty()) return script.fields[ordinal].values;
    Json result=Json::array();bool inside=false;
    for(const auto &token:script.tokens) {
        if(!inside) {if(token.at("offset")==script.fields[ordinal].offset) inside=true;continue;}
        const auto &value=token.at("value");
        if(value.is_string() && normalize(value.get<std::string>())=="[/ability category]") break;
        result.push_back(value);
    }
    return result;
}
Json document(const Script &script) {
    Json fields=Json::array();
    for(const auto &field:script.fields) fields.push_back({{"tag",field.tag},{"values",field.values},{"offset",field.offset}});
    return {{"path",script.path},{"source",script.source},{"raw_bytes",script.rawBytes},{"fields",fields},{"tokens",script.tokens}};
}
struct CombatBinding {const char *tag,*category,*name;size_t column;int MonsterCombatAttributeValues::*member;};
const CombatBinding bindings[]={
    {"[physical attack]","[physical_attack]","physical_attack_coefficient",1,&MonsterCombatAttributeValues::physicalAttackCoefficient},
    {"[magical attack]","[magical_attack]","magical_attack_coefficient",2,&MonsterCombatAttributeValues::magicalAttackCoefficient},
    {"[physical defense]","[physical_defense]","physical_defense_coefficient",3,&MonsterCombatAttributeValues::physicalDefenseCoefficient},
    {"[magical defense]","[magical_defense]","magical_defense_coefficient",4,&MonsterCombatAttributeValues::magicalDefenseCoefficient},
    {"[equipment physical attack]","[equipment_physical_attack]","equipment_physical_attack",7,&MonsterCombatAttributeValues::equipmentPhysicalAttack},
    {"[equipment magical attack]","[equipment_magical_attack]","equipment_magical_attack",9,&MonsterCombatAttributeValues::equipmentMagicalAttack},
    {"[equipment physical defense]","[equipment_physical_defense]","equipment_physical_defense",8,&MonsterCombatAttributeValues::equipmentPhysicalDefense},
    {"[equipment magical defense]","[equipment_magical_defense]","equipment_magical_defense",10,&MonsterCombatAttributeValues::equipmentMagicalDefense}
};
const char *elements[]={"fire","water","dark","light"};
const char *statuses[]={"slow","freeze","poison","stun","curse","blind","lightning","stone","sleep",
    "burn","weapon break","bleeding","piercing","stuck","confuse","hold","armor break"};
struct LevelRange {int low=0,high=0;std::optional<size_t> ordinal;};
std::optional<double> endpoint(const Script &script,const std::string &tag,const LevelRange &range,int level,
                              Json &trace,Json &diagnostics,bool signedValue) {
    const auto index=selected(script,tag,diagnostics);
    if(!index) return std::nullopt;
    const auto &values=script.fields[*index].values;double first=0,last=0;
    if(!range.ordinal || values.size()!=2 || !number(values[0],first) || !number(values[1],last) ||
        first<(signedValue?double(std::numeric_limits<int>::min()):0.0) || last<(signedValue?double(std::numeric_limits<int>::min()):0.0) ||
        first>double(std::numeric_limits<int>::max()) || last>double(std::numeric_limits<int>::max())) {
        diagnostic(diagnostics,"malformed_monster_combat_endpoints_or_range","error",
            {{"tag",tag},{"source",fieldRef(script,*index)},{"values",values}});
        return std::nullopt;
    }
    const int clamped=std::clamp(level,range.low,range.high);
    const double fraction=range.low==range.high?0:double(clamped-range.low)/double(range.high-range.low);
    const double evaluated=first+(last-first)*fraction;
    trace.push_back({{"stage","mob_combat_endpoint"},{"tag",tag},{"source",fieldRef(script,*index)},
        {"level_source",fieldRef(script,*range.ordinal)},{"first",first},{"last",last},{"requested_level",level},
        {"evaluated_level",clamped},{"fraction",fraction},{"interpolated",evaluated}});
    if(clamped!=level) diagnostic(diagnostics,"monster_combat_endpoint_level_clamped","warning",{{"tag",tag},{"requested",level},{"evaluated",clamped}});
    if(range.low==range.high && first!=last)
        diagnostic(diagnostics,"single_level_monster_combat_conflicting_endpoints","warning",{{"tag",tag},{"first",first},{"last",last}});
    return evaluated;
}
void applyEndpoint(const Script &script,const std::string &tag,const LevelRange &range,int level,int &target,
                   Json &trace,Json &diagnostics,bool signedValue=false) {
    if(const auto value=endpoint(script,tag,range,level,trace,diagnostics,signedValue)) {
        int converted=0;
        if(!integer(*value,converted,signedValue))
            diagnostic(diagnostics,"invalid_monster_combat_endpoint_result","error",{{"tag",tag},{"value",*value}});
        else {
            trace.push_back({{"stage","combat_endpoint_integer_consumer"},{"tag",tag},{"before",target},{"after",converted},
                {"rounding","truncate_toward_zero_at_integer_consumer"}});
            target=converted;
        }
    }
}
} // namespace

MonsterCombatAttributePolicy MonsterCombatAttributePolicy::inferredMobCombatTableV1() {return {"inferred-mob-combat-table-v1"};}
Json MonsterCombatAttributePolicy::describe() const {
    return {{"id",id},{"classification","inferred_beta"},{"native_pc_parity","pending"},
        {"arithmetic","binary64 endpoint interpolation; truncate toward zero at each integer consumer; no final damage assembly"},
        {"basis",Json::array({
            {{"kind","annotated_sample"},{"path","newmonstersample.mob"},{"encoding","CP949"},
             {"sha256","b37eb5e8dc0014c320e3a4596c457e5a2d56d431522ef0c020f74af251172bda"},{"lines",Json::array({31,33,34,35,36,37,41,59,61,65,68,71,86})}},
            {{"kind","cross_version_server_reference"},{"path","STMonsterScript/ImportMonsterBaseTable.inc"},
             {"sha256","ce0b8e18e0c03aa16cae5dca17abc7e3a5b2c0e55258ad950c65db4cfad3d223"}},
            {{"kind","cross_version_server_reference"},{"path","STMonsterScript/setBasicAbilityByLevel.inc"},
             {"sha256","6134a5e1586708e93eac4497dae5ae56a05191619852487aca259e4fd7233553"}},
            {{"kind","cross_version_server_reference"},{"path","MonsterAbilityLeafC3/upgradeAbilityByMonsterParameterCategory.inc"},
             {"sha256","1e5b497b6345c1e2dfdf4cc760400ee37f87042e58c8a8eb0f57bb7f51745881"}}
        })},
        {"raw_columns",{{"physical_attack_coefficient",1},{"magical_attack_coefficient",2},{"physical_defense_coefficient",3},
            {"magical_defense_coefficient",4},{"hp_external_authority",5},{"mp_external_authority",6},
            {"equipment_physical_attack",7},{"equipment_physical_defense",8},{"equipment_magical_attack",9},{"equipment_magical_defense",10},{"table_attack_miss_delta",11}}},
        {"inferences",Json::array({"semantic category names select their own coefficient/equipment group; no enum-number transplant",
            "MOB resistance tag meanings follow annotated sample; server resistTable/elemAttack names disagree and are not PC proof",
            "table 13..16 add elemental attack; table 17..20 add elemental resistance in fire/water/dark/light order",
            "absent absolute/critical/hit bonuses are neutral; authored nonzero unresolved terms block"})},
        {"pending",Json::array({"protected raw11 miss outcome continuation and complete native miss formula","difficulty/party/named/champion rules",
            "PC endpoint override consumers and float32 edges","final attribute conversion and damage consumers","AI/motion/status application"})}};
}
Json MonsterCombatAttributeValues::snapshot() const {
    Json result=preserved;
    for(const auto &binding:bindings) result[binding.name]=this->*binding.member;
    result["elemental_attack"]=elementalAttack;result["elemental_resistance"]=elementalResistance;
    result["status_resistance"]=statusResistance;
    result["element_order"]=Json::array({"fire","water","dark","light"});
    result["status_order"]=Json::array();
    for(const auto status:statuses) result["status_order"].push_back(status);
    result["physical_critical_rate"]=physicalCriticalRate;result["magical_critical_rate"]=magicalCriticalRate;
    result["hit_rate_bonus"]=hitRateBonus;result["evasion_rate_bonus"]=evasionRateBonus;
    result["absolute_damage"]=absoluteDamage;result["flat_damage_reduction"]=flatDamageReduction;
    result["absolute_defense_rate"]=absoluteDefenseRate;result["absolute_damage_resistance_rate"]=absoluteDamageResistanceRate;
    result["absolute_defense_ignore_rate"]=absoluteDefenseIgnoreRate;
    result["table_attack_miss_delta_percent"]=tableAttackMissDeltaPercent;
    result["table_attack_miss_source"]=tableAttackMissSource;
    result["damage_miss_bonus_percent"]=damageMissBonusPercent;
    result["damage_miss_bonus_source"]=damageMissBonusSource;
    return result;
}
Json MonsterCombatAttributes::snapshot(bool includeSource) const {
    Json result=preserved;
    result["schema"]=1;result["policy"]=policy;result["classification"]="inferred_beta";
    result["level"]=level;result["boss"]=boss;result["usable"]=usable();
    result["attributes"]=attributes?attributes->snapshot():Json();
    result["sources"]=sources;result["trace"]=trace;result["diagnostics"]=diagnostics;
    if(includeSource) result["source_documents"]={{"monster",document(source.monster)},{"table",document(source.table)},
        {"table_selection",source.tableSelection},{"diagnostics",source.diagnostics}};
    else result.erase("source_documents");
    return result;
}
MonsterCombatAttributes evaluateMonsterCombatAttributes(const MonsterAttributeSource &source,int level,bool boss,
                                                       const MonsterCombatAttributePolicy &policy) {
    MonsterCombatAttributes result;result.policy=policy.id;result.level=level;result.boss=boss;result.source=source;
    // This is a source preflight only. Never publish this HP result into an
    // actor or reinterpret previously saved HP with a new combat policy.
    const auto validation=evaluateMonsterHp(source,level,boss,MonsterHpPolicy::inferredMobTableHpV1());
    result.sources=validation.sources;result.sources["monster"]=ref(source.monster);result.sources["table"]=ref(source.table);
    result.diagnostics=validation.diagnostics;
    if(policy.id!="inferred-mob-combat-table-v1") diagnostic(result.diagnostics,"monster_combat_policy_disabled_or_unknown","error");
    const auto monsterIdentity=source.monster.source.value("package_identity",std::string());
    const auto tableIdentity=source.table.source.value("package_identity",std::string());
    if(monsterIdentity.empty() || monsterIdentity!=tableIdentity)
        diagnostic(result.diagnostics,"monster_combat_source_identity_mismatch","error",{{"monster",monsterIdentity},{"table",tableIdentity}});
    if(!validation.usable() || errors(result.diagnostics)) return result;
    size_t row=0;
    for(;row<source.table.tokens.size();row+=24) if(source.table.tokens[row]["value"]==level) break;
    Json columns=Json::array();
    for(size_t i=0;i<24;++i) columns.push_back(source.table.tokens[row+i]["value"]);
    result.trace.push_back({{"stage","exact_level_monster_combat_table"},{"source",ref(source.table,2+row*5,120,row/24)},
        {"columns",columns},{"hp_column_5","external authority; not returned or committed"},{"mp_column_6","external resource consumer"}});
    MonsterCombatAttributeValues values;
    LevelRange range;
    if(const auto index=selected(source.monster,"[level]",result.diagnostics)) {
        // HP preflight has already validated the preserved range shape/type.
        range.low=source.monster.fields[*index].values[0].get<int>();
        range.high=source.monster.fields[*index].values[1].get<int>();range.ordinal=index;
    }
    for(const auto &binding:bindings) {
        int &target=values.*binding.member;
        target=columns[binding.column].get<int>();
        if(target<0) diagnostic(result.diagnostics,"negative_monster_combat_table_value","error",{{"column",binding.column},{"value",target}});
        applyEndpoint(source.monster,binding.tag,range,level,target,result.trace,result.diagnostics);
    }
    for(size_t i=0;i<4;++i) {
        values.elementalAttack[i]=columns[13+i].get<int>();
        int resistance=0;
        applyEndpoint(source.monster,"["+std::string(elements[i])+" resistance]",range,level,resistance,result.trace,result.diagnostics,true);
        const int64_t sum=int64_t(resistance)+columns[17+i].get<int>();
        if(sum<std::numeric_limits<int>::min() || sum>std::numeric_limits<int>::max())
            diagnostic(result.diagnostics,"monster_elemental_resistance_overflow","error",{{"element",elements[i]},{"value",sum}});
        else values.elementalResistance[i]=int(sum);
    }
    for(size_t i=0;i<17;++i) {
        int resistance=0;
        applyEndpoint(source.monster,"["+std::string(statuses[i])+" resistance]",range,level,resistance,result.trace,result.diagnostics,true);
        const int additive=i==13?columns[12].get<int>()/10:columns[23].get<int>();
        const int64_t sum=int64_t(resistance)+additive;
        if(sum<std::numeric_limits<int>::min() || sum>std::numeric_limits<int>::max())
            diagnostic(result.diagnostics,"monster_status_resistance_overflow","error",{{"status",statuses[i]},{"value",sum}});
        else values.statusResistance[i]=int(sum);
    }
    if(const auto index=selected(source.monster,"[stuckbonus on damage]",result.diagnostics)) {
        const auto &raw=source.monster.fields[*index].values;bool valid=raw.size()==4&&range.ordinal.has_value();
        std::array<double,4> endpoints{};
        for(size_t n=0;n<raw.size()&&n<4;++n)valid=number(raw[n],endpoints[n])&&endpoints[n]>=0&&endpoints[n]<=100&&valid;
        if(!valid)diagnostic(result.diagnostics,"malformed_monster_stuckbonus_on_damage","error",{{"values",raw},{"source",fieldRef(source.monster,*index)}});
        else {
            const double position=range.high==range.low?0.0:double(std::clamp(level,range.low,range.high)-range.low)/(range.high-range.low);
            values.damageMissBonusPercent[1]=endpoints[0]+(endpoints[1]-endpoints[0])*position;
            values.damageMissBonusPercent[0]=endpoints[2]+(endpoints[3]-endpoints[2])*position;
            values.damageMissBonusSource={{"policy","inferred-source-stuckbonus-on-damage-v1"},{"classification","inferred_beta"},
                {"source",fieldRef(source.monster,*index)},{"endpoints_ranged_then_melee",raw},{"level",level},{"source_level_range",{range.low,range.high}},
                {"evaluated_melee_ranged_percent",values.damageMissBonusPercent},
                {"basis","CP949 newmonstersample.mob164-166; source endpoints are percent bonus when attacked at distance/close range"},
                {"operation","binary64 clamped endpoint interpolation; target additive miss percentage consumed by real hit roll; native arithmetic pending"}};
            result.trace.push_back({{"stage","source_stuckbonus_on_damage"},{"receipt",values.damageMissBonusSource}});
        }
    }
    const int tableMissRaw=columns[11].get<int>();
    values.tableAttackMissDeltaPercent=tableAttackMissDelta(tableMissRaw);
    values.tableAttackMissSource=tableAttackMissReceipt(source.table,row,level,tableMissRaw);
    result.trace.push_back({{"stage","source_table_attack_miss_delta"},{"receipt",values.tableAttackMissSource}});
    result.trace.push_back({{"stage","resistance_table_additions"},{"element_attack_columns",Json::array({13,14,15,16})},
        {"element_resistance_columns",Json::array({17,18,19,20})},{"stuck_resistance_column_12_divisor",10},
        {"other_status_resistance_column",23},{"attributes",values.snapshot()}});
    if(const auto category=selected(source.monster,"[ability category]",result.diagnostics)) {
        const auto tuples=categoryValues(source.monster,*category);
        for(size_t i=0;i+2<tuples.size();i+=3) {
            const auto tag=normalize(tuples[i].get<std::string>());
            const auto op=tuples[i+1].get<std::string>();double operand=0;number(tuples[i+2],operand);
            const CombatBinding *binding=nullptr;
            for(const auto &candidate:bindings) if(tag==candidate.category) {binding=&candidate;break;}
            Json entry={{"stage","ordered_monster_combat_category"},{"source",fieldRef(source.monster,*category)},
                {"tuple_ordinal",i/3},{"tag",tuples[i]},{"operator",op},{"value",operand}};
            if(binding || tag=="[stuck]") {
                int &target=binding?values.*binding->member:values.statusResistance[13];
                const double computed=op=="*"?double(target)*operand/100.0:double(target)+operand;
                int converted=0;
                entry["before"]=target;entry["computed"]=computed;
                if(!integer(computed,converted,tag=="[stuck]"))
                    diagnostic(result.diagnostics,"invalid_monster_combat_category_result","error",{{"tag",tag},{"tuple_ordinal",i/3},{"value",computed}});
                else target=converted;
                entry["after"]=target;entry["applied"]=true;entry["rounding"]="truncate_toward_zero_at_integer_consumer";
            } else if(tag=="[hp max]" || tag=="[hp max boss]") {
                entry["applied"]=false;entry["external_consumer"]="independent_monster_hp_authority";
            } else if(tag=="[attack_speed]" || tag=="[move_speed]" || tag=="[hit_recovery]") {
                entry["applied"]=false;entry["external_consumer"]="monster_motion_and_response_attributes";
                diagnostic(result.diagnostics,"monster_category_requires_motion_consumer","warning",{{"tag",tag},{"tuple_ordinal",i/3}});
            } else diagnostic(result.diagnostics,"unsupported_monster_combat_category","error",{{"tag",tag},{"tuple_ordinal",i/3},{"source",fieldRef(source.monster,*category)}});
            result.trace.push_back(std::move(entry));
        }
    }
    // A neutral explicit value is harmless; a nonzero authored damage mechanic
    // with an unresolved consumer must block rather than become a silent zero.
    const std::vector<std::string> neutralOnly={"[physical critical hit]","[magical critical hit]","[physical critical hit rate]",
        "[magical critical hit rate]","[attack success rate]","[hit rate]","[evasion]","[evasion rate]","[absolute damage]",
        "[damage reduce]","[absolute defense]","[absolute damage resistance rate]","[absolute defense ignore rate]",
        "[hp regen rate]","[destroy count damage]"};
    std::set<std::string> consumed={"[stuckbonus on damage]"};
    for(const auto &binding:bindings) consumed.insert(binding.tag);
    for(const auto element:elements) consumed.insert("["+std::string(element)+" resistance]");
    for(const auto status:statuses) consumed.insert("["+std::string(status)+" resistance]");
    for(const auto &tag:neutralOnly) if(const auto index=selected(source.monster,tag,result.diagnostics)) {
        consumed.insert(tag);
        const auto &raw=source.monster.fields[*index].values;
        bool neutral=!raw.empty(),valid=!raw.empty();
        for(const auto &item:raw) {double value=0;const bool numeric=number(item,value);valid=valid && numeric;neutral=neutral && numeric && value==0;}
        result.trace.push_back({{"stage","unresolved_combat_input_neutral_check"},{"tag",tag},{"values",raw},{"neutral",neutral},{"source",fieldRef(source.monster,*index)}});
        if(!valid || !neutral) diagnostic(result.diagnostics,"unsupported_monster_combat_input","error",{{"tag",tag},{"values",raw},
            {"source",fieldRef(source.monster,*index)},{"reason","authored nonneutral damage/critical/hit/regen mechanism lacks a verified or complete inferred consumer"}});
    }
    const std::set<std::string> externalFields={"[hp max]","[mp max]","[hp regen speed]","[mp regen speed]",
        "[move speed]","[attack speed]","[cast speed]","[hit recovery]","[destroy count]",
        "[damage motion 1]","[damage motion 2]","[damage action 1]","[damage action 2]","[damage sound]",
        "[attack info]","[etc attack info]","[attack kind]","[attack delay]","[attack motion]","[attack action]",
        "[attack sound]","[counter attack]"};
    std::set<std::string> scanned;
    for(const auto &field:source.monster.fields) {
        const auto tag=normalize(field.tag);
        if(tag.rfind("[/",0)==0 || consumed.count(tag) || externalFields.count(tag) || !scanned.insert(tag).second ||
            candidates(source.monster,tag).empty() || tag.find("[targeting ")==0) continue;
        const bool relevant=tag.find("resistan")!=std::string::npos || tag.find("critical")!=std::string::npos ||
            tag.find("absolute")!=std::string::npos || tag.find("damage")!=std::string::npos ||
            tag.find("defense")!=std::string::npos || tag.find("attack bonus")!=std::string::npos ||
            tag.find("attack rate")!=std::string::npos || tag.find("attack besed")!=std::string::npos ||
            tag.find("hit rate")!=std::string::npos || tag.find("evasion")!=std::string::npos;
        if(relevant) {
            Json refs=Json::array();
            for(const auto index:candidates(source.monster,tag))
                refs.push_back({{"source",fieldRef(source.monster,index)},{"values",source.monster.fields[index].values}});
            diagnostic(result.diagnostics,"unsupported_monster_combat_field","error",{{"tag",tag},{"candidates",refs},
                {"reason","potential material damage field requires explicit semantics or a separate capability consumer"}});
        }
    }
    result.trace.push_back({{"stage","combat_attribute_capability_boundary"},{"motion_table_columns_external",Json::array({21,22})},
        {"motion_table_values",Json::array({columns[21],columns[22]})},{"live_hp_recomputed_or_published",false},
        {"final_damage_assembled",false},{"difficulty_party_champion","separate source consumers"},{"native_pc_parity","pending"}});
    if(!errors(result.diagnostics)) result.attributes=values;
    return result;
}

MonsterCombatAttributes restoreMonsterCombatAttributes(const Json &saved,const MonsterAttributeSource &expectedSource) {
    const auto reject=[](const std::string &reason) {
        throw std::invalid_argument("Invalid frozen monster combat receipt: "+reason);
    };
    const auto storedInt=[&](const Json &value,const std::string &name,bool signedValue=false) {
        if(!value.is_number_integer()) reject("noninteger "+name);
        // JSON unsigned values must be bounded before conversion; binary64
        // is not used for saved integer range checks or reconstruction.
        if(value.is_number_unsigned() && value.get<uint64_t>()>uint64_t(std::numeric_limits<int>::max()))
            reject("overflowing "+name);
        if(value<std::numeric_limits<int>::min() || value>std::numeric_limits<int>::max()) reject("overflowing "+name);
        const int result=value.get<int>();
        if(!signedValue && result<0) reject("negative "+name);
        return result;
    };
    if(!saved.is_object()) reject("root must be an object");
    if(!saved.contains("schema") || storedInt(saved.at("schema"),"schema")!=1) reject("unsupported schema");
    if(saved.at("policy")!="inferred-mob-combat-table-v1" || saved.at("classification")!="inferred_beta")
        reject("unknown policy or evidence classification");
    if(!saved.at("usable").is_boolean() || !saved.at("usable").get<bool>()) reject("receipt is not usable");
    MonsterCombatAttributes result;
    result.policy=saved.at("policy").get<std::string>();
    result.level=storedInt(saved.at("level"),"level");
    if(result.level<1) reject("nonpositive level");
    if(!saved.at("boss").is_boolean()) reject("boss role must be boolean");
    result.boss=saved.at("boss").get<bool>();
    const auto &sources=saved.at("sources");
    if(!sources.is_object() || expectedSource.monster.path.empty() || expectedSource.table.path.empty() ||
        expectedSource.monster.rawBytes.empty() || expectedSource.table.rawBytes.empty() || errors(expectedSource.diagnostics))
        reject("unusable expected source documents");
    const auto monsterIdentity=expectedSource.monster.source.value("package_identity",std::string());
    if(monsterIdentity.empty() || monsterIdentity!=expectedSource.table.source.value("package_identity",std::string()))
        reject("expected package identities disagree");
    const Script *documents[]={&expectedSource.monster,&expectedSource.table};
    const char *sourceNames[]={"monster","table"};
    for(size_t n=0;n<2;++n) {
        const auto expected=ref(*documents[n]);
        const auto &actual=sources.at(sourceNames[n]);
        if(!actual.is_object()) reject(std::string(sourceNames[n])+" source reference is not an object");
        for(auto i=expected.begin();i!=expected.end();++i)
            if(!actual.contains(i.key()) || actual.at(i.key())!=i.value()) reject(std::string(sourceNames[n])+" source mismatch: "+i.key());
    }
    if(sources.at("table_selection")!=expectedSource.tableSelection) reject("source table selection mismatch");
    // Selection identity is immutable source metadata, not a request to rebuild
    // attributes. Explicit source base-table overrides remain legal for either
    // role; the two ordinary role-selected table names must remain consistent.
    if((expectedSource.tableSelection=="map_boss_role" && !result.boss) ||
       ((expectedSource.tableSelection=="normal_pve_role" || expectedSource.tableSelection=="source_summon_ability_table") && result.boss))
        reject("saved role disagrees with source table selection");
    const auto &attributes=saved.at("attributes");
    if(!attributes.is_object()) reject("attributes must be an object");
    MonsterCombatAttributeValues values;
    for(const auto &binding:bindings) values.*binding.member=storedInt(attributes.at(binding.name),binding.name);
    const auto restoreArray=[&](const char *name,auto &target) {
        const auto &array=attributes.at(name);
        if(!array.is_array() || array.size()!=target.size()) reject(std::string(name)+" has incorrect width");
        for(size_t i=0;i<target.size();++i) target[i]=storedInt(array[i],std::string(name)+"/"+std::to_string(i),true);
    };
    restoreArray("elemental_attack",values.elementalAttack);
    restoreArray("elemental_resistance",values.elementalResistance);
    restoreArray("status_resistance",values.statusResistance);
    Json statusOrder=Json::array();for(const auto status:statuses) statusOrder.push_back(status);
    if(attributes.at("element_order")!=Json::array({"fire","water","dark","light"}) || attributes.at("status_order")!=statusOrder)
        reject("resistance axis ordering mismatch");
    struct NeutralBinding {const char *name;double MonsterCombatAttributeValues::*member;};
    const NeutralBinding neutral[]={
        {"physical_critical_rate",&MonsterCombatAttributeValues::physicalCriticalRate},
        {"magical_critical_rate",&MonsterCombatAttributeValues::magicalCriticalRate},
        {"hit_rate_bonus",&MonsterCombatAttributeValues::hitRateBonus},{"evasion_rate_bonus",&MonsterCombatAttributeValues::evasionRateBonus},
        {"absolute_damage",&MonsterCombatAttributeValues::absoluteDamage},{"flat_damage_reduction",&MonsterCombatAttributeValues::flatDamageReduction},
        {"absolute_defense_rate",&MonsterCombatAttributeValues::absoluteDefenseRate},
        {"absolute_damage_resistance_rate",&MonsterCombatAttributeValues::absoluteDamageResistanceRate},
        {"absolute_defense_ignore_rate",&MonsterCombatAttributeValues::absoluteDefenseIgnoreRate}};
    for(const auto &binding:neutral) {
        double value=0;
        if(!number(attributes.at(binding.name),value) || value!=0) reject(std::string(binding.name)+" is nonneutral under this policy");
        values.*binding.member=value;
    }
    if(attributes.contains("damage_miss_bonus_percent")!=attributes.contains("damage_miss_bonus_source"))reject("partial stuckbonus receipt");
    if(attributes.contains("damage_miss_bonus_percent")) {
        const auto &raw=attributes.at("damage_miss_bonus_percent");
        if(!raw.is_array()||raw.size()!=2||!attributes.at("damage_miss_bonus_source").is_object())reject("malformed stuckbonus receipt");
        for(size_t i=0;i<2;++i)if(!number(raw[i],values.damageMissBonusPercent[i])||values.damageMissBonusPercent[i]<0||values.damageMissBonusPercent[i]>100)
            reject("out-of-range stuckbonus percentage");
        values.damageMissBonusSource=attributes.at("damage_miss_bonus_source");
        if(!values.damageMissBonusSource.empty()) {
            const auto indices=candidates(expectedSource.monster,"[stuckbonus on damage]");
            const auto ranges=candidates(expectedSource.monster,"[level]");
            if(indices.size()!=1||ranges.size()!=1||values.damageMissBonusSource.at("policy")!="inferred-source-stuckbonus-on-damage-v1"||
                values.damageMissBonusSource.at("classification")!="inferred_beta"||
                values.damageMissBonusSource.at("source")!=fieldRef(expectedSource.monster,indices[0])||
                values.damageMissBonusSource.at("endpoints_ranged_then_melee")!=expectedSource.monster.fields[indices[0]].values||
                values.damageMissBonusSource.at("source_level_range")!=expectedSource.monster.fields[ranges[0]].values||
                values.damageMissBonusSource.at("level")!=result.level||
                values.damageMissBonusSource.at("evaluated_melee_ranged_percent")!=Json(values.damageMissBonusPercent))reject("stuckbonus source binding disagrees");
        }else {
            if(values.damageMissBonusPercent!=std::array<double,2>{})reject("nonzero stuckbonus needs bound source receipt");
            for(const auto index:candidates(expectedSource.monster,"[stuckbonus on damage]"))
                for(const auto &value:expectedSource.monster.fields[index].values)if(!value.is_number()||value.get<double>()!=0)
                    reject("nonneutral authored stuckbonus needs source receipt");
        }
    }else {
        // Historical v1 receipts admitted only zero. Never recompute/reinterpret
        // a nonzero current source while decoding an old frozen receipt.
        for(const auto index:candidates(expectedSource.monster,"[stuckbonus on damage]"))
            for(const auto &value:expectedSource.monster.fields[index].values)if(!value.is_number()||value.get<double>()!=0)
                reject("legacy receipt cannot drop authored stuckbonus");
    }
    const auto &trace=saved.at("trace"),&diagnostics=saved.at("diagnostics");
    if(!trace.is_array() || trace.empty() || !diagnostics.is_array()) reject("trace/diagnostics shape");
    for(const auto &entry:trace) if(!entry.is_object()) reject("trace entry must be an object");
    const auto &rowReceipt=trace[0];
    if(rowReceipt.at("stage")!="exact_level_monster_combat_table" || !rowReceipt.at("columns").is_array() ||
        rowReceipt.at("columns").size()!=24 || storedInt(rowReceipt.at("columns")[0],"table receipt level")!=result.level)
        reject("frozen row receipt disagrees with level");
    bool rowMatched=false;size_t matchedRow=0;
    const auto &tokens=expectedSource.table.tokens;
    if(tokens.size()%24) reject("expected table has a partial row");
    for(size_t row=0;row+24<=tokens.size();row+=24) if(tokens[row].at("value")==result.level) {
        if(rowMatched) reject("expected table level is ambiguous");
        Json columns=Json::array();
        for(size_t i=0;i<24;++i) columns.push_back(tokens[row+i].at("value"));
        if(rowReceipt.at("columns")!=columns || rowReceipt.at("source")!=ref(expectedSource.table,2+row*5,120,row/24))
            reject("frozen row source does not match expected bytes");
        rowMatched=true;matchedRow=row;
    }
    if(!rowMatched) reject("saved level has no exact source row");
    const int tableMissRaw=storedInt(tokens[matchedRow+11].at("value"),"source raw11",true);
    const bool hasDelta=attributes.contains("table_attack_miss_delta_percent");
    const bool hasReceipt=attributes.contains("table_attack_miss_source");
    if(hasDelta!=hasReceipt)reject("partial table attack miss receipt");
    if(hasDelta) {
        double savedDelta=0;
        if(!number(attributes.at("table_attack_miss_delta_percent"),savedDelta) ||
            savedDelta!=double(tableAttackMissDelta(tableMissRaw)))reject("table attack miss result disagrees with source raw11");
        const auto expected=tableAttackMissReceipt(expectedSource.table,matchedRow,result.level,tableMissRaw);
        if(attributes.at("table_attack_miss_source")!=expected)reject("table attack miss source/policy binding disagrees");
        // Validate only this immutable source transform. Never rerun HP or the
        // complete attribute evaluator while restoring an old frozen receipt.
        values.tableAttackMissDeltaPercent=float(savedDelta);values.tableAttackMissSource=expected;
    }else if(tableMissRaw!=0)reject("legacy receipt cannot drop nonzero source raw11");
    for(const auto &entry:diagnostics)
        if(!entry.is_object() || !entry.contains("severity") || !entry.at("severity").is_string() || entry.at("severity")=="error")
            reject("saved diagnostic is malformed or contains a blocking error");
    if(saved.contains("source_documents")) {
        const auto &embedded=saved.at("source_documents");
        if(!embedded.is_object() || embedded.at("monster")!=document(expectedSource.monster) ||
            embedded.at("table")!=document(expectedSource.table) || embedded.at("table_selection")!=expectedSource.tableSelection ||
            embedded.at("diagnostics")!=expectedSource.diagnostics) reject("embedded source documents mismatch");
    }
    values.preserved=attributes;
    result.attributes=std::move(values);result.source=expectedSource;result.sources=sources;
    result.trace=trace;result.diagnostics=diagnostics;result.preserved=saved;
    return result;
}
} // namespace dnf
