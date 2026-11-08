#pragma once
#include "storage.hpp"
namespace dnf {
// Requires an already forked BetaSaveBranch store. Never accepts the normal
// writer. Scene/UI publication remains the application boundary's job.
Json selectBetaTestCharacter(CharacterStore &, int slot, World &, Progression &, CharacterIdentity);
Json unlockExecutableBetaSkills(World &);
}
