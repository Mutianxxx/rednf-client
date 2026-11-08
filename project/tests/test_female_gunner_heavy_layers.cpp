#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/female_gunner_entities.hpp"
#include "dnf/female_gunner_world.hpp"
#include "dnf/storage.hpp"
#include "female_gunner_test_weapon.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
Json runFemaleGunnerHeavyLayersTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool okay,const std::string &message) {
        checks.push_back({{"passed",okay},{"message",message}});
        if(!okay){writeJson("heavy-layers-failed.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}
    };
    CharacterCatalog characters(pvf);RegionCatalog regions(pvf,assets);
    for(const auto policy:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("fixture-heavy-"+std::string(ani_clock::policyName(policy))));
        store.data["characters"][0]={{"name","HeavySourceRuntime"},{"class","atgunner"},{"identity",CharacterIdentity{5,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(policy);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        const auto normal=world.skillState().snapshot(world.nowMs());
        const auto configure=[&](int id) {
            world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
            world.combat=true;world.freezeAi=true;world.freeCd=true;world.mapWidth=2400;world.walkRects={{0,185,2400,500}};
            world.player.x=world.player.px=500;world.player.y=world.player.py=300;world.player.z=world.player.pz=0;
            world.player.dead=false;world.player.life=ActorLife::Alive;world.player.recovery=0;world.player.stunUntil=0;
            world.player.hp=world.player.maxHp;world.player.hitStopTicks=0;world.player.hitStopped=false;world.player.mp=INT32_MAX;
            runtime.configuration()=ExperimentalSkillConfiguration(plan);runtime.configuration().configureFemaleGunnerSourceSkill({5,id},1,plan);
            runtime.configuration().assignSlot(0,SkillKey{5,id},plan);
        };
        configure(71);world.enqueue({world.simulationNanoseconds(),20,true});
        std::map<std::string,std::set<uint64_t>> receipts;std::set<std::string> seenStage;
        bool started=false,finished=false,independent=false,pauseChecked=false,nonDamaging=true,sourceLoops=true;
        for(int tick=0;tick<600;++tick) {
            world.advanceSingleTick();started|=runtime.attacking();
            for(const auto &fx:world.effects)if(fx.animation.find("character/gunner/effect/animation/extruder/")==0) {
                const auto role=fx.projectileSource.value("role",std::string());
                if(role.rfind("x1_stage_visual_",0)!=0)continue;
                receipts[role].insert(fx.projectileSource.at("action").get<uint64_t>());
                seenStage.insert(fx.animation);
                nonDamaging&=!fx.damageEnabled&&!fx.attackInstance;
                const auto ani=assets.animation(fx.animation);
                sourceLoops&=fx.loop==ani->globals.value("0",false)&&fx.attached;
                if(role=="x1_stage_visual_bodyready1"&&fx.animationClock&&world.player.animationClock&&
                   fx.animationClock->frame>=2&&world.player.animationClock->frame==0)independent=true;
            }
            if(!pauseChecked&&tick>6&&world.player.animationPath.find("extruderready.ani")!=std::string::npos) {
                const auto current=std::find_if(world.effects.begin(),world.effects.end(),[](const auto &fx){return fx.projectileSource.value("role",std::string())=="x1_stage_visual_bodyready1";});
                if(current!=world.effects.end()&&current->animationClock) {
                    const auto id=current->id;const auto age=current->animationClock->elapsedMs;world.player.hitStopTicks=4;
                    world.advanceSingleTick();world.advanceSingleTick();
                    const auto paused=std::find_if(world.effects.begin(),world.effects.end(),[&](const auto &fx){return fx.id==id;});
                    check(paused!=world.effects.end()&&paused->animationClock&&paused->animationClock->elapsedMs==age,
                        "Actual X1 independent source animation pauses with its owning actor hitstop without cursor synchronization");pauseChecked=true;
                }
            }
            if(started&&!runtime.attacking()){finished=true;break;}
        }
        check(started&&finished&&pauseChecked&&independent,"Actual X1 input traverses Ready, Charge and Shoot with independent source timelines in both clock policies");
        check(nonDamaging,"Actual X1 appearance publishes no independent damage or contact instance");
        check(sourceLoops,"Actual X1 appearance keeps the authored loop and body-stage ownership for every sampled tick");
        for(const auto *role:{"bodyready1","bodyready2","bodycharge","bodyshoot1","bodyshoot2"})
            check(receipts[std::string("x1_stage_visual_")+role].size()==1,"Each X1 machine track is spawned once by its real phase entry: "+std::string(role));
        check(std::none_of(world.effects.begin(),world.effects.end(),[](const auto &fx){return fx.projectileSource.value("role",std::string()).rfind("x1_stage_visual_",0)==0&&fx.expires>0;}),
            "Completed X1 stage ownership retires every attached machine/light track");
        check(world.skillState().snapshot(world.nowMs())==normal,"X1 stage visuals do not alter the normal learning ledger");
        evidence.push_back({{"clock",ani_clock::policyName(policy)},{"x1_seen_visuals",seenStage},{"one_spawn_action_receipts",receipts}});
        // Actual interruption after the shot preserves a detached projectile,
        // while removing only the interrupted body-stage appearance.
        configure(71);world.enqueue({world.simulationNanoseconds(),20,true});bool shot=false;
        for(int tick=0;tick<500&&!shot;++tick){world.advanceSingleTick();for(const auto &fx:world.effects)
            shot|=fx.projectileSource.value("role",std::string())=="x1_stage_visual_bodyshoot1";}
        check(shot,"Interruption fixture reaches the actual X1 Shoot stage");
        world.player.recovery=20;world.advanceSingleTick();
        bool attachedLeft=false,detachedLeft=false;
        for(const auto &fx:world.effects){attachedLeft|=fx.projectileSource.value("role",std::string()).rfind("x1_stage_visual_",0)==0;
            detachedLeft|=fx.projectileSource.value("role",std::string())=="charged_pull_ball";}
        check(!attachedLeft&&detachedLeft,"Actual hit interruption removes X1 body-stage visuals and preserves the launched independent ball");
        configure(71);world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        world.player.dead=true;world.player.life=ActorLife::Dying;world.advanceSingleTick();
        check(world.femaleGunnerDiagnostics().at("entities").empty(),"Actual owner death removes X1 visual entities and future emissions");
        world.changeScene();check(world.effects.empty()&&world.femaleGunnerDiagnostics().at("entities").empty(),"Scene reset leaves no X1 stage effects or pending entities");

        // Real request gating is checked before cost/action publication with
        // every other source subtype, then through an actually equipped EQU.
        const auto shared=std::make_shared<ExperimentalCharacterPlan>(plan);
        for(const int subtype:{-1,0,1,2,4}) {
            ExperimentalCharacterRuntime gate(shared);gate.setAnimationClockPolicy(policy);
            gate.configuration().configureFemaleGunnerSourceSkill({5,73},1,plan);
            CharacterActionRequest request;request.action=CharacterAction::Skill;request.skill=SkillKey{5,73};request.inputDown=true;gate.request(request);
            ExperimentalActorState actor;actor.x=500;actor.y=300;actor.mp=1000000;actor.weaponSubtype=subtype;
            const auto rejected=gate.advance(1,actor,[](double,double){return true;});bool requirement=false;
            for(const auto &diagnostic:rejected.diagnostics)requirement|=diagnostic.value("code",std::string())=="female_gunner_requires_handcannon";
            evidence.push_back({{"weapon_negative_subtype",subtype},{"diagnostics",rejected.diagnostics},{"mp_before",actor.mp},
                {"mp_after",rejected.actor.mp},{"remaining_cd",gate.remainingCooldown({5,73},17)},{"attacking",gate.attacking()}});
            check(requirement&&!gate.attacking()&&rejected.actor.mp==actor.mp&&gate.remainingCooldown({5,73},17)==0&&rejected.femaleGunnerCommands.empty(),
                "Real CannonBall request rejects non-handcannon subtype before MP/CD/action or visual publication: "+std::to_string(subtype));
        }
        configure(73);const auto nonHandcannonMp=world.player.mp;world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        const auto rejectedWorldDiagnostics=world.experimentalDiagnostics();
        bool worldRequirement=false;for(const auto &diagnostic:rejectedWorldDiagnostics.at("world"))
            worldRequirement|=diagnostic.value("code",std::string())=="female_gunner_requires_handcannon";
        evidence.push_back({{"world_weapon_negative_diagnostics",world.experimentalDiagnostics()},{"service",world.femaleGunnerDiagnostics()},
            {"mp_before",nonHandcannonMp},{"mp_after",world.player.mp},{"hp",world.player.hp},{"dead",world.player.dead},
            {"life",int(world.player.life)},{"attacking",runtime.attacking()},{"remaining_cd",runtime.remainingCooldown({5,73},world.nowMs())}});
        check(worldRequirement&&!runtime.attacking()&&world.player.mp==nonHandcannonMp&&runtime.remainingCooldown({5,73},world.nowMs())==0&&
            world.femaleGunnerDiagnostics().at("entities").empty(),"Actual World non-handcannon release is rejected with a visible reason and no MP/CD/entity publication");
        int handcannon=-1;
        for(const auto &field:characters.at(5).settings.script.fields)if(field.tag=="[key value index]"&&!field.values.empty()&&
            (field.values[0]=="weaponSubTypeIndex"||field.values[0]=="defaultWeaponBySubType"))
            for(size_t at=2;at+1<field.values.size();at+=2)if(field.values[at]==3)handcannon=field.values[at+1].get<int>();
        const auto *weapon=progression.item(handcannon);check(weapon&&weapon->source.number("[sub type]",-1)==3,"Current female settings table resolves a real source handcannon EQU");
        const auto handcannonPath=weapon->path;
        configure(73);FemaleGunnerHandcannonTestFixture equippedWeapon(world,progression,plan.characterDefinition);
        check(progression.equippedIndex("[weapon]")>=0,"Real equipment-change transaction equips the source handcannon at its required source level");
        world.player.mp=INT32_MAX;world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        check(runtime.attacking(),"Actual World CannonBall request accepts the equipped source handcannon");
        Json weaponEvidence=Json::array();size_t visibleLayers=0;
        for(const auto &stage:plan.femaleGunnerSkills.at({5,73}).stages) {
            const auto *motion=plan.motion(stage.motionTag,stage.motionSlot);const auto *body=appearanceBodyMotion(world.characterAppearance(),motion->source.memberPath);
            check(body!=nullptr,"CannonBall actual CHR stage is bound in the equipped appearance");
            for(const auto &layer:world.characterAppearance().orderedLayers())if(layer.slot=="[weapon]") {
                const auto path=appearanceLayerMotion(layer,*body);if(path.empty())continue;const auto ani=assets.animation(path);bool visible=false;
                for(const auto &frame:ani->frames)if(!frame.image.empty()) {
                    const auto image=assets.pixels(appearanceImage(frame.image,layer.variation),frame.imageFrame);
                    for(size_t pixel=0;pixel+3<image.rgba.size();pixel+=4)if(image.rgba[pixel+3]&&(image.rgba[pixel]||image.rgba[pixel+1]||image.rgba[pixel+2])){visible=true;break;}
                    if(visible)break;
                }
                visibleLayers+=visible;weaponEvidence.push_back({{"body",motion->source.json()},{"equipment",layer.sourcePath},
                    {"lay",layer.animationScript},{"weapon_animation",makeSourceRef(pvf,path).json()},{"visible_source_pixels",visible}});
            }
        }
        bool aImageMissing=false;std::string aImageError;
        try{(void)assets.pixels("character/gunner/atequipment/weapon/hcan/gg_hcan0000a.img",36);}
        catch(const std::exception &error){aImageMissing=true;aImageError=error.what();}
        evidence.push_back({{"clock",ani_clock::policyName(policy)},{"handcannon_equipment",handcannonPath},{"equipment_fixture",equippedWeapon.source()},
            {"equipment_layer_chain",weaponEvidence},{"visible_weapon_layers",visibleLayers},
            {"visual_source_gap",{{"status","unresolved"},{"source_bc_frames_transparent",visibleLayers==0},
                {"unregistered_a_img_missing",aImageMissing},{"missing_image_error",aImageError},
                {"visibility_acceptance","not passed; no substitute weapon added"}}}});
        check(weaponEvidence.size()==4,"Both actual CannonBall CHR stages resolve the real source EQU/LAY b/c ANI and IMG consumers");
        check(visibleLayers==0&&aImageMissing,
            "Current default handcannon has transparent source b/c skill frames and no loadable a IMG; visible weapon remains an explicitly unresolved source gap");
        world.changeScene();check(equippedWeapon.restore(),"CannonBall source equipment fixture restores the prior progression and appearance");

        configure(97);world.enqueue({world.simulationNanoseconds(),20,true});bool particle=false;
        std::set<std::string> particleRoles,activeParticleRoles;bool fullInputDiagnostic=false,particleVisualOnly=true,particleLoops=true,bodyFinalPose=false;
        for(int tick=0;tick<700;++tick) {
            world.advanceSingleTick();const auto diagnostic=world.femaleGunnerDiagnostics();
            for(const auto &entity:diagnostic.at("entities"))particleRoles.insert(entity.at("command").at("role").get<std::string>());
            for(const auto &fx:world.effects)if(fx.born<=world.nowMs()&&fx.expires>world.nowMs()&&fx.animationClock&&
                fx.phase=="female-gunner:awakening_particle_cannon") {
                const auto role=fx.projectileSource.value("role",std::string());activeParticleRoles.insert(role);
                particleVisualOnly&=!fx.damageEnabled&&!fx.attackInstance;
                const auto clip=assets.animation(fx.animation);particleLoops&=fx.loop==clip->globals.value("0",false);
                if(role=="cannon_appear"&&fx.animationClock->elapsedMs>clip->duration&&fx.animationClock->frame==clip->frames.size()-1)
                    bodyFinalPose=true;
            }
            const auto experimentalDiagnostics=world.experimentalDiagnostics();
            for(const auto &entry:experimentalDiagnostics.at("world"))fullInputDiagnostic|=entry.value("code",std::string())=="female_gunner_particle_charge_input_unverified";
            particle|=particleRoles.count("cannon_sub_body")>0;
            if(particle&&!runtime.attacking()&&diagnostic.at("entities").empty())break;
        }
        check(particle&&particleRoles.count("cannon_gauge_ready")&&particleRoles.count("cannon_gauge_shot")&&particleRoles.count("cannon_main_disappear"),
            "Actual World particle skill publishes SubBody, GaugeReady/Shot, normal main layers and scheduled source disappearance");
        check(activeParticleRoles.count("cannon_sub_body")&&activeParticleRoles.count("cannon_gauge_ready")&&
            activeParticleRoles.count("cannon_gauge_shot")&&activeParticleRoles.count("cannon_main_disappear"),
            "Particle SubBody, Gauge and main disappearance reach live source clocks after their real scheduled births");
        check(particleVisualOnly&&particleLoops&&bodyFinalPose,
            "Particle appearance remains visual-only with authored loops and holds its independent completed main-machine pose");
        check(fullInputDiagnostic,"Actual particle input exposes the unimplemented rapid-ATTACK full-charge contract in diagnostics");
        auto full=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,97}),*plan.skills.at({5,97}).data,1,3);
        full.actionSequence=7000;full.rawTables["particle_full_charge"]=true;
        const auto fullParts=expandFemaleGunnerEntities(pvf,assets,{full});size_t fullAttackCount=0,fullVisualCount=0;
        for(const auto &part:fullParts)if(part.effectRole=="cannon_main") {
            ++fullAttackCount;check(part.animationSource->memberPath.find("fulllasertile1.ani")!=std::string::npos&&
                part.attackSource->memberPath.find("ancienttriggerfull.atk")!=std::string::npos,
                "Explicit full candidate selects the owning FullLaser ANI and Full ATK rather than normal source assets");
        }else if(part.effectRole=="cannon_full_visual") {++fullVisualCount;check(!part.attackSource&&part.kind==FemaleGunnerCommandKind::Stage,"Full candidate visual layers cannot create extra damage");}
        check(fullAttackCount==1&&fullVisualCount>5,"Full candidate source branch has one main attack consumer and multiple independent visual layers");
        evidence.push_back({{"clock",ani_clock::policyName(policy)},{"particle_prepared_roles",particleRoles},{"particle_live_roles",activeParticleRoles},
            {"full_candidate_parts",fullParts.size()},{"full_input_limit","not reachable through current rapid ATTACK input; no native threshold claimed"}});
        world.changeScene();check(world.femaleGunnerDiagnostics().at("entities").empty(),"Particle scene cancellation removes all normal/full pending visual and attack entities");
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"all_skill_visuals_complete",false},{"cannonball_weapon_visibility","unresolved source gap; not passed"},
        {"classification","actual-runtime-world-stage-and-equipment-consumers; full-charge-assets-only candidate"},
        {"original_dynamic_comparison","pending_user"}};
}
}
