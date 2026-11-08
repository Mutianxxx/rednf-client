#include "dnf/presentation/characters/character_presentation.hpp"
#include "dnf/appearance.hpp"
#include "dnf/combat.hpp"
#include <algorithm>
#include <array>
#include <stdexcept>

namespace dnf {
void CharacterPresentation::draw(const Actor &p, int64_t ms, double a,
                                 const CharacterAppearance &look,
                                 ani_render::RenderProfile profile,
                                 double cameraX, double cameraY,
                                 const std::string &bodyMotion) {
    double x = p.px + (p.x - p.px) * a - cameraX,
           y = p.py + (p.y - p.py) * a - (p.pz + (p.z - p.pz) * a) - cameraY;
    // The user-requested cue affects only the composed character pixels.
    if (!p.dead && p.life == ActorLife::Alive) x += p.skillFailureFeedback.offsetX(ms);
    const auto t = ms - p.animStart;
    const bool loop = p.animation == "stay" || p.animation == "move" ||
                      p.animation == "dash" || p.animation == "guard";
    std::shared_ptr<const Animation> rootAnimation;
    const auto *clockBody = appearanceBodyMotion(look, bodyMotion.empty() ? p.animation : bodyMotion);
    if (p.animationClock && clockBody &&
        normalize(clockBody->resource.path) == normalize(p.animationClockSource))
        rootAnimation = assets_.animation(p.animationClockSource);

    const auto drawLayer = [&](const std::string &path,
                               const std::array<int, 2> &variation, bool body = false) {
        try {
            const auto ani = assets_.animation(path);
            if (ani->frames.empty()) return;
            std::optional<ani_clock::Snapshot> childClock;
            if (p.animationClock && rootAnimation && p.poseFrame < 0)
                childClock = body ? *p.animationClock : ani->followClock(
                    *rootAnimation, *p.animationClock, p.animationClock->loop,
                    p.animationControllerDelays.get());
            const auto pose = ani->samplePose(t, loop, p.poseFrame, profile,
                                              childClock ? &*childClock : nullptr);
            const auto image = appearanceImage(pose.image, variation, body);
            if (image.find('%') != std::string::npos) {
                sink_.reportCharacterIssue("appearance:" + image,
                    {{"appearance_image", image}, {"source_animation", path}}, true);
                return;
            }
            sink_.drawCharacterAnimation({path, double(t), x, y, p.dir, loop, image,
                                           p.poseFrame, childClock});
        } catch (const std::exception &error) {
            sink_.reportCharacterIssue(path, {{"animation", path}, {"error", error.what()}}, false);
        }
    };
    const auto *body = appearanceBodyMotion(look, bodyMotion.empty() ? p.animation : bodyMotion);
    if (!body) {
        sink_.reportCharacterIssue("appearance-motion:" + look.job + ":" + p.animation,
            {{"kind", "unbound_character_motion"}, {"job", look.job},
             {"motion", p.animation}, {"requested_path", bodyMotion}}, true);
        return;
    }
    const auto &bodyPath = body->resource.path;
    // 40JP sub_499C70 draws its ordered negative attachments, the composed
    // actor, then its ordered nonnegative attachments. Creation/restore order
    // is not a layer order. Keep equal layers stable without mutating gameplay
    // instances, and avoid a render-frame allocation for normal layer counts.
    std::array<size_t, 32> inlineOrder{};
    std::vector<size_t> overflowOrder;
    auto *layerOrder = inlineOrder.data();
    if (p.skillAnimationLayers.size() > inlineOrder.size()) {
        overflowOrder.resize(p.skillAnimationLayers.size());
        layerOrder = overflowOrder.data();
    }
    size_t layerCount = 0;
    const auto normalizedBody = normalize(bodyPath);
    for (size_t i = 0; i < p.skillAnimationLayers.size(); ++i)
        if (p.skillAnimationLayers[i].trigger == SourceSkillVisualTrigger::StageLayer &&
            normalize(p.skillAnimationLayers[i].bodyPath) == normalizedBody)
            layerOrder[layerCount++] = i;
    std::sort(layerOrder, layerOrder + layerCount, [&](size_t lhs, size_t rhs) {
        const auto left = p.skillAnimationLayers[lhs].layer;
        const auto right = p.skillAnimationLayers[rhs].layer;
        return left < right || (left == right && lhs < rhs);
    });
    const auto drawSkillLayers = [&](bool front) {
        for (size_t i = 0; i < layerCount; ++i) {
            const auto &layer = p.skillAnimationLayers[layerOrder[i]];
            if ((layer.layer >= 0) != front) continue;
            try {
                const auto &path = layer.source.memberPath;
                const auto ani = assets_.animation(path);
                std::optional<ani_clock::Snapshot> layerClock = layer.instanceClock;
                if (layerClock && layerClock->ended) continue;
                if (!layerClock && p.animationClock && rootAnimation && p.poseFrame < 0) {
                    if (layer.synchronizedToBody)
                        layerClock = ani->followClock(*rootAnimation, *p.animationClock,
                            p.animationClock->loop, p.animationControllerDelays.get());
                    else {
                        auto sourceClock = *p.animationClock;
                        if (!layer.inheritBodyRate) {
                            sourceClock.ratePercent = 100;
                            sourceClock.policy = ani_clock::ClockPolicy::SourceDelay100;
                            sourceClock.rateRevision = 1;
                        }
                        layerClock = ani->followClock(*ani, sourceClock, layer.loop);
                    }
                }
                sink_.drawCharacterAnimation({path,
                    p.animationClock ? double(p.animationClock->elapsedMs) : double(t),
                    x+p.dir*layer.offset[0], y+layer.offset[1]-layer.offset[2], p.dir, layer.loop, "",
                    !layer.instanceClock && layer.synchronizedToBody ? p.poseFrame : -1,
                    layerClock,layer.scaleX,layer.scaleY});
            } catch (const std::exception &error) {
                const auto &path = layer.source.memberPath;
                sink_.reportCharacterIssue(path, {{"animation", path}, {"error", error.what()},
                    {"consumer", "skill-character-layer"}}, false);
            }
        }
    };
    drawSkillLayers(false);
    bool bodyDrawn = false;
    // EQU layer numbers interleave costume, equipment and body. They must not
    // be regrouped into three independent drawing passes.
    for (const auto &layer : look.orderedLayers()) {
        if (!bodyDrawn && layer.order >= look.bodyOrder) {
            drawLayer(bodyPath, {0, look.bodyVariation()}, true);
            bodyDrawn = true;
        }
        const auto path = appearanceLayerMotion(layer, *body);
        if (!path.empty()) drawLayer(path, layer.variation);
    }
    if (!bodyDrawn) drawLayer(bodyPath, {0, look.bodyVariation()}, true);
    drawSkillLayers(true);
}
} // namespace dnf
