#include "dnf/act_world_host.hpp"
#include "dnf/axis_motion.hpp"
#include "dnf/renderer.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *teleportSource="monster/newmonsters/shonan/kaizen/action/teleport.act";
constexpr const char *speedSource="monster/newmonsters/heaven/jena/action/dash.act";
constexpr const char *soundSource="monster/newmonsters/bloodbutterfly/bloodbutterflynamed/action/butterfly_attack6.act";
constexpr const char *destroySource="passiveobject/actionobject/monster/timegate/topsecretarea/rudol/action/iceball_break.act";
constexpr const char *spawnSource="monster/newmonsters/queen_rosi/action/attack2.act";
constexpr const char *spawnObjectSource="passiveobject/monster/soceress/iceniddlegroup.obj";
constexpr int spawnObjectId=30059;
constexpr const char *warningMarkSource="passiveobject/actionobject/common/action/flamestrike_item.act";
constexpr const char *transparentMotionSource="passiveobject/actionobject/monster/haze/action/bomb1.act";
constexpr const char *unknownObjectSource="passiveobject/actionobject/j_event/riceobj/action/rice1.act";
// Frame-0 [PARTICLE] source: BASE ANI is 80 ms with no type15 box, the PTL is
// a 5-particle / 500 ms one-shot burst, and there is no DESTROY command. That
// makes "the action completes naturally but its particles keep their own
// [life time] clock" observable without a paired ATK or a retired owner.
constexpr const char *particleSource="passiveobject/actionobject/monster/bloodbutterfly/action/destroy.act";
constexpr const char *particleProgram="passiveobject/actionobject/monster/bloodbutterfly/particle/destroy.ptl";
constexpr const char *particleOffsetSource="passiveobject/actionobject/monster/action/snowrockblast.act";
constexpr const char *unsupportedParticleSource="monster/newmonsters/lizardman/dragon_man/action/change_breath.act";
constexpr uint64_t generation=19;

struct WorldFixture {
    World world;
    ActWorldHost host;
    explicit WorldFixture(Pvf &p,Assets &a,bool speech=true)
        :world(p,a),host(world,p,a,"act-world-logic-test-static:"+sha256(a.staticBytes("audio.xml")),ActWorldHostOptions{speech,1200}) {
        world.freezeAi=true;world.combat=false;world.mapWidth=20000;
        world.walkRects={{12,185,19976,155}};world.blockedRects.clear();world.monsters.clear();
        world.player.x=world.player.px=6000;world.player.y=world.player.py=260;world.player.dir=1;
        Actor actor;actor.id=31;actor.x=actor.px=1000;actor.y=actor.py=260;actor.hp=actor.maxHp=100;
        actor.monsterPath="monster/newmonsters/shonan/kaizen/kaizen.mob";actor.dir=1;
        world.monsters.push_back(std::move(actor));world.synchronizeEntityHandles();
        world.setObjectTick([this](World &w) {
            SimulationStep step;step.tick=uint64_t(w.tick);step.milliseconds=uint64_t(w.nowMs());
            step.deltaMilliseconds=uint32_t(step.milliseconds-FixedStepClock::millisecondsAtTick(step.tick-1));
            const auto result=host.advance(step);if(!result.ok)throw std::runtime_error(result.error);
        });
    }
    EntityHandle owner() const {return world.monsters.front().handle;}
    ActBindRequest request(uint64_t id=40) const {
        ActBindRequest r;r.instanceId=id;r.actionId=id+100;r.owner=owner();r.tick=uint64_t(world.tick);
        r.simulationMs=uint64_t(world.nowMs());r.randomSequence=77;
        // Kaizen's first draw is its source 30% localized speech probability.
        // Select a deterministic source-test seed whose first draw speaks.
        for(uint64_t seed=0;seed<100;++seed){Pcg32 random(seed,77);if(random.bounded(100)<30){r.randomSeed=seed;break;}}
        return r;
    }
    std::shared_ptr<const ActProgram> bind(const std::string &source,uint64_t id=40,
                                          ActClockMode clockMode=ActClockMode::SourceMilliseconds) {
        const auto compiled=host.compile(source);if(!compiled.ok)throw std::runtime_error("World ACT fixture source rejected: "+compiled.json().dump());
        auto binding=request(id);binding.clockMode=clockMode;
        const auto result=host.bind(compiled.program,binding);
        if(!result.ok)throw std::runtime_error("World ACT fixture bind failed for "+source+" id="+std::to_string(id)+": "+result.error);
        return compiled.program;
    }
    void ticks(size_t count){for(size_t i=0;i<count;++i)world.advanceSingleTick();}
    Json summary() const {
        Json actors=Json::array();for(const auto &a:world.monsters)actors.push_back({{"handle",a.handle.json()},{"x",a.x},{"y",a.y},{"z",a.z},{"life",int(a.life)},{"animation",a.animation},{"path",a.animationPath}});
        return {{"host",host.snapshot(generation)},{"actors",actors},{"events",world.eventLog()}};
    }
};
size_t sounds(const World &w,const std::string &id) {
    return size_t(std::count_if(w.events.begin(),w.events.end(),[&](const auto &e){return e.kind=="sound" && e.name==id;}));
}
bool diagnostic(const Json &list,const std::string &code) {
    return std::any_of(list.begin(),list.end(),[&](const Json &v){return v.value("code",std::string())==code;});
}
Json sourceStatus(WorldFixture &fixture,Pvf &pvf,EntityHandle target) {
    // Explicit diagnostic source-bundle import, not a normal Kaizen/Tau skill
    // chain or recovered monster resistance formula. The real 30% source is
    // rolled by a local RNG against a labeled zero-resistance test target.
    auto &world=fixture.world;
    const auto source=readAttackStatuses(pvf.script("monster/tau/attackinfo/heading.atk"));
    StatusResistanceSnapshot resistance;resistance.packageIdentity=pvf.identity();resistance.level=1;
    resistance.trace.push_back({{"classification","diagnostic-zero-resistance-target"}});
    const auto attack=world.idSources().attacks.next();const auto watermark=world.simulationCheckpoint().at("status_instance_ids");
    for(uint64_t seed=0;seed<256;++seed) {
        StatusHost host(pvf.identity(),StunStatusPolicy::inferredFlatChanceStunV1());host.mergeInstanceWatermark(watermark);
        Pcg32 random(seed,17);StatusRequest request;request.attacker=fixture.owner();request.attackerLevel=1;
        request.target={target,resistance,false,Json::object()};request.attackInstance=attack;request.attack=source;
        auto prepared=host.prepare(request,uint64_t(world.nowMs()),random);
        if(!prepared.ready())throw std::runtime_error("ACT status lifecycle fixture rejected: "+prepared.receipt.dump());
        if(!prepared.receipt.at("outcomes")[0].at("procced").get<bool>())continue;
        host.publish(std::move(prepared),random);const auto bundle=host.snapshotTarget(target,uint64_t(world.nowMs()),generation);
        world.restoreStatusCheckpoint(bundle,target,target,generation);return bundle;
    }
    throw std::runtime_error("ACT status lifecycle fixture did not proc in its bounded local-seed search");
}
struct PreparedGraphFixture {
    Actor player;
    std::vector<Actor> monsters;
    EntityRegistry entities;
    SimulationIdSources ids;
    StatusHost statuses;
    uint64_t tick = 0;
    int characterLevel = 1;
    std::map<EntityHandle, EntityHandle> mapping;
    PreparedGraphFixture(const ActWorldRestoreGraph &saved,const ActWorldRestoreGraph &current,Pvf &pvf)
        : player(saved.player),monsters(saved.monsters),entities(saved.entities),
          statuses(pvf.identity(),StunStatusPolicy::inferredFlatChanceStunV1(
              saved.statusReceipt.at("policy").at("infer_resistance_as_percent").get<bool>())),
          tick(saved.tick),characterLevel(saved.characterLevel) {
        entities.mergeAllocationWatermark(current.entities);entities.retireAll();
        for(auto old:saved.entities.active())mapping.emplace(old,entities.create());
        player.handle=mapping.at(player.handle);
        for(auto &a:monsters)if(a.life!=ActorLife::Removed)a.handle=mapping.at(a.handle);
        ids.restore(saved.worldIds);
        auto value=saved.statusReceipt;
        auto target=[&](Json &v) {
            const auto handle=EntityHandle::fromJson(v);const auto found=mapping.find(handle);
            if(found!=mapping.end())v=found->second.json();
        };
        for(auto &active:value.at("active"))target(active["target"]);
        for(auto &contact:value.at("contacts"))target(contact["identity"]["target"]);
        // The production outer coordinator must copy the current StatusHost
        // before restore. This test-owned reconstruction retains both floors
        // and advances beyond both revisions without touching the real World.
        value["revision"]=std::max(value.at("revision").get<uint64_t>(),current.statusReceipt.at("revision").get<uint64_t>());
        MonotonicIds floor;floor.restore(value.at("instance_ids"));floor.merge(current.statusReceipt.at("instance_ids"));
        value["instance_ids"]=floor.snapshot();
        statuses.restore(value,FixedStepClock::millisecondsAtTick(tick),generation,
            [&](const std::string &path){return pvf.script(path);},[&](EntityHandle h){return entities.valid(h);});
    }
    ActWorldRestoreGraph graph() const {
        return {player,monsters,entities,ids.snapshot(),statuses.snapshot(FixedStepClock::millisecondsAtTick(tick),generation),tick,characterLevel};
    }
};
} // namespace

