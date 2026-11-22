#include "dnf/object_presentation.hpp"
#include "dnf/renderer.hpp"
namespace dnf {
namespace {
struct ObjectPresentationVideo {
 bool initialized=false;
 ObjectPresentationVideo() {
  if(!(SDL_WasInit(SDL_INIT_VIDEO)&SDL_INIT_VIDEO)) {
   SDL_SetMainReady();SDL_setenv("SDL_VIDEODRIVER","dummy",1);
   if(SDL_InitSubSystem(SDL_INIT_VIDEO))throw std::runtime_error(SDL_GetError());initialized=true;
  }
 }
 ~ObjectPresentationVideo(){if(initialized)SDL_QuitSubSystem(SDL_INIT_VIDEO);}
};
Bytes objectPresentationPixels(Renderer &r){const auto wh=r.outputSize();Bytes b(size_t(wh[0])*wh[1]*4);if(SDL_RenderReadPixels(r.raw(),nullptr,SDL_PIXELFORMAT_RGBA32,b.data(),wh[0]*4))throw std::runtime_error(SDL_GetError());return b;}
}
Json runObjectPresentationTests(Pvf &pvf,Assets &assets) {
 Json checks=Json::array(),rows=Json::array();
 const auto out=std::filesystem::u8path("reports/seven-job-world/monster-presentation");
 const auto output=out/"object-registered.json";
 try {
  ObjectPresentationVideo video;
  ObjectCatalog catalog(pvf,assets);
  const auto check=[&](bool value,const std::string &why){if(!value)throw std::runtime_error(why);checks.push_back(why);};
  RendererOptions options;options.shown=false;options.vsync=false;Renderer r(assets,options);
  for(int id:{221,222,223,224,231,243,244}) {
   World world(pvf,assets);world.freezeAi=true;world.combat=true;world.walkRects={{0,185,2000,800}};
   world.player.x=world.player.px=560;world.player.y=world.player.py=344;world.player.dir=1;
   Scene scene;ObjectPlacement placement;placement.id=id;placement.x=635;placement.y=344;placement.identity={"object-actual-input","room","source-fixture.map",uint64_t(id),0};
   const auto d=catalog.definition(id);scene.objectSystem.add(placement,d,currentObjectBehavior(*d));scene.refreshObjectViews();
   Json sample={{"id",id},{"source",d->source},{"diagnostics",d->diagnostics},{"hit_particle_programs",d->hitParticles.size()},{"destroy_particle_programs",d->destroyParticles.size()}};
   const auto contact=[&](){
    const auto before=world.events.size();world.normalAttack();bool hit=false;
    for(int i=0;i<180&&!hit;++i){world.advanceSingleTick();scene.updateObjects(world,pvf,assets);for(size_t k=before;k<world.events.size();++k)if(world.events[k].kind=="object_hit")hit=true;}
    check(hit,"Actual World ordinary input reaches source type14 object hurt boxes: "+std::to_string(id));
   };
   contact();
   if(id==221){for(int i=0;i<95;++i){world.advanceSingleTick();scene.updateObjects(world,pvf,assets);}world.idle();contact();}
   auto *instance=scene.objectSystem.find(placement.identity);
   if(id==223||id==224)check(instance->state==ObjectState::Reacting,"Trees retain source shake response and are not given invented destruction");
   else check(instance->state==ObjectState::Destroying||instance->state==ObjectState::Destroyed||instance->state==ObjectState::Removed,"Accepted object contact enters source destruction lifecycle");
   if(id!=222)check(!instance->visualParticles.empty(),"Source object PTL burst reaches live runtime particles: "+std::to_string(id));
   if(id==222)check(instance->motion()&&instance->motion()->path.find("treasureboxdestroy.ani")!=std::string::npos,"Source string-data chest destroy ANI is the active consumer");
   const auto saved=scene.objectSystem.save();ObjectSystem restored;restored.add(placement,d,currentObjectBehavior(*d));restored.restore(saved);
   check(restored.save()==saved,"Object particle positions, lifetime, RNG, state and hit ledger restore exactly");
   Scene restoredScene;restoredScene.objectSystem.add(placement,d,currentObjectBehavior(*d));
   restoredScene.refreshObjectViews();restoredScene.restoreObjects(saved,world.nowMs());
   World geometryWorld(pvf,assets);restoredScene.rebuildObstacles(geometryWorld);
   check(restoredScene.blockedRects==geometryWorld.blockedRects,
         "Restored private Scene and published World use the same live object obstacles");
   check(restoredScene.blockedRects.size()==restoredScene.objectSystem.activeObstacles().size(),
         "Scene geometry has one footprint per active obstacle without stale destroyed footprints");
   for(int sampleMs:{0,100,200}) {
    if(sampleMs){scene.objectSystem.advance(100000);restored.advance(100000);scene.refreshObjectViews();}
    check(restored.save()==scene.objectSystem.save(),"Restored particle progression matches uninterrupted fixed-time lifecycle");
    r.begin();const auto blank=objectPresentationPixels(r);
    for(const auto &o:scene.objects)if(!o.destroyed&&!o.animation.empty())r.animation(o.animation,o.animationMs,o.x-290,o.y-o.z,o.direction,o.loop);
    check(objectPresentationPixels(r)!=blank,"Actual hidden SDL draws source object/particle presentation at "+std::to_string(sampleMs)+"ms for "+std::to_string(id));
    r.screenshot(out/("object-"+std::to_string(id)+"-"+std::to_string(sampleMs)+".png"));
   }
   scene.objectSystem.advance(31000000);scene.refreshObjectViews();
   check(scene.objectSystem.find(placement.identity)->visualParticles.empty(),"Completed source PTL particles leave no persistent live visual");
   bool sound=false,reward=false;for(const auto &e:world.events){sound|=e.kind=="sound"&&(e.name==d->hitSound||e.name==d->destroySound);reward|=e.kind=="kill"||e.kind=="drop"||e.kind=="reward";}
   if(!d->hitSound.empty()||!d->destroySound.empty())check(sound,"Actual source object sound reaches World event consumer");
   check(!reward,"Object presentation produces no monster or duplicate reward");
   sample["snapshot_at_contact"]=saved;sample["world_events"]=world.eventLog();rows.push_back(sample);
  }
  check(r.errors.empty(),"All actual source object particles and destroy clips decode without renderer errors");
  Json report={{"status","pass"},{"check_count",checks.size()},{"checks",checks},{"cases",rows},{"asset_errors",assets.errors},{"pvf_sha256",pvf.identity()},
   {"classification","source runtime presentation; explicitly inferred legacy contact thresholds and emitter projection"}};

  report["count"]=checks.size();writeJson(output,report);return report;
 }catch(const std::exception &e) {
  writeJson(output,{{"status","fail"},{"checks",checks},{"cases",rows},{"error",e.what()},{"pvf_sha256",pvf.identity()}});
  throw;
 }
}
} // namespace dnf
