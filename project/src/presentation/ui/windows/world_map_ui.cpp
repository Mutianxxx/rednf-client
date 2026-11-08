#include "dnf/world_map_ui.hpp"
#include "dnf/business_ui_render.hpp"
#include "dnf/content_profile.hpp"
#include <cmath>
#include <set>
namespace dnf {
namespace {
std::map<int,std::string> paths(Pvf &p,const std::string &registry) {
    std::map<int,std::string> out;const auto list=p.script(registry).tokens;
    for(size_t i=0;i+1<list.size();++i)if(list[i]["value"].is_number_integer()&&list[i+1]["value"].is_string()) {
        const auto child=normalize(list[++i]["value"]);
        out[list[i-1]["value"].get<int>()]=normalize((std::filesystem::u8path(registry).parent_path()/std::filesystem::u8path(child)).lexically_normal().generic_u8string());
    }return out;
}
SelectionRect rect(const Json &v) {
    if(v.size()!=4)throw std::runtime_error("MM rectangle requires four source coordinates");
    for(const auto &n:v)if(!n.is_number())throw std::runtime_error("MM rectangle is not numeric");
    return {v[0],v[1],v[2].get<double>()-v[0].get<double>(),v[3].get<double>()-v[1].get<double>()};
}
Json fieldRows(const Script&s) {Json rows=Json::array();for(const auto &f:s.fields)rows.push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});return rows;}
}
void WorldMapUi::bind(Pvf &pvf,Assets &assets) {
    pages_.clear();sources_=Json::array();diagnostics_=Json::array();page_=0;followedTown_=-1;
    const auto worldmaps=paths(pvf,"worldmap/worldmap.lst"),regions=paths(pvf,"region/region.lst"),npcs=paths(pvf,"npc/npc.lst");
    for(const auto &[id,rgn]:regions)try {
        const auto region=pvf.script(rgn);const auto literal=region.text("[minimap]");
        if(literal.empty())throw std::runtime_error("Registered region has no minimap binding");
        const auto path=normalize((std::filesystem::u8path(rgn).parent_path()/std::filesystem::u8path(literal)).lexically_normal().generic_u8string());
        const auto s=pvf.script(path);WorldMapPageView page;page.name=region.text("[name]",rgn);page.path=path;
        const auto image=s.values("[map]"),background=s.values("[background]");
        if(image.size()<2||!image[0].is_string()||!image[1].is_number_integer())throw std::runtime_error("MM map image binding missing");
        page.image=normalize(image[0]);page.imageFrame=image[1];page.imageFrames.push_back(page.imageFrame);
        if(background.size()>=2&&background[0].is_string()&&background[1].is_number_integer()){page.background=normalize(background[0]);page.backgroundFrame=background[1];}
        const auto px=assets.pixels(page.image,page.imageFrame);page.width=px.logicalWidth;page.height=px.logicalHeight;
        if(page.width<=0||page.height<=0)throw std::runtime_error("MM map image has invalid logical extent");
        enum class Scope {None,Town,World};Scope scope=Scope::None;int town=-1;WorldMapAreaView *area=nullptr;WorldMapGateView *gate=nullptr;bool grid=false;
        for(const auto &f:s.fields) {
            const auto tag=normalize(f.tag);
            if(tag=="[town]"){scope=Scope::Town;town=-1;area=nullptr;gate=nullptr;}
            else if(tag=="[/town]"){scope=Scope::None;area=nullptr;}
            else if(tag=="[world]"){scope=Scope::World;page.gates.emplace_back();gate=&page.gates.back();area=nullptr;}
            else if(tag=="[/world]"){scope=Scope::None;gate=nullptr;}
            else if(tag=="[grid map]")grid=true;
            else if(tag=="[/grid map]")grid=false;
            else if(scope==Scope::Town&&tag=="[area]"){page.areas.push_back({});area=&page.areas.back();area->town=town;}
            else if(tag=="[/area]")area=nullptr;
            else if(tag=="[index]"&&!f.values.empty()&&f.values[0].is_number_integer()) {
                if(scope==Scope::Town){if(area)area->area=f.values[0];else town=f.values[0];}
                else if(gate)gate->worldmap=f.values[0];
            } else if(area&&tag=="[real rect]")area->real=rect(f.values);
            else if(area&&tag=="[project rect]")area->projected=rect(f.values);
            else if(area&&tag=="[npc]"&&f.values.size()==3&&f.values[0].is_number_integer()&&f.values[1].is_number()&&f.values[2].is_number()) {
                WorldMapNpcView npc;npc.id=f.values[0];npc.real={f.values[1],f.values[2]};npc.sourceOffset=f.offset;
                if(const auto found=npcs.find(npc.id);found!=npcs.end())npc.name=pvf.script(found->second).text("[name]",found->second);
                // Current client NPC-indexed minimap sheet, not dialogue portraits.
                // ID->frame association is supported by matching 1031 NPC registrations
                // and source art; native loader mapping remains an explicit inference.
                try{const auto px=assets.pixels("interface2/minimap/town/minimap_npcicon.img",npc.id);
                    if(px.logicalWidth<=0||px.logicalHeight<=0)throw std::runtime_error("Empty NPC minimap icon");npc.frame=npc.id;
                }catch(const std::exception&e){diagnostics_.push_back({{"code","mm_npc_icon_unavailable"},{"id",npc.id},{"source",path},{"offset",f.offset},{"error",e.what()}});}
                area->npcs.push_back(std::move(npc));
            }
            else if(gate&&tag=="[point]"&&f.values.size()==2)gate->point={f.values[0],f.values[1]};
            else if(gate&&tag=="[level]"&&!grid)gate->levels=f.values;
            else if(grid&&tag=="[image number]"&&!f.values.empty()&&f.values[0].is_number_integer()) {
                const int frame=f.values[0];if(frame>=0&&std::find(page.imageFrames.begin(),page.imageFrames.end(),frame)==page.imageFrames.end()) {
                    try{assets.pixels(page.image,frame);page.imageFrames.push_back(frame);}
                    catch(const std::exception&e){diagnostics_.push_back({{"code","mm_grid_image_unavailable"},{"source",path},{"offset",f.offset},{"image",page.image},{"frame",frame},{"error",e.what()}});}
                }
            }
        }
        for(auto &g:page.gates)if(const auto found=worldmaps.find(g.worldmap);found!=worldmaps.end()) {
            g.path=found->second;try{g.name=pvf.script(g.path).text("[name]",g.path);}catch(const std::exception&e){diagnostics_.push_back({{"path",g.path},{"error",e.what()}});}
        }else diagnostics_.push_back({{"code","unregistered_mm_worldmap"},{"id",g.worldmap},{"source",path}});
        sources_.push_back({{"region",makeSourceRef(pvf,rgn).json()},{"minimap",makeSourceRef(pvf,path).json()},
            {"raw_bytes",s.rawBytes},{"tokens",s.tokens},{"fields",fieldRows(s)}});
        pages_.push_back(std::move(page));
    }catch(const std::exception&e){diagnostics_.push_back({{"path",rgn},{"error",e.what()}});}
}
std::optional<SelectionPoint> WorldMapUi::project(const WorldMapAreaView &a,double x,double y) {
    if(a.real.width<=0||a.real.height<=0||a.projected.width<=0||a.projected.height<=0)return {};
    return SelectionPoint{a.projected.x+std::clamp((x-a.real.x)/a.real.width,0.0,1.0)*a.projected.width,
        a.projected.y+std::clamp((y-a.real.y)/a.real.height,0.0,1.0)*a.projected.height};
}
Json WorldMapUi::snapshot() const {
    Json pages=Json::array();for(const auto&p:pages_){Json gates=Json::array();for(const auto&g:p.gates)gates.push_back({{"id",g.worldmap},{"path",g.path},{"point",{g.point.x,g.point.y}},{"name",g.name},{"levels",g.levels}});
        Json areas=Json::array();for(const auto&a:p.areas){Json npcs=Json::array();for(const auto&n:a.npcs)npcs.push_back({{"id",n.id},{"frame",n.frame},{"source_point",{n.real.x,n.real.y}},{"name",n.name},{"offset",n.sourceOffset}});
            areas.push_back({{"town",a.town},{"area",a.area},{"npc",npcs}});}
        pages.push_back({{"areas",areas},{"path",p.path},{"image",p.image},{"frame",p.imageFrame},{"image_frames",p.imageFrames},{"area_count",p.areas.size()},{"gates",gates}});}
    return {{"classification","1031 MM coordinates/images confirmed; projection and navigation UI inferred"},{"pages",pages},{"sources",sources_},{"diagnostics",diagnostics_}};
}
WorldMapUiAction WorldMapUi::draw(Renderer&r,int town,int area,double px,double py,SelectionUiPointer pointer,int64_t ms) {
    if(pages_.empty()){r.text("当前来源没有可显示的世界地图",225,260,18);return {};}
    if(town!=followedTown_){for(size_t i=0;i<pages_.size();++i)if(std::any_of(pages_[i].areas.begin(),pages_[i].areas.end(),[&](const auto&a){return a.town==town;})){page_=i;break;}followedTown_=town;}
    // Hit testing precedes drawing so a tab click switches in this same frame.
    for(size_t i=0;i<pages_.size();++i)if(pointer.click&&SelectionRect{double(12+i*160),8,150,27}.contains({double(pointer.x),double(pointer.y)}))page_=i;
    const auto&p=pages_[page_];const double scale=std::min(800.0/p.width,600.0/p.height),ox=(800-p.width*scale)/2,oy=(600-p.height*scale)/2;
    r.rect(0,0,800,600,{8,9,14,255});
    if(!p.background.empty())r.sprite(p.background,p.backgroundFrame,ox,oy,1,scale);
    for(const int frame:p.imageFrames)r.sprite(p.image,frame,ox,oy,1,scale);
    for(const auto&a:p.areas)for(const auto&npc:a.npcs)if(npc.frame>=0)if(const auto point=project(a,npc.real.x,npc.real.y)) {
        const double x=ox+point->x*scale,y=oy+point->y*scale;
        r.sprite("interface2/minimap/town/minimap_npcicon.img",npc.frame,x-9.5,y-9.5,1,1,0,255,0,false);
        if(SelectionRect{x-10,y-10,20,20}.contains({double(pointer.x),double(pointer.y)})) {
            const float tx=float(std::clamp(x-75,4.0,646.0)),ty=float(std::clamp(y+12,38.0,551.0));
            r.rect(tx,ty,150,23,{12,14,24,245});r.text(businessUiFitted(r,npc.name,140,12),tx+5,ty+4,12);
        }
    }
    // The source world-map area rectangle is a navigation/mapping region, not
    // a screen selection border. Do not paint the old reconstructed yellow
    // rectangle over the map; keep the source-backed player marker only.
    for(const auto&a:p.areas)if(a.town==town&&a.area==area)
        if(const auto point=project(a,px,py))
            r.sprite("interface2/minimap/dungeon/minimap.img",196,ox+point->x*scale,oy+point->y*scale-14,1,0.8,0,uint8_t(190+(ms/250%2)*65));
    WorldMapUiAction action;for(const auto&g:p.gates){const double x=ox+g.point.x*scale,y=oy+g.point.y*scale;const SelectionRect hit{x-14,y-14,28,28};const bool hover=hit.contains({double(pointer.x),double(pointer.y)});
        r.sprite("interface/minimap.img",37,x-7,y-7,1,1,0,g.path.empty()?90:255);
        if(hover){r.rect(float(std::clamp(x-85,0.0,620.0)),float(y+13),180,24,{12,14,24,245});r.text(businessUiFitted(r,g.name,174,13),float(std::clamp(x-82,3.0,623.0)),float(y+17),13);if(pointer.click&&!g.path.empty())action={g.path,g.worldmap};}}
    for(size_t i=0;i<pages_.size();++i)r.button(pages_[i].name,12+int(i)*160,8,150,27,pointer.x,pointer.y,false);
    r.text("点击地下城标记预览该区域；M / Esc 关闭",230,576,13);return action;
}
int dungeonMinimapFrame(int doors,int64_t ms,bool active) {
    if(doors<1||doors>15)return -1;
    // Current 1031 IMG is 15 greed bitmask groups, eight phase frames each.
    (void)ms; // Current room is a stable source phase, not a persistent blink.
    return 44+(doors-1)*8+(active?4:0);
}
void drawSourceDungeonMinimap(Renderer&r,const DungeonRun&run,bool expanded,int64_t ms) {
    if(run.rooms.empty())return;
    if(expanded)r.rect(0,0,800,600,{8,9,14,250});
    const double step=expanded?std::min({60.0,720.0/std::max(1,run.width),500.0/std::max(1,run.height)}):std::min(23.0,210.0/std::max(run.width,run.height));
    const double scale=step/23.0,ox=expanded?(800-run.width*step)/2:776-run.width*step,oy=expanded?(600-run.height*step)/2:42;
    // Reconstructed outer panel; source room/door/Boss icons remain unchanged.
    // Do not stretch minimap.img frame2: it contains a different compass ornament.
    const float panelX=float(ox-8),panelY=float(oy-8),panelW=float(run.width*step+16),panelH=float(run.height*step+16);
    r.rect(panelX,panelY,panelW,panelH,{10,12,22,215});r.rect(panelX,panelY,panelW,panelH,{170,153,107,255},false);
    for(size_t i=0;i<run.rooms.size();++i){const auto&room=run.rooms[i];const double x=ox+room.x*step,y=oy+room.y*step;const int frame=dungeonMinimapFrame(room.doors,ms,int(i)==run.current);
        if(frame>=0)r.sprite("interface/minimap.img",frame,x,y,1,scale,0,room.visited?255:130);
        if(room.boss)r.sprite("interface/minimap.img",37,x+2*scale,y+2*scale,1,scale,0,255);
        if(int(i)==run.current)r.rect(float(x-1),float(y-1),float(19*scale+2),float(19*scale+2),{255,224,129,255},false);
    }
}
} // namespace dnf
