#include "dnf/skill_learning_transaction.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/character_attack.hpp"
#include "dnf/scene.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr SkillKey upper{4,1},upperTp{4,210},devilGauge{4,123};
Json upperRoot(int level) {
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    root["characters"][0]={{"name","PriestUpperConsumer"},{"class","priest"},{"identity",CharacterIdentity{4,0,0}.json()},
        {"level",level},{"weapon",0},{"skill_initialization","source-v1"}};return root;
}
void upperRest(World &w) {
    w.releaseInputs();w.changeScene();w.monsters.clear();w.events.clear();w.idle();w.combat=false;
    auto &a=w.player;a.dead=false;a.life=ActorLife::Alive;a.hp=a.maxHp;a.recovery=0;a.stunUntil=0;a.hitStopTicks=0;a.hitStopped=false;
    a.x=a.px=700;a.y=a.py=344;a.z=a.pz=a.vx=a.vy=a.vz=0;a.dir=1;
}
void upperArena(World &w) {
    w.combat=true;w.freezeAi=true;w.freeCd=false;w.mapWidth=3000;w.walkRects={{0,185,3000,600}};w.blockedRects.clear();
    w.player.mp=w.player.maxMp;
}
void upperInput(World &w,int key,bool down){w.enqueue({w.simulationNanoseconds(),key,down});}
void upperCast(World &w){upperInput(w,20,true);w.advanceSingleTick();upperInput(w,20,false);}
void upperTicks(World &w,int n){while(n-->0)w.advanceSingleTick();}
void upperCooldown(World &w) {
    while(w.experimentalRuntime()->remainingCooldown(upper,w.nowMs())>0)w.advanceSingleTick();w.releaseInputs();
}
size_t upperAudio(const World &w) {
    return size_t(std::count_if(w.events.begin(),w.events.end(),[](const Event &e){return e.kind=="sound"&&e.name=="PR_ANTIAIR";}));
}
Scene upperTrainer(const World &w) {
    Scene scene;MapNpc npc;npc.id=w.advancementCatalog().trainerId();npc.source=w.advancementCatalog().trainerPath();
    npc.visible=true;npc.x=w.player.x;npc.y=w.player.y;scene.npcs.push_back(npc);return scene;
}
Json upperLive(const World &w,const Progression &p) {
    return {{"world",w.snapshot()},{"simulation",w.simulationCheckpoint()},{"ledger",w.skillState().snapshot(w.nowMs())},
        {"configuration",w.experimentalRuntime()->configuration().snapshot()},{"overlay",w.skillTestOverlay().snapshot()},
        {"cooldowns",w.experimentalRuntime()->cooldownSnapshot(w.nowMs())},{"progression",p.state}};
}
}

