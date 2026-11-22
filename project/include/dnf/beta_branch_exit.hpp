#pragma once
#include "debug.hpp"
#include <functional>

namespace dnf {
class BetaSaveBranch;
class CharacterStore;
class PendingRewardService;
class Progression;
struct BetaBranchExitResult {
    bool ok = false;
    std::string stage, error;
    uint64_t resetRequestId = 0;
    Json resetReceipt = Json::object();
    Json json() const;
};
// Application-owned leave operation. Old queued debug commands are rejected
// using the service's existing invalid-target rule; no application callback
// may run while leaving. Reset must have an Applied receipt and empty queue.
// The supplied persist is main's real capture/save/ack lambda. The actual
// writer is proved again after persist, before release and close. Any failure
// keeps the branch and its pending candidate available for the existing retry
// UI. This never clears progression, learning or the persistent reward ledger.
BetaBranchExitResult leaveBetaSaveBranch(BetaSaveBranch &, CharacterStore &normal,
    PendingRewardService &, Progression &, World &, DebugService &,
    DebugContext, uint64_t &debugGeneration, int slot,
    const std::function<bool()> &persist);
} // namespace dnf
