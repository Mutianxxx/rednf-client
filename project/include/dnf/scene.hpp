#pragma once
#include "resources.hpp"
#include "objects.hpp"
#include "scene_camera.hpp"
#include <array>
#include <tuple>
namespace dnf {
class Renderer;
class World;
struct MapLayer {
    std::string animation;
    double x = 0, y = 0;
    int order = 0;
    double scroll = 1;
    double depthY = 0;
    std::string sourceLayer, sourceOrder;
    bool background = false, loopY = false, screenPosition = false;
    int repeatWidth = 0, repeatHeight = 0;
};
// Source labels and their order remain intact. The two spellings of upper
// occur in this 1031 PVF; normalization is an execution rule, not a source edit.
int mapLayerOrder(const std::string &sourceLayer);
bool mapBackgroundUpper(const std::string &sourceOrder);
void configureMapBackground(MapLayer &, const Script &map);
struct MapDrawCommand {
    enum class Kind { Tile, Animation };
    Kind kind = Kind::Animation;
    size_t index = 0;
};
struct MapNpc {
    int id = 0, direction = 1;
    double x = 0, y = 0, z = 0;
    std::string source, animation, name, voice;
    bool visibleOnDungeonClear = false;
    bool visible = true, generatedPlacement = false;
    // Negative keeps the ordinary ANI clock. A nonnegative index pins a stable
    // frame for decoration ANIs that are grade sheets, not motions.
    int staticFrame = -1;
    int64_t appearedAt = 0;
    std::array<double, 3> sourcePosition{0, 0, 0};
};
struct TownExit {
    // Source MAP rectangle, with only the MAP background origin added to Y.
    double x = 0, y = 0, width = 0, height = 0;
    int town = 0, area = 0;
    size_t offset = 0;
    Json raw = Json::array();
    bool contains(double px, double py) const {
        return px >= x && px <= x + width && py >= y && py <= y + height;
    }
};
struct MapObject {
    ObjectIdentity identity;
    int id = 0;
    double x = 0, y = 0, z = 0;
    std::string source, animation, name, layer, passType;
    int width = 0, height = 0;
    bool breakable = false, special = false;
    bool destroyed = false, consumed = false;
    int64_t animationMs = 0;
    int direction = 1;
    bool loop = true;
    Json payload = Json::array(), raw = Json::array();
};
struct Scene {
    std::string path, name;
    int width = 1000, bg = 80;
    Script script;
    std::vector<MapLayer> layers;
    std::vector<MapNpc> npcs;
    std::vector<TownExit> townExits;
    std::vector<MapObject> objects;
    ObjectSystem objectSystem;
    int64_t objectClockTick = -1;
    std::vector<std::array<double, 4>> blockedRects;
    std::vector<std::array<double, 4>> walkRects;
    std::vector<std::tuple<std::string, int, double, double>> tiles;
    std::vector<SourceTileVisual> sourceTileVisuals;
    Json issues = Json::array();
    Json tileGrids = Json::array(); // Source dimensions and the separately inferred walk-grid footprint.
    void load(Pvf &p, Assets &assets, const std::string &path,
              const std::string &run = "preview", const std::string &room = "0");
    const TownExit *townExitAt(double x, double y) const;
    std::array<double, 2> townArrivalFrom(int town, int area) const;
    // Clear-only NPC placement is application state, never a rendering side effect.
    void updateNpcs(const World &, bool dungeonCleared);
    void draw(Renderer &r, int64_t ms, double camera, bool front = false, double cameraY = 0);
    void updateObjects(World &, Pvf &, Assets &);
    void rebuildObstacles(World &) const;
    Json saveObjects(int64_t now) const;
    void restoreObjects(const Json &, int64_t now);
    void refreshObjectViews();
};
// The renderer executes this exact plan around its existing actor/Y queue.
// It contains source tiles and fixed layers; normal Y-sorted ANI stay in the
// actor queue. This permits source-backed draw-order tests without a window.
std::vector<MapDrawCommand> sceneDrawCommands(const Scene &, bool front);
} // namespace dnf
