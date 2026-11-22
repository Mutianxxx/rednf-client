#include "dnf/combat.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/dungeon_difficulty.hpp"
#include "dnf/monster_spawn.hpp"
#include "dnf/session.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *jena="monster/newmonsters/heaven/jena/jena.mob";
constexpr const char *botti="monster/act8/botticelli/botticelli.mob";
constexpr const char *modern="monster/poongjintrainingroom/sandbag/sandbag.mob";
struct Checks {
    Json rows=Json::array();
    void operator()(bool okay,const std::string &message) {
        if(!okay)throw std::runtime_error("Normal Event.ai: "+message);rows.push_back(message);
    }
};
int registeredMonster(Pvf &pvf,const std::string &path) {
    const auto registry=pvf.script("monster/monster.lst");int selected=-1;
    for(size_t i=0;i+1<registry.tokens.size();++i) {
        const auto &id=registry.tokens[i].at("value"),&name=registry.tokens[i+1].at("value");
        if(!id.is_number_integer()||!name.is_string()||normalize("monster/"+name.get<std::string>())!=path)continue;
        if(selected!=-1)throw std::runtime_error("Normal AI fixture registration is ambiguous");selected=id.get<int>();
    }
    if(selected<0)throw std::runtime_error("Normal AI fixture has no source registry row: "+path);return selected;
}
Json normalRows(const World &world) {return world.monsterEventAiState().at("normal_auto_install").at("diagnostics");}
Json outcomes(const World &world) {
    Json rows=Json::array();const auto state=world.monsterEventAiState();
    for(const auto &row:state.at("diagnostics"))if(row.value("kind",std::string())=="monster_event_ai_outcome")rows.push_back(row);
    return rows;
}
struct Fixture {
    World world;EntityHandle owner;
    // Real registry/MOB/Event/ACT and World accepted normalAttack consumer.
    // Diagnostic placement, legacy player balance and high target HP isolate
    // installation/continuation; this is not regional/source-stat acceptance.
    Fixture(Pvf &pvf,Assets &assets,const std::string &mob=jena):world(pvf,assets) {
        world.combat=true;world.freezeAi=true;world.mapWidth=20000;world.walkRects={{12,185,19976,1200}};
        world.player.x=world.player.px=560;world.player.y=world.player.py=344;world.player.dir=1;
        Actor actor;actor.id=17;actor.sourceId=registeredMonster(pvf,mob);actor.monsterPath=mob;
        actor.x=actor.px=640;actor.y=actor.py=344;actor.dir=-1;actor.hp=actor.maxHp=1000000;
        actor.sourceStats["spawn"]={{"diagnostic_fixture","real source AI; wide plane and legacy high HP"}};
        world.monsters.push_back(std::move(actor));world.synchronizeEntityHandles();owner=world.monsters[0].handle;
        world.configureSourceActions("normal-event-fixture-static:"+sha256(assets.staticBytes("audio.xml")));
    }
    Actor &actor(){auto *p=world.resolveActor(owner);if(!p)throw std::runtime_error("Normal AI fixture owner retired");return *p;}
    void ticks(int count){while(count--)world.advanceSingleTick();}
    Json pending()const{return world.monsterEventAiState().at("pending");}
    void hit() {
        world.idle();world.releaseInputs();world.player.x=world.player.px=actor().x-80;
        world.player.y=world.player.py=actor().y;world.player.dir=1;
        const auto hp=actor().hp;const auto size=pending().size();world.normalAttack();
        for(int i=0;i<180&&pending().size()==size;++i)ticks(1);
        if(actor().hp>=hp||pending().size()!=size+1)throw std::runtime_error("Actual normalAttack did not publish one accepted hit");
    }
    Json save(uint64_t generation=19)const {
        auto value=saveActor(world.monsters[0],world.nowMs());
        value["monster_event_ai_state"]=world.monsterEventActorCheckpoint(owner,generation);return value;
    }
    void restore(const Json &value) {
        std::vector<Actor> candidates{loadActor(value,world.nowMs())};
        world.restoreRoomActors(std::move(candidates),Json::array({value}));owner=world.monsters[0].handle;
    }
    void settle() {
        world.freezeAi=false;
        for(int i=0;i<360&&!pending().empty();++i)ticks(1);
        if(!pending().empty())throw std::runtime_error("Normal installed accepted-hit event never reached terminal outcome");
    }
};
uint64_t selectedSeed(Pvf &pvf,const Fixture &fixture) {
    const auto route=selectMonsterEventAi(pvf,pvf.script(jena),dungeonDifficultyRequest(0));
    const auto compiled=compileMonsterEventAi(pvf,pvf.script(route.resolvedPath),MonsterEventAiPolicy::inferredIntegralChanceV1());
    if(!compiled.ok)throw std::runtime_error("Actual Jena Event grammar unavailable");
    MonsterEventAiContext context;context.owner=fixture.owner;context.acceptedHit=MonsterAcceptedHit{1,fixture.world.player.handle};
    for(uint64_t seed=0;seed<4096;++seed) {
        RandomStreams streams(seed);const auto candidate=evaluateMonsterEventAi(*compiled.program,context,
            streams.stream(RandomDomain::MonsterEventAi,fixture.owner.id),[](EntityHandle,int)->std::optional<bool>{return false;});
        if(candidate.ok&&candidate.returnedActionIndex==4)return seed;
    }
    throw std::runtime_error("Bounded diagnostic seed search cannot select source return4");
}
} // namespace

