#include "dnf/session.hpp"
#include "dnf/monster_attributes.hpp"
#include <stdexcept>
#include <limits>
namespace dnf {
Json runSessionLayoutTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    auto check=[&](bool value,const char *name){if(!value)throw std::runtime_error(name);checks.push_back(name);};
    auto rejects=[&](auto function,const char *name){bool threw=false;try{function();}catch(const std::exception&){threw=true;}check(threw,name);};
    RegionCatalog catalog(pvf,assets);World world(pvf,assets);
    RegionSession original;original.begin(catalog,1,9801);
    original.run.room().cleared=true;
    const auto snapshot=original.save(world,"dungeon");
    RegionSession restored;
    check(snapshot.at("version")==4&&restored.load(snapshot,catalog)&&restored.run.describe()==original.run.describe(),"Session v4 restores complete selected layout and generation RNG state");
    auto cannotGenerate=catalog;
    // A source-compatible maze still validates the saved subset, while an
    // excessive unused edge list would make the generator reject enumeration.
    // Restoration validates the saved topology directly and draws no RNG.
    auto extra=cannotGenerate.dungeons.at(1).mazes.front();
    extra.width=10;extra.height=10;extra.doorMasks.assign(100,15);
    cannotGenerate.dungeons.at(1).mazes.push_back(extra);
    check(restored.load(snapshot,cannotGenerate)&&restored.run.describe()==original.run.describe()&&
        restored.run.randomState==snapshot["run"]["random_state"],"Layout restoration validates source without generator enumeration and preserves RNG state");
    const auto before=restored.save(world,"dungeon");
    RegionSession sourceRun;
    sourceRun.begin(catalog,1,9801,{},MonsterHpPolicy::inferredMobTableHpV1().id);
    const auto sourceSnapshot=sourceRun.save(world,"dungeon");
    RegionSession sourceRestored;
    check(sourceRestored.load(sourceSnapshot,catalog) &&
          sourceRestored.monsterStatPolicy==MonsterHpPolicy::inferredMobTableHpV1().id &&
          std::any_of(sourceRestored.roomStates.begin(),sourceRestored.roomStates.end(),[](const Json &room){return room.is_null();}),
          "A new source-policy run preserves its monster rule for rooms not visited before save/reload");
    auto legacyPolicy=sourceSnapshot; legacyPolicy.erase("monster_stat_policy");
    check(sourceRestored.load(legacyPolicy,catalog) && sourceRestored.monsterStatPolicy=="legacy-demo-v1",
          "Snapshots lacking monster-stat identity migrate to the historical policy for the whole run");
    const auto retainedPolicy=sourceRestored.save(world,"dungeon");
    auto badPolicy=sourceSnapshot; badPolicy["monster_stat_policy"]="future-unavailable-policy";
    rejects([&]{sourceRestored.load(badPolicy,catalog);},"Unknown saved monster policies reject without substituting a current formula");
    check(sourceRestored.save(world,"dungeon")==retainedPolicy,"A rejected monster-policy restore preserves the active run");
    rejects([&]{sourceRestored.begin(catalog,1,17,{},"future-unavailable-policy");},"Unknown new-run policy rejects before replacing a previous session");
    check(sourceRestored.save(world,"dungeon")==retainedPolicy,"A rejected begin preserves previous run and frozen policy");
    auto corrupt=snapshot;corrupt["run"]["rooms"][0]["path"]="map/another-version.map";
    rejects([&]{restored.load(corrupt,catalog);},"Changed selected MAP path is rejected without reroll");
    check(restored.save(world,"dungeon")==before,"Failed restore leaves prior session intact");
    corrupt=snapshot;corrupt["run"]["rooms"][0]["doors"]=0;
    rejects([&]{restored.load(corrupt,catalog);},"Invalid or dangling room doors are rejected");
    corrupt=snapshot;corrupt["run"]["rooms"][0]["candidates"].push_back(99999999);
    rejects([&]{restored.load(corrupt,catalog);},"Every saved candidate dependency is validated, including unselected candidates");
    corrupt=snapshot;corrupt["version"]=99;
    rejects([&]{restored.load(corrupt,catalog);},"Future session versions cannot be silently downgraded");
    auto unavailable=catalog;unavailable.dungeons.at(1).enabled=false;
    rejects([&]{restored.load(snapshot,unavailable);},"Unavailable saved dungeon is diagnosed instead of silently returned to town");
    auto noSource=catalog;noSource.dungeons.at(1).mazes.clear();
    rejects([&]{restored.load(snapshot,noSource);},"Saved topology requires a compatible source DGN maze without rerolling");
    corrupt=snapshot;corrupt["run"]["token"]="different-reward-ledger";
    rejects([&]{restored.load(corrupt,catalog);},"Run token must agree with preserved dungeon and seed identity");
    for(const char *field:{"version","dungeon","width","height","start","boss","current","seed"}) {
        for(const Json value:{Json(1.5),Json(-1),Json(std::numeric_limits<uint64_t>::max())}) {
            if(std::string(field)=="seed"&&value.is_number_unsigned())continue; // UINT64_MAX is a legal seed.
            corrupt=snapshot;
            if(std::string(field)=="version")corrupt[field]=value;else corrupt["run"][field]=value;
            rejects([&]{restored.load(corrupt,catalog);},("Malformed session integer is rejected before narrowing: "+std::string(field)+"="+value.dump()).c_str());
            check(restored.save(world,"dungeon")==before,"Rejected numeric restore cannot partially mutate a live session");
        }
    }
    for(const char *field:{"x","y","map","doors"})for(const Json value:{Json(0.5),Json(-1),Json(std::numeric_limits<uint64_t>::max())}) {
        corrupt=snapshot;corrupt["run"]["rooms"][0][field]=value;
        rejects([&]{restored.load(corrupt,catalog);},("Malformed room integer is rejected: "+std::string(field)).c_str());
    }
    corrupt=snapshot;corrupt["run"]["rooms"][0]["candidates"][0]=1.5;
    rejects([&]{restored.load(corrupt,catalog);},"Fractional MAP candidates cannot truncate to a registered ID");
    corrupt=snapshot;corrupt["run"]["rooms"][0]["candidates"].push_back(corrupt["run"]["rooms"][0]["candidates"][0]);
    rejects([&]{restored.load(corrupt,catalog);},"Duplicate MAP candidates cannot change source closure weights");
    for(const Json value:{Json::object(),Json::array({42})}) {
        corrupt=snapshot;corrupt["room_states"][0]=value;
        rejects([&]{restored.load(corrupt,catalog);},"Room states must be null or arrays of actor objects");
    }
    auto changedStart=catalog;
    for(auto &maze:changedStart.dungeons.at(1).mazes)maze.starts.clear();
    rejects([&]{restored.load(snapshot,changedStart);},"Preserved entry room must be an authored DGN start coordinate");
    auto changedCandidates=catalog;
    for(auto &maze:changedCandidates.dungeons.at(1).mazes) {
        const auto &room=original.run.rooms.front();const int cell=room.y*maze.width+room.x;
        (room.boss?maze.specifiedBossMaps:maze.specifiedMaps)[cell]={99999999};
    }
    rejects([&]{restored.load(snapshot,changedCandidates);},"Complete saved candidate set must match the cell-specific DGN specification");
    auto unknown=snapshot;
    unknown["future_root"]={{"ordered",Json::array({"a","b","a"})}};
    unknown["run"]["future_run"]=77;
    unknown["run"]["rooms"][0]["future_room"]={{"preserve",true}};
    unknown["player"]["future_player"]=29;
    check(restored.load(unknown,catalog),"Unknown snapshot metadata does not block a known source layout");
    const auto roundTrip=restored.save(world,"dungeon");
    check(roundTrip["future_root"]==unknown["future_root"]&&roundTrip["run"]["future_run"]==77&&
        roundTrip["run"]["rooms"][0]["future_room"]==unknown["run"]["rooms"][0]["future_room"]&&roundTrip["player"]["future_player"]==29,
        "Unknown root, run, room and player metadata survives normal load/save overlays");
    for(const Json version:{Json(5),Json(2.5),Json(-1),Json(std::numeric_limits<uint64_t>::max())}) {
        auto town=Json{{"version",version},{"location","town"}};
        rejects([&]{restored.load(town,catalog);},"Unsupported or malformed town snapshot versions refuse before clearing current session");
        check(restored.save(world,"dungeon")==roundTrip,"Rejected town snapshot preserves the active dungeon");
    }
    auto town=Json{{"version",4},{"location","town"},{"future_town",13}};
    check(!restored.load(town,catalog)&&!restored.active()&&restored.save(world,"town")["future_town"]==13,
        "Known town snapshot clears active dungeon and retains unknown town fields");
    RegionSession legacy;legacy.run=DungeonRun::generate(catalog,1,9801,"legacy-mt19937_64-v1");legacy.roomStates.resize(legacy.run.rooms.size());
    auto old=legacy.save(world,"dungeon");old["version"]=3;
    old["run"].erase("generator_version");old["run"].erase("random_state");
    old["run"].erase("width");old["run"].erase("height");old["run"].erase("token");
    check(restored.load(old,catalog)&&restored.run.generatorVersion=="legacy-mt19937_64-v1"&&restored.run.rooms.size()==legacy.run.rooms.size(),"Schema3 legacy MT layout migrates through its original generator and exact selected-map validation");

