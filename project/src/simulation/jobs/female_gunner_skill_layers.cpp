#include "dnf/female_gunner_skill_layers.hpp"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <stdexcept>

namespace dnf {
namespace {
std::string stem(const std::string &path) {
    return normalize(std::filesystem::path(path).stem().string());
}
bool identicalDelays(const Animation &a,const Animation &b) {
    if(a.frames.size()!=b.frames.size())return false;
    for(size_t i=0;i<a.frames.size();++i)if(a.frames[i].duration!=b.frames[i].duration)return false;
    return true;
}
Json delays(const Animation &a) {
    Json out=Json::array();for(const auto &f:a.frames)out.push_back(f.duration);return out;
}
bool begins(const std::string &value,const std::string &prefix) {
    return value.rfind(prefix,0)==0;
}
}
Json SourceSkillVisualCue::snapshot() const {
    Json out={{"source",source.json()},{"body_path",bodyPath},{"relative_layer",layer},
        {"synchronized_to_body",synchronizedToBody},{"loop",loop},{"evidence",evidence},
        {"classification","source_bound_skill_visual_cue"},{"native_confirmed",false},
        {"trigger",trigger==SourceSkillVisualTrigger::AcceptedHit?"accepted_hit":"stage_layer"},
        {"scale",{{"policy",scalePolicy==SourceSkillVisualScalePolicy::HeldTargetWidth?"held_target_mob_width_inferred":"fixed"},
            {"x",scaleX},{"y",scaleY}}}};
    if(inheritBodyRate)out["inherit_body_rate_with_own_source_delays"]=true;
    if(offset!=std::array<double,3>{})out["actor_local_xyz"]=offset;
    if(!controllerSubstates.empty())out["controller_substates"]=controllerSubstates;
    if(controllerStyle>=0)out["controller_style"]=controllerStyle;
    return out;
}
bool sourceSkillVisualCueMatches(const SourceSkillVisualCue &cue,int substate,int style) noexcept {
    if(cue.trigger!=SourceSkillVisualTrigger::StageLayer)return false;
    if(!cue.controllerSubstates.empty()&&std::find(cue.controllerSubstates.begin(),cue.controllerSubstates.end(),substate)==cue.controllerSubstates.end())return false;
    return cue.controllerStyle<0||cue.controllerStyle==style;
}
double heldTargetWidthVisualScale(double width) noexcept {
    if(!std::isfinite(width))return 1;
    const double t=std::clamp((width-100.0)/150.0,0.0,1.0);
    return 1.0+2.0*t;
}
std::vector<FemaleGunnerSkillLayer> buildFemaleGunnerSkillLayers(Pvf &pvf,Assets &assets,
    const FemaleGunnerSkillDescriptor &descriptor,const std::string &bodyPath) {
    std::vector<FemaleGunnerSkillLayer> out;
    if(descriptor.key.jobId!=5||!descriptor.dedicatedRuntime)return out;
    const auto normalized=normalize(bodyPath),bodyStem=stem(normalized);
    // A source skill reference alone, or the presence of a preload dependency,
    // must never draw an unrelated clip during another CHR action.
    if(!begins(normalized,"character/gunner/atanimation/"))return out;
    const auto add=[&](const std::string &path,int layer,const std::string &bindingBasis,
                       const std::string &alias) {
        if(!pvf.has(path))throw std::invalid_argument("Missing current-PVF female Gunner skill layer: "+path);
        const auto body=assets.animation(normalized),clip=assets.animation(path);
        if(body->frames.empty()||clip->frames.empty())throw std::invalid_argument("Empty female Gunner body/layer ANI: "+path);
        FemaleGunnerSkillLayer value;value.source=makeSourceRef(pvf,path);value.bodyPath=normalized;
        value.layer=layer;value.synchronizedToBody=identicalDelays(*body,*clip);
        value.loop=clip->globals.value("0",false);
        value.evidence.push_back({{"policy","inferred-1031-female-gunner-skill-appearance-v1"},
            {"classification","inferred"},{"native_confirmed",false},{"skill_source",descriptor.source.json()},
            {"body_source",makeSourceRef(pvf,normalized).json()},{"layer_source",value.source.json()},
            {"binding_basis",bindingBasis},{"source_name_alias",alias},
            {"body_delays_ms",delays(*body)},{"layer_delays_ms",delays(*clip)},
            {"source_loop",value.loop},{"synchronized_to_body",value.synchronizedToBody},
            {"coordinate_policy","Use the source ANI frame XY, image crop, RGBA, blend and transform without foot-anchor compensation"},
            {"order_policy","a/back or upper blade behind the actor; b/body/light/lower blade in front; controller layer order unverified"},
            {"unverified_conditions","Compiled1031 controller attachment/spawn calls and relative layer order require original dynamic comparison; this is not an authored CHR/ALS reference"}});
        out.push_back(std::move(value));
    };
    if(descriptor.family=="radial_multishot"&&bodyStem==descriptor.stem) {
        const auto body=assets.animation(normalized);
        const std::string prefix="character/gunner/effect/animation/shooteffect/";
        // The current four authored body/blade tracks share every delay and
        // frame index with the actual RandomShoot body. Select by that current
        // source relationship, not a list of IMG names or every preloaded ANI.
        for(const auto &path:pvf.paths(prefix,".ani")) {
            if(!begins(stem(path),"at"+bodyStem))continue;
            const auto clip=assets.animation(path);
            if(!identicalDelays(*body,*clip))continue;
            int layer=10;
            // The source image name supplies a layer hint; ANI positions are
            // still read verbatim and are never recentered by these hints.
            for(const auto &f:clip->frames)if(normalize(f.image).find("blade_up")!=std::string::npos){layer=-10;break;}
            add(path,layer,"Selected SKL stem + actual CHR body stem + all authored frame delays equal","");
        }
        return out;
    }
    if(!begins(bodyStem,"subweapon"))return out;
    const bool weaponFamily=descriptor.family=="channel_projectile"||descriptor.family=="channel_flame"||
        descriptor.family=="heavy_projectile"||descriptor.family=="grab_aerial_gatling"||descriptor.family=="cluster_bomb";
    if(!weaponFamily)return out;
    auto folder=descriptor.stem,stageStem=bodyStem.substr(std::string("subweapon").size());
    std::string alias;
    // These are version-scoped name/controller aliases. They carry no timing,
    // coordinate, texture list, hitbox or damage constants.
    if(folder=="laserrifle"){folder="laserrifleeffect";alias="laserrifle -> laserrifleeffect";}
    else if(folder=="aerialgatling"){folder="gatling";alias="aerialgatling -> gatling";}
    else if(folder=="stingerex"){folder="stinger";alias="stingerex -> stinger (shared weapon appearance)";}
    if(folder=="fm31"&&begins(stageStem,"frontonce")) {
        stageStem="frontrapid"+stageStem.substr(std::string("frontonce").size());
        alias="FM31 CHR frontonce -> authored FM31 frontrapid appearance; keep independent source loop/delays";
    }
    const auto prefix="character/gunner/effect/animation/subweapon/"+folder+"/at"+stageStem;
    // A missing matching pair means this controller has no established weapon
    // appearance template. Do not substitute another skill's weapon or effects.
    if(!pvf.has(prefix+"a.ani")&&!pvf.has(prefix+"b.ani"))return out;
    for(const auto &suffix:{std::pair<const char *,int>{"a.ani",-10},{"b.ani",10}})
        add(prefix+suffix.first,suffix.second,"Selected SKL stem + actual CHR subweapon stage + authored paired a/b ANI",alias);
    return out;
}
} // namespace dnf
