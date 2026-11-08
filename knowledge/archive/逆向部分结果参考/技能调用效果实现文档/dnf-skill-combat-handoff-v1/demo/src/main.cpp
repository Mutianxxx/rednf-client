// Resource-driven battle reconstruction. Native gaps remain explicit in data.
#define SDL_MAIN_HANDLED
#include <windows.h>
#include <bcrypt.h>
#include <SDL.h>
#include "dnf/entry.hpp"
#include "dnf/resources.hpp"
#include "dnf/geometry.hpp"
#include "dnf/shared_death.hpp"
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <functional>
#include <sstream>
#include <iomanip>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#include "stb_image_write.h"
#pragma clang diagnostic pop
using namespace dnf;
namespace fs=std::filesystem;
static std::wstring wide(const std::string&s){int n=MultiByteToWideChar(CP_UTF8,0,s.data(),int(s.size()),nullptr,0);std::wstring w(n,0);MultiByteToWideChar(CP_UTF8,0,s.data(),int(s.size()),w.data(),n);return w;}
static std::string concrete(std::string p){p=normalize(p);for(auto [a,b]:{std::pair{"%04d","0000"},std::pair{"%02d","00"}}){size_t i;while((i=p.find(a))!=p.npos)p.replace(i,strlen(a),b);}return p;}
static fs::path rootDir(){wchar_t p[32768];GetModuleFileNameW(nullptr,p,32768);return fs::path(p).parent_path();}
static Json jsonFile(const fs::path&p){return Json::parse(readFile(p));}
static std::string sha256(const fs::path&path){
    std::ifstream in(path,std::ios::binary);if(!in)throw std::runtime_error("Missing source executable: "+path.u8string());
    BCRYPT_ALG_HANDLE alg=nullptr;BCRYPT_HASH_HANDLE hash=nullptr;DWORD size=0,got=0;
    if(BCryptOpenAlgorithmProvider(&alg,BCRYPT_SHA256_ALGORITHM,nullptr,0)<0)throw std::runtime_error("SHA256 unavailable");
    BCryptGetProperty(alg,BCRYPT_OBJECT_LENGTH,(PUCHAR)&size,sizeof(size),&got,0);Bytes object(size),digest(32),buf(65536);
    if(BCryptCreateHash(alg,&hash,object.data(),size,nullptr,0,0)<0)throw std::runtime_error("SHA256 creation failed");
    while(in){in.read((char*)buf.data(),buf.size());if(in.gcount()&&BCryptHashData(hash,buf.data(),ULONG(in.gcount()),0)<0)throw std::runtime_error("SHA256 update failed");}
    if(BCryptFinishHash(hash,digest.data(),32,0)<0)throw std::runtime_error("SHA256 finish failed");
    BCryptDestroyHash(hash);BCryptCloseAlgorithmProvider(alg,0);std::ostringstream out;for(auto b:digest)out<<std::hex<<std::setfill('0')<<std::setw(2)<<int(b);return out.str();
}
struct Content{Pvf pvf;Assets assets;Json profile,battle,catalog;Content(const fs::path&root,const fs::path&client):pvf(root/"content/cache"),assets(client,pvf),profile(jsonFile(root/"content/profile.json")),battle(jsonFile(root/"content/battle.json")),catalog(jsonFile(root/"content/skills.json")){assets.setOverrides(profile["archive_overrides"]);}};
#include "canvas.hpp"
static const std::string bodyDir="character/swordman/animation/";
static const SDL_Color muted{142,163,178,255},accent{84,218,197,255},gold{246,211,153,255};
struct Volume{double x,y,z,w,h,d;};
static Volume volume(const Box&b,double x,double y,double z,int face){return {x+(face>0?b.x:-b.x-b.w),y+b.y,z+b.z,double(b.w),double(b.h),double(b.d)};}
static bool overlaps(const Volume&a,const Volume&b){return a.x<b.x+b.w&&a.x+a.w>b.x&&a.y<b.y+b.h&&a.y+a.h>b.y&&a.z<b.z+b.d&&a.z+a.d>b.z;}
struct Track{
    std::string path,anchor="actor",basis;double begin=0,end=0,x=0,y=0,z=0,spawn=0;int layer=0;bool repeat=false,projection=false;
};
struct BodyStage{std::string path;double begin,end;};
struct Motion{
    double distance=0,height=0,ready=0,t1=360,t2=600;
    double offset(double t)const{t-=ready;if(t<=0)return 0;if(t<t1)return int(float(int(float(distance)*.8f))*float(t)/float(t1));if(t<t2)return int(float(int(float(distance)*.8f))+(float(distance)-float(int(float(distance)*.8f)))*float(t-t1)/float(t2-t1));return distance;}
    double z(double t)const{double u=std::clamp((t-ready)/t2,0.0,1.0);return height*4*u*(1-u);}
};
struct Cast{uint64_t id=0;std::string key,name;double start=0,x=0,y=0,duration=0,lock=0;int face=1;std::vector<BodyStage> body;std::vector<Track> effects;Motion motion;bool inferred=false;};
struct Monster{
    uint64_t id=0,generation=1;int type=0,hp=700,maxHp=700,hits=0,face=-1;double x=0,y=0,age=0;std::string state="idle";
    std::set<uint64_t> accepted;Json frozen;double frozenAge=0;bool frozenLoop=false,shared=false;std::array<double,4> bounds{};std::vector<DeathParticle> fragments;
};
struct Floating{double x,y,at;int damage;};
struct Battle{
    Content&c;Canvas&r;fs::path root;double clock=0,x=310,y=485,idleAge=0,buffSince=-1,buffAt=0;int face=1,combo=-1,type=0,job=3,selection=0,scroll=0;
    bool buff=false,paused=false,boxes=false,library=false,running=true,walking=false,queued=false;std::set<SDL_Scancode> held;
    std::vector<Cast> casts;std::vector<Monster> monsters;std::vector<Floating> numbers;Json events=Json::array(),errors=Json::array();std::set<std::string> errorSet;std::map<std::string,double> hitTimes;
    std::map<std::string,Json> specs;std::vector<int> visible;std::string notice=u8"方向键移动，X 攻击；靠近怪物后释放技能。",last=u8"待机";double noticeUntil=5000;uint64_t serial=0;int hits=0,deaths=0,screens=0;double gravity=1500,particleLife=3000,pieceSpeed=400;int pieceCount=10;
    Battle(Content&content,Canvas&canvas,fs::path path):c(content),r(canvas),root(std::move(path)){
        for(auto&s:c.battle["skills"])specs.emplace(s["key"].get<std::string>(),s);
        auto p=c.pvf.script("monster/common/particle/monsterdiepiece.ptl");gravity=p.number("[gravity]",1500);particleLife=p.number("[life time]",3000);pieceCount=int(p.number("[maximum create number]",10));auto v=p.values("[move variable 1]");if(!v.empty())pieceSpeed=v[0];
        if(gravity<=0||particleLife<=0||pieceCount<0||pieceCount>128)throw std::runtime_error("Unsupported death PTL parameters");
        reset();filter();
    }
    void log(const std::string&e,Json data=Json::object()){data["event"]=e;data["clock_ms"]=clock;events.push_back(data);}
    void say(const std::string&s){notice=s;noticeUntil=clock+4500;}
    void fail(const std::string&context,const std::exception&e){std::string key=context+": "+e.what();if(errorSet.insert(key).second){errors.push_back({{"context",context},{"error",e.what()}});log("resource_error",errors.back());}say(u8"资源诊断："+context);}
    void reset(){casts.clear();numbers.clear();held.clear();hitTimes.clear();x=310;y=485;face=1;buff=false;buffSince=-1;queued=false;combo=-1;hits=deaths=0;monsters.clear();for(int i=0;i<3;++i){Monster m;m.id=++serial;m.generation=serial;m.type=type;m.x=560+i*175;m.y=485+(i==1?-30:i==2?28:0);monsters.push_back(m);}log("arena_reset",{{"type",type}});}
    void filter(){visible.clear();int i=0;for(auto&s:c.catalog["skills"]){bool match=job<0;for(auto g:s["groups"])if(g==job||g==0)match=true;if(match&&s["type"]=="[active]")visible.push_back(i);++i;}selection=scroll=0;}
    const Json&monsterRow(const Monster&m)const{return c.battle["monsters"][m.type];}
    const Json*statePlan(const Monster&m,const std::string&state)const{auto&s=monsterRow(m)["states"];return s.contains(state)&&!s[state]["tracks"].empty()?&s[state]:nullptr;}
    double stateDuration(const Monster&m)const{if(m.state=="death"&&m.shared)return 220+particleLife;auto*p=statePlan(m,m.state);return p?p->value("duration",1.0):1;}
    static Track track(const Json&e){Track t;t.path=e["path"];t.begin=e.value("begin",0.0);t.end=e.value("end",0.0);t.layer=e.value("layer",0);auto v=e.value("position",Json::array({0,0,0}));t.x=v[0];t.y=v[1];t.z=v[2];t.anchor=e.value("anchor","actor");t.spawn=e.value("spawn",t.begin);t.repeat=e.value("repeat",false);t.projection=e.value("projection_only",false);t.basis=e.value("basis","");return t;}
    Cast*active(){for(auto i=casts.rbegin();i!=casts.rend();++i)if(clock-i->start<i->lock)return &*i;return nullptr;}
    double playerX()const{for(auto i=casts.rbegin();i!=casts.rend();++i)if(clock-i->start<i->lock)return i->x+i->face*i->motion.offset(clock-i->start);return x;}
    std::pair<double,double> point(const Cast&s,const Track&e,double time)const{double offset=e.anchor=="cast"?0:e.anchor=="spawn"?s.motion.offset(e.spawn):s.motion.offset(time);double z=e.anchor=="actor"?s.motion.z(time):e.anchor=="spawn"?s.motion.z(e.spawn):0;return {s.x+s.face*(offset+e.x),s.y+e.y-e.z-z};}
    void addAls(Cast&cast,const std::string&path,double start,int layer=0,std::set<std::string> stack={}){
        if(stack.size()>12||stack.count(path))return;stack.insert(path);auto ap=path+".als";if(!c.pvf.has(ap))return;
        auto script=c.pvf.script(ap);std::map<std::string,std::string> names;auto a=c.assets.animation(path);
        auto boundary=[&](int frame){if(frame<0||frame>=int(a->frames.size()))throw std::runtime_error("ALS frame outside animation");double t=0;for(int i=0;i<frame;++i)t+=a->frames[i].duration;return t;};
        for(auto&f:script.fields)if(normalize(f.tag)=="[use animation]"&&f.values.size()==2)names[f.values[1]]=normalize((fs::u8path(path).parent_path()/fs::u8path(f.values[0].get<std::string>())).generic_u8string());
        for(auto&f:script.fields)if(normalize(f.tag)=="[add]"&&f.values.size()==3){try{int frame=f.values[0];std::string n=f.values[2];auto child=names.at(n);double begin=start+boundary(frame),end=std::min(start+a->duration,begin+c.assets.animation(child)->duration);for(auto&other:script.fields)if(normalize(other.tag)=="[remove]"&&other.values.size()==3&&other.values[2]==n&&other.values[0].get<int>()>=frame)end=std::min(end,start+boundary(other.values[0]));if(end>begin){Track t;t.path=child;t.begin=begin;t.spawn=begin;t.end=end;t.layer=layer+f.values[1].get<int>();t.basis="source ALS (inferred generic execution)";cast.effects.push_back(t);addAls(cast,child,begin,t.layer,stack);}}catch(const std::exception&e){if(errorSet.insert(ap+std::to_string(f.offset)).second)errors.push_back({{"source",ap},{"offset",f.offset},{"unexecuted",e.what()}});}}
    }
    void startSpec(const Json&s,bool force=false){
        std::string key=s["key"];if(key=="bloodyrave"){say(u8"嗜魂封魔斩已按要求排除。");return;}
        if(!force&&active()){say(u8"当前动作结束后再释放技能。");return;}
        if(!force&&key=="bloodsword"&&!buff){say(u8"血气之刃需要先按 W 开启血之狂暴。");log("skill_rejected",{{"key",key},{"reason","frenzy_required_observed"}});return;}
        if(key=="frenzy"&&buff){if(!force&&clock-buffSince<10000){say(u8"开启后 10 秒内无法关闭血之狂暴。");return;}buff=false;log("buff_disabled");say(u8"血之狂暴已关闭");return;}
        Cast cast;cast.id=++serial;cast.key=key;cast.name=s["name"];cast.start=clock;cast.x=x;cast.y=y;cast.face=face;cast.duration=s["duration"];cast.inferred=!specs.count(key);
        for(auto&b:s["body"])cast.body.push_back({b["path"],b["begin"],b["end"]});
        if(cast.body.empty()){say(u8"该技能尚无动作映射，可在原技能浏览器检查候选资源。");return;}
        cast.lock=cast.body.back().end;
        for(auto&e:s["effects"]){auto t=track(e);if(key=="frenzy"&&t.path=="character/swordman/effect/animation/frenzy/buff.ani")continue;cast.effects.push_back(t);}
        if(s.contains("motion")){cast.motion.ready=cast.body.at(1).begin;double param=s.value("internal_parameter",27.0);auto&m=s["motion"];cast.motion.distance=int(float(m["distance_range"][0].get<int>())+(m["distance_range"][1].get<float>()-m["distance_range"][0].get<float>())*float(param)/100);cast.motion.height=int(float(m["height_range"][0].get<int>())+(m["height_range"][1].get<float>()-m["height_range"][0].get<float>())*float(param)/100);cast.motion.t1=m["frame_times_ms"][1];cast.motion.t2=m["frame_times_ms"][2];}
        if(s.contains("inferred_motion")){auto&m=s["inferred_motion"];cast.motion.distance=m["distance"];cast.motion.ready=m["ready"];cast.motion.t2=m["end"].get<double>()-cast.motion.ready;cast.motion.t1=cast.motion.t2*.8;}
        if(key=="frenzy"){buff=true;buffSince=clock;buffAt=clock;for(auto&e:s["effects"])if(e["path"]=="character/swordman/effect/animation/frenzy/buff.ani")buffAt=clock+e["begin"].get<double>();say(u8"血之狂暴开启：普攻切换为狂暴动作。");}
        if(key=="bloodblast"||key=="bloodblastex")cast.lock=std::min(cast.duration,1000.0);
        std::stable_sort(cast.effects.begin(),cast.effects.end(),[](auto&a,auto&b){return a.layer<b.layer;});
        last=cast.name;log("skill_started",{{"key",key},{"cast_id",cast.id},{"inferred_catalog_mapping",cast.inferred},{"effect_instances",cast.effects.size()},{"origin",{cast.x,cast.y}},{"facing",face}});casts.push_back(std::move(cast));queued=false;combo=-1;
    }
    Json inferred(const Json&s){
        Json spec={{"key",s["key"]},{"name",s["name"]},{"body",Json::array()},{"effects",Json::array()},{"duration",0}};double t=0;std::vector<double> offsets;
        for(auto&p:s["body_sequence"]){auto a=c.assets.animation(p);offsets.push_back(t);spec["body"].push_back({{"path",p},{"begin",t},{"end",t+a->duration}});t+=a->duration;}
        for(auto&e:s["effects_timeline"]){int stage=e["stage"];if(stage<0||stage>=int(offsets.size()))continue;Json row=e;row["begin"]=offsets[stage]+e.value("offset_ms",0.0);row["end"]=row["begin"].get<double>()+c.assets.animation(e["path"])->duration;row["spawn"]=offsets[stage]+e.value("spawn_offset_ms",e.value("offset_ms",0.0));spec["effects"].push_back(row);t=std::max(t,row["end"].get<double>());}
        spec["duration"]=t;return spec;
    }
    void selectedSkill(){if(visible.empty())return;if(active()){say(u8"当前动作结束后再释放技能。");return;}auto&s=c.catalog["skills"][visible[selection]];auto k=s["key"].get<std::string>();try{if(specs.count(k))startSpec(specs.at(k));else {auto spec=inferred(s);startSpec(spec);if(!casts.empty()&&casts.back().key==k){auto&cast=casts.back();if(cast.effects.empty())for(auto&b:cast.body)addAls(cast,b.path,b.begin);say(u8"资源推导演示：该技能未完成运行链验证。");}}}catch(const std::exception&e){fail(k,e);}}
    void attack(bool force=false){auto*prev=active();if(prev&&!force){if(prev->key=="normal"&&clock-prev->start>prev->lock*.35)queued=true;return;}
        combo=(combo+1)%(buff?4:3);Cast s;s.id=++serial;s.key="normal";s.name=buff?u8"狂暴普攻":u8"太刀普攻";s.start=clock;s.x=x;s.y=y;s.face=face;
        auto path=bodyDir+(buff?"frenzy":"attack")+std::to_string(combo+1)+".ani";auto a=c.assets.animation(path);s.duration=s.lock=a->duration;s.body.push_back({path,0,s.lock});addAls(s,path,0);last=s.name;log("normal_attack",{{"cast_id",s.id},{"combo",combo+1},{"buff",buff},{"path",path}});casts.push_back(std::move(s));queued=false;
    }
    std::array<double,4> planBounds(const Json&plan,double age,bool loop){
        double x0=1e9,y0=1e9,x1=-1e9,y1=-1e9;double t=loop?std::fmod(age,std::max(1.0,plan["duration"].get<double>())):age;
        for(auto&e:plan["tracks"]){double start=e["begin"],end=e["end"];if(t<start||t>=end)continue;auto a=c.assets.animation(e["path"]);auto p=a->samplePose(t-start,false);if(p.image.empty())continue;auto&tex=r.texture(p.image,p.imageFrame);auto q=imageQuad(0,0,p.x,p.y,tex.cropX,tex.cropY,tex.w,tex.h,1,(p.flip&1)?-p.scaleX:p.scaleX,(p.flip&2)?-p.scaleY:p.scaleY,radiansToDegrees(p.rotationRadians));for(auto v:q){x0=std::min(x0,v.x);y0=std::min(y0,v.y);x1=std::max(x1,v.x);y1=std::max(y1,v.y);}}
        if(x1<x0)return {-20,-70,40,70};return {x0,y0,x1-x0,y1-y0};
    }
    bool acceptedHit(Monster&m,uint64_t generation,uint64_t eventId,int reaction,int damage){
        if(m.generation!=generation||m.hp<=0||!m.accepted.insert(eventId).second)return false;
        m.hp=std::max(0,m.hp-damage);++m.hits;++hits;numbers.push_back({m.x,m.y-75,clock,damage});
        if(m.hp==0){
            const Json*death=statePlan(m,"death");bool declared=monsterRow(m)["states"].contains("death");m.shared=!declared;
            auto*current=statePlan(m,m.state);if(!current)current=statePlan(m,"idle");if(current){m.frozen=*current;m.frozenAge=m.age;m.frozenLoop=m.state=="idle";m.bounds=planBounds(*current,m.age,m.frozenLoop);}
            if(m.shared){auto&b=m.bounds;m.fragments=deathParticles(deathSeed(monsterRow(m)["path"]),pieceCount,b[0]+b[2]/2,b[1]+b[3]/2,b[2],b[3],pieceSpeed);}
            else if(!death)say(u8"此怪物声明的死亡动作不可执行，已保留诊断。");
            m.state="death";m.age=0;++deaths;log("monster_died",{{"id",m.id},{"generation",m.generation},{"event_id",eventId},{"shared",m.shared},{"source",monsterRow(m)["path"]}});
        }else{std::string state=reaction%2?"damage2":"damage1";if(statePlan(m,state)){m.state=state;m.age=0;}else log("reaction_unavailable",{{"id",m.id},{"requested",state}});}
        log("accepted_hit",{{"id",m.id},{"generation",m.generation},{"event_id",eventId},{"hp",m.hp},{"reaction",m.state},{"damage_policy","demo fixed 100; native formula unresolved"}});return true;
    }
    std::vector<Volume> hurtBoxes(Monster&m){
        auto*plan=statePlan(m,m.state);if(!plan)plan=statePlan(m,"idle");std::vector<Volume> out;if(!plan)return out;
        auto&e=(*plan)["tracks"][0];auto a=c.assets.animation(e["path"]);auto frame=a->frameAt(int64_t(m.age),m.state=="idle");for(auto&b:a->frames.at(frame).boxes)if(b.type==14)out.push_back(volume(b,m.x,m.y,0,m.face));
        return out;
    }
    void collision(Cast&cast,const std::string&path,double age,double px,double py,double pz,const std::string&instance,bool repeat,int overrideFrame=-1){
        auto a=c.assets.animation(path);auto index=overrideFrame<0?a->frameAt(int64_t(age),repeat):std::min(size_t(overrideFrame),a->frames.size()-1);const auto&f=a->frames.at(index);
        for(auto&b:f.boxes)if(b.type==15){auto attack=volume(b,px,py,pz,cast.face);for(auto&m:monsters){if(m.hp<=0)continue;std::string k=std::to_string(cast.id)+"/"+instance+"/"+std::to_string(m.id);auto it=hitTimes.find(k);if(it!=hitTimes.end()&&clock-it->second<250)continue;bool hit=false;for(auto hurt:hurtBoxes(m))if(overlaps(attack,hurt)){hit=true;break;}if(hit){hitTimes[k]=clock;acceptedHit(m,m.generation,++serial,m.hits,100);}}}
    }
    void step(double dt){if(paused)return;clock+=dt;idleAge+=dt;walking=false;
        auto*act=active();if(!act){int dx=int(held.count(SDL_SCANCODE_RIGHT))-int(held.count(SDL_SCANCODE_LEFT)),dy=int(held.count(SDL_SCANCODE_DOWN))-int(held.count(SDL_SCANCODE_UP));if(dx||dy){double n=std::hypot(dx,dy);x=std::clamp(x+dx/n*.18*dt,70.0,1130.0);y=std::clamp(y+dy/n*.18*dt,335.0,590.0);if(dx)face=dx;walking=true;combo=-1;}if(queued||held.count(SDL_SCANCODE_X))attack();}
        for(auto&cast:casts){double t=clock-cast.start;if(t<0)continue;
            if(t<cast.lock){x=std::clamp(cast.x+cast.face*cast.motion.offset(t),70.0,1130.0);y=cast.y;}
            for(auto&b:cast.body)if(t>=b.begin&&t<b.end)try{double px=cast.x+cast.face*cast.motion.offset(t),pz=cast.motion.z(t);collision(cast,b.path,t-b.begin,px,cast.y,pz,"body",false);auto wp="equipment/character/swordman/weapon/katana/katana/"+fs::u8path(b.path).filename().string();if(c.pvf.has(wp)){auto a=c.assets.animation(b.path);collision(cast,wp,t-b.begin,px,cast.y,pz,"weapon",false,int(a->frameAt(int64_t(t-b.begin),false)));}}catch(const std::exception&e){fail(b.path,e);}
            for(size_t i=0;i<cast.effects.size();++i){auto&e=cast.effects[i];if(t<e.begin||t>=e.end)continue;try{double origin=e.anchor=="cast"?0:e.anchor=="spawn"?cast.motion.offset(e.spawn):cast.motion.offset(t);double pz=e.anchor=="actor"?cast.motion.z(t):e.anchor=="spawn"?cast.motion.z(e.spawn):0;collision(cast,e.path,t-e.begin,cast.x+cast.face*(origin+e.x),cast.y+e.y,e.z+pz,"effect"+std::to_string(i),e.repeat);}catch(const std::exception&ex){fail(e.path,ex);}}
        }
        for(auto&m:monsters){m.age+=dt;if(m.state!="idle"&&m.state!="death"&&m.age>=stateDuration(m)){m.state="idle";m.age=0;}}
        casts.erase(std::remove_if(casts.begin(),casts.end(),[&](auto&s){return clock-s.start>std::max(s.duration,s.lock)+50;}),casts.end());
        numbers.erase(std::remove_if(numbers.begin(),numbers.end(),[&](auto&n){return clock-n.at>750;}),numbers.end());
    }
    void body(const std::string&path,double ms,double px,double py,bool loop,int facing){
        auto a=c.assets.animation(path);int frame=int(a->frameAt(int64_t(ms),loop));auto stem=fs::u8path(path).filename().string();
        for(auto&layer:c.profile["body_layers"]){std::string motion=path;if(layer["motion"]=="katana"){auto wp="equipment/character/swordman/weapon/katana/katana/"+stem;if(c.pvf.has(wp))motion=wp;}r.animation(motion,ms,px,py,facing,loop,frame,layer["image"]);}
    }
    void drawPlan(const Json&plan,double age,double px,double py,int facing,bool loop,bool white=false,double alpha=1){
        double t=loop?std::fmod(age,std::max(1.0,plan["duration"].get<double>())):std::min(age,std::max(0.0,plan["duration"].get<double>()-1));
        for(auto&e:plan["tracks"]){double start=e["begin"],end=e["end"];if(t<start||t>=end)continue;auto a=c.assets.animation(e["path"]);auto p=a->samplePose(t-start,false);if(p.image.empty())continue;auto pos=e.value("position",Json::array({0,0,0}));r.sprite(p.image,p.imageFrame,px+facing*pos[0].get<double>(),py+pos[1].get<double>()-pos[2].get<double>(),facing,p.x,p.y,(p.flip&1)?-p.scaleX:p.scaleX,(p.flip&2)?-p.scaleY:p.scaleY,p.rotationRadians,p.blend,{uint8_t(p.rgba[0]),uint8_t(p.rgba[1]),uint8_t(p.rgba[2]),uint8_t(p.rgba[3]*alpha)},true,white);}
    }
    void effectSprite(const std::string&image,int frame,double px,double py,double scale,double angle,SDL_Color color,int facing,bool additive=false){auto&tex=r.texture(image,frame);r.sprite(image,frame,px,py,facing,-tex.w*scale*.5,-tex.h*scale*.5,scale,scale,angle*3.141592653589793/180,additive?1:0,color,false);}
    void drawMonster(Monster&m){
        if(m.state=="death"&&m.shared){DeathProfile profile(monsterRow(m));auto&b=m.bounds;double fade=std::clamp(1-(m.age-220)/90,0.0,1.0);if(fade>0&&!m.frozen.is_null())drawPlan(m.frozen,m.frozenAge,m.x,m.y,m.face,m.frozenLoop,m.age>=60,fade);
            double age=m.age-220;if(age>=0){
                if(profile.pieces&&age<particleLife){auto ani=c.assets.animation("monster/common/animation/monsterdiepiece.ani");auto p=ani->samplePose(age,false);for(auto&part:m.fragments){auto v=deathPosition(part,age/1000,gravity,b[1]+b[3]);effectSprite(profile.image,part.frame,m.x+m.face*v.x,m.y+v.y,part.size,v.angle,{255,255,255,uint8_t(p.rgba[3])},m.face);}}
                if(profile.flash){auto a=c.assets.animation("monster/common/animation/monsterdieflash.ani");if(age<a->duration){auto p=a->samplePose(age,false);effectSprite(p.image,p.imageFrame,m.x+m.face*(b[0]+b[2]/2),m.y+b[1]+b[3]/2,std::max(.5,p.scaleX),0,{255,255,255,uint8_t(p.rgba[3])},m.face,true);}}
                if(profile.smoke&&age<1500){double k=age/1500;effectSprite("monster/common/monsterdiesmoke.img",0,m.x+m.face*(b[0]+b[2]/2),m.y+b[1]+b[3]-k*30,1.4+k*2.5,0,{205,205,205,uint8_t(55*(1-k))},m.face,true);}
            }
        }else if(auto*p=statePlan(m,m.state))drawPlan(*p,m.age,m.x,m.y,m.face,m.state=="idle");
        if(m.hp>0){r.rect(float(m.x-30),float(m.y-92),60,5,{44,53,63,255});r.rect(float(m.x-30),float(m.y-92),60.f*m.hp/m.maxHp,5,accent);r.text(std::to_string(m.hp),int(m.x-18),int(m.y-112),12,muted);}
        if(boxes&&m.hp>0)for(auto b:hurtBoxes(m))r.rect(float(b.x),float(b.y-b.z-b.d),float(b.w),float(b.d),{82,221,164,230},false);
    }
    void drawVolume(const Box&b,double px,double py,double pz,int facing){auto v=volume(b,px,py,pz,facing);r.rect(float(v.x),float(v.y-v.z-v.d),float(v.w),float(v.d),{255,157,83,240},false);}
    void drawPlayer(Cast*current,double px){
        bool drawn=false;
        if(current){double t=clock-current->start;for(auto&b:current->body)if(t>=b.begin&&t<b.end){double pz=current->motion.z(t);body(b.path,t-b.begin,px,y-pz,false,current->face);drawn=true;
            if(boxes){auto a=c.assets.animation(b.path);auto frame=a->frameAt(int64_t(t-b.begin),false);for(auto&v:a->frames[frame].boxes)if(v.type==15)drawVolume(v,px,y,pz,current->face);auto wp="equipment/character/swordman/weapon/katana/katana/"+fs::u8path(b.path).filename().string();if(c.pvf.has(wp)){auto w=c.assets.animation(wp);for(auto&v:w->frames[std::min(frame,w->frames.size()-1)].boxes)if(v.type==15)drawVolume(v,px,y,pz,current->face);}}
            break;}}
        if(!drawn)body(bodyDir+(walking?"move.ani":"stay.ani"),idleAge,px,y,true,face);
    }
    void draw(){SDL_SetRenderDrawColor(r.renderer,14,22,30,255);SDL_RenderClear(r.renderer);
        r.rect(0,0,1200,88,{23,35,46,255});r.text(u8"DNF  /  技能战斗试验场",24,16,27,gold);r.text(u8"鬼剑士 · 太刀",905,20,20,accent);r.text(u8"方向键 移动    X 普攻    W 狂暴    R 重置    M 怪物    B 判定框    F1 技能库    F5 导出",25,58,15,muted);
        r.rect(0,235,1200,390,{19,34,42,255});for(int yy=320;yy<=615;yy+=38)r.rect(0,float(yy),1200,1,{34,52,59,255});for(int xx=0;xx<1200;xx+=70)r.rect(float(xx),235,1,390,{29,45,54,255});
        r.text(last,28,110,25,gold);r.text(paused?u8"已暂停 · Space 继续":buff?u8"血之狂暴已开启":u8"血之狂暴关闭",28,148,16,buff?accent:muted);r.text(u8"命中 "+std::to_string(hits)+u8"    击败 "+std::to_string(deaths),930,111,18);r.text(c.battle["monsters"][type]["name"].get<std::string>()+u8" × 3",932,145,16,muted);
        SDL_Rect clip{0,185,1200,440};SDL_RenderSetClipRect(r.renderer,&clip);
        struct Draw{double depth;int layer;std::function<void()> fn;};std::vector<Draw> list;
        for(auto&m:monsters)list.push_back({m.y,0,[&,mp=&m](){try{drawMonster(*mp);}catch(const std::exception&e){fail(monsterRow(*mp)["path"],e);}}});
        double px=playerX();Cast*current=active();
        list.push_back({y,0,[&,current,px](){try{drawPlayer(current,px);}catch(const std::exception&e){fail("player",e);}}});
        for(auto&cast:casts){double t=clock-cast.start;for(auto&e:cast.effects)if(t>=e.begin&&t<e.end){auto p=point(cast,e,t);list.push_back({cast.y+e.y,e.layer,[&,cp=&cast,ep=&e,p,t](){try{r.animation(ep->path,t-ep->begin,p.first,p.second,cp->face,ep->repeat);if(boxes){auto a=c.assets.animation(ep->path);for(auto&b:a->frames[a->frameAt(int64_t(t-ep->begin),ep->repeat)].boxes)if(b.type==15)drawVolume(b,p.first,cp->y+ep->y,cp->y+ep->y-p.second,cp->face);}}catch(const std::exception&ex){fail(ep->path,ex);}}});}}
        if(buff&&clock>=buffAt)list.push_back({y,10005,[&,px,current](){try{double pz=current?current->motion.z(clock-current->start):0;r.animation("character/swordman/effect/animation/frenzy/buff.ani",clock-buffAt,px,y-pz,face,true);}catch(const std::exception&e){fail("frenzy buff",e);}}});
        std::stable_sort(list.begin(),list.end(),[](auto&a,auto&b){if(a.depth==b.depth)return a.layer<b.layer;return a.depth<b.depth;});for(auto&d:list)d.fn();
        for(auto&n:numbers){double k=(clock-n.at)/750;r.text(std::to_string(n.damage),int(n.x-15),int(n.y-k*38),23,{255,225,150,uint8_t(255*(1-k))});}
        SDL_RenderSetClipRect(r.renderer,nullptr);
        r.rect(0,625,1200,195,{19,29,39,255});int i=0;for(auto&s:c.battle["skills"]){int xx=22+i*147;r.rect(float(xx),644,138,76,{33,49,61,255});r.rect(float(xx),644,138,76,{58,88,98,255},false);r.text(s["hotkey"].get<std::string>(),xx+10,650,18,accent);r.text(s["name"].get<std::string>(),xx+10,681,17);++i;}
        r.text(u8"按一下释放 · 连按 X 连段 · 血气之刃需开启狂暴 · 狂暴开启 10 秒后可关闭",25,733,15,muted);
        if(clock<noticeUntil||!errors.empty())r.text(clock<noticeUntil?notice:u8"部分资源规则未执行，F5 可导出诊断。",25,765,16,gold);
        r.text(u8"重建战斗：技能效果使用 PVF / NPK；伤害、冷却与部分控制时序为演示规则。",25,796,12,muted);
        if(library)drawLibrary();
    }
    void drawLibrary(){r.rect(10,91,420,533,{16,27,37,246});std::string name=job<0?u8"全部职业":c.catalog["jobs"][job]["name"].get<std::string>();r.text(name+u8" / 主动技能 "+std::to_string(visible.size()),24,102,20,accent);r.text(u8"Tab 职业 · 滚轮选择 · Enter 释放 · F1 收起",24,135,14,muted);for(int i=0;i<13&&scroll+i<int(visible.size());++i){int n=scroll+i,yy=165+i*33;auto&s=c.catalog["skills"][visible[n]];if(n==selection)r.rect(20,float(yy-2),398,31,{42,66,76,255});bool linked=specs.count(s["key"].get<std::string>());r.text(s["name"],29,yy,16,linked?gold:SDL_Color{219,226,231,255});r.text(linked?u8"实测链":s["body_sequence"].empty()?u8"待映射":u8"资源推导",327,yy+2,13,linked?accent:muted);}}
    void moveSelection(int d){if(visible.empty())return;selection=std::clamp(selection+d,0,int(visible.size())-1);if(selection<scroll)scroll=selection;if(selection>=scroll+13)scroll=selection-12;}
    void exportReport(const std::string&folder=""){
        fs::path out=root/"reports"/(folder.empty()?"feedback-"+std::to_string(GetTickCount64()):folder);fs::create_directories(out);draw();r.screenshot(out/"frame.png");
        Json ms=Json::array();for(auto&m:monsters)ms.push_back({{"id",m.id},{"generation",m.generation},{"path",monsterRow(m)["path"]},{"hp",m.hp},{"state",m.state},{"age_ms",m.age},{"shared_death",m.shared},{"frozen_age",m.frozenAge},{"particle_count",m.fragments.size()}});
        Json cs=Json::array();for(auto&s:casts){double t=clock-s.start;Json ee=Json::array(),bb=Json::array();for(auto&e:s.effects){auto p=point(s,e,t);ee.push_back({{"path",e.path},{"begin",e.begin},{"end",e.end},{"active",t>=e.begin&&t<e.end},{"position",{e.x,e.y,e.z}},{"screen_anchor",{p.first,p.second}},{"anchor",e.anchor},{"projected_coordinate_inference",e.projection},{"basis",e.basis}});}for(auto&b:s.body){auto a=c.assets.animation(b.path);bb.push_back({{"path",b.path},{"begin",b.begin},{"end",b.end},{"active",t>=b.begin&&t<b.end},{"frame",a->frameAt(int64_t(t-b.begin),false)}});}cs.push_back({{"key",s.key},{"id",s.id},{"age_ms",t},{"effects",ee},{"body_stages",bb},{"motion",{{"distance",s.motion.distance},{"height",s.motion.height},{"horizontal_offset",s.motion.offset(t)},{"vertical_offset",s.motion.z(t)}}}});}
        writeJson(out/"state.json",{{"clock_ms",clock},{"player",{x,y}},{"facing",face},{"buff",buff},{"monsters",ms},{"casts",cs},{"events",events},{"errors",errors},{"source_reads",{{"pvf",c.pvf.reads()},{"npk",c.assets.reads()}}},{"unconsumed_render_nodes",r.unsupported},{"policy",c.battle["policy"]},{"appearance_profile",c.profile},{"content_diagnostics",c.battle["diagnostics"]},{"content_source_exe_sha256",c.battle["source_exe_sha256"]}});if(fs::exists(root/"reports/build-manifest.json"))fs::copy_file(root/"reports/build-manifest.json",out/"build-manifest.json",fs::copy_options::overwrite_existing);say(u8"已导出画面及诊断到 battle_demo/reports。");
    }
    void key(SDL_Scancode k){
        if(k==SDL_SCANCODE_ESCAPE){if(library)library=false;else running=false;return;}if(k==SDL_SCANCODE_F1){library=!library;return;}if(k==SDL_SCANCODE_TAB){job=job==4?-1:job+1;filter();library=true;return;}if(k==SDL_SCANCODE_SPACE){paused=!paused;return;}if(k==SDL_SCANCODE_R){reset();return;}if(k==SDL_SCANCODE_M){type=(type+1)%int(c.battle["monsters"].size());reset();return;}if(k==SDL_SCANCODE_B){boxes=!boxes;return;}if(k==SDL_SCANCODE_F5){exportReport();return;}
        if(library&&(k==SDL_SCANCODE_UP||k==SDL_SCANCODE_DOWN)){moveSelection(k==SDL_SCANCODE_UP?-1:1);return;}if(library&&k==SDL_SCANCODE_RETURN){selectedSkill();return;}if(paused)return;
        if(k==SDL_SCANCODE_X){attack();return;}char code=k==SDL_SCANCODE_A?'A':k==SDL_SCANCODE_S?'S':k==SDL_SCANCODE_D?'D':k==SDL_SCANCODE_G?'G':k==SDL_SCANCODE_H?'H':k==SDL_SCANCODE_Q?'Q':k==SDL_SCANCODE_E?'E':k==SDL_SCANCODE_W?'W':0;
        if(code)for(auto&s:c.battle["skills"])if(s["hotkey"].get<std::string>()==std::string(1,code)){startSpec(s);break;}
    }
    void event(const SDL_Event&e){if(e.type==SDL_QUIT)running=false;if(e.type==SDL_KEYDOWN&&!e.key.repeat){auto k=e.key.keysym.scancode;if(!(library&&(k==SDL_SCANCODE_UP||k==SDL_SCANCODE_DOWN)))held.insert(k);key(k);}if(e.type==SDL_KEYUP)held.erase(e.key.keysym.scancode);if(e.type==SDL_WINDOWEVENT&&e.window.event==SDL_WINDOWEVENT_FOCUS_LOST){held.clear();queued=false;}if(e.type==SDL_MOUSEWHEEL&&library)moveSelection(-e.wheel.y*2);if(e.type==SDL_MOUSEBUTTONDOWN&&e.button.button==SDL_BUTTON_LEFT){float xx,yy;SDL_RenderWindowToLogical(r.renderer,e.button.x,e.button.y,&xx,&yy);if(library&&xx>=20&&xx<=420&&yy>=163&&yy<594){selection=std::clamp(scroll+int(yy-163)/33,0,std::max(0,int(visible.size())-1));if(e.button.clicks>=2)selectedSkill();}}}
};

