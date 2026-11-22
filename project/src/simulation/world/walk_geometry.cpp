#include "dnf/walk_geometry.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
namespace dnf {
bool WalkGeometryView::canWalk(double x, double y) const {
    if(sourceUnavailable) return false;
    if (!std::isfinite(x) || !std::isfinite(y) || x < 12 || x > width - 12)
        return false;
    for (const auto &b : blockedRects)
        if (x >= b[0] && x <= b[0] + b[2] && y >= b[1] && y <= b[1] + b[3]) return false;
    if (walkRects.empty())
        return y >= 185 && y <= 340;
    for (auto &r : walkRects)
        if (x >= r[0] && x <= r[0] + r[2] && y >= r[1] && y <= r[1] + r[3]) {
            return true;
        }
    return false;
}
std::array<double, 2> WalkGeometryView::nearestWalkable(double x, double y) const {
    if(sourceUnavailable) return {x,y};
    if (canWalk(x, y)) return {x, y};
    std::array<double, 2> best{x, y};
    double distance = std::numeric_limits<double>::infinity();
    const auto ground = walkRects.empty() ? std::vector<std::array<double, 4>>{{12, 185, double(width - 24), 155}} : walkRects;
    for (const auto &r : ground) {
        double lo = std::max(12.0, r[0]), hi = std::min(double(width - 12), r[0] + r[2]);
        if (lo > hi || r[2] <= 0 || r[3] <= 0) continue;
        // Subtract closed blocker rectangles before projecting. Clamping to a
        // ground cell alone can place a spawn/NPC inside a barrel or column.
        std::vector<std::array<double, 4>> free{{lo, r[1], hi, r[1] + r[3]}};
        constexpr double clearance = 0.01;
        for (const auto &b : blockedRects) {
            std::vector<std::array<double, 4>> next;
            for (const auto &f : free) {
                const double bx0 = b[0], by0 = b[1], bx1 = b[0] + b[2], by1 = b[1] + b[3];
                if (bx1 < f[0] || bx0 > f[2] || by1 < f[1] || by0 > f[3]) { next.push_back(f); continue; }
                auto part = [&](double x0, double y0, double x1, double y1) {
                    if (x0 <= x1 && y0 <= y1) next.push_back({x0, y0, x1, y1});
                };
                part(f[0], f[1], std::min(f[2], bx0 - clearance), f[3]);
                part(std::max(f[0], bx1 + clearance), f[1], f[2], f[3]);
                const double cx0 = std::max(f[0], bx0), cx1 = std::min(f[2], bx1);
                part(cx0, f[1], cx1, std::min(f[3], by0 - clearance));
                part(cx0, std::max(f[1], by1 + clearance), cx1, f[3]);
            }
            free.swap(next);
        }
        for (const auto &f : free) {
            const double nx = std::clamp(x, f[0], f[2]), ny = std::clamp(y, f[1], f[3]);
            const double d = (nx - x) * (nx - x) + (ny - y) * (ny - y);
            if (d < distance && canWalk(nx, ny)) { best = {nx, ny}; distance = d; }
        }
    }
    return best;
}
}
