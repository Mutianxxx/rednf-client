#include "dnf/town_access.hpp"
#include "dnf/town_source_adapter.hpp"
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
int integer(const Json &j) {
    if(!j.is_number_integer() || j<std::numeric_limits<int>::min() || j>std::numeric_limits<int>::max())
        throw std::runtime_error("Town identity requires a signed integer in range");
    return j.get<int>();
}
double number(const Json &j) {
    if(!j.is_number() || !std::isfinite(j.get<double>())) throw std::runtime_error("Town coordinate is not finite");
    return j.get<double>();
}
std::string member(const std::string &root, std::string literal) {
    std::replace(literal.begin(),literal.end(),'\\','/');
    auto path=std::filesystem::u8path(literal);
    if(literal.empty() || path.is_absolute() || path.has_root_name()) throw std::runtime_error("Invalid town source path");
    if(normalize(literal).rfind(root+"/",0)!=0) path=std::filesystem::u8path(root)/path;
    const auto result=normalize(path.lexically_normal().generic_u8string());
    if(result.rfind(root+"/",0)!=0 || result.find("../")!=std::string::npos) throw std::runtime_error("Town path escaped source namespace");
    return result;
}
void issue(Json &out,const std::string &code,Json details=Json::object()) {
    details["code"]=code;out.push_back(std::move(details));
}
Json fields(const Script &s) {
    Json out=Json::array();for(const auto &f:s.fields)out.push_back({{"tag",f.tag},{"offset",f.offset},{"values",f.values}});return out;
}
std::vector<std::string> worldmaps(Pvf &p,int id) {
    std::vector<std::string> out;const auto list=p.script("worldmap/worldmap.lst").tokens;
    for(size_t i=0;i+1<list.size();i+=2) if(list[i].at("value").is_number_integer() &&
        list[i].at("value")==id && list[i+1].at("value").is_string()) out.push_back(member("worldmap",list[i+1].at("value")));
    return out;
}
} // namespace
Json TownLocation::json() const {
    Json out=preserved;out["version"]=1;out["town_id"]=townId;out["area_id"]=areaId;
    out["town_path"]=townPath;out["map_path"]=mapPath;
    out["town_source"]=townSource.json();out["map_source"]=mapSource.json();return out;
}
Json TownAccessArea::json() const {
    return {{"index",index},{"registration_ordinal",registrationOrdinal},{"area_ordinal",areaOrdinal},
        {"town_id",townId},{"area_id",areaId},{"town_path",townPath},{"town_name",townName},
        {"map_literal",mapLiteral},{"map_path",mapPath},{"kind",kind},{"readable",readable},{"valid",valid},
        {"authored_spawn",authoredSpawn?Json(*authoredSpawn):Json()},
        {"worldmap_id",worldmapId?Json(*worldmapId):Json()},{"worldmap_area",worldmapArea?Json(*worldmapArea):Json()},
        {"worldmap_path",worldmapPath},{"registration_source",registrationSource.json()},{"town_source",townSource.json()},
        {"area_source",areaSource.json()},{"map_source",mapSource.json()},
        {"registration",registration},{"raw",raw},{"diagnostics",diagnostics},{"complete_business",false}};
}
TownAccessCatalog::TownAccessCatalog(Pvf &p):pvf_(p) {
    const auto list=p.script("town/town.lst");
    documents_.push_back({{"source",makeSourceRef(p,list.path).json()},{"raw_bytes",list.rawBytes},{"tokens",list.tokens},{"fields",fields(list)}});
    std::set<std::string> registered;
    for(size_t i=0;i<list.tokens.size();) {
        const auto &token=list.tokens[i];
        const bool pair=token.at("value").is_number_integer() && i+1<list.tokens.size() && list.tokens[i+1].at("value").is_string();
        if(!pair) {issue(diagnostics_,"malformed_town_registration",{{"token",token},{"ordinal",i}});++i;continue;}
        const auto ordinal=i; i+=2;
        try {
            const int townId=integer(token.at("value"));
            const auto townPath=member("town",list.tokens[ordinal+1].at("value"));registered.insert(townPath);
            const auto town=p.script(townPath);const auto townSource=makeSourceRef(p,townPath);
            documents_.push_back({{"source",townSource.json()},{"raw_bytes",town.rawBytes},{"tokens",town.tokens},{"fields",fields(town)}});
            for(size_t f=0;f<town.fields.size();++f) {
                const auto &field=town.fields[f];if(normalize(field.tag)!="[area]")continue;
                TownAccessArea a;a.index=areas_.size();a.registrationOrdinal=ordinal;a.areaOrdinal=f;a.townId=townId;
                a.townPath=townPath;a.townName=town.text("[name]",townPath);a.raw=field.values;a.townSource=townSource;
                a.registration=Json::array({token,list.tokens[ordinal+1]});
                a.registrationSource=makeSourceRef(p,list.path,token.at("offset"),10,ordinal,"town-registration");
                const auto end=f+1<town.fields.size()?town.fields[f+1].offset:town.rawBytes.size();
                a.areaSource=makeSourceRef(p,townPath,field.offset,end-field.offset,f,"town-area");
                try {
                    if(field.values.size()<3 || !field.values[1].is_string())throw std::runtime_error("Malformed TWN area record");
                    a.areaId=integer(field.values[0]);if(a.townId<0 || a.areaId<0)throw std::runtime_error("Negative town/area ID");
                    a.mapLiteral=field.values[1];a.mapPath=member("map",a.mapLiteral);
                    const auto alias=townMapAliases1031().find(a.mapPath);
                    if(p.identity()==townMapAliasPackage1031() && !p.has(a.mapPath) && alias!=townMapAliases1031().end() && p.has(alias->second)) {
                        a.mapPath=alias->second;
                        issue(a.diagnostics,"explicit_1031_town_map_alias",{{"literal",a.mapLiteral},{"resolved",a.mapPath},
                            {"classification","inferred-current-source-adapter"},{"policy","1031-town-map-r-prefix-v1"}});
                    }
                    for(size_t v=2;v<field.values.size();++v) if(field.values[v].is_string()) {
                        const auto kind=normalize(field.values[v].get<std::string>());
                        if(kind!="[normal]" && kind!="[gate]" && kind!="[dungeon gate]" && kind!="[pub]" && kind!="[fishing place]")continue;
                        if(!a.kind.empty())throw std::runtime_error("Multiple TWN area kinds are ambiguous");
                        a.kind=kind;
                        if(kind=="[gate]") {
                            if(v+2>=field.values.size())throw std::runtime_error("Gate spawn has missing coordinates");
                            a.authoredSpawn=std::array<double,2>{number(field.values[v+1]),number(field.values[v+2])};
                        } else if(kind=="[dungeon gate]") {
                            if(v+1>=field.values.size())throw std::runtime_error("Dungeon gate has no source worldmap");
                            a.worldmapId=integer(field.values[v+1]);
                            if(v+2<field.values.size() && field.values[v+2].is_number_integer())a.worldmapArea=integer(field.values[v+2]);
                            else issue(a.diagnostics,"source_dungeon_gate_has_no_area_operand",{{"worldmap_id",*a.worldmapId},{"policy","retain-absent-no-fabricated-zero"}});
                            try {const auto paths=worldmaps(p,*a.worldmapId);if(paths.size()==1)a.worldmapPath=paths.front();
                                else issue(a.diagnostics,"worldmap_registration_missing_or_ambiguous",{{"worldmap_id",*a.worldmapId},{"paths",paths}});
                            }catch(const std::exception &e){issue(a.diagnostics,"worldmap_registry_unavailable",{{"error",e.what()}});}
                        }
                    }
                    if(a.kind.empty())issue(a.diagnostics,"unknown_town_area_kind_retained");
                    if(!p.has(a.mapPath))throw std::runtime_error("Registered town area MAP is missing");
                    a.mapSource=makeSourceRef(p,a.mapPath);p.script(a.mapPath);a.readable=true;a.valid=true;
                }catch(const std::exception &e){issue(a.diagnostics,"town_area_unavailable",{{"error",e.what()}});}
                areas_.push_back(std::move(a));
            }
        }catch(const std::exception &e){issue(diagnostics_,"registered_town_unavailable",{{"ordinal",ordinal},{"error",e.what()},{"registration",Json::array({token,list.tokens[ordinal+1]})}});}
    }
    for(const auto &path:p.paths("town/",".twn"))if(!registered.count(path))
        issue(diagnostics_,"unregistered_town_member_no_fabricated_id",{{"path",path},{"source",makeSourceRef(p,path).json()}});
    for(auto &a:areas_)if(find(a.townId,a.areaId).size()!=1) {
        a.valid=false;issue(a.diagnostics,"ambiguous_town_area_identity",{{"town_id",a.townId},{"area_id",a.areaId}});
    }
}
std::vector<size_t> TownAccessCatalog::find(int town,int area) const {
    std::vector<size_t> out;for(const auto &a:areas_)if(a.townId==town && a.areaId==area)out.push_back(a.index);return out;
}
size_t TownAccessCatalog::require(int town,int area) const {
    const auto found=find(town,area);if(found.size()!=1 || !admitted(found.front()))throw std::runtime_error("Town/area identity is missing, ambiguous or unreadable: "+std::to_string(town)+":"+std::to_string(area));return found.front();
}
bool TownAccessCatalog::admitted(size_t index) const {const auto &a=at(index);return a.valid && a.readable;}
TownLocation TownAccessCatalog::location(size_t index) const {
    if(!admitted(index))throw std::runtime_error("Town area is not available");const auto &a=at(index);
    TownLocation out;out.townId=a.townId;out.areaId=a.areaId;out.townPath=a.townPath;out.mapPath=a.mapPath;
    out.townSource=a.townSource;out.mapSource=a.mapSource;return out;
}
TownLocation TownAccessCatalog::validateLocation(const Json &saved) const {
    if(!saved.is_object() || integer(saved.at("version"))!=1)throw std::runtime_error("Unsupported TownLocation schema");
    auto result=location(require(integer(saved.at("town_id")),integer(saved.at("area_id"))));const auto current=result.json();
    for(const char *key:{"town_path","map_path","town_source","map_source"})if(saved.at(key)!=current.at(key))
        throw std::runtime_error(std::string("Saved town source mismatch: ")+key);
    result.preserved=saved;return result;
}
TownRestoreState TownAccessCatalog::restoreState(const Json &saved) const {
    if(!saved.is_object())throw std::runtime_error("Town restoration requires a region session object");
    TownRestoreState out;const auto where=saved.value("location",std::string("room"));
    if(saved.contains("town_location"))out.current=validateLocation(saved.at("town_location"));
    else if(where=="room" || where=="town" || where=="entrance") {
        out.current=location(require(1,where=="room"?1:where=="entrance"?2:0));
        issue(out.migrations,"legacy_elvengard_location",{{"location",where},{"town_id",1},{"area_id",out.current->areaId}});
    }
    if(saved.contains("return_town"))out.returnAnchor=validateLocation(saved.at("return_town"));
    else if(where=="dungeon") {
        out.returnAnchor=location(require(1,0));issue(out.migrations,"legacy_dungeon_return_elvengard_area_zero");
    }
    if(where=="room" || where=="entrance") {
        const int expected=where=="room"?1:2;
        if(!out.current || out.current->townId!=1 || out.current->areaId!=expected)throw std::runtime_error("Legacy location alias contradicts explicit TownLocation");
    } else if(where=="town" && !out.current)throw std::runtime_error("Town location is missing");
    return out;
}
void TownAccessCatalog::attachState(Json &j,const std::optional<TownLocation> &current,const std::optional<TownLocation> &anchor) const {
    Json next=j;
    if(current)next["town_location"]=validateLocation(current->json()).json();else next.erase("town_location");
    if(anchor)next["return_town"]=validateLocation(anchor->json()).json();else next.erase("return_town");
    j=std::move(next);
}
MapAccessPage TownAccessCatalog::page(const std::string &search,size_t offset,size_t limit) const {
    MapAccessPage out;std::vector<MapAccessEntry> matches;const auto query=normalize(search);
    for(const auto &a:areas_) {
        const auto label=a.townName+" / 区域 "+std::to_string(a.areaId);
        const auto haystack=normalize(std::to_string(a.townId)+":"+std::to_string(a.areaId)+" "+label+" "+a.mapPath+" "+a.townPath);
        if(!query.empty() && haystack.find(query)==std::string::npos)continue;
        MapAccessEntry row;row.index=a.index;row.id=a.areaId;row.key="town:"+std::to_string(a.townId)+":"+std::to_string(a.areaId);
        row.name=label;row.path=a.mapPath;row.type=a.kind;row.readable=a.readable;row.registered=true;
        row.source=a.mapSource;row.registrationSource=a.areaSource;row.diagnostics=a.diagnostics;matches.push_back(std::move(row));
    }
    out.total=matches.size();limit=std::max<size_t>(1,std::min<size_t>(limit,100));
    out.offset=matches.empty()?0:std::min(offset,((matches.size()-1)/limit)*limit);
    for(size_t i=out.offset;i<matches.size() && i<out.offset+limit;++i)out.entries.push_back(std::move(matches[i]));
    out.diagnostics=diagnostics_;return out;
}
Json TownNavigation::json() const {
    return {{"kind",kind==Kind::Area?"area":kind==Kind::DungeonGate?"dungeon_gate":"unavailable"},
        {"destination",destination?Json(*destination):Json()},{"worldmap_id",worldmapId?Json(*worldmapId):Json()},
        {"worldmap_area",worldmapArea?Json(*worldmapArea):Json()},{"worldmap_path",worldmapPath},{"diagnostics",diagnostics}};
}
TownNavigation TownAccessCatalog::navigate(const TownLocation &current,const TownExit &exit) const {
    TownNavigation out;try {
        const auto valid=validateLocation(current.json());const auto &source=at(require(valid.townId,valid.areaId));
        if(exit.town>=0 && exit.area>=0) {out.destination=require(exit.town,exit.area);out.kind=TownNavigation::Kind::Area;}
        else if(exit.town==-1 && exit.area==-1 && source.kind=="[dungeon gate]" && source.worldmapId) {
            out.kind=TownNavigation::Kind::DungeonGate;out.worldmapId=source.worldmapId;
            out.worldmapArea=source.worldmapArea;out.worldmapPath=source.worldmapPath;
            if(out.worldmapPath.empty())issue(out.diagnostics,"source_dungeon_gate_worldmap_unavailable",source.json());
        } else if(exit.town==-2 && exit.area==-2)
            issue(out.diagnostics,"guild_agit_entrance_requires_business_capability",{{"exit",exit.raw},{"source_area",source.json()},
                {"basis","CP949 mapsample.map:94-96 documents -2/-2 guild entrance/exit; no fabricated target town"}});
        else issue(out.diagnostics,"source_town_exit_mechanism_unavailable",{{"exit",exit.raw},{"source_area",source.json()}});
    }catch(const std::exception &e){issue(out.diagnostics,"town_navigation_unavailable",{{"error",e.what()},{"exit",exit.raw}});}
    return out;
}
Json TownAccessCatalog::json() const {
    Json rows=Json::array();for(const auto &a:areas_)rows.push_back(a.json());
    return {{"areas",rows},{"documents",documents_},{"diagnostics",diagnostics_},{"admission_policy","all-source-town-areas-early-access-v1"},{"complete_business",false}};
}
std::string townRuntimeLocation(const TownLocation &where) {
    if(where.townId==1 && where.areaId==1)return "room";
    if(where.townId==1 && where.areaId==2)return "entrance";
    return "town";
}
Json PreparedTownArea::json() const {
    return {{"ok",ok},{"town_location",location.json()},{"map",scene.path},{"spawn",spawn},
        {"diagnostics",diagnostics},{"records",records},{"complete_business",false}};
}
PreparedTownArea prepareTownArea(Pvf &p,Assets &assets,World &world,const RegionCatalog &legacy,
    const TownAccessCatalog &towns,size_t index,const std::optional<TownLocation> &from) {
    PreparedTownArea out;try {
        out.location=towns.location(index);const auto &area=towns.at(index);
        MapAccessEntry map;map.path=area.mapPath;map.key="town:"+std::to_string(area.townId)+":"+std::to_string(area.areaId);
        map.name=area.townName;map.readable=true;map.source=area.mapSource;
        auto prepared=prepareTownMapTraversal(p,assets,world,legacy,map);
        out.diagnostics=std::move(prepared.diagnostics);out.records=std::move(prepared.records);
        if(!prepared.ok || !prepared.geometryAvailable)throw std::runtime_error("Town has no usable source movement geometry");
        out.scene=std::move(prepared.scene);out.spawn=prepared.playerSpawn;
        bool reciprocal=false;
        if(from) {
            const auto source=towns.validateLocation(from->json());
            for(const auto &exit:out.scene.townExits)if(exit.town==source.townId && exit.area==source.areaId) {
                out.spawn=out.scene.townArrivalFrom(source.townId,source.areaId);reciprocal=true;break;
            }
            if(!reciprocal)issue(out.diagnostics,"reciprocal_town_exit_absent_use_authored_or_source_floor",{{"from",source.json()}});
        }
        if(!reciprocal && area.authoredSpawn)out.spawn={(*area.authoredSpawn)[0],(*area.authoredSpawn)[1]+out.scene.bg};
        World candidate(p,assets,WorldRules::BetaFoundationV1);candidate.tick=world.tick;candidate.mapWidth=out.scene.width;
        candidate.walkRects=out.scene.walkRects;candidate.blockedRects=out.scene.blockedRects;
        const auto requested=out.spawn;out.spawn=candidate.nearestWalkable(out.spawn[0],out.spawn[1]);
        if(!candidate.canWalk(out.spawn[0],out.spawn[1]))throw std::runtime_error("Town arrival has no reachable source floor");
        if(out.spawn!=requested)issue(out.diagnostics,"town_arrival_recovered_to_source_floor",{{"requested",requested},{"resolved",out.spawn}});
        for(const auto &npc:out.scene.npcs)if(!legacy.npcs.count(npc.id))
            issue(out.diagnostics,"town_npc_business_unavailable",{{"npc_id",npc.id},{"source",npc.source}});
        out.scene.issues=out.diagnostics;out.ok=true;
    }catch(const std::exception &e){issue(out.diagnostics,"town_preparation_failed_current_scene_preserved",{{"error",e.what()}});}
    return out;
}
} // namespace dnf
