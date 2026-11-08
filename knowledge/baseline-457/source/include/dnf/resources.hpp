#pragma once
#include "json.hpp"
#include "../../../reverse-60us/integration/include/dnf_ani_render.hpp"
#include "../../../reverse-60us/integration/include/dnf_ani_clock.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace dnf {
using Json = nlohmann::ordered_json;
using Bytes = std::vector<uint8_t>;
std::string normalize(std::string s);
std::string gbk(const std::string &s);
Bytes readFile(const std::filesystem::path &p);
void writeJson(const std::filesystem::path &p, const Json &value);
struct Cursor {
    const Bytes &b;
    size_t at = 0;
    void need(size_t n) const;
    template <class T> T get() {
        need(sizeof(T));
        T v;
        std::memcpy(&v, b.data() + at, sizeof(T));
        at += sizeof(T);
        return v;
    }
    std::string text(size_t n);
    std::string sizedText();
};
struct Field {
    std::string tag;
    Json values = Json::array();
    size_t offset = 0;
};
struct Script {
    std::string path;
    Bytes rawBytes;
    Json source = Json::object();
    std::vector<Field> fields;
    Json tokens = Json::array();
    Json values(std::string tag) const;
    double number(std::string tag, double fallback = 0) const;
    std::string text(std::string tag, std::string fallback = "") const;
};
// A metadata projection, never a complete parsed script. All source bytes and
// offsets remain available; selectedTokens only contains the requested fields.
struct ScriptFieldView {
    std::string path;
    Bytes rawBytes;
    Json source = Json::object();
    std::vector<Field> fields;
    Json selectedTokens = Json::array();
    Json values(std::string tag) const;
};
class CharacterCatalog;
class CharacterAdvancementCatalog;
class Pvf {
    // Content-derived values live with this source owner. Copy/move of a Pvf
    // deliberately starts a fresh cache and never aliases mutable counters or
    // entries with another Pvf instance. The payload has no reference to Pvf.
    struct AdvancementCacheSlot {
        std::string context, contextSha256;
        std::shared_ptr<const CharacterAdvancementCatalog> value;
        uint64_t requests = 0, hits = 0, builds = 0;
        AdvancementCacheSlot() = default;
        AdvancementCacheSlot(const AdvancementCacheSlot &) noexcept {}
        AdvancementCacheSlot(AdvancementCacheSlot &&other) noexcept { other.clear(); }
        AdvancementCacheSlot &operator=(const AdvancementCacheSlot &) noexcept { clear(); return *this; }
        AdvancementCacheSlot &operator=(AdvancementCacheSlot &&other) noexcept {
            clear(); if(this!=&other)other.clear(); return *this;
        }
        void clear() noexcept {
            value.reset(); context.clear(); contextSha256.clear(); requests=hits=builds=0;
        }
    };
    mutable AdvancementCacheSlot advancementSourceCache_;
    friend std::shared_ptr<const CharacterAdvancementCatalog> sharedCharacterAdvancementCatalog(Pvf &,const CharacterCatalog &);
    friend Json characterAdvancementCacheSnapshot(const Pvf &);
    struct Entry {
        uint32_t size, crc;
        uint64_t offset;
        std::string literalPath;
    };
    std::filesystem::path path_;
    std::string identity_;
    std::unordered_map<std::string, Entry> entries_;
    Bytes stringTable_;
    std::vector<uint32_t> stringOffsets_;
    mutable std::unordered_map<int32_t, std::string> decodedStrings_;
    std::unordered_map<int, std::vector<int32_t>> translationMembers_;
    const std::string &stringAt(int32_t index, const std::string &context) const;
    const std::unordered_map<std::string, std::string> &translationGroup(int id) const;
    void parseTokens(const Bytes &, const std::string &, std::vector<Field> &, Json &,
                     const std::unordered_set<std::string> *wanted = nullptr) const;
    mutable std::unordered_map<std::string, Script> scriptCache_;
    mutable Json reads_ = Json::object();
    mutable std::unordered_map<int, std::unordered_map<std::string, std::string>> translations_;

