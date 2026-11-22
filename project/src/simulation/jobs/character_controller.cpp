#include "dnf/character_controller.hpp"
#include <algorithm>
#include <cctype>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
const char *readinessName(ControllerReadiness value) {
    switch (value) {
    case ControllerReadiness::Unavailable: return "unavailable";
    case ControllerReadiness::ExistingPartialCandidate: return "existing_partial_candidate";
    case ControllerReadiness::NativeChainClosed: return "native_chain_closed";
    case ControllerReadiness::DeferredByUser: return "deferred_by_user";
    case ControllerReadiness::ReconstructedBeta: return "reconstructed_beta";
    case ControllerReadiness::ExperimentalUserTest: return "experimental_user_test";
    case ControllerReadiness::UserAdvancementPartial: return "user_advancement_partial";
    }
    throw std::invalid_argument("Unknown controller readiness");
}
bool hasText(const std::string &value) {
    return std::any_of(value.begin(), value.end(), [](unsigned char c) { return !std::isspace(c); });
}
const char *checkStatusName(ControllerCheckStatus value) {
    switch (value) {
    case ControllerCheckStatus::Pending: return "pending";
    case ControllerCheckStatus::Passed: return "passed";
    case ControllerCheckStatus::Failed: return "failed";
    }
    throw std::invalid_argument("Unknown controller check status");
}
const char *actionName(CharacterAction value) {
    switch (value) {
    case CharacterAction::Move: return "move";
    case CharacterAction::Jump: return "jump";
    case CharacterAction::BasicAttack: return "basic_attack";
    case CharacterAction::DashAttack: return "dash_attack";
    case CharacterAction::JumpAttack: return "jump_attack";
    case CharacterAction::CommandInput: return "command_input";
    case CharacterAction::Skill: return "skill";
    }
    throw std::invalid_argument("Unknown character action");
}
bool validHash(const std::string &value) {
    return value.size() == 64 && std::all_of(value.begin(), value.end(), [](unsigned char c) {
        return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
    });
}
void validateIdentity(CharacterIdentity value) {
    if (value.jobId < 0 || value.growtype < 0 || value.awakening < 0)
        throw std::invalid_argument("Negative character identity");
}
void validateKey(SkillKey value) {
    if (value.jobId < 0 || value.skillId < 0) throw std::invalid_argument("Negative skill key");
}
void validateTime(int64_t value) {
    if (value < 0) throw std::invalid_argument("Negative simulation time");
}
int64_t expiry(int64_t nowMs, int64_t durationMs) {
    validateTime(nowMs);
    validateTime(durationMs);
    const auto max = std::numeric_limits<int64_t>::max();
    return durationMs > max - nowMs ? max : nowMs + durationMs;
}
int64_t nonnegativeInteger(const Json &value, const std::string &name) {
    if (!value.is_number_integer()) throw std::invalid_argument("Non-integer " + name);
    if (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(std::numeric_limits<int64_t>::max()))
        throw std::invalid_argument("Overflowing " + name);
    const auto result = value.get<int64_t>();
    if (result < 0) throw std::invalid_argument("Negative " + name);
    return result;
}
int boundedInt(const Json &value, const std::string &name) {
    const auto result = nonnegativeInteger(value, name);
    if (result > std::numeric_limits<int>::max()) throw std::invalid_argument("Overflowing " + name);
    return int(result);
}
CharacterIdentity storedIdentity(const Json &value) {
    if (!value.is_object()) throw std::invalid_argument("Missing character identity");
    return {boundedInt(value.at("job_id"), "job_id"), boundedInt(value.at("growtype"), "growtype"),
            boundedInt(value.at("awakening"), "awakening")};
}
SkillKey storedKey(const Json &value) {
    if (!value.is_object()) throw std::invalid_argument("Missing skill key");
    return {boundedInt(value.at("job_id"), "job_id"), boundedInt(value.at("skill_id"), "skill_id")};
}
Json chainSnapshot(const NativeControllerChain &chain) {
    return {{"release_qualification", chain.releaseQualification.snapshot()}, {"input_request", chain.inputRequest.snapshot()},
        {"state_commit", chain.stateCommit.snapshot()}, {"action_and_attack", chain.actionAndAttack.snapshot()},
        {"contact_and_effects", chain.contactAndEffects.snapshot()}, {"continuation", chain.continuation.snapshot()},
        {"exit_cleanup", chain.exitCleanup.snapshot()}, {"execution_complete", chain.runtimeComplete()},
        {"native_confirmed", chain.nativeConfirmed()}};
}
Json userCheckSnapshot(const NativeEvidenceRef &evidence) {
    return {{"status", evidence.confirmed() ? "passed" : "pending"}, {"evidence", evidence.snapshot()}};
}
bool controllerChainsComplete(const CharacterControllerInfo &info, bool nativeOnly) {
    if (info.identity.jobId < 0 || info.identity.growtype < 0 || info.identity.awakening < 0 ||
        !validHash(info.exeSha256) || !validHash(info.pvfSha256) || !hasText(info.implementation)) return false;
    const auto complete = [nativeOnly](const NativeControllerChain &chain) {
        return nativeOnly ? chain.nativeConfirmed() : chain.runtimeComplete();
    };
    for (const auto action : {CharacterAction::Move, CharacterAction::Jump, CharacterAction::BasicAttack,
                              CharacterAction::DashAttack, CharacterAction::JumpAttack}) {
        if (info.actionEvidence.find(action) == info.actionEvidence.end()) return false;
    }
    // Input and skill actions can also be explicitly declared. No extra
    // declared action may carry an unknown or unfinished lifecycle.
    for (const auto &entry : info.actionEvidence) {
        switch (entry.first) {
        case CharacterAction::Move: case CharacterAction::Jump: case CharacterAction::BasicAttack:
        case CharacterAction::DashAttack: case CharacterAction::JumpAttack:
        case CharacterAction::CommandInput: case CharacterAction::Skill: break;
        default: return false;
        }
        if (!complete(entry.second)) return false;
    }
    if (info.requiredRuntimeSkills.empty() || info.requiredRuntimeSkills.size() != info.skillEvidence.size()) return false;
    for (const auto &key : info.requiredRuntimeSkills) {
        const auto found = info.skillEvidence.find(key);
        if (key.jobId != info.identity.jobId || key.skillId < 0 || found == info.skillEvidence.end() ||
            !complete(found->second)) return false;
    }
    return true;
}
class ExistingSwordmanAdapter final : public CharacterController {
    CharacterControllerServices services_;
    int64_t lastTick_ = -1;
  public:
    explicit ExistingSwordmanAdapter(CharacterControllerServices services) : services_(std::move(services)) {
        if (!services_.request || !services_.tick || !services_.cancel)
            throw std::invalid_argument("Existing Swordman factory requires executable World callbacks");
    }
    CharacterIdentity identity() const override { return {}; }
    bool request(const CharacterActionRequest &request) override {
        validateTime(request.simulationMs);
        if (request.action == CharacterAction::Skill &&
            (!request.skill || request.skill->jobId != 0 || request.skill->skillId < 0))
            return false;
        if (request.action != CharacterAction::Skill && request.skill) return false;
        return services_.request(request);
    }
    void tick(int64_t simulationMs) override {
        validateTime(simulationMs);
        if (simulationMs < lastTick_) throw std::invalid_argument("Controller clock moved backwards");
        // Once per fixed simulation tick. The caller owns the simulation rate.
        if (simulationMs == lastTick_) return;
        services_.tick(simulationMs);
        lastTick_ = simulationMs;
    }
    void cancel(ControllerCancelReason reason) override {
        services_.cancel(reason);
        lastTick_ = -1;
    }
};
}

