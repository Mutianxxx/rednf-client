#pragma once
#include "resources.hpp"
#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace dnf {

class Pvf;
class RegionCatalog;

struct DungeonSelectionToken {
    uint8_t type = 0;
    int32_t value = 0;
    size_t offset = 0;
    std::array<uint8_t, 5> raw{};
};

struct DungeonSelectionField {
    std::string tag;
    size_t offset = 0;
    Json values = Json::array();
};

struct DungeonSelectionSource {
    std::string path;
    Bytes bytes;
    std::string sha256;
    uint64_t pvfEntryOffset = 0;
    uint32_t pvfEntryCrc = 0;
    std::vector<DungeonSelectionToken> tokens;
    std::vector<DungeonSelectionField> fields;
};

struct DungeonSelectionControl {
    std::string type;
    std::string name;
    double x = 0, y = 0;
    std::vector<std::string> strings;
    std::vector<int32_t> integers;
    std::string commonAction;
    std::string resolvedCommonAction;
    size_t sourceOffset = 0;
    Json sourceValues = Json::array();
};

struct DungeonPatternRow {
    std::string tag;
    std::vector<int32_t> values;
    size_t sourceOffset = 0;
    Json sourceValues = Json::array();
};

struct DungeonSelectionChoice {
    int id = 0;
    std::string name;
    std::string slotImage;
    int slotFrame = 0;
    int minimumLevel = 1;
    int basisLevel = 1;
    bool sourceEnabled = false;
    Json modeValues = Json::array();
    std::string dungeonPath;
    size_t dungeonSourceOffset = 0;
    Json sourceFields = Json::array();
};

struct DungeonSelectionModel {
    std::string worldmapPath, worldmapName, uiPath;
    Json diagnostics = Json::array();
    std::string backgroundImage;
    int backgroundFrame = 0;
    std::vector<DungeonSelectionChoice> choices;
    std::vector<DungeonSelectionControl> controls;
    std::vector<DungeonPatternRow> firstPatternTable;
    std::vector<DungeonPatternRow> secondPatternTable;
    std::vector<DungeonSelectionSource> sources;
    std::string layoutClassification = "inferred-from-client-resources-and-reference-captures";
};

DungeonSelectionModel captureDungeonSelectionModel(Pvf &pvf, const RegionCatalog &catalog);
DungeonSelectionModel captureDungeonSelectionModel(Pvf &,const RegionCatalog &,const std::string &worldmapPath);

struct SelectionPoint { double x = 0, y = 0; };
struct SelectionRect {
    double x = 0, y = 0, width = 0, height = 0;
    bool contains(SelectionPoint point) const;
};
struct DungeonSelectionCardLayout {
    int dungeonId = 0;
    SelectionRect hitRect;
    SelectionRect imageRect;
};
struct DungeonSelectionLayout {
    SelectionRect viewport;
    std::vector<DungeonSelectionCardLayout> cards;
    SelectionRect enterButton;
    SelectionRect cancelButton;
    SelectionRect difficultyLeft;
    SelectionRect difficultyRight;
    SelectionRect difficultyLabel;
    double scale = 1;
    double offsetX = 0, offsetY = 0;
    SelectionPoint toLogical(SelectionPoint physical) const;
};

enum class DungeonSelectionAction {
    PointerMove, PointerActivate, Enter, Cancel, MoveLeft, MoveRight, MoveUp, MoveDown,
    DifficultyLeft, DifficultyRight
};
struct DungeonSelectionInput {
    DungeonSelectionAction action = DungeonSelectionAction::PointerMove;
    SelectionPoint pointer;
    int64_t wallMs = -1;
    int clickCount = 1; // SDL click count; no wall-clock synthesis by rendering.
};
enum class DungeonSelectionEventKind { None, Selected, Cancelled, EnterDungeon, DifficultyChanged };
struct DungeonSelectionEvent {
    DungeonSelectionEventKind kind = DungeonSelectionEventKind::None;
    int dungeonId = 0;
    int difficulty = 0;
};
struct DungeonSelectionAdmission {
    int characterLevel = 1;
    bool allowSupportedDifficulty = false;
    int supportedDifficultyCount = 1;
    bool bypassLevelAndTasks = false;
};
struct DungeonSelectionState {
    int selectedDungeon = 0;
    int hoveredDungeon = 0;
    int difficulty = 0;
    bool open = false;
    bool awaitingEntranceExit = false;
    bool entryConsumed = false;
    // Source common/UI action uses wall time, independent of paused simulation.
    int64_t openedWallMs = 0;
    int64_t cardsVisibleAfterMs = 0;
};

bool canEnterDungeonSelection(const DungeonSelectionModel &model, int dungeonId,
    DungeonSelectionAdmission admission);
Json describeDungeonSelection(const DungeonSelectionModel &model, const DungeonSelectionLayout &layout,
    const DungeonSelectionState &state);

DungeonSelectionLayout makeDungeonSelectionLayout(const DungeonSelectionModel &model,
    double viewportWidth = 800, double viewportHeight = 600);
// Recompute after selected source card dimensions/anchors change.
void positionDungeonDifficultyControls(DungeonSelectionLayout &, int selectedDungeon);
DungeonSelectionState enterDungeonSelection(const DungeonSelectionModel &model,
    DungeonSelectionState state = {});
DungeonSelectionEvent updateDungeonSelection(const DungeonSelectionModel &model,
    const DungeonSelectionLayout &layout, DungeonSelectionState &state,
    const DungeonSelectionInput &input, DungeonSelectionAdmission admission);
void leaveDungeonEntrance(DungeonSelectionState &state);

} // namespace dnf
