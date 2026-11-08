#pragma once
#include "pending_rewards.hpp"
#include <cstdint>
#include <filesystem>
#include <functional>
#include <string>

namespace dnf {
enum class RewardDiagnosticResult { Written, Unchanged, Unavailable };
// Runtime report output has no authority over a CharacterStore checkpoint.
// Failed writes invalidate deduplication and are retried for unchanged input.
class RewardRecoveryReporter {
    std::filesystem::path path_;
    std::string lastSuccessful_;
    std::function<void(const std::string &)> fallback_;
    void fallback(const Json &, const char *) const noexcept;
  public:
    explicit RewardRecoveryReporter(std::filesystem::path path,
        std::function<void(const std::string &)> fallback = {});
    RewardDiagnosticResult publish(const Json &) noexcept;
};

// This is the actual application flow called by main; hooks retain main's
// scene/store ownership and are also usable by isolated production fixtures.
struct RewardRecoveryHooks {
    std::function<bool()> savePending;
    std::function<bool()> capture;
    std::function<bool()> persist;
    std::function<void()> afterPublish;
    std::function<void(const std::string &)> failure;
};
class RewardRecoveryFlow {
    PendingRewardService &service_;
    Progression &progress_;
    World &world_;
    RegionCatalog &catalog_;
    uint64_t retryAfter_ = 0;
    static void notify(const RewardRecoveryHooks &, const char *) noexcept;
  public:
    RewardRecoveryFlow(PendingRewardService &, Progression &, World &, RegionCatalog &);
    bool pump(const RewardRecoveryHooks &);
    // Returns whether an attempt was made, not whether that attempt succeeded.
    bool tryAutomaticRetry(uint64_t wallMs, bool enabled, const RewardRecoveryHooks &);
    void deferRetry(uint64_t wallMs) noexcept;
    uint64_t retryAfter() const noexcept { return retryAfter_; }
    bool resultsReady(bool pumpSucceeded, bool savePending, const RegionSession &);
    // Source preparation failure may exit after its captured intent is saved;
    // an uncaptured event or failed CharacterStore commit may not.
    bool allowControlledExit(bool autoRun, bool inGame, const RewardRecoveryHooks &);
};
} // namespace dnf
