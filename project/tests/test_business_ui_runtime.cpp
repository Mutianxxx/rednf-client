#include "dnf/entry.hpp"
#include "dnf/content_profile.hpp"
#include "dnf/region_ui.hpp"
#include "dnf/skill_learning_ui.hpp"
#include "dnf/skill_configuration_ui.hpp"
#include "dnf/selection_ui.hpp"
#include <iostream>
#include <stdexcept>

using namespace dnf;
namespace dnf { Json runSdlTextInputTests(Pvf &,Assets &,const std::filesystem::path &);
Json runPortalRendererTests(Pvf &,Assets &);
Json runSelectionFeedbackRuntimeTests(Pvf &,Assets &,const std::filesystem::path &);
Json runLongUiTextTests(Renderer &,const std::filesystem::path &);
Json runScenePresentationUiTests(Pvf &,Assets &,const std::filesystem::path &);
Json runWorldPresentationRuntimeTests(Pvf &,Assets &,const std::filesystem::path &);
Json runCharacterAdvancementUiTests(Pvf &,Assets &,const std::filesystem::path &);
Json runNormalLearningUiBridgeTests(Pvf &,Assets &,const std::filesystem::path &);
Json runPendingInputUiTests(Pvf &,Assets &,const std::filesystem::path &);
Json runSceneTileHiddenTests(Pvf &,Assets &,Renderer &,const std::filesystem::path &); }
namespace {
Json exercise(Pvf &pvf,Assets &assets,const std::filesystem::path &output) {
    Json checks=Json::array();auto check=[&](bool okay,const std::string &name){if(!okay)throw std::runtime_error(name);checks.push_back(name);};
    RegionCatalog catalog(pvf,assets);Progression progress(catalog);progress.initialize(4);
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progress);
    auto initialized=world.skillLearning().prepareInitialization(CharacterSkillState(world.identity()),4,SkillInitializationMode::NewCharacter,world.nowMs());
    check(initialized.ok,"normal learning fixture initialized");world.publishSkillLedger(initialized.state);
    auto appearance=progress.appearance(pvf,world.characterCatalog(),world.identity());
    Renderer renderer(assets,RendererOptions{"Hidden requested UI regression",800,600,false,false,false});
    { Renderer mapRenderer(assets,RendererOptions{"Hidden source tiles",800,600,false,false,false});
      writeJson(output/"scene-tiles-hidden-tests.json",runSceneTileHiddenTests(pvf,assets,mapRenderer,output/"scene-tiles")); }
    RegionUi ui;ui.bindSources(pvf);RegionSession session;SkillLearningUi learning(pvf,assets);
    auto draw=[&](int x=-1,int y=-1,bool click=false,bool activate=false,const std::string &shot=""){
        renderer.begin();renderer.ui();ui.draw(renderer,world,progress,session,appearance,x,y,click,activate);
        if(!shot.empty())renderer.screenshot(output/(shot+".png"));renderer.present();
    };
    auto skill=[&](int x=-1,int y=-1,bool click=false,bool test=false,const std::string &shot=""){
        renderer.begin();renderer.ui();auto result=learning.draw(renderer,world,4,test,x,y,click);
        if(!shot.empty())renderer.screenshot(output/(shot+".png"));renderer.present();return result;
    };
    // Town minimap: the panel crops the source parchment IMG around the active
    // TWN area rect, and its on-panel control collapses/restores the map.
    {
        std::vector<TownArea> areas(2);
        areas[0].id=0;areas[0].raw=Json::array({0,"a.map","[minimap rect]",372,242,438,268,"[/minimap rect]"});
        areas[1].id=1;areas[1].raw=Json::array({1,"b.map","[minimap rect]",399,230,412,239,"[/minimap rect]"});
        std::vector<MapNpc> npcs;
        renderer.begin();renderer.ui();
        check(ui.townMinimap(renderer,areas,1,100,100,896,600,"赛利亚房间",npcs,-1,-1,false),
              "town minimap draws the source map panel");
        renderer.screenshot(output/"town-minimap.png");renderer.present();
        const int toggleX=800-128-12+128-15+6,toggleY=32+7;
        renderer.begin();renderer.ui();
        check(!ui.townMinimap(renderer,areas,1,100,100,896,600,"赛利亚房间",npcs,toggleX,toggleY,true),
              "town minimap toggle collapses the panel");
        check(!ui.townMinimapVisible(),"town minimap toggle state is retained between frames");
        renderer.begin();renderer.ui();
        check(ui.townMinimap(renderer,areas,1,100,100,896,600,"赛利亚房间",npcs,toggleX,toggleY,true),
              "town minimap toggle restores the panel");
    }
    const auto progressionBefore=progress.state;const auto normalBefore=world.skillState().snapshot(world.nowMs());
    ui.openInventory();draw(-1,-1,false,false,"inventory");
    check(progress.state==progressionBefore,"inventory opening and drawing preserve inventory/equipment ledger");
    draw(550,125,true);check(ui.snapshot().at("inventory_tab")==1,"source avatar tab hit test");draw(-1,-1,false,false,"avatar");
    draw(480,125,true);check(ui.snapshot().at("inventory_tab")==0,"source item tab hit test");
    draw(705,95,true);check(!ui.open(),"inventory close hit extent");
    ui.openNpc(1,progress);draw(-1,-1,false,false,"npc-menu");
    check(ui.panel==RegionPanel::NpcMenu,"clicking NPC opens independent source menu");
    auto afterTalk=progress.state;draw(360,211,true);check(ui.panel==RegionPanel::Npc,"source talk menu event");
    draw(-1,-1,false,false,"npc-dialogue");draw(450,555,true);
    check(progress.state==afterTalk,"dialogue navigation does not alter business ledger");
    draw(70,557,true);check(ui.panel==RegionPanel::NpcMenu,"dialogue returns to NPC menu");
    draw(360,263,true);check(ui.panel==RegionPanel::Shop,"source shop menu event");
    draw(-1,-1,false,false,"shop");const auto beforeRejectedBuy=progress.state;draw(330,194,true);
    check(progress.state==beforeRejectedBuy,"purchase without gold cannot mutate inventory or currency");
    ui.openNpc(2,progress);draw(360,237,true);check(ui.panel==RegionPanel::Npc,"source task menu event");draw(-1,-1,false,false,"npc-quest");
    const auto available=progress.availableQuests(2);
    if(!available.empty()) {
        const auto &q=available.front();int id=q.at("id");const bool canAccept=q.value("available",false)&&!q.value("active",false);
        draw(510,559,true);if(canAccept)check(progress.questActive(id),"task accept uses actual Progression transaction");
    }
    ui.panel=RegionPanel::Quests;draw(-1,-1,false,false,"quests");
    draw(510,99,true);check(ui.snapshot().at("completed_quests")==true,"quest active/completed filter is operable");
    ui.close();
    const auto actualBeforeLearning=world.skillState().snapshot(world.nowMs());
    skill(-1,-1,false,false,"skill-learning");
    check(world.skillState().snapshot(world.nowMs())==actualBeforeLearning,"learning rendering cannot mutate normal SP/TP ledger");
    int eligible=-1;const auto learningView=learning.snapshot().at("view");
    const auto &learningRows=learningView.at("rows");
    for(size_t row=0;row<learningRows.size();++row){const auto key=SkillKey::fromJson(learningRows[row].at("key"));if(world.quoteSkillLearning(key,4).accepted()){eligible=int(row);break;}}
    const auto grid=learningView.at("grid");const int pageSize=grid.at("page_size").get<int>();
    check(eligible>=0,"normal learning has an eligible source-key fixture");
    for(int page=0;page<eligible/pageSize;++page)skill(grid.at("left").get<int>()+grid.at("width").get<int>()-80,grid.at("navigation_y").get<int>()+5,true);
    skill(grid.at("left").get<int>()+(eligible%pageSize%3)*grid.at("cell_width").get<int>()+5,
        grid.at("top").get<int>()+(eligible%pageSize/3)*grid.at("row_height").get<int>()+5,true);
    auto requested=skill(240,552,true);check(bool(requested.purchase)&&requested.quote.accepted(),"learning click returns an authorized purchase request");
    check(world.skillState().snapshot(world.nowMs())==actualBeforeLearning,"UI request does not bypass durable normal learning transaction");
    auto prepared=world.skillLearning().prepare(world.skillState(),4,world.runtimeSkillPolicy(*requested.purchase),
        {"ui-regression-learning",*requested.purchase,requested.quote.revision,requested.quote.targetLevel},world.nowMs());
    check(prepared.ok,"returned quote passes the actual normal learning service");
    world.combat=true;check(!skill(240,552,true).purchase,"learning purchase blocked during combat");world.combat=false;
    check(!skill(240,552,true,true).purchase,"test branch without enabled overlay cannot spend normal points");
    skill(320,552,true);check(!learning.snapshot().at("selected").is_object(),"cancel clears selection for current frame");
    auto savedSkills=world.skills,savedPassives=world.passives;world.skills.clear();world.passives.clear();
    learning.reset();check(!skill().purchase,"empty active/passive sets render safely");world.skills=std::move(savedSkills);world.passives=std::move(savedPassives);
    check(world.skillState().snapshot(world.nowMs())==actualBeforeLearning,"all normal learning UI checks preserve source ledger");
    // Source records and all pages remain reachable for the experimental job.
    world.enableExperimentalCharacters();world.selectCharacter({5,0,0});auto *runtime=world.experimentalRuntime();
    check(runtime!=nullptr,"female gunner experimental UI fixture available");SkillConfigurationUi configuration;
    DebugOverrides previewDebug;previewDebug.enabled=true;world.applyDebugOverrides(previewDebug,world.normalCharacterLevel());
    const auto explicitPreview=world.setExperimentalSkillPreviewEnabled(true);
    check(explicitPreview.ok&&world.experimentalSkillPreviewEnabled(),"source configuration fixture explicitly selects isolated manual preview mode");
    const auto normalFemale=world.skillState().snapshot(world.nowMs());
    auto config=[&](int x=-1,int y=-1,bool click=false,const std::string &shot=""){
        renderer.begin();renderer.ui();auto changed=configuration.draw(renderer,world,x,y,click,true);
        if(!shot.empty())renderer.screenshot(output/(shot+".png"));renderer.present();return changed;
    };
    config();config(555,90,true);config(-1,-1,false,"female-gunner-all-source");
    check(configuration.snapshot().at("visible_count")==runtime->plan().skills.size(),"all registered female gunner source skills visible across pages");
    check(runtime->plan().skills.size()==167,"fixed 1031 female gunner registry contains 167 preserved source records");
    std::vector<SkillKey> keys;int passiveIndex=-1;for(const auto &[key,row]:runtime->plan().skills){if(passiveIndex<0&&row.kind==SkillSourceKind::Passive)passiveIndex=int(keys.size());keys.push_back(key);}
    check(passiveIndex>=0,"female passive source fixture exists");
    for(int page=0;page<passiveIndex/8;++page)config(320,460,true);
    config(140,212+(passiveIndex%8)*30,true);config();
    const auto slotsBefore=runtime->configuration().slots();const auto key=keys[passiveIndex];
    check(config(420,410,true),"female source passive level can be explicitly configured");
    check(runtime->configuration().femaleGunnerPassiveLevel(key)==1,"female passive overlay receives requested source level");
    check(runtime->configuration().slots()==slotsBefore,"passive configuration does not occupy an active hotkey");
    check(world.skillState().snapshot(world.nowMs())==normalFemale,"experimental passive UI leaves normal skill ledger intact");
    config(-1,-1,false,"female-gunner-passive");
    check(config(430,445,true)&&runtime->configuration().femaleGunnerPassiveLevel(key)==0,"removing passive coverage clears only selected overlay");
    for(const auto &[width,height]:std::vector<std::array<int,2>>{{640,480},{1000,750},{1280,720}}){
        renderer.resize(width,height);renderer.ui();ui.openInventory();draw();check(renderer.errors.empty(),"source UI assets render after resize "+std::to_string(width)+"x"+std::to_string(height));
    }
    const auto longText=runLongUiTextTests(renderer,output);
    writeJson(output/"long-ui-text-tests.json",longText);
    check(longText.at("status")=="passed","oversized source diagnostic safely renders through actual Renderer");
    check(renderer.errors.empty(),"all requested interface assets load without renderer errors");
    return {{"status","passed"},{"checks",checks},{"count",checks.size()},{"renderer_errors",renderer.errors},{"renderer_unsupported",renderer.unsupported},
        {"skill_learning_view",learning.snapshot()},{"configuration_view",configuration.snapshot()},
        {"scope","hidden SDL dummy source rendering and UI event/transaction checks; frontend look, audio and feel require user verification"}};
}
}
int run(int argc,char **argv) {
    if(argc!=3){std::cerr<<"dnf_ui_tests CLIENT OUTPUT_DIRECTORY\n";return 2;}
    const auto output=std::filesystem::u8path(argv[2]);
    try {
        SDL_SetMainReady();SDL_setenv("SDL_VIDEODRIVER","dummy",1);SDL_setenv("SDL_AUDIODRIVER","dummy",1);
        if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS)!=0)throw std::runtime_error(SDL_GetError());
        const auto root=std::filesystem::u8path(argv[1]);
        ContentProfile profile;profile.pvfPath=root/"Script.pvf";profile.resourceRoots={root};
        const auto identity=profile.fingerprint();Pvf pvf(root/"Script.pvf",identity.pvfSha256);
        Assets assets(std::vector<std::filesystem::path>{root},pvf,identity.manifest);
        const auto portal=dnf::runPortalRendererTests(pvf,assets);
        writeJson(output/"scene-presentation-ui-tests.json",dnf::runScenePresentationUiTests(pvf,assets,output/"scene-presentation"));
        writeJson(output/"world-presentation-runtime-tests.json",dnf::runWorldPresentationRuntimeTests(pvf,assets,output/"world-presentation"));
        writeJson(output/"character-advancement-ui-tests.json",dnf::runCharacterAdvancementUiTests(pvf,assets,output/"gsd-advancement"));
        writeJson(output/"portal-renderer-tests.json",portal);
        writeJson(output/"normal-learning-ui-bridge-tests.json",
            dnf::runNormalLearningUiBridgeTests(pvf,assets,output/"normal-learning-ui"));
        writeJson(output/"pending-input-ui-tests.json",
            dnf::runPendingInputUiTests(pvf,assets,output/"pending-input"));
        auto report=exercise(pvf,assets,output);report["content_identity"]=identity.json();
        report["portal_renderer"]=portal;
        const auto selection=dnf::runSelectionUiRuntimeTests(pvf,assets,output/"selection");
        writeJson(output/"selection-runtime-tests.json",selection);
        if(selection.at("status")!="passed")throw std::runtime_error("Selection runtime checks failed");
        report["selection_runtime"]=selection;
        const auto selectionFeedback=dnf::runSelectionFeedbackRuntimeTests(pvf,assets,output/"selection-feedback");
        writeJson(output/"selection-feedback-runtime-tests.json",selectionFeedback);
        if(selectionFeedback.at("status")!="passed")throw std::runtime_error("Selection feedback runtime checks failed");
        report["selection_feedback"]=selectionFeedback;
        const auto textInput=dnf::runSdlTextInputTests(pvf,assets,output/"text-input");
        if(textInput.at("status")!="passed")throw std::runtime_error("SDL text input routing checks failed");
        report["sdl_text_input"]=textInput;
        writeJson(output/"ui-runtime-tests.json",report);SDL_Quit();
        std::cout<<report.at("count")<<" hidden UI checks passed\n";return 0;
    }catch(const std::exception &e){writeJson(output/"ui-runtime-failure.json",{{"status","failed"},{"error",e.what()}});SDL_Quit();std::cerr<<e.what()<<"\n";return 1;}
}
DNF_ENTRY(run)
