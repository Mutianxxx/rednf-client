#include "dnf/attributes.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
CharacterDefinition attributeFixture() {
    CharacterDefinition definition;
    definition.registration.id = 0;
    definition.source.script.path = "fixture/scoped-growth.chr";
    definition.source.bytes.resize(512, 0);
    definition.source.provenance = {{"package_identity","fixture-package"},{"literal_path","Fixture/Scoped-Growth.chr"}};
    definition.stats = {
        {"[initial value]",0,0,2,102,{
            {"[HP MAX]",Json::array({100.5}),7}, {"[MP MAX]",Json::array({50.5}),17},
            {"[physical attack]",Json::array({7.5}),27}, {"[physical defense]",Json::array({6.5}),37},
            {"[magical attack]",Json::array({5.5}),47}, {"[magical defense]",Json::array({4.5}),57},
            {"[attack speed]",Json::array({850}),67}, {"[dark resistance]",Json::array({-3.5}),77},
            {"[unknown authored field]",Json::array({"keep",17,17}),87}}},
        {"[growtype 1]",1,0,102,152,{
            {"[HP MAX]",Json::array({0.75}),107}, {"[MP MAX]",Json::array({0.75}),117}}},
        {"[growtype 2]",2,0,152,202,{
            {"[HP MAX]",Json::array({2.5}),157}, {"[MP MAX]",Json::array({3.5}),167}}},
        {"[awakening 1]",2,1,202,252,{
            {"[HP MAX]",Json::array({4.5}),207}}},
        {"[growtype 3]",3,0,252,302,{
            {"[HP MAX]",Json::array({9.5}),257}, {"[MP MAX]",Json::array({8.5}),267}}},
        {"[awakening 1]",3,1,302,352,{
            {"[HP MAX]",Json::array({19.5}),307}, {"[MP MAX]",Json::array({18.5}),317}}}
    };
    return definition;
}
bool hasDiagnostic(const CharacterBaseAttributes &result, const std::string &kind) {
    for (const auto &entry : result.diagnostics) if (entry.value("kind",std::string()) == kind) return true;
    return false;
}
template <class Action> bool rejects(Action action) {
    try { action(); } catch (const std::exception &) { return true; }
    return false;
}
} // namespace

