#include "dnf/combat.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <chrono>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
struct RestoreHandleChecks {
    Json checks=Json::array();
    void operator()(bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Restore handles: ")+message);
        checks.push_back(message);
    }
    template<class Action> bool rejects(Action action) const {
        try {action();} catch(const std::exception &) {return true;}return false;
    }
};
std::vector<EntityHandle> liveHandles(const World &world) {
    std::vector<EntityHandle> handles{world.player.handle};
    for(const auto &actor:world.monsters) if(actor.life!=ActorLife::Removed) handles.push_back(actor.handle);
    return handles;
}
bool stale(const World &world,const std::vector<EntityHandle> &handles) {
    return std::all_of(handles.begin(),handles.end(),[&](EntityHandle h){return !world.resolveActor(h);});
}
bool attached(const World &world) {
    if(world.resolveActor(world.player.handle)!=&world.player) return false;
    for(const auto &actor:world.monsters)
        if(actor.life!=ActorLife::Removed && world.resolveActor(actor.handle)!=&actor) return false;
    return true;
}
Json deterministicSimulation(Json checkpoint) {
    // Entity identity is deliberately fresh after a successful restore. The
    // existing policy also cancels pending key edges, retaining their sequence.
    Json result=Json::object();
    for(const char *key:{"schema","clock","ids","effects","inputs","random","restore_policy","status_instance_ids"})
        if(checkpoint.contains(key)) result[key]=checkpoint.at(key);
    result["inputs"]["pending"]=Json::array();
    return result;
}
Json liveState(const World &world) {
    return {{"world",world.snapshot()},{"simulation",world.simulationCheckpoint()},
        {"events",world.eventLog()},{"inputs",world.inputs()},
        {"skills",world.skillState().snapshot(world.nowMs())},{"attack_volumes",world.attackVolumes.size()}};
}
void markerState(World &world) {
    // Explicit diagnostic sentinels for rejected-restore atomicity. These are
    // not normal skill, particle or collision execution claims.
    Effect effect;effect.id=701;effect.phase="restore-rejection-sentinel";
    world.effects.push_back(effect);world.attackVolumes.push_back(AttackVolume{});
    world.enqueue({world.simulationNanoseconds()+1000000000,1,true});
    world.randomStreams().stream(RandomDomain::Loot).next();
    world.player.hp=std::max(1,world.player.maxHp-9);world.player.stunUntil=world.nowMs()+321;
}
void appendActors(World &world) {
    // A dead actor still requires an identity; a Removed actor must not be
    // resurrected or consume replacement capacity.
    Actor alive;alive.id=37;
    Actor dying;dying.id=38;dying.dead=true;dying.hp=0;dying.life=ActorLife::Dying;
    Actor removed;removed.id=39;removed.dead=true;removed.hp=0;removed.life=ActorLife::Removed;
    world.monsters={alive,dying,removed};world.synchronizeEntityHandles();
}
Json checkpointAtNext(Json checkpoint,uint64_t next) {
    checkpoint["entities"]["ids"]["next"]=next;
    checkpoint["entities"]["entries"]=Json::array();
    return checkpoint;
}
Json sourceStun(World &world,Pvf &pvf) {
    // Diagnostic source-bundle injection, using the real authored 30-percent
    // Tau stun and a local RNG. It does not establish a normal skill chain.
    const auto source=readAttackStatuses(pvf.script("monster/tau/attackinfo/heading.atk"));
    const auto base=buildCharacterBaseAttributes(world.characterSource(),world.identity(),world.characterLevel,
        CharacterGrowthPolicy::inferredChrGrowthV1());
    const auto resistance=evaluateCharacterStatusResistances(base,world.characterSource(),{},world.characterLevel);
    for(uint64_t seed=0;seed<256;++seed) {
        StatusHost host(pvf.identity(),StunStatusPolicy::inferredFlatChanceStunV1());Pcg32 random(seed,17);
        StatusRequest request;request.attacker=world.player.handle;request.attackerLevel=world.characterLevel;
        request.target={world.player.handle,resistance,false,Json::object()};request.attackInstance=91;request.attack=source;
        auto prepared=host.prepare(request,uint64_t(world.nowMs()),random);
        if(!prepared.ready()) throw std::runtime_error("Restore-handle diagnostic source rejected: "+prepared.receipt.dump());
        if(!prepared.receipt.at("outcomes")[0].at("procced").get<bool>()) continue;
        host.publish(std::move(prepared),random);
        auto bundle=host.snapshotTarget(world.player.handle,uint64_t(world.nowMs()),1);
        world.restoreStatusCheckpoint(bundle,world.player.handle,world.player.handle,1);
        return bundle;
    }
    throw std::runtime_error("Restore-handle diagnostic source did not proc in its bounded local-seed search");
}
} // namespace

