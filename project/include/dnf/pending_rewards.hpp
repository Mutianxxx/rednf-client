#pragma once
#include "progression.hpp"
#include "session.hpp"

namespace dnf {
class CharacterStore;
// Application transaction coordinator, not native reward arithmetic. The JSON
// ledger is character/branch local; the event cursor is process local and never
// substitutes for a persistent kill identity.
class PendingRewardService {
    size_t eventCursor_ = 0;
    bool dirty_ = false, captureFailed_ = false;
    uint64_t durableGeneration_ = 0;
    Json checkpointWriter_ = Json();
    Json diagnostic_ = Json::object();
    void fail(const char *phase, const std::string &error);
  public:
    static constexpr const char *policy = "beta-basic-reward-intent-checkpoint-v1";
    // Only at a character boundary after the previous character was durably
    // saved. This does not clear the new character's persistent namespace.
    void characterBoundary(const World &);
    size_t eventCursor() const { return eventCursor_; }
    bool needsCheckpoint() const { return dirty_; }
    bool captureIncomplete() const { return captureFailed_; }
    void captureFailure(const std::string &error) { captureFailed_ = true; fail("capture-origin", error); }
    bool blocked(const Progression &) const;
    bool hasPending(const Progression &) const;
    const Json &diagnostic() const { return diagnostic_; }
    uint64_t durableGeneration() const { return durableGeneration_; }
    // Capture all kills and a same-frame nonempty boss clear privately, in
    // event order. A failure leaves both progression and this cursor unchanged.
    // originSession must be the current complete region capture (with objects).
    bool observe(Progression &, const World &, const RegionSession &, const Json &originSession);
    // Require a durable intent checkpoint before private source/RNG/reward
    // preparation. No live receipt, drop or random draw is published on failure.
    // On success callers must checkpoint the final snapshot before resuming.
    bool prepareAndPublish(Progression &, World &, RegionCatalog &);
    // Confirm an actual committed CharacterStore character. A failed disk
    // candidate, or an unrelated/stale generation, is not acknowledgement.
    bool acknowledgeCheckpoint(const Progression &, const World &, const CharacterStore &, int slot);
    // Different save directories have independent generation counters. A clean
    // explicit handover must prove the target's actual durable root matches
    // this world; old/unrelated candidate JSON is never a writer binding.
    bool switchCheckpointWriter(const Progression &, const World &, const CharacterStore &, int slot);
    bool releaseCheckpointWriter(const Progression &, const CharacterStore &, int slot);
    // Results must use the original receipt's room count after optional branch
    // rooms are cleared. A conflicting token is a diagnostic, never a reroll.
    bool clearReceipt(const Progression &, const RegionSession &);
};
} // namespace dnf
