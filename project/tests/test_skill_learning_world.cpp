#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include <stdexcept>

namespace dnf {
Json runSkillLearningWorldTests(Pvf &pvf, Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool okay,const char *name) {
        if (!okay) throw std::runtime_error(std::string("Learning World: ")+name);
        checks.push_back(name);
    };
    RegionCatalog catalog(pvf,assets);
    Progression progression(catalog); progression.initialize(4);
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    world.applyEquipment(progression);
    auto initialized=world.skillLearning().prepareInitialization(CharacterSkillState(world.identity()),4,
        SkillInitializationMode::NewCharacter,world.nowMs());
    check(initialized.ok,"Source initialization prepares a normal character ledger");
    world.publishSkillLedger(initialized.state);
    const auto index=[&](int id) { for(size_t i=0;i<world.skills.size();++i) if(world.skills[i].id==id) return int(i); throw std::runtime_error("Missing active fixture"); };
    check(world.skills[index(46)].level==1 && world.skills[index(5)].level==1 && world.skills[index(8)].level==0 &&
        world.skills[index(64)].level==0,"Active controller arrays project CHR grants without giving every skill level one");
    check(world.runtimeSkillPolicy(world.passives.back().identity()).passiveConsumerBound==false,
        "Light armor mastery remains blocked until its real attribute consumer exists");
    world.activate(index(8));
    check(world.activeSkill()<0,"Unlearned source skill cannot activate through the actual controller");
    auto quote=world.quoteSkillLearning({0,46},4);
    auto purchase=world.skillLearning().prepare(world.skillState(),4,world.runtimeSkillPolicy({0,46}),
        {"world-upper2",{0,46},quote.revision,2},world.nowMs());
    check(purchase.ok && world.skills[index(46)].level==1,"Preparing a normal purchase leaves runtime arrays untouched");
    world.publishSkillLedger(purchase.state);
    const auto normal=world.skillState().snapshot(world.nowMs());
    DebugOverrides overrides; overrides.enabled=true; overrides.level=1; overrides.noCooldown=true;
    world.applyDebugOverrides(overrides,4);
    world.activate(index(46));
    check(world.skills[index(46)].level==2 && world.activeSkill()<0 &&
        world.skillUseEligibility({0,46}).gate==SkillLearningGate::TemporaryLevelIneligible,
        "No cooldown cannot bypass a reduced effective character-level requirement");
    overrides.level=15; world.applyDebugOverrides(overrides,4);
    auto testQuote=world.quoteTestSkillLearning({0,8});
    check(testQuote.accepted(),"Higher test level opens a source-qualified test purchase");
    const SkillLearningRequest request{"test-world-triple",{0,8},testQuote.revision,testQuote.targetLevel};
    check(world.learnTestSkill(request).ok && world.skills[index(8)].level==1 &&
        world.skillState().snapshot(world.nowMs())==normal,"Test purchase updates the controller while preserving the entire normal ledger");
    const auto overlay=world.skillTestOverlay().snapshot();
    check(world.learnTestSkill(request).ok && world.skillTestOverlay().snapshot()==overlay,
        "Repeated test request does not purchase or spend twice");
    overrides={}; world.applyDebugOverrides(overrides,4);
    check(world.skills[index(8)].level==0 && world.skills[index(46)].level==2 &&
        world.skillState().snapshot(world.nowMs())==normal,"Disabling debug restores the normal skill projection and purchase history");
    overrides.enabled=true; overrides.level=15; world.applyDebugOverrides(overrides,4);
    check(world.skills[index(8)].level==1,"Reenabling debug recovers the isolated test overlay");
    world.resetTestSkillLearning();
    check(world.skills[index(8)].level==0 && world.skillTestOverlay().levels.empty(),
        "Explicit test reset removes only test purchases");
    world.applyDebugOverrides({},4);
    world.activate(index(46));
    check(world.activeSkill()>=0,"A qualified normally purchased skill reaches its actual controller");
    world.reset();
    check(world.skills[index(46)].level==2 && world.skillTestOverlay().levels.empty() && !world.debugOverrides().enabled,
        "World reset clears test overrides and retains normal learned levels");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},
        {"scope","Actual skill controller, independent test projection and effective-level use gates; no frontend"}};
}
} // namespace dnf
