#include "dnf/act_world_host.hpp"
#include "dnf/axis_motion.hpp"
#include "dnf/monster_behavior.hpp"
#include "dnf/monster_spawn.hpp"
#include "dnf/session.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *nagorMap="map/bakalcastle/15076nagor.map";
constexpr const char *jenaMap="map/gentsouthgate/(4,0)normal.map";
constexpr int nagorId=56721,jenaId=56503;
constexpr uint64_t generation=23;

struct SourceActionChecks {
    Json checks=Json::array();
    void operator()(bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Source action World: ")+message);
        checks.push_back(message);
    }
};
Script sourceDungeon(Pvf &pvf,int id) {
    const auto registry=pvf.script("dungeon/dungeon.lst");
    std::string selected;
    for(size_t i=0;i+1<registry.tokens.size();++i) {
        const auto &key=registry.tokens[i].at("value"),&value=registry.tokens[i+1].at("value");
        if(!key.is_number_integer() || key!=id || !value.is_string()) continue;
        if(!selected.empty()) throw std::runtime_error("Test DGN registration is ambiguous");
        selected=normalize((std::filesystem::u8path(registry.path).parent_path()/
            std::filesystem::u8path(value.get<std::string>())).generic_u8string());
    }
    if(selected.empty()) throw std::runtime_error("Test MAP DGN is not registered");
    return pvf.script(selected);
}
struct SourceActionFixture {
    World world;
    Script map,dungeon;
    int dungeonId=0,basisLevel=0;
    EntityHandle owner;
    std::string staticIdentity;
    // Real MAP records, registry MOBs and DGN levels enter the production
    // factory unchanged. The wide collision plane and legacy HP/combat rules
    // isolate ACT service logic; they are explicitly not regional capability,
    // source-derived monster balance or a complete real Scene acceptance test.
    SourceActionFixture(Pvf &pvf,Assets &assets,const RegionCatalog &catalog,
                        const std::string &mapPath,int sourceId,bool speech=false)
        :world(pvf,assets),map(pvf.script(mapPath)) {
        const auto dungeonValues=map.values("[dungeon]");
        if(dungeonValues.size()!=1 || !dungeonValues[0].is_number_integer())
            throw std::runtime_error("Test MAP needs one authored dungeon ID");
        dungeonId=dungeonValues[0].get<int>();dungeon=sourceDungeon(pvf,dungeonId);
        const auto basis=dungeon.values("[basis level]");
        if(basis.size()!=1 || !basis[0].is_number_integer() || basis[0]<1 || basis[0]>std::numeric_limits<int>::max())
            throw std::runtime_error("Test DGN needs an explicit valid basis level");
        basisLevel=basis[0].get<int>();
        const auto background=dungeon.values("[background pos]");
        if(background.size()!=1 || !background[0].is_number()) throw std::runtime_error("Test DGN background is unavailable");
        world.combat=true;world.freezeAi=false;world.mapWidth=20000;
        world.walkRects={{12,185,19976,1200}};world.blockedRects.clear();
        world.player.x=world.player.px=6000;world.player.y=world.player.py=500;world.player.dir=1;
        staticIdentity="source-action-world-test-static:"+sha256(assets.staticBytes("audio.xml"));
        world.configureSourceActions(staticIdentity,speech);
        std::vector<Event> prepared;
        world.monsters=prepareSourceMonsterSpawns(world,catalog,map,dungeonId,basisLevel,background[0].get<double>(),
            "legacy-demo-v1","legacy-snapshot-damage-v1",DemoBalance{},&prepared);
        world.events.insert(world.events.end(),prepared.begin(),prepared.end());
        world.synchronizeEntityHandles();
        for(const auto &actor:world.monsters) if(actor.sourceId==sourceId) {
            if(owner) throw std::runtime_error("Test MAP has repeated selected monster");owner=actor.handle;
        }
        if(!owner) throw std::runtime_error("Test MAP factory did not produce selected monster");
    }
    Actor &actor() {
        auto *result=world.resolveActor(owner);
        if(!result) throw std::runtime_error("Selected factory actor was retired");return *result;
    }
    MonsterActionRoute route(Pvf &pvf,const std::string &state,int index=0) {
        return selectMonsterAction(pvf,pvf.script(actor().monsterPath),state,index);
    }
    void ticks(size_t count) {for(size_t i=0;i<count;++i)world.advanceSingleTick();}
    uint64_t running() const {
        for(const auto &[id,instance]:world.actHost()->instances())
            if(instance.owner==owner && instance.status==ActInstanceStatus::Running) return id;
        throw std::runtime_error("Factory actor has no running source action: "+world.sourceActionDiagnostics().dump());
    }
    Json summary() const {
        Json actors=Json::array();for(const auto &actor:world.monsters)actors.push_back(saveActor(actor,world.nowMs()));
        return {{"actors",actors},{"simulation",world.simulationCheckpoint()},
            {"host",world.actHost()->snapshot(generation)},{"service",world.sourceActionDiagnostics()},{"events",world.eventLog()}};
    }
};
size_t boundaryResults(const World &world,EntityHandle owner,const std::string &kind,const std::string &reason="") {
    const auto diagnostics=world.sourceActionDiagnostics();
    return size_t(std::count_if(diagnostics.begin(),diagnostics.end(),[&](const Json &entry) {
        return entry.value("kind",std::string())==kind && entry.at("owner")==owner.json() &&
            (reason.empty() || entry.value("reason",std::string())==reason);
    }));
}
Json injectSourceStun(SourceActionFixture &fixture,Pvf &pvf) {
    // Diagnostic status import only. No Tau AI/learned-skill/monster-resistance
    // completion is claimed by this local source30/level0/1000ms fixture.
    auto &world=fixture.world;const auto source=readAttackStatuses(pvf.script("monster/tau/attackinfo/heading.atk"));
    StatusResistanceSnapshot resistance;resistance.packageIdentity=pvf.identity();resistance.level=fixture.basisLevel;
    resistance.trace.push_back({{"classification","diagnostic-zero-resistance-target"}});
    const auto watermark=world.simulationCheckpoint().at("status_instance_ids");
    const auto attack=world.idSources().attacks.next();
    for(uint64_t seed=0;seed<256;++seed) {
        StatusHost host(pvf.identity(),StunStatusPolicy::inferredFlatChanceStunV1());host.mergeInstanceWatermark(watermark);
        Pcg32 random(seed,17);StatusRequest request;request.attacker=world.player.handle;request.attackerLevel=world.characterLevel;
        request.target={fixture.owner,resistance,false,Json::object()};request.attackInstance=attack;request.attack=source;
        auto prepared=host.prepare(request,uint64_t(world.nowMs()),random);
        if(!prepared.ready()) throw std::runtime_error("Source-action stun fixture rejected: "+prepared.receipt.dump());
        if(!prepared.receipt.at("outcomes")[0].at("procced").get<bool>()) continue;
        host.publish(std::move(prepared),random);const auto bundle=host.snapshotTarget(fixture.owner,uint64_t(world.nowMs()),generation);
        world.restoreStatusCheckpoint(bundle,fixture.owner,fixture.owner,generation);return bundle;
    }
    throw std::runtime_error("Source-action fixture did not proc in its bounded diagnostic seed search");
}
double sourceXSpeed(const ActProgram &program) {
    for(const auto &behavior:program.behaviors)for(const auto &instruction:behavior.instructions)
        if(const auto *speed=std::get_if<ActSetSpeed>(&instruction.payload))if(speed->x && *speed->x!=0)return *speed->x;
    throw std::runtime_error("Selected source action has no nonzero X speed");
}
} // namespace

