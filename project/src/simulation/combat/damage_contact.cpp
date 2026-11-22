#include "dnf/damage_contact.hpp"
#include <algorithm>
#include <cassert>
#include <type_traits>

namespace dnf {
PreparedDamageContact prepareDamageContact(const DamageRequest &request,
    const DamageResolutionPolicy &policy,const StatusResistanceSnapshot &resistance,
    const StatusHost &statuses,const RandomStreams &random,uint64_t nowMs,
    const SkillStatusApplication *skill) {
    PreparedDamageContact prepared;
    auto candidateStatuses=statuses;
    auto candidateRandom=random;
    auto &stream=candidateRandom.stream(RandomDomain::Combat,request.attackInstance);
    auto damageRequest=request;
    const auto blind=candidateStatuses.blindMissPercent(request.attacker,nowMs);
    damageRequest.attackerStats.attackMissDeltaPercent+=float(blind);
    prepared.resolution=resolveDamage(damageRequest,policy,&stream);
    auto &result=prepared.resolution;
    if(blind)result.trace.push_back({{"stage","blind_accuracy_consumer"},{"increase_miss_percent",blind},
        {"source",candidateStatuses.activeEffects(request.attacker,nowMs)}});
    if(!result.usable())return prepared;
    PreparedStatusApplication application;
    if(!result.missed) {
        auto source=readAttackStatuses(request.attack.source);
        const bool hasStatus=std::any_of(source.entries.begin(),source.entries.end(),[](const AttackStatusEntry &entry) {
            return entry.runtime && entry.kind!=AttackStatusKind::None;
        });
        if(!source.usable() || hasStatus || (skill && !skill->entries.empty()) || candidateStatuses.hasEffects(request.target,nowMs)) {
            StatusRequest status;
            status.attacker=request.attacker;status.attackerLevel=request.attackerStats.level;
            status.target={request.target,resistance,false,Json::object()};
            status.attackInstance=request.attackInstance;status.hitIndex=request.hitIndex;
            status.attack=std::move(source);if(skill)status.skill=*skill;
            status.independentAttack=request.attackerStats.independentAttack;status.independentRate=request.attackerStats.independentRate;
            status.strength=request.attackerStats.strength;status.intelligence=request.attackerStats.intelligence;
            application=candidateStatuses.prepare(status,nowMs,stream);
            result.trace.push_back({{"stage","attack_status_transaction"},{"receipt",application.receipt}});
            if(!application.ready() || !candidateStatuses.canPublish(application,stream)) {
                result.hpDamage.reset();result.diagnostics.push_back({{"kind","status_transaction_blocked"},{"severity","error"},
                    {"receipt",application.receipt}});return prepared;
            }
            const auto bonus=application.receipt.value("bonus_hp_damage",0);
            if(bonus<0 || bonus>INT32_MAX-*result.hpDamage) {
                result.hpDamage.reset();result.diagnostics.push_back({{"kind","status_contact_damage_overflow"},{"severity","error"}});return prepared;
            }
            *result.hpDamage+=bonus;
        }
    }
    if(application.ready())candidateStatuses.publish(std::move(application),stream);
    prepared.statuses=std::move(candidateStatuses);prepared.random=std::move(candidateRandom);
    return prepared;
}
void publishDamageContact(PreparedDamageContact &&prepared,StatusHost &statuses,RandomStreams &random) noexcept {
    assert(prepared.ready());
    static_assert(std::is_nothrow_swappable<StatusHost>::value,"Contact status publication must not throw");
    static_assert(std::is_nothrow_swappable<RandomStreams>::value,"Contact random publication must not throw");
    using std::swap;swap(statuses,*prepared.statuses);swap(random,*prepared.random);
}
} // namespace dnf
