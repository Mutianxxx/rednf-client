#include "dnf/scene_presentation.hpp"
#include "dnf/renderer.hpp"
namespace dnf {
void drawScenePresentation(Renderer &r,const ScenePresentation &state,int64_t wallMs) {
    const auto frame=state.frame(wallMs);if(!frame.active)return;
    const auto &plan=state.plan();r.ui();
    if(frame.cutsceneVisible) {
        r.rect(0,0,800,600,{0,0,0,255});
        const auto draw=[&](int index,const std::array<int,2> &size) {
            if(size[0]<=0||size[1]<=0)return;
            // Retain source aspect ratio; cover the viewport to avoid black
            // edges at other window ratios. This is a presentation policy.
            const auto scale=std::max(800.0/size[0],600.0/size[1]);
            r.sprite(plan.image,index,(800-size[0]*scale)/2,(600-size[1]*scale)/2,1,scale);
        };
        if(!plan.image.empty()) {
            if(plan.backgroundFrame>=0)draw(plan.backgroundFrame,plan.backgroundSize);
            draw(plan.imageFrame,plan.imageSize);
        }
        r.text("正在进入 "+plan.name,22,560,16,{255,255,255,255});
        if(!plan.diagnostics.empty())r.text("部分入场资源未加载，详情见 scene-presentation.json",22,582,12,{255,210,130,255});
    }
    if(frame.blackAlpha)r.rect(0,0,800,600,{0,0,0,frame.blackAlpha});
    if(frame.titleMs>=0&&!plan.title.empty())
        // The source ANI already carries exact title glyph frames, offsets,
        // 50ms delays and transparency. Do not replace them with a host font.
        r.animation(plan.title,double(frame.titleMs),400,170,1,false);
}
} // namespace dnf
