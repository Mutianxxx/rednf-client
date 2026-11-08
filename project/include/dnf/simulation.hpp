#pragma once
#include "resources.hpp"
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <tuple>
#include <utility>

namespace dnf {
// Reconstruction contracts from plan D01/D02/D15. These helpers have no
// dependency on SDL, a wall clock, rendering, filesystem paths or native RNG.
struct SimulationStep {
    uint64_t tick = 0;
    uint64_t milliseconds = 0;
    uint32_t deltaMilliseconds = 0; // The original 60 Hz boundary: 16/17 ms.
};

class FixedStepClock {
    uint64_t tick_ = 0, units_ = 0;

  public:
    static constexpr uint64_t frequency = 60;
    static constexpr uint64_t unitsPerTick = 1000000000;
    void addNanoseconds(int64_t elapsedNanoseconds);
    // Each pop is exactly one real simulation tick. Callers may budget pops;
    // unprocessed ticks remain in units_, including across serialization.
    std::optional<SimulationStep> popTick();
    uint64_t tick() const { return tick_; }
    uint64_t pendingTicks() const { return units_ / unitsPerTick; }
    uint64_t accumulatedUnits() const { return units_; }
    double alpha() const { return double(units_ % unitsPerTick) / double(unitsPerTick); }
    uint64_t milliseconds() const { return millisecondsAtTick(tick_); }
    static uint64_t millisecondsAtTick(uint64_t tick);
    // ceil(ns * 60 / 1e9), evaluated without an overflowing product. An input
    // at time zero is due on the first tick, as in the existing World queue.
    static uint64_t targetTickForNanoseconds(int64_t nanoseconds);
    Json snapshot() const;
    void restore(const Json &state);
};

// Zero is reserved. After allocating UINT64_MAX the source is exhausted;
// its persisted next value is zero. Exhaustion can never wrap back to one.
class MonotonicIds {
    uint64_t next_ = 1;

  public:
    explicit MonotonicIds(uint64_t next = 1) : next_(next) {}
    uint64_t next();
    uint64_t nextValue() const { return next_; }
    // Used by an explicit legacy migration/replay; never lowers the source.
    void reserveThrough(uint64_t allocated);
    // Merge allocation history without replaying it. Zero is the terminal
    // exhausted watermark, so either exhausted input keeps the result zero.
    // This does not allocate an ID; UINT64_MAX remains available exactly once.
    void merge(const MonotonicIds &other) noexcept;
    // Validate a complete serialized watermark before changing this source.
    void merge(const Json &state);
    Json snapshot() const;
    void restore(const Json &state);
};

struct SimulationIdSources {
    MonotonicIds actions, attacks, requests, events;
    Json snapshot() const;
    void restore(const Json &state);
};

struct EntityHandle {
    uint64_t id = 0;
    uint32_t generation = 0;
    explicit operator bool() const { return id != 0 && generation != 0; }
    bool operator==(EntityHandle other) const { return id == other.id && generation == other.generation; }
    bool operator!=(EntityHandle other) const { return !(*this == other); }
    bool operator<(EntityHandle other) const {
        return std::tie(id, generation) < std::tie(other.id, other.generation);
    }
    Json json() const;
    static EntityHandle fromJson(const Json &value);
};

// Identity validity only; entity storage and ownership remain in World and
// ObjectSystem. No long-lived entity pointer is stored by this registry.
class EntityRegistry {
    struct Entry { uint32_t generation = 1; bool live = true; };
    MonotonicIds ids_;
    std::map<uint64_t, Entry> entries_;

