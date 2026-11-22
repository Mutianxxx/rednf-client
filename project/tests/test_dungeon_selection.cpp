#include "dnf/dungeon_selection.hpp"
#include "dnf/dungeon_difficulty.hpp"
#include "dnf/region.hpp"
#include <stdexcept>

namespace dnf {
Json runDungeonSelectionTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto require = [&](bool passed, const char *description) {
        if (!passed) throw std::runtime_error(std::string("Dungeon selection: ") + description);
        checks.push_back(description);
    };
    RegionCatalog catalog(pvf, assets);
    const auto model = captureDungeonSelectionModel(pvf, catalog);
    require(model.backgroundImage == "worldmap/lorien.img" && model.backgroundFrame == 0,
        "WDM background image and frame come from the original source");
    require(model.choices.size() == 4 && model.choices[0].id == 1 && model.choices[1].id == 2 &&
            model.choices[2].id == 1500 && model.choices[3].id == 1501,
        "Cards retain UI control order and disabled WDM dungeon IDs");
    require(model.choices[0].minimumLevel == 1 && model.choices[1].minimumLevel == 2 &&
            model.choices[0].sourceEnabled && model.choices[1].sourceEnabled &&
            !model.choices[2].sourceEnabled && !model.choices[3].sourceEnabled,
        "Source level requirements combine with explicit demo availability gates");
    require(model.choices[0].modeValues.size() == 4 && model.choices[0].modeValues[0] == 1 &&
            model.choices[0].modeValues[1] == 1 && model.choices[0].modeValues[2] == "WorldMap/SelectdungeonSlot/elvengard.img" &&
            model.choices[1].modeValues[1] == 2,
        "DGN world-map pattern values remain ordered and uncollapsed");
    require(model.controls.size() == 9 && model.controls[4].type == "[balloon]" &&
            model.controls[4].name == "IDC_WORLDMAP_BUTTON1" && model.controls[4].integers.size() == 3 &&
            model.controls[4].integers[0] == 1 && model.controls[4].integers[1] == 13 &&
            model.controls[4].integers[2] == 1 && model.controls[4].commonAction == "Action/worldmap_balloon.act" &&
            model.controls[4].resolvedCommonAction == "worldmap/ui/action/worldmap_balloon.act",
        "UI balloon arrays, action, name, order and source offsets are retained");
    require(model.firstPatternTable.size() == 2 && model.firstPatternTable[0].values.size() == 60 &&
            model.secondPatternTable.size() == 18 && model.secondPatternTable[0].values.size() == 6,
        "Full six-value world-map mode rows remain available for both original tables");
    auto hasSource = [&](const std::string &path) {
        for (const auto &source : model.sources) if (source.path == path && !source.bytes.empty() &&
                source.pvfEntryOffset > 0 && source.pvfEntryCrc != 0 && !source.tokens.empty()) {
            for (const auto &token : source.tokens)
                if (token.offset + token.raw.size() > source.bytes.size()) return false;
            return true;
        }
        return false;
    };
    require(hasSource("town/elvengard.twn") && hasSource("worldmap/lorien.wdm") &&
            hasSource("worldmap/ui/lorien.ui") && hasSource("worldmap/worldmap.lst") &&
            hasSource("dungeon/act1/lorien.dgn") && hasSource("dungeon/act1/lorieninside.dgn"),
        "TWN, WDM, UI, mode tables and DGN retain source bytes with valid token offsets");

    const auto layout = makeDungeonSelectionLayout(model);
    require(canEnterDungeonSelection(model,1,{1,false}) && !canEnterDungeonSelection(model,2,{1,false}) &&
            canEnterDungeonSelection(model,2,{2,false}) && !canEnterDungeonSelection(model,1500,{99,false}) &&
            !canEnterDungeonSelection(model,-1,{99,false}),
        "One public admission gate rejects unknown, unopened and under-level dungeons");
    require(layout.cards.size() == model.choices.size() && layout.cards[0].hitRect.width == 168 &&
            layout.cards[0].hitRect.height == 73 && layout.cards[0].hitRect.contains(
                {layout.cards[0].hitRect.x, layout.cards[0].hitRect.y}) &&
            !layout.cards[0].hitRect.contains({layout.cards[0].hitRect.x + 168, layout.cards[0].hitRect.y}),
        "Card paint and hit geometry share stable source-sized rectangles with half-open edges");

