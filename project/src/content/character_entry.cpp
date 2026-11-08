#include "dnf/character_entry.hpp"
#include <limits>
#include <queue>
#include <stdexcept>

namespace dnf {
namespace {
int entryInteger(const Json &value,int low,int high,const char *name) {
    if(!value.is_number_integer() || value<low || value>high)
        throw std::invalid_argument(std::string("Invalid character entry ")+name);
    return value.get<int>();
}
}
void CharacterEntryService::index() {
    if(indexed_)return;
    std::set<size_t> rooms;std::map<size_t,std::vector<size_t>> edges;Json evidence=Json::array();
    // Current source registration, not a translated-name search or filename
    // guess. Keep this policy binding in one place with its registry evidence.
    constexpr int roomNpc=2;
    const auto registry=pvf_.script("npc/npc.lst");
    std::vector<std::string> paths;
    for(size_t i=0;i+1<registry.tokens.size();i+=2)
        if(registry.tokens[i].at("value")==roomNpc && registry.tokens[i+1].at("value").is_string())
            paths.push_back(normalize("npc/"+registry.tokens[i+1].at("value").get<std::string>()));
    if(paths.size()!=1 || !pvf_.has(paths.front()))throw std::runtime_error("Login room NPC source registration missing or ambiguous");
    evidence.push_back({{"kind","login_npc_policy_binding"},{"npc",roomNpc},{"path",paths.front()},
        {"registry",makeSourceRef(pvf_,registry.path).json()},{"source",makeSourceRef(pvf_,paths.front()).json()},
        {"classification","current-source-registration-and-user-login-policy"}});
    for(size_t i=0;i<towns_.size();++i) {
        if(!towns_.admitted(i))continue;
        const auto &area=towns_.at(i);const auto map=pvf_.script(area.mapPath);
        Json fields=Json::array();bool hasRoomNpc=false;
        for(const auto &field:map.fields) {
            const auto tag=normalize(field.tag);
            if(tag!="[npc]" && tag!="[town movable area]")continue;
            fields.push_back({{"tag",field.tag},{"offset",field.offset},{"values",field.values}});
            const size_t stride=tag=="[npc]"?5:6;
            if(field.values.size()%stride)continue; // retained and never invented
            for(size_t j=0;j<field.values.size();j+=stride) {
                if(tag=="[npc]")hasRoomNpc=hasRoomNpc || field.values[j]==roomNpc;
                else if(field.values[j+4].is_number_integer() && field.values[j+5].is_number_integer() &&
                        field.values[j+4]>=0 && field.values[j+4]<=std::numeric_limits<int>::max() &&
                        field.values[j+5]>=0 && field.values[j+5]<=std::numeric_limits<int>::max()) {
                    const auto targets=towns_.find(field.values[j+4].get<int>(),field.values[j+5].get<int>());
                    if(targets.size()==1 && towns_.admitted(targets.front()))edges[i].push_back(targets.front());
                }
            }
        }
        const bool room=area.kind=="[gate]" && hasRoomNpc;if(room)rooms.insert(i);
        evidence.push_back({{"kind","source_town_login_graph"},{"area",area.json()},
            {"fields",fields},{"seria_gate",room},{"destinations",edges[i]}});
    }
    if(rooms.empty())throw std::runtime_error("No source-backed Seria gate room available");
    rooms_.swap(rooms);edges_.swap(edges);evidence_=std::move(evidence);indexed_=true;
}
TownLocation CharacterEntryService::roomFor(const TownLocation &where,const std::optional<TownLocation> &previous,Json *trace) {
    index();const auto valid=towns_.validateLocation(where.json());const auto start=towns_.require(valid.townId,valid.areaId);
    std::vector<size_t> candidates;
    for(const auto i:rooms_)if(towns_.at(i).townId==valid.townId)candidates.push_back(i);
    std::string method="same-source-town-seria-gate";std::vector<size_t> path;
    if(candidates.empty()) {
        method="source-map-exits-nearest-town-with-seria-room";
        std::queue<size_t> pending;std::map<size_t,size_t> parent;std::map<size_t,int> distance,roomArrival;
        pending.push(start);distance[start]=0;int foundDistance=-1;
        while(!pending.empty()) {
            const auto current=pending.front();pending.pop();
            if(foundDistance>=0 && distance[current]>foundDistance)break;
            // Select the nearest connected town that owns a room first.
            // Searching for the room door itself can cross another town's
            // boundary merely because its door is geometrically nearer.
            bool linkedTown=false;
            for(const auto room:rooms_)if(towns_.at(room).townId==towns_.at(current).townId) {
                linkedTown=true;foundDistance=distance[current];
                if(std::find(candidates.begin(),candidates.end(),room)==candidates.end()) {
                    candidates.push_back(room);roomArrival[room]=current;
                }
            }
            if(linkedTown)continue;
            for(const auto target:edges_[current])if(!distance.count(target)) {
                distance[target]=distance[current]+1;parent[target]=current;pending.push(target);
            }
        }
        if(candidates.size()==1) {
            auto current=size_t(roomArrival.at(candidates.front()));path.push_back(current);
            while(current!=start){current=parent.at(current);path.push_back(current);}
            std::reverse(path.begin(),path.end());
        }
    }
    if(candidates.size()>1)throw std::runtime_error("Multiple source Seria rooms require an explicit login mapping");
    if(candidates.empty() && previous) {
        const auto home=towns_.validateLocation(previous->json());const auto index=towns_.require(home.townId,home.areaId);
        if(!rooms_.count(index))throw std::runtime_error("Saved login_town is not a source Seria gate room");
        candidates.push_back(index);method="special-area-retains-previous-seria-room";
    }
    if(candidates.empty()) {
        // Explicit legacy migration for snapshots made before login_town
        // existed. No fake connection or native room is assigned to the area.
        const auto initial=towns_.require(1,1);
        if(!rooms_.count(initial))throw std::runtime_error("Legacy login-room migration source is unavailable");
        candidates.push_back(initial);method="legacy-no-source-room-no-home-creation-room-migration";
    }
    auto destination=towns_.location(candidates.front());
    if(previous && previous->townId==destination.townId && previous->areaId==destination.areaId)
        destination.preserved=previous->preserved;
    if(trace)*trace={{"policy","user-region-seria-entry-v1"},{"classification","user_requested_login_policy"},
        {"origin",valid.json()},{"destination",destination.json()},{"resolution",method},{"source_path_indices",path},
        {"special_area_source_room_absent",method=="special-area-retains-previous-seria-room" ||
            method=="legacy-no-source-room-no-home-creation-room-migration"},{"source_evidence",evidence_}};
    return destination;
}
CharacterTownEntry CharacterEntryService::prepare(World &world,const Json &saved) {
    const auto restored=towns_.restoreState(saved);
    std::optional<TownLocation> home;
    if(saved.contains("login_town"))home=towns_.validateLocation(saved.at("login_town"));
    const auto location=saved.value("location",std::string("room"));
    const auto origin=(location=="dungeon" || location=="exploration") && restored.returnAnchor?
        restored.returnAnchor:restored.current?restored.current:restored.returnAnchor;
    if(!origin)throw std::runtime_error("Character entry has no source town or return anchor");
    CharacterTownEntry out;Json resolution;
    const auto destination=roomFor(*origin,home,&resolution);
    out.town=prepareTownArea(pvf_,assets_,world,regions_,towns_,towns_.require(destination.townId,destination.areaId));
    if(!out.town.ok)throw std::runtime_error("Character entry source Seria room preparation failed");
    out.town.location.preserved=destination.preserved;
    if(saved.contains("player")) {
        const auto &player=saved.at("player");
        if(!player.is_object())throw std::invalid_argument("Saved entry player must be an object");
        if(player.contains("hp"))out.hp=entryInteger(player.at("hp"),0,std::numeric_limits<int>::max(),"HP");
        if(player.contains("mp"))out.mp=entryInteger(player.at("mp"),0,std::numeric_limits<int>::max(),"MP");
        if(player.contains("dir")) {
            const auto dir=entryInteger(player.at("dir"),-1,1,"direction");
            if(dir==0)throw std::invalid_argument("Saved entry direction cannot be zero");out.direction=dir;
        }
        if(player.contains("dead") && !player.at("dead").is_boolean())throw std::invalid_argument("Saved entry dead must be boolean");
        const int life=player.contains("life")?entryInteger(player.at("life"),0,int(ActorLife::Removed),"life"):0;
        out.revive=player.value("dead",false) || life!=0 || (out.hp && *out.hp==0);
    }
    out.report={{"status","prepared"},{"policy","user-region-seria-entry-v1"},{"resolution",resolution},
        {"old_location",location},{"discarded_combat_session",saved.contains("run") || saved.contains("exploration_map")},
        {"resource_policy","preserve-living-hp-mp; dead-reentry-minimum-one-hp; clamp-to-source-limits"},
        {"resource_policy_classification","inferred-beta-reentry-no-free-heal"},{"revive",out.revive},
        {"town",out.town.json()},{"legacy_migrations",restored.migrations},
        {"progression_rewards_consumption_rng","restored by CharacterStore without replay or reroll"}};
    return out;
}
void publishCharacterEntry(World &world,Scene &scene,CharacterTownEntry &&entry) {
    if(!entry.town.ok)throw std::invalid_argument("Cannot publish an unprepared character entry");
    if(world.player.maxHp<1 || world.player.maxMp<0)throw std::runtime_error("Source character resource limits unavailable");
    auto walks=entry.town.scene.walkRects,blocks=entry.town.scene.blockedRects;
    const auto spawn=entry.town.spawn;
    world.validateSceneActorCapacity(0);world.changeScene();world.monsters.clear();world.combat=false;
    scene=std::move(entry.town.scene);world.walkRects.swap(walks);world.blockedRects.swap(blocks);world.mapWidth=scene.width;
    Actor next=world.player;
    next.x=next.px=spawn[0];next.y=next.py=spawn[1];next.z=next.pz=next.vx=next.vy=next.vz=0;
    next.hp=entry.revive?1:std::clamp(entry.hp.value_or(next.hp),1,next.maxHp);
    next.mp=std::clamp(entry.mp.value_or(next.mp),0,next.maxMp);if(entry.direction)next.dir=*entry.direction;
    next.dead=false;next.life=ActorLife::Alive;next.animation="stay";next.animationPath.clear();next.animStart=world.nowMs();
    next.poseFrame=-1;next.capturedBy=-1;next.recovery=0;next.attackHit=false;next.attackVariant=next.attackSerial=0;next.nextAttack=0;
    next.deathStart=next.lifeStart=world.nowMs();next.deathPoseTime=0;next.deathDuration=500;next.deathLoop=false;
    next.deathAnchorX=next.x;next.deathAnchorY=next.y;next.deathHeight=0;next.deathMotion.reset();next.deathFragments.clear();
    next.deathProfile={};next.independentDeath=false;next.deathRoute.clear();next.deathBounds={};next.hitFlashUntil=0;
    world.player=std::move(next);world.synchronizeEntityHandles();scene.updateNpcs(world,false);
}
} // namespace dnf
