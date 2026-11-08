// Harness adapter only; checks copied unchanged from the frozen gsd_advancement_probe.cpp.
#include "dnf/character_advancement.hpp"
#include "dnf/storage.hpp"
#include "dnf/scene.hpp"
#include "dnf/session.hpp"
#include "dnf/entry.hpp"
#include <chrono>
#include <stdexcept>
using namespace dnf;
namespace {
Json rootFor(int job,int level) {
    const std::array<std::string,9> storedClasses={"swordman","fighter","gunner","mage","priest","atgunner","thief","atfighter","atmage"};
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)},{"future_root","preserve"}};
    root["characters"][0]={{"name","GSD private probe"},{"class",storedClasses.at(job)},
        {"identity",CharacterIdentity{job,0,0}.json()},{"level",level},{"weapon",0},{"skill_initialization","source-v1"},
        {"future_character",{{"payload",Json::array({4,2,4})}}}};
    return root;
}
Scene trainerScene(const World &world) {
    Scene scene;MapNpc trainer;trainer.id=world.advancementCatalog().trainerId();
    trainer.source=world.advancementCatalog().trainerPath();trainer.visible=true;
    trainer.x=world.player.x;trainer.y=world.player.y;scene.npcs.push_back(trainer);return scene;
}
Json live(const World &world,const Progression &progression) {
    return {{"identity",world.identity().json()},{"world",world.snapshot()},{"simulation",world.simulationCheckpoint()},
        {"ledger",world.skillState().snapshot(world.nowMs())},{"progression",progression.state}};
}
Json region(const World &world) {
    return {{"schema",3},{"location","town"},{"player",saveActor(world.player,world.nowMs())},
        {"reward_ledger",{{"same-generation","already-granted"}}},{"future_region",Json::array({7,3,7})}};
}
CharacterAdvancementRequest request(const CharacterStore &store,const World &world,const std::string &id,CharacterIdentity target) {
    return {id,world.identity(),target,store.generation(),world.advancementCatalog().trainerId()};
}
}
namespace dnf {
Json runCharacterAdvancementTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool okay,const std::string &name) {
        if(!okay)throw std::runtime_error(name);checks.push_back(name);
    };
    const auto stamp=std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto out=std::filesystem::absolute(std::filesystem::path("cache/character-advancement-tests")/std::to_string(stamp));
    std::filesystem::create_directories(out);
    try {
        CharacterCatalog characters(pvf);CharacterAdvancementCatalog catalog(pvf,characters);
        writeJson(out/"catalog.json",catalog.snapshot());
        check(catalog.options().size()==64,"All 32 registered branches and 32 first awakenings are admitted independently of skill implementation");
        check(catalog.trainerId()==7&&catalog.trainerPath()=="npc/gsd.npc"&&!catalog.isTrainer(1008),"Actual unique GSD registration 7 is used, not the cc_gsd actor");
        for(const auto &[identity,option]:catalog.options()) {
            check(option.requiredLevel==(identity.awakening?50:15),"Exact source level for job "+std::to_string(identity.jobId)+" branch "+std::to_string(identity.growtype)+" stage "+std::to_string(identity.awakening));
            check(!option.sources.empty()&&option.sources.front().memberSha256.size()==64,"Identity reward retains full source reference "+std::to_string(identity.jobId)+":"+std::to_string(identity.growtype)+":"+std::to_string(identity.awakening));
            check(!catalog.supports({identity.jobId,identity.growtype,2}),"An awakening name does not fabricate a second-awakening level");
        }
        check(!catalog.supports({9,1,0})&&!catalog.supports({10,1,0})&&!catalog.supports({6,3,0})&&!catalog.supports({8,3,0}),"Absent source rewards/deferred Creator and future branches remain unavailable");
        RegionCatalog regions(pvf,assets);
        check(regions.npcs.count(catalog.trainerId())&&
            normalize(regions.npcs.at(catalog.trainerId()).path)==catalog.trainerPath(),
            "The real source GSD is available through RegionCatalog and the normal main interaction gate");
        // Current scope uses seven jobs; each actual source identity must save
        // and restore without inventing a skill controller or starter reward.
        for(int job:{0,1,2,3,4,5,8}) {
            const auto dir=out/"saves"/("job"+std::to_string(job));
            CharacterStore store(dir,"gsd-private-probe");store.data=rootFor(job,15);
            World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
            Progression progression(regions);store.apply(0,world,progression);world.combat=false;world.releaseInputs();
            store.capture(0,world,progression);store.checkpoint();
            const auto before=progression.state,ledger=world.skillState().snapshot(world.nowMs()),simulation=world.simulationCheckpoint();
            const auto sourceBudget=world.skillLearning().budget(world.skillState(),15,world.nowMs()).json();
            auto scene=trainerScene(world);const auto req=request(store,world,"advance-job-"+std::to_string(job),{job,1,0});
            CharacterAdvancementTransaction transaction;
            const auto result=transaction.submit(store,0,world,progression,scene,req,region(world));
            if(!result.ok)throw std::runtime_error("Job "+std::to_string(job)+" advancement: "+result.json().dump());
            check(world.identity()==req.target&&!transaction.pending()&&store.receipt(req.requestId).is_object(),"Job "+std::to_string(job)+" commits actual GSD identity durably");
            check(progression.state==before&&world.simulationCheckpoint()==simulation,"Job "+std::to_string(job)+" preserves equipment/inventory/simulation/RNG/handles");
            auto after=world.skillState().snapshot(world.nowMs());after["identity"]=ledger["identity"];
            check(after==ledger&&world.skillLearning().budget(world.skillState(),15,world.nowMs()).json()==sourceBudget,
                "Job "+std::to_string(job)+" preserves learned entries, unknown fields, costs and point history exactly");
            check(store.data.at("characters")[0].at("region_session").at("reward_ledger")==region(world).at("reward_ledger"),"Job "+std::to_string(job)+" retains same-generation reward ledger");
            const auto generation=store.generation();const auto duplicate=transaction.submit(store,0,world,progression,scene,req,region(world));
            check(duplicate.state==CharacterAdvancementState::Replayed&&store.generation()==generation,"Job "+std::to_string(job)+" request replay never repeats a commit or source reward");
            auto collision=req;collision.target.growtype=2;
            check(!transaction.submit(store,0,world,progression,scene,collision,region(world)).ok&&store.generation()==generation,
                "Job "+std::to_string(job)+" duplicate ID with another target is rejected");
            World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression restoredProgress(regions);
            store.apply(0,restored,restoredProgress);
            check(restored.identity()==world.identity()&&restoredProgress.state==progression.state&&
                restored.skillState().snapshot(restored.nowMs())==world.skillState().snapshot(world.nowMs()),"Job "+std::to_string(job)+" advanced identity reloads through real CharacterStore");
            const auto coverage=world.controllerCoverage();bool partial=false;
            for(const auto &entry:coverage)if(entry.at("identity")==req.target.json())
                partial=entry.at("readiness")=="user_advancement_partial"&&!entry.at("execution_complete").get<bool>()&&!entry.at("native_confirmed").get<bool>();
            check(partial,"Job "+std::to_string(job)+" adapter remains explicitly incomplete/native-unverified");
            store.close();
        }
        for(int job:{0,1,2,3,4,5,8}) {
            CharacterStore store(out/"saves"/("awaken-job"+std::to_string(job)),"gsd-private-probe");store.data=rootFor(job,50);
            World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression p(regions);store.apply(0,world,p);
            world.combat=false;world.releaseInputs();store.capture(0,world,p);store.checkpoint();auto scene=trainerScene(world);
            CharacterAdvancementTransaction transaction;const auto req=request(store,world,"awaken-job"+std::to_string(job),{job,1,1});
            const auto before=p.state;const auto result=transaction.submit(store,0,world,p,scene,req,region(world));
            if(!result.ok)throw std::runtime_error("Job "+std::to_string(job)+" first awakening: "+result.json().dump());
            check(world.identity()==req.target&&p.state==before,"Job "+std::to_string(job)+" source50 awakening publishes without tasks/materials or equipment loss");
            World reloaded(pvf,assets,WorldRules::BetaFoundationV1);reloaded.enableExperimentalCharacters();Progression rp(regions);store.apply(0,reloaded,rp);
            check(reloaded.identity()==req.target&&rp.state==p.state,"Job "+std::to_string(job)+" first awakening reloads exact source branch/stage");
            const auto good=store.data;store.data["characters"][0]["level"]=1;store.data["characters"][0]["progression"]["level"]=1;
            const auto current=live(world,p);bool refused=false;
            try{store.apply(0,world,p);}catch(const std::exception &){refused=true;}
            check(refused&&live(world,p)==current,"Job "+std::to_string(job)+" below-source-level saved identity is rejected before live publication");
            store.data=good;store.close();
        }
        const std::vector<SaveFailurePoint> faults={SaveFailurePoint::BeforeWrite,SaveFailurePoint::AfterWrite,
            SaveFailurePoint::AfterFlush,SaveFailurePoint::AfterValidation,SaveFailurePoint::AfterBackup,
            SaveFailurePoint::BeforePublish,SaveFailurePoint::AfterPublish};
        for(size_t index=0;index<faults.size();++index) {
            CharacterStore store(out/"saves"/("fault"+std::to_string(index)),"gsd-private-probe");store.data=rootFor(0,15);
            World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progression(regions);store.apply(0,world,progression);
            world.combat=false;world.releaseInputs();world.randomStreams().stream(RandomDomain::Loot,517).next();
            const SkillLearningRequest buy{"paid-upper-2",{0,46},0,2};
            const auto purchase=world.skillLearning().prepare(world.skillState(),15,world.runtimeSkillPolicy(buy.key),buy,world.nowMs());
            check(purchase.ok,"Real source skill purchase prepared before identity fault "+std::to_string(index));world.publishSkillLedger(purchase.state);
            world.skillState().startCooldown({0,46},world.nowMs(),1700);
            world.player.hp-=3;world.player.mp-=2;store.capture(0,world,progression);store.checkpoint();
            const auto original=live(world,progression);const auto generation=store.generation();const auto hp=world.player.hp;auto scene=trainerScene(world);
            const auto req=request(store,world,"fault-identity-"+std::to_string(index),{0,1,0});CharacterAdvancementTransaction transaction;
            store.setFailureInjector([point=faults[index]](SaveFailurePoint actual){if(actual==point)throw std::runtime_error("injected GSD save failure");});
            const auto result=transaction.submit(store,0,world,progression,scene,req,region(world));
            check(result.state==CharacterAdvancementState::Pending&&transaction.pending()&&store.hasPendingCommit()&&
                live(world,progression)==original&&store.generation()==generation,"Fault "+std::to_string(index)+" keeps old live state/MP/CD/costs/RNG while exact target waits");
            store.setFailureInjector({});const auto recovered=transaction.retry(store,world);
            if(!recovered.ok)throw std::runtime_error("Retry: "+recovered.json().dump());
            check(world.identity()==req.target&&store.generation()==generation+1&&!transaction.pending()&&!store.hasPendingCommit(),
                "Fault "+std::to_string(index)+" retry commits exactly one durable generation");
            check(world.skillState().learnedLevel({0,46})==2&&world.skillState().remainingCooldown({0,46},world.nowMs())==1700&&
                world.player.hp<=hp,"Fault "+std::to_string(index)+" preserves paid learned level, remaining CD and HP deficit");
            store.close();
        }
        {
            CharacterStore store(out/"saves/awakening-switch","gsd-private-probe");store.data=rootFor(0,49);
            World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression p(regions);store.apply(0,world,p);
            world.combat=false;world.releaseInputs();store.capture(0,world,p);store.checkpoint();auto scene=trainerScene(world);
            CharacterAdvancementTransaction transaction;
            auto advance=request(store,world,"switch-advance",{0,1,0});
            auto result=transaction.submit(store,0,world,p,scene,advance,region(world));
            if(!result.ok)throw std::runtime_error("Lv49 branch: "+result.json().dump());
            auto awaken=request(store,world,"before-awaken-level",{0,1,1});
            check(!transaction.submit(store,0,world,p,scene,awaken,region(world)).ok,"Lv49 advanced identity cannot awaken before source50");
            // Pay for an actually implemented normal skill; source-exclusive
            // Swordman passives are not bound by the current candidate. Keep
            // that fact explicit instead of inventing a runtime consumer.
            const SkillLearningRequest paid{"real-upper-purchase",{0,46},0,2};
            const auto bought=world.skillLearning().prepare(world.skillState(),49,world.runtimeSkillPolicy(paid.key),paid,world.nowMs());
            check(bought.ok,"Actual implemented normal skill purchase records real SP cost before branch switch");
            world.publishSkillLedger(bought.state);
            std::optional<SkillKey> branchPassive;
            for(const auto &entry:world.characterSource().skills.entries)
                if(std::filesystem::u8path(entry.path).stem()=="lightswordmastery")branchPassive=SkillKey{0,entry.id};
            check(bool(branchPassive)&&!world.runtimeSkillPolicy(*branchPassive).implemented,
                "Source-exclusive lightsword mastery remains explicitly unimplemented; its source presence grants no runtime consumer");
            // Explicit legacy-import fixture exercises preservation of an old
            // learned but unsupported source skill, as permitted by save
            // migration. It is not a new player purchase or source grant.
            auto imported=world.skillState().snapshot(world.nowMs());
            imported["skills"].push_back({{"key",branchPassive->json()},{"level",1},{"remaining_cooldown_ms",0}});
            imported["learning"]["grants"].push_back({{"key",branchPassive->json()},{"level",1},{"kind","legacy_grant"},
                {"source",{{"classification","explicit-test-fixture"}}}});
            CharacterSkillState importedState(world.identity());importedState.restore(imported,world.nowMs());
            world.skillLearning().budget(importedState,49,world.nowMs());world.publishSkillLedger(importedState);
            check(world.skillUseEligibility(*branchPassive).allowed(),"Legacy source-exclusive learned fixture has current branch1 source eligibility");
            const auto oldLedger=world.skillState().snapshot(world.nowMs()),oldProgress=p.state;
            const auto oldBudget=world.skillLearning().budget(world.skillState(),49,world.nowMs()).json();
            auto switchBranch=request(store,world,"switch-branch",{0,2,0});
            result=transaction.submit(store,0,world,p,scene,switchBranch,region(world));
            if(!result.ok)throw std::runtime_error("Branch switch: "+result.json().dump());
            check(world.skillState().learnedLevel(*branchPassive)>0&&!world.skillUseEligibility(*branchPassive).allowed(),
                "Purchased old-branch skill remains in ledger but loses its use qualification immediately");
            check(!world.runtimeSkillPolicy(*branchPassive).implemented,"Changing identity never enables an unsupported passive consumer");
            auto newLedger=world.skillState().snapshot(world.nowMs());newLedger["identity"]=oldLedger.at("identity");
            check(newLedger==oldLedger&&p.state==oldProgress&&world.skillLearning().budget(world.skillState(),49,world.nowMs()).json()==oldBudget,
                "Branch switch preserves actual purchase receipts, cost history, learned level and equipped instances");
            p.addExperience(p.experienceToNextLevel());world.applyEquipment(p);world.releaseInputs();
            check(p.level()==50&&world.normalCharacterLevel()==50,"Awakening uses real normal progression level50");
            const auto beforeAwaken=world.skillState().snapshot(world.nowMs());
            auto validAwaken=request(store,world,"source50-awaken",{0,2,1});
            result=transaction.submit(store,0,world,p,scene,validAwaken,region(world));
            if(!result.ok)throw std::runtime_error("Lv50 awakening: "+result.json().dump());
            check(world.identity()==CharacterIdentity{0,2,1}&&store.data.at("characters")[0].at("identity")==world.identity().json(),
                "At actual source50 GSD publishes and durably records exact first-awakened branch identity");
            World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression rp(regions);store.apply(0,restored,rp);
            check(restored.identity()==world.identity()&&rp.level()==50&&restored.skillState().snapshot(restored.nowMs())==world.skillState().snapshot(world.nowMs()),
                "First awakening restores exact identity and preserved normal learning history through real store");
            store.close();
        }
        {
            CharacterStore store(out/"saves/gates","gsd-private-probe");store.data=rootFor(0,14);
            World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression p(regions);store.apply(0,world,p);
            world.combat=false;world.releaseInputs();store.capture(0,world,p);store.checkpoint();auto scene=trainerScene(world);
            CharacterAdvancementTransaction transaction;const auto req=request(store,world,"level-floor",{0,1,0});const auto before=live(world,p);
            check(!transaction.submit(store,0,world,p,scene,req,region(world)).ok&&live(world,p)==before,"Level14 cannot bypass actual source15 advancement gate");
            auto awakening=req;awakening.requestId="awakening-floor";awakening.target={0,1,1};
            check(!transaction.submit(store,0,world,p,scene,awakening,region(world)).ok,"Level14 cannot bypass actual source50 first-awakening gate");
            auto unknown=req;unknown.requestId="unknown-stage";unknown.target={0,1,2};
            check(!transaction.submit(store,0,world,p,scene,unknown,region(world)).ok,"Unknown second-awakening level remains unavailable");
            scene.npcs[0].x+=181;
            check(!transaction.submit(store,0,world,p,scene,req,region(world)).ok,"Remote GSD menu/forged command cannot bypass NPC proximity");
            scene.npcs[0].x-=181;scene.npcs[0].source="npc/cc_gsd.npc";
            check(!transaction.submit(store,0,world,p,scene,req,region(world)).ok,"Matching numeric ID with a foreign NPC source is rejected");
            store.close();
        }
        Json result={{"status","pass"},{"count",checks.size()},{"checks",checks},
            {"scope","source catalog + real World/CharacterStore transactions; frontend and original-client comparison pending"},
            {"fixture_directory",out.u8string()}};
        writeJson(out/"gsd-tests.json",result);return result;
    }catch(const std::exception &e){
        writeJson(out/"gsd-tests.json",{{"status","failed"},{"count",checks.size()},{"checks",checks},{"error",e.what()}});throw;
    }
}
} // namespace dnf
