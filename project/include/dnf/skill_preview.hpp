#pragma once
#include "character.hpp"
#include "resources.hpp"
#include "skill_data.hpp"
#include "skill_preview_combat.hpp"
#include "skill_preview_mapping.hpp"
#include "skill_preview_particles.hpp"
#include "skill_preview_timeline.hpp"
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace dnf {
class Assets;
class Pvf;
class Renderer;
struct CharacterAppearance;
struct EffectEventPlan;

// A rectangle drawn over the viewport while the box overlay is on.
struct OverlayBox {
    double x = 0, y = 0, w = 0, h = 0;
    int kind = 0; // 0 source attack volume, 1 reconstructed, 2 dummy hurt box
    std::string label;
    bool dashed = false;
};

// A skill demonstration session: no world, no level, no cooldown.
//
// 40JP decides what a skill looks like from the .ani frame table alone, and its
// timeline is an accumulated millisecond value. Keeping that shape here means
// the viewer has no simulation state to fall out of step with: the same elapsed
// time always produces the same picture, at any frame rate.
class SkillPreviewSession {
  public:
    SkillPreviewSession(Pvf &, Assets &, CharacterCatalog &, SkillMappingTable &);
    ~SkillPreviewSession();

    // Builds the character appearance only. No level, no equipment qualification,
    // no learning ledger — none of them affect how a skill is drawn.
    bool selectJob(int jobId, std::string &error);
    // Builds the timeline for one skill: body clock, attack volumes, dummies,
    // particles, and the ALS sub-chain plan.
    bool play(const SkillVisualMapping &, std::string &error);
    void advance(double realMilliseconds);
    void stepFrame(int direction);
    void reset();

    void draw(Renderer &, double cameraX, double cameraY);

    void setPaused(bool value) { paused_ = value; }
    void setSpeed(double value);
    void setFacing(int value);
    void setBoxesVisible(bool value) { boxesVisible_ = value; }
    void setLoop(bool value);
    void cycleDummy();

    bool paused() const { return paused_; }
    bool loop() const { return loop_; }
    bool hasJob() const { return hasJob_; }
    int jobId() const { return jobId_; }
    int facing() const { return facing_; }
    double speed() const { return speed_; }
    double ageMs() const;
    double durationMs() const;
    double stageX() const { return stageX_; }
    double stageY() const { return stageY_; }
    bool boxesVisible() const { return boxesVisible_; }
    int dummyCount() const { return dummyCount_; }
    size_t hitCount() const { return hitLog_.size(); }
    size_t particleCount() const;
    size_t layerCount() const;
    size_t volumeCount() const { return volumes_.size(); }
    const CharacterAppearance *appearance() const { return appearance_.get(); }
    const SkillVisualMapping *current() const { return current_; }
    const PreviewTimeline *timeline() const { return timeline_.get(); }
    const std::vector<OverlayBox> &boxes() const { return boxes_; }
    const std::vector<PreviewHit> &hits() const { return hitLog_; }
    const std::string &status() const { return status_; }
    const std::string &missing() const { return missing_; }
    std::vector<std::string> drainSounds();

    Json report() const;

  private:
    void clearPassState();
    void seedLayers(const SkillVisualMapping &);
    void appendLayerVolumes(const PreviewLayer &);
    void dropLayerVolumes(const std::string &instance, double liveMs);
    void dispatchFrame(const Animation &body, const FrameSpan &span);
    void rebuildBoxes();
    void detectHits(double fromMs, double toMs);
    void emitSounds(double fromMs, double toMs);
    const EffectEventPlan *effectPlan(const std::string &bodyPath);

    Pvf &pvf_;
    Assets &assets_;
    CharacterCatalog &catalog_;
    SkillMappingTable &table_;

    std::unique_ptr<CharacterAppearance> appearance_;
    std::unique_ptr<PreviewTimeline> timeline_;
    const SkillVisualMapping *current_ = nullptr;

    std::map<std::string, EffectEventPlan> effectPlans_;
    std::map<std::string, std::vector<size_t>> layerVolumes_;
    std::vector<PreviewVolume> volumes_;
    std::vector<PreviewDummy> dummies_;
    std::vector<PreviewHit> hitLog_;
    std::set<std::string> hitKeys_;
    std::vector<PtlProgram> particlePrograms_;
    PreviewParticleField particles_;

    int jobId_ = -1;
    int facing_ = 1;
    int dummyCount_ = 1;
    int frameVisits_ = 0;
    bool hasJob_ = false;
    bool paused_ = false;
    bool boxesVisible_ = true;
    bool loop_ = true;
    double speed_ = 1;
    double stageX_ = 600, stageY_ = 300;
    std::vector<OverlayBox> boxes_;
    std::vector<std::string> pendingSounds_;
    std::string status_, missing_;
};
} // namespace dnf
