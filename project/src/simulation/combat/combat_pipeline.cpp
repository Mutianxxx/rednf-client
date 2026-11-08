#include "dnf/combat_pipeline.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {

const char *combatPipelineStageName(CombatPipelineStage stage) noexcept {
    switch (stage) {
    case CombatPipelineStage::Presentation: return "presentation";
    case CombatPipelineStage::ResponseSelection: return "response_selection";
    case CombatPipelineStage::AcceptancePreflight: return "acceptance_preflight";
    case CombatPipelineStage::Qualification: return "qualification";
    case CombatPipelineStage::Damage: return "damage";
    case CombatPipelineStage::HpCommit: return "hp_commit";
    case CombatPipelineStage::DeathTransition: return "death_transition";
    case CombatPipelineStage::HitStop: return "hit_stop";
    case CombatPipelineStage::Reaction: return "reaction";
    case CombatPipelineStage::StatusTransaction: return "status_transaction";
    case CombatPipelineStage::Status: return "status";
    case CombatPipelineStage::HitFeedback: return "hit_feedback";
    case CombatPipelineStage::Notification: return "notification";
    }
    return "unknown";
}
const char *combatPipelineOutcomeName(CombatPipelineOutcome outcome) noexcept {
    switch (outcome) {
    case CombatPipelineOutcome::Pending: return "pending";
    case CombatPipelineOutcome::Accepted: return "accepted";
    case CombatPipelineOutcome::TargetDead: return "target_dead";
    case CombatPipelineOutcome::QualificationRejected: return "qualification_rejected";
    case CombatPipelineOutcome::AcceptancePreflightRejected: return "acceptance_preflight_rejected";
    case CombatPipelineOutcome::DamageInputsUnavailable: return "damage_inputs_unavailable";
    case CombatPipelineOutcome::Missed: return "missed";
    }
    return "unknown";
}

Json CombatPipelineTrace::snapshot() const {
    Json order = Json::array();
    for (size_t i = 0; i < stageCount; ++i) order.push_back(combatPipelineStageName(stages[i]));
    return {
        {"policy", "40jp-structural-adapter-v2"},
        {"order", order},
        {"outcome", combatPipelineOutcomeName(outcome)},
        {"accepted", outcome == CombatPipelineOutcome::Accepted},
        {"lethal", lethal},
        {"requested_damage", requestedDamage},
        {"accepted_damage", acceptedDamage},
        {"native_numeric_parity", false},
        {"scope", "journal only; 1031 source formulas, callers, status and HP owners remain authoritative"},
        {"reference_order", "40jp structural reference only; live 1031 order is recorded at its actual consumers"}
    };
}

CombatPipelineTrace runCombatPipeline(const CombatPipelineInput &input) {
    if (input.targetHp < 0 || input.requestedDamage < 0)
        throw std::invalid_argument("Combat pipeline received negative HP or damage");

    CombatPipelineTrace trace;
    trace.requestedDamage = input.requestedDamage;
    trace.add(CombatPipelineStage::Presentation);
    trace.add(CombatPipelineStage::Qualification);
    if (!input.targetAlive) {
        trace.outcome = CombatPipelineOutcome::TargetDead;
        return trace;
    }
    if (!input.qualified) {
        trace.outcome = CombatPipelineOutcome::QualificationRejected;
        return trace;
    }
    if (!input.damageUsable) {
        trace.outcome = CombatPipelineOutcome::DamageInputsUnavailable;
        return trace;
    }
    if (input.missed) {
        trace.outcome = CombatPipelineOutcome::Missed;
        return trace;
    }

    trace.add(CombatPipelineStage::Damage);
    trace.acceptedDamage = std::min(input.targetHp, input.requestedDamage);
    trace.outcome = CombatPipelineOutcome::Accepted;
    trace.lethal = input.targetHp > 0 && trace.acceptedDamage >= input.targetHp;
    trace.add(CombatPipelineStage::HpCommit);
    // This is a structural reference fixture. The live 1031 adapter records
    // its actual hit-stop location and may differ in order.
    trace.add(CombatPipelineStage::HitStop);
    trace.add(CombatPipelineStage::Reaction);
    trace.add(CombatPipelineStage::Status);
    trace.add(CombatPipelineStage::Notification);
    return trace;
}

} // namespace dnf
