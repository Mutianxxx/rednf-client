#include "dnf/skill_learning_transaction.hpp"
#include "dnf/character_attack.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr SkillKey upper{3,12},thrust{3,4};
Json mageRoot(int level) {
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    root["characters"][0]={{"name","MageUpperConsumer"},{"class","mage"},{"identity",CharacterIdentity{3,0,0}.json()},
        {"level",level},{"weapon",0},{"skill_initialization","source-v1"}};return root;
}
void mageRest(World &w) {
    w.releaseInputs();w.changeScene();w.monsters.clear();w.events.clear();w.idle();w.combat=false;
    auto &a=w.player;a.dead=false;a.life=ActorLife::Alive;a.hp=a.maxHp;a.recovery=0;a.stunUntil=0;a.hitStopTicks=0;a.hitStopped=false;
    a.x=a.px=700;a.y=a.py=344;a.z=a.pz=a.vx=a.vy=a.vz=0;a.dir=1;
}
void mageArena(World &w) {
    w.combat=true;w.freezeAi=true;w.freeCd=false;w.mapWidth=3000;w.walkRects={{0,185,3000,600}};w.blockedRects.clear();w.player.mp=w.player.maxMp;
}
void mageInput(World &w,int key,bool down){w.enqueue({w.simulationNanoseconds(),key,down});}
void mageCast(World &w){mageInput(w,20,true);w.advanceSingleTick();mageInput(w,20,false);}
void mageTicks(World &w,int n){while(n-->0)w.advanceSingleTick();}
void mageCooldown(World &w){while(w.experimentalRuntime()->remainingCooldown(upper,w.nowMs())>0)w.advanceSingleTick();w.releaseInputs();}
Json mageLive(const World &w,const Progression &p) {
    return {{"world",w.snapshot()},{"simulation",w.simulationCheckpoint()},{"ledger",w.skillState().snapshot(w.nowMs())},
        {"config",w.experimentalRuntime()->configuration().snapshot()},{"cooldowns",w.experimentalRuntime()->cooldownSnapshot(w.nowMs())},
        {"overlay",w.skillTestOverlay().snapshot()},{"progression",p.state}};
}
}