bool NativeControllerChain::nativeConfirmed() const {
    return releaseQualification.confirmed() && inputRequest.confirmed() && stateCommit.confirmed() &&
        actionAndAttack.confirmed() && contactAndEffects.confirmed() && continuation.confirmed() && exitCleanup.confirmed();
}
bool NativeControllerChain::runtimeComplete() const {
    return releaseQualification.explainedForRuntime() && inputRequest.explainedForRuntime() &&
        stateCommit.explainedForRuntime() && actionAndAttack.explainedForRuntime() &&
        contactAndEffects.explainedForRuntime() && continuation.explainedForRuntime() && exitCleanup.explainedForRuntime();
}
bool NativeEvidenceRef::confirmed() const {
    return classification == "confirmed" && hasText(report) && hasText(anchor) && hasText(finding);
}
bool NativeEvidenceRef::explainedForRuntime() const {
    return confirmed() || (classification == "inferred" && hasText(report) && hasText(anchor) && hasText(finding) &&
        hasText(basis) && hasText(unverifiedConditions) && hasText(impact));
}
Json NativeEvidenceRef::snapshot() const {
    return {{"classification", classification}, {"report", report}, {"anchor", anchor},
        {"finding", finding}, {"basis", basis}, {"unverified_conditions", unverifiedConditions}, {"impact", impact},
        {"confirmed", confirmed()}, {"explained_for_runtime", explainedForRuntime()}};
}
bool ControllerCheckEvidence::passed() const {
    return status == ControllerCheckStatus::Passed && hasText(report) && hasText(anchor) && hasText(finding);
}
Json ControllerCheckEvidence::snapshot() const {
    return {{"status", checkStatusName(status)}, {"report", report}, {"anchor", anchor},
        {"finding", finding}, {"passed", passed()}};
}
bool CharacterControllerInfo::runtimeComplete() const {
    if (readiness == ControllerReadiness::ExperimentalUserTest || readiness == ControllerReadiness::UserAdvancementPartial) return false;
    return controllerChainsComplete(*this, false);
}
bool CharacterControllerInfo::nativeConfirmed() const {
    if (readiness == ControllerReadiness::ExperimentalUserTest || readiness == ControllerReadiness::UserAdvancementPartial) return false;
    return controllerChainsComplete(*this, true) && normalInputEvidence.confirmed() &&
        originalClientComparisonEvidence.confirmed();
}
bool CharacterControllerInfo::executable() const {
    return readiness == ControllerReadiness::ExistingPartialCandidate || readiness == ControllerReadiness::NativeChainClosed ||
        readiness == ControllerReadiness::ReconstructedBeta || readiness == ControllerReadiness::ExperimentalUserTest ||
        readiness == ControllerReadiness::UserAdvancementPartial;
}
Json CharacterControllerInfo::snapshot() const {
    Json actions = Json::array(), skills = Json::array();
    for (const auto &entry : actionEvidence)
        actions.push_back({{"action", actionName(entry.first)}, {"chain", chainSnapshot(entry.second)}});
    for (const auto &entry : skillEvidence)
        skills.push_back({{"key", entry.first.json()}, {"chain", chainSnapshot(entry.second)}});
    Json runtimeSkills = Json::array();
    for (const auto &key : requiredRuntimeSkills) runtimeSkills.push_back(key.json());
    return {{"identity", identity.json()}, {"name", name}, {"implementation", implementation},
        {"readiness", readinessName(readiness)}, {"executable", executable()}, {"limitation", limitation},
        {"execution_complete", runtimeComplete()}, {"native_confirmed", nativeConfirmed()},
        {"exe_sha256", exeSha256}, {"pvf_sha256", pvfSha256}, {"actions", actions}, {"skills", skills},
        {"required_runtime_skills", runtimeSkills}, {"normal_input", normalInputEvidence.snapshot()},
        {"original_client_comparison", originalClientComparisonEvidence.snapshot()},
        {"automated_runtime", automatedRuntimeEvidence.snapshot()},
        {"user_checks", {{"normal_input", userCheckSnapshot(normalInputEvidence)},
                         {"original_client_comparison", userCheckSnapshot(originalClientComparisonEvidence)}}}};
}
CharacterControllerRegistry CharacterControllerRegistry::currentCandidate(const CharacterCatalog &catalog) {
    CharacterControllerRegistry result;
    for (const auto &definition : catalog.definitions) {
        CharacterControllerInfo info;
        info.identity = {definition.registration.id, 0, 0};
        info.name = definition.job;
        info.readiness = definition.runtimeDeferredByUser ? ControllerReadiness::DeferredByUser : ControllerReadiness::Unavailable;
        info.limitation = definition.runtimeDeferredByUser ? "Runtime deferred by user; source retained" :
            "Complete executable class behavior, declared skill consumers and automated runtime validation unresolved";
        result.registerController(std::move(info));
    }
    CharacterControllerInfo legacy;
    legacy.identity = {};
    legacy.name = catalog.at(0).job;
    legacy.implementation = "world-swordman-existing-partial";
    legacy.readiness = ControllerReadiness::ExistingPartialCandidate;
    legacy.exeSha256 = "246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264";
    legacy.pvfSha256 = "d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d";
    legacy.limitation = "Existing unadvanced Swordman candidate; native qualification, attributes, movement and full parity remain partial";
    result.registerController(std::move(legacy), [](CharacterControllerServices services) {
        return std::make_unique<ExistingSwordmanAdapter>(std::move(services));
    });
    return result;
}
void CharacterControllerRegistry::registerController(CharacterControllerInfo info, CharacterControllerFactory factory) {
    validateIdentity(info.identity);
    readinessName(info.readiness);
    checkStatusName(info.automatedRuntimeEvidence.status);
    if (info.executable() != bool(factory)) throw std::invalid_argument("Controller availability/factory mismatch");
    if (info.readiness == ControllerReadiness::ExistingPartialCandidate &&
        (!(info.identity == CharacterIdentity{}) || info.implementation != "world-swordman-existing-partial"))
        throw std::invalid_argument("Partial compatibility is restricted to the existing base Swordman");
    if (info.readiness == ControllerReadiness::NativeChainClosed) {
        if (!info.nativeConfirmed())
            throw std::invalid_argument("Native controller requires confirmed source, action, skill and distinct user-check evidence");
    }
    if (info.readiness == ControllerReadiness::ReconstructedBeta &&
        (!info.runtimeComplete() || !info.automatedRuntimeEvidence.passed()))
        throw std::invalid_argument("Reconstructed beta controller requires source identity, explained complete behavior and passed runtime checks");
    if (info.readiness == ControllerReadiness::ExperimentalUserTest &&
        (!hasText(info.implementation) || !hasText(info.limitation) || !validHash(info.pvfSha256) ||
         info.identity.growtype != 0 || info.identity.awakening != 0 || info.identity.jobId == 0))
        throw std::invalid_argument("Experimental test entry requires source identity, explicit incomplete scope and a separate base non-Swordman controller");
    if (info.readiness == ControllerReadiness::UserAdvancementPartial &&
        (info.implementation!="source-advancement-existing-actions-v1" || !hasText(info.limitation) ||
         !validHash(info.pvfSha256) || info.identity.growtype<=0))
        throw std::invalid_argument("User advancement adapter needs exact source identity, incomplete scope and a nonbase branch");
    if (deferredJobs_.count(info.identity.jobId) && info.readiness != ControllerReadiness::DeferredByUser)
        throw std::invalid_argument("User-deferred job cannot be enabled or have its deferral replaced");
    const auto found = entries_.find(info.identity);
    if (found != entries_.end() && found->second.info.executable())
        throw std::invalid_argument("Executable controller already registered");
    if (info.readiness == ControllerReadiness::DeferredByUser) {
        for (const auto &entry : entries_)
            if (entry.first.jobId == info.identity.jobId && entry.second.info.executable())
                throw std::invalid_argument("Cannot defer a job with an executable controller already registered");
        deferredJobs_.insert(info.identity.jobId);
    }
    const auto identity = info.identity;
    entries_[identity] = {std::move(info), std::move(factory)};
}
const CharacterControllerInfo *CharacterControllerRegistry::find(CharacterIdentity identity) const {
    const auto found = entries_.find(identity);
    return found == entries_.end() ? nullptr : &found->second.info;
}
bool CharacterControllerRegistry::supports(CharacterIdentity identity) const {
    const auto info = find(identity);
    return info && info->executable();
}
std::unique_ptr<CharacterController> CharacterControllerRegistry::create(CharacterIdentity identity, CharacterControllerServices services) const {
    const auto found = entries_.find(identity);
    if (found == entries_.end() || !found->second.info.executable() || !found->second.factory)
        throw std::runtime_error("Character controller not restored for exact identity");
    auto result = found->second.factory(std::move(services));
    if (!result || !(result->identity() == identity)) throw std::runtime_error("Controller factory returned the wrong identity");
    return result;
}
Json CharacterControllerRegistry::snapshot() const {
    Json result = Json::array();
    for (const auto &entry : entries_) result.push_back(entry.second.info.snapshot());
    return result;
}
std::vector<OrderedCharacterBinding> orderedCharacterBindings(const CharacterDefinition &definition) {
    std::vector<OrderedCharacterBinding> result;
    std::map<std::string, std::map<size_t, size_t>> occurrences;
    for (const auto &resource : definition.resources) {
        auto &fields = occurrences[normalize(resource.tag)];
        const auto inserted = fields.emplace(resource.fieldOffset, fields.size());
        result.push_back({result.size(), inserted.first->second, resource});
    }
    return result;
}
EquipmentJobRestriction equipmentJobRestriction(const CharacterDefinition &character, const Script &equipment) {
    EquipmentJobRestriction result;
    result.sourceJob = character.job;
    for (const auto &field : equipment.fields)
        if (normalize(field.tag) == "[usable job]") result.fields.push_back(field);
    if (result.fields.size() != 1 || result.sourceJob.empty() || result.fields[0].values.empty()) return result;
    bool allowed = false;
    for (const auto &value : result.fields[0].values) {
        if (!value.is_string()) return result;
        const auto job = normalize(value.get<std::string>());
        if (job.empty() || job.front() != '[' || job.back() != ']') return result;
        if (job == "[all]" || job == normalize(result.sourceJob)) allowed = true;
    }
    result.gate = allowed ? EquipmentJobGate::Allowed : EquipmentJobGate::Excluded;
    return result;
}
bool equipmentAllowsJob(const CharacterDefinition &character, const Script &equipment) {
    return equipmentJobRestriction(character, equipment).gate == EquipmentJobGate::Allowed;
}

