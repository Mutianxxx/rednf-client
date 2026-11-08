#pragma once
#include "resources.hpp"
#include <array>
#include <string>
#include <vector>

namespace dnf {
class Pvf;

// One [object] entry of a .ptl: the animation a particle draws and the frame it
// holds. 40JP gives every particle its own clock (+33 = sub_699000(+104 clock)),
// so the animation advances with the particle's age, not with the skill's.
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
};

PtlProgram readPtl(Pvf &, const std::string &path);

struct PreviewParticle {
    std::array<double, 3> origin{};
    std::array<double, 3> velocityStart{};
    std::array<double, 3> velocityEnd{};
    std::array<int32_t, 3> changingTerm{};
    double ageMs = 0, lifeMs = 0, gravity = 0;
    double alphaStart = 100, alphaEnd = 100;
    std::string animation;
    int frame = -1;
    bool alive() const { return ageMs < lifeMs; }
};

// Axis displacement follows the reviewed straight/keep-last evaluator (1031
// E581E0, VA 1565E18, scale 0.001 per ms), which is 40JP's CNRDParticle__vmt48
// linear/trapezoid branch (pvp_ui.cpp:5940-6000). The gravity term is 40JP's
// vmt8 free-fall second order: z += age^2 * gravity / -2000000
// (pvp_ui.cpp:6330). Positions are a pure function of age, so a seek needs no
// integration history.
std::array<double, 3> particlePosition(const PreviewParticle &);
// Linear [transparent value] fade across the lifetime. The two endpoints are
// source values; the linear ramp itself is inference.
double particleAlpha(const PreviewParticle &);

struct PreviewParticleField {
    std::vector<PreviewParticle> particles;

    void clear() { particles.clear(); }
    // Emits program.count particles around (originX, originY). The seed keeps a
    // replay of the same skill identical, which 40JP does not have to care about
    // but a demonstration does.
    void spawn(const PtlProgram &, double originX, double originY, unsigned seed);
    void advance(double dtMs);
    void seekFrom(double actionMs);
    size_t aliveCount() const;
};
} // namespace dnf
