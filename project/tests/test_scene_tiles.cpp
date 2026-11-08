#include "dnf/scene_tiles.hpp"
#include "dnf/scene.hpp"
#include "dnf/combat.hpp"
#include "dnf/map_exploration.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace dnf {
namespace {
bool near(double a,double b){return std::abs(a-b)<1e-7;}
Json checkTileMap(Pvf &pvf,Assets &assets,const std::string &path) {
    size_t count=0;
    auto check=[&](bool ok,const std::string &message){
        if(!ok)throw std::runtime_error("Source TIL: "+path+": "+message);
        ++count;
    };
    Scene scene;scene.path=path;scene.script=pvf.script(path);
    scene.bg=int(scene.script.number("[background pos]",80));
    const auto bytes=pvf.read(path);
    auto loaded=loadSceneSourceTiles(pvf,assets,scene);
    if(!loaded.complete)return {{"path",path},{"complete",false},{"diagnostics",loaded.diagnostics},{"count",count}};
    check(loaded.columnsResolved,"all authored source columns resolved");
    size_t zero=0,drawable=0,transparent=0,extended=0;
    const size_t basics=scene.script.values("[tile]").size();
    check(loaded.records.size()==basics+scene.script.values("[extended tile]").size(),"all authored repeated tile slots consumed");
    check(scene.tileGrids.size()==loaded.records.size(),"every source tile has a preserved grid");
    for(size_t t=0;t<scene.tileGrids.size();++t) {
        const auto &grid=scene.tileGrids[t];
        const auto source=pvf.script(grid.at("tile"));
        check(grid.at("pass_values")==source.values("[pass type]"),"pass0/1/2 retained without conversion");
        check(loaded.records[t].at("tile_tokens")==source.tokens,"original ordered source TIL tokens preserved");
        const auto sourceBefore=pvf.read(source.path);
        const auto &origin=grid.at("origin");const auto &size=grid.at("image_logical_size");
        const size_t column=grid.at("column");
        check(column<basics,"extended tile refers to authored basic column");
        if(grid.at("extended").get<bool>()) {
            ++extended;
            const size_t row=grid.at("extended_row");
            check(column==(t-basics)%basics&&row==(t-basics)/basics,"extended order wraps by authored basic count");
            double y=scene.bg+scene.tileGrids[column].at("image_logical_size")[1].get<double>();
            for(size_t prior=basics+column;prior<t;prior+=basics)y+=scene.tileGrids[prior].at("image_logical_size")[1].get<double>();
            check(near(origin[0],scene.tileGrids[column].at("origin")[0])&&near(origin[1],y),"extended origin accumulates actual source canvas per column");
        }
        const auto passes=source.values("[pass type]");
        std::array<int,3> counts{};
        for(const auto &pass:passes)++counts[pass.get<int>()];
        zero+=counts[0];
        check(grid.at("pass_counts")==Json(counts),"pass counts retain floating-only and blocked cells");
        check(size[0].get<double>()>0&&size[1].get<double>()>0,"transparent and drawable slots retain positive dimensions");
        if(grid.at("transparent").get<bool>()) {
            ++transparent;
            check(grid.at("image")==""&&!grid.at("dimension_policy").get<std::string>().empty(),"empty IMAGE stays transparent with explicit dimension policy");
        } else ++drawable;
        check(pvf.read(source.path)==sourceBefore,"TIL bytes remain unchanged by geometry consumption");
    }
    check(scene.walkRects.size()==zero,"only authored pass0 cells create ground movement");
    check(scene.tiles.size()==drawable&&scene.sourceTileVisuals.size()==drawable,"only authored nonempty IMAGE slots feed renderer and camera");
    for(size_t i=0;i<scene.tiles.size();++i) {
        const auto &tile=scene.tiles[i];const auto &visual=scene.sourceTileVisuals[i];
        const auto pixels=assets.pixels(std::get<0>(tile),std::get<1>(tile));
        check(visual.logical==std::array<double,4>{std::get<2>(tile),std::get<3>(tile),double(pixels.logicalWidth),double(pixels.logicalHeight)}&&
              visual.pixels==std::array<double,4>{std::get<2>(tile)+pixels.x,std::get<3>(tile)+pixels.y,double(pixels.width),double(pixels.height)},
              "logical IMG dimensions and cropped pixels feed existing sourceTileVisual");
    }
    size_t tileCommands=0;
    for(const auto &cmd:sceneDrawCommands(scene,false))if(cmd.kind==MapDrawCommand::Kind::Tile) {
        check(cmd.index==tileCommands++,"existing sceneDrawCommands draws every base and extension once in source order");
    }
    check(tileCommands==drawable,"draw plan retains all nonempty extended tiles");
    check(sceneDrawCommands(scene,true).empty(),"source tiles never enter actor foreground pass");
    World geometry(pvf,assets,WorldRules::BetaFoundationV1);
    geometry.mapWidth=scene.width;geometry.walkRects=scene.walkRects;geometry.blockedRects.clear();
    Json positions=Json::array();
    const auto position=[&](const std::string &kind,double x,double y) {
        if(scene.walkRects.empty()){positions.push_back({{"kind",kind},{"source",{x,y}},{"walk_geometry",false}});return;}
        const auto safe=geometry.nearestWalkable(x,y);
        positions.push_back({{"kind",kind},{"source",{x,y}},{"walkable_at_source",geometry.canWalk(x,y)},
            {"nearest_walkable",safe},{"distance",std::hypot(x-safe[0],y-safe[1])}});
    };
    const auto spawn=scene.script.values("[dungeon start area]");
    if(spawn.size()==4)position("dungeon_start_center",spawn[0].get<double>()+spawn[2].get<double>()/2,
        scene.bg+spawn[1].get<double>()+spawn[3].get<double>()/2);
    const auto gates=scene.script.values("[pathgate pos]");
    for(size_t i=0;i+1<gates.size();i+=2) {
        const auto x=gates[i].get<double>(),y=gates[i+1].get<double>();
        if(x!=0||y!=-120)position("pathgate_"+std::to_string(i/2),x,y+scene.bg);
    }
    check(pvf.read(path)==bytes,"MAP bytes remain unchanged");
    return {{"path",path},{"complete",true},{"count",count},{"width",scene.width},{"background_origin",scene.bg},
        {"base_tiles",basics},{"extended_tiles",extended},{"drawable_tiles",drawable},{"transparent_tiles",transparent},
        {"pass0_walk_cells",zero},{"source_positions",positions},{"diagnostics",loaded.diagnostics}};
}
} // namespace

