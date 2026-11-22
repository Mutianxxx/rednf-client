#pragma once
#include "dnf/content_profile.hpp"
#include "dnf/simulation.hpp"
#include <functional>

namespace dnf {
struct MonsterEventAiLimits {
    size_t maxSourceBytes = 65536, maxFields = 4096, maxNodes = 1024, maxDepth = 32;
    size_t maxEvaluationSteps = 256, maxRandomDraws = 32;
};
struct MonsterEventAiPolicy {
    std::string id = "disabled";
    static MonsterEventAiPolicy inferredIntegralChanceV1();
    Json json() const;
};
struct MonsterEventAiRoute {
    bool configured = false, ok = false;
    std::string difficulty, literalPath, resolvedPath;
    SourceRef monsterSource, fieldSource, operandSource, resolvedSource;
    Json orderedAiFields = Json::array(), fieldTokens = Json::array(), diagnostics = Json::array();
    Json json() const;
};
// Explicit authored difficulty only. The first path of the complete selected
// MOB difficulty row is Event.ai; no difficulty/path/name-based fallback.
MonsterEventAiRoute selectMonsterEventAi(const Pvf &, const Script &, const std::string &difficulty);
// Only an accepted World hit supplies this record. The evaluator never infers a
// hit from HP loss, distance, animations or a path/name. The caller owns event
// deduplication and same-generation publication of the consumed event identity.
struct MonsterAcceptedHit {
    uint64_t eventId = 0;
    EntityHandle attacker;
    int actualHpLoss = 0;
    int64_t damageWindowAmount = 0;
    bool damageCheckEnabled = false;
    Json damageWindowConfiguration=Json::object();
};
struct MonsterEventAiContext {
    EntityHandle owner;
    uint64_t tick = 0;
    std::optional<MonsterAcceptedHit> acceptedHit;
};
// nullopt means invalid/unsupported action index, rather than "not in CD".
// Query must be read-only, deterministic and bound to this preparation boundary.
using MonsterEventCooldownQuery = std::function<std::optional<bool>(EntityHandle, int)>;
struct MonsterEventAiEvaluation;
struct MonsterEventAiCompilation;
struct MonsterEventAiCompiler;
class MonsterEventAiProgram {
    enum class Kind { Return, Hit, Chance, Cooldown, DamageCheck };
    struct Node {
        Kind kind = Kind::Return;
        int value = -1;
        uint32_t numerator = 0, denominator = 1;
        size_t yes = 0, no = 0;
        SourceRef source;
        Json operands = Json::array();
    };
    Script script_;
    SourceRef source_;
    std::vector<Node> nodes_;
    size_t root_ = 0;
    MonsterEventAiLimits limits_;
    MonsterEventAiPolicy policy_;
    Json retainedFields_ = Json::array();
    MonsterEventAiProgram() = default;
    friend struct MonsterEventAiCompiler;
    friend MonsterEventAiCompilation compileMonsterEventAi(const Pvf &, const Script &,
        const MonsterEventAiPolicy &, const MonsterEventAiLimits &);
    friend MonsterEventAiEvaluation evaluateMonsterEventAi(const MonsterEventAiProgram &,
        const MonsterEventAiContext &, const Pcg32 &, const MonsterEventCooldownQuery &);
  public:
    const Script &sourceScript() const { return script_; }
    const SourceRef &source() const { return source_; }
    const Json &retainedFields() const { return retainedFields_; }
    Json json() const;
};
struct MonsterEventAiCompilation {
    bool ok = false;
    std::shared_ptr<const MonsterEventAiProgram> program;
    Json diagnostics = Json::array();
    Json json() const;
};
MonsterEventAiCompilation compileMonsterEventAi(const Pvf &, const Script &,
    const MonsterEventAiPolicy & = {}, const MonsterEventAiLimits & = {});
struct MonsterEventAiEvaluation {
    bool ok = false;
    // Engaged -1 is a valid authored "no action" result. Missing means failure.
    std::optional<int> returnedActionIndex;
    std::optional<SourceRef> returnSource;
    Json trace = Json::array(), diagnostics = Json::array();
    Json randomBefore = Json::object();
    // Input RNG is never mutated. Only success exposes a candidate to publish
    // together with consumed-event/outcome state. Failure has no candidate.
    std::optional<Pcg32> candidateRandom;
    Json json() const;
};
MonsterEventAiEvaluation evaluateMonsterEventAi(const MonsterEventAiProgram &,
    const MonsterEventAiContext &, const Pcg32 &, const MonsterEventCooldownQuery &);
} // namespace dnf
