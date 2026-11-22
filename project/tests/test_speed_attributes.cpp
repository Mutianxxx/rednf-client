#include "dnf/speed_attributes.hpp"
#include "dnf/progression.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
CharacterBaseAttributes speedBase() {
    CharacterBaseAttributes base; base.level = 5; base.policy = "inferred-chr-growth-v1";
    base.source = {{"path","fixture/speed.chr"},{"provenance",{{"package_identity","fixture-package"}}}};
    for (const auto attribute : {ChrAttribute::HpMax,ChrAttribute::MpMax,ChrAttribute::PhysicalAttack,
            ChrAttribute::PhysicalDefense,ChrAttribute::MagicalAttack,ChrAttribute::MagicalDefense}) {
        CharacterAttributeValue value; value.state = CharacterAttributeState::Value; value.value = 100;
        value.unit = "chr_base_coefficient"; base.attributes.emplace(attribute,std::move(value));
    }
    for (const auto &[attribute,number] : std::vector<std::pair<ChrAttribute,float>>{
            {ChrAttribute::AttackSpeed,850},{ChrAttribute::CastSpeed,700},{ChrAttribute::MoveSpeed,850}}) {
        CharacterAttributeValue value; value.state = CharacterAttributeState::Value;
        value.value = number; value.unit = "chr_per_mille_base_1000";
        value.trace.push_back({{"fixture_source",true},{"attribute",chrAttributeName(attribute)}});
        base.attributes.emplace(attribute,std::move(value));
    }
    return base;
}
void spans(Script &source) {
    size_t offset = 2;
    for (auto &field : source.fields) { field.offset = offset; offset += 5 * (1 + field.values.size()); }
    source.rawBytes.assign(offset,0);
}
EquippedSpeedSource speedItem(int uid, const std::string &slot, float attack, float cast, float move, float dashX, float dashY) {
    EquippedSpeedSource item; item.instanceUid = uid; item.equippedSlot = slot; item.currentDurability = 35;
    item.source.path = "fixture/equipment" + std::to_string(uid) + ".equ";
    item.source.source = {{"package_identity","fixture-package"},{"literal_path","Fixture/Equipment" + std::to_string(uid) + ".equ"}};
    item.source.fields = {{"[usable job]",Json::array({"[swordman]"}),0},
        {"[equipment type]",Json::array({slot,17}),0}, {"[minimum level]",Json::array({1}),0},
        {"[durability]",Json::array({35}),0}, {"[attack speed]",Json::array({attack}),0},
        {"[cast speed]",Json::array({cast}),0}, {"[move speed]",Json::array({move}),0},
        {"[x move dash speed]",Json::array({dashX}),0}, {"[y move dash speed]",Json::array({dashY}),0},
        {"[unknown authored field]",Json::array({"keep",17,17}),0}};
    spans(item.source); return item;
}
bool diagnostic(const CharacterSpeeds &speeds, const std::string &kind) {
    for (const auto &value : speeds.diagnostics) if (value.value("kind",std::string()) == kind) return true;
    return false;
}
} // namespace

