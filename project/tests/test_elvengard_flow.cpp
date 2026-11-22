#include "dnf/scene.hpp"
#include "dnf/combat.hpp"
#include "dnf/region.hpp"
#include "dnf/progression.hpp"
#include <cmath>
#include <stdexcept>
namespace dnf {
Json runElvengardFlowTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto require = [&](bool ok, const char *message) {
        if (!ok) throw std::runtime_error(std::string("Elvengard flow: ") + message);
        checks.push_back(message);
    };
    RegionCatalog catalog(pvf, assets);
    const auto roomArea = catalog.townArea(1);
    require(roomArea && roomArea->path == "map/elvengard/gate.map" &&
        !pvf.has(roomArea->path) && roomArea->resolvedPath == "map/elvengard/(r)gate.map" &&
        roomArea->spawnX == 474 && roomArea->spawnY == 234,
        "Original missing TWN gate path and explicit existing-client alias preserved with source spawn");
    require(catalog.npcs.at(22).name=="金库" && !catalog.npcs.at(22).unavailableReason.empty() &&
        !catalog.npcs.at(32).unavailableReason.empty() && !catalog.shops.at(57).enabled &&
        !catalog.shops.at(68).enabled && catalog.shops.at(2).enabled && catalog.shops.at(15).enabled && catalog.shops.at(1000).enabled,
        "Storage/mail/event services are explicitly unavailable while regional normal merchants remain enabled");
    Progression progress(catalog); progress.state["gold"]=1000000; const auto beforeShop=progress.state;
    require(!progress.buy(57,catalog.shops.at(57).items.empty()?0:catalog.shops.at(57).items.front()).ok &&
        progress.state==beforeShop, "Unavailable activity merchants reject purchases without charging gold or granting items");
    Scene scene;
    World world(pvf, assets);
    auto load = [&](const std::string &path) {
        scene.load(pvf, assets, path); world.mapWidth = scene.width;
        world.walkRects = scene.walkRects; world.blockedRects = scene.blockedRects;
    };
    load(roomArea->resolvedPath);
    const auto roomExit = scene.townExitAt(474, 415);
    require(scene.townExits.size() == 2 && roomExit && roomExit->town == 1 && roomExit->area == 0 &&
        roomExit->raw == Json::array({330,324,289,24,1,0}) && !scene.townExitAt(320,415) &&
        !scene.townExitAt(474,390), "Seria exit uses the full source rectangle with MAP Y origin, not a global Y threshold");
    require(world.canWalk(roomArea->spawnX,roomArea->spawnY+scene.bg), "Source TWN room spawn lies on walkable ground");
    const auto seria = std::find_if(scene.npcs.begin(),scene.npcs.end(),[](const auto &n){ return n.id==2; });
    require(seria!=scene.npcs.end() && seria->name == "赛丽亚" && seria->visible &&
        std::abs(seria->x-roomArea->spawnX)+std::abs(seria->y-roomArea->spawnY-scene.bg)<180,
        "Source field name and Seria interaction range from source spawn");
    const auto storage = std::find_if(scene.npcs.begin(),scene.npcs.end(),[](const auto &n){ return n.id==22; });
    require(storage!=scene.npcs.end() && storage->name=="金库", "Storage dynamic field-name ANI is never displayed as literal UI text");
    load(catalog.townArea(0)->resolvedPath);
    const auto toRoom = scene.townExitAt(785,240), toEntrance = scene.townExitAt(1547,340);
    require(scene.townExits.size()==4 && toRoom && toRoom->town==1 && toRoom->area==1 &&
        toEntrance && toEntrance->town==1 && toEntrance->area==2 &&
        !scene.townExitAt(785,280) && !scene.townExitAt(1547,250),
        "Elvengard source doorway bounds and destination area identities");
    for (int fromArea : {1,2}) {
        const auto point = scene.townArrivalFrom(1,fromArea);
        if (!world.canWalk(point[0],point[1]) || scene.townExitAt(point[0],point[1]))
            throw std::runtime_error("Elvengard reciprocal arrival re-enters a portal or misses ground");
    }
    checks.push_back("Reciprocal room/entrance arrivals lie on ground outside transition rectangles");
    const auto linus = std::find_if(scene.npcs.begin(),scene.npcs.end(),[](const auto &n){ return n.id==1; });
    require(linus!=scene.npcs.end() && linus->name=="铁匠·林纳斯", "Source Linus field identity retained independently from dialogue name");
    load(catalog.townArea(2)->resolvedPath);
    const auto choose = scene.townExitAt(872,340), back = scene.townExitAt(12,340);
    require(choose && choose->town==-1 && choose->area==-1 && back && back->town==1 && back->area==0 &&
        !scene.townExitAt(830,340) && !scene.townExitAt(872,410),
        "Dungeon selection is confined to original entry rectangle, with original return exit");
    const auto entry = scene.townArrivalFrom(1,0);
    require(world.canWalk(entry[0],entry[1]) && !scene.townExitAt(entry[0],entry[1]), "Entrance reciprocal arrival cannot immediately bounce back");
    Json portals = Json::array();
    for (const auto &[id,map] : catalog.maps) {
        if (map.special) continue;
        load(map.path);
        const auto gates=scene.script.values("[pathgate pos]");
        for (int d=0;d<4;++d) if (map.allowedDoors&directionBit(Direction(d))) {
            if (gates.size()<size_t(d*2+2)) throw std::runtime_error("Missing source gate position: "+map.path);
            const double x=gates[d*2], y=gates[d*2+1].get<double>()+scene.bg;
            const auto point=world.nearestWalkable(x,y);
            if (!world.canWalk(point[0],point[1]) || std::abs(point[0]-x)>=28 || std::abs(point[1]-y)>=32)
                throw std::runtime_error("Source gate cannot be reached within transition bounds: "+map.path+" direction "+std::to_string(d));
            portals.push_back({{"map",id},{"direction",d},{"source",{x,y}},{"walkable",point}});
        }
    }
    checks.push_back("Every allowed door in all ordinary Lorien/Lorien Inside MAP candidates has reachable trigger ground");
    load("map/lorien/b1.map");
    world.player.x=400; world.player.y=344; world.player.dir=1; world.monsters.clear();
    Actor boss; boss.boss=true;boss.dead=true;boss.x=600;boss.y=344;world.monsters.push_back(boss);
    scene.updateNpcs(world,false);
    require(scene.npcs.size()==1 && !scene.npcs[0].visible && scene.npcs[0].sourcePosition==std::array<double,3>{0,0,0},
        "Clear merchant remains hidden before dungeon completion and retains placeholder source coordinates");
    scene.updateNpcs(world,true);
    const auto merchant=scene.npcs[0];
    require(merchant.visible && merchant.generatedPlacement && world.canWalk(merchant.x,merchant.y) &&
        catalog.npcs.at(merchant.id).shop==1000,
        "Dungeon completion generates an interactable merchant on safe ground with original shop identity");
    world.player.x=1000;scene.updateNpcs(world,true);
    require(scene.npcs[0].x==merchant.x && scene.npcs[0].y==merchant.y,
        "Merchant placement is stable while player moves and is independent of rendering");
    scene.updateNpcs(world,false);
    require(!scene.npcs[0].visible,"Clear-only merchant cannot remain visible when clear condition is absent");
    return {{"status","pass"},{"checks",checks},{"door_samples",portals},
        {"scope","Core source transitions/NPC lifecycle; actual screen/input checks separate"}};
}
} // namespace dnf
