#include "dnf/beta_branch.hpp"
#include <chrono>
namespace dnf {
Json runBetaBranchTests() {
    Json checks=Json::array();
    const auto check=[&](bool ok,const char *name){if(!ok)throw std::runtime_error(name);checks.push_back(name);};
    const auto root=std::filesystem::path("reports/test-saves")/ ("beta-branch-"+
        std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    CharacterStore normal(root/"normal","branch-test-content");
    normal.data["normal_inventory"]={{"gold",300},{"unknown_future",Json::array({1,2,3})}};
    normal.data["normal_world"]={{"random_stream",17},{"pending",Json::array({"reward-event"})}};
    normal.save();
    BetaSaveBranch branch;
    check(!branch.active()&&&branch.select(normal)==&normal,"New process selects the normal writer with no test overrides");
    branch.fork(normal,root/"test",{{"run_id","isolated-test"}});
    const auto normalBytes=readFile(root/"normal/characters.json");
    const auto normalData=normal.data;
    auto &test=branch.select(normal);
    check(branch.active()&&&test!=&normal&&test.data.at("normal_inventory")==normalData.at("normal_inventory")&&
          test.data.at("normal_world")==normalData.at("normal_world"),"Test fork starts with the complete normal inventory, random and pending state");
    test.data["normal_inventory"]["gold"]=9999;
    test.data["normal_world"]["random_stream"]=456;
    test.data["normal_world"]["pending"]=Json::array();
    test.data["test_overrides"]={{"level",99},{"hp_lock",true}};
    test.save();
    check(readFile(root/"normal/characters.json")==normalBytes&&normal.data==normalData,
          "Test rewards, random progression, consumed events and level/HP selections cannot change the normal disk or memory checkpoint");
    branch.fork(normal,root/"ignored",Json::object());
    check(branch.directory()==root/"test"&&!std::filesystem::exists(root/"ignored"),
          "Turning test features on again retains the existing branch instead of recopying or merging state");
    branch.close();
    check(!branch.active()&&&branch.select(normal)==&normal&&readFile(root/"normal/characters.json")==normalBytes,
          "Returning to normal character selection releases the test writer and retains the exact normal checkpoint");
    CharacterStore reopened(root/"test","branch-test-content");
    check(reopened.data.at("normal_inventory").at("gold")==9999&&reopened.data.at("beta_branch").at("merge_into_normal")==false,
          "The durable test branch remains inspectable without importing test rewards into normal saves");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()}};
}
} // namespace dnf
