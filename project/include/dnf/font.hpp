#pragma once
#include "resources.hpp"
#include <memory>

namespace dnf {
struct FontMask {
    int width = 0, height = 0, advance = 0;
    Bytes coverage;
};
// Optional platform rasterizer. All input remains the immutable source font;
// the caller supplies its portable unhinted fallback when unavailable.
class HintedFont {
    struct State;
    std::unique_ptr<State> state_;
  public:
    explicit HintedFont(const Bytes &font);
    ~HintedFont();
    bool available() const;
    bool mask(const std::string &utf8, int pixels, int padding, FontMask &out);
    int width(const std::string &utf8, int pixels);
};
} // namespace dnf
