#include "dnf/combat_attributes.hpp"
#include "dnf/progression.hpp"
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
void combatSpans(Script &script) {
    size_t offset=2;
    for (auto &field:script.fields) { field.offset=offset; offset+=5*(1+field.values.size()); }
    script.rawBytes.assign(offset,0);
}
CharacterBaseAttributes combatBase() {
    CharacterBaseAttributes base; base.level=5; base.policy="inferred-chr-growth-v1";
    base.source={{"path","character/fixture.chr"},{"provenance",{{"package_identity","fixture-package"}}}};
    const std::pair<ChrAttribute,float> values[]={{ChrAttribute::HpMax,100},{ChrAttribute::MpMax,50},
        {ChrAttribute::PhysicalAttack,12.25f},{ChrAttribute::PhysicalDefense,21.25f},
        {ChrAttribute::MagicalAttack,31.5f},{ChrAttribute::MagicalDefense,41.5f}};
    for (const auto &[attribute,number]:values) {
        CharacterAttributeValue value; value.state=CharacterAttributeState::Value; value.value=number;
        value.unit=attribute==ChrAttribute::HpMax?"hp_points":attribute==ChrAttribute::MpMax?"mp_points":"chr_base_coefficient";
        value.trace.push_back({{"fixture_source",true}}); base.attributes.emplace(attribute,std::move(value));
    }
    for (const auto attribute:{ChrAttribute::FireResistance,ChrAttribute::WaterResistance,ChrAttribute::DarkResistance,ChrAttribute::LightResistance}) {
        CharacterAttributeValue value; value.state=CharacterAttributeState::Value; value.value=2.5f;
        value.unit="source_resistance_points"; base.attributes.emplace(attribute,std::move(value));
    }
    return base;
}
Script combatConstants(float physical=5,float magical=5) {
    Script script; script.path="etc/etcparameter.etc";
    script.source={{"package_identity","fixture-package"},{"literal_path","ETC/EtcParameter.etc"}};
    Json values=Json::array(); for (int i=0;i<27;++i) values.push_back(i==22?physical:i==23?magical:0.0f);
    script.fields.push_back({"[damage fomula constant]",values,0}); combatSpans(script); return script;
}
EquippedAttributeSource combatItem(int uid,const std::string &slot) {
    EquippedAttributeSource item; item.instanceUid=uid; item.equippedSlot=slot; item.currentDurability=35;
    item.source.path="equipment/fixture/"+std::to_string(uid)+".equ";
    item.source.source={{"package_identity","fixture-package"},{"literal_path",item.source.path}};
    item.source.fields={{"[usable job]",Json::array({"[swordman]"}),0},{"[equipment type]",Json::array({slot,17}),0},
        {"[minimum level]",Json::array({1}),0},{"[durability]",Json::array({35}),0}};
    return item;
}
void append(EquippedAttributeSource &item,const std::string &tag,Json values) {
    item.source.fields.push_back({tag,std::move(values),0}); combatSpans(item.source);
}
bool combatDiagnostic(const CombatAttributeSnapshot &result,const std::string &kind) {
    for (const auto &entry:result.diagnostics) if (entry.value("kind",std::string())==kind) return true;
    return false;
}
} // namespace

