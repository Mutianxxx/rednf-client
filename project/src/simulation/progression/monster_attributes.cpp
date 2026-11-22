#include "dnf/monster_attributes.hpp"
#include "dnf/region.hpp"
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
bool hasErrors(const Json &values) {
    for (const auto &value : values) if (value.value("severity",std::string()) == "error") return true;
    return false;
}
Json sourceRef(const Script &script, size_t offset = 0, size_t length = 0, size_t ordinal = 0,
               const std::string &scope = "monster_attributes") {
    SourceRef ref;
    ref.packageIdentity = script.source.value("package_identity",std::string());
    ref.memberPath = script.path;
    ref.memberSha256 = sha256(script.rawBytes);
    ref.literalPath = script.source.value("literal_path",script.path);
    ref.byteOffset = offset; ref.byteLength = length ? length : script.rawBytes.size()-std::min(offset,script.rawBytes.size());
    ref.ordinal = ordinal; ref.scope = scope;
    return ref.json();
}
Json fieldRef(const Script &script, size_t ordinal) {
    const auto &field = script.fields.at(ordinal);
    const size_t end = ordinal+1 < script.fields.size() ? script.fields[ordinal+1].offset : script.rawBytes.size();
    return sourceRef(script,field.offset,end >= field.offset ? end-field.offset : 0,ordinal);
}
bool integer(const Json &value, int &out) {
    if (!value.is_number_integer() || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) return false;
    out = value.get<int>(); return true;
}
bool number(const Json &value, double &out) {
    if (!value.is_number()) return false;
    out = value.get<double>(); return std::isfinite(out);
}
bool hpInteger(double value, int &out) {
    if (!std::isfinite(value) || value < 1 || value > std::numeric_limits<int>::max()) return false;
    out = int(value); return out > 0;
}
// Category strings sometimes use type-5 tokens too. Never read a category's
// [HP MAX] key as a top-level endpoint merely because Script.fields splits it.
std::vector<size_t> candidates(const Script &script, const std::string &wanted) {
    std::vector<size_t> result;
    bool category = false, traits = false, excludedMode = false;
    for (size_t i=0; i<script.fields.size(); ++i) {
        const auto tag = normalize(script.fields[i].tag);
        if (tag=="[/ability category]") { category=false; continue; }
        if (tag=="[/category]") { traits=false; continue; }
        if (tag=="[/pvp]" || tag=="[/warroom]" || tag=="[/death tower]") { excludedMode=false; continue; }
        if (!category && !traits && !excludedMode && tag==wanted) result.push_back(i);
        if (tag=="[ability category]") category=true;
        if (tag=="[category]") traits=true;
        if (tag=="[pvp]" || tag=="[warroom]" || tag=="[death tower]") excludedMode=true;
    }
    return result;
}
std::optional<size_t> selected(const Script &script, const std::string &tag, Json &diagnostics, bool required = false) {
    const auto found = candidates(script,tag);
    if (found.size()==1) return found.front();
    if (found.empty() && !required) return std::nullopt;
    Json refs = Json::array();
    for (auto i : found) refs.push_back({{"source",fieldRef(script,i)},{"values",script.fields[i].values}});
    diagnostic(diagnostics,found.empty()?"missing_monster_attribute_field":"ambiguous_monster_attribute_field","error",
        {{"tag",tag},{"candidates",refs}});
    return std::nullopt;
}
Json categoryValues(const Script &script, size_t ordinal, Json &diagnostics) {
    const auto &field = script.fields[ordinal];
    if (script.tokens.empty()) return field.values; // Authored parser fixture.
    Json result = Json::array();
    bool inside = false;
    for (const auto &token : script.tokens) {
        if (!inside) {
            if (token.at("offset")==field.offset) inside=true;
            continue;
        }
        const auto &value = token.at("value");
        if (value.is_string() && normalize(value.get<std::string>())=="[/ability category]") return result;
        result.push_back(value);
    }
    diagnostic(diagnostics,"unterminated_monster_ability_category","error",{{"source",fieldRef(script,ordinal)}});
    return result;
}
bool validateDocument(const Script &script, Json &diagnostics) {
    if (script.path.empty() || script.rawBytes.size()<2 || (script.rawBytes.size()-2)%5) {
        diagnostic(diagnostics,"invalid_monster_attribute_source_document","error",{{"path",script.path},{"size",script.rawBytes.size()}});
        return false;
    }
    size_t previous = 0;
    for (size_t i=0; i<script.fields.size(); ++i) {
        const auto offset = script.fields[i].offset;
        if (offset<2 || (offset-2)%5 || offset<=previous || offset>script.rawBytes.size()-5)
            diagnostic(diagnostics,"invalid_monster_attribute_field_span","error",{{"ordinal",i},{"offset",offset},{"path",script.path}});
        previous=offset;
    }
    return !hasErrors(diagnostics);
}
} // namespace

