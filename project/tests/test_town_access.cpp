#include "dnf/town_access.hpp"
#include "dnf/town_source_adapter.hpp"
#include "dnf/session.hpp"
#include "dnf/storage.hpp"
#include <chrono>
#include <set>
#include <stdexcept>

namespace dnf {
Json runTownAccessTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),preparations=Json::array(),unresolved=Json::array();
    const auto check=[&](bool okay,const std::string &name){if(!okay)throw std::runtime_error("Town access: "+name);checks.push_back(name);};
    const auto rejects=[](auto action){try{action();}catch(const std::exception &){return true;}return false;};
    TownAccessCatalog towns(pvf);RegionCatalog legacy(pvf,assets);
    const auto snapshot=towns.json();const auto registry=pvf.script("town/town.lst");
    std::set<std::string> townPaths;size_t expectedAreas=0;
    for(size_t i=0;i+1<registry.tokens.size();i+=2) {
        auto path=normalize("town/"+registry.tokens[i+1].at("value").get<std::string>());townPaths.insert(path);
        for(const auto &field:pvf.script(path).fields)if(normalize(field.tag)=="[area]")++expectedAreas;
    }
    check(towns.size()==expectedAreas && snapshot.at("documents").size()==townPaths.size()+1,
        "All registered source TWNs and all repeated area records are represented without city whitelist");
    check(snapshot.at("documents")[0].at("raw_bytes")==registry.rawBytes && snapshot.at("documents")[0].at("tokens")==registry.tokens,
        "Town list retains original decoded bytes and ordered tokens as well as SourceRef");
    if(pvf.identity()==townMapAliasPackage1031())
        check(townPaths.size()==17 && towns.size()==77,"Actual bound 1031 package exposes 17 towns and all 77 source areas");
    check(towns.page("",999999,9).entries.size()>0 && towns.page("",0,9).total==expectedAreas,
        "Town browser pages cover the complete catalog and clamp invalid offsets");
    check(towns.page("hendonmyre").total>0 && towns.page("not-a-source-town-zzzz").total==0,
        "Town browser searches source town and map paths without inventing empty results");

    World live(pvf,assets,WorldRules::BetaFoundationV1);live.tick=120;live.mapWidth=333;
    live.walkRects={{12,900,150,12}};live.blockedRects={{20,900,10,10}};
    live.player.x=101;live.player.y=906;live.randomStreams().stream(RandomDomain::Loot).next();
    live.events.push_back({live.tick,"fixture","town-preparation-live-sentinel"});
    const auto beforeWorld=live.snapshot(),beforeSimulation=live.simulationCheckpoint(),beforeEvents=live.eventLog();
    const auto unchanged=[&]{return live.snapshot()==beforeWorld && live.simulationCheckpoint()==beforeSimulation && live.eventLog()==beforeEvents &&
        live.mapWidth==333 && live.walkRects==std::vector<std::array<double,4>>{{12,900,150,12}} && live.blockedRects==std::vector<std::array<double,4>>{{20,900,10,10}};};
    size_t aliases=0,ready=0,sourceExits=0,resolvedExits=0,dungeonGates=0;
    for(size_t i=0;i<towns.size();++i) {
        const auto &area=towns.at(i);check(towns.admitted(i),"Source town area admitted in normal and test modes: "+std::to_string(area.townId)+":"+std::to_string(area.areaId));
        auto location=towns.location(i);check(towns.validateLocation(location.json()).json()==location.json(),"Source identity is stable: "+area.mapPath);
        if(normalize("map/"+area.mapLiteral)!=area.mapPath)++aliases;
        auto prepared=prepareTownArea(pvf,assets,live,legacy,towns,i);
        auto summary=prepared.json();summary.erase("records");preparations.push_back(summary);
        check(unchanged(),"Town preparation preserves live actors, geometry, time, RNG and events: "+area.mapPath);
        if(prepared.ok) {
            ++ready;
            World projected(pvf,assets,WorldRules::BetaFoundationV1);projected.mapWidth=prepared.scene.width;
            projected.walkRects=prepared.scene.walkRects;projected.blockedRects=prepared.scene.blockedRects;
            check(prepared.scene.path==area.mapPath && prepared.scene.script.rawBytes==pvf.read(area.mapPath) &&
                projected.canWalk(prepared.spawn[0],prepared.spawn[1]),"Town entry uses its own exact MAP and source floor: "+area.mapPath);
            size_t expected=0;for(const auto &field:prepared.scene.script.fields)if(normalize(field.tag)=="[town movable area]")expected+=field.values.size()/6;
            check(prepared.scene.townExits.size()==expected,"Every source town-exit tuple is consumed: "+area.mapPath);
            for(const auto &exit:prepared.scene.townExits) {
                ++sourceExits;const auto navigation=towns.navigate(location,exit);
                if(exit.town>=0 && exit.area>=0 && towns.find(exit.town,exit.area).size()==1) {
                    check(navigation.kind==TownNavigation::Kind::Area && navigation.destination &&
                        towns.at(*navigation.destination).townId==exit.town && towns.at(*navigation.destination).areaId==exit.area,
                        "MAP transition preserves destination town and area identity: "+area.mapPath+" -> "+std::to_string(exit.town)+":"+std::to_string(exit.area));++resolvedExits;
                } else if(exit.town==-1 && exit.area==-1 && area.kind=="[dungeon gate]") {
                    check(navigation.kind==TownNavigation::Kind::DungeonGate && navigation.worldmapId==area.worldmapId &&
                        navigation.worldmapArea==area.worldmapArea && navigation.worldmapPath==area.worldmapPath,
                        "Dungeon sentinel retains its source WDM and optional area without routing to Lorien: "+area.mapPath);++dungeonGates;
                } else {check(!navigation.diagnostics.empty(),"Unsupported source exit has a specific diagnostic: "+area.mapPath);unresolved.push_back({{"area",area.json()},{"exit",exit.raw},{"navigation",navigation.json()}});}
            }
        } else check(!prepared.diagnostics.empty(),"Unavailable town source geometry is explicitly diagnosed without a fake floor: "+area.mapPath);
    }
    check(ready>0 && resolvedExits>0 && dungeonGates>0,"Actual town floor, cross-area navigation and source-bound dungeon gates have consumers");
    if(pvf.identity()==townMapAliasPackage1031()) {
        check(aliases==14,"Exactly 14 verified 1031 aliases retain original literals and source identity");
        check(ready==77 && sourceExits==178 && resolvedExits==137 && dungeonGates==30 && unresolved.size()==11,
            "All 77 bound source town areas prepare; all 137 area exits resolve and all 30 dungeon gates retain identity; 11 guild service entrances diagnose");
    }
    const auto from=towns.location(towns.require(1,0));
    const auto cross=prepareTownArea(pvf,assets,live,legacy,towns,towns.require(2,1),from);
    check(cross.ok && cross.location.townId==2 && cross.location.areaId==1 && unchanged(),
        "Actual Elvengard to HendonMyre source exit prepares the correct town with reciprocal arrival privately");
    const auto failed=prepareTownArea(pvf,assets,live,legacy,towns,towns.size()+100,from);
    check(!failed.ok && unchanged(),"Invalid destination preparation leaves current live scene, random streams and events intact");
    auto stale=from.json();stale["map_source"]["member_sha256"]=std::string(64,'0');
    check(rejects([&]{towns.validateLocation(stale);}) && unchanged(),"Stale source hash is rejected before any town publication");
    auto wrong=from.json();wrong["town_id"]=2;
    check(rejects([&]{towns.validateLocation(wrong);}),"An ID/path mismatch cannot silently restore another town");
    wrong=from.json();wrong["area_id"]=0.5;
    check(rejects([&]{towns.validateLocation(wrong);}),"Fractional saved town identity is refused");
    wrong=from.json();wrong["town_source"]["package_identity"]="foreign";
    check(rejects([&]{towns.validateLocation(wrong);}),"Cross-PVF town identity cannot use the 1031 alias adapter or source snapshot");
    auto badAnchor=from;badAnchor.mapSource.memberSha256=std::string(64,'0');Json unmodified={{"location","town"},{"sentinel","keep"}};
    const auto beforeAttach=unmodified;
    check(rejects([&]{towns.attachState(unmodified,from,badAnchor);}) && unmodified==beforeAttach,
        "Invalid return anchor rejects the entire region metadata candidate without partial attachment");
    for(const auto &old:std::vector<std::pair<std::string,int>>{{"room",1},{"town",0},{"entrance",2}}) {
        const auto migrated=towns.restoreState({{"location",old.first}});
        check(migrated.current && migrated.current->townId==1 && migrated.current->areaId==old.second && !migrated.migrations.empty(),
            "Explicit legacy location migration: "+old.first);
    }
    check(towns.restoreState({{"location","dungeon"}}).returnAnchor->areaId==0,
        "Legacy dungeon without anchor migrates the historically used Elvengard area zero explicitly");
    check(rejects([&]{towns.restoreState({{"location","room"},{"town_location",from.json()}});}),
        "Explicit TownLocation contradicting a legacy room alias is refused");

    const auto stamp=std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto directory=std::filesystem::absolute(std::filesystem::path("cache/town-access-tests")/std::to_string(stamp));
    CharacterStore store(directory,"town-access-same-generation-source-test");
    store.data={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    store.data["characters"][0]={{"name","Town source identity"},{"class","swordman"},{"identity",CharacterIdentity{0,0,0}.json()},
        {"level",1},{"weapon",0},{"skill_initialization","source-v1"}};
    World player(pvf,assets,WorldRules::BetaFoundationV1);Progression progress(legacy);store.apply(0,player,progress);
    RegionSession session;auto current=towns.location(towns.require(2,1));current.preserved["future_town_data"]="keep";
    auto anchor=towns.location(towns.require(3,3));
    player.player.x=654;player.player.y=321;player.randomStreams().stream(RandomDomain::Loot).next();
    auto region=session.save(player,"town");towns.attachState(region,current,anchor);
    store.capture(0,player,progress);store.data["characters"][0]["region_session"]=region;
    const auto savedSimulation=store.data["characters"][0]["simulation"];
    store.save();const auto generation=store.generation();store.close();
    CharacterStore restored(directory,"town-access-same-generation-source-test");
    const auto disk=readFile(directory/"characters.json");const auto &saved=restored.data.at("characters")[0];
    const auto restoredTowns=towns.restoreState(saved.at("region_session"));
    check(restored.generation()==generation && saved.at("simulation")==savedSimulation &&
        restoredTowns.current->json()==current.json() && restoredTowns.returnAnchor->json()==anchor.json() &&
        saved.at("region_session").at("player").at("x")==654 && saved.at("region_session").at("player").at("y")==321,
        "Actual disk reload retains exact current town, return anchor, player position and RNG/simulation in one durable generation");
    World loaded(pvf,assets,WorldRules::BetaFoundationV1);Progression loadedProgress(legacy);
    restored.apply(0,loaded,loadedProgress);RegionSession loadedSession;loadedSession.load(saved.at("region_session"),legacy);
    auto recaptured=loadedSession.save(loaded,"town");towns.attachState(recaptured,restoredTowns.current,restoredTowns.returnAnchor);
    check(recaptured.at("town_location")==current.json() && recaptured.at("return_town")==anchor.json() && readFile(directory/"characters.json")==disk,
        "Source town metadata and unknown fields survive RegionSession/CharacterStore restore without rewriting disk");
    restored.setFailureInjector([](SaveFailurePoint point){if(point==SaveFailurePoint::BeforePublish)throw std::runtime_error("town disk failure fixture");});
    restored.data["characters"][0]["region_session"]["town_location"]=anchor.json();
    check(rejects([&]{restored.save();}) && restored.hasPendingCommit() && readFile(directory/"characters.json")==disk,
        "A failed outer publication retains the old durable town generation and its return anchor");
    restored.setFailureInjector({});restored.retryPending();const auto committed=restored.data.at("characters")[0].at("region_session");
    check(towns.restoreState(committed).current->json()==anchor.json() && towns.restoreState(committed).returnAnchor->json()==anchor.json(),
        "Retry publishes the frozen whole-root town candidate without recapturing location or rerolling source state");
    return {{"status","pass"},{"checks",checks},{"preparations",preparations},{"unresolved_exits",unresolved},
        {"statistics",{{"towns",townPaths.size()},{"areas",towns.size()},{"prepared",ready},{"aliases",aliases},{"source_exits",sourceExits},{"resolved_area_exits",resolvedExits},{"source_dungeon_gates",dungeonGates}}},
        {"scope","All source town traversal/directory and same-generation identity; incomplete NPC/special-world business, UI/feel/audio and original-client parity remain separate"}};
}
} // namespace dnf