Json runCombatAttributeTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array();
    const auto check=[&](bool okay,const char *message) {
        if (!okay) throw std::runtime_error(std::string("Combat attributes: ")+message);
        checks.push_back(message);
    };
    const auto base=combatBase(); const auto before=base.snapshot();
    CharacterDefinition character; character.registration.id=0; character.job="[swordman]";
    const auto policy=CombatAttributePolicy::inferredEquipmentCombatStatV1(combatConstants());
    check(!evaluateCombatAttributes(base,character,{},5).usable(),"The default policy cannot enable inferred combat attributes");
    const auto empty=evaluateCombatAttributes(base,character,{},5,policy);
    check(empty.usable() && empty.strength==12.25f && empty.vitality==21.25f && empty.intelligence==31.5f && empty.spirit==41.5f &&
          empty.physicalAttack==0 && empty.magicalAttack==0 && empty.physicalDefense==106.25f && empty.magicalDefense==207.5f &&
          empty.independentRate==1 && empty.weaponElement==4,
          "Pure CHR coefficients map to separate primary inputs and source-selected defense factors without inventing a training weapon");
    check(base.snapshot()==before && empty.pureChr.snapshot()==before,
          "The input and owned pure CHR copy preserve coefficient units, source traces and resource maxima");
    auto weapon=combatItem(10,"[weapon]");
    append(weapon,"[equipment physical attack]",Json::array({22,12}));
    append(weapon,"[equipment magical attack]",Json::array({24,14}));
    append(weapon,"[separate attack]",Json::array({21,10}));
    append(weapon,"[separate rate]",Json::array({1.5f,0.5f}));
    append(weapon,"[physical critical hit]",Json::array({2}));
    append(weapon,"[stuck]",Json::array({1}));
    append(weapon,"[physical absolute damage]",Json::array({3}));
    append(weapon,"[magical absolute damage]",Json::array({4}));
    append(weapon,"[elemental property]",Json::array({"[fire element]"}));
    append(weapon,"[unknown authored field]",Json::array({"keep",17,17}));
    weapon.source.tokens.push_back({{"fixture_raw_token",true}});
    auto coat=combatItem(20,"[coat]");
    append(coat,"[physical attack]",Json::array({3})); append(coat,"[physical defense]",Json::array({4}));
    append(coat,"[magical attack]",Json::array({5})); append(coat,"[magical defense]",Json::array({6}));
    append(coat,"[equipment physical defense]",Json::array({100,60}));
    append(coat,"[equipment magical defense]",Json::array({200,80}));
    append(coat,"[physical absolute defense]",Json::array({12.5f}));
    append(coat,"[magical absolute defense]",Json::array({7.5f}));
    append(coat,"[all elemental resistance]",Json::array({3})); append(coat,"[dark resistance]",Json::array({-2}));
    append(coat,"[fire attack]",Json::array({4})); append(coat,"[stuck resistance]",Json::array({13}));
    const auto combined=evaluateCombatAttributes(base,character,{coat,weapon},5,policy);
    bool durabilityConsumed=false;
    for (const auto &entry:combined.trace) if (entry.value("stage",std::string())=="consumed_equipment_metadata" &&
        entry.value("tag",std::string())=="[durability]" && entry.value("instance_uid",int64_t(0))==10)
        durabilityConsumed=entry["values"]==Json::array({35}) && entry["current_durability"]==35 &&
            entry["consumer"]=="combat durability qualification and broken-item activation";
    check(combined.usable() && durabilityConsumed && !combatDiagnostic(combined,"unsupported_combat_equipment_field"),
          "Maximum/current durability is an evidenced lifecycle consumer and is not mistaken for an unknown ability effect");
    check(combined.usable() && combined.strength==15.25f && combined.vitality==25.25f && combined.intelligence==36.5f && combined.spirit==47.5f &&
          combined.physicalAttack==22 && combined.magicalAttack==24 && combined.equipmentPhysicalDefense==100 &&
          combined.equipmentMagicalDefense==200 && combined.physicalDefense==226.25f && combined.magicalDefense==437.5f,
          "Primary-stat flats and PvE physical/magical attack/defense groups stay separate and select only mode index zero");
    check(combined.independentAttack==21 && combined.independentRate==1.5f && combined.physicalAbsoluteDamage==3 && combined.magicalAbsoluteDamage==4 &&
          combined.physicalAbsoluteDefensePercent==12.5f && combined.magicalAbsoluteDefensePercent==7.5f &&
          combined.physicalCriticalBonusPercent==2 && combined.magicalCriticalBonusPercent==0 && combined.attackMissDeltaPercent==1 &&
          combined.evasionPerMille==13 && combined.weaponElement==0 && combined.elementalAttack[0]==4 &&
          combined.elementalResistance[0]==5.5f && combined.elementalResistance[2]==3.5f,
          "Independent attack, factors, absolute groups, critical increments, miss, evasion and elements have independent typed values");
    check(evaluateCombatAttributes(base,character,{weapon,coat},5,policy).trace==combined.trace,
          "UID-ordered arithmetic and trace do not depend on the caller's equipped source order");
    const auto saved=combined.snapshot(true);
    check(saved["equipment_sources"][1]["fields"][4]["values"]==Json::array({22,12}) &&
          saved["equipment_sources"][1]["fields"].back()["values"]==Json::array({"keep",17,17}) &&
          saved["equipment_sources"][1]["ordered_tokens"]==weapon.source.tokens &&
          saved["equipment_sources"][1]["raw_bytes_hex"].get<std::string>().size()==weapon.source.rawBytes.size()*2 &&
          combined.equipmentSources[1].source.rawBytes==weapon.source.rawBytes && base.snapshot()==before,
          "The second source mode, unknown repeated operands, tokens, bytes and pure CHR remain owned and lossless");
    bool provenance=false;
    for (const auto &entry:combined.trace) if (entry.value("stage",std::string())=="equipment_combat_group" && entry["tag"]=="[equipment physical attack]")
        provenance=entry["candidates"][0]["source"]["package_identity"]=="fixture-package" &&
            entry["candidates"][0]["source"]["member_sha256"]==sha256(weapon.source.rawBytes) &&
            entry["candidates"][0]["source"]["ordinal"]==4 && entry["source_values"]==Json::array({22,12});
    check(provenance,"Combat traces retain exact source package, computed hash, field ordinal, span and both mode operands");
    const auto alternate=CombatAttributePolicy::inferredEquipmentCombatStatV1(combatConstants(7,11));
    const auto changed=evaluateCombatAttributes(base,character,{},5,alternate);
    check(changed.usable() && changed.physicalDefense==148.75f && changed.magicalDefense==456.5f &&
          changed.vitalityDefenseFactor==7 && changed.spiritDefenseFactor==11,
          "VIT/SPR conversion reads the explicit source constants rather than scattering literal five factors");
    auto noPrimary=policy; noPrimary.derivePrimaryDefense=false;
    const auto excluded=evaluateCombatAttributes(base,character,{coat},5,noPrimary);
    check(excluded.usable() && excluded.physicalDefense==100 && excluded.magicalDefense==200 &&
          excluded.policyDetails["derive_primary_defense"]==false,
          "Primary-defense conversion is an explicit independently recorded policy switch");
    auto broken=weapon; broken.currentDurability=0;
    const auto brokenResult=evaluateCombatAttributes(base,character,{broken},5,policy);
    check(brokenResult.usable() && brokenResult.physicalAttack==0 && brokenResult.magicalAttack==0 && brokenResult.independentAttack==0 &&
          brokenResult.physicalCriticalBonusPercent==0 && brokenResult.weaponElement==4 && combatDiagnostic(brokenResult,"broken_combat_equipment_inactive"),
          "A broken durable weapon removes every combat group including independent, critical and element contributions");
    auto infinite=weapon; infinite.source.fields[3].values=Json::array({0}); infinite.currentDurability=0;
    const auto infiniteResult=evaluateCombatAttributes(base,character,{infinite},5,policy);
    check(infiniteResult.usable() && infiniteResult.physicalAttack==22 && infiniteResult.magicalAttack==24,
          "Zero source maximum durability means nondurable and retains combat values at current zero");
    for (const auto &invalid:{Json::array(),Json::array({-1}),Json::array({1,2}),Json::array({1.5})}) {
        auto malformed=weapon; malformed.source.fields[3].values=invalid; combatSpans(malformed.source);
        check(!evaluateCombatAttributes(base,character,{malformed},5,policy).usable(),
              "Recognized durability metadata still requires exactly one nonnegative integer and a valid current value");
    }
    auto repeatedDurability=weapon; append(repeatedDurability,"[durability]",Json::array({35}));
    check(!evaluateCombatAttributes(base,character,{repeatedDurability},5,policy).usable(),
          "Duplicate maximum-durability metadata remains ambiguous and blocks equipment publication");
    auto unknownDurabilityEffect=weapon; append(unknownDurabilityEffect,"[durability bonus ability]",Json::array({0}));
    check(!evaluateCombatAttributes(base,character,{unknownDurabilityEffect},5,policy).usable(),
          "The metadata exception does not suppress an unknown durability-related ability even when its operand is zero");
    auto high=weapon; high.source.fields[2].values=Json::array({6});
    auto lowBase=base; lowBase.level=1; auto highBase=base; highBase.level=99;
    check(evaluateCombatAttributes(lowBase,character,{high},6,policy).usable() &&
          !evaluateCombatAttributes(highBase,character,{high},5,policy).usable(),
          "Normal equipment qualification is independent of both low and high debug effective CHR levels");
    check(!evaluateCombatAttributes(base,character,{weapon,weapon},5,policy).usable(),"Persistent UID and occupied slot cannot contribute twice");
    auto wrongSlot=weapon; wrongSlot.equippedSlot="[coat]";
    check(!evaluateCombatAttributes(base,character,{wrongSlot},5,policy).usable(),"Ownership slot must equal the authored EQU slot");
    auto wrongJob=weapon; wrongJob.source.fields[0].values=Json::array({"[mage]"});
    check(!evaluateCombatAttributes(base,character,{wrongJob},5,policy).usable(),"Current CHR job must qualify the owned weapon");
    auto foreign=weapon; foreign.source.source["package_identity"]="foreign";
    check(!evaluateCombatAttributes(base,character,{foreign},5,policy).usable(),"EQU and CHR package identities must agree");
    auto badHash=weapon; badHash.source.source["member_sha256"]="incorrect";
    check(!evaluateCombatAttributes(base,character,{badHash},5,policy).usable(),"An authored member hash conflicting with owned bytes blocks evaluation");
    auto badSpan=weapon; badSpan.source.fields[4].offset=std::numeric_limits<size_t>::max();
    check(!evaluateCombatAttributes(base,character,{badSpan},5,policy).usable(),"An invalid source span cannot contribute combat values");
    auto duplicate=weapon; append(duplicate,"[equipment physical attack]",Json::array({99,88}));
    check(!evaluateCombatAttributes(base,character,{duplicate},5,policy).usable(),"Repeated combat fields retain candidates and do not select the first value");
    for (const auto &invalid:{Json::array(),Json::array({1}),Json::array({1,2,3}),Json::array({true,2}),Json::array({1.5,2}),
            Json::array({std::numeric_limits<uint64_t>::max(),2})}) {
        auto malformed=weapon; malformed.source.fields[4].values=invalid;
        check(!evaluateCombatAttributes(base,character,{malformed},5,policy).usable(),
              "Mode-pair arity, signed i32 range and integer equipment points are validated without coercion");
    }
    auto otherSkill=coat; append(otherSkill,"[skill levelup]",Json::array({"[mage]",12,1}));
    check(evaluateCombatAttributes(base,character,{otherSkill},5,policy).usable(),"Skill increments for another source job are explicitly inactive");
    auto ownSkill=coat; append(ownSkill,"[skill levelup]",Json::array({"[swordman]",46,1}));
    check(!evaluateCombatAttributes(base,character,{ownSkill},5,policy).usable(),"A matching nonzero skill increment requires a real skill-ledger consumer");
    for (const auto *tag:{"[if]","[set ability]","[stat]","[avatar select ability]","[usable period]","[mystery attack group]","[physical damage reduce]"}) {
        auto unsupported=weapon; append(unsupported,tag,Json::array({1}));
        check(!evaluateCombatAttributes(base,character,{unsupported},5,policy).usable(),
              "Conditional, set, choice, qualification and unconsumed material combat groups fail closed");
    }
    auto neutral=weapon; append(neutral,"[physical damage reduce]",Json::array({0}));
    check(evaluateCombatAttributes(base,character,{neutral},5,policy).usable(),"A known zero additive unconsumed delta is recorded as neutral");
    auto badConstants=policy; badConstants.damageConstants.fields[0].values.erase(26);
    check(!evaluateCombatAttributes(base,character,{},5,badConstants).usable(),"The exact current 27-value constant source layout is required");
    auto wrongConstants=policy; wrongConstants.damageConstants.source["package_identity"]="foreign";
    check(!evaluateCombatAttributes(base,character,{},5,wrongConstants).usable(),"Primary-defense constants cannot cross the content package boundary");
    auto adjusted=base; adjusted.source["equipment_resource_evaluation"]=Json::object();
    check(!evaluateCombatAttributes(adjusted,character,{},5,policy).usable(),"The combat adapter requires a fresh pure CHR build rather than an adjusted resource cache");
    auto roundBase=base; roundBase.attributes.at(ChrAttribute::PhysicalAttack).value=16777216;
    auto one=coat; one.source.fields[4].values=Json::array({1});
    check(evaluateCombatAttributes(roundBase,character,{one},5,policy).strength==16777216,
          "Each main-stat addition stores binary32 before the next modifier consumer");

    CharacterCatalog characters(pvf); const auto &swordman=characters.at(0);
    const auto growth=CharacterGrowthPolicy::inferredChrGrowthV1();
    const auto realBase=buildCharacterBaseAttributes(swordman,{},5,growth);
    const auto realLow=buildCharacterBaseAttributes(swordman,{},1,growth);
    const auto realPolicy=CombatAttributePolicy::inferredEquipmentCombatStatV1(pvf.script("etc/etcparameter.etc"));
    RegionCatalog catalog(pvf,assets); Progression progression(catalog); progression.initialize(5);
    const auto starter=evaluateCombatAttributes(realBase,progression,swordman,realPolicy);
    check(starter.usable() && starter.physicalAttack==5 && starter.magicalAttack==5 && starter.independentAttack==0 &&
          starter.strength==realBase.value(ChrAttribute::PhysicalAttack),
          "Real starter 27118 contributes its exact five/five source attack without a training-weapon offset");
    const auto starterState=progression.state;
    const auto starterUid=progression.state.at("equipped").at("[weapon]");
    bool sourceDurabilityConsumed=false;
    for (const auto &entry:starter.trace) if (entry.value("stage",std::string())=="consumed_equipment_metadata" &&
        entry.value("tag",std::string())=="[durability]")
        sourceDurabilityConsumed=entry["values"]==Json::array({35}) && entry["current_durability"]==35 &&
            entry["source"]["member_path"]=="equipment/character/swordman/weapon/ssword/sswd_default.equ";
    check(sourceDurabilityConsumed && !combatDiagnostic(starter,"unsupported_combat_equipment_field"),
          "Real sswd_default source durability35 is attributed to its existing consumer instead of blocking initial World preparation");
    for (auto &entry:progression.state["inventory"]) if (entry["uid"]==starterUid) entry["durability"]=0;
    const auto brokenStarter=evaluateCombatAttributes(realBase,progression,swordman,realPolicy);
    check(brokenStarter.usable() && brokenStarter.physicalAttack==0 && brokenStarter.magicalAttack==0 &&
          combatDiagnostic(brokenStarter,"broken_combat_equipment_inactive") &&
          !combatDiagnostic(brokenStarter,"unsupported_combat_equipment_field"),
          "Real starter current durability zero removes both attack groups while source maximum durability remains valid metadata");
    for (auto &entry:progression.state["inventory"]) if (entry["uid"]==starterUid) entry["durability"]=1;
    const auto repairedStarter=evaluateCombatAttributes(realBase,progression,swordman,realPolicy);
    check(repairedStarter.usable() && repairedStarter.physicalAttack==5 && repairedStarter.magicalAttack==5,
          "Repairing the real starter to positive current durability restores its exact source attack groups");
    progression.state=starterState;
    const auto grantFixture=[&](int id) {
        const auto *definition=progression.item(id);
        if (!definition) throw std::runtime_error("Missing real combat EQU fixture");
        const int uid=progression.state.at("next_uid").get<int>();
        progression.state["inventory"].push_back({{"uid",uid},{"id",id},{"count",1},{"durability",definition->durability}});
        progression.state["next_uid"]=uid+1;
        return int(progression.state["inventory"].size()-1);
    };
    const int katanaIndex=grantFixture(27600);
    check(progression.equip(katanaIndex,swordman).ok,"Real 27600 equips through the existing normal equipment transaction");
    const auto katana=evaluateCombatAttributes(realBase,progression,swordman,realPolicy);
    check(katana.usable() && katana.physicalAttack==22 && katana.magicalAttack==24 && katana.independentAttack==21 &&
          katana.physicalCriticalBonusPercent==2 && katana.magicalCriticalBonusPercent==0 && katana.attackMissDeltaPercent==1,
          "Real 27600 separates source physical 22, magical 24, independent 21, critical two and miss one");
    const int coatIndex=grantFixture(10564);
    check(progression.equip(coatIndex,swordman).ok,"Real 10564 equips with its normal level-one and all-job qualification");
    const auto ownedBefore=progression.state;
    const auto real=evaluateCombatAttributes(realBase,progression,swordman,realPolicy);
    check(real.usable() && real.strength==realBase.value(ChrAttribute::PhysicalAttack)+5 &&
          real.intelligence==realBase.value(ChrAttribute::MagicalAttack)+5 && real.spirit==realBase.value(ChrAttribute::MagicalDefense)+5 &&
          real.equipmentPhysicalDefense==288 && real.equipmentMagicalDefense==0 && real.physicalAttack==22 && real.magicalAttack==24 &&
          real.vitalityDefenseFactor==5 && real.spiritDefenseFactor==5 && progression.state==ownedBefore,
          "Real 10564 adds three primary flats and dungeon defense 288 while its other-job skill triples remain inactive");
    const auto debug=evaluateCombatAttributes(realLow,progression,swordman,realPolicy);
    check(debug.usable() && debug.level==1 && debug.qualificationLevel==5 && debug.physicalAttack==22 &&
          debug.strength==realLow.value(ChrAttribute::PhysicalAttack)+5 && progression.state==ownedBefore,
          "A real debug level-one rebuild retains normal-level equipment without mutating progression or its learning ledger");
    progression.state["inventory"][katanaIndex]["durability"]=0;
    const auto realBroken=evaluateCombatAttributes(realBase,progression,swordman,realPolicy);
    check(realBroken.usable() && realBroken.physicalAttack==0 && realBroken.magicalAttack==0 && realBroken.independentAttack==0 &&
          realBroken.equipmentPhysicalDefense==288 && realBroken.strength==realBase.value(ChrAttribute::PhysicalAttack)+5,
          "A real broken 27600 loses weapon groups while the equipped 10564 coat retains its own contributions");
    progression.state=ownedBefore; progression.state["inventory"][katanaIndex]["reinforcement"]=1;
    check(!evaluateCombatAttributes(realBase,progression,swordman,realPolicy).usable(),
          "A preserved material reinforcement instance field cannot be silently omitted from the combat snapshot");
    progression.state=ownedBefore; progression.state["inventory"].push_back(progression.state["inventory"][katanaIndex]);
    check(!evaluateCombatAttributes(realBase,progression,swordman,realPolicy).usable(),"Duplicate inventory ownership fails before publication");
    progression.state=ownedBefore; progression.state["inventory"][katanaIndex].erase("count");
    check(!evaluateCombatAttributes(realBase,progression,swordman,realPolicy).usable(),"Missing equipped instance count cannot be repaired by a definition lookup");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"fixture",combined.snapshot(true)},
        {"real_starter",starter.snapshot()},{"real_broken_starter",brokenStarter.snapshot()},{"real_repaired_starter",repairedStarter.snapshot()},
        {"real_katana",katana.snapshot()},{"real_katana_coat",real.snapshot()},
        {"real_debug",debug.snapshot()},{"real_broken",realBroken.snapshot()},
        {"scope","Combat attribute aggregation only; World and full hit/damage/passive consumers require separate integration checks"}};
}
} // namespace dnf
