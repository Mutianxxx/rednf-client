#include "dnf/simulation.hpp"
#include <type_traits>
#include <cstring>

namespace dnf {
namespace {
constexpr const char *pcgAlgorithm = "pcg32-xsh-rr-64-32-v1";
constexpr const char *seedDerivation = "fnv1a64-le-domain-instance-v1";

uint64_t unsignedField(const Json &state, const char *key, uint64_t maximum = UINT64_MAX) {
    if (!state.is_object() || !state.contains(key))
        throw std::invalid_argument(std::string("Missing simulation checkpoint field: ") + key);
    const auto &value = state.at(key);
    if (!value.is_number_unsigned() && (!value.is_number_integer() || value.get<int64_t>() < 0))
        throw std::invalid_argument(std::string("Invalid simulation checkpoint integer: ") + key);
    const uint64_t result = value.get<uint64_t>();
    if (result > maximum) throw std::invalid_argument(std::string("Simulation checkpoint integer out of range: ") + key);
    return result;
}

void schemaOne(const Json &state) {
    if (unsignedField(state, "schema") != 1) throw std::invalid_argument("Unsupported simulation checkpoint schema");
}

// FNV-1a 64, fixed ASCII prefix and domain, length-prefixed domain, and little
// endian seed/instance integers. No locale, std::hash or native byte order.
uint64_t deriveSeed(uint64_t runSeed, RandomDomain domain, uint64_t instance, uint8_t tag) {
    uint64_t hash = UINT64_C(14695981039346656037);
    auto byte = [&](uint8_t b) { hash = (hash ^ b) * UINT64_C(1099511628211); };
    auto littleEndian = [&](uint64_t value, unsigned count) {
        for (unsigned i = 0; i < count; ++i) byte(uint8_t(value >> (i * 8)));
    };
    const char *prefix = "dnf-pcg32-domain-v1";
    for (const char *p = prefix; *p; ++p) byte(uint8_t(*p));
    byte(tag);
    littleEndian(runSeed, 8);
    const char *name = randomDomainName(domain);
    littleEndian(std::strlen(name), 4);
    for (const char *p = name; *p; ++p) byte(uint8_t(*p));
    littleEndian(instance, 8);
    return hash;
}

RandomDomain parseDomain(const Json &value) {
    if (!value.is_string()) throw std::invalid_argument("Invalid random stream domain");
    const auto name = value.get<std::string>();
    for (auto domain : {RandomDomain::WorldGeneration, RandomDomain::Ai, RandomDomain::Combat,
                        RandomDomain::Loot, RandomDomain::Particles, RandomDomain::Audio, RandomDomain::MonsterEventAi, RandomDomain::MonsterHurt, RandomDomain::HitPresentation, RandomDomain::HitReaction})
        if (name == randomDomainName(domain)) return domain;
    throw std::invalid_argument("Unknown random stream domain: " + name);
}
} // namespace

void FixedStepClock::addNanoseconds(int64_t elapsedNanoseconds) {
    if (elapsedNanoseconds < 0) throw std::invalid_argument("Negative simulation elapsed time");
    const uint64_t elapsed = uint64_t(elapsedNanoseconds);
    if (elapsed > (UINT64_MAX - units_) / frequency) throw std::overflow_error("Simulation accumulator overflow");
    units_ += elapsed * frequency;
}

std::optional<SimulationStep> FixedStepClock::popTick() {
    if (units_ < unitsPerTick) return std::nullopt;
    if (tick_ == UINT64_MAX) throw std::overflow_error("Simulation tick overflow");
    const uint64_t nextTick = tick_ + 1;
    const uint64_t before = millisecondsAtTick(tick_), after = millisecondsAtTick(nextTick);
    SimulationStep step{nextTick, after, uint32_t(after - before)};
    units_ -= unitsPerTick;
    tick_ = nextTick;
    return step;
}

uint64_t FixedStepClock::millisecondsAtTick(uint64_t tick) {
    const uint64_t seconds = tick / frequency, fraction = (tick % frequency) * 1000 / frequency;
    if (seconds > (UINT64_MAX - fraction) / 1000) throw std::overflow_error("Simulation millisecond overflow");
    return seconds * 1000 + fraction;
}

uint64_t FixedStepClock::targetTickForNanoseconds(int64_t nanoseconds) {
    if (nanoseconds < 0) throw std::invalid_argument("Negative input simulation timestamp");
    const uint64_t ns = uint64_t(nanoseconds);
    const uint64_t whole = (ns / unitsPerTick) * frequency;
    const uint64_t fraction = (ns % unitsPerTick) * frequency;
    return whole + fraction / unitsPerTick + (fraction % unitsPerTick != 0);
}

Json FixedStepClock::snapshot() const {
    return {{"schema", 1}, {"frequency", frequency}, {"tick", tick_}, {"accumulated_units", units_}};
}

void FixedStepClock::restore(const Json &state) {
    schemaOne(state);
    if (unsignedField(state, "frequency") != frequency) throw std::invalid_argument("Unsupported simulation frequency");
    const auto tick = unsignedField(state, "tick"), units = unsignedField(state, "accumulated_units");
    millisecondsAtTick(tick); // Validate every stored time before mutation.
    tick_ = tick;
    units_ = units;
}

uint64_t MonotonicIds::next() {
    if (!next_) throw std::overflow_error("Simulation identity source exhausted");
    const uint64_t result = next_;
    next_ = result == UINT64_MAX ? 0 : result + 1;
    return result;
}

void MonotonicIds::reserveThrough(uint64_t allocated) {
    if (next_ && allocated >= next_) next_ = allocated == UINT64_MAX ? 0 : allocated + 1;
}
void MonotonicIds::merge(const MonotonicIds &other) noexcept {
    next_ = next_ && other.next_ ? std::max(next_, other.next_) : 0;
}
void MonotonicIds::merge(const Json &state) {
    MonotonicIds candidate;
    candidate.restore(state);
    merge(candidate);
}

Json MonotonicIds::snapshot() const { return {{"schema", 1}, {"next", next_}}; }
void MonotonicIds::restore(const Json &state) { schemaOne(state); next_ = unsignedField(state, "next"); }

Json SimulationIdSources::snapshot() const {
    return {{"schema", 1}, {"actions", actions.snapshot()}, {"attacks", attacks.snapshot()},
            {"requests", requests.snapshot()}, {"events", events.snapshot()}};
}
void SimulationIdSources::restore(const Json &state) {
    schemaOne(state);
    SimulationIdSources next;
    next.actions.restore(state.at("actions"));
    next.attacks.restore(state.at("attacks"));
    next.requests.restore(state.at("requests"));
    next.events.restore(state.at("events"));
    *this = std::move(next);
}

Json EntityHandle::json() const { return {{"id", id}, {"generation", generation}}; }
EntityHandle EntityHandle::fromJson(const Json &value) {
    const auto id = unsignedField(value, "id"), generation = unsignedField(value, "generation", UINT32_MAX);
    if ((id == 0) != (generation == 0)) throw std::invalid_argument("Incomplete entity handle");
    return {id, uint32_t(generation)};
}

EntityHandle EntityRegistry::create() {
    const auto id = ids_.next();
    entries_.emplace(id, Entry{});
    return {id, 1};
}
bool EntityRegistry::valid(EntityHandle handle) const {
    const auto found = entries_.find(handle.id);
    return bool(handle) && found != entries_.end() && found->second.live && found->second.generation == handle.generation;
}
bool EntityRegistry::retire(EntityHandle handle) {
    if (!valid(handle)) return false;
    auto &entry = entries_.at(handle.id);
    entry.live = false;
    if (entry.generation != UINT32_MAX) ++entry.generation;
    return true;
}
EntityHandle EntityRegistry::renew(EntityHandle handle) {
    if (!valid(handle)) throw std::invalid_argument("Cannot renew stale entity handle");
    auto &entry = entries_.at(handle.id);
    if (entry.generation == UINT32_MAX) throw std::overflow_error("Entity generation exhausted");
    return {handle.id, ++entry.generation};
}
void EntityRegistry::retireAll() {
    for (auto &entry : entries_) if (entry.second.live) retire({entry.first, entry.second.generation});
}
std::vector<EntityHandle> EntityRegistry::active() const {
    std::vector<EntityHandle> result;
    for (const auto &entry : entries_) if (entry.second.live) result.push_back({entry.first, entry.second.generation});
    return result;
}
Json EntityRegistry::snapshot() const {
    Json entries = Json::array();
    for (const auto &entry : entries_)
        entries.push_back({{"id", entry.first}, {"generation", entry.second.generation}, {"live", entry.second.live}});
    return {{"schema", 1}, {"ids", ids_.snapshot()}, {"entries", entries}};
}
void EntityRegistry::restore(const Json &state) {
    schemaOne(state);
    EntityRegistry next;
    next.ids_.restore(state.at("ids"));
    const auto &entries = state.at("entries");
    if (!entries.is_array()) throw std::invalid_argument("Invalid entity registry entries");
    for (const auto &value : entries) {
        const auto handle = EntityHandle::fromJson(value);
        if (!handle || !value.at("live").is_boolean() ||
            (next.ids_.nextValue() && handle.id >= next.ids_.nextValue()) ||
            !next.entries_.emplace(handle.id, Entry{handle.generation, value.at("live").get<bool>()}).second)
            throw std::invalid_argument("Invalid entity registry identity watermark");
    }
    *this = std::move(next);
}
void EntityRegistry::mergeAllocationWatermark(const EntityRegistry &other) noexcept {
    ids_.merge(other.ids_);
}

Pcg32::Pcg32(uint64_t seed, uint64_t sequence) : increment_((sequence << 1u) | 1u) {
    step();
    state_ += seed;
    step();
}
uint32_t Pcg32::step() {
    const uint64_t old = state_;
    state_ = old * UINT64_C(6364136223846793005) + increment_;
    const uint32_t shifted = uint32_t(((old >> 18u) ^ old) >> 27u), rotation = uint32_t(old >> 59u);
    return (shifted >> rotation) | (shifted << ((0u - rotation) & 31u));
}
uint32_t Pcg32::next() {
    if (draws_ == UINT64_MAX) throw std::overflow_error("Random draw counter exhausted");
    ++draws_;
    return step();
}
uint32_t Pcg32::bounded(uint32_t exclusiveUpperBound) {
    if (!exclusiveUpperBound) throw std::invalid_argument("Random range must not be empty");
    const uint32_t threshold = (uint32_t(0) - exclusiveUpperBound) % exclusiveUpperBound;
    for (;;) { const auto value = next(); if (value >= threshold) return value % exclusiveUpperBound; }
}
uint64_t Pcg32::bounded64(uint64_t exclusiveUpperBound) {
    if (!exclusiveUpperBound) throw std::invalid_argument("Random range must not be empty");
    const uint64_t threshold = (uint64_t(0) - exclusiveUpperBound) % exclusiveUpperBound;
    for (;;) {
        if (draws_ > UINT64_MAX - 2) throw std::overflow_error("Random draw counter exhausted");
        // Explicit high-word-first ordering, independent of host endianness.
        const uint64_t high = next(), low = next(), value = (high << 32) | low;
        if (value >= threshold) return value % exclusiveUpperBound;
    }
}
int32_t Pcg32::uniformInt32(int32_t lowerInclusive, int32_t upperInclusive) {
    if (lowerInclusive > upperInclusive) throw std::invalid_argument("Inverted random integer range");
    const uint64_t width = uint64_t(int64_t(upperInclusive) - int64_t(lowerInclusive)) + 1;
    const uint32_t offset = width == (UINT64_C(1) << 32) ? next() : bounded(uint32_t(width));
    return int32_t(int64_t(lowerInclusive) + int64_t(offset));
}
Json Pcg32::snapshot() const {
    return {{"schema", 1}, {"algorithm", pcgAlgorithm}, {"state", state_}, {"increment", increment_}, {"draws", draws_}};
}
void Pcg32::restore(const Json &state) {
    schemaOne(state);
    if (state.at("algorithm") != pcgAlgorithm) throw std::invalid_argument("Unsupported random algorithm");
    const auto nextState = unsignedField(state, "state"), increment = unsignedField(state, "increment"),
               draws = unsignedField(state, "draws");
    if (!(increment & 1)) throw std::invalid_argument("PCG increment must be odd");
    state_ = nextState;
    increment_ = increment;
    draws_ = draws;
}

const char *randomDomainName(RandomDomain domain) {
    switch (domain) {
    case RandomDomain::WorldGeneration: return "world";
    case RandomDomain::Ai: return "ai";
    case RandomDomain::Combat: return "combat";
    case RandomDomain::Loot: return "loot";
    case RandomDomain::Particles: return "particles";
    case RandomDomain::Audio: return "audio";
    case RandomDomain::MonsterEventAi: return "monster_event_ai";
    case RandomDomain::MonsterHurt: return "monster_hurt";
    case RandomDomain::HitPresentation: return "hit_presentation";
    case RandomDomain::HitReaction: return "hit_reaction";
    }
    throw std::invalid_argument("Unknown random domain value");
}
Pcg32 &RandomStreams::stream(RandomDomain domain, uint64_t instance) {
    randomDomainName(domain); // Invalid enum values cannot silently form a stream.
    const auto key = std::make_pair(domain, instance);
    auto found = streams_.find(key);
    if (found == streams_.end())
        found = streams_.emplace(key, Pcg32(deriveSeed(runSeed_, domain, instance, 0),
                                           deriveSeed(runSeed_, domain, instance, 1))).first;
    return found->second;
}
Json RandomStreams::snapshot() const {
    Json streams = Json::array();
    for (const auto &entry : streams_)
        streams.push_back({{"domain", randomDomainName(entry.first.first)}, {"instance", entry.first.second},
                           {"rng", entry.second.snapshot()}});
    return {{"schema", 1}, {"algorithm", pcgAlgorithm}, {"derivation", seedDerivation},
            {"run_seed", runSeed_}, {"streams", streams}};
}
void RandomStreams::publishPreparedAudio(RandomStreams &&prepared) noexcept {
    static_assert(std::is_nothrow_copy_assignable<Pcg32>::value,"Audio random publication must not throw");
    for(auto it=prepared.streams_.begin();it!=prepared.streams_.end();) {
        if(it->first.first!=RandomDomain::Audio){++it;continue;}
        const auto selected=it++;auto node=prepared.streams_.extract(selected);
        const auto existing=streams_.find(node.key());
        if(existing==streams_.end())streams_.insert(std::move(node));else existing->second=node.mapped();
    }
}
void RandomStreams::restore(const Json &state) {
    schemaOne(state);
    if (state.at("algorithm") != pcgAlgorithm || state.at("derivation") != seedDerivation || !state.at("streams").is_array())
        throw std::invalid_argument("Unsupported random stream checkpoint");
    RandomStreams next(unsignedField(state, "run_seed"));
    for (const auto &entry : state.at("streams")) {
        const auto key = std::make_pair(parseDomain(entry.at("domain")), unsignedField(entry, "instance"));
        Pcg32 random;
        random.restore(entry.at("rng"));
        if (!next.streams_.emplace(key, random).second) throw std::invalid_argument("Duplicate random stream identity");
    }
    *this = std::move(next);
}
} // namespace dnf
