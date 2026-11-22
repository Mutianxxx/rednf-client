#include "dnf/simulation.hpp"
#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/session.hpp"
#include "dnf/storage.hpp"
#include "dnf/local_pause_clock.hpp"
#include <chrono>
#include <cmath>
#include <functional>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
struct SimulationChecks {
    Json items = Json::array();
    void operator()(bool passed, const char *message) {
        if (!passed) throw std::runtime_error(std::string("Simulation: ") + message);
        items.push_back(message);
    }
    template <class Action> bool rejects(Action action) {
        try { action(); } catch (const std::exception &) { return true; }
        return false;
    }
    Json report(const char *scope) const {
        return {{"status", "pass"}, {"check_count", items.size()}, {"checks", items}, {"scope", scope},
                {"classification", "beta reconstruction; native movement arithmetic is outside this scheduler"}};
    }
};
}

Json runSimulationTests() {
    SimulationChecks check;
    {
        LocalPauseClock clock;
        check(LocalPauseClock::ticksForMilliseconds(0) == 0 &&
              LocalPauseClock::ticksForMilliseconds(-1) == 0 &&
              LocalPauseClock::ticksForMilliseconds(std::numeric_limits<double>::infinity()) == 0 &&
              LocalPauseClock::ticksForMilliseconds(16.0) == 1 &&
              LocalPauseClock::ticksForMilliseconds(17.0) == 2,
              "Local pause clock converts authored milliseconds to the existing 60Hz tick contract");
        clock.setCountdown(50.0);
        check(clock.frozen() && clock.remainingTicks() == 3 && clock.advance() &&
              clock.remainingTicks() == 2 && clock.advance() && clock.remainingTicks() == 1 &&
              clock.advance() && clock.remainingTicks() == 0 && clock.frozen() &&
              !clock.advance() && !clock.frozen(),
              "Local pause clock preserves the final frozen tick and resumes on the next fixed tick");
        clock.setCountdown(100.0);
        clock.setCountdown(10.0);
        check(clock.remainingTicks() == 6,
              "A shorter repeated hit pause does not shorten the existing local freeze");
        clock.restore(2, true);
        check(clock.advance() && clock.remainingTicks() == 1,
              "Restored actor-local pause resumes from the saved remaining ticks");
        clock.advance(true);
        check(!clock.frozen() && clock.remainingTicks() == 0,
              "Death clears the actor-local pause clock");
    }
    std::vector<uint64_t> reference;
    for (const int fps : {30, 60, 120, 144, 240}) {
        FixedStepClock clock;
        std::vector<uint64_t> observed;
        bool deltas = true;
        int64_t before = 0;
        for (int frame = 1; frame <= fps * 10; ++frame) {
            const int64_t boundary = int64_t(frame) * 1000000000 / fps;
            clock.addNanoseconds(boundary - before);
            before = boundary;
            while (auto step = clock.popTick()) {
                observed.push_back(step->milliseconds);
                deltas &= step->deltaMilliseconds == (step->tick % 3 == 1 ? 16 : 17);
            }
        }
        if (reference.empty()) reference = observed;
        check(observed == reference && clock.tick() == 600 && clock.milliseconds() == 10000 &&
              clock.accumulatedUnits() == 0 && deltas,
              "30/60/120/144/240 Hz renders preserve all 600 integer tick times and 16/17 ms deltas");
    }
    {
        FixedStepClock clock;
        clock.addNanoseconds(3000000001);
        bool eightTicks = true;
        for (int i = 0; i < 8; ++i) eightTicks &= bool(clock.popTick());
        check(eightTicks, "An eight-tick pump consumes eight actual ticks");
        check(clock.tick() == 8 && clock.pendingTicks() == 172 && std::abs(clock.alpha() - .00000006) < 1e-14,
              "Budgeted catch-up retains every unprocessed tick and the sub-tick remainder");
        FixedStepClock restored;
        restored.restore(Json::parse(clock.snapshot().dump()));
        bool matched = true;
        while (auto step = clock.popTick()) {
            const auto resumed = restored.popTick();
            matched &= resumed && step->tick == resumed->tick && step->milliseconds == resumed->milliseconds &&
                       step->deltaMilliseconds == resumed->deltaMilliseconds;
        }
        check(matched, "Restored catch-up follows the exact saved tick and millisecond sequence");
        check(restored.snapshot() == clock.snapshot() && clock.tick() == 180,
              "The complete three-second backlog drains without discarding time");
        const auto before = clock.snapshot();
        check(check.rejects([&] { clock.addNanoseconds(-1); }) && clock.snapshot() == before,
              "Negative elapsed time is rejected before clock mutation");
        check(check.rejects([&] { clock.addNanoseconds(INT64_MAX); }) && clock.snapshot() == before,
              "Accumulator multiplication overflow is rejected before clock mutation");
        auto corrupt = before; corrupt["frequency"] = 59;
        check(check.rejects([&] { clock.restore(corrupt); }) && clock.snapshot() == before,
              "A mismatched scheduler frequency cannot partially restore the clock");
        corrupt = before; corrupt["tick"] = UINT64_MAX;
        check(check.rejects([&] { clock.restore(corrupt); }) && clock.snapshot() == before,
              "A persisted tick whose millisecond conversion overflows is rejected");
    }
    check(FixedStepClock::targetTickForNanoseconds(0) == 0 &&
          FixedStepClock::targetTickForNanoseconds(16666666) == 1 &&
          FixedStepClock::targetTickForNanoseconds(16666667) == 2 &&
          FixedStepClock::targetTickForNanoseconds(INT64_MAX) == UINT64_C(553402322212),
          "Input target ticks match the old inclusive nanosecond boundary without multiplying large timestamps");
    {
        SimulationIdSources ids;
        check(ids.actions.next() == 1 && ids.attacks.next() == 1 && ids.requests.next() == 1 && ids.events.next() == 1,
              "Independent ID domains start at one");
        ids.actions.reserveThrough(900);
        SimulationIdSources copy; copy.restore(Json::parse(ids.snapshot().dump()));
        check(copy.actions.next() == 901 && copy.attacks.next() == 2 && copy.events.next() == 2,
              "Reload and explicit legacy reservation cannot reissue old action/attack/event IDs");
        MonotonicIds last(UINT64_MAX);
        check(last.next() == UINT64_MAX && last.nextValue() == 0 && check.rejects([&] { last.next(); }),
              "Maximum uint64 identity exhausts instead of wrapping to a duplicate");
        MonotonicIds exhausted; exhausted.restore(last.snapshot());
        check(check.rejects([&] { exhausted.next(); }), "Identity exhaustion survives serialization");
    }
    {
        MonotonicIds ids(7);
        ids.merge(MonotonicIds(20));
        check(ids.next() == 20, "Forward watermark merge skips every identity already allocated by the other source");
        ids.merge(MonotonicIds(3)); ids.merge(MonotonicIds(21));
        check(ids.next() == 21, "Backward and equal watermark merges cannot reissue a previously allocated identity");
        ids.merge(MonotonicIds(90).snapshot());
        check(ids.next() == 90, "A serialized next-ID watermark merges with the same allocation semantics");
        const auto before = ids.snapshot();
        for (const auto &bad : std::vector<Json>{Json{{"schema",2},{"next",100}}, Json{{"schema",1},{"next",-1}},
                Json{{"schema",1},{"next",1.5}}, Json{{"schema",1},{"next",true}}, Json{{"schema",1}}})
            check(check.rejects([&] { ids.merge(bad); }) && ids.snapshot() == before,
                  "Invalid serialized watermark merge rejects before changing live allocation history");
        ids.merge(MonotonicIds(UINT64_MAX));
        check(ids.nextValue() == UINT64_MAX && ids.next() == UINT64_MAX && ids.nextValue() == 0,
              "Merging UINT64_MAX leaves exactly its final identity available before permanent exhaustion");
        ids.merge(MonotonicIds(1)); ids.merge(MonotonicIds(UINT64_MAX).snapshot());
        check(ids.nextValue() == 0 && check.rejects([&] { ids.next(); }),
              "An exhausted local source cannot be revived by either an earlier or a maximum remote watermark");
        MonotonicIds remoteExhausted(50); remoteExhausted.merge(MonotonicIds(0));
        check(remoteExhausted.nextValue() == 0 && check.rejects([&] { remoteExhausted.next(); }),
              "Merging an exhausted remote source permanently exhausts a still-available local source");
    }
    {
        EntityRegistry registry;
        const auto first = registry.create(), second = registry.create();
        const auto renewed = registry.renew(first);
        check(!registry.valid(first) && registry.valid(renewed) && renewed.id == first.id && renewed.generation == 2,
              "Renewing an entity invalidates an old generation without changing its instance identity");
        check(!registry.retire(first) && registry.valid(renewed), "A stale destroy request cannot retire the new generation");
        EntityRegistry copy; copy.restore(Json::parse(registry.snapshot().dump()));
        check(copy.active() == std::vector<EntityHandle>{renewed, second} && copy.create().id > second.id,
              "Registry restore retains stable identity order and its allocation watermark");
        registry.retireAll();
        check(!registry.valid(renewed) && !registry.valid(second) && registry.create().id > second.id,
              "Scene retirement invalidates all handles and never recycles instance IDs");
        const auto before = copy.snapshot();
        auto corrupt = before; corrupt["entries"].push_back(corrupt["entries"][0]);
        check(check.rejects([&] { copy.restore(corrupt); }) && copy.snapshot() == before,
              "Duplicate persisted entity identities reject the whole registry checkpoint");
        check(EntityHandle::fromJson(EntityHandle{}.json()) == EntityHandle{} &&
              check.rejects([&] { EntityHandle::fromJson({{"id", 1}, {"generation", 0}}); }),
              "Only the complete zero handle is an accepted null handle");
    }
    {
        EntityRegistry live;
        const auto original = live.create();
        const auto saved = live.snapshot();
        std::vector<EntityHandle> retired{original};
        bool distinct = true, stale = true, sourceUntouched = true;
        uint64_t previous = original.id;
        // Reuse the identical old checkpoint, as repeated room/character
        // recovery does. The private candidate merges the current allocator
        // before cancelling saved incarnations and allocating its new actor.
        for (int recovery = 0; recovery < 4; ++recovery) {
            const auto liveBefore = live.snapshot();
            EntityRegistry candidate; candidate.restore(saved);
            const auto savedEntries = candidate.snapshot().at("entries");
            candidate.mergeAllocationWatermark(live);
            sourceUntouched &= live.snapshot() == liveBefore && candidate.snapshot().at("entries") == savedEntries;
            candidate.retireAll();
            const auto next = candidate.create();
            distinct &= next.id > previous && next.generation == 1 && candidate.valid(next);
            for (const auto old : retired) stale &= !candidate.valid(old);
            live = std::move(candidate);previous = next.id;retired.push_back(next);
        }
        check(distinct && stale && live.active().size() == 1,
              "Repeated restoration of the same registry checkpoint never revives any previous actor handle");
        check(sourceUntouched, "Allocator merge changes neither the live source registry nor the candidate's saved entry generations and flags");
        EntityRegistry lower; lower.restore(saved);
        const auto beforeBackward = live.snapshot();live.mergeAllocationWatermark(lower);
        check(live.snapshot() == beforeBackward,
              "A backward registry allocator merge preserves all current entries and the larger live watermark");
        EntityRegistry high;
        auto highState = high.snapshot();highState["ids"] = MonotonicIds(100).snapshot();high.restore(highState);
        const auto existingEntries = live.snapshot().at("entries");live.mergeAllocationWatermark(high);
        check(live.snapshot().at("entries") == existingEntries && live.create().id == 100,
              "A forward registry allocator merge advances allocation without importing the other registry's entities");
        EntityRegistry exhausted;
        auto exhaustedState = exhausted.snapshot();exhaustedState["ids"] = MonotonicIds(0).snapshot();exhausted.restore(exhaustedState);
        live.mergeAllocationWatermark(exhausted);const auto exhaustedBefore = live.snapshot();
        live.mergeAllocationWatermark(high);
        check(live.snapshot() == exhaustedBefore && check.rejects([&] { live.create(); }) && live.snapshot() == exhaustedBefore,
              "Registry exhaustion survives later available-watermark merges and rejects allocation without changing entries");
        EntityRegistry maximum;
        auto maximumState = maximum.snapshot();maximumState["ids"] = MonotonicIds(UINT64_MAX).snapshot();maximum.restore(maximumState);
        maximum.mergeAllocationWatermark(lower);const auto lastHandle = maximum.create();
        check(lastHandle.id == UINT64_MAX && maximum.valid(lastHandle) && check.rejects([&] { maximum.create(); }),
              "A registry can allocate the maximum uint64 identity once and never wraps back to a retired low handle");
    }
    {
        SequencedCommandQueue<int> queue;
        const auto a = queue.enqueue(3, 30), b = queue.enqueue(1, 10), c = queue.enqueue(3, 31);
        auto encode = [](int value) { return Json(value); };
        auto decode = [](const Json &value) { return value.get<int>(); };
        SequencedCommandQueue<int> restored; restored.restore(Json::parse(queue.snapshot(encode).dump()), decode);
        const auto early = restored.popDue(1);
        const auto sameA = restored.popDue(3), sameB = restored.popDue(3);
        check(early && early->sequence == b && sameA && sameA->sequence == a && sameB && sameB->sequence == c &&
              !restored.popDue(3) && restored.nextSequence() == 4,
              "Pending restore preserves target-tick order and stable acceptance order within a tick");
        restored.clear();
        check(restored.enqueue(4, 40) == 4, "Clearing pending input never resets its persisted sequence watermark");
        SequencedCommandQueue<int> replay;
        replay.appendReplay({a, 3, 30}); replay.appendReplay({b, 1, 10}); replay.appendReplay({c, 3, 31});
        check(replay.snapshot(encode) == queue.snapshot(encode), "Recorded input acceptance order replays the exact queue state");
        const auto before = replay.snapshot(encode);
        check(check.rejects([&] { replay.appendReplay({a, 3, 99}); }) && replay.snapshot(encode) == before,
              "Duplicate or stale replay sequence is rejected without queue mutation");
        auto corrupt = before; corrupt["pending"][0]["sequence"] = 999;
        check(check.rejects([&] { replay.restore(corrupt, decode); }) && replay.snapshot(encode) == before,
              "A pending sequence beyond the saved watermark rejects the complete queue restore");
    }
    {
        Pcg32 random(42, 54);
        std::vector<uint32_t> words;
        for (int i = 0; i < 6; ++i) words.push_back(random.next());
        check(words == std::vector<uint32_t>{0xa15c02b7u, 0x7b47f409u, 0xba1d3330u,
                                            0x83d2f293u, 0xbfa4784bu, 0xcbed606eu},
              "PCG32 standard seed 42 / sequence 54 agrees with the published six-word reference vector");
        Pcg32 copy; copy.restore(Json::parse(random.snapshot().dump()));
        bool equal = true;
        for (int i = 0; i < 100; ++i) equal &= copy.next() == random.next();
        check(equal && copy.snapshot() == random.snapshot(), "PCG32 raw state and draw count resume exactly after JSON serialization");
        Pcg32 rejection(42, 54); rejection.next();
        check(rejection.bounded(0x80000001u) == 974992175u && rejection.draws() == 3,
              "Bounded sampling rejects the known low second word instead of introducing modulo bias");
        Pcg32 full(42, 54);
        check(full.uniformInt32(INT32_MIN, INT32_MAX) == int32_t(int64_t(INT32_MIN) + 0xa15c02b7u),
              "The full signed int32 range uses one unbiased raw 32-bit word");
        const auto before = random.snapshot();
        check(check.rejects([&] { random.bounded(0); }) && check.rejects([&] { random.uniformInt32(1, -1); }) &&
              random.snapshot() == before, "Invalid random ranges do not consume state");
        auto corrupt = before; corrupt["increment"] = 2;
        check(check.rejects([&] { random.restore(corrupt); }) && random.snapshot() == before,
              "An invalid even PCG increment rejects without partially mutating RNG state");
    }
    {
        RandomStreams streams(123), referenceStreams(123);
        auto &known = streams.stream(RandomDomain::Combat, 7);
        std::vector<uint32_t> golden;
        for (int i = 0; i < 4; ++i) golden.push_back(known.next());
        check(golden == std::vector<uint32_t>{2654573759u, 479477666u, 3277469082u, 864194503u},
              "Fixed FNV-1a little-endian derivation has a platform-independent golden stream vector");
        bool equal = true;
        for (int i = 0; i < 1000; ++i) {
            streams.stream(RandomDomain::Audio).bounded(7);
            streams.stream(RandomDomain::Particles, 1).next();
            streams.stream(RandomDomain::Ai, 2).next();
            equal &= streams.stream(RandomDomain::Loot).next() == referenceStreams.stream(RandomDomain::Loot).next();
        }
        check(equal, "Audio, particles and AI consumption cannot change loot randomness");
        RandomStreams copy; copy.restore(Json::parse(streams.snapshot().dump()));
        bool resumed = true;
        for (auto domain : {RandomDomain::WorldGeneration, RandomDomain::Ai, RandomDomain::Combat,
                            RandomDomain::Loot, RandomDomain::Particles, RandomDomain::Audio})
            for (uint64_t instance : {uint64_t(0), uint64_t(1), uint64_t(900)})
                resumed &= streams.stream(domain, instance).next() == copy.stream(domain, instance).next();
        check(resumed && copy.snapshot() == streams.snapshot(),
              "Restored and newly requested named streams derive and advance identically after reload");
        const auto before = copy.snapshot();
        auto corrupt = before; corrupt["streams"].push_back(corrupt["streams"][0]);
        check(check.rejects([&] { copy.restore(corrupt); }) && copy.snapshot() == before,
              "Duplicate random stream identity rejects the entire bank without mutation");
        corrupt = before; corrupt["algorithm"] = "unknown";
        check(check.rejects([&] { copy.restore(corrupt); }) && copy.snapshot() == before,
              "An unsupported persisted RNG algorithm is rejected rather than silently reseeded");
    }
    return check.report("Portable clock/identity/command/RNG checks; frontend and cross-platform binary parity are not exercised");
}

