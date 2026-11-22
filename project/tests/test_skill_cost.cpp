#include "dnf/skill_cost.hpp"
#include "dnf/combat.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
Json runSkillCostTests(Pvf &pvf) {
    Json checks = Json::array();
    auto check = [&](bool passed, const std::string &name) {
        if (!passed) throw std::runtime_error("Skill cost: " + name);
        checks.push_back(name);
    };
    auto close = [](double a, double b) { return std::abs(a-b) < 1e-9; };
    auto findKind = [](const Json &values, const std::string &kind) -> const Json * {
        for (const auto &value : values) if (value.value("kind", std::string()) == kind) return &value;
        return nullptr;
    };
    auto findStage = [](const Json &values, const std::string &stage) -> const Json * {
        for (const auto &value : values) if (value.value("stage", std::string()) == stage) return &value;
        return nullptr;
    };
    CharacterScript authored;
    authored.script.path = "fixture/endpoint.skl"; authored.bytes.resize(250, 0);
    authored.script.fields = {{"[maximum level]", Json::array({5}), 2},
        {"[growtype maximum level]", Json::array({2}), 12},
        {"[consume MP]", Json::array({10.9,20.9}), 22},
        {"[cool time]", Json::array({1000.25,2000.75}), 37},
        {"[unknown]", Json::array({"preserved"}), 52},
        {"[dungeon]", Json::array(), 62}, {"[consume MP]", Json::array({30.9,50.9}), 67},
        {"[/dungeon]", Json::array(), 82}, {"[pvp]", Json::array(), 87},
        {"[consume MP]", Json::array(), 92}, {"[cool time]", Json::array({500.5,1000.5}), 97},
        {"[/pvp]", Json::array(), 112}};
    auto data = [&](const CharacterScript &source, const std::string &mode = "common") {
        return readSkillSourceData(parseCharacterSkillSource({0,42}, {}, source), mode);
    };
    const auto common = data(authored);
    const auto low = evaluateSkillCosts(common, 1), mid = evaluateSkillCosts(common, 3), high = evaluateSkillCosts(common, 5);
    check(low.consumeMp() == 10 && mid.consumeMp() == 15 && high.consumeMp() == 20 &&
          close(*low.cooldownMs(),1000.25) && close(*mid.cooldownMs(),1500.5) && close(*high.cooldownMs(),2000.75),
          "N from maximum-level source evaluates both endpoints and midpoint; MP truncates only final, CD keeps authored milliseconds");
    check(mid.mp.trace[0]["source"]["byte_offset"] == 22 && mid.mp.trace[0]["source"]["scope"] == "common" &&
          mid.mp.trace[1]["source"]["byte_offset"] == 2 && mid.mp.trace[1]["last_level"] == 5 &&
          mid.mp.trace[1]["evidence"][0]["lines"] == Json::array({36,37,58,85,86}),
          "Endpoint, range, evidence and policy trace preserve exact source scopes and offsets");
    check(evaluateSkillCosts(data(authored,"dungeon"),3).consumeMp() == 40 &&
          evaluateSkillCosts(data(authored,"dungeon"),3).mp.trace[0]["source"]["byte_offset"] == 67 &&
          !evaluateSkillCosts(data(authored,"pvp"),3).consumeMp() &&
          evaluateSkillCosts(data(authored,"pvp"),3).mp.state == SkillNumericState::ExplicitEmpty &&
          close(*evaluateSkillCosts(data(authored,"pvp"),3).cooldownMs(),750.5),
          "Mode selection consumes the exact dungeon override and retains explicit-empty PvP without common fallback");
    check(!evaluateSkillCosts(common,0).consumeMp() && !evaluateSkillCosts(common,-1).cooldownMs() &&
          evaluateSkillCosts(common,99).consumeMp() == high.consumeMp() &&
          findKind(evaluateSkillCosts(common,99).mp.diagnostics,"level_clamped_to_source_endpoint_range"),
          "Unlearned/negative levels are blocked; over-range source evaluation clamps with an explicit trace");
    auto one = authored; one.script.fields[0].values = Json::array({1});
    const auto singleton = evaluateSkillCosts(data(one),1);
    check(singleton.consumeMp() == 10 && close(*singleton.cooldownMs(),1000.25) &&
          findKind(singleton.mp.diagnostics,"single_level_conflicting_endpoints"),
          "N=1 selects the first endpoint and diagnoses the conflicting second without division by zero");
    auto noRange = authored; noRange.script.fields.erase(noRange.script.fields.begin());
    const auto unknownRange = evaluateSkillCosts(data(noRange),1);
    check(!unknownRange.consumeMp() && unknownRange.mp.state == SkillNumericState::Malformed &&
          findKind(unknownRange.mp.diagnostics,"numeric_adapter_blocked") &&
          findKind(unknownRange.mp.diagnostics,"numeric_adapter_blocked")->at("reason").get<std::string>().find("explicit source-field adapter") != std::string::npos &&
          unknownRange.mp.trace.size() == 1,
          "Unknown N reports an adapter gap and never falls back to the purchase ceiling or level-info row count");
    auto duplicate = authored; duplicate.script.fields.insert(duplicate.script.fields.begin()+3,
        {"[consume MP]",Json::array({1,2}),32});
    check(evaluateSkillCosts(data(duplicate),1).mp.state == SkillNumericState::Ambiguous &&
          evaluateSkillCosts(data(duplicate),1).cooldown.usable(),
          "Duplicate selected parameter is ambiguous and cannot poison a separately valid cooldown field");
    auto noCost = authored; noCost.script.fields.erase(noCost.script.fields.begin()+2);
    check(evaluateSkillCosts(data(noCost),1).mp.state == SkillNumericState::Absent,
          "Absent common cost remains absent rather than becoming a zero-cost release");
    for (const auto &bad : {Json::array({}),Json::array({0}),Json::array({-2}),Json::array({2.5}),
             Json::array({"five"}),Json::array({5,6}),Json::array({uint64_t(std::numeric_limits<uint64_t>::max())})}) {
        auto source = authored; source.script.fields[0].values = bad;
        check(!evaluateSkillCosts(data(source),1).consumeMp(), "Invalid endpoint N fails with diagnostics: " + bad.dump());
    }
    for (const auto &bad : {Json::array({1}),Json::array({1,2,3}),Json::array({"one",2}),
             Json::array({-1,2}),Json::array({1,std::numeric_limits<double>::infinity()})}) {
        auto source = authored; source.script.fields[2].values = bad;
        check(evaluateSkillCosts(data(source),1).mp.state == SkillNumericState::Malformed,
              "Malformed endpoint pair is never executable: " + bad.dump());
    }
    SkillCostModifier weapon; weapon.id = "fixture.weapon-mp"; weapon.multiply = 1.1;
    weapon.evidence = Json::array({"Fixture source weapon multiplier"});
    SkillCostModifier state = weapon; state.id = "fixture.state-mp";
    const auto modified = evaluateSkillCosts(common,1,{weapon,state},{weapon});
    check(modified.consumeMp() == 13 && close(*modified.cooldownMs(),1100.275) &&
          modified.mp.trace[3]["id"] == "fixture.weapon-mp" &&
          modified.mp.trace[4]["id"] == "fixture.state-mp" &&
          close(modified.mp.trace[4]["before"].get<double>(),11.99),
          "Ordered weapon/state modifiers consume fractional intermediate values and truncate positive MP once at the end");
    CharacterDefinition chr;
    chr.source.script.path = "character/fixture.chr"; chr.source.bytes.resize(260, 0);
    chr.source.script.fields = {{"[weapon skill info]", Json::array({1.0, 1.1, 2.0, 2.1, 0.5, 0.6, 0.7, 0.8}), 40}};
    auto physical = authored;
    physical.script.fields.push_back({"[weapon effect type]", Json::array({"[physical]"}), 127});
    physical.script.fields.push_back({"[skill command advantage]", Json::array({10,20}), 137});
    auto physicalData = data(physical);
    auto characterCost = evaluateCharacterSkillCosts(physicalData, 3, chr, 1);
    check(characterCost.consumeMp() == 7 && close(*characterCost.cooldownMs(), 900.3) &&
          findKind(characterCost.consumerDiagnostics,"selected_weapon_effect_type") &&
          characterCost.mp.trace.back()["stage"] == "positive_truncate_final_mp" &&
          characterCost.mp.trace[characterCost.mp.trace.size()-2]["stage"] == "weapon_skill_multiplier",
          "Unique SKL weapon effect selects physical MP/CD columns from the raw EQU subtype CHR row");
    const auto inferredAbsence = inferred1031SkillCostAbsencePolicy();
    check(evaluateSkillCosts(data(noCost),1,{}, {},inferredAbsence).mp.state==SkillNumericState::Absent,
          "Named optional-field policy never supplies missing MP endpoints");
    auto optionalFields = authored;
    optionalFields.script.fields.push_back({"[weapon effect type]", Json::array({"[physical]"}), 127});
    optionalFields.script.fields.erase(std::remove_if(optionalFields.script.fields.begin(), optionalFields.script.fields.end(),
        [](const Field &field){return field.tag=="[cool time]";}),optionalFields.script.fields.end());
    const auto strictOptional = evaluateCharacterSkillCosts(data(optionalFields), 3, chr, 1);
    const auto inferredOptional = evaluateCharacterSkillCosts(data(optionalFields), 3, chr, 1, false, {}, {}, inferredAbsence);
    const auto *cooldownPolicyTrace = findStage(inferredOptional.cooldown.trace,"optional_field_absence_policy");
    check(!strictOptional.cooldownMs() && strictOptional.consumeMp()==7 && inferredOptional.consumeMp()==7 &&
          inferredOptional.cooldownMs()==0.0 && inferredOptional.absencePolicy==inferredAbsence &&
          cooldownPolicyTrace && cooldownPolicyTrace->at("native_default_confirmed")==false &&
          cooldownPolicyTrace->at("source_ref_kind")=="document" && cooldownPolicyTrace->at("source").at("scope")=="document" &&
          cooldownPolicyTrace->at("source").at("byte_offset")==0 &&
          cooldownPolicyTrace->at("source").at("byte_length")==optionalFields.bytes.size() &&
          cooldownPolicyTrace->at("source").at("member_path")==optionalFields.script.path &&
          cooldownPolicyTrace->at("source").at("member_sha256")==sha256(optionalFields.bytes),
          "Named 1031 opt-in treats only absent cooldown as zero while strict remains blocked and trace points to whole source document");
    check(evaluateSkillCosts(data(optionalFields),3).cooldown.state==SkillNumericState::Absent &&
          evaluateSkillCosts(data(optionalFields),3,{}, {},inferredAbsence).cooldownMs()==0.0 &&
          !evaluateSkillCosts(data(optionalFields),0,{}, {},inferredAbsence).cooldownMs() &&
          !evaluateCharacterSkillCosts(data(optionalFields),0,chr,1,false,{}, {},inferredAbsence).consumeMp(),
          "Free endpoint evaluator keeps strict absence default; opt-in zero cooldown cannot enable an unlearned skill");
    auto magical = physical;
    for (auto &field : magical.script.fields)
        if (field.tag == "[weapon effect type]") field.values = Json::array({"[magical]"});
    const auto magicalCost = evaluateCharacterSkillCosts(data(magical), 3, chr, 1);
    check(magicalCost.consumeMp() == 11 && close(*magicalCost.cooldownMs(), 1200.4),
          "Magical effect selects the separate CHR multiplier columns without using skill presentation flags");
    auto command = evaluateCharacterSkillCosts(physicalData, 3, chr, 1, true);
    check(command.consumeMp() == 7 && close(*command.cooldownMs(), 891.297) &&
          command.json()["classification"] == "inferred_beta" &&
          command.mp.trace.back()["stage"] == "positive_truncate_final_mp" &&
          close(command.mp.trace[command.mp.trace.size()-2]["result"].get<double>(), 7.791),
          "Command advantage uses source 0.1% units after weapon scaling with trace classification: " + command.json().dump());
    auto unknownEffect = physical;
    for (auto &field : unknownEffect.script.fields)
        if (field.tag == "[weapon effect type]") field.values = Json::array({"[hybrid]"});
    const auto blockedEffect = evaluateCharacterSkillCosts(data(unknownEffect), 3, chr, 1);
    check(!blockedEffect.consumeMp() && blockedEffect.mp.state == SkillNumericState::Malformed,
          "Unknown weapon effect type blocks the affected costs instead of guessing physical or magical");
    auto duplicateEffect = physical; duplicateEffect.script.fields.push_back({"[weapon effect type]", Json::array({"[magical]"}), 137});
    const auto blockedDuplicate = evaluateCharacterSkillCosts(data(duplicateEffect), 3, chr, 1);
    check(!blockedDuplicate.consumeMp() && blockedDuplicate.mp.state == SkillNumericState::Ambiguous,
          "Repeated weapon effect type is ambiguous and cannot select a multiplier row");
    auto malformedChr = chr; malformedChr.source.script.fields[0].values = Json::array({1, 2, 3});
    const auto blockedChr = evaluateCharacterSkillCosts(physicalData, 3, malformedChr, 1);
    check(!blockedChr.consumeMp() && blockedChr.mp.state == SkillNumericState::Malformed,
          "Malformed CHR multiplier table blocks source costs with a consumer diagnostic");
    const auto outOfRangeChr = evaluateCharacterSkillCosts(physicalData, 3, chr, 9);
    check(!outOfRangeChr.consumeMp() && findKind(outOfRangeChr.consumerDiagnostics,"weapon_skill_info_unavailable"),
          "Raw subtype outside CHR rows is rejected rather than mapped through legacy appearance category");
    check(characterCost.json().at("consumer_diagnostics") == characterCost.consumerDiagnostics,
          "Serialized cost trace includes consumer field selection and failure diagnostics");
    auto scoped = physical;
    scoped.script.fields.push_back({"[pvp]", Json::array(), 147});
    scoped.script.fields.push_back({"[weapon effect type]", Json::array({"[magical]"}), 152});
    scoped.script.fields.push_back({"[skill command advantage]", Json::array({1000,1000}), 162});
    scoped.script.fields.push_back({"[/pvp]", Json::array(), 177});
    const auto scopedCosts = evaluateCharacterSkillCosts(data(scoped), 3, chr, 1, true);
    check(scopedCosts.consumeMp() == command.consumeMp() && close(*scopedCosts.cooldownMs(), *command.cooldownMs()) &&
          findKind(scopedCosts.consumerDiagnostics,"selected_weapon_effect_type")->at("source").at("scope") == "common",
          "Non-overridable effect and command metadata are read from common scope without leaking later PvP fields");
    for (const auto &bad : {Json::array(),Json::array({}),Json::array({5}),Json::array({"[physical]","[magical]"})}) {
        auto source = physical;
        for (auto &field : source.script.fields) if (field.tag == "[weapon effect type]") field.values = bad;
        const auto costs = evaluateCharacterSkillCosts(data(source), 3, chr, 1);
        check(!costs.consumeMp() && costs.mp.state == (bad.empty() ? SkillNumericState::ExplicitEmpty : SkillNumericState::Malformed),
              "Empty/malformed effect never retains executable Value state: " + bad.dump());
        const auto optIn = evaluateCharacterSkillCosts(data(source), 3, chr, 1, false, {}, {}, inferredAbsence);
        check(!optIn.consumeMp() && optIn.mp.state == costs.mp.state,
              "Opt-in absence policy does not repair explicit-empty, malformed, or ambiguous effect metadata: " + bad.dump());
    }
    auto missingEffect = authored;
    const auto strictMissingEffect = evaluateCharacterSkillCosts(data(missingEffect),3,chr,1);
    const auto inferredMissingEffect = evaluateCharacterSkillCosts(data(missingEffect),3,chr,1,false,{}, {},inferredAbsence);
    check(!strictMissingEffect.consumeMp() && inferredMissingEffect.consumeMp()==15 &&
          findKind(inferredMissingEffect.consumerDiagnostics,"weapon_effect_type_absent_policy") &&
          findKind(inferredMissingEffect.consumerDiagnostics,"weapon_effect_type_absent_policy")->at("native_default_confirmed")==false &&
          findKind(inferredMissingEffect.consumerDiagnostics,"weapon_multiplier_not_applied") &&
          findStage(inferredMissingEffect.mp.trace,"optional_field_absence_policy")->at("source").at("member_path")==optionalFields.script.path,
          "Opt-in interprets only a truly absent common weapon effect as no multiplier and records an inferred document reference");
    auto repeatedMissingEffect = missingEffect;
    repeatedMissingEffect.script.fields.push_back({"[weapon effect type]",Json::array({"[physical]"}),177});
    repeatedMissingEffect.script.fields.push_back({"[weapon effect type]",Json::array({"[none]"}),192});
    check(evaluateCharacterSkillCosts(data(repeatedMissingEffect),3,chr,1,false,{}, {},inferredAbsence).mp.state == SkillNumericState::Ambiguous,
          "Opt-in absence policy does not repair repeated/ambiguous effect metadata");
    auto emptyCooldown = optionalFields;
    emptyCooldown.script.fields.push_back({"[cool time]",Json::array(),177});
    const auto strictEmptyCooldown = evaluateCharacterSkillCosts(data(emptyCooldown),3,chr,1);
    const auto inferredEmptyCooldown = evaluateCharacterSkillCosts(data(emptyCooldown),3,chr,1,false,{}, {},inferredAbsence);
    check(!strictEmptyCooldown.cooldownMs() && !inferredEmptyCooldown.cooldownMs() &&
          inferredEmptyCooldown.cooldown.state == SkillNumericState::ExplicitEmpty,
          "Opt-in no-cooldown rule does not repair an authored empty cooldown");
    auto repeatedCooldown = optionalFields;
    repeatedCooldown.script.fields.push_back({"[cool time]",Json::array({10,20}),177});
    repeatedCooldown.script.fields.push_back({"[cool time]",Json::array({30,40}),192});
    check(evaluateCharacterSkillCosts(data(repeatedCooldown),3,chr,1,false,{}, {},inferredAbsence).cooldown.state == SkillNumericState::Ambiguous,
          "Opt-in no-cooldown rule does not repair repeated/ambiguous cooldown metadata");
    auto malformedCooldown = optionalFields;
    malformedCooldown.script.fields.push_back({"[cool time]",Json::array({"bad",20}),177});
    check(evaluateCharacterSkillCosts(data(malformedCooldown),3,chr,1,false,{}, {},inferredAbsence).cooldown.state == SkillNumericState::Malformed,
          "Opt-in no-cooldown rule does not repair malformed cooldown endpoints");
    auto badAdvantage = physical;
    for (auto &field : badAdvantage.script.fields) if (field.tag == "[skill command advantage]") field.values = Json::array({"bad",2});
    const auto badCommand = evaluateCharacterSkillCosts(data(badAdvantage),3,chr,1,true);
    check(!badCommand.consumeMp() && badCommand.mp.state == SkillNumericState::Malformed &&
          findKind(badCommand.consumerDiagnostics,"command_advantage_unavailable"),
          "Malformed command reduction is Malformed rather than a Value with an absent numeric result");
    auto noAdvantage = physical;
    noAdvantage.script.fields.erase(std::remove_if(noAdvantage.script.fields.begin(),noAdvantage.script.fields.end(),
        [](const Field &field){return field.tag=="[skill command advantage]";}),noAdvantage.script.fields.end());
    const auto noCommandModifier = evaluateCharacterSkillCosts(data(noAdvantage),3,chr,1,true);
    check(noCommandModifier.consumeMp()==characterCost.consumeMp() &&
          close(*noCommandModifier.cooldownMs(),*characterCost.cooldownMs()) &&
          findKind(noCommandModifier.consumerDiagnostics,"command_advantage_absent"),
          "Absent optional command modifier is explicitly diagnosed as no reduction; numeric base remains source-driven");
    SkillCostModifier postWeapon; postWeapon.id = "post.weapon.add"; postWeapon.add = 1;
    postWeapon.evidence = Json::array({"Synthetic state modifier applies after weapon/command"});
    const auto ordered = evaluateCharacterSkillCosts(physicalData,3,chr,1,true,{postWeapon});
    check(ordered.consumeMp() == 8 && findStage(ordered.mp.trace,"modifier") &&
          close(findStage(ordered.mp.trace,"modifier")->at("before").get<double>(),7.791),
          "Additional ordered modifiers run after weapon and command scaling before the single final MP truncation");
    size_t finalConversions = 0;
    for (const auto &step : ordered.mp.trace) if (step.value("stage",std::string()) == "positive_truncate_final_mp") ++finalConversions;
    check(finalConversions == 1, "Character MP modifier chain performs exactly one final integer conversion");
    SkillCostResult unsafe;
    unsafe.mp.state = SkillNumericState::Value;
    for (double invalid : {-1.0, 0.5, std::numeric_limits<double>::infinity(), double(std::numeric_limits<int>::max())+1.0}) {
        unsafe.mp.value = invalid;
        check(!unsafe.consumeMp(), "Public MP consumer rejects invalid or unrepresentable completed cost");
    }
    auto reduction = weapon; reduction.multiply = 0; reduction.add = -10;
    check(evaluateSkillCosts(common,1,{reduction}).consumeMp() == 0,
          "Final negative additive cost is explicitly clamped to zero before positive truncation");
    auto invalidModifier = weapon; invalidModifier.evidence.clear();
    check(!evaluateSkillCosts(common,1,{invalidModifier}).consumeMp(),
          "A modifier without source evidence is diagnosed rather than silently accepted");
    invalidModifier = weapon; invalidModifier.multiply = std::numeric_limits<double>::max();
    check(!evaluateSkillCosts(common,1,{invalidModifier}).consumeMp(),
          "Modifier numeric overflow fails before an integer conversion");
    CharacterCatalog catalog(pvf);
    Json actual = Json::array();
    for (int job = 0; job < 10; ++job) {
        bool found = false;
        for (const auto &entry : catalog.at(job).skills.entries) {
            const auto &definition = catalog.skillDefinition({job,entry.id});
            if (definition.kind != SkillSourceKind::Active) continue;
            const auto selected = readSkillSourceData(definition);
            const auto first = evaluateSkillCosts(selected,1);
            if (!first.mp.usable() || !first.cooldown.usable()) continue;
            const int maximum = selected.values("[maximum level]")[0].get<int>();
            const auto last = evaluateSkillCosts(selected,maximum);
            const auto endpoints = selected.values("[consume MP]");
            const auto cooldowns = selected.values("[cool time]");
            check(first.consumeMp() == int(std::trunc(endpoints[0].get<double>())) &&
                  last.consumeMp() == int(std::trunc(endpoints[maximum == 1 ? 0 : 1].get<double>())) &&
                  close(*first.cooldownMs(),cooldowns[0].get<double>()) &&
                  close(*last.cooldownMs(),cooldowns[maximum == 1 ? 0 : 1].get<double>()),
                  "Actual job-local active skill source endpoints are consumed through the same range adapter: " + std::to_string(job));
            check(first.mp.trace[0]["source"]["member_sha256"] == makeSourceRef(pvf,entry.path).memberSha256,
                  "Actual numeric result is bound to the current PVF skill member hash: " + std::to_string(job));
            const auto effectFields = definition.fieldsInScope("[weapon effect type]");
            const auto weaponFields = catalog.at(job).source.script.fields;
            bool hasWeaponTable = false;
            for (const auto &field : weaponFields) if (normalize(field.tag) == "[weapon skill info]") hasWeaponTable = true;
            if (effectFields.size() == 1 && hasWeaponTable) {
                const auto consumer = evaluateCharacterSkillCosts(selected, 1, catalog.at(job), 0);
                check(findKind(consumer.consumerDiagnostics,"selected_weapon_effect_type") && consumer.mp.usable() && consumer.cooldown.usable(),
                      "Actual job source selects a unique weapon effect and CHR subtype-0 MP/CD row: " + std::to_string(job));
                const auto *multiplier = findStage(consumer.mp.trace, "weapon_skill_multiplier");
                if (effectFields.front()->field.values == Json::array({"[none]"}))
                    check(!multiplier && findKind(consumer.consumerDiagnostics,"weapon_multiplier_not_applied"),
                          "Explicit none effect retains the source's no-weapon-scaling semantics: " + std::to_string(job));
                else check(multiplier && multiplier->at("source").at("member_path") == catalog.at(job).source.script.path,
                           "Actual CHR multiplier trace retains the current character source identity: " + std::to_string(job));
            }
            actual.push_back({{"job", job}, {"skill", entry.id}, {"first", first.json()}, {"last", last.json()}});
            found = true; break;
        }
        check(found, "At least one actual active source in non-Creator job has explicit range and both endpoint fields: " + std::to_string(job));
    }
    for (const auto &path : {"skill/swordman/jumpattackmulti.skl", "skill/swordman/khazan.skl", "skill/swordman/guard.skl"}) {
        const CharacterSkillDefinition *definition = nullptr;
        for (const auto &entry : catalog.at(0).skills.entries)
            if (entry.path == path) { definition = &catalog.skillDefinition({0,entry.id}); break; }
        check(definition != nullptr, std::string("Current corpus resolves absence-policy control source ") + path);
        const auto selected = readSkillSourceData(*definition);
        const auto strict = evaluateCharacterSkillCosts(selected, 1, catalog.at(0), 0);
        const auto inferred = evaluateCharacterSkillCosts(selected, 1, catalog.at(0), 0, false, {}, {}, inferredAbsence);
        const bool strictBlocks = path == std::string("skill/swordman/jumpattackmulti.skl")
            ? !strict.cooldownMs() : !strict.consumeMp();
        check(strictBlocks && inferred.consumeMp().has_value() && inferred.cooldownMs().has_value() &&
              inferred.absencePolicy == inferredAbsence &&
              (path != std::string("skill/swordman/jumpattackmulti.skl") || inferred.cooldownMs() == 0.0),
              std::string("Only named 1031 absence policy enables current source optional fields: ") + path);
        const auto *trace = findStage(path == std::string("skill/swordman/jumpattackmulti.skl") ? inferred.cooldown.trace : inferred.mp.trace,
                                      "optional_field_absence_policy");
        check(trace && trace->at("native_default_confirmed") == false &&
              trace->at("source").at("member_path") == path && trace->at("source").at("scope") == "document",
              std::string("Current corpus absence evidence is source-bound and explicitly not native-default proof: ") + path);
    }
    // Resolve UpperSlash by source registration rather than assuming its local ID.
    bool upperFound = false;
    for (const auto &entry : catalog.at(0).skills.entries) if (entry.path == "skill/swordman/upperslash.skl") {
        upperFound = true;
        const auto selected = readSkillSourceData(catalog.skillDefinition({0,entry.id}));
        const auto atPurchaseCap = evaluateSkillCosts(selected,10);
        check(selected.values("[maximum level]") == Json::array({50}) && selected.purchaseMaximum(0) == 10 &&
              atPurchaseCap.consumeMp() == 12 && evaluateSkillCosts(selected,50).consumeMp() == 40,
              "Current UpperSlash maximum 50 controls MP range while purchase ceiling 10 never substitutes for N");
    }
    check(upperFound, "Current Swordman registry resolves the UpperSlash source used by the cost-range regression");
    return {{"status", "pass"}, {"checks", checks.size()}, {"passed", checks}, {"actual_source_endpoints", actual},
        {"classification", "Explicit inferred beta adapter with sample/current source evidence; full native numeric chain not claimed"}};
}
Json runSkillCostWorldTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), samples = Json::array();
    auto check = [&](bool passed, const std::string &message) {
        if (!passed) throw std::runtime_error("World skill cost: " + message);
        checks.push_back(message);
    };
    for (int category : {0,1,2,3}) for (int level : {1,10,50}) {
        World world(pvf,assets); world.weapon = category; world.freezeAi = true;
        int index = -1;
        for (size_t i=0;i<world.skills.size();++i) if (world.skills[i].source == "skill/swordman/upperslash.skl") index=int(i);
        check(index>=0,"Actual runtime resolves UpperSlash by its registered source");
        world.skills[index].level = level;
        const auto expected = world.skillCosts(index);
        check(expected.consumeMp().has_value() && expected.cooldownMs().has_value(),
              "Current runtime source EQU subtype and SKL/CHR fields produce executable costs");
        const int before = world.player.mp;
        world.activate(index);
        check(world.activeSkill()==index && world.player.mp==before-*expected.consumeMp() &&
              world.remainingCd(index)==int(std::ceil(*expected.cooldownMs())),
              "Real activation commits source-level weapon MP and CD for category " + std::to_string(category) + " level " + std::to_string(level));
        const auto trace = world.snapshot().at("last_skill_cost");
        check(trace.at("commit").at("consume_mp")==*expected.consumeMp() &&
              trace.at("consumer_diagnostics")==expected.consumerDiagnostics,
              "Runtime committed cost trace preserves exact field selection and source EQU diagnostics");
        samples.push_back({{"category",category},{"level",level},{"committed",trace}});
    }
    {
        World world(pvf,assets); world.freezeAi=true;
        int index=-1;
        for(size_t i=0;i<world.skills.size();++i)if(world.skills[i].source=="skill/swordman/gorecross.skl")index=int(i);
        check(index>=0,"Actual runtime resolves GoreCross command advantage source");
        const auto expected=world.skillCosts(index,true);const int before=world.player.mp;
        world.activate(index,true);
        check(expected.consumeMp().has_value() && world.activeSkill()==index && world.player.mp==before-*expected.consumeMp() &&
              world.remainingCd(index)==int(std::ceil(*expected.cooldownMs())),
              "Real command activation consumes source command advantage after weapon scaling");
    }
    return {{"status","pass"},{"checks",checks.size()},{"passed",checks},{"actual_commits",samples}};
}
} // namespace dnf
