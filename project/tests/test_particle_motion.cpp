#include "dnf/particle_motion.hpp"
#include "dnf/resources.hpp"
#include <cmath>
#include <cstring>
#include <limits>
#include <stdexcept>

namespace dnf {
Json runParticleMotionTests(Pvf &pvf) {
    Json checks = Json::array(), samples = Json::array();
    auto check = [&](bool ok, const char *description) {
        if (!ok) throw std::runtime_error(std::string("Particle motion: ") + description);
        checks.push_back(description);
    };
    auto near = [](float a, double b) { return std::abs(double(a) - b) < .0001; };
    const auto ptl = pvf.script("character/swordman/particle/gorecross.ptl");
    const auto velocities = ptl.values("[move variable 1]");
    check(velocities == Json::array({400, 0}) && ptl.number("[changing term]") == 280 &&
        ptl.text("[move type]") == "[straight line]" && ptl.text("[changing type]") == "[keep last value]",
        "Analytical source fixture uses the current PVF 400-to-zero/280ms straight/keep-last descriptor");
    const int v0 = velocities[0].get<int>(), v1 = velocities[1].get<int>();
    const int times[] = {0, 70, 140, 210, 280, 560};
    const double distances[] = {0, 24.5, 42, 52.5, 56, 56};
    bool sourceSamplesMatch = true;
    for (int i = 0; i < 6; ++i) {
        const float distance = particleStraightKeepLast(v0, v1, 280, times[i]);
        sourceSamplesMatch &= near(distance, distances[i]);
        samples.push_back({{"ms", times[i]}, {"unmodified_displacement", distance}});
    }
    check(sourceSamplesMatch, "Unmodified source descriptor integrates to the analytical deceleration area and holds its endpoint");
    auto bits = [](float value) {
        uint32_t result;
        std::memcpy(&result, &value, sizeof result);
        return result;
    };
    check(bits(particleStraightKeepLast(400, 0, 280, 70)) == 0x41c40001u &&
        bits(particleStraightKeepLast(400, 0, 280, 140)) == 0x42280001u &&
        bits(particleStraightKeepLast(400, 0, 280, 210)) == 0x42520001u,
        "Fixed binary32 samples preserve every source operation boundary rather than a reassociated double formula");
    check(near(particleStraightKeepLast(400, 100, 200, 100), 32.5) &&
        near(particleStraightKeepLast(400, 100, 200, 200), 50) &&
        near(particleStraightKeepLast(400, 100, 200, 400), 70),
        "A nonzero terminal velocity continues after the changing term instead of stopping at its endpoint");
    check(near(particleStraightKeepLast(-400, -100, 200, 400), -70) &&
        near(particleStraightKeepLast(400, -400, 200, 100), 20) &&
        particleStraightKeepLast(400, -400, 200, 200) == 0 &&
        near(particleStraightKeepLast(400, -400, 200, 300), -40),
        "Signed velocities support reversed axes and crossing through zero");
    check(near(particleStraightKeepLast(400, 999, 0, 100), 40) &&
        particleStraightKeepLast(400, 999, 0, 0) == 0,
        "Zero term uses the original constant-speed start velocity and ignores the terminal operand");
    check(particleStraightKeepLast(2000000000, 0, 0, 2) == -294967.3125f,
        "Zero-term multiplication wraps as signed i32 before converting to float32");
    check(near(particleStraightKeepLast(16777217, -16777216, 2, 1), 8388.6083984375),
        "Nonzero-term operands convert separately to float32 before velocity arithmetic");
    check(std::isfinite(particleStraightKeepLast(std::numeric_limits<int32_t>::max(),
        std::numeric_limits<int32_t>::min(), 1, 1)),
        "Opposite i32 velocity extremes do not use overflowing signed addition/subtraction");
    bool rejectedTime = false, rejectedTerm = false;
    try { particleStraightKeepLast(400, 0, 280, -1); } catch (const std::invalid_argument &) { rejectedTime = true; }
    try { particleStraightKeepLast(400, 0, -1, 100); } catch (const std::invalid_argument &) { rejectedTerm = true; }
    check(rejectedTime && rejectedTerm, "Negative times are explicitly rejected as a portable boundary");
    return {{"status", "pass"}, {"check_count", checks.size()}, {"checks", checks}, {"samples", samples},
        {"contract", "particles/straight-keep-last.json"}, {"rounding_assumption", "Host default nearest-even; source MXCSR not dynamically captured"},
        {"runtime_integration", false},
        {"scope", "Pure unprojected axis arithmetic only; GoreCross final velocity modifiers, projection, lifetime and object removal remain unresolved"}};
}
} // namespace dnf
