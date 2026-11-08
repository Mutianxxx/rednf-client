#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/session.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
constexpr int64_t damageStepNs=16666667;
void damageFloor(World &world,bool freezeAi=true) {
    world.combat=true; world.freezeAi=freezeAi;
    world.mapWidth=1200; world.walkRects={{0,240,1200,240}};
    world.player.x=world.player.px=560; world.player.y=world.player.py=344;
    world.player.dir=1;
}
void damageGoblin(World &world,double distance=80,
                  const std::string &hpPolicy="inferred-mob-table-hp-v1",
                  const std::string &combatPolicy="inferred-mob-combat-table-v1") {
    Actor actor; actor.id=1; actor.monsterPath="monster/goblin/goblin.mob";
    actor.x=actor.px=world.player.x+distance;
    actor.y=actor.py=world.player.y; actor.dir=-1;
    world.initializeMonsterAttributes(actor,1,hpPolicy,combatPolicy);
    world.monsters.push_back(std::move(actor));
}
void damageThrower(World &world,double distance=150) {
    Actor actor;actor.id=1;actor.monsterPath="monster/goblin/goblinthrower.mob";
    actor.x=actor.px=world.player.x+distance;actor.y=actor.py=world.player.y;actor.dir=-1;
    world.initializeMonsterAttributes(actor,2,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    world.monsters.push_back(std::move(actor));
}
const Effect *damageAwaitProjectile(World &world) {
    for(int i=0;i<120;++i) {
        world.advance(damageStepNs);
        for(const auto &effect:world.effects) if(effect.hostile && effect.hostileStats) return &effect;
    }
    return nullptr;
}
bool damageDiagnostic(const MonsterProjectileDefinition &definition,const std::string &kind) {
    return std::any_of(definition.diagnostics.begin(),definition.diagnostics.end(),[&](const Json &item){
        return item.value("kind",std::string())==kind;
    });
}
int damageOwn(Progression &progression,int id) {
    const auto *item=progression.item(id);
    if(!item) throw std::runtime_error("Damage World: missing source equipment fixture");
    const int index=int(progression.state.at("inventory").size());
    const int uid=progression.state.at("next_uid").get<int>();
    progression.state["inventory"].push_back({{"uid",uid},{"id",id},{"count",1},{"durability",item->durability}});
    progression.state["next_uid"]=uid+1;
    return index;
}
int damageEvents(const World &world,const std::string &kind) {
    return int(std::count_if(world.events.begin(),world.events.end(),[&](const Event &e){return e.kind==kind;}));
}
bool damageAwait(World &world,const std::string &kind,int ticks=240) {
    const int before=damageEvents(world,kind);
    for(int i=0;i<ticks;++i) {
        world.advance(damageStepNs);
        if(damageEvents(world,kind)>before) return true;
    }
    return false;
}
const Json &damageStage(const Json &receipt,const std::string &name) {
    for(const auto &stage:receipt.at("trace")) if(stage.value("stage",std::string())==name) return stage;
    throw std::runtime_error("Damage World: missing live damage stage "+name);
}
Json damageWorldState(const World &world) {
    Json actors=Json::array();
    for(const auto &actor:world.monsters) actors.push_back(saveActor(actor,world.nowMs()));
    return {{"world",world.snapshot()},{"simulation",world.simulationCheckpoint()},
        {"stats",world.statReport()},{"events",world.eventLog()},{"inputs",world.inputs()},
        {"player",saveActor(world.player,world.nowMs())},{"monsters",actors},
        {"skills",world.skillState().snapshot(world.nowMs())}};
}
} // namespace

