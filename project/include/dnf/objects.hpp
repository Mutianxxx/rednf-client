#pragma once
#include "collision.hpp"
#include <map>
#include <optional>
#include <set>
#include <tuple>

namespace dnf {

// Stable across room changes and process restarts. Coordinates and OBJ ID are
// deliberately not the key: MAPs may place identical records more than once.
struct ObjectIdentity {
    std::string run, room, map;
    uint64_t fieldOffset = 0, recordOrdinal = 0;
    std::string key() const;
    Json json() const;
    bool operator==(const ObjectIdentity &other) const { return key() == other.key(); }
    bool operator!=(const ObjectIdentity &other) const { return !(*this == other); }
};
struct ObjectPlacement {
    ObjectIdentity identity;
    int id = 0;
    double x = 0, y = 0, z = 0;
    bool special = false;
    Json raw = Json::array(), payload = Json::array();
    Bytes sourceBytes;
};
// Source width is the XY passage footprint. It is not an ANI damage box and
// supplies no height in Z. A vertical bound requires a separate consumer.
struct ObjectObstacle {
    ObjectIdentity identity;
    double x = 0, y = 0, width = 0, height = 0;
    std::optional<std::array<double, 2>> zRange;
};
struct ObjectMotion {
    std::string tag, path;
    size_t offset = 0, slot = 0;
    std::shared_ptr<const Animation> animation;
    Bytes raw;
};
struct ObjectParticleProgram {
    std::string source;
    std::vector<std::string> animations;
    std::array<std::array<double,2>,3> velocity{};
    std::array<double,3> area{};
    double gravity = 0;
    int count = 0, lifeMs = 0;
    Json evidence = Json::object();
};
struct ObjectVisualParticle {
    std::string source, animation;
    std::array<double,3> origin{}, position{}, velocity{};
    double gravity = 0;
    int64_t ageUs = 0, lifeUs = 0;
};
struct ObjectDefinition {
    int id = 0;
    std::string source, name, layer, passType;
    Script script;
    Bytes raw;
    Json provenance = Json::object(), diagnostics = Json::array();
    std::vector<int> intData;
    std::vector<ObjectParticleProgram> hitParticles, destroyParticles;
    std::string hitSound, destroySound;
    std::array<double,3> presentationOffset{};
    std::vector<ObjectMotion> motions;
    std::vector<Field> sounds, particleReferences, actions;
    double width = 0, height = 0;
    std::optional<int> explicitHpMax;
    bool explicitHpDestroy = true;
    const ObjectMotion *motion(const std::string &tag, size_t slot = 0) const;
};
class ObjectCatalog {
    Pvf &pvf_;
    Assets &assets_;
    std::map<int, std::string> paths_;
    std::map<int, std::shared_ptr<const ObjectDefinition>> definitions_;
  public:
    ObjectCatalog(Pvf &, Assets &);
    std::shared_ptr<const ObjectDefinition> definition(int id);
};

enum class ObjectState { Intact, Reacting, Destroying, Destroyed, Removed };
// Unresolved legacy int data must not acquire guessed durability. An adapter
// may provide a scoped reconstruction, with its evidence retained in saves.
struct ObjectBehavior {
    std::optional<int> durability;
    bool destroyAtZero = true, releaseObstacleOnDestroy = true;
    bool removeAfterDestroy = false;
    bool reconstructedHitShapeFallback = false;
    std::string reactionTag = "[damage motion]", destructionTag = "[last motion]";
    size_t reactionSlot = 0, destructionSlot = 0;
    bool directionalReaction = false;
    size_t reactionLeftSlot = 0, reactionRightSlot = 0;
    std::string evidence;
};
ObjectBehavior currentObjectBehavior(const ObjectDefinition &);
struct ObjectAttack {
    uint64_t owner = 0, serial = 0, pulse = 0;
    CombatBox volume;
    int damage = 1, direction = 1;
    bool missed = false;
    Json damageTrace = Json::object();
};
struct ObjectHitKey {
    uint64_t owner = 0, serial = 0, pulse = 0;
    bool operator<(const ObjectHitKey &o) const {
        return std::tie(owner, serial, pulse) < std::tie(o.owner, o.serial, o.pulse);
    }
};
struct ObjectEvent {
    uint64_t sequence = 0;
    std::string key, kind;
    ObjectIdentity object;
    int64_t ageUs = 0;
    Json payload = Json::object();
    Json savedFields = Json::object(); // Forward-compatible fields from a save.
};
struct ObjectInstance {
    ObjectPlacement placement;
    std::shared_ptr<const ObjectDefinition> definition;
    ObjectBehavior behavior;
    ObjectState state = ObjectState::Intact;
    int64_t ageUs = 0, actionAgeUs = 0;
    uint64_t randomState = 1;
    std::vector<ObjectVisualParticle> visualParticles;
    std::optional<int> durability;
    int direction = 1;
    bool collisionEnabled = true;
    std::string motionTag = "[basic motion]";
    size_t motionSlot = 0;
    std::set<ObjectHitKey> hits;
    std::set<std::string> consumedPayload;
    Json unknown = Json::object();
    Json savedFields = Json::object();
    const ObjectMotion *motion() const;
    std::vector<CombatBox> damageBoxes() const;
};

// No World, renderer, platform clock or monster reward dependency. Advance this
// once per fixed simulation tick, including ticks without any attack contact.
// Events remain pending until the consumer acknowledges their stable key.
class ObjectSystem {
    std::vector<ObjectInstance> instances_;
    std::vector<ObjectEvent> pending_;
    uint64_t nextSequence_ = 1;
    Json unknown_ = Json::object();
    Json savedFields_ = Json::object(), unmatchedInstances_ = Json::array();
    void emit(ObjectInstance &, const std::string &, Json payload = Json::object());
    void beginMotion(ObjectInstance &, const std::string &, size_t);
  public:
    Json diagnostics = Json::array();
    void clear();
    ObjectInstance &add(ObjectPlacement, std::shared_ptr<const ObjectDefinition>, ObjectBehavior = {});
    const std::vector<ObjectInstance> &instances() const { return instances_; }
    const std::vector<ObjectEvent> &pendingEvents() const { return pending_; }
    ObjectInstance *find(const ObjectIdentity &);
    const ObjectInstance *find(const ObjectIdentity &) const;
    void advance(int64_t deltaUs);
    // Pure acceptance check. Resolve a target's numerical damage only after
    // this succeeds, so rejected geometry/duplicates consume no combat RNG.
    bool acceptsContact(const ObjectIdentity &, const ObjectAttack &) const;
    bool contact(const ObjectIdentity &, const ObjectAttack &);
    bool destroy(const ObjectIdentity &, const std::string &evidence);
    bool remove(const ObjectIdentity &);
    std::vector<ObjectObstacle> activeObstacles() const;
    // Explicit payload interpretation belongs to a factory/controller. This
    // method provides durable at-most-once scheduling, never guesses six-tuples.
    bool consumePayload(const ObjectIdentity &, const std::string &token, const std::string &kind, Json payload);
    void acknowledge(const std::string &eventKey);
    void retireAttack(uint64_t owner, uint64_t serial);
    // Outer scene/process restore discards this owner's transient attacks.
    // Payload scheduling and acknowledgements remain durable.
    void retireOwnerAttacks(uint64_t owner);
    Json save() const;
    void restore(const Json &);
};

std::vector<ObjectPlacement> objectPlacements(const Script &map, const std::string &run,
                                            const std::string &room, double backgroundY,
                                            Json *diagnostics = nullptr, const Bytes *mapRaw = nullptr);
Json runObjectSystemTests(Pvf &, Assets &);
} // namespace dnf
