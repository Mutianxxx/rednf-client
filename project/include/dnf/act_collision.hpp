#pragma once
#include "dnf/monster_behavior.hpp"
#include "dnf/damage_contact.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace dnf {
struct ActCollisionAttack {
    Script original;
    AttackDamageDefinition damage;
    std::string reaction = "[damage]", sound;
    double push = 0, lift = 0, pauseMs = 0, delayRate = 1;
    bool enemy = true;
    Json hitInfo = Json::array(), diagnostics = Json::array();
    bool sourceReady = false, reactionReady = false;
};
// Retains all ATK bytes/fields. Non-neutral unimplemented reaction mechanics
// stay a precise contact-time gate; damage parsing does not grant reaction.
ActCollisionAttack readActCollisionAttack(const Script &);
// One independently timed authored ANI track inside an ACT MOTION. BASE has a
// zero start; SUB inherits its source frame boundary, layer and XY placement.
// Each track owns its attack/hit identity so an ATTACKRECT reset cannot erase
// contact evidence belonging to another source animation.
struct ActCollisionTrack {
    std::string animation;
    uint64_t startUs = 0, endUs = UINT64_MAX;
    bool loop = false;
    double x = 0, y = 0;
    int layer = 0;
    uint64_t attackInstance = 0;
    uint32_t hitIndex = 0;
    bool enabled = true;
    std::string lastBlockedReason;
    std::map<EntityHandle,Json> acceptedTargets;
};
struct ActCollisionState {
    uint64_t attackInstance = 0;
    uint32_t hitIndex = 0;
    bool enabled = true;
    std::string baseAnimation, defaultAttack, currentAttack;
    // Full source-route receipt, including exact paired MOB or OBJ operand.
    // Empty for an explicitly self-contained ACT DEFAULT ATTACKINFO binding.
    Json route = Json::object();
    std::string lastBlockedReason;
    std::map<EntityHandle,Json> acceptedTargets;
    // Non-empty once the ACT has more than one attack-bearing MOTION track.
    std::vector<ActCollisionTrack> tracks;
};
// Samples both actual crossed ANI frames and the currently active frame. The
// host applies one fixed-tick endpoint position; this is named beta inference,
// not continuous collision or a recovered native scheduler.
std::vector<size_t> actCollisionFrames(const Animation &,uint64_t beforeUs,
    uint64_t afterUs,bool first,size_t maximum = 4096);
} // namespace dnf
