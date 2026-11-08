#include "dnf/attack_status.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *statusPolicy = "inferred-flat-chance-stun-v1";
bool errors(const Json &values) {
    for(const auto &value:values) if(value.value("severity",std::string())=="error") return true;
    return false;
}
void issue(Json &out,const char *kind,Json details=Json::object(),const char *severity="error") {
    details["kind"]=kind;details["severity"]=severity;out.push_back(std::move(details));
}
bool i32(const Json &value,int &out,bool signedValue=false) {
    if(!value.is_number_integer() || (value.is_number_unsigned() && value.get<uint64_t>()>uint64_t(INT32_MAX))) return false;
    const auto n=value.get<int64_t>();if(n<(signedValue?INT32_MIN:0) || n>INT32_MAX) return false;
    out=int(n);return true;
}
uint64_t u64(const Json &value) {
    if(!value.is_number_unsigned() && (!value.is_number_integer() || value.get<int64_t>()<0))
        throw std::invalid_argument("Status checkpoint integer is negative or noninteger");
    return value.get<uint64_t>();
}
uint64_t plus(uint64_t a,uint64_t b) {
    if(b>UINT64_MAX-a) throw std::overflow_error("Status simulation time overflow");
    return a+b;
}
void advanceRevision(uint64_t &revision) { revision=plus(revision,1); }
float add32(float a,float b) {volatile float out=a+b;return out;}
std::string metadata(const Script &source,const char *key) {
    const auto found=source.source.is_object()?source.source.find(key):source.source.end();
    return found!=source.source.end() && found->is_string()?found->get<std::string>():std::string();
}
SourceRef reference(const Script &source,size_t offset=0,size_t length=0,size_t ordinal=0) {
    SourceRef out;out.packageIdentity=metadata(source,"package_identity");out.memberPath=source.path;
    out.literalPath=metadata(source,"literal_path");if(out.literalPath.empty()) out.literalPath=source.path;
    out.memberSha256=sha256(source.rawBytes);
    out.byteOffset=offset;out.byteLength=length?length:source.rawBytes.size()-std::min(offset,source.rawBytes.size());
    out.ordinal=ordinal;out.scope="attack_status";return out;
}
SourceRef fieldReference(const Script &source,size_t ordinal) {
    const auto offset=source.fields.at(ordinal).offset;
    const auto end=ordinal+1<source.fields.size()?source.fields[ordinal+1].offset:source.rawBytes.size();
    return reference(source,offset,end>=offset?end-offset:0,ordinal);
}
Json document(const Script &source) {
    Json fields=Json::array();
    for(const auto &field:source.fields) fields.push_back({{"tag",field.tag},{"offset",field.offset},{"values",field.values}});
    return {{"path",source.path},{"source",source.source},{"raw_bytes",source.rawBytes},{"tokens",source.tokens},{"fields",fields}};
}
void validateSource(const Script &source,Json &diagnostics) {
    if(source.path.empty() || source.rawBytes.size()<2 || (source.rawBytes.size()-2)%5 || !source.source.is_object()) {
        issue(diagnostics,"invalid_status_source_document",{{"path",source.path}});return;
    }
    const auto package=source.source.find("package_identity");
    if(package==source.source.end() || !package->is_string() || package->get<std::string>().empty())
        issue(diagnostics,"missing_status_source_identity",{{"path",source.path}});
    const auto hash=source.source.find("member_sha256");
    if(hash==source.source.end() || !hash->is_string() || hash->get<std::string>()!=sha256(source.rawBytes))
        issue(diagnostics,"status_source_hash_mismatch",{{"path",source.path}});
    size_t previous=0;
    for(const auto &field:source.fields) {
        if(!field.values.is_array() || field.offset<2 || (field.offset-2)%5 || field.offset<=previous ||
           field.offset>source.rawBytes.size() || source.rawBytes.size()-field.offset<5)
            issue(diagnostics,"invalid_status_source_field_span",{{"path",source.path},{"offset",field.offset}});
        previous=field.offset;
    }
}
std::string digest(const Json &value) {const auto bytes=value.dump();return sha256(Bytes(bytes.begin(),bytes.end()));}
Json contactIdentity(const StatusRequest &request) {
    Json out={{"attacker",request.attacker.json()},{"target",request.target.handle.json()},
        {"attack_instance",request.attackInstance},{"hit_index",request.hitIndex},
        {"source_path",request.attack.source.path},{"source_sha256",sha256(request.attack.source.rawBytes)}};
    if(request.skill) out["skill_status"]=digest(request.skill->snapshot());return out;
}
Json scalarCandidates(const Script &source,const std::vector<Field> &fields,const std::string &tag) {
    Json result=Json::array();
    for(const auto &field:fields) if(normalize(field.tag)==tag) {
        size_t ordinal=0;while(ordinal<source.fields.size() && source.fields[ordinal].offset!=field.offset) ++ordinal;
        result.push_back({{"values",field.values},{"source",ordinal<source.fields.size()?fieldReference(source,ordinal).json():Json()}});
    }
    return result;
}
struct Scalar {bool present=false;float value=0;};
Scalar scalar(StatusResistanceSnapshot &out,const Script &source,const std::vector<Field> &fields,
              const std::string &tag,const std::string &stage) {
    Scalar value;const auto found=scalarCandidates(source,fields,tag);value.present=!found.empty();
    bool valid=found.empty();
    if(found.size()==1) {
        const auto &v=found[0].at("values");
        if(v.is_array() && v.size()==1 && v[0].is_number()) {
            const double n=v[0].get<double>();
            valid=std::isfinite(n) && std::abs(n)<=double(INT32_MAX);
            if(valid) value.value=float(n);
        }
    }
    if(!valid) issue(out.diagnostics,"invalid_status_resistance_scalar",{{"tag",tag},{"candidates",found},{"stage",stage}});
    out.trace.push_back({{"stage",stage},{"tag",tag},{"present",value.present},{"value",value.value},{"candidates",found},
        {"absent_default","explicit inferred zero"}});
    return value;
}
const CharacterStatBlock *blockAt(const CharacterDefinition &character,const Json &selection) {
    if(!selection.is_object() || !selection.contains("offset") || !selection.contains("tag")) return nullptr;
    const CharacterStatBlock *out=nullptr;
    for(const auto &block:character.stats) if(block.offset==selection.at("offset") && block.tag==selection.at("tag")) {
        if(out) return nullptr;out=&block;
    }
    return out;
}
void unsupportedResistanceFields(StatusResistanceSnapshot &out,const Script &source,const std::vector<Field> &fields) {
    bool scoped=false;
    for(const auto &field:fields) {
        const auto tag=normalize(field.tag);
        if(tag=="[pvp]" || tag=="[if]" || tag=="[then]" || tag=="[equipment option]" || tag=="[ability]" || tag=="[special effect]") scoped=true;
        bool resistanceTag=tag=="[all activestatus resistance]";
        for(const auto name:statusResistanceOrder()) if(tag=="["+std::string(name)+" resistance]") resistanceTag=true;
        if(scoped && resistanceTag) issue(out.diagnostics,"scoped_status_resistance_consumer_required",
            {{"tag",field.tag},{"values",field.values},{"path",source.path},{"offset",field.offset}});
        if(tag=="[active status control info]" || tag=="[all active status resistance]" ||
           tag=="[active status resistance]" || tag.find("[change status")==0)
            issue(out.diagnostics,"status_resistance_modifier_consumer_required",{{"tag",field.tag},{"values",field.values},{"path",source.path},{"offset",field.offset}});
    }
}
} // namespace

