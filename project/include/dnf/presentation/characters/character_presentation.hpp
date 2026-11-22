#pragma once
#include "dnf/resources.hpp"
#include <optional>

namespace dnf {
struct Actor;
struct CharacterAppearance;

// Borrowed animation paths are valid only during the synchronous sink call.
// Image overrides and optional clock snapshots are owned by this request.
struct CharacterAnimationRequest {
    const std::string &path;
    double elapsedMs = 0, x = 0, y = 0;
    int direction = 1;
    bool loop = true;
    std::string imageOverride;
    int frameOverride = -1;
    std::optional<ani_clock::Snapshot> clock;
    double scaleX = 1, scaleY = 1;
};

class ICharacterDrawSink {
  public:
    virtual ~ICharacterDrawSink() = default;
    virtual void drawCharacterAnimation(const CharacterAnimationRequest &) = 0;
    // The backend owns issue deduplication, shared with its other consumers.
    virtual void reportCharacterIssue(const std::string &key, const Json &issue,
                                      bool unsupported) = 0;
};

// Composes source-authored body, equipment, costume and temporary skill layers.
// This object samples read-only actor state; it never advances a simulation
// clock, retires an instance or changes a normal gameplay/save ledger.
class CharacterPresentation {
    Assets &assets_;
    ICharacterDrawSink &sink_;

  public:
    CharacterPresentation(Assets &assets, ICharacterDrawSink &sink) noexcept
        : assets_(assets), sink_(sink) {}
    void draw(const Actor &, int64_t renderMs, double interpolation,
              const CharacterAppearance &, ani_render::RenderProfile,
              double cameraX = 0, double cameraY = 0,
              const std::string &bodyMotion = "");
};
} // namespace dnf
