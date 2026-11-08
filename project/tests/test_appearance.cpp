#include "dnf/appearance.hpp"
#include "dnf/progression.hpp"
#include "dnf/storage.hpp"
#include <chrono>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
Json appearanceState(const CharacterAppearance &appearance) {
    Json parts = Json::object(), layers = Json::array();
    for (const auto &[slot, part] : appearance.parts)
        parts[slot] = {{"path", part.source.path}, {"variation", part.variation}};
    for (const auto &layer : appearance.orderedLayers())
        layers.push_back({{"order", layer.order}, {"slot", layer.slot}, {"name", layer.name},
                          {"source", layer.sourcePath}, {"variation", layer.variation},
                          {"offset", layer.sourceOffset}});
    return {{"parts", parts}, {"layers", layers}, {"body_variation", appearance.bodyVariation()}};
}
}

Json runAppearanceTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto require = [&](bool condition, const std::string &name) {
        if (!condition) throw std::runtime_error(std::string("Appearance: ") + name);
        checks.push_back(name);
    };
    const auto sword = pvf.script("equipment/character/swordman/weapon/ssword/sswd_default.equ");
    const auto club = pvf.script("equipment/character/swordman/weapon/club/club_default.equ");
    const auto hair = pvf.script("equipment/character/swordman/avatar/hair/ahair_default.equ");
    const auto twoLayerCoat = pvf.script("equipment/character/swordman/avatar/coat/101500425.equ");
    const auto oneLayerCoat = pvf.script("equipment/character/swordman/avatar/coat/101500008.equ");
    const auto skin = pvf.script("equipment/character/swordman/avatar/skin/101580060.equ");
    const auto armor = pvf.script("equipment/character/common/jacket/cloth/vest_owool.equ");
    std::map<std::string, Bytes> originalBytes;
    for (const auto *source : {&sword, &club, &hair, &twoLayerCoat, &oneLayerCoat, &skin, &armor})
        originalBytes.emplace(source->path, pvf.read(source->path));

    // Fixed expectations below are independently checked source fields, rather
    // than deriving the expected output through the appearance parser itself.
    require(sword.values("[variation]") == Json::array({0, 0}) &&
            sword.values("[layer variation]") == Json::array({2790, "sswdc"}) &&
            club.values("[variation]") == Json::array({0, 7}) &&
            twoLayerCoat.values("[variation]") == Json::array({37, 1}) &&
            oneLayerCoat.values("[variation]") == Json::array({123, 0}) &&
            skin.values("[variation]") == Json::array({0, 1}),
            "Real EQU fixtures retain authored model/palette pairs and front weapon layer 2790");
    auto parsedSword = parseEquipmentAppearance(sword);
    require(parsedSword.layers.size() == 2 && parsedSword.layers[0].name == "sswdc" &&
            parsedSword.layers[0].order == 2790 && parsedSword.layers[1].name == "sswdb" &&
            parsedSword.layers[1].order == 650 && parsedSword.layers[0].sourceOffset == 242 &&
            parsedSword.layers[1].sourceOffset == 267,
            "Both source weapon layers and their original field offsets survive parsing");
    auto parsedHair = parseEquipmentAppearance(hair);
    auto demonicHair = parseEquipmentAppearance(hair, "[demonic swordman]");
    require(parsedHair.variation == std::array<int, 2>{0, 0} &&
            demonicHair.variation == std::array<int, 2>{114, 0} &&
            parsedHair.layers.size() == 1 && demonicHair.layers.size() == 1 &&
            parsedHair.layers[0].name == "hair_a" && parsedHair.layers[0].order == 2000,
            "Repeated animation-job blocks select Swordman without leaking Demonic Swordman variation 114");
    require(parsedSword.source.tokens == sword.tokens && parsedSword.source.fields.size() == sword.fields.size() &&
            parsedHair.source.tokens == hair.tokens && parsedHair.source.values("[name2]") == hair.values("[name2]"),
            "Complete ordered source tokens and unrelated EQU fields remain available for future ports");

    CharacterCatalog characterCatalog(pvf);
    auto appearance = defaultCharacterAppearance(pvf, characterCatalog, {0, 0, 0});
    require(appearance.identity == CharacterIdentity{0, 0, 0} &&
            appearance.job == characterCatalog.at(0).job && !appearance.parts.empty() &&
            appearance.parts.at("[coat avatar]").source.path ==
                "equipment/character/swordman/avatar/coat/acoat_default.equ" &&
            appearance.parts.at("[pants avatar]").variation == std::array<int, 2>{0, 0},
            "Swordman appearance resolves from its registered CHR default-equipment source");
    bool distinctJobSource = false;
    for (int jobId = 0; jobId < 10; ++jobId) {
        const auto &character = characterCatalog.at(jobId);
        const auto source = characterCatalog.defaultAppearanceSources(jobId);
        const auto actual = defaultCharacterAppearance(pvf, characterCatalog, {jobId, 0, 0});
        std::set<std::string> eligiblePaths;
        for (const auto &entry : source.equipment)
            if (entry.equipmentId >= 0 && entry.registered && entry.exists && entry.hasAnimationJob)
                eligiblePaths.insert(entry.path);
        bool referenced = !actual.parts.empty();
        for (const auto &[slot, part] : actual.parts)
            referenced = referenced && part.job == character.job && eligiblePaths.count(part.source.path) != 0;
        require(actual.identity == CharacterIdentity{jobId, 0, 0} && actual.job == character.job &&
                referenced && actual.bodyMotions.size() > 0,
                "Base appearance uses only this CHR's registered default EQU sources for job " +
                    std::to_string(jobId));
        if (jobId != 0) for (const auto &path : eligiblePaths)
            if (path.find("equipment/character/swordman/") == std::string::npos) distinctJobSource = true;
    }
    require(distinctJobSource, "Other base jobs resolve their own registered equipment resources");
    require(applyEquipmentAppearance(appearance, sword) && applyEquipmentAppearance(appearance, twoLayerCoat),
            "Authored weapon and split front/rear coat appearances apply");
    std::vector<int> orders;
    std::vector<std::string> names;
    for (const auto &layer : appearance.orderedLayers()) { orders.push_back(layer.order); names.push_back(layer.name); }
    require(orders == std::vector<int>({650, 900, 1200, 1300, 1400, 1500, 1800, 2000, 2790}) &&
            names == std::vector<std::string>({"sswdb", "coat_b", "shoes_b", "pants_b", "shoes_a",
                                               "pants_a", "coat_a", "hair_a", "sswdc"}),
            "Numeric EQU layer order places rear weapon 650 before clothes and front weapon 2790 after hair");
    auto beforeArmor = appearanceState(appearance);
    require(armor.text("[equipment type]") == "[coat]" && armor.values("[variation]").empty() &&
            !applyEquipmentAppearance(appearance, armor) && appearanceState(appearance) == beforeArmor,
            "Ordinary stat coat without authored appearance cannot erase an equipped coat avatar");
    require(applyEquipmentAppearance(appearance, oneLayerCoat) &&
            appearance.parts.at("[coat avatar]").variation == std::array<int, 2>{123, 0} &&
            appearance.parts.at("[coat avatar]").layers.size() == 1 &&
            appearance.parts.at("[coat avatar]").layers[0].name == "coat_a" &&
            appearance.orderedLayers().size() == 8,
            "Changing the same avatar slot replaces its full layer set without leaving the previous coat rear layer");

    const auto coatAni = assets.animation("equipment/character/swordman/avatar/coat/coat_a/stay.ani");
    const auto clubAni = assets.animation("equipment/character/swordman/weapon/club/clubc/stay.ani");
    const auto bodyAni = assets.animation("character/swordman/animation/stay.ani");
    require(coatAni->frames[0].image == "Character/Swordman/Equipment/Avatar/coat/sm_coat%02d%02da.img" &&
            coatAni->frames[0].imageFrame == 90 && clubAni->frames[0].imageFrame == 90 &&
            bodyAni->frames[0].image == "Character/Swordman/Equipment/Avatar/skin/sm_body%04d.img",
            "Real ANI fixture supplies authored IMG placeholder patterns and frame 90");
    const auto coat37Image = appearanceImage(coatAni->frames[0].image, {37, 1});
    const auto coat123Image = appearanceImage(coatAni->frames[0].image, {123, 0});
    const auto clubImage = appearanceImage(clubAni->frames[0].image, {0, 7});
    const auto skinImage = appearanceImage(bodyAni->frames[0].image, {0, 1}, true);
    require(coat37Image == "character/swordman/equipment/avatar/coat/sm_coat3701a.img" &&
            coat123Image == "character/swordman/equipment/avatar/coat/sm_coat12300a.img" &&
            clubImage == "character/swordman/equipment/weapon/club/club0007c.img" &&
            skinImage == "character/swordman/equipment/avatar/skin/sm_body0001.img" &&
            appearanceImage("future/%s_%02d.img", {7, 2}) == "future/%s_07.img",
            "Model and palette substitute independently, three-digit model 123 survives, unknown placeholders stay literal");
    Json images = Json::array();
    for (const auto &path : {coat37Image, coat123Image, clubImage, skinImage}) {
        const auto pixels = assets.pixels(path, 90);
        require(pixels.width > 0 && pixels.height > 0 &&
                pixels.rgba.size() == size_t(pixels.width) * pixels.height * 4,
                "Resolved real outfit/weapon/skin frame is present and decodes as nonempty RGBA");
        images.push_back({{"path", path}, {"frame", 90}, {"width", pixels.width}, {"height", pixels.height},
                          {"crop_x", pixels.x}, {"crop_y", pixels.y}});
    }

    RegionCatalog catalog(pvf, assets);
    Progression progression(catalog);
    progression.state["level"] = 99;
    auto appendItem = [&](int id) {
        const auto *definition = progression.item(id);
        if (!definition) throw std::runtime_error("Appearance fixture item ID missing");
        int index = int(progression.state["inventory"].size());
        int uid = progression.state["next_uid"];
        progression.state["next_uid"] = uid + 1;
        progression.state["inventory"].push_back({{"uid", uid}, {"id", id}, {"count", 1},
            {"durability", definition->durability}, {"future_instance", {{"retained", id}}}});
        return index;
    };
    const int clubIndex = appendItem(27900), coatTwoIndex = appendItem(101500425);
    const int coatOneIndex = appendItem(101500008), hairIndex = appendItem(1010000);
    const int skinIndex = appendItem(101580060), armorIndex = appendItem(10018);
    require(progression.item(27900)->path == club.path && progression.item(101500425)->path == twoLayerCoat.path &&
            progression.item(1010000)->avatar && progression.item(101500425)->avatar &&
            !progression.item(10018)->avatar && progression.item(10018)->slot == "[coat]",
            "Original item IDs resolve to real definitions and keep cosmetic avatar slots distinct from stat armor");
    require(progression.equip(clubIndex).ok && progression.equip(coatTwoIndex).ok &&
            progression.equip(hairIndex).ok && progression.equip(skinIndex).ok && progression.equip(armorIndex).ok &&
            progression.equippedIndex("[coat]") == armorIndex &&
            progression.equippedIndex("[coat avatar]") == coatTwoIndex,
            "Weapon, hair, skin, coat avatar and ordinary coat equip independently by their original slots");
    auto equippedAppearance = progression.appearance(pvf);
    require(equippedAppearance.parts.at("[weapon]").variation == std::array<int, 2>{0, 7} &&
            equippedAppearance.parts.at("[coat avatar]").variation == std::array<int, 2>{37, 1} &&
            equippedAppearance.parts.at("[hair avatar]").variation == std::array<int, 2>{1, 0} &&
            equippedAppearance.bodyVariation() == 1,
            "Persistent equipment drives exact source weapon, outfit, hair and skin appearance variants");
    require(progression.equip(coatOneIndex).ok && !progression.equipped(coatTwoIndex) &&
            progression.equipped(coatOneIndex) && progression.appearance(pvf).parts.at("[coat avatar]").layers.size() == 1 &&
            progression.unequip(coatOneIndex).ok && !progression.equipped(coatOneIndex) &&
            progression.equipped(armorIndex) && progression.appearance(pvf).parts.at("[coat avatar]").source.path ==
                "equipment/character/swordman/avatar/coat/acoat_default.equ",
            "Avatar replacement and removal refresh appearance and restore default clothing while preserving stat armor");
    require(progression.equip(coatTwoIndex).ok, "Split coat can be equipped again after removal");
    auto beforeInvalid = progression.state;
    require(!progression.unequip(coatOneIndex).ok && !progression.equip(-1).ok &&
            progression.state == beforeInvalid, "Invalid appearance operations cannot mutate persistent inventory");

    progression.state["future_appearance_rules"] = {{"version", 7}, {"unrecognized", Json::array({1, "keep"})}};
    const auto expectedAppearance = appearanceState(progression.appearance(pvf));
    const auto expectedInventory = progression.state["inventory"];
    const auto directory = std::filesystem::path("reports/test-saves/appearance") /
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    CharacterStore store(directory);
    World world(pvf, assets);
    store.data["future_root"] = {{"kept", 29}};
    store.data["characters"][0] = {{"name", "Appearance"}, {"class", "swordman"}, {"level", 99},
                                  {"weapon", 3}, {"future_character", 23}};
    store.capture(0, world, progression);
    store.save();
    store.close();
    CharacterStore durable(directory);
    Progression restored(catalog);
    durable.apply(0, world, restored);
    require(appearanceState(restored.appearance(pvf)) == expectedAppearance &&
            restored.state["inventory"] == expectedInventory &&
            restored.state["equipped"] == progression.state["equipped"] &&
            restored.state["future_appearance_rules"] == progression.state["future_appearance_rules"] &&
            durable.data["future_root"] == store.data["future_root"] &&
            durable.data["characters"][0]["future_character"] == 23,
            "Isolated durable character save restores exact appearance and every unknown root/character/progression/item field");
    bool unchanged = true;
    for (const auto &[path, bytes] : originalBytes) unchanged = unchanged && pvf.read(path) == bytes;
    require(unchanged, "Source EQU bytes remain unchanged throughout parsing, equipment changes and save round trip");

    return {{"status", "pass"}, {"checks", checks}, {"resolved_source_images", images},
            {"saved_appearance", expectedAppearance}, {"save_directory", directory.generic_string()},
            {"scope", "source appearance data, layer ordering and persistence; visual pose parity and original body layer number are not established"}};
}
} // namespace dnf
