#include "dnf/dungeon_difficulty.hpp"
#include "dnf/dungeon_selection.hpp"
#include "dnf/region.hpp"
#include <algorithm>
#include <limits>

namespace dnf {
namespace {
const DungeonSelectionChoice *choice(const DungeonSelectionModel &model, int id) {
    const auto it = std::find_if(model.choices.begin(), model.choices.end(),
        [id](const auto &item) { return item.id == id; });
    return it == model.choices.end() ? nullptr : &*it;
}

bool admitted(const DungeonSelectionChoice *item, const DungeonSelectionAdmission &admission) {
    return item && (admission.bypassLevelAndTasks ||
        (item->sourceEnabled && admission.characterLevel >= item->minimumLevel));
}

int firstChoice(const DungeonSelectionModel &model) {
    return model.choices.empty() ? 0 : model.choices.front().id;
}

DungeonSelectionSource captureSource(Pvf &pvf, const std::string &path) {
    DungeonSelectionSource result;
    result.path = normalize(path);
    result.bytes = pvf.read(result.path);
    const auto &entry = pvf.reads().at(result.path);
    result.pvfEntryOffset = entry.at("offset").get<uint64_t>();
    result.pvfEntryCrc = entry.at("crc").get<uint32_t>();
    const auto script = pvf.script(result.path);
    for (const auto &field : script.fields)
        result.fields.push_back({field.tag, field.offset, field.values});
    for (const auto &token : script.tokens) {
        DungeonSelectionToken item;
        item.type = token.at("type").get<uint8_t>();
        item.value = token.at("raw").get<int32_t>();
        item.offset = token.at("offset").get<size_t>();
        if (item.offset + item.raw.size() <= result.bytes.size())
            std::copy_n(result.bytes.begin() + item.offset, item.raw.size(), item.raw.begin());
        result.tokens.push_back(item);
    }
    return result;
}

std::vector<DungeonPatternRow> capturePatternTable(Pvf &pvf, const std::string &path) {
    std::vector<DungeonPatternRow> rows;
    const auto script = pvf.script(path);
    for (const auto &field : script.fields) {
        DungeonPatternRow row;
        row.tag = field.tag;
        row.sourceOffset = field.offset;
        row.sourceValues = field.values;
        for (const auto &value : field.values)
            if (value.is_number_integer()) row.values.push_back(value.get<int32_t>());
        rows.push_back(std::move(row));
    }
    return rows;
}
}

DungeonSelectionModel captureDungeonSelectionModel(Pvf &pvf, const RegionCatalog &catalog) {
    return captureDungeonSelectionModel(pvf,catalog,catalog.worldmap.path);
}
DungeonSelectionModel captureDungeonSelectionModel(Pvf &pvf,const RegionCatalog &catalog,const std::string &worldmapPath) {
    DungeonSelectionModel result;
    const auto worldmap=pvf.script(worldmapPath);
    result.worldmapPath=worldmap.path;result.worldmapName=worldmap.text("[name]",worldmap.path);
    const auto image = worldmap.values("[map image]");
    if (image.size() >= 2) {
        result.backgroundImage = normalize(image[0].get<std::string>());
        result.backgroundFrame = image[1].get<int>();
    }
    const auto uiPathValues = worldmap.values("[ui path]");
    if(uiPathValues.empty()||!uiPathValues[0].is_string())throw std::runtime_error("WDM has no source UI path: "+worldmap.path);
    const std::string uiPath=normalize(uiPathValues[0]);result.uiPath=uiPath;
    const auto ui = pvf.script(uiPath);
    std::vector<std::string> sourcePaths = {catalog.town.path, "worldmap/worldmap.lst", worldmap.path,
        uiPath, "worldmap/worldmappatterntable.tbl", "worldmap/worldmappatterntable2nd.tbl",
        "dungeon/dungeon.lst"};
    bool insideControl = false;
    for (size_t index = 0; index < ui.fields.size(); ++index) {
        const auto &field = ui.fields[index];
        if (field.tag == "[ui controls]" && !field.values.empty()) {
            insideControl = true;
            DungeonSelectionControl control;
            control.type = field.values[0].get<std::string>();
            control.sourceOffset = field.offset;
            control.sourceValues = field.values;
            if (field.values.size() > 1 && field.values[1].is_string()) control.name = field.values[1];
            if (field.values.size() > 3 && field.values[2].is_number() && field.values[3].is_number()) {
                control.x = field.values[2].get<double>();
                control.y = field.values[3].get<double>();
            }
            if (field.values.size() > 4 && field.values[4].is_number_integer()) {
                size_t cursor = 5;
                const auto stringCount = std::clamp(field.values[4].get<int>(), 0, int(field.values.size() - cursor));
                for (int i = 0; i < stringCount; ++i) control.strings.push_back(field.values[cursor++].get<std::string>());
                if (cursor < field.values.size() && field.values[cursor].is_number_integer()) {
                    const int count = std::clamp(field.values[cursor].get<int>(), 0, int(field.values.size() - cursor - 1));
                    ++cursor;
                    for (int i = 0; i < count; ++i) {
                        if (field.values[cursor].is_number_integer()) control.integers.push_back(field.values[cursor].get<int32_t>());
                        else control.integers.push_back(0);
                        ++cursor;
                    }
                }
            }
            // The .ui owns its visible background control. In this 1031 source,
            // TimeGate WDM spells TimeGate.img while UI explicitly binds TimegGate.img.
            // Preserve both source fields; do not manufacture a resource alias.
            if(control.type=="[image]"&&control.name=="IDC_WORLDMAP_BACKGROUND"&&!control.strings.empty()&&!control.integers.empty()) {
                const auto uiImage=normalize(control.strings[0]);const int uiFrame=control.integers[0];
                if(uiImage!=result.backgroundImage||uiFrame!=result.backgroundFrame)
                    result.diagnostics.push_back({{"code","wdm_ui_background_binding_differs"},{"wdm",worldmap.path},
                        {"wdm_image",result.backgroundImage},{"wdm_frame",result.backgroundFrame},{"ui",uiPath},
                        {"ui_image",uiImage},{"ui_frame",uiFrame},{"offset",control.sourceOffset}});
                result.backgroundImage=uiImage;result.backgroundFrame=uiFrame;
            }
            if (control.type == "[balloon]" && !control.integers.empty()) {
                const int dungeonId = control.integers.back();
                const auto found = catalog.dungeons.find(dungeonId);
                if (found != catalog.dungeons.end()) {
                    const auto &source = found->second;
                    DungeonSelectionChoice choice;
                    choice.id = source.id;
                    choice.name = source.name;
                    choice.slotImage = source.slotImage;
                    choice.slotFrame = source.slotFrame;
                    choice.minimumLevel = source.minimumLevel;
                    choice.basisLevel = int(source.source.number("[basis level]",source.minimumLevel));
                    choice.sourceEnabled = source.enabled;
                    choice.dungeonPath = source.path;
                    const auto mode = source.source.values("[worldmap pattern info]");
                    choice.modeValues = mode;
                    for (const auto &sourceField : source.source.fields)
                        choice.sourceFields.push_back({{"tag", sourceField.tag}, {"offset", sourceField.offset},
                            {"values", sourceField.values}});
                    choice.dungeonSourceOffset = source.source.fields.empty() ? 0 : source.source.fields.front().offset;
                    if (!choice.dungeonPath.empty()) sourcePaths.push_back(choice.dungeonPath);
                    result.choices.push_back(std::move(choice));
                } else {
                    result.diagnostics.push_back({{"code","balloon_dungeon_unregistered"},
                        {"dungeon",dungeonId},{"ui",uiPath},{"offset",field.offset},{"raw",field.values}});
                }
            }
            result.controls.push_back(std::move(control));
        } else if (insideControl && field.tag == "[common action]" && !field.values.empty()) {
            auto &control = result.controls.back();
            control.commonAction = field.values.front().get<std::string>();
            control.resolvedCommonAction = normalize((std::filesystem::u8path(uiPath).parent_path() /
                std::filesystem::u8path(control.commonAction)).generic_u8string());
            sourcePaths.push_back(control.resolvedCommonAction);
        } else if (field.tag == "[/ui controls]") {
            insideControl = false;
        }
    }
    result.firstPatternTable = capturePatternTable(pvf, "worldmap/worldmappatterntable.tbl");
    result.secondPatternTable = capturePatternTable(pvf, "worldmap/worldmappatterntable2nd.tbl");
    std::vector<std::string> uniquePaths;
    for (const auto &path : sourcePaths)
        if (std::find(uniquePaths.begin(), uniquePaths.end(), path) == uniquePaths.end()) uniquePaths.push_back(path);
    for (const auto &path : uniquePaths)
        if (!path.empty() && pvf.has(path)) result.sources.push_back(captureSource(pvf, path));
    return result;
}

bool SelectionRect::contains(SelectionPoint point) const {
    return point.x >= x && point.y >= y && point.x < x + width && point.y < y + height;
}

SelectionPoint DungeonSelectionLayout::toLogical(SelectionPoint physical) const {
    if (scale <= 0) return {};
    return {(physical.x - offsetX) / scale, (physical.y - offsetY) / scale};
}

DungeonSelectionLayout makeDungeonSelectionLayout(const DungeonSelectionModel &model,
    double viewportWidth, double viewportHeight) {
    DungeonSelectionLayout result;
    if (viewportWidth <= 0 || viewportHeight <= 0) return result;
    result.scale = std::min(viewportWidth / 800.0, viewportHeight / 600.0);
    result.offsetX = (viewportWidth - 800 * result.scale) / 2;
    result.offsetY = (viewportHeight - 600 * result.scale) / 2;
    result.viewport = {result.offsetX, result.offsetY, 800 * result.scale, 600 * result.scale};

    // The source slot image is 168x73. Its placement around the UI control
    // anchor is inferred; mode-table anchor and animation semantics remain unknown.
    for (size_t i = 0; i < model.choices.size(); ++i) {
        const auto &item = model.choices[i];
        const auto control = std::find_if(model.controls.begin(), model.controls.end(),
            [&item](const auto &candidate) { return candidate.integers.size() >= 1 && candidate.integers.back() == item.id; });
        double x = 0, y = 0;
        if (control != model.controls.end()) {
            x = control->x - 84;
            y = control->y - 89;
        } else {
            x = 290 + (i % 2) * 130;
            y = 130 + (i / 2) * 110;
        }
        const SelectionRect card{x, y, 168, 73};
        result.cards.push_back({item.id, card, card});
    }
    result.enterButton = {694, 570, 106, 27};
    result.cancelButton = {700, 540, 92, 31};
    positionDungeonDifficultyControls(result,firstChoice(model));
    return result;
}

void positionDungeonDifficultyControls(DungeonSelectionLayout &layout,int selectedDungeon) {
    layout.difficultyLeft={};layout.difficultyRight={};layout.difficultyLabel={};
    const auto selected=std::find_if(layout.cards.begin(),layout.cards.end(),
        [&](const auto &card){return card.dungeonId==selectedDungeon;});
    if(selected==layout.cards.end())return;
    const auto &q=selected->imageRect;
    // Requested middle/lower row; exact native balloon placement remains unknown.
    constexpr double controlsWidth=99,height=19;
    const double x=q.x+(q.width-controlsWidth)/2;
    const double y=q.y+std::clamp(q.height*0.60,0.0,std::max(0.0,q.height-height-5));
    layout.difficultyLeft={x,y,20,height};layout.difficultyLabel={x+24,y,51,height};
    layout.difficultyRight={x+79,y,20,height};
}

DungeonSelectionState enterDungeonSelection(const DungeonSelectionModel &model, DungeonSelectionState state) {
    if (state.awaitingEntranceExit || state.entryConsumed || state.open) return state;
    state.open = true;
    state.entryConsumed = false;
    state.selectedDungeon = choice(model, state.selectedDungeon) ? state.selectedDungeon : firstChoice(model);
    state.hoveredDungeon = 0;
    return state;
}

bool canEnterDungeonSelection(const DungeonSelectionModel &model, int dungeonId,
    DungeonSelectionAdmission admission) {
    return admitted(choice(model, dungeonId), admission);
}

Json describeDungeonSelection(const DungeonSelectionModel &model, const DungeonSelectionLayout &layout,
    const DungeonSelectionState &state) {
    auto rect = [](const SelectionRect &r) {
        return Json{{"x",r.x},{"y",r.y},{"width",r.width},{"height",r.height}};
    };
    Json cards = Json::array();
    for (const auto &card : layout.cards) {
        auto value = rect(card.hitRect);
        value["id"] = card.dungeonId;
        cards.push_back(value);
    }
    return {{"selected",state.selectedDungeon},{"hovered",state.hoveredDungeon},
        {"difficulty",state.difficulty},{"open",state.open},{"awaiting_exit",state.awaitingEntranceExit},
        {"entry_consumed",state.entryConsumed},{"cards",cards},{"enter_button",rect(layout.enterButton)},
        {"cancel_button",rect(layout.cancelButton)},{"difficulty_left",rect(layout.difficultyLeft)},
        {"difficulty_right",rect(layout.difficultyRight)},{"difficulty_label",rect(layout.difficultyLabel)},{"layout_classification",model.layoutClassification}};
}

DungeonSelectionEvent updateDungeonSelection(const DungeonSelectionModel &model,
    const DungeonSelectionLayout &layout, DungeonSelectionState &state,
    const DungeonSelectionInput &input, DungeonSelectionAdmission admission) {
    if (!state.open) return {};
    const auto pointer = layout.toLogical(input.pointer);
    const int difficultyCount=admission.allowSupportedDifficulty?
        std::clamp(admission.supportedDifficultyCount,1,dungeonDifficultyCount):1;
    state.difficulty=std::clamp(state.difficulty,0,difficultyCount-1);
    const bool intro = input.wallMs >= 0 &&
        input.wallMs - state.openedWallMs < state.cardsVisibleAfterMs;
    const bool cancel = input.action == DungeonSelectionAction::Cancel ||
        (input.action == DungeonSelectionAction::PointerActivate && layout.cancelButton.contains(pointer));
    if (intro && !cancel) { state.hoveredDungeon = 0; return {}; }
    auto cardAt = [&]() -> int {
        // Drawing follows source order; the last overlapping card is visible
        // on top and must receive the pointer first.
        for (auto card = layout.cards.rbegin(); card != layout.cards.rend(); ++card)
            if (card->hitRect.contains(pointer)) return card->dungeonId;
        return 0;
    };

    switch (input.action) {
    case DungeonSelectionAction::PointerMove:
        state.hoveredDungeon = cardAt();
        return {};
    case DungeonSelectionAction::PointerActivate: {
        // Local arrows lie inside the selected card and must consume the click
        // before card selection or double-click entrance.
        if (layout.difficultyLeft.contains(pointer) || layout.difficultyRight.contains(pointer)) {
            if (difficultyCount>1) {
                state.difficulty=std::clamp(state.difficulty+
                    (layout.difficultyLeft.contains(pointer)?-1:1),0,difficultyCount-1);
                return {DungeonSelectionEventKind::DifficultyChanged,state.selectedDungeon,state.difficulty};
            }
            return {};
        }
        const int id = cardAt();
        if (id != 0) {
            state.selectedDungeon = id;
            if(input.clickCount>=2&&!state.entryConsumed&&admitted(choice(model,id),admission)) {
                state.entryConsumed=true;state.open=false;
                return {DungeonSelectionEventKind::EnterDungeon,id,state.difficulty};
            }
            return {DungeonSelectionEventKind::Selected, id, state.difficulty};
        }
        if (layout.enterButton.contains(pointer)) {
            const auto *selected = choice(model, state.selectedDungeon);
            if (!state.entryConsumed && admitted(selected, admission)) {
                state.entryConsumed = true;
                state.open = false;
                return {DungeonSelectionEventKind::EnterDungeon, selected->id, state.difficulty};
            }
        }
        if (layout.cancelButton.contains(pointer)) {
            state.open = false;
            state.awaitingEntranceExit = true;
            return {DungeonSelectionEventKind::Cancelled, state.selectedDungeon, state.difficulty};
        }
        return {};
    }
    case DungeonSelectionAction::Enter: {
        const auto *selected = choice(model, state.selectedDungeon);
        if (!state.entryConsumed && admitted(selected, admission)) {
            state.entryConsumed = true;
            state.open = false;
            return {DungeonSelectionEventKind::EnterDungeon, selected->id, state.difficulty};
        }
        return {};
    }
    case DungeonSelectionAction::Cancel:
        state.open = false;
        state.awaitingEntranceExit = true;
        return {DungeonSelectionEventKind::Cancelled, state.selectedDungeon, state.difficulty};
    case DungeonSelectionAction::MoveLeft:
    case DungeonSelectionAction::MoveRight:
    case DungeonSelectionAction::MoveUp:
    case DungeonSelectionAction::MoveDown: {
        const auto current = std::find_if(layout.cards.begin(), layout.cards.end(),
            [&](const auto &card) { return card.dungeonId == state.selectedDungeon; });
        if (current == layout.cards.end()) return {};
        const auto center = [](const SelectionRect &r) {
            return SelectionPoint{r.x + r.width / 2, r.y + r.height / 2};
        };
        const auto origin = center(current->hitRect);
        double best = std::numeric_limits<double>::infinity();
        int selected = state.selectedDungeon;
        for (const auto &card : layout.cards) {
            const auto target = center(card.hitRect);
            const double dx = target.x - origin.x, dy = target.y - origin.y;
            const double forward = input.action == DungeonSelectionAction::MoveLeft ? -dx :
                input.action == DungeonSelectionAction::MoveRight ? dx :
                input.action == DungeonSelectionAction::MoveUp ? -dy : dy;
            const double distance = dx * dx + dy * dy;
            if (forward > 0 && distance < best) { best = distance; selected = card.dungeonId; }
        }
        if (selected == state.selectedDungeon) return {};
        state.selectedDungeon = selected;
        return {DungeonSelectionEventKind::Selected, selected, state.difficulty};
    }
    case DungeonSelectionAction::DifficultyLeft:
    case DungeonSelectionAction::DifficultyRight:
        if (difficultyCount > 1) {
            state.difficulty = std::clamp(state.difficulty +
                (input.action == DungeonSelectionAction::DifficultyLeft ? -1 : 1),
                0, difficultyCount - 1);
            return {DungeonSelectionEventKind::DifficultyChanged, state.selectedDungeon, state.difficulty};
        }
        return {};
    }
    return {};
}

void leaveDungeonEntrance(DungeonSelectionState &state) {
    state.awaitingEntranceExit = false;
    state.entryConsumed = false;
}

} // namespace dnf
