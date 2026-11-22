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
            "reference Fighter jump boundaries retain current long ANI holds and switch on motion state");
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
              hasPlanDiagnostic("fighter_reference_effect_binding_inferred","liftupper"),
            "Reviewed 1031 Upper visual inference remains explicit and is not claimed as a reference caller");
        const auto *energy=findAction("energyball");
        const auto *charge=energy&&!energy->nativeStages.empty()?
            findCue(energy->nativeStages.front().layers,"character/fighter/effect/animation/energycharge.ani"):nullptr;
        const auto *shoot=energy&&energy->nativeStages.size()>1?
            findCue(energy->nativeStages[1].layers,"character/fighter/effect/animation/energyballshoot.ani"):nullptr;
        check(charge&&charge->controllerSubstates==std::vector<int>({12,16})&&charge->controllerStyle<0&&
              sourceSkillVisualCueMatches(*charge,12,1)&&sourceSkillVisualCueMatches(*charge,16,0),
            "reference EnergyCharge cue is selected only for controller substates 12 or 16");
        check(shoot&&shoot->controllerSubstates==std::vector<int>({12})&&shoot->controllerStyle==1&&
              sourceSkillVisualCueMatches(*shoot,12,1)&&!sourceSkillVisualCueMatches(*shoot,12,0)&&
              !sourceSkillVisualCueMatches(*shoot,16,1),
            "reference EnergyBallShoot cue requires substate 12 and style 1");
        check(heldTargetWidthVisualScale(100)==1&&heldTargetWidthVisualScale(175)==2&&
              heldTargetWidthVisualScale(250)==3&&heldTargetWidthVisualScale(400)==3&&
              heldTargetWidthVisualScale(std::numeric_limits<double>::infinity())==1,
            "Spire target-width scale follows the bounded reference 1-to-3 curve and has a stable invalid-input fallback");
        const auto &tackle=plan->sourceSkillActions.at({1,54});
        Json tackleLayers=Json::array(),tackleDiagnostics=Json::array();
        for(const auto &layer:tackle.nativeStages.front().layers)tackleLayers.push_back(layer.source.memberPath);
        for(const auto &diagnostic:plan->diagnostics)
            if(diagnostic.value("skill","")=="shouldertackle")tackleDiagnostics.push_back(diagnostic);
        const auto *tackleHit=findCue(tackle.nativeStages.front().contactEffects,
            "character/fighter/effect/animation/shouldertacklehit.ani");
        evidence.push_back({{"phase","fighter_reference_tackle_visual_binding"},{"layers",tackleLayers},
            {"contact_effect",tackleHit?tackleHit->snapshot():Json()},{"diagnostics",tackleDiagnostics},
            {"stage_count",tackle.nativeStages.size()}});
        check(hasLayer(tackle.nativeStages.front(),"character/fighter/effect/animation/shouldertackle.ani")&&
              tackleHit&&tackleHit->trigger==SourceSkillVisualTrigger::AcceptedHit&&
              !sourceSkillVisualCueMatches(*tackleHit,0,0),
            "reference ShoulderTackle action ANI stays separate from its accepted-hit-only ShoulderTackleHit cue");
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
            "ClosePunchExecute is attached only through its exact reference ANI callsite");
        // Beat Drive: the current1031 state53 handler owns both the four own CHR
        // motions and a one-shot seven-instance effect pool. Only the instances
        // that the handler actually plays may be attached; the remaining
        // same-family ANI (punch/turn_end/kick_dust_turn/foot_right) have no
        // recovered play site and stay unattached.
        const auto *beat=findAction("randomkick");
        const auto layerPaths=[](const SourceNativeStage &stage) {
            std::vector<std::string> paths;
            for(const auto &layer:stage.layers)paths.push_back(normalize(layer.source.memberPath));
            return paths;
        };
        const auto hasPath=[](const std::vector<std::string> &paths,const std::string &leaf) {
            return std::find(paths.begin(),paths.end(),"character/fighter/effect/animation/randomkick/"+leaf)==paths.end()?false:true;
        };
        const auto leafIs=[](const std::string &full,const std::string &leaf) {
            const auto slash=full.find_last_of('/');
            return (slash==std::string::npos?full:full.substr(slash+1))==leaf;
        };
        check(beat&&beat->nativeStages.size()==4&&beat->castSound=="FT_BEAT_DRIVE",
            "Beat Drive keeps its four own CHR stages and takes the native FT_BEAT_DRIVE cast cue");
        std::vector<std::string> kickLayers,fanLayers,punchLayers;
        int kickRepeatStatic=-1;
        if(beat&&beat->nativeStages.size()==4) {
            kickLayers=layerPaths(beat->nativeStages[1]);fanLayers=layerPaths(beat->nativeStages[2]);
            punchLayers=layerPaths(beat->nativeStages[3]);kickRepeatStatic=beat->nativeStages[1].repeatStatic;
        }
        check(hasPath(kickLayers,"kick.ani")&&hasPath(kickLayers,"kick_dust_foot.ani")&&kickLayers.size()==2&&kickRepeatStatic==0,
            "Beat Drive kick stage owns exactly kick + kick_dust_foot and repeats on static operand 0");
        bool fanSynced=beat&&beat->nativeStages.size()==4&&fanLayers.size()==5&&
            hasPath(fanLayers,"kick_dust_turn.ani")&&hasPath(fanLayers,"kick_dust_foot_right.ani");
        if(fanSynced)for(const auto &layer:beat->nativeStages[2].layers) {
            const auto full=normalize(layer.source.memberPath);
            if(leafIs(full,"turn.ani")||leafIs(full,"spin-punch1.ani")||leafIs(full,"spin-punch2.ani"))
                fanSynced=fanSynced&&layer.synchronizedToBody;
        }
        Json fanDetail=Json::array();
        if(beat&&beat->nativeStages.size()==4)for(const auto &layer:beat->nativeStages[2].layers)
            fanDetail.push_back({{"path",normalize(layer.source.memberPath)},{"synced",layer.synchronizedToBody},{"layer",layer.layer}});
        check(fanSynced&&hasPath(fanLayers,"turn.ani")&&hasPath(fanLayers,"spin-punch1.ani")&&hasPath(fanLayers,"spin-punch2.ani"),
            ("Beat Drive phase2/3 stage creates both cached dust entities and keeps turn/spin-punch body-frame synchronized: "+
             Json{{"fan_layers",fanLayers},{"synced",fanSynced},{"detail",fanDetail}}.dump()).c_str());
        std::array<double,3> punchOffset{};
        if(beat&&beat->nativeStages.size()==4)for(const auto &layer:beat->nativeStages[3].layers)
            if(leafIs(normalize(layer.source.memberPath),"randomkickpunch.ani"))punchOffset=layer.offset;
        check(hasPath(punchLayers,"randomkickpunch.ani")&&hasPath(punchLayers,"kick_dust_foot_left.ani")&&
              punchLayers.size()==2&&beat->nativeStages[3].sound=="FT_BEAT_DRIVE_FIN",
            "Beat Drive finisher stage plays only RandomKickPunch plus the left foot dust");
        check(std::abs(punchOffset[0]-60)<1e-9&&std::abs(punchOffset[1]+65)<1e-9&&std::abs(punchOffset[2])<1e-9,
            "RandomKickPunch keeps the only non-zero native attach position: X=60, Y=-65, Z=0");
        check(!hasPath(kickLayers,"punch.ani")&&!hasPath(kickLayers,"turn_end.ani")&&
              !hasPath(punchLayers,"punch.ani")&&!hasPath(punchLayers,"turn_end.ani")&&
              !hasPath(fanLayers,"punch.ani")&&!hasPath(fanLayers,"turn_end.ani"),
            "Beat Drive does not attach the two same-family ANI that the native handler never plays");
        evidence.push_back({{"phase","current1031_beat_drive_visual_binding"},
            {"cast_sound",beat?Json(beat->castSound):Json()},
            {"kick_layers",kickLayers},{"fan_layers",fanLayers},{"punch_layers",punchLayers},
            {"native_callers",beat?beat->evidence.value("current_native_callers",Json()):Json()}});
        {
            ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
            runtime.configuration().configureSourceSkillAction({1,82},1,*plan);
            CharacterActionRequest request;request.action=CharacterAction::Skill;request.skill=SkillKey{1,82};request.inputDown=true;
            check(runtime.request(request),"Beat Drive request enters the shared Fighter stage executor");
            ExperimentalActorState actor;actor.x=300;actor.y=300;actor.mp=0;actor.fighterReferenceTestFreedom=true;
            std::vector<int> visits;std::vector<std::vector<std::string>> kickPublishes;
            std::vector<std::string> fanPublish,punchPublish,dustPublish;std::set<std::string> sounds,attackSources;
            int kickRestarts=0,stage2Tick=-1,stage3Tick=-1,fanFirstTick=-1,fanLastTick=-1,dustFirstTick=-1;
            const auto walk=[](double,double){return true;};
            for(uint64_t tick=1;tick<=400;++tick) {
                auto out=runtime.advance(tick,actor,walk);actor=out.actor;
                for(const auto &sound:out.sounds)sounds.insert(sound);
                for(const auto &frame:out.attacks)
                    if(frame.attack&&!frame.suppressBodyDamage)attackSources.insert(normalize(frame.attack->source.memberPath));
                for(const auto &item:out.diagnostics)if(item.value("code","")=="fighter_reference_native_stage")visits.push_back(item.value("stage",-1));
                if(!visits.empty()&&stage2Tick<0&&visits.back()==2)stage2Tick=int(tick);
                if(!visits.empty()&&stage3Tick<0&&visits.back()==3)stage3Tick=int(tick);
                if(out.skillAnimationLayers.empty())continue;
                std::vector<std::string> published;
                for(const auto &layer:out.skillAnimationLayers)published.push_back(normalize(layer.source.memberPath));
                if(hasPath(published,"kick.ani")) {
                    kickPublishes.push_back(published);
                    if(out.animationClock&&out.animationClock->elapsedMs==0)++kickRestarts;
                }
                if(hasPath(published,"spin-punch1.ani")) {
                    if(fanFirstTick<0)fanFirstTick=int(tick);
                    fanLastTick=int(tick);fanPublish=published;
                }
                if(hasPath(published,"kick_dust_turn.ani")&&dustFirstTick<0) {dustFirstTick=int(tick);dustPublish=published;}
                if(hasPath(published,"randomkickpunch.ani"))punchPublish=published;
            }
            Json heard=Json::array();for(const auto &sound:sounds)heard.push_back(sound);
            Json landed=Json::array();for(const auto &source:attackSources)landed.push_back(source);
            evidence.push_back({{"phase","current1031_beat_drive_runtime"},
                {"stage_visits",visits},{"kick_publishes",int(kickPublishes.size())},
                {"kick_restarts",kickRestarts},
                {"stage2_tick",stage2Tick},{"stage3_tick",stage3Tick},
                {"fan_first_tick",fanFirstTick},{"fan_last_tick",fanLastTick},
                {"dust_first_tick",dustFirstTick},
                {"fan_publish",fanPublish},{"dust_publish",dustPublish},{"punch_publish",punchPublish},
                {"sounds",std::move(heard)},{"attack_sources",std::move(landed)}});
            const std::vector<int> expected(7,1);
            check(visits.size()==9&&std::equal(expected.begin(),expected.end(),visits.begin())&&
                  visits[7]==2&&visits[8]==3&&kickRestarts==7,
                "Beat Drive visits its kick stage seven times from static operand 0 and reinstalls its root clock each time");
            check(!kickPublishes.empty()&&
                  std::all_of(kickPublishes.begin(),kickPublishes.end(),[&](const std::vector<std::string> &paths) {
                      return paths.size()==2&&hasPath(paths,"kick.ani")&&hasPath(paths,"kick_dust_foot.ani");
                  }),
                "Every published kick tick carries exactly its own two effect layers and nothing else");
            check(stage2Tick>0&&dustFirstTick==stage2Tick&&
                  hasPath(dustPublish,"turn.ani")==false&&
                  hasPath(dustPublish,"kick_dust_turn.ani")&&hasPath(dustPublish,"kick_dust_foot_right.ani")&&
                  hasPath(punchPublish,"randomkickpunch.ani")&&hasPath(punchPublish,"kick_dust_foot_left.ani"),
                "Beat Drive creates the two cached dust entities on the phase-2 stage entry and the punch pair on the finisher stage");
            // The exe schedules phase 3 one 200 ms command step after phase 2,
            // and native effect objects keep their own clip across the body
            // stage boundary, so the fan is neither born early nor cut off.
            const int fanDelayMs=stage2Tick>0&&fanFirstTick>0?(fanFirstTick-stage2Tick)*16:0;
            check(fanFirstTick>0&&fanDelayMs>=190&&fanDelayMs<=215&&
                  hasPath(fanPublish,"turn.ani")&&hasPath(fanPublish,"spin-punch1.ani")&&hasPath(fanPublish,"spin-punch2.ani"),
                "Beat Drive births the body-synchronized fan 200 ms into its second stage");
            check(stage3Tick>0&&fanLastTick>=stage3Tick&&hasPath(punchPublish,"kick_dust_foot_left.ani"),
                "The fan instance survives the punch-stage boundary instead of restarting with the body");
            check(sounds.count("FT_BEAT_DRIVE")&&sounds.count("CHASERP_SWING")&&
                  sounds.count("FT_BEAT_DRIVE_SPIN")&&sounds.count("FT_BEAT_DRIVE_FIN")&&
                  !runtime.attacking(),
                "Beat Drive emits its four native sound cues and clears the action at the source boundary");
            check(attackSources.count("character/fighter/attackinfo/randomkickstart.atk")&&
                  attackSources.count("character/fighter/attackinfo/randomkickend.atk"),
                "Beat Drive lands both its kick and its finisher source ATK instead of visuals only");
        }
        {
            // Attack-speed sensitivity of the stage-layer ledger. The native
            // ledger is independent of the body instance, but not of the
            // actor's attack-rate context: a cue authored at delay200 must
            // reach the body's frame at the same *virtual* moment. At
            // rate150 that is 200*100/150 = 133 ms of wall time, so the same
            // cue appearing 200 ms late is the defect this check pins down.
            const auto walkFast=[](double,double){return true;};
            const auto fanBirth=[&](double attackPerMille,int &fanTick,int &stage2Tick,int &stage3Tick) {
                ExperimentalCharacterRuntime runtime(plan);
                runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::InferredReferencePercentDeadlines);
                runtime.configuration().configureSourceSkillAction({1,82},1,*plan);
                CharacterActionRequest request;request.action=CharacterAction::Skill;request.skill=SkillKey{1,82};request.inputDown=true;
                if(!runtime.request(request))return false;
                ExperimentalActorState actor;actor.x=300;actor.y=300;actor.mp=0;actor.fighterReferenceTestFreedom=true;
                actor.attackPerMille=attackPerMille;
                for(uint64_t tick=1;tick<=400;++tick) {
                    auto out=runtime.advance(tick,actor,walkFast);actor=out.actor;
                    for(const auto &item:out.diagnostics) {
                        const auto code=item.value("code","");
                        if(code!="fighter_reference_native_stage")continue;
                        const auto stage=item.value("stage",-1);
                        if(stage==2&&stage2Tick<0)stage2Tick=int(tick);
                        if(stage==3&&stage3Tick<0)stage3Tick=int(tick);
                    }
                    if(fanTick>=0||out.skillAnimationLayers.empty())continue;
                    for(const auto &layer:out.skillAnimationLayers)
                        if(normalize(layer.source.memberPath)=="character/fighter/effect/animation/randomkick/spin-punch1.ani") {
                            fanTick=int(tick);break;
                        }
                }
                return fanTick>0&&stage2Tick>0;
            };
            int slowFan=-1,slowStage2=-1,slowStage3=-1,fastFan=-1,fastStage2=-1,fastStage3=-1;
            const bool slowOk=fanBirth(1000.0,slowFan,slowStage2,slowStage3);
            const bool fastOk=fanBirth(1500.0,fastFan,fastStage2,fastStage3);
            const int slowDelayMs=slowOk?(slowFan-slowStage2)*16:0;
            const int fastDelayMs=fastOk?(fastFan-fastStage2)*16:0;
            evidence.push_back({{"phase","stage_layer_attack_speed"},
                {"rate1000_fan_tick",slowFan},{"rate1000_stage2_tick",slowStage2},{"rate1000_delay_ms",slowDelayMs},
                {"rate1500_fan_tick",fastFan},{"rate1500_stage2_tick",fastStage2},{"rate1500_delay_ms",fastDelayMs}});
            check(slowOk&&slowDelayMs>=190&&slowDelayMs<=215,
                ("At rate100 the fan still births 200 ms into phase 2: "+
                 Json{{"fan_tick",slowFan},{"stage2_tick",slowStage2},{"delay_ms",slowDelayMs}}.dump()).c_str());
            check(fastOk&&fastDelayMs>=115&&fastDelayMs<=150&&fastDelayMs<slowDelayMs,
                ("At rate150 the same delay200 cue births at 133 ms, so the layer ledger follows the body rate: "+
                 Json{{"fan_tick",fastFan},{"stage2_tick",fastStage2},{"delay_ms",fastDelayMs}}.dump()).c_str());
        }
        const auto walk=[](double,double){return true;};
        for(bool accepted:{false,true}) {
            ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
            runtime.configuration().configureSourceSkillAction({1,9},1,*plan);
            CharacterActionRequest request;request.action=CharacterAction::Skill;request.skill=SkillKey{1,9};request.inputDown=true;
            check(runtime.request(request),"Shared source Suplex request is accepted without a basic/Upper template");
            ExperimentalActorState actor;actor.x=300;actor.y=300;actor.mp=0;actor.fighterReferenceTestFreedom=true;
            uint64_t owner=0;bool tryVolume=false,followup=false,release=false;int directHits=0,shockwaves=0;
            bool independentWave=false;
            for(uint64_t tick=1;tick<=100;++tick) {
                auto out=runtime.advance(tick,actor,walk);actor=out.actor;
                for(const auto &frame:out.attacks) {
                    if(frame.sourceEntity) {
                        independentWave|=frame.sourceOrigin==std::array<double,3>{actor.x-47,actor.y,actor.z}&&
                            frame.attack&&frame.attack->source.memberPath=="passiveobject/character/fighter/attackinfo/suplexsub.atk"&&
                            frame.skillModifiers&&frame.skillModifiers->percent==0&&frame.skillModifiers->independentPercent==168&&
                            !frame.sourceLift;
                    }
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
                for(const auto &visual:out.sourceSkillVisuals)
                    if(visual.kind==ExperimentalSourceVisual::Kind::Spawn)++shockwaves;
            }
            check(tryVolume&&followup==accepted&&release==accepted,
                "Suplex follow-up and release require accepted source contact; empty cast stops at try animation");
            check(directHits==int(accepted),"Suplex native held-target callback fires once after accepted grab and never on an empty cast");
            check(shockwaves==int(accepted)&&independentWave==accepted,
                "Suplex impact emits one separately-owned shockwave with native offset, independent column1 and original ATK lift only after capture");
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
        evidence.push_back({{"phase","fighter_reference_jump"},{"poses",poses},{"rose",rose},{"fell",fell},{"landed",landed},
            {"runtime",jump.snapshotDiagnostics()}});
        check(rose&&fell&&landed&&poses.count(7)&&poses.count(13),
            "Native jump enters descending and landing source frames without waiting 100000/10000ms held poses");
        const auto &nen=plan->sourceSkillActions.at({1,12});
        check(nen.nativeProjectile&&nen.objectId==21002&&nen.offset[2]>0&&nen.objectAnimation,
            "Source Nen projectile retains actual OBJ/ANI/ATK and a native muzzle-height consumer");
        check(nen.nativeStages.size()==2&&nen.nativeStages[0].motionTag=="[throw motion 2-1]"&&
              nen.nativeStages[1].motionTag=="[throw motion 2-2]"&&
              nen.nativeStages[0].motion.memberPath=="character/fighter/animation/throw1.ani"&&
              nen.nativeStages[1].motion.memberPath=="character/fighter/animation/shoot.ani"&&
              nen.nativeProjectile->birthStage==1&&nen.nativeProjectile->birthElapsedMs>=0,
            "Nen source group selector resolves CHR throw2 phases and release-effect frame gate instead of Buff placeholder");
        for(const auto *name:{"throwsand","kikouken"}) {
            const auto *cast=findAction(name);
            check(cast&&cast->nativeStages.size()==2&&cast->nativeProjectile&&cast->nativeProjectile->birthStage==1,
                std::string(name)+" uses two native throw phases and emits only from release");
            const bool sand=std::string(name)=="throwsand";
            check(cast->nativeStages[0].motionTag==(sand?"[throw motion 1-1]":"[throw motion 2-1]")&&
                cast->nativeStages[1].motionTag==(sand?"[throw motion 1-2]":"[throw motion 2-2]")&&
                cast->offset==(sand?std::array<double,3>{0,0,65}:std::array<double,3>{107,1,62}),
                std::string(name)+" resolves its current CHR group and native XYZ instead of Buff/feet");
            for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::InferredReferencePercentDeadlines}) {
                ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(clock);
                runtime.configuration().configureSourceSkillAction(cast->key,1,*plan);
                CharacterActionRequest request;request.action=CharacterAction::Skill;request.skill=cast->key;request.inputDown=true;
                check(runtime.request(request),std::string(name)+" accepts the shared source action");
                ExperimentalActorState actor;actor.x=300;actor.y=300;actor.fighterReferenceTestFreedom=true;
                int spawned=0;bool prepared=false,released=false,badBirth=false;Json trace=Json::array();
                for(uint64_t tick=1;tick<=150;++tick) {
                    const auto out=runtime.advance(tick,actor,walk);actor=out.actor;
                    for(const auto &diagnostic:out.diagnostics)if(diagnostic.value("code","")=="fighter_reference_native_stage")
                        check(out.animationPath==cast->nativeStages[1].motion.memberPath&&
                            (out.animationClock?out.animationClock->frame==0:out.poseFrame==0),
                            "A native phase boundary displays the new frame0 in the same tick, without a stale prior pose");
                    prepared|=out.animationPath==cast->nativeStages[0].motion.memberPath;
                    released|=out.animationPath==cast->nativeStages[1].motion.memberPath;
                    if(runtime.attacking()||!out.sourceSkillVisuals.empty())trace.push_back({{"tick",tick},{"path",out.animationPath},{"frame",out.poseFrame},{"visuals",out.sourceSkillVisuals.size()}});
                    for(const auto &visual:out.sourceSkillVisuals)if(visual.kind==ExperimentalSourceVisual::Kind::Spawn) {
                        const auto bodyFrame=out.animationClock?int(out.animationClock->frame):out.poseFrame;
                        ++spawned;badBirth|=out.animationPath!=cast->nativeStages[1].motion.memberPath||
                            bodyFrame<cast->nativeProjectile->birthFrame;
                        check(visual.position==std::array<double,3>{actor.x+actor.direction*cast->offset[0],actor.y+cast->offset[1],actor.z+cast->offset[2]},
                            std::string(name)+" actual emitted entity retains native spawn position");
                    }
                }
                evidence.push_back({{"phase",name},{"clock",ani_clock::policyName(clock)},{"prepared",prepared},{"released",released},{"spawned",spawned},{"bad_birth",badBirth},{"attacking",runtime.attacking()},{"trace",trace}});
                check(prepared&&released&&spawned==1&&!badBirth&&!runtime.attacking(),
                    std::string(name)+" traverses preparation/release, emits once at native gate and finishes on both clocks");
            }
        }
        const auto *web=findAction("throwweb");
        const auto burst=readPtl(pvf,"character/fighter/particle/throwweb.ptl");
        const auto motion=readPtl(pvf,"character/fighter/particle/throwweb.ptl",PtlUse::ObjectMotion);
        check(!burst.valid()&&!burst.error.empty()&&motion.error.empty()&&motion.fullyConsumed()&&motion.objects.empty(),
            "Motion-only PO driver is admitted separately from drawable particle bursts");
        check(motion.velocity[0]==std::array<double,2>{400,0}&&motion.velocity[2]==std::array<double,2>{50,50}&&
            motion.changingTermMs==std::array<int32_t,3>{0,0,900}&&motion.gravity==100,
            "ThrowWeb preserves ordered PTL axes: 900ms applies to Z rather than decelerating X");
        check(web&&web->attackDefinition.usable(),"Web damage delegates its dormant hold entry to the actual status host");
        const auto webStatus=readSkillAttackStatuses(*plan->skills.at(web->key).data,1);
        check(webStatus.usable()&&webStatus.entries.size()==1&&webStatus.entries[0].kind==AttackStatusKind::Hold&&
            webStatus.entries[0].chancePercent==100&&webStatus.entries[0].level==37&&webStatus.entries[0].durationMs==5000,
            "Current Web selected SKL columns set capped chance, authored level and duration without localized-label matching");
        check(web&&web->nativeStages.size()==1&&!web->nativeProjectile&&web->nativePull&&
              web->nativeStages[0].motionSlot==35&&web->nativeStages[0].attackSlot==22,
            "Current state43 owns CHR motion35 and ATK22, without mixing in legacy state13 PO21015");
        check(hasLayer(web->nativeStages[0],"character/fighter/effect/animation/throwwebnormal.ani")&&
              hasLayer(web->nativeStages[0],"character/fighter/effect/animation/throwweblineardodge.ani"),
            "Both current Web layers follow the dedicated body timeline at the native origin");
        for(int direction:{-1,1}) {
            ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(ani_clock::ClockPolicy::SourceDelay100);
            runtime.configuration().configureSourceSkillAction(web->key,1,*plan);
            CharacterActionRequest request;request.action=CharacterAction::Skill;request.skill=web->key;request.inputDown=true;
            check(runtime.request(request),"Web enters the shared body action executor");
            ExperimentalActorState actor;actor.x=300;actor.y=300;actor.direction=direction;actor.fighterReferenceTestFreedom=true;
            bool collision=false,layers=false;int objects=0;std::map<std::string,int> sounds;
            for(uint64_t tick=1;tick<=150;++tick) {
                const auto out=runtime.advance(tick,actor,walk);actor=out.actor;
                layers|=out.skillAnimationLayers.size()==2;
                for(const auto &sound:out.sounds)++sounds[sound];
                for(const auto &visual:out.sourceSkillVisuals)objects+=visual.kind==ExperimentalSourceVisual::Kind::Spawn;
                for(const auto &frame:out.attacks)if(!frame.boxes.empty()&&frame.attack) {
                    collision=true;check(frame.sourceFrame>=3&&frame.sourceFrame<=5&&!frame.suppressBodyDamage,
                        "Only authored outbound Web frames3..5 publish the current attack geometry");
                }
            }
            check(collision&&layers&&objects==0&&!runtime.attacking(),"Dedicated Web presents both layers and finishes without a legacy PO");
            check(sounds["FT_NET"]==1&&sounds["NET_OUT"]==1&&sounds["FT_NET_PULL"]==1&&sounds["NET_IN"]==1,
                "Native Web frame2/frame5 sounds fire exactly once rather than every held sample");
        }
        // Input and deadlines are independent: charge power may reach maximum
        // while the user continues holding the original skill key.
        for(const auto clock:{std::optional<ani_clock::ClockPolicy>{},
              std::optional<ani_clock::ClockPolicy>{ani_clock::ClockPolicy::SourceDelay100},
              std::optional<ani_clock::ClockPolicy>{ani_clock::ClockPolicy::InferredReferencePercentDeadlines}})
        for(int releaseTick:{2,90,0}) {
            ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(clock);
            runtime.configuration().configureSourceSkillAction({1,54},1,*plan);
            runtime.configuration().assignSlot(0,SkillKey{1,54},*plan);
            CharacterActionRequest key;key.action=CharacterAction::Skill;key.skill=SkillKey{1,54};key.inputKey=20;key.inputDown=true;
            check(runtime.request(key),"Charge tracks its physical activation key");
            ExperimentalActorState actor;actor.x=300;actor.y=300;actor.fighterReferenceTestFreedom=true;
            bool waited=false,released=false;int firstRelease=0;double independent=0;
            for(uint64_t tick=1;tick<=380;++tick) {
                if(int(tick)==releaseTick){key.inputDown=false;runtime.request(key);}
                if(tick==50) {auto other=key;other.inputKey=21;other.inputDown=true;other.skill=SkillKey{1,19};runtime.request(other);}
                const auto out=runtime.advance(tick,actor,walk);actor=out.actor;
                const auto frame=out.animationClock?int(out.animationClock->frame):out.poseFrame;
                if(frame==1&&runtime.attacking()) {
                    waited=true;check(actor.x==300,"Charge hold cannot start the dash movement before release");
                }
                if(frame>=2&&out.animationPath==tackle.nativeStages[0].motion.memberPath&&!firstRelease)firstRelease=int(tick);
                for(const auto &f:out.attacks)if(f.skill==std::optional<SkillKey>{{1,54}}&&f.sourceFrame>=2&&f.skillModifiers) {
                    released=true;independent=std::max(independent,double(f.skillModifiers->independentPercent));
                }
            }
            check(released&&!runtime.attacking(),"Tap, long-hold and native maximum-wait all reach release and recovery");
            if(releaseTick==90)check(waited&&firstRelease==90&&independent==691,
                "Maximum charge strength does not force release; a different rejected key cannot release the owning action");
            if(releaseTick==0)check(waited&&firstRelease>=300&&firstRelease<=301,
                "Only the actual source static6 five-second maximum can release a continuously held charge");
            if(releaseTick==2)check(firstRelease>=6&&firstRelease<=8&&independent<691,
                "Release before the hold frame is remembered and preserves the finite preparation without full-charge damage");
        }
        for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::InferredReferencePercentDeadlines}) {
            const auto duration=[&](double speed) {
                ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(clock);
                runtime.configuration().configureSourceSkillAction({1,19},1,*plan);
                runtime.configuration().assignSlot(0,SkillKey{1,19},*plan);
                CharacterActionRequest key;key.action=CharacterAction::Skill;key.skill=SkillKey{1,19};key.inputKey=20;key.inputDown=true;
                check(runtime.request(key),"Speed fixture enters the authored LowKick");
                ExperimentalActorState actor;actor.fighterReferenceTestFreedom=true;actor.attackPerMille=speed;
                int ticks=0;do {actor=runtime.advance(++ticks,actor,walk).actor;}while(runtime.attacking()&&ticks<200);
                check(!runtime.attacking(),"Finite native action completes without an added recovery timer");return ticks;
            };
            const int normal=duration(1000),fast=duration(1500);
            check(clock==ani_clock::ClockPolicy::SourceDelay100?normal==fast:fast<normal,
                "Actor attack speed affects scaled body deadlines while explicit source-rate100 remains an unscaled comparison");
            evidence.push_back({{"phase","body_speed"},{"clock",ani_clock::policyName(clock)},{"normal_ticks",normal},{"fast_ticks",fast}});
            for(const std::string ending:{"release_during_hitstop","release_during_block","lost_focus","cancel"}) {
                ExperimentalCharacterRuntime runtime(plan);runtime.setAnimationClockPolicy(clock);
                runtime.configuration().configureSourceSkillAction({1,54},1,*plan);
                runtime.configuration().assignSlot(0,SkillKey{1,54},*plan);
                CharacterActionRequest key;key.action=CharacterAction::Skill;key.skill=SkillKey{1,54};key.inputKey=20;key.inputDown=true;
                check(runtime.request(key),"Hold lifecycle fixture accepts its physical activation key");
                ExperimentalActorState actor;actor.x=300;actor.y=300;actor.fighterReferenceTestFreedom=true;
                ExperimentalTickResult before;for(uint64_t tick=1;tick<=30;++tick){before=runtime.advance(tick,actor,walk);actor=before.actor;}
                check(before.animationClock&&before.animationClock->frame==1,"Fixture reaches actual native hold frame before interruption");
                if(ending=="cancel")runtime.cancel(ControllerCancelReason::ExplicitReset);
                else if(ending=="lost_focus")runtime.releaseInputs();
                else {key.inputDown=false;runtime.request(key);actor.hitStopped=ending=="release_during_hitstop";actor.blocked=ending=="release_during_block";}
                for(uint64_t tick=31;tick<=45;++tick) {
                    const auto paused=runtime.advance(tick,actor,walk);actor=paused.actor;
                    if(ending=="release_during_hitstop")
                        check(paused.animationClock&&paused.animationClock->frame==1&&paused.animationClock->elapsedMs==before.animationClock->elapsedMs&&actor.x==300,
                            "Hitstop freezes a released hold until its owning actor can advance");
                    if(ending=="release_during_block")check(!runtime.attacking()&&actor.x==300,
                        "A blocking hurt/stun cancels the charge through the existing actor interruption contract");
                }
                actor.hitStopped=actor.blocked=false;bool release=false;
                for(uint64_t tick=46;tick<=160;++tick) {
                    const auto out=runtime.advance(tick,actor,walk);actor=out.actor;
                    for(const auto &frame:out.attacks)release|=frame.skill==std::optional<SkillKey>{{1,54}}&&frame.sourceFrame>=2;
                }
                check(!runtime.attacking()&&((ending=="cancel"||ending=="release_during_block")?!release:release),
                    "Release/focus loss resumes once; explicit cancellation cannot leave a delayed charge or recast");
            }
        }
        for(const auto &entry:plan->sourceSkillActions)for(const auto &stage:entry.second.nativeStages)
            check(stage.runtimeDelays.empty(),"No Fighter held pose is replaced by an adjacent arbitrary fixed delay");

        evidence.push_back({{"phase","fighter_reference_shared_stages"},{"plan",plan->snapshot()},{"executed_by_child_agent",false}});
    }
    RegionCatalog regions(pvf,assets);
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::InferredReferencePercentDeadlines})
    for(int direction:{-1,1}) {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        world.configureAnimationClock(clock);
        CharacterStore store(std::filesystem::absolute("web-lifecycle-"+std::to_string(direction)+"-"+std::to_string(int(clock))));
        store.data={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
        store.data["characters"][0]={{"name","WebLifecycle"},{"class","fighter"},
            {"identity",CharacterIdentity{1,0,0}.json()},{"level",1},{"weapon",0},{"skill_initialization","source-v1"}};
        Progression progress(regions);store.apply(0,world,progress);
        DebugOverrides debug;debug.enabled=true;world.applyDebugOverrides(debug,1);
        check(world.setExperimentalSkillPreviewEnabled(true).ok,"Web lifecycle uses isolated main World source admission");
        auto &runtime=*world.experimentalRuntime();runtime.configuration().configureSourceSkillAction({1,52},1,runtime.plan());
        runtime.configuration().assignSlot(0,SkillKey{1,52},runtime.plan());
        world.combat=true;world.freezeAi=true;world.freeCd=true;world.monsters.clear();
        world.mapWidth=3000;world.walkRects={{0,0,3000,1200}};world.blockedRects.clear();
        world.player.x=world.player.px=1000;world.player.y=world.player.py=344;world.player.dir=direction;
        world.randomStreams()=RandomStreams(67);
        for(int i=0;i<2;++i) {
            Actor target;target.id=i+1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
            target.x=target.px=1000+direction*(160+i*140);target.y=target.py=344;target.dir=-direction;
            world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
            target.hp=target.maxHp=100000000;world.monsters.push_back(std::move(target));
        }
        world.synchronizeEntityHandles();world.enqueue({world.simulationNanoseconds(),20,true});
        world.enqueue({world.simulationNanoseconds()+16666667,20,false});
        bool pulled=false,clockedPull=false;std::set<int> instances;std::set<EntityHandle> held;
        for(int tick=0;tick<420;++tick) {
            world.advanceSingleTick();
            if(world.player.animationClock&&world.player.animationClock->frame==7)
                for(const auto &target:world.monsters)clockedPull|=target.capturedBy==0;
            for(const auto &fx:world.effects)if(fx.skill==52&&world.nowMs()<fx.expires&&fx.phase=="source-nut:passive-object")instances.insert(fx.id);
            for(const auto &target:world.monsters)if(std::abs(target.x-(1000+direction*50))<0.001)pulled=true;
            for(const auto &target:world.monsters)for(const auto &effect:world.statusEffects(target.handle))
                if(effect.at("kind")=="hold") {held.insert(target.handle);check(!world.statusStunned(target.handle),"Web hold never becomes a stun action lock");}
        }
        writeJson("web-world-diagnostic-"+std::to_string(direction)+".json",world.snapshot());
        check(instances.empty()&&pulled&&clockedPull,"Main World current Web pulls through an owned animation clock to the native front offset without legacy net entities");
        for(const auto &target:world.monsters) {
            int hits=0;for(const auto &event:world.events)if(event.kind=="hit"&&event.target==target.id)++hits;
            check(hits==1&&target.hp<target.maxHp,"Outbound Web contacts each separated real MOB hurt box once with accepted damage");
            check(std::abs(target.x-(1000+direction*50))<0.001&&target.capturedBy<0,
                "Every qualified victim reaches the front of the caster and leaves transient capture after owner frame8");
            check(held.count(target.handle)&&world.statusEffects(target.handle).empty(),"Each net victim receives and independently expires the authored five-second hold");
        }
        check(runtime.snapshotDiagnostics().at("source_nut_entities")==0,"Web simulation entities retire at the source ANI lifetime");
    }
    for(int direction:{-1,1})for(bool targetPresent:{false,true}) {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("nen-lifecycle-"+std::to_string(direction)+"-"+std::to_string(targetPresent)));
        store.data={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
        store.data["characters"][0]={{"name","NenLifecycle"},{"class","fighter"},
            {"identity",CharacterIdentity{1,0,0}.json()},{"level",1},{"weapon",0},{"skill_initialization","source-v1"}};
        Progression progress(regions);store.apply(0,world,progress);
        DebugOverrides debug;debug.enabled=true;world.applyDebugOverrides(debug,1);
        check(world.setExperimentalSkillPreviewEnabled(true).ok,"Nen lifecycle uses explicit isolated preview admission");
        auto &runtime=*world.experimentalRuntime();
        runtime.configuration().configureSourceSkillAction({1,12},1,runtime.plan());
        runtime.configuration().assignSlot(0,SkillKey{1,12},runtime.plan());
        world.combat=true;world.freezeAi=true;world.freeCd=true;world.monsters.clear();
        world.mapWidth=3000;world.walkRects={{0,0,3000,1200}};world.blockedRects.clear();
        world.player.x=world.player.px=1000;world.player.y=world.player.py=344;world.player.dir=direction;
        world.randomStreams()=RandomStreams(67);
        if(targetPresent) for(int i=0;i<2;++i) {
            Actor target;target.id=i+1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
            target.x=target.px=1000+direction*(70+i*180);target.y=target.py=344;target.dir=-direction;
            world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
            target.hp=target.maxHp=100000000;world.monsters.push_back(std::move(target));
        }
        world.synchronizeEntityHandles();world.enqueue({world.simulationNanoseconds(),20,true});
        world.enqueue({world.simulationNanoseconds()+16666667,20,false});
        std::set<int> instances;bool moved=false,paused=false,sawPreparation=false,sawRelease=false;
        bool preparationVisual=false,releaseVisual=false,birthOnRelease=false;double firstX=0;
        Json bodyTrace=Json::array();
        for(int tick=0;tick<180;++tick) {
            world.advanceSingleTick();
            const auto &body=world.player.animationPath;
            const bool preparing=body=="character/fighter/animation/throw1.ani";
            const bool releasing=body=="character/fighter/animation/shoot.ani";
            sawPreparation|=preparing;sawRelease|=releasing;
            bool charge=false,shoot=false;
            for(const auto &cue:world.player.skillAnimationLayers) {
                charge|=cue.source.memberPath=="character/fighter/effect/animation/energycharge.ani";
                shoot|=cue.source.memberPath=="character/fighter/effect/animation/energyballshoot.ani";
            }
            preparationVisual|=preparing&&charge&&!shoot;
            releaseVisual|=releasing&&shoot&&!charge;
            if(bodyTrace.empty()||bodyTrace.back()["path"]!=body)
                bodyTrace.push_back({{"tick",world.tick},{"path",body}});
            for(const auto &fx:world.effects)if(fx.phase=="source-nut:passive-object"&&fx.skill==12&&world.nowMs()<fx.expires) {
                if(instances.empty()) {
                    firstX=fx.x;
                    birthOnRelease=releasing;
                }
                instances.insert(fx.id);moved|=direction*(fx.x-firstX)>0;
                check(fx.loop==runtime.plan().sourceSkillActions.at({1,12}).nativeProjectile->loop,
                    "Moving Nen visual preserves the same source loop as its collision entity");
                if(!paused){world.player.hitStopTicks=10;paused=true;}
            }
        }
        writeJson("nen-body-diagnostic.json",{{"preparation",sawPreparation},{"release",sawRelease},{"preparation_visual",preparationVisual},
            {"release_visual",releaseVisual},{"birth_on_release",birthOnRelease},{"body_trace",bodyTrace}});
        check(sawPreparation&&sawRelease&&preparationVisual&&releaseVisual&&birthOnRelease,
            "Nen World input plays preparation then release with separate effects and creates its projectile only at the release gate");
        check(instances.size()==1&&moved,"Nen creates one mirrored moving World projectile through hitstop");
        check(std::none_of(world.effects.begin(),world.effects.end(),[&](const Effect &fx){
            return fx.phase=="source-nut:passive-object"&&fx.skill==12&&world.nowMs()<fx.expires;
        }),"Nen runtime retires its visual and entity after completion");
        bool hit=false;
        for(const auto &event:world.events) {
            check(event.kind!="skill_rejected","Nen lifecycle never loses its entity/visual ledger");
            hit|=event.kind=="hit"&&event.name=="source_nut_passive_object";
        }
        check(hit==targetPresent,"Nen ordinary standing target accepts a real collision; empty cast does not hit");
        if(targetPresent)for(const auto &target:world.monsters) {
            size_t hits=0;for(const auto &event:world.events)if(event.kind=="hit"&&event.name=="source_nut_passive_object"&&event.target==target.id)++hits;
            check(hits==1,"Nen penetrates two separated targets and hits each exactly once");
        }
        evidence.push_back({{"phase","nen_world_lifecycle"},{"direction",direction},{"target_present",targetPresent},
            {"instances",instances.size()},{"moved",moved},{"hit",hit},{"body_trace",bodyTrace},{"birth_on_release",birthOnRelease}});
    }
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::InferredReferencePercentDeadlines}) {
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