Json runSpeedAttributeTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool okay, const char *message) {
        if (!okay) throw std::runtime_error(std::string("Character speeds: ")+message);
        checks.push_back(message);
    };
    const auto policy = CharacterSpeedPolicy::inferredFlatEquipmentV1();
    auto base = speedBase();
    CharacterDefinition character; character.registration.id = 0; character.job = "[swordman]";
    const auto weapon = speedItem(10,"[weapon]",20,30,10,0.5f,-0.5f);
    const auto shoes = speedItem(20,"[shoes]",-10,40,20,0.25f,0.25f);
    check(!evaluateCharacterSpeeds(base,character,{weapon,shoes}).usable(),
          "Default construction cannot silently enable inferred equipment-speed grouping");
    const auto empty = evaluateCharacterSpeeds(base,character,{},policy);
    check(empty.usable() && empty.attackPerMille == 850 && empty.castPerMille == 700 && empty.movePerMille == 850 &&
          empty.dashXRatio == 1 && empty.dashYRatio == 1,
          "CHR absolute speed bases remain in their authored thousand-based units with independent normal dash ratios");
    const auto combined = evaluateCharacterSpeeds(base,character,{weapon,shoes},policy);
    check(combined.usable() && combined.attackPerMille == 860 && combined.castPerMille == 770 && combined.movePerMille == 880 &&
          combined.dashXRatio == 1.75f && combined.dashYRatio == 0.75f,
          "Signed EQU 0.1-percent point deltas add to the CHR group while dash ratio deltas stay independent");
    const auto reversed = evaluateCharacterSpeeds(base,character,{shoes,weapon},policy);
    check(reversed.trace == combined.trace && reversed.attackPerMille == combined.attackPerMille &&
          evaluateCharacterSpeeds(base,character,{weapon,shoes},policy).snapshot() == combined.snapshot(),
          "Full rebuilds are deterministic in persistent UID order and never accumulate old equipment contributions");
    const auto detailed = combined.snapshot(true);
    check(detailed.at("equipment_sources")[0]["fields"][9]["values"] == Json::array({"keep",17,17}) &&
          detailed.at("equipment_sources")[0]["raw_bytes_hex"].get<std::string>().size() == weapon.source.rawBytes.size()*2 &&
          combined.equipmentSources[0].source.rawBytes == weapon.source.rawBytes &&
          combined.trace[3]["candidates"][0]["source"]["package_identity"] == "fixture-package" &&
          combined.trace[3]["candidates"][0]["source"]["member_sha256"] == sha256(weapon.source.rawBytes) &&
          combined.trace[3]["candidates"][0]["source"]["ordinal"] == 4 &&
          !detailed["consumers"]["str_int_conversion_applied"].get<bool>() &&
          !detailed["consumers"]["ani_percent_conversion_applied"].get<bool>(),
          "Trace preserves exact source ownership, hashes, ordinal/ranges, raw bytes and unknown fields without claiming final STR/INT or ANI rates");
    auto broken = weapon; broken.currentDurability = 0;
    const auto brokenResult = evaluateCharacterSpeeds(base,character,{broken,shoes},policy);
    check(brokenResult.usable() && brokenResult.attackPerMille == 840 && brokenResult.dashXRatio == 1.25f &&
          diagnostic(brokenResult,"broken_equipment_speed_inactive"),
          "Broken durable items contribute no speed under the explicit inferred broken-item policy");
    auto durableZero = weapon; durableZero.source.fields[3].values = Json::array({0}); durableZero.currentDurability = 0;
    check(evaluateCharacterSpeeds(base,character,{durableZero},policy).attackPerMille == 870 &&
          evaluateCharacterSpeeds(base,character,{durableZero},policy).usable(),
          "A source-defined nondurable item is active at zero durability instead of being mistaken for broken equipment");
    auto noField = weapon; noField.source.fields.erase(noField.source.fields.begin()+4); spans(noField.source);
    check(evaluateCharacterSpeeds(base,character,{noField},policy).usable() &&
          evaluateCharacterSpeeds(base,character,{noField},policy).attackPerMille == 850,
          "An absent speed field is an explicit zero contribution rather than a manufactured weapon-category modifier");
    for (const Json value : {Json::array(),Json::array({"bad"}),Json::array({1,2}),Json::array({true}),
            Json::array({std::numeric_limits<double>::infinity()}),Json::array({std::numeric_limits<uint64_t>::max()})}) {
        auto malformed = weapon; malformed.source.fields[4].values = value;
        const auto failed = evaluateCharacterSpeeds(base,character,{malformed},policy);
        check(!failed.usable() && diagnostic(failed,"invalid_equipment_speed_scalar"),
              "Explicit empty, nonnumeric, repeated-value, nonfinite and out-of-i32 recognized source scalars block aggregation");
    }
    auto duplicate = weapon; duplicate.source.fields.push_back(duplicate.source.fields[4]); spans(duplicate.source);
    const auto repeated = evaluateCharacterSpeeds(base,character,{duplicate},policy);
    check(!repeated.usable() && repeated.trace[3]["candidates"].size() == 2,
          "Duplicate scalar tags retain both exact source candidates and fail instead of selecting the first");
    check(!evaluateCharacterSpeeds(base,character,{weapon,weapon},policy).usable(),
          "Repeated persistent item UIDs and duplicate occupied equipment slots cannot double-count modifiers");
    auto wrongSlot = weapon; wrongSlot.equippedSlot = "[coat]";
    check(!evaluateCharacterSpeeds(base,character,{wrongSlot},policy).usable(),
          "The actual equipped slot must match the uniquely authored EQU slot");
    auto wrongJob = weapon; wrongJob.source.fields[0].values = Json::array({"[mage]"});
    check(!evaluateCharacterSpeeds(base,character,{wrongJob},policy).usable(),
          "Equipment job qualification follows actual CHR identity rather than appearance or a Swordman boolean");
    auto highLevel = weapon; highLevel.source.fields[2].values = Json::array({6});
    check(!evaluateCharacterSpeeds(base,character,{highLevel},policy).usable(),
          "Equipment level requirements remain part of speed eligibility");
    const auto qualificationIndependent = evaluateCharacterSpeeds(base,character,{highLevel},6,policy);
    check(qualificationIndependent.usable() && qualificationIndependent.level == base.level &&
          qualificationIndependent.qualificationLevel == 6 &&
          qualificationIndependent.snapshot()["qualification_level"] == 6,
          "An explicit normal-ledger qualification level is independent from the effective CHR level used by a debug override");
    auto highEffectiveBase = base; highEffectiveBase.level = 10;
    check(!evaluateCharacterSpeeds(highEffectiveBase,character,{highLevel},5,policy).usable(),
          "Raising the debug CHR level does not qualify equipment above the normal progression ledger");
    auto lowEffectiveBase = base; lowEffectiveBase.level = 1;
    auto levelThree = weapon; levelThree.source.fields[2].values = Json::array({3});
    check(evaluateCharacterSpeeds(lowEffectiveBase,character,{levelThree},5,policy).usable() &&
          !evaluateCharacterSpeeds(lowEffectiveBase,character,{levelThree},2,policy).usable(),
          "Lowering effective CHR level does not unequip a normally qualified item, while qualification still rejects an underlevel ledger");
    auto badDurability = weapon; badDurability.currentDurability = 36;
    check(!evaluateCharacterSpeeds(base,character,{badDurability},policy).usable(),
          "Instance durability cannot exceed its exact source maximum");
    auto malformedSpan = weapon; malformedSpan.source.fields[4].offset = std::numeric_limits<size_t>::max();
    check(!evaluateCharacterSpeeds(base,character,{malformedSpan},policy).usable(),
          "Malformed source byte ranges remain diagnostic and cannot become an active permanent modifier");
    auto packageMismatch = weapon; packageMismatch.source.source["package_identity"] = "different-package";
    check(!evaluateCharacterSpeeds(base,character,{packageMismatch},policy).usable(),
          "Equipment source identity cannot silently cross the base CHR package boundary");
    auto unknown = weapon; unknown.source.fields.push_back({"[attack speed rate]",Json::array({1.1}),0}); spans(unknown.source);
    const auto unsupported = evaluateCharacterSpeeds(base,character,{unknown},policy);
    check(!unsupported.usable() && diagnostic(unsupported,"unsupported_equipment_speed_field") &&
          unsupported.snapshot()["equipment_sources"][0]["fields"].back()["tag"] == "[attack speed rate]",
          "Unknown related speed fields are preserved and diagnosed rather than guessed into an additive or multiplicative group");
    auto gated = weapon; gated.source.fields.push_back({"[usable world]",Json::array({3}),0}); spans(gated.source);
    check(!evaluateCharacterSpeeds(base,character,{gated},policy).usable() &&
          diagnostic(evaluateCharacterSpeeds(base,character,{gated},policy),"unsupported_equipment_qualification"),
          "Unresolved usable-period/world equipment conditions fail closed instead of becoming permanent speed eligibility");
    auto conditional = weapon; conditional.source.fields.insert(conditional.source.fields.begin()+4,{"[if]",Json::array(),0}); spans(conditional.source);
    check(!evaluateCharacterSpeeds(base,character,{conditional},policy).usable(),
          "Recognized speed fields following conditional sections cannot be promoted to unconditional equipment bonuses");
    auto zero = weapon; zero.source.fields[4].values = Json::array({-850});
    check(!evaluateCharacterSpeeds(base,character,{zero},policy).usable(),
          "A zero or negative final attack speed is blocked instead of clamped into a fabricated animation rate");
    zero = weapon; zero.source.fields[7].values = Json::array({-1});
    check(!evaluateCharacterSpeeds(base,character,{zero},policy).usable(),
          "A zero final dash factor is blocked before any movement consumer divides or integrates it");
    auto fractional = weapon; fractional.source.fields[4].values = Json::array({20.5});
    check(evaluateCharacterSpeeds(base,character,{fractional},policy).attackPerMille == 870.5f,
          "Fractional source deltas retain float32 precision without integer truncation at equipment collection");
    auto roundingBase = base; roundingBase.attributes.at(ChrAttribute::AttackSpeed).value = 16777216;
    fractional.source.fields[4].values = Json::array({1});
    check(evaluateCharacterSpeeds(roundingBase,character,{fractional},policy).attackPerMille == 16777216,
          "Each deterministic speed group addition stores binary32 rather than an excess-precision intermediate");
    auto overflowA = weapon, overflowB = shoes;
    overflowA.source.fields[4].values = Json::array({std::numeric_limits<float>::max()});
    overflowB.source.fields[4].values = Json::array({std::numeric_limits<float>::max()});
    const auto overflow = evaluateCharacterSpeeds(base,character,{overflowA,overflowB},policy);
    check(!overflow.usable() && diagnostic(overflow,"equipment_speed_arithmetic_overflow") &&
          std::isfinite(overflow.attackPerMille),
          "Equipment additions that overflow binary32 fail with finite output and an explicit diagnostic");
    auto invalidBase = base; invalidBase.attributes.at(ChrAttribute::AttackSpeed).unit = "ani_percent";
    check(!evaluateCharacterSpeeds(invalidBase,character,{},policy).usable(),
          "CHR per-mille values cannot be confused with animation percent or raw damage coefficients");

    CharacterCatalog characters(pvf);
    const float move[] = {850,910,820,800,780,850,960,880,820,850};
    const float attack[] = {850,950,950,1000,950,950,1000,950,1000,1000};
    const float cast[] = {700,1000,800,1000,1000,800,1000,1000,1000,1000};
    for (int job = 0; job < 10; ++job) {
        const auto &definition = characters.at(job);
        const auto sourceBase = buildCharacterBaseAttributes(definition,{job,0,0},5,CharacterGrowthPolicy::inferredChrGrowthV1());
        const auto result = evaluateCharacterSpeeds(sourceBase,definition,{},policy);
        check(result.usable() && result.movePerMille == move[job] && result.attackPerMille == attack[job] && result.castPerMille == cast[job],
              "Each of the ten current PVF CHR files supplies its isolated move/attack/cast basis without granting a playable controller");
    }
    RegionCatalog catalog(pvf,assets); Progression progression(catalog);
    progression.state["level"] = 5;
    const auto &swordman = characters.at(0);
    const auto sourceBase = buildCharacterBaseAttributes(swordman,{},5,CharacterGrowthPolicy::inferredChrGrowthV1());
    const auto starter = evaluateCharacterSpeeds(sourceBase,progression,swordman,policy);
    check(starter.usable() && starter.attackPerMille == 850 && starter.castPerMille == 700 && starter.movePerMille == 850 &&
          starter.equipmentSources.size() == 1 && starter.equipmentSources[0].source.path == "equipment/character/swordman/weapon/ssword/sswd_default.equ",
          "Actual persistent starter equipment is resolved through equipped UID and source EQU; its absent attack/move and explicit cast zero remain neutral");
    const auto *avatar = progression.item(39180);
    if (!avatar) throw std::runtime_error("Character speeds: real low-level speed-avatar fixture is absent");
    progression.state["inventory"] = Json::array({{{"uid",76},{"id",39180},{"count",1},{"durability",avatar->durability}}});
    progression.state["equipped"] = {{"[hat avatar]",76}};
    const auto avatarSpeed = evaluateCharacterSpeeds(sourceBase,progression,swordman,policy);
    check(!avatarSpeed.usable() && avatarSpeed.level == 5 && avatarSpeed.qualificationLevel == progression.level() &&
          avatarSpeed.attackPerMille == 850 && avatarSpeed.movePerMille == 850 &&
          diagnostic(avatarSpeed,"unsupported_equipment_qualification") &&
          avatarSpeed.equipmentSources[0].source.path == "equipment/character/swordman/avatar/cap/ahat_39180.equ",
          "A real speed-avatar with unresolved usable-period qualification fails closed instead of applying permanent speed bonuses");
    const auto *iron = progression.item(27001);
    if (!iron) throw std::runtime_error("Character speeds: real iron-sword fixture is absent");
    progression.state["inventory"] = Json::array({{{"uid",77},{"id",27001},{"count",1},{"durability",iron->durability}}});
    progression.state["equipped"] = {{"[weapon]",77}};
    const auto ironSpeed = evaluateCharacterSpeeds(sourceBase,progression,swordman,policy);
    check(ironSpeed.usable() && ironSpeed.attackPerMille == 850 && ironSpeed.castPerMille == 720 &&
          ironSpeed.equipmentSources[0].source.source.at("package_identity") == pvf.identity(),
          "A real equipped iron-sword cast-speed 20 contributes two percentage points with original package provenance");
    progression.state["inventory"].push_back(progression.state["inventory"][0]);
    check(!evaluateCharacterSpeeds(sourceBase,progression,swordman,policy).usable(),
          "A duplicated equipped inventory UID fails source collection rather than choosing an arbitrary instance");
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"fixture_trace",combined.snapshot(true)},
        {"real_starter",starter.snapshot()},{"real_speed_avatar",avatarSpeed.snapshot()},{"real_iron_sword",ironSpeed.snapshot()},
        {"scope","Source speed aggregation and qualification only; World animation/movement consumers and full conditional/set/passive/buff effects are independently required"}};
}
} // namespace dnf
