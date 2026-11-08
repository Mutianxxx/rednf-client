#include "dnf/pending_rewards.hpp"
#include "dnf/reward_recovery.hpp"
#include "dnf/storage.hpp"
#include "dnf/character_entry.hpp"
#include "dnf/beta_branch.hpp"
#include <algorithm>
#include <chrono>
#include <climits>
#include <fstream>
#include <memory>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
namespace fs = std::filesystem;
std::string killKey(const RegionSession &session, int actor) {
    return session.run.token + ":" + std::to_string(session.run.current) + ":" + std::to_string(actor);
}
fs::path testDirectory(const std::string &label) {
    static uint64_t sequence = 0;
    return fs::absolute(fs::path("cache/pending-reward-tests") /
        (std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + "-" +
         std::to_string(++sequence) + "-" + label));
}
void character(CharacterStore &store) {
    store.data["characters"][0] = {{"name", "Pending reward regression"}, {"class", "swordman"},
        {"identity", CharacterIdentity{}.json()}, {"future_character", {{"preserved", 71}}}};
}
bool rejects(const std::function<void()> &action) {
    try { action(); } catch (const std::exception &) { return true; }
    return false;
}
struct Fixture {
    RegionCatalog &catalog;
    Progression progress;
    World world;
    RegionSession session;
    PendingRewardService service;
    explicit Fixture(Pvf &pvf, Assets &assets, RegionCatalog &content, bool sourceWorld = false)
        : catalog(content), progress(content),
          world(pvf, assets, sourceWorld ? WorldRules::BetaFoundationV1 : WorldRules::LegacyDemoV1) {
        if(content.prepareDungeon(1).at("status")!="prepared")
            throw std::runtime_error("Pending fixture requires prepared source Lorien closure");
        world.applyEquipment(progress); world.freezeAi = true; world.combat = true;
        world.mapWidth = 1400; world.walkRects = {{0, 0, 1400, 700}};
        session.begin(content, 1, 9801); session.run.current = session.run.boss;
        const auto &spawns = content.maps.at(session.run.room().mapId).monsters;
        if (spawns.size() < 2) throw std::runtime_error("Pending fixture requires actual multi-actor Lorien boss MAP");
        for (size_t i = 0; i < spawns.size(); ++i) {
            Actor actor; actor.id = int(i + 1); actor.sourceId = spawns[i].id;
            actor.monsterPath = content.monsterPath(spawns[i].id);
            actor.x = actor.px = spawns[i].x; actor.y = actor.py = spawns[i].y + 80;
            actor.z = actor.pz = spawns[i].z; actor.hp = actor.maxHp = 1;
            actor.boss = spawns[i].type == "[boss]";
            world.monsters.push_back(std::move(actor));
        }
        world.synchronizeEntityHandles();
        service.characterBoundary(world);
    }
    void kills(int64_t firstTick = 2, int64_t restTick = 4) {
        world.setObjectTick([this, firstTick, restTick](World &simulation) {
            if (simulation.tick == firstTick) simulation.diagnosticHit(1, 1, 0, 0, 1, {});
            if (simulation.tick == restTick)
                for (size_t i = 1; i < simulation.monsters.size(); ++i)
                    simulation.diagnosticHit(int(i + 1), 1, 0, 0, 1, {});
        });
        world.advance(1000000000, 8);
        session.remember(world);
    }
    bool observe() { return service.observe(progress, world, session, session.save(world, "dungeon")); }
    void capture(CharacterStore &store, bool town = false) {
        store.capture(0, world, progress);
        store.data["characters"][0]["region_session"] = town ? RegionSession{}.save(world, "town") : session.save(world, "dungeon");
    }
    bool checkpoint(CharacterStore &store, bool town = false) {
        capture(store, town); store.checkpoint();
        return service.acknowledgeCheckpoint(progress, world, store, 0);
    }
};
// Hooks use the actual B/C service and CharacterStore. Recovery sequencing,
// deadlines, exit and Results gates execute the same Flow called by main.
struct RecoveryHarness {
    Fixture &fixture;
    CharacterStore &store;
    int captureCalls=0,persistCalls=0,publishCalls=0,failureCalls=0,unavailableReports=0;
    bool captureFault=false,failFinalSave=false,throwPresentation=false;
    std::string fallbackText,saveError;
    RewardRecoveryReporter reporter;
    RewardRecoveryFlow flow;
    RewardRecoveryHooks hooks;
    RecoveryHarness(Fixture &f,CharacterStore &s,const fs::path &report)
        : fixture(f),store(s),reporter(report,[this](const std::string &text){fallbackText=text;}),
          flow(f.service,f.progress,f.world,f.catalog),
          hooks{[this]{return store.hasPendingCommit();},
                [this]{
                    ++captureCalls;
                    if(captureFault) {fixture.service.captureFailure("Injected main capture failure");failure("");return false;}
                    if(!fixture.observe()){failure("");return false;}return true;
                },
                [this]{
                    ++persistCalls;
                    try {fixture.capture(store);store.save();
                        return fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,store,0);
                    }catch(const std::exception &error){saveError=error.what();return false;}
                },
                [this]{
                    ++publishCalls;
                    if(failFinalSave)store.setFailureInjector([](SaveFailurePoint at){
                        if(at==SaveFailurePoint::AfterWrite)throw std::runtime_error("Injected main final checkpoint failure");});
                    if(throwPresentation)throw std::runtime_error("Injected main appearance refresh failure");
                },
                [this](const std::string &error){failure(error);}} {}
    void failure(const std::string &error) {
        ++failureCalls;auto diagnostic=fixture.service.diagnostic();
        if(!error.empty())diagnostic["recovery_error"]=error;
        if(reporter.publish(diagnostic)==RewardDiagnosticResult::Unavailable)++unavailableReports;
    }
};
} // namespace

