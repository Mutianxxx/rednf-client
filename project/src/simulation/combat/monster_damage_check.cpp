#include "dnf/monster_damage_check.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
uint64_t integer(const Json &v,uint64_t high=UINT64_MAX) {
    if(!v.is_number_integer() || (!v.is_number_unsigned()&&v.get<int64_t>()<0) || v.get<uint64_t>()>high)
        throw std::invalid_argument("Invalid monster damage-window unsigned integer");
    return v.get<uint64_t>();
}
Json description() {
    return {{"policy",monsterDamageWindowPolicy},{"classification","inferred_beta"},
        {"quantity","accepted actual HP decrease; overkill clipped; zero accepted contacts retained; DOT excluded until separate consumer"},
        {"window","rolling accepted_ms >= max(configured_ms,now_ms-interval_ms), inclusive endpoint; no reset on query"},
        {"comparison","window_amount>=authored_threshold"},
        {"reconfigure","every explicit ACT start/stop resets samples at command publication; pending accepted queries retain their immutable prior window sum"},
        {"origin","source MOB interval from consumer install; ACT interval from actual typed command commit"},
        {"native_window_reset_comparison_and_timer","unconfirmed"}};
}
}
int64_t MonsterDamageWindow::amount(uint64_t ms) const {
    if(!enabled)return 0;
    if(ms<configuredMs)throw std::invalid_argument("Monster damage-window time moved backwards");
    int64_t result=0;
    for(const auto &s:samples)if(s.acceptedMs>=configuredMs&&s.acceptedMs<=ms&&ms-s.acceptedMs<=intervalMs)result+=s.actualHpLoss;
    return result;
}
void MonsterDamageWindow::prune(uint64_t ms) {
    if(ms<configuredMs)throw std::invalid_argument("Monster damage-window time moved backwards");
    samples.erase(std::remove_if(samples.begin(),samples.end(),[&](const auto &s) {
        return !enabled||s.acceptedMs<configuredMs||s.acceptedMs>ms||ms-s.acceptedMs>intervalMs;
    }),samples.end());
}
Json MonsterDamageWindow::snapshot() const {
    Json rows=Json::array();for(const auto &s:samples)rows.push_back({{"event_id",s.eventId},{"accepted_ms",s.acceptedMs},{"actual_hp_loss",s.actualHpLoss}});
    return {{"policy",monsterDamageWindowPolicy},{"enabled",enabled},{"interval_ms",intervalMs},{"configured_ms",configuredMs},
        {"monster_source",monsterSource.json()},{"configuration_source",configurationSource.json()},{"samples",rows},{"receipt",receipt}};
}
MonsterDamageWindow initialMonsterDamageWindow(const Pvf &pvf,const Script &source,uint64_t ms) {
    if(!pvf.has(source.path)||source.rawBytes!=pvf.read(source.path))throw std::invalid_argument("Monster damage-window foreign source");
    MonsterDamageWindow out;out.monsterSource=makeSourceRef(pvf,source.path);out.configurationSource=out.monsterSource;
    out.configuredMs=ms;out.receipt=description();out.receipt["origin"]="source MOB consumer install";
    bool seen=false;
    for(size_t i=0;i<source.fields.size();++i)if(normalize(source.fields[i].tag)=="[set damage check]") {
        if(seen||source.fields[i].values.size()!=1)throw std::invalid_argument("Repeated or malformed MOB SET DAMAGE CHECK");seen=true;
        out.intervalMs=integer(source.fields[i].values[0],INT32_MAX);out.enabled=true;
        out.configurationSource=makeSourceRef(pvf,source.path,source.fields[i].offset,10,i);
        out.receipt["ordered_operands"]=source.fields[i].values;
    }
    out.receipt["initial_configured"]=seen;return out;
}
void configureMonsterDamageWindow(MonsterDamageWindow &out,bool enabled,uint64_t interval,uint64_t ms,const SourceRef &source) {
    if(interval>INT32_MAX||ms<out.configuredMs||source.packageIdentity!=out.monsterSource.packageIdentity)
        throw std::invalid_argument("Invalid ACT monster damage-window configuration");
    out.enabled=enabled;out.intervalMs=interval;out.configuredMs=ms;out.samples.clear();out.configurationSource=source;
    out.receipt=description();out.receipt["origin"]="typed ACT command private batch";
    out.receipt["ordered_operands"]=Json::array({int(enabled),interval});
}
MonsterDamageWindow restoreMonsterDamageWindow(const Pvf &pvf,const Script &monster,const Json &saved,uint64_t ms) {
    if(!saved.is_object()||saved.at("policy")!=monsterDamageWindowPolicy||!saved.at("enabled").is_boolean()||
       !saved.at("samples").is_array()||saved.at("samples").size()>1024||saved.at("monster_source")!=makeSourceRef(pvf,monster.path).json())
        throw std::invalid_argument("Invalid source-bound monster damage-window receipt");
    MonsterDamageWindow out=initialMonsterDamageWindow(pvf,monster,integer(saved.at("configured_ms")));
    if(out.configuredMs>ms)throw std::invalid_argument("Monster damage-window configured in future");
    const auto &ref=saved.at("configuration_source");const auto path=ref.at("member_path").get<std::string>();
    const auto source=pvf.script(path);const auto ordinal=integer(ref.at("ordinal"));
    if(path==monster.path && ref==out.configurationSource.json()) {
        if(saved.at("enabled")!=out.enabled||integer(saved.at("interval_ms"),INT32_MAX)!=out.intervalMs||saved.at("receipt")!=out.receipt)
            throw std::invalid_argument("MOB damage-window configuration changed");
    } else {
        if(ordinal>=source.fields.size()||normalize(source.fields[ordinal].tag)!="[set damage check]"||source.fields[ordinal].values.size()!=2)
            throw std::invalid_argument("Damage-window ACT source opcode missing");
        size_t behavior=0;bool inside=false,found=false;
        for(size_t i=0;i<=ordinal;++i) {
            const auto tag=normalize(source.fields[i].tag);
            if(tag=="[behavior]")inside=true;
            if(i==ordinal)found=inside;
            if(tag=="[/behavior]"){inside=false;++behavior;}
        }
        const auto expected=makeSourceRef(pvf,path,source.fields[ordinal].offset,15,ordinal,"BEHAVIOR["+std::to_string(behavior)+"]");
        if(!found||ref!=expected.json())throw std::invalid_argument("Damage-window ACT SourceRef scope/bytes changed");
        const auto enabled=integer(source.fields[ordinal].values[0],1),interval=integer(source.fields[ordinal].values[1],INT32_MAX);
        configureMonsterDamageWindow(out,enabled!=0,interval,out.configuredMs,expected);
        if(saved.at("enabled")!=out.enabled||integer(saved.at("interval_ms"),INT32_MAX)!=interval||saved.at("receipt")!=out.receipt)
            throw std::invalid_argument("Damage-window ACT frozen inputs changed");
    }
    uint64_t previous=0,lastMs=out.configuredMs;
    for(const auto &row:saved.at("samples")) {
        MonsterDamageSample sample{integer(row.at("event_id")),integer(row.at("accepted_ms")),int(integer(row.at("actual_hp_loss"),INT32_MAX))};
        if(!out.enabled||!sample.eventId||sample.eventId<=previous||sample.acceptedMs<lastMs||sample.acceptedMs>ms)
            throw std::invalid_argument("Invalid monster damage-window sample order or time");
        previous=sample.eventId;lastMs=sample.acceptedMs;out.samples.push_back(sample);
    }
    return out;
}
} // namespace dnf
