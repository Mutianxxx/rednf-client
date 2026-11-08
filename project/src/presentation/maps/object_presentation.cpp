#include "dnf/object_presentation.hpp"
#include "dnf/content_profile.hpp"
#include "dnf/simulation.hpp"
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
std::string relative(const std::string &parent,const std::string &literal) {
 return normalize((std::filesystem::u8path(parent).parent_path()/std::filesystem::u8path(normalize(literal))).lexically_normal().generic_u8string());
}
bool suffix(const std::string &s,const char *tail) {const std::string t=tail;return s.size()>=t.size()&&s.substr(s.size()-t.size())==t;}
ObjectParticleProgram particle(Pvf &pvf,Assets &assets,const std::string &path) {
 const auto source=pvf.script(path);ObjectParticleProgram p;p.source=path;
 p.evidence={{"source",makeSourceRef(pvf,path).json()},{"ordered_fields",Json::array()},
  {"policy","inferred-map-object-source-particle-burst-v1"},
  {"classification","source values; inferred burst selection, angular distribution and XYZ projection"}};
 int axis=-1;
 for(const auto &f:source.fields) {
  const auto tag=normalize(f.tag);p.evidence["ordered_fields"].push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});
  if(tag=="[x axis]")axis=0;else if(tag=="[y axis]")axis=1;else if(tag=="[z axis]")axis=2;
  else if(tag=="[move type]" && axis>=0 && (f.values.size()!=1||f.values[0]!="[straight line]"))throw std::runtime_error("Unsupported object PTL axis mode: "+path);
  else if(tag=="[move variable 1]"&&axis>=0) {
   if(f.values.size()!=2||!f.values[0].is_number()||!f.values[1].is_number())throw std::runtime_error("Malformed object PTL velocity");
   p.velocity[axis]={f.values[0].get<double>(),f.values[1].get<double>()};
  } else if(tag=="[gravity]")p.gravity=source.number(f.tag);
  else if(tag=="[life time]")p.lifeMs=int(source.number(f.tag));
  else if(tag=="[maximum create number]")p.count=int(source.number(f.tag));
  else if(tag=="[create area size]"&&f.values.size()==3)for(size_t i=0;i<3;++i)p.area[i]=f.values[i].get<double>();
  else if(tag=="[object]") {
   if(f.values.size()%2)throw std::runtime_error("Malformed PTL object pairs");
   for(size_t i=0;i<f.values.size();i+=2) {
    if(!f.values[i].is_string()||!f.values[i+1].is_number_integer())throw std::runtime_error("Malformed PTL ANI pair");
    const auto ani=relative(path,f.values[i].get<std::string>());
    if(!suffix(ani,".ani")||!pvf.has(ani))throw std::runtime_error("Unresolved object PTL ANI: "+ani);
    const auto a=assets.animation(ani);if(a->frames.empty())throw std::runtime_error("Empty object PTL ANI");
    for(const auto &frame:a->frames)if(!frame.image.empty())assets.pixels(frame.image,frame.imageFrame);
    p.animations.push_back(ani);
   }
  }
 }
 if(source.text("[object type]")!="[animation]"||source.number("[creation frequency]")!=-1||p.count<=0||p.count>256||p.lifeMs<=0||p.lifeMs>30000||p.animations.empty())
  throw std::runtime_error("Object PTL is outside bounded one-shot animation-burst contract: "+path);
 p.evidence["unrecovered_fields"]=Json::array({"native rotation distribution","random range consumer","display effect rate","native emitter clock"});
 return p;
}
}
void compileObjectPresentation(Pvf &pvf,Assets &assets,ObjectDefinition &d) {
 // Legacy subclass layout is version- and namespace-scoped. Source arrays stay
 // unchanged. Instance-vector positions are supported by the bounded 1031
 // A41E42/A41FFA/A42042 review; the protected base-copy edge remains inferred.
 const std::map<int,std::string> audited={
  {221,"barrel.obj"},{222,"treasurebox.obj"},{223,"actiontree1lorien.obj"},
  {224,"actiontree2lorien.obj"},{231,"actionstonepillar.obj"},
  {243,"largegrasslorien.obj"},{244,"smallgrasslorien.obj"}};
 const auto audit=audited.find(d.id);
 if(audit==audited.end()||d.source!="passiveobject/mapobject/breakableobject/"+audit->second)return;
 const auto strings=d.script.values("[string data]");
 const auto add=[&](size_t slot,std::vector<ObjectParticleProgram> &programs) {
  if(slot>=strings.size()||!strings[slot].is_string()||strings[slot].get<std::string>().empty())return;
  const auto path=relative(d.source,strings[slot].get<std::string>());
  if(!suffix(path,".ptl"))return;
  try{programs.push_back(particle(pvf,assets,path));}
  catch(const std::exception &e){d.diagnostics.push_back({{"kind","object_particle_presentation_unavailable"},{"source",path},{"error",e.what()}});}
 };
 // Breakable factory strings 0/1/2 are create/hit/destroy PTLs. Grasses
 // use their separate source factory: string0 supplies destruction particles.
 if(d.id==243||d.id==244) {
  add(0,d.destroyParticles);
  if(strings.size()>1&&strings[1].is_string())d.hitSound=strings[1].get<std::string>();
  if(strings.size()>2&&strings[2].is_string())d.destroySound=strings[2].get<std::string>();
 } else {
  add(1,d.hitParticles);add(2,d.destroyParticles);
  if(strings.size()>4&&strings[4].is_string())d.hitSound=strings[4].get<std::string>();
  if(strings.size()>5&&strings[5].is_string())d.destroySound=strings[5].get<std::string>();
  if(d.intData.size()==7)for(size_t i=0;i<3;++i)d.presentationOffset[i]=d.intData[i+3];
 }
 if(d.id==222&&strings.size()>6&&strings[6].is_string()) {
  const auto path=relative(d.source,strings[6].get<std::string>());
  if(suffix(path,".ani")&&pvf.has(path)) {
   ObjectMotion m;m.tag="[legacy destroy motion]";m.path=path;m.animation=assets.animation(path);m.raw=pvf.read(path);
   for(const auto &field:d.script.fields)if(field.tag=="[string data]"){m.offset=field.offset;break;}
   d.motions.push_back(std::move(m));
   d.diagnostics.push_back({{"kind","legacy_destroy_motion_binding"},{"source_tag","[string data]"},
    {"source_slot",6},{"source_field_offset",d.motions.back().offset},{"resolved",path},
    {"classification","inferred native factory slot binding; source ANI is preserved"}});
  }
 }
 if(!d.hitParticles.empty()||!d.destroyParticles.empty()||!d.hitSound.empty()||!d.destroySound.empty())
  d.diagnostics.push_back({{"kind","inferred_object_presentation_binding"},{"policy","inferred-1031-legacy-breakable-string-slots-v1"},
   {"source",d.source},{"note","Source PTL/ANI/sounds consumed; native source-to-instance copy, emitter distribution and legacy durability remain unrecovered"}});
}
void createObjectPresentation(ObjectInstance &i,bool destroyed) {
 if(!i.definition)return;
 const auto &programs=destroyed?i.definition->destroyParticles:i.definition->hitParticles;
 if(programs.empty())return;
 auto particles=i.visualParticles;Pcg32 random(i.randomState,13);
 const auto unit=[&](){return random.next()/4294967296.0;};
 for(const auto &p:programs)for(int n=0;n<p.count;++n) {
  if(particles.size()>=512)throw std::runtime_error("Object presentation particle budget exceeded");
  ObjectVisualParticle v;v.source=p.source;v.animation=p.animations.at(random.bounded(uint32_t(p.animations.size())));v.lifeUs=int64_t(p.lifeMs)*1000;
  const double angle=unit()*6.283185307179586;
  for(size_t axis=0;axis<3;++axis) {
   v.origin[axis]=(axis==0?i.placement.x:axis==1?i.placement.y:i.placement.z)+i.definition->presentationOffset[axis]+(unit()-.5)*p.area[axis];
   v.velocity[axis]=p.velocity[axis][0]+unit()*(p.velocity[axis][1]-p.velocity[axis][0]);
  }
  // Broad source-constrained beta burst. The source ranges/area/gravity/life
  // are retained; angular emission and Y projection are explicit inference.
  const double radial=v.velocity[0];v.velocity[0]=radial*std::cos(angle);v.velocity[1]=radial*.29*std::sin(angle);
  v.gravity=p.gravity;v.position=v.origin;particles.push_back(std::move(v));
 }
 i.randomState=uint64_t(random.next())<<32;i.randomState|=random.next();i.visualParticles=std::move(particles);
}
void advanceObjectPresentation(ObjectInstance &i,int64_t deltaUs) {
 for(auto &v:i.visualParticles) {
  v.ageUs=std::min(v.lifeUs,v.ageUs+std::min(deltaUs,v.lifeUs));const double seconds=v.ageUs/1000000.0;
  for(size_t axis=0;axis<3;++axis)v.position[axis]=v.origin[axis]+v.velocity[axis]*seconds;
  v.position[2]-=.5*v.gravity*seconds*seconds;
 }
 i.visualParticles.erase(std::remove_if(i.visualParticles.begin(),i.visualParticles.end(),[](const auto &v){return v.ageUs>=v.lifeUs||v.position[2]<0;}),i.visualParticles.end());
}
Json saveObjectPresentation(const ObjectInstance &i) {
 Json out=Json::array();for(const auto &v:i.visualParticles)out.push_back({{"source",v.source},{"animation",v.animation},{"origin",v.origin},{"position",v.position},
  {"velocity",v.velocity},{"gravity",v.gravity},{"age_us",v.ageUs},{"life_us",v.lifeUs}});return out;
}
void restoreObjectPresentation(ObjectInstance &i,const Json &rows) {
 if(!rows.is_array()||rows.size()>512)throw std::runtime_error("Invalid saved object particle array");
 std::vector<ObjectVisualParticle> particles;
 for(const auto &row:rows) {
  ObjectVisualParticle v;v.source=row.at("source");v.animation=row.at("animation");v.origin=row.at("origin").get<std::array<double,3>>();
  v.position=row.at("position").get<std::array<double,3>>();v.velocity=row.at("velocity").get<std::array<double,3>>();
  v.gravity=row.at("gravity");v.ageUs=row.at("age_us");v.lifeUs=row.at("life_us");
  bool bound=false;for(const auto *programs:{&i.definition->hitParticles,&i.definition->destroyParticles})for(const auto &p:*programs)
   if(p.source==v.source&&std::find(p.animations.begin(),p.animations.end(),v.animation)!=p.animations.end())bound=true;
  if(!bound||v.ageUs<0||v.lifeUs<=0||v.ageUs>=v.lifeUs||v.lifeUs>30000000)throw std::runtime_error("Saved object particle source/lifetime mismatch");
  for(const auto &xyz:{v.origin,v.position,v.velocity})for(double value:xyz)if(!std::isfinite(value))throw std::runtime_error("Nonfinite saved object particle coordinate");
  if(!std::isfinite(v.gravity))throw std::runtime_error("Nonfinite saved object particle gravity");
  particles.push_back(std::move(v));
 }
 i.visualParticles=std::move(particles);
}
}
