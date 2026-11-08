#include "dnf/combat.hpp"
#include <stdexcept>
namespace dnf {
Json runNativeAttackTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), samples = Json::array();
    auto check = [&](bool ok, const std::string &message) {
        if (!ok) throw std::runtime_error("Native ordinary attack: " + message);
        checks.push_back(message);
    };
    auto step = [](World &world) { world.advance(16666667); };
    for (int weapon = 0; weapon < 4; ++weapon) for (int direction : {-1, 1}) {
        World world(pvf, assets);
        world.weapon = weapon; world.freezeAi = true;
        world.player.x = world.player.px = 500;
        world.player.y = world.player.py = 260;
        world.player.dir = direction;
        world.normalAttack(); world.normalAttack();
        int64_t first = -1, second = -1, ended = -1;
        for (int tick = 0; tick < 120; ++tick) {
            step(world);
            if (first < 0 && world.player.animation == "attack2") {
                first = world.nowMs();
                check(world.player.poseFrame == 0, "First native chain begins at pose0, weapon " + std::to_string(weapon));
                world.normalAttack();
            }
            if (second < 0 && world.player.animation == "attack3") {
                second = world.nowMs(); world.normalAttack(); // Third swing must not wrap into attack1.
            }
            if (second >= 0 && world.player.animation == "stay") { ended = world.nowMs(); break; }
        }
        check(first == 250 && second == 450 && ended == 1000,
              "Both-facing three-swing queue uses native frame5/4 (250/200ms source at current 100% clock), weapon " + std::to_string(weapon));
        int transitions = 0;
        for (const auto &event : world.events) if (event.kind == "basic_chain") {
            check(event.source == transitions && event.target == transitions + 1 && event.value == (transitions == 0 ? 5 : 4),
                  "Native cancel table is zero-indexed and exhausts after the second transition");
            ++transitions;
        }
        check(transitions == 2, "Final swing cannot gain an invented third cancel threshold");
        samples.push_back({{"weapon", weapon}, {"direction", direction}, {"second_swing_ms", first},
                           {"third_swing_ms", second}, {"finished_ms", ended}});
    }
    {
        World world(pvf, assets); world.normalAttack();
        for (int tick = 0; tick < 25; ++tick) step(world);
        check(world.nowMs() == 416 && world.player.animation == "attack1", "Without queued input the native cancel window does not cut off recovery");
        world.normalAttack(); step(world);
        check(world.player.animation == "attack2" && world.player.poseFrame == 0,
              "A new attack after the threshold chains on the next eligible tick without waiting for ANI end");
    }
    {
        World world(pvf, assets); world.normalAttack();
        for (int tick = 0; tick < 36; ++tick) step(world);
        check(world.player.animation == "stay" && world.nowMs() == 600,
              "An unqueued first swing still plays its complete 600ms source animation");
    }
    {
        World world(pvf, assets); world.normalAttack(); world.normalAttack();
        for (int tick = 0; tick < 14; ++tick) step(world);
        check(world.player.animation == "attack1", "Queued first swing cannot chain before source frame5");
        world.player.hitStopTicks = 5;
        for (int tick = 0; tick < 5; ++tick) {
            step(world);
            check(world.player.animation == "attack1" && world.player.hitStopped,
                  "Local hit pause rejects next-swing transition and freezes the current cancel-frame clock");
        }
        step(world);
        check(world.player.animation == "attack2" && world.player.poseFrame == 0,
              "Queued native transition resumes at its threshold on the first unfrozen tick");
    }
    return {{"status", "pass"}, {"checks", checks}, {"check_count", checks.size()}, {"samples", samples},
        {"scope", "Default unadvanced Swordman source-frame chain and local pause; native +1A4 semantics, attack speed, skill cancels and other playable jobs remain pending"}};
}
} // namespace dnf
