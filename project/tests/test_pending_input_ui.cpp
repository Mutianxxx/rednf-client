#include "dnf/sdl_game_input.hpp"
#include "dnf/sdl_text_input.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/storage.hpp"
#include "dnf/scene.hpp"
#include "dnf/session.hpp"
#include "dnf/reward_recovery.hpp"
#include "dnf/debug_window.hpp"
#include "dnf/renderer.hpp"
#include "dnf/skill_learning_ui.hpp"
#include <array>
#include <stdexcept>
#include <utility>

namespace dnf {
namespace {
namespace fs=std::filesystem;
void push(SDL_Event event) {
    if(SDL_PushEvent(&event)!=1)throw std::runtime_error("Pending input: SDL_PushEvent failed");
}
void key(Uint32 window,Uint32 type,SDL_Keycode symbol,Uint8 repeat=0) {
    SDL_Event event{};event.type=type;event.key.windowID=window;
    event.key.timestamp=SDL_GetTicks();event.key.keysym.sym=symbol;event.key.repeat=repeat;push(event);
}
void windowEvent(Uint32 window,Uint8 kind) {
    SDL_Event event{};event.type=SDL_WINDOWEVENT;event.window.windowID=window;event.window.event=kind;push(event);
}
void click(Uint32 window,int x,int y) {
    SDL_Event event{};event.type=SDL_MOUSEBUTTONDOWN;event.button.windowID=window;
    event.button.button=SDL_BUTTON_LEFT;event.button.x=x;event.button.y=y;push(event);
}
Json sourceCharacter() {
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    root["characters"][0]={{"name","Pending SDL GSD source fixture"},{"class","swordman"},
        {"identity",CharacterIdentity{0,0,0}.json()},{"level",15},{"weapon",0},
        {"skill_initialization","source-v1"},{"future_character",{{"preserved",17}}}};
    return root;
}
Scene sourceTrainer(const World &world) {
    Scene scene;MapNpc npc;npc.id=world.advancementCatalog().trainerId();
    npc.source=world.advancementCatalog().trainerPath();npc.visible=true;
    npc.x=world.player.x;npc.y=world.player.y;scene.npcs.push_back(npc);return scene;
}
Json region(const World &world) { return RegionSession{}.save(world,"town"); }
Json frozenState(const World &world,const Progression &progress) {
    return {{"simulation",world.simulationCheckpoint()},{"identity",world.identity().json()},
        {"skills",world.skillState().snapshot(world.nowMs())},{"progression",progress.state},
        {"normal_config",world.normalSkillConfigurationSnapshot()},
        {"test_config",world.testSkillConfigurationSnapshot()},
        {"manual_config",world.manualSkillPreviewSnapshot()},
        {"preview_enabled",world.experimentalSkillPreviewEnabled()},
        {"debug",world.debugOverrides().json()}};
}
struct UiEvents {
    Renderer &renderer;
    DebugWindow &debugWindow;
    DebugService &debug;
    SdlTextInputBatch batch;
    TextInputModel text;
    int mouseX=-100,mouseY=-100;
    bool focused=true,clicked=false;
    size_t dispatched=0,debugEvents=0,focusEvents=0;
    UiEvents(Renderer &r,DebugWindow &d,DebugService &s):renderer(r),debugWindow(d),debug(s) {}
    // Uses real SDL transport, existing window/debug/text ownership and the
    // production physical dispatcher. This is not a copied full main loop.
    void collect(World &world,SdlGameInputContext context) {
        clicked=false;batch.collect();const auto main=SDL_GetWindowID(renderer.window());
        text.beginEventBatch(batch.hasTextTraffic(main));
        for(const auto &event:batch.events()) {
            if(debugWindow.handleEvent(event)){++debugEvents;continue;}
            const auto owner=sdlInputEventWindow(event);if(owner&&owner!=main)continue;
            if(event.type==SDL_WINDOWEVENT&&event.window.event==SDL_WINDOWEVENT_FOCUS_LOST) {
                focused=false;text.setFocused(false);world.releaseInputs();++focusEvents;
            }
            if(event.type==SDL_WINDOWEVENT&&event.window.event==SDL_WINDOWEVENT_FOCUS_GAINED) {
                focused=true;text.setFocused(true);++focusEvents;
            }
            if(event.type==SDL_KEYUP)text.keyUp(sdlTextInputKey(event.key.keysym.sym));
            if(event.type==SDL_MOUSEBUTTONDOWN&&event.button.button==SDL_BUTTON_LEFT) {
                clicked=true;mouseX=event.button.x;mouseY=event.button.y;
            }
            context.mainWindowId=main;context.wallMs=SDL_GetTicks();
            if(dispatchSdlGameInput(world,event,context))++dispatched;
        }
        text.endEventBatch();
    }
};
}

Json runPendingInputUiTests(Pvf &pvf,Assets &assets,const fs::path &output) {
    const auto directory=fs::absolute(output);
    if(normalize(directory.root_name().u8string())!="d:")
        throw std::runtime_error("Pending input fixtures require an explicit D: output directory");
    fs::create_directories(directory);
    Json checks=Json::array(),samples=Json::array();
    const auto check=[&](bool okay,const std::string &name) {
        if(!okay)throw std::runtime_error("Pending input: "+name);checks.push_back(name);
    };
    Renderer renderer(assets,RendererOptions{"Hidden pending SDL transactions",800,600,false,false,false});
    const auto mainWindow=SDL_GetWindowID(renderer.window());
    RegionCatalog catalog(pvf,assets);
    // Mapping and normal-modal cleanup use the real World queue, including
    // default Z, jump C, held-slot/space mapping. No skill completeness claim.
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService debug;DebugWindow tools(assets,debug);UiEvents events(renderer,tools,debug);
        events.batch.collect();events.batch.clear();
        SdlGameInputContext context{mainWindow,SDL_GetTicks(),true,false,false,false,false,0,16666667};
        const std::array<std::pair<SDL_Keycode,int>,20> mappings={{{SDLK_LEFT,0},{SDLK_RIGHT,1},
            {SDLK_UP,2},{SDLK_DOWN,3},{SDLK_x,4},{SDLK_c,5},{SDLK_z,6},{SDLK_SPACE,7},
            {SDLK_a,20},{SDLK_s,21},{SDLK_d,22},{SDLK_f,23},{SDLK_g,24},{SDLK_h,25},
            {SDLK_q,26},{SDLK_w,27},{SDLK_e,28},{SDLK_r,29},{SDLK_t,30},{SDLK_y,31}}};
        world.bindings[12]=12;
        for(const auto &[physical,logical]:mappings) {
            world.releaseInputs();key(mainWindow,SDL_KEYDOWN,physical);events.collect(world,context);
            auto queue=world.simulationCheckpoint().at("inputs").at("pending");
            check(queue.size()==1&&queue.back().at("payload").at("key")==logical&&
                queue.back().at("payload").at("down")==true,"Physical key maps to original logical input "+std::to_string(logical));
        }
        world.releaseInputs();world.bindings[12]=3;key(mainWindow,SDL_KEYDOWN,SDLK_SPACE);events.collect(world,context);
        check(world.simulationCheckpoint().at("inputs").at("pending").back().at("payload").at("key")==32,
            "Nondefault space binding uses held skill slot32 instead of jump/default code");
        world.releaseInputs();world.mapWidth=1400;world.walkRects={{0,0,1400,700}};
        world.player.x=world.player.px=600;world.player.y=world.player.py=400;
        context.frameNs=0;key(mainWindow,SDL_KEYDOWN,SDLK_LEFT);events.collect(world,context);
        world.advanceSingleTick();const auto heldX=world.player.x;
        check(heldX<600,"Actual accepted direction down is held by World before opening ordinary modal");
        const auto beforeUp=world.simulationCheckpoint().at("inputs").at("sequences");
        context.paused=true;context.modal=true;
        key(mainWindow,SDL_KEYDOWN,SDLK_LEFT);key(mainWindow,SDL_KEYUP,SDLK_LEFT);events.collect(world,context);
        const auto modalQueue=world.simulationCheckpoint().at("inputs");
        check(modalQueue.at("pending").size()==1&&modalQueue.at("pending")[0].at("payload").at("down")==false&&
              modalQueue.at("sequences").at("next").get<uint64_t>()==beforeUp.at("next").get<uint64_t>()+1,
            "Ordinary modal pauses reject down and still enqueue exactly one held-input KEYUP");
        world.advanceSingleTick();const auto releasedX=world.player.x;world.advanceSingleTick();
        check(world.player.x==releasedX,"Actual ordinary modal KEYUP clears held movement when simulation resumes");
        world.releaseInputs();context.paused=false;context.modal=false;context.mapOpen=true;
        key(mainWindow,SDL_KEYDOWN,SDLK_LEFT);key(mainWindow,SDL_KEYDOWN,SDLK_z);events.collect(world,context);
        check(world.simulationCheckpoint().at("inputs").at("pending").size()==1&&
            world.simulationCheckpoint().at("inputs").at("pending")[0].at("payload").at("key")==0,
            "Map view keeps original movement-only physical routing");
        world.releaseInputs();context.mapOpen=false;
        const auto untouched=world.simulationCheckpoint();
        key(mainWindow,SDL_KEYDOWN,SDLK_LEFT,1);key(mainWindow,SDL_KEYUP,SDLK_LEFT,1);
        key(tools.windowId(),SDL_KEYUP,SDLK_z);key(mainWindow+100000,SDL_KEYUP,SDLK_a);
        events.collect(world,context);
        check(world.simulationCheckpoint()==untouched,"Repeat and debug/foreign-window input consume no World sequence");
    }
    const std::array<SaveFailurePoint,4> faults={SaveFailurePoint::BeforeWrite,SaveFailurePoint::AfterWrite,
        SaveFailurePoint::BeforePublish,SaveFailurePoint::AfterPublish};
    for(size_t index=0;index<faults.size();++index) {
        const auto caseDirectory=directory/("fault-"+std::to_string(index));
        CharacterStore store(caseDirectory/"save",pvf.identity());store.data=sourceCharacter();
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        Progression progress(catalog);store.apply(0,world,progress);world.combat=false;world.releaseInputs();
        const SkillLearningRequest purchase{"paid-upper-before-input-fault",{0,46},0,2};
        const auto learned=world.skillLearning().prepare(world.skillState(),15,world.runtimeSkillPolicy(purchase.key),purchase,world.nowMs());
        check(learned.ok,"Actual normal source skill purchase prepared before SDL fault "+std::to_string(index));
        world.publishSkillLedger(learned.state);world.skillState().startCooldown({0,46},world.nowMs(),1700);
        world.randomStreams().stream(RandomDomain::Loot,517).next();world.player.hp-=3;world.player.mp-=2;
        store.capture(0,world,progress);store.save();
        PendingRewardService reward;reward.characterBoundary(world);
        check(reward.acknowledgeCheckpoint(progress,world,store,0),"Real initial writer bound before GSD fault "+std::to_string(index));
        const auto generation=store.generation();const auto frozen=frozenState(world,progress);
        const auto originalSkills=world.skillState().snapshot(world.nowMs());
        auto scene=sourceTrainer(world);const auto uuid=store.data.at("characters")[0].at("uuid").get<std::string>();
        CharacterAdvancementTransaction advancement;
        CharacterAdvancementRequest request{"sdl-gsd-fault-"+std::to_string(index),world.identity(),{0,1,0},generation,world.advancementCatalog().trainerId()};
        store.setFailureInjector([point=faults[index]](SaveFailurePoint at){
            if(at==point)throw std::runtime_error("Injected actual GSD/store SDL fault");});
        const auto failed=advancement.submit(store,0,world,progress,scene,request,region(world));
        check(failed.state==CharacterAdvancementState::Pending&&advancement.pending()&&store.hasPendingCommit()&&
              store.generation()==generation&&frozenState(world,progress)==frozen,
            "GSD fault retains original live World and exact disk candidate "+std::to_string(index));
        const auto pendingRoot=store.data,pendingTransaction=advancement.pendingSnapshot();
        DebugService debug;
        const DebugContext debugContext{{pvf.identity(),uuid,"town",1},15,true};
        debug.refresh(world,debugContext);DebugWindow tools(assets,debug);tools.show();
        tools.draw(debug.snapshot(),SDL_GetTicks64());UiEvents events(renderer,tools,debug);
        events.batch.collect();events.batch.clear();
        const auto savePending=[&]{return advancement.pending()||store.hasPendingCommit();};
        bool quitRequested=false;
        const auto blocked=[&]{return savePending()||reward.blocked(progress)||quitRequested;};
        const auto context=[&]{return SdlGameInputContext{mainWindow,SDL_GetTicks(),true,blocked(),true,true,false,
            world.simulationNanoseconds(),16666667};};
        for(const auto physical:{SDLK_LEFT,SDLK_a,SDLK_z}) {
            key(mainWindow,SDL_KEYDOWN,physical);key(mainWindow,SDL_KEYUP,physical);
        }
        windowEvent(mainWindow,SDL_WINDOWEVENT_FOCUS_LOST);windowEvent(mainWindow,SDL_WINDOWEVENT_FOCUS_GAINED);
        key(tools.windowId(),SDL_KEYUP,SDLK_LEFT);key(mainWindow+100000,SDL_KEYUP,SDLK_a);
        click(tools.windowId(),30,415); // Actual "pause simulation" control; no test-mode enable.
        windowEvent(tools.windowId(),SDL_WINDOWEVENT_CLOSE);
        events.collect(world,context());
        // Application-owned debug boundary follows the production freeze gate.
        // Only physical dispatch and click suppression are shared consumers.
        if(!blocked())debug.applyAtBoundary(world,debugContext);
        debug.refresh(world,debugContext);
        check(events.dispatched==0&&events.focusEvents>=2&&events.debugEvents>=3&&!tools.visible()&&
              debug.snapshot().pendingCount==1&&!debug.pauseRequested(),
            "Real SDL focus/debug-window events retain queued debug command without executing blocked application boundary "+std::to_string(index));
        check(frozenState(world,progress)==frozen&&store.data==pendingRoot&&advancement.pendingSnapshot()==pendingTransaction,
            "Real SDL blocked down/up/focus/debug leaves complete frozen generation unchanged "+std::to_string(index));
        check(world.simulationCheckpoint().at("inputs")==frozen.at("simulation").at("inputs")&&
              world.simulationCheckpoint().at("inputs").at("sequences")==frozen.at("simulation").at("inputs").at("sequences"),
            "Complete inputs pending commands and next sequence are exact during GSD freeze "+std::to_string(index));
        int captureCalls=0,persistCalls=0,publishCalls=0;
        RegionSession session;
        RewardRecoveryFlow recovery(reward,progress,world,catalog);
        const RewardRecoveryHooks townHooks{savePending,[&]{++captureCalls;return reward.observe(progress,world,session,Json::object());},
            [&]{++persistCalls;store.capture(0,world,progress);store.save();return reward.acknowledgeCheckpoint(progress,world,store,0);},
            [&]{++publishCalls;},[](const std::string &){}};
        check(!recovery.pump(townHooks)&&captureCalls==0&&persistCalls==0&&frozenState(world,progress)==frozen,
            "Actual reward Flow stops before capture while real GSD/disk candidate is pending "+std::to_string(index));
        store.setFailureInjector({});quitRequested=true; // Ordinary gate still blocks; retry must survive.
        click(mainWindow,300,325);events.collect(world,context());
        bool ordinaryClick=events.clicked,itemActivate=true;
        const bool retrySaveClick=ordinaryClick&&savePending();
        const bool retryRewardClick=ordinaryClick&&!savePending()&&reward.blocked(progress);
        suppressBlockedGameClicks(blocked(),ordinaryClick,itemActivate);
        suppressBlockedGameClicks(blocked(),ordinaryClick,itemActivate); // post-tick check must not clear retry snapshots.
        check(retrySaveClick&&!retryRewardClick&&!ordinaryClick&&!itemActivate,
            "Shared click suppression retains save retry snapshot while quitRequested blocks ordinary UI "+std::to_string(index));
        renderer.begin();renderer.ui();
        const bool retrySelected=renderer.button("重试当前保存",270,315,250,34,events.mouseX,events.mouseY,retrySaveClick);
        renderer.present();check(retrySelected,"Real hidden Renderer selects retained SDL save-retry click "+std::to_string(index));
        const auto recovered=advancement.retry(store,world);
        check(recovered.ok&&!advancement.pending()&&!store.hasPendingCommit()&&world.identity()==request.target&&
              store.generation()==generation+1,"Actual GSD retry publishes frozen prepared runtime once after SDL events "+std::to_string(index));
        check(reward.acknowledgeCheckpoint(progress,world,store,0),
            "Reward acknowledges actual committed writer only after GSD runtime publication "+std::to_string(index));
        auto updatedSkills=world.skillState().snapshot(world.nowMs());updatedSkills["identity"]=originalSkills.at("identity");
        check(updatedSkills==originalSkills&&world.skillState().learnedLevel({0,46})==2&&
              world.skillState().remainingCooldown({0,46},world.nowMs())==1700&&
              world.testSkillConfigurationSnapshot()==frozen.at("test_config")&&
              world.manualSkillPreviewSnapshot()==frozen.at("manual_config")&&!world.experimentalSkillPreviewEnabled()&&!world.debugOverrides().enabled,
            "GSD prepared publication preserves paid normal level/CD and isolated test/manual fields "+std::to_string(index));
        check(world.simulationCheckpoint()==frozen.at("simulation")&&progress.state==frozen.at("progression"),
            "GSD retry preserves complete input sequence clock RNG and progression "+std::to_string(index));
        auto appearance=world.characterAppearance();SkillLearningUi learning(pvf,assets);
        renderer.begin();renderer.ui();(void)learning.draw(renderer,world,15,false,-1,-1,false);
        learning.reset();renderer.present();
        check(appearance.identity==request.target&&learning.snapshot().at("view").empty(),
            "Actual published appearance matches identity and learning UI can be invalidated after retry "+std::to_string(index));
        check(recovery.pump(townHooks)&&captureCalls==1&&persistCalls==0&&publishCalls==0,
            "Actual reward pump resumes after GSD publication and actual writer acknowledgement "+std::to_string(index));
        const auto committedGeneration=store.generation();const auto duplicate=advancement.submit(store,0,world,progress,scene,request,region(world));
        check(duplicate.state==CharacterAdvancementState::Replayed&&store.generation()==committedGeneration&&
              !advancement.retry(store,world).ok,"Repeated GSD request or retry cannot duplicate identity receipt "+std::to_string(index));
        quitRequested=false;debug.applyAtBoundary(world,debugContext);
        check(debug.pauseRequested()&&debug.snapshot().pendingCount==0&&world.simulationCheckpoint()==frozen.at("simulation"),
            "Queued real debug pause applies only after explicit unblocked boundary without changing simulation "+std::to_string(index));

        // Same source-v1 World now tests actual reward intent/final disk faults.
        // Actors and diagnostic accepted hits follow existing pending-reward
        // fixtures; this does not claim source-map traversal or real combat input.
        check(catalog.prepareDungeon(1).at("status")=="prepared","Reward source Lorien closure prepared "+std::to_string(index));
        session.begin(catalog,1,9801+index);session.run.current=session.run.boss;
        world.combat=true;world.freezeAi=true;world.mapWidth=1400;world.walkRects={{0,0,1400,700}};
        world.monsters.clear();const auto &spawns=catalog.maps.at(session.run.room().mapId).monsters;
        check(spawns.size()>=2,"Reward source boss has actual multiple actors "+std::to_string(index));
        for(size_t i=0;i<spawns.size();++i) {
            Actor actor;actor.id=int(i+1);actor.sourceId=spawns[i].id;actor.monsterPath=catalog.monsterPath(spawns[i].id);
            actor.x=actor.px=spawns[i].x;actor.y=actor.py=spawns[i].y+80;actor.z=actor.pz=spawns[i].z;
            actor.hp=actor.maxHp=1;actor.boss=spawns[i].type=="[boss]";world.monsters.push_back(std::move(actor));
        }
        world.synchronizeEntityHandles();
        world.setObjectTick([&](World &simulation){
            if(simulation.tick==2)simulation.diagnosticHit(1,1,0,0,1,{});
            if(simulation.tick==4)for(size_t i=1;i<simulation.monsters.size();++i)simulation.diagnosticHit(int(i+1),1,0,0,1,{});
        });
        world.advance(1000000000,8);world.setObjectTick({});session.remember(world);
        check(session.run.complete(),"Diagnostic accepted hits leave actual nonempty boss clear for reward service "+std::to_string(index));
        const bool finalFault=index%2!=0;bool armFinal=finalFault;
        int rewardCaptures=0,rewardPersists=0,rewardPublications=0;
        const auto inject=[](SaveFailurePoint at){if(at==SaveFailurePoint::AfterWrite)throw std::runtime_error("Injected reward SDL checkpoint fault");};
        if(!finalFault)store.setFailureInjector(inject);
        const RewardRecoveryHooks rewardHooks{savePending,[&]{++rewardCaptures;session.remember(world);
                return reward.observe(progress,world,session,session.save(world,"dungeon"));},
            [&]{++rewardPersists;try{store.capture(0,world,progress);store.data["characters"][0]["region_session"]=session.save(world,"dungeon");
                    store.save();return reward.acknowledgeCheckpoint(progress,world,store,0);}catch(const std::exception &){return false;}},
            [&]{++rewardPublications;if(armFinal)store.setFailureInjector(inject);},[](const std::string &){}};
        // A real SDL ordinary click was accepted before ticks/pump. The actual
        // pump now creates a pending intent/final checkpoint in this frame.
        click(mainWindow,300,325);events.collect(world,context());ordinaryClick=events.clicked;itemActivate=true;
        const bool oldRetrySave=ordinaryClick&&savePending();
        const bool oldRetryReward=ordinaryClick&&!savePending()&&reward.blocked(progress);
        suppressBlockedGameClicks(blocked(),ordinaryClick,itemActivate);
        check(ordinaryClick&&!oldRetrySave&&!oldRetryReward,"No pending save consumes pre-pump SDL ordinary click "+std::to_string(index));
        check(!recovery.pump(rewardHooks)&&store.hasPendingCommit()&&reward.needsCheckpoint(),
            "Actual reward pump opens "+std::string(finalFault?"final":"intent")+" pending checkpoint after event-phase click "+std::to_string(index));
        suppressBlockedGameClicks(blocked(),ordinaryClick,itemActivate);
        check(!ordinaryClick&&!itemActivate&&!oldRetrySave&&!oldRetryReward,
            "M22 shared post-tick gate removes stale ordinary SDL click without inventing retry flags "+std::to_string(index));
        const auto rewardFrozen=frozenState(world,progress),rewardPendingRoot=store.data;
        key(mainWindow,SDL_KEYUP,SDLK_LEFT);key(mainWindow,SDL_KEYDOWN,SDLK_a);
        key(mainWindow,SDL_KEYUP,SDLK_z);windowEvent(mainWindow,SDL_WINDOWEVENT_FOCUS_LOST);windowEvent(mainWindow,SDL_WINDOWEVENT_FOCUS_GAINED);
        events.collect(world,context());
        check(frozenState(world,progress)==rewardFrozen&&store.data==rewardPendingRoot,
            "Reward pending disk candidate also freezes actual SDL input queue sequence clock RNG and ledger "+std::to_string(index));
        const auto capturesBeforeRetry=rewardCaptures;
        check(!recovery.pump(rewardHooks)&&rewardCaptures==capturesBeforeRetry,
            "Reward Flow does not replace exact pending disk root during repeated pump "+std::to_string(index));
        store.setFailureInjector({});armFinal=false;click(mainWindow,300,325);events.collect(world,context());
        const bool rewardSaveClick=events.clicked&&savePending();
        ordinaryClick=events.clicked;itemActivate=true;suppressBlockedGameClicks(blocked(),ordinaryClick,itemActivate);
        renderer.begin();renderer.ui();const bool rewardRetrySelected=renderer.button("重试当前保存",270,315,250,34,
            events.mouseX,events.mouseY,rewardSaveClick);renderer.present();
        check(rewardRetrySelected&&!ordinaryClick&&!itemActivate,"Hidden Renderer preserves reward disk retry button through shared click gate "+std::to_string(index));
        store.retryPending();check(reward.acknowledgeCheckpoint(progress,world,store,0),"Actual reward disk retry acknowledged without replacing original candidate "+std::to_string(index));
        check(recovery.pump(rewardHooks)&&rewardPublications==1&&!reward.blocked(progress)&&
              recovery.resultsReady(true,false,session),"Actual reward recovery completes once and unlocks durable Results "+std::to_string(index));
        if(finalFault)check(progress.state==rewardFrozen.at("progression")&&world.randomStreams().snapshot()==rewardFrozen.at("simulation").at("random"),
            "Final-checkpoint retry never rerolls already prepared reward output "+std::to_string(index));
        const auto finalState=progress.state,finalRng=world.randomStreams().snapshot();const auto finalGeneration=store.generation();
        check(recovery.pump(rewardHooks)&&progress.state==finalState&&world.randomStreams().snapshot()==finalRng&&
              store.generation()==finalGeneration&&rewardPublications==1,"Further actual recovery pump is idempotent "+std::to_string(index));
        samples.push_back({{"case",index},{"final_reward_fault",finalFault},{"gsd_receipt",store.receipt(request.requestId)},
            {"frozen_before_gsd",frozen},{"reward_frozen",rewardFrozen},{"final_generation",store.generation()},
            {"debug",debug.snapshot().json()},{"scope","SDL batch/shared dispatcher/real services; application harness hooks are not full main lambdas"}});
        store.close();
    }
    const Json report={{"status","passed"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","Actual SDL_PushEvent/SdlTextInputBatch/shared production physical and click gates, real GSD/store/reward services and hidden Renderer; source trainer/diagnostic-hit fixtures, not full main while-loop or source-map traversal"}};
    writeJson(directory/"pending-input-ui-tests.json",report);return report;
}
} // namespace dnf
