#include "dnf/skill_preview_combat.hpp"
#include <algorithm>
#include <cmath>

namespace dnf {
namespace {
// 15 = [ATTACK BOX], 14 = [DAMAGE BOX] in this client's ANI node encoding.
constexpr int attackBox = 15;
constexpr int damageBox = 14;
bool usable(const Box &box) { return box.w != 0 && box.h != 0; }
} // namespace

CombatBox worldVolume(const PreviewVolume &volume, double stageX, double stageY, int facing) {
    const double originX = stageX + (facing > 0 ? volume.offset[0] : -volume.offset[0]);
    return combatBox(volume.box, originX, stageY + volume.offset[1], volume.offset[2], facing);
}

std::vector<PreviewVolume> collectVolumes(Assets &assets, const SkillVisualMapping &mapping,
                                          const Animation *body, double bodyDurationMs,
                                          const std::vector<PreviewLayer> &layers) {
    std::vector<PreviewVolume> volumes;
    if (body && !body->frames.empty()) {
        const auto spans = frameSpans(*body);
        for (size_t index = 0; index < body->frames.size(); ++index) {
            for (const auto &box : body->frames[index].boxes) {
                if (box.type != attackBox || !usable(box)) continue;
                volumes.push_back({box, index, spans[index].startMs, spans[index].endMs, {},
                                   AttackBoxSource::AniBody, {}, "ani:body [ATTACK BOX]"});
            }
        }
        for (size_t index = 0; index < mapping.reconstructedBoxes.size(); ++index) {
            Box box = mapping.reconstructedBoxes[index];
            box.type = attackBox;
            size_t first = 0, last = body->frames.size() - 1;
            if (index < mapping.reconstructedFrames.size()) {
                first = std::min(mapping.reconstructedFrames[index].first, last);
                last = std::min(mapping.reconstructedFrames[index].second, last);
                if (first > last) first = last;
            }
            const double startMs = first < spans.size() ? spans[first].startMs : 0;
            const double endMs = last < spans.size() ? spans[last].endMs : bodyDurationMs;
            volumes.push_back({box, first, startMs, endMs, {},
                               AttackBoxSource::Reconstructed40Jp, {}, "mapping: cited constant"});
        }
    }
    // 40JP attaches an effect as a pooled animation; its own frame table carries
    // the attack volume, and its live window starts at the attach time.
    for (const auto &layer : layers) {
        if (layer.path.empty()) continue;
        try {
            const auto animation = assets.animation(layer.path);
            if (!animation || animation->frames.empty()) continue;
            const auto spans = frameSpans(*animation);
            for (size_t index = 0; index < animation->frames.size(); ++index) {
                for (const auto &box : animation->frames[index].boxes) {
                    if (box.type != attackBox || !usable(box)) continue;
                    volumes.push_back({box, index, layer.birthMs + spans[index].startMs,
                                       layer.birthMs + spans[index].endMs, layer.offset,
                                       AttackBoxSource::AniBody, layer.path,
                                       "ani:layer [ATTACK BOX]"});
                }
            }
        } catch (const std::exception &) {
            // A layer that cannot be decoded has no volume; the mapping already
            // reports the missing resource for the skill itself.
        }
    }
    std::stable_sort(volumes.begin(), volumes.end(), [](const PreviewVolume &lhs, const PreviewVolume &rhs) {
        return lhs.startMs < rhs.startMs;
    });
    return volumes;
}

std::vector<PreviewDummy> buildDummies(const Animation *body, double stageX, double stageY,
                                       int facing, int count) {
    std::vector<PreviewDummy> dummies;
    if (count <= 0) return dummies;
    // Fallback shape when the animation has no [DAMAGE BOX]: a standing target.
    // Marked as inference because no source frame carries it.
    Box shape{damageBox, -30, -110, 0, 60, 110, 1};
    bool sourced = false;
    if (body) {
        bool first = true;
        int minX = 0, minY = 0, maxX = 0, maxY = 0;
        for (const auto &frame : body->frames) {
            for (const auto &box : frame.boxes) {
                if (box.type != damageBox || !usable(box)) continue;
                if (first) {
                    minX = box.x; minY = box.y; maxX = box.x + box.w; maxY = box.y + box.h;
                    first = false;
                } else {
                    minX = std::min(minX, box.x);
                    minY = std::min(minY, box.y);
                    maxX = std::max(maxX, box.x + box.w);
                    maxY = std::max(maxY, box.y + box.h);
                }
            }
        }
        if (!first) {
            shape = Box{damageBox, minX, minY, 0, maxX - minX, maxY - minY, 1};
            sourced = true;
        }
    }
    const std::array<double, 3> single{90, 0, 0};
    const std::array<double, 3> triple{90, 190, -70};
    const double *offsets = count == 1 ? single.data() : triple.data();
    for (int index = 0; index < count; ++index) {
        PreviewDummy dummy;
        dummy.index = index;
        dummy.x = stageX + facing * offsets[index];
        dummy.y = stageY;
        // The target faces the actor, so its own hurt volume is not mirrored.
        dummy.hurt = combatBox(shape, dummy.x, dummy.y, 0, 1);
        dummy.sourced = sourced;
        dummies.push_back(std::move(dummy));
    }
    return dummies;
}

bool volumeLiveIn(const PreviewVolume &volume, double fromMs, double toMs) {
    return volume.endMs > fromMs && volume.startMs < toMs;
}

bool previewOverlap(const CombatBox &attack, const CombatBox &hurt, CombatBox *overlap) {
    CombatBox a = attack, b = hurt;
    // The stage is one plane: depth is not drawn and a source box often leaves d
    // at 0. 40JP's separating-axis test rejects a zero extent, which would make
    // every contact fail here, so the preview gives such a box the smallest
    // depth. This is inference, not source data.
    if (a.d == 0) a.d = 1;
    if (b.d == 0) b.d = 1;
    return intersectCombatBoxes(a, b, overlap);
}
} // namespace dnf
