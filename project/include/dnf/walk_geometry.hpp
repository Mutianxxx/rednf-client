#pragma once
#include <array>
#include <vector>

namespace dnf {
// Borrowed, immutable scene geometry. Preparation can use the next scene
// without temporarily replacing the live world's collision or exploration mode.
struct WalkGeometryView {
    int width;
    const std::vector<std::array<double,4>> &walkRects;
    const std::vector<std::array<double,4>> &blockedRects;
    bool sourceUnavailable = false;
    bool canWalk(double x,double y) const;
    std::array<double,2> nearestWalkable(double x,double y) const;
};
}
