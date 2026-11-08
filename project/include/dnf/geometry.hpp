#pragma once
#include <array>
#include <cmath>

namespace dnf {
struct Point2 { double x, y; };
inline double radiansToDegrees(double radians) {
    return radians * 180.0 / 3.14159265358979323846;
}

// ANI offsets and IMG crop coordinates share the untrimmed image coordinate
// system. Apply signed scaling, rotation, and actor facing to their sum, then
// translate to the entity anchor. Never give a backend a negative rectangle.
// This is a portable rendering transform, not a change to source ANI/IMG data.
inline std::array<Point2, 4> imageQuad(double anchorX, double anchorY, double offsetX,
                                     double offsetY, double cropX, double cropY,
                                     double width, double height, int facing = 1,
                                     double scaleX = 1, double scaleY = 1,
                                     double degrees = 0) {
    const double rad = degrees * 3.14159265358979323846 / 180.0;
    const double c = std::cos(rad), s = std::sin(rad);
    std::array<Point2, 4> out;
    const Point2 uv[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    for (int i = 0; i < 4; ++i) {
        double x = (offsetX + cropX + uv[i].x * width) * scaleX;
        double y = (offsetY + cropY + uv[i].y * height) * scaleY;
        out[i] = {anchorX + facing * (x * c - y * s), anchorY + x * s + y * c};
    }
    return out;
}
} // namespace dnf
