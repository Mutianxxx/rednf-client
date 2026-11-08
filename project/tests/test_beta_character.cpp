#include "dnf/beta_character.hpp"
#include "dnf/beta_branch.hpp"
#include <chrono>
namespace dnf {
Json runBetaCharacterTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();const auto check=[&](bool ok,const char *name){if(!ok)throw std::runtime_error(name);checks.push_back(name);};
    const auto root=std::filesystem::path("reports/test-saves")/("beta-character-"+
        std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    CharacterStore normal(root/"normal",pvf.identity());
    normal.data["characters"][0]={{"uuid","12345678-1234-4234-8234-123456789abc"},{"name","测试"},
        {"identity",CharacterIdentity{}.json()},{"class","swordman"},{"level",4},{"weapon",0},{"skill_initialization","source-v1"}};
    normal.save();RegionCatalog regions(pvf,assets);Progression progress(regions);
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();normal.apply(0,world,progress);
    DebugOverrides options;options.enabled=true;options.level=85;world.applyDebugOverrides(options,progress.level());
    bool rejected=false;try{selectBetaTestCharacter(normal,0,world,progress,{5,0,0});}catch(...){rejected=true;}
    check(rejected&&world.identity()==CharacterIdentity{},"Normal writer rejects debug identity replacement before mutation");
    BetaSaveBranch branch;branch.fork(normal,root/"test",Json::object());
    const auto disk=readFile(root/"normal/characters.json");const auto memory=normal.data.dump();
    const auto swordLedger=world.skillState().snapshot(world.nowMs());
    const auto opened=unlockExecutableBetaSkills(world);
    check(!opened.at("opened").empty(),"High test level opens additional executable Swordman skills through isolated learning");
    check(world.skillState().snapshot(world.nowMs())==swordLedger,"Opening test skills preserves the entire normal learning ledger");
    const auto switched=selectBetaTestCharacter(branch.select(normal),0,world,progress,{5,0,0});
    check(world.identity()==CharacterIdentity{5,0,0}&&world.debugOverrides().enabled&&world.characterLevel==85,
        "Test profession switch restores source female Gunner identity, real equipment and effective test level");
    check(world.experimentalRuntime()&&world.characterAppearance().identity==world.identity()&&world.combatAttributes(),
        "Profession switch publishes a real own-job appearance and combat attribute consumer");
    const auto femaleLedger=world.skillState().snapshot(world.nowMs());const auto female=unlockExecutableBetaSkills(world);
    check(!female.at("opened").empty()&&world.experimentalRuntime()->configuration().binding({5,13}),
        "Female source controllers including M3 become configurable without changing the normal skill ledger");
    check(world.skillState().snapshot(world.nowMs())==femaleLedger,"Experimental source bindings do not grant normal SP purchases");
    selectBetaTestCharacter(branch.select(normal),0,world,progress,{});
    check(world.identity()==CharacterIdentity{}&&!world.experimentalRuntime(),"Switching back restores the Swordman controller and clears female transient state");
    check(readFile(root/"normal/characters.json")==disk&&normal.data.dump()==memory,
        "Repeated test identity and skill changes preserve normal disk and memory records byte for byte");
    world.combat=true;rejected=false;try{selectBetaTestCharacter(branch.select(normal),0,world,progress,{5,0,0});}catch(...){rejected=true;}
    check(rejected&&world.identity()==CharacterIdentity{},"Active combat rejects test profession switching");
    branch.close();normal.apply(0,world,progress);
    check(world.identity()==CharacterIdentity{}&&!world.debugOverrides().enabled&&world.characterLevel==4&&
        world.skillState().snapshot(world.nowMs())==swordLedger,"Returning to the normal writer restores its original identity, level and learning");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"female_opened",female.at("opened").size()},
        {"female_blocked",female.at("blocked")},{"swordman_opened",opened.at("opened")}};
}
}