  public:
    EntityHandle create();
    bool valid(EntityHandle handle) const;
    bool retire(EntityHandle handle);
    // A new incarnation of a still registered entity invalidates the old
    // generation. Retired handles cannot be resurrected with this API.
    EntityHandle renew(EntityHandle handle);
    void retireAll();
    std::vector<EntityHandle> active() const; // Stable ascending identity order.
    Json snapshot() const;
    void restore(const Json &state);
    // After restoring a private checkpoint candidate, retain the live
    // registry's allocation history before retiring saved incarnations and
    // creating new ones. Saved entries, generations and live flags are not
    // merged or revived by this operation; only the next-ID watermark moves.
    void mergeAllocationWatermark(const EntityRegistry &other) noexcept;
};

// The queue supplies ordering, not gameplay eligibility or action buffering.
// Skill/weapon/MP/CD qualification must still be checked when a command runs.
template <class Payload> struct SequencedCommand {
    uint64_t sequence = 0, targetTick = 0;
    Payload payload;
};

template <class Payload> class SequencedCommandQueue {
    MonotonicIds sequences_;
    std::map<std::pair<uint64_t, uint64_t>, Payload> pending_;

  public:
    uint64_t enqueue(uint64_t targetTick, Payload payload) {
        const auto sequence = sequences_.next();
        pending_.emplace(std::make_pair(targetTick, sequence), std::move(payload));
        return sequence;
    }
    // Replay records are supplied in their recorded acceptance order. Future
    // target ticks may be out of order; duplicate/old sequences are rejected.
    void appendReplay(SequencedCommand<Payload> command) {
        if (!command.sequence || !sequences_.nextValue() || command.sequence < sequences_.nextValue())
            throw std::invalid_argument("Replay command sequence is stale or exhausted");
        sequences_.reserveThrough(command.sequence);
        pending_.emplace(std::make_pair(command.targetTick, command.sequence), std::move(command.payload));
    }
    std::optional<SequencedCommand<Payload>> popDue(uint64_t tick) {
        if (pending_.empty() || pending_.begin()->first.first > tick) return std::nullopt;
        auto it = pending_.begin();
        SequencedCommand<Payload> result{it->first.second, it->first.first, std::move(it->second)};
        pending_.erase(it);
        return result;
    }
    size_t size() const { return pending_.size(); }
    uint64_t nextSequence() const { return sequences_.nextValue(); }
    // Scene/input-mode cleanup must not reset the persisted sequence source.
    void clear() { pending_.clear(); }
    template <class Encode> Json snapshot(Encode encode) const {
        Json commands = Json::array();
        for (const auto &entry : pending_)
            commands.push_back({{"sequence", entry.first.second}, {"target_tick", entry.first.first},
                                {"payload", encode(entry.second)}});
        return {{"schema", 1}, {"sequences", sequences_.snapshot()}, {"pending", commands}};
    }
    template <class Decode> void restore(const Json &state, Decode decode) {
        if (!state.is_object() || !state.contains("schema") || !state.at("schema").is_number_integer() ||
            state.at("schema") != 1 || !state.at("pending").is_array())
            throw std::invalid_argument("Invalid command queue checkpoint");
        SequencedCommandQueue next;
        next.sequences_.restore(state.at("sequences"));
        std::set<uint64_t> seen;
        for (const auto &command : state.at("pending")) {
            auto number = [&](const char *key) -> uint64_t {
                const auto &value = command.at(key);
                if (!value.is_number_unsigned() && (!value.is_number_integer() || value.template get<int64_t>() < 0))
                    throw std::invalid_argument("Invalid command queue integer");
                return value.template get<uint64_t>();
            };
            const auto sequence = number("sequence"), target = number("target_tick");
            if (!sequence || (next.sequences_.nextValue() && sequence >= next.sequences_.nextValue()) ||
                !seen.insert(sequence).second)
                throw std::invalid_argument("Invalid command queue sequence watermark");
            next.pending_.emplace(std::make_pair(target, sequence), decode(command.at("payload")));
        }
        *this = std::move(next);
    }
};

// PCG XSH-RR 64/32, standard two-step seeding, explicit unsigned wraparound.
// This is a versioned beta reconstruction, not the original client's RNG.
class Pcg32 {
    uint64_t state_ = 0, increment_ = 1, draws_ = 0;
    uint32_t step();

  public:
    explicit Pcg32(uint64_t seed = 0, uint64_t sequence = 1);
    uint32_t next();
    uint32_t bounded(uint32_t exclusiveUpperBound);
    uint64_t bounded64(uint64_t exclusiveUpperBound);
    int32_t uniformInt32(int32_t lowerInclusive, int32_t upperInclusive);
    uint64_t draws() const { return draws_; }
    Json snapshot() const;
    void restore(const Json &state);
};

enum class RandomDomain : uint8_t { WorldGeneration, Ai, Combat, Loot, Particles, Audio, MonsterEventAi, MonsterHurt, HitPresentation, HitReaction };
const char *randomDomainName(RandomDomain domain);

class RandomStreams {
    friend class PendingRewardService;
    uint64_t runSeed_ = 0;
    std::map<std::pair<RandomDomain, uint64_t>, Pcg32> streams_;
    // Prepared reward batches publish Loot alone, preserving references to
    // existing named streams. Called only after source/World preflight.
    void publishPreparedLoot(RandomStreams &&prepared) noexcept;

  public:
    explicit RandomStreams(uint64_t runSeed = 0) : runSeed_(runSeed) {}
    // Instance IDs allow independent actors to consume independent streams.
    // References remain stable until checkpoint restore replaces the bank.
    Pcg32 &stream(RandomDomain domain, uint64_t instance = 0);
    // Source audio is prepared on a value copy. Preserve other domain nodes
    // and references when publishing only accepted audio choices.
    void publishPreparedAudio(RandomStreams &&prepared) noexcept;
    uint64_t runSeed() const { return runSeed_; }
    Json snapshot() const;
    void restore(const Json &state);
};
} // namespace dnf
