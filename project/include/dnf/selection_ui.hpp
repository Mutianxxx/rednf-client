#pragma once
#include "business_ui_render.hpp"
#include "dungeon_selection.hpp"
#include <array>
#include <cstdint>
#include <vector>

namespace dnf {

// Source whitelist only. UTF-8 decoding, composition and length policy are
// owned by TextInput, and existing saved names are not revalidated on load.
class CharacterNameSourceRules {
    Script allowed_, invalid_, slang_;
    std::vector<std::array<uint32_t,2>> ranges_;
  public:
    void bind(Pvf &);
    bool allows(uint32_t codepoint) const;
    Json snapshot() const;
};

// Centralized, version-bound art association inferred from the current 1031
// sheet and character registration. Never a substitute for a native loader.
struct CharacterCreationArt {
    int jobId = 0, background = 0, portrait = 38, button = 6;
    int logo = 46, description = 60, stats = 52;
    std::string classification = "inferred-1031-source-art-association";
};
const CharacterCreationArt *characterCreationArt(int jobId);

struct CharacterSelectionSlotView {
    bool occupied = false;
    int level = 1;
    std::string name, jobName;
    bool experimental = false;
    const CharacterAppearance *appearance = nullptr;
};
struct CharacterCreationJobView {
    int jobId = 0;
    std::string name;
    bool experimental = false, deferred = false;
};
struct SelectionUiPointer {
    int x = -1, y = -1;
    bool click = false;
};
struct CharacterSelectionAction {
    int selected = 0, page = 0;
    bool start = false, create = false, quit = false;
};
struct CharacterCreationAction {
    int selectedJob = 0;
    bool create = false, cancel = false, focusName = false;
};

// All coordinates below are the same 800x600 logical space as Renderer::ui.
// Native code supplies dynamic slot origins and several footer positions;
// these values are a single explicit reconstruction policy.
struct CharacterSelectionGeometry {
    static constexpr int slotCount = 20, slotsPerPage = 12;
    static SelectionRect slot(int visibleSlot);
    static int hitSlot(int page, SelectionPoint);
    static int clampPage(int page);
    static SelectionRect nameField();
    static SelectionRect creationJobButton(int visibleJob);
};

struct DungeonUiAlphaSegment { int64_t durationMs=0; double from=0,to=0; };
struct DungeonUiTransition { uint8_t bannerAlpha=0, cardsAlpha=255; bool cardsInteractive=true; };

class SelectionUi {
    Assets *assets_ = nullptr;
    BusinessUiLayout under_, over_, dungeonCommon_;
    CharacterNameSourceRules nameRules_;
    std::string sourceIdentity_;
    bool creationArtProfile_ = false;
    Script dungeonBannerAction_;
    std::vector<DungeonUiAlphaSegment> dungeonBannerAlpha_, dungeonCardsAlpha_;
    int64_t dungeonCardsDelayMs_ = 0;
    std::array<std::array<int,2>,9> boardMetrics_{};
    void drawImage(Renderer &,const BusinessUiLayout &,const BusinessUiControl &,
                   double dx=0,double dy=0) const;
    void drawLoopBoard(Renderer &) const;
  public:
    void bind(Pvf &,Assets &);
    bool bound() const { return assets_ != nullptr; }
    const CharacterNameSourceRules &nameRules() const { return nameRules_; }
    Json snapshot() const;
    CharacterSelectionAction drawCharacters(Renderer &,
        const std::array<CharacterSelectionSlotView,20> &,int selected,int page,
        SelectionUiPointer,int64_t wallMs,const std::string &message="") const;
    // The IME model draws text/preedit/caret in nameField() after this call.
    CharacterCreationAction drawCreation(Renderer &,
        const std::vector<CharacterCreationJobView> &,int selectedJob,
        bool nameCanSubmit,SelectionUiPointer,int64_t wallMs,
        const std::string &message="",bool transactionPending=false) const;
    DungeonSelectionLayout dungeonLayout(const DungeonSelectionModel &,int selectedDungeon=0) const;
    void startDungeonPresentation(DungeonSelectionState &,int64_t wallMs) const;
    DungeonUiTransition dungeonTransition(const DungeonSelectionState &,int64_t wallMs) const;
    void drawDungeon(Renderer &,const DungeonSelectionModel &,
        const DungeonSelectionLayout &,const DungeonSelectionState &,
        DungeonSelectionAdmission,SelectionUiPointer,int64_t wallMs) const;
};

Json runSelectionUiTests(Pvf &,Assets &);
Json runSelectionUiRuntimeTests(Pvf &,Assets &,const std::filesystem::path &output);
} // namespace dnf