    DungeonSelectionState state;
    state = enterDungeonSelection(model, state);
    require(state.open && state.selectedDungeon == 1, "Entrance opens with a valid source-ordered selection");
    auto navigation = state;
    auto navigationEvent = updateDungeonSelection(model,layout,navigation,
        {DungeonSelectionAction::MoveUp,{}},{1,false});
    require(navigationEvent.kind == DungeonSelectionEventKind::Selected && navigation.selectedDungeon == 2 &&
            navigation.hoveredDungeon == 0,
        "Geometric keyboard selection moves to the source card above without granting admission or changing hover");
    auto overlapped = layout;
    overlapped.cards[1].hitRect = overlapped.cards[0].hitRect;
    auto overlapState = state;
    updateDungeonSelection(model,overlapped,overlapState,
        {DungeonSelectionAction::PointerMove,{layout.cards[0].hitRect.x+2,layout.cards[0].hitRect.y+2}},{1,false});
    require(overlapState.hoveredDungeon == 2,
        "Overlapping card hit testing follows the same last-painted order as rendering");
    auto event = updateDungeonSelection(model, layout, state,
        {DungeonSelectionAction::PointerMove, {layout.cards[1].hitRect.x + 10, layout.cards[1].hitRect.y + 10}}, {1, false});
    require(event.kind == DungeonSelectionEventKind::None && state.hoveredDungeon == 2 && state.selectedDungeon == 1,
        "Hover state remains independent of the committed selection");
    updateDungeonSelection(model, layout, state,
        {DungeonSelectionAction::PointerMove, {-100, -100}}, {1, false});
    require(state.hoveredDungeon == 0 && state.selectedDungeon == 1,
        "Pointer leave clears hover without changing the committed selection");
    event = updateDungeonSelection(model, layout, state,
        {DungeonSelectionAction::PointerActivate, {layout.cards[1].hitRect.x + 10, layout.cards[1].hitRect.y + 10}}, {1, false});
    require(event.kind == DungeonSelectionEventKind::Selected && state.selectedDungeon == 2,
        "Pointer activation selects a card without treating hover as selection");
    event = updateDungeonSelection(model, layout, state,
        {DungeonSelectionAction::Enter, {}}, {1, false});
    require(event.kind == DungeonSelectionEventKind::None && state.open,
        "Under-level entry is denied while the selection stays open");
    event = updateDungeonSelection(model, layout, state,
        {DungeonSelectionAction::Enter, {}}, {2, false});
    require(event.kind == DungeonSelectionEventKind::EnterDungeon && event.dungeonId == 2 && !state.open,
        "Shared level/open gate admits at the exact minimum level");
    event = updateDungeonSelection(model, layout, state, {DungeonSelectionAction::Enter, {}}, {99, false});
    require(event.kind == DungeonSelectionEventKind::None,
        "A consumed entry cannot emit a second enter event");
    state = enterDungeonSelection(model, state);
    require(!state.open, "A consumed entrance cannot reopen before the character exits it");
    leaveDungeonEntrance(state);

    state = enterDungeonSelection(model, state);
    event = updateDungeonSelection(model, layout, state,
        {DungeonSelectionAction::PointerActivate, {layout.cards[2].hitRect.x + 5, layout.cards[2].hitRect.y + 5}}, {99, false});
    require(event.kind == DungeonSelectionEventKind::Selected && state.selectedDungeon == 1500,
        "Locked content remains inspectable/selectable without granting admission");
    event = updateDungeonSelection(model, layout, state, {DungeonSelectionAction::Enter, {}}, {99, false});
    require(event.kind == DungeonSelectionEventKind::None && state.open,
        "Disabled source-backed dungeon remains blocked by the same admission check");
    event = updateDungeonSelection(model, layout, state, {DungeonSelectionAction::Cancel, {}}, {99, false});
    require(event.kind == DungeonSelectionEventKind::Cancelled && !state.open && state.awaitingEntranceExit,
        "Cancel closes the UI and locks reopening until the entrance is left");
    state = enterDungeonSelection(model, state);
    require(!state.open, "Re-entering the same entrance cannot immediately reopen after cancel");
    leaveDungeonEntrance(state);
    state = enterDungeonSelection(model, state);
    require(state.open && !state.awaitingEntranceExit,
        "Leaving and entering the town entrance rearms dungeon selection");

