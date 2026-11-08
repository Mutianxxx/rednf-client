#include "dnf/content_catalog.hpp"
#include "dnf/region.hpp"
#include <limits>
#include <stdexcept>

namespace dnf {
Json runContentCatalogTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool value, const std::string &name) {
        if (!value) throw std::runtime_error("Content catalog: " + name);
        checks.push_back(name);
    };
    SourceRef fixture;
    fixture.packageIdentity = "synthetic-package"; fixture.memberPath = "fixture/boss.act";
    fixture.memberSha256 = "synthetic-member"; fixture.byteOffset = 37; fixture.ordinal = 4;
    fixture.literalPath = "../Boss.ACT"; fixture.scope = "dungeon";
    auto node = [&](const std::string &key, CapabilityState state = CapabilityState::Supported) {
        return CapabilityNode{key, state, state == CapabilityState::Supported ? "Implemented fixture consumer" :
            state == CapabilityState::Inferred ? "Explicit beta inference" : "Required mechanism not implemented",
            fixture, Json::array({"fixture consumer evidence"})};
    };
    auto edge = [&](const std::string &from, const std::string &to,
                    DependencyUse use = DependencyUse::Required, const std::string &condition = "",
                    const std::string &compiler = "") {
        return DependencyEdge{from, to, "source_reference", use, fixture, condition, compiler};
    };
    CapabilityGraph cycle;
    cycle.define(node("dungeon")); cycle.define(node("room")); cycle.define(node("portal"));
    cycle.depend(edge("dungeon", "room")); cycle.depend(edge("room", "portal")); cycle.depend(edge("portal", "room"));
    check(cycle.evaluate("dungeon").state == CapabilityState::Supported && cycle.evaluate("room").causes.empty(),
          "Legal implemented cycles converge without a recursive-visit false failure");
    cycle.define(node("boss", CapabilityState::Blocked)); cycle.depend(edge("portal", "boss"));
    auto blocked = cycle.evaluate("dungeon");
    check(!blocked.playable() && blocked.causes.size() == 1 && blocked.causes[0]["node"] == "boss" &&
          blocked.causes[0]["path"].size() == 3 &&
          blocked.causes[0]["path"][0]["from"] == "dungeon" &&
          blocked.causes[0]["path"][2]["to"] == "boss" &&
          blocked.causes[0]["source"]["byte_offset"] == 37,
          "A missing required boss mechanism propagates through a cycle with the full source cause path");
    const auto blockedSnapshot = cycle.snapshot();
    const Json *roomRegistration = nullptr;
    for (const auto &registration : blockedSnapshot.at("nodes"))
        if (registration.at("key") == "room") roomRegistration = &registration;
    check(roomRegistration && roomRegistration->at("local_state") == "Supported" &&
          roomRegistration->at("aggregate_evaluation_required") == true && !roomRegistration->contains("status") &&
          blockedSnapshot.at("aggregate_evaluation_required") == true && cycle.evaluate("room").json().at("status") == "Blocked",
          "A locally supported room with a missing required boss never appears Playable in the graph snapshot");
    CapabilityGraph inference;
    inference.define(node("player")); inference.define(node("skill", CapabilityState::Inferred));
    inference.depend(edge("player", "skill"));
    check(inference.evaluate("player").state == CapabilityState::Inferred && inference.evaluate("player").playable() &&
          inference.evaluate("player").json()["status"] == "PlayableWithInference",
          "Complete inferred consumers remain playable with their inference classification and evidence");
    CapabilityGraph optional;
    optional.define(node("room")); optional.define(node("spark")); optional.define(node("emitter", CapabilityState::Blocked));
    optional.depend(edge("room", "spark", DependencyUse::OptionalPresentation));
    optional.depend(edge("spark", "emitter"));
    optional.depend(edge("room", "missing-preload", DependencyUse::Preload));
    optional.depend(edge("room", "external-notice", DependencyUse::Metadata));
    auto presentation = optional.evaluate("room");
    check(presentation.state == CapabilityState::Supported && presentation.causes.empty() && presentation.warnings.size() == 2 &&
          presentation.warnings[0]["node"] == "emitter" && presentation.warnings[0]["path"].size() == 2,
          "Classified optional presentation and preload report complete warning paths without blocking; metadata stays metadata");
    CapabilityGraph conditional;
    conditional.define(node("dungeon")); conditional.define(node("quest-room", CapabilityState::Blocked));
    conditional.depend(edge("dungeon", "quest-room", DependencyUse::Required, "quest-variant"));
    CapabilityContext ordinary{"dungeon", {{"quest-variant", false}}};
    CapabilityContext quest{"dungeon", {{"quest-variant", true}}};
    check(conditional.evaluate("dungeon", ordinary).state == CapabilityState::Supported &&
          conditional.evaluate("dungeon", quest).state == CapabilityState::Blocked &&
          conditional.evaluate("dungeon").state == CapabilityState::Blocked &&
          conditional.evaluate("dungeon").causes[0]["reason"] == "Unresolved dependency condition: quest-variant",
          "Explicit conditions respect the selected mode; unknown required conditions fail closed");
    CapabilityGraph compiler;
    compiler.define(node("skill")); compiler.define(node("skill.skl"));
    compiler.depend(edge("skill", "skill.skl", DependencyUse::Required, "", "action.capture"));
    auto missingCompiler = compiler.evaluate("skill");
    check(missingCompiler.state == CapabilityState::Blocked && missingCompiler.causes[0]["node"] == "action.capture" &&
          missingCompiler.causes[0]["path"][0]["kind"] == "semantic_compiler_for:source_reference",
          "Source existence cannot bypass a missing executable semantic compiler capability");
    CapabilityGraph compilerWarnings;
    for (const auto &key : {"skill", "skill.skl", "action.capture"}) compilerWarnings.define(node(key));
    compilerWarnings.depend(edge("skill", "skill.skl", DependencyUse::Required, "", "action.capture"));
    compilerWarnings.depend(edge("action.capture", "missing-capture-effect", DependencyUse::OptionalPresentation));
    compilerWarnings.depend(edge("action.capture", "missing-capture-preload", DependencyUse::Preload));
    compilerWarnings.depend(edge("action.capture", "external-capture-metadata", DependencyUse::Metadata));
    const auto compilerPresentation = compilerWarnings.evaluate("skill");
    check(compilerPresentation.state == CapabilityState::Supported && compilerPresentation.causes.empty() &&
          compilerPresentation.warnings.size() == 2 &&
          compilerPresentation.warnings[0].at("node") == "missing-capture-effect" &&
          compilerPresentation.warnings[1].at("node") == "missing-capture-preload" &&
          compilerPresentation.warnings[0].at("path").size() == 2 &&
          compilerPresentation.warnings[0].at("path")[0].at("kind") == "semantic_compiler_for:source_reference" &&
          compilerPresentation.warnings[0].at("path")[0].at("to") == "action.capture" &&
          compilerPresentation.warnings[0].at("path")[1].at("from") == "action.capture",
          "Required compiler optional-presentation and preload gaps retain compiler source paths without blocking skill gameplay");
    check(compiler.evaluate("unregistered").state == CapabilityState::Blocked &&
          compiler.evaluate("unregistered").causes[0]["reason"] == "Missing dependency node",
          "Absent targets fail closed and explain the missing node");
    bool rejected = false;
    try { compiler.define(node("skill")); } catch (const std::exception &) { rejected = true; }
    check(rejected, "Conflicting node registrations cannot silently replace runtime claims");
    // All variants, rather than a selected random room, are required dependencies.
    CapabilityGraph alternatives;
    for (const auto &key : {"dungeon", "ordinary-a", "ordinary-b", "boss-a"}) alternatives.define(node(key));
    alternatives.define(node("boss-b", CapabilityState::Blocked));
    for (const auto &key : {"ordinary-a", "ordinary-b", "boss-a", "boss-b"}) alternatives.depend(edge("dungeon", key));
    check(alternatives.evaluate("ordinary-a").playable() && !alternatives.evaluate("dungeon").playable(),
          "An implemented selected room cannot hide an unsupported legal boss alternative");
    SemanticAdapterRegistry adapters;
    auto adapter = [&](const std::string &id, const std::string &identity, int priority) {
        SemanticAdapter value;
        value.id = id; value.version = "1"; value.format = "act-1031"; value.contentIdentity = identity;
        value.behavior = "fixture.capture"; value.sourceSelection = "exact ACT field +37";
        value.invalidation = "different consumer/field layout"; value.priority = priority;
        value.state = CapabilityState::Inferred; value.evidence = Json::array({fixture.json()});
        value.limitations = Json::array({"Only a synthetic adapter"});
        return value;
    };
    adapters.add(adapter("format-rule", "", 0)); adapters.add(adapter("scoped-rule", "pvf-a", 0));
    const auto ambiguous = adapters.resolve("act-1031", "pvf-a");
    check(!ambiguous.adapter && ambiguous.candidates.size() == 2 &&
          ambiguous.reason == "Ambiguous semantic adapters at equal priority" &&
          adapters.resolve("act-1031", "pvf-b").adapter->id == "format-rule" &&
          !adapters.resolve("act-other", "pvf-a").adapter,
          "Version/content matching is exact and equal-priority overlap refuses an implicit winner");
    adapters.add(adapter("explicit-priority", "pvf-a", 2));
    const auto chosen = adapters.resolve("act-1031", "pvf-a");
    check(chosen.adapter && chosen.adapter->id == "explicit-priority" && chosen.adapter->state == CapabilityState::Inferred &&
          chosen.adapter->json()["evidence"][0]["literal_path"] == "../Boss.ACT",
          "Explicit adapter priority selects a versioned inferred consumer while preserving source evidence");
    rejected = false;
    try { auto bad = adapter("no-evidence", "pvf-a", 3); bad.evidence.clear(); adapters.add(bad); }
    catch (const std::exception &) { rejected = true; }
    check(rejected, "Adapter behavior cannot be registered without evidence and invalidation metadata");
    ContentCatalog catalog(pvf);
    check(catalog.members().size() == pvf.count() && catalog.members().size() == pvf.paths("").size(),
          "Every member of the actual current archive remains indexed without an executable-behavior claim");
    check(catalog.member("CHARACTER\\CHARACTER.LST") && !catalog.member("missing/example.skl"),
          "Canonical lookup preserves existence and does not invent source members");
    std::map<std::string, size_t> formats;
    for (const auto &member : catalog.members()) ++formats[member.format];
    for (const auto &format : {"chr", "skl", "equ", "stk", "mob", "obj", "twn", "wdm", "dgn", "map", "til", "ui", "act", "ani", "als", "ptl"})
        check(formats[format] > 0, std::string("Current PVF source discovery includes ") + format + " inputs");
    const auto &jobList = catalog.registries().at("skill/skilllist.lst");
    const auto &characters = catalog.registries().at("character/character.lst");
    size_t skills = 0;
    for (const auto &job : jobList.list.entries) {
        const auto &skillsList = catalog.registries().at(job.path);
        check(skillsList.kind == "skill" && skillsList.list.source.bytes == pvf.read(job.path) &&
              skillsList.source.memberSha256 == makeSourceRef(pvf, job.path).memberSha256,
              "Actual job-local registration retains exact source bytes and member identity: " + job.path);
        skills += skillsList.list.entries.size();
        for (const auto &row : skillsList.list.entries) {
            check(!row.literal.empty() && row.pathOffset == row.offset + 5 &&
                  skillsList.list.source.script.tokens.at(row.ordinal * 2).at("value") == row.id &&
                  skillsList.list.source.script.tokens.at(row.ordinal * 2 + 1).at("value") == row.literal,
                  "Job-local skill row preserves ID, literal, ordinal and both token offsets: " + job.path + ":" + std::to_string(row.id));
        }
    }
    check(jobList.list.entries.size() == characters.list.entries.size() && skills > 0 &&
          catalog.registration("character/character.lst", 10) &&
          catalog.registration("skill/skilllist.lst", 10),
          "Character and skill registries retain the user-deferred Creator source as well as every other job");
    const auto source = catalog.loadDocument("character/character.lst");
    check(source.token5 && source.bytes == characters.list.source.bytes &&
          source.script.tokens == characters.list.source.script.tokens &&
          source.json(true)["bytes"].get<Bytes>() == source.bytes,
          "Lazy documents retain original raw bytes, token string indices and fields for future ports");
    const auto raw = catalog.loadDocument("stringtable.bin");
    check(!raw.token5 && !raw.diagnostics.empty() && raw.bytes == pvf.read("stringtable.bin") &&
          raw.source.memberPath == "stringtable.bin",
          "Undecodable token5 data remains available with diagnostics rather than being discarded");
    RegionCatalog actualRegion(pvf, assets);
    const auto regionGraph = buildRegionCapabilityGraph(pvf, actualRegion);
    Json regionReports = Json::array();
    const auto worldReport = regionGraph.evaluate("beta.world");
    bool fullWorldBlocked = false;
    for (const auto &cause : worldReport.causes) if (cause["node"] == "region.full-world-closure") fullWorldBlocked = true;
    check(worldReport.state == CapabilityState::Blocked && fullWorldBlocked,
          "Full-world target records the limited runtime catalog instead of claiming all registered regions were audited");
    const auto actualSnapshot = regionGraph.snapshot();
    bool localWorldOnly = false;
    for (const auto &registration : actualSnapshot.at("nodes")) if (registration.at("key") == "beta.world")
        localWorldOnly = registration.at("local_state") == "Supported" &&
            registration.at("aggregate_evaluation_required") == true && !registration.contains("status");
    check(localWorldOnly && worldReport.json().at("status") == "Blocked",
          "Actual current world snapshot reports its local registration without mislabeling its blocked aggregate as Playable");
    regionReports.push_back(worldReport.json());
    for (const auto &[id, dungeon] : actualRegion.dungeons) {
        const auto key = "beta.dungeon:" + std::to_string(id);
        const auto report = regionGraph.evaluate(key);
        check(report.state == CapabilityState::Blocked && !report.causes.empty(),
              "Actual dungeon source never claims the unfinished full beta behavior is playable: " + std::to_string(id));
        size_t fullWorld = 0, normalGameplay = 0;
        for (const auto &cause : report.causes) {
            if (cause["node"] == "region.full-world-closure") ++fullWorld;
            if (cause["node"] == "dungeon.complete-progression") ++normalGameplay;
        }
        check(fullWorld == 0 && normalGameplay == 1,
              "Local dungeon has its normal-gameplay blocker without depending on unrelated world coverage: " + std::to_string(id));
        std::set<int> expected;
        for (int mapId : dungeon.mapIds) {
            auto map = actualRegion.maps.find(mapId);
            if (map == actualRegion.maps.end() || !map->second.special) expected.insert(mapId);
        }
        for (const auto &maze : dungeon.mazes)
            for (const auto *groups : {&maze.specifiedMaps, &maze.specifiedBossMaps})
                for (const auto &[cell, maps] : *groups) expected.insert(maps.begin(), maps.end());
        std::set<int> audited;
        for (const auto &edge : regionGraph.edges()) if (edge.from == key && edge.kind == "all_legal_candidate_rooms" &&
                edge.to.rfind("map:", 0) == 0) audited.insert(std::stoi(edge.to.substr(4)));
        check(audited == expected,
              "Actual DGN audit includes every normal MAP and explicit ordinary/boss alternative: " + std::to_string(id));
        bool hasObjectPath = false, hasMonsterPath = false;
        for (const auto &cause : report.causes) {
            if (cause["node"] == "object.complete-behavior" && cause["path"].size() == 3)
                hasObjectPath = true;
            if (cause["node"] == "monster.complete-behavior" && cause["path"].size() == 3)
                hasMonsterPath = true;
        }
        if (dungeon.enabled) check(hasObjectPath && hasMonsterPath,
            "Current demo entry exposes full DGN/MAP/entity/consumer paths for beta gaps: " + std::to_string(id));
        regionReports.push_back(report.json());
    }
    // Reproduce the dangerous case: a source DGN explicitly references a MAP
    // which the current runtime folder filter never loaded.
    auto &firstDungeon = actualRegion.dungeons.begin()->second;
    const auto existingMaps = firstDungeon.mapIds;
    const auto existingEnabled = firstDungeon.enabled;
    const int missingMap = std::numeric_limits<int>::max();
    firstDungeon.mapIds.push_back(missingMap);
    const auto missingGraph = buildRegionCapabilityGraph(pvf, actualRegion);
    const auto missingReport = missingGraph.evaluate("beta.dungeon:" + std::to_string(firstDungeon.id));
    bool missingFound = false;
    for (const auto &cause : missingReport.causes) if (cause["node"] == "map:" + std::to_string(missingMap))
        missingFound = cause["reason"] == "DGN candidate MAP is absent from the runtime RegionCatalog" &&
            cause["path"].size() == 1;
    check(missingFound && firstDungeon.enabled == existingEnabled,
          "A missing legal MAP candidate has an explicit cause path and does not rewrite historical demo eligibility");
    firstDungeon.mapIds = existingMaps;
    return {{"status", "pass"}, {"checks", checks.size()}, {"passed", checks},
        {"actual_member_count", catalog.members().size()}, {"actual_formats", formats},
        {"actual_registry_count", catalog.registries().size()}, {"actual_skill_registration_rows", skills},
        {"registry_diagnostics", catalog.diagnostics()}, {"actual_region_beta_capabilities", regionReports},
        {"scope", "Source discovery, fixed-point capability evaluation and adapter selection; full semantic closure is not claimed"}};
}
} // namespace dnf
