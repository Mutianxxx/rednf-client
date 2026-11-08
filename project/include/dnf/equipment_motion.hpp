#pragma once
#include "character.hpp"
#include <limits>

namespace dnf {
enum class EquipmentMotionStatus { Resolved, Empty, Unsupported };

// Source ranges, not EQU draw depths. Native semantics for other LAYER values
// have not been recovered; all ranges and the complete source remain available.
struct EquipmentMotionLayer {
    Field field;
    size_t ordinal = 0, beginField = 0, endField = 0, endOffset = 0;
    bool supported = false;
};
struct EquipmentMotionBinding {
    std::string tag, literal, path;
    Json value;
    size_t fieldOrdinal = 0, fieldOffset = 0, slot = 0, occurrence = 0;
    size_t layerOrdinal = std::numeric_limits<size_t>::max();
    EquipmentMotionStatus status = EquipmentMotionStatus::Unsupported;
    // parseEquipmentMotionSource resolves syntax only. The PVF loader also
    // checks existence and clears path if the exact authored target is absent.
    bool existenceChecked = false, exists = false;
};
struct EquipmentMotionDefinition {
    CharacterScript source;
    std::string animationDirectory;
    std::vector<EquipmentMotionLayer> layers;
    std::vector<EquipmentMotionBinding> bindings;
    Json issues = Json::array();
};

EquipmentMotionDefinition parseEquipmentMotionSource(CharacterScript source,
    const std::string &animationDirectory);
EquipmentMotionDefinition loadEquipmentMotion(Pvf &pvf, const std::string &layPath,
    const std::string &animationDirectory);
// Identity is CHR tag + repeated-field occurrence + original value index.
// Empty/Unsupported return their binding with an empty path; absent is nullptr.
// No filename-stem, neighboring-slot or other-layer fallback is permitted.
const EquipmentMotionBinding *resolveEquipmentMotion(const EquipmentMotionDefinition &definition,
    const CharacterResource &bodyBinding, size_t occurrence = 0);
} // namespace dnf
