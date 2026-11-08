#include "dnf/combat.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/monster_behavior.hpp"
#include "dnf/session.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *eventMob="monster/newmonsters/heaven/jena/jena.mob";
struct EventChecks {
    Json checks=Json::array();
    void operator()(bool okay,const char *message) {
        if(!okay) throw std::runtime_error(std::string("Event.ai World: ")+message);
        checks.push_back(message);
    }
};
struct EventFixture {
    World world;
    EntityHandle owner;
    MonsterEventAiRoute route;
    std::shared_ptr<const MonsterEventAiProgram> program;
    // One real source MOB/AI/ACT, an explicitly diagnostic collision plane and
    // legacy10000HP isolate accepted-contact scheduling from MOB balance and
    // regional admission. Actual damage below always uses World normalAttack.
    EventFixture(Pvf &pvf,Assets &assets,bool install=true):world(pvf,assets) {
        world.combat=true;world.mapWidth=20000;world.walkRects={{12,185,19976,1200}};
        world.player.x=world.player.px=560;world.player.y=world.player.py=344;world.player.dir=1;
        Actor actor;actor.id=17;actor.sourceId=56503;actor.monsterPath=eventMob;
        actor.x=actor.px=640;actor.y=actor.py=344;actor.dir=-1;actor.hp=actor.maxHp=10000;
        world.monsters.push_back(std::move(actor));world.synchronizeEntityHandles();owner=world.monsters[0].handle;
        world.configureSourceActions("event-ai-world-static:"+sha256(assets.staticBytes("audio.xml")));
        route=selectMonsterEventAi(pvf,pvf.script(eventMob),"easy");
        if(!route.ok) throw std::runtime_error("Jena actual Event.ai source route unavailable");
        const auto compiled=compileMonsterEventAi(pvf,pvf.script(route.resolvedPath),MonsterEventAiPolicy::inferredIntegralChanceV1());
        if(!compiled.ok) throw std::runtime_error("Jena actual Event.ai compilation unavailable");program=compiled.program;
        if(install && !world.configureMonsterEventAi(owner,"easy",MonsterEventAiPolicy::inferredIntegralChanceV1()))
            throw std::runtime_error("Jena Event.ai install failed: "+world.monsterEventAiState().dump());
    }
    Actor &actor() {
        auto *actor=world.resolveActor(owner);if(!actor)throw std::runtime_error("Event.ai fixture actor retired");return *actor;
    }
    void ticks(size_t count) {for(size_t i=0;i<count;++i)world.advanceSingleTick();}
    Json pending() const {return world.monsterEventAiState().at("pending");}
    Json outcomes() const {
        const auto state=world.monsterEventAiState();
        Json rows=Json::array();for(const auto &row:state.at("diagnostics"))
            if(row.value("kind",std::string())=="monster_event_ai_outcome")rows.push_back(row);
        return rows;
    }
    void ordinaryHit() {
        const auto hp=actor().hp;
        const auto events=pending().size();
        world.normalAttack();
        for(size_t step=0;step<180 && pending().size()==events;++step)world.advanceSingleTick();
        if(actor().hp>=hp || pending().size()!=events+1)
            throw std::runtime_error("Real Jena ordinary contact did not publish one accepted hit: "+world.eventLog().dump());
    }
    void settle() {
        for(size_t i=0;i<360 && !pending().empty();++i)world.advanceSingleTick();
        if(!pending().empty())throw std::runtime_error("Accepted Event.ai hit did not reach a terminal source outcome");
    }
    uint64_t running() const {
        for(const auto &[id,instance]:world.actHost()->instances())
            if(instance.owner==owner && instance.status==ActInstanceStatus::Running)return id;
        throw std::runtime_error("Event.ai did not bind a running source action");
    }
    Json summary() const {
        return {{"simulation",world.simulationCheckpoint()},{"player",saveActor(world.player,world.nowMs())},
            {"actor",saveActor(world.monsters[0],world.nowMs())},{"events",world.eventLog()},
            {"event_ai",world.monsterEventAiState()},{"host",world.actHost()->snapshot(31)}};
    }
};
uint64_t seedFor(EventFixture &fixture,bool selected,bool secondPass=false) {
    MonsterEventAiContext context;context.owner=fixture.owner;context.tick=1;
    context.acceptedHit=MonsterAcceptedHit{1,fixture.world.player.handle};
    for(uint64_t seed=0;seed<4096;++seed) {
        RandomStreams streams(seed);const auto &stream=streams.stream(RandomDomain::MonsterEventAi,fixture.owner.id);
        const auto first=evaluateMonsterEventAi(*fixture.program,context,stream,
            [](EntityHandle,int)->std::optional<bool>{return false;});
        if(!first.ok || !first.candidateRandom || (*first.returnedActionIndex==4)!=selected)continue;
        if(secondPass) {
            const auto second=evaluateMonsterEventAi(*fixture.program,context,*first.candidateRandom,
                [](EntityHandle,int)->std::optional<bool>{return false;});
            if(!second.ok || second.returnedActionIndex!=4)continue;
        }
        return seed;
    }
    throw std::runtime_error("Diagnostic bounded seed search did not reach desired real source chance branches");
}
const Json *traceKind(const Json &outcome,const char *kind) {
    for(const auto &row:outcome.at("evaluation").at("trace"))if(row.at("kind")==kind)return &row;
    return nullptr;
}
bool hasAiStream(const World &world) {
    const auto random=world.randomStreams().snapshot();
    for(const auto &stream:random.at("streams"))if(stream.at("domain")=="monster_event_ai")return true;
    return false;
}
} // namespace

