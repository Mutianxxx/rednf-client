#include "dnf/monster_equipment.hpp"
#include "dnf/content_profile.hpp"
#include <cmath>
#include <map>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
std::string canonical(const std::string &path) {
 return normalize(std::filesystem::u8path(normalize(path)).lexically_normal().generic_u8string());
}
std::string resolve(Pvf &pvf,const std::string &parent,const std::string &literal,bool equipment=false) {
 std::set<std::string> choices;
 for(const auto &candidate:{canonical((std::filesystem::u8path(parent).parent_path()/std::filesystem::u8path(literal)).generic_u8string()),
                            canonical(literal),canonical((equipment?"equipment/":"monster/")+literal)})
  if(pvf.has(candidate))choices.insert(candidate);
 if(choices.size()!=1)throw std::runtime_error((choices.empty()?"Missing":"Ambiguous")+std::string(" explicit resource: ")+parent+" -> "+literal);
 return *choices.begin();
}
bool motionTag(const std::string &tag) {
 static const std::set<std::string> tags={"[waiting motion]","[move motion]","[sit motion]",
   "[damage motion 1]","[damage motion 2]","[down motion]","[overturn motion]",
   "[jump motion]","[jumpattack motion]","[attack motion]","[etc motion]"};
 return tags.count(tag)!=0;
}
struct Slot {std::string tag;size_t index=0,offset=0;};
struct Layer {int layer=0;size_t blockOffset=0;std::map<std::string,const Field *> motions;};
struct Binding {int layer=0;size_t blockOffset=0,offset=0;std::string path;};
std::vector<Binding> select(Pvf &pvf,const Script &equ,const std::vector<Layer> &layers,const Slot &slot) {
 std::vector<Binding> result;
 for(const auto &layer:layers) {
  const auto selected=layer.motions.find(slot.tag);if(selected==layer.motions.end())continue;
  const auto &field=*selected->second;
  if(slot.index>=field.values.size())throw std::runtime_error("Equipment motion array omits selected MOB slot: "+slot.tag+" #"+std::to_string(slot.index));
  const auto &literal=field.values[slot.index];if(!literal.is_string())throw std::runtime_error("Equipment motion slot is not a string");
  if(literal.get<std::string>().empty())continue;
  const auto path=resolve(pvf,equ.path,literal.get<std::string>());
  if(path.size()<4||path.substr(path.size()-4)!=".ani")throw std::runtime_error("Equipment visual slot is not an ANI");
  result.push_back({layer.layer,layer.blockOffset,field.offset,path});
 }
 return result;
}
bool equivalent(const std::vector<Binding> &a,const std::vector<Binding> &b) {
 if(a.size()!=b.size())return false;
 for(size_t i=0;i<a.size();++i)if(a[i].layer!=b[i].layer||a[i].path!=b[i].path)return false;
 return true;
}
}
void appendMonsterEquipment(Pvf &pvf,Assets &assets,MonsterMotion &motion,const std::string &monster) {
 if(!motion.valid()||monster.empty())return;
 const auto issue=[&](const std::string &code,const std::string &reason,const std::string &resource,size_t offset) {
  motion.issues.push_back({{"kind","monster_equipment"},{"code",code},{"reason",reason},{"resource",resource},{"offset",offset}});
 };
 try {
  const auto mob=pvf.script(monster);std::vector<Slot> slots;
  // All candidates are exact resolved MOB ANI paths, including empty preceding
  // array entries in their slot identity. No cross-species or stem fallback.
  for(const auto &field:mob.fields)if(motionTag(normalize(field.tag))) {
   for(size_t index=0;index<field.values.size();++index) {
    const auto &literal=field.values[index];if(!literal.is_string()||literal.get<std::string>().empty())continue;
    try {if(resolve(pvf,mob.path,literal.get<std::string>())==motion.base->path)
      slots.push_back({normalize(field.tag),index,field.offset});}
    catch(const std::exception &){ /* unrelated malformed slots do not alias selected body */ }
   }
  }
  std::vector<std::pair<size_t,std::string>> equipment;
  for(const auto &field:mob.fields)if(normalize(field.tag)=="[equipment]") {
   motion.references.push_back({{"source",mob.path},{"offset",field.offset},{"tag",field.tag},{"values",field.values},
      {"member_source",makeSourceRef(pvf,mob.path).json()}});
   if(field.values.empty()) {issue("empty_equipment_block","Repeated empty opening tag retained; no invented entry",mob.path,field.offset);continue;}
   const auto &v=field.values;
   if(!v[0].is_number_integer()||v[0].get<int64_t>()<0||uint64_t(v[0].get<int64_t>())!=v.size()-1) {
    issue("invalid_equipment_count","Equipment count must equal its ordered literal path count",mob.path,field.offset);continue;
   }
   for(size_t i=1;i<v.size();++i) {
    if(!v[i].is_string()||v[i].get<std::string>().empty()) {
     issue("invalid_equipment_reference","Empty or nonstring EQU literal",mob.path,field.offset);continue;
    }
    equipment.emplace_back(field.offset,resolve(pvf,mob.path,v[i].get<std::string>(),true));
   }
  }
  if(equipment.empty())return;
  // compileMonsterMotion selects the first resource in its exact source field.
  // Prefer that proven binding over unrelated slots reusing the same body ANI.
  // An explicit override has no such receipt and must remain unambiguous.
  if(!motion.bindingTag.empty()) {
   const auto selected=std::find_if(slots.begin(),slots.end(),[&](const Slot &slot) {
    return slot.tag==motion.bindingTag&&slot.offset==motion.bindingOffset;
   });
   if(selected!=slots.end())slots={*selected};
  }
  if(slots.empty()) {
   issue("equipment_motion_slot_unresolved","Selected body has no exact MOB motion-array identity; ACT-only binding remains unsupported",mob.path,motion.bindingOffset);return;
  }
  for(const auto &entry:equipment) {
   const auto checkpoint=motion.tracks.size();
   const auto referenceCheckpoint=motion.references.size();
   try {
    const auto equ=pvf.script(entry.second);std::vector<Layer> layers;
    for(const auto &field:equ.fields) {
     const auto tag=normalize(field.tag);
     if(tag=="[layer]") {
      if(field.values.size()!=1||!field.values[0].is_number_integer())throw std::runtime_error("Malformed EQU layer block");
      layers.push_back({field.values[0].get<int>(),field.offset,{}});
     } else if(motionTag(tag)) {
      if(layers.empty())throw std::runtime_error("EQU motion precedes an explicit layer");
      if(!layers.back().motions.emplace(tag,&field).second)throw std::runtime_error("Repeated motion tag inside same EQU layer block");
     }
    }
    if(layers.empty())throw std::runtime_error("EQU has no explicit layer blocks");
    const auto selected=select(pvf,equ,layers,slots.front());
    for(size_t i=1;i<slots.size();++i)if(!equivalent(selected,select(pvf,equ,layers,slots[i])))
      throw std::runtime_error("Exact body path appears in multiple MOB slots with different EQU bindings");
    for(const auto &binding:selected) {
     const auto explicitTrack=std::find_if(motion.tracks.begin(),motion.tracks.end(),[&](const auto &track) {
      return track.animation->path==binding.path&&track.layer==binding.layer;
     });
     if(explicitTrack!=motion.tracks.end()) {
      motion.references.push_back({{"source",equ.path},{"offset",binding.offset},{"path",binding.path},
          {"layer",binding.layer},{"consumer","already-explicit-ACT-or-ALS-track; not duplicated"}});continue;
     }
     const auto animation=assets.animation(binding.path);
     if(animation->frames.empty())throw std::runtime_error("Empty EQU ANI");
     // Exercise actual IMG decompression here. Transparent source layers are
     // valid and remain transparent; no procedural replacement is generated.
     for(const auto &frame:animation->frames)if(!frame.image.empty())assets.pixels(frame.image,frame.imageFrame);
     MonsterTrack track;track.animation=animation;track.start=0;track.end=motion.duration;track.layer=binding.layer;
     track.hold=true;track.role="equipment";
     track.drawOrder.emplace_back(binding.layer,motion.tracks.size());
     motion.tracks.push_back(std::move(track));
     motion.references.push_back({{"source",equ.path},{"member_source",makeSourceRef(pvf,equ.path).json()},
       {"offset",binding.offset},{"layer_block_offset",binding.blockOffset},{"layer",binding.layer},{"path",binding.path},
       {"animation_source",makeSourceRef(pvf,binding.path).json()},{"mob_equipment_offset",entry.first},
       {"body_slot",{{"tag",slots.front().tag},{"index",slots.front().index},{"offset",slots.front().offset}}},
       {"clock_classification","inferred-root-elapsed-min-source-delays; original bytes unchanged"}});
     if(pvf.has(binding.path+".als"))issue("equipment_als_not_executed",
       "EQU ANI has an ALS dependency that needs a live equipment host; not silently counted as complete",
       binding.path+".als",binding.offset);
    }
   }catch(const std::exception &error) {
    motion.tracks.resize(checkpoint);motion.references.erase(motion.references.begin()+referenceCheckpoint,motion.references.end());
    issue("equipment_binding_rejected",error.what(),entry.second,entry.first);
   }
  }
  std::stable_sort(motion.tracks.begin(),motion.tracks.end(),monsterTrackBefore);
 }catch(const std::exception &error) {issue("equipment_source_rejected",error.what(),monster,motion.bindingOffset);}
}
std::optional<ani_clock::Snapshot> monsterTrackClock(const MonsterMotion &motion,const MonsterTrack &track,double time) {
 if(track.role!="equipment")return std::nullopt;
 ani_clock::Snapshot root;root.elapsedMs=uint64_t(std::max(0.0,std::trunc(time-track.start)));
 root.policy=ani_clock::ClockPolicy::SourceDelay100;root.ratePercent=100;
 return track.animation->followClock(*motion.base,root,false);
}
}
