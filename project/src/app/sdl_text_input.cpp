#include "dnf/sdl_text_input.hpp"
#include <algorithm>
namespace dnf {
TextInputKey sdlTextInputKey(SDL_Keycode key) {
    switch(key) {
    case SDLK_RETURN:case SDLK_KP_ENTER:return TextInputKey::Return;
    case SDLK_ESCAPE:return TextInputKey::Escape;case SDLK_BACKSPACE:return TextInputKey::Backspace;
    case SDLK_DELETE:return TextInputKey::Delete;case SDLK_LEFT:return TextInputKey::Left;
    case SDLK_RIGHT:return TextInputKey::Right;case SDLK_HOME:return TextInputKey::Home;
    case SDLK_END:return TextInputKey::End;case SDLK_UP:return TextInputKey::Up;
    case SDLK_DOWN:return TextInputKey::Down;case SDLK_PAGEUP:return TextInputKey::PageUp;
    case SDLK_PAGEDOWN:return TextInputKey::PageDown;case SDLK_SPACE:return TextInputKey::Space;
    default:return TextInputKey::Other;
    }
}
Uint32 sdlInputEventWindow(const SDL_Event &event) {
    if(event.type==SDL_WINDOWEVENT)return event.window.windowID;
    if(event.type==SDL_KEYDOWN||event.type==SDL_KEYUP)return event.key.windowID;
    if(event.type==SDL_TEXTINPUT)return event.text.windowID;
    if(event.type==SDL_TEXTEDITING)return event.edit.windowID;
    if(event.type==SDL_TEXTEDITING_EXT)return event.editExt.windowID;
    if(event.type==SDL_MOUSEMOTION)return event.motion.windowID;
    if(event.type==SDL_MOUSEBUTTONDOWN||event.type==SDL_MOUSEBUTTONUP)return event.button.windowID;
    if(event.type==SDL_MOUSEWHEEL)return event.wheel.windowID;
    return 0;
}
SdlTextInputBatch::~SdlTextInputBatch(){clear();}
void SdlTextInputBatch::clear() noexcept {
    for(auto &event:events_)if(event.type==SDL_TEXTEDITING_EXT) {
        SDL_free(event.editExt.text);event.editExt.text=nullptr;
    }
    events_.clear();
}
void SdlTextInputBatch::collect() {
    clear();SDL_Event event;
    while(SDL_PollEvent(&event)) {
        try{events_.push_back(event);}catch(...) {
            if(event.type==SDL_TEXTEDITING_EXT)SDL_free(event.editExt.text);
            throw;
        }
    }
}
bool SdlTextInputBatch::hasTextTraffic(Uint32 windowId) const {
    return std::any_of(events_.begin(),events_.end(),[&](const SDL_Event &event) {
        return sdlInputEventWindow(event)==windowId&&(event.type==SDL_TEXTINPUT||
            event.type==SDL_TEXTEDITING||event.type==SDL_TEXTEDITING_EXT);
    });
}
} // namespace dnf