const char *attackStatusKindName(AttackStatusKind kind) {
    switch(kind) {
    case AttackStatusKind::None:return "none";case AttackStatusKind::Stun:return "stun";
    case AttackStatusKind::Freeze:return "freeze";case AttackStatusKind::Lightning:return "lightning";
    case AttackStatusKind::Burn:return "burn";case AttackStatusKind::Bleeding:return "bleeding";
    case AttackStatusKind::Blind:return "blind";
    default:return "required_unsupported";}
}
bool AttackStatusEntry::usable() const {
    return !runtime || (!errors(diagnostics) && (kind==AttackStatusKind::None ||
        (kind!=AttackStatusKind::RequiredUnsupported && std::isfinite(chancePercent) && chancePercent>=0 && chancePercent<=100 &&
         level>=0 && durationMs>0 && std::isfinite(damage) && damage>=0)));
}
Json AttackStatusEntry::snapshot() const {
    Json refs=Json::array();for(const auto &ref:sources) refs.push_back(ref.json());
    Json out={{"kind",attackStatusKindName(kind)},
        {"tag",tag},{"scope",scope},{"runtime",runtime},{"chance_percent",chancePercent},{"level",level},
        {"duration_ms",durationMs},{"ordinal",ordinal},{"raw_payload",rawPayload},{"sources",refs},{"diagnostics",diagnostics}};
    if(kind==AttackStatusKind::Burn || kind==AttackStatusKind::Bleeding || kind==AttackStatusKind::Lightning) out["damage"]=damage;
    if(maximumTriggers) out["maximum_triggers"]=maximumTriggers;
    if(kind==AttackStatusKind::Blind) {out["blind_evasion_percent"]=blindEvasionPercent;out["blind_vision_percent"]=blindVisionPercent;}
    return out;
}
bool AttackStatusSource::usable() const {
    if(errors(diagnostics) || source.path.empty()) return false;
    for(const auto &entry:entries) if(!entry.usable()) return false;
    return true;
}
Json AttackStatusSource::snapshot(bool full) const {
    Json ordered=Json::array();for(const auto &entry:entries) ordered.push_back(entry.snapshot());
    Json out={{"usable",usable()},{"source",reference(source).json()},{"entries",ordered},{"diagnostics",diagnostics}};
    if(full) out["document"]=document(source);return out;
}
AttackStatusSource readAttackStatuses(const Script &source) {
    AttackStatusSource out;out.source=source;validateSource(source,out.diagnostics);
    const auto path=normalize(source.path);
    if(path.size()<4 || path.substr(path.size()-4)!=".atk") issue(out.diagnostics,"unexpected_attack_status_path",{{"path",source.path}});
    std::string scope="dungeon";bool pvp=false;
    for(size_t i=0;i<source.fields.size();++i) {
        const auto &field=source.fields[i];const auto tag=normalize(field.tag);
        if(tag=="[pvp]") {if(pvp) issue(out.diagnostics,"nested_status_pvp_scope");pvp=true;scope="pvp";continue;}
        if(tag=="[/pvp]") {if(!pvp) issue(out.diagnostics,"unmatched_status_pvp_scope");pvp=false;scope="dungeon";continue;}
        if(tag!="[active status]") continue;
        AttackStatusEntry entry;entry.ordinal=out.entries.size();entry.scope=scope;entry.runtime=!pvp;
        entry.sources.push_back(fieldReference(source,i));
        if(!field.values.is_array()) {
            issue(entry.diagnostics,"malformed_attack_status_payload_shape");out.entries.push_back(std::move(entry));continue;
        }
        if(!field.values.empty() && field.values[0].is_string()) {
            entry.tag=normalize(field.values[0].get<std::string>());
            for(size_t j=1;j<field.values.size();++j) entry.rawPayload.push_back(field.values[j]);
        } else if(field.values.empty() && i+1<source.fields.size()) {
            const auto &type=source.fields[i+1];entry.tag=normalize(type.tag);entry.rawPayload=type.values;
            entry.sources.push_back(fieldReference(source,++i));
        } else issue(entry.diagnostics,"malformed_attack_status_type");
        // These exact source triples occur in 1031 gunner ATKs whose skills
        // expose status parameters separately. A zero-probability
        // source entry cannot apply a status and needs no positive duration.
        // Keep the original tag, payload and references; this is deliberately
        // not a general consumer for burn or arbitrary zero-chance payloads.
        const bool dormantType=entry.tag=="[stun]" || entry.tag=="[burn]";
        int dormantChance=0,dormantLevel=0,dormantDuration=0;
        const bool dormant=dormantType && entry.rawPayload.is_array() && entry.rawPayload.size()==3 &&
            i32(entry.rawPayload[0],dormantChance) && dormantChance==0 &&
            i32(entry.rawPayload[1],dormantLevel) && dormantLevel==0 &&
            i32(entry.rawPayload[2],dormantDuration) && dormantDuration==0;
        if(dormant) {
            entry.kind=AttackStatusKind::None;
            issue(entry.diagnostics,"zero_probability_dormant_source_status",
                {{"tag",entry.tag},{"complete_payload",entry.rawPayload},{"reason","exact authored integer 0 0 0 cannot apply an active status"},
                 {"consumer","no active status; any skill-supplied status requires a separate provenance-bearing consumer"}},"info");
        } else if(entry.tag=="[none]") entry.kind=AttackStatusKind::None;
        else if(entry.tag=="[stun]") {
            entry.kind=AttackStatusKind::Stun;int duration=0;
            if(!entry.rawPayload.is_array() || entry.rawPayload.size()!=3 || !entry.rawPayload[0].is_number() ||
               !i32(entry.rawPayload[1],entry.level) || !i32(entry.rawPayload[2],duration) || duration<=0)
                issue(entry.diagnostics,"malformed_stun_payload",{{"payload",entry.rawPayload},{"expected","probability percent, nonnegative authored level, positive duration milliseconds"}});
            else {
                entry.chancePercent=entry.rawPayload[0].get<double>();entry.durationMs=uint32_t(duration);
                if(!std::isfinite(entry.chancePercent) || entry.chancePercent<0 || entry.chancePercent>100)
                    issue(entry.diagnostics,"invalid_stun_probability",{{"payload",entry.rawPayload}});
            }
        } else if(entry.tag=="[freeze]" || entry.tag=="[lightning]" || entry.tag=="[burn]" || entry.tag=="[bleeding]" || entry.tag=="[blind]") {
            entry.kind=entry.tag=="[freeze]"?AttackStatusKind::Freeze:entry.tag=="[lightning]"?AttackStatusKind::Lightning:
                entry.tag=="[burn]"?AttackStatusKind::Burn:entry.tag=="[blind]"?AttackStatusKind::Blind:AttackStatusKind::Bleeding;
            const size_t width=entry.kind==AttackStatusKind::Freeze?3:entry.kind==AttackStatusKind::Blind?5:4;int duration=0;
            if(!entry.rawPayload.is_array() || entry.rawPayload.size()!=width || !entry.rawPayload[0].is_number() ||
               !i32(entry.rawPayload[1],entry.level) || !i32(entry.rawPayload[2],duration) || duration<=0 ||
               (width>=4 && !entry.rawPayload[3].is_number()) || (width==5 && !entry.rawPayload[4].is_number()))
                issue(entry.diagnostics,"malformed_extended_status_payload",{{"complete_payload",entry.rawPayload},
                    {"expected",width==3?"probability, level, positive duration ms":"probability, level, positive duration ms, damage"},
                    {"burn_aura","nonzero nearby/aura operands require a separate geometry consumer"}});
            else {
                entry.chancePercent=entry.rawPayload[0].get<double>();entry.durationMs=uint32_t(duration);
                if(width==4) entry.damage=entry.rawPayload[3].get<double>();
                if(width==5) {entry.blindVisionPercent=entry.rawPayload[3].get<double>();entry.blindEvasionPercent=entry.rawPayload[4].get<double>();}
                if(!std::isfinite(entry.chancePercent) || entry.chancePercent<0 || entry.chancePercent>100 ||
                   !std::isfinite(entry.damage) || entry.damage<0 || !std::isfinite(entry.blindVisionPercent) ||
                   !std::isfinite(entry.blindEvasionPercent) || entry.blindVisionPercent<0 || entry.blindEvasionPercent<0)
                    issue(entry.diagnostics,"invalid_extended_status_operand",{{"complete_payload",entry.rawPayload}});
            }
        } else issue(entry.diagnostics,"attack_status_consumer_required",{{"tag",entry.tag},{"complete_payload",entry.rawPayload}});
        if(!entry.runtime) for(auto &diagnostic:entry.diagnostics) diagnostic["severity"]="info";
        out.entries.push_back(std::move(entry));
    }
    if(pvp) issue(out.diagnostics,"unterminated_status_pvp_scope");
    return out;
}

