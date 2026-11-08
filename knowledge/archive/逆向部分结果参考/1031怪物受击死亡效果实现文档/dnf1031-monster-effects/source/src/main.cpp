// Independent 1031 visual preview. No process injection or damage simulation.
#define SDL_MAIN_HANDLED
#include <windows.h>
#include <shellapi.h>
#include <bcrypt.h>
#include <SDL.h>
#include "dnf/resources.hpp"
#include "dnf/geometry.hpp"
#include "dnf/shared_death.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#include "stb_image_write.h"
#pragma clang diagnostic pop
using namespace dnf;
namespace fs = std::filesystem;

static std::wstring wide(const std::string& s) {
    int n=MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,s.data(),int(s.size()),nullptr,0);
    std::wstring out(n,0); if(n)MultiByteToWideChar(CP_UTF8,0,s.data(),int(s.size()),out.data(),n);return out;
}
static std::string utf8(const std::wstring& s) {
    int n=WideCharToMultiByte(CP_UTF8,0,s.data(),int(s.size()),nullptr,0,nullptr,nullptr);
    std::string out(n,0);if(n)WideCharToMultiByte(CP_UTF8,0,s.data(),int(s.size()),out.data(),n,nullptr,nullptr);return out;
}
static fs::path executableRoot() {wchar_t path[32768];GetModuleFileNameW(nullptr,path,32768);return fs::path(path).parent_path();}
static std::string rel(const std::string& source,const std::string& value) {return normalize((fs::u8path(source).parent_path()/fs::u8path(value)).generic_u8string());}
static Json jsonFile(const fs::path& file) {std::ifstream in(file);if(!in)throw std::runtime_error("Cannot read: "+file.u8string());Json j;in>>j;return j;}
static std::string sha256(const fs::path& path) {
    std::ifstream stream(path,std::ios::binary);if(!stream)throw std::runtime_error("Cannot hash: "+path.u8string());
    BCRYPT_ALG_HANDLE algorithm=nullptr;BCRYPT_HASH_HANDLE hash=nullptr;
    if(BCryptOpenAlgorithmProvider(&algorithm,BCRYPT_SHA256_ALGORITHM,nullptr,0)<0)throw std::runtime_error("SHA256 provider failed");
    DWORD size=0,got=0;BCryptGetProperty(algorithm,BCRYPT_OBJECT_LENGTH,(PUCHAR)&size,sizeof(size),&got,0);
    Bytes object(size),digest(32),buffer(65536);
    if(BCryptCreateHash(algorithm,&hash,object.data(),size,nullptr,0,0)<0){BCryptCloseAlgorithmProvider(algorithm,0);throw std::runtime_error("SHA256 creation failed");}
    while(stream){stream.read((char*)buffer.data(),buffer.size());auto n=stream.gcount();if(n&&BCryptHashData(hash,buffer.data(),ULONG(n),0)<0)throw std::runtime_error("SHA256 update failed");}
    if(BCryptFinishHash(hash,digest.data(),32,0)<0)throw std::runtime_error("SHA256 finish failed");
    BCryptDestroyHash(hash);BCryptCloseAlgorithmProvider(algorithm,0);
    std::ostringstream out;for(auto b:digest)out<<std::hex<<std::setw(2)<<std::setfill('0')<<int(b);return out.str();
}
static double boundary(const Animation& ani,int frame) {
    if(frame<0||frame>=int(ani.frames.size()))throw std::runtime_error("Frame event outside parent ANI: "+ani.path);
    double time=0;for(int i=0;i<frame;++i)time+=ani.frames[i].duration;return time;
}
struct Track {std::shared_ptr<Animation> animation;double start=0,end=0,x=0,y=0;int layer=0;bool hold=false;std::string role;};
struct Plan {std::string key,entry,kind,error;std::vector<Track> tracks;std::shared_ptr<Animation> base;double duration=1;Json issues=Json::array();int unexecuted=0,visibleFrames=0;bool valid()const{return base&&!base->frames.empty()&&error.empty();}};

struct Content {
    Json catalog;Pvf pvf;Assets assets;std::map<std::string,Plan> plans;int selected=-1;
    explicit Content(const fs::path& root,Json data):catalog(std::move(data)),pvf(root/"Script.pvf"),assets(root,pvf) {}
    Json& monsters(){return catalog["monsters"];}
    void addTrack(Plan& plan,const std::string& path,double start,int layer,double x,double y,bool hold,
                  double limit,std::set<std::string> stack={},int depth=0) {
        if(depth>12||stack.count(path))throw std::runtime_error("Recursive ANI/ALS graph: "+path);
        if(plan.tracks.size()>=256)throw std::runtime_error("Animation instance budget exceeded");
        stack.insert(path);auto ani=assets.animation(path);
        if(ani->frames.empty())throw std::runtime_error("Empty ANI: "+path);
        double end=std::min(limit,start+std::max(1,ani->duration));
        plan.tracks.push_back({ani,start,end,x,y,layer,hold,depth?"als":hold?"base":"sub"});
        if(!pvf.has(path+".als"))return;
        auto script=pvf.script(path+".als");std::map<std::string,std::string> declarations;
        struct Event{int frame,layer;std::string name;bool add;};std::vector<Event> events;
        for(auto& field:script.fields) {
            auto tag=normalize(field.tag);auto& v=field.values;
            if(tag=="[use animation]"&&v.size()==2&&v[0].is_string()&&v[1].is_string())declarations[v[1].get<std::string>()]=rel(path,v[0]);
            else if((tag=="[add]"||tag=="[remove]")&&v.size()==3&&v[0].is_number_integer()&&v[1].is_number_integer()&&v[2].is_string())events.push_back({v[0],v[1],v[2],tag=="[add]"});
            else plan.issues.push_back({{"resource",script.path},{"offset",field.offset},{"unsupported",field.tag}});
        }
        std::stable_sort(events.begin(),events.end(),[](auto&a,auto&b){return a.frame<b.frame;});
        for(size_t i=0;i<events.size();++i)if(events[i].add) {
            auto e=events[i];
            try {
                if(!declarations.count(e.name))throw std::runtime_error("Undeclared ALS name: "+e.name);
                double childStart=start+boundary(*ani,e.frame),childLimit=std::min(limit,end);
                for(size_t j=i+1;j<events.size();++j)if(events[j].name==e.name){childLimit=std::min(childLimit,start+boundary(*ani,events[j].frame));break;}
                if(childLimit>childStart)addTrack(plan,declarations.at(e.name),childStart,layer+e.layer,x,y,false,childLimit,stack,depth+1);
            }catch(const std::exception& ex){plan.issues.push_back({{"resource",script.path},{"error",ex.what()}});}
        }
    }
    void select(int index) {
        assets.clearTransient();plans.clear();selected=index;auto& row=monsters().at(index);
        for(auto it=row["states"].begin();it!=row["states"].end();++it) {
            Plan p;p.key=it.key();auto& src=it.value();p.entry=src.value("entry","");p.kind=src.value("kind","");p.issues=src["issues"];p.unexecuted=int(src["unexecuted_tags"].size());
            try {
                if(src["tracks"].empty())throw std::runtime_error("No unambiguous animation binding");
                auto base=std::find_if(src["tracks"].begin(),src["tracks"].end(),[](const Json& t){return t["role"]=="base";});
                if(base==src["tracks"].end())throw std::runtime_error("No base animation");
                p.base=assets.animation((*base)["path"]);p.duration=std::max(1,p.base->duration);
                for(auto& track:src["tracks"]) {
                    try {
                        double start=boundary(*p.base,track["start_frame"]);
                        addTrack(p,track["path"],start,track["layer"],track["x"],track["y"],track["role"]=="base",1e12);
                    }catch(const std::exception& ex){if(track["role"]=="base")throw;p.issues.push_back({{"resource",track["path"]},{"error",ex.what()}});}
                }
                for(auto& t:p.tracks) {
                    p.duration=std::max(p.duration,t.end);
                    // Decode every unique source frame before enabling this state.
                    std::set<std::string> images;
                    for(auto& f:t.animation->frames)if(!f.image.empty()) {
                        auto key=f.image+"#"+std::to_string(f.imageFrame);
                        if(images.insert(key).second){auto pixels=assets.pixels(f.image,f.imageFrame);bool visible=false;for(size_t i=3;i<pixels.rgba.size();i+=4)if(pixels.rgba[i]){visible=true;break;}if(visible)++p.visibleFrames;}
                    }
                }
                if(!p.visibleFrames)throw std::runtime_error("Source IMG frames are fully transparent placeholders; no visible animation");
                std::stable_sort(p.tracks.begin(),p.tracks.end(),[](auto&a,auto&b){return a.layer<b.layer;});
            }catch(const std::exception& ex){p.error=ex.what();p.tracks.clear();p.base.reset();}
            plans.emplace(p.key,std::move(p));
        }
    }
    bool has(const std::string& key)const {auto i=plans.find(key);return i!=plans.end()&&i->second.valid();}
    Json description()const {
        Json result=Json::object();
        for(auto&[key,p]:plans){Json tracks=Json::array();for(auto&t:p.tracks)tracks.push_back({{"path",t.animation->path},{"start_ms",t.start},{"end_ms",t.end},{"layer",t.layer},{"x",t.x},{"y",t.y},{"role",t.role},{"frames",t.animation->frames.size()}});
            result[key]={{"available",p.valid()},{"entry",p.entry},{"duration_ms",p.duration},{"tracks",tracks},{"visible_image_frames",p.visibleFrames},{"error",p.error},{"issues",p.issues},{"unexecuted_act_tags",p.unexecuted}};}
        return result;
    }
};

