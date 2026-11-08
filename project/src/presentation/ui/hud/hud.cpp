#include "dnf/hud.hpp"
#include "dnf/experimental_character.hpp"
#include <cmath>

namespace dnf {
namespace {
constexpr const char *hudImage = "interface2/hud/hud.img";
constexpr int hudY = 508;
constexpr int orbY = 524;
constexpr int slotSize = 28;
// The source bar paints the slot frame; icons keep a 2px margin so it stays visible.
constexpr int slotInset = 2;
constexpr int slotInner = slotSize - slotInset * 2;

bool inside(int mx, int my, double x, double y, double w, double h) {
    return mx >= x && mx < x + w && my >= y && my < y + h;
}

// These labels are ASCII, so centering does not need a CJK glyph estimate.
void centeredText(Renderer &render, const std::string &s, float cx, float y, int size,
                  SDL_Color color) {
    float x = cx - float(s.size()) * size * 0.25f;
    render.text(s, x + 1, y + 1, size, {0, 0, 0, 255});
    render.text(s, x, y, size, color);
}

// Keep the caller's clip intact; the bottom-anchored source liquid is revealed
// by a horizontal liquid surface, with the empty source orb visible above it.
// The source orbs print a percentage, not current/maximum.
void drawOrb(Renderer &render, int frame, int x, int value, int maximum, SDL_Color color) {
    double ratio = std::clamp(double(value) / std::max(1, maximum), 0.0, 1.0);
    int filled = int(std::lround(56 * ratio));
    if (filled > 0) {
        SDL_Renderer *raw = render.raw();
        SDL_Rect previous{};
        bool clipped = SDL_RenderIsClipEnabled(raw) == SDL_TRUE;
        if (clipped) SDL_RenderGetClipRect(raw, &previous);
        SDL_Rect liquid{x, orbY + 56 - filled, 56, filled};
        if (!clipped || SDL_IntersectRect(&previous, &liquid, &liquid)) {
            SDL_RenderSetClipRect(raw, &liquid);
            render.sprite(hudImage, frame, x, orbY, 1, 1, 0, 255, 0, false);
        }
        SDL_RenderSetClipRect(raw, clipped ? &previous : nullptr);
    }
    const int percent = maximum > 0 ? int(std::lround(100.0 * value / maximum)) : 0;
    centeredText(render, std::to_string(percent) + "%", float(x + 28), float(orbY + 24), 11, color);
}
} // namespace

Hud::Hud(Pvf &pvf, Assets &assets) : pvf_(pvf), assets_(assets),
    source_(readHudSourceLayout(pvf.script("ui/hud/hud.ui"))) {
    const auto &menu = source_.require("main_menu", "[button]", 1, 4);
    const auto pixels = assets_.pixels(menu.strings[0], menu.integers[0]);
    menuWidth_ = pixels.logicalWidth; menuHeight_ = pixels.logicalHeight;
    if (menuWidth_ <= 0 || menuHeight_ <= 0) throw std::runtime_error("HUD menu has no source hit extent");
    const auto &shop = source_.require("cerashop_button", "[button]", 1, 4);
    const auto shopPixels = assets_.pixels(shop.strings[0], shop.integers[3]);
    shopWidth_ = shopPixels.logicalWidth; shopHeight_ = shopPixels.logicalHeight;
    source_.require("skill2_button", "[button]", 1, 4);
    bool first = true;
    for (const auto *name : {"myinfo_button", "inventory_button", "quest_button", "skill_button", "auction_button"}) {
        const auto &control = source_.require(name, "[highlight button]", 1, 5);
        const auto metrics = assets_.pixels(control.strings[0], control.integers[0]);
        auto &bounds = disabledBounds_;
        if (first) { bounds = {control.x, control.y, control.x, control.y}; first = false; }
        bounds[0] = std::min(bounds[0], control.x); bounds[1] = std::min(bounds[1], control.y);
        bounds[2] = std::max(bounds[2], control.x + metrics.logicalWidth);
        bounds[3] = std::max(bounds[3], control.y + metrics.logicalHeight);
    }
}

bool Hud::systemMenuContains(int x, int y) const {
    const auto &menu = source_.require("main_menu", "[button]", 1, 4);
    return inside(x, y, menu.x, hudY + menu.y, menuWidth_, menuHeight_);
}
Json Hud::sourceReport() const {
    auto result = source_.snapshot();
    result["adapter"] = {{"id", "existing-1031-hud-buttons-v1"},
        {"classification", "source-position-and-parameters; inferred-existing-state-order"},
        {"origin_y", hudY}, {"menu_logical_extent", {menuWidth_, menuHeight_}},
        {"ordinary_button_states", {"normal", "hover", "pressed", "disabled"}},
        {"highlight_consumed_integer_indices", {0}},
        {"unimplemented", {"highlight extra parameters", "common action execution", "aura and new-skill animation", "generic UI events"}}};
    return result;
}

const Hud::SkillIcons &Hud::icons(const std::string &source) {
    auto found = icons_.find(source);
    if (found != icons_.end()) return found->second;
    SkillIcons result;
    auto values = pvf_.script(source).values("[icon]");
    auto readIcon = [&](size_t index) {
        Icon icon;
        if (index + 1 >= values.size() || !values[index].is_string() ||
            !values[index + 1].is_number_integer()) return icon;
        icon.path = values[index].get<std::string>();
        icon.frame = values[index + 1].get<int>();
        try {
            auto pixels = assets_.pixels(icon.path, icon.frame);
            icon.width = std::max(1, pixels.logicalWidth);
            icon.height = std::max(1, pixels.logicalHeight);
        } catch (const std::exception &) {
            // Draw via Renderer anyway so its existing resource-error report
            // owns the failure, instead of making optional HUD metrics fatal.
        }
        return icon;
    };
    result.normal = readIcon(0);
    result.disabled = values.size() >= 4 ? readIcon(2) : result.normal;
    return icons_.emplace(source, std::move(result)).first->second;
}

bool Hud::draw(Renderer &render, const World &world, int mx, int my, bool click) {
    // Frame 0 has crop (0,1), logical size 800x92. Respecting the crop places
    // its visible top at 509, and its bottom at the 600px reference boundary.
    render.sprite(hudImage, 0, 0, hudY);
    drawOrb(render, 1, 13, world.player.hp, world.player.maxHp, {238, 152, 54, 255});
    drawOrb(render, 2, 732, world.player.mp, world.player.maxMp, {208, 236, 255, 255});
    // Source level plate sits under the health orb, not at the frame corner.
    render.text("Lv." + std::to_string(world.characterLevel), 24, 581, 12,
                {240, 206, 120, 255});
    // Source SP readout: cyan number in the plate to the right of the SP glyph.
    // A character without a learning ledger has no budget to show.
    if (world.hasLearningLedger())
        try {
            render.text(std::to_string(world.skillLearningBudget(false, world.characterLevel).remainingSp),
                        754, 585, 13, {120, 220, 255, 255});
        } catch (const std::exception &) {
            // HUD never owns learning state; a missing budget stays blank.
        }

    // Source middle buttons: preserve the source shapes and positions. Their
    // original screens are outside this demo; the system menu is enabled.
    for (const auto *name : {"myinfo_button", "inventory_button", "quest_button", "skill_button", "auction_button"}) {
        const auto &control = source_.require(name, "[highlight button]", 1, 5);
        // Only the first highlight parameter is consumed. The remaining four
        // are retained; they are not interpreted as ordinary button states.
        render.sprite(control.strings[0], control.integers[0], control.x, hudY + control.y,
                      1, 1, 0, 255, 0, false, 0, {115, 115, 115, 255});
    }
    const auto &menu = source_.require("main_menu", "[button]", 1, 4);
    const bool menuHover = systemMenuContains(mx, my);
    // State order is the existing named 1031 HUD adapter, supported by its
    // source images/reference. This does not assert a generic native UI ABI.
    render.sprite(menu.strings[0], menu.integers[menuHover ? (click ? 2 : 1) : 0],
                  menu.x, hudY + menu.y, 1, 1, 0, 255, 0, false);
    const auto &shop = source_.require("cerashop_button", "[button]", 1, 4);
    render.sprite(shop.strings[0], shop.integers[3], shop.x, hudY + shop.y, 1, 1, 0, 255, 0, false);
    const auto &toggle = source_.require("skill2_button", "[button]", 1, 4);
    render.sprite(toggle.strings[0], toggle.integers[3], toggle.x, hudY + toggle.y, 1, 1, 0, 255, 0, false);

    static constexpr const char *keys[] = {
        "A", "S", "D", "F", "G", "H", "Q", "W", "E", "R", "T", "Y", "Space"};
    for (int slot = 0; slot < int(world.bindings.size()); ++slot) {
        bool upper = slot >= 6;
        int column = upper ? slot - 6 : slot;
        // The reference has six slots per row. Keep all twelve source anchors;
        // the thirteenth binding is a separate demo extension to their left.
        int x = slot == 12 ? 488 : 538 + column * 30;
        int y = upper ? 519 : 558;
        if (upper)
            render.sprite("interface/exskillquickslot.img", 0, x, y, 1, 1, 0, 255, 0, false);
        if(const auto *runtime=world.experimentalRuntime()) {
            const auto key=runtime->configuration().slots()[size_t(slot)];
            if(key) {
                const auto &plan=runtime->plan();const auto found=plan.skills.find(*key);
                if(found!=plan.skills.end()) {
                    const auto &pair=icons(found->second.source.memberPath);
                    const bool configured=runtime->configuration().binding(*key)!=nullptr;
                    const auto &icon=configured?pair.normal:pair.disabled;
                    if(!icon.path.empty()) {
                        // The source bar already paints each slot's recess and
                        // border; a full-size icon hid it. Inset every icon so
                        // the 28x28 slot frame stays visible, as in the source UI.
                        const double scale=std::min(double(slotInner)/icon.width,double(slotInner)/icon.height);
                        render.sprite(icon.path,icon.frame,x+slotInset+(slotInner-icon.width*scale)/2,
                            y+slotInset+(slotInner-icon.height*scale)/2,1,scale);
                    }
                    const auto cd=runtime->remainingCooldown(*key,world.nowMs());
                    if(cd>0) {
                        render.rect(float(x),float(y),slotSize,slotSize,{0,0,0,165});
                        centeredText(render,std::to_string((cd+999)/1000),float(x+14),float(y+5),15,{255,244,214,255});
                    }
                    if(const auto *binding=runtime->configuration().binding(*key))
                        render.text("Lv."+std::to_string(binding->level),float(x+3),float(y+1),8,
                                    {246,196,96,255});
                }
            }
            // Source key letters sit in the slot's lower-right corner in the
            // reference HUD, not over the icon's lower-left.
            const int keySize = slot == 12 ? 8 : 10;
            const int keyWidth = int(std::strlen(keys[slot])) * keySize / 2;
            const float keyX = float(x + slotSize - keyWidth - 2), keyY = float(y + slotSize - keySize - 2);
            render.text(keys[slot], keyX + 1, keyY + 1, keySize, {0, 0, 0, 255});
            render.text(keys[slot], keyX, keyY, keySize, {232, 92, 70, 255});
            continue;
        }
        int index = world.bindings[slot];
        if (index < 0 || index >= int(world.skills.size())) continue;
        const auto &skill = world.skills[index];
        const auto &pair = icons(skill.source);
        const auto consumeMp = world.skillCosts(index).consumeMp();
        const auto &icon = !consumeMp || world.player.mp < *consumeMp ? pair.disabled : pair.normal;
        if (!icon.path.empty()) {
            double scale = std::min(double(slotInner) / icon.width, double(slotInner) / icon.height);
            // Source icons are currently 28x28; logical-size fitting keeps a
            // future cropped icon's original origin rather than stretching it.
            render.sprite(icon.path, icon.frame, x + slotInset + (slotInner - icon.width * scale) / 2,
                          y + slotInset + (slotInner - icon.height * scale) / 2, 1, scale);
        }
        int cd = world.remainingCd(index);
        if (cd > 0) {
            render.rect(float(x), float(y), slotSize, slotSize, {0, 0, 0, 165});
            centeredText(render, std::to_string((cd + 999) / 1000), float(x + 14),
                         float(y + 5), 15, {255, 244, 214, 255});
        }
        render.text("Lv." + std::to_string(skill.level), float(x + 3), float(y + 1), 8,
                    {246, 196, 96, 255});
        int keySize = slot == 12 ? 8 : 10;
        int keyWidth = int(std::strlen(keys[slot])) * keySize / 2;
        float keyX = float(x + slotSize - keyWidth - 2), keyY = float(y + slotSize - keySize - 2);
        render.text(keys[slot], keyX + 1, keyY + 1, keySize, {0, 0, 0, 255});
        render.text(keys[slot], keyX, keyY, keySize, {232, 92, 70, 255});
    }
    const auto &bounds = disabledBounds_;
    if (inside(mx, my, bounds[0], hudY + bounds[1], bounds[2] - bounds[0], bounds[3] - bounds[1]) ||
        inside(mx, my, shop.x, hudY + shop.y, shopWidth_, shopHeight_)) {
        render.rect(339, 531, 178, 23, {15, 18, 23, 235});
        render.text("该功能暂未开放", 351, 534, 13, {192, 187, 173, 255});
    }
    return click && menuHover;
}
} // namespace dnf
