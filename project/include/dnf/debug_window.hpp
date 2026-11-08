#pragma once
#include "debug.hpp"
#include <SDL.h>
#include <memory>

namespace dnf {
class Renderer;
// Second SDL window, main-thread only. Owns a separate Renderer/texture cache.
// It reads confirmed snapshots and submits commands; never accesses World.
class DebugWindow {
    struct Control { SDL_Rect rect; DebugCommandKind kind; Json payload; bool enabled; bool selectIdentity = false; };
    std::unique_ptr<Renderer> renderer_;
    DebugService &service_;
    std::vector<Control> controls_;
    DebugTarget displayedTarget_;
    std::optional<DebugResult> submitted_;
    Json draftIdentity_;
    bool visible_ = false, dirty_ = true;
    int mouseX_ = -100, mouseY_ = -100;
    uint64_t nextDraw_ = 0;
    void submit(const Control&);
  public:
    DebugWindow(Assets&, DebugService&);
    ~DebugWindow();
    DebugWindow(const DebugWindow&) = delete;
    DebugWindow &operator=(const DebugWindow&) = delete;
    uint32_t windowId() const;
    bool visible() const { return visible_; }
    bool hasFocus() const;
    void show();
    void hide();
    // Returns true only for this window's events. Main-window F9 is routed
    // by the application to show(); no second-window key enters combat.
    bool handleEvent(const SDL_Event&);
    void draw(const DebugSnapshot&, uint64_t uiTimeMs);
};
} // namespace dnf
