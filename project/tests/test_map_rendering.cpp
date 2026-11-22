#include "dnf/map_exploration.hpp"
#include "dnf/renderer.hpp"
#include <cmath>
#include <map>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
std::map<int, std::string> sourceRegistry(Pvf &pvf, const std::string &path) {
    const auto source = pvf.script(path);
    std::map<int, std::string> result;
    for (size_t i = 0; i + 1 < source.tokens.size(); ++i)
        if (source.tokens[i]["value"].is_number_integer() && source.tokens[i + 1]["value"].is_string()) {
            result[source.tokens[i]["value"].get<int>()] = normalize((std::filesystem::u8path(path).parent_path() /
                std::filesystem::u8path(source.tokens[i + 1]["value"].get<std::string>())).generic_u8string());
            ++i;
        }
    return result;
}
}
Json runMapRenderingTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), coverage = Json::array(), sourceExamples = Json::array();
    const auto check = [&](bool ok, const std::string &name) {
        if (!ok) throw std::runtime_error("MAP rendering: " + name);
        checks.push_back(name);
    };
    const auto mapsById = sourceRegistry(pvf, "map/map.lst");
    const auto dungeonsById = sourceRegistry(pvf, "dungeon/dungeon.lst");
    const auto sky = pvf.script("worldmap/skycastle.wdm");
    const auto skyValues = sky.values("[dungeon]");
    std::set<int> priorityDungeons{2};
    for (size_t i = 0; i + 1 < skyValues.size(); i += 2) priorityDungeons.insert(skyValues[i].get<int>());
    check(priorityDungeons == std::set<int>({2, 11, 12, 13, 14, 15, 17}) &&
          pvf.script(dungeonsById.at(2)).text("[name]") == "洛兰深处",
          "Priority area is source WDM Sky Castle's six dungeons plus the source Lorien Inside dungeon");
    MapAccessCatalog access(pvf);
    RegionCatalog region(pvf, assets);
    World world(pvf, assets, WorldRules::BetaFoundationV1);
    const auto worldBefore = world.snapshot(), simulationBefore = world.simulationCheckpoint(), eventsBefore = world.eventLog();
    const auto prepare = [&](const std::string &path, bool town) {
        const auto indices = access.findByPath(path);
        if (indices.empty()) throw std::runtime_error("Missing priority source map: " + path);
        return town ? prepareTownMapTraversal(pvf, assets, world, region, access.at(indices.front())) :
                      prepareMapExploration(pvf, assets, world, region, access.at(indices.front()), true);
    };
    std::map<std::string, int> priority;
    priority.emplace("map/elvengard/elvengard.map", 0);
    std::map<int, size_t> registeredCounts;
    for (const auto &[id, path] : mapsById) {
        if (!pvf.has(path)) continue;
        const auto source = pvf.script(path);
        for (const auto &value : source.values("[dungeon]"))
            if (value.is_number_integer() && priorityDungeons.count(value.get<int>())) {
                priority.emplace(path, value.get<int>()); ++registeredCounts[value.get<int>()]; break;
            }
    }
    check(registeredCounts == std::map<int, size_t>({{2, 19}, {11, 20}, {12, 21}, {13, 16}, {14, 17}, {15, 21}, {17, 9}}),
          "The priority audit includes all 123 registered dungeon maps, a superset of legal topology candidates");
    const std::array<std::array<int, 2>, 5> sizes{{{{800, 600}}, {{1280, 720}}, {{1920, 1080}}, {{2560, 720}}, {{801, 601}}}};
    for (const auto &[path, dungeon] : priority) {
        const auto prepared = prepare(path, dungeon == 0);
        const auto &scene = prepared.scene;
        check(prepared.ok && !scene.sourceTileVisuals.empty() && scene.sourceTileVisuals.size() == scene.tiles.size(),
              "Every priority source MAP publishes its real tile visuals: " + path);
        const auto before = sceneDrawCommands(scene, false), after = sceneDrawCommands(scene, true);
        size_t tileCount = 0;
        std::set<size_t> drawn;
        for (const auto &command : before) {
            if (command.kind == MapDrawCommand::Kind::Tile) ++tileCount;
            else check(drawn.insert(command.index).second, "Fixed layer drawn once before actors: " + path);
        }
        for (const auto &command : after)
            check(command.kind == MapDrawCommand::Kind::Animation && drawn.insert(command.index).second,
                  "Foreground contains no tile and never redraws a fixed layer: " + path);
        check(tileCount == scene.tiles.size(), "Each priority source tile is drawn exactly once: " + path);
        for (size_t i = 0; i < scene.layers.size(); ++i) {
            const auto &layer = scene.layers[i];
            check(drawn.count(i) == size_t(layer.background || layer.order != 0),
                  "Each fixed source layer is in the actual render plan; Y-layer stays with actors: " + path);
        }
        Json bounds = Json::array();
        for (const auto &size : sizes) {
            const auto view = sceneViewport(size[0], size[1], scene);
            for (const double x : {-10000.0, scene.width / 2.0, scene.width + 10000.0})
                for (const double y : {-10000.0, 10000.0}) {
                    const auto camera = sceneCamera(scene, view, x, y);
                    check(camera.sourceFloorCovered && camera.x >= 0 &&
                          camera.x + view.width <= sceneVisualWidth(scene) + 1e-7 &&
                          camera.sourceFloorBottom - camera.scrollY + 1e-7 >= view.gameplayBottom,
                          "Priority source floor remains bounded at both camera extremes after resize: " + path);
                }
            bounds.push_back(sceneCameraDiagnostics(scene, size[0], size[1], prepared.playerSpawn[0], 10000));
        }
        coverage.push_back({{"map", path}, {"dungeon", dungeon}, {"registered_source", true},
            {"special_room", scene.script.values("[greed]").empty()}, {"visual_bounds", bounds},
            {"diagnostics", prepared.diagnostics},
            {"scope", "all registered source maps, including special rooms; not a grant of ordinary topology admission"}});
        check(scene.script.rawBytes == pvf.read(path), "Priority map rendering leaves original member bytes unchanged: " + path);
    }
    // The annotated sample says close/below precedes tiles, close/upper follows
    // close objects/ANI. The old consumer painted both behind the floor.
    const auto fire = prepare("map/conflagration/17300s.map", false);
    const auto fog = prepare("map/astraythief/b6201.map", false);
    const auto ocean = prepare("map/ocean/b2601.map", false);
    const auto findBackground = [&](const Scene &scene, const std::string &filename) -> MapLayer {
        for (const auto &layer : scene.layers) if (layer.background && layer.animation == filename) return layer;
        throw std::runtime_error("Source background missing from runtime: " + filename);
    };
    const auto fireLayer = findBackground(fire.scene, "map/conflagration/animation/firecurtain01.ani");
    const auto fogLayer = findBackground(fog.scene, "map/commonanimation/fogmild.ani");
    const auto oceanLayer = findBackground(ocean.scene, "passiveobject/mapobject/particlefactory/animation/oceangradationbottom.ani");
    check(fire.ok && fireLayer.sourceLayer == "[close]" && fireLayer.sourceOrder == "[upper]" &&
          fireLayer.order == 101 && fireLayer.screenPosition && fireLayer.x == 0 && fireLayer.y == 80,
          "Real 1031 FireCurtain retains close/upper and its exact screen-position source binding");
    check(fog.ok && std::abs(fogLayer.scroll - 1.1) < 1e-9 &&
          std::abs(backgroundOrigin(fogLayer, 100, -120)[0] + 110) < 1e-9,
          "Real 1031 close fog consumes near sight 110 percent rather than middle sight 90 percent");
    check(ocean.ok && oceanLayer.sourceOrder == "upper" && oceanLayer.order == 101 &&
          mapBackgroundUpper("upper") && mapBackgroundUpper("[upper]") && !mapBackgroundUpper("[below]"),
          "Actual Ocean unbracketed upper is consumed while its source literal remains intact");
    Scene order; order.tiles.emplace_back("unused", 0, 0, 80);
    MapLayer far; far.sourceLayer = "[distantback]"; far.sourceOrder = "[upper]"; far.background = true;
    configureMapBackground(far, fire.scene.script);
    MapLayer farAni; farAni.sourceLayer = "[distantback]"; farAni.order = mapLayerOrder(farAni.sourceLayer);
    MapLayer closeAni; closeAni.sourceLayer = "[close]"; closeAni.order = mapLayerOrder(closeAni.sourceLayer);
    MapLayer below = fireLayer; below.sourceOrder = "[below]"; configureMapBackground(below, fire.scene.script);
    order.layers = {fireLayer, far, closeAni, below, farAni};
    const auto backPlan = sceneDrawCommands(order, false), frontPlan = sceneDrawCommands(order, true);
    check(backPlan.size() == 4 && backPlan[0].index == 4 && backPlan[1].index == 1 &&
          backPlan[2].index == 3 && backPlan[3].kind == MapDrawCommand::Kind::Tile &&
          frontPlan.size() == 2 && frontPlan[0].index == 2 && frontPlan[1].index == 0,
          "Actual renderer plan interleaves far upper with far ANI and close upper after close ANI; close below precedes tiles");

    const char *driver = SDL_getenv("SDL_VIDEODRIVER");
    if (!driver || std::string(driver) != "dummy") throw std::runtime_error("MAP renderer test requires SDL dummy");
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) throw std::runtime_error(SDL_GetError());
    struct VideoGuard { ~VideoGuard() { SDL_QuitSubSystem(SDL_INIT_VIDEO); } } video;
    RendererOptions options; options.shown = false; options.vsync = false;
    Renderer render(assets, options);
    Scene overlay; overlay.layers = {fireLayer};
    render.begin(); render.viewport();
    overlay.draw(render, 0, 500, false, -120);
    render.rect(0, 0, 800, 600, {20, 30, 40, 255});
    Bytes pixelsBefore(800 * 600 * 4), pixelsAfter(pixelsBefore.size());
    check(SDL_RenderReadPixels(render.raw(), nullptr, SDL_PIXELFORMAT_RGBA32, pixelsBefore.data(), 800 * 4) == 0,
          "Read actual SDL dummy actor-plane color before the foreground pass");
    overlay.draw(render, 0, 500, true, -120);
    check(SDL_RenderReadPixels(render.raw(), nullptr, SDL_PIXELFORMAT_RGBA32, pixelsAfter.data(), 800 * 4) == 0 &&
          pixelsBefore != pixelsAfter && render.errors.empty(),
          "Actual Scene::draw renders original FireCurtain pixels over the actor plane in the foreground pass");
    check(world.snapshot() == worldBefore && world.simulationCheckpoint() == simulationBefore && world.eventLog() == eventsBefore,
          "Priority source preparation and dummy rendering do not change World time, RNG, rewards, attacks or input");
    for (const auto *prepared : {&fire, &fog, &ocean}) sourceExamples.push_back(prepared->json());
    return {{"status", "pass"}, {"count", checks.size()}, {"checks", checks}, {"priority_maps", coverage},
        {"source_examples", sourceExamples}, {"frontend_started", false},
        {"scope", "source-backed fixed-layer draw plan, real dummy foreground pixels and all priority registered map bounds; user visual/native comparison pending"}};
}
} // namespace dnf
