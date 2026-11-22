#include "dnf/character_attack.hpp"
#include <stdexcept>

namespace dnf {
CharacterAttackMotion readCharacterAttackMotion(Assets &assets, const CharacterAppearance &appearance,
                                               const std::string &bodyPath) {
    const auto *binding = appearanceBodyMotion(appearance, bodyPath);
    if (!binding) throw std::runtime_error("Attack has no source CHR motion binding");
    CharacterAttackMotion result;
    result.body = assets.animation(bodyPath);
    for (const auto &layer : appearance.orderedLayers()) if (layer.slot == "[weapon]") {
        const auto path = appearanceLayerMotion(layer, *binding);
        if (!path.empty()) result.weapons.push_back(assets.animation(path));
    }
    return result;
}
std::vector<Box> CharacterAttackMotion::boxesAt(size_t frame) const {
    if (!body || frame >= body->frames.size()) throw std::out_of_range("Source attack body pose is unavailable");
    std::vector<Box> result;
    for (const auto &box : body->frames[frame].boxes) if (box.type == 15) result.push_back(box);
    for (const auto &weapon : weapons) if (frame < weapon->frames.size())
        for (const auto &box : weapon->frames[frame].boxes) if (box.type == 15) result.push_back(box);
    return result;
}
std::vector<Box> CharacterAttackMotion::boxesAt(const ani_clock::Snapshot &clock, const std::vector<int32_t> *controllerDelays) const {
    if (!body || clock.frame >= body->frames.size()) throw std::out_of_range("Source attack clock frame unavailable");
    std::vector<Box> result;
    for (const auto &box : body->frames[clock.frame].boxes) if (box.type == 15) result.push_back(box);
    for (const auto &weapon : weapons) {
        if (weapon->frames.empty()) continue;
        const auto child = weapon->followClock(*body, clock, clock.loop,controllerDelays);
        for (const auto &box : weapon->frames[child.frame].boxes) if (box.type == 15) result.push_back(box);
    }
    return result;
}
Json CharacterAttackMotion::json() const {
    Json layers = Json::array();
    for (const auto &weapon : weapons) layers.push_back(weapon->path);
    return {{"policy", "shared-swordman-source-attack-reader-v1"},
        {"classification", "user_requested_temporary"}, {"body", body ? body->path : std::string()},
        {"weapon_layers", layers}, {"clock", "body-pose-index"},
        {"native_controller_restored", false}};
}
} // namespace dnf
