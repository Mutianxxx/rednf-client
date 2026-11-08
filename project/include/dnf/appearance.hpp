#pragma once
#include "character.hpp"
#include <map>
namespace dnf {
struct EquipmentMotionDefinition;
struct AppearanceBodyMotion {
    CharacterResource resource;
    size_t occurrence = 0;
};
// Source EQU layer numbers are independent from world Y sorting. The original
// ordered fields remain in AppearancePart::source, including other job blocks.
struct AppearanceLayer {
    int order = 0;
    std::array<int, 2> variation{0, 0};
    std::string slot, sourcePath, name, animationScript, animationDirectory;
    size_t sourceOffset = 0;
    std::shared_ptr<const EquipmentMotionDefinition> motionDefinition;
};
struct AppearancePart {
    std::string slot, job = "[swordman]";
    std::array<int, 2> variation{0, 0};
    std::vector<AppearanceLayer> layers;
    std::vector<std::string> hideEquipment;
    std::vector<int> hideLayers;
    Script source;
};
struct CharacterAppearance {
    CharacterIdentity identity;
    std::string job;
    std::vector<AppearanceBodyMotion> bodyMotions;
    Json issues = Json::array();
    std::map<std::string, AppearancePart> parts;
    // Body=1000 is a reconstruction convention; EQU supplies clothing/weapon
    // numbers but this client's CHR does not expose the native body's number.
    int bodyOrder = 1000;
    std::vector<AppearanceLayer> orderedLayers() const;
    int bodyVariation() const;
};
AppearancePart parseEquipmentAppearance(const Script &source, const std::string &job = "[swordman]");
// Returns false for ordinary armor with no authored appearance. It never removes
// a costume simply because the armor occupies the corresponding stat slot.
bool applyEquipmentAppearance(CharacterAppearance &appearance, const Script &source,
                              const std::string &job = "[swordman]");
CharacterAppearance defaultCharacterAppearance(Pvf &pvf, const CharacterCatalog &catalog,
                                               CharacterIdentity identity);
// Binds exact EQU LAY sources after inventory overlays; never guesses ANI names.
void bindEquipmentMotions(Pvf &pvf, CharacterAppearance &appearance);
const AppearanceBodyMotion *appearanceBodyMotion(const CharacterAppearance &appearance,
                                                 const std::string &pathOrStem);
std::string appearanceLayerMotion(const AppearanceLayer &layer, const AppearanceBodyMotion &body);
// Existing diagnostic/save categories 0/1/2/3 mean source subtypes 0/1/3/2.
// This adapter does not define new item content or native equipment qualification.
int legacyWeaponSubtype(int category);
CharacterAppearance diagnosticWeaponAppearance(Pvf &pvf, const CharacterCatalog &catalog,
                                               CharacterIdentity identity, int category);
// Resolve only the authored integer placeholders; unknown format tokens remain
// literal so the caller can report unsupported data rather than guessing.
std::string appearanceImage(std::string pattern, const std::array<int, 2> &variation,
                            bool body = false);
} // namespace dnf
