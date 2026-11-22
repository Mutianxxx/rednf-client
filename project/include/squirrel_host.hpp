#pragma once
#include "dnf/content_profile.hpp"
#include "dnf/simulation.hpp"
#include <array>
#include <functional>
#include <memory>
#include <optional>
#include <thread>

namespace dnf::squirrel_stage {
inline constexpr const char *vmPolicyId="official3.1-int32-UTF16-float32-stringhash32-inferred-v1";
struct DecodedText {
    std::u16string text;
    // One original-byte boundary per UTF-16 code unit, plus final boundary.
    std::vector<uint64_t> byteOffsets;
};
class SourceServices {
  public:
    virtual ~SourceServices() = default;
    virtual DecodedText decodeCp936(const Bytes &) const = 0;
    virtual std::string digest(const Bytes &) const = 0;
};
// Platform adapter only; the host core contains no Windows API.
std::unique_ptr<SourceServices> windowsSourceServices();

struct SourceUnit { SourceRef source; Bytes original; };
struct Limits {
    uint64_t instructions = 100000, nativeCalls = 1024, callDepth = 64;
    uint64_t heapBytes = 8 * 1024 * 1024, heapBlocks = 65536;
    uint64_t sourceBytes = 1024 * 1024, lexicalTokens = 100000, sourceNesting = 64;
    uint64_t commands = 64;
};
struct Diagnostic {
    std::string code, message;
    SourceRef source;
    uint64_t line = 0, column = 0;
};
struct CallSite {
    std::string name, kind, classification;
    uint64_t byteOffset = 0, line = 1, column = 1;
};
struct Inspection {
    bool executable = false;
    std::vector<CallSite> calls;
    std::vector<Diagnostic> diagnostics;
};

struct SoundCommand {
    uint64_t instanceId = 0, actionId = 0, sequence = 0;
    EntityHandle owner;
    SourceRef scriptSource, soundSource;
    std::string tag;
};
struct PreparedSoundBatch { virtual ~PreparedSoundBatch() = default; };
// Read-only skill parameter queries behind sq_GetSkillLevel / sq_GetLevelData /
// sq_GetIntData / sq_GetCastTime / sq_GetBonusRateWithPassive. Every member is
// optional: an unset function means that capability is absent, so the token
// stays capability-rejected instead of silently returning a fabricated 0.
// Callers pass already-validated int32 arguments; a nullopt result means the
// source has no such cell, which the host surfaces as a script-visible null.
// Read-only view of the owning actor's current ANI clock. `frameStartMs` is the
// boundary of the frame the clock is currently in; a requested frame that is
// not the current one has no recovered timeline and stays nullopt.
struct ScriptAnimationSnapshot {
    int frame = -1;
    uint64_t elapsedMs = 0, frameStartMs = 0, frameSpanMs = 0;
};
struct ScriptWorldApi {
    std::function<int(int skill)> level;
    std::function<std::optional<double>(int skill,int column,int level)> levelData;
    std::function<std::optional<int>(int skill,int index)> intData;
    std::function<std::optional<int>(int skill,int level)> castTime;
    std::function<std::optional<double>(int skill,int state,int column,double ratio)> bonusRate;
    // The bridge may return the actor's published ANI clock; it never derives
    // a clock from video durations or other out-of-source timing.
    std::function<std::optional<ScriptAnimationSnapshot>(EntityHandle owner)> animation;
    // Current actor coordinates from the live World; scripts use these to
    // derive target ranges. They are never substituted with video estimates.
    std::function<std::optional<std::array<double,3>>(EntityHandle owner)> position;
    // A recorded animation-selection request. The bridge notes which source
    // animation id the script asked for; it does not claim a native state
    // transition or a recovered id-to-ANI mapping.
    std::function<bool(EntityHandle owner,int animationId)> setCurrentAnimation;
    bool any() const noexcept {
        return level||levelData||intData||castTime||bonusRate||animation||position||setCurrentAnimation;
    }
};
class Bridge {
  public:
    virtual ~Bridge() = default;
    // Default empty: existing bridges and test doubles keep their behaviour.
    virtual ScriptWorldApi scriptWorldApi() const { return {}; }
    virtual bool valid(EntityHandle) const noexcept = 0;
    virtual bool hasBuffSkillIndex() const noexcept = 0;
    virtual bool hasSoundConsumer() const noexcept = 0;
    virtual int buffSkillIndex(EntityHandle) const = 0;
    virtual std::optional<SourceRef> resolveSound(const std::string &, const SourceRef &) const = 0;
    // Prepare may throw/reject; it MUST leave externally visible state unchanged.
    // Validate every source receipt and handle generation again here.
    virtual std::unique_ptr<PreparedSoundBatch> prepare(const std::vector<SoundCommand> &) = 0;
    // Commit must publish the complete prepared batch by no-throw swap/move.
    virtual void commit(std::unique_ptr<PreparedSoundBatch>) noexcept = 0;
    // Called exactly once on fault/explicit close/destruction, before VM storage
    // is released. Must cancel owned pending work without throwing. It must not
    // resurrect stale handles or undo unrelated instances' committed events.
    virtual void cleanup(uint64_t instanceId, const std::string &reason) noexcept = 0;
};
struct Result {
    bool ok = false, closed = false, stackRestored = false, arenaReleased = false;
    Json value = nullptr;
    std::vector<Diagnostic> diagnostics;
    uint64_t instructions = 0, nativeCalls = 0, heapPeak = 0, liveHeap = 0;
    size_t stagedCommands = 0;
};

// Single simulation-thread instance. Only successful calls retain VM globals.
// Any failure quarantines the entire instance, clears pending commands, invokes
// cleanup once, and requires a NEW instance (no callback replay/implicit restore).
// Resource/closure/coroutine serialization is intentionally unsupported.
// close/destruction also belong to the owning simulation thread; the caller
// must serialize lifecycle changes. inspect performs no VM mutation.
class Instance {
    struct Impl;
    std::unique_ptr<Impl> impl_;
  public:
    Instance(const SourceServices &, Bridge &, uint64_t instanceId, Limits = {});
    ~Instance();
    Instance(const Instance &) = delete;
    Instance &operator=(const Instance &) = delete;
    Inspection inspect(const SourceUnit &) const;
    Result compileOnly(const SourceUnit &);
    Result load(const SourceUnit &); // Reject unknown calls before execute.
    Result invoke(const std::string &callback, EntityHandle owner,
                  uint64_t actionId, const std::vector<Json> &arguments = {});
    void close(const std::string &reason = "closed") noexcept;
    bool closed() const noexcept;
    uint64_t liveHeap() const noexcept;
};
} // namespace dnf::squirrel_stage
