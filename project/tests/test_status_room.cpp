#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/session.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
struct StatusRoomChecks {
    Json checks=Json::array();
    void operator()(bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Status room: ")+message);
        checks.push_back(message);
    }
    template<class Action> bool rejects(Action action) const {
        try {action();} catch(const std::exception &) {return true;}return false;
    }
};
void statusRoomFloor(World &world,bool freeze=true) {
    world.combat=true;world.freezeAi=freeze;world.mapWidth=1200;
    world.walkRects={{0,240,1200,240}};
    world.player.x=world.player.px=560;world.player.y=world.player.py=344;world.player.dir=1;
}
void statusRoomGoblin(World &world,int actorId=1,double x=760) {
    Actor actor;actor.id=actorId;actor.monsterPath="monster/goblin/goblin.mob";
    actor.x=actor.px=x;actor.y=actor.py=344;actor.dir=-1;
    world.initializeMonsterAttributes(actor,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    world.monsters.push_back(std::move(actor));world.synchronizeEntityHandles();
}
// Diagnostic setup only: the real Tau heading source is rolled by StatusHost
// and imported through the public target-restore API. This does not represent
// a Swordman skill, a normal Tau-to-monster contact or a normal combat RNG draw.
Json statusRoomInject(World &world,Pvf &pvf,Actor &target) {
    const auto source=readAttackStatuses(pvf.script("monster/tau/attackinfo/heading.atk"));
    StatusResistanceSnapshot resistance;
    if(&target==&world.player) {
        const auto base=buildCharacterBaseAttributes(world.characterSource(),world.identity(),world.characterLevel,
            CharacterGrowthPolicy::inferredChrGrowthV1());
        resistance=evaluateCharacterStatusResistances(base,world.characterSource(),{},world.normalCharacterLevel());
    } else {
        if(!target.combatAttributes) throw std::runtime_error("Status-room diagnostic target has no frozen source combat attributes");
        resistance=makeMonsterStatusResistances(*target.combatAttributes);
    }
    const auto watermark=world.simulationCheckpoint().at("status_instance_ids");
    const auto attack=world.idSources().attacks.next();
    for(uint64_t seed=0;seed<256;++seed) {
        StatusHost host(pvf.identity(),StunStatusPolicy::inferredFlatChanceStunV1());host.mergeInstanceWatermark(watermark);
        Pcg32 random(seed,17);StatusRequest request;
        request.attacker=world.player.handle;request.attackerLevel=world.characterLevel;
        request.target={target.handle,resistance,false,Json::object()};request.attackInstance=attack;request.attack=source;
        auto prepared=host.prepare(request,uint64_t(world.nowMs()),random);
        if(!prepared.ready()) throw std::runtime_error("Status-room source diagnostic preparation rejected: "+prepared.receipt.dump());
        if(!prepared.receipt.at("outcomes")[0].at("procced").get<bool>()) continue;
        const auto receipt=prepared.receipt;host.publish(std::move(prepared),random);
        auto bundle=host.snapshotTarget(target.handle,uint64_t(world.nowMs()),1);
        bundle["diagnostic_setup"]={{"kind","source-stun-bundle-fixture"},{"local_seed",seed},
            {"source_probability_percent",30},{"normal_skill_execution",false},{"local_random",random.snapshot()},{"receipt",receipt}};
        world.restoreStatusCheckpoint(bundle,target.handle,target.handle,1);return bundle;
    }
    throw std::runtime_error("Status-room fixture could not obtain an authored 30-percent proc in its bounded local seed search");
}
Json statusRoomState(const World &world) {
    Json actors=Json::array(),statuses=Json::array();
    for(const auto &actor:world.monsters) {
        actors.push_back(saveActor(actor,world.nowMs()));
        if(actor.handle) statuses.push_back(world.statusCheckpoint(actor.handle));
    }
    return {{"world",world.snapshot()},{"simulation",world.simulationCheckpoint()},
        {"player",saveActor(world.player,world.nowMs())},{"actors",actors},{"statuses",statuses},
        {"events",world.eventLog()},{"stats",world.statReport()},{"inputs",world.inputs()},
        {"skills",world.skillState().snapshot(world.nowMs())}};
}
int statusRoomAttacks(const World &world) {
    return int(std::count_if(world.events.begin(),world.events.end(),[](const Event &event){return event.kind=="monster_attack";}));
}
} // namespace