    World playerWorld(pvf,assets,WorldRules::BetaFoundationV1);
    playerWorld.applyBaseAttributes(playerWorld.prepareBaseAttributes(playerWorld.identity(),3),AttributeRebuildReason::CharacterRestore);
    playerWorld.tick=120;
    const auto playerHandle=playerWorld.player.handle;
    const auto playerIdentity=playerWorld.identity();
    const int playerId=playerWorld.player.id,playerSourceId=playerWorld.player.sourceId;
    Actor highLevel=playerWorld.player;
    highLevel.id=777;highLevel.sourceId=888;highLevel.monsterPath="monster/untrusted-player-snapshot.mob";
    highLevel.maxHp=highLevel.hp=315;highLevel.maxMp=highLevel.mp=215;
    highLevel.x=410;highLevel.y=270;highLevel.dir=-1;highLevel.z=24;highLevel.vz=80;
    highLevel.animation="attack2";highLevel.animStart=2800;
    const auto highLevelSnapshot=saveActor(highLevel,3000);
    playerWorld.normalAttack();
    playerWorld.enqueue({playerWorld.simulationNanoseconds(),1,true});
    restoreSessionPlayer(playerWorld,highLevelSnapshot);
    check(playerWorld.player.maxHp==270&&playerWorld.player.hp==270&&playerWorld.player.maxMp==190&&playerWorld.player.mp==190&&
          playerWorld.characterLevel==3&&playerWorld.player.x==410&&playerWorld.player.y==270&&playerWorld.player.dir==-1,
          "Session restore clamps a level-4 315/215 snapshot to current normal-level source limits 270/190");
    check(playerWorld.player.handle==playerHandle&&playerWorld.identity()==playerIdentity&&playerWorld.player.id==playerId&&
          playerWorld.player.sourceId==playerSourceId&&playerWorld.player.monsterPath.empty()&&playerWorld.resolveActor(playerHandle)==&playerWorld.player,
          "Player restore preserves the current registry handle, player identity and source ownership rather than copying snapshot authority");
    check(playerWorld.activeSkill()<0&&playerWorld.player.animation=="stay"&&playerWorld.player.animStart==playerWorld.nowMs()&&
          playerWorld.player.z==0&&playerWorld.player.vz==0&&playerWorld.player.poseFrame==-1&&
          playerWorld.simulationCheckpoint().at("inputs").at("pending").empty(),
          "Living session restore cancels short actions, airborne controller state and pending input instead of replaying an old attack");
    auto resourceLoss=highLevelSnapshot;resourceLoss["hp"]=153;resourceLoss["mp"]=29;
    restoreSessionPlayer(playerWorld,resourceLoss);
    check(playerWorld.player.hp==153&&playerWorld.player.mp==29,
          "Normal session recovery retains current resource loss rather than healing to source maxima");

