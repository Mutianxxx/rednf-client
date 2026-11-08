#include "dnf/combat.hpp"
#include "dnf/demo_settings.hpp"
#include "dnf/session.hpp"
#include "dnf/storage.hpp"
#include <chrono>
#include <set>
#include <stdexcept>
namespace dnf {
Json runUserFeedbackTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool ok, const char *message) {
        if (!ok) throw std::runtime_error(std::string("User feedback: ") + message);
        checks.push_back(message);
    };
    const auto defaults = DemoBalance::fromJson(Json());
    check(defaults.monsterHp(false) == 130 && defaults.monsterHp(true) == 720,
          "Default requested 2x/3x increases old demo 65/240 HP without modifying MOB data");
    const auto malformed = DemoBalance::fromJson({{"normal_hp_multiplier", uint64_t(-1)}, {"boss_hp_multiplier", "5"}});
    check(malformed.normalHpMultiplier == 2 && malformed.bossHpMultiplier == 3,
          "Malformed and overflowing preferences retain independent safe defaults");
    const auto volumes = AudioVolumes::fromJson({{"master", -1}, {"music", .4}, {"ambient", "quiet"}});
    check(volumes.master == 0 && volumes.music == .4 && volumes.effects == 1 && volumes.ambient == 1,
          "Volumes clamp valid numbers and preserve other groups when one setting is malformed");
    {
        RegionCatalog regions(pvf, assets);
        RegionSession session;
        DemoBalance preference{4, 7};
        session.begin(regions, 1, 92731, preference);
        preference = {10, 10};
        check(session.balance.normalHpMultiplier == 4 && session.balance.bossHpMultiplier == 7,
              "A new run takes a value copy of the HP profile; changing preferences cannot heal existing monsters");
        World world(pvf, assets);
        Actor monster; monster.id = 1; monster.hp = 17; monster.maxHp = session.balance.monsterHp(false);
        monster.monsterPath = "monster/goblin/goblin.mob";
        world.monsters.push_back(monster);
        auto saved = session.save(world, "dungeon");
        RegionSession restored;
        check(restored.load(saved, regions) && restored.balance.describe() == session.balance.describe(),
              "Save/reload retains the run HP multipliers independently from application settings");
        World other(pvf, assets);
        check(restored.restore(other) && other.monsters[0].hp == 17 && other.monsters[0].maxHp == 260,
              "Restoring a partly damaged room preserves actual HP and maximum HP exactly");
        saved.erase("demo_balance"); saved["version"] = 2;
        RegionSession legacy;
        check(legacy.load(saved, regions) && legacy.balance.monsterHp(false) == 65 && legacy.balance.monsterHp(true) == 240,
              "Pre-setting sessions retain historical HP for unvisited rooms as well");
    }
    {
        const auto directory = std::filesystem::path("reports/test-saves/identity") /
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
        CharacterStore store(directory);
        store.data["schema"] = 3;
        store.data["future_root"] = 27;
        store.data["characters"][0] = {{"name", "Identity"}, {"class", "swordman"},
            {"identity", {{"job_id", 0}, {"growtype", 0}, {"awakening", 0}, {"future", 91}}}};
        World world(pvf, assets); world.bindings[0] = -1;
        store.capture(0, world); store.save();
        store.close();
        CharacterStore restored(directory);
        World loaded(pvf, assets); restored.apply(0, loaded);
        check(restored.data["schema"] == 5 && restored.data["future_root"] == 27 &&
            restored.data["characters"][0]["identity"]["future"] == 91 && loaded.bindings[0] == -1 &&
            loaded.identity() == CharacterIdentity{},
            "Schema5 preserves unknown identity/root fields and explicitly unbound shortcut slots");
        loaded.player.x = 537;
        bool rejected = false;
        try { loaded.selectCharacter({5, 0, 0}); } catch (const std::exception &) { rejected = true; }
        check(rejected && loaded.player.x == 537 && loaded.identity() == CharacterIdentity{},
            "Unrestored controllers are rejected before changing state, rather than using a Swordman substitute");
        for (const auto &binding : std::vector<std::pair<std::string, std::string>>{
                 {"stay", "[waiting motion]"}, {"move", "[move motion]"}, {"dash", "[dash motion]"},
                 {"jump", "[jump motion]"}, {"dashattack", "[dashattack motion]"}}) {
            loaded.player.animation = binding.first;
            check(loaded.actorAni() == loaded.characterSource().motion(binding.second),
                "Body motion uses the exact registered CHR tag binding");
        }
    }
    {
        World world(pvf, assets); world.freezeAi = true;
        world.player.x = 400; world.player.poseFrame = 9; // Interrupted combat pose.
        world.enqueue({0, 1, true}); world.advance(16666667);
        world.enqueue({world.nowMs() * 1000000, 1, false}); world.advance(16666667);
        world.enqueue({world.nowMs() * 1000000, 1, true}); world.advance(16666667);
        check(world.player.animation == "dash" && world.player.poseFrame == -1,
              "Entering a run releases any stale combat frame override");
        std::set<size_t> frames;
        const auto animation = assets.animation(world.actorAni());
        for (int i = 0; i < 40; ++i) {
            frames.insert(animation->frameAt(world.nowMs() - world.player.animStart, true));
            world.advance(16666667);
        }
        check(frames.size() > 1 && world.player.animation == "dash" && world.player.poseFrame == -1,
              "Held running advances multiple authored animation frames without repeated resets");
        world.player.poseFrame = 7;
        world.enqueue({world.nowMs() * 1000000, 5, true}); world.advance(16666667);
        check(world.player.z > 0 && world.player.poseFrame == -1,
              "Jumping from movement releases a prior explicit frame too");
    }
    {
        World world(pvf, assets); world.freezeAi = true;
        const int mp = world.player.mp;
        world.enqueue({0, 20, true}); world.advance(16666667);
        check(world.activeSkill() == 0 && world.events.front().tick == 1 && world.player.mp == mp - world.skills[0].mp,
              "An eligible shortcut starts on its first simulation tick and consumes MP exactly once");
        const int paid = world.player.mp;
        world.enqueue({world.nowMs() * 1000000, 20, true}); world.advance(16666667);
        check(world.player.mp == paid, "Repeated input cannot consume the active skill transaction twice");
    }
    {
        World world(pvf, assets); world.freezeAi = true;
        world.player.animation = "dashattack"; world.player.animStart = world.nowMs();
        const int mp = world.player.mp;
        world.normalAttack();
        check(world.activeSkill() < 0 && world.player.mp == mp,
              "Dash follow-up cannot start or spend MP before the source frame3 gate");
        const auto dash = assets.animation(world.actorAni());
        for (int tick = 0; tick < 120 && world.player.animation == "dashattack" &&
                 dash->frameAt(world.nowMs() - world.player.animStart, false) < 3; ++tick)
            world.advance(16666667);
        world.normalAttack();
        check(world.activeSkill() == 3 && world.player.mp == mp - world.skills[3].mp,
              "Dash follow-up uses the real SD frame gate and commits a single eligible skill transaction");
        for (int tick = 0; tick < 180 && world.activeSkill() >= 0; ++tick) {
            world.normalAttack(); world.advance(16666667);
        }
        check(world.activeSkill() < 0 && world.player.animation == "stay",
              "Repeated X during the active follow-up cannot restart it indefinitely");
    }
    {
        World world(pvf, assets); world.freezeAi = true;
        auto press = [&](int key, bool down) {
            world.enqueue({world.nowMs() * 1000000, key, down}); world.advance(16666667);
        };
        press(1, true); press(1, false); press(1, true);
        press(4, true); press(4, false);
        check(world.player.animation == "dashattack", "A fresh double tap followed by X enters the genuine dash attack state");
        for (int tick = 0; tick < 180 && world.player.animation == "dashattack"; ++tick) world.advance(16666667);
        world.advance(16666667);
        check(world.player.animation == "move", "Holding the old run direction after dash attack returns to walk without requalifying a run");
        press(4, true); press(4, false);
        check(world.player.animation == "attack1", "A later X starts ordinary attack instead of looping the stale dash attack");
        world.advance(1500000000);
        press(1, false); press(1, true);
        check(world.player.animation == "move", "One fresh direction press after combat does not reuse the earlier double-tap candidate");
        press(1, false); press(1, true);
        check(world.player.animation == "dash", "A new double-tap sequence can deliberately enter running again");
    }
    {
        const auto profile = readMonsterDeathProfile(pvf, assets, "monster/goblin/goblin.mob");
        check(profile.lifeMs == 3000 && monsterFragmentDisplayMs(profile) == 700,
              "Requested short visibility leaves original PTL lifetime unchanged");
        check(monsterFragmentOpacity(profile, 549) == 1 &&
              std::abs(monsterFragmentOpacity(profile, 625) - .5) < 1e-9 &&
              monsterFragmentOpacity(profile, 700) == 0,
              "Stones fade over the final 150ms and are fully gone at the visibility cutoff");
        World world(pvf, assets); world.freezeAi = true;
        Actor monster; monster.id = 1; monster.monsterPath = "monster/goblin/goblin.mob";
        monster.dead = true; monster.hp = 0; world.monsters.push_back(monster);
        world.advance(16666667); world.advance(950000000);
        check(world.monsters[0].life == ActorLife::Removed,
              "Shared stone-death actor is removed within one second rather than waiting the 3s PTL");
    }
    return {{"status", "pass"}, {"checks", checks}, {"check_count", checks.size()},
            {"scope", "User-requested HP/death tuning, save compatibility and local animation/input regression; original native motion parity is not claimed"}};
}
} // namespace dnf
