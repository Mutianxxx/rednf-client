#include "dnf/act_particles.hpp"
#include <algorithm>
#include <cstdint>
#include <limits>

namespace dnf {
namespace {
uint64_t fnv1a(const std::string &value) {
    uint64_t hash = 1469598103934665603ull;
    for (unsigned char c : value) { hash ^= c; hash *= 1099511628211ull; }
    return hash;
}
uint64_t splitMix(uint64_t &state) {
    state += 0x9E3779B97F4A7C15ull;
    uint64_t z = state;
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    return z ^ (z >> 31);
}
double unit(uint64_t &state) {
    return double(splitMix(state) >> 11) * (1.0 / 9007199254740992.0);
}
double within(const std::array<double, 2> &range, uint64_t &state) {
    return range[0] + (range[1] - range[0]) * unit(state);
}
int32_t ageMs(const ActParticleInstance &particle) {
    return int32_t(std::clamp(particle.ageUs / 1000, int64_t(0), int64_t(INT32_MAX)));
}
} // namespace

std::array<double, 3> ActParticleInstance::position() const {
    const int32_t age = ageMs(*this);
    std::array<double, 3> out{x, y, z};
    for (size_t axis = 0; axis < 3; ++axis) {
        const float delta = particleStraightKeepLast(
            int32_t(std::clamp(velocity[axis][0], double(INT32_MIN), double(INT32_MAX))),
            int32_t(std::clamp(velocity[axis][1], double(INT32_MIN), double(INT32_MAX))),
            changingTermMs[axis], age);
        out[axis] += double(delta);
    }
    out[2] += double(age) * double(age) * gravity / -2000000.0;
    return out;
}
double ActParticleInstance::alpha() const {
    if (lifeUs <= 0) return 1;
    const double progress = std::clamp(double(ageUs) / double(lifeUs), 0.0, 1.0);
    // The two [transparent value] endpoints are source bytes; the linear ramp
    // is an explicit inferred presentation policy, not recovered EXE behavior.
    return std::clamp((alphaStart + (alphaEnd - alphaStart) * progress) / 100.0, 0.0, 1.0);
}
Json ActParticleInstance::json() const {
    return {{"serial", serial}, {"act_instance_id", actInstanceId}, {"action_id", actionId},
            {"sequence", sequence}, {"program", program}, {"animation", animation},
            {"image", image}, {"frame", frame}, {"x", x}, {"y", y}, {"z", z},
            {"offset", {offsetX, offsetY, offsetZ}}, {"position", position()},
            {"velocity", {velocity[0], velocity[1], velocity[2]}},
            {"changing_term_ms", {changingTermMs[0], changingTermMs[1], changingTermMs[2]}},
            {"gravity", gravity}, {"direction", direction},
            {"age_us", ageUs}, {"life_us", lifeUs},
            {"alpha", alpha()}, {"alive", alive()}};
}
size_t ActParticleSystem::emit(const ActParticleEmit &request) {
    const auto &a = request.admission;
    if (!a || a->objects.empty() || a->count <= 0 || a->lifeUs <= 0) return 0;
    if (instances_.size() >= maximumInstances) return 0;
    const size_t before = instances_.size();
    const size_t budget = std::min(size_t(a->count), maximumInstances - instances_.size());
    for (size_t i = 0; i < budget; ++i) {
        const auto &object = a->objects[i % a->objects.size()];
        if (nextSerial_ == std::numeric_limits<uint64_t>::max()) break;
        // Local deterministic source sampling. It keeps replay identical without
        // consuming the World RNG or perturbing gameplay random streams; the
        // PRNG policy itself is reconstruction, not a recovered 1031 algorithm.
        uint64_t state = fnv1a(request.program) ^ request.actInstanceId ^
                         (request.actionId * 0x9E3779B97F4A7C15ull) ^
                         (request.sequence * 0xBF58476D1CE4E5B9ull) ^ nextSerial_;
        ActParticleInstance particle;
        particle.serial = nextSerial_++;
        particle.actInstanceId = request.actInstanceId;
        particle.actionId = request.actionId;
        particle.sequence = request.sequence;
        particle.program = request.program;
        particle.animation = object.animation;
        particle.image = object.image;
        particle.frame = object.frame;
        for (size_t axis = 0; axis < 3; ++axis) {
            particle.velocity[axis][0] = within(a->velocity[axis], state);
            particle.velocity[axis][1] = within(a->velocity[axis], state);
            particle.changingTermMs[axis] = a->changingTermMs[axis];
            particle.areaOffset[axis] = a->area[axis] * (unit(state) - 0.5);
        }
        particle.gravity = a->gravity;
        particle.x = request.x + particle.areaOffset[0];
        particle.y = request.y + particle.areaOffset[1];
        particle.z = request.z + particle.areaOffset[2];
        particle.offsetX = request.offsetX; particle.offsetY = request.offsetY;
        particle.offsetZ = request.offsetZ;
        particle.direction = request.direction;
        particle.lifeUs = a->lifeUs;
        particle.alphaStart = a->alphaStart; particle.alphaEnd = a->alphaEnd;
        instances_.push_back(std::move(particle));
    }
    return instances_.size() - before;
}
std::vector<uint64_t> ActParticleSystem::advance(int64_t deltaUs) {
    if (deltaUs <= 0 || instances_.empty()) return {};
    std::vector<uint64_t> expired;
    for (auto &particle : instances_) {
        if (particle.ageUs > std::numeric_limits<int64_t>::max() - deltaUs)
            particle.ageUs = std::numeric_limits<int64_t>::max();
        else particle.ageUs += deltaUs;
        if (!particle.alive()) expired.push_back(particle.serial);
    }
    if (!expired.empty())
        instances_.erase(std::remove_if(instances_.begin(), instances_.end(),
                                        [](const auto &p) { return !p.alive(); }), instances_.end());
    return expired;
}
size_t ActParticleSystem::retireActInstance(uint64_t actInstanceId) {
    const auto before = instances_.size();
    instances_.erase(std::remove_if(instances_.begin(), instances_.end(),
                                    [&](const auto &p) { return p.actInstanceId == actInstanceId; }),
                     instances_.end());
    return before - instances_.size();
}
size_t ActParticleSystem::aliveCount() const {
    return size_t(std::count_if(instances_.begin(), instances_.end(),
                                [](const auto &p) { return p.alive(); }));
}
} // namespace dnf
