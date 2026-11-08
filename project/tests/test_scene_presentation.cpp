#include "dnf/scene_presentation.hpp"
#include "dnf/drop_presentation.hpp"
#include <stdexcept>
namespace dnf {
Json runScenePresentationTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();const auto check=[&](bool okay,const char *name){if(!okay)throw std::runtime_error(name);checks.push_back(name);};
    const auto lorien=prepareScenePresentation(pvf,assets,pvf.script("dungeon/act1/lorien.dgn"),"Lorien");
    const auto town=prepareScenePresentation(pvf,assets,pvf.script("town/elvengard.twn"),"Elvengard");
    const auto sky=prepareScenePresentation(pvf,assets,pvf.script("dungeon/act2/golemtower.dgn"),"Sky Castle");
    check(lorien.image=="map/cutscene/lorien.img"&&lorien.imageSize==std::array<int,2>{800,600}&&lorien.backgroundFrame==-1,
        "Actual Lorien cutscene uses authored frame0 without probing a nonexistent frame1");
    check(lorien.title=="dungeon/act1/title/lorien.ani"&&lorien.titleDurationMs==700,
        "Actual entering title resolves relative to its DGN and retains all700 source milliseconds");
    check(town.image!=lorien.image&&sky.image!=lorien.image&&!town.title.empty()&&!sky.title.empty(),
        "Town, Lorien and Sky Castle select their own source cutscene/title chains");
    check(lorien.diagnostics.empty()&&town.diagnostics.empty()&&sky.diagnostics.empty(),
        "Three actual source preflights decode their title images without diagnostics");
    ScenePresentation transition;transition.begin(lorien,10000);
    check(transition.frame(20000).cutsceneVisible&&transition.frame(20000).blocked,
        "A slow preparation cannot release the scene or finish the loading screen before ready");
    transition.ready(20000);transition.ready(25000);
    check(transition.frame(20000).blackAlpha==0&&transition.frame(20299).cutsceneVisible,
        "First ready owns fade timeline and later notifications cannot restart it");
    check(!transition.frame(20300).cutsceneVisible&&transition.frame(20300).blackAlpha==255,
        "Cutscene reaches full black before the new scene is revealed");
    check(transition.frame(20700).blackAlpha==0&&!transition.frame(20700).blocked&&transition.frame(20700).titleMs==400,
        "Scene reveal completes without waiting for a separate title clip to finish");
    check(!transition.frame(21000).active,"Finite source title retires at its own end instead of looping indefinitely");
    transition.begin(town,100);transition.ready(101);
    check(transition.frame(1099).cutsceneVisible&&transition.frame(1099).blackAlpha==0,
        "Fast loading still leaves source artwork visible for at least1000 milliseconds");
    for(int fps:{30,60,144,240}) {
        ScenePresentation candidate;candidate.begin(lorien,0);candidate.ready(1);
        for(int i=0;i<fps*3;++i)candidate.frame(int64_t(i)*1000/fps);
        check(candidate.frame(1450).blackAlpha==160&&candidate.frame(1450).titleMs==150,
            "Wall-time transition endpoints are unchanged by render cadence or repeated draws");
    }
    transition.cancel();check(!transition.frame(100000).blocked&&!transition.frame(100000).active,
        "Failed scene preparation can cancel presentation without leaving input or simulation blocked");
    const auto coin=prepareGoldDropSprite(pvf,assets);
    check(coin.image=="interface/windowcommon.img"&&coin.frame==299&&coin.diagnostics.empty(),
        "Gold-only rewards obtain the current gold definition's visible coin icon");
    const auto material=prepareDropSprite(assets,pvf.script("stackable/material/tigerskin_charnak.stk"));
    const auto materialPixels=assets.pixels(material.image,material.frame);
    const auto origin=material.drawingOrigin(500,344);
    check(material.image=="item/field_material.img"&&material.frame==0&&material.anchorX==59.5&&material.anchorY==71&&
        origin[0]+materialPixels.x+materialPixels.width/2.0==500&&origin[1]+materialPixels.y+materialPixels.height==344,
        "Actual tiger-skin crop44,49 in120px canvas anchors visible image to the same ground point used for pickup");
    Script source;source.path="diagnostic/missing-field-item.stk";
    source.fields={{"[field image]",Json::array({"interface/windowcommon.img",999999}),0},
                   {"[icon]",Json::array({coin.image,coin.frame}),5}};
    const auto fallback=prepareDropSprite(assets,source);
    check(fallback.image==coin.image&&fallback.frame==coin.frame&&!fallback.diagnostics.empty()&&
        fallback.evidence.at("selected_tag")=="[icon]",
        "An invalid field frame preserves diagnostics while using only the same item's authored icon");
    const auto absent=prepareDropSprite(assets,Script{});
    check(absent.image.empty()&&!absent.diagnostics.empty(),"Missing art remains diagnosed rather than fabricated");
    return {{"status","passed"},{"count",checks.size()},{"checks",checks},
        {"lorien",lorien.evidence},{"elvengard",town.evidence},{"sky",sky.evidence},{"gold",coin.evidence},
        {"scope","Actual current source resources and deterministic user transition policy; frontend comparison pending"}};
}
} // namespace dnf
