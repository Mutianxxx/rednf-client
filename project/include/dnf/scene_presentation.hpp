#pragma once
#include "resources.hpp"
namespace dnf {
struct ScenePresentationPlan {
    std::string owner, name, image, title;
    int imageFrame = 0, backgroundFrame = -1;
    std::array<int,2> imageSize{800,600}, backgroundSize{800,600};
    int titleDurationMs = 0;
    Json evidence = Json::object(), diagnostics = Json::array();
};
// TWN/DGN image is globally bound; entering title is relative to its owner.
// Source bytes/ordered fields and resource receipts remain in evidence.
ScenePresentationPlan prepareScenePresentation(Pvf &,Assets &,const Script &,std::string name);
struct ScenePresentationFrame {
    bool active = false, cutsceneVisible = false, blocked = false;
    uint8_t blackAlpha = 0;
    int64_t titleMs = -1;
};
class ScenePresentation {
    ScenePresentationPlan plan_;
    int64_t began_ = -1, ready_ = -1;
  public:
    // User policy: at least 1000ms loading art, then 300ms to black and
    // 400ms into the new scene. Not claimed as native timings.
    void begin(ScenePresentationPlan,int64_t wallMs);
    void ready(int64_t wallMs);
    void cancel() noexcept { began_ = ready_ = -1; }
    ScenePresentationFrame frame(int64_t wallMs) const;
    const ScenePresentationPlan &plan() const { return plan_; }
    Json snapshot(int64_t wallMs) const;
};
class Renderer;
void drawScenePresentation(Renderer &,const ScenePresentation &,int64_t wallMs);
Json runScenePresentationTests(Pvf &,Assets &);
} // namespace dnf