const std::array<const char *,17> &statusResistanceOrder() {
    static const std::array<const char *,17> names={"slow","freeze","poison","stun","curse","blind","lightning","stone","sleep",
        "burn","weapon break","bleeding","piercing","stuck","confuse","hold","armor break"};return names;
}
bool StatusResistanceSnapshot::usable() const {
    if(packageIdentity.empty() || level<1 || errors(diagnostics) || !std::isfinite(allActiveStatusResistance)) return false;
    for(const auto value:values) if(!std::isfinite(value)) return false;
    return std::isfinite(add32(values[3],allActiveStatusResistance));
}
float StatusResistanceSnapshot::stunResistance() const {return add32(values[3],allActiveStatusResistance);}
Json StatusResistanceSnapshot::snapshot() const {
    Json names=Json::array();for(const auto name:statusResistanceOrder()) names.push_back(name);
    return {{"usable",usable()},{"package_identity",packageIdentity},{"level",level},{"order",names},{"values",values},
        {"all_active_status_resistance",allActiveStatusResistance},{"stun_resistance",stunResistance()},
        {"unit","raw source resistance points; percentage interpretation requires explicit inference"},
        {"sources",sources},{"trace",trace},{"diagnostics",diagnostics}};
}
StatusResistanceSnapshot evaluateCharacterStatusResistances(const CharacterBaseAttributes &base,
    const CharacterDefinition &character,const std::vector<EquippedAttributeSource> &equipment,int qualificationLevel, const EquipmentSkillContext *normalSkills) {
    StatusResistanceSnapshot out;out.level=base.level;
    out.packageIdentity=metadata(character.source.script,"package_identity");
    out.sources["character"]=document(character.source.script);out.sources["base_selection"]=base.snapshot();
    const auto qualified=evaluateCharacterSpeeds(base,character,equipment,qualificationLevel,CharacterSpeedPolicy::inferredFlatEquipmentV1(),normalSkills);
    out.sources["equipment_qualification"]=qualified.snapshot(true);
    if(!qualified.usable() || !base.usable() || base.policy!="inferred-chr-growth-v1" || base.selectedBlocks.size()<2 || base.selectedBlocks.size()>3) {
        issue(out.diagnostics,"unusable_status_resistance_qualification",{{"diagnostics",qualified.diagnostics}});return out;
    }
    validateSource(character.source.script,out.diagnostics);
    if(!base.source.is_object() || !base.source.contains("member_sha256") ||
       base.source.at("member_sha256")!=sha256(character.source.script.rawBytes)) issue(out.diagnostics,"status_resistance_character_hash_mismatch");
    const auto initial=blockAt(character,base.selectedBlocks[0]),growth=blockAt(character,base.selectedBlocks[1]);
    const auto awakened=base.selectedBlocks.size()==3?blockAt(character,base.selectedBlocks[2]):nullptr;
    if(!initial || !growth || (base.selectedBlocks.size()==3 && !awakened)) {
        issue(out.diagnostics,"status_resistance_selection_mismatch");return out;
    }
    for(const auto *block:{initial,growth,awakened}) if(block) unsupportedResistanceFields(out,character.source.script,block->fields);
    for(size_t n=0;n<18;++n) {
        const auto tag=n==17?"[all activestatus resistance]":"["+std::string(statusResistanceOrder()[n])+" resistance]";
        auto baseValue=scalar(out,character.source.script,initial->fields,tag,"chr_status_initial");
        auto delta=scalar(out,character.source.script,growth->fields,tag,"chr_status_growth_delta");
        if(awakened) {
            const auto replacement=scalar(out,character.source.script,awakened->fields,tag,"chr_status_awakening_delta");
            if(replacement.present) delta=replacement;
        }
        for(int level=2;level<=base.level;++level) baseValue.value=add32(baseValue.value,delta.value);
        if(n==17) out.allActiveStatusResistance=baseValue.value;else out.values[n]=baseValue.value;
    }
    auto sorted=equipment;std::stable_sort(sorted.begin(),sorted.end(),[](const auto &a,const auto &b){return a.instanceUid<b.instanceUid;});
    for(const auto &item:sorted) {
        unsupportedResistanceFields(out,item.source,item.source.fields);
        int maximumDurability=0;const auto durability=scalar(out,item.source,item.source.fields,"[durability]","status_equipment_durability");
        if(durability.present) maximumDurability=int(durability.value);
        const bool active=maximumDurability==0 || item.currentDurability>0;
        for(size_t n=0;n<18;++n) {
            const auto tag=n==17?"[all activestatus resistance]":"["+std::string(statusResistanceOrder()[n])+" resistance]";
            const auto value=scalar(out,item.source,item.source.fields,tag,"equipment_status_resistance");
            float &target=n==17?out.allActiveStatusResistance:out.values[n];const auto before=target;
            if(active) target=add32(target,value.value);
            out.trace.push_back({{"stage","equipment_status_resistance_add"},{"uid",item.instanceUid},{"tag",tag},{"active",active},
                {"before",before},{"operand",value.value},{"after",target},{"classification","inferred flat UID-ordered source-point addition"}});
        }
    }
    if(!out.usable() && !errors(out.diagnostics)) issue(out.diagnostics,"status_resistance_arithmetic_overflow");
    return out;
}
StatusResistanceSnapshot makeMonsterStatusResistances(const MonsterCombatAttributes &frozen) {
    StatusResistanceSnapshot out;out.level=frozen.level;out.packageIdentity=frozen.source.monster.source.value("package_identity",std::string());
    out.sources["frozen_monster_combat"]=frozen.snapshot();out.diagnostics=frozen.diagnostics;
    if(!frozen.usable()) {issue(out.diagnostics,"unusable_frozen_monster_status_resistance");return out;}
    for(size_t i=0;i<17;++i) out.values[i]=float(frozen.attributes->statusResistance[i]);
    out.trace.push_back({{"stage","frozen_monster_status_resistance"},{"stun_index",3},{"source_tag","[stun resistance]"},
        {"mapping","MOB own endpoint plus table column23; stuck index13 uses column12/10; no 17 separate table columns"},
        {"native_enum_order","unproven; named adapter order only"}});return out;
}