Json runStatusRoomTests(Pvf &pvf,Assets &assets) {
    StatusRoomChecks check;Json samples=Json::object();RegionCatalog catalog(pvf,assets);Progression progression(catalog);
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);
        statusRoomFloor(world,false);statusRoomGoblin(world);
        const auto random=world.randomStreams().snapshot();const auto handle=world.monsters[0].handle;
        const auto setup=statusRoomInject(world,pvf,world.monsters[0]);
        check(world.statusStunned(handle) && world.randomStreams().snapshot()==random &&
            setup.at("active")[0].at("source_entry").at("raw_payload")==Json::array({30,0,1000}) &&
            setup.at("diagnostic_setup").at("normal_skill_execution")==false,
            "Explicit diagnostic setup rolls the real authored stun30/level0/1000ms through StatusHost and leaves normal World RNG untouched");
        const auto x=world.monsters[0].x,y=world.monsters[0].y;const auto attacks=statusRoomAttacks(world);
        world.advance(300000000);
        check(world.statusStunned(handle) && world.monsters[0].x==x && world.monsters[0].y==y &&
            statusRoomAttacks(world)==attacks && !world.freezeAi && !world.monsters[0].dead && world.monsters[0].stunUntil==0,
            "Source status pauses an otherwise enabled live goblin AI without relying on hit reaction or global AI freeze");
        world.advance(1000000000);
        check(!world.statusStunned(handle) && world.monsters[0].x<x,
            "Exact status expiry allows the same normal monster AI to resume approaching the player");
        const auto heading=pvf.script("monster/tau/attackinfo/heading.atk");
        check(!readAttackDamage(heading).usable() && readAttackDamage(heading,AttackStatusConsumer::StunHostV1).usable(),
            "The source damage reader admits stun only when the actual status consumer is explicitly registered");
        samples["diagnostic_ai_setup"]=setup;
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.applyEquipment(progression);
        statusRoomFloor(world);statusRoomGoblin(world);
        statusRoomInject(world,pvf,world.monsters[0]);statusRoomInject(world,pvf,world.player);
        const auto playerHandle=world.player.handle,monsterHandle=world.monsters[0].handle;
        const auto monsterStatus=world.statusCheckpoint(monsterHandle);
        const auto random=world.randomStreams().snapshot();
        auto living=saveActor(world.player,world.nowMs());
        auto invalid=living;invalid["dir"]=0;
        const auto beforeInvalid=statusRoomState(world);
        check(check.rejects([&]{restoreSessionPlayer(world,invalid);}) &&
            statusRoomState(world)==beforeInvalid && world.statusStunned(playerHandle),
            "A rejected no-bundle player snapshot preserves the old active stun, contact ledger, actors, inputs and RNG");

        living["x"]=600.0;living["hp"]=world.player.hp-1;
        const auto livingWatermark=world.simulationCheckpoint().at("status_instance_ids");
        restoreSessionPlayer(world,living);
        const auto clearedLiving=world.statusCheckpoint(playerHandle);
        const auto monsterAfterLiving=world.statusCheckpoint(monsterHandle);
        check(!world.statusStunned(playerHandle) && clearedLiving.at("active").empty() &&
            clearedLiving.at("contacts").empty() && clearedLiving.at("sources").empty() &&
            world.player.handle==playerHandle && !world.player.dead && world.player.x==600.0 &&
            world.player.hp==living.at("hp").get<int>() && world.statusStunned(monsterHandle) &&
            monsterAfterLiving.at("active")==monsterStatus.at("active") &&
            monsterAfterLiving.at("contacts")==monsterStatus.at("contacts") &&
            monsterAfterLiving.at("sources")==monsterStatus.at("sources") &&
            world.simulationCheckpoint().at("status_instance_ids")==livingWatermark &&
            world.randomStreams().snapshot()==random,
            "Restoring a living no-bundle player replaces its old status and contacts while preserving another target, RNG and the global ID watermark");

        statusRoomInject(world,pvf,world.player);
        auto dying=saveActor(world.player,world.nowMs());
        dying["dead"]=true;dying["life"]=int(ActorLife::Dying);dying["hp"]=0;dying["animation"]="down";
        const auto deathWatermark=world.simulationCheckpoint().at("status_instance_ids");
        restoreSessionPlayer(world,dying);
        const auto clearedDead=world.statusCheckpoint(playerHandle);
        const auto monsterAfterDeath=world.statusCheckpoint(monsterHandle);
        check(world.player.dead && world.player.life==ActorLife::Dying && world.player.hp==0 &&
            world.player.handle==playerHandle && !world.statusStunned(playerHandle) &&
            clearedDead.at("active").empty() && clearedDead.at("contacts").empty() && clearedDead.at("sources").empty() &&
            world.statusStunned(monsterHandle) && monsterAfterDeath.at("active")==monsterStatus.at("active") &&
            monsterAfterDeath.at("contacts")==monsterStatus.at("contacts") &&
            monsterAfterDeath.at("sources")==monsterStatus.at("sources") &&
            world.simulationCheckpoint().at("status_instance_ids")==deathWatermark &&
            world.randomStreams().snapshot()==random,
            "Restoring a dead no-bundle player cannot inherit its prior live stun or contact ledger and does not clear another target or rewind IDs");
        samples["standalone_living_player_without_status"]=living;
        samples["standalone_dead_player_without_status"]=dying;
    }
    World first(pvf,assets,WorldRules::BetaFoundationV1);first.applyEquipment(progression);
    statusRoomFloor(first);statusRoomGoblin(first,37);
    RegionSession session;session.begin(catalog,1,40121,{},"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");
    check(session.run.rooms.size()>1,"The source dungeon supplies distinct room slots for room-state restoration checks");
    const int roomA=session.run.current;
    const int roomB=roomA==0?1:0;
    const auto originalHandle=first.monsters[0].handle,originalOwner=first.player.handle;
    const auto sourceSetup=statusRoomInject(first,pvf,first.monsters[0]);first.advance(200000000);
    check(first.statusCheckpoint(originalHandle).at("active")[0].at("id")==1,
        "Room A begins with global status instance1 on a diagnostic source monster target");
    session.remember(first);
    const auto roomBundle=session.roomStates.at(roomA)[0].at("status_state");
    check(session.roomStates.at(roomA)[0].at("id")==37 &&
        session.roomStates.at(roomA)[0].at("entity_handle")==originalHandle.json() &&
        roomBundle.at("active")[0].at("remaining_ms")==800,
        "RegionSession remembers the stable room actor slot, its separate entity handle and frozen remaining status milliseconds");
    session.run.current=roomB;first.changeScene();first.monsters.clear();first.synchronizeEntityHandles();
    const auto emptyCheckpoint=first.simulationCheckpoint();
    check(!first.statusStunned(originalHandle) && !static_cast<const World &>(first).resolveActor(originalHandle) &&
        emptyCheckpoint.at("status_instance_ids").at("next")==2 && !emptyCheckpoint.contains("player_status"),
        "Leaving room A clears the live status and retires its handles while the empty room checkpoint retains global next-instance2");
    World resumed(pvf,assets,WorldRules::BetaFoundationV1);resumed.applyEquipment(progression);
    resumed.restoreSimulationCheckpoint(emptyCheckpoint);statusRoomFloor(resumed);
    check(resumed.simulationCheckpoint().at("status_instance_ids").at("next")==2 && resumed.monsters.empty(),
        "A new World restored in empty room B keeps the global watermark even without a player or monster status bundle");
    statusRoomGoblin(resumed,91,820);const auto handleB=resumed.monsters[0].handle;
    statusRoomInject(resumed,pvf,resumed.monsters[0]);
    check(resumed.statusCheckpoint(handleB).at("active")[0].at("id")==2,
        "Room B allocates instance2 after empty-room simulation reload rather than reusing saved room A instance1");
    session.remember(resumed);session.run.current=roomA;
    resumed.changeScene();resumed.monsters.clear();resumed.synchronizeEntityHandles();
    const auto beforeReturnRandom=resumed.randomStreams().snapshot();
    check(session.restore(resumed) && resumed.monsters.size()==1 && resumed.monsters[0].id==37,
        "RegionSession restores the actual saved room A actor instead of treating its entity handle as its room actor ID");
    auto recovered=resumed.monsters[0].handle;const auto recoveredBundle=resumed.statusCheckpoint(recovered);
    check(recovered!=originalHandle && recovered!=handleB && resumed.statusStunned(recovered) &&
        !static_cast<const World &>(resumed).resolveActor(originalHandle) &&
        recoveredBundle.at("active")[0].at("id")==1 && recoveredBundle.at("active")[0].at("remaining_ms")==800 &&
        recoveredBundle.at("active")[0].at("attacker")==originalOwner.json() &&
        resumed.simulationCheckpoint().at("status_instance_ids").at("next")==3 &&
        resumed.randomStreams().snapshot()==beforeReturnRandom,
        "Returning to A explicitly remaps target handles, preserves historical owner and remaining time, and merges instance1 without colliding with B instance2");
    // Keep a different live target active while replacing the monster roster.
    // This also exercises the full merged-host live-target validation callback.
    statusRoomInject(resumed,pvf,resumed.player);
    const auto playerHandle=resumed.player.handle;const auto playerBundle=resumed.statusCheckpoint(playerHandle);
    check(playerBundle.at("active")[0].at("id")==3,"A subsequent independent target allocates global instance3");
    const auto beforeRepeatRandom=resumed.randomStreams().snapshot();
    check(session.restore(resumed),"The same saved room A can restore a second time without a scene reset");
    const auto repeated=resumed.monsters[0].handle;
    check(repeated!=recovered && !static_cast<const World &>(resumed).resolveActor(recovered) &&
        resumed.statusStunned(repeated) && resumed.statusCheckpoint(repeated).at("contacts").size()==1 &&
        resumed.statusCheckpoint(repeated).at("active")[0].at("id")==1 && resumed.statusStunned(playerHandle) &&
        resumed.statusCheckpoint(playerHandle).at("active")[0].at("id")==3 &&
        resumed.simulationCheckpoint().at("status_instance_ids").at("next")==4 &&
        resumed.randomStreams().snapshot()==beforeRepeatRandom,
        "Repeated room restoration retires the previous remapped ledger, preserves the live player's status and never duplicates IDs or random work");
    auto bad=session;const auto sourcePath=std::string("monster/tau/attackinfo/heading.atk");
    bad.roomStates.at(roomA)[0]["status_state"]["sources"][sourcePath]["source"]["member_sha256"]="source-mismatch";
    const auto beforeFailure=statusRoomState(resumed);
    check(check.rejects([&]{bad.restore(resumed);}) && statusRoomState(resumed)==beforeFailure,
        "A room status source mismatch rejects the private actor/registry/host candidate without changing live actors, player, status, RNG or events");
    bad=session;bad.roomStates.at(roomA)[0]["status_state"]["contacts"][0]["identity"]["target"]=playerHandle.json();
    check(check.rejects([&]{bad.restore(resumed);}) && statusRoomState(resumed)==beforeFailure,
        "A foreign target injected into a room bundle cannot be rebound through the monster's legacy room ID");
    // Diagnostic lethal damage checks lifecycle cleanup only. It is separate
    // from normal skill damage and the normal AI contact test in root's suite.
    resumed.diagnosticHit(resumed.monsters[0].id,resumed.monsters[0].hp,0,0,1,{});
    check(resumed.monsters[0].dead && !resumed.statusStunned(repeated) && resumed.statusStunned(playerHandle) &&
        resumed.statusCheckpoint(repeated).at("contacts").size()==1,
        "Diagnostic lethal damage clears the dead monster's active status while retaining its accepted contact until complete entity retirement");
    resumed.monsters[0].life=ActorLife::Removed;resumed.synchronizeEntityHandles();
    check(!static_cast<const World &>(resumed).resolveActor(repeated) &&
        resumed.statusCheckpoint(repeated).at("contacts").empty() && resumed.statusStunned(playerHandle),
        "Explicit complete removal retires the monster handle and ledger without cleansing another live target");
    const auto watermark=resumed.simulationCheckpoint().at("status_instance_ids");resumed.changeScene();
    check(!resumed.statusStunned(playerHandle) && !static_cast<const World &>(resumed).resolveActor(playerHandle) &&
        resumed.statusCheckpoint(resumed.player.handle).at("contacts").empty() &&
        resumed.simulationCheckpoint().at("status_instance_ids")==watermark,
        "Scene change clears remaining active states and contacts, retires old targets and retains the global instance watermark");
    samples["room_a_diagnostic_setup"]=sourceSetup;samples["room_a_saved_bundle"]=roomBundle;
    samples["room_a_remapped_bundle"]=recoveredBundle;samples["empty_room_simulation"]=emptyCheckpoint;
    return {{"status","pass"},{"count",check.checks.size()},{"checks",check.checks},{"samples",samples},
        {"scope","Real source StatusHost diagnostic setup; World AI gate, RegionSession target remap/repeat/source rejection, empty-room reload ID watermark and lifecycle cleanup"},
        {"diagnostic_setup_is_normal_skill_execution",false},{"frontend_and_native_dynamic_comparison","pending user"}};
}
} // namespace dnf
