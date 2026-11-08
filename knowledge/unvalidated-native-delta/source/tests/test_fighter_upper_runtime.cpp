#include "explicit_skill_preview_fixture.hpp"
#include "dnf/character_attack.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/scene.hpp"
#include "dnf/skill_learning_transaction.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr SkillKey upper{1,5},upperTp{1,163};
Json upperRoot(int level) {
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    root["characters"][0]={{"name","OwnFemaleUpper"},{"class","fighter"},
        {"identity",CharacterIdentity{1,0,0}.json()},{"level",level},{"weapon",0},{"skill_initialization","source-v1"}};
    return root;
}
void upperInput(World &w,int key,bool down){w.enqueue({w.simulationNanoseconds(),key,down});}
void upperCast(World &w,int key=20){upperInput(w,key,true);w.advanceSingleTick();upperInput(w,key,false);}
void upperTicks(World &w,int count){while(count-->0)w.advanceSingleTick();}
void upperRest(World &w) {
    w.releaseInputs();w.changeScene();w.monsters.clear();w.events.clear();w.idle();w.combat=false;
    auto &a=w.player;a.x=a.px=600;a.y=a.py=344;a.z=a.pz=a.vx=a.vy=a.vz=0;a.dir=1;
    a.dead=false;a.life=ActorLife::Alive;a.hp=a.maxHp;a.mp=a.maxMp;a.recovery=0;a.stunUntil=0;a.hitStopTicks=0;a.hitStopped=false;
}
void upperArena(World &w) {
    w.combat=true;w.freezeAi=true;w.freeCd=false;w.mapWidth=3000;
    w.walkRects={{0,185,3000,600}};w.blockedRects.clear();
}
size_t upperSound(const World &w,const char *id) {
    return size_t(std::count_if(w.events.begin(),w.events.end(),[&](const Event &e){return e.kind=="sound"&&e.name==id;}));
}
Json upperLive(const World &w,const Progression &p) {
    return {{"world",w.snapshot()},{"simulation",w.simulationCheckpoint()},{"progression",p.state},
        {"ledger",w.skillState().snapshot(w.nowMs())},{"normal_configuration",w.normalSkillConfigurationSnapshot()},
        {"runtime",w.experimentalRuntime()->configuration().snapshot()},{"cd",w.experimentalRuntime()->cooldownSnapshot(w.nowMs())},
        {"rng",w.randomStreams().snapshot()},{"overlay",w.skillTestOverlay().snapshot()}};
}
void upperTarget(World &w,int id,int direction,const Box &box) {
    Actor a;a.id=id;a.sourceId=10;a.monsterPath="monster/goblin/goblin.mob";a.dir=-direction;
    a.x=a.px=w.player.x+direction*(box.x+box.w*.5);a.y=a.py=w.player.y+box.y+box.h*.5;
    w.initializeMonsterAttributes(a,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    // Explicit contact/de-duplication fixture only; normal cases below retain source HP/MP.
    a.hp=a.maxHp=100000000;w.monsters.push_back(std::move(a));w.synchronizeEntityHandles();
}
Scene upperTrainer(const World &w) {
    Scene scene;MapNpc n;n.id=w.advancementCatalog().trainerId();n.source=w.advancementCatalog().trainerPath();
    n.visible=true;n.x=w.player.x;n.y=w.player.y;scene.npcs.push_back(n);return scene;
}
}