Json runDamageWorldTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Damage World: ")+message);
        checks.push_back(message);
    };
    RegionCatalog catalog(pvf,assets);
    {
        Progression progression(catalog);
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        world.applyEquipment(progression); damageFloor(world); damageGoblin(world);
        const int before=world.monsters.front().hp;
        check(before==35 && world.monsters.front().combatAttributes.has_value(),
              "A newly initialized source goblin publishes its actual 35 HP and frozen combat inputs");
        world.normalAttack();
        check(damageAwait(world,"hit"),"Ordinary attack reaches a real source animation-box contact without diagnostic damage");
        const auto receipt=world.statReport().at("last_damage");
        check(receipt.at("usable")==true && receipt.at("policy")=="inferred-pve-damage-v1" &&
              receipt.at("sources").at("attack").at("source").at("path")=="character/swordman/attackinfo/attack1.atk" &&
              world.monsters.front().hp==std::max(0,before-receipt.at("hp_damage").get<int>()),
              "Accepted ordinary contact writes exactly the source damage receipt into monster HP");
        const auto pipeline=world.statReport().at("combat_pipeline");
        check(pipeline.at("policy")=="40jp-structural-adapter-v2" && pipeline.at("outcome")=="accepted" &&
              pipeline.at("accepted_damage")==std::min(before,receipt.at("hp_damage").get<int>()) &&
              pipeline.at("order")==Json::array({"qualification","response_selection","acceptance_preflight","damage",
                  "status_transaction","hp_commit","death_transition","hit_stop","reaction","status","hit_feedback","notification"}),
              "Live World damage journal records the actual 1031 qualification, source transaction, HP, hitstop, reaction and feedback order");
        check(receipt.at("sources").at("attacker").at("physical_attack")==5 &&
              receipt.at("sources").at("attacker").at("magical_attack")==5 &&
              receipt.at("sources").at("target").at("physical_attack")==9 &&
              damageStage(receipt,"target_defense").at("defense")==37,
              "Live damage separates starter EQU five/five, goblin equipment attack nine and source-converted defense37");
        world.advance(1000000000);
        check(damageEvents(world,"hit")==1,"Repeated body and weapon box samples register only one hit for the ordinary swing");
        samples["ordinary_attack"]=receipt;
    }
    {
        Progression progression(catalog); progression.initialize(5);
        World world(pvf,assets,WorldRules::BetaFoundationV1); world.applyEquipment(progression);
        const int katana=damageOwn(progression,27600);
        check(world.changeEquipment(progression,katana).ok,"Source katana27600 equips through the actual owned-item World transaction");
        damageFloor(world); damageGoblin(world);
        const auto skill=std::find_if(world.skills.begin(),world.skills.end(),[](const Skill &s){return s.id==5;});
        check(skill!=world.skills.end(),"The existing Swordman magical attack controller is registered");
        const int before=world.monsters.front().hp;
        world.activate(int(skill-world.skills.begin()));
        check(damageAwait(world,"hit"),"The magical controller reaches its actual contact and HP consumer");
        const auto receipt=world.statReport().at("last_damage");
        const auto &attacker=receipt.at("sources").at("attacker");
        const auto &stage=damageStage(receipt,"attack_and_skill");
        check(receipt.at("usable")==true && attacker.at("physical_attack")==22 && attacker.at("magical_attack")==24 &&
              stage.at("type")=="magical" && stage.at("weapon_base").get<float>()==
                  24.0f*receipt.at("sources").at("skill").at("attack_multiplier").get<float>() &&
              world.monsters.front().hp==std::max(0,before-receipt.at("hp_damage").get<int>()),
              "Actual magical damage consumes EQU magical24 separately from physical22 and publishes its result to HP");
        samples["magical_equipment_attack"]=receipt;
    }
    {
        Progression plainProgression(catalog),coatProgression(catalog);
        World plain(pvf,assets,WorldRules::BetaFoundationV1),coat(pvf,assets,WorldRules::BetaFoundationV1);
        plain.applyEquipment(plainProgression); coat.applyEquipment(coatProgression);
        check(coat.changeEquipment(coatProgression,damageOwn(coatProgression,10564)).ok,
              "Source defense coat10564 equips through the same live transaction");
        damageFloor(plain,false); damageFloor(coat,false);
        damageGoblin(plain,45); damageGoblin(coat,45);
        const int plainHp=plain.player.hp,coatHp=coat.player.hp;
        check(damageAwait(plain,"player_hit") && damageAwait(coat,"player_hit"),
              "Source goblin AI chooses its attack and makes real animation-box contact in both equipment states");
        const auto a=plain.statReport().at("last_damage"),b=coat.statReport().at("last_damage");
        check(a.at("usable")==true && b.at("usable")==true &&
              a.at("sources").at("attack").at("source").at("path")=="monster/goblin/attackinfo/attack1.atk" &&
              a.at("sources").at("attacker").at("physical_attack")==9 &&
              plain.player.hp==std::max(0,plainHp-a.at("hp_damage").get<int>()) &&
              coat.player.hp==std::max(0,coatHp-b.at("hp_damage").get<int>()),
              "Incoming HP writes consume MOB-bound ATK and equipment attack9 rather than the legacy five-point hit");
        const auto &da=damageStage(a,"target_defense"),&db=damageStage(b,"target_defense");
        check(b.at("sources").at("target").at("physical_defense").get<float>()==
                  a.at("sources").at("target").at("physical_defense").get<float>()+288 &&
              db.at("multiplier").get<float>()<da.at("multiplier").get<float>() &&
              damageStage(a,"random_variation").at("roll_0_999")==damageStage(b,"random_variation").at("roll_0_999") &&
              b.at("hp_damage").get<int>()<=a.at("hp_damage").get<int>(),
              "Real equipped PvE defense288 reduces the live ratio-defense multiplier under matching combat random draws");
        samples["incoming_plain"]=a; samples["incoming_coat"]=b;
    }
    {
        Progression progression(catalog);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);
        damageFloor(world,false);damageThrower(world);
        const auto before=damageWorldState(world);
        const auto definition=world.prepareMonsterProjectile(world.monsters.front());
        check(definition.usable() && definition.policy=="inferred-mob-particle-object-projectile-v1" &&
              definition.level==2 && definition.objectId==30001 && definition.objectType==1 && definition.power==0 &&
              definition.projectileCount==1 && definition.attackNumber==1,
              "Thrower source preflight selects the exact attack variant, frozen monster level and registered particle/OBJ beta policy");
        check(definition.object.path=="passiveobject/monster/goblin/throwstone.obj" &&
              definition.animation=="passiveobject/monster/goblin/animation/throwstone.ani" &&
              definition.attackPath=="passiveobject/monster/goblin/attackinfo/throwstone.atk" &&
              definition.attack.usable() && definition.attack.weaponDamageApply,
              "MOB throw-attack registration resolves OBJ ANI and physical weapon-applied ATK instead of the empty melee ATK slot");
        check(definition.throwFrame==2 && definition.offsetX==20 && definition.offsetY==0 && definition.offsetZ==60 &&
              definition.throwSound=="THROW_STONE" && definition.speed==250 && definition.lifetimeMs==1200 && definition.loop &&
              definition.motionParticle.path=="monster/goblin/particle/throwstone.ptl" &&
              definition.throwAnimation=="monster/goblin/animation_thrower/throw.ani",
              "Source throw frame, XYZ offset, sound, looping ANI and constant-X PTL speed/lifetime are typed launch inputs");
        bool exactBoxes=definition.projectileMotion && definition.projectileMotion->frames.size()==2;
        for(const auto &frame:definition.projectileMotion->frames) {
            const auto box=std::find_if(frame.boxes.begin(),frame.boxes.end(),[](const Box &value){return value.type==15;});
            exactBoxes=exactBoxes && box!=frame.boxes.end() && box->x==-10 && box->y==-10 && box->z==-10 &&
                box->w==20 && box->h==20 && box->d==20;
        }
        check(exactBoxes,"Both projectile ANI frames retain their source XYZ type-15 attack boxes without a fabricated contact volume");
        const auto full=definition.snapshot(true);
        check(definition.sources.at("throw_attack").at("byte_offset")==672 &&
              definition.sources.at("object_registration").at("member_path")=="passiveobject/passiveobject.lst" &&
              definition.sources.at("animation").at("member_sha256")==sha256(definition.projectileAnimationBytes) &&
              full.at("source_documents").at("object").at("raw_bytes").get<Bytes>()==pvf.read(definition.object.path) &&
              full.at("source_documents").at("motion_particle").at("tokens")==definition.motionParticle.tokens &&
              full.at("source_documents").at("projectile_animation_bytes").get<Bytes>()==pvf.read(definition.animation),
              "Projectile receipt preserves registry/member identity, field offsets, original script/ANI bytes and ordered PTL tokens");
        check(damageDiagnostic(definition,"projectile_destroy_particle_presentation_pending") &&
              definition.destroyParticle.path=="passiveobject/monster/goblin/particle/throwstonedestroy.ptl" &&
              full.at("capabilities").at("destroy_particle_presentation")==false,
              "Authored multi-particle destroy PTL remains source-preserved and explicitly pending rather than silently declared complete");
        Actor wrong=world.monsters.front();wrong.attackVariant=99;
        const auto absent=world.prepareMonsterProjectile(wrong);
        check(!absent.usable() && damageDiagnostic(absent,"missing_or_ambiguous_monster_throw_attack"),
              "An absent MOB throw attack variant returns a source diagnostic instead of borrowing another attack slot");
        wrong=world.monsters.front();wrong.sourceStats["level"]=3;
        const auto mismatch=world.prepareMonsterProjectile(wrong);
        check(!mismatch.usable() && damageDiagnostic(mismatch,"projectile_frozen_monster_source_mismatch"),
              "A projectile level that conflicts with the frozen source combat receipt rejects before live publication");
        wrong=world.monsters.front();wrong.monsterPath="monster/goblin/goblin.mob";wrong.combatAttributes.reset();
        const auto melee=world.prepareMonsterProjectile(wrong);
        check(!melee.usable() && damageDiagnostic(melee,"missing_or_ambiguous_monster_throw_attack") && damageWorldState(world)==before,
              "Nonthrowing MOB and all projectile preflights preserve live actors, HP, clock, IDs, RNG, inputs and event receipts");
        const int hpBefore=world.player.hp;
        const auto *spawned=damageAwaitProjectile(world);
        check(spawned && damageEvents(world,"monster_attack")==1 && damageEvents(world,"monster_projectile")==1,
              "Normal source thrower AI actually creates its projectile without diagnostic hits or debug overrides");
        const Effect launch=*spawned;
        const auto owner=world.monsters.front().handle;
        const int sourceAttack=world.monsters.front().combatAttributes->attributes->equipmentPhysicalAttack;
        check(!world.god && !world.freeCd && !world.debugOverrides().enabled && launch.attackInstance>0 &&
              launch.hostileOwnerHandle==owner && launch.hostileStats && launch.hostileStats->level==2 &&
              launch.hostileStats->physicalAttack==sourceAttack && sourceAttack==11 &&
              launch.animation==definition.animation && launch.hostileAttack==definition.attackPath &&
              launch.sourceObject==definition.object.path && launch.resourceSource==definition.motionParticle.path &&
              launch.speed==definition.speed && launch.expires-launch.born==definition.lifetimeMs &&
              launch.x==world.monsters.front().x+world.monsters.front().dir*definition.offsetX &&
              launch.y==world.monsters.front().y+definition.offsetY && launch.z==definition.offsetZ,
              "Live projectile carries stable attack identity, frozen source attack11 and the prepared OBJ/ANI/PTL launch inputs");
        check(damageAwait(world,"player_hit"),"The normally launched source projectile reaches a real ANI-box player contact");
        const auto receipt=world.statReport().at("last_damage");
        check(receipt.at("usable")==true && receipt.at("policy")=="inferred-pve-damage-v1" &&
              receipt.at("attack_instance")==launch.attackInstance && receipt.at("attacker")==owner.json() &&
              receipt.at("sources").at("attacker").at("physical_attack")==11 &&
              receipt.at("sources").at("attack").at("source").at("path")==definition.attackPath &&
              world.player.hp==std::max(0,hpBefore-receipt.at("hp_damage").get<int>()),
              "Projectile contact consumes OBJ-bound ATK and frozen monster attack11 through the unified HP damage consumer");
        world.advance(1000000000);
        check(damageEvents(world,"player_hit")==1,"A zero-piercing source projectile cannot apply duplicate player HP writes after its accepted hit");
        samples["thrower_projectile_definition"]=definition.snapshot();samples["thrower_projectile_damage"]=receipt;
    }
    {
        Progression progression(catalog);
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);
        damageFloor(world,false);damageThrower(world);
        const auto *spawned=damageAwaitProjectile(world);
        check(spawned!=nullptr,"Owner-lifetime regression starts with a projectile created by normal source AI");
        const Effect launch=*spawned;const int before=world.player.hp;
        world.monsters.clear();world.synchronizeEntityHandles();
        check(!world.resolveActor(launch.hostileOwnerHandle),"The projectile's originating entity handle is stale after its owner is removed");
        check(damageAwait(world,"player_hit"),"An already launched source projectile remains executable after its owner is removed");
        const auto receipt=world.statReport().at("last_damage");
        check(receipt.at("usable")==true && receipt.at("attack_instance")==launch.attackInstance &&
              receipt.at("attacker")==launch.hostileOwnerHandle.json() && receipt.at("policy")=="inferred-pve-damage-v1" &&
              receipt.at("sources").at("attacker").at("physical_attack")==launch.hostileStats->physicalAttack &&
              world.player.hp==std::max(0,before-receipt.at("hp_damage").get<int>()),
              "Stale owner lookup retains the projectile's launch identity and source damage snapshot without legacy eight-point fallback");
        samples["removed_owner_projectile_damage"]=receipt;
    }
    {
        Progression progression(catalog);
        World world(pvf,assets,WorldRules::BetaFoundationV1); world.applyEquipment(progression);
        damageFloor(world); damageGoblin(world,45);
        RegionSession session; session.begin(catalog,1,19801,{},"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
        auto saved=session.save(world,"dungeon");
        auto &frozen=saved["room_states"][session.run.current][0]["source_stats"]["combat"];
        frozen["attributes"]["equipment_physical_attack"]=123;
        frozen["future_test_metadata"]={{"preserved",true}};
        RegionSession restored;
        check(restored.load(saved,catalog) && restored.restore(world) && world.monsters.front().hp==35 &&
              world.monsters.front().combatAttributes->attributes->equipmentPhysicalAttack==123 &&
              world.monsters.front().combatAttributes->snapshot().at("future_test_metadata").at("preserved")==true,
              "Session restores frozen in-range combat values and unknown metadata without recomputing the source nine");
        world.freezeAi=false;
        check(damageAwait(world,"player_hit") &&
              world.statReport().at("last_damage").at("sources").at("attacker").at("physical_attack")==123,
              "A restored goblin actually attacks with the frozen123 value through the normal AI damage consumer");
        const auto before=damageWorldState(world);
        auto corrupt=saved;
        corrupt["room_states"][session.run.current][0]["source_stats"]["combat"]["sources"]["monster"]["member_sha256"]="wrong-source-hash";
        RegionSession invalid; bool rejected=false;
        try { invalid.load(corrupt,catalog); invalid.restore(world); } catch(const std::exception &) { rejected=true; }
        check(rejected && damageWorldState(world)==before,
              "A frozen source-hash mismatch rejects room restore before changing actors, RNG, clock, inputs, events or damage trace");
        auto unknown=saved; unknown["monster_combat_policy"]="future-unknown-policy";
        const auto sessionBefore=restored.save(world,"dungeon"); rejected=false;
        try { restored.load(unknown,catalog); } catch(const std::exception &) { rejected=true; }
        check(rejected && restored.save(world,"dungeon")==sessionBefore && damageWorldState(world)==before,
              "Unknown frozen run combat policy rejects load atomically and retains the existing session and World");
        samples["restored_damage"]=world.statReport().at("last_damage");
    }
    {
        Progression progression(catalog);
        World world(pvf,assets,WorldRules::BetaFoundationV1); world.applyEquipment(progression);
        damageFloor(world); damageGoblin(world,80,"inferred-mob-table-hp-v1","legacy-snapshot-damage-v1");
        RegionSession old; old.begin(catalog,1,19802,{},"inferred-mob-table-hp-v1");
        auto saved=old.save(world,"dungeon"); saved.erase("monster_combat_policy");
        RegionSession migrated;
        check(migrated.load(saved,catalog) && migrated.monsterCombatPolicy=="legacy-snapshot-damage-v1" && migrated.restore(world) &&
              !world.monsters.front().combatAttributes && world.monsters.front().hp==35,
              "HP-only historical sessions missing combat policy retain their saved HP and legacy damage identity");
        const bool unvisited=std::any_of(migrated.roomStates.begin(),migrated.roomStates.end(),[](const Json &state){return state.is_null();});
        world.monsters.clear(); damageGoblin(world,80,migrated.monsterStatPolicy,migrated.monsterCombatPolicy);
        check(unvisited && world.monsters.front().hp==35 && !world.monsters.front().combatAttributes &&
              !world.monsters.front().sourceStats.contains("combat"),
              "A previously unvisited room in the restored HP-only run initializes source HP without silently adopting new combat arithmetic");
        world.normalAttack();
        check(damageAwait(world,"hit") && world.monsters.front().hp<35 &&
              world.statReport().at("last_damage").at("policy")=="legacy-snapshot-damage-v1",
              "Ordinary input against a historical HP-only actor consumes the explicit legacy snapshot damage policy");
    }
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"samples",samples},
        {"scope","Real World source-box ordinary/magical contact, EQU transaction, goblin AI ATK/defense, source MOB/registry/OBJ/ANI/PTL projectile launch/contact and removed-owner lifetime, frozen session restore and legacy run compatibility; inferred arithmetic/particle-object dispatch, destroy-particle presentation pending; no frontend or original-client parity claim"}};
}
} // namespace dnf
