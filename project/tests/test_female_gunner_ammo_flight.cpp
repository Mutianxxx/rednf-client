#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/storage.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
Json runFemaleGunnerAmmoFlightTests(Pvf &pvf,Assets &assets) {
    RegionCatalog regions(pvf,assets);Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool pass,const std::string &message){
        checks.push_back({{"passed",pass},{"message",message}});
        if(!pass){writeJson("ammo-flight-failed.json",{{"checks",checks},{"evidence",evidence}});throw std::runtime_error(message);}
    };
    for(const auto clock:{ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        Progression progression(regions);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        CharacterStore store(std::filesystem::absolute("ammo-flight-fixture-"+std::string(ani_clock::policyName(clock))));
        store.data["characters"][0]={{"name","AmmoFlight"},{"class","atgunner"},{"identity",CharacterIdentity{5,0,0}.json()},
            {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(clock);
        auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        const auto floor=[&](){world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
            world.combat=true;world.freezeAi=true;world.freeCd=true;world.mapWidth=3000;world.walkRects={{0,185,3000,600}};
            auto &p=world.player;p.x=p.px=1000;p.y=p.py=300;p.z=p.pz=0;p.vz=0;p.dir=1;p.mp=INT32_MAX;
            p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;};
        const Field *table=nullptr;for(const auto &field:plan.characterDefinition.settings.script.fields)
            if(field.tag=="[key value index]"&&!field.values.empty()&&
                (field.values[0]=="weaponSubTypeIndex"||field.values[0]=="defaultWeaponBySubType"))table=&field;
        if(!table)throw std::invalid_argument("Missing source weapon table");
        for(int subtype=0;subtype<5;++subtype) {
            floor();int equipment=-1;for(size_t i=2;i+1<table->values.size();i+=2)if(table->values[i]==subtype)equipment=table->values[i+1].get<int>();
            const auto *item=progression.item(equipment);if(!item)throw std::invalid_argument("Missing current weapon item");
            while(progression.level()<item->minimumLevel)progression.addExperience(progression.experienceToNextLevel());
            const auto uid=progression.state.at("next_uid").get<int>();const auto inventory=int(progression.state.at("inventory").size());
            progression.state["next_uid"]=uid+1;progression.state["inventory"].push_back({{"uid",uid},{"id",equipment},{"count",1},{"durability",item->durability}});
            const auto equipped=world.changeEquipment(progression,inventory);check(equipped.ok,"Actual EQU/LAY equips source weapon for ammo visual");
            for(const int skill:{1,2,30,52})for(const int direction:{-1,1})for(const bool airborne:{false,true}) {
                if(airborne&&subtype!=0&&subtype!=4)continue;
                floor();world.player.dir=direction;runtime.configuration()=ExperimentalSkillConfiguration(plan);
                runtime.configuration().configureFemaleGunnerSourceSkill({5,skill},1,plan);runtime.configuration().assignSlot(0,SkillKey{5,skill},plan);
                const auto normal=world.skillState().snapshot(world.nowMs());const auto mp=world.player.mp;
                world.enqueue({world.simulationNanoseconds(),20,true});bool started=false,finished=false;
                for(int step=0;step<600;++step){world.advanceSingleTick();started|=runtime.attacking();if(started&&!runtime.attacking()){finished=true;break;}}
                check(started&&finished&&world.player.mp<mp,"Real configured ammo input finishes and debits its source MP");
                world.enqueue({world.simulationNanoseconds(),20,false});world.advanceSingleTick();
                const auto buffBefore=world.femaleGunnerDiagnostics().at("buffs");
                check(buffBefore.size()==1,"Real source buff reaches World before ordinary X");
                const auto countBefore=buffBefore[0].at("command").at("count").get<uint32_t>();
                if(airborne) {
                    world.enqueue({world.simulationNanoseconds(),5,true});world.advanceSingleTick();
                    world.enqueue({world.simulationNanoseconds(),5,false});for(int step=0;step<5;++step)world.advanceSingleTick();
                    check(world.player.z>0,"Real jump input enters airborne state before attribute X");
                }
                if(subtype==0&&!airborne)for(const double distance:{100.0,250.0,400.0}) {
                    Actor target;target.id=int(world.monsters.size()+1);target.sourceId=10;target.monsterPath="monster/goblin/goblin.mob";
                    target.x=target.px=world.player.x+direction*distance;target.y=target.py=world.player.y;target.dir=-direction;
                    world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
                    target.hp=target.maxHp=100000000;world.monsters.push_back(std::move(target));
                }
                world.synchronizeEntityHandles();world.enqueue({world.simulationNanoseconds(),4,true});
                Json first,firstEntity;std::set<int> ordinaryVisuals,extraVisuals;size_t accepted=0;
                for(int step=0;step<90;++step) {
                    world.advanceSingleTick();
                    for(const auto &fx:world.effects) {
                        if(fx.phase=="female-gunner:ordinary_bullet") {
                            ordinaryVisuals.insert(fx.id);if(first.is_null())first={{"animation",fx.animation},{"direction",fx.dir},
                                {"position",{fx.x,fx.y,fx.z}},{"source",fx.projectileSource}};
                        }
                        if(fx.phase=="female-gunner:enchanted_bullet"&&fx.projectileSource.value("role",std::string())=="projectile")extraVisuals.insert(fx.id);
                    }
                    const auto current=world.femaleGunnerDiagnostics();
                    for(const auto &entity:current.at("entities"))if(entity.at("command").at("family")=="ordinary_bullet") {
                        if(firstEntity.is_null())firstEntity=entity;accepted=std::max(accepted,entity.at("accepted_targets").get<size_t>());
                    }
                }
                evidence.push_back({{"clock",ani_clock::policyName(clock)},{"subtype",subtype},{"skill",skill},{"direction",direction},{"airborne",airborne},
                    {"first_visual",first},{"first_entity",firstEntity},{"ordinary_visual_count",ordinaryVisuals.size()},
                    {"extra_ammo_visual_count",extraVisuals.size()},{"ordinary_accepted_targets",accepted},
                    {"diagnostics",world.femaleGunnerDiagnostics()}});
                check(!first.is_null()&&ordinaryVisuals.size()==1,"One ordinary X has one source flight visual");
                check(extraVisuals.empty(),"Additive enchanted damage does not draw a duplicate ordinary projectile");
                const auto &binding=first.at("source").at("ammo_visual_binding");
                const auto collision=first.at("source").at("animation").at("member_path").get<std::string>();
                check(firstEntity.at("collision_animation").at("member_path")==collision,"Actual entity preserves original OBJ collision ANI");
                if(subtype==3)check(binding.at("result")=="native_null_for_handcannon_preserve_basic_visual"&&first.at("animation")==collision,
                    "Handcannon native-null attribute selection preserves source base flight");
                else {
                    const auto attribute=binding.at("flight_animation").at("member_path").get<std::string>();
                    check(first.at("animation")==attribute&&attribute!=collision,"Actual renderer receives attribute ANI independently of collision ANI");
                    check(attribute.find("31439")==std::string::npos&&binding.at("owner_override").is_string(),"Unresolved native equipment override is retained, never replaced with constant 31439");
                    const std::string prefix=skill==1?"flame":skill==2?"freeze":skill==30?"silver":"1_tan_normal";
                    const std::string suffix=subtype==2?"musket.ani":subtype==4?"bowgun.ani":skill==52?".ani":"pistol.ani";
                    check(attribute=="character/gunner/effect/animation/bullet/"+prefix+suffix,"Equipped weapon subtype consumes current version default selector");
                    check(binding.at("collision_animation_preserved").at("member_path")==collision,"Visual receipt retains exact collision provenance");
                }
                check(first.at("direction")==direction,"Attribute flight consumes actual actor direction");
                const auto buffsAfter=world.femaleGunnerDiagnostics().at("buffs");
                check((countBefore==1&&buffsAfter.empty())||(buffsAfter.size()==1&&buffsAfter[0].at("command").at("count")==countBefore-1),
                    "One real ordinary activation consumes one source ammo charge");
                if(subtype==0&&!airborne) {
                    size_t hit=0;for(const auto &target:world.monsters)hit+=target.hp<target.maxHp;
                    check(hit==3&&accepted==3,"Attribute visuals preserve one ordinary projectile hit ledger through three real MOB hurt boxes");
                }
                check(world.skillState().snapshot(world.nowMs())==normal,"Test ammo release and source colors leave normal learning state unchanged");
                if(subtype==0&&skill==30&&direction==1&&!airborne) {
                    world.player.dead=true;world.player.life=ActorLife::Dying;world.advanceSingleTick();
                    const auto death=world.femaleGunnerDiagnostics();
                    check(death.at("entities").empty()&&death.at("buffs").empty(),"Death clears property ammo ownership before another ordinary shot");
                }
                world.changeScene();check(world.femaleGunnerDiagnostics().at("entities").empty()&&world.femaleGunnerDiagnostics().at("buffs").empty(),
                    "Scene cancellation removes attribute damage and visuals with source ownership");
            }
        }
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"limitations",{"Default native selector only; owner override and excluded native modes unresolved","Silver PTL trail and native hit selector are preserved evidence, not integrated", "Original frontend and dynamic visual comparison pending user"}}};
}
}
