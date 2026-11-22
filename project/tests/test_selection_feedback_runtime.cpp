#include "dnf/selection_ui.hpp"
#include "dnf/world_map_ui.hpp"
#include "dnf/target_hud.hpp"
#include <stdexcept>

namespace dnf {
Json runSelectionFeedbackRuntimeTests(Pvf &pvf,Assets &assets,const std::filesystem::path &output) {
    std::filesystem::create_directories(output);
    Json checks=Json::array(),sourceMaps=Json::array();
    auto check=[&](bool okay,const char *what){
        if(!okay)throw std::runtime_error(std::string("Selection feedback render: ")+what);
        checks.push_back(what);
    };
    RegionCatalog catalog(pvf,assets,RegionPreparation::OnDemand);
    SelectionUi ui;ui.bind(pvf,assets);WorldMapUi map;map.bind(pvf,assets);
    Renderer renderer(assets,RendererOptions{"Hidden selection feedback",800,600,false,false,false});
    int maps=0;
    for(const auto &path:pvf.paths("worldmap/",".wdm")) {
        catalog.prepareWorldmap(path);auto model=captureDungeonSelectionModel(pvf,catalog,path);
        if(model.choices.empty())continue;
        ++maps;
        auto state=enterDungeonSelection(model);ui.startDungeonPresentation(state,5000);
        const auto layout=ui.dungeonLayout(model,state.selectedDungeon);
        const auto selected=state.selectedDungeon;
        for(int64_t now:{5000,5150,5300,6150,6300,6450,6600}) {
            renderer.begin();renderer.ui();
            ui.drawDungeon(renderer,model,layout,state,{50,false,1,true},{},now);renderer.present();
        }
        state.hoveredDungeon=model.choices.back().id;
        renderer.begin();renderer.ui();
        ui.drawDungeon(renderer,model,layout,state,{50,false,1,true},{760,510,false},6600);
        check(state.open&&state.selectedDungeon==selected,
            "drawing source intro and hover does not mutate selection or consume entry");
        if(maps==1)renderer.screenshot(output/"dungeon-selection-hover.png");
        renderer.present();
        check(renderer.errors.empty(),"every source WDM has functioning UI image/hover consumers");
        sourceMaps.push_back({{"path",path},{"cards",model.choices.size()},
            {"selection",describeDungeonSelection(model,layout,state)}});
    }
    check(maps>=20,"hidden SDL draws all current nonempty WDMs");
    for(const auto &size:std::vector<std::array<int,2>>{{800,600},{1280,720},{1920,1080}}) {
        renderer.resize(size[0],size[1]);
        for(int town:{1,2,6,11}) {
            renderer.begin();renderer.ui();
            const auto action=map.draw(renderer,town,0,500,200,{},1600);
            check(action.worldmapPath.empty(),"passive full-screen MM render does not synthesize gate input");
            renderer.present();
        }
        check(renderer.errors.empty(),"source MM map, tabs and NPC icons render at each requested resolution");
    }
    renderer.resize(800,600);
    Actor boss;boss.id=1;boss.hp=5000;boss.maxHp=5000;boss.boss=true;
    for(const auto &path:pvf.paths("monster/",".mob")) {
        if(pvf.script(path).values("[face image]").size()>=2){boss.monsterPath=path;break;}
    }
    check(!boss.monsterPath.empty(),"Boss portrait test uses a real current MOB face binding");
    TargetHud target;target.hit(boss,100);renderer.begin();renderer.ui();target.draw(renderer,pvf,200);renderer.present();
    boss.hp=1000;target.hit(boss,300,5000);renderer.begin();renderer.ui();target.draw(renderer,pvf,400);
    renderer.screenshot(output/"boss-layer-source-face.png");renderer.present();
    check(boss.hp==1000&&boss.maxHp==5000,"layered Boss rendering leaves gameplay HP unchanged");
    DungeonRun run;run.width=2;run.height=1;run.current=0;run.rooms.resize(2);
    run.rooms[0].doors=2;run.rooms[0].visited=true;
    run.rooms[1].x=1;run.rooms[1].doors=1;run.rooms[1].boss=true;
    renderer.begin();renderer.ui();drawSourceDungeonMinimap(renderer,run,false,300);renderer.present();
    renderer.begin();renderer.ui();drawSourceDungeonMinimap(renderer,run,true,300);
    renderer.screenshot(output/"dungeon-minimap-expanded.png");renderer.present();
    check(run.current==0&&run.rooms[0].visited,"minimap source-frame consumers do not change room state");
    writeJson(output/"selection-feedback-pre-final.json",{{"checks",checks},{"worldmaps",sourceMaps},
        {"renderer_errors",renderer.errors},{"renderer_unsupported",renderer.unsupported}});
    check(renderer.errors.empty(),"hidden source selection/MM/Boss/minimap renders have no resource errors");
    check(renderer.unsupported.empty(),"hidden source selection/MM/Boss/minimap renders have no unsupported operations");
    return {{"status","passed"},{"count",checks.size()},{"checks",checks},{"maps",maps},
        {"worldmaps",sourceMaps},{"renderer_errors",renderer.errors},{"renderer_unsupported",renderer.unsupported},
        {"scope","hidden SDL image/consumer checks; source absence diagnostics retained; frontend and original comparison require the user"}};
}
} // namespace dnf
