#include "dnf/scene_camera.hpp"
#include "dnf/scene.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
constexpr double referenceHeight = 600, referenceGameplayBottom = 557;
constexpr double foregroundOffset = 120, referencePlayerY = 360;
bool finite(double n) { return std::isfinite(n); }
}

SourceTileVisual sourceTileVisual(const std::string &source, const std::string &image,
                                 int frame, double x, double y, const Pixels &p) {
    const int w = p.logicalWidth > 0 ? p.logicalWidth : p.width;
    const int h = p.logicalHeight > 0 ? p.logicalHeight : p.height;
    if (!finite(x) || !finite(y) || w <= 0 || h <= 0 || p.width < 0 || p.height < 0)
        throw std::invalid_argument("Invalid source tile visual dimensions");
    return {source, image, frame, {x, y, double(w), double(h)},
            {x + p.x, y + p.y, double(p.width), double(p.height)},
            !image.empty() && p.width > 0 && p.height > 0};
}

SceneViewport sceneViewport(int w, int h, double mapWidth) {
    if (w <= 0 || h <= 0 || !finite(mapWidth) || mapWidth < 0)
        throw std::invalid_argument("Invalid scene viewport dimensions");
    const double scale = std::max(h / referenceHeight, mapWidth > 0 ? w / mapWidth : 0.0);
    const double width = mapWidth > 0 ? std::min(w / scale, mapWidth) : w / scale;
    return {w, h, scale, width, h / scale, h / scale * referenceGameplayBottom / referenceHeight};
}

double sceneVisualWidth(const Scene &scene) {
    double right = 0;
    for (const auto &tile : scene.sourceTileVisuals)
        if (tile.drawable) right = std::max(right, tile.logical[0] + tile.logical[2]);
    // Missing source cover remains explicitly uncertified by sceneCamera.
    return right > 0 ? right : std::max(0, scene.width);
}

SceneViewport sceneViewport(int w, int h, const Scene &scene) {
    return sceneViewport(w, h, sceneVisualWidth(scene));
}

SceneCameraFrame sceneCamera(const Scene &scene, const SceneViewport &view, double px, double py) {
    if (!finite(px) || !finite(py) || !finite(view.width) || !finite(view.height) ||
        view.width <= 0 || view.height <= 0 || view.gameplayBottom <= 0)
        throw std::invalid_argument("Invalid scene camera input");
    SceneCameraFrame out;
    out.x = std::clamp(px - view.width / 2, 0.0, std::max(0.0, sceneVisualWidth(scene) - view.width));
    // Cut the actual visible X span at every authored column boundary. Use
    // logical X coverage (IMG crop is intentionally transparent in many tiles)
    // but the actual image bottom in Y; never substitute a maximum from a
    // different/taller column for the visible shorter column.
    const double right = out.x + view.width;
    std::vector<double> cuts{out.x, right};
    for (const auto &t : scene.sourceTileVisuals) {
        if (!t.drawable) continue;
        for (double x : {t.logical[0], t.logical[0] + t.logical[2]})
            if (x > out.x && x < right) cuts.push_back(x);
    }
    std::sort(cuts.begin(), cuts.end());
    cuts.erase(std::unique(cuts.begin(), cuts.end()), cuts.end());
    double bottom = std::numeric_limits<double>::infinity();
    double groundTop = -bottom;
    double logicalTop = std::numeric_limits<double>::infinity(), logicalBottom = -logicalTop;
    bool covered = !scene.sourceTileVisuals.empty();
    for (size_t i = 1; i < cuts.size(); ++i) {
        const double x = (cuts[i - 1] + cuts[i]) / 2;
        std::vector<std::array<double, 2>> intervals;
        for (const auto &t : scene.sourceTileVisuals)
            if (t.drawable && x >= t.logical[0] && x < t.logical[0] + t.logical[2]) {
                intervals.push_back({t.pixels[1], t.pixels[1] + t.pixels[3]});
                logicalTop = std::min(logicalTop, t.logical[1]);
                logicalBottom = std::max(logicalBottom, t.logical[1] + t.logical[3]);
            }
        if (intervals.empty()) { covered = false; break; }
        std::sort(intervals.begin(), intervals.end());
        const double columnTop = intervals.front()[0];
        double columnBottom = intervals.front()[1];
        for (size_t n = 1; n < intervals.size(); ++n) {
            if (intervals[n][0] > columnBottom + 1e-9) {
                out.sourceVisualGap = true;
                break; // A later row cannot certify a missing intervening row.
            }
            columnBottom = std::max(columnBottom, intervals[n][1]);
        }
        groundTop = std::max(groundTop, columnTop);
        bottom = std::min(bottom, columnBottom);
    }
    const double base = referenceGameplayBottom - view.gameplayBottom;
    if (!covered || !finite(bottom) || groundTop >= bottom) {
        double low = std::numeric_limits<double>::infinity(), high = -low;
        for (const auto &r : scene.walkRects) {
            low = std::min(low, r[1]); high = std::max(high, r[1] + r[3]);
        }
        const double target = referencePlayerY * view.gameplayBottom / referenceGameplayBottom;
        out.minimumScrollY = finite(low) ? std::min(base, low + foregroundOffset - target) : base;
        out.maximumScrollY = finite(high) ? std::max(base, high + foregroundOffset - target) : base;
        out.followsY = finite(low) && high - low > 200;
        out.scrollY = out.followsY ? std::clamp(py + foregroundOffset - target, out.minimumScrollY, out.maximumScrollY) : base;
        out.y = out.scrollY - foregroundOffset;
        out.diagnostic = "source_tile_visual_cover_unavailable; walk-bounded observation only, no no-border guarantee";
        return out;
    }
    out.sourceFloorCovered = true;
    out.sourceFloorTop = groundTop;
    out.sourceFloorBottom = bottom;
    out.maximumScrollY = bottom - view.gameplayBottom;
    out.minimumScrollY = std::min(base, out.maximumScrollY);
    // A normal 480-line source canvas remains fixed. Extended/taller source
    // space may scroll only inside its real visible-column bottom boundary.
    out.followsY = logicalBottom - logicalTop > 480.0 + 1e-9 &&
                   out.maximumScrollY > out.minimumScrollY + 1e-9;
    const double target = referencePlayerY * view.gameplayBottom / referenceGameplayBottom;
    out.scrollY = out.followsY ? std::clamp(py + foregroundOffset - target,
                                           out.minimumScrollY, out.maximumScrollY)
                               : out.minimumScrollY;
    out.y = out.scrollY - foregroundOffset;
    if (out.sourceVisualGap)
        out.diagnostic = "source_tile_visual_column_gap; camera restricted to first continuous IMG-rectangle segment";
    else if (bottom < referenceGameplayBottom)
        out.diagnostic = "short_source_floor_bottom_aligned; camera reconstruction, native parity pending";
    if (groundTop - out.scrollY > view.gameplayBottom) {
        out.sourceFloorCovered = false;
        out.diagnostic = "source_tile_visual_floor_below_view; source imagery cannot certify current scene coverage";
    }
    return out;
}

