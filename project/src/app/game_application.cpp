#include "dnf/app/game_application.hpp"
#include "dnf/diagnostics/frame_statistics.hpp"
#include "dnf/pending_rewards.hpp"
#include "dnf/reward_recovery.hpp"
#include "dnf/audio.hpp"
#include "dnf/entry.hpp"
#include "dnf/renderer.hpp"
#include "dnf/storage.hpp"
#include "dnf/skill_learning_transaction.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/hud.hpp"
#include "dnf/target_hud.hpp"
#include "dnf/region_ui.hpp"
#include "dnf/world_map_ui.hpp"
#include "dnf/dungeon_selection.hpp"
#include "dnf/content_profile.hpp"
#include "dnf/content_catalog.hpp"
#include "dnf/debug_window.hpp"
#include "dnf/beta_branch.hpp"
#include "dnf/beta_branch_exit.hpp"
#include "dnf/beta_character.hpp"
#include "dnf/monster_attributes.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/monster_spawn.hpp"
#include "dnf/map_access.hpp"
#include "dnf/map_exploration.hpp"
#include "dnf/town_access.hpp"
#include "dnf/character_entry.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/skill_configuration_ui.hpp"
#include "dnf/skill_learning_ui.hpp"
#include "dnf/runtime_paths.hpp"
#include "dnf/selection_ui.hpp"
#include "dnf/portal_visuals.hpp"
#include "dnf/text_input.hpp"
#include "dnf/sdl_text_input.hpp"
#include "dnf/sdl_game_input.hpp"
#include "dnf/scene_presentation.hpp"
#include "dnf/dungeon_difficulty.hpp"
#include "dnf/drop_presentation.hpp"
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <set>
#include <windows.h>
#include <shlobj.h>
using namespace dnf;
namespace fs = std::filesystem;
static std::string resolve(const std::string &parent, const std::string &child) {
    return normalize((fs::path(parent).parent_path() / child).generic_string());
}
namespace dnf::app {
fs::path GameApplication::reportPath(const std::string &name) const { return reportDirectory_ / fs::u8path(name); }

namespace {
// Resource discovery happens before Renderer owns the SDL device. This small
// loading surface gives the user a visible heartbeat every 100 ms without
// parsing PVF/NPK data from the UI thread. The bar is intentionally a pulse,
// rather than a fabricated percentage: the underlying readers report exact
// counts only after each phase commits.
class LoadingProgress final {
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    bool closed_ = false;
    bool initialized_ = false;
    uint64_t pulse_ = 0;
public:
    explicit LoadingProgress(bool enabled) {
        if (!enabled) return;
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "Loading window unavailable: " << SDL_GetError() << std::endl;
            return;
        }
        initialized_ = true;
        window_ = SDL_CreateWindow("DNF - loading", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  720, 150, SDL_WINDOW_SHOWN);
        if (window_) renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer_) {
            std::cerr << "Loading renderer unavailable: " << SDL_GetError() << std::endl;
            if (window_) SDL_DestroyWindow(window_);
            window_ = nullptr;
        }
    }
    ~LoadingProgress() {
        if (renderer_) SDL_DestroyRenderer(renderer_);
        if (window_) SDL_DestroyWindow(window_);
        if (initialized_) SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
    bool available() const noexcept { return renderer_ != nullptr && !closed_; }
    void dismiss() noexcept {
        if (renderer_) { SDL_DestroyRenderer(renderer_); renderer_ = nullptr; }
        if (window_) { SDL_DestroyWindow(window_); window_ = nullptr; }
        if (initialized_) { SDL_QuitSubSystem(SDL_INIT_VIDEO); initialized_ = false; }
    }
    void update(const std::string &phase, const std::string &detail = {}) {
        ++pulse_;
        std::cout << "\r[loading] " << phase << (detail.empty() ? std::string() : " - " + detail)
                  << "    " << std::flush;
        if (!renderer_ || closed_) return;
        SDL_Event event;
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) { closed_ = true; return; }
        const auto title = std::string("DNF - ") + phase + (detail.empty() ? "" : " - " + detail);
        SDL_SetWindowTitle(window_, title.c_str());
        SDL_SetRenderDrawColor(renderer_, 12, 14, 22, 255); SDL_RenderClear(renderer_);
        SDL_Rect frame{35, 62, 650, 24};
        SDL_SetRenderDrawColor(renderer_, 75, 82, 103, 255); SDL_RenderDrawRect(renderer_, &frame);
        const int width = 10 + int((pulse_ % 100) * 6.3);
        SDL_Rect bar{frame.x + 2, frame.y + 2, std::min(frame.w - 4, width), frame.h - 4};
        SDL_SetRenderDrawColor(renderer_, 215, 177, 78, 255); SDL_RenderFillRect(renderer_, &bar);
        SDL_RenderPresent(renderer_);
    }
    void complete(const std::string &phase, const std::string &detail = {}) {
        if (renderer_ && !closed_) {
            pulse_ = 99; update(phase, detail);
            SDL_Delay(100);
        }
        std::cout << "\n";
    }
};

template <class Function>
auto runLoadingPhase(LoadingProgress &loading, const std::string &phase, Function &&function)
    -> std::invoke_result_t<Function> {
    using Result = std::invoke_result_t<Function>;
    std::packaged_task<Result()> task(std::forward<Function>(function));
    auto future = task.get_future();
    const auto started = std::chrono::steady_clock::now();
    std::thread worker(std::move(task));
    while (future.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) {
        const auto elapsed = std::chrono::duration<double>(std::chrono::steady_clock::now() - started).count();
        loading.update(phase, "working " + std::to_string(elapsed).substr(0, 4) + "s");
    }
    worker.join();
    loading.complete(phase, "complete");
    return future.get();
}

bool hasClientPvf(const fs::path &directory) {
    return fs::is_directory(directory) && fs::is_regular_file(directory / "Script.pvf");
}

bool hasImagePackDirectory(const fs::path &directory) {
    return fs::is_directory(directory / "ImagePacks2") &&
        std::filesystem::directory_iterator(directory / "ImagePacks2") != std::filesystem::directory_iterator{};
}

