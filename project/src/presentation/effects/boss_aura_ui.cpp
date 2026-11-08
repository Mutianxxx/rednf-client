#include "dnf/boss_aura_ui.hpp"
namespace dnf {
void drawSourceBossAura(Renderer &r,const Actor &actor,int64_t ms,double interpolation,
                        double cameraX,double cameraY) {
    if(!actor.boss||actor.life!=ActorLife::Alive||actor.dead)return;
    const auto a=std::clamp(interpolation,0.0,1.0);
    const double x=actor.px+(actor.x-actor.px)*a-cameraX;
    const double groundY=actor.py+(actor.y-actor.py)*a-cameraY;
    r.animation("common/etc/animation/aura/bossauramaster.ani",ms,x,groundY,1,true);
}
}
