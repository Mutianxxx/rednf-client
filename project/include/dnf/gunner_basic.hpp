#pragma once
#include "content_profile.hpp"
#include "female_gunner_timing.hpp"
#include <array>
#include <map>
namespace dnf {
struct GunnerBasicSource {
    SourceRef settings;
    int subtype=-1;
    std::array<int32_t,10> values{};
    Json snapshot() const;
};
struct GunnerBasicDeadlines {
    int32_t shot=0,continuation=0,recovery=0,drawRate=1000,shootRate=1000;
    Json snapshot() const;
};
std::map<int,GunnerBasicSource> readGunnerBasicSources(Pvf &);
GunnerBasicDeadlines gunnerBasicDeadlines(const GunnerBasicSource &,double effectiveAttackSpeed,bool finalShot);
FemaleGunnerStageTiming gunnerBasicStageTiming(const Animation &,int phase,const GunnerBasicDeadlines &);
struct GunnerBasicParticle {
    SourceRef source;
    std::array<int32_t,3> axisVelocity{};
    int32_t lifetimeMs=0;
    double pitchDegrees=0;
    Json fields;
    Json snapshot() const;
    std::array<float,3> displacement(int32_t elapsedMs) const;
};
GunnerBasicParticle readGunnerBasicParticle(Pvf &,const Script &);
} // namespace dnf
