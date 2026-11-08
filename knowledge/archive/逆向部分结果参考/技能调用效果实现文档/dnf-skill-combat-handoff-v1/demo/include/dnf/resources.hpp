#pragma once
#include "json.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
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
    std::vector<Field> fields;
    Json tokens = Json::array();
    Json values(std::string tag) const;
    double number(std::string tag, double fallback = 0) const;
    std::string text(std::string tag, std::string fallback = "") const;
};
class Pvf {
    struct Entry {
        uint32_t size, crc;
        uint64_t offset;
    };
    std::filesystem::path path_;
    bool normalizedCache_ = false;
    std::unordered_map<std::string, Entry> entries_;
    std::vector<std::string> strings_;
    mutable std::unordered_map<std::string, Script> scriptCache_;
    mutable Json reads_ = Json::object();
    std::unordered_map<int, std::unordered_map<std::string, std::string>> translations_;

  public:
    explicit Pvf(std::filesystem::path path);
    bool has(const std::string &name) const;
    Bytes read(const std::string &name) const;
    Script script(const std::string &name) const;
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
    AniPose samplePose(double ms, bool loop, int frameOverride = -1) const;
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
    std::filesystem::path root_;
    std::unordered_map<std::string, std::vector<NpkEntry>> entries_;
    std::unordered_map<std::string, std::shared_ptr<Bytes>> blobs_;
    std::unordered_map<std::string, std::shared_ptr<Animation>> animations_;
    Pvf &pvf_;
    mutable Json reads_ = Json::object();
    std::unordered_map<std::string, std::string> overrides_;

  public:
    Json errors = Json::array();
    Assets(std::filesystem::path root, Pvf &pvf);
    void setOverrides(const Json &rules) { for (auto it=rules.begin();it!=rules.end();++it) overrides_[normalize(it.key())]=it.value().get<std::string>(); }
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
