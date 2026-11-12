#include "dnf/act_particles.hpp"
#include <algorithm>
#include <limits>

namespace dnf {
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
            {"offset", {offsetX, offsetY, offsetZ}}, {"age_us", ageUs}, {"life_us", lifeUs},
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
        ActParticleInstance particle;
        particle.serial = nextSerial_++;
        particle.actInstanceId = request.actInstanceId;
        particle.actionId = request.actionId;
        particle.sequence = request.sequence;
        particle.program = request.program;
        particle.animation = object.animation;
        particle.image = object.image;
        particle.frame = object.frame;
        particle.x = request.x; particle.y = request.y; particle.z = request.z;
        particle.offsetX = request.offsetX; particle.offsetY = request.offsetY;
        particle.offsetZ = request.offsetZ;
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
