#include "dnf/female_gunner_skill_layers.hpp"
#include "dnf/experimental_character.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
Json runFemaleGunnerSkillLayerTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),failures=Json::array(),rows=Json::array();
    const auto check=[&](bool passed,const std::string &message) {
        checks.push_back({{"passed",passed},{"message",message}});if(!passed)failures.push_back(message);
    };
    CharacterCatalog catalog(pvf);const auto plan=loadExperimentalCharacterPlan(pvf,assets,catalog,{5,0,0});
    const auto build=[&](int id,size_t stageIndex) {
        const auto &d=plan.femaleGunnerSkills.at({5,id});const auto &s=d.stages.at(stageIndex);
        const auto *motion=plan.motion(s.motionTag,s.motionSlot);
        if(!motion)throw std::logic_error("Source skill-layer test has no current CHR motion");
        return buildFemaleGunnerSkillLayers(pvf,assets,d,motion->source.memberPath);
    };
    const auto wait=build(9,0),random=build(9,1);
    check(wait.empty(),"RandomShoot Wait does not draw preloaded Shoot/fire effects before its actual body phase");
    check(random.size()==4,"Current1031 RandomShoot binds four full20-frame matching appearance tracks");
    std::set<std::string> sourcePaths;size_t back=0,front=0;
    for(const auto &layer:random) {
        const auto clip=assets.animation(layer.source.memberPath);
        check(layer.synchronizedToBody&&clip->frames.size()==20&&clip->duration==62400,
            "Gun dance appearance retains all20 source frame identities and follows body controller schedule");
        check(layer.source.packageIdentity==pvf.identity()&&layer.source.memberSha256==sha256(pvf.read(layer.source.memberPath)),
            "Gun dance layer is bound to current immutable PVF source bytes");
        sourcePaths.insert(layer.source.memberPath);back+=layer.layer<0;front+=layer.layer>=0;
        rows.push_back(layer.snapshot());
    }
    check(sourcePaths.size()==4&&back>0&&front>0,"Gun dance overlays remain distinct with explicit inferred front/back order");
    check(!sourcePaths.count("character/gunner/effect/animation/shooteffect/atrandomshootfire.ani"),
        "Five-frame shot effect with unresolved trigger is not spawned by a preload or20-frame appearance binding");
    for(const int id:{12,13,14,36,38,39,40,75,107,108}) {
        const auto &d=plan.femaleGunnerSkills.at({5,id});bool paired=false;
        for(size_t stage=0;stage<d.stages.size();++stage) {
            const auto layers=build(id,stage);if(layers.empty())continue;
            paired=true;check(layers.size()==2,"Heavy weapon appearance has the selected source a/b pair: "+std::to_string(id));
            for(const auto &layer:layers) {
                const auto clip=assets.animation(layer.source.memberPath),body=assets.animation(layer.bodyPath);
                bool same=clip->frames.size()==body->frames.size();
                if(same)for(size_t f=0;f<clip->frames.size();++f)same&=clip->frames[f].duration==body->frames[f].duration;
                check(layer.synchronizedToBody==same&&layer.loop==clip->globals.value("0",false),
                    "Each actual heavy weapon track uses equal-frame body timing or its own source delays/loop: "+std::to_string(id));
                check(layer.source.memberSha256==sha256(pvf.read(layer.source.memberPath)),
                    "Selected weapon ANI references current source bytes: "+std::to_string(id));
                rows.push_back(layer.snapshot());
            }
        }
        check(paired,"Skill has a real source weapon appearance consumer candidate: "+std::to_string(id));
    }
    const auto gatling=build(12,0),flame=build(13,0),laser=build(39,0);
    check(gatling.size()==2&&flame.size()==2&&laser.size()==2&&
          gatling.front().source.memberPath!=flame.front().source.memberPath&&
          flame.front().source.memberPath!=laser.front().source.memberPath,
        "Shared CHR body stage cannot replace selected skill's Gatling/Flame/Laser weapon identity");
    const auto flameMismatch=std::find_if(flame.begin(),flame.end(),[](const auto &l){return !l.synchronizedToBody;});
    check(flameMismatch!=flame.end()&&assets.animation(flameMismatch->source.memberPath)->frames.size()==5,
        "Five-frame Flame front layer keeps its own source timeline instead of borrowing a six-frame cursor");
    const auto flameHold=build(13,1);bool blankPreserved=false;
    for(const auto &layer:flameHold) {
        const auto clip=assets.animation(layer.source.memberPath);
        if(std::all_of(clip->frames.begin(),clip->frames.end(),[](const auto &f){return f.image.empty();}))blankPreserved=layer.loop;
    }
    check(blankPreserved,"Authored image-free looping Flame track stays empty; no guessed texture is injected");
    auto wrongJob=plan.femaleGunnerSkills.at({5,9});wrongJob.key.jobId=0;
    check(buildFemaleGunnerSkillLayers(pvf,assets,wrongJob,random.front().bodyPath).empty(),
        "Female Gunner skill attachment cannot leak to another job identity");
    check(buildFemaleGunnerSkillLayers(pvf,assets,plan.femaleGunnerSkills.at({5,9}),
        "character/gunner/animation/randomshoot.ani").empty(),
        "Male Gunner's same stem cannot authorize a Female Gunner attachment");
    const auto again=build(9,1);bool stable=again.size()==random.size();
    if(stable)for(size_t i=0;i<again.size();++i)stable&=again[i].snapshot()==random[i].snapshot();
    check(stable,"Immutable stage-layer rebuilding is deterministic and creates no command/entity side effects");
    return {{"status",failures.empty()?"passed":"failed"},{"checks",checks},{"failures",failures},{"bindings",rows},
        {"scope","Current-PVF attachment source/identity/timing checks; actual World-to-Renderer pixel consumption is verified by the renderer effect test, native layer order remains pending"}};
}
} // namespace dnf