// Parent owns compilation/execution and full closure verification. This suite
// invokes real normal input, durable learning, EQU and World damage consumers.
Json runPriestUpperRuntimeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message){checks.push_back({{"passed",pass},{"message",message}});
        if(!pass){writeJson("priest-upper-failure.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}};
    RegionCatalog regions(pvf,assets);
    const auto root=std::filesystem::absolute(std::filesystem::path("cache/priest-upper-tests")/
        std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    {
        CharacterStore store(root/"source-level1","priest-upper-test");store.data=upperRoot(1);
        World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);upperRest(w);
        const auto quote=w.quoteSkillLearning(upper,1);
        check(w.skillState().learnedLevel(upper)==1&&w.skillUseEligibility(upper).allowed()&&
            w.experimentalRuntime()->configuration().binding(upper)->level==1&&w.skillLearningBudget(false,1).spentSp==0&&
            quote.gate==SkillLearningGate::CharacterLevel&&quote.requiredCharacterLevel==4,
            "Actual Priest source-v1 creation grants usable free Upper1 at Lv1; buying Upper2 still needs source character4");store.close();
    }
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        CharacterStore store(root/ani_clock::policyName(clock),"priest-upper-test");store.data=upperRoot(4);
        World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);
        upperRest(w);w.configureAnimationClock(clock);auto &r=*w.experimentalRuntime();const auto &plan=r.plan();const auto &d=plan.sourceSkillActions.at(upper);
        const auto body=assets.animation(d.motion.memberPath);
        check(!w.experimentalSkillPreviewEnabled()&&!w.debugOverrides().enabled&&w.runtimeSkillPolicy(upper).implemented&&
            !w.runtimeSkillPolicy(upperTp).implemented&&d.kind==SourceSkillActionKind::BodyAttack&&d.state==20&&d.motionSlot==1&&d.attackSlot==2&&
            d.requiresEquippedAttackVolume&&d.sourceFrameSuperArmor&&d.actorAttackSpeedOnly&&d.speedColumn==-1&&d.bodyLayerBirthFrame==2,
            "Exact own Priest source resolves initial body state20/motion1/ATK2, real equipment and explicit absent speed-column policy");
        check(d.registration.memberPath.empty()&&d.callback.memberPath.empty()&&d.objectId==-1&&d.bodyLayers.size()==2&&body->duration==780&&
            std::none_of(body->frames.begin(),body->frames.end(),[](const AniFrame &f){return std::any_of(f.boxes.begin(),f.boxes.end(),[](const Box &b){return b.type==15;});}),
            "Upper never fabricates a NUT controller/PO or substitutes its late hurtboxes for actual weapon attacks");
        for(int level:{1,10}) {
            const auto values=plan.skills.at(upper).data->values("[level info]");const auto o=evaluateSourceSkillAction(d,*plan.skills.at(upper).data,level);
            check(o.damage.percent==float(*skillLevelValue(values,level,0))&&o.damage.independentPercent==float(*skillLevelValue(values,level,2))&&
                o.damage.fixedDamage==0&&o.bodyLift&&*o.bodyLift==*skillLevelValue(values,level,1)&&o.attackSpeedBonusPermille==0,
                "Actual Upper operands use percent0/independent2/lift1, preserving zero skill speed bonus at level "+std::to_string(level));
        }
        check(w.assignLearnedSkillSlot(0,upper).ok,"Normally granted Upper1 is available through actual learned hotbar assignment");
        store.capture(0,w,p);store.checkpoint();const auto quote=w.quoteSkillLearning(upper,4);
        check(quote.accepted()&&quote.targetLevel==2&&quote.cost==20&&quote.currency=="SP"&&quote.requiredCharacterLevel==4&&quote.purchaseMaximum==10,
            "Normal Upper2 quote consumes real char4/SP20/purchase10, separate from all-means maximum50");
        SkillLearningTransaction purchase;const SkillLearningRequest buy{"upper-normal2",upper,quote.revision,2};
        const auto before=upperLive(w,p);const auto generation=store.generation();
        store.setFailureInjector([](SaveFailurePoint point){if(point==SaveFailurePoint::AfterPublish)throw std::runtime_error("upper durable publication fault");});
        check(!purchase.submit(store,0,w,p,buy,Json::object()).ok&&purchase.pending()&&upperLive(w,p)==before,
            "Real durable publication fault retains normal Upper ledger, slots, MP/CD, RNG and configuration privately");
        store.setFailureInjector({});check(purchase.retry(store,w).ok&&store.generation()==generation+1&&w.skillState().learnedLevel(upper)==2&&
            r.configuration().binding(upper)->level==2&&w.skillLearningBudget(false,4).spentSp==20,
            "Retried durable purchase publishes one Upper2 and exactly source SP20");
        const auto normal=w.skillState().snapshot(w.nowMs()),budget=w.skillLearningBudget(false,4).json();
        check(purchase.submit(store,0,w,p,buy,Json::object()).state==SkillLearningTransactionState::Replayed&&w.skillLearningBudget(false,4).json()==budget,
            "Replay cannot spend Upper SP or grant the same purchase twice");
        upperArena(w);const auto mp=w.player.mp;upperCast(w);const auto cost=r.snapshotDiagnostics().at("last_cost");
        check(r.attacking()&&mp-w.player.mp==cost.at("mp").at("value").get<int>()&&upperAudio(w)==1&&
            r.remainingCooldown(upper,w.nowMs())==int64_t(std::ceil(cost.at("cooldown_ms").at("value").get<double>()))&&
            w.player.skillAnimationLayers.empty(),"Normal accepted empty cast pays one actual MP/CD and source voice, without prematurely starting Upper effects");
        bool sawLayers=false,sawRetirementBeforeBody=false,sawVolume=false;uint64_t firstEffectAge=0;
        for(int tick=0;tick<100;++tick) {
            for(const auto &volume:w.attackVolumes)if(volume.skillId==1&&volume.sourceModifiers) {
                sawVolume=true;check(volume.sourceModifiers->percent==float(*skillLevelValue(plan.skills.at(upper).data->values("[level info]"),2,0)),
                    "Actual World equipment attack volume receives the normally paid Upper2 damage operands");
            }
            if(!w.player.skillAnimationLayers.empty()) {
                check(w.player.animationClock&&w.player.animationClock->frame>=2&&w.player.skillAnimationLayers.size()==2,
                    "Both effects begin only after actual crossed source attack frame2");
                check(bool(w.player.skillAnimationLayers.front().instanceClock),"Actual timed layer carries its own immutable presentation clock");
                if(!sawLayers) {
                    firstEffectAge=w.player.skillAnimationLayers.front().instanceClock->elapsedMs;
                    check(w.player.animationClock->frame==size_t(d.bodyLayerBirthFrame)&&
                        firstEffectAge==w.player.animationClock->elapsedMs-w.player.animationClock->frameStartMs,
                        "First actual World effect age equals precise crossed-frame deadline overshoot, including a replaced current-frame sample");
                }
                sawLayers=true;
                for(const auto &layer:w.player.skillAnimationLayers)check(layer.instanceClock&&
                    layer.instanceClock->policy==ani_clock::ClockPolicy::SourceDelay100&&layer.instanceClock->ratePercent==100&&
                    layer.instanceClock->elapsedMs<240&&!layer.instanceClock->ended,
                    "Runtime-owned Upper visual preserves source rate100 and retires instead of clamping its last frame");
            }else if(sawLayers&&r.attacking())sawRetirementBeforeBody=true;
            w.advanceSingleTick();
        }
        check(sawLayers&&firstEffectAge<17&&sawRetirementBeforeBody&&sawVolume&&!r.attacking()&&w.player.skillAnimationLayers.empty()&&upperAudio(w)==1&&
            w.skillState().snapshot(w.nowMs())==normal,"Empty normal cast runs equipment collision and timed effects, retires effects before body780 ends, and preserves normal ledger");
        const auto cdMp=w.player.mp;upperCast(w);check(!r.attacking()&&w.player.mp==cdMp&&upperAudio(w)==1,"Real remaining cooldown rejects repeat fee and source voice");
        upperRest(w);upperCooldown(w);upperArena(w);w.player.mp=0;upperCast(w);
        check(!r.attacking()&&r.remainingCooldown(upper,w.nowMs())==0&&upperAudio(w)==0,"Insufficient MP cannot create body, effects, voice or cooldown");
        upperRest(w);upperCooldown(w);upperArena(w);
        const auto composed=readCharacterAttackMotion(assets,w.characterAppearance(),d.motion.memberPath);
        const auto contact=composed.boxesAt(size_t(d.bodyLayerBirthFrame));check(!contact.empty(),"Default real EQU/LAY contains a first attack volume");
        const auto &box=contact.front();Actor target;target.id=1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";target.dir=-1;
        target.x=target.px=w.player.x+box.x+box.w*.5;target.y=target.py=w.player.y+box.y+box.h*.5;
        w.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");target.hp=target.maxHp=100000000;
        w.monsters.push_back(std::move(target));w.synchronizeEntityHandles();w.randomStreams()=RandomStreams(67);upperCast(w);
        bool ownReaction=false,lift=false;
        for(int tick=0;tick<110;++tick){ownReaction|=w.monsters[0].animationPath.rfind("monster/goblin/",0)==0&&
            (w.monsters[0].animation=="damage1"||w.monsters[0].animation=="damage2"||w.monsters[0].animation=="down");
            lift|=w.monsters[0].vz>0;w.advanceSingleTick();}
        const auto contacts=std::count_if(w.events.begin(),w.events.end(),[](const Event &e){return e.kind=="hit"&&e.name=="experimental_source_skill";});
        check(contacts==1&&w.monsters[0].hp<100000000&&ownReaction&&lift,
            "Actual multi-frame weapon boxes deduplicate one monster and consume unified damage plus own MOB reaction ANI and SKL350 lift");
        evidence.push_back({{"clock",ani_clock::policyName(clock)},{"descriptor",d.snapshot()},{"quote",quote.json()},{"cost",cost},{"damage",w.statReport().at("last_damage")}});
        upperRest(w);store.capture(0,w,p);store.checkpoint();const auto cooldown=r.cooldownSnapshot(w.nowMs()),random=w.randomStreams().snapshot();
        World loaded(pvf,assets,WorldRules::BetaFoundationV1);loaded.enableExperimentalCharacters();Progression lp(regions);store.apply(0,loaded,lp);
        check(!loaded.experimentalSkillPreviewEnabled()&&loaded.skillState().snapshot(loaded.nowMs())==normal&&
            loaded.experimentalRuntime()->configuration().binding(upper)->level==2&&
            loaded.experimentalRuntime()->configuration().slots()[0]==std::optional<SkillKey>(upper)&&
            loaded.experimentalRuntime()->cooldownSnapshot(loaded.nowMs())==cooldown&&loaded.randomStreams().snapshot()==random,
            "Same-generation real CharacterStore reload preserves Upper2 purchase, source slot, MP/CD authority and random streams");
        upperRest(loaded);upperCooldown(loaded);check(loaded.assignLearnedSkillSlot(0,std::nullopt).ok,"Default Z test clears explicit slot");
        upperArena(loaded);const auto zMp=loaded.player.mp;
        upperInput(loaded,4,true);loaded.advanceSingleTick();upperInput(loaded,4,false);upperInput(loaded,6,true);loaded.advanceSingleTick();upperInput(loaded,6,false);
        check(loaded.experimentalRuntime()->attacking()&&loaded.player.mp==zMp&&upperAudio(loaded)==0,
            "Own source default Z buffers during a basic action and cannot charge or force an early cancel");
        bool continued=false;for(int n=0;n<240&&!continued;++n){loaded.advanceSingleTick();continued=loaded.player.animationPath==d.motion.memberPath;}
        check(continued&&loaded.player.mp<zMp&&upperAudio(loaded)==1,"Buffered learned Z starts Upper immediately at completed action boundary with one cost and voice");
        upperTicks(loaded,120);upperRest(loaded);const auto normalAgain=loaded.skillState().snapshot(loaded.nowMs()),normalConfig=loaded.normalSkillConfigurationSnapshot();
        DebugOverrides debug;debug.enabled=true;debug.level=99;loaded.applyDebugOverrides(debug,4);
        const auto testQuote=loaded.quoteTestSkillLearning(upper);
        check(testQuote.accepted()&&loaded.learnTestSkill({"upper-test3",upper,testQuote.revision,3}).ok&&
            loaded.experimentalRuntime()->configuration().binding(upper)->level==3,"Actual isolated test learning projects its own Upper3");
        check(loaded.setExperimentalSkillPreviewEnabled(true).ok,"Manual Upper preview remains explicit");
        loaded.experimentalRuntime()->configuration().configureSourceSkillAction(upper,10,loaded.experimentalRuntime()->plan());
        check(loaded.setExperimentalSkillPreviewEnabled(false).ok&&loaded.experimentalRuntime()->configuration().binding(upper)->level==3,
            "Leaving manual Upper10 restores test-effective Upper3");loaded.applyDebugOverrides({},4);
        check(loaded.skillState().snapshot(loaded.nowMs())==normalAgain&&loaded.normalSkillConfigurationSnapshot()==normalConfig&&
            loaded.experimentalRuntime()->configuration().binding(upper)->level==2,"Leaving test restores paid normal Upper2 and exact SP/slot ledger");
        check(loaded.assignLearnedSkillSlot(0,upper).ok,"Fault and cleanup cases restore the actual normal hotbar slot after independent default Z test");
        upperRest(loaded);upperCooldown(loaded);upperArena(loaded);
        auto &appearance=const_cast<CharacterAppearance &>(loaded.characterAppearance());auto removed=appearance.parts.extract("[weapon]");
        const auto failMp=loaded.player.mp;const auto failRandom=loaded.randomStreams().snapshot();upperCast(loaded);
        check(!removed.empty()&&!loaded.experimentalRuntime()->attacking()&&loaded.player.mp==failMp&&upperAudio(loaded)==0&&
            loaded.experimentalRuntime()->remainingCooldown(upper,loaded.nowMs())==0&&loaded.randomStreams().snapshot()==failRandom,
            "Missing actual equipped type15 rejects MP/CD, voice and action before publication; no hurtbox fallback");appearance.parts.insert(std::move(removed));
        check(loaded.experimentalDiagnostics().at("world").back().at("code")=="experimental_attack_source_preflight_rejected",
            "Missing-weapon test reaches actual normal source preflight rather than an unassigned-key no-op");
        for(const std::string fault:{"missing_visual","wrong_audio","wrong_equipped_birth","malformed_response"}) {
            upperRest(loaded);upperCooldown(loaded);upperArena(loaded);auto changed=std::make_shared<ExperimentalCharacterPlan>(loaded.experimentalRuntime()->plan());
            auto &descriptor=changed->sourceSkillActions.at(upper);
            if(fault=="missing_visual")descriptor.bodyLayers.front().source.memberPath="missing/priest-upper-test.ani";
            else if(fault=="wrong_audio")descriptor.castSound="__MISSING_UPPER_VOICE";
            else if(fault=="wrong_equipped_birth")++descriptor.bodyLayerBirthFrame;
            else {
                size_t injected=0;
                for(auto &field:descriptor.attackDefinition.source.fields)if(normalize(field.tag)=="[push aside]") {
                    check(field.values==Json::array({30}),"Malformed-response fixture starts from the actual Upper push30 source field");
                    field.values=Json::array({"__UPPER_TEST_NOT_A_NUMBER"});++injected;
                }
                check(injected==1,"Malformed-response fixture corrupts exactly one existing numeric source field, never a missing optional sound");
            }
            ExperimentalCharacterRuntime injected(changed);injected.setAnimationClockPolicy(clock);
            injected.configuration().configureSourceSkillAction(upper,2,*changed);injected.configuration().assignSlot(0,upper,*changed);
            const auto mp=loaded.player.mp;const auto random=loaded.randomStreams().snapshot();auto ids=loaded.idSources().snapshot();ids.erase("requests");
            CharacterActionRequest press;press.inputKey=20;press.inputDown=true;injected.request(press);
            ExperimentalWorldAdapter adapter(loaded);adapter.advance(injected,uint64_t(loaded.tick)+1);
            auto afterIds=loaded.idSources().snapshot();afterIds.erase("requests");
            check(!injected.attacking()&&loaded.player.mp==mp&&upperAudio(loaded)==0&&injected.remainingCooldown(upper,loaded.nowMs())==0&&
                loaded.player.skillAnimationLayers.empty()&&loaded.randomStreams().snapshot()==random&&ids==afterIds&&
                loaded.experimentalDiagnostics().at("world").back().at("code")=="experimental_attack_source_preflight_rejected",
                "Actual normal source preflight retains MP/CD, IDs, RNG, audio and effects after injected "+fault);
            if(fault=="malformed_response")check(loaded.experimentalDiagnostics().at("world").back().at("message")=="Invalid experimental ATK response number",
                "Malformed-response fixture reaches the actual numeric response validator before resource publication");
        }
        for(const std::string reason:{"cancel","scene","death","blocked"}) {
            upperRest(loaded);upperCooldown(loaded);upperArena(loaded);upperCast(loaded);
            for(int n=0;n<100&&loaded.player.skillAnimationLayers.empty();++n)loaded.advanceSingleTick();
            check(loaded.experimentalRuntime()->attacking()&&!loaded.player.skillAnimationLayers.empty(),"Cleanup starts with an actual live timed Upper effect");
            if(reason=="cancel")loaded.idle();else if(reason=="scene")loaded.changeScene();
            else if(reason=="blocked")loaded.player.stunUntil=loaded.nowMs()+1000;else {loaded.player.dead=true;loaded.player.life=ActorLife::Dying;}
            loaded.advanceSingleTick();check(!loaded.experimentalRuntime()->attacking()&&!loaded.armor()&&loaded.player.skillAnimationLayers.empty()&&
                loaded.experimentalRuntime()->snapshotDiagnostics().at("source_body_actions")==0,"Action and delayed effect ownership retire together on "+reason);
        }
        store.close();

        // Pure runtime still exercises real crossed-frame/event production;
        // World tests above bind it to normally learned resource publication.
        const Field *fixtureWeapons=nullptr;
        for(const auto &field:plan.characterDefinition.settings.script.fields)
            if(field.tag=="[key value index]"&&!field.values.empty()&&field.values[0]=="defaultWeaponBySubType")fixtureWeapons=&field;
        check(fixtureWeapons&&fixtureWeapons->values.size()>=4&&fixtureWeapons->values[2]==0&&fixtureWeapons->values[3]==35000,
            "Isolated clock fixture uses the real priest.etc subtype0 default cross registration");
        const auto fixtureWeapon=CharacterCatalog(pvf).equipment(fixtureWeapons->values[3].get<int>());
        const auto fixtureSubtype=fixtureWeapon.script.values("[sub type]");
        check(fixtureSubtype==Json::array({0}),"Isolated clock fixture obtains raw subtype0 from the actual default cross EQU");
        const auto fixtureCost=evaluateCharacterSkillCosts(*plan.skills.at(upper).data,1,plan.characterDefinition,
            fixtureSubtype[0].get<int>(),false,{}, {},inferred1031SkillCostAbsencePolicy());
        check(fixtureCost.consumeMp().has_value()&&fixtureCost.cooldownMs().has_value(),
            "Isolated clock fixture has valid real weapon-adjusted source MP and cooldown before timing assertions");
        const auto shared=std::make_shared<ExperimentalCharacterPlan>(plan);ExperimentalCharacterRuntime isolated(shared);isolated.setAnimationClockPolicy(clock);
        isolated.configuration().configureSourceSkillAction(upper,1,*shared);isolated.configuration().assignSlot(0,upper,*shared);
        ExperimentalActorState actor;actor.mp=10000;actor.attackPerMille=1700;actor.weaponSubtype=fixtureSubtype[0].get<int>();
        CharacterActionRequest request;request.inputKey=20;request.inputDown=true;isolated.request(request);
        ExperimentalTickResult out;uint64_t tick=0;size_t shakes=0;
        for(;tick<100;++tick){out=isolated.advance(tick+1,actor,[](double,double){return true;});actor=out.actor;shakes+=out.sourceCameraShakes.size();if(!out.skillAnimationLayers.empty())break;}
        check(isolated.attacking()&&isolated.snapshotDiagnostics().at("action_sequence")==1&&
            actor.mp==10000-*fixtureCost.consumeMp()&&isolated.snapshotDiagnostics().at("last_cost")==fixtureCost.json(),
            "Isolated1700 clock fixture really admits one source-costed action before checking its frame clock");
        check(!out.skillAnimationLayers.empty()&&out.animationClock&&std::abs(out.animationClock->ratePercent-
            (clock==ani_clock::ClockPolicy::SourceDelay100?100.:170.))<.0001,"Actual runtime clock uses actor1700 without adding Upper lift350 to speed");
        check(out.animationClock->frame==size_t(d.bodyLayerBirthFrame)&&out.skillAnimationLayers.front().instanceClock&&
            out.skillAnimationLayers.front().instanceClock->elapsedMs==out.animationClock->elapsedMs-out.animationClock->frameStartMs,
            "Initial1700-rate effect starts at the real frame deadline rather than replacing its birth with the current tick sample");
        const auto age=out.skillAnimationLayers.front().instanceClock->elapsedMs;actor.hitStopped=true;
        for(int n=0;n<4;++n){out=isolated.advance(++tick+1,actor,[](double,double){return true;});actor=out.actor;
            check(!out.skillAnimationLayers.empty()&&out.skillAnimationLayers.front().instanceClock->elapsedMs==age,
                "Hitstop freezes action-owned effect age without restarting birth");}
        actor.hitStopped=false;actor.attackPerMille=1100;out=isolated.advance(++tick+1,actor,[](double,double){return true;});
        check(!out.skillAnimationLayers.empty()&&out.skillAnimationLayers.front().instanceClock->elapsedMs>age&&
            out.skillAnimationLayers.front().instanceClock->elapsedMs-age<=17,"Live attack-speed refresh cannot rescale past source effect age");
        for(int n=0;n<100;++n){out=isolated.advance(++tick+1,out.actor,[](double,double){return true;});shakes+=out.sourceCameraShakes.size();}
        check(shakes==1&&!isolated.attacking()&&out.skillAnimationLayers.empty(),"Repeated held frames, pause and rate refresh never repeat source shake/birth or retain effects after action exit");
        for(const double speed:{1700.,30000.}) {
            ExperimentalCharacterRuntime refreshed(shared);refreshed.setAnimationClockPolicy(clock);
            refreshed.configuration().configureSourceSkillAction(upper,1,*shared);refreshed.configuration().assignSlot(0,upper,*shared);
            ExperimentalActorState state;state.mp=10000;state.attackPerMille=950;state.weaponSubtype=fixtureSubtype[0].get<int>();refreshed.request(request);
            ExperimentalTickResult sample;bool born=false;size_t birthShakes=0;
            for(uint64_t at=1;at<=100&&!born;++at) {
                if(at==2)state.attackPerMille=speed;
                sample=refreshed.advance(at,state,[](double,double){return true;});state=sample.actor;birthShakes+=sample.sourceCameraShakes.size();
                if(at==1)check(refreshed.attacking()&&refreshed.snapshotDiagnostics().at("action_sequence")==1&&
                    state.mp==10000-*fixtureCost.consumeMp()&&refreshed.snapshotDiagnostics().at("last_cost")==fixtureCost.json(),
                    "Refreshed clock fixture really admits one source-costed action before changing attack speed");
                if(sample.skillAnimationLayers.empty())continue;
                const auto visit=std::find_if(sample.attacks.begin(),sample.attacks.end(),[&](const ExperimentalAttackFrame &frame){
                    return frame.sourceFrame==size_t(d.bodyLayerBirthFrame)&&frame.animationClock&&frame.skill==std::optional<SkillKey>(upper);});
                check(visit!=sample.attacks.end()&&sample.animationClock&&sample.skillAnimationLayers.front().instanceClock&&
                    sample.skillAnimationLayers.front().instanceClock->elapsedMs==sample.animationClock->elapsedMs-visit->animationClock->frameStartMs,
                    "A rate refresh before birth preserves exact first attack deadline and overshoot even when several body frames cross in one tick");born=true;
            }
            check(born&&birthShakes==1,"Refreshed single/multiframe birth publishes exactly one source shake and one layer pair");
        }

        const auto schedule=[&](int fps,bool budgeted) {
            CharacterStore saved(root/("schedule-"+std::string(ani_clock::policyName(clock))+"-"+std::to_string(fps)),"priest-upper-test");
            saved.data=upperRoot(1);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progress(regions);
            saved.apply(0,world,progress);upperRest(world);world.configureAnimationClock(clock);
            check(world.assignLearnedSkillSlot(0,upper).ok,"Schedule fixture uses normal free initial learned slot");
            upperArena(world);world.randomStreams()=RandomStreams(1031);
            world.enqueue({0,20,true});world.enqueue({16666667,20,false});Json frames=Json::array();
            world.setObjectTick([&](World &v) {
                Json layers=Json::array();for(const auto &layer:v.player.skillAnimationLayers)layers.push_back({{"source",layer.source.memberPath},
                    {"frame",layer.instanceClock->frame},{"age",layer.instanceClock->elapsedMs},{"ended",layer.instanceClock->ended}});
                frames.push_back({{"tick",v.tick},{"mp",v.player.mp},{"path",v.player.animationPath},{"layers",layers},
                    {"runtime",v.experimentalRuntime()->snapshotDiagnostics()},{"events",v.eventLog()},{"random",v.randomStreams().snapshot()}});
            });
            constexpr int64_t total=2000000000;int64_t previous=0;
            if(budgeted){world.advance(total,8);while(world.pendingTicks())world.advance(0,8);}
            else for(int frame=1;frame<=fps*2;++frame){const auto current=total*frame/(fps*2);world.advance(current-previous);previous=current;}
            check(world.tick==120&&!world.pendingTicks(),"Normal Upper render schedule consumes all120 fixed ticks");saved.close();return frames;
        };
        const auto reference=schedule(60,false);
        for(int fps:{30,144})check(schedule(fps,false)==reference,"Normal Upper costs/effect birth/retirement/events are identical at render FPS "+std::to_string(fps));
        check(schedule(1,true)==reference,"Budget8 catch-up preserves every normal Upper fixed-tick presentation and cost result");
    }

    // All five real starter weapon families use actual inventory -> EQU/LAY;
    // the rosary's second layer is necessary to retain source frames4/5.
    {
        CharacterStore store(root/"five-weapons","priest-upper-test");store.data=upperRoot(15);World w(pvf,assets,WorldRules::BetaFoundationV1);
        w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);upperRest(w);check(w.assignLearnedSkillSlot(0,upper).ok,"Equipment fixture binds normal initial Upper");
        const auto &plan=w.experimentalRuntime()->plan();const auto &d=plan.sourceSkillActions.at(upper);const Field *table=nullptr;
        for(const auto &f:plan.characterDefinition.settings.script.fields)if(f.tag=="[key value index]"&&!f.values.empty()&&f.values[0]=="defaultWeaponBySubType")table=&f;
        check(table!=nullptr,"Own priest.etc supplies real defaultWeaponBySubType registrations");int count=0;Json footprints=Json::array();
        for(size_t cell=2;cell+1<table->values.size();cell+=2) {
            const auto id=table->values[cell+1].get<int>();const auto *item=p.item(id);check(item&&item->minimumLevel<=15&&p.itemUsableBy(id,w.characterSource()),"Actual source starter weapon is eligible");
            const int uid=p.state.at("next_uid").get<int>(),index=int(p.state.at("inventory").size());p.state["next_uid"]=uid+1;
            p.state["inventory"].push_back({{"uid",uid},{"id",id},{"count",1},{"durability",item->durability}});
            check(w.changeEquipment(p,index).ok,"Normal owned weapon transaction refreshes real EQU and attack-speed consumers");
            const auto actual=readCharacterAttackMotion(assets,w.characterAppearance(),d.motion.memberPath);std::set<size_t> frames;
            for(size_t f=0;f<actual.body->frames.size();++f)if(!actual.boxesAt(f).empty())frames.insert(f);
            check(frames==std::set<size_t>{2,3,4,5}&&!actual.weapons.empty(),"Every actual starter family supplies all source attack frames2..5");
            if(id==35300)check(actual.weapons.size()==2&&!actual.weapons.back()->frames[4].boxes.empty()&&
                std::any_of(actual.weapons.back()->frames[4].boxes.begin(),actual.weapons.back()->frames[4].boxes.end(),[](const Box &b){return b.type==15;}),
                "Rosary second source weapon layer supplies real late attacks and is not silently omitted");
            upperCooldown(w);upperArena(w);w.events.clear();const auto mp=w.player.mp;upperCast(w);
            check(w.experimentalRuntime()->attacking()&&w.player.mp<mp&&upperAudio(w)==1,"Actual equipped family passes source preflight and normal MP/CD cast");
            upperTicks(w,120);upperRest(w);footprints.push_back({{"equipment",id},{"motion",actual.json()}});++count;
        }
        check(count==5,"All five source starter weapon families execute normal Upper");evidence.push_back({{"five_weapon_closures",footprints}});store.close();
    }
    for(int branch:{1,2,3,4}) {
        CharacterStore store(root/("gsd"+std::to_string(branch)),"priest-upper-test");store.data=upperRoot(50);World w(pvf,assets,WorldRules::BetaFoundationV1);
        w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);upperRest(w);check(w.assignLearnedSkillSlot(0,upper).ok,"GSD fixture binds actual initial Upper");
        const auto ledger=w.skillState().snapshot(w.nowMs()),budget=w.skillLearningBudget(false,50).json();
        for(int awakening:{0,1}) {
            CharacterAdvancementTransaction transaction;const auto scene=upperTrainer(w);const CharacterIdentity destination{4,branch,awakening};
            const auto result=transaction.submit(store,0,w,p,scene,{"upper-gsd-"+std::to_string(branch)+"-"+std::to_string(awakening),
                w.identity(),destination,store.generation(),w.advancementCatalog().trainerId()},Json::object());
            check(result.ok,"Real source-qualified GSD branch/awakening transaction succeeds");auto after=w.skillState().snapshot(w.nowMs());after["identity"]=ledger["identity"];
            check(after==ledger&&w.skillLearningBudget(false,50).json()==budget&&w.skillUseEligibility(upper).allowed()&&
                w.experimentalRuntime()->configuration().binding(upper)->level==1&&w.experimentalRuntime()->configuration().slots()[0]==std::optional<SkillKey>(upper)&&
                w.skillState().learnedLevel(upperTp)==0&&w.skillState().learnedLevel(devilGauge)==0,
                "GSD preserves initial Upper and ledger across all four branches without inventing unsupported TP/gauge grants or denying learned Blue Monk alone");
        }
        World loaded(pvf,assets,WorldRules::BetaFoundationV1);loaded.enableExperimentalCharacters();Progression lp(regions);store.apply(0,loaded,lp);
        check(loaded.identity()==w.identity()&&loaded.skillState().snapshot(loaded.nowMs())==w.skillState().snapshot(w.nowMs())&&loaded.skillUseEligibility(upper).allowed(),
            "Real awakened Priest save reload retains source Upper and exact learned ledger");store.close();
    }
    for(const SkillKey unsupported:{upperTp,devilGauge}) {
        CharacterStore store(root/("legacy-"+std::to_string(unsupported.skillId)),"priest-upper-test");store.data=upperRoot(50);
        World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);upperRest(w);
        if(unsupported==devilGauge) {
            CharacterAdvancementTransaction transaction;const auto scene=upperTrainer(w);
            check(transaction.submit(store,0,w,p,scene,{"upper-legacy-avenger",w.identity(),{4,4,0},store.generation(),
                w.advancementCatalog().trainerId()},Json::object()).ok,"Legacy gauge fixture enters actual Avenger identity through GSD");
        }
        check(w.assignLearnedSkillSlot(0,upper).ok,"Legacy fixture retains an actually assigned normal Upper slot");
        auto imported=w.skillState().snapshot(w.nowMs());imported.erase("learning");
        for(auto &record:imported["skills"])if(SkillKey::fromJson(record.at("key"))==upper)record["level"]=10;
        imported["skills"].push_back({{"key",unsupported.json()},{"level",1},{"remaining_cooldown_ms",0},
            {"fixture","explicit legacy import; unsupported modifier retained"}});
        CharacterSkillState raw(w.identity());raw.restore(imported,w.nowMs());
        const auto migration=w.skillLearning().prepareInitialization(raw,50,SkillInitializationMode::LegacyImport,w.nowMs());
        check(migration.ok,"Legacy fixture uses actual source-bound initialization and retained grant history");w.publishSkillLedger(migration.state);
        const auto normal=w.skillState().snapshot(w.nowMs());const auto gate=w.skillUseEligibility(upper);
        check(w.runtimeSkillPolicy(upper).implemented&&!w.runtimeSkillPolicy(unsupported).implemented&&
            gate.gate==SkillLearningGate::SpecialQualification&&gate.error.find(std::to_string(unsupported.skillId))!=std::string::npos&&
            w.skillLearningConsumerMetadata(upper).at("normal_release_blocker")==gate.error&&w.skillState().learnedLevel(unsupported)==1,
            "Already learned TP210 or Avenger123 produces concrete Upper use diagnostic without hiding or deleting source/ledger rows");
        upperArena(w);w.events.clear();const auto mp=w.player.mp;const auto random=w.randomStreams().snapshot();upperCast(w);upperTicks(w,40);
        check(!w.experimentalRuntime()->attacking()&&w.player.mp==mp&&upperAudio(w)==0&&w.player.skillAnimationLayers.empty()&&
            w.experimentalRuntime()->remainingCooldown(upper,w.nowMs())==0&&w.randomStreams().snapshot()==random&&w.skillState().snapshot(w.nowMs())==normal,
            "Previously assigned Upper cannot silently omit an imported unsupported modifier or publish MP/CD/voice/effects before its gate");
        upperRest(w);store.capture(0,w,p);store.checkpoint();World loaded(pvf,assets,WorldRules::BetaFoundationV1);loaded.enableExperimentalCharacters();
        Progression lp(regions);store.apply(0,loaded,lp);
        check(loaded.skillState().snapshot(loaded.nowMs())==normal&&loaded.skillState().learnedLevel(unsupported)==1&&
            loaded.skillUseEligibility(upper).gate==SkillLearningGate::SpecialQualification,"Exact unsupported legacy modifier and specific Upper blocker survive real reload");
        evidence.push_back({{"unsupported_modifier",unsupported.json()},{"gate",gate.json()}});store.close();
    }
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"evidence",evidence},{"save_directory",root.u8string()},
        {"normal_upper_consumer_bound",true},{"tp_210_normal_admitted",false},{"native_parity",false},
        {"scope","Normal input/learning/equipment/MP/CD/damage/monster response/GSD/save and actual fixed-tick effect consumers; no frontend or native dynamic comparison"}};
}
} // namespace dnf
