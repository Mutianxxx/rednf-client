#pragma once
#include "dnf/experimental_character.hpp"
#include "dnf/squirrel_world_bridge.hpp"

namespace dnf {
// The implementation is an explicitly inferred source-state adapter. The
// callback body is actual PVF code; dispatch from a manual experimental action
// is not proof of the original executable's state dispatcher or Buff stats.
inline constexpr const char *squirrelActionPolicy = "inferred-atmage-source-buff-callback-v1";
class SquirrelActionService {
    struct Impl;
    std::unique_ptr<Impl> impl_;
  public:
    SquirrelActionService(World &, Pvf &, Assets &, std::string staticIdentity);
    ~SquirrelActionService();
    SquirrelActionService(const SquirrelActionService &) = delete;
    SquirrelActionService &operator=(const SquirrelActionService &) = delete;
    // nullptr means no admitted callback is routed for this experimental
    // template. A routed but unsupported/faulting callback throws BEFORE cost.
    std::unique_ptr<PreparedExperimentalSkillAction> prepare(const ExperimentalSkillActionRequest &);
    void observe(std::optional<uint64_t> activeActionSequence) noexcept;
    void cancel(const std::string &reason) noexcept;
    Json diagnostics() const;
};
Json runSquirrelActionServiceTests(Pvf &, Assets &, const std::string &staticIdentity);
} // namespace dnf
