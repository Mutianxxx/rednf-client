#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/storage.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
Json runEquipmentResourceWorldTests(Pvf &pvf, Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool ok,const char *message) {
        if (!ok) throw std::runtime_error(std::string("Equipment resource consumer: ")+message);
        checks.push_back(message);
    };
    RegionCatalog catalog(pvf,assets);
    Progression progression(catalog);
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    world.applyEquipment(progression);
    const auto *coat=progression.item(10564);
    check(coat && coat->source.number("[HP MAX]")==100 && coat->source.number("[MP MAX]")==100,
          "Current EQU 10564 supplies the two independently authored 100-point resource deltas");
    const auto coatSlot=coat->slot;
    const int index=int(progression.state.at("inventory").size());
    const int uid=progression.state.at("next_uid").get<int>();
    progression.state["inventory"].push_back({{"uid",uid},{"id",10564},{"count",1},{"durability",coat->durability}});
    progression.state["next_uid"]=uid+1;
    world.player.hp=137; world.player.mp=121;
    check(world.changeEquipment(progression,index).ok && world.player.maxHp==280 && world.player.maxMp==240 &&
          world.player.hp==137 && world.player.mp==121 && progression.equipped(index),
          "The real equipment-change transaction publishes HP/MP maxima together with the owned equipped instance without healing");
    const auto equippedReport=world.statReport();
    check(equippedReport.at("equipment_resources").at("usable")==true &&
          equippedReport.at("equipment_resources").at("policy")=="inferred-equipment-resource-flat-rate-v1" &&
          !equippedReport.at("equipment_resources").at("trace").empty(),
          "Live stat diagnostics expose source resource grouping, equipment ownership and the inferred policy");
    for(int i=0;i<3;++i) world.applyEquipment(progression);
    check(world.player.maxHp==280 && world.player.maxMp==240 && world.player.hp==137 && world.player.mp==121,
          "Repeated runtime synchronization rebuilds from pure CHR and never stacks equipped resource deltas");
    const auto normalLedger=progression.state;
    DebugOverrides debug; debug.enabled=true; debug.level=3;
    world.applyDebugOverrides(debug,progression.level());
    check(world.characterLevel==3 && world.player.maxHp==370 && world.player.maxMp==290 &&
          world.player.hp==137 && world.player.mp==121 && progression.state==normalLedger,
          "Debug level recomputes CHR and equipment maxima while keeping normal equipment qualification and the progression ledger intact");
    world.applyDebugOverrides({},progression.level());
    check(world.characterLevel==1 && world.player.maxHp==280 && world.player.maxMp==240 && world.player.hp==137,
          "Disabling debug level restores normally qualified resource limits without healing or accumulating bonuses");
    progression.addExperience(progression.experienceToNextLevel());
    world.applyEquipment(progression);
    check(world.characterLevel==2 && world.player.maxHp==325 && world.player.maxMp==265 &&
          world.player.hp==182 && world.player.mp==146,
          "Normal source growth with equipped HP/MP preserves absolute resource loss across both new maxima");
    check(world.changeEquipment(progression,index,true).ok && world.player.maxHp==225 && world.player.maxMp==165 &&
          world.player.hp==182 && world.player.mp==146 && !progression.equipped(index),
          "Unequipping removes both contributions atomically and clamps current values without extra restoration");
    check(world.changeEquipment(progression,index).ok,"The same owned coat can be equipped again through the transaction service");
    progression.state["inventory"][index]["durability"]=0;
    world.applyEquipment(progression);
    check(world.player.maxHp==225 && world.player.maxMp==165 && world.player.hp==182 &&
          progression.state["inventory"][index]["id"]==10564 && progression.equipped(index),
          "Broken-item policy removes resource effects while retaining the equipped inventory instance");
    progression.state["gold"]=1000000;
    check(progression.repair(index).ok,"The real source repair service repairs the resource-bearing coat");
    world.applyEquipment(progression);
    check(world.player.maxHp==325 && world.player.maxMp==265 && world.player.hp==182 && world.player.mp==146,
          "Repair synchronization restores the original deltas once without restoring current HP/MP");

    const auto directory=std::filesystem::path("cache/tests/equipment-resources-world")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    {
        CharacterStore store(directory);
        store.data["characters"][0]={{"name","ResourceRestore"},{"class","swordman"},{"level",2},{"weapon",0}};
        store.capture(0,world,progression); store.save();
    }
    {
        CharacterStore store(directory);
        Progression restoredProgression(catalog);
        World restored(pvf,assets,WorldRules::BetaFoundationV1);
        store.apply(0,restored,restoredProgression);
        check(restored.player.maxHp==325 && restored.player.maxMp==265 && restored.characterLevel==2 &&
              restoredProgression.equippedIndex(coatSlot)==index &&
              restored.statReport().at("equipment_resources").at("usable")==true,
              "Disk restore preflights owned equipment resources privately and publishes the same normal source maxima");
    }
    world.player.hp=0; world.player.dead=true; world.player.life=ActorLife::Dying;
    check(world.changeEquipment(progression,index,true).ok && world.player.hp==0 && world.player.dead &&
          world.player.life==ActorLife::Dying && world.player.maxHp==225,
          "Equipment resource recalculation cannot revive a dead actor or restart its lifecycle");
    World legacy(pvf,assets);
    legacy.applyEquipment(progression);
    check(legacy.player.maxHp==180 && legacy.player.maxMp==140 && legacy.statReport().at("equipment_resources").is_null(),
          "The legacy World does not silently opt into inferred equipment resource arithmetic");
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"equipped_trace",equippedReport},
        {"scope","Actual equip/unequip, growth, debug, durability, repair, disk restore and death consumers; complete equipment/passive/damage pipeline remains pending"}};
}
} // namespace dnf
