#include "dnf/equipment_motion.hpp"
#include <stdexcept>

namespace dnf {
Json runEquipmentMotionTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool ok, const std::string &message) {
        if (!ok) throw std::runtime_error("Equipment motion: " + message);
        checks.push_back(message);
    };
    CharacterCatalog catalog(pvf);
    auto body = [&](int job, const std::string &tag, size_t slot = 0) -> const CharacterResource & {
        const auto *resource = catalog.at(job).resource(tag, slot);
        if (!resource) throw std::runtime_error("Missing independently audited CHR fixture");
        return *resource;
    };
    const auto thief = loadEquipmentMotion(pvf, "equipment/character/thief.lay",
        "equipment/character/thief/avatar/coat/coat_a");
    const auto *knife = resolveEquipmentMotion(thief, body(6, "[etc motion]", 42));
    const auto *jumpKnife = resolveEquipmentMotion(thief, body(6, "[etc motion]", 43));
    check(body(6, "[etc motion]", 42).literal == "Animation/Shuriken.ani" &&
          knife && knife->status == EquipmentMotionStatus::Resolved && knife->fieldOffset == 252 &&
          knife->slot == 42 && knife->literal == "%s/ThrowKnife.ani" &&
          knife->path == "equipment/character/thief/avatar/coat/coat_a/throwknife.ani" &&
          knife->existenceChecked && knife->exists &&
          pvf.has("equipment/character/thief/avatar/coat/coat_a/shuriken.ani"),
          "Thief slot 42 uses authored ThrowKnife even though the incorrect body-stem Shuriken path also exists");
    check(jumpKnife && jumpKnife->slot == 43 && jumpKnife->literal == "%s/ThrowKnifeJump.ani" &&
          jumpKnife->path == "equipment/character/thief/avatar/coat/coat_a/throwknifejump.ani" &&
          !assets.animation(knife->path)->frames.empty() && !assets.animation(jumpKnife->path)->frames.empty(),
          "Thief grounded and jumping knife bindings independently resolve and decode real equipment ANI");
    check(thief.source.bytes == pvf.read("equipment/character/thief.lay") &&
          thief.source.script.tokens == pvf.script("equipment/character/thief.lay").tokens &&
          thief.source.provenance.contains("crc") && thief.layers.size() == 1 &&
          thief.layers[0].field.offset == 2 && thief.layers[0].supported &&
          thief.layers[0].endField == thief.source.script.fields.size() &&
          thief.layers[0].endOffset == thief.source.bytes.size(),
          "Original LAY bytes, ordered tokens, PVF provenance and layer source range are retained");

    const auto priest = loadEquipmentMotion(pvf, "equipment/character/priest.lay",
        "equipment/character/priest/avatar/hair/hair_a");
    for (size_t slot : {size_t(119), size_t(120)}) {
        const auto *empty = resolveEquipmentMotion(priest, body(4, "[etc motion]", slot));
        check(!body(4, "[etc motion]", slot).literal.empty() && empty &&
              empty->fieldOffset == 272 && empty->status == EquipmentMotionStatus::Empty &&
              empty->value == "" && empty->literal.empty() && empty->path.empty(),
              "Priest explicit empty equipment slot remains empty without a body or neighboring-slot fallback: " +
                  std::to_string(slot));
    }
    const auto sword = loadEquipmentMotion(pvf, "equipment/character/swordman.lay",
        "equipment/character/swordman/weapon/ssword/sswdc");
    const auto demonic = loadEquipmentMotion(pvf, "equipment/character/dsswordman.lay",
        "equipment/character/swordman/weapon/ssword/sswdc");
    const auto *swordStay = resolveEquipmentMotion(sword, body(0, "[waiting motion]"));
    const auto *dsStay = resolveEquipmentMotion(demonic, body(9, "[waiting motion]"));
    const auto *gore = resolveEquipmentMotion(sword, body(0, "[etc motion]", 25));
    check(swordStay && dsStay && gore && swordStay->path == dsStay->path &&
          swordStay->path == "equipment/character/swordman/weapon/ssword/sswdc/stay.ani" &&
          demonic.source.script.path == "equipment/character/dsswordman.lay" &&
          gore->path == "equipment/character/swordman/weapon/ssword/sswdc/gorecross.ani",
          "Swordman and Demonic Swordman retain separate LAY sources despite sharing an EQU animation directory");
    const auto atGunner = loadEquipmentMotion(pvf, "equipment/character/atgunner.lay",
        "equipment/character/gunner/weapon/revolver/at_revc");
    const auto *shot6 = resolveEquipmentMotion(atGunner, body(5, "[etc motion]", 6));
    const auto *shot7 = resolveEquipmentMotion(atGunner, body(5, "[etc motion]", 7));
    check(shot6 && shot7 && shot6 != shot7 && shot6->slot == 6 && shot7->slot == 7 &&
          shot6->fieldOffset == 262 && shot7->fieldOffset == 262 &&
          shot6->path == "equipment/character/gunner/weapon/revolver/at_revc/jumpattackshoot.ani" &&
          shot6->path == shot7->path && !assets.animation(shot6->path)->frames.empty(),
          "ATGunner duplicate JumpAttackShoot paths keep distinct original slots and decode the AT weapon resource");
    const auto atMage = loadEquipmentMotion(pvf, "equipment/character/atmage.lay",
        "equipment/character/mage/weapon/staff/at_staffa");
    const auto *attack3 = resolveEquipmentMotion(atMage, body(8, "[attack motion]", 2));
    check(attack3 && attack3->fieldOffset == 242 && attack3->slot == 2 &&
          attack3->path == "equipment/character/mage/weapon/staff/at_staffa/attack3.ani" &&
          !assets.animation(attack3->path)->frames.empty(),
          "ATMage resolves its own original attack slot and AT staff animation");
    const auto missingDirectory = loadEquipmentMotion(pvf, "equipment/character/thief.lay",
        "equipment/character/thief/no_such_equipment_layer");
    const auto *missing = resolveEquipmentMotion(missingDirectory, body(6, "[etc motion]", 42));
    check(missing && missing->status == EquipmentMotionStatus::Unsupported && missing->path.empty() &&
          missing->existenceChecked && !missing->exists && !missingDirectory.issues.empty(),
          "Missing exact PVF target clears the executable path and records a diagnostic");

    CharacterScript source;
    source.script.path = "synthetic/repeated.lay";
    source.bytes = {0xb0, 0xd0, 5, 0, 255, 0};
    source.provenance = {{"fixture", true}, {"future_metadata", Json::array({1, "keep"})}};
    source.script.tokens = Json::array({{{"offset", 2}, {"raw", "opaque_token"}}});
    source.script.fields = {{"[LAYER]", Json::array({0}), 2},
        {"[attack motion]", Json::array({"%s/First.ani", "", "%s/Third.ani"}), 12},
        {"[/attack motion]", Json::array(), 32},
        {"[future unknown]", Json::array({7, "unmodified"}), 37},
        {"[ATTACK MOTION]", Json::array({"%s/Repeated.ani"}), 52},
        {"[etc motion]", Json::array({"%s/ok.ani", "%s/%s.ani", "%02d.ani", "fixed.ani", "%s/%q.ani", 17}), 62},
        {"[throw motion 1-1]", Json::array({"%s/Throw.ani"}), 97},
        {"[damage motion 1]", Json::array({"%s/Damage.ani"}), 107}};
    auto parsed = parseEquipmentMotionSource(source, "Equipment/Test/Layer");
    CharacterResource requested;
    requested.tag = "[attack motion]";
    requested.valueIndex = 0;
    const auto *first = resolveEquipmentMotion(parsed, requested);
    const auto *repeat = resolveEquipmentMotion(parsed, requested, 1);
    check(first && repeat && first->path == "equipment/test/layer/first.ani" &&
          repeat->path == "equipment/test/layer/repeated.ani" &&
          first->fieldOffset == 12 && repeat->fieldOffset == 52 &&
          first->occurrence == 0 && repeat->occurrence == 1 &&
          !first->existenceChecked && !first->exists && parsed.bindings.size() == 12,
          "Repeated tags, original order and field occurrences survive without collapsing equal keys or claiming PVF existence");
    requested.valueIndex = 1;
    const auto *empty = resolveEquipmentMotion(parsed, requested);
    check(empty && empty->status == EquipmentMotionStatus::Empty && empty->path.empty() &&
          !resolveEquipmentMotion(parsed, requested, 1) && !resolveEquipmentMotion(parsed, requested, 2),
          "Empty slot is distinct from missing slot and missing repeated field");
    requested.tag = "[etc motion]";
    for (size_t slot = 1; slot < 6; ++slot) {
        requested.valueIndex = slot;
        const auto *unsupported = resolveEquipmentMotion(parsed, requested);
        check(unsupported && unsupported->status == EquipmentMotionStatus::Unsupported && unsupported->path.empty(),
              "Malformed, repeated, missing or unknown placeholders and non-string slots fail explicitly: " + std::to_string(slot));
    }
    check(parsed.source.bytes == source.bytes && parsed.source.provenance == source.provenance &&
          parsed.source.script.path == source.script.path && parsed.source.script.tokens == source.script.tokens &&
          parsed.source.script.fields.size() == source.script.fields.size() &&
          parsed.source.script.fields[3].values == Json::array({7, "unmodified"}) &&
          parsed.source.script.fields[4].tag == "[ATTACK MOTION]" &&
          parsed.source.script.fields[5].values[5] == 17,
          "Raw bytes, opaque tokens, metadata, original tag spelling, unknown fields and non-string source slots remain unchanged");
    for (int mode = 0; mode < 4; ++mode) {
        auto unsupportedSource = source;
        if (mode == 0) unsupportedSource.script.fields[0].values = Json::array({1});
        if (mode == 1) unsupportedSource.script.fields.insert(unsupportedSource.script.fields.begin() + 4,
            Field{"[LAYER]", Json::array({0}), 47});
        if (mode == 2) unsupportedSource.script.fields.erase(unsupportedSource.script.fields.begin());
        if (mode == 3) unsupportedSource.script.fields[0].values = Json::array({"0"});
        const auto unsupported = parseEquipmentMotionSource(unsupportedSource, "equipment/test/layer");
        bool allUnsupported = !unsupported.bindings.empty();
        for (const auto &binding : unsupported.bindings)
            allUnsupported = allUnsupported && binding.status == EquipmentMotionStatus::Unsupported && binding.path.empty();
        check(allUnsupported && !unsupported.issues.empty() &&
              unsupported.layers.size() == (mode == 1 ? 2u : mode == 2 ? 0u : 1u) &&
              (mode != 1 || (unsupported.layers[0].endField == 4 &&
                             unsupported.layers[0].endOffset == 47 && unsupported.layers[1].beginField == 4)),
              "Unsupported layer ID, repeated layers, absent marker and non-integer marker retain source ranges and disable bindings: " +
                  std::to_string(mode));
    }
    auto absentDirectory = parseEquipmentMotionSource(source, "");
    requested.tag = "[attack motion]"; requested.valueIndex = 0;
    const auto *absentPath = resolveEquipmentMotion(absentDirectory, requested);
    check(absentPath && absentPath->status == EquipmentMotionStatus::Unsupported && absentPath->path.empty(),
          "An absent animation directory cannot produce an invented relative path");
    return {{"status", "pass"}, {"checks", checks}, {"check_count", checks.size()},
        {"scope", "LAY source preservation, exact tag/occurrence/slot binding, explicit empties and real ANI decoding; native clocks/draw depth/gameplay parity not verified"}};
}
} // namespace dnf
