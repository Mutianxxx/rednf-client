#pragma once
#include "resources.hpp"
#include <cmath>
namespace dnf {
// World XYZ with a minimum corner and signed source extents. No screen-space
// ANI/IMG offsets enter this volume. Native 876F47..876F95 mirrors x as -x-w.
struct CombatBox {
    double x = 0, y = 0, z = 0, w = 0, h = 0, d = 0;
};
inline CombatBox combatBox(const Box &box, double x, double y, double z, int facing) {
    return {x + (facing > 0 ? box.x : -double(box.x) - box.w), y + box.y, z + box.z,
            double(box.w), double(box.h), double(box.d)};
}
// Current 1031 helper 1090040 rejects zero input extents, then rejects strict
// separation on any axis. Nonzero boxes touching on a face/edge are contacts.
// Only the optional overlap output may therefore have a zero extent. This
// helper does not accept damage, assign teams, query armor or select hitboxes.
inline bool intersectCombatBoxes(const CombatBox &a, const CombatBox &b, CombatBox *overlap = nullptr) {
    const auto valid = [](const CombatBox &box) {
        return std::isfinite(box.x) && std::isfinite(box.y) && std::isfinite(box.z) &&
            std::isfinite(box.w) && std::isfinite(box.h) && std::isfinite(box.d) &&
            box.w != 0 && box.h != 0 && box.d != 0;
    };
    if (!valid(a) || !valid(b) || a.x + a.w < b.x || b.x + b.w < a.x ||
        a.y + a.h < b.y || b.y + b.h < a.y || a.z + a.d < b.z || b.z + b.d < a.z) return false;
    if (overlap) {
        const double x = std::max(a.x, b.x), y = std::max(a.y, b.y), z = std::max(a.z, b.z);
        *overlap = {x, y, z, std::min(a.x + a.w, b.x + b.w) - x,
                    std::min(a.y + a.h, b.y + b.h) - y, std::min(a.z + a.d, b.z + b.d) - z};
    }
    return true;
}
} // namespace dnf
