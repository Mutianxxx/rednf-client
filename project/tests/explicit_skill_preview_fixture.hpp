#pragma once
#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include <stdexcept>

namespace dnf {
// Test-only opt-in at a fixture's cache/save directory. This permits the old
// source/raw-controller experiments without claiming learned normal skills.
// Production UI independently requires the isolated test branch and debug.
inline void enterExplicitSkillPreviewFixture(World &world) {
    if(!world.isExperimentalCharacter()||world.experimentalSkillPreviewEnabled())return;
    const bool combat=world.combat;world.combat=false;
    const auto result=world.setExperimentalSkillPreviewEnabled(true);world.combat=combat;
    if(!result.ok)throw std::runtime_error("Explicit preview fixture admission: "+result.message);
}
}
