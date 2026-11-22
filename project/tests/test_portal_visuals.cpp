#include "dnf/portal_visuals.hpp"
#include <stdexcept>

namespace dnf {
Json runPortalVisualTests(Pvf &pvf,Assets &assets) {
    int checks=0;Json traces=Json::array();
    auto check=[&](bool good,const std::string &name){++checks;if(!good)throw std::runtime_error("Portal visuals: "+name);};
    Json sourceTraces=Json::array();
    auto dungeonFromSource=[&](const std::string &path) {
        DungeonDefinition dungeon;dungeon.path=path;dungeon.source=pvf.script(path);
        for(const auto &value:dungeon.source.values("[pathgate object]"))dungeon.pathgateObjects.push_back(value.get<int>());
        return dungeon;
    };
    const auto lorien=dungeonFromSource("dungeon/act1/lorien.dgn");
    const char *directionNames[]={"left","right","up","down"};
    for(int direction=0;direction<4;++direction)for(bool boss:{false,true}) {
        const auto source=resolveDungeonPortalSource(pvf,lorien,Direction(direction),boss);
        const auto expected="passiveobject/mapobject/pathgate/act1/lorien"+std::string(directionNames[direction])+(boss?"boss":"normal")+".obj";
        check(source.available&&source.object==expected,"DGN selected ID binds the actual four-direction registry OBJ");
        check(source.registryMatches.size()==1&&source.dungeonSource.memberPath==lorien.path&&
              source.registrySource.memberPath=="passiveobject/passiveobject.lst"&&
              source.objectSource.memberPath==expected,"DGN/registry/OBJ SourceRefs remain attached");
        sourceTraces.push_back(source.snapshot());
    }
    const auto mixed=dungeonFromSource("dungeon/event/bluemarble/3007.dgn");
    const auto mixedNormal=resolveDungeonPortalSource(pvf,mixed,Direction::Left,false);
    const auto mixedBoss=resolveDungeonPortalSource(pvf,mixed,Direction::Left,true);
    check(mixedNormal.available&&mixedNormal.object=="passiveobject/mapobject/pathgate/act3/gtleftnormal.obj"&&
          mixedBoss.available&&mixedBoss.object=="passiveobject/mapobject/pathgate/act3/behemothleftboss.obj",
          "event DGN mixes distinct normal/boss skins; no filename boss substitution");
    sourceTraces.push_back(mixedNormal.snapshot());sourceTraces.push_back(mixedBoss.snapshot());
    const auto tower=dungeonFromSource("dungeon/towers/ztowerofdespair054.dgn");
    const auto towerNormal=resolveDungeonPortalSource(pvf,tower,Direction::Up,false);
    const auto towerBoss=resolveDungeonPortalSource(pvf,tower,Direction::Up,true);
    check(towerNormal.available&&towerBoss.available&&towerNormal.object==towerBoss.object&&
          towerNormal.object=="passiveobject/mapobject/pathgate/towerofdespair/02upnormal.obj",
          "source boss registration may intentionally use the same UpNormal resource");
    bool towerHasNoVisualPlan=false;
    try {portalVisuals(pvf,towerNormal.object,true);}
    catch(const std::runtime_error &error) {towerHasNoVisualPlan=std::string(error.what()).find("no source visual plan")!=std::string::npos;}
    check(towerHasNoVisualPlan,"tower source UpNormal OBJ only has layer/name; missing visuals are diagnosed without fallback");
    sourceTraces.push_back(towerNormal.snapshot());sourceTraces.push_back(towerBoss.snapshot());
    for(const auto &ids:{std::vector<int>{},std::vector<int>(8,361)}) {
        const auto source=resolveDungeonPortalSource(pvf,ids,Direction::Left,false);
        check(!source.available&&source.object.empty()&&!source.diagnostic.empty(),"unknown layout remains diagnosed without Lorien fallback");
        sourceTraces.push_back(source.snapshot());
    }
    auto invalid=lorien.pathgateObjects;invalid[0]=-1;
    auto source=resolveDungeonPortalSource(pvf,invalid,Direction::Left,false);
    check(!source.available&&source.object.empty()&&source.objectId==-1,"source absent object remains absent");
    invalid[0]=2147483647;source=resolveDungeonPortalSource(pvf,invalid,Direction::Left,false);
    check(!source.available&&source.object.empty()&&source.diagnostic.find("Unregistered")!=std::string::npos,"unknown registry ID remains diagnosed");
    source=resolveDungeonPortalSource(pvf,lorien.pathgateObjects,Direction(7),false);
    check(!source.available&&!source.diagnostic.empty(),"invalid direction remains diagnosed");
    auto altered=lorien;altered.pathgateObjects[0]=364;
    source=resolveDungeonPortalSource(pvf,altered,Direction::Left,false);
    check(!source.available&&source.diagnostic.find("differs")!=std::string::npos,"stale source/model mapping is rejected");
    DungeonPortalSourceCache sourceCache;
    const auto &firstCached=sourceCache.resolve(pvf,lorien,Direction::Left,false);
    const auto &secondCached=sourceCache.resolve(pvf,lorien,Direction::Left,false);
    check(&firstCached==&secondCached&&firstCached.available&&sourceCache.size()==1,
          "repeated source resolution reuses the actual cached result without scanning registry again");
    altered.id=-99;
    const auto &badCached=sourceCache.resolve(pvf,altered,Direction::Left,false);
    const auto &badAgain=sourceCache.resolve(pvf,altered,Direction::Left,false);
    check(&badCached==&badAgain&&!badCached.available&&sourceCache.size()==2,
          "distinct immutable source owner is validated once; failures are cached too");
    sourceCache.resolve(pvf,lorien,Direction::Left,true);
    sourceCache.resolve(pvf,lorien,Direction::Right,false);
    check(sourceCache.size()==4&&sourceCache.snapshot().at("cache_hits")==2,
          "boss/direction source cache keys remain separate");
    for(const auto *direction:{"left","right","up","down"})for(const auto *kind:{"normal","boss"})for(bool open:{false,true}) {
        const auto object="passiveobject/mapobject/pathgate/act1/lorien"+std::string(direction)+kind+".obj";
        const auto plan=portalVisuals(pvf,object,open);
        const auto side=std::string(direction);
        const size_t common=side=="down"?1:side=="up"?2:3;
        check(plan.tracks.size()==common+(open?2:1),"actual current direction/state track count: "+object+
              (open?" open":" closed"));
        bool hasOpen=false,hasClose=false,hasLight=false;
        for(const auto &track:plan.tracks) {
            hasOpen|=track.animation.find("opendoor.ani")!=std::string::npos;
            hasClose|=track.animation.find("closedoor.ani")!=std::string::npos;
            hasLight|=track.animation.find("light.ani")!=std::string::npos;
            check(track.state==0||track.state==(open?2:1),"selected tracks use the same source state rule");
            const auto ani=assets.animation(track.animation);check(!ani->frames.empty(),"selected source ANI exists");
            for(const auto &frame:ani->frames)if(!frame.image.empty()) {
                const auto image=portalImageVariant(frame.image,track.imageVariant);
                check(image.find("%d%d")==std::string::npos&&assets.has(image),"source state/variant binds actual IMG");
                const auto p=assets.pixels(image,frame.imageFrame);check(!p.rgba.empty(),"all selected state IMG frames decode");
            }
        }
        check(hasOpen==open&&hasClose!=open&&hasLight==open,"open renders OpenDoor/Light while closed renders CloseDoor");
        if(std::string(direction)=="left"||std::string(direction)=="right") {
            check(plan.tiles.size()==1&&pvf.has(plan.tiles[0].path),"source door TIL remains preserved without invented collider");
            check(plan.tiles[0].sourcePair[1]==19,"TIL numeric pair is preserved, not interpreted as ANI state");
        } else check(plan.tiles.empty(),"up/down source does not invent a door TIL");
        traces.push_back(plan.snapshot());
    }
    check(portalImageVariant("Map/PathGate/Test%d%d.img",1)=="Map/PathGate/Test01.img"&&
          portalImageVariant("Map/PathGate/Test%d%d.img",5)=="Map/PathGate/Test05.img","source variants format both digits");
    check(portalImageVariant("fixed.img",5)=="fixed.img","untemplated source image unchanged");
    return {{"status","passed"},{"checks",checks},{"traces",traces},{"object_source_traces",sourceTraces},
        {"source_cache",sourceCache.snapshot()},
        {"scope","actual normal/boss four-direction open/closed source plans and resource decode; native dynamic state timing and collision remain separate"}};
}
} // namespace dnf
