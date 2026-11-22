#include "dnf/monster_attributes.hpp"
#include "dnf/combat.hpp"
#include "dnf/session.hpp"
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
MonsterAttributeSource monsterAttributeFixture() {
    MonsterAttributeSource source;
    source.monster.path="fixture/monster.mob"; source.monster.rawBytes.resize(102,0);
    source.monster.source={{"package_identity","fixture-content"}};
    source.monster.fields={{"[level]",Json::array({1,3}),2},{"[HP MAX]",Json::array({10.9,20.9}),17},
        {"[ability category]",Json::array({"[HP MAX]","*",150,"[HP MAX]","+",0.9}),32},
        {"[/ability category]",Json::array(),82},{"[unknown future field]",Json::array({"preserved"}),87}};
    source.table.path="fixture/base.tbl"; source.table.rawBytes.resize(362,0);
    source.table.source={{"package_identity","fixture-content"}};
    source.tableSelection="fixture_explicit_table";
    for (int level=1;level<=3;++level) for (int column=0;column<24;++column) {
        const int value=column==0?level:column==5?level*100:0;
        source.table.tokens.push_back({{"offset",2+source.table.tokens.size()*5},{"type",2},{"raw",value},{"value",value}});
    }
    return source;
}
bool monsterDiagnostic(const MonsterHpResult &result, const std::string &kind) {
    for (const auto &entry:result.diagnostics) if(entry.value("kind",std::string())==kind) return true;
    return false;
}
} // namespace

