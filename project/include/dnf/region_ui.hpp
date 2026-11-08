#pragma once
#include "progression.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "session.hpp"
#include "business_ui_source.hpp"
namespace dnf {
enum class RegionPanel { None, Npc, Shop, Inventory, Quests, Results, NpcMenu, Advancement };
class RegionUi {
    BusinessUiSources uiSources_;
    int npcMenuPage_ = 0, npcQuestPage_ = 0, questPage_ = 0, textPage_ = 0, dialogueIndex_ = 0;
    bool completedQuests_ = false;
    bool dialogueAdvanceRequested_ = false;
    int inventorySelection_ = -1, shopPage_ = 0, questSelection_ = -1;
    // Source minimap panel has its own on-map toggle; state lives with the UI.
    bool minimapVisible_ = true;
    int inventoryTab_ = 0, bagTab_ = 0, bagPage_ = 0;
    bool previewMoving_ = false;
    bool bagSorted_ = false;
    bool inventorySelling_ = false;
    bool fitting_ = false;
    std::map<std::string, int> fittingItems_;
    int fittingSelection_ = -1;
    uint64_t inventoryMessageUntil_ = 0;
    void inventory(Renderer &, World &, Progression &, const CharacterAppearance &, int mx, int my, bool click, bool activate);
  public:
    void bindSources(Pvf &pvf) { uiSources_.bind(pvf); }
    Json sourceSnapshot() const { return uiSources_.snapshot(); }
    RegionPanel panel = RegionPanel::None;
    int npc = 2, dungeon = 1;
    bool changed = false, returnTown = false;
    bool equipmentPublished = false;
    bool learnSkillsRequested = false;
    std::optional<CharacterIdentity> advancementRequested;
    std::string message;
    bool open() const { return panel != RegionPanel::None; }
    Json snapshot() const { return {{"inventory_tab",inventoryTab_},{"bag_tab",bagTab_},{"bag_page",bagPage_},
        {"fitting",fitting_},{"fitting_items",fittingItems_},{"preview_moving",previewMoving_},
        {"npc",npc},{"message",message},{"npc_menu_page",npcMenuPage_},{"npc_quest_page",npcQuestPage_},
        {"quest_page",questPage_},{"text_page",textPage_},{"dialogue_index",dialogueIndex_},
        {"panel",int(panel)},{"completed_quests",completedQuests_}}; }
    void close() { panel = RegionPanel::None; inventorySelling_=false; fitting_=false; fittingItems_.clear(); dialogueAdvanceRequested_=false; }
    bool requestDialogueAdvance() { if(panel!=RegionPanel::Npc)return false; dialogueAdvanceRequested_=true; return true; }
    void openInventory(bool selling=false) { panel=RegionPanel::Inventory;inventorySelling_=selling; }
    void openNpc(int id, Progression &progress);
    void draw(Renderer &, World &, Progression &, const RegionSession &, const CharacterAppearance &, int mx,int my,bool click, bool activate=false);
    int drawDungeon(Renderer &, const Progression &, int mx,int my,bool click);
    void minimap(Renderer &,const RegionSession &,bool expanded=false);
    // Town/room panel. The parchment map is frame 0 of the source town minimap
    // IMG (640x424); TWN [minimap rect] entries index that same canvas, so the
    // panel crops around the current area and marks the player/NPCs.
    bool townMinimap(Renderer &, const std::vector<TownArea> &, int areaId, double playerX,
                     double playerY, int sceneWidth, int sceneHeight, const std::string &title,
                     const std::vector<MapNpc> &npcs, int mx, int my, bool click);
    bool townMinimapVisible() const { return minimapVisible_; }
};
void sourceWindow(Renderer &,int x,int y,int w,int h);
} // namespace dnf
