#pragma once
#include "resources.hpp"
#include <array>
#include <string>
#include <vector>

namespace dnf {
struct Scene;
struct MapLayer;
struct Pixels;

// Source logical canvases and IMG crop rectangles are distinct. Neither is
// collision geometry. Coordinates below use the existing MAP + background Y.
struct SourceTileVisual {
    std::string source, image;
    int frame = 0;
    std::array<double, 4> logical{0, 0, 0, 0};
    std::array<double, 4> pixels{0, 0, 0, 0};
    bool drawable = false;
};
SourceTileVisual sourceTileVisual(const std::string &source, const std::string &image,
                                 int frame, double x, double y, const Pixels &);

// Named reconstruction: preserve the established 800x600 projection and the
// existing 557px scene/footer boundary; fit a narrow authored map by changing
// the scene viewport scale. UI coordinates retain their own centred transform.
struct SceneViewport {
    int outputWidth = 800, outputHeight = 600;
    double scale = 1, width = 800, height = 600, gameplayBottom = 557;
};
SceneViewport sceneViewport(int outputWidth, int outputHeight, double sourceMapWidth = 0);
// Simulation width may include actor-radius padding beyond the final tile.
// Rendering bounds use authored columns without changing that walk boundary.
double sceneVisualWidth(const Scene &);
SceneViewport sceneViewport(int outputWidth, int outputHeight, const Scene &);

struct SceneCameraFrame {
    double x = 0, y = -120, scrollY = 0;
    double minimumScrollY = 0, maximumScrollY = 0, sourceFloorTop = 0, sourceFloorBottom = 0;
    // Geometric first continuous IMG-rectangle segment across visible authored
    // columns only. Does not certify opaque pixels, other layers or visual parity.
    bool followsY = false, sourceFloorCovered = false, sourceVisualGap = false;
    std::string diagnostic;
};
SceneCameraFrame sceneCamera(const Scene &, const SceneViewport &, double playerX, double playerY);
Json sceneCameraDiagnostics(const Scene &, int outputWidth, int outputHeight, double playerX, double playerY);
std::array<double, 2> scenePointFromUi(const SceneViewport &, const SceneCameraFrame &,
                                     double uiX, double uiY);
std::vector<double> backgroundRepeatOrigins(double origin, double period, double visibleLength,
                                            bool repeat, bool downwardOnly = false);
std::array<double, 2> backgroundOrigin(const MapLayer &, double cameraX, double cameraY);
} // namespace dnf
