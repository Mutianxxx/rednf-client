#include "dnf/combat.hpp"
#include "dnf/debug.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/map_exploration.hpp"
#include "dnf/progression.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *sourceMap="map/gentsouthgate/(4,0)normal.map";
constexpr const char *sourceMob="monster/newmonsters/heaven/jena/jena.mob";
struct PolicyFixture {
    World world;
    DebugService debug;
    DebugContext context{{"source-event-ai-policy","isolated-test-character","isolated-test-run",1},1,true};
    EntityHandle owner;
    Json preparation;
    PolicyFixture(Pvf &pvf,Assets &assets,MapAccessCatalog &maps,const RegionCatalog &catalog,const Progression &progression)
        :world(pvf,assets,WorldRules::BetaFoundationV1) {
        world.applyEquipment(progression);
        world.configureSourceActions("source-event-ai-policy-static:"+sha256(assets.staticBytes("audio.xml")));
        const auto matches=maps.findByPath(sourceMap);
        if(matches.empty()) throw std::runtime_error("Event.ai policy source MAP missing from directory");
        auto prepared=prepareMapExploration(pvf,assets,world,catalog,maps.at(matches.front()),true);
        preparation=prepared.json();preparation.erase("records");
        if(!prepared.ok || !prepared.geometryAvailable) throw std::runtime_error("Event.ai source MAP preparation failed: "+preparation.dump());
        world.walkRects=prepared.scene.walkRects;world.blockedRects=prepared.scene.blockedRects;world.mapWidth=prepared.scene.width;
        world.monsters=std::move(prepared.monsters);world.combat=true;
        world.player.x=world.player.px=prepared.playerSpawn[0];world.player.y=world.player.py=prepared.playerSpawn[1];
        world.synchronizeEntityHandles();world.setMapExplorationPolicy(prepared.geometryAvailable);
        for(const auto &actor:world.monsters) if(actor.monsterPath==sourceMob) owner=actor.handle;
        if(!owner) throw std::runtime_error("Actual F7 source MAP did not prepare its registered Jena actor: "+preparation.dump());
        world.refreshExplorationMonsterEventAiTestPolicy();debug.refresh(world,context);
        world.setBeforeTick([this](World &simulation) {
            debug.applyAtBoundary(simulation,context);
            simulation.refreshExplorationMonsterEventAiTestPolicy();debug.refresh(simulation,context);
        });
    }
    void command(DebugCommandKind kind,Json payload) {
        const auto request=debug.nextRequestId();const auto queued=debug.submit({request,context.target,kind,std::move(payload)});
        if(queued.state!=DebugResultState::Accepted) throw std::runtime_error("AI test policy command queue rejected: "+queued.reason);
        debug.applyAtBoundary(world,context);world.refreshExplorationMonsterEventAiTestPolicy();debug.refresh(world,context);
        if(debug.snapshot().recentResults.back().state!=DebugResultState::Applied)
            throw std::runtime_error("AI test policy command boundary rejected: "+debug.snapshot().recentResults.back().reason);
    }
    Actor &actor() {auto *value=world.resolveActor(owner);if(!value) throw std::runtime_error("AI policy owner retired");return *value;}
    Json ownerReceipt() const {
        const auto policy=world.monsterEventAiTestPolicy();
        for(const auto &row:policy.at("actors")) if(row.at("owner")==owner.json()) return row;
        throw std::runtime_error("AI policy actor receipt missing");
    }
    Json outcomes() const {
        Json result=Json::array();const auto state=world.monsterEventAiState();
        for(const auto &row:state.at("diagnostics")) if(row.value("kind",std::string())=="monster_event_ai_outcome" &&
            row.at("owner")==owner.json()) result.push_back(row);
        return result;
    }
    void hit() {
        const double x=actor().x-80,y=actor().y;
        if(!world.canWalk(x,y)) throw std::runtime_error("Source MAP has no walkable ordinary-attack setup left of Jena");
        world.player.x=world.player.px=x;world.player.y=world.player.py=y;world.player.dir=1;
        const auto hp=actor().hp;const auto count=outcomes().size();world.normalAttack();
        for(size_t tick=0;tick<360 && actor().hp==hp && outcomes().size()==count;++tick)world.advanceSingleTick();
        if(actor().hp>=hp) throw std::runtime_error("Source-growth exploration ordinary attack did not damage Jena: "+world.eventLog().dump()+
            " policy="+world.mapExplorationPolicy().dump());
    }
};
uint64_t selectedSeed(Pvf &pvf,PolicyFixture &fixture,bool twice=false) {
    const auto route=selectMonsterEventAi(pvf,pvf.script(sourceMob),"easy");
    if(!route.ok) throw std::runtime_error("AI test seed source route unavailable");
    const auto compiled=compileMonsterEventAi(pvf,pvf.script(route.resolvedPath),MonsterEventAiPolicy::inferredIntegralChanceV1());
    if(!compiled.ok || !compiled.program) throw std::runtime_error("AI test seed source program unavailable");
    MonsterEventAiContext context;context.owner=fixture.owner;context.acceptedHit=MonsterAcceptedHit{1,fixture.world.player.handle};
    for(uint64_t seed=0;seed<4096;++seed) {
        RandomStreams streams(seed);
        const auto first=evaluateMonsterEventAi(*compiled.program,context,streams.stream(RandomDomain::MonsterEventAi,fixture.owner.id),
            [](EntityHandle,int)->std::optional<bool>{return false;});
        if(!first.ok || first.returnedActionIndex!=4 || !first.candidateRandom) continue;
        if(twice) {
            const auto second=evaluateMonsterEventAi(*compiled.program,context,*first.candidateRandom,
                [](EntityHandle,int)->std::optional<bool>{return false;});
            if(!second.ok || second.returnedActionIndex!=4) continue;
        }
        return seed;
    }
    throw std::runtime_error("Bounded diagnostic seed search could not select source30/100 return4");
}
} // namespace

Json runMonsterEventAiTestPolicyTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool condition,const char *text) {
        if(!condition) throw std::runtime_error(std::string("Event.ai test policy: ")+text);checks.push_back(text);
    };
    MapAccessCatalog maps(pvf);RegionCatalog catalog(pvf,assets);Progression progression(catalog);
    {
        // This integration's first real source MAP exposed a P06 semantic gap.
        // Retain and verify the exact refusal; never replace its source level,
        // table term, combat attributes or HP with an isolated diagnostic actor.
        World sourceWorld(pvf,assets,WorldRules::BetaFoundationV1);
        sourceWorld.applyEquipment(progression);
        sourceWorld.configureSourceActions("source-event-ai-policy-static:"+sha256(assets.staticBytes("audio.xml")));
        const auto matches=maps.findByPath(sourceMap);
        check(!matches.empty(),"The actual source Jena MAP remains indexed");
        auto prepared=prepareMapExploration(pvf,assets,sourceWorld,catalog,maps.at(matches.front()),true);
        check(prepared.ok && prepared.geometryAvailable,"Actual source MAP geometry prepares independently of monster capability");
        const bool admitted=std::any_of(prepared.monsters.begin(),prepared.monsters.end(),
            [](const Actor &actor){return actor.monsterPath==sourceMob;});
        if(!admitted) {
            bool retained=false,blocked=false;
            for(const auto &record:prepared.records) if(record.value("kind",std::string())=="monster" &&
                record.contains("raw") && record.at("raw").is_array() && !record.at("raw").empty() && record.at("raw")[0]==56503) {
                retained=true;
                blocked=record.value("error",std::string()).find("unsupported_monster_table_statbase27")!=std::string::npos;
            }
            check(retained && blocked,"Unresolved nonzero statBase27 rejects real source-level Jena with retained source placement and exact diagnostic");
            sourceWorld.walkRects=prepared.scene.walkRects;sourceWorld.monsters=std::move(prepared.monsters);
            sourceWorld.synchronizeEntityHandles();sourceWorld.setMapExplorationPolicy(prepared.geometryAvailable);
            DebugOverrides overrides;overrides.enabled=true;overrides.monsterAiDifficulty="easy";
            sourceWorld.applyDebugOverrides(overrides,1);sourceWorld.refreshExplorationMonsterEventAiTestPolicy();
            check(sourceWorld.monsterEventAiTestPolicy().at("installed")==0 && sourceWorld.monsterEventAiState().at("bindings").empty(),
                "F9 cannot manufacture source actors rejected by shared combat preflight");
            auto receipt=prepared.json();receipt.erase("records");samples["source_map_preparation"]=std::move(receipt);
            samples["test_policy"]=sourceWorld.monsterEventAiTestPolicy();
            return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
                {"positive_f7_source_growth_verified",false},{"source_growth_f7_jena_admission","blocked_by_unresolved_statbase27"},
                {"scope","Source MAP fail-closed preflight and F9 refusal only. Positive F7 contact/action/cleanup cases below are pending; existing isolated Event.ai World tests remain separate evidence."}};
        }
    }
    {
        PolicyFixture fixture(pvf,assets,maps,catalog,progression);auto &world=fixture.world;
        const auto disabled=world.monsterEventAiTestPolicy();
        check(!world.debugOverrides().enabled && disabled.at("selected_difficulty")=="" && disabled.at("installed")==0 &&
            world.monsterEventAiState().at("bindings").empty(),"Real F7 MAP source actors begin with Event.ai disabled and no implicit difficulty");
        check(fixture.actor().combatAttributes && fixture.actor().combatAttributes->usable() &&
            fixture.actor().sourceStats.contains("spawn") && fixture.actor().sourceStats.at("policy")=="inferred-mob-table-hp-v1",
            "F7 Event.ai actor keeps shared source-spawn, source HP and frozen combat attributes");
        const auto row=fixture.ownerReceipt();
        check(row.at("available_difficulties")==Json::array({"easy","hard","medium","ultimate","hero"}),
            "F9 source choices come from the ordered Jena AI block without later level-of-difficulty aliases");
        fixture.command(DebugCommandKind::SetEnabled,true);
        fixture.command(DebugCommandKind::SetMonsterAiDifficulty,"normal");
        check(fixture.ownerReceipt().at("reason")=="selected_source_difficulty_route_unavailable" &&
            !fixture.ownerReceipt().at("route").at("diagnostics").empty(),
            "A missing explicit normal row retains exact per-actor route diagnostics without mapping to easy");
        fixture.command(DebugCommandKind::SetMonsterAiDifficulty,"easy");
        check(fixture.ownerReceipt().at("installed")==true,"F9 easy command installs the actual F7 Jena Event.ai source route");
        const auto state=world.monsterEventAiState(),simulation=world.simulationCheckpoint(),policy=world.monsterEventAiTestPolicy();
        world.refreshExplorationMonsterEventAiTestPolicy();world.refreshExplorationMonsterEventAiTestPolicy();
        check(state==world.monsterEventAiState() && simulation==world.simulationCheckpoint() && policy==world.monsterEventAiTestPolicy(),
            "An unchanged boundary does not reinstall, allocate identities, draw RNG or append diagnostics");
        // Let the same spawn-driven stay service used by main bind before the
        // accepted hit. Seed only the diagnostic random root; source ratio,
        // return slot, damage, stats and all geometry remain unchanged.
        world.advanceSingleTick();world.randomStreams()=RandomStreams(selectedSeed(pvf,fixture,true));
        fixture.hit();
        check(fixture.actor().hp>0,"Actual source HP survives the source-driven ordinary attack without a legacy HP override");
        for(size_t tick=0;tick<360 && fixture.outcomes().empty();++tick)world.advanceSingleTick();
        const auto outcomes=fixture.outcomes();
        check(outcomes.size()==1 && outcomes[0].at("result")=="source_action_bound" &&
            outcomes[0].at("action_route").at("resolved")=="monster/newmonsters/heaven/jena/action/dash.act" &&
            outcomes[0].at("action_route").at("resolved_source")==makeSourceRef(pvf,"monster/newmonsters/heaven/jena/action/dash.act").json(),
            "Source-growth ordinary contact in the actual F7 map reaches accepted Event.ai and real Dash ACT binding");
        const auto instance=outcomes[0].at("instance").get<uint64_t>();
        check(world.actHost()->instances().at(instance).status==ActInstanceStatus::Running,
            "The source action result has a live consumer rather than only an algorithm or preview receipt");
        const auto random=world.randomStreams().snapshot();const auto logical=world.idSources().snapshot();
        fixture.command(DebugCommandKind::SetMonsterAiDifficulty,"");
        check(world.actHost()->instances().at(instance).status!=ActInstanceStatus::Running &&
            !world.actHost()->controlsMovement(fixture.owner) && world.randomStreams().snapshot()==random && world.idSources().snapshot()==logical,
            "Disabling the test AI cancels its exact live action without a random draw or new global logical identity");
        check(world.monsterEventAiState().at("bindings").empty(),"Disabling this test selection clears its owned source bindings");
        samples["source_map_preparation"]=fixture.preparation;
        samples["actual_source_combat_to_event_action"]=outcomes;
        samples["policy"]=policy;
        fixture.command(DebugCommandKind::SetMonsterAiDifficulty,"easy");
        // Stay resumes through the normal source service, without clearing the
        // 10000ms Dash cooldown. The next real accepted hit checks retained CD.
        for(size_t tick=0;tick<100;++tick) world.advanceSingleTick();
        world.idle();fixture.hit();
        for(size_t tick=0;tick<360 && fixture.outcomes().size()<2;++tick)world.advanceSingleTick();
        const auto second=fixture.outcomes();
        check(second.size()==2 && second[1].at("result")=="authored_no_action",
            "Closing and re-enabling the policy cannot reset the source Dash cooldown or reroll the first accepted event");
        bool cooldown=false;
        for(const auto &trace:second[1].at("evaluation").at("trace")) if(trace.at("kind")=="cooldown") cooldown=trace.at("result")==true;
        check(cooldown,"The second real source hit reaches the retained authored cooldown query");
        samples["retained_cooldown"]=second[1];
        world.changeScene();
        check(world.monsterEventAiState().at("bindings").empty() && world.monsterEventAiState().at("pending").empty() &&
            world.monsterEventAiTestPolicy().at("state")=="not_prepared", "Scene exit clears test policy ownership and pending event lifetime");
    }
    {
        PolicyFixture fixture(pvf,assets,maps,catalog,progression);auto &world=fixture.world;
        fixture.command(DebugCommandKind::SetEnabled,true);
        fixture.command(DebugCommandKind::SetMonsterAiDifficulty,"easy");
        fixture.command(DebugCommandKind::SetAiPaused,true);
        fixture.hit();
        const auto queued=world.monsterEventAiState().at("pending");
        check(std::any_of(queued.begin(),queued.end(),[&](const Json &row){return row.at("owner")==fixture.owner.json();}),
            "A real accepted hit can remain pending behind the independent AI-pause command");
        const auto random=world.randomStreams().snapshot();const auto ids=world.idSources().snapshot();
        fixture.command(DebugCommandKind::SetEnabled,false);
        check(world.monsterEventAiState().at("pending").empty() && world.monsterEventAiState().at("bindings").empty() &&
            world.randomStreams().snapshot()==random && world.idSources().snapshot()==ids &&
            fixture.outcomes().back().at("result")=="cancelled",
            "Disabling the master switch cancels test-owned pending accepted hits once without drawing or allocating");
        samples["pending_cancel"]=fixture.outcomes();
    }
    {
        PolicyFixture fixture(pvf,assets,maps,catalog,progression);auto &world=fixture.world;
        fixture.command(DebugCommandKind::SetEnabled,true);
        // An explicit source install is deliberately outside F9 ownership.
        check(world.configureMonsterEventAi(fixture.owner,"easy",MonsterEventAiPolicy::inferredIntegralChanceV1()),
            "External explicit source installation is available before selecting the F9 policy");
        fixture.command(DebugCommandKind::SetMonsterAiDifficulty,"easy");
        check(fixture.ownerReceipt().at("reason")=="explicit_external_binding_preserved", "F9 does not claim or replace an external explicit registration");
        fixture.command(DebugCommandKind::SetMonsterAiDifficulty,"");
        const auto bindings=world.monsterEventAiState().at("bindings");
        check(std::any_of(bindings.begin(),bindings.end(),[&](const Json &binding){return binding.at("owner")==fixture.owner.json();}),
            "Closing F9 AI leaves the external source registration intact");
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","Actual source MAP preparation, shared spawn/source attributes, exploration consumer gate, queued F9 selection and normalAttack to Event.ai to source ACT; no frontend or native dynamic comparison"}};
}
} // namespace dnf
