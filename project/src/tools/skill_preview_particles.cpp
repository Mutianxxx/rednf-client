#include "dnf/skill_preview_particles.hpp"
#include "dnf/particle_motion.hpp"
#include "dnf/resources.hpp"
#include <algorithm>
#include <cmath>
#include <random>
#include <utility>

namespace dnf {
namespace {
int32_t asInt32(double value) {
    return int32_t(std::clamp(value, double(INT32_MIN), double(INT32_MAX)));
}
} // namespace

// PTL decoding (readPtl) moved to dnf_core's src/simulation/animation/ptl_program.cpp
// so the ACT World particle factory admits the exact same 1031 PTL bytes as
// this previewer. Only the preview-only field/clock helpers remain here.

std::array<double, 3> particlePosition(const PreviewParticle &particle) {
    const auto age = int32_t(std::clamp(particle.ageMs, 0.0, double(INT32_MAX)));
    std::array<double, 3> position{};
    for (size_t axis = 0; axis < 3; ++axis) {
        const float displacement = particleStraightKeepLast(
            asInt32(particle.velocityStart[axis]), asInt32(particle.velocityEnd[axis]),
            particle.changingTerm[axis], age);
        position[axis] = particle.origin[axis] + double(displacement);
    }
    position[2] += particle.ageMs * particle.ageMs * particle.gravity / -2000000.0;
    return position;
}

double particleAlpha(const PreviewParticle &particle) {
    if (particle.lifeMs <= 0) return 1;
    const double progress = std::clamp(particle.ageMs / particle.lifeMs, 0.0, 1.0);
    const double percent = particle.alphaStart +
                           (particle.alphaEnd - particle.alphaStart) * progress;
    return std::clamp(percent / 100.0, 0.0, 1.0);
}

void PreviewParticleField::spawn(const PtlProgram &program, double originX, double originY,
                                unsigned seed) {
    if (!program.valid()) return;
    std::mt19937 random(seed);
    const auto unit = [&]() { return std::uniform_real_distribution<double>(-0.5, 0.5)(random); };
    const auto range = [&](const std::array<double, 2> &bounds) {
        return bounds[0] + (bounds[1] - bounds[0]) * (unit() + 0.5);
    };
    for (int index = 0; index < program.count; ++index) {
        if (particles.size() >= 512) break;
        const auto &object = program.objects[size_t(index) % program.objects.size()];
        PreviewParticle particle;
        particle.origin = {originX + program.area[0] * unit(), originY + program.area[1] * unit(),
                           program.area[2] * unit()};
        for (size_t axis = 0; axis < 3; ++axis) {
            particle.velocityStart[axis] = range(program.velocity[axis]);
            particle.velocityEnd[axis] = range(program.velocity[axis]);
            particle.changingTerm[axis] = program.changingTermMs[axis];
        }
        particle.lifeMs = program.lifeMs;
        particle.gravity = program.gravity;
        particle.alphaStart = program.alphaStart;
        particle.alphaEnd = program.alphaEnd;
        particle.animation = object.animation;
        particle.frame = object.frame;
        particles.push_back(std::move(particle));
    }
}

void PreviewParticleField::advance(double dtMs) {
    if (!(dtMs > 0)) return;
    for (auto &particle : particles) particle.ageMs += dtMs;
    particles.erase(std::remove_if(particles.begin(), particles.end(),
                                   [](const PreviewParticle &particle) { return !particle.alive(); }),
                    particles.end());
}

void PreviewParticleField::seekFrom(double actionMs) {
    if (!(actionMs >= 0)) return;
    // A burst is emitted at the skill's first frame; seeking back to an earlier
    // instant simply rewinds every particle.
    for (auto &particle : particles) particle.ageMs = std::max(0.0, actionMs);
}

size_t PreviewParticleField::aliveCount() const {
    return size_t(std::count_if(particles.begin(), particles.end(),
                                [](const PreviewParticle &particle) { return particle.alive(); }));
}
} // namespace dnf
