#include "dnf/skill_preview_audio.hpp"
#include "dnf/audio.hpp"

namespace dnf {
namespace {
class AudioSkillSoundSink final : public SkillSoundSink {
    Audio audio_;
    int played_ = 0, rejected_ = 0;
  public:
    explicit AudioSkillSoundSink(Assets &assets) : audio_(assets) {}
    void play(const std::string &id) override {
        try {
            audio_.play(id);
            ++played_;
        } catch (const std::exception &) {
            // Unknown id or a dead device stays a diagnostic, never a crash.
            ++rejected_;
        }
    }
    int played() const override { return played_; }
    int rejected() const override { return rejected_; }
};
} // namespace

std::unique_ptr<SkillSoundSink> makeAudioSkillSoundSink(Assets &assets) {
    try {
        return std::make_unique<AudioSkillSoundSink>(assets);
    } catch (const std::exception &) {
        return nullptr;
    }
}
} // namespace dnf
