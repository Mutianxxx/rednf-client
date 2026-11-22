#include "dnf/runtime_paths.hpp"
#include <stdexcept>

namespace dnf {
std::filesystem::path defaultRuntimeSaveDirectory(const std::filesystem::path &executable,
    const std::filesystem::path &workspace, const std::string &contentId,
    const std::string &binarySha256) {
    const auto runtime = std::filesystem::absolute(executable).lexically_normal().parent_path();
    const auto manifest = runtime.parent_path() / "manifest.json";
    if (runtime.filename() == "runtime" && std::filesystem::exists(manifest)) {
        // A damaged node must never silently fall back to the normal user save.
        const auto metadata = Json::parse(readFile(manifest));
        if (!metadata.is_object()) throw std::runtime_error("Invalid runtime node manifest");
        if (metadata.value("kind", std::string()) == "development-node-backup") {
            if (binarySha256.empty() || metadata.value("binary_sha256", std::string()) != binarySha256)
                throw std::runtime_error("Runtime node executable differs from its backup manifest");
            return runtime / "saves";
        }
    }
    return std::filesystem::absolute(workspace / "saves" / "content" / contentId).lexically_normal();
}
} // namespace dnf