StunStatusPolicy StunStatusPolicy::inferredFlatChanceStunV1(bool infer) {return {statusPolicy,infer};}
Json StunStatusPolicy::snapshot() const {
    return {{"id",id},{"classification","inferred_beta"},{"infer_resistance_as_percent",inferResistanceAsPercent},
        {"probability","clamp(source_percent * max(0, 1 - resistance_points / 100), 0, 100)"},
        {"nonzero_resistance_default","requires explicit comparable inference opt-in; otherwise rejects"},
        {"level","authored level retained, including zero; native level suppression and zero-level dispatch unverified, no invented ratio"},
        {"duration","source fixed milliseconds, no invented resistance/level duration scaling"},
        {"refresh","one stun per target; new successful application gets a unique instance, expiry=max(old,new)"},
        {"probability_resolution",1000000},{"arithmetic","binary64 probability; binary32 source resistance aggregation"},
        {"source",{{"path","attackinfosample.atk"},{"encoding","CP949"},
            {"sha256","ffd0d2541f7598962a59ed5c5415bdd00e28945838bbae3373bd65ff4aefd675"},{"lines",Json::array({45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62})}}},
        {"native_pc_probability_and_resistance_formula","unrecovered"},{"world_movement_cast_ai_gates","caller must integrate; this module is not beta completion"}};
}
Json StunStatusInstance::snapshot(uint64_t nowMs) const {
    Json out=preserved;out["id"]=id;out["attacker"]=attacker.json();out["target"]=target.json();
    out["attack_instance"]=attackInstance;out["hit_index"]=hitIndex;out["authored_level"]=authoredLevel;
    out["attacker_level"]=attackerLevel;out["target_level"]=targetLevel;
    out["applied_ago_ms"]=nowMs>=appliedMs?nowMs-appliedMs:0;out["remaining_ms"]=expiresMs>nowMs?expiresMs-nowMs:0;
    out["maximum_duration_ms"]=maximumDurationMs;out["source_path"]=sourcePath;out["status_ordinal"]=statusOrdinal;
    out["source_entry"]=sourceEntry;out["resistance"]=resistance;out["trace"]=trace;return out;
}
StatusHost::StatusHost(std::string identity,StunStatusPolicy policy):packageIdentity_(std::move(identity)),policy_(std::move(policy)) {}

