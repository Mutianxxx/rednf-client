#include "dnf/pending_rewards.hpp"
#include "dnf/skill_learning_transaction.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/character_entry.hpp"
#include "dnf/beta_branch.hpp"
#include "dnf/female_gunner_modifiers.hpp"
#include "dnf/scene.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <functional>
#include <stdexcept>

namespace dnf {
namespace {
namespace fs=std::filesystem;
using Check=std::function<void(bool,const std::string &)>;
Json sourceCharacter(int job,int level) {
    static const char *names[]={"swordman","fighter","gunner","mage","priest","atgunner","thief","atfighter","atmage"};
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    root["characters"][0]={{"name","Normal learning reward bridge"},{"class",names[job]},
        {"identity",CharacterIdentity{job,0,0}.json()},{"level",level},{"weapon",0},
        {"skill_initialization","source-v1"},{"future_character",{{"preserved",53}}}};
    return root;
}
Json learningViews(const World &world) {
    return {{"ledger",world.skillState().snapshot(world.nowMs())},
        {"overlay",world.skillTestOverlay().snapshot()},
        {"normal",world.normalSkillConfigurationSnapshot()},
        {"test",world.testSkillConfigurationSnapshot()},
        {"manual",world.manualSkillPreviewSnapshot()},
        {"preview_enabled",world.experimentalSkillPreviewEnabled()}};
}
Json frozen(const World &world,const Progression &progress) {
    return {{"simulation",world.simulationCheckpoint()},{"learning",learningViews(world)},
        {"progression",progress.state},{"cooldowns",world.experimentalRuntime()->cooldownSnapshot(world.nowMs())},
        {"stats",world.statReport()},{"hp",world.player.hp},{"mp",world.player.mp}};
}
Json townSession(const World &world) {return RegionSession{}.save(world,"town");}
void capture(CharacterStore &store,const World &world,const Progression &progress,const RegionSession *session=nullptr) {
    store.capture(0,world,progress);
    store.data["characters"][0]["region_session"]=session?session->save(world,"dungeon"):townSession(world);
}
void checkpoint(CharacterStore &store,PendingRewardService &reward,const World &world,
                const Progression &progress,const Check &check,const RegionSession *session=nullptr) {
    capture(store,world,progress,session);store.checkpoint();
    check(reward.acknowledgeCheckpoint(progress,world,store,0),"Actual captured writer generation acknowledged");
}
void learn(CharacterStore &store,World &world,const Progression &progress,SkillKey key,
           const std::string &requestId,const Check &check) {
    const auto quote=world.quoteSkillLearning(key,progress.level());
    check(quote.accepted(),"Current source normal quote accepted for "+requestId);
    const auto spent=world.skillLearningBudget(false,progress.level()).spentSp;
    SkillLearningTransaction transaction;
    const auto result=transaction.submit(store,0,world,progress,
        {requestId,key,quote.revision,quote.targetLevel},townSession(world));
    check(result.ok&&!transaction.pending()&&!store.hasPendingCommit()&&
          world.skillState().learnedLevel(key)==quote.targetLevel&&
          world.skillLearningBudget(false,progress.level()).spentSp==spent+quote.cost,
        "Real durable normal transaction spends the actual quote once for "+requestId);
}
// Only simulation ticks finish actions/recovery/entities. A timeout reports the
// actual runtime state; no idle(), cancel(), changeScene() or actor reset hides it.
void finishAction(World &world,const Check &check) {
    const auto start=world.tick;
    while(!world.skillLearningProjectionReady()&&world.tick-start<3600)world.advanceSingleTick();
    if(!world.skillLearningProjectionReady())throw std::runtime_error("Source action did not reach neutral within diagnostic 60s guard: "+
        world.experimentalRuntime()->snapshotDiagnostics().dump());
    check(true,"Source action naturally reaches neutral without state reset");
}
Json castOnce(World &world,SkillKey key,int level,int slot,const Check &check) {
    auto &runtime=*world.experimentalRuntime();
    check(world.skillLearningProjectionReady()&&runtime.remainingCooldown(key,world.nowMs())==0,
        "Actual input starts at neutral with elapsed source cooldown");
    const auto ledger=world.skillState().snapshot(world.nowMs());
    const auto sequence=runtime.snapshotDiagnostics().at("action_sequence").get<uint64_t>();
    const int mp=world.player.mp;const int logical=20+slot;
    world.enqueue({world.simulationNanoseconds(),logical,true});world.advanceSingleTick();
    const auto cost=runtime.snapshotDiagnostics().at("last_cost");
    const auto rawMp=cost.at("mp").at("value").get<double>();
    const auto rawCd=cost.at("cooldown_ms").at("value").get<double>();
    check(cost.at("key")==key.json()&&cost.at("effective_level")==level&&std::isfinite(rawMp)&&
          rawMp>0&&rawMp==std::trunc(rawMp)&&std::isfinite(rawCd)&&rawCd>0,
        "Runtime release exposes this SkillKey/effective level and source integer MP/CD trace");
    const auto chargedMp=world.player.mp;const auto releasedAt=world.nowMs();
    const auto cd=int64_t(std::ceil(rawCd));
    check(runtime.attacking()&&mp-chargedMp==int(rawMp)&&runtime.remainingCooldown(key,releasedAt)==cd&&
          runtime.snapshotDiagnostics().at("action_sequence").get<uint64_t>()==sequence+1&&
          world.skillState().snapshot(world.nowMs())==ledger,
        "Actual logical slot charges exactly one runtime MP/CD/action and leaves generic normal ledger untouched");
    world.enqueue({world.simulationNanoseconds(),logical,true});
    world.enqueue({world.simulationNanoseconds(),logical,false});world.advanceSingleTick();
    check(world.player.mp==chargedMp&&runtime.remainingCooldown(key,world.nowMs())==
          std::max<int64_t>(0,cd-(world.nowMs()-releasedAt))&&
          runtime.snapshotDiagnostics().at("action_sequence").get<uint64_t>()==sequence+1&&
          world.skillState().snapshot(world.nowMs())==ledger,
        "Repeated down and real up during the source action cannot charge a second MP/CD consumer");
    finishAction(world,check);return cost;
}
// Source boss identities/positions are real. HP=1 and diagnostic accepted hits
// are explicitly a reward fixture, not normal combat or complete main traversal.
void diagnosticBossClear(World &world,RegionSession &session,RegionCatalog &catalog,uint64_t seed,const Check &check) {
    check(world.skillLearningProjectionReady()&&world.monsters.empty(),"Reward fixture installs no actors over an active action or prior room");
    check(catalog.prepareDungeon(1).at("status")=="prepared","Actual Lorien DGN/MAP/MOB reward closure prepared");
    session.begin(catalog,1,seed);session.run.current=session.run.boss;
    const auto &spawns=catalog.maps.at(session.run.room().mapId).monsters;
    check(spawns.size()>=2,"Source boss room contains actual multiple actors");
    world.combat=true;world.freezeAi=true;world.mapWidth=1400;world.walkRects={{0,0,1400,700}};
    for(size_t i=0;i<spawns.size();++i) {
        Actor actor;actor.id=int(i+1);actor.sourceId=spawns[i].id;actor.monsterPath=catalog.monsterPath(spawns[i].id);
        actor.x=actor.px=spawns[i].x;actor.y=actor.py=spawns[i].y+80;actor.z=actor.pz=spawns[i].z;
        actor.hp=actor.maxHp=1;actor.boss=spawns[i].type=="[boss]";world.monsters.push_back(std::move(actor));
    }
    world.synchronizeEntityHandles();const auto first=world.tick+2,rest=world.tick+4;
    world.setObjectTick([first,rest](World &simulation){
        if(simulation.tick==first)simulation.diagnosticHit(1,1,0,0,1,{});
        if(simulation.tick==rest)for(size_t i=1;i<simulation.monsters.size();++i)
            simulation.diagnosticHit(int(i+1),1,0,0,1,{});
    });
    for(int i=0;i<4;++i)world.advanceSingleTick();world.setObjectTick({});session.remember(world);
    check(session.run.complete(),"Relative diagnostic ticks actually kill a nonempty source boss room");
}
void justBelowNextLevel(Progression &progress,const Check &check) {
    const auto level=progress.level();const int needed=progress.experienceToNextLevel();
    check(needed>1,"Source XP threshold permits an explicit below-next-level fixture");
    progress.addExperience(needed-1);
    check(progress.level()==level&&progress.experienceToNextLevel()==1,
        "Fixture uses actual Progression XP API and never directly rewrites level or reward receipts");
}
Json passive(World &world) {
    return evaluateFemaleGunnerActorModifiers({},world.effectiveFemaleGunnerLevels(),world.experimentalRuntime()->plan(),-1).snapshot();
}
}

Json runNormalRewardRuntimeBridgeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::array();
    const Check check=[&](bool okay,const std::string &message) {
        if(!okay)throw std::runtime_error("Normal reward bridge: "+message);checks.push_back(message);
    };
    const auto directory=fs::absolute(fs::path("cache/normal-reward-runtime-bridge")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    check(normalize(directory.root_name().u8string())=="d:","All isolated save fixtures and evidence stay on D:");
    RegionCatalog catalog(pvf,assets);
    const std::array<SkillKey,3> cases={{{1,6},{3,4},{5,5}}};
    for(size_t index=0;index<cases.size();++index) {
        const auto key=cases[index];const auto path=directory/("normal-job"+std::to_string(key.jobId));
        CharacterStore store(path,pvf.identity());store.data=sourceCharacter(key.jobId,key.jobId==5?30:5);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        Progression progress(catalog);store.apply(0,world,progress);world.combat=false;
        check(world.skillLearningProjectionReady(),"Fresh source-v1 character has no active transient action");
        PendingRewardService reward;reward.characterBoundary(world);checkpoint(store,reward,world,progress,check);
        if(key.jobId==5) {
            check(world.skillState().learnedLevel({5,47})==1&&!world.quoteSkillLearning(key,30).accepted(),
                "Real CHR UpBullet initial grant does not bypass HeadShot Ranger qualification");
            Scene scene;MapNpc trainer;trainer.id=world.advancementCatalog().trainerId();
            trainer.source=world.advancementCatalog().trainerPath();trainer.visible=true;
            trainer.x=world.player.x;trainer.y=world.player.y;scene.npcs.push_back(trainer);
            CharacterAdvancementTransaction advancement;
            const auto result=advancement.submit(store,0,world,progress,scene,
                {"reward-bridge-ranger",world.identity(),{5,1,0},store.generation(),trainer.id},townSession(world));
            check(result.ok&&world.identity()==CharacterIdentity{5,1,0},"Real GSD transaction establishes source Ranger before advanced learning");
            learn(store,world,progress,{5,186},"reward-bridge-critical1",check);
            const auto modifiers=passive(world);
            check(world.effectiveFemaleGunnerLevels().at({5,186})==1&&
                  modifiers.at("physical_critical_percent").get<double>()>0&&!modifiers.at("trace").empty(),
                "Normally purchased female passive reaches existing critical probability evaluator");
        }
        learn(store,world,progress,key,"reward-bridge-active1",check);
        check(world.assignLearnedSkillSlot(0,key).ok,"Normally learned SkillKey is assigned by production normal hotbar API");
        checkpoint(store,reward,world,progress,check);
        const auto normal=learningViews(world);const auto modifiers=key.jobId==5?passive(world):Json();
        const auto cast=castOnce(world,key,1,0,check);
        check(learningViews(world)==normal,"Natural release/recovery cannot mutate any normal/test/manual learning view");
        justBelowNextLevel(progress,check);checkpoint(store,reward,world,progress,check);
        const int level=progress.level();RegionSession session;
        diagnosticBossClear(world,session,catalog,12001+index,check);
        const auto rng=world.randomStreams().snapshot();
        check(reward.observe(progress,world,session,session.save(world,"dungeon"))&&reward.hasPending(progress)&&
              reward.needsCheckpoint()&&world.randomStreams().snapshot()==rng,
            "Actual accepted kills capture durable reward intent without drawing Loot");
        checkpoint(store,reward,world,progress,check,&session);
        const int hpLoss=world.player.maxHp-world.player.hp,mpLoss=world.player.maxMp-world.player.mp;
        const auto cd=world.experimentalRuntime()->cooldownSnapshot(world.nowMs());
        check(reward.prepareAndPublish(progress,world,catalog)&&progress.level()>level&&
              world.normalCharacterLevel()==progress.level()&&world.characterLevel==progress.level()&&
              world.statReport().at("last_attribute_change").at("reason")=="normal_level_up"&&
              world.player.maxHp-world.player.hp==hpLoss&&world.player.maxMp-world.player.mp==mpLoss,
            "Actual reward candidate calls World applyEquipment and source level-up preserves consumed HP/MP losses");
        check(learningViews(world)==normal&&world.experimentalRuntime()->cooldownSnapshot(world.nowMs())==cd&&
              (key.jobId!=5||passive(world)==modifiers)&&!reward.hasPending(progress)&&reward.needsCheckpoint(),
            "Reward publication keeps exact SkillKey ledgers/passive/normal-test-manual slots/CD and remains blocked until final save");
        const auto prepared=frozen(world,progress);const auto generation=store.generation();
        const auto point=index%2?SaveFailurePoint::AfterPublish:SaveFailurePoint::BeforePublish;
        store.setFailureInjector([point](SaveFailurePoint at){if(at==point)throw std::runtime_error("Injected normal reward final boundary fault");});
        capture(store,world,progress,&session);bool failed=false;
        try{store.checkpoint();}catch(const std::exception &){failed=true;}
        check(failed&&store.hasPendingCommit()&&store.generation()==generation&&frozen(world,progress)==prepared&&
              !reward.acknowledgeCheckpoint(progress,world,store,0),
            "Before/after final disk publication fault leaves exact prepared runtime/progress/RNG/CD and no false acknowledgement");
        store.setFailureInjector({});store.retryPending();
        check(store.generation()==generation+1&&reward.acknowledgeCheckpoint(progress,world,store,0)&&
              !reward.blocked(progress)&&reward.clearReceipt(progress,session)&&frozen(world,progress)==prepared,
            "Actual retained final checkpoint retries once without reroll or another runtime projection");
        const auto finalCharacter=store.data.at("characters")[0];store.close();
        CharacterStore reloaded(path,pvf.identity());World restored(pvf,assets,WorldRules::BetaFoundationV1);
        restored.enableExperimentalCharacters();Progression rp(catalog);reloaded.apply(0,restored,rp);
        restoreSessionPlayer(restored,finalCharacter.at("region_session").at("player"));
        const auto savedSimulation=finalCharacter.at("simulation"),restoredSimulation=restored.simulationCheckpoint();
        // Restore intentionally retires every saved actor incarnation and
        // allocates a fresh player. Preserve all other checkpoint fields.
        auto expectedStable=savedSimulation,actualStable=restoredSimulation;
        expectedStable.erase("entities");actualStable.erase("entities");
        check(actualStable==expectedStable&&savedSimulation.at("inputs").at("pending").empty(),
            "Restore preserves exact clock, action/effect/status watermarks, input sequence, RNG and source-think checkpoint under explicit transient policy");
        EntityRegistry remapped;remapped.restore(restoredSimulation.at("entities"));
        const auto savedNext=savedSimulation.at("entities").at("ids").at("next").get<uint64_t>();
        const auto restoredNext=restoredSimulation.at("entities").at("ids").at("next").get<uint64_t>();
        const auto oldPlayer=EntityHandle::fromJson(finalCharacter.at("region_session").at("player").at("entity_handle"));
        bool stale=true,retiredExactly=true;
        for(const auto &old:savedSimulation.at("entities").at("entries")) {
            const auto handle=EntityHandle::fromJson(old);stale=stale&&!remapped.valid(handle);
            auto expected=old;expected["live"]=false;
            if(old.at("live").get<bool>()&&handle.generation!=UINT32_MAX)
                expected["generation"]=handle.generation+1;
            bool found=false;
            for(const auto &entry:restoredSimulation.at("entities").at("entries"))
                if(entry.at("id")==old.at("id")){found=true;retiredExactly=retiredExactly&&(entry==expected);break;}
            retiredExactly=retiredExactly&&found;
        }
        const auto active=remapped.active();
        check(stale&&retiredExactly&&!remapped.valid(oldPlayer)&&restored.player.handle!=oldPlayer&&
              remapped.valid(restored.player.handle)&&active.size()==1&&active[0]==restored.player.handle&&
              static_cast<const World &>(restored).resolveActor(oldPlayer)==nullptr&&
              static_cast<const World &>(restored).resolveActor(restored.player.handle)==&restored.player&&
              restored.player.handle.id>=savedNext&&restoredNext>restored.player.handle.id&&
              restored.monsters.empty()&&restoredSimulation.at("entities").at("entries").size()==
                  savedSimulation.at("entities").at("entries").size()+1,
            "Restore exactly retires all saved incarnations, retains allocation history and publishes only one fresh resolvable player handle");
        PendingRewardService recovered;recovered.characterBoundary(restored);
        check(rp.state==progress.state&&learningViews(restored)==normal&&restored.identity()==world.identity()&&
              restored.characterLevel==progress.level()&&restored.experimentalRuntime()->cooldownSnapshot(restored.nowMs())==cd&&
              restored.player.hp==world.player.hp&&restored.player.mp==world.player.mp&&
              (key.jobId!=5||passive(restored)==modifiers)&&recovered.acknowledgeCheckpoint(rp,restored,reloaded,0)&&
              recovered.clearReceipt(rp,session),
            "Real reopened store plus session player restore preserves source identity/level/passive/MP/CD/learning/clear receipt in one epoch");
        const auto finalProgress=rp.state,finalRandom=restored.randomStreams().snapshot();
        check(recovered.prepareAndPublish(rp,restored,catalog)&&rp.state==finalProgress&&
              restored.randomStreams().snapshot()==finalRandom&&!recovered.needsCheckpoint(),
            "Recovered completed receipts cannot re-award XP/SP/gold/drops or redraw Loot");
        samples.push_back({{"key",key.json()},{"cast_cost",cast},{"initial_level",level},{"reward_level",progress.level()},
            {"final_fault",int(point)},{"final_generation",reloaded.generation()},{"learning",normal},{"passive",modifiers}});
        reloaded.close();
    }
    {
        const SkillKey key{1,6};const auto path=directory/"normal-beta-isolation";
        CharacterStore normal(path/"normal",pvf.identity());normal.data=sourceCharacter(1,5);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progress(catalog);
        normal.apply(0,world,progress);world.combat=false;learn(normal,world,progress,key,"beta-boundary-normal1",check);
        check(world.assignLearnedSkillSlot(0,key).ok,"High-generation normal baseline has an actual paid source hotbar");
        justBelowNextLevel(progress,check);
        PendingRewardService reward;reward.characterBoundary(world);
        TownAccessCatalog towns(pvf);const auto home=towns.location(towns.require(1,1));
        capture(normal,world,progress);auto &region=normal.data["characters"][0]["region_session"];
        towns.attachState(region,home,home);region["login_town"]=home.json();
        for(int i=0;i<12;++i) {
            normal.checkpoint();check(reward.acknowledgeCheckpoint(progress,world,normal,0),"Actual normal writer advances before beta fork");
        }
        const auto baseline=learningViews(world),normalProgress=progress.state,normalRandom=world.randomStreams().snapshot();
        const auto previousGeneration=normal.generation();
        BetaSaveBranch branch;branch.fork(normal,path/"beta",{{"run_id","normal-reward-learning-preview"}});
        auto &writer=branch.select(normal);const auto normalBytes=readFile(path/"normal/characters.json");
        const auto normalData=normal.data;
        check(normal.generation()==previousGeneration+1&&writer.generation()==1&&writer.generation()<normal.generation()&&
              !reward.acknowledgeCheckpoint(progress,world,writer,0)&&
              reward.switchCheckpointWriter(progress,world,writer,0)&&reward.durableGeneration()==1,
            "Real high-generation normal fork hands over explicitly to independent beta generation one");
        DebugOverrides debug;debug.enabled=true;debug.level=99;world.applyDebugOverrides(debug,progress.level());
        const auto quote=world.quoteTestSkillLearning(key);
        check(quote.accepted()&&quote.targetLevel==2&&
              world.learnTestSkill({"beta-boundary-test2",key,quote.revision,quote.targetLevel}).ok&&
              world.assignLearnedSkillSlot(1,key).ok&&world.skillState().snapshot(world.nowMs())==baseline.at("ledger")&&
              world.experimentalRuntime()->configuration().binding(key)->level==2,
            "Beta test learning and independent slot project level2 without granting normal level2");
        const auto test=world.testSkillConfigurationSnapshot(),overlay=world.skillTestOverlay().snapshot();
        check(world.setExperimentalSkillPreviewEnabled(true).ok,"Actual explicit preview starts inside the isolated beta branch");
        auto &configuration=world.experimentalRuntime()->configuration();const auto &plan=world.experimentalRuntime()->plan();
        configuration.configureSourceSkillAction(key,10,plan);configuration.assignSlot(2,key,plan);
        const auto manual=world.manualSkillPreviewSnapshot();checkpoint(writer,reward,world,progress,check);
        check(writer.data.at("characters")[0].at("experimental_skill_execution_mode")=="manual_preview"&&
              writer.data.at("characters")[0].at("experimental_manual_preview_configuration")==manual&&
              world.normalSkillConfigurationSnapshot()==baseline.at("normal")&&world.testSkillConfigurationSnapshot()==test&&
              world.skillState().snapshot(world.nowMs())==baseline.at("ledger")&&normal.data==normalData&&readFile(path/"normal/characters.json")==normalBytes,
            "Manual level10/slots are saved by beta writer while normal bytes/data/ledger/config remain exact");
        check(world.setExperimentalSkillPreviewEnabled(false).ok&&world.experimentalRuntime()->configuration().binding(key)->level==2,
            "Leaving manual preview returns to actual test-learned level2 instead of raw level10");
        const auto cast=castOnce(world,key,2,1,check);RegionSession session;
        diagnosticBossClear(world,session,catalog,13001,check);
        check(reward.observe(progress,world,session,session.save(world,"dungeon")),"Beta captures actual source reward intent after test cast");
        checkpoint(writer,reward,world,progress,check,&session);const int level=progress.level();
        check(reward.prepareAndPublish(progress,world,catalog)&&progress.level()>level&&world.characterLevel==99&&
              world.normalCharacterLevel()==progress.level()&&world.skillState().snapshot(world.nowMs())==baseline.at("ledger")&&
              world.normalSkillConfigurationSnapshot()==baseline.at("normal")&&world.testSkillConfigurationSnapshot()==test&&
              world.manualSkillPreviewSnapshot()==manual&&world.skillTestOverlay().snapshot()==overlay,
            "Beta reward levels its progression through applyEquipment while preserving override99 and separate learned/manual views");
        checkpoint(writer,reward,world,progress,check,&session);
        check(!reward.blocked(progress)&&reward.clearReceipt(progress,session)&&normal.data==normalData&&
              readFile(path/"normal/characters.json")==normalBytes,
            "Final beta reward/XP/drop/RNG generation never writes the normal branch");
        check(!reward.releaseCheckpointWriter(progress,normal,0)&&reward.releaseCheckpointWriter(progress,writer,0),
            "Only the bound clean beta writer can release after learning/preview/reward");
        const auto betaGeneration=writer.generation();branch.close();
        CharacterEntryService entries(pvf,assets,catalog,towns);
        auto entry=entries.prepare(world,normal.data.at("characters")[0].at("region_session"));
        normal.apply(0,world,progress);reward.characterBoundary(world);session=RegionSession{};
        Scene scene;publishCharacterEntry(world,scene,std::move(entry));
        check(progress.state==normalProgress&&world.randomStreams().snapshot()==normalRandom&&learningViews(world)==baseline&&
              !world.debugOverrides().enabled&&!world.experimentalSkillPreviewEnabled()&&!world.combat&&world.monsters.empty()&&
              world.characterLevel==5&&world.normalCharacterLevel()==5&&world.skillState().learnedLevel(key)==1&&
              world.experimentalRuntime()->configuration().binding(key)->level==1&&
              normal.data==normalData&&readFile(path/"normal/characters.json")==normalBytes,
            "Actual normal apply and source Seria entry restore normal SP/XP/RNG/slots/ledger without beta level2 or manual10 contamination");
        capture(normal,world,progress);auto &returned=normal.data["characters"][0]["region_session"];
        towns.attachState(returned,home,home);returned["login_town"]=home.json();normal.checkpoint();
        check(reward.acknowledgeCheckpoint(progress,world,normal,0)&&reward.durableGeneration()==normal.generation()&&
              !normal.data.contains("beta_branch"),"Explicit normal rebind commits only the restored normal world after beta closes");
        samples.push_back({{"case","normal-beta-test-preview-reward-return"},{"cast_cost",cast},
            {"normal_generation",normal.generation()},{"beta_generation",betaGeneration},{"baseline_learning",baseline},
            {"beta_test",test},{"beta_overlay",overlay},{"beta_manual",manual}});normal.close();
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"save_directory",directory.u8string()},
        {"scope","Real source-v1 World/normal paid learning/GSD/SkillKey slots/runtime costs/PendingRewardService applyEquipment/final durable retry/reopened store/explicit beta handover and source Seria restore; diagnostic HP1 kills are fixture-only, no complete main-loop playthrough or original-client parity claim"}};
}
} // namespace dnf
