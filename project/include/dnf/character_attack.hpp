#pragma once
#include "dnf/appearance.hpp"

namespace dnf {
// Shared Swordman-compatible reader: exact CHR -> EQU/LAY bindings, with the
// body pose index selecting weapon collision frames. This indexing policy is
// an explicit temporary inference, not each job's recovered native controller.
struct CharacterAttackMotion {
    std::shared_ptr<const Animation> body;
    std::vector<std::shared_ptr<const Animation>> weapons;
    std::vector<Box> boxesAt(size_t bodyFrame) const;
    std::vector<Box> boxesAt(const ani_clock::Snapshot &, const std::vector<int32_t> *controllerDelays = nullptr) const;
    Json json() const;
};
CharacterAttackMotion readCharacterAttackMotion(Assets &, const CharacterAppearance &,
                                               const std::string &bodyPath);
} // namespace dnf
