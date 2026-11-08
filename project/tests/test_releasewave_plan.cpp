#include "dnf/releasewave_plan.hpp"
#include <limits>
#include <stdexcept>
#ifdef DNF_RELEASEWAVE_PLAN_STANDALONE
#include "dnf/entry.hpp"
#include <iostream>
#endif

namespace dnf {
Json runReleaseWavePlanTests(Pvf &pvf) {
    Json checks = Json::array();
    const auto check = [&](bool ok, const std::string &name) {
        if (!ok) throw std::runtime_error("ReleaseWave plan: " + name);
        checks.push_back(name);
    };
    CharacterCatalog catalog(pvf);
    const auto source = readReleaseWaveSourceContract(pvf, catalog);
    check(source.skill == SkillKey{0,32} && source.skillData.definition.kind == SkillSourceKind::Active &&
        source.skillData.definition.source.script.path == "skill/swordman/releasewave.skl" &&
        source.skillData.definition.source.bytes == pvf.read("skill/swordman/releasewave.skl"),
        "Job-local32 uses actual registered ReleaseWave SKL and preserved raw bytes;20 is not substituted");
    check(!source.skillData.definition.source.script.tokens.empty() &&
        source.skillData.selected.at("[level info]").field.offset == 267 &&
        source.skillData.selected.at("[level info]").scope == "dungeon" &&
        source.skillData.values("[consume MP]") == Json::array({65,630}) &&
        source.skillData.values("[cool time]") == Json::array({15000,0}),
        "Dungeon selection retains ordered tokens, offsets, mode and both MP/CD endpoints");
    check(source.phaseMotions[0].animation->duration == 150 && source.phaseMotions[1].animation->duration == 600 &&
        source.phaseBindings[0].scope == "[throw motion 2-1]" &&
        source.phaseBindings[1].scope == "[throw motion 2-2]" &&
        source.phaseMotions[0].source.memberPath == catalog.at(0).motion("[throw motion 2-1]") &&
        source.phaseMotions[1].source.memberPath == catalog.at(0).motion("[throw motion 2-2]"),
        "Both cast bodies come from exact current CHR throw2 pair rather than a folder guess");
    check(source.objectRegistration.id == 20018 &&
        source.objectRegistration.path == "passiveobject/character/swordman/releasewave.obj" &&
        source.objectMotionBinding.byteOffset == 42 && source.objectAttackBinding.byteOffset == 52 &&
        source.attackInfo.script.path == "passiveobject/character/swordman/attackinfo/releasewave.atk" &&
        source.floatingHeight == 1,
        "Registered20018 OBJ links exact basic ANI/ATK fields and keeps floating height as metadata");
    check(source.visuals[0].animation->duration == 490 && source.visuals[1].animation->duration == 420 &&
        source.visuals[0].animation->frames.size() == 7 && source.visuals[1].animation->frames.size() == 6 &&
        source.visuals[0].animation->frames.back().image.empty() &&
        source.visuals[1].animation->frames.back().image.empty(),
        "Two source visual lifetimes and final empty images remain separate from the logical attack");
    check(source.attackAnimation.animation->duration == 400 && source.attackAnimation.animation->frames.size() == 5,
        "The no-image attack has its own source five-by80ms timeline");
    for (size_t frame = 0; frame < 5; ++frame) {
        const auto boxes = source.attackBoxesAt(frame);
        check(source.attackAnimation.animation->frames[frame].image.empty() && boxes.size() == 1 &&
            boxes[0].x == -84 && boxes[0].y == -50 && boxes[0].z == 0 &&
            boxes[0].w == 168 && boxes[0].h == 100 && boxes[0].d == (frame == 4 ? 200 : 234),
            "Current1031 no-image frame" + std::to_string(frame) + " keeps its actual XYZ attack box");
        bool exactSpan = false;
        for (const auto &node : source.attackAnimation.byteSpans)
            if (node.at("kind") == "box" && node.at("frame") == frame)
                exactSpan = node.at("source").at("byte_offset") == 11 + frame * 50 &&
                    node.at("source").at("byte_length") == 26 && node.at("type") == 15;
        check(exactSpan,"ANI box frame" + std::to_string(frame) + " retains its source byte offset and extent");
    }
    for (const auto *resource : {&source.characterSource,&source.objectRegistry,&source.objectSource,&source.attackInfo,
        &source.phaseMotions[0],&source.phaseMotions[1],&source.visuals[0],&source.visuals[1],&source.attackAnimation}) {
        check(resource->source.packageIdentity == pvf.identity() && resource->raw == pvf.read(resource->source.memberPath) &&
            resource->source.memberSha256 == sha256(resource->raw) && resource->source.byteLength == resource->raw.size(),
            "Source identity/bytes/hash remain available: " + resource->source.memberPath);
    }
    check(source.attackInfo.script.values("[push aside]") == Json::array({400}) &&
        source.attackInfo.script.values("[lift up]") == Json::array({400}) &&
        source.attackInfo.script.values("[hit wav]") == Json::array({"R_SHOCKWAVE_HIT"}),
        "Original ATK reaction/movement/sound fields are retained without claiming final damage or hit acceptance");
    const auto exported = source.snapshot(true);
    check(exported.at("attack_animation").at("raw_bytes").get<Bytes>() == source.attackAnimation.raw &&
        exported.at("object").at("tokens") == source.objectSource.script.tokens &&
        exported.at("object_registry").at("tokens") == source.objectRegistry.script.tokens &&
        !exported.at("skill_runtime_complete").get<bool>() && !exported.at("native_controller_restored").get<bool>(),
        "Explicit export retains raw ANI/OBJ/registry tokens without claiming runtime skill completion");

    const CharacterIdentity asura{0,4,0};
    check(evaluateReleaseWaveQualification(source,asura,1,25).ok,
        "Accurate Asura identity at source level may pass source qualification only");
    check(!evaluateReleaseWaveQualification(source,{0,0,0},1,99).ok &&
        !evaluateReleaseWaveQualification(source,{0,1,0},1,99).ok &&
        !evaluateReleaseWaveQualification(source,{2,4,0},1,99).ok,
        "Base Swordman, SwordSoul and another job cannot borrow32 even at high level");
    check(!evaluateReleaseWaveQualification(source,asura,0,99).ok &&
        !evaluateReleaseWaveQualification(source,asura,1,24).ok &&
        !evaluateReleaseWaveQualification(source,asura,2,27).ok &&
        evaluateReleaseWaveQualification(source,asura,2,28).ok &&
        !evaluateReleaseWaveQualification(source,asura,51,999).ok,
        "Learned level, source required-level interval and all-means maximum remain independent gates");

    ReleaseWaveActivationRequest request;
    request.identity = asura; request.learnedLevel = 1; request.characterLevel = 25;
    request.owner = request.localOwner = {11,7}; request.ownerLive = true;
    request.actionId = 51; request.attackId = 71; request.position = {320,240,9}; request.direction = -1;
    const auto before = source.snapshot().dump();
    const auto plan = planReleaseWavePhaseEvent(source, request);
    check(plan.ok && plan.ownerGatePassed && plan.spawns.size() == 3 && plan.phaseDurationMs == std::array<int,2>{0,600},
        "Named default duration chooses zero then currentSKL static600, separate from body duration150");
    check(plan.spawns[0].kind == ReleaseWaveSpawnKind::Visual && plan.spawns[0].signedAttachmentArgument == 1 &&
        plan.spawns[1].kind == ReleaseWaveSpawnKind::Visual && plan.spawns[1].signedAttachmentArgument == -1 &&
        plan.spawns[2].kind == ReleaseWaveSpawnKind::AttackEntity && plan.spawns[2].objectId == 20018,
        "Phase0 ordered plan emits visual1,visual2 then the conditional registered logical entity");
    check(plan.spawns[2].position == request.position && plan.spawns[2].speed == 0 &&
        plan.spawns[2].direction == -1 && plan.spawns[2].scalar == 929 &&
        plan.spawns[2].owner == request.owner && plan.spawns[2].actionId == 51 && plan.spawns[2].attackId == 71 &&
        !plan.spawns[2].followsOwnerPosition && plan.spawns[2].removeOnAnimationEnd,
        "Attack keeps actorXYZ without floating-height addition or throw velocity; IDs and scalar929 are instance data");
    check(plan.spawns[0].followsOwnerPosition && plan.spawns[1].followsOwnerPosition &&
        plan.spawns[0].attackId == 0 && plan.spawns[1].attackId == 0 &&
        plan.spawns[0].animation->duration != plan.spawns[2].animation->duration,
        "Visuals follow position with independent timelines and never receive an attack identity");
    check(plan.json().at("trace").dump().find("inferred-1031-releasewave-unmodified-column0-v1") != std::string::npos &&
        plan.json().at("diagnostics").dump().find("phase_duration_inference") != std::string::npos &&
        source.snapshot().dump() == before,
        "Plan preserves immutable source and exposes named scalar/duration/owner inference diagnostics");

    auto changed = request; changed.localOwner.generation++;
    auto gated = planReleaseWavePhaseEvent(source,changed);
    check(gated.ok && !gated.ownerGatePassed && gated.spawns.size() == 2 &&
        gated.spawns[0].kind == ReleaseWaveSpawnKind::Visual && gated.spawns[1].kind == ReleaseWaveSpawnKind::Visual,
        "Stale local-owner generation rejects only logical spawn after the two ordered visuals");
    changed = request; changed.ownerLive = false; changed.attackId = 0;
    gated = planReleaseWavePhaseEvent(source,changed);
    check(gated.ok && !gated.ownerGatePassed && gated.spawns.size() == 2,
        "Failed live-owner gate does not require or allocate a logical attack ID");
    changed = request; changed.phase = 1;
    const auto phase1 = planReleaseWavePhaseEvent(source,changed);
    check(phase1.ok && phase1.spawns.empty() && phase1.phaseDurationMs == plan.phaseDurationMs,
        "Phase1 does not respawn phase0 visuals or attack");
    ReleaseWavePolicies comparison; comparison.duration = ReleaseWaveDurationPolicy::InferredSourceMotionDurationsV1;
    check(planReleaseWavePhaseEvent(source,request,comparison).phaseDurationMs == std::array<int,2>{150,600},
        "Explicit comparison policy uses source body lifetimes and stays separately labelled inference");
    changed = request; changed.learnedLevel = 2; changed.characterLevel = 28;
    check(planReleaseWavePhaseEvent(source,changed).spawns.back().scalar == 1016,
        "Scalar consumes actual current level row rather than a demo damage constant");

    const auto rejected = [&](const ReleaseWaveSourceContract &input, const ReleaseWaveActivationRequest &r,
                              const std::string &name) {
        const auto result = planReleaseWavePhaseEvent(input,r);
        check(!result.ok && result.spawns.empty() && !result.reason.empty(), name);
    };
    changed = request; changed.identity = {};
    rejected(source,changed,"Invalid base qualification rejects the entire activation before any spawn");
    changed = request; changed.owner = {};
    rejected(source,changed,"An invalid owner handle cannot create orphaned visuals");
    changed = request; changed.actionId = 0;
    rejected(source,changed,"Zero action identity cannot create an unowned activation");
    changed = request; changed.attackId = 0;
    rejected(source,changed,"An accepted logical spawn requires a nonzero supplied attack identity");
    changed = request; changed.phase = 2;
    rejected(source,changed,"Unknown cast phases cannot create operations");
    changed = request; changed.position[0] = std::numeric_limits<float>::infinity();
    rejected(source,changed,"Nonfinite spawn coordinates cannot enter the host");
    auto broken = source; broken.skillData.definition.key = {0,20};
    rejected(broken,request,"NormalWave20 source cannot satisfy ReleaseWave32 identity");
    broken = source; broken.attackAnimation.animation.reset();
    rejected(broken,request,"Missing attack animation rejects visuals as part of atomic source preflight");
    broken = source; broken.visuals[1].source.packageIdentity = "different-version";
    rejected(broken,request,"Cross-version resource mixing rejects the whole activation");
    broken = source; broken.skillData.ambiguousFields.insert("[level info]");
    rejected(broken,request,"Ambiguous selected level table cannot silently pick one source field");
    broken = source; broken.skillData.selected.at("[static data]").field.values = Json::array();
    rejected(broken,request,"An authored-empty static duration rejects the selected policy instead of inventing a duration");
    broken = source;
    auto altered = std::make_shared<Animation>(*source.attackAnimation.animation);
    altered->frames.back().boxes.front().d = 201; broken.attackAnimation.animation = altered;
    check(broken.attackBoxesAt(4).front().d == 201 && source.attackBoxesAt(4).front().d == 200,
        "Attack geometry consumer reads the supplied actual frame rather than a frozen60US or1031 box constant");
    bool outOfRange = false;
    try { source.attackBoxesAt(5); } catch (const std::out_of_range &) { outOfRange = true; }
    check(outOfRange,"Past-end geometry access rejects instead of looping or reusing the last attack frame");
    const auto pvp = readReleaseWaveSourceContract(pvf,catalog,"pvp");
    const auto pvpPlan = planReleaseWavePhaseEvent(pvp,request);
    check(pvpPlan.ok && pvpPlan.spawns.back().scalar == 62 && pvpPlan.phaseDurationMs[1] == 800 &&
        pvp.skillData.selected.at("[level info]").field.offset == 672 &&
        source.skillData.selected.at("[level info]").field.offset == 267,
        "Explicit PvP source mode changes scalar62/static800 without mutating dungeon929/static600");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},
        {"source",source.snapshot()},{"phase0_plan",plan.json()},{"phase1_plan",phase1.json()},
        {"pvp_plan",pvpPlan.json()},{"verification_scope","source and pure plan only; no World/MP/CD/collision/normal advancement"},
        {"frontend_started",false},{"skill_runtime_complete",false}};
}
} // namespace dnf

#ifdef DNF_RELEASEWAVE_PLAN_STANDALONE
static int runReleaseWaveTests(int argc, char **argv) {
    try {
        if (argc != 3) throw std::runtime_error("Expected PVF path and new report path");
        dnf::Pvf pvf(std::filesystem::u8path(argv[1]));
        const auto report = dnf::runReleaseWavePlanTests(pvf);
        dnf::writeJson(std::filesystem::u8path(argv[2]),report);
        std::cout << "ReleaseWave source/plan checks passed: " << report.at("count") << '\n';
        return 0;
    } catch (const std::exception &e) { std::cerr << e.what() << '\n'; return 1; }
}
DNF_ENTRY(runReleaseWaveTests)
#endif