Json runAttributeTests(Pvf &pvf) {
    Json checks = Json::array();
    auto check = [&](bool passed, const char *message) {
        if (!passed) throw std::runtime_error(std::string("CHR attributes: ")+message);
        checks.push_back(message);
    };
    const auto policy = CharacterGrowthPolicy::inferredChrGrowthV1();
    const auto fixture = attributeFixture();
    const auto disabled = buildCharacterBaseAttributes(fixture,{},3);
    check(!disabled.usable() && hasDiagnostic(disabled,"growth_policy_not_enabled") &&
          rejects([&] { disabled.integer(ChrAttribute::HpMax); }),
          "Default evaluation cannot enable inferred growth or return legacy/demo resource maxima");
    const auto base = buildCharacterBaseAttributes(fixture,{},3,policy);
    check(base.usable() && base.value(ChrAttribute::HpMax) == 102 && base.integer(ChrAttribute::MpMax) == 52 &&
          base.value(ChrAttribute::AttackSpeed) == 850 && base.integer(ChrAttribute::DarkResistance) == -3,
          "The opt-in curve retains fractional per-level growth and signed resistance, converting integers only at consumption");
    const auto branch = buildCharacterBaseAttributes(fixture,{0,1,0},3,policy);
    const auto awakened = buildCharacterBaseAttributes(fixture,{0,1,1},3,policy);
    const auto otherAwakening = buildCharacterBaseAttributes(fixture,{0,2,1},3,policy);
    check(branch.usable() && branch.value(ChrAttribute::HpMax) == 105.5f &&
          awakened.usable() && awakened.value(ChrAttribute::HpMax) == 109.5f && awakened.value(ChrAttribute::MpMax) == 57.5f &&
          otherAwakening.usable() && otherAwakening.value(ChrAttribute::HpMax) == 139.5f,
          "Runtime g maps to source g+1 and awakening overrides only that branch delta, with explicit absent-field inheritance");
    check(base.at(ChrAttribute::PhysicalAttack).unit == "chr_base_coefficient" &&
          base.at(ChrAttribute::AttackSpeed).unit == "chr_per_mille_base_1000" &&
          base.at(ChrAttribute::InventoryLimit).unit == "source_inventory_unit_unresolved" &&
          !base.snapshot().at("identity_authorization").get<bool>(),
          "Raw coefficient, speed and unresolved units remain separate from final combat/STR/INT and identity authorization");
    const auto serialized = base.snapshot();
    check(serialized.at("selected_blocks").at(0).at("fields").at(8).at("values") == Json::array({"keep",17,17}) &&
          serialized.at("attributes").at("hp_max").at("trace").at(0).at("selection").at("candidates").at(0).at("source").at("byte_offset") == 7 &&
          serialized.at("attributes").at("hp_max").at("trace").at(0).at("selection").at("candidates").at(0).at("source").at("package_identity") == "fixture-package" &&
          serialized.at("source").at("member_sha256") == sha256(fixture.source.bytes),
          "Trace retains source package/member identity, field offsets/ordinal, scope and unknown ordered field payloads");
    for (const int invalidLevel : {-1,0,100,std::numeric_limits<int>::max()}) {
        const auto invalid = buildCharacterBaseAttributes(fixture,{},invalidLevel,policy);
        check(!invalid.usable() && hasDiagnostic(invalid,"level_outside_policy_range"),
              "Out-of-policy character levels reject without implicit clamping or extrapolation");
    }
    check(buildCharacterBaseAttributes(fixture,{},1,policy).integer(ChrAttribute::HpMax) == 100 &&
          buildCharacterBaseAttributes(fixture,{},99,policy).integer(ChrAttribute::HpMax) == 174,
          "Level one consumes the separate initial block and level 99 performs exactly 98 growth additions");
    for (const CharacterIdentity identity : {CharacterIdentity{1,0,0},CharacterIdentity{0,-1,0},
             CharacterIdentity{0,6,0},CharacterIdentity{0,0,-1},CharacterIdentity{0,0,3}})
        check(!buildCharacterBaseAttributes(fixture,identity,3,policy).usable(),
              "Wrong-job, negative and out-of-adapter identities cannot select another source branch");
    for (const Json malformed : {Json::array(),Json::array({"bad"}),Json::array({1,2}),
             Json::array({-1}),Json::array({-1e-100}),
             Json::array({int64_t(-2147483649LL)}),Json::array({std::numeric_limits<uint64_t>::max()}),
             Json::array({std::numeric_limits<double>::infinity()})}) {
        auto source = fixture;
        source.stats[1].fields[0].values = malformed;
        const auto invalid = buildCharacterBaseAttributes(source,{},3,policy);
        check(!invalid.usable() && rejects([&] { invalid.integer(ChrAttribute::MpMax); }),
              "Empty, nonnumeric, nonfinite, negative, out-of-i32 and multi-value fields block the complete snapshot");
    }
    auto duplicate = fixture;
    duplicate.stats[1].fields.push_back(duplicate.stats[1].fields[0]);
    const auto ambiguous = buildCharacterBaseAttributes(duplicate,{},3,policy);
    check(!ambiguous.usable() && ambiguous.at(ChrAttribute::HpMax).state == CharacterAttributeState::Ambiguous &&
          ambiguous.at(ChrAttribute::HpMax).trace.at(1).at("selection").at("candidates").size() == 2,
          "Repeated numeric fields remain separate candidates and cannot silently pick the first identical value");
    duplicate = fixture;
    duplicate.stats.push_back(duplicate.stats[1]);
    const auto ambiguousBlock = buildCharacterBaseAttributes(duplicate,{},3,policy);
    check(!ambiguousBlock.usable() && hasDiagnostic(ambiguousBlock,"ambiguous_stat_block") &&
          ambiguousBlock.selectedBlocks.size() == 3,
          "Repeated source growth blocks fail with all candidate spans retained");
    for (const size_t malformedOffset : {size_t(0),size_t(102),size_t(108),size_t(152),size_t(513),std::numeric_limits<size_t>::max()}) {
        auto source = fixture;
        source.stats[1].fields[0].offset = malformedOffset;
        const auto invalid = buildCharacterBaseAttributes(source,{},3,policy);
        check(!invalid.usable() && hasDiagnostic(invalid,"malformed_stat_field_span") &&
              invalid.selectedBlocks.at(1).at("fields").at(0).at("offset") == malformedOffset &&
              rejects([&] { invalid.integer(ChrAttribute::HpMax); }),
              "Invalid, unaligned, enclosing-tag and out-of-member field offsets stay visible and block all consumers");
    }
    for (const size_t malformedEnd : {size_t(0),size_t(102),size_t(151),size_t(517),std::numeric_limits<size_t>::max()}) {
        auto source = fixture;
        source.stats[1].endOffset = malformedEnd;
        const auto invalid = buildCharacterBaseAttributes(source,{},3,policy);
        check(!invalid.usable() && hasDiagnostic(invalid,"malformed_stat_block_span"),
              "Empty, reversed, unaligned and out-of-member stat block spans are rejected without offset repair");
    }
    auto overlapping = fixture;
    overlapping.stats[0].endOffset = 152;
    const auto overlap = buildCharacterBaseAttributes(overlapping,{},3,policy);
    check(!overlap.usable() && hasDiagnostic(overlap,"overlapping_stat_block_spans"),
          "Selected scopes cannot overlap source ranges even when their individual bounds are valid");
    auto noAwakening = fixture;
    noAwakening.stats.erase(noAwakening.stats.begin()+3);
    check(!buildCharacterBaseAttributes(noAwakening,{0,1,1},3,policy).usable(),
          "A missing requested awakening block cannot borrow a different branch awakening");
    auto emptyAwakening = fixture;
    emptyAwakening.stats[3].fields.clear();
    const auto empty = buildCharacterBaseAttributes(emptyAwakening,{0,1,1},3,policy);
    check(empty.usable() && hasDiagnostic(empty,"empty_stat_block") && empty.value(ChrAttribute::HpMax) == branch.value(ChrAttribute::HpMax),
          "A present empty awakening block stays diagnosed and follows the declared field-inheritance policy");
    auto emptyOverride = fixture;
    emptyOverride.stats[3].fields[0].values = Json::array();
    check(!buildCharacterBaseAttributes(emptyOverride,{0,1,1},3,policy).usable(),
          "An explicitly empty awakening value blocks instead of behaving as an absent inherited field");
    auto rounding = fixture;
    rounding.stats[0].fields[0].values = Json::array({16777216});
    rounding.stats[1].fields[0].values = Json::array({1});
    check(buildCharacterBaseAttributes(rounding,{},4,policy).integer(ChrAttribute::HpMax) == 16777216,
          "Each level stores binary32 so sub-ULP additions cannot become a fused multiply or integer accumulation");
    CharacterAttributeValue tooLarge;
    tooLarge.state = CharacterAttributeState::Value; tooLarge.value = 2147483648.0f;
    check(rejects([&] { tooLarge.integer(); }) && !tooLarge.snapshot().contains("integer_consumer"),
          "The float32 value just beyond INT_MAX cannot overflow an integer consumer");
    auto overflow = fixture;
    overflow.stats[0].fields[0].values = Json::array({double(std::numeric_limits<float>::max())});
    overflow.stats[1].fields[0].values = Json::array({double(std::numeric_limits<float>::max())});
    const auto overflowed = buildCharacterBaseAttributes(overflow,{},2,policy);
    check(!overflowed.usable() && hasDiagnostic(overflowed,"attribute_arithmetic_overflow"),
          "Overflow during a float32 growth step produces a blocked snapshot and the failing level diagnostic");

    CharacterCatalog catalog(pvf);
    // These are exact current-PVF source facts, independently read from the
    // ten CHR entries. They are regression fixtures, never runtime constants.
    const float initialHp[] = {180,200,160,120,220,150,170,210,115,180};
    const float initialMp[] = {140,120,160,200,100,170,150,110,205,140};
    const float deltaHp[] = {45,50,40,35,50,37.5f,42.5f,50,34.5f,45};
    const float deltaMp[] = {25,20,30,35,20,32.5f,27.5f,18,35.5f,25};
    Json sourceCases = Json::array();
    for (int job = 0; job < 10; ++job) {
        const auto &definition = catalog.at(job);
        const auto first = buildCharacterBaseAttributes(definition,{job,0,0},1,policy);
        const auto second = buildCharacterBaseAttributes(definition,{job,0,0},2,policy);
        const auto high = buildCharacterBaseAttributes(definition,{job,0,0},99,policy);
        check(first.usable() && second.usable() && high.usable() &&
              first.value(ChrAttribute::HpMax) == initialHp[job] && first.value(ChrAttribute::MpMax) == initialMp[job] &&
              second.value(ChrAttribute::HpMax) == initialHp[job]+deltaHp[job] &&
              second.value(ChrAttribute::MpMax) == initialMp[job]+deltaMp[job] &&
              high.value(ChrAttribute::HpMax) == initialHp[job]+deltaHp[job]*98 &&
              high.value(ChrAttribute::MpMax) == initialMp[job]+deltaMp[job]*98,
              "Each of the ten current source jobs has an isolated initial/growtype-1 curve at levels 1, 2 and 99");
        check(first.source.at("member_sha256") == definition.source.provenance.at("member_sha256") &&
              first.source.at("provenance").at("package_identity") == pvf.identity() &&
              first.at(ChrAttribute::PhysicalAttack).unit == "chr_base_coefficient",
              "Current-PVF source identity and raw coefficient classification survive the executable base-growth adapter");
        sourceCases.push_back({{"job",job},{"source",first.source},{"initial_hp",first.value(ChrAttribute::HpMax)},
            {"initial_mp",first.value(ChrAttribute::MpMax)},{"level99_hp",high.value(ChrAttribute::HpMax)},
            {"level99_mp",high.value(ChrAttribute::MpMax)}});
    }
    const auto maleFighter = buildCharacterBaseAttributes(catalog.at(7),{7,2,0},3,policy);
    const auto maleFighterAwakened = buildCharacterBaseAttributes(catalog.at(7),{7,2,1},3,policy);
    check(maleFighter.usable() && maleFighterAwakened.usable() &&
          maleFighter.value(ChrAttribute::MpMax) == 145 && maleFighterAwakened.value(ChrAttribute::MpMax) == 141,
          "A real differing male-Fighter awakening MP field replaces the branch delta instead of adding both increments");
    return {{"status","pass"},{"checks",checks},{"check_count",checks.size()},{"source_cases",sourceCases},
        {"fixture_trace",base.snapshot()},
        {"scope","CHR source growth adapter and numeric boundaries; World HP/MP integration is checked by the runtime owner; equipment/STR/INT/final damage and playable branch gates remain outside this base evaluator"}};
}
} // namespace dnf