Json runSceneTileCorpusTests(Pvf &pvf,Assets &assets,const std::vector<std::string> &paths) {
    Json maps=Json::array();size_t count=0,failed=0;
    for(const auto &path:paths) {
        const auto report=checkTileMap(pvf,assets,path);count+=report.at("count").get<size_t>();
        if(!report.at("complete").get<bool>())++failed;
        maps.push_back(report);
        std::cout<<"TIL "<<path<<" "<<(report.at("complete").get<bool>()?"pass":"unresolved")<<std::endl;
    }
    return {{"status",failed?"unresolved":"pass"},{"count",count},{"map_count",maps.size()},{"unresolved",failed},{"maps",maps}};
}

Json runSceneTileTests(Pvf &pvf,Assets &assets) {
    const std::vector<std::string> paths={"map/lorien/s0.map","map/lorien/b1.map","map/elvengard/elvengard.map",
        "map/golemtower/(4,2)2016.map","map/bwanga/(0,0)bwangastart.map","map/cosmofiend/17058_boss.map",
        "map/cartelcommand/15288(4.0).map"};
    auto report=runSceneTileCorpusTests(pvf,assets,paths);
    if(report.at("unresolved")!=0)throw std::runtime_error("Source TIL real-map dependency unresolved: "+report.dump());
    return report;
}