    Actor dying=highLevel;
    dying.dead=true;dying.life=ActorLife::DeathEffect;dying.hp=23;dying.z=dying.vz=0;
    dying.animation="down";dying.animationPath.clear();dying.animStart=1900;
    dying.deathStart=2000;dying.lifeStart=2200;dying.deathPoseTime=47;
    const auto deathSnapshot=saveActor(dying,2500);
    restoreSessionPlayer(playerWorld,deathSnapshot);
    const auto rebased=saveActor(playerWorld.player,playerWorld.nowMs());
    check(playerWorld.player.dead&&playerWorld.player.hp==0&&playerWorld.player.life==ActorLife::DeathEffect&&
          rebased.at("death_age")==deathSnapshot.at("death_age")&&rebased.at("life_age")==deathSnapshot.at("life_age")&&
          rebased.at("anim_age")==deathSnapshot.at("anim_age")&&rebased.at("death_pose_time")==47&&playerWorld.player.animation=="down",
          "Dead player recovery forces HP zero and preserves death, phase and animation ages across different simulation clocks");
    check(playerWorld.player.handle==playerHandle&&playerWorld.player.maxHp==270&&playerWorld.player.maxMp==190,
          "Death restoration also retains current entity generation and source resource limits");
    auto flagOnlyDeath=deathSnapshot;flagOnlyDeath["life"]=int(ActorLife::Alive);flagOnlyDeath["hp"]=200;
    restoreSessionPlayer(playerWorld,flagOnlyDeath);
    check(playerWorld.player.dead&&playerWorld.player.hp==0&&playerWorld.player.life==ActorLife::Dying&&
          playerWorld.nowMs()-playerWorld.player.deathStart==deathSnapshot.at("death_age"),
          "A legacy dead flag with an Alive phase becomes Dying without restarting its saved death age");
    auto phaseOnlyDeath=deathSnapshot;phaseOnlyDeath["dead"]=false;phaseOnlyDeath["hp"]=200;
    restoreSessionPlayer(playerWorld,phaseOnlyDeath);
    check(playerWorld.player.dead&&playerWorld.player.hp==0&&playerWorld.player.life==ActorLife::DeathEffect,
          "A non-Alive saved phase cannot restore positive HP or permit normal input even when the dead flag is false");