Json runMonsterEventAiWorldTests(Pvf &pvf,Assets &assets) {
    EventChecks check;Json samples=Json::object();
    {
        EventFixture fixture(pvf,assets,false);auto &world=fixture.world;
        const auto before=world.simulationCheckpoint();
        check(!world.configureMonsterEventAi(fixture.owner,"normal",MonsterEventAiPolicy::inferredIntegralChanceV1()) &&
            world.simulationCheckpoint()==before && world.monsterEventAiState().at("bindings").empty(),
            "An absent explicit difficulty cannot install AI, change actor identity, allocate IDs or create a random stream");
        check(world.configureMonsterEventAi(fixture.owner,"easy",MonsterEventAiPolicy::inferredIntegralChanceV1()) &&
            world.simulationCheckpoint()==before,
            "Successful exact-source Event.ai installation performs no live ID, RNG, HP or tick mutation");
        const auto ids=world.idSources().snapshot(),random=world.randomStreams().snapshot();
        const auto hp=fixture.actor().hp;
        // Jena has two distinct valid standing hurt motions. Diagnostic
        // damage chooses that presentation too, using only its saved domain.
        auto expectedRandom=world.randomStreams();
        expectedRandom.stream(RandomDomain::MonsterHurt,0).bounded(2);
        world.diagnosticHit(17,1,0,0,1,{});
        check(fixture.actor().hp==hp-1 && fixture.pending().empty() && fixture.outcomes().empty() &&
            world.idSources().events.snapshot()==ids.at("events") &&
            world.randomStreams().snapshot()==expectedRandom.snapshot() && !hasAiStream(world),
            "Diagnostic damage draws only its hurt-presentation stream and cannot publish a gameplay hit or activate Event.ai");
        check(!world.configureMonsterEventAi(fixture.owner,"easy",MonsterEventAiPolicy::inferredIntegralChanceV1()),
            "An installed actor incarnation cannot silently reconfigure its difficulty or event program");
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;
        const auto seed=seedFor(fixture,false);world.randomStreams()=RandomStreams(seed);
        const auto ids=world.idSources().events.snapshot();fixture.ordinaryHit();
        const auto pending=fixture.pending()[0],accepted=pending.at("event_id");
        check(accepted==ids.at("next") && fixture.outcomes().empty() && !hasAiStream(world),
            "Real ordinary attack damage publishes exactly one current-handle accepted event without evaluating AI during contact");
        const auto pendingIds=world.idSources().snapshot();fixture.settle();const auto outcome=fixture.outcomes().at(0);
        check(outcome.at("ok")==true && outcome.at("result")=="authored_no_action" &&
            outcome.at("accepted_event")==accepted && traceKind(outcome,"chance") &&
            !traceKind(outcome,"cooldown") && !world.actHost()->ownsActor(fixture.owner) &&
            world.idSources().snapshot()==pendingIds && hasAiStream(world),
            "The real source failed30/100 branch commits its sample and consumes its accepted event once without a cooldown query or action ID");
        const auto random=world.randomStreams().snapshot();fixture.ticks(90);
        check(fixture.outcomes().size()==1 && fixture.pending().empty() && world.randomStreams().snapshot()==random,
            "A consumed failed-chance event never rerolls or dispatches again on later fixed ticks");
        samples["chance_false"]={{"seed",seed},{"pending",pending},{"outcome",outcome}};
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;
        const auto seed=seedFor(fixture,true,true);world.randomStreams()=RandomStreams(seed);fixture.ordinaryHit();
        const auto event=fixture.pending()[0].at("event_id");fixture.settle();const auto id=fixture.running();
        const auto first=fixture.outcomes().at(0);const auto &instance=world.actHost()->instances().at(id);
        const auto expected=selectMonsterAction(pvf,pvf.script(eventMob),"attack",4);
        check(first.at("ok")==true && first.at("result")=="source_action_bound" &&
            first.at("accepted_event")==event && traceKind(first,"cooldown") &&
            traceKind(first,"cooldown")->at("result")==false &&
            instance.program->source.memberPath==expected.resolvedPath &&
            instance.program->source.memberSha256==sha256(pvf.read(expected.resolvedPath)) &&
            world.actHost()->controlsMovement(fixture.owner) && first.at("boundary_tick")==uint64_t(world.tick),
            "Actual accepted ordinary damage traverses source hit/chance/CDfalse/return4 and binds the exact current Jena Dash ACT at the admitted next boundary");
        const auto x=fixture.actor().x;fixture.ticks(2);
        check(fixture.actor().x!=x && world.actHost()->instances().at(id).animationUs>0,
            "The Event.ai-selected source Dash400 actually advances actor position and the existing exclusive ACT animation clock");
        size_t finish=0;while(world.actHost()->ownsActor(fixture.owner) && finish++<120)fixture.ticks(1);
        check(!world.actHost()->ownsActor(fixture.owner),"The selected ACT naturally releases its velocity before the second real contact");
        // Diagnostic placement isolates a second actual normal-attack contact;
        // it does not inject a damage event, chance result or cooldown flag.
        world.player.x=world.player.px=fixture.actor().x-80;world.player.y=world.player.py=fixture.actor().y;
        world.idle();fixture.ordinaryHit();const auto afterSecondHit=world.idSources().snapshot();fixture.settle();
        const auto second=fixture.outcomes().at(1);
        check(second.at("ok")==true && second.at("result")=="authored_no_action" &&
            traceKind(second,"cooldown") && traceKind(second,"cooldown")->at("result")==true &&
            second.at("accepted_event")!=event && world.idSources().snapshot()==afterSecondHit,
            "A second real contact reads the first action's retained source10000ms cooldown and consumes its fresh event/sample without rebinding or allocating an action");
        samples["source_action_and_cooldown"]={{"seed",seed},{"first",first},{"second",second},{"state",world.monsterEventAiState()}};
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;
        world.randomStreams()=RandomStreams(seedFor(fixture,true));fixture.ordinaryHit();world.freezeAi=true;
        const auto pending=fixture.pending(),random=world.randomStreams().snapshot(),ids=world.idSources().snapshot();fixture.ticks(90);
        check(fixture.pending()==pending && fixture.outcomes().empty() && world.randomStreams().snapshot()==random &&
            world.idSources().snapshot()==ids,
            "AI pause preserves a real accepted event and its unconsumed chance/CD/action state while reaction time passes");
        world.freezeAi=false;fixture.settle();
        check(fixture.outcomes().size()==1 && fixture.outcomes()[0].at("result")=="source_action_bound",
            "Resuming AI evaluates the held event once after reaction admission and executes the selected source action");
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;
        world.randomStreams()=RandomStreams(seedFor(fixture,true));fixture.ordinaryHit();world.freezeAi=true;fixture.ticks(90);
        world.idSources().events=MonotonicIds(0);const auto ids=world.idSources().snapshot(),random=world.randomStreams().snapshot();
        world.freezeAi=false;fixture.ticks(1);const auto outcome=fixture.outcomes()[0];
        check(outcome.at("ok")==false && outcome.at("reason")=="event_return_action_bind" &&
            fixture.pending().empty() && world.randomStreams().snapshot()==random && world.idSources().snapshot()==ids &&
            !world.actHost()->ownsActor(fixture.owner),
            "A real OnSet event-ID exhaustion rejects the selected ACT batch with no live candidate RNG, action IDs or cooldown publication and consumes the hit terminally");
        fixture.ticks(10);
        check(fixture.outcomes().size()==1 && world.randomStreams().snapshot()==random,
            "A failed action bind cannot become an infinite retry or a chance reroll");
        samples["bind_fault"]=outcome;
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;
        world.idSources().events=MonotonicIds(0);const auto hp=fixture.actor().hp;
        const auto random=world.randomStreams().snapshot();
        world.normalAttack();fixture.ticks(90);
        check(fixture.actor().hp==hp && fixture.pending().empty() && fixture.outcomes().empty() &&
            world.randomStreams().snapshot()==random && world.idSources().events.nextValue()==0,
            "Accepted-hit ID exhaustion rejects the real contact before HP or damage/status/event RNG publication");
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;fixture.ordinaryHit();world.freezeAi=true;fixture.ticks(90);
        auto &stream=world.randomStreams().stream(RandomDomain::MonsterEventAi,fixture.owner.id);
        auto exhausted=stream.snapshot();exhausted["draws"]=UINT64_MAX;stream.restore(exhausted);
        const auto random=world.randomStreams().snapshot(),ids=world.idSources().snapshot();world.freezeAi=false;fixture.ticks(1);
        check(fixture.outcomes()[0].at("reason")=="event_ai_evaluation_rejected" && fixture.pending().empty() &&
            world.randomStreams().snapshot()==random && world.idSources().snapshot()==ids,
            "An exhausted separate Event.ai random stream terminally rejects an actual pending hit without publishing a partial result");
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;fixture.ordinaryHit();
        const auto event=fixture.pending()[0].at("event_id"),random=world.randomStreams().snapshot();world.changeScene();
        check(fixture.pending().empty() && world.monsterEventAiState().at("bindings").empty() &&
            fixture.outcomes()[0].at("accepted_event")==event && fixture.outcomes()[0].at("reason")=="scene_change" &&
            world.randomStreams().snapshot()==random && !world.resolveActor(fixture.owner),
            "Scene exit cancels the accepted event and its handle-bound source registration without a random draw or stale-owner delivery");
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;
        world.randomStreams()=RandomStreams(seedFor(fixture,true));fixture.ordinaryHit();
        fixture.actor().capturedBy=0;const auto pending=fixture.pending(),random=world.randomStreams().snapshot();fixture.ticks(90);
        check(fixture.pending()==pending && fixture.outcomes().empty() && world.randomStreams().snapshot()==random,
            "A real accepted event waits through the existing capture-admission gate without chance/CD evaluation");
        fixture.actor().capturedBy=-1;fixture.settle();
        check(fixture.outcomes().size()==1 && fixture.outcomes()[0].at("result")=="source_action_bound",
            "Releasing the diagnostic capture gate admits the held real contact once without injecting an Event.ai result");
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;fixture.actor().hp=1;fixture.ordinaryHit();
        const auto random=world.randomStreams().snapshot();fixture.settle();
        check(fixture.actor().dead && fixture.outcomes().size()==1 &&
            fixture.outcomes()[0].at("reason")=="owner_lifecycle_exit" && world.randomStreams().snapshot()==random &&
            !world.actHost()->ownsActor(fixture.owner),
            "A lethal real contact retains its accepted identity but cannot run counterattack AI after owner death or draw a chance sample");
    }
    {
        EventFixture fixture(pvf,assets);auto &world=fixture.world;fixture.ordinaryHit();
        const auto checkpoint=world.simulationCheckpoint(),random=world.randomStreams().snapshot();
        world.restoreSimulationCheckpoint(checkpoint);fixture.ticks(2);
        check(fixture.pending().empty() && world.monsterEventAiState().at("bindings").empty() &&
            !world.resolveActor(fixture.owner) && world.randomStreams().snapshot()==random &&
            fixture.outcomes().size()==1 && fixture.outcomes()[0].at("classification")=="transient_cancel",
            "The explicit legacy transient-cancel restore retires pending AI and its old handle without replaying or rerolling a saved hit; continuation is not claimed");
    }
    {
        Json expected;
        for(const int rate:{30,60,144,0}) {
            EventFixture fixture(pvf,assets);fixture.world.randomStreams()=RandomStreams(seedFor(fixture,true));
            fixture.world.normalAttack();constexpr int64_t total=2000000000;
            if(rate) {
                int64_t previous=0;for(int frame=1;frame<=2*rate;++frame) {
                    const auto end=total*frame/(2*rate);fixture.world.advance(end-previous);previous=end;
                }
            } else {fixture.world.advance(total,3);while(fixture.world.pendingTicks())fixture.world.advance(0,3);}
            const auto state=fixture.summary();if(expected.is_null())expected=state;
            check(fixture.outcomes().size()==1 && fixture.outcomes()[0].at("result")=="source_action_bound" && state==expected,
                "Actual normal contact, accepted-event ordering, source AI/CD/ACT, IDs, RNG, HP and position agree at30/60/144FPS and budgeted catch-up ticks");
        }
        samples["fixed_tick"]=expected;
    }
    return {{"status","pass"},{"count",check.checks.size()},{"checks",check.checks},{"samples",samples},
        {"scope","Actual ordinary contact to typed accepted-hit scheduling, bounded source Event.ai, independent RNG, readonly action CD and transactional Jena ACT binding"},
        {"fixture","Single real source Jena with diagnostic collision/legacy10000HP; not a region/source-balance/full-AI acceptance test"},
        {"disk_continuation",false},{"whole_monster_or_region_complete",false},{"frontend_and_native_dynamic_comparison","pending user"}};
}
} // namespace dnf
