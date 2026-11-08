#pragma once
#include "dnf/female_gunner.hpp"
namespace dnf {
// Explicit reconstructed phase dispatch. Every ANI/ATK is selected from the
// exact owning OBJ/MOB ordered binding; no parallel-array or filename pairing.
std::vector<FemaleGunnerSkillCommand> expandFemaleGunnerEntities(Pvf &, Assets &,
    const std::vector<FemaleGunnerSkillCommand> &);
// A real controller phase-entry receipt. The owning action, exact CHR source
// and phase identity govern lifetime; its visual tracks keep independent ANI
// clocks. No collision, attack or resource charge is added by this receipt.
std::optional<FemaleGunnerSkillCommand> femaleGunnerHeavyStageVisualReceipt(
    const FemaleGunnerSkillCommand &,const SourceRef &motion,size_t stage);
// Exact display operands: G2/G3's extension is never a fresh base duration.
int64_t femaleGunnerGTransformBaseDurationMs(const FemaleGunnerSkillCommand &);
int64_t femaleGunnerGTransformExtensionMs(const FemaleGunnerSkillCommand &);
// Call only after the enchanted projectile has actually hit. Caller supplies
// that contact's world origin; categories are original MOB category names.
std::vector<FemaleGunnerSkillCommand> femaleGunnerFlameImpactCommands(Pvf &, Assets &,
    const FemaleGunnerSkillCommand &, const std::vector<std::string> &targetCategories = {});
Json runFemaleGunnerEntityTests(Pvf &, Assets &);
}