    const auto liveBeforeInvalid=playerWorld.snapshot(),actorBeforeInvalid=saveActor(playerWorld.player,playerWorld.nowMs());
    const auto simulationBeforeInvalid=playerWorld.simulationCheckpoint(),eventsBeforeInvalid=playerWorld.eventLog();
    auto checkPlayerFailure=[&](const Json &bad,const char *name){
        rejects([&]{restoreSessionPlayer(playerWorld,bad);},name);
        check(playerWorld.snapshot()==liveBeforeInvalid&&saveActor(playerWorld.player,playerWorld.nowMs())==actorBeforeInvalid&&
              playerWorld.simulationCheckpoint()==simulationBeforeInvalid&&playerWorld.eventLog()==eventsBeforeInvalid,
              "Malformed player decode leaves live actor, controller, handles, events and simulation checkpoint untouched");
    };
    auto badPlayer=deathSnapshot;badPlayer["x"]="invalid";
    checkPlayerFailure(badPlayer,"Player scalar decode failure is staged before live publication");
    badPlayer=deathSnapshot;badPlayer["death_anchor"]=Json::array({0,1});
    checkPlayerFailure(badPlayer,"Late player death-payload decode failure cannot partly restore position or HP");
    for(const char *key:{"x","y","z","vx","vy","vz"}) {
        badPlayer=deathSnapshot;badPlayer[key]=std::numeric_limits<double>::infinity();
        checkPlayerFailure(badPlayer,"Nonfinite saved player position or motion is rejected before publication");
    }
    for(const char *key:{"anim_age","death_age","life_age","death_pose_time","stun_remaining","next_attack"}) {
        for(const Json value:{Json(-1),Json(0.5),Json(std::numeric_limits<uint64_t>::max()),Json(std::numeric_limits<int64_t>::max())}) {
            badPlayer=deathSnapshot;badPlayer[key]=value;
            checkPlayerFailure(badPlayer,"Saved player clocks reject negative, fractional and overflowing ages/deadlines before arithmetic");
        }
    }
    for(const char *key:{"hp","mp","dir","life"}) {
        badPlayer=deathSnapshot;badPlayer[key]=std::numeric_limits<uint64_t>::max();
        checkPlayerFailure(badPlayer,"Oversized saved player integers cannot narrow into valid resources, direction or lifecycle");
    }
    badPlayer=deathSnapshot;badPlayer["dir"]=0;
    checkPlayerFailure(badPlayer,"Saved player direction must remain one of the two supported facing values");
    badPlayer=deathSnapshot;badPlayer["life"]=4;
    checkPlayerFailure(badPlayer,"Unknown saved player lifecycle cannot clamp into a supported phase");
    badPlayer=deathSnapshot;badPlayer["life_age"]=501;
    checkPlayerFailure(badPlayer,"A death phase cannot begin before the saved death event");

    // The restored effect is 300 ms old. Keep the first tick below its 320 ms
    // boundary and let the next one complete it, rather than replaying death.
    playerWorld.advance(16666667);
    check(playerWorld.player.life==ActorLife::DeathEffect&&playerWorld.nowMs()-playerWorld.player.lifeStart==316,
          "The first resumed death tick advances the saved phase age instead of restarting it");
    playerWorld.advance(16666667);
    check(playerWorld.player.life==ActorLife::Removed&&playerWorld.player.hp==0,
          "A restored death phase reaches its original removal boundary without an extra death replay");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},
            {"scope","Selected layout persistence, source-limit player restore and death clocks; continuous skill/entity graph restoration remains incomplete"}};
}
}
