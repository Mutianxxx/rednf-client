#include "dnf/resources.hpp"
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
static std::string archiveText(const std::string &s) {
#ifdef _WIN32
    if(s.empty()||MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,s.data(),int(s.size()),nullptr,0)>0)return s;
#endif
    return gbk(s);
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
Pvf::Pvf(std::filesystem::path path) : path_(std::move(path)) {
    if (std::filesystem::is_directory(path_)) {
        auto index = Json::parse(readFile(path_ / "index.json"));
        if (index.value("format", "") != "dnf-source-cache-v3") throw std::runtime_error("Unsupported source cache");
        normalizedCache_ = true;
        strings_ = index["strings"].get<std::vector<std::string>>();
        for (auto it=index["entries"].begin();it!=index["entries"].end();++it) {
            auto &e=it.value();
            entries_.emplace(it.key(),Entry{e["size"].get<uint32_t>(),0,e["offset"].get<uint64_t>()});
        }
        path_ /= "resources.bin";
        return;
    }
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
        auto name = normalize(gbk(r.text(n)));
        auto sz = r.get<uint32_t>(), c = r.get<uint32_t>(), off = r.get<uint32_t>();
        uint64_t pos = 56ull + len + off;
        if (pos + ((uint64_t(sz) + 3) & ~3ull) > size)
            throw std::runtime_error("PVF entry bounds");
        if (!entries_.emplace(name, Entry{sz, c, pos}).second)
            throw std::runtime_error("Duplicate PVF path");
    }
    auto raw = read("stringtable.bin");
    Cursor st{raw};
    auto cnt = st.get<uint32_t>();
    if (cnt > 10000000)
        throw std::runtime_error("String table limit");
    std::vector<uint32_t> offsets;
    for (uint32_t i = 0; i <= cnt; i++)
        offsets.push_back(st.get<uint32_t>());
    for (uint32_t i = 0; i < cnt; i++) {
        if (offsets[i] > offsets[i + 1] || offsets[i + 1] + 4ull > raw.size())
            throw std::runtime_error("String table bounds");
        Cursor t{raw, size_t(offsets[i]) + 4};
        strings_.push_back(gbk(t.text(offsets[i + 1] - offsets[i])));
    }
    if (has("n_string.lst")) {
        auto list = read("n_string.lst");
        Cursor q{list, 2};
        while (q.at + 10 <= list.size()) {
            q.get<uint8_t>();
            int id = q.get<int32_t>();
            q.get<uint8_t>();
            int s = q.get<int32_t>();
            if (s < 0 || size_t(s) >= strings_.size())
                continue;
            auto file = normalize(strings_[s]);
            if (!has(file))
                continue;
            auto b = read(file);
            std::istringstream lines(gbk(std::string(b.begin(), b.end())));
            std::string line;
            while (std::getline(lines, line)) {
                if (!line.empty() && line.back() == '\r')
                    line.pop_back();
                auto pos = line.find('>');
                if (pos != line.npos)
                    translations_[id][line.substr(0, pos)] = line.substr(pos + 1);
            }
        }
    }
}
bool Pvf::has(const std::string &n) const { return entries_.count(normalize(n)); }
Bytes Pvf::read(const std::string &n) const {
    auto i = entries_.find(normalize(n));
    if (i == entries_.end())
        throw std::runtime_error("Missing PVF: " + n);
    auto &e = i->second;
    if (normalizedCache_) {
        reads_[normalize(n)] = {{"normalized_cache",path_.u8string()},{"offset",e.offset},{"size",e.size}};
        return range(path_,e.offset,e.size);
    }
    auto b = decrypt(range(path_, e.offset, (uint64_t(e.size) + 3) & ~3ull), e.crc);
    b.resize(e.size);
    reads_[normalize(n)] = {{"pvf", path_.u8string()}, {"offset", e.offset}, {"size", e.size}, {"crc", e.crc}};
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
    Cursor r{b, 2};
    Script out;
    out.path = normalize(name);
    int link = -1;
    while (r.at < b.size()) {
        size_t off = r.at;
        auto type = r.get<uint8_t>();
        auto val = r.get<int32_t>();
        Json v = val;
        if (type == 4) {
            float f;
            std::memcpy(&f, &val, 4);
            v = std::isfinite(f) ? Json(f) : Json();
        }
        if (type == 5 || type == 6 || type == 7 || type == 8 || type == 10) {
            if (val < 0 || size_t(val) >= strings_.size())
                throw std::runtime_error("String index in " + name);
            v = strings_[val];
        }
        out.tokens.push_back({{"offset", off}, {"type", type}, {"raw", val}, {"value", v}});
        if (type == 5) {
            out.fields.push_back({v.get<std::string>(), Json::array(), off});
            link = -1;
        } else if (type == 9)
            link = val;
        else if (!out.fields.empty()) {
            if (type == 10 && link >= 0) {
                auto t = translations_.find(link);
                if (t != translations_.end()) {
                    auto it = t->second.find(v.get<std::string>());
                    if (it != t->second.end())
                        v = it->second;
                }
                link = -1;
            }
            out.fields.back().values.push_back(v);
        }
    }
    scriptCache_[key] = out;
    return out;
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
    if (!b.empty() && b[0]=='{') {
        auto j=Json::parse(b);
        if(j.value("format","")!="dnf-normalized-ani-v3")throw std::runtime_error("Unknown ANI cache");
        Animation a;a.path=path;a.globals=j["globals"];
        Json unconsumed=a.globals.value("unconsumed",Json::array());
        for(auto &n:j["frames"]){AniFrame f;f.image=n["image"];f.imageFrame=n["imageFrame"];f.x=n["x"];f.y=n["y"];f.duration=n["duration"];f.properties=n["properties"];
            for(auto &v:n["boxes"])f.boxes.push_back({v["type"],v["x"],v["y"],v["z"],v["w"],v["h"],v["d"]});
            if(f.properties.contains("unconsumed"))for(auto &v:f.properties["unconsumed"])unconsumed.push_back(v);
            a.duration+=f.duration;a.frames.push_back(std::move(f));}
        a.globals["source_unconsumed"]=unconsumed;
        return a;
    }
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
AniPose Animation::samplePose(double ms, bool loop, int frameOverride) const {
    AniPose out;
    if (frames.empty()) return out;
    double time = std::max(0.0, std::isfinite(ms) ? ms : 0.0);
    if (loop && duration > 0) time = std::fmod(time, double(duration));
    size_t index = frames.size() - 1;
    double start = 0;
    if (frameOverride >= 0) index = std::min(size_t(frameOverride), frames.size() - 1);
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
        if (props.contains("unconsumed")) for(auto &v:props["unconsumed"])p.unsupported.push_back(v);
        if (props.contains("source_unconsumed")) for(auto &v:props["source_unconsumed"])p.unsupported.push_back(v);
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
    out.nextFrame = index + 1 < frames.size() ? index + 1 : loop ? 0 : index;
    out.localTime = frameOverride >= 0 ? 0 : std::max(0.0, time - start);
    out.progress = frames[index].duration > 0 ?
        std::clamp(out.localTime / frames[index].duration, 0.0, 1.0) : 0;
    out.interpolated = frameOverride < 0 && current.value("10", false) && out.nextFrame != index;
    if (out.interpolated) {
        AniPose next = pose(out.nextFrame, effective(out.nextFrame));
        auto mix = [&](double a, double b) { return a + (b - a) * out.progress; };
        out.x = mix(out.x, next.x); out.y = mix(out.y, next.y);
        out.scaleX = mix(out.scaleX, next.scaleX); out.scaleY = mix(out.scaleY, next.scaleY);
        // Direct angular interpolation retains authored full rotations (e.g. 6.28).
        out.rotationRadians = mix(out.rotationRadians, next.rotationRadians);
        for (int c = 0; c < 4; ++c) out.rgba[c] = mix(out.rgba[c], next.rgba[c]);
    }
    return out;
}
Assets::Assets(std::filesystem::path root, Pvf &p) : root_(std::move(root)), pvf_(p) {
    for (auto folder : {"ImagePacks2", "SoundPacks"}) {
        auto dir = root_ / folder;
        if (!std::filesystem::exists(dir))
            continue;
        std::vector<std::filesystem::path> paths;
        for (auto &f : std::filesystem::directory_iterator(dir))
            if (normalize(f.path().extension().string()) == ".npk")
                paths.push_back(f.path());
        std::sort(paths.begin(), paths.end());
        for (auto &file : paths) {
            try {
                auto h = range(file, 0, 20);
                Cursor r{h};
                if (r.text(16) != "NeoplePack_Bill")
                    throw std::runtime_error("NPK signature");
                auto n = r.get<uint32_t>();
                if (n > 1000000)
                    throw std::runtime_error("NPK count");
                auto b = range(file, 20, size_t(n) * 264);
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
                    entries_[normalize(archiveText(name))].push_back({file, off, len});
                }
            } catch (const std::exception &e) {
                errors.push_back({{"archive", file.u8string()}, {"error", e.what()}});
            }
        }
    }
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
    std::string selectedArchive=archive;
    auto override=overrides_.find(p);
    if(selectedArchive.empty()&&override!=overrides_.end())selectedArchive=override->second;
    for (auto &e : i->second) {
        if (!selectedArchive.empty() && normalize(e.archive.filename().u8string()) != normalize(selectedArchive))
            continue;
        if (choice && selectedArchive.empty())
            throw std::runtime_error("Ambiguous NPK resource: " + p);
        choice = &e;
    }
    if (!choice)
        throw std::runtime_error("Archive override not found");
    reads_[p] = {{"archive", choice->archive.u8string()}, {"offset", choice->offset}, {"length", choice->length}};
    return range(choice->archive, choice->offset, choice->length);
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
