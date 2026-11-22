#pragma once
#include "text_input.hpp"
#include <SDL.h>
#include <vector>
namespace dnf {
TextInputKey sdlTextInputKey(SDL_Keycode);
Uint32 sdlInputEventWindow(const SDL_Event &);
// Owns TEXTEDITING_EXT text transferred by SDL_PollEvent. The borrowed events
// remain valid until clear/destruction. Never copy event owners to a new batch.
class SdlTextInputBatch {
    std::vector<SDL_Event> events_;
  public:
    SdlTextInputBatch()=default;
    SdlTextInputBatch(const SdlTextInputBatch &)=delete;
    SdlTextInputBatch &operator=(const SdlTextInputBatch &)=delete;
    ~SdlTextInputBatch();
    void collect();
    void clear() noexcept;
    const std::vector<SDL_Event> &events() const { return events_; }
    bool hasTextTraffic(Uint32 windowId) const;
};
} // namespace dnf
