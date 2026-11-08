#pragma once
#include "resources.hpp"
namespace dnf {
struct DropSprite {
    std::string image;
    int frame = 0;
    double anchorX = 0, anchorY = 0;
    std::array<double,2> drawingOrigin(double groundX,double groundY) const {
        return {groundX-anchorX,groundY-anchorY};
    }
    Json evidence = Json::object(), diagnostics = Json::array();
};
// Missing field art can use the same item's authored icon, explicitly recorded
// as a display fallback. A gold-only reward has its own source definition.
DropSprite prepareDropSprite(Assets &,const Script &item);
DropSprite prepareGoldDropSprite(Pvf &,Assets &);
} // namespace dnf
