#pragma once
#include "dnf/attack_status.hpp"
#include "dnf/damage_resolution.hpp"

namespace dnf {
// Private candidate shared by ordinary World contacts and ACT collisions.
// It never changes the supplied host/random or HP. The owner validates its
// complete actor/reaction/ledger transaction before no-throw publication.
struct PreparedDamageContact {
    DamageResolution resolution;
    std::optional<StatusHost> statuses;
    std::optional<RandomStreams> random;
    bool ready() const { return resolution.usable() && statuses && random; }
};
PreparedDamageContact prepareDamageContact(const DamageRequest &,
    const DamageResolutionPolicy &,const StatusResistanceSnapshot &,
    const StatusHost &,const RandomStreams &,uint64_t nowMs,
    const SkillStatusApplication *skill = nullptr);
// Caller-owned candidates only; no stale-candidate protection is implied.
// World/ACT single-writer coordinators must publish HP/IDs/ledger with this.
void publishDamageContact(PreparedDamageContact &&,StatusHost &,RandomStreams &) noexcept;
} // namespace dnf
