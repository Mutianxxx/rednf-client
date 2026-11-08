#pragma once
#include "resources.hpp"
#include <cmath>
#include <cstdio>

// Resource-backed preview policy. These clocks/trajectories are not recovered
// native controller constants. Keep them distinct from original PTL/ANI data.
namespace dnf {
struct DeathProfile {
    bool configured=false, pieces=false, smoke=false, flash=false;
    int selector=0, palette=0, omit=0;
    std::string image;
    explicit DeathProfile(const Json& row) {
        auto values=row.value("die_effect",Json::array());
        if(values.size()!=1||values[0].size()!=3)return;
        for(auto&v:values[0])if(!v.is_number_integer())return;
        selector=values[0][0];palette=values[0][1];omit=values[0][2];
        // Negative selector has no established meaning here: do not guess.
        configured=selector>=0&&palette>=0&&palette<=9999&&omit>=0;
        if(!configured)return;
        pieces=palette>0&&!(omit&1);smoke=!(omit&4);flash=!(omit&8);
        char path[80];std::snprintf(path,sizeof(path),"monster/common/m%04d.img",palette);image=path;
    }
    Json describe()const{return {{"configured",configured},{"raw",{selector,palette,omit}},{"piece_image",image},{"pieces",pieces},{"smoke",smoke},{"flash",flash},{"blood_executed",false},{"native_route_selection_verified",false}};}
};
struct DeathParticle {double x,y,vx,vy,spin,angle;int frame;double size;};
struct ParticlePosition {double x,y,angle;};
inline uint32_t deathSeed(const std::string& path){uint32_t seed=2166136261u;for(auto ch:path){seed^=uint8_t(ch);seed*=16777619u;}return seed;}
inline std::vector<DeathParticle> deathParticles(uint32_t seed,int count,double x,double y,double w,double h,double speed) {
    auto random=[&](){seed^=seed<<13;seed^=seed>>17;seed^=seed<<5;return double(seed&0xffffff)/0x1000000;};
    std::vector<DeathParticle> out;
    for(int i=0;i<count;++i)out.push_back({x+(random()-.5)*w*.7,y+(random()-.5)*h*.65,(random()*2-1)*speed*.6,-speed*(.55+random()*.55),(random()*2-1)*270,random()*360,int(random()*4),.5+random()*.5});
    return out;
}
// Analytic flight, then stop on the ground. Deterministic under seek/replay.
inline ParticlePosition deathPosition(const DeathParticle&p,double seconds,double gravity,double floor) {
    double impact=( -p.vy+std::sqrt(p.vy*p.vy+2*gravity*std::max(0.0,floor-p.y)) )/gravity;
    double t=std::clamp(seconds,0.0,impact);
    return {p.x+p.vx*t,std::min(floor,p.y+p.vy*t+.5*gravity*t*t),p.angle+p.spin*t};
}
}
