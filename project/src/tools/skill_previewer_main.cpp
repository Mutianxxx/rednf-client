#include "dnf/character.hpp"
#include "dnf/content_profile.hpp"
#include "dnf/entry.hpp"
#include "dnf/renderer.hpp"
#include "dnf/skill_preview.hpp"
#include "dnf/skill_preview_audio.hpp"
#include "dnf/skill_preview_mapping.hpp"
#include "dnf/skill_preview_ui.hpp"
#include <SDL.h>
#include <filesystem>
#include <iostream>
#include <stdexcept>

using namespace dnf;
namespace fs = std::filesystem;
namespace {

constexpr int uiWidth = 1280;
constexpr int uiHeight = 720;

struct Options {
    std::optional<fs::path> profile;
    fs::path client, reportDirectory = "reports/skill-previewer";
    int job = -1, skill = -1;
    bool audio = true;
    fs::path capture;
    int captureFrames = 0;
    // Wall-clock capture: run this many milliseconds of real time, then
    // screenshot. This exercises the real time path instead of the fixed step.
    int captureAfterMs = 0;
    bool auditMap = false;
};

Options parseOptions(int argc, char **argv) {
    Options options;
    for (int i = 1; i < argc; ++i) {
        const std::string argument = argv[i];
        const auto next = [&]() -> std::string {
            if (i + 1 >= argc) throw std::runtime_error("Missing value for " + argument);
            return argv[++i];
        };
        if (argument == "--content-profile") options.profile = fs::u8path(next());
        else if (argument == "--client") options.client = fs::u8path(next());
        else if (argument == "--report-dir") options.reportDirectory = fs::u8path(next());
        else if (argument == "--job") options.job = std::stoi(next());
        else if (argument == "--skill") options.skill = std::stoi(next());
        else if (argument == "--no-audio") options.audio = false;
        else if (argument == "--capture") { options.capture = fs::u8path(next()); options.captureFrames = 90; }
        else if (argument == "--capture-frames") options.captureFrames = std::stoi(next());
        else if (argument == "--capture-after-ms") options.captureAfterMs = std::stoi(next());
        else if (argument == "--audit-map") options.auditMap = true;
        else throw std::runtime_error("Unknown argument: " + argument);
    }
    return options;
}

} // namespace

