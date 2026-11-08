#include "dnf/combat.hpp"
#include "dnf/experimental_character.hpp"
#include "dnf/gunner_pixel_anchor.hpp"
#include "dnf/storage.hpp"
#include <cmath>
#include <stdexcept>

namespace dnf {
Json runGunnerRenderProfileTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),evidence=Json::array();
    const auto check=[&](bool passed,const std::string &message) {
        checks.push_back({{"passed",passed},{"message",message}});
        if(!passed)throw std::runtime_error("Gunner render profile: "+message);
    };
    const auto near=[](double a,double b){return std::abs(a-b)<1e-8;};
    try {
    // Independent 90-degree matrix vectors: crop/IMAGEPOS before anisotropic
    // scaling/rotation, with opposite rotation/order in the inferred profile.
    for(const auto profile:{ani_render::RenderProfile::Legacy1031,ani_render::RenderProfile::Inferred60Us1031})
    for(const int flip:{0,1,2,3})for(const int direction:{-1,1}) {
        AniPose pose;pose.x=7;pose.y=-11;pose.scaleX=1.75;pose.scaleY=.4;pose.rotationRadians=std::acos(-1.)/2;pose.flip=flip;
        const auto point=inferredGunnerPixelPoint(pose,-40,22,80.5,13.5,profile,direction);
        const double signX=(flip&1)?-1:1,signY=(flip&2)?-1:1;
        const bool inferred=profile==ani_render::RenderProfile::Inferred60Us1031;
        const double expectedX=direction*(inferred?42.875*signX:-9.8*signY);
        const double expectedY=inferred?-19.*signY:83.125*signX;
        check(near(point.x,expectedX)&&near(point.y,expectedY),"Crop, authored offset, anisotropic scale, radians, flip and facing match independent profile-specific matrix vectors");
        evidence.push_back({{"kind","matrix_vector"},{"profile",ani_render::profileName(profile)},
            {"flip",flip},{"direction",direction},{"point",{point.x,point.y}},{"expected",{expectedX,expectedY}}});
    }
    Animation tween;tween.path="fixture/profile-tween.ani";tween.duration=200;
    AniFrame a,b;a.duration=b.duration=100;a.x=-10;a.y=-20;b.x=30;b.y=40;
    a.properties={{"7",{2.,.5}},{"8",0.0},{"10",true}};
    b.properties={{"7",{.5,1.5}},{"8",std::acos(-1.)/2}};tween.frames={a,b};
    for(const auto profile:{ani_render::RenderProfile::Legacy1031,ani_render::RenderProfile::Inferred60Us1031}) {
        const auto early=tween.samplePose(10.75,false,-1,profile),late=tween.samplePose(70.75,false,-1,profile);
        const auto p=inferredGunnerPixelPoint(early,-21,-8,50.5,11.5,profile),q=inferredGunnerPixelPoint(late,-21,-8,50.5,11.5,profile);
        check(early.interpolated&&late.interpolated&&(!near(p.x,q.x)||!near(p.y,q.y)),
            "One immutable crop/pixel sample is transformed separately at two live tween times rather than caching an old pose");
    }
    RegionCatalog regions(pvf,assets);
    for(const int job:{2,5}) {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();Progression progression(regions);
        CharacterStore store(std::filesystem::absolute("profile-fixture-"+std::to_string(job)));
        store.data["characters"][0]={{"name","GunnerProfile"},{"class",job==2?"gunner":"atgunner"},
            {"identity",CharacterIdentity{job,0,0}.json()},{"level",1},{"skill_initialization","source-v1"}};
        store.apply(0,world,progression);world.configureAnimationClock(ani_clock::ClockPolicy::Inferred60UsPercentDeadlines);
        auto &runtime=*world.experimentalRuntime();
        const auto floor=[&]() {
            world.changeScene();world.monsters.clear();world.events.clear();world.releaseInputs();world.idle();
            world.combat=true;world.freezeAi=true;world.freeCd=true;world.mapWidth=4000;world.walkRects={{0,185,4000,800}};world.blockedRects.clear();
            auto &p=world.player;p.x=p.px=1400;p.y=p.py=400;p.z=p.pz=p.vz=0;p.dir=1;
            p.dead=false;p.life=ActorLife::Alive;p.hp=p.maxHp;p.mp=p.maxMp;p.recovery=0;p.stunUntil=0;p.hitStopTicks=0;p.hitStopped=false;
        };
        const auto fire=[&](ani_render::RenderProfile profile,int direction) {
            floor();world.configureRenderProfile(profile);world.player.dir=direction;
            const auto normal=world.skillState().snapshot(world.nowMs());
            world.enqueue({world.simulationNanoseconds(),4,true});world.advanceSingleTick();world.enqueue({world.simulationNanoseconds(),4,false});
            Json shot;
            for(int tick=0;tick<90&&shot.is_null();++tick) {
                for(const auto &fx:world.effects)if(fx.phase=="female-gunner:ordinary_bullet") {
                    shot={{"origin",{fx.x,fx.y,fx.z}},{"born",fx.born},{"source",fx.projectileSource}};break;
                }
                if(shot.is_null())world.advanceSingleTick();
            }
            check(!shot.is_null(),"Actual equipped job "+std::to_string(job)+" publishes a source shot under "+ani_render::profileName(profile));
            const auto &trace=shot.at("source").at("coordinate_trace");
            check(trace.at("render_profile")==ani_render::profileName(profile)&&world.renderProfile()==profile,
                "World profile and published source coordinate receipt use the same actual strategy");
            const auto &muzzle=trace.at("weapon_muzzle"),&sprite=trace.at("bullet_sprite");
            for(const auto *point:{&muzzle,&sprite})if(!point->is_null()) {
                const auto &transform=point->at("source_transform");
                check(transform.at("profile")==ani_render::profileName(profile),"Cached muzzle and projectile both apply the requested profile after lookup");
                AniPose pose;pose.x=transform.at("position")[0];pose.y=transform.at("position")[1];
                pose.scaleX=transform.at("rate")[0];pose.scaleY=transform.at("rate")[1];pose.rotationRadians=transform.at("rotation_radians");pose.flip=transform.at("flip");
                const auto &crop=point->at("img_crop"),&pixel=point->at("source_pixel");
                const auto p=inferredGunnerPixelPoint(pose,crop[0].get<int>(),crop[1].get<int>(),pixel[0].get<double>(),pixel[1].get<double>(),profile);
                check(near(p.x,point->at("local_point")[0])&&near(p.y,point->at("local_point")[1]),
                    "Actual source pixel/crop/ANI pose recomposes the exact cached-request local coordinate");
            }
            if(trace.at("muzzle_basis")=="visible_equipped_weapon_edge"&&!muzzle.at("source_transform").at("future_visible_fallback").get<bool>()) {
                const auto path=muzzle.at("animation").at("member_path").get<std::string>();
                const auto clip=assets.animation(path),root=assets.animation(world.player.animationClockSource);
                const auto child=clip->followClock(*root,*world.player.animationClock,world.player.animationClock->loop,world.player.animationControllerDelays.get());
                const auto pose=clip->samplePose(child,profile);const auto &transform=muzzle.at("source_transform");
                check(muzzle.at("frame")==pose.frame&&near(transform.at("position")[0],pose.x)&&near(transform.at("position")[1],pose.y)&&
                    near(transform.at("rate")[0],pose.scaleX)&&near(transform.at("rate")[1],pose.scaleY)&&near(transform.at("rotation_radians"),pose.rotationRadians),
                    "Actual gun muzzle follows the same child clock and live pose as the equipped Renderer layer");
            }
            const auto spritePoint=sprite.is_null()?Json::array({0,0}):sprite.at("local_point");
            const auto &origin=shot.at("origin"),&muzzlePoint=muzzle.at("local_point");
            check(near(origin[0].get<double>()+direction*spritePoint[0].get<double>(),world.player.x+direction*muzzlePoint[0].get<double>())&&
                near(origin[1].get<double>()-origin[2].get<double>()+spritePoint[1].get<double>(),world.player.y-world.player.z+muzzlePoint[1].get<double>()),
                "Actual left/right source projectile visible center is born at the matching equipped muzzle in world coordinates");
            check(world.skillState().snapshot(world.nowMs())==normal,"Render-profile coordinate work never changes normal learning state");
            bool rejected=false;try{world.configureRenderProfile(profile==ani_render::RenderProfile::Legacy1031?
                ani_render::RenderProfile::Inferred60Us1031:ani_render::RenderProfile::Legacy1031);}catch(const std::invalid_argument &){rejected=true;}
            check(rejected&&world.renderProfile()==profile,"Live action/projectile prevents a profile switch from invalidating its published spawn receipt");
            evidence.push_back({{"kind","actual_world_shot"},{"job",job},{"direction",direction},{"profile",ani_render::profileName(profile)},
                {"shot",shot},{"cache",world.femaleGunnerDiagnostics().at("source_work_cache")}});
            return world.femaleGunnerDiagnostics().at("source_work_cache");
        };
        const auto legacy=fire(ani_render::RenderProfile::Legacy1031,1);
        const auto inferred=fire(ani_render::RenderProfile::Inferred60Us1031,-1);
        check(inferred.at("point_entries")>legacy.at("point_entries"),"Switching profile on one owner creates independent point-cache keys");
        const auto repeat=fire(ani_render::RenderProfile::Inferred60Us1031,1);
        check(repeat.at("pixel_decodes")==inferred.at("pixel_decodes")&&repeat.at("point_hits")>inferred.at("point_hits"),
            "Repeated same-profile source frame reuses pixel work while recomputing its current pose");
        fire(ani_render::RenderProfile::Legacy1031,-1);
    }
    return {{"passed",true},{"check_count",checks.size()},{"checks",checks},{"evidence",evidence},
        {"native_socket_verified",false},{"frontend_started",false},{"original_dynamic_comparison","pending_user"}};
    }catch(const std::exception &error){writeJson("gunner-render-profile-failed.json",{{"error",error.what()},{"checks",checks},{"evidence",evidence}});throw;}
}
}
