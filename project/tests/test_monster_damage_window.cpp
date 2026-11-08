#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/monster_behavior.hpp"
#include "dnf/session.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *botti="monster/act8/botticelli/botticelli.mob";
struct Checks {Json rows=Json::array();void operator()(bool ok,const std::string &message) {
    if(!ok)throw std::runtime_error("Monster damage window: "+message);rows.push_back(message);std::cerr<<"window check "<<rows.size()<<": "<<message<<"\n";
}};
struct Fixture {
    World w;EntityHandle owner;
    Fixture(Pvf &p,Assets &a,const std::string &mob=botti,bool install=true):w(p,a) {
        w.combat=true;w.freezeAi=true;w.mapWidth=20000;w.walkRects={{0,185,20000,1200}};
        w.player.x=w.player.px=560;w.player.y=w.player.py=344;w.player.dir=1;
        Actor m;m.id=17;m.sourceId=56503;m.monsterPath=mob;m.x=m.px=640;m.y=m.py=344;m.dir=-1;m.hp=m.maxHp=1000000;
        w.monsters.push_back(m);w.synchronizeEntityHandles();owner=w.monsters[0].handle;
        w.configureSourceActions("damage-window-static:"+sha256(a.staticBytes("audio.xml")));
        if(install&&!w.configureMonsterEventAi(owner,"easy",MonsterEventAiPolicy::inferredIntegralChanceV1()))
            throw std::runtime_error("Source damage-check install: "+w.monsterEventAiState().dump());
    }
    Actor &actor(){auto *a=w.resolveActor(owner);if(!a)throw std::runtime_error("fixture owner retired");return *a;}
    void ticks(int n){while(n--)w.advanceSingleTick();}
    Json pending()const{return w.monsterEventAiState().at("pending");}
    Json window()const {const auto state=w.monsterEventAiState();for(const auto &v:state.at("damage_windows"))if(v.at("owner")==owner.json())return v.at("window");throw std::runtime_error("Missing source window");}
    Json outcomes()const {Json r=Json::array();const auto state=w.monsterEventAiState();for(const auto &v:state.at("diagnostics"))if(v.value("kind",std::string())=="monster_event_ai_outcome")r.push_back(v);return r;}
    int hit() {
        w.idle();w.releaseInputs();w.player.x=w.player.px=actor().x-80;w.player.y=w.player.py=actor().y;w.player.dir=1;
        const auto hp=actor().hp;const auto count=pending().size();w.normalAttack();
        for(int i=0;i<180&&actor().hp==hp;++i)ticks(1);
        if(actor().hp==hp)throw std::runtime_error("Real ordinary contact did not reduce HP");
        if(!pending().empty()&&pending().size()!=count+1)throw std::runtime_error("Unexpected accepted event count");
        return hp-actor().hp;
    }
    Json savedActor(uint64_t generation=7)const {auto result=saveActor(w.monsters[0],w.nowMs());result["monster_event_ai_state"]=w.monsterEventActorCheckpoint(owner,generation);return result;}
    void restore(const Json &saved) {std::vector<Actor> actors{loadActor(saved,w.nowMs())};w.restoreRoomActors(std::move(actors),Json::array({saved}));owner=w.monsters[0].handle;}
    void settle(){w.freezeAi=false;for(int i=0;i<360&&!pending().empty();++i)ticks(1);if(!pending().empty())throw std::runtime_error("Window pending did not settle");}
};
const Json *damageTrace(const Json &outcome){if(!outcome.contains("evaluation"))return nullptr;for(const auto &v:outcome.at("evaluation").at("trace"))if(v.at("kind")=="damage_check")return &v;return nullptr;}
}
Json runMonsterDamageWindowTests(Pvf &pvf,Assets &assets) {
    Checks check;Json samples=Json::object();
    {
        const auto source=pvf.script(botti);auto window=initialMonsterDamageWindow(pvf,source,0);
        check(window.enabled&&window.intervalMs==5000,"Current Botti MOB5000 is consumed as interval with exact source receipt");
        window.samples={{1,0,7},{2,5000,11}};
        check(window.amount(5000)==18&&window.amount(5001)==11,"Rolling inferred window includes the exact interval endpoint and expires one millisecond later");
        const auto receipt=window.snapshot();check(restoreMonsterDamageWindow(pvf,source,receipt,5000).snapshot()==receipt,"Exact source-bound rolling window roundtrips without HP or arithmetic replay");
        auto configured=window;
        const auto action=pvf.script("monster/newmonsters/bwanga/action/move.act");
        size_t command=0;while(command<action.fields.size()&&normalize(action.fields[command].tag)!="[set damage check]")++command;
        if(command==action.fields.size())throw std::runtime_error("Real Bwanga command missing");
        const auto commandSource=makeSourceRef(pvf,action.path,action.fields[command].offset,15,command,"BEHAVIOR[0]");
        configureMonsterDamageWindow(configured,false,2000,5000,commandSource);
        check(!configured.enabled&&configured.samples.empty()&&configured.amount(5000)==0&&configured.intervalMs==2000,
            "Explicit inferred stop clears history and keeps its ordered interval configuration");
        configureMonsterDamageWindow(configured,true,1000,5000,commandSource);configured.samples.push_back({3,5000,19});
        configureMonsterDamageWindow(configured,true,5000,5001,commandSource);
        check(configured.enabled&&configured.samples.empty()&&configured.configuredMs==5001&&configured.intervalMs==5000,
            "Explicit restart and interval change reset history at publication under the named policy");
        bool backward=false;const auto prior=configured.snapshot();try{configureMonsterDamageWindow(configured,true,1,5000,commandSource);}catch(...){backward=true;}
        check(backward&&configured.snapshot()==prior,"Backward ACT configuration is rejected before private window mutation");
        for(int corruption=0;corruption<8;++corruption) {
            auto bad=receipt;
            if(corruption==0)bad["interval_ms"]=2999;if(corruption==1)bad["samples"][0]["actual_hp_loss"]=-1;
            if(corruption==2)bad["samples"][1]["event_id"]=1;if(corruption==3)bad["samples"][1]["accepted_ms"]=5001;
            if(corruption==4)bad["monster_source"]["member_sha256"]="wrong";if(corruption==5)bad["receipt"]["policy"]="native";
            if(corruption==6)bad["enabled"]=false;if(corruption==7)bad["samples"]=Json::array({receipt["samples"][1],receipt["samples"][0]});
            bool rejected=false;try{restoreMonsterDamageWindow(pvf,source,bad,5000);}catch(...){rejected=true;}
            check(rejected,"Malformed/future/reordered/foreign/reconfigured frozen window rejects: "+std::to_string(corruption));
        }
        const auto compiled=compileMonsterEventAi(pvf,pvf.script("monster/act8/botticelli/ai/event.ai"),MonsterEventAiPolicy::inferredIntegralChanceV1());
        check(compiled.ok,"Actual source Event.ai damage check grammar compiles with ordered threshold provenance");
        for(const auto amount:{99999,100000,100001}) {
            MonsterEventAiContext context;context.owner={2,1};context.tick=3;context.acceptedHit=MonsterAcceptedHit{3,{1,1},1,amount,true};
            Pcg32 rng(7,9);const auto before=rng.snapshot();const auto out=evaluateMonsterEventAi(*compiled.program,context,rng,[](EntityHandle,int)->std::optional<bool>{return false;});
            check(out.ok&&out.returnedActionIndex==(amount>=100000?4:-1)&&out.candidateRandom->snapshot()==before,
                "Actual source threshold comparison has explicit below/equal/above semantics without consuming RNG: "+std::to_string(amount));
        }
    }
    {
        Fixture f(pvf,assets);const auto loss=f.hit();const auto pending=f.pending();const auto window=f.window();
        check(pending.size()==1&&pending[0]["actual_hp_loss"]==loss&&pending[0]["window_amount"]==loss&&pending[0]["damage_check_enabled"]==true,
            "Real ordinary attack publishes accepted actual HP loss and immutable rolling sum to the existing same-boundary event");
        check(window["samples"].size()==1&&window["samples"][0]["actual_hp_loss"]==loss,
            "Real accepted damage sample uses settled HP decrease rather than animation, configured interval or guessed damage");
        f.ticks(1);check(f.pending()==pending,"A single multi-frame attack does not count duplicate contact while AI is paused");
        f.settle();const auto outcome=f.outcomes().at(0);const auto *trace=damageTrace(outcome);
        check(trace&&trace->at("window_amount")==loss&&trace->at("authored_threshold")==100000&&trace->at("result")==false&&outcome.at("result")=="authored_no_action",
            "Real contact traverses actual source hit→damage check→authored no-action branch; no fake counterattack or dependency bypass");
        samples["ordinary_source_chain"]=outcome;
    }
    {
        Fixture f(pvf,assets);f.actor().hp=1;const auto loss=f.hit();
        check(loss==1&&f.pending()[0]["actual_hp_loss"]==1&&f.pending()[0]["window_amount"]==1,
            "A real lethal contact clips overkill to actual1HP decrease");
        const auto random=f.w.randomStreams().snapshot();f.settle();
        check(f.outcomes()[0].at("reason")=="owner_lifecycle_exit"&&f.w.randomStreams().snapshot()==random,"Dead window owner cannot counterattack or reroll");
    }
    {
        Fixture f(pvf,assets);f.w.idSources().events=MonotonicIds(0);const auto hp=f.actor().hp;const auto random=f.w.randomStreams().snapshot();
        f.w.normalAttack();f.ticks(180);
        check(f.actor().hp==hp&&f.window()["samples"].empty()&&f.pending().empty()&&f.w.randomStreams().snapshot()==random,
            "Accepted-event exhaustion rejects before live HP, RNG or sample publication");
    }
    {
        Fixture f(pvf,assets);const auto loss=f.hit();const auto saved=f.savedActor();const auto old=f.owner;const auto random=f.w.randomStreams().snapshot(),ids=f.w.idSources().snapshot();
        f.restore(saved);
        check(f.owner!=old&&!f.w.resolveActor(old)&&f.actor().hp==1000000-loss&&f.w.randomStreams().snapshot()==random&&f.w.idSources().snapshot()==ids,
            "Room restore stages fresh owner handles while preserving settled HP, event allocation and exact random state");
        check(f.pending().size()==1&&f.pending()[0]["event_id"]==saved["monster_event_ai_state"]["pending"][0]["event_id"]&&
            f.pending()[0]["attacker"]==f.w.player.handle.json()&&f.window()==saved["monster_event_ai_state"]["window"],
            "Typed owner/player remap preserves pending identity, actual quantity and complete window without replay");
        f.settle();check(f.actor().hp==1000000-loss&&f.outcomes().size()==1&&damageTrace(f.outcomes()[0])->at("window_amount")==loss,
            "Restored pending dispatch runs once and never applies damage or rewards again");
        f.ticks(20);check(f.outcomes().size()==1,"Restored consumed event cannot retry or reroll");
        samples["room_restore"]=f.w.monsterEventAiState();
    }
    {
        const auto route=selectMonsterEventAi(pvf,pvf.script("monster/newmonsters/heaven/jena/jena.mob"),"easy");
        const auto program=compileMonsterEventAi(pvf,pvf.script(route.resolvedPath),MonsterEventAiPolicy::inferredIntegralChanceV1()).program;
        for(const bool selected:{false,true}) {
            Fixture uninterrupted(pvf,assets,"monster/newmonsters/heaven/jena/jena.mob"),restored(pvf,assets,"monster/newmonsters/heaven/jena/jena.mob");
            MonsterEventAiContext context;context.owner=uninterrupted.owner;context.tick=1;
            context.acceptedHit=MonsterAcceptedHit{1,uninterrupted.w.player.handle};uint64_t seed=0;
            for(;seed<4096;++seed) {
                RandomStreams streams(seed);const auto out=evaluateMonsterEventAi(*program,context,streams.stream(RandomDomain::MonsterEventAi,uninterrupted.owner.id),
                    [](EntityHandle,int)->std::optional<bool>{return false;});
                if(out.ok&&((*out.returnedActionIndex==4)==selected))break;
            }
            if(seed==4096)throw std::runtime_error("Bounded Jena chance fixture seed unavailable");
            uninterrupted.w.randomStreams()=RandomStreams(seed);restored.w.randomStreams()=RandomStreams(seed);
            uninterrupted.hit();restored.hit();const auto saved=restored.savedActor();const auto old=restored.owner;
            restored.restore(saved);
            check(restored.owner!=old&&restored.w.monsterEventAiState().at("bindings")[0].at("random_stream_key")==old.id,
                "Room remap keeps the original explicit Event.ai stream key: "+std::to_string(selected));
            uninterrupted.settle();restored.settle();const auto one=uninterrupted.outcomes()[0],two=restored.outcomes()[0];
            check(one.at("result")==two.at("result")&&two.at("result")==std::string(selected?"source_action_bound":"authored_no_action")&&
                uninterrupted.w.randomStreams().snapshot()==restored.w.randomStreams().snapshot()&&uninterrupted.actor().hp==restored.actor().hp,
                "Actual chance/optional source ACT and global random state match uninterrupted dispatch after owner remap: "+std::to_string(selected));
            const auto random=restored.w.randomStreams().snapshot();restored.ticks(20);
            check(restored.outcomes().size()==1&&restored.w.randomStreams().snapshot()==random,
                "Room-restored chance result dispatches once without a retry or random redraw: "+std::to_string(selected));
            samples[selected?"remapped_chance_true":"remapped_chance_false"]={{"seed",seed},{"outcome",two}};
        }
    }
    {
        Fixture f(pvf,assets);f.hit();const auto saved=f.savedActor();
        for(int corruption=0;corruption<4;++corruption) {
            auto second=saved;second["id"]=18;second["entity_handle"]={{"id",3},{"generation",1}};
            auto &bundle=second["monster_event_ai_state"];bundle["actor_id"]=18;bundle["owner"]=second["entity_handle"];
            bundle["entity_ids"]["next"]=4;bundle["random_stream_key"]=3;
            auto first=saved;first["monster_event_ai_state"]["entity_ids"]["next"]=4;
            if(corruption==0){bundle["random_stream_key"]=saved["monster_event_ai_state"]["random_stream_key"];bundle["pending"]=Json::array();bundle["window"]["samples"]=Json::array();}
            if(corruption==1)bundle["window"]["samples"]=Json::array();
            if(corruption==2){bundle["pending"]=Json::array();bundle["window"]["samples"]=Json::array();bundle["saved_tick"]=0;bundle["saved_ms"]=0;}
            if(corruption==3){bundle["pending"]=Json::array();bundle["window"]["samples"]=Json::array();bundle["owner"]=first["entity_handle"];second["entity_handle"]=first["entity_handle"];}
            const auto before=f.w.monsterEventAiState(),registry=f.w.simulationCheckpoint().at("entities");bool rejected=false;
            try{std::vector<Actor> actors{loadActor(first,f.w.nowMs()),loadActor(second,f.w.nowMs())};f.w.restoreRoomActors(std::move(actors),Json::array({first,second}));}catch(...){rejected=true;}
            check(rejected&&f.w.monsterEventAiState()==before&&f.w.simulationCheckpoint().at("entities")==registry,
                "Multi-owner room restore rejects colliding stream/event/clock/old-owner receipt atomically: "+std::to_string(corruption));
        }
    }
    {
        Fixture f(pvf,assets);f.hit();const auto saved=f.savedActor();
        for(int corruption=0;corruption<8;++corruption) {
            auto bad=saved;auto &b=bad["monster_event_ai_state"];
            if(corruption==0)b["owner"]={{"id",999},{"generation",1}};if(corruption==1)b["pending"][0]["accepted_tick"]=uint64_t(f.w.tick)+1;
            if(corruption==2)b["pending"][0]["attacker_role"]="monster";if(corruption==3)b["ai_source"]["member_sha256"]="wrong";
            if(corruption==4)b["pending"][0]["event_id"]=f.w.idSources().events.nextValue();if(corruption==5)b["random_stream_key"]=0;
            if(corruption==6)b["pending"][0]["window_amount"]=-1;if(corruption==7)bad.erase("monster_event_ai_state");
            const auto before=f.w.monsterEventAiState();const auto hp=f.actor().hp;const auto registry=f.w.simulationCheckpoint().at("entities");bool rejected=false;
            try{f.restore(bad);}catch(...){rejected=true;}
            check(rejected&&f.actor().hp==hp&&f.w.monsterEventAiState()==before&&f.w.simulationCheckpoint().at("entities")==registry,
                "Invalid owner/source/clock/role/watermark/key/missing mechanism receipt rejects whole room prepare: "+std::to_string(corruption));
        }
    }
    {
        Fixture f(pvf,assets,"monster/newmonsters/bwanga/bwanga.mob",false);
        const auto route=selectMonsterAction(pvf,pvf.script(f.actor().monsterPath),"move");
        check(route.ok&&route.engine==MonsterActionEngine::Act,"Current Bwanga authored move slot resolves without filename fallback");
        const auto compiled=f.w.actHost()->compile(route.resolvedPath);check(compiled.ok,"Current complete source move ACT compiles with actual SET DAMAGE CHECK World consumer");
        ActBindRequest request;request.owner=f.owner;request.instanceId=1;request.actionId=1;request.tick=uint64_t(f.w.tick);request.simulationMs=uint64_t(f.w.nowMs());
        const auto bound=f.w.actHost()->bind(compiled.program,request,{},true);check(bound.ok,"Actual current-source move ACT binds transactionally");
        f.ticks(1);check(f.window().at("enabled")==true&&f.window().at("interval_ms")==5000&&f.window().at("configuration_source").at("member_path")==route.resolvedPath,
            "Real frame-zero behavior emits typed start5000 command and publishes exact actor window through private ACT batch");
        const auto frozen=f.w.monsterEventActorCheckpoint(f.owner,7);check(!frozen.is_null(),"ACT-created window has actor continuation receipt even without Event.ai install");
        const auto actor=f.savedActor();f.restore(actor);check(f.window()==frozen.at("window"),"ACT-configured interval/source/strategy survives exact typed room restore");
        samples["source_act_window"]=f.window();
    }
    {
        Json expected;
        for(const int fps:{30,60,144,0}) {
            Fixture f(pvf,assets);f.w.freezeAi=false;f.w.normalAttack();constexpr int64_t total=2000000000;
            if(fps){int64_t previous=0;for(int n=1;n<=2*fps;++n){const auto end=total*n/(2*fps);f.w.advance(end-previous);previous=end;}}
            else{f.w.advance(total,3);while(f.w.pendingTicks())f.w.advance(0,3);}
            const auto summary=Json{{"hp",f.actor().hp},{"state",f.w.monsterEventAiState()},{"ids",f.w.idSources().snapshot()},{"random",f.w.randomStreams().snapshot()}};
            if(expected.is_null())expected=summary;check(summary==expected&&f.outcomes().size()==1,"Actual damage/window/query/pending/IDs/RNG are identical across render grouping and catch-up: "+std::to_string(fps));
        }
    }
    {
        RegionCatalog regions(pvf,assets);Progression progression(regions);
        for(const int skill:{4,12}) {
            World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
            CharacterStore store(std::filesystem::absolute("tests/source-quantity-fixture-"+std::to_string(skill)));
            store.data["characters"][0]={{"name","WindowQuantity"},{"class","atgunner"},{"identity",CharacterIdentity{5,0,0}.json()},
                {"level",1},{"skill_initialization","source-v1"}};store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);
            world.combat=true;world.freezeAi=true;world.freeCd=true;world.mapWidth=6000;world.walkRects={{0,185,6000,600}};
            world.player.x=world.player.px=2500;world.player.y=world.player.py=400;world.player.mp=INT32_MAX;
            Actor target;target.id=1;target.sourceId=56503;target.monsterPath="monster/newmonsters/heaven/jena/jena.mob";
            target.x=target.px=2555;target.y=target.py=400;target.dir=-1;
            world.initializeMonsterAttributes(target,1,"inferred-mob-table-hp-v1","inferred-mob-combat-table-v1");target.hp=target.maxHp=100000000;
            world.monsters.push_back(std::move(target));world.synchronizeEntityHandles();
            world.configureSourceActions("quantity-static:"+sha256(assets.staticBytes("audio.xml")));
            const auto installed=world.configureMonsterEventAi(world.monsters[0].handle,"easy",MonsterEventAiPolicy::inferredIntegralChanceV1());
            if(!installed)throw std::runtime_error(world.monsterEventAiState().dump());
            check(installed,"Actual combat-source Jena Event.ai installs for quantity verification: "+std::to_string(skill));
            auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();runtime.configuration()=ExperimentalSkillConfiguration(plan);
            const SkillKey key{5,skill};runtime.configuration().configureFemaleGunnerSourceSkill(key,1,plan);runtime.configuration().assignSlot(0,key,plan);
            world.enqueue({world.simulationNanoseconds(),20,true});
            for(int t=0;t<600&&world.monsterEventAiState().at("pending").empty();++t)world.advanceSingleTick();
            const auto pending=world.monsterEventAiState().at("pending");int64_t total=0;for(const auto &p:pending)total+=p.at("actual_hp_loss").get<int>();
            check(!pending.empty()&&total==100000000-world.monsters[0].hp&&total>0,
                "Actual source body/projectile contact publishes exactly the accepted HP decrease to pending: "+std::to_string(skill));
            const std::string cause=skill==4?"experimental_source_skill":"female_gunner_source_entity";bool actual=false;
            for(const auto &event:world.events)actual|=event.kind=="hit"&&event.name==cause;
            check(actual,"Quantity verification reaches its intended live damage adapter: "+cause);
            samples["source_quantity_"+std::to_string(skill)]=pending;
        }
    }
    {
        Fixture f(pvf,assets);f.hit();const auto saved=f.savedActor();
        CharacterStore store(std::filesystem::absolute("tests/same-generation-fixture"));
        store.data["characters"][0]={{"name","WindowGeneration"},{"class","swordman"},{"identity",f.w.identity().json()}};store.capture(0,f.w);
        store.data["characters"][0]["region_session"]={{"room_states",Json::array({Json::array({saved})})}};
        store.checkpoint();const auto generation=store.generation();
        const auto &character=store.data.at("characters")[0];const auto &bundle=character.at("region_session").at("room_states")[0][0].at("monster_event_ai_state");
        check(generation>0&&bundle.at("commit_generation")==generation&&character.at("simulation").at("random")==f.w.randomStreams().snapshot(),
            "Actual CharacterStore commit binds pending/window and frozen world random snapshot to one outer generation");
        auto bad=bundle;bad["commit_generation"]=generation+1;bool rejected=false;
        try{f.w.validateMonsterEventActorCheckpoint(f.actor(),bad,uint64_t(f.w.nowMs()),generation);}catch(...){rejected=true;}
        check(rejected,"A window/pending bundle from another commit generation is rejected before room publication");
    }
    return {{"status","pass"},{"checks",check.rows},{"samples",samples},{"scope","Actual current-source ordinary damage/Event.ai/typed ACT window/private Room continuation"},
        {"native_window_semantics","named inference, dynamic comparison pending"},{"all_monsters_or_maps_complete",false}};
}
} // namespace dnf
