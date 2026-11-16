#pragma once
#include "dnf/resources.hpp"
#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace dnf {
class Pvf;

// One [object] entry of a .ptl: the animation a particle draws and the frame it
// holds. 40JP gives every particle its own clock (+33 = sub_699000(+104 clock)),
// so the animation advances with the particle's age, not with the skill's.
// This definition lives in dnf_core: both the standalone previewer and the ACT
// World particle factory must read the same 1031 PTL bytes, not two parsers.
struct PtlObject {
    std::string animation;
    int frame = -1;
};

// A one-shot burst emitter. Field set mirrors the reviewed PTL readers of this
// project (src/presentation/maps/object_presentation.cpp:14-47,
// src/simulation/jobs/gunner_basic.cpp readGunnerBasicParticle): straight-line
// motion, per-axis velocity range with an optional keep-last changing term,
// gravity, lifetime, particle count, spawn area and an alpha fade.
// Anything else is reported, never guessed.
struct PtlProgram {
    std::string path;
    std::vector<PtlObject> objects;
    std::array<std::array<double, 2>, 3> velocity{}; // [axis][start,end]
    std::array<int32_t, 3> changingTermMs{};         // 0 = pure linear
    std::array<double, 3> area{};
    double gravity = 0;
    double lifeMs = 0;
    int count = 0;
    double alphaStart = 100, alphaEnd = 100; // [transparent value], percent
    std::string error;
    Json diagnostics = Json::array();
    bool valid() const { return error.empty() && !objects.empty() && count > 0 && lifeMs > 0; }
    // Syntax validity is NOT runtime equivalence. Diagnostics list every source
    // field whose behavior this build does not consume; a fully consumed PTL has
    // no diagnostics.
    bool fullyConsumed() const { return diagnostics.empty(); }
};

// Pure tag classification used by the shared decoder and its tests. A false
// result never means "safe to ignore": the decoder records a diagnostic.
bool ptlFieldConsumed(const std::string &tag);
bool ptlFieldStructural(const std::string &tag);
PtlProgram readPtl(Pvf &, const std::string &path);
} // namespace dnf