// Isolated proposal only. Parent owns compilation, execution and publication.
Json runFighterUpperRuntimeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool yes,const std::string &message){checks.push_back({{"passed",yes},{"message",message}});
        if(!yes)throw std::runtime_error("Female Upper: "+message);};
    RegionCatalog regions(pvf,assets);
    const auto root=std::filesystem::absolute(std::filesystem::path("cache/fighter-upper-runtime")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        const std::string policy=ani_clock::policyName(clock);
        for(const auto failure:{SaveFailurePoint::BeforePublish,SaveFailurePoint::AfterPublish}) {
            CharacterStore store(root/(policy+"-normal-"+std::to_string(int(failure))),"fighter-upper-test");store.data=upperRoot(4);
            World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);
            store.apply(0,w,p);upperRest(w);w.configureAnimationClock(clock);auto &r=*w.experimentalRuntime();const auto &plan=r.plan();
            check(w.skillState().learnedLevel(upper)==1&&w.runtimeSkillPolicy(upper).implemented&&
                r.configuration().binding(upper)&&r.configuration().binding(upper)->level==1&&
                w.skillLearningBudget(false,4).spentSp==0&&!w.experimentalSkillPreviewEnabled()&&!w.debugOverrides().enabled,
                "Real source-v1 gives free own female Upper1 and canonical normal consumer without preview/test grants");
            check(plan.sourceSkillActions.count({1,6})&&w.skillState().learnedLevel({1,6})==0&&
                w.skillState().learnedLevel({1,46})==1&&!w.runtimeSkillPolicy({1,46}).implemented&&
                !w.runtimeSkillPolicy(upperTp).implemented,"Existing LowKick remains separate; initial SingleKick ledger is retained without pretending Upper implements it or TP163");
            const auto &d=plan.sourceSkillActions.at(upper);const auto body=assets.animation(d.motion.memberPath);
            check(d.kind==SourceSkillActionKind::BodyAttack&&d.inferredNativeBody&&d.state==30&&d.motionSlot==2&&d.attackSlot==1&&
                d.callback.memberPath.empty()&&d.registration.memberPath.empty()&&d.objectId==-1,
                "Own female enum and actual CHR resolve skill5/state30/motion2/ATK1 without inventing NUT or PO");
            check(body->frames.size()==6&&body->duration==740&&d.recoveryMs==0&&d.sourceFrameSuperArmor&&!d.requiresEquippedAttackVolume&&
                d.bodyLayers.size()==1&&d.bodyLayers[0].source.memberPath=="character/fighter/effect/animation/upper.ani",
                "Own 740ms body and exact female visual remain distinct from source weapon1370ms and male resources");
            const auto visual=assets.animation(d.bodyLayers[0].source.memberPath);
            check(visual->duration==650&&visual->frames[0].image.empty()&&visual->frames[1].image.empty()&&
                visual->frames[0].duration+visual->frames[1].duration==320&&!d.bodyLayers[0].synchronizedToBody&&d.bodyLayers[0].inheritBodyRate,
                "650ms effect retains its own 320ms blank lead and inherits rate without replacing delays");
            const auto meta=w.skillLearningConsumerMetadata(upper);
            check(meta.at("normal_learning_consumer_bound")==true&&meta.at("tp_163_normal_admitted")==false&&
                meta.at("normal_release_blocker")==""&&meta.at("source_action")==d.snapshot(),"Normal admission wraps immutable inferred source descriptor");
            check(!w.skillLearning().sourceUseEligibility({1,5,0},upper,1,50).allowed(),"Sixth maximum column does not invent growtype5 qualification");
            check(w.assignLearnedSkillSlot(0,upper).ok,"Actual normal learned hotbar assigns own free Upper1");
            store.capture(0,w,p);store.checkpoint();const auto initial=w.skillState().snapshot(w.nowMs());
            World repeated(pvf,assets,WorldRules::BetaFoundationV1);repeated.enableExperimentalCharacters();Progression repeatedProgress(regions);
            store.apply(0,repeated,repeatedProgress);store.apply(0,repeated,repeatedProgress);
            check(repeated.skillState().snapshot(repeated.nowMs())==initial&&repeated.skillLearningBudget(false,4).spentSp==0,
                "Repeated actual reload does not grant initial Upper or spend SP twice");
            const auto quote=w.quoteSkillLearning(upper,4);const auto batch=w.quoteSkillLearningBatch(false,4);
            const auto row=std::find_if(batch.quotes.begin(),batch.quotes.end(),[](const auto &q){return q.key==upper;});
            check(quote.accepted()&&quote.targetLevel==2&&quote.requiredCharacterLevel==4&&quote.cost==20&&quote.currency=="SP"&&
                quote.purchaseMaximum==10&&row!=batch.quotes.end()&&row->json()==quote.json(),
                "Individual and normal UI batch quotes use real character4/SP20/purchase10 for Upper1 to2");
            const SkillLearningRequest buy{"female-upper-level2",upper,quote.revision,2};SkillLearningTransaction purchase;
            const auto before=upperLive(w,p);const auto generation=store.generation();
            store.setFailureInjector([failure](SaveFailurePoint actual){if(actual==failure)throw std::runtime_error("Upper durable failure");});
            check(!purchase.submit(store,0,w,p,buy,Json::object()).ok&&purchase.pending()&&upperLive(w,p)==before,
                "Before/after durable publication fault retains live source ledger, slots, MP/CD, RNG and progression");
            store.setFailureInjector({});check(purchase.retry(store,w).ok&&store.generation()==generation+1&&
                w.skillState().learnedLevel(upper)==2&&r.configuration().binding(upper)->level==2,
                "Retry publishes precisely one retained normal Upper2 generation");
            const auto budget=w.skillLearningBudget(false,4).json();const auto committed=store.generation();
            check(budget.at("spent_sp")==20&&purchase.submit(store,0,w,p,buy,Json::object()).state==SkillLearningTransactionState::Replayed&&
                store.generation()==committed&&w.skillLearningBudget(false,4).json()==budget,"Exact purchase replay cannot spend SP20 twice");
            const auto next=w.quoteSkillLearning(upper,4);
            check(next.gate==SkillLearningGate::CharacterLevel&&next.requiredCharacterLevel==7&&next.targetLevel==3,
                "Next Upper3 retains source required-level range3 rather than granting high preview levels");
            upperRest(w);upperArena(w);const int mp=w.player.mp;const auto ledger=w.skillState().snapshot(w.nowMs());
            const auto rng=w.randomStreams().snapshot();upperCast(w,6);const auto cost=r.snapshotDiagnostics().at("last_cost");
            check(r.attacking()&&w.player.animationClockSource==d.motion.memberPath&&mp-w.player.mp==cost.at("mp").at("value").get<int>()&&
                r.remainingCooldown(upper,w.nowMs())==int64_t(std::ceil(cost.at("cooldown_ms").at("value").get<double>()))&&
                upperSound(w,"FT_UPPER_READY")==1&&upperSound(w,"FT_UPPER_SWING")==0&&w.randomStreams().snapshot()==rng,
                "Actual source default Z pays one evaluated equipment MP/CD and READY; no early SWING or Audio random draw");
            bool sawBodyAttack=false;
            for(int tick=0;tick<240&&r.attacking();++tick){for(const auto &v:w.attackVolumes)if(v.skillId==5)sawBodyAttack=true;w.advanceSingleTick();}
            check(!r.attacking()&&sawBodyAttack&&upperSound(w,"FT_UPPER_READY")==1&&upperSound(w,"FT_UPPER_SWING")==1&&
                w.player.skillAnimationLayers.empty()&&r.snapshotDiagnostics().at("source_body_actions")==0&&w.randomStreams().snapshot()==rng,
                "Empty learned release visits real attack frames, emits SWING once, then retires all body layers without RNG");
            const int cooldownMp=w.player.mp;w.events.clear();upperCast(w);
            check(!r.attacking()&&w.player.mp==cooldownMp&&upperSound(w,"FT_UPPER_READY")==0&&upperSound(w,"FT_UPPER_SWING")==0,
                "Remaining real source cooldown rejects a second cast before audio or fee");
            upperRest(w);while(r.remainingCooldown(upper,w.nowMs())>0)w.advanceSingleTick();
            upperArena(w);w.player.mp=0;upperCast(w);
            check(!r.attacking()&&r.remainingCooldown(upper,w.nowMs())==0&&upperSound(w,"FT_UPPER_READY")==0&&upperSound(w,"FT_UPPER_SWING")==0,
                "Actual normal insufficient MP rejects before cooldown or either cue");
            upperRest(w);r.configuration().configureSourceSkillAction(upper,10,plan);w.advanceSingleTick();
            check(r.configuration().binding(upper)->level==2&&w.skillState().snapshot(w.nowMs())==ledger,
                "Normal simulation restores ledger-derived Upper2 over a raw high-level binding");
            check(w.assignLearnedSkillSlot(0,std::nullopt).ok,"Default Z scenario removes the hotbar slot and reads source command");
            upperArena(w);const int bufferedMp=w.player.mp;w.events.clear();upperInput(w,4,true);w.advanceSingleTick();
            upperInput(w,4,false);upperInput(w,6,true);w.advanceSingleTick();upperInput(w,6,false);
            check(r.attacking()&&w.player.animationPath!=d.motion.memberPath&&w.player.mp==bufferedMp&&upperSound(w,"FT_UPPER_READY")==0,
                "Normal source Z buffers behind current own basic action without early Upper cost or cue");
            bool continued=false;for(int n=0;n<240&&!continued;++n){w.advanceSingleTick();continued=w.player.animationPath==d.motion.memberPath;}
            check(continued&&w.player.mp<bufferedMp&&r.remainingCooldown(upper,w.nowMs())>0&&upperSound(w,"FT_UPPER_READY")==1,
                "Default Z releases real learned Upper at current action boundary with a single fee");
            for(int n=0;n<240&&r.attacking();++n)w.advanceSingleTick();
            check(!r.attacking()&&r.remainingCooldown(upper,w.nowMs())>0,"Body ends before actual source cooldown; save fixture retains a nonzero cooldown");
            upperRest(w);check(w.assignLearnedSkillSlot(0,upper).ok,"Actual learned slot restores after default Z comparison");
            const auto cooldown=r.cooldownSnapshot(w.nowMs()),random=w.randomStreams().snapshot();store.capture(0,w,p);store.checkpoint();
            World loaded(pvf,assets,WorldRules::BetaFoundationV1);loaded.enableExperimentalCharacters();Progression lp(regions);store.apply(0,loaded,lp);
            check(loaded.skillState().snapshot(loaded.nowMs())==ledger&&loaded.experimentalRuntime()->configuration().binding(upper)->level==2&&
                loaded.experimentalRuntime()->configuration().slots()[0]==std::optional<SkillKey>(upper)&&
                loaded.experimentalRuntime()->cooldownSnapshot(loaded.nowMs())==cooldown&&loaded.randomStreams().snapshot()==random&&
                loaded.skillLearningBudget(false,4).json()==budget,"Same-generation actual reload preserves own paid Upper2, slot, cooldown, RNG and SP history");
            const auto normalConfig=loaded.normalSkillConfigurationSnapshot();DebugOverrides debug;debug.enabled=true;debug.level=99;loaded.applyDebugOverrides(debug,4);
            const auto test=loaded.quoteTestSkillLearning(upper);
            check(test.accepted()&&loaded.learnTestSkill({"upper-test3",upper,test.revision,3}).ok&&
                loaded.experimentalRuntime()->configuration().binding(upper)->level==3,"Isolated test learning reaches its own qualified Upper3 consumer");
            loaded.applyDebugOverrides({},4);
            check(loaded.skillState().snapshot(loaded.nowMs())==ledger&&loaded.normalSkillConfigurationSnapshot()==normalConfig&&
                loaded.experimentalRuntime()->configuration().binding(upper)->level==2,"Leaving test restores exact normal Upper2 ledger and configuration");
            evidence.push_back({{"phase","normal-learning-cost-save"},{"clock",policy},{"failure",int(failure)},{"quote",quote.json()},{"cost",cost},{"budget",budget}});
            store.close();
        }
        // Diagnostic high levels and high-HP targets are explicitly isolated
        // preview comparisons. Equipment still uses actual EQU/LAY transactions.
        CharacterStore store(root/(policy+"-weapons"),"fighter-upper-test");store.data=upperRoot(50);
        World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);
        upperRest(w);enterExplicitSkillPreviewFixture(w);w.configureAnimationClock(clock);auto &r=*w.experimentalRuntime();const auto &plan=r.plan();
        const auto &d=plan.sourceSkillActions.at(upper);const auto body=assets.animation(d.motion.memberPath);
        const Field *weapons=nullptr;
        for(const auto &field:plan.characterDefinition.settings.script.fields)if(field.tag=="[key value index]"&&!field.values.empty()&&field.values[0]=="defaultWeaponBySubType")weapons=&field;
        check(weapons,"Actual female character settings expose starter weapon-by-subtype mapping");
        std::optional<Box> first;for(const auto &f:body->frames)for(const auto &b:f.boxes)if(b.type==15&&!first)first=b;
        check(first.has_value(),"Own female body has actual attack geometry independently of weapon boxes");
        for(const int subtype:{0,1,2,3,5}) {
            upperRest(w);int itemId=-1;for(size_t i=2;i+1<weapons->values.size();i+=2)if(weapons->values[i]==subtype)itemId=weapons->values[i+1].get<int>();
            const auto *item=p.item(itemId);check(item,"Exact source starter EQU exists for subtype "+std::to_string(subtype));
            const int uid=p.state.at("next_uid").get<int>(),index=int(p.state.at("inventory").size());
            p.state["next_uid"]=uid+1;p.state["inventory"].push_back({{"uid",uid},{"id",itemId},{"count",1},{"durability",item->durability}});
            if(subtype==3) {
                // This exact starter glove has unimplemented permission/effect
                // consumers. Preserve its refusal; source geometry is separate.
                const auto exactField=[&](const char *tag,size_t offset,const Json &values) {
                    size_t count=0;bool exact=false;
                    for(const auto &field:item->source.fields)if(normalize(field.tag)==tag) {
                        ++count;exact=field.offset==offset&&field.values==values;
                    }
                    return count==1&&exact;
                };
                check(itemId==30200&&item->source.path=="equipment/character/fighter/weapon/boxglove/bglove_waprrentice.equ"&&
                    sha256(item->source.rawBytes)=="165febf01dbb1b53495912e339cd078b9151fbbb609e8aea461863d798cf6d21"&&
                    item->source.source.value("package_identity",std::string())==pvf.identity()&&
                    exactField("[required skill]",487,Json::array({34}))&&exactField("[if]",497,Json::array())&&
                    exactField("[cooltime]",502,Json::array({4000}))&&exactField("[attack success]",512,Json::array({1}))&&
                    exactField("[/if]",522,Json::array())&&exactField("[then]",527,Json::array())&&
                    exactField("[target]",532,Json::array({"enemy",-1}))&&exactField("[duration]",547,Json::array({2000}))&&
                    exactField("[probability]",557,Json::array({2}))&&exactField("[active status]",567,Json::array({"stun",18}))&&
                    exactField("[/then]",582,Json::array())&&w.skillState().learnedLevel({1,34})==0,
                    "Only exact real30200 required34 and conditional stun source enter the expected refusal fixture; no permission is granted");
                const auto normalizedLive=[&]() {
                    auto value=upperLive(w,p);value["world"]["stats"].erase("last_equipment_change");return value;
                };
                const auto before=normalizedLive();const auto rejected=w.changeEquipment(p,index);
                const auto diagnostic=w.statReport().at("last_equipment_change");
                check(!rejected.ok&&normalizedLive()==before&&diagnostic.at("status")=="rejected"&&
                    diagnostic.at("phase")=="inventory_qualification"&&
                    diagnostic.value("error",std::string()).find("equipment_required_skill_rejected: ")==0&&
                    diagnostic.value("error",std::string()).find("\"gate\":\"not_learned\"")!=std::string::npos&&
                    diagnostic.value("error",std::string()).find("\"skill_id\":34")!=std::string::npos&&
                    diagnostic.value("error",std::string()).find("Normal ledger does not own the required skill")!=std::string::npos,
                    "Real30200 rejects at normal own34 inventory qualification and preserves all live state except its explicit equipment diagnostic");
                auto raw=defaultCharacterAppearance(pvf,w.characterCatalog(),w.identity());
                check(applyEquipmentAppearance(raw,item->source,w.characterSource().job),
                    "Read-only real30200 source appearance applies only to a private raw geometry descriptor");
                bindEquipmentMotions(pvf,raw);const auto source=readCharacterAttackMotion(assets,raw,d.motion.memberPath);
                check(source.body&&source.body->path==body->path&&source.body->frames.size()==6&&source.body->duration==740&&source.weapons.size()==2&&std::all_of(source.weapons.begin(),source.weapons.end(),[](const auto &a){return a->frames.size()==6&&a->duration==1370;}),
                    "Private real30200 EQU/LAY retains both raw1370ms weapon layers and the original740ms six-frame body");
                const auto boxes=[](const std::vector<Box> &values) {
                    Json out=Json::array();for(const auto &box:values)out.push_back({box.type,box.x,box.y,box.z,box.w,box.h,box.d});return out;
                };
                Json geometry=Json::array();
                for(size_t frame=0;frame<body->frames.size();++frame) {
                    std::vector<Box> expected;
                    for(const auto &box:body->frames[frame].boxes)if(box.type==15)expected.push_back(box);
                    for(const auto &weapon:source.weapons)for(const auto &box:weapon->frames[frame].boxes)if(box.type==15)expected.push_back(box);
                    check(boxes(source.boxesAt(frame))==boxes(expected),
                        "Private real30200 geometry reads exact body plus both original weapon type15 boxes for frame "+std::to_string(frame));
                    geometry.push_back({{"frame",frame},{"boxes",boxes(expected)}});
                }
                AnimationPlayback timeline;timeline.install(*body,false,100,clock,0);std::set<size_t> visits;
                for(uint64_t tick=0;tick<=90;++tick) {
                    const auto &snapshot=timeline.snapshot();visits.insert(snapshot.frame);
                    for(const auto &weapon:source.weapons)check(weapon->followClock(*body,snapshot,false).frame==snapshot.frame,
                        "Private real30200 weapon follows every body clock frame without installing an equipped World consumer");
                    check(boxes(source.boxesAt(snapshot))==boxes(source.boxesAt(size_t(snapshot.frame))),
                        "Private real30200 clock geometry agrees with exact source frame geometry");
                    timeline.advance(tick+1,false);
                }
                check(visits==std::set<size_t>({0,1,2,3,4,5})&&normalizedLive()==before,
                    "Private real30200 source-only six-frame traversal preserves live World, ledger, MP-CD, RNG, slots and progression");
                evidence.push_back({{"phase","real30200-rejected-atomic"},{"clock",policy},{"equipment",itemId},
                    {"diagnostic",diagnostic},{"permission34_granted",false},{"runtime_equipped",false}});
                evidence.push_back({{"phase","real30200-source-geometry-only"},{"clock",policy},{"equipment",itemId},
                    {"motion",source.json()},{"frames",visits},{"geometry",geometry},{"runtime_equipped",false}});
                continue;
            }
            check(w.changeEquipment(p,index).ok,"Actual EQU/LAY transaction equips female preview subtype "+std::to_string(subtype));
            const auto composed=readCharacterAttackMotion(assets,w.characterAppearance(),d.motion.memberPath);
            check(composed.weapons.size()==2&&std::all_of(composed.weapons.begin(),composed.weapons.end(),[](const auto &a){return a->frames.size()==6&&a->duration==1370;}),
                "Both real weapon layers preserve raw1370ms timelines; body remains740ms");
            for(const int level:{1,10})for(const int direction:{-1,1})for(const bool contact:{false,true}) {
                upperRest(w);upperArena(w);r.publishCooldownRestore({});r.configuration().configureSourceSkillAction(upper,level,plan);r.configuration().assignSlot(0,upper,plan);w.player.dir=direction;
                w.player.mp=100000;w.randomStreams()=RandomStreams(0x1031);const auto ledger=w.skillState().snapshot(w.nowMs());
                if(contact)for(int id=1;id<=3;++id)upperTarget(w,id,direction,*first);
                const auto started=w.nowMs();const int mp=w.player.mp;upperCast(w);const auto cost=r.snapshotDiagnostics().at("last_cost");
                check(r.attacking()&&mp-w.player.mp==cost.at("mp").at("value").get<int>()&&w.armor()&&!w.invincible(),
                    "Actual source slot uses equipped MP and explicit first-frame armor without invincibility");
                std::set<size_t> frames;bool volume=false,launch=false,unarmored=false,ownReaction=false,layer=false;
                int64_t completedMs=-1;
                const auto operands=evaluateSourceSkillAction(d,*plan.skills.at(upper).data,level);
                check(operands.bodyLift&&operands.attackSpeedBonusPermille==*skillLevelValue(plan.skills.at(upper).data->values("[level info]"),level,0)*10,
                    "Real selected level drives source speed0 and force2 operands");
                for(int tick=0;tick<120;++tick) {
                    if(r.attacking()&&w.player.animationClock){const auto frame=size_t(w.player.animationClock->frame);frames.insert(frame);
                        if(frame>0)unarmored|=!w.armor();
                        for(const auto &weapon:composed.weapons)check(weapon->followClock(*body,*w.player.animationClock,false).frame==frame,
                            "Live root740ms clock consumes same weapon frame including4/5 without extending to1370ms");}
                    layer|=!w.player.skillAnimationLayers.empty();
                    for(const auto &v:w.attackVolumes)if(v.skillId==5){volume=true;check(v.sourceAttack&&v.sourceAttack->source.path==d.attack.memberPath&&v.sourceModifiers&&
                        v.sourceModifiers->percent==operands.damage.percent&&v.sourceModifiers->independentPercent==operands.damage.independentPercent&&v.sourceModifiers->fixedDamage==0,
                        "Actual body/equipment volumes carry separate own source percent1 and independent3 through unified damage");}
                    for(const auto &m:w.monsters){launch|=m.vz>0;ownReaction|=m.animationPath.rfind("monster/goblin/",0)==0;}
                    w.advanceSingleTick();if(completedMs<0&&!r.attacking())completedMs=w.nowMs()-started;
                }
                if(!contact&&clock==ani_clock::ClockPolicy::SourceDelay100)
                    check(completedMs>=740&&completedMs<=774,"Actual empty raw-delay action completes on body740ms, never weapon1370ms");
                const auto contacts=std::count_if(w.events.begin(),w.events.end(),[](const Event &e){return (e.kind=="hit"&&e.name=="experimental_source_skill")||e.kind=="miss";});
                check(volume&&layer&&unarmored&&frames.count(4)&&frames.count(5)&&contacts==(contact?3:0)&&(!contact||(launch&&ownReaction)),
                    "All six body and real weapon frames execute, targets de-duplicate once, and nonmiss launches actual own MOB animation");
                check(upperSound(w,"FT_UPPER_READY")==1&&upperSound(w,"FT_UPPER_SWING")==1&&!r.attacking()&&
                    w.player.skillAnimationLayers.empty()&&w.skillState().snapshot(w.nowMs())==ledger,
                    "Held/multiple attack frames do not repeat audio or mutate normal ledger; action and layers retire");
                evidence.push_back({{"phase","real-four-weapons"},{"clock",policy},{"equipment",itemId},{"level",level},
                    {"direction",direction},{"contact",contact},{"cost",cost},{"contacts",contacts},{"frames",frames}});
            }
        }
        // Hitstop pauses the action-local cue; accepted MP/CD stay paid.
        upperRest(w);upperArena(w);r.publishCooldownRestore({});r.configuration().configureSourceSkillAction(upper,1,plan);r.configuration().assignSlot(0,upper,plan);upperCast(w);
        const int stoppedMp=w.player.mp;const auto stoppedFrame=w.player.animationClock->frame;
        w.player.hitStopTicks=25;upperTicks(w,25);
        check(r.attacking()&&w.player.animationClock->frame==stoppedFrame&&w.player.mp==stoppedMp&&upperSound(w,"FT_UPPER_SWING")==0,
            "Actual World hitstop holds the blank/windup and cannot emit future attack cue or repay costs");
        upperTicks(w,100);
        check(!r.attacking()&&w.player.mp==stoppedMp&&upperSound(w,"FT_UPPER_READY")==1&&upperSound(w,"FT_UPPER_SWING")==1,
            "Resumed action reaches its first real body attack cue exactly once after hitstop");
        // Failure/exit tests observe the concrete adapter and all transactional consumers.
        for(const std::string reason:{"cancel","scene","death","blocked"}) {
            upperRest(w);upperArena(w);r.publishCooldownRestore({});r.configuration().configureSourceSkillAction(upper,1,plan);r.configuration().assignSlot(0,upper,plan);upperCast(w);
            check(r.attacking()&&upperSound(w,"FT_UPPER_READY")==1&&upperSound(w,"FT_UPPER_SWING")==0,"Exit starts before first source attack cue");
            if(reason=="cancel")w.idle();else if(reason=="scene")w.changeScene();else if(reason=="blocked")w.player.stunUntil=w.nowMs()+1000;else {w.player.dead=true;w.player.life=ActorLife::Dying;}
            upperTicks(w,90);
            check(!r.attacking()&&!w.armor()&&w.player.skillAnimationLayers.empty()&&upperSound(w,"FT_UPPER_SWING")==0,
                "Cancellation/scene/death/control clears pending attack cue and layers without late SWING: "+reason);
        }
        for(const std::string fault:{"missing_visual","malformed_response","audio_association"}) {
            upperRest(w);upperArena(w);auto changed=std::make_shared<ExperimentalCharacterPlan>(plan);auto &a=changed->sourceSkillActions.at(upper);
            std::string expected;
            if(fault=="missing_visual"){a.bodyLayers[0].source.memberPath="missing/female-upper.ani";expected="Missing PVF: missing/female-upper.ani";}
            else if(fault=="audio_association"){a.attackSound="NO_REVIEWED_FEMALE_UPPER_SWING";expected="Reviewed female Upper audio association changed";}
            else {
                size_t count=0;
                for(auto &f:a.attackDefinition.source.fields)if(normalize(f.tag)=="[push aside]") {
                    check(f.values==Json::array({130}),"Malformed-response fixture starts from the actual female Upper push130 source field");
                    f.values=Json::array({"__FIGHTER_UPPER_TEST_NOT_A_NUMBER"});++count;
                }
                check(count==1,"Malformed-response fixture corrupts exactly one existing numeric push130 source field");
                expected="Invalid experimental ATK response number";
            }
            ExperimentalCharacterRuntime injected(changed);injected.setAnimationClockPolicy(clock);injected.configuration().configureSourceSkillAction(upper,1,*changed);injected.configuration().assignSlot(0,upper,*changed);
            const auto rng=w.randomStreams().snapshot();auto ids=w.idSources().snapshot();ids.erase("requests");const int mp=w.player.mp;
            CharacterActionRequest request;request.action=CharacterAction::CommandInput;request.inputKey=20;request.inputDown=true;request.simulationMs=w.nowMs();check(injected.request(request),"Fault fixture uses actual configured input");
            ExperimentalWorldAdapter adapter(w);adapter.advance(injected,uint64_t(w.tick)+1);auto afterIds=w.idSources().snapshot();afterIds.erase("requests");
            const auto diagnostics=w.experimentalDiagnostics().at("world");
            check(std::any_of(diagnostics.begin(),diagnostics.end(),[&](const Json &row){return row.value("code",std::string())=="experimental_attack_source_preflight_rejected"&&row.value("message",std::string())==expected;}),
                "Actual adapter reaches requested private preflight failure, not earlier qualification: "+fault);
            check(w.player.mp==mp&&!injected.attacking()&&injected.remainingCooldown(upper,w.nowMs())==0&&w.randomStreams().snapshot()==rng&&ids==afterIds&&
                upperSound(w,"FT_UPPER_READY")==0&&upperSound(w,"FT_UPPER_SWING")==0&&w.player.skillAnimationLayers.empty(),
                "Failed source/audio preparation publishes no MP/CD/audio/RNG/IDs/action/layer: "+fault);
        }
        const auto schedule=[&](int fps,bool catchup) {
            CharacterStore c(root/(policy+"-schedule"+std::to_string(fps)),"fighter-upper-test");c.data=upperRoot(4);
            World sim(pvf,assets,WorldRules::BetaFoundationV1);sim.enableExperimentalCharacters();Progression progress(regions);c.apply(0,sim,progress);
            upperRest(sim);check(sim.assignLearnedSkillSlot(0,upper).ok,"Schedule uses actual normally learned Upper1");upperArena(sim);sim.configureAnimationClock(clock);sim.randomStreams()=RandomStreams(0x1031);upperTarget(sim,1,1,*first);
            sim.enqueue({0,20,true});sim.enqueue({16666667,20,false});Json rows=Json::array();
            sim.setObjectTick([&](World &current){rows.push_back({{"tick",current.tick},{"mp",current.player.mp},{"runtime",current.experimentalRuntime()->snapshotDiagnostics()},
                {"hp",current.monsters[0].hp},{"monster_position",{current.monsters[0].x,current.monsters[0].y,current.monsters[0].z}},
                {"monster_ani",current.monsters[0].animationPath},{"events",current.eventLog()},{"rng",current.randomStreams().snapshot()}});});
            constexpr int64_t total=2000000000;int64_t previous=0;
            if(catchup){sim.advance(total,8);while(sim.pendingTicks())sim.advance(0,8);}
            else for(int n=1;n<=fps*2;++n){const int64_t now=total*n/(fps*2);sim.advance(now-previous);previous=now;}
            check(sim.tick==120&&!sim.pendingTicks(),"Cadence completes all fixed60Hz simulation ticks");return rows;
        };
        const auto canonical=schedule(60,false);check(schedule(30,false)==canonical&&schedule(144,false)==canonical&&schedule(1,true)==canonical,
            "Actual normal Upper/monster/audio/MP-CD/RNG timeline agrees at30/60/144 render pumping and budget8 catchup");
        store.close();
    }
    // Genuine legacy history, not a new grant: retain unsupported learned TP
    // and reject Upper before fees instead of silently discarding the modifier.
    {
        CharacterStore store(root/"legacy163","fighter-upper-test");store.data=upperRoot(50);
        World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);upperRest(w);
        check(w.assignLearnedSkillSlot(0,upper).ok,"Legacy fixture begins with actual normally assigned source Upper");
        auto imported=w.skillState().snapshot(w.nowMs());imported.erase("learning");for(auto &record:imported["skills"])if(SkillKey::fromJson(record.at("key"))==upper)record["level"]=10;
        imported["skills"].push_back({{"key",upperTp.json()},{"level",1},{"remaining_cooldown_ms",0}});
        CharacterSkillState raw(w.identity());raw.restore(imported,w.nowMs());const auto migrated=w.skillLearning().prepareInitialization(raw,50,SkillInitializationMode::LegacyImport,w.nowMs());
        check(migrated.ok,"Legacy TP fixture uses real source-bound import initialization");w.publishSkillLedger(migrated.state);const auto normal=w.skillState().snapshot(w.nowMs());
        const auto gate=w.skillUseEligibility(upper);
        check(gate.gate==SkillLearningGate::SpecialQualification&&gate.error.find("163")!=std::string::npos&&
            w.skillLearningConsumerMetadata(upper).at("normal_release_blocker")==gate.error&&w.skillState().learnedLevel(upperTp)==1,
            "Already learned163 produces concrete base5 pre-cost diagnostic while preserving original history");
        upperArena(w);const int mp=w.player.mp;const auto rng=w.randomStreams().snapshot();upperCast(w);upperTicks(w,50);
        check(!w.experimentalRuntime()->attacking()&&w.player.mp==mp&&w.experimentalRuntime()->remainingCooldown(upper,w.nowMs())==0&&
            upperSound(w,"FT_UPPER_READY")==0&&upperSound(w,"FT_UPPER_SWING")==0&&w.randomStreams().snapshot()==rng&&w.skillState().snapshot(w.nowMs())==normal,
            "Preassigned normal slot cannot bypass TP163 diagnostic, consume fee/audio/random or erase ledger");
        upperRest(w);store.capture(0,w,p);store.checkpoint();World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();Progression rp(regions);store.apply(0,restored,rp);
        check(restored.skillState().snapshot(restored.nowMs())==normal&&restored.skillUseEligibility(upper).gate==SkillLearningGate::SpecialQualification,
            "Unsupported TP163 and exact Upper blocker survive actual same-generation reload");store.close();
    }
    for(int branch:{1,2,3,4}) {
        CharacterStore store(root/("gsd"+std::to_string(branch)),"fighter-upper-test");store.data=upperRoot(50);
        World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();Progression p(regions);store.apply(0,w,p);upperRest(w);
        check(w.assignLearnedSkillSlot(0,upper).ok,"Own initial normal Upper binds before GSD transition");
        const auto quote=w.quoteSkillLearning(upper,50);SkillLearningTransaction purchase;
        check(quote.accepted()&&purchase.submit(store,0,w,p,{"upper-before-gsd2",upper,quote.revision,2},Json::object()).ok,"Paid normal Upper2 exists before source GSD branch rebase");
        const auto ledger=w.skillState().snapshot(w.nowMs()),budget=w.skillLearningBudget(false,50).json();
        for(int awakening:{0,1}) {
            const CharacterIdentity destination{1,branch,awakening};const auto scene=upperTrainer(w);
            CharacterAdvancementTransaction transaction;CharacterAdvancementRequest request{"upper-gsd"+std::to_string(branch)+"-"+std::to_string(awakening),w.identity(),destination,
                store.generation(),w.advancementCatalog().trainerId()};const auto result=transaction.submit(store,0,w,p,scene,request,Json::object());
            check(result.ok,"Actual source GSD advancement/awakening accepts legal female branch");auto current=w.skillState().snapshot(w.nowMs());current["identity"]=ledger.at("identity");
            check(current==ledger&&w.skillLearningBudget(false,50).json()==budget&&w.skillUseEligibility(upper).allowed()&&
                w.experimentalRuntime()->configuration().binding(upper)->level==2&&w.experimentalRuntime()->configuration().slots()[0]==std::optional<SkillKey>(upper),
                "Actual GSD rebase preserves own paid Upper2/slot/budget without additional initial or TP grants");
        }
        World loaded(pvf,assets,WorldRules::BetaFoundationV1);loaded.enableExperimentalCharacters();Progression lp(regions);store.apply(0,loaded,lp);
        check(loaded.identity()==w.identity()&&loaded.skillState().snapshot(loaded.nowMs())==w.skillState().snapshot(w.nowMs())&&loaded.skillUseEligibility(upper).allowed(),
            "Actual awakened save reload preserves normally learned Upper and source qualification");store.close();
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"evidence",evidence},{"save_directory",root.u8string()},
        {"normal_base_5_consumer_bound",true},{"tp_163_normal_admitted",false},{"native_parity",false},
        {"scope","Own female Upper normal learning/cost/save, source equipment/contact comparisons and exact exit/fault/cadence consumers; ACT active reaction in runActCollisionTests; no frontend/native comparison claim"}};
    } catch(const std::exception &error) {
        writeJson("fighter-upper-exception.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence},{"save_directory",root.u8string()}});throw;
    }
}
} // namespace dnf
