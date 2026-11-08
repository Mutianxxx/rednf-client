#include "dnf/resources.hpp"
#include "dnf/content_profile.hpp"
#include <cmath>
#include <cstring>
#include <set>
#include <sstream>
#include <zlib.h>
#ifdef _WIN32
#include <windows.h>
#endif
namespace dnf {
std::string normalize(std::string s) {
    std::replace(s.begin(), s.end(), '\\', '/');
    for (char &c : s)
        if (c >= 'A' && c <= 'Z')
            c += 32;
    while (s.rfind("./", 0) == 0)
        s.erase(0, 2);
    // PVF scripts frequently resolve child resources through paths such as
    // passiveobject/mapobject/obstacle/../../../map/..., which must address
    // the archive's canonical path rather than remain a literal `..` key.
    s = std::filesystem::u8path(s).lexically_normal().generic_u8string();
    return s;
}
std::string gbk(const std::string &s) {
#ifdef _WIN32
    int n = MultiByteToWideChar(936, 0, s.data(), int(s.size()), nullptr, 0);
    std::wstring w(n, 0);
    MultiByteToWideChar(936, 0, s.data(), int(s.size()), w.data(), n);
    int m = WideCharToMultiByte(CP_UTF8, 0, w.data(), n, nullptr, 0, nullptr, nullptr);
    std::string out(m, 0);
    WideCharToMultiByte(CP_UTF8, 0, w.data(), n, out.data(), m, nullptr, nullptr);
    return out;
#else
    if (std::any_of(s.begin(), s.end(), [](unsigned char c) { return c >= 128; }))
        throw std::runtime_error("CP936 conversion unavailable on this platform");
    return s;
#endif
}
Bytes readFile(const std::filesystem::path &p) {
    std::ifstream f(p, std::ios::binary);
    if (!f)
        throw std::runtime_error("Cannot open: " + p.u8string());
    f.seekg(0, std::ios::end);
    auto n = f.tellg();
    if (n < 0)
        throw std::runtime_error("File size");
    Bytes b(size_t(n), 0);
    f.seekg(0);
    if (n && !f.read((char *)b.data(), n))
        throw std::runtime_error("Truncated file");
    return b;
}
void writeJson(const std::filesystem::path &p, const Json &v) {
    if (!p.parent_path().empty())
        std::filesystem::create_directories(p.parent_path());
    std::ofstream f(p);
    if (!f)
        throw std::runtime_error("Cannot write " + p.u8string());
    f << v.dump(2) << '\n';
    f.flush();
    if (!f)
        throw std::runtime_error("Failed writing " + p.u8string());
}
void Cursor::need(size_t n) const {
    if (at > b.size() || n > b.size() - at)
        throw std::runtime_error("Binary bounds at " + std::to_string(at));
}
std::string Cursor::text(size_t n) {
    need(n);
    std::string s((char *)b.data() + at, n);
    at += n;
    auto z = s.find('\0');
    if (z != s.npos)
        s.resize(z);
    return s;
}
std::string Cursor::sizedText() {
    auto n = get<int32_t>();
    if (n < 0 || n > 1048576)
        throw std::runtime_error("Invalid string size");
    return gbk(text(n));
}
static Bytes decrypt(Bytes b, uint32_t crc) {
    for (size_t i = 0; i + 4 <= b.size(); i += 4) {
        uint32_t v;
        std::memcpy(&v, b.data() + i, 4);
        v ^= 0x81A79011u ^ crc;
        v = (v >> 6) | (v << 26);
        std::memcpy(b.data() + i, &v, 4);
    }
    return b;
}
static Bytes range(const std::filesystem::path &p, uint64_t at, size_t n) {
    std::ifstream f(p, std::ios::binary);
    if (!f)
        throw std::runtime_error("Cannot open archive");
    f.seekg(at);
    Bytes b(n);
    if (n && !f.read((char *)b.data(), n))
        throw std::runtime_error("Archive bounds");
    return b;
}
Pvf::Pvf(std::filesystem::path path, std::string verifiedIdentity)
    : path_(std::move(path)), identity_(sha256File(path_)) {
    if(!verifiedIdentity.empty()&&verifiedIdentity!=identity_)
        throw std::runtime_error("PVF bytes changed after profile fingerprinting");
    auto head = range(path_, 0, 56);
    Cursor h{head};
    if (h.get<uint32_t>() != 36)
        throw std::runtime_error("PVF GUID length");
    h.at = 40;
    h.get<uint32_t>();
    auto len = h.get<uint32_t>(), crc = h.get<uint32_t>(), count = h.get<uint32_t>();
    if (count > 2000000 || len > 512 * 1024 * 1024)
        throw std::runtime_error("PVF header limits");
    auto tree = decrypt(range(path_, 56, len), crc);
    Cursor r{tree};
    auto size = std::filesystem::file_size(path_);
    for (uint32_t i = 0; i < count; i++) {
        r.get<uint32_t>();
        auto n = r.get<uint32_t>();
        if (n > 4096)
            throw std::runtime_error("PVF filename");
        auto literalPath = gbk(r.text(n));
        auto name = normalize(literalPath);
        auto sz = r.get<uint32_t>(), c = r.get<uint32_t>(), off = r.get<uint32_t>();
        uint64_t pos = 56ull + len + off;
        if (pos + ((uint64_t(sz) + 3) & ~3ull) > size)
            throw std::runtime_error("PVF entry bounds");
        if (!entries_.emplace(name, Entry{sz, c, pos, literalPath}).second)
            throw std::runtime_error("Duplicate PVF path");
    }
    stringTable_ = read("stringtable.bin");
    Cursor st{stringTable_};
    auto cnt = st.get<uint32_t>();
    if (cnt > 10000000)
        throw std::runtime_error("String table limit");
    stringOffsets_.reserve(size_t(cnt) + 1);
    for (uint32_t i = 0; i <= cnt; ++i)
        stringOffsets_.push_back(st.get<uint32_t>());
    for (uint32_t i = 0; i < cnt; ++i)
        if (stringOffsets_[i] > stringOffsets_[i + 1] ||
            stringOffsets_[i + 1] + 4ull > stringTable_.size())
            throw std::runtime_error("String table bounds");
    // Keep list order even for repeated ids: later files override duplicate keys.
    // Names and member bodies are resolved only when a type10 link uses this id.
    if (has("n_string.lst")) {
        const auto list = read("n_string.lst");
        Cursor q{list, 2};
        while (q.at + 10 <= list.size()) {
            q.get<uint8_t>();
            const auto id = q.get<int32_t>();
            q.get<uint8_t>();
            const auto index = q.get<int32_t>();
            if (index >= 0 && size_t(index) < cnt)
                translationMembers_[id].push_back(index);
        }
    }
}
const std::string &Pvf::stringAt(int32_t index, const std::string &context) const {
    if (index < 0 || size_t(index) + 1 >= stringOffsets_.size())
        throw std::runtime_error("String index in " + context);
    const auto cached = decodedStrings_.find(index);
    if (cached != decodedStrings_.end()) return cached->second;
    Cursor value{stringTable_, size_t(stringOffsets_[index]) + 4};
    auto text = gbk(value.text(stringOffsets_[index + 1] - stringOffsets_[index]));
    return decodedStrings_.emplace(index, std::move(text)).first->second;
}
const std::unordered_map<std::string, std::string> &Pvf::translationGroup(int id) const {
    const auto cached = translations_.find(id);
    if (cached != translations_.end()) return cached->second;
    // Publish only a complete group so a failed read cannot cache partial values.
    std::unordered_map<std::string, std::string> group;
    const auto indexed = translationMembers_.find(id);
    if (indexed != translationMembers_.end()) {
        for (const auto index : indexed->second) {
            const auto file = normalize(stringAt(index, "n_string.lst"));
            if (!has(file)) continue; // Same missing-member behavior as the original parser.
            const auto bytes = read(file);
            std::istringstream lines(gbk(std::string(bytes.begin(), bytes.end())));
            std::string line;
            while (std::getline(lines, line)) {
                if (!line.empty() && line.back() == '\r') line.pop_back();
                const auto separator = line.find('>');
                if (separator != line.npos)
                    group[line.substr(0, separator)] = line.substr(separator + 1);
            }
        }
    }
    return translations_.emplace(id, std::move(group)).first->second;
}

bool Pvf::has(const std::string &n) const { return entries_.count(normalize(n)); }
Bytes Pvf::read(const std::string &n) const {
    auto i = entries_.find(normalize(n));
    if (i == entries_.end())
        throw std::runtime_error("Missing PVF: " + n);
    auto &e = i->second;
    auto b = decrypt(range(path_, e.offset, (uint64_t(e.size) + 3) & ~3ull), e.crc);
    b.resize(e.size);
    reads_[normalize(n)] = {{"pvf", path_.u8string()}, {"package_identity", identity_},
                            {"literal_path",e.literalPath}, {"member_sha256",sha256(b)},
                            {"offset", e.offset}, {"size", e.size}, {"crc", e.crc}};
    return b;
}
Script Pvf::script(const std::string &name) const {
    auto key = normalize(name);
    auto cached = scriptCache_.find(key);
    if (cached != scriptCache_.end())
        return cached->second;
    auto b = read(name);
    if (b.size() < 2 || (b.size() - 2) % 5)
        throw std::runtime_error("Not token5: " + name);
    Script out;
    out.path = key;
    out.rawBytes = b;
    out.source = reads_.at(key);
    parseTokens(b, name, out.fields, out.tokens);
    scriptCache_[key] = out;
    return out;
}
void Pvf::parseTokens(const Bytes &bytes, const std::string &name, std::vector<Field> &fields,
                      Json &tokens, const std::unordered_set<std::string> *wanted) const {
    Cursor r{bytes, 2};
    int link = -1;
    bool selected = wanted == nullptr;
    while (r.at < bytes.size()) {
        const size_t offset = r.at;
        const auto type = r.get<uint8_t>();
        const auto raw = r.get<int32_t>();
        const bool stringType = type == 5 || type == 6 || type == 7 || type == 8 || type == 10;
        // Validate even unselected indices; projection must not hide malformed tokens.
        if (stringType && (raw < 0 || size_t(raw) + 1 >= stringOffsets_.size()))
            throw std::runtime_error("String index in " + name);
        Json value = raw;
        if (type == 5) {
            const auto &tag = stringAt(raw, name);
            selected = !wanted || wanted->count(normalize(tag)) != 0;
            link = -1;
            if (!selected) continue;
            value = tag;
            fields.push_back({tag, Json::array(), offset});
        } else {
            if (!selected) continue;
            if (type == 4) {
                float number;
                std::memcpy(&number, &raw, 4);
                value = std::isfinite(number) ? Json(number) : Json();
            } else if (stringType) value = stringAt(raw, name);
        }
        // Tokens retain the untranslated key, matching the lossless full parser.
        tokens.push_back({{"offset", offset}, {"type", type}, {"raw", raw}, {"value", value}});
        if (type == 5) continue;
        if (type == 9) link = raw;
        else if (!fields.empty()) {
            if (type == 10 && link >= 0) {
                const auto &translation = translationGroup(link);
                const auto found = translation.find(value.get<std::string>());
                if (found != translation.end()) value = found->second;
                link = -1;
            }
            fields.back().values.push_back(value);
        }
    }
}
ScriptFieldView Pvf::fieldView(const std::string &name, const std::vector<std::string> &wantedTags) const {
    ScriptFieldView view;
    view.path = normalize(name);
    view.rawBytes = read(name);
    view.source = reads_.at(view.path);
    if (view.rawBytes.size() < 2 || (view.rawBytes.size() - 2) % 5)
        throw std::runtime_error("Not token5: " + name);
    std::unordered_set<std::string> wanted;
    for (const auto &tag : wantedTags) wanted.insert(normalize(tag));
    parseTokens(view.rawBytes, name, view.fields, view.selectedTokens, &wanted);
    return view;
}
Json ScriptFieldView::values(std::string tag) const {
    tag = normalize(tag);
    for (const auto &field : fields)
        if (normalize(field.tag) == tag) return field.values;
    return Json::array();
}
Json Pvf::loadingStats() const {
    return {{"entries", entries_.size()}, {"string_count", stringOffsets_.empty() ? 0 : stringOffsets_.size() - 1},
            {"decoded_strings", decodedStrings_.size()}, {"translation_groups_indexed", translationMembers_.size()},
            {"translation_groups_loaded", translations_.size()}, {"scripts_cached", scriptCache_.size()},
            {"members_read", reads_.size()}, {"policy", "index_then_on_demand"}};
}

std::vector<std::string> Pvf::paths(const std::string &prefix, const std::string &suffix) const {
    std::vector<std::string> out;
    for (auto &e : entries_)
        if (e.first.rfind(prefix, 0) == 0 &&
            (suffix.empty() || (e.first.size() >= suffix.size() &&
                                e.first.compare(e.first.size() - suffix.size(), suffix.size(), suffix) == 0)))
            out.push_back(e.first);
    std::sort(out.begin(), out.end());
    return out;
}
Json Script::values(std::string tag) const {
    tag = normalize(tag);
    for (auto &f : fields)
        if (normalize(f.tag) == tag)
            return f.values;
    return Json::array();
}
double Script::number(std::string t, double d) const {
    auto v = values(t);
    return !v.empty() && v[0].is_number() ? v[0].get<double>() : d;
}
std::string Script::text(std::string t, std::string d) const {
    auto v = values(t);
    return !v.empty() && v[0].is_string() ? v[0].get<std::string>() : d;
}
static Json property(Cursor &r, int k, bool global) {
    switch (k) {
    case 0:
    case 1:
    case 10:
        return bool(r.get<uint8_t>());
    case 3:
    case 24:
    case 28:
        return r.get<uint16_t>();
    case 7: {
        auto a = r.get<float>(), b = r.get<float>();
        return Json::array({a, b});
    }
    case 8:
        return r.get<float>();
    case 9: {
        Json v = Json::array();
        for (int i = 0; i < 4; i++)
            v.push_back(r.get<uint8_t>());
        return v;
    }
    case 11: {
        int e = r.get<uint16_t>();
        Json j = {{"effect", e}};
        if (e == 5) {
            j["rgb"] = Json::array();
            for (int i = 0; i < 3; i++)
                j["rgb"].push_back(r.get<uint8_t>());
        } else if (e == 6) {
            auto x = r.get<int16_t>(), y = r.get<int16_t>();
            j["position"] = Json::array({x, y});
        } else if (e > 6)
            throw std::runtime_error("ANI graphic effect");
        return j;
    }
    case 12:
    case 23:
    case 26:
        return r.get<int32_t>();
    case 13:
        return r.get<uint16_t>();
    case 16:
        return r.sizedText();
    case 17:
    case 25:
        return true;
    case 27: {
        Json v = Json::array();
        for (int i = 0; i < 4; i++)
            v.push_back(r.get<int16_t>());
        return v;
    }
    case 18:
        if (global) {
            Json v;
            v["flag"] = r.get<uint8_t>();
            v["term"] = r.get<int32_t>();
            v["life"] = r.get<int32_t>();
            v["rgba"] = Json::array();
            for (int i = 0; i < 4; i++)
                v["rgba"].push_back(r.get<uint8_t>());
            v["effect"] = r.get<uint16_t>();
            return v;
        }
    }
    throw std::runtime_error("Unsupported ANI node " + std::to_string(k) + " at " + std::to_string(r.at));
}
Animation decodeAni(const Bytes &b, const std::string &path) {
    Cursor r{b};
    Animation a;
    a.path = path;
    int count = r.get<uint16_t>(), nr = r.get<uint16_t>();
    std::vector<std::string> names;
    for (int i = 0; i < nr; i++)
        names.push_back(r.sizedText());
    int ng = r.get<uint16_t>();
    for (int i = 0; i < ng; i++) {
        int k = r.get<uint16_t>();
        a.globals[std::to_string(k)] = property(r, k, true);
    }
    for (int i = 0; i < count; i++) {
        AniFrame f;
        int nb = r.get<uint16_t>();
        for (int j = 0; j < nb; j++) {
            Box q;
            q.type = r.get<uint16_t>();
            q.x = r.get<int32_t>();
            q.y = r.get<int32_t>();
            q.z = r.get<int32_t>();
            q.w = r.get<int32_t>();
            q.h = r.get<int32_t>();
            q.d = r.get<int32_t>();
            f.boxes.push_back(q);
        }
        int idx = r.get<int16_t>();
        if (idx >= 0) {
            f.imageFrame = r.get<uint16_t>();
            if (idx >= nr)
                throw std::runtime_error("ANI image index");
            f.image = names[idx];
        }
        f.x = r.get<int32_t>();
        f.y = r.get<int32_t>();
        int np = r.get<uint16_t>();
        for (int j = 0; j < np; j++) {
            int k = r.get<uint16_t>();
            f.properties[std::to_string(k)] = property(r, k, false);
        }
        if (f.properties.contains("12"))
            f.duration = f.properties["12"].get<int>();
        else if (a.globals.contains("12"))
            f.duration = a.globals["12"].get<int>();
        if (f.duration < 0)
            throw std::runtime_error("Negative ANI delay");
        a.duration += f.duration;
        a.frames.push_back(std::move(f));
    }
    if (r.at != b.size())
        throw std::runtime_error("ANI trailing bytes: " + path);
    return a;
}
size_t Animation::frameAt(int64_t ms, bool loop) const {
    if (frames.empty())
        return 0;
    if (loop && duration > 0)
        ms %= duration;
    ms = std::max<int64_t>(0, ms);
    int64_t end = 0;
    for (size_t i = 0; i < frames.size(); i++) {
        end += frames[i].duration;
        if (ms < end)
            return i;
    }
    return frames.size() - 1;
}
AniPose Animation::samplePose(double ms, bool loop, int frameOverride, ani_render::RenderProfile profile,
                              const ani_clock::Snapshot *clock) const {
    AniPose out;
    if (frames.empty()) return out;
    double time = std::max(0.0, std::isfinite(ms) ? ms : 0.0);
    if (profile == ani_render::RenderProfile::Inferred60Us1031) time = std::trunc(time);
    if (loop && duration > 0) time = std::fmod(time, double(duration));
    size_t index = frames.size() - 1;
    double start = 0;
    if (clock && frameOverride < 0) {
        if (clock->frame >= frames.size() || clock->nextFrame >= frames.size())
            throw std::out_of_range("ANI clock/source frame mismatch: " + path);
        index = clock->frame;
    }
    else if (frameOverride >= 0) index = std::min(size_t(frameOverride), frames.size() - 1);
    else {
        for (size_t i = 0; i < frames.size(); ++i) {
            double end = start + frames[i].duration;
            if (time < end) { index = i; break; }
            if (i + 1 < frames.size()) start = end;
        }
    }
    auto effective = [&](size_t i) {
        // A missing frame property resets to global/default, never previous frame.
        Json properties = globals;
        for (auto it = frames[i].properties.begin(); it != frames[i].properties.end(); ++it)
            properties[it.key()] = it.value();
        return properties;
    };
    auto pose = [&](size_t i, const Json &props) {
        AniPose p;
        p.image = frames[i].image; p.imageFrame = frames[i].imageFrame;
        p.x = frames[i].x; p.y = frames[i].y;
        if (props.contains("7")) { p.scaleX = props["7"][0]; p.scaleY = props["7"][1]; }
        if (props.contains("8")) p.rotationRadians = props["8"].get<double>();
        if (props.contains("9")) for (int c = 0; c < 4; ++c) p.rgba[c] = props["9"][c];
        if (props.contains("11")) {
            p.blend = props["11"].value("effect", 0);
            if (props["11"].contains("rgb"))
                for (int c = 0; c < 3; ++c) p.effectRgb[c] = props["11"]["rgb"][c];
        }
        if (props.contains("24")) p.flip = props["24"].get<int>();
        // Preserve and expose unconsumed rendering controls; never silently skip.
        for (const char *key : {"1", "3", "18", "25", "26", "27", "28"}) {
            if (!props.contains(key)) continue;
            const auto &v = props[key];
            if ((v.is_boolean() && !v.get<bool>()) || (v.is_number() && v.get<double>() == 0)) continue;
            p.unsupported.push_back({{"node", std::stoi(key)}, {"value", v}});
        }
        return p;
    };
    Json current = effective(index);
    out = pose(index, current);
    out.frame = index;
    out.nextFrame = clock && frameOverride < 0 ? clock->nextFrame :
        index + 1 < frames.size() ? index + 1 : loop ? 0 : index;
    out.localTime = frameOverride >= 0 ? 0 : clock ? double(clock->localMs) : std::max(0.0, time - start);
    const double span = clock && frameOverride < 0 ? double(clock->spanMs) : frames[index].duration;
    out.progress = span > 0 ? std::clamp(out.localTime / span, 0.0, 1.0) : 0;
    const auto numeric = [](const AniPose &p) {
        return ani_render::Pose{{p.x, p.y}, {p.scaleX, p.scaleY}, p.rotationRadians, p.rgba};
    };
    ani_render::SampleContext context;
    context.elapsed = out.localTime;
    context.span = span;
    context.requested = current.value("10", false);
    context.frozen = frameOverride >= 0;
    context.ended = clock && frameOverride < 0 ? clock->ended : !loop && time >= duration;
    context.hasNext = out.nextFrame != index;
    const AniPose next = context.requested && context.hasNext && !context.frozen ?
        pose(out.nextFrame, effective(out.nextFrame)) : out;
    const auto sampled = ani_render::samplePose(numeric(out), numeric(next), context, profile);
    out.interpolated = profile == ani_render::RenderProfile::Legacy1031 ?
        frameOverride < 0 && context.requested && context.hasNext : sampled.active;
    out.x = sampled.pose.position[0]; out.y = sampled.pose.position[1];
    out.scaleX = sampled.pose.rate[0]; out.scaleY = sampled.pose.rate[1];
    out.rotationRadians = sampled.pose.angle;
    out.rgba = sampled.pose.rgba;
    return out;
}
ani_clock::Snapshot Animation::followClock(const Animation &root, const ani_clock::Snapshot &clock, bool loop,
                                         const std::vector<int32_t> *controllerDelays) const {
    std::vector<int32_t> own, shared;
    own.reserve(frames.size()); shared.reserve(root.frames.size());
    for (const auto &frame : frames) own.push_back(frame.duration);
    if (controllerDelays) {
        if (controllerDelays->size()!=root.frames.size())throw std::invalid_argument("Controller timing does not match source body frames");
        shared=*controllerDelays;
    } else for (const auto &frame : root.frames) shared.push_back(frame.duration);
    return ani_clock::followRoot({own.data(), own.size(), loop, shared.data(), std::min(own.size(), shared.size())}, clock);
}
ani_clock::Advance AnimationPlayback::install(const Animation &animation, bool loop, float rate,
                                             ani_clock::ClockPolicy policy, uint64_t tick) {
    auto delays = std::make_shared<std::vector<int32_t>>();
    delays->reserve(animation.frames.size());
    for (const auto &frame : animation.frames) delays->push_back(frame.duration);
    ani_clock::Cursor candidate;
    auto result = candidate.install({delays->data(), delays->size(), loop}, rate, policy, tick);
    delays_ = std::move(delays); cursor_ = std::move(candidate);
    return result;
}
ani_clock::Advance AnimationPlayback::advance(uint64_t tick, bool paused) {
    const auto delta = ani_clock::millisecondsAtTick(tick) - ani_clock::millisecondsAtTick(tick - 1);
    return cursor_.advance({tick, uint32_t(delta), paused});
}
Assets::Assets(std::filesystem::path root, Pvf &p) : Assets(std::vector<std::filesystem::path>{std::move(root)},p) {}
Assets::Assets(std::vector<std::filesystem::path> roots, Pvf &p)
    : root_(roots.empty()?std::filesystem::path():roots.front()), roots_(std::move(roots)), pvf_(p) {
    indexArchives();
}
Assets::Assets(std::vector<std::filesystem::path> roots, Pvf &p, const Json &manifest)
    : root_(roots.empty()?std::filesystem::path():roots.front()), roots_(std::move(roots)), pvf_(p) {
    bindManifest(manifest);
    indexArchives();
}
namespace {
std::string staticFileKey(const std::filesystem::path &file) {
    return normalize(std::filesystem::absolute(file).lexically_normal().generic_u8string());
}
}
void Assets::bindManifest(const Json &manifest) {
    if (!manifest.is_array()) throw std::runtime_error("Bound static manifest must be an array");
    manifestBound_ = true;
    for (const auto &entry : manifest) {
        if (!entry.is_object() || !entry.contains("root") || !entry.at("root").is_number_integer() ||
            (!entry.at("root").is_number_unsigned() && entry.at("root").get<int64_t>() < 0) ||
            entry.at("root").get<uint64_t>() >= roots_.size() || !entry.contains("path") || !entry.at("path").is_string() ||
            !entry.contains("size") || !entry.at("size").is_number_integer() ||
            (!entry.at("size").is_number_unsigned() && entry.at("size").get<int64_t>() < 0) ||
            !entry.contains("sha256") || !entry.at("sha256").is_string())
            throw std::runtime_error("Invalid bound static manifest entry");
        const auto relative = std::filesystem::u8path(entry.at("path").get<std::string>());
        if (relative.has_root_path() || !fingerprintedStaticPath(relative))
            throw std::runtime_error("Bound static manifest path escapes its resource namespace");
        auto digest = entry.at("sha256").get<std::string>();
        if (digest.size() != 64 || !std::all_of(digest.begin(),digest.end(),[](char c) {
            return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
        })) throw std::runtime_error("Invalid bound static manifest SHA-256");
        const auto file = roots_.at(entry.at("root").get<size_t>()) / relative;
        const auto key = staticFileKey(file);
        if (!staticManifest_.emplace(key, StaticManifestEntry{entry.at("size").get<uint64_t>(),std::move(digest),file}).second)
            throw std::runtime_error("Duplicate bound static manifest path");
    }
}
void Assets::verifyStaticFile(const std::filesystem::path &file, bool forceHash) const {
    if (!manifestBound_) return;
    const auto key = staticFileKey(file);
    const auto expected = staticManifest_.find(key);
    if (expected == staticManifest_.end()) throw std::runtime_error("Static file was not fingerprinted: " + file.u8string());
    const auto size = std::filesystem::file_size(file);
    const auto modified = std::filesystem::last_write_time(file);
    const auto verified = verifiedStaticFiles_.find(key);
    if (!forceHash && verified != verifiedStaticFiles_.end() && verified->second.size == size && verified->second.modified == modified) return;
    if (size != expected->second.size || sha256File(file) != expected->second.sha256)
        throw std::runtime_error("Static file differs from its fingerprint: " + file.u8string());
    if (size != std::filesystem::file_size(file) || modified != std::filesystem::last_write_time(file))
        throw std::runtime_error("Static file changed while verifying: " + file.u8string());
    verifiedStaticFiles_[key] = {size,modified};
}
Bytes Assets::verifiedStaticBytes(const std::filesystem::path &file) const {
    auto raw = readFile(file);
    if (!manifestBound_) return raw;
    const auto expected = staticManifest_.find(staticFileKey(file));
    if (expected == staticManifest_.end()) throw std::runtime_error("Static file was not fingerprinted: " + file.u8string());
    if (raw.size() != expected->second.size || sha256(raw) != expected->second.sha256)
        throw std::runtime_error("Consumed static bytes differ from their fingerprint: " + file.u8string());
    return raw;
}
Bytes Assets::verifiedStaticRange(const std::filesystem::path &file, uint64_t offset, size_t length) const {
    verifyStaticFile(file);
    if (!manifestBound_) return range(file,offset,length);
    const auto size = std::filesystem::file_size(file);
    const auto modified = std::filesystem::last_write_time(file);
    const auto raw = range(file,offset,length);
    if (size != std::filesystem::file_size(file) || modified != std::filesystem::last_write_time(file))
        throw std::runtime_error("Static archive changed while reading: " + file.u8string());
    return raw;
}
void Assets::indexArchives() {
    if(roots_.empty()) throw std::runtime_error("No static resource roots");
    // Missing archives must fail as a changed manifest, rather than disappear
    // from the index and silently alter resource availability.
    if (manifestBound_) for (const auto &[key, expected] : staticManifest_)
        if (normalize(expected.file.extension().u8string()) == ".npk") verifyStaticFile(expected.file);
    for(const auto &root:roots_)
    for (auto folder : {"ImagePacks2", "SoundPacks"}) {
        auto dir = root / folder;
        if (!std::filesystem::exists(dir))
            continue;
        std::vector<std::filesystem::path> paths;
        for (auto &f : std::filesystem::directory_iterator(dir))
            if (normalize(f.path().extension().string()) == ".npk")
                paths.push_back(f.path());
        std::sort(paths.begin(), paths.end());
        for (auto &file : paths) {
            // Manifest violations are startup errors, not recoverable NPK parse
            // warnings. A later consumer cannot index newly introduced bytes.
            verifyStaticFile(file);
            try {
                auto h = verifiedStaticRange(file, 0, 20);
                Cursor r{h};
                if (r.text(16) != "NeoplePack_Bill")
                    throw std::runtime_error("NPK signature");
                auto n = r.get<uint32_t>();
                if (n > 1000000)
                    throw std::runtime_error("NPK count");
                auto b = verifiedStaticRange(file, 20, size_t(n) * 264);
                Cursor q{b};
                std::string key = "puchikon@neople dungeon and fighter ";
                while (key.size() < 255)
                    key += "DNF"[key.size() % 3];
                key.resize(256, 0);
                auto size = std::filesystem::file_size(file);
                for (uint32_t i = 0; i < n; i++) {
                    auto off = q.get<uint32_t>(), len = q.get<uint32_t>();
                    q.need(256);
                    std::string name;
                    for (int j = 0; j < 256; j++) {
                        char ch = b[q.at + j] ^ key[j];
                        if (ch == 0)
                            break;
                        name += ch;
                    }
                    q.at += 256;
                    if (off < 20ull + n * 264ull || uint64_t(off) + len > size)
                        throw std::runtime_error("NPK entry bounds");
                    entries_[normalize(gbk(name))].push_back({file, off, len});
                }
            } catch (const std::exception &e) {
                // A detected content change is fatal even if it happened after
                // the initial index verification, during a later range read.
                verifyStaticFile(file);
                errors.push_back({{"archive", file.u8string()}, {"error", e.what()}});
            }
        }
    }
}
std::filesystem::path Assets::staticFile(const std::filesystem::path &relative) const {
    if(relative.has_root_path()) throw std::runtime_error("Static resource path must be relative");
    const auto normalized=relative.lexically_normal();
    for(const auto &part:normalized) if(part=="..") throw std::runtime_error("Static resource path escapes root");
    if(!fingerprintedStaticPath(normalized)) throw std::runtime_error("Static resource namespace is outside the fingerprint manifest: "+relative.u8string());
    std::filesystem::path found;
    for(const auto &root:roots_) {
        const auto file=root/normalized;
        if(!std::filesystem::is_regular_file(file)) {
            if (manifestBound_ && staticManifest_.count(staticFileKey(file)))
                throw std::runtime_error("Fingerprint-declared loose resource is missing: " + file.u8string());
            continue;
        }
        verifyStaticFile(file);
        if(!found.empty()&&sha256File(found)!=sha256File(file)) throw std::runtime_error("Ambiguous loose static resource: "+relative.u8string());
        if(found.empty()) found=file;
    }
    return found.empty()?root_/normalized:found;
}
Bytes Assets::staticBytes(const std::filesystem::path &relative) const {
    return verifiedStaticBytes(staticFile(relative));
}
bool Assets::has(std::string p) const {
    p = normalize(p);
    return entries_.count(p) || entries_.count("sprite/" + p);
}
Bytes Assets::blob(std::string p, const std::string &archive) const {
    p = normalize(p);
    if (p.empty())
        throw std::runtime_error("Empty NPK resource path (caller must handle source placeholders)");
    auto i = entries_.find(p);
    if (i == entries_.end())
        i = entries_.find("sprite/" + p);
    if (i == entries_.end())
        throw std::runtime_error("Missing NPK resource: " + p);
    const NpkEntry *choice = nullptr;
    for (auto &e : i->second) {
        if (!archive.empty() && normalize(e.archive.filename().u8string()) != normalize(archive))
            continue;
        if (choice)
            throw std::runtime_error("Ambiguous NPK resource: " + p + " (archive basename does not disambiguate roots)");
        choice = &e;
    }
    if (!choice)
        throw std::runtime_error("Archive override not found");
    const auto archiveKey = staticFileKey(choice->archive);
    verifyStaticFile(choice->archive, consumedArchives_.count(archiveKey) == 0);
    auto raw = verifiedStaticRange(choice->archive, choice->offset, choice->length);
    consumedArchives_.insert(archiveKey);
    reads_[p] = {{"archive", choice->archive.u8string()}, {"offset", choice->offset}, {"length", choice->length},
        {"manifest_bound", manifestBound_}};
    if (manifestBound_) reads_[p]["archive_sha256"] = staticManifest_.at(archiveKey).sha256;
    return raw;
}
std::shared_ptr<Animation> Assets::animation(const std::string &name) {
    auto n = normalize(name);
    auto i = animations_.find(n);
    if (i != animations_.end())
        return i->second;
    auto a = std::make_shared<Animation>(decodeAni(pvf_.read(n), n));
    animations_[n] = a;
    return a;
}
Pixels Assets::pixels(std::string path, int index) {
    path = normalize(path);
    auto it = blobs_.find(path);
    if (it == blobs_.end())
        it = blobs_.emplace(path, std::make_shared<Bytes>(blob(path))).first;
    const Bytes &b = *it->second;
    try {
        return decodeImg(b, index);
    } catch (const std::exception &e) {
        throw std::runtime_error("IMG " + path + " frame=" + std::to_string(index) + ": " + e.what());
    }
}
Pixels decodeImg(const Bytes &b, int index) {
    Cursor r{b};
    auto sig = r.text(16);
    bool legacy = b.size() >= 17 && std::memcmp(b.data(), "Neople Image File", 17) == 0;
    if (!legacy && sig != "Neople Img File")
        throw std::runtime_error("IMG signature");
    auto indexLength = r.get<uint64_t>();
    int ver = r.get<int32_t>(), count = r.get<int32_t>();
    if (count < 0 || count > 100000 || index < 0 || index >= count)
        throw std::runtime_error("IMG frame bounds");
    if (ver != 1 && ver != 2 && ver != 4)
        throw std::runtime_error("IMG version " + std::to_string(ver));
    Bytes palette;
    if (ver == 4) {
        int n = r.get<int32_t>();
        if (n < 0 || n > 65536)
            throw std::runtime_error("Palette count");
        r.need(n * 4);
        palette.assign(b.begin() + r.at, b.begin() + r.at + n * 4);
        r.at += n * 4;
    }
    struct F {
        int type = 0, mode = 0, w = 0, h = 0, length = 0, x = 0, y = 0, fw = 0, fh = 0, link = -1;
        size_t at = 0;
    };
    auto rawSize = [&](const F &f) -> size_t {
        if (f.type >= 18) return size_t((f.w + 3) / 4) * ((f.h + 3) / 4) * (f.type == 18 ? 8 : 16);
        return size_t(f.w) * f.h * (f.type == 16 ? 4 : !palette.empty() && f.type == 14 && f.mode == 6 ? 1 : 2);
    };
    std::vector<F> fs;
    size_t walked = 0;
    for (int i = 0; i < count; i++) {
        F f;
        f.type = r.get<int32_t>();
        if (f.type == 17) {
            f.link = r.get<int32_t>();
            walked += 8;
        } else {
            f.mode = r.get<int32_t>();
            f.w = r.get<int32_t>();
            f.h = r.get<int32_t>();
            f.length = r.get<int32_t>();
            f.x = r.get<int32_t>();
            f.y = r.get<int32_t>();
            f.fw = r.get<int32_t>();
            f.fh = r.get<int32_t>();
            if (f.w < 0 || f.h < 0 || int64_t(f.w) * f.h > 64 * 1024 * 1024 || f.length < 0)
                throw std::runtime_error("IMG dimensions");
            if (f.type < 14 || f.type > 20 || f.mode < 5 || f.mode > 7)
                throw std::runtime_error("IMG encoding");
            walked += 36;
            if (legacy && ver == 1) {
                f.at = r.at;
                size_t n = f.mode == 5 ? rawSize(f) : size_t(f.length);
                r.need(n);
                r.at += n;
            }
        }
        fs.push_back(f);
    }
    if (!legacy && indexLength != walked)
        throw std::runtime_error("IMG index length");
    if (!(legacy && ver == 1))
        for (auto &f : fs)
            if (f.type != 17) {
                f.at = r.at;
                size_t n = f.mode == 5 ? rawSize(f) : size_t(f.length);
                r.need(n);
                r.at += n;
            }
    std::set<int> seen;
    while (fs[index].type == 17) {
        if (!seen.insert(index).second)
            throw std::runtime_error("IMG cyclic link");
        index = fs[index].link;
        if (index < 0 || index >= count)
            throw std::runtime_error("IMG link bounds");
    }
    auto &f = fs[index];
    Pixels p;
    p.width = f.w;
    p.height = f.h;
    p.x = f.x;
    p.y = f.y;
    p.logicalWidth = f.fw;
    p.logicalHeight = f.fh;
    if (f.w == 0 || f.h == 0)
        return p;
    size_t expected = rawSize(f);
    Bytes data;
    if (f.mode == 5)
        data.assign(b.begin() + f.at, b.begin() + f.at + expected);
    else {
        data.resize(expected);
        uLongf n = data.size();
        if (uncompress(data.data(), &n, b.data() + f.at, f.length) != Z_OK)
            throw std::runtime_error("IMG zlib");
        data.resize(n);
    }
    if (f.type <= 16 && data.size() != expected)
        throw std::runtime_error("IMG decoded size");
    p.rgba.resize(size_t(f.w) * f.h * 4);
    if (f.type >= 18) {
        int blockBytes = f.type == 18 ? 8 : 16;
        size_t blocksX = (f.w + 3) / 4, blocksY = (f.h + 3) / 4;
        if (data.size() != blocksX * blocksY * blockBytes)
            throw std::runtime_error("DXT decoded size");
        for (size_t by = 0; by < blocksY; by++)
            for (size_t bx = 0; bx < blocksX; bx++) {
                const uint8_t *block = data.data() + (by * blocksX + bx) * blockBytes;
                const uint8_t *color = block + (f.type == 18 ? 0 : 8);
                uint16_t c0 = color[0] | uint16_t(color[1]) << 8, c1 = color[2] | uint16_t(color[3]) << 8;
                uint8_t colors[4][4];
                auto rgb565 = [](uint16_t c, uint8_t *out) {
                    out[0] = uint8_t(((c >> 11) & 31) * 255 / 31);
                    out[1] = uint8_t(((c >> 5) & 63) * 255 / 63);
                    out[2] = uint8_t((c & 31) * 255 / 31);
                    out[3] = 255;
                };
                rgb565(c0, colors[0]);
                rgb565(c1, colors[1]);
                for (int k = 0; k < 3; k++) {
                    if (c0 > c1 || f.type != 18) {
                        colors[2][k] = (2 * colors[0][k] + colors[1][k]) / 3;
                        colors[3][k] = (colors[0][k] + 2 * colors[1][k]) / 3;
                    } else {
                        colors[2][k] = (colors[0][k] + colors[1][k]) / 2;
                        colors[3][k] = 0;
                    }
                }
                colors[2][3] = 255;
                colors[3][3] = (c0 > c1 || f.type != 18) ? 255 : 0;
                uint32_t codes =
                    color[4] | uint32_t(color[5]) << 8 | uint32_t(color[6]) << 16 | uint32_t(color[7]) << 24;
                uint8_t alpha[8]{};
                uint64_t alphaBits = 0;
                if (f.type == 20) {
                    alpha[0] = block[0];
                    alpha[1] = block[1];
                    if (alpha[0] > alpha[1])
                        for (int i = 2; i < 8; i++)
                            alpha[i] = uint8_t(((8 - i) * alpha[0] + (i - 1) * alpha[1]) / 7);
                    else {
                        for (int i = 2; i < 6; i++)
                            alpha[i] = uint8_t(((6 - i) * alpha[0] + (i - 1) * alpha[1]) / 5);
                        alpha[6] = 0;
                        alpha[7] = 255;
                    }
                    for (int i = 0; i < 6; i++)
                        alphaBits |= uint64_t(block[2 + i]) << (i * 8);
                }
                for (int i = 0; i < 16; i++) {
                    int x = int(bx * 4 + i % 4), y = int(by * 4 + i / 4);
                    if (x >= f.w || y >= f.h)
                        continue;
                    int code = (codes >> (i * 2)) & 3;
                    auto dst = p.rgba.data() + (size_t(y) * f.w + x) * 4;
                    std::memcpy(dst, colors[code], 4);
                    if (f.type == 19)
                        dst[3] = uint8_t(((block[i / 2] >> ((i % 2) * 4)) & 15) * 17);
                    else if (f.type == 20)
                        dst[3] = alpha[(alphaBits >> (i * 3)) & 7];
                }
            }
        return p;
    }
    for (size_t i = 0; i < size_t(f.w) * f.h; i++) {
        uint8_t red, green, blue, alpha;
        if (f.type == 16) {
            blue = data[i * 4];
            green = data[i * 4 + 1];
            red = data[i * 4 + 2];
            alpha = data[i * 4 + 3];
        } else if (!palette.empty() && f.type == 14 && f.mode == 6) {
            size_t k = size_t(data[i]) * 4;
            if (k + 4 > palette.size())
                throw std::runtime_error("IMG palette bounds");
            blue = palette[k];
            green = palette[k + 1];
            red = palette[k + 2];
            alpha = palette[k + 3];
        } else {
            uint16_t v = data[i * 2] | uint16_t(data[i * 2 + 1]) << 8;
            if (f.type == 15) {
                red = ((v >> 8) & 15) * 17;
                green = ((v >> 4) & 15) * 17;
                blue = (v & 15) * 17;
                alpha = (v >> 12) * 17;
            } else {
                red = uint8_t(std::lround(((v >> 10) & 31) * 255.0 / 31));
                green = uint8_t(std::lround(((v >> 5) & 31) * 255.0 / 31));
                blue = uint8_t(std::lround((v & 31) * 255.0 / 31));
                alpha = (v >> 15) * 255;
            }
        }
        p.rgba[i * 4] = red;
        p.rgba[i * 4 + 1] = green;
        p.rgba[i * 4 + 2] = blue;
        p.rgba[i * 4 + 3] = alpha;
    }
    return p;
}
} // namespace dnf
