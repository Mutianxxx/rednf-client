#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/storage.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
Json runAttributeWorldTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool ok, const char *message) {
        if (!ok) throw std::runtime_error(message);
        checks.push_back(message);
    };
    RegionCatalog catalog(pvf,assets);
    Progression progression(catalog);
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    world.applyEquipment(progression);
    check(world.player.maxHp == 180 && world.player.maxMp == 140,
        "Actual beta World consumes initial resource limits from current Swordman CHR");
    world.player.hp -= 37; world.player.mp -= 19;
    progression.addExperience(progression.experienceToNextLevel());
    check(progression.level() == 2,"Actual experience consumer reaches the next source level");
    world.applyEquipment(progression);
    check(world.characterLevel == 2 && world.player.maxHp == 225 && world.player.maxMp == 165 &&
          world.player.hp == 188 && world.player.mp == 146,
        "Normal level-up updates source limits and preserves absolute HP/MP loss");
    const auto unchanged = world.snapshot();
    world.applyEquipment(progression);
    check(world.player.hp == unchanged.at("hp") && world.player.mp == unchanged.at("mp") &&
          world.player.maxHp == unchanged.at("max_hp") && world.player.maxMp == unchanged.at("max_mp"),
        "Repeated equipment synchronization neither stacks growth nor heals resource loss");
    world.applyBaseAttributes(world.prepareBaseAttributes(world.identity(),1),AttributeRebuildReason::DebugLevelOverride);
    check(world.characterLevel == 1 && world.player.hp == 180 && world.player.mp == 140 && progression.level() == 2,
        "Debug level rebuild clamps current resources and leaves normal progression authority untouched");
    world.applyEquipment(progression);
    world.player.hp = 0; world.player.dead = true; world.player.life = ActorLife::Dying;
    progression.addExperience(progression.experienceToNextLevel());
    world.applyEquipment(progression);
    check(world.player.hp == 0 && world.player.dead && world.player.life == ActorLife::Dying && world.player.maxHp == 270,
        "Normal growth during death cannot revive or replace the death lifecycle");
    const auto death = world.snapshot();
    world.applyBaseAttributes(world.prepareBaseAttributes(world.identity(),4),AttributeRebuildReason::CharacterRestore);
    check(world.player.hp == 0 && world.player.mp <= world.player.maxMp && world.player.dead,
        "Even a full-resource restore reason cannot revive a dead actor implicitly");
    check(world.statReport().at("base_attributes").is_object() &&
          world.statReport().at("last_attribute_change").at("reason") == "character_restore",
        "The real World stat report exposes source attributes and committed resource-change trace");
    bool rejected = false;
    const auto beforeBadLevel = world.snapshot();
    try { world.applyBaseAttributes(world.prepareBaseAttributes(world.identity(),0),AttributeRebuildReason::DebugLevelOverride); }
    catch (const std::exception &) { rejected = true; }
    check(rejected && world.snapshot() == beforeBadLevel,"Unsupported growth level fails before mutating live World");

    const auto directory = std::filesystem::path("cache/tests/attribute-world") /
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    Json committed;
    {
        CharacterStore store(directory);
        store.data["characters"][0] = {{"name","GrowthRestore"},{"class","swordman"},{"level",progression.level()},{"weapon",0}};
        store.capture(0,world,progression); store.save();
        committed = store.data;
    }
    {
        CharacterStore store(directory);
        Progression restoredProgression(catalog);
        World restored(pvf,assets,WorldRules::BetaFoundationV1);
        store.apply(0,restored,restoredProgression);
        check(restored.characterLevel == restoredProgression.level() && restored.characterLevel == 3 &&
              restored.player.maxHp == 270 && restored.player.maxMp == 190 &&
              restored.statReport().at("rule_profile") == "beta-foundation-v1",
            "Disk restore rebuilds beta limits from normal saved level instead of saving a debug level override");
    }
    World legacy(pvf,assets);
    legacy.applyEquipment(progression);
    check(legacy.characterLevel == 3 && legacy.player.maxHp == 180 && legacy.player.maxMp == 140 &&
          legacy.statReport().at("base_attributes").is_null(),
        "Named legacy World retains historical limits rather than silently adopting beta growth");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},
        {"sample",unchanged},{"saved_progression",committed.at("characters")[0].at("progression")},
        {"scope","Source HP/MP maxima and real experience/equipment/restore consumers; full stats/damage/debug service remain incomplete"}};
}
} // namespace dnf
