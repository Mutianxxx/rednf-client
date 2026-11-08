#include "dnf/combat.hpp"
#include "dnf/entry.hpp"
#include "dnf/scene_presentation.hpp"
#include "dnf/scene.hpp"
#include "dnf/storage.hpp"
#include "dnf/geometry.hpp"
#include "dnf/font.hpp"
#include "dnf/dungeon_selection.hpp"
#include "dnf/content_profile.hpp"
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <SDL.h>
using namespace dnf;
namespace dnf {
Json runSkillEffectsTests(Pvf &, Assets &);
Json runMonsterEffectsTests(Pvf &, Assets &);
Json runMonsterEquipmentTests(Pvf &, Assets &);
Json runElvengardFlowTests(Pvf &, Assets &);
Json runCombatFeedbackTests(Pvf &, Assets &);
Json runCharacterCatalogTests(Pvf &, Assets &);
Json runNativeAttackTests(Pvf &, Assets &);
Json runAnimationClockTests(Pvf &, Assets &);
Json runEffectCoordinatesTests(Pvf &, Assets &);
Json runFemaleGunnerTimingTests(Pvf &, Assets &);
Json runFemaleGunnerSkillLayerTests(Pvf &, Assets &);
Json runSelectionUiTests(Pvf &, Assets &);
Json runPortalVisualTests(Pvf &, Assets &);
Json runPortalStateTests(Pvf &, Assets &);
Json runSourceSkillActionTests(Pvf &, Assets &);
Json runFighterNativeGrabTests(Pvf &, Assets &);
Json runWaterCannonRuntimeTests(Pvf &,Assets &);
Json runWaterCannonNormalTests(Pvf &,Assets &);
Json runPriestUpperRuntimeTests(Pvf &,Assets &);
Json runHedgehogRuntimeTests(Pvf &,Assets &);
Json runLowKickRuntimeTests(Pvf &,Assets &);
Json runMageThrustRuntimeTests(Pvf &,Assets &);
Json runMageUpperRuntimeTests(Pvf &,Assets &);
Json runGunnerKneeRuntimeTests(Pvf &,Assets &);
Json runFighterUpperRuntimeTests(Pvf &,Assets &);
Json runExperimentalMovementReactionTests(Pvf &,Assets &);
Json runPickupActionTests(Pvf &,Assets &);
Json runWorldPresentationSourceTests(Pvf &,Assets &);
Json runCharacterAdvancementTests(Pvf &,Assets &);
Json runCharacterAdvancementCacheTests(Pvf &,Assets &);
Json runSelectionFeedbackSourceTests(Pvf &, Assets &);
Json runTextInputTests();
Json runSkillReleaseRegressionTests(Pvf &, Assets &);
Json runHudSourceTests(Pvf &, Assets &);
Json runFemaleGunnerSourceTests(Pvf &, Assets &);
Json runFemaleGunnerWorldTests(Pvf &, Assets &);
Json runFemaleGunnerContactWorldTests(Pvf &, Assets &);
Json runFemaleGunnerContactWorldInferredClockTests(Pvf &, Assets &);
Json runFemaleGunnerEntityTests(Pvf &, Assets &);
Json runFemaleGunnerHeavyLayersTests(Pvf &, Assets &);
Json runFemaleGunnerModifierTests(Pvf &, Assets &);
Json runAttackStatusDormantTests(Pvf &, Assets &);
Json runStatusEffectsTests(Pvf &, Assets &);
Json runStatusEffectsWorldTests(Pvf &, Assets &);
Json runBusinessUiSourceTests(Pvf &);
Json runMapRenderingTests(Pvf &, Assets &);
Json runUserFeedbackTests(Pvf &, Assets &);
Json runCharacterIdentityTests(Pvf &);
Json runAnimationEventTests(Assets &);
Json runAxisMotionTests(Pvf &, Assets &);
Json runParticleMotionTests(Pvf &);
Json runStaticMotionTests();
Json runSkillEligibilityTests(Pvf &, Assets &);
Json runCharacterControllerTests(Pvf &);
Json runDungeonSelectionTests(Pvf &, Assets &);
Json runObjectSystemTests(Pvf &, Assets &);
Json runEquipmentMotionTests(Pvf &, Assets &);
Json runSkillDataTests(Pvf &, Assets &);
Json runContentProfileTests(Pvf &, Assets &);
Json runPvfLoadingTests();
Json runScenePreparationTests(Pvf &,Assets &);
Json runMonsterHurtVariationTests(Pvf &, Assets &);
Json runObjectPresentationTests(Pvf &, Assets &);
Json runFemaleGunnerReleaseOriginTests(Pvf &, Assets &);
Json runFemaleGunnerJumpWeaponTests(Pvf &, Assets &);
Json runFemaleGunnerSourceCacheTests(Pvf &, Assets &);
Json runFemaleGunnerAmmoFlightTests(Pvf &, Assets &);
Json runBasicAttackMovementTests(Pvf &, Assets &);
Json runMonsterActionAiTests(Pvf &, Assets &);
Json runContentCatalogTests(Pvf &, Assets &);
Json runSimulationTests();
Json runTransactionStorageTests();
Json runTransactionStorageWorldTests(Pvf &, Assets &);
Json runSessionLayoutTests(Pvf &, Assets &);
Json runWorldSimulationTests(Pvf &, Assets &);
Json runSkillCostTests(Pvf &);
Json runSkillCostWorldTests(Pvf &, Assets &);
Json runAttributeTests(Pvf &);
Json runAttributeWorldTests(Pvf &, Assets &);
Json runSpeedAttributeTests(Pvf &, Assets &);
Json runSpeedWorldTests(Pvf &, Assets &);
Json runDebugTests(Pvf &, Assets &);
Json runBetaBranchTests();
Json runBetaCharacterTests(Pvf &,Assets &);
Json runDebugWindowTests(Pvf &, Assets &);
Json runEquipmentAttributeTests(Pvf &, Assets &);
Json runEquipmentResourceWorldTests(Pvf &, Assets &);
Json runEquipmentTransactionTests(Pvf &, Assets &);
Json runMonsterAttributeTests(Pvf &, Assets &);
Json runSkillLearningTests(Pvf &);
Json runSecondGrowtypeLearningTests(Pvf &,Assets &);
Json runNormalLearningRuntimeBridgeTests(Pvf &,Assets &);
Json runNormalRewardRuntimeBridgeTests(Pvf &,Assets &);
Json runSkillLearningWorldTests(Pvf &, Assets &);
Json runSkillLearningStorageTests(Pvf &, Assets &);
Json runSkillLearningTransactionTests(Pvf &, Assets &);
Json runCombatAttributeTests(Pvf &, Assets &);
Json runMonsterCombatAttributeTests(Pvf &);
Json runMonsterAccuracyTests(Pvf &,Assets &);
Json runDamageResolutionTests(Pvf &, Assets &);
Json runDamageWorldTests(Pvf &, Assets &);
Json runObjectDamageWorldTests(Pvf &, Assets &);
Json runAttackStatusTests(Pvf &,Assets &);
Json runStatusWorldTests(Pvf &,Assets &);
Json runStatusRoomTests(Pvf &,Assets &);
Json runActRuntimeTests(Pvf &,Assets &);
Json runRestoreHandleTests(Pvf &,Assets &);
Json runActWorldHostTests(Pvf &,Assets &);
Json runActCollisionTests(Pvf &,Assets &);
Json runMonsterDamageWindowTests(Pvf &,Assets &);
Json runMonsterBehaviorTests(Pvf &,Assets &);
Json runSourceActionWorldTests(Pvf &,Assets &);
Json runMonsterEventAiTests(Pvf &);
Json runMonsterEventAiWorldTests(Pvf &,Assets &);
Json runMonsterEventAiTestPolicyTests(Pvf &,Assets &);
Json runMonsterEventAiNormalPolicyTests(Pvf &,Assets &);
Json runSquirrelWorldBridgeTests(Pvf &,Assets &,const std::string &);
Json runSquirrelActionServiceTests(Pvf &,Assets &,const std::string &);
Json runSkillInputFeedbackTests(Pvf &,Assets &);
Json runRuntimePathTests();
Json runMapAccessTests(Pvf &);
Json runCharacterEntryTests(Pvf &,Assets &);
Json runMonsterLevelPolicyTests(Pvf &,Assets &);
Json runSceneTileTests(Pvf &,Assets &);
Json runGunnerBasicRuntimeTests(Pvf &,Assets &);
Json runGunnerRenderProfileTests(Pvf &,Assets &);
Json runTableAttackMissTests(Pvf &,Assets &);
Json runSceneTileRuntimeTests(Pvf &,Assets &);
Json runTownAccessTests(Pvf &,Assets &);
Json runMapExplorationTests(Pvf &,Assets &);
Json runMapExplorationWorldTests(Pvf &,Assets &);
Json runExperimentalCharacterTests(Pvf &,Assets &);
Json runExperimentalStorageTests(Pvf &,Assets &);
Json runCharacterAttackTests(Pvf &,Assets &);
Json runSceneCameraTests(Pvf &,Assets &);
}
namespace dnf { Json runBetaBranchExitTests(Pvf &,Assets &); Json runPendingRewardTests(Pvf &,Assets &); Json runAnimationDynamicsTests(Pvf &,Assets &); Json runRegionProgressionTests(Pvf &,Assets &); Json runAppearanceTests(Pvf &,Assets &); }
static void require(bool b, const char *m) {
    if (!b)
        throw std::runtime_error(m);
}
int run(int argc, char **argv) {
    std::string checkpoint = "startup/font";
    int selectedGroup = -1;
    bool focused40jp = false;
    std::string focused40jpSuite;
    Json contentIdentity;
    Json fontChecks = Json::array();
    Json baseline;
    Json rows = Json::array();
    Json animationDynamics, regionProgression, appearance, skillEffects, monsterEffects, elvengardFlow;
    try {
        if (argc > 2) {
            if (argc != 4)
                throw std::invalid_argument("Usage: dnf_tests CLIENT [--group 0..11 | --focus 40jp]");
            const std::string selector=argv[3];
            focused40jp=std::string(argv[2])=="--focus"&&(selector=="40jp"||selector.rfind("40jp/",0)==0);
            if(focused40jp&&selector!="40jp")focused40jpSuite=selector.substr(5);
            if(!focused40jp) {
                if(std::string(argv[2])!="--group")throw std::invalid_argument("Unknown core test selector");
                selectedGroup = std::stoi(argv[3]);
                if (selectedGroup < 0 || selectedGroup > 11)
                    throw std::invalid_argument("Core test group must be between 0 and 11");
            }
        }
        auto root = std::filesystem::u8path(argc > 1 ? argv[1] : "../DNF1031客户端");
        if (selectedGroup >= 0) {
            const char *drivers[] = {"win32", "win32", "win32", "win32", "win32", "dummy", "win32", "win32", "win32", "dummy", "win32", "win32"};
            SDL_setenv("SDL_VIDEODRIVER", drivers[selectedGroup], 1);
        }
#ifdef _WIN32
        {
            const auto original=readFile(root/"Fonts/msjh.ttf");
            auto source=original;
            {
                HintedFont font(source);
                require(font.available(),"Hinted rasterizer must select the actual source glyph/hint tables");
                fontChecks.push_back("exact source glyf/loca/cmap/hmtx/hhea/fpgm/prep/cvt tables verified");
                require(font.width("赛丽亚",12)==36&&font.width("ABC",12)==18&&font.width("I W",12)==18,
                        "Source Chinese fullwidth and Latin halfwidth metrics");
                fontChecks.push_back("Chinese/Latin widths match actual rasterizer metrics");
                for(int size:{10,11,12,13,14,16,20}) {
                    FontMask mask;
                    require(font.mask("赛丽亚 任务完成。Agjp 123",size,3,mask),"Source mixed UI glyphs rasterize");
                    require(mask.advance==font.width("赛丽亚 任务完成。Agjp 123",size)&&
                            mask.coverage.size()==size_t(mask.width)*mask.height,"Measured and raster advances agree");
                    require(*std::max_element(mask.coverage.begin(),mask.coverage.end())==255,
                            "Small source font has fully bright stroke centres");
                    for(int x=0;x<mask.width;++x)
                        require(mask.coverage[x]==0&&mask.coverage[size_t(mask.height-1)*mask.width+x]==0,
                                "Mixed glyph ascent/descenders are not clipped");
                }
                fontChecks.push_back("7 sizes: bright stroke centres, mixed Chinese/Latin/descenders and unclipped mask");
                FontMask empty;
                require(!font.mask("test",0,3,empty),"Invalid font size rejected");
            }
            require(source==original&&readFile(root/"Fonts/msjh.ttf")==original,
                    "Source font bytes survive private registration and teardown");
            HintedFont invalid(Bytes{0,0,0});require(!invalid.available(),"Unknown font selects portable fallback");
            fontChecks.push_back("source immutable; private font teardown; unknown font fallback");
        }
#endif
        SDL_setenv("SDL_VIDEODRIVER", "dummy", 1);
        checkpoint = "PVF/assets";
        ContentProfile testProfile;
        testProfile.pvfPath = root / "Script.pvf";
        testProfile.resourceRoots = {root};
        const auto testedContent = testProfile.fingerprint();
        contentIdentity = testedContent.json();
        writeJson("reports/test-content-identity.json",{{"identity",testedContent.json()},
            {"effective_profile",testProfile.effective(testedContent)},{"frontend_started",false}});
        Pvf p(root / "Script.pvf", testedContent.pvfSha256);
        Assets a(std::vector<std::filesystem::path>{root}, p, testedContent.manifest);
        if(focused40jp) {
            // Deliberately narrow integration run. Each suite retains its real
            // World/Renderer checks; this never stands in for all core shards.
            size_t focusedCount=0;
            const auto focused=[&](const char *name,const std::function<Json()> &suite) {
                if(!focused40jpSuite.empty()&&focused40jpSuite!=name)return;
                ++focusedCount;
                checkpoint=name;
                std::cout<<"40JP focus: "<<name<<std::endl;
                writeJson(std::filesystem::path("reports/40jp-focus")/(std::string(name)+".json"),suite());
            };
            focused("combat-feedback",[&]{return runCombatFeedbackTests(p,a);});
            focused("monster-ai",[&]{return runMonsterActionAiTests(p,a);});
            focused("monster-effects",[&]{return runMonsterEffectsTests(p,a);});
            focused("monster-equipment",[&]{return runMonsterEquipmentTests(p,a);});
            focused("selection-ui",[&]{return runSelectionUiTests(p,a);});
            focused("source-skill-actions",[&]{return runSourceSkillActionTests(p,a);});
            focused("fighter-upper",[&]{return runFighterUpperRuntimeTests(p,a);});
            focused("fighter-native-grab",[&]{return runFighterNativeGrabTests(p,a);});
            focused("experimental-characters",[&]{return runExperimentalCharacterTests(p,a);});
            if(!focusedCount)throw std::invalid_argument("Unknown 40JP focus suite: "+focused40jpSuite);
            writeJson("reports/40jp-focus/result.json",{{"status","pass"},{"content_identity",contentIdentity},
                {"suite",focused40jpSuite.empty()?"all":focused40jpSuite},{"suite_count",focusedCount},
                {"scope","Focused 40JP changed-path suites only; full regression deferred; frontend pending"}});
            return 0;
        }
        // These groups run in separate processes when the build runner is
        // in parallel mode. Their working directories are isolated so report
        // files, saves and temporary SDL state cannot race with another group.
        if (selectedGroup < 0 || selectedGroup == 0) {
        checkpoint = "Pvf advancement source cache lifetime and World isolation";
        writeJson("reports/seven-job-world/character-advancement-cache-tests.json",
            runCharacterAdvancementCacheTests(p,a));
        checkpoint = "content profiles, source identity and independent static roots";
        writeJson("reports/beta-foundation/runtime-path-tests.json", runRuntimePathTests());
        writeJson("reports/beta-foundation/content-profile-tests.json", runContentProfileTests(p, a));
        writeJson("reports/seven-job-world/pvf-loading-tests.json",runPvfLoadingTests());
        writeJson("reports/seven-job-world/scene-preparation-tests.json",runScenePreparationTests(p,a));
        writeJson("reports/seven-job-world/scene-tiles-tests.json",runSceneTileTests(p,a));
        writeJson("reports/seven-job-world/scene-tiles-runtime-tests.json",runSceneTileRuntimeTests(p,a));
        writeJson("reports/seven-job-world/monster-hurt-variation-tests.json",runMonsterHurtVariationTests(p,a));
        writeJson("reports/seven-job-world/object-presentation-tests.json",runObjectPresentationTests(p,a));
        }
        if (selectedGroup < 0 || selectedGroup == 10) {
        writeJson("reports/seven-job-world/female-release-key-tests.json",runFemaleGunnerReleaseOriginTests(p,a));
        writeJson("reports/seven-job-world/female-jump-weapon-tests.json",runFemaleGunnerJumpWeaponTests(p,a));
        writeJson("reports/seven-job-world/female-source-cache-tests.json",runFemaleGunnerSourceCacheTests(p,a));
        writeJson("reports/seven-job-world/female-ammo-flight-tests.json",runFemaleGunnerAmmoFlightTests(p,a));
        writeJson("reports/seven-job-world/basic-attack-movement-tests.json",runBasicAttackMovementTests(p,a));
        writeJson("reports/seven-job-world/gunner-basic-runtime-tests.json",runGunnerBasicRuntimeTests(p,a));
        writeJson("reports/seven-job-world/gunner-knee-runtime-tests.json",runGunnerKneeRuntimeTests(p,a));
        }
        if (selectedGroup < 0 || selectedGroup == 11) {
        writeJson("reports/seven-job-world/fighter-upper-runtime-tests.json",runFighterUpperRuntimeTests(p,a));
        writeJson("reports/seven-job-world/experimental-movement-reaction-tests.json",runExperimentalMovementReactionTests(p,a));
        writeJson("reports/seven-job-world/gunner-render-profile-tests.json",runGunnerRenderProfileTests(p,a));
        writeJson("reports/seven-job-world/monster-action-ai-tests.json",runMonsterActionAiTests(p,a));
        }
        if (selectedGroup < 0 || selectedGroup == 1) {
        checkpoint = "full source membership and capability dependency contracts";
        writeJson("reports/beta-foundation/content-catalog-tests.json", runContentCatalogTests(p, a));
        checkpoint = "deterministic simulation infrastructure";
        writeJson("reports/beta-foundation/simulation-tests.json", runSimulationTests());
        writeJson("reports/beta-foundation/world-simulation-tests.json", runWorldSimulationTests(p,a));
        checkpoint = "same-generation recoverable storage";
        writeJson("reports/beta-foundation/transaction-storage-tests.json", runTransactionStorageTests());
        writeJson("reports/beta-foundation/transaction-storage-world-tests.json", runTransactionStorageWorldTests(p,a));
        checkpoint = "selected dungeon layout restoration without reroll";
        writeJson("reports/beta-foundation/session-layout-tests.json", runSessionLayoutTests(p,a));
        checkpoint = "source skill endpoint and final-cost trace";
        writeJson("reports/beta-foundation/skill-cost-tests.json", runSkillCostTests(p));
        checkpoint = "runtime source skill cost consumers";
        writeJson("reports/beta-foundation/skill-cost-world-tests.json", runSkillCostWorldTests(p,a));
        checkpoint = "source character base attributes and live growth consumers";
        writeJson("reports/beta-foundation/attribute-tests.json", runAttributeTests(p));
        writeJson("reports/beta-foundation/attribute-world-tests.json", runAttributeWorldTests(p,a));
        checkpoint = "source equipment speed and real movement/attack consumers";
        writeJson("reports/beta-foundation/speed-attribute-tests.json",runSpeedAttributeTests(p,a));
        writeJson("reports/beta-foundation/speed-world-tests.json",runSpeedWorldTests(p,a));
        checkpoint = "source equipment resources and atomic runtime changes";
        writeJson("reports/beta-foundation/equipment-attribute-tests.json",runEquipmentAttributeTests(p,a));
        writeJson("reports/beta-foundation/equipment-resource-world-tests.json",runEquipmentResourceWorldTests(p,a));
        writeJson("reports/beta-foundation/equipment-transaction-tests.json",runEquipmentTransactionTests(p,a));
        }
        if (selectedGroup < 0 || selectedGroup == 2) {
        checkpoint = "source monster HP and frozen session policy";
        writeJson("reports/beta-foundation/monster-attribute-tests.json",runMonsterAttributeTests(p,a));
        checkpoint = "source learning, runtime use and durable purchasing";
        writeJson("reports/beta-learning/skill-learning-tests.json",runSkillLearningTests(p));
        writeJson("reports/beta-learning/second-growtype-learning-tests.json",runSecondGrowtypeLearningTests(p,a));
        checkpoint = "normal learned runtime bridge and durable prepared publication";
        writeJson("reports/beta-learning/normal-learning-runtime-bridge-tests.json",runNormalLearningRuntimeBridgeTests(p,a));
        checkpoint = "normal learned runtime and pending reward final generation bridge";
        writeJson("reports/beta-learning/normal-reward-runtime-bridge-tests.json",runNormalRewardRuntimeBridgeTests(p,a));
        writeJson("reports/beta-learning/skill-learning-world-tests.json",runSkillLearningWorldTests(p,a));
        writeJson("reports/beta-learning/skill-learning-storage-tests.json",runSkillLearningStorageTests(p,a));
        writeJson("reports/beta-learning/skill-learning-transaction-tests.json",runSkillLearningTransactionTests(p,a));
        checkpoint = "typed equipment and monster combat attributes";
        writeJson("reports/beta-learning/combat-attribute-tests.json",runCombatAttributeTests(p,a));
        writeJson("reports/beta-learning/monster-combat-attribute-tests.json",runMonsterCombatAttributeTests(p));
        writeJson("reports/beta-learning/monster-accuracy-tests.json",runMonsterAccuracyTests(p,a));
        writeJson("reports/seven-job-world/table-attack-miss-tests.json",runTableAttackMissTests(p,a));
        writeJson("reports/beta-learning/damage-resolution-tests.json",runDamageResolutionTests(p,a));
        writeJson("reports/beta-learning/damage-world-tests.json",runDamageWorldTests(p,a));
        writeJson("reports/beta-learning/object-damage-world-tests.json",runObjectDamageWorldTests(p,a));
        writeJson("reports/beta-status/attack-status-tests.json",runAttackStatusTests(p,a));
        writeJson("reports/beta-status/status-world-tests.json",runStatusWorldTests(p,a));
        writeJson("reports/beta-status/status-room-tests.json",runStatusRoomTests(p,a));
        writeJson("reports/beta-status/restore-handle-tests.json",runRestoreHandleTests(p,a));
        }
        if (selectedGroup < 0 || selectedGroup == 3) {
        checkpoint = "ACT source runtime, World host and source action service";
        writeJson("reports/beta-act/act-runtime-tests.json",runActRuntimeTests(p,a));
        writeJson("reports/beta-act/act-world-host-tests.json",runActWorldHostTests(p,a));
        writeJson("reports/seven-job-world/act-collision-tests.json",runActCollisionTests(p,a));
        writeJson("reports/seven-job-world/monster-damage-window-tests.json",runMonsterDamageWindowTests(p,a));
        writeJson("reports/beta-act/monster-behavior-tests.json",runMonsterBehaviorTests(p,a));
        writeJson("reports/beta-act/source-action-world-tests.json",runSourceActionWorldTests(p,a));
        checkpoint = "source Event.ai and accepted-contact World action service";
        writeJson("reports/beta-act/monster-event-ai-tests.json",runMonsterEventAiTests(p));
        writeJson("reports/beta-act/monster-event-ai-world-tests.json",runMonsterEventAiWorldTests(p,a));
        writeJson("reports/beta-act/monster-event-ai-test-policy-tests.json",runMonsterEventAiTestPolicyTests(p,a));
        writeJson("reports/seven-job-world/monster-event-ai-normal-policy-tests.json",runMonsterEventAiNormalPolicyTests(p,a));
        checkpoint = "all-map source directory and prepared exploration";
        writeJson("reports/beta-experiment/map-access-tests.json",runMapAccessTests(p));
        writeJson("reports/seven-job-world/character-entry-tests.json",runCharacterEntryTests(p,a));
        writeJson("reports/beta-experiment/town-access-tests.json",runTownAccessTests(p,a));
        writeJson("reports/beta-experiment/map-exploration-tests.json",runMapExplorationTests(p,a));
        writeJson("reports/beta-experiment/map-exploration-world-tests.json",runMapExplorationWorldTests(p,a));
        }
        if (selectedGroup < 0 || selectedGroup == 4) {
        checkpoint = "opt-in source character actions, manual skills and isolated persistence";
        writeJson("reports/beta-experiment/experimental-character-tests.json",runExperimentalCharacterTests(p,a));
        writeJson("reports/beta-experiment/experimental-storage-tests.json",runExperimentalStorageTests(p,a));
        writeJson("reports/beta-experiment/character-attack-tests.json",runCharacterAttackTests(p,a));
        writeJson("reports/beta-experiment/scene-camera-tests.json",runSceneCameraTests(p,a));
        checkpoint = "World source NUT action lifecycle and default skill input";
        writeJson("reports/beta-script/squirrel-world-bridge-tests.json",runSquirrelWorldBridgeTests(p,a,testedContent.archiveManifestHash));
        writeJson("reports/beta-script/squirrel-action-service-tests.json",runSquirrelActionServiceTests(p,a,testedContent.archiveManifestHash));
        writeJson("reports/beta-experiment/skill-input-feedback-tests.json",runSkillInputFeedbackTests(p,a));
        checkpoint = "isolated beta management commands and save branch";
        writeJson("reports/beta-foundation/beta-branch-tests.json",runBetaBranchTests());
        writeJson("reports/beta-foundation/beta-character-tests.json",runBetaCharacterTests(p,a));
        writeJson("reports/beta-foundation/debug-tests.json",runDebugTests(p,a));
        }
        if (selectedGroup < 0 || selectedGroup == 5) {
        checkpoint = "SDL dummy dual-window management; no frontend";
        SDL_setenv("SDL_VIDEODRIVER","dummy",1);
        writeJson("reports/beta-foundation/debug-window-tests.json",runDebugWindowTests(p,a));
        checkpoint = "source HUD controls and dummy-only runtime consumer";
        writeJson("reports/knowledge-base/hud-source-tests.json",runHudSourceTests(p,a));
        checkpoint = "requested business UI and source skill execution";
        writeJson("reports/knowledge-base/business-ui-source-tests.json",runBusinessUiSourceTests(p));
        writeJson("reports/knowledge-base/attack-status-dormant-tests.json",runAttackStatusDormantTests(p,a));
        writeJson("reports/knowledge-base/status-effects-tests.json",runStatusEffectsTests(p,a));
        writeJson("reports/knowledge-base/status-effects-world-tests.json",runStatusEffectsWorldTests(p,a));
        writeJson("reports/knowledge-base/female-gunner-source-tests.json",runFemaleGunnerSourceTests(p,a));
        writeJson("reports/knowledge-base/female-gunner-world-tests.json",runFemaleGunnerWorldTests(p,a));
        writeJson("reports/knowledge-base/female-gunner-contact-world-tests.json",runFemaleGunnerContactWorldTests(p,a));
        writeJson("reports/knowledge-base/female-gunner-contact-inferred-clock-tests.json",runFemaleGunnerContactWorldInferredClockTests(p,a));
        const auto femaleEntities=runFemaleGunnerEntityTests(p,a);
        writeJson("reports/knowledge-base/female-gunner-entities-tests.json",femaleEntities);
        require(femaleEntities.at("status")=="passed","Female Gunner phase graph failures; see complete per-skill report");
        writeJson("reports/knowledge-base/female-gunner-modifiers-tests.json",runFemaleGunnerModifierTests(p,a));
        checkpoint = "actual female gunner heavy-weapon stage consumers";
        const auto femaleHeavy=runFemaleGunnerHeavyLayersTests(p,a);
        writeJson("reports/selection-ime/female-gunner-heavy-layers-tests.json",femaleHeavy);
        require(femaleHeavy.at("passed")==true,"Female Gunner heavy-weapon runtime checks failed");
        writeJson("reports/knowledge-base/map-rendering-tests.json",runMapRenderingTests(p,a));
        }
        if (selectedGroup < 0 || selectedGroup == 6) {
        require(p.count() > 100000, "PVF index count");
        checkpoint = "all-character source contracts";
        const auto characterCatalog = runCharacterCatalogTests(p, a);
        writeJson("reports/combat-native-reverse/character-catalog-tests.json", characterCatalog);
        writeJson("reports/combat-native-reverse/character-identity-tests.json", runCharacterIdentityTests(p));
        checkpoint = "controller registry and SkillKey contracts";
        const auto controllerContracts = runCharacterControllerTests(p);
        writeJson("reports/combat-native-reverse/character-controller-tests.json", controllerContracts);
        checkpoint = "shared SKL data loading and zero passive consumers";
        writeJson("reports/combat-native-reverse/skill-data/runtime-tests.json", runSkillDataTests(p, a));
        checkpoint = "dungeon selection source model and input state";
        const auto textInputTests=runTextInputTests();
        writeJson("reports/selection-ime/text-input-tests.json",textInputTests);
        require(textInputTests.at("status")=="passed","UTF8/IME routing checks failed");
        const auto selectionUiTests=runSelectionUiTests(p,a);
        writeJson("reports/selection-ime/selection-ui-tests.json",selectionUiTests);
        require(selectionUiTests.at("status")=="passed","Source selection UI checks failed");
        const auto selectionFeedback=runSelectionFeedbackSourceTests(p,a);
        writeJson("reports/seven-job-world/selection-feedback-source-tests.json",selectionFeedback);
        require(selectionFeedback.at("status")=="passed","Selection feedback source checks failed");
        const auto portalVisualTests=runPortalVisualTests(p,a);
        writeJson("reports/selection-ime/portal-visual-tests.json",portalVisualTests);
        writeJson("reports/seven-job-world/portal-state-tests.json",runPortalStateTests(p,a));
        writeJson("reports/seven-job-world/source-skill-actions-tests.json",runSourceSkillActionTests(p,a));
        writeJson("reports/seven-job-world/watercannon-runtime-tests.json",runWaterCannonRuntimeTests(p,a));
        writeJson("reports/seven-job-world/watercannon-normal-tests.json",runWaterCannonNormalTests(p,a));
        writeJson("reports/seven-job-world/priest-upper-runtime-tests.json",runPriestUpperRuntimeTests(p,a));
        writeJson("reports/seven-job-world/hedgehog-runtime-tests.json",runHedgehogRuntimeTests(p,a));
        writeJson("reports/seven-job-world/lowkick-runtime-tests.json",runLowKickRuntimeTests(p,a));
        writeJson("reports/seven-job-world/mage-thrust-runtime-tests.json",runMageThrustRuntimeTests(p,a));
        writeJson("reports/seven-job-world/mage-upper-runtime-tests.json",runMageUpperRuntimeTests(p,a));
        writeJson("reports/seven-job-world/pickup-action-tests.json",runPickupActionTests(p,a));
        writeJson("reports/seven-job-world/scene-presentation-tests.json",runScenePresentationTests(p,a));
        writeJson("reports/seven-job-world/world-presentation-source-tests.json",runWorldPresentationSourceTests(p,a));
        writeJson("reports/seven-job-world/character-advancement-tests.json",runCharacterAdvancementTests(p,a));
        writeJson("reports/selection-ime/monster-equipment-tests.json",runMonsterEquipmentTests(p,a));
        require(portalVisualTests.at("status")=="passed","DGN portal source/variant checks failed");
        const auto dungeonSelection = runDungeonSelectionTests(p, a);
        writeJson("reports/combat-native-reverse/dungeon-selection/tests.json", dungeonSelection);
        checkpoint = "equipment LAY source bindings";
        writeJson("reports/combat-native-reverse/equipment-motion/tests.json", runEquipmentMotionTests(p, a));
        checkpoint = "passive object source/runtime contracts";
        const auto objectSystem = runObjectSystemTests(p, a);
        writeJson("reports/combat-native-reverse/objects/tests.json", objectSystem);
        checkpoint = "native default ordinary attack";
        writeJson("reports/combat-native-reverse/native-attack-tests.json", runNativeAttackTests(p, a));
        checkpoint = "user feedback settings/animation regression";
        writeJson("reports/combat-native-reverse/user-feedback-tests.json", runUserFeedbackTests(p, a));
        checkpoint = "native ANI event flags";
        writeJson("reports/combat-native-reverse/animation-events/tests.json", runAnimationEventTests(a));
        checkpoint = "native axis integration subset";
        writeJson("reports/combat-native-reverse/axis-motion-tests.json", runAxisMotionTests(p, a));
        checkpoint = "native particle straight/keep-last arithmetic";
        writeJson("reports/combat-native-reverse/particle-motion-tests.json", runParticleMotionTests(p));
        checkpoint = "native static movement operands and stop duration";
        writeJson("reports/combat-native-reverse/static-motion-tests.json", runStaticMotionTests());
        checkpoint = "native zero-level skill start gate";
        const auto eligibility = runSkillEligibilityTests(p, a);
        writeJson("reports/combat-native-reverse/skill-eligibility-tests.json", eligibility);
        require(eligibility.at("status") == "pass", "Zero-level skill start regression");
        auto s = p.script("skill/swordman/guard.skl");
        require(s.text("[name]") == "格挡", "GBK translation");
        require(normalize("技能/效果/../动画.ANI") == "技能/动画.ani", "UTF-8 logical paths use explicit UTF-8 conversion");
        auto ani = a.animation("character/swordman/animation/stay.ani");
        require(!ani->frames.empty(), "ANI frames");
        auto px = a.pixels("character/swordman/equipment/avatar/skin/sm_body0000.img", 176);
        require(px.width > 0 && px.rgba.size() == size_t(px.width) * px.height * 4, "IMG RGBA");
        {
            // Real Seria ANI (-51,-162), signed scale (-1,1), cropped IMG
            // (23,54,56,111): both facing directions must stay at the NPC anchor.
            auto q = imageQuad(477, 360, -51, -162, 23, 54, 56, 111, -1, -1, 1);
            require(q[0].x == 449 && q[2].x == 505 && q[0].y == 252 && q[2].y == 363,
                    "Seria negative ANI scale preserves anchor");
            auto flipped = imageQuad(477, 360, -51, -162, 23, 54, 56, 111, 1, -1, 1);
            require(flipped[0].x == 505 && flipped[2].x == 449,
                    "Facing and negative ANI scaling compose");
            auto rotated = imageQuad(100, 100, -10, -20, 2, 3, 4, 6, 1, 2, 1, 90);
            require(std::abs(rotated[0].x - 117) < 1e-8 && std::abs(rotated[0].y - 84) < 1e-8,
                    "Rotation uses entity anchor including ANI and crop offsets");
        }
        }
        if (selectedGroup < 0 || selectedGroup == 7) {
        checkpoint = "source scenes";
        {
            Scene scene;
            scene.load(p, a, "map/elvengard/(r)gate.map");
            require(scene.width == 896 && scene.tiles.empty() && scene.tileGrids.size() == 4,
                    "Blank source TIL room retains four transparent columns without fabricated artwork");
            require(scene.issues.size() == 5 && std::count_if(scene.issues.begin(),scene.issues.end(),
                    [](const Json &issue){return issue.value("kind","")=="transparent_tile_dimensions_inferred";}) == 4,
                    "Each blank TIL keeps its dimension inference diagnostic");
            const auto tileReceipt=std::find_if(scene.issues.begin(),scene.issues.end(),
                    [](const Json &issue){return issue.value("kind","")=="source_tile_load_receipt";});
            require(tileReceipt!=scene.issues.end() && tileReceipt->at("complete")==true &&
                    tileReceipt->at("columns_resolved")==true && tileReceipt->at("records").size()==4,
                    "Source TIL load receipt proves all four authored columns resolved");
            for(const auto &grid:scene.tileGrids)
                require(grid.at("transparent")==true && grid.at("tile")=="map/elvengard/tile/dummy.til" &&
                        grid.at("image")=="" && grid.at("image_logical_size")==Json::array({224,480}),
                        "Blank Seria TIL keeps exact source identity and calibrated geometry");
            require(!scene.walkRects.empty(), "Room virtual walk area");
            require(scene.npcs.size() == 5 && scene.npcs[0].id == 2 &&
                    scene.npcs[0].animation == "npc/animation/npc_se.ani", "Room NPC list resolution");
            scene.load(p, a, "map/elvengard/elvengard.map");
            require(scene.npcs.size() == 2, "Exact duplicate NPC placements only");
            auto bgLayer = std::find_if(scene.layers.begin(), scene.layers.end(),
                                       [](auto &l) { return l.background && l.sourceLayer == "[distantback]"; });
            require(bgLayer != scene.layers.end() && bgLayer->repeatWidth == 640 &&
                    bgLayer->sourceOrder == "[below]" && bgLayer->scroll == 0.5,
                    "Original background canvas and ordering metadata");
            scene.load(p, a, "map/lorien/b1.map");
            require(scene.npcs.size() == 1 && scene.npcs[0].id == 1000 &&
                    scene.npcs[0].visibleOnDungeonClear, "Delilah original clear visibility");
        }
        {
            // Hand-encoded, independent DXT1/3/5 red blocks; partial 3x2 image,
            // raw mode 5 followed by a BGRA frame tests the next payload offset.
            for (int type : {18, 19, 20}) {
                Bytes raw(16, 0);
                const char *signature = "Neople Img File";
                std::memcpy(raw.data(), signature, std::strlen(signature));
                auto put = [&](auto v) { auto *ptr = reinterpret_cast<const uint8_t *>(&v); raw.insert(raw.end(), ptr, ptr + sizeof(v)); };
                put(uint64_t(72)); put(int32_t(2)); put(int32_t(2));
                for (int i = 0; i < 2; i++) {
                    put(int32_t(i == 0 ? type : 16)); put(int32_t(5));
                    put(int32_t(i == 0 ? 3 : 1)); put(int32_t(i == 0 ? 2 : 1));
                    put(int32_t(0)); put(int32_t(-7)); put(int32_t(-9)); put(int32_t(10)); put(int32_t(12));
                }
                if (type == 19) raw.insert(raw.end(), 8, 0xff);
                if (type == 20) { raw.push_back(255); raw.push_back(0); raw.insert(raw.end(), 6, 0); }
                for (uint8_t v : {0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}) raw.push_back(v);
                for (uint8_t v : {0x33, 0x22, 0x11, 0xff}) raw.push_back(v);
                auto img = decodeImg(raw, 0);
                require(img.width == 3 && img.height == 2 && img.x == -7 && img.y == -9, "DXT geometry");
                for (size_t i = 0; i < img.rgba.size(); i += 4)
                    require(img.rgba[i] == 255 && img.rgba[i + 1] == 0 && img.rgba[i + 2] == 0 && img.rgba[i + 3] == 255, "DXT golden red block");
                require(decodeImg(raw, 1).rgba == Bytes({0x11, 0x22, 0x33, 0xff}), "Raw DXT next payload alignment");
                raw.resize(raw.size() - 5);
                bool rejected = false;
                try { decodeImg(raw, 0); } catch (...) { rejected = true; }
                require(rejected, "Truncated DXT data rejected");
            }
        }
        {
            // Regression for the formerly stale obstacle list: breaking a
            // source barrel must free its footprint in this visit and after
            // restoring the room from a save. Repeat render updates cannot
            // count one attack serial as multiple hits.
            Scene scene; scene.load(p,a,"map/lorien/6.map");
            World world(p,a); world.mapWidth=scene.width; world.walkRects=scene.walkRects;
            auto it=std::find_if(scene.objects.begin(),scene.objects.end(),[&](const MapObject &o) {
                return o.source=="passiveobject/mapobject/breakableobject/barrel.obj" &&
                       world.canWalk(o.x,o.y-o.height/2.0);
            });
            require(it!=scene.objects.end(),"Source barrel inside walk grid");
            const double x=it->x,y=it->y-it->height/2.0;
            const auto identity=it->identity;
            auto *object=scene.objectSystem.find(identity);
            require(object&&object->durability==2,"Explicit local barrel candidate is isolated in ObjectSystem");
            scene.rebuildObstacles(world);
            require(!world.canWalk(x,y),"Intact barrel must block its footprint");
            AttackVolume attack;attack.serial=101;attack.x=it->x;attack.y=it->y;
            attack.z=it->z;attack.direction=1;attack.box={15,-30,-20,0,60,20,100};
            world.attackVolumes={attack};scene.updateObjects(world,p,a);
            require(object->durability==1&&object->state==ObjectState::Intact,"Source barrel first distinct hit");
            scene.updateObjects(world,p,a);
            require(object->durability==1&&object->state==ObjectState::Intact,"One attack cannot repeatedly damage barrel");
            world.attackVolumes[0].serial=102;scene.updateObjects(world,p,a);
            require((object->state==ObjectState::Destroying||object->state==ObjectState::Destroyed)&&world.canWalk(x,y),
                    "Accepted barrel destruction releases the movement footprint");
            const auto saved=scene.saveObjects(world.nowMs());
            Scene restored;restored.load(p,a,"map/lorien/6.map");restored.restoreObjects(saved,world.nowMs());
            restored.rebuildObstacles(world);
            const auto *restoredObject=restored.objectSystem.find(identity);
            require(restoredObject&&restoredObject->state!=ObjectState::Intact&&world.canWalk(x,y),
                    "Restored destroyed barrel cannot reintroduce collision");
            Scene fresh;fresh.load(p,a,"map/lorien/6.map");fresh.rebuildObstacles(world);
            require(!world.canWalk(x,y),"Fresh dungeon preserves source barrel collision");
        }
        {
            Scene scene; scene.load(p,a,"map/lorien/6.map");
            World world(p,a); world.tick=1;
            scene.updateObjects(world,p,a);
            const auto firstAge=scene.objectSystem.instances().front().ageUs;
            require(firstAge==16666,"Object system advances by the first exact fixed-tick interval");
            scene.updateObjects(world,p,a);
            require(scene.objectSystem.instances().front().ageUs==firstAge,
                    "Repeated object contact processing in one simulation tick does not advance time twice");
            world.tick=2;
            scene.updateObjects(world,p,a);
            require(scene.objectSystem.instances().front().ageUs==33333,
                    "Object simulation time follows fixed ticks with no accumulated millisecond truncation");
        }
        }
        if (selectedGroup < 0 || selectedGroup == 8) {
        checkpoint = "combat render rates";
        rows = Json::array();
        for (int fps : {30, 60, 120, 144, 240}) {
            World w(p, a);
            w.freezeAi = true;
            w.enqueue({0, 1, true});
            w.enqueue({80000000, 1, false});
            w.enqueue({120000000, 1, true});
            w.enqueue({900000000, 1, false});
            w.enqueue({1000000000, 20, true});
            w.enqueue({1010000000, 20, false});
            w.enqueue({2500000000, 26, true});
            w.enqueue({2510000000, 26, false});
            int64_t elapsed = 0;
            for (int i = 1; i <= fps * 5; i++) {
                int64_t next = int64_t(i) * 5000000000ll / (fps * 5);
                w.advance(next - elapsed);
                elapsed = next;
            }
            auto state = w.snapshot();
            auto ev = w.eventLog();
            Json value = {{"state", state}, {"events", ev}};
            if (baseline.is_null())
                baseline = value;
            else
                require(value == baseline, "Render-rate independence mismatch");
            rows.push_back({{"render_fps", fps}, {"ticks", w.tick}, {"same_result", true}});
        }
        checkpoint = "combat regression";
        World w(p, a);
        w.advance(5000000000ll);
        require(w.tick == 300, "Stall catch-up");
        Json skillResults = Json::array();
        for (int i = 0; i < 13; i++) {
            World trial(p, a);
            trial.combat = true;
            trial.freezeAi = true;
            trial.freeCd = true;
            trial.player.x = trial.player.px = 300;
            trial.player.y = trial.player.py = 300;
            Actor dummy;
            dummy.id = 1;
            dummy.monsterPath = "monster/goblin/goblin.mob";
            dummy.hp = dummy.maxHp = 100000;
            dummy.x = dummy.px = 380;
            dummy.y = dummy.py = 300;
            trial.monsters.push_back(dummy);
            if (i == 3)
                trial.player.animation = "dashattack";
            if (trial.skills[i].airOnly) {
                trial.player.z = trial.player.pz = 100;
                trial.player.vz = 350;
            }
            if (i == 12)
                trial.enqueue({0, 32, true});
            else
                trial.activate(i);
            int64_t elapsed = 0;
            for (int frame = 1; frame <= 180; frame++) {
                if (trial.skills[i].continuation && trial.activeSkill() == i)
                    trial.activate(i);
                if (i == 12 && frame == 20)
                    trial.enqueue({300000000, 32, false});
                auto &target = trial.monsters[0];
                target.x = target.px = trial.player.x + 80;
                target.y = target.py = trial.player.y;
                if (i == 5)
                    target.z = target.pz = trial.player.z;
                int64_t next = int64_t(frame) * 1000000000 / 60;
                trial.advance(next - elapsed);
                elapsed = next;
            }
            int hits = 0, stages = 0;
            for (auto &ev : trial.events) {
                if (ev.kind == "hit")
                    hits++;
                if (ev.kind == "stage")
                    stages++;
            }
            Json row = {{"skill", trial.skills[i].key},
                        {"stages", stages},
                        {"hits", hits},
                        {"ended", trial.activeSkill() < 0},
                        {"armor_cleared", !trial.armor()},
                        {"invincibility_cleared", !trial.invincible()}};
            skillResults.push_back(row);
            writeJson("reports/skill-tests.json", skillResults);
            require(trial.activeSkill() < 0, "Skill did not terminate within three simulation seconds");
            require(!trial.armor() && !trial.invincible(), "Leaked skill protection");
            if (i != 7 && i != 12)
                require(hits > 0, ("No hit from " + trial.skills[i].key).c_str());
            if (i == 2)
                require(stages == 3, "Triple Slash continuation stages");
            if (i == 11 || i == 5)
                require(stages == 2, "Two-stage continuation");
            if (i == 6)
                require(stages == 1 && trial.effects.empty(), "Wave stuck in sentinel ANI frame");
        }
        {
            World basic(p, a);
            basic.freezeAi = true;
            basic.player.x = basic.player.px = 300;
            basic.player.y = basic.player.py = 300;
            Actor dummy;
            dummy.id = 1;
            dummy.x = dummy.px = 380;
            dummy.y = dummy.py = 300;
            dummy.monsterPath = "monster/goblin/goblin.mob";
            dummy.hp = 1000;
            basic.monsters.push_back(dummy);
            basic.normalAttack();
            basic.advance(1000000000);
            require(basic.monsters[0].hp < 1000, "Basic attack weapon-layer hit box");
            require(basic.player.poseFrame < 0, "Normal attack pose leaked into idle");
        }
        {
            // Real keyboard input semantics: three separate X presses queue the
            // original attack1/2/3 motions. Keep one target on the original MAP
            // floor; do not move it back into the hit boxes between swings.
            Scene ground;
            ground.load(p, a, "map/lorien/s0.map");
            Json comboRows = Json::array();
            bool allSwingsHit = true, allSingleHits = true, allEnded = true, allMoved = true;
            const auto firstDuration = a.animation("character/swordman/animation/attack1.ani")->duration;
            const auto secondDuration = a.animation("character/swordman/animation/attack2.ani")->duration;
            const auto thirdDuration = a.animation("character/swordman/animation/attack3.ani")->duration;
            require(firstDuration > 100 && secondDuration > 100 && thirdDuration > 0,
                    "Source normal combo durations");
            for (int weapon = 0; weapon < 4; ++weapon) {
                for (int direction : {1, -1}) {
                    World combo(p, a);
                    combo.combat = true;
                    combo.freezeAi = true;
                    combo.weapon = weapon;
                    combo.mapWidth = ground.width;
                    combo.walkRects = ground.walkRects;
                    combo.player.x = combo.player.px = 560;
                    combo.player.y = combo.player.py = 344;
                    combo.player.dir = direction;
                    Actor target;
                    target.id = 1;
                    target.x = target.px = combo.player.x + direction * 80;
                    target.y = target.py = combo.player.y;
                    target.dir = -direction;
                    target.hp = target.maxHp = 100000;
                    target.monsterPath = "monster/goblin/goblin.mob";
                    require(combo.canWalk(combo.player.x, combo.player.y) &&
                            combo.canWalk(target.x, target.y), "Normal combo source-ground placement");
                    combo.monsters.push_back(target);
                    const int mp = combo.player.mp;
                    for (int64_t when : {int64_t(0), int64_t(100000000)}) {
                        combo.enqueue({when, 4, true});
                        combo.enqueue({when + 40000000, 4, false});
                    }
                    std::array<bool, 3> observed{};
                    const int totalMs = firstDuration + secondDuration + thirdDuration + 1000;
                    bool thirdQueued = false;
                    const int frames = (totalMs * 60 + 999) / 1000;
                    int64_t elapsed = 0;
                    for (int frame = 1; frame <= frames; ++frame) {
                        const int64_t next = int64_t(frame) * 1000000000ll / 60;
                        combo.advance(next - elapsed);
                        elapsed = next;
                        if (!thirdQueued && combo.player.animation == "attack2") {
                            // Contact pause extends wall time. Queue the third
                            // X from the actual second swing, not the old
                            // no-hit wall-clock estimate for its start.
                            combo.enqueue({elapsed + 100000000, 4, true});
                            combo.enqueue({elapsed + 140000000, 4, false});
                            thirdQueued = true;
                        }
                        for (int swing = 0; swing < 3; ++swing)
                            if (combo.player.animation == "attack" + std::to_string(swing + 1))
                                observed[swing] = true;
                    }
                    std::array<int, 3> hits{};
                    int damage = 0;
                    for (const auto &event : combo.events) {
                        if (event.kind != "hit" || event.target != target.id) continue;
                        damage += event.value;
                        for (int swing = 0; swing < 3; ++swing)
                            if (event.name == "attack" + std::to_string(swing + 1))
                                ++hits[swing];
                    }
                    const bool eachHit = hits[0] > 0 && hits[1] > 0 && hits[2] > 0;
                    const bool singleHits = hits[0] <= 1 && hits[1] <= 1 && hits[2] <= 1;
                    const bool ended = combo.player.animation == "stay" && combo.player.poseFrame < 0 &&
                                       combo.activeSkill() < 0 && combo.player.mp == mp &&
                                       observed[0] && observed[1] && observed[2];
                    // A finished combo must release movement. Walk in the
                    // attack direction, away from the room edges, for 300ms.
                    const double x = combo.player.x;
                    const int walkKey = direction > 0 ? 1 : 0;
                    combo.enqueue({elapsed, walkKey, true});
                    combo.enqueue({elapsed + 300000000, walkKey, false});
                    combo.advance(400000000);
                    const double movement = (combo.player.x - x) * direction;
                    const bool moved = movement > 40 && combo.player.animation == "stay" &&
                                       combo.canWalk(combo.player.x, combo.player.y);
                    comboRows.push_back({{"weapon", weapon}, {"direction", direction},
                                         {"hit_counts", hits}, {"damage", damage},
                                         {"remaining_hp", combo.monsters[0].hp},
                                         {"animations_observed", observed}, {"each_swing_hit", eachHit},
                                         {"single_hit_per_swing", singleHits}, {"ended", ended},
                                         {"movement_after_combo", movement}, {"movement_resumed", moved}});
                    allSwingsHit = allSwingsHit && eachHit;
                    allSingleHits = allSingleHits && singleHits;
                    allEnded = allEnded && ended;
                    allMoved = allMoved && moved;
                }
            }
            // Preserve all eight cases on failure, including the original
            // attack2 omission, so a failed run remains reviewable.
            writeJson("reports/basic-combo-tests.json",
                      {{"status", allSwingsHit && allSingleHits && allEnded && allMoved ? "pass" : "fail"},
                       {"scope", "original Lorien floor and PVF animations; X input queue; four weapons and both facings"},
                       {"cases", comboRows}});
            require(allSwingsHit, "Four weapons/both directions: every normal combo swing must hit (including attack2)");
            require(allSingleHits, "Overlapping body/weapon layers or frames dealt duplicate normal-swing damage");
            require(allEnded && allMoved, "Normal combo did not terminate or release movement");
        }
        {
            World cmd(p, a);
            cmd.enqueue({0, 3, true});
            cmd.enqueue({30000000, 3, false});
            cmd.enqueue({80000000, 1, true});
            cmd.enqueue({100000000, 6, true});
            cmd.advance(150000000);
            require(cmd.activeSkill() == 6, "PVF DOWN RIGHT SKILL command");
        }
        {
            World tri(p, a);
            tri.freezeAi = true;
            int mp = tri.player.mp;
            tri.activate(2);
            int cost = tri.skills[2].mp;
            for (int f = 0; f < 120; f++) {
                if (tri.activeSkill() == 2)
                    tri.activate(2);
                tri.advance(16666667);
            }
            require(tri.player.mp == mp - cost, "Continuation charged MP again");
            require(tri.remainingCd(2) > 0, "Continuation end cooldown");
        }
        {
            World vane(p, a);
            vane.combat = true; vane.freezeAi = true;
            vane.player.x = vane.player.px = 300; vane.player.y = vane.player.py = 300;
            for (int n = 1; n <= 2; n++) {
                Actor m; m.id = n; m.x = m.px = n == 1 ? 350 : 440; m.y = m.py = 300;
                m.hp = m.maxHp = 100000; m.monsterPath = "monster/goblin/goblin.mob";
                vane.monsters.push_back(m);
            }
            vane.activate(8);
            vane.advance(3000000000ll);
            int capture = 0, down = 0, primary = 0, neighbor = 0, pulseEvents = 0;
            int64_t lastPulse = -10000;
            for (auto &ev : vane.events) {
                if (ev.kind == "pulse") {
                    ++pulseEvents;
                    require(ev.tick - lastPulse >= 15, "Vane pulse spacing below 250ms"); lastPulse = ev.tick;
                }
                if (ev.kind != "hit") continue;
                if (ev.name == "vaneslash:capture") { ++capture; require(ev.target == 1, "Capture hit neighbor"); }
                if (ev.name == "vaneslash:downslash") { ++down; require(ev.target == 1, "Downslash hit non-captured enemy"); }
                if (ev.name == "vaneslash:pulse") { if (ev.target == 1) ++primary; else ++neighbor; }
            }
            writeJson("reports/combat-feel/vane-response-regression.json",
                      {{"capture",capture},{"downslash",down},{"primary",primary},{"neighbor",neighbor},
                       {"pulses",pulseEvents},{"events",vane.eventLog()},{"end",vane.snapshot()}});
            // The primary is held by the capture controller. A nearby free
            // enemy may leave the authored volume after the source PO's push;
            // the former exact-three-neighbor assertion depended on wrongly
            // using the downslash's [none] response for the rotating object.
            require(capture == 1 && down == 1 && primary == 3 && neighbor >= 1 && neighbor <= 3 && pulseEvents == 3,
                    "Vane capture/downslash/three area pulses with source push on free neighbors");
            require(!vane.invincible() && vane.monsters[0].capturedBy < 0, "Vane capture protection cleanup");
            World miss(p, a); miss.activate(8); miss.advance(3000000000ll);
            require(miss.effects.empty() && !miss.invincible() && miss.activeSkill() < 0, "Missed grab generated protected wave");
        }
        {
            World cross(p, a); cross.freezeAi = true;
            cross.player.x = cross.player.px = 300; cross.player.y = cross.player.py = 300;
            Actor m; m.id = 1; m.hp = m.maxHp = 100000; m.x = m.px = 380; m.y = m.py = 300;
            m.monsterPath = "monster/goblin/goblin.mob"; cross.monsters.push_back(m);
            cross.activate(9); cross.advance(2000000000ll);
            int slash = 0, blood = 0;
            for (const auto &e : cross.events) if (e.kind == "hit") {
                if (e.name == "gorecross:blood") blood = e.value; else slash = e.value;
            }
            // SKL Lv1: 149% + 35; training sword 18, mastery 1.4%, STR 7.5.
            require(blood == 64, "Blood cross failed to use independent phase percentage and fixed damage");
        }
        {
            // Every original Lorien spawn must already be on the source ground;
            // the previous 16-unit row assumption projected upper spawns away.
            for (const char *path : {"map/lorien/s0.map", "map/lorien/4.map", "map/lorien/b1.map"}) {
                Scene ground; ground.load(p, a, path);
                World trial(p, a); trial.mapWidth = ground.width; trial.walkRects = ground.walkRects;
                auto spawns = ground.script.values("[monster]");
                for (size_t i = 0; i + 9 < spawns.size(); i += 10)
                    require(trial.canWalk(spawns[i + 3].get<double>(), spawns[i + 4].get<double>() + ground.bg),
                            "Original forest monster spawn outside walk grid");
                require(trial.canWalk(560, 420) && !trial.canWalk(560, 440),
                        "Forest ground extends below the visible source floor");
                for (const auto &r : ground.walkRects)
                    require(r[1] + r[3] + 120 <= 558, "Forest ground feet extend below HUD");
            }
        }
        {
            World ground(p, a); ground.mapWidth = 1120;
            ground.walkRects = {{0, 272, 1120, 272}};
            Actor m; m.x = m.px = 300; m.y = m.py = 260;
            ground.recoverPosition(m);
            require(m.y == 272 && ground.canWalk(m.x, m.y), "Out-of-grid source spawn recovery");
        }
        {
            auto stone = [](World &trial) {
                Effect e; e.hostile = true; e.x = e.px = trial.player.x; e.y = e.py = trial.player.y;
                e.z = 50; e.dir = -1; e.expires = trial.nowMs() + 1000; trial.effects.push_back(e);
            };
            World armored(p, a); armored.activate(0); stone(armored);
            int hp = armored.player.hp;
            armored.advance(16666667);
            require(armored.player.hp < hp && armored.activeSkill() == 0 && armored.armor(), "Superarmor must take damage and preserve skill");
            World interrupted(p, a); interrupted.activate(1); stone(interrupted);
            interrupted.advance(16666667);
            require(interrupted.activeSkill() < 0 && interrupted.effects.empty(), "Hostile hit must safely remove attached effects on interruption");
            World protectedWorld(p, a); protectedWorld.skills[0].stages[0].invincible = true;
            protectedWorld.activate(0); stone(protectedWorld); hp = protectedWorld.player.hp;
            protectedWorld.advance(16666667);
            require(protectedWorld.player.hp == hp && protectedWorld.activeSkill() == 0, "Invincibility must reject damage");
            armored.player.hp = 1; stone(armored); armored.advance(16666667);
            require(armored.player.dead && armored.activeSkill() < 0 && !armored.armor() && !armored.invincible(), "Death must clear superarmor and protection");
        }
        {
            Scene bossRoom; bossRoom.load(p, a, "map/lorien/b1.map");
            World ai(p, a); ai.combat = true; ai.mapWidth = bossRoom.width; ai.walkRects = bossRoom.walkRects;
            ai.player.x = ai.player.px = 59; ai.player.y = ai.player.py = 313;
            Actor mob; mob.id = 1; mob.x = mob.px = 525; mob.y = mob.py = 296;
            mob.monsterPath = "monster/goblin/goblin.mob"; ai.monsters.push_back(mob);
            ai.advance(100000000ll);
            require(ai.monsters[0].x < 525 && ai.monsters[0].y > 296,
                    "Boss room AI cannot advance on original walk grid");
        }
        {
            World transition(p, a); transition.activate(0);
            int remaining = transition.remainingCd(0);
            require(remaining > 0, "Skill cooldown not started");
            transition.changeScene();
            require(transition.remainingCd(0) == remaining && transition.activeSkill() < 0 &&
                    !transition.armor() && !transition.invincible(), "Room transition reset cooldown or retained protection");
            transition.god = transition.freeCd = transition.freezeAi = true;
            transition.reset();
            require(transition.remainingCd(0) == 0 && !transition.god && !transition.freeCd && !transition.freezeAi,
                    "Character reset inherited test flags or cooldown");
        }
        {
            auto dir = std::filesystem::path("reports/test-saves") / std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
            CharacterStore original(dir);
            original.data["schema"] = 1;
            original.data["characters"][0] = {{"name", "Legacy1"}, {"class", "swordman"}, {"level", 1}, {"weapon", 2}, {"future_field", 17}};
            original.save();
            World one(p, a); original.apply(0, one);
            one.skills[2].level = 3; std::swap(one.bindings[0], one.bindings[2]); one.passives[1].level = 2;
            original.capture(0, one); original.save();
            original.close();
            CharacterStore reloaded(dir); World two(p, a); reloaded.apply(0, two);
            require(two.skills[2].level == 3 && two.bindings[0] == 2 && two.weapon == 2 && two.passives[1].level == 2, "Save migration/configuration roundtrip");
            require(reloaded.data["characters"][0]["future_field"] == 17, "Save lost unknown field");
            reloaded.close();
            writeJson(dir / "characters.json", {{"damaged", true}});
            CharacterStore fallback(dir); require(fallback.data["characters"][0]["name"] == "Legacy1", "Save backup recovery");
            fallback.save(); fallback.close(); CharacterStore recovered(dir);
            require(!recovered.data["characters"][0].is_null(), "Recovered save not durable");
        }
        Bytes bad = {0, 0, 1};
        bool caught = false;
        try {
            decodeAni(bad, "bad");
        } catch (...) {
            caught = true;
        }
        require(caught, "ANI truncation");
        }
        if (selectedGroup < 0 || selectedGroup == 9) {
        checkpoint = "animation dynamics";
        animationDynamics=dnf::runAnimationDynamicsTests(p,a);
        writeJson("reports/animation-dynamics-tests.json",animationDynamics);
        checkpoint = "animation clock consumers";
        writeJson("reports/animation-clock-tests.json",dnf::runAnimationClockTests(p,a));
        const auto effectCoordinates=dnf::runEffectCoordinatesTests(p,a);
        writeJson("reports/effect-coordinate-tests.json",effectCoordinates);
        require(effectCoordinates.value("status",std::string())=="pass"||effectCoordinates.value("status",std::string())=="passed","effect coordinate consumer regressions");
        const auto femaleTiming=dnf::runFemaleGunnerTimingTests(p,a);
        writeJson("reports/female-gunner-timing-tests.json",femaleTiming);
        require(femaleTiming.value("status",std::string())=="passed","female Gunner source/controller timing regressions");
        const auto femaleLayers=dnf::runFemaleGunnerSkillLayerTests(p,a);
        writeJson("reports/female-gunner-skill-layers-tests.json",femaleLayers);
        require(femaleLayers.value("status",std::string())=="passed","female Gunner skill layer regressions");
        writeJson("reports/skill-release-regression.json",dnf::runSkillReleaseRegressionTests(p,a));
        checkpoint = "region progression";
        regionProgression=dnf::runRegionProgressionTests(p,a);
        writeJson("reports/region-progression-tests.json",regionProgression);
        checkpoint = "pending reward transactions";
        writeJson("reports/pending-reward-tests.json",dnf::runPendingRewardTests(p,a));
        writeJson("reports/beta-branch-exit-tests.json",dnf::runBetaBranchExitTests(p,a));
        checkpoint = "appearance";
        appearance=dnf::runAppearanceTests(p,a);
        writeJson("reports/appearance-tests.json",appearance);
        checkpoint = "skill effects";
        skillEffects = runSkillEffectsTests(p, a);
        writeJson("reports/skill-chain-rework/tests.json", skillEffects);
        checkpoint = "monster effects";
        monsterEffects = runMonsterEffectsTests(p, a);
        writeJson("reports/monster-rework/tests.json", monsterEffects);
        checkpoint = "elvengard flow";
        elvengardFlow = runElvengardFlowTests(p, a);
        writeJson("reports/elvengard-rework/tests.json", elvengardFlow);
        checkpoint = "combat feedback";
        runCombatFeedbackTests(p, a);
        checkpoint = "frozen player-adapted monster level";
        writeJson("reports/seven-job-world/monster-level-policy-tests.json",runMonsterLevelPolicyTests(p,a));
        writeJson("reports/font-tests.json",{{"status","pass"},{"checks",fontChecks},
                  {"scope","source rasterization/metrics/immutability; no original PC pixel-parity claim"}});
        }
        if (selectedGroup >= 0) {
            const auto resultPath = std::filesystem::path("reports") /
                ("core-group-" + std::to_string(selectedGroup) + "-result.json");
            const char *groupNames[] = {"source-cache-and-content-index", "catalog-simulation-and-progression",
                "learning-damage-and-status", "combat-ai-and-map-access", "experimental-actions-and-nut",
                "ui-and-female-gunner", "character-and-skill-source", "scene-and-resource", "world-combat",
                "timing-and-effects", "gunner-source-and-basic-runtime", "fighter-ai-and-reaction-runtime"};
            const Json result = {{"status", "pass"}, {"group", selectedGroup},
                {"name", groupNames[selectedGroup]}, {"last_checkpoint", checkpoint},
                {"content_identity", contentIdentity},
                {"scope", "Isolated core regression shard; combine all twelve groups for a full core run"}};
            writeJson(resultPath, result);
            std::cout << "Core test group " << selectedGroup << " (" << groupNames[selectedGroup] << ") passed\n";
            return 0;
        }
        Json report = {{"status", "pass"},
                       {"checks", Json::array({"PVF index", "GBK translation", "ANI frames", "IMG RGBA",
                                               "30/60/120/144/240 render independence", "stall catch-up",
                                               "13 skill termination and protection cleanup", "weapon-layer basic attack boxes",
                                               "PVF direction command", "single MP/end cooldown continuation", "blank source TIL room regression",
                                               "DXT1/3/5 raw blocks and payload alignment", "grab target/downslash/three area pulses",
                                               "independent blood cross damage", "source spawn walk-grid recovery",
                                               "superarmor takes damage; invincibility rejects; death clears protection",
                                               "hostile hit safely removes attached effects", "room cooldown continuity and character test flag reset",
                                               "boss room AI advances on source walk grid",
                                               "schema1 migration/configuration/backup recovery", "truncation",
                                               "signed ANI scale/crop/facing and anchor rotation",
                                               "forest 12-unit vertical grid: all original spawns and visible floor bounds",
                                               "NPC ID resolution, exact placement deduplication and background metadata",
                                               "four weapons/both directions: each normal combo swing hits",
                                               "normal swing hit deduplication across weapon layers and frames",
                                               "normal combo completion and movement recovery",
                                               "source barrel hit deduplication/destruction/collision/save-revisit",
                                               "source hinted Chinese font, true metrics, bright centre and immutable bytes",
                                               "source equipment/avatar variants, numeric layer order and durable appearance save"})},
                       {"font_checks",fontChecks},
                       {"rates", rows}, {"animation_dynamics",animationDynamics}, {"region_progression",regionProgression},
                       {"appearance",appearance},
                       {"skill_effects", skillEffects}, {"monster_effects", monsterEffects},
                       {"elvengard_flow", elvengardFlow},
                       {"source", root.u8string()}, {"content_identity",testedContent.json()}};
        writeJson("reports/core-tests.json", report);
        std::cout << report.dump(2) << std::endl;
        return 0;
    } catch (const std::exception &e) {
        if(focused40jp) {
            try {writeJson("reports/40jp-focus/result.json",{{"status","failed"},{"last_checkpoint",checkpoint},
                {"error",e.what()},{"content_identity",contentIdentity}});}catch(...) {}
        }
        if (selectedGroup >= 0) {
            try {
                const auto resultPath = std::filesystem::path("reports") /
                    ("core-group-" + std::to_string(selectedGroup) + "-result.json");
                writeJson(resultPath, {{"status", "failed"}, {"group", selectedGroup},
                    {"last_checkpoint", checkpoint}, {"error", e.what()},
                    {"content_identity", contentIdentity}});
            } catch (...) {}
        }
        std::cerr << "FAIL [" << checkpoint << "] " << e.what() << std::endl;
        return 1;
    }
}

DNF_ENTRY(run)
