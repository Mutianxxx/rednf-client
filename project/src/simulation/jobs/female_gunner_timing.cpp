#include "dnf/female_gunner_timing.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
int64_t positiveMs(double value,const char *label) {
    if(!std::isfinite(value)||value<1||value>INT32_MAX)
        throw std::invalid_argument(std::string("Female Gunner controller time out of range: ")+label);
    return int64_t(std::llround(value));
}
std::optional<double> exact(const FemaleGunnerSkillCommand &c,const std::string &label) {
    for(const auto &p:c.parameters)if(p.value("label",std::string())==label) {
        if(!p.contains("value")||!p["value"].is_number()||!std::isfinite(p["value"].get<double>()))
            throw std::invalid_argument("Invalid female Gunner timing operand: "+label);
        return p["value"].get<double>();
    }
    return {};
}
double requiredStatic(const FemaleGunnerSkillCommand &c,size_t column) {
    const auto found=c.rawTables.find("static_data");
    if(found==c.rawTables.end()||!found->is_array()||column>=found->size()||!(*found)[column].is_number())
        throw std::invalid_argument("Missing female Gunner timing static operand");
    const auto value=(*found)[column].get<double>();
    if(!std::isfinite(value))throw std::invalid_argument("Nonfinite female Gunner timing static operand");
    return value;
}
uint32_t positiveCount(double value,const char *label) {
    if(!std::isfinite(value)||value<1||value>512||std::floor(value)!=value)
        throw std::invalid_argument(std::string("Female Gunner timing count out of range: ")+label);
    return uint32_t(value);
}
int64_t sum(const std::vector<int32_t> &delays) {
    int64_t total=0;
    for(const auto value:delays) {
        if(value<0)throw std::invalid_argument("Negative source/controller ANI delay");
        total+=value;
        if(total>INT32_MAX)throw std::invalid_argument("Female Gunner controller duration exceeds supported span");
    }
    return total;
}
std::vector<int32_t> removeControllerHolds(const std::vector<int32_t> &source) {
    std::vector<int32_t> shortDelays;
    for(const auto value:source)if(value>0&&value<10000)shortDelays.push_back(value);
    if(shortDelays.empty())throw std::invalid_argument("Controller-held ANI has no finite cadence evidence");
    std::sort(shortDelays.begin(),shortDelays.end());const auto typical=shortDelays[(shortDelays.size()-1)/2];
    auto result=source;int32_t previous=typical;
    for(auto &value:result) {
        if(value>=10000)value=previous;
        else if(value>0)previous=value;
    }
    return result;
}
// Integer apportionment preserves all positive authored frames and exact total
// milliseconds, with no zero-frame insertion and no rounding accumulation.
std::vector<int32_t> distribute(const std::vector<int32_t> &weights,int64_t total) {
    size_t positive=0;int64_t weightTotal=0;
    for(const auto value:weights)if(value>0){++positive;weightTotal+=value;}
    if(!positive||total<int64_t(positive)||total>INT32_MAX)
        throw std::invalid_argument("Female Gunner timeline cannot visit all source frames in its deadline");
    const auto remaining=total-int64_t(positive);int64_t previous=0,cumulative=0;
    std::vector<int32_t> result;result.reserve(weights.size());
    for(const auto value:weights) {
        if(value==0){result.push_back(0);continue;}
        cumulative+=value;const auto boundary=remaining*cumulative/weightTotal;
        result.push_back(int32_t(1+boundary-previous));previous=boundary;
    }
    return result;
}
bool animationStem(const Animation &a,const char *stem) {
    return normalize(std::filesystem::path(a.path).stem().string())==stem;
}
void record(FemaleGunnerStageTiming &out,const FemaleGunnerSkillCommand &c,const Animation &a,
            const char *policy,const char *basis) {
    out.evidence.push_back({{"policy",policy},{"classification","inferred-1031-controller-timeline"},
        {"skill_source",c.skillSource.json()},{"animation",a.path},{"basis",basis},
        {"native_setter_dispatch_verified",false},{"source_bytes_unchanged",true},
        {"source_delays_ms",out.sourceDelays},{"runtime_delays_ms",out.runtimeDelays}});
}
} // namespace
Json FemaleGunnerStageTiming::snapshot() const {
    return {{"source_delays_ms",sourceDelays},{"runtime_delays_ms",runtimeDelays},
        {"source_duration_ms",sourceDurationMs},{"runtime_duration_ms",runtimeDurationMs},
        {"controlled",controlled},{"repeat_animation",repeatAnimation},{"completion_after_ms",completionAfterMs},
        {"overrides_command_timing",overridesCommandTiming},{"count",count},{"minimum_count",minimumCount},
        {"maximum_count",maximumCount},{"acceleration_presses",accelerationPresses},{"presses_for_maximum",pressesForMaximum},
        {"interval_ms",intervalMs},{"command_lifetime_ms",commandLifetimeMs},{"evidence",evidence}};
}
FemaleGunnerStageTiming buildFemaleGunnerStageTiming(const FemaleGunnerSkillCommand &c,
    const FemaleGunnerStage &stage,const Animation &a,uint32_t attackPresses) {
    FemaleGunnerStageTiming out;out.count=c.count;out.intervalMs=c.intervalMs;out.commandLifetimeMs=c.lifetimeMs;
    for(const auto &frame:a.frames)out.sourceDelays.push_back(frame.duration);
    out.runtimeDelays=out.sourceDelays;out.sourceDurationMs=out.runtimeDurationMs=sum(out.sourceDelays);
    if(c.key.jobId!=5)return out;
    if((c.family=="bullet_headshot"||c.family=="bullet_launcher")&&
       normalize(stage.motionTag)=="[attack motion]"&&out.runtimeDelays.size()>1&&out.runtimeDelays.back()>=9999) {
        out.controlled=true;out.runtimeDelays.back()=0;out.runtimeDurationMs=sum(out.runtimeDelays);
        record(out,c,a,"inferred-female-gunner-named-basic-motion-exit-v1",
            "Explicit bullet skills borrow CHR attack motion; its final 9999+ms frame is a controller exit pose. Retain the source final frame with zero deadline, preserving frame identity without a ten-second action lock.");
    }
    if(c.family=="radial_multishot"&&c.key.skillId==9) {
        std::vector<double> counts;
        for(const auto &p:c.parameters)if(p.value("label",std::string())=="攻击次数")counts.push_back(p.at("value").get<double>());
        if(counts.size()!=2)throw std::invalid_argument("RandomShoot requires its exact minimum and maximum source counts");
        out.minimumCount=positiveCount(counts[0],"RandomShoot minimum");out.maximumCount=positiveCount(counts[1],"RandomShoot maximum");
        if(out.maximumCount<out.minimumCount)throw std::invalid_argument("RandomShoot count range is reversed");
        const auto baseGap=positiveMs(requiredStatic(c,0),"RandomShoot static0");
        out.pressesForMaximum=positiveCount(requiredStatic(c,1),"RandomShoot static1");
        const auto increase=requiredStatic(c,2);
        if(increase<0||increase>10000)throw std::invalid_argument("RandomShoot acceleration is outside supported range");
        out.accelerationPresses=std::min(attackPresses,out.pressesForMaximum);
        const double progress=double(out.accelerationPresses)/out.pressesForMaximum;
        out.count=out.minimumCount+uint32_t(uint64_t(out.maximumCount-out.minimumCount)*out.accelerationPresses/out.pressesForMaximum);
        out.intervalMs=positiveMs(std::ceil(baseGap/(1+increase*progress/100)),"RandomShoot accelerated gap");
        out.commandLifetimeMs=positiveMs(double(out.count)*out.intervalMs,"RandomShoot pulse deadline");
        out.overridesCommandTiming=true;
        if(animationStem(a,"randomshoot")) {
            out.controlled=true;out.runtimeDelays=distribute(removeControllerHolds(out.sourceDelays),out.commandLifetimeMs);
            out.runtimeDurationMs=sum(out.runtimeDelays);
        }
        record(out,c,a,"inferred-randomshoot-source-pulse-timeline-v1",
            "Current1031 SKL minimum/maximum counts and static0/1/2; matching KB11332 identifies interval/key-count/speed-increase. Linear key acceleration and full-frame timeline apportionment remain reconstruction; bleeding duration is not action duration.");
        return out;
    }
    // These families contain controller-owned waiting poses, not 60+ second
    // playback requests. Never apply this rule to unknown families or ordinary
    // basic animations merely because an authored frame has a large delay.
    if((c.family=="grab_ground_shoot"&&animationStem(a,"treadshoot"))||
       (c.family=="charged_ammo_shot"&&(animationStem(a,"chargebustershoot")||animationStem(a,"chargebustershootdown")))) {
        out.runtimeDelays=removeControllerHolds(out.sourceDelays);out.runtimeDurationMs=sum(out.runtimeDelays);
        out.controlled=out.runtimeDelays!=out.sourceDelays;
        if(c.family=="grab_ground_shoot") {
            out.count=positiveCount(c.count,"Punisher shot count");
            std::vector<int32_t> shortDelays=out.runtimeDelays;std::sort(shortDelays.begin(),shortDelays.end());
            out.intervalMs=c.intervalMs>0?c.intervalMs:shortDelays[(shortDelays.size()-1)/2];
            out.commandLifetimeMs=positiveMs(double(out.intervalMs)*out.count,"Punisher pulse deadline");
            out.runtimeDelays=distribute(out.runtimeDelays,out.commandLifetimeMs);out.runtimeDurationMs=sum(out.runtimeDelays);
            out.overridesCommandTiming=true;
        }
        record(out,c,a,"inferred-female-gunner-explicit-held-discharge-v1",
            "Only Punisher/ChargeBuster named controller phases replace 10000ms holds with surrounding finite source cadence; every authored frame remains visited. Punisher uses evaluated shot count and one shared entity/body deadline.");
    }
    if(stage.holdForCommandLifetime) {
        if(c.family=="ranged_guard"&&out.commandLifetimeMs<=0)out.commandLifetimeMs=out.sourceDurationMs;
        if(c.family=="channel_projectile") {
            if(const auto seconds=exact(c,"发射时间上限"))out.commandLifetimeMs=positiveMs(*seconds*1000,"Gatling duration");
            if(const auto rate=exact(c,"每秒发射数")) {
                out.intervalMs=positiveMs(std::floor(1000/ *rate),"Gatling interval");
                out.count=positiveCount(double(std::max<int64_t>(1,out.commandLifetimeMs/out.intervalMs)),"Gatling count");
            }
        } else if(c.family=="channel_flame") {
            if(const auto seconds=exact(c,"喷火持续时间"))out.commandLifetimeMs=positiveMs(*seconds*1000,"Flame duration");
            auto seconds=exact(c,"攻击间隔");if(!seconds)seconds=exact(c,"多段攻击间隔");
            if(seconds)out.intervalMs=positiveMs(*seconds*1000,"Flame interval");
            if(out.commandLifetimeMs>0&&out.intervalMs>0)
                out.count=positiveCount(double(std::max<int64_t>(1,out.commandLifetimeMs/out.intervalMs)),"Flame count");
        } else if(c.family=="awakening_g0") {
            if(const auto seconds=exact(c,"锁定限制时间"))out.commandLifetimeMs=positiveMs(*seconds*1000,"G0 lock duration");
        } else if(c.family=="awakening_particle_cannon") {
            if(const auto seconds=exact(c,"主炮持续时间"))out.commandLifetimeMs=positiveMs(*seconds*1000,"AncientTrigger duration");
            if(const auto count=exact(c,"主炮攻击次数"))out.count=positiveCount(*count,"AncientTrigger count");
            if(out.count&&out.commandLifetimeMs>0)out.intervalMs=positiveMs(std::max<int64_t>(1,out.commandLifetimeMs/out.count),"AncientTrigger interval");
        }
        if(out.commandLifetimeMs>0) {
            if(!out.runtimeDurationMs)throw std::invalid_argument("Channel phase has no positive source animation cycle");
            out.controlled=true;out.repeatAnimation=true;out.completionAfterMs=out.commandLifetimeMs;out.overridesCommandTiming=true;
            record(out,c,a,"inferred-female-gunner-source-channel-deadline-v1",
                "Authored phase repeats its source frames while the evaluated command lifetime advances in unpaused simulation milliseconds; exact lifetime ends the phase independently of ANI ended. No command is republished on visual loop boundaries.");
        }
    }
    return out;
}
void applyFemaleGunnerStageTiming(FemaleGunnerSkillCommand &c,const FemaleGunnerStageTiming &timing) {
    if(!timing.overridesCommandTiming)return;
    c.count=timing.count;c.intervalMs=timing.intervalMs;c.lifetimeMs=timing.commandLifetimeMs;
    // Replace the current receipt on retries/stage transitions. Original source
    // operands remain intact; timing evaluation never appends duplicate effects.
    c.rawTables["controller_timing"]=timing.snapshot();
}
bool femaleGunnerStageTimingComplete(const FemaleGunnerStageTiming &timing,int64_t elapsedMs,bool animationEnded) {
    if(elapsedMs<0)throw std::invalid_argument("Negative female Gunner phase elapsed time");
    if(timing.controlled&&timing.completionAfterMs>0)return elapsedMs>=timing.completionAfterMs;
    return animationEnded;
}
Json FemaleGunnerChannelContract::snapshot() const {
    const char *name=mode==FemaleGunnerChannelInputMode::HoldAttack?"hold_attack":
        mode==FemaleGunnerChannelInputMode::HoldReleaseKey?"hold_release_key":
        mode==FemaleGunnerChannelInputMode::PressAttackToExtend?"press_attack_to_extend":"none";
    return {{"mode",name},{"maximum_ms",maximumMs},{"initial_ms",initialMs},{"press_window_ms",pressWindowMs},
        {"jump_stops",jumpStops},{"recovery_minimum_ms",recoveryMinimumMs},{"recovery_maximum_ms",recoveryMaximumMs},
        {"evidence",evidence},{"diagnostics",diagnostics}};
}
FemaleGunnerChannelContract femaleGunnerChannelContract(const FemaleGunnerSkillCommand &command) {
    FemaleGunnerChannelContract out;
    if(command.key.jobId!=5)return out;
    if(command.key.skillId==13&&command.family=="channel_flame") {
        out.mode=FemaleGunnerChannelInputMode::HoldAttack;
        out.maximumMs=out.initialMs=positiveMs(double(command.lifetimeMs),"M3 channel maximum");
        out.recoveryMinimumMs=positiveMs(requiredStatic(command,1),"M3 inferred minimum recovery");
        out.recoveryMaximumMs=positiveMs(requiredStatic(command,0),"M3 inferred maximum recovery");
        if(out.recoveryMaximumMs<out.recoveryMinimumMs)throw std::invalid_argument("M3 recovery bounds are reversed");
        out.evidence.push_back({{"skill_source",command.skillSource.json()},{"classification","source_explain_contract"},
            {"basis","Current flamethrower.skl explicitly names ATTACK held, ATTACK released and maximum spray duration"},
            {"native_setter_verified",false},{"recovery_after_release","Source describes duration-dependent recovery but its compiled formula is not recovered"}});
        out.evidence.push_back({{"policy","inferred-m3-source-static-recovery-v1"},{"classification","inferred"},
            {"minimum_source_column",1},{"maximum_source_column",0},
            {"minimum_ms",out.recoveryMinimumMs},{"maximum_ms",out.recoveryMaximumMs},
            {"basis","Source explain requires duration-dependent recovery; current static0/1 are unnamed800/400. Interpret as bounds and interpolate actual spray elapsed/source maximum; KB leaves these columns unexplained"},
            {"native_formula_verified",false}});
    }else if(command.key.skillId==12&&command.family=="channel_projectile") {
        out.mode=FemaleGunnerChannelInputMode::PressAttackToExtend;out.jumpStops=true;
        out.maximumMs=positiveMs(double(command.lifetimeMs),"Gatling channel maximum");
        out.pressWindowMs=positiveMs(requiredStatic(command,1),"Gatling static1 repeat-input window");
        out.initialMs=std::min(out.maximumMs,out.pressWindowMs);
        out.evidence.push_back({{"skill_source",command.skillSource.json()},{"classification","mixed_source_and_inference"},
            {"source_fact","Current gatling.skl explicitly names repeated ATTACK presses, JUMP cancellation and maximum fire duration"},
            {"policy","inferred-gatling-static1-renewal-window-v1"},{"window_source_column",1},
            {"window_ms",out.pressWindowMs},{"native_setter_verified",false},
            {"inference","Static1 is an unnamed same-version 700ms operand. Use it as initial/renewal window; each distinct press renews to elapsed+window, capped by source maximum. Original dynamic comparison is pending"}});
    }else if(command.family=="channel_flame"&&(command.key.skillId==36||command.key.skillId==107)) {
        out.mode=FemaleGunnerChannelInputMode::HoldReleaseKey;
        out.maximumMs=out.initialMs=positiveMs(double(command.lifetimeMs),"User hold source phase bound");
        out.evidence.push_back({{"policy","user-requested-1031-focus-ice-release-key-v1"},{"classification","user_requested"},
            {"skill_source",command.skillSource.json()},{"native_setter_verified",false},
            {"source_fact","Current SKL explicitly permits movement during spraying; ATTACK hold/release is not established there"},
            {"input_contract","Hold the initiating physical skill key, including Space/slot/command; release ends damage and visuals atomically"},
            {"duration_limit","Retain existing finite source-level operand bound; its native column semantics remain inferred"}});
    }else if(command.family=="channel_flame") {
        out.diagnostics.push_back({{"code","channel_input_contract_unverified"},{"skill",command.key.json()},
            {"message","Current source establishes movement/interval but does not explicitly establish ATTACK hold/release; retain existing finite phase instead of copying M3 input behavior"}});
    }
    return out;
}
FemaleGunnerChannelState beginFemaleGunnerChannel(const FemaleGunnerChannelContract &contract) {
    if(contract.mode==FemaleGunnerChannelInputMode::None||contract.initialMs<=0||
       contract.maximumMs<contract.initialMs||contract.maximumMs>INT32_MAX)
        throw std::invalid_argument("Cannot begin an unsupported or malformed female Gunner input channel");
    return {contract.initialMs,false,{}};
}
void advanceFemaleGunnerChannel(const FemaleGunnerChannelContract &contract,FemaleGunnerChannelState &state,
    int64_t elapsedMs,bool attackHeld,bool attackPressed,bool jumpPressed) {
    if(elapsedMs<0||contract.mode==FemaleGunnerChannelInputMode::None||contract.maximumMs<=0||contract.maximumMs>INT32_MAX||
       state.deadlineMs<=0||state.deadlineMs>contract.maximumMs)
        throw std::invalid_argument("Invalid female Gunner channel state/time");
    if(state.stopped)return;
    const auto stop=[&](const char *reason){state.stopped=true;state.reason=reason;};
    if(elapsedMs>=contract.maximumMs){stop("source_maximum");return;}
    if(contract.jumpStops&&jumpPressed){stop("jump_pressed");return;}
    if(contract.mode==FemaleGunnerChannelInputMode::HoldAttack&&!attackHeld){stop("attack_released");return;}
    if(contract.mode==FemaleGunnerChannelInputMode::HoldReleaseKey&&!attackHeld){stop("release_key_released");return;}
    // A press at or after the old deadline cannot revive an expired channel.
    if(elapsedMs>=state.deadlineMs){stop("input_window_expired");return;}
    if(contract.mode==FemaleGunnerChannelInputMode::PressAttackToExtend&&attackPressed) {
        if(contract.pressWindowMs<=0||contract.pressWindowMs>INT32_MAX)
            throw std::invalid_argument("Invalid female Gunner repeat-input window");
        state.deadlineMs=std::max(state.deadlineMs,std::min(contract.maximumMs,elapsedMs+contract.pressWindowMs));
    }
}
int64_t femaleGunnerChannelRecoveryMs(const FemaleGunnerChannelContract &contract,int64_t elapsedMs) {
    if(elapsedMs<0||contract.mode==FemaleGunnerChannelInputMode::None||contract.maximumMs<=0||contract.maximumMs>INT32_MAX||
       contract.recoveryMinimumMs<0||contract.recoveryMaximumMs<contract.recoveryMinimumMs||contract.recoveryMaximumMs>INT32_MAX)
        throw std::invalid_argument("Invalid female Gunner channel recovery contract/time");
    const auto elapsed=std::min(elapsedMs,contract.maximumMs);
    return contract.recoveryMinimumMs+(contract.recoveryMaximumMs-contract.recoveryMinimumMs)*elapsed/contract.maximumMs;
}
FemaleGunnerSkillCommand stopFemaleGunnerChannel(const FemaleGunnerSkillCommand &command,const std::string &reason) {
    if(femaleGunnerChannelContract(command).mode==FemaleGunnerChannelInputMode::None||!command.actionSequence||reason.empty())
        throw std::invalid_argument("Channel stop requires a supported source skill, exact action and reason");
    auto out=command;out.kind=FemaleGunnerCommandKind::Clear;out.effectRole="stop_channel";out.preflightOnly=false;
    out.animationSource.reset();out.attackSource.reset();out.objectSource.reset();out.motionSource.reset();out.box.reset();
    out.count=0;out.lifetimeMs=out.intervalMs=out.releaseDelayMs=0;out.speed=out.range=0;out.followCaster=false;
    out.rawTables["channel_stop"]={{"reason",reason},{"action_sequence",command.actionSequence}};
    return out;
}
} // namespace dnf
