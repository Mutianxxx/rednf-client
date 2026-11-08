#include "dnf/character.hpp"
#include <limits>
#include <stdexcept>
namespace dnf {
Json runCharacterIdentityTests(Pvf &pvf) {
    Json checks = Json::array();
    auto check = [&](bool ok, const std::string &message) {
        if (!ok) throw std::runtime_error("Character identity/source contract: " + message);
        checks.push_back(message);
    };
    check(CharacterIdentity::fromJson(Json::object()) == CharacterIdentity{},
          "Legacy absent identity defaults to unadvanced Swordman without changing job IDs");
    const CharacterIdentity identity{5, 4, 2};
    check(CharacterIdentity::fromJson(identity.json()) == identity,
          "Job, growtype and awakening survive portable identity round trip");
    check(!(SkillKey{0, 64} == SkillKey{9, 64}) && SkillKey{0, 64} < SkillKey{9, 64},
          "Equal local skill IDs in different jobs are distinct stable keys");
    check(SkillKey::fromJson(SkillKey{9, 64}.json()) == SkillKey{9, 64},
          "Qualified skill key survives portable round trip");
    for (const Json &invalid : {Json::array(), Json{{"job_id", -1}}, Json{{"growtype", 1.5}},
             Json{{"awakening", "1"}}, Json{{"job_id", uint64_t(std::numeric_limits<uint64_t>::max())}}}) {
        bool rejected = false;
        try { CharacterIdentity::fromJson(invalid); } catch (const std::exception &) { rejected = true; }
        check(rejected, "Malformed or overflowing identity is rejected: " + invalid.dump());
    }
    CharacterScript scripted;
    scripted.script.path = "synthetic/source.skl";
    scripted.bytes = {0xb0, 0xd0};
    scripted.script.tokens = {{{"offset", 2}, {"type", 5}, {"value", "[type]"}}};
    scripted.script.fields = {{"[type]", Json::array({"[active]"}), 2},
        {"[consume MP]", Json::array({1, 2}), 12}, {"[dungeon]", Json::array(), 27},
        {"[consume MP]", Json::array({3, 4}), 32}, {"[consume MP]", Json::array({5, 6}), 47},
        {"[/dungeon]", Json::array(), 62}, {"[pvp]", Json::array(), 67},
        {"[consume MP]", Json::array({7, 8}), 72}, {"[/pvp]", Json::array(), 87}};
    const auto parsed = parseCharacterSkillSource({2, 99}, {}, scripted);
    check(parsed.kind == SkillSourceKind::Active && parsed.runtimeRole == "unresolved" &&
          parsed.source.bytes == scripted.bytes && parsed.source.script.tokens == scripted.script.tokens,
          "Declared active type preserves original bytes/tokens and does not infer an internal/player role");
    check(parsed.values("[consume MP]") == Json::array({1, 2}) &&
          parsed.values("[consume MP]", "pvp") == Json::array({7, 8}) &&
          parsed.fieldsInScope("[consume MP]", "dungeon").size() == 2,
          "Common, dungeon and pvp retain independent ordered repeated fields");
    bool repeated = false;
    try { parsed.values("[consume MP]", "dungeon"); } catch (const std::exception &) { repeated = true; }
    check(repeated, "Ambiguous repeated field refuses a lossy first-value choice");
    scripted.script.fields.push_back({"[type]", Json::array({"[passive]"}), 92});
    check(parseCharacterSkillSource({2, 99}, {}, scripted).kind == SkillSourceKind::Unknown,
          "Conflicting active/passive declarations remain unresolved");
    CharacterCatalog catalog(pvf);
    for (int job : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
        const auto &definition = catalog.at(job);
        const auto motions = definition.motions("[attack motion]");
        for (const auto *source : motions)
            check(definition.motion("[attack motion]", source->valueIndex) == source->path,
                  "CHR original attack slot resolves for job " + std::to_string(job) + ":" + std::to_string(source->valueIndex));
        const auto appearance = catalog.defaultAppearanceSources(job);
        check(appearance.job == definition.job && appearance.bodyImageTemplates == definition.source.script.values("[body image path]") &&
              appearance.settings.bytes == definition.settings.bytes && !appearance.equipment.empty(),
              "Job-specific default appearance retains authored CHR template and exact settings source: " + std::to_string(job));
        const auto facts = catalog.identityEvidence({job, 5, 0});
        check(facts["runtime_branch_open"] == "not_established_by_source_model",
              "A sixth name slot never grants a playable advancement: " + std::to_string(job));
    }
    check(catalog.at(5).motion("[waiting motion]") == "character/gunner/atanimation/stay.ani" &&
          catalog.at(9).motion("[waiting motion]") == "character/swordman/dsanimation/stay.ani",
          "AT and DS waiting motions resolve by source field rather than a guessed folder");
    const auto &atMage = catalog.at(8);
    check(atMage.attackInfo("[attack info]", 2) == atMage.attackInfo("[attack info]", 3) &&
          atMage.resource("[attack info]", 2)->valueIndex != atMage.resource("[attack info]", 3)->valueIndex,
          "Repeated attack-info paths preserve distinct native source slots");
    bool emptyChecked = false;
    for (const auto &definition : catalog.definitions) for (const auto &binding : definition.resources)
        if (binding.literal.empty() && binding.tag == "[etc motion]") {
            check(definition.resource(binding.tag, binding.valueIndex) != nullptr,
                  "An empty authored motion occupies its original slot");
            bool rejected = false;
            try { definition.motion(binding.tag, binding.valueIndex); } catch (const std::exception &) { rejected = true; }
            check(rejected, "An empty motion does not borrow the next slot");
            emptyChecked = true; break;
        }
    check(emptyChecked, "Current source exercises authored empty motion slots");
    const auto &cross = catalog.skillDefinition({0, 64});
    check(cross.source.script.path == "skill/swordman/gorecross.skl" && cross.kind == SkillSourceKind::Active &&
          cross.source.bytes == pvf.read(cross.source.script.path) &&
          cross.values("[skill fitness growtype]") == Json::array({0, 1, 2, 3, 4}),
          "Real source skill retains exact job-local identity and explicit fitness");
    const auto novice = catalog.skillEligibility({0, 0, 0}, {0, 63});
    const auto berserker = catalog.skillEligibility({0, 3, 0}, {0, 63});
    check(novice.state == SourceLearningState::ExplicitlyExcluded &&
          berserker.state == SourceLearningState::ExplicitLearningCandidate && !berserker.grantsRuntimeUse,
          "Blood Lust is excluded from base job and only a source learning candidate for Berserker");
    check(catalog.skillEligibility({9, 0, 0}, {0, 64}).state == SourceLearningState::ExplicitlyExcluded,
          "A skill registered to another job is not qualified by its local numeric ID");
    const auto priest = catalog.defaultAppearanceSources(4);
    bool retainedUnknownNumber = false;
    for (const auto &entry : priest.equipment)
        if (entry.equipmentId == 4 && !entry.registered) retainedUnknownNumber = true;
    check(retainedUnknownNumber && !priest.issues.empty(),
          "Unresolved Priest default-equipment number survives instead of being silently interpreted as a slot");
    const auto gunner = catalog.defaultAppearanceSources(5);
    bool retainedWrongScope = false;
    for (const auto &entry : gunner.equipment)
        if (entry.equipmentId == 55820 && entry.registered && entry.exists && !entry.hasAnimationJob)
            retainedWrongScope = true;
    check(retainedWrongScope, "Cross-job default reference is retained and cannot masquerade as ATGunner animation scope");
    check(catalog.at(10).runtimeDeferredByUser && !catalog.skillDefinition({10, 254}).source.bytes.empty(),
          "Creator runtime deferral still retains its real registered skill source");
    return {{"status", "pass"}, {"checks", checks}, {"check_count", checks.size()},
        {"scope", "Source identity, typed registration, scope and appearance evidence; no all-character runtime/parity claim"}};
}
} // namespace dnf
