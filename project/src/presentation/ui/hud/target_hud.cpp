#include "dnf/target_hud.hpp"
#include "dnf/renderer.hpp"

namespace dnf {
void TargetHud::draw(Renderer &r, Pvf &pvf, int64_t now,int referenceMaximumHp) {
    double opacity = state.opacity(now);
    if (opacity <= 0 || monsterPath_.empty()) return;
    // 40JP sub_4684F0 loads name/portrait/type on observation target changes.
    // Keep immutable MOB data outside the per-frame PVF parsing path.
    if(cachedPath_!=monsterPath_) {
        const auto model=pvf.script(monsterPath_);
        cachedName_=model.text("[name]","怪物");cachedFace_.clear();cachedCategory_.clear();
        const auto face=model.values("[face image]");
        if(face.size()>=2&&face[0].is_string()&&face[1].is_number_integer()) {
            cachedFace_=face[0].get<std::string>();cachedFaceFrame_=face[1].get<int>();
        }
        for(const auto &value:model.values("[category]"))if(value.is_string()) {
            const auto tag=normalize(value.get<std::string>());
            for(const auto &entry:std::array<std::pair<const char *,const char *>,9>{{
                {"[human]","人型"},{"[beast]","野兽"},{"[undead]","不死"},
                {"[machine]","机械"},{"[plant]","植物"},{"[insect]","昆虫"},
                {"[devil]","恶魔"},{"[dragon]","龙族"},{"[spirit]","精灵"}}})
                if(tag==entry.first&&cachedCategory_.empty())cachedCategory_=entry.second;
        }
        cachedPath_=monsterPath_;
    }
    if(boss_) {
        // Current-source backing and six fill colors, with requested taller geometry.
        // Screen anchor and trail timing are explicit reconstructed HUD policy.
        constexpr const char *boss="interface/newstyle/windows/monster_hp/bossmonsterhp_cn.img";
        constexpr float bx=BossHealthGeometry::x,by=BossHealthGeometry::y,
            bw=BossHealthGeometry::width,bh=BossHealthGeometry::height;
        const uint8_t alpha=uint8_t(std::lround(255*opacity));
        r.text("BOSS  "+cachedName_,bx,by-21,15,{255,156,99,alpha});
        r.imageRegion(boss,0,{0,0,545,2},bx,by,545,2,{255,255,255,alpha});
        r.imageRegion(boss,0,{0,2,545,4},bx,by+2,545,bh,{255,255,255,alpha});
        r.imageRegion(boss,0,{0,6,545,2},bx,by+2+bh,545,2,{255,255,255,alpha});
        if(!cachedFace_.empty())
            r.sprite(cachedFace_,cachedFaceFrame_,bx-32,by,1,1,0,alpha,0,false);
        constexpr const char *colors="interface/newstyle/windows/monster_hp/monster_hp.img";
        const auto layers=BossHealthLayerView::split(state.hp,state.maximum);
        const float current=float(layers.ratio*bw);
        if(layers.remaining>1)r.imageRegion(colors,layers.behindFrame,{0,0,597,9},bx+3,by+2,bw,bh,{255,255,255,alpha});
        if(current>0)r.imageRegion(colors,layers.frame,{0,0,597,9},bx+3,by+2,current,bh,{255,255,255,alpha});
        // Trail stays within this current layer; crossing a layer does not redraw
        // old colors over the new HP state or make a full layer look empty.
        const double oldHp=state.trail(now)*state.maximum;
        const double layerBase=double(std::max(0,layers.remaining-1))*layers.capacity;
        const float trail=float(std::clamp((oldHp-layerBase)/layers.capacity,0.0,1.0)*bw);
        if(trail>current)r.imageRegion(colors,layers.frame,{0,0,597,9},bx+3+current,by+2,trail-current,bh,{120,120,120,uint8_t(alpha*0.65)});
        r.text("×"+std::to_string(layers.remaining),bx+bw+12,by+6,14,{244,223,191,alpha});
        r.text(std::to_string(state.hp)+" / "+std::to_string(state.maximum),bx+222,by+bh+6,11,{244,223,191,alpha});
        return;
    }
    constexpr const char *bar = "interface/newstyle/windows/monster_hp/monster_hp.img";
    // Original screenshot (1000x750) normalized to800x600: portrait at(4,98),
    // compact outer width140. Preserve corner widths while resizing the strip.
    constexpr float x = 4, y = 98;
    // 40JP sub_4684F0: 300 * target max HP / reference max HP, cap 475.
    // Preserve the existing 1031 panel anchor/corners and a readable 108px
    // minimum fill. The minimum is a presentation policy for the wider art.
    const float fillWidth=referenceMaximumHp>0?
        float(std::clamp(int64_t(300)*state.maximum/referenceMaximumHp,int64_t(108),int64_t(475))):108;
    const float width=fillWidth+32;
    uint8_t alpha = uint8_t(std::lround(255 * opacity));
    SDL_Color white{255, 255, 255, alpha};
    r.imageRegion(bar, 1, {0, 0, 28, 32}, x, y, 28, 32, white);
    r.imageRegion(bar, 1, {28, 0, 1, 32}, x + 28, y, width - 30, 32, white);
    r.imageRegion(bar, 1, {624, 0, 2, 32}, x + width - 2, y, 2, 32, white);
    if (!cachedFace_.empty())
        r.sprite(cachedFace_, cachedFaceFrame_, x + 1, y + 1,
                 1, 1, 0, alpha, 0, false);
    constexpr float fillX = x + 30, fillY = y + 16;
    // Source red/orange fill; dark lost-health segment is independently timed.
    int fillFrame = boss_ ? 3 : 2;
    float current = float(state.ratio() * fillWidth), trail = float(state.trail(now) * fillWidth);
    if (trail > current)
        r.imageRegion(bar, fillFrame, {0, 0, 597, 9}, fillX + current, fillY,
                      trail - current, 9, {100, 100, 100, uint8_t(alpha * 0.65)});
    if (current > 0)
        r.imageRegion(bar, fillFrame, {0, 0, 597, 9}, fillX, fillY, current, 9, white);
    r.text(cachedCategory_, x + 32, y + 1, 10, {225, 137, 67, alpha});
    r.text(cachedName_, x + 35+r.textWidth(cachedCategory_,10), y + 1, 11, {244, 238, 218, alpha});
}
} // namespace dnf
