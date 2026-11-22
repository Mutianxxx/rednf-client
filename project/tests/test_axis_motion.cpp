#include "dnf/axis_motion.hpp"
#include "dnf/combat.hpp"
#include <cmath>
#include <stdexcept>

namespace dnf {
Json runAxisMotionTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), jumpSamples = Json::array();
    auto check = [&](bool passed, const char *description) {
        if (!passed) throw std::runtime_error(std::string("Axis motion: ") + description);
        checks.push_back(description);
    };
    auto near = [](double a, double b) { return std::abs(a - b) < 0.0001; };
    {
        AxisMotion m{100, 1000, -1};
        const float distance = advanceAxisMotion(m, 100);
        check(near(m.velocity, 200) && near(distance, 15) && m.acceleration == 1000,
            "Unbounded acceleration integrates the average of old and new velocity");
        AxisMotion mirror{-100, -1000, -1};
        check(near(advanceAxisMotion(mirror, 100), -distance) && near(mirror.velocity, -m.velocity),
            "Negative-axis acceleration mirrors displacement and velocity");
    }
    {
        AxisMotion m{100, 1000, 50};
        check(near(advanceAxisMotion(m, 100), 13.75) && near(m.velocity, 150) &&
            m.acceleration == 0 && m.accelerationRemainingMs == 0,
            "Mid-tick acceleration expiry integrates both the accelerating and terminal segments");
        check(near(advanceAxisMotion(m, 100), 15) && near(m.velocity, 150),
            "Expired acceleration keeps terminal velocity on later updates");
        AxisMotion split{100, 1000, 50};
        const double first = advanceAxisMotion(split, 25);
        const double second = advanceAxisMotion(split, 75);
        check(near(first + second, 13.75) && near(split.velocity, 150),
            "Splitting an update across the finite acceleration boundary preserves motion");
        AxisMotion exact{100, 1000, 100};
        check(near(advanceAxisMotion(exact, 100), 15) && exact.acceleration == 0 &&
            exact.accelerationRemainingMs == 0,
            "An acceleration deadline exactly at the tick end is cleared after integration");
        AxisMotion expired{100, 1000, 0};
        check(near(advanceAxisMotion(expired, 100), 10) && expired.acceleration == 0 && near(expired.velocity, 100),
            "An already expired stop timer cannot apply another acceleration impulse");
    }
    {
        AxisMotion m{30000, 1000, -1};
        check(advanceAxisMotion(m, 100) == 2000 && near(m.velocity, 30100),
            "Native per-tick displacement clamp does not clamp the updated velocity");
        AxisMotion mirror{-30000, -1000, -1};
        check(advanceAxisMotion(mirror, 100) == -2000, "Negative displacement uses the matching native clamp");
        AxisMotion still{0, 0, -1};
        check(advanceAxisMotion(still, 100) == 0 && still.velocity == 0, "Resting axes stay still");
        AxisMotion zero{100, 1000, 50};
        check(advanceAxisMotion(zero, 0) == 0 && zero.velocity == 100 && zero.accelerationRemainingMs == 50,
            "Zero elapsed time leaves velocity and the stop timer unchanged");
        AxisMotion deadline{100, 1000, 0};
        check(advanceAxisMotion(deadline, 0) == 0 && deadline.velocity == 100 && deadline.acceleration == 0,
            "Zero elapsed time still clears an already expired acceleration");
        bool rejected = false;
        try { advanceAxisMotion(zero, -1); } catch (const std::invalid_argument &) { rejected = true; }
        check(rejected && zero.velocity == 100, "Negative time is rejected by the portable API before mutation");
        AxisMotion wrapped{0, 2147483647, -1};
        check(std::abs(advanceAxisMotion(wrapped, 2) + .000002) < 1e-10 &&
            std::abs(wrapped.velocity + .002) < 1e-8,
            "Acceleration multiplication preserves the native low-i32 product before the float velocity update");
    }
    {
        World world(pvf, assets); world.freezeAi = true;
        world.enqueue({0, 5, true});
        double apex = 0;
        int airborneTicks = 0;
        bool integratedPositionsMatch = true, landed = false;
        for (int t = 1; t <= 60; ++t) {
            world.advance(16666667);
            const double seconds = world.nowMs() / 1000.0;
            const double expected = 1 + 430 * seconds - .5 * 980 * seconds * seconds;
            jumpSamples.push_back({{"ms", world.nowMs()}, {"height", world.player.z},
                {"velocity", world.player.vz}, {"analytical_height_before_landing", expected}});
            if (expected > 0) {
                integratedPositionsMatch &= std::abs(world.player.z - expected) < .001;
                ++airborneTicks;
            } else {
                landed = world.player.z == 0 && world.player.vz == 0;
                break;
            }
            apex = std::max(apex, world.player.z);
        }
        check(integratedPositionsMatch, "Every ordinary jump sample agrees with the time-scaled acceleration integral");
        check(landed, "Landing clamps height and velocity after the integrated ground crossing");
        check(apex > 95 && apex < 95.4 && airborneTicks > 50 && airborneTicks < 55,
            "Jump apex and air duration retain the declared demo launch/gravity calibration");
    }
    return {{"status", "pass"}, {"check_count", checks.size()}, {"checks", checks}, {"jump_samples", jumpSamples},
        {"native_evidence", "jump-physics/README.md; 8B1C40 average velocity, finite acceleration stop and +/-2000 clamp"},
        {"scope", "Portable arithmetic and existing demo vertical motion; source CHR parameter mapping, outer clock, collision and FPU bit parity remain open"}};
}
} // namespace dnf
