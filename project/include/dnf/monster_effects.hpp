#pragma once
#include <cmath>
#include "resources.hpp"
#include <limits>
#include <optional>
#include <utility>

namespace dnf {
// Rendering plans retain source paths, offsets, ordered values and diagnostics.
// An ACT plan executes only MOTION composition, never its behavior instructions.
struct MonsterTrack {
    std::shared_ptr<Animation> animation;
    double start = 0, end = 0, x = 0, y = 0;
    int layer = 0;
    bool hold = false;
    std::string role;
    // Child ANI LOOP is independent of the actor state's repetition policy.
    // end remains the finite attachment/remove boundary, not a loop duration.
    bool loop = false;
    // Each pair is a local layer and its stable source insertion order. Nested
    // children stay within their parent's composition; layer sums lose that.
    std::vector<std::pair<int, size_t>> drawOrder;
};
inline bool monsterTrackBefore(const MonsterTrack &a, const MonsterTrack &b) {
    const auto count = std::min(a.drawOrder.size(), b.drawOrder.size());
    for (size_t i = 0; i < count; ++i)
        if (a.drawOrder[i] != b.drawOrder[i]) return a.drawOrder[i] < b.drawOrder[i];
    if (a.drawOrder.size() == b.drawOrder.size()) return a.layer < b.layer;
    // A node draws after its negative children and before its other children.
    if (a.drawOrder.size() == count) return b.drawOrder[count].first >= 0;
    return a.drawOrder[count].first < 0;
}
struct MonsterMotion {
    std::string monster, state, entry, bindingTag, error;
    size_t bindingOffset = 0;
    bool configured = false;
    std::shared_ptr<Animation> base;
    std::vector<MonsterTrack> tracks;
    double duration = 0;
    Json references = Json::array(), issues = Json::array();
    bool valid() const { return base && !base->frames.empty() && error.empty(); }
};
std::shared_ptr<const MonsterMotion> compileMonsterMotion(Pvf &pvf, Assets &assets,
    const std::string &monster, const std::string &state);
std::shared_ptr<const MonsterMotion> compileMonsterAnimation(Pvf &pvf, Assets &assets,
    const std::string &animation, const std::string &state);
std::shared_ptr<const MonsterMotion> compileMonsterAnimationForMob(Pvf &pvf, Assets &assets,
    const std::string &monster, const std::string &animation, const std::string &state);
double monsterMotionTime(const MonsterMotion &motion, double elapsed, bool loop);
std::array<double, 4> monsterMotionBounds(Assets &assets, const MonsterMotion &motion,
    double elapsed, bool loop, int facing = 1);

// Source is the accepted attack's world ground-plane origin; height stays a
// separate axis. NaN permits old callers to use the player origin explicitly.
struct ImpactContext {
    double sourceX = std::numeric_limits<double>::quiet_NaN();
    double sourceY = std::numeric_limits<double>::quiet_NaN();
    double travelSpeed = 0;
};
struct DeathImpulse {
    double x = 1, y = 0, speedScale = 1;
    double attackSpeed = 0, damageFraction = 0, push = 0, lift = 0;
};
DeathImpulse monsterDeathImpulse(double dx, double dy, int fallbackFacing,
    double attackSpeed, int damage, int maxHp, double push, double lift);
struct MonsterDeathProfile {
    bool configured = false, valid = false, pieces = false, smoke = false, flash = false;
    int selector = 0, palette = 0, omit = 0, count = 0, lifeMs = 0;
    double gravity = 0, speed = 0;
    std::string image, pieceAnimation, flashAnimation, smokeAnimation;
    Json raw = Json::array(), issues = Json::array();
};
MonsterDeathProfile readMonsterDeathProfile(Pvf &pvf, Assets &assets, const std::string &monster);
// These lifecycle clocks are an explicit reconstruction from the supplied
// accepted visual demo. They are not native EXE timing claims.
constexpr int monsterDeathWhiteMs = 60;
constexpr int monsterDeathBurstMs = 220;
constexpr int monsterDeathFadeMs = 90;
// User-requested display tuning, separate from the immutable 3000ms source PTL.
// Flight integration keeps real age/velocity; only visibility is shortened.
constexpr int monsterFragmentDisplayCapMs = 700;
constexpr int monsterFragmentFadeMs = 150;
inline int monsterFragmentDisplayMs(const MonsterDeathProfile &profile) {
    return std::clamp(profile.lifeMs, 0, monsterFragmentDisplayCapMs);
}
inline double monsterFragmentOpacity(const MonsterDeathProfile &profile, double ageMs) {
    const int duration = monsterFragmentDisplayMs(profile);
    if (!std::isfinite(ageMs) || ageMs < 0 || duration <= 0 || ageMs >= duration) return 0;
    const int fade = std::min(monsterFragmentFadeMs, duration);
    return std::clamp((duration - ageMs) / fade, 0.0, 1.0);
}
struct MonsterFragment {
    double x = 0, y = 0, z = 0, vx = 0, vy = 0, vz = 0;
    double spin = 0, angle = 0, size = 1;
    int frame = 0;
};
struct MonsterFragmentPose { double x, y, z, angle; };
uint32_t monsterDeathSeed(const std::string &path, int instance, int64_t tick);
std::vector<MonsterFragment> monsterDeathFragments(uint32_t seed, const MonsterDeathProfile &profile,
    const std::array<double, 4> &bounds, double height, const DeathImpulse &impulse);
MonsterFragmentPose monsterFragmentPose(const MonsterFragment &fragment, double seconds, double gravity);
} // namespace dnf
