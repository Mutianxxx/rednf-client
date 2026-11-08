#pragma once
#include "experimental_character.hpp"
#include <memory>

namespace dnf {
class World;
struct Actor;
// Actual fixed-tick consumers of the source-driven female Gunner controller.
// Preparation owns a private copy of entities, source reads, effect instances
// and ID watermarks; a rejected batch cannot charge MP/CD or publish a visual.
class FemaleGunnerWorld {
    struct State;
    World &world_;
    std::unique_ptr<State> state_;
    explicit FemaleGunnerWorld(World &, std::unique_ptr<State>);
  public:
    explicit FemaleGunnerWorld(World &);
    ~FemaleGunnerWorld();
    std::unique_ptr<FemaleGunnerWorld> prepare(const std::vector<FemaleGunnerSkillCommand> &,
        const ExperimentalActorState &, size_t reservedBodyAttacks,
        const std::vector<ExperimentalAttackFrame> &bodyFrames = {}) const;
    void capture(Actor &,SkillKey);
    bool updateCapturedPose(Actor &);
    void publish(std::unique_ptr<FemaleGunnerWorld>) noexcept;
    void advance();
    void clear(const std::string &) noexcept;
    void applyActor(ExperimentalActorState &) const;
    bool invulnerable() const;
    bool neutralReactionReady() const noexcept;
    bool skillProjectionReady() const noexcept;
    std::unique_ptr<FemaleGunnerWorld> prepareNeutralDeath() const;
    void publishNeutralDeath(std::shared_ptr<FemaleGunnerWorld>) noexcept;
    void applyDefense(DamageRequest &) const;
    void applyAttack(DamageRequest &,std::optional<SkillKey>,const std::string &motion,const std::string &family = "") const;
    Json snapshot() const;
};
} // namespace dnf
