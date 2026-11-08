#include "dnf/act_runtime.hpp"
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
// These tests execute the staged ACT scheduler against an immutable query and
// command-capture host. They do not implement or validate World entity/HP/audio/
// PTL consumers, so passing them is not a P06 integration-completion claim.
class CaptureWorld final : public ActWorldView {
  public:
    std::map<EntityHandle, ActEntityView> values;
    std::optional<ActEntityView> entity(EntityHandle handle) const override {
        const auto found = values.find(handle);
        return found == values.end() ? std::nullopt : std::optional<ActEntityView>(found->second);
    }
    std::vector<EntityHandle> entities() const override {
        std::vector<EntityHandle> result;
        // Return reverse order to ensure the runtime imposes stable identity.
        for (auto it = values.rbegin(); it != values.rend(); ++it) result.push_back(it->first);
        return result;
    }
};
class CaptureResources final : public ActResourceResolver {
    Pvf &pvf_;
    Assets &assets_;
    std::map<int, std::string> objectPaths_;
    std::string canonical(const std::string &value) const {
        return normalize(std::filesystem::u8path(value).lexically_normal().generic_u8string());
    }
    std::optional<std::string> resolvePath(const std::string &parent, const std::string &literal) const {
        std::set<std::string> found;
        const auto directory = std::filesystem::u8path(parent).parent_path();
        for (auto candidate : {canonical((directory / std::filesystem::u8path(literal)).generic_u8string()),
                               canonical(literal), canonical("monster/" + literal)})
            if (pvf_.has(candidate)) found.insert(candidate);
        if (found.size() != 1) return std::nullopt;
        return *found.begin();
    }
    static std::optional<ActResourceKind> pathKind(const std::string &path) {
        const auto suffix = normalize(std::filesystem::u8path(path).extension().generic_u8string());
        if (suffix == ".act") return ActResourceKind::Action;
        if (suffix == ".ani") return ActResourceKind::Animation;
        if (suffix == ".atk") return ActResourceKind::AttackInfo;
        if (suffix == ".ptl") return ActResourceKind::Particle;
        return std::nullopt;
    }
    void trace(const std::string &path, std::set<std::string> &visited, std::vector<ActDependency> &dependencies, size_t depth) const {
        if (!visited.insert(path).second) return;
        if (depth > 16 || visited.size() > 512) throw std::runtime_error("Test dependency graph budget exceeded");
        const auto extension = normalize(std::filesystem::u8path(path).extension().generic_u8string());
        if (extension == ".ani") {
            if (pvf_.has(path + ".als")) {
                ActDependency layers;
                layers.request = {ActResourceKind::Animation, makeSourceRef(pvf_, path), path + ".als", -1};
                layers.resolved = makeSourceRef(pvf_, path + ".als");
                layers.found = layers.runtimeSupported = true;
                layers.diagnostic = "test command-capture ALS dependency; production composition not asserted";
                dependencies.push_back(std::move(layers));
                trace(path + ".als", visited, dependencies, depth + 1);
            }
            return;
        }
        const auto script = pvf_.script(path);
        bool spawn = false;
        for (const auto &field : script.fields) {
            const auto tag = normalize(field.tag);
            if (tag == "[create passiveobject]") spawn = true;
            else if (tag == "[/create passiveobject]") spawn = false;
            else if (spawn && tag == "[index]" && field.values.size() == 1 && field.values[0].is_number_integer()) {
                const int index = field.values[0].get<int>();
                ActDependency child;
                child.request = {ActResourceKind::PassiveObject, makeSourceRef(pvf_, path, field.offset), "", index};
                const auto found = objectPaths_.find(index);
                child.found = found != objectPaths_.end() && pvf_.has(found->second);
                child.runtimeSupported = child.found;
                child.diagnostic = "test command-capture child-object dependency";
                if (child.found) child.resolved = makeSourceRef(pvf_, found->second);
                dependencies.push_back(child);
                if (child.found) trace(found->second, visited, dependencies, depth + 1);
            } else if (tag == "[sound]" || tag == "[sound probability]") {
                const size_t stride = tag == "[sound probability]" ? 3 : field.values.size() == 1 ? 1 : 2;
                for (size_t at = 0; at < field.values.size(); at += stride) if (field.values[at].is_string()) {
                    ActDependency sound;
                    sound.request = {ActResourceKind::Sound, makeSourceRef(pvf_, path, field.offset), field.values[at].get<std::string>(), -1};
                    sound.resolved = sound.request.origin; sound.found = sound.runtimeSupported = true;
                    sound.diagnostic = "test command-capture sound literal; audio registry not asserted";
                    dependencies.push_back(std::move(sound));
                }
            }
        }
        for (const auto &field : script.fields) for (const auto &value : field.values) {
            if (!value.is_string()) continue;
            const auto literal = value.get<std::string>();
            const auto kind = pathKind(literal);
            if (!kind) continue;
            ActDependency dependency;
            dependency.request = {*kind, makeSourceRef(pvf_, path, field.offset), literal, -1};
            const auto resolved = resolvePath(path, literal);
            dependency.found = bool(resolved);
            // Test host only: capability is command capture, not real behavior.
            dependency.runtimeSupported = bool(resolved);
            dependency.diagnostic = "test command-capture dependency; production consumer not asserted";
            if (resolved) dependency.resolved = makeSourceRef(pvf_, *resolved);
            dependencies.push_back(dependency);
            if (resolved) trace(*resolved, visited, dependencies, depth + 1);
        }
    }
  public:
    std::optional<ActResourceKind> deny;
    bool knowSpawnClosure = true;
    explicit CaptureResources(Pvf &pvf, Assets &assets) : pvf_(pvf), assets_(assets) {
        const auto list = pvf_.script("passiveobject/passiveobject.lst");
        for (size_t i = 0; i + 1 < list.tokens.size(); i += 2) {
            const auto &id = list.tokens[i].at("value");
            const auto &name = list.tokens[i + 1].at("value");
            if (id.is_number_integer() && name.is_string())
                objectPaths_[id.get<int>()] = canonical("passiveobject/" + name.get<std::string>());
        }
    }
    ActResolvedResource resolve(const ActResourceRequest &request) const override {
        ActResolvedResource result;
        result.diagnostic = "test command-capture capability only; no World consumer claim";
        if (request.kind == ActResourceKind::Sound) {
            // This test host captures the literal event; production resolver
            // must consult the actual audio registry and consumer capability.
            result.found = !request.literal.empty(); result.runtimeSupported = result.found;
            result.source = request.origin;
        } else {
            std::optional<std::string> path;
            if (request.kind == ActResourceKind::PassiveObject) {
                const auto found = objectPaths_.find(request.index);
                if (found != objectPaths_.end() && pvf_.has(found->second)) path = found->second;
            } else path = resolvePath(request.origin.memberPath, request.literal);
            result.found = bool(path); result.runtimeSupported = result.found;
            if (path) {
                result.source = makeSourceRef(pvf_, *path);
                if (request.kind == ActResourceKind::Animation) {
                    const auto animation = assets_.animation(*path);
                    for (const auto &frame : animation->frames) result.frameDurationsMs.push_back(frame.duration);
                    // Tests deliberately exercise non-loop action instances.
                    result.animationLoops = false;
                }
                result.transitiveClosureKnown = request.kind != ActResourceKind::PassiveObject || knowSpawnClosure;
                std::set<std::string> visited;
                trace(*path, visited, result.transitive, 0);
            }
        }
        if (deny && *deny == request.kind) { result.runtimeSupported = false; result.diagnostic = "intentionally missing test host consumer"; }
        return result;
    }
};
struct Fixture {
    CaptureWorld world;
    EntityHandle owner{11, 1}, characterA{21, 1}, characterB{22, 1};
    Fixture() {
        ActEntityView source; source.handle = owner; source.kind = ActEntityKind::Passive; source.team = 1;
        source.target = characterA; source.direction = -1; source.position = {100, 200, 0};
        source.lastAttackSuccess = characterA; source.lastAttackSuccesses = {characterA, characterB};
        ActEntityView a; a.handle = characterA; a.kind = ActEntityKind::Character; a.team = 2;
        a.position = {300, 210, 0}; a.hp = 80; a.mp = 20; a.level = 50;
        ActEntityView b = a; b.handle = characterB; b.position.x = 500; b.hp = 20;
        world.values.emplace(owner, source); world.values.emplace(characterA, a); world.values.emplace(characterB, b);
    }
    ActBindRequest request(uint64_t id = 100) const {
        ActBindRequest value; value.owner = owner; value.instanceId = id; value.actionId = id + 1;
        value.randomSeed = 12345; value.randomSequence = 77;
        return value;
    }
};
ActAdvanceInput tickInput(uint64_t tick) {
    ActAdvanceInput input;
    input.step.tick = tick; input.step.milliseconds = FixedStepClock::millisecondsAtTick(tick);
    input.step.deltaMilliseconds = uint32_t(input.step.milliseconds - FixedStepClock::millisecondsAtTick(tick - 1));
    return input;
}
std::vector<ActEmittedCommand> runTicks(ActInstanceState &state, size_t count, const ActWorldView &world) {
    std::vector<ActEmittedCommand> commands;
    for (size_t i = 0; i < count; ++i) {
        const auto step = prepareActAdvance(state, tickInput(state.lastTick + 1), world);
        if (!step.ok) throw std::runtime_error(step.error);
        commands.insert(commands.end(), step.commands.begin(), step.commands.end());
        if (!publishActStep(state, step)) throw std::runtime_error("ACT test failed to publish command-capture step");
    }
    return commands;
}
template<class Payload> std::vector<const ActEmittedCommand *> commandsOf(const std::vector<ActEmittedCommand> &commands) {
    std::vector<const ActEmittedCommand *> result;
    for (const auto &command : commands) if (std::holds_alternative<Payload>(command.payload)) result.push_back(&command);
    return result;
}
Json commandsJson(const std::vector<ActEmittedCommand> &commands) {
    Json result = Json::array(); for (const auto &command : commands) result.push_back(command.json()); return result;
}
constexpr uint64_t testGeneration = 7;
Json checkpoint(const ActInstanceState &state) { return snapshotActInstance(state, testGeneration); }
ActBindResult recover(std::shared_ptr<const ActProgram> program, const Json &value, const ActWorldView &world) {
    return restoreActInstance(std::move(program), value, world, testGeneration);
}
Script rewriteTokenInteger(Script script, const std::string &tag, int value) {
    for (auto &field : script.fields) if (normalize(field.tag) == normalize(tag) && !field.values.empty() && field.values[0].is_number_integer()) {
        field.values[0] = value;
        const auto offset = field.offset + 5;
        bool changed = false;
        for (auto &token : script.tokens) if (token.at("offset") == offset) {
            token["raw"] = value; token["value"] = value; changed = true; break;
        }
        if (!changed || offset + 5 > script.rawBytes.size()) throw std::runtime_error("Cannot mutate test integer token");
        int32_t raw = value; std::memcpy(script.rawBytes.data() + offset + 1, &raw, sizeof(raw));
        return script;
    }
    throw std::runtime_error("Test integer tag was not found");
}
Script syntheticScript(const std::vector<Field> &input) {
    // Synthetic edge-case source has its own explicit identity and complete
    // bytes/tokens; it is never represented as a native PVF member.
    Script result; result.path = "test/synthetic-act-host-edge-case.act";
    result.rawBytes = {0xb0, 0xd0}; result.source = {{"test_only", true}, {"evidence", "synthetic"}};
    int32_t stringId = 1;
    auto token = [&](int type, int32_t raw, Json value) {
        const auto offset = result.rawBytes.size();
        result.rawBytes.push_back(uint8_t(type));
        const auto *bytes = reinterpret_cast<const uint8_t *>(&raw);
        result.rawBytes.insert(result.rawBytes.end(), bytes, bytes + sizeof(raw));
        result.tokens.push_back({{"offset", offset}, {"type", type}, {"raw", raw}, {"value", std::move(value)}});
    };
    for (const auto &field : input) {
        const auto offset = result.rawBytes.size();
        token(5, stringId++, field.tag);
        result.fields.push_back({field.tag, field.values, offset});
        for (const auto &value : field.values) {
            if (value.is_string()) token(7, stringId++, value);
            else if (value.is_number_integer()) token(2, value.get<int32_t>(), value);
            else throw std::runtime_error("Synthetic test source supports integer/string operands only");
        }
    }
    return result;
}
template<class Function> bool rejectsReceipt(Function function) {
    try { function(); } catch (const std::exception &) { return true; }
    return false;
}
// This independent copy is the historical fingerprint contract. A codec change
// must not accidentally hash event IDs, receipt versions or extension fields.
Json historicalEventPayload(const ActEventContext &event) {
    Json value = {{"kind", int(event.kind)}, {"subject", event.subject.json()}, {"other", event.other.json()},
                  {"stuck", event.stuck}, {"metadata", event.metadata}};
    if (event.subjectSnapshot) {
        const auto &e = *event.subjectSnapshot;
        Json hits = Json::array(); for (auto handle : e.lastAttackSuccesses) hits.push_back(handle.json());
        value["subject_snapshot"] = {{"handle", e.handle.json()}, {"target", e.target.json()},
            {"last_attacker", e.lastAttacker.json()}, {"last_attack_success", e.lastAttackSuccess.json()},
            {"summon_master", e.summonMaster.json()}, {"last_attack_successes", hits}, {"kind", int(e.kind)},
            {"position", Json::array({e.position.x, e.position.y, e.position.z})}, {"team", e.team},
            {"direction", e.direction}, {"hp", e.hp}, {"mp", e.mp}, {"level", e.level}, {"alive", e.alive}};
    }
    return value;
}
std::string historicalEventDigest(const ActEventContext &event) {
    const auto bytes = historicalEventPayload(event).dump();
    return sha256(Bytes(bytes.begin(), bytes.end()));
}
struct ReceiptRemapFixture {
    EntityRegistry saved, prepared;
    CaptureWorld original, fresh;
    EntityHandle owner, target, other, stale;
    std::map<EntityHandle, EntityHandle> mapping;
    ReceiptRemapFixture() {
        owner = saved.create(); target = saved.create(); other = saved.create(); stale = saved.create();
        saved.retire(stale);
        ActEntityView a; a.handle = owner; a.target = target; a.lastAttacker = stale;
        a.lastAttackSuccess = other; a.lastAttackSuccesses = {target, other, stale}; a.summonMaster = other;
        a.kind = ActEntityKind::Monster; a.hp = 100; a.mp = 30; a.position = {110, 220, 0}; a.direction = -1;
        original.values.emplace(owner, a);
        a.handle = target; a.kind = ActEntityKind::Character; a.team = 2; original.values.emplace(target, a);
        a.handle = other; a.alive = false; a.hp = 0; original.values.emplace(other, a);
        prepared = saved; prepared.retireAll();
        for (auto old : saved.active()) mapping.emplace(old, prepared.create());
        for (const auto &entry : original.values) {
            a = entry.second; remap(a); fresh.values.emplace(a.handle, a);
        }
    }
    EntityHandle remap(EntityHandle value) const {
        const auto found = mapping.find(value); return found == mapping.end() ? value : found->second;
    }
    void remap(ActEntityView &a) const {
        a.handle = remap(a.handle); a.target = remap(a.target); a.lastAttacker = remap(a.lastAttacker);
        a.lastAttackSuccess = remap(a.lastAttackSuccess); a.summonMaster = remap(a.summonMaster);
        for (auto &hit : a.lastAttackSuccesses) hit = remap(hit);
    }
    ActEventContext event(uint64_t id = 9000) const {
        ActEventContext value; value.eventId = id; value.kind = ActEventKind::SetAction;
        value.subject = owner; value.other = target; value.subjectSnapshot = original.values.at(owner); return value;
    }
    ActBindRequest request() const {
        ActBindRequest value; value.owner = owner; value.instanceId = 900; value.actionId = 901;
        value.randomSeed = 77; value.randomSequence = 21; return value;
    }
};
} // namespace

