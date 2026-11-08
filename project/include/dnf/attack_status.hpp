#pragma once
#include "combat_attributes.hpp"
#include "monster_combat_attributes.hpp"
#include "simulation.hpp"
#include "skill_data.hpp"
#include <functional>

namespace dnf {
enum class AttackStatusKind { None, Stun, Freeze, Lightning, Burn, Bleeding, Blind, RequiredUnsupported };
const char *attackStatusKindName(AttackStatusKind);
struct AttackStatusEntry {
    AttackStatusKind kind = AttackStatusKind::RequiredUnsupported;
    std::string tag, scope = "dungeon";
    bool runtime = true;
    double chancePercent = 0;
    int level = 0;
    uint32_t durationMs = 0;
    double damage = 0;
    uint32_t maximumTriggers = 0;
    double blindEvasionPercent = 0, blindVisionPercent = 100;
    size_t ordinal = 0;
    Json rawPayload = Json::array();
    std::vector<SourceRef> sources;
    Json diagnostics = Json::array();
    bool usable() const;
    Json snapshot() const;
};
struct AttackStatusSource {
    Script source;
    std::vector<AttackStatusEntry> entries;
    Json diagnostics = Json::array();
    bool usable() const;
    Json snapshot(bool includeSource = false) const;
};
// Preserves every type/payload, both inline string enums and separate type-5
// enums. Only dungeon stun and none have complete consumers in this module.
AttackStatusSource readAttackStatuses(const Script &source);

// Skill setters are a separate, source-bound inference. They never change the
// original ATK bytes or turn a display label into an unqualified source fact.
struct SkillStatusFeature {
    SkillSourceData source;
    int level = 0;
};
struct SkillStatusApplication {
    SkillSourceData source;
    std::vector<SkillStatusFeature> features;
    int level = 0;
    std::vector<AttackStatusEntry> entries;
    Json diagnostics = Json::array();
    bool usable() const;
    Json snapshot(bool includeSource = false) const;
};
SkillStatusApplication readSkillAttackStatuses(const SkillSourceData &,int level);
SkillStatusApplication readSkillAttackStatuses(const SkillSourceData &,int level,const std::vector<SkillStatusFeature> &);
struct FemaleGunnerSkillCommand;
struct ExperimentalCharacterPlan;
// Recomputes feature tables/schema from immutable registered sources and
// validates the command's frozen overlay before producing status setters.
SkillStatusApplication readFemaleGunnerSkillAttackStatuses(const FemaleGunnerSkillCommand &,const ExperimentalCharacterPlan &);

// This is the existing monster adapter's named 17-slot order, not a numeric
// native-enum assertion. Obsolete CHR deelement/deadlystrike remain in source
// documents and never get relabelled burn/weapon-break. Stuck remains evasion.
const std::array<const char *,17> &statusResistanceOrder();
struct StatusResistanceSnapshot {
    std::string packageIdentity;
    int level = 0;
    std::array<float,17> values{};
    float allActiveStatusResistance = 0;
    Json sources = Json::object(), trace = Json::array(), diagnostics = Json::array();
    bool usable() const;
    float stunResistance() const;
    Json snapshot() const;
};
// Reuses the existing equipment speed evaluator's UID/slot/job/normal-level/
// durability qualification. CHR uses its already selected initial/growth/
// awakening blocks; binary32 additions mirror the selected growth policy.
StatusResistanceSnapshot evaluateCharacterStatusResistances(const CharacterBaseAttributes &base,
    const CharacterDefinition &character, const std::vector<EquippedAttributeSource> &equipment,
    int qualificationLevel);
StatusResistanceSnapshot makeMonsterStatusResistances(const MonsterCombatAttributes &frozen);

struct StunStatusPolicy {
    std::string id = "disabled";
    // This is a comparable beta inference, not a recovered source formula:
    // source chance * max(0, 1 - resistance/100), clamped to [0,100]. Source
    // level is preserved but has no invented level-ratio multiplier. Source
    // duration is fixed milliseconds. Nonzero resistance requires explicit
    // opt-in; otherwise it blocks instead of being silently discarded.
    bool inferResistanceAsPercent = false;
    static StunStatusPolicy inferredFlatChanceStunV1(bool inferResistanceAsPercent = false);
    Json snapshot() const;
};
struct StatusTarget {
    EntityHandle handle;
    StatusResistanceSnapshot resistance;
    bool immuneToStun = false;
    Json immunitySource = Json::object();
};
struct StatusRequest {
    EntityHandle attacker;
    int attackerLevel = 0;
    StatusTarget target;
    uint64_t attackInstance = 0;
    uint32_t hitIndex = 0;
    AttackStatusSource attack;
    std::optional<SkillStatusApplication> skill;
    float independentAttack = 0, independentRate = 1, strength = 0, intelligence = 0;
};
struct StunStatusInstance {
    uint64_t id = 0, attackInstance = 0;
    uint32_t hitIndex = 0;
    EntityHandle attacker, target;
    int authoredLevel = 0, attackerLevel = 0, targetLevel = 0;
    uint64_t appliedMs = 0, expiresMs = 0;
    uint32_t maximumDurationMs = 0;
    std::string sourcePath;
    size_t statusOrdinal = 0;
    Json sourceEntry, resistance, trace = Json::array(), preserved = Json::object();
    Json snapshot(uint64_t nowMs) const;
};
class StatusHost;
struct StatusEffectInstance {
    uint64_t id = 0, attackInstance = 0, appliedMs = 0, expiresMs = 0, nextDamageMs = 0;
    uint32_t hitIndex = 0, intervalMs = 1000;
    EntityHandle attacker,target;
    AttackStatusKind kind = AttackStatusKind::None;
    int hpDamage = 0;
    uint32_t remainingTriggers = 0;
    Json definition = Json::object(),trace = Json::array(),preserved = Json::object();
    Json snapshot(uint64_t nowMs) const;
};
struct PreparedStatusAdvance {
    Json receipt = Json::object();
    bool ready() const {return bool(candidate_);}
  private:
    friend class StatusHost;
    std::shared_ptr<StatusHost> candidate_;
    const StatusHost *origin_ = nullptr;
    uint64_t expectedRevision_ = 0;
};
struct PreparedStatusApplication {
    Json receipt = Json::object();
    bool ready() const { return bool(candidate_); }
  private:
    friend class StatusHost;
    std::shared_ptr<StatusHost> candidate_;
    const StatusHost *origin_ = nullptr;
    uint64_t expectedRevision_ = 0;
    Json expectedRandom_;
    Pcg32 candidateRandom_;
};
class StatusHost {
    std::string packageIdentity_;
    StunStatusPolicy policy_;
    MonotonicIds instances_;
    uint64_t revision_ = 0, lastNowMs_ = 0;
    std::map<EntityHandle,StunStatusInstance> active_;
    std::map<std::pair<EntityHandle,AttackStatusKind>,StatusEffectInstance> effects_;
    std::map<std::string,Json> contacts_;
    std::map<std::string,AttackStatusSource> sources_;
    Json lifecycle_ = Json::array(), preserved_ = Json::object();
    int applyEffectStatuses(const StatusRequest &,uint64_t,Pcg32 &,Json &);
    void restoreEffects(const Json &,uint64_t,const std::function<Script(const std::string &)> &,
        const std::function<bool(EntityHandle)> &);
  public:
    explicit StatusHost(std::string packageIdentity = {}, StunStatusPolicy policy = {});
    // Preparation changes no host, HP, RNG, IDs or caller-owned source. The
    // caller first validates the complete HP/status/world transaction, then
    // publishes this candidate under its same simulation commit generation.
    PreparedStatusApplication prepare(const StatusRequest &request,uint64_t nowMs,const Pcg32 &random) const;
    bool canPublish(const PreparedStatusApplication &prepared,const Pcg32 &random) const;
    // Throws before mutation on stale/reused candidates. Final publication
    // moves privately prepared state and copies PCG's scalar state only.
    void publish(PreparedStatusApplication &&prepared,Pcg32 &random);
    bool stunned(EntityHandle target,uint64_t nowMs) const;
    bool frozen(EntityHandle target,uint64_t nowMs) const;
    bool controlled(EntityHandle target,uint64_t nowMs) const;
    bool hasEffects(EntityHandle target,uint64_t nowMs) const;
    Json activeEffects(EntityHandle target,uint64_t nowMs) const;
    double blindMissPercent(EntityHandle target,uint64_t nowMs) const;
    uint64_t controlRemaining(EntityHandle target,uint64_t nowMs) const;
    PreparedStatusAdvance prepareAdvance(uint64_t nowMs) const;
    bool needsEffectAdvance(uint64_t nowMs) const;
    bool canPublish(const PreparedStatusAdvance &) const;
    void publish(PreparedStatusAdvance &&);
    const StunStatusInstance *instance(EntityHandle target,uint64_t nowMs) const;
    void expire(uint64_t nowMs);
    void clearTarget(EntityHandle target,uint64_t nowMs,const std::string &reason);
    // Complete entity retirement differs from cleansing/death: its accepted
    // contacts can no longer be sampled and its private ledger may be freed.
    // The global instance watermark and lifecycle evidence remain monotonic.
    void retireTarget(EntityHandle target,uint64_t nowMs,const std::string &reason);
    Json instanceWatermark() const { return instances_.snapshot(); }
    // Merge the global watermark even when no target has an active status.
    void mergeInstanceWatermark(const Json &saved);
    void clearAll(uint64_t nowMs,const std::string &reason);
    Json snapshot(uint64_t nowMs,uint64_t commitGeneration,bool includeSource = false) const;
    // A room/character save carries only its explicitly named target. The
    // global monotonic watermark is retained, even for an empty bundle.
    Json snapshotTarget(EntityHandle target,uint64_t nowMs,uint64_t commitGeneration,
        bool includeSource = false) const;
    // Sources and entity registry must be staged from the same generation.
    // Attacker handles may be stale; target handles must still be live. RNG
    // restores separately in that same transaction; this service never rerolls.
    void restore(const Json &saved,uint64_t nowMs,uint64_t expectedGeneration,
        const std::function<Script(const std::string &)> &source,
        const std::function<bool(EntityHandle)> &targetIsLive);
    // Replaces newTarget's state while preserving all other targets. When
    // oldTarget differs it must be retired; its old contact/active data are
    // replaced too. A still-live oldTarget cannot be duplicated. Both
    // identities are explicit; incoming targets must all equal oldTarget.
    // Attacker handles remain historical. Source/ID conflicts, unknown live
    // targets or malformed bundles reject without changing this host.
    void mergeTarget(const Json &saved,EntityHandle oldTarget,EntityHandle newTarget,
        uint64_t nowMs,uint64_t expectedGeneration,
        const std::function<Script(const std::string &)> &source,
        const std::function<bool(EntityHandle)> &targetIsLive);
};
} // namespace dnf
