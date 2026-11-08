#pragma once
#include "audio_catalog.hpp"
#include <SDL.h>
#include <array>
#include <map>
#include <mutex>
namespace dnf {
class Audio {
    struct Sound {
        std::vector<float> samples;
        int sourceRate = 0, sourceChannels = 0;
    };
    struct Voice {
        std::shared_ptr<Sound> sound;
        std::string id, resolved, file;
        AudioKind kind = AudioKind::Effect;
        size_t pos = 0;
        uint64_t loops = 0, mixedSamples = 0, nonzeroSamples = 0;
    };
    struct Prepared {
        std::shared_ptr<Sound> sound;
        std::string id, resolved, file;
        AudioKind kind = AudioKind::Unknown;
    };
    SDL_AudioDeviceID device_ = 0;
    Assets &assets_;
    AudioCatalog catalog_;
    // Decode/cache work does not hold the callback's state mutex.
    mutable std::mutex controlMutex_, stateMutex_;
    std::map<std::string, std::shared_ptr<Sound>> cache_;
    std::map<std::string, int> missing_;
    std::vector<Voice> voices_;
    uint32_t seed_ = 17;
    float master_ = 1, music_ = 1, effects_ = 1, ambient_ = 1;
    AudioScenePlan scene_;
    Json requests_ = Json::array();
    uint64_t requestCount_ = 0, callbacks_ = 0, outputSamples_ = 0, nonzeroOutput_ = 0, droppedEffects_ = 0;
    std::array<uint64_t, 3> busSamples_{}, busNonzero_{};
    float peakOutput_ = 0;
    static void callback(void *userdata, Uint8 *stream, int len);
    Prepared prepare(const std::string &id, AudioKind expected);
    void apply(const AudioScenePlan &plan);
    void record(const std::string &id, const char *status, const Json &detail = Json::object());
    bool active(const std::string &id, AudioKind kind) const;
    void append(const Prepared &prepared);

  public:
    // Control calls write this legacy field; snapshot() is the synchronized API.
    Json errors = Json::array();
    explicit Audio(Assets &a);
    ~Audio();
    Audio(const Audio &) = delete;
    Audio &operator=(const Audio &) = delete;
    void play(const std::string &id, bool music = false);
    // Screen music also clears map ambient voices.
    void music(const std::string &id);
    // Complete ordered MAP [sound] values; MUSIC and AMBIENT may appear in any order.
    void scene(const Json &ids);
    // Local linear controls 0..1; unknown source volume units stay untouched.
    void setVolumes(float master, float music, float effects, float ambient);
    Json volumes() const;
    Json missing() const;
    Json snapshot(bool includeCatalog = false) const;
};
} // namespace dnf