Json sceneCameraDiagnostics(const Scene &scene, int w, int h, double x, double y) {
    const auto view = sceneViewport(w, h, scene);
    const auto camera = sceneCamera(scene, view, x, y);
    Json tiles = Json::array();
    for (const auto &t : scene.sourceTileVisuals)
        tiles.push_back({{"source", t.source}, {"image", t.image}, {"frame", t.frame},
                         {"logical", t.logical}, {"pixels", t.pixels}, {"drawable", t.drawable}});
    return {{"policy", "source-column-bounds-scene-camera-v1"}, {"classification", "source dimensions with explicit camera reconstruction"},
            {"map", scene.path}, {"source_background_origin", scene.bg}, {"simulation_map_width", scene.width},
            {"source_visual_width", sceneVisualWidth(scene)},
            {"output", {w, h}}, {"scene_scale", view.scale}, {"logical_view", {view.width, view.height}},
            {"gameplay_bottom", view.gameplayBottom}, {"camera", {camera.x, camera.y}},
            {"scroll_y", camera.scrollY}, {"scroll_y_bounds", {camera.minimumScrollY, camera.maximumScrollY}},
            {"follows_y", camera.followsY}, {"source_floor_covered", camera.sourceFloorCovered},
            {"source_floor_top", camera.sourceFloorTop}, {"source_floor_bottom", camera.sourceFloorBottom},
            {"source_visual_gap", camera.sourceVisualGap}, {"diagnostic", camera.diagnostic},
            {"cover_contract", "first continuous IMG-rectangle segment over visible logical columns; no opaque-pixel or whole-scene visual guarantee"},
            {"tiles", tiles}, {"native_dynamic_parity", "pending user comparison"}};
}

std::array<double, 2> scenePointFromUi(const SceneViewport &view, const SceneCameraFrame &camera,
                                     double x, double y) {
    const double uiScale = std::min(view.outputWidth / 800.0, view.outputHeight / 600.0);
    return {(x * uiScale + (view.outputWidth - 800 * uiScale) / 2) / view.scale + camera.x,
            (y * uiScale + (view.outputHeight - 600 * uiScale) / 2) / view.scale + camera.y};
}

std::vector<double> backgroundRepeatOrigins(double origin, double period, double length,
                                            bool repeat, bool downwardOnly) {
    if (!finite(origin) || !finite(period) || !finite(length) || length <= 0)
        throw std::invalid_argument("Invalid background repeat extent");
    if (!repeat || period <= 0) return {origin};
    // Modulo keeps large source origins and either camera direction bounded.
    // Y rows retain source row >= 0: the source requests repetition downward.
    const double first = downwardOnly ? std::max(0.0, std::floor(-origin / period) - 1)
                                     : std::floor(-origin / period) - 1;
    const double end = std::ceil((length - origin) / period) + 1;
    if (end - first > 100000) throw std::runtime_error("Background repeat budget exceeded");
    std::vector<double> result;
    for (double i = first; i <= end; ++i) result.push_back(origin + i * period);
    return result;
}

std::array<double, 2> backgroundOrigin(const MapLayer &l, double cameraX, double cameraY) {
    if (l.screenPosition) return {l.x, l.y};
    const double scroll = cameraY + foregroundOffset;
    // Vertical use of authored scroll percentages is an explicit reconstruction.
    // At the known fixed projection this is exactly the historical origin.
    // Never move the finite source's top downward and expose an upper border.
    return {l.x - cameraX * l.scroll, std::min(l.y, l.y - scroll * l.scroll)};
}
} // namespace dnf
