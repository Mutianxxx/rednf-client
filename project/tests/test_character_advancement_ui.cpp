// Harness adapter only; runner owns SDL initialization and teardown.
#include "dnf/character_advancement.hpp"
#include "dnf/region_ui.hpp"
#include <stdexcept>
using namespace dnf;
namespace dnf {
Json runCharacterAdvancementUiTests(Pvf &pvf,Assets &assets,const std::filesystem::path &out) {
    std::filesystem::create_directories(out);
    Json checks=Json::array();const auto check=[&](bool okay,const char *s){if(!okay)throw std::runtime_error(s);checks.push_back(s);};
    try {
        RegionCatalog catalog(pvf,assets);Progression p(catalog);p.initialize(15);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();world.applyEquipment(p);
        world.combat=false;world.releaseInputs();
        const auto initial=world.skillLearning().prepareInitialization(CharacterSkillState(world.identity()),15,SkillInitializationMode::NewCharacter,world.nowMs());
        if(!initial.ok)throw std::runtime_error(initial.quote.json().dump());world.publishSkillLedger(initial.state);
        auto appearance=world.characterAppearance();RegionSession session;RegionUi ui;ui.bindSources(pvf);
        Renderer renderer(assets,RendererOptions{"Hidden GSD input regression",800,600,false,false,false});
        const auto draw=[&](int x=-1,int y=-1,bool click=false,const char *shot=nullptr) {
            renderer.begin();renderer.ui();ui.draw(renderer,world,p,session,appearance,x,y,click);
            if(shot)renderer.screenshot(out/(std::string(shot)+".png"));renderer.present();
        };
        ui.openNpc(world.advancementCatalog().trainerId(),p);draw();
        check(ui.panel==RegionPanel::NpcMenu,"Actual GSD opens existing NPC menu");
        const auto before=p.state,ledger=world.skillState().snapshot(world.nowMs());
        draw(360,320,true);
        check(ui.panel==RegionPanel::Advancement,"Actual new GSD menu button opens source identity page");
        draw(-1,-1,false,"gsd-options");
        check(!ui.advancementRequested&&p.state==before&&world.skillState().snapshot(world.nowMs())==ledger,
            "GSD source page rendering does not mutate normal progression or learned/cost ledger");
        draw(220,206,true);
        check(ui.advancementRequested&&*ui.advancementRequested==CharacterIdentity{0,1,0},
            "At source15 first branch click emits exact same-job target command");
        draw();check(!ui.advancementRequested,"Identity request is cleared on next draw and does not repeat without a click");
        draw(220,240,true);check(!ui.advancementRequested,"Source50 first-awakening button remains disabled at15");
        p.initialize(14);draw(220,206,true);check(!ui.advancementRequested,"Source15 branch button remains disabled at14");
        p.initialize(50);draw(220,240,true);
        check(ui.advancementRequested&&*ui.advancementRequested==CharacterIdentity{0,1,1},"At normal50 first-awakening click emits exact branch/awakening identity");
        auto debug=world.debugOverrides();debug.enabled=true;world.applyDebugOverrides(debug,50);
        draw(220,206,true);check(!ui.advancementRequested,"Active test override cannot emit a normal identity command");
        debug.enabled=false;world.applyDebugOverrides(debug,50);
        draw(610,118,true);check(!ui.open(),"Identity page close event returns control without committing identity");
        ui.openNpc(1,p);draw(360,320,true);check(ui.panel!=RegionPanel::Advancement,"Non-GSD NPC does not expose the identity command");
        check(renderer.errors.empty(),"Hidden GSD source menu/page render without asset errors");
        Json result={{"status","pass"},{"count",checks.size()},{"checks",checks},
            {"classification","hidden SDL software regression; frontend appearance/original parity pending"}};
        writeJson(out/"gsd-ui-tests.json",result);return result;
    }catch(const std::exception &e){writeJson(out/"gsd-ui-tests.json",{{"status","failed"},{"checks",checks},{"error",e.what()}});throw;}
}
} // namespace dnf
