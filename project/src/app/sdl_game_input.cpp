#include "dnf/sdl_game_input.hpp"
#include "dnf/combat.hpp"
#include "dnf/sdl_text_input.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>

namespace dnf {
bool dispatchSdlGameInput(World &world,const SDL_Event &event,const SdlGameInputContext &context) {
    if(!context.inGame || context.businessBlocked ||
       (event.type!=SDL_KEYDOWN&&event.type!=SDL_KEYUP) || event.key.repeat)return false;
    const auto window=sdlInputEventWindow(event);
    if(window&&window!=context.mainWindowId)return false;
    int key=-1;const auto symbol=event.key.keysym.sym;
    switch(symbol) {
    case SDLK_LEFT:key=0;break;case SDLK_RIGHT:key=1;break;
    case SDLK_UP:key=2;break;case SDLK_DOWN:key=3;break;
    case SDLK_x:key=4;break;case SDLK_c:key=5;break;
    case SDLK_z:key=6;break;case SDLK_SPACE:key=7;break;
    default:break;
    }
    const SDL_Keycode hot[]={SDLK_a,SDLK_s,SDLK_d,SDLK_f,SDLK_g,SDLK_h,
        SDLK_q,SDLK_w,SDLK_e,SDLK_r,SDLK_t,SDLK_y,SDLK_SPACE};
    for(int i=0;i<13;++i)
        if(symbol==hot[i]&&(symbol!=SDLK_SPACE||world.bindings[12]!=12))key=20+i;
    const bool modal=context.modal||(context.mapOpen&&key>3);
    if(key<0 || ((context.paused||modal)&&event.type!=SDL_KEYUP))return false;
    if(context.submittedNs<0||context.frameNs<0||
       context.frameNs>std::numeric_limits<int64_t>::max()-context.submittedNs)
        throw std::overflow_error("Input timeline overflow");
    const auto inputNs=std::max<int64_t>(0,context.submittedNs+context.frameNs-
        int64_t(Uint32(context.wallMs-event.key.timestamp))*1000000);
    world.enqueue({inputNs,key,event.type==SDL_KEYDOWN});
    return true;
}
void suppressBlockedGameClicks(bool blocked,bool &click,bool &itemActivate) noexcept {
    if(blocked){click=false;itemActivate=false;}
}
} // namespace dnf
