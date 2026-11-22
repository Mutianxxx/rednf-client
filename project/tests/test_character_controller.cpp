#include "dnf/character_controller.hpp"
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
class ProbeController final : public CharacterController {
    CharacterIdentity identity_;
  public:
    explicit ProbeController(CharacterIdentity identity) : identity_(identity) {}
    CharacterIdentity identity() const override { return identity_; }
    bool request(const CharacterActionRequest &) override { return true; }
    void tick(int64_t) override {}
    void cancel(ControllerCancelReason) override {}
};
NativeEvidenceRef evidence(const std::string &label) {
    return {"confirmed", "synthetic-test/" + label + ".json", "test-anchor", "test fixture only", {}, {}, {}};
}
NativeControllerChain completeChain(const std::string &prefix) {
    return {evidence(prefix+"/qualification"), evidence(prefix+"/input"), evidence(prefix+"/commit"),
        evidence(prefix+"/action"), evidence(prefix+"/contact"), evidence(prefix+"/continuation"),
        evidence(prefix+"/cleanup")};
}
NativeEvidenceRef inferredEvidence(const std::string &label) {
    auto result = evidence(label);
    result.classification = "inferred";
    result.basis = "Synthetic source-consumer inference used only to exercise admission";
    result.unverifiedConditions = "Original-client timing and visual parity remain unverified";
    result.impact = "Execute this fixture as reconstructed beta behavior without native confirmation";
    return result;
}
NativeControllerChain reconstructedChain(const std::string &prefix) {
    // Mixed classifications must remain visible rather than being promoted to
    // confirmed when the complete implementation passes its automated checks.
    return {evidence(prefix+"/qualification"), inferredEvidence(prefix+"/input"), evidence(prefix+"/commit"),
        inferredEvidence(prefix+"/action"), inferredEvidence(prefix+"/contact"), evidence(prefix+"/continuation"),
        inferredEvidence(prefix+"/cleanup")};
}
CharacterControllerInfo reconstructedInfo(CharacterIdentity identity) {
    CharacterControllerInfo info;
    info.identity = identity;
    info.name = "synthetic-test beta controller";
    info.implementation = "synthetic-test/executable-controller-fixture";
    info.readiness = ControllerReadiness::ReconstructedBeta;
    info.exeSha256 = "246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264";
    info.pvfSha256 = "d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d";
    for (const auto action : {CharacterAction::Move, CharacterAction::Jump, CharacterAction::BasicAttack,
                              CharacterAction::DashAttack, CharacterAction::JumpAttack, CharacterAction::CommandInput})
        info.actionEvidence.emplace(action, reconstructedChain("beta/action"));
    info.requiredRuntimeSkills = {{identity.jobId,9}, {identity.jobId,10}};
    for (const auto key : info.requiredRuntimeSkills)
        info.skillEvidence.emplace(key, reconstructedChain("beta/skill/"+std::to_string(key.skillId)));
    info.automatedRuntimeEvidence = {ControllerCheckStatus::Passed, "synthetic-test/beta-runtime.json", "all-lifecycles",
        "Fixture admission checks only; this is not evidence of a playable implementation"};
    return info;
}
}
Json runCharacterControllerTests(Pvf &pvf) {
    Json checks = Json::array();
    auto check = [&](bool ok, const std::string &message) {
        if (!ok) throw std::runtime_error("Character controller contract: " + message);
        checks.push_back(message);
    };
    auto throws = [](auto callback) {
        try { callback(); } catch (const std::exception &) { return true; }
        return false;
    };
    CharacterCatalog catalog(pvf);
    auto registry = CharacterControllerRegistry::currentCandidate(catalog);
    check(registry.snapshot().size() == catalog.definitions.size(),
          "Every current CHR has an explicit controller coverage record");
    check(registry.supports({0,0,0}) && !registry.supports({0,1,0}) && !registry.supports({0,0,1}) &&
          !registry.supports({9,0,0}) && !registry.supports({999,0,0}),
          "Registry lookup uses exact job, growtype and awakening without Swordman fallback");
    for (int id = 1; id < 10; ++id)
        check(registry.find({id,0,0}) && !registry.supports({id,0,0}),
              "Unfinished class remains disabled: " + std::to_string(id));
    check(registry.find({10,0,0})->readiness == ControllerReadiness::DeferredByUser &&
          registry.find({0,0,0})->readiness == ControllerReadiness::ExistingPartialCandidate,
          "Creator deferral and existing partial Swordman are explicit distinct states");
    int requests = 0, ticks = 0, cancels = 0;
    CharacterControllerServices services;
    services.request = [&](const CharacterActionRequest &request) {
        ++requests;
        return request.action == CharacterAction::BasicAttack || request.action == CharacterAction::CommandInput ||
            (request.action == CharacterAction::Skill && request.skill && request.skill->jobId == 0);
    };
    services.tick = [&](int64_t) { ++ticks; };
    services.cancel = [&](ControllerCancelReason) { ++cancels; };
    auto controller = registry.create({}, services);
    CharacterActionRequest request;
    check(controller->identity() == CharacterIdentity{} && controller->request(request) && requests == 1,
          "Existing factory invokes the executable host action callback");
    request.action = CharacterAction::Skill; request.skill = SkillKey{9,64};
    check(!controller->request(request) && requests == 1,
          "Existing adapter refuses a foreign local skill ID before host mutation");
    request.skill = SkillKey{0,-1};
    check(!controller->request(request) && requests == 1,
          "Unresolved skills cannot be encoded as a negative SkillKey sentinel");
    request.skill.reset();
    check(!controller->request(request) && requests == 1,
          "A skill action requires an explicit resolved SkillKey");
    request.skill = SkillKey{0,64};
    check(controller->request(request) && requests == 2,
          "A resolved job-local SkillKey reaches the controller host");
    request.action = CharacterAction::CommandInput;
    request.skill.reset();
    request.inputKey = 6;
    check(controller->request(request) && requests == 3,
          "Command-sequence input remains distinct from a concrete skill request");
    controller->tick(16); controller->tick(16); controller->tick(33);
    check(ticks == 2 && throws([&] { controller->tick(32); }),
          "Adapter uses monotonic simulation time and does not tick twice for the same instant");
    controller->cancel(ControllerCancelReason::Reload); controller->tick(0);
    check(cancels == 1 && ticks == 3, "Cancellation reaches host cleanup and allows a reset simulation clock");
    check(throws([&] { registry.create({}, {}); }) && throws([&] { registry.create({1,0,0}, services); }),
          "Missing callbacks and an unfinished class never produce a no-op executable controller");
    CharacterControllerInfo unfinished;
    unfinished.identity = {1,0,0}; unfinished.implementation = "synthetic-test";
    unfinished.readiness = ControllerReadiness::NativeChainClosed;
    check(throws([&] { registry.registerController(unfinished, [](CharacterControllerServices) { return std::unique_ptr<CharacterController>(); }); }),
          "A new executable class cannot register without complete native action proof and source identity");
    unfinished.readiness = ControllerReadiness::ExistingPartialCandidate;
    check(throws([&] { registry.registerController(unfinished, [](CharacterControllerServices) { return std::unique_ptr<CharacterController>(); }); }),
          "The legacy partial exception cannot be assigned to another character");
    unfinished.readiness = ControllerReadiness::NativeChainClosed;
    unfinished.exeSha256 = "246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264";
    unfinished.pvfSha256 = "d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d";
    unfinished.normalInputEvidence = evidence("normal-input");
    unfinished.originalClientComparisonEvidence = evidence("original-client");
    for (auto action : {CharacterAction::Move, CharacterAction::Jump, CharacterAction::BasicAttack,
                        CharacterAction::DashAttack, CharacterAction::JumpAttack})
        unfinished.actionEvidence.emplace(action, completeChain("class/action"));
    unfinished.requiredRuntimeSkills.insert({1,9});
    unfinished.skillEvidence.emplace(SkillKey{1,9}, completeChain("class/skill"));
    auto nullFactoryRegistry = CharacterControllerRegistry::currentCandidate(catalog);
    nullFactoryRegistry.registerController(unfinished, [](CharacterControllerServices) {
        return std::unique_ptr<CharacterController>();
    });
    check(throws([&] { nullFactoryRegistry.create({1,0,0}, services); }),
          "A registered factory must return a controller instance before the class can execute");
    registry.registerController(unfinished, [](CharacterControllerServices) {
        return std::make_unique<ProbeController>(CharacterIdentity{1,0,0});
    });
    auto probe = registry.create({1,0,0}, {});
    check(registry.supports({1,0,0}) && probe->identity() == CharacterIdentity{1,0,0},
          "A complete exact-identity evidence record and executable factory can register without a fixed job count");
    auto incompleteEvidence = completeChain("test");
    incompleteEvidence.exitCleanup.classification = "inferred";
    check(!incompleteEvidence.nativeConfirmed() && !incompleteEvidence.runtimeComplete() &&
          evidence("test").report.rfind("synthetic-test/",0) == 0,
          "An unexplained inferred link fails both gates and synthetic references remain visibly namespaced");
    CharacterControllerRegistry emptyRegistry;
    CharacterControllerInfo missingSkills = unfinished;
    missingSkills.identity = {2,0,0};
    missingSkills.requiredRuntimeSkills.clear(); missingSkills.skillEvidence.clear();
    for (auto &entry : missingSkills.actionEvidence) entry.second = completeChain("gunner/action");
    check(throws([&] { emptyRegistry.registerController(missingSkills, [](CharacterControllerServices) {
        return std::make_unique<ProbeController>(CharacterIdentity{2,0,0});
    }); }), "Basic action proof alone cannot close a class with an omitted runtime skill set");

    const CharacterIdentity betaIdentity{8,1,0};
    const auto beta = reconstructedInfo(betaIdentity);
    const auto betaFactory = [betaIdentity](CharacterControllerServices) {
        return std::make_unique<ProbeController>(betaIdentity);
    };
    auto betaRegistry = CharacterControllerRegistry::currentCandidate(catalog);
    betaRegistry.registerController(beta, betaFactory);
    auto betaController = betaRegistry.create(betaIdentity, {});
    check(betaRegistry.supports(betaIdentity) && betaController->identity() == betaIdentity && beta.runtimeComplete() &&
          !beta.nativeConfirmed(),
          "A complete mixed confirmed/inferred beta registers and creates its exact identity with passed automated evidence");
    check(!betaRegistry.supports({8,0,0}) && !betaRegistry.supports({8,1,1}) && !betaRegistry.supports({10,0,0}),
          "Registering one beta identity does not open its base, awakening or deferred Creator");
    const auto betaSnapshot = betaRegistry.find(betaIdentity)->snapshot();
    check(betaSnapshot.at("readiness") == "reconstructed_beta" && betaSnapshot.at("execution_complete") == true &&
          betaSnapshot.at("native_confirmed") == false && betaSnapshot.at("automated_runtime").at("passed") == true &&
          betaSnapshot.at("user_checks").at("normal_input").at("status") == "pending" &&
          betaSnapshot.at("user_checks").at("original_client_comparison").at("status") == "pending" &&
          betaSnapshot.at("actions")[0].at("chain").at("execution_complete") == true &&
          betaSnapshot.at("actions")[0].at("chain").at("native_confirmed") == false &&
          betaSnapshot.at("actions")[0].at("chain").at("input_request").at("classification") == "inferred",
          "Execution completeness, native confirmation, automatic evidence and pending user checks are reported independently");
    const auto legacySnapshot = betaRegistry.find({})->snapshot();
    check(legacySnapshot.at("executable") == true && legacySnapshot.at("execution_complete") == false &&
          legacySnapshot.at("native_confirmed") == false,
          "The historical partial Swordman remains executable without being relabelled a complete beta or native implementation");
    check(unfinished.nativeConfirmed() && unfinished.runtimeComplete() &&
          registry.find({1,0,0})->snapshot().at("native_confirmed") == true,
          "The strict native route continues to require and report its separate confirmed evidence");
    auto allInferred = beta;
    const auto inferredChain = [](const std::string &label) {
        const auto ref = inferredEvidence(label);
        return NativeControllerChain{ref,ref,ref,ref,ref,ref,ref};
    };
    for (auto &entry : allInferred.actionEvidence) entry.second = inferredChain("all-inferred/action");
    for (auto &entry : allInferred.skillEvidence) entry.second = inferredChain("all-inferred/skill");
    CharacterControllerRegistry allInferredRegistry;
    allInferredRegistry.registerController(allInferred, betaFactory);
    check(allInferredRegistry.create(betaIdentity, {})->identity() == betaIdentity &&
          allInferred.runtimeComplete() && !allInferred.nativeConfirmed(),
          "A fully explained reconstruction can execute beta behavior without any native-confirmed lifecycle links");

    const auto rejectsBeta = [&](const CharacterControllerInfo &candidate) {
        CharacterControllerRegistry target;
        return throws([&] { target.registerController(candidate, betaFactory); }) && !target.supports(candidate.identity);
    };
    auto malformedBeta = beta;
    malformedBeta.readiness = ControllerReadiness::NativeChainClosed;
    malformedBeta.normalInputEvidence = evidence("beta/user-input");
    malformedBeta.originalClientComparisonEvidence = evidence("beta/client-comparison");
    check(rejectsBeta(malformedBeta),
          "Passed automated and user checks cannot promote any inferred lifecycle link to NativeChainClosed");
    for (const auto member : {&NativeControllerChain::releaseQualification, &NativeControllerChain::inputRequest,
                             &NativeControllerChain::stateCommit, &NativeControllerChain::actionAndAttack,
                             &NativeControllerChain::contactAndEffects, &NativeControllerChain::continuation,
                             &NativeControllerChain::exitCleanup}) {
        auto chain = completeChain("all-seven");
        chain.*member = inferredEvidence("all-seven/inferred");
        check(chain.runtimeComplete() && !chain.nativeConfirmed(),
              "Every one of the seven links accepts explained inference without claiming native confirmation");
        chain.*member = {};
        check(!chain.runtimeComplete() && !chain.nativeConfirmed(),
              "Omitting any one of the seven lifecycle links blocks complete runtime admission");
    }
    for (const auto classification : {"unknown", "placeholder", "user_tuning", "inferred_typo", ""}) {
        malformedBeta = beta;
        malformedBeta.skillEvidence.at({8,9}).actionAndAttack.classification = classification;
        check(rejectsBeta(malformedBeta), "Unknown or placeholder classification rejects a beta skill: "+std::string(classification));
    }
    for (const auto member : {&NativeEvidenceRef::report, &NativeEvidenceRef::anchor, &NativeEvidenceRef::finding,
                             &NativeEvidenceRef::basis, &NativeEvidenceRef::unverifiedConditions, &NativeEvidenceRef::impact}) {
        malformedBeta = beta;
        malformedBeta.actionEvidence.at(CharacterAction::Move).inputRequest.*member = " \t\n";
        check(rejectsBeta(malformedBeta),
              "Whitespace cannot stand in for a source reference, inference basis, unresolved conditions or impact");
    }
    for (const auto status : {ControllerCheckStatus::Pending, ControllerCheckStatus::Failed}) {
        malformedBeta = beta;
        malformedBeta.automatedRuntimeEvidence.status = status;
        check(rejectsBeta(malformedBeta), "Pending or failed automatic runtime validation cannot admit a reconstructed controller");
    }
    malformedBeta = beta; malformedBeta.automatedRuntimeEvidence.status = ControllerCheckStatus(999);
    check(rejectsBeta(malformedBeta), "An unknown validation status cannot be published as runtime evidence");
    for (const auto member : {&ControllerCheckEvidence::report, &ControllerCheckEvidence::anchor, &ControllerCheckEvidence::finding}) {
        malformedBeta = beta;
        malformedBeta.automatedRuntimeEvidence.*member = "";
        check(rejectsBeta(malformedBeta), "An asserted automatic pass must have an attributable report, anchor and finding");
    }
    malformedBeta = beta; malformedBeta.exeSha256 = "unidentified";
    check(rejectsBeta(malformedBeta), "A reconstructed controller requires a valid executable source hash");
    malformedBeta = beta; malformedBeta.pvfSha256.clear();
    check(rejectsBeta(malformedBeta), "A reconstructed controller requires a valid content source hash");
    malformedBeta = beta; malformedBeta.implementation = " \n";
    check(rejectsBeta(malformedBeta), "Explained source evidence does not replace an implementation identifier");
    malformedBeta = beta; malformedBeta.actionEvidence.erase(CharacterAction::JumpAttack);
    check(rejectsBeta(malformedBeta), "A missing mandatory basic action prevents full beta admission");
    malformedBeta = beta; malformedBeta.actionEvidence[CharacterAction::CommandInput] = {};
    check(rejectsBeta(malformedBeta), "An extra declared action cannot contain an unfinished lifecycle");
    malformedBeta = beta; malformedBeta.actionEvidence[CharacterAction(999)] = reconstructedChain("bad-action");
    check(rejectsBeta(malformedBeta), "An unknown action category cannot be used as complete runtime evidence");
    malformedBeta = beta; malformedBeta.skillEvidence.erase({8,9});
    check(rejectsBeta(malformedBeta), "Every declared required runtime skill needs its complete evidence chain");
    malformedBeta = beta; malformedBeta.skillEvidence.emplace(SkillKey{8,11}, reconstructedChain("undeclared"));
    check(rejectsBeta(malformedBeta), "Undeclared skill evidence cannot hide a mismatch in the required runtime set");
    malformedBeta = beta; malformedBeta.requiredRuntimeSkills.clear(); malformedBeta.skillEvidence.clear();
    check(rejectsBeta(malformedBeta), "A reconstructed character cannot declare its entire runtime skill set empty");
    malformedBeta = beta; malformedBeta.requiredRuntimeSkills.erase({8,9}); malformedBeta.skillEvidence.erase({8,9});
    malformedBeta.requiredRuntimeSkills.insert({9,9});
    malformedBeta.skillEvidence.emplace(SkillKey{9,9}, reconstructedChain("foreign"));
    check(rejectsBeta(malformedBeta), "A complete chain for a foreign job does not cover the required local skill");
    malformedBeta = beta; malformedBeta.requiredRuntimeSkills.erase({8,9}); malformedBeta.skillEvidence.erase({8,9});
    malformedBeta.requiredRuntimeSkills.insert({8,-1});
    malformedBeta.skillEvidence.emplace(SkillKey{8,-1}, reconstructedChain("negative"));
    check(rejectsBeta(malformedBeta), "Negative skill identifiers cannot be used to close declared beta coverage");
    malformedBeta = beta; malformedBeta.readiness = ControllerReadiness(999);
    check(rejectsBeta(malformedBeta), "An unknown readiness value cannot publish an executable record");
    CharacterControllerRegistry noFactoryRegistry;
    check(throws([&] { noFactoryRegistry.registerController(beta); }) && !noFactoryRegistry.supports(betaIdentity),
          "Complete inferred evidence and automated passes still require a real factory binding");
    CharacterControllerRegistry wrongFactoryRegistry;
    wrongFactoryRegistry.registerController(beta, [](CharacterControllerServices) {
        return std::make_unique<ProbeController>(CharacterIdentity{0,0,0});
    });
    check(throws([&] { wrongFactoryRegistry.create(betaIdentity, {}); }),
          "An inferred beta factory cannot execute an instance with a different character identity");
    CharacterControllerRegistry emptyBetaFactoryRegistry;
    emptyBetaFactoryRegistry.registerController(beta, [](CharacterControllerServices) {
        return std::unique_ptr<CharacterController>();
    });
    check(throws([&] { emptyBetaFactoryRegistry.create(betaIdentity, {}); }),
          "An inferred beta factory returning no instance cannot execute");
    auto deferralRegistry = CharacterControllerRegistry::currentCandidate(catalog);
    const auto creatorBeta = reconstructedInfo({10,0,0});
    check(throws([&] { deferralRegistry.registerController(creatorBeta, [](CharacterControllerServices) {
        return std::make_unique<ProbeController>(CharacterIdentity{10,0,0});
    }); }) && !deferralRegistry.supports({10,0,0}),
          "Complete inferred metadata cannot revoke the source-declared user deferral of Creator");
    const auto creatorBranchBeta = reconstructedInfo({10,1,0});
    check(throws([&] { deferralRegistry.registerController(creatorBranchBeta, [](CharacterControllerServices) {
        return std::make_unique<ProbeController>(CharacterIdentity{10,1,0});
    }); }) && !deferralRegistry.supports({10,1,0}),
          "A deferred job cannot be opened through a new branch identity");
    CharacterControllerInfo erasedDeferral;
    erasedDeferral.identity = {10,0,0};
    check(throws([&] { deferralRegistry.registerController(erasedDeferral); }) &&
          deferralRegistry.find({10,0,0})->readiness == ControllerReadiness::DeferredByUser,
          "Replacing a deferred record with unavailable cannot bypass the user deferral on a later registration");
    auto preservedRegistry = CharacterControllerRegistry::currentCandidate(catalog);
    malformedBeta = reconstructedInfo({8,0,0});
    malformedBeta.skillEvidence.at({8,9}).exitCleanup = {};
    check(throws([&] { preservedRegistry.registerController(malformedBeta, [](CharacterControllerServices) {
        return std::make_unique<ProbeController>(CharacterIdentity{8,0,0});
    }); }) && preservedRegistry.find({8,0,0})->readiness == ControllerReadiness::Unavailable &&
          !preservedRegistry.supports({8,0,0}),
          "A rejected incomplete replacement leaves the previous disabled source record intact");

    CharacterDefinition synthetic;
    synthetic.resources = {{"[attack motion]", "A.ani", "a.ani", 10, 0, true},
        {"[attack motion]", "", "", 10, 1, false}, {"[attack motion]", "A.ani", "a.ani", 30, 0, true}};
    const auto bindings = orderedCharacterBindings(synthetic);
    check(bindings.size() == 3 && bindings[0].sourceOrdinal == 0 && bindings[1].resource.literal.empty() &&
          bindings[1].resource.valueIndex == 1 && bindings[1].occurrence == 0 && bindings[2].occurrence == 1,
          "Ordered binding projection preserves duplicate tags, empty slots, source offsets and original ordinals");
    for (const auto &definition : catalog.definitions) {
        const auto ordered = orderedCharacterBindings(definition);
        bool equal = ordered.size() == definition.resources.size();
        for (size_t i = 0; i < ordered.size(); ++i) {
            const auto &a = ordered[i].resource, &b = definition.resources[i];
            equal = equal && a.tag == b.tag && a.literal == b.literal && a.path == b.path &&
                a.fieldOffset == b.fieldOffset && a.valueIndex == b.valueIndex;
        }
        check(equal, "Real CHR binding projection retains every source entry: " + std::to_string(definition.registration.id));
    }
    Script equipment;
    equipment.fields = {{"[usable job]", Json::array({"[fighter]", "[at fighter]"}), 18}};
    check(equipmentAllowsJob(catalog.at(1), equipment) && equipmentAllowsJob(catalog.at(7), equipment) &&
          !equipmentAllowsJob(catalog.at(0), equipment) && !equipmentAllowsJob(catalog.at(5), equipment),
          "Equipment qualification uses actual CHR tags rather than Swordman or filename substitution");
    equipment.fields[0].values = Json::array({"[all]"});
    check(equipmentAllowsJob(catalog.at(8), equipment), "Explicit all-job equipment permits the actual male Mage job");
    equipment.fields.push_back(equipment.fields[0]);
    check(equipmentJobRestriction(catalog.at(8), equipment).gate == EquipmentJobGate::Unresolved,
          "Ambiguous repeated usable-job fields remain unresolved");
    equipment.fields.clear();
    check(!equipmentAllowsJob(catalog.at(0), equipment), "Absent job restriction does not authorize equipment");

    CharacterSkillState state;
    const SkillKey swordKey{0,64}, darkKey{9,64};
    state.startCooldown(swordKey,100,500);
    state.startCooldown(darkKey,100,900);
    check(state.remainingCooldown(swordKey,200) == 400 && state.remainingCooldown(darkKey,200) == 800,
          "Equal numeric skill IDs from different jobs have independent cooldowns");
    state.setLearnedLevel(swordKey,0);
    state.clearCooldowns();
    check(state.remainingCooldown(swordKey,100) == 0 && state.learnedLevel(swordKey) == 0,
          "Clearing cooldowns preserves an explicit zero learned level");
    for (int id = 0; id < 128; ++id) state.setLearnedLevel({0,1000+id}, id%5);
    check(state.learnedLevel({0,1127}) == 2, "Skill ledger has no fixed thirteen-controller capacity");
    RuntimeSkillPolicy active{swordKey, SkillSourceKind::Active, true, false, 20};
    SkillLearningAuthorization authorization;
    authorization.identity = {}; authorization.qualificationPassed = true;
    check(state.learn(active,1,authorization) == SkillGate::SourceLearningUnresolved && state.learnedLevel(swordKey) == 0,
          "Implementation alone cannot authorize unresolved source learning");
    authorization.source = SourceLearningState::ExplicitlyExcluded;
    check(state.learn(active,1,authorization) == SkillGate::SourceLearningExcluded,
          "Explicit source exclusion remains distinct from unresolved learning");
    authorization.source = SourceLearningState::ExplicitLearningCandidate;
    authorization.qualificationPassed = false;
    check(state.learn(active,1,authorization) == SkillGate::LearningNotQualified,
          "A source learning candidate alone does not pass branch, prerequisite and cost checks");
    authorization.qualificationPassed = true;
    check(state.learn(active,1,authorization) == SkillGate::Accepted && state.learnedLevel(swordKey) == 1 &&
          state.learn(active,3,authorization) == SkillGate::InvalidLevel,
          "Authorized learning commits one level and rejects skipped level purchases");
    RuntimeSkillPolicy passive{{0,0},SkillSourceKind::Passive,true,false,10};
    check(state.learn(passive,1,authorization) == SkillGate::PassiveHasNoConsumer,
          "Passive display data cannot be learned without a bound behavior or attribute consumer");
    passive.passiveConsumerBound = true;
    check(state.learn(passive,1,authorization) == SkillGate::Accepted,
          "Explicit passive consumer binding participates in learning eligibility");
    RuntimeSkillPolicy unavailable = active; unavailable.implemented = false;
    check(state.learn(unavailable,2,authorization) == SkillGate::MissingImplementation,
          "A source file never grants runtime skill implementation");
    SkillUseContext context;
    context.nowMs = 1000; context.mpCost = 5; context.cooldownMs = 500;
    int mp = 20;
    check(state.checkUse(active,context,mp) == SkillGate::Accepted && mp == 20,
          "Request eligibility has no MP or cooldown side effects");
    state.setLearnedLevel(swordKey,0);
    check(state.commitUse(active,context,mp) == SkillGate::NotLearned && mp == 20 && state.remainingCooldown(swordKey,1000) == 0,
          "Commit rechecks level zero after an earlier accepted request and cannot spend resources");
    state.setLearnedLevel(swordKey,1);
    context.stateAllowsUse = false;
    check(state.commitUse(active,context,mp) == SkillGate::StateBlocked && mp == 20,
          "Commit rechecks class state before resource mutation");
    context.stateAllowsUse = true;
    check(state.commitUse(active,context,mp) == SkillGate::Accepted && mp == 15 && state.remainingCooldown(swordKey,1000) == 500 &&
          state.commitUse(active,context,mp) == SkillGate::Cooldown && mp == 15,
          "Accepted use spends once and repeated use is rejected by its qualified cooldown");
    context.nowMs = 1500; mp = 4;
    check(state.commitUse(active,context,mp) == SkillGate::InsufficientMp && mp == 4,
          "Insufficient MP leaves the ledger and resource counter untouched");
    mp = 20; context.startCooldown = false;
    check(state.commitUse(active,context,mp) == SkillGate::Accepted && mp == 15 && state.remainingCooldown(swordKey,1500) == 0,
          "Controller can defer CD until its proven later event without changing the MP transaction");
    check(state.checkUse(passive,context,mp) == SkillGate::PassiveCannotActivate,
          "A learned passive cannot be dispatched as an active skill");
    context.identity = {0,1,0};
    check(state.commitUse(active,context,mp) == SkillGate::WrongCharacter && mp == 15,
          "Use transaction requires the exact current advancement and awakening identity");

    auto saved = state.snapshot(1500);
    saved["future_root"] = "retained"; saved["identity"]["future_identity"] = 7;
    saved["skills"][0]["future_record"] = Json::array({1,2});
    saved["skills"][0]["key"]["future_key"] = true;
    CharacterSkillState restored;
    restored.restore(saved,2000);
    const auto roundtrip = restored.snapshot(2000);
    check(roundtrip == saved, "Relative-time persistence retains unknown root, identity, key and per-skill fields");
    auto duplicate = saved; duplicate["skills"].push_back(duplicate["skills"][0]);
    check(throws([&] { restored.restore(duplicate,3000); }) && restored.snapshot(2000) == saved,
          "Duplicate skill keys reject the entire restore without partial mutation");
    auto wrongIdentity = saved; wrongIdentity["identity"]["job_id"] = 9;
    check(throws([&] { restored.restore(wrongIdentity,2000); }), "Persistence cannot migrate a ledger silently to another class");
    auto fractional = saved; fractional["skills"][0]["level"] = 1.5;
    check(throws([&] { restored.restore(fractional,2000); }), "Fractional saved levels do not become learned skill levels");
    restored.startCooldown(swordKey,2000,500);
    CharacterSkillState rebased;
    rebased.restore(restored.snapshot(2100),0);
    check(rebased.remainingCooldown(swordKey,0) == 400 && rebased.remainingCooldown(swordKey,400) == 0,
          "Reload restores remaining duration relative to the new simulation epoch");
    state.startCooldown(swordKey,std::numeric_limits<int64_t>::max()-2,10);
    check(state.remainingCooldown(swordKey,std::numeric_limits<int64_t>::max()-2) == 2,
          "Cooldown expiry saturates without signed overflow");
    check(throws([&] { state.startCooldown(swordKey,0,-1); }) && throws([&] { state.setLearnedLevel(swordKey,-1); }) &&
          throws([&] { state.remainingCooldown(swordKey,-1); }),
          "Negative simulation times, cooldowns and learned levels are rejected");
    return {{"status","pass"},{"checks",checks},{"check_count",checks.size()},
        {"scope","Exact-identity factory boundary, complete inferred beta admission independent of native and user checks, preserved user deferrals, source job restriction, ordered CHR bindings and SkillKey transactions; synthetic registration checks validate gates only and do not claim new playable characters or original-client dynamic parity"}};
}
} // namespace dnf
