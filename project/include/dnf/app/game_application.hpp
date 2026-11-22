#pragma once
#include <cstdint>
#include <filesystem>
#include <string>

namespace dnf::app {
// Owns one invocation's paths and diagnostic identity. World and devices remain
// scoped inside run(), so their established destruction order is preserved.
class GameApplication final {
public:
    int run(int argc, char** argv);
private:
    std::filesystem::path reportDirectory_ = "reports";
    std::filesystem::path saveDirectory_ = "saves";
    std::string runId_;
    int64_t startedMs_ = 0;
    std::filesystem::path reportPath(const std::string& name) const;
};
} // namespace dnf::app
