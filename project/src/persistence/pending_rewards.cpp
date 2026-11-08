#include "dnf/pending_rewards.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <climits>
#include <cmath>
#include <limits>
#include <set>
#include <type_traits>

namespace dnf {
namespace {
uint64_t number(const Json &value, uint64_t maximum, const char *name) {
    uint64_t result;
    if (value.is_number_unsigned()) result = value.get<uint64_t>();
    else if (value.is_number_integer() && value.get<int64_t>() >= 0) result = uint64_t(value.get<int64_t>());
    else throw std::runtime_error(std::string("Invalid pending reward integer: ") + name);
    if (result > maximum) throw std::runtime_error(std::string("Pending reward integer overflow: ") + name);
    return result;
}
int count(const Json &value, const char *name, int minimum = 0) {
    const auto result = number(value, INT_MAX, name);
    if (result < uint64_t(minimum)) throw std::runtime_error(std::string("Pending reward integer below minimum: ") + name);
    return int(result);
}
std::string string(const Json &value, const char *name) {
    if (!value.is_string() || value.get_ref<const std::string &>().empty())
        throw std::runtime_error(std::string("Missing pending reward string: ") + name);
    return value.get<std::string>();
}
Json emptyLedger() {
    return {{"schema", 1}, {"policy", PendingRewardService::policy}, {"next_sequence", uint64_t(1)},
            {"kills", Json::object()}, {"clears", Json::object()}, {"origins", Json::object()},
            {"completed_kills", Json::object()}, {"completed_clears", Json::object()}};
}
void validateLedger(const Json &value) {
    if (!value.is_object() || !value.contains("schema") || count(value.at("schema"), "schema") != 1 ||
        value.at("policy") != PendingRewardService::policy)
        throw std::runtime_error("Unsupported or malformed pending reward namespace; raw data retained");
    for (const char *key : {"kills", "clears", "origins"})
        if (!value.at(key).is_object()) throw std::runtime_error(std::string("Invalid pending reward container: ") + key);
    for (const char *key : {"completed_kills", "completed_clears"})
        if (value.contains(key) && !value.at(key).is_object()) throw std::runtime_error(std::string("Invalid completed reward archive: ") + key);
    const auto next = number(value.at("next_sequence"), UINT64_MAX, "next_sequence");
    std::set<uint64_t> sequences;
    for (auto it = value.at("kills").begin(); it != value.at("kills").end(); ++it) {
        if (!it.value().is_object() || it.key().empty()) throw std::runtime_error("Invalid pending kill row");
        const auto sequence = number(it.value().at("sequence"), UINT64_MAX, "sequence");
        if (!sequence || (next && sequence >= next) || !sequences.insert(sequence).second)
            throw std::runtime_error("Invalid pending kill sequence/watermark");
    }
    for (auto it = value.at("clears").begin(); it != value.at("clears").end(); ++it)
        if (!it.value().is_object() || it.key().empty()) throw std::runtime_error("Invalid pending clear row");
}
const Json *ledger(const Progression &progress) {
    const auto found = progress.state.find("pending_rewards");
    if (found == progress.state.end()) return nullptr; // Explicit old-save migration.
    validateLedger(*found);
    return &*found;
}
std::string keyFor(const std::string &run, int room, int actor) {
    return run + ":" + std::to_string(room) + ":" + std::to_string(actor);
}
void mergeObject(Json &destination, const Json &known) {
    if (destination.is_null()) destination = Json::object();
    if (!destination.is_object()) throw std::runtime_error("Pending origin is malformed; raw data retained");
    for (auto it = known.begin(); it != known.end(); ++it) destination[it.key()] = it.value();
}
const Json &source(const DungeonDefinition &dungeon) {
    if (!dungeon.source.source.is_object()) throw std::runtime_error("Pending dungeon source identity is malformed");
    return dungeon.source.source;
}
void validateSource(const Json &row, const DungeonDefinition &definition) {
    if (row.at("source") != source(definition) ||
        normalize(string(row.at("dungeon_path"), "dungeon_path")) != normalize(definition.path) ||
        string(row.at("package_identity"), "package_identity") !=
            string(source(definition).at("package_identity"), "current package_identity") ||
        count(row.at("basis_level"), "basis_level", 1) != definition.basisLevel)
        throw std::runtime_error("Pending reward belongs to different dungeon/PVF source; original intent retained");
}
const Json &actorEvidence(const Json &origin, int room, int actor) {
    const auto &states = origin.at("session").at("room_states");
    if (!states.is_array() || size_t(room) >= states.size() || !states.at(room).is_array())
        throw std::runtime_error("Pending kill has no frozen room actor evidence");
    const Json *found = nullptr;
    for (const auto &row : states.at(room))
        if (count(row.at("id"), "actor id") == actor) {
            if (found) throw std::runtime_error("Ambiguous pending kill actor identity");
            found = &row;
        }
    if (!found) throw std::runtime_error("Pending kill actor absent from frozen origin");
    return *found;
}
void validateReceipt(const Progression &progress, const std::string &key, const Json &row) {
    const auto &event = progress.state.at("events").at(key);
    const auto &drop = progress.state.at("drops").at(key);
    if (!event.is_object() || !drop.is_object() || event.at("dungeon") != row.at("dungeon") ||
        event.at("monster") != row.at("monster") || drop.at("monster") != row.at("monster") ||
        drop.at("seed") != row.at("seed") || drop.at("run") != row.at("run") || drop.at("room") != row.at("room") ||
        drop.at("x") != row.at("position").at(0) || drop.at("y") != row.at("position").at(1) ||
        !drop.at("claimed").is_boolean() || !drop.at("items").is_array() ||
        drop.at("random_policy") != "pcg32-loot-legacy-reward-selection-v1")
        throw std::runtime_error("Pending kill conflicts with durable event/drop receipt: " + key);
    Pcg32 before, after; before.restore(drop.at("random_before")); after.restore(drop.at("random_after"));
    if (after.draws() < before.draws()) throw std::runtime_error("Pending drop RNG receipt moved backwards: " + key);
    count(drop.at("gold"), "drop gold");
    for (const auto &item : drop.at("items")) {
        count(item.at("id"), "drop item", 1); count(item.at("count"), "drop quantity", 1);
    }
}
const Json &committedCharacter(const CharacterStore &writer,int slot) {
    if(writer.hasPendingCommit())throw std::runtime_error("Checkpoint writer still has an uncommitted candidate");
    const auto &root=writer.committedSnapshot();
    if(!root.is_object()||!writer.generation()||root.at("_storage").at("generation")!=writer.generation()||
        root.at("_storage").at("content_identity")!=writer.contentIdentity()||slot<0||
        !root.at("characters").is_array()||size_t(slot)>=root.at("characters").size())
        throw std::runtime_error("Checkpoint writer has no matching committed root/slot");
    const auto &saved=root.at("characters").at(slot);
    if(!saved.is_object()||!saved.contains("uuid")||!saved.at("uuid").is_string()||saved.at("uuid").get_ref<const std::string &>().empty())
        throw std::runtime_error("Checkpoint writer has no durable character UUID");
    return saved;
}
Json writerContext(const CharacterStore &writer,int slot,const Json &saved) {
    return {{"directory",writer.directory().generic_u8string()},{"content_identity",writer.contentIdentity()},
        {"slot",slot},{"character_uuid",saved.at("uuid")}};
}
void requireSnapshot(const Progression &progress,const World &world,const Json &saved) {
    if(!(CharacterIdentity::fromJson(saved.at("identity"))==world.identity())||saved.at("progression")!=progress.state||
        saved.at("simulation").at("random")!=world.randomStreams().snapshot()||
        saved.at("simulation").at("clock")!=world.simulationCheckpoint().at("clock"))
        throw std::runtime_error("Committed character does not match current reward/progression/RNG/clock snapshot");
}
} // namespace

void PendingRewardService::fail(const char *phase, const std::string &error) {
    diagnostic_ = {{"status", "blocked"}, {"phase", phase}, {"error", error},
                   {"event_cursor", eventCursor_}, {"needs_checkpoint", dirty_},
                   {"durable_generation", durableGeneration_}, {"policy", policy}};
}
void PendingRewardService::characterBoundary(const World &world) {
    eventCursor_ = world.events.size(); dirty_ = false; captureFailed_ = false;
    durableGeneration_ = 0;checkpointWriter_=Json();diagnostic_ = Json::object();
}
bool PendingRewardService::hasPending(const Progression &progress) const {
    const auto *pending = ledger(progress);
    return pending && (!pending->at("kills").empty() || !pending->at("clears").empty());
}
bool PendingRewardService::blocked(const Progression &progress) const {
    try { return dirty_ || captureFailed_ || hasPending(progress); }
    catch (const std::exception &) { return true; }
}
bool PendingRewardService::observe(Progression &progress, const World &world, const RegionSession &session,
                                   const Json &originSession) {
    try {
        (void)ledger(progress);
        if (eventCursor_ > world.events.size())
            throw std::runtime_error("World event history shrank before reward capture");
        if (!session.active()) {
            // Map exploration is explicitly not a registered rewarded run.
            // Main captures before every registered-run scene publication.
            eventCursor_ = world.events.size(); captureFailed_ = false; return true;
        }
        Json next = progress.state;
        if (!next.contains("pending_rewards")) next["pending_rewards"] = emptyLedger();
        auto &pending = next.at("pending_rewards");
        const auto &run = session.run;
        const auto &definition = progress.catalog().dungeons.at(run.dungeonId);
        bool changed = false;
        const Json identity = {{"run", run.token}, {"dungeon", run.dungeonId}, {"dungeon_path", definition.path},
            {"basis_level", definition.basisLevel}, {"package_identity", source(definition).value("package_identity", Json())},
            {"source", source(definition)}};
        for (size_t i = eventCursor_; i < world.events.size(); ++i) {
            const auto &event = world.events[i];
            if (event.kind != "killed") continue;
            const auto key = keyFor(run.token, run.current, event.target);
            Json row = identity;
            row["room"] = run.current; row["actor"] = event.target; row["monster"] = event.value;
            row["event"] = {{"tick", event.tick}, {"kind", event.kind}, {"name", event.name},
                            {"source", event.source}, {"target", event.target}, {"value", event.value}};
            // Retain an invalid/missing actor as a diagnosable persistent intent;
            // never turn a source mismatch into an already-consumed event.
            row["actor_source"] = Json(); row["actor_path"] = Json(); row["handle"] = Json(); row["position"] = Json();
            int matches = 0;
            for (const auto &actor : world.monsters) if (actor.id == event.target) {
                ++matches; row["actor_source"] = actor.sourceId; row["actor_path"] = actor.monsterPath;
                row["handle"] = actor.handle.json(); row["position"] = Json::array({actor.x, actor.y});
            }
            row["actor_matches"] = matches;
            if (event.target < 0 || run.seed > UINT64_MAX - uint64_t(std::max(0, event.target))) row["seed"] = Json();
            else row["seed"] = run.seed + uint64_t(event.target);
            if (pending.at("kills").contains(key)) {
                const auto &previous = pending.at("kills").at(key);
                for (auto field = row.begin(); field != row.end(); ++field)
                    if (previous.at(field.key()) != field.value())
                        throw std::runtime_error("Pending kill identity collision: " + key);
                continue;
            }
            const auto sequence = number(pending.at("next_sequence"), UINT64_MAX, "next_sequence");
            if (!sequence) throw std::overflow_error("Pending reward sequence exhausted");
            row["sequence"] = sequence;
            pending["next_sequence"] = sequence == UINT64_MAX ? uint64_t(0) : sequence + 1;
            pending["kills"][key] = std::move(row); changed = true;
        }
        const bool nonemptyBoss = run.room().boss && run.current == run.boss && !world.monsters.empty() &&
            std::all_of(world.monsters.begin(), world.monsters.end(), [](const Actor &a) { return a.dead; });
        if (run.complete() && next.at("clears").contains(run.token)) {
            const auto &receipt = next.at("clears").at(run.token);
            const auto rooms = count(receipt.at("rooms"), "existing receipt rooms", 1);
            if (rooms > std::count_if(run.rooms.begin(), run.rooms.end(), [](const RunRoom &r) { return r.cleared; }) ||
                !progress.dungeonClearRecorded(run.dungeonId, run.token, rooms))
                throw std::runtime_error("Existing clear receipt conflicts with captured run: " + run.token);
        }
        if (nonemptyBoss && run.complete() && !next.at("clears").contains(run.token) && !pending.at("clears").contains(run.token)) {
            Json row = identity;
            row["rooms"] = std::count_if(run.rooms.begin(), run.rooms.end(), [](const RunRoom &r) { return r.cleared; });
            row["boss_room"] = run.boss; row["nonempty_boss"] = true;
            pending["clears"][run.token] = std::move(row); changed = true;
        }
        if (changed) {
            if (originSession.at("location") != "dungeon" || originSession.at("run").at("token") != run.token ||
                originSession.at("run").at("dungeon") != run.dungeonId)
                throw std::runtime_error("Reward capture does not match frozen region origin");
            // Preserve extensions on each origin; the full same-tick session is
            // retained independently of the later Seria login region_session.
            mergeObject(pending["origins"][run.token], {{"session", originSession},
                {"source", source(definition)}, {"simulation_clock", world.simulationCheckpoint().at("clock")}});
            validateLedger(pending);
            progress.state.swap(next); dirty_ = true;
        }
        eventCursor_ = world.events.size(); captureFailed_ = false;
        return true;
    } catch (const std::exception &error) { captureFailed_ = true; fail("capture", error.what()); return false; }
}
bool PendingRewardService::acknowledgeCheckpoint(const Progression &progress, const World &world,
                                                const CharacterStore &writer,int slot) {
    try {
        const auto &saved=committedCharacter(writer,slot);const auto context=writerContext(writer,slot,saved);
        if(!checkpointWriter_.is_null()&&context!=checkpointWriter_)
            throw std::runtime_error("Reward checkpoint belongs to a different writer; explicit clean handover required");
        const auto generation=writer.generation();
        if (!generation || generation < durableGeneration_ || (dirty_ && generation <= durableGeneration_) ||
            (checkpointWriter_.is_null()&&durableGeneration_))
            throw std::runtime_error("Reward checkpoint did not advance its bound writer generation");
        requireSnapshot(progress,world,saved);
        checkpointWriter_=context;dirty_ = false; durableGeneration_ = generation;
        return true;
    } catch (const std::exception &error) { fail("checkpoint-proof", error.what()); return false; }
}
bool PendingRewardService::switchCheckpointWriter(const Progression &progress,const World &world,const CharacterStore &writer,int slot) {
    try {
        if(blocked(progress))throw std::runtime_error("Complete pending rewards before changing checkpoint writer");
        const auto &saved=committedCharacter(writer,slot);auto context=writerContext(writer,slot,saved);
        requireSnapshot(progress,world,saved);
        if(context==checkpointWriter_)return acknowledgeCheckpoint(progress,world,writer,slot);
        checkpointWriter_=std::move(context);durableGeneration_=writer.generation();diagnostic_=Json::object();return true;
    }catch(const std::exception &error){fail("writer-handover",error.what());return false;}
}
bool PendingRewardService::releaseCheckpointWriter(const Progression &progress,const CharacterStore &writer,int slot) {
    try {
        if(blocked(progress))throw std::runtime_error("Complete pending rewards before releasing checkpoint writer");
        const auto &saved=committedCharacter(writer,slot);
        if(checkpointWriter_!=writerContext(writer,slot,saved))throw std::runtime_error("Cannot release a different checkpoint writer");
        checkpointWriter_=Json();durableGeneration_=0;diagnostic_=Json::object();return true;
    }catch(const std::exception &error){fail("writer-release",error.what());return false;}
}
bool PendingRewardService::prepareAndPublish(Progression &progress, World &world, RegionCatalog &catalog) {
    try {
        if (&progress.catalog() != &catalog) throw std::runtime_error("Pending reward catalog owner mismatch");
        if (captureFailed_) throw std::runtime_error("Capture must be retried before preparing rewards");
        if (dirty_) throw std::runtime_error("Reward intent/final result requires a durable same-generation checkpoint");
        const auto *current = ledger(progress);
        if (!current || (current->at("kills").empty() && current->at("clears").empty())) return true;
        if (!durableGeneration_) throw std::runtime_error("Pending rewards have no confirmed committed generation");
        Progression candidate(progress);
        RandomStreams random(world.randomStreams());
        // recordKill/clearDungeon swap candidate.state. Keep our work ledger
        // independent so no reference can dangle across those transactions.
        Json pending = candidate.state.at("pending_rewards");
        for (const char *key : {"completed_kills", "completed_clears"})
            if (!pending.contains(key)) pending[key] = Json::object();
        std::map<std::string, RegionSession> origins;
        auto requireOrigin = [&](const Json &row) -> const RegionSession & {
            const auto run = string(row.at("run"), "run");
            const int dungeon = count(row.at("dungeon"), "dungeon");
            auto found = origins.find(run);
            if (found == origins.end()) {
                const auto prepared = catalog.prepareDungeon(dungeon);
                if (prepared.at("status") != "prepared") throw std::runtime_error("Pending dungeon dependency preparation failed: " + prepared.dump());
                const auto &origin = pending.at("origins").at(run);
                if (origin.at("source") != row.at("source")) throw std::runtime_error("Pending origin source conflict");
                RegionSession restored;
                if (!restored.load(origin.at("session"), catalog) || restored.run.token != run || restored.run.dungeonId != dungeon)
                    throw std::runtime_error("Pending origin is not the captured source run");
                found = origins.emplace(run, std::move(restored)).first;
            }
            if (found->second.run.dungeonId != dungeon) throw std::runtime_error("Pending run/dungeon collision");
            validateSource(row, catalog.dungeons.at(dungeon));
            return found->second;
        };
        std::vector<std::pair<uint64_t, std::string>> order;
        for (auto it = pending.at("kills").begin(); it != pending.at("kills").end(); ++it)
            order.emplace_back(number(it.value().at("sequence"), UINT64_MAX, "sequence"), it.key());
        std::sort(order.begin(), order.end());
        for (const auto &entry : order) {
            const auto key = entry.second;
            const Json row = pending.at("kills").at(key);
            const auto &origin = requireOrigin(row);
            const auto run = string(row.at("run"), "run");
            const int room = count(row.at("room"), "room"), actor = count(row.at("actor"), "actor", 1);
            const int monster = count(row.at("monster"), "monster", 1);
            const auto seed = number(row.at("seed"), UINT64_MAX, "seed");
            if (key != keyFor(run, room, actor) || size_t(room) >= origin.run.rooms.size() ||
                origin.run.seed > UINT64_MAX - uint64_t(actor) || seed != origin.run.seed + uint64_t(actor) ||
                count(row.at("actor_matches"), "actor matches") != 1 || row.at("actor_source") != monster ||
                row.at("event").at("kind") != "killed" || row.at("event").at("target") != actor || row.at("event").at("value") != monster ||
                normalize(string(row.at("event").at("name"), "event path")) != normalize(catalog.monsterPath(monster)) ||
                normalize(string(row.at("actor_path"), "actor path")) != normalize(catalog.monsterPath(monster)))
                throw std::runtime_error("Pending kill source/actor/seed identity mismatch: " + key);
            number(row.at("event").at("tick"), UINT64_MAX, "event tick");
            const auto handle = EntityHandle::fromJson(row.at("handle"));
            const auto &position = row.at("position");
            if (!handle || !position.is_array() || position.size() != 2 || !position.at(0).is_number() || !position.at(1).is_number() ||
                !std::isfinite(position.at(0).get<double>()) || !std::isfinite(position.at(1).get<double>()))
                throw std::runtime_error("Pending kill lacks a stable handle/finite position: " + key);
            const auto &evidence = actorEvidence(pending.at("origins").at(run), room, actor);
            if (evidence.at("dead") != true || evidence.at("source_id") != monster || evidence.at("entity_handle") != row.at("handle") ||
                evidence.at("x") != position.at(0) || evidence.at("y") != position.at(1) || evidence.at("path") != row.at("actor_path"))
                throw std::runtime_error("Pending kill disagrees with frozen dead actor: " + key);
            const bool inserted = candidate.recordKill(origin.run.dungeonId, monster,
                count(row.at("basis_level"), "basis_level", 1), key, seed, &random);
            if (inserted) {
                auto &drop = candidate.state.at("drops").at(key);
                drop["x"] = position.at(0); drop["y"] = position.at(1); drop["run"] = run; drop["room"] = room;
            }
            validateReceipt(candidate, key, row); // false is success only with matching receipts.
            mergeObject(pending["completed_kills"][key], row);
            pending.at("kills").erase(key);
        }
        std::vector<std::string> clears;
        for (auto it = pending.at("clears").begin(); it != pending.at("clears").end(); ++it) clears.push_back(it.key());
        for (const auto &key : clears) {
            const Json row = pending.at("clears").at(key);
            const auto &origin = requireOrigin(row);
            const int boss = count(row.at("boss_room"), "boss_room");
            const int rooms = count(row.at("rooms"), "cleared rooms", 1);
            if (string(row.at("run"), "run") != key || row.at("nonempty_boss") != true ||
                boss != origin.run.boss || !origin.run.complete() ||
                rooms != std::count_if(origin.run.rooms.begin(), origin.run.rooms.end(), [](const RunRoom &r) { return r.cleared; }))
                throw std::runtime_error("Pending clear does not match completed captured run: " + key);
            const auto &actors = pending.at("origins").at(key).at("session").at("room_states").at(boss);
            if (!actors.is_array() || actors.empty() || !std::all_of(actors.begin(), actors.end(), [](const Json &a) { return a.at("dead") == true; }))
                throw std::runtime_error("Pending clear has no nonempty defeated boss evidence: " + key);
            (void)candidate.clearDungeon(origin.run.dungeonId, key, rooms);
            if (!candidate.dungeonClearRecorded(origin.run.dungeonId, key, rooms)) throw std::runtime_error("Pending clear produced no receipt");
            mergeObject(pending["completed_clears"][key], row);
            pending.at("clears").erase(key);
        }
        candidate.state.at("pending_rewards").swap(pending);
        if (random.runSeed() != world.randomStreams().runSeed()) throw std::runtime_error("Prepared reward RNG owner changed");
        // All throwing source/attribute preparations happen before either live
        // progression or Loot bank publication. This follows the existing
        // equipment preflight contract; it does not promise global bad_alloc
        // rollback for arbitrary external World/controller implementations.
        world.applyEquipment(candidate);
        progress.commitPrepared(std::move(candidate));
        world.randomStreams().publishPreparedLoot(std::move(random));
        dirty_ = true; diagnostic_ = {{"status", "awaiting-final-checkpoint"}, {"policy", policy}};
        return true;
    } catch (const std::exception &error) { fail("prepare", error.what()); return false; }
}
bool PendingRewardService::clearReceipt(const Progression &progress, const RegionSession &session) {
    try {
    if (!session.active() || !session.run.complete() || blocked(progress)) return false;
    const auto &clears = progress.state.at("clears");
    if (!clears.is_object()) throw std::runtime_error("Invalid clear ledger");
    const auto found = clears.find(session.run.token);
    if (found == clears.end()) return false;
    const int rooms = count(found->at("rooms"), "receipt rooms", 1);
    if (rooms > std::count_if(session.run.rooms.begin(), session.run.rooms.end(), [](const RunRoom &r) { return r.cleared; }))
        throw std::runtime_error("Clear receipt exceeds current completed room evidence");
    return progress.dungeonClearRecorded(session.run.dungeonId, session.run.token, rooms);
    } catch (const std::exception &error) {
        captureFailed_ = true; fail("clear-receipt", error.what()); return false;
    }
}

// Move only Loot nodes. std::allocator node transfer allocates nothing and the
// key comparator compares two integral fields. Existing AI and Loot references
// retain their addresses; no whole-bank restore or assignment occurs here.
void RandomStreams::publishPreparedLoot(RandomStreams &&prepared) noexcept {
    static_assert(std::is_nothrow_copy_assignable<Pcg32>::value, "Prepared Loot publication must not throw");
    for (auto it = prepared.streams_.begin(); it != prepared.streams_.end();) {
        if (it->first.first != RandomDomain::Loot) { ++it; continue; }
        const auto selected = it++;
        auto node = prepared.streams_.extract(selected);
        const auto existing = streams_.find(node.key());
        if (existing == streams_.end()) streams_.insert(std::move(node));
        else existing->second = node.mapped();
    }
}
} // namespace dnf
