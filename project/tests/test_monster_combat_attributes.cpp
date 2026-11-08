#include "dnf/monster_combat_attributes.hpp"
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
MonsterAttributeSource combatFixture() {
    MonsterAttributeSource source;
    source.monster.path="fixture/combat.mob";source.monster.rawBytes.resize(402,0);
    source.monster.source={{"package_identity","fixture-content"}};
    source.monster.fields={
        {"[level]",Json::array({1,3}),2},
        {"[physical attack]",Json::array({10.9,20.9}),17},
        {"[magical attack]",Json::array({20,40}),32},
        {"[physical defense]",Json::array({30,50}),47},
        {"[magical defense]",Json::array({40,60}),62},
        {"[equipment physical attack]",Json::array({100.9,200.9}),77},
        {"[equipment magical attack]",Json::array({200,400}),92},
        {"[equipment physical defense]",Json::array({300,500}),107},
        {"[equipment magical defense]",Json::array({400,600}),122},
        {"[ability category]",Json::array({"[PHYSICAL_ATTACK]","*",150,"[PHYSICAL_ATTACK]","+",0.9,
            "[EQUIPMENT_PHYSICAL_ATTACK]","*",50,"[EQUIPMENT_PHYSICAL_ATTACK]","+",10,
            "[EQUIPMENT_MAGICAL_DEFENSE]","+",3,"[HP MAX]","*",90}),137},
        {"[/ability category]",Json::array(),337},
        {"[unknown future field]",Json::array({"retained","retained",7}),342}};
    source.table.path="fixture/combat.tbl";source.table.rawBytes.resize(362,0);
    source.table.source={{"package_identity","fixture-content"}};
    source.tableSelection="fixture_explicit_source_table";
    for(int level=1;level<=3;++level) for(int column=0;column<24;++column) {
        int value=0;
        if(column==0) value=level;
        else if(column>=1 && column<=4) value=level*10+column;
        else if(column==5) value=level*100;
        else if(column==6) value=level*50;
        else if(column>=7 && column<=10) value=level*100+column;
        source.table.tokens.push_back({{"offset",2+source.table.tokens.size()*5},{"type",2},{"raw",value},{"value",value}});
    }
    return source;
}
void appendField(MonsterAttributeSource &source,const std::string &tag,Json values) {
    const size_t offset=source.monster.rawBytes.size();
    source.monster.rawBytes.resize(offset+5*(values.size()+1),0);
    source.monster.fields.push_back({tag,std::move(values),offset});
}
bool diagnostic(const MonsterCombatAttributes &value,const std::string &kind) {
    for(const auto &entry:value.diagnostics) if(entry.value("kind",std::string())==kind) return true;
    return false;
}
MonsterAttributeSource tableOnlyFixture() {
    auto source=combatFixture();
    source.monster.fields={{"[level]",Json::array({1,3}),2}};
    return source;
}
} // namespace