Json runRestoreHandleTests(Pvf &pvf,Assets &assets) {
    RestoreHandleChecks check;Json samples=Json::object();
    World source(pvf,assets);source.freezeAi=true;
    source.advance(500000001,8);source.enqueue({1000000000,1,true});
    source.idSources().actions.next();source.idSources().attacks.next();source.idSources().events.next();
    source.randomStreams().stream(RandomDomain::Loot).next();
    source.randomStreams().stream(RandomDomain::Combat,11).next();
    const auto checkpoint=source.simulationCheckpoint();const auto frozen=checkpoint.dump();
    const auto simulation=deterministicSimulation(checkpoint);
    {
        World world(pvf,assets);world.freezeAi=true;appendActors(world);
        std::vector<EntityHandle> previous=liveHandles(world);
        for(int attempt=0;attempt<3;++attempt) {
            const auto issuedNext=world.simulationCheckpoint().at("entities").at("ids").at("next").get<uint64_t>();
            world.restoreSimulationCheckpoint(checkpoint);const auto current=liveHandles(world);
            check(attached(world) && stale(world,previous) &&
                std::all_of(current.begin(),current.end(),[&](EntityHandle h){return h.id>=issuedNext;}),
                "Repeated restoration into the same live World gives every surviving actor a fresh identity beyond all earlier allocations");
            check(world.monsters.size()==3 && world.monsters[1].life==ActorLife::Dying && !world.monsters[2].handle &&
                deterministicSimulation(world.simulationCheckpoint())==simulation && world.effects.empty() && world.activeSkill()<0,
                "Fresh incarnations preserve same-generation clock, backlog, RNG, command watermarks and the declared cancellation policy");
            previous.insert(previous.end(),current.begin(),current.end());
        }
        check(checkpoint.dump()==frozen,"A restore never rewrites the frozen input checkpoint to manufacture a new save generation");
    }
    {
        World world(pvf,assets);std::vector<EntityHandle> history{world.player.handle};
        for(int i=0;i<5;++i){world.changeScene();history.push_back(world.player.handle);}
        const auto liveNext=world.simulationCheckpoint().at("entities").at("ids").at("next").get<uint64_t>();
        world.restoreSimulationCheckpoint(checkpoint);
        check(stale(world,history) && world.player.handle.id>=liveNext && attached(world),
            "An older saved registry cannot rewind a destination World's newer player incarnation history");
        markerState(world);const auto before=liveState(world);auto malformed=checkpoint;
        malformed["random"]["algorithm"]="corrupt";
        check(check.rejects([&]{world.restoreSimulationCheckpoint(malformed);}) && liveState(world)==before,
            "Malformed restoration rejects before clearing effects, pending input, actors, status, random state or identity history");
    }
    {
        World world(pvf,assets);appendActors(world);markerState(world);const auto before=liveState(world);
        const auto insufficient=checkpointAtNext(checkpoint,UINT64_MAX-1);
        check(check.rejects([&]{world.restoreSimulationCheckpoint(insufficient);}) && liveState(world)==before,
            "All surviving monster identities are preallocated privately so a roster larger than remaining capacity leaves the live World unchanged");
        world.restoreSimulationCheckpoint(checkpointAtNext(checkpoint,UINT64_MAX-2));
        check(world.player.handle.id==UINT64_MAX-2 && world.monsters[0].handle.id==UINT64_MAX-1 &&
            world.monsters[1].handle.id==UINT64_MAX && !world.monsters[2].handle && attached(world) &&
            world.simulationCheckpoint().at("entities").at("ids").at("next")==0,
            "The final three identities fit exactly for a player, a live monster and a dying monster while Removed actors consume none");
        markerState(world);const auto exhausted=liveState(world);
        check(check.rejects([&]{world.restoreSimulationCheckpoint(checkpoint);}) && liveState(world)==exhausted,
            "An exhausted live allocator cannot be revived by restoring an older nonexhausted checkpoint");
        check(check.rejects([&]{world.changeScene();}) && liveState(world)==exhausted &&
            check.rejects([&]{world.selectCharacter(world.identity());}) && liveState(world)==exhausted,
            "Scene and character changes reject identity exhaustion before cancelling or mutating the live scene");
    }
    {
        World world(pvf,assets);Actor monster;monster.id=82;world.monsters.push_back(monster);world.synchronizeEntityHandles();
        const auto lastTwo=checkpointAtNext(checkpoint,UINT64_MAX-1);world.restoreSimulationCheckpoint(lastTwo);
        check(world.player.handle.id==UINT64_MAX-1 && world.monsters[0].handle.id==UINT64_MAX && attached(world),
            "A public World restore can consume exactly the final two entity IDs without hidden intermediate allocations");
        markerState(world);const auto before=liveState(world);
        check(check.rejects([&]{world.restoreSimulationCheckpoint(lastTwo);}) && liveState(world)==before,
            "Repeating a near-limit checkpoint rejects permanently exhausted identity history without partial cleanup");
    }
    {
        World world(pvf,assets);const auto original=world.player.handle;const auto random=world.randomStreams().snapshot();
        const auto bundle=sourceStun(world,pvf);const auto saved=world.simulationCheckpoint();
        std::vector<EntityHandle> old{original};Json targets=Json::array();
        for(int i=0;i<3;++i) {
            world.restoreSimulationCheckpoint(saved);const auto current=world.player.handle;
            const auto remapped=world.statusCheckpoint(current);
            check(stale(world,old) && world.statusStunned(current) && world.randomStreams().snapshot()==random &&
                remapped.at("active")[0].at("id")==bundle.at("active")[0].at("id") &&
                remapped.at("active")[0].at("attacker")==original.json() &&
                remapped.at("active")[0].at("remaining_ms")==bundle.at("active")[0].at("remaining_ms") &&
                remapped.at("active")[0].at("target")==current.json(),
                "Each repeated restore explicitly remaps source status to a new target while retaining historical attacker, status ID, duration and RNG");
            old.push_back(current);targets.push_back(current.json());
        }
        samples["diagnostic_status_targets"]=targets;
    }
    {
        const auto path=std::filesystem::absolute(std::filesystem::path("cache/restore-handle-test-saves")/
            std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
        CharacterStore store(path,"restore-handle-test-content");
        store.data["characters"][0]={{"name","Restore handles"},{"class","swordman"},{"identity",CharacterIdentity{}.json()},
            {"future_saved_field",{{"preserved",true}}},{"progression",{{"reward_receipt","already-claimed"}}}};
        store.capture(0,source);store.commit("restore-identity-baseline");
        const auto data=store.data;const auto bytes=readFile(path/"characters.json");const auto generation=store.generation();
        World world(pvf,assets);std::vector<EntityHandle> previous{world.player.handle};
        for(int attempt=0;attempt<3;++attempt) {
            store.apply(0,world);
            check(stale(world,previous) && attached(world) && world.randomStreams().snapshot()==checkpoint.at("random") &&
                deterministicSimulation(world.simulationCheckpoint())==simulation && store.data==data &&
                store.generation()==generation && readFile(path/"characters.json")==bytes,
                "Repeated CharacterStore apply changes only the live incarnation while preserving durable generation, bytes, custom fields and saved simulation streams");
            previous.push_back(world.player.handle);
        }
        World oneLeft(pvf,assets);oneLeft.restoreSimulationCheckpoint(checkpointAtNext(checkpoint,UINT64_MAX-1));
        markerState(oneLeft);const auto before=liveState(oneLeft);
        check(check.rejects([&]{store.apply(0,oneLeft);}) && liveState(oneLeft)==before && store.data==data &&
            store.generation()==generation && readFile(path/"characters.json")==bytes,
            "CharacterStore preflights both selectCharacter and final restored player allocations before touching a live World with only one ID left");
        store.data["characters"][0].erase("simulation");const auto noSimulation=store.data;
        World exhausted(pvf,assets);exhausted.restoreSimulationCheckpoint(checkpointAtNext(checkpoint,UINT64_MAX));
        markerState(exhausted);const auto exhaustedBefore=liveState(exhausted);
        check(check.rejects([&]{store.apply(0,exhausted);}) && liveState(exhausted)==exhaustedBefore && store.data==noSimulation &&
            store.generation()==generation && readFile(path/"characters.json")==bytes,
            "A legacy character without simulation data also checks selectCharacter capacity before cancelling the live scene");
        samples["isolated_store_directory"]=path.generic_u8string();samples["save_generation"]=generation;
    }
    return {{"status","pass"},{"count",check.checks.size()},{"checks",check.checks},{"samples",samples},
        {"scope","Entity incarnation nonreuse, rejection atomicity, diagnostic source-status remap and immutable CharacterStore apply; no ACT continuation or frontend/native parity claim"}};
}
} // namespace dnf
