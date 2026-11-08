// 1031 UI laboratory. Callbacks copy bounded POD only; the worker owns all I/O.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <bcrypt.h>
#include <atomic>
#include <array>
#include <vector>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <deque>
#include <thread>
#include "json.hpp"
#include "vendor/memory_probe.hpp"
#include "vendor/bounded_queue.hpp"
#include "profile.hpp"
#include "resource_profile.hpp"
#include "watch_profile.hpp"
#include "guard_diagnostics.hpp"
#include "geometry_profile.hpp"
using Json=nlohmann::ordered_json;
namespace fs=std::filesystem;
using memory_probe::read;
using U=uint32_t;
enum Kind:U {Load=1,LoadEnd,Bind,Control,TreeEnd,Image,Clip,Lookup,Factory,Device,Present,Reset,Draw,Texture,Health,ResourceOpen,ResourceEnd,ParseOpen,ParseEnd,ArchiveIO};
struct Event{
    U kind=0,tid=0,site=0,object=0,parent=0,vtable=0,frame=0,span=0,flags=0;
    int64_t tick=0;U args[16]{};U bytes=0;unsigned char payload[4096]{};
    wchar_t path[260]{};wchar_t name[100]{};
    U callerCount=0,callers[12]{};
};
static BoundedQueue<Event,4096> queue;
static std::atomic<U> losses{0},sequence{0},nextFrame{1},nextSpan{1};
static std::atomic<int64_t> callbackTicks{0};
static std::atomic<U> detailInterval{1000};
struct CallbackTimer{LARGE_INTEGER start{};CallbackTimer(){QueryPerformanceCounter(&start);}~CallbackTimer(){DWORD saved=GetLastError();LARGE_INTEGER end;QueryPerformanceCounter(&end);callbackTicks.fetch_add(end.QuadPart-start.QuadPart,std::memory_order_relaxed);SetLastError(saved);}};
static std::atomic<bool> running{false},ready{false};
static std::atomic<LONG> once{0};
static int64_t frequency=0;
static HMODULE selfModule=nullptr;
static bool fixture=false;
static constexpr U ObserverRevision=6;
static std::atomic<bool> geometryReady{false};
static fs::path folder;
static U base=0,imageSize=0;
static std::array<memory_probe::Installed,32> hooks;
static std::vector<memory_probe::Installed*> installed;
static std::array<memory_probe::Installed,8> resourceHooks;
static std::vector<memory_probe::Installed*> resourceInstalled;
static U now(){return GetTickCount();}
static U word(U at){U v=0;read(&v,(void*)at,4);return v;}
static Event event(U kind,U site=0){Event e;e.kind=kind;e.site=site;e.tid=GetCurrentThreadId();LARGE_INTEGER t;QueryPerformanceCounter(&t);e.tick=t.QuadPart;return e;}
static void emit(const Event&e){if(queue.push(e)!=decltype(queue)::Ok)++losses;}
static void text(wchar_t*out,unsigned count,U at){
    if(!at)return;unsigned i=0;
    while(i+1<count){U pointer=at+i*2;unsigned n=std::min(64u,std::min(count-1-i,(4096u-(pointer&4095u))/2));
        if(!n||!read(out+i,(void*)pointer,n*2)){out[i]=0;return;}
        for(unsigned j=0;j<n;++j)if(!out[i+j])return;i+=n;}
    out[count-1]=0;
}
static void stringObject(wchar_t*out,unsigned count,U at){
    // MSVC UTF16 string including iterator proxy: data+4, size+14, cap+18.
    U length=word(at+0x14),cap=word(at+0x18);
    if(length>=count||length>cap||cap>0x100000)return;
    U data=cap<8?at+4:word(at+4);
    if(length&&read(out,(void*)data,length*2))out[length]=0;
}
struct Local{
    U loads=0,loadEsp[16]{},loadReturn[16]{},loadSpan[16]{};wchar_t paths[16][260]{};
    U depth=0,objects[64]{},drawEsp[64]{},frame=0,lost=0;bool capture=false;
    U lastCapture=0,burstUntil=0,lastState=0,frameEvents=0;bool detailed=false;
};
static thread_local Local local;
static void copyPath(Event&e){if(local.loads){e.span=local.loadSpan[local.loads-1];memcpy(e.path,local.paths[local.loads-1],sizeof(e.path));}}
static bool loaderOnStack(U ebp){
    if(!local.loads)return false;U n=local.loads-1,target=local.loadEsp[n]-4;
    for(unsigned i=0;i<64;++i){
        if(ebp==target)return word(target+4)==local.loadReturn[n];
        U next=word(ebp);if(next<=ebp||next-ebp>0x100000)break;ebp=next;
    }
    return false;
}
static bool imageResource(Event&e,U object){
    U pack=word(object+0x64),frame=word(object+0x68),packVt=word(pack);
    if(!pack||(!fixture&&packVt!=base+0x145a380))return false;
    U begin=word(pack+0x58),end=word(pack+0x5c);
    if(end<begin||frame>65535||frame>=(end-begin)/16||word(begin+frame*16)!=object)return false;
    stringObject(e.path,260,pack+0x30);e.args[12]=frame;e.args[13]=pack;e.args[14]=word(object+0x5c);return e.path[0]!=0;
}
#include "resource_callbacks.hpp"
static void maybeDevice();
static void __stdcall callback(memory_probe::Installed*h,const memory_probe::Registers*r){
    DWORD saved=GetLastError();
    CallbackTimer timer;
    if(!running){SetLastError(saved);return;}
    U id=h->spec.id,esp=r->saved_esp+4;
    if(id>=21&&id<=28){resourceCallback(id,r,esp);}
    else if(id==1){
        while(local.loads&&esp>=local.loadEsp[local.loads-1]){--local.loads;++losses;}
        Event e=event(Load,id);e.object=r->ecx;e.parent=word(esp);read(e.args,(void*)(esp+4),12);e.args[3]=word(r->ecx+0x18);e.args[4]=word(r->ecx+0x24);text(e.path,260,e.args[0]);e.span=nextSpan++;
        // Only .ui resources; never inspect general input or edit-box strings.
        if(local.loads<16){U n=local.loads++;local.loadEsp[n]=esp;local.loadReturn[n]=word(esp);local.loadSpan[n]=e.span;memcpy(local.paths[n],e.path,sizeof(e.path));}
        emit(e);
    }else if(id==2||id==3){
        Event e=event(LoadEnd,id);e.args[0]=id==2?(r->eax&255):0;e.object=r->edi;copyPath(e);emit(e);
        if(local.loads&&local.loadEsp[local.loads-1]==r->ebp+4)--local.loads;
        else {local.loads=0;++losses;}
    }else if(id==4){
        Event e=event(Bind,id);e.object=r->edi;e.vtable=word(e.object);e.args[0]=word(r->ebp-0x1d0);
        stringObject(e.name,100,r->ebp-0xb0);if(loaderOnStack(r->ebp))copyPath(e);emit(e);
        local.burstUntil=now()+3000;
    }else if(id==5){
        if(local.depth&&esp>=local.drawEsp[0]){local.depth=0;local.capture=false;++losses;}
        if(!local.depth){
            U t=now();bool state=U(t-local.lastState)>=200;
            U interval=detailInterval.load();
            if(interval==1000&&int32_t(local.burstUntil-t)>0)interval=200;
            local.detailed=U(t-local.lastCapture)>=interval;
            local.capture=state;
            if(local.capture){if(local.detailed)local.lastCapture=t;local.frame=nextFrame++;local.lost=losses.load();local.frameEvents=0;}
            if(state){local.lastState=t;maybeDevice();}
        }
        if(local.depth<64){
            if(local.capture){
                Event e=event(Control,id);e.object=r->ecx;e.vtable=word(e.object);e.frame=local.frame;
                e.parent=local.depth?local.objects[local.depth-1]:0;
                unsigned char raw[0x70]{};
                if(read(raw,(void*)e.object,sizeof(raw))){memcpy(e.args,raw+0xc,4);memcpy(e.args+1,raw+0x14,8);memcpy(e.args+3,raw+0x38,8);e.flags=1;}
                if(!local.depth)e.flags|=0x100;
                ++local.frameEvents;emit(e);
            }
            local.objects[local.depth]=r->ecx;local.drawEsp[local.depth]=esp;
        }else ++losses;
        ++local.depth;
    }else if(id==6){
        if(local.depth)--local.depth;else ++losses;
        if(!local.depth&&local.capture){Event e=event(TreeEnd,id);e.frame=local.frame;e.args[0]=local.lost;e.args[1]=losses.load();e.args[2]=local.frameEvents;e.flags=local.detailed?1:0;emit(e);local.capture=false;}
    }else if((id==7||id==8||id==9)&&local.capture&&local.detailed&&local.depth){
        Event e=event(id==9?Clip:Image,id);e.frame=local.frame;e.parent=local.depth<=64?local.objects[local.depth-1]:0;
        read(e.args,(void*)(esp+4),(id==7?3:id==8?9:4)*4);
        e.callerCount=1;e.callers[0]=word(esp);e.args[15]=r->ecx;
        if(read(e.payload,(void*)r->ecx,0x30)){e.bytes=0x30;e.flags|=2;}
        if(geometryReady)e.flags|=4;
        if(id!=9){e.object=e.args[2];e.vtable=word(e.object);e.flags|=imageResource(e,e.object)?1u:0u;e.args[11]=word(e.object+8);
            if(e.bytes&&read(e.payload+0x30,(void*)(e.object+0x1c),8))e.bytes=0x38;
        }else {e.object=r->ecx;e.vtable=word(e.object);}
        ++local.frameEvents;emit(e);
    }else if(id==10&&loaderOnStack(r->ebp)){
        Event e=event(Lookup,id);e.object=r->ecx;e.args[0]=word(esp+4);stringObject(e.path,260,r->ecx+0x30);e.span=local.loadSpan[local.loads-1];emit(e);
    }else if(id==11&&loaderOnStack(r->ebp)){Event e=event(Factory,id);copyPath(e);text(e.name,100,word(esp+4));emit(e);}
    SetLastError(saved);
}
static std::vector<uint8_t> hex(const char*s){std::vector<uint8_t> v;for(;s[0]&&s[1];s+=2){char b[3]={s[0],s[1],0};v.push_back(uint8_t(strtoul(b,nullptr,16)));}return v;}
static std::string utf8(const wchar_t*s){int n=WideCharToMultiByte(CP_UTF8,0,s,-1,nullptr,0,nullptr,nullptr);if(n<=1)return {};std::string v(n,0);WideCharToMultiByte(CP_UTF8,0,s,-1,&v[0],n,nullptr,nullptr);v.pop_back();return v;}
static std::string hashFile(const fs::path&p){
    BCRYPT_ALG_HANDLE alg=nullptr;BCRYPT_HASH_HANDLE hash=nullptr;DWORD n=0,length=0;
    if(BCryptOpenAlgorithmProvider(&alg,BCRYPT_SHA256_ALGORITHM,nullptr,0))return {};
    BCryptGetProperty(alg,BCRYPT_OBJECT_LENGTH,(PUCHAR)&length,4,&n,0);std::vector<unsigned char> object(length);unsigned char result[32]{};
    bool ok=BCryptCreateHash(alg,&hash,object.data(),length,nullptr,0,0)==0;
    std::ifstream f(p,std::ios::binary);char buf[65536];if(!f)ok=false;
    while(ok&&f){f.read(buf,sizeof(buf));if(f.gcount())ok=BCryptHashData(hash,(PUCHAR)buf,ULONG(f.gcount()),0)==0;}
    if(ok)ok=BCryptFinishHash(hash,result,32,0)==0;
    if(hash)BCryptDestroyHash(hash);BCryptCloseAlgorithmProvider(alg,0);
    const char*digits="0123456789abcdef";std::string out;if(ok)for(auto b:result){out+=digits[b>>4];out+=digits[b&15];}return out;
}
static const char* names[]={"unknown","load","load_end","bind","control","tree_end","image","clip_raw","lookup","factory","device","present","reset","draw","texture","health","resource_open","resource_end","parse_open","parse_end","archive_io"};
static Json jsonEvent(const Event&e){
    Json j={{"event",names[e.kind]},{"qpc",e.tick},{"tid",e.tid},{"site",e.site},{"object",e.object},{"parent",e.parent},{"vtable",e.vtable},{"frame",e.frame},{"span",e.span},{"flags",e.flags},{"args",e.args}};
    if(e.path[0])j["path"]=utf8(e.path);if(e.name[0])j["name"]=utf8(e.name);
    if(e.kind>=ResourceOpen&&e.kind<=ParseEnd&&e.path[0]){auto path=utf8(e.path);auto slash=path.find_last_of("/\\"),dot=path.find_last_of('.');std::string ext=dot!=std::string::npos&&(slash==std::string::npos||dot>slash)?path.substr(dot):u8"<无后缀>";
        for(auto&c:ext)if(c>='A'&&c<='Z')c+=32;
        for(auto&w:WatchTypes)if(ext==w.extension){j["pvf_extension_candidate"]={{"extension",ext},{"purpose",w.purpose},{"gap",w.gap}};break;}}
    if(e.callerCount){j["callers"]=Json::array();j["caller_rvas"]=Json::array();for(U i=0;i<e.callerCount;++i){j["callers"].push_back(e.callers[i]);j["caller_rvas"].push_back(e.callers[i]>=base&&e.callers[i]-base<imageSize?Json(e.callers[i]-base):Json(nullptr));}}
    if(e.bytes){const char*digits="0123456789abcdef";std::string s;for(U i=0;i<e.bytes;++i){s+=digits[e.payload[i]>>4];s+=digits[e.payload[i]&15];}j["payload_hex"]=s;}
    if((e.kind==Image||e.kind==Clip)&&e.bytes>=0x30){
        uint16_t rectangle[4];memcpy(rectangle,e.payload+0x28,8);U contextVtable=0;memcpy(&contextVtable,e.payload,4);
        j["draw_state"]={{"context",e.args[15]},{"context_vtable",contextVtable},{"rectangle_words",rectangle},{"capture_phase",e.kind==Clip?"before member write":"image request"},{"image_vtable",e.kind==Image?Json(e.vtable):Json(nullptr)},{"image_type",e.args[11]},{"consumer_verified",bool(e.flags&4)}};
        if(e.kind==Clip){uint16_t result[4];for(unsigned index=0;index<4;++index)result[index]=int32_t(e.args[index])>0?uint16_t(e.args[index]):0;j["draw_state"]["written_rectangle_words"]=result;}
        if(e.bytes==0x38){uint16_t dimensions[2];int16_t crop[2];memcpy(dimensions,e.payload+0x30,4);memcpy(crop,e.payload+0x34,4);j["draw_state"]["image_dimensions"]=dimensions;j["draw_state"]["image_crop"]=crop;}
    }
    return j;
}
// Graphics fallback is deliberately independent of semantic UI hooks.
#include "graphics.hpp"
#include "archive_io.hpp"
static Json current=Json::object();
static void writeAtomic(const fs::path&p,const Json&j){auto t=p;t+=L".new";{std::ofstream f(t,std::ios::binary);f<<j.dump();}MoveFileExW(t.c_str(),p.c_str(),MOVEFILE_REPLACE_EXISTING);}
#include "resource_journal.hpp"
static Json checkGeometry(){
    Json diagnostics=Json::array();bool matched=true;
    for(auto&window:GeometryWindows){std::vector<unsigned char> bytes(window.size);bool readable=read(bytes.data(),(void*)(base+window.va-0x400000),window.size);unsigned char result[32]{};
        bool hashed=false;
        if(readable){BCRYPT_ALG_HANDLE algorithm=nullptr;
            if(BCryptOpenAlgorithmProvider(&algorithm,BCRYPT_SHA256_ALGORITHM,nullptr,0)==0){hashed=BCryptHash(algorithm,nullptr,0,bytes.data(),ULONG(bytes.size()),result,32)==0;BCryptCloseAlgorithmProvider(algorithm,0);}}
        std::string actual=hashed?ui_guard::hexBytes(result,32):"";bool valid=actual==window.sha256;matched=matched&&valid;
        diagnostics.push_back({{"va",window.va},{"size",window.size},{"expected_sha256",window.sha256},{"actual_sha256",actual},{"matched",valid}});
    }
    bool table=word(base+0x185c76c+0xac-0x400000)==base+0x11db510-0x400000&&word(base+0x185c76c+0xb4-0x400000)==base+0x11db180-0x400000;
    bool constants=word(base+0x1562250-0x400000)==0x7e967699&&word(base+0x15661b0-0x400000)==0&&word(base+0x15661b4-0x400000)==0x4f800000&&word(base+0x5b9080-0x400000)==0xc308418b;
    geometryReady=matched&&table&&constants;return {{"ready",geometryReady.load()},{"windows",diagnostics},{"image_vtable_matched",table},{"constants_matched",constants}};
}
static DWORD WINAPI worker(void*){
    wchar_t exe[MAX_PATH]{};GetModuleFileNameW(nullptr,exe,MAX_PATH);base=U(GetModuleHandleW(nullptr));
    imageSize=word(base+word(base+0x3c)+0x50);
    wchar_t test[4]{};fixture=GetEnvironmentVariableW(L"UI1031_FIXTURE",test,4)>0;
    fs::path client=fs::path(exe).parent_path();
    LARGE_INTEGER fq;QueryPerformanceFrequency(&fq);frequency=fq.QuadPart;
    SYSTEMTIME st;GetSystemTime(&st);wchar_t session[100];swprintf_s(session,L"%04u%02u%02uT%02u%02u%02u-%lu",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,GetCurrentProcessId());
    folder=client/L"trace-ui-lab-1031"/session;fs::create_directories(folder);
    {std::ofstream f(client/L"trace-ui-lab-1031/latest-session.txt",std::ios::binary);f<<folder.u8string();}
    std::ofstream log(folder/L"events.jsonl",std::ios::binary);
    ResourceJournal resourceLog(folder);uint64_t resourceDiskOmitted=0;
    ResourceJournal lifecycleLog(folder,4ull*1024*1024,4,"ui-lifecycle");uint64_t lifecycleDiskOmitted=0;
    uint64_t loggedBytes=0,diskOmitted=0;const uint64_t maxLog=256ull*1024*1024;
    auto record=[&](const Json&j,bool lifecycle=true){auto data=j.dump();if(loggedBytes+data.size()+1<=maxLog&&log){log<<data<<'\n';if(log)loggedBytes+=data.size()+1;else ++diskOmitted;}else ++diskOmitted;
        if(lifecycle&&!lifecycleLog.append(data))++lifecycleDiskOmitted;};
    auto identity=hashFile(exe);
    wchar_t dllPath[MAX_PATH]{};GetModuleFileNameW(selfModule,dllPath,MAX_PATH);
    record({{"event","attach"},{"version",1},{"observer_revision",ObserverRevision},{"qpc",event(Health).tick},{"pid",GetCurrentProcessId()},{"exe",fs::path(exe).u8string()},{"exe_sha256",identity},{"dll_sha256",hashFile(dllPath)},{"module_base",base},{"fixture",fixture},{"qpc_frequency",frequency},{"session",utf8(session)}});log.flush();
    if(!fixture&&identity!="246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264"){
        record({{"event","rejected"},{"reason","1031 fingerprint mismatch"}});return 0;
    }
    running=true;bool codeReady=fixture,semanticRejected=false;U attempts=0;
    bool resourcesReady=fixture,resourcesRejected=false;U resourceAttempts=0;Json resourceDiagnostics=Json::array();std::string resourceGuardSignature;
    Json archiveSlots=fixture?Json::array():archive_io::install();
    record({{"event","archive_slots"},{"slots",archiveSlots}});
    std::vector<std::vector<uint8_t>> expectedGuards;for(auto&s:Sites)expectedGuards.push_back(hex(s.guard));
    Json guardDiagnostics={{"status",fixture?"fixture":"waiting"},{"sites",Json::array()}};
    Json selfReadback=Json::array();std::string guardSignature,semanticFailure;
    Json geometryDiagnostics=fixture?Json({{"ready",true},{"fixture",true}}):checkGeometry();if(fixture)geometryReady=true;
    observeForeground();
    bool reloadProfile=false;U lastReadback=0;
    HANDLE pipe=INVALID_HANDLE_VALUE;bool connected=false;
    std::wstring pipeName=L"\\\\.\\pipe\\dnf-ui-1031-"+std::to_wstring(GetCurrentProcessId());
    pipe=CreateNamedPipeW(pipeName.c_str(),PIPE_ACCESS_DUPLEX,PIPE_TYPE_MESSAGE|PIPE_READMODE_MESSAGE|PIPE_NOWAIT|PIPE_REJECT_REMOTE_CLIENTS,1,1024*1024,256,0,nullptr);
    U lastStatus=0,lastDevice=0,lastBudget=now(),lastArchive=now();double callbackShare=0;
    std::unordered_map<U,Json> bindings;std::unordered_map<U,bool> firstSeen;
    std::array<uint64_t,21> counts{};Json lastDraw=nullptr;std::deque<Json> resourceRecent;
    std::unordered_map<U,std::vector<Json>> pending;std::vector<Json> detailFrame,stateFrame;
    std::unordered_map<U,U> generations;
    while(running){
        MSG message;for(unsigned index=0;index<64&&PeekMessageW(&message,nullptr,0,0,PM_REMOVE);++index){TranslateMessage(&message);DispatchMessageW(&message);}
        if(!fixture&&U(now()-lastArchive)>=1000){lastArchive=now();auto slots=archive_io::install();if(slots!=archiveSlots){archiveSlots=slots;record({{"event","archive_slots"},{"slots",slots}});}}
        if(!resourcesReady&&!resourcesRejected&&resourceAttempts++%100==0){
            bool guards=true;resourceDiagnostics=Json::array();
            for(auto&s:ResourceSites){auto check=ui_guard::inspect((void*)(base+s.va-0x400000),hex(s.guard));check["name"]=s.name;
                if(!check["matched"].get<bool>())guards=false;resourceDiagnostics.push_back(check);}
            auto signature=resourceDiagnostics.dump();if(signature!=resourceGuardSignature){resourceGuardSignature=signature;
                record({{"event","resource_guard_check"},{"qpc",event(Health).tick},{"sites",resourceDiagnostics}});
                fs::create_directories(folder/L"resource-guard-windows");Json windows=Json::array();
                for(auto&s:ResourceSites){U address=base+s.va-0x400000-128;unsigned char bytes[640]{};bool ok=read(bytes,(void*)address,sizeof(bytes));std::string name=std::string(s.name)+".bin";
                    if(ok){std::ofstream f(folder/L"resource-guard-windows"/name,std::ios::binary);f.write((char*)bytes,sizeof(bytes));}
                    windows.push_back({{"name",s.name},{"address",address},{"size",sizeof(bytes)},{"readable",ok},{"file",name}});}
                writeAtomic(folder/L"resource-guard-windows/index.json",windows);
            }
            if(guards){
                for(auto&s:ResourceSites){auto&h=resourceHooks[resourceInstalled.size()];h.spec.id=s.id;h.spec.name=s.name;h.spec.rva=s.va-0x400000;h.spec.overwritten=s.size;h.spec.guard=hex(s.guard);h.spec.expected=hex(s.bytes);h.target=(uint8_t*)(base+h.spec.rva);
                    if(!memory_probe::prepare(h,callback))break;resourceInstalled.push_back(&h);}
                std::string reason;resourcesReady=resourceInstalled.size()==std::size(ResourceSites)&&memory_probe::transaction(resourceInstalled,false,reason);
                resourcesRejected=!resourcesReady;record({{"event","resource_hooks"},{"ready",resourcesReady},{"reason",reason}});
            }
        }
        if(reloadProfile&&!codeReady){
            reloadProfile=false;
            // Reload is deliberately an explicit command; never auto-trust observed bytes.
            try{
                for(auto h:installed)if(h->patched)throw std::runtime_error("review_reload_refused_active_patches");
                auto p=folder/L"reviewed-profile.json";
                if(fs::file_size(p)>65536)throw std::runtime_error("review_file_too_large");
                std::ifstream file(p);Json profile;file>>profile;std::string reason;
                if(ui_guard::reviewed(profile,Sites,utf8(session),identity,expectedGuards,reason)){
                    installed.clear();semanticRejected=false;semanticFailure.clear();attempts=0;
                    record({{"event","reviewed_profile_loaded"},{"review_note",profile["review_note"]}});
                }else throw std::runtime_error(reason);
            }catch(const std::exception&ex){record({{"event","reviewed_profile_rejected"},{"reason",ex.what()}});semanticFailure=ex.what();}
        }
        if(!codeReady&&!semanticRejected&&U(attempts++%10)==0){
            bool guards=true;Json checks=Json::array();unsigned index=0;
            for(auto&s:Sites){auto check=ui_guard::inspect((void*)(base+s.va-0x400000),expectedGuards[index++]);check["id"]=s.id;check["name"]=s.name;if(!check["matched"].get<bool>())guards=false;checks.push_back(check);}
            auto signature=checks.dump();
            guardDiagnostics={{"status",guards?"matched":"guard_mismatch"},{"sites",checks}};
            if(signature!=guardSignature){
                guardSignature=signature;record({{"event","guard_check"},{"qpc",event(Health).tick},{"diagnostics",guardDiagnostics}});
                // Fixed bounded code windows allow offline disassembly without remote reads.
                fs::create_directories(folder/L"guard-windows");
                Json windows=Json::array();
                for(auto&s:Sites){U address=base+s.va-0x400000-128;unsigned char bytes[640]{};bool ok=read(bytes,(void*)address,sizeof(bytes));
                    std::string name=std::string(s.name)+".bin";if(ok){std::ofstream f(folder/L"guard-windows"/name,std::ios::binary);f.write((char*)bytes,sizeof(bytes));}
                    windows.push_back({{"name",s.name},{"address",address},{"size",sizeof(bytes)},{"readable",ok},{"file",name}});
                }
                writeAtomic(folder/L"guard-windows/index.json",windows);
            }
            if(guards){
                index=0;
                for(auto&s:Sites){auto&h=hooks[installed.size()];h.spec.id=s.id;h.spec.name=s.name;h.spec.rva=s.va-0x400000;h.spec.overwritten=s.size;h.spec.guard=expectedGuards[index++];h.spec.expected.assign(h.spec.guard.begin(),h.spec.guard.begin()+s.size);h.target=(uint8_t*)(base+h.spec.rva);
                    if(!memory_probe::prepare(h,callback)){record({{"event","hook_rejected"},{"site",s.name}});break;}installed.push_back(&h);}
                std::string reason;
                if(installed.size()==std::size(Sites)&&memory_probe::transaction(installed,false,reason)){codeReady=true;record({{"event","code_ready"},{"qpc",event(Health).tick},{"sites",installed.size()}});}
                else {if(reason.empty())reason="site_prepare_failed";record({{"event","hooks_unavailable"},{"reason",reason}});semanticFailure=reason;semanticRejected=true;}
            }
        }
        Event e;for(unsigned i=0;i<512&&queue.pop(e);++i){auto j=jsonEvent(e);
            if(e.kind==Control){auto b=bindings.find(e.object);if(b!=bindings.end())j["binding"]={{"revision",b->second["binding_revision"]},{"generation",b->second["observation_generation"]},{"span",b->second["span"]},{"path",b->second.value("path",std::string())},{"name",b->second.value("name",std::string())}};}
            if(e.kind==Bind){j["binding_revision"]=++sequence;j["observation_generation"]=++generations[e.object];bindings[e.object]=j;
                if(bindings.size()>8192){bindings.erase(bindings.begin());++losses;}
            }
            // Resource events have their own journal; keep them out of the UI/GPU log.
            if(e.kind<ResourceOpen)record(j,e.kind<=Bind||e.kind==Lookup||e.kind==Factory||(e.kind==Device&&e.flags!=2)||e.kind==Reset);
            if(e.kind>=ResourceOpen){resourceRecent.push_back(j);if(resourceRecent.size()>128)resourceRecent.pop_front();
                if(!resourceLog.append(j.dump()))++resourceDiskOmitted;}
            if(e.kind<std::size(counts))++counts[e.kind];if(e.kind==Draw)lastDraw=j;
            if(!firstSeen[e.kind]){firstSeen[e.kind]=true;record({{"event","first_observation"},{"kind",names[e.kind]},{"qpc",e.tick}});}
            if(e.kind==Control||e.kind==Image||e.kind==Clip||e.kind==TreeEnd){
                if(e.kind==Control&&(e.flags&0x100))pending[e.frame].clear();
                auto at=pending.find(e.frame);
                if(at!=pending.end()){
                    if(e.kind==TreeEnd){
                        if(e.args[0]==e.args[1]&&at->second.size()==e.args[2]){
                            at->second.push_back(j);stateFrame=at->second;if(e.flags&1)detailFrame=at->second;
                        }
                        pending.erase(at);
                    }else if(at->second.size()<8192)at->second.push_back(j);
                    else {pending.erase(at);++losses;}
                }
                if(pending.size()>32){pending.clear();++losses;}
            }
        }
        if(!fixture&&U(now()-lastDevice)>=200){lastDevice=now();maybeDevice();}
        if(pipe!=INVALID_HANDLE_VALUE){
            if(!connected){BOOL ok=ConnectNamedPipe(pipe,nullptr);DWORD error=GetLastError();connected=ok||error==ERROR_PIPE_CONNECTED;}
            if(connected){
                char request[256]{};DWORD got=0;
                if(ReadFile(pipe,request,255,&got,nullptr)&&got){
                    std::string command(request,got);
                    if(command=="stop"){record({{"event","stop_requested"}});running=false;}
                    if(command=="reload_profile")reloadProfile=true;
                    std::string data=current.dump();
                    if(data.size()>900000)data=Json({{"snapshot_file",(folder/L"state.json").u8string()}}).dump();
                    data+='\n';DWORD sent=0;
                    if(!WriteFile(pipe,data.data(),DWORD(data.size()),&sent,nullptr)||sent!=data.size()){DisconnectNamedPipe(pipe);connected=false;}
                }else {DWORD error=GetLastError();if(error==ERROR_BROKEN_PIPE||error==ERROR_NO_DATA){DisconnectNamedPipe(pipe);connected=false;}}
            }
        }
        if(U(now()-lastStatus)>=200){
            std::error_code stopError;
            if(fs::exists(folder/L"stop.request",stopError)){fs::remove(folder/L"stop.request",stopError);record({{"event","stop_requested"},{"source","local session file"}});running=false;}
            if((codeReady||resourcesReady)&&!fixture&&U(now()-lastReadback)>=1000){
                lastReadback=now();selfReadback=Json::array();
                auto geometry=checkGeometry();if(geometry!=geometryDiagnostics){geometryDiagnostics=geometry;record({{"event","geometry_guard_check"},{"diagnostics",geometryDiagnostics}});}
                auto all=installed;all.insert(all.end(),resourceInstalled.begin(),resourceInstalled.end());
                for(auto h:all){unsigned char actual[32]{};bool readable=read(actual,h->target,h->spec.overwritten);
                    selfReadback.push_back({{"id",h->spec.id},{"name",h->spec.name},{"address",U(h->target)},
                        {"bytes",readable?ui_guard::hexBytes(actual,h->spec.overwritten):""},{"owned",readable&&h->patched&&!memcmp(actual,h->after.data(),h->spec.overwritten)}});
                }
            }
            lastStatus=now();Json rows=Json::array();for(auto&b:bindings)rows.push_back(b.second);
            auto recent=detailFrame;
            if(!stateFrame.empty()&&(detailFrame.empty()||stateFrame.back()["frame"]!=detailFrame.back()["frame"]))recent.insert(recent.end(),stateFrame.begin(),stateFrame.end());
            if(U(now()-lastBudget)>=1000){U elapsed=now()-lastBudget;lastBudget=now();callbackShare=double(callbackTicks.exchange(0))/double(frequency)/(elapsed/1000.0);
                current["present_statistics"]=collectPresentStatistics();current["present_statistics"]["aggregation_period_ms"]=elapsed;record({{"event","present_statistics"},{"qpc",event(Health).tick},{"statistics",current["present_statistics"]}},false);
                if(callbackShare>0.05&&detailInterval<8000){detailInterval=std::min(8000u,detailInterval.load()*2);record({{"event","auto_throttle"},{"callback_wall_share",callbackShare},{"detail_interval_ms",detailInterval.load()}});}
            }
            Json presentation=current.value("present_statistics",Json::object());
            current={{"version",1},{"observer_revision",ObserverRevision},{"pid",GetCurrentProcessId()},{"session",utf8(session)},{"code_ready",codeReady},{"running",bool(running)},{"losses",losses.load()},{"bindings",rows},{"recent",recent},{"pipe",utf8(pipeName.c_str())},{"frame_kind","UI traversal, not full GPU frame"},
                {"present_statistics",presentation},
                {"geometry_diagnostics",geometryDiagnostics},
                {"guard_diagnostics",guardDiagnostics},{"semantic_failure",semanticFailure},{"self_readback",selfReadback},
                {"callback_wall_share",callbackShare},{"detail_interval_ms",detailInterval.load()},{"event_log_bytes",loggedBytes},{"disk_omitted",diskOmitted},{"performance_validation","Present median/p95 available per device/epoch; callback wall share excludes worker/listener/Present telemetry overhead. Live overhead baseline pending."}};
            Json counters=Json::object();for(unsigned i=1;i<std::size(counts);++i)counters[names[i]]=counts[i];current["counts"]=counters;current["last_gpu_draw"]=lastDraw;
            current["resource_ready"]=resourcesReady;current["resource_diagnostics"]=resourceDiagnostics;
            current["resource_recent"]=resourceRecent;current["resource_unmatched"]=resourceUnmatched.load();current["archive_slots"]=archiveSlots;current["archive_omitted"]=archive_io::omitted.load();
            resourceLog.flush();current["resource_log_bytes"]=resourceLog.written();current["resource_disk_omitted"]=resourceDiskOmitted;current["resource_journal"]=resourceLog.status();
            current["archive_throttled"]=archive_io::throttled.load();current["archive_handle_overflow"]=archive_io::handleOverflow.load();
            current["embedded_pvf_watch_groups"]=std::size(WatchTypes);
            lifecycleLog.flush();current["ui_lifecycle_journal"]=lifecycleLog.status();current["ui_lifecycle_disk_omitted"]=lifecycleDiskOmitted;
            current["event_log_scope"]="UI/GPU detail; resource events in resource_journal; lifecycle continues in ui_lifecycle_journal";
            writeAtomic(folder/L"state.json",current);log.flush();resourceLog.flush();
        }
        ready=codeReady;Sleep(10);
    }
    ready=false;std::string reason;std::vector<memory_probe::Installed*> owned;
    for(auto h:installed)if(h->patched)owned.push_back(h);
    for(auto h:resourceInstalled)if(h->patched)owned.push_back(h);
    bool restored=owned.empty()||memory_probe::transaction(owned,true,reason);
    bool graphicsRestored=restoreGraphics();
    current["final_present_statistics"]=collectPresentStatistics();
    if(foregroundHook){UnhookWinEvent(foregroundHook);foregroundHook=nullptr;}
    bool archiveRestored=archive_io::restore();record({{"event","archive_restored"},{"restored",archiveRestored}});
    record({{"event","stopped"},{"code_restored",restored},{"graphics_restored",graphicsRestored},{"reason",reason},{"losses",losses.load()}});log.flush();
    resourceLog.flush();lifecycleLog.flush();current["resource_journal"]=resourceLog.status();current["ui_lifecycle_journal"]=lifecycleLog.status();current["ui_lifecycle_disk_omitted"]=lifecycleDiskOmitted;
    current["event_log_bytes"]=loggedBytes;current["disk_omitted"]=diskOmitted;current["running"]=false;current["code_restored"]=restored;current["archive_restored"]=archiveRestored;current["graphics_restored"]=graphicsRestored;writeAtomic(folder/L"state.json",current);
    if(pipe!=INVALID_HANDLE_VALUE)CloseHandle(pipe);return 0;
}
static void start(){if(once.exchange(1)==0){HANDLE t=CreateThread(nullptr,0,worker,nullptr,0,nullptr);if(t)CloseHandle(t);}}
extern "C" __declspec(dllexport) BOOL WINAPI ClientPatchPluginInit(){start();return TRUE;}
extern "C" __declspec(dllexport) BOOL WINAPI UiLabReady(){return ready;}
extern "C" __declspec(dllexport) void WINAPI UiLabStop(){running=false;}
extern "C" __declspec(dllexport) BOOL WINAPI UiLabFixtureDevice(void*object){if(!fixture||!ready)return FALSE;fixtureDevice=U(object);maybeDevice();return graphicsFor(object)!=nullptr;}
extern "C" __declspec(dllexport) BOOL WINAPI UiLabFixtureCall(U id,const memory_probe::Registers*r){if(!fixture||!ready)return FALSE;memory_probe::Installed h;h.spec.id=id;callback(&h,r);return TRUE;}
extern "C" __declspec(dllexport) BOOL WINAPI UiLabFixtureIO(){
    if(!fixture||!ready)return FALSE;
    auto path=folder/L"fixture-resource.pvf";HANDLE file=archive_io::openW(path.c_str(),GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,nullptr,CREATE_ALWAYS,0,nullptr);
    if(file==INVALID_HANDLE_VALUE)return FALSE;const char data[]="1031-resource-fixture";DWORD written;WriteFile(file,data,sizeof(data),&written,nullptr);
    archive_io::seek(file,0,nullptr,FILE_BEGIN);char raw[64]{};DWORD got=0;SetLastError(0x7192);
    if(!archive_io::readFile(file,raw,sizeof(data),&got,nullptr)||got!=sizeof(data)||memcmp(data,raw,got)||GetLastError()!=0x7192)return FALSE;
    HANDLE mapping=archive_io::mappingW(file,nullptr,PAGE_READONLY,0,0,nullptr);if(!mapping)return FALSE;
    void*view=archive_io::view(mapping,FILE_MAP_READ,0,0,0);if(!view||memcmp(view,data,sizeof(data)))return FALSE;
    UnmapViewOfFile(view);archive_io::close(mapping);archive_io::close(file);
    file=archive_io::openW(path.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,nullptr);
    if(file==INVALID_HANDLE_VALUE)return FALSE;OVERLAPPED ov{};ov.hEvent=CreateEventW(nullptr,TRUE,FALSE,nullptr);
    BOOL async=archive_io::readFile(file,raw,sizeof(data),&got,&ov);DWORD asyncError=GetLastError();
    if(!async&&asyncError!=ERROR_IO_PENDING)return FALSE;
    if(!GetOverlappedResult(file,&ov,&got,TRUE)||got!=sizeof(data))return FALSE;
    CloseHandle(ov.hEvent);archive_io::close(file);
    HANDLE fail=archive_io::openW((folder/L"missing-resource.pvf").c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,0,nullptr);
    return fail==INVALID_HANDLE_VALUE&&GetLastError()==ERROR_FILE_NOT_FOUND;
}
extern "C" __declspec(dllexport) U WINAPI UiLabFixture(U kind,U object,U parent,const wchar_t*path){
    if(!fixture||!ready)return 0;Event e=event(kind);e.object=object;e.parent=parent;e.frame=1;e.flags=1;if(path)wcsncpy_s(e.path,path,_TRUNCATE);emit(e);return 1;
}
BOOL WINAPI DllMain(HINSTANCE module,DWORD reason,LPVOID){if(reason==DLL_PROCESS_ATTACH){selfModule=module;DisableThreadLibraryCalls(module);start();}return TRUE;}
