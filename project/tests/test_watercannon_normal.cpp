#include "dnf/skill_learning_transaction.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/scene.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
constexpr SkillKey water{8,26},tp{8,236},chain{8,51};
Json normalRoot(int level) {
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    root["characters"][0]={{"name","WaterNormalConsumer"},{"class","atmage"},
        {"identity",CharacterIdentity{8,0,0}.json()},{"level",level},{"weapon",0},{"skill_initialization","source-v1"}};
    return root;
}
void rest(World &world) {
    world.releaseInputs();world.changeScene();world.monsters.clear();world.events.clear();world.idle();world.combat=false;
    auto &a=world.player;a.dead=false;a.life=ActorLife::Alive;a.hp=a.maxHp;a.recovery=0;a.stunUntil=0;a.hitStopTicks=0;a.hitStopped=false;
    a.x=a.px=700;a.y=a.py=344;a.z=a.pz=a.vx=a.vy=a.vz=0;a.dir=1;
}
void arena(World &world) {
    world.combat=true;world.freezeAi=true;world.freeCd=false;world.mapWidth=3000;
    world.walkRects={{0,185,3000,600}};world.blockedRects.clear();world.player.mp=world.player.maxMp;
}
void input(World &world,int key,bool down){world.enqueue({world.simulationNanoseconds(),key,down});}
void cast(World &world){input(world,20,true);world.advanceSingleTick();input(world,20,false);}
void ticks(World &world,int count){while(count-->0)world.advanceSingleTick();}
void awaitCooldown(World &world) {
    for(int count=0;count<600&&world.experimentalRuntime()->remainingCooldown(water,world.nowMs())>0;++count)world.advanceSingleTick();
    world.releaseInputs();
}
Effect *flight(World &world) {
    for(auto &effect:world.effects)if(effect.phase=="source-nut:passive-object"&&effect.skill==26&&world.nowMs()<effect.expires)return &effect;
    return nullptr;
}
Effect *impact(World &world) {
    for(auto &effect:world.effects)if(effect.phase=="source-nut:watercannon-impact"&&world.nowMs()<effect.expires)return &effect;
    return nullptr;
}
bool reachFlight(World &world) {
    for(int count=0;count<100;++count){if(flight(world))return true;world.advanceSingleTick();}return false;
}
size_t audioCount(const World &world) {
    return size_t(std::count_if(world.events.begin(),world.events.end(),[](const Event &event){return event.kind=="sound"&&
        (event.name=="MW_WCANNON_READY"||event.name=="WCANNON_CAST");}));
}
size_t hitCount(const World &world,int target) {
    return size_t(std::count_if(world.events.begin(),world.events.end(),[&](const Event &event){
        return event.kind=="hit"&&event.name=="source_nut_passive_object"&&event.target==target;}));
}
void target(World &world,int id,double x,double y,double z) {
    Actor a;a.id=id;a.sourceId=10;a.monsterPath="monster/goblin/goblin.mob";a.x=a.px=x;a.y=a.py=y;a.z=a.pz=z;a.dir=-1;
    world.initializeMonsterAttributes(a,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");a.hp=a.maxHp=100000000;
    world.monsters.push_back(std::move(a));world.synchronizeEntityHandles();
}
Json live(const World &world,const Progression &progression) {
    const auto &runtime=*world.experimentalRuntime();
    return {{"world",world.snapshot()},{"simulation",world.simulationCheckpoint()},
        {"ledger",world.skillState().snapshot(world.nowMs())},{"overlay",world.skillTestOverlay().snapshot()},
        {"normal_configuration",world.normalSkillConfigurationSnapshot()},{"configuration",runtime.configuration().snapshot()},
        {"manual_configuration",world.manualSkillPreviewSnapshot()},{"cooldowns",runtime.cooldownSnapshot(world.nowMs())},
        {"progression",progression.state},{"preview",world.experimentalSkillPreviewEnabled()}};
}
Scene trainer(const World &world) {
    Scene scene;MapNpc npc;npc.id=world.advancementCatalog().trainerId();npc.source=world.advancementCatalog().trainerPath();
    npc.visible=true;npc.x=world.player.x;npc.y=world.player.y;scene.npcs.push_back(npc);return scene;
}
}