Json runActWorldHostTests(Pvf &pvf,Assets &assets) {
    // These are actual World actor/event consumers using current PVF source.
    // Fixture setup binds actions directly and freezes legacy AI; it does not
    // claim a general OBJ factory, NPC activation or CharacterStore disk load.
    Json checks=Json::array();auto check=[&](bool ok,const char *message){if(!ok)throw std::runtime_error(std::string("ACT World host: ")+message);checks.push_back(message);};
    {
        WorldFixture f(pvf,assets,false);const auto compiled=f.host.compile(teleportSource);
        check(!compiled.ok && diagnostic(compiled.json().at("diagnostics"),"missing_command_consumer"),
              "Localized SPEECH blocks execution until its real presentation endpoint is explicitly attached");
        check(f.host.hasCommandConsumer("spawn_passive_object") && f.host.hasCommandConsumer("particle") &&
              f.host.hasCommandConsumer("attack_rect") && f.host.hasCommandConsumer("change_attack_info") &&
              f.host.hasCommandConsumer("deferred_call") && f.host.hasCommandConsumer("trigger_control") &&
              !f.host.hasCommandConsumer("deferred_call_cross_program"),
              "Object/PTL/attack/self-delivered behavior/local trigger consumers are registered while foreign recipients remain blocked");
        const auto attack=f.host.compile("passiveobject/actionobject/monster/new_event/action/assault_missile0.act");
        check(attack.ok && attack.program->runtimeReady,
              "Root ANI type15 is admitted only through the real registered collision and source damage host");
        auto messageHas=[](const Json &list,const std::string &needle){
            return std::any_of(list.begin(),list.end(),[&](const Json &v){
                return v.value("message",std::string()).find(needle)!=std::string::npos;});};
        // [SEND DO BEHAVIOR] [ME] is an immediate nested dispatch of this program's
        // own behavior table; [DELAY DO BEHAVIOR] [ME] is the same dispatch on a
        // deadline. Only the recipient name decides, so both share one consumer.
        const auto selfSend=f.host.compile("monster/newmonsters/queen_rosi/action/command1.act");
        check(!messageHas(selfSend.json().at("diagnostics"),"deferred_call_cross_program"),
              "1031 SEND DO BEHAVIOR [ME] compiles as an immediate self-dispatch instead of a foreign delivery gap");
        const auto selfDelay=f.host.compile("monster/newmonsters/shonan/gado/action/attack3.act");
        check(!messageHas(selfDelay.json().at("diagnostics"),"deferred_call"),
              "1031 DELAY DO BEHAVIOR [ME] is consumed by the owning ACT, not reported as a missing consumer");
        // Trigger-level [DELAY DO BEHAVIOR] is a different construct: its
        // recipient comes from the trigger query and its index has never been
        // observed outside this program's table (0 of 278 sites). It keeps the
        // existing scheduling path; only the BEHAVIOR-embedded SEND is split here.
        const auto checkupDelay=f.host.compile("monster/newmonsters/shonan/kinshou/action/swing2.act");
        check(diagnostic(checkupDelay.json().at("diagnostics"),"missing_resource_consumer") &&
              !messageHas(checkupDelay.json().at("diagnostics"),"deferred_call"),
              "1031 trigger-level DELAY DO BEHAVIOR keeps its scheduling path while OBJ recursion still blocks the source ACT");
        // 10 of the 356 1031 call sites pass a behavior index beyond the file's
        // own table; every one of them names CHECKUP OBJECT. That is direct
        // evidence the index belongs to the receiving object's table, so a
        // foreign recipient cannot be executed from this program at all.
        const auto crossSend=f.host.compile("monster/newmonsters/risk_dungeon/noirpera/disease_spirit/action/absorption.act");
        check(messageHas(crossSend.json().at("diagnostics"),"deferred_call_cross_program"),
              "1031 SEND DO BEHAVIOR to CHECKUP OBJECT stays an explicit consumer gap instead of inheriting the self path");
        const auto selfSendTile=f.host.compile("passiveobject/actionobject/monster/dimensiongate/cosmofiend/gaunis/_namgyu/action/red_success_07_tile.act");
        check(!messageHas(selfSendTile.json().at("diagnostics"),"deferred_call_cross_program"),
              "The same construct with a [ME] recipient no longer borrows the foreign-recipient block");
    }
    {
        constexpr const char *triggerControlSource="passiveobject/actionobject/map/risk_dungeon/cartelcommand/action/xyz1.act";
        WorldFixture f(pvf,assets,false);
        const auto triggerControl=f.host.compile(triggerControlSource);
        check(triggerControl.ok && triggerControl.program->runtimeReady,
              "A 1031 ACT whose only gap was TRIGGER control now reaches real World admission");
        f.bind(triggerControlSource,40);
        check(f.host.instances().at(40).triggers[0].enabled,
              "The sourced FRAME2 trigger starts enabled before its own BEHAVIOR disables it");
        f.ticks(60);
        check(!f.host.instances().at(40).triggers[0].enabled &&
              std::any_of(f.world.events.begin(),f.world.events.end(),[](const auto &e){return e.kind=="act_trigger_control";}),
              "Local TRIGGER OFF changes the owning ACT trigger state and publishes a real World control event");
    }
    {
        WorldFixture f(pvf,assets);
        const auto before=f.world.snapshot();const auto random=f.world.randomStreams().snapshot();
        f.ticks(12);
        const auto host=f.host.snapshot(generation);
        check(host.at("last_tick")==12 && host.at("instances").empty() && f.host.instances().empty() &&
            f.world.monsters.front().x==before.at("monsters")[0].at("x") && f.world.randomStreams().snapshot()==random,
            "An empty ACT host advances its exact commit clock without modifying actors or drawing random numbers");
        const auto unchanged=f.summary();
        SimulationStep repeated{12,200,17};
        check(!f.host.advance(repeated).ok && f.summary()==unchanged,
            "The empty-host path still rejects a repeated tick before publishing anything");
        f.bind(teleportSource);f.ticks(12);
        check(f.host.speechBubbles().size()==1,
            "An ACT bound after empty ticks executes source frame events at the relative action clock");
    }
    {
        WorldFixture f(pvf,assets);const auto p=f.bind(teleportSource);
        check(p->source.memberSha256=="acdafb8bbbf17095c7ec35a1c96fdf7d953d73e205ea4b5ec46e55cc404fc9b5" &&
              p->motion && p->motion->frameDurationsMs==std::vector<int64_t>(8,100),
              "Kaizen binds current source bytes and all eight 100 ms ANI delays");
        check(f.world.monsters.front().animation=="act" && f.world.monsters.front().animationPath==teleportSource &&
              f.host.ownsActor(f.owner()),"Binding publishes actual MonsterMotion presentation and ownership on the World actor");
        f.ticks(11);check(f.host.speechBubbles().empty(),"Kaizen speech does not appear before source frame 2");
        f.ticks(1);check(f.host.speechBubbles().size()==1 && f.host.speechBubbles()[0].text==std::get<ActSpeech>(p->motion->events[0].payload).text &&
              f.host.speechBubbles()[0].speaker==f.owner() && sounds(f.world,"kaizen_speech_03")==0,
              "Source-localized speech becomes a real owner-bound text bubble instead of an audio ID");
        f.ticks(29);check(f.world.tick==41 && f.world.monsters.front().x==1000,
              "Kaizen World position remains unchanged through the fixed tick before frame 7");
        f.ticks(1);check(f.world.tick==42 && f.world.monsters.front().x==5860 && f.world.monsters.front().y==260 &&
              f.world.player.x==6000,"MOVE ME teleports the actual monster to the queried character base plus the source -140 offset at 700 ms");
        f.ticks(6);check(!f.host.ownsActor(f.owner()) && f.host.speechBubbles().empty() && f.world.monsters.front().animation=="stay" &&
              f.world.monsters.front().animationPath.empty(),"Source motion completion releases owned speech and restores the prior actor presentation");
    }
    {
        WorldFixture f(pvf,assets);const auto program=f.bind(speedSource);double expected=1000;f.ticks(1);
        AxisMotion first{400,0,-1};expected+=advanceAxisMotion(first,16);
        check(std::abs(f.world.monsters.front().x-expected)<1e-7 && f.host.controlsMovement(f.owner()),
              "SET SPEED moves the actual World actor using the recovered fixed-tick arithmetic on its first source frame");
        f.ticks(4);for(uint64_t i=2;i<=5;++i){AxisMotion axis{400,0,-1};expected+=advanceAxisMotion(axis,int32_t(FixedStepClock::millisecondsAtTick(i)-FixedStepClock::millisecondsAtTick(i-1)));}
        check(std::abs(f.world.monsters.front().x-expected)<1e-7,"Successive 16/17 ms ticks have one native arithmetic movement integration each");
        const auto x=f.world.monsters.front().x;check(f.host.cancel(40,"test action exit").ok && !f.host.controlsMovement(f.owner()),
              "Action cancellation removes only its owned velocity and presentation");
        f.ticks(5);check(f.world.monsters.front().x==x,"A cancelled ACT cannot leave residual speed on subsequent World ticks");
        const auto unchanged=f.summary();check(!f.host.bind(program,f.request()).ok && f.summary()==unchanged,
              "Cancelled or pruned actions cannot reuse the persisted ACT instance watermark");
    }
    {
        WorldFixture f(pvf,assets);f.bind(soundSource);f.ticks(1);
        check(sounds(f.world,"RUCY_COMB")==1,"Source frame-0 SOUND reaches the real World sound event consumed by main-loop Audio::play");
        f.ticks(80);check(sounds(f.world,"RUCY_COMB")==1,"Later ticks and completed source motion cannot replay the same SOUND occurrence");
        const auto source=f.host.instances().at(40).program->source;
        check(!source.packageIdentity.empty() && source.memberPath==soundSource && !source.memberSha256.empty(),
              "World sound execution keeps its original PVF program identity");
    }
    {
        WorldFixture f(pvf,assets);f.bind(destroySource);const auto handle=f.owner();f.ticks(25);
        check(static_cast<const World &>(f.world).resolveActor(handle)!=nullptr,"DESTROY does not remove its World actor before source frame 7");
        f.ticks(1);check(f.world.monsters.front().life==ActorLife::Removed && static_cast<const World &>(f.world).resolveActor(handle)==nullptr &&
              !f.host.ownsActor(handle),"Source-frame DESTROY removes the real actor and retires its stable generation");
        check(std::none_of(f.world.events.begin(),f.world.events.end(),[](const auto &e){return e.kind=="killed";}),
              "ACT DESTROY cannot manufacture an accepted lethal attack or a kill reward");
    }
    {
        WorldFixture f(pvf,assets);const auto p=f.host.compile(teleportSource);check(p.ok,"The external-clock fixture uses the same executable real Kaizen source");
        auto request=f.request();request.clockMode=ActClockMode::ExternalAnimationDelta;
        const auto bound=f.host.bind(p.program,request);if(!bound.ok)throw std::runtime_error(bound.error);
        uint64_t animationDelta=0;
        f.world.setObjectTick([&](World &w){SimulationStep step{uint64_t(w.tick),uint64_t(w.nowMs()),
            uint32_t(uint64_t(w.nowMs())-FixedStepClock::millisecondsAtTick(uint64_t(w.tick)-1))};
            const auto result=f.host.advance(step,{{40,animationDelta}});if(!result.ok)throw std::runtime_error(result.error);});
        f.ticks(50);check(f.world.monsters.front().x==1000 && f.host.instances().at(40).animationUs==0 &&
              f.world.nowMs()-f.world.monsters.front().animStart==0 && f.host.speechBubbles().empty(),
              "Zero external animation delta freezes actual MonsterMotion age while fixed simulation time continues");
        animationDelta=200000;f.ticks(3);
        check(f.world.monsters.front().x==1000 && f.host.instances().at(40).animationUs==600000 &&
              f.world.nowMs()-f.world.monsters.front().animStart==600 && f.host.speechBubbles().size()==1,
              "One already-scaled external delta controls source events and real presentation without a second multiplier");
        f.ticks(1);check(f.world.monsters.front().x==5860 && !f.host.ownsActor(f.owner()),
              "Crossing several external-clock source frames still applies the real frame-7 teleport and lifecycle cleanup");
    }
    {
        WorldFixture f(pvf,assets);f.bind(teleportSource);f.ticks(20);
        auto saved=f.host.snapshot(generation);saved["future_host_field"]={{"retained",true}};
        WorldFixture reference(pvf,assets);reference.bind(teleportSource);reference.ticks(80);
        const auto continuous=reference.summary();
        // Import into an already prepared same-tick World. Rewinding public
        // tick alone would leave StatusHost's monotonic clock in the future.
        // Full outer actor/status/registry restoration remains separate.
        check(f.host.restore(saved,generation).ok && f.host.snapshot(generation).at("future_host_field").at("retained")==true,
              "Same-generation World actor receipts restore ACT age, random stream, speech and unknown host fields");
        f.ticks(60);auto resumed=f.summary();resumed["host"].erase("future_host_field");
        check(resumed==continuous,"A real World teleport and source-event stream match uninterrupted execution after same-generation restore");
        auto current=f.host.snapshot(generation);const auto unchanged=f.summary();
        check(!f.host.restore(current,generation+1).ok && f.summary()==unchanged,"Wrong outer commit generation is rejected without mutating the World or ACT state");
        current["static_identity"]="different-static-content";
        check(!f.host.restore(current,generation).ok && f.summary()==unchanged,"Changing static-content identity cannot silently reuse an old ACT continuation");
        current=f.host.snapshot(generation);current["actor_receipts"][0]["hp"]=1;
        check(!f.host.restore(current,generation).ok && f.summary()==unchanged,"Mismatched live actor resource/pose receipts are rejected before publication");
        current=f.host.snapshot(generation);current["status_receipt"]["revision"]=UINT64_MAX;
        check(!f.host.restore(current,generation).ok && f.summary()==unchanged,
              "ACT continuation rejects a different same-generation World status receipt without rewriting the status service");
        current=f.host.snapshot(generation);current["actor_receipts"][0]["hit_stop_ticks"]=99;
        check(!f.host.restore(current,generation).ok && f.summary()==unchanged,
              "ACT continuation requires the same actor hit-stop and movement ownership receipts");
    }
    {
        WorldFixture f(pvf,assets);f.bind(teleportSource);f.ticks(20);
        const auto saved=f.host.snapshot(generation);const auto before=f.summary();
        auto one=f.host.prepareRestore(saved,generation,f.host.liveGraph(generation));
        auto other=f.host.prepareRestore(saved,generation,f.host.liveGraph(generation));
        check(one.ready() && other.ready() && f.host.canPublish(one) && f.summary()==before,
              "Preparing full host restore is pure and retains a complete origin guard");
        check(f.host.publish(std::move(one)).ok && !one.ready() && f.summary()==before,
              "Same-graph host candidate publishes once without replaying bind events, sounds or speech");
        check(!f.host.canPublish(other) && !f.host.publish(std::move(other)).ok && f.summary()==before,
              "Runtime publication epoch rejects pre-restore work even when saved logical state is identical");
        check(!f.host.publish(std::move(one)).ok && f.summary()==before,
              "A consumed host restore cannot be applied twice");
        WorldFixture foreign(pvf,assets);foreign.bind(teleportSource);foreign.ticks(20);
        auto wrongOrigin=f.host.prepareRestore(saved,generation,f.host.liveGraph(generation));const auto foreignBefore=foreign.summary();
        check(!foreign.host.publish(std::move(wrongOrigin)).ok && foreign.summary()==foreignBefore && f.summary()==before,
              "A prepared host restore cannot publish through another host with identical logical state");
        auto stale=f.host.prepareRestore(saved,generation,f.host.liveGraph(generation));
        f.world.player.hp-=1;const auto changed=f.summary();
        check(!f.host.canPublish(stale) && !f.host.publish(std::move(stale)).ok && f.summary()==changed,
              "Changed outer actor receipt rejects prepared import without undoing newer live state");
    }
    {
        WorldFixture f(pvf,assets);f.bind(teleportSource);f.ticks(20);
        sourceStatus(f,pvf,f.world.player.handle);
        const auto saved=f.host.snapshot(generation);const auto original=f.host.liveGraph(generation);const auto before=f.summary();
        PreparedGraphFixture fresh(original,original,pvf);const auto graph=fresh.graph();
        auto prepared=f.host.prepareRemappedRestore(saved,generation,original,graph,fresh.mapping);
        check(prepared.ready() && f.host.canPublish(prepared) && f.summary()==before,
              "Typed host remap prepares privately against candidate actors, registry and status rather than querying the live roster");
        const auto &value=prepared.snapshot();
        check(value.at("schema")==3 && value.at("instances")[0].at("owner")==fresh.mapping.at(f.owner()).json() &&
              value.at("entity_registry")==fresh.entities.snapshot() && value.at("actor_receipts")[0].at("handle")==fresh.player.handle.json() &&
              value.at("world_ids")==saved.at("world_ids"),
              "Candidate host carries fresh actor ownership while retaining source, clock, instance and logical-ID receipts");
        check(value.at("speech").size()==1 && value.at("speech")[0].at("speaker")==fresh.mapping.at(f.owner()).json() &&
              value.at("speech")[0].at("event_key")==saved.at("speech")[0].at("event_key") &&
              value.at("speech")[0].at("expires_ms")==saved.at("speech")[0].at("expires_ms"),
              "Continued speech keeps its occurrence and expiry while remapping only its typed speaker");
        check(value.at("status_receipt").at("active")[0].at("target")==fresh.player.handle.json() &&
              value.at("status_receipt").at("active")[0].at("attacker")==saved.at("status_receipt").at("active")[0].at("attacker") &&
              value.at("status_receipt").at("active")[0].at("id")==saved.at("status_receipt").at("active")[0].at("id") &&
              value.at("status_receipt").at("active")[0].at("remaining_ms")==saved.at("status_receipt").at("active")[0].at("remaining_ms"),
              "Status target identity changes without rewriting historical attacker, frozen outcome, instance ID or lifetime");
        check(!f.host.publish(std::move(prepared)).ok && f.summary()==before,
              "Standalone host import refuses to publish a fresh graph over unmatched live World actors and status");
        auto bad=saved;bad["actor_receipts"][1]["hit_stop_ticks"]=99;
        check(!f.host.prepareRemappedRestore(bad,generation,original,graph,fresh.mapping).ready() && f.summary()==before,
              "Original actor receipt corruption rejects before remapped receipts can bless it");
        bad=saved;bad["instances"][0]["accepted_event_receipts"][0]["payload"]["other"]=f.world.player.handle.json();
        check(!f.host.prepareRemappedRestore(bad,generation,original,graph,fresh.mapping).ready() && f.summary()==before,
              "Original event preimage corruption rejects the whole host candidate before any mutation");
        bad=saved;bad["static_identity"]="other-static-source";
        check(!f.host.prepareRemappedRestore(bad,generation,original,graph,fresh.mapping).ready() && f.summary()==before,
              "Typed host import cannot reuse a different static-content identity");
        bad=saved;bad["schema"]=2;bad["policy"]="inferred-act-world-host-v2-status-lifecycle";
        check(!f.host.prepareRemappedRestore(bad,generation,original,graph,fresh.mapping).ready() && f.summary()==before,
              "Explicit remapped continuation refuses legacy host policy without silently cancelling actions");
        auto missing=fresh.mapping;missing.erase(original.player.handle);
        check(!f.host.prepareRemappedRestore(saved,generation,original,graph,missing).ready() && f.summary()==before,
              "Incomplete fresh ownership mapping rejects and preserves the entire live World");
        auto wrongStatus=graph;wrongStatus.statusReceipt["active"][0]["attacker"]=fresh.mapping.at(f.owner()).json();
        check(!f.host.prepareRemappedRestore(saved,generation,original,wrongStatus,fresh.mapping).ready() && f.summary()==before,
              "Changing a historical status attacker cannot enter through a candidate target remap");
        auto wrongIds=graph;wrongIds.worldIds["events"]["next"]=999999;
        check(!f.host.prepareRemappedRestore(saved,generation,original,wrongIds,fresh.mapping).ready() && f.summary()==before,
              "Candidate restore cannot advance logical event allocation or reissue SetAction during import");
        auto wrongClock=graph;wrongClock.tick+=1;
        check(!f.host.prepareRemappedRestore(saved,generation,original,wrongClock,fresh.mapping).ready() && f.summary()==before,
              "Mixed candidate clock/status boundary rejects before publication");
    }
    {
        WorldFixture f(pvf,assets);f.bind(teleportSource);f.world.blockedRects={{5850,250,20,20}};f.ticks(42);
        check(f.host.instances().at(40).status==ActInstanceStatus::Faulted && f.world.monsters.front().x==1000 &&
              f.host.speechBubbles().empty() && diagnostic(f.host.diagnostics(),"act_world_consumer_fault"),
              "A collision-rejected teleport discards partial World effects and faults with owned-state cleanup");
        f.ticks(3);check(f.world.tick==45,"A World consumer fault cannot leave the host one tick behind and block all future simulation");
    }
    {
        WorldFixture f(pvf,assets);f.bind(speedSource);f.ticks(2);const auto retired=f.owner();
        Actor replacement=f.world.monsters.front();replacement.handle={};replacement.x=replacement.px=4000;
        replacement.animation="stay";replacement.animationPath.clear();f.world.monsters.clear();f.world.monsters.push_back(replacement);f.world.synchronizeEntityHandles();
        const auto handle=f.owner();f.ticks(1);
        check(handle!=retired && f.world.monsters.front().x==4000 && f.host.instances().at(40).status==ActInstanceStatus::Cancelled,
              "A replacement with the same legacy actor ID never receives stale owner-generation speed or cleanup");
    }
    {
        WorldFixture f(pvf,assets);f.bind(destroySource);const auto removed=f.owner();
        const auto targetStatus=sourceStatus(f,pvf,removed);const auto retained=sourceStatus(f,pvf,f.world.player.handle);
        const auto random=f.world.randomStreams().snapshot();f.ticks(26);
        const auto removedStatus=f.world.statusCheckpoint(removed,generation);
        const auto playerStatus=f.world.statusCheckpoint(f.world.player.handle,generation);
        check(f.world.monsters.front().life==ActorLife::Removed && !static_cast<const World &>(f.world).resolveActor(removed) &&
              removedStatus.at("active").empty() && removedStatus.at("contacts").empty() &&
              !targetStatus.at("active").empty() && playerStatus.at("active").size()==1 && playerStatus.at("contacts").size()==1,
              "ACT DESTROY atomically retires its actual actor, generation, independent active status and accepted-contact ledger");
        check(playerStatus.at("active")[0].at("attacker")==removed.json() &&
              playerStatus.at("active")[0].at("id")==retained.at("active")[0].at("id") &&
              playerStatus.at("instance_ids").at("next")==3 && f.world.randomStreams().snapshot()==random,
              "Destroying a status attacker preserves another target's historical attacker, global status watermark and RNG");
    }
    {
        WorldFixture f(pvf,assets);f.bind(speedSource);f.ticks(1);const auto x=f.world.monsters.front().x;
        const auto status=sourceStatus(f,pvf,f.owner());const auto random=f.world.randomStreams().snapshot();f.ticks(5);
        check(f.world.monsters.front().x==x && f.world.statusStunned(f.owner()) && f.host.controlsMovement(f.owner()),
              "Independent source status eligibility suppresses actual ACT-owned recipient speed while retaining its ownership receipt");
        check(f.host.cancel(40,"diagnostic stun cleanup").ok && !f.host.controlsMovement(f.owner()) &&
              f.world.statusStunned(f.owner()) && f.world.statusCheckpoint(f.owner(),generation).at("active")[0].at("id")==status.at("active")[0].at("id"),
              "Action cancellation cleans only ACT-owned movement and presentation while preserving the target's independent stun");
        f.ticks(61);check(!f.world.statusStunned(f.owner()) && f.world.monsters.front().x==x &&
              f.world.randomStreams().snapshot()==random,
              "Status expiry follows source milliseconds after action cancellation and cannot revive a cancelled ACT velocity");
    }
    {
        WorldFixture f(pvf,assets);f.bind(speedSource,40,ActClockMode::ExternalAnimationDelta);
        f.world.monsters.front().hitStopTicks=3;
        f.world.setObjectTick([&](World &w){
            const auto delta=uint32_t(uint64_t(w.nowMs())-FixedStepClock::millisecondsAtTick(uint64_t(w.tick)-1));
            const auto paused=w.monsters.front().hitStopped;
            const auto result=f.host.advance({uint64_t(w.tick),uint64_t(w.nowMs()),delta},{{40,paused?0:uint64_t(delta)*1000}});
            if(!result.ok)throw std::runtime_error(result.error);
        });
        f.ticks(3);check(f.world.monsters.front().x==1000 && f.host.instances().at(40).animationUs==0 &&
              f.host.instances().at(40).elapsedMs==50 && f.world.nowMs()-f.world.monsters.front().animStart==0,
              "The selected external animation clock supplies zero during actual actor hit-stop while simulation age continues");
        f.ticks(1);const auto delta=FixedStepClock::millisecondsAtTick(4)-FixedStepClock::millisecondsAtTick(3);
        AxisMotion movement{400,0,-1};const auto expected=1000.0+double(advanceAxisMotion(movement,int32_t(delta)));
        check(std::abs(f.world.monsters.front().x-expected)<1e-7 &&
              f.host.instances().at(40).animationUs==delta*1000 && !f.world.monsters.front().hitStopped,
              "Leaving hit-stop advances source events, presentation and actor movement once using the controller's single already-scaled delta");
        f.world.monsters.front().hitStopTicks=2;f.world.monsters.front().hitStopped=true;
        check(f.host.cancel(40,"diagnostic hit-stop exit").ok && f.world.monsters.front().hitStopTicks==2 &&
              f.world.monsters.front().hitStopped && !f.host.controlsMovement(f.owner()),
              "ACT cleanup cannot clear unrelated actor hit-stop state");
    }
    {
        WorldFixture f(pvf,assets);f.bind(destroySource);sourceStatus(f,pvf,f.owner());f.ticks(25);
        const auto handle=f.owner();const auto random=f.world.randomStreams().snapshot();
        f.world.setObjectTick([&](World &w){
            // Diagnostic exhaustion injects a real StatusHost consumer failure
            // after the private ACT candidate has marked its actor Removed.
            // Target import validates the historical state and publishes the
            // combined state, advancing revision at both restore boundaries.
            // Exhaust it after that import, inside the real
            // DESTROY consumer, rather than failing the fixture setup.
            auto bundle=w.statusCheckpoint(handle,generation);bundle["revision"]=UINT64_MAX-2;
            w.restoreStatusCheckpoint(bundle,handle,handle,generation);
            const auto delta=uint32_t(uint64_t(w.nowMs())-FixedStepClock::millisecondsAtTick(uint64_t(w.tick)-1));
            const auto result=f.host.advance({uint64_t(w.tick),uint64_t(w.nowMs()),delta});
            if(!result.ok)throw std::runtime_error(result.error);
        });
        f.ticks(1);const auto status=f.world.statusCheckpoint(handle,generation);
        check(static_cast<const World &>(f.world).resolveActor(handle) && !f.world.monsters.front().dead &&
              f.world.monsters.front().life==ActorLife::Alive && status.at("active").size()==1 && status.at("contacts").size()==1 &&
              f.host.instances().at(40).status==ActInstanceStatus::Faulted && !f.host.ownsActor(handle) &&
              diagnostic(f.host.diagnostics(),"act_world_consumer_fault") && f.world.randomStreams().snapshot()==random &&
              std::none_of(f.world.events.begin(),f.world.events.end(),[](const auto &e){return e.kind=="act_destroy" || e.kind=="killed";}),
              "A real status-retirement failure discards candidate actor removal and ledger edits, publishing only ACT fault and ownership cleanup");
    }
    {
        Json reference;for(const int fps:{30,60,144,240}) {
            WorldFixture f(pvf,assets);f.bind(speedSource);int64_t previous=0;
            for(int frame=1;frame<=fps*2;++frame){const int64_t now=int64_t(frame)*1000000000/fps;f.world.advance(now-previous);previous=now;}
            const auto summary=f.summary();if(reference.is_null())reference=summary;
            check(summary==reference,"Actual World position, ACT state and events are identical at 30/60/144/240 render schedules");
        }
        WorldFixture catchup(pvf,assets);catchup.bind(speedSource);catchup.world.advance(2000000000,3);
        while(catchup.world.pendingTicks())catchup.world.advance(0,3);
        check(catchup.summary()==reference,"Budgeted catch-up ticks preserve the same real World movement and ACT event results");
    }
    {
        // P0-2 scoped factory. 1031 PVF [WARNING MARK] has 2 or 4 integer
        // operands, not the zero the old catch-all assumed. After preserving
        // those operands and emitting an explicit non-blocking consumer gap,
        // real monster/actionobject ACTs reach full static admission. This
        // sample's BASE ANI has no type15 attack box, so bind needs no forged
        // paired ATK; its four CREATE PASSIVEOBJECT commands spawn object
        // 30059, whose OBJ literal closure is ANI/ATK only.
        WorldFixture f(pvf,assets,false);
        const auto admitted=f.host.compile(spawnSource);
        check(admitted.ok && admitted.program->runtimeReady &&
              diagnostic(admitted.json().at("diagnostics"),"warning_mark_consumer_unregistered"),
            "1031 WARNING MARK operands are retained while the unregistered warning-decal consumer stays an explicit non-blocking gap");
        size_t marks=0;
        for(const auto &behavior:admitted.program->behaviors)
            for(const auto &instruction:behavior.instructions)
                if(const auto *spawn=std::get_if<ActSpawn>(&instruction.payload))
                    marks+=spawn->warningMark.size()==4 && spawn->objectIndex==spawnObjectId;
        check(marks==4,"CREATE PASSIVEOBJECT keeps its four source WARNING MARK operands in the compiled instructions");
        const auto warning=f.host.compile(warningMarkSource);
        check(warning.ok && warning.program->runtimeReady,
            "The 1031 [WARNING MARK] operand fix removes a real syntax misclassification");
        WorldFixture attack(pvf,assets,false);
        const auto unpaired=attack.host.bind(warning.program,attack.request(42));
        check(!unpaired.ok && unpaired.error.find("type15")!=std::string::npos,
            "An admitted ACT whose BASE ANI has unpaired type15 boxes is still blocked at bind instead of silently losing attack identity");
        auto pairedRequest=attack.request(42);
        pairedRequest.sourceObject="passiveobject/actionobject/common/flamebomb_item.obj";
        const auto paired=attack.host.bind(warning.program,pairedRequest);
        check(paired.ok,
            "A BASE ANI type15 box binds when its exact OBJ [basic action] supplies one authored [attack info]");
        auto forgedRequest=attack.request(43);
        forgedRequest.sourceObject="passiveobject/actionobject/common/darkthunderbolt1.obj";
        const auto forged=attack.host.bind(warning.program,forgedRequest);
        check(!forged.ok && forged.error.find("[basic action]")!=std::string::npos,
            "An unrelated OBJ attack identity cannot be borrowed for another ACT");
        constexpr const char *subSource="passiveobject/actionobject/common/action/darkthunderbolt1.act";
        const auto staticSub=attack.host.compile(subSource);
        check(!staticSub.ok && diagnostic(staticSub.json().at("diagnostics"),"act_sub_animation_collision_binding_missing"),
            "SUB ANI type15 stays a static rejection until an exact attack identity is supplied");
        auto subRequest=attack.request(44);
        subRequest.sourceObject="passiveobject/actionobject/common/darkthunderbolt1.obj";
        const auto compiledSub=attack.host.compile(subSource,{},&subRequest);
        check(compiledSub.ok && compiledSub.program->runtimeReady,
            "The exact OBJ action/ATK context admits an attack-bearing SUB ANI World program");
        const auto compiledSubJson=compiledSub.json();
        bool subTrack=false,sourceFrameKept=false;
        for(const auto &track:compiledSubJson.at("collision_tracks")) {
            const bool isSub=track.at("role").get<std::string>()=="sub";
            subTrack|=isSub;
            sourceFrameKept|=isSub && track.at("start_us").is_number() &&
                track.at("x").is_number() && track.at("y").is_number() && track.at("layer").is_number_integer();
        }
        const std::string trackEvidence="SUB ANI collision tracks retain authored frame boundary, layer and XY placement: "+
            compiledSubJson.at("collision_tracks").dump();
        check(subTrack && sourceFrameKept,trackEvidence.c_str());
        const auto ptl=f.host.compile("passiveobject/actionobject/common/action/exsviperbullet.act");
        check(!ptl.ok && diagnostic(ptl.json().at("diagnostics"),"missing_resource_consumer"),
            "OBJ-internal [string data] PTL references are not ACT-level [PARTICLE] commands and stay precisely blocked");
        const auto transparent=f.host.compile(transparentMotionSource);
        check(!transparent.ok && diagnostic(transparent.json().at("diagnostics"),"missing_resource_consumer"),
            "A motion ANI with only transparent placeholder frames stays blocked instead of being counted as an admitted closure");
        const auto unknown=f.host.compile(unknownObjectSource);
        check(!unknown.ok && diagnostic(unknown.json().at("diagnostics"),"missing_resource"),
            "An unregistered passive-object index is reported as a missing source instead of fabricating an entity");
        f.bind(spawnSource,41);f.ticks(60);
        const auto &objects=f.host.spawnedObjects().instances();
        check(!objects.empty() && objects.front().definition && objects.front().definition->id==spawnObjectId &&
              objects.front().definition->source==spawnObjectSource &&
              objects.front().placement.identity.run=="act-runtime" && objects.front().placement.z==0,
            "ACT CREATE PASSIVEOBJECT publishes a real ObjectInstance with its registered OBJ definition and source coordinates");
        check(std::any_of(objects.begin(),objects.end(),[](const auto &o){
                return o.placement.identity.room.rfind("41:",0)==0;}),
            "Spawned entities carry their owning ACT instance/action identity for scoped cleanup");
        check(std::any_of(f.world.events.begin(),f.world.events.end(),[](const auto &e){return e.kind=="act_spawn_passive_object";}),
            "World event log records the ACT-owned object creation");
        check(f.host.particles().instances().empty(),
            "Four empty CREATE PASSIVEOBJECT [PARTICLE FILENAME] operands emit no fabricated particle burst");
        const auto retired=f.host.cancelAll("p0-2 ownership cleanup");
        const auto &after=f.host.spawnedObjects().instances();
        check(retired.ok && !after.empty() &&
              std::all_of(after.begin(),after.end(),[](const auto &o){return o.state==ObjectState::Removed;}) &&
              std::any_of(f.world.events.begin(),f.world.events.end(),[](const auto &e){return e.kind=="act_spawn_retired";}),
            "Cancelling the owning ACT instance retires its spawned entities and records the retirement event");
    }
    {
        // P0-2 general motion. 1031 authors 38 STRAIGHT MOVE and 171 SET POS
        // FORCE blocks across 19,079 ACT files. Every field asserted here is
        // read from those bytes. The World displacement path is implemented,
        // but NO 1031 sample reaches bind/dispatch yet: every such ACT stays
        // blocked by unrelated TRIGGER/IF predicates or missing ANI closures.
        // Displacement therefore remains TYPE-FIRST, SAMPLE-LATER.
        WorldFixture f(pvf,assets,false);
        check(f.host.hasCommandConsumer("straight_move") && f.host.hasCommandConsumer("set_position_force"),
            "1031 STRAIGHT MOVE and SET POS FORCE register real World consumers instead of a missing-command gap");
        const auto stay=f.host.compile("monster/newmonsters/ranjerus/g3/action/stay1.act");
        size_t forceBlocks=0;
        bool uniform=false,reduce=false,useTarget=false,moveOwner=false;
        double zStart=0;
        if(stay.program) for(const auto &behavior:stay.program->behaviors)
            for(const auto &instruction:behavior.instructions)
                if(const auto *force=std::get_if<ActSetPositionForce>(&instruction.payload)) {
                    ++forceBlocks;
                    uniform|=force->moveUniform;reduce|=force->moveReduce;
                    useTarget|=force->useTargetPosition;moveOwner|=force->moveOwner;
                    zStart=force->start.value.z;
                }
        check(forceBlocks>0 && uniform && reduce && useTarget && moveOwner && zStart==150,
            "1031 SET POS FORCE keeps X/Y/Z START, USE TARGET POS, MOVE UNIFORM/REDUCE and MOVE ME as typed source facts");
        check(!diagnostic(stay.json().at("diagnostics"),"unsupported_set_pos_force_opcode"),
            "SET POS FORCE is no longer reported as an unexecuted behavior tag");
        // 127 of the 171 blocks use the owner-relative shape instead.
        const auto shoot=f.host.compile("monster/newmonsters/heaven/majorcamoka/action/shoot.act");
        bool ownerRelative=false;
        if(shoot.program) for(const auto &behavior:shoot.program->behaviors)
            for(const auto &instruction:behavior.instructions)
                if(const auto *force=std::get_if<ActSetPositionForce>(&instruction.payload))
                    ownerRelative|=force->useOwnerBase && force->useOwnerDirection;
        check(ownerRelative,
            "1031 SET POS FORCE keeps the owner-relative USE MY BASEPOS/USE MY DIRECTION shape as typed source facts");
        const auto cliff=f.host.compile("passiveobject/actionobject/map/risk_dungeon/cartelcommand/action/cliff_falling.act");
        bool timedJump=false;
        if(cliff.program) for(const auto &behavior:cliff.program->behaviors)
            for(const auto &instruction:behavior.instructions)
                if(const auto *move=std::get_if<ActStraightMove>(&instruction.payload))
                    timedJump|=move->axis==ActMoveAxis::Z && move->motion==ActMoveMotion::Jump &&
                        move->timeMs && *move->timeMs==4000 && move->damageHp==0 && !move->distance;
        check(timedJump,
            "1031 STRAIGHT MOVE keeps AXIS Z, MOVING MOTION JUMP and TIME 4000 as typed source facts");
        check(!diagnostic(cliff.json().at("diagnostics"),"unsupported_straight_move_opcode"),
            "STRAIGHT MOVE is no longer reported as an unexecuted behavior tag");
        const auto bridge=f.host.compile("passiveobject/actionobject/map/cartelcommand/action/bridge_up_fall.act");
        bool acceleratedY=false;
        if(bridge.program) for(const auto &behavior:bridge.program->behaviors)
            for(const auto &instruction:behavior.instructions)
                if(const auto *move=std::get_if<ActStraightMove>(&instruction.payload))
                    acceleratedY|=move->axis==ActMoveAxis::Y && move->releaseMotionDown &&
                        move->distance && *move->distance==850 && move->accelerate && *move->accelerate==1000 &&
                        move->damageHp==40 && !move->timeMs;
        check(acceleratedY,
            "1031 STRAIGHT MOVE keeps the Y-axis DISTANCE 850 / ACCELERATE 1000 / RELEASE MOTION shape without inventing a TIME");
        // Honest boundary: the consumer exists and the source is typed, but the
        // reachable 1031 samples still stop at unrelated TRIGGER/IF predicates,
        // so no World displacement is claimed from them yet.
        check(stay.program && cliff.program && bridge.program,
            "General motion compiles typed source instructions even when unrelated TRIGGER/IF tags still block the sample");
    }
    {
        // P0-2 PARTICLE factory: the same 1031 PTL bytes the previewer reads
        // now reach a real World-owned entity with a validated texture and an
        // independent [life time] clock. Anything unrecovered stays visible.
        WorldFixture f(pvf,assets,false);
        const auto program=f.host.compile(particleSource);
        check(program.ok && program.program && program.program->runtimeReady,
            "A 1031 frame-0 [PARTICLE] ACT is fully admitted through the shared PTL decoder and ANI/IMG texture closure");
        const auto &deps=program.program->dependencies;
        const auto ptl=std::find_if(deps.begin(),deps.end(),[](const ActDependency &d){return d.request.kind==ActResourceKind::Particle;});
        check(ptl!=deps.end() && ptl->found && ptl->runtimeSupported &&
              ptl->diagnostic.find("one-shot burst")!=std::string::npos &&
              ptl->diagnostic.find("5 particles")!=std::string::npos &&
              ptl->diagnostic.find("3 [object]")!=std::string::npos &&
              ptl->diagnostic.find("unrecovered")!=std::string::npos,
            "PTL admission reports its byte-derived count/textures/lifetime and explicitly lists unrecovered source fields");
        const auto unsupported=f.host.compile(unsupportedParticleSource);
        check(!unsupported.ok && diagnostic(unsupported.json().at("diagnostics"),"missing_resource_consumer"),
            "A PTL with an unrecovered [changing type] is rejected precisely instead of having its motion guessed");
        const auto decoded=readPtl(pvf,particleProgram);
        check(decoded.valid() && decoded.count==5 && decoded.lifeMs==500 && decoded.objects.size()==3 &&
              decoded.gravity==1500 && decoded.velocity[0][0]==400 && decoded.velocity[0][1]==400 &&
              decoded.velocity[2][0]==80 && decoded.velocity[2][1]==80,
            "The World factory and standalone previewer decode identical 1031 PTL source bytes (5/500ms/3 ANI/gravity/velocity)");
        check(!decoded.fullyConsumed() &&
              std::all_of(decoded.diagnostics.begin(),decoded.diagnostics.end(),[](const Json &j){
                  return j.is_object() && j.contains("field") && j.contains("reason") &&
                         !j.at("field").get<std::string>().empty() && !j.at("reason").get<std::string>().empty();}) &&
              std::any_of(decoded.diagnostics.begin(),decoded.diagnostics.end(),[](const Json &j){
                return j.value("field",std::string()).find("rotation")!=std::string::npos;}),
            "Unconsumed source fields are explicit diagnostics, never silently dropped or called equivalent");
        check(!ptlFieldConsumed("[unknown behavior]") && ptlFieldConsumed("[life time]") &&
              ptlFieldStructural("[/object]") && !ptlFieldStructural("[unknown behavior]"),
            "Unknown PTL tags classify as gaps while structural closers are not behavioral fields");
        f.bind(particleSource,41);f.ticks(1);
        const auto &particles=f.host.particles().instances();
        check(particles.size()==5,
            "A frame-0 [PARTICLE] command emits exactly the source [maximum create number] of real World entities");
        check(std::all_of(particles.begin(),particles.end(),[](const auto &p){
                return p.program==particleProgram && !p.animation.empty() && !p.image.empty() && p.frame==-1 &&
                       p.actInstanceId==41 && p.actionId==141 && p.lifeUs==500000 && p.alive() &&
                       p.alpha()>0 && p.alpha()<=1 && p.json().contains("offset");}),
            "Each World particle retains its source PTL, validated ANI/IMG texture, ACT/action ownership and byte-derived lifetime");
        check(std::all_of(particles.begin(),particles.end(),[](const auto &p){
                return p.offsetX==0 && p.offsetY==0 && p.offsetZ==0 &&
                       std::isfinite(p.x) && std::isfinite(p.y) && std::isfinite(p.z) &&
                       p.direction==1;}),
            "Particle XYZ is based on the owner's immutable coordinate receipt plus signed source offset and facing");
        check(std::all_of(particles.begin(),particles.end(),[](const auto &p){
                const auto at=p.position();
                return at!=(std::array<double,3>{p.x,p.y,p.z}) && p.json().contains("position") &&
                       p.json().contains("velocity") && p.json().contains("gravity");}),
            "Implemented straight/keep-last velocity and gravity change each particle's source-clock position");
        check(std::any_of(f.world.events.begin(),f.world.events.end(),[](const auto &e){return e.kind=="act_particle_spawn";}),
            "The World event log records the ACT-owned particle burst");
        std::set<uint64_t> serials;for(const auto &p:particles)serials.insert(p.serial);
        check(serials.size()==particles.size() && *serials.begin()>0,
            "Every emitted particle receives its own distinct World serial");
        // The action's BASE ANI is only 80 ms; its PTL lifetime is 500 ms.
        // Natural completion runs cleanup but must not truncate the burst.
        f.ticks(12);
        check(f.host.particles().instances().size()==5 && f.host.particles().instances().front().ageUs>0,
            "Natural completion of the emitting action does not retire particles that still have their own [life time] clock");
        f.ticks(40);
        check(f.host.particles().instances().empty() &&
              std::any_of(f.world.events.begin(),f.world.events.end(),[](const auto &e){return e.kind=="act_particle_expired";}),
            "Particles expire on their own 500 ms source clock with a real World retirement event");
    }
    {
        WorldFixture f(pvf,assets,false);
        const auto compiled=f.host.compile(particleOffsetSource);
        check(compiled.ok && compiled.program->runtimeReady,"A source [PARTICLE] with a non-zero Z offset is admitted");
        f.bind(particleOffsetSource,42);f.ticks(1);
        const auto &particles=f.host.particles().instances();
        check(!particles.empty() && std::all_of(particles.begin(),particles.end(),[](const auto &p){
                return p.offsetZ==60 && p.z!=0 && std::isfinite(p.x) && std::isfinite(p.y) &&
                       std::isfinite(p.z);}),
            "The signed source [PARTICLE] Z=60 offset is retained in the owner-based World coordinate receipt");
        const auto retired=f.host.cancel(42,"p0-2 particle ownership cleanup");
        check(retired.ok && f.host.particles().instances().empty() &&
              std::any_of(f.world.events.begin(),f.world.events.end(),[](const auto &e){return e.kind=="act_particle_retired";}),
            "Explicit cancellation of the owning ACT instance retires its particles and records the retirement event");
    }
    {
        WorldFixture f(pvf,assets,false);
        f.bind(particleSource,43);f.ticks(12);
        check(f.host.particles().instances().size()==5,"Transient particle burst is live before the World clock reset");
        f.host.resetCancelledClock();
        check(f.host.particles().instances().empty(),
            "Transient ACT-emitted PTL bursts never survive a cancelled-clock reset");
        WorldFixture completed(pvf,assets,false);
        completed.bind(particleSource,45);completed.ticks(12);
        check(completed.host.cancel(45,"cancel completed particle owner").ok &&
              completed.host.particles().instances().empty(),
            "Explicit per-instance cancellation retires particles after their source action completed");
        WorldFixture interrupted(pvf,assets,false);
        interrupted.bind(particleSource,46);interrupted.ticks(1);
        interrupted.world.monsters.front().dead=true;
        interrupted.ticks(1);
        check(interrupted.host.particles().instances().empty(),
            "Owner lifecycle exit retires its particles through the ACT cancellation path");
        WorldFixture g(pvf,assets,false);
        g.bind(particleSource,44);g.ticks(1);
        check(g.host.cancelAll("p0-2 particle factory teardown").ok && g.host.particles().instances().empty() &&
              std::any_of(g.world.events.begin(),g.world.events.end(),[](const auto &e){return e.kind=="act_particle_retired";}),
            "cancelAll reclaims bursts whose emitting action already completed naturally");
    }
    {
        // Bounded, ownership-scoped particle container independent of World.
        auto admission=std::make_shared<ActParticleAdmission>();
        admission->program=particleProgram;admission->count=7;admission->lifeUs=1000;
        admission->alphaStart=100;admission->alphaEnd=0;
        admission->objects.push_back({"a.ani","a.img",-1});
        ActParticleEmit emit;emit.admission=admission;emit.program=particleProgram;
        emit.actInstanceId=9;emit.actionId=10;emit.sequence=11;
        emit.x=1;emit.y=2;emit.z=3;emit.offsetX=4;emit.offsetY=5;emit.offsetZ=6;
        ActParticleSystem system;
        check(system.emit(emit)==7 && system.instances().size()==7 &&
              std::abs(system.instances().front().alpha()-1.0)<1e-9 && system.aliveCount()==7,
            "Particle emission is a bounded one-shot burst with a source alpha endpoint");
        check(system.advance(500).empty() && std::abs(system.instances().front().alpha()-0.5)<1e-9,
            "Each particle advances its own clock and its alpha follows the two source [transparent value] endpoints");
        check(system.advance(500).size()==7 && system.instances().empty(),
            "Lifetime expiry removes expired entities and returns their retired serials");
        admission->count=1000;
        check(system.emit(emit)==int(ActParticleSystem::maximumInstances) &&
              system.instances().size()==ActParticleSystem::maximumInstances,
            "A source count beyond the World budget is clamped, not silently truncated to zero");
        check(system.retireActInstance(9)==ActParticleSystem::maximumInstances && system.instances().empty(),
            "Explicit ACT instance ownership retirement reclaims every one of its particles");
        const auto sample=system.emit(emit);
        check(sample>0 && system.instances().front().json().contains("program") &&
              system.instances().front().json().contains("alpha") &&
              system.instances().front().json().contains("alive"),
            "World particle receipts expose source, alpha and liveness without a renderer");
    }
    {
        // The main scene must not merely own particle records: a hidden real
        // SDL renderer consumes one ACT particle through its source ANI/IMG.
        const bool ownsVideo=!(SDL_WasInit(SDL_INIT_VIDEO)&SDL_INIT_VIDEO);
        if(ownsVideo && SDL_InitSubSystem(SDL_INIT_VIDEO)!=0)
            throw std::runtime_error(std::string("SDL video init: ")+SDL_GetError());
        RendererOptions options;options.shown=false;options.vsync=false;options.width=320;options.height=200;
        Renderer renderer(assets,options);
        auto pixels=[&] {
            const auto size=renderer.outputSize();Bytes bytes(size_t(size[0])*size[1]*4);
            if(SDL_RenderReadPixels(renderer.raw(),nullptr,SDL_PIXELFORMAT_RGBA32,bytes.data(),size[0]*4)!=0)
                throw std::runtime_error(std::string("SDL readback: ")+SDL_GetError());
            return sha256(bytes);
        };
        const auto drawProgram=readPtl(pvf,particleProgram);
        ActParticleInstance draw;
        draw.program=particleProgram;draw.animation=drawProgram.objects.front().animation;draw.image="";draw.frame=-1;
        draw.x=150;draw.y=110;draw.z=0;draw.direction=1;draw.lifeUs=1000000;draw.ageUs=0;
        draw.alphaStart=100;draw.alphaEnd=100;
        renderer.begin();renderer.ui();const auto empty=pixels();
        renderer.begin();renderer.ui();renderer.actParticle(draw,0,0);const auto drawn=pixels();
        check(drawn!=empty && renderer.errors.empty(),
            "The real hidden SDL renderer draws an ACT particle from its source ANI/IMG lease");
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"evidence","inferred World host; current-PVF source fixtures"},
        {"scope","Real World actors, status lifecycle/contact ledgers, hit-stop/external clock, entity generations/events and same-tick prepared-World ACT import; ACT-owned objects are real World entities and ACT PTL particles have a real hidden-SDL renderer consumer, but object contact settlement and OBJ-internal PTL remain P0-3; diagnostic status setup is not a normal skill chain, audio-device/controller activation/CharacterStore disk restore remain separate"}};
}
} // namespace dnf