Json runMonsterEventAiNormalPolicyTests(Pvf &pvf,Assets &assets) {
    Checks check;Json samples=Json::object();
    {
        Fixture f(pvf,assets);f.ticks(1);
        check(f.world.monsterEventAiState().at("bindings").empty()&&normalRows(f.world).empty(),
            "Configured ACT alone does not turn the ordinary source-think policy on");
        f.world.configureMonsterActionAi(dungeonDifficultyRequest(0));
        const auto random=f.world.randomStreams().snapshot(),ids=f.world.idSources().snapshot();f.ticks(1);
        const auto state=f.world.monsterEventAiState();const auto rows=normalRows(f.world);
        check(!f.world.debugOverrides().enabled&&state.at("bindings").size()==1&&rows.size()==1&&rows[0].at("installed")==true,
            "First ordinary source-think boundary installs real Jena Event.ai without F7 or debug mode");
        check(state.at("bindings")[0].at("route").at("difficulty")==dungeonDifficultyRequest(0)&&
            state.at("bindings")[0].at("route").at("resolved_path")=="monster/newmonsters/heaven/jena/ai/event.ai",
            "Normal installation uses frozen tier request and exact authored source Event route");
        check(f.world.randomStreams().snapshot()==random&&f.world.idSources().snapshot()==ids&&f.world.actHost()->instances().empty(),
            "Installing while AI is paused draws no RNG, allocates no game identity and binds no ACT");
        f.ticks(20);check(state==f.world.monsterEventAiState()&&f.world.randomStreams().snapshot()==random&&f.world.idSources().snapshot()==ids,
            "Unchanged ordinary boundaries do not reinstall or append duplicate diagnostics");
        samples["ordinary_first_boundary"]=state;
    }
    for(const char *path:{botti,modern})for(int tier=0;tier<4;++tier) {
        Fixture f(pvf,assets,path);const auto request=dungeonDifficultyRequest(tier);
        const auto expected=selectMonsterEventAi(pvf,pvf.script(path),request);
        check(expected.ok,"Actual family member has requested source difficulty row");
        f.world.configureMonsterActionAi(request);f.ticks(1);
        const auto state=f.world.monsterEventAiState();
        check(state.at("bindings").size()==1&&state.at("bindings")[0].at("route")==expected.json(),
            "Old/new authored family reaches actual ordinary installer with exact route evidence: "+std::string(path)+" tier"+std::to_string(tier));
    }
    {
        Fixture f(pvf,assets);f.world.configureMonsterActionAi(dungeonDifficultyRequest(0));f.ticks(1);
        f.world.randomStreams()=RandomStreams(selectedSeed(pvf,f));f.hit();
        check(f.pending().size()==1&&!f.world.debugOverrides().enabled,"Actual ordinary attack queues one typed accepted event in normal mode");
        f.settle();const auto rows=outcomes(f.world);
        check(rows.size()==1&&rows[0].at("result")=="source_action_bound"&&
            rows[0].at("action_route").at("resolved")=="monster/newmonsters/heaven/jena/action/dash.act",
            "Automatically installed Event dispatches actual authored return4 into the real Jena Dash ACT");
        const auto id=rows[0].at("instance").get<uint64_t>();
        const auto &source=f.world.actHost()->instances().at(id).program->source;
        check(source.packageIdentity==pvf.identity()&&source.memberPath=="monster/newmonsters/heaven/jena/action/dash.act"&&
            source.memberSha256==sha256(pvf.read(source.memberPath))&&source.scope=="ACT",
            "Normal event result has an actual source-bound ACT instance rather than only an algorithm receipt");
        samples["normal_contact_to_act"]=rows;
    }
    {
        Fixture f(pvf,assets,botti);f.world.configureMonsterActionAi(dungeonDifficultyRequest(0));f.ticks(1);f.hit();
        const auto saved=f.save();const auto hp=f.actor().hp;const auto before=f.world.monsterEventAiState();
        const auto random=f.world.randomStreams().snapshot(),ids=f.world.idSources().snapshot();const auto old=f.owner;
        f.restore(saved);const auto restored=f.world.monsterEventAiState();f.ticks(1);
        const auto after=f.world.monsterEventAiState();
        check(f.owner!=old&&!f.world.resolveActor(old)&&f.actor().hp==hp&&f.pending().size()==1&&
            after.at("bindings")==restored.at("bindings")&&after.at("pending")==restored.at("pending")&&after.at("damage_windows")==restored.at("damage_windows"),
            "New room incarnation preserves restored binding, accepted pending and complete damage window without reinstallation");
        check(after.at("bindings")[0].at("random_stream_key")==old.id&&f.world.randomStreams().snapshot()==random&&f.world.idSources().snapshot()==ids,
            "Normal restore keeps saved Event stream key and exact logical RNG/IDs while paused");
        check(normalRows(f.world).back().at("existing_binding_preserved")==true,
            "Normal installer explicitly records preservation of same-generation room continuation");
        f.settle();const auto terminal=outcomes(f.world);
        check(terminal.size()==1&&terminal[0].at("result")=="authored_no_action"&&f.actor().hp==hp,
            "Restored accepted event evaluates actual Botti threshold once without replaying HP or rewards");
        f.world.freezeAi=true;const auto settled=f.world.randomStreams().snapshot();f.ticks(20);
        check(outcomes(f.world)==terminal&&f.world.randomStreams().snapshot()==settled,"Consumed restored normal Event never retries or rerolls");
        samples["normal_pending_restore"]={{"before",before},{"restored",after},{"outcome",terminal}};
    }
    {
        Fixture f(pvf,assets,botti);
        check(f.world.configureMonsterEventAi(f.owner,"easy",MonsterEventAiPolicy::inferredIntegralChanceV1()),"Explicit source install precedes normal policy");
        f.world.configureMonsterActionAi(dungeonDifficultyRequest(0));f.hit();const auto pending=f.pending();
        const auto existing=f.world.monsterEventAiState().at("bindings");f.ticks(1);
        check(f.world.monsterEventAiState().at("bindings")==existing&&f.pending()==pending&&normalRows(f.world).back().at("existing_binding_preserved")==true,
            "Explicit exact-name Event binding and accepted pending are preserved by normal tier discovery");
        f.world.configureMonsterActionAi(dungeonDifficultyRequest(3));f.ticks(1);
        check(f.world.monsterEventAiState().at("bindings")==existing&&f.pending()==pending&&
            normalRows(f.world).back().at("requested_difficulty_matches_existing")==false&&normalRows(f.world).back().contains("diagnostic"),
            "Changing the request on a live actor diagnoses mismatch and preserves its pending tree until proper scene rebuild");
    }
    {
        Fixture f(pvf,assets);f.world.configureMonsterActionAi(dungeonDifficultyRequest(0));
        f.world.setMapExplorationPolicy(true);
        DebugOverrides overrides;overrides.enabled=true;overrides.monsterAiDifficulty="easy";
        f.world.applyDebugOverrides(overrides,1);f.world.refreshExplorationMonsterEventAiTestPolicy();
        check(f.world.monsterEventAiTestPolicy().at("installed")==1,"Actual F7 exploration installer owns source Jena independently");
        const auto binding=f.world.monsterEventAiState().at("bindings");f.ticks(1);
        check(f.world.monsterEventAiState().at("bindings")==binding&&normalRows(f.world).empty(),
            "Ordinary installer does not claim or replace F7 exploration ownership");
        overrides.monsterAiDifficulty.clear();f.world.applyDebugOverrides(overrides,2);f.world.refreshExplorationMonsterEventAiTestPolicy();
        check(f.world.monsterEventAiState().at("bindings").empty(),"Existing F7 cleanup still removes only its own binding");
        f.ticks(1);check(f.world.monsterEventAiState().at("bindings").empty()&&normalRows(f.world).empty(),
            "Ordinary policy never reinstalls an exploration binding after the user disables F7 selection");
    }
    for(const char *path:{"monster/newmonsters/goblin/foreman_gonlin/foreman_gonlin.mob","monster/goblin/goblin.mob"}) {
        Fixture f(pvf,assets,path);f.world.configureMonsterActionAi(dungeonDifficultyRequest(0));
        const auto random=f.world.randomStreams().snapshot(),ids=f.world.idSources().snapshot();f.ticks(1);
        const auto state=f.world.monsterEventAiState();const auto rows=normalRows(f.world);
        check(state.at("bindings").empty()&&rows.size()==1&&rows[0].at("installed")==false&&rows[0].contains("reason"),
            "Unsupported grammar or absent AI is specifically diagnosed without a manufactured attack");
        f.ticks(20);check(f.world.monsterEventAiState()==state&&f.world.randomStreams().snapshot()==random&&f.world.idSources().snapshot()==ids,
            "Rejected immutable source is attempted once without identity allocation, random draw or diagnostic spam");
        if(std::string(path).find("foreman_gonlin")!=std::string::npos)
            check(rows[0].at("reason")=="source_event_ai_install_rejected"&&rows[0].at("details").contains("compilation"),
                "Unsupported current Event grammar retains the actual compiler's complete rejection diagnostic");
    }
    {
        Fixture f(pvf,assets);f.world.configureMonsterActionAi("normal");f.ticks(1);
        check(f.world.monsterEventAiState().at("bindings").empty()&&normalRows(f.world)[0].at("reason")=="selected_source_difficulty_route_unavailable",
            "Historic exact normal request cannot silently alias the Jena easy row");
    }
    {
        Fixture f(pvf,assets);f.world.configureMonsterActionAi(dungeonDifficultyRequest(0));
        f.actor().sourceStats.erase("spawn");f.ticks(1);
        check(normalRows(f.world).empty()&&f.world.monsterEventAiState().at("bindings").empty(),"Unspawned diagnostic actor is outside automatic ordinary discovery");
        f.actor().sourceStats["spawn"]={{"diagnostic_fixture",true}};f.world.combat=false;f.ticks(1);
        check(normalRows(f.world).empty()&&f.world.monsterEventAiState().at("bindings").empty(),"Town/noncombat scene does not auto-install Event.ai");
        f.world.combat=true;f.ticks(1);const auto old=f.owner;
        check(f.world.monsterEventAiState().at("bindings").size()==1,"A newly eligible ordinary source actor installs at its first actual boundary");
        f.world.changeScene();
        check(f.world.monsterEventAiState().at("bindings").empty()&&f.world.monsterEventAiState().at("pending").empty()&&normalRows(f.world).empty(),
            "Scene exit clears automatic attempt cache with binding, pending and source windows");
        f.ticks(1);f.owner=f.world.monsters[0].handle;
        check(f.owner!=old&&f.world.monsterEventAiState().at("bindings").size()==1&&normalRows(f.world).size()==1,
            "Fresh typed room incarnation gets a fresh automatic source installation");
    }
    {
        // One production factory case uses real source MAP/DGN/provenance,
        // source growth and user frozen-level policy. Its wide walk plane
        // deliberately does not claim original room geometry/admission.
        RegionCatalog catalog(pvf,assets);
        const auto map=pvf.script("map/gentsouthgate/(4,0)normal.map");
        World live(pvf,assets,WorldRules::BetaFoundationV1);
        live.combat=true;live.freezeAi=true;live.mapWidth=20000;live.walkRects={{0,185,20000,1500}};
        live.configureSourceActions("normal-event-factory-static:"+sha256(assets.staticBytes("audio.xml")));
        const auto dungeon=map.values("[dungeon]").at(0).get<int>();catalog.prepareDungeon(dungeon);
        const auto &definition=catalog.dungeons.at(dungeon);
        const double background=definition.source.values("[background pos]").at(0).get<double>();
        live.monsters=prepareSourceMonsterSpawns(live,catalog,map,dungeon,definition.basisLevel,background,
            MonsterHpPolicy::inferredMobTableHpV1().id,"inferred-mob-combat-table-v1",{},nullptr,nullptr,MonsterLevelPolicy::playerLevel(1));
        live.synchronizeEntityHandles();live.configureMonsterActionAi(dungeonDifficultyRequest(0));live.advanceSingleTick();
        const auto state=live.monsterEventAiState();
        const auto actor=std::find_if(live.monsters.begin(),live.monsters.end(),[](const Actor &a){return a.monsterPath==jena;});
        check(actor!=live.monsters.end()&&actor->sourceStats.at("spawn").at("map_provenance")==map.source&&actor->combatAttributes&&actor->combatAttributes->usable(),
            "Real normal MAP factory retains source placement and frozen source-growth Jena attributes");
        check(std::any_of(state.at("bindings").begin(),state.at("bindings").end(),[&](const Json &row){return row.at("owner")==actor->handle.json();}),
            "Production source-spawn actor reaches automatic ordinary Event installation without manually calling configureMonsterEventAi");
        samples["production_factory"]={{"source_map",map.source},{"actor",saveActor(*actor,live.nowMs())},{"normal_auto_install",state.at("normal_auto_install")}};
    }
    return {{"status","pass"},{"count",check.rows.size()},{"checks",check.rows},{"samples",samples},
        {"scope","Actual ordinary boundary, current source route/compiler, real normalAttack/Event/ACT, F7 independence and same-generation pending room restoration; diagnostic plane/balance isolated from final regional acceptance"},
        {"whole_ai_complete",false},{"native_phase_rng_comparison","pending user/original-client comparison"}};
}
} // namespace dnf
