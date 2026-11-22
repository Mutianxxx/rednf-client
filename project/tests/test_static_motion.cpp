#include "dnf/static_motion.hpp"
#include "dnf/resources.hpp"
#include <cmath>
#include <cstring>
#include <limits>
#include <stdexcept>

namespace dnf {
Json runStaticMotionTests() {
    Json checks = Json::array(), samples = Json::array();
    auto check = [&](bool pass, const char *description) {
        if (!pass) throw std::runtime_error(std::string("Static motion: ") + description);
        checks.push_back(description);
    };
    auto near = [](double a, double b, double epsilon = .0001) { return std::abs(a - b) < epsilon; };
    bool selectorsMatch = true;
    for (int direction = 0; direction <= 4; ++direction) {
        const int sign = direction == 0 || direction == 2 ? -1 : direction == 4 ? 0 : 1;
        const auto normal = staticAxisOperands(600, 1000, -10000, direction, false, 1000);
        const auto alternate = staticAxisOperands(600, 1000, -10000, direction, true, 1000);
        selectorsMatch &= normal.velocity == sign * 600 && normal.acceleration == sign * -10000 &&
                          alternate.velocity == sign * 1000 && alternate.acceleration == normal.acceleration;
    }
    check(selectorsMatch, "All native direction selectors and normal/alternate values preserve independent acceleration");
    {
        const auto scaled = staticAxisOperands(600, 1000, -1000, 0, false, 333);
        check(near(scaled.velocity, -199.8000030517578125) && scaled.acceleration == 333,
              "The 1000-based scale multiplies direction before both operands; acceleration truncates toward zero");
        const auto invalid = staticAxisOperands(600, 1000, -1000, -1, false, 1000);
        check(invalid.velocity == 0 && invalid.acceleration == 0,
              "Unknown direction selectors have zero factor instead of being treated as facing right");
        const auto overflow = staticAxisOperands(0, 0, std::numeric_limits<int32_t>::max(), 1, false, 1000);
        check(overflow.acceleration == std::numeric_limits<int32_t>::min(),
              "Native int32-to-float rounding and CVTTSS2SI indefinite result survive acceleration conversion");
        const auto ordered = staticAxisOperands(72218, 0, 0, 1, false, 5180);
        uint32_t bits = 0;
        std::memcpy(&bits, &ordered.velocity, sizeof bits);
        check(bits == 0x48b6a928u,
              "Native scale-first SSE order yields 374089.25 rather than the reassociated 374089.28125");
    }
    {
        AxisMotion checked{100, -1000, 37};
        applyStaticAxisOperands(checked, {100, -1000}, AxisWritePath::Checked, false);
        check(checked.accelerationRemainingMs == 37,
              "Repeated checked commands with the same acceleration retain the elapsed stop timer");
        applyStaticAxisOperands(checked, {100, -2000}, AxisWritePath::Checked, false);
        check(checked.acceleration == -2000 && checked.accelerationRemainingMs == -1,
              "A changed checked acceleration resets the stop duration before any optional recomputation");
        AxisMotion direct{100, -1000, 37};
        applyStaticAxisOperands(direct, {100, -1000}, AxisWritePath::Direct, false);
        check(direct.accelerationRemainingMs == -1,
              "The direct write path resets even an equal acceleration's duration");
        AxisMotion tolerant{100, 0, -1};
        const float adjacent = std::nextafter(100.0f, 101.0f);
        applyStaticAxisOperands(tolerant, {adjacent, 0}, AxisWritePath::Checked, false);
        check(tolerant.velocity == 100,
              "Checked velocity ignores the adjacent float inside the relative native tolerance");
        const float twoSteps = std::nextafter(adjacent, 101.0f);
        applyStaticAxisOperands(tolerant, {twoSteps, 0}, AxisWritePath::Checked, false);
        check(tolerant.velocity == twoSteps,
              "Checked velocity accepts a change outside that relative tolerance");
        AxisMotion tiny{0, 0, -1};
        applyStaticAxisOperands(tiny, {1e-20f, 0}, AxisWritePath::Checked, false);
        check(tiny.velocity == 1e-20f,
              "Zero velocity has no absolute deadzone that could suppress a small legal request");
    }
    {
        AxisMotion positive{1, -3, -1}, negative{-1, 3, -1};
        check(calculateAxisDecelerationDuration(positive) && calculateAxisDecelerationDuration(negative) &&
              positive.accelerationRemainingMs == 333 && negative.accelerationRemainingMs == 333,
              "Opposing signs calculate milliseconds with truncation symmetrically in both directions");
        AxisMotion ordered{55500.484375f, -149597, -1};
        check(calculateAxisDecelerationDuration(ordered) && ordered.accelerationRemainingMs == 370,
              "Multiplication before division preserves the native truncation boundary of 370 rather than 371ms");
        const float distance = advanceAxisMotion(positive, 500);
        check(positive.acceleration == 0 && positive.accelerationRemainingMs == 0 &&
              positive.velocity > .0009f && positive.velocity < .0011f && near(distance, .1668335),
              "A noninteger zero crossing leaves terminal residual velocity and integrates the rest of the tick");
        const float residual = positive.velocity;
        check(near(advanceAxisMotion(positive, 100), residual * .1, 1e-9) && positive.velocity == residual,
              "Later updates keep the residual; a stop duration is not a force-to-zero policy");
        AxisMotion accelerating{100, 1000, 23}, still{0, -1000, 17}, coasting{100, 0, 42};
        check(!calculateAxisDecelerationDuration(accelerating) && accelerating.accelerationRemainingMs == 23 &&
              !calculateAxisDecelerationDuration(still) && still.accelerationRemainingMs == 17 &&
              !calculateAxisDecelerationDuration(coasting) && coasting.accelerationRemainingMs == 42,
              "Equal signs and zero factors preserve an existing timer");
        AxisMotion underflow{std::numeric_limits<float>::denorm_min(), -1, 42};
        check(calculateAxisDecelerationDuration(underflow) && underflow.accelerationRemainingMs == 0,
              "A tiny opposite-sign normal-host product can produce an immediate integer deadline");
        AxisMotion oversize{1e20f, -1, 19};
        bool rejected = false;
        try { calculateAxisDecelerationDuration(oversize); } catch (const std::invalid_argument &) { rejected = true; }
        check(rejected && oversize.accelerationRemainingMs == 19,
              "Portable duration overflow is rejected without changing the old state");
        AxisMotion atomic{100, -1000, 19};
        rejected = false;
        try { applyStaticAxisOperands(atomic, {1e20f, -1}, AxisWritePath::Direct, true); }
        catch (const std::invalid_argument &) { rejected = true; }
        check(rejected && atomic.velocity == 100 && atomic.acceleration == -1000 && atomic.accelerationRemainingMs == 19,
              "An unsupported command cannot partially overwrite velocity or acceleration before rejection");
    }
    bool trajectoriesMatch = true;
    for (int sign : {-1, 1}) {
        AxisMotion motion;
        auto operands = staticAxisOperands(700, 1200, -10000, sign < 0 ? 0 : 1, false, 1000);
        applyStaticAxisOperands(motion, operands, AxisWritePath::Checked, true);
        double x = 0;
        for (int dt : {16, 17, 17, 16, 17, 17}) {
            x += advanceAxisMotion(motion, dt);
            samples.push_back({{"direction", sign}, {"dt", dt}, {"position", x},
                {"velocity", motion.velocity}, {"acceleration", motion.acceleration},
                {"remaining_ms", motion.accelerationRemainingMs}});
        }
        trajectoriesMatch &= near(x, sign * 24.5, .001) && motion.acceleration == 0 && motion.accelerationRemainingMs == 0;
    }
    check(trajectoriesMatch,
          "Command plus finite integration preserves both signed 700/-10000 arithmetic trajectories across 16/17ms ticks");
    return {{"status", "pass"}, {"check_count", checks.size()}, {"checks", checks}, {"samples", samples},
        {"native_evidence", "horizontal-motion/README.md; 8328A0, 8B13D0, 8B2660, 8B0600"},
        {"scope", "Bounded effective-operand arithmetic and axis storage only; no skill/actor/authority/collision/dynamic parity claim"},
        {"runtime_entity_connection", false}};
}
} // namespace dnf
