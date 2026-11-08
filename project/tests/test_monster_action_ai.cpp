#include "dnf/monster_action_ai.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/monster_behavior.hpp"
#include "dnf/session.hpp"
#include "dnf/storage.hpp"
#include <chrono>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *mobPath="monster/newmonsters/shonan/kaizen/kaizen.mob";
constexpr const char *actionPath="monster/newmonsters/shonan/kaizen/ai/action.ai";
constexpr const char *teleportPath="monster/newmonsters/shonan/kaizen/action/teleport.act";
constexpr const char *chancePath="monster/event/bluemarble/launcher/ai/action.ai";
const std::filesystem::path reportRoot=std::filesystem::u8path("reports/seven-job-world/action-ai");
size_t sourceExecutions(const World &world,const std::string &path=teleportPath) {
 return size_t(std::count_if(world.events.begin(),world.events.end(),[&](const Event &e){return e.kind=="source_action"&&e.name==path;}));
}
void plane(World &w) {
 w.mapWidth=20000;w.walkRects={{12,185,19976,1200}};w.blockedRects.clear();w.combat=true;w.freezeAi=false;
}
void configure(World &w,Assets &assets) {
 w.configureSourceActions("monster-action-ai-test:"+sha256(assets.staticBytes("audio.xml")),true);
}
void kaizen(World &w,Pvf &pvf) {
 plane(w);w.randomStreams()=RandomStreams(5002);w.monsters.clear();
 w.player.x=w.player.px=6000;w.player.y=w.player.py=500;w.player.dir=1;
 const auto registry=pvf.script("monster/monster.lst");int sourceId=-1;
 for(size_t i=0;i+1<registry.tokens.size();++i)if(registry.tokens[i].at("value").is_number_integer()&&registry.tokens[i+1].at("value").is_string()&&
  normalize("monster/"+registry.tokens[i+1].at("value").get<std::string>())==mobPath) {
  if(sourceId>=0)throw std::runtime_error("Ambiguous source Kaizen registry ID");sourceId=registry.tokens[i].at("value").get<int>();
 }
 if(sourceId<0)throw std::runtime_error("Source Kaizen is not registered");
 Actor a;a.id=31;a.sourceId=sourceId;a.monsterPath=mobPath;a.hp=a.maxHp=10000;a.x=a.px=1000;a.y=a.py=500;a.dir=1;
 // Explicit source-service fixture, not a fabricated claim of MAP spawn data.
 a.sourceStats["spawn"]={{"diagnostic_fixture","real Kaizen MOB/AI/ACT on wide test plane"}};
 w.monsters.push_back(std::move(a));w.synchronizeEntityHandles();w.configureMonsterActionAi("easy");
}
void ticks(World &w,int n){while(n-->0)w.advanceSingleTick();}
Json normalized(const World &w) {
 Json actors=Json::array();for(const auto &a:w.monsters)actors.push_back({{"id",a.id},{"x",a.x},{"y",a.y},{"z",a.z},
  {"hp",a.hp},{"dir",a.dir},{"animation",a.animation},{"path",a.animationPath},{"life",int(a.life)}});
 return {{"tick",w.tick},{"actors",actors},{"simulation",w.simulationCheckpoint()},
  {"host",w.actHost()->snapshot(37)},{"events",w.eventLog()},{"diagnostics",w.monsterActionAiState()}};
}
template<class F>bool rejects(F f){try{f();}catch(const std::exception&){return true;}return false;}
}

