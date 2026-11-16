#pragma once
#include "dnf/simulation.hpp"
#include <cstdint>
#include <deque>
#include <set>
#include <string>
#include <tuple>

namespace dnf {
// One accepted source contact against an entity target.
//
// The identity is the union of every entity-target hit producer in World:
// the character ANI attack box (`World::strike`), the job adapters
// (experimental source frames, female gunner entities, Squirrel bridge) and
// the ACT type15 collision tracks. Each producer keeps its own local guard,
// but a contact must not commit twice when two producers observe the same
// authored attack identity on the same target in the same tick.
//
// `attackInstance == 0` means the producer held no source identity (legacy
// snapshots, diagnostic fixtures, scripted calibration hits). Those contacts
// are never deduplicated here: inventing an identity would silently drop
// authored multi-hits that the source itself repeats.
//
// Passive-object durability is a separate target domain. ObjectSystem keeps
// its own durable `ObjectHitKey{owner,serial,pulse}` set inside the object
// instance, so object contacts are already at-most-once per serialized state
// and never enter this entity ledger.
struct HitAcceptanceKey {
    EntityHandle attacker, target;
    uint64_t attackInstance = 0;
    uint32_t hitIndex = 0;
    bool identified() const { return attackInstance != 0; }
    bool operator<(const HitAcceptanceKey &o) const {
        return std::tie(attacker, target, attackInstance, hitIndex) <
               std::tie(o.attacker, o.target, o.attackInstance, o.hitIndex);
    }
    bool operator==(const HitAcceptanceKey &o) const {
        return attacker == o.attacker && target == o.target &&
               attackInstance == o.attackInstance && hitIndex == o.hitIndex;
    }
    bool operator!=(const HitAcceptanceKey &o) const { return !(*this == o); }
    Json json() const {
        return Json{{"attacker", attacker.json()}, {"target", target.json()},
                    {"attack_instance", attackInstance}, {"hit_index", hitIndex}};
    }
    static HitAcceptanceKey fromJson(const Json &value) {
        HitAcceptanceKey key;
        key.attacker = EntityHandle::fromJson(value.at("attacker"));
        key.target = EntityHandle::fromJson(value.at("target"));
        const auto &instance = value.at("attack_instance");
        const auto &index = value.at("hit_index");
        if (!instance.is_number_unsigned() && !instance.is_number_integer())
            throw std::invalid_argument("Saved hit ledger attack instance is not integral");
        if (!index.is_number_unsigned() && !index.is_number_integer())
            throw std::invalid_argument("Saved hit ledger hit index is not integral");
        const int64_t savedInstance = instance.get<int64_t>();
        const int64_t savedIndex = index.get<int64_t>();
        if (savedInstance < 0 || savedIndex < 0)
            throw std::invalid_argument("Saved hit ledger identity is negative");
        if (static_cast<uint64_t>(savedIndex) > UINT32_MAX)
            throw std::invalid_argument("Saved hit ledger hit index exceeds its source range");
        key.attackInstance = static_cast<uint64_t>(savedInstance);
        key.hitIndex = static_cast<uint32_t>(savedIndex);
        return key;
    }
};

// Bounded, deterministic at-most-once acceptance ledger. Capacity overflow
// evicts the oldest identity and reports the eviction count, so a long room
// cannot grow memory without bound and the loss is visible instead of silent.
class HitAcceptanceLedger {
  public:
    static constexpr size_t capacity = 4096;
    // Pure read: reports whether this identity was already committed.
    bool accepted(const HitAcceptanceKey &key) const {
        return !key.identified() || entries_.count(key) == 0;
    }
    // Atomic check-and-record. Returns false for an already-committed identity.
    bool commit(const HitAcceptanceKey &key) {
        if (!key.identified()) return true; // Unidentified contacts are never deduplicated.
        if (!entries_.insert(key).second) return false;
        order_.push_back(key);
        if (order_.size() > capacity) {
            entries_.erase(order_.front());
            order_.pop_front();
            ++evictions_;
        }
        return true;
    }
    // Record without gating. Same as commit(); named for call sites that have
    // already passed an equivalent local guard and only publish evidence.
    bool record(const HitAcceptanceKey &key) { return commit(key); }
    void clear() {
        entries_.clear();
        order_.clear();
    }
    size_t size() const { return entries_.size(); }
    uint64_t evictions() const { return evictions_; }
    Json snapshot() const {
        Json entries = Json::array();
        for (const auto &key : order_) entries.push_back(key.json());
        return Json{{"policy", "shared-entity-hit-acceptance-v1"},
                    {"capacity", capacity},
                    {"evictions", evictions_},
                    {"size", entries_.size()},
                    {"entries", entries}};
    }
    void restore(const Json &value) {
        if (value.is_null()) return; // Legacy checkpoint: no ledger was captured.
        if (!value.is_object() || value.at("policy") != "shared-entity-hit-acceptance-v1")
            throw std::invalid_argument("Unsupported shared hit ledger checkpoint");
        const auto &entries = value.at("entries");
        const auto &evictions = value.at("evictions");
        if (!entries.is_array() || entries.size() > capacity)
            throw std::invalid_argument("Saved hit ledger entries exceed the bounded capacity");
        if (!evictions.is_number_unsigned())
            throw std::invalid_argument("Saved hit ledger eviction count is not unsigned");
        std::deque<HitAcceptanceKey> order;
        std::set<HitAcceptanceKey> keys;
        for (const auto &entry : entries) {
            auto key = HitAcceptanceKey::fromJson(entry);
            if (!key.identified())
                throw std::invalid_argument("Saved hit ledger holds an unidentified contact");
            if (!keys.insert(key).second)
                throw std::invalid_argument("Saved hit ledger repeats one contact identity");
            order.push_back(key);
        }
        order_ = std::move(order);
        entries_ = std::move(keys);
        evictions_ = evictions.get<uint64_t>();
    }

  private:
    std::deque<HitAcceptanceKey> order_;
    std::set<HitAcceptanceKey> entries_;
    uint64_t evictions_ = 0;
};
} // namespace dnf
