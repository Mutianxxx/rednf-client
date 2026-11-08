#include "dnf/portal_visuals.hpp"
#include "dnf/renderer.hpp"
#include "dnf/entry.hpp"
#include <iostream>
namespace dnf {
Json runPortalRendererTests(Pvf &pvf,Assets &assets) {
    int checks=0;Json samples=Json::array();
    auto check=[&](bool good,const std::string &message){++checks;if(!good)throw std::runtime_error("Portal renderer: "+message);};
    RendererOptions options;options.shown=false;options.vsync=false;options.width=800;options.height=600;
    Renderer renderer(assets,options);const std::string object="passiveobject/mapobject/pathgate/act1/lorienleftnormal.obj";
    auto read=[&] {
        const auto size=renderer.outputSize();Bytes pixels(size_t(size[0])*size[1]*4);
        if(SDL_RenderReadPixels(renderer.raw(),nullptr,SDL_PIXELFORMAT_RGBA32,pixels.data(),size[0]*4)!=0)
            throw std::runtime_error(SDL_GetError());
        return sha256(pixels);
    };
    auto direct=[&](bool open,int64_t commonMs,int64_t stateMs,bool forced) {
        renderer.begin();renderer.ui();
        for(const auto &track:portalVisuals(pvf,object,open).tracks) {
            const auto animation=assets.animation(track.animation);const auto flag=animation->globals.find("0");
            const bool loop=forced||(flag!=animation->globals.end()&&flag->get<bool>());
            renderer.animation(track.animation,double(track.state==0?commonMs:stateMs),200,400,1,loop,"",-1,1,false,nullptr,
                [variant=track.imageVariant](const std::string&image){return portalImageVariant(image,variant);});
        }
        return read();
    };
    renderer.begin();renderer.ui();const auto empty=read();
    int oldDifferences=0;
    for(auto profile:{ani_render::RenderProfile::Legacy1031,ani_render::RenderProfile::Inferred60Us1031}) {
        renderer.setRenderProfile(profile);const auto scene="test-profile-"+std::to_string(int(profile));
        renderer.begin();renderer.ui();renderer.portal(pvf,object,10000,200,400,false,scene,0);
        const auto closed=read();check(closed==direct(false,0,0,false)&&closed!=empty,
            "The hidden real SDL renderer displays the source closed door at installation");
        for(int64_t ms:{0,499,500,1099,1100,1600,2200,10000}) {
            renderer.begin();renderer.ui();renderer.portal(pvf,object,11000+ms,200,400,true,scene,0);
            const auto actual=read(),expected=direct(true,1000+ms,ms,false);
            check(actual==expected,"Actual Renderer::portal consumes source LOOP and its state transition clock");
            const auto old=direct(true,1000+ms,ms,true);oldDifferences+=actual!=old;
            samples.push_back({{"profile",int(profile)},{"state_ms",ms},{"actual",actual},{"source_reference",expected},{"forced_loop",old}});
            renderer.begin();renderer.ui();renderer.portal(pvf,object,11000+ms,200,400,true,scene,0);
            check(read()==actual,"Repeated rendered frame at the same simulation instant is identical");
        }
        renderer.begin();renderer.ui();renderer.portal(pvf,object,22000,200,400,false,scene,0);
        check(read()==direct(false,12000,0,false),"The actual close transition restarts its source state animation");
        renderer.begin();renderer.ui();renderer.portal(pvf,object,25000,200,400,true,scene+":new-room",0);
        check(read()==direct(true,0,0,false),"The actual new scene starts its own clocks even when global simulation time is large");
    }
    check(oldDifferences>0,"Actual captured output differs from the previous forced-loop output for late open-door frames");
    Json cadence=Json::array();
    for(int fps:{30,60,144,240}) {
        const auto scene="actual-render-cadence-"+std::to_string(fps);int64_t tick=0;
        renderer.observePortal(scene,0,object,0,false);
        for(int frame=0;tick<120;++frame) {
            const auto target=std::min<int64_t>(120,int64_t(frame)*60/fps);
            while(tick<target) {
                // Observe the previous completed fixed tick before beginning
                // its successor, exactly like main's setBeforeTick callback.
                renderer.observePortal(scene,0,object,tick*1000/60,tick>=30);++tick;
            }
            renderer.begin();renderer.ui();renderer.portal(pvf,object,tick*1000/60,200,400,tick>=30,scene,0);
        }
        const auto row=renderer.portalSourceReport().at("playback").at("instances").at(0);
        check(row.at("common_start_ms")==0&&row.at("state_start_ms")==500&&row.at("last_ms")==2000,
            "Actual Renderer boundary observation preserves the exact fixed transition across render catch-up grouping");
        cadence.push_back({{"fps",fps},{"clock",row},{"image",read()}});
    }
    for(size_t i=1;i<cadence.size();++i)check(cadence[i].at("image")==cadence[0].at("image")&&
        cadence[i].at("clock")==cadence[0].at("clock"),"Actual late portal frame and clock match30/60/144/240FPS");
    check(renderer.errors.empty()&&assets.errors.empty(),"Real portal rendering and source image decode emit no errors");
    return {{"status","pass"},{"checks",checks},{"samples",samples},{"old_policy_output_differences",oldDifferences},
        {"cadence",cadence},{"portal_source_report",renderer.portalSourceReport()},{"render_errors",renderer.errors},{"asset_errors",assets.errors},
        {"scope","Hidden SDL actual renderer/readback, both profiles, real source ANI/IMG; frontend/native dynamic comparison remains user verification"}};
}
}
