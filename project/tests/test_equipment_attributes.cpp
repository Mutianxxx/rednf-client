#include "dnf/equipment_attributes.hpp"
#include "dnf/progression.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
CharacterBaseAttributes resourceBase() {
    CharacterBaseAttributes base; base.level = 5; base.policy = "inferred-chr-growth-v1";
    base.source = {{"path","character/fixture.chr"},{"provenance",{{"package_identity","fixture-package"}}}};
    for (const auto attribute : {ChrAttribute::HpMax,ChrAttribute::MpMax,ChrAttribute::PhysicalAttack,
            ChrAttribute::PhysicalDefense,ChrAttribute::MagicalAttack,ChrAttribute::MagicalDefense}) {
        CharacterAttributeValue value; value.state = CharacterAttributeState::Value;
        value.value = attribute == ChrAttribute::HpMax ? 100.5f : attribute == ChrAttribute::MpMax ? 50.5f : 17.25f;
        value.unit = attribute == ChrAttribute::HpMax ? "hp_points" : attribute == ChrAttribute::MpMax ? "mp_points" : "chr_base_coefficient";
        value.trace.push_back({{"fixture_source",true}});
        base.attributes.emplace(attribute,std::move(value));
    }
    return base;
}
void spans(Script &source) {
    size_t offset = 2;
    for (auto &field : source.fields) { field.offset = offset; offset += 5 * (1 + field.values.size()); }
    source.rawBytes.assign(offset,0);
}
EquippedAttributeSource resourceItem(int uid, const std::string &slot, int hp, int mp, float mpPercent) {
    EquippedAttributeSource item; item.instanceUid = uid; item.equippedSlot = slot; item.currentDurability = 35;
    item.source.path = "equipment/fixture/item" + std::to_string(uid) + ".equ";
    item.source.source = {{"package_identity","fixture-package"},{"literal_path","Equipment/Fixture/Item" + std::to_string(uid) + ".equ"}};
    item.source.fields = {{"[usable job]",Json::array({"[swordman]"}),0},
        {"[equipment type]",Json::array({slot,17}),0},{"[minimum level]",Json::array({1}),0},
        {"[durability]",Json::array({35}),0},{"[HP MAX]",Json::array({hp}),0},
        {"[MP MAX]",Json::array({mp}),0},{"[MP MAX rate]",Json::array({mpPercent}),0},
        {"[unknown authored field]",Json::array({"keep",17,17}),0}};
    spans(item.source); item.source.tokens.push_back({{"fixture_raw_token",true}}); return item;
}
bool diagnostic(const EquipmentResourceAttributes &attributes, const std::string &kind) {
    for (const auto &entry : attributes.diagnostics) if (entry.value("kind",std::string()) == kind) return true;
    return false;
}
} // namespace

