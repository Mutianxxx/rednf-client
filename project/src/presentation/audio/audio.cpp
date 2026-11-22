#include "dnf/audio.hpp"
#include <cmath>
#include <limits>
#include <set>
#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"
#undef STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"

namespace dnf {
namespace {
size_t busIndex(AudioKind kind) { return kind == AudioKind::Music ? 0 : kind == AudioKind::Ambient ? 1 : 2; }
float volume(float value) { return std::isfinite(value) ? std::clamp(value, 0.0f, 1.0f) : 1.0f; }
}
Audio::Audio(Assets &a) : assets_(a) {
    try {
        auto path = a.staticFile("audio.xml");
        catalog_ = AudioCatalog(a.staticBytes("audio.xml"), path.generic_u8string());
    } catch (const std::exception &e) { errors.push_back({{"stage", "catalog"}, {"error", e.what()}}); }
    SDL_AudioSpec spec{};
    spec.freq = 48000; spec.format = AUDIO_F32SYS; spec.channels = 2; spec.samples = 1024;
    spec.callback = callback; spec.userdata = this;
    device_ = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);
    if (device_) SDL_PauseAudioDevice(device_, 0);
    else errors.push_back({{"stage", "device"}, {"error", SDL_GetError()}});
}
Audio::~Audio() { if (device_) SDL_CloseAudioDevice(device_); }
void Audio::callback(void *u, Uint8 *stream, int len) {
    auto &self = *static_cast<Audio *>(u);
    float *out = reinterpret_cast<float *>(stream);
    const size_t n = size_t(std::max(0, len)) / sizeof(float);
    std::fill(out, out + n, 0);
    std::lock_guard<std::mutex> lock(self.stateMutex_);
    ++self.callbacks_; self.outputSamples_ += n;
    for (auto &v : self.voices_) {
        size_t total = v.sound->samples.size(), bus = busIndex(v.kind);
        const bool loop = v.kind == AudioKind::Music || v.kind == AudioKind::Ambient;
        const float gain = self.master_ * (v.kind == AudioKind::Music ? .17f * self.music_ :
                                          v.kind == AudioKind::Ambient ? .17f * self.ambient_ : .4f * self.effects_);
        for (size_t i = 0; i < n && total; ++i) {
            if (v.pos >= total) { if (!loop) break; v.pos = 0; ++v.loops; }
            float value = v.sound->samples[v.pos++] * gain;
            out[i] += value; ++v.mixedSamples; ++self.busSamples_[bus];
            if (std::abs(value) > 1e-8f) { ++v.nonzeroSamples; ++self.busNonzero_[bus]; }
        }
    }
    self.voices_.erase(std::remove_if(self.voices_.begin(), self.voices_.end(), [](const Voice &v) {
        return v.kind == AudioKind::Effect && v.pos >= v.sound->samples.size();
    }), self.voices_.end());
    for (size_t i = 0; i < n; ++i) {
        out[i] = out[i] / (1.0f + std::abs(out[i]));
        self.peakOutput_ = std::max(self.peakOutput_, std::abs(out[i]));
        if (std::abs(out[i]) > 1e-8f) ++self.nonzeroOutput_;
    }
}
void Audio::record(const std::string &id, const char *status, const Json &detail) {
    std::lock_guard<std::mutex> lock(stateMutex_);
    Json row = {{"sequence", ++requestCount_}, {"id", id}, {"status", status}};
    for (auto it = detail.begin(); it != detail.end(); ++it) row[it.key()] = it.value();
    requests_.push_back(std::move(row));
    if (requests_.size() > 128) requests_.erase(requests_.begin());
}
bool Audio::active(const std::string &id, AudioKind kind) const {
    std::lock_guard<std::mutex> lock(stateMutex_);
    return std::any_of(voices_.begin(), voices_.end(), [&](const Voice &v) { return v.id == id && v.kind == kind; });
}
Audio::Prepared Audio::prepare(const std::string &id, AudioKind expected) {
    Prepared result; result.id = id; result.kind = expected;
    if (!device_) { record(id, "device_unavailable"); return result; }
    std::string resolved = id;
    std::set<std::string> visited;
    const AudioDeclaration *declaration = nullptr;
    for (int depth = 0; depth < 16; ++depth) {
        if (!visited.insert(resolved).second) break;
        auto entries = catalog_.find(resolved);
        if (entries.empty()) break;
        seed_ = seed_ * 1664525 + 1013904223;
        declaration = entries[seed_ % entries.size()];
        if (declaration->kind != AudioKind::Random) break;
        uint64_t total = 0;
        for (const auto &item : declaration->items) total += uint64_t(std::max(0, item.weight));
        if (!total) { declaration = nullptr; break; }
        seed_ = seed_ * 1664525 + 1013904223;
        uint64_t pick = seed_ % total; bool found = false;
        for (const auto &item : declaration->items) {
            if (pick < uint64_t(std::max(0, item.weight))) { resolved = item.id; found = true; break; }
            pick -= uint64_t(std::max(0, item.weight));
        }
        declaration = nullptr;
        if (!found) break;
    }
    if (declaration && declaration->kind != expected) {
        record(id, "category_mismatch", {{"expected", audioKindName(expected)}, {"actual", audioKindName(declaration->kind)}});
        return result;
    }
    if (declaration) result.file = declaration->file;
    else if (expected == AudioKind::Effect && assets_.has(resolved)) result.file = resolved;
    if (result.file.empty()) {
        { std::lock_guard<std::mutex> lock(stateMutex_); ++missing_[id]; }
        record(id, "unresolved"); return result;
    }
    result.resolved = resolved;
    auto cached = cache_.find(result.file);
    if (cached != cache_.end()) { result.sound = cached->second; record(id, "prepared_cached", {{"file", result.file}}); return result; }
    std::string actualSource;
    try {
        Bytes raw;
        if (assets_.has(result.file)) { raw = assets_.blob(result.file); actualSource = "NPK:" + result.file; }
        else {
            auto relative = std::filesystem::u8path(result.file);
            auto local = assets_.staticFile(relative);
            if (!std::filesystem::exists(local)) {
                auto slash = result.file.find("music/");
                if (slash != result.file.npos) {
                    relative = std::filesystem::path("Music") / std::filesystem::u8path(result.file.substr(slash + 6));
                    local = assets_.staticFile(relative);
                }
            }
            actualSource = local.generic_u8string(); raw = assets_.staticBytes(relative);
        }
        if (raw.empty() || raw.size() > size_t(std::numeric_limits<int>::max())) throw std::runtime_error("empty or oversized audio source");
        auto sound = std::make_shared<Sound>();
        if (raw.size() >= 12 && std::memcmp(raw.data(), "RIFF", 4) == 0) {
            SDL_AudioSpec spec{}; Uint8 *pcm = nullptr; Uint32 length = 0;
            if (!SDL_LoadWAV_RW(SDL_RWFromConstMem(raw.data(), int(raw.size())), 1, &spec, &pcm, &length))
                throw std::runtime_error("WAV decode: " + std::string(SDL_GetError()));
            sound->sourceRate = spec.freq; sound->sourceChannels = spec.channels;
            SDL_AudioCVT cvt{};
            int status = SDL_BuildAudioCVT(&cvt, spec.format, spec.channels, spec.freq, AUDIO_F32SYS, 2, 48000);
            if (status < 0) { SDL_FreeWAV(pcm); throw std::runtime_error("WAV conversion setup"); }
            Bytes converted(size_t(length) * std::max(1, cvt.len_mult));
            std::memcpy(converted.data(), pcm, length); SDL_FreeWAV(pcm);
            cvt.buf = converted.data(); cvt.len = int(length);
            if (status && SDL_ConvertAudio(&cvt)) throw std::runtime_error("WAV resampling");
            size_t bytes = status ? size_t(cvt.len_cvt) : size_t(length);
            sound->samples.resize(bytes / sizeof(float)); std::memcpy(sound->samples.data(), converted.data(), bytes);
        } else {
            int channels = 0, rate = 0; short *pcm = nullptr;
            int n = stb_vorbis_decode_memory(raw.data(), int(raw.size()), &channels, &rate, &pcm);
            if (n <= 0 || !pcm || channels <= 0 || rate <= 0) { free(pcm); throw std::runtime_error("Vorbis decode"); }
            sound->sourceRate = rate; sound->sourceChannels = channels;
            size_t count = size_t(n) * 48000 / rate;
            sound->samples.resize(count * 2);
            for (size_t i = 0; i < count; ++i) {
                double t = double(i) * rate / 48000;
                size_t k = std::min<size_t>(size_t(t), n - 1), k2 = std::min<size_t>(k + 1, n - 1);
                float f = float(t - k);
                for (int c = 0; c < 2; ++c) {
                    int ch = std::min(c, channels - 1);
                    sound->samples[i * 2 + c] = ((1 - f) * pcm[k * channels + ch] + f * pcm[k2 * channels + ch]) / 32768.0f;
                }
            }
            free(pcm);
        }
        if (sound->samples.empty() || sound->samples.size() % 2) throw std::runtime_error("empty or incomplete stereo PCM");
        cache_[result.file] = sound; result.sound = std::move(sound);
        record(id, "prepared", {{"resolved_id", resolved}, {"category", audioKindName(expected)}, {"file", result.file},
                                {"source", actualSource}, {"source_bytes", raw.size()}, {"source_rate", result.sound->sourceRate},
                                {"source_channels", result.sound->sourceChannels}, {"output_frames", result.sound->samples.size() / 2}});
    } catch (const std::exception &e) {
        { std::lock_guard<std::mutex> lock(stateMutex_); errors.push_back({{"stage", "decode"}, {"id", id}, {"sound", result.file}, {"source", actualSource}, {"error", e.what()}}); }
        record(id, "failed", {{"file", result.file}, {"source", actualSource}, {"error", e.what()}});
    }
    return result;
}
void Audio::append(const Prepared &p) {
    if (!p.sound) return;
    Voice voice; voice.sound = p.sound; voice.id = p.id; voice.resolved = p.resolved; voice.file = p.file; voice.kind = p.kind;
    voices_.push_back(std::move(voice));
}
void Audio::apply(const AudioScenePlan &plan) {
    // Caller owns controlMutex_. Decode outside stateMutex_, then commit only
    // successfully prepared voices. Identical live IDs retain playback phase.
    Prepared music;
    if (!plan.music.empty() && !active(plan.music, AudioKind::Music)) music = prepare(plan.music, AudioKind::Music);
    std::vector<Prepared> ambient, effects;
    for (const auto &id : plan.ambient) if (!active(id, AudioKind::Ambient)) ambient.push_back(prepare(id, AudioKind::Ambient));
    for (const auto &id : plan.effects) effects.push_back(prepare(id, AudioKind::Effect));
    for (const auto &issue : plan.issues) if (issue.contains("id")) {
        std::lock_guard<std::mutex> lock(stateMutex_); ++missing_[issue["id"].get<std::string>()];
    }
    std::lock_guard<std::mutex> lock(stateMutex_);
    scene_ = plan;
    voices_.erase(std::remove_if(voices_.begin(), voices_.end(), [&](const Voice &v) {
        return (v.kind == AudioKind::Music && v.id != plan.music) ||
               (v.kind == AudioKind::Ambient && std::find(plan.ambient.begin(), plan.ambient.end(), v.id) == plan.ambient.end());
    }), voices_.end());
    append(music); for (const auto &p : ambient) append(p);
    for (const auto &p : effects) {
        if (std::count_if(voices_.begin(), voices_.end(), [](const Voice &v) { return v.kind == AudioKind::Effect; }) < 32) append(p);
        else if (p.sound) ++droppedEffects_;
    }
}
void Audio::scene(const Json &ids) { std::lock_guard<std::mutex> lock(controlMutex_); apply(catalog_.scene(ids)); }
void Audio::music(const std::string &id) {
    std::lock_guard<std::mutex> lock(controlMutex_);
    AudioScenePlan plan; plan.music = id; if (!id.empty()) plan.sourceIds.push_back(id); apply(plan);
}
void Audio::play(const std::string &id, bool asMusic) {
    if (id.empty()) return;
    auto kind = catalog_.kind(id);
    if (asMusic || kind == AudioKind::Music) { music(id); return; }
    if (kind == AudioKind::Unknown) kind = AudioKind::Effect;
    std::lock_guard<std::mutex> lock(controlMutex_);
    if (kind == AudioKind::Ambient && active(id, kind)) return;
    auto prepared = prepare(id, kind); if (!prepared.sound) return;
    std::lock_guard<std::mutex> state(stateMutex_);
    if (kind != AudioKind::Effect || std::count_if(voices_.begin(), voices_.end(), [](const Voice &v) { return v.kind == AudioKind::Effect; }) < 32) append(prepared);
    else ++droppedEffects_;
}
void Audio::setVolumes(float master, float music, float effects, float ambient) {
    std::lock_guard<std::mutex> lock(stateMutex_);
    master_ = volume(master); music_ = volume(music); effects_ = volume(effects); ambient_ = volume(ambient);
}
Json Audio::volumes() const {
    std::lock_guard<std::mutex> lock(stateMutex_);
    return {{"master", master_}, {"music", music_}, {"effects", effects_}, {"ambient", ambient_}};
}
Json Audio::missing() const {
    std::lock_guard<std::mutex> lock(stateMutex_);
    Json out = Json::object(); for (const auto &i : missing_) out[i.first] = i.second; return out;
}
Json Audio::snapshot(bool includeCatalog) const {
    std::lock_guard<std::mutex> control(controlMutex_);
    std::lock_guard<std::mutex> lock(stateMutex_);
    Json voices = Json::array(), buses = Json::object(), missing = Json::object();
    for (const auto &v : voices_) voices.push_back({{"id", v.id}, {"resolved_id", v.resolved}, {"kind", audioKindName(v.kind)},
        {"file", v.file}, {"position_frames", v.pos / 2}, {"duration_frames", v.sound->samples.size() / 2},
        {"source_rate", v.sound->sourceRate}, {"source_channels", v.sound->sourceChannels}, {"loops", v.loops},
        {"mixed_samples", v.mixedSamples}, {"nonzero_mixed_samples", v.nonzeroSamples}});
    for (auto kind : {AudioKind::Music, AudioKind::Ambient, AudioKind::Effect}) {
        auto index = busIndex(kind);
        buses[audioKindName(kind)] = {{"mixed_samples", busSamples_[index]}, {"nonzero_mixed_samples", busNonzero_[index]}};
    }
    for (const auto &i : missing_) missing[i.first] = i.second;
    const char *driver = SDL_GetCurrentAudioDriver();
    Json out = {{"device_open", device_ != 0}, {"driver", driver ? driver : ""},
        {"output", {{"rate", 48000}, {"channels", 2}, {"format", "F32SYS"}, {"callback_frames", 1024}}},
        {"volumes", {{"master", master_}, {"music", music_}, {"effects", effects_}, {"ambient", ambient_}}},
        {"source_volume_policy", "local linear bus controls; source VOLUME_ADJUST/PRIORITY/LOOP_DELAY units unverified"},
        {"scene", scene_.snapshot()}, {"voices", voices}, {"buses", buses}, {"callback_count", callbacks_},
        {"output_samples", outputSamples_}, {"nonzero_output_samples", nonzeroOutput_}, {"peak_output", peakOutput_},
        {"request_count", requestCount_}, {"recent_requests", requests_}, {"dropped_effects", droppedEffects_},
        {"cache_files", cache_.size()}, {"catalog_declarations", catalog_.declarations().size()}, {"errors", errors}, {"unresolved_ids", missing},
        {"verification_boundary", "nonzero mixed PCM does not prove OS routing or human audibility"}};
    if (includeCatalog) out["catalog"] = catalog_.snapshot(true);
    return out;
}
} // namespace dnf
