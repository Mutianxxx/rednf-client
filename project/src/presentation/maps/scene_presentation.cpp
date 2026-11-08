#include "dnf/scene_presentation.hpp"
#include "dnf/content_profile.hpp"
#include <stdexcept>
namespace dnf {
ScenePresentationPlan prepareScenePresentation(Pvf &pvf,Assets &assets,const Script &owner,std::string name) {
    ScenePresentationPlan result;result.owner=owner.path;result.name=std::move(name);
    result.evidence={{"pvf_sha256",pvf.identity()},{"owner",owner.path},{"owner_sha256",sha256(owner.rawBytes)},
        {"source_fields",Json::array()},{"classification","current source bindings; display scheduling is user reconstruction"}};
    for(const auto &f:owner.fields)if(f.tag=="[cutscene image]"||f.tag=="[entering title]")
        result.evidence["source_fields"].push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});
    const auto image=owner.values("[cutscene image]");
    if(image.size()>=2&&image[0].is_string()&&image[1].is_number_integer()&&!image[0].get<std::string>().empty()) {
        try {
            const auto path=normalize(image[0]);const auto frame=image[1].get<int>();
            const auto pixels=assets.pixels(path,frame);
            if(pixels.logicalWidth<=0||pixels.logicalHeight<=0)throw std::runtime_error("Cutscene has no logical canvas");
            result.image=path;result.imageFrame=frame;result.imageSize={pixels.logicalWidth,pixels.logicalHeight};
            const auto blob=assets.blob(path);Cursor header{blob};header.text(16);header.get<uint64_t>();header.get<int32_t>();
            const auto count=header.get<int32_t>();
            // Annotated MAP sample explicitly describes frame1 behind frame0.
            // Optional frame is checked through the IMG count, not swallowed as
            // a decode exception. The common 1031 Lorien IMG has only frame0.
            if(frame==0&&count>1) {
                const auto background=assets.pixels(path,1);result.backgroundFrame=1;
                result.backgroundSize={background.logicalWidth,background.logicalHeight};
            }
            result.evidence["cutscene"]={{"path",path},{"frame",frame},{"frame_count",count},
                {"sha256",sha256(blob)},{"optional_background",result.backgroundFrame}};
        }catch(const std::exception &error){result.image.clear();result.backgroundFrame=-1;
            result.diagnostics.push_back({{"kind","cutscene_resource_failure"},{"source",owner.path},{"error",error.what()}});}
    }else result.diagnostics.push_back({{"kind","cutscene_binding_absent"},{"source",owner.path}});
    const auto title=owner.values("[entering title]");
    if(!title.empty()&&title[0].is_string()&&!title[0].get<std::string>().empty()) {
        try {
            const auto path=normalize((std::filesystem::u8path(owner.path).parent_path()/
                std::filesystem::u8path(title[0].get<std::string>())).generic_u8string());
            const auto animation=assets.animation(path);
            if(animation->frames.empty()||animation->duration<=0)throw std::runtime_error("Entering title has no finite source animation");
            for(const auto &f:animation->frames)if(!f.image.empty())assets.pixels(f.image,f.imageFrame);
            result.title=path;result.titleDurationMs=animation->duration;
            result.evidence["title"]={{"path",path},{"sha256",sha256(pvf.read(path))},
                {"duration_ms",animation->duration},{"frames",animation->frames.size()},
                {"timing","source milliseconds, one finite source clip; no fabricated glyph blink"}};
        }catch(const std::exception &error){result.diagnostics.push_back({{"kind","entering_title_resource_failure"},
            {"source",owner.path},{"error",error.what()}});}
    }
    return result;
}
void ScenePresentation::begin(ScenePresentationPlan plan,int64_t wallMs) {
    if(wallMs<0)throw std::invalid_argument("Negative presentation clock");
    plan_=std::move(plan);began_=wallMs;ready_=-1;
}
void ScenePresentation::ready(int64_t wallMs) {
    if(began_<0||wallMs<began_)throw std::invalid_argument("Presentation ready clock precedes begin");
    if(ready_<0)ready_=wallMs; // First ready owns the timeline; repeated draws cannot restart it.
}
ScenePresentationFrame ScenePresentation::frame(int64_t wallMs)const {
    if(began_<0)return {};
    if(wallMs<began_)throw std::invalid_argument("Presentation clock precedes begin");
    const auto elapsed=wallMs-began_;
    if(ready_<0)return {true,true,true,0,-1};
    const auto fadeStart=std::max<int64_t>(1000,ready_-began_);
    if(elapsed<fadeStart)return {true,true,true,0,-1};
    const auto fade=elapsed-fadeStart;
    if(fade<300)return {true,true,true,uint8_t(fade*255/300),-1};
    const auto reveal=fade-300;
    const auto titleMs=reveal<plan_.titleDurationMs?reveal:int64_t(-1);
    if(reveal<400)return {true,false,true,uint8_t(255-reveal*255/400),titleMs};
    return {titleMs>=0,false,false,0,titleMs};
}
Json ScenePresentation::snapshot(int64_t wallMs)const {
    const auto f=frame(wallMs);
    return {{"source",plan_.evidence},{"diagnostics",plan_.diagnostics},{"began_wall_ms",began_},
        {"ready_wall_ms",ready_},{"active",f.active},{"blocked",f.blocked},{"cutscene",f.cutsceneVisible},
        {"black_alpha",f.blackAlpha},{"title_ms",f.titleMs},
        {"transition_policy","user-min1000-art-300-to-black-400-reveal-v1"}};
}
} // namespace dnf
