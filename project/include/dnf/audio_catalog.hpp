#pragma once
#include "resources.hpp"
#include <map>

namespace dnf {
enum class AudioKind { Unknown, Effect, Music, Ambient, Random };
const char *audioKindName(AudioKind kind);

struct AudioRandomItem {
    std::string id;
    int weight = 0;
    size_t offset = 0;
    Json attributes = Json::array();
    std::string rawHex;
};
struct AudioDeclaration {
    AudioKind kind = AudioKind::Unknown;
    std::string id, file, fileLiteral;
    size_t offset = 0, endOffset = 0;
    // Ordered attributes and original tag bytes retain unknown fields/units.
    Json attributes = Json::array();
    std::string rawHex;
    std::vector<AudioRandomItem> items;
};
struct AudioScenePlan {
    std::string music;
    std::vector<std::string> ambient, effects;
    Json sourceIds = Json::array(), issues = Json::array();
    Json snapshot() const;
};
// Source-only model. XML volume/priority/delay units are retained, not guessed.
class AudioCatalog {
    Bytes source_;
    std::string sourcePath_;
    std::vector<AudioDeclaration> declarations_;
    std::map<std::string, std::vector<size_t>> byId_;
    Json issues_ = Json::array();
    AudioKind kind(const std::string &id, std::vector<std::string> &stack) const;
  public:
    AudioCatalog() = default;
    AudioCatalog(Bytes source, std::string sourcePath);
    const std::vector<AudioDeclaration> &declarations() const { return declarations_; }
    std::vector<const AudioDeclaration *> find(const std::string &id) const;
    AudioKind kind(const std::string &id) const;
    AudioScenePlan scene(const Json &ids) const;
    Json snapshot(bool includeSource = false) const;
};
} // namespace dnf