// This is an actual source/normal-runtime consumer test, not an assertion that
// native caller parity or all Mage skills have been recovered. Parent runs it.
Json runMageUpperRuntimeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message){checks.push_back({{"passed",pass},{"message",message}});
        if(!pass){writeJson("mage-upper-failure.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}};
    RegionCatalog regions(pvf,assets);
    const auto root=std::filesystem::absolute(std::filesystem::path("cache/mage-upper-tests")/
        std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        CharacterStore store(root/ani_clock::policyName(clock),"mage-upper-test");store.data=mageRoot(4);
        World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);
        mageRest(w);w.configureAnimationClock(clock);auto &runtime=*w.experimentalRuntime();const auto &plan=runtime.plan();
        check(plan.sourceSkillActions.size()==2&&plan.sourceSkillActions.count(upper)&&plan.sourceSkillActions.count(thrust),
            "New own Upper and existing Thrust survive independently in current source plan");
        const auto &d=plan.sourceSkillActions.at(upper);const auto body=assets.animation(d.motion.memberPath);
        check(d.state==-1&&d.motionSlot==2&&d.attackSlot==1&&d.requiresEquippedAttackVolume&&d.bodySidestep&&
            d.bodySidestep->returnFrame==3&&d.bodySidestep->returnSourceMs==340&&body->duration==680&&
            d.callback.memberPath.empty()&&d.objectId==-1&&!d.sourceFrameSuperArmor&&d.bodyLayers.size()==1,
            "Exact current own CHR2/ATK1/body680/weapon first3 are used without invented state/NUT/PO/protection");
        check(!w.experimentalSkillPreviewEnabled()&&!w.debugOverrides().enabled&&w.skillState().learnedLevel(upper)==1&&
            runtime.configuration().binding(upper)&&runtime.configuration().binding(upper)->level==1&&w.skillLearningBudget(false,4).spentSp==0,
            "Normal source-v1 initial Upper1 has a real canonical consumer without double charging SP or granting test skills");
        check(w.runtimeSkillPolicy(upper).implemented&&w.runtimeSkillPolicy(thrust).implemented&&
            !w.runtimeSkillPolicy({3,210}).implemented&&!w.runtimeSkillPolicy({3,212}).implemented&&w.assignLearnedSkillSlot(0,upper).ok,
            "Normal initial Upper uses learned hotbar and leaves unsupported TP outside purchase admission");
        for(int level:{1,10}) {
            const auto values=plan.skills.at(upper).data->values("[level info]");const auto op=evaluateSourceSkillAction(d,*plan.skills.at(upper).data,level);
            check(op.damage.percent==float(*skillLevelValue(values,level,0))&&op.damage.independentPercent==float(*skillLevelValue(values,level,4))&&
                op.attackSpeedBonusPermille==*skillLevelValue(values,level,1)&&op.bodyLift&&*op.bodyLift==*skillLevelValue(values,level,2)&&op.damage.fixedDamage==0,
                "Real source percent0/speed-tenth1/lift2/independent4 preserve unknown3 and avoid course speed10x at level "+std::to_string(level));
        }
        store.capture(0,w,p);store.checkpoint();const auto quote=w.quoteSkillLearning(upper,4);
        check(quote.accepted()&&quote.targetLevel==2&&quote.cost==20&&quote.requiredCharacterLevel==4&&quote.purchaseMaximum==10,
            "Normal Upper2 quote uses own char4/SP20/growtype maximum10");
        SkillLearningTransaction purchase;const SkillLearningRequest buy{"mage-upper2",upper,quote.revision,2};
        const auto before=mageLive(w,p);store.setFailureInjector([](SaveFailurePoint point){
            if(point==SaveFailurePoint::AfterPublish)throw std::runtime_error("Mage Upper durable fault");});
        check(!purchase.submit(store,0,w,p,buy,Json::object()).ok&&purchase.pending()&&mageLive(w,p)==before,
            "Actual durable publication failure keeps Upper budget/ledger/slot/runtime private");
        store.setFailureInjector({});check(purchase.retry(store,w).ok&&w.skillState().learnedLevel(upper)==2&&
            runtime.configuration().binding(upper)->level==2&&w.skillLearningBudget(false,4).spentSp==20,
            "Real retry publishes Upper2 and exactly one own SP20 purchase");
        const auto budget=w.skillLearningBudget(false,4).json();check(purchase.submit(store,0,w,p,buy,Json::object()).state==SkillLearningTransactionState::Replayed&&
            w.skillLearningBudget(false,4).json()==budget,"Normal purchase replay cannot spend or grant twice");
        const auto normal=w.skillState().snapshot(w.nowMs());mageArena(w);const auto mp=w.player.mp;mageCast(w);
        const auto cost=runtime.snapshotDiagnostics().at("last_cost");
        check(runtime.attacking()&&mp-w.player.mp==cost.at("mp").at("value").get<int>()&&
            runtime.remainingCooldown(upper,w.nowMs())==int64_t(std::ceil(cost.at("cooldown_ms").at("value").get<double>()))&&!w.armor(),
            "Normal empty Upper casts through actual weapon-adjusted MP/CD with no fabricated armor");
        bool layers=false,volume=false;
        for(int tick=0;tick<100;++tick) {
            layers|=!w.player.skillAnimationLayers.empty();
            for(const auto &v:w.attackVolumes)if(v.skillId==12&&v.sourceModifiers) {
                volume=true;check(v.sourceModifiers->percent==float(*skillLevelValue(plan.skills.at(upper).data->values("[level info]"),2,0)),
                    "Actual equipped Upper attack receives paid level2 source coefficients");
            }
            w.advanceSingleTick();
        }
        check(layers&&volume&&!runtime.attacking()&&w.player.skillAnimationLayers.empty()&&w.skillState().snapshot(w.nowMs())==normal,
            "Actual empty release executes own body/effect/equipment and retires all owned layers");
        const auto afterMp=w.player.mp;mageCast(w);check(!runtime.attacking()&&w.player.mp==afterMp,"Real remaining cooldown rejects a repeat fee");
        mageRest(w);mageCooldown(w);mageArena(w);w.player.mp=0;mageCast(w);
        check(!runtime.attacking()&&runtime.remainingCooldown(upper,w.nowMs())==0,"MP failure publishes neither action nor cooldown");
        mageRest(w);mageCooldown(w);mageArena(w);
        const auto composed=readCharacterAttackMotion(assets,w.characterAppearance(),d.motion.memberPath);const auto boxes=composed.boxesAt(3);
        check(!boxes.empty()&&!composed.weapons.empty(),"Actual saved default rod supplies source type15 at Upper frame3");
        const auto &box=boxes.front();
        for(int id:{1,2}) {
            Actor target;target.id=id;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";target.dir=-1;
            target.x=target.px=w.player.x+box.x+box.w*.5;target.y=target.py=w.player.y+box.y+box.h*.5;
            w.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");target.hp=target.maxHp=100000000;
            w.monsters.push_back(std::move(target));
        }
        w.synchronizeEntityHandles();w.randomStreams()=RandomStreams(67);mageCast(w);bool reaction=false,lift=false;
        for(int tick=0;tick<110;++tick) {
            for(const auto &m:w.monsters){reaction|=m.animationPath.rfind("monster/goblin/",0)==0&&
                (m.animation=="damage1"||m.animation=="damage2"||m.animation=="down");lift|=m.vz>0;}
            w.advanceSingleTick();
        }
        const auto contacts=std::count_if(w.events.begin(),w.events.end(),[](const Event &e){return (e.kind=="hit"&&e.name=="experimental_source_skill")||e.kind=="miss";});
        check(contacts==2&&reaction&&lift&&(w.monsters[0].hp<100000000||w.monsters[1].hp<100000000),
            "Actual two-target weapon contact deduplicates per swing and consumes SKL lift despite own ATK lacking lift tags");
        evidence.push_back({{"clock",ani_clock::policyName(clock)},{"descriptor",d.snapshot()},{"cost",cost},{"damage",w.statReport().at("last_damage")}});
        mageRest(w);store.capture(0,w,p);store.checkpoint();const auto cooldown=runtime.cooldownSnapshot(w.nowMs()),random=w.randomStreams().snapshot();
        World loaded(pvf,assets,WorldRules::BetaFoundationV1);loaded.enableExperimentalCharacters();Progression lp(regions);store.apply(0,loaded,lp);
        check(!loaded.experimentalSkillPreviewEnabled()&&loaded.skillState().snapshot(loaded.nowMs())==normal&&
            loaded.experimentalRuntime()->configuration().binding(upper)->level==2&&loaded.experimentalRuntime()->configuration().slots()[0]==std::optional<SkillKey>(upper)&&
            loaded.experimentalRuntime()->cooldownSnapshot(loaded.nowMs())==cooldown&&loaded.randomStreams().snapshot()==random&&
            loaded.experimentalRuntime()->snapshotDiagnostics().at("source_body_sidesteps").empty(),
            "Real reload preserves paid Upper ledger/slot/CD/random generation and never restores transient sidestep requests");
        mageRest(loaded);mageCooldown(loaded);check(loaded.assignLearnedSkillSlot(0,std::nullopt).ok,"Default Z fixture removes explicit slot");mageArena(loaded);
        const auto zMp=loaded.player.mp;mageInput(loaded,4,true);loaded.advanceSingleTick();mageInput(loaded,4,false);
        mageInput(loaded,6,true);loaded.advanceSingleTick();mageInput(loaded,6,false);
        check(loaded.experimentalRuntime()->attacking()&&loaded.player.mp==zMp,"Own learned default Z buffers without early force cancel or fee");
        bool continued=false;for(int n=0;n<240&&!continued;++n){loaded.advanceSingleTick();continued=loaded.player.animationPath==d.motion.memberPath;}
        check(continued&&loaded.player.mp<zMp,"Default Z starts own Upper at completed source boundary with actual cost");
        mageTicks(loaded,100);mageRest(loaded);check(loaded.assignLearnedSkillSlot(0,upper).ok,"Normal slot restored before rollback and cleanup checks");
        const auto normalAgain=loaded.skillState().snapshot(loaded.nowMs()),normalConfig=loaded.normalSkillConfigurationSnapshot();
        DebugOverrides debug;debug.enabled=true;debug.level=99;loaded.applyDebugOverrides(debug,4);
        const auto testQuote=loaded.quoteTestSkillLearning(upper);
        check(testQuote.accepted()&&loaded.learnTestSkill({"mage-upper-test3",upper,testQuote.revision,3}).ok&&
            loaded.experimentalRuntime()->configuration().binding(upper)->level==3,"Isolated test learning projects Upper3 without changing normal purchases");
        check(loaded.setExperimentalSkillPreviewEnabled(true).ok,"Independent manual comparison remains explicit");
        loaded.experimentalRuntime()->configuration().configureSourceSkillAction(upper,10,loaded.experimentalRuntime()->plan());
        check(loaded.setExperimentalSkillPreviewEnabled(false).ok&&loaded.experimentalRuntime()->configuration().binding(upper)->level==3,
            "Leaving manual Upper10 restores actual test-effective Upper3");loaded.applyDebugOverrides({},4);
        check(loaded.skillState().snapshot(loaded.nowMs())==normalAgain&&loaded.normalSkillConfigurationSnapshot()==normalConfig&&
            loaded.experimentalRuntime()->configuration().binding(upper)->level==2,"Leaving test restores exact normal paid Upper2 ledger and slot");
        mageCooldown(loaded);mageArena(loaded);auto &appearance=const_cast<CharacterAppearance &>(loaded.characterAppearance());
        auto removed=appearance.parts.extract("[weapon]");const auto faultMp=loaded.player.mp;const auto faultRng=loaded.randomStreams().snapshot();mageCast(loaded);
        check(!removed.empty()&&!loaded.experimentalRuntime()->attacking()&&loaded.player.mp==faultMp&&loaded.randomStreams().snapshot()==faultRng&&
            loaded.experimentalRuntime()->remainingCooldown(upper,loaded.nowMs())==0&&
            loaded.experimentalDiagnostics().at("world").back().at("code")=="experimental_attack_source_preflight_rejected",
            "Missing real weapon reaches preflight and cannot publish action/fee/CD/random/sidestep");appearance.parts.insert(std::move(removed));
        {
            mageRest(loaded);mageCooldown(loaded);mageArena(loaded);
            auto broken=std::make_shared<ExperimentalCharacterPlan>(loaded.experimentalRuntime()->plan());
            broken->sourceSkillActions.at(upper).bodyLayers.front().source.memberPath="missing/mage-upper.ani";
            ExperimentalCharacterRuntime injected(broken);injected.setAnimationClockPolicy(clock);
            injected.configuration().configureSourceSkillAction(upper,2,*broken);injected.configuration().assignSlot(0,upper,*broken);
            CharacterActionRequest request;request.inputKey=20;request.inputDown=true;injected.request(request);
            const auto mp=loaded.player.mp;const auto rng=loaded.randomStreams().snapshot();auto ids=loaded.idSources().snapshot();ids.erase("requests");
            ExperimentalWorldAdapter adapter(loaded);adapter.advance(injected,uint64_t(loaded.tick)+1);
            auto afterIds=loaded.idSources().snapshot();afterIds.erase("requests");
            check(!injected.attacking()&&injected.remainingCooldown(upper,loaded.nowMs())==0&&loaded.player.mp==mp&&
                loaded.randomStreams().snapshot()==rng&&ids==afterIds&&loaded.player.skillAnimationLayers.empty()&&
                injected.snapshotDiagnostics().at("source_body_sidesteps").empty()&&
                loaded.experimentalDiagnostics().at("world").back().at("code")=="experimental_attack_source_preflight_rejected",
                "Missing own visual rolls back private action, MP/CD, random, combat identities and side-return state before publication");
        }
        for(const std::string reason:{"cancel","scene","death","blocked"}) {
            mageRest(loaded);mageCooldown(loaded);mageArena(loaded);mageInput(loaded,3,true);mageCast(loaded);mageInput(loaded,3,false);mageTicks(loaded,4);
            check(loaded.experimentalRuntime()->attacking()&&!loaded.experimentalRuntime()->snapshotDiagnostics().at("source_body_sidesteps").empty(),
                "Cleanup starts with a live actual directional Upper");
            if(reason=="cancel")loaded.idle();else if(reason=="scene")loaded.changeScene();
            else if(reason=="blocked")loaded.player.stunUntil=loaded.nowMs()+1000;else {loaded.player.dead=true;loaded.player.life=ActorLife::Dying;}
            loaded.advanceSingleTick();const auto diagnostics=loaded.experimentalRuntime()->snapshotDiagnostics();
            check(!loaded.experimentalRuntime()->attacking()&&loaded.player.skillAnimationLayers.empty()&&diagnostics.at("source_body_actions")==0&&
                diagnostics.at("source_body_sidesteps").empty(),"Source action, side return and visual cleanup share exit ownership: "+reason);
        }
        store.close();

        // Actual runtime progression with physical input, copied policy/state,
        // both arithmetic clocks, hitstop, live speed and swept map collision.
        const auto shared=std::make_shared<ExperimentalCharacterPlan>(plan);
        const auto subtypeValues=w.characterAppearance().parts.at("[weapon]").source.values("[sub type]");
        check(subtypeValues.size()==1&&subtypeValues.front().is_number_integer(),"Isolated runtime reads real saved default EQU subtype");
        const auto fixtureSubtype=subtypeValues.front().get<int>();
        for(const int direction:{-1,0,1})for(const bool wall:{false,true}) {
            ExperimentalCharacterRuntime run(shared);run.setAnimationClockPolicy(clock);run.configuration().configureSourceSkillAction(upper,1,*shared);
            run.configuration().assignSlot(0,upper,*shared);ExperimentalActorState actor;actor.mp=10000;actor.weaponSubtype=fixtureSubtype;actor.y=344;actor.x=700;
            actor.attackPerMille=1700;CharacterActionRequest request;
            if(direction){request.inputKey=direction<0?2:3;request.inputDown=true;run.request(request);}
            request.inputKey=20;request.inputDown=true;run.request(request);
            const auto walk=[&](double,double y){return !wall||std::abs(y-344)<=5;};
            double peak=0;bool returned=false,paused=false;ExperimentalTickResult out;
            for(uint64_t tick=1;tick<=100;++tick) {
                actor.hitStopped=tick>=5&&tick<=8;const auto oldY=actor.y;
                out=run.advance(tick,actor,walk);actor=out.actor;
                if(tick==1&&direction){request.inputKey=direction<0?2:3;request.inputDown=false;run.request(request);}
                if(actor.hitStopped){check(actor.y==oldY,"Hitstop freezes actual sidestep position");paused=true;}
                peak=std::max(peak,std::abs(actor.y-344));
                if(out.animationClock&&out.animationClock->frame>=3){returned=true;check(std::abs(actor.y-344)<1e-7,"Actual first equipped attack begins after accepted slide returns");}
                if(tick==9)actor.attackPerMille=1100;
            }
            check(returned&&paused&&!run.attacking()&&std::abs(actor.y-344)<1e-7&&
                (direction?peak>0:peak==0)&&(!wall||peak<=5)&&run.snapshotDiagnostics().at("source_body_sidesteps").empty(),
                "Source-local sidestep handles up/down/neutral, real wall limit, clock refresh and complete cleanup");
            evidence.push_back({{"direction",direction},{"wall",wall},{"peak",peak},{"clock",ani_clock::policyName(clock)}});
        }
        {
            ExperimentalCharacterRuntime run(shared);run.setAnimationClockPolicy(clock);run.configuration().configureSourceSkillAction(upper,1,*shared);
            run.configuration().assignSlot(0,upper,*shared);ExperimentalActorState actor;actor.mp=10000;actor.weaponSubtype=fixtureSubtype;actor.x=700;actor.y=344;
            CharacterActionRequest input;input.inputKey=3;input.inputDown=true;run.request(input);input.inputKey=20;run.request(input);
            bool returnWall=false;double stoppedY=344;ExperimentalTickResult out;
            const auto walk=[&](double,double y){return !returnWall||y>=354;};
            for(uint64_t tick=1;tick<=70;++tick) {
                out=run.advance(tick,actor,walk);actor=out.actor;
                if(tick==1){input.inputKey=3;input.inputDown=false;run.request(input);}
                if(out.animationClock&&sourceBodyElapsedMs(*body,*out.animationClock)>=d.bodySidestep->turnSourceMs)returnWall=true;
                if(returnWall)stoppedY=actor.y;
            }
            check(returnWall&&stoppedY>=354&&stoppedY<368&&!run.attacking()&&
                run.snapshotDiagnostics().at("source_body_sidesteps").empty(),
                "A real new return-path obstacle preserves accepted ground position through action completion and never teleports to origin");
            SourceBodySidestepState fast{344,1};double largest=344;
            const auto swept=[&](double,double y){largest=std::max(largest,y);return y<=349;};
            const auto y=advanceSourceBodySidestep(*d.bodySidestep,fast,d.bodySidestep->returnSourceMs+1,700,344,swept);
            check(y==344&&fast.outwardBlocked&&fast.extent==5&&largest==350,
                "The production sidestep helper sweeps the crossed outward and return path even when one clock step crosses the entire windup");
        }
        const auto schedule=[&](int fps,bool budgeted) {
            CharacterStore saved(root/("schedule-"+std::string(ani_clock::policyName(clock))+"-"+std::to_string(fps)),"mage-upper-test");saved.data=mageRoot(1);
            World v(pvf,assets,WorldRules::BetaFoundationV1);v.enableExperimentalCharacters();Progression progress(regions);saved.apply(0,v,progress);
            mageRest(v);v.configureAnimationClock(clock);check(v.assignLearnedSkillSlot(0,upper).ok,"Schedule uses actual free initial Upper1");mageArena(v);v.randomStreams()=RandomStreams(1031);
            v.enqueue({0,3,true});v.enqueue({0,20,true});v.enqueue({16666667,3,false});v.enqueue({16666667,20,false});Json frames=Json::array();
            v.setObjectTick([&](World &sample){frames.push_back({{"tick",sample.tick},{"y",sample.player.y},{"mp",sample.player.mp},
                {"runtime",sample.experimentalRuntime()->snapshotDiagnostics()},{"events",sample.eventLog()},{"rng",sample.randomStreams().snapshot()}});});
            constexpr int64_t total=2000000000;int64_t previous=0;
            if(budgeted){v.advance(total,8);while(v.pendingTicks())v.advance(0,8);}
            else for(int frame=1;frame<=fps*2;++frame){const auto now=total*frame/(fps*2);v.advance(now-previous);previous=now;}
            check(v.tick==120&&!v.pendingTicks(),"Normal directional Upper schedule consumes all120 fixed ticks");saved.close();return frames;
        };
        const auto reference=schedule(60,false);for(int fps:{30,144})check(schedule(fps,false)==reference,"Actual directional Upper is render-FPS invariant: "+std::to_string(fps));
        check(schedule(1,true)==reference,"Budget8 catch-up preserves side trajectory, fees, clocks and events");
    }
    {
        CharacterStore store(root/"weapons","mage-upper-test");store.data=mageRoot(50);World w(pvf,assets,WorldRules::BetaFoundationV1);
        w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);mageRest(w);check(w.assignLearnedSkillSlot(0,upper).ok,"Weapon fixtures use normal initial Upper");
        const auto &plan=w.experimentalRuntime()->plan();const auto &d=plan.sourceSkillActions.at(upper);const Field *table=nullptr;
        for(const auto &f:plan.characterDefinition.settings.script.fields)if(f.tag=="[key value index]"&&!f.values.empty()&&f.values[0]=="defaultWeaponBySubType")table=&f;
        check(table&&table->values.size()==12,"Actual mage.etc provides five own subtype starter registrations");int executed=0,refused=0;
        for(size_t cell=2;cell+1<table->values.size();cell+=2) {
            mageRest(w);const int subtype=table->values[cell].get<int>(),id=table->values[cell+1].get<int>();const auto *item=p.item(id);check(item!=nullptr,"Source starter item exists");
            const int uid=p.state.at("next_uid").get<int>(),index=int(p.state.at("inventory").size());p.state["next_uid"]=uid+1;
            p.state["inventory"].push_back({{"uid",uid},{"id",id},{"count",1},{"durability",item->durability}});
            if(subtype==4) {
                check(id==34200&&item->minimumLevel==18&&item->source.values("[required skill]")==Json::array({91})&&w.skillState().learnedLevel({3,91})==0,
                    "Current broom source has both level18 and required skill91; no synthetic permission or grant");
                const auto before=mageLive(w,p);const auto rejected=w.changeEquipment(p,index);auto after=mageLive(w,p),normalized=before;
                after["world"]["stats"].erase("last_equipment_change");normalized["world"]["stats"].erase("last_equipment_change");
                const auto diagnostic=w.statReport().at("last_equipment_change");
                check(!rejected.ok&&after==normalized&&diagnostic.at("status")=="rejected"&&
                    diagnostic.value("error",std::string()).find("[required skill]")!=std::string::npos,
                    "Unimplemented broom91 permission reaches real source preflight and rejects without changing live state");++refused;
            } else {
                check(w.changeEquipment(p,index).ok,"Eligible real spear/pole/rod/staff equip via inventory and source transaction");
                const auto actual=readCharacterAttackMotion(assets,w.characterAppearance(),d.motion.memberPath);std::set<size_t> frames;
                for(size_t f=0;f<actual.body->frames.size();++f)if(!actual.boxesAt(f).empty())frames.insert(f);
                check(frames==std::set<size_t>{3,4}&&actual.weapons.size()>=2,"Real equipped multilayer weapon supplies exact Upper frames3/4");
                mageCooldown(w);mageArena(w);const auto mp=w.player.mp;mageCast(w);check(w.experimentalRuntime()->attacking()&&w.player.mp<mp,
                    "Actual eligible family passes own Upper MP/CD and equipment preflight");mageTicks(w,100);++executed;
            }
        }
        // Broom geometry is source evidence even while its normal qualification
        // consumer remains blocked. Never count this read as equipped/runtime.
        for(const auto *family:{"spear","pole","rod","staff","broom"}) {
            std::set<size_t> frames;for(char layer:{'c','d'}) {
                const std::string path=std::string("equipment/character/mage/weapon/")+family+"/"+family+layer+"/upperswing.ani";
                const auto clip=assets.animation(path);for(size_t f=0;f<clip->frames.size();++f)for(const auto &box:clip->frames[f].boxes)
                    if(box.type==15)frames.insert(f);
            }
            check(frames==std::set<size_t>{3,4},std::string("Own raw c/d source geometry retained independently: ")+family);
        }
        check(executed==4&&refused==1,"Four eligible families execute; broom remains a specific source permission refusal");store.close();
    }
    for(const auto base:{upper,thrust}) {
        const SkillKey tp{3,base==upper?210:212};CharacterStore store(root/("legacy"+std::to_string(tp.skillId)),"mage-upper-test");store.data=mageRoot(50);
        World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);mageRest(w);
        auto imported=w.skillState().snapshot(w.nowMs());imported.erase("learning");
        bool present=false;for(auto &record:imported["skills"])if(SkillKey::fromJson(record.at("key"))==base){record["level"]=10;present=true;}
        if(!present)imported["skills"].push_back({{"key",base.json()},{"level",10},{"remaining_cooldown_ms",0}});
        imported["skills"].push_back({{"key",tp.json()},{"level",1},{"remaining_cooldown_ms",0},{"fixture","legacy unsupported TP retained"}});
        CharacterSkillState raw(w.identity());raw.restore(imported,w.nowMs());
        const auto migration=w.skillLearning().prepareInitialization(raw,50,SkillInitializationMode::LegacyImport,w.nowMs());check(migration.ok,"Real source-bound legacy import retains Mage TP");
        w.publishSkillLedger(migration.state);const auto normal=w.skillState().snapshot(w.nowMs());const auto gate=w.skillUseEligibility(base);
        check(gate.gate==SkillLearningGate::SpecialQualification&&gate.error.find(std::to_string(tp.skillId))!=std::string::npos&&
            w.skillState().learnedLevel(tp)==1&&w.skillLearningConsumerMetadata(base).at("normal_release_blocker")==gate.error,
            "Unsupported learned own TP gives specific fee-before-base diagnostic and preserves its ledger");
        mageArena(w);const auto mp=w.player.mp;CharacterActionRequest input;input.action=CharacterAction::Skill;input.skill=base;input.inputDown=true;
        // Physical source-default Z reaches Upper even if no user slot exists;
        // Thrust's fee gate is also explicitly exercised through command API.
        check(w.experimentalRuntime()->request(input),"Legacy TP fault fixture reaches a valid own source command request");w.advanceSingleTick();mageTicks(w,30);
        check(!w.experimentalRuntime()->attacking()&&w.player.mp==mp&&w.experimentalRuntime()->remainingCooldown(base,w.nowMs())==0&&
            w.skillState().snapshot(w.nowMs())==normal,"Actual command cannot silently omit legacy TP or publish a base fee");
        mageRest(w);store.capture(0,w,p);store.checkpoint();World loaded(pvf,assets,WorldRules::BetaFoundationV1);loaded.enableExperimentalCharacters();Progression lp(regions);store.apply(0,loaded,lp);
        check(loaded.skillState().snapshot(loaded.nowMs())==normal&&loaded.skillUseEligibility(base).gate==SkillLearningGate::SpecialQualification,
            "Concrete Mage TP blocker and unchanged legacy grant survive real save/reload");store.close();
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"normal_upper_consumer_bound",true},{"broom_qualification_admitted",false},{"tp210_212_admitted",false},
        {"full_skill_complete",false},{"native_dynamic_parity",false}};
}
} // namespace dnf
