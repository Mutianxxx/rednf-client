#pragma once
#include "dnf/act_runtime.hpp"
#include "dnf/particle_motion.hpp"
#include "dnf/ptl_program.hpp"
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace dnf {
// An admitted ACT PTL program. This is a static-admission record: the PTL
// bytes were decoded with the same readPtl the previewer uses, every [object]
// ANI/ALS/IMG texture leaf was validated by the World resource resolver, and
// the source lifetime/count remain byte-derived. Fields the World factory does
// NOT consume are listed explicitly instead of being silently dropped.
struct ActParticleObject {
    std::string animation; // [object] .ani
    std::string image;     // resolved IMG texture member of the selected frame
    int frame = -1;        // [object] frame; -1 means the ANI's own clock
};
struct ActParticleAdmission {
    std::string program;
    std::vector<ActParticleObject> objects;
    std::vector<ActDependency> dependencies;
    std::vector<std::string> unrecovered;
    int count = 0;
    int64_t lifeUs = 0;
    double alphaStart = 100, alphaEnd = 100;
    std::array<std::array<double, 2>, 3> velocity{};
    std::array<int32_t, 3> changingTermMs{};
    std::array<double, 3> area{};
    double gravity = 0;
    // True only when every source PTL field has a real consumer. Runtime
    // execution can still be a documented subset when this is false.
    bool equivalent = false;
};

// 一个由 World 持有的真实粒子。按策略是瞬态的：它不属于
// ACT host 的 checkpoint，与 ActWorldHost::spawnedObjects() 同理。
// 每个粒子有自己的时钟，因此能在发出它的 ACT 动作自然结束后继续存活。
struct ActParticleInstance {
    uint64_t serial = 0, actInstanceId = 0, actionId = 0, sequence = 0;
    std::string program, animation, image;
    int frame = -1;
    double x = 0, y = 0, z = 0;
    double offsetX = 0, offsetY = 0, offsetZ = 0; // source [PARTICLE] XYZ
    std::array<std::array<double, 2>, 3> velocity{};
    std::array<int32_t, 3> changingTermMs{};
    std::array<double, 3> areaOffset{}; // deterministic spawn offset from [create area size]
    double gravity = 0;
    int direction = 1; // emitting owner's immutable facing receipt
    int64_t ageUs = 0, lifeUs = 0;
    double alphaStart = 100, alphaEnd = 100;
    bool alive() const { return ageUs < lifeUs; }
    double alpha() const;
    // Pure function of the particle's own age: straight/keep-last per axis plus
    // the reviewed free-fall term. No integration history is stored.
    std::array<double, 3> position() const;
    Json json() const;
};
struct ActParticleEmit {
    uint64_t actInstanceId = 0, actionId = 0, sequence = 0;
    std::string program;
    double x = 0, y = 0, z = 0;
    double offsetX = 0, offsetY = 0, offsetZ = 0;
    int direction = 1;
    std::shared_ptr<const ActParticleAdmission> admission;
};

// No renderer, wall clock, World RNG or combat dependency. The outer host
// advances this exactly once per fixed simulation tick with an already-scaled
// delta. Straight/keep-last velocity, free-fall gravity and source area are a
// pure function of that clock; continuous emission, rotation and landing are
// still explicit gaps (P0-2 #76).
class ActParticleSystem {
    std::vector<ActParticleInstance> instances_;
    uint64_t nextSerial_ = 1;
  public:
    static constexpr size_t maximumInstances = 512;
    void clear() { instances_.clear(); }
    const std::vector<ActParticleInstance> &instances() const { return instances_; }
    // Returns the number of particles actually created (budget-bounded).
    size_t emit(const ActParticleEmit &);
    // Advances every particle's independent clock; returns expired serials.
    std::vector<uint64_t> advance(int64_t deltaUs);
    // Explicit ownership cleanup (cancel / room change), returns retired count.
    size_t retireActInstance(uint64_t actInstanceId);
    size_t aliveCount() const;
};
} // namespace dnf
