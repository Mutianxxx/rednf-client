#include "dnf/animation_events.hpp"
#include <stdexcept>
namespace dnf {
Json runAnimationEventTests(Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool pass, const char *name) {
        if (!pass) throw std::runtime_error(std::string("ANI event: ") + name);
        checks.push_back(name);
    };
    Animation animation; animation.path = "synthetic event state-machine contract";
    animation.frames.resize(7);
    animation.frames[1].properties["23"] = 1;
    animation.frames[3].properties["23"] = 2;
    animation.frames[4].properties["23"] = -1;
    animation.frames[6].properties["23"] = 65539;
    AnimationEventCursor events;
    events.update(animation, 2);
    check(events.lastFrame() == 2 && events.pending() == 1,
          "Skipped forward event remains pending across an empty current frame");
    check(events.consume(1) && events.pending() == 0xffff && !events.consume(1),
          "A caller accepts and clears the pending flag once");
    events.update(animation, 2);
    check(events.pending() == 0xffff, "Staying on the same source frame does not rearm a consumed event");
    events.reset(); events.update(animation, 5);
    check(events.pending() == 2, "Multiple skipped events use the last nonsentinel value in source order");
    events.reset(); events.update(animation, 6, true);
    check(events.lastFrame() == -1 && events.pending() == 0xffff,
          "Suppression leaves both cursor and pending event untouched");
    events.update(animation, 6);
    check(events.pending() == 3, "Runtime event retains the source int32 low word without changing source properties");
    events.consume(3); events.update(animation, 0);
    check(events.pending() == 0xffff && events.lastFrame() == 0,
          "Backward frame change inspects its current frame without replaying the old tail");
    events.reset(); events.update(animation, 1);
    check(events.pending() == 1 && animation.frames[6].properties["23"] == 65539,
          "New playback resets event history and preserves immutable raw values");
    bool rejected = false;
    try { events.update(animation, 7); } catch (const std::exception &) { rejected = true; }
    check(rejected, "Out-of-source indices fail explicitly at the portable API boundary");
    const auto slash = assets.animation("character/swordman/effect/animation/gorecross/slash2.ani");
    events.reset();
    events.update(*slash, int(slash->frameAt(499, false)));
    check(!events.matches(1), "Current Slash2 source has no event1 before its authored event frame");
    events.update(*slash, int(slash->frameAt(500, false)));
    check(events.lastFrame() == 10 && events.consume(1),
          "Current skill64 index1 produces event1 at its own frame10, not body frame7");
    return {{"status", "pass"}, {"check_count", checks.size()}, {"checks", checks},
            {"scope", "Native bounded event-flag semantics and current source ANI; full engine scheduling/attack speed remain separate"}};
}
} // namespace dnf
