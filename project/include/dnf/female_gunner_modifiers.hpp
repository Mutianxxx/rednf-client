#pragma once
#include "female_gunner.hpp"
#include "skill_cost.hpp"
#include <map>

namespace dnf {
struct ExperimentalCharacterPlan;
struct FemaleGunnerAttackContext {
    int weaponSubtype = -1;
    int characterLevel = 1;
    std::optional<SkillKey> attackSkill;
    std::string family, basicMotion;
    bool airborne = false, backAttack = false;
};
// Input is already filtered to live, owner-bound buffs by World. These pure
// evaluators never alter the normal learning ledger, content or live entities.
struct FemaleGunnerActorModifiers {
    double moveMultiplier=1, attackMultiplier=1, castMultiplier=1, jumpMultiplier=1;
    double strength=0, intelligence=0, vitality=0, spirit=0;
    double physicalDefense=0, magicalDefense=0, evasionPercent=0;
    double physicalCriticalPercent=0, magicalCriticalPercent=0;
    double physicalDamageReductionPercent=0, magicalDamageReductionPercent=0;
    double hpMaximumMultiplier=1;
    Json trace=Json::array(), diagnostics=Json::array();
    Json snapshot() const;
};
struct FemaleGunnerCostModifiers {
    std::vector<SkillCostModifier> mp, cooldown;
    Json trace=Json::array(), diagnostics=Json::array();
};
// Selects the linked feature's alternate source tables/schema at BASE level,
// then applies exact [special level up] cells at learned TP level to a private
// copy and reevaluates duration/count/coefficient consumers. This source-led
// template selection is explicitly inferred; each mode remains independent.
void applyFemaleGunnerTpOperands(FemaleGunnerSkillCommand &,
    const std::map<SkillKey,int> &configured, const ExperimentalCharacterPlan &,
    int weaponSubtype = -1);
// Reload-time maximum, independent of the subsequently consumed live charges.
void applyFemaleGunnerAmmoCapacity(FemaleGunnerSkillCommand &,
    const std::map<SkillKey,int> &configured, const ExperimentalCharacterPlan &);
struct FemaleGunnerShotCountModifier {
    uint32_t extraShots = 0;
    Json trace = Json::array();
};
FemaleGunnerShotCountModifier femaleGunnerAdditionalBasicShots(
    const std::map<SkillKey,int> &configured,const ExperimentalCharacterPlan &,int weaponSubtype);
int femaleGunnerEffectiveSkillLevel(SkillKey, int configuredLevel,
    const std::map<SkillKey,int> &configured, const ExperimentalCharacterPlan &);
FemaleGunnerActorModifiers evaluateFemaleGunnerActorModifiers(
    const std::vector<FemaleGunnerSkillCommand> &liveBuffs,
    const std::map<SkillKey,int> &configured, const ExperimentalCharacterPlan &, int weaponSubtype);
FemaleGunnerCostModifiers femaleGunnerCostModifiers(SkillKey,
    const std::vector<FemaleGunnerSkillCommand> &liveBuffs,
    const std::map<SkillKey,int> &configured, const ExperimentalCharacterPlan &, int weaponSubtype);
Json applyFemaleGunnerAttackOperands(DamageRequest &,
    const std::vector<FemaleGunnerSkillCommand> &liveBuffs,
    const std::map<SkillKey,int> &configured, const ExperimentalCharacterPlan &,
    const FemaleGunnerAttackContext &);
Json runFemaleGunnerModifierTests(Pvf &, Assets &);
} // namespace dnf
