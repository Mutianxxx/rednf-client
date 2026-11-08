#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/storage.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/gunner_pixel_anchor.hpp"
#include <algorithm>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
Json runHedgehogRuntimeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message) {
        checks.push_back({{"passed",pass},{"message",message}});
        if(!pass){writeJson("hedgehog-failure.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}
    };
    try {
    RegionCatalog regions(pvf,assets);
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("hedgehog-"+std::string(ani_clock::policyName(clock))));
        store.data["characters"][0]={{"name","SourceHedge"},{"class","priest"},{"identity",CharacterIdentity{4,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clock);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        evidence.push_back({{"phase","plan_admission"},{"clock",ani_clock::policyName(clock)},{"diagnostics",plan.diagnostics}});
        check(plan.sourceSkillActions.size()==2&&plan.sourceSkillActions.count({4,1})&&plan.sourceSkillActions.count({4,116}),
            "Reviewed initial Upper body and separate source Hedgehog program both retain actual consumers");
        const auto &descriptor=plan.sourceSkillActions.at({4,116});
        check(descriptor.kind==SourceSkillActionKind::BodyAttack&&descriptor.state==63&&descriptor.motionSlot==90&&descriptor.attackSlot==72&&descriptor.objectId==-1,
            "Current NUT registration reads state63/own CHR motion90 and attack72 without fake passive objects");
        check(descriptor.percentColumn==0&&descriptor.fixedColumn==-1&&descriptor.flag==2&&descriptor.castSound=="PR_HEDGEHOG"&&
              descriptor.shakeAmplitude==3&&descriptor.shakeDurationMs==150,"NUT callback supplies percent column, cast sound and one flag-driven shake");
        check(descriptor.motion.memberPath=="character/priest/animation/hedgehog.ani"&&descriptor.attack.memberPath=="character/priest/attackinfo/hedgehog.atk",
            "Own Priest CHR paths drive body animation and dark magical attack");
        check(descriptor.attackDefinition.type==DamageAttackType::Magical&&descriptor.attackDefinition.element==2,
            "Real ATK retains magical type and dark element through coefficient replacement");
        check(descriptor.bodyLayers.size()==10,"Ten source ALS none-effect attachments have an actual rendering consumer");
        const auto generic=animationEffectEvents(pvf,assets,descriptor.motion.memberPath);
        check(generic.events.empty()&&generic.diagnostics.size()==10,"Generic ALS keeps unsupported native none-effect semantics; no global alias is introduced");
        evidence.push_back({{"phase","descriptor"},{"clock",ani_clock::policyName(clock)},{"source",descriptor.snapshot()},
            {"generic_als_diagnostics",generic.diagnostics}});
        std::set<std::string> expectedLayers;
        for(const auto &layer:descriptor.bodyLayers) {
            const auto &receipt=layer.evidence.at(0);
            check(receipt.at("native_kind")==5&&receipt.at("native_child_flag")==1&&receipt.at("native_flag_render_consumer")=="unsupported"&&
                  receipt.at("als_source").at("member_path")==descriptor.layersSource.memberPath,
                "Dedicated inferred layer retains exact native kind5/childFlag1 and unresolved renderer meaning");
            expectedLayers.insert(layer.source.memberPath);
        }
        for(const int level:{1,10,50}) {
            const auto operands=evaluateSourceSkillAction(descriptor,*plan.skills.at({4,116}).data,level);
            check(operands.damage.percent==float(*skillLevelValue(plan.skills.at({4,116}).data->values("[level info]"),level,0))&&
                operands.damage.fixedDamage==0&&operands.damage.replacesAttackCoefficients,"Source level "+std::to_string(level)+" reaches actual percentage operand without inventing fixed/lift columns");
        }
        const auto floor=[&]() {
            world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();runtime.publishCooldownRestore({});
            world.combat=true;world.freezeAi=true;world.freeCd=false;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};world.blockedRects.clear();
            auto &p=world.player;p.x=p.px=600;p.y=p.py=300;p.z=p.pz=0;p.vx=p.vy=p.vz=0;p.dir=1;p.mp=100000;
            p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;
        };
        const auto configure=[&](int level) {runtime.configuration().configureBasicAttackTemplate({4,116},level,plan);runtime.configuration().assignSlot(0,SkillKey{4,116},plan);};
        const auto press=[&](bool down){world.enqueue({world.simulationNanoseconds(),20,down});};
        const auto countEvents=[&](const std::string &kind,const std::string &name){size_t count=0;for(const auto &event:world.events)if(event.kind==kind&&event.name==name)++count;return count;};
        const auto root=plan.animations.at(descriptor.motion.memberPath);
        std::optional<Box> hitBox;for(const auto &frame:root->frames)for(const auto &box:frame.boxes)if(box.type==15&&box.w>0&&box.h>0&&box.d>0&&!hitBox)hitBox=box;
        check(bool(hitBox),"Actual source body contains a nonempty type15 attack volume");
        for(const int level:{1,10})for(const int direction:{-1,1})for(const bool targets:{false,true}) {
            floor();world.player.dir=direction;configure(level);
            check(runtime.configuration().binding({4,116})->attack.has_value()&&
                !runtime.configuration().binding({4,116})->unknown.contains("user_requested_temporary_template"),"Selected skill uses dedicated source body ATK rather than a basic template");
            const auto saved=runtime.configuration().snapshot();ExperimentalSkillConfiguration restored(plan);restored.restore(saved,plan);
            check(restored.snapshot()==saved,"Dedicated body controller and exact ATK source round trip through isolated test configuration");
            auto bad=saved;bad["skill_bindings"][0]["source_nut_action_controller"]["attack_slot"]=0;
            bool rejected=false;try{ExperimentalSkillConfiguration changed(plan);changed.restore(bad,plan);}catch(...){rejected=true;}
            check(rejected,"Stale source body controller receipt rejects restoration");
            const auto normal=world.skillState().snapshot(world.nowMs());
            if(targets)for(int i=0;i<3;++i) {
                Actor target;target.id=i+1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
                target.x=target.px=600+direction*(hitBox->x+hitBox->w*.5);target.y=target.py=300+hitBox->y+hitBox->h*.5;
                target.dir=-direction;world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
                target.hp=target.maxHp=100000000;world.monsters.push_back(std::move(target));
            }
            world.synchronizeEntityHandles();const auto mp=world.player.mp;press(true);world.advanceSingleTick();press(false);
            check(world.player.mp<mp&&runtime.remainingCooldown({4,116},world.nowMs())>0,"Actual slot activation commits source MP/CD with real action publication");
            bool sawMotion=false,sawVolume=false,sawResponse=false,allLayers=true,realLayerPixels=false;size_t samples=0;std::set<std::string> seenLayers;
            Json renderSamples=Json::array(),firstVolume;
            for(int tick=0;tick<110;++tick) {
                sawMotion|=world.player.animationPath==descriptor.motion.memberPath;
                if(world.player.animationPath==descriptor.motion.memberPath&&world.player.animationClock&&!world.player.skillAnimationLayers.empty()) {
                    allLayers&=world.player.skillAnimationLayers.size()==expectedLayers.size();
                    for(const auto &layer:world.player.skillAnimationLayers) {
                        seenLayers.insert(layer.source.memberPath);const auto clip=assets.animation(layer.source.memberPath);
                        auto sourceClock=*world.player.animationClock;
                        if(!layer.synchronizedToBody&&!layer.inheritBodyRate){sourceClock.ratePercent=100;sourceClock.policy=ani_clock::ClockPolicy::SourceDelay100;sourceClock.rateRevision=1;}
                        const auto child=layer.synchronizedToBody?clip->followClock(*root,sourceClock,sourceClock.loop,world.player.animationControllerDelays.get()):clip->followClock(*clip,sourceClock,layer.loop);
                        const auto pose=clip->samplePose(child,world.renderProfile());
                        check(child.frame<clip->frames.size()&&pose.frame==child.frame,"Actual render layer uses its source clock and frame");
                        if(pose.image.empty())continue;
                        const auto pixels=assets.pixels(pose.image,pose.imageFrame);realLayerPixels|=!pixels.rgba.empty();
                        const auto right=inferredGunnerPixelPoint(pose,pixels.x,pixels.y,0,0,world.renderProfile(),1);
                        const auto left=inferredGunnerPixelPoint(pose,pixels.x,pixels.y,0,0,world.renderProfile(),-1);
                        check(std::isfinite(right.x)&&std::isfinite(right.y)&&left.x==-right.x&&left.y==right.y,
                            "Source crop/ANI position/scale/rotation mirror horizontally without recentering");
                        if(renderSamples.size()<20)renderSamples.push_back({{"layer",layer.snapshot()},{"clock_frame",child.frame},
                            {"image",pose.image},{"img_frame",pose.imageFrame},{"crop",{pixels.x,pixels.y,pixels.width,pixels.height}},
                            {"ani_position",{pose.x,pose.y}},{"rate",{pose.scaleX,pose.scaleY}},{"rotation",pose.rotationRadians},
                            {"blend",pose.blend},{"rgba",pose.rgba},{"world_origin",{world.player.x,world.player.y,world.player.z}},
                            {"right_local",{right.x,right.y}},{"left_local",{left.x,left.y}}});
                        ++samples;
                    }
                }
                for(const auto &volume:world.attackVolumes)if(volume.skillId==116) {
                    sawVolume=true;
                    check(volume.sourceAttackFamily=="reviewed_nut_body_attack"&&volume.sourceAttack&&volume.sourceAttack->source.path==descriptor.attack.memberPath&&
                        volume.sourceModifiers&&volume.sourceModifiers->percent==float(*skillLevelValue(plan.skills.at({4,116}).data->values("[level info]"),level,0)),
                        "Actual World attack volume consumes exact source body ATK and level percent once");
                    if(firstVolume.is_null())firstVolume={{"box",{volume.box.x,volume.box.y,volume.box.z,volume.box.w,volume.box.h,volume.box.d}},
                        {"origin",{volume.x,volume.y,volume.z}},{"trace",volume.sourceModifiers->snapshot()}};
                }
                for(const auto &target:world.monsters)sawResponse|=target.animation=="damage1"||target.animation=="damage2"||target.animation=="down"||target.z>0;
                world.advanceSingleTick();
            }
            const auto hits=countEvents("hit","experimental_source_skill");size_t misses=0;for(const auto &event:world.events)if(event.kind=="miss")++misses;
            evidence.push_back({{"phase","world_cast"},{"clock",ani_clock::policyName(clock)},{"level",level},{"direction",direction},{"targets",targets},
                {"hits",hits},{"misses",misses},{"render_samples",renderSamples},{"first_volume",firstVolume},{"diagnostics",world.experimentalDiagnostics()}});
            check(sawMotion&&sawVolume&&allLayers&&seenLayers==expectedLayers&&realLayerPixels&&samples>0,"Real World renders all ten authorized source layers while actual body geometry executes");
            check(countEvents("sound","PR_HEDGEHOG")==1&&countEvents("camera_shake","reviewed_nut_body_flag")==1,"Source cast sound and flag2 camera feedback occur once per action");
            check(!targets?hits+misses==0:hits+misses==3,"One body action deduplicates contacts for three real Goblin hurt boxes, including held/repeated frames");
            check(!targets||sawResponse,"Source dark magical contact reaches actual monster response animation/lift");
            check(!runtime.attacking()&&world.player.skillAnimationLayers.empty()&&world.player.sourceSkillCameraFeedback.offsetX(world.nowMs())==0&&
                runtime.snapshotDiagnostics().at("source_nut_entities")==0,"ANI end clears body/layers/camera feedback with no fake persistent entity");
            check(world.skillState().snapshot(world.nowMs())==normal,"Test branch release leaves normal learning ledger unchanged");
        }
        // Source skill activation must also reject an explicit repeat after
        // body completion while the original source CD remains alive.
        floor();configure(1);press(true);world.advanceSingleTick();press(false);
        for(int tick=0;tick<110;++tick)world.advanceSingleTick();
        const auto cooldownMp=world.player.mp;const auto cooldownSounds=countEvents("sound","PR_HEDGEHOG");
        press(true);world.advanceSingleTick();press(false);
        check(!runtime.attacking()&&world.player.mp==cooldownMp&&countEvents("sound","PR_HEDGEHOG")==cooldownSounds,
            "A new post-animation slot press cannot bypass the active source cooldown");
        // Rate/stop are sampled through the actual render layer contract.
        // A plain value runtime fixture isolates this from hit responses.
        {
            auto shared=std::make_shared<ExperimentalCharacterPlan>(plan);ExperimentalCharacterRuntime isolated(shared);
            isolated.setAnimationClockPolicy(clock);isolated.configuration().configureBasicAttackTemplate({4,116},1,*shared);
            isolated.configuration().assignSlot(0,SkillKey{4,116},*shared);
            ExperimentalActorState actor;actor.alive=true;actor.x=600;actor.y=300;actor.mp=100000;actor.attackPerMille=1700;
            CharacterActionRequest request;request.inputKey=20;request.inputDown=true;request.action=CharacterAction::CommandInput;isolated.request(request);
            const auto first=isolated.advance(1,actor,[](double,double){return true;});actor=first.actor;
            check(first.skillAnimationLayers.size()==10&&first.animationClock.has_value(),"Actual accelerated body publishes all source attachments with one owner clock");
            const auto held=*first.animationClock;actor.hitStopped=true;
            const auto paused=isolated.advance(2,actor,[](double,double){return true;});
            check(paused.animationClock&&paused.animationClock->elapsedMs==held.elapsedMs&&paused.sourceCameraShakes.empty(),
                "Contact pause freezes the source body clock and cannot replay a held flag");
            for(const auto &layer:first.skillAnimationLayers) {
                check(layer.inheritBodyRate&&!layer.synchronizedToBody,"Source ALS child inherits body rate while preserving its own delay sequence");
                const auto child=assets.animation(layer.source.memberPath);
                const auto a=child->followClock(*child,held,layer.loop),b=child->followClock(*child,*paused.animationClock,layer.loop);
                check(a.frame==b.frame&&a.localMs==b.localMs&&a.ratePercent==held.ratePercent,
                    "Each real source layer preserves owner rate and exact frame/local time across hitstop");
            }
        }
        for(const auto *reason:{"cancel","scene","death"}) {
            floor();configure(1);press(true);world.advanceSingleTick();press(false);
            check(runtime.attacking()&&!world.player.skillAnimationLayers.empty(),"Exit fixture reaches actual source body and layer publication");
            if(std::string(reason)=="cancel")world.idle();else if(std::string(reason)=="scene")world.changeScene();
            else {world.player.dead=true;world.player.life=ActorLife::Dying;}
            for(int tick=0;tick<30;++tick)world.advanceSingleTick();
            check(world.player.skillAnimationLayers.empty()&&world.player.sourceSkillCameraFeedback.offsetX(world.nowMs())==0&&
                runtime.snapshotDiagnostics().at("source_nut_entities")==0,std::string("No layer, callback or camera feedback survives ")+reason);
        }
        floor();configure(1);world.player.z=100;const auto airMp=world.player.mp;press(true);world.advanceSingleTick();press(false);
        check(world.player.mp==airMp&&runtime.remainingCooldown({4,116},world.nowMs())==0&&!runtime.attacking(),"SKL airborne qualification rejects before MP/CD/action");
        floor();configure(1);world.player.mp=0;press(true);world.advanceSingleTick();press(false);
        check(!runtime.attacking()&&runtime.remainingCooldown({4,116},world.nowMs())==0,"Insufficient MP rejects before publishing layers, sound or cooldown");
        // All source dependencies must preflight on the private candidate.
        for(const bool badVisual:{true,false}) {
            auto badPlan=std::make_shared<ExperimentalCharacterPlan>(plan);auto &bad=badPlan->sourceSkillActions.at({4,116});
            if(badVisual)bad.bodyLayers[0].source.memberPath="missing/hedgehog-actual-layer.ani";
            else for(auto &field:bad.attackDefinition.source.fields)if(normalize(field.tag)=="[hit wav]")field.values=Json::array({42});
            ExperimentalCharacterRuntime injected(badPlan);injected.setAnimationClockPolicy(clock);injected.configuration().configureBasicAttackTemplate({4,116},1,*badPlan);
            injected.configuration().assignSlot(0,SkillKey{4,116},*badPlan);floor();
            const auto mp=world.player.mp;const auto rng=world.randomStreams().snapshot();auto ids=world.idSources().snapshot();ids.erase("requests");
            ExperimentalWorldAdapter adapter(world);CharacterActionRequest request;request.inputKey=20;request.inputDown=true;request.action=CharacterAction::CommandInput;
            injected.request(request);adapter.advance(injected,uint64_t(world.tick)+1);auto afterIds=world.idSources().snapshot();afterIds.erase("requests");
            check(world.player.mp==mp&&injected.remainingCooldown({4,116},world.nowMs())==0&&!injected.attacking()&&
                world.effects.empty()&&world.player.skillAnimationLayers.empty()&&world.randomStreams().snapshot()==rng&&afterIds==ids&&
                countEvents("sound","PR_HEDGEHOG")==0,"Faulted layer/ATK response preflight rolls back MP/CD/IDs/RNG/sounds/layers");
        }
        // Replay actual World input at several render pump schedules and
        // compare every completed fixed tick, including source layers/flags.
        const auto schedule=[&](int fps,bool budgeted) {
            Progression p(regions);World w(pvf,assets,WorldRules::BetaFoundationV1);w.enableExperimentalCharacters();
            CharacterStore c(std::filesystem::absolute("hedge-schedule-"+std::string(ani_clock::policyName(clock))+"-"+std::to_string(fps)));
            c.data["characters"][0]={{"name","ReplayHedge"},{"class","priest"},{"identity",CharacterIdentity{4,0,0}.json()},
                {"level",1},{"skill_initialization","source-v1"}};c.apply(0,w,p);dnf::enterExplicitSkillPreviewFixture(w);w.configureAnimationClock(clock);
            auto &r=*w.experimentalRuntime();r.configuration().configureBasicAttackTemplate({4,116},1,r.plan());r.configuration().assignSlot(0,SkillKey{4,116},r.plan());
            w.monsters.clear();w.events.clear();w.combat=true;w.freezeAi=true;w.mapWidth=3000;w.walkRects={{0,185,3000,600}};
            w.player.x=w.player.px=600;w.player.y=w.player.py=300;w.player.z=w.player.pz=0;w.player.mp=10000;
            w.randomStreams()=RandomStreams(0x1031);
            for(int n=0;n<3;++n){Actor target;target.id=n+1;target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
                target.x=target.px=600+hitBox->x+hitBox->w*.5;target.y=target.py=300+hitBox->y+hitBox->h*.5;
                w.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
                target.hp=target.maxHp=100000000;w.monsters.push_back(std::move(target));}
            w.synchronizeEntityHandles();w.enqueue({0,20,true});w.enqueue({16666667,20,false});
            Json frames=Json::array();w.setObjectTick([&](World &current){Json targets=Json::array(),layers=Json::array();
                for(const auto &target:current.monsters)targets.push_back({{"hp",target.hp},{"position",{target.x,target.y,target.z}},
                    {"velocity",{target.vx,target.vy,target.vz}},{"animation",target.animationPath},{"life",int(target.life)}});
                for(const auto &layer:current.player.skillAnimationLayers)layers.push_back(layer.snapshot());
                auto ids=current.idSources().snapshot();ids.erase("requests");frames.push_back({{"tick",current.tick},{"mp",current.player.mp},
                    {"runtime",r.snapshotDiagnostics()},{"cd",r.cooldownSnapshot(current.nowMs())},{"targets",targets},{"layers",layers},
                    {"camera_offset",current.player.sourceSkillCameraFeedback.offsetX(current.nowMs())},
                    {"events",current.eventLog()},{"rng",current.randomStreams().snapshot()},{"ids",ids}});});
            constexpr int64_t total=2000000000;int64_t previous=0;
            if(budgeted){w.advance(total,8);while(w.pendingTicks())w.advance(0,8);}
            else for(int frame=1;frame<=fps*2;++frame){const auto now=total*frame/(fps*2);w.advance(now-previous);previous=now;}
            check(w.tick==120&&w.pendingTicks()==0,"Render schedule completes all source skill ticks without dropping backlog");return frames;
        };
        const auto reference=schedule(60,false);
        for(const int fps:{30,144})check(schedule(fps,false)==reference,"Body/layers/contacts/MP/CD/RNG/flags are tick-identical at render FPS "+std::to_string(fps));
        check(schedule(1,true)==reference,"Eight-tick catchup budget preserves all source body skill results");
        evidence.push_back({{"phase","render_schedule_determinism"},{"clock",ani_clock::policyName(clock)},{"ticks",reference.size()},
            {"schedules",{30,60,144,"2s-budget8"}}});
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"scope","Priest4 skill116 reviewed NUT body action; inferred none-effect render strategy"},{"full_skill_complete",false},{"native_dynamic_parity",false}};
    }catch(const std::exception &error){writeJson("hedgehog-exception.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence}});throw;}
}
}
