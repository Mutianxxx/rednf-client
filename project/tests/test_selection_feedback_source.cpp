#include "dnf/selection_ui.hpp"
#include "dnf/world_map_ui.hpp"
#include "dnf/target_hud.hpp"
#include <climits>
#include <cmath>
#include <stdexcept>

namespace dnf {
Json runSelectionFeedbackSourceTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    auto check=[&](bool okay,const char *what){
        if(!okay)throw std::runtime_error(std::string("Selection feedback source: ")+what);
        checks.push_back(what);
    };
    RegionCatalog catalog(pvf,assets,RegionPreparation::OnDemand);
    SelectionUi ui;ui.bind(pvf,assets);
    DungeonSelectionState timing;ui.startDungeonPresentation(timing,5000);
    check(timing.openedWallMs==5000&&timing.cardsVisibleAfterMs==1300,
        "current source banner action consumes wall time and its source reveal delay");
    for(const auto &key:std::vector<std::array<int64_t,3>>{
        {0,0,0},{150,128,0},{300,255,0},{999,255,0},{1150,128,0},
        {1300,0,0},{1450,0,128},{1600,0,255}}) {
        const auto view=ui.dungeonTransition(timing,5000+key[0]);
        check(std::abs(int(view.bannerAlpha)-key[1])<=1&&std::abs(int(view.cardsAlpha)-key[2])<=1,
            "source banner and balloon alpha phases have actual consumers");
        check(view.cardsInteractive==(key[0]>=1300),"input follows the source reveal window");
    }
    int maps=0,cards=0;Json sourceMaps=Json::array();DungeonSelectionModel last;
    for(const auto &path:pvf.paths("worldmap/",".wdm")) {
        catalog.prepareWorldmap(path);auto model=captureDungeonSelectionModel(pvf,catalog,path);
        if(model.choices.empty())continue;
        ++maps;
        for(const auto &choice:model.choices) {
            ++cards;
            check(canEnterDungeonSelection(model,choice.id,{1,false,1,true}),
                "registered source cards use the requested temporary level/task bypass");
            const auto layout=ui.dungeonLayout(model,choice.id);
            const auto card=std::find_if(layout.cards.begin(),layout.cards.end(),
                [&](const auto &item){return item.dungeonId==choice.id;});
            check(card!=layout.cards.end(),"every source card survives layout");
            if(!choice.slotImage.empty()) {
                const auto pixels=assets.pixels(choice.slotImage,choice.slotFrame);
                check(card->imageRect.width==pixels.logicalWidth&&card->imageRect.height==pixels.logicalHeight,
                    "selected image uses its own original IMG canvas");
            }
            check(card->imageRect.x>=0&&card->imageRect.y>=0&&
                card->imageRect.x+card->imageRect.width<=800&&
                card->imageRect.y+card->imageRect.height<=600,
                "each source-direction expanded image fits the logical map viewport");
            check(layout.cards.back().dungeonId==choice.id,"selected draw and hit order agree");
            auto state=enterDungeonSelection(model);state.selectedDungeon=choice.id;
            ui.startDungeonPresentation(state,5000);
            auto event=updateDungeonSelection(model,layout,state,
                {DungeonSelectionAction::Enter,{},6299},{1,false,1,true});
            check(event.kind==DungeonSelectionEventKind::None&&state.open,
                "hidden cards cannot consume entry during the source banner");
            event=updateDungeonSelection(model,layout,state,
                {DungeonSelectionAction::Enter,{},6600},{1,false,1,true});
            check(event.kind==DungeonSelectionEventKind::EnterDungeon&&!state.open&&event.dungeonId==choice.id,
                "registered cards enter after reveal while retaining their source IDs");
        }
        sourceMaps.push_back({{"path",path},{"cards",model.choices.size()}});last=std::move(model);
    }
    check(maps>=20&&cards>=100,"all current nonempty WDMs and source cards are examined");
    check(!canEnterDungeonSelection(last,INT_MAX,{100,false,1,true}),
        "bypass does not invent an unregistered dungeon");
    auto state=enterDungeonSelection(last);ui.startDungeonPresentation(state,10000);
    const auto layout=ui.dungeonLayout(last,state.selectedDungeon);
    const auto cancel=updateDungeonSelection(last,layout,state,
        {DungeonSelectionAction::PointerActivate,{layout.cancelButton.x+1,layout.cancelButton.y+1},10001},
        {1,false,1,true});
    check(cancel.kind==DungeonSelectionEventKind::Cancelled&&!state.open&&state.awaitingEntranceExit,
        "source return button is live during the banner and prevents entrance auto-reopen");
    WorldMapUi world;world.bind(pvf,assets);int npcCount=0;
    for(const auto &page:world.pages())for(const auto &area:page.areas)for(const auto &npc:area.npcs) {
        ++npcCount;const auto projected=WorldMapUi::project(area,npc.real.x,npc.real.y);
        check(projected.has_value(),"each source NPC projects through its own MM area");
        check(projected->x>=area.projected.x&&projected->x<=area.projected.x+area.projected.width&&
            projected->y>=area.projected.y&&projected->y<=area.projected.y+area.projected.height,
            "source NPC projection remains in that MM rectangle");
    }
    check(npcCount>=50,"MM NPC registrations remain reachable by the renderer");
    for(int doors=1;doors<=15;++doors)for(int64_t now:{0,159,160,7999})
        check(dungeonMinimapFrame(doors,now,true)==44+(doors-1)*8+4,
            "current-room frame uses a stable source phase for every door mask");
    check(dungeonMinimapFrame(0,0,true)==-1&&dungeonMinimapFrame(16,0,true)==-1,
        "invalid minimap door masks do not invent frames");
    for(const auto &row:std::vector<std::array<int,3>>{
        {0,5000,0},{1,5000,1},{999,5000,1},{1000,5000,1},{1001,5000,2},
        {5000,5000,5},{500,500,1},{INT_MAX,INT_MAX,2147484}}) {
        const auto view=BossHealthLayerView::split(row[0],row[1]);
        check(view.remaining==row[2]&&view.ratio>=0&&view.ratio<=1,
            "display-only Boss layer split handles zero, exact edges and integer overflow");
    }
    check(BossHealthLayerView::split(1000,5000).ratio==1&&BossHealthLayerView::split(500,500).ratio==1,
        "exact HP boundaries and low-max Bosses display a full live layer");
    check(BossHealthLayerView::split(1001,5000).frame!=BossHealthLayerView::split(1000,5000).frame,
        "Boss layer change selects distinct source fill colors");
    return {{"status","passed"},{"count",checks.size()},{"checks",checks},
        {"maps",maps},{"cards",cards},{"npc_count",npcCount},{"worldmaps",sourceMaps},
        {"selection_source",ui.snapshot()},{"worldmap_source",world.snapshot()},
        {"scope","current source/layout/admission/controller/display boundary checks; no SDL or frontend equivalence claim"}};
}
} // namespace dnf
