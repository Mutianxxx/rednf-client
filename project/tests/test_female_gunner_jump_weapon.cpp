#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/source_weapon_qualification.hpp"
#include "dnf/storage.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
Json runFemaleGunnerJumpWeaponTests(Pvf &pvf,Assets &assets) {
    RegionCatalog regions(pvf,assets);Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message) {
        checks.push_back({{"passed",pass},{"message",message}});
        if(!pass){writeJson("jump-weapon-failed.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}
    };
    try {
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("jump-weapon-fixture-"+std::string(ani_clock::policyName(clock))));
        store.data["characters"][0]={{"name","JumpWeapon"},{"class","atgunner"},{"identity",CharacterIdentity{5,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clock);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        const auto floor=[&]() {world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
            world.combat=true;world.freezeAi=true;world.freeCd=true;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};
            auto &p=world.player;p.x=p.px=500;p.y=p.py=300;p.z=p.pz=0;p.vz=0;p.dir=1;p.mp=INT32_MAX;
            p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;};
        const auto press=[&](int key,bool down) {world.enqueue({world.simulationNanoseconds(),key,down});};
        const auto jump=[&]() {press(5,true);world.advanceSingleTick();press(5,false);for(int tick=0;tick<5;++tick)world.advanceSingleTick();};
        const auto bullets=[&]() {Json rows=Json::array();for(const auto &fx:world.effects)if(fx.phase=="female-gunner:ordinary_bullet")
            rows.push_back({{"id",fx.id},{"position",{fx.x,fx.y,fx.z}},{"source",fx.projectileSource}});return rows;};
        const Field *table=nullptr;
        for(const auto &field:plan.characterDefinition.settings.script.fields)if(field.tag=="[key value index]"&&!field.values.empty()&&
            (field.values[0]=="weaponSubTypeIndex"||field.values[0]=="defaultWeaponBySubType")) {
            if(table)throw std::invalid_argument("Ambiguous source weapon table");table=&field;
        }
        if(!table)throw std::invalid_argument("Missing source weapon table");
        for(int subtype=0;subtype<5;++subtype) {
            floor();int equipment=-1;
            for(size_t i=2;i+1<table->values.size();i+=2)if(table->values[i]==subtype)equipment=table->values[i+1].get<int>();
            const auto *item=progression.item(equipment);if(!item)throw std::invalid_argument("Missing source weapon item");
            check(characterWeaponSourceSupported(plan.characterDefinition,item->source,item->weapon),"Raw current CHR row supports equipped subtype "+std::to_string(subtype));
            auto duplicate=item->source;for(const auto &field:item->source.fields)if(normalize(field.tag)=="[sub type]"){duplicate.fields.push_back(field);break;}
            check(!characterWeaponSourceSupported(plan.characterDefinition,duplicate,item->weapon),"Repeated source subtype cannot qualify a weapon");
            auto invalid=item->source;for(auto &field:invalid.fields)if(normalize(field.tag)=="[sub type]")field.values={9999};
            check(!characterWeaponSourceSupported(plan.characterDefinition,invalid,item->weapon),"Out-of-range subtype cannot bypass current CHR row boundary");
            while(progression.level()<item->minimumLevel)progression.addExperience(progression.experienceToNextLevel());
            const auto uid=progression.state.at("next_uid").get<int>();const auto index=int(progression.state.at("inventory").size());
            progression.state["next_uid"]=uid+1;progression.state["inventory"].push_back({{"uid",uid},{"id",equipment},{"count",1},{"durability",item->durability}});
            const auto equipped=world.changeEquipment(progression,index);
            evidence.push_back({{"phase","equip"},{"subtype",subtype},{"source",item->path},{"legacy_category",item->weapon},
                {"success",equipped.ok},{"message",equipped.message}});
            check(equipped.ok,"Actual World EQU/LAY transaction equips source subtype "+std::to_string(subtype));
            store.capture(0,world,progression);Progression restoredProgression(regions);World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.enableExperimentalCharacters();
            store.apply(0,restored,restoredProgression);
            check(restoredProgression.state.at("equipped")==progression.state.at("equipped"),"Source weapon including subtype4 survives actual capture/apply restoration");
            for(const bool airborne:{false,true})for(const int direction:{-1,1}) {
                floor();world.player.dir=direction;const auto normal=world.skillState().snapshot(world.nowMs());if(airborne)jump();
                check(!airborne||world.player.z>0,"Actual JUMP enters airborne state before aerial X");press(4,true);
                std::set<std::string> motions;std::set<uint64_t> bulletIds;bool sawReady=false,sawShoot=false,sawEnd=false,wrongShotSource=false;Json firstBullet;
                for(int tick=0;tick<90;++tick) {
                    if(airborne&&tick<8)press(4,true); // Repeats during the ready stage cannot manufacture another shot.
                    world.advanceSingleTick();motions.insert(world.player.animationPath);
                    sawReady|=world.player.animationPath=="character/gunner/atanimation/jumpattackready.ani";
                    sawShoot|=world.player.animationPath=="character/gunner/atanimation/jumpattackshoot.ani";
                    sawEnd|=world.player.animationPath=="character/gunner/atanimation/jumpattackend.ani";
                    for(const auto &row:bullets()) {
                        if(bulletIds.insert(row.at("id").get<uint64_t>()).second&&firstBullet.is_null())firstBullet=row;
                        const auto &source=row.at("source");const auto &trace=source.at("coordinate_trace");
                        if(airborne)wrongShotSource|=trace.at("body").at("member_path")!="character/gunner/atanimation/jumpattackshoot.ani";
                    }
                }
                check(!firstBullet.is_null(),"Actual ground/aerial X emits equipped source projectile "+std::to_string(subtype));
                check(!wrongShotSource,"Ready/end pose never emits a bullet; actual aerial projectile belongs to source shoot stage");
                check(bulletIds.size()==1,"One ordinary activation produces one projectile with repeated DOWN");
                check(!airborne||(sawReady&&sawShoot&&sawEnd),"Female aerial X renders all three distinct source stages");
                const auto &sourceBinding=firstBullet.at("source").at("basic_source_binding");
                check(sourceBinding.at("object_id")==22001+3*subtype+(airborne?2:0)&&
                      sourceBinding.at("variant")==std::string(airborne?"jump":"up"),
                    "Actual equipped Up/Jump source PTL chooses its independent registered object, not an Up-only name template");
                const auto actualObject=firstBullet.at("source").at("object").at("member_path").get<std::string>();
                check(actualObject==sourceBinding.at("object").at("member_path")&&
                    (!airborne||firstBullet.at("source").at("attack").at("member_path").get<std::string>().find("/jumpbullet")!=std::string::npos),
                    "Published aerial projectile retains its source Jump OBJ and dedicated Jump ATK");
                const auto &trace=firstBullet.at("source").at("coordinate_trace");
                const auto &muzzle=trace.at("weapon_muzzle").at("local_point"),&offset=trace.at("offset_xyz");
                const bool visibleSprite=!trace.at("bullet_sprite").is_null();
                const auto sprite=visibleSprite?trace.at("bullet_sprite").at("local_point"):Json::array({0,0});
                check(std::abs(offset[0].get<double>()+sprite[0].get<double>()-muzzle[0].get<double>())<.001&&
                      std::abs(-offset[2].get<double>()+sprite[1].get<double>()-muzzle[1].get<double>())<.001,
                    visibleSprite?"Transformed visible projectile center equals inferred source weapon muzzle":
                        "Transparent projectile preserves source origin at inferred weapon muzzle; visible center is unverified");
                check(world.skillState().snapshot(world.nowMs())==normal,"Ordinary source stages leave normal skill learning ledger unchanged");
                evidence.push_back({{"clock",ani_clock::policyName(clock)},{"subtype",subtype},{"airborne",airborne},{"direction",direction},
                    {"motions",motions},{"first_bullet",firstBullet},{"projectile_count",bulletIds.size()}});
            }
            if(subtype==0)for(const int direction:{-1,1}) {
                floor();world.player.dir=direction;
                for(const double distance:{100.0,250.0,400.0}) {
                    Actor target;target.id=int(world.monsters.size()+1);target.sourceId=10;
                    target.monsterPath="monster/goblin/goblin.mob";target.x=target.px=world.player.x+direction*distance;
                    target.y=target.py=world.player.y;target.dir=-direction;
                    world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
                    target.hp=target.maxHp=100000000;world.monsters.push_back(std::move(target));
                }
                world.synchronizeEntityHandles();press(4,true);
                for(int tick=0;tick<90;++tick)world.advanceSingleTick();
                Json targets=Json::array();size_t hits=0;
                for(const auto &target:world.monsters){hits+=target.hp<target.maxHp;
                    targets.push_back({{"handle",target.handle.json()},{"hp",target.hp},{"max_hp",target.maxHp}});}
                evidence.push_back({{"phase","three_actual_goblin_source_targets"},{"clock",ani_clock::policyName(clock)},
                    {"direction",direction},{"targets",targets},{"world",world.femaleGunnerDiagnostics()}});
                check(hits==3,"One actual source revolver projectile reaches all three real MOB hurt-box targets");
            }
        }
        floor();const auto originalAppearance=world.characterAppearance();auto bodyOnly=originalAppearance;
        bodyOnly.parts.erase("[weapon]");world.setCharacterAppearance(std::move(bodyOnly));press(4,true);
        Json fallbackBullet;
        for(int tick=0;tick<90;++tick){world.advanceSingleTick();for(const auto &row:bullets())if(fallbackBullet.is_null())fallbackBullet=row;}
        check(!fallbackBullet.is_null(),"Missing weapon pixels preserve actual body activation and projectile publication");
        check(fallbackBullet.at("source").at("coordinate_trace").at("muzzle_basis")=="diagnosed_source_body_fallback"&&
              !fallbackBullet.at("source").at("diagnostics").empty(),"Missing visible weapon muzzle has a specific source-backed fallback receipt");
        evidence.push_back({{"phase","actual_missing_weapon_pixel_fallback"},{"clock",ani_clock::policyName(clock)},{"projectile",fallbackBullet}});
        world.setCharacterAppearance(originalAppearance);
        for(const auto *cancel:{"landing","interrupted","scene","dead"}) {
            floor();jump();press(4,true);world.advanceSingleTick();check(bullets().empty(),"Ready pose has no early bullet");
            if(std::string(cancel)=="landing"){world.player.z=1;world.player.vz=-1000;}
            else if(std::string(cancel)=="interrupted")world.player.recovery=5;
            else if(std::string(cancel)=="dead"){world.player.dead=true;world.player.life=ActorLife::Dying;}
            else world.changeScene();
            for(int tick=0;tick<60;++tick)world.advanceSingleTick();
            check(bullets().empty(),std::string("No delayed ready-stage shot survives ")+cancel);
        }
    }
    // Male TurningShoot is also explicitly described as inheriting current
    // HeadShot MP. This only restores the authorized generic test template.
    Progression progression(regions);World male(pvf,assets,WorldRules::BetaFoundationV1);male.enableExperimentalCharacters();
    CharacterStore store(std::filesystem::absolute("male-turning-fixture"));
    store.data["characters"][0]={{"name","MaleTurning"},{"class","gunner"},{"identity",CharacterIdentity{2,0,0}.json()},
        {"level",1},{"skill_initialization","source-v1"}};store.apply(0,male,progression);dnf::enterExplicitSkillPreviewFixture(male);
    auto &runtime=*male.experimentalRuntime();const auto &plan=runtime.plan();
    runtime.configuration().configureBasicAttackTemplate({2,5},1,plan);runtime.configuration().configureBasicAttackTemplate({2,20},1,plan);
    runtime.configuration().assignSlot(0,SkillKey{2,20},plan);male.player.mp=INT32_MAX;male.freeCd=true;
    const auto before=male.player.mp;male.enqueue({male.simulationNanoseconds(),20,true});male.advanceSingleTick();
    check(runtime.attacking(),"Male TurningShoot actual temporary template starts with inherited source MP");
    const auto cost=runtime.snapshotDiagnostics().at("last_cost");
    check(cost.contains("inferred_turning_shoot_mp_inheritance")&&male.player.mp<before,"Male inherited MP has actual debit and source receipt");
    evidence.push_back({{"phase","male_turning_template"},{"last_cost",cost},{"classification","source MP restoration; full native skill incomplete"}});
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"source_stage_order_classification","inferred from current CHR ready/shoot/end bindings; native setters unverified"},
        {"original_dynamic_comparison","pending_user"}};
    }catch(const std::exception &error) {
        writeJson("jump-weapon-exception.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence}});throw;
    }
}
}