    auto wide = makeDungeonSelectionLayout(model, 1600, 900);
    const auto physical = SelectionPoint{wide.offsetX + wide.cards[0].hitRect.x * wide.scale + 2,
                                         wide.offsetY + wide.cards[0].hitRect.y * wide.scale + 2};
    const auto logical = wide.toLogical(physical);
    require(wide.scale == 1.5 && wide.offsetX == 200 &&
            wide.cards[0].hitRect.contains(logical),
        "Letterboxed wide viewport input maps back to the rendered logical hit region");
    event = updateDungeonSelection(model, wide, state,
        {DungeonSelectionAction::PointerMove, physical}, {99, false});
    require(event.kind == DungeonSelectionEventKind::None && state.hoveredDungeon == 1,
        "Viewport mapping is shared by pointer hover and paint geometry");
    event = updateDungeonSelection(model, layout, state,
        {DungeonSelectionAction::DifficultyRight, {}}, {99, false});
    require(event.kind == DungeonSelectionEventKind::None && state.difficulty == 0,
        "Unrestored difficulty choices remain unavailable");

    const SelectionPoint difficultyRight{layout.difficultyRight.x+1,layout.difficultyRight.y+1};
    event = updateDungeonSelection(model,layout,state,
        {DungeonSelectionAction::PointerActivate,difficultyRight},{99,true,1});
    require(event.kind == DungeonSelectionEventKind::None && state.difficulty == 0,
        "Pointer admission override cannot enable an unsupported difficulty");
    for(int i=0;i<8;++i)event=updateDungeonSelection(model,layout,state,
        {DungeonSelectionAction::PointerActivate,difficultyRight},{99,true,3});
    require(state.difficulty==2,"Three-tier admission subset retains index-two maximum");
    for(int i=0;i<8;++i)event=updateDungeonSelection(model,layout,state,
        {DungeonSelectionAction::DifficultyLeft,{}},{99,true,3});
    require(state.difficulty==0,"Keyboard and pointer difficulty transitions share bounds");
    for(int i=0;i<8;++i)event=updateDungeonSelection(model,layout,state,
        {DungeonSelectionAction::PointerActivate,difficultyRight,-1,2},{99,true,dungeonDifficultyCount});
    require(state.difficulty==3&&event.difficulty==3&&state.open&&!state.entryConsumed,
        "Four-tier pointer arrows reach king without triggering double-click entrance");
    for(int i=0;i<8;++i)event=updateDungeonSelection(model,layout,state,
        {DungeonSelectionAction::DifficultyLeft,{}},{99,true,dungeonDifficultyCount});
    require(state.difficulty==0,"Four-tier keyboard lower bound remains normal");
    for(int i=0;i<8;++i)event=updateDungeonSelection(model,layout,state,
        {DungeonSelectionAction::DifficultyRight,{}},{99,true,dungeonDifficultyCount});
    require(state.difficulty==3&&event.difficulty==3,"Four-tier keyboard and pointer share index-three maximum");
    event=updateDungeonSelection(model,layout,state,
        {DungeonSelectionAction::DifficultyRight,{}},{99,true,99});
    require(state.difficulty==3,"Excessive supported count cannot admit an unproven fifth tier");
    event=updateDungeonSelection(model,layout,state,
        {DungeonSelectionAction::DifficultyRight,{}},{99,false,dungeonDifficultyCount});
    require(state.difficulty==0&&event.kind==DungeonSelectionEventKind::None,
        "Disabling difficulty support clamps prior king selection to normal");

    return {{"status", "pass"}, {"checks", checks},
        {"classification", "portable service checks plus hash-bound source model checks; no runtime visual claim"}};
}
} // namespace dnf