std::string skillGateName(SkillGate gate) {
    switch (gate) {
    case SkillGate::Accepted: return "accepted";
    case SkillGate::WrongCharacter: return "wrong_character";
    case SkillGate::MissingImplementation: return "missing_implementation";
    case SkillGate::UnknownKind: return "unknown_kind";
    case SkillGate::PassiveHasNoConsumer: return "passive_has_no_consumer";
    case SkillGate::SourceLearningUnresolved: return "source_learning_unresolved";
    case SkillGate::SourceLearningExcluded: return "source_learning_excluded";
    case SkillGate::LearningNotQualified: return "learning_not_qualified";
    case SkillGate::InvalidLevel: return "invalid_level";
    case SkillGate::NotLearned: return "not_learned";
    case SkillGate::PassiveCannotActivate: return "passive_cannot_activate";
    case SkillGate::Dead: return "dead";
    case SkillGate::StateBlocked: return "state_blocked";
    case SkillGate::Cooldown: return "cooldown";
    case SkillGate::InsufficientMp: return "insufficient_mp";
    }
    throw std::invalid_argument("Unknown skill gate");
}
CharacterSkillState::CharacterSkillState(CharacterIdentity identity) : identity_(identity) { validateIdentity(identity); }
SkillGate CharacterSkillState::policyGate(const RuntimeSkillPolicy &policy) const {
    if (policy.key.jobId != identity_.jobId || policy.key.skillId < 0) return SkillGate::WrongCharacter;
    if (!policy.implemented) return SkillGate::MissingImplementation;
    if (policy.kind == SkillSourceKind::Unknown) return SkillGate::UnknownKind;
    if (policy.kind == SkillSourceKind::Passive && !policy.passiveConsumerBound) return SkillGate::PassiveHasNoConsumer;
    if (policy.maximumLevel <= 0) return SkillGate::InvalidLevel;
    return SkillGate::Accepted;
}
int CharacterSkillState::learnedLevel(SkillKey key) const {
    const auto found = states_.find(key);
    return found == states_.end() ? 0 : found->second.level;
}
void CharacterSkillState::setLearnedLevel(SkillKey key, int level) {
    validateKey(key);
    if (level < 0) throw std::invalid_argument("Negative learned skill level");
    states_[key].level = level;
}
SkillGate CharacterSkillState::checkLearning(const RuntimeSkillPolicy &policy, int targetLevel,
                                             const SkillLearningAuthorization &authorization) const {
    if (!(authorization.identity == identity_)) return SkillGate::WrongCharacter;
    const auto gate = policyGate(policy);
    if (gate != SkillGate::Accepted) return gate;
    if (authorization.source == SourceLearningState::ExplicitlyExcluded) return SkillGate::SourceLearningExcluded;
    if (authorization.source != SourceLearningState::ExplicitLearningCandidate) return SkillGate::SourceLearningUnresolved;
    if (!authorization.qualificationPassed) return SkillGate::LearningNotQualified;
    if (targetLevel < 1 || targetLevel > policy.maximumLevel || targetLevel != learnedLevel(policy.key) + int64_t(1))
        return SkillGate::InvalidLevel;
    return SkillGate::Accepted;
}
SkillGate CharacterSkillState::learn(const RuntimeSkillPolicy &policy, int targetLevel,
                                     const SkillLearningAuthorization &authorization) {
    const auto gate = checkLearning(policy, targetLevel, authorization);
    if (gate == SkillGate::Accepted) states_[policy.key].level = targetLevel;
    return gate;
}
int64_t CharacterSkillState::remainingCooldown(SkillKey key, int64_t nowMs) const {
    validateTime(nowMs);
    const auto found = states_.find(key);
    return found == states_.end() || found->second.cooldownUntilMs <= nowMs ? 0 : found->second.cooldownUntilMs - nowMs;
}
void CharacterSkillState::startCooldown(SkillKey key, int64_t nowMs, int64_t durationMs) {
    validateKey(key);
    const auto until = expiry(nowMs, durationMs);
    states_[key].cooldownUntilMs = until;
}
void CharacterSkillState::clearCooldowns() {
    for (auto &entry : states_) entry.second.cooldownUntilMs = 0;
}
SkillGate CharacterSkillState::checkUse(const RuntimeSkillPolicy &policy, const SkillUseContext &context, int availableMp) const {
    validateTime(context.nowMs);
    if (context.mpCost < 0 || context.cooldownMs < 0 || availableMp < 0)
        throw std::invalid_argument("Negative skill resource value");
    if (!(context.identity == identity_)) return SkillGate::WrongCharacter;
    const auto gate = policyGate(policy);
    if (gate != SkillGate::Accepted) return gate;
    if (policy.kind == SkillSourceKind::Passive) return SkillGate::PassiveCannotActivate;
    const auto level = learnedLevel(policy.key);
    if (level == 0) return SkillGate::NotLearned;
    if (level > policy.maximumLevel) return SkillGate::InvalidLevel;
    if (!context.alive) return SkillGate::Dead;
    if (!context.stateAllowsUse) return SkillGate::StateBlocked;
    if (!context.ignoreCooldown && remainingCooldown(policy.key, context.nowMs) > 0) return SkillGate::Cooldown;
    if (!context.ignoreMpGate && availableMp < context.mpCost) return SkillGate::InsufficientMp;
    return SkillGate::Accepted;
}
SkillGate CharacterSkillState::commitUse(const RuntimeSkillPolicy &policy, const SkillUseContext &context, int &availableMp) {
    const auto gate = checkUse(policy, context, availableMp);
    if (gate != SkillGate::Accepted) return gate;
    // Allocate/update the ledger before spending MP so allocation failure cannot
    // leave a half-committed resource transaction. No controller callback here.
    if (context.startCooldown) startCooldown(policy.key, context.nowMs, context.cooldownMs);
    availableMp = std::max(0, availableMp - context.mpCost);
    return SkillGate::Accepted;
}
Json CharacterSkillState::snapshot(int64_t nowMs) const {
    validateTime(nowMs);
    Json result = preserved_, records = Json::array();
    result["schema"] = 1;
    Json identity = result.contains("identity") && result["identity"].is_object() ? result["identity"] : Json::object();
    identity["job_id"] = identity_.jobId;
    identity["growtype"] = identity_.growtype;
    identity["awakening"] = identity_.awakening;
    result["identity"] = std::move(identity);
    for (const auto &entry : states_) {
        Json record = entry.second.preserved;
        // Preserve any unknown fields in the serialized key object as well.
        Json key = record.contains("key") && record["key"].is_object() ? record["key"] : Json::object();
        key["job_id"] = entry.first.jobId;
        key["skill_id"] = entry.first.skillId;
        record["key"] = key;
        record["level"] = entry.second.level;
        record["remaining_cooldown_ms"] = remainingCooldown(entry.first, nowMs);
        records.push_back(std::move(record));
    }
    result["skills"] = std::move(records);
    return result;
}
void CharacterSkillState::restore(const Json &value, int64_t nowMs) {
    validateTime(nowMs);
    if (!value.is_object() || !value.contains("schema") || boundedInt(value.at("schema"), "schema") != 1)
        throw std::invalid_argument("Unsupported skill ledger schema");
    if (!(storedIdentity(value.at("identity")) == identity_)) throw std::invalid_argument("Skill ledger identity mismatch");
    if (!value.at("skills").is_array()) throw std::invalid_argument("Skill ledger records are not an array");
    std::map<SkillKey, LearnedSkillState> pending;
    for (const auto &record : value.at("skills")) {
        if (!record.is_object()) throw std::invalid_argument("Invalid skill ledger record");
        const auto key = storedKey(record.at("key"));
        const auto level = boundedInt(record.at("level"), "level");
        const auto duration = nonnegativeInteger(record.at("remaining_cooldown_ms"), "remaining_cooldown_ms");
        if (!pending.emplace(key, LearnedSkillState{level, expiry(nowMs, duration), record}).second)
            throw std::invalid_argument("Ambiguous duplicate skill ledger key");
    }
    Json preserved = value;
    states_.swap(pending);
    preserved_.swap(preserved);
}

} // namespace dnf