struct Texture {SDL_Texture* value=nullptr;int w=0,h=0,x=0,y=0;};
struct Canvas {
    Content& content;SDL_Window* window=nullptr;SDL_Renderer* renderer=nullptr;
    std::map<std::string,Texture> sprites,texts;Json unsupported=Json::array();std::set<std::string> noted;
    double fit=1,offsetX=0,offsetY=0;
    explicit Canvas(Content& c,bool hidden):content(c) {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0");
        window=SDL_CreateWindow(u8"1031 · 怪物受击与死亡动画",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,800,
            SDL_WINDOW_RESIZABLE|SDL_WINDOW_ALLOW_HIGHDPI|(hidden?SDL_WINDOW_HIDDEN:SDL_WINDOW_SHOWN));
        if(!window)throw std::runtime_error(SDL_GetError());
        renderer=SDL_CreateRenderer(window,-1,hidden?SDL_RENDERER_SOFTWARE:SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        if(!renderer)renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
        if(!renderer)throw std::runtime_error(SDL_GetError());
        SDL_SetWindowMinimumSize(window,1024,640);SDL_RenderSetLogicalSize(renderer,1280,800);SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);SDL_StopTextInput();
    }
    void clearSprites(){for(auto&[_,t]:sprites)SDL_DestroyTexture(t.value);sprites.clear();}
    ~Canvas(){clearSprites();for(auto&[_,t]:texts)SDL_DestroyTexture(t.value);SDL_DestroyRenderer(renderer);SDL_DestroyWindow(window);}
    Texture& sprite(const std::string& image,int frame,bool silhouette=false) {
        auto key=image+"#"+std::to_string(frame)+(silhouette?"#white":"");auto found=sprites.find(key);if(found!=sprites.end())return found->second;
        auto p=content.assets.pixels(image,frame);Texture t;t.w=p.width;t.h=p.height;t.x=p.x;t.y=p.y;
        if(silhouette)for(size_t i=0;i<p.rgba.size();i+=4)p.rgba[i]=p.rgba[i+1]=p.rgba[i+2]=255;
        if(t.w&&t.h){t.value=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STATIC,t.w,t.h);if(!t.value||SDL_UpdateTexture(t.value,nullptr,p.rgba.data(),t.w*4))throw std::runtime_error(SDL_GetError());}
        return sprites.emplace(key,t).first->second;
    }
    void fitSelected() {
        double minX=1e9,minY=1e9,maxX=-1e9,maxY=-1e9;
        // Fit the resting model, keeping one stable camera throughout reactions.
        // Distant death fragments must not shrink every other animation.
        const Plan* reference=nullptr;
        if(content.has("idle"))reference=&content.plans.at("idle");
        else for(auto&[_,p]:content.plans)if(p.valid()){reference=&p;break;}
        if(reference)for(auto&t:reference->tracks)for(auto& f:t.animation->frames)if(!f.image.empty()){
            auto& img=sprite(f.image,f.imageFrame);double x=f.x+t.x+img.x,y=f.y+t.y+img.y;
            minX=std::min(minX,x);minY=std::min(minY,y);maxX=std::max(maxX,x+img.w);maxY=std::max(maxY,y+img.h);
        }
        if(maxX>minX&&maxY>minY){fit=std::clamp(std::min({2.5,760/(maxX-minX),300/(maxY-minY)}),.1,4.0);offsetX=(minX+maxX)/2;offsetY=(minY+maxY)/2;}
        else{fit=1;offsetX=offsetY=0;}
    }
    void rect(float x,float y,float w,float h,SDL_Color color,bool fill=true){SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);SDL_FRect r{x,y,w,h};if(fill)SDL_RenderFillRectF(renderer,&r);else SDL_RenderDrawRectF(renderer,&r);}
    void line(int x1,int y1,int x2,int y2,SDL_Color c){SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,c.a);SDL_RenderDrawLine(renderer,x1,y1,x2,y2);}
    void text(const std::string& message,int x,int y,int size,SDL_Color color={215,225,234,255},int maxW=0) {
        if(message.empty())return;
        if(texts.size()>400){for(auto&[_,t]:texts)SDL_DestroyTexture(t.value);texts.clear();}
        std::string key=message+"#"+std::to_string(size);auto found=texts.find(key);
        if(found==texts.end()) {
            auto s=wide(message);HDC dc=CreateCompatibleDC(nullptr);HFONT font=CreateFontW(-size,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH,L"Microsoft YaHei");
            auto oldfont=SelectObject(dc,font);SIZE dim{};GetTextExtentPoint32W(dc,s.data(),int(s.size()),&dim);int w=std::max(4L,dim.cx+4),h=size+9;
            BITMAPINFO bi{};bi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);bi.bmiHeader.biWidth=w;bi.bmiHeader.biHeight=-h;bi.bmiHeader.biPlanes=1;bi.bmiHeader.biBitCount=32;bi.bmiHeader.biCompression=BI_RGB;
            void* bits=nullptr;auto bitmap=CreateDIBSection(dc,&bi,DIB_RGB_COLORS,&bits,nullptr,0);auto oldbmp=SelectObject(dc,bitmap);
            memset(bits,0,size_t(w)*h*4);SetTextColor(dc,RGB(255,255,255));SetBkMode(dc,TRANSPARENT);TextOutW(dc,2,1,s.data(),int(s.size()));GdiFlush();
            Bytes rgba(size_t(w)*h*4);auto* src=(uint8_t*)bits;
            for(size_t i=0;i<size_t(w)*h;++i){rgba[i*4]=rgba[i*4+1]=rgba[i*4+2]=255;rgba[i*4+3]=std::max({src[i*4],src[i*4+1],src[i*4+2]});}
            SelectObject(dc,oldbmp);SelectObject(dc,oldfont);DeleteObject(bitmap);DeleteObject(font);DeleteDC(dc);
            Texture t;t.w=w;t.h=h;t.value=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STATIC,w,h);SDL_UpdateTexture(t.value,nullptr,rgba.data(),w*4);SDL_SetTextureBlendMode(t.value,SDL_BLENDMODE_BLEND);found=texts.emplace(key,t).first;
        }
        auto&t=found->second;SDL_Rect src{0,0,maxW?std::min(maxW,t.w):t.w,t.h};SDL_FRect dst{float(x),float(y),float(src.w),float(t.h)};
        SDL_SetTextureColorMod(t.value,color.r,color.g,color.b);SDL_SetTextureAlphaMod(t.value,color.a);SDL_RenderCopyF(renderer,t.value,&src,&dst);
    }
    void plan(const Plan& plan,double ms,int facing,double zoom,bool loop,bool silhouette=false,double alpha=1) {
        if(!plan.valid())return;double time=loop?std::fmod(std::max(0.0,ms),plan.duration):std::clamp(ms,0.0,plan.duration);
        SDL_Rect clip{328,162,932,410};SDL_RenderSetClipRect(renderer,&clip);double scale=fit*zoom;
        double ax=794-facing*offsetX*scale,ay=382-offsetY*scale;
        for(auto&t:plan.tracks){if(time<t.start||(!t.hold&&time>=t.end))continue;
            auto pose=t.animation->samplePose(std::max(0.0,time-t.start),false);if(pose.image.empty())continue;
            auto& image=sprite(pose.image,pose.imageFrame,silhouette);if(!image.value)continue;
            if(pose.flip&1)pose.scaleX=-pose.scaleX;if(pose.flip&2)pose.scaleY=-pose.scaleY;
            if(!pose.unsupported.empty()&&noted.insert(t.animation->path).second)unsupported.push_back({{"path",t.animation->path},{"nodes",pose.unsupported}});
            auto q=imageQuad(ax+facing*t.x*scale,ay+t.y*scale,pose.x,pose.y,image.x,image.y,image.w,image.h,facing,pose.scaleX*scale,pose.scaleY*scale,radiansToDegrees(pose.rotationRadians));
            auto byte=[](double v){return uint8_t(std::lround(std::clamp(v,0.0,255.0)));};SDL_Color color{byte(pose.rgba[0]),byte(pose.rgba[1]),byte(pose.rgba[2]),byte(pose.rgba[3])};
            if(silhouette)color.r=color.g=color.b=255;color.a=byte(color.a*alpha);
            bool finite=true;for(auto&v:q)if(!std::isfinite(v.x)||!std::isfinite(v.y)||std::abs(v.x)>1e7||std::abs(v.y)>1e7)finite=false;if(!finite)continue;
            SDL_Vertex vertices[4];const SDL_FPoint uv[]={{0,0},{1,0},{1,1},{0,1}};for(int i=0;i<4;++i)vertices[i]={{float(q[i].x),float(q[i].y)},color,uv[i]};const int indices[]={0,1,2,0,2,3};
            SDL_SetTextureBlendMode(image.value,!silhouette&&(pose.blend==1||pose.blend==2)?SDL_BLENDMODE_ADD:SDL_BLENDMODE_BLEND);if(SDL_RenderGeometry(renderer,image.value,vertices,4,indices,6))throw std::runtime_error(SDL_GetError());
        }
        SDL_RenderSetClipRect(renderer,nullptr);
    }
    std::array<double,4> bounds(const Plan& p,double ms,bool loop){
        double time=loop?std::fmod(ms,p.duration):std::clamp(ms,0.0,p.duration);
        double x1=1e9,y1=1e9,x2=-1e9,y2=-1e9;
        for(auto&t:p.tracks){if(time<t.start||(!t.hold&&time>=t.end))continue;auto pose=t.animation->samplePose(time-t.start,false);if(pose.image.empty())continue;auto&i=sprite(pose.image,pose.imageFrame);
            double sx=pose.scaleX*(pose.flip&1?-1:1),sy=pose.scaleY*(pose.flip&2?-1:1);
            auto q=imageQuad(t.x,t.y,pose.x,pose.y,i.x,i.y,i.w,i.h,1,sx,sy,radiansToDegrees(pose.rotationRadians));
            for(auto&v:q){x1=std::min(x1,v.x);y1=std::min(y1,v.y);x2=std::max(x2,v.x);y2=std::max(y2,v.y);}}
        if(x2<=x1||y2<=y1)return {offsetX-30,offsetY-40,60,80};return{x1,y1,x2-x1,y2-y1};
    }
    void effectSprite(const std::string& path,int frame,double x,double y,double size,double rotation,SDL_Color color,int facing,double zoom,bool additive=false){
        auto&i=sprite(path,frame);if(!i.value)return;double scale=fit*zoom;SDL_FRect dst{float(794+facing*(x-offsetX)*scale-i.w*size*scale*.5),float(382+(y-offsetY)*scale-i.h*size*scale*.5),float(i.w*size*scale),float(i.h*size*scale)};
        SDL_SetTextureBlendMode(i.value,additive?SDL_BLENDMODE_ADD:SDL_BLENDMODE_BLEND);SDL_SetTextureColorMod(i.value,color.r,color.g,color.b);SDL_SetTextureAlphaMod(i.value,color.a);
        SDL_RenderCopyExF(renderer,i.value,nullptr,&dst,facing*rotation,nullptr,facing<0?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
        SDL_SetTextureColorMod(i.value,255,255,255);SDL_SetTextureAlphaMod(i.value,255);
    }
    void screenshot(const fs::path& file){int w,h;SDL_GetRendererOutputSize(renderer,&w,&h);Bytes pixels(size_t(w)*h*4);if(SDL_RenderReadPixels(renderer,nullptr,SDL_PIXELFORMAT_RGBA32,pixels.data(),w*4))throw std::runtime_error(SDL_GetError());fs::create_directories(file.parent_path());std::ofstream stream(file,std::ios::binary);auto write=[](void*c,void*d,int n){((std::ofstream*)c)->write((char*)d,n);};if(!stbi_write_png_to_func(write,&stream,w,h,4,pixels.data(),w*4)||!stream)throw std::runtime_error("Screenshot failed");}
};

