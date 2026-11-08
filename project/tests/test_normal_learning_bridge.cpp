#include "dnf/skill_learning_transaction.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/female_gunner_modifiers.hpp"
#include "dnf/scene.hpp"
#include "dnf/beta_character.hpp"
#include "dnf/character_attack.hpp"
#include <algorithm>
#include <chrono>
#include <climits>
#include <cmath>
#include <filesystem>
#include <stdexcept>

namespace dnf {
namespace {
Json bridgeRoot(CharacterIdentity identity,int level) {
    static const char *names[]={"swordman","fighter","gunner","mage","priest","atgunner","thief","atfighter","atmage"};
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    root["characters"][0]={{"name","NormalBridgeActualWorld"},{"class",names[identity.jobId]},
        {"identity",identity.json()},{"level",level},{"weapon",0},{"skill_initialization","source-v1"}};
    return root;
}
Json bridgeLive(const World &world,const Progression &progression) {
    const auto *r=world.experimentalRuntime();
    return {{"world",world.snapshot()},{"simulation",world.simulationCheckpoint()},
        {"skills",world.skillState().snapshot(world.nowMs())},{"overlay",world.skillTestOverlay().snapshot()},
        {"configuration",r?r->configuration().snapshot():Json()},{"normal_configuration",world.normalSkillConfigurationSnapshot()},
        {"preview_configuration",world.manualSkillPreviewSnapshot()},{"mode",world.experimentalSkillPreviewEnabled()},
        {"cooldowns",r?r->cooldownSnapshot(world.nowMs()):Json()},{"progression",progression.state}};
}
void bridgeRest(World &w) {
    w.releaseInputs();w.changeScene();w.monsters.clear();w.events.clear();w.idle();w.combat=false;
    w.player.recovery=0;w.player.stunUntil=0;w.player.hitStopTicks=0;w.player.hitStopped=false;
    w.player.dead=false;w.player.life=ActorLife::Alive;w.player.hp=w.player.maxHp;
    w.player.z=w.player.pz=w.player.vz=w.player.vx=w.player.vy=0;
}
template<class F> bool bridgeRejects(F &&f) {try{f();return false;}catch(const std::exception &){return true;}}
}
Json runNormalLearningRuntimeBridgeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool yes,const std::string &name){if(!yes)throw std::runtime_error(name);checks.push_back(name);};
    RegionCatalog regions(pvf,assets);
    const auto stamp=std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto root=std::filesystem::absolute(std::filesystem::path("cache/normal-learning-runtime-bridge")/std::to_string(stamp));
    for(const SkillKey key:std::array<SkillKey,2>{{{1,6},{3,4}}}) {
        for(const auto fault:{SaveFailurePoint::BeforePublish,SaveFailurePoint::AfterPublish}) {
            const auto directory=root/("job"+std::to_string(key.jobId)+"-fault"+std::to_string(int(fault)));
            CharacterStore store(directory,"normal-bridge-test");store.data=bridgeRoot({key.jobId,0,0},5);
            World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progress(regions);
            store.apply(0,world,progress);bridgeRest(world);
            check(world.runtimeSkillPolicy(key).implemented&&world.skillState().learnedLevel(key)==0,
                "Own reviewed source consumer exists without fabricated initial grant");
            auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
            runtime.configuration().configureSourceSkillAction(key,10,plan);runtime.configuration().assignSlot(0,key,plan);
            const int unlearnedMp=world.player.mp;world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
            check(world.player.mp==unlearnedMp&&!runtime.attacking()&&runtime.remainingCooldown(key,world.nowMs())==0,
                "Unlearned high raw binding cannot release, deduct MP, start CD or survive canonical projection");
            bridgeRest(world);store.capture(0,world,progress);store.checkpoint();
            const auto quote=world.quoteSkillLearning(key,5);
            check(quote.accepted()&&quote.targetLevel==1&&quote.cost==15&&quote.requiredCharacterLevel==5,
                "Actual source first purchase uses level5/SP15");
            const auto batch=world.quoteSkillLearningBatch(false,5);
            const auto batchQuote=std::find_if(batch.quotes.begin(),batch.quotes.end(),[&](const auto &q){return q.key==key;});
            check(batchQuote!=batch.quotes.end()&&batchQuote->json()==quote.json()&&batch.budget.json()==quote.budget.json(),
                "One normal batch budget preserves exact individual quote semantics for actual source key");
            const SkillLearningRequest request{"normal-bridge-buy",key,quote.revision,1};
            const auto before=bridgeLive(world,progress);const auto generation=store.generation();
            store.setFailureInjector([fault](SaveFailurePoint p){if(p==fault)throw std::runtime_error("normal bridge durable fault");});
            SkillLearningTransaction transaction;const auto pending=transaction.submit(store,0,world,progress,request,Json::object());
            check(!pending.ok&&transaction.pending()&&bridgeLive(world,progress)==before,
                "Before/after disk publication fault preserves exact live ledger, binding, CD and progression");
            store.setFailureInjector({});const auto committed=transaction.retry(store,world);
            check(committed.ok&&!transaction.pending()&&store.generation()==generation+1&&
                world.skillState().learnedLevel(key)==1&&runtime.configuration().binding(key)&&runtime.configuration().binding(key)->level==1,
                "Retry publishes one retained prepared binding and exactly one durable generation");
            const auto budget=world.skillLearningBudget(false,5).json();const auto committedGeneration=store.generation();
            check(transaction.submit(store,0,world,progress,request,Json::object()).state==SkillLearningTransactionState::Replayed&&
                store.generation()==committedGeneration&&world.skillLearningBudget(false,5).json()==budget,
                "Exact request replay never re-spends or recreates a save generation");
            check(world.assignLearnedSkillSlot(0,key).ok,"Normal SkillKey hotbar accepts learned reviewed action");
            const auto ledgerCd=world.skillState().remainingCooldown(key,world.nowMs());const int castMp=world.player.mp;
            world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
            check(runtime.attacking()&&world.player.mp<castMp&&runtime.remainingCooldown(key,world.nowMs())>0&&
                world.skillState().remainingCooldown(key,world.nowMs())==ledgerCd,
                "Actual input consumes exactly experimental MP/CD authority and leaves generic ledger CD unchanged");
            const auto cd=runtime.cooldownSnapshot(world.nowMs());bridgeRest(world);store.capture(0,world,progress);store.checkpoint();
            World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression restoredProgress(regions);
            store.apply(0,restored,restoredProgress);bridgeRest(restored);
            check(restored.skillState().learnedLevel(key)==1&&restored.experimentalRuntime()->configuration().binding(key)->level==1&&
                restored.experimentalRuntime()->cooldownSnapshot(restored.nowMs())==cd&&restored.skillLearningBudget(false,5).json()==budget,
                "Real save/reload preserves normal learned binding, budget, hotbar and experimental cooldown in one epoch");
            const auto normal=restored.skillState().snapshot(restored.nowMs());const auto normalConfig=restored.normalSkillConfigurationSnapshot();
            DebugOverrides debug;debug.enabled=true;debug.level=99;restored.applyDebugOverrides(debug,5);
            const auto testQuote=restored.quoteTestSkillLearning(key);
            check(testQuote.accepted()&&restored.learnTestSkill({"isolated-level2",key,testQuote.revision,testQuote.targetLevel}).ok,
                "Independent test purchase projects its actual binding level");
            check(restored.experimentalRuntime()->configuration().binding(key)->level==2&&restored.skillState().snapshot(restored.nowMs())==normal,
                "Test projection cannot mutate normal grants, purchases, SP or cooldown ledger");
            check(restored.assignLearnedSkillSlot(1,key).ok&&restored.setExperimentalSkillPreviewEnabled(true).ok,
                "Explicit preview opens separately from test learning and normal hotbar");
            check(restored.testSkillConfigurationSnapshot().at("slots")[0].is_null(),
                "Moving a learned SkillKey to another test slot clears the previous slot");
            auto &preview=restored.experimentalRuntime()->configuration();preview.configureSourceSkillAction(key,10,restored.experimentalRuntime()->plan());
            preview.assignSlot(2,key,restored.experimentalRuntime()->plan());
            check(restored.setExperimentalSkillPreviewEnabled(false).ok&&restored.experimentalRuntime()->configuration().binding(key)->level==2,
                "Leaving explicit manual preview returns test-effective learned level, not hand-selected level10");
            restored.applyDebugOverrides({},5);
            check(restored.normalSkillConfigurationSnapshot()==normalConfig&&restored.experimentalRuntime()->configuration().binding(key)->level==1&&
                restored.skillState().snapshot(restored.nowMs())==normal,
                "Leaving test returns normal source binding and normal slots exactly");
            auto badSaved=store.data.at("characters")[0];badSaved["experimental_skill_configuration"]["pvf_identity"]="wrong-current-source";
            const auto restoreBefore=bridgeLive(restored,restoredProgress);const auto saved=store.data["characters"][0];
            store.data["characters"][0]=badSaved;
            check(bridgeRejects([&]{store.apply(0,restored,restoredProgress);})&&bridgeLive(restored,restoredProgress)==restoreBefore,
                "Saved binding source mismatch rejects before selectCharacter changes live state");store.data["characters"][0]=saved;
            auto invalidPlan=std::make_shared<ExperimentalCharacterPlan>(restored.experimentalRuntime()->plan());
            invalidPlan->sourceSkillActions.at(key).animation.memberPath="missing/normal-bridge-source-fault.ani";
            ExperimentalCharacterRuntime invalidRuntime(invalidPlan);SkillRuntimeProjectionContext context;
            context.runtime=&invalidRuntime;context.normalPreferences=&restored.experimentalRuntime()->configuration();context.normalLevel=context.effectiveLevel=5;
            check(bridgeRejects([&]{restored.prepareSkillRuntime(restored.skillState(),restored.skillTestOverlay(),context);})&&
                bridgeLive(restored,restoredProgress)==restoreBefore,
                "Selected visual resource failure stays private before any runtime publication");
            // This deliberately exercises the low-level isolated fixture mode;
            // production preview editing additionally requires testBranch+debug.
            check(restored.setExperimentalSkillPreviewEnabled(true).ok&&!restored.debugOverrides().enabled,
                "An explicit isolated preview is distinct from numeric debug overrides");
            restored.experimentalRuntime()->configuration().configureSourceSkillAction(key,10,restored.experimentalRuntime()->plan());
            store.capture(0,restored,restoredProgress);store.checkpoint();
            World previewLoaded(pvf,assets,WorldRules::BetaFoundationV1);previewLoaded.enableExperimentalCharacters();Progression pp(regions);
            store.apply(0,previewLoaded,pp);bridgeRest(previewLoaded);
            check(previewLoaded.experimentalSkillPreviewEnabled()&&!previewLoaded.debugOverrides().enabled&&
                previewLoaded.experimentalRuntime()->configuration().binding(key)->level==10&&previewLoaded.skillState().learnedLevel(key)==1,
                "Explicit isolated manual-preview save roundtrip restores mode without promoting raw level10 into normal ledger");
            SkillLearningTransaction previewTransaction;
            check(!previewTransaction.submit(store,0,previewLoaded,pp,{"must-not-buy-in-preview",key,0,2},Json::object()).ok,
                "Normally durable learning is rejected during explicit manual-preview execution");
            previewLoaded.applyDebugOverrides({},5);
            check(!previewLoaded.experimentalSkillPreviewEnabled()&&previewLoaded.experimentalRuntime()->configuration().binding(key)->level==1,
                "Disabling debug explicitly returns a restored isolated preview to canonical learned mode");
            auto legacy=store.data["characters"][0];legacy["experimental_skill_configuration"]=legacy.at("experimental_manual_preview_configuration");
            legacy.erase("experimental_skill_execution_mode");legacy.erase("experimental_manual_preview_configuration");store.data["characters"][0]=legacy;
            World legacyLoaded(pvf,assets,WorldRules::BetaFoundationV1);legacyLoaded.enableExperimentalCharacters();Progression lp(regions);store.apply(0,legacyLoaded,lp);
            const auto dormantPreview=legacyLoaded.manualSkillPreviewSnapshot();
            const auto &dormantBindings=dormantPreview.at("skill_bindings");const Json *dormantBinding=nullptr;size_t dormantMatches=0;
            for(const auto &binding:dormantBindings)if(SkillKey::fromJson(binding.at("key"))==key) {dormantBinding=&binding;++dormantMatches;}
            check(!legacyLoaded.experimentalSkillPreviewEnabled()&&legacyLoaded.experimentalRuntime()->configuration().binding(key)->level==1&&
                dormantMatches==1&&dormantBinding&&dormantBinding->at("level")==10,
                "Legacy raw configuration without explicit mode loads learned level1 while retaining dormant preview level10");
            store.close();
        }
    }
    // Actual CHR initial grant is free; subsequent purchase charges once.
    {
        CharacterStore store(root/"male-mage","normal-bridge-test");store.data=bridgeRoot({8,0,0},4);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progress(regions);store.apply(0,world,progress);bridgeRest(world);
        const SkillKey key{8,1};const auto initialBudget=world.skillLearningBudget(false,4);
        check(world.skillState().learnedLevel(key)==1&&initialBudget.spentSp==0&&world.experimentalRuntime()->configuration().binding(key)->level==1,
            "Male Mage CHR WindStrike initial level1 is projected without a second fee");
        const auto quote=world.quoteSkillLearning(key,4);SkillLearningTransaction transaction;
        check(quote.accepted()&&quote.targetLevel==2&&transaction.submit(store,0,world,progress,{"wind2",key,quote.revision,2},Json::object()).ok&&
            world.skillLearningBudget(false,4).spentSp==quote.cost,"Only WindStrike level2 purchase increases normal SP spend");
        check(world.assignLearnedSkillSlot(0,key).ok,"Male Mage learned initial/action consumer binds normally");
        const int mp=world.player.mp;world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        check(world.experimentalRuntime()->attacking()&&world.player.mp<mp,"Male Mage normal learned action reaches NUT/MP consumer");store.close();
    }
    // Real GSD transaction first, then real branch4 skill purchase/reload.
    {
        CharacterStore store(root/"priest-gsd","normal-bridge-test");store.data=bridgeRoot({4,0,0},30);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progress(regions);store.apply(0,world,progress);bridgeRest(world);
        check(!world.quoteSkillLearning({4,116},30).accepted(),"Unadvanced Priest cannot normally learn branch4 Hedgehog");
        store.capture(0,world,progress);store.checkpoint();Scene scene;MapNpc npc;npc.id=world.advancementCatalog().trainerId();
        npc.source=world.advancementCatalog().trainerPath();npc.visible=true;npc.x=world.player.x;npc.y=world.player.y;scene.npcs.push_back(npc);
        CharacterAdvancementTransaction advancement;const auto budget=world.skillLearningBudget(false,30).json();
        const CharacterAdvancementRequest request{"priest-avenger",world.identity(),{4,4,0},store.generation(),npc.id};
        check(advancement.submit(store,0,world,progress,scene,request,Json::object()).ok&&world.skillLearningBudget(false,30).json()==budget,
            "Actual GSD branch4 commit preserves SP and does not grant Hedgehog automatically");
        const auto quote=world.quoteSkillLearning({4,116},30);SkillLearningTransaction learning;
        check(quote.accepted()&&learning.submit(store,0,world,progress,{"hedgehog1",{4,116},quote.revision,1},Json::object()).ok&&
            world.assignLearnedSkillSlot(0,SkillKey{4,116}).ok,"Actual Avenger can purchase and bind reviewed Hedgehog at source level30");
        const int mp=world.player.mp;world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        check(world.experimentalRuntime()->attacking()&&world.player.mp<mp,"Normally learned Priest action reaches source release/MP");
        bridgeRest(world);store.capture(0,world,progress);store.checkpoint();World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression rp(regions);
        store.apply(0,restored,rp);check(restored.identity()==CharacterIdentity{4,4,0}&&restored.experimentalRuntime()->configuration().binding({4,116})->level==1,
            "Branch4 identity and actual normal learned binding survive disk reload together");store.close();
    }
    {
        // Use a real source-supported normal level; numeric debug remains a
        // separate override and must not create level99 progression history.
        CharacterStore store(root/"male-gunner-preview-isolation","normal-bridge-test");store.data=bridgeRoot({2,0,0},15);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progress(regions);store.apply(0,world,progress);bridgeRest(world);
        check(world.skillState().learnedLevel({2,4})==1&&world.runtimeSkillPolicy({2,4}).implemented&&world.quoteSkillLearning({2,4},15).accepted()&&
            !world.runtimeSkillPolicy({2,168}).implemented&&!world.quoteSkillLearning({2,168},15).accepted(),
            "Male Gunner base Knee is separately admitted from the still-disabled TP family");
        check(world.skillLearningBudget(false,15).earnedSp>0,"Normal source budget is available independently of preview");
        DebugOverrides debug;debug.enabled=true;debug.level=99;world.applyDebugOverrides(debug,15);
        const auto normal=world.skillState().snapshot(world.nowMs());
        const auto opened=unlockExecutableBetaSkills(world);
        check(world.experimentalSkillPreviewEnabled()&&!opened.at("opened").empty()&&world.experimentalRuntime()->configuration().binding({2,4}),
            "Actual F9 unlock function explicitly enters isolated preview before publishing raw templates");
        const auto preview=world.experimentalRuntime()->configuration().snapshot();
        world.advanceSingleTick();
        check(world.experimentalRuntime()->configuration().snapshot()==preview&&world.skillState().snapshot(world.nowMs())==normal,
            "F9 preview templates survive the next canonical-projection tick without granting normal learned skills");
        world.experimentalRuntime()->configuration().assignSlot(0,SkillKey{2,4},world.experimentalRuntime()->plan());
        const int previewMp=world.player.mp;world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        check(world.experimentalRuntime()->attacking()&&world.player.mp<previewMp,
            "F9 explicit male Gunner comparison reaches actual input/MP without replacing the independent normal source ledger");
        store.close();
    }
    // Full base Knee admission uses the real source initial grant and normal
    // durable learning/input projection. No F9 or debug grants these levels.
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines})
    for(const auto fault:{SaveFailurePoint::BeforePublish,SaveFailurePoint::AfterPublish}) {
        const SkillKey knee{2,4},tp{2,168};
        CharacterStore store(root/("normal-knee-"+std::string(ani_clock::policyName(clock))+"-"+std::to_string(int(fault))),"normal-bridge-test");
        store.data=bridgeRoot({2,0,0},4);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        Progression progress(regions);store.apply(0,world,progress);bridgeRest(world);world.configureAnimationClock(clock);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();const auto &descriptor=plan.sourceSkillActions.at(knee);
        check(!world.experimentalSkillPreviewEnabled()&&!world.debugOverrides().enabled&&world.skillState().learnedLevel(knee)==1&&
            runtime.configuration().binding(knee)&&runtime.configuration().binding(knee)->level==1&&
            runtime.configuration().sourceActionAudioPolicy()=="inferred-current1031-knee-cast-audio-v1",
            "New source-v1 Gunner automatically projects free Knee1 and reviewed normal audio, without a manual binding");
        check(!world.runtimeSkillPolicy(tp).implemented&&!world.quoteSkillLearning(tp,4).accepted()&&
            !world.skillLearning().sourceUseEligibility({2,5,0},knee,1,15).allowed(),
            "Base admission neither opens TP168 nor invents growtype5 fitness from a sixth maximum value");
        check(world.assignLearnedSkillSlot(0,knee).ok,"Normal free Knee1 can be assigned through actual learned-slot operation");
        store.capture(0,world,progress);store.checkpoint();const auto initialization=world.skillState().snapshot(world.nowMs());
        World initialized(pvf,assets,WorldRules::BetaFoundationV1);initialized.enableExperimentalCharacters();Progression ip(regions);
        store.apply(0,initialized,ip);store.apply(0,initialized,ip);
        check(initialized.skillState().snapshot(initialized.nowMs())==initialization&&initialized.skillState().learnedLevel(knee)==1,
            "Repeated real source-v1 reload never repeats initial grants or SP purchases");
        const auto quote=world.quoteSkillLearning(knee,4);
        check(quote.accepted()&&quote.targetLevel==2&&quote.requiredCharacterLevel==4&&quote.currency=="SP"&&quote.cost==20&&quote.purchaseMaximum==10,
            "Actual normal Knee1 to2 quotes source character4, SP20 and maximum10");
        const SkillLearningRequest buy{"normal-knee-level2",knee,quote.revision,2};
        const auto before=bridgeLive(world,progress);const auto generation=store.generation();
        store.setFailureInjector([fault](SaveFailurePoint point){if(point==fault)throw std::runtime_error("Knee normal durable fault");});
        SkillLearningTransaction learning;const auto failed=learning.submit(store,0,world,progress,buy,Json::object());
        check(!failed.ok&&learning.pending()&&bridgeLive(world,progress)==before,
            "Knee disk fault before/after durable publication preserves live ledger/audio policy/slot/MP/CD/RNG");
        store.setFailureInjector({});check(learning.retry(store,world).ok&&store.generation()==generation+1&&
            world.skillState().learnedLevel(knee)==2&&runtime.configuration().binding(knee)->level==2,
            "Knee retry publishes exactly retained level2 canonical source binding once");
        const auto budget=world.skillLearningBudget(false,4).json();const auto committed=store.generation();
        check(learning.submit(store,0,world,progress,buy,Json::object()).state==SkillLearningTransactionState::Replayed&&
            store.generation()==committed&&world.skillLearningBudget(false,4).json()==budget,
            "Normal Knee request replay cannot spend SP20 twice");
        const auto next=world.quoteSkillLearning(knee,4);
        check(next.gate==SkillLearningGate::CharacterLevel&&next.targetLevel==3&&next.requiredCharacterLevel==7,
            "Normal Knee3 retains source character7 growth gate after actual level2 purchase");
        const auto normal=world.skillState().snapshot(world.nowMs());const auto canonical=world.normalSkillConfigurationSnapshot();
        runtime.configuration().configureSourceSkillAction(knee,10,plan);runtime.configuration().configureSourceActionPassive(tp,1,plan);
        runtime.configuration().setSourceActionAudioPolicy("disabled",plan);world.advanceSingleTick();
        check(runtime.configuration().binding(knee)->level==2&&runtime.configuration().sourceActionPassiveLevel(tp)==0&&
            runtime.configuration().sourceActionAudioPolicy()=="inferred-current1031-knee-cast-audio-v1"&&world.skillState().snapshot(world.nowMs())==normal,
            "Normal tick rejects raw level/TP/audio overrides and restores ledger-derived source policy");
        world.combat=true;world.freezeAi=true;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};world.blockedRects.clear();
        world.player.x=world.player.px=600;world.player.y=world.player.py=300;world.player.dir=1;world.player.mp=world.player.maxMp;
        world.randomStreams()=RandomStreams(0x1031);world.events.clear();
        const auto composed=readCharacterAttackMotion(assets,world.characterAppearance(),descriptor.motion.memberPath);
        std::optional<Box> box;for(size_t frame=0;frame<composed.body->frames.size()&&!box;++frame)
            for(const auto &candidate:composed.boxesAt(frame))if(candidate.w>0&&candidate.h>0&&candidate.d>0){box=candidate;break;}
        check(bool(box),"Normal Knee uses actual body/equipped source attack geometry");
        Actor target;target.id=1;target.monsterPath="monster/goblin/goblin.mob";target.sourceId=10;target.dir=-1;
        target.x=target.px=world.player.x+box->x+box->w*.5;target.y=target.py=world.player.y+box->y+box->h*.5;
        world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");target.hp=target.maxHp=100000000;
        world.monsters.push_back(target);world.synchronizeEntityHandles();
        const auto audioCount=[&](const World &w){return std::count_if(w.events.begin(),w.events.end(),[](const Event &e){return e.kind=="sound"&&
            (e.name=="GN_JACKSPIKE_01"||e.name=="GN_JACKSPIKE_02"||e.name=="JACKSPIKE_SWING");});};
        const int mp=world.player.mp;world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        world.enqueue({world.simulationNanoseconds(),20,false});
        const auto cost=runtime.snapshotDiagnostics().at("last_cost");
        check(runtime.attacking()&&mp-world.player.mp==cost.at("mp").at("value").get<int>()&&
            runtime.remainingCooldown(knee,world.nowMs())==int64_t(std::ceil(cost.at("cooldown_ms").at("value").get<double>()))&&audioCount(world)==2,
            "Normal slot Knee2 publishes source MP/CD and one own voice plus swing exactly once");
        bool volume=false,lift=false;for(int tick=0;tick<100;++tick) {
            for(const auto &v:world.attackVolumes)if(v.skillId==4&&v.sourceModifiers){volume=true;
                check(v.sourceModifiers->percent==float(*skillLevelValue(plan.skills.at(knee).data->values("[level info]"),2,0))&&
                    v.sourceModifiers->independentPercent==float(*skillLevelValue(plan.skills.at(knee).data->values("[level info]"),2,3)),
                    "Normal learned level2, without manual TP, reaches real attack damage coefficients");}
            lift|=world.monsters.front().vz>0;world.advanceSingleTick();
        }
        check(volume&&lift&&world.monsters.front().hp<target.hp&&audioCount(world)==2&&!runtime.attacking()&&
            world.player.skillAnimationLayers.empty()&&!world.armor()&&world.skillState().snapshot(world.nowMs())==normal,
            "Normal source Knee damages/lifts real monster and retires body/layers/armor without repeats or ledger mutation");
        const auto rejectCast=[&](bool noMp){
            bridgeRest(world);world.combat=true;world.freezeAi=true;world.events.clear();
            world.player.mp=noMp?0:world.player.maxMp;const auto beforeRandom=world.randomStreams().snapshot();
            const auto beforeCooldown=runtime.cooldownSnapshot(world.nowMs());const auto beforeMp=world.player.mp;
            world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();world.enqueue({world.simulationNanoseconds(),20,false});
            check(!runtime.attacking()&&world.player.mp==beforeMp&&audioCount(world)==0&&world.randomStreams().snapshot()==beforeRandom,
                noMp?"Normal MP rejection emits no cast audio and consumes no RNG or cost":"Normal cooldown rejection emits no cast audio and consumes no RNG or cost");
            (void)beforeCooldown;
        };
        rejectCast(false);
        while(runtime.remainingCooldown(knee,world.nowMs())>0)world.advanceSingleTick();rejectCast(true);
        bridgeRest(world);world.player.mp=world.player.maxMp;world.events.clear();
        world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();world.enqueue({world.simulationNanoseconds(),20,false});
        for(int n=0;n<100;++n)world.advanceSingleTick();
        const auto cooldown=runtime.cooldownSnapshot(world.nowMs());const auto rng=world.randomStreams().snapshot();
        bridgeRest(world);store.capture(0,world,progress);store.checkpoint();
        World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression rp(regions);store.apply(0,restored,rp);
        auto &loaded=*restored.experimentalRuntime();
        check(!restored.experimentalSkillPreviewEnabled()&&!restored.debugOverrides().enabled&&
            restored.skillState().snapshot(restored.nowMs())==normal&&loaded.configuration().binding(knee)->level==2&&
            loaded.configuration().slots()[0]==std::optional<SkillKey>(knee)&&loaded.cooldownSnapshot(restored.nowMs())==cooldown&&
            loaded.configuration().sourceActionAudioPolicy()=="inferred-current1031-knee-cast-audio-v1"&&
            restored.randomStreams().snapshot()==rng&&restored.skillLearningBudget(false,4).json()==budget,
            "Same-generation real reload preserves paid normal level/slot/cooldown/audio RNG and point budget");
        RandomStreams resumed;resumed.restore(rng);const auto nextVoice=resumed.stream(RandomDomain::Audio,0).bounded(100);
        Json expectedAudio;const auto resumedState=resumed.snapshot();for(const auto &row:resumedState.at("streams"))if(row.at("domain")=="audio"&&row.at("instance")==0)expectedAudio=row.at("rng");
        bridgeRest(restored);restored.configureAnimationClock(clock);
        while(loaded.remainingCooldown(knee,restored.nowMs())>0)restored.advanceSingleTick();
        check(restored.assignLearnedSkillSlot(0,std::nullopt).ok,"Normal Z test removes slot and uses source base command");
        restored.events.clear();restored.combat=true;restored.freezeAi=true;restored.player.mp=restored.player.maxMp;
        restored.mapWidth=3000;restored.walkRects={{0,185,3000,600}};restored.player.x=restored.player.px=600;
        restored.player.y=restored.player.py=300;const int zMp=restored.player.mp;
        restored.enqueue({restored.simulationNanoseconds(),4,true});restored.advanceSingleTick();
        restored.enqueue({restored.simulationNanoseconds(),4,false});restored.enqueue({restored.simulationNanoseconds(),6,true});restored.advanceSingleTick();
        restored.enqueue({restored.simulationNanoseconds(),6,false});
        check(loaded.attacking()&&restored.player.mp==zMp&&audioCount(restored)==0,
            "Normal default Z buffers during own basic action without early Knee cost or voice");
        bool continued=false;for(int n=0;n<240&&!continued;++n){restored.advanceSingleTick();continued=restored.player.animationPath==descriptor.motion.memberPath;}
        check(continued&&restored.player.mp<zMp&&loaded.remainingCooldown(knee,restored.nowMs())>0&&audioCount(restored)==2,
            "Normal source Z continues at the current action boundary with one real learned Knee cost and audio");
        Json actualAudio;const auto actualRandom=restored.randomStreams().snapshot();for(const auto &row:actualRandom.at("streams"))if(row.at("domain")=="audio"&&row.at("instance")==0)actualAudio=row.at("rng");
        check(actualAudio==expectedAudio&&std::count_if(restored.events.begin(),restored.events.end(),[&](const Event &e){
            return e.kind=="sound"&&e.name==(nextVoice<50?"GN_JACKSPIKE_01":"GN_JACKSPIKE_02");})==1,
            "First post-reload normal cast consumes the persisted next Audio choice, with no replay or reroll");
        for(int n=0;n<120;++n)restored.advanceSingleTick();bridgeRest(restored);
        const auto loadedNormal=restored.skillState().snapshot(restored.nowMs());const auto loadedConfig=restored.normalSkillConfigurationSnapshot();
        DebugOverrides debug;debug.enabled=true;debug.level=99;restored.applyDebugOverrides(debug,4);
        const auto testQuote=restored.quoteTestSkillLearning(knee);
        check(testQuote.accepted()&&restored.learnTestSkill({"normal-knee-isolated-level3",knee,testQuote.revision,3}).ok&&
            loaded.configuration().binding(knee)->level==3,"Knee test learning uses its own source-qualified level3 pool");
        check(restored.setExperimentalSkillPreviewEnabled(true).ok,"Knee manual preview opens explicitly after test learning");
        loaded.configuration().configureSourceSkillAction(knee,10,loaded.plan());loaded.configuration().configureSourceActionPassive(tp,1,loaded.plan());
        loaded.configuration().setSourceActionAudioPolicy("disabled",loaded.plan());
        check(restored.setExperimentalSkillPreviewEnabled(false).ok&&loaded.configuration().binding(knee)->level==3&&
            loaded.configuration().sourceActionPassiveLevel(tp)==0&&loaded.configuration().sourceActionAudioPolicy()=="inferred-current1031-knee-cast-audio-v1",
            "Leaving manual Knee preview strips manual TP/audio and rebuilds test-effective canonical source policy");
        restored.applyDebugOverrides({},4);
        check(restored.skillState().snapshot(restored.nowMs())==loadedNormal&&restored.normalSkillConfigurationSnapshot()==loadedConfig&&
            loaded.configuration().binding(knee)->level==2,"Leaving test restores exact paid normal Knee level/slots/history");
        store.close();
    }
    // Advancement and owned EQU changes must preserve the same normal source
    // consumer, paid budget and source qualification without a manual rebind.
    {
        const SkillKey knee{2,4};CharacterStore store(root/"normal-knee-equipment-gsd","normal-bridge-test");store.data=bridgeRoot({2,0,0},15);
        World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);bridgeRest(w);
        auto quote=w.quoteSkillLearning(knee,15);SkillLearningTransaction learning;
        check(quote.accepted()&&learning.submit(store,0,w,p,{"knee-equipment-buy",knee,quote.revision,2},Json::object()).ok&&
            w.assignLearnedSkillSlot(0,knee).ok,"Gunner source15 purchases actual Knee2 before equipment/GSD");
        auto &runtime=*w.experimentalRuntime();const auto &plan=runtime.plan();const Field *table=nullptr;
        for(const auto &f:plan.characterDefinition.settings.script.fields)if(f.tag=="[key value index]"&&!f.values.empty()&&
            (f.values[0]=="weaponSubTypeIndex"||f.values[0]=="defaultWeaponBySubType"))table=&f;
        check(table!=nullptr,"Knee equipment test reads current own subtype starter table");
        int count=0;
        for(size_t cell=2;cell+1<table->values.size();cell+=2) {
            const auto id=table->values[cell+1].get<int>();const auto *item=p.item(id);
            if(!item||item->minimumLevel>p.level()||!p.itemUsableBy(id,w.characterSource()))continue;
            const int uid=p.state.at("next_uid").get<int>(),index=int(p.state.at("inventory").size());p.state["next_uid"]=uid+1;
            p.state["inventory"].push_back({{"uid",uid},{"id",id},{"count",1},{"durability",item->durability}});
            check(w.changeEquipment(p,index).ok,"Normal Knee equips actual owned own-source EQU subtype");
            const auto normal=w.skillState().snapshot(w.nowMs()),budget=w.skillLearningBudget(false,15).json();
            const auto motion=readCharacterAttackMotion(assets,w.characterAppearance(),plan.sourceSkillActions.at(knee).motion.memberPath);
            check(!motion.weapons.empty()&&runtime.configuration().binding(knee)->level==2,
                "Actual EQU/LAY changes preserve learned Knee body/weapon composition");
            while(runtime.remainingCooldown(knee,w.nowMs())>0)w.advanceSingleTick();
            w.events.clear();w.player.mp=w.player.maxMp;const int before=w.player.mp;
            w.enqueue({w.simulationNanoseconds(),20,true});w.advanceSingleTick();w.enqueue({w.simulationNanoseconds(),20,false});
            const auto cost=runtime.snapshotDiagnostics().at("last_cost");
            check(runtime.attacking()&&before-w.player.mp==cost.at("mp").at("value").get<int>()&&
                runtime.configuration().sourceActionAudioPolicy()=="inferred-current1031-knee-cast-audio-v1",
                "Normally learned Knee uses equipped cost/clock and own canonical voice policy");
            for(int n=0;n<120;++n)w.advanceSingleTick();bridgeRest(w);
            check(w.skillState().snapshot(w.nowMs())==normal&&w.skillLearningBudget(false,15).json()==budget,
                "Changing EQU and casting Knee cannot alter normal learned/SP history");++count;
        }
        check(count>=2,"At least two distinct legal own-source weapon subtype compositions exercised");
        while(runtime.remainingCooldown(knee,w.nowMs())>0)w.advanceSingleTick();bridgeRest(w);store.capture(0,w,p);store.checkpoint();
        const auto budget=w.skillLearningBudget(false,15).json();Scene scene;MapNpc trainer;trainer.id=w.advancementCatalog().trainerId();
        trainer.source=w.advancementCatalog().trainerPath();trainer.visible=true;trainer.x=w.player.x;trainer.y=w.player.y;scene.npcs.push_back(trainer);
        CharacterAdvancementTransaction advancement;
        check(advancement.submit(store,0,w,p,scene,{"normal-knee-gsd",w.identity(),{2,1,0},store.generation(),trainer.id},Json::object()).ok&&
            w.identity()==CharacterIdentity{2,1,0}&&w.skillState().learnedLevel(knee)==2&&w.experimentalRuntime()->configuration().binding(knee)->level==2&&
            w.experimentalRuntime()->configuration().sourceActionAudioPolicy()=="inferred-current1031-knee-cast-audio-v1"&&w.skillLearningBudget(false,15).json()==budget,
            "Actual GSD source15 branch1 transaction retains paid Knee2, canonical voice and budget");
        World loaded(pvf,assets,WorldRules::BetaFoundationV1);loaded.enableExperimentalCharacters();Progression lp(regions);store.apply(0,loaded,lp);
        check(loaded.identity()==CharacterIdentity{2,1,0}&&loaded.experimentalRuntime()->configuration().binding(knee)->level==2&&
            loaded.experimentalRuntime()->configuration().sourceActionAudioPolicy()=="inferred-current1031-knee-cast-audio-v1",
            "GSD identity and normal Knee/audio policy reload through actual CharacterStore");
        loaded.player.mp=loaded.player.maxMp;loaded.enqueue({loaded.simulationNanoseconds(),6,true});loaded.advanceSingleTick();
        check(loaded.experimentalRuntime()->attacking()&&loaded.experimentalRuntime()->remainingCooldown(knee,loaded.nowMs())>0,
            "GSD-rebased own normal Knee still dispatches actual source default Z");store.close();
    }
    // Real female prerequisite and passive projections, not descriptor count.
    {
        CharacterStore store(root/"female-gunner","normal-bridge-test");store.data=bridgeRoot({5,0,0},30);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progress(regions);store.apply(0,world,progress);bridgeRest(world);
        writeJson(root/"female-initial-diagnostic.json",{{"ledger",world.skillState().snapshot(world.nowMs())},
            {"headshot_quote",world.quoteSkillLearning({5,5},30).json()},
            {"upbullet_policy",world.skillLearningConsumerMetadata({5,47})}});
        check(world.skillState().learnedLevel({5,47})==1&&world.runtimeSkillPolicy({5,47}).implemented&&
            !world.quoteSkillLearning({5,5},30).accepted(),
            "Female UpBullet free grant is preserved while HeadShot retains its real Ranger branch gate");
        store.capture(0,world,progress);store.checkpoint();
        Scene scene;MapNpc trainer;trainer.id=world.advancementCatalog().trainerId();
        trainer.source=world.advancementCatalog().trainerPath();trainer.visible=true;
        trainer.x=world.player.x;trainer.y=world.player.y;scene.npcs.push_back(trainer);
        CharacterAdvancementTransaction advancement;
        check(advancement.submit(store,0,world,progress,scene,
            {"female-ranger",world.identity(),{5,1,0},store.generation(),trainer.id},Json::object()).ok&&
            world.quoteSkillLearning({5,5},30).accepted(),
            "Actual GSD Ranger advancement makes HeadShot eligible using the same free initial UpBullet prerequisite");
        check(!world.runtimeSkillPolicy({5,8}).implemented&&!world.runtimeSkillPolicy({5,41}).implemented&&
            !world.runtimeSkillPolicy({5,35}).implemented&&!world.runtimeSkillPolicy({5,45}).implemented,
            "Unimplemented moving-kick/charged-laser passive chains remain visible blocked source rows");
        const SkillKey key{5,186};const auto quote=world.quoteSkillLearning(key,30);SkillLearningTransaction learning;
        check(quote.accepted()&&learning.submit(store,0,world,progress,{"physicalcrit1",key,quote.revision,1},Json::object()).ok,
            "Reviewed female physical critical passive purchases through the normal transaction");
        const auto levels=world.effectiveFemaleGunnerLevels();const auto &plan=world.experimentalRuntime()->plan();
        const auto modifiers=evaluateFemaleGunnerActorModifiers({},levels,plan,-1);
        check(levels.at(key)==1&&modifiers.physicalCriticalPercent>0&&!modifiers.trace.empty(),
            "Actual passive projection reaches existing damage critical-probability consumer");
        const auto canonical=world.effectiveFemaleGunnerLevels();world.experimentalRuntime()->configuration().configureFemaleGunnerSourceSkill(key,10,plan);
        check(world.effectiveFemaleGunnerLevels()==canonical,"Raw passive level cannot affect normal defense/attack consumers before the next tick");store.close();
    }
    return {{"status","pass"},{"checks",checks},{"save_directory",root.u8string()},
        {"scope","Actual World/storage/normal transaction/GSD/source-preflight tests; registration and execution are parent-owned and pending"}};
}
} // namespace dnf