Json runMonsterCombatAttributeTests(Pvf &pvf) {
    Json checks=Json::array();
    const auto check=[&](bool ok,const std::string &message) {
        if(!ok) throw std::runtime_error("Monster combat attributes: "+message);
        checks.push_back(message);
    };
    const auto policy=MonsterCombatAttributePolicy::inferredMobCombatTableV1();
    const auto evaluate=[&](const MonsterAttributeSource &source,int level=2,bool boss=false) {
        return evaluateMonsterCombatAttributes(source,level,boss,policy);
    };
    const auto source=combatFixture();
    const auto low=evaluate(source,1),mid=evaluate(source,2),high=evaluate(source,3);
    check(low.usable() && mid.usable() && high.usable() &&
          low.attributes->physicalAttackCoefficient==15 && mid.attributes->physicalAttackCoefficient==22 &&
          high.attributes->physicalAttackCoefficient==30 && mid.attributes->magicalAttackCoefficient==30 &&
          mid.attributes->physicalDefenseCoefficient==40 && mid.attributes->magicalDefenseCoefficient==50,
          "All four coefficient endpoints interpolate then consume ordered integer category steps at both ends and midpoint");
    check(low.attributes->equipmentPhysicalAttack==60 && mid.attributes->equipmentPhysicalAttack==85 &&
          high.attributes->equipmentPhysicalAttack==110 && mid.attributes->equipmentMagicalAttack==300 &&
          mid.attributes->equipmentPhysicalDefense==400 && mid.attributes->equipmentMagicalDefense==503,
          "Equipment attack and defense remain separate from coefficients and consume their own endpoints and categories");
    auto tableOnly=tableOnlyFixture();const auto table=evaluate(tableOnly);
    check(table.usable() && table.attributes->physicalAttackCoefficient==21 && table.attributes->magicalAttackCoefficient==22 &&
          table.attributes->physicalDefenseCoefficient==23 && table.attributes->magicalDefenseCoefficient==24 &&
          table.attributes->equipmentPhysicalAttack==207 && table.attributes->equipmentMagicalAttack==209 &&
          table.attributes->equipmentPhysicalDefense==208 && table.attributes->equipmentMagicalDefense==210,
          "Distinct fixture columns prove raw 1/2/3/4 and equipment 7/9/8/10 mappings without attack-defense transposition");
    auto reversed=source;
    reversed.monster.fields[9].values=Json::array({"[EQUIPMENT_PHYSICAL_ATTACK]","+",10,"[EQUIPMENT_PHYSICAL_ATTACK]","*",50});
    const auto reverseResult=evaluate(reversed);
    check(reverseResult.usable() && reverseResult.attributes->equipmentPhysicalAttack==80 &&
          mid.attributes->equipmentPhysicalAttack==85,
          "Reversing addition and percentage changes the result instead of sorting or collapsing authored category order");
    const auto receipt=mid.snapshot(true);
    check(receipt["source_documents"]["monster"]["raw_bytes"]==Json(source.monster.rawBytes) &&
          receipt["source_documents"]["monster"]["fields"].back()["values"]==Json::array({"retained","retained",7}) &&
          receipt["source_documents"]["table"]["tokens"]==source.table.tokens &&
          mid.trace[0]["columns"].size()==24 && mid.trace[0]["source"]["byte_offset"]==122 &&
          mid.sources["monster"]["package_identity"]=="fixture-content" &&
          source.monster.rawBytes==combatFixture().monster.rawBytes,
          "Receipts own unchanged raw documents, repeated unknowns, exact row offsets, tokens and package identity");
    check(policy.describe()["classification"]=="inferred_beta" && policy.describe()["native_pc_parity"]=="pending" &&
          !evaluateMonsterCombatAttributes(source,2,false).usable(),
          "The named inference requires explicit selection and never advertises native PC confirmation");
    for(const auto level:{0,-1,4})
        check(!evaluate(source,level).usable(),"Nonpositive or absent exact table level cannot fall back: "+std::to_string(level));
    auto clamped=source;clamped.monster.fields[0].values=Json::array({2,3});
    const auto clamp=evaluate(clamped,1);
    check(clamp.usable() && clamp.attributes->physicalAttackCoefficient==15 &&
          diagnostic(clamp,"monster_combat_endpoint_level_clamped"),
          "Endpoint clamping is explicit and retains the separate exact growth-table row");
    auto singleton=source;singleton.monster.fields[0].values=Json::array({2,2});
    const auto single=evaluate(singleton);
    check(single.usable() && single.attributes->physicalAttackCoefficient==15 &&
          diagnostic(single,"single_level_monster_combat_conflicting_endpoints"),
          "A singleton range consumes its first endpoint and reports conflicting second values without division by zero");

    for(const auto bad:{Json::array(),Json::array({1}),Json::array({1,2,3}),Json::array({-1,2}),
            Json::array({"one",2}),Json::array({1,std::numeric_limits<double>::infinity()}),
            Json::array({1,uint64_t(std::numeric_limits<uint64_t>::max())})}) {
        auto malformed=source;malformed.monster.fields[1].values=bad;
        check(!evaluate(malformed,3).usable(),"Malformed or out-of-range combat endpoints block: "+bad.dump());
    }
    for(const auto index:{1,2,3,4,5,6,7,8}) {
        auto duplicated=source;
        appendField(duplicated,source.monster.fields[index].tag,source.monster.fields[index].values);
        check(!evaluate(duplicated).usable() && diagnostic(evaluate(duplicated),"ambiguous_monster_combat_field"),
              "Every combat endpoint rejects duplicate source declarations: "+source.monster.fields[index].tag);
    }
    auto missingRange=source;missingRange.monster.fields.erase(missingRange.monster.fields.begin());
    check(!evaluate(missingRange).usable(),"Combat endpoints cannot invent an absent MOB level range");
    auto duplicateRange=source;appendField(duplicateRange,"[level]",Json::array({1,3}));
    check(!evaluate(duplicateRange).usable(),"Source preflight rejects ambiguous level ranges before any combat values publish");
    for(const auto bad:{Json::array({1,3,5}),Json::array({3,1}),Json::array({1.5,3}),Json::array({0,3})}) {
        auto malformed=source;malformed.monster.fields[0].values=bad;
        check(!evaluate(malformed).usable(),"Source preflight rejects malformed MOB level ranges: "+bad.dump());
    }
    auto overflow=source;overflow.monster.fields[9].values=Json::array({"[PHYSICAL_ATTACK]","*",1e308});
    check(!evaluate(overflow).usable() && diagnostic(evaluate(overflow),"invalid_monster_combat_category_result"),
          "A category multiplication overflow blocks rather than narrowing infinity into an integer");
    auto negative=source;negative.monster.fields[9].values=Json::array({"[EQUIPMENT_PHYSICAL_ATTACK]","+",-1000});
    check(!evaluate(negative).usable(),"Combat category subtraction cannot publish a negative attack or defense");
    auto wrongCategory=source;wrongCategory.monster.fields[9].values=Json::array({"[FUTURE_DAMAGE]","*",150});
    check(!evaluate(wrongCategory).usable() && diagnostic(evaluate(wrongCategory),"unsupported_monster_combat_category"),
          "An unknown ability category carries a concrete diagnostic instead of disappearing");
    for(const auto bad:{Json::array({"[PHYSICAL_ATTACK]","*"}),Json::array({"[PHYSICAL_ATTACK]","/",10}),
            Json::array({"[PHYSICAL_ATTACK]","*","many"})}) {
        auto malformed=source;malformed.monster.fields[9].values=bad;
        check(!evaluate(malformed).usable(),"Shared source preflight rejects malformed category tuples: "+bad.dump());
    }
    auto duplicateCategory=source;appendField(duplicateCategory,"[ability category]",Json::array());
    check(!evaluate(duplicateCategory).usable(),"Repeated category blocks cannot silently choose a winning declaration");
    auto duplicateRow=tableOnly;duplicateRow.table.tokens[24]["value"]=1;
    check(!evaluate(duplicateRow).usable(),"Duplicate table levels reject before exact-row selection");
    auto partialRow=tableOnly;partialRow.table.tokens.erase(partialRow.table.tokens.end()-1);
    check(!evaluate(partialRow).usable(),"Partial base-table rows cannot form a usable combat input");
    for(const auto bad:{Json(2.5),Json("twenty"),Json(uint64_t(std::numeric_limits<uint64_t>::max()))}) {
        auto malformed=tableOnly;malformed.table.tokens[25]["value"]=bad;
        check(!evaluate(malformed).usable(),"Base-table values must be exact int32 tokens: "+bad.dump());
    }
    auto negativeTable=tableOnly;negativeTable.table.tokens[25]["value"]=-1;
    check(!evaluate(negativeTable).usable(),"Negative source coefficient rejects without substituting a demo attack");
    auto package=source;package.table.source["package_identity"]="other-pvf";
    check(!evaluate(package).usable() && diagnostic(evaluate(package),"monster_combat_source_identity_mismatch"),
          "Monster and table from different source packages cannot be combined");

    auto resistances=tableOnly;
    appendField(resistances,"[fire resistance]",Json::array({-21,-1}));
    appendField(resistances,"[water resistance]",Json::array({30,50}));
    appendField(resistances,"[slow resistance]",Json::array({-10,10}));
    appendField(resistances,"[stuck resistance]",Json::array({-30,-10}));
    resistances.table.tokens[24+12]["value"]=25;
    resistances.table.tokens[24+13]["value"]=7;
    resistances.table.tokens[24+17]["value"]=3;
    resistances.table.tokens[24+23]["value"]=4;
    const auto resistant=evaluate(resistances);
    check(resistant.usable() && resistant.attributes->elementalAttack[0]==7 &&
          resistant.attributes->elementalResistance[0]==-8 && resistant.attributes->elementalResistance[1]==40 &&
          resistant.attributes->statusResistance[0]==4 && resistant.attributes->statusResistance[13]==-18 &&
          resistant.attributes->statusResistance[16]==4,
          "Signed element/status endpoints combine with distinct table columns and special stuck divisor without mixing HP");
    auto stuckCategory=resistances;
    appendField(stuckCategory,"[ability category]",Json::array({"[STUCK]","+",7}));
    appendField(stuckCategory,"[/ability category]",Json::array());
    const auto stuck=evaluate(stuckCategory);
    check(stuck.usable() && stuck.attributes->statusResistance[13]==-11,
          "The STUCK category modifies the dedicated status resistance after source interpolation and table addition");
    auto resistanceOverflow=tableOnly;
    appendField(resistanceOverflow,"[fire resistance]",Json::array({std::numeric_limits<int>::max(),std::numeric_limits<int>::max()}));
    resistanceOverflow.table.tokens[24+17]["value"]=1;
    check(!evaluate(resistanceOverflow).usable() && diagnostic(evaluate(resistanceOverflow),"monster_elemental_resistance_overflow"),
          "Resistance additions use checked wide arithmetic before narrowing");
    auto unresolvedColumn=tableOnly;unresolvedColumn.table.tokens[24+11]["value"]=1;
    const auto consumedColumn=evaluate(unresolvedColumn);
    check(consumedColumn.usable() && consumedColumn.attributes->tableAttackMissDeltaPercent==0.01f &&
          consumedColumn.attributes->tableAttackMissSource.at("raw_value")==1,
          "Source raw11 is consumed as a distinct inferred attacker miss delta with its exact raw receipt");
    for(const auto tag:{"[absolute damage]","[absolute damage resistance rate]","[absolute defense ignore rate]",
                       "[physical critical hit]","[attack success rate]","[hp regen rate]"}) {
        auto neutral=tableOnly;appendField(neutral,tag,Json::array({0,0}));
        check(evaluate(neutral).usable(),"An explicit neutral unresolved input has a retained receipt: "+std::string(tag));
        neutral.monster.fields.back().values=Json::array({1});
        check(!evaluate(neutral).usable() && diagnostic(evaluate(neutral),"unsupported_monster_combat_input"),
              "Nonneutral authored damage/hit/critical/regen inputs fail closed: "+std::string(tag));
    }
    auto futureDamage=tableOnly;appendField(futureDamage,"[future damage multiplier]",Json::array({2}));
    check(!evaluate(futureDamage).usable() && diagnostic(evaluate(futureDamage),"unsupported_monster_combat_field"),
          "Unknown material damage fields are diagnosed by source tag instead of being silently neutralized");
    auto pvp=tableOnly;appendField(pvp,"[pvp]",Json::array());
    appendField(pvp,"[physical attack]",Json::array({999,999}));appendField(pvp,"[/pvp]",Json::array());
    check(evaluate(pvp).usable() && evaluate(pvp).attributes->physicalAttackCoefficient==21,
          "Excluded PvP endpoint values cannot override the selected PvE source scope");
    auto nested=tableOnly;
    nested.monster.fields={{"[level]",Json::array({1,3}),2},{"[ability category]",Json::array(),17},
        {"[EQUIPMENT_PHYSICAL_ATTACK]",Json::array({"*",50}),22},{"[/ability category]",Json::array(),37}};
    nested.monster.tokens=Json::array({{{"offset",17},{"type",5},{"value","[ability category]"}},
        {{"offset",22},{"type",5},{"value","[EQUIPMENT_PHYSICAL_ATTACK]"}},{{"offset",27},{"type",7},{"value","*"}},
        {{"offset",32},{"type",2},{"value",50}},{{"offset",37},{"type",5},{"value","[/ability category]"}}});
    const auto nestedResult=evaluate(nested);
    check(nestedResult.usable() && nestedResult.attributes->equipmentPhysicalAttack==103,
          "Type-5 nested category keys execute from ordered tokens and cannot masquerade as top-level endpoints");
    nested.monster.tokens.erase(nested.monster.tokens.end()-1);
    check(!evaluate(nested).usable(),"Unterminated type-5 categories fail shared document preflight");

    const auto goblinSource=readMonsterAttributeSource(pvf,"monster/goblin/goblin.mob",false);
    const auto lugaruSource=readMonsterAttributeSource(pvf,"monster/lugaru/lugaru.mob",false);
    const auto tauSource=readMonsterAttributeSource(pvf,"monster/tau/taubeast.mob",true);
    const auto goblin=evaluate(goblinSource,1),lugaru=evaluate(lugaruSource,9),tau=evaluate(tauSource,4,true);
    check(goblin.usable() && goblin.attributes->physicalAttackCoefficient==5 && goblin.attributes->magicalAttackCoefficient==5 &&
          goblin.attributes->equipmentPhysicalAttack==9 && goblin.attributes->equipmentMagicalAttack==9 &&
          goblin.attributes->equipmentPhysicalDefense==12 && goblin.attributes->equipmentMagicalDefense==12,
          "Current goblin applies authored equipment 90 percent to 11/14, retaining raw four coefficients at 5");
    check(lugaru.usable() && lugaru.attributes->physicalAttackCoefficient==45 && lugaru.attributes->equipmentPhysicalAttack==36 &&
          lugaru.attributes->equipmentMagicalAttack==36 && lugaru.attributes->equipmentPhysicalDefense==499 &&
          lugaru.attributes->equipmentMagicalDefense==499,
          "Current Lugaru consumes its level-9 row and own 80-percent equipment categories");
    check(tau.usable() && tau.attributes->physicalAttackCoefficient==20 && tau.attributes->equipmentPhysicalAttack==24 &&
          tau.attributes->equipmentMagicalAttack==19 && tau.attributes->equipmentPhysicalDefense==139 &&
          tau.attributes->equipmentMagicalDefense==111 && tauSource.table.path=="monster/bossmonsterbaseparameter.tbl",
          "MAP boss role selects the boss table and Tau retains separate 100/80-percent physical/magical equipment groups");
    const auto hpBefore=evaluateMonsterHp(goblinSource,1,false,MonsterHpPolicy::inferredMobTableHpV1());
    const auto hpAfter=evaluateMonsterHp(goblin.source,1,false,MonsterHpPolicy::inferredMobTableHpV1());
    check(hpBefore.hp==35 && hpAfter.snapshot()==hpBefore.snapshot() &&
          goblin.source.monster.rawBytes==pvf.read(goblinSource.monster.path) &&
          goblin.sources["table"]["package_identity"]==pvf.identity() && !goblin.snapshot().contains("hp"),
          "Combat evaluation preserves independent HP receipts and original current-source bytes without returning or healing live HP");
    const auto boss9=evaluate(readMonsterAttributeSource(pvf,"monster/tau/taubeast.mob",true),9,true);
    check(boss9.usable() && boss9.attributes->tableAttackMissDeltaPercent==0.01f &&
          boss9.attributes->tableAttackMissSource.at("raw_value")==1,
          "A real boss level9 freezes and consumes its source raw11 rather than losing it to a removed gate");
    const auto rejectsRestore=[&](const Json &snapshot,const MonsterAttributeSource &expected) {
        try {restoreMonsterCombatAttributes(snapshot,expected);} catch(const std::exception &) {return true;}
        return false;
    };
    auto frozen=mid.snapshot();
    frozen["future_root"]=Json::array({"retained","retained",7});
    frozen["attributes"]["future_attribute"]={{"payload",Json::array({3,2,1})}};
    frozen["sources"]["monster"]["future_source"]=true;
    frozen["trace"][0]["future_trace"]="preserved";
    const auto restored=restoreMonsterCombatAttributes(frozen,source);
    check(restored.usable() && restored.attributes->equipmentPhysicalAttack==85 && restored.snapshot()==frozen,
          "Frozen combat receipts restore typed values and round-trip root/attribute/source/trace unknown metadata");
    const auto fullFrozen=mid.snapshot(true);
    check(restoreMonsterCombatAttributes(fullFrozen,source).snapshot(true)==fullFrozen,
          "Explicit full-source exports restore with raw bytes, ordered tokens and fields validated against expected source");
    auto noRecalculation=frozen;
    noRecalculation["attributes"]["equipment_physical_attack"]=123;
    check(restoreMonsterCombatAttributes(noRecalculation,source).attributes->equipmentPhysicalAttack==123,
          "Restoration consumes frozen valid attributes without recomputing or replacing them from current source arithmetic");
    for(const auto field:{"schema","policy","classification","level","boss","usable","attributes","sources","trace","diagnostics"}) {
        auto corrupt=frozen;corrupt.erase(field);
        check(rejectsRestore(corrupt,source),"Missing required receipt member rejects the entire restore: "+std::string(field));
    }
    for(const auto bad:{Json(),Json::array(),Json(7),Json("receipt")})
        check(rejectsRestore(bad,source),"Nonobject frozen receipt rejects: "+bad.dump());
    for(const auto bad:{Json(-1),Json(0),Json(1.5),Json("2"),Json(uint64_t(std::numeric_limits<uint64_t>::max()))}) {
        auto corrupt=frozen;corrupt["level"]=bad;
        check(rejectsRestore(corrupt,source),"Frozen level shape and range reject before publication: "+bad.dump());
    }
    auto changedLevel=frozen;changedLevel["level"]=3;
    check(rejectsRestore(changedLevel,source),"Frozen level must agree with the preserved exact-row receipt");
    for(const auto field:{"physical_attack_coefficient","magical_attack_coefficient","physical_defense_coefficient",
                         "magical_defense_coefficient","equipment_physical_attack","equipment_magical_attack",
                         "equipment_physical_defense","equipment_magical_defense"}) {
        for(const auto bad:{Json(-1),Json(1.5),Json("attack"),Json(uint64_t(std::numeric_limits<uint64_t>::max()))}) {
            auto corrupt=frozen;corrupt["attributes"][field]=bad;
            check(rejectsRestore(corrupt,source),"Frozen attack/defense requires nonnegative int32: "+std::string(field)+"="+bad.dump());
        }
    }
    const auto resistantSaved=resistant.snapshot();
    const auto resistantRestored=restoreMonsterCombatAttributes(resistantSaved,resistances);
    check(resistantRestored.attributes->elementalResistance[0]==-8 && resistantRestored.attributes->statusResistance[13]==-18 &&
          resistantRestored.snapshot()==resistantSaved,
          "Signed elemental/status resistances survive frozen typed restoration without unsigned conversion");
    for(const auto field:{"elemental_attack","elemental_resistance","status_resistance"}) {
        auto corrupt=frozen;corrupt["attributes"][field].erase(corrupt["attributes"][field].end()-1);
        check(rejectsRestore(corrupt,source),"Frozen resistance arrays require exact source axis width: "+std::string(field));
        corrupt=frozen;corrupt["attributes"][field][0]=uint64_t(std::numeric_limits<uint64_t>::max());
        check(rejectsRestore(corrupt,source),"Frozen signed resistance still rejects int32 overflow: "+std::string(field));
    }
    for(const auto field:{"physical_critical_rate","magical_critical_rate","hit_rate_bonus","evasion_rate_bonus",
                         "absolute_damage","flat_damage_reduction","absolute_defense_rate","absolute_damage_resistance_rate",
                         "absolute_defense_ignore_rate"}) {
        auto corrupt=frozen;corrupt["attributes"][field]=1;
        check(rejectsRestore(corrupt,source),"Frozen receipt cannot introduce an unsupported nonneutral mechanism: "+std::string(field));
    }
    for(const auto kind:{"monster","table"}) for(const auto field:{"package_identity","member_path","member_sha256","encoding","byte_offset","byte_length"}) {
        auto corrupt=frozen;corrupt["sources"][kind][field]="wrong";
        check(rejectsRestore(corrupt,source),"Frozen source path/hash/package/span mismatch rejects: "+std::string(kind)+"/"+field);
    }
    auto changedBytes=source;changedBytes.monster.rawBytes[0]^=1;
    check(rejectsRestore(frozen,changedBytes),"Changed current MOB bytes cannot accept a frozen receipt under its previous hash");
    auto changedTable=source;changedTable.table.rawBytes[0]^=1;
    check(rejectsRestore(frozen,changedTable),"Changed current base-table bytes cannot accept a frozen receipt under its previous hash");
    auto changedRole=goblin.snapshot();changedRole["boss"]=true;
    check(rejectsRestore(changedRole,goblinSource),"Role-selected normal table receipts cannot be reclassified as a boss");
    auto errorReceipt=frozen;errorReceipt["diagnostics"].push_back({{"kind","corrupt"},{"severity","error"}});
    check(rejectsRestore(errorReceipt,source),"Blocking saved diagnostics cannot be hidden behind a usable flag");
    auto absentTrace=frozen;absentTrace["trace"]=Json::array();
    check(rejectsRestore(absentTrace,source),"An attributed frozen value requires its preserved calculation trace");
    auto wrongColumns=frozen;wrongColumns["trace"][0]["columns"][1]=999;
    check(rejectsRestore(wrongColumns,source),"Frozen exact-row evidence must match the expected immutable source table");
    auto wrongDocuments=fullFrozen;wrongDocuments["source_documents"]["monster"]["raw_bytes"][0]=255;
    check(rejectsRestore(wrongDocuments,source),"Embedded source exports cannot disagree with expected raw bytes");
    const auto unsupported=evaluate(wrongCategory);
    check(!unsupported.usable() && rejectsRestore(unsupported.snapshot(),unsupported.source),"An unsupported combat result cannot be resurrected as a valid frozen snapshot");
    return {{"status","pass"},{"policy",policy.describe()},{"checks",checks},{"check_count",checks.size()},
        {"source_examples",Json::array({goblin.snapshot(),lugaru.snapshot(),tau.snapshot()})},
        {"scope","source combat coefficients/equipment/resistances only; HP authority, live World publication, final damage, AI, difficulty/champion rules and original-client parity are separate"}};
}
} // namespace dnf
