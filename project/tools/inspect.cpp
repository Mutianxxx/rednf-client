#include "dnf/entry.hpp"
#include "dnf/resources.hpp"
#include "dnf/character.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/skill_preview_mapping.hpp"
#define STBIW_WINDOWS_UTF8
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <algorithm>
#include <iostream>
#include <map>
using namespace dnf;
int run(int argc, char **argv) {
    try {
        if (argc < 4) {
            std::cout << "dnf_inspect CLIENT --script|--ani|--image|--paths|--npk-paths|--export-image|--export-frames|--characters|--skill-sources|--skill-chain|--act-coverage|--act-coverage-prefix PATH [FRAME_OR_SUFFIX] [OUTPUT]\n"
                         "--skill-chain JOBID SKILLID [OUTPUT] dumps the resolved body-chain timeline, ALS events and diagnostics for AVI cross-validation.\n"
                         "--npk-paths lists archive image paths containing PATH; --paths lists PVF paths.\n"
                         "--export-image writes a cropped RGBA PNG and sidecar JSON; --export-frames writes every frame plus manifest.json to OUTPUT directory.\n"
                         "Use a placeholder FRAME_OR_SUFFIX when writing --script or --act-coverage output.\n"
                         "--act-coverage PATH [placeholder] [OUTPUT] exports static ACT compilation and real World-host admission, not execution evidence.\n"
                         "--act-coverage-prefix PREFIX _ OUTPUT compiles sorted PVF .act paths with one World host and exports per-file diagnostics plus counts.\n"
                         "ACT coverage uses default host options (speech presentation disabled); exit 0 means report generated, inspect JSON ok for overall admission; stage readiness flags are independent.\n"
                         "--characters summary|source exports all registered CHR/skill lists; source includes original bytes/tokens.\n"
                         "--skill-sources summary|source exports every registered skill with ordered mode-scoped fields; this is source evidence, not runtime coverage.\n";
            return 2;
        }
        auto root = std::filesystem::u8path(argv[1]);
        Pvf p(root / "Script.pvf");
        std::string mode = argv[2], name = argv[3];
        Json j;
        if (mode == "--act-coverage" || mode == "--act-coverage-prefix") {
            if (mode == "--act-coverage" && argc > 6) throw std::runtime_error("--act-coverage PATH [placeholder] [OUTPUT]");
            if (mode == "--act-coverage-prefix" && (argc != 6 || std::string(argv[4]) != "_"))
                throw std::runtime_error("--act-coverage-prefix PREFIX _ OUTPUT");
            Assets a(root, p);
            World world(p, a);
            ActWorldHost host(world, p, a, "act-coverage-audio-xml:" + sha256(a.staticBytes("audio.xml")));
            if (mode == "--act-coverage") {
                j = host.compile(name).json();
                j["purpose"] = "Static ACT compilation and real World-host admission; no bind, dispatch or simulation advance, not execution evidence.";
                j["host_options"] = {{"enable_speech_presentation", false}, {"speech_duration_ms", 1200}};
                j["static_identity_scope"] = "audio.xml SHA256 only, not a full static-content package fingerprint; dependencies retain their own hashes";
            } else {
                std::vector<std::string> paths = p.paths(name, ".act");
                std::sort(paths.begin(), paths.end());
                Json files = Json::array(), statusCounts = {{"syntax", {{"pass", 0}, {"fail", 0}, {"error", 0}}},
                    {"source", {{"pass", 0}, {"fail", 0}, {"error", 0}}}, {"runtime", {{"pass", 0}, {"fail", 0}, {"error", 0}}}};
                std::map<std::string, size_t> blockingCodes;
                size_t admittedCount = 0, exceptionCount = 0;
                for (const auto &path : paths) {
                    Json item = {{"path", path}};
                    try {
                        item["coverage"] = host.compile(path).json();
                        const auto &coverage = item["coverage"];
                        if (coverage.value("ok", false)) ++admittedCount;
                        for (const char *stage : {"syntax_complete", "source_ready", "runtime_ready"}) {
                            const char *label = stage == std::string("syntax_complete") ? "syntax" :
                                stage == std::string("source_ready") ? "source" : "runtime";
                            const char *result = coverage.value(stage, false) ? "pass" : "fail";
                            statusCounts[label][result] = statusCounts[label][result].get<size_t>() + 1;
                        }
                        for (const auto &diagnostic : coverage.value("diagnostics", Json::array()))
                            if (diagnostic.value("blocking", true))
                                ++blockingCodes[diagnostic.value("code", "UNKNOWN")];
                    } catch (const std::exception &e) {
                        ++exceptionCount;
                        item["error"] = e.what();
                        for (const char *label : {"syntax", "source", "runtime"})
                            statusCounts[label]["error"] = statusCounts[label]["error"].get<size_t>() + 1;
                    } catch (...) {
                        ++exceptionCount;
                        item["error"] = "unknown exception";
                        for (const char *label : {"syntax", "source", "runtime"})
                            statusCounts[label]["error"] = statusCounts[label]["error"].get<size_t>() + 1;
                    }
                    files.push_back(item);
                }
                Json codes = Json::object();
                for (const auto &[code, count] : blockingCodes) codes[code] = count;
                j = {{"purpose", "Static ACT prefix compilation and real World-host admission; no bind, dispatch or simulation advance, not execution evidence."},
                     {"prefix", name}, {"suffix", ".act"}, {"host_options", {{"enable_speech_presentation", false}, {"speech_duration_ms", 1200}}},
                     {"static_identity_scope", "audio.xml SHA256 only, not a full static-content package fingerprint; dependencies retain their own hashes"},
                     {"files", files}, {"file_count", files.size()}, {"exception_count", exceptionCount}, {"admitted_count", admittedCount}, {"status_counts", statusCounts}, {"blocking_diagnostic_codes", codes}};
            }
        } else if (mode == "--skill-sources") {
            if (name != "summary" && name != "source") throw std::runtime_error("Use --skill-sources summary|source");
            CharacterCatalog characters(p);
            j = characters.skillSourceSnapshot(name == "source");
        } else if (mode == "--characters") {
            if (name != "summary" && name != "source") throw std::runtime_error("Use --characters summary|source");
            CharacterCatalog characters(p);
            j = characters.snapshot(name == "source");
        } else if (mode == "--skill-chain") {
            if (argc < 5) throw std::runtime_error("--skill-chain JOBID SKILLID [OUTPUT]");
            const int jobId = std::stoi(name);
            const int skillId = std::stoi(argv[4]);
            Assets a(root, p);
            CharacterCatalog characters(p);
            SkillMappingTable table(p, a, characters);
            table.ensureJob(jobId);
            const auto *m = table.mapping(SkillKey{jobId, skillId});
            if (!m) throw std::runtime_error("no mapping for the requested skill key");
            // Body stages are laid end to end on one action clock. Keeping the
            // raw [DELAY] table next to each stage lets a consumer recompute
            // any frame boundary instead of trusting a single derived number.
            Json stages = Json::array();
            std::vector<double> stageStart;
            double cursor = 0;
            for (const auto &path : m->bodyChain) {
                stageStart.push_back(cursor);
                Json delays = Json::array();
                double duration = 0;
                try {
                    const auto an = a.animation(path);
                    for (const auto &f : an->frames) {
                        const int d = std::max(1, f.duration);
                        delays.push_back(d);
                        duration += d;
                    }
                } catch (const std::exception &) {
                }
                stages.push_back({{"index", int(stageStart.size() - 1)}, {"path", path},
                                  {"startMs", cursor}, {"durationMs", duration},
                                  {"frameDelays", delays}});
                cursor += duration;
            }
            // Every ALS command is retained, including the ones the renderer
            // cannot consume yet. A diagnostic is an observed source command,
            // not a claim that it is invisible in the original client: the AVI
            // cross-check is what decides that.
            Json als = Json::array();
            for (size_t s = 0; s < m->bodyChain.size(); ++s) {
                const auto plan = animationEffectEvents(p, a, m->bodyChain[s]);
                for (const auto &ev : plan.events) {
                    double boundary = 0;
                    try {
                        const auto an = a.animation(m->bodyChain[s]);
                        for (int i = 0; i < ev.frame && i < int(an->frames.size()); ++i)
                            boundary += std::max(1, an->frames[i].duration);
                    } catch (const std::exception &) {
                    }
                    const char *kind = ev.kind == EffectEventKind::Remove ? "remove"
                        : ev.kind == EffectEventKind::DrawOnly ? "draw_only"
                        : ev.kind == EffectEventKind::DrawOnlyFollowParent ? "draw_only_follow_parent"
                                                                          : "add";
                    als.push_back({{"stage", int(s)}, {"parent", m->bodyChain[s]},
                                   {"kind", kind}, {"frame", ev.frame}, {"layer", ev.layer},
                                   {"instance", ev.instance}, {"animation", ev.animation},
                                   {"sourceOrder", ev.sourceOrder},
                                   {"offset", {ev.offsetX, ev.offsetY, ev.offsetZ}},
                                   {"boundaryMs", boundary},
                                   {"actionMs", stageStart[s] + boundary}});
                }
                for (const auto &d : plan.diagnostics)
                    als.push_back({{"stage", int(s)}, {"parent", m->bodyChain[s]},
                                   {"kind", "diagnostic"}, {"diagnostic", d}});
            }
            // Predicted timeline for AVI cross-validation. The source gives
            // fixed [DELAY] spans; input-wait states and the gaps between
            // triggered pairs are NOT timed by any file, so they are exported
            // as external slots. Only an independent observation can quantify
            // them. Nothing here is fitted to the video.
            Json fixed = Json::array();
            for (size_t i = 0; i < m->chainSlots.size(); ++i) {
                const auto &s = m->chainSlots[i];
                const char *role = s.role == ChainSlotRole::Entry ? "entry"
                                   : s.role == ChainSlotRole::Triggered ? "triggered"
                                   : s.role == ChainSlotRole::Finish ? "finish"
                                   : s.role == ChainSlotRole::Plain ? "plain" : "external_hold";
                fixed.push_back({{"index", int(i)}, {"path", s.path}, {"role", role},
                                 {"startMs", s.startMs},
                                 {"endMs", s.startMs + s.durationMs},
                                 {"durationMs", s.durationMs},
                                 {"frameCount", s.frameCount},
                                 {"evidence", s.evidence}});
            }
            Json external = Json::array();
            for (const auto &s : m->externalSlots)
                external.push_back({{"path", s.path}, {"startMs", nullptr},
                                    {"sourceDurationMs", s.durationMs},
                                    {"frameCount", s.frameCount},
                                    {"evidence", s.evidence},
                                    {"quantifiedBy", "independent observation only"}});
            const double nominal = m->nominalActionMs > 0 ? m->nominalActionMs : cursor;
            Json births = Json::array();
            for (const auto &l : m->effectLayers) {
                const char *clock = l.timed ? "als"
                                    : l.stageBound ? "stage_bound" : "stem_order";
                const double at = l.birthMs >= 0 ? l.birthMs : l.birthRatio * nominal;
                births.push_back({{"path", l.path}, {"birthMs", at}, {"endMs", l.endMs},
                                  {"clock", clock}, {"timed", l.timed},
                                  {"stageBound", l.stageBound},
                                  {"bodyStage", l.bodyStage}, {"source", l.source},
                                  {"evidence", l.evidence}});
            }
            Json windows = Json::array();
            for (size_t i = 0; i < fixed.size();) {
                size_t j = i + 1;
                const std::string role = fixed[i]["role"].get<std::string>();
                while (j < fixed.size() && fixed[j]["role"].get<std::string>() == role) ++j;
                const double from = m->chainSlots[i].startMs;
                const double to = m->chainSlots[j - 1].startMs + m->chainSlots[j - 1].durationMs;
                windows.push_back({{"role", role}, {"fromMs", from}, {"toMs", to},
                                   {"slotCount", int(j - i)}});
                i = j;
            }
            j = {{"purpose", "Base-client skill-chain parse for AVI cross-validation; diagnostics are unresolved source commands, not runtime proof."},
                 {"pvf_identity", p.identity()}, {"jobId", jobId}, {"skillId", skillId},
                 {"mapping", m->audit()}, {"bodyStages", stages},
                 {"actionDurationMs", cursor}, {"nominalActionMs", nominal},
                 {"alsEvents", als},
                 {"predictedTimeline", {
                     {"clock", "nominal ANI [DELAY] sum; input-wait states excluded"},
                     {"fixedSlots", fixed}, {"externalSlots", external},
                     {"phaseWindows", windows}, {"layerBirths", births},
                     {"note", "Fixed spans come from the base PVF. External slots and inter-trigger gaps are unquantified here; the AVI observation supplies them."}}}};
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