int resolveMonsterLevel(const MonsterSpawn &spawn, int dungeonBasisLevel) {
    if (!spawn.raw.is_array()) throw std::invalid_argument("MAP monster raw placement must be an array");
    if (!spawn.raw.empty()) {
        int flag=0, rawLevel=0;
        if (spawn.raw.size()<3 || !integer(spawn.raw[1],flag) || (flag!=0 && flag!=1) ||
            !integer(spawn.raw[2],rawLevel) || (flag!=0)!=spawn.autoLevel || rawLevel!=spawn.level)
            throw std::invalid_argument("MAP monster level fields are malformed or disagree with the preserved placement");
    }
    if (spawn.autoLevel && dungeonBasisLevel<1)
        throw std::invalid_argument("Auto-level monster requires a positive DGN basis level");
    const int64_t resolved=spawn.autoLevel?int64_t(dungeonBasisLevel)+int64_t(spawn.level):int64_t(spawn.level);
    if (resolved<1 || resolved>std::numeric_limits<int>::max())
        throw std::invalid_argument("MAP monster level is outside positive int storage: " + Json{{"monster",spawn.id},
            {"auto_level",spawn.autoLevel},{"raw_level",spawn.level},{"dungeon_basis_level",dungeonBasisLevel},{"resolved",resolved}}.dump());
    return int(resolved);
}
MonsterHpPolicy MonsterHpPolicy::inferredMobTableHpV1() { return {"inferred-mob-table-hp-v1"}; }
Json MonsterHpPolicy::describe() const {
    return {{"id",id},{"classification","inferred_beta"},
        {"arithmetic","binary64 endpoint interpolation and percent calculation; truncate positive HP at each integer consumer; differs from unverified server float32 multiplication edges"},
        {"basis",Json::array({
            {{"kind","annotated_sample"},{"path","newmonstersample.mob"},{"encoding","CP949"},
             {"sha256","b37eb5e8dc0014c320e3a4596c457e5a2d56d431522ef0c020f74af251172bda"},
             {"lines",Json::array({19,31,41,59,61})}},
            {{"kind","cross_version_server_reference"},{"path","rednf-master/remake/source/DNFServer/GameServer/Game"},
             {"consumers",Json::array({"InitScriptProducers_4/InitMonsterScript_1.inc","STMonsterScript/ImportMonsterBaseTable.inc",
                 "STMonsterScript/setBasicAbilityByLevel.inc","MonsterAbilityLeafC3/upgradeAbilityByMonsterParameterCategory.inc"})}}
        })},
        {"order",Json::array({"exact_level_source_table_hp_column_5","optional_mob_hp_endpoint_override",
            "ordered_hp_category_integer_consumers"})},
        {"native_pc_parity","pending"},
        {"pending",Json::array({"difficulty and party scaling","named registry and champion bonuses",
            "source HP endpoint override vs current PC consumer","HP MAX BOSS selection against MAP boss role"})}};
}
Json MonsterHpResult::snapshot() const {
    return {{"policy",policy},{"classification","inferred_beta"},{"level",level},{"boss",boss},
        {"usable",usable()},{"hp",hp?Json(*hp):Json()},{"sources",sources},{"trace",trace},{"diagnostics",diagnostics}};
}
MonsterAttributeSource readMonsterAttributeSource(const Pvf &pvf, const std::string &path, bool boss) {
    MonsterAttributeSource result;
    result.monster = pvf.script(path);
    int abilityTable=0;
    if (auto i=selected(result.monster,"[ability table]",result.diagnostics)) {
        const auto &values=result.monster.fields[*i].values;
        if (values.size()!=1 || !integer(values[0],abilityTable) || abilityTable<0 || abilityTable>2)
            diagnostic(result.diagnostics,"malformed_monster_ability_table","error",{{"source",fieldRef(result.monster,*i)},{"values",values}});
        else if (abilityTable==2)
            diagnostic(result.diagnostics,"competitive_monster_ability_table_outside_pve_adapter","error",{{"source",fieldRef(result.monster,*i)}});
    }
    std::string tablePath = boss ? "monster/bossmonsterbaseparameter.tbl" :
        abilityTable==1 ? "monster/summonmonsterbaseparameter.tbl" : "monster/commonmonsterbaseparameter.tbl";
    result.tableSelection = boss ? "map_boss_role" : abilityTable==1 ? "source_summon_ability_table" : "normal_pve_role";
    if (auto i=selected(result.monster,"[base table]",result.diagnostics)) {
        const auto &values=result.monster.fields[*i].values;
        if (values.size()!=1 || !values[0].is_string() || values[0].get<std::string>().empty())
            diagnostic(result.diagnostics,"malformed_monster_base_table","error",{{"source",fieldRef(result.monster,*i)},{"values",values}});
        else {
            const auto literal=normalize(values[0].get<std::string>());
            tablePath=literal.rfind("monster/",0)==0?literal:"monster/"+literal;
            const auto relative=std::filesystem::u8path(tablePath).lexically_normal().generic_u8string();
            if (relative!=tablePath || tablePath.rfind("monster/",0)!=0 || tablePath.find(':')!=std::string::npos)
                diagnostic(result.diagnostics,"invalid_monster_base_table_path","error",{{"literal",literal},{"resolved",tablePath}});
            result.tableSelection="explicit_source_base_table";
        }
    }
    if (!hasErrors(result.diagnostics)) {
        if (!pvf.has(tablePath)) diagnostic(result.diagnostics,"missing_monster_base_table","error",{{"path",tablePath}});
        else result.table=pvf.script(tablePath);
    }
    return result;
}

