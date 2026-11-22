#pragma once
#include "storage.hpp"
#include <optional>

namespace dnf {
enum class SkillLearningTransactionState { Rejected, Committed, Replayed, Pending };
struct SkillLearningTransactionResult {
    SkillLearningTransactionState state = SkillLearningTransactionState::Rejected;
    bool ok = false;
    std::string message, error;
    SkillLearningQuote quote;
    Json receipt = Json::object();
    Json json() const;
};
// Normal purchase commits a complete durable character generation before the
// World receives its prepared ledger. A failed disk/publish operation freezes
// that exact prepared candidate; retry never repeats qualification or costs.
// The UI must stop simulation and mutations while pending(), also respecting
// CharacterStore::hasPendingCommit() for other business/checkpoint failures.
class SkillLearningTransaction {
    struct Pending {
        CharacterStore *store = nullptr;
        World *world = nullptr;
        int slot = -1;
        CharacterIdentity identity;
        int64_t simulationMs = 0;
        std::string requestId;
        PreparedSkillLearning prepared;
        std::unique_ptr<PreparedSkillRuntime> runtime;
        bool durable = false;
        Json receipt = Json::object();
    };
    std::optional<Pending> pending_;
    SkillLearningTransactionResult publish();
  public:
    bool pending() const { return pending_.has_value(); }
    Json pendingSnapshot() const;
    SkillLearningTransactionResult submit(CharacterStore &store, int slot, World &world,
        const Progression &progression, const SkillLearningRequest &request, const Json &regionSessionSnapshot);
    SkillLearningTransactionResult retry(CharacterStore &store, World &world);
};
Json runSkillLearningStorageTests(Pvf &pvf, Assets &assets);
Json runSkillLearningTransactionTests(Pvf &pvf, Assets &assets);
} // namespace dnf
