#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include <stdexcept>

namespace dnf {
namespace {
int addSourceItem(Progression &progression, int id) {
    const auto *definition = progression.item(id);
    if (!definition) throw std::runtime_error("Equipment transaction source fixture is absent");
    const int index = int(progression.state.at("inventory").size());
    const int uid = progression.state.at("next_uid").get<int>();
    progression.state["inventory"].push_back({{"uid",uid},{"id",id},{"count",1},{"durability",definition->durability}});
    progression.state["next_uid"] = uid + 1;
    return index;
}
Json equipmentAppearance(const CharacterAppearance &appearance) {
    Json parts = Json::object(), layers = Json::array(), bodies = Json::array();
    for (const auto &[slot,part] : appearance.parts)
        parts[slot] = {{"source",part.source.path},{"variation",part.variation},
            {"source_hash",sha256(part.source.rawBytes)}};
    for (const auto &layer : appearance.orderedLayers())
        layers.push_back({{"order",layer.order},{"slot",layer.slot},{"source",layer.sourcePath},
            {"name",layer.name},{"animation",layer.animationScript},{"directory",layer.animationDirectory},
            {"variation",layer.variation},{"offset",layer.sourceOffset}});
    for (const auto &body : appearance.bodyMotions)
        bodies.push_back({{"tag",body.resource.tag},{"path",body.resource.path},{"occurrence",body.occurrence}});
    return {{"identity",appearance.identity.json()},{"job",appearance.job},{"parts",parts},{"layers",layers},
        {"bodies",bodies},{"body_order",appearance.bodyOrder},{"issues",appearance.issues}};
}
Json gameplayState(const World &world) {
    auto snapshot = world.snapshot();
    snapshot["stats"].erase("last_equipment_change");
    return {{"world",snapshot},{"simulation",world.simulationCheckpoint()},
        {"ledger",world.skillState().snapshot(world.nowMs())},{"events",world.eventLog()},{"inputs",world.inputs()},
        {"appearance",equipmentAppearance(world.characterAppearance())},{"weapon",world.weapon},
        {"equipment_attack",world.equipmentAttack},{"equipment_defense",world.equipmentDefense}};
}
Json transientState(const World &world) {
    auto snapshot = world.snapshot();
    snapshot.erase("stats"); snapshot.erase("weapon");
    return {{"world",snapshot},{"simulation",world.simulationCheckpoint()},
        {"ledger",world.skillState().snapshot(world.nowMs())},{"events",world.eventLog()},{"inputs",world.inputs()}};
}
} // namespace

Json runEquipmentTransactionTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    const auto check = [&](bool okay, const char *name) {
        if (!okay) throw std::runtime_error(std::string("Equipment transaction: ") + name);
        checks.push_back(name);
    };
    RegionCatalog catalog(pvf,assets);
    Progression progression(catalog); progression.initialize(5);
    const int avatarIndex = addSourceItem(progression,39180);
    const int ironIndex = addSourceItem(progression,27001);
    const auto avatar = *progression.item(39180), iron = *progression.item(27001);
    const auto avatarBytes = pvf.read(avatar.path), ironBytes = pvf.read(iron.path);
    check(avatar.source.number("[usable period]") == 15 && iron.minimumLevel == 3 && iron.durability > 0,
        "Real source fixtures retain the limited-period avatar and level-three durable iron sword");
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    world.applyEquipment(progression);
    world.freezeAi = true;
    world.advance(500000000,8);
    world.activate(0);
    world.player.hp -= 37; world.player.mp -= 19;
    Actor target; target.id = 93; target.hp = 61; target.x = 900;
    world.monsters.push_back(target); world.synchronizeEntityHandles();
    world.enqueue({world.simulationNanoseconds() + 2000000000,27,true});
    world.randomStreams().stream(RandomDomain::Combat,29).next();
    check(world.activeSkill() >= 0 && world.pendingTicks() > 0 && !world.simulationCheckpoint()["inputs"]["pending"].empty(),
        "Failure fixture contains a live action, catch-up debt, queued input and a named random stream");
    Progression candidate(progression);
    check(candidate.equip(avatarIndex,world.characterSource()).ok,
        "Inventory-level equip accepts the real avatar so failure exercises source preflight after candidate preparation");
    const auto before = gameplayState(world), beforeProgression = progression.state;
    const auto rejected = world.changeEquipment(progression,avatarIndex);
    const auto rejection = world.statReport().at("last_equipment_change");
    check(!rejected && progression.state == beforeProgression && gameplayState(world) == before,
        "Rejected source qualification preserves inventory, appearance, HPMP, actions, actors, clocks, RNG, ledger and queued input");
    check(rejected.message.size() < 160 && rejected.message.find('{') == std::string::npos &&
        rejection.at("status") == "rejected" && rejection.at("phase") == "source_preflight" &&
        rejection.at("error").get<std::string>().find("unsupported_equipment_qualification") != std::string::npos,
        "UI receives a short failure while the stat report retains the detailed unsupported source qualification");
    const auto invalid = world.changeEquipment(progression,-1);
    const auto unworn = world.changeEquipment(progression,ironIndex,true);
    check(!invalid && !unworn && progression.state == beforeProgression && gameplayState(world) == before,
        "Invalid selection and unequipping an unworn item reject without publishing candidate state");

