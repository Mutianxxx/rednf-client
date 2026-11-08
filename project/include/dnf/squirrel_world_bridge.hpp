#pragma once
#include "dnf/act_world_host.hpp"
#include "squirrel_host.hpp"
#include <map>
#include <set>
#include <thread>
#include <tuple>

namespace dnf {
struct SquirrelInvocationContext {
    // The caller allocates instanceId from World.requests and actionId from
    // World.actions before binding. Issuance is checked; the caller owns the
    // semantic association because World has no general action-owner registry.
    uint64_t instanceId = 0, actionId = 0;
    EntityHandle owner;
    // Caller-supplied source event context, not a purchase/use-skill grant.
    // Native callback dispatch and skill eligibility remain the caller's job.
    std::optional<SkillKey> buffSkill;
};
// Internal C++ interface, NOT a new Squirrel/DNF native API. Only admitted own
// CHR ATK slots; SKL coefficients and WindStrike PO24201 remain unsupported.
struct SquirrelSourceContact {
    uint64_t instanceId = 0, actionId = 0, attackOrdinal = 0;
    uint32_t hitIndex = 0;
    EntityHandle owner, target;
    SourceRef scriptSource, attackSource;
    std::string weaponTypePolicy = "blocked"; // blocked, physical, magical
};
struct SquirrelContactResult {
    bool ok = false;
    size_t accepted = 0, duplicates = 0;
    Json receipts = Json::array(), diagnostics = Json::array();
};
// One instance/action, one simulation thread, one immutable content profile.
// Requires `friend class SquirrelWorldBridge;` in World. Staging only; uses the
// explicitly inferred 3.1 typed host, without claiming original 2.1.1 parity.
class SquirrelWorldBridge final : public squirrel_stage::Bridge {
    struct SoundBatch;
    struct AttackIdentity {
        uint64_t worldId = 0;
        SourceRef source;
        std::string weaponTypePolicy;
    };
    struct AdmittedAttack { SourceRef source; Script document; };
    using ContactIdentity = std::tuple<uint64_t,uint32_t,EntityHandle>;
    World &world_;
    Pvf &pvf_;
    Assets &assets_;
    ActWorldResources resources_;
    SquirrelInvocationContext context_;
    CharacterIdentity character_;
    std::thread::id thread_;
    bool closed_ = false;
    uint64_t cleanupCount_ = 0, lastSoundSequence_ = 0;
    uint64_t requestWatermark_ = 0, actionWatermark_ = 0, attackWatermark_ = 0;
    std::optional<SourceRef> buffSkillSource_;
    std::map<std::string,squirrel_stage::SourceUnit> sources_;
    std::map<std::string,AdmittedAttack> attacks_;
    mutable std::map<std::pair<std::string,std::string>,ActResolvedResource> resolvedSounds_;
    std::map<uint64_t,AttackIdentity> attackIdentities_;
    std::set<ContactIdentity> contacts_;
    Json soundReceipts_ = Json::array(), contactReceipts_ = Json::array();
    void requireContext() const;
    bool admittedScript(const SourceRef &) const;
    bool admittedAttack(const SourceRef &) const;
  public:
    SquirrelWorldBridge(World &, Pvf &, Assets &, std::string staticIdentity,
                        SquirrelInvocationContext);
    squirrel_stage::SourceUnit source(const std::string &member);
    SourceRef attackSource(const std::string &chrTag, size_t slot = 0, size_t occurrence = 0);
    bool valid(EntityHandle) const noexcept override;
    bool hasBuffSkillIndex() const noexcept override { return bool(context_.buffSkill); }
    bool hasSoundConsumer() const noexcept override { return true; }
    int buffSkillIndex(EntityHandle) const override;
    std::optional<SourceRef> resolveSound(const std::string &,const SourceRef &) const override;
    std::unique_ptr<squirrel_stage::PreparedSoundBatch> prepare(
        const std::vector<squirrel_stage::SoundCommand> &) override;
    void commit(std::unique_ptr<squirrel_stage::PreparedSoundBatch>) noexcept override;
    void cleanup(uint64_t,const std::string &) noexcept override;
    // World simulation state is published for the entire vector or not at all.
    // Shared read-only providers may fill caches/read telemetry on rejection.
    // A fresh scratch World executes existing damage/status/death services,
    // then publishes only the prepared values using noexcept swaps.
    SquirrelContactResult applySourceContacts(const std::vector<SquirrelSourceContact> &);
    Json diagnostics() const;
};
Json runSquirrelWorldBridgeTests(Pvf &,Assets &,const std::string &staticIdentity);
} // namespace dnf
