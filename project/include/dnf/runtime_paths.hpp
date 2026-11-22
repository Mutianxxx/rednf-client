#pragma once
#include "dnf/content_profile.hpp"

namespace dnf {
// Read-only default selection. An explicit --save-dir remains caller-owned.
// Development node executables use their own runtime/saves even on double click.
std::filesystem::path defaultRuntimeSaveDirectory(const std::filesystem::path &executable,
    const std::filesystem::path &workspace, const std::string &contentId,
    const std::string &binarySha256);
} // namespace dnf