Json runEquipmentAttributeTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool okay, const char *message) {
        if (!okay) throw std::runtime_error(std::string("Equipment resources: ") + message);
        checks.push_back(message);
    };
    const auto policy = EquipmentResourcePolicy::inferredFlatAndRateV1();
    const auto base = resourceBase();
    CharacterDefinition character; character.registration.id = 0; character.job = "[swordman]";
    const auto coat = resourceItem(10,"[coat]",25,20,10.0f);
    const auto pants = resourceItem(20,"[pants]",-5,10,15.0f);
    const auto original = base.snapshot();
    check(!evaluateEquipmentResourceAttributes(base,character,{coat},5).usable(),
          "Default construction cannot enable an inferred equipment HP/MP rule");
    const auto empty = evaluateEquipmentResourceAttributes(base,character,{},5,policy);
    check(empty.usable() && empty.adjusted.value(ChrAttribute::HpMax) == 100.5f &&
          empty.adjusted.value(ChrAttribute::MpMax) == 50.5f,
          "Empty equipped ownership preserves pure CHR HP/MP bases and fractional source precision");
    const auto combined = evaluateEquipmentResourceAttributes(base,character,{coat,pants},5,policy);
    check(combined.usable() && combined.adjusted.value(ChrAttribute::HpMax) == 120.5f &&
          combined.adjusted.value(ChrAttribute::MpMax) == 100.625f &&
          combined.adjusted.integer(ChrAttribute::HpMax) == 120 && combined.adjusted.integer(ChrAttribute::MpMax) == 100,
          "Signed flat EQU points apply before the explicitly inferred MP percentage group with conversion only at the integer consumer");
    check(base.snapshot() == original && combined.adjusted.policy == base.policy &&
          combined.adjusted.attributes.at(ChrAttribute::PhysicalAttack).snapshot() == base.attributes.at(ChrAttribute::PhysicalAttack).snapshot() &&
          combined.adjusted.attributes.at(ChrAttribute::MagicalDefense).snapshot() == base.attributes.at(ChrAttribute::MagicalDefense).snapshot(),
          "Evaluation publishes a private adjusted copy and never converts or changes the four CHR attack/defense coefficients");
    check(evaluateEquipmentResourceAttributes(base,character,{pants,coat},5,policy).trace == combined.trace &&
          evaluateEquipmentResourceAttributes(base,character,{coat,pants},5,policy).snapshot() == combined.snapshot(),
          "Persistent UID ordering makes complete rebuilds deterministic without accumulating prior equipment modifiers");
    const auto reapplied = evaluateEquipmentResourceAttributes(combined.adjusted,character,{coat,pants},5,policy);
    check(!reapplied.usable() && !reapplied.adjusted.usable() && diagnostic(reapplied,"equipment_resource_already_applied"),
          "An already adjusted base is rejected so a caller cannot apply an equipped item twice");
    const auto snapshot = combined.snapshot(true);
    check(snapshot["equipment_sources"][0]["fields"][7]["values"] == Json::array({"keep",17,17}) &&
          snapshot["equipment_sources"][0]["raw_bytes_hex"].get<std::string>().size() == coat.source.rawBytes.size()*2 &&
          snapshot["equipment_sources"][0]["ordered_tokens"] == coat.source.tokens &&
          combined.equipmentSources[0].source.rawBytes == coat.source.rawBytes &&
          combined.trace[0]["candidates"][0]["source"]["package_identity"] == "fixture-package" &&
          combined.trace[0]["candidates"][0]["source"]["member_sha256"] == sha256(coat.source.rawBytes) &&
          combined.trace[0]["candidates"][0]["source"]["ordinal"] == 4,
          "Snapshots and traces retain exact instance ownership, package, literal path, member hash, field ordinal, raw bytes, tokens and unknown repetitions");
    check(combined.adjusted.at(ChrAttribute::HpMax).trace.back()["policy"] == policy.id &&
          combined.adjusted.at(ChrAttribute::MpMax).trace.back()["evaluation_trace"] == combined.trace,
          "The adjusted base keeps its original source trace and the full equipment resource calculation trace for World publication");
    auto broken = coat; broken.currentDurability = 0;
    const auto brokenResult = evaluateEquipmentResourceAttributes(base,character,{broken},5,policy);
    check(brokenResult.usable() && brokenResult.adjusted.value(ChrAttribute::HpMax) == 100.5f &&
          brokenResult.adjusted.value(ChrAttribute::MpMax) == 50.5f && diagnostic(brokenResult,"broken_equipment_resource_inactive"),
          "A broken durable item contributes no resource flats or percent group under the named inferred policy");
    auto nondurable = coat; nondurable.source.fields[3].values = Json::array({0}); nondurable.currentDurability = 0;
    check(evaluateEquipmentResourceAttributes(base,character,{nondurable},5,policy).usable() &&
          evaluateEquipmentResourceAttributes(base,character,{nondurable},5,policy).adjusted.value(ChrAttribute::HpMax) == 125.5f,
          "Zero source durability means nondurable and does not disable otherwise eligible resource modifiers");
    auto highMinimum = coat; highMinimum.source.fields[2].values = Json::array({6});
    check(!evaluateEquipmentResourceAttributes(base,character,{highMinimum},5,policy).usable() &&
          evaluateEquipmentResourceAttributes(base,character,{highMinimum},6,policy).usable(),
          "The supplied normal level ledger qualifies equipment independently of the effective CHR level");
    auto lowEffective = base; lowEffective.level = 1;
    check(evaluateEquipmentResourceAttributes(lowEffective,character,{highMinimum},6,policy).usable(),
          "A low debug effective level does not remove normally qualified equipment");
    auto highEffective = base; highEffective.level = 99;
    check(!evaluateEquipmentResourceAttributes(highEffective,character,{highMinimum},5,policy).usable(),
          "A high debug effective level cannot qualify equipment above the normal progression level");
    check(!evaluateEquipmentResourceAttributes(base,character,{coat,coat},5,policy).usable(),
          "A duplicate persistent UID and occupied slot cannot contribute HP/MP twice");
    auto duplicateSlot = pants; duplicateSlot.equippedSlot = coat.equippedSlot; duplicateSlot.source.fields[1].values[0] = coat.equippedSlot;
    check(!evaluateEquipmentResourceAttributes(base,character,{coat,duplicateSlot},5,policy).usable(),
          "Different item UIDs cannot occupy the same resource modifier slot");
    auto wrongSlot = coat; wrongSlot.equippedSlot = "[shoes]";
    check(!evaluateEquipmentResourceAttributes(base,character,{wrongSlot},5,policy).usable(),
          "Equipped ownership must use the exact authored EQU slot");
    auto wrongJob = coat; wrongJob.source.fields[0].values = Json::array({"[mage]"});
    check(!evaluateEquipmentResourceAttributes(base,character,{wrongJob},5,policy).usable(),
          "Resource qualification follows the actual CHR job restriction");
    auto badDurability = coat; badDurability.currentDurability = 36;
    check(!evaluateEquipmentResourceAttributes(base,character,{badDurability},5,policy).usable(),
          "Current durability must lie within the exact EQU source maximum");
    auto packageMismatch = coat; packageMismatch.source.source["package_identity"] = "another-package";
    check(!evaluateEquipmentResourceAttributes(base,character,{packageMismatch},5,policy).usable() &&
          diagnostic(evaluateEquipmentResourceAttributes(base,character,{packageMismatch},5,policy),"equipment_resource_package_mismatch"),
          "Item definitions cannot cross the CHR package identity boundary");
    auto badHash = coat; badHash.source.source["member_sha256"] = "not-the-member-hash";
    check(!evaluateEquipmentResourceAttributes(base,character,{badHash},5,policy).usable(),
          "Conflicting authored member identity rejects resource evaluation");
    auto badSpan = coat; badSpan.source.fields[4].offset = std::numeric_limits<size_t>::max();
    check(!evaluateEquipmentResourceAttributes(base,character,{badSpan},5,policy).usable(),
          "Malformed byte ranges preserve diagnostics without becoming active resource modifiers");
    for (const Json value : {Json::array(),Json::array({"bad"}),Json::array({1,2}),Json::array({true}),Json::array({2.5}),
            Json::array({std::numeric_limits<uint64_t>::max()})}) {
        auto invalid = coat; invalid.source.fields[4].values = value;
        const auto failed = evaluateEquipmentResourceAttributes(base,character,{invalid},5,policy);
        check(!failed.usable() && !failed.adjusted.usable() && diagnostic(failed,"invalid_equipment_resource_scalar"),
              "Empty, nonnumeric, multi-value, fractional or non-i32 flat HP/MP fields block both wrapper and adjusted base");
    }
    auto repeated = coat; repeated.source.fields.push_back(repeated.source.fields[4]); spans(repeated.source);
    check(!evaluateEquipmentResourceAttributes(base,character,{repeated},5,policy).usable() &&
          evaluateEquipmentResourceAttributes(base,character,{repeated},5,policy).trace[0]["candidates"].size() == 2,
          "Repeated normalized HP/MP scalar fields retain all source candidates instead of choosing one");
    auto conditional = coat; conditional.source.fields.insert(conditional.source.fields.begin()+4,{"[if]",Json::array(),0}); spans(conditional.source);
    check(!evaluateEquipmentResourceAttributes(base,character,{conditional},5,policy).usable(),
          "Conditional HP/MP fields are never promoted to unconditional item modifiers");
    auto set = coat; set.source.fields.push_back({"[set item master]",Json::array({123}),0}); spans(set.source);
    check(!evaluateEquipmentResourceAttributes(base,character,{set},5,policy).usable() &&
          diagnostic(evaluateEquipmentResourceAttributes(base,character,{set},5,policy),"equipment_resource_set_unresolved"),
          "Referenced set effects require a real set consumer and fail closed in this resource-only evaluator");
    auto unknownRate = coat; unknownRate.source.fields.push_back({"[HP MAX rate]",Json::array({10.0}),0}); spans(unknownRate.source);
    check(!evaluateEquipmentResourceAttributes(base,character,{unknownRate},5,policy).usable(),
          "An unobserved HP MAX rate group is preserved but never guessed from MP MAX rate semantics");
    auto timed = coat; timed.source.fields.push_back({"[usable period]",Json::array({15}),0}); spans(timed.source);
    check(!evaluateEquipmentResourceAttributes(base,character,{timed},5,policy).usable(),
          "Unresolved usable-period or world qualification cannot yield permanent resource modifiers");
    auto selected = coat; selected.source.fields.push_back({"[avatar select ability]",Json::array({"[HP MAX]","+",100}),0}); spans(selected.source);
    check(!evaluateEquipmentResourceAttributes(base,character,{selected},5,policy).usable(),
          "An avatar option containing HP/MP requires an owned selection and cannot become an automatic bonus");
    auto lethal = coat; lethal.source.fields[4].values = Json::array({-101});
    check(!evaluateEquipmentResourceAttributes(base,character,{lethal},5,policy).usable(),
          "Resource aggregation rejects a nonpositive integer HP maximum before World publication");
    auto rateZero = coat; rateZero.source.fields[6].values = Json::array({-100.0});
    check(!evaluateEquipmentResourceAttributes(base,character,{rateZero},5,policy).usable(),
          "A nonpositive MP percent factor fails instead of inventing a usable clamp");
    auto enormous = coat; enormous.source.fields[6].values = Json::array({std::numeric_limits<float>::max()});
    check(!evaluateEquipmentResourceAttributes(base,character,{enormous},5,policy).usable(),
          "Nonfinite percentage arithmetic or integer-consumer overflow blocks the resource result");
    for (const Json value : {Json::array(),Json::array({"bad"}),Json::array({1.0,2.0}),
            Json::array({std::numeric_limits<double>::infinity()})}) {
        auto invalidRate = coat; invalidRate.source.fields[6].values = value;
        const auto failed = evaluateEquipmentResourceAttributes(base,character,{invalidRate},5,policy);
        check(!failed.usable() && diagnostic(failed,"invalid_equipment_resource_scalar"),
              "Empty, nonnumeric, multiple or nonfinite MP percentage operands are retained and rejected");
    }
    auto roundingBase = base; roundingBase.attributes.at(ChrAttribute::HpMax).value = 16777216;
    auto rounded = coat; rounded.source.fields[4].values = Json::array({1});
    check(evaluateEquipmentResourceAttributes(roundingBase,character,{rounded},5,policy).adjusted.value(ChrAttribute::HpMax) == 16777216,
          "Each UID-ordered resource addition stores IEEE binary32 precision");
    auto badUnit = base; badUnit.attributes.at(ChrAttribute::HpMax).unit = "chr_base_coefficient";
    check(!evaluateEquipmentResourceAttributes(badUnit,character,{},5,policy).usable(),
          "CHR resource points cannot be confused with attack/defense coefficients");

    CharacterCatalog characters(pvf); const auto &swordman = characters.at(0);
    const auto realBase = buildCharacterBaseAttributes(swordman,{},5,CharacterGrowthPolicy::inferredChrGrowthV1());
    RegionCatalog catalog(pvf,assets); Progression progression(catalog); progression.initialize(5);
    const auto inventoryFixture = [&](int id) {
        const auto *definition = progression.item(id);
        if (!definition) throw std::runtime_error("Equipment resources: real EQU fixture is missing");
        const int uid = progression.state.at("next_uid").get<int>();
        progression.state["inventory"].push_back({{"uid",uid},{"id",id},{"count",1},{"durability",definition->durability}});
        progression.state["next_uid"] = uid+1;
    };
    inventoryFixture(10050);
    check(progression.equip(1,swordman).ok,
          "A real level-4 adventure-coat inventory fixture equips through normal source qualification");
    const auto real = evaluateEquipmentResourceAttributes(realBase,progression,swordman,policy);
    bool coatSource = false;
    for (const auto &source : real.equipmentSources)
        if (source.source.path == "equipment/character/common/jacket/cloth/garb_adventure.equ") coatSource = true;
    check(real.usable() && real.adjusted.value(ChrAttribute::HpMax) == realBase.value(ChrAttribute::HpMax)+25 &&
          real.adjusted.value(ChrAttribute::MpMax) == realBase.value(ChrAttribute::MpMax) &&
          coatSource,
          "Real EQU 10050 HP MAX 25 reaches the adjusted resource base with MP unchanged and source ownership preserved");
    const auto inventoryBefore = progression.state;
    const auto realLowBase = buildCharacterBaseAttributes(swordman,{},1,CharacterGrowthPolicy::inferredChrGrowthV1());
    const auto debug = evaluateEquipmentResourceAttributes(realLowBase,progression,swordman,policy);
    check(debug.usable() && debug.adjusted.level == 1 && debug.qualificationLevel == 5 &&
          debug.adjusted.value(ChrAttribute::HpMax) == realLowBase.value(ChrAttribute::HpMax)+25 && progression.state == inventoryBefore,
          "A real level-1 debug CHR rebuild preserves normally qualified coat stats without mutating progression");
    progression.state["level"] = 3;
    check(!evaluateEquipmentResourceAttributes(realBase,progression,swordman,policy).usable(),
          "A real underlevel normal ledger rejects the level-4 coat even with a higher effective CHR base");
    progression.state["level"] = 5; progression.state["inventory"][1]["durability"] = 0;
    const auto realBroken = evaluateEquipmentResourceAttributes(realBase,progression,swordman,policy);
    check(realBroken.usable() && realBroken.adjusted.value(ChrAttribute::HpMax) == realBase.value(ChrAttribute::HpMax),
          "The real coat loses its HP bonus at zero durability under the explicit broken-item policy");
    progression.initialize(1);
    inventoryFixture(10564);
    check(progression.equip(1,swordman).ok,
          "A real minimum-level-1 dual-resource coat qualifies from the normal level-1 ledger");
    const auto dual = evaluateEquipmentResourceAttributes(realLowBase,progression,swordman,policy);
    check(dual.usable() && dual.adjusted.value(ChrAttribute::HpMax) == realLowBase.value(ChrAttribute::HpMax)+100 &&
          dual.adjusted.value(ChrAttribute::MpMax) == realLowBase.value(ChrAttribute::MpMax)+100,
          "Real EQU 10564 independently adds its HP MAX 100 and MP MAX 100 fields without consuming its unrelated coefficient fields");
    progression.initialize(1);
    inventoryFixture(63000);
    check(progression.equip(1,swordman).ok,
          "The real nondurable creature EQU can qualify its separate MP percent modifier");
    const auto creature = evaluateEquipmentResourceAttributes(realLowBase,progression,swordman,policy);
    volatile float expectedFraction = 5.0f/100.0f; volatile float expectedFactor = 1.0f+expectedFraction;
    volatile float expectedMp = realLowBase.value(ChrAttribute::MpMax)*expectedFactor;
    check(creature.usable() && creature.adjusted.value(ChrAttribute::MpMax) == expectedMp &&
          creature.adjusted.value(ChrAttribute::HpMax) == realLowBase.value(ChrAttribute::HpMax),
          "Real creature EQU 63000 MP MAX rate 5.0 uses percentage points rather than EQU speed per-mille units");
    progression.initialize(5); inventoryFixture(10104);
    check(progression.equip(1,swordman).ok,
          "The real level-5 set-coat fixture reaches normal equipment qualification");
    const auto realSet = evaluateEquipmentResourceAttributes(realBase,progression,swordman,policy);
    check(!realSet.usable() && diagnostic(realSet,"equipment_resource_set_unresolved"),
          "Real EQU 10104 permanent HP MAX 35 and nested set HP MAX 50 are preserved and rejected instead of silently adding or selecting one");
    progression.state["inventory"].push_back(progression.state["inventory"][1]);
    const auto duplicateInventory = evaluateEquipmentResourceAttributes(realLowBase,progression,swordman,policy);
    check(!duplicateInventory.usable() && diagnostic(duplicateInventory,"equipped_resource_collection_failed"),
          "Ambiguous equipped inventory ownership fails collection instead of selecting the first duplicate UID");
    progression.initialize(1); progression.state["inventory"][0].erase("uid");
    const auto missingInventoryUid = evaluateEquipmentResourceAttributes(realLowBase,progression,swordman,policy);
    check(!missingInventoryUid.usable() && diagnostic(missingInventoryUid,"equipped_resource_collection_failed"),
          "Missing current inventory ownership cannot be repaired by guessing from appearance or the item definition");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"fixture",combined.snapshot(true)},
        {"real_coat",real.snapshot()},{"real_dual_coat",dual.snapshot()},{"real_creature",creature.snapshot()},
        {"real_set_rejected",realSet.snapshot()},
        {"scope","Source equipment HP/MP max aggregation only; World publication and full sets/conditions/passives remain separate consumers"}};
}
} // namespace dnf
