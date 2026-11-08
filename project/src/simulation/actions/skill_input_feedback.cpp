#include "dnf/combat.hpp"

namespace dnf {
void World::clearSkillInputTransients() noexcept {
    player.sourceSkillCameraFeedback={};
    bufferedDefaultSkill_.reset();player.skillFailureFeedback.startedMs=-1;
    player.skillFailureFeedback.reason.clear();player.skillFailureFeedback.skill.reset();
}
void World::rejectSkillFeedback(const std::string &reason,std::optional<SkillKey> skill) {
    if(player.dead||player.life!=ActorLife::Alive){clearSkillInputTransients();return;}
    player.skillFailureFeedback={nowMs(),reason,skill};
    events.push_back({tick,"skill_rejected",reason,0,0,skill?skill->skillId:0});
}
bool World::ownsDefaultSkillBuffer() const {
    if(!bufferedDefaultSkill_||!bufferedDefaultSkill_->ownerAction)return false;
    return bufferedDefaultSkill_->basic ? active_<0&&basicAttacking()&&bufferedDefaultSkill_->ownerAction==objectAttackSerial_ :
        active_>=0&&bufferedDefaultSkill_->ownerAction==actionInstance_;
}
void World::finishPlayerAction() {
    const auto buffered=ownsDefaultSkillBuffer()?bufferedDefaultSkill_:std::nullopt;
    auto presentation=std::move(player.skillFailureFeedback);
    idle();player.skillFailureFeedback=std::move(presentation);if(player.z>0)player.animation="jump";
    if(!buffered)return;
    // Completion, rather than input admission, consumes the one-shot queue.
    // activate/requestSkill checks current MP/CD/learning/air/state again.
    for(size_t index=0;index<skills.size();++index)if(skills[index].identity()==buffered->skill) {
        events.push_back({tick,"skill_buffer_released",UserRequestedSkillFeedbackV1::bufferPolicy,0,0,buffered->skill.skillId});
        activate(int(index),true);return;
    }
    rejectSkillFeedback("buffered_skill_binding_unavailable",buffered->skill);
}
Json World::skillInputDiagnostics() const {
    Json buffered;
    if(bufferedDefaultSkill_)buffered={{"skill",bufferedDefaultSkill_->skill.json()},
        {"owner_action",bufferedDefaultSkill_->ownerAction},{"basic",bufferedDefaultSkill_->basic},{"owner_current",ownsDefaultSkillBuffer()}};
    return {{"policy",UserRequestedSkillFeedbackV1::bufferPolicy},{"classification","user_requested_inference"},
        {"buffered_default_skill",buffered},{"failure_feedback",player.skillFailureFeedback.json()},
        {"persistent",false},{"replay_after_restore",false}};
}
} // namespace dnf
