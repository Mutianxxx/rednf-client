#pragma once
#include "character_controller.hpp"
#include "content_profile.hpp"
#include <map>

namespace dnf {
enum class SkillInitializationMode { NewCharacter, LegacyImport };
enum class SkillLearningGate {
    Accepted, Uninitialized, InvalidLedger, SourceMismatch, SourceInvalid,
    WrongCharacter, MissingImplementation, PassiveHasNoConsumer, UnknownKind,
    SourceExcluded, InvalidLevel, CharacterLevel, Prerequisite, SpecialQualification,
    InsufficientPoints, BudgetConflict, StaleRevision, InvalidRequest, RequestConflict,
    NotLearned, TemporaryLevelIneligible
};
const char *skillLearningGateName(SkillLearningGate gate);

struct SkillLearningPolicy {
    std::string id = "inferred-1031-learning-v1";
    std::string tpPolicy = "inferred-server-tp-v1";
    int maximumNormalLevel = 99;
    // Explicit candidate: official sample/server integer SP fitness discount.
    bool applyGrowtypeFitnessDiscount = true;
};
struct SkillLearningBudget {
    int64_t earnedSp = 0, earnedTp = 0, spentSp = 0, spentTp = 0;
    int64_t remainingSp = 0, remainingTp = 0;
    uint64_t revision = 0;
    Json trace = Json::array();
    Json json() const;
};
struct SkillLearningQuote {
    SkillLearningGate gate = SkillLearningGate::SourceInvalid;
    std::string message, error, currency;
    SkillKey key;
    int currentLevel = 0, targetLevel = 0, requiredCharacterLevel = 0, purchaseMaximum = 0;
    int64_t cost = 0;
    uint64_t revision = 0;
    SkillLearningBudget budget;
    Json trace = Json::array();
    bool accepted() const { return gate == SkillLearningGate::Accepted; }
    Json json() const;
};
struct SkillLearningRequest {
    std::string requestId;
    SkillKey key;
    uint64_t expectedRevision = 0;
    // Explicit target is required, including on retries. No level cycling.
    int targetLevel = 0;
};
struct SkillLearningBatch {
    SkillLearningBudget budget;
    std::vector<SkillLearningQuote> quotes;
};
struct PreparedSkillLearning {
    bool ok = false, replayed = false;
    SkillLearningQuote quote;
    CharacterSkillState state;
    Json receipt = Json::object();
};
struct SkillLearningUseEligibility {
    SkillLearningGate gate = SkillLearningGate::SourceInvalid;
    int learnedLevel = 0, requiredCharacterLevel = 0;
    Json trace = Json::array();
    std::string error;
    bool allowed() const { return gate == SkillLearningGate::Accepted; }
    Json json() const;
};
struct SkillLearningTestOverlay;
struct PreparedTestSkillLearning;

// No World/SDL/file writes. Every mutation returns a private prepared ledger;
// the caller publishes it together with its durable character transaction.
// nowMs is the same simulation epoch used by CharacterSkillState cooldowns.
class SkillLearningService {
    const CharacterCatalog &catalog_;
    Script spTable_;
    std::string packageIdentity_;
    SkillLearningPolicy policy_;
    std::map<int,int64_t> spAtLevel_;
    void loadSpTable();
    SkillLearningBudget baseBudget(int normalLevel) const;
    SkillLearningQuote quoteWithBudget(const CharacterSkillState &state, int characterLevel,
        const RuntimeSkillPolicy &runtime, const CharacterSkillDefinition &definition,
        int targetLevel, const SkillLearningBudget &budget) const;
  public:
    SkillLearningService(Pvf &pvf, const CharacterCatalog &catalog, SkillLearningPolicy policy = {});
    // Source-injected constructor keeps malformed/updated table tests portable.
    SkillLearningService(const CharacterCatalog &catalog, Script spTable,
        std::string packageIdentity, SkillLearningPolicy policy = {});
    PreparedSkillLearning prepareInitialization(const CharacterSkillState &state, int normalLevel,
        SkillInitializationMode mode, int64_t nowMs = 0) const;
    SkillLearningBudget budget(const CharacterSkillState &state, int normalLevel, int64_t nowMs = 0) const;
    SkillLearningQuote quote(const CharacterSkillState &state, int normalLevel,
        const RuntimeSkillPolicy &runtime, int targetLevel = 0, int64_t nowMs = 0) const;
    // Public source evaluator also permits version adapters/tests to inspect an
    // exact lossless definition. It obeys the same ledger and runtime gates.
    SkillLearningQuote quoteDefinition(const CharacterSkillState &state, int normalLevel,
        const RuntimeSkillPolicy &runtime, const CharacterSkillDefinition &definition,
        int targetLevel = 0, int64_t nowMs = 0) const;
    PreparedSkillLearning prepare(const CharacterSkillState &state, int normalLevel,
        const RuntimeSkillPolicy &runtime, const SkillLearningRequest &request, int64_t nowMs = 0) const;
    // Refunds only actual purchases, leaves source/legacy grants and cooldowns.
    PreparedSkillLearning prepareReset(const CharacterSkillState &state, int normalLevel,
        const std::string &requestId, uint64_t expectedRevision, int64_t nowMs = 0) const;
    // Stable external task/reward event IDs prevent repeated SP/TP grants.
    PreparedSkillLearning preparePointReward(const CharacterSkillState &state, int normalLevel,
        const std::string &requestId, uint64_t expectedRevision, int64_t sp, int64_t tp,
        const Json &source, int64_t nowMs = 0) const;
    const std::string &packageIdentity() const noexcept { return packageIdentity_; }
    // Required EQU permission uses the normal source-bound ledger and source
    // identity/level limits, without requiring an active runtime or inventing
    // a required character level absent from the permission SKL.
    SkillLearningUseEligibility equipmentPermissionEligibility(const CharacterSkillState &normal,
        SkillKey key, int normalCharacterLevel, int64_t nowMs = 0) const;
    SkillLearningUseEligibility useEligibility(const CharacterSkillState &state,
        SkillKey key, int effectiveCharacterLevel) const;
    // Pure source eligibility for an explicitly configured preview level;
    // does not grant learning, spending or a runtime implementation.
    SkillLearningUseEligibility sourceUseEligibility(CharacterIdentity, SkillKey,
        int configuredLevel, int effectiveCharacterLevel) const;
    SkillLearningBudget testBudget(const CharacterSkillState &normal, const SkillLearningTestOverlay &overlay,
        int effectiveCharacterLevel, int64_t nowMs = 0) const;
    SkillLearningBatch quoteBatch(const CharacterSkillState &, const SkillLearningTestOverlay *, int characterLevel,
        const std::vector<RuntimeSkillPolicy> &, int64_t nowMs = 0) const;
    SkillLearningQuote quoteTest(const CharacterSkillState &normal, const SkillLearningTestOverlay &overlay,
        int effectiveCharacterLevel, const RuntimeSkillPolicy &runtime, int targetLevel = 0, int64_t nowMs = 0) const;
    PreparedTestSkillLearning prepareTest(const CharacterSkillState &normal, const SkillLearningTestOverlay &overlay,
        int effectiveCharacterLevel, const RuntimeSkillPolicy &runtime,
        const SkillLearningRequest &request, int64_t nowMs = 0) const;
};

// Independent test point pool/levels. Overlay preparation uses effectiveLevel
// and an isolated budget; normal earned/spent/history are never modified.
// Persist separately in a test branch, and discard to recover normal skills.
struct SkillLearningTestOverlay {
    std::map<SkillKey,int> levels;
    int64_t spentSp = 0, spentTp = 0;
    uint64_t revision = 0;
    std::string normalFingerprint;
    Json purchases = Json::array(), receipts = Json::object();
    Json snapshot() const;
    void restore(const Json &value);
    CharacterSkillState effectiveState(const CharacterSkillState &normal, int64_t nowMs = 0) const;
    // Exact legacy validation precedes canonical migration; purchases and
    // receipts remain unchanged. Call on a private candidate before publish.
    void upgradeNormalBinding(const CharacterSkillState &normal, int64_t nowMs = 0);
};
struct PreparedTestSkillLearning {
    bool ok = false, replayed = false;
    SkillLearningQuote quote;
    SkillLearningTestOverlay overlay;
    Json receipt = Json::object();
};
Json runSkillLearningTests(Pvf &pvf);
} // namespace dnf
