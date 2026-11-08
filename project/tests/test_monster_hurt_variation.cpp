#include "dnf/combat.hpp"
#include "dnf/session.hpp"
#include "dnf/content_profile.hpp"
#include <set>
namespace dnf {
Json runMonsterHurtVariationTests(Pvf &pvf,Assets &assets) {
 Json checks=Json::array(),samples=Json::array();
 const auto output=std::filesystem::u8path("reports/seven-job-world/monster-presentation/hurt-registered.json");
 try {
  const auto check=[&](bool okay,const std::string &message){if(!okay)throw std::runtime_error(message);checks.push_back(message);};
  for(const auto &path:{"monster/goblin/goblin.mob","monster/goblin/goblinthrower.mob","monster/tau/tauarmy.mob"}) {
   World world(pvf,assets);world.freezeAi=true;world.combat=true;world.randomStreams()=RandomStreams(801);
   world.walkRects={{0,185,2000,800}};world.player.x=world.player.px=560;world.player.y=world.player.py=344;
   Actor actor;actor.id=17;actor.monsterPath=path;actor.hp=actor.maxHp=100000;actor.x=actor.px=640;actor.y=actor.py=344;
   world.monsters.push_back(actor);world.synchronizeEntityHandles();
   std::set<std::string> seen;Json sequence=Json::array();
   for(int i=0;i<24;++i) {
    auto &m=world.monsters[0];m.x=m.px=640;m.y=m.py=344;m.z=m.pz=0;m.vx=m.vy=m.vz=0;
    m.recovery=0;m.animation="stay";m.animationPath.clear();m.animStart=world.nowMs();
    const auto hp=m.hp;
    world.normalAttack();
    for(int j=0;j<180&&world.monsters[0].hp==hp;++j)world.advanceSingleTick();
    check(world.monsters[0].hp<hp,"Actual ordinary input reaches accepted grounded contact");
    check(world.monsters[0].animation=="damage1"||world.monsters[0].animation=="damage2","Actual contact chooses an authored hurt state");
    seen.insert(world.monsters[0].animation);sequence.push_back(world.monsters[0].animation);
    const auto contactSave=saveActor(world.monsters[0],world.nowMs());
    const auto contactRandom=world.randomStreams().snapshot();
    Actor contactRestore=loadActor(contactSave,world.nowMs());world.restoreMonsterVisuals(contactRestore);
    check(contactRestore.animation==world.monsters[0].animation &&
          contactRestore.animationPath==world.monsters[0].animationPath &&
          contactRestore.animStart==world.monsters[0].animStart &&
          world.randomStreams().snapshot()==contactRandom,
          "Immediate hurt-pose restore preserves selected authored path and age without RNG");
    for(int j=0;j<90;++j)world.advanceSingleTick();world.idle();
   }
   check(seen.size()==2,"Repeated actual grounded hits exercise both source hurt variants: "+std::string(path));
   const auto checkpoint=world.simulationCheckpoint();const auto saved=saveActor(world.monsters[0],world.nowMs());
   const auto random=world.randomStreams().snapshot();
   Actor restored=loadActor(saved,world.nowMs());world.restoreMonsterVisuals(restored);
   check(restored.animationPath==world.monsters[0].animationPath&&world.randomStreams().snapshot()==random,"Actor restore keeps selected pose without reroll");
   const auto actorId=world.monsters[0].id;
   world.monsters[0].z=world.monsters[0].pz=20;world.monsters[0].recovery=1;
   const auto beforeAir=world.randomStreams().snapshot();world.diagnosticHit(actorId,1,0,0,1,{});
   check(world.monsters[0].animation=="damage2"&&world.randomStreams().snapshot()==beforeAir,"Airborne reaction preserves current recovery route without hurt RNG");
   world.monsters[0].z=world.monsters[0].pz=0;world.monsters[0].recovery=2;
   const auto beforeDown=world.randomStreams().snapshot();world.diagnosticHit(actorId,1,0,0,1,{});
   check(world.monsters[0].animation=="down"&&world.randomStreams().snapshot()==beforeDown,"Downed reaction holds lying source pose without hurt RNG");
   world.restoreSimulationCheckpoint(checkpoint);
   check(world.randomStreams().snapshot()==random,"Simulation restore includes the separate hurt stream");
   RandomStreams comparison;comparison.restore(random);
   const auto a=world.randomStreams().stream(RandomDomain::MonsterHurt,0).next();
   const auto b=comparison.stream(RandomDomain::MonsterHurt,0).next();
   check(a==b,"Restored hurt stream advances exactly once from saved watermark");
   samples.push_back({{"monster",path},{"sequence",sequence},{"random",random}});
  }

  const auto setup=[&](World &world) {
   world.freezeAi=true;world.combat=true;world.randomStreams()=RandomStreams(803);
   world.walkRects={{0,185,2000,800}};world.player.x=world.player.px=560;world.player.y=world.player.py=344;
   Actor actor;actor.id=17;actor.monsterPath="monster/goblin/goblinthrower.mob";
   actor.hp=actor.maxHp=100000;actor.x=actor.px=640;actor.y=actor.py=344;
   world.monsters.push_back(actor);world.synchronizeEntityHandles();
  };
  const auto nextContact=[&](World &world) {
   world.idle();auto &m=world.monsters[0];m.x=m.px=640;m.y=m.py=344;m.z=m.pz=0;m.vx=m.vy=m.vz=0;
   m.recovery=0;m.animation="stay";m.animationPath.clear();m.animStart=world.nowMs();
   const auto hp=m.hp;world.normalAttack();
   for(int i=0;i<180&&world.monsters[0].hp==hp;++i)world.advanceSingleTick();
   check(world.monsters[0].hp<hp,"Continuation comparison uses an actual accepted ordinary contact");
   return Json{{"animation",world.monsters[0].animation},{"path",world.monsters[0].animationPath},
    {"damage",hp-world.monsters[0].hp},{"random",world.randomStreams().snapshot()}};
  };
  World original(pvf,assets);setup(original);nextContact(original);
  for(int i=0;i<90;++i)original.advanceSingleTick();original.idle();
  const auto state=original.simulationCheckpoint();
  const auto oldHandle=original.monsters[0].handle;
  World resumed(pvf,assets);setup(resumed);
  resumed.player=loadActor(saveActor(original.player,original.nowMs()),original.nowMs());
  resumed.monsters[0]=loadActor(saveActor(original.monsters[0],original.nowMs()),original.nowMs());
  resumed.restoreMonsterVisuals(resumed.monsters[0]);resumed.restoreSimulationCheckpoint(state);
  check(resumed.monsters[0].handle!=oldHandle,"World restore renews monster handles before continuation");
  for(int hit=0;hit<12;++hit) {
   const auto live=nextContact(original),reload=nextContact(resumed);
   check(live==reload,"Restored World next actual grounded contact matches uninterrupted hurt RNG, pose and damage");
   for(int i=0;i<90;++i){original.advanceSingleTick();resumed.advanceSingleTick();}
  }

  const auto cadence=[&](const std::vector<int64_t> &deltas) {
   World world(pvf,assets);setup(world);Json trace=Json::array();
   world.setBeforeTick([&](World &w) {
    if(w.tick%90==0) {
     w.idle();auto &m=w.monsters[0];m.x=m.px=640;m.y=m.py=344;m.z=m.pz=0;
     m.vx=m.vy=m.vz=0;m.recovery=0;m.animation="stay";m.animationPath.clear();w.normalAttack();
    }
   });
   world.setObjectTick([&](World &w) {
    trace.push_back({{"tick",w.tick},{"hp",w.monsters[0].hp},{"animation",w.monsters[0].animation},
     {"path",w.monsters[0].animationPath},{"random",w.randomStreams().snapshot()}});
   });
   for(auto delta:deltas)world.advance(delta);
   check(world.tick==360,"Hurt cadence covers six seconds of fixed simulation");return trace;
  };
  const auto deltas=[](int fps) {
   std::vector<int64_t> out;int64_t previous=0;
   for(int frame=1;frame<=fps*6;++frame){auto current=int64_t(frame)*6000000000ll/(fps*6);out.push_back(current-previous);previous=current;}
   return out;
  };
  const auto reference=cadence(deltas(60));
  for(int fps:{30,144,240})check(cadence(deltas(fps))==reference,"Actual grounded-hurt trace matches 60 FPS at "+std::to_string(fps)+" FPS");
  check(cadence({500000000,2500000000,1000000000,2000000000})==reference,"Render stalls and catch-up preserve each actual hurt draw");
  Json report={{"status","pass"},{"checks",checks},{"check_count",checks.size()},{"samples",samples},
    {"classification","user-requested grounded-hurt variation; original distribution unrecovered"},{"pvf_sha256",pvf.identity()}};

  report["count"]=checks.size();writeJson(output,report);return report;
 }catch(const std::exception &e) {
  writeJson(output,{{"status","fail"},{"checks",checks},{"samples",samples},{"error",e.what()},{"pvf_sha256",pvf.identity()}});
  throw;
 }
}
} // namespace dnf
