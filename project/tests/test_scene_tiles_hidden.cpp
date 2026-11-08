#include "dnf/scene_tiles.hpp"
#include "dnf/renderer.hpp"
#include <stdexcept>

namespace dnf {
Json runSceneTileHiddenTests(Pvf &pvf,Assets &assets,Renderer &renderer,const std::filesystem::path &out) {
    size_t count=0;Json maps=Json::array();
    auto check=[&](bool ok,const std::string &message){
        if(!ok)throw std::runtime_error("Scene tiles hidden SDL: "+message);
        ++count;
    };
    for(const auto &path:{"map/lorien/s0.map","map/elvengard/elvengard.map","map/golemtower/(4,2)2016.map",
        "map/bwanga/(0,0)bwangastart.map","map/cosmofiend/17058_boss.map","map/cartelcommand/15288(4.0).map"}) {
        Scene scene;scene.load(pvf,assets,path);
        check(!scene.tileGrids.empty(),std::string("normal Scene::load supplies authored base and extension grids: ")+path);
        // Real normal Scene::load -> existing draw plan -> Scene::draw, with
        // every actual fixed source layer, background, and its original order.
        const auto commands=sceneDrawCommands(scene,false),front=sceneDrawCommands(scene,true);
        size_t tileCommands=0;
        for(const auto &command:commands) {
            if(command.kind==MapDrawCommand::Kind::Tile)++tileCommands;
            else if(scene.layers[command.index].order<=-49)
                check(tileCommands==0,"actual distant/middle source layer draws before the ground");
        }
        check(tileCommands==scene.tiles.size(),"actual draw plan retains every basic and extended source tile");
        for(const auto &command:front)check(command.kind==MapDrawCommand::Kind::Animation&&scene.layers[command.index].order>0,
            "actual foreground fixed ANI remains after actor rendering");
        Json captures=Json::array();
        for(const auto size:{std::array<int,2>{800,600},std::array<int,2>{1280,720}}) {
            renderer.resize(size[0],size[1]);renderer.begin();renderer.viewport(scene);
            const auto cam=sceneCamera(scene,renderer.sceneView,scene.width/2,1000000);
            const auto errorsBefore=renderer.errors.size();
            scene.draw(renderer,0,cam.x,false,cam.y);scene.draw(renderer,0,cam.x,true,cam.y);
            check(renderer.errors.size()==errorsBefore,"existing Scene::draw consumes base/extended source IMG and ANI without new runtime errors");
            const auto name=std::filesystem::u8path(path).parent_path().filename().u8string()+"-"+std::to_string(size[0])+".bmp";
            renderer.screenshot(out/name);renderer.present();
            captures.push_back({{"resolution",size},{"screenshot",name},{"camera",sceneCameraDiagnostics(scene,size[0],size[1],scene.width/2,1000000)}});
        }
        check(scene.tiles.size()==scene.sourceTileVisuals.size(),"hidden drawing leaves source metadata intact");
        maps.push_back({{"path",path},{"tiles",scene.tiles.size()},{"captures",captures}});
    }
    return {{"status","pass"},{"count",count},{"maps",maps},{"renderer_errors",renderer.errors},
        {"visual_parity","user confirmation pending; these are actual hidden SDL consumer captures"}};
}
} // namespace dnf
