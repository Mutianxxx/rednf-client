#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
Json runSourceSkillActionTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool passed,const std::string &message) {
        checks.push_back({{"passed",passed},{"message",message}});
        if(!passed){writeJson("source-skill-failure.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}
    };
    try {
    // Shared Fighter stages are exercised directly, independent of the World
    // UI/default learning fixture. Root owns execution of this regression.
    {
        CharacterCatalog catalog(pvf);
        auto plan=std::make_shared<ExperimentalCharacterPlan>(loadExperimentalCharacterPlan(pvf,assets,catalog,{1,0,0}));
        check(plan->nativeJump&&plan->nativeJump->takeoff==1&&plan->nativeJump->fall==7&&plan->nativeJump->landing==13,
            "40JP Fighter jump boundaries retain current long ANI holds and switch on motion state");
        const auto &leg=plan->sourceSkillActions.at({1,62});
        check(leg.nativeStages.front().motionSlot==20&&leg.nativeStages.front().motion.memberPath=="character/fighter/animation/trylegsuplex.ani",
            "Current own CHR order overrides conflicting later NUT custom slot23");
        const auto hasLayer=[](const SourceNativeStage &stage,const std::string &path) {
            return std::any_of(stage.layers.begin(),stage.layers.end(),[&](const FemaleGunnerSkillLayer &layer) {
                return layer.source.memberPath==path;
            });
        };
        const auto findAction=[&](const std::string &name)->const SourceSkillAction * {
            const auto path="skill/fighter/"+name+".skl";
            for(const auto &entry:plan->sourceSkillActions)
                if(normalize(entry.second.skill.memberPath)==path)return &entry.second;
            return nullptr;
        };
        const auto findCue=[](const std::vector<SourceSkillVisualCue> &cues,const std::string &path)->const SourceSkillVisualCue * {
            const auto found=std::find_if(cues.begin(),cues.end(),[&](const SourceSkillVisualCue &cue) {
                return normalize(cue.source.memberPath)==path;
            });
            return found==cues.end()?nullptr:&*found;
        };
        const auto hasPlanDiagnostic=[&](const std::string &code,const std::string &skill) {
            return std::any_of(plan->diagnostics.begin(),plan->diagnostics.end(),[&](const Json &item) {
                return item.value("code","")==code&&item.value("skill","")==skill;
            });
        };
        const auto &upper=plan->sourceSkillActions.at({1,5});
        check(hasLayer(upper.nativeStages.front(),"character/fighter/effect/animation/upper.ani")&&
              hasPlanDiagnostic("fighter40jp_effect_binding_inferred","liftupper"),
            "Reviewed 1031 Upper visual inference remains explicit and is not claimed as a 40JP caller");
        const auto *energy=findAction("energyball");
        const auto *charge=energy&&!energy->nativeStages.empty()?
            findCue(energy->nativeStages.front().layers,"character/fighter/effect/animation/energycharge.ani"):nullptr;
        const auto *shoot=energy&&!energy->nativeStages.empty()?
            findCue(energy->nativeStages.front().layers,"character/fighter/effect/animation/energyballshoot.ani"):nullptr;
        check(charge&&charge->controllerSubstates==std::vector<int>({12,16})&&charge->controllerStyle<0&&
              sourceSkillVisualCueMatches(*charge,12,1)&&sourceSkillVisualCueMatches(*charge,16,0),
            "40JP EnergyCharge cue is selected only for controller substates 12 or 16");
        check(shoot&&shoot->controllerSubstates==std::vector<int>({12})&&shoot->controllerStyle==1&&
              sourceSkillVisualCueMatches(*shoot,12,1)&&!sourceSkillVisualCueMatches(*shoot,12,0)&&
              !sourceSkillVisualCueMatches(*shoot,16,1),
            "40JP EnergyBallShoot cue requires substate 12 and style 1");
        check(heldTargetWidthVisualScale(100)==1&&heldTargetWidthVisualScale(175)==2&&
              heldTargetWidthVisualScale(250)==3&&heldTargetWidthVisualScale(400)==3&&
              heldTargetWidthVisualScale(std::numeric_limits<double>::infinity())==1,
            "Spire target-width scale follows the bounded 40JP 1-to-3 curve and has a stable invalid-input fallback");
        const auto &tackle=plan->sourceSkillActions.at({1,54});
        Json tackleLayers=Json::array(),tackleDiagnostics=Json::array();
        for(const auto &layer:tackle.nativeStages.front().layers)tackleLayers.push_back(layer.source.memberPath);
        for(const auto &diagnostic:plan->diagnostics)
            if(diagnostic.value("skill","")=="shouldertackle")tackleDiagnostics.push_back(diagnostic);
        const auto *tackleHit=findCue(tackle.nativeStages.front().contactEffects,
            "character/fighter/effect/animation/shouldertacklehit.ani");
        evidence.push_back({{"phase","fighter40jp_tackle_visual_binding"},{"layers",tackleLayers},
            {"contact_effect",tackleHit?tackleHit->snapshot():Json()},{"diagnostics",tackleDiagnostics},
            {"stage_count",tackle.nativeStages.size()}});
        check(hasLayer(tackle.nativeStages.front(),"character/fighter/effect/animation/shouldertackle.ani")&&
              tackleHit&&tackleHit->trigger==SourceSkillVisualTrigger::AcceptedHit&&
              !sourceSkillVisualCueMatches(*tackleHit,0,0),
            "40JP ShoulderTackle action ANI stays separate from its accepted-hit-only ShoulderTackleHit cue");
        const auto *spire=findAction("spire");
        const auto *rollUnder=spire&&spire->nativeStages.size()>1?
            findCue(spire->nativeStages[1].layers,"character/fighter/effect/animation/jumpsuplexrollunder.ani"):nullptr;
        const auto *rollOver=spire&&spire->nativeStages.size()>1?
            findCue(spire->nativeStages[1].layers,"character/fighter/effect/animation/jumpsuplexrollover.ani"):nullptr;
        check(rollUnder&&rollOver&&rollUnder->scalePolicy==SourceSkillVisualScalePolicy::HeldTargetWidth&&
              rollOver->scalePolicy==SourceSkillVisualScalePolicy::HeldTargetWidth,
            "Both Spire roll layers consume the captured-target scale policy on the held-target stage");
        const auto &close=plan->sourceSkillActions.at({1,19});
        check(hasLayer(close.nativeStages.front(),"character/fighter/effect/animation/closepunchexecute.ani"),
            "ClosePunchExecute is attached only through its exact 40JP ANI callsite");
        const auto walk=[](double,double){return true;};
        for(bool accepted:{false,true}) {
            ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
            runtime.configuration().configureSourceSkillAction({1,9},1,*plan);
            CharacterActionRequest request;request.action=CharacterAction::Skill;request.skill=SkillKey{1,9};request.inputDown=true;
            check(runtime.request(request),"Shared source Suplex request is accepted without a basic/Upper template");
            ExperimentalActorState actor;actor.x=300;actor.y=300;actor.mp=0;actor.fighter40JpTestFreedom=true;
            uint64_t owner=0;bool tryVolume=false,followup=false,release=false;int directHits=0;
            for(uint64_t tick=1;tick<=100;++tick) {
                auto out=runtime.advance(tick,actor,walk);actor=out.actor;
                for(const auto &frame:out.attacks) {
                    if(frame.sourceGrabTry&&!frame.boxes.empty()) {
                        tryVolume=true;owner=frame.sourceGrabOwner;
                        if(accepted&&runtime.sourceGrabState()&&!runtime.sourceGrabState()->holding)
                            check(runtime.acceptSourceGrabHit(owner),"A qualified World collision can atomically accept its stable grab owner");
                    }
                    followup|=frame.motion.source.memberPath=="character/fighter/animation/suplex.ani";
                    release|=frame.sourceGrabRelease;
                    if(frame.sourceGrabDirectHit) {
                        ++directHits;check(frame.sourceFrame==4&&frame.boxes.empty()&&!frame.suppressBodyDamage&&frame.attack&&
                            frame.attack->source.memberPath=="character/fighter/attackinfo/suplex.atk",
                            "Native frame4 held-target callback retains real ATK and never fabricates an ANI collision box");
                    }
                }
            }
            check(tryVolume&&followup==accepted&&release==accepted,
                "Suplex follow-up and release require accepted source contact; empty cast stops at try animation");
            check(directHits==int(accepted),"Suplex native held-target callback fires once after accepted grab and never on an empty cast");
            check(!runtime.attacking()&&!runtime.sourceGrabState()&&actor.mp==0,
                "Shared grab lifecycle clears on completion and explicit test freedom consumes no normal resource");
            runtime.cancel(ControllerCancelReason::RoomChange);
            check(!runtime.sourceGrabState(),"Scene cancellation cannot retain a source grab owner");
        }
        ExperimentalCharacterRuntime jump(plan);jump.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
        CharacterActionRequest request;request.action=CharacterAction::Jump;request.inputKey=5;request.inputDown=true;
        check(jump.request(request),"Explicit Jump action enters the native Fighter jump controller");
        ExperimentalActorState actor;actor.x=300;actor.y=300;
        std::set<int> poses;bool rose=false,fell=false,landed=false;
        for(uint64_t tick=1;tick<=100;++tick) {
            auto out=jump.advance(tick,actor,walk);actor=out.actor;
            if(out.state=="jump")poses.insert(out.poseFrame);
            rose|=actor.vz>0;fell|=actor.vz<0;landed|=rose&&fell&&actor.z==0&&out.state!="jump";
        }
        evidence.push_back({{"phase","fighter40jp_jump"},{"poses",poses},{"rose",rose},{"fell",fell},{"landed",landed},
            {"runtime",jump.snapshotDiagnostics()}});
        check(rose&&fell&&landed&&poses.count(7)&&poses.count(13),
            "Native jump enters descending and landing source frames without waiting 100000/10000ms held poses");
        const auto &nen=plan->sourceSkillActions.at({1,12});
        check(nen.nativeProjectile&&nen.objectId==21002&&nen.offset[2]>0&&nen.objectAnimation,
            "Source Nen projectile retains actual OBJ/ANI/ATK and a native muzzle-height consumer");
        evidence.push_back({{"phase","fighter40jp_shared_stages"},{"plan",plan->snapshot()},{"executed_by_child_agent",false}});
    }
    RegionCatalog regions(pvf,assets);
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("source-skill-fixture-"+std::string(ani_clock::policyName(clock))));
        store.data["characters"][0]={{"name","SourceWind"},{"class","atmage"},{"identity",CharacterIdentity{8,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clock);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        evidence.push_back({{"phase","plan_admission"},{"clock",ani_clock::policyName(clock)},{"diagnostics",plan.diagnostics}});
        check(plan.sourceSkillActions.size()==2&&plan.sourceSkillActions.count({8,26}),"Reviewed WindStrike and actual moving-impact WaterCannon families are separate consumers");
        const auto &descriptor=plan.sourceSkillActions.at({8,1});
        check(descriptor.state==20&&descriptor.motionSlot==0&&descriptor.flag==1&&descriptor.objectId==24201,
            "Runtime reads current NUT registration/state/CHR custom slot/flag/PO ID");
        check(descriptor.object.memberPath=="passiveobject/character/mage/atwindstrike.obj"&&
              descriptor.animation.memberPath=="passiveobject/character/mage/animation/atwindstrike/00_wind_dodge.ani"&&
              descriptor.attack.memberPath=="passiveobject/character/mage/attackinfo/atwindstrike.atk",
            "Runtime follows actual passive registry/OBJ basic motion/ATK references");
        check(descriptor.percentColumn==0&&descriptor.fixedColumn==1&&descriptor.liftColumn==2&&descriptor.offset==std::array<double,3>{120,1,0},
            "Payload columns and spawn XYZ are derived from current source calls");
        evidence.push_back({{"phase","source_descriptor"},{"clock",ani_clock::policyName(clock)},{"descriptor",descriptor.snapshot()}});
        check(descriptor.executableStates==std::set<int>{descriptor.standState,descriptor.dashState,descriptor.attackState}&&
              !descriptor.executableStates.count(descriptor.jumpState),"Current SKL executable states resolve through this version's NUT enum header");
        for(int level=1;level<=10;++level) {
            const auto operands=evaluateSourceSkillAction(descriptor,*plan.skills.at({8,1}).data,level);
            const auto table=plan.skills.at({8,1}).data->values("[level info]");
            check(operands.damage.percent==float(*skillLevelValue(table,level,0))&&
                  operands.damage.fixedDamage==float(*skillLevelValue(table,level,1))&&operands.lift==*skillLevelValue(table,level,2),
                "Source level "+std::to_string(level)+" reaches percentage/fixed/lift consumers without treating all column0 values as universal damage");
        }
        const auto floor=[&]() {world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
            runtime.publishCooldownRestore({});
            world.combat=true;world.freezeAi=true;world.freeCd=false;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};
            auto &p=world.player;p.x=p.px=600;p.y=p.py=300;p.z=p.pz=0;p.vx=p.vy=p.vz=0;p.dir=1;p.mp=100000;
            p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;};
        const auto press=[&](int key,bool down){world.enqueue({world.simulationNanoseconds(),key,down});};
        const auto ownedEffects=[&]() {std::set<int> ids;for(const auto &fx:world.effects)if(fx.phase=="source-nut:passive-object"&&world.nowMs()<fx.expires)ids.insert(fx.id);return ids;};
        for(const int level:{1,10})for(const int direction:{-1,1})for(const bool withTargets:{false,true}) {
            floor();world.player.dir=direction;
            const auto normal=world.skillState().snapshot(world.nowMs());
            runtime.configuration().configureBasicAttackTemplate({8,1},level,plan);runtime.configuration().assignSlot(0,SkillKey{8,1},plan);
            check(runtime.configuration().binding({8,1})->unknown.contains("source_nut_action_controller")&&
                  !runtime.configuration().binding({8,1})->unknown.contains("user_requested_temporary_template"),
                "Existing config entry dispatches this reviewed source controller instead of the basic-attack template");
            const auto saved=runtime.configuration().snapshot();ExperimentalSkillConfiguration restored(plan);restored.restore(saved,plan);
            check(restored.snapshot()==saved,"Source controller config round trips with exact source dispatch identity");
            auto invalid=saved;invalid["skill_bindings"][0]["source_nut_action_controller"]["source_flag"]=99;
            bool rejected=false;try{ExperimentalSkillConfiguration changed(plan);changed.restore(invalid,plan);}catch(...){rejected=true;}
            check(rejected,"Stale/tampered source NUT controller receipt rejects restore");
            if(withTargets)for(int index=0;index<3;++index) {
                Actor target;target.id=index+1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
                target.x=target.px=world.player.x+direction*(120+(index-1)*10);target.y=target.py=world.player.y+1;target.dir=-direction;
                world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
                target.hp=target.maxHp=100000000;world.monsters.push_back(std::move(target));
            }
            world.synchronizeEntityHandles();const auto beforeMp=world.player.mp;press(20,true);world.advanceSingleTick();press(20,false);
            const auto cost=runtime.snapshotDiagnostics().at("last_cost");
            check(world.player.mp<beforeMp&&runtime.remainingCooldown({8,1},world.nowMs())>0,
                "Actual World source action debits MP and starts real source CD");
            std::set<int> effectIds;bool actualSourceMotion=false,badBodyVolume=false,sawLaunch=false;Json firstVisual,firstVolume;
            for(int tick=0;tick<90;++tick) {
                actualSourceMotion|=world.player.animationPath==descriptor.motion.memberPath;
                for(const auto &fx:world.effects)if(fx.phase=="source-nut:passive-object") {
                    effectIds.insert(fx.id);if(firstVisual.is_null())firstVisual={{"x",fx.x},{"y",fx.y},{"z",fx.z},{"dir",fx.dir},
                        {"animation",fx.animation},{"object",fx.sourceObject},{"provenance",fx.projectileSource}};
                }
                for(const auto &volume:world.attackVolumes)if(volume.skillId==1) {
                    badBodyVolume|=volume.sourceAttackFamily!="reviewed_nut_passive_object";
                    if(firstVolume.is_null())firstVolume={{"origin",{volume.x,volume.y,volume.z}},{"serial",volume.serial},
                        {"source_attack",volume.sourceAttack?volume.sourceAttack->source.path:""},{"modifiers",volume.sourceModifiers?volume.sourceModifiers->snapshot():Json()}};
                }
                for(const auto &target:world.monsters)sawLaunch|=target.z>0&&target.vz>0;
                world.advanceSingleTick();
            }
            Json targets=Json::array();size_t hitEvents=0;
            for(const auto &event:world.events)if(event.kind=="hit"&&event.name=="source_nut_passive_object")++hitEvents;
            for(const auto &target:world.monsters)targets.push_back({{"id",target.id},{"hp",target.hp},{"max_hp",target.maxHp},{"animation",target.animationPath}});
            evidence.push_back({{"phase","world_cast"},{"clock",ani_clock::policyName(clock)},{"level",level},{"direction",direction},
                {"targets_present",withTargets},{"visual_count",effectIds.size()},{"first_visual",firstVisual},{"first_volume",firstVolume},
                {"targets",targets},{"hit_events",hitEvents},{"saw_launch",sawLaunch},{"cost",cost},{"diagnostics",world.experimentalDiagnostics()}});
            check(actualSourceMotion&&effectIds.size()==1,"One slot activation renders the actual source CHR action and exactly one flagged PO");
            check(!badBodyVolume&&!firstVolume.is_null(),"Attack geometry comes from PO type15; source body does not add a template attack");
            check(firstVisual.at("x")==600+direction*120&&firstVisual.at("y")==301&&firstVisual.at("z")==0&&firstVisual.at("dir")==direction,
                "Source world/local XYZ and left/right direction remain distinct");
            check(ownedEffects().empty()&&runtime.snapshotDiagnostics().at("source_nut_entities")==0,
                "Source PO ANI completion retires its visual and transient collision entity");
            check(!withTargets||hitEvents==3,"Three actual Goblin source hurt boxes each accept one hit from one PO ledger");
            check(withTargets||hitEvents==0,"Empty release has no contact side effects");
            check(!withTargets||sawLaunch,"Source payload upForce reaches actual monster airborne/reaction behavior");
            check(world.skillState().snapshot(world.nowMs())==normal,"Experimental source release leaves normal learning ledger unchanged");
        }
        // Exit/cancel after actual creation, and cancellation before source flag.
        for(const auto *reason:{"before_flag","scene","death","explicit_cancel"}) {
            floor();world.freeCd=true;runtime.configuration().configureBasicAttackTemplate({8,1},1,plan);runtime.configuration().assignSlot(0,SkillKey{8,1},plan);
            press(20,true);world.advanceSingleTick();press(20,false);
            if(std::string(reason)!="before_flag")for(int tick=0;tick<60&&ownedEffects().empty();++tick)world.advanceSingleTick();
            check(std::string(reason)=="before_flag"||!ownedEffects().empty(),"Cancellation fixture reaches actual PO publication");
            if(std::string(reason)=="death"){world.player.dead=true;world.player.life=ActorLife::Dying;}
            else if(std::string(reason)=="explicit_cancel")world.idle();else world.changeScene();
            for(int tick=0;tick<45;++tick)world.advanceSingleTick();
            check(ownedEffects().empty()&&runtime.snapshotDiagnostics().at("source_nut_entities")==0,
                std::string("No source NUT PO or delayed flag survives ")+reason);
        }
        // Deliberate faults use caller-owned appearance and immutable-plan
        // test copies; source PVF/static bytes and normal saves stay untouched.
        const auto stableIds=[&]() {auto state=world.simulationCheckpoint();auto ids=state.at("ids");ids.erase("requests");
            return Json{{"ids",ids},{"effects",state.at("effects")}};};
        const auto rejectWorldFault=[&](const std::string &fault) {
            const auto mp=world.player.mp;const auto events=world.events.size();
            const auto ids=stableIds(),rng=world.randomStreams().snapshot(),config=runtime.configuration().snapshot();
            const auto sequence=runtime.snapshotDiagnostics().at("action_sequence");
            const auto entitySequence=runtime.snapshotDiagnostics().at("source_nut_entity_sequence");
            press(20,true);world.advanceSingleTick();press(20,false);
            check(world.player.mp==mp&&runtime.remainingCooldown({8,1},world.nowMs())==0&&!runtime.attacking()&&
                  world.effects.empty()&&world.attackVolumes.empty()&&world.randomStreams().snapshot()==rng&&stableIds()==ids&&
                  runtime.snapshotDiagnostics().at("action_sequence")==sequence&&
                  runtime.snapshotDiagnostics().at("source_nut_entity_sequence")==entitySequence,
                fault+" rejects before MP/CD/effects/attack IDs/RNG/action or passive entity publication");
            check(runtime.configuration().snapshot()==config&&std::all_of(world.events.begin()+events,world.events.end(),
                [](const Event &event){return event.kind=="skill_rejected";}),fault+" emits only skill rejection feedback and preserves configuration");
            const auto diagnostics=world.experimentalDiagnostics().at("world");
            check(!diagnostics.empty()&&diagnostics.back().at("code")=="experimental_attack_source_preflight_rejected"&&
                diagnostics.back().at("source_nut_programs").size()==1&&
                diagnostics.back().at("source_nut_programs")[0].at("member_path")==descriptor.callback.memberPath,
                fault+" reports the exact current NUT program at the failed source transaction");
            evidence.push_back({{"phase","fault"},{"fault",fault},{"clock",ani_clock::policyName(clock)},{"diagnostics",diagnostics}});
        };
        floor();runtime.configuration().configureBasicAttackTemplate({8,1},1,plan);runtime.configuration().assignSlot(0,SkillKey{8,1},plan);
        const auto goodAppearance=world.characterAppearance();auto broken=goodAppearance;broken.bodyMotions.clear();
        world.setCharacterAppearance(std::move(broken));rejectWorldFault("Actual CHR/EQU motion preflight failure");
        world.setCharacterAppearance(goodAppearance);world.releaseInputs();press(20,true);world.advanceSingleTick();press(20,false);
        check(runtime.attacking()&&runtime.remainingCooldown({8,1},world.nowMs())>0,
            "A new explicit request after source appearance repair starts the same reviewed controller");
        floor();const auto attacks=world.idSources().attacks;world.idSources().attacks=MonotonicIds(0);
        rejectWorldFault("Passive-object attack ID exhaustion");world.idSources().attacks=attacks;
        floor();world.player.z=100;world.player.vz=0;const auto airborneMp=world.player.mp;
        press(20,true);world.advanceSingleTick();press(20,false);
        check(world.player.mp==airborneMp&&runtime.remainingCooldown({8,1},world.nowMs())==0&&!runtime.attacking()&&ownedEffects().empty(),
            "A real airborne source-state rejection has no MP/CD or delayed passive object");
        for(const bool badVisual:{false,true}) {
            auto badPlan=std::make_shared<ExperimentalCharacterPlan>(plan);
            auto &bad=badPlan->sourceSkillActions.at({8,1});
            if(badVisual)bad.animation.memberPath="missing/source-nut-passive-visual.ani";
            else for(auto &field:bad.attackDefinition.source.fields)if(normalize(field.tag)=="[hit wav]")field.values=Json::array({42});
            ExperimentalCharacterRuntime injected(badPlan);injected.setAnimationClockPolicy(clock);
            injected.configuration().configureBasicAttackTemplate({8,1},1,*badPlan);injected.configuration().assignSlot(0,SkillKey{8,1},*badPlan);
            floor();ExperimentalWorldAdapter adapter(world);const auto ids=stableIds(),rng=world.randomStreams().snapshot();const auto mp=world.player.mp;
            CharacterActionRequest request;request.inputKey=20;request.inputDown=true;request.action=CharacterAction::CommandInput;
            injected.request(request);adapter.advance(injected,uint64_t(world.tick)+1);
            check(world.player.mp==mp&&injected.remainingCooldown({8,1},world.nowMs())==0&&!injected.attacking()&&
                  world.effects.empty()&&world.randomStreams().snapshot()==rng&&stableIds()==ids,
                badVisual?"Late PO ANI/IMG closure failure rolls back a privately staged source cast":
                          "Late PO ATK response failure rolls back a privately staged source cast");
        }
        // Same timestamped input is pumped at different render schedules;
        // compare every completed fixed tick, not just final HP.
        const auto schedule=[&](int fps,bool budgeted) {
            Progression p(regions);World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();
            CharacterStore c(std::filesystem::absolute("source-schedule-"+std::string(ani_clock::policyName(clock))+"-"+std::to_string(fps)));
            c.data["characters"][0]={{"name","Schedule"},{"class","atmage"},{"identity",CharacterIdentity{8,0,0}.json()},
                {"level",1},{"skill_initialization","source-v1"}};c.apply(0,w,p);dnf::enterExplicitSkillPreviewFixture(w);w.configureAnimationClock(clock);
            auto &r=*w.experimentalRuntime();r.configuration().configureBasicAttackTemplate({8,1},1,r.plan());r.configuration().assignSlot(0,SkillKey{8,1},r.plan());
            w.monsters.clear();w.events.clear();w.combat=true;w.freezeAi=true;w.mapWidth=3000;w.walkRects={{0,185,3000,600}};
            w.player.x=w.player.px=600;w.player.y=w.player.py=300;w.player.z=w.player.pz=0;w.player.mp=10000;
            w.randomStreams()=RandomStreams(0x1031);
            for(int n=0;n<3;++n){Actor target;target.id=n+1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
                target.x=target.px=720+n*5;target.y=target.py=301;w.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
                target.hp=target.maxHp=100000000;w.monsters.push_back(std::move(target));}
            w.synchronizeEntityHandles();w.enqueue({0,20,true});w.enqueue({16666667,20,false});
            Json frames=Json::array();w.setObjectTick([&](World &current){Json targets=Json::array();
                for(const auto &target:current.monsters)targets.push_back({{"hp",target.hp},{"position",{target.x,target.y,target.z}},
                    {"velocity",{target.vx,target.vy,target.vz}},{"animation",target.animationPath},{"life",int(target.life)}});
                Json effects=Json::array();for(const auto &effect:current.effects)effects.push_back({{"id",effect.id},{"animation",effect.animation},
                    {"position",{effect.x,effect.y,effect.z}},{"born",effect.born},{"expires",effect.expires}});
                auto ids=current.idSources().snapshot();ids.erase("requests");frames.push_back({{"tick",current.tick},{"mp",current.player.mp},
                    {"runtime",r.snapshotDiagnostics()},{"cd",r.cooldownSnapshot(current.nowMs())},{"targets",targets},{"effects",effects},
                    {"events",current.eventLog()},{"rng",current.randomStreams().snapshot()},{"ids",ids}});});
            constexpr int64_t total=2000000000;int64_t previous=0;
            if(budgeted){w.advance(total,8);while(w.pendingTicks())w.advance(0,8);}
            else for(int frame=1;frame<=fps*2;++frame){const auto now=total*frame/(fps*2);w.advance(now-previous);previous=now;}
            check(w.tick==120&&w.pendingTicks()==0,"Render schedule completes all 120 fixed ticks without deleting backlog");return frames;
        };
        const auto reference=schedule(60,false);
        for(const auto fps:{30,144})check(schedule(fps,false)==reference,"Source skill tick/contact/effect/MP/CD/RNG trace identical at "+std::to_string(fps)+" render pumps per second");
        check(schedule(1,true)==reference,"One two-second pump with eight-tick budget and catch-up preserves every source skill tick");
        evidence.push_back({{"phase","render_determinism"},{"clock",ani_clock::policyName(clock)},{"ticks",reference.size()},{"schedules",{30,60,144,"2s-budget8"}}});
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"scope","One reviewed source NUT state/PO family in five-job matrix; normal branch/passive qualification still incomplete"},
        {"original_dynamic_comparison","pending_user"},{"seven_jobs_complete",false}};
    }catch(const std::exception &error){writeJson("source-skill-exception.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence}});throw;}
}
} // namespace dnf
