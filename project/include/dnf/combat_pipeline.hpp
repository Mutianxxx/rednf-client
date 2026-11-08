#pragma once

#include "simulation.hpp"
#include <array>
#include <cstddef>
#include <string>

namespace dnf {

// The 40JP source shows a single hit entry point with explicit presentation,
// damage, HP, reaction and notification boundaries.  This type is a journal,
// not a second damage implementation: World remains the owner of actor state,
// source formulas, status transactions and random streams.
enum class CombatPipelineStage {
    Presentation,
    ResponseSelection,
    AcceptancePreflight,
    Qualification,
    Damage,
    HpCommit,
    DeathTransition,
    HitStop,
    Reaction,
    StatusTransaction,
    Status,
    HitFeedback,
    Notification
};
enum class CombatPipelineOutcome {
    Pending,
    Accepted,
    TargetDead,
    QualificationRejected,
    AcceptancePreflightRejected,
    DamageInputsUnavailable,
    Missed
};

const char *combatPipelineStageName(CombatPipelineStage stage) noexcept;
const char *combatPipelineOutcomeName(CombatPipelineOutcome outcome) noexcept;

struct CombatPipelineTrace {
    std::array<CombatPipelineStage, 16> stages{};
    size_t stageCount = 0;
    CombatPipelineOutcome outcome = CombatPipelineOutcome::Pending;
    bool lethal = false;
    int requestedDamage = 0;
    int acceptedDamage = 0;

    void add(CombatPipelineStage stage) noexcept {
        if (stageCount < stages.size()) stages[stageCount++] = stage;
    }
    Json snapshot() const;
};

// Small deterministic fixture helper used by focused checks.  It applies the
// reference lifecycle order only to supplied values; it does not claim 40JP
// numeric parity and is never used to mutate a live World.
struct CombatPipelineInput {
    bool targetAlive = true;
    bool qualified = true;
    bool damageUsable = true;
    bool missed = false;
    int targetHp = 0;
    int requestedDamage = 0;
};

CombatPipelineTrace runCombatPipeline(const CombatPipelineInput &input);

} // namespace dnf
