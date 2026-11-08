#include "dnf/region.hpp"
#include "dnf/content_profile.hpp"
#include <chrono>
#include <set>
namespace dnf {
namespace {
std::string relative(const std::string &root,const std::string &child) {
    return normalize((std::filesystem::u8path(root).parent_path()/std::filesystem::u8path(child)).lexically_normal().generic_u8string());
}
std::map<int,std::string> registry(Pvf&p,const std::string&path) {
    std::map<int,std::string> out;const auto tokens=p.script(path).tokens;
    for(size_t i=0;i+1<tokens.size();++i)if(tokens[i]["value"].is_number_integer()&&tokens[i+1]["value"].is_string()) {
        out[tokens[i]["value"].get<int>()]=relative(path,tokens[i+1]["value"]);++i;
    }return out;
}
std::vector<int> masks(std::string text) {
    std::vector<int> out;for(size_t i=0;i<text.size();++i)if(text[i]>='A'&&text[i]<='P'){out.push_back(text[i]-'A');if(i+1<text.size()&&text[i+1]==text[i])++i;}return out;
}
std::vector<std::array<int,2>> coords(const Json&v){std::vector<std::array<int,2>>out;for(size_t i=0;i+1<v.size();i+=2)out.push_back({v[i],v[i+1]});return out;}
}
void RegionCatalog::prepareWorldDungeonIndex() {
    if(worldDungeonIndexReady_)return;
    worldRegisteredMaps_=registry(pvf_,"map/map.lst");
    for(const auto &[id,path]:registry(pvf_,"dungeon/dungeon.lst")) {
        if(dungeons.count(id))continue;
        DungeonDefinition d;d.id=id;d.path=path;d.name=path;
        d.lockedReason="DGN metadata not yet requested";dungeons[id]=std::move(d);
    }
    // Directory only: no MAP, MOB, ANI, NPK or image decode.
    worldDungeonIndexReady_=true;
}
Json RegionCatalog::prepareDungeonMetadata(int id) {
    prepareWorldDungeonIndex();Json report={{"id",id},{"status","failed"},{"diagnostics",Json::array()}};
    const auto found=dungeons.find(id);if(found==dungeons.end()){report["diagnostics"].push_back({{"code","dungeon_not_registered"}});return report;}
    auto&existing=found->second;report["path"]=existing.path;
    if(preparedDungeonMetadata_.count(id)){report["status"]=existing.enabled?"prepared":"failed";report["cached"]=true;report["reason"]=existing.lockedReason;return report;}
    if((id==1||id==2)&&existing.enabled){preparedDungeonMetadata_.insert(id);report["status"]="prepared";return report;}
    DungeonDefinition d;d.id=id;d.path=existing.path;d.name=existing.path;
    try {
        d.source=pvf_.script(d.path);report["source"]=makeSourceRef(pvf_,d.path).json();
        d.name=d.source.text("[name]",d.path);d.minimumLevel=int(d.source.number("[minimum required level]",1));d.basisLevel=int(d.source.number("[basis level]",d.minimumLevel));
        const auto slot=d.source.values("[worldmap pattern info]");if(slot.size()>=4&&slot[2].is_string()&&slot[3].is_number_integer()){d.slotImage=normalize(slot[2]);d.slotFrame=slot[3];}
        for(const auto&v:d.source.values("[pathgate object]"))if(v.is_number_integer())d.pathgateObjects.push_back(v.get<int>());
        MazeDefinition*maze=nullptr;for(const auto&f:d.source.fields){
            if(f.tag=="[maze info]"){d.mazes.emplace_back();maze=&d.mazes.back();}
            if(!maze)continue;
            maze->sourceFields.push_back({{"tag",f.tag},{"values",f.values},{"offset",f.offset}});
            if(f.tag=="[size]"&&f.values.size()>=2){maze->width=f.values[0];maze->height=f.values[1];}
            if(f.tag=="[greed]"&&!f.values.empty())maze->doorMasks=masks(f.values[0]);
            if(f.tag=="[start map]")maze->starts=coords(f.values);
            if(f.tag=="[boss map]")maze->bosses=coords(f.values);
            if((f.tag=="[map specification]"||f.tag=="[boss map specification]")&&f.values.size()>=3){
                const int cell=f.values[1].get<int>()*maze->width+f.values[0].get<int>();auto &target=f.tag=="[map specification]"?maze->specifiedMaps[cell]:maze->specifiedBossMaps[cell];
                for(size_t i=2;i<f.values.size();++i)if(f.values[i].is_number_integer())target.push_back(f.values[i].get<int>());
            }
        }
        d.enabled=!d.mazes.empty();if(!d.enabled)d.lockedReason="Source DGN has no supported maze info; special flow retained";
    }catch(const std::exception&e){d.lockedReason=e.what();report["diagnostics"].push_back({{"code","dungeon_metadata_unavailable"},{"error",e.what()}});}
    existing=std::move(d);preparedDungeonMetadata_.insert(id);report["status"]=existing.enabled?"prepared":"failed";report["reason"]=existing.lockedReason;return report;
}
Json RegionCatalog::prepareWorldmap(const std::string&path) {
    prepareWorldDungeonIndex();Json report={{"path",path},{"status","prepared"},{"dungeons",Json::array()},{"diagnostics",Json::array()}};
    try {
        const auto source=pvf_.script(path);const auto ui=source.text("[ui path]");
        if(ui.empty())throw std::runtime_error("WDM has no source UI path");
        std::set<int> seen;for(const auto&f:pvf_.script(ui).fields)if(f.tag=="[ui controls]"&&!f.values.empty()&&f.values[0]=="[balloon]"&&f.values.back().is_number_integer()) {
            int id=f.values.back();if(seen.insert(id).second)report["dungeons"].push_back(prepareDungeonMetadata(id));
        }
    }catch(const std::exception&e){report["status"]="failed";report["diagnostics"].push_back({{"code","worldmap_ui_unavailable"},{"error",e.what()}});}
    return report;
}
void RegionCatalog::prepareMapMembershipIndex() {
    if(worldMapMembershipReady_)return;
    prepareWorldDungeonIndex();
    const auto started=std::chrono::steady_clock::now();size_t scanned=0;
    for(const auto&[id,path]:worldRegisteredMaps_)try {
        const auto source=pvf_.fieldView(path,{"[dungeon]"});std::set<int> owners;
        for(const auto&field:source.fields)for(const auto&value:field.values)
            if(value.is_number_integer()&&value.get<int>()>=0)owners.insert(value.get<int>());
        for(int owner:owners)worldMapPaths_[owner].push_back({id,path});++scanned;
    }catch(const std::exception&e){issues.push_back({{"code","map_membership_unreadable"},{"map_id",id},{"path",path},{"error",e.what()}});}
    issues.push_back({{"code","on_demand_map_membership_index"},{"registered",worldRegisteredMaps_.size()},{"scanned",scanned},{"elapsed_ms",std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-started).count()},{"scope","selected dungeon fields only via Pvf::fieldView; no full MAP Script/Assets decode"}});
    worldMapMembershipReady_=true;
}
Json RegionCatalog::prepareDungeon(int id) {
    auto report=prepareDungeonMetadata(id);if(report["status"]!="prepared")return report;
    auto&d=dungeons.at(id);report["status"]="failed";
    if(preparedWorldDungeons_.count(id)){report["status"]="prepared";report["cached"]=true;return report;}
    try {prepareMapMembershipIndex();}catch(const std::exception&e){report["diagnostics"].push_back({{"code","map_membership_index_failed"},{"error",e.what()}});return report;}
    std::map<int,std::string> dependencies;for(const auto&[mapId,path]:worldMapPaths_[id])dependencies[mapId]=path;
    for(const auto&m:d.mazes)for(const auto*spec:{&m.specifiedMaps,&m.specifiedBossMaps})for(const auto&[cell,ids]:*spec)for(int mapId:ids){
        (void)cell;const auto it=worldRegisteredMaps_.find(mapId);if(it==worldRegisteredMaps_.end())report["diagnostics"].push_back({{"code","specified_map_not_registered"},{"map_id",mapId}});else dependencies[mapId]=it->second;
    }
    std::vector<MapDefinition> staged;std::set<int> used;
    for(const auto &[mapId,path]:dependencies)try {
        MapDefinition m;m.id=mapId;m.path=path;m.dungeon=id;m.source=pvf_.script(path);m.boss=m.source.text("[type]")=="[boss]";
        auto g=masks(m.source.text("[greed]"));m.acceptedDoorMasks=sourceMapDoorMasks(m.source);m.special=g.empty();if(!g.empty()){m.allowedDoors=g[0];m.requiredDoors=g.size()>1?g[1]:g[0];}
        const auto stem=std::filesystem::u8path(path).stem().u8string();m.start=!stem.empty()&&stem[0]=='s';
        m.monsters=parseMonsterSpawns(m.source.values("[monster]"));for(const auto&spawn:m.monsters)used.insert(spawn.id);staged.push_back(std::move(m));
    }catch(const std::exception&e){report["diagnostics"].push_back({{"code","dungeon_map_unavailable"},{"map_id",mapId},{"path",path},{"error",e.what()}});}
    if(staged.empty())report["diagnostics"].push_back({{"code","dungeon_has_no_registered_maps"}});
    if(!report["diagnostics"].empty()){report["reason"]="MAP source failure; complete dependency pool retained, no reduced pool published";return report;}
    std::map<int,Script> mobs;
    for(int mobId:used)try {const auto path=monsterPath(mobId);if(path.empty())throw std::runtime_error("Monster ID not registered");mobs[mobId]=pvf_.script(path);}
    catch(const std::exception&e){report["diagnostics"].push_back({{"code","dungeon_monster_unavailable"},{"monster_id",mobId},{"error",e.what()}});}
    if(!report["diagnostics"].empty())return report;
    d.mapIds.clear();for(auto&m:staged){d.mapIds.push_back(m.id);maps[m.id]=std::move(m);}for(auto &[mobId,s]:mobs)monsters[mobId]=std::move(s);
    preparedWorldDungeons_.insert(id);report["status"]="prepared";report["map_count"]=d.mapIds.size();report["monster_count"]=used.size();return report;
}
} // namespace dnf
