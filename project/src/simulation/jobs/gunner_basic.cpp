#include "dnf/gunner_basic.hpp"
#include "dnf/particle_motion.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>
namespace dnf {
Json GunnerBasicSource::snapshot() const {
    return {{"source",settings.json()},{"subtype",subtype},{"integer",values},
        {"basis","1031 C06F10/BFE0E0; native BF8840/BF89E0/BF8B00 default base-identity path"},
        {"unverified",{"EQU GunInfo override vectors","native shared attackIndex input predicates","Reload-to-idle exit"}}};
}
Json GunnerBasicDeadlines::snapshot() const {
    return {{"shot_ms",shot},{"continuation_ms",continuation},{"recovery_ms",recovery},
        {"draw_rate_permille",drawRate},{"shoot_rate_permille",shootRate},
        {"classification","current1031-default-source-with-inferred-local-host-clock"}};
}
std::map<int,GunnerBasicSource> readGunnerBasicSources(Pvf &pvf) {
    const auto script=pvf.script("etc/gunnerdefaultguninfo.etc");std::map<int,GunnerBasicSource> out;int selected=-1;
    for(const auto &field:script.fields) {
        const auto tag=normalize(field.tag);
        if(tag=="[sub type]") {
            if(field.values.size()!=1||!field.values[0].is_number_integer())throw std::invalid_argument("Malformed source gun subtype");
            selected=field.values[0].get<int>();
        } else if(tag=="[integer]") {
            if(selected<0||field.values.size()!=10||out.count(selected))throw std::invalid_argument("Ambiguous/truncated source gun integer block");
            GunnerBasicSource source;source.settings=makeSourceRef(pvf,script.path);source.subtype=selected;
            for(size_t i=0;i<10;++i) {
                if(!field.values[i].is_number_integer()||field.values[i]<INT32_MIN||field.values[i]>INT32_MAX)
                    throw std::invalid_argument("Invalid source gun integer operand");
                source.values[i]=field.values[i].get<int32_t>();
            }
            if(source.values[0]<1||source.values[0]>128||source.values[3]<0||source.values[4]<0||source.values[5]<1||source.values[9]<1)
                throw std::invalid_argument("Unsupported source gun schedule values");
            out.emplace(selected,std::move(source));
        }
    }
    return out;
}
GunnerBasicDeadlines gunnerBasicDeadlines(const GunnerBasicSource &source,double attackSpeed,bool finalShot) {
    if(!std::isfinite(attackSpeed)||attackSpeed<1||attackSpeed>INT32_MAX)throw std::invalid_argument("Source gun attack speed requires positive int32");
    const auto speed=std::max(1,int32_t(std::trunc(attackSpeed)));
    const auto convert=[](double value){if(!std::isfinite(value)||value<0||value>INT32_MAX)throw std::overflow_error("Source gun schedule overflow");return int32_t(std::trunc(value));};
    GunnerBasicDeadlines out;
    out.drawRate=std::max(1,convert(double(source.values[9])*speed*.001));
    out.shootRate=std::max(1,convert(double(source.values[5])*speed*.001));
    out.shot=convert(source.values[3]*(1000.0/speed));
    const int64_t continuation=int64_t(out.shot)+convert(source.values[4]*(1000.0/speed));
    const int64_t recovery=continuation+(finalShot?100000/out.shootRate:std::max(250000/out.shootRate,125));
    if(recovery>INT32_MAX)throw std::overflow_error("Source gun recovery overflow");
    out.continuation=int32_t(continuation);out.recovery=int32_t(recovery);return out;
}
FemaleGunnerStageTiming gunnerBasicStageTiming(const Animation &animation,int phase,const GunnerBasicDeadlines &deadline) {
    if(phase<0||phase>4||animation.frames.empty())throw std::invalid_argument("Source gun phase ANI unavailable");
    FemaleGunnerStageTiming out;out.controlled=true;
    int64_t elapsed=0;const int rate=phase==0||phase==2?deadline.drawRate:deadline.shootRate;
    for(size_t i=0;i<animation.frames.size();++i) {
        const auto source=animation.frames[i].duration;out.sourceDelays.push_back(source);out.sourceDurationMs+=source;
        int64_t span=source?std::max<int64_t>(1,int64_t(source)*1000/rate):0;
        if(phase==1||phase==3) {
            if(i==0)span=deadline.shot;
            else if(i+1==animation.frames.size())span=std::max<int64_t>(1,int64_t(deadline.recovery)-elapsed);
        }
        if(span>INT32_MAX||elapsed>INT32_MAX-span)throw std::overflow_error("Source gun controller ANI deadline overflow");
        out.runtimeDelays.push_back(int32_t(span));elapsed+=span;
    }
    out.runtimeDurationMs=elapsed;
    out.evidence.push_back({{"policy","inferred-1031-ground-gunner-five-phase-host-v1"},{"phase",phase},{"deadlines",deadline.snapshot()},
        {"basis","Source held pose DELAY stays immutable; host scheduledShot releases frame0, native raise last-frame gate, separate recovery and shoot/reload rate"},
        {"unverified","Native protected ANI setter exact frame reset and Reload-to-idle; default weapon values only"}});
    return out;
}
Json GunnerBasicParticle::snapshot() const {
    return {{"source",source.json()},{"axis_velocity",axisVelocity},{"lifetime_ms",lifetimeMs},{"source_pitch_degrees",pitchDegrees},{"source_fields",fields},
        {"arithmetic","1031-E581E0-straight-keep-last-f32"},{"classification","inferred-host-source-centerline"},
        {"unverified",{"Source rotation cone random distribution and aim/origin modifiers","Native signed-axis projection and owner motion"}},
        {"policy","Source equal-range velocity axes; absent axes stay zero; source lifetime; explicit centerline host projection"}};
}
std::array<float,3> GunnerBasicParticle::displacement(int32_t elapsedMs) const {
    if(elapsedMs<0)throw std::invalid_argument("Negative source basic PTL age");
    std::array<float,3> out{};
    for(size_t axis=0;axis<3;++axis)out[axis]=particleStraightKeepLast(axisVelocity[axis],axisVelocity[axis],0,elapsedMs);
    return out;
}
GunnerBasicParticle readGunnerBasicParticle(Pvf &pvf,const Script &script) {
    GunnerBasicParticle out;out.source=makeSourceRef(pvf,script.path);out.fields=Json::array();
    int axis=-1;std::array<bool,3> seen{},declared{};
    for(const auto &field:script.fields) {
        out.fields.push_back({{"tag",field.tag},{"values",field.values},{"byte_offset",field.offset}});
        const auto tag=normalize(field.tag);
        if(tag=="[x axis]"||tag=="[y axis]"||tag=="[z axis]")axis=tag=="[x axis]"?0:tag=="[y axis]"?1:2;
        else if(tag=="[move type]") {
            if(axis<0||field.values!=Json::array({"[straight line]"}))throw std::invalid_argument("Unsupported basic PTL axis movement type");
            if(declared[size_t(axis)])throw std::invalid_argument("Repeated basic PTL axis movement type");
            declared[size_t(axis)]=true;
        } else if(tag=="[move variable 1]") {
            // These Up PTLs use equal endpoints. Do not reinterpret a random
            // range as acceleration endpoints when future source values differ.
            if(axis<0||!declared[size_t(axis)]||seen[size_t(axis)]||field.values.size()!=2||!field.values[0].is_number_integer()||
                field.values[0]!=field.values[1]||field.values[0]<INT32_MIN||field.values[0]>INT32_MAX)
                throw std::invalid_argument("Basic PTL needs equal int32 velocity range");
            out.axisVelocity[size_t(axis)]=field.values[0].get<int32_t>();seen[size_t(axis)]=true;
        } else if(tag=="[rotation angle]") {
            if(field.values.size()!=3||!field.values[1].is_number()||field.values[0]!=0||field.values[2]!=0)
                throw std::invalid_argument("Unsupported basic PTL rotation axes");
            out.pitchDegrees=field.values[1].get<double>();
        } else if(tag=="[life time]") {
            if(out.lifetimeMs||field.values.size()!=1||!field.values[0].is_number_integer()||field.values[0]<1||field.values[0]>INT32_MAX)
                throw std::invalid_argument("Basic PTL needs one positive int32 source lifetime");
            out.lifetimeMs=field.values[0].get<int32_t>();
        }
    }
    if(!out.lifetimeMs)throw std::invalid_argument("Basic PTL source lifetime unavailable");
    return out;
}
} // namespace dnf