std::optional<fs::path> chooseDirectory(const wchar_t *title) {
#ifdef _WIN32
    const HRESULT comStatus = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    BROWSEINFOW request{};
    request.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    request.lpszTitle = title;
    PIDLIST_ABSOLUTE item = SHBrowseForFolderW(&request);
    if (!item) { if (SUCCEEDED(comStatus)) CoUninitialize(); return std::nullopt; }
    wchar_t selected[MAX_PATH]{};
    const bool converted = SHGetPathFromIDListW(item, selected) != FALSE;
    CoTaskMemFree(item);
    if (SUCCEEDED(comStatus)) CoUninitialize();
    if (!converted) return std::nullopt;
    return fs::path(selected);
#else
    return std::nullopt;
#endif
}
} // namespace
static int64_t addElapsed(int64_t base, int64_t delta) {
    if(base<0||delta<0||delta>std::numeric_limits<int64_t>::max()-base)
        throw std::overflow_error("Input timeline overflow");
    return base+delta;
}
// Window coordinates for IME; renderer coordinates for pixels. This helper
// never commits text or creates an SDL/World simulation event.
static void drawTextField(Renderer &render,const TextInputModel &input,
                          const SelectionRect &field,int64_t wallMs,int fontSize=15) {
    const auto prefix=input.beforeCaret(),preedit=input.composition(),suffix=input.afterCaret();
    const auto byteForCodepoint=[](const std::string &value,size_t count) {
        size_t offset=0;
        while(offset<value.size()&&count--){const auto c=uint8_t(value[offset]);offset+=c<0x80?1:c<0xe0?2:c<0xf0?3:4;}
        return offset;
    };
    const auto compositionByte=byteForCodepoint(preedit,input.compositionCaret());
    const auto prefixWidth=render.textWidth(prefix,fontSize);
    const auto compositionCaretWidth=render.textWidth(preedit.substr(0,compositionByte),fontSize);
    const auto caretWidth=prefixWidth+(input.composing()?compositionCaretWidth:0);
    const double left=field.x+4,top=field.y+1,available=std::max(1.0,field.width-8);
    const auto shift=std::max(0.0,double(caretWidth)-available+2);
    SDL_Rect previousClip{};const bool wasClipped=SDL_RenderIsClipEnabled(render.raw())==SDL_TRUE;
    SDL_RenderGetClipRect(render.raw(),&previousClip);
    SDL_Rect clip{int(field.x+2),int(field.y),std::max(1,int(field.width-4)),std::max(1,int(field.height))};
    SDL_RenderSetClipRect(render.raw(),&clip);
    render.text(prefix,float(left-shift),float(top),fontSize);
    const auto preeditX=left-shift+prefixWidth;
    if(input.compositionSelection()) {
        const auto selectionEnd=byteForCodepoint(preedit,input.compositionCaret()+input.compositionSelection());
        const auto selectedWidth=render.textWidth(preedit.substr(compositionByte,selectionEnd-compositionByte),fontSize);
        render.rect(float(preeditX+compositionCaretWidth),float(top),float(selectedWidth),float(fontSize+1),{70,79,117,255});
    }
    render.text(preedit,float(preeditX),float(top),fontSize,{255,220,125,255});
    const auto preeditWidth=render.textWidth(preedit,fontSize);
    render.text(suffix,float(preeditX+preeditWidth),float(top),fontSize);
    if(!preedit.empty())render.rect(float(preeditX),float(top+fontSize),float(std::max(1,preeditWidth)),1,{255,220,125,255});
    const auto caretX=left-shift+caretWidth;
    if(input.active()&&(wallMs/500)%2==0)render.rect(float(caretX),float(top+1),1,float(fontSize),{255,244,213,255});
    SDL_RenderSetClipRect(render.raw(),wasClipped?&previousClip:nullptr);
    if(input.active()) {
        int windowX=0,windowY=0,lowerX=0,lowerY=0;
        SDL_RenderLogicalToWindow(render.raw(),float(caretX),float(top),&windowX,&windowY);
        SDL_RenderLogicalToWindow(render.raw(),float(caretX+1),float(top+fontSize+3),&lowerX,&lowerY);
        SDL_Rect candidate{windowX,windowY,std::max(1,lowerX-windowX),std::max(1,lowerY-windowY)};
        SDL_SetTextInputRect(&candidate);
    }
}
int GameApplication::run(int argc, char **argv) {
    bool showFatalWindow=true;
    try {
        const auto invocationDirectory = fs::current_path();
        fs::path exe = fs::absolute(fs::u8path(argv[0]));
        const auto binaryHash = sha256File(exe);
        // Project-local isolated build directories may be nested under cache.
        // Locate the owning workspace without changing saves/client resolution.
        auto workspace = exe.parent_path();
        while (!workspace.empty() && !fs::exists(workspace / "CURRENT_TASK.md")) {
            auto parent = workspace.parent_path();
            if (parent == workspace) { workspace.clear(); break; }
            workspace = std::move(parent);
        }
        fs::current_path(workspace.empty() ? exe.parent_path().parent_path() : workspace);
        startedMs_ = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch()).count();
        runId_ = std::to_string(startedMs_) + "-" + std::to_string(GetCurrentProcessId());
        reportDirectory_ = fs::path("reports/runs") / runId_;
        fs::path client = fs::absolute(fs::u8path("../DNF1031客户端"));
        std::optional<fs::path> profilePath;
        ContentProfileOverrides profileOverrides;
        bool explicitClient = false, explicitSaveDirectory = false, importLegacySave = false, profileAudit = false, contentAudit = false;
        int autoSeconds = 0;
        int flowSceneSeconds = 30;
        bool autoRun = false, audit = false, flowSmoke = false, trace = false, effectsFixture = false;
        auto aniRenderProfile = ani_render::RenderProfile::Legacy1031;
        std::optional<ani_clock::ClockPolicy> aniClockPolicy;
        bool basicAttackMovement=true;
        int quitAfter = 0;
        std::string shot;
        for (int i = 1; i < argc; i++) {
            std::string a = argv[i];
            if (a == "--resolution" && i + 2 < argc) { /* applied after renderer creation */
                ++i;
                ++i;
            } else if (a == "--client" && i + 1 < argc) {
                client = fs::absolute(invocationDirectory / fs::u8path(argv[++i]));
                explicitClient = true;
            }
            else if (a == "--content-profile" && i + 1 < argc)
                profilePath = fs::u8path(argv[++i]);
            else if (a == "--pvf" && i + 1 < argc)
                profileOverrides.pvfPath = fs::u8path(argv[++i]);
            else if (a == "--resource-root" && i + 1 < argc)
                profileOverrides.resourceRoots.push_back(fs::u8path(argv[++i]));
            else if (a == "--ani-render-profile" && i + 1 < argc) {
                const std::string value = argv[++i];
                if (value == "legacy1031") aniRenderProfile = ani_render::RenderProfile::Legacy1031;
                else if (value == "inferred60us1031") aniRenderProfile = ani_render::RenderProfile::Inferred60Us1031;
                else throw std::runtime_error("Unknown ANI render profile: " + value);
            }
            else if (a == "--ani-clock-policy" && i + 1 < argc) {
                const std::string value = argv[++i];
                if (value == "legacy-scaled-local-age") aniClockPolicy.reset();
                else if (value == "source-delay-rate100") aniClockPolicy = ani_clock::ClockPolicy::SourceDelay100;
                else if (value == "inferred60us-percent-deadlines") aniClockPolicy = ani_clock::ClockPolicy::Inferred60UsPercentDeadlines;
                else throw std::runtime_error("Unknown ANI clock policy: " + value);
            }
            else if (a == "--basic-attack-movement" && i + 1 < argc) {
                const std::string value=argv[++i];
                if(value=="inferred-user-v1")basicAttackMovement=true;
                else if(value=="legacy-stationary")basicAttackMovement=false;
                else throw std::runtime_error("Unknown basic attack movement policy: "+value);
            }
            else if (a == "--import-legacy-save")
                importLegacySave = true;
            else if (a == "--profile-audit")
                profileAudit = true;
            else if (a == "--content-audit")
                contentAudit = true;
            else if (a == "--combat-effects-fixture") {
                effectsFixture = true;
                autoRun = true;
                trace = true;
            } else if (a == "--flow-smoke" && i + 1 < argc) {
                autoSeconds = std::stoi(argv[++i]);
                autoRun = true;
                flowSmoke = true;
            } else if (a == "--smoke" && i + 1 < argc) {
                autoSeconds = std::stoi(argv[++i]);
                autoRun = true;
            } else if (a == "--flow-scene-seconds" && i + 1 < argc) {
                flowSceneSeconds = std::max(2, std::stoi(argv[++i]));
            } else if (a == "--screenshot" && i + 1 < argc)
                shot = argv[++i];
            else if (a == "--audit")
                audit = true;
            else if (a == "--quit-after" && i + 1 < argc)
                quitAfter = std::stoi(argv[++i]);
            else if (a == "--run-id" && i + 1 < argc)
                runId_ = argv[++i];
            else if (a == "--report-dir" && i + 1 < argc)
                reportDirectory_ = fs::u8path(argv[++i]);
            else if (a == "--save-dir" && i + 1 < argc) {
                saveDirectory_ = fs::u8path(argv[++i]);
                explicitSaveDirectory = true;
            }
            else if (a == "--trace")
                trace = true;
            else
                throw std::runtime_error("Unknown or incomplete argument: " + a);
        }
        showFatalWindow=!(autoRun||audit||profileAudit||contentAudit||effectsFixture);
        if (effectsFixture && (flowSmoke || autoSeconds > 0 || audit))
            throw std::runtime_error("Combat-effects fixture cannot be combined with other diagnostic modes");
        const bool showLoading = showFatalWindow;
        LoadingProgress loading(showLoading);
        loading.update("Preparing content", "locating client PVF/NPK");
        bool manualContentSelected = false;
        // A packaged executable may sit directly beside Script.pvf and its
        // ImagePacks2/SoundPacks. Prefer that portable layout. If it is not
        // present, an interactive launch offers a folder picker; diagnostics
        // remain fail-fast and never open a modal dialog.
        const bool adjacentClient = !profilePath && !explicitClient && hasClientPvf(exe.parent_path());
        if (adjacentClient)
            client = exe.parent_path();
        if (!profilePath && !hasClientPvf(client) && showLoading) {
            const auto selectedClient = chooseDirectory(L"PVF 不在程序旁边。请选择包含 Script.pvf 的客户端目录");
            if (selectedClient && hasClientPvf(*selectedClient)) { client = *selectedClient; manualContentSelected = true; }
            else throw std::runtime_error("No usable client directory selected; Script.pvf is required");
        }
        if (!profilePath && !hasImagePackDirectory(client) && showLoading) {
            loading.update("Preparing content", "choose ImagePacks2 folder");
            const auto selectedNpk = chooseDirectory(L"程序目录缺少 ImagePacks2。请选择 ImagePacks2 NPK 目录");
            if (!selectedNpk) throw std::runtime_error("No ImagePacks2 directory selected");
            fs::path root = *selectedNpk;
            if (root.filename() == "ImagePacks2") root = root.parent_path();
            if (!hasImagePackDirectory(root))
                throw std::runtime_error("Selected folder must be the client root or its ImagePacks2 directory");
            if (root != client) {
                profileOverrides.resourceRoots = {root};
                manualContentSelected = true;
                loading.update("Preparing content", "PVF=" + client.u8string() + "; NPK=" + root.u8string());
            }
        }
        // A profile is consumed only when the launcher passes
        // --content-profile. Directly launching the executable therefore
        // follows the portable rule above and discovers the client beside the
        // binary (or asks for PVF/NPK roots), rather than silently selecting a
        // stale profile file from the build directory.
        loading.update("Preparing content", client.u8string());
        const auto profile = resolveContentProfile(profilePath, client, profileOverrides, invocationDirectory);
        if (profile.parserVersion != "dnf-source-v1" || profile.compatibilityProfileId != "1031-v1" ||
            (profile.ruleProfileId != "legacy-demo-v1" && profile.ruleProfileId != "beta-foundation-v1"))
            throw std::runtime_error("This candidate supports parser dnf-source-v1, compatibility 1031-v1 and rules legacy-demo-v1 or beta-foundation-v1 only");
        std::cout << "Fingerprinting PVF and static resources..." << std::endl;
        const auto contentIdentity = runLoadingPhase(loading, "Fingerprinting PVF/NPK", [&] { return profile.fingerprint(); });
        loading.update("Fingerprinting PVF/NPK", std::to_string(contentIdentity.manifest.size()) + " static files indexed");
        if (!explicitSaveDirectory) saveDirectory_ = defaultRuntimeSaveDirectory(exe,
            workspace.empty() ? fs::current_path() : workspace, contentIdentity.contentId, binaryHash);
        const auto contentCache = fs::path("cache/content") / contentIdentity.cacheId;
        fs::create_directories(contentCache);
        writeJson(contentCache / "effective-profile.json", profile.effective(contentIdentity));
        writeJson(contentCache / "static-manifest.json", contentIdentity.manifest);
        writeJson(reportPath("effective-profile.json"), profile.effective(contentIdentity));
        if (profileAudit) {
            writeJson(reportPath("run.json"), {{"run_id",runId_},{"status","completed"},{"mode","profile-audit"},
                {"binary_sha256",binaryHash}, {"frontend_started",false},
                {"identity",contentIdentity.json()},{"save_directory",saveDirectory_.u8string()},
                {"scope","File fingerprints and effective configuration only; no gameplay or frontend test"}});
            return 0;
        }
        // A visual fixture never opens a user-provided character directory.
        if (effectsFixture || (autoRun && !explicitSaveDirectory)) saveDirectory_ = reportDirectory_ / "saves";
        writeJson(reportPath("run.json"), {{"run_id", runId_}, {"started_unix_ms", startedMs_},
            {"status", "running"}, {"binary_sha256",binaryHash}, {"binary_path",exe.u8string()},
            {"save_directory",fs::absolute(saveDirectory_).u8string()}});
        std::cout << "Indexing PC PVF; content members load on demand..." << std::endl;
        auto loadedPvf = runLoadingPhase(loading, "Indexing PVF", [&] {
            return std::make_unique<Pvf>(profile.pvfPath, contentIdentity.pvfSha256);
        });
        Pvf &pvf = *loadedPvf;
        writeJson(reportPath("pvf-index.json"),{{"identity",pvf.identity()},{"loading",pvf.loadingStats()},
            {"members_read",pvf.reads()},{"scope","archive/string/translation directory only; no scene preparation"}});
        auto loadedAssets = runLoadingPhase(loading, "Indexing NPK", [&] {
            return std::make_unique<Assets>(profile.resourceRoots, pvf, contentIdentity.manifest);
        });
        Assets &assets = *loadedAssets;
        loading.update("Resources ready", std::to_string(pvf.count()) + " PVF members / " + std::to_string(assets.count()) + " NPK entries");
        if (contentAudit) {
            ContentCatalog sources(pvf);
            RegionCatalog region(pvf, assets);
            const auto graph = buildRegionCapabilityGraph(pvf, region);
            Json regions = Json::array();
            for (const auto &[id, definition] : region.dungeons)
                regions.push_back(graph.evaluate("beta.dungeon:" + std::to_string(id)).json());
            writeJson(reportPath("content-catalog.json"), sources.snapshot(true, false));
            MapAccessCatalog mapDirectory(pvf);
            writeJson(reportPath("all-map-index.json"),mapDirectory.indexSnapshot());
            TownAccessCatalog townDirectory(pvf);
            writeJson(reportPath("all-town-index.json"),townDirectory.json());
            writeJson(reportPath("capabilities.json"), {{"identity", contentIdentity.json()},
                {"scope", "Full source archive membership and current RegionCatalog beta gaps; source existence is not executable coverage"},
                {"world",graph.evaluate("beta.world").json()},
                {"regions",regions},{"graph",graph.snapshot()},{"static_index_errors",assets.errors}});
            writeJson(reportPath("run.json"), {{"run_id",runId_},{"status","completed"},{"mode","content-audit"},
                {"binary_sha256",binaryHash},
                {"identity",contentIdentity.json()},{"frontend_started",false},{"gameplay_gate_passed",false}});
            return 0;
        }
        World world(pvf, assets, profile.ruleProfileId == "beta-foundation-v1" ? WorldRules::BetaFoundationV1 : WorldRules::LegacyDemoV1);
        world.configureAnimationClock(aniClockPolicy);
        world.configureBasicAttackMovement(basicAttackMovement);
        writeJson(reportPath("basic-attack-movement-policy.json"),world.basicAttackMovementReport());
        writeJson(reportPath("ani-clock-policy.json"), world.animationClockReport());
        world.enableExperimentalCharacters();
        world.configureSourceActions(contentIdentity.archiveManifestHash,true);
        world.configureMonsterActionAi("easy");
        world.configureSquirrelActions(contentIdentity.archiveManifestHash);
        RegionCatalog catalog(pvf,assets,RegionPreparation::OnDemand);
        auto dungeonSelectionModel = captureDungeonSelectionModel(pvf, catalog);
        WorldMapUi worldMapUi;bool worldMapBound=false;
        SelectionUi selectionUi;selectionUi.bind(pvf,assets);
        const auto selectionSource=selectionUi.snapshot();
        const bool creationArtProfileSupported=selectionSource.value("creation_art_profile_supported",false);
        writeJson(reportPath("selection-ui-source.json"),selectionSource);
        auto dungeonSelectionLayout = selectionUi.dungeonLayout(dungeonSelectionModel);
        DungeonSelectionState dungeonSelectionState;
        Progression progress(catalog);
        auto playerAppearance = progress.appearance(pvf, world.characterCatalog(), world.identity());
        std::map<int, std::pair<std::string, CharacterAppearance>> selectionAppearances;
        RegionSession session;
        RegionUi regionUi;
        regionUi.bindSources(pvf);
        writeJson(reportPath("business-ui-source.json"),regionUi.sourceSnapshot());
        TargetHud targetHud;
        int64_t submittedNs = world.simulationNanoseconds();
        if (audit) {
            Json maps = Json::array();
            for (const char *path : {"map/elvengard/(r)gate.map", "map/elvengard/elvengard.map",
                                     "map/elvengard/d_elvengard.map", "map/lorien/s0.map",
                                     "map/lorien/4.map", "map/lorien/6.map", "map/lorien/b1.map"}) {
                Scene s; s.load(pvf, assets, path);
                int blockedObjects = int(std::count_if(s.objects.begin(), s.objects.end(),
                    [](const MapObject &o) { return !o.destroyed && o.passType == "[do not pass]"; }));
                Json objectAudit = Json::array();
                for (const auto &o : s.objects)
                    objectAudit.push_back({{"id", o.id}, {"x", o.x}, {"y", o.y}, {"z", o.z},
                                           {"source", o.source}, {"pass_type", o.passType},
                                           {"width", o.width}, {"height", o.height},
                                            {"breakable_candidate", o.breakable},
                                            {"identity", o.identity.json()}});
                maps.push_back({{"path", path}, {"width", s.width}, {"walk_rects", s.walkRects.size()},
                                 {"objects", s.objects.size()}, {"blocked_objects", blockedObjects},
                                 {"blocked_rects", s.blockedRects}, {"object_details", objectAudit},
                                 {"issues", s.issues}, {"tile_grids", s.tileGrids}});
            }
            writeJson(reportPath("audit.json"), {{"run_id", runId_}, {"maps", maps},
                      {"scope", "map loading only; no visual or input verification"}});
            writeJson(reportPath("resources.json"), {{"run_id", runId_}, {"pvf_reads", pvf.reads()},
                      {"npk_reads", assets.reads()}, {"scope", "actually accessed by map audit"}});
            writeJson(reportPath("run.json"), {{"run_id", runId_}, {"started_unix_ms", startedMs_},
                                               {"status", "completed"}, {"mode", "audit"}});
            return 0;
        }
        std::cout << "PVF " << pvf.count() << " NPK entries " << assets.count() << std::endl;
        const auto imeInternal=SDL_SetHint(SDL_HINT_IME_INTERNAL_EDITING,"0");
        const auto imeNative=SDL_SetHint(SDL_HINT_IME_SHOW_UI,"1");
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER))
            throw std::runtime_error(SDL_GetError());
        loading.dismiss();
        Renderer render(assets);
        SDL_StopTextInput();
        writeJson(reportPath("ime-policy.json"),{{"internal_editing_hint_set",imeInternal==SDL_TRUE},
            {"native_candidate_hint_set",imeNative==SDL_TRUE},
            {"internal_editing",SDL_GetHint(SDL_HINT_IME_INTERNAL_EDITING)?SDL_GetHint(SDL_HINT_IME_INTERNAL_EDITING):""},
            {"native_candidate_ui",SDL_GetHint(SDL_HINT_IME_SHOW_UI)?SDL_GetHint(SDL_HINT_IME_SHOW_UI):""},
            {"scope","Application preedit, native candidate UI; actual Windows IME behavior requires user verification"}});
        render.setRenderProfile(aniRenderProfile);
        world.configureRenderProfile(render.renderProfile());
        writeJson(reportPath("ani-render-policy.json"), render.renderProfileReport());
        Hud hud(pvf, assets);
        writeJson(reportPath("hud-source.json"), hud.sourceReport());
        Audio audio(assets);
        Scene scene;
        world.setObjectTick([&](World &simulation) { scene.updateObjects(simulation, pvf, assets); });
        Json clientSettings = Json::object();
        if (fs::exists(saveDirectory_ / "settings.json")) {
            try {
                auto loaded = Json::parse(readFile(saveDirectory_ / "settings.json"));
                if (loaded.is_object()) clientSettings = std::move(loaded);
            } catch (const std::exception &error) {
                std::cerr << "Settings preserved; using defaults: " << error.what() << std::endl;
            }
        }
        DemoBalance demoBalance = DemoBalance::fromJson(clientSettings.value("demo_balance", Json()));
        AudioVolumes audioVolumes = AudioVolumes::fromJson(clientSettings.value("audio", Json()));
        auto applyAudioVolumes = [&] {
            audio.setVolumes(float(audioVolumes.master), float(audioVolumes.music),
                             float(audioVolumes.effects), float(audioVolumes.ambient));
        };
        auto saveSettings = [&] {
            for (const auto &group : {std::make_pair("demo_balance", demoBalance.describe()),
                                      std::make_pair("audio", audioVolumes.describe())}) {
                if (!clientSettings.contains(group.first) || !clientSettings[group.first].is_object())
                    clientSettings[group.first] = Json::object();
                clientSettings[group.first].update(group.second);
            }
            atomicJson(saveDirectory_ / "settings.json", clientSettings);
        };
        applyAudioVolumes();
        audio.music("M_CHARACTER_SELECT");
        Json displayConfig = Json::object();
        if (fs::exists(saveDirectory_ / "display.json")) {
            try {
                displayConfig = Json::parse(readFile(saveDirectory_ / "display.json"));
                render.resize(displayConfig.value("width", 800), displayConfig.value("height", 600));
                render.setVsync(displayConfig.value("vsync", true));
                render.fullscreen(displayConfig.value("fullscreen", false));
            } catch (...) {
            }
        }
        for (int i = 1; i + 2 < argc; i++)
            if (std::string(argv[i]) == "--resolution") {
                render.resize(std::stoi(argv[i + 1]), std::stoi(argv[i + 2]));
                break;
            }
        CharacterStore store(saveDirectory_, contentIdentity.contentId, importLegacySave);
        Json &saves = store.data;
        BetaSaveBranch testBranch;
        SkillLearningTransaction learningTransaction;
        CharacterAdvancementTransaction advancementTransaction;
        auto savePending = [&] { return learningTransaction.pending() || advancementTransaction.pending() || testBranch.select(store).hasPendingCommit(); };
        PendingRewardService rewardService;
        uint64_t betaForkAttempt=0;
        bool quitRequested=false;
        auto businessBlocked=[&] {return savePending() || rewardService.blocked(progress) || quitRequested;};
        DebugService debugService;
        std::unique_ptr<DebugWindow> debugWindow;
        uint64_t debugGeneration = 1, savedDebugRevision = 0;
        if (fs::exists(saveDirectory_ / "beta-settings.json")) {
            try { debugService.loadConfiguration(Json::parse(readFile(saveDirectory_ / "beta-settings.json"))); }
            catch (const std::exception &error) { std::cerr << "Beta settings preserved; using disabled defaults: " << error.what() << std::endl; }
        }
        int selected = 0, page = 0;
        int createJob = 0;
        SkillConfigurationUi skillConfigurationUi;
        SkillLearningUi skillLearningUi(pvf,assets);
        bool configureSkills = false;
        auto characterName = [&](int jobId) {
            const auto &definition=world.characterCatalog().at(jobId);
            if(!definition.growtypeNames.empty()&&definition.growtypeNames[0].is_string())
                return definition.growtypeNames[0].get<std::string>();
            return definition.job;
        };
        std::string name = "";
        enum Screen { Select, Create, Game };
        Screen screen = Select;
        std::string location = "room";
        bool settingsMenu = false;
        bool menu = false, map = false, skillMenu = false, dialog = false, selectDungeon = false,
             debug = false, quit = false;
        int room = 0;
        std::vector<std::vector<Actor>> roomStates(3);
        std::vector<bool> visited(3,false);
        bool resultShown=false;
        int64_t transitionUntil = 0;
        ScenePresentation scenePresentation;
        std::map<int,DropSprite> dropSprites;
        std::optional<DropSprite> goldDropSprite;
        auto itemDropSprite=[&](int id)->const DropSprite& {
            auto found=dropSprites.find(id);
            if(found!=dropSprites.end())return found->second;
            DropSprite sprite;
            try {
                const auto *item=progress.item(id);
                if(!item)throw std::runtime_error("Drop item ID has no source registration");
                sprite=prepareDropSprite(assets,item->source);sprite.evidence["name"]=item->name;
            }catch(const std::exception &error) {
                sprite.diagnostics.push_back({{"kind","drop_item_source_failure"},{"id",id},{"error",error.what()}});
            }
            writeJson(reportPath("drops/item-"+std::to_string(id)+".json"),
                {{"source",sprite.evidence},{"diagnostics",sprite.diagnostics}});
            return dropSprites.emplace(id,std::move(sprite)).first->second;
        };
        auto beginScenePresentation=[&](const Script &source,const std::string &name) {
            world.releaseInputs();
            scenePresentation.begin(prepareScenePresentation(pvf,assets,source,name),int64_t(SDL_GetTicks64()));
            writeJson(reportPath("scene-presentation.json"),scenePresentation.snapshot(int64_t(SDL_GetTicks64())));
            // Show the actual source artwork before synchronous preparation.
            // PVF/Assets remain single-owner; no unsafe background cache writes.
            render.begin();drawScenePresentation(render,scenePresentation,int64_t(SDL_GetTicks64()));render.present();
        };
        auto nearestPickup=[&]() {
            std::string result;double closest=1e100;
            if(!session.active()||location!="dungeon")return result;
            for(auto it=progress.state["drops"].begin();it!=progress.state["drops"].end();++it) {
                const auto &drop=it.value();
                if(drop.value("claimed",false)||drop.value("run",std::string())!=session.run.token||
                    drop.value("room",-1)!=session.run.current)continue;
                const auto dx=world.player.x-drop.value("x",0.0),dy=world.player.y-drop.value("y",0.0);
                if(std::abs(dx)>=55||std::abs(dy)>=35)continue;
                const auto distance=dx*dx+dy*dy;
                if(distance<closest){closest=distance;result=it.key();}
            }
            return result;
        };
        std::string message;
        DungeonPortalSourceCache portalObjects;
        std::unordered_set<std::string> portalDiagnostics;
        auto observePortalBoundary = [&] {
            if(location!="dungeon")return;
            const auto identity=scene.path+":"+std::to_string(debugGeneration);
            const bool open=world.combat&&std::all_of(world.monsters.begin(),world.monsters.end(),[](const Actor &m){return m.dead;});
            const auto gates=scene.script.values("[pathgate pos]");
            const int dungeon=session.active()&&!autoRun?session.run.dungeonId:1;
            const auto owner=catalog.dungeons.find(dungeon);if(owner==catalog.dungeons.end())return;
            for(int d=0;d<4;++d) {
                const int destination=session.active()&&!autoRun?session.run.destination(Direction(d)):
                    d==0&&room>0?room-1:d==1&&room<2?room+1:-1;
                if(destination<0||gates.size()<size_t(d*2+2))continue;
                const bool boss=session.active()&&!autoRun?session.run.rooms[destination].boss:destination==2;
                const auto &source=portalObjects.resolve(pvf,owner->second,Direction(d),boss);
                if(source.available)render.observePortal(identity,d,source.object,world.nowMs(),open);
            }
        };
        std::unique_ptr<MapAccessCatalog> allMaps;
        MapAccessPage mapPage;
        std::optional<MapAccessEntry> explorationMap;
        TownAccessCatalog allTowns(pvf);
        std::optional<TownLocation> townLocation, returnTown, loginTown;
        CharacterEntryService characterEntry(pvf,assets,catalog,allTowns);
        bool townBrowser = false;
        bool mapBrowser = false;
        bool mapQueryDirty = false;
        std::string mapQuery,mapAppliedQuery;
        size_t mapOffset = 0;
        std::optional<size_t> selectedMap;
        TextInputModel textInput;
        bool textInputRunning=false,mainWindowFocused=SDL_GetKeyboardFocus()==render.window();
        bool textBatchActive=false,textBatchTraffic=false;
        bool creationCommitPending=false;
        auto synchronizeTextScope=[&] {
            const auto wanted=autoRun||effectsFixture||businessBlocked()?TextInputField::None:
                screen==Create?TextInputField::CharacterName:
                screen==Game&&mapBrowser?TextInputField::MapQuery:TextInputField::None;
            if(wanted!=textInput.field()) {
                if(wanted==TextInputField::None)textInput.deactivate();
                else if(wanted==TextInputField::CharacterName)
                    textInput.activate(wanted,name,TextInputPolicy::characterName([&](uint32_t cp){return selectionUi.nameRules().allows(cp);}));
                else textInput.activate(wanted,mapQuery,TextInputPolicy::mapQuery());
                if(textBatchActive)textInput.beginEventBatch(textBatchTraffic);
            }
            textInput.setFocused(mainWindowFocused);
            if(textInput.active()!=textInputRunning) {
                textInputRunning=textInput.active();
                if(textInputRunning)SDL_StartTextInput();
                else {SDL_ClearComposition();SDL_StopTextInput();}
            }
        };
        auto createCharacter=[&] {
            if(screen!=Create||businessBlocked()||creationCommitPending||!textInput.canSubmit())return;
            name=textInput.text();
            if(!saves["characters"][selected].is_null()){message="当前角色槽位已被占用，请返回重新选择。";return;}
            const auto previous=saves["characters"][selected];
            try {
                const auto &definition=world.characterCatalog().at(createJob);
                if(definition.runtimeDeferredByUser)throw std::runtime_error("该职业暂缓开放");
                saves["characters"][selected]={{"name",name},
                    {"class",fs::u8path(definition.registration.path).stem().u8string()},
                    {"identity",CharacterIdentity{createJob,0,0}.json()},{"level",1},{"weapon",0},
                    {"skill_initialization","source-v1"}};
                store.save();screen=Select;message="角色已创建并保存。";
            }catch(const std::exception &error) {
                creationCommitPending=store.hasPendingCommit();
                if(!creationCommitPending)saves["characters"][selected]=previous;
                message="创建保存失败："+std::string(error.what());
            }
            synchronizeTextScope();
        };
        auto beginCharacterCreation=[&] {
            if(businessBlocked()||!saves["characters"][selected].is_null())return;
            if(!creationArtProfileSupported) {
                message="当前PVF尚无已核实的角色创建图集映射。";return;
            }
            screen=Create;name.clear();message.clear();creationCommitPending=false;synchronizeTextScope();
        };
        Json explorationDiagnostics = Json::array();
        bool full = (SDL_GetWindowFlags(render.window()) & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
        int resolutionIndex = 0;
        int windowWidth = displayConfig.value("width", 800), windowHeight = displayConfig.value("height", 600);
        if (!full) SDL_GetWindowSize(render.window(), &windowWidth, &windowHeight);
        auto saveDisplay = [&] {
            atomicJson(saveDirectory_ / "display.json", {{"width", windowWidth}, {"height", windowHeight},
                        {"vsync", render.vsync}, {"fullscreen", full}});
        };
        auto captureRegionSession = [&](const std::string &where) {
            auto state=session.save(world,where);
            if(!explorationMap)state.erase("exploration_map");
            allTowns.attachState(state,townLocation,returnTown);
            if(loginTown)state["login_town"]=allTowns.validateLocation(loginTown->json()).json();
            else state.erase("login_town");
            return state;
        };
        auto persist = [&]() -> bool {
            if (savePending()) { message="保存尚未完成，请先重试当前提交"; return false; }
            if (!autoRun && screen == Game) { auto &writer = testBranch.select(store);
                try {
                    writer.capture(selected, world, progress);
                    if (location == "dungeon" && session.active())
                        session.objects[std::to_string(session.run.current)] = scene.saveObjects(world.nowMs());
                    auto regionState=captureRegionSession(explorationMap?"town":location);
                    if(explorationMap) {
                        regionState["exploration_map"]=explorationMap->json();
                        // Exploration coordinates/status belong to the isolated
                        // preview, never to the normal town restoration point.
                        regionState.erase("player");
                    }
                    writer.data["characters"][selected]["region_session"]=std::move(regionState);
                    if(testBranch.active()) writer.data["beta_overrides"] = debugService.snapshot().json();
                    writer.save();
                    if(!rewardService.acknowledgeCheckpoint(progress,world,writer,selected))
                        throw std::runtime_error(rewardService.diagnostic().dump());
                } catch(const std::exception &error) { message="保存失败："+std::string(error.what()); return false; }
            }
            return true;
        };
        RewardRecoveryReporter rewardReporter(reportPath("reward-pending.json"));
        auto rewardFailure=[&](const std::string &error=std::string()) {
            world.releaseInputs();
            auto diagnostic=rewardService.diagnostic();
            if(!error.empty())diagnostic["recovery_error"]=error;
            const auto cause=error.empty()?diagnostic.value("error",std::string()):error;
            message="奖励事务尚未完成，已暂停操作；可重试。"+cause;
            if(rewardReporter.publish(diagnostic)==RewardDiagnosticResult::Unavailable)
                message+=" 报告写入失败，错误显示在当前窗口，并已尝试输出调试日志。";
        };
        auto captureRewards=[&] {
            if(autoRun || screen!=Game)return true;
            try {
                if(location=="dungeon"&&session.active()) {
                    session.objects[std::to_string(session.run.current)]=scene.saveObjects(world.nowMs());
                    session.remember(world);
                    if(!rewardService.observe(progress,world,session,captureRegionSession(location))) {rewardFailure();return false;}
                } else if(!rewardService.observe(progress,world,session,Json::object())) {rewardFailure();return false;}
                return true;
            }catch(const std::exception &error) {
                rewardService.captureFailure(error.what());
                rewardFailure(error.what());return false;
            }
        };
        RewardRecoveryFlow rewardRecovery(rewardService,progress,world,catalog);
        const RewardRecoveryHooks rewardRecoveryHooks{savePending,captureRewards,persist,
            [&] {playerAppearance=world.characterAppearance();},
            [&](const std::string &error) {rewardFailure(error);}};
        auto pumpRewards=[&] {
            if(autoRun || screen!=Game)return true;
            return rewardRecovery.pump(rewardRecoveryHooks);
        };
        auto debugContext = [&] {
            DebugTarget target{contentIdentity.contentId,"",session.active()?session.run.token:"town",debugGeneration};
            if(screen==Game && saves["characters"][selected].is_object())
                target.characterUuid = saves["characters"][selected].value("uuid",std::string());
            return DebugContext{target,progress.level(),false};
        };
        auto ensureTestBranch = [&] {
            if(testBranch.active()) return;
            if(autoRun || screen!=Game) throw std::runtime_error("Select a normal character before enabling beta tests");
            if(!persist()) throw std::runtime_error("Complete the normal save before forking beta tests");
            if(businessBlocked()) throw std::runtime_error("Complete the pending normal save before forking beta tests");
            if(betaForkAttempt==std::numeric_limits<uint64_t>::max())throw std::overflow_error("Beta fork attempt exhausted");
            const auto directory=saveDirectory_/"beta-tests"/(runId_+"-"+std::to_string(debugGeneration)+"-fork-"+std::to_string(++betaForkAttempt));
            try {
                testBranch.fork(store,directory,{{"run_id",runId_},{"binary_sha256",binaryHash},{"selected_slot",selected}});
                if(!rewardService.switchCheckpointWriter(progress,world,testBranch.select(store),selected))
                    throw std::runtime_error(rewardService.diagnostic().dump());
            }catch(...) {
                // fork owns unpublished partial writers. Preserve their files
                // and every normal pending root; only close a published branch.
                if(testBranch.active())testBranch.close();
                throw;
            }
            message = "已进入隔离测试分支；返回选角恢复正常进度。";
        };
        bool debugBoundaryPaused = false;
        auto applyDebugBoundary = [&](World &simulation) {
            if (businessBlocked()) return;
            auto context = debugContext(); context.simulationPaused=debugBoundaryPaused;
            if(debugService.hasEnableRequest(context.target)) ensureTestBranch();
            debugService.applyAtBoundary(simulation,context);
            simulation.refreshExplorationMonsterEventAiTestPolicy();
            debugService.refresh(simulation,context);
            if(savedDebugRevision!=debugService.snapshot().revision) {
                atomicJson(saveDirectory_/"beta-settings.json",debugService.configuration());
                savedDebugRevision=debugService.snapshot().revision;
            }
        };
        world.setBeforeTick([&](World &simulation) {
            applyDebugBoundary(simulation);
            observePortalBoundary();
        });
        auto showDebugWindow = [&] {
            try {
                if(!debugWindow) debugWindow=std::make_unique<DebugWindow>(assets,debugService);
                debugWindow->show(); world.releaseInputs();
            } catch(const std::exception &error) { message="测试窗口初始化失败："+std::string(error.what()); }
        };
        auto leaveTestBranch = [&]() -> bool {
            if(!testBranch.active())return persist();
            auto context=debugContext();context.simulationPaused=true;
            const auto result=leaveBetaSaveBranch(testBranch,store,rewardService,progress,world,debugService,
                context,debugGeneration,selected,persist);
            if(!result.ok)message="退出测试分支未完成，保留当前现场；请重试保存后再次返回选角。"+result.error;
            return result.ok;
        };
        auto purchaseSkill = [&](SkillKey key,const SkillLearningQuote &quote) {
            if (businessBlocked() || !quote.accepted() || !(quote.key==key) || key.jobId!=world.identity().jobId) return;
            if(testBranch.active()&&!world.debugOverrides().enabled)return;
            const std::string uuid=saves["characters"][selected].value("uuid",std::string());
            SkillLearningRequest request{std::string(testBranch.active()?"test-skill:":"skill:")+uuid+":"+
                std::to_string(quote.revision)+":"+std::to_string(key.jobId)+":"+std::to_string(key.skillId)+":"+std::to_string(quote.targetLevel),
                key,quote.revision,quote.targetLevel};
            if(testBranch.active()) { message=world.learnTestSkill(request).message; persist(); }
            else {
                const auto result=learningTransaction.submit(store,selected,world,progress,request,captureRegionSession(location));
                message=result.message;
                if(learningTransaction.pending()) world.releaseInputs();
            }
        };
        double camera = 0;
        size_t audioEvent = 0;
        int64_t npcVoice = -12000;
        std::vector<std::string> rooms = {"map/lorien/s0.map", "map/lorien/4.map", "map/lorien/b1.map"};
        auto loadScene = [&](const std::string &where) {
            // Shared by smoke/autoRun/effects fixtures and normal door hops.
            // Prepare before changing the live scene, including Lorien.
            if(where=="dungeon") {
                const int requested=session.active()&&!autoRun?session.run.dungeonId:1;
                const auto prepared=catalog.prepareDungeon(requested);
                writeJson(reportPath("dungeon-dependencies.json"),prepared);
                if(prepared.at("status")!="prepared")throw std::runtime_error("Dungeon source dependencies unavailable: "+prepared.dump());
            }
            const int areaId = where == "room" ? 1 : where == "town" ? 0 : where == "entrance" ? 2 : -1;
            const auto townArea = catalog.townArea(areaId);
            const std::string path = townArea ? townArea->resolvedPath
                : session.active() && !autoRun ? session.run.room().path : rooms.at(room);
            Scene preparedScene;
            preparedScene.load(pvf,assets,path,session.active() && where=="dungeon"?session.run.token:"town",
                session.active() && where=="dungeon"?std::to_string(session.run.current):where);
            if(where=="dungeon" && session.active() && !autoRun) {
                const auto key=std::to_string(session.run.current);
                if(session.objects.is_object() && session.objects.contains(key))
                    preparedScene.restoreObjects(session.objects.at(key),world.nowMs());
            }
            const WalkGeometryView nextGeometry{preparedScene.width,preparedScene.walkRects,preparedScene.blockedRects};
            const bool savedActors=where=="dungeon" && session.active() && !autoRun &&
                !session.roomStates.at(session.run.current).is_null();
            std::vector<Actor> preparedActors;
            std::vector<Event> preparedSpawnEvents;
            if(savedActors) {
                // Validate saved source/visual dependencies before retiring the
                // current room. RegionSession publishes its statuses afterwards.
                for(const auto &row:session.roomStates.at(session.run.current)) {
                    auto actor=loadActor(row,world.nowMs());
                    world.restoreMonsterAttributes(actor);world.restoreMonsterVisuals(actor);
                    preparedActors.push_back(std::move(actor));
                }
            } else if(where=="dungeon" && autoRun && visited.at(room)) preparedActors=roomStates.at(room);
            else if(where=="dungeon") {
                const auto hpPolicy=session.active() && !autoRun?session.monsterStatPolicy:
                    world.usesSourceGrowth()?MonsterHpPolicy::inferredMobTableHpV1().id:"legacy-demo-v1";
                const auto combatPolicy=session.active() && !autoRun?session.monsterCombatPolicy:
                    world.usesSourceGrowth()?MonsterCombatAttributePolicy::inferredMobCombatTableV1().id:"legacy-snapshot-damage-v1";
                const int sourceDungeon=session.active() && !autoRun?session.run.dungeonId:1;
                preparedActors=prepareSourceMonsterSpawns(world,catalog,preparedScene.script,sourceDungeon,
                    catalog.dungeons.at(sourceDungeon).basisLevel,preparedScene.bg,hpPolicy,combatPolicy,
                    session.active() && !autoRun?session.balance:demoBalance,&preparedSpawnEvents,&nextGeometry,
                    session.active() && !autoRun?session.monsterLevelPolicy:MonsterLevelPolicy{});
            }
            world.validateSceneActorCapacity(preparedActors.size());
            writeJson(reportPath("scene-preparation.json"),{{"map",path},{"actors",preparedActors.size()},
                {"location",where},{"pvf_loading",pvf.loadingStats()},{"status","prepared"},
                {"scope","next-scene source dependencies prepared before live scene replacement"}});
            if(debugGeneration==std::numeric_limits<uint64_t>::max()) throw std::overflow_error("Debug target generation exhausted");
            ++debugGeneration;
            explorationMap.reset();explorationDiagnostics=Json::array();
            if (location == "entrance" && where != "entrance")
                leaveDungeonEntrance(dungeonSelectionState);
            location = where;
            if(where=="room" || where=="town" || where=="entrance")
                townLocation=allTowns.location(allTowns.require(1,where=="room"?1:where=="entrance"?2:0));
            world.configureMonsterActionAi(where=="dungeon"&&session.active()&&!autoRun?session.monsterAiDifficulty():"easy");
            world.changeScene();
            world.monsters.clear();
            targetHud.reset();
            regionUi.close();
            world.combat = where == "dungeon";
            scene=std::move(preparedScene);
            audio.scene(scene.script.values("[sound]"));
            world.mapWidth = scene.width;
            world.walkRects = scene.walkRects;
            world.blockedRects = scene.blockedRects;
            if (where == "dungeon" && session.active() && !autoRun) {
                scene.rebuildObstacles(world);
            }
            world.player.x = world.player.px = where == "room" ? 470 : 80;
            world.player.y = world.player.py = where == "room" ? 330 : 340;
            if (townArea && townArea->kind == "gate") {
                world.player.x = world.player.px = townArea->spawnX;
                world.player.y = world.player.py = townArea->spawnY + scene.bg;
            }
            if (where == "dungeon" && session.active() && !autoRun && session.restore(world)) {
                // Room actors are rebased to this simulation clock by RegionSession.
            } else if (where == "dungeon") {
                if(autoRun)visited[room]=true;
                world.monsters=std::move(preparedActors);
                world.events.insert(world.events.end(),preparedSpawnEvents.begin(),preparedSpawnEvents.end());
            }
            if (where == "dungeon") {
                auto spawn = scene.script.values("[dungeon start area]");
                if (spawn.size() >= 4) {
                    world.player.x = world.player.px = spawn[0].get<double>() + spawn[2].get<double>() / 2;
                    world.player.y = world.player.py =
                        scene.bg + spawn[1].get<double>() + spawn[3].get<double>() / 2;
                }
            }
            world.recoverPosition(world.player);
            scene.updateNpcs(world, where == "dungeon" && session.active() && session.run.complete() && session.run.room().boss);
            camera = std::clamp(world.player.x - 400.0, 0.0, std::max(0.0, scene.width - 800.0));
            std::cout << "SCENE " << path << " width " << scene.width << " walk " << world.walkRects.size()
                      << std::endl;
        };
        auto finishTownPublication = [&](PreparedTownArea &prepared) {
            if(townLocation && townLocation->townId==prepared.location.townId && townLocation->areaId==prepared.location.areaId)
                prepared.location.preserved=townLocation->preserved;
            townLocation=std::move(prepared.location);location=townRuntimeLocation(*townLocation);
            explorationMap.reset();explorationDiagnostics=std::move(prepared.diagnostics);
            world.synchronizeEntityHandles();scene.updateNpcs(world,false);
            ++debugGeneration;submittedNs=world.simulationNanoseconds();audioEvent=world.events.size();
            resultShown=false;room=0;mapBrowser=false;synchronizeTextScope();
            camera=std::clamp(world.player.x-400.0,0.0,std::max(0.0,scene.width-800.0));
            transitionUntil=world.nowMs()+650;audio.scene(scene.script.values("[sound]"));
        };
        auto publishTown = [&](PreparedTownArea &&prepared) {
            if(debugGeneration==std::numeric_limits<uint64_t>::max())throw std::overflow_error("Debug target generation exhausted");
            world.validateSceneActorCapacity(0);
            auto walks=prepared.scene.walkRects,blocks=prepared.scene.blockedRects;
            world.configureMonsterActionAi("easy");
            world.changeScene();if(session.active())session.clear();targetHud.reset();regionUi.close();
            dungeonSelectionState.open=false;selectDungeon=false;leaveDungeonEntrance(dungeonSelectionState);
            scene=std::move(prepared.scene);world.monsters.clear();world.combat=false;
            world.walkRects.swap(walks);world.blockedRects.swap(blocks);world.mapWidth=scene.width;
            world.player.x=world.player.px=prepared.spawn[0];world.player.y=world.player.py=prepared.spawn[1];
            world.player.z=world.player.pz=0;world.player.vx=world.player.vy=world.player.vz=0;
            finishTownPublication(prepared);
        };
        auto enterTownArea = [&](size_t index, const std::optional<TownLocation> &from=std::optional<TownLocation>{}, bool revive=false) {
            if(businessBlocked()){message="请先完成奖励或保存事务，再切换城镇。";return false;}
            bool presenting=false;
            try {
                const auto &target=allTowns.at(index);
                if(screen==Game&&townLocation&&townLocation->townId!=target.townId) {
                    beginScenePresentation(pvf.script(target.townPath),target.townName);presenting=true;
                }
                auto prepared=prepareTownArea(pvf,assets,world,catalog,allTowns,index,from);
                if(!prepared.ok) {writeJson(reportPath("town-entry-error.json"),prepared.json());
                    if(presenting)scenePresentation.cancel();
                    message="城镇准备未通过，保留当前现场；详情见 town-entry-error.json。";return false;}
                if(debugGeneration==std::numeric_limits<uint64_t>::max())throw std::overflow_error("Debug target generation exhausted");
                world.validateSceneActorCapacity(0);
                Json homeTrace;
                auto nextLoginTown=characterEntry.roomFor(prepared.location,loginTown,&homeTrace);
                auto report=prepared.json();report["login_room"]=std::move(homeTrace);
                if(!persist()){if(presenting)scenePresentation.cancel();return false;}
                publishTown(std::move(prepared));loginTown=std::move(nextLoginTown);
                if(revive) {world.player.dead=false;world.player.life=ActorLife::Alive;world.player.hp=world.player.maxHp;world.player.mp=world.player.maxMp;}
                returnTown=townLocation;
                message="已进入 "+allTowns.at(index).townName+" / "+scene.name+"；机制诊断 "+std::to_string(explorationDiagnostics.size())+" 项。";
                const bool saved=persist();writeJson(reportPath("town-traversal.json"),report);
                if(presenting){scenePresentation.ready(int64_t(SDL_GetTicks64()));writeJson(reportPath("scene-presentation.json"),scenePresentation.snapshot(int64_t(SDL_GetTicks64())));}
                return saved;
            }catch(const std::exception &error){if(presenting)scenePresentation.cancel();message="城镇进入失败："+std::string(error.what());return false;}
        };
        auto returnToTown = [&](bool revive=false) {
            const auto anchor=returnTown?returnTown:townLocation;
            const auto target=anchor?allTowns.require(anchor->townId,anchor->areaId):allTowns.require(1,0);
            return enterTownArea(target,std::optional<TownLocation>{},revive);
        };
        auto refreshMapBrowser = [&](bool applyDraft=true) {
            if(applyDraft){mapAppliedQuery=mapQuery;mapQueryDirty=false;}
            if(townBrowser)mapPage=allTowns.page(mapAppliedQuery,mapOffset,9);
            else {if(!allMaps) allMaps=std::make_unique<MapAccessCatalog>(pvf);mapPage=allMaps->partialPage(mapAppliedQuery,mapOffset,9);}
            mapOffset=mapPage.offset;
            if(!selectedMap || std::none_of(mapPage.entries.begin(),mapPage.entries.end(),
                [&](const auto &entry){return entry.index==*selectedMap;}))
                selectedMap=mapPage.entries.empty()?std::optional<size_t>{}:std::optional<size_t>{mapPage.entries.front().index};
        };
        auto openMapBrowser = [&](bool towns=false) {
            if(businessBlocked()){message="请先完成奖励或保存事务，再浏览地图。";return;}
            textInput.deactivate();
            townBrowser=towns;mapQuery.clear();mapAppliedQuery.clear();mapOffset=0;selectedMap.reset();
            try {refreshMapBrowser();
                if(dungeonSelectionState.open)
                    dnf::updateDungeonSelection(dungeonSelectionModel,dungeonSelectionLayout,dungeonSelectionState,
                        {DungeonSelectionAction::Cancel,{},int64_t(SDL_GetTicks64())},{world.characterLevel,true,dungeonDifficultyCount,true});
                mapBrowser=true;menu=skillMenu=map=dialog=selectDungeon=false;
                regionUi.close();world.releaseInputs();synchronizeTextScope();}
            catch(const std::exception &error) {message="地图目录读取失败："+std::string(error.what());}
        };
        auto enterExplorationMap = [&](size_t index) {
            if(businessBlocked()){message="请先完成奖励或保存事务，再切换地图。";return;}
            if(townBrowser) {enterTownArea(index);return;}
            try {
                if(!mapPage.matchesComplete){message="地图名称索引尚未完成，请稍后进入，避免使用未完成的查询结果。";return;}
                // User-requested temporary level/task bypass. Source format and
                // dependency failures remain required and explicitly diagnosed.
                const bool unrestricted=true;
                const auto admission=allMaps->admission(index,progress.level(),unrestricted);
                if(!admission.allowed) {
                    writeJson(reportPath("map-entry-error.json"),admission.json());
                    message="地图准入未通过，具体诊断已保存到 map-entry-error.json。";return;
                }
                const auto entry=allMaps->at(index);
                auto prepared=prepareMapExploration(pvf,assets,world,catalog,entry,unrestricted,
                    MonsterLevelPolicy::playerLevel(world.characterLevel));
                if(!prepared.ok) {
                    writeJson(reportPath("map-entry-error.json"),prepared.json());
                    message="地图准备失败，保留当前现场；具体诊断已保存到 map-entry-error.json。";return;
                }
                if(debugGeneration==std::numeric_limits<uint64_t>::max())throw std::overflow_error("Debug target generation exhausted");
                auto walks=prepared.scene.walkRects,blocks=prepared.scene.blockedRects;
                world.validateSceneActorCapacity(prepared.monsters.size());
                if(!persist())return;
                returnTown=townLocation;
                world.configureMonsterActionAi("easy");
                world.changeScene();session.clear();targetHud.reset();regionUi.close();
                scene=std::move(prepared.scene);world.monsters=std::move(prepared.monsters);
                world.walkRects.swap(walks);world.blockedRects.swap(blocks);world.mapWidth=scene.width;
                world.player.x=world.player.px=prepared.playerSpawn[0];world.player.y=world.player.py=prepared.playerSpawn[1];
                world.player.z=world.player.pz=0;world.player.vx=world.player.vy=world.player.vz=0;
                world.combat=true;world.synchronizeEntityHandles();
                world.setMapExplorationPolicy(prepared.geometryAvailable);
                world.refreshExplorationMonsterEventAiTestPolicy();
                explorationDiagnostics=std::move(prepared.diagnostics);explorationMap=entry;
                explorationDiagnostics.push_back({{"kind","runtime_exploration_policy"},{"policy",world.mapExplorationPolicy()}});
                location="exploration";room=0;resultShown=false;audioEvent=world.events.size();
                world.events.insert(world.events.end(),prepared.preparedEvents.begin(),prepared.preparedEvents.end());
                ++debugGeneration;submittedNs=world.simulationNanoseconds();
                camera=std::clamp(world.player.x-400.0,0.0,std::max(0.0,scene.width-800.0));
                audio.scene(scene.script.values("[sound]"));mapBrowser=false;synchronizeTextScope();
                message="已进入 "+entry.name+"；地图机制诊断 "+std::to_string(explorationDiagnostics.size())+" 项。F7 可切换地图。";
                writeJson(reportPath("map-exploration.json"),{{"map",entry.json()},{"test_mode",unrestricted},
                    {"diagnostics",explorationDiagnostics},{"complete",false},{"records",prepared.records},
                    {"source",prepared.source},{"source_fields",scene.script.source}});
                persist();
            } catch(const std::exception &error) {message="地图进入失败，保留诊断："+std::string(error.what());}
        };
        auto moveRoom = [&](Direction direction) {
            if(businessBlocked()){message="请先完成奖励或保存事务，再离开房间。";return;}
            if(!session.active())return;
            session.objects[std::to_string(session.run.current)] = scene.saveObjects(world.nowMs());
            session.remember(world);
            const auto previousSession=session;
            const auto previousRoom=room;
            if(!session.run.move(direction))return;
            try {
                room=session.run.current;
                loadScene("dungeon");
            } catch(const std::exception &error) {
                const auto failedPath=session.run.room().path;
                session=previousSession;room=previousRoom;world.releaseInputs();
                world.configureMonsterActionAi(session.monsterAiDifficulty());
                message="房间准备失败："+std::string(error.what());transitionUntil=world.nowMs()+650;
                writeJson(reportPath("room-preparation-error.json"),{{"map",failedPath},{"error",error.what()}});
                return;
            }
            auto gates=scene.script.values("[pathgate pos]");int d=int(opposite(direction));
            if(gates.size()>=size_t(d*2+2)) {
                world.player.x=world.player.px=gates[d*2].get<double>()+(d==0?45:d==1?-45:0);
                world.player.y=world.player.py=gates[d*2+1].get<double>()+scene.bg+(d==2?35:d==3?-35:0);
            }
            world.recoverPosition(world.player);transitionUntil=world.nowMs()+650;persist();
        };
        auto setDungeonSelectionWorldmap=[&](const std::string &path) {
            try {
                const auto prepared=catalog.prepareWorldmap(path);
                writeJson(reportPath("worldmap-preparation.json"),prepared);
                if(prepared.at("status")!="prepared")throw std::runtime_error(prepared.dump());
                auto candidate=captureDungeonSelectionModel(pvf,catalog,path);
                auto layout=selectionUi.dungeonLayout(candidate);
                dungeonSelectionModel=std::move(candidate);dungeonSelectionLayout=std::move(layout);
                dungeonSelectionState={};return true;
            }catch(const std::exception &error){message="区域选择准备失败："+std::string(error.what());return false;}
        };
        auto enterDungeon=[&](int id,int difficulty=0){
            if(businessBlocked()){message="旧副本奖励尚未完成，不能覆盖现场或开启新副本。";return;}
            if (!canEnterDungeonSelection(dungeonSelectionModel, id, {world.characterLevel, true,dungeonDifficultyCount,true})) return;
            try {
                beginScenePresentation(pvf.script(catalog.dungeons.at(id).path),catalog.dungeons.at(id).name);
                const auto preparation=catalog.prepareDungeon(id);
                writeJson(reportPath("dungeon-preparation.json"),preparation);
                if(preparation.at("status")!="prepared")throw std::runtime_error(preparation.dump());
                RegionSession candidate;
                candidate.begin(catalog,id,uint64_t(startedMs_)+SDL_GetTicks64()+uint64_t(selected)*1000003,demoBalance,
                    world.usesSourceGrowth() ? MonsterHpPolicy::inferredMobTableHpV1().id : "legacy-demo-v1",
                    world.usesSourceGrowth() ? MonsterCombatAttributePolicy::inferredMobCombatTableV1().id : "legacy-snapshot-damage-v1",
                    MonsterLevelPolicy::playerLevel(world.characterLevel),difficulty);
                if(!persist()){scenePresentation.cancel();return;}
                const auto previousSession=session;const auto previousRoom=room;
                session=std::move(candidate);room=session.run.current;
                try {loadScene("dungeon");}
                catch(...) {session=previousSession;room=previousRoom;
                    world.configureMonsterActionAi(session.active()?session.monsterAiDifficulty():"easy");throw;}
                returnTown=townLocation;dungeonSelectionState.open=false;selectDungeon=false;resultShown=false;persist();
                scenePresentation.ready(int64_t(SDL_GetTicks64()));
                writeJson(reportPath("scene-presentation.json"),scenePresentation.snapshot(int64_t(SDL_GetTicks64())));
            }catch(const std::exception &error){
                scenePresentation.cancel();
                writeJson(reportPath("dungeon-entry-error.json"),{{"dungeon",id},{"error",error.what()},
                    {"previous_scene",scene.path},{"scene_preserved",true}});
                message="副本准备失败，已保留当前场景。详情见运行日志 dungeon-entry-error.json。";
            }
        };
        auto openDungeonSelection = [&] {
            if(businessBlocked()){message="旧副本奖励尚未完成，请先重试。";return;}
            if(townLocation) {
                const auto &gate=allTowns.at(allTowns.require(townLocation->townId,townLocation->areaId));
                if(gate.kind!="[dungeon gate]"||gate.worldmapPath.empty()) {
                    message="当前区域没有可用的来源地下城门";writeJson(reportPath("town-dungeon-gate.json"),gate.json());return;
                }
                writeJson(reportPath("town-dungeon-gate.json"),gate.json());
                if(!setDungeonSelectionWorldmap(gate.worldmapPath))return;
            }
            dungeonSelectionState = enterDungeonSelection(dungeonSelectionModel, dungeonSelectionState);
            selectDungeon = dungeonSelectionState.open;
            if (selectDungeon) {
                selectionUi.startDungeonPresentation(dungeonSelectionState,int64_t(SDL_GetTicks64()));
                dungeonSelectionLayout=selectionUi.dungeonLayout(dungeonSelectionModel,dungeonSelectionState.selectedDungeon);
                world.releaseInputs();
            }
        };
        auto updateDungeonSelection = [&](DungeonSelectionAction action, SelectionPoint point = {},int clickCount=1) {
            if (!dungeonSelectionState.open) return;
            const auto event = dnf::updateDungeonSelection(dungeonSelectionModel, dungeonSelectionLayout,
                dungeonSelectionState, {action, point,int64_t(SDL_GetTicks64()),clickCount},
                {world.characterLevel, true,dungeonDifficultyCount,true});
            selectDungeon = dungeonSelectionState.open;
            if (event.kind == DungeonSelectionEventKind::Selected) {
                regionUi.dungeon = event.dungeonId;
                dungeonSelectionLayout=selectionUi.dungeonLayout(dungeonSelectionModel,event.dungeonId);
            } else if (event.kind == DungeonSelectionEventKind::Cancelled) {
                world.releaseInputs();
                Json report={{"action","dungeon_selection_cancel"},{"scene_before",scene.path},{"status","resolving"}};
                try {
                    if(!townLocation)throw std::runtime_error("Current source town is unavailable for selection return");
                    report["current_town"]=townLocation->json();
                    Json resolution;
                    const auto destination=characterEntry.roomFor(*townLocation,loginTown,&resolution);
                    report["room_resolution"]=std::move(resolution);
                    report["destination"]=destination.json();report["status"]="destination_resolved";
                    writeJson(reportPath("dungeon-selection-return-town.json"),report);
                    const bool entered=enterTownArea(allTowns.require(destination.townId,destination.areaId));
                    report["status"]=entered?"entered_and_saved":"town_entry_failed_or_save_pending";
                    report["scene_after"]=scene.path;report["message"]=message;
                    writeJson(reportPath("dungeon-selection-return-town.json"),report);
                }catch(const std::exception &error){
                    report["status"]="failed";report["error"]=error.what();
                    writeJson(reportPath("dungeon-selection-return-town.json"),report);
                    message="选关返回失败，保留当前现场；详情见 dungeon-selection-return-town.json："+std::string(error.what());
                }
            } else if (event.kind == DungeonSelectionEventKind::EnterDungeon)
                enterDungeon(event.dungeonId,event.difficulty);
        };
        auto syncEquipment=[&]{
            world.applyEquipment(progress);
            playerAppearance=world.characterAppearance();
        };
        auto talkToNpc = [&](const MapNpc &npc) {
            if(businessBlocked()){message="请先完成奖励或保存事务。";return false;}
            if(!catalog.npcs.count(npc.id)){message="该NPC业务机制尚未接入："+npc.name+"（"+std::to_string(npc.id)+"）";return false;}
            if (!npc.visible || world.player.dead || world.activeSkill() >= 0) return false;
            if (std::abs(npc.x-world.player.x)+std::abs(npc.y-world.player.y) >= 180) {
                message = "请靠近" + npc.name + "后交谈。"; return false;
            }
            regionUi.openNpc(npc.id, progress); syncEquipment(); persist();
            auto speech = pvf.script(npc.source).values("[popup wav]");
            if (!speech.empty()) audio.play(speech[0]);
            world.releaseInputs(); return true;
        };
        auto resumeCharacter=[&]{
            if(businessBlocked())return;
            try {
                const auto saved=saves["characters"][selected].value("region_session",Json::object());
                auto entry=characterEntry.prepare(world,saved);
                if(debugGeneration==std::numeric_limits<uint64_t>::max())throw std::overflow_error("Debug generation exhausted");
                auto report=entry.report;
                store.apply(selected,world,progress);syncEquipment();
                rewardService.characterBoundary(world);
                // Login always publishes the current region's source Seria
                // room. Old-run pending provenance lives in progression; only
                // its immutable source metadata may be prepared for retry.
                session.clear();targetHud.reset();regionUi.close();
                dungeonSelectionState.open=false;selectDungeon=false;leaveDungeonEntrance(dungeonSelectionState);
                publishCharacterEntry(world,scene,std::move(entry));
                screen=Game;finishTownPublication(entry.town);
                loginTown=townLocation;returnTown=townLocation;
                skillConfigurationUi.reset();skillLearningUi.reset();configureSkills=false;
                synchronizeTextScope();submittedNs=world.simulationNanoseconds();
                report["status"]="entered";report["character_uuid"]=saves["characters"][selected].value("uuid",std::string());
                report["checkpoint_saved"]=persist();
                if(report.at("checkpoint_saved")==true&&rewardService.blocked(progress))
                    report["pending_rewards_resolved"]=pumpRewards();
                report["pending_rewards_preserved"]=rewardService.blocked(progress);
                writeJson(reportPath("character-entry.json"),report);
                if(report.at("checkpoint_saved")==true&&!rewardService.blocked(progress))message="已返回当前区域的赛丽亚房间。";
            } catch(const std::exception &error) {
                message="角色进入失败，详情已保存到运行日志 character-entry-error.json。";
                writeJson(reportPath("character-entry-error.json"),{{"slot",selected},{"error",error.what()}});
            }
        };
        debugService.setApplicationCommandHandler([&](World &simulation,const DebugCommand &command) -> Json {
            if(!testBranch.active()||screen!=Game||businessBlocked())
                throw std::runtime_error("An active isolated test branch without pending saves is required");
            if(simulation.combat||session.active()||explorationMap)
                throw std::runtime_error("Return to a town before switching test profession or opening skills");
            Json actual;
            if(command.kind==DebugCommandKind::SetTestIdentity) {
                if(debugGeneration==std::numeric_limits<uint64_t>::max())throw std::overflow_error("Debug generation exhausted");
                const auto target=CharacterIdentity::fromJson(command.payload);
                const auto anchor=townLocation.value_or(TownLocation{});
                const auto index=townLocation?allTowns.require(anchor.townId,anchor.areaId):allTowns.require(1,0);
                auto prepared=prepareTownArea(pvf,assets,simulation,catalog,allTowns,index);
                if(!prepared.ok)throw std::runtime_error("Selected test character's source town cannot be prepared");
                actual=selectBetaTestCharacter(testBranch.select(store),selected,simulation,progress,target);
                publishTown(std::move(prepared));playerAppearance=simulation.characterAppearance();
                skillConfigurationUi.reset();skillLearningUi.reset();configureSkills=false;
                regionUi.close();skillMenu=false;submittedNs=simulation.simulationNanoseconds();
                message="已切换隔离测试职业；F9开放可执行技能，K中配置快捷栏。返回选角恢复正常角色。";
            } else if(command.kind==DebugCommandKind::UnlockExecutableSkills) {
                actual=unlockExecutableBetaSkills(simulation);
                message=simulation.identity().jobId==1?
                    "女格斗全源技能测试已开启；K中可配置所有分支，缺失源动作仅提示，正常账本未变。":
                    "已开放当前可执行测试技能；未开放项及来源门槛见F8反馈。K中配置快捷栏。";
                if(simulation.identity().jobId==1){skillConfigurationUi.reset();skillLearningUi.reset();}
            } else throw std::runtime_error("Unknown application debug command");
            actual["checkpoint_saved"]=persist();actual["checkpoint_pending"]=businessBlocked();
            return actual;
        });
        if (autoRun) {
            screen = Game;
            loadScene("dungeon");
            world.god = true;
            world.freeCd = true;
            world.freezeAi = true;
        }
        synchronizeTextScope();
        auto start = std::chrono::steady_clock::now(), last = start;
        uint64_t frames = 0;
        int lastAuto = -1;
        Json captures = Json::array();
        Json skillTrials = Json::array(), skillSamples = Json::array(), skillDetailSamples = Json::array();
        int64_t lastFrameNs = 0, maxFrameNs = 0;
        int flowScene = -1;
        std::set<int> skillCaptures, skillDetailCaptures;
        std::set<int> sceneCaptures;
        diagnostics::FrameStatistics frameStatistics;
        int peakEffects = 0;
        int targetMonster = -1;
        struct EffectsCase {
            std::string key, monster, kind, side;
            double sourceDx = -75, sourceDy = 0;
            bool strong = false;
            int durationMs = 2200, bloodVigorous = 0;
        };
        std::vector<EffectsCase> effectsCases;
        if (effectsFixture) {
            const char *sides[] = {"left", "right", "above", "below"};
            const double offsets[][2] = {{-75, 0}, {75, 0}, {0, -55}, {0, 55}};
            for (int side = 0; side < 4; ++side) for (int strong = 0; strong < 2; ++strong)
                effectsCases.push_back({std::string("shared-") + sides[side] + (strong ? "-strong" : "-weak"),
                    side < 2 ? "monster/goblin/goblin.mob" : "monster/lugaru/lugaru.mob",
                    "shared-death", sides[side], offsets[side][0], offsets[side][1], bool(strong), 4000});
            effectsCases.push_back({"explicit-ghost", "monster/act8/ghost_flu/ghost_flu.mob", "explicit-death", "left", -75, 0, false, 2800});
            effectsCases.push_back({"explicit-chief", "monster/act8/chiefsars/chiefsars.mob", "explicit-death", "right", 75, 0, true, 5000});
            effectsCases.push_back({"hurt-standing", "monster/goblin/goblin.mob", "hurt", "left"});
            effectsCases.push_back({"hurt-knockdown", "monster/goblin/goblin.mob", "knockdown", "left"});
            effectsCases.push_back({"airborne-rehit", "monster/goblin/goblin.mob", "airborne", "left"});
            effectsCases.push_back({"hopsmash-base", "monster/goblin/goblin.mob", "hopsmash", "left", -75, 0, false, 3000, 0});
            effectsCases.push_back({"hopsmash-blood-vigorous", "monster/goblin/goblin.mob", "hopsmash", "left", -75, 0, false, 3000, 1});
            // The source floor/background remains visible; unrelated breakable
            // objects are excluded from this explicitly artificial visual fixture.
            scene.objectSystem.clear(); scene.objects.clear(); world.blockedRects.clear();
        }
        Json effectsTrials = Json::array(), effectsSamples = Json::array();
        int effectsCase = -1;
        int64_t effectsCaseStart = 0;
        bool effectsHit = false, effectsRehit = false, effectsReleased = false, effectsFinished = false;
        std::set<int> effectsCapturePhases;
        auto effectsState = [&] {
            Json details = Json::array();
            for (const auto &m : world.monsters) {
                std::array<double, 3> velocity{};
                for (const auto &p : m.deathFragments) { velocity[0] += p.vx; velocity[1] += p.vy; velocity[2] += p.vz; }
                if (!m.deathFragments.empty()) for (auto &v : velocity) v /= m.deathFragments.size();
                details.push_back({{"id", m.id}, {"source", m.monsterPath}, {"hp", m.hp}, {"max_hp", m.maxHp},
                    {"life", int(m.life)}, {"animation", m.animation}, {"animation_path", m.animationPath},
                    {"position", {m.x, m.y, m.z}}, {"velocity", {m.vx, m.vy, m.vz}}, {"death_route", m.deathRoute},
                    {"independent_death", m.independentDeath}, {"death_duration_ms", m.deathDuration},
                    {"death_elapsed_ms", m.dead ? world.nowMs() - m.deathStart : 0},
                    {"fragment_display_ms", monsterFragmentDisplayMs(m.deathProfile)},
                    {"fragment_opacity", m.dead && !m.independentDeath
                        ? monsterFragmentOpacity(m.deathProfile, world.nowMs() - m.deathStart - monsterDeathBurstMs) : 0},
                    {"death_motion", m.deathMotion ? m.deathMotion->entry : ""},
                    {"death_motion_binding", m.deathMotion ? m.deathMotion->bindingTag : ""},
                    {"death_profile", m.deathProfile.raw}, {"death_issues", m.deathProfile.issues},
                    {"fragment_count", m.deathFragments.size()}, {"fragment_velocity_mean", velocity},
                    {"impact", {{"direction", {m.lastImpact.x, m.lastImpact.y}}, {"speed_scale", m.lastImpact.speedScale},
                                {"attack_speed", m.lastImpact.attackSpeed}, {"damage_fraction", m.lastImpact.damageFraction}}}});
            }
            return Json{{"world", world.snapshot()}, {"targets", details}};
        };
        auto beginEffectsCase = [&](int index) {
            effectsCase = index; effectsCaseStart = world.nowMs();
            effectsHit = effectsRehit = effectsReleased = false; effectsCapturePhases.clear();
            world.changeScene(); world.monsters.clear(); targetHud.reset();
            world.player = Actor{}; world.player.id = 0;
            world.god = world.freeCd = world.freezeAi = true;
            const auto &c = effectsCases.at(index);
            world.bloodVigorousLevel = c.bloodVigorous;
            const auto anchor = world.nearestWalkable(world.mapWidth * .5, 320);
            world.player.x = world.player.px = anchor[0] + c.sourceDx;
            world.player.y = world.player.py = anchor[1] + c.sourceDy;
            world.player.dir = c.sourceDx > 0 ? -1 : 1;
            if (c.kind == "hopsmash") {
                world.player.x = world.player.px = anchor[0] - 150;
                world.player.y = world.player.py = anchor[1]; world.player.dir = 1;
            }
            if (!world.canWalk(world.player.x, world.player.y))
                throw std::runtime_error("Effects fixture source outside original walk grid: " + c.key);
            for (int target = 0; target < (c.kind == "hopsmash" ? 3 : 1); ++target) {
                Actor m; m.id = 1000 + target; m.monsterPath = c.monster;
                m.x = m.px = c.kind == "hopsmash" ? world.player.x + 90 + target * 80 : anchor[0];
                m.y = m.py = anchor[1]; m.dir = -world.player.dir; m.animStart = world.nowMs();
                const bool lethal = c.kind == "shared-death" || c.kind == "explicit-death";
                m.maxHp = lethal ? 100 : 10000; m.hp = lethal ? 1 : m.maxHp;
                if (c.kind == "airborne") { m.z = m.pz = 35; m.vz = 120; m.recovery = 1; }
                if (!world.canWalk(m.x, m.y)) throw std::runtime_error("Effects fixture target outside original walk grid: " + c.key);
                world.monsters.push_back(m);
            }
            if (c.kind == "hopsmash") world.enqueue({submittedNs, 30, true});
            world.events.push_back({world.tick, "fixture_case", c.key});
            effectsTrials.push_back({{"index", index}, {"key", c.key}, {"kind", c.kind}, {"source_side", c.side},
                {"strong", c.strong}, {"blood_vigorous_level", c.bloodVigorous}, {"duration_ms", c.durationMs},
                {"start_ms", effectsCaseStart}, {"start", effectsState()}});
        };
        if (effectsFixture) beginEffectsCase(0);
        auto lastTitle = start;
        int uiMouseX=-100,uiMouseY=-100;
        while (!quit) {
            auto now = std::chrono::steady_clock::now();
            int64_t dt = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last).count();
            last = now;
            double wall = std::chrono::duration<double>(now - start).count();
            lastFrameNs = dt;
            maxFrameNs = std::max(maxFrameNs, dt);
            // SDL wall clock continues while the simulation is paused.
            (void)rewardRecovery.tryAutomaticRetry(SDL_GetTicks64(),!autoRun&&screen==Game,rewardRecoveryHooks);
            bool click = false, itemActivate = false;
            int pressX=-100,pressY=-100;
            int mx=uiMouseX, my=uiMouseY;
            synchronizeTextScope();
            SdlTextInputBatch batch;batch.collect();
            const auto mainWindowId=SDL_GetWindowID(render.window());
            const auto hasTextTraffic=batch.hasTextTraffic(mainWindowId);
            textBatchActive=true;textBatchTraffic=hasTextTraffic;textInput.beginEventBatch(hasTextTraffic);
            bool pageChangedByText=false;
            bool pause = menu || skillMenu || dialog || selectDungeon || mapBrowser || regionUi.open() || scenePresentation.frame(int64_t(SDL_GetTicks64())).blocked;
            for(const auto &e:batch.events()) {
                if (e.type == SDL_QUIT)
                    quitRequested = true;
                if(debugWindow && debugWindow->handleEvent(e)) continue;
                const auto eventWindow=sdlInputEventWindow(e);
                if(eventWindow && eventWindow!=mainWindowId) continue;
                if(e.type==SDL_WINDOWEVENT&&e.window.event==SDL_WINDOWEVENT_FOCUS_LOST) {
                    mainWindowFocused=false;textInput.setFocused(false);synchronizeTextScope();world.releaseInputs();
                }
                if(e.type==SDL_WINDOWEVENT&&e.window.event==SDL_WINDOWEVENT_FOCUS_GAINED) {
                    mainWindowFocused=true;synchronizeTextScope();textInput.beginEventBatch(hasTextTraffic);
                }
                if(e.type==SDL_KEYUP)textInput.keyUp(sdlTextInputKey(e.key.keysym.sym));
                if(e.type==SDL_KEYDOWN&&!mainWindowFocused)continue;
                if(scenePresentation.frame(int64_t(SDL_GetTicks64())).blocked&&
                    (e.type==SDL_KEYDOWN||e.type==SDL_MOUSEBUTTONDOWN))continue;
                if(e.type==SDL_KEYDOWN&&pageChangedByText)continue;
                if(e.type==SDL_WINDOWEVENT && e.window.event==SDL_WINDOWEVENT_CLOSE) quitRequested=true;
                if (effectsFixture) {
                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quitRequested = true;
                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F12)
                        shot = reportPath("manual.png").u8string();
                    continue;
                }
                if(e.type==SDL_MOUSEMOTION){mx=e.motion.x;my=e.motion.y;render.mouse(mx,my);
                    updateDungeonSelection(DungeonSelectionAction::PointerMove,{double(mx),double(my)});}
                if(e.type==SDL_WINDOWEVENT&&e.window.event==SDL_WINDOWEVENT_LEAVE){
                    mx=my=-100;
                    render.mouse(mx,my);
                    updateDungeonSelection(DungeonSelectionAction::PointerMove,{double(mx),double(my)});
                }
                if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED && !autoRun && !full) {
                    SDL_GetWindowSize(render.window(), &windowWidth, &windowHeight);
                    saveDisplay();
                }
                if (e.type == SDL_MOUSEBUTTONDOWN &&
                    (e.button.button == SDL_BUTTON_LEFT || e.button.button == SDL_BUTTON_RIGHT)) {
                    click = e.button.button == SDL_BUTTON_LEFT;
                    itemActivate = e.button.button == SDL_BUTTON_RIGHT || e.button.clicks >= 2;
                    mx = e.button.x; my = e.button.y;
                    render.mouse(mx, my);
                    pressX=mx;pressY=my;
                    if (dungeonSelectionState.open) {
                        updateDungeonSelection(DungeonSelectionAction::PointerMove,{double(mx),double(my)});
                        if (click)
                            updateDungeonSelection(DungeonSelectionAction::PointerActivate,{double(mx),double(my)},e.button.clicks);
                        click = false;
                        itemActivate = false;
                    }
                }
                if(e.type==SDL_TEXTINPUT) {
                    if(textInput.commitUtf8(e.text.text)) {
                        if(textInput.field()==TextInputField::CharacterName)name=textInput.text();
                        else if(textInput.field()==TextInputField::MapQuery){mapQuery=textInput.text();mapOffset=0;mapQueryDirty=true;}
                    }
                    continue;
                }
                if(e.type==SDL_TEXTEDITING||e.type==SDL_TEXTEDITING_EXT) {
                    textInput.updateComposition(e.type==SDL_TEXTEDITING?e.edit.text:(e.editExt.text?e.editExt.text:""),
                        e.type==SDL_TEXTEDITING?e.edit.start:e.editExt.start,
                        e.type==SDL_TEXTEDITING?e.edit.length:e.editExt.length);
                    continue;
                }
                if(e.type==SDL_KEYDOWN&&textInput.active()) {
                    const auto route=textInput.keyDown(sdlTextInputKey(e.key.keysym.sym),e.key.repeat!=0);
                    if(route.changed) {
                        if(textInput.field()==TextInputField::CharacterName)name=textInput.text();
                        else {mapQuery=textInput.text();mapOffset=0;mapQueryDirty=true;}
                    }
                    if(route.consumed) {
                        if(textInput.field()==TextInputField::CharacterName) {
                            if(route.intent==TextInputIntent::Submit){createCharacter();pageChangedByText=screen!=Create;}
                            else if(route.intent==TextInputIntent::Cancel){screen=Select;pageChangedByText=true;message.clear();synchronizeTextScope();}
                        }else if(textInput.field()==TextInputField::MapQuery) {
                            if(route.intent==TextInputIntent::Cancel){mapBrowser=false;pageChangedByText=true;synchronizeTextScope();}
                            else if(route.intent==TextInputIntent::Submit){if(mapQueryDirty)refreshMapBrowser();else if(selectedMap)enterExplorationMap(*selectedMap);pageChangedByText=!mapBrowser;}
                            else if(route.intent==TextInputIntent::PageUp||route.intent==TextInputIntent::PageDown) {
                                if(route.intent==TextInputIntent::PageUp)mapOffset=mapOffset>=9?mapOffset-9:0;
                                else if(mapOffset+9<mapPage.total)mapOffset+=9;
                                refreshMapBrowser();
                            }else if(route.intent==TextInputIntent::Up||route.intent==TextInputIntent::Down) {
                                const auto found=std::find_if(mapPage.entries.begin(),mapPage.entries.end(),[&](const auto &entry){return selectedMap&&entry.index==*selectedMap;});
                                if(!mapPage.entries.empty()) {
                                    auto row=found==mapPage.entries.end()?0:int(found-mapPage.entries.begin());
                                    row=std::clamp(row+(route.intent==TextInputIntent::Up?-1:1),0,int(mapPage.entries.size())-1);
                                    selectedMap=mapPage.entries[size_t(row)].index;
                                }
                            }
                        }
                        synchronizeTextScope();continue;
                    }
                }
                if (e.type == SDL_KEYDOWN && !e.key.repeat) {
                    if (businessBlocked()) continue;
                    auto k = e.key.keysym.sym;
                    if(k==SDLK_F9) { showDebugWindow();mainWindowFocused=SDL_GetKeyboardFocus()==render.window();synchronizeTextScope();continue; }
                    if(screen==Game && k==SDLK_F10) {
                        if(mapBrowser && townBrowser){mapBrowser=false;synchronizeTextScope();}
                        else openMapBrowser(true);
                        continue;
                    }
                    if(screen==Game && k==SDLK_F7) {
                        if(mapBrowser && !townBrowser) {mapBrowser=false;synchronizeTextScope();}
                        else openMapBrowser();
                        continue;
                    }
                    if(screen==Game && k==SDLK_F6 && !mapBrowser) {
                        configureSkills=true;skillMenu=true;menu=map=dialog=selectDungeon=false;
                        regionUi.close();world.releaseInputs();continue;
                    }
                    if(mapBrowser)continue;
                    if(screen==Select) {
                        const auto slotsPerPage=CharacterSelectionGeometry::slotsPerPage;
                        const auto last=CharacterSelectionGeometry::slotCount-1;
                        int columns=1;const auto first=CharacterSelectionGeometry::slot(0);
                        while(columns<slotsPerPage&&CharacterSelectionGeometry::slot(columns).y==first.y)++columns;
                        if(k==SDLK_RETURN||k==SDLK_KP_ENTER) {
                            if(saves["characters"][selected].is_null())beginCharacterCreation();else resumeCharacter();
                            pageChangedByText=true;continue;
                        }
                        bool moved=true;
                        if(k==SDLK_LEFT)selected=std::max(0,selected-1);
                        else if(k==SDLK_RIGHT)selected=std::min(last,selected+1);
                        else if(k==SDLK_UP)selected=std::max(0,selected-columns);
                        else if(k==SDLK_DOWN)selected=std::min(last,selected+columns);
                        else if(k==SDLK_PAGEUP||k==SDLK_PAGEDOWN) {
                            page=CharacterSelectionGeometry::clampPage(page+(k==SDLK_PAGEUP?-1:1));
                            selected=std::min(last,page*slotsPerPage+selected%slotsPerPage);
                        }else moved=false;
                        if(moved){page=selected/slotsPerPage;continue;}
                    }
                    if (screen == Game && selectDungeon) {
                        if (k == SDLK_F12) shot = reportPath("manual.png").u8string();
                        else if (k == SDLK_LEFT) updateDungeonSelection(DungeonSelectionAction::MoveLeft);
                        else if (k == SDLK_RIGHT) updateDungeonSelection(DungeonSelectionAction::MoveRight);
                        else if (k == SDLK_UP) updateDungeonSelection(DungeonSelectionAction::MoveUp);
                        else if (k == SDLK_DOWN) updateDungeonSelection(DungeonSelectionAction::MoveDown);
                        else if (k == SDLK_RETURN) updateDungeonSelection(DungeonSelectionAction::Enter);
                        else if (k == SDLK_ESCAPE) updateDungeonSelection(DungeonSelectionAction::Cancel);
                        // Selection consumes its keys; unrelated gameplay menus
                        // must not open behind it or receive the enter action.
                        continue;
                    }
                    if (k == SDLK_ESCAPE) {
                        if (screen == Game) {
                            if (regionUi.open()) regionUi.close();
                            else if (selectDungeon)
                                updateDungeonSelection(DungeonSelectionAction::Cancel);
                            else if (map || skillMenu || dialog)
                                map = skillMenu = dialog = selectDungeon = false;
                            else
                                menu = !menu;
                            world.releaseInputs();
                        }
                    }
                    if (k == SDLK_F3)
                        debug = !debug;
                    if (k == SDLK_F12) {
                        shot = reportPath("manual.png").u8string();
                    }
                    if (screen == Game) {
                        if(k==SDLK_x&&regionUi.requestDialogueAdvance())continue;
                        if (k == SDLK_m)
                            map = !map;
                        if (k == SDLK_k) {
                            skillMenu = !skillMenu;
                            configureSkills=false;
                        }
                        if(k==SDLK_i){if(regionUi.panel==RegionPanel::Inventory)regionUi.close();else regionUi.openInventory();world.releaseInputs();}
                        if(k==SDLK_l){regionUi.panel=regionUi.panel==RegionPanel::Quests?RegionPanel::None:RegionPanel::Quests;world.releaseInputs();}
                        if (skillMenu || menu) world.releaseInputs();
                        if(k==SDLK_F5)
                            message="F9 打开独立测试窗口；测试修改使用隔离进度。";
                        if (k == SDLK_F8) {
                            auto dir = reportPath("feedback") / std::to_string(SDL_GetTicks64());
                            const auto cameraOutput = render.outputSize();
                            writeJson(dir / "state.json", world.snapshot());
                            writeJson(dir / "inputs.json", world.inputs());
                            writeJson(dir / "events.json", world.eventLog());
                            writeJson(dir / "context.json", {{"binary_sha256",binaryHash},{"content_identity",contentIdentity.json()},
                                {"debug",debugService.snapshot().json()},{"attributes",world.statReport()},
                                {"simulation",world.simulationCheckpoint()},{"region",captureRegionSession(location)},
                                {"exploration_map",explorationMap?explorationMap->json():Json()},
                                {"map_diagnostics",explorationDiagnostics},
                                {"portal_sources",portalObjects.snapshot()},{"portal_visuals",render.portalSourceReport()},
                                {"render_errors",render.errors},{"render_unsupported",render.unsupported},
                                {"scene_camera",sceneCameraDiagnostics(scene,cameraOutput[0],cameraOutput[1],
                                    world.player.px+(world.player.x-world.player.px)*world.alpha(),
                                    world.player.py+(world.player.y-world.player.py)*world.alpha())},
                                {"monster_event_ai",world.monsterEventAiState()},
                                {"monster_event_ai_test",world.monsterEventAiTestPolicy()},
                                {"experimental_character",world.experimentalDiagnostics()},
                                {"experimental_skill_configuration",world.experimentalRuntime()?world.experimentalRuntime()->configuration().snapshot():Json()},
                                {"test_branch",testBranch.active()},{"test_save_directory",testBranch.directory().u8string()}});
                            render.screenshot(dir / "screen.png");
                            message = "反馈包已保存：" + dir.u8string();
                        }
                    if (k == SDLK_RETURN && !menu && !skillMenu && !map && !dialog) {
                            if(selectDungeon) updateDungeonSelection(DungeonSelectionAction::Enter);
                            else if(regionUi.open())regionUi.close();
                            else if(townLocation&&!world.combat&&scene.townExitAt(world.player.x,world.player.y)&&
                                    scene.townExitAt(world.player.x,world.player.y)->town==-1)openDungeonSelection();
                            else {
                                const MapNpc *nearest=nullptr;double distance=1e9;
                                for(const auto &npc:scene.npcs) {
                                    if(!npc.visible)continue;
                                    double d=std::abs(npc.x-world.player.x)+std::abs(npc.y-world.player.y);
                                    if(d<distance&&d<180){distance=d;nearest=&npc;}
                                }
                                if(nearest)talkToNpc(*nearest);
                            }
                        }
                        if(k==SDLK_x&&!menu&&!skillMenu&&!map&&!dialog&&location=="dungeon"&&session.active()&&world.activeSkill()<0){
                            const auto claim=nearestPickup();
                            if(!claim.empty()) {
                                // Consume this press even if inventory/source preparation
                                // fails. A pickup attempt must never also enqueue attack.
                                auto candidate=progress;
                                const auto result=candidate.claimDrop(claim);message=result.message;
                                if(result.ok) {
                                    if(world.tryPickupAction()) {
                                        progress.commitPrepared(std::move(candidate));persist();
                                    }else message="当前动作无法拾取；详情见拾取诊断。";
                                }
                                writeJson(reportPath("pickup-action.json"),world.pickupActionTrace());
                                continue;
                            }
                        }
                    }
                }
                if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_FOCUS_LOST && !autoRun) {
                    world.releaseInputs();
                }
                const SdlGameInputContext gameInput{mainWindowId,SDL_GetTicks(),screen==Game,businessBlocked(),pause,
                    menu||skillMenu||dialog||selectDungeon||mapBrowser||regionUi.open()||
                        scenePresentation.frame(int64_t(SDL_GetTicks64())).blocked,
                    map,submittedNs,dt};
                (void)dispatchSdlGameInput(world,e,gameInput);
            }
            textInput.endEventBatch();textBatchActive=false;synchronizeTextScope();
            if(click||itemActivate){mx=pressX;my=pressY;}
            const bool retrySaveClick=click && savePending();
            const bool retryRewardClick=click && !savePending() && rewardService.blocked(progress);
            suppressBlockedGameClicks(businessBlocked(),click,itemActivate);
            if(mapBrowser&&!townBrowser&&allMaps&&!allMaps->nameIndexProgress().complete) {
                const auto indexing=allMaps->stepNameIndex(2,2000);
                if(indexing.lastStepEntries)refreshMapBrowser(false);
            }
            if (flowSmoke) {
                int next = int(wall / flowSceneSeconds) % 6;
                if (next != flowScene) {
                    flowScene = next;
                    const char *places[] = {"room", "town", "entrance", "dungeon", "dungeon", "dungeon"};
                    if (next >= 3) {
                        room = next - 3;
                        visited[room] = false;
                    }
                    loadScene(places[next]);
                    world.god = true;
                    world.freeCd = true;
                    world.freezeAi = next != 5;
                    auto modes = std::array<std::array<int, 2>, 3>{{{800, 600}, {1280, 720}, {1024, 768}}};
                    render.resize(modes[next % 3][0], modes[next % 3][1]);
                }
            }
            const bool neitherWindowFocused = !autoRun && SDL_GetKeyboardFocus()!=render.window() &&
                                               !(debugWindow&&debugWindow->hasFocus());
            pause = businessBlocked() || menu || skillMenu || dialog || selectDungeon || mapBrowser || regionUi.open() || scenePresentation.frame(int64_t(SDL_GetTicks64())).blocked ||
                    neitherWindowFocused || debugService.pauseRequested();
            debugBoundaryPaused=pause;
            applyDebugBoundary(world);
            pause = businessBlocked() || menu || skillMenu || dialog || selectDungeon || mapBrowser || regionUi.open() || scenePresentation.frame(int64_t(SDL_GetTicks64())).blocked ||
                    neitherWindowFocused || debugService.pauseRequested();
            debugBoundaryPaused=pause;
            const bool singleStep=!businessBlocked()&&!scenePresentation.frame(int64_t(SDL_GetTicks64())).blocked&&screen==Game&&pause&&debugService.takeSingleStepRequest();
            if (trace && frames % 15 == 0) {
                Json traceNpcs = Json::array();
                for (const auto &npc : scene.npcs)
                    traceNpcs.push_back({{"id", npc.id}, {"name", npc.name}, {"x", npc.x}, {"y", npc.y},
                        {"visible", npc.visible}, {"generated_placement", npc.generatedPlacement}});
                atomicJson(reportPath("live.json"), {{"screen", int(screen)}, {"location", location}, {"room", room},
                    {"menu", menu}, {"skill_menu", skillMenu}, {"map_menu",map}, {"select_dungeon", selectDungeon},
                    {"dungeon_selection",describeDungeonSelection(dungeonSelectionModel,dungeonSelectionLayout,dungeonSelectionState)},
                    {"settings_menu", settingsMenu}, {"audio",audio.snapshot()},
                    {"settings",clientSettings}, {"requested_balance",demoBalance.describe()},
                    {"selected", selected}, {"world", world.snapshot()}, {"gates", scene.script.values("[pathgate pos]")},
                    {"background_y", scene.bg}, {"panel",int(regionUi.panel)}, {"progression",progress.state},
                    {"region_ui",regionUi.snapshot()},{"ui_mouse",{mx,my}}, {"npcs", traceNpcs},
                    {"navigation",{{"walk_rects",world.walkRects},{"blocked_rects",world.blockedRects},
                                    {"map_width",world.mapWidth}}},
                    {"run",session.active()?captureRegionSession(location):Json()}});
            }
            if (screen == Game && (!pause || singleStep)) {
                if (effectsFixture && !effectsFinished) {
                    if (world.nowMs() - effectsCaseStart >= effectsCases[effectsCase].durationMs) {
                        effectsTrials[effectsCase]["end"] = effectsState();
                        if (effectsCase + 1 == int(effectsCases.size())) effectsFinished = true;
                        else beginEffectsCase(effectsCase + 1);
                    }
                    if (!effectsFinished) {
                        const auto &c = effectsCases[effectsCase];
                        const auto elapsed = world.nowMs() - effectsCaseStart;
                        if (c.kind == "hopsmash") {
                            if (!effectsReleased && elapsed >= 220) {
                                world.enqueue({submittedNs, 30, false}); effectsReleased = true;
                            }
                        } else if (!effectsHit && elapsed >= 350) {
                            const int responseSkill = c.kind == "knockdown" || c.kind == "airborne" ? 20 : 64;
                            world.diagnosticHit(1000, c.strong ? 120 : 5, responseSkill, 0, world.player.dir,
                                {world.player.x, world.player.y, c.strong ? 650.0 : 80.0});
                            effectsHit = true;
                        } else if (c.kind == "airborne" && !effectsRehit && elapsed >= 500) {
                            world.diagnosticHit(1000, 5, 20, 0, world.player.dir,
                                {world.player.x, world.player.y, 300}); effectsRehit = true;
                        }
                    }
                }
                if (autoRun && !effectsFixture && world.combat && wall < autoSeconds) {
                    int step = int(wall / 4.0);
                    if (step != lastAuto) {
                        lastAuto = step;
                        world.changeScene(); // Clear controller/input/protection state between trials.
                        int direction = (step / 13) % 2 == 0 ? 1 : -1;
                        // Leave room for the entire three-slash displacement in either
                        // direction. All placements must still be on the source walk grid.
                        double startX = world.mapWidth * (direction > 0 ? 0.25 : 0.75);
                        if (flowSmoke && step % 13 != 2)
                            startX = world.mapWidth / 2.0; // Exercise fractional wide-screen tile boundaries.
                        world.player.x = world.player.px = startX;
                        world.player.y = world.player.py = 344;
                        world.player.z = world.player.pz = 0;
                        world.player.vz = 0;
                        world.player.dir = direction;
                        world.player.dead = false;
                        world.player.hp = world.player.maxHp;
                        if (!world.canWalk(world.player.x, world.player.y))
                            throw std::runtime_error("Skill smoke player placement outside source walk grid");
                        for (size_t k = 0; k < world.monsters.size(); k++) {
                            auto &m = world.monsters[k];
                            Actor fresh;
                            fresh.id = m.id;
                            fresh.boss = m.boss;
                            fresh.monsterPath = m.monsterPath;
                            m = fresh;
                            // Convert the unsigned container index before multiplying
                            // by a negative direction; otherwise left placements wrap.
                            double distance = (step % 13 == 8 ? 45.0 : 80.0) + double(k) * 35.0;
                            m.x = m.px = startX + direction * distance;
                            m.y = m.py = world.player.y;
                            m.dir = -direction;
                            m.hp = m.maxHp = 10000;
                            m.animStart = world.nowMs();
                            if (!world.canWalk(m.x, m.y))
                                throw std::runtime_error("Skill smoke target placement outside source walk grid");
                        }
                        int idx = step % 13;
                        if (world.skills[idx].airOnly) {
                            world.player.z = world.player.pz = 100;
                            world.player.vz = 50;
                        }
                        world.player.mp = world.player.maxMp;
                        if (idx == 3)
                            world.player.animation = "dashattack";
                        if (idx == 12)
                            world.enqueue({submittedNs, 32, true}); // Hold the default Guard slot.
                        world.activate(idx);
                        if (world.skills[idx].continuation)
                            world.activate(idx);
                        skillTrials.push_back({{"step", step}, {"skill_index", idx},
                            {"direction", direction}, {"tick", world.tick}, {"wall_seconds", wall},
                            {"scene", scene.path}, {"state", world.snapshot()}});
                    }
                }
                if (autoRun && world.activeSkill() >= 0 && world.skills[world.activeSkill()].continuation)
                    world.activate(world.activeSkill());
                // Expose short white/burst phases even when a rendered frame
                // stalls: only this diagnostic mode caps submitted simulation
                // time per rendered frame. Normal gameplay timing is unchanged.
                const auto advanceNs = effectsFixture ? std::min<int64_t>(dt, 16666667) : dt;
                if(singleStep) { world.advanceSingleTick(); submittedNs=world.simulationNanoseconds(); }
                else { submittedNs = addElapsed(submittedNs, advanceNs); world.advance(advanceNs, 8); }
                if (!world.combat && townLocation) {
                    const auto *exit = scene.townExitAt(world.player.x, world.player.y);
                    if (!exit || exit->town != -1 || exit->area != -1)
                        leaveDungeonEntrance(dungeonSelectionState);
                }
                // Reward capture happens immediately after fixed-tick advance,
                // before any transition, and is independent of sound/HUD.
                const bool rewardsReady=pumpRewards();
                while (audioEvent < world.events.size()) {
                    const auto &ev=world.events[audioEvent++];
                    if(ev.kind=="hit") {
                        targetMonster=ev.target;
                        for(const auto &m:world.monsters)if(m.id==ev.target)targetHud.hit(m,world.nowMs(),std::min(m.maxHp,m.hp+ev.value));
                    }
                    if(ev.kind=="sound")audio.play(ev.name);
                }
                if (rewardsReady && !businessBlocked() && !world.combat && world.nowMs() > transitionUntil && !world.player.dead) {
                    if (const auto exit = scene.townExitAt(world.player.x, world.player.y)) {
                        if(townLocation) {
                            const auto navigation=allTowns.navigate(*townLocation,*exit);
                            if(navigation.kind==TownNavigation::Kind::Area && navigation.destination) {
                                const auto from=townLocation;enterTownArea(*navigation.destination,from);
                            } else if(navigation.kind==TownNavigation::Kind::DungeonGate)openDungeonSelection();
                            else {message="城镇道路机制未通过，诊断已保存。";
                                writeJson(reportPath("town-exit-error.json"),navigation.json());transitionUntil=world.nowMs()+1000;}
                        }
                    }
                }
                if(location=="dungeon"&&session.active()&&!autoRun) {
                    // Empty ordinary transit rooms may open, but an empty boss
                    // room/source failure is not evidence of a defeated boss.
                    bool cleared=(!session.run.room().boss||!world.monsters.empty())&&
                        std::all_of(world.monsters.begin(),world.monsters.end(),[](const Actor &m){return m.dead;});
                    session.run.room().cleared=cleared;
                    scene.updateNpcs(world, session.run.complete() && session.run.room().boss);
                    if(!resultShown&&rewardRecovery.resultsReady(rewardsReady,savePending(),session)) {
                        resultShown=true;regionUi.panel=RegionPanel::Results;world.releaseInputs();
                    }
                    if(rewardsReady&&!businessBlocked()&&cleared&&world.nowMs()>transitionUntil&&!world.player.dead&&world.activeSkill()<0){
                        auto gates=scene.script.values("[pathgate pos]");
                        for(int d=0;d<4;++d)if(session.run.destination(Direction(d))>=0&&gates.size()>=size_t(d*2+2)) {
                            if(std::abs(world.player.x-gates[d*2].get<double>())<28&&
                               std::abs(world.player.y-gates[d*2+1].get<double>()-scene.bg)<32){moveRoom(Direction(d));break;}
                        }
                    }
                }
            }
            // Fixed ticks and reward capture may have opened a pending
            // transaction after the event-phase click gate in this frame.
            suppressBlockedGameClicks(businessBlocked(),click,itemActivate);
            render.begin();
            render.viewport();
            uiMouseX=mx;uiMouseY=my;
            auto ms = world.nowMs();
            double a = world.alpha();
            if (screen == Select || screen == Create) {
                render.ui();
                if (screen == Select) {
                    std::array<CharacterSelectionSlotView,20> slots{};
                    for(int slot=0;slot<20;++slot) {
                        const auto &ch=saves["characters"][slot];if(ch.is_null())continue;
                        const auto identity=ch.contains("identity")?CharacterIdentity::fromJson(ch["identity"]):CharacterIdentity{};
                        auto key=ch.dump();auto &cached=selectionAppearances[slot];
                        if(cached.first!=key) {
                            Progression dress(catalog);dress.load(ch.value("progression",Json::object()),ch.value("level",1),ch.value("weapon",0));
                            cached={std::move(key),dress.appearance(pvf,world.characterCatalog(),identity)};
                        }
                        slots[size_t(slot)]={true,ch.value("level",1),ch.value("name",std::string("Swordman")),
                            characterName(identity.jobId),identity.jobId!=0,&cached.second};
                    }
                    const auto action=selectionUi.drawCharacters(render,slots,selected,page,{mx,my,click},int64_t(wall*1000),message);
                    selected=action.selected;page=action.page;
                    if(action.quit)quitRequested=true;
                    if(action.create&&!businessBlocked())beginCharacterCreation();
                    else if(action.start&&!businessBlocked())resumeCharacter();
                }else {
                    std::vector<CharacterCreationJobView> jobs;
                    for(const auto &definition:world.characterCatalog().definitions)
                        jobs.push_back({definition.registration.id,characterName(definition.registration.id),
                            definition.registration.id!=0,definition.runtimeDeferredByUser});
                    const auto feedback=textInput.error().empty()?message:textInput.error();
                    const auto action=selectionUi.drawCreation(render,jobs,createJob,textInput.canSubmit(),
                        {mx,my,click},int64_t(wall*1000),feedback,businessBlocked()||creationCommitPending);
                    createJob=action.selectedJob;
                    drawTextField(render,textInput,CharacterSelectionGeometry::nameField(),int64_t(wall*1000));
                    if(action.cancel&&!businessBlocked()) {screen=Select;message.clear();synchronizeTextScope();}
                    else if(action.create)createCharacter();
                }
            } else {
                render.viewport(scene);
                double px = world.player.px + (world.player.x - world.player.px) * a;
                const double py = world.player.py + (world.player.y - world.player.py) * a;
                const auto cameraFrame = sceneCamera(scene, render.sceneView, px, py);
                // Presentation-only source NUT shake, clipped to authored
                // scene width so viewport edges do not expose outside pixels.
                camera = std::clamp(cameraFrame.x+world.player.sourceSkillCameraFeedback.offsetX(ms),0.0,
                    std::max(0.0,sceneVisualWidth(scene)-render.sceneView.width));
                const double cameraY = cameraFrame.y;
                if (click && !autoRun && !menu && !map && !skillMenu && !dialog && !selectDungeon && !mapBrowser && !regionUi.open()) {
                    // Mouse events use the centred 800x600 UI coordinates;
                    // characters use the full-width scene viewport.
                    const auto point = scenePointFromUi(render.sceneView, cameraFrame, mx, my);
                    const double mouseX = point[0], mouseY = point[1];
                    const MapNpc *clickedNpc = nullptr;
                    double closest = 1e9;
                    for (const auto &npc : scene.npcs) if (npc.visible && std::abs(mouseX-npc.x)<42 &&
                         mouseY>=npc.y-npc.z-130 && mouseY<=npc.y-npc.z+12) {
                        double distance = std::abs(mouseX-npc.x) + std::abs(mouseY-(npc.y-npc.z-55));
                        if (distance < closest) { closest = distance; clickedNpc = &npc; }
                    }
                    if (clickedNpc) { talkToNpc(*clickedNpc); click=false; }
                }
                scene.draw(render, ms, camera, false, cameraY);
                struct SceneDraw { double first; std::function<void()> second; int layer=0; };
                std::vector<SceneDraw> drawQueue;
                std::vector<std::function<void()>> dropOverlays;
                bool dungeonCleared = world.combat && std::all_of(world.monsters.begin(), world.monsters.end(),
                                                                  [](auto &m) { return m.dead; });
                auto npcVisible = [&](const MapNpc &npc) {
                    return npc.visible;
                };
                for (auto &layer : scene.layers)
                    if (!layer.background && layer.order == 0) {
                        auto l = layer;
                        drawQueue.push_back(
                            {l.depthY,
                             [&, l] { render.animation(l.animation, ms, std::round(l.x - camera), l.y - cameraY); }});
                    }
                for (auto &npc : scene.npcs) {
                    if (!npcVisible(npc)) continue;
                    drawQueue.push_back({npc.y, [&, npc] {
                        if (!npc.animation.empty())
                            render.animation(npc.animation, ms - npc.appearedAt, npc.x - camera,
                                             npc.y - npc.z - cameraY, npc.direction, true, "",
                                             npc.staticFrame);
                    }});
                    if (std::abs(world.player.x - npc.x) < 110 && std::abs(world.player.y - npc.y) < 100 &&
                        ms - npcVoice > 12000) {
                        npcVoice = ms;
                        if (!npc.voice.empty()) audio.play(npc.voice);
                    }
                }
                for (const auto &object : scene.objects) {
                    if (object.destroyed || object.animation.empty()) continue;
                    double objectOrder = object.y - object.z + (object.layer == "[close]" ? 100000 : 0);
                    drawQueue.push_back({objectOrder, [&, object] {
                        render.animation(object.animation, object.animationMs, object.x - camera,
                                         object.y - object.z - cameraY, object.direction, object.loop);
                    }});
                }
                std::vector<Actor *> actors;
                actors.push_back(&world.player);
                for (auto &m : world.monsters)
                    actors.push_back(&m);
                std::stable_sort(actors.begin(), actors.end(), [](auto l, auto r) { return l->y < r->y; });
                for (auto p : actors) {
                    drawQueue.push_back(
                        {p->py + (p->y - p->py) * a, [&, p] {
                             if (p == &world.player)
                                 render.player(*p, ms, a, world.characterAppearance(), camera, cameraY, world.actorAni());
                             else render.monster(pvf,*p,ms,a,camera,cameraY,world.actHost() && world.actHost()->ownsActor(p->handle));
                         }});
                }
                if(location=="dungeon") {
                    bool open=dungeonCleared;auto gates=scene.script.values("[pathgate pos]");
                    const auto portalSceneIdentity=scene.path+":"+std::to_string(debugGeneration);
                    // The fixed auto-run rooms belong to registered DGN 1. Normal
                    // sessions use their real owner; no resource filename fallback.
                    const int portalDungeon=session.active()&&!autoRun?session.run.dungeonId:1;
                    const auto portalOwner=catalog.dungeons.find(portalDungeon);
                    for(int d=0;d<4;++d){int destination=session.active()&&!autoRun?session.run.destination(Direction(d)):
                        d==0&&room>0?room-1:d==1&&room<2?room+1:-1;
                        if(destination<0||gates.size()<size_t(d*2+2))continue;
                        const bool boss=session.active()&&!autoRun?session.run.rooms[destination].boss:destination==2;
                        if(portalOwner==catalog.dungeons.end()) {
                            const auto key="missing-dgn:"+std::to_string(portalDungeon)+":"+std::to_string(d);
                            if(portalDiagnostics.insert(key).second) {
                                render.unsupported.push_back({{"kind","pathgate-owner-missing"},
                                    {"dungeon_id",portalDungeon},{"direction",d},{"boss",boss}});
                                message="门资源未支持：找不到地下城来源 "+std::to_string(portalDungeon);
                            }
                            continue;
                        }
                        const auto &source=portalObjects.resolve(pvf,portalOwner->second,Direction(d),boss);
                        if(!source.available) {
                            const auto key=pvf.identity()+":"+portalOwner->second.path+":"+
                                std::to_string(d)+(boss?":boss":":normal");
                            if(portalDiagnostics.insert(key).second) {
                                render.unsupported.push_back({{"kind","pathgate-source-unavailable"},
                                    {"dungeon_id",portalDungeon},{"source",source.snapshot()}});
                                message="门资源未支持："+source.diagnostic;
                            }
                            continue;
                        }
                        const auto object=source.object;
                        double gx=gates[d*2].get<double>(),gy=gates[d*2+1].get<double>()+scene.bg;
                        drawQueue.push_back({gy,[&,object,gx,gy,open,d,portalSceneIdentity]{render.portal(pvf,object,ms,gx-camera,gy-cameraY,open,portalSceneIdentity,d);}});
                    }
                    const auto highlightedPickup=nearestPickup();
                    if(session.active()&&!autoRun)for(auto it=progress.state["drops"].begin();it!=progress.state["drops"].end();++it){const auto &drop=it.value();
                        if(drop.value("claimed",false)||drop.value("run",std::string())!=session.run.token||drop.value("room",-1)!=session.run.current)continue;
                        double x=drop.value("x",0.0),y=drop.value("y",0.0);Json items=drop["items"];
                        bool nearby=it.key()==highlightedPickup;
                        const auto gold=drop.value("gold",0);
                        std::string label="金币 × "+std::to_string(gold);
                        if(!items.empty()) {
                            const auto id=items.front().value("id",-1);
                            label=itemDropSprite(id).evidence.value("name","物品 #"+std::to_string(id));
                        }
                        std::vector<DropSprite> sprites;
                        for(const auto &entry:items) {
                            const auto id=entry.value("id",-1);
                            sprites.push_back(itemDropSprite(id));
                        }
                        if(gold>0) {
                            if(!goldDropSprite){goldDropSprite=prepareGoldDropSprite(pvf,assets);
                                writeJson(reportPath("drops/gold.json"),{{"source",goldDropSprite->evidence},{"diagnostics",goldDropSprite->diagnostics}});}
                            sprites.push_back(*goldDropSprite);
                        }
                        drawQueue.push_back({y,[&,x,y,sprites,nearby]{
                            double offset=-12.0*double(sprites.empty()?0:sprites.size()-1);
                            for(const auto &sprite:sprites) {
                                if(!sprite.image.empty()) {
                                    const auto origin=sprite.drawingOrigin(x-camera+offset,y-cameraY);
                                    if(nearby)render.outlinedSprite(sprite.image,sprite.frame,origin[0],origin[1],{255,235,80,255});
                                    else render.sprite(sprite.image,sprite.frame,origin[0],origin[1]);
                                }
                                offset+=24;
                            }
                        }});
                        auto labelCopy = label;
                        dropOverlays.push_back([&,x,y,labelCopy,nearby] {
                            int plaqueWidth = render.textWidth(labelCopy, 12) + 16;
                            float plaqueX = float(x - camera - plaqueWidth / 2.0), plaqueY = float(y - cameraY - 42);
                            render.rect(plaqueX, plaqueY, plaqueWidth, 20,
                                nearby?SDL_Color{72,52,6,245}:SDL_Color{0,0,0,220});
                            render.rect(plaqueX + 1, plaqueY + 1, plaqueWidth - 2, 18,
                                        nearby ? SDL_Color{255,245,100,255} : SDL_Color{193,210,174,245}, false);
                            if(nearby)render.rect(plaqueX,plaqueY,plaqueWidth,20,{255,235,80,255},false);
                            render.text(labelCopy, plaqueX + 8, plaqueY + 2, 12, {255, 255, 238, 255});
                            if (nearby) {
                                // This prompt uses the same claim range as X.
                                render.text("X 拾取",float(x-camera-render.textWidth("X 拾取",12)/2.0),plaqueY-18,12,{255,255,240,255});
                            }
                        });
                    }
                }
                for(const auto &fx:world.effects){if(ms<fx.born)continue;
                    double depth=fx.groundRender?-100000.0:fx.py+(fx.y-fx.py)*a;
                    if(fx.parentId==0&&!fx.groundRender)depth=world.player.py+(world.player.y-world.player.py)*a;
                    drawQueue.push_back({depth,[&,fx]{render.effect(fx,ms,a,camera,cameraY);},fx.layer});
                }
                std::stable_sort(drawQueue.begin(), drawQueue.end(),
                                 [](auto &l, auto &r) { return l.first!=r.first?l.first<r.first:l.layer<r.layer; });
                for (auto &q : drawQueue) q.second();
                if(world.actHost()) render.actionSpeech(world,world.actHost()->speechBubbles(),a,camera,cameraY);
                scene.draw(render, ms, camera, true, cameraY);
                for (auto &overlay : dropOverlays) overlay();
                for (auto &npc : scene.npcs)
                    if (npcVisible(npc))
                        render.text(npc.name, float(npc.x-camera-render.textWidth(npc.name,12)/2.0),
                                    float(npc.y-npc.z-cameraY-125),12,{218,201,158,255});
                render.sceneFooter();
                render.ui();
                if(!selectDungeon&&!map) {
                if(world.combat){targetHud.observe(world.monsters,ms);targetHud.draw(render,pvf,ms,world.player.maxHp);regionUi.minimap(render,session);}
                else if(!menu&&!map&&!dialog&&!skillMenu)
                    regionUi.townMinimap(render,catalog.townAreas,townLocation?townLocation->areaId:0,
                        world.player.x,world.player.y,scene.width,600,
                        location=="room"?"赛利亚房间":location=="town"?"艾尔文防线":scene.name,
                        scene.npcs,mx,my,click);
                if (hud.draw(render, world, mx, my, click && !mapBrowser)) {
                    menu = !menu;
                    world.releaseInputs();
                }
                render.text(townLocation && !world.combat ? allTowns.at(allTowns.require(townLocation->townId,townLocation->areaId)).townName+" / "+scene.name :
                            location == "room"       ? std::string("赛利亚房间")
                            : location == "town"     ? "艾尔文防线"
                            : location == "entrance" ? "洛兰入口"
                                                     : explorationMap?explorationMap->name:session.active()?catalog.dungeons.at(session.run.dungeonId).name:"洛兰",
                            12, 10, 20);
                const char *keys[] = {"A", "S", "D", "F", "G", "H", "Q", "W", "E", "R", "T", "Y", "Space"};
                if (testBranch.active())
                    render.text("隔离测试进度 · 返回选角恢复正常存档 · F9 测试窗", 10, 38, 14, {236, 189, 83, 255});
                // Adapter status text is a diagnostic, not source HUD. Audit and
                // explicit debug runs keep it; ordinary and smoke playback match
                // the source screen instead of carrying an unremovable watermark.
                if (audit || profileAudit || contentAudit || effectsFixture || debug)
                    render.text("战斗测试版 · 伤害与成长参数仍在核对", 445, 10, 13);
                if (debug) {
                    render.text("Tick " + std::to_string(world.tick) + " " + world.player.animation +
                                    " stage " + std::to_string(world.stage()),
                                10, 65, 14);
                    render.text("X " + std::to_string(int(world.player.x)) + " Y " +
                                    std::to_string(int(world.player.y)) + " Z " +
                                    std::to_string(int(world.player.z)),
                                10, 85, 14);
                }
                if(explorationMap && !mapBrowser && !menu && !map && !skillMenu && !dialog) {
                    render.text("单图探索 · 机制诊断 "+std::to_string(explorationDiagnostics.size())+" 项 · F7 全地图",10,64,13);
                    if(render.button("返回城镇",655,50,125,28,mx,my,click)) {returnToTown();}
                }
                }
                bool cleared = world.combat && std::all_of(world.monsters.begin(), world.monsters.end(),
                                                           [](auto &m) { return m.dead; });
                if (cleared && autoRun && !effectsFixture) {
                    render.text(room == 2 ? "地下城通关" : "房间已清理", 320, 90, 26);
                    if (render.button(room == 2 ? "结算并返回" : "前往右侧传送门", 310, 135, 180, 36, mx, my,
                                      click)) {
                        if (room == 2) {
                            loadScene("town");
                        } else {
                            message = "沿地面前往右侧传送门";
                        }
                    }
                }
                if (world.player.dead) {
                    render.text("角色倒地", 315, 220, 24);
                    if(render.button("返回城镇",300,270,200,36,mx,my,click)){returnToTown(true);}
                }
                if (menu || skillMenu || map || dialog) {
                    if(!map&&(!skillMenu || configureSkills)) {
                        render.rect(100, 65, 600, 450, {18, 20, 29, 242});
                        render.rect(100, 65, 600, 450, {190, 160, 96, 255}, false);
                    }
                    if (menu && settingsMenu) {
                        render.text("声音与战斗测试", 280, 86, 24);
                        auto volumeRow = [&](const std::string &label, double &volume, int y) {
                            render.text(label, 145, y + 6, 18);
                            render.text(std::to_string(int(std::lround(volume * 100))) + "%", 425, y + 6, 18);
                            bool changed = false;
                            if (render.button("-", 515, y, 44, 32, mx, my, click)) {
                                volume = std::max(0.0, (std::lround(volume * 10) - 1) / 10.0); changed = true;
                            }
                            if (render.button("+", 575, y, 44, 32, mx, my, click)) {
                                volume = std::min(1.0, (std::lround(volume * 10) + 1) / 10.0); changed = true;
                            }
                            if (changed) { applyAudioVolumes(); saveSettings(); }
                        };
                        volumeRow("总音量", audioVolumes.master, 140);
                        volumeRow("背景音乐", audioVolumes.music, 185);
                        volumeRow("技能与音效", audioVolumes.effects, 230);
                        volumeRow("环境声音", audioVolumes.ambient, 275);
                        auto hpRow = [&](const std::string &label, int &multiplier, int y) {
                            render.text(label, 145, y + 6, 18);
                            render.text(std::to_string(multiplier) + " 倍", 425, y + 6, 18);
                            if (render.button("-",515,y,44,32,mx,my,click,!world.usesSourceGrowth()) && multiplier > 1) {
                                --multiplier; saveSettings();
                            }
                            if (render.button("+",575,y,44,32,mx,my,click,!world.usesSourceGrowth()) && multiplier < 10) {
                                ++multiplier; saveSettings();
                            }
                        };
                        hpRow("普通怪物血量", demoBalance.normalHpMultiplier, 320);
                        hpRow("首领血量", demoBalance.bossHpMultiplier, 365);
                        render.text(world.usesSourceGrowth()?"来源血量规则已生效；历史演示倍率不参与计算":"血量倍率在下一次进入新副本时生效",145,412,16);
                        if (session.active() && session.monsterStatPolicy=="legacy-demo-v1") render.text("本次历史副本：普通 " + std::to_string(session.balance.normalHpMultiplier) +
                            " 倍 / 首领 " + std::to_string(session.balance.bossHpMultiplier) + " 倍", 145, 437, 16);
                        if (render.button("返回菜单", 285, 470, 230, 30, mx, my, click)) settingsMenu = false;
                    } else if (menu) {
                        render.text("系统菜单", 330, 85, 24);
                        if (render.button("声音/测试设置", 120, 135, 145, 34, mx, my, click)) settingsMenu = true;
                        if (render.button("继续游戏", 275, 135, 250, 34, mx, my, click))
                            menu = false;
                        if (render.button(std::string("垂直同步：") +
                                              (render.vsync ? "跟随显示器" : "关闭，无上限"),
                                          230, 185, 340, 34, mx, my, click)) {
                            render.setVsync(!render.vsync);
                            saveDisplay();
                        }
                        if (render.button("F9 独立 Beta 测试窗口", 230, 230,340,34,mx,my,click)) showDebugWindow();
                        if (render.button("全部地图 F7", 120, 230,105,34,mx,my,click)) openMapBrowser();
                        if (render.button("全部城镇 F10", 575, 230,110,34,mx,my,click)) openMapBrowser(true);
                        render.text(testBranch.active()?"当前为隔离测试分支":"当前为正常进度；启用测试后自动隔离",230,275,14);
                        if (render.button("分辨率：" + std::to_string(render.outputSize()[0]) + " × " +
                                              std::to_string(render.outputSize()[1]),
                                          230, 315, 340, 30, mx, my, click)) {
                            auto modes = render.modes();
                            auto size = render.outputSize();
                            auto it = std::find(modes.begin(), modes.end(), size);
                            resolutionIndex =
                                it == modes.end() ? 0 : (int(it - modes.begin()) + 1) % int(modes.size());
                            render.resize(modes[resolutionIndex][0], modes[resolutionIndex][1]);
                            full = false;
                            windowWidth = modes[resolutionIndex][0]; windowHeight = modes[resolutionIndex][1];
                            saveDisplay();
                        }
                        if (render.button(full ? "退出无边框全屏" : "无边框全屏", 230, 350, 340, 30, mx, my,
                                          click)) {
                            full = !full;
                            render.fullscreen(full);
                            if (!full) render.resize(windowWidth, windowHeight);
                            saveDisplay();
                        }
                        if (render.button("返回选角并保存", 230, 390, 340, 34, mx, my, click)) {
                            if(!businessBlocked()&&leaveTestBranch()) {
                                menu = false;
                                screen = Select;
                                audio.music("M_CHARACTER_SELECT");
                            }
                        }
                        render.text("F3 诊断  F8反馈包  F9独立测试窗", 145, 450, 15);
                    } else if (skillMenu) {
                        if(configureSkills) {
                            if(skillConfigurationUi.draw(render,world,mx,my,click,testBranch.active()&&world.debugOverrides().enabled))persist();
                            if(render.button("返回技能学习",125,535,175,27,mx,my,click)){
                                if(world.experimentalSkillPreviewEnabled()){
                                    const auto result=world.setExperimentalSkillPreviewEnabled(false);message=result.message;
                                    if(result.ok){persist();configureSkills=false;skillLearningUi.reset();}
                                }else configureSkills=false;
                            }
                        } else {
                        const auto action=skillLearningUi.draw(render,world,progress.level(),testBranch.active(),mx,my,click);
                        if(action.purchase)purchaseSkill(*action.purchase,action.quote);
                        if(action.resetTest){world.resetTestSkillLearning();persist();message="测试点池和技能覆盖已清除";}
                        if(action.openTestPreview) {
                            const auto result=world.setExperimentalSkillPreviewEnabled(true);message=result.message;
                            if(result.ok){configureSkills=true;skillConfigurationUi.reset();persist();}
                        }
                        if(action.configure)configureSkills=true;
                        if(action.close){skillMenu=false;world.releaseInputs();}
                        }
                    } else if (map) {
                        if(location=="dungeon")regionUi.minimap(render,session,true);
                        else try {
                            if(!worldMapBound){worldMapUi.bind(pvf,assets);writeJson(reportPath("world-map-source.json"),worldMapUi.snapshot());worldMapBound=true;}
                            const auto action=worldMapUi.draw(render,townLocation?townLocation->townId:-1,townLocation?townLocation->areaId:-1,
                                world.player.x,world.player.y-scene.bg,{mx,my,click},int64_t(SDL_GetTicks64()));
                            if(!action.worldmapPath.empty()&&setDungeonSelectionWorldmap(action.worldmapPath)) {
                                dungeonSelectionState=enterDungeonSelection(dungeonSelectionModel,{});selectDungeon=dungeonSelectionState.open;
                                selectionUi.startDungeonPresentation(dungeonSelectionState,int64_t(SDL_GetTicks64()));
                                dungeonSelectionLayout=selectionUi.dungeonLayout(dungeonSelectionModel,dungeonSelectionState.selectedDungeon);
                                map=false;world.releaseInputs();
                            }
                        }catch(const std::exception &error){message="世界地图失败："+std::string(error.what());map=false;}
                    }
                }
                if (selectDungeon) {
                    selectionUi.drawDungeon(render,dungeonSelectionModel,dungeonSelectionLayout,dungeonSelectionState,
                        {world.characterLevel,true,dungeonDifficultyCount,true},{mx,my,false},int64_t(SDL_GetTicks64()));
                }
                if(regionUi.open()){
                    regionUi.draw(render,world,progress,session,playerAppearance,mx,my,click,itemActivate);
                    if(regionUi.advancementRequested&&!businessBlocked()){
                        if(testBranch.active()) {
                            message="请先返回角色选择，退出隔离测试后再设置正常身份";
                            regionUi.message=message;
                        } else {
                        const auto target=*regionUi.advancementRequested;
                        const auto uuid=saves["characters"][selected].value("uuid",std::string());
                        CharacterAdvancementRequest request;
                        request.requestId="identity:"+uuid+":"+std::to_string(store.generation())+":"+
                            std::to_string(target.growtype)+":"+std::to_string(target.awakening);
                        request.expectedIdentity=world.identity();request.target=target;
                        request.expectedGeneration=store.generation();request.npcId=regionUi.npc;
                        world.releaseInputs();
                        const auto result=advancementTransaction.submit(store,selected,world,progress,scene,request,captureRegionSession(location));
                        message=result.message;
                        regionUi.message=message;
                        if(!result.error.empty())std::cerr<<"GSD identity: "<<result.error<<std::endl;
                        writeJson(reportPath("last-gsd-identity.json"),result.json());
                        if(result.ok){playerAppearance=world.characterAppearance();regionUi.close();skillLearningUi.reset();++debugGeneration;}
                        }
                    }
                    if(regionUi.changed){
                        if(regionUi.equipmentPublished) playerAppearance=world.characterAppearance();
                        else syncEquipment();
                        persist();
                    }
                    if(regionUi.returnTown){returnToTown();}
                    if(regionUi.learnSkillsRequested){
                        configureSkills=false;skillMenu=true;menu=map=dialog=selectDungeon=false;
                        world.releaseInputs();
                    }
                }
                if(location=="dungeon"&&session.active()&&session.run.complete()&&!regionUi.open()){
                    if(render.button("通关结算",325,90,150,32,mx,my,click)&&rewardRecovery.resultsReady(true,savePending(),session))regionUi.panel=RegionPanel::Results;
                }
                if(!world.combat&&!regionUi.open()&&!menu&&!skillMenu&&!map&&!dialog&&!selectDungeon&&!mapBrowser)
                    render.text("Enter 交谈   I 物品栏   L 任务   M 地图",230,485,14);

                if(mapBrowser) {
                    const bool unrestricted=true;
                    render.rect(25,40,750,510,{15,18,29,250});
                    render.rect(25,40,750,510,{190,160,96,255},false);
                    render.text(townBrowser?"全部城镇 · 提前开放源区域（F10）":unrestricted?"全部地图 · 隔离测试（不限等级/任务）":"全部地图 · 开启 F9 测试后进入",45,55,22);
                    render.text(townBrowser?"查询城镇 / 路径：":"id: / path: / name:",45,90,14);
                    const SelectionRect queryField{215,86,440,24};
                    render.rect(float(queryField.x),float(queryField.y),float(queryField.width),float(queryField.height),{8,10,20,255});
                    render.rect(float(queryField.x),float(queryField.y),float(queryField.width),float(queryField.height),{164,143,95,255},false);
                    drawTextField(render,textInput,queryField,int64_t(wall*1000),14);
                    if(render.button("搜索",670,86,75,25,mx,my,click,textInput.canSubmit()))refreshMapBrowser();
                    std::string queryHint=townBrowser?"↑↓选择  PgUp/PgDn翻页  Enter查询/进入  Esc关闭；所有源城镇提前开放":
                        mapQueryDirty?"Enter 执行查询；名称索引分帧加载，界面继续响应。":"↑↓选择  PgUp/PgDn翻页  Enter进入  Esc关闭  F9开启测试模式";
                    if(!townBrowser&&allMaps) {
                        const auto indexing=allMaps->nameIndexProgress();
                        if(!indexing.complete)queryHint="地图名称索引 "+std::to_string(indexing.indexed)+" / "+std::to_string(indexing.total)+
                            (mapPage.matchesComplete?"；当前id/路径结果已完整":"；名称结果尚未完整，请稍后进入");
                    }
                    if(!textInput.error().empty())queryHint=textInput.error();
                    render.text(queryHint,45,115,12);
                    for(size_t row=0;row<mapPage.entries.size();++row) {
                        const auto &entry=mapPage.entries[row];const int y=143+int(row)*36;
                        if(selectedMap && *selectedMap==entry.index) render.rect(38,y-2,722,35,{70,64,42,255});
                        const auto label=(entry.id?std::to_string(*entry.id):std::string("路径"))+"  "+(entry.name.empty()?entry.path:entry.name)+
                            (townBrowser?std::string():entry.minimumLevelKnown?"  Lv."+std::to_string(entry.minimumLevel):"  信息加载中");
                        if(render.button(label,42,y,704,18,mx,my,click)) selectedMap=entry.index;
                        render.text(entry.path,48,y+19,10,{174,185,203,255});
                    }
                    if(render.button("上一页",42,477,95,25,mx,my,click,mapOffset>0)) {
                        mapOffset=mapOffset>=9?mapOffset-9:0;refreshMapBrowser();
                    }
                    if(render.button("下一页",143,477,95,25,mx,my,click,mapOffset+9<mapPage.total)) {
                        mapOffset+=9;refreshMapBrowser();
                    }
                    render.text(std::to_string(mapOffset+1)+" / "+std::to_string(mapPage.total),255,481,13);
                    bool allowed=false;
                    if(selectedMap) allowed=townBrowser?allTowns.admitted(*selectedMap):unrestricted&&mapPage.matchesComplete;
                    allowed=allowed&&!textInput.composing()&&!mapQueryDirty;
                    if(render.button(townBrowser?"进入选中城镇区域":"进入选中地图",480,477,160,27,mx,my,click,allowed) && selectedMap)
                        enterExplorationMap(*selectedMap);
                    if(render.button("关闭",650,477,95,27,mx,my,click)) {mapBrowser=false;synchronizeTextScope();}
                    render.text(townBrowser?"正常与测试均可提前进入；原道路切图，缺失业务保留诊断。F7 全MAP / F10 全城镇。":"地图机制与区域业务尚在实现；诊断记录随反馈导出。单图探索不产生副本结算。",42,516,12);
                }

                if (!message.empty())
                    render.text(message, 10, 505, 13);
            }
            if (effectsFixture && effectsCase >= 0) {
                render.ui();
                const auto &c = effectsCases[effectsCase];
                render.rect(8, 65, 784, 76, {0, 0, 0, 220});
                render.text("效果诊断样本 " + std::to_string(effectsCase + 1) + "/" + std::to_string(effectsCases.size()) +
                            "  " + c.key, 16, 70, 16, {255, 231, 148, 255});
                render.text(c.monster + "  /  " + c.side + (c.strong ? " / strong" : " / weak"), 16, 95, 12);
                const std::string route = world.monsters.empty() ? "" : world.monsters.front().deathRoute;
                render.text("route: " + route + "  |  blood vigorous: " + std::to_string(world.bloodVigorousLevel) +
                            "  |  isolated fixture, Esc to stop", 16, 117, 12);
                // Hit350 + burst220 + visibility700 = absolute cutoff1270ms.
                // Capture the full-opacity/fade/cutoff boundary as real frames.
                const int phases[] = {0, 320, 390, 470, 620, 850, 1120, 1200, 1250, 1270, 1300, 1750, 2450, 3800, 4300};
                const auto elapsed = world.nowMs() - effectsCaseStart;
                for (int phase = 0; phase < int(std::size(phases)); ++phase)
                    if (elapsed >= phases[phase] && effectsCapturePhases.insert(phase).second) {
                        const auto f = reportPath("captures/effects-" + c.key + "-" + std::to_string(phase) + ".png");
                        render.screenshot(f); captures.push_back(f.u8string());
                        effectsSamples.push_back({{"case", c.key}, {"phase", phase}, {"elapsed_ms", elapsed},
                            {"requested_ms", phases[phase]}, {"capture", f.u8string()}, {"state", effectsState()}});
                    }
            }
            if (!shot.empty() && frames > 3) {
                render.screenshot(fs::u8path(shot));
                shot.clear();
            }
            if (autoRun && !effectsFixture && world.combat) {
                int stamp = int(wall / 4);
                double local = wall - stamp * 4;
                const double phases[] = {0.10, 0.30, 0.65, 1.10, 1.60, 2.40, 3.50};
                for (int phase = 0; phase < 7; phase++)
                if (local >= phases[phase] && skillCaptures.insert(stamp * 7 + phase).second) {
                    auto f = (reportPath("captures").generic_string() + "/skill-") + std::to_string(stamp % 13) + "-" +
                             std::to_string(stamp) + "-phase-" + std::to_string(phase) + ".png";
                    render.screenshot(f);
                    captures.push_back(f);
                    skillSamples.push_back({{"step", stamp}, {"phase", phase}, {"tick", world.tick},
                        {"local_seconds", local}, {"capture", f}, {"state", world.snapshot()}});
                }
                // Preserve the canonical seven samples while also observing the
                // short Vane Slash black-core / Hop Smash descending-sword
                // intervals skipped between 0.65s and 1.10s. These diagnostic
                // captures do not change gameplay timing or ordinary saves.
                const double details[] = {0.80, 0.90, 1.35};
                if (!flowSmoke) for (int phase = 0; phase < 3; ++phase)
                if (local >= details[phase] && skillDetailCaptures.insert(stamp * 3 + phase).second) {
                    auto f = reportPath("captures/detail-" + std::to_string(stamp % 13) + "-" +
                                        std::to_string(stamp) + "-phase-" + std::to_string(phase) + ".png");
                    render.screenshot(f); captures.push_back(f.u8string());
                    skillDetailSamples.push_back({{"step", stamp}, {"phase", phase}, {"tick", world.tick},
                        {"requested_seconds", details[phase]}, {"local_seconds", local},
                        {"capture", f.u8string()}, {"state", world.snapshot()}});
                }
            }
            if (flowSmoke && wall - int(wall / flowSceneSeconds) * flowSceneSeconds > 0.8 &&
                sceneCaptures.insert(int(wall / flowSceneSeconds)).second) {
                auto f = reportPath("captures/scene-" + std::to_string(int(wall / flowSceneSeconds)) + "-" + location + ".png");
                render.screenshot(f); captures.push_back(f.u8string());
            }
            frameStatistics.record(dt);
            peakEffects = std::max(peakEffects, int(world.effects.size()));
            if(quit || effectsFinished || (autoRun&&!effectsFixture&&wall>=autoSeconds) || (quitAfter>0&&wall>=quitAfter))
                render.screenshot(reportPath("last-frame.png"));
            if(savePending()) {
                render.rect(110,220,580,150,{15,18,28,250});
                render.text("保存尚未完成，模拟与业务操作已暂停",145,240,20);
                render.text(message,145,275,14);
                if(render.button("重试当前保存",270,315,250,34,mx,my,retrySaveClick)) {
                    try {
                        if(advancementTransaction.pending()) {
                            const auto result=advancementTransaction.retry(store,world);message=result.message;
                            writeJson(reportPath("last-gsd-identity.json"),result.json());
                            if(result.ok){playerAppearance=world.characterAppearance();regionUi.close();skillLearningUi.reset();++debugGeneration;}
                        }
                        else if(learningTransaction.pending()) message=learningTransaction.retry(store,world).message;
                        else { testBranch.select(store).retryPending(); message="保存已恢复"; }
                        if(creationCommitPending&&!store.hasPendingCommit()) {
                            creationCommitPending=false;screen=Select;message="角色已创建并保存。";
                        }
                        if(screen==Game&&!savePending()) {
                            auto &writer=testBranch.select(store);
                            if(!rewardService.acknowledgeCheckpoint(progress,world,writer,selected))rewardFailure();
                        }
                        synchronizeTextScope();
                    } catch(const std::exception &error) { message="保存失败："+std::string(error.what()); }
                }
            }
            else if(screen==Game&&rewardService.blocked(progress)) {
                render.rect(110,220,580,150,{15,18,28,250});
                render.text("奖励事务等待完成，现场与掉落账本保留",140,240,18);
                render.text(message,140,275,14);
                if(render.button("重试奖励与保存",270,315,250,34,mx,my,retryRewardClick)) {
                    rewardRecovery.deferRetry(SDL_GetTicks64());(void)pumpRewards();
                }
            }
            if(quitRequested) {
                world.releaseInputs();
                if(rewardRecovery.allowControlledExit(autoRun,screen==Game,rewardRecoveryHooks))quit=true;
                else message="退出前保存未完成，请重试；奖励现场继续保留。";
            }
            synchronizeTextScope();
            if(screen==Game)drawScenePresentation(render,scenePresentation,int64_t(SDL_GetTicks64()));
            render.present();
            auto currentDebugContext=debugContext(); currentDebugContext.simulationPaused=pause;
            debugService.refresh(world,currentDebugContext);
            if(debugWindow) debugWindow->draw(debugService.snapshot(),SDL_GetTicks64());
            ++frames;
            if (std::chrono::duration<double>(now - lastTitle).count() > 1) {
                double sec = std::chrono::duration<double>(now - lastTitle).count();
                static uint64_t lastCount = 0;
                render.title(std::to_string(render.viewWidth) + "x" + std::to_string(render.viewHeight) +
                             " | DNF Native | " + std::to_string(int((frames - lastCount) / sec)) +
                             " FPS | render independent");
                lastCount = frames;
                lastTitle = now;
            }
            if (effectsFinished || (autoRun && !effectsFixture && wall >= autoSeconds) || (quitAfter > 0 && wall >= quitAfter))
                quitRequested = true;
        }
        // Controlled exit already checkpointed; do not publish a second generation here.
        const auto frameSummary = frameStatistics.snapshot();
        writeJson(
            reportPath("runtime.json"),
            {{"run_id", runId_}, {"started_unix_ms", startedMs_}, {"mode", effectsFixture ? "combat-effects-fixture" : flowSmoke ? "flow-smoke" : autoRun ? "skill-smoke" : "interactive"},
             {"pvf_files", pvf.count()},
             {"npk_entries", assets.count()},
             {"output_size", render.outputSize()},
             {"frames", frames},
             {"ticks", world.tick},
             {"max_frame_ms", maxFrameNs / 1e6},
             {"median_frame_ms", frameSummary.windowMedianNanoseconds / 1e6},
             {"p95_frame_ms", frameSummary.windowP95Nanoseconds / 1e6},
             {"frame_statistics", {{"percentile_scope", "most-recent-frame-window"},
                {"capacity", frameSummary.capacity}, {"window_samples", frameSummary.windowSamples},
                {"total_samples", frameSummary.totalSamples}, {"lifetime_max_ms", frameSummary.lifetimeMaxNanoseconds / 1e6}}},
             {"peak_effects", peakEffects},
             {"captures", captures},
             {"state", world.snapshot()},
             {"asset_errors", assets.errors},
             {"render_errors", render.errors}, {"ani_render_policy",render.renderProfileReport()},
             {"render_unsupported",render.unsupported}, {"region_issues",catalog.issues},
             {"portal_sources",portalObjects.snapshot()},{"portal_visuals",render.portalSourceReport()},
             {"font",render.fontReport()},
             {"progression",progress.state}, {"session",captureRegionSession(location)},
             {"beta_tools",debugService.snapshot().json()}, {"test_branch",testBranch.active()},
             {"test_save_directory",testBranch.directory().u8string()},
             {"demo_settings", {{"requested_balance",demoBalance.describe()}, {"audio",audioVolumes.describe()}}},
             {"audio", audio.snapshot()},
             {"audio_errors", audio.errors},
             {"unresolved_sound_ids", audio.missing()},
             {"duration_seconds",
              std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count()}});
        writeJson(reportPath("inputs.json"), world.inputs());
        writeJson(reportPath("events.json"), world.eventLog());
        if (autoRun)
            writeJson(reportPath("skill-samples.json"), {{"scope", "actual smoke placements and sampled state; no PC timing parity claim"},
                {"trials", skillTrials}, {"samples", skillSamples}});
        if (autoRun && !flowSmoke && !effectsFixture)
            writeJson(reportPath("skill-detail-samples.json"), {
                {"scope", "supplemental real framebuffer samples of short effect windows; diagnostic placements, no PC timing parity claim"},
                {"samples", skillDetailSamples}});
        if (effectsFixture)
            writeJson(reportPath("effects-fixture.json"), {
                {"scope", "Artificial visible combat-effects fixture; diagnosticHit injects accepted hits, not collision/input acceptance"},
                {"isolated_save_directory", saveDirectory_.u8string()}, {"completed", effectsFinished},
                {"simulation_policy", "normal 60 Hz simulation; cap submission at one tick per rendered frame only in fixture"},
                {"expected_cases", effectsCases.size()}, {"trials", effectsTrials}, {"samples", effectsSamples}});
        writeJson(reportPath("resources.json"), {{"run_id", runId_}, {"pvf_reads", pvf.reads()},
                  {"npk_reads", assets.reads()}, {"scope", "actually accessed; not a complete dependency closure"}});
        writeJson(reportPath("run.json"), {{"run_id", runId_}, {"started_unix_ms", startedMs_}, {"status", "completed"},
            {"binary_sha256",binaryHash},{"identity",contentIdentity.json()},
            {"binary_path",exe.u8string()}, {"save_directory",fs::absolute(saveDirectory_).u8string()}});
        SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        try {
            writeJson(reportPath("fatal.json"), {{"run_id", runId_}, {"started_unix_ms", startedMs_}, {"error", e.what()}});
            writeJson(reportPath("run.json"), {{"run_id", runId_}, {"started_unix_ms", startedMs_}, {"status", "failed"}});
        } catch (...) {
        }
        const std::string failure="运行失败，详细原因已写入日志。\n"+std::string(e.what())+
            "\n日志目录："+reportPath("fatal.json").parent_path().u8string();
        if(showFatalWindow)SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"DNF 运行错误",failure.c_str(),nullptr);
        return 1;
    }
}

} // namespace dnf::app
