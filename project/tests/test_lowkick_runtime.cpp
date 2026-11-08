#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace dnf {
Json runLowKickRuntimeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message) {
        checks.push_back({{"passed",pass},{"message",message}});
        if(!pass){writeJson("lowkick-failure.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}
    };
    try {
    RegionCatalog regions(pvf,assets);
    const SkillKey key{1,6};
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("lowkick-"+std::string(ani_clock::policyName(clock))));
        store.data["characters"][0]={{"name","SourceLow"},{"class","fighter"},{"identity",CharacterIdentity{1,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clock);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        evidence.push_back({{"phase","source_plan"},{"diagnostics",plan.diagnostics}});
        check(plan.sourceSkillActions.size()==2&&plan.sourceSkillActions.count(key)&&plan.sourceSkillActions.count({1,5}),"Reviewed female Upper and existing exact LowKick are independent own-source consumers");
        const auto &descriptor=plan.sourceSkillActions.at(key);
        check(descriptor.kind==SourceSkillActionKind::BodyAttack&&descriptor.inferredNativeBody&&descriptor.key==key&&
            descriptor.motionSlot==3&&descriptor.attackSlot==2&&descriptor.state==21,"Current enum and own CHR bind exact skill6/state21/motion3/ATK2");
        check(descriptor.callback.memberPath.empty()&&descriptor.registration.memberPath.empty()&&descriptor.objectId==-1,
            "Native body reconstruction invents neither NUT callback registration nor passive objects");
        check(descriptor.motion.memberPath=="character/fighter/animation/damagelowkick.ani"&&
              descriptor.attack.memberPath=="character/fighter/attackinfo/damagelowkick.atk"&&
              descriptor.bodyLayers.empty()&&descriptor.castSound.empty(),"Own Fighter source paths execute without invented effects or cast sounds");
        check(descriptor.attackDefinition.type==DamageAttackType::Physical&&descriptor.attackDefinition.weaponDamageApply,
            "Current physical ATK and actual equipped attack remain in the unified damage chain");
        check(descriptor.percentColumn==1&&descriptor.independentColumn==2&&descriptor.speedColumn==0&&descriptor.recoveryMs==1000,
            "Current dungeon operands preserve percent1/independent2/speed0/static1000 with named inference");
        for(int level:{1,10,50}) {
            const auto values=evaluateSourceSkillAction(descriptor,*plan.skills.at(key).data,level);
            const auto table=plan.skills.at(key).data->values("[level info]");
            check(values.damage.percent==float(*skillLevelValue(table,level,1))&&values.damage.fixedDamage==0&&
                values.damage.independentPercent==float(*skillLevelValue(table,level,2))&&values.attackSpeedBonusPermille==*skillLevelValue(table,level,0)*10,
                "Current source level "+std::to_string(level)+" uses independent attack coefficient rather than flat damage");
            check(values.damage.sources[0].at("independent_percent")==*skillLevelValue(table,level,2)&&values.recoveryMs==1000,
                "Source operand and post-release recovery identities survive damage trace");
        }
        const auto floor=[&]() {
            world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();runtime.publishCooldownRestore({});
            world.combat=true;world.freezeAi=true;world.freeCd=false;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};world.blockedRects.clear();
            auto &p=world.player;p.x=p.px=600;p.y=p.py=300;p.z=p.pz=0;p.vx=p.vy=p.vz=0;p.dir=1;p.mp=100000;
            p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;
        };
        const auto configure=[&](int level){runtime.configuration().configureBasicAttackTemplate(key,level,plan);runtime.configuration().assignSlot(0,key,plan);};
        const auto press=[&](bool down){world.enqueue({world.simulationNanoseconds(),20,down});};
        const auto countEvents=[&](const std::string &kind,const std::string &name){size_t count=0;for(const auto &event:world.events)if(event.kind==kind&&event.name==name)++count;return count;};
        const auto root=plan.animations.at(descriptor.motion.memberPath);
        std::optional<Box> hitBox;for(const auto &frame:root->frames)for(const auto &box:frame.boxes)if(box.type==15&&!hitBox)hitBox=box;
        check(hitBox.has_value()&&root->duration==400,"Actual five-frame LowKick ANI has its own 400ms source timeline and attack volume");
        for(const int level:{1,10})for(const int direction:{-1,1})for(const bool targets:{false,true}) {
            floor();configure(level);world.player.dir=direction;runtime.configuration().setSourceBodyRecoveryPolicy("after_animation");
            const auto *binding=runtime.configuration().binding(key);
            check(binding&&binding->attack&&binding->unknown.contains("source_body_action_controller")&&
                !binding->unknown.contains("user_requested_temporary_template")&&!binding->unknown.contains("source_nut_action_controller"),
                "Slot selects real native-body reconstruction rather than temporary basic attack or invented NUT controller");
            auto saved=runtime.configuration().snapshot();saved["future_unknown"]=Json::array({1,"unchanged"});
            ExperimentalSkillConfiguration restored(plan);restored.restore(saved,plan);
            check(restored.snapshot()==saved,"Exact body ATK, comparison policy and unknown fields round trip without normal saves");
            auto bad=saved;Json *selectedBinding=nullptr;size_t selectedMatches=0;
            for(auto &binding:bad.at("skill_bindings"))if(SkillKey::fromJson(binding.at("key"))==key) {selectedBinding=&binding;++selectedMatches;}
            if(selectedMatches!=1)throw std::runtime_error("LowKick fixture requires one exact own SkillKey binding");
            (*selectedBinding)["source_body_action_controller"]["attack_slot"]=0;
            bool rejected=false;try{ExperimentalSkillConfiguration other(plan);other.restore(bad,plan);}catch(...){rejected=true;}
            check(rejected,"Tampered source-body dispatch is rejected before restoration");
            const auto normal=world.skillState().snapshot(world.nowMs());
            if(targets)for(int i=0;i<3;++i) {
                Actor target;target.id=i+1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
                target.x=target.px=600+direction*(hitBox->x+hitBox->w*.5);target.y=target.py=300+hitBox->y+hitBox->h*.5;target.dir=-direction;
                world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
                target.hp=target.maxHp=100000000;
                if(i==2){target.recovery=2;target.animation="down";
                    target.animationPath=normalize((std::filesystem::u8path(target.monsterPath).parent_path()/
                        std::filesystem::u8path(pvf.script(target.monsterPath).text("[down motion]"))).generic_u8string());
                    target.animStart=world.nowMs();target.lifeStart=world.nowMs();target.stunUntil=world.nowMs()+1000;}
                world.monsters.push_back(std::move(target));
            }
            world.synchronizeEntityHandles();const auto mp=world.player.mp;press(true);world.advanceSingleTick();press(false);
            check(world.player.mp<mp&&runtime.remainingCooldown(key,world.nowMs())>0,"Actual slot release commits evaluated current MP/CD once");
            const auto cost=runtime.snapshotDiagnostics().at("last_cost");
            check(mp-world.player.mp==cost.at("mp").at("value").get<int>()&&
                runtime.remainingCooldown(key,world.nowMs())==int64_t(std::ceil(cost.at("cooldown_ms").at("value").get<double>())),
                "Committed MP and cooldown exactly match source endpoints plus real equipped subtype trace");
            bool sawVolume=false,sawMotion=false,sawRecovery=false,sawResponse=false;int64_t recoveryTicks=0;Json volumeEvidence;
            for(int tick=0;tick<100;++tick) {
                sawMotion|=world.player.animationPath==descriptor.motion.memberPath;
                const auto diagnostic=runtime.snapshotDiagnostics();
                if(diagnostic.at("source_body_recovery").at("remaining_ms").get<int64_t>()>0){sawRecovery=true;++recoveryTicks;}
                for(const auto &volume:world.attackVolumes)if(volume.skillId==6) {
                    sawVolume=true;
                    check(volume.sourceAttackFamily=="inferred_current1031_body_skill"&&volume.sourceAttack&&
                        volume.sourceAttack->source.path==descriptor.attack.memberPath&&volume.sourceModifiers&&
                        volume.sourceModifiers->fixedDamage==0&&volume.sourceModifiers->independentPercent==float(*skillLevelValue(plan.skills.at(key).data->values("[level info]"),level,2)),
                        "Actual World volume uses exact LowKick ATK and source independent coefficient");
                    if(volumeEvidence.is_null())volumeEvidence=volume.sourceModifiers->snapshot();
                }
                for(const auto &target:world.monsters)sawResponse|=target.animation=="damage1"||target.animation=="damage2"||target.z>0;
                world.advanceSingleTick();
            }
            const auto hits=countEvents("hit","experimental_source_skill");size_t misses=0;for(const auto &event:world.events)if(event.kind=="miss")++misses;
            evidence.push_back({{"phase","world_cast"},{"clock",ani_clock::policyName(clock)},{"level",level},{"direction",direction},
                {"targets",targets},{"hits",hits},{"misses",misses},{"recovery_ticks",recoveryTicks},{"modifiers",volumeEvidence},
                {"last_damage",world.statReport().at("last_damage")},{"diagnostic",runtime.snapshotDiagnostics()}});
            check(sawMotion&&sawVolume&&sawRecovery&&recoveryTicks>=60,"Real source action reaches a full one-second after-animation recovery");
            check(!targets?hits+misses==0:hits+misses==3,"LowKick deduplicates each standing or down-target source hurtbox exactly once");
            check(!targets||sawResponse,"LowKick contact reaches real monster hit/reaction animation");
            if(targets) {
                const auto trace=world.statReport().at("last_damage");
                check(trace.at("usable").get<bool>()&&trace.at("sources").at("skill").at("fixed_damage")==0&&
                    trace.at("sources").at("skill").at("independent_percent")==*skillLevelValue(plan.skills.at(key).data->values("[level info]"),level,2),
                    "Accepted real World contact preserves source independentPercent and zero fixedDamage in unified damage trace");
                // A named counterfactual proves the nonzero coefficient's
                // mathematical consumer without pretending the level1 source
                // starter equipment has any nonzero independent attack.
                auto policy=DamageResolutionPolicy::inferredPveDamageV1(world.combatAttributes()->damageConstants);
                policy.randomVariation=policy.rollCritical=policy.rollHit=false;
                DamageRequest request;request.attacker=world.player.handle;request.target=world.monsters.front().handle;request.attackInstance=1;
                request.attackerStats=makeDamageCombatant(*world.combatAttributes());
                request.attackerStats.independentAttack=100;request.targetStats=makeDamageCombatant(*world.monsters.front().combatAttributes,policy);
                request.attack=descriptor.attackDefinition;request.skill=evaluateSourceSkillAction(descriptor,*plan.skills.at(key).data,level).damage;
                request.contactRange=DamageContactRange::Melee;
                const auto nonzero=resolveDamage(request,policy);request.attackerStats.independentAttack=0;const auto zero=resolveDamage(request,policy);
                evidence.push_back({{"phase","synthetic_independent_counterfactual"},{"nonzero",nonzero.snapshot()},{"zero",zero.snapshot()}});
                bool consumed=false;for(const auto &step:nonzero.trace)if(step.value("stage",std::string())=="attack_and_skill")
                    consumed=step.at("independent_component").get<float>()>0&&step.at("fixed_group").get<float>()>0;
                check(nonzero.usable()&&zero.usable()&&*nonzero.hpDamage>*zero.hpDamage&&consumed,
                    "Explicit synthetic nonzero-independent counterfactual executes existing unified formula, without flat-damage substitution");
            }
            check(!runtime.attacking()&&runtime.snapshotDiagnostics().at("source_body_recovery").at("remaining_ms")==0&&world.player.skillAnimationLayers.empty(),
                "Body action and recovery retire without lingering effects/entities");
            check(world.skillState().snapshot(world.nowMs())==normal,"Test overlay leaves normal learning and advancement ledger unchanged");
            const auto cdMp=world.player.mp;press(true);world.advanceSingleTick();press(false);
            check(world.player.mp==cdMp&&!runtime.attacking(),"Fresh press after recovery still respects the original source cooldown");
        }
        // Isolate actual runtime speed/after-delay consumers from contact randomness.
        const auto isolated=[&](const std::string &policy,int level,bool exerciseBlocking) {
            auto shared=std::make_shared<ExperimentalCharacterPlan>(plan);ExperimentalCharacterRuntime r(shared);r.setAnimationClockPolicy(clock);
            r.configuration().configureBasicAttackTemplate(key,level,*shared);r.configuration().assignSlot(0,key,*shared);r.configuration().setSourceBodyRecoveryPolicy(policy);
            ExperimentalActorState actor;actor.x=600;actor.y=300;actor.mp=100000;actor.attackPerMille=1700;actor.weaponSubtype=0;
            CharacterActionRequest request;request.inputKey=20;request.inputDown=true;request.action=CharacterAction::CommandInput;r.request(request);
            auto out=r.advance(1,actor,[](double,double){return true;});actor=out.actor;
            const auto initial=out.animationClock;check(initial.has_value(),"Source body action owns actual selected clock");
            if(clock==ani_clock::ClockPolicy::Inferred60UsPercentDeadlines)
                check(initial->ratePercent>170,"Source skill speed column accelerates the effective actor clock at level10");
            else check(initial->ratePercent==100,"SourceDelay100 comparison retains raw ANI delays despite stat/skill speed");
            actor.hitStopped=true;const auto paused=r.advance(2,actor,[](double,double){return true;});actor=paused.actor;
            check(paused.animationClock&&paused.animationClock->elapsedMs==initial->elapsedMs,"Hitstop freezes the skill body clock");actor.hitStopped=false;
            int recoveryStart=-1,completed=-1;bool blocked=false;
            for(uint64_t tick=3;tick<150;++tick) {
                auto result=r.advance(tick,actor,[](double,double){return true;});actor=result.actor;
                if(r.snapshotDiagnostics().at("source_body_recovery").at("remaining_ms").get<int64_t>()>0&&recoveryStart<0) {
                    recoveryStart=int(tick);
                    if(exerciseBlocking){CharacterActionRequest move;move.inputKey=1;move.inputDown=true;move.simulationMs=int64_t(FixedStepClock::millisecondsAtTick(tick));r.request(move);
                        CharacterActionRequest skill;skill.inputKey=20;skill.inputDown=true;r.request(skill);CharacterActionRequest attack;attack.action=CharacterAction::BasicAttack;r.request(attack);}
                } else if(exerciseBlocking&&recoveryStart>=0&&r.attacking()) {
                    check(actor.vx==0&&actor.vy==0&&result.attacks.empty(),"Source static recovery suppresses movement and repeated body contact samples");
                    for(const auto &diagnostic:result.diagnostics)blocked|=diagnostic.value("code",std::string())=="source_body_recovery_blocked";
                }
                if(!r.attacking()){completed=int(tick);break;}
            }
            check(recoveryStart>0&&completed>recoveryStart,"Skill enters finite source-duration recovery and returns to locomotion");
            if(exerciseBlocking)check(blocked,"Source recovery rejects another skill request through actual failure feedback");
            evidence.push_back({{"phase","recovery_comparison"},{"clock",ani_clock::policyName(clock)},{"policy",policy},
                {"level",level},{"start_tick",recoveryStart},{"completed_tick",completed}});return completed;
        };
        const auto after=isolated("after_animation",10,true),since=isolated("since_activation",10,false);
        check(after>since,"Named static-duration interpretations produce distinct executable comparison outcomes");
        floor();configure(1);world.player.z=100;const auto airMp=world.player.mp;press(true);world.advanceSingleTick();press(false);
        check(world.player.mp==airMp&&runtime.remainingCooldown(key,world.nowMs())==0&&!runtime.attacking(),"Named inferred ground admission rejects airborne release before MP/CD");
        floor();configure(1);world.player.mp=0;press(true);world.advanceSingleTick();press(false);
        check(!runtime.attacking()&&runtime.remainingCooldown(key,world.nowMs())==0,"Insufficient MP cannot publish action or recovery");
        for(const auto *reason:{"cancel","scene","death","blocked"}) {
            floor();configure(1);press(true);world.advanceSingleTick();press(false);
            for(int n=0;n<35;++n)world.advanceSingleTick();
            check(runtime.snapshotDiagnostics().at("source_body_recovery").at("remaining_ms").get<int64_t>()>0,"Exit fixture reaches actual recovery");
            if(std::string(reason)=="cancel")world.idle();else if(std::string(reason)=="scene")world.changeScene();
            else if(std::string(reason)=="blocked")world.player.stunUntil=world.nowMs()+1000;
            else {world.player.dead=true;world.player.life=ActorLife::Dying;}
            world.advanceSingleTick();
            check(runtime.snapshotDiagnostics().at("source_body_recovery").at("remaining_ms")==0&&
                  runtime.snapshotDiagnostics().at("source_body_actions")==0,std::string("No recovery/callback survives ")+reason);
        }
        // Response failure preflights before MP/CD/IDs/RNG or source motion publication.
        floor();auto badPlan=std::make_shared<ExperimentalCharacterPlan>(plan);auto &bad=badPlan->sourceSkillActions.at(key);
        for(auto &field:bad.attackDefinition.source.fields)if(normalize(field.tag)=="[hit wav]")field.values=Json::array({42});
        ExperimentalCharacterRuntime injected(badPlan);injected.setAnimationClockPolicy(clock);injected.configuration().configureBasicAttackTemplate(key,1,*badPlan);
        injected.configuration().assignSlot(0,key,*badPlan);const auto mp=world.player.mp;const auto rng=world.randomStreams().snapshot();auto ids=world.idSources().snapshot();ids.erase("requests");
        CharacterActionRequest request;request.inputKey=20;request.inputDown=true;injected.request(request);
        ExperimentalWorldAdapter adapter(world);adapter.advance(injected,uint64_t(world.tick)+1);auto afterIds=world.idSources().snapshot();afterIds.erase("requests");
        check(world.player.mp==mp&&injected.remainingCooldown(key,world.nowMs())==0&&!injected.attacking()&&world.randomStreams().snapshot()==rng&&ids==afterIds,
            "Malformed current ATK response rolls back costs, motion, recovery, combat IDs and RNG");
        const auto schedule=[&](int fps,bool budgeted) {
            Progression p(regions);World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();
            CharacterStore c(std::filesystem::absolute("low-schedule-"+std::string(ani_clock::policyName(clock))+"-"+std::to_string(fps)));
            c.data["characters"][0]={{"name","ReplayLow"},{"class","fighter"},{"identity",CharacterIdentity{1,0,0}.json()},
                {"level",1},{"skill_initialization","source-v1"}};c.apply(0,w,p);dnf::enterExplicitSkillPreviewFixture(w);w.configureAnimationClock(clock);
            auto &r=*w.experimentalRuntime();r.configuration().configureBasicAttackTemplate(key,10,r.plan());r.configuration().assignSlot(0,key,r.plan());
            w.monsters.clear();w.events.clear();w.combat=true;w.freezeAi=true;w.mapWidth=3000;w.walkRects={{0,185,3000,600}};
            w.player.x=w.player.px=600;w.player.y=w.player.py=300;w.player.z=w.player.pz=0;w.player.mp=10000;w.randomStreams()=RandomStreams(0x1031);
            Actor target;target.id=1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";target.x=target.px=640;target.y=target.py=300;
            w.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");target.hp=target.maxHp=100000000;w.monsters.push_back(std::move(target));w.synchronizeEntityHandles();
            w.enqueue({0,20,true});w.enqueue({16666667,20,false});Json frames=Json::array();
            w.setObjectTick([&](World &current){frames.push_back({{"tick",current.tick},{"mp",current.player.mp},{"runtime",r.snapshotDiagnostics()},
                {"cd",r.cooldownSnapshot(current.nowMs())},{"hp",current.monsters[0].hp},{"position",{current.monsters[0].x,current.monsters[0].y,current.monsters[0].z}},
                {"animation",current.monsters[0].animationPath},{"events",current.eventLog()},{"rng",current.randomStreams().snapshot()}});});
            constexpr int64_t total=2000000000;int64_t previous=0;
            if(budgeted){w.advance(total,8);while(w.pendingTicks())w.advance(0,8);}
            else for(int frame=1;frame<=fps*2;++frame){const auto now=total*frame/(fps*2);w.advance(now-previous);previous=now;}
            check(w.tick==120&&w.pendingTicks()==0,"Render pump completes every fixed skill/recovery tick");return frames;
        };
        const auto reference=schedule(60,false);for(const int fps:{30,144})check(schedule(fps,false)==reference,"Source LowKick contact/cost/recovery deterministic at FPS "+std::to_string(fps));
        check(schedule(1,true)==reference,"Budget8 catchup retains every source LowKick simulation result");
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"scope","Fighter1 skill6 current1031 source body reconstruction; overlay-only, inferred qualifications/speed/recovery"},
        {"full_skill_complete",false},{"native_dynamic_parity",false},{"normal_learning_consumer_bound",false}};
    } catch(const std::exception &error){writeJson("lowkick-exception.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence}});throw;}
}
}
