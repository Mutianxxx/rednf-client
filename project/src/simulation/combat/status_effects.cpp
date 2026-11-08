#include "dnf/attack_status.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
uint64_t addTime(uint64_t a,uint64_t b) {if(b>UINT64_MAX-a) throw std::overflow_error("Extended status time exhausted");return a+b;}
uint64_t integer(const Json &v) {
    if(!v.is_number_integer() || (!v.is_number_unsigned() && v.get<int64_t>()<0)) throw std::invalid_argument("Invalid extended status integer");
    return v.get<uint64_t>();
}
AttackStatusKind kindFrom(const std::string &name) {
    for(const auto kind:{AttackStatusKind::Stun,AttackStatusKind::Freeze,AttackStatusKind::Lightning,AttackStatusKind::Burn,AttackStatusKind::Bleeding,AttackStatusKind::Blind})
        if(name==attackStatusKindName(kind)) return kind;
    throw std::invalid_argument("Unknown extended status kind");
}
int resistanceIndex(AttackStatusKind kind) {
    switch(kind) {case AttackStatusKind::Stun:return 3;case AttackStatusKind::Freeze:return 1;
    case AttackStatusKind::Lightning:return 6;case AttackStatusKind::Burn:return 9;case AttackStatusKind::Bleeding:return 11;
    case AttackStatusKind::Blind:return 5;
    default:throw std::invalid_argument("Missing extended status resistance consumer");}
}
SkillSourceData selectedSkillFromSaved(const Json &saved,const std::function<Script(const std::string &)> &resolver) {
    const auto &definition=saved.at("source");const auto &doc=definition.at("source");
    const auto script=resolver(doc.at("path").get<std::string>());
    CharacterScript source;source.script=script;source.bytes=script.rawBytes;source.provenance=doc.at("provenance");
    const auto &r=definition.at("registration");CharacterRegistration registration;
    registration.id=r.at("id");registration.ordinal=r.at("ordinal");registration.offset=r.at("offset");registration.pathOffset=r.at("path_offset");
    registration.literal=r.at("literal");registration.path=r.at("path");registration.exists=r.at("exists");
    auto selected=readSkillSourceData(parseCharacterSkillSource(SkillKey::fromJson(definition.at("key")),registration,std::move(source)),saved.at("mode"));
    if(selected.snapshot(true)!=saved)throw std::invalid_argument("Extended status selected skill source snapshot mismatch");
    return selected;
}
SkillStatusApplication skillFromSaved(const Json &saved,const std::function<Script(const std::string &)> &resolver) {
    const auto selected=selectedSkillFromSaved(saved.at("source"),resolver);
    std::vector<SkillStatusFeature> features;
    if(saved.contains("feature_sources")) {
        if(!saved.at("feature_sources").is_array()||saved.at("feature_sources").empty())throw std::invalid_argument("Invalid frozen status feature list");
        for(const auto &feature:saved.at("feature_sources"))features.push_back({selectedSkillFromSaved(feature.at("source"),resolver),feature.at("level").get<int>()});
    }
    auto result=readSkillAttackStatuses(selected,saved.at("level"),features);
    if(!result.usable() || result.snapshot(true)!=saved) throw std::invalid_argument("Extended status skill source, ordered table or setter snapshot mismatch");
    return result;
}
int damagePoints(const AttackStatusEntry &entry,const StatusRequest &request,bool skill) {
    if(entry.kind==AttackStatusKind::Freeze || entry.kind==AttackStatusKind::Stun || entry.kind==AttackStatusKind::Blind) return 0;
    double value=entry.damage;
    // This explicit beta setter policy follows the SKL's raw independent
    // operand. Native status defense/level/resistance formulas remain unknown.
    if(skill) value=value*request.independentAttack/100.0*request.independentRate*
        (1.0+((entry.kind==AttackStatusKind::Bleeding)?request.strength:request.intelligence)/250.0);
    if(!std::isfinite(value) || value<0 || value>INT32_MAX) throw std::overflow_error("Extended status damage is outside int32");
    return entry.damage==0?0:std::max(1,int(value));
}
} // namespace
Json StatusEffectInstance::snapshot(uint64_t nowMs) const {
    auto out=preserved.is_object()?preserved:Json::object();
    out.update({{"id",id},{"kind",attackStatusKindName(kind)},{"attacker",attacker.json()},{"target",target.json()},
        {"attack_instance",attackInstance},{"hit_index",hitIndex},{"applied_ago_ms",nowMs-appliedMs},
        {"remaining_ms",expiresMs>nowMs?expiresMs-nowMs:0},{"next_damage_in_ms",nextDamageMs>nowMs?nextDamageMs-nowMs:0},
        {"next_damage_overdue_ms",nextDamageMs<nowMs?nowMs-nextDamageMs:0},
        {"interval_ms",intervalMs},{"hp_damage",hpDamage},{"remaining_triggers",remainingTriggers},{"definition",definition},{"trace",trace}});
    return out;
}
int StatusHost::applyEffectStatuses(const StatusRequest &request,uint64_t nowMs,Pcg32 &random,Json &outcomes) {
    int64_t bonus=0;
    const auto lightning=effects_.find({request.target.handle,AttackStatusKind::Lightning});
    if(lightning!=effects_.end() && lightning->second.expiresMs>nowMs) {
        auto &effect=lightning->second;bonus=effect.hpDamage;
        outcomes.push_back({{"kind","lightning_accepted_hit_damage"},{"instance_id",effect.id},{"hp_damage",effect.hpDamage},
            {"definition",effect.definition},{"classification","inferred subsequent accepted-hit trigger; no recursive status proc"}});
        if(effect.remainingTriggers && --effect.remainingTriggers==0) effects_.erase(lightning);
    }
    struct Entry {const AttackStatusEntry *entry;bool skill;};std::vector<Entry> entries;
    for(const auto &entry:request.attack.entries) if(entry.kind!=AttackStatusKind::Stun) entries.push_back({&entry,false});
    if(request.skill) for(const auto &entry:request.skill->entries) entries.push_back({&entry,true});
    for(const auto &binding:entries) {
        const auto &entry=*binding.entry;if(!entry.runtime || entry.kind==AttackStatusKind::None) continue;
        const double resistance=request.target.resistance.values[size_t(resistanceIndex(entry.kind))]+request.target.resistance.allActiveStatusResistance;
        if(resistance!=0 && !policy_.inferResistanceAsPercent) throw std::invalid_argument("Nonzero extended status resistance needs selected percentage inference");
        const double chance=std::clamp(entry.chancePercent*std::max(0.0,1.0-resistance/100.0),0.0,100.0);
        const bool immune=entry.kind==AttackStatusKind::Stun && request.target.immuneToStun;
        std::optional<uint32_t> roll;bool procced=!immune && chance>=100;
        if(!immune && chance>0 && chance<100) {roll=random.bounded(1000000);procced=double(*roll)<std::floor(chance*10000.0);}
        Json outcome={{"kind","extended_status_application"},{"status",entry.snapshot()},{"from_skill",binding.skill},
            {"resistance",request.target.resistance.snapshot()},{"effective_chance_percent",chance},
            {"roll_0_999999",roll?Json(*roll):Json()},{"procced",procced}};
        if(procced) {
            StatusEffectInstance effect;effect.id=instances_.next();effect.kind=entry.kind;
            effect.attacker=request.attacker;effect.target=request.target.handle;effect.attackInstance=request.attackInstance;effect.hitIndex=request.hitIndex;
            effect.appliedMs=nowMs;effect.expiresMs=addTime(nowMs,entry.durationMs);effect.nextDamageMs=addTime(nowMs,effect.intervalMs);
            effect.hpDamage=damagePoints(entry,request,binding.skill);effect.remainingTriggers=entry.maximumTriggers;
            effect.definition={{"entry",entry.snapshot()},{"attack_path",request.attack.source.path},
                {"attack_sha256",sha256(request.attack.source.rawBytes)},{"from_skill",binding.skill}};
            if(binding.skill) effect.definition["skill"]=request.skill->snapshot(true);
            effect.trace.push_back({{"policy","inferred-1031-active-status-v1"},{"classification","inferred"},
                {"periodic_interval_ms",1000},{"periodic_basis","explicit beta interval; native cadence not present in ATK/SKL sample"},
                {"stacking","replace same target/kind, retain source and monotonic ID; independent kinds coexist"},
                {"damage_points",effect.hpDamage},{"raw_damage",entry.damage},{"skill_independent_scaling",binding.skill},
                {"independent_attack",request.independentAttack},{"independent_rate",request.independentRate},
                {"strength",request.strength},{"intelligence",request.intelligence},{"native_parity","pending"}});
            outcome["instance_id"]=effect.id;outcome["definition"]=effect.definition;
            effects_[{effect.target,effect.kind}]=std::move(effect);
        }
        outcomes.push_back(std::move(outcome));
    }
    if(bonus>INT32_MAX) throw std::overflow_error("Extended status contact damage overflow");return int(bonus);
}
bool StatusHost::frozen(EntityHandle target,uint64_t nowMs) const {
    const auto i=effects_.find({target,AttackStatusKind::Freeze});return i!=effects_.end() && i->second.appliedMs<=nowMs && nowMs<i->second.expiresMs;
}
uint64_t StatusHost::controlRemaining(EntityHandle target,uint64_t nowMs) const {
    uint64_t remaining=0;if(const auto *stun=instance(target,nowMs)) remaining=stun->expiresMs-nowMs;
    for(const auto kind:{AttackStatusKind::Stun,AttackStatusKind::Freeze}) {
        const auto i=effects_.find({target,kind});if(i!=effects_.end() && i->second.appliedMs<=nowMs && i->second.expiresMs>nowMs)
            remaining=std::max(remaining,i->second.expiresMs-nowMs);
    }
    return remaining;
}
bool StatusHost::controlled(EntityHandle target,uint64_t nowMs) const {return controlRemaining(target,nowMs)>0;}
bool StatusHost::hasEffects(EntityHandle target,uint64_t nowMs) const {
    for(const auto &[key,effect]:effects_) if(effect.target==target && effect.appliedMs<=nowMs && effect.expiresMs>nowMs) return true;
    return false;
}
Json StatusHost::activeEffects(EntityHandle target,uint64_t nowMs) const {
    Json out=Json::array();if(const auto *stun=instance(target,nowMs)) {
        auto entry=stun->snapshot(nowMs);entry["kind"]="stun";out.push_back(std::move(entry));
    }
    for(const auto &[key,effect]:effects_) if(effect.target==target && effect.appliedMs<=nowMs && nowMs<effect.expiresMs)
        out.push_back(effect.snapshot(nowMs));
    return out;
}
double StatusHost::blindMissPercent(EntityHandle target,uint64_t nowMs) const {
    const auto i=effects_.find({target,AttackStatusKind::Blind});
    if(i==effects_.end() || nowMs<i->second.appliedMs || nowMs>=i->second.expiresMs) return 0;
    return i->second.definition.at("entry").at("blind_evasion_percent").get<double>();
}
bool StatusHost::needsEffectAdvance(uint64_t nowMs) const {
    for(const auto &[key,effect]:effects_)
        if(effect.expiresMs<=nowMs || ((effect.kind==AttackStatusKind::Burn || effect.kind==AttackStatusKind::Bleeding) && effect.nextDamageMs<=nowMs)) return true;
    return false;
}
PreparedStatusAdvance StatusHost::prepareAdvance(uint64_t nowMs) const {
    PreparedStatusAdvance result;
    try {
        if(nowMs<lastNowMs_ || revision_==UINT64_MAX) throw std::invalid_argument("Extended status advance needs monotonic time and revision");
        auto candidate=std::make_shared<StatusHost>(*this);Json damages=Json::array();
        for(auto it=candidate->effects_.begin();it!=candidate->effects_.end();) {
            auto &effect=it->second;
            if(effect.kind==AttackStatusKind::Burn || effect.kind==AttackStatusKind::Bleeding) {
                while(effect.nextDamageMs<=nowMs && effect.nextDamageMs<=effect.expiresMs) {
                    if(damages.size()>=100000) throw std::overflow_error("Extended status pending damage limit exceeded");
                    damages.push_back({{"instance",effect.id},{"kind",attackStatusKindName(effect.kind)},{"attacker",effect.attacker.json()},
                        {"target",effect.target.json()},{"amount",effect.hpDamage},{"at_ms",effect.nextDamageMs},{"definition",effect.definition}});
                    effect.nextDamageMs=addTime(effect.nextDamageMs,effect.intervalMs);
                }
            }
            if(effect.expiresMs<=nowMs) it=candidate->effects_.erase(it);else ++it;
        }
        candidate->expire(nowMs);
        if(candidate->revision_==revision_) candidate->revision_=addTime(candidate->revision_,1);
        result.receipt={{"usable",true},{"damages",damages},{"at_ms",nowMs}};
        result.origin_=this;result.expectedRevision_=revision_;result.candidate_=std::move(candidate);
    } catch(const std::exception &e) {result.receipt={{"usable",false},{"reason",e.what()}};}
    return result;
}
bool StatusHost::canPublish(const PreparedStatusAdvance &candidate) const {
    return candidate.ready() && candidate.origin_==this && candidate.expectedRevision_==revision_;
}
void StatusHost::publish(PreparedStatusAdvance &&candidate) {
    if(!canPublish(candidate)) throw std::invalid_argument("Extended status advance is stale or belongs to another host");
    *this=std::move(*candidate.candidate_);candidate.candidate_.reset();
}
void StatusHost::restoreEffects(const Json &saved,uint64_t nowMs,const std::function<Script(const std::string &)> &resolver,
    const std::function<bool(EntityHandle)> &isLive) {
    if(!saved.is_array()) throw std::invalid_argument("Extended status checkpoint effects must be an array");
    std::set<uint64_t> applicationIds;
    for(const auto &[key,record]:contacts_) {
        std::optional<SkillStatusApplication> skill;
        if(record.contains("skill_source")) {
            skill=skillFromSaved(record.at("skill_source"),resolver);const auto value=skill->snapshot().dump();
            if(!record.at("identity").contains("skill_status") ||
               record.at("identity").at("skill_status")!=sha256(Bytes(value.begin(),value.end())))
                throw std::invalid_argument("Extended status contact skill identity mismatch");
        } else if(record.at("identity").contains("skill_status")) throw std::invalid_argument("Missing frozen skill status contact source");
        for(const auto &outcome:record.at("outcomes")) if(outcome.value("procced",false))
            applicationIds.insert(integer(outcome.at("instance_id")));
        for(const auto &outcome:record.value("extended_outcomes",Json::array())) {
            if(outcome.value("kind",std::string())=="lightning_accepted_hit_damage") {
                if(integer(outcome.at("instance_id"))==0 || outcome.at("hp_damage").get<int>()<0)
                    throw std::invalid_argument("Invalid frozen lightning contact outcome");
                continue;
            }
            if(outcome.at("kind")!="extended_status_application" || !outcome.at("procced").is_boolean())
                throw std::invalid_argument("Unknown frozen extended status outcome");
            const bool fromSkill=outcome.at("from_skill");
            if(fromSkill && !skill) throw std::invalid_argument("Frozen skill status outcome lacks its original skill source");
            const auto &entries=fromSkill?skill->entries:sources_.at(record.at("identity").at("source_path")).entries;
            bool matched=false;for(const auto &entry:entries) if(entry.snapshot()==outcome.at("status")) matched=true;
            if(!matched) throw std::invalid_argument("Frozen extended status outcome no longer matches its source");
            if(outcome.at("procced").get<bool>()) {
                const auto id=integer(outcome.at("instance_id"));
                if(!id || !applicationIds.insert(id).second || (instances_.nextValue() && id>=instances_.nextValue()))
                    throw std::invalid_argument("Frozen extended status application ID watermark mismatch");
            }
        }
    }
    std::set<uint64_t> ids;for(const auto &[target,stun]:active_) ids.insert(stun.id);
    for(const auto &v:saved) {
        StatusEffectInstance effect;effect.id=integer(v.at("id"));effect.kind=kindFrom(v.at("kind"));
        effect.attacker=EntityHandle::fromJson(v.at("attacker"));effect.target=EntityHandle::fromJson(v.at("target"));
        effect.attackInstance=integer(v.at("attack_instance"));const auto hit=integer(v.at("hit_index"));
        if(hit>UINT32_MAX) throw std::invalid_argument("Extended status hit index overflow");effect.hitIndex=uint32_t(hit);
        const auto age=integer(v.at("applied_ago_ms")),remaining=integer(v.at("remaining_ms")),next=integer(v.at("next_damage_in_ms"));
        const auto overdue=integer(v.value("next_damage_overdue_ms",Json(uint64_t(0))));
        if(age>nowMs || !remaining || !effect.id || !ids.insert(effect.id).second || !effect.attacker || !effect.target ||
           !effect.attackInstance || !isLive(effect.target) || (instances_.nextValue() && effect.id>=instances_.nextValue()))
            throw std::invalid_argument("Extended status checkpoint live identity, time or watermark mismatch");
        if(overdue>nowMs || (overdue && next)) throw std::invalid_argument("Extended status overdue schedule mismatch");
        effect.appliedMs=nowMs-age;effect.expiresMs=addTime(nowMs,remaining);effect.nextDamageMs=overdue?nowMs-overdue:addTime(nowMs,next);
        effect.intervalMs=v.at("interval_ms");effect.hpDamage=v.at("hp_damage");effect.remainingTriggers=v.value("remaining_triggers",0u);
        effect.definition=v.at("definition");effect.trace=v.at("trace");effect.preserved=v;
        if(effect.intervalMs!=1000 || effect.hpDamage<0 || !effect.trace.is_array() || effect.trace.size()!=1)
            throw std::invalid_argument("Extended status checkpoint damage or interval policy mismatch");
        const auto attack=readAttackStatuses(resolver(effect.definition.at("attack_path")));
        if(!attack.usable() || sha256(attack.source.rawBytes)!=effect.definition.at("attack_sha256") ||
           attack.source.source.value("package_identity",std::string())!=packageIdentity_)
            throw std::invalid_argument("Extended status checkpoint ATK source mismatch");
        std::optional<SkillStatusApplication> skill;if(effect.definition.at("from_skill").get<bool>())
            skill=skillFromSaved(effect.definition.at("skill"),resolver);
        const auto &entries=skill?skill->entries:attack.entries;const AttackStatusEntry *matched=nullptr;
        for(const auto &entry:entries) if(entry.snapshot()==effect.definition.at("entry")) matched=&entry;
        if(!matched || matched->kind!=effect.kind || age+remaining!=matched->durationMs || next>effect.intervalMs ||
           (matched->maximumTriggers && (!effect.remainingTriggers || effect.remainingTriggers>matched->maximumTriggers)))
            throw std::invalid_argument("Extended status checkpoint source entry or relative schedule mismatch");
        StatusRequest q;const auto &trace=effect.trace[0];q.independentAttack=trace.at("independent_attack");q.independentRate=trace.at("independent_rate");
        q.strength=trace.at("strength");q.intelligence=trace.at("intelligence");
        if(trace.at("policy")!="inferred-1031-active-status-v1" || trace.at("periodic_interval_ms")!=1000 ||
           trace.at("damage_points")!=effect.hpDamage || damagePoints(*matched,q,bool(skill))!=effect.hpDamage)
            throw std::invalid_argument("Extended status frozen damage snapshot mismatch");
        bool contact=false;
        for(const auto &[key,record]:contacts_) if(record.at("identity").at("target")==effect.target.json() &&
            record.at("identity").at("attacker")==effect.attacker.json() && record.at("identity").at("attack_instance")==effect.attackInstance &&
            record.at("identity").at("hit_index")==effect.hitIndex && record.contains("extended_outcomes"))
            for(const auto &outcome:record.at("extended_outcomes")) if(outcome.value("instance_id",uint64_t(0))==effect.id &&
                outcome.value("procced",false) && outcome.at("definition")==effect.definition) contact=true;
        if(!contact || !effects_.emplace(std::make_pair(effect.target,effect.kind),std::move(effect)).second)
            throw std::invalid_argument("Extended status checkpoint has no same-generation accepted contact or duplicates a target/kind");
    }
}
} // namespace dnf
