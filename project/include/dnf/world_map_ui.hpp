#pragma once
#include "dungeon_selection.hpp"
#include "region.hpp"
#include "renderer.hpp"
#include "selection_ui.hpp"
namespace dnf {
struct WorldMapNpcView {
    int id=-1, frame=-1;
    SelectionPoint real;
    std::string name;
    size_t sourceOffset=0;
};
struct WorldMapAreaView {
    int town = -1, area = -1;
    SelectionRect real, projected;
    std::vector<WorldMapNpcView> npcs;
};
struct WorldMapGateView {
    int worldmap = -1;
    SelectionPoint point;
    std::string name, path;
    Json levels = Json::array();
};
struct WorldMapPageView {
    std::string name, path, image, background;
    int imageFrame = 0, backgroundFrame = 0, width = 800, height = 600;
    std::vector<int> imageFrames;
    std::vector<WorldMapAreaView> areas;
    std::vector<WorldMapGateView> gates;
};
struct WorldMapUiAction {
    std::string worldmapPath;
    int worldmapId = -1;
};
// Source content and projection, with explicitly inferred navigation/hit areas.
// Does not modify eligibility, source bytes, source order or normal save data.
class WorldMapUi {
    std::vector<WorldMapPageView> pages_;
    Json sources_ = Json::array(), diagnostics_ = Json::array();
    size_t page_ = 0;
    int followedTown_ = -1;
 public:
    void bind(Pvf &,Assets &);
    Json snapshot() const;
    WorldMapUiAction draw(Renderer &,int town,int area,double sourceX,double sourceY,
                          SelectionUiPointer pointer,int64_t ms);
    const std::vector<WorldMapPageView> &pages() const { return pages_; }
    static std::optional<SelectionPoint> project(const WorldMapAreaView &,double x,double y);
};
int dungeonMinimapFrame(int doorMask,int64_t ms,bool active);
void drawSourceDungeonMinimap(Renderer &,const DungeonRun &,bool expanded,int64_t ms);
} // namespace dnf
