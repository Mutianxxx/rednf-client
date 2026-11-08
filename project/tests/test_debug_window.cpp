#include "dnf/debug_window.hpp"
#include "dnf/renderer.hpp"
#include <stdexcept>

namespace dnf {
namespace {
// Never opens a frontend: this entry refuses any driver other than SDL dummy.
// SDL initialization is scoped after the existing source/font tests; windows,
// renderers and private font registrations are destroyed before video teardown.
struct DummyVideo {
    bool initialized = false;
    DummyVideo() {
        const char *configured = SDL_getenv("SDL_VIDEODRIVER");
        if (!configured || std::string(configured) != "dummy")
            throw std::runtime_error("Debug-window logic checks require SDL_VIDEODRIVER=dummy; no frontend was started");
        if (!(SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO)) {
            if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) throw std::runtime_error(SDL_GetError());
            initialized = true;
        }
        const char *current = SDL_GetCurrentVideoDriver();
        if (!current || std::string(current) != "dummy") {
            if (initialized) SDL_QuitSubSystem(SDL_INIT_VIDEO);
            initialized = false;
            throw std::runtime_error("Existing SDL video driver is not dummy; debug window test refused");
        }
    }
    ~DummyVideo() { if (initialized) SDL_QuitSubSystem(SDL_INIT_VIDEO); }
};
SDL_Event debugClick(uint32_t window, int x, int y) {
    SDL_Event event{}; event.type = SDL_MOUSEBUTTONDOWN;
    event.button.windowID = window; event.button.button = SDL_BUTTON_LEFT;
    event.button.x = x; event.button.y = y;
    return event;
}
SDL_Event debugKey(uint32_t window, SDL_Keycode key) {
    SDL_Event event{}; event.type = SDL_KEYDOWN;
    event.key.windowID = window; event.key.keysym.sym = key;
    return event;
}
} // namespace

