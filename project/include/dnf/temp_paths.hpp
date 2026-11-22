#pragma once
#include <filesystem>
#include <string>

namespace dnf {
// Root of the disposable artifact area: <repo>/temp-project-dir.
//
// Resolution order:
//   1. DNF_TEMP_ROOT environment variable (the temp directory itself)
//   2. DNF_REPO_ROOT compile definition, trusted only while <root>/.git exists
//   3. walking up from the executable looking for a .git directory
//
// Created once on first use and cached for the process lifetime. Everything
// that is regenerated on every run (test fixtures, diagnostics, reports,
// content caches) belongs under this root; user saves never do.
const std::filesystem::path &projectTempRoot();

// Absolute paths pass through untouched; relative paths resolve under
// projectTempRoot(). Products use this to keep diagnostics and caches out of
// the repository root without changing any library I/O semantics.
std::filesystem::path writablePath(const std::filesystem::path &p);

// RAII switch of the process working directory. Tests use it so that the
// hundreds of relative fixture paths land inside projectTempRoot() instead of
// the repository root. Restores the previous directory on destruction.
class ScopedWorkingDirectory {
public:
    explicit ScopedWorkingDirectory(const std::filesystem::path &directory);
    ~ScopedWorkingDirectory();
    ScopedWorkingDirectory(const ScopedWorkingDirectory &) = delete;
    ScopedWorkingDirectory &operator=(const ScopedWorkingDirectory &) = delete;
    const std::filesystem::path &previous() const { return previous_; }

private:
    std::filesystem::path previous_;
    bool active_ = false;
};

// Convenience for tests: <temp>/test-runs/<tag>-<pid>/ created on demand. The
// pid suffix keeps concurrent suite workers from colliding on the writer lock.
std::filesystem::path testRunDirectory(const std::string &tag);

// Directory the process started in, captured on first call. Suite entry points
// must read it before entering their scoped working directory, because a few
// suites still default a relative client path that is only valid from there.
const std::filesystem::path &testOriginDirectory();

// Current process id, spelled portably for both the suite entry point and the
// diagnostics that want to tag a run.
long processId();
} // namespace dnf
