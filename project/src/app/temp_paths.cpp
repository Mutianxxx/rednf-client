#include "dnf/temp_paths.hpp"

#include <cstdlib>
#include <iterator>
#include <stdexcept>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#endif

namespace dnf {
namespace {
#ifdef DNF_REPO_ROOT
constexpr const char *kRepoRootHint = DNF_REPO_ROOT;
#else
constexpr const char *kRepoRootHint = nullptr;
#endif

bool hasGit(const std::filesystem::path &p) {
    std::error_code ec;
    return std::filesystem::exists(p / ".git", ec);
}

std::filesystem::path executableDirectory() {
#ifdef _WIN32
    wchar_t buffer[MAX_PATH * 4];
    const DWORD n = GetModuleFileNameW(nullptr, buffer, DWORD(std::size(buffer)));
    if (n == 0 || n >= DWORD(std::size(buffer)))
        return {};
    return std::filesystem::path(buffer).parent_path();
#else
    std::error_code ec;
    const auto link = std::filesystem::read_symlink("/proc/self/exe", ec);
    return ec ? std::filesystem::path() : link.parent_path();
#endif
}

std::filesystem::path discoverTempRoot() {
    // 1. explicit override: the temp directory itself, no probing
    if (const char *env = std::getenv("DNF_TEMP_ROOT"))
        if (*env)
            return std::filesystem::path(env);

    // 2. compile-time hint, only trusted while the tree still sits there. A
    //    stale absolute path would otherwise create a whole tree on the wrong
    //    drive after the repository is moved or renamed.
    if (kRepoRootHint) {
        const std::filesystem::path repo = std::filesystem::path(kRepoRootHint).lexically_normal();
        if (hasGit(repo))
            return repo / "temp-project-dir";
    }

    // 3. walk up from the executable
    auto dir = executableDirectory();
    for (int depth = 0; depth < 8 && !dir.empty(); ++depth) {
        if (hasGit(dir))
            return dir / "temp-project-dir";
        const auto parent = dir.parent_path();
        if (parent.empty() || parent == dir)
            break;
        dir = parent;
    }
    throw std::runtime_error("Cannot locate the project root for temp-project-dir; set DNF_TEMP_ROOT");
}

void createDirectories(const std::filesystem::path &p) {
    std::error_code ec;
    std::filesystem::create_directories(p, ec);
    if (ec && !std::filesystem::is_directory(p))
        throw std::runtime_error("Cannot create " + p.u8string() + ": " + ec.message());
}
} // namespace

long processId() {
#ifdef _WIN32
    return long(_getpid());
#else
    return long(::getpid());
#endif
}

const std::filesystem::path &projectTempRoot() {
    static const std::filesystem::path root = [] {
        auto p = discoverTempRoot();
        createDirectories(p);
        std::error_code ec;
        return std::filesystem::absolute(p, ec).lexically_normal();
    }();
    return root;
}

std::filesystem::path writablePath(const std::filesystem::path &p) {
    if (p.is_absolute())
        return p;
    return projectTempRoot() / p;
}

ScopedWorkingDirectory::ScopedWorkingDirectory(const std::filesystem::path &directory) {
    std::error_code ec;
    previous_ = std::filesystem::current_path(ec);
    if (ec)
        throw std::runtime_error("Cannot read the current working directory: " + ec.message());
    createDirectories(directory);
    std::filesystem::current_path(directory, ec);
    if (ec)
        throw std::runtime_error("Cannot enter " + directory.u8string() + ": " + ec.message());
    active_ = true;
}

ScopedWorkingDirectory::~ScopedWorkingDirectory() {
    if (!active_)
        return;
    std::error_code ec;
    std::filesystem::current_path(previous_, ec);
    // Destructors must not throw; a failed restore leaves the suite in the
    // temp tree, which is harmless for a one-shot test process.
}

std::filesystem::path testRunDirectory(const std::string &tag) {
    auto dir = projectTempRoot() / "test-runs" / (tag + "-" + std::to_string(processId()));
    createDirectories(dir);
    return dir;
}

const std::filesystem::path &testOriginDirectory() {
    static const std::filesystem::path origin = [] {
        std::error_code ec;
        return std::filesystem::current_path(ec);
    }();
    return origin;
}
} // namespace dnf
