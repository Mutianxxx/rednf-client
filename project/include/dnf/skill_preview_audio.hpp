#pragma once
#include <memory>
#include <string>
#include <vector>

namespace dnf {
class Assets;
// Sound boundary for the previewer. Implementations must never throw: a missing
// device or an unknown sound id is reported, not fatal.
class SkillSoundSink {
  public:
    virtual ~SkillSoundSink() = default;
    virtual void play(const std::string &id) = 0;
    virtual int played() const { return 0; }
    virtual int rejected() const { return 0; }
};

class NullSkillSoundSink : public SkillSoundSink {
    std::vector<std::string> ids_;
  public:
    void play(const std::string &id) override { ids_.push_back(id); }
    int played() const override { return int(ids_.size()); }
    const std::vector<std::string> &ids() const { return ids_; }
};

// Returns nullptr when the audio device cannot be created; callers fall back to
// NullSkillSoundSink and keep the preview running.
std::unique_ptr<SkillSoundSink> makeAudioSkillSoundSink(Assets &assets);
} // namespace dnf
