#include "dnf/entry.hpp"
#include "dnf/resources.hpp"
#include "dnf/character.hpp"
#define STBIW_WINDOWS_UTF8
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
using namespace dnf;
int run(int argc, char **argv) {
    try {
        if (argc < 4) {
            std::cout << "dnf_inspect CLIENT --script|--ani|--image|--paths|--npk-paths|--export-image|--export-frames|--characters|--skill-sources PATH [FRAME_OR_SUFFIX] [OUTPUT]\n"
                         "--npk-paths lists archive image paths containing PATH; --paths lists PVF paths.\n"
                         "--export-image writes a cropped RGBA PNG and sidecar JSON; --export-frames writes every frame plus manifest.json to OUTPUT directory.\n"
                         "Use a placeholder FRAME_OR_SUFFIX when writing --script output.\n"
                         "--characters summary|source exports all registered CHR/skill lists; source includes original bytes/tokens.\n"
                         "--skill-sources summary|source exports every registered skill with ordered mode-scoped fields; this is source evidence, not runtime coverage.\n";
            return 2;
        }
        auto root = std::filesystem::u8path(argv[1]);
        Pvf p(root / "Script.pvf");
        std::string mode = argv[2], name = argv[3];
        Json j;
        if (mode == "--skill-sources") {
            if (name != "summary" && name != "source") throw std::runtime_error("Use --skill-sources summary|source");
            CharacterCatalog characters(p);
            j = characters.skillSourceSnapshot(name == "source");
        } else if (mode == "--characters") {
            if (name != "summary" && name != "source") throw std::runtime_error("Use --characters summary|source");
            CharacterCatalog characters(p);
            j = characters.snapshot(name == "source");
        } else if (mode == "--script") {
            auto s = p.script(name);
            j = {{"path", name}, {"fields", Json::array()}, {"tokens", s.tokens}};
            for (auto &f : s.fields)
                j["fields"].push_back({{"tag", f.tag}, {"values", f.values}, {"offset", f.offset}});
        } else if (mode == "--paths")
            j = p.paths(name, argc > 4 ? argv[4] : "");
        else {
            Assets a(root, p);
            if (mode == "--npk-paths") {
                j = Json::array();
                const auto filter = normalize(name);
                std::vector<std::string> paths;
                for (const auto &entry : a.entries())
                    if (entry.first.find(filter) != std::string::npos) paths.push_back(entry.first);
                std::sort(paths.begin(), paths.end());
                j = paths;
            } else if (mode == "--export-image" || mode == "--export-frames") {
                if (argc < 6) throw std::runtime_error("Export requires FRAME_OR_SUFFIX and OUTPUT");
                const auto output = std::filesystem::u8path(argv[5]);
                const auto raw = a.blob(name);
                Cursor header{raw};
                header.text(16);
                header.get<uint64_t>();
                const int version = header.get<int32_t>(), count = header.get<int32_t>();
                if (count < 0 || count > 100000) throw std::runtime_error("IMG frame count");
                const bool all = mode == "--export-frames";
                const auto directory = all ? output : output.parent_path();
                if (!directory.empty()) std::filesystem::create_directories(directory);
                j = {{"path", name}, {"version", version}, {"frame_count", count},
                     {"purpose", "Original cropped IMG pixels and source coordinate metadata; diagnostic export, not gameplay capture"},
                     {"frames", Json::array()}};
                const int first = all ? 0 : std::stoi(argv[4]), end = all ? count : first + 1;
                for (int i = first; i < end; ++i) {
                    const auto px = a.pixels(name, i);
                    auto file = all ? output / (std::to_string(i) + ".png") : output;
                    Json frame = {{"frame", i}, {"width", px.width}, {"height", px.height},
                                  {"x", px.x}, {"y", px.y}, {"logical_width", px.logicalWidth},
                                  {"logical_height", px.logicalHeight}, {"png", nullptr}};
                    if (px.width > 0 && px.height > 0) {
                        if (!stbi_write_png(file.u8string().c_str(), px.width, px.height, 4, px.rgba.data(), px.width * 4))
                            throw std::runtime_error("PNG export failed: " + file.u8string());
                        frame["png"] = file.filename().u8string();
                    }
                    j["frames"].push_back(frame);
                }
                j["resource_reads"] = a.reads();
                auto sidecar = all ? output / "manifest.json" : std::filesystem::path(output.u8string() + ".json");
                writeJson(sidecar, j);
                std::cout << sidecar.u8string() << std::endl;
                return 0;
            } else if (mode == "--image") {
                auto px = a.pixels(name, argc > 4 ? std::stoi(argv[4]) : 0);
                j = {{"width", px.width},
                     {"height", px.height},
                     {"x", px.x},
                     {"y", px.y},
                     {"logical_width", px.logicalWidth},
                     {"logical_height", px.logicalHeight}};
            } else if (mode == "--ani") {
                auto an = a.animation(name);
                j = {{"path", name},
                     {"duration", an->duration},
                     {"globals", an->globals},
                     {"frames", Json::array()}};
                for (auto &f : an->frames) {
                    Json boxes = Json::array();
                    for (auto &b : f.boxes)
                        boxes.push_back({b.type, b.x, b.y, b.z, b.w, b.h, b.d});
                    j["frames"].push_back({{"image", f.image},
                                           {"frame", f.imageFrame},
                                           {"x", f.x},
                                           {"y", f.y},
                                           {"duration", f.duration},
                                           {"properties", f.properties},
                                           {"boxes", boxes}});
                }
            } else
                throw std::runtime_error("Unknown mode");
        }
        if (argc > 5)
            writeJson(std::filesystem::u8path(argv[5]), j);
        else
            std::cout << j.dump(2) << std::endl;
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
DNF_ENTRY(run)