static void require(bool v,const std::string&msg){if(!v)throw std::runtime_error("Verification failed: "+msg);}
static int verify(Battle&b){
    Json checks=Json::array();auto check=[&](const std::string&name,bool ok){require(ok,name);checks.push_back({{"name",name},{"passed",ok}});};
    b.held.insert(SDL_SCANCODE_RIGHT);b.step(100);b.held.clear();check("movement",b.x>310);b.held.insert(SDL_SCANCODE_LEFT);b.step(100);b.held.clear();check("facing",b.face==-1);b.reset();
    auto&m=b.monsters[0];auto g=m.generation;auto hp=m.hp;check("generation rejection",!b.acceptedHit(m,g+1,10,0,100)&&m.hp==hp);check("accepted reaction 1",b.acceptedHit(m,g,11,0,100)&&m.state=="damage1");check("event deduplication",!b.acceptedHit(m,g,11,0,100)&&m.hp==hp-100);check("accepted reaction 2",b.acceptedHit(m,g,12,1,100)&&m.state=="damage2");b.acceptedHit(m,g,13,0,1000);check("shared death and frozen pose",m.state=="death"&&m.shared&&!m.frozen.is_null()&&int(m.fragments.size())==b.pieceCount);check("dead hit rejection",!b.acceptedHit(m,g,14,0,100));auto fragments=m.fragments;b.paused=true;b.step(100);check("pause keeps particle state",m.fragments.size()==fragments.size()&&m.age==0);b.paused=false;b.step(400);b.draw();b.r.screenshot(b.root/"reports/verification/shared-death.png");
    b.reset();b.x=500;b.face=1;b.attack();for(int i=0;i<200;++i)b.step(8);check("source boxes cause actual HP damage",b.hits>0);b.draw();b.r.screenshot(b.root/"reports/verification/normal-hit.png");
    b.reset();b.x=620;b.face=-1;b.attack();for(int i=0;i<200;++i)b.step(8);check("mirrored weapon boxes cause HP damage",b.hits>0);
    b.reset();size_t beforeCombo=b.events.size();SDL_Event press{};press.type=SDL_KEYDOWN;press.key.keysym.scancode=SDL_SCANCODE_X;b.event(press);for(int i=0;i<240;++i)b.step(8);SDL_Event release{};release.type=SDL_KEYUP;release.key.keysym.scancode=SDL_SCANCODE_X;b.event(release);int comboEvents=0;for(size_t i=beforeCombo;i<b.events.size();++i)if(b.events[i]["event"]=="normal_attack")++comboEvents;check("held X drives source combo stages",comboEvents>=3);b.held.insert(SDL_SCANCODE_RIGHT);SDL_Event focus{};focus.type=SDL_WINDOWEVENT;focus.window.event=SDL_WINDOWEVENT_FOCUS_LOST;b.event(focus);check("focus loss clears movement input",b.held.empty());
    b.reset();b.startSpec(b.specs.at("bloodsword"));check("Q rejected before frenzy",b.casts.empty());b.startSpec(b.specs.at("frenzy"));check("W enables frenzy",b.buff);b.step(1500);b.startSpec(b.specs.at("frenzy"));check("10 second frenzy close restriction",b.buff);b.step(8501);b.startSpec(b.specs.at("frenzy"));check("W disables after restriction",!b.buff);
    b.reset();b.startSpec(b.specs.at("hopsmash"));auto&hop=b.casts.back();auto wave=std::find_if(hop.effects.begin(),hop.effects.end(),[](auto&e){return e.path=="passiveobject/character/swordman/animation/hopsmashsubfront1.ani";});require(wave!=hop.effects.end(),"wave source exists");auto impact=b.point(hop,*wave,wave->begin);check("wave uses verified forward 123 offset after 90 travel",std::abs(impact.first-(hop.x+213))<.01&&std::abs(impact.second-(hop.y+1))<.01);check("source height drives inferred jump arc",hop.motion.z(hop.motion.ready+300)>0);b.step(700);b.draw();b.r.screenshot(b.root/"reports/verification/hopsmash-jump.png");
    Json skillResults=Json::array();for(auto&s:b.c.battle["skills"]){b.reset();b.x=370;b.buff=true;b.buffSince=b.clock-12000;if(s["key"]=="frenzy")b.buff=false;b.startSpec(s,true);require(!b.casts.empty(),"cast exists");double duration=b.casts.back().duration;std::vector<double> times;for(auto&e:b.casts.back().effects)times.push_back(e.begin+(std::min(e.end-e.begin,180.0)/2));times.push_back(100);std::sort(times.begin(),times.end());double age=0;size_t decoded=0;
        for(auto t:times){if(t>=duration)continue;while(age<t){auto dt=std::min(8.0,t-age);b.step(dt);age+=dt;}b.draw();++decoded;}
        b.exportReport("verification/skills/"+s["key"].get<std::string>());skillResults.push_back({{"key",s["key"]},{"render_samples",decoded},{"effect_instances",s["effects"].size()}});
    }
    check("no missing resource or renderer exceptions",b.errors.empty());
    // Exercise catalog transfer outside the eight captured branches, selecting
    // distinct class groups rather than claiming every catalog record is valid.
    Json inferredResults=Json::array();std::set<int> testedGroups;
    for(auto&s:b.c.catalog["skills"]){if(s["type"]!="[active]"||s["body_sequence"].empty()||b.specs.count(s["key"].get<std::string>())||s["key"]=="bloodyrave")continue;int group=-1;for(auto g:s["groups"])if(g.get<int>()<=4&&!testedGroups.count(g.get<int>())&&(g==0||s["groups"].size()==1)){group=g;break;}if(group<0)continue;
        b.reset();auto spec=b.inferred(s);b.startSpec(spec,true);require(!b.casts.empty(),"inferred catalog cast exists");double total=b.casts.back().duration;for(double t=0;t<total;t+=80){b.step(80);b.draw();}inferredResults.push_back({{"key",s["key"]},{"group",group},{"body_stages",s["body_sequence"].size()}});testedGroups.insert(group);
    }
    check("catalog inference sampled across five class groups",testedGroups.size()==5);check("catalog inference has no missing resources",b.errors.empty());
    b.type=2;b.reset();auto&boss=b.monsters[0];b.acceptedHit(boss,boss.generation,++b.serial,0,1000);check("explicit last action selected",boss.state=="death"&&!boss.shared&&b.statePlan(boss,"death"));b.step(300);b.draw();b.r.screenshot(b.root/"reports/verification/independent-death.png");
    b.type=1;b.reset();b.draw();check("three independent monster instances",b.monsters.size()==3&&b.monsters[0].id!=b.monsters[1].id);auto original=b.monsters[1].hp;b.acceptedHit(b.monsters[0],b.monsters[0].generation,++b.serial,0,100);check("entity HP isolation",b.monsters[1].hp==original);b.step(10001);check("full source reaction returns to idle",b.monsters[0].state=="idle");
    b.type=0;b.reset();b.library=true;b.exportReport("verification/final");writeJson(b.root/"reports/verification.json",{{"passed",true},{"checks",checks},{"skills",skillResults},{"inferred_catalog_samples",inferredResults},{"errors",b.errors},{"renderer",b.r.rendererName},{"limitations","Native formula/state machine not fully recovered; resources and mechanics reconstruction tested"}});return 0;
}
static int run(int argc,char**argv){
    auto root=rootDir();bool verification=false;for(int i=1;i<argc;++i)if(std::string(argv[i])=="--verify")verification=true;
    try{
        auto client=root/"client-assets";auto manifest=jsonFile(root/"content/battle.json");
        auto bound=jsonFile(client/"asset-manifest.json");
        if(bound["source_exe_sha256"]!=manifest["source_exe_sha256"])throw std::runtime_error("Portable source version mismatch");
        for(auto&entry:bound["archives"]){auto name=entry["path"].get<std::string>();if(name.find("..")!=std::string::npos||fs::u8path(name).is_absolute())throw std::runtime_error("Invalid asset path");if(sha256(client/fs::u8path(name))!=entry["sha256"].get<std::string>())throw std::runtime_error("Portable asset hash mismatch: "+name);}
        if(verification)SDL_setenv("DNF_DEMO_HIDDEN","1",1);SDL_SetMainReady();if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER))throw std::runtime_error(SDL_GetError());
        {Content content(root,client);Canvas canvas(content);Battle battle(content,canvas,root);if(verification)return verify(battle);
            auto previous=SDL_GetPerformanceCounter();double accumulator=0;while(battle.running){SDL_Event e;while(SDL_PollEvent(&e))battle.event(e);auto now=SDL_GetPerformanceCounter();double dt=std::min(100.0,double(now-previous)*1000/SDL_GetPerformanceFrequency());previous=now;accumulator+=dt;while(accumulator>=8){battle.step(8);accumulator-=8;}battle.draw();SDL_RenderPresent(canvas.renderer);SDL_Delay(1);}writeJson(root/"reports/last-session.json",{{"events",battle.events},{"errors",battle.errors},{"source_reads",{{"pvf",content.pvf.reads()},{"npk",content.assets.reads()}}}});
        }SDL_Quit();return 0;
    }catch(const std::exception&e){fs::create_directories(root/"reports");writeJson(root/"reports/startup-error.json",{{"error",e.what()}});std::cerr<<e.what()<<std::endl;if(!verification)MessageBoxW(nullptr,wide(e.what()).c_str(),L"Battle demo",MB_OK|MB_ICONERROR);return 1;}
}
DNF_ENTRY(run)
