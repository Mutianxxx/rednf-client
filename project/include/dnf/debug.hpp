#pragma once
#include "debug_types.hpp"
#include "character.hpp"
#include <deque>
#include <map>
#include <functional>

namespace dnf {
class World;

// Single-threaded management service. SDL callbacks only enqueue requests.
// The application consumes them before a fixed tick or at the existing paused
// boundary, and owns isolation of the test save/progression/session branch.
// This service intentionally has no Progression or CharacterStore reference.
class DebugService {
    struct Receipt { Json command; DebugResult result; };
    size_t queueCapacity_, resultCapacity_;
    uint64_t issuedId_ = 0, seenId_ = 0;
    std::deque<DebugCommand> pending_;
    std::map<uint64_t, Receipt> receipts_;
    std::deque<uint64_t> completed_;
    DebugOverrides selected_;
    bool pauseRequested_ = false, bound_ = false;
    unsigned singleStepRequests_ = 0;
    Json preservedConfiguration_ = Json::object();
    DebugSnapshot snapshot_;
    // Source catalogs are immutable for a World/content binding. Recheck the
    // small typed controller support set so enabling experimental controllers
    // invalidates the UI rows even without changing the current identity.
    const World *identityWorld_ = nullptr;
    const CharacterCatalog *identityCatalog_ = nullptr;
    std::string identityContent_;
    std::vector<std::pair<CharacterIdentity,bool>> identitySupport_;
    bool resultsDirty_ = true;
    std::function<Json(World&, const DebugCommand&)> applicationCommandHandler_;
    void finish(const DebugCommand&, DebugResult);
    void bindTarget(const World&, const DebugContext&);
    void refreshActual(const World&, const DebugContext&);
    void publish(const World&, const DebugContext&);
  public:
    explicit DebugService(size_t queueCapacity = 128, size_t resultCapacity = 256);
    uint64_t nextRequestId();
    DebugResult submit(DebugCommand command);
    void applyAtBoundary(World&, const DebugContext&);
    void refresh(const World&, const DebugContext&);
    const DebugSnapshot &snapshot() const { return snapshot_; }
    bool pauseRequested() const { return pauseRequested_; }
    // The application must establish the isolated save/session branch before
    // consuming a pending enable. This query does not execute any command.
    bool hasEnableRequest(const DebugTarget&) const;
    // Only the paused application loop advances World for these requests.
    bool takeSingleStepRequest();
    // Only test identity/skill commands use this application-owned callback.
    // It must preflight and commit to the isolated test branch, then return an
    // actual receipt; an exception rejects the request. Other commands keep
    // using World's existing override transaction.
    void setApplicationCommandHandler(std::function<Json(World&, const DebugCommand&)> handler) {
        applicationCommandHandler_ = std::move(handler);
    }
    // Independent beta-settings schema. Unknown fields survive; enabled and
    // world pause are never restored from disk. Loading does not touch World.
    void loadConfiguration(const Json&);
    Json configuration() const;
};
} // namespace dnf
