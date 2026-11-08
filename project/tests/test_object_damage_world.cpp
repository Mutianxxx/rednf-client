#include "dnf/combat.hpp"
#include "dnf/objects.hpp"
#include "dnf/progression.hpp"
#include "dnf/scene.hpp"
#include <stdexcept>

namespace dnf {
Json runObjectDamageWorldTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool okay,const char *message) {
        if (!okay) throw std::runtime_error(std::string("Object damage World: ")+message);
        checks.push_back(message);
    };
    RegionCatalog regions(pvf,assets);
    Progression progression(regions);
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    world.applyEquipment(progression);
    world.player.x=500;world.player.y=344;world.player.dir=1;
    world.combat=true;world.freezeAi=true;
    world.mapWidth=1200;world.walkRects={{0,240,1200,240}};
    ObjectCatalog catalog(pvf,assets);
    const auto definition=catalog.definition(10422);
    check(definition->source=="passiveobject/actionobject/map/haze/drum_map1.obj" &&
          definition->explicitHpMax==10000,
          "A real registered source drum supplies its explicit 10000 HP without a demo durability value");
    ObjectPlacement placement;
    placement.id=definition->id;placement.x=560;placement.y=344;
    placement.identity={"object-damage-run","room","diagnostic-object-contact.map",34,0};
    Scene scene;
    scene.objectSystem.add(placement,definition,currentObjectBehavior(*definition));
    auto &object=*scene.objectSystem.find(placement.identity);
    const auto boxes=object.damageBoxes();
    check(!boxes.empty(),"The real source drum animation exposes a decoded hurt box to the running ObjectSystem");
    const auto &box=boxes.front();
    world.normalAttack();
    for (int i=0;i<100 && world.attackVolumes.empty();++i) world.advance(16666667);
    check(!world.attackVolumes.empty() && world.attackVolumes.front().sourceAttack &&
          world.attackVolumes.front().sourceModifiers,
          "Normal attack scheduling freezes the actual source ATK and modifiers before the caller's pose can change");
    AttackVolume volume=world.attackVolumes.front();
    world.idle();
    check(world.player.animation=="stay","The source attack receipt survives an actual return to idle before object contact");
    volume.x=volume.y=volume.z=0;
    volume.box={15,int(box.x),int(box.y),int(box.z),int(box.w),int(box.h),int(box.d)};
    volume.damage=0; // The beta geometry preview is deliberately non-numerical.
    world.attackVolumes={volume};
    scene.updateObjects(world,pvf,assets);
    const auto after=scene.objectSystem.find(placement.identity)->durability.value();
    const auto receipt=world.statReport().at("last_damage");
    check(receipt.at("usable")==true && receipt.at("hp_damage").get<int>()>0 && after<10000 &&
          after==10000-receipt.at("hp_damage").get<int>(),
          "Scene consumes unified source damage for explicit-HP objects even when AttackVolume preview is zero");
    check(receipt.at("sources").at("target").at("adapter")=="inferred-explicit-hp-object-target-v1" &&
          receipt.at("sources").at("target").at("sources").at("object_identity")==placement.identity.json() &&
          receipt.at("sources").at("attack").at("source").at("path")=="character/swordman/attackinfo/attack1.atk",
          "The receipt retains the persistent object identity, neutral-target inference and actual player ATK source");
    auto random=world.simulationCheckpoint().at("random");
    scene.updateObjects(world,pvf,assets);
    check(scene.objectSystem.find(placement.identity)->durability==after &&
          world.simulationCheckpoint().at("random")==random,
          "A duplicate Scene contact changes neither object HP nor the combat random stream");
    world.attackVolumes.front().serial++;
    world.attackVolumes.front().box.x+=10000;
    scene.updateObjects(world,pvf,assets);
    check(scene.objectSystem.find(placement.identity)->durability==after &&
          world.simulationCheckpoint().at("random")==random,
          "A geometrically rejected contact consumes no combat random draws");
    // Unknown target combat fields must never be silently replaced by zero.
    auto unsupported=std::make_shared<ObjectDefinition>(*definition);
    unsupported->script.fields.push_back({"[physical defense]",Json::array({80}),unsupported->script.rawBytes.size()});
    ObjectInstance candidate=object;candidate.definition=unsupported;
    const auto rejected=world.resolveObjectContact(volume,candidate);
    check(!rejected.usable() && world.simulationCheckpoint().at("random")==random,
          "Authored target defense without a consumer blocks damage and preserves RNG");
    // An accepted miss must retire this contact without hurting or reacting.
    ObjectAttack missed;
    missed.owner=0;missed.serial=777;missed.missed=true;
    missed.volume=box;missed.damage=0;
    const auto previousState=object.state;
    check(scene.objectSystem.contact(placement.identity,missed) &&
          object.durability==after && object.state==previousState &&
          !scene.objectSystem.acceptsContact(placement.identity,missed),
          "An accepted miss is deduplicated without HP loss or reaction state changes");
    bool missFound=false;
    for (const auto &event:scene.objectSystem.pendingEvents()) {
        if (event.kind=="miss") missFound=true;
    }
    // Scene acknowledges ordinary hit events, while the direct miss above stays pending.
    check(missFound,"The object miss has a stable pending event rather than a repeated numerical roll");
    {
        auto robot=volume;robot.serial+=1000;
        robot.sourceAttack=readAttackDamage(pvf.script("passiveobject/character/gunner/attackinfo/rx78explosion.atk"));
        robot.sourceModifiers=DamageSkillModifiers{};robot.sourceModifiers->fixedDamage=100;robot.sourceModifiers->percent=0;
        const auto before=scene.objectSystem.find(placement.identity)->durability.value();world.attackVolumes={robot};
        scene.updateObjects(world,pvf,assets);const auto result=world.statReport().at("last_damage");
        bool fort=false;for(const auto &stage:result.at("trace"))
            if(stage.value("stage",std::string())=="target_category_rate" && stage.at("target_category")=="fort" && stage.at("percent")==125)fort=true;
        check(result.at("usable")==true && fort && result.at("sources").at("target").at("target_category")=="fort" &&
              scene.objectSystem.find(placement.identity)->durability.value()==before-result.at("hp_damage").get<int>(),
            "Actual Scene/ObjectSystem consumes original robot fort125 against a source destructible object through the same damage chain");
        auto unknown=std::make_shared<ObjectDefinition>(*definition);size_t offset=unknown->script.rawBytes.size();
        unknown->script.fields.push_back({"[category]",Json::array({"[divine armor]"}),offset});
        unknown->script.rawBytes.resize(offset+10);unknown->script.fields.push_back({"[/category]",Json::array(),offset+10});
        unknown->script.rawBytes.resize(offset+15);unknown->script.source["member_sha256"]=sha256(unknown->script.rawBytes);
        ObjectInstance target=object;target.definition=unknown;robot.serial+=1;
        const auto rng=world.simulationCheckpoint().at("random");const auto rejectedClass=world.resolveObjectContact(robot,target);
        check(!rejectedClass.usable() && world.simulationCheckpoint().at("random")==rng,
            "Unknown explicit object armor rejects a nonneutral category attack without even allocating a new normal RNG stream");
    }
    samples["source_damage"]=receipt;samples["object_after"]=scene.objectSystem.save();
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","Scene/ObjectSystem numerical contact consumer; source drum destruction/spawn/PTL lifecycle not claimed"}};
}
} // namespace dnf
