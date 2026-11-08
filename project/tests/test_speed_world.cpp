#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include <stdexcept>
namespace dnf {
Json runSpeedWorldTests(Pvf &pvf, Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool ok,const char *name){if(!ok)throw std::runtime_error(name);checks.push_back(name);};
    RegionCatalog catalog(pvf,assets); Progression progression(catalog);
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    world.applyEquipment(progression);
    const auto report=world.statReport();
    check(report.at("source_speeds").at("policy")=="inferred-flat-equipment-speed-v1",
          "Beta equipment synchronization publishes the named source speed policy");
    check(report.at("speed_consumers").at("clock_mode")=="ScaledLocalAge; ordinary/dash/jump attacks only; source delays unchanged",
          "Speed report declares the one local animation clock mode and pending skill consumers");
    world.combat=false; world.player.x=500; world.player.y=300;
    world.enqueue({world.simulationNanoseconds(),1,true});
    world.advance(1000000000);
    check(world.player.x>500,"Source move speed is consumed by fixed-tick locomotion rather than only stored in a trace");
    const auto moved=world.player.x;
    world.normalAttack(); world.advance(1000000000);
    check(world.player.animation=="stay"||world.activeSkill()<0,
          "Basic attack with source speed reaches a completed idle state through the local age clock");
    check(world.statReport().at("source_speeds").at("attack_per_mille")>0 &&
          world.statReport().at("source_speeds").at("move_per_mille")>0,
          "Attack and movement speed consumers retain positive source-derived rates");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"moved_x",moved}};
}
} // namespace dnf
