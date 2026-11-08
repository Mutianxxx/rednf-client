#include "dnf/character_entry.hpp"
#include "dnf/session.hpp"
#include "dnf/storage.hpp"
#include "dnf/town_source_adapter.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
Json runCharacterEntryTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),routes=Json::array();
    const auto check=[&](bool okay,const std::string &name){if(!okay)throw std::runtime_error("Character entry: "+name);checks.push_back(name);};
    const auto rejects=[](auto action){try{action();}catch(const std::exception&){return true;}return false;};
    TownAccessCatalog towns(pvf);RegionCatalog regions(pvf,assets,RegionPreparation::OnDemand);
    CharacterEntryService service(pvf,assets,regions,towns);
    const auto prior=towns.location(towns.require(2,5));
    const std::map<int,std::pair<int,int>> expected={{1,{1,1}},{2,{2,5}},{3,{3,2}},{4,{4,1}},{5,{5,1}},
        {6,{6,4}},{7,{2,5}},{8,{2,5}},{9,{9,2}},{10,{2,5}},{11,{11,3}},{12,{11,3}},
        {13,{11,3}},{14,{14,3}},{15,{2,5}},{16,{16,3}},{17,{17,0}}};
    for(size_t i=0;i<towns.size();++i)if(towns.admitted(i)) {
        const auto current=towns.location(i);Json trace;
        const auto home=service.roomFor(current,prior,&trace);
        if(pvf.identity()==townMapAliasPackage1031()) {
            const auto target=expected.at(current.townId);
            check(home.townId==target.first && home.areaId==target.second,
                "All source areas resolve correct regional home: "+std::to_string(current.townId)+":"+std::to_string(current.areaId));
        }
        trace.erase("source_evidence");routes.push_back(std::move(trace));
    }
    Json legacyTrace;const auto migrated=service.roomFor(towns.location(towns.require(7,0)),{},&legacyTrace);
    check(migrated.townId==1 && migrated.areaId==1 && legacyTrace.at("special_area_source_room_absent")==true &&
        legacyTrace.at("resolution")=="legacy-no-source-room-no-home-creation-room-migration",
        "Legacy special-area save without a source room or previous home has an explicit diagnosed migration");
    World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
    world.mapWidth=1000;world.walkRects={{0,300,1000,100}};world.player.x=400;world.player.y=330;
    const auto before=world.snapshot(),rngBefore=world.randomStreams().snapshot(),idsBefore=world.idSources().snapshot();
    Json saved={{"location","dungeon"},{"town_location",towns.location(towns.require(3,3)).json()},
        {"return_town",towns.location(towns.require(3,3)).json()},{"login_town",prior.json()},
        {"run",{{"dungeon",2147483647},{"obsolete_resource","must-not-be-prepared"}}},
        {"player",{{"hp",17},{"mp",9},{"dir",-1},{"dead",false},{"life",0},{"x",-99999},{"y",99999},{"z",999}}}};
    auto entry=service.prepare(world,saved);
    check(entry.town.ok && entry.town.location.townId==3 && entry.town.location.areaId==2,
        "Dungeon login uses the regional return anchor and prepares West Coast Seria room without the obsolete dungeon");
    check(world.snapshot()==before && world.randomStreams().snapshot()==rngBefore && world.idSources().snapshot()==idsBefore,
        "Source room and resource preparation preserve live World, RNG and entity IDs");
    auto invalid=saved;invalid["player"]["hp"]=1.5;
    check(rejects([&]{service.prepare(world,invalid);}) && world.snapshot()==before,
        "Malformed saved entry resources reject privately without publishing a new scene");

    const auto stamp=std::chrono::high_resolution_clock::now().time_since_epoch().count();
    const auto directory=std::filesystem::absolute(std::filesystem::path("cache/character-entry-tests")/std::to_string(stamp));
    CharacterStore store(directory,"character-entry-source-test");
    store.data={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    regions.prepareDungeon(1);
    int slot=0;
    for(const int job:{0,1,2,3,4,5,8}) {
        const auto className=std::filesystem::u8path(world.characterCatalog().at(job).registration.path).stem().u8string();
        store.data["characters"][slot]={{"name","Entry fixture"},{"class",className},{"identity",CharacterIdentity{job,0,0}.json()},
            {"level",1},{"weapon",0},{"skill_initialization","source-v1"}};
        Progression progress(regions);store.apply(slot,world,progress);
        progress.state["gold"]=173;progress.state["events"]["entry-consumed-once"]=true;
        progress.state["clears"]["previous-committed-run"]={{"claimed",true}};
        const auto durable=progress.state;
        world.randomStreams().stream(RandomDomain::Loot).next();
        for(const int state:{0,1,2,3,4,5}) {
            world.changeScene();world.combat=true;world.mapWidth=4000;world.walkRects={{0,200,4000,600}};world.blockedRects.clear();
            world.player.x=world.player.px=1200;world.player.y=world.player.py=400;
            world.player.dead=false;world.player.life=ActorLife::Alive;world.player.z=world.player.pz=0;
            world.player.hp=std::max(1,world.player.maxHp/2);world.player.mp=std::min(9,world.player.maxMp);
            if(state==0) {world.enqueue({world.simulationNanoseconds(),4,true});world.advanceSingleTick();}
            if(state==1) {world.player.z=world.player.pz=60;world.player.vz=150;}
            if(state==2) {world.player.stunUntil=world.nowMs()+300;world.player.hitStopTicks=5;world.player.recovery=20;}
            if(state>=3) {world.player.dead=true;world.player.hp=0;world.player.life=ActorLife(state-2);
                world.player.deathStart=world.player.lifeStart=world.nowMs();world.player.animation="damage";}
            const auto hp=world.player.hp,mp=world.player.mp;
            RegionSession run;run.begin(regions,1,uint64_t(4200+job*10+state));
            auto session=run.save(world,"dungeon");
            towns.attachState(session,towns.location(towns.require(3,3)),towns.location(towns.require(3,3)));
            session["login_town"]=prior.json();session["future_session_metadata"]="preserve-original-until-checkpoint";
            store.capture(slot,world,progress);store.data["characters"][slot]["region_session"]=session;
            store.save();const auto diskBefore=readFile(directory/"characters.json");const auto generation=store.generation();
            const auto frozenRng=world.randomStreams().snapshot();
            auto prepared=service.prepare(world,store.data["characters"][slot].at("region_session"));
            store.apply(slot,world,progress);Scene scene;
            publishCharacterEntry(world,scene,std::move(prepared));
            check(scene.path==towns.at(towns.require(3,2)).mapPath && !world.combat && world.monsters.empty() &&
                world.canWalk(world.player.x,world.player.y) && world.player.z==0 && world.player.vz==0 &&
                !world.player.dead && world.player.life==ActorLife::Alive && world.player.animation=="stay",
                "Actual stored character reenters regional room from lifecycle "+std::to_string(state)+" job "+std::to_string(job));
            check(world.player.hp==(state>=3?1:hp) && world.player.mp==mp && world.player.hitStopTicks==0 &&
                world.player.stunUntil==0 && world.player.recovery==0 && world.player.capturedBy==-1 &&
                world.effects.empty() && world.attackVolumes.empty(),
                "Reentry clears actions, motion and damage/death transients without healing living resources");
            check(progress.state==durable && world.randomStreams().snapshot()==frozenRng &&
                store.generation()==generation && readFile(directory/"characters.json")==diskBefore,
                "Reentry preserves committed progression, consumption, rewards, RNG and disk until an explicit checkpoint");
        }
        ++slot;
    }
    // Publish a normal post-entry checkpoint through the real atomic writer.
    Progression progress(regions);store.apply(slot-1,world,progress);
    auto prepared=service.prepare(world,store.data["characters"][slot-1]["region_session"]);
    const auto home=prepared.town.location;Scene scene;publishCharacterEntry(world,scene,std::move(prepared));
    RegionSession cleared;auto session=cleared.save(world,townRuntimeLocation(home));towns.attachState(session,home,home);session["login_town"]=home.json();
    store.capture(slot-1,world,progress);store.data["characters"][slot-1]["region_session"]=session;
    const auto disk=readFile(directory/"characters.json");
    store.setFailureInjector([](SaveFailurePoint point){if(point==SaveFailurePoint::BeforePublish)throw std::runtime_error("entry checkpoint disk fixture");});
    check(rejects([&]{store.save();}) && store.hasPendingCommit() && readFile(directory/"characters.json")==disk,
        "Failed login checkpoint retains old disk generation and the complete frozen retry candidate");
    store.setFailureInjector({});store.retryPending();const auto generation=store.generation();store.close();
    CharacterStore reopened(directory,"character-entry-source-test");
    const auto &post=reopened.data["characters"][slot-1]["region_session"];
    check(reopened.generation()==generation && !post.contains("run") && !post.contains("room_states") &&
        post.at("login_town")==home.json() && post.at("town_location")==home.json(),
        "Disk close/reopen retains Seria home and discards the old dungeon only in the new atomic generation");
    auto again=service.prepare(world,post);check(again.town.location.townId==3 && again.town.location.areaId==2,
        "Repeated login remains in the same regional room without source dungeon preparation or reward replay");
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"routes",routes},
        {"scope","Actual regional source room preparation and CharacterStore/World publication; frontend visual and native reentry resource parity pending"}};
}
} // namespace dnf
