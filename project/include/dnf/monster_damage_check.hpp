#pragma once
#include "dnf/content_profile.hpp"
#include "dnf/simulation.hpp"

namespace dnf {
inline constexpr const char *monsterDamageWindowPolicy="inferred-source-damage-window-rolling-v1";
struct MonsterDamageSample {
    uint64_t eventId=0,acceptedMs=0;
    int actualHpLoss=0;
};
struct MonsterDamageWindow {
    bool enabled=false;
    uint64_t intervalMs=0,configuredMs=0;
    SourceRef monsterSource,configurationSource;
    std::vector<MonsterDamageSample> samples;
    Json receipt=Json::object();
    int64_t amount(uint64_t nowMs) const;
    void prune(uint64_t nowMs);
    Json snapshot() const;
};
// Source and command shape are validated before callers publish HP/RNG/ACT.
MonsterDamageWindow initialMonsterDamageWindow(const Pvf &,const Script &,uint64_t nowMs);
void configureMonsterDamageWindow(MonsterDamageWindow &,bool enabled,uint64_t intervalMs,
    uint64_t nowMs,const SourceRef &commandSource);
MonsterDamageWindow restoreMonsterDamageWindow(const Pvf &,const Script &,const Json &,uint64_t nowMs);
} // namespace dnf
