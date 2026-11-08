#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/storage.hpp"
#include "dnf/character_attack.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace dnf {
// Integration overlay proposal, not compiled/run. Requires the five-file
// frozen Knee runtime patch and an isolated, fully rebuilt dnf_tests closure.
Json runGunnerKneeRuntimeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message){checks.push_back({{"passed",pass},{"message",message}});
        if(!pass)throw std::runtime_error(message);};
    const auto countEvent=[](const World &w,const std::string &kind){return std::count_if(w.events.begin(),w.events.end(),
        [&](const Event &event){return event.kind==kind;});};
    try {
    RegionCatalog regions(pvf,assets);const SkillKey key{2,4};
    {
        RandomStreams random(1031);auto &combat=random.stream(RandomDomain::Combat,1);(void)combat.next();
        auto &ai=random.stream(RandomDomain::Ai,2);(void)ai.next();const auto combatState=combat.snapshot(),aiState=ai.snapshot();
        auto *combatAddress=&combat;auto *aiAddress=&ai;auto prepared=random;
        (void)prepared.stream(RandomDomain::Audio,3).bounded(100);random.publishPreparedAudio(std::move(prepared));
        check(&random.stream(RandomDomain::Combat,1)==combatAddress && &random.stream(RandomDomain::Ai,2)==aiAddress&&
            combat.snapshot()==combatState&&ai.snapshot()==aiState,
            "Prepared Audio publication preserves unrelated live RNG state and node references");
        RandomStreams restored;restored.restore(random.snapshot());
        check(restored.stream(RandomDomain::Audio,3).bounded(100)==random.stream(RandomDomain::Audio,3).bounded(100),
            "Saved named Audio random stream resumes its next choice exactly");
    }
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("gunner-knee-"+std::string(ani_clock::policyName(clock))));
        store.data["characters"][0]={{"name","SourceGunner"},{"class","gunner"},{"identity",CharacterIdentity{2,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clock);
        auto &r=*world.experimentalRuntime();const auto &plan=r.plan();
        check(world.experimentalSkillPreviewEnabled()&&world.runtimeSkillPolicy(key).implemented,
            "Knee operand/comparison tests explicitly use preview separately from the admitted normal source consumer");
        check(world.hasLearningLedger()&&world.skillState().learnedLevel(key)==1,
            "Real source-v1 CharacterStore creation grants own Gunner skill4 level1 before configuring any test slot");
        check(plan.sourceSkillActions.size()==1&&plan.sourceSkillActions.count(key),"Exactly one reviewed Gunner Knee action is admitted");
        const auto &d=plan.sourceSkillActions.at(key);const auto body=assets.animation(d.motion.memberPath);
        check(d.kind==SourceSkillActionKind::BodyAttack&&d.inferredNativeBody&&d.motionSlot==11&&d.attackSlot==1&&d.state==-1,
            "Own source registration resolves motion11/ATK1 with unknown state rather than importing a later NUT enum");
        check(d.registration.memberPath.empty()&&d.callback.memberPath.empty()&&d.objectId==-1,
            "Gunner Knee does not claim an absent own NUT registration/callback/passive entity");
        check(body->frames.size()==5&&body->duration==750&&d.bodyLayers.size()==1&&d.recoveryMs==0,
            "Source body timeline, one explicit inferred visual and absence of invented recovery are preserved");
        check(d.sourceFrameSuperArmor&&!d.requiresEquippedAttackVolume&&body->frames[0].properties.at("13")==1,
            "Only own reviewed frame protection policy is enabled; Knee uses real body geometry without requiring a weapon box");
        const auto composed=readCharacterAttackMotion(assets,world.characterAppearance(),d.motion.memberPath);
        std::optional<Box> first;
        for(size_t f=0;f<body->frames.size();++f)for(const auto &box:composed.boxesAt(f))if(!first)first=box;
        check(!composed.weapons.empty()&&first.has_value(),"Actual default inventory EQU/LAY resolves own weapon layers alongside source body contact");
        evidence.push_back({{"phase","sources"},{"descriptor",d.snapshot()},{"equipment",composed.json()}});
        for(const int level:{1,10,50}) {
            const auto table=plan.skills.at(key).data->values("[level info]");const auto o=evaluateSourceSkillAction(d,*plan.skills.at(key).data,level);
            check(o.damage.percent==float(*skillLevelValue(table,level,0))&&o.damage.independentPercent==float(*skillLevelValue(table,level,3))&&o.damage.fixedDamage==0,
                "Own percent0/independent3 are consumed without treating independent33 as flat damage at level "+std::to_string(level));
            check(o.bodyLift&&*o.bodyLift==*skillLevelValue(table,level,2)&&o.attackSpeedBonusPermille==*skillLevelValue(table,level,1)*10,
                "Actual selected level drives optional body lift2 and percent-speed1 consumers");
        }
        const auto floor=[&](){world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();r.publishCooldownRestore({});
            world.combat=true;world.freezeAi=true;world.freeCd=false;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};world.blockedRects.clear();
            auto &p=world.player;p.x=p.px=600;p.y=p.py=300;p.z=p.pz=0;p.vx=p.vy=p.vz=0;p.mp=100000;
            p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;};
        const auto configure=[&](int level){r.configuration().configureBasicAttackTemplate(key,level,plan);r.configuration().assignSlot(0,key,plan);};
        const auto press=[&](bool down){world.enqueue({world.simulationNanoseconds(),20,down});};
        const auto playerFrame=[&](){return world.player.animationClock?size_t(world.player.animationClock->frame):
            size_t(std::max(0,world.player.poseFrame));};
        const auto target=[&](int index,int direction){Actor a;a.id=index+1;a.sourceId=10;a.monsterPath="monster/goblin/goblin.mob";
            a.x=a.px=600+direction*(first->x+first->w*.5);a.y=a.py=300+first->y+first->h*.5;a.dir=-direction;
            world.initializeMonsterAttributes(a,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");a.hp=a.maxHp=100000000;
            world.monsters.push_back(std::move(a));};
        const SkillKey tpKey{2,168};const auto &tpRow=plan.skills.at(tpKey);
        check(!world.runtimeSkillPolicy(tpKey).implemented&&world.runtimeSkillPolicy(key).implemented,
            "TP remains independently disabled after admitting only the reviewed normal base Knee consumer");
        for(const int tpLevel:{0,1,5}) {
            const auto baseline=plan.skills.at(key).data->snapshot(true);
            const auto upgraded=evaluateSourceSkillActionTp(d,*plan.skills.at(key).data,10,tpKey,tpRow.source,*tpRow.data,tpLevel);
            const auto plain=evaluateSourceSkillAction(d,*plan.skills.at(key).data,10);
            check(upgraded.damage.percent==float(317*(1+8.0*tpLevel/100))&&
                upgraded.damage.independentPercent==float(66*(1+8.0*tpLevel/100))&&
                upgraded.attackSpeedBonusPermille==plain.attackSpeedBonusPermille&&upgraded.bodyLift==plain.bodyLift&&
                plan.skills.at(key).data->snapshot(true)==baseline,
                "Own TP168 changes only source base-level10 attack columns0/3; immutable source, speed and lift remain exact");
            check(evaluateSourceSkillActionTp(d,*plan.skills.at(key).data,10,tpKey,tpRow.source,*tpRow.data,tpLevel).damage.percent==upgraded.damage.percent,
                "Reevaluating TP from immutable source never compounds a prior application");
        }
        for(int kind=0;kind<3;++kind) {
            bool rejected=false;auto source=tpRow.source;
            if(kind==0)source.memberSha256="stale";
            try{(void)evaluateSourceSkillActionTp(d,*plan.skills.at(key).data,kind==1?9:10,tpKey,source,*tpRow.data,kind==2?6:1);}catch(...){rejected=true;}
            check(rejected,"TP rejects stale source, insufficient real base prerequisite or level beyond purchase ceiling");
        }
        std::map<int,int> tpDamage;
        for(const int tpLevel:{0,1,5}) {
            floor();configure(10);r.configuration().configureSourceActionPassive(tpKey,tpLevel,plan);target(0,1);
            world.player.dir=1;world.synchronizeEntityHandles();world.randomStreams()=RandomStreams(0x1031);
            const auto normal=world.skillState().snapshot(world.nowMs());
            auto savedTp=r.configuration().snapshot();savedTp["future_passive_unknown"]=71;
            ExperimentalSkillConfiguration restoredTp(plan);restoredTp.restore(savedTp,plan);
            check(restoredTp.snapshot()==savedTp&&restoredTp.sourceActionPassiveLevel(tpKey)==tpLevel,
                "Exact source-bound TP levels and unknown fields survive configuration restoration");
            press(true);world.advanceSingleTick();press(false);bool saw=false;
            for(int tick=0;tick<100;++tick) {
                for(const auto &volume:world.attackVolumes)if(volume.skillId==4&&volume.sourceModifiers) {
                    saw=true;check(volume.sourceModifiers->percent==float(317*(1+8.0*tpLevel/100))&&
                        volume.sourceModifiers->independentPercent==float(66*(1+8.0*tpLevel/100)),
                        "Actual input/runtime/body volume consumes separately configured source TP level");
                }
                world.advanceSingleTick();
            }
            tpDamage[tpLevel]=world.monsters[0].maxHp-world.monsters[0].hp;
            check(saw&&tpDamage[tpLevel]>0&&world.skillState().snapshot(world.nowMs())==normal,
                "TP preview reaches real monster HP while preserving normal learned/purchase ledger");
            if(tpLevel>0)check(world.statReport().at("last_damage").dump().find("inferred-current1031-knee-tp-linear-base-overlay-v1")!=std::string::npos,
                "Final accepted damage receipt retains TP source/cell/level evidence");
            evidence.push_back({{"phase","source_tp_world"},{"tp_level",tpLevel},{"hp_loss",tpDamage[tpLevel]},
                {"configuration",savedTp},{"last_damage",world.statReport().at("last_damage")}});
        }
        check(tpDamage[5]>tpDamage[1]&&tpDamage[1]>tpDamage[0],"Actual source TP1/5 monotonically increase accepted unified HP damage");
        r.configuration().clearSkillBinding(tpKey);
        check(r.configuration().sourceActionPassiveLevel(tpKey)==0,"Removing source TP projection removes its consumer level");
        // Audio comparison explicitly opt-in; normal projection strips it.
        const auto voices=[&](){return std::count_if(world.events.begin(),world.events.end(),[](const Event &e){return e.kind=="sound"&&
            (e.name=="GN_JACKSPIKE_01"||e.name=="GN_JACKSPIKE_02");});};
        const auto swings=[&](){return std::count_if(world.events.begin(),world.events.end(),[](const Event &e){return e.kind=="sound"&&e.name=="JACKSPIKE_SWING";});};
        floor();configure(1);r.configuration().setSourceActionAudioPolicy("inferred-current1031-knee-cast-audio-v1",plan);
        const auto audioNormal=world.skillState().snapshot(world.nowMs());const auto beforeAudio=world.randomStreams().snapshot();
        press(true);world.advanceSingleTick();press(false);
        check(voices()==1&&swings()==1&&world.randomStreams().snapshot()!=beforeAudio,
            "Accepted empty cast publishes one resolved own voice and swing with saved Audio random receipt");
        const auto audioAfter=world.randomStreams().snapshot();const auto diagnostic=world.experimentalDiagnostics().dump();
        for(int n=0;n<100;++n)world.advanceSingleTick();
        check(voices()==1&&swings()==1&&world.randomStreams().snapshot()==audioAfter&&
            diagnostic.find("inferred-current1031-knee-cast-audio-v1")!=std::string::npos,
            "Held source frames never repeat accepted cast audio or consume extra random");
        const auto continuation=world.randomStreams().snapshot();RandomStreams resumed;resumed.restore(continuation);
        const auto expectedNext=resumed.stream(RandomDomain::Audio,0).bounded(100);
        world.idle();r.publishCooldownRestore({});press(true);world.advanceSingleTick();press(false);
        check(voices()==2&&swings()==2&&world.randomStreams().snapshot()==resumed.snapshot(),
            "Next accepted cast continues the saved Audio stream without restoring or rerolling prior cast");
        evidence.push_back({{"phase","source_audio_continuation"},{"next_roll",expectedNext},{"events",world.eventLog()},
            {"random",world.randomStreams().snapshot()}});
        floor();configure(1);world.player.mp=0;const auto failedAudio=world.randomStreams().snapshot();press(true);world.advanceSingleTick();press(false);
        check(voices()==0&&swings()==0&&world.randomStreams().snapshot()==failedAudio,
            "MP-rejected cast has no source audio or Audio random consumption");
        check(world.skillState().snapshot(world.nowMs())==audioNormal,"Audio comparison never changes normal learning ledger");
        r.configuration().setSourceActionAudioPolicy("disabled",plan);
        floor();configure(1);const auto disabledAudio=world.randomStreams().snapshot();press(true);world.advanceSingleTick();press(false);
        check(voices()==0&&swings()==0&&world.randomStreams().snapshot()==disabledAudio,
            "Default disabled comparison keeps prior source behavior and does not instantiate an Audio stream");
        for(const auto *fault:{"malformed_response","missing_visual"}) {
            floor();auto changed=std::make_shared<ExperimentalCharacterPlan>(plan);auto &action=changed->sourceSkillActions.at(key);
            if(std::string(fault)=="malformed_response") {
                size_t count=0;for(auto &field:action.attackDefinition.source.fields)if(normalize(field.tag)=="[hit wav]") {field.values=Json::array({42});++count;}
                check(count==1,"Audio fault diagnostic replaces exactly actual own hit-wav field");
            } else action.bodyLayers.front().source.memberPath="character/gunner/effect/animation/__missing_knee_audio.ani";
            ExperimentalCharacterRuntime injected(changed);injected.setAnimationClockPolicy(clock);
            injected.configuration().configureSourceSkillAction(key,1,*changed);injected.configuration().assignSlot(0,key,*changed);
            injected.configuration().setSourceActionAudioPolicy("inferred-current1031-knee-cast-audio-v1",*changed);
            CharacterActionRequest request;request.action=CharacterAction::CommandInput;request.inputKey=20;request.inputDown=true;
            request.simulationMs=world.nowMs();check(injected.request(request),"Audio failure fixture uses actual input and explicit source comparison");
            const auto rng=world.randomStreams().snapshot();const auto mp=world.player.mp;ExperimentalWorldAdapter adapter(world);
            adapter.advance(injected,uint64_t(world.tick)+1);
            check(world.player.mp==mp&&!injected.attacking()&&injected.remainingCooldown(key,world.nowMs())==0&&
                voices()==0&&swings()==0&&world.randomStreams().snapshot()==rng,
                "Visual/response fault before audio preparation publishes no audio events/random or MP/CD/action");
        }
        std::map<int,int> sourceRates,sourceLaunches;
        // Source grant is used as a real consumer input; manually configuring
        // its slot still does not establish the pending normal-learning bridge.
        floor();configure(world.skillState().learnedLevel(key));
        auto saved=r.configuration().snapshot();saved["future_knee_unknown"]=31;
        ExperimentalSkillConfiguration restored(plan);restored.restore(saved,plan);
        check(restored.snapshot()==saved,"Source descriptor and unknown future test configuration survive exact restore");
        auto stale=saved;stale["skill_bindings"][0]["source_body_action_controller"]["motion_slot"]=0;
        bool rejected=false;try{ExperimentalSkillConfiguration invalid(plan);invalid.restore(stale,plan);}catch(...){rejected=true;}
        check(rejected,"Restoring a stale/replaced Knee source descriptor is rejected");
        for(int level:{1,10})for(int direction:{-1,1})for(bool contact:{false,true}) {
            floor();configure(level);world.player.dir=direction;const auto normal=world.skillState().snapshot(world.nowMs());
            const auto binding=r.configuration().binding(key);
            check(binding&&binding->unknown.contains("source_body_action_controller")&&!binding->unknown.contains("user_requested_temporary_template"),
                "Actual skill slot dispatches Knee own source action instead of a basic-attack template");
            if(contact)for(int n=0;n<3;++n)target(n,direction);
            world.synchronizeEntityHandles();const auto mp=world.player.mp;press(true);world.advanceSingleTick();press(false);
            const auto cost=r.snapshotDiagnostics().at("last_cost");
            sourceRates[level]=r.snapshotDiagnostics().at("animation_clock").at("rate_percent").get<int>();
            check(mp-world.player.mp==cost.at("mp").at("value").get<int>()&&
                r.remainingCooldown(key,world.nowMs())==int64_t(std::ceil(cost.at("cooldown_ms").at("value").get<double>())),
                "Accepted actual input publishes exact source MP/CD using current equipped cost modifiers");
            check(world.player.animationClock&&world.player.poseFrame==-1&&world.player.animationClockSource==d.motion.memberPath,
                "Accepted Knee publishes its actual body clock; poseFrame remains the unfrozen sentinel");
            check(world.armor()&&!world.invincible(),"Accepted first Knee pose has super armor without granting invincibility");
            bool pose=false,volume=false,layer=false,launched=false,armorExited=false;double acceptedLift=0;
            for(int tick=0;tick<90;++tick) {
                pose|=world.player.animationPath==d.motion.memberPath;layer|=world.player.skillAnimationLayers.size()==1;
                if(r.attacking()&&playerFrame()>0)armorExited|=!world.armor();
                for(const auto &v:world.attackVolumes)if(v.skillId==4){volume=true;
                    check(v.sourceAttack&&v.sourceAttack->source.path==d.attack.memberPath&&v.sourceModifiers&&
                        v.sourceModifiers->percent==float(*skillLevelValue(plan.skills.at(key).data->values("[level info]"),level,0))&&
                        v.sourceModifiers->independentPercent==float(*skillLevelValue(plan.skills.at(key).data->values("[level info]"),level,3))&&v.sourceModifiers->fixedDamage==0,
                        "Real body attack volume carries own ATK and separate current-level damage coefficients");}
                for(const auto &a:world.monsters)if(a.vz>0){launched=true;acceptedLift=std::max(acceptedLift,a.vz);}
                world.advanceSingleTick();
            }
            const auto contacts=std::count_if(world.events.begin(),world.events.end(),[](const Event&e){
                return (e.kind=="hit"&&e.name=="experimental_source_skill")||e.kind=="miss";});
            check(pose&&volume&&layer&&armorExited,"Body/equipment/effect/contact consumers run and source first-frame armor expires");
            check(contacts==(contact?3:0),"Multiple Knee boxes and held frames contact each actual target at most once");
            check(!contact||launched,"Accepted source contacts produce real monster launch/reaction instead of visual-only playback");
            for(const auto &event:world.events)if(event.kind=="relaunch"&&event.name==d.attack.memberPath)
                sourceLaunches[level]=std::max(sourceLaunches[level],event.value);
            check(!r.attacking()&&!world.armor()&&world.player.skillAnimationLayers.empty()&&r.snapshotDiagnostics().at("source_body_actions")==0,
                "Normal finite source animation retires body/protection/owned layers");
            check(world.skillState().snapshot(world.nowMs())==normal,"Preview binding never changes normal learned/granted or purchase ledger");
            const auto x=world.player.x;world.enqueue({world.simulationNanoseconds(),1,true});world.advanceSingleTick();
            check(world.player.x>x,"Actual movement input resumes after Knee completion");world.enqueue({world.simulationNanoseconds(),1,false});world.advanceSingleTick();
            evidence.push_back({{"phase","world_cast"},{"clock",ani_clock::policyName(clock)},{"level",level},{"direction",direction},
                {"contact",contact},{"contacts",contacts},{"observed_launch_velocity",acceptedLift},{"cost",cost}});
        }
        check(sourceLaunches[10]>sourceLaunches[1]&&sourceLaunches[1]>0,
            "The same real source MOB receives greater launch from level10 SKL force than level1, proving the optional body lift reaches World response");
        check(clock==ani_clock::ClockPolicy::SourceDelay100?(sourceRates[1]==100&&sourceRates[10]==100):(sourceRates[10]>sourceRates[1]),
            "Actual release clock consumes skill speed under inferred-rate policy and preserves raw100 in source-delay comparison");
        // Real ordinary source MOB contact; not diagnosticHit/hurtPlayer access.
        // Place the actual authored attack frame at the actual player's hurtbox.
        const auto incoming=[&](){
            const auto mob=pvf.script("monster/goblin/goblin.mob");
            const auto path=normalize((std::filesystem::u8path(mob.path).parent_path()/std::filesystem::u8path(mob.text("[attack motion]"))).generic_u8string());
            const auto attack=assets.animation(path);std::optional<Box> attackBox,hurtBox;int64_t start=0;
            const auto pose=playerFrame();
            check(r.attacking()&&world.player.animationPath==d.motion.memberPath&&pose<body->frames.size(),
                "Incoming contact samples the live own Knee clock frame instead of sentinel poseFrame");
            for(const auto &f:attack->frames){for(const auto &b:f.boxes)if(b.type==15)for(const auto &h:body->frames.at(pose).boxes)
                if(h.type==14&&b.z<h.z+h.d&&h.z<b.z+b.d){attackBox=b;hurtBox=h;break;}
                if(attackBox)break;start+=f.duration;}
            check(attackBox&&hurtBox,"Real source hostile attack and current own Knee hurtbox have a nonempty Z intersection");
            Actor a;a.id=77;a.monsterPath=mob.path;a.dir=-world.player.dir;
            a.x=a.px=world.player.x+world.player.dir*(hurtBox->x+hurtBox->w*.5)-a.dir*(attackBox->x+attackBox->w*.5);
            a.y=a.py=world.player.y+hurtBox->y+hurtBox->h*.5-attackBox->y-attackBox->h*.5;
            world.initializeMonsterAttributes(a,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");a.hp=a.maxHp=100000000;
            a.animation="attack1";a.animationPath=path;a.animStart=int64_t(FixedStepClock::millisecondsAtTick(uint64_t(world.tick)+1))-start;
            a.attackHit=false;world.monsters.push_back(std::move(a));world.synchronizeEntityHandles();world.freezeAi=false;
        };
        for(const auto *mode:{"armored","unarmored","lethal"}) {
            bool accepted=false;
            for(int attempt=0;attempt<32&&!accepted;++attempt) {
                floor();configure(1);press(true);world.advanceSingleTick();press(false);
                if(std::string(mode)=="unarmored")for(int n=0;n<100&&r.attacking()&&playerFrame()<3;++n)world.advanceSingleTick();
                check(r.attacking()&&(std::string(mode)=="unarmored"?!world.armor():world.armor()),"Incoming fixture reaches exact live armor state");
                if(std::string(mode)=="lethal")world.player.hp=1;
                const auto hp=world.player.hp;incoming();world.advanceSingleTick();accepted=world.player.hp<hp;
                if(!accepted)continue;
                if(std::string(mode)=="armored")check(!world.player.dead&&r.attacking()&&world.armor(),"Real accepted MOB hit deducts HP without interrupting live Knee super armor");
                else if(std::string(mode)=="unarmored")check(!world.player.dead&&!r.attacking()&&!world.armor(),"Real accepted hit after armor pose interrupts Knee normally");
                else check(world.player.dead&&!r.attacking()&&!world.armor(),"Real lethal hit terminates even an armored Knee action");
                world.advanceSingleTick();
                if(std::string(mode)!="armored")check(world.player.skillAnimationLayers.empty()&&r.snapshotDiagnostics().at("source_body_actions")==0,
                    "Accepted interruption/death leaves no owned Knee layers or source action");
                evidence.push_back({{"phase","incoming_source_contact"},{"mode",mode},{"attempt",attempt},{"damage",world.statReport().at("last_damage")}});
            }
            check(accepted,"Deterministic source MOB contacts eventually accept positive incoming damage for "+std::string(mode));
        }
        for(const auto *reason:{"cancel","scene","death","blocked"}) {
            floor();configure(1);press(true);world.advanceSingleTick();press(false);check(r.attacking(),"Exit fixture owns a real source Knee action");
            if(std::string(reason)=="cancel")world.idle();else if(std::string(reason)=="scene")world.changeScene();
            else if(std::string(reason)=="blocked")world.player.stunUntil=world.nowMs()+1000;else {world.player.dead=true;world.player.life=ActorLife::Dying;}
            world.advanceSingleTick();check(!r.attacking()&&!world.armor()&&world.player.skillAnimationLayers.empty()&&r.snapshotDiagnostics().at("source_body_actions")==0,
                std::string("No body/protection/layers survive ")+reason);
        }
        floor();configure(1);world.player.z=100;const auto airMp=world.player.mp;press(true);world.advanceSingleTick();press(false);
        check(world.player.mp==airMp&&!r.attacking()&&r.remainingCooldown(key,world.nowMs())==0,"Air admission fails before costs or source action publication");
        floor();configure(1);world.player.mp=0;press(true);world.advanceSingleTick();press(false);
        check(!r.attacking()&&r.remainingCooldown(key,world.nowMs())==0,"MP rejection publishes no Knee action/CD");
        for(const auto *fault:{"malformed_response","missing_visual"}) {
            floor();auto badPlan=std::make_shared<ExperimentalCharacterPlan>(plan);auto &bad=badPlan->sourceSkillActions.at(key);
            const std::string missingVisual="character/gunner/effect/animation/__missing_knee.ani";
            const bool malformed=std::string(fault)=="malformed_response";
            if(malformed) {
                size_t changed=0;for(auto &f:bad.attackDefinition.source.fields)if(normalize(f.tag)=="[hit wav]"){f.values=Json::array({42});++changed;}
                check(changed==1,"ATK fault injection replaces exactly the actual unique hit-wav field");
            } else {
                check(!pvf.has(missingVisual)&&!bad.bodyLayers.empty(),"Visual fault has an actual missing source and an owned layer to replace");
                bad.bodyLayers.front().source.memberPath=missingVisual;
            }
            ExperimentalCharacterRuntime injected(badPlan);injected.setAnimationClockPolicy(clock);
            injected.configuration().configureBasicAttackTemplate(key,1,*badPlan);injected.configuration().assignSlot(0,key,*badPlan);
            const auto mp=world.player.mp;const auto rng=world.randomStreams().snapshot();auto ids=world.idSources().snapshot();ids.erase("requests");
            check(world.experimentalSkillPreviewEnabled(),"Fault-injection World explicitly admits the manual source action");
            const std::string expectedMessage=malformed?"Invalid experimental ATK sound":"Missing PVF: "+missingVisual;
            const auto matchesFault=[&](const Json &row){return row.value("code",std::string())=="experimental_attack_source_preflight_rejected"&&
                row.value("message",std::string())==expectedMessage&&row.value("current_action_rejected",false);};
            const auto beforeDiagnostics=world.experimentalDiagnostics().at("world");
            const auto previousFaults=std::count_if(beforeDiagnostics.begin(),beforeDiagnostics.end(),matchesFault);
            CharacterActionRequest request;request.action=CharacterAction::CommandInput;request.inputKey=20;request.inputDown=true;
            request.simulationMs=world.nowMs();check(injected.request(request),"Fault fixture accepts the actual configured source skill input");
            ExperimentalWorldAdapter adapter(world);adapter.advance(injected,uint64_t(world.tick)+1);auto afterIds=world.idSources().snapshot();afterIds.erase("requests");
            const auto afterDiagnostics=world.experimentalDiagnostics().at("world");
            check(std::count_if(afterDiagnostics.begin(),afterDiagnostics.end(),matchesFault)==previousFaults+1,
                std::string("Actual adapter reaches the injected source preflight error, never an earlier normal gate: ")+fault);
            evidence.push_back({{"phase","injected_source_preflight"},{"clock",ani_clock::policyName(clock)},
                {"fault",fault},{"expected_error",expectedMessage},{"diagnostics_before",beforeDiagnostics},{"diagnostics_after",afterDiagnostics}});
            check(world.player.mp==mp&&!injected.attacking()&&injected.remainingCooldown(key,world.nowMs())==0&&
                ids==afterIds&&world.randomStreams().snapshot()==rng&&world.player.skillAnimationLayers.empty(),
                std::string("Actual source preflight rolls back MP/CD/action/visuals/IDs/RNG for ")+fault);
        }
        // Same real World action, source hit, RNG and fixed-tick results under
        // different render pumping and budgeted catchup; no expected algorithm clone.
        const auto schedule=[&](int fps,bool budgeted) {
            Progression p(regions);World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();
            CharacterStore c(std::filesystem::absolute("knee-schedule-"+std::string(ani_clock::policyName(clock))+"-"+std::to_string(fps)));
            c.data["characters"][0]={{"name","ReplayKnee"},{"class","gunner"},{"identity",CharacterIdentity{2,0,0}.json()},
                {"level",1},{"skill_initialization","source-v1"}};c.apply(0,w,p);dnf::enterExplicitSkillPreviewFixture(w);w.configureAnimationClock(clock);
            check(w.experimentalSkillPreviewEnabled()&&w.runtimeSkillPolicy(key).implemented,"Replay World explicitly uses comparison preview while normal Knee is independently admitted");
            auto &runtime=*w.experimentalRuntime();runtime.configuration().configureBasicAttackTemplate(key,10,runtime.plan());runtime.configuration().assignSlot(0,key,runtime.plan());
            w.monsters.clear();w.events.clear();w.combat=true;w.freezeAi=true;w.mapWidth=3000;w.walkRects={{0,185,3000,600}};
            w.player.x=w.player.px=600;w.player.y=w.player.py=300;w.player.z=w.player.pz=0;w.player.mp=10000;w.randomStreams()=RandomStreams(0x1031);
            Actor a;a.id=1;a.sourceId=10;a.monsterPath="monster/goblin/goblin.mob";a.x=a.px=640;a.y=a.py=300;
            w.initializeMonsterAttributes(a,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");a.hp=a.maxHp=100000000;w.monsters.push_back(std::move(a));w.synchronizeEntityHandles();
            w.enqueue({0,20,true});w.enqueue({16666667,20,false});Json frames=Json::array();
            w.setObjectTick([&](World &current){frames.push_back({{"tick",current.tick},{"mp",current.player.mp},{"runtime",runtime.snapshotDiagnostics()},
                {"armor",current.armor()},{"cd",runtime.cooldownSnapshot(current.nowMs())},{"hp",current.monsters[0].hp},
                {"position",{current.monsters[0].x,current.monsters[0].y,current.monsters[0].z}},
                {"animation",current.monsters[0].animationPath},{"events",current.eventLog()},{"rng",current.randomStreams().snapshot()}});});
            constexpr int64_t total=2000000000;int64_t previous=0;
            if(budgeted){w.advance(total,8);while(w.pendingTicks())w.advance(0,8);}
            else for(int frame=1;frame<=fps*2;++frame){const auto now=total*frame/(fps*2);w.advance(now-previous);previous=now;}
            check(w.tick==120&&w.pendingTicks()==0,"Render pumping completes all fixed Knee simulation ticks");return frames;
        };
        const auto reference=schedule(60,false);for(const int fps:{30,144})check(schedule(fps,false)==reference,"Real Knee World result stable at FPS "+std::to_string(fps));
        check(schedule(1,true)==reference,"Budget8 catchup preserves every source Knee simulation result");
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"scope","Current1031 Gunner2 skill4 own-source body/action/effect/ordinary-MOB-contact reconstruction; manually configured preview binding"},
        {"full_skill_complete",false},{"native_dynamic_parity",false},{"normal_learning_consumer_bound",true},
        {"comparison_fixture_normal_learning_exercised",false},{"act_active_action_reaction_consumer_bound",true},
        {"normal_and_active_act_verification","Separate normal-learning bridge and actual ACT collision suites; this suite exercises comparison operands"}};
    } catch(const std::exception &error){writeJson("gunner-knee-exception.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence}});throw;}
}
} // namespace dnf