static const SDL_Color muted{131,151,168,255},accent{84,212,199,255},white{230,239,247,255},orange{248,177,118,255};
static std::string label(const std::string& key){return key=="damage1"?u8"受击 1":key=="damage2"?u8"受击 2":key=="death"?u8"死亡":key=="down"?u8"倒地":u8"待机";}
struct Demo {
    Content& content;Canvas& canvas;std::vector<int> filtered;int row=0,scroll=0,facing=1,hits=0;
    bool deathOnly=true,searchFocus=false,paused=false,completed=false,automatic=false,info=false,dragging=false;
    std::string search,composition,state="idle",notice;double time=0,clock=0,speed=1,zoom=1,autoTime=0;int autoIndex=0;
    Json events=Json::array();fs::path report;int screenshots=0;
    int deathMode=0;bool sharedActive=false;Plan sharedPlan,frozenPlan;
    double frozenTime=0,burst=220,gravity=1500,pieceSpeed=400,particleLife=3000;bool frozenLoop=false;
    std::array<double,4> frozenBounds{};std::vector<DeathParticle> fragments;
    std::shared_ptr<Animation> pieceAnimation,flashAnimation,smokeAnimation;
    Json deathDetails=Json::object();
    Demo(Content& c,Canvas& cv,fs::path r):content(c),canvas(cv),report(std::move(r)){filter();}
    void log(const std::string& event,const std::string& result="ok"){events.push_back({{"wall_ms",clock},{"event",event},{"state",state},{"time_ms",time},{"monster",content.selected>=0?content.monsters()[content.selected]["path"]:Json(nullptr)},{"result",result}});}
    bool configured(int index,const std::string& key)const {auto&s=content.catalog["monsters"][index]["states"];return s.contains(key)&&!s[key]["tracks"].empty();}
    bool sharedConfigured(int index)const{return DeathProfile(content.catalog["monsters"][index]).configured&&(configured(index,"idle")||configured(index,"damage1"));}
    bool useShared()const{return deathMode==1||(deathMode==0&&!content.has("death")&&!content.monsters()[content.selected]["states"].contains("death"));}
    bool canDeath()const{return useShared()?sharedPlan.valid():content.has("death");}
    void prepareShared(){
        sharedPlan=Plan{};sharedPlan.key="death";sharedPlan.kind="shared_death_preview";sharedPlan.entry="MOB [die effect] + frozen pose + Monster/Common";
        DeathProfile profile(content.monsters()[content.selected]);deathDetails=profile.describe();pieceAnimation.reset();flashAnimation.reset();smokeAnimation.reset();
        try{
            if(!profile.configured)throw std::runtime_error("Missing/ambiguous/unsupported [die effect] configuration");
            if(!content.has("idle")&&!content.has("damage1"))throw std::runtime_error("No visible pose available to freeze");
            auto ptl=content.pvf.script("monster/common/particle/monsterdiepiece.ptl");
            gravity=ptl.number("[gravity]",1500);particleLife=ptl.number("[life time]",3000);auto vars=ptl.values("[move variable 1]");pieceSpeed=vars.empty()?400:vars[0].get<double>();
            int count=int(ptl.number("[maximum create number]",10));
            if(gravity<=0||particleLife<=0||count<0||count>128)throw std::runtime_error("Unsupported common particle parameters");
            deathDetails["ptl"]=ptl.path;deathDetails["count"]=count;deathDetails["gravity"]=gravity;deathDetails["speed"]=pieceSpeed;deathDetails["life_ms"]=particleLife;
            deathDetails["preview_policy"]={{"white_at_ms",60},{"burst_ms",burst},{"body_fade_ms",90},{"trajectory","analytic ballistic then stop; seeded by MOB path"}};
            if(profile.pieces){for(int f=0;f<4;++f)canvas.sprite(profile.image,f);pieceAnimation=content.assets.animation("monster/common/animation/monsterdiepiece.ani");}
            if(profile.flash)flashAnimation=content.assets.animation("monster/common/animation/monsterdieflash.ani");
            if(profile.smoke)smokeAnimation=content.assets.animation("monster/common/animation/monsterdiesmoke.ani");
            sharedPlan.duration=burst+particleLife;sharedPlan.base=std::make_shared<Animation>();sharedPlan.base->path="preview://shared-death-clock";
            for(double t=0;t<sharedPlan.duration;t+=50){AniFrame f;f.duration=int(std::min(50.0,sharedPlan.duration-t));sharedPlan.base->frames.push_back(f);}
            sharedPlan.base->duration=int(sharedPlan.duration);
        }catch(const std::exception&ex){sharedPlan.error=ex.what();sharedPlan.base.reset();}
        deathDetails["available"]=sharedPlan.valid();deathDetails["error"]=sharedPlan.error;
    }
    void freeze(){
        if(state!="death"){auto*p=current();if(!p||!p->valid())p=content.has("idle")?&content.plans.at("idle"):&content.plans.at("damage1");frozenPlan=*p;frozenTime=time;frozenLoop=state=="idle";}
        frozenBounds=canvas.bounds(frozenPlan,frozenTime,frozenLoop);auto&b=frozenBounds;
        fragments=deathParticles(deathSeed(content.monsters()[content.selected]["path"]),deathDetails.value("count",10),b[0]+b[2]/2,b[1]+b[3]/2,b[2],b[3],pieceSpeed);
        deathDetails["frozen"]={{"state",frozenPlan.key},{"entry",frozenPlan.entry},{"time_ms",frozenTime},{"loop",frozenLoop},{"bounds",b}};
        if(frozenPlan.base)deathDetails["frozen"]["frame"]=frozenPlan.base->frameAt(int64_t(frozenTime),frozenLoop);
    }
    void sharedDraw(){
        if(!sharedPlan.valid()||!frozenPlan.valid())return;
        double fade=std::clamp(1-(time-burst)/90,0.0,1.0);
        if(fade>0)canvas.plan(frozenPlan,frozenTime,facing,zoom,frozenLoop,time>=60,fade);
        if(time<burst)return;DeathProfile profile(content.monsters()[content.selected]);auto&b=frozenBounds;double age=time-burst,seconds=age/1000;
        SDL_Rect clip{328,162,932,410};SDL_RenderSetClipRect(canvas.renderer,&clip);
        if(profile.pieces&&pieceAnimation&&age<particleLife){auto pose=pieceAnimation->samplePose(age,false);for(auto&p:fragments){auto pos=deathPosition(p,seconds,gravity,b[1]+b[3]);canvas.effectSprite(profile.image,p.frame,pos.x,pos.y,p.size,pos.angle,{255,255,255,uint8_t(pose.rgba[3])},facing,zoom);}}
        if(profile.flash&&flashAnimation&&age<flashAnimation->duration){auto p=flashAnimation->samplePose(age,false);canvas.effectSprite(p.image,p.imageFrame,b[0]+b[2]/2,b[1]+b[3]/2,std::max(.5,p.scaleX),0,{255,255,255,uint8_t(p.rgba[3])},facing,zoom,true);}
        if(profile.smoke&&smokeAnimation&&age<1500){double k=age/1500;canvas.effectSprite("monster/common/monsterdiesmoke.img",0,b[0]+b[2]/2,b[1]+b[3]-k*30,1.4+k*2.5,0,{205,205,205,uint8_t(55*(1-k))},facing,zoom,true);}
        SDL_RenderSetClipRect(canvas.renderer,nullptr);
    }
    void filter(){filtered.clear();auto term=normalize(search);for(int i=0;i<int(content.monsters().size());++i){auto&r=content.monsters()[i];if(deathOnly&&!configured(i,"death")&&!sharedConfigured(i))continue;std::string text=normalize(r["name"].get<std::string>()+" "+r["path"].get<std::string>()+" "+r["ids"].dump());if(term.empty()||text.find(term)!=text.npos)filtered.push_back(i);}row=0;scroll=0;}
    void select(int index){canvas.clearSprites();content.select(index);canvas.fitSelected();prepareShared();frozenPlan=Plan{};fragments.clear();sharedActive=false;state="idle";time=0;hits=0;completed=false;paused=false;automatic=false;notice.clear();log("monster_selected");if(!content.has("idle"))notice=u8"该怪物的待机资源暂不可播放，可查看其他动作。";
        auto found=std::find(filtered.begin(),filtered.end(),index);if(found!=filtered.end()){row=int(found-filtered.begin());scroll=std::clamp(row-4,0,std::max(0,int(filtered.size())-12));}}
    void move(int delta){if(filtered.empty())return;row=std::clamp(row+delta,0,int(filtered.size())-1);select(filtered[row]);}
    Plan* current(){if(state=="death"&&sharedActive)return &sharedPlan;auto i=content.plans.find(state);return i==content.plans.end()?nullptr:&i->second;}
    void start(const std::string& key,bool fromAuto=false){if(!fromAuto)automatic=false;
        if(key=="death"?!canDeath():!content.has(key)){notice=key=="death"?u8"当前死亡模式不可用；按 T 切换模式或 F1 查看资源诊断。":u8"当前动作资源不可播放，请切换怪物或动作。";log("action_rejected",key);return;}
        if(state=="death"&&key!="death"&&key!="idle"){notice=u8"先点「复活 / 重置」，再播放受击。";log("action_rejected","dead");return;}
        if(key=="death"){bool shared=useShared();if(shared)freeze();sharedActive=shared;}
        state=key;time=0;paused=false;completed=false;notice.clear();if(key=="damage1"||key=="damage2")++hits;log("action_started");
    }
    void reset(){automatic=false;state="idle";time=0;paused=false;completed=false;hits=0;notice.clear();sharedActive=false;frozenPlan=Plan{};fragments.clear();log("reset");}
    void autoPlay(){if(!canDeath()){notice=u8"当前死亡模式不可用，按 T 切换。";log("sequence_rejected","no_death_animation");return;}reset();automatic=true;autoTime=0;autoIndex=0;log("sequence_started");}
    void step(double dt){clock+=dt;if(paused)return;
        if(automatic){autoTime+=dt*speed;double d1=content.has("damage1")?content.plans.at("damage1").duration:0,d2=content.has("damage2")?content.plans.at("damage2").duration:0;if(useShared()){d1=std::min(500.0,d1);d2=std::min(500.0,d2);}double thresholds[]={700,700+d1+650,700+d1+650+d2+650};const char* keys[]={"damage1","damage2","death"};while(autoIndex<3&&autoTime>=thresholds[autoIndex]){std::string key=keys[autoIndex++];if(key=="death"&&useShared()&&content.has("damage1")){start("damage1",true);time=std::min(50.0,content.plans.at("damage1").duration*.5);}if(key=="death"?canDeath():content.has(key))start(key,true);} }
        auto* p=current();if(!p||!p->valid()||(completed&&state!="idle"))return;time+=dt*speed;
        if(state=="idle")time=std::fmod(time,p->duration);
        else if(time>=p->duration&&!completed){time=p->duration;completed=true;log("action_completed");if(state=="damage1"||state=="damage2"){state="idle";time=0;completed=false;}else if(state=="death")automatic=false;}
    }
    void frameStep(int delta){auto*p=current();if(!p||!p->valid())return;automatic=false;paused=true;completed=false;int index=int(p->base->frameAt(int64_t(time),false));index=std::clamp(index+delta,0,int(p->base->frames.size())-1);time=boundary(*p->base,index);log("frame_step");}
    void seek(float x){auto*p=current();if(!p||!p->valid())return;automatic=false;paused=true;completed=false;time=std::clamp((x-360)/868.0,0.0,1.0)*p->duration;log("timeline_seek");}
    void toggleSearch(bool on){searchFocus=on;if(on){SDL_StartTextInput();SDL_Rect r{26,98,270,34};SDL_SetTextInputRect(&r);}else{SDL_StopTextInput();composition.clear();}}
    void eraseSearch(){if(!search.empty()){size_t p=search.size()-1;while(p&&((uint8_t(search[p])&0xC0)==0x80))--p;search.erase(p);filter();}}
    void command(SDL_Scancode key){
        if(key==SDL_SCANCODE_1||key==SDL_SCANCODE_H)start("damage1");else if(key==SDL_SCANCODE_2)start("damage2");else if(key==SDL_SCANCODE_D)start("death");else if(key==SDL_SCANCODE_R)reset();
        else if(key==SDL_SCANCODE_A)autoPlay();else if(key==SDL_SCANCODE_3)start("down");else if(key==SDL_SCANCODE_SPACE){paused=!paused;log("pause_toggled");}
        else if(key==SDL_SCANCODE_PERIOD)frameStep(1);else if(key==SDL_SCANCODE_COMMA)frameStep(-1);else if(key==SDL_SCANCODE_L){facing=-facing;log("facing_changed");}
        else if(key==SDL_SCANCODE_F4){speed=speed==1?.5:speed==.5?.25:speed==.25?2:1;log("speed_changed");}
        else if(key==SDL_SCANCODE_EQUALS||key==SDL_SCANCODE_KP_PLUS)zoom=std::min(3.0,zoom+.25);else if(key==SDL_SCANCODE_MINUS||key==SDL_SCANCODE_KP_MINUS)zoom=std::max(.25,zoom-.25);
        else if(key==SDL_SCANCODE_UP)move(-1);else if(key==SDL_SCANCODE_DOWN)move(1);else if(key==SDL_SCANCODE_PAGEUP)move(-12);else if(key==SDL_SCANCODE_PAGEDOWN)move(12);
        else if(key==SDL_SCANCODE_F2){deathOnly=!deathOnly;filter();}else if(key==SDL_SCANCODE_F1)info=!info;
        else if(key==SDL_SCANCODE_T){deathMode=(deathMode+1)%3;reset();log("death_mode_changed",std::to_string(deathMode));}
        else if(key==SDL_SCANCODE_SLASH)toggleSearch(true);else if(key==SDL_SCANCODE_F12)canvas.screenshot(report/("manual-"+std::to_string(screenshots++)+".png"));
    }
    void click(float x,float y){
        if(x>=930&&x<=1248&&y>=88&&y<=124){command(SDL_SCANCODE_T);return;}
        if(x>=24&&x<300&&y>=96&&y<136){toggleSearch(true);return;}toggleSearch(false);
        if(x>=24&&x<300&&y>=147&&y<178){deathOnly=!deathOnly;filter();return;}
        if(x>=20&&x<306&&y>=190&&y<706){int n=scroll+int(y-190)/43;if(n>=0&&n<int(filtered.size()))select(filtered[n]);return;}
        if(y>=638&&y<684){if(x>=340&&x<480)start("damage1");else if(x>=492&&x<632)start("damage2");else if(x>=644&&x<784)start("death");else if(x>=796&&x<936)reset();else if(x>=948&&x<1248)autoPlay();}
        if(y>=700&&y<739){if(x>=340&&x<460){paused=!paused;log("pause_toggled");}else if(x>=472&&x<592)command(SDL_SCANCODE_F4);else if(x>=604&&x<724)command(SDL_SCANCODE_L);else if(x>=736&&x<856)frameStep(-1);else if(x>=868&&x<988)frameStep(1);else if(x>=1000&&x<1248)info=!info;}
        if(x>=360&&x<=1228&&y>=587&&y<=625){seek(x);dragging=true;}
    }
    void event(const SDL_Event& e,bool& running){
        if(e.type==SDL_QUIT){running=false;return;}
        if(e.type==SDL_TEXTINPUT&&searchFocus){search+=e.text.text;composition.clear();filter();}
        if(e.type==SDL_TEXTEDITING&&searchFocus)composition=e.edit.text;
        if(e.type==SDL_KEYDOWN&&!e.key.repeat){auto key=e.key.keysym.scancode;
            if(searchFocus){if(key==SDL_SCANCODE_ESCAPE)toggleSearch(false);else if(key==SDL_SCANCODE_RETURN){toggleSearch(false);if(!filtered.empty())select(filtered[0]);}else if(key==SDL_SCANCODE_BACKSPACE)eraseSearch();else if(key==SDL_SCANCODE_DOWN){toggleSearch(false);move(0);}return;}
            if(key==SDL_SCANCODE_ESCAPE)running=false;else command(key);}
        if(e.type==SDL_MOUSEBUTTONDOWN&&e.button.button==SDL_BUTTON_LEFT){float x,y;SDL_RenderWindowToLogical(canvas.renderer,e.button.x,e.button.y,&x,&y);click(x,y);}
        if(e.type==SDL_MOUSEBUTTONUP&&e.button.button==SDL_BUTTON_LEFT)dragging=false;
        if(e.type==SDL_MOUSEMOTION&&dragging){float x,y;SDL_RenderWindowToLogical(canvas.renderer,e.motion.x,e.motion.y,&x,&y);seek(x);}
        if(e.type==SDL_MOUSEWHEEL){scroll=std::clamp(scroll-e.wheel.y*3,0,std::max(0,int(filtered.size())-12));}
        if(e.type==SDL_WINDOWEVENT&&e.window.event==SDL_WINDOWEVENT_FOCUS_LOST)dragging=false;
    }
    void button(const std::string& title,int x,int y,int w,bool enabled,bool active=false,bool danger=false){auto& c=canvas;c.rect(float(x),float(y),float(w),42,enabled?(active?SDL_Color{31,84,84,255}:danger?SDL_Color{67,43,46,255}:SDL_Color{37,53,68,255}):SDL_Color{24,34,44,255});c.rect(float(x),float(y),float(w),42,active?accent:SDL_Color{58,77,91,255},false);c.text(title,x+15,y+10,17,enabled?(danger?orange:white):muted,w-24);}
    void draw(){auto& c=canvas;SDL_SetRenderDrawColor(c.renderer,14,21,29,255);SDL_RenderClear(c.renderer);
        c.rect(0,0,1280,72,{20,30,40,255});c.line(0,71,1280,71,{48,67,79,255});c.text(u8"1031  /  怪物动作演示",24,17,26,white);c.text(u8"受击动画  ·  通用死亡效果预览",377,26,15,muted);c.rect(1157,21,91,29,{28,66,68,255});c.text("DNF 1031",1166,25,13,accent);
        c.rect(12,84,300,696,{20,30,40,255});c.rect(24,96,276,40,{13,22,31,255});c.rect(24,96,276,40,searchFocus?accent:SDL_Color{53,72,85,255},false);c.text(search.empty()&&composition.empty()?u8"搜索名称 / ID / 路径   /":search+composition+(searchFocus?"|":""),32,105,15,search.empty()?muted:white,258);
        c.rect(24,147,276,31,deathOnly?SDL_Color{29,66,67,255}:SDL_Color{32,44,56,255});c.text(deathOnly?u8"✓  只看可配置死亡预览":u8"全部怪物   ·   点击筛选死亡预览",31,152,14,deathOnly?accent:muted,262);
        for(int i=0;i<12&&scroll+i<int(filtered.size());++i){int n=filtered[scroll+i],y=190+i*43;auto&r=content.monsters()[n];bool selected=n==content.selected;if(selected){c.rect(20,float(y),286,42,{29,58,68,255});c.rect(20,float(y),3,42,accent);}c.text(r["name"],31,y+3,16,selected?white:SDL_Color{187,202,214,255},260);std::string id=r["ids"].empty()?"PATH":r["ids"][0].dump();c.text("ID "+id+"  /  "+(configured(n,"death")?u8"独立动作":sharedConfigured(n)?u8"通用死亡":u8"普通动作"),32,y+24,11,muted,260);}
        if(filtered.empty())c.text(u8"没有匹配的怪物",41,218,17,muted);
        c.text(std::to_string(filtered.size())+u8" 个结果   ·   鼠标滚轮 / ↑↓",26,724,13,muted);c.text(u8"F2 筛选    / 搜索    Esc 退出",26,752,12,muted);
        if(content.selected<0)return;auto&r=content.monsters()[content.selected];std::string id=r["ids"].empty()?u8"无列表 ID":r["ids"][0].dump();c.text(r["name"],340,89,27,white,565);c.text("ID "+id+"   /   "+r["path"].get<std::string>(),341,129,12,muted,894);
        c.rect(328,162,932,410,{18,31,41,255});c.rect(328,457,932,115,{22,37,46,255});
        for(int y=478;y<=567;y+=22)c.line(330,y,1258,y,{34,53,62,255});for(int x=360;x<1280;x+=65)c.line(794,445,x,570,{32,51,61,255});
        c.line(330,456,1258,456,{45,67,77,255});for(int y=-5;y<=5;++y){double w=std::sqrt(std::max(0.0,1-double(y*y)/36))*48;c.rect(float(794-w),float(520+y),float(w*2),1,{0,0,0,14});}
        c.rect(930,88,318,36,{31,65,71,255});c.text(deathMode==0?u8"T  死亡：自动选择":deathMode==1?u8"T  死亡：定格碎裂预览":u8"T  死亡：独立末尾动作",945,95,15,accent);
        auto* p=current();if(state=="death"&&sharedActive)sharedDraw();else if(p&&p->valid())c.plan(*p,time,facing,zoom,state=="idle");else{c.text(u8"此动作暂不可播放",658,337,24,muted);c.text(u8"请选择其他动作或切换怪物",635,378,16,muted);}
        c.rect(346,178,completed&&state=="death"?194:116,29,{17,29,37,230});c.text(completed&&state=="death"?u8"死亡动画播放完毕":label(state),356,181,16,state=="death"?orange:accent);c.text(paused?u8"已暂停":automatic?u8"自动演示中":sharedActive?u8"通用死亡预览":u8"原始 ANI 动画",1110,182,13,muted,130);
        if(info&&p){c.rect(347,227,894,211,{12,21,29,240});c.text(sharedActive?u8"通用死亡预览 / 原始石块资源":u8"当前动作来源",363,241,17,accent);c.text(sharedActive?frozenPlan.entry:p->entry,363,275,12,white,861);c.text(sharedActive?deathDetails.value("piece_image",""):p->base?p->base->path:p->error,363,300,12,muted,861);c.text(sharedActive?u8"[die effect] "+content.monsters()[content.selected]["die_effect"].dump():u8"动画轨道："+std::to_string(p->tracks.size())+u8"   附加诊断："+std::to_string(p->issues.size()),363,332,15,white);c.text(sharedActive?u8"定格 / 变白 / 弹道时间为预览参数，未完成原客户端逐帧校准。":u8"仅播放动画组合；ACT 行为与脚本未在此预览中执行。",363,367,14,muted);if(!p->error.empty())c.text(p->error,363,399,12,orange,858);}
        double progress=p&&p->valid()?std::clamp(time/p->duration,0.0,1.0):0;c.rect(360,600,868,5,{46,65,78,255});c.rect(360,600,float(868*progress),5,accent);c.rect(float(357+868*progress),595,7,15,accent);
        std::string timing="--";if(p&&p->valid()){auto frame=p->base->frameAt(int64_t(time),state=="idle");timing=(sharedActive?(time<60?u8"姿态定格":time<burst?u8"白色定格":time<burst+90?u8"碎块崩飞":completed?u8"死亡完成":u8"碎块散落"):u8"帧 "+std::to_string(frame+1)+" / "+std::to_string(p->base->frames.size()))+std::string("    ")+std::to_string(int(time))+" / "+std::to_string(int(p->duration))+" ms";}c.text(timing,349,575,12,muted);c.text(u8"拖动时间轴逐帧查看",1090,575,12,muted);
        bool alive=state!="death";button(u8"1  受击一",340,638,140,alive&&content.has("damage1"),state=="damage1");button(u8"2  受击二",492,638,140,alive&&content.has("damage2"),state=="damage2");button(u8"D  死亡",644,638,140,canDeath(),state=="death",true);button(u8"R  复活 / 重置",796,638,140,true);button(u8"A  一键完整演示",948,638,300,canDeath(),automatic);
        button(paused?u8"继续播放":u8"暂停播放",340,700,120,true,paused);std::ostringstream sp;sp<<speed;button(sp.str()+u8"×  速度",472,700,120,true);button(facing>0?u8"朝右  L":u8"朝左  L",604,700,120,true);button(u8"上一帧  ,",736,700,120,true);button(u8"下一帧  .",868,700,120,true);button(info?u8"关闭资源信息  F1":u8"资源信息  F1",1000,700,248,true,info);
        bool placeholder=content.plans.count("death")&&content.plans.at("death").error.find("transparent placeholders")!=std::string::npos;
        c.text(notice.empty()?(useShared()&&canDeath()?u8"定格变白 → 原始石块飞散；时间/弹道为预览参数。T 切换死亡模式 · F4 慢放":content.has("death")?u8"播放独立末尾动作。T 可比较定格碎裂模式 · F4 慢放 · F12 截图":placeholder?u8"独立死亡动作含透明占位图；T 可手动比较通用碎裂预览。":u8"当前死亡模式不可用，按 T 切换或选择其他怪物。 "):notice,341,756,13,notice.empty()?muted:orange,903);
    }
};

