#include "dnf/skill_learning_ui.hpp"
#include "dnf/skill_configuration_ui.hpp"
#include "dnf/skill_learning_transaction.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/scene.hpp"
#include "dnf/session.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
namespace {
Json normalUiRoot(int job,int branch,int level) {
    const std::array<std::string,9> classes={"swordman","fighter","gunner","mage","priest","atgunner","thief","atfighter","atmage"};
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    root["characters"][0]={{"name","Normal UI fixture"},{"class",classes.at(job)},{"identity",CharacterIdentity{job,branch,0}.json()},
        {"level",level},{"weapon",0},{"skill_initialization","source-v1"},{"future_ui_fixture","retain"}};return root;
}
Json normalUiRegion(const World &world) {
    return {{"schema",3},{"location","town"},{"player",saveActor(world.player,world.nowMs())},
        {"reward_ledger",{{"ui-fixture-existing","retained"}}}};
}
}
Json runNormalLearningUiBridgeTests(Pvf &pvf,Assets &assets,const std::filesystem::path &output) {
    Json checks=Json::array(),cases=Json::array();
    const auto check=[&](bool okay,const std::string &name){if(!okay)throw std::runtime_error("Normal learning UI: "+name);checks.push_back(name);};
    std::filesystem::create_directories(output);
    const auto temporary=std::filesystem::absolute(std::filesystem::path("cache/tests/normal-learning-ui")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(temporary);
    try {
        RegionCatalog regions(pvf,assets);
        Renderer renderer(assets,RendererOptions{"Hidden normal learning bridge",800,600,false,false,false});
        BusinessUiSources sources;sources.bind(pvf);
        const auto &shop=sources.layout("ui/skill/skillshopwindow.ui");const auto buy=shop.position("1001");
        const auto choose=[&](SkillLearningUi &ui,World &world,int level,SkillKey key,bool testBranch=false) {
            ui.reset();
            const auto draw=[&](int x=-1,int y=-1,bool click=false){renderer.begin();renderer.ui();auto result=ui.draw(renderer,world,level,testBranch,x,y,click);renderer.present();return result;};
            draw();auto initial=ui.snapshot();
            check(initial.at("view").at("work").at("quote_batch_requests_this_draw")==1,
                "First real UI draw requests one shared-budget quote batch");
            draw();const auto warm=ui.snapshot().at("view").at("work");
            check(warm.at("quote_batch_requests_this_draw")==0&&warm.at("metadata_reads_this_draw")==0&&warm.at("detail_reads_this_draw")==0&&
                warm.at("quote_builds")==initial.at("view").at("work").at("quote_builds"),
                "Unchanged actual UI draw reuses source metadata, row quotes and selected source details");
            const auto &definition=world.characterCatalog().skillDefinition(key);const auto radio=shop.position("1");
            if(!definition.fieldsInScope("[special purchase cost]","common").empty())draw(radio[0]+135,radio[1]+5,true);
            if(definition.kind==SkillSourceKind::Passive)draw(radio[0]+275,radio[1]+5,true);
            initial=ui.snapshot();const auto &rows=initial.at("view").at("rows");
            size_t index=0;for(;index<rows.size();++index)if(rows[index].at("key")==key.json())break;
            check(index<rows.size(),"Actual key "+key.json().dump()+" is available in source-backed learning rows");
            const auto grid=initial.at("view").at("grid");const int size=grid.at("page_size").get<int>();
            for(size_t page=0;page<index/size;++page)draw(grid.at("left").get<int>()+grid.at("width").get<int>()-80,grid.at("navigation_y").get<int>()+5,true);
            const int visible=int(index%size);
            draw(grid.at("left").get<int>()+(visible%3)*grid.at("cell_width").get<int>()+5,
                grid.at("top").get<int>()+(visible/3)*grid.at("row_height").get<int>()+5,true);
            check(ui.snapshot().at("selected")==key.json(),"Real source tile click selects exact job+skill key");
            return draw(buy[0]+5,buy[1]+5,true);
        };
        struct Case{int job,branch,skill,level;};
        for(const auto spec:{Case{1,0,6,5},Case{3,0,4,5},Case{4,0,1,4},Case{4,4,116,30},Case{8,0,1,4},Case{8,0,26,3}}) {
            const SkillKey key{spec.job,spec.skill};
            CharacterStore store(temporary/("job"+std::to_string(spec.job)+"-skill"+std::to_string(spec.skill)),"normal-ui-bridge-fixture");store.data=normalUiRoot(spec.job,0,spec.level);
            World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progression(regions);
            store.apply(0,world,progression);world.combat=false;world.releaseInputs();store.capture(0,world,progression);store.checkpoint();
            if(spec.branch!=0) {
                Scene scene;MapNpc trainer;trainer.id=world.advancementCatalog().trainerId();
                trainer.source=world.advancementCatalog().trainerPath();trainer.visible=true;
                trainer.x=world.player.x;trainer.y=world.player.y;scene.npcs.push_back(trainer);
                CharacterAdvancementTransaction advancement;
                check(advancement.submit(store,0,world,progression,scene,
                    {"ui-gsd-"+std::to_string(spec.job),world.identity(),{spec.job,spec.branch,0},store.generation(),trainer.id},
                    normalUiRegion(world)).ok,"Branched UI fixture enters through actual GSD advancement after valid source creation");
            }
            check(world.isExperimentalCharacter()&&world.skills.empty()&&world.passives.empty(),"Fixture exercises actual non-Swordman runtime without compatibility Skill arrays");
            check(world.runtimeSkillPolicy(key).implemented,"Key has a reviewed actual normal consumer before learning UI");
            const auto ledger=world.skillState().snapshot(world.nowMs()),configuration=world.experimentalRuntime()->configuration().snapshot();
            const auto diskGeneration=store.generation();
            SkillLearningUi learning(pvf,assets);const auto request=choose(learning,world,spec.level,key);
            check(request.purchase&&*request.purchase==key&&request.quote.accepted(),"Actual source tile and learn button return an authorized non-Swordman SkillKey purchase");
            check(world.skillState().snapshot(world.nowMs())==ledger&&store.generation()==diskGeneration&&
                world.experimentalRuntime()->configuration().snapshot()==configuration,"Rendering and purchase request do not spend points, alter bindings or write a save");
            check(learning.snapshot().at("view").at("budget")==world.skillLearning().budget(world.skillState(),spec.level,world.nowMs()).json(),
                "Displayed normal SP/TP comes directly from service independently of empty Skill arrays");
            const auto beforeLevel=world.skillState().learnedLevel(key);
            SkillLearningTransaction transaction;
            const SkillLearningRequest buyRequest{"ui-key-purchase-"+std::to_string(spec.job),key,request.quote.revision,request.quote.targetLevel};
            const auto result=transaction.submit(store,0,world,progression,buyRequest,normalUiRegion(world));
            check(result.ok&&!transaction.pending()&&world.skillState().learnedLevel(key)==beforeLevel+1,
                "UI SkillKey passes actual durable normal learning transaction and publishes one learned level");
            renderer.begin();renderer.ui();learning.draw(renderer,world,spec.level,false,-1,-1,false);renderer.present();
            check(learning.snapshot().at("view").at("work").at("quote_batch_requests_this_draw")==1&&
                learning.snapshot().at("view").at("budget")==world.skillLearning().budget(world.skillState(),spec.level,world.nowMs()).json(),
                "Real committed learning invalidates cached quotes and updates displayed service budget on next draw");
            const auto exactLearning=world.skillState().snapshot(world.nowMs());const auto projectionRevision=world.skillRuntimeProjectionRevision();
            auto importedLearning=exactLearning;importedLearning["ui_same_revision_import"]=true;
            world.skillState().restore(importedLearning,world.nowMs());
            renderer.begin();renderer.ui();learning.draw(renderer,world,spec.level,false,-1,-1,false);renderer.present();
            check(world.skillRuntimeProjectionRevision()==projectionRevision&&
                learning.snapshot().at("view").at("work").at("quote_batch_requests_this_draw")==1,
                "Raw fixture/import content replaced at the same revision still invalidates exact ledger quote context");
            world.skillState().restore(exactLearning,world.nowMs());
            renderer.begin();renderer.ui();learning.draw(renderer,world,spec.level,false,-1,-1,false);renderer.present();
            world.skillState().startCooldown(key,world.nowMs(),1234);
            renderer.begin();renderer.ui();learning.draw(renderer,world,spec.level,false,-1,-1,false);renderer.present();
            check(learning.snapshot().at("view").at("work").at("quote_batch_requests_this_draw")==0,
                "Cooldown-only changes do not rebuild unchanged learning quotes");
            world.skillState().restore(exactLearning,world.nowMs());
            const auto saved=store.generation();const auto replay=transaction.submit(store,0,world,progression,buyRequest,normalUiRegion(world));
            check(replay.state==SkillLearningTransactionState::Replayed&&store.generation()==saved,"Exact UI request replay cannot spend or commit twice");
            const auto ledgerAfter=world.skillState().snapshot(world.nowMs());
            SkillConfigurationUi configurationUi;
            const auto configure=[&](int x=-1,int y=-1,bool click=false,bool allow=false){renderer.begin();renderer.ui();const auto changed=configurationUi.draw(renderer,world,x,y,click,allow);renderer.present();return changed;};
            configure();const auto rows=configurationUi.snapshot().at("view").at("rows");
            size_t index=0;for(;index<rows.size();++index)if(rows[index].at("key")==key.json())break;
            check(index<rows.size(),"Reviewed active consumer is present in learned shortcut page");
            for(size_t page=0;page<index/8;++page)configure(320,460,true);
            configure(140,212+int(index%8)*30,true);
            check(configure(410,365,true)&&world.experimentalRuntime()->configuration().slots()[0]&&
                *world.experimentalRuntime()->configuration().slots()[0]==key,"Normal shortcut button binds actual learned key without choosing ANI/ATK or manual level");
            check(world.skillState().snapshot(world.nowMs())==ledgerAfter,"Normal slot assignment preserves learned levels and paid SP/TP history");
            check(!configure(410,420,true)&&!world.experimentalSkillPreviewEnabled(),"Manual preview button cannot activate from an ordinary branch");
            store.capture(0,world,progression);store.checkpoint();
            World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression restoredProgression(regions);store.apply(0,restored,restoredProgression);
            check(restored.skillState().learnedLevel(key)==world.skillState().learnedLevel(key)&&
                !restored.experimentalSkillPreviewEnabled()&&restored.experimentalRuntime()->configuration().slots()[0]&&
                *restored.experimentalRuntime()->configuration().slots()[0]==key,"Real CharacterStore restores normal learned level and key slot without entering manual preview");
            const auto generation=store.generation();world.combat=true;const auto combatRequest=choose(learning,world,spec.level,key);world.combat=false;
            check(!combatRequest.purchase&&store.generation()==generation,"Learning UI cannot purchase during combat");
            cases.push_back({{"key",key.json()},{"level_before",beforeLevel},{"level_after",world.skillState().learnedLevel(key)},
                {"normal_budget",learning.snapshot().at("view").at("budget")},{"transaction",result.json()}});
            if(spec.job==1) {
                DebugOverrides debug;debug.enabled=true;debug.level=15;world.applyDebugOverrides(debug,spec.level);
                const auto normalBefore=world.skillState().snapshot(world.nowMs());
                renderer.begin();renderer.ui();learning.draw(renderer,world,spec.level,true,-1,-1,false);renderer.present();
                check(learning.snapshot().at("view").at("test_learning")==true&&
                    learning.snapshot().at("view").at("work").at("quote_batch_requests_this_draw")==1,
                    "Actual test-mode and effective-level transition invalidates the existing normal quote cache");
                const auto testRequest=choose(learning,world,spec.level,key,true);
                check(testRequest.purchase&&testRequest.quote.accepted()&&learning.snapshot().at("view").at("test_learning")==true,
                    "Explicit test branch obtains independent test-effective learning quote");
                const auto testResult=world.learnTestSkill({"ui-test-key",key,testRequest.quote.revision,testRequest.quote.targetLevel});
                check(testResult.ok&&world.skillState().snapshot(world.nowMs())==normalBefore,
                    "Actual test-learning UI key changes overlay without charging normal SP or learned level");
                renderer.begin();renderer.ui();learning.draw(renderer,world,spec.level,true,-1,-1,false);renderer.present();
                check(learning.snapshot().at("view").at("work").at("quote_batch_requests_this_draw")==1&&
                    learning.snapshot().at("view").at("budget")==world.skillLearningBudget(true,spec.level).json(),
                    "Actual test purchase invalidates quotes and displays the independent test-effective budget");
                check(configure(410,420,true,true)&&world.experimentalSkillPreviewEnabled(),"Isolated debug branch can explicitly enter manual preview");
                configure(140,480,true,true);
                check(!world.experimentalSkillPreviewEnabled()&&world.skillState().snapshot(world.nowMs())==normalBefore,
                    "Returning from manual preview projects learned/test-effective configuration without granting normal learning");
                world.applyDebugOverrides({},spec.level);
                check(world.skillState().snapshot(world.nowMs())==normalBefore&&!world.experimentalSkillPreviewEnabled(),
                    "Disabling debug retains the normal learning ledger and leaves preview off");
            }
            store.close();
        }
        // Male Gunner base Knee now has an actual reviewed normal consumer.
        // Its TP is independently retained as a disabled visible source row.
        CharacterStore unavailableStore(temporary/"unavailable","normal-ui-negative-fixture");unavailableStore.data=normalUiRoot(2,0,15);
        World unavailable(pvf,assets,WorldRules::BetaFoundationV1);unavailable.enableExperimentalCharacters();Progression unavailableProgress(regions);unavailableStore.apply(0,unavailable,unavailableProgress);
        SkillLearningUi unavailableUi(pvf,assets);const auto unavailableLedger=unavailable.skillState().snapshot(unavailable.nowMs());
        const auto unavailableRequest=choose(unavailableUi,unavailable,15,{2,4});
        check(unavailable.runtimeSkillPolicy({2,4}).implemented&&bool(unavailableRequest.purchase),
            "Normally admitted own-source Knee upgrade is purchasable through actual learning UI");
        const auto tpRequest=choose(unavailableUi,unavailable,15,{2,168});
        check(!unavailable.runtimeSkillPolicy({2,168}).implemented&&!tpRequest.purchase,
            "Independently unadmitted TP168 remains inspectable but cannot be purchased through UI");
        check(unavailableUi.snapshot().at("view").at("budget")==unavailable.skillLearning().budget(unavailable.skillState(),15,unavailable.nowMs()).json()&&
            unavailable.skillState().snapshot(unavailable.nowMs())==unavailableLedger,"Inspecting admitted base and disabled TP displays authoritative points without mutating source grants");
        unavailableStore.close();
        CharacterStore waterStore(temporary/"water-optional-passives","normal-ui-water-negative-fixture");waterStore.data=normalUiRoot(8,0,50);
        World waterWorld(pvf,assets,WorldRules::BetaFoundationV1);waterWorld.enableExperimentalCharacters();Progression waterProgress(regions);waterStore.apply(0,waterWorld,waterProgress);
        SkillLearningUi waterUi(pvf,assets);const auto waterLedger=waterWorld.skillState().snapshot(waterWorld.nowMs());
        for(const SkillKey key:{SkillKey{8,236},SkillKey{8,51}}) {
            const auto blocked=choose(waterUi,waterWorld,50,key);
            check(!blocked.purchase&&!waterWorld.runtimeSkillPolicy(key).implemented&&
                waterWorld.skillState().snapshot(waterWorld.nowMs())==waterLedger,
                "Actual Water TP/elemental passive UI row stays inspectable and specifically unimplemented without a hidden purchase or ledger mutation");
        }
        waterStore.close();
        for(const auto spec:{Case{1,0,6,1},Case{4,0,116,30}}){
            CharacterStore gatedStore(temporary/("gated-job"+std::to_string(spec.job)),"normal-ui-gate-fixture");gatedStore.data=normalUiRoot(spec.job,spec.branch,spec.level);
            World gated(pvf,assets,WorldRules::BetaFoundationV1);gated.enableExperimentalCharacters();Progression gatedProgress(regions);gatedStore.apply(0,gated,gatedProgress);
            const auto before=gated.skillState().snapshot(gated.nowMs());SkillLearningUi gatedUi(pvf,assets);
            const auto rejected=choose(gatedUi,gated,spec.level,{spec.job,spec.skill});
            check(!rejected.purchase&&gated.skillState().snapshot(gated.nowMs())==before,
                "Real source level/branch gate disables learning for job "+std::to_string(spec.job)+" without mutation");
            gatedStore.close();
        }
        check(renderer.errors.empty(),"Actual hidden SDL learning/configuration rendering reports no resource errors");
        Json report={{"status","pass"},{"checks",checks},{"count",checks.size()},{"cases",cases},
            {"renderer_errors",renderer.errors},{"renderer_unsupported",renderer.unsupported},{"temporary_saves",temporary.u8string()},
            {"scope","Real hidden SDL tile/button -> SkillKey -> normal transaction -> learned slot -> CharacterStore consumers; main keyboard routing and frontend comparison pending"}};
        writeJson(output/"normal-learning-ui-bridge-tests.json",report);return report;
    }catch(const std::exception &error){writeJson(output/"normal-learning-ui-bridge-tests.json",{{"status","failed"},{"error",error.what()},
        {"checks",checks},{"count",checks.size()},{"temporary_saves",temporary.u8string()}});throw;}
}
} // namespace dnf
