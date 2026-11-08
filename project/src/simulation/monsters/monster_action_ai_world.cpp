#include "dnf/combat.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/monster_behavior.hpp"
#include "dnf/monster_action_ai.hpp"
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
void append(Json &rows,Json row) {
 rows.push_back(std::move(row));if(rows.size()>256)rows.erase(rows.begin(),rows.begin()+std::ptrdiff_t(rows.size()-256));
}
bool validDifficulty(const std::string &s) {return !s.empty()&&s.find_first_not_of("abcdefghijklmnopqrstuvwxyz_")==std::string::npos;}
bool boundedInteger(const Json &v,int64_t low,int64_t high) {
 if(!v.is_number_integer())return false;
 if(v.is_number_unsigned())return v.get<uint64_t>()<=uint64_t(high)&&v.get<uint64_t>()>=uint64_t(std::max<int64_t>(low,0));
 const auto n=v.get<int64_t>();return n>=low&&n<=high;
}
bool sourceActionBusy(const ActWorldHost &host,EntityHandle owner,const MonsterActionAiBinding &binding) {
 for(const auto &[id,instance]:host.instances())if(instance.owner==owner&&instance.status==ActInstanceStatus::Running&&instance.program) {
  const auto &path=instance.program->source.memberPath;
  if(path==binding.stayAction||path==binding.moveAction)continue;
  if(!instance.pending.empty()||!instance.program->motion||instance.program->motion->loop)return true;
  uint64_t end=0;for(auto duration:instance.program->motion->frameDurationsMs) {
   if(duration<0||uint64_t(duration)>(UINT64_MAX-end)/1000)throw std::runtime_error("Invalid source action duration");end+=uint64_t(duration)*1000;
  }
  if(instance.animationUs<end)return true;
 }
 return false;
}
Json savedMovement(const MonsterSourceMovement &movement) {
 return {{"policy","40jp-destination-axis-movement-v1"},{"destination",movement.destination},
  {"method",movement.method},{"offset",{movement.offsetX,movement.offsetY}},{"side",{movement.sideX,movement.sideY}},{"evidence",movement.evidence}};
}
}
void World::configureMonsterActionAi(std::string difficulty) {
 difficulty=normalize(difficulty);if(!validDifficulty(difficulty))throw std::invalid_argument("Explicit source monster AI difficulty required");
 if(!actHost_)throw std::logic_error("Source monster think needs ACT service");
 monsterActionAiEnabled_=true;monsterActionAiDifficulty_=std::move(difficulty);monsterActionAiSources_.clear();monsterSourceMovements_.clear();
 append(monsterActionAiDiagnostics_,{{"kind","monster_action_ai_enabled"},{"difficulty",monsterActionAiDifficulty_},{"policy",monsterActionAiPolicy()}});
}
void World::prepareMonsterActionAiBoundary() {
 if(!monsterActionAiEnabled_||!actHost_||!combat||player.dead||freezeAi||(debugOverrides_.enabled&&debugOverrides_.pauseAi))return;
 std::vector<EntityHandle> owners;
 for(const auto &actor:monsters)if(actor.handle&&!actor.dead&&actor.life==ActorLife::Alive&&explorationAllowsSourceActions(actor))owners.push_back(actor.handle);
 for(auto at=monsterSourceMovements_.begin();at!=monsterSourceMovements_.end();)
  if(!static_cast<const World *>(this)->resolveActor(at->first))at=monsterSourceMovements_.erase(at);else ++at;
 for(const auto owner:owners) {
  const auto *actor=static_cast<const World *>(this)->resolveActor(owner);if(!actor)continue;
  const auto key=normalize(actor->monsterPath)+":"+monsterActionAiDifficulty_;
  auto found=monsterActionAiSources_.find(key);
  if(found==monsterActionAiSources_.end()) {
   MonsterActionAiBinding binding;binding.actorId=actor->id;binding.sourceId=actor->sourceId;binding.monster=normalize(actor->monsterPath);
   Json receipt={{"kind","monster_action_ai_source"},{"monster",binding.monster},{"difficulty",monsterActionAiDifficulty_}};
   try {
    const auto mob=pvf_.script(binding.monster);binding.routes=selectMonsterActionAiRoutes(pvf_,mob,monsterActionAiDifficulty_);receipt["routes"]=binding.routes.json();
    if(binding.routes.configured&&binding.routes.ok) {
     // The cache is source/difficulty scoped. It contains no actor pointer or
     // runtime handle, and cannot restore an old incarnation.
     receipt["compilations"]=Json::array();
     for(size_t i=0;i<3;++i){const auto c=compileMonsterActionAi(pvf_,pvf_.script(binding.routes.paths[i+1]));binding.programs[i]=c.program;receipt["compilations"].push_back(c.json());}
     const auto stay=selectMonsterAction(pvf_,mob,"stay"),move=selectMonsterAction(pvf_,mob,"move");
     if(stay.ok&&stay.engine==MonsterActionEngine::Act)binding.stayAction=stay.resolvedPath;
     if(move.ok&&move.engine==MonsterActionEngine::Act)binding.moveAction=move.resolvedPath;
     size_t terms=0;
     for(const auto &f:mob.fields)if(normalize(f.tag)=="[think term]") {
      if(++terms>1||f.values.size()!=1||!boundedInteger(f.values[0],1,60000))throw std::runtime_error("ambiguous/invalid source think term");binding.thinkMs=f.values[0].get<int64_t>();
     }
     receipt["think_ms"]=binding.thinkMs;receipt["think_classification"]=terms?"source think term":"inferred missing-source default 500ms";
     binding.ready=bool(binding.programs[1]);
     if(!binding.ready)receipt["blocked"]= "Action.ai grammar is unsupported";
    }
   }catch(const std::exception &e){receipt["error"]=e.what();}
   receipt["ready_action"]=binding.ready;receipt["whole_ai_complete"]=false;
   append(monsterActionAiDiagnostics_,std::move(receipt));found=monsterActionAiSources_.emplace(key,std::move(binding)).first;
  }
  const auto &binding=found->second;if(!binding.ready)continue;
  // Aligned source-time phases are reconstructed from the saved simulation
  // clock. There is no hidden wall-clock deadline to reroll after restore.
  const auto ms=nowMs();const auto previous=tick?int64_t(FixedStepClock::millisecondsAtTick(uint64_t(tick-1))):-1;
  if(tick&&ms/binding.thinkMs==previous/binding.thinkMs)continue;
  // A temporary stun must not accumulate one deferred marker per think phase.
  // Do not advance a hidden deadline; the next legal source-time phase wins.
  if(statusStunned(owner)||actor->hitStopped||actor->capturedBy>=0||actor->recovery!=0||nowMs()<actor->stunUntil)continue;
  if(std::any_of(sourceActionRequests_.begin(),sourceActionRequests_.end(),[&](const SourceActionRequest &r){return r.owner==owner&&r.state=="_source_think";}))continue;
  if(sourceActionRequests_.size()>=1024)throw std::overflow_error("Source monster think queue exceeded");
  sourceActionRequests_.push_back({owner,"_source_think",0});
 }
}
std::optional<World::SourceActionRequest> World::prepareMonsterActionAiDecision(EntityHandle owner) {
 const auto *actor=static_cast<const World *>(this)->resolveActor(owner);
 if(!actor||!monsterActionAiEnabled_||!actHost_)return std::nullopt;
 const auto found=monsterActionAiSources_.find(normalize(actor->monsterPath)+":"+monsterActionAiDifficulty_);
 if(found==monsterActionAiSources_.end()||!found->second.ready)return std::nullopt;
 const auto &binding=found->second;
 // A source attack keeps ownership until its authored non-loop motion and
 // pending calls end. Looping attacks need a source cleanup or explicit gate.
 if(sourceActionBusy(*actHost_,owner,binding))return std::nullopt;
 const auto actorId=actor->id;const auto mob=pvf_.script(actor->monsterPath);
 MonsterActionAiContext context;context.owner=owner;context.target=player.handle;context.direction=actor->dir;
 context.ownerPosition={actor->x,actor->y,actor->z};context.targetPosition={player.x,player.y,player.z};
 context.cooldown=[&](int index)->std::optional<bool> {
  const auto route=selectMonsterAction(pvf_,mob,"attack",index);
  if(!route.ok||route.engine!=MonsterActionEngine::Act)return std::nullopt;
  const auto cd=sourceActionCooldowns_.find({owner,index});return cd!=sourceActionCooldowns_.end()&&cd->second>nowMs();
 };
 auto random=random_;auto &stream=random.stream(RandomDomain::Ai,0);
 const auto action=evaluateMonsterActionAi(*binding.programs[1],context,stream);
 Json receipt={{"kind","monster_action_ai_decision"},{"tick",tick},{"actor",actorId},{"owner",owner.json()},
  {"action",action.json()},{"whole_ai_complete",false}};
 if(!action.ok||!action.returned||!action.candidateRandom){append(monsterActionAiDiagnostics_,std::move(receipt));return std::nullopt;}
 stream=*action.candidateRandom;
 SourceActionRequest request{owner,"attack",*action.returned};
 if(*action.returned<0) {
  auto movements=monsterSourceMovements_;movements.erase(owner);
  // Destination enums come from the current scripts. Their limited consumer
  // below is an explicitly classified cross-version reconstruction.
  receipt["movement"]={{"status","unavailable"},{"destination_source",binding.routes.paths[1]},{"move_method_source",binding.routes.paths[3]}};
  if(binding.programs[0]&&binding.programs[2]) {
   const auto destination=evaluateMonsterActionAi(*binding.programs[0],context,stream);
   receipt["movement"]["destination"]=destination.json();
   const auto movementRandom=destination.ok&&destination.candidateRandom?*destination.candidateRandom:stream;
   const auto method=evaluateMonsterActionAi(*binding.programs[2],context,movementRandom);
   receipt["movement"]["method"]=method.json();
   if(destination.ok&&method.ok&&destination.returned&&method.returned) {
    auto plan=readMonsterSourceMovement(pvf_,mob,actor->sourceStats.value("level",1),*destination.returned,*method.returned);
    receipt["movement"]["plan"]=plan.evidence;
    receipt["movement"]["status"]=plan.ready?"source_movement_scheduled":"unsupported_monster_destination_or_move_method";
    receipt["movement"]["returned_destination"]=*destination.returned;
    receipt["movement"]["returned_move_method"]=*method.returned;
    if(plan.ready&&method.candidateRandom) {
     auto movementStream=*method.candidateRandom;
     plan.sideX=player.x>=actor->x?-1:1;plan.sideY=player.y>=actor->y?-1:1;
     if(plan.destination==11) {
      plan.offsetX=double(movementStream.bounded(uint32_t(plan.radiusX)*2+1))-plan.radiusX;
      plan.offsetY=double(movementStream.bounded(uint32_t(plan.radiusY)*2+1))-plan.radiusY;
     }
     movements[owner]=plan;
     stream=movementStream;
     receipt["movement"]["offset"]={plan.offsetX,plan.offsetY};
    }
   }
  }
  // Unsupported movement keeps its candidate RNG private. Supported movement
  // publishes one source decision and advances at the fixed simulation rate.
  auto diagnostics=monsterActionAiDiagnostics_;append(diagnostics,std::move(receipt));
  random_=std::move(random);monsterSourceMovements_=std::move(movements);monsterActionAiDiagnostics_=std::move(diagnostics);return std::nullopt;
 }
 const auto route=selectMonsterAction(pvf_,mob,"attack",request.index);
 if(!route.ok||route.engine!=MonsterActionEngine::Act) {
  receipt["blocked"]="selected source attack route unavailable";receipt["route"]=route.json();append(monsterActionAiDiagnostics_,std::move(receipt));return std::nullopt;
 }
 request.aiRandom=stream;request.aiTrace=std::move(receipt);
 // prepareSourceActionBoundary publishes aiRandom only with successful bind.
 return request;
}
void World::advanceMonsterSourceMovement(Actor &actor,int64_t deltaMs) {
 // Called after px/py and the shared hit/recovery lifecycle, at the normal
 // movement boundary. No host bind or actor-vector publication occurs here.
 if(!monsterActionAiEnabled_||!actHost_||!combat||player.dead||freezeAi||
    (debugOverrides_.enabled&&debugOverrides_.pauseAi)||actor.dead||actor.life!=ActorLife::Alive||
    actor.hitStopped||actor.capturedBy>=0||actor.recovery!=0||nowMs()<actor.stunUntil||
    statusStunned(actor.handle)||!explorationAllowsSourceActions(actor)||actHost_->controlsMovement(actor.handle))return;
 const auto found=monsterActionAiSources_.find(normalize(actor.monsterPath)+":"+monsterActionAiDifficulty_);
 if(found==monsterActionAiSources_.end()||!found->second.ready||sourceActionBusy(*actHost_,actor.handle,found->second))return;
 const auto movement=monsterSourceMovements_.find(actor.handle);if(movement==monsterSourceMovements_.end())return;
 const auto &binding=found->second;
 const auto step=planMonsterMovement(movement->second,{actor.x,actor.y},{player.x,player.y},actor.dir,deltaMs,player.dir);
 const auto oldX=actor.x,oldY=actor.y;actor.dir=step.direction;
 if(canWalk(actor.x+step.dx,actor.y))actor.x+=step.dx;
 if(canWalk(actor.x,actor.y+step.dy))actor.y+=step.dy;
 const bool moved=std::abs(actor.x-oldX)>1e-8||std::abs(actor.y-oldY)>1e-8;
 const auto &desired=moved?binding.moveAction:binding.stayAction;
 bool already=false;for(const auto &[id,instance]:actHost_->instances())if(instance.owner==actor.handle&&
  instance.status==ActInstanceStatus::Running&&instance.program&&instance.program->source.memberPath==desired)already=true;
 if(!desired.empty()&&!already&&sourceActionRequests_.size()<1024&&
    std::none_of(sourceActionRequests_.begin(),sourceActionRequests_.end(),[&](const SourceActionRequest &r){return r.owner==actor.handle&&r.state!="_source_think";}))
  sourceActionRequests_.push_back({actor.handle,moved?"move":"stay",0});
}
Json World::monsterActionAiState()const {
 Json movements=Json::array();for(const auto &[owner,movement]:monsterSourceMovements_)
  movements.push_back({{"owner",owner.json()},{"movement",savedMovement(movement)}});
 return {{"enabled",monsterActionAiEnabled_},{"difficulty",monsterActionAiDifficulty_},{"policy",monsterActionAiPolicy()},
  {"source_bindings",monsterActionAiSources_.size()},{"movements",movements},{"diagnostics",monsterActionAiDiagnostics_}};
}
Json World::monsterActionAiCheckpoint()const {
 return {{"schema",1},{"policy","inferred-source-monster-think-sequence-v1"},{"enabled",monsterActionAiEnabled_},
  {"difficulty",monsterActionAiDifficulty_},{"instance_ids",sourceActionInstanceIds_.snapshot()}};
}
void World::validateMonsterActionAiCheckpoint(const Json &saved)const {
 (void)prepareMonsterActionAiRestore(saved);
}
MonsterActionAiRestore World::prepareMonsterActionAiRestore(const Json &saved)const {
 MonsterActionAiRestore out;out.enabled=monsterActionAiEnabled_;out.difficulty=monsterActionAiDifficulty_;out.instances=sourceActionInstanceIds_;
 if(saved.is_null())return out;
 if(!saved.is_object()||saved.at("schema")!=1||saved.at("policy")!="inferred-source-monster-think-sequence-v1"||
    !saved.at("enabled").is_boolean()||!saved.at("difficulty").is_string())
  throw std::invalid_argument("Invalid source monster think checkpoint");
 out.enabled=saved.at("enabled").get<bool>();out.difficulty=saved.at("difficulty").get<std::string>();
 out.instances.restore(saved.at("instance_ids"));out.instances.merge(sourceActionInstanceIds_);
 if(out.enabled&&(!actHost_||!validDifficulty(out.difficulty)))throw std::invalid_argument("Saved source monster think service unavailable");
 return out;
}
void World::publishMonsterActionAiRestore(MonsterActionAiRestore &&state)noexcept {
 monsterActionAiEnabled_=state.enabled;monsterActionAiDifficulty_=std::move(state.difficulty);
 sourceActionInstanceIds_=std::move(state.instances);
 monsterActionAiSources_.clear();monsterSourceMovements_.clear();monsterActionAiDiagnostics_=Json::array();
}
Json World::sourceMonsterCooldownCheckpoint(EntityHandle owner)const {
 const auto *actor=resolveActor(owner);if(!actor||actor==&player||actor->dead||actor->life!=ActorLife::Alive)return Json();
 Json rows=Json::array();
 for(const auto &[key,until]:sourceActionCooldowns_)if(key.first==owner&&until>nowMs())
  rows.push_back({{"index",key.second},{"remaining_ms",until-nowMs()}});
 const auto movement=monsterSourceMovements_.find(owner);
 if(rows.empty()&&movement==monsterSourceMovements_.end())return Json();
 Json result={{"schema",1},{"policy","source-monster-action-cooldowns-v1"},{"commit_generation",0},
  {"source",makeSourceRef(pvf_,actor->monsterPath).json()},{"rows",rows}};
 if(movement!=monsterSourceMovements_.end())result["movement"]=savedMovement(movement->second);
 return result;
}
std::map<int,int64_t> World::prepareSourceMonsterCooldownRestore(const Actor &actor,const Json &saved,int64_t ms)const {
 std::map<int,int64_t> out;if(saved.is_null())return out;
 if(ms<0||actor.monsterPath.empty()||actor.dead||actor.life!=ActorLife::Alive||!saved.is_object()||
    saved.at("schema")!=1||saved.at("policy")!="source-monster-action-cooldowns-v1"||
    !saved.at("rows").is_array()||saved.at("rows").size()>1024||!saved.at("commit_generation").is_number_integer()||
    (!saved.at("commit_generation").is_number_unsigned()&&saved.at("commit_generation").get<int64_t>()<0))
  throw std::invalid_argument("Invalid source monster cooldown bundle");
 const auto source=makeSourceRef(pvf_,actor.monsterPath).json();
 if(saved.at("source")!=source)throw std::invalid_argument("Source monster cooldown identity mismatch");
 (void)prepareSourceMonsterMovementRestore(actor,saved);
 for(const auto &row:saved.at("rows")) {
  if(!row.is_object()||!boundedInteger(row.at("index"),0,INT32_MAX)||!boundedInteger(row.at("remaining_ms"),1,INT64_MAX-ms))
   throw std::invalid_argument("Invalid saved source monster cooldown row");
  const auto index=row.at("index").get<int>();const auto route=selectMonsterAction(pvf_,pvf_.script(actor.monsterPath),"attack",index);
  const auto remaining=row.at("remaining_ms").get<int64_t>();
  if(!route.ok||route.engine!=MonsterActionEngine::Act||!route.cooldownMs||remaining>*route.cooldownMs)
   throw std::invalid_argument("Saved cooldown differs from source action route");
  if(!out.emplace(index,ms+remaining).second)throw std::invalid_argument("Repeated saved source monster cooldown");
 }
 return out;
}
std::optional<MonsterSourceMovement> World::prepareSourceMonsterMovementRestore(const Actor &actor,const Json &saved)const {
 if(saved.is_null()||!saved.contains("movement"))return std::nullopt;
 if(actor.monsterPath.empty()||actor.dead||actor.life!=ActorLife::Alive||!saved.is_object()||
    saved.at("source")!=makeSourceRef(pvf_,actor.monsterPath).json())throw std::invalid_argument("Saved monster movement source mismatch");
 const auto &movement=saved.at("movement");
 if(!movement.is_object()||movement.at("policy")!="40jp-destination-axis-movement-v1"||
    !boundedInteger(movement.at("destination"),0,19)||!boundedInteger(movement.at("method"),0,0))
  throw std::invalid_argument("Invalid saved monster movement adapter");
 auto plan=readMonsterSourceMovement(pvf_,pvf_.script(actor.monsterPath),actor.sourceStats.value("level",1),
  movement.at("destination").get<int>(),movement.at("method").get<int>());
 const auto &offset=movement.at("offset");
 if(!offset.is_array()||offset.size()!=2||!offset[0].is_number()||!offset[1].is_number())throw std::invalid_argument("Invalid saved movement offset");
 plan.offsetX=offset[0].get<double>();plan.offsetY=offset[1].get<double>();
 if(!std::isfinite(plan.offsetX)||!std::isfinite(plan.offsetY)||std::floor(plan.offsetX)!=plan.offsetX||std::floor(plan.offsetY)!=plan.offsetY||
    std::abs(plan.offsetX)>plan.radiusX||std::abs(plan.offsetY)>plan.radiusY)throw std::invalid_argument("Saved movement offset outside source range");
 const auto &side=movement.at("side");
 if(!side.is_array()||side.size()!=2||!boundedInteger(side[0],-1,1)||!boundedInteger(side[1],-1,1)||
    side[0]==0||side[1]==0)throw std::invalid_argument("Invalid saved movement side");
 plan.sideX=side[0].get<int>();plan.sideY=side[1].get<int>();
 if(!plan.ready||savedMovement(plan)!=movement)throw std::invalid_argument("Saved monster movement differs from current source");
 return plan;
}
} // namespace dnf
