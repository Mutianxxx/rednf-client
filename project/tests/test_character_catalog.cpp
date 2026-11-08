#include "dnf/character.hpp"
#include "dnf/collision.hpp"
#include "dnf/combat.hpp"
#include <stdexcept>
namespace dnf {
Json runCharacterCatalogTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool ok, const std::string &message) {
        if (!ok) throw std::runtime_error("Character source contract: " + message);
        checks.push_back(message);
    };
    CharacterCatalog catalog(pvf);
    check(catalog.characters.entries.size() == 11 && catalog.skillLists.entries.size() == 11 &&
          catalog.definitions.size() == 11, "All 11 actual CHR and skill-list registrations are retained");
    check(catalog.characters.issues.empty() && catalog.skillLists.issues.empty() && catalog.issues.empty(),
          "Current character and skill-list registries are unambiguous");
    check(catalog.nativeSkillData.size() == 7 && !catalog.defaultSettings.bytes.empty(),
          "All native SD parameter files and default character settings are retained without guessing controller ownership");
    const char *jobs[] = {"[swordman]", "[fighter]", "[gunner]", "[mage]", "[priest]", "[at gunner]",
        "[thief]", "[at fighter]", "[at mage]", "[demonic swordman]", "[creator mage]"};
    const size_t skillCounts[] = {175,163,167,207,195,167,120,178,104,201,57};
    const size_t attackCounts[] = {3,4,2,3,4,2,4,4,4,3,0};
    size_t allSkills = 0, emptyMotions = 0, motions = 0, attackInfos = 0;
    for (int id = 0; id < 11; ++id) {
        const auto &character = catalog.at(id);
        check(character.registration.ordinal == size_t(id) && character.registration.offset == size_t(2 + 10*id) &&
              character.registration.pathOffset == size_t(7 + 10*id) && character.job == jobs[id],
              "Job " + std::to_string(id) + " keeps its registry ID, ordinal, offsets and original job tag");
        check(character.skills.entries.size() == skillCounts[id] && character.skills.issues.empty(),
              "Job " + std::to_string(id) + " keeps all registered skills with their original IDs");
        check(character.motions("[attack motion]").size() == attackCounts[id],
              "Job " + std::to_string(id) + " preserves its own basic attack count");
        check(character.runtimeDeferredByUser == (id == 10),
              "Job " + std::to_string(id) + " applies only the user's CreatorMage deferral");
        check(character.issues.empty() && character.source.bytes == pvf.read(character.registration.path) &&
              character.source.script.tokens == pvf.script(character.registration.path).tokens &&
              character.source.provenance.contains("crc") && !character.settings.bytes.empty() &&
              character.settings.bytes == pvf.read(character.settings.script.path),
              "Job " + std::to_string(id) + " keeps immutable source bytes, ordered tokens and PVF provenance");
        for (const auto &entry : character.skills.entries) {
            check(entry.exists && character.skills.unique(entry.id) == &entry,
                  "Registered skill resolves: " + std::to_string(id) + ":" + std::to_string(entry.id));
        }
        allSkills += character.skills.entries.size();
        for (const auto &resource : character.resources) {
            const bool attackInfo = resource.tag.find("info]") != std::string::npos;
            if (attackInfo) ++attackInfos;
            else { ++motions; if (resource.literal.empty()) ++emptyMotions; }
            if (!resource.literal.empty()) {
                if (!resource.exists) throw std::runtime_error("Missing CHR binding: " + resource.path);
                if (!attackInfo && assets.animation(resource.path)->frames.empty())
                    throw std::runtime_error("Empty registered CHR ANI: " + resource.path);
            }
        }
    }
    check(allSkills == 1734 && motions == 1497 && emptyMotions == 67 && attackInfos == 670,
          "Independent Python/source audit totals agree, including all empty motion slots and attack-info entries");
    check(catalog.at(5).motionByStem("stay") == "character/gunner/atanimation/stay.ani" &&
          catalog.at(7).motionByStem("stay") == "character/fighter/atanimation/stay.ani" &&
          catalog.at(8).motionByStem("stay") == "character/mage/atanimation/stay.ani" &&
          catalog.at(9).motionByStem("stay") == "character/swordman/dsanimation/stay.ani",
          "AT and DS variants resolve relative to their actual CHR rather than invented job folders");
    const auto atMageAttacks = catalog.at(8).motions("[attack info]");
    check(atMageAttacks.size() == 4 && atMageAttacks[2]->path == atMageAttacks[3]->path &&
          atMageAttacks[2]->valueIndex == 2 && atMageAttacks[3]->valueIndex == 3,
          "Repeated ATMage attack-info paths remain separate indexed slots");
    const auto &swordman = catalog.at(0);
    bool initial = false, growth = false, awakening = false;
    for (const auto &block : swordman.stats) {
        check(block.endOffset > block.offset, "Stat source span has ordered bounds: " + block.tag);
        if (block.tag == "[initial value]") {
            initial = block.growtype == 0 && block.awakening == 0 && block.values("[attack speed]") == Json::array({850.0}) &&
                block.values("[MP regen speed]") == Json::array({50.0});
        }
        if (block.growtype == 2 && block.awakening == 0) growth = block.values("[MP regen speed]") == Json::array({2.5});
        if (block.growtype == 2 && block.awakening == 1) awakening = block.values("[MP regen speed]") == Json::array({2.5});
    }
    check(initial && growth && awakening, "Initial, growth and awakening repeated stat fields are never flattened");
    check(catalog.skill(0, 46).script.path == "skill/swordman/upperslash.skl" &&
          catalog.skill(0, 25).script.path == "skill/swordman/khazan.skl", "Existing active skills use their real registry IDs");
    bool absent = false;
    try { catalog.skill(0, -1); } catch (const std::exception &) { absent = true; }
    check(absent, "An absent skill is rejected without inventing a path or controller");
    auto sourceExport = catalog.snapshot(true);
    check(sourceExport["definitions"][10]["runtime_deferred_by_user"] == true &&
          sourceExport["definitions"][10]["source"]["bytes"].get<Bytes>() == catalog.at(10).source.bytes &&
          sourceExport["definitions"][10]["skills"]["entries"].size() == 57,
          "CreatorMage deferral retains its full data and skill list in portable source export");
    World world(pvf, assets);
    check(world.actorAni() == swordman.motionByStem("stay"), "Playable controller uses the source CHR motion binding");
    const CombatBox base{10,20,30,40,50,60};
    for (int axis = 0; axis < 3; ++axis) {
        auto edge = base;
        if (axis == 0) edge.x += base.w;
        if (axis == 1) edge.y += base.h;
        if (axis == 2) edge.z += base.d;
        CombatBox overlap;
        check(intersectCombatBoxes(base, edge, &overlap), "Native nonzero box face contact is inclusive, axis " + std::to_string(axis));
        check((axis == 0 ? overlap.w : axis == 1 ? overlap.h : overlap.d) == 0,
              "Native optional intersection can have zero extent at contact, axis " + std::to_string(axis));
        if (axis == 0) edge.x += 0.001;
        if (axis == 1) edge.y += 0.001;
        if (axis == 2) edge.z += 0.001;
        check(!intersectCombatBoxes(base, edge), "Strictly separated boxes are rejected, axis " + std::to_string(axis));
    }
    auto zero = base; zero.w = 0;
    check(!intersectCombatBoxes(base, zero), "Zero-size input boxes do not become point attacks");
    auto mirrored = combatBox({15,10,0,3,40,10,20},100,200,30,-1);
    check(mirrored.x == 50 && mirrored.y == 200 && mirrored.z == 33 && mirrored.w == 40,
          "Left-facing world volume mirrors local x as -x-width, keeping Y and Z independent");
    return {{"status", "pass"}, {"checks", checks}, {"check_count", checks.size()},
        {"scope", "Registered source data, real ANI decoding, current Swordman bindings and confirmed box helper; no full-job gameplay/parity claim"}};
}
} // namespace dnf
