#pragma once
#include <SDL.h>
#include <cstdint>

namespace dnf {
class World;
// Application-owned state, sampled after window/text/UI ownership routing.
// This adapter does not own focus, IME, debug commands, modal toggles or saves.
struct SdlGameInputContext {
    Uint32 mainWindowId = 0, wallMs = 0;
    bool inGame = false, businessBlocked = false, paused = false;
    bool modal = false, mapOpen = false;
    int64_t submittedNs = 0, frameNs = 0;
};
// Maps the existing physical keys and enqueues through World's real command
// queue. Blocked rejects down AND up before allocation/sequence consumption;
// ordinary modal/paused KEYUP remains accepted for held-input cleanup.
bool dispatchSdlGameInput(World &, const SDL_Event &, const SdlGameInputContext &);
// Main samples retry flags first. This only clears ordinary UI actions and
// is called again after ticks/reward capture can create a new pending save.
void suppressBlockedGameClicks(bool blocked, bool &click, bool &itemActivate) noexcept;
} // namespace dnf
