#pragma once
#include "resources.hpp"
#include <optional>

namespace dnf {
// Process/session management identity. generation changes on room, character
// or reload boundaries; it is deliberately not the disk commit generation.
struct DebugTarget {
    std::string contentId, characterUuid, runToken;
    uint64_t generation = 0;
    bool valid() const;
    bool operator==(const DebugTarget &other) const;
    bool operator!=(const DebugTarget &other) const { return !(*this == other); }
    Json json() const;
};

// These are temporary runtime overrides, never a progression/learning record.
// Stored selections may be retained with enabled=false; consumers must gate
// every override on enabled. A new process always starts disabled.
struct DebugOverrides {
    bool enabled = false;
    bool hpLock = false, mpLock = false, noCooldown = false, pauseAi = false;
    std::optional<int> level;
    // Exact authored MOB AI row name. Empty disables this F7-only test policy.
    std::string monsterAiDifficulty;
    Json json() const;
    bool operator==(const DebugOverrides &other) const;
    bool operator!=(const DebugOverrides &other) const { return !(*this == other); }
};

struct DebugContext {
    DebugTarget target;
    int normalLevel = 1;
    bool simulationPaused = false;
};

enum class DebugCommandKind {
    SetEnabled, SetHpLock, SetMpLock, SetNoCooldown, SetAiPaused,
    SetLevelOverride, ClearLevelOverride, Reset, SetSimulationPaused, SingleStep,
    SetMonsterAiDifficulty, SetTestIdentity, UnlockExecutableSkills
};
const char *debugCommandName(DebugCommandKind kind);
enum class DebugResultState { Accepted, Applied, Rejected };
const char *debugResultName(DebugResultState state);

struct DebugCommand {
    uint64_t requestId = 0;
    DebugTarget target;
    DebugCommandKind kind = DebugCommandKind::Reset;
    Json payload;
    Json json() const;
};
struct DebugResult {
    uint64_t requestId = 0;
    DebugResultState state = DebugResultState::Rejected;
    std::string reason;
    int64_t appliedTick = -1;
    Json actual = Json::object();
    Json json() const;
};
struct DebugSnapshot {
    DebugTarget target;
    DebugOverrides selected, effective;
    int normalLevel = 1;
    int64_t tick = 0;
    bool simulationPaused = false, pauseRequested = false;
    size_t pendingCount = 0;
    unsigned singleStepRequests = 0;
    uint64_t revision = 0;
    Json actual = Json::object();
    std::vector<DebugResult> recentResults;
    Json json() const;
};
} // namespace dnf
