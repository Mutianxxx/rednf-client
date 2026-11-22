#pragma once
#include "resources.hpp"
#include <optional>

namespace dnf {
// Source identity is computed from bytes, never from a physical directory or mtime.
std::string sha256(const Bytes &bytes);
std::string sha256File(const std::filesystem::path &path);
// The v1 manifest covers these static namespaces. Consumers must not silently
// read loose files outside them under the same content identity.
bool fingerprintedStaticPath(const std::filesystem::path &relative);

struct SourceRef {
    std::string packageIdentity, memberPath, memberSha256, textEncoding = "CP936";
    uint64_t byteOffset = 0, byteLength = 0;
    size_t ordinal = 0;
    std::string scope, literalPath;
    Json json() const;
};
SourceRef makeSourceRef(const Pvf &, const std::string &path, uint64_t offset = 0,
                        uint64_t length = 0, size_t ordinal = 0, const std::string &scope = "");

struct ContentProfileOverrides {
    std::optional<std::filesystem::path> pvfPath;
    std::vector<std::filesystem::path> resourceRoots;
};
struct ContentIdentity {
    std::string contentId, pvfSha256, archiveManifestHash, cacheId;
    Json manifest = Json::array();
    Json json() const;
};
struct ContentProfile {
    std::string profileId = "default", textEncoding = "CP936";
    std::string parserVersion = "dnf-source-v1", compatibilityProfileId = "1031-v1";
    // Source HP/MP growth and skill costs; damage/monster balance still legacy.
    std::string ruleProfileId = "beta-foundation-v1";
    std::filesystem::path pvfPath;
    std::vector<std::filesystem::path> resourceRoots;
    Json resolution = Json::array();
    ContentIdentity fingerprint() const;
    Json effective(const ContentIdentity &) const;
};
// Relative profile paths resolve against the profile file, CLI paths against
// invocationDirectory. A missing explicitly requested profile is an error.
ContentProfile resolveContentProfile(const std::optional<std::filesystem::path> &profile,
    const std::filesystem::path &defaultClient, const ContentProfileOverrides &overrides = {},
    const std::filesystem::path &invocationDirectory = std::filesystem::current_path());
} // namespace dnf