Json runActRuntimeTests(Pvf &pvf, Assets &assets) {
    Json report = {{"scope", "staged ACT core and command-capture host; no production World integration"},
        {"native_behavior_verified", false}, {"world_consumers_verified", false}, {"checks", Json::array()}};
    int passed = 0, failed = 0;
    auto check = [&](const std::string &name, bool condition) {
        report["checks"].push_back({{"name", name}, {"passed", condition}});
        if (condition) ++passed; else ++failed;
    };
    auto run = [&](const std::string &name, auto function) {
        try { function(); }
        catch (const std::exception &error) { report["checks"].push_back({{"name", name}, {"passed", false}, {"error", error.what()}}); ++failed; }
    };
    CaptureResources resources(pvf, assets);
    ActCompileContext context; context.packageIdentity = pvf.identity(); context.resources = &resources;
    context.hasCommandConsumer = [](const std::string &) { return true; }; // Explicit command-capture harness only.
    if (context.packageIdentity.empty()) context.packageIdentity = "test-package:" + sha256(pvf.read("passiveobject/passiveobject.lst"));
    const auto drakScript = pvf.script("passiveobject/actionobject/monster/riding/action/drak_sword.act");
    const auto breathScript = pvf.script("monster/newmonsters/lizardman/dragon_man/action/change_breath.act");
    const auto teleportScript = pvf.script("monster/newmonsters/shonan/kaizen/action/teleport.act");
    const auto procScript = pvf.script("monster/newmonsters/dimensiongate/bakal/gold_dragon_main/action/proc.act");
    const auto drak = compileActProgram(drakScript, context);
    const auto breath = compileActProgram(breathScript, context);
    const auto teleport = compileActProgram(teleportScript, context);
    const auto proc = compileActProgram(procScript, context);
    report["compilation"] = Json::array({drak.json(), breath.json(), teleport.json(), proc.json()});
    check("Four real ACT examples compile against explicit test command-capture capabilities", drak.ok && breath.ok && teleport.ok && proc.ok);
    if (!drak.ok || !breath.ok || !teleport.ok || !proc.ok) {
        report["passed"] = passed; report["failed"] = failed; return report;
    }
    Fixture fixture;
    check("Source raw bytes/hash/tokens retained", drak.program->original.rawBytes == drakScript.rawBytes &&
        drak.program->source.memberSha256 == sha256(drakScript.rawBytes) && drak.program->original.tokens == drakScript.tokens);
    check("Interleaved BEHAVIOR declaration numbering remains stable", drak.program->behaviors.size() == 5 &&
        std::holds_alternative<ActDestroy>(drak.program->behaviors[3].instructions.at(0).payload) &&
        std::get<ActSpawn>(drak.program->behaviors[4].instructions.at(0).payload).objectIndex == 9124);
    check("Logic-only PROC has no artificial BASE ANI requirement", !proc.program->motion && proc.program->triggers.size() == 1);
    run("drak fixed frames", [&] {
        auto bound = bindActProgram(drak.program, fixture.request(), fixture.world);
        if (!bound.ok) throw std::runtime_error(bound.error);
        const auto commands = runTicks(bound.state, 180, fixture.world);
        const auto speeds = commandsOf<ActSetSpeed>(commands);
        check("drak source frame0/6/7 set three velocity stages", speeds.size() == 3 &&
            std::get<ActSetSpeed>(speeds[0]->payload).x == -10 && std::get<ActSetSpeed>(speeds[1]->payload).x == 200 &&
            std::get<ActSetSpeed>(speeds[2]->payload).x == 1200);
        check("drak frame8 destroys itself once", commandsOf<ActDestroy>(commands).size() == 1);
        const auto sounds = commandsOf<ActSound>(commands);
        check("drak MOTION SOUND events are emitted", sounds.size() == 2 &&
            std::get<ActSound>(sounds[0]->payload).tag == "A_WHEEL_CREATION" && std::get<ActSound>(sounds[1]->payload).tag == "STAFF_02");
        std::set<std::string> keys; for (const auto &command : commands) keys.insert(command.stableKey());
        check("Every emitted command owns a stable unique instance/action/sequence key", keys.size() == commands.size());
    });
    run("drak event dispatch", [&] {
        auto bound = bindActProgram(drak.program, fixture.request(200), fixture.world);
        ActEventContext event; event.eventId = 900; event.kind = ActEventKind::AttackSuccess;
        event.subject = fixture.owner; event.other = fixture.characterB;
        const auto before = checkpoint(bound.state);
        auto first = prepareActEvent(bound.state, event, fixture.world);
        auto retry = prepareActEvent(bound.state, event, fixture.world);
        check("Preparing event is pure and exact retry reproduces command IDs/RNG", first.ok && retry.ok &&
            checkpoint(bound.state) == before && commandsJson(first.commands) == commandsJson(retry.commands));
        const auto spawns = commandsOf<ActSpawn>(first.commands);
        const auto destroys = commandsOf<ActDestroy>(first.commands);
        check("Accepted-hit event captures actual recipient and spawns before owner destroy", spawns.size() == 1 && destroys.size() == 1 &&
            spawns[0]->recipient == fixture.characterB && destroys[0]->recipient == fixture.owner && first.commands[0].recipient == fixture.characterB);
        check("Captured origin bases remain explicit", spawns.size() == 1 && spawns[0]->ownerSnapshot && spawns[0]->recipientSnapshot &&
            spawns[0]->ownerSnapshot->position.x == 100 && spawns[0]->recipientSnapshot->position.x == 500);
        check("Commit candidate publishes once after host acceptance", publishActStep(bound.state, first) && !publishActStep(bound.state, retry));
        const auto duplicate = prepareActEvent(bound.state, event, fixture.world);
        check("Duplicate stable event emits no commands", duplicate.ok && duplicate.replayed && duplicate.commands.empty());
        event.other = fixture.characterA;
        const auto conflict = prepareActEvent(bound.state, event, fixture.world);
        check("Conflicting event identity is rejected without changing state", !conflict.ok && !conflict.faulted && conflict.commands.empty());
    });
    run("particle and PROC", [&] {
        auto breathState = bindActProgram(breath.program, fixture.request(300), fixture.world);
        const auto commands = runTicks(breathState.state, 180, fixture.world);
        const auto particles = commandsOf<ActParticle>(commands);
        check("Five independent breath frame triggers each emit both PTL commands", particles.size() == 10);
        check("PTL source XYZ is preserved", std::all_of(particles.begin(), particles.end(), [](const auto *command) {
            return std::get<ActParticle>(command->payload).offset.z == 88;
        }));
        auto procState = bindActProgram(proc.program, fixture.request(400), fixture.world);
        const auto procCommands = runTicks(procState.state, 30, fixture.world);
        const auto spawns = commandsOf<ActSpawn>(procCommands);
        check("Logic PROC LIMIT1 produces one real typed spawn request", spawns.size() == 1 &&
            std::get<ActSpawn>(spawns[0]->payload).objectIndex == 9174 && std::get<ActSpawn>(spawns[0]->payload).followingTarget);
    });
    run("teleport target and recovery", [&] {
        auto stateA = bindActProgram(teleport.program, fixture.request(500), fixture.world);
        const auto prefix = runTicks(stateA.state, 2, fixture.world);
        (void)prefix;
        const auto saved = checkpoint(stateA.state);
        auto restored = recover(teleport.program, saved, fixture.world);
        if (!restored.ok) throw std::runtime_error(restored.error);
        check("Snapshot restore is byte-structure stable", checkpoint(restored.state) == saved);
        const auto tailA = runTicks(stateA.state, 180, fixture.world);
        const auto tailB = runTicks(restored.state, 180, fixture.world);
        check("Restored random target/frame/SPEECH execution reproduces exact command log", commandsJson(tailA) == commandsJson(tailB) &&
            checkpoint(stateA.state) == checkpoint(restored.state));
        const auto teleports = commandsOf<ActTeleport>(tailA);
        check("FRAME7 random CHARACTER query calls teleport on exactly one character", teleports.size() == 1 &&
            (teleports[0]->recipient == fixture.characterA || teleports[0]->recipient == fixture.characterB));
        check("Teleport retains relative -140/MOVE ME contract", teleports.size() == 1 &&
            std::get<ActTeleport>(teleports[0]->payload).position.value.x == -140 && std::get<ActTeleport>(teleports[0]->payload).moveOwner);
        auto invalid = saved; invalid["program"]["member_sha256"] = std::string(64, '0');
        check("Changed source identity rejects entire restore", !recover(teleport.program, invalid, fixture.world).ok);
        invalid = saved; invalid["triggers"][0]["fires"] = 1000;
        check("Malformed trigger ledger rejects entire restore", !recover(teleport.program, invalid, fixture.world).ok);
        check("Mixed world commit generation rejects entire restore", !restoreActInstance(teleport.program, saved, fixture.world, testGeneration + 1).ok);
        invalid = saved; invalid["future_field"] = {{"preserve", 7}};
        const auto forward = recover(teleport.program, invalid, fixture.world);
        check("Unknown snapshot root data survives restore", forward.ok && checkpoint(forward.state).at("future_field") == invalid.at("future_field"));
    });
    run("budgets clocks cancellation", [&] {
        auto budgetContext = context; budgetContext.policy.maximumCommands = 1;
        const auto limited = compileActProgram(breathScript, budgetContext);
        auto state = bindActProgram(limited.program, fixture.request(600), fixture.world).state;
        bool faulted = false;
        for (int i = 0; i < 180 && !faulted; ++i) {
            const auto before = checkpoint(state);
            const auto step = prepareActAdvance(state, tickInput(state.lastTick + 1), fixture.world);
            if (step.faulted) {
                faulted = true;
                check("Budget failure discards partial PTL batch and emits only cleanup", !step.ok && step.commands.size() == 1 &&
                    std::holds_alternative<ActCleanup>(step.commands[0].payload) && checkpoint(state) == before);
                check("Fault cleanup can publish only after host commit", publishActStep(state, step) && state.status == ActInstanceStatus::Faulted);
            } else if (!step.ok || !publishActStep(state, step)) throw std::runtime_error(step.error);
        }
        check("Two-PTL source behavior reaches command budget fault", faulted);
        auto normal = bindActProgram(drak.program, fixture.request(700), fixture.world).state;
        const auto invalidClock = [&] { auto input = tickInput(1); input.animationDeltaUs = 16000; return prepareActAdvance(normal, input, fixture.world); }();
        check("Source clock rejects a second speed-scaled clock", invalidClock.faulted && invalidClock.commands.size() == 1);
        auto request = fixture.request(800); request.clockMode = ActClockMode::ExternalAnimationDelta;
        auto external = bindActProgram(drak.program, request, fixture.world).state;
        auto input = tickInput(1); input.animationDeltaUs = 0;
        auto frozen = prepareActAdvance(external, input, fixture.world);
        check("External zero animation delta preserves fixed simulation time and frame0", frozen.ok && frozen.candidate.elapsedMs == 16 && frozen.candidate.animationUs == 0);
        if (!publishActStep(external, frozen)) throw std::runtime_error("External step publish failed");
        const auto cancel = prepareActCancel(external, "test_scene_exit");
        check("Cancellation emits typed ownership cleanup", cancel.ok && cancel.commands.size() == 1 &&
            std::get<ActCleanup>(cancel.commands[0].payload).reason == "test_scene_exit");
        check("Cancelled continuation cannot keep executing", publishActStep(external, cancel) &&
            !prepareActAdvance(external, tickInput(2), fixture.world).ok);
        auto stale = fixture.world; stale.values.erase(fixture.owner);
        check("Stale owner generation rejects bind and running restore", !bindActProgram(drak.program, fixture.request(900), stale).ok &&
            !recover(drak.program, checkpoint(normal), stale).ok);
    });
    run("delayed calls and frame policy", [&] {
        const auto source = syntheticScript({
            {"[TRIGGER]", Json::array()}, {"[LIMIT]", Json::array({1})},
            {"[WHICH]", Json::array()}, {"[TARGET]", Json::array()},
            {"[DELAY DO BEHAVIOR]", Json::array()}, {"[CHECKUP OBJECT]", Json::array({0, 50})}, {"[/TRIGGER]", Json::array()},
            {"[BEHAVIOR]", Json::array()}, {"[SET SPEED]", Json::array()}, {"[X AXIS]", Json::array({30})},
            {"[/SET SPEED]", Json::array()}, {"[/BEHAVIOR]", Json::array()}});
        const auto compiled = compileActProgram(source, context);
        if (!compiled.ok) throw std::runtime_error(compiled.json().dump());
        auto state = bindActProgram(compiled.program, fixture.request(1000), fixture.world).state;
        const auto initial = runTicks(state, 1, fixture.world);
        check("Delayed behavior remains pending without early effects", initial.empty() && state.pending.size() == 1 && state.pending[0].dueMs == 66);
        const auto saved = checkpoint(state);
        auto restored = recover(compiled.program, saved, fixture.world);
        if (!restored.ok) throw std::runtime_error(restored.error);
        const auto commandsA = runTicks(state, 4, fixture.world);
        const auto commandsB = runTicks(restored.state, 4, fixture.world);
        check("Delayed continuation recovers the same recipients/deadline/IDs", commandsA.size() == 1 &&
            commandsA[0].recipient == fixture.characterA && commandsJson(commandsA) == commandsJson(commandsB));
        auto bad = saved; bad["pending"][0]["call"]["behavior"] = 50;
        check("Forged continuation absent from source is rejected", !recover(compiled.program, bad, fixture.world).ok);
        bad = saved; bad["pending"][0]["expected_action_id"] = 44;
        check("Old-action pending continuation is rejected", !recover(compiled.program, bad, fixture.world).ok);
        auto staleWorld = fixture.world;
        auto replacement = staleWorld.values.at(fixture.characterA); staleWorld.values.erase(fixture.characterA);
        replacement.handle.generation = 2; staleWorld.values.emplace(replacement.handle, replacement);
        auto stale = recover(compiled.program, saved, staleWorld);
        if (!stale.ok) throw std::runtime_error(stale.error);
        check("Stale delayed recipient does not retarget a new generation", runTicks(stale.state, 4, staleWorld).empty());
        auto another = recover(compiled.program, saved, fixture.world);
        const auto cancel = prepareActCancel(another.state, "action_replaced");
        check("Action cancellation clears delayed continuation atomically", cancel.ok && cancel.candidate.pending.empty() && another.state.pending.size() == 1);
        auto stepRequest = fixture.request(1100); stepRequest.clockMode = ActClockMode::ExternalAnimationDelta;
        auto crossed = bindActProgram(breath.program, stepRequest, fixture.world).state;
        auto first = tickInput(1); first.animationDeltaUs = 0;
        auto frame0 = prepareActAdvance(crossed, first, fixture.world);
        if (!frame0.ok || !publishActStep(crossed, frame0)) throw std::runtime_error("Crossed frame0 failed");
        uint64_t duration = 0; for (auto ms : breath.program->motion->frameDurationsMs) duration += uint64_t(ms) * 1000;
        auto jump = tickInput(2); jump.animationDeltaUs = duration;
        const auto allFrames = prepareActAdvance(crossed, jump, fixture.world);
        check("A single scaled animation step crossing five frames does not drop independent PTL triggers", allFrames.ok && commandsOf<ActParticle>(allFrames.commands).size() == 10);
        auto everyContext = context; everyContext.policy.id = "test-every-fixed-step";
        everyContext.policy.frameEvaluation = ActFrameEvaluation::EverySimulationStep;
        everyContext.policy.defaultLimit = 0;
        const auto every = compileActProgram(drakScript, everyContext);
        auto held = bindActProgram(every.program, stepRequest, fixture.world).state;
        auto holdInput = tickInput(1); holdInput.animationDeltaUs = 0;
        auto holdFirst = prepareActAdvance(held, holdInput, fixture.world);
        if (!holdFirst.ok || !publishActStep(held, holdFirst)) throw std::runtime_error("Held source frame step failed");
        holdInput = tickInput(2); holdInput.animationDeltaUs = 0;
        const auto holdSecond = prepareActAdvance(held, holdInput, fixture.world);
        check("Alternate explicit policy can recheck an unlimited held FRAME each simulation tick", holdSecond.ok && commandsOf<ActSetSpeed>(holdSecond.commands).size() == 1);
        const auto recursion = syntheticScript({
            {"[TRIGGER]", Json::array()}, {"[DO BEHAVIOR]", Json::array()}, {"[ME]", Json::array({0})}, {"[/TRIGGER]", Json::array()},
            {"[BEHAVIOR]", Json::array()}, {"[DELAY DO BEHAVIOR]", Json::array()}, {"[ME]", Json::array({0, 0})}, {"[/BEHAVIOR]", Json::array()}});
        const auto recursiveProgram = compileActProgram(recursion, context);
        if (!recursiveProgram.ok) throw std::runtime_error(recursiveProgram.json().dump());
        const auto recursiveState = bindActProgram(recursiveProgram.program, fixture.request(1150), fixture.world);
        const auto interrupted = prepareActAdvance(recursiveState.state, tickInput(1), fixture.world);
        check("Zero-delay recursive behavior is bounded with source-located cleanup", interrupted.faulted && interrupted.failureSource &&
            interrupted.failureSource->scope.find("BEHAVIOR") != std::string::npos && interrupted.commands.size() == 1 &&
            std::holds_alternative<ActCleanup>(interrupted.commands[0].payload));
    });
    run("render cadence and catchup invariance", [&] {
        auto drive = [&](uint64_t fps, size_t budget) {
            auto state = bindActProgram(teleport.program, fixture.request(1200), fixture.world).state;
            FixedStepClock clock;
            std::vector<ActEmittedCommand> commands;
            uint64_t priorNs = 0;
            auto consume = [&] {
                const auto tick = clock.popTick();
                if (!tick) return false;
                ActAdvanceInput input; input.step = *tick;
                const auto prepared = prepareActAdvance(state, input, fixture.world);
                if (!prepared.ok) throw std::runtime_error(prepared.error);
                commands.insert(commands.end(), prepared.commands.begin(), prepared.commands.end());
                if (!publishActStep(state, prepared)) throw std::runtime_error("Render cadence publish failed");
                return true;
            };
            for (uint64_t frame = 1; frame <= fps * 3; ++frame) {
                const uint64_t nextNs = frame * 1000000000ULL / fps;
                clock.addNanoseconds(int64_t(nextNs - priorNs)); priorNs = nextNs;
                for (size_t count = 0; count < budget; ++count) if (!consume()) break;
            }
            while (consume()) {}
            return Json{{"state", checkpoint(state)}, {"commands", commandsJson(commands)}};
        };
        const auto baseline = drive(60, 8);
        for (const auto fps : {30ULL, 144ULL, 240ULL})
            check(std::to_string(fps) + " Hz rendering leaves ACT state/RNG/commands unchanged", drive(fps, 8) == baseline);
        check("Budgeted catchup preserves every deferred fixed tick", drive(30, 1) == baseline);
    });
    run("source failures", [&] {
        auto noConsumers = context; noConsumers.hasCommandConsumer = {};
        const auto unhosted = compileActProgram(procScript, noConsumers);
        check("A typed parser alone cannot claim missing World command consumers", !unhosted.ok && !unhosted.program->runtimeReady &&
            std::any_of(unhosted.program->diagnostics.begin(), unhosted.program->diagnostics.end(), [](const auto &diagnostic) {
                return diagnostic.code == "missing_command_consumer";
            }));
        const auto malformed = compileActProgram(pvf.script("passiveobject/actionobject/common/action/throw_wave.act"), context);
        check("Missing dispatch/closing behavior does not receive implicit behavior0", !malformed.ok && !malformed.program->syntaxComplete);
        auto unsupported = breathScript;
        for (auto &field : unsupported.fields) if (normalize(field.tag) == "[particle]") { field.tag = "[unsupported mandatory command]"; break; }
        const auto unknown = compileActProgram(unsupported, context);
        check("Unknown mandatory opcode blocks program", !unknown.ok && !unknown.program->syntaxComplete);
        check("Source failure retains original raw bytes and ordered tokens", unknown.program->original.rawBytes == breathScript.rawBytes &&
            unknown.program->original.tokens == breathScript.tokens);
        for (const auto kind : {ActResourceKind::Sound, ActResourceKind::Particle, ActResourceKind::PassiveObject}) {
            resources.deny = kind;
            const auto blocked = compileActProgram(kind == ActResourceKind::Particle ? breathScript : drakScript, context);
            check(std::string("Missing ") + actResourceKindName(kind) + " consumer blocks ACT capability", !blocked.ok && !blocked.program->runtimeReady &&
                std::any_of(blocked.program->dependencies.begin(), blocked.program->dependencies.end(), [&](const auto &dependency) {
                    return dependency.request.kind == kind && !dependency.runtimeSupported;
                }));
        }
        resources.deny.reset(); resources.knowSpawnClosure = false;
        const auto incomplete = compileActProgram(drakScript, context);
        check("Unknown child-object closure blocks spawn capability", !incomplete.ok && !incomplete.program->sourceReady);
        resources.knowSpawnClosure = true;
        check("Spawn dependency audit retains child ACT records", std::any_of(drak.program->dependencies.begin(), drak.program->dependencies.end(), [](const auto &dependency) {
            return dependency.request.kind == ActResourceKind::Action;
        }));
        const auto invalidIndex = compileActProgram(rewriteTokenInteger(drakScript, "[ME]", 999999), context);
        check("Out-of-range source behavior is a compile failure", !invalidIndex.ok && !invalidIndex.program->syntaxComplete);
    });
    run("typed receipt historical codec and bounds", [&] {
        ReceiptRemapFixture f; auto event = f.event();
        auto receipt = snapshotActEventReceipt({event, Json{{"future_root", {{"id", 123}, {"generation", 4}}}}});
        check("Typed receipt shares the exact historical digest including snapshot handles", actEventIdentityJson(event) == historicalEventPayload(event) &&
            actEventFingerprint(event) == historicalEventDigest(event));
        const auto decoded = restoreActEventReceipt(receipt);
        check("Unknown receipt-root data survives without entering the fingerprint", snapshotActEventReceipt(decoded) == receipt &&
            receipt.at("fingerprint") == historicalEventDigest(event));
        auto trailing = snapshotActEventReceipt({event, Json::object()});
        trailing["future_tail"] = {{"id", f.owner.id}, {"generation", f.owner.generation}};
        check("Trailing receipt extension keeps exact ordered bytes",
            snapshotActEventReceipt(restoreActEventReceipt(trailing)).dump() == trailing.dump());
        Json middle = Json::object();
        for (auto field = trailing.begin(); field != trailing.end(); ++field) {
            middle[field.key()] = field.value();
            if (field.key() == "payload") middle["future_middle"] = {{"raw", true}};
        }
        auto middleDecoded = restoreActEventReceipt(middle);
        check("Middle and trailing receipt extensions keep exact ordered bytes",
            snapshotActEventReceipt(middleDecoded).dump() == middle.dump());
        middleDecoded.event.other = f.other;
        auto remappedTemplate = snapshotActEventReceipt(middleDecoded);
        auto expectedTemplate = middle;
        expectedTemplate["payload"] = actEventIdentityJson(middleDecoded.event);
        expectedTemplate["fingerprint"] = actEventFingerprint(middleDecoded.event);
        check("Typed remap replaces known receipt values in their original positions",
            remappedTemplate.dump() == expectedTemplate.dump());
        event.eventId += 1;
        check("Event occurrence ID remains outside the historical payload fingerprint", actEventFingerprint(event) == receipt.at("fingerprint"));
        auto bad = receipt; bad["payload"]["other"] = f.other.json();
        check("Original receipt payload changes reject before any remap", rejectsReceipt([&]{ restoreActEventReceipt(bad); }));
        bad = receipt; bad["payload"]["subject_snapshot"]["future_handle"] = f.target.json();
        check("Unknown typed snapshot fields cannot hide unregistered handle semantics", rejectsReceipt([&]{ restoreActEventReceipt(bad); }));
        bad = receipt; bad["payload"]["future_payload"] = true;
        check("Unknown identity payload fields reject", rejectsReceipt([&]{ restoreActEventReceipt(bad); }));
        bad = receipt; bad["metadata_schema"] = "future-v2";
        check("Unknown metadata codec rejects", rejectsReceipt([&]{ restoreActEventReceipt(bad); }));
        event = f.event(); event.metadata = {{"padding", std::string(ActEventReceiptBudget::maximumReceiptBytes, 'x')}};
        check("Receipt byte overflow is bounded before acceptance", rejectsReceipt([&]{ snapshotActEventReceipt({event, Json::object()}); }));
        event = f.event(); Json deep = 1;
        for (size_t i = 0; i <= ActEventReceiptBudget::maximumJsonDepth; ++i) deep = Json::array({deep});
        event.metadata = deep;
        check("Receipt JSON depth overflow rejects", rejectsReceipt([&]{ snapshotActEventReceipt({event, Json::object()}); }));
        event = f.event(); event.subjectSnapshot->lastAttackSuccesses.resize(ActEventReceiptBudget::maximumSnapshotSuccesses + 1, f.target);
        check("Typed snapshot success count overflow rejects", rejectsReceipt([&]{ snapshotActEventReceipt({event, Json::object()}); }));
        event = f.event(); event.subjectSnapshot->position.x = std::numeric_limits<double>::infinity();
        check("Nonfinite snapshot coordinates reject", rejectsReceipt([&]{ snapshotActEventReceipt({event, Json::object()}); }));
    });
    run("typed receipt remap and replay continuation", [&] {
        const auto script = syntheticScript({
            {"[TRIGGER]", Json::array()}, {"[LIMIT]", Json::array({1})}, {"[WHICH]", Json::array()}, {"[TARGET]", Json::array()},
            {"[DELAY DO BEHAVIOR]", Json::array()}, {"[CHECKUP OBJECT]", Json::array({0, 50})}, {"[/TRIGGER]", Json::array()},
            {"[BEHAVIOR]", Json::array()}, {"[SET SPEED]", Json::array()}, {"[X AXIS]", Json::array({30})},
            {"[/SET SPEED]", Json::array()}, {"[/BEHAVIOR]", Json::array()}});
        const auto compiled = compileActProgram(script, context);
        if (!compiled.ok) throw std::runtime_error(compiled.json().dump());
        ReceiptRemapFixture f; auto state = bindActProgram(compiled.program, f.request(), f.original).state;
        auto event = f.event(); const auto accepted = prepareActEvent(state, event, f.original);
        if (!accepted.ok || !publishActStep(state, accepted)) throw std::runtime_error(accepted.error);
        runTicks(state, 1, f.original); state.savedTargets[3] = f.other; state.savedTargets[4] = f.stale;
        state.variables = {{"diagnostic_only", {{"id", f.owner.id}, {"generation", f.owner.generation}}}};
        state.unknown = {{"future_extension", {{"id", f.owner.id}, {"generation", f.owner.generation}}}};
        auto saved = checkpoint(state); const auto original = saved;
        saved["accepted_event_receipts"][0]["future_root"] = {{"id", f.owner.id}, {"generation", f.owner.generation}};
        const auto restored = restoreRemappedActInstance(compiled.program, saved, f.saved, f.mapping, f.prepared, f.fresh, testGeneration);
        if (!restored.ok) throw std::runtime_error(restored.error);
        check("Remap is pure and retains clock/RNG/logical IDs", checkpoint(state) == original && restored.state.lastTick == state.lastTick &&
            restored.state.random.snapshot() == state.random.snapshot() && restored.state.commandIds.snapshot() == state.commandIds.snapshot());
        const auto &typed = restored.state.acceptedEventReceipts.at(event.eventId).event;
        check("Owner/pending/targets and all typed snapshot relations use the same ordered fresh mapping", restored.state.owner == f.mapping.at(f.owner) &&
            restored.state.pending[0].recipients[0] == f.mapping.at(f.target) && restored.state.savedTargets.at(3) == f.mapping.at(f.other) &&
            typed.subject == f.mapping.at(f.owner) && typed.other == f.mapping.at(f.target) && typed.subjectSnapshot->target == f.mapping.at(f.target) &&
            typed.subjectSnapshot->lastAttackSuccess == f.mapping.at(f.other) && typed.subjectSnapshot->summonMaster == f.mapping.at(f.other) &&
            typed.subjectSnapshot->lastAttackSuccesses == std::vector<EntityHandle>({f.mapping.at(f.target), f.mapping.at(f.other), f.stale}));
        check("Historical tombstones stay stale and opaque diagnostics remain byte-exact", typed.subjectSnapshot->lastAttacker == f.stale &&
            restored.state.savedTargets.at(4) == f.stale && !f.prepared.valid(f.stale) && !f.fresh.entity(f.owner) &&
            restored.state.variables == state.variables && restored.state.unknown == state.unknown &&
            checkpoint(restored.state)["accepted_event_receipts"][0]["future_root"] == saved["accepted_event_receipts"][0]["future_root"]);
        auto continued = restored.state; auto freshEvent = event; freshEvent.subject = f.mapping.at(event.subject); freshEvent.other = f.mapping.at(event.other);
        f.remap(*freshEvent.subjectSnapshot); const auto before = checkpoint(continued);
        const auto replay = prepareActEvent(continued, freshEvent, f.fresh);
        check("Remapped exact replay emits no commands or RNG and does not reinsert history", replay.ok && replay.replayed && replay.commands.empty() &&
            publishActStep(continued, replay) && checkpoint(continued) == before);
        freshEvent.other = f.mapping.at(f.other); const auto conflict = prepareActEvent(continued, freshEvent, f.fresh);
        check("Remapped conflicting replay preserves the live candidate", !conflict.ok && !conflict.faulted && checkpoint(continued) == before);
        const auto oldTail = runTicks(state, 4, f.original); const auto freshTail = runTicks(continued, 4, f.fresh);
        check("Pending call resumes once with unchanged stable command key and new recipient", oldTail.size() == 1 && freshTail.size() == 1 &&
            oldTail[0].stableKey() == freshTail[0].stableKey() && freshTail[0].recipient == f.mapping.at(f.target) &&
            state.random.snapshot() == continued.random.snapshot());
        auto malformed = saved; malformed["accepted_event_receipts"][0]["payload"]["other"] = f.other.json();
        check("Remap validates original receipt fingerprint before transformation", !restoreRemappedActInstance(compiled.program, malformed, f.saved, f.mapping, f.prepared, f.fresh, testGeneration).ok);
        auto legacy = saved; legacy["schema"] = 1; legacy.erase("accepted_event_receipts"); legacy.erase("event_receipt_coverage");
        const auto diagnostic = recover(compiled.program, legacy, f.original);
        check("Legacy digest-only history remains readable but cannot be remapped", diagnostic.ok && !diagnostic.state.eventReceiptsComplete &&
            !restoreRemappedActInstance(compiled.program, legacy, f.saved, f.mapping, f.prepared, f.fresh, testGeneration).ok);
        auto opaqueEvent = f.event(event.eventId + 1); opaqueEvent.metadata = {{"unregistered_handle", f.owner.json()}};
        auto withOpaque = bindActProgram(compiled.program, f.request(), f.original).state;
        const auto opaqueStep = prepareActEvent(withOpaque, opaqueEvent, f.original); publishActStep(withOpaque, opaqueStep);
        check("Opaque metadata remains valid diagnostic history and explicitly blocks remap", opaqueStep.ok &&
            recover(compiled.program, checkpoint(withOpaque), f.original).ok &&
            !restoreRemappedActInstance(compiled.program, checkpoint(withOpaque), f.saved, f.mapping, f.prepared, f.fresh, testGeneration).ok);
        auto mapping = f.mapping; mapping.erase(f.target);
        check("Incomplete saved-live map rejects", !restoreRemappedActInstance(compiled.program, saved, f.saved, mapping, f.prepared, f.fresh, testGeneration).ok);
        mapping = f.mapping; mapping[f.target] = mapping.at(f.owner);
        check("Duplicate fresh endpoint rejects", !restoreRemappedActInstance(compiled.program, saved, f.saved, mapping, f.prepared, f.fresh, testGeneration).ok);
        mapping = f.mapping; std::swap(mapping[f.owner], mapping[f.target]);
        check("Changing handle order cannot silently change query tie breaks", !restoreRemappedActInstance(compiled.program, saved, f.saved, mapping, f.prepared, f.fresh, testGeneration).ok);
        auto missing = f.fresh; missing.values.erase(f.mapping.at(f.other));
        check("Candidate view missing a registered dying actor rejects", !restoreRemappedActInstance(compiled.program, saved, f.saved, f.mapping, f.prepared, missing, testGeneration).ok);
        auto futureState = recover(compiled.program, saved, f.original).state; futureState.savedTargets[5] = {100000, 1};
        check("Unknown future historical handle rejects instead of later becoming live", !restoreRemappedActInstance(compiled.program, checkpoint(futureState), f.saved, f.mapping, f.prepared, f.fresh, testGeneration).ok);
        check("Mixed commit generation cannot enter remapped restore", !restoreRemappedActInstance(compiled.program, saved, f.saved, f.mapping, f.prepared, f.fresh, testGeneration + 1).ok);
    });
    run("typed receipt coverage and fault atomicity", [&] {
        auto policy = context; policy.policy.maximumRememberedEvents = 1;
        const auto compiled = compileActProgram(procScript, policy);
        if (!compiled.ok) throw std::runtime_error(compiled.json().dump());
        ReceiptRemapFixture f; auto state = bindActProgram(compiled.program, f.request(), f.original).state;
        const auto first = prepareActEvent(state, f.event(), f.original); if (!first.ok || !publishActStep(state, first)) throw std::runtime_error(first.error);
        const auto saved = checkpoint(state); const auto fault = prepareActEvent(state, f.event(9001), f.original);
        check("History budget fault rolls back receipt/RNG/commands and emits ownership cleanup only", fault.faulted && !fault.ok && fault.commands.size() == 1 &&
            std::holds_alternative<ActCleanup>(fault.commands[0].payload) && checkpoint(state) == saved &&
            fault.candidate.acceptedEventReceipts.size() == 1 && !fault.candidate.rememberedEvents.count(9001) &&
            fault.candidate.random.snapshot() == state.random.snapshot());
        auto invalid = saved; invalid["accepted_event_receipts"] = Json::array();
        check("Complete receipt coverage cannot omit a remembered event", !recover(compiled.program, invalid, f.original).ok);
        invalid = saved; invalid["accepted_event_receipts"].push_back(invalid["accepted_event_receipts"][0]);
        check("Duplicate or over-budget receipt count rejects", !recover(compiled.program, invalid, f.original).ok);
        auto bytesState = bindActProgram(proc.program, f.request(), f.original).state;
        auto bytes = checkpoint(bytesState); bytes["remembered_events"] = Json::array(); bytes["accepted_event_receipts"] = Json::array();
        for (uint64_t i = 1; i <= 70; ++i) {
            auto receipt = snapshotActEventReceipt({f.event(i), {{"future_padding", std::string(61000, 'x')}}});
            bytes["remembered_events"].push_back({{"id", i}, {"fingerprint", receipt.at("fingerprint")}});
            bytes["accepted_event_receipts"].push_back(std::move(receipt));
        }
        check("Aggregate per-instance receipt byte overflow rejects", !recover(proc.program, bytes, f.original).ok);
        auto collision = saved; collision["schema"] = 1; collision["event_receipt_coverage"] = {{"unknown_legacy", true}};
        const auto legacy = recover(compiled.program, collision, f.original);
        check("Legacy colliding extension fields are preserved under an explicit envelope", legacy.ok &&
            checkpoint(legacy.state).at("legacy_event_receipt_extension_fields").at("fields").at("event_receipt_coverage") == collision.at("event_receipt_coverage"));
    });
    report["passed"] = passed; report["failed"] = failed;
    return report;
}
} // namespace dnf