Json runSourceActionWorldTests(Pvf &pvf,Assets &assets) {
    SourceActionChecks check;Json samples=Json::object();RegionCatalog catalog(pvf,assets);
    {
        SourceActionFixture fixture(pvf,assets,catalog,nagorMap,nagorId);
        auto &world=fixture.world;const auto route=fixture.route(pvf,"stay");fixture.actor().dir=-1;
        const auto rawSpawns=parseMonsterSpawns(fixture.map.values("[monster]"));
        const auto spawn=std::find_if(rawSpawns.begin(),rawSpawns.end(),[](const MonsterSpawn &entry){return entry.id==nagorId;});
        check(route.ok && route.engine==MonsterActionEngine::Act && spawn!=rawSpawns.end() &&
            fixture.actor().sourceStats.at("spawn").at("raw")==spawn->raw &&
            fixture.actor().sourceStats.at("spawn").at("map_provenance")==fixture.map.source &&
            fixture.actor().sourceStats.at("spawn").at("basis_level")==fixture.basisLevel &&
            fixture.actor().sourceStats.at("policy")=="legacy-demo-v1" && !world.actHost()->ownsActor(fixture.owner),
            "Nagor is prepared by the normal complete MAP factory with real DGN level/provenance and an explicit legacy balance fixture before service discovery");
        const auto beforePausedBind=world.randomStreams().snapshot();world.freezeAi=true;fixture.ticks(3);
        check(fixture.actor().dir==-1 && !world.actHost()->ownsActor(fixture.owner) &&
            boundaryResults(world,fixture.owner,"source_action_bound")==0 &&
            world.randomStreams().snapshot()==beforePausedBind,
            "AI pause defers automatic factory binding and OnSet rather than executing source commands or drawing RNG before resume");
        world.freezeAi=false;
        const auto x=fixture.actor().x,y=fixture.actor().y;fixture.ticks(1);const auto id=fixture.running();
        const auto &instance=world.actHost()->instances().at(id);const auto actual=pvf.script(route.resolvedPath);
        const auto mob=pvf.script(fixture.actor().monsterPath);
        check(fixture.actor().dir==1 && fixture.actor().x==x && fixture.actor().y==y &&
            world.actHost()->ownsActor(fixture.owner) && instance.clockMode==ActClockMode::ExternalAnimationDelta &&
            instance.program->source.packageIdentity==pvf.identity() && instance.program->source.memberPath==route.resolvedPath &&
            instance.program->source.memberSha256==sha256(actual.rawBytes) && instance.program->original.rawBytes==actual.rawBytes &&
            route.source.packageIdentity==pvf.identity() && route.source.memberPath==fixture.actor().monsterPath &&
            route.source.memberSha256==sha256(mob.rawBytes) && route.source.byteLength==5 &&
            route.source.byteOffset+route.source.byteLength<=mob.rawBytes.size() &&
            std::any_of(mob.tokens.begin(),mob.tokens.end(),[&](const Json &token) {
                return token.at("offset")==route.source.byteOffset && token.at("value")==route.literalPath;
            }) &&
            boundaryResults(world,fixture.owner,"source_action_bound")==1,
            "A World-owned boundary automatically selects MOB stay and executes its actual OnSet RIGHT with exact PVF SourceRefs, without a direct host bind");
        fixture.ticks(3);
        check(boundaryResults(world,fixture.owner,"source_action_bound")==1 && fixture.actor().dir==1 && fixture.actor().x==x,
            "Factory discovery and OnSet occur once across later fixed ticks while source-owned actors bypass legacy AI movement");
        samples["nagor_route"]=route.json();samples["nagor_service"]=world.sourceActionDiagnostics();
    }
    {
        for(const int sourceId:{nagorId,jenaId}) {
            Json expected;
            for(const int rate:{30,60,144,0}) {
                SourceActionFixture fixture(pvf,assets,catalog,sourceId==nagorId?nagorMap:jenaMap,sourceId);
                if(sourceId==nagorId)fixture.actor().dir=-1;
                else {fixture.ticks(1);fixture.actor().dir=1;fixture.world.requestSourceMonsterAction(fixture.owner,"attack",4);}
                constexpr int64_t totalNs=2000000000;
                if(rate) {
                    int64_t previous=0;for(int frame=1;frame<=rate*2;++frame) {
                        const auto end=totalNs*frame/(rate*2);fixture.world.advance(end-previous);previous=end;
                    }
                } else {
                    fixture.world.advance(totalNs,3);while(fixture.world.pendingTicks())fixture.world.advance(0,3);
                }
                const auto result=fixture.summary();if(expected.is_null())expected=result;
                check(result==expected,"Actual Nagor/Jena factory service actor state, motion, host clock, IDs, RNG and events agree at 30/60/144 FPS and budgeted catch-up ticks");
            }
            samples[sourceId==nagorId?"nagor_fixed_tick_state":"jena_fixed_tick_state"]=expected;
        }
    }
    {
        SourceActionFixture fixture(pvf,assets,catalog,jenaMap,jenaId,true);auto &world=fixture.world;
        const auto route=fixture.route(pvf,"attack",4);fixture.ticks(1);fixture.actor().dir=1;
        check(route.ok && route.engine==MonsterActionEngine::Act && route.sourceActionIndex==4 &&
            route.cooldownMs && *route.cooldownMs==10000 && route.cooldownSource &&
            route.attackInfoLiteral && route.attackInfoLiteral->empty(),
            "Jena retains the actual action-list slot4, its paired 10000ms source cooldown and explicitly empty paired attack-info operand");
        const auto beforeBind=world.nowMs();const auto x=fixture.actor().x;
        world.requestSourceMonsterAction(fixture.owner,"attack",4);fixture.ticks(1);const auto id=fixture.running();
        const auto program=world.actHost()->instances().at(id).program;const auto speed=sourceXSpeed(*program);
        const auto dt=int32_t(FixedStepClock::millisecondsAtTick(uint64_t(world.tick))-FixedStepClock::millisecondsAtTick(uint64_t(world.tick-1)));
        AxisMotion movement{float(speed),0,-1};const auto expected=x+double(advanceAxisMotion(movement,dt));
        check(program->source.memberPath==route.resolvedPath && speed==400 && world.actHost()->controlsMovement(fixture.owner) &&
            std::abs(fixture.actor().x-expected)<1e-7 && world.actHost()->instances().at(id).animationUs==uint64_t(dt)*1000,
            "An explicit boundary action request executes Jena's actual Dash400 source speed once through the World-owned fixed-tick host");
        const auto rng=world.randomStreams().snapshot();const auto ids=world.idSources().snapshot();
        world.requestSourceMonsterAction(fixture.owner,"attack",4);fixture.ticks(1);
        check(world.randomStreams().snapshot()==rng && world.idSources().snapshot()==ids && fixture.running()==id &&
            boundaryResults(world,fixture.owner,"source_action_blocked","source_action_cooldown")==1,
            "A repeated source slot4 request is rejected by its cooldown without allocating an action or drawing from World RNG");
        uint64_t duration=0;for(const auto delay:program->motion->frameDurationsMs)duration+=uint64_t(delay);
        size_t exitTicks=0;
        while(world.actHost()->instances().at(id).status==ActInstanceStatus::Running && exitTicks++<120)fixture.ticks(1);
        check(duration==600 && world.actHost()->instances().at(id).status==ActInstanceStatus::Cancelled &&
            world.actHost()->instances().at(id).animationUs==duration*1000 &&
            !world.actHost()->controlsMovement(fixture.owner) && fixture.actor().animation!="act",
            "Dash naturally reaches all authored 600ms and releases its owned velocity and presentation without inventing a frame3 stop behavior");
        const auto stoppedX=fixture.actor().x;fixture.ticks(5);
        const auto beforeRetry=world.randomStreams().snapshot();world.requestSourceMonsterAction(fixture.owner,"attack",4);fixture.ticks(1);
        check(fixture.actor().x==stoppedX && world.randomStreams().snapshot()==beforeRetry &&
            boundaryResults(world,fixture.owner,"source_action_blocked","source_action_cooldown")==2,
            "Natural action exit leaves no residual or legacy movement and does not reset the original slot cooldown");
        while(world.nowMs()<beforeBind+*route.cooldownMs)fixture.ticks(1);
        world.requestSourceMonsterAction(fixture.owner,"attack",4);fixture.ticks(1);
        check(fixture.running()!=id && world.actHost()->controlsMovement(fixture.owner) && fixture.actor().x>stoppedX,
            "The same source slot becomes executable after its own authored cooldown expires");
        const auto oldOwner=fixture.owner;const auto beforeScene=world.randomStreams().snapshot();world.changeScene();
        check(!world.actHost()->ownsActor(oldOwner) && !world.actHost()->controlsMovement(oldOwner) &&
            world.actHost()->speechBubbles().empty() && world.randomStreams().snapshot()==beforeScene &&
            !static_cast<const World &>(world).resolveActor(oldOwner),
            "Scene cleanup cancels actual service-owned actions and movement, clears presentation and retires the old actor generation without RNG work");
        samples["jena_route"]=route.json();samples["jena_service"]=world.sourceActionDiagnostics();
    }
    {
        SourceActionFixture fixture(pvf,assets,catalog,jenaMap,jenaId);auto &world=fixture.world;
        fixture.ticks(1);fixture.actor().dir=1;fixture.actor().hitStopTicks=3;const auto x=fixture.actor().x;
        world.requestSourceMonsterAction(fixture.owner,"attack",4);fixture.ticks(3);const auto id=fixture.running();
        check(fixture.actor().x==x && fixture.actor().hitStopped &&
            world.actHost()->instances().at(id).animationUs==0 && world.actHost()->instances().at(id).elapsedMs==50,
            "The World automatically supplies zero ACT animation delta during three real hit-stop ticks while simulation time continues");
        fixture.ticks(1);const auto animationUs=world.actHost()->instances().at(id).animationUs;
        check(!fixture.actor().hitStopped && fixture.actor().x>x && animationUs>0,
            "Leaving hit-stop automatically resumes the mutually exclusive source animation clock and one movement integration");
        const auto status=injectSourceStun(fixture,pvf);const auto stoppedX=fixture.actor().x;
        const auto random=world.randomStreams().snapshot();fixture.ticks(5);
        check(world.statusStunned(fixture.owner) && fixture.actor().x==stoppedX &&
            world.actHost()->instances().at(id).animationUs==animationUs &&
            world.actHost()->instances().at(id).elapsedMs>50 && world.randomStreams().snapshot()==random,
            "An independent real-source diagnostic stun freezes the service's action clock and movement without advancing animation or rerolling World RNG");
        size_t waited=0;while(world.statusStunned(fixture.owner) && waited++<70)fixture.ticks(1);
        check(!world.statusStunned(fixture.owner) && fixture.actor().x>stoppedX &&
            world.actHost()->instances().at(id).status==ActInstanceStatus::Running &&
            world.actHost()->instances().at(id).animationUs>animationUs && world.randomStreams().snapshot()==random,
            "Source millisecond stun expiry resumes the still-running Dash without treating paused simulation age as animation completion");
        const auto beforeAiPauseX=fixture.actor().x;
        const auto beforeAiPauseAnimation=world.actHost()->instances().at(id).animationUs;
        const auto beforeAiPauseElapsed=world.actHost()->instances().at(id).elapsedMs;
        world.freezeAi=true;fixture.ticks(3);
        check(fixture.actor().x==beforeAiPauseX && world.actHost()->instances().at(id).animationUs==beforeAiPauseAnimation &&
            world.actHost()->instances().at(id).elapsedMs==beforeAiPauseElapsed+50 &&
            world.actHost()->controlsMovement(fixture.owner) && world.randomStreams().snapshot()==random,
            "AI pause supplies zero external animation delta and suppresses its ACT-owned Dash movement while simulation age advances by three fixed ticks");
        world.freezeAi=false;fixture.ticks(1);
        check(fixture.actor().x>beforeAiPauseX && world.actHost()->instances().at(id).animationUs>beforeAiPauseAnimation,
            "Resuming AI advances the retained source action clock and actual Dash position once again");
        samples["diagnostic_source_stun"]=status;
    }
    {
        SourceActionFixture fixture(pvf,assets,catalog,jenaMap,jenaId);auto &world=fixture.world;
        fixture.ticks(1);fixture.actor().dir=1;
        world.requestSourceMonsterAction(fixture.owner,"attack",4);fixture.ticks(1);const auto id=fixture.running();
        // Diagnostic existing capture-state input only. The present World
        // follow offset is exercised without claiming a native grab formula
        // or a newly implemented player grab-controller acquisition chain.
        fixture.actor().capturedBy=0;fixture.ticks(1);
        check(fixture.actor().x==world.player.x+world.player.dir*65 && fixture.actor().y==world.player.y &&
            fixture.actor().z==45 && !world.actHost()->controlsMovement(fixture.owner) &&
            world.actHost()->instances().at(id).status==ActInstanceStatus::Cancelled,
            "A captured source-factory Jena still follows the existing World grab state and cancels its real ACT velocity instead of bypassing capture handling");
        world.player.x+=40;world.player.px=world.player.x;fixture.ticks(1);
        const auto releasedX=fixture.actor().x;
        fixture.actor().capturedBy=-1;fixture.ticks(5);
        check(releasedX==world.player.x+world.player.dir*65 && fixture.actor().x==releasedX &&
            !world.actHost()->controlsMovement(fixture.owner) &&
            world.actHost()->instances().at(id).status==ActInstanceStatus::Cancelled,
            "Capture keeps following a moved player and releasing it cannot revive cancelled source Dash speed or legacy movement");
    }
    return {{"status","pass"},{"count",check.checks.size()},{"checks",check.checks},{"samples",samples},
        {"scope","Production MAP factory and World-owned source-action boundary/tick/cooldown/cleanup service; explicit wide collision plane and legacy balance fixture"},
        {"event_ai_consumer_complete",false},{"whole_monster_or_region_complete",false},
        {"status_injection_is_normal_combat",false},{"frontend_and_native_dynamic_comparison","pending user"}};
}
} // namespace dnf