PreparedStatusApplication StatusHost::prepare(const StatusRequest &request,uint64_t nowMs,const Pcg32 &random) const {
    PreparedStatusApplication out;Json diagnostics=Json::array(),trace=Json::array(),outcomes=Json::array();
    const auto reject=[&]() {
        out.receipt={{"usable",false},{"policy",policy_.snapshot()},{"trace",trace},{"diagnostics",diagnostics},{"outcomes",outcomes}};
    };
    try {
        if(policy_.id!=statusPolicy || packageIdentity_.empty()) issue(diagnostics,"status_policy_disabled_or_unbound");
        if(nowMs<lastNowMs_ || revision_==UINT64_MAX) issue(diagnostics,"invalid_status_simulation_time_or_revision");
        if(!request.attacker || !request.target.handle || !request.attackInstance || request.attackerLevel<1 || !request.target.resistance.usable())
            issue(diagnostics,"invalid_status_request_participants");
        const auto parsed=readAttackStatuses(request.attack.source);
        if(!request.attack.usable() || !parsed.usable() || parsed.snapshot()!=request.attack.snapshot())
            issue(diagnostics,"unusable_or_modified_status_source",{{"source",parsed.snapshot()}});
        if(request.attack.source.source.value("package_identity",std::string())!=packageIdentity_ || request.target.resistance.packageIdentity!=packageIdentity_)
            issue(diagnostics,"status_source_package_mismatch");
        if(request.skill) {
            const auto selected=readSkillAttackStatuses(request.skill->source,request.skill->level,request.skill->features);
            if(!request.skill->usable() || !selected.usable() || selected.snapshot(true)!=request.skill->snapshot(true) ||
               request.skill->source.definition.source.script.source.value("package_identity",std::string())!=packageIdentity_)
                issue(diagnostics,"unusable_or_modified_skill_status_source");
        }
        for(const auto value:{request.independentAttack,request.independentRate,request.strength,request.intelligence})
            if(!std::isfinite(value) || value<0) issue(diagnostics,"invalid_status_attacker_scaling");
        const double resistance=request.target.resistance.stunResistance();
        const bool needsStun=std::any_of(parsed.entries.begin(),parsed.entries.end(),[](const auto &entry){return entry.runtime && entry.kind==AttackStatusKind::Stun;});
        if(needsStun && resistance!=0 && !policy_.inferResistanceAsPercent) issue(diagnostics,"nonzero_stun_resistance_strategy_required",{{"raw_source_points",resistance}});
        if(request.target.immuneToStun && request.target.immunitySource.empty()) issue(diagnostics,"stun_immunity_source_required");
        if(errors(diagnostics)) {reject();return out;}
        const auto identity=contactIdentity(request);const auto key=digest(identity);
        const auto candidate=std::make_shared<StatusHost>(*this);candidate->expire(nowMs);
        auto candidateRandom=random;
        const auto previous=candidate->contacts_.find(key);
        if(previous!=candidate->contacts_.end()) {
            out.receipt={{"usable",true},{"deduplicated",true},{"contact",identity},{"previous",previous->second},
                {"policy",policy_.snapshot()},{"trace",trace},{"diagnostics",diagnostics},{"outcomes",outcomes}};
        } else {
            const auto currentSource=candidate->sources_.find(parsed.source.path);
            if(currentSource!=candidate->sources_.end() && currentSource->second.snapshot()!=parsed.snapshot()) {
                issue(diagnostics,"status_source_changed_within_bound_host",{{"path",parsed.source.path}});reject();return out;
            }
            for(const auto &entry:parsed.entries) {
                if(!entry.runtime || entry.kind!=AttackStatusKind::Stun) continue;
                const double factor=std::max(0.0,1.0-resistance/100.0);
                const double chance=std::clamp(entry.chancePercent*factor,0.0,100.0);
                if(!std::isfinite(factor) || !std::isfinite(chance)) throw std::overflow_error("Status probability overflow");
                std::optional<uint32_t> roll;bool proc=false;
                if(!request.target.immuneToStun && chance>=100) proc=true;
                else if(!request.target.immuneToStun && chance>0) {
                    roll=candidateRandom.bounded(1000000);proc=double(*roll)<std::floor(chance*10000.0);
                }
                Json outcome={{"status",entry.snapshot()},{"resistance",request.target.resistance.snapshot()},
                    {"source_chance_percent",entry.chancePercent},{"resistance_factor",factor},{"effective_chance_percent",chance},
                    {"roll_0_999999",roll?Json(*roll):Json()},{"procced",proc},{"immune",request.target.immuneToStun},
                    {"authored_level",entry.level},{"attacker_level",request.attackerLevel},{"target_level",request.target.resistance.level},
                    {"level_probability_consumer","unverified; no level scaling applied"},{"duration_ms",entry.durationMs}};
                if(proc) {
                    StunStatusInstance instance;instance.id=candidate->instances_.next();instance.attackInstance=request.attackInstance;
                    instance.hitIndex=request.hitIndex;instance.attacker=request.attacker;instance.target=request.target.handle;
                    instance.authoredLevel=entry.level;instance.attackerLevel=request.attackerLevel;instance.targetLevel=request.target.resistance.level;
                    instance.appliedMs=nowMs;instance.expiresMs=plus(nowMs,entry.durationMs);instance.maximumDurationMs=entry.durationMs;
                    instance.sourcePath=parsed.source.path;instance.statusOrdinal=entry.ordinal;instance.sourceEntry=entry.snapshot();
                    instance.resistance=request.target.resistance.snapshot();
                    const auto active=candidate->active_.find(request.target.handle);
                    if(active!=candidate->active_.end()) {
                        outcome["replaced_instance"]=active->second.id;
                        instance.expiresMs=std::max(instance.expiresMs,active->second.expiresMs);
                        instance.maximumDurationMs=std::max(instance.maximumDurationMs,active->second.maximumDurationMs);
                    }
                    outcome["instance_id"]=instance.id;outcome["expires_ms"]=instance.expiresMs;
                    instance.trace.push_back(outcome);candidate->active_[request.target.handle]=std::move(instance);
                }
                outcomes.push_back(std::move(outcome));
            }
            Json extended=Json::array();const int bonus=candidate->applyEffectStatuses(request,nowMs,candidateRandom,extended);
            candidate->sources_[parsed.source.path]=parsed;
            candidate->contacts_[key]={{"identity",identity},{"outcomes",outcomes}};
            if(!extended.empty()) candidate->contacts_[key]["extended_outcomes"]=extended;
            if(request.skill) candidate->contacts_[key]["skill_source"]=request.skill->snapshot(true);
            out.receipt={{"usable",true},{"deduplicated",false},{"contact",identity},{"policy",policy_.snapshot()},
                {"trace",trace},{"diagnostics",diagnostics},{"outcomes",outcomes}};
            if(!extended.empty()) {out.receipt["extended_outcomes"]=extended;out.receipt["bonus_hp_damage"]=bonus;}
        }
        candidate->lastNowMs_=nowMs;advanceRevision(candidate->revision_);
        out.receipt["draws_before"]=random.draws();out.receipt["draws_after"]=candidateRandom.draws();
        out.candidate_=candidate;out.origin_=this;out.expectedRevision_=revision_;
        out.expectedRandom_=random.snapshot();out.candidateRandom_=candidateRandom;
    } catch(const std::exception &error) {
        issue(diagnostics,"status_preparation_failed",{{"reason",error.what()}});reject();
    }
    return out;
}
bool StatusHost::canPublish(const PreparedStatusApplication &prepared,const Pcg32 &random) const {
    return prepared.ready() && prepared.origin_==this && revision_==prepared.expectedRevision_ && random.snapshot()==prepared.expectedRandom_;
}
void StatusHost::publish(PreparedStatusApplication &&prepared,Pcg32 &random) {
    if(!canPublish(prepared,random)) throw std::invalid_argument("Status candidate is stale, reused or belongs to a different host/RNG state");
    *this=std::move(*prepared.candidate_);random=prepared.candidateRandom_;prepared.candidate_.reset();
}
bool StatusHost::stunned(EntityHandle target,uint64_t nowMs) const {return instance(target,nowMs)!=nullptr;}
const StunStatusInstance *StatusHost::instance(EntityHandle target,uint64_t nowMs) const {
    const auto found=active_.find(target);
    return found!=active_.end() && nowMs>=found->second.appliedMs && nowMs<found->second.expiresMs?&found->second:nullptr;
}
void StatusHost::mergeInstanceWatermark(const Json &saved) {
    MonotonicIds restored;restored.restore(saved);
    const auto current=instances_.nextValue(),incoming=restored.nextValue();
    const auto next=(!current || !incoming)?uint64_t(0):std::max(current,incoming);
    if(next==current) return;
    if(revision_==UINT64_MAX) throw std::overflow_error("Status revision exhausted");
    instances_=MonotonicIds(next);++revision_;
}
void StatusHost::expire(uint64_t nowMs) {
    if(nowMs<lastNowMs_) throw std::invalid_argument("Status clock cannot move backwards");
    const bool expired=std::any_of(active_.begin(),active_.end(),[&](const auto &v){return v.second.expiresMs<=nowMs;}) ||
        std::any_of(effects_.begin(),effects_.end(),[&](const auto &v){return v.second.expiresMs<=nowMs;});
    if(nowMs==lastNowMs_ && !expired) return;
    const auto nextRevision=plus(revision_,1);
    // The common fixed-step path touches scalars only. Copying the source
    // documents and accepted-contact ledger at 60 Hz has no gameplay purpose.
    if(!expired) {revision_=nextRevision;lastNowMs_=nowMs;return;}
    StatusHost next=*this;next.revision_=nextRevision;next.lastNowMs_=nowMs;
    for(auto it=next.active_.begin();it!=next.active_.end();) if(it->second.expiresMs<=nowMs) {
        next.lifecycle_.push_back({{"kind","expired"},{"instance",it->second.id},{"target",it->first.json()},{"at_ms",nowMs}});
        it=next.active_.erase(it);
    } else ++it;
    for(auto it=next.effects_.begin();it!=next.effects_.end();) if(it->second.expiresMs<=nowMs) {
        next.lifecycle_.push_back({{"kind","extended_expired"},{"instance",it->second.id},{"target",it->first.first.json()},{"at_ms",nowMs}});
        it=next.effects_.erase(it);
    } else ++it;
    *this=std::move(next);
}
void StatusHost::clearTarget(EntityHandle target,uint64_t nowMs,const std::string &reason) {
    if(!target || reason.empty() || nowMs<lastNowMs_) throw std::invalid_argument("Status target cleanup requires identity, reason and monotonic time");
    const bool extended=std::any_of(effects_.begin(),effects_.end(),[&](const auto &v){return v.first.first==target;});
    if(!active_.count(target) && !extended) {expire(nowMs);return;}
    StatusHost next=*this;next.expire(nowMs);advanceRevision(next.revision_);
    next.active_.erase(target);
    for(auto i=next.effects_.begin();i!=next.effects_.end();) if(i->first.first==target) i=next.effects_.erase(i);else ++i;
    // Cleansing a live target must not permit the same accepted hit to reroll.
    // Contact records remain until the scene's attack/effect cleanup clears all.
    next.lifecycle_.push_back({{"kind","clear_target"},{"target",target.json()},{"reason",reason},{"at_ms",nowMs}});
    *this=std::move(next);
}
void StatusHost::clearAll(uint64_t nowMs,const std::string &reason) {
    if(reason.empty() || nowMs<lastNowMs_) throw std::invalid_argument("Status scene cleanup requires reason and monotonic time");
    StatusHost next=*this;advanceRevision(next.revision_);next.lastNowMs_=nowMs;
    next.active_.clear();next.effects_.clear();next.contacts_.clear();next.sources_.clear();
    next.lifecycle_.push_back({{"kind","clear_all"},{"reason",reason},{"at_ms",nowMs}});*this=std::move(next);
}
void StatusHost::retireTarget(EntityHandle target,uint64_t nowMs,const std::string &reason) {
    if(!target || reason.empty() || nowMs<lastNowMs_) throw std::invalid_argument("Status retirement requires identity, reason and monotonic time");
    const bool contacts=std::any_of(contacts_.begin(),contacts_.end(),[&](const auto &value){
        return value.second.at("identity").at("target")==target.json();});
    const bool extended=std::any_of(effects_.begin(),effects_.end(),[&](const auto &v){return v.first.first==target;});
    if(!active_.count(target) && !contacts && !extended) {expire(nowMs);return;}
    StatusHost next=*this;next.expire(nowMs);advanceRevision(next.revision_);next.active_.erase(target);
    for(auto i=next.effects_.begin();i!=next.effects_.end();) if(i->first.first==target) i=next.effects_.erase(i);else ++i;
    for(auto it=next.contacts_.begin();it!=next.contacts_.end();)
        if(it->second.at("identity").at("target")==target.json()) it=next.contacts_.erase(it);else ++it;
    std::set<std::string> needed;
    for(const auto &[handle,instance]:next.active_) needed.insert(instance.sourcePath);
    for(const auto &[key,instance]:next.effects_) needed.insert(instance.definition.at("attack_path").get<std::string>());
    for(const auto &[key,contact]:next.contacts_) needed.insert(contact.at("identity").at("source_path").get<std::string>());
    for(auto it=next.sources_.begin();it!=next.sources_.end();) if(!needed.count(it->first)) it=next.sources_.erase(it);else ++it;
    next.lifecycle_.push_back({{"kind","retire_target"},{"target",target.json()},{"reason",reason},{"at_ms",nowMs}});
    *this=std::move(next);
}
Json StatusHost::snapshot(uint64_t nowMs,uint64_t generation,bool full) const {
    if(nowMs<lastNowMs_ || !generation) throw std::invalid_argument("Status snapshot requires monotonic time and a concrete commit generation");
    for(const auto &[key,effect]:effects_) if((effect.kind==AttackStatusKind::Burn || effect.kind==AttackStatusKind::Bleeding) &&
        effect.nextDamageMs<=nowMs && effect.nextDamageMs<=effect.expiresMs)
        throw std::invalid_argument("Status snapshot requires publishing pending periodic HP damage in the same commit generation first");
    Json active=Json::array(),contacts=Json::array(),sources=Json::object();
    for(const auto &[target,instance]:active_) if(instance.expiresMs>nowMs) active.push_back(instance.snapshot(nowMs));
    for(const auto &[key,value]:contacts_) contacts.push_back(value);
    for(const auto &[path,source]:sources_) sources[path]=source.snapshot(full);
    Json out=preserved_;out["schema"]=1;out["package_identity"]=packageIdentity_;out["policy"]=policy_.snapshot();
    out["commit_generation"]=generation;out["saved_at_ms"]=nowMs;out["revision"]=revision_;out["instance_ids"]=instances_.snapshot();
    out["active"]=active;out["contacts"]=contacts;out["sources"]=sources;out["lifecycle"]=lifecycle_;
    out["effects"]=Json::array();for(const auto &[key,effect]:effects_) if(effect.expiresMs>nowMs) out["effects"].push_back(effect.snapshot(nowMs));
    return out;
}
Json StatusHost::snapshotTarget(EntityHandle target,uint64_t nowMs,uint64_t generation,bool full) const {
    if(!target) throw std::invalid_argument("Status target snapshot requires an explicit entity handle");
    auto out=snapshot(nowMs,generation,full);Json active=Json::array(),contacts=Json::array(),sources=Json::object(),lifecycle=Json::array(),effects=Json::array();
    std::set<std::string> needed;
    for(const auto &instance:out.at("active")) if(instance.at("target")==target.json()) {
        needed.insert(instance.at("source_path").get<std::string>());active.push_back(instance);
    }
    for(const auto &contact:out.at("contacts")) if(contact.at("identity").at("target")==target.json()) {
        needed.insert(contact.at("identity").at("source_path").get<std::string>());contacts.push_back(contact);
    }
    for(const auto &effect:out.at("effects")) if(effect.at("target")==target.json()) {
        needed.insert(effect.at("definition").at("attack_path").get<std::string>());effects.push_back(effect);
    }
    for(const auto &path:needed) sources[path]=out.at("sources").at(path);
    for(const auto &entry:out.at("lifecycle")) if(entry.is_object() && entry.contains("target") && entry.at("target")==target.json())
        lifecycle.push_back(entry);
    out["active"]=std::move(active);out["contacts"]=std::move(contacts);out["sources"]=std::move(sources);out["lifecycle"]=std::move(lifecycle);
    out["effects"]=std::move(effects);
    out["target_bundle"]={{"schema",1},{"target",target.json()},{"scope","single-target"}};return out;
}
void StatusHost::restore(const Json &saved,uint64_t nowMs,uint64_t generation,
    const std::function<Script(const std::string &)> &source,const std::function<bool(EntityHandle)> &targetIsLive) {
    if(!saved.is_object() || saved.at("schema")!=1 || saved.at("package_identity")!=packageIdentity_ ||
       saved.at("policy")!=policy_.snapshot() || !generation || u64(saved.at("commit_generation"))!=generation ||
       !source || !targetIsLive || !saved.at("active").is_array() || !saved.at("contacts").is_array() ||
       !saved.at("sources").is_object() || !saved.at("lifecycle").is_array())
        throw std::invalid_argument("Status checkpoint source, policy, generation or shape mismatch");
    StatusHost next(packageIdentity_,policy_);next.instances_.restore(saved.at("instance_ids"));
    next.revision_=u64(saved.at("revision"));next.lastNowMs_=nowMs;next.lifecycle_=saved.at("lifecycle");next.preserved_=saved;
    for(auto it=saved.at("sources").begin();it!=saved.at("sources").end();++it) {
        auto parsed=readAttackStatuses(source(it.key()));const auto expected=parsed.snapshot();
        if(!parsed.usable() || parsed.source.path!=it.key() || parsed.source.source.value("package_identity",std::string())!=packageIdentity_)
            throw std::invalid_argument("Status checkpoint source cannot be resolved under the selected content identity");
        for(auto key=expected.begin();key!=expected.end();++key) if(!it.value().contains(key.key()) || it.value().at(key.key())!=key.value())
            throw std::invalid_argument("Status checkpoint source hash, ordered payload or diagnostic mismatch");
        if(it.value().contains("document") && it.value().at("document")!=document(parsed.source))
            throw std::invalid_argument("Status checkpoint embedded source bytes mismatch");
        next.sources_[it.key()]=std::move(parsed);
    }
    std::set<uint64_t> ids;
    for(const auto &value:saved.at("active")) {
        StunStatusInstance instance;instance.preserved=value;instance.id=u64(value.at("id"));
        instance.attacker=EntityHandle::fromJson(value.at("attacker"));instance.target=EntityHandle::fromJson(value.at("target"));
        instance.attackInstance=u64(value.at("attack_instance"));const auto hit=u64(value.at("hit_index"));
        if(hit>UINT32_MAX) throw std::invalid_argument("Status checkpoint hit index overflow");instance.hitIndex=uint32_t(hit);
        int maximum=0;
        if(!i32(value.at("authored_level"),instance.authoredLevel) || !i32(value.at("attacker_level"),instance.attackerLevel) ||
           !i32(value.at("target_level"),instance.targetLevel) || instance.attackerLevel<1 || instance.targetLevel<1 ||
           !i32(value.at("maximum_duration_ms"),maximum) || maximum<=0)
            throw std::invalid_argument("Status checkpoint level or duration is malformed");
        instance.maximumDurationMs=uint32_t(maximum);const auto remaining=u64(value.at("remaining_ms")),age=u64(value.at("applied_ago_ms"));
        if(!remaining || remaining>instance.maximumDurationMs || age>nowMs) throw std::invalid_argument("Status checkpoint relative time is invalid");
        instance.appliedMs=nowMs-age;instance.expiresMs=plus(nowMs,remaining);
        instance.sourcePath=value.at("source_path").get<std::string>();instance.statusOrdinal=u64(value.at("status_ordinal"));
        const auto definition=next.sources_.find(instance.sourcePath);
        if(!instance.id || !ids.insert(instance.id).second || (next.instances_.nextValue() && instance.id>=next.instances_.nextValue()) ||
           !instance.attacker || !instance.target || !instance.attackInstance || !targetIsLive(instance.target) || next.active_.count(instance.target) ||
           definition==next.sources_.end() || instance.statusOrdinal>=definition->second.entries.size())
            throw std::invalid_argument("Status checkpoint instance identity, watermark, live target or source is invalid");
        const auto &entry=definition->second.entries[instance.statusOrdinal];
        if(!entry.runtime || entry.kind!=AttackStatusKind::Stun || entry.snapshot()!=value.at("source_entry") ||
           entry.level!=instance.authoredLevel || entry.durationMs>instance.maximumDurationMs || !value.at("trace").is_array())
            throw std::invalid_argument("Status checkpoint stun definition or trace mismatch");
        instance.sourceEntry=entry.snapshot();instance.resistance=value.at("resistance");instance.trace=value.at("trace");
        if(instance.resistance.at("package_identity")!=packageIdentity_ || instance.resistance.at("level")!=instance.targetLevel ||
           instance.resistance.at("usable")!=true) throw std::invalid_argument("Status checkpoint frozen resistance identity mismatch");
        next.active_[instance.target]=std::move(instance);
    }
    for(const auto &contact:saved.at("contacts")) {
        const auto &identity=contact.at("identity");const auto owner=EntityHandle::fromJson(identity.at("attacker"));
        const auto target=EntityHandle::fromJson(identity.at("target"));const auto attack=u64(identity.at("attack_instance"));
        const auto hit=u64(identity.at("hit_index"));const auto path=identity.at("source_path").get<std::string>();
        const auto definition=next.sources_.find(path);
        if(!owner || !target || !attack || hit>UINT32_MAX || !contact.at("outcomes").is_array() || definition==next.sources_.end() ||
           identity.at("source_sha256")!=sha256(definition->second.source.rawBytes) || !next.contacts_.emplace(digest(identity),contact).second)
            throw std::invalid_argument("Status checkpoint contact ledger is malformed or duplicates an accepted contact");
    }
    std::set<uint64_t> appliedIds;std::set<uint64_t> matchedActive;
    for(const auto &[key,contact]:next.contacts_) {
        const auto &identity=contact.at("identity");const auto &definition=next.sources_.at(identity.at("source_path").get<std::string>());
        for(const auto &outcome:contact.at("outcomes")) {
            if(!outcome.is_object() || !outcome.at("procced").is_boolean()) throw std::invalid_argument("Malformed frozen status outcome");
            const auto ordinal=u64(outcome.at("status").at("ordinal"));
            if(ordinal>=definition.entries.size() || outcome.at("status")!=definition.entries[ordinal].snapshot())
                throw std::invalid_argument("Frozen status outcome source mismatch");
            if(!outcome.at("procced").get<bool>()) continue;
            const auto id=u64(outcome.at("instance_id"));
            if(!id || !appliedIds.insert(id).second || (next.instances_.nextValue() && id>=next.instances_.nextValue()))
                throw std::invalid_argument("Frozen status outcome instance watermark mismatch");
            const auto target=EntityHandle::fromJson(identity.at("target"));const auto active=next.active_.find(target);
            if(active!=next.active_.end() && active->second.id==id) {
                const auto &instance=active->second;
                if(instance.attacker.json()!=identity.at("attacker") || instance.attackInstance!=identity.at("attack_instance") ||
                   instance.hitIndex!=identity.at("hit_index") || instance.sourcePath!=definition.source.path || instance.statusOrdinal!=ordinal)
                    throw std::invalid_argument("Active status and accepted contact do not belong to the same application");
                matchedActive.insert(id);
            }
        }
    }
    if(matchedActive.size()!=next.active_.size()) throw std::invalid_argument("Active status has no accepted contact in the same checkpoint generation");
    next.restoreEffects(saved.value("effects",Json::array()),nowMs,source,targetIsLive);
    // A restore is a publication boundary. Candidates prepared against the
    // previous incarnation must never become publishable through revision ABA.
    next.revision_=plus(std::max(revision_,next.revision_),1);*this=std::move(next);
}
void StatusHost::mergeTarget(const Json &saved,EntityHandle oldTarget,EntityHandle newTarget,
    uint64_t nowMs,uint64_t generation,const std::function<Script(const std::string &)> &source,
    const std::function<bool(EntityHandle)> &targetIsLive) {
    if(!oldTarget || !newTarget || !targetIsLive || !targetIsLive(newTarget) || nowMs<lastNowMs_ ||
       !saved.is_object() || !saved.contains("target_bundle") || !saved.at("target_bundle").is_object() ||
       saved.at("target_bundle").at("schema")!=1 || saved.at("target_bundle").at("scope")!="single-target" ||
       saved.at("target_bundle").at("target")!=oldTarget.json())
        throw std::invalid_argument("Status target merge requires explicit matching old/live-new identities and a target bundle");
    for(const auto &instance:saved.at("active")) if(instance.at("target")!=oldTarget.json())
        throw std::invalid_argument("Status target bundle contains another active target");
    for(const auto &contact:saved.at("contacts")) if(contact.at("identity").at("target")!=oldTarget.json())
        throw std::invalid_argument("Status target bundle contains another contact target");
    for(const auto &effect:saved.value("effects",Json::array())) if(effect.at("target")!=oldTarget.json())
        throw std::invalid_argument("Status target bundle contains another extended effect target");
    if(oldTarget!=newTarget) {
        if(targetIsLive(oldTarget)) throw std::invalid_argument("Status target merge cannot duplicate a still-live old target");
    }
    // Fully validate the historical bundle against its explicit old identity
    // before remapping. It need not still be live in the new entity registry.
    StatusHost incoming(packageIdentity_,policy_);incoming.restore(saved,nowMs,generation,source,
        [&](EntityHandle target){return target==oldTarget;});
    auto imported=incoming.snapshot(nowMs,generation);auto combined=snapshot(nowMs,generation);
    Json active=Json::array(),contacts=Json::array(),effects=Json::array();
    for(const auto &instance:combined.at("active"))
        if(instance.at("target")!=newTarget.json() && instance.at("target")!=oldTarget.json()) active.push_back(instance);
    for(const auto &contact:combined.at("contacts"))
        if(contact.at("identity").at("target")!=newTarget.json() && contact.at("identity").at("target")!=oldTarget.json()) contacts.push_back(contact);
    for(auto instance:imported.at("active")) {instance["target"]=newTarget.json();active.push_back(std::move(instance));}
    for(auto contact:imported.at("contacts")) {contact["identity"]["target"]=newTarget.json();contacts.push_back(std::move(contact));}
    for(const auto &effect:combined.at("effects"))
        if(effect.at("target")!=newTarget.json() && effect.at("target")!=oldTarget.json()) effects.push_back(effect);
    for(auto effect:imported.at("effects")) {effect["target"]=newTarget.json();effects.push_back(std::move(effect));}
    for(auto it=imported.at("sources").begin();it!=imported.at("sources").end();++it) {
        const auto found=combined.at("sources").find(it.key());
        if(found!=combined.at("sources").end() && found.value()!=it.value())
            throw std::invalid_argument("Status target merge source conflicts with another bound target");
        combined["sources"][it.key()]=it.value();
    }
    const auto existingNext=instances_.nextValue(),incomingNext=incoming.instances_.nextValue();
    combined["instance_ids"]["next"]=existingNext && incomingNext?std::max(existingNext,incomingNext):0;
    combined["revision"]=std::max(revision_,incoming.revision_);combined["active"]=std::move(active);combined["contacts"]=std::move(contacts);
    combined["effects"]=std::move(effects);
    Json evidence={{"kind","merge_target"},{"old_target",oldTarget.json()},{"target",newTarget.json()},
        {"at_ms",nowMs},{"source_commit_generation",generation},{"source_saved_at_ms",saved.at("saved_at_ms")},
        {"attacker_handles","preserved historical identities"},{"identity_mapping","explicit one old target to one live new target"}};
    Json unknown=saved;
    for(const char *key:{"schema","package_identity","policy","commit_generation","saved_at_ms","revision","instance_ids",
                         "active","effects","contacts","sources","lifecycle","target_bundle"}) unknown.erase(key);
    evidence["preserved_bundle_metadata"]=std::move(unknown);evidence["source_target_lifecycle"]=saved.at("lifecycle");
    combined["lifecycle"].push_back(std::move(evidence));combined.erase("target_bundle");
    // This final restore rejects cross-target instance-ID collisions and
    // reconstructs contact digests only after the entire merge is assembled.
    StatusHost next=*this;next.restore(combined,nowMs,generation,source,targetIsLive);*this=std::move(next);
}
} // namespace dnf
