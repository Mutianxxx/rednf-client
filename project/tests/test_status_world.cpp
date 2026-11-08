#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/session.hpp"
#include "dnf/storage.hpp"
#include <memory>
#include <chrono>
#include <stdexcept>

namespace dnf {
namespace {
void statusFloor(World &w) {
    w.combat=true;w.mapWidth=1200;w.walkRects={{0,240,1200,240}};
    w.player.x=w.player.px=560;w.player.y=w.player.py=344;w.player.dir=1;
}
void statusTau(World &w) {
    Actor a;a.id=1;a.sourceId=11;a.monsterPath="monster/tau/tauarmy.mob";
    a.x=a.px=605;a.y=a.py=344;a.dir=-1;a.attackSerial=1;
    w.initializeMonsterAttributes(a,1);w.monsters.push_back(std::move(a));w.synchronizeEntityHandles();
}
bool awaitStun(World &w,int maximum=360) {
    for(int i=0;i<maximum;++i) {
        w.advance(16666667);
        if(w.statusStunned(w.player.handle)) return true;
        if(w.player.dead) return false;
    }
    return false;
}
bool basicAttack(const World &w) {
    return w.player.animation.rfind("attack",0)==0 || w.player.animation=="dashattack" || w.player.animation=="jumpattack";
}
template<class F> bool rejected(F &&f) {try {f();return false;}catch(const std::exception &){return true;}}
Json compactStatus(const World &w) {
    Json events=Json::array();
    for(const auto &event:w.events) if(event.kind=="status_stun" || event.kind=="player_hit" || event.kind=="player_miss")
        events.push_back({event.tick,event.kind,event.name,event.value});
    return {{"hp",w.player.hp},{"status",w.statusCheckpoint(w.player.handle)},
        {"random",w.randomStreams().snapshot()},{"events",events},{"tick",w.tick}};
}
} // namespace
Json runStatusWorldTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Status World: ")+message);checks.push_back(message);
    };
    RegionCatalog catalog(pvf,assets);Progression progression(catalog);
    std::unique_ptr<World> selected;uint64_t seed=0;
    for(;seed<32;++seed) {
        auto candidate=std::make_unique<World>(pvf,assets,WorldRules::BetaFoundationV1);
        candidate->applyEquipment(progression);candidate->randomStreams()=RandomStreams(seed);
        statusFloor(*candidate);statusTau(*candidate);
        if(awaitStun(*candidate)) {selected=std::move(candidate);break;}
        if(seed==0) writeJson("reports/beta-status/status-world-first-attempt.json",{
            {"world",candidate->snapshot()},{"events",candidate->eventLog()},{"stats",candidate->statReport()},
            {"simulation",candidate->simulationCheckpoint()}});
    }
    check(bool(selected),"Real Tau Army AI reaches its second source attack and applies an authored stun to the player");
    auto &w=*selected;
    const auto source=pvf.script("monster/tau/attackinfo/heading.atk");
    check(!readAttackDamage(source).usable() && readAttackDamage(source,AttackStatusConsumer::StunHostV1).usable(),
        "The pure damage reader blocks stun while an explicitly registered real status consumer admits the same source");
    auto bundle=w.statusCheckpoint(w.player.handle,7);
    check(bundle.at("active").size()==1 && bundle.at("active")[0].at("maximum_duration_ms")==1000 &&
          bundle.at("active")[0].at("source_path")==source.path,
        "Accepted heading.atk chance30/level0/duration1000 produces a separate source-bound status instance");
    check(w.statReport().at("last_damage").at("usable")==true && !w.player.dead,
        "The same source attack publishes actual HP damage together with its successful status outcome");
    w.freezeAi=true;const auto hp=w.player.hp,mp=w.player.mp;
    w.normalAttack();w.activate(0);w.enqueue({w.simulationNanoseconds(),1,true});
    const auto x=w.player.x;
    w.advance(100000000);
    check(w.activeSkill()<0 && !basicAttack(w) && w.player.x==x && w.player.mp==mp && w.player.hp==hp,
        "Independent stun blocks normal attack, skill admission and held movement without consuming MP");
    const auto simulation=w.simulationCheckpoint();const auto savedRandom=w.randomStreams().snapshot();
    const auto oldHandle=w.player.handle;
    World restored(pvf,assets,WorldRules::BetaFoundationV1);restored.applyEquipment(progression);statusFloor(restored);
    restored.restoreSimulationCheckpoint(simulation);
    check(restored.player.handle!=oldHandle && restored.statusStunned(restored.player.handle) &&
          restored.randomStreams().snapshot()==savedRandom,
        "Simulation restore remaps the saved status to a new player incarnation without rerolling combat RNG");
    const auto remapped=restored.statusCheckpoint(restored.player.handle);
    check(remapped.at("active")[0].at("attacker")==bundle.at("active")[0].at("attacker") &&
          remapped.at("active")[0].at("id")==bundle.at("active")[0].at("id"),
        "Remapping preserves the frozen possibly stale attacker and monotonic status instance identity");
    const auto firstIncarnation=restored.player.handle;
    restored.restoreSimulationCheckpoint(simulation);
    check(restored.player.handle!=firstIncarnation && !static_cast<const World &>(restored).resolveActor(firstIncarnation) &&
          restored.statusStunned(restored.player.handle) && restored.randomStreams().snapshot()==savedRandom,
        "Repeated simulation restore cannot resurrect the previous live player handle or reroll the accepted stun");
    auto invalidGlobal=simulation;invalidGlobal["status_instance_ids"]["next"]=1;
    const auto beforeInvalid=compactStatus(restored);
    check(rejected([&]{restored.restoreSimulationCheckpoint(invalidGlobal);}) && compactStatus(restored)==beforeInvalid,
        "Direct restore rejects a regressed global status watermark without publishing actor or RNG changes");
    auto advancedGlobal=simulation;advancedGlobal["status_instance_ids"]["next"]=50;
    restored.restoreSimulationCheckpoint(advancedGlobal);restored.restoreSimulationCheckpoint(simulation);
    check(restored.simulationCheckpoint().at("status_instance_ids").at("next")==50 &&
          restored.statusStunned(restored.player.handle) && restored.randomStreams().snapshot()==savedRandom,
        "Restoring an older World preserves the live status allocation watermark without rerolling its frozen application");
    restored.player.stunUntil=restored.nowMs()+5000;
    restored.advance(1000000000);
    check(!restored.statusStunned(restored.player.handle) && restored.player.stunUntil>restored.nowMs(),
        "Source millisecond stun expires independently while ordinary hit reaction can remain active");
    w.player.stunUntil=0;w.advance(1000000000);w.normalAttack();
    check(!w.statusStunned(w.player.handle) && basicAttack(w),"Expiry reopens ordinary attack admission");
    // Durable snapshot: player status lives both in standalone simulation and
    // session-owned actor data; the writer stamps the same outer generation.
    auto durableWorld=std::make_unique<World>(pvf,assets,WorldRules::BetaFoundationV1);
    durableWorld->applyEquipment(progression);durableWorld->randomStreams()=RandomStreams(seed);
    statusFloor(*durableWorld);statusTau(*durableWorld);
    check(awaitStun(*durableWorld),"A second identical normal AI execution reproduces the accepted source status");
    RegionSession session;
    auto savedSession=session.save(*durableWorld,"town");
    const auto dir=std::filesystem::path("reports/beta-status/test-saves")/std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    CharacterStore store(dir,"status-test-content");
    store.data["characters"][0]={{"name","status checkpoint"},{"class","swordman"},{"identity",CharacterIdentity{0,0,0}.json()}};
    store.capture(0,*durableWorld,progression);store.data["characters"][0]["region_session"]=savedSession;
    store.save();
    const auto &character=store.data.at("characters")[0];
    check(character.at("simulation").at("player_status").at("commit_generation")==store.generation() &&
          character.at("region_session").at("player").at("status_state").at("commit_generation")==store.generation(),
        "CharacterStore binds simulation and region status bundles to exactly the same durable generation");
    World disk(pvf,assets,WorldRules::BetaFoundationV1);Progression diskProgression(catalog);
    store.apply(0,disk,diskProgression);statusFloor(disk);
    check(disk.statusStunned(disk.player.handle),"Standalone normal CharacterStore apply restores player stun through the real simulation checkpoint");
    const auto diskFirstHandle=disk.player.handle;
    store.apply(0,disk,diskProgression);statusFloor(disk);
    check(disk.player.handle!=diskFirstHandle && !static_cast<const World &>(disk).resolveActor(diskFirstHandle) &&
          disk.statusStunned(disk.player.handle),
        "Repeated CharacterStore apply issues a fresh player incarnation while preserving the saved status");
    disk.changeScene();
    restoreSessionPlayer(disk,character.at("region_session").at("player"));
    check(disk.statusStunned(disk.player.handle) && disk.randomStreams().snapshot()==durableWorld->randomStreams().snapshot(),
        "The normal scene/player resume order restores the same frozen status without consuming a fresh random draw");
    const auto liveBefore=compactStatus(disk);auto corrupt=store.data;
    store.data["characters"][0]["simulation"]["status_restore_policy"]="unknown";
    check(rejected([&]{store.apply(0,disk,diskProgression);}) && compactStatus(disk)==liveBefore,
        "Unknown status restore policy is rejected before CharacterStore changes the live character incarnation");
    store.data=corrupt;
    for(const auto field:{"dead","hp","life"}) {
        auto &actor=store.data["characters"][0]["region_session"]["player"];
        if(std::string(field)=="dead") actor[field]=true;
        else actor[field]=std::string(field)=="hp"?0:int(ActorLife::Removed);
        check(rejected([&]{store.apply(0,disk,diskProgression);}) && compactStatus(disk)==liveBefore,
            "A dead, zero-HP or removed saved player cannot carry a live status bundle through character restore preflight");
        store.data=corrupt;
    }
    auto otherActor=corrupt.at("characters")[0].at("region_session").at("player");
    const auto otherHandle=EntityHandle{100000,1}.json();otherActor["entity_handle"]=otherHandle;
    auto &otherStatus=otherActor["status_state"];otherStatus["target_bundle"]["target"]=otherHandle;
    for(auto &active:otherStatus["active"]) active["target"]=otherHandle;
    for(auto &contact:otherStatus["contacts"]) contact["identity"]["target"]=otherHandle;
    store.data["characters"][0]["region_session"]["room_states"]=Json::array({Json::array({otherActor})});
    check(rejected([&]{store.apply(0,disk,diskProgression);}) && compactStatus(disk)==liveBefore,
        "Individually source-valid player and room bundles cannot reuse a successful status instance ID for different targets");
    store.data=corrupt;
    otherActor["life"]=int(ActorLife::Removed);
    store.data["characters"][0]["region_session"]["room_states"]=Json::array({Json::array({otherActor})});
    check(rejected([&]{store.apply(0,disk,diskProgression);}) && compactStatus(disk)==liveBefore,
        "A removed room actor with a saved live status is rejected before the current player or world is reset");
    store.data=corrupt;
    store.data["characters"][0]["region_session"]["player"]["status_state"]["commit_generation"]=store.generation()+1;
    check(rejected([&]{store.apply(0,disk,diskProgression);}) && compactStatus(disk)==liveBefore,
        "A status from another generation is rejected before cancelling live play, HP, RNG or state");
    store.data=corrupt;
    store.data["characters"][0]["simulation"]["status_instance_ids"]["next"]=1;
    check(rejected([&]{store.apply(0,disk,diskProgression);}) && compactStatus(disk)==liveBefore,
        "CharacterStore rejects a global status watermark behind its saved actor bundles before cancelling play");
    store.data=corrupt;
    store.data["characters"][0]["region_session"]["player"]["status_state"]["sources"][source.path]["usable"]=false;
    check(rejected([&]{store.apply(0,disk,diskProgression);}) && compactStatus(disk)==liveBefore,
        "A changed status source receipt is rejected in private restore preflight");
    store.data=corrupt;
    disk.changeScene();
    check(!disk.statusStunned(disk.player.handle),"Scene change clears active state and cannot carry a stun into another actor incarnation");
    Json expected=Json();
    for(const auto rate:{30,60,144,0}) {
        World timed(pvf,assets,WorldRules::BetaFoundationV1);timed.applyEquipment(progression);
        timed.randomStreams()=RandomStreams(seed);statusFloor(timed);statusTau(timed);
        constexpr int64_t totalNs=2500000000;
        if(rate) {
            const auto frames=rate*5/2;int64_t before=0;
            for(int frame=1;frame<=frames;++frame) {
                const auto end=totalNs*frame/frames;timed.advance(end-before);before=end;
            }
        } else {
            timed.advance(totalNs,3);
            while(timed.pendingTicks()) timed.advance(0,3);
        }
        const auto state=compactStatus(timed);
        if(expected.is_null()) expected=state;
        check(state==expected,"Actual Tau HP/status/RNG and accepted events are identical at 30/60/144 FPS and budgeted catch-up ticks");
    }
    samples["source_player_bundle"]=bundle;samples["remapped_player_bundle"]=remapped;samples["normal_ai_seed"]=seed;
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","Source Tau AI, HP/status/RNG, input/expiry and durable player restore; original-client numerical/visual parity pending"}};
}
} // namespace dnf