    const auto starterAppearance = equipmentAppearance(world.characterAppearance());
    const auto starterSpeeds = world.statReport().at("source_speeds");
    const auto transient = transientState(world);
    const int hp = world.player.hp, mp = world.player.mp;
    const auto equipped = world.changeEquipment(progression,ironIndex);
    const auto ironSpeeds = world.statReport().at("source_speeds");
    check(equipped.ok && progression.equippedIndex("[weapon]") == ironIndex &&
        world.equipmentAttack == iron.physicalAttack && world.equipmentAttack == progression.attackBonus() &&
        ironSpeeds.at("cast_per_mille") == 720 && ironSpeeds.at("attack_per_mille") == 850 &&
        ironSpeeds.at("equipment_sources")[0].at("provenance").at("package_identity") == pvf.identity(),
        "Successful transaction publishes the exact equipped UID, source attack and cast speed with package identity");
    check(equipmentAppearance(world.characterAppearance()) != starterAppearance && world.player.hp == hp && world.player.mp == mp &&
        transientState(world) == transient && world.statReport()["last_equipment_change"]["status"] == "applied",
        "Replacing a weapon changes source appearance without healing, canceling the action or touching simulation and skill state");
    const auto equippedProgression = progression.state;
    const auto equippedAppearance = equipmentAppearance(world.characterAppearance());
    check(world.changeEquipment(progression,ironIndex).ok && progression.state == equippedProgression &&
        world.statReport().at("source_speeds") == ironSpeeds && world.equipmentAttack == iron.physicalAttack,
        "Repeated replacement fully rebuilds equipment contributions without stacking or modifying ledger authority");
    progression.state["inventory"][ironIndex]["durability"] = 0;
    check(world.changeEquipment(progression,ironIndex).ok && world.equipmentAttack == 0 &&
        world.statReport()["source_speeds"]["cast_per_mille"] == 700 &&
        equipmentAppearance(world.characterAppearance()) == equippedAppearance,
        "Broken durable equipment loses attack and speed contributions while its real appearance and instance remain");
    progression.state["inventory"][ironIndex]["durability"] = iron.durability;
    check(world.changeEquipment(progression,ironIndex).ok && world.equipmentAttack == iron.physicalAttack &&
        world.statReport().at("source_speeds") == ironSpeeds,
        "Restored source durability reactivates exactly one equipment contribution");
    check(world.changeEquipment(progression,ironIndex,true).ok && progression.equippedIndex("[weapon]") == -1 &&
        world.equipmentAttack == 0 && world.statReport()["source_speeds"]["cast_per_mille"] == 700 &&
        equipmentAppearance(world.characterAppearance()) == starterAppearance,
        "Unequip commits inventory ownership and neutral source stats while restoring default CHR equipment appearance");
    check(world.changeEquipment(progression,0).ok && world.statReport().at("source_speeds") == starterSpeeds &&
        equipmentAppearance(world.characterAppearance()) == starterAppearance && transientState(world) == transient,
        "Re-equipping the original item restores the original sources without clearing active combat state");

    Progression qualification(catalog); qualification.initialize(2);
    const int qualifiedIron = addSourceItem(qualification,27001);
    World qualificationWorld(pvf,assets,WorldRules::BetaFoundationV1);
    qualificationWorld.applyEquipment(qualification);
    DebugOverrides overrides; overrides.enabled = true; overrides.level = 99;
    qualificationWorld.applyDebugOverrides(overrides,qualification.level());
    const auto levelTwoState = qualification.state, levelTwoWorld = gameplayState(qualificationWorld);
    const auto underlevel = qualificationWorld.changeEquipment(qualification,qualifiedIron);
    check(!underlevel && underlevel.message == "角色等级不足" && qualification.state == levelTwoState &&
        gameplayState(qualificationWorld) == levelTwoWorld,
        "A high effective debug level cannot authorize source equipment above the normal progression level");
    qualification.addExperience(qualification.experienceToNextLevel());
    check(qualification.level() == 3,"Normal source experience reaches the iron-sword qualification level");
    qualificationWorld.applyEquipment(qualification);
    overrides.level = 1;
    qualificationWorld.applyDebugOverrides(overrides,qualification.level());
    const auto levelThreeState = qualification.state;
    const auto normalSkillLedger = qualificationWorld.skillState().snapshot(qualificationWorld.nowMs());
    auto expected = levelThreeState;
    expected["equipped"]["[weapon]"] = qualification.state["inventory"][qualifiedIron]["uid"];
    check(qualificationWorld.changeEquipment(qualification,qualifiedIron).ok && qualification.state == expected &&
        qualificationWorld.characterLevel == 1 && qualification.level() == 3 &&
        qualificationWorld.statReport()["source_speeds"]["qualification_level"] == 3 &&
        qualificationWorld.skillState().snapshot(qualificationWorld.nowMs()) == normalSkillLedger,
        "A normally qualified item equips at a lower debug level without rewriting XP, normal level or learning ledger");
    check(pvf.read(avatar.path) == avatarBytes && pvf.read(iron.path) == ironBytes,
        "Equipment transactions leave original PVF member bytes unchanged");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},
        {"source_rejection",rejection},{"committed_speed",ironSpeeds},
        {"scope","Real World equip/unequip atomic source preflight, source speed/durability consumers and debug qualification isolation; full modifier and repair transactions remain separate"}};
}
} // namespace dnf
