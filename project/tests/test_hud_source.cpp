#include "dnf/hud.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
Json runHudSourceTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    const auto check = [&](bool condition, const char *message) {
        if (!condition) throw std::runtime_error(std::string("HUD source: ") + message);
        checks.push_back(message);
    };
    const auto original = pvf.script("ui/hud/hud.ui");
    const auto parsed = readHudSourceLayout(original);
    const auto &menu = parsed.require("main_menu", "[button]", 1, 4);
    check(parsed.controls.size() == 12 && menu.x == 413 && menu.y == 52 && menu.offset == 417 &&
          menu.strings[0] == "interface2/HUD/HUD.img" && menu.integers == std::vector<int>({68, 69, 70, 71}),
          "Current 1031 menu decodes its exact local position, resource, four parameters and source offset");
    check(parsed.require("myinfo_button", "[highlight button]", 1, 5).integers ==
          std::vector<int>({5, 6, 7, 93, 98}), "Five highlight parameters retain their order without a four-state reinterpretation");
    const auto report = parsed.snapshot();
    check(parsed.source.rawBytes == original.rawBytes && report.at("tokens") == original.tokens &&
          report.at("provenance") == original.source && report.at("fields").size() == original.fields.size(),
          "The runtime model preserves source bytes, token types, ordering, unknown control types and provenance");
    check(parsed.require("aura_gauge_lineardodge", "[image]", 3, 1).strings[1] == "LINEARDODGE" &&
          parsed.require("newly_skill", "[animation]", 1, 1).strings[0] == "UI/HUD/Animation/hud_new.ani",
          "Unimplemented aura and new-skill animation bindings remain available as source rather than being deleted");
    const auto menuOrdinal = menu.ordinal;
    // Independent decoded-record mutations: parser behavior must follow input,
    // not a table of this particular client's coordinates or image frames.
    Script changed = original;
    changed.fields[menuOrdinal].values[2] = 123;
    changed.fields[menuOrdinal].values[3] = 34;
    changed.fields[menuOrdinal].values[5] = "fixture/alternate.img";
    changed.fields[menuOrdinal].values[7] = 314;
    const auto modified = readHudSourceLayout(changed);
    const auto &moved = modified.require("main_menu", "[button]", 1, 4);
    check(moved.x == 123 && moved.y == 34 && moved.strings[0] == "fixture/alternate.img" && moved.integers[0] == 314 &&
          parsed.require("main_menu", "[button]", 1, 4).x == 413,
          "A different source position/resource/frame is consumed while the original model stays immutable");
    const auto rejects = [&](Script source) {
        try { (void)readHudSourceLayout(std::move(source)); return false; }
        catch (const std::runtime_error &) { return true; }
    };
    for (const int invalidCount : {-1, 1000000}) {
        changed = original; changed.fields[menuOrdinal].values[4] = invalidCount;
        check(rejects(changed), "A negative or oversized string count is rejected before UI publication");
    }
    changed = original; changed.fields[menuOrdinal].values[6] = 3;
    check(rejects(changed), "A parameter count cannot silently discard an extra ordered integer");
    changed = original; changed.fields[menuOrdinal].values[7] = "68";
    check(rejects(changed), "Text that resembles an integer is not coerced into a source frame");
    changed = original; changed.fields[menuOrdinal].values[2] = std::numeric_limits<double>::infinity();
    check(rejects(changed), "A nonfinite control position never reaches renderer coordinates");
    changed = original; changed.fields.erase(changed.fields.begin() + menuOrdinal + 1);
    check(rejects(changed), "An unclosed control cannot absorb the next record");
    changed = original; changed.fields.push_back(original.fields[menuOrdinal]);
    changed.fields.push_back(original.fields[menuOrdinal + 1]);
    const auto duplicate = readHudSourceLayout(changed);
    bool ambiguous = false;
    try { (void)duplicate.require("main_menu", "[button]", 1, 4); }
    catch (const std::runtime_error &) { ambiguous = true; }
    check(ambiguous && duplicate.controls.size() == 13, "Repeated names stay lossless but a named runtime binding refuses ambiguity");

    const char *configured = SDL_getenv("SDL_VIDEODRIVER");
    if (!configured || std::string(configured) != "dummy")
        throw std::runtime_error("HUD consumer tests require SDL dummy; no frontend started");
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) throw std::runtime_error(SDL_GetError());
    struct VideoGuard { ~VideoGuard() { SDL_QuitSubSystem(SDL_INIT_VIDEO); } } video;
    if (!SDL_GetCurrentVideoDriver() || std::string(SDL_GetCurrentVideoDriver()) != "dummy")
        throw std::runtime_error("HUD consumer test refused a non-dummy video driver");
    Hud hud(pvf, assets);
    check(hud.sourceReport().at("adapter").at("menu_logical_extent") == Json::array({51, 26}) &&
          hud.systemMenuContains(413, 560) && hud.systemMenuContains(463, 585) &&
          !hud.systemMenuContains(464, 585) && !hud.systemMenuContains(413, 559),
          "The actual HUD hit test combines source local coordinates, the existing parent origin and source IMG logical extent");
    World world(pvf, assets); world.bindings.fill(-1);
    RendererOptions options; options.shown = false; options.vsync = false;
    Renderer render(assets, options);
    for (const auto size : {std::array<int, 2>{800, 600}, {1280, 720}, {1920, 1080}}) {
        render.resize(size[0], size[1]); render.begin(); render.ui();
        check(!hud.draw(render, world, 430, 570, false) && hud.draw(render, world, 430, 570, true) &&
              !hud.draw(render, world, 480, 570, true) && !hud.draw(render, world, 350, 570, true),
              "Actual source-bound HUD draw activates only the system menu and keeps other business buttons disabled");
    }
    check(render.errors.empty(), "Actual HUD source paths and chosen state frames render without missing-resource errors under SDL dummy");
    check(sha256(pvf.read("ui/hud/hud.ui")) == sha256(original.rawBytes), "HUD decode and draw leave original source member bytes unchanged");
    return {{"status", "pass"}, {"count", checks.size()}, {"checks", checks}, {"hud", hud.sourceReport()},
        {"scope", "1031 source envelope, mutation/invalid-source cases, real Hud hit testing and dummy-only drawing; no visual/native equivalence claim"}};
}
} // namespace dnf
