#pragma once
#include "skill_data.hpp"

namespace dnf {
// Current source includes conditional one-key Z skills as well as the base
// default. This narrow selector uses source purchase metadata, never a job ID,
// filename or translated command explanation. Conditional variants remain
// intact and require their own controller qualification.
inline bool sourceBaseDefaultSkillCommand(const SkillSourceData &data,int growtype) {
    const auto command=data.values("[command]");
    const auto level=data.firstNumber("[required level]");
    if(data.definition.kind!=SkillSourceKind::Active||command.size()!=1||command[0]!="(SKILL)"||!level||*level!=1)return false;
    for(const auto &value:data.values("[skill fitness growtype]"))if(value.is_number_integer()&&value==growtype)return true;
    return false;
}
struct UserRequestedSkillFeedbackV1 {
    static constexpr const char *policy="user-requested-skill-failure-shake-v1";
    static constexpr const char *bufferPolicy="user-requested-source-default-z-after-owned-action-v1";
    static constexpr int durationMs=120, phaseMs=20;
    static constexpr double amplitudePixels=2;
};
// Presentation-only transient state. It is deliberately absent from saves,
// simulation checkpoints, action codecs and replay input queues.
struct SkillFailureFeedback {
    int64_t startedMs=-1;
    std::string reason;
    std::optional<SkillKey> skill;
    double offsetX(int64_t renderMs) const {
        if(startedMs<0||renderMs<startedMs)return 0;
        const auto age=uint64_t(renderMs)-uint64_t(startedMs);
        if(age>=UserRequestedSkillFeedbackV1::durationMs)return 0;
        return (age/UserRequestedSkillFeedbackV1::phaseMs)%2 ? -UserRequestedSkillFeedbackV1::amplitudePixels : UserRequestedSkillFeedbackV1::amplitudePixels;
    }
    Json json() const {
        return {{"policy",UserRequestedSkillFeedbackV1::policy},{"classification","user_requested_presentation_inference"},
            {"started_ms",startedMs},{"reason",reason},{"skill",skill?skill->json():Json()},
            {"amplitude_pixels",UserRequestedSkillFeedbackV1::amplitudePixels},{"duration_ms",UserRequestedSkillFeedbackV1::durationMs},
            {"world_coordinates_changed",false},{"persistent",false}};
    }
};
} // namespace dnf