Json runMonsterActionAiTests(Pvf &pvf,Assets &assets) {
 Json out={{"status","running"},{"checks",Json::array()},{"samples",Json::object()},{"pvf_sha256",pvf.identity()},
  {"scope","Real 1031 Action.ai ordered evaluator, World automatic scheduler and Kaizen teleport consumer; wide collision/legacy balance fixture; real CharacterStore and RegionSession APIs"},
  {"policy",monsterActionAiPolicy()},{"whole_monster_or_region_complete",false},{"frontend_and_native_dynamic_comparison","pending user"}};
 const auto check=[&](bool okay,const std::string &message){if(!okay)throw std::runtime_error(message);out["checks"].push_back(message);};
 try {
  const auto source=pvf.script(actionPath);const auto compilation=compileMonsterActionAi(pvf,source);
  check(compilation.ok()&&compilation.program->original.rawBytes==source.rawBytes&&compilation.program->original.tokens==source.tokens&&
   compilation.program->retainedFields.size()==source.fields.size(),"Compiler retains exact current Kaizen bytes, ordered tokens/fields and source identities");
  const auto routes=selectMonsterActionAiRoutes(pvf,pvf.script(mobPath),"easy");
  check(routes.ok&&routes.configured&&routes.paths[2]==actionPath,"Complete explicit MOB easy row resolves Action slot without filename fallback");
  check(!selectMonsterActionAiRoutes(pvf,pvf.script(mobPath),"nonexistent").ok&&
   !selectMonsterActionAiRoutes(pvf,pvf.script(mobPath),"../easy").ok,"Missing and unsafe AI difficulties fail without normal/easy fallback");
  MonsterActionAiContext context;context.owner={10,1};context.target={11,1};context.ownerPosition={1000,500,0};context.targetPosition={6000,500,0};
  context.cooldown=[](int)->std::optional<bool>{return false;};Pcg32 random(21,8);const auto before=random.snapshot();
  auto result=evaluateMonsterActionAi(*compilation.program,context,random);
  check(result.ok&&result.returned==3&&random.snapshot()==before,"Distant target chooses authored Kaizen teleport slot3 without mutating input RNG");
  context.targetPosition[0]=1080;result=evaluateMonsterActionAi(*compilation.program,context,random);
  check(result.ok&&result.returned==1,"Nested near-area sequence returns authored slot1 rather than a later statement");
  context.targetPosition[0]=1150;result=evaluateMonsterActionAi(*compilation.program,context,random);
  check(result.ok&&result.returned==0,"Second source-area branch selects actual slot0");
  context.targetPosition[0]=6000;context.cooldown=[](int index)->std::optional<bool>{return index==3;};
  result=evaluateMonsterActionAi(*compilation.program,context,random);
  check(result.ok&&result.returned==-1,"Authored cooldown true branch returns terminal no-action");
  context.owner={};result=evaluateMonsterActionAi(*compilation.program,context,random);
  check(!result.ok&&!result.candidateRandom&&random.snapshot()==before,"Invalid typed context fails without a candidate or live random draw");
  auto changed=source;changed.rawBytes.back()^=1;check(!compileMonsterActionAi(pvf,changed).ok(),"Forged AI raw bytes fail current PVF identity validation");
  changed=source;changed.fields[0].values.push_back("forged");check(!compileMonsterActionAi(pvf,changed).ok(),"Forged ordered fields fail even when original raw bytes are retained");
  const auto chance=compileMonsterActionAi(pvf,pvf.script(chancePath));check(chance.ok(),"Real 1031 source nested cooldown/chance program compiles");
  context.owner={10,1};context.cooldown=[](int)->std::optional<bool>{return false;};std::set<int> chosen;
  for(uint64_t seed=0;seed<32;++seed) {
   Pcg32 input(seed,31);const auto state=input.snapshot();auto expected=input;const auto expectedValue=expected.bounded(100);
   const auto draw=evaluateMonsterActionAi(*chance.program,context,input);
   check(draw.ok&&draw.returned==(expectedValue<50?0:-1)&&input.snapshot()==state&&draw.candidateRandom->snapshot()==expected.snapshot(),
    "Source chance evaluates one bounded candidate draw without publishing it");chosen.insert(*draw.returned);
  }
  check(chosen==std::set<int>({-1,0}),"Source chance fixture covers both authored outcomes");
  out["samples"]["kaizen_ai"]=compilation.json();out["samples"]["routes"]=routes.json();
  {
   const auto mob=pvf.script(mobPath);
   const auto chase=readMonsterSourceMovement(pvf,mob,1,0,0);
   check(chase.ready&&chase.speed==216,"Current Kaizen source1200 uses declared shared per-mille movement conversion");
   auto step=planMonsterMovement(chase,{1000,500},{1001,501},1,17);
   check(step.dx==1&&step.dy==1&&step.direction==1,"Destination integrator clamps both axes at target without overshoot");
   step=planMonsterMovement(chase,{1000,500},{900,500},1,17);
   check(step.dx<0&&step.dy==0&&step.direction==-1,"Source locomotion faces target and stops the already aligned axis");
   const auto behind=readMonsterSourceMovement(pvf,mob,1,19,0);
   step=planMonsterMovement(behind,{1000,500},{1100,500},1,17,1);
   check(behind.ready&&step.dx<0,"Source destination19 selects target rear using actual keep-distance field");
   check(!readMonsterSourceMovement(pvf,mob,1,25,0).ready&&!readMonsterSourceMovement(pvf,mob,1,0,1).ready,
    "Unknown destination and unverified dash method do not fabricate movement");
   auto forged=mob;for(auto &field:forged.fields)if(normalize(field.tag)=="[move speed]")field.values[0]=1;
   check(!readMonsterSourceMovement(pvf,forged,1,0,0).ready,"Movement source validation rejects edited fields with unchanged PVF bytes");
   const auto range=readMonsterSourceMovement(pvf,pvf.script("monster/newmonsters/heaven/jena/jena.mob"),40,11,0);
   check(range.ready&&range.keepDistance==250&&range.keepY==10&&range.radiusX==100&&range.radiusY==100,
    "Jena range destination consumes all four current source operands");
   out["samples"]["movement_source"]=behind.evidence;
  }
  {
   World w(pvf,assets);configure(w,assets);kaizen(w,pvf);
   check(sourceExecutions(w)==0,"Source configuration is pure before the first simulation boundary");
   ticks(w,1);const auto owner=w.monsters[0].handle;
   check(sourceExecutions(w)==1&&w.actHost()->ownsActor(owner),"World tick automatically evaluates actual Action.ai and binds real teleport ACT");
   const auto bound=w.monsterActionAiState();const auto rng=w.randomStreams().snapshot();
   uint64_t age=0;for(const auto &[id,instance]:w.actHost()->instances())if(instance.owner==owner&&instance.status==ActInstanceStatus::Running)age=instance.animationUs;
   w.freezeAi=true;ticks(w,12);uint64_t pausedAge=0;for(const auto &[id,instance]:w.actHost()->instances())if(instance.owner==owner&&instance.status==ActInstanceStatus::Running)pausedAge=instance.animationUs;
   check(age==pausedAge&&w.randomStreams().snapshot()==rng&&w.monsterActionAiState()==bound,"AI pause freezes source animation/selection and does not reroll decisions");
   // Leave the authored close-range branch after its teleport starts. The
   // active source cooldown then reaches the real no-action/movement branch.
   w.player.x=w.player.px=15000;
   w.freezeAi=false;ticks(w,65);
   const auto &moved=w.monsters[0];const bool owns=w.actHost()->ownsActor(owner);
   const auto executionCount=sourceExecutions(w);
   out["samples"]["world_teleport_runtime"]={{"position",{moved.x,moved.y,moved.z}},
    {"source_teleport_executions",executionCount},{"act_owns_actor",owns},
    {"ai_state",w.monsterActionAiState()},{"source_action_diagnostics",w.sourceActionDiagnostics()},
    {"act_host",w.actHost()->snapshot(37)}};
   check(std::isfinite(moved.x)&&std::isfinite(moved.y)&&moved.x>1000&&executionCount==1,
    "Authored frame7 teleport and 40JP source movement remain in the real finite World position (x="+
     std::to_string(moved.x)+", y="+std::to_string(moved.y)+", actions="+
     std::to_string(executionCount)+", ACT owner="+(owns?"yes":"no")+")");
   const auto beforeScene=w.randomStreams().snapshot();w.changeScene();
   check(!w.actHost()->ownsActor(owner)&&!static_cast<const World&>(w).resolveActor(owner)&&w.randomStreams().snapshot()==beforeScene,
    "Scene boundary retires source ownership and presentation without random work");
  }
  {
   World w(pvf,assets);configure(w,assets);kaizen(w,pvf);w.monsters[0].stunUntil=1500;
   const auto beforeStun=w.randomStreams().snapshot();ticks(w,89);
   check(sourceExecutions(w)==0&&w.randomStreams().snapshot()==beforeStun,"Stun across several think phases does not queue markers or consume chance state");
   const auto authoredTerm=pvf.script(mobPath).values("[think term]");
   const auto term=authoredTerm.size()==1?authoredTerm[0].get<int>():500;
   int waited=0;while(!sourceExecutions(w)&&waited++<int(std::ceil(term*60.0/1000))+4)ticks(w,1);
   check(sourceExecutions(w)==1,"First legal source-time phase after stun performs one actual source action");
  }
  {
   World w(pvf,assets);configure(w,assets);kaizen(w,pvf);w.player.x=w.player.px=1080;ticks(w,1);const auto rng=w.randomStreams().snapshot();ticks(w,29);out["samples"]["blocked_attack_diagnostics"]=w.sourceActionDiagnostics();
   check(sourceExecutions(w)==0&&w.randomStreams().snapshot()==rng&&w.sourceActionDiagnostics().dump().find("unsupported_behavior_opcode")!=std::string::npos,
    "Real selected Kaizen attack still blocks unsupported authored opcodes without publishing AI RNG");
  }
  {
   World w(pvf,assets);configure(w,assets);kaizen(w,pvf);ticks(w,49);
   // Let the initial teleport finish near its authored far target, then move
   // the target beyond attack range while the teleport slot is cooling down.
   w.player.x=w.player.px=1000;ticks(w,131);
   const auto owner=w.monsters[0].handle;
   const auto checkpoint=w.sourceMonsterCooldownCheckpoint(owner);
   out["samples"]["no_action_movement_runtime"]={{"checkpoint",checkpoint},
    {"actor",{{"position",{w.monsters[0].x,w.monsters[0].y,w.monsters[0].z}},
     {"animation",w.monsters[0].animation},{"stun_until",w.monsters[0].stunUntil}}},
    {"ai_state",w.monsterActionAiState()},{"source_action_diagnostics",w.sourceActionDiagnostics()},
    {"act_host",w.actHost()->snapshot(37)}};
   check(checkpoint.contains("movement")&&checkpoint.at("movement").at("destination")==19,
    "Actual source no-action decision schedules and checkpoints Kaizen rear movement (checkpoint="+
     checkpoint.dump()+", x="+std::to_string(w.monsters[0].x)+", y="+
     std::to_string(w.monsters[0].y)+")");
   const auto plan=w.prepareSourceMonsterMovementRestore(w.monsters[0],checkpoint);
   check(plan&&plan->ready,"Movement restores from the existing source/generation room bundle without drawing RNG");
   auto bad=checkpoint;bad["movement"]["offset"][0]=1;
   check(rejects([&]{w.prepareSourceMonsterMovementRestore(w.monsters[0],bad);}),
    "Movement restore rejects offsets outside actual source radius");
   const auto x=w.monsters[0].x,y=w.monsters[0].y;w.freezeAi=true;ticks(w,30);
   check(w.monsters[0].x==x&&w.monsters[0].y==y,"AI pause freezes actual source movement and does not drift");
  }
  {
   Json reference;
   for(const int fps:{60,30,144,240,0}) {
    World w(pvf,assets);configure(w,assets);kaizen(w,pvf);
    if(fps){int64_t previous=0;for(int frame=1;frame<=fps*2;++frame){const auto end=int64_t(frame)*2000000000ll/(fps*2);w.advance(end-previous);previous=end;}}
    else {w.advance(2000000000ll,3);while(w.pendingTicks())w.advance(0,3);}
    const auto state=normalized(w);if(reference.is_null())reference=state;
    check(state==reference,"Full source scheduler/host, coordinates, IDs, RNG and diagnostics agree across render rates and budgeted catch-up");
   }
   out["samples"]["fixed_tick"]=reference;
  }
  {
   RegionCatalog catalog(pvf,assets);RegionSession session;session.begin(catalog,1,522);
   const auto directory=reportRoot/"source-ai-save"/std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
   CharacterStore store(directory,"source-ai-character-test");
   store.data["characters"][0]={{"name","Source AI"},{"class","swordman"},{"level",1},{"weapon",0}};
   World original(pvf,assets);configure(original,assets);Progression progress(catalog);store.apply(0,original,progress);kaizen(original,pvf);ticks(original,120);
   original.player.x=original.player.px=15000;const auto oldOwner=original.monsters[0].handle;
   const auto cooldown=original.sourceMonsterCooldownCheckpoint(oldOwner);
   check(!cooldown.is_null()&&cooldown.at("rows")[0].at("index")==3,"Executed source teleport retains authored slot3 cooldown on the actual actor");
   store.capture(0,original,progress);store.data["characters"][0]["region_session"]=session.save(original,"dungeon");store.save();
   const auto saved=store.data["characters"][0];const auto &region=saved.at("region_session");const auto &bundle=region.at("room_states").at(session.run.current)[0].at("source_action_cooldowns");
   check(bundle.at("commit_generation")==store.generation()&&saved.at("simulation").at("random")==original.randomStreams().snapshot(),
    "Actual disk commit binds room cooldown and simulation RNG to one immutable CharacterStore generation");
   store.close();CharacterStore recovered(directory,"source-ai-character-test");World resumed(pvf,assets);configure(resumed,assets);Progression resumedProgress(catalog);
   recovered.apply(0,resumed,resumedProgress);RegionSession loaded;check(loaded.load(recovered.data["characters"][0]["region_session"],catalog),"Actual saved legal DGN topology reloads before actor restoration");
   plane(resumed);check(loaded.restore(resumed),"RegionSession restores actor cooldowns only after new room handles exist");
   restoreSessionPlayer(resumed,recovered.data["characters"][0]["region_session"]["player"]);
   check(resumed.monsters[0].handle!=oldOwner&&resumed.sourceMonsterCooldownCheckpoint(resumed.monsters[0].handle).at("rows")==cooldown.at("rows"),
    "Reload remaps owner incarnation and preserves source cooldown remaining time");
   const auto trace=[](const World &w){return Json{{"tick",w.tick},{"x",w.monsters[0].x},{"y",w.monsters[0].y},{"random",w.randomStreams().snapshot()},
    {"cooldown",w.sourceMonsterCooldownCheckpoint(w.monsters[0].handle).is_null()?Json():w.sourceMonsterCooldownCheckpoint(w.monsters[0].handle).at("rows")}};};
   for(int i=0;i<720;++i){ticks(original,1);ticks(resumed,1);check(trace(original)==trace(resumed),"Actual post-load ticks preserve source action decision/cooldown and world RNG without replaying stay OnSet");}
   check(sourceExecutions(original)==2&&sourceExecutions(resumed)==1,"Both World continuations execute the next actual teleport after the original authored cooldown expires");
   auto beforeLive=normalized(resumed);std::vector<Json> invalid;
   auto bad=saved;bad["simulation"]["source_monster_think"]["difficulty"]="../easy";invalid.push_back(bad);
   bad=saved;bad["region_session"]["room_states"][session.run.current][0]["source_action_cooldowns"]["commit_generation"]=0;invalid.push_back(bad);
   bad=saved;bad["region_session"]["room_states"][session.run.current][0]["source_action_cooldowns"]["source"]["member_sha256"]="bad";invalid.push_back(bad);
   bad=saved;bad["region_session"]["room_states"][session.run.current][0]["source_action_cooldowns"]["rows"][0]["remaining_ms"]=10001;invalid.push_back(bad);
   for(const auto &candidate:invalid){recovered.data["characters"][0]=candidate;check(rejects([&]{recovered.apply(0,resumed,resumedProgress);})&&normalized(resumed)==beforeLive,
    "Malformed source config/cooldown identity/time/generation fails before cancelling the live World");}
   recovered.close();out["samples"]["save_directory"]=directory.u8string();
  }
  out["status"]="pass";out["count"]=out["checks"].size();writeJson(reportRoot/"monster-action-ai.json",out);return out;
 }catch(const std::exception &e){out["status"]="fail";out["count"]=out["checks"].size();out["error"]=e.what();writeJson(reportRoot/"monster-action-ai.json",out);
  writeJson(reportRoot/("monster-action-ai-failed-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".json"),out);throw;}
}
} // namespace dnf
