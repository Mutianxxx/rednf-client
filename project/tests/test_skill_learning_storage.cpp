#include "dnf/skill_learning_transaction.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
namespace {
Json learningStorageRoot() {
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)},{"future_root",{{"keep",true}}}};
    root["characters"][0]={{"name","Learning storage"},{"class","swordman"},{"identity",CharacterIdentity{0,0,0}.json()},
        {"level",4},{"weapon",0},{"skill_initialization","source-v1"},{"future_character",Json::array({0,"keep"})}};
    return root;
}
Json learningWorldState(const World &world) {
    return {{"snapshot",world.snapshot()},{"simulation",world.simulationCheckpoint()},
        {"skills",world.skillState().snapshot(world.nowMs())},{"overlay",world.skillTestOverlay().snapshot()},
        {"events",world.eventLog()},{"inputs",world.inputs()}};
}
} // namespace
Json runSkillLearningStorageTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool okay,const char *name) {
        if (!okay) throw std::runtime_error(std::string("Skill learning storage: ")+name);
        checks.push_back(name);
    };
    const auto stamp=std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto directory=std::filesystem::absolute(std::filesystem::path("cache/skill-learning-storage-tests")/std::to_string(stamp));
    CharacterStore store(directory,"learning-storage-test"); store.data=learningStorageRoot();
    RegionCatalog catalog(pvf,assets); Progression progression(catalog); progression.initialize(4);
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    store.apply(0,world,progression);
    check(world.hasLearningLedger() && world.skillState().learnedLevel({0,5})==1 &&
        world.skillState().learnedLevel({0,46})==1 && world.skillState().learnedLevel({0,8})==0 &&
        world.skills[0].level==world.skillState().learnedLevel(world.skills[0].identity()),
        "New beta character source marker applies CHR gifts and projects the sole ledger into runtime arrays");
    const auto normal=world.skillState().snapshot(world.nowMs());
    store.capture(0,world,progression);
    auto character=store.data["characters"][0];
    check(character["skill_state"]["learning"]["mode"]=="new" && character["skills"]["8"]==0 &&
        character["skills"]["46"]==1 && character.contains("skill_test_overlay"),
        "Capture writes normal compatibility levels and a separate persistent test overlay");
    auto corruptedViews=character; corruptedViews["skills"]["46"]=99; corruptedViews["skills"]["8"]=999;
    corruptedViews["passives"]["basicmastery"]={{"obsolete_view","ignored"}};
    store.data["characters"][0]=corruptedViews;
    store.apply(0,world,progression);
    check(world.skillState().snapshot(world.nowMs())==normal && world.skillState().learnedLevel({0,46})==1 &&
        world.skillState().learnedLevel({0,8})==0,
        "Existing learning metadata outranks stale or obsolete compatibility arrays without granting skills");
    const auto prepared=world.skillLearning().prepare(world.skillState(),4,world.runtimeSkillPolicy({0,46}),
        {"storage-upper-2",{0,46},0,2},world.nowMs());
    check(prepared.ok,"Real source purchase prepares before storage round-trip");
    world.publishSkillLedger(prepared.state); store.capture(0,world,progression);
    store.commit("storage-learning-persist");
    const auto saved=store.data["characters"][0]; store.close();
    CharacterStore recovered(directory,"learning-storage-test");
    World loaded(pvf,assets,WorldRules::BetaFoundationV1); Progression restoredProgression(catalog);
    recovered.apply(0,loaded,restoredProgression);
    check(loaded.skillState().learnedLevel({0,46})==2 && loaded.skillLearning().budget(loaded.skillState(),4,loaded.nowMs()).spentSp==20 &&
        loaded.skillLearning().budget(loaded.skillState(),4,loaded.nowMs()).remainingSp==70 &&
        loaded.skillState().snapshot(loaded.nowMs())["learning"]["receipts"].contains("storage-upper-2"),
        "Actual reload preserves purchased level, spent points and stable learning receipt in the same save generation");
    const auto replay=loaded.skillLearning().prepare(loaded.skillState(),4,loaded.runtimeSkillPolicy({0,46}),
        {"storage-upper-2",{0,46},0,2},loaded.nowMs());
    check(replay.ok && replay.replayed && replay.state.snapshot(loaded.nowMs())==loaded.skillState().snapshot(loaded.nowMs()),
        "Learning request replay remains idempotent after disk reload");
    SkillLearningTestOverlay overlay;
    const auto test=loaded.skillLearning().prepareTest(loaded.skillState(),overlay,7,loaded.runtimeSkillPolicy({0,46}),
        {"storage-test-upper-3",{0,46},0,3},loaded.nowMs());
    check(test.ok,"Independent test purchase prepares with the source level gate");
    loaded.restoreSkillTestOverlay(test.overlay);
    auto debug=loaded.debugOverrides(); debug.enabled=true; debug.level=7;
    loaded.applyDebugOverrides(debug,4);
    recovered.capture(0,loaded,restoredProgression);
    check(recovered.data["characters"][0]["skills"]["46"]==2 &&
        recovered.data["characters"][0]["skill_state"]["learning"]["purchases"].size()==1 &&
        recovered.data["characters"][0]["skill_test_overlay"]["levels"][0]["level"]==3 &&
        recovered.data["characters"][0]["level"]==4,
        "Enabled test skills never enter normal compatibility views, point history or saved normal progression level");
    const auto savedTest=recovered.data["characters"][0];
    World testReload(pvf,assets,WorldRules::BetaFoundationV1); Progression testReloadProgression(catalog);
    recovered.apply(0,testReload,testReloadProgression);
    check(!testReload.debugOverrides().enabled && testReload.skillState().learnedLevel({0,46})==2 &&
        testReload.skillTestOverlay().snapshot()==test.overlay.snapshot(),
        "New-process restore retains separate test selections while normal authoritative skills remain active");
    auto legacy=learningStorageRoot()["characters"][0]; legacy.erase("skill_initialization");
    legacy["skills"]={{"46",0},{"8",0},{"99999",7},{"future_active",{{"keep",1}}}};
    legacy["passives"]={{"basicmastery",0},{"future_passive",{{"keep",2}}}};
    CharacterSkillState old({0,0,0}); old.setLearnedLevel({0,88888},3);
    auto oldSnapshot=old.snapshot(0); oldSnapshot["future_ledger"]={{"keep",true}}; old.restore(oldSnapshot,0);
    legacy["skill_state"]=old.snapshot(0);
    recovered.data["characters"][0]=legacy;
    recovered.apply(0,testReload,testReloadProgression); recovered.capture(0,testReload,testReloadProgression);
    check(testReload.skillState().learnedLevel({0,46})==0 && testReload.skillState().learnedLevel({0,8})==0 &&
        testReload.skillState().learnedLevel({0,99999})==7 && testReload.skillState().learnedLevel({0,88888})==3 &&
        testReload.skillLearning().budget(testReload.skillState(),4,testReload.nowMs()).spentSp==0 &&
        recovered.data["characters"][0]["skill_state"]["future_ledger"]["keep"]==true &&
        recovered.data["characters"][0]["skills"]["future_active"]["keep"]==1 &&
        recovered.data["characters"][0]["passives"]["future_passive"]["keep"]==2,
        "Legacy migration preserves explicit zero, unknown ledger keys, numeric future IDs and unknown fields without inventing consumption");
    recovered.data["characters"][0]=saved;
    World live(pvf,assets,WorldRules::BetaFoundationV1);
    // Prepare a live action whose cancellation must be observable if a malformed
    // restored skill budget is checked too late.
    live.skillState().setLearnedLevel({0,46},1);
    auto liveInitialized=live.skillLearning().prepareInitialization(live.skillState(),4,SkillInitializationMode::LegacyImport,live.nowMs());
    check(liveInitialized.ok,"Live preflight fixture initializes its own skill history");
    live.publishSkillLedger(liveInitialized.state); live.characterLevel=4; live.activate(0);
    live.player.hp-=9; live.randomStreams().stream(RandomDomain::Combat,19).next(); live.enqueue({2000000000,27,true});
    const auto liveBefore=learningWorldState(live), progressionBefore=testReloadProgression.state;
    std::vector<Json> invalid;
    auto bad=saved; bad["skill_state"]["learning"]["package_identity"]="mismatch"; invalid.push_back(bad);
    bad=saved; bad["skill_state"]["learning"]["purchases"][0]["from_level"]=7; invalid.push_back(bad);
    bad=saved; bad["skill_state"]["learning"]["purchases"][0]["cost"]=-1; invalid.push_back(bad);
    bad=saved; bad["skill_state"]["learning"]["schema"]=999; invalid.push_back(bad);
    bad=saved; bad["skill_initialization"]="unrecognized"; invalid.push_back(bad);
    bad=savedTest; bad["skill_test_overlay"]["spent_sp"]=0; invalid.push_back(bad);
    bad=savedTest; bad["skill_test_overlay"]["levels"][0]["key"]["job_id"]=1; invalid.push_back(bad);
    for (const auto &candidate:invalid) {
        recovered.data["characters"][0]=candidate; bool rejected=false;
        try { recovered.apply(0,live,testReloadProgression); } catch (const std::exception &) { rejected=true; }
        check(rejected && learningWorldState(live)==liveBefore && testReloadProgression.state==progressionBefore,
            "Malformed learning or test-overlay restoration fails before live controller, simulation, RNG, ledger and progression mutation");
    }
    // A dormant overlay can become stale after a normal purchase. Keep it for
    // explicit conflict reporting/reset without refusing the normal saved game.
    auto dormant=saved; dormant["skill_test_overlay"]=test.overlay.snapshot();
    const auto next=loaded.skillLearning().prepare(loaded.skillState(),7,loaded.runtimeSkillPolicy({0,46}),
        {"dormant-new-normal",{0,46},1,3},loaded.nowMs());
    if (next.ok) {
        dormant["skill_state"]=next.state.snapshot(loaded.nowMs());
        dormant["level"]=7; dormant["progression"]["level"]=7;
        recovered.data["characters"][0]=dormant;
        World dormantReload(pvf,assets,WorldRules::BetaFoundationV1); Progression dormantProgression(catalog);
        recovered.apply(0,dormantReload,dormantProgression);
        check(dormantReload.skillState().learnedLevel({0,46})==3 &&
            dormantReload.skillLearning().quoteTest(dormantReload.skillState(),dormantReload.skillTestOverlay(),10,
                dormantReload.runtimeSkillPolicy({0,46}),4,dormantReload.nowMs()).gate==SkillLearningGate::StaleRevision,
            "Dormant stale overlay reloads with normal state and reports conflict on test use without silent deletion");
    } else throw std::runtime_error("Skill learning storage dormant-overlay fixture purchase failed");
    recovered.close();
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"save_directory",directory.u8string()},
        {"scope","Isolated real CharacterStore capture/apply/migration; no player saves or frontend automation"}};
}
} // namespace dnf