  public:
    explicit Pvf(std::filesystem::path path, std::string verifiedIdentity = "");
    const std::string &identity() const { return identity_; }
    const std::filesystem::path &path() const { return path_; }
    bool has(const std::string &name) const;
    Bytes read(const std::string &name) const;
    Script script(const std::string &name) const;
    // No script-cache insertion and no decoding of values in unselected fields.
    ScriptFieldView fieldView(const std::string &name, const std::vector<std::string> &wantedTags) const;
    Json loadingStats() const;
    std::vector<std::string> paths(const std::string &prefix, const std::string &suffix = "") const;
    size_t count() const { return entries_.size(); }
    const Json &reads() const { return reads_; }
};
struct Box {
    int type;
    int x, y, z, w, h, d;
};
struct AniFrame {
    std::string image;
    int imageFrame = 0, x = 0, y = 0;
    int duration = 50;
    std::vector<Box> boxes;
    Json properties = Json::object();
};
// Source ANI rotations remain radians. Backend conversion occurs at draw time.
// Image/frame, blend modes, hit boxes and events stay discrete during a tween.
struct AniPose {
    size_t frame = 0, nextFrame = 0;
    double progress = 0, localTime = 0;
    bool interpolated = false;
    std::string image;
    int imageFrame = 0, blend = 0, flip = 0;
    double x = 0, y = 0, scaleX = 1, scaleY = 1, rotationRadians = 0;
    std::array<double, 4> rgba{255, 255, 255, 255};
    std::array<uint8_t, 3> effectRgb{255, 255, 255};
    Json unsupported = Json::array();
};
struct Animation {
    std::string path;
    std::vector<AniFrame> frames;
    Json globals = Json::object();
    int duration = 0;
    size_t frameAt(int64_t ms, bool loop) const;
    AniPose samplePose(double ms, bool loop, int frameOverride = -1,
                       ani_render::RenderProfile profile = ani_render::RenderProfile::Legacy1031,
                       const ani_clock::Snapshot *clock = nullptr) const;
    AniPose samplePose(const ani_clock::Snapshot &clock,
                       ani_render::RenderProfile profile = ani_render::RenderProfile::Legacy1031) const {
        return samplePose(0, clock.loop, -1, profile, &clock);
    }
    // Same-motion child: copy only the min decoded delays into a borrowed view;
    // source frames/bytes stay immutable. This 60US->1031 binding is inference.
    ani_clock::Snapshot followClock(const Animation &root, const ani_clock::Snapshot &, bool loop,
                                   const std::vector<int32_t> *controllerDelays = nullptr) const;
};
// Value-copyable host instance. Shared immutable delays keep Cursor's borrowed
// view valid across experimental transaction copies and vector relocation.
class AnimationPlayback {
    std::shared_ptr<const std::vector<int32_t>> delays_;
    ani_clock::Cursor cursor_;
  public:
    bool installed() const noexcept { return bool(delays_); }
    void clear() noexcept { delays_.reset(); cursor_ = {}; }
    ani_clock::Advance install(const Animation &, bool loop, float rate,
                              ani_clock::ClockPolicy, uint64_t tick);
    ani_clock::Advance advance(uint64_t tick, bool paused);
    ani_clock::Snapshot setRate(float rate) { return cursor_.setRate(rate); }
    const ani_clock::Snapshot &snapshot() const { return cursor_.snapshot(); }
};
Animation decodeAni(const Bytes &raw, const std::string &path);
struct Pixels {
    int width = 0, height = 0, x = 0, y = 0, logicalWidth = 0, logicalHeight = 0;
    Bytes rgba;
};
Pixels decodeImg(const Bytes &raw, int frame);
struct NpkEntry {
    std::filesystem::path archive;
    uint64_t offset = 0;
    uint32_t length = 0;
};
class Assets {
    struct StaticManifestEntry {
        uint64_t size = 0;
        std::string sha256;
        std::filesystem::path file;
    };
    struct VerifiedStaticFile {
        uintmax_t size = 0;
        std::filesystem::file_time_type modified;
    };
    std::filesystem::path root_;
    std::vector<std::filesystem::path> roots_;
    std::unordered_map<std::string, std::vector<NpkEntry>> entries_;
    std::unordered_map<std::string, std::shared_ptr<Bytes>> blobs_;
    std::unordered_map<std::string, std::shared_ptr<Animation>> animations_;
    Pvf &pvf_;
    mutable Json reads_ = Json::object();
    bool manifestBound_ = false;
    std::unordered_map<std::string, StaticManifestEntry> staticManifest_;
    mutable std::unordered_map<std::string, VerifiedStaticFile> verifiedStaticFiles_;
    mutable std::unordered_set<std::string> consumedArchives_;
    void bindManifest(const Json &manifest);
    void indexArchives();
    void verifyStaticFile(const std::filesystem::path &file, bool forceHash = false) const;
    Bytes verifiedStaticBytes(const std::filesystem::path &file) const;
    Bytes verifiedStaticRange(const std::filesystem::path &file, uint64_t offset, size_t length) const;

  public:
    Json errors = Json::array();
    Assets(std::filesystem::path root, Pvf &pvf);
    // Compatibility constructors are explicitly unbound. Runtime profiles must
    // use the manifest constructor to bind consumers to the fingerprinted bytes.
    Assets(std::vector<std::filesystem::path> roots, Pvf &pvf);
    Assets(std::vector<std::filesystem::path> roots, Pvf &pvf, const Json &manifest);
    bool manifestBound() const { return manifestBound_; }
    std::filesystem::path staticFile(const std::filesystem::path &relative) const;
    // Exact loose-file bytes are hashed after reading. Prefer this over opening
    // a returned staticFile path in a consumer. External writes/hot replacement
    // are unsupported; metadata checks do not claim an atomic filesystem snapshot.
    Bytes staticBytes(const std::filesystem::path &relative) const;
    Bytes blob(std::string path, const std::string &archive = "") const;
    std::shared_ptr<Animation> animation(const std::string &path);
    Pixels pixels(std::string path, int frame);
    bool has(std::string path) const;
    size_t count() const { return entries_.size(); }
    const auto &entries() const { return entries_; }
    const std::filesystem::path &root() const { return root_; }
    const Json &reads() const { return reads_; }
};
} // namespace dnf
