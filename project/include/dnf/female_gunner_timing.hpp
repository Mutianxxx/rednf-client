#pragma once
#include "female_gunner.hpp"

namespace dnf {
// Controller schedules are separate from immutable ANI bytes. Runtime delays
// retain one entry per authored frame, so collision/sound/ALS frame identities
// never become virtual frame numbers. Looping channel phases use a wall-time
// deadline; finite phases complete only after the cursor visits every frame.
struct FemaleGunnerStageTiming {
    std::vector<int32_t> sourceDelays, runtimeDelays;
    int64_t sourceDurationMs = 0, runtimeDurationMs = 0;
    bool controlled = false, repeatAnimation = false;
    int64_t completionAfterMs = 0;
    bool overridesCommandTiming = false;
    uint32_t count = 1, minimumCount = 1, maximumCount = 1;
    uint32_t accelerationPresses = 0, pressesForMaximum = 0;
    int64_t intervalMs = 0, commandLifetimeMs = 0;
    Json evidence = Json::array();
    Json snapshot() const;
};
// attackPresses counts distinct Attack DOWN edges during this skill, not held
// ticks or rendering frames. Default0 selects RandomShoot's authored minimum.
// Timing command operands are resolved even for its initial Wait stage.
FemaleGunnerStageTiming buildFemaleGunnerStageTiming(const FemaleGunnerSkillCommand &,
    const FemaleGunnerStage &, const Animation &, uint32_t attackPresses = 0);
void applyFemaleGunnerStageTiming(FemaleGunnerSkillCommand &, const FemaleGunnerStageTiming &);
// Paused/hit-stopped ticks must not increment elapsedMs. For looping channel
// phases the exact command deadline is authoritative even if ANI never ends.
// Finite schedules require animationEnded, independent of source total delay.
bool femaleGunnerStageTimingComplete(const FemaleGunnerStageTiming &, int64_t elapsedMs,
                                    bool animationEnded);
enum class FemaleGunnerChannelInputMode { None, HoldAttack, PressAttackToExtend, HoldReleaseKey };
// M3/13 and Gatling/12 keep their source ATTACK contracts. User explicitly
// requests36/107 to hold the actual initiating key; this separate mode is a
// user strategy, not a source claim that their SKL establishes ATTACK hold.
struct FemaleGunnerChannelContract {
    FemaleGunnerChannelInputMode mode = FemaleGunnerChannelInputMode::None;
    int64_t maximumMs = 0, initialMs = 0, pressWindowMs = 0;
    int64_t recoveryMinimumMs = 0, recoveryMaximumMs = 0;
    bool jumpStops = false;
    Json evidence = Json::array(), diagnostics = Json::array();
    Json snapshot() const;
};
struct FemaleGunnerChannelState {
    int64_t deadlineMs = 0;
    bool stopped = false;
    std::string reason;
};
FemaleGunnerChannelContract femaleGunnerChannelContract(const FemaleGunnerSkillCommand &);
FemaleGunnerChannelState beginFemaleGunnerChannel(const FemaleGunnerChannelContract &);
// elapsedMs is unpaused channel-phase time. attackPressed/jumpPressed are
// distinct DOWN edges; repeated OS KEYDOWN must not extend the deadline.
// The host must stop evaluating while paused and must discard this transient
// state on scene/death/character changes. A stopped state never resurrects.
void advanceFemaleGunnerChannel(const FemaleGunnerChannelContract &, FemaleGunnerChannelState &,
    int64_t elapsedMs, bool attackHeld, bool attackPressed, bool jumpPressed);
// M3 source describes duration-dependent recovery; static1..static0 bounds
// and the linear interpolation remain explicitly inferred, not a native formula.
int64_t femaleGunnerChannelRecoveryMs(const FemaleGunnerChannelContract &, int64_t elapsedMs);
// Clear is published in the same World transaction as the controller exit.
// It identifies one exact channel action; buffs and detached fired bullets
// owned by other skills/actions are preserved.
FemaleGunnerSkillCommand stopFemaleGunnerChannel(const FemaleGunnerSkillCommand &, const std::string &reason);
Json runFemaleGunnerTimingTests(Pvf &, Assets &);
} // namespace dnf
