#include "dnf/skill_learning_transaction.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
namespace {
Json learningTransactionRoot() {
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)},{"future_root","kept"}};
    root["characters"][0]={{"name","Learning transaction"},{"class","swordman"},
        {"identity",CharacterIdentity{0,0,0}.json()},{"level",4},{"weapon",0},{"skill_initialization","source-v1"}};
    return root;
}
Json transactionLive(const World &world,const Progression &progression) {
    return {{"snapshot",world.snapshot()},{"simulation",world.simulationCheckpoint()},
        {"ledger",world.skillState().snapshot(world.nowMs())},{"overlay",world.skillTestOverlay().snapshot()},
        {"progression",progression.state},{"events",world.eventLog()},{"inputs",world.inputs()}};
}
} // namespace
Json runSkillLearningTransactionTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool okay,const char *name) {
        if (!okay) throw std::runtime_error(std::string("Durable skill learning: ")+name);
        checks.push_back(name);
    };
    const auto stamp=std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto root=std::filesystem::absolute(std::filesystem::path("cache/skill-learning-transaction-tests")/std::to_string(stamp));
    RegionCatalog catalog(pvf,assets);
    const std::vector<SaveFailurePoint> points={SaveFailurePoint::BeforePublish,SaveFailurePoint::AfterPublish};
    for (size_t index=0;index<points.size();++index) {
        const auto directory=root/std::to_string(index);
        CharacterStore store(directory,"learning-transaction-test"); store.data=learningTransactionRoot();
        World world(pvf,assets,WorldRules::BetaFoundationV1); Progression progression(catalog);
        store.apply(0,world,progression);
        world.advance(25000000,0); world.enqueue({2000000000,27,true});
        world.randomStreams().stream(RandomDomain::Loot,31).next();
        store.capture(0,world,progression); store.checkpoint();
        const auto baselineGeneration=store.generation();
        const auto before=transactionLive(world,progression);
        const auto priorBytes=readFile(directory/"characters.json");
        const Json region={{"schema",3},{"run_token","same-generation-run"},{"rewards",{{"kill-A","claimed"}}},
            {"world",{{"hp",world.player.hp},{"mp",world.player.mp}}},{"future_region",Json::array({1,4,1})}};
        const SkillLearningRequest request{"durable-upper-2",{0,46},0,2};
        store.setFailureInjector([failure=points[index]](SaveFailurePoint point) {
            if (point==failure) throw std::runtime_error("injected skill-learning save fault");
        });
        SkillLearningTransaction transaction;
        const auto failed=transaction.submit(store,0,world,progression,request,region);
        check(failed.state==SkillLearningTransactionState::Pending && !failed.ok && transaction.pending() &&
            store.hasPendingCommit() && transactionLive(world,progression)==before && store.generation()==baselineGeneration,
            "Injected disk fault retains an exact prepared request while live skill levels, MP, cooldown, simulation, RNG and progression stay unchanged");
        const auto diskAfter=readFile(directory/"characters.json");
        if (points[index]==SaveFailurePoint::BeforePublish)
            check(diskAfter==priorBytes,"BeforePublish failure preserves the complete previous primary generation");
        else {
            const auto published=Json::parse(diskAfter);
            check(diskAfter!=priorBytes && published["characters"][0]["skill_state"]["learning"]["purchases"].size()==1 &&
                published["characters"][0]["region_session"]==region && published["characters"][0]["skills"]["46"]==2,
                "AfterPublish failure has one complete durable learning generation including region rewards and compatible normal levels");
        }
        const auto pending=transaction.pendingSnapshot(); const auto staged=store.data;
        const auto blocked=transaction.submit(store,0,world,progression,{"second-request",{0,5},0,2},region);
        check(!blocked.ok && transaction.pendingSnapshot()==pending && store.data==staged && transactionLive(world,progression)==before,
            "A second learning command cannot replace a retained pending candidate");
        store.setFailureInjector({});
        const auto recovered=transaction.retry(store,world);
        check(recovered.ok && recovered.state==SkillLearningTransactionState::Committed && !transaction.pending() &&
            !store.hasPendingCommit() && store.generation()==baselineGeneration+1 && world.skillState().learnedLevel({0,46})==2 &&
            world.skillLearning().budget(world.skillState(),4,world.nowMs()).spentSp==20,
            "Retry publishes the frozen candidate after its exact durable generation without repeating source costs");
        check(store.data["characters"][0]["region_session"]==region &&
            store.data["characters"][0]["simulation"]==before["simulation"] &&
            store.data["characters"][0]["progression"]==progression.state &&
            store.data["characters"][0]["skill_state"]==world.skillState().snapshot(world.nowMs()),
            "Durable learning uses the same complete region, simulation, pending input, RNG and progression generation");
        const auto completed=transactionLive(world,progression);
        const auto generation=store.generation();
        const auto repeated=transaction.submit(store,0,world,progression,request,region);
        check(repeated.ok && repeated.state==SkillLearningTransactionState::Replayed && store.generation()==generation &&
            transactionLive(world,progression)==completed,
            "A repeated durable purchase is acknowledged without a new save generation or a second point spend");
        auto conflict=request; conflict.targetLevel=3;
        const auto conflictResult=transaction.submit(store,0,world,progression,conflict,region);
        check(!conflictResult.ok && !transaction.pending() && transactionLive(world,progression)==completed && store.generation()==generation,
            "Durable request-ID payload conflict fails without mutating the saved or live state");
        store.close();
        CharacterStore reloadedStore(directory,"learning-transaction-test");
        World reloadedWorld(pvf,assets,WorldRules::BetaFoundationV1); Progression reloadedProgression(catalog);
        reloadedStore.apply(0,reloadedWorld,reloadedProgression);
        SkillLearningTransaction restarted;
        const auto restartedReplay=restarted.submit(reloadedStore,0,reloadedWorld,reloadedProgression,request,region);
        check(restartedReplay.ok && restartedReplay.state==SkillLearningTransactionState::Replayed &&
            reloadedWorld.skillState().learnedLevel({0,46})==2 &&
            reloadedWorld.skillLearning().budget(reloadedWorld.skillState(),4,reloadedWorld.nowMs()).spentSp==20 &&
            reloadedStore.generation()==generation,
            "New-process store reload recognizes the durable request and preserves the exact purchased budget");
        const auto noPending=restarted.retry(reloadedStore,reloadedWorld);
        check(!noPending.ok && !restarted.pending(),"Retry without a pending request cannot execute learning");
        reloadedStore.close();
    }
    {
        CharacterStore store(root/"gates","learning-transaction-test"); store.data=learningTransactionRoot();
        World world(pvf,assets,WorldRules::BetaFoundationV1); Progression progression(catalog);
        store.apply(0,world,progression); store.capture(0,world,progression); store.checkpoint();
        const Json region=Json::object(); SkillLearningTransaction transaction;
        const SkillLearningRequest request{"gate-upper-2",{0,46},0,2};
        const auto baseline=world.skillState().snapshot(world.nowMs()); const auto generation=store.generation();
        world.combat=true; const auto combat=transaction.submit(store,0,world,progression,request,region); world.combat=false;
        world.player.dead=true; const auto dead=transaction.submit(store,0,world,progression,request,region); world.player.dead=false;
        auto debug=world.debugOverrides(); debug.enabled=true; world.applyDebugOverrides(debug,4);
        const auto testMode=transaction.submit(store,0,world,progression,request,region);
        debug.enabled=false; world.applyDebugOverrides(debug,4);
        check(!combat.ok && !dead.ok && !testMode.ok && !transaction.pending() &&
            world.skillState().snapshot(world.nowMs())==baseline && store.generation()==generation,
            "Combat, death and enabled test overrides cannot enter normal durable learning or alter its budget");
        world.activate(0); const auto active=transaction.submit(store,0,world,progression,request,region);
        check(!active.ok && !transaction.pending() && store.generation()==generation,
            "An active skill action cannot execute a normal learning transaction");
        world.idle();
        const auto invalid=transaction.submit(store,0,world,progression,{"gate-skip",{0,46},0,5},region);
        check(!invalid.ok && !transaction.pending() && store.generation()==generation &&
            world.skillState().snapshot(world.nowMs())["learning"]["purchases"].empty(),
            "Rejected qualification does not capture or write a save generation");
        store.close();
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"save_directory",root.u8string()},
        {"scope","Durable-first normal learning, exact retry/replay and isolated BeforePublish/AfterPublish failures; no player saves or frontend automation"}};
}
} // namespace dnf
