#pragma once
#include "resources.hpp"

namespace dnf {
// The source envelope is shared by several UI types. Parameter meaning belongs
// to a type adapter; a five-integer highlight is not a four-state button.
struct HudSourceControl {
    std::string type, name;
    double x = 0, y = 0;
    size_t ordinal = 0, offset = 0;
    std::vector<std::string> strings;
    std::vector<int> integers;
    Json snapshot() const;
};
struct HudSourceLayout {
    // Retain bytes, ordered tokens, repeated/unknown fields and provenance.
    Script source;
    std::vector<HudSourceControl> controls;
    const HudSourceControl &require(const std::string &name, const std::string &type,
                                    size_t stringCount, size_t integerCount) const;
    Json snapshot() const;
};
// Decodes the count-prefixed envelope only, not native UI event/ACT semantics.
// Named lookup rejects ambiguity; repeated named records stay in source order.
// Numeric anonymous IDs used by other UI files are outside this HUD adapter.
HudSourceLayout readHudSourceLayout(Script source);
} // namespace dnf
