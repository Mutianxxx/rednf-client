#pragma once
#include "renderer.hpp"
#include "hud_source.hpp"

namespace dnf {
// PC HUD at the 800 x 600 UI reference size. Source pixel origins stay in
// Assets; these anchors come from the local PC reference, not MAP coordinates.
class Hud {
    struct Icon {
        std::string path;
        int frame = 0;
        int width = 28, height = 28;
    };
    struct SkillIcons {
        Icon normal, disabled;
    };
    Pvf &pvf_;
    Assets &assets_;
    HudSourceLayout source_;
    int menuWidth_ = 0, menuHeight_ = 0;
    int shopWidth_ = 0, shopHeight_ = 0;
    std::array<double, 4> disabledBounds_{};
    std::unordered_map<std::string, SkillIcons> icons_;
    const SkillIcons &icons(const std::string &source);

  public:
    Hud(Pvf &pvf, Assets &assets);
    bool systemMenuContains(int x, int y) const;
    Json sourceReport() const;
    // Call after Renderer::ui(). Mouse coordinates must use Renderer::mouse().
    // Returns a click on the enabled system-menu button. Other source HUD
    // buttons remain visibly disabled until their corresponding UI is ready.
    bool draw(Renderer &render, const World &world, int mx, int my, bool click);
};
} // namespace dnf