Json runPendingRewardTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), samples = Json::object();
    const auto check = [&](bool okay, const char *message) {
        if (!okay) throw std::runtime_error(std::string("Pending rewards: ") + message);
        checks.push_back(message);
    };
    RegionCatalog catalog(pvf, assets);
    {
        const auto directory=testDirectory("best-effort-report");
        const auto path=directory/"reward-pending.json";fs::create_directories(path);
        const Json diagnostic={{"status","blocked"},{"error","original source preparation error"},{"pending_key","keep-this-intent"}};
        int fallbacks=0;std::string fallback;
        RewardRecoveryReporter reporter(path,[&](const std::string &text){++fallbacks;fallback=text;});
        check(reporter.publish(diagnostic)==RewardDiagnosticResult::Unavailable&&fallbacks==1&&
              fallback.find("original source preparation error")!=std::string::npos&&
              reporter.publish(diagnostic)==RewardDiagnosticResult::Unavailable&&fallbacks==2,
            "Actual writeJson directory collision keeps the original diagnostic and retries unchanged failed output without throwing");
        fs::rename(path,directory/"preserved-failed-report-directory");
        check(reporter.publish(diagnostic)==RewardDiagnosticResult::Written&&
              Json::parse(readFile(path))==diagnostic&&reporter.publish(diagnostic)==RewardDiagnosticResult::Unchanged&&fallbacks==2,
            "Only a successful real report write is deduplicated after the failed path is repaired without deleting evidence");
        fs::rename(path,directory/"preserved-first-success.json");fs::create_directories(path);
        auto changed=diagnostic;changed["later_attempt"]=2;
        check(reporter.publish(changed)==RewardDiagnosticResult::Unavailable,
            "A later diagnostic write failure invalidates prior success deduplication");
        fs::rename(path,directory/"preserved-later-report-directory");
        check(reporter.publish(diagnostic)==RewardDiagnosticResult::Written&&Json::parse(readFile(path))==diagnostic,
            "After a later failed output, even a previously successful diagnostic is really written again");
        const auto bad=directory/"fallback-throws.json";fs::create_directories(bad);
        RewardRecoveryReporter brokenFallback(bad,[](const std::string &){throw std::runtime_error("Injected fallback sink failure");});
        check(brokenFallback.publish(diagnostic)==RewardDiagnosticResult::Unavailable,
            "A failing report and failing fallback sink cannot escape the noexcept diagnostic consumer");
    }
    {
        Fixture fixture(pvf,assets,catalog);
        const auto directory=testDirectory("main-recovery-source-report");
        CharacterStore store(directory/"save","main-recovery-source-report");character(store);
        check(fixture.checkpoint(store),"Application recovery starts from an actual committed world");
        fixture.kills();const auto beforeRng=fixture.world.randomStreams().snapshot();
        const auto path=directory/"reports/reward-pending.json";fs::create_directories(path);
        RecoveryHarness recovery(fixture,store,path);
        auto missing=catalog.monsters.extract(fixture.world.monsters.back().sourceId);
        const auto generation=store.generation();
        const bool ready=recovery.flow.pump(recovery.hooks);
        check(!ready&&store.generation()==generation+1&&fixture.service.hasPending(fixture.progress)&&
              recovery.persistCalls==1&&recovery.publishCalls==0&&recovery.unavailableReports==1&&
              !recovery.fallbackText.empty()&&fixture.world.randomStreams().snapshot()==beforeRng&&
              !recovery.flow.resultsReady(ready,false,fixture.session)&&
              !recovery.flow.resultsReady(true,false,fixture.session),
            "Actual application pump keeps durable source-failed intent/RNG and denies automatic plus manual same-frame Results despite report I/O failure");
        const auto pending=fixture.progress.state, pausedClock=fixture.world.simulationCheckpoint().at("clock");
        check(recovery.flow.allowControlledExit(false,true,recovery.hooks)&&fixture.progress.state==pending&&
              fixture.world.randomStreams().snapshot()==beforeRng&&fixture.service.hasPending(fixture.progress),
            "Controlled exit may save durable source-failed intent without drawing rewards or requiring successful diagnostics");
        check(recovery.flow.tryAutomaticRetry(100,true,recovery.hooks)&&recovery.flow.retryAfter()==1100&&
              !recovery.flow.tryAutomaticRetry(1099,true,recovery.hooks)&&recovery.unavailableReports==2&&
              fixture.world.simulationCheckpoint().at("clock")==pausedClock&&fixture.progress.state==pending&&
              fixture.world.randomStreams().snapshot()==beforeRng,
            "Actual retry schedule uses supplied wall time while paused simulation and source-failed intent/RNG remain unchanged");
        catalog.monsters.insert(std::move(missing));
        check(recovery.flow.tryAutomaticRetry(1100,true,recovery.hooks)&&recovery.publishCalls==1&&
              !fixture.service.blocked(fixture.progress)&&recovery.flow.resultsReady(true,false,fixture.session),
            "Repairing the actual MOB source lets the due application retry publish and durably unlock Results exactly once");
        const auto final=fixture.progress.state,finalRng=fixture.world.randomStreams().snapshot();
        check(!recovery.flow.tryAutomaticRetry(2100,true,recovery.hooks)&&fixture.progress.state==final&&
              fixture.world.randomStreams().snapshot()==finalRng&&recovery.publishCalls==1,
            "Resolved application retries do not rerun rewards or consume further Loot draws");
        store.close();
    }
    {
        for(const bool finalPhase:{false,true}) {
            Fixture fixture(pvf,assets,catalog);
            const auto directory=testDirectory(finalPhase?"main-final-fault":"main-intent-fault");
            CharacterStore store(directory/"save","main-recovery-disk-fault");character(store);
            check(fixture.checkpoint(store),"Application disk-fault fixture has a prior durable generation");
            fixture.kills();RecoveryHarness recovery(fixture,store,directory/"reports/reward-pending.json");
            recovery.failFinalSave=finalPhase;
            if(!finalPhase)store.setFailureInjector([](SaveFailurePoint at){
                if(at==SaveFailurePoint::AfterWrite)throw std::runtime_error("Injected main intent checkpoint failure");});
            const bool ready=recovery.flow.pump(recovery.hooks);
            const auto pending=fixture.progress.state,rng=fixture.world.randomStreams().snapshot();
            const int captures=recovery.captureCalls,persists=recovery.persistCalls;
            check(!ready&&store.hasPendingCommit()&&!recovery.flow.resultsReady(ready,true,fixture.session)&&
                  !recovery.flow.resultsReady(true,true,fixture.session)&&
                  !recovery.flow.allowControlledExit(false,true,recovery.hooks)&&
                  !recovery.flow.tryAutomaticRetry(3000,true,recovery.hooks)&&
                  !recovery.flow.pump(recovery.hooks)&&recovery.captureCalls==captures&&recovery.persistCalls==persists&&
                  fixture.progress.state==pending&&fixture.world.randomStreams().snapshot()==rng,
                "Both actual intent/final disk faults block same-frame Results, controlled exit and further capture until exact pending save retry");
            store.setFailureInjector({});store.retryPending();
            check(fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,store,0),
                "Application save-retry boundary confirms the retained actual CharacterStore candidate");
            recovery.failFinalSave=false;
            check(recovery.flow.pump(recovery.hooks)&&recovery.publishCalls==1&&
                  recovery.flow.resultsReady(true,false,fixture.session)&&!store.hasPendingCommit(),
                "Retrying either saved phase completes the actual application flow and opens Results with one reward publication");
            if(finalPhase)check(fixture.progress.state==pending&&fixture.world.randomStreams().snapshot()==rng,
                "Final-phase retry preserves the exact already-prepared receipt/drop/RNG without a second reward execution");
            store.close();
        }
    }
    {
        Fixture fixture(pvf,assets,catalog);
        const auto directory=testDirectory("main-exit-capture-fault");
        CharacterStore store(directory/"save","main-exit-capture-fault");character(store);
        check(fixture.checkpoint(store),"Uncaptured exit fault starts from a real prior save");
        fixture.kills();const auto progress=fixture.progress.state,rng=fixture.world.randomStreams().snapshot();
        const auto path=directory/"reports/reward-pending.json";fs::create_directories(path);
        RecoveryHarness recovery(fixture,store,path);recovery.captureFault=true;
        check(!recovery.flow.allowControlledExit(false,true,recovery.hooks)&&fixture.service.captureIncomplete()&&
              fixture.progress.state==progress&&fixture.world.randomStreams().snapshot()==rng&&recovery.persistCalls==0&&
              recovery.unavailableReports==1,
            "Actual controlled exit refuses uncaptured deaths even when diagnostic output also fails");
        recovery.captureFault=false;
        check(recovery.flow.allowControlledExit(false,true,recovery.hooks)&&!fixture.service.captureIncomplete()&&
              fixture.service.hasPending(fixture.progress)&&recovery.persistCalls==1&&recovery.publishCalls==0&&
              fixture.world.randomStreams().snapshot()==rng,
            "Repairing capture permits exit only after real intent checkpoint and never grants rewards during exit");
        store.close();
    }
    {
        Fixture fixture(pvf,assets,catalog);
        const auto directory=testDirectory("main-recovery-catch-report");
        CharacterStore store(directory/"save","main-recovery-catch-report");character(store);
        check(fixture.checkpoint(store),"Presentation-fault application flow has a real starting checkpoint");
        fixture.kills();const auto path=directory/"reports/reward-pending.json";fs::create_directories(path);
        RecoveryHarness recovery(fixture,store,path);recovery.throwPresentation=true;
        check(!recovery.flow.pump(recovery.hooks)&&fixture.service.needsCheckpoint()&&
              !fixture.service.hasPending(fixture.progress)&&recovery.publishCalls==1&&recovery.unavailableReports==1&&
              recovery.fallbackText.find("Injected main appearance refresh failure")!=std::string::npos&&
              !recovery.flow.resultsReady(true,false,fixture.session),
            "Actual pump catch after reward publication retains dirty output and original error when report writing fails without fatal");
        const auto prepared=fixture.progress.state,rng=fixture.world.randomStreams().snapshot();
        check(recovery.flow.tryAutomaticRetry(5000,true,recovery.hooks)&&!fixture.service.blocked(fixture.progress)&&
              recovery.publishCalls==1&&fixture.progress.state==prepared&&fixture.world.randomStreams().snapshot()==rng&&
              recovery.flow.resultsReady(true,false,fixture.session),
            "Next real application retry checkpoints prepared output after presentation/report failure without replaying rewards");
        store.close();
    }
    {
        Fixture fixture(pvf, assets, catalog);
        CharacterStore store(testDirectory("batch"), "pending-reward-fixture"); character(store);
        check(fixture.checkpoint(store), "Initial production CharacterStore snapshot is acknowledged");
        const auto initialCursor = fixture.service.eventCursor();
        fixture.kills();
        const auto oldRng = fixture.world.randomStreams().snapshot();
        size_t soundCursor = fixture.service.eventCursor();
        std::set<int64_t> ticks;
        while (soundCursor < fixture.world.events.size()) {
            const auto &event = fixture.world.events[soundCursor++];
            if (event.kind == "killed") ticks.insert(event.tick);
        }
        check(ticks == std::set<int64_t>{2,4} && fixture.service.eventCursor() == initialCursor &&
              fixture.progress.state.at("events").empty(),
            "Sound/HUD cursor can consume real World deaths while reward cursor and receipts remain untouched");
        check(fixture.observe() && fixture.service.needsCheckpoint() && fixture.service.blocked(fixture.progress) &&
              fixture.service.eventCursor() == fixture.world.events.size(),
            "Actual same-pump kill capture atomically advances its independent cursor and blocks gameplay");
        const auto &pending = fixture.progress.state.at("pending_rewards");
        check(pending.at("kills").size() == fixture.world.monsters.size() && pending.at("clears").size() == 1 &&
              pending.at("origins").at(fixture.session.run.token).at("session").at("room_states").at(fixture.session.run.boss).size() == fixture.world.monsters.size(),
            "Every death and the nonempty boss clear retain one frozen same-tick source session");
        const auto captured = fixture.progress.state;
        check(!fixture.service.prepareAndPublish(fixture.progress, fixture.world, catalog) && fixture.progress.state == captured &&
              fixture.world.randomStreams().snapshot() == oldRng,
            "No reward draw or receipt occurs before the pending death facts have a committed checkpoint");
        check(fixture.checkpoint(store) && fixture.service.hasPending(fixture.progress),
            "Intent checkpoint preserves dead actors, pending rows and pre-reward RNG in one generation");
        auto &ai = fixture.world.randomStreams().stream(RandomDomain::Ai, 19);
        auto *aiAddress = &ai; ai.next();
        auto &loot = fixture.world.randomStreams().stream(RandomDomain::Loot, 29);
        auto *lootAddress = &loot; loot.next();
        const auto aiBefore = ai.snapshot(), lootBefore = loot.snapshot();
        check(fixture.checkpoint(store), "Pre-existing named streams are part of the durable input generation");
        check(fixture.service.prepareAndPublish(fixture.progress, fixture.world, catalog) && fixture.service.needsCheckpoint() &&
              !fixture.service.hasPending(fixture.progress) && fixture.service.blocked(fixture.progress),
            "Prepared entire batch publishes once but remains blocked until final receipt/drop/RNG checkpoint");
        check(&fixture.world.randomStreams().stream(RandomDomain::Ai, 19) == aiAddress && ai.snapshot() == aiBefore &&
              &fixture.world.randomStreams().stream(RandomDomain::Loot, 29) == lootAddress && loot.snapshot() == lootBefore,
            "Loot-node publication preserves existing AI and unrelated Loot references and values");
        check(fixture.progress.state.at("events").size() == fixture.world.monsters.size() &&
              fixture.progress.state.at("drops").size() == fixture.world.monsters.size() &&
              fixture.progress.state.at("clears").size() == 1 && !fixture.service.clearReceipt(fixture.progress, fixture.session),
            "All kills and one clear publish together and cannot expose Results before durable acknowledgement");
        check(fixture.checkpoint(store) && fixture.service.clearReceipt(fixture.progress, fixture.session),
            "Only matching durably saved clear receipt opens Results");
        const auto final = fixture.progress.state, finalRng = fixture.world.randomStreams().snapshot();
        check(fixture.observe() && fixture.service.prepareAndPublish(fixture.progress, fixture.world, catalog) &&
              fixture.progress.state == final && fixture.world.randomStreams().snapshot() == finalRng,
            "Repeated frame capture and pump do not grant another clear or draw another drop");
        for (auto &room : fixture.session.run.rooms) room.cleared = true;
        check(fixture.service.clearReceipt(fixture.progress, fixture.session),
            "Post-boss optional branch clearing reads original receipt room count without issuing or conflicting rewards");
        samples["normal_batch"] = final.at("pending_rewards"); store.close();
    }
    {
        Fixture fixture(pvf, assets, catalog); fixture.kills();
        const auto before = fixture.progress.state;
        const auto cursor = fixture.service.eventCursor();
        auto invalidOrigin = fixture.session.save(fixture.world, "dungeon"); invalidOrigin["run"]["token"] = "wrong";
        check(!fixture.service.observe(fixture.progress, fixture.world, fixture.session, invalidOrigin) &&
              fixture.progress.state == before && fixture.service.eventCursor() == cursor && fixture.service.captureIncomplete(),
            "Origin/capture failure preserves the entire event batch and old cursor instead of skipping a death");
        check(fixture.observe() && !fixture.service.captureIncomplete(), "Corrected origin captures exactly the retained batch");
        fixture.world.events.clear(); const auto pending = fixture.progress.state;
        check(!fixture.observe() && fixture.progress.state == pending && fixture.service.captureIncomplete(),
            "Shrinking event history before a character boundary is a blocking diagnostic, never a silent cursor reset");
    }
    {
        // Source faults are applied after the durable pending generation. Each
        // must reject the COMPLETE batch, including any preceding valid rows.
        for (const std::string fault : {"missing-mob", "bad-later-item", "unknown-item", "xp-overflow", "rng-exhausted"}) {
            RegionCatalog isolated(pvf, assets);
            Fixture fixture(pvf, assets, isolated); fixture.kills(); check(fixture.observe(), "Fault fixture captures real deaths");
            if (fault == "xp-overflow") fixture.progress.state["xp"] = INT64_MAX;
            if (fault == "rng-exhausted") {
                const auto &row = fixture.progress.state.at("pending_rewards").at("kills").begin().value();
                const auto key = fixture.progress.state.at("pending_rewards").at("kills").begin().key();
                uint64_t hash = 1469598103934665603ull;
                for (unsigned char ch : key) hash = (hash ^ ch) * 1099511628211ull;
                auto &random = fixture.world.randomStreams().stream(RandomDomain::Loot, hash ^ row.at("seed").get<uint64_t>());
                auto checkpoint = random.snapshot(); checkpoint["draws"] = UINT64_MAX; random.restore(checkpoint);
            }
            CharacterStore store(testDirectory(fault), "pending-reward-fault"); character(store);
            check(fixture.checkpoint(store), "Fault fixture checkpoints complete pending/RNG input");
            const int monster = fixture.world.monsters.back().sourceId;
            auto savedMob = isolated.monsters.at(monster);
            if (fault == "missing-mob") isolated.monsters.erase(monster);
            if (fault == "bad-later-item") {
                auto &mob = isolated.monsters.at(monster);
                mob.fields.push_back({"[item]", Json::array({3227,800,17}), uint32_t(mob.rawBytes.size())});
                mob.fields.push_back({"[/item]", Json::array(), uint32_t(mob.rawBytes.size()+1)});
            }
            if (fault == "unknown-item") {
                auto &mob = isolated.monsters.at(monster);
                mob.fields.push_back({"[item]", Json::array({INT_MAX,1}), uint32_t(mob.rawBytes.size())});
                mob.fields.push_back({"[/item]", Json::array(), uint32_t(mob.rawBytes.size()+1)});
            }
            const auto before = fixture.progress.state, rng = fixture.world.randomStreams().snapshot();
            const auto state = fixture.world.snapshot(), simulation = fixture.world.simulationCheckpoint();
            check(!fixture.service.prepareAndPublish(fixture.progress, fixture.world, isolated) &&
                  fixture.progress.state == before && fixture.world.randomStreams().snapshot() == rng &&
                  fixture.world.snapshot() == state && fixture.world.simulationCheckpoint() == simulation && fixture.service.blocked(fixture.progress),
                "Source/decoder/item/XP/RNG rejection retains the whole pending batch, live attributes, receipt/drop ledgers and random streams");
            isolated.monsters[monster] = std::move(savedMob);
            if(fault=="missing-mob") {
                check(fixture.service.prepareAndPublish(fixture.progress,fixture.world,isolated),
                    "Restoring the exact missing MOB source retries the saved same batch successfully");
                Fixture clean(pvf,assets,isolated);clean.kills();check(clean.observe(),"Clean comparison captures identical source deaths");
                CharacterStore reference(testDirectory("clean-reference"),"pending-reward-reference");character(reference);
                check(clean.checkpoint(reference) && clean.service.prepareAndPublish(clean.progress,clean.world,isolated) &&
                      clean.progress.state==fixture.progress.state && clean.world.randomStreams().snapshot()==fixture.world.randomStreams().snapshot(),
                    "Source-corrected retry produces exactly the clean first-attempt rewards, traces and RNG without reroll");
                reference.close();
            }
            store.close();
        }
    }
    {
        Fixture fixture(pvf, assets, catalog, true); fixture.kills(); check(fixture.observe(), "World preflight fixture captures source deaths");
        const auto *avatar = fixture.progress.item(39180);
        check(avatar != nullptr, "World preflight uses actual unsupported limited-period avatar39180");
        const int uid = fixture.progress.state.at("next_uid").get<int>();
        fixture.progress.state["inventory"].push_back({{"uid",uid},{"id",39180},{"count",1},{"durability",avatar->durability}});
        fixture.progress.state["equipped"][avatar->slot] = uid; fixture.progress.state["next_uid"] = uid+1;
        CharacterStore store(testDirectory("world-preflight"), "pending-reward-preflight"); character(store);
        check(fixture.checkpoint(store), "World preflight input is durably captured before candidate preparation");
        const auto before = fixture.progress.state, rng = fixture.world.randomStreams().snapshot(), world = fixture.world.snapshot();
        check(!fixture.service.prepareAndPublish(fixture.progress, fixture.world, catalog) && fixture.progress.state == before &&
              fixture.world.randomStreams().snapshot() == rng && fixture.world.snapshot() == world,
            "Growth/equipment preflight failure rolls back all candidate kill/clear rewards and Loot draws");
        fixture.progress.state["equipped"].erase(avatar->slot);
        check(fixture.checkpoint(store) && fixture.service.prepareAndPublish(fixture.progress, fixture.world, catalog),
            "Correcting the actual equipment source precondition retries retained events once");
        store.close();
    }
    {
        for (auto point : {SaveFailurePoint::BeforeWrite, SaveFailurePoint::AfterWrite, SaveFailurePoint::AfterFlush,
                           SaveFailurePoint::AfterValidation, SaveFailurePoint::AfterBackup, SaveFailurePoint::BeforePublish,
                           SaveFailurePoint::AfterPublish}) {
            Fixture fixture(pvf, assets, catalog);
            const auto directory = testDirectory("save-fault");
            CharacterStore store(directory, "pending-reward-save"); character(store);
            check(fixture.checkpoint(store), "Fault matrix establishes an intact prior committed generation");
            fixture.kills(); check(fixture.observe(), "Fault matrix freezes pending deaths");
            fixture.capture(store); const auto expectedPending = fixture.progress.state;
            const auto oldRng = fixture.world.randomStreams().snapshot();
            const auto generation = store.generation();
            store.setFailureInjector([point](SaveFailurePoint at) { if(at==point) throw std::runtime_error("Injected intent write failure"); });
            check(rejects([&] { store.checkpoint(); }) && store.hasPendingCommit() && store.generation() == generation &&
                  fixture.service.needsCheckpoint() && !fixture.service.prepareAndPublish(fixture.progress, fixture.world, catalog) &&
                  fixture.progress.state == expectedPending && fixture.world.randomStreams().snapshot() == oldRng,
                "Every disk boundary rejects reward preparation while retaining the exact pending input generation");
            check(!fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,store,0)&&fixture.service.needsCheckpoint(),
                "An in-memory candidate with the old durable generation cannot impersonate a successful checkpoint");
            store.setFailureInjector({}); store.retryPending();
            check(store.generation() == generation+1 && fixture.service.acknowledgeCheckpoint(fixture.progress, fixture.world,store,0),
                "Retry acknowledges the frozen same-generation intent, including already-published disk candidate");
            check(fixture.service.prepareAndPublish(fixture.progress, fixture.world, catalog), "Pending batch prepares after exact intent retry");
            fixture.capture(store); const auto final = fixture.progress.state, finalRng = fixture.world.randomStreams().snapshot();
            const auto finalGeneration = store.generation();
            store.setFailureInjector([point](SaveFailurePoint at) { if(at==point) throw std::runtime_error("Injected final write failure"); });
            check(rejects([&] { store.checkpoint(); }) && store.hasPendingCommit() && fixture.service.blocked(fixture.progress) &&
                  !fixture.service.clearReceipt(fixture.progress, fixture.session),
                "Every final write boundary retains prepared receipt/drop/RNG and keeps Results and transitions blocked");
            store.setFailureInjector({}); store.retryPending();
            check(store.generation() == finalGeneration+1 && fixture.service.acknowledgeCheckpoint(fixture.progress, fixture.world,store,0) && fixture.service.clearReceipt(fixture.progress, fixture.session),
                "Final retry publishes the frozen output generation without executing reward logic a second time");
            store.close();
            CharacterStore reopened(directory, "pending-reward-save"); Progression restored(catalog); World resumed(pvf,assets);
            reopened.apply(0,resumed,restored);
            PendingRewardService service; service.characterBoundary(resumed);
            check(restored.state == final && resumed.randomStreams().snapshot() == finalRng &&
                  !service.hasPending(restored) && service.acknowledgeCheckpoint(restored,resumed,reopened,0),
                "Reload sees complete final reward ledgers and exactly matching Loot generation");
            reopened.close();
        }
    }
    {
        // Crash after durable intent, before any reward publication. World does
        // not serialize historical events; pending must be sufficient alone.
        Fixture fixture(pvf,assets,catalog); fixture.kills(); check(fixture.observe(), "Reload fixture captures actual deaths");
        const auto run = fixture.session.run.token;
        const auto directory = testDirectory("intent-reload");
        fixture.progress.state["pending_rewards"]["future_namespace"] = {{"kept",91}};
        auto &row = fixture.progress.state["pending_rewards"]["kills"].begin().value(); row["future_row"] = Json::array({2,1,2});
        fixture.progress.state["drops"]["historical-unclaimed"] = {{"gold",7},{"items",Json::array()},{"claimed",false},{"future_drop",13}};
        const auto historical = fixture.progress.state.at("drops").at("historical-unclaimed");
        TownAccessCatalog towns(pvf);
        const auto home=towns.location(towns.require(1,1));
        CharacterStore store(directory,"pending-reward-reload");character(store);check(fixture.checkpoint(store), "Pending input and unknown fields persist");
        auto &savedRegion=store.data["characters"][0]["region_session"];
        towns.attachState(savedRegion,home,home);savedRegion["login_town"]=home.json();store.checkpoint();store.close();
        CharacterStore reopened(directory,"pending-reward-reload");Progression progress(catalog);World world(pvf,assets);
        reopened.apply(0,world,progress);
        PendingRewardService service;service.characterBoundary(world);
        check(world.events.empty() && service.hasPending(progress), "No killed event replay is required after process restart");
        // Follow main's policy: source Seria entry replaces active dungeon; the
        // pending origins independently retain its old run provenance.
        CharacterEntryService entryService(pvf,assets,catalog,towns);
        const auto saved = reopened.data.at("characters").at(0).at("region_session");
        auto entry = entryService.prepare(world,saved);Scene scene;
        publishCharacterEntry(world,scene,std::move(entry));RegionSession town;
        reopened.capture(0,world,progress);reopened.data["characters"][0]["region_session"] = town.save(world,"town");reopened.checkpoint();
        check(!world.combat && world.monsters.empty() && !town.active() &&
              progress.state.at("pending_rewards").at("origins").contains(run) &&
              service.acknowledgeCheckpoint(progress,world,reopened,0),
            "Login publishes Seria town while retaining durable old-run pending provenance and random streams");
        auto missing = catalog.monsters.extract(fixture.world.monsters.back().sourceId);
        const auto pending = progress.state, rng = world.randomStreams().snapshot();
        check(!service.prepareAndPublish(progress,world,catalog) && service.blocked(progress) && progress.state == pending &&
              world.randomStreams().snapshot() == rng && !world.combat,
            "Source failure allows diagnostic Seria login with old intent intact and new-run/settlement gate blocked");
        catalog.monsters.insert(std::move(missing));
        check(service.prepareAndPublish(progress,world,catalog) && progress.state.at("drops").at("historical-unclaimed") == historical &&
              progress.state.at("pending_rewards").at("future_namespace").at("kept") == 91 &&
              progress.state.at("pending_rewards").at("completed_kills").begin().value().at("future_row") == Json::array({2,1,2}),
            "Same-source retry preserves prior drop ledgers and unknown nested fields in completed intent archive");
        reopened.capture(0,world,progress);reopened.data["characters"][0]["region_session"] = town.save(world,"town");reopened.checkpoint();
        check(service.acknowledgeCheckpoint(progress,world,reopened,0) &&
              !service.blocked(progress) && progress.state.at("drops").at("historical-unclaimed").at("claimed") == false,
            "Recovered old-run ground drops stay unclaimed in the normal ledger; no auto-inventory or new recovery UI is introduced");
        reopened.close();
    }
    {
        Fixture fixture(pvf,assets,catalog);fixture.kills();check(fixture.observe(), "Duplicate/conflict fixture captures deaths");
        CharacterStore store(testDirectory("duplicates"),"pending-reward-duplicate");character(store);
        check(fixture.checkpoint(store), "Duplicate fixture pending is durable");
        const auto captured = fixture.progress.state.at("pending_rewards");
        check(fixture.service.prepareAndPublish(fixture.progress,fixture.world,catalog) && fixture.checkpoint(store), "Duplicate fixture completes once");
        const auto receipts = fixture.progress.state.at("events"), drops = fixture.progress.state.at("drops"), rng = fixture.world.randomStreams().snapshot();
        // Reintroduced intent with already-committed receipts must validate all
        // provenance and remove only the pending rows, without a second draw.
        fixture.progress.state["pending_rewards"]["kills"] = captured.at("kills");
        fixture.progress.state["pending_rewards"]["clears"] = captured.at("clears");
        check(fixture.checkpoint(store) && fixture.service.prepareAndPublish(fixture.progress,fixture.world,catalog) &&
              fixture.progress.state.at("events") == receipts && fixture.progress.state.at("drops") == drops && fixture.world.randomStreams().snapshot() == rng,
            "Duplicate intent validates matching event, drop, claim and clear receipt without rerolling");
        check(fixture.checkpoint(store), "Duplicate completion archive is durable");
        fixture.progress.state["pending_rewards"]["kills"] = captured.at("kills");
        const auto key = captured.at("kills").begin().key();fixture.progress.state["events"][key]["monster"] = INT_MAX;
        check(fixture.checkpoint(store), "Conflicting duplicate fixture is durably preserved for diagnosis");
        const auto before = fixture.progress.state;
        check(!fixture.service.prepareAndPublish(fixture.progress,fixture.world,catalog) && fixture.progress.state == before &&
              fixture.world.randomStreams().snapshot() == rng,
            "Conflicting duplicate receipt blocks without clearing pending facts or granting compensation rewards");
        store.close();
    }
    {
        Fixture fixture(pvf,assets,catalog);fixture.kills();check(fixture.observe(), "Malformed namespace fixture captures deaths");
        fixture.progress.state["pending_rewards"]["kills"] = Json::array();
        const auto before = fixture.progress.state, rng = fixture.world.randomStreams().snapshot();
        check(fixture.service.blocked(fixture.progress) && !fixture.observe() &&
              !fixture.service.prepareAndPublish(fixture.progress,fixture.world,catalog) && fixture.progress.state == before &&
              fixture.world.randomStreams().snapshot() == rng,
            "Malformed persistent namespace remains byte-preserved and blocks capture, rewards and business instead of silent reset");
    }
    {
        Fixture fixture(pvf,assets,catalog);fixture.kills();
        const auto lost=fixture.world.monsters.back().id;fixture.world.monsters.pop_back();fixture.session.remember(fixture.world);
        check(fixture.observe(),"A killed actor missing at capture is retained as a raw persistent intent instead of skipped");
        const auto key=killKey(fixture.session,lost);
        check(fixture.progress.state.at("pending_rewards").at("kills").at(key).at("actor_matches")==0,
            "Missing actor capture records explicit zero matches while preserving the original event/source identity");
        CharacterStore store(testDirectory("missing-actor"),"pending-reward-actor");character(store);
        check(fixture.checkpoint(store),"Missing actor intent can be durably preserved for controlled exit and diagnosis");
        const auto before=fixture.progress.state,rng=fixture.world.randomStreams().snapshot();
        check(!fixture.service.prepareAndPublish(fixture.progress,fixture.world,catalog)&&fixture.progress.state==before&&
              fixture.world.randomStreams().snapshot()==rng,
            "Missing actor provenance blocks the complete batch without losing earlier kills or drawing Loot");
        store.close();
    }
    {
        Fixture fixture(pvf,assets,catalog);
        const auto directory=testDirectory("beta-isolation");
        CharacterStore normal(directory/"normal","pending-reward-beta");character(normal);
        for(int i=0;i<10;++i)check(fixture.checkpoint(normal),"Beta isolation advances the real normal writer before forking");
        TownAccessCatalog towns(pvf);const auto home=towns.location(towns.require(1,1));
        auto &normalRegion=normal.data["characters"][0]["region_session"];
        towns.attachState(normalRegion,home,home);normalRegion["login_town"]=home.json();normal.checkpoint();
        check(fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,normal,0),
            "Normal return anchor and source Seria login room are durably recorded before beta isolation");
        const auto normalGeneration=normal.generation();
        const auto committed=normal.committedSnapshot(), normalProgress=fixture.progress.state;
        const auto normalRandom=fixture.world.randomStreams().snapshot();
        fixture.progress.state["uncommitted_writer_proof"]=71;fixture.capture(normal);
        check(normal.committedSnapshot()==committed&&normal.data!=committed&&
              !fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,normal,0)&&
              fixture.service.durableGeneration()==normalGeneration,
            "Mutable character data at the same generation cannot impersonate the actual committed snapshot");
        fixture.progress.state=normalProgress;normal.data=committed;
        BetaSaveBranch branch;branch.fork(normal,directory/"beta",{{"run_id","reward-isolation"}});
        auto &writer=branch.select(normal);
        check(normal.generation()==normalGeneration+1&&writer.generation()==1&&writer.generation()<normal.generation(),
            "Real fork legitimately checkpoints normal once and starts its independent beta writer at generation one");
        // The fork itself checkpoints normal. Isolation starts after this
        // authorized normal boundary, rather than comparing a pre-fork file.
        const auto normalBytes=readFile(directory/"normal/characters.json");
        const auto normalData=normal.data;
        check(!fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,writer,0)&&
              fixture.service.durableGeneration()==normalGeneration&&
              fixture.service.switchCheckpointWriter(fixture.progress,fixture.world,writer,0)&&
              fixture.service.durableGeneration()==1,
            "An unrelated lower-generation writer requires explicit clean handover instead of weakening same-writer checks");
        fixture.kills();check(fixture.observe(),"Beta fork captures actual pending deaths");
        const auto pending=fixture.progress.state, rng=fixture.world.randomStreams().snapshot();
        const auto cursor=fixture.service.eventCursor();
        check(!fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,writer,0)&&
              !fixture.service.switchCheckpointWriter(fixture.progress,fixture.world,normal,0)&&
              !fixture.service.releaseCheckpointWriter(fixture.progress,writer,0)&&
              fixture.service.needsCheckpoint()&&fixture.service.hasPending(fixture.progress)&&
              fixture.service.durableGeneration()==1&&fixture.service.eventCursor()==cursor&&
              fixture.progress.state==pending&&fixture.world.randomStreams().snapshot()==rng,
            "Dirty same-writer generation, pending handover and release are rejected without losing intent, cursor or RNG");
        check(fixture.checkpoint(writer)&&fixture.service.prepareAndPublish(fixture.progress,fixture.world,catalog)&&fixture.checkpoint(writer)&&
              writer.generation()==3&&fixture.service.durableGeneration()==3&&
              readFile(directory/"normal/characters.json")==normalBytes&&normal.data==normalData,
            "Beta intent and final publish in exactly two saves without generation catch-up or any normal reward writes");
        check(!fixture.service.releaseCheckpointWriter(fixture.progress,normal,0)&&
              fixture.service.releaseCheckpointWriter(fixture.progress,writer,0)&&fixture.service.durableGeneration()==0,
            "Only the bound clean beta writer can be explicitly released before branch close");
        branch.close();
        CharacterEntryService entryService(pvf,assets,catalog,towns);
        auto entry=entryService.prepare(fixture.world,normal.data.at("characters").at(0).at("region_session"));
        normal.apply(0,fixture.world,fixture.progress);fixture.service.characterBoundary(fixture.world);
        fixture.session=RegionSession{};Scene scene;publishCharacterEntry(fixture.world,scene,std::move(entry));
        fixture.capture(normal,true);
        auto &returnedRegion=normal.data["characters"][0]["region_session"];
        towns.attachState(returnedRegion,home,home);returnedRegion["login_town"]=home.json();normal.checkpoint();
        check(fixture.progress.state==normalProgress&&fixture.world.randomStreams().snapshot()==normalRandom&&
              !fixture.world.combat&&fixture.world.monsters.empty()&&
              fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,normal,0)&&
              fixture.service.durableGeneration()==normal.generation()&&
              !normal.data.contains("beta_branch"),
            "Normal apply, character boundary and source Seria publication restore normal ledgers/RNG without beta actors before rebinding");
        branch.fork(normal,directory/"beta-second",{{"run_id","reward-isolation-second"}});
        auto &second=branch.select(normal);
        const auto secondNormalBytes=readFile(directory/"normal/characters.json");
        const auto secondNormalData=normal.data;
        check(second.generation()==1&&fixture.service.switchCheckpointWriter(fixture.progress,fixture.world,second,0)&&
              fixture.service.durableGeneration()==1&&fixture.checkpoint(second,true)&&second.generation()==2&&
              readFile(directory/"normal/characters.json")==secondNormalBytes&&normal.data==secondNormalData&&
              fixture.service.releaseCheckpointWriter(fixture.progress,second,0),
            "Returning from beta can fork a fresh low-generation branch again without carrying either prior writer counter");
        branch.close();normal.close();
    }
    {
        Fixture fixture(pvf,assets,catalog);
        const auto directory=testDirectory("beta-fork-failure");
        CharacterStore normal(directory/"normal","pending-reward-beta-failure");character(normal);
        check(fixture.checkpoint(normal),"Fork failure fixture starts with an actual committed normal writer");
        const auto before=normal.committedSnapshot();const auto generation=normal.generation();
        BetaSaveBranch branch;
        normal.setFailureInjector([](SaveFailurePoint at){if(at==SaveFailurePoint::BeforeWrite)throw std::runtime_error("Injected normal fork checkpoint failure");});
        check(rejects([&]{branch.fork(normal,directory/"normal-save-failed",Json::object());})&&
              !branch.active()&&normal.hasPendingCommit()&&normal.committedSnapshot()==before&&normal.generation()==generation&&
              !fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,normal,0)&&
              !fs::exists(directory/"normal-save-failed"),
            "Fork's own normal checkpoint failure preserves the exact pending root and publishes no beta writer");
        normal.setFailureInjector({});normal.retryPending();
        check(fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,normal,0)&&normal.generation()==generation+1,
            "Normal fork checkpoint retries its retained candidate before any later test handover");
        {
            std::ofstream blocker(directory/"not-a-directory",std::ios::binary);
            blocker<<"preserve failed fork evidence";
            if(!blocker)throw std::runtime_error("Cannot create isolated fork filesystem fault fixture");
        }
        const auto blockedPath=directory/"not-a-directory"/"beta";
        const auto blockedBytes=readFile(directory/"not-a-directory");
        check(rejects([&]{branch.fork(normal,blockedPath,Json::object());})&&!branch.active()&&
              !normal.hasPendingCommit()&&readFile(directory/"not-a-directory")==blockedBytes&&
              fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,normal,0),
            "Fork filesystem initialization failure keeps normal readable and bound while preserving failed-path evidence");
        branch.fork(normal,directory/"published-handover-failed",Json::object());
        const auto normalRoot=normal.committedSnapshot(), liveProgress=fixture.progress.state;
        const auto betaBytes=readFile(directory/"published-handover-failed/characters.json");
        fixture.progress.state["uncommitted_handover_proof"]=13;
        check(!fixture.service.switchCheckpointWriter(fixture.progress,fixture.world,branch.select(normal),0),
            "Published beta handover rejects a live snapshot that its durable target never committed");
        // Same cleanup as main's catch: never delete the branch files and
        // never discard/reload a normal root merely because handover failed.
        if(branch.active())branch.close();
        fixture.progress.state=liveProgress;
        check(!branch.active()&&normal.committedSnapshot()==normalRoot&&
              fixture.service.acknowledgeCheckpoint(fixture.progress,fixture.world,normal,0)&&
              readFile(directory/"published-handover-failed/characters.json")==betaBytes,
            "Failed handover closes only the published beta writer, retains normal binding and preserves both roots");
        CharacterStore evidence(directory/"published-handover-failed","pending-reward-beta-failure");
        check(evidence.generation()==1,"Failed handover releases beta's writer lock so its preserved checkpoint remains inspectable");
        evidence.close();
        branch.fork(normal,directory/"fresh-retry",Json::object());
        check(fixture.service.switchCheckpointWriter(fixture.progress,fixture.world,branch.select(normal),0)&&
              fixture.service.durableGeneration()==1&&fixture.service.releaseCheckpointWriter(fixture.progress,branch.select(normal),0),
            "A later fresh-directory retry performs explicit writer handover without deleting failed attempts");
        branch.close();normal.close();
    }
    {
        // Actual producer regression: both direct remember and const save's
        // private remember copy must reject the old all_of(empty)==true boss.
        Fixture fixture(pvf,assets,catalog);fixture.world.monsters.clear();
        fixture.session.remember(fixture.world);
        const auto snapshot = fixture.session.save(fixture.world,"dungeon");
        check(!fixture.session.run.room().cleared && !fixture.session.run.complete() &&
              snapshot.at("run").at("rooms").at(fixture.session.run.boss).at("cleared") == false,
            "Empty boss does not clear through either RegionSession::remember or RegionSession::save");
        check(fixture.observe() && !fixture.progress.state.contains("pending_rewards") &&
              fixture.progress.state.at("clears").empty(),
            "Empty boss capture produces no clear intent or reward and retains missing-entity diagnostic boundary");
        fixture.session.run.current = fixture.session.run.start;fixture.session.remember(fixture.world);
        check(fixture.session.run.room().cleared,
            "Prepared source ordinary empty corridor retains existing transit behavior; failed scene preparation must never publish it");
    }
    {
        Json expected;
        for (const int hz : {30,60,144,240}) for (const size_t budget : {size_t(1),size_t(8)}) {
            Fixture fixture(pvf,assets,catalog);
            fixture.world.setObjectTick([&](World &world) {
                if(world.tick==2)world.diagnosticHit(1,1,0,0,1,{});
                if(world.tick==4)for(size_t i=1;i<world.monsters.size();++i)world.diagnosticHit(int(i+1),1,0,0,1,{});
            });
            // Stop at exactly eight completed ticks with identical zero debt;
            // the number of render pumps changes, not the simulation contract.
            int64_t submitted=0;
            const int64_t total=133333334;
            while(submitted<total) {
                const auto delta=std::min<int64_t>(1000000000/hz,total-submitted);
                fixture.world.advance(delta,budget);submitted+=delta;
            }
            while(fixture.world.pendingTicks())fixture.world.advance(0,budget);
            fixture.session.remember(fixture.world);check(fixture.observe(), "Cadence fixture captures exact fixed-tick batch");
            CharacterStore store(testDirectory("cadence"),"pending-reward-cadence");character(store);
            check(fixture.checkpoint(store) && fixture.service.prepareAndPublish(fixture.progress,fixture.world,catalog) && fixture.checkpoint(store),
                "Cadence fixture publishes complete same-generation reward output");
            Json actual={{"progression",fixture.progress.state},{"random",fixture.world.randomStreams().snapshot()},
                         {"clock",fixture.world.simulationCheckpoint().at("clock")}};
            if(expected.is_null())expected=actual;
            check(actual==expected,"30/60/144/240 Hz and bounded catch-up budgets produce identical pending order, reward ledgers, Loot streams and clock");
            store.close();
        }
        samples["cadence"] = expected;
    }
    return {{"status","passed"},{"checks",checks},{"check_count",checks.size()},{"samples",samples},
        {"scope","Production World/Progression/RegionSession/CharacterStore consumers and isolated fault saves; diagnostic lethal hits are not normal input or complete-DGN acceptance"},
        {"old_drop_pickup_after_seria_login","unimplemented separate boundary; ledger preserved, no auto-claim"}};
}
} // namespace dnf