Json runWaterCannonNormalTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool accepted,const std::string &message){
        checks.push_back({{"passed",accepted},{"message",message}});
        if(!accepted){writeJson("watercannon-normal-failure.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}
    };
    RegionCatalog regions(pvf,assets);const auto stamp=std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto root=std::filesystem::absolute(std::filesystem::path("cache/watercannon-normal-tests")/std::to_string(stamp));
    {
        CharacterStore store(root/"source-level1","watercannon-normal-test");store.data=normalRoot(1);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progression(regions);
        store.apply(0,world,progression);rest(world);const auto quote=world.quoteSkillLearning(water,1);
        check(world.skillState().learnedLevel(water)==1&&world.experimentalRuntime()->configuration().binding(water)->level==1&&
            world.skillLearningBudget(false,1).spentSp==0&&world.skillUseEligibility(water).allowed()&&
            quote.gate==SkillLearningGate::CharacterLevel&&quote.requiredCharacterLevel==3,
            "An actual level1 source-v1 character receives usable free Water1 while Water2 remains source-level3 gated");store.close();
    }
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines})
    for(const auto fault:{SaveFailurePoint::BeforePublish,SaveFailurePoint::AfterPublish}) {
        const auto run=std::string(ani_clock::policyName(clock))+"-"+std::to_string(int(fault));
        CharacterStore store(root/run,"watercannon-normal-test");store.data=normalRoot(3);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progression(regions);
        store.apply(0,world,progression);rest(world);world.configureAnimationClock(clock);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();const auto &descriptor=plan.sourceSkillActions.at(water);
        check(!world.experimentalSkillPreviewEnabled()&&!world.debugOverrides().enabled&&world.runtimeSkillPolicy(water).implemented&&
            world.skillState().learnedLevel(water)==1&&runtime.configuration().binding(water)&&runtime.configuration().binding(water)->level==1&&
            world.skillLearningBudget(false,3).spentSp==0,"Real source-v1 CHR grants free normal WaterCannon1 and projects its own moving-impact binding");
        check(!world.runtimeSkillPolicy(tp).implemented&&!world.runtimeSkillPolicy(chain).implemented&&
            !world.quoteSkillLearning(tp,3).accepted()&&!world.quoteSkillLearning(chain,3).accepted()&&
            !world.skillLearning().sourceUseEligibility({8,5,0},water,1,50).allowed(),
            "Normal base26 admission does not fabricate TP/chain consumers or growtype5 fitness from a sixth maximum slot");
        const auto metadata=world.skillLearningConsumerMetadata(water);
        check(metadata.at("normal_learning_consumer_bound")==true&&metadata.at("normal_release_blocker")==""&&
            metadata.at("tp_236_normal_admitted")==false&&metadata.at("elemental_chain_51_normal_admitted")==false&&
            metadata.at("source_action")==descriptor.snapshot(),"Current normal admission metadata wraps immutable source descriptor without rewriting its evidence");
        check(world.assignLearnedSkillSlot(0,water).ok,"Normal free WaterCannon1 is selectable through actual learned hotbar command");
        store.capture(0,world,progression);store.checkpoint();const auto initialized=world.skillState().snapshot(world.nowMs());
        World repeated(pvf,assets,WorldRules::BetaFoundationV1);repeated.enableExperimentalCharacters();Progression repeatedProgress(regions);
        store.apply(0,repeated,repeatedProgress);store.apply(0,repeated,repeatedProgress);
        check(repeated.skillState().snapshot(repeated.nowMs())==initialized&&repeated.experimentalRuntime()->configuration().binding(water)->level==1&&
            repeated.skillLearningBudget(false,3).spentSp==0,"Repeated actual CharacterStore reload never grants WaterCannon or charges SP twice");
        const auto quote=world.quoteSkillLearning(water,3);const auto batch=world.quoteSkillLearningBatch(false,3);
        const auto row=std::find_if(batch.quotes.begin(),batch.quotes.end(),[](const auto &entry){return entry.key==water;});
        check(quote.accepted()&&quote.targetLevel==2&&quote.requiredCharacterLevel==3&&quote.cost==15&&quote.currency=="SP"&&quote.purchaseMaximum==50&&
            row!=batch.quotes.end()&&row->json()==quote.json(),"Normal UI batch and individual quote use exact source Lv3/SP15/max50 for WaterCannon1 to2");
        const SkillLearningRequest buy{"normal-water-level2",water,quote.revision,2};SkillLearningTransaction transaction;
        const auto before=live(world,progression);const auto generation=store.generation();
        store.setFailureInjector([fault](SaveFailurePoint actual){if(actual==fault)throw std::runtime_error("normal WaterCannon durable fault");});
        const auto pending=transaction.submit(store,0,world,progression,buy,Json::object());
        check(!pending.ok&&transaction.pending()&&live(world,progression)==before,
            "Before/after durable publication fault retains exact live Water ledger, slot, MP/CD, RNG and source configuration");
        store.setFailureInjector({});check(transaction.retry(store,world).ok&&store.generation()==generation+1&&
            world.skillState().learnedLevel(water)==2&&runtime.configuration().binding(water)->level==2,
            "Retry publishes one retained prepared normal WaterCannon2 generation");
        const auto budget=world.skillLearningBudget(false,3).json();const auto committedGeneration=store.generation();
        check(budget.at("spent_sp")==15&&transaction.submit(store,0,world,progression,buy,Json::object()).state==SkillLearningTransactionState::Replayed&&
            store.generation()==committedGeneration&&world.skillLearningBudget(false,3).json()==budget,
            "Exact durable Water purchase replay cannot spend the source SP15 twice");
        const auto next=world.quoteSkillLearning(water,3);
        check(next.gate==SkillLearningGate::CharacterLevel&&next.targetLevel==3&&next.requiredCharacterLevel==5,
            "Next normal Water level3 retains source character5 growth requirement");
        const auto normal=world.skillState().snapshot(world.nowMs()),canonical=world.normalSkillConfigurationSnapshot();
        runtime.configuration().configureSourceSkillAction(water,10,plan);world.advanceSingleTick();
        check(runtime.configuration().binding(water)->level==2&&world.normalSkillConfigurationSnapshot()==canonical&&
            world.skillState().snapshot(world.nowMs())==normal,"Normal simulation rejects raw high Water level and restores ledger-derived binding before input");
        arena(world);world.events.clear();const auto mp=world.player.mp;const auto ledgerCd=world.skillState().remainingCooldown(water,world.nowMs());
        cast(world);const auto cost=runtime.snapshotDiagnostics().at("last_cost");
        check(runtime.attacking()&&mp-world.player.mp==cost.at("mp").at("value").get<int>()&&
            runtime.remainingCooldown(water,world.nowMs())==int64_t(std::ceil(cost.at("cooldown_ms").at("value").get<double>()))&&
            world.skillState().remainingCooldown(water,world.nowMs())==ledgerCd,
            "Real learned slot starts fixed Water body and pays exactly one evaluated experimental MP/CD authority");
        check(reachFlight(world),"Normal learned Water source flag actually creates flight");const auto rootFlight=*flight(world);
        check(rootFlight.imageScale==1.27&&rootFlight.expires-rootFlight.born==850,
            "Normal paid Water level2, without TP, controls actual 127 percent flight size and independent lifetime");
        bool sawFlightVolume=false;
        for(const auto &volume:world.attackVolumes)if(volume.skillId==26&&volume.sourceAttackFamily=="source_watercannon_flight"&&volume.sourceModifiers)
            sawFlightVolume|=volume.sourceModifiers->percent==188;
        for(int count=0;count<100&&runtime.attacking();++count)world.advanceSingleTick();
        check(sawFlightVolume&&!runtime.attacking()&&flight(world)&&runtime.remainingCooldown(water,world.nowMs())>0&&audioCount(world)==2,
            "Empty normal cast consumes source level2 coefficient188 and one READY/CAST pair; body ends while independently timed flight and evaluated cooldown remain");
        world.events.clear();const auto cooldownMp=world.player.mp;const auto randomBefore=world.randomStreams().snapshot();
        cast(world);
        check(!runtime.attacking()&&flight(world)&&flight(world)->id==rootFlight.id&&world.player.mp==cooldownMp&&audioCount(world)==0&&world.randomStreams().snapshot()==randomBefore,
            "Normal cooldown rejection starts no body, audio, RNG, replacement entity or second fee during the actual independent-flight window");
        ticks(world,85);
        check(!runtime.attacking()&&runtime.snapshotDiagnostics().at("source_nut_entities")==0&&!flight(world)&&!impact(world)&&
            world.skillState().snapshot(world.nowMs())==normal,
            "Empty normal cast retires all independent effects on source lifetime without normal ledger mutation");
        rest(world);awaitCooldown(world);world.player.mp=0;world.events.clear();cast(world);
        check(!runtime.attacking()&&runtime.remainingCooldown(water,world.nowMs())==0&&world.player.mp==0&&audioCount(world)==0,
            "Normal insufficient-MP rejection keeps cooldown clear and emits no cast audio");
        rest(world);arena(world);cast(world);check(reachFlight(world),"Normal contact cast reaches its own flying entity");const auto fired=*flight(world);
        target(world,1,fired.x+15,fired.y,fired.z);target(world,2,fired.x+55,fired.y,fired.z);world.randomStreams()=RandomStreams(67);
        for(int count=0;count<20&&!impact(world);++count)world.advanceSingleTick();
        check(impact(world)&&hitCount(world,1)==1&&!flight(world),"Normal World nonmiss contact retires flight and creates an independent impact once");
        const auto impactReceipt=impact(world)->projectileSource;bool monsterOwnAni=false,lift=false;
        for(int count=0;count<65;++count){for(const auto &monster:world.monsters){
            monsterOwnAni|=monster.animationPath.rfind("monster/goblin/",0)==0;lift|=monster.vz>0;}world.advanceSingleTick();}
        check(hitCount(world,1)==1&&hitCount(world,2)==1&&monsterOwnAni&&lift&&world.monsters[0].hp<100000000&&world.monsters[1].hp<100000000&&
            !impact(world)&&runtime.snapshotDiagnostics().at("source_nut_entities")==0,
            "Normal learned Water reaches real damage, original-target exclusion, second-target impact and monster own ANI/lift consumers");
        rest(world);const auto cooldown=runtime.cooldownSnapshot(world.nowMs()),random=world.randomStreams().snapshot();
        store.capture(0,world,progression);store.checkpoint();
        World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression restoredProgress(regions);store.apply(0,restored,restoredProgress);
        auto &loaded=*restored.experimentalRuntime();
        check(!restored.experimentalSkillPreviewEnabled()&&!restored.debugOverrides().enabled&&restored.skillState().snapshot(restored.nowMs())==normal&&
            loaded.configuration().binding(water)->level==2&&loaded.configuration().slots()[0]==std::optional<SkillKey>(water)&&
            loaded.cooldownSnapshot(restored.nowMs())==cooldown&&restored.randomStreams().snapshot()==random&&restored.skillLearningBudget(false,3).json()==budget,
            "Same-generation normal reload preserves Water paid level, exact slot, cooldown, point history and random streams");
        rest(restored);const auto loadedNormal=restored.skillState().snapshot(restored.nowMs()),loadedConfig=restored.normalSkillConfigurationSnapshot();
        DebugOverrides debug;debug.enabled=true;debug.level=99;restored.applyDebugOverrides(debug,3);
        const auto testQuote=restored.quoteTestSkillLearning(water);
        check(testQuote.accepted()&&restored.learnTestSkill({"water-test-level3",water,testQuote.revision,3}).ok&&loaded.configuration().binding(water)->level==3,
            "Isolated test Water purchase reaches its own source-qualified binding without normal SP changes");
        check(restored.setExperimentalSkillPreviewEnabled(true).ok,"Water manual preview switches explicitly after test-effective projection");
        loaded.configuration().configureSourceSkillAction(water,10,loaded.plan());
        check(restored.setExperimentalSkillPreviewEnabled(false).ok&&loaded.configuration().binding(water)->level==3,
            "Leaving manual Water10 preview restores test-effective Water3");
        restored.applyDebugOverrides({},3);
        check(restored.skillState().snapshot(restored.nowMs())==loadedNormal&&restored.normalSkillConfigurationSnapshot()==loadedConfig&&
            loaded.configuration().binding(water)->level==2,"Leaving isolated test restores exact normal Water2 ledger and slots");
        for(const std::string faultName:{"impact_clip","flight_clip"}) {
            auto invalid=std::make_shared<ExperimentalCharacterPlan>(loaded.plan());auto &moving=*invalid->sourceSkillActions.at(water).movingImpact;
            if(faultName=="impact_clip")moving.impactAnimation.memberPath="missing/normal-water-impact.ani";
            else invalid->sourceSkillActions.at(water).animation.memberPath="missing/normal-water-flight.ani";
            ExperimentalCharacterRuntime invalidRuntime(invalid);SkillRuntimeProjectionContext context;context.runtime=&invalidRuntime;
            context.normalPreferences=&loaded.configuration();context.normalLevel=context.effectiveLevel=3;
            const auto unchanged=live(restored,restoredProgress);bool refused=false;
            try{restored.prepareSkillRuntime(restored.skillState(),restored.skillTestOverlay(),context);}catch(const std::exception &){refused=true;}
            check(refused&&live(restored,restoredProgress)==unchanged,
                "Normal learned preparation validates impact/tree policy privately before any ledger/slot/save publication: "+faultName);
        }
        evidence.push_back({{"run",run},{"quote",quote.json()},{"cost",cost},{"impact",impactReceipt},{"budget",budget}});store.close();
    }
    // Current user policy preserves the learned ledger through actual GSD
    // identity transactions. It does not grant all CHR awakening skills.
    for(int branch:{1,2}) {
        CharacterStore store(root/("gsd-branch"+std::to_string(branch)),"watercannon-normal-test");store.data=normalRoot(50);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progression(regions);store.apply(0,world,progression);rest(world);
        check(world.assignLearnedSkillSlot(0,water).ok,"Normal base Water binds before source GSD identity changes");
        const auto quote=world.quoteSkillLearning(water,50);SkillLearningTransaction purchase;
        check(quote.accepted()&&purchase.submit(store,0,world,progression,{"before-gsd-water2",water,quote.revision,2},Json::object()).ok,
            "Actual paid Water2 ledger exists before GSD branch change");
        const auto ledger=world.skillState().snapshot(world.nowMs()),budget=world.skillLearningBudget(false,50).json();
        for(int awakening:{0,1}) {
            const CharacterIdentity destination{8,branch,awakening};const auto scene=trainer(world);
            const CharacterAdvancementRequest request{"water-gsd-"+std::to_string(branch)+"-"+std::to_string(awakening),world.identity(),destination,
                store.generation(),world.advancementCatalog().trainerId()};CharacterAdvancementTransaction advancement;
            const auto result=advancement.submit(store,0,world,progression,scene,request,Json::object());
            if(!result.ok)throw std::runtime_error("Water normal GSD: "+result.json().dump());
            auto after=world.skillState().snapshot(world.nowMs());after["identity"]=ledger["identity"];
            check(world.identity()==destination&&after==ledger&&world.skillLearningBudget(false,50).json()==budget&&
                world.runtimeSkillPolicy(water).implemented&&world.skillUseEligibility(water).allowed()&&
                world.experimentalRuntime()->configuration().binding(water)->level==2&&world.experimentalRuntime()->configuration().slots()[0]==std::optional<SkillKey>(water)&&
                world.skillState().learnedLevel(chain)==0&&world.skillState().learnedLevel(tp)==0,
                "Actual GSD branch/awakening rebase preserves paid base Water eligibility and slot without inventing unsupported passive grants");
        }
        World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression restoredProgress(regions);store.apply(0,restored,restoredProgress);
        check(restored.identity()==world.identity()&&restored.skillState().snapshot(restored.nowMs())==world.skillState().snapshot(world.nowMs())&&
            restored.skillUseEligibility(water).allowed()&&restored.experimentalRuntime()->configuration().binding(water)->level==2,
            "Real awakened GSD save reload retains normally learned Water2 and source qualification");store.close();
    }
    // Genuine legacy-import initialization validates a complete retained grant
    // history. These are diagnostic fixtures, never new source/player rewards.
    for(const SkillKey unsupported:{tp,chain}) {
        CharacterStore store(root/("legacy-passive"+std::to_string(unsupported.skillId)),"watercannon-normal-test");store.data=normalRoot(50);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progression(regions);store.apply(0,world,progression);rest(world);
        check(world.assignLearnedSkillSlot(0,water).ok,"Legacy fixture starts with a real assigned normally learned Water slot");
        auto imported=world.skillState().snapshot(world.nowMs());imported.erase("learning");
        for(auto &record:imported["skills"])if(SkillKey::fromJson(record.at("key"))==water)record["level"]=10;
        imported["skills"].push_back({{"key",unsupported.json()},{"level",1},{"remaining_cooldown_ms",0},
            {"fixture","explicit legacy import; unsupported passive retained"}});
        CharacterSkillState raw(world.identity());raw.restore(imported,world.nowMs());
        const auto migration=world.skillLearning().prepareInitialization(raw,50,SkillInitializationMode::LegacyImport,world.nowMs());
        check(migration.ok,"Legacy optional passive fixture uses real source-bound initialization and complete legacy grant history");
        world.publishSkillLedger(migration.state);const auto normal=world.skillState().snapshot(world.nowMs());
        const auto gate=world.skillUseEligibility(water);const auto metadata=world.skillLearningConsumerMetadata(water);
        check(world.runtimeSkillPolicy(water).implemented&&!world.runtimeSkillPolicy(unsupported).implemented&&
            gate.gate==SkillLearningGate::SpecialQualification&&gate.error.find(std::to_string(unsupported.skillId))!=std::string::npos&&
            metadata.at("normal_release_blocker")==gate.error&&world.skillState().learnedLevel(unsupported)==1,
            "Already learned unsupported 236/51 produces concrete base26 release diagnostic while preserving capability row and ledger");
        arena(world);world.events.clear();const auto beforeMp=world.player.mp;const auto random=world.randomStreams().snapshot();cast(world);ticks(world,40);
        check(!world.experimentalRuntime()->attacking()&&world.player.mp==beforeMp&&world.experimentalRuntime()->remainingCooldown(water,world.nowMs())==0&&
            audioCount(world)==0&&!flight(world)&&!impact(world)&&world.randomStreams().snapshot()==random&&world.skillState().snapshot(world.nowMs())==normal,
            "A previously assigned normal Water slot cannot silently ignore imported unsupported passive or charge MP/CD/audio before its blocker");
        rest(world);store.capture(0,world,progression);store.checkpoint();
        World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression restoredProgress(regions);store.apply(0,restored,restoredProgress);
        check(restored.skillState().snapshot(restored.nowMs())==normal&&restored.skillState().learnedLevel(unsupported)==1&&
            restored.skillUseEligibility(water).gate==SkillLearningGate::SpecialQualification,
            "Unsupported legacy passive and specific Water blocker survive same-generation save/reload without erasing learned data");
        evidence.push_back({{"legacy_passive",unsupported.json()},{"release_gate",gate.json()},{"metadata",metadata}});store.close();
    }
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"evidence",evidence},{"save_directory",root.u8string()},
        {"normal_base_26_consumer_bound",true},{"tp_236_normal_admitted",false},{"elemental_chain_51_normal_admitted",false},
        {"native_parity",false},{"scope","Normal World/learning/hotbar/MP/CD/contact/GSD/save consumers; no frontend or native dynamic comparison"}};
}
} // namespace dnf
