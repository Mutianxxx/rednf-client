#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/female_gunner_entities.hpp"
#include "dnf/session.hpp"
#include "dnf/storage.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
void effectsWorldFloor(World &world) {
    world.combat=true;world.freezeAi=true;world.freeCd=true;world.mapWidth=2400;world.walkRects={{0,185,2400,500}};
    world.player.x=world.player.px=500;world.player.y=world.player.py=300;world.player.dir=1;
    world.player.mp=INT32_MAX;world.player.stunUntil=0;world.player.recovery=0;
}
void effectsWorldMonster(World &world,int id,double x,int hp=1000000) {
    Actor actor;actor.id=id;actor.sourceId=10;actor.monsterPath="monster/goblin/goblin.mob";
    actor.x=actor.px=x;actor.y=actor.py=300;actor.dir=-1;
    world.initializeMonsterAttributes(actor,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    actor.hp=actor.maxHp=hp;world.monsters.push_back(std::move(actor));world.synchronizeEntityHandles();
}
void effectsWorldConfigure(World &world,int skill) {
    auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();const SkillKey key{5,skill};
    runtime.configuration()=ExperimentalSkillConfiguration(plan);
    runtime.configuration().configureFemaleGunnerSourceSkill(key,1,plan);runtime.configuration().assignSlot(0,key,plan);
}
// Explicit setup for the lifecycle/restoration half of this test. Source SKL
// and original ATK are parsed normally; only the status probability seed and
// attacker scalar snapshot are local diagnostic inputs. This does not claim
// a normal-input source-controller invocation or original numerical parity.
Json effectsWorldInject(World &world,Pvf &pvf,Actor &target,int skillId) {
    CharacterCatalog catalog(pvf);const auto skill=readSkillAttackStatuses(readSkillSourceData(catalog.skillDefinition({5,skillId})),1);
    const auto attack=readAttackStatuses(pvf.script("character/gunner/atattackinfo/fastknee.atk"));
    const auto watermark=world.simulationCheckpoint().at("status_instance_ids");
    const auto attackId=world.idSources().attacks.next();
    for(uint64_t seed=0;seed<256;++seed) {
        StatusHost host(pvf.identity(),StunStatusPolicy::inferredFlatChanceStunV1());host.mergeInstanceWatermark(watermark);Pcg32 random(seed,37);
        StatusRequest q;q.attacker=world.player.handle;q.attackerLevel=20;q.target.handle=target.handle;
        q.target.resistance=makeMonsterStatusResistances(*target.combatAttributes);q.attackInstance=attackId;q.attack=attack;q.skill=skill;
        q.independentAttack=100;q.independentRate=1;
        auto prepared=host.prepare(q,uint64_t(world.nowMs()),random);
        if(!prepared.ready()) throw std::runtime_error("Extended World status setup rejected: "+prepared.receipt.dump());
        host.publish(std::move(prepared),random);auto bundle=host.snapshotTarget(target.handle,uint64_t(world.nowMs()),31,true);
        if(bundle.at("effects").empty()) continue;
        bundle["diagnostic_setup"]={{"source_skill",SkillKey{5,skillId}.json()},{"local_probability_seed",seed},
            {"normal_input",false},{"local_random",random.snapshot()}};
        world.restoreStatusCheckpoint(bundle,target.handle,target.handle,31);return bundle;
    }
    throw std::runtime_error("Extended World source status did not proc in bounded diagnostic seed search");
}
} // namespace
Json runStatusEffectsWorldTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();const auto check=[&](bool value,const char *message) {
        if(!value) throw std::runtime_error(std::string("Extended status World: ")+message);checks.push_back(message);
    };
    RegionCatalog regions(pvf,assets);Progression progression(regions);
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
    CharacterStore store(std::filesystem::absolute("cache/status-effects-world-fixtures"));
    store.data["characters"][0]={{"name","StatusEffectsWorldRegression"},{"class","atgunner"},
        {"identity",CharacterIdentity{5,0,0}.json()},{"level",1},{"skill_initialization","source-v1"}};
    store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(ani_clock::ClockPolicy::SourceDelay100);effectsWorldFloor(world);
    effectsWorldConfigure(world,107);world.enqueue({world.simulationNanoseconds(),20,true});
    const auto emptyRandom=world.randomStreams().snapshot();bool started=false,ended=false;
    for(int step=0;step<1800;++step) {
        world.advance(16666667);started|=world.experimentalRuntime()->attacking();
        if(started && !world.experimentalRuntime()->attacking()){ended=true;break;}
    }
    check(started && ended && world.randomStreams().snapshot()==emptyRandom,
        "Actual source ice-thrower empty release starts and finishes without allocating status RNG or effects to nonexistent targets");
    world.changeScene();world.monsters.clear();world.events.clear();effectsWorldFloor(world);effectsWorldConfigure(world,107);
    // Place the multi-target fixture inside this skill's actual muzzle-local
    // source volume. Coordinates from before the weapon-origin repair put
    // three of the four actors behind the muzzle and could only contact one.
    const auto &plan=world.experimentalRuntime()->plan();
    const auto command=evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at({5,107}),*plan.skills.at({5,107}).data,1,0);
    const auto phases=expandFemaleGunnerEntities(pvf,assets,{command});
    std::optional<std::pair<FemaleGunnerSkillCommand,Box>> contact;
    for(const auto &phase:phases)if(phase.attackSource&&phase.animationSource)
        for(const auto &frame:assets.animation(phase.animationSource->memberPath)->frames)
            for(const auto &box:frame.boxes)if(box.type==15&&box.w>0){contact=std::make_pair(phase,box);break;}
    check(contact.has_value(),"Ice-thrower multi-target fixture uses an authored attacking ANI volume");
    const auto &volume=contact->second;const auto muzzle=contact->first.offsetX;
    for(int i=0;i<4;++i) effectsWorldMonster(world,i+1,world.player.x+muzzle+volume.x+volume.w*(i+1)/5.0);
    effectsWorldMonster(world,5,world.player.x-200);
    world.enqueue({world.simulationNanoseconds(),20,true});std::set<EntityHandle> frozen;
    for(int step=0;step<900;++step) {
        world.advance(16666667);
        for(const auto &actor:world.monsters) for(const auto &effect:world.statusEffects(actor.handle))
            if(effect.at("kind")=="freeze") frozen.insert(actor.handle);
        if(frozen.size()>=2) break;
    }
    check(frozen.size()>=2,"Actual source ice-thrower geometry/ATK/SKL sidecar applies independent freeze instances to multiple contacted World targets");
    check(world.monsters.back().hp==world.monsters.back().maxHp&&world.statusEffects(world.monsters.back().handle).empty(),
        "Ice-thrower does not apply damage or freeze behind its actual forward source volume");
    samples["normal_input_multitarget_freeze"]={{"targets",frozen.size()},{"world",world.snapshot()},
        {"diagnostics",world.femaleGunnerDiagnostics()},{"normal_random",world.randomStreams().snapshot()}};
    world.changeScene();world.monsters.clear();world.events.clear();effectsWorldFloor(world);
    effectsWorldMonster(world,1,640);effectsWorldMonster(world,2,700);
    const auto normalRandom=world.randomStreams().snapshot();
    const auto burn=effectsWorldInject(world,pvf,world.monsters[0],108);
    const auto bleeding=effectsWorldInject(world,pvf,world.monsters[1],9);
    check(world.randomStreams().snapshot()==normalRandom && burn.at("effects")[0].at("kind")=="burn" &&
          bleeding.at("effects")[0].at("kind")=="bleeding",
        "Explicit real-source burn/bleeding diagnostic bundles enter actual World consumers without altering normal combat RNG");
    const auto burnHandle=world.monsters[0].handle,bleedHandle=world.monsters[1].handle;
    const auto firstHp=world.monsters[0].hp,secondHp=world.monsters[1].hp;
    world.advance(500000000);
    check(world.monsters[0].hp==firstHp && world.monsters[1].hp==secondHp,
        "World does not apply periodic burn/bleeding before the frozen next deadline");
    const auto simulation=world.simulationCheckpoint();Json savedActors=Json::array();
    for(const auto &actor:world.monsters) {
        auto saved=saveActor(actor,world.nowMs());saved["status_state"]=world.statusCheckpoint(actor.handle,31);savedActors.push_back(saved);
    }
    std::vector<Actor> actors;for(const auto &saved:savedActors) {
        auto actor=loadActor(saved,world.nowMs());world.restoreMonsterAttributes(actor);actors.push_back(std::move(actor));
    }
    World resumed(pvf,assets,WorldRules::BetaFoundationV1);resumed.enableExperimentalCharacters();store.apply(0,resumed,progression);
    effectsWorldFloor(resumed);resumed.restoreSimulationCheckpoint(simulation);resumed.restoreRoomActors(std::move(actors),savedActors);
    check(resumed.monsters[0].handle!=burnHandle && resumed.monsters[1].handle!=bleedHandle &&
          !resumed.resolveActor(burnHandle) && !resumed.resolveActor(bleedHandle) && resumed.randomStreams().snapshot()==normalRandom,
        "Same-generation World/room restore creates new target incarnations and restores pending status deadlines without rerolling");
    const auto rngBeforeTick=resumed.randomStreams().snapshot();resumed.advance(500000000);world.advance(500000000);
    check(resumed.monsters[0].hp==world.monsters[0].hp && resumed.monsters[1].hp==world.monsters[1].hp &&
          resumed.monsters[0].hp<firstHp && resumed.monsters[1].hp<secondHp && resumed.randomStreams().snapshot()==rngBeforeTick,
        "Restored and uninterrupted World commit the same two target periodic HP amounts at the next deadline without RNG draws");
    int damageEvents=0;for(const auto &event:resumed.events)if(event.kind=="status_damage")++damageEvents;
    resumed.advance(0);int unchangedEvents=0;for(const auto &event:resumed.events)if(event.kind=="status_damage")++unchangedEvents;
    check(unchangedEvents==damageEvents,"Zero new simulation ticks cannot duplicate a committed periodic damage receipt");
    resumed.monsters[0].hp=1;resumed.advance(1000000000);
    check(resumed.monsters[0].dead && resumed.monsters[0].hp==0 && resumed.statusEffects(resumed.monsters[0].handle).empty(),
        "Lethal periodic World damage enters normal death lifecycle and clears all victim status effects");
    const auto retired=resumed.monsters[1].handle;resumed.monsters.clear();resumed.synchronizeEntityHandles();
    effectsWorldMonster(resumed,2,700);
    check(resumed.monsters[0].handle!=retired && resumed.statusEffects(resumed.monsters[0].handle).empty() &&
          !resumed.resolveActor(retired),"Retired target handles cannot transfer periodic damage to a replacement actor with the same legacy numeric ID");
    samples["diagnostic_burn"]=burn;samples["diagnostic_bleeding"]=bleeding;
    samples["restored_world"]=resumed.snapshot();
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","actual normal-input source freeze plus explicitly identified source status injection for World periodic/restore/death lifecycle"}};
}
} // namespace dnf