Json runSceneTileRuntimeTests(Pvf &pvf,Assets &assets) {
    size_t count=0,normalBlocked=0,explorationPartial=0;
    const auto check=[&](bool ok,const std::string &name){
        if(!ok)throw std::runtime_error("Scene tile runtime: "+name);
        ++count;
    };
    const std::vector<std::string> paths={"map/lorien/s0.map","map/lorien/b1.map","map/elvengard/elvengard.map",
        "map/golemtower/(4,2)2016.map","map/bwanga/(0,0)bwangastart.map","map/cosmofiend/17058_boss.map",
        "map/cartelcommand/15288(4.0).map"};
    MapAccessCatalog catalog(pvf);RegionCatalog regions(pvf,assets,RegionPreparation::OnDemand);
    World world(pvf,assets,WorldRules::BetaFoundationV1);
    const auto before=world.simulationCheckpoint();
    Json maps=Json::array();
    for(const auto &path:paths) {
        Scene normal;std::string error;
        try{normal.load(pvf,assets,path);}catch(const std::exception &e){error=e.what();++normalBlocked;}
        Scene source;source.path=path;source.script=pvf.script(path);source.bg=int(source.script.number("[background pos]",80));
        const auto receipt=loadSceneSourceTiles(pvf,assets,source);
        check(receipt.complete,"real source tiles complete: "+path);
        check(normal.tileGrids==source.tileGrids&&normal.tiles==source.tiles,"normal Scene::load actually consumes shared base/extended/empty tile service: "+path);
        check(normal.sourceTileVisuals.size()==source.sourceTileVisuals.size(),"normal Scene camera receives all existing visual metadata: "+path);
        const auto indices=catalog.findByPath(path);check(!indices.empty(),"source MAP identity retained: "+path);
        const auto prepared=path=="map/elvengard/elvengard.map"?
            prepareTownMapTraversal(pvf,assets,world,regions,catalog.at(indices.front())):
            prepareMapExploration(pvf,assets,world,regions,catalog.at(indices.front()),true);
        check(prepared.scene.tileGrids==source.tileGrids&&prepared.scene.tiles==source.tiles,
            "test exploration uses identical source tile service and placement: "+path);
        check(normal.width==source.width&&prepared.scene.width>=source.width,
            "normal authored tile width preserved; existing explicit-walk radius padding may extend test simulation width: "+path);
        if(!prepared.complete)++explorationPartial;
        if(prepared.geometryAvailable) {
            World geometry(pvf,assets,WorldRules::BetaFoundationV1);geometry.mapWidth=prepared.scene.width;
            geometry.walkRects=prepared.scene.walkRects;geometry.blockedRects=prepared.scene.blockedRects;
            check(geometry.canWalk(prepared.playerSpawn[0],prepared.playerSpawn[1]),"prepared actual spawn belongs to unexpanded source walk union: "+path);
        }
        maps.push_back({{"path",path},{"normal_load_complete",error.empty()},{"normal_error",error},
            {"test_ok",prepared.ok},{"test_complete",prepared.complete},{"geometry_available",prepared.geometryAvailable},
            {"spawn",prepared.playerSpawn},{"normal_width",normal.width},{"exploration_simulation_width",prepared.scene.width},
            {"test_diagnostics",prepared.diagnostics},
            {"normal_source_tile_issues",normal.issues}});
        std::cout<<"Runtime "<<path<<" normal="<<error.empty()<<" test-complete="<<prepared.complete<<std::endl;
    }
    check(world.simulationCheckpoint()==before,"scene preparation never changes live simulation/RNG/pending state");
    return {{"status","pass"},{"count",count},{"normal_maps_blocked_by_other_dependencies",normalBlocked},
        {"partial_exploration_maps",explorationPartial},{"maps",maps}};
}
} // namespace dnf