Json runWorldSimulationTests(Pvf &pvf, Assets &assets) {
    SimulationChecks check;
    {
        World reference(pvf, assets), budgeted(pvf, assets);
        reference.freezeAi = budgeted.freezeAi = true;
        for (World *world : {&reference, &budgeted}) {
            world->enqueue({0, 1, true});
            world->enqueue({500000000, 1, false});
        }
        std::vector<uint64_t> callbackTicks;
        budgeted.setObjectTick([&](World &world) { callbackTicks.push_back(uint64_t(world.tick)); });
        reference.advance(1000000000);
        budgeted.advance(1000000000, 8);
        check(budgeted.tick == 8 && budgeted.pendingTicks() == 52 && budgeted.simulationNanoseconds() == 1000000000,
              "World pumps execute at most eight ticks while retaining the full one-second backlog");
        while (budgeted.pendingTicks()) budgeted.advance(0, 8);
        check(budgeted.tick == reference.tick && budgeted.player.x == reference.player.x &&
              budgeted.player.y == reference.player.y && budgeted.nowMs() == 1000 && callbackTicks.size() == 60 &&
              callbackTicks.front() == 1 && callbackTicks.back() == 60,
              "Budgeted World catch-up preserves movement, input release and one ObjectSystem callback per tick");
        check(budgeted.inputs() == reference.inputs() && budgeted.inputs()[0]["sequence"] == 1 &&
              budgeted.inputs()[1]["sequence"] == 2,
              "Real World input records carry stable sequence and normalized target tick fields");
        budgeted.advance(1, 0);
        check(budgeted.simulationNanoseconds() == 1000000001 && budgeted.tick == 60 &&
              std::abs(budgeted.alpha() - .00000006) < 1e-14,
              "The input time base retains a single submitted nanosecond across an unfinished tick");
        budgeted.attackVolumes.push_back(AttackVolume{});
        const auto before = budgeted.simulationCheckpoint();
        check(check.rejects([&] { budgeted.advance(-1); }) && budgeted.attackVolumes.size() == 1 &&
              budgeted.simulationCheckpoint() == before,
              "World rejects invalid elapsed time before clearing attack volumes or changing its clock");
    }
    {
        World world(pvf, assets);
        const auto oldPlayer = world.player.handle;
        check(world.resolveActor(oldPlayer) == &world.player, "A live player handle resolves through the registry");
        Actor monster; monster.id = 77;
        world.monsters.push_back(monster);
        world.synchronizeEntityHandles();
        const auto first = world.monsters[0].handle;
        world.monsters.push_back(world.monsters[0]);
        world.synchronizeEntityHandles();
        const auto second = world.monsters[1].handle;
        check(first != second && world.resolveActor(first) == &world.monsters[0] &&
              world.resolveActor(second) == &world.monsters[1],
              "Copied source actors receive separate live instance handles rather than sharing mutable identity");
        world.monsters.clear();
        check(!world.resolveActor(first) && !world.resolveActor(second),
              "Direct actor vector removal invalidates lookup before the next gameplay request");
        world.changeScene();
        check(!world.resolveActor(oldPlayer) && world.resolveActor(world.player.handle) == &world.player,
              "A scene change invalidates the previous player incarnation");
    }
    {
        World before(pvf, assets);
        before.freezeAi = true;
        before.advance(500000000, 8);
        before.enqueue({1000000000, 1, true}); // Future hold must not replay after load.
        before.normalAttack();
        before.randomStreams().stream(RandomDomain::Loot).next();
        const auto oldPlayer = before.player.handle;
        const auto checkpoint = Json::parse(before.simulationCheckpoint().dump());
        World resumed(pvf, assets);
        resumed.restoreSimulationCheckpoint(checkpoint);
        check(resumed.tick == before.tick && resumed.pendingTicks() == before.pendingTicks() &&
              resumed.randomStreams().snapshot() == before.randomStreams().snapshot() &&
              resumed.simulationNanoseconds() == before.simulationNanoseconds(),
              "World checkpoint restores its exact clock/backlog and named random states");
        check(!resumed.resolveActor(oldPlayer) && resumed.activeSkill() == -1 && resumed.effects.empty(),
              "Declared restore cancellation invalidates transient instance handles and does not recreate an action");
        check(resumed.idSources().attacks.nextValue() == before.idSources().attacks.nextValue() &&
              resumed.idSources().actions.nextValue() == before.idSources().actions.nextValue(),
              "Restoring canceled actions preserves allocation watermarks for later attacks and actions");
        resumed.enqueue({1000000000, 1, false});
        check(resumed.inputs().back()["sequence"] == 2,
              "Saved future keys are canceled while their input sequence watermark survives reload");
        resumed.advance(1500000000);
        check(resumed.player.x == 240 && resumed.player.y == 260,
              "A canceled future Down edge cannot cause phantom movement after restoration");
        const auto valid = resumed.simulationCheckpoint();
        auto invalid = valid; invalid["random"]["algorithm"] = "corrupt";
        check(check.rejects([&] { resumed.restoreSimulationCheckpoint(invalid); }) &&
              resumed.simulationCheckpoint() == valid,
              "Malformed checkpoint validation leaves the live World unchanged");
        resumed.tick = std::numeric_limits<int64_t>::max() / 1000;
        check(check.rejects([&] { resumed.simulationNanoseconds(); }),
              "Nanosecond timestamp overflow is checked before resuming an SDL input time base");
    }
    {
        auto simulate = [&](int fps) {
            World world(pvf, assets); world.freezeAi = true;
            world.enqueue({0, 1, true}); world.enqueue({400000000, 1, false});
            world.enqueue({450000000, 5, true}); world.enqueue({470000000, 5, false});
            int64_t previous = 0;
            for (int frame = 1; frame <= fps * 2; ++frame) {
                const auto boundary = int64_t(frame) * 1000000000 / fps;
                world.advance(boundary - previous);
                previous = boundary;
            }
            return Json{{"tick", world.tick}, {"ms", world.nowMs()}, {"position", {world.player.x, world.player.y, world.player.z}},
                        {"mp", world.player.mp}, {"animation", world.player.animation}, {"inputs", world.inputs()}};
        };
        check(simulate(30) == simulate(240),
              "The integrated World produces identical movement/jump/input state at 30 and 240 render Hz");
    }
    {
        // Exercise the production drop path with source-backed MOB data. The
        // event ledger is deliberately tested separately from the World
        // fixture so a duplicate kill cannot be hidden by combat setup.
        RegionCatalog catalog(pvf, assets);
        Progression first(catalog), isolated(catalog);
        RandomStreams firstRandom(0x12345678), isolatedRandom(0x12345678);
        isolatedRandom.stream(RandomDomain::WorldGeneration).next();
        isolatedRandom.stream(RandomDomain::Ai, 19).bounded(97);
        isolatedRandom.stream(RandomDomain::Particles, 7).next();
        isolatedRandom.stream(RandomDomain::Audio).next();
        const std::string eventKey = "simulation-loot-isolation";
        check(first.recordKill(2, 1, 2, eventKey, 42, &firstRandom) &&
              isolated.recordKill(2, 1, 2, eventKey, 42, &isolatedRandom),
              "Production recordKill accepts one source-backed kill in each isolated ledger");
        const auto &firstDrop = first.state.at("drops").at(eventKey);
        const auto &isolatedDrop = isolated.state.at("drops").at(eventKey);
        check(firstDrop.at("random_before") == isolatedDrop.at("random_before") &&
              firstDrop.at("random_after") == isolatedDrop.at("random_after") &&
              firstDrop.at("items") == isolatedDrop.at("items") &&
              firstDrop.at("gold") == isolatedDrop.at("gold"),
              "AI, particle, audio and world-generation draws cannot change the production loot stream");
        const auto randomAfter = firstRandom.snapshot();
        const auto stateAfter = first.state;
        check(!first.recordKill(2, 1, 2, eventKey, 42, &firstRandom) &&
              first.state == stateAfter && firstRandom.snapshot() == randomAfter,
              "A duplicate kill key is idempotent and consumes no additional loot randomness or XP");
        const auto lootKey = firstDrop.at("random_after");
        const auto lootStream = firstRandom.stream(RandomDomain::Loot,
            [&] {
                uint64_t hash = UINT64_C(1469598103934665603);
                for (unsigned char c : eventKey) hash = (hash ^ c) * UINT64_C(1099511628211);
                return hash ^ uint64_t(42);
            }());
        check(lootStream.snapshot() == lootKey,
              "The persisted random-after trace identifies the actual shared Loot stream state");

        Progression failed(catalog);
        failed.state["quests"]["103"] = {{"status", "active"}, {"progress", 0}};
        RandomStreams failureRandom(0xabcdef);
        const std::string failureKey = "simulation-loot-atomic-failure";
        const auto originalState = failed.state;
        const auto originalRandom = failureRandom.snapshot();
        // Inject malformed decoded fields into a local source model; never
        // modify the source PVF. Even a row after a valid item must be checked.
        auto &monsterFields = catalog.monsters.at(1).fields;
        for (const auto &malformed : {Json::array({1106, 10, 1112, "bad-weight"}),
                                      Json::array({1106, 10, 1112}),
                                      Json::array({1106, UINT64_MAX})}) {
            monsterFields.insert(monsterFields.begin(), Field{"[item]", malformed, 0});
            const bool rejected = check.rejects([&] { failed.recordKill(2, 1, 2, failureKey, 42, &failureRandom); });
            monsterFields.erase(monsterFields.begin());
            check(rejected && failed.state == originalState && failureRandom.snapshot() == originalRandom,
                  "Malformed source drop rows leave kill/quest/XP/drop ledgers and the shared RNG bank untouched");
        }
        auto &questFields = catalog.quests.at(103).fields;
        questFields.insert(questFields.begin(), Field{"[int data]", Json::array({2, 0, 1, "bad-count"}), 0});
        const bool rejectedQuest = check.rejects([&] { failed.recordKill(2, 1, 2, failureKey, 42, &failureRandom); });
        questFields.erase(questFields.begin());
        check(rejectedQuest && failed.state == originalState && failureRandom.snapshot() == originalRandom,
              "A source quest count error cannot record a kill or partially advance quest/experience state");

        uint64_t instance = UINT64_C(1469598103934665603);
        for (unsigned char c : failureKey) instance = (instance ^ c) * UINT64_C(1099511628211);
        instance ^= uint64_t(42);
        auto &exhausting = failureRandom.stream(RandomDomain::Loot, instance);
        auto exhausted = exhausting.snapshot(); exhausted["draws"] = UINT64_MAX - 1;
        exhausting.restore(exhausted);
        const auto exhaustedBank = failureRandom.snapshot();
        check(check.rejects([&] { failed.recordKill(2, 1, 2, failureKey, 42, &failureRandom); }) &&
              failed.state == originalState && failureRandom.snapshot() == exhaustedBank,
              "RNG exhaustion after a prepared loot draw cannot consume live randomness, XP or the event key");
        failureRandom.restore(originalRandom);
        Progression retryReference(catalog); retryReference.state = originalState;
        RandomStreams referenceRandom(0xabcdef);
        check(failed.recordKill(2, 1, 2, failureKey, 42, &failureRandom) &&
              retryReference.recordKill(2, 1, 2, failureKey, 42, &referenceRandom) &&
              failed.state == retryReference.state && failureRandom.snapshot() == referenceRandom.snapshot(),
              "Retry after source/RNG failure produces exactly the same complete reward and random state as a first attempt");
        const auto completed = failed.state;
        const auto completedRandom = failureRandom.snapshot();
        check(!failed.recordKill(2, 1, 2, failureKey, 42, &failureRandom) &&
              failed.state == completed && failureRandom.snapshot() == completedRandom,
              "A successful retry commits one kill, quest increment, XP award and drop, then rejects duplicate processing");
        failed.state["xp"] = INT64_MAX;
        const auto overflowState = failed.state;
        check(check.rejects([&] { failed.recordKill(2, 1, 2, "simulation-loot-xp-overflow", 42, &failureRandom); }) &&
              failed.state == overflowState && failureRandom.snapshot() == completedRandom,
              "Experience overflow rejects the reward before any event, drop or RNG state is committed");
    }
    {
        RegionCatalog catalog(pvf, assets);
        RegionSession session;
        session.begin(catalog, 1, 9801);
        session.run.current = session.run.boss;
        World world(pvf, assets);
        world.freezeAi = true;
        world.combat = true;
        Progression progress(catalog);
        // Use the selected source boss-room spawn list. Lethal diagnostic hits
        // isolate reward batching from balance/input behavior; World produces
        // its actual killed events on different ticks of one catch-up pump.
        const auto &spawns = catalog.maps.at(session.run.room().mapId).monsters;
        check(spawns.size() >= 2, "The source boss-room fixture contains multiple independently rewarded actors");
        for (size_t i = 0; i < spawns.size(); ++i) {
            Actor monster;
            monster.id = int(i + 1); monster.sourceId = spawns[i].id;
            monster.monsterPath = catalog.monsterPath(spawns[i].id);
            monster.x = monster.px = spawns[i].x;
            monster.y = monster.py = spawns[i].y + 80;
            monster.z = monster.pz = spawns[i].z;
            monster.boss = spawns[i].type == "[boss]";
            monster.hp = monster.maxHp = 1;
            world.monsters.push_back(std::move(monster));
        }
        const auto stamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        const auto path = std::filesystem::absolute(std::filesystem::path("cache/simulation-catchup-reward-tests") / std::to_string(stamp));
        CharacterStore store(path, "simulation-catchup-test-content");
        store.data["characters"][0] = {{"name", "Catch-up rewards"}, {"class", "swordman"},
            {"identity", CharacterIdentity{}.json()}};
        store.capture(0, world, progress);
        store.data["characters"][0]["region_session"] = session.save(world, "dungeon");
        store.commit("before-catchup");
        const auto previousGeneration = store.generation();
        world.setObjectTick([&](World &simulation) {
            if (simulation.tick == 2) simulation.diagnosticHit(1, 1, 0, 0, 1, {});
            if (simulation.tick == 4)
                for (size_t i = 1; i < spawns.size(); ++i) simulation.diagnosticHit(int(i + 1), 1, 0, 0, 1, {});
        });
        world.advance(1000000000, 8);
        std::set<int64_t> killedTicks;
        std::vector<std::pair<std::string, Event>> kills;
        for (const auto &event : world.events) if (event.kind == "killed") {
            const auto key = session.run.token + ":" + std::to_string(session.run.current) + ":" + std::to_string(event.target);
            check(progress.recordKill(session.run.dungeonId, event.value, catalog.dungeons.at(session.run.dungeonId).basisLevel,
                                      key, session.run.seed + event.target, &world.randomStreams()),
                  "A real catch-up death event enters the production reward transaction once");
            killedTicks.insert(event.tick);
            kills.emplace_back(key, event);
        }
        session.remember(world);
        check(killedTicks == std::set<int64_t>{2, 4} && kills.size() == spawns.size() && session.run.complete() &&
              progress.clearDungeon(session.run.dungeonId, session.run.token, 1),
              "One budgeted catch-up pump produces separate-tick kills and the source boss-room clear reward");
        world.characterLevel = progress.level();
        store.capture(0, world, progress);
        store.data["characters"][0]["region_session"] = session.save(world, "dungeon");
        const auto expectedState = progress.state;
        const auto expectedRandom = world.randomStreams().snapshot();
        const auto expectedClock = world.simulationCheckpoint().at("clock");
        store.commit("catchup-kills-and-clear");
        const auto &saved = store.data.at("characters").at(0);
        check(store.generation() == previousGeneration + 1 && saved.at("progression") == expectedState &&
              saved.at("simulation").at("clock") == expectedClock && saved.at("simulation").at("random") == expectedRandom &&
              saved.at("region_session").at("run").at("rooms").at(session.run.boss).at("cleared") == true &&
              saved.at("progression").at("events").size() == spawns.size() &&
              saved.at("progression").at("drops").size() == spawns.size() && saved.at("progression").at("clears").size() == 1,
              "All catch-up kills, drops, XP, boss clear, world clock/backlog and RNG publish in one save generation");
        store.close();
        CharacterStore recovered(path, "simulation-catchup-test-content");
        World resumed(pvf, assets); resumed.freezeAi = true;
        Progression restoredProgress(catalog);
        recovered.apply(0, resumed, restoredProgress);
        RegionSession restoredSession;
        check(restoredSession.load(recovered.data.at("characters").at(0).at("region_session"), catalog) &&
              restoredSession.restore(resumed) && resumed.monsters.size() == spawns.size() &&
              std::all_of(resumed.monsters.begin(), resumed.monsters.end(), [](const Actor &actor) { return actor.dead && actor.hp == 0; }) &&
              resumed.pendingTicks() == 52 && resumed.randomStreams().snapshot() == expectedRandom,
              "Reload restores every rewarded dead actor, remaining catch-up debt and the matching loot RNG generation");
        for (const auto &[key, event] : kills)
            check(!restoredProgress.recordKill(restoredSession.run.dungeonId, event.value,
                                              catalog.dungeons.at(restoredSession.run.dungeonId).basisLevel,
                                              key, restoredSession.run.seed + event.target, &resumed.randomStreams()),
                  "Reprocessing a saved catch-up kill cannot reaward or reroll its drop");
        check(!restoredProgress.clearDungeon(restoredSession.run.dungeonId, restoredSession.run.token, 1),
              "Reprocessing the restored boss clear cannot grant another clear reward");
        resumed.advance(0, 8);
        check(restoredProgress.state == expectedState && resumed.randomStreams().snapshot() == expectedRandom &&
              std::none_of(resumed.events.begin(), resumed.events.end(), [](const Event &event) { return event.kind == "killed"; }),
              "Continuing restored catch-up does not emit another kill or consume additional reward randomness");
    }
    return check.report("Integrated World clock/input/handle/checkpoint compatibility; ongoing controller and persistent effect continuation remain outside this restore policy");
}
} // namespace dnf
