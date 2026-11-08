#include "dnf/runtime_paths.hpp"
#include <chrono>
#include <stdexcept>

namespace dnf {
Json runRuntimePathTests() {
    Json checks = Json::array();
    auto check = [&](bool okay, const char *name) {
        if (!okay) throw std::runtime_error(name);
        checks.push_back(name);
    };
    auto rejects = [&](auto fn, const char *name) {
        bool failed = false;
        try { fn(); } catch (const std::exception &) { failed = true; }
        check(failed, name);
    };
    const auto directory = std::filesystem::absolute(std::filesystem::path("cache/tests/runtime-paths") /
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const auto workspace = directory / "project", node = workspace / "checkpoints/node";
    const auto executable = node / "runtime/dnf_native.exe";
    const std::string identity(64, 'a'), binary(64, 'b');
    const auto normal = workspace / "saves/content" / identity;
    check(defaultRuntimeSaveDirectory(workspace / "cache/build/dnf_native.exe", workspace, identity, binary) == normal,
        "An ordinary isolated build retains the content-specific normal save default");
    writeJson(node / "manifest.json", {{"kind", "development-node-backup"}, {"binary_sha256", binary}});
    check(defaultRuntimeSaveDirectory(executable, workspace, identity, binary) == node / "runtime/saves",
        "Direct execution of a verified development backup defaults to its own saves");
    check(!std::filesystem::exists(node / "runtime/saves") && !std::filesystem::exists(normal),
        "Default-path resolution reads metadata without creating or importing any save");
    rejects([&] { defaultRuntimeSaveDirectory(executable, workspace, identity, "changed"); },
        "A changed backup executable is rejected before normal-save fallback");
    writeJson(node / "manifest.json", {{"kind", "development-node-backup"}});
    rejects([&] { defaultRuntimeSaveDirectory(executable, workspace, identity, binary); },
        "Missing backup executable identity cannot silently open normal user saves");
    writeJson(node / "manifest.json", Json::array());
    rejects([&] { defaultRuntimeSaveDirectory(executable, workspace, identity, binary); },
        "Malformed backup metadata cannot silently open normal user saves");
    writeJson(node / "manifest.json", {{"kind", "other-package"}});
    check(defaultRuntimeSaveDirectory(executable, workspace, identity, binary) == normal,
        "Unrelated package metadata is not mistaken for a development backup");
    writeJson(node / "manifest.json", {{"kind", "development-node-backup"}, {"binary_sha256", binary}});
    check(defaultRuntimeSaveDirectory(node / "tools/dnf_native.exe", workspace, identity, binary) == normal,
        "Only the backed-up runtime directory activates the node save default");
    return {{"status", "pass"}, {"checks", checks}, {"frontend_started", false},
        {"scope", "Default-path and corrupt-backup boundary checks; explicit CLI overrides remain in main"}};
}
} // namespace dnf
