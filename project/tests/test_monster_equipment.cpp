#include "dnf/monster_equipment.hpp"
#include "dnf/renderer.hpp"
#include "dnf/session.hpp"
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
Bytes pixels(Renderer &renderer) {
 const auto size=renderer.outputSize();Bytes out(size_t(size[0])*size[1]*4);
 if(SDL_RenderReadPixels(renderer.raw(),nullptr,SDL_PIXELFORMAT_RGBA32,out.data(),size[0]*4))throw std::runtime_error(SDL_GetError());
 return out;
}
size_t equipmentCount(const MonsterMotion &motion) {
 return std::count_if(motion.tracks.begin(),motion.tracks.end(),[](const auto &t){return t.role=="equipment";});
}
bool equipmentError(const MonsterMotion &motion) {
 for(const auto &issue:motion.issues)if(issue.value("kind",std::string())=="monster_equipment"&&
    issue.value("code",std::string())!="empty_equipment_block")return true;
 return false;
}
}
Json runMonsterEquipmentTests(Pvf &pvf,Assets &assets) {
 Json checks=Json::array(),rows=Json::array(),scan=Json::array(),sourceOverrides=Json::array();
 const auto require=[&](bool value,const std::string &name){if(!value)throw std::runtime_error(name);checks.push_back(name);};
 const std::string thrower="monster/goblin/goblinthrower.mob";
 const std::vector<std::string> monsters={thrower,"monster/goblin/hillgab.mob","monster/goblin/seagab.mob",
  "monster/coldboy/coldboy.mob","monster/headlessknight/headlessknight.mob","monster/new_golem/biggolem.mob",
  "monster/new_golem/claygolem.mob","monster/succubus/azuriness.mob","monster/succubus/mistylime.mob",
  "monster/skeleton/skeleton_headless.mob","monster/zombie/nicol_zombie.mob"};
 RendererOptions options;options.shown=false;options.vsync=false;Renderer renderer(assets,options);
 renderer.setRenderProfile(ani_render::RenderProfile::Legacy1031);
 {
  // Current bytes: parent frame 0 lasts 500ms; the charge attachment loops
  // every 360ms and is explicitly removed at parent frame 1.
  const auto plan=compileMonsterAnimation(pvf,assets,
      "monster/soldier/animationsandorexpellerex/chargepierce.ani","attack1");
  require(plan->valid(),"Current 1031 charge parent and ALS dependency compile");
  const auto charge=std::find_if(plan->tracks.begin(),plan->tracks.end(),[](const auto &track) {
   return track.animation->path=="monster/soldier/animationsandorexpellerex/charge.ani";
  });
  require(charge!=plan->tracks.end()&&charge->loop&&charge->start==0&&charge->end==500&&
      charge->animation->duration==360,
      "Source LOOP child survives its first 360ms cycle until the 500ms parent remove event");
  const auto pose=charge->animation->samplePose(430,true);
  require(pose.frame==charge->animation->frameAt(70,false),
      "Late charge attachment selects its own second-cycle ANI frame");
  Actor sourceActor;sourceActor.animation="attack1";sourceActor.x=sourceActor.px=320;
  sourceActor.y=sourceActor.py=340;sourceActor.dead=true;sourceActor.life=ActorLife::Dying;
  sourceActor.deathMotion=plan;sourceActor.independentDeath=true;sourceActor.deathAnchorX=320;
  sourceActor.deathAnchorY=340;
  for(int dir:{-1,1})for(int64_t ms:{359,430,499,500}) {
   sourceActor.dir=dir;
   renderer.begin();renderer.monster(pvf,sourceActor,ms,1,0,0,true);const auto actual=pixels(renderer);
   renderer.begin();
   for(const auto &track:plan->tracks)if(ms>=track.start&&(track.hold||ms<track.end))
    renderer.animation(track.animation->path,ms-track.start,320+dir*track.x,340+track.y,dir,track.loop);
   require(actual==pixels(renderer),
       "Actual monster renderer consumes source loop/parent removal on either facing before and after frame 1");
  }
 }
 for(const auto &path:monsters)for(const auto &state:{"stay","move","attack1","damage1","damage2"}) {
  const auto plan=compileMonsterMotion(pvf,assets,path,state);
  require(plan->valid(),"Actual MOB body resolves: "+path+"|"+state+" "+plan->error);
  require(!equipmentError(*plan),"All selected EQU layers resolve: "+path+"|"+state+" "+plan->issues.dump());
  require(equipmentCount(*plan)>0,"Source EQU reaches composed motion: "+path+"|"+state);
  const auto body=compileMonsterAnimation(pvf,assets,plan->entry,state);
  require(body->valid()&&body->duration==plan->duration&&body->base==plan->base,
      "Visual equipment preserves body identity/duration: "+path+"|"+state);
  Json tracks=Json::array();
  std::set<std::pair<std::string,int>> identities;
  for(const auto &track:plan->tracks) {
   require(identities.emplace(track.animation->path,track.layer).second,"ACT/ALS/EQU track identity not duplicated: "+track.animation->path);
   if(track.role!="equipment")continue;
   require(track.hold&&track.start==0&&track.end==plan->duration,"Equipment visual lifetime follows current body action");
   const auto before=track.animation->frames.front().duration;
   for(double ms:{0.,30.,121.,double(plan->base->duration)}) {
    const auto clock=monsterTrackClock(*plan,track,ms);
    ani_clock::Snapshot root;root.elapsedMs=uint64_t(ms);root.ratePercent=100;root.policy=ani_clock::ClockPolicy::SourceDelay100;
    const auto expected=track.animation->followClock(*plan->base,root,false);
    require(clock&&clock->frame==expected.frame&&clock->elapsedMs==expected.elapsedMs,
      "Equipment uses root elapsed and borrowed source delays without advancing root twice");
   }
   require(track.animation->frames.front().duration==before,"Borrowed equipment clock does not mutate source delays");
   tracks.push_back({{"path",track.animation->path},{"layer",track.layer},{"source_frames",track.animation->frames.size()}});
  }
  size_t pixelCases=0,visibleIncrement=0,isolatedEquipmentPixels=0;
  for(int dir:{-1,1})for(int64_t ms:{0,60,150,300}) {
   Actor actor;actor.monsterPath=path;actor.animation=state;actor.dir=dir;actor.x=actor.px=320;actor.y=actor.py=340;
   renderer.begin();renderer.monster(pvf,actor,ms,1,0,0,true);const auto actual=pixels(renderer);
   renderer.begin();renderer.monster(pvf,actor,ms,1,0,0,false);
   require(actual==pixels(renderer),"World-consumed ACT diagnostics do not suppress source equipment pixels");
   renderer.begin();
   const bool loop=state==std::string("stay")||state==std::string("move");
   const auto equipmentTime=monsterMotionTime(*plan,ms,loop);
   for(const auto &track:plan->tracks)if(equipmentTime>=track.start&&(track.hold||equipmentTime<track.end)) {
    const auto clock=monsterTrackClock(*plan,track,equipmentTime);
    renderer.animation(track.animation->path,equipmentTime-track.start,320+dir*track.x,340+track.y,dir,track.loop,
       "",-1,1,false,clock?&*clock:nullptr);
   }
   require(actual==pixels(renderer),"Actual Renderer::monster consumes the composed current-PVF body and equipment source transforms");
   renderer.begin();
   const auto t=monsterMotionTime(*body,ms,loop);
   for(const auto &track:body->tracks)if(t>=track.start&&(track.hold||t<track.end))
    renderer.animation(track.animation->path,t-track.start,320+dir*track.x,340+track.y,dir,track.loop);
   visibleIncrement+=actual!=pixels(renderer);++pixelCases;
   renderer.begin();const auto blank=pixels(renderer);
   for(const auto &track:plan->tracks)if(track.role=="equipment") {
    const auto clock=monsterTrackClock(*plan,track,equipmentTime);
    renderer.animation(track.animation->path,equipmentTime-track.start,320+dir*track.x,340+track.y,dir,track.loop,
       "",-1,1,false,clock?&*clock:nullptr);
   }
   isolatedEquipmentPixels+=blank!=pixels(renderer);
  }
  if(path.find("/goblin/")!=std::string::npos||path.find("/coldboy/")!=std::string::npos)
   require(visibleIncrement>0,"Actual hidden Renderer::monster has visible source EQU increment: "+path+"|"+state);
  const auto right=monsterMotionBounds(assets,*plan,60,true,1),left=monsterMotionBounds(assets,*plan,60,true,-1);
  require(std::abs(right[0]+right[2]+left[0])<.001&&std::abs(right[2]-left[2])<.001,
     "Composed equipment bounds mirror exactly once");
  rows.push_back({{"monster",path},{"state",state},{"entry",plan->entry},{"tracks",tracks},
     {"pixel_cases",pixelCases},{"cases_with_visible_equipment_increment",visibleIncrement},
     {"cases_with_isolated_equipment_pixels",isolatedEquipmentPixels},
     {"pixel_observation",visibleIncrement?"source equipment changes composed pixels":isolatedEquipmentPixels?
       "isolated equipment is visible; composed output matches body (source overlap/occlusion)":"selected source equipment produces no isolated pixels at sampled times"},
     {"issues",plan->issues}});
 }
 const auto ordinary=compileMonsterMotion(pvf,assets,"monster/goblin/goblin.mob","stay");
 require(ordinary->valid()&&equipmentCount(*ordinary)==0,"Ordinary goblin without MOB equipment has no invented layers");
 const auto throwAttack=compileMonsterMotion(pvf,assets,thrower,"attack1");
 bool layer100=false,layer400=false;for(const auto &t:throwAttack->tracks) {
  layer100|=t.role=="equipment"&&t.layer==100&&t.animation->path.find("tcc2")!=std::string::npos;
  layer400|=t.role=="equipment"&&t.layer==400&&t.animation->path.find("tcc2")!=std::string::npos;
 }
 require(layer100&&layer400,"Repeated tcc2 EQU layer100 body and layer400 throw effect are both retained");
 const auto bigSit=compileMonsterMotion(pvf,assets,"monster/new_golem/biggolem.mob","sit");
 if(bigSit->valid())require(equipmentCount(*bigSit)==0&&!equipmentError(*bigSit),"Explicit empty golem sit equipment slot produces no replacement image");
 const auto original=compileMonsterMotion(pvf,assets,thrower,"move");
 const auto override=compileMonsterAnimationForMob(pvf,assets,thrower,original->base->path,"move");
 require(override->valid()&&equipmentCount(*override)==equipmentCount(*original),"Exact override preserves selected MOB equipment");
 {
  World world(pvf,assets);world.freezeAi=true;world.combat=true;Actor actor;actor.id=1;actor.monsterPath=thrower;
  actor.x=actor.px=350;actor.y=actor.py=300;actor.animation="move";actor.animationPath=original->base->path;
  actor.animStart=-130;actor.hp=0;actor.dead=true;world.monsters.push_back(actor);world.advanceSingleTick();
  auto &target=world.monsters[0];
  require(target.dead&&target.life!=ActorLife::Alive&&target.deathMotion&&equipmentCount(*target.deathMotion)>0,
    "Real World death freezes override including its source equipment");
  const auto saved=saveActor(target,world.nowMs());Actor restored=loadActor(saved,world.nowMs());
  world.restoreMonsterVisuals(restored);
  require(restored.dead&&restored.life==target.life&&restored.deathMotion&&
    equipmentCount(*restored.deathMotion)==equipmentCount(*target.deathMotion)&&restored.deathPoseTime==target.deathPoseTime,
    "Actual actor persistence and World restore rebuild equipment without reviving or restarting death pose");
 }
 size_t equipmentMobs=0,validStates=0,equipmentStates=0;
 for(const auto &path:pvf.paths("monster/",".mob")) {
  const auto mob=pvf.script(path);bool configured=false;for(const auto &f:mob.fields)configured|=normalize(f.tag)=="[equipment]";
  if(!configured)continue;++equipmentMobs;
  for(const auto &state:{"stay","move","sit","damage1","damage2","down","overturn","attack1","death"}) {
   const auto motion=compileMonsterMotion(pvf,assets,path,state);validStates+=motion->valid();equipmentStates+=equipmentCount(*motion)>0;
   scan.push_back({{"monster",path},{"state",state},{"valid",motion->valid()},{"entry",motion->entry},
     {"equipment_tracks",equipmentCount(*motion)},{"error",motion->error},{"issues",motion->issues}});
  }
  // Every explicit body slot is audited independently, including attack arrays
  // with empty preceding entries. Missing/ambiguous entries stay diagnostic.
  for(const auto &field:mob.fields)if(field.tag.find("motion")!=std::string::npos&&field.tag.find("[/")!=0)
   for(size_t index=0;index<field.values.size();++index) {
    const auto &literal=field.values[index];if(!literal.is_string()||literal.get<std::string>().empty())continue;
    const auto ani=normalize((std::filesystem::u8path(mob.path).parent_path()/std::filesystem::u8path(normalize(literal.get<std::string>()))).lexically_normal().generic_u8string());
    if(!pvf.has(ani))continue;
    const auto motion=compileMonsterAnimationForMob(pvf,assets,path,ani,field.tag);
    sourceOverrides.push_back({{"monster",path},{"tag",field.tag},{"index",index},{"animation",ani},
       {"valid",motion->valid()},{"equipment_tracks",equipmentCount(*motion)},{"error",motion->error},{"issues",motion->issues}});
   }
 }
 require(equipmentMobs==50,"Full current 1031 PVF inventory retains all 50 equipment-bearing MOBs");
 require(renderer.errors.empty(),"All required real monster equipment pixel cases render without resource errors");
 return {{"status","pass"},{"check_count",checks.size()},{"checks",checks},{"required_cases",rows},
   {"all_equipment_mobs",equipmentMobs},{"valid_state_plans",validStates},{"state_plans_with_equipment",equipmentStates},
   {"state_inventory",scan},{"explicit_motion_slot_inventory",sourceOverrides},{"asset_errors",assets.errors},
   {"classification","staged-source-binding-and-real-hidden-SDL-consumer-regression"},
   {"original_dynamic_comparison","pending_user"},{"equipment_clock_policy","inferred root elapsed / borrowed minimum source delays"}};
}
}