Json runMonsterAttributeTests(Pvf &pvf, Assets &assets) {
    Json checks=Json::array();
    auto check=[&](bool ok,const std::string &name) {
        if(!ok) throw std::runtime_error("Monster attributes: "+name);
        checks.push_back(name);
    };
    auto rejects=[&](auto operation,const std::string &name) {
        bool threw=false; try { operation(); } catch(const std::exception &) { threw=true; }
        check(threw,name);
    };
    const auto policy=MonsterHpPolicy::inferredMobTableHpV1();
    const auto source=monsterAttributeFixture();
    auto evaluate=[&](const MonsterAttributeSource &value,int level=2,bool boss=false) {
        return evaluateMonsterHp(value,level,boss,policy);
    };
    const auto low=evaluate(source,1),middle=evaluate(source,2),high=evaluate(source,3);
    check(low.hp==15 && middle.hp==22 && high.hp==30,
        "Source table, endpoint interpolation and ordered integer category consumers execute at both endpoints and midpoint");
    check(middle.trace[0]["columns"].size()==24 && middle.trace[0]["source"]["byte_offset"]==122 &&
          middle.trace[0]["hp_column"]==5 && middle.trace[1]["source"]["byte_offset"]==17 &&
          middle.trace[1]["level_source"]["byte_offset"]==2 && middle.trace[2]["tuple_ordinal"]==0 &&
          middle.trace[3]["tuple_ordinal"]==1 && middle.sources["monster"]["package_identity"]=="fixture-content",
        "Calculation receipts retain exact table row, field offsets, source identity and repeated category order");
    check(source.monster.rawBytes==monsterAttributeFixture().monster.rawBytes &&
          source.monster.fields.back().values==Json::array({"preserved"}) && source.table.tokens.size()==72 &&
          policy.describe()["classification"]=="inferred_beta" && policy.describe()["native_pc_parity"]=="pending",
        "Unknown fields and raw source documents remain intact; policy never labels beta inference native proof");
    check(!evaluateMonsterHp(source,2,false).usable(),"Default source HP policy does not silently enable an inference");
    check(!evaluate(source,0).usable() && !evaluate(source,-1).usable() &&
          !evaluate(source,4).usable() && monsterDiagnostic(evaluate(source,4),"missing_exact_monster_table_level"),
        "Nonpositive levels and missing exact growth rows fail without a nearest-row fallback");
    auto clamped=source; clamped.monster.fields[0].values=Json::array({2,3});
    check(evaluate(clamped,1).hp==15 && monsterDiagnostic(evaluate(clamped,1),"monster_hp_endpoint_level_clamped"),
        "Endpoint range clamping is explicit and cannot change exact table-level selection");
    auto singleton=source;singleton.monster.fields[0].values=Json::array({2,2});
    check(evaluate(singleton).hp==15 && monsterDiagnostic(evaluate(singleton),"single_level_monster_hp_conflicting_endpoints"),
        "Single-level endpoint range consumes its first value and diagnoses conflicting second value without division by zero");
    auto tableOnly=source;tableOnly.monster.fields.erase(tableOnly.monster.fields.begin()+1);
    check(evaluate(tableOnly).hp==300,"Absent optional MOB HP endpoints consume the actual source growth table");
    auto role=tableOnly;role.monster.fields[1].values=Json::array({"[HP MAX]","*",50,"[HP MAX BOSS]","*",250});
    check(evaluate(role,2,false).hp==100 && evaluate(role,2,true).hp==500,
        "Explicit named boss-category candidate selects its own HP category without also multiplying common HP");
    for(const auto &bad: {Json::array(),Json::array({1}),Json::array({1,2,3}),Json::array({-1,2}),
            Json::array({"one",2}),Json::array({1,std::numeric_limits<double>::infinity()})}) {
        auto value=source;value.monster.fields[1].values=bad;
        check(!evaluate(value).usable(),"Malformed or empty source HP endpoint blocks initialization: "+bad.dump());
    }
    for(const auto &bad: {Json::array(),Json::array({0,3}),Json::array({3,1}),Json::array({1.5,3}),
            Json::array({1,uint64_t(std::numeric_limits<uint64_t>::max())})}) {
        auto value=source;value.monster.fields[0].values=bad;
        check(!evaluate(value).usable(),"Invalid source endpoint range cannot narrow or divide silently: "+bad.dump());
    }
    auto duplicate=source;duplicate.monster.fields.insert(duplicate.monster.fields.begin()+2,{"[HP MAX]",Json::array({20,40}),27});
    check(!evaluate(duplicate).usable() && monsterDiagnostic(evaluate(duplicate),"ambiguous_monster_attribute_field"),
        "Duplicate HP endpoint fields retain candidates and reject instead of choosing the first");
    duplicate=source;duplicate.monster.fields.insert(duplicate.monster.fields.begin()+1,{"[level]",Json::array({1,3}),12});
    check(!evaluate(duplicate).usable(),"Duplicate endpoint range fields reject independently of matching values");
    auto broken=source;broken.table.tokens.erase(broken.table.tokens.end()-1);
    check(!evaluate(broken).usable(),"Partial growth-table rows cannot be treated as complete source levels");
    broken=source;broken.table.tokens[24]["value"]=1;
    check(!evaluate(broken).usable() && monsterDiagnostic(evaluate(broken),"invalid_or_duplicate_monster_table_level"),
        "Duplicate table levels reject without a first-match selection");
    broken=source;broken.table.tokens[6]["value"]="bad-unused-column";
    check(!evaluate(broken).usable(),"Malformed unused growth columns remain diagnosed rather than discarded");
    broken=source;broken.table.tokens[29]["value"]=0;
    check(!evaluate(broken).usable(),"Nonpositive source growth HP cannot initialize an immortal or dead placeholder");
    broken=source;broken.table.tokens[29]["offset"]="bad-offset";
    check(!evaluate(broken).usable(),"Malformed token offsets produce a source diagnostic without unsafe conversion");
    broken=source;broken.monster.fields[1].offset=18;
    check(!evaluate(broken).usable(),"Misaligned source field offsets reject before their values execute");
    for(const auto &bad:{Json::array({"[HP MAX]","*",0}),Json::array({"[HP MAX]","/",2}),
            Json::array({"[HP MAX]","*",-100}),Json::array({"[HP MAX]","+"}),
            Json::array({"[HP MAX]","*",double(std::numeric_limits<int>::max())*100.0})}) {
        broken=source;broken.monster.fields[2].values=bad;
        check(!evaluate(broken).usable(),"Invalid category tuple or HP overflow cannot be published: "+bad.dump());
    }
    auto integerBoundary=source;
    integerBoundary.monster.fields[1].values=Json::array({100,100});
    integerBoundary.monster.fields[2].values=Json::array({"[HP MAX]","*",std::numeric_limits<int>::max()});
    check(evaluate(integerBoundary).hp==std::numeric_limits<int>::max(),
        "A large percentage operand is allowed when its final HP is exactly the signed integer boundary");
    integerBoundary.monster.fields[2].values[2]=double(std::numeric_limits<int>::max())+1.0;
    check(!evaluate(integerBoundary).usable() && monsterDiagnostic(evaluate(integerBoundary),"invalid_monster_hp_category_result"),
        "The next HP above the integer boundary rejects before narrowing instead of wrapping");
    broken=source;broken.monster.fields.back()={"[destroy count]",Json::array({5}),87};
    check(!evaluate(broken).usable() && monsterDiagnostic(evaluate(broken),"hit_count_death_requires_separate_consumer"),
        "Hit-count death source is not misrepresented as ordinary HP death");
    auto nested=tableOnly;
    nested.monster.fields={{"[level]",Json::array({1,3}),2},{"[ability category]",Json::array(),32},
        {"[HP MAX]",Json::array({"*",50}),37},{"[/ability category]",Json::array(),52}};
    nested.monster.tokens=Json::array({{{"offset",32},{"type",5},{"value","[ability category]"}},
        {{"offset",37},{"type",5},{"value","[HP MAX]"}},{{"offset",42},{"type",7},{"value","*"}},
        {{"offset",47},{"type",2},{"value",50}},{{"offset",52},{"type",5},{"value","[/ability category]"}}});
    check(evaluate(nested).hp==100,"Category keys encoded as type-5 tokens cannot masquerade as top-level HP endpoints");
    nested.monster.tokens.erase(nested.monster.tokens.end()-1);
    check(!evaluate(nested).usable(),"Unterminated category token blocks diagnose and reject");

    MonsterSpawn spawn;spawn.level=-2;
    check(resolveMonsterLevel(spawn,10)==8,"MAP automatic level consumes a signed DGN basis-level adjustment");
    spawn.autoLevel=false;spawn.level=7;
    check(resolveMonsterLevel(spawn,999)==7,"MAP fixed level ignores the DGN basis and remains absolute");
    spawn.level=0;rejects([&]{resolveMonsterLevel(spawn,10);},"Fixed level zero rejects before source evaluation");
    spawn.autoLevel=true;spawn.level=1;
    rejects([&]{resolveMonsterLevel(spawn,std::numeric_limits<int>::max());},"Auto-level addition rejects signed overflow before narrowing");
    rejects([&]{resolveMonsterLevel(spawn,0);},"Automatic level cannot invent a missing DGN basis level");
    spawn.level=std::numeric_limits<int>::min();
    rejects([&]{resolveMonsterLevel(spawn,1);},"Extreme negative level adjustment cannot underflow into a positive spawn");
    spawn.level=1;spawn.raw=Json::array({0,1,1.5});
    rejects([&]{resolveMonsterLevel(spawn,10);},"Preserved fractional MAP level rejects instead of accepting an earlier truncation");
    spawn.raw=Json::array({0,2,1});
    rejects([&]{resolveMonsterLevel(spawn,10);},"Unknown source auto-level flags cannot become a true boolean silently");

    const auto goblinSource=readMonsterAttributeSource(pvf,"monster/goblin/goblin.mob",false);
    const auto goblin=evaluate(goblinSource,1),goblin2=evaluate(goblinSource,2);
    check(goblin.hp==35 && goblin2.hp==58 && goblinSource.monster.rawBytes==pvf.read(goblinSource.monster.path) &&
          goblinSource.table.tokens.size()==4800 && goblin.sources["table"]["package_identity"]==pvf.identity(),
        "Current 1031 goblin consumes common table HP 51/84 and authored HP category 70 percent with original bytes retained");
    const auto tauSource=readMonsterAttributeSource(pvf,"monster/tau/taubeast.mob",true);
    const auto tau=evaluate(tauSource,4,true);
    check(tau.hp==686 && tauSource.table.path=="monster/bossmonsterbaseparameter.tbl" &&
          evaluate(readMonsterAttributeSource(pvf,"monster/lugaru/lugaru.mob",false),9).usable(),
        "Current MAP boss role consumes boss growth table and Tau 175 percent; Lugaru consumes its own source multiplier");

    World world(pvf,assets,WorldRules::BetaFoundationV1);
    Actor monster;monster.id=1;monster.monsterPath=goblinSource.monster.path;
    world.initializeMonsterAttributes(monster,1);
    check(monster.hp==35 && monster.maxHp==35 && monster.sourceStats["policy"]==policy.id,
        "Real beta World initializer publishes source HP and its receipt rather than legacy 65/240 bases");
    world.monsters.push_back(monster);
    world.diagnosticHit(1,1,-1,0,1,{});
    check(world.monsters[0].hp==34 && world.monsters[0].maxHp==35 &&
          world.snapshot()["monsters"][0]["source_stats"]==monster.sourceStats,
        "Actual combat damage consumes initialized source HP and World diagnostics expose the unchanged receipt");
    const auto beforeReinit=saveActor(world.monsters[0],world.nowMs());
    rejects([&]{world.initializeMonsterAttributes(world.monsters[0],2);},"Used or restored actors cannot be reinitialized with a new level");
    check(saveActor(world.monsters[0],world.nowMs())==beforeReinit,"Rejected reinitialization preserves combat resource loss");
    Actor bad;bad.id=2;bad.monsterPath=monster.monsterPath;
    const auto badBefore=saveActor(bad,0);
    rejects([&]{world.initializeMonsterAttributes(bad,0);},"Invalid source level blocks actual World initialization");
    check(saveActor(bad,0)==badBefore,"Failed World source evaluation leaves the detached actor unchanged");
    World legacy(pvf,assets);Actor previous;previous.hp=previous.maxHp=DemoBalance{}.monsterHp(false);
    legacy.initializeMonsterAttributes(previous,1);
    check(previous.hp==130 && previous.maxHp==130 && previous.sourceStats["policy"]=="legacy-demo-v1",
        "Legacy World retains the historical caller-frozen demo HP without source substitution");
    Actor oldRun;oldRun.hp=oldRun.maxHp=DemoBalance{}.monsterHp(true);oldRun.boss=true;
    world.initializeMonsterAttributes(oldRun,1,"legacy-demo-v1");
    check(oldRun.hp==720 && oldRun.maxHp==720 && oldRun.sourceStats["policy"]=="legacy-demo-v1",
        "Beta World preserves an explicitly frozen historical run policy in a previously unvisited room");
    Actor unknown;unknown.monsterPath=monster.monsterPath;
    const auto beforeUnknown=saveActor(unknown,0);
    rejects([&]{world.initializeMonsterAttributes(unknown,1,"unknown-future-hp");},
        "Unknown frozen run HP policy rejects instead of silently substituting the beta default");
    check(saveActor(unknown,0)==beforeUnknown,"Rejected policy selection leaves a fresh actor unchanged");
    rejects([&]{legacy.initializeMonsterAttributes(unknown,1,policy.id);},
        "Explicit source HP policy cannot bypass a legacy World profile");

    auto receipt=world.monsters[0].sourceStats;receipt["future"]=Json::array({"x","x",3});
    world.monsters[0].sourceStats=receipt;
    const auto saved=saveActor(world.monsters[0],world.nowMs());
    const auto decoded=loadActor(saved,10000);
    check(decoded.hp==34 && decoded.maxHp==35 && decoded.sourceStats==receipt,
        "Actor source-stat receipts including unknown metadata round-trip without recomputation or healing");
    auto old=saved;old.erase("source_stats");old["hp"]=17;old["max_hp"]=130;
    const auto oldActor=loadActor(old,10000);
    check(oldActor.hp==17 && oldActor.maxHp==130 && oldActor.sourceStats.empty(),
        "Legacy actor snapshots lacking a trace retain their saved HP and receive an empty receipt");
    for(const auto &badType:{Json(),Json::array(),Json(7),Json("trace")}) {
        auto corrupt=saved;corrupt["source_stats"]=badType;
        rejects([&]{loadActor(corrupt,0);},"Invalid saved source-stat type cannot become an accepted receipt: "+badType.dump());
    }
    RegionCatalog catalog(pvf,assets);RegionSession session;session.begin(catalog,1,19801);
    const auto sessionSaved=session.save(world,"dungeon");
    RegionSession restored;
    check(restored.load(sessionSaved,catalog),"Actual RegionSession accepts the saved monster receipt");
    world.monsters.clear();
    check(restored.restore(world) && world.monsters.size()==1 && world.monsters[0].hp==34 &&
          world.monsters[0].maxHp==35 && world.monsters[0].sourceStats==receipt,
        "Room reload restores saved source HP loss and receipt without running the initializer");
    auto oldSession=sessionSaved;
    oldSession["room_states"][restored.run.current][0].erase("source_stats");
    oldSession["room_states"][restored.run.current][0]["hp"]=17;
    oldSession["room_states"][restored.run.current][0]["max_hp"]=130;
    check(restored.load(oldSession,catalog) && restored.restore(world) && world.monsters[0].hp==17 &&
          world.monsters[0].maxHp==130 && world.monsters[0].sourceStats.empty(),
        "Old room reload retains historical HP even in a beta World");
    auto corruptSession=sessionSaved;corruptSession["room_states"][restored.run.current][0]["source_stats"]=Json::array();
    check(restored.load(corruptSession,catalog),"Session structural decode retains a malformed actor for resource-free actor validation");
    const auto beforeBadRestore=saveActor(world.monsters[0],world.nowMs());
    rejects([&]{restored.restore(world);},"Malformed source-stat receipts reject before publishing restored room actors");
    check(saveActor(world.monsters[0],world.nowMs())==beforeBadRestore,"Rejected room restore preserves the existing live monster");
    return {{"status","pass"},{"policy",policy.describe()},{"checks",checks},{"source_examples",Json::array({goblin.snapshot(),goblin2.snapshot(),tau.snapshot()})},
        {"scope","monster HP initialization/source preservation/recovery only; combat damage formula, AI, difficulty and PC parity remain pending"}};
}
} // namespace dnf