int entry(int argc, char **argv) {
    Options options;
    try {
        options = parseOptions(argc, argv);
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
        return 2;
    }
    fs::create_directories(options.reportDirectory);

    ContentProfileOverrides overrides;
    if (!options.client.empty()) {
        overrides.pvfPath = options.client / "Script.pvf";
        overrides.resourceRoots = {options.client};
    }
    std::unique_ptr<Pvf> pvf;
    std::unique_ptr<Assets> assets;
    std::unique_ptr<CharacterCatalog> characters;
    try {
        std::cout << "[1/4] 定位客户端与 PVF" << std::endl;
        const auto profile = resolveContentProfile(options.profile, fs::current_path(), overrides,
                                                   fs::current_path());
        std::cout << "[2/4] 读取 PVF: " << profile.pvfPath.u8string() << std::endl;
        pvf = std::make_unique<Pvf>(profile.pvfPath);
        assets = std::make_unique<Assets>(profile.resourceRoots, *pvf);
        std::cout << "[3/4] 加载职业与技能注册表" << std::endl;
        characters = std::make_unique<CharacterCatalog>(*pvf);
    } catch (const std::exception &error) {
        std::cerr << "内容加载失败: " << error.what() << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "技能演示", error.what(), nullptr);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL 初始化失败: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::unique_ptr<SkillMappingTable> table;
    std::unique_ptr<SkillPreviewSession> session;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<SkillPreviewUi> ui;
    std::unique_ptr<SkillSoundSink> sink;
    try {
        std::cout << "[4/4] 建立技能映射表" << std::endl;
        table = std::make_unique<SkillMappingTable>(*pvf, *assets, *characters);

        if (options.auditMap) {
            for (const auto &definition : characters->definitions) {
                if (definition.registration.id < 0) continue;
                table->ensureJob(definition.registration.id);
            }
            std::vector<int> jobIds;
            for (const auto &job : table->jobs()) jobIds.push_back(job.jobId);
            const auto audit = table->auditJson(jobIds);
            writeJson(options.reportDirectory / "skill-map-audit.json", audit);
            const auto &totals = audit["totals"];
            std::cout << "技能映射审计 A/B/C/D = " << totals["A"] << "/" << totals["B"]
                      << "/" << totals["C"] << "/" << totals["D"] << std::endl;
            for (const auto &job : table->jobs())
                std::cout << "  job " << job.jobId << "  " << job.skillCount << " 条  A "
                          << job.gradeA << "  B " << job.gradeB << "  C " << job.gradeC
                          << "  D " << job.gradeD << std::endl;
            std::cout << "明细: "
                      << (options.reportDirectory / "skill-map-audit.json").u8string() << std::endl;
            SDL_Quit();
            return 0;
        }

        session = std::make_unique<SkillPreviewSession>(*pvf, *assets, *characters, *table);
        // 40JP drives its frame loop from an idle PeekMessage pump with no frame
        // cap, so the viewer must not let present() throttle it.
        renderer = std::make_unique<Renderer>(*assets,
            RendererOptions{"DNF 40JP 技能演示", uiWidth, uiHeight, false, true, true});
        ui = std::make_unique<SkillPreviewUi>(uiWidth, uiHeight);
        if (options.audio) sink = makeAudioSkillSoundSink(*assets);
        if (!sink) sink = std::make_unique<NullSkillSoundSink>();
    } catch (const std::exception &error) {
        std::cerr << "初始化失败: " << error.what() << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "技能演示", error.what(), nullptr);
        return 1;
    }

    // Build every job's mapping rows up front so the UI job list has content
    // on first frame; jobs() only reflects jobs that ensureJob has visited.
    for (const auto &definition : characters->definitions) {
        if (definition.registration.id < 0) continue;
        table->ensureJob(definition.registration.id);
    }
    int selectedJob = options.job >= 0 ? options.job
        : table->jobs().empty() ? -1 : table->jobs().front().jobId;
    int selectedSkill = -1;
    if (selectedJob >= 0) {
        table->ensureJob(selectedJob);
        std::string error;
        if (!session->selectJob(selectedJob, error)) std::cerr << "职业不可用: " << error << std::endl;
        if (options.skill >= 0) {
            const auto &rows = table->rows(selectedJob);
            for (size_t i = 0; i < rows.size(); ++i)
                if (rows[i].key.skillId == options.skill) selectedSkill = int(i);
        }
    }

    const auto playSelected = [&]() {
        const auto &rows = table->rows(selectedJob);
        if (selectedSkill < 0 || selectedSkill >= int(rows.size())) return;
        const auto *mapping = table->mapping(rows[size_t(selectedSkill)].key);
        if (!mapping) return;
        std::string error;
        if (!session->play(*mapping, error)) std::cerr << "播放失败: " << error << std::endl;
    };
    if (options.skill >= 0) playSelected();

    bool running = true;
    int frameCount = 0;
    const uint64_t captureStart = SDL_GetTicks64();
    uint64_t lastTicks = captureStart;
    while (running) {
        bool click = false, doubleClick = false;
        int wheel = 0;
        int mx = 0, my = 0, clickX = -1, clickY = -1;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                click = true;
                doubleClick = event.button.clicks >= 2;
                // Use the coordinates carried by the event: sampling the pointer
                // before polling returns last frame's position, which lands on a
                // neighbouring row while the cursor is still moving.
                clickX = event.button.x;
                clickY = event.button.y;
            } else if (event.type == SDL_MOUSEWHEEL) {
                wheel += event.wheel.y;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: running = false; break;
                    case SDLK_SPACE: session->setPaused(!session->paused()); break;
                    case SDLK_LEFT: session->setPaused(true); session->stepFrame(-1); break;
                    case SDLK_RIGHT: session->setPaused(true); session->stepFrame(1); break;
                    case SDLK_1: session->setSpeed(1.0); break;
                    case SDLK_2: session->setSpeed(0.5); break;
                    case SDLK_3: session->setSpeed(0.25); break;
                    case SDLK_4: session->setSpeed(2.0); break;
                    case SDLK_r: session->reset(); playSelected(); break;
                    case SDLK_f: session->setFacing(-session->facing()); playSelected(); break;
                    case SDLK_b: session->setBoxesVisible(!session->boxesVisible()); break;
                    case SDLK_h: session->cycleDummy(); break;
                    case SDLK_l: session->setLoop(!session->loop()); break;
                    case SDLK_UP:
                        if (selectedSkill > 0) { --selectedSkill; playSelected(); }
                        break;
                    case SDLK_DOWN: {
                        const auto &rows = table->rows(selectedJob);
                        if (selectedSkill + 1 < int(rows.size())) { ++selectedSkill; playSelected(); }
                        break;
                    }
                    case SDLK_F12:
                        renderer->screenshot(options.reportDirectory / "skill-preview.png");
                        break;
                    default: break;
                }
            }
        }
        // Polling has already consumed this frame's events, so the pointer read
        // here is current rather than one frame stale.
        SDL_GetMouseState(&mx, &my);
        renderer->mouse(mx, my, uiWidth, uiHeight);
        if (clickX >= 0) {
            int cx = clickX, cy = clickY;
            renderer->mouse(cx, cy, uiWidth, uiHeight);
            clickX = cx;
            clickY = cy;
        }
        if (wheel != 0) ui->scroll(wheel * 3, mx);

        const auto now = SDL_GetTicks64();
        // SDL_GetTicks64() is milliseconds; the session takes milliseconds too.
        const bool fixedStep = !options.capture.empty() && options.captureAfterMs <= 0;
        session->advance(fixedStep ? 1000.0 / 60.0 : double(now - lastTicks));
        lastTicks = now;
        for (const auto &id : session->drainSounds()) sink->play(id);

        renderer->begin();
        renderer->ui(uiWidth, uiHeight);
        SkillPreviewUi::InputState input;
        input.mx = mx;
        input.my = my;
        input.clickX = clickX;
        input.clickY = clickY;
        input.click = click;
        input.doubleClick = doubleClick;
        const auto request = ui->draw(*renderer, *pvf, *table, *session, selectedJob, selectedSkill, input);
        renderer->present();

        ++frameCount;
        const bool frameReached = options.captureAfterMs <= 0 && frameCount >= options.captureFrames;
        const bool timeReached = options.captureAfterMs > 0 &&
            int64_t(now - captureStart) >= options.captureAfterMs;
        if (!options.capture.empty() && (frameReached || timeReached)) {
            renderer->screenshot(options.capture);
            running = false;
        }

        if (request.jobId >= 0 && request.jobId != selectedJob) {
            selectedJob = request.jobId;
            selectedSkill = -1;
            table->ensureJob(selectedJob);
            std::string error;
            if (!session->selectJob(selectedJob, error)) std::cerr << "职业不可用: " << error << std::endl;
        }
        if (request.skillIndex >= 0) {
            // A single click plays immediately; a double click on the same row
            // replays from the start.
            const bool sameSkill = request.skillIndex == selectedSkill;
            selectedSkill = request.skillIndex;
            if (request.cast && sameSkill) session->reset();
            playSelected();
        }
    }
    if (session->hasJob())
        writeJson(options.reportDirectory / "skill-preview-report.json", session->report());
    renderer.reset();
    SDL_Quit();
    return 0;
}

DNF_ENTRY(entry)
