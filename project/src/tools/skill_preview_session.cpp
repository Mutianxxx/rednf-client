#include "dnf/skill_preview.hpp"
#include "dnf/appearance.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/renderer.hpp"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <stdexcept>

namespace dnf {
namespace {
namespace fs = std::filesystem;

std::string stemOf(const std::string &path) {
    return normalize(fs::u8path(path).stem().u8string());
}

// 40JP draws the ordered negative attachments, the composed body, then the
// ordered non-negative ones. Equal layers keep their insertion order.
void sortLayerIndices(const std::vector<PreviewLayer> &layers, std::vector<size_t> &order) {
    order.clear();
    for (size_t i = 0; i < layers.size(); ++i) order.push_back(i);
    std::stable_sort(order.begin(), order.end(),
                     [&](size_t lhs, size_t rhs) { return layers[lhs].order < layers[rhs].order; });
}

// Hit flash stays visible for this long after contact. Rendering only: 40JP's
// own flash lives in the target's hit reaction, which the viewer does not run.
constexpr double hitFlashMs = 150;

// A chained release carries one frame table per stage. Collect each stage's
// [ATTACK BOX] windows, then shift them onto the shared action clock. Cited
// reconstructed volumes belong to the stage the mapping selected as bodyAni.
std::vector<PreviewVolume> collectChainVolumes(Assets &assets, const SkillVisualMapping &mapping,
                                               const std::vector<PreviewBodyStage> &stages) {
    std::vector<PreviewVolume> all;
    for (const auto &stage : stages) {
        std::shared_ptr<Animation> animation;
        try {
            animation = assets.animation(stage.path);
        } catch (const std::exception &) {
            continue;
        }
        if (!animation) continue;
        SkillVisualMapping slice = mapping;
        if (stage.path != mapping.bodyAni) slice.reconstructedBoxes.clear();
        auto part = collectVolumes(assets, slice, animation.get(), stage.durationMs, {});
        for (auto &volume : part) {
            volume.startMs += stage.startMs;
            volume.endMs += stage.startMs;
        }
        all.insert(all.end(), part.begin(), part.end());
    }
    std::stable_sort(all.begin(), all.end(), [](const PreviewVolume &lhs, const PreviewVolume &rhs) {
        return lhs.startMs < rhs.startMs;
    });
    return all;
}
} // namespace

SkillPreviewSession::SkillPreviewSession(Pvf &pvf, Assets &assets, CharacterCatalog &catalog,
                                         SkillMappingTable &table)
    : pvf_(pvf), assets_(assets), catalog_(catalog), table_(table) {}

SkillPreviewSession::~SkillPreviewSession() = default;

bool SkillPreviewSession::selectJob(int jobId, std::string &error) {
    if (jobId < 0) {
        error = "no_job";
        return false;
    }
    try {
        // Only the appearance is needed to draw a skill. No level, no equipped
        // weapon qualification, no learning ledger: 40JP's release animation is
        // a property of the .ani, not of the character's progression.
        appearance_ = std::make_unique<CharacterAppearance>(
            defaultCharacterAppearance(pvf_, catalog_, CharacterIdentity{jobId, 0, 0}));
        jobId_ = jobId;
        hasJob_ = true;
        timeline_.reset();
        current_ = nullptr;
        clearPassState();
        status_ = "职业已就绪";
        missing_.clear();
        return true;
    } catch (const std::exception &failure) {
        error = failure.what();
        hasJob_ = false;
        appearance_.reset();
        status_ = std::string("外观构建失败: ") + failure.what();
        return false;
    }
}

void SkillPreviewSession::clearPassState() {
    boxes_.clear();
    pendingSounds_.clear();
    volumes_.clear();
    dummies_.clear();
    hitLog_.clear();
    hitKeys_.clear();
    layerVolumes_.clear();
    particlePrograms_.clear();
    particles_.clear();
    frameVisits_ = 0;
}

const EffectEventPlan *SkillPreviewSession::effectPlan(const std::string &bodyPath) {
    if (bodyPath.empty()) return nullptr;
    if (const auto found = effectPlans_.find(bodyPath); found != effectPlans_.end())
        return &found->second;
    // The ALS sidecar is the source of the sub-chain: which animation is
    // attached, at which layer, with which offset, at which frame
    // (anim_parser.cpp:1744-1788). A plan with no events is a plain leaf
    // animation, not a failure.
    auto inserted = effectPlans_.emplace(bodyPath, animationEffectEvents(pvf_, assets_, bodyPath));
    return &inserted.first->second;
}

void SkillPreviewSession::appendLayerVolumes(const PreviewLayer &layer) {
    const size_t first = volumes_.size();
    const SkillVisualMapping empty;
    auto added = collectVolumes(assets_, empty, nullptr, 0, {layer});
    volumes_.insert(volumes_.end(), added.begin(), added.end());
    if (volumes_.size() > first) {
        auto &indices = layerVolumes_[layer.instance];
        for (size_t index = first; index < volumes_.size(); ++index) indices.push_back(index);
    }
}

void SkillPreviewSession::dropLayerVolumes(const std::string &instance, double absoluteEndMs) {
    const auto found = layerVolumes_.find(instance);
    if (found == layerVolumes_.end()) return;
    for (size_t index : found->second)
        if (index < volumes_.size()) volumes_[index].endMs = std::min(volumes_[index].endMs, absoluteEndMs);
    layerVolumes_.erase(found);
}

void SkillPreviewSession::seedLayers(const SkillVisualMapping &mapping) {
    if (!timeline_) return;
    timeline_->persistents.clear();
    const auto *plan = effectPlan(timeline_->bodyPath);
    // Entities that stay on the field own their animation for the whole
    // action, so the matching effect file must not also play as a plain layer
    // (the sword array would flicker at the caster's feet).
    const auto persistentPath = [&](const std::string &path) {
        for (const auto &entity : mapping.persistents)
            if (entity.path == path) return true;
        return false;
    };
    for (const auto &entity : mapping.persistents) {
        PreviewPersistent persistent;
        persistent.path = entity.path;
        persistent.kind = entity.kind == PersistentKind::Orbit ? PreviewPersistentKind::Orbit
                          : entity.kind == PersistentKind::AirSword ? PreviewPersistentKind::AirSword
                                                                   : PreviewPersistentKind::GroundField;
        persistent.count = std::max(1, entity.count);
        persistent.radius = entity.radius;
        persistent.angularDegPerSec = entity.angularDegPerSec;
        persistent.phaseDeg = entity.phaseDeg;
        persistent.offset = {entity.offsetX, entity.offsetY};
        persistent.evidence = entity.evidence;
        persistent.clock.reset();
        timeline_->persistents.push_back(std::move(persistent));
    }
    // A layer the ALS sidecar schedules is created by dispatchFrame when the
    // body reaches its frame. Only untimed layers are seeded here, and they
    // start at the release stage the file stem names instead of all at once.
    const bool hasAls = plan && !plan->events.empty();
    if (hasAls) return;
    if (mapping.effectLayers.empty()) {
        // Fallback for a row built before the layer plan existed: keep the old
        // stem-prefix behaviour rather than dropping the effect entirely.
        int index = 0;
        for (const auto &path : mapping.effects) {
            if (persistentPath(path)) continue;
            PreviewLayer layer;
            layer.path = path;
            layer.kind = PreviewLayerKind::EffectFront;
            layer.order = 0;
            layer.instance = "stem:" + std::to_string(index++);
            layer.evidence = "stem-prefix; order inferred";
            try {
                layer.lifeMs = animationDurationMs(*assets_.animation(path));
            } catch (const std::exception &) {
                continue;
            }
            timeline_->layers.push_back(layer);
        }
        for (const auto &layer : timeline_->layers) appendLayerVolumes(layer);
        return;
    }
    const double actionMs = timeline_->durationMs > 0 ? timeline_->durationMs : 0;
    for (const auto &planned : mapping.effectLayers) {
        if (planned.timed) continue; // created on its own frame by dispatchFrame
        if (persistentPath(planned.path)) continue;
        PreviewLayer layer;
        layer.path = planned.path;
        layer.kind = PreviewLayerKind::EffectFront;
        layer.order = planned.alsLayer;
        layer.offset = {planned.offsetX, planned.offsetY, planned.offsetZ};
        layer.birthMs = actionMs > 0 ? planned.birthRatio * actionMs : 0;
        layer.instance = planned.instance;
        layer.loop = planned.loop;
        layer.evidence = planned.evidence;
        try {
            layer.lifeMs = animationDurationMs(*assets_.animation(planned.path));
        } catch (const std::exception &) {
            continue;
        }
        // A layer that starts later still has to be reachable: clamp the birth
        // inside the action so it cannot appear only after the loop restarts.
        if (actionMs > 0 && layer.birthMs >= actionMs) layer.birthMs = actionMs * 0.9;
        layer.clock.ageMs = 0;
        timeline_->layers.push_back(layer);
    }
    for (const auto &layer : timeline_->layers) appendLayerVolumes(layer);
}

void SkillPreviewSession::dispatchFrame(const Animation &body, const FrameSpan &span) {
    (void)body;
    const auto *plan = effectPlan(timeline_->bodyPath);
    if (!plan) return;
    for (const auto &event : plan->events) {
        if (event.frame != int(span.index)) continue;
        if (event.kind == EffectEventKind::Remove) {
            for (auto it = timeline_->layers.begin(); it != timeline_->layers.end(); ++it) {
                if (it->instance != event.instance) continue;
                dropLayerVolumes(it->instance, span.startMs);
                timeline_->layers.erase(it);
                break;
            }
            continue;
        }
        const bool oneShot = event.kind == EffectEventKind::DrawOnly ||
                             event.kind == EffectEventKind::DrawOnlyFollowParent;
        if (!oneShot && !event.instance.empty()) {
            const bool exists = std::any_of(timeline_->layers.begin(), timeline_->layers.end(),
                                            [&](const PreviewLayer &layer) {
                                                return layer.instance == event.instance;
                                            });
            if (exists) continue;
        }
        PreviewLayer layer;
        layer.path = event.animation;
        layer.kind = PreviewLayerKind::EffectFront;
        layer.order = event.layer;
        layer.offset = {double(event.offsetX), double(event.offsetY), double(event.offsetZ)};
        layer.birthMs = span.startMs;
        layer.instance = oneShot ? std::string() : event.instance;
        layer.evidence = oneShot ? "als:draw-only@" + std::to_string(event.frame)
                                 : "als:add@" + std::to_string(event.frame);
        try {
            const auto animation = assets_.animation(layer.path);
            layer.lifeMs = animationDurationMs(*animation);
            layer.loop = !oneShot && animation->globals.value("0", false);
        } catch (const std::exception &) {
            continue;
        }
        timeline_->layers.push_back(layer);
        appendLayerVolumes(timeline_->layers.back());
    }
}

bool SkillPreviewSession::play(const SkillVisualMapping &mapping, std::string &error) {
    if (!hasJob_) {
        error = "no_job";
        status_ = "先选择职业";
        return false;
    }
    current_ = &mapping;
    missing_ = mapping.missing;
    clearPassState();

    auto timeline = std::make_unique<PreviewTimeline>();
    timeline->loop = loop_;
    // A chained release is laid out end to end: every stage starts where the
    // previous one ends, so the whole chain is one continuous action clock.
    // A single-stage action keeps bodyPath/durationMs and no stages.
    if (mapping.bodyChain.size() > 1) {
        double at = 0;
        for (const auto &path : mapping.bodyChain) {
            PreviewBodyStage stage;
            stage.path = path;
            stage.startMs = at;
            try {
                stage.durationMs = animationDurationMs(*assets_.animation(path));
            } catch (const std::exception &) {
                stage.durationMs = 0;
            }
            // A stage with no frames contributes nothing; skip it rather than
            // inserting a blank gap in the middle of the action.
            if (stage.durationMs <= 0) continue;
            stage.startMs = at;
            at += stage.durationMs;
            timeline->stages.push_back(std::move(stage));
        }
        if (!timeline->stages.empty()) {
            timeline->bodyPath = timeline->stages.front().path;
            timeline->durationMs = at;
        }
    }
    std::shared_ptr<Animation> body;
    if (timeline->stages.empty() && !mapping.bodyAni.empty()) {
        try {
            body = assets_.animation(mapping.bodyAni);
            timeline->bodyPath = mapping.bodyAni;
            timeline->durationMs = animationDurationMs(*body);
        } catch (const std::exception &failure) {
            error = failure.what();
            timeline->bodyPath.clear();
            timeline->durationMs = 0;
        }
    }
    timeline_ = std::move(timeline);

    // Body + cited reconstructed volumes first; layer volumes are appended when
    // each ALS child appears, so their time windows follow the real attach frame.
    if (!timeline_->stages.empty())
        volumes_ = collectChainVolumes(assets_, mapping, timeline_->stages);
    else
        volumes_ = collectVolumes(assets_, mapping, body ? body.get() : nullptr,
                                  timeline_->durationMs, {});

    // Skill particles are one-shot bursts emitted when the action starts.
    // Programs that fail to parse stay in the list with their reason so the
    // report can say why nothing was emitted instead of silently dropping them.
    for (const auto &path : mapping.particles) {
        auto program = readPtl(pvf_, path);
        if (program.valid())
            particles_.spawn(program, stageX_ + facing_ * 20.0, stageY_ - 40.0,
                             0x5eedu + unsigned(jobId_));
        particlePrograms_.push_back(std::move(program));
    }

    seedLayers(mapping);
    if (timeline_->durationMs <= 0)
        for (const auto &layer : timeline_->layers)
            timeline_->durationMs = std::max(timeline_->durationMs, layer.lifeMs);
    // A pure field skill (Spiral Nen) has no body motion at all: the entity is
    // the whole action, so give the clock a window long enough to show it.
    if (timeline_->durationMs <= 0 && !timeline_->persistents.empty())
        timeline_->durationMs = 2000;
    // A skill that leaves something on the field runs longer than its cast
    // animation: the lotus flowers sit on the ground and are detonated later.
    // NenFlower.ani is 700ms, so every placed layer would otherwise fire inside
    // the cast and the detonation would never be seen. Widening the action moves
    // the stage-spread births with it, and the body holds its final pose.
    if (!timeline_->persistents.empty() && timeline_->durationMs > 0 &&
        timeline_->durationMs < 2600) {
        const double scale = 2600.0 / timeline_->durationMs;
        timeline_->durationMs = 2600;
        for (auto &layer : timeline_->layers) layer.birthMs *= scale;
    }

    if (timeline_->durationMs <= 0 && timeline_->layers.empty()) {
        error = "no_playable_resource";
        status_ = "无可播放资源";
        rebuildBoxes();
        return false;
    }
    if (timeline_->bodyPath.empty())
        status_ = mapping.effects.empty() ? "无可播放资源" : "仅特效（缺身体动作）";
    else
        status_ = "播放";

    dummies_ = buildDummies(body ? body.get() : nullptr, stageX_, stageY_, facing_, dummyCount_);
    for (const auto &program : particlePrograms_)
        particles_.spawn(program, stageX_ + facing_ * 20.0, stageY_ - 40.0, 0x5eedu + unsigned(jobId_));
    if (body && !body->frames.empty()) {
        if (const auto span = spanAt(*body, 0)) dispatchFrame(*body, *span);
    }
    rebuildBoxes();
    paused_ = false;
    return true;
}

void SkillPreviewSession::detectHits(double fromMs, double toMs) {
    if (dummies_.empty()) return;
    for (size_t index = 0; index < volumes_.size(); ++index) {
        const auto &volume = volumes_[index];
        if (!volumeLiveIn(volume, fromMs, toMs)) continue;
        const auto attack = worldVolume(volume, stageX_, stageY_, facing_);
        for (const auto &dummy : dummies_) {
            CombatBox overlap;
            if (!previewOverlap(attack, dummy.hurt, &overlap)) continue;
            const auto key = volume.owner + "#" + std::to_string(volume.frame) + "@" +
                             std::to_string(dummy.index) + ":" + std::to_string(int(volume.startMs));
            if (!hitKeys_.insert(key).second) continue;
            hitLog_.push_back({timeline_ ? timeline_->ageMs : 0, index, dummy.index, overlap});
            if (hitLog_.size() > 256) hitLog_.erase(hitLog_.begin());
        }
    }
}

void SkillPreviewSession::advance(double realMilliseconds) {
    if (!timeline_) return;
    const double before = timeline_->ageMs;
    timeline_->paused = paused_;
    timeline_->advance(std::isnan(realMilliseconds) ? 0.0 : realMilliseconds, speed_);
    const double after = timeline_->ageMs;

    if (timeline_->looped) {
        // New pass: every ALS child, hit record and particle belongs to the pass
        // that just ended.
        timeline_->layers.clear();
        volumes_.clear();
        layerVolumes_.clear();
        hitKeys_.clear();
        hitLog_.clear();
        particles_.clear();
        std::shared_ptr<Animation> body;
        if (timeline_->bodyPath.empty() || !timeline_->stages.empty()) {
            // Chain volumes are rebuilt from the stage list below.
        } else {
            try {
                body = assets_.animation(timeline_->bodyPath);
            } catch (const std::exception &) {
            }
        }
        if (!timeline_->stages.empty())
            volumes_ = collectChainVolumes(assets_, *current_, timeline_->stages);
        else
            volumes_ = collectVolumes(assets_, *current_, body ? body.get() : nullptr,
                                      timeline_->durationMs, {});
        seedLayers(*current_);
        for (const auto &program : particlePrograms_)
            particles_.spawn(program, stageX_ + facing_ * 20.0, stageY_ - 40.0, 0x5eedu + unsigned(jobId_));
        particles_.seekFrom(timeline_->ageMs);
        if (body && !body->frames.empty()) {
            if (const auto span = spanAt(*body, timeline_->ageMs)) dispatchFrame(*body, *span);
        }
    } else if (after > before) {
        const double dt = after - before;
        // Attack windows are one or two frames wide, so the whole interval is
        // visited instead of sampling its endpoints. A chained release visits
        // each stage over its own slice of that interval.
        const auto visit = [&](const Animation &animation, double from, double to) {
            visitFrames(animation, from, to, [&](const FrameSpan &span) {
                ++frameVisits_;
                dispatchFrame(animation, span);
                // [SOUND] is a per-frame ANI property; 40JP plays it on the
                // frame that carries it (combat.cpp:2286-2291).
                const auto &properties = animation.frames[span.index].properties;
                if (properties.contains("16") && properties.at("16").is_string())
                    pendingSounds_.push_back(properties.at("16").get<std::string>());
            });
        };
        if (!timeline_->stages.empty()) {
            for (const auto &stage : timeline_->stages) {
                const double from = std::max(before, stage.startMs);
                const double to = std::min(after, stage.startMs + stage.durationMs);
                if (to <= from) continue;
                try {
                    const auto animation = assets_.animation(stage.path);
                    if (animation) visit(*animation, from - stage.startMs, to - stage.startMs);
                } catch (const std::exception &) {
                }
            }
        } else if (!timeline_->bodyPath.empty()) {
            try {
                const auto body = assets_.animation(timeline_->bodyPath);
                if (body) visit(*body, before, after);
            } catch (const std::exception &) {
            }
        }
        detectHits(before, after);
        particles_.advance(dt);
    }
    rebuildBoxes();
}

void SkillPreviewSession::rebuildBoxes() {
    boxes_.clear();
    if (!timeline_) return;
    const double now = timeline_->ageMs;
    // Targets first so a source attack volume is never hidden behind a hurt box
    // that happens to share its rectangle.
    for (const auto &dummy : dummies_)
        boxes_.push_back({dummy.hurt.x, dummy.hurt.y - dummy.hurt.z, dummy.hurt.w, dummy.hurt.h, 2,
                          dummy.sourced ? std::string() : std::string("推断"), true});
    for (const auto &volume : volumes_) {
        if (now < volume.startMs || now >= volume.endMs) continue;
        const auto box = worldVolume(volume, stageX_, stageY_, facing_);
        const bool reconstructed = volume.source == AttackBoxSource::Reconstructed40Jp;
        boxes_.push_back({box.x, box.y - box.z, box.w, box.h, reconstructed ? 1 : 0, {}, reconstructed});
    }
}

void SkillPreviewSession::stepFrame(int direction) {
    if (!timeline_ || timeline_->bodyPath.empty()) return;
    // Frame stepping is a millisecond seek, not a fixed tick: 40JP has no tick.
    // A chained release steps across every stage's frame boundary, so the marks
    // are collected onto one shared action clock.
    try {
        std::vector<double> marks;
        if (!timeline_->stages.empty()) {
            for (const auto &stage : timeline_->stages) {
                const auto animation = assets_.animation(stage.path);
                if (!animation) continue;
                for (const auto &span : frameSpans(*animation))
                    marks.push_back(stage.startMs + span.startMs);
            }
        } else {
            const auto body = assets_.animation(timeline_->bodyPath);
            if (!body) return;
            for (const auto &span : frameSpans(*body)) marks.push_back(span.startMs);
        }
        if (marks.empty()) return;
        std::sort(marks.begin(), marks.end());
        const double now = timeline_->ageMs;
        double target = direction >= 0 ? timeline_->durationMs : 0;
        if (direction >= 0) {
            for (const double mark : marks)
                if (mark > now + 0.0001) {
                    target = mark;
                    break;
                }
        } else {
            for (auto it = marks.rbegin(); it != marks.rend(); ++it)
                if (*it < now - 0.0001) {
                    target = *it;
                    break;
                }
        }
        timeline_->body.ageMs = target;
        timeline_->ageMs = target;
        timeline_->body.freezeRemainingMs = 0;
        timeline_->ended = false;
        // Every attached layer seeks with the body, otherwise the effects stay
        // where they were while the pose jumps.
        for (auto &layer : timeline_->layers) {
            layer.clock.freezeRemainingMs = 0;
            layer.clock.ageMs = std::max(0.0, target - layer.birthMs);
        }
        particles_.seekFrom(target);
        hitKeys_.clear();
        hitLog_.clear();
        rebuildBoxes();
    } catch (const std::exception &) {
    }
}

void SkillPreviewSession::reset() {
    if (!timeline_) return;
    timeline_->reset();
    timeline_->loop = loop_;
    hitKeys_.clear();
    hitLog_.clear();
    particles_.clear();
    frameVisits_ = 0;
    for (const auto &program : particlePrograms_)
        particles_.spawn(program, stageX_ + facing_ * 20.0, stageY_ - 40.0, 0x5eedu + unsigned(jobId_));
    rebuildBoxes();
}

void SkillPreviewSession::setSpeed(double value) {
    for (const double allowed : {0.25, 0.5, 1.0, 2.0})
        if (std::abs(value - allowed) < 1e-9) { speed_ = value; return; }
    speed_ = std::clamp(value, 0.05, 4.0);
}

void SkillPreviewSession::setFacing(int value) {
    facing_ = value >= 0 ? 1 : -1;
    if (!timeline_) return;
    const auto body = [&]() -> std::shared_ptr<Animation> {
        if (timeline_->bodyPath.empty()) return nullptr;
        try {
            return assets_.animation(timeline_->bodyPath);
        } catch (const std::exception &) {
            return nullptr;
        }
    }();
    dummies_ = buildDummies(body ? body.get() : nullptr, stageX_, stageY_, facing_, dummyCount_);
    hitKeys_.clear();
    hitLog_.clear();
    rebuildBoxes();
}

void SkillPreviewSession::cycleDummy() {
    dummyCount_ = dummyCount_ == 0 ? 1 : dummyCount_ == 1 ? 3 : 0;
    std::shared_ptr<Animation> body;
    if (timeline_ && !timeline_->bodyPath.empty()) {
        try {
            body = assets_.animation(timeline_->bodyPath);
        } catch (const std::exception &) {
        }
    }
    dummies_ = buildDummies(body ? body.get() : nullptr, stageX_, stageY_, facing_, dummyCount_);
    hitKeys_.clear();
    hitLog_.clear();
    rebuildBoxes();
}

void SkillPreviewSession::setLoop(bool value) {
    loop_ = value;
    if (timeline_) timeline_->loop = value;
}

void SkillPreviewSession::draw(Renderer &render, double cameraX, double cameraY) {
    if (!appearance_ || !timeline_) return;

    Actor actor;
    actor.x = actor.px = stageX_;
    actor.y = actor.py = stageY_;
    actor.z = actor.pz = 0;
    actor.dir = facing_;
    actor.life = ActorLife::Alive;
    actor.dead = false;
    // A chained release plays whichever stage owns the current instant, so the
    // pose follows the client's own stage order instead of one fragment of it.
    const auto *stage = timeline_->stageAt(timeline_->body.ageMs);
    std::string bodyPath = stage ? stage->path : timeline_->bodyPath;
    // A body-less row still shows the caster in the CHR's generic buff pose. It
    // is a stand-in for the picture, never part of the action clock.
    if (bodyPath.empty() && current_ && !current_->fallbackPose.empty())
        bodyPath = current_->fallbackPose;
    const double bodyMs = stage ? timeline_->body.ageMs - stage->startMs : timeline_->body.ageMs;
    actor.animation = bodyPath.empty() ? "stay" : stemOf(bodyPath);
    actor.animStart = 0;
    // No clock snapshot and no frame override: the ms value alone selects the
    // pose, which is what keeps drawing independent of any simulation tick.
    actor.poseFrame = -1;

    // Particles are the bottom layer: 40JP keeps them as separate objects that
    // are drawn before the actor they belong to.
    for (const auto &particle : particles_.particles) {
        const auto position = particlePosition(particle);
        render.animation(particle.animation, particle.ageMs,
                         stageX_ + facing_ * position[0] - cameraX,
                         stageY_ + position[1] - position[2] - cameraY, facing_, false, "",
                         particle.frame, particleAlpha(particle));
    }

    std::vector<size_t> order;
    sortLayerIndices(timeline_->layers, order);
    const double actionNow = timeline_->ageMs;
    const auto drawLayers = [&](bool front) {
        for (size_t index : order) {
            const auto &layer = timeline_->layers[index];
            if ((layer.order >= 0) != front) continue;
            if (!layer.visible(actionNow)) continue;
            render.animation(layer.path, layer.clock.ageMs,
                             stageX_ + facing_ * layer.offset[0] - cameraX,
                             stageY_ + layer.offset[1] - layer.offset[2] - cameraY,
                             facing_, layer.loop);
        }
    };
    // Persistent entities sit with the effect layers: the orbs orbit the body,
    // the lotus field lies on the ground, the sword array hangs overhead. The
    // anchor is the caster's feet because that is where the state handler
    // spawns the object.
    const auto drawPersistents = [&](bool behind) {
        const double now = timeline_->ageMs;
        for (const auto &entity : timeline_->persistents) {
            if (!entity.visible(now)) continue;
            const bool isBehind = entity.kind == PreviewPersistentKind::GroundField;
            if (isBehind != behind) continue;
            const double localMs = now - entity.birthMs;
            if (entity.kind == PreviewPersistentKind::Orbit) {
                for (int index = 0; index < entity.count; ++index) {
                    const double phase = entity.phaseDeg +
                        (360.0 * index) / double(entity.count) +
                        entity.angularDegPerSec * localMs / 1000.0;
                    const double radians = phase * 3.14159265358979323846 / 180.0;
                    const double x = entity.offset[0] + entity.radius * std::sin(radians);
                    const double y = entity.offset[1] - entity.radius * 0.32 * std::cos(radians);
                    render.animation(entity.path, localMs, stageX_ + facing_ * x - cameraX,
                                     stageY_ + y - cameraY, facing_, true);
                }
                continue;
            }
            if (entity.kind == PreviewPersistentKind::AirSword) {
                // Several swords hang in an arc over the caster. The spacing is
                // reconstructed: the source only says how many move stages the
                // release has, not where the swords stand.
                const int count = std::max(1, entity.count);
                for (int index = 0; index < count; ++index) {
                    const double centred = double(index) - double(count - 1) / 2.0;
                    const double x = entity.offset[0] + centred * 56.0;
                    const double y = entity.offset[1] + std::abs(centred) * 18.0;
                    render.animation(entity.path, localMs + index * 90.0,
                                     stageX_ + facing_ * x - cameraX,
                                     stageY_ + y - cameraY, facing_, true);
                }
                continue;
            }
            render.animation(entity.path, localMs,
                             stageX_ + facing_ * entity.offset[0] - cameraX,
                             stageY_ + entity.offset[1] - cameraY, facing_, true);
        }
    };
    drawPersistents(true);
    drawLayers(false);
    if (!bodyPath.empty())
        render.player(actor, int64_t(bodyMs), 1.0, *appearance_,
                      cameraX, cameraY, bodyPath);
    drawLayers(true);
    drawPersistents(false);

    // Targets: a flat silhouette over the source hurt volume, plus the flash of
    // a contact that happened within the last few frames.
    const double now = timeline_->ageMs;
    for (const auto &dummy : dummies_) {
        const float x = float(dummy.hurt.x - cameraX);
        const float y = float(dummy.hurt.y - dummy.hurt.z - cameraY);
        render.rect(x, y, float(dummy.hurt.w), float(dummy.hurt.h), {70, 96, 140, 46}, true);
    }
    for (const auto &hit : hitLog_) {
        if (now - hit.ms > hitFlashMs || hit.ms > now) continue;
        const float x = float(hit.overlap.x - cameraX);
        const float y = float(hit.overlap.y - hit.overlap.z - cameraY);
        render.rect(x, y, float(std::max(2.0, hit.overlap.w)), float(std::max(2.0, hit.overlap.h)),
                    {236, 96, 72, 150}, true);
    }

    if (!boxesVisible_) return;
    for (const auto &box : boxes_) {
        const float x = float(box.x - cameraX), y = float(box.y - cameraY);
        const SDL_Color color = box.kind == 0 ? SDL_Color{235, 84, 74, 255}
                              : box.kind == 1 ? SDL_Color{226, 196, 84, 255}
                                              : SDL_Color{96, 156, 232, 255};
        render.rect(x, y, float(box.w), float(box.h), color, false);
    }
}

double SkillPreviewSession::ageMs() const {
    return timeline_ ? timeline_->ageMs : 0;
}

double SkillPreviewSession::durationMs() const {
    return timeline_ ? timeline_->durationMs : 0;
}

size_t SkillPreviewSession::particleCount() const {
    return particles_.aliveCount();
}

size_t SkillPreviewSession::layerCount() const {
    return timeline_ ? timeline_->layers.size() : 0;
}

std::vector<std::string> SkillPreviewSession::drainSounds() {
    std::vector<std::string> drained;
    drained.swap(pendingSounds_);
    return drained;
}

Json SkillPreviewSession::report() const {
    Json result{{"status", status_}, {"missing", missing_}, {"jobId", jobId_},
                {"ageMs", ageMs()}, {"durationMs", durationMs()},
                {"paused", paused_}, {"loop", loop_}, {"speed", speed_}, {"facing", facing_},
                {"frameVisits", frameVisits_}, {"dummies", dummyCount_},
                {"layers", layerCount()}, {"volumes", volumeCount()},
                {"hits", hitLog_.size()}, {"particles", particleCount()}};
    Json hits = Json::array();
    for (const auto &hit : hitLog_) {
        CombatBox world{};
        if (hit.volume < volumes_.size()) world = worldVolume(volumes_[hit.volume], stageX_, stageY_, facing_);
        hits.push_back({{"ms", hit.ms}, {"dummy", hit.dummy}, {"x", world.x}, {"y", world.y},
                        {"z", world.z}, {"w", world.w}, {"h", world.h}, {"d", world.d}});
    }
    result["hitLog"] = hits;
    Json particleErrors = Json::array();
    for (const auto &program : particlePrograms_)
        if (!program.valid())
            particleErrors.push_back({{"path", program.path}, {"reason", program.error}});
    if (!particleErrors.empty()) result["particleErrors"] = particleErrors;
    if (current_) result["skill"] = current_->audit();
    return result;
}
} // namespace dnf
