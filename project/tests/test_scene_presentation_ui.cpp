#include "dnf/scene_presentation.hpp"
#include "dnf/drop_presentation.hpp"
#include "dnf/region_ui.hpp"
#include <stdexcept>
namespace dnf {
Json runScenePresentationUiTests(Pvf &pvf,Assets &assets,const std::filesystem::path &output) {
    Json checks=Json::array();const auto check=[&](bool okay,const char *name){if(!okay)throw std::runtime_error(name);checks.push_back(name);};
    Renderer renderer(assets,RendererOptions{"Hidden scene/pickup UI",800,600,false,false,false});
    const auto pixels=[&] {Bytes data(800*600*4);if(SDL_RenderReadPixels(renderer.raw(),nullptr,SDL_PIXELFORMAT_RGBA32,data.data(),800*4))
        throw std::runtime_error(SDL_GetError());return data;};
    const auto plan=prepareScenePresentation(pvf,assets,pvf.script("dungeon/act1/lorien.dgn"),"Lorien");
    ScenePresentation transition;transition.begin(plan,0);transition.ready(1);
    renderer.begin();renderer.ui();renderer.sprite(plan.image,plan.imageFrame,0,0);
    renderer.text("正在进入 Lorien",22,560,16,{255,255,255,255});const auto source=pixels();
    renderer.begin();drawScenePresentation(renderer,transition,900);check(pixels()==source,
        "Real hidden renderer loading frame matches the source artwork without unrelated game UI");
    renderer.screenshot(output/"loading-lorien.png");
    renderer.begin();renderer.ui();renderer.rect(0,0,800,600,{110,140,170,255});drawScenePresentation(renderer,transition,1250);
    renderer.screenshot(output/"loading-to-black.png");
    renderer.begin();renderer.ui();renderer.rect(0,0,800,600,{110,140,170,255});drawScenePresentation(renderer,transition,1550);
    renderer.screenshot(output/"scene-reveal-and-source-title.png");
    check(renderer.errors.empty(),"Actual source title ANI and cutscene draw without renderer errors");
    const auto gold=prepareGoldDropSprite(pvf,assets);renderer.begin();renderer.ui();const auto empty=pixels();
    const auto goldOrigin=gold.drawingOrigin(400,300);
    renderer.sprite(gold.image,gold.frame,goldOrigin[0],goldOrigin[1]);check(pixels()!=empty,"Actual gold reward image contributes visible pixels");
    renderer.screenshot(output/"gold-drop-source-icon.png");
    const auto material=prepareDropSprite(assets,pvf.script("stackable/material/tigerskin_charnak.stk"));
    const auto materialOrigin=material.drawingOrigin(400,300);
    renderer.begin();renderer.ui();const auto background=pixels();
    renderer.sprite(material.image,material.frame,materialOrigin[0],materialOrigin[1]);const auto drawn=pixels();
    int minX=800,maxX=-1,minY=600,maxY=-1;
    for(int y=0;y<600;++y)for(int x=0;x<800;++x) {
        const size_t offset=size_t(y*800+x)*4;
        if(!std::equal(drawn.begin()+offset,drawn.begin()+offset+4,background.begin()+offset)) {
            minX=std::min(minX,x);maxX=std::max(maxX,x);minY=std::min(minY,y);maxY=std::max(maxY,y);
        }
    }
    check(maxX>=minX&&std::abs((minX+maxX)/2.0-400)<=1&&maxY<=300&&minY>=277,
        "Actual material visible pixels are centered over ledger ground instead of shifted44,49 away from pickup range");
    renderer.screenshot(output/"material-drop-aligned-to-ground.png");
    RegionCatalog catalog(pvf,assets);Progression progress(catalog);progress.initialize(4);
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progress);
    const auto look=world.characterAppearance();RegionSession session;
    RegionUi keyboard,mouse;keyboard.bindSources(pvf);mouse.bindSources(pvf);
    const auto draw=[&](RegionUi &ui,int x=-1,int y=-1,bool click=false) {
        renderer.begin();renderer.ui();ui.draw(renderer,world,progress,session,look,x,y,click);
    };
    keyboard.openNpc(1,progress);mouse.openNpc(1,progress);
    keyboard.panel=mouse.panel=RegionPanel::Npc;draw(keyboard);draw(mouse);
    const auto before=progress.state;const auto ledger=world.skillState().snapshot(world.nowMs());
    check(keyboard.requestDialogueAdvance(),"X continue is accepted only by an actual NPC dialogue");
    draw(keyboard);draw(mouse,600,455,true);
    check(keyboard.snapshot()==mouse.snapshot()&&keyboard.panel==mouse.panel,
        "Clicking dialogue and requesting X use the same page/segment/end transition");
    check(progress.state==before&&world.skillState().snapshot(world.nowMs())==ledger,
        "Dialogue continue never accepts a quest, purchases, changes learning or invokes combat");
    keyboard.close();check(!keyboard.requestDialogueAdvance(),"Closed dialogue cannot queue a stale X continuation");
    return {{"status","passed"},{"count",checks.size()},{"checks",checks},{"renderer_errors",renderer.errors},
        {"scope","Hidden real SDL rendering and dialogue input consumers; native/frontend appearance pending user"}};
}
} // namespace dnf
