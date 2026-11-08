// Independent process: reuses the hash-bound 1031 decoder, never calls the game.
#include "dnf/resources.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <set>
#include <windows.h>
using namespace dnf;
namespace fs=std::filesystem;
int wmain(int argc,wchar_t**argv){
    try{
        if(argc!=3)throw std::runtime_error("usage: ui_assets CLIENT OUTPUT");
        Pvf pvf(fs::path(argv[1])/L"Script.pvf");Assets assets(fs::path(argv[1]),pvf);
        fs::path out=argv[2];fs::create_directories(out);
        std::cout<<Json({{"ready",true},{"npk_errors",assets.errors},{"images",assets.count()}}).dump()<<std::endl;
        std::string line;
        while(std::getline(std::cin,line)){
            Json answer;
            try{
                auto q=Json::parse(line);std::string op=q.at("op");
                if(op=="catalog"){
                    Json scripts=Json::array();
                    for(auto&p:pvf.paths("",".ui")){
                        auto raw=pvf.read(p);Json row={{"path",p},{"size",raw.size()}};
                        if(raw.empty()){row["empty"]=true;scripts.push_back(row);continue;}
                        try{auto s=pvf.script(p);row["tokens"]=s.tokens;row["fields"]=Json::array();
                            for(auto&f:s.fields)row["fields"].push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});
                        }catch(const std::exception&e){row["error"]=e.what();}
                        scripts.push_back(row);
                    }
                    Json entries=Json::object();for(auto&e:assets.entries()){
                        auto &a=entries[e.first]=Json::array();for(auto&n:e.second)a.push_back({{"archive",n.archive.u8string()},{"offset",n.offset},{"length",n.length}});
                    }
                    writeJson(out/"scripts.json",scripts);writeJson(out/"npk-index.json",entries);
                    answer={{"ok",true},{"scripts",scripts.size()},{"images",entries.size()},{"npk_errors",assets.errors}};
                }else if(op=="audit_ani"){
                    std::ofstream f(out/"ani-audit.jsonl",std::ios::binary);UCHAR unused=0;(void)unused;
                    size_t total=0,failed=0,frames=0;Json nodes=Json::object(),missing=Json::object(),errors=Json::object();
                    for(auto&p:pvf.paths("",".ani")){
                        Json row={{"path",p}};++total;
                        try{auto a=decodeAni(pvf.read(p),p);row["frames"]=a.frames.size();frames+=a.frames.size();row["nodes"]=Json::array();
                            auto properties=[&](const Json&props){for(auto i=props.begin();i!=props.end();++i){auto key=i.key();nodes[key]=nodes.value(key,size_t(0))+1;if(std::find(row["nodes"].begin(),row["nodes"].end(),key)==row["nodes"].end())row["nodes"].push_back(key);}};
                            properties(a.globals);for(auto&frame:a.frames){properties(frame.properties);if(!frame.image.empty()&&!assets.has(frame.image))missing[frame.image]=missing.value(frame.image,size_t(0))+1;}
                            row["decoded"]=true;
                        }catch(const std::exception&e){++failed;row["decoded"]=false;row["error"]=e.what();errors[e.what()]=errors.value(e.what(),size_t(0))+1;}
                        f<<row.dump()<<'\n';
                    }
                    answer={{"ok",true},{"total",total},{"failed",failed},{"frames",frames},{"node_occurrences",nodes},{"errors",errors},{"missing_image_references",missing}};
                    writeJson(out/"ani-summary.json",answer);
                }else if(op=="reference_sources"){
                    std::set<std::string> targets;
                    for(const auto&value:q.at("targets")){auto path=normalize(value.get<std::string>());if(path.rfind("sprite/",0)!=0)path="sprite/"+path;targets.insert(path);}
                    if(targets.size()>4096)throw std::runtime_error("Too many reference targets");
                    struct ReferenceStats{size_t count=0;std::set<std::string>animations;std::set<int>frames;Json examples=Json::array();};
                    std::unordered_map<std::string,ReferenceStats> references;
                    size_t scanned=0,failed=0;
                    Json failures=Json::array();
                    for(const auto&path:pvf.paths("",".ani")){
                        ++scanned;
                        try{
                            auto animation=decodeAni(pvf.read(path),path);
                            for(size_t frame=0;frame<animation.frames.size();++frame){
                                const auto&source=animation.frames[frame];
                                auto image=normalize(source.image);if(!image.empty()&&image.rfind("sprite/",0)!=0)image="sprite/"+image;
                                if(targets.count(image)){
                                    auto&stats=references[image];++stats.count;stats.animations.insert(path);stats.frames.insert(source.imageFrame);
                                    if(stats.examples.size()<8)stats.examples.push_back({{"animation",path},{"ani_frame",frame},{"image_frame",source.imageFrame}});
                                }
                            }
                        }catch(const std::exception&error){
                            ++failed;if(failures.size()<256)failures.push_back({{"path",path},{"error",error.what()}});
                        }
                    }
                    Json rows=Json::array();size_t total=0,matched=0;
                    for(const auto&target:targets){auto found=references.find(target);Json row={{"path",target},{"frame_references",0},{"animation_count",0},{"image_frames",Json::array()},{"examples",Json::array()}};
                        if(found!=references.end()){
                            row["frame_references"]=found->second.count;row["animation_count"]=found->second.animations.size();row["image_frames"]=found->second.frames;row["examples"]=found->second.examples;
                            total+=found->second.count;if(found->second.count)++matched;
                        }
                        rows.push_back(row);
                    }
                    Json report={{"scanned",scanned},{"matched_paths",matched},{"frame_references",total},{"failed",failed},{"references",rows},{"failures",failures}};
                    writeJson(out/"ani-reference-usage-native.json",report);
                    answer={{"ok",true},{"scanned",scanned},{"matched_paths",matched},{"frame_references",total},{"failed",failed},{"failures",failures},{"file","ani-reference-usage-native.json"}};
                }else if(op=="image"){
                    std::string name=normalize(q.at("path"));int frame=q.at("frame");
                    Pixels pixels;
                    std::string archive=q.value("archive",std::string());
                    if(archive.empty())pixels=assets.pixels(name,frame);
                    else{
                        std::string physical=name.rfind("sprite/",0)==0?name:"sprite/"+name;
                        auto found=assets.entries().find(physical);
                        if(found==assets.entries().end())throw std::runtime_error("Missing NPK resource: "+physical);
                        const NpkEntry*selected=nullptr;size_t filename_matches=0;
                        for(const auto&entry:found->second){
                            auto relative=entry.archive.lexically_relative(assets.root()).generic_u8string();
                            if(normalize(relative)==normalize(archive))selected=&entry;
                            if(normalize(entry.archive.filename().u8string())==normalize(std::filesystem::u8path(archive).filename().u8string()))++filename_matches;
                        }
                        if(!selected)throw std::runtime_error("Physical NPK candidate not found: "+archive);
                        if(filename_matches!=1)throw std::runtime_error("Physical NPK filename is not unique for archive selector: "+archive);
                        auto raw=assets.blob(name,selected->archive.filename().u8string());
                        pixels=decodeImg(raw,frame);
                    }
                    if(pixels.width<=0||pixels.height<=0||pixels.rgba.empty())throw std::runtime_error("empty image");
                    // Request IDs, not arbitrary user paths, name generated files.
                    auto key=q.at("key").get<std::string>();
                    if(key.empty()||key.find_first_not_of("0123456789abcdef")!=std::string::npos)throw std::runtime_error("invalid key");
                    fs::path png=out/(key+".png");std::ofstream f(png,std::ios::binary);
                    auto write=[](void*c,void*d,int n){((std::ofstream*)c)->write((char*)d,n);};
                    if(!stbi_write_png_to_func(write,&f,pixels.width,pixels.height,4,pixels.rgba.data(),pixels.width*4)||!f)throw std::runtime_error("PNG write");
                    Json sourceReads=Json::object();
                    auto read=assets.reads().find(normalize(name));
                    if(read!=assets.reads().end())sourceReads[normalize(name)]=read.value();
                    answer={{"ok",true},{"png",png.u8string()},{"width",pixels.width},{"height",pixels.height},{"x",pixels.x},{"y",pixels.y},{"logical_width",pixels.logicalWidth},{"logical_height",pixels.logicalHeight},{"source_reads",sourceReads}};
                }else if(op=="animation"){
                    auto name=normalize(q.at("path"));auto animation=assets.animation(name);
                    Json frames=Json::array();
                    for(size_t i=0;i<animation->frames.size();++i){
                        const auto& f=animation->frames[i];auto p=animation->samplePose(0,false,int(i));
                        bool tween=f.properties.value("10",animation->globals.value("10",false));
                        frames.push_back({{"duration",f.duration},{"interpolate",tween},{"properties",f.properties},
                            {"pose",{{"image",p.image},{"image_frame",p.imageFrame},{"x",p.x},{"y",p.y},
                                {"scale_x",p.scaleX},{"scale_y",p.scaleY},{"rotation",p.rotationRadians},
                                {"rgba",p.rgba},{"blend",p.blend},{"flip",p.flip},{"effect_rgb",p.effectRgb},{"unsupported",p.unsupported}}}});
                    }
                    answer={{"ok",true},{"path",name},{"duration",animation->duration},{"frames",frames},{"globals",animation->globals}};
                }else if(op=="quit")break;
                else throw std::runtime_error("unknown op");
            }catch(const std::exception&e){answer={{"ok",false},{"error",e.what()}};}
            std::cout<<answer.dump()<<std::endl;
        }
    }catch(const std::exception&e){std::cerr<<e.what()<<std::endl;return 1;}
}