static fs::path findClient(const fs::path& root,const fs::path& requested,const Json& source) {
    const std::string expected=source["pvf_sha256"];
    if(!requested.empty()){if(sha256(requested/"Script.pvf")!=expected)throw std::runtime_error("Source version mismatch: this demo requires the bound 1031 Script.pvf");return requested;}
    for(auto&e:fs::directory_iterator(root.parent_path()))if(e.is_directory()&&fs::exists(e.path()/"Script.pvf")&&fs::exists(e.path()/"DNF.exe"))if(sha256(e.path()/"Script.pvf")==expected)return e.path();
    throw std::runtime_error("1031 resources not found. Keep monster_demo beside the 1031 client or use --client PATH.");
}
static void sendKey(Demo& demo,SDL_Scancode key){SDL_Event event{};event.type=SDL_KEYDOWN;event.key.keysym.scancode=key;SDL_PushEvent(&event);bool running=true;while(SDL_PollEvent(&event))demo.event(event,running);}
static void verify(Demo& demo,const fs::path& report) {
    demo.deathMode=2;auto& c=demo.content;Json cases=Json::array();int rendered=0;const int ids[]={61491,62638,56013,59005,5001,59001};
    for(int id:ids){int index=-1;for(int i=0;i<int(c.monsters().size());++i)for(auto&v:c.monsters()[i]["ids"])if(v==id)index=i;if(index<0)throw std::runtime_error("Verification ID missing");demo.select(index);Json states=Json::array();
        for(auto key:{"idle","damage1","damage2","death"}){
            if(!c.has(key)){if(std::string(key)!="death"||(id!=5001&&id!=59001))throw std::runtime_error("Required preview state unavailable: "+std::to_string(id)+" / "+key);continue;}
            demo.reset();if(std::string(key)!="idle")sendKey(demo,std::string(key)=="damage1"?SDL_SCANCODE_1:std::string(key)=="damage2"?SDL_SCANCODE_2:SDL_SCANCODE_D);
            if(demo.state!=key)throw std::runtime_error("SDL input did not start state");auto&p=c.plans.at(key);
            for(size_t frame=0;frame<p.base->frames.size();++frame){demo.time=boundary(*p.base,int(frame));demo.paused=true;demo.draw();SDL_RenderPresent(demo.canvas.renderer);++rendered;}
            demo.time=p.duration*.43;demo.paused=true;demo.draw();auto shot=report/(std::to_string(id)+"-"+key+".png");demo.canvas.screenshot(shot);SDL_RenderPresent(demo.canvas.renderer);
            if(std::string(key)=="death"){demo.time=0;demo.paused=false;demo.step(p.duration+1);if(demo.state!="death"||!demo.completed)throw std::runtime_error("Death lifecycle did not complete");demo.start("damage1");if(demo.state!="death")throw std::runtime_error("Dead state accepted hit");demo.reset();if(demo.state!="idle")throw std::runtime_error("Reset failed");}
            else if(std::string(key)!="idle"){demo.state=key;demo.time=0;demo.paused=false;demo.step(p.duration+1);if(demo.state!="idle")throw std::runtime_error("Damage did not return to idle");}
            states.push_back({{"state",key},{"frames",p.base->frames.size()},{"duration_ms",p.duration},{"tracks",p.tracks.size()},{"screenshot",shot.u8string()}});
        }
        // Exercise SDL's window-to-logical conversion as well as the button action.
        if(c.has("damage1")){demo.reset();SDL_Event click{};click.type=SDL_MOUSEBUTTONDOWN;click.button.button=SDL_BUTTON_LEFT;SDL_RenderLogicalToWindow(demo.canvas.renderer,380,657,&click.button.x,&click.button.y);SDL_PushEvent(&click);bool running=true;while(SDL_PollEvent(&click))demo.event(click,running);if(demo.state!="damage1")throw std::runtime_error("Mouse hit button failed");demo.frameStep(1);if(!demo.paused)throw std::runtime_error("Frame stepping failed");demo.seek(800);if(!demo.paused)throw std::runtime_error("Seek failed");}
        if(c.has("death")){demo.autoPlay();for(int n=0;n<12000&&demo.automatic;++n)demo.step(10);if(demo.state!="death"||!demo.completed)throw std::runtime_error("Auto sequence failed");}
        else {demo.reset();sendKey(demo,SDL_SCANCODE_D);if(demo.state!="idle"||demo.notice.empty())throw std::runtime_error("Missing death animation was not diagnosed");demo.autoPlay();if(demo.automatic)throw std::runtime_error("Incomplete sequence accepted");}
        cases.push_back({{"id",id},{"name",c.monsters()[index]["name"]},{"path",c.monsters()[index]["path"]},{"states",states},{"bindings",c.description()}});
    }
    if(c.plans.at("death").error.find("transparent placeholders")==std::string::npos)throw std::runtime_error("Transparent placeholder not diagnosed");
    Json sharedCases=Json::array();
    auto stagePixels=[&](){demo.draw();SDL_Rect r{410,220,750,345};Bytes bytes(size_t(r.w)*r.h*4);if(SDL_RenderReadPixels(demo.canvas.renderer,&r,SDL_PIXELFORMAT_RGBA32,bytes.data(),r.w*4))throw std::runtime_error(SDL_GetError());return bytes;};
    for(int id:{5001,1,56013,61491}){
        int index=-1;for(int i=0;i<int(c.monsters().size());++i)for(auto&v:c.monsters()[i]["ids"])if(v==id)index=i;
        demo.deathMode=1;demo.select(index);demo.start("damage1");demo.time=std::min(50.0,demo.current()->duration*.5);
        std::string poseEntry=demo.current()->entry;double poseTime=demo.time;sendKey(demo,SDL_SCANCODE_D);
        if(!demo.sharedActive||!demo.sharedPlan.valid()||demo.frozenPlan.entry!=poseEntry||demo.frozenTime!=poseTime)throw std::runtime_error("Death did not capture current hit pose");
        demo.paused=true;demo.time=80;auto white1=stagePixels();demo.canvas.screenshot(report/(std::to_string(id)+"-shared-white.png"));
        demo.time=180;auto white2=stagePixels();if(white1!=white2)throw std::runtime_error("Frozen white pose changed during hold");
        demo.time=0;auto source=stagePixels();demo.canvas.screenshot(report/(std::to_string(id)+"-shared-frozen.png"));if(source==white1)throw std::runtime_error("White silhouette not visible");
        demo.time=350;demo.draw();demo.canvas.screenshot(report/(std::to_string(id)+"-shared-burst.png"));
        demo.time=650;auto flight=stagePixels();demo.canvas.screenshot(report/(std::to_string(id)+"-shared-flight.png"));
        demo.time=1050;stagePixels();demo.time=650;if(flight!=stagePixels())throw std::runtime_error("Particle seek not deterministic");
        demo.facing=-1;auto mirror=stagePixels();demo.canvas.screenshot(report/(std::to_string(id)+"-shared-left.png"));demo.facing=1;if(flight!=stagePixels())throw std::runtime_error("Facing round trip altered particles");
        DeathProfile profile(c.monsters()[index]);if(id==61491&&profile.pieces)throw std::runtime_error("MOB omit-piece flag ignored");
        if(profile.pieces&&mirror==flight)throw std::runtime_error("Particle facing not mirrored");
        demo.time=demo.sharedPlan.duration;auto finished=stagePixels();demo.canvas.screenshot(report/(std::to_string(id)+"-shared-finished.png"));if(finished==white1)throw std::runtime_error("Body did not disappear");
        demo.time=0;demo.paused=false;demo.step(demo.sharedPlan.duration+10);if(!demo.completed||demo.state!="death")throw std::runtime_error("Shared death lifecycle failed");
        demo.start("damage1");if(demo.state!="death")throw std::runtime_error("Shared dead state accepted hit");
        sharedCases.push_back({{"id",id},{"profile",demo.deathDetails},{"frozen_pose_stable",true},{"white_changes_source",true},{"seek_deterministic",true},{"mirrored",mirror!=flight},{"completed",true}});
        demo.reset();if(!demo.fragments.empty()||demo.frozenPlan.valid())throw std::runtime_error("Reset retained frozen death state");
    }
    // Default ordinary monster route and SDL mode selector are independent of names.
    demo.deathMode=0;for(int i=0;i<int(c.monsters().size());++i)if(c.monsters()[i]["path"]=="monster/lugaru/lugaru.mob")demo.select(i);
    if(!demo.useShared()||!demo.canDeath())throw std::runtime_error("Ordinary configured death was not selected");
    sendKey(demo,SDL_SCANCODE_T);if(demo.deathMode!=1)throw std::runtime_error("Death mode key failed");
    demo.autoPlay();for(int n=0;n<1000&&demo.automatic;++n)demo.step(10);if(!demo.completed||!demo.sharedActive)throw std::runtime_error("Shared auto sequence failed");
    writeJson(report/"shared-death-verification.json",{{"ok",true},{"cases",sharedCases},{"source",c.catalog["source"]},{"scope","Resource-backed reconstruction; deterministic preview verified, not native pixel/timing parity"}});
    demo.search=u8"巨灵布鲁";demo.filter();if(demo.filtered.empty())throw std::runtime_error("Chinese search failed");demo.search="61491";demo.filter();if(demo.filtered.empty())throw std::runtime_error("ID search failed");demo.search.clear();demo.deathOnly=false;demo.filter();if(demo.filtered.size()!=2070)throw std::runtime_error("All-monster filter failed");
    writeJson(report/"verification.json",{{"ok",true},{"rendered_main_animation_frames",rendered},{"cases",cases},{"source",c.catalog["source"]},{"events",demo.events},{"unconsumed_render_nodes",demo.canvas.unsupported},{"scope","Resource/frame and reconstructed preview behavior verification; not original-client pixel parity or full combat/death controller acceptance"}});
    writeJson(report/"resource-reads.json",{{"pvf",c.pvf.reads()},{"npk",c.assets.reads()},{"archive_index_errors",c.assets.errors}});
}
static int run(const std::vector<std::string>& args) {
    fs::path root=executableRoot(),client,report=root/"reports/interactive";bool verification=false,smoke=false;double seconds=9;int id=5001;
    try {
        for(size_t i=1;i<args.size();++i){auto s=args[i];if(s=="--client"&&i+1<args.size())client=fs::u8path(args[++i]);else if(s=="--report"&&i+1<args.size())report=fs::u8path(args[++i]);else if(s=="--id"&&i+1<args.size())id=std::stoi(args[++i]);else if(s=="--verify")verification=true;else if(s=="--smoke"){smoke=true;if(i+1<args.size())seconds=std::stod(args[++i]);}else throw std::runtime_error("Unknown or incomplete argument: "+s);}
        auto data=jsonFile(root/"content/monsters.json");client=findClient(root,client,data["source"]);fs::create_directories(report);
        if(sha256(client/"DNF.exe")!=data["source"]["exe_sha256"].get<std::string>())throw std::runtime_error("1031 EXE hash mismatch");
        Content content(client,std::move(data));SDL_SetMainReady();if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER))throw std::runtime_error(SDL_GetError());
        {
            Canvas canvas(content,verification);Demo demo(content,canvas,report);int selected=-1;for(int i=0;i<int(content.monsters().size());++i)for(auto&v:content.monsters()[i]["ids"])if(v==id){if(selected>=0&&selected!=i)throw std::runtime_error("Ambiguous monster ID");selected=i;}
            if(selected<0)throw std::runtime_error("Monster ID not found");demo.select(selected);
            if(verification)verify(demo,report);
            else {bool running=true;uint64_t previous=SDL_GetPerformanceCounter();double freq=double(SDL_GetPerformanceFrequency()),wall=0;bool started=false,shot1=false,shot2=false;while(running){uint64_t now=SDL_GetPerformanceCounter();double dt=(now-previous)*1000/freq;previous=now;wall+=dt;SDL_Event event;while(SDL_PollEvent(&event))demo.event(event,running);
                    if(smoke&&!started&&wall>=200){demo.autoPlay();started=true;}
                    demo.step(std::min(dt,100.0));demo.draw();if(smoke&&!shot1&&demo.state=="damage1"){canvas.screenshot(report/"smoke-damage.png");shot1=true;}if(smoke&&!shot2&&demo.state=="death"&&demo.time>demo.current()->duration*.43){canvas.screenshot(report/"smoke-death.png");shot2=true;}
                    SDL_RenderPresent(canvas.renderer);if(smoke&&wall>=seconds*1000)running=false;if(!(SDL_GetWindowFlags(canvas.window)&SDL_WINDOW_INPUT_FOCUS))SDL_Delay(12);}
                writeJson(report/"run.json",{{"source",content.catalog["source"]},{"monster",content.monsters()[content.selected]["path"]},{"state",demo.state},{"time_ms",demo.time},{"completed",demo.completed},{"events",demo.events},{"bindings",content.description()},{"shared_death",demo.deathDetails},{"shared_active",demo.sharedActive},{"duration_ms",demo.current()?demo.current()->duration:0},{"wall_ms",wall},{"unconsumed_render_nodes",canvas.unsupported},{"smoke",smoke},{"scope","Resource-backed preview: explicit last action or frozen pose/common death; native HP/death controller not executed"}});
                writeJson(report/"resource-reads.json",{{"pvf",content.pvf.reads()},{"npk",content.assets.reads()},{"archive_index_errors",content.assets.errors}});
            }
        }
        SDL_Quit();return 0;
    }catch(const std::exception& ex){try{fs::create_directories(report);writeJson(report/"error.json",{{"error",ex.what()}});}catch(...){}if(!verification&&!smoke)MessageBoxW(nullptr,wide(ex.what()).c_str(),L"1031 monster preview",MB_ICONERROR);SDL_Quit();return 1;}
}
int WINAPI wWinMain(HINSTANCE,HINSTANCE,PWSTR,int) {int argc=0;auto argv=CommandLineToArgvW(GetCommandLineW(),&argc);std::vector<std::string> args;for(int i=0;i<argc;++i)args.push_back(utf8(argv[i]));LocalFree(argv);return run(args);}