Json runDebugWindowTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    const auto check = [&](bool condition, const char *message) {
        if (!condition) throw std::runtime_error(std::string("Beta debug window: ") + message);
        checks.push_back(message);
    };
    DummyVideo video;
    const DebugContext context{{"dummy-content","dummy-character","dummy-run",1},1,true};
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    DebugService service;
    service.refresh(world,context);
    RendererOptions mainOptions;
    mainOptions.title = "Dummy-only routing fixture";
    mainOptions.shown = false; mainOptions.vsync = false;
    Renderer mainRenderer(assets,mainOptions);
    const auto mainId = SDL_GetWindowID(mainRenderer.window());
    DebugWindow window(assets,service);
    const auto id = window.windowId();
    auto *native = SDL_GetWindowFromID(id);
    auto *renderer = SDL_GetRenderer(native);
    SDL_RendererInfo info{};
    check(id && id != mainId && renderer && renderer != mainRenderer.raw(),
        "Test window owns a different SDL window and renderer from the simulated main window");
    check(SDL_GetRendererInfo(renderer,&info) == 0 && !(info.flags & SDL_RENDERER_PRESENTVSYNC),
        "Second renderer is created without present-vsync and cannot throttle game simulation through its swap policy");
    check(!window.visible() && (SDL_GetWindowFlags(native) & SDL_WINDOW_HIDDEN),
        "The test-tools constructor leaves the independent window hidden");
    check(!window.handleEvent(debugKey(mainId,SDLK_F9)) && !window.visible(),
        "Main-window F9 is left for application routing instead of being captured by the test window");
    window.show();
    check(window.visible() && !(SDL_GetWindowFlags(native) & SDL_WINDOW_HIDDEN),
        "Application-routed show makes the test window available under the dummy driver");
    window.draw(service.snapshot(),100);
    SDL_Event foreignResize{}; foreignResize.type = SDL_WINDOWEVENT;
    foreignResize.window.windowID = mainId; foreignResize.window.event = SDL_WINDOWEVENT_SIZE_CHANGED;
    check(!window.handleEvent(foreignResize) && !window.handleEvent(debugClick(mainId,100,180)),
        "Foreign resize and mouse events never reach test-window controls");
    const auto beforeEnable = world.debugOverrides();
    check(window.handleEvent(debugClick(id,100,180)) && world.debugOverrides() == beforeEnable &&
          service.hasEnableRequest(context.target),
        "Clicking the test master switch only queues an enable request until the application boundary");
    service.applyAtBoundary(world,context);
    window.draw(service.snapshot(),140);
    check(world.debugOverrides().enabled,"The displayed enable request becomes effective through the command service");
    window.handleEvent(debugClick(id,100,222));
    check(!world.debugOverrides().hpLock,"An HP checkbox does not optimistically mutate actual World resources");
    service.applyAtBoundary(world,context);
    window.draw(service.snapshot(),180);
    check(world.debugOverrides().hpLock && !world.debugOverrides().mpLock,
        "The independent HP control queues only its own confirmed override");
    window.handleEvent(debugClick(id,500,222));
    service.applyAtBoundary(world,context);
    window.draw(service.snapshot(),220);
    check(world.debugOverrides().hpLock && world.debugOverrides().mpLock,
        "The separate MP control is routed independently of HP");
    const auto tick = world.tick;
    window.handleEvent(debugClick(id,350,420));
    service.applyAtBoundary(world,context);
    check(world.tick == tick && service.takeSingleStepRequest() && !service.takeSingleStepRequest(),
        "The single-step button queues one paused request without advancing the simulation or duplicating consumption");
    world.configureSourceActions("dummy-event-ai-static:"+sha256(assets.staticBytes("audio.xml")));
    world.combat=true;world.mapWidth=2000;world.walkRects={{12,185,1976,1000}};
    Actor sourceActor;sourceActor.id=17;sourceActor.sourceId=56503;
    sourceActor.monsterPath="monster/newmonsters/heaven/jena/jena.mob";
    sourceActor.x=sourceActor.px=640;sourceActor.y=sourceActor.py=344;
    world.initializeMonsterAttributes(sourceActor,1);world.monsters.push_back(std::move(sourceActor));
    world.synchronizeEntityHandles();world.setMapExplorationPolicy(true);
    world.refreshExplorationMonsterEventAiTestPolicy();service.refresh(world,context);
    window.draw(service.snapshot(),230);
    window.handleEvent(debugClick(id,100,635));
    check(world.debugOverrides().monsterAiDifficulty.empty() && world.monsterEventAiState().at("bindings").empty(),
        "The appended source difficulty button queues a command without optimistic selection or registration");
    service.applyAtBoundary(world,context);world.refreshExplorationMonsterEventAiTestPolicy();service.refresh(world,context);
    window.draw(service.snapshot(),240);
    check(world.debugOverrides().monsterAiDifficulty=="easy" && world.monsterEventAiTestPolicy().at("installed")==1,
        "The F9 button selects an actual current MOB difficulty and installs it only at the shared exploration boundary");
    window.handleEvent(debugClick(id,660,635));
    check(world.monsterEventAiState().at("bindings").size()==1,"F9 close-AI also waits for the command boundary");
    service.applyAtBoundary(world,context);world.refreshExplorationMonsterEventAiTestPolicy();service.refresh(world,context);
    check(world.debugOverrides().monsterAiDifficulty.empty() && world.monsterEventAiState().at("bindings").empty(),
        "The independent close-AI control removes only the selected test policy after confirmation");
    SDL_SetWindowSize(native,1000,1125);window.draw(service.snapshot(),250);
    window.handleEvent(debugClick(id,125,793));
    check(world.debugOverrides().monsterAiDifficulty.empty(),"A scaled F9 difficulty click remains a deferred command");
    service.applyAtBoundary(world,context);world.refreshExplorationMonsterEventAiTestPolicy();service.refresh(world,context);
    check(world.debugOverrides().monsterAiDifficulty=="easy", "Resized F9 uses the same800x900 canvas for appended controls and mouse coordinates");
    SDL_SetWindowSize(native,800,900);window.draw(service.snapshot(),251);
    int applicationCalls=0;
    service.setApplicationCommandHandler([&](World &actual,const DebugCommand &command) {
        ++applicationCalls;
        return Json{{"kind",debugCommandName(command.kind)},{"identity",actual.identity().json()}};
    });
    const auto pendingBeforeSelection=service.snapshot().pendingCount;
    window.handleEvent(debugClick(id,100,762));
    check(applicationCalls==0&&service.snapshot().pendingCount==pendingBeforeSelection,
        "The appended job selector changes only its local draft without queueing an identity mutation");
    window.draw(service.snapshot(),252);
    window.handleEvent(debugClick(id,100,834));
    check(applicationCalls==0&&service.snapshot().pendingCount==pendingBeforeSelection,
        "A selected source-only job without an executable controller leaves its apply control disabled");
    window.handleEvent(debugClick(id,590,834));
    check(applicationCalls==0,"The executable-skill button also waits for the shared application boundary");
    service.applyAtBoundary(world,context);
    check(applicationCalls==1&&service.snapshot().recentResults.back().actual.at("application").at("kind")=="unlock_executable_skills",
        "The appended executable-skill UI dispatches exactly once and displays the actual application receipt");
    SDL_Event text{}; text.type = SDL_TEXTINPUT; text.text.windowID = id;
    check(window.handleEvent(text) && !window.handleEvent(debugKey(mainId,SDLK_a)),
        "Test-window text is consumed while main-window combat keys remain available to the application");
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {}
    SDL_Event close{}; close.type = SDL_WINDOWEVENT;
    close.window.windowID = id; close.window.event = SDL_WINDOWEVENT_CLOSE;
    const auto retained = world.debugOverrides();
    check(window.handleEvent(close) && !window.visible() && SDL_GetWindowFromID(id) == native &&
          world.debugOverrides() == retained,
        "Closing tools hides its window, preserves session settings and keeps the window alive");
    bool quit = false;
    while (SDL_PollEvent(&event)) quit |= event.type == SDL_QUIT;
    check(!quit && SDL_GetWindowFromID(mainId) == mainRenderer.window(),
        "Hiding the test window neither emits global quit nor destroys the main window");
    window.show(); window.draw(service.snapshot(),260);
    check(window.handleEvent(debugKey(id,SDLK_ESCAPE)) && !window.visible() && world.debugOverrides() == retained,
        "Escape hides tools without changing actual test settings");
    window.show();
    check(window.handleEvent(debugKey(id,SDLK_F9)) && !window.visible(),
        "F9 in the test window hides that window without becoming a gameplay key");
    window.show(); window.draw(service.snapshot(),300);
    auto next = context; ++next.target.generation;
    window.handleEvent(debugClick(id,100,222));
    service.applyAtBoundary(world,next);
    check(world.debugOverrides() == retained && service.snapshot().recentResults.back().reason == "target_generation_changed",
        "A click on a previously displayed room snapshot cannot affect a newer target generation");
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"video_driver","dummy"},
        {"frontend_started",false},{"scope","SDL dummy event routing, hidden/show lifecycle and independent software renderers; no visual, focus, DPI, audio or feel acceptance"}};
}
} // namespace dnf
