#pragma once
#include "monster_effects.hpp"

namespace dnf {
// Compiles only the current MOB's explicit EQU references. No appearance is
// inferred from the species, filename stem or a different monster's defaults.
// Does not alter duration, gameplay boxes, source animations or Actor state.
void appendMonsterEquipment(Pvf &, Assets &, MonsterMotion &, const std::string &monster);
// The selected body clip supplies elapsed/source delays for the visual layer.
// This same-motion synchronization is a classified beta inference.
std::optional<ani_clock::Snapshot> monsterTrackClock(const MonsterMotion &, const MonsterTrack &, double time);
Json runMonsterEquipmentTests(Pvf &, Assets &);
}
