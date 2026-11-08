#include "dnf/dungeon_difficulty.hpp"
#include "dnf/monster_action_ai.hpp"
#include <algorithm>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
void issue(Json &rows,const std::string &reason,const SourceRef &source={}) {
 rows.push_back({{"kind","unsupported_monster_action_ai"},{"reason",reason},{"source",source.json()}});
}
bool integer(const Json &v,int64_t low,int64_t high) {
 if(!v.is_number())return false;const double d=v.get<double>();
 return std::isfinite(d)&&std::floor(d)==d&&d>=double(low)&&d<=double(high);
}
void verify(const Pvf &pvf,const Script &s) {
 if(s.rawBytes.size()<2||s.rawBytes.size()>131072||(s.rawBytes.size()-2)%5||s.fields.empty()||s.fields.size()>8192||
    s.source.value("package_identity",std::string())!=pvf.identity()||!pvf.has(s.path))throw std::runtime_error("foreign, malformed or over-budget source");
 const auto original=pvf.script(s.path);
 if(original.rawBytes!=s.rawBytes||original.tokens!=s.tokens||original.fields.size()!=s.fields.size())throw std::runtime_error("source identity differs from PVF");
 for(size_t i=0;i<s.fields.size();++i)if(original.fields[i].tag!=s.fields[i].tag||original.fields[i].values!=s.fields[i].values||original.fields[i].offset!=s.fields[i].offset)
  throw std::runtime_error("ordered source fields differ from PVF");
}
struct Compiler {
 const Pvf &pvf;const Script &script;MonsterActionAiProgram &program;size_t at=0;
 SourceRef source(size_t ordinal)const {
  if(ordinal>=script.fields.size())return makeSourceRef(pvf,script.path,script.rawBytes.size(),0,ordinal,"monster_action_ai/end");
  const auto &f=script.fields[ordinal];const auto end=ordinal+1<script.fields.size()?script.fields[ordinal+1].offset:script.rawBytes.size();
  return makeSourceRef(pvf,script.path,f.offset,end-f.offset,ordinal,"monster_action_ai/statement");
 }
 const Field &take(const std::string &tag,bool empty=true) {
  if(at>=script.fields.size()||normalize(script.fields[at].tag)!=tag||(empty&&!script.fields[at].values.empty()))throw std::runtime_error("expected "+tag+" at field "+std::to_string(at));
  return script.fields[at++];
 }
 std::vector<size_t> sequence(size_t depth,const std::set<std::string> &end) {
  if(depth>32)throw std::runtime_error("AI nesting exceeds budget");std::vector<size_t> out;
  while(at<script.fields.size()&&!end.count(normalize(script.fields[at].tag))) {
   if(program.nodes.size()>=2048)throw std::runtime_error("AI statement budget exceeded");
   const auto index=program.nodes.size();program.nodes.push_back({});out.push_back(index);
   MonsterActionAiNode node;node.source=source(at);
   if(normalize(script.fields[at].tag)=="[return]") {
    const auto &v=take("[return]",false).values;
    if(v.size()!=1||!integer(v[0],-1,INT32_MAX))throw std::runtime_error("return needs one integral index or -1");node.value=v[0].get<int>();
   } else {
    take("[think]");node.source=source(at);const auto &f=take("[void]",false);const auto &v=f.values;
    if(v.empty()||!v[0].is_string())throw std::runtime_error("AI void needs named function");const auto fn=v[0].get<std::string>();
    if(fn=="is the skill in cooltime()"&&v.size()==2&&integer(v[1],0,INT32_MAX)) {
     node.kind=MonsterActionAiNode::Kind::Cooldown;node.value=v[1].get<int>();
    } else if(fn=="is target in attack area()"&&v.size()==5) {
     node.kind=MonsterActionAiNode::Kind::Area;
     for(size_t i=0;i<4;++i){if(!v[i+1].is_number())throw std::runtime_error("nonnumeric target area");const auto n=v[i+1].get<double>();
      if(!std::isfinite(n)||n<0||n>1000000)throw std::runtime_error("invalid target-area range");node.area[i]=n;}
    } else if(fn=="check random()"&&v.size()==3&&integer(v[1],0,UINT32_MAX)&&integer(v[2],1,UINT32_MAX)&&v[1].get<uint64_t>()<=v[2].get<uint64_t>()) {
     node.kind=MonsterActionAiNode::Kind::Chance;node.numerator=v[1].get<uint32_t>();node.denominator=v[2].get<uint32_t>();
    } else throw std::runtime_error("unsupported AI void function/operands: "+fn);
    take("[true]");node.yes=sequence(depth+1,{"[false]","[/think]"});
    take("[false]");node.no=sequence(depth+1,{"[/think]"});take("[/think]");
   }
   program.nodes[index]=std::move(node);
  }
  return out;
 }
 void compile() {
  const auto &header=take("[ai pattern]",false);
  if(header.values.size()>1||(!header.values.empty()&&!header.values[0].is_string()))throw std::runtime_error("invalid AI header");
  program.sequence=sequence(1,{"[/ai pattern]"});take("[/ai pattern]");
  if(at!=script.fields.size())throw std::runtime_error("trailing AI fields");
 }
};
}
Json monsterActionAiPolicy() {
 return {{"id","inferred-source-monster-think-sequence-v1"},{"classification","inferred_beta"},
  {"sequence","ordered statements; return ends the complete evaluation; all source branches preflighted"},
  {"area","owner-facing XY front/back/up/down inclusive rectangle; selection only, not attack collision"},
  {"chance","saved world-scoped PCG32 AI stream; bounded integral-ratio rejection"},
  {"scheduler","source think term aligned to fixed simulation boundary including initial phase0; missing term uses explicit inferred500ms; no render clock"},
  {"movement","40jp-destination-axis-movement-v1: source DestinationSelect 0/1/2/11/19 and MoveMethod 0; unknown values diagnosed; existing 1031 character per-mille/base180 conversion reused explicitly"},
  {"native_phase_rng_and_caller","unrecovered"},{"whole_ai_complete",false}};
}
MonsterSourceMovement readMonsterSourceMovement(const Pvf &pvf,const Script &mob,int level,int destination,int method) {
 MonsterSourceMovement out;out.destination=destination;out.method=method;
 out.evidence={{"policy","40jp-destination-axis-movement-v1"},{"classification","cross_version_inference"},
  {"monster",makeSourceRef(pvf,mob.path).json()},{"destination",destination},{"method",method},{"level",level},
  {"native_reference","40JP combat_core.cpp sub_4DF2D0 0x4DF2D0; per-axis destination and stop"},
  {"speed_conversion","MOB endpoint interpolation; reuse current 1031 character walk180 * sourceMove/1000, Y ratio0.65. MOB native scale unverified"},
  {"retained_fields",Json::array()}};
 try {
  verify(pvf,mob);
  if(level<1||level>10000)throw std::runtime_error("movement needs resolved source level");
  if((destination<0||destination>2)&&destination!=11&&destination!=19)throw std::runtime_error("unsupported destination");
  if(method!=0)throw std::runtime_error("unsupported move method; no fabricated dash speed");
  const Field *speed=nullptr,*levels=nullptr,*distance=nullptr,*range=nullptr,*fixed=nullptr;
  for(size_t i=0;i<mob.fields.size();++i) {
   const auto &f=mob.fields[i];const auto tag=normalize(f.tag);const Field **slot=nullptr;
   if(tag=="[move speed]")slot=&speed;else if(tag=="[level]")slot=&levels;
   else if(tag=="[keep distance with target]")slot=&distance;else if(tag=="[keep range distance with target]")slot=&range;else if(tag=="[fix direction]")slot=&fixed;
   if(!slot)continue;
   if(*slot)throw std::runtime_error("repeated movement field: "+tag);*slot=&f;
   out.evidence["retained_fields"].push_back({{"tag",f.tag},{"values",f.values},
    {"source",makeSourceRef(pvf,mob.path,f.offset,0,i,"monster_movement/field").json()}});
  }
  if(!speed||(speed->values.size()!=1&&speed->values.size()!=2))throw std::runtime_error("missing/malformed source move speed");
  for(const auto &v:speed->values)if(!v.is_number()||!std::isfinite(v.get<double>())||v.get<double>()<0||v.get<double>()>1000000)
   throw std::runtime_error("invalid move speed");
  double value=speed->values[0].get<double>();
  if(speed->values.size()==2&&speed->values[0]!=speed->values[1]) {
   if(!levels||levels->values.size()!=2||!integer(levels->values[0],1,10000)||!integer(levels->values[1],1,10000)||
      levels->values[1].get<int>()<levels->values[0].get<int>())throw std::runtime_error("speed endpoints need ordered source level endpoints");
   const auto lo=levels->values[0].get<int>(),hi=levels->values[1].get<int>();
   const double ratio=hi==lo?0:std::clamp((double(level)-lo)/(hi-lo),0.0,1.0);
   value+=(speed->values[1].get<double>()-value)*ratio;
  }
  if(destination==1||destination==19) {
   if(!distance||distance->values.size()!=1||!distance->values[0].is_number())throw std::runtime_error("keep-distance source field missing");
   out.keepDistance=distance->values[0].get<double>();
   if(!std::isfinite(out.keepDistance)||out.keepDistance<0||out.keepDistance>1000000)throw std::runtime_error("invalid keep distance");
  }
  if(destination==11) {
   if(!range||range->values.size()!=4)throw std::runtime_error("range-distance source field missing");
   for(const auto &v:range->values)if(!integer(v,0,1000000))throw std::runtime_error("unsupported range-distance operand");
   out.keepDistance=range->values[0].get<double>();out.keepY=range->values[1].get<double>();
   out.radiusX=range->values[2].get<double>();out.radiusY=range->values[3].get<double>();
  }
  if(fixed) {
   if(fixed->values.empty()||fixed->values.size()>2||!integer(fixed->values[0],0,1))throw std::runtime_error("unsupported fix-direction shape");
   if(fixed->values[0].get<int>()&&fixed->values.size()==1)out.fixedDirection=2; // preserve spawn-facing
   else if(fixed->values[0].get<int>()) {
    if(!fixed->values[1].is_string())throw std::runtime_error("unsupported fixed direction");
    const auto direction=normalize(fixed->values[1].get<std::string>());
    if(direction=="[left]")out.fixedDirection=-1;else if(direction=="[right]")out.fixedDirection=1;
    else throw std::runtime_error("unknown fixed direction");
   }
  }
  out.speed=value*180.0/1000.0;out.ready=true;out.evidence["world_speed"]=out.speed;
 }catch(const std::exception &e){out.evidence["blocked"]=e.what();}
 return out;
}
MonsterMovementStep planMonsterMovement(const MonsterSourceMovement &plan,
 const std::array<double,2> &owner,const std::array<double,2> &target,int facing,int64_t deltaMs,int targetFacing) {
 MonsterMovementStep out;out.direction=facing;
 if(!plan.ready||deltaMs<0||deltaMs>1000||(facing!=1&&facing!=-1)||(targetFacing!=1&&targetFacing!=-1))return out;
 for(const auto &p:{owner,target})for(auto v:p)if(!std::isfinite(v))return out;
 const double difference=target[0]-owner[0];
 out.direction=plan.fixedDirection==2?facing:plan.fixedDirection?plan.fixedDirection:(difference==0?facing:(difference>0?1:-1));
 double goalX=target[0],goalY=target[1];
 if(plan.destination==1)goalX+=(difference>=0?-1:1)*plan.keepDistance;
 else if(plan.destination==11) {
  goalX+=plan.sideX*plan.keepDistance+plan.offsetX;
  goalY+=plan.sideY*plan.keepY+plan.offsetY;
 }
 else if(plan.destination==19)goalX-=targetFacing*plan.keepDistance;
 else if(plan.destination==2) {
  // A flee decision is continuous until the next authored think phase. The
  // single-player tie has a stable facing-based direction, without an RNG draw.
  goalX=owner[0]+(difference==0?-facing:(difference>0?-1:1))*plan.speed;
  const auto dy=target[1]-owner[1];goalY=owner[1]+(dy==0?0:(dy>0?-1:1))*plan.speed;
 }
 const auto bound=plan.speed*double(deltaMs)/1000;
 out.dx=std::clamp(goalX-owner[0],-bound,bound);out.dy=std::clamp(goalY-owner[1],-bound*.65,bound*.65);
 out.moving=std::abs(out.dx)>1e-8||std::abs(out.dy)>1e-8;return out;
}
Json MonsterActionAiCompilation::json()const {
 return {{"ok",ok()},{"source",program?program->source.json():Json()},
  {"nodes",program?program->nodes.size():0},{"ordered_fields",program?program->retainedFields:Json()},
  {"diagnostics",diagnostics},{"policy",monsterActionAiPolicy()}};
}
MonsterActionAiCompilation compileMonsterActionAi(const Pvf &pvf,const Script &script) {
 MonsterActionAiCompilation out;auto program=std::make_shared<MonsterActionAiProgram>();
 try {
  verify(pvf,script);program->original=script;program->source=makeSourceRef(pvf,script.path);
  Compiler compiler{pvf,script,*program};
  for(size_t i=0;i<script.fields.size();++i)program->retainedFields.push_back({{"tag",script.fields[i].tag},{"values",script.fields[i].values},{"source",compiler.source(i).json()}});
  try{compiler.compile();}catch(const std::exception &e){issue(out.diagnostics,e.what(),compiler.source(compiler.at));return out;}
  out.program=std::move(program);
 }catch(const std::exception &e){issue(out.diagnostics,e.what());}
 return out;
}
Json MonsterActionAiEvaluation::json()const {
 return {{"ok",ok},{"returned",returned?Json(*returned):Json()},{"trace",trace},{"diagnostics",diagnostics}};
}
MonsterActionAiEvaluation evaluateMonsterActionAi(const MonsterActionAiProgram &p,const MonsterActionAiContext &context,const Pcg32 &random) {
 MonsterActionAiEvaluation out;auto candidate=random;size_t steps=0,draws=0;
 try {
  if(!context.owner||!context.target||(context.direction!=1&&context.direction!=-1))throw std::runtime_error("invalid typed AI context");
  for(const auto &xyz:{context.ownerPosition,context.targetPosition})for(const auto value:xyz)if(!std::isfinite(value))throw std::runtime_error("nonfinite AI coordinate");
  const auto execute=[&](const auto &self,const std::vector<size_t> &sequence)->std::optional<int> {
   for(const auto index:sequence) {
    if(++steps>256)throw std::runtime_error("AI evaluation budget exceeded");const auto &n=p.nodes.at(index);
    Json trace={{"source",n.source.json()}};
    if(n.kind==MonsterActionAiNode::Kind::Return){trace["kind"]="return";trace["value"]=n.value;out.trace.push_back(std::move(trace));return n.value;}
    bool chosen=false;
    if(n.kind==MonsterActionAiNode::Kind::Area) {
     const auto dx=(context.targetPosition[0]-context.ownerPosition[0])*context.direction,dy=context.targetPosition[1]-context.ownerPosition[1];
     chosen=dx<=n.area[0]&&dx>=-n.area[1]&&dy>=-n.area[2]&&dy<=n.area[3];trace["kind"]="target_area";trace["local_xy"]={dx,dy};trace["source_area"]=n.area;
    } else if(n.kind==MonsterActionAiNode::Kind::Cooldown) {
     if(!context.cooldown)throw std::runtime_error("missing source-action cooldown query");const auto value=context.cooldown(n.value);
     if(!value)throw std::runtime_error("source-action cooldown index unsupported");chosen=*value;trace["kind"]="cooldown";trace["index"]=n.value;
    } else {
     const auto threshold=(uint32_t(0)-n.denominator)%n.denominator;uint32_t value;
     do{if(++draws>32)throw std::runtime_error("AI random budget exceeded");value=candidate.next();}while(value<threshold);
     chosen=value%n.denominator<n.numerator;trace["kind"]="chance";trace["sample"]=value%n.denominator;
    }
    trace["result"]=chosen;out.trace.push_back(std::move(trace));
    if(auto result=self(self,chosen?n.yes:n.no))return result;
   }
   return std::nullopt;
  };
  out.returned=execute(execute,p.sequence);
  if(!out.returned)throw std::runtime_error("AI execution reached end without authored return");
  out.candidateRandom=std::move(candidate);out.ok=true;
 }catch(const std::exception &e){issue(out.diagnostics,e.what(),p.source);}
 return out;
}
Json MonsterActionAiRoutes::json()const {return {{"configured",configured},{"ok",ok},{"difficulty",difficulty},{"paths",paths},{"source",source},{"diagnostics",diagnostics}};}
MonsterActionAiRoutes selectMonsterActionAiRoutes(const Pvf &pvf,const Script &mob,const std::string &difficulty) {
 MonsterActionAiRoutes out;out.difficulty=normalize(difficulty);
 try {
  verify(pvf,mob);
  if(out.difficulty.empty()||out.difficulty.find_first_not_of("abcdefghijklmnopqrstuvwxyz_")!=std::string::npos)throw std::runtime_error("explicit AI difficulty required");
  size_t begin=mob.fields.size(),end=mob.fields.size(),row=mob.fields.size();
  for(size_t i=0;i<mob.fields.size();++i)if(normalize(mob.fields[i].tag)=="[ai pattern]") {
   if(begin!=mob.fields.size()||!mob.fields[i].values.empty())throw std::runtime_error("repeated or malformed MOB AI block");begin=i;out.configured=true;
  }
  if(!out.configured)return out;
  for(size_t i=begin+1;i<mob.fields.size();++i)if(normalize(mob.fields[i].tag)=="[/ai pattern]"){end=i;break;}
  if(end==mob.fields.size())throw std::runtime_error("unterminated MOB AI block");
  const auto difficultySelection=resolveDungeonDifficulty(mob,out.difficulty);
  for(size_t i=begin+1;i<end;++i)if(normalize(mob.fields[i].tag)=="["+difficultySelection.selected+"]") {
   if(row!=mob.fields.size())throw std::runtime_error("repeated selected MOB difficulty");row=i;
  }
  if(row==mob.fields.size())throw std::runtime_error("selected MOB difficulty is absent");const auto &field=mob.fields[row];
  if(field.values.size()!=4||row+1>=end||normalize(mob.fields[row+1].tag)!="[/"+difficultySelection.selected+"]"||!mob.fields[row+1].values.empty())throw std::runtime_error("MOB difficulty needs complete four-path row");
  out.source={{"difficulty_selection",difficultySelection.json()},{"monster",makeSourceRef(pvf,mob.path).json()},{"row",makeSourceRef(pvf,mob.path,field.offset,mob.fields[row+1].offset-field.offset,row,"monster_action_ai/difficulty_row").json()},{"values",field.values}};
  for(size_t i=0;i<4;++i) {
   if(!field.values[i].is_string())throw std::runtime_error("nonstring AI path");const auto literal=normalize(field.values[i].get<std::string>());
   if(literal.empty()||literal.front()=='/'||literal.find(':')!=std::string::npos||literal.find('\0')!=std::string::npos||literal.size()<4||literal.substr(literal.size()-3)!=".ai")throw std::runtime_error("unsafe or missing explicit AI path");
   std::set<std::string> paths;
   for(const auto &candidate:{(std::filesystem::u8path(mob.path).parent_path()/std::filesystem::u8path(literal)).generic_u8string(),literal,"monster/"+literal}) {
    const auto path=normalize(std::filesystem::u8path(candidate).lexically_normal().generic_u8string());
    if(path==".."||path.rfind("../",0)==0)throw std::runtime_error("AI path escapes content root");if(pvf.has(path))paths.insert(path);
   }
   if(paths.size()!=1)throw std::runtime_error("absent or ambiguous AI slot "+std::to_string(i));out.paths[i]=*paths.begin();
  }
  out.ok=true;
 }catch(const std::exception &e){issue(out.diagnostics,e.what(),makeSourceRef(pvf,mob.path));}
 return out;
}
} // namespace dnf