MonsterHpResult evaluateMonsterHp(const MonsterAttributeSource &source, int level, bool boss, const MonsterHpPolicy &policy) {
    MonsterHpResult result;
    result.policy=policy.id; result.level=level; result.boss=boss; result.diagnostics=source.diagnostics;
    result.sources={{"monster",sourceRef(source.monster)},{"table",sourceRef(source.table)},{"table_selection",source.tableSelection}};
    if (policy.id!="inferred-mob-table-hp-v1") diagnostic(result.diagnostics,"monster_hp_policy_disabled_or_unknown","error");
    if (level<1) diagnostic(result.diagnostics,"invalid_monster_spawn_level","error",{{"level",level}});
    if (!validateDocument(source.monster,result.diagnostics) || !validateDocument(source.table,result.diagnostics) || hasErrors(result.diagnostics)) return result;

    // Validate every row, preserving all 24 columns in source tokens. No
    // nearest-row fallback, partial last row or first duplicate level selection.
    const auto &tokens=source.table.tokens;
    if (!source.table.fields.empty() || tokens.empty() || tokens.size()%24 || tokens.size()!=(source.table.rawBytes.size()-2)/5)
        diagnostic(result.diagnostics,"malformed_monster_base_table_shape","error",{{"path",source.table.path},{"token_count",tokens.size()},{"row_width",24}});
    std::set<int> levels;
    std::optional<size_t> row;
    for (size_t i=0; i+24<=tokens.size(); i+=24) {
        int rowLevel=0, hp=0;
        for (size_t j=0;j<24;++j) {
            int value=0, type=0;
            const auto &token=tokens[i+j];
            if (!token.is_object() || !token.contains("value") || !integer(token["value"],value) ||
                !token.contains("type") || !integer(token["type"],type) || type!=2 ||
                !token.contains("offset") || !token["offset"].is_number_integer() || token["offset"]!=2+(i+j)*5)
                diagnostic(result.diagnostics,"malformed_monster_base_table_token","error",{{"ordinal",i+j},{"token",token}});
            if (j==0) rowLevel=value;
            if (j==5) hp=value;
        }
        if (rowLevel<1 || !levels.insert(rowLevel).second)
            diagnostic(result.diagnostics,"invalid_or_duplicate_monster_table_level","error",{{"row",i/24},{"level",rowLevel}});
        if (hp<=0) diagnostic(result.diagnostics,"nonpositive_monster_table_hp","error",{{"row",i/24},{"hp",hp}});
        if (rowLevel==level) row=i;
    }
    if (!row) diagnostic(result.diagnostics,"missing_exact_monster_table_level","error",{{"level",level},{"table",source.table.path}});
    if (hasErrors(result.diagnostics)) return result;
    int hp=tokens[*row+5]["value"].get<int>();
    Json columns=Json::array();
    for(size_t j=0;j<24;++j) columns.push_back(tokens[*row+j]["value"]);
    result.trace.push_back({{"stage","exact_level_source_table_hp"},{"source",sourceRef(source.table,2+*row*5,120,*row/24,"monster_base_table_row")},
        {"columns",columns},{"hp_column",5},{"after",hp}});

    const auto range=selected(source.monster,"[level]",result.diagnostics);
    const auto rangeValues=range?source.monster.fields[*range].values:Json::array();
    int low=0,high=0;
    const bool rangeValid=rangeValues.size()==2 && integer(rangeValues[0],low) && integer(rangeValues[1],high) && low>0 && high>=low;
    if (range && !rangeValid) diagnostic(result.diagnostics,"malformed_monster_level_range","error",
        {{"source",fieldRef(source.monster,*range)},{"values",rangeValues}});
    if (range) result.sources["mob_level_range"]={{"source",fieldRef(source.monster,*range)},{"values",rangeValues}};

    if (auto destroy=selected(source.monster,"[destroy count]",result.diagnostics)) {
        const auto &values=source.monster.fields[*destroy].values;
        int count=0;
        if (values.size()!=1 || !integer(values[0],count) || count<0)
            diagnostic(result.diagnostics,"malformed_monster_destroy_count","error",{{"source",fieldRef(source.monster,*destroy)},{"values",values}});
        else if(count>0)
            diagnostic(result.diagnostics,"hit_count_death_requires_separate_consumer","error",{{"source",fieldRef(source.monster,*destroy)},{"destroy_count",count}});
    }
    if (auto endpoints=selected(source.monster,"[hp max]",result.diagnostics)) {
        const auto &values=source.monster.fields[*endpoints].values;
        double first=0,last=0;
        const bool pairValid=values.size()==2 && number(values[0],first) && number(values[1],last) && first>0 && last>0;
        if (!pairValid || !rangeValid) diagnostic(result.diagnostics,"malformed_monster_hp_endpoints_or_range","error",
            {{"source",fieldRef(source.monster,*endpoints)},{"values",values},{"level_values",rangeValues}});
        else {
            const int clamped=std::clamp(level,low,high);
            const double fraction=low==high?0:double(clamped-low)/double(high-low);
            const double interpolated=first+(last-first)*fraction;
            int converted=0;
            if (!hpInteger(interpolated,converted)) diagnostic(result.diagnostics,"invalid_monster_hp_endpoint_result","error",{{"value",interpolated}});
            else {
                result.trace.push_back({{"stage","mob_hp_endpoint_override"},{"source",fieldRef(source.monster,*endpoints)},
                    {"level_source",fieldRef(source.monster,*range)},{"first_level",low},{"last_level",high},{"evaluated_level",clamped},
                    {"before",hp},{"interpolated",interpolated},{"after",converted},{"rounding","positive_truncate_at_integer_consumer"}});
                hp=converted;
            }
            if (clamped!=level) diagnostic(result.diagnostics,"monster_hp_endpoint_level_clamped","warning",{{"requested",level},{"evaluated",clamped}});
            if (low==high && first!=last) diagnostic(result.diagnostics,"single_level_monster_hp_conflicting_endpoints","warning",{{"first",first},{"last",last}});
        }
    }
    if (auto category=selected(source.monster,"[ability category]",result.diagnostics)) {
        const auto values=categoryValues(source.monster,*category,result.diagnostics);
        if (values.size()%3) diagnostic(result.diagnostics,"malformed_monster_ability_category_arity","error",{{"source",fieldRef(source.monster,*category)},{"values",values}});
        bool hasBossHp=false;
        for(size_t i=0;i+2<values.size();i+=3)
            if(values[i].is_string() && normalize(values[i].get<std::string>())=="[hp max boss]") hasBossHp=true;
        for(size_t i=0;i+2<values.size();i+=3) {
            double value=0;
            if (!values[i].is_string() || !values[i+1].is_string() || !number(values[i+2],value) ||
                (values[i+1]!="+" && values[i+1]!="*")) {
                diagnostic(result.diagnostics,"malformed_monster_ability_category_tuple","error",{{"source",fieldRef(source.monster,*category)},{"tuple_ordinal",i/3},{"values",values}});
                continue;
            }
            const auto tag=normalize(values[i].get<std::string>());
            if (tag!="[hp max]" && tag!="[hp max boss]") continue;
            const bool apply=tag=="[hp max boss]"?boss:!(boss && hasBossHp);
            Json entry={{"stage","ordered_monster_hp_category"},{"source",fieldRef(source.monster,*category)},
                {"tuple_ordinal",i/3},{"tag",values[i]},{"operator",values[i+1]},{"value",value},{"applied",apply},{"before",hp}};
            if (apply) {
                const double computed=values[i+1]=="*"?double(hp)*value/100.0:double(hp)+value;
                int converted=0;
                if (!hpInteger(computed,converted)) diagnostic(result.diagnostics,"invalid_monster_hp_category_result","error",{{"tuple_ordinal",i/3},{"value",computed}});
                else hp=converted;
                entry["computed"]=computed;
                entry["rounding"]="positive_truncate_at_integer_consumer";
            }
            entry["after"]=hp;
            result.trace.push_back(std::move(entry));
        }
    }
    result.trace.push_back({{"stage","hp_capability_boundary"},{"difficulty_multiplier",1},{"party_multiplier",1},
        {"named_champion_bonuses","pending separate source consumers"},{"legacy_demo_multipliers_applied",false},
        {"native_pc_final_formula","pending"}});
    if (!hasErrors(result.diagnostics)) result.hp=hp;
    return result;
}
} // namespace dnf
