#include "dnf/attack_status.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/female_gunner_modifiers.hpp"
#include <algorithm>
#include <cmath>
#include <regex>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
bool has(const std::string &s,const std::string &part){return s.find(part)!=std::string::npos;}
void diagnostic(Json &out,const char *kind,Json details=Json::object(),const char *severity="error") {
    details["kind"]=kind;details["severity"]=severity;out.push_back(std::move(details));
}
SourceRef skillRef(const Script &s,size_t ordinal) {
    SourceRef ref;ref.packageIdentity=s.source.value("package_identity",std::string());ref.memberPath=s.path;
    ref.literalPath=s.source.value("literal_path",s.path);ref.memberSha256=sha256(s.rawBytes);ref.ordinal=ordinal;
    ref.byteOffset=s.fields.at(ordinal).offset;const auto end=ordinal+1<s.fields.size()?s.fields[ordinal+1].offset:s.rawBytes.size();
    ref.byteLength=end-ref.byteOffset;ref.scope="skill_status_setter";return ref;
}
void validateCanonical(const SkillSourceData &source) {
    const auto &script=source.definition.source.script;
    if(source.mode!="dungeon" || !source.ambiguousFields.empty() || script.rawBytes.empty() ||
       script.source.value("package_identity",std::string()).empty() ||
       script.source.value("member_sha256",std::string())!=sha256(script.rawBytes))
        throw std::invalid_argument("Skill status setter needs exact dungeon source and member identity");
    const auto canonical=readSkillSourceData(parseCharacterSkillSource(source.definition.key,source.definition.registration,
        source.definition.source),source.mode);
    if(canonical.snapshot(true)!=source.snapshot(true))throw std::invalid_argument("Modified skill status selected-field view");
}
Json selectedParameters(const SkillSourceData &source,int level,const SkillSourceData &schema,
    const std::map<std::string,const SkillSourceData *> &owners) {
    Json out=Json::array();const auto fields=schema.definition.fieldsInScope("[level property]","common");
    if(fields.empty()) return out;
    if(fields.size()!=1) throw std::invalid_argument("Repeated skill status property schema");
    const auto &field=*fields.front();const auto &v=field.field.values;
    if(v.size()<3 || !v[2].is_string() || (v.size()-3)%3) throw std::invalid_argument("Malformed skill status display schema");
    const auto format=v[2].get<std::string>();const std::regex pattern("<(?:int|float[0-9]*)>");size_t operand=0,start=0;
    while(start<=format.size()) {
        const auto end=format.find("\\n",start),size=end==std::string::npos?std::string::npos:end-start;
        const auto line=format.substr(start,size);const auto colon=line.find(':');
        const auto label=line.substr(0,colon==std::string::npos?line.find("："):colon);
        for(auto match=std::sregex_iterator(line.begin(),line.end(),pattern);match!=std::sregex_iterator();++match) {
            const auto offset=3+3*operand++;
            if(offset+2>=v.size() || !v[offset].is_number_integer() || !v[offset+1].is_number_integer() || !v[offset+2].is_number())
                throw std::invalid_argument("Malformed skill status operand selector");
            const int selector=v[offset].get<int>(),column=v[offset+1].get<int>();const double scale=v[offset+2].get<double>();
            const auto tag=selector<0?"[level info]":"[static data]";const auto table=source.values(tag);
            std::optional<double> value;
            if(selector<0) value=skillLevelValue(table,level,column);
            else if(column>=0 && size_t(column)<table.size() && table[size_t(column)].is_number()) value=table[size_t(column)].get<double>();
            if(!value || !std::isfinite(*value) || !std::isfinite(scale) || !std::isfinite(*value*scale))
                throw std::invalid_argument("Selected skill status table operand is unavailable");
            const auto selected=source.selected.find(tag);if(selected==source.selected.end()) throw std::invalid_argument("Missing selected skill status table");
            const auto suffix=line.substr(size_t(match->position()+match->length()));
            out.push_back({{"label",label},{"line",line},{"ordinal",operand-1},{"selector",selector},{"column",column},
                {"scale",scale},{"raw_value",*value},{"value",*value*scale},{"seconds",suffix.rfind("秒",0)==0},
                {"schema_source",skillRef(schema.definition.source.script,field.ordinal).json()},
                {"table_source",skillRef(owners.at(tag)->definition.source.script,selected->second.ordinal).json()}});
        }
        if(end==std::string::npos) break;start=end+2;
    }
    // Some current SKLs retain trailing selector triples that have no visible
    // placeholder. Preserve them in the original schema, without interpreting
    // or consuming them as an additional status operand.
    return out;
}
} // namespace
bool SkillStatusApplication::usable() const {
    if(level<1 || source.mode!="dungeon" || source.definition.source.script.path.empty() || !source.ambiguousFields.empty()) return false;
    for(const auto &d:diagnostics) if(d.value("severity",std::string())=="error") return false;
    for(const auto &entry:entries) if(!entry.usable()) return false;
    return true;
}
Json SkillStatusApplication::snapshot(bool full) const {
    Json values=Json::array();for(const auto &entry:entries) values.push_back(entry.snapshot());
    Json result={{"policy","inferred-1031-skl-status-setters-v1"},{"classification","inferred"},{"usable",usable()},
        {"level",level},{"key",source.definition.key.json()},{"mode",source.mode},{"source",source.snapshot(full)},
        {"entries",values},{"diagnostics",diagnostics}};
    if(!features.empty()) {
        result["feature_sources"]=Json::array();for(const auto &feature:features)
            result["feature_sources"].push_back({{"level",feature.level},{"source",feature.source.snapshot(full)}});
    }
    return result;
}
SkillStatusApplication readSkillAttackStatuses(const SkillSourceData &source,int level) {
    return readSkillAttackStatuses(source,level,{});
}
SkillStatusApplication readSkillAttackStatuses(const SkillSourceData &source,int level,const std::vector<SkillStatusFeature> &features) {
    SkillStatusApplication out;out.source=source;out.features=features;out.level=level;
    try {
        const auto &script=source.definition.source.script;
        if(level<1)throw std::invalid_argument("Skill status level must be positive");validateCanonical(source);
        auto selected=source;const auto *schema=&source;
        std::map<std::string,const SkillSourceData *> owners={{"[level info]",&source},{"[static data]",&source}};
        std::set<SkillKey> seen;
        for(const auto &feature:features) {
            const auto &tp=feature.source;validateCanonical(tp);
            if(feature.level<1 || tp.definition.kind!=SkillSourceKind::Passive ||
               tp.definition.key.jobId!=source.definition.key.jobId ||
               tp.definition.source.script.source.value("package_identity",std::string())!=script.source.value("package_identity",std::string()) ||
               !seen.insert(tp.definition.key).second)throw std::invalid_argument("Skill status feature identity or level is invalid");
            bool target=false;const auto featureFields=source.definition.fieldsInScope("[feature skill index]","common");
            if(featureFields.size()>1)throw std::invalid_argument("Repeated skill status feature registration");
            if(!featureFields.empty())for(const auto &id:featureFields.front()->field.values)
                if(id.is_number_integer()&&id.get<int>()==tp.definition.key.skillId)target=true;
            const auto prerequisiteFields=tp.definition.fieldsInScope("[pre required skill]","common");
            if(prerequisiteFields.size()>1)throw std::invalid_argument("Repeated skill status feature prerequisite");
            const auto prerequisite=prerequisiteFields.empty()?Json::array():prerequisiteFields.front()->field.values;
            for(size_t n=0;n+1<prerequisite.size();n+=2)if(prerequisite[n].is_number_integer()&&
                prerequisite[n].get<int>()==source.definition.key.skillId)target=true;
            auto special=tp.definition.fieldsInScope("[special level up]",tp.mode);
            if(special.empty())special=tp.definition.fieldsInScope("[special level up]","common");
            if(!target||special.size()!=1)throw std::invalid_argument("Skill status feature lacks an original target/special tuple");
            for(const auto *tag:{"[level info]","[static data]"}) {
                const auto replacement=tp.selected.find(tag);if(replacement!=tp.selected.end()) {
                    selected.selected[tag]=replacement->second;owners[tag]=&tp;
                }
            }
            if(!tp.definition.fieldsInScope("[level property]","common").empty())schema=&tp;
            const auto &v=special.front()->field.values;
            if(v.size()%4)throw std::invalid_argument("Malformed skill status feature tuple");
            for(size_t n=0;n<v.size();n+=4) {
                if(!v[n].is_number_integer()||!v[n+1].is_number_integer()||!v[n+2].is_string()||!v[n+3].is_number())
                    throw std::invalid_argument("Invalid skill status feature operand types");
                const int selector=v[n].get<int>(),column=v[n+1].get<int>();
                const std::string tag=selector<0?"[level info]":"[static data]";const auto op=v[n+2].get<std::string>();
                auto table=selected.selected.find(tag);bool available=table!=selected.selected.end()&&column>=0;size_t cell=0;
                if(available&&selector<0) {
                    const auto &values=table->second.field.values;available=bool(skillLevelValue(values,level,column));
                    if(available)cell=1+size_t(level-1)*values[0].get<size_t>()+size_t(column);
                } else if(available){cell=size_t(column);available=cell<table->second.field.values.size();}
                if(!available||!table->second.field.values[cell].is_number()) {
                    diagnostic(out.diagnostics,"tp_status_target_cell_unavailable",{{"tp_key",tp.definition.key.json()},
                        {"selector",selector},{"column",column}},"info");continue;
                }
                const double before=table->second.field.values[cell].get<double>(),delta=v[n+3].get<double>();double after=before;
                if(op=="%")after=before*(1+delta*feature.level/100);
                else if(op=="+")after=before+delta*feature.level;
                else if(op=="-")after=before-delta*feature.level;
                else throw std::invalid_argument("Unsupported skill status feature operator");
                if(!std::isfinite(after)||after<0)throw std::invalid_argument("Skill status feature yields invalid value");
                table->second.field.values[cell]=after;
            }
        }
        // Magazine enlargement and other passive bases can have real feature
        // overlays. Validate and preserve them above, but never turn their
        // display status groups into unrelated global attack procs.
        if(source.definition.kind==SkillSourceKind::Passive)return out;
        const auto params=selectedParameters(selected,level,*schema,owners);
        struct Kind {AttackStatusKind kind;const char *name,*tag;};
        const Kind kinds[]={{AttackStatusKind::Stun,"眩晕","[stun]"},{AttackStatusKind::Freeze,"冰冻","[freeze]"},
            {AttackStatusKind::Lightning,"感电","[lightning]"},{AttackStatusKind::Burn,"灼伤","[burn]"},
            {AttackStatusKind::Bleeding,"出血","[bleeding]"},{AttackStatusKind::Blind,"失明","[blind]"}};
        for(const auto &kind:kinds) {
            const Json *chance=nullptr,*duration=nullptr,*authoredLevel=nullptr,*damage=nullptr,*triggers=nullptr;bool special=false;
            Json operands=Json::array();
            for(const auto &p:params) {
                const auto label=p.at("label").get<std::string>();
                if(!has(label,kind.name)) continue;
                if(has(label,"特殊感电")) special=true;
                const Json **destination=nullptr;
                if(has(label,"几率")) destination=&chance;
                else if(has(label,"持续时间") || has(label,"冰冻时间")) destination=&duration;
                else if(has(label,"Lv")) destination=&authoredLevel;
                else if(has(label,"攻击力")) destination=&damage;
                else if(has(label,"伤害次数上限")) destination=&triggers;
                if(destination) {
                    if(*destination) throw std::invalid_argument("Ambiguous repeated skill status setter group");
                    *destination=&p;operands.push_back(p);
                }
            }
            if(!duration || (!chance && !special && kind.kind!=AttackStatusKind::Freeze)) continue;
            AttackStatusEntry entry;entry.kind=kind.kind;entry.tag=kind.tag;entry.ordinal=out.entries.size();entry.scope="dungeon";
            const double ms=special?duration->at("raw_value").get<double>():
                duration->at("value").get<double>()*(duration->at("seconds").get<bool>()?1000:1);
            const double probability=chance?chance->at("value").get<double>():100;
            const double statusLevel=authoredLevel?authoredLevel->at("value").get<double>():0;
            if(!std::isfinite(ms) || ms<0 || ms>INT32_MAX || statusLevel<0 || statusLevel>INT32_MAX || std::floor(statusLevel)!=statusLevel)
                throw std::invalid_argument("Skill status duration or authored level is outside supported range");
            entry.chancePercent=std::clamp(probability,0.0,100.0);entry.level=int(statusLevel);entry.durationMs=uint32_t(std::llround(ms));
            entry.damage=damage?damage->at("raw_value").get<double>():0;entry.rawPayload=operands;
            if(kind.kind==AttackStatusKind::Blind) {
                entry.blindEvasionPercent=20;entry.blindVisionPercent=50;
                diagnostic(entry.diagnostics,"inferred_missing_skl_blind_operands",{{"miss_increase_percent",20},{"vision_percent",50},
                    {"basis","SKL authors blind chance/level/duration, but omits vision and stuck operands; explicit comparable beta defaults"}},"info");
            }
            if(special) {
                if(!triggers || triggers->at("value").get<double>()<1 || triggers->at("value").get<double>()>UINT32_MAX)
                    throw std::invalid_argument("Special lightning requires its source-authored positive trigger count");
                entry.maximumTriggers=uint32_t(triggers->at("value").get<double>());
                diagnostic(entry.diagnostics,"inferred_counted_special_lightning",{{"maximum_triggers",entry.maximumTriggers},
                    {"duration","raw static milliseconds; source display scales 0.001 without a written suffix"},
                    {"trigger","each subsequent accepted hit, at most the source-authored count"}},"info");
            }
            for(const auto &p:operands) {
                const auto ref=p.at("table_source");SourceRef r;
                r.packageIdentity=ref.at("package_identity");r.memberPath=ref.at("member_path");r.literalPath=ref.at("literal_path");
                r.memberSha256=ref.at("member_sha256");r.byteOffset=ref.at("byte_offset");r.byteLength=ref.at("byte_length");
                r.ordinal=ref.at("ordinal");r.scope="skill_status_setter";entry.sources.push_back(r);
            }
            for(const auto &feature:features) {
                auto special=feature.source.definition.fieldsInScope("[special level up]",feature.source.mode);
                if(special.empty())special=feature.source.definition.fieldsInScope("[special level up]","common");
                entry.sources.push_back(skillRef(feature.source.definition.source.script,special.front()->ordinal));
            }
            diagnostic(entry.diagnostics,"inferred_skill_status_setter",{{"basis","Current SKL ordered display schema and exact selected source row"},
                {"parameters",operands},{"probability_source_value",probability},{"clamped_probability",entry.chancePercent},
                {"missing_probability",chance?"authored":"inferred guaranteed freeze when source specifies freeze duration/level"},
                {"level_source",authoredLevel?"authored":"no source level; explicit neutral authored level0"},
                {"damage_scaling","raw status damage operand; independent-attack scaling uses named beta policy"},
                {"native_dispatch","unverified"}},"info");
            if(entry.chancePercent==0 || entry.durationMs==0) {
                if(entry.chancePercent==0) entry.kind=AttackStatusKind::None;
                else diagnostic(entry.diagnostics,"positive_skill_status_requires_duration");
            }
            out.entries.push_back(std::move(entry));
        }
    } catch(const std::exception &e) {diagnostic(out.diagnostics,"skill_status_source_preparation_failed",{{"reason",e.what()}});}
    return out;
}
SkillStatusApplication readFemaleGunnerSkillAttackStatuses(const FemaleGunnerSkillCommand &command,const ExperimentalCharacterPlan &plan) {
    const auto row=plan.skills.find(command.key);
    if(row==plan.skills.end()||!row->second.data) {
        SkillStatusApplication invalid;diagnostic(invalid.diagnostics,"skill_status_command_source_missing");return invalid;
    }
    const auto &base=*row->second.data;auto out=readSkillAttackStatuses(base,command.level);
    try {
        if(command.skillSource.json()!=row->second.source.json())throw std::invalid_argument("Skill status command source identity differs");
        if(command.key.skillId!=100&&command.family.rfind("twingunblade_",0)==0) {
            const std::string expected=command.key==SkillKey{5,3}?"twingunblade_somersault":command.key==SkillKey{5,6}?"twingunblade_chain_cut":
                command.key==SkillKey{5,7}?"twingunblade_spinning_blade":"";
            const auto &mode=plan.skills.at({5,100});
            if(expected.empty()||command.family!=expected||command.rawTables.at("source")!=mode.source.json())
                throw std::invalid_argument("Alternate mode status authority is foreign or inconsistent");
            // Source100 changes these actions; ordinary source7 stun and
            // source6 grab/status are not inherited by the alternate action.
            // The selected alternate ATK remains an independent status source.
            auto authority=command;authority.key={5,100};authority.skillSource=mode.source;
            return readFemaleGunnerSkillAttackStatuses(authority,plan);
        }
        if(!command.rawTables.contains("feature_template_selection")) {
            if(command.rawTables.contains("tp_applied_cells")||command.rawTables.contains("source_level_info")||command.rawTables.contains("source_static_data"))
                throw std::invalid_argument("Skill status command feature overlay lacks original feature sources");
            return out;
        }
        std::vector<SkillStatusFeature> features;std::map<SkillKey,int> levels;
        const auto &templates=command.rawTables.at("feature_template_selection");
        if(!templates.is_array()||templates.empty())throw std::invalid_argument("Skill status feature template list is invalid");
        for(const auto &selection:templates) {
            const SkillSourceData *tp=nullptr;SkillKey key;
            for(const auto &[candidate,skill]:plan.skills)if(skill.source.json()==selection.at("tp_source")){tp=skill.data.get();key=candidate;break;}
            if(!tp||!selection.at("tp_level").is_number_integer()||levels.count(key))throw std::invalid_argument("Skill status feature source is foreign or repeated");
            const int level=selection.at("tp_level");levels[key]=level;features.push_back({*tp,level});
        }
        auto rebuilt=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at(command.key),base,command.level,0);
        applyFemaleGunnerTpOperands(rebuilt,levels,plan,0);
        if(rebuilt.parameters!=command.parameters)throw std::invalid_argument("Skill status command parameters differ from immutable source recomputation");
        for(const auto *key:{"level_info","static_data","property_schema","tp_applied_cells","source_level_info","source_static_data","feature_template_selection"})
            if(rebuilt.rawTables.at(key)!=command.rawTables.at(key))
                throw std::invalid_argument("Skill status command feature overlay differs from immutable source recomputation");
        return readSkillAttackStatuses(base,command.level,features);
    }catch(const std::exception &error){diagnostic(out.diagnostics,"skill_status_feature_command_invalid",{{"reason",error.what()}});}
    return out;
}
} // namespace dnf
