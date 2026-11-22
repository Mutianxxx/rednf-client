#include "dnf/scene_camera.hpp"
#include "dnf/map_exploration.hpp"
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
bool near(double a, double b) { return std::abs(a - b) < 1e-7; }
}
Json runSceneCameraTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), examples = Json::array();
    const auto check = [&](bool ok, const std::string &name) {
        if (!ok) throw std::runtime_error("Scene camera: " + name);
        checks.push_back(name);
    };
    const auto rejects = [](auto action) { try { action(); } catch (const std::exception &) { return true; } return false; };
    MapAccessCatalog maps(pvf);
    RegionCatalog region(pvf, assets);
    World world(pvf, assets, WorldRules::BetaFoundationV1);
    const auto worldBefore = world.snapshot(), simulationBefore = world.simulationCheckpoint(), eventsBefore = world.eventLog();
    const auto prepare = [&](const std::string &path, bool town) {
        const auto indices = maps.findByPath(path);
        if (indices.empty()) throw std::runtime_error("Missing source camera MAP: " + path);
        return town ? prepareTownMapTraversal(pvf, assets, world, region, maps.at(indices.front()))
                    : prepareMapExploration(pvf, assets, world, region, maps.at(indices.front()), true);
    };
    const std::array<std::array<int, 2>, 9> sizes{{{{800, 600}}, {{640, 480}}, {{1024, 768}},
        {{1280, 720}}, {{1920, 1080}}, {{2560, 720}}, {{640, 1080}}, {{801, 601}}, {{320, 200}}}};
    for (const auto &path : {"map/elvengard/elvengard.map", "map/hendonmyre/hendon_city.map"}) {
        const auto prepared = prepare(path, true);
        const auto &scene = prepared.scene;
        check(prepared.ok && scene.bg == 80 && scene.sourceTileVisuals.size() == scene.tiles.size() && !scene.tiles.empty(),
              "Actual source town records every drawable tile and exact MAP background origin: " + std::string(path));
        const auto sourceBytes = scene.script.rawBytes;
        const auto walkBefore = scene.walkRects;
        for (size_t i = 0; i < scene.tiles.size(); ++i) {
            const auto &tile = scene.tiles[i]; const auto &record = scene.sourceTileVisuals[i];
            const auto p = assets.pixels(std::get<0>(tile), std::get<1>(tile));
            check(record.logical == std::array<double, 4>{std::get<2>(tile), std::get<3>(tile), double(p.logicalWidth), double(p.logicalHeight)} &&
                  record.pixels == std::array<double, 4>{std::get<2>(tile) + p.x, std::get<3>(tile) + p.y, double(p.width), double(p.height)} &&
                  !record.source.empty() && record.image == std::get<0>(tile),
                  "Source logical canvas, IMG crop and placement remain independent: " + std::string(path) + ":" + std::to_string(i));
        }
        const auto reference = sceneViewport(800, 600, scene);
        const auto top = sceneCamera(scene, reference, scene.width / 2, -1000000);
        const auto bottom = sceneCamera(scene, reference, scene.width / 2, 1000000);
        check(top.sourceFloorCovered && !top.followsY && top.y == -120 && bottom.y == -120 &&
              top.sourceFloorBottom == 560 && reference.gameplayBottom == 557,
              "Elvengard reference and same-height Hendon keep exact fixed 800x600 projection across all Y: " + std::string(path));
        for (const auto &size : sizes) {
            const auto view = sceneViewport(size[0], size[1], scene);
            for (double x : {-1000.0, scene.width / 2.0, scene.width + 1000.0}) {
                const auto camera = sceneCamera(scene, view, x, 50000);
                check(view.width <= scene.width + 1e-7 && near(view.width * view.scale, size[0]) &&
                      near(view.height * view.scale, size[1]) && camera.x >= 0 &&
                      camera.x + view.width <= scene.width + 1e-7 && camera.sourceFloorCovered &&
                      camera.sourceFloorBottom - camera.scrollY + 1e-7 >= view.gameplayBottom,
                      "Resized source town stays inside both horizontal edges and actual floor bottom: " + std::string(path) + ":" + std::to_string(size[0]) + "x" + std::to_string(size[1]));
                const double sourceX = camera.x + view.width * .4, sourceY = camera.y + view.height * .6;
                const double uiScale = std::min(size[0] / 800.0, size[1] / 600.0);
                const double uiX = ((sourceX - camera.x) * view.scale - (size[0] - 800 * uiScale) / 2) / uiScale;
                const double uiY = ((sourceY - camera.y) * view.scale - (size[1] - 600 * uiScale) / 2) / uiScale;
                const auto point = scenePointFromUi(view, camera, uiX, uiY);
                check(near(point[0], sourceX) && near(point[1], sourceY),
                      "Actual camera and UI inverse share the resized viewport for NPC picking: " + std::string(path));
            }
        }
        check(scene.walkRects == walkBefore && scene.script.rawBytes == sourceBytes,
              "Camera/resize never changes authored source bytes or walk union: " + std::string(path));
        examples.push_back(sceneCameraDiagnostics(scene, 800, 600, prepared.playerSpawn[0], prepared.playerSpawn[1]));
        // Loading the established legacy entry and prepared town uses the same
        // visual metadata/consumer; this guards a disconnected helper-only fix.
        if (std::string(path) == "map/elvengard/elvengard.map") {
            Scene legacy; legacy.load(pvf, assets, path);
            const auto oldCamera = sceneCamera(legacy, reference, 800, 400);
            check(oldCamera.y == -120 && oldCamera.sourceFloorCovered && legacy.sourceTileVisuals.size() == scene.sourceTileVisuals.size(),
                  "Normal Scene::load and prepared town both feed the shared camera consumer");
        }
    }
    const auto tall = prepare("map/golemtower/(4,2)2016.map", false);
    check(tall.ok && !tall.scene.sourceTileVisuals.empty() && tall.scene.sourceTileVisuals.size() == tall.scene.tiles.size(),
          "Actual extended Sky Tower source publishes every basic and extended visual rectangle");
    for (const auto &size : sizes) {
        const auto view = sceneViewport(size[0], size[1], tall.scene);
        const auto top = sceneCamera(tall.scene, view, tall.scene.width / 2, -1000000);
        const auto bottom = sceneCamera(tall.scene, view, tall.scene.width / 2, 1000000);
        const auto middle = sceneCamera(tall.scene, view, tall.scene.width / 2, 600);
        check(top.sourceFloorCovered && top.followsY && bottom.scrollY > top.scrollY &&
              near(top.scrollY, top.minimumScrollY) && near(bottom.scrollY, bottom.maximumScrollY) &&
              near(bottom.sourceFloorBottom - bottom.scrollY, view.gameplayBottom) &&
              middle.scrollY >= top.scrollY && middle.scrollY <= bottom.scrollY,
              "Actual tall MAP follows Y and clamps both extremes using current resized visible source columns: " + std::to_string(size[0]) + "x" + std::to_string(size[1]));
    }
    examples.push_back(sceneCameraDiagnostics(tall.scene, 1280, 720, tall.playerSpawn[0], 99999));
    const auto resizeBack = sceneCamera(tall.scene, sceneViewport(800, 600, tall.scene), 500, 610);
    for (const auto &size : sizes) (void)sceneCamera(tall.scene, sceneViewport(size[0], size[1], tall.scene), 500, 610);
    const auto afterResize = sceneCamera(tall.scene, sceneViewport(800, 600, tall.scene), 500, 610);
    check(resizeBack.x == afterResize.x && resizeBack.y == afterResize.y &&
          resizeBack.maximumScrollY == afterResize.maximumScrollY,
          "Switching resolution repeatedly has no stale camera-bound or cumulative offset state");

    // Independent edge fixture: a maximum over all source columns would
    // incorrectly allow the shorter visible right column to reveal the clear.
    Scene ragged; ragged.width = 896;
    Pixels p; p.width = p.logicalWidth = 448; p.height = p.logicalHeight = 480;
    ragged.sourceTileVisuals.push_back(sourceTileVisual("left", "left.img", 0, 0, 80, p));
    ragged.sourceTileVisuals.push_back(sourceTileVisual("right", "right.img", 0, 448, 80, p));
    p.height = p.logicalHeight = 360;
    ragged.sourceTileVisuals.push_back(sourceTileVisual("extended-left", "left-ex.img", 0, 0, 560, p));
    const auto narrow = sceneViewport(448, 600, ragged.width);
    const auto left = sceneCamera(ragged, narrow, 224, 99999);
    const auto right = sceneCamera(ragged, narrow, 672, 99999);
    const auto straddle = sceneCamera(ragged, sceneViewport(800, 600, ragged.width), 448, 99999);
    check(left.sourceFloorBottom == 920 && right.sourceFloorBottom == 560 && straddle.sourceFloorBottom == 560 &&
          straddle.scrollY <= 3 && right.y == -120,
          "Camera clips to minimum visible-column floor instead of borrowing height from a different column");
    ragged.width += 12; // Existing collision-radius padding is deliberately preserved.
    for (const auto &size : sizes) {
        const auto view = sceneViewport(size[0], size[1], ragged);
        const auto camera = sceneCamera(ragged, view, 99999, 99999);
        check(sceneVisualWidth(ragged) == 896 && ragged.width == 908 &&
              camera.x + view.width <= 896 + 1e-7 && camera.sourceFloorCovered,
              "Collision padding cannot expose pixels beyond authored tile columns at a resized right edge");
    }
    Scene gapped; gapped.width = 896;
    p.height = p.logicalHeight = 480;
    gapped.sourceTileVisuals.push_back(sourceTileVisual("basic", "basic.img", 0, 0, 80, p));
    p.height = p.logicalHeight = 120;
    gapped.sourceTileVisuals.push_back(sourceTileVisual("first-extension", "first.img", 0, 0, 560, p));
    // The absent680..800row must not be borrowed from the later800..920row.
    gapped.sourceTileVisuals.push_back(sourceTileVisual("late-extension", "late.img", 0, 0, 800, p));
    const auto gap = sceneCamera(gapped, narrow, 224, 99999);
    check(gap.sourceVisualGap && gap.sourceFloorCovered && gap.sourceFloorTop == 80 && gap.sourceFloorBottom == 680 &&
          gap.scrollY <= 123 && gap.diagnostic.find("source_tile_visual_column_gap") != std::string::npos,
          "Missing middle extended row restricts camera to the first continuous source image segment and diagnoses the gap");
    Scene missing; missing.width = 896; missing.walkRects = {{0, 400, 896, 900}};
    const auto unknown = sceneCamera(missing, sceneViewport(800, 600, missing.width), 300, 900);
    check(!unknown.sourceFloorCovered && unknown.followsY && !unknown.diagnostic.empty() && unknown.scrollY >= unknown.minimumScrollY &&
          unknown.scrollY <= unknown.maximumScrollY && missing.sourceTileVisuals.empty(),
          "Missing source dimensions retain bounded observation and an explicit no-coverage diagnostic without fabricating tiles");
    const auto storm = prepare("map/stormpass/stormpass.map", true);
    const auto stormReport = sceneCameraDiagnostics(storm.scene, 800, 600, storm.playerSpawn[0], storm.playerSpawn[1]);
    size_t transparentBasic = 0;
    bool transparentEvidence = true, onlyRealImages = true, inferredBlankDiagnostic = false;
    for (const auto &record : storm.records) if (record.value("kind", std::string()) == "tile") {
        const auto &grid = record.at("grid");
        if (!grid.at("transparent").get<bool>()) continue;
        ++transparentBasic;
        transparentEvidence = transparentEvidence && grid.at("image") == "" &&
            grid.at("dimension_policy") == "inferred-empty-basic-row-height-from-local-extended-grid-v1" &&
            !grid.at("dimension_evidence").empty() &&
            grid.at("pass_values") == pvf.script(record.at("resolved")).values("[pass type]");
        for (const auto &visual : storm.scene.sourceTileVisuals)
            onlyRealImages = onlyRealImages && visual.source != record.at("resolved");
    }
    for (const auto &visual : storm.scene.sourceTileVisuals) onlyRealImages = onlyRealImages && !visual.image.empty();
    for (const auto &diagnostic : storm.diagnostics)
        inferredBlankDiagnostic = inferredBlankDiagnostic || diagnostic.value("kind", std::string()) == "transparent_tile_dimensions_inferred";
    check(storm.ok && transparentBasic == storm.scene.script.values("[tile]").size() && transparentBasic > 0 &&
          transparentEvidence && inferredBlankDiagnostic && onlyRealImages,
          "Actual Stormpass transparent basics retain source pass values and explicitly inferred local-extended dimensions without fabricating imagery");
    check(stormReport.at("source_floor_covered").get<bool>() &&
          stormReport.at("source_floor_bottom").get<double>() - stormReport.at("scroll_y").get<double>() >=
              stormReport.at("gameplay_bottom").get<double>() &&
          storm.scene.sourceTileVisuals.size() == storm.scene.tiles.size(),
          "Actual Stormpass now bounds its camera using loaded real extended IMG rectangles; transparent basics are excluded from visual coverage");
    examples.push_back(stormReport);

    MapLayer layer; layer.x = 37; layer.y = 80; layer.scroll = .5;
    const auto baseline = backgroundOrigin(layer, 120, -120);
    const auto moved = backgroundOrigin(layer, 120, 180);
    const auto topClipped = backgroundOrigin(layer, 120, -200);
    check(baseline == std::array<double, 2>{-23, 80} && moved == std::array<double, 2>{-23, -70} && topClipped[1] == 80,
          "Background uses the bounded camera delta and source scroll while retaining the reference origin and top edge");
    layer.screenPosition = true;
    check(backgroundOrigin(layer, 5000, 3000) == std::array<double, 2>{37, 80},
          "Explicit source screen-position backgrounds retain their authored screen origin");
    for (double origin : {-500000.0, -641.5, 0.0, 500000.0}) {
        const auto xs = backgroundRepeatOrigins(origin, 640, 1066.67, true);
        check(!xs.empty() && xs.front() <= 0 && xs.back() >= 1066.67 && xs.size() < 10,
              "Background horizontal repetition covers either signed phase and large authored origins");
    }
    const auto rows = backgroundRepeatOrigins(-1500, 480, 600, true, true);
    check(!rows.empty() && rows.front() <= 0 && rows.back() >= 600 &&
          backgroundRepeatOrigins(80, 480, 600, false, true) == std::vector<double>{80},
          "Source loop-Y advances downward rows after scroll; nonloop layers remain a single authored image");
    check(rejects([] { sceneViewport(0, 600); }) && rejects([&] { sceneCamera(ragged, narrow, NAN, 0); }),
          "Nonfinite or empty viewport inputs fail explicitly");
    check(world.snapshot() == worldBefore && world.simulationCheckpoint() == simulationBefore && world.eventLog() == eventsBefore,
          "All source preparation, camera and resize checks leave World time, RNG, input, actors and rewards unchanged");
    return {{"checks", checks}, {"examples", examples}, {"frontend_started", false},
            {"classification", "source-coordinate and camera-logic checks; visual, audio, feel and native dynamic comparison pending user"}};
}
} // namespace dnf
