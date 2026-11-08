#include "dnf/presentation/characters/character_presentation.hpp"
#include "dnf/appearance.hpp"
#include "dnf/combat.hpp"
#include "dnf/entry.hpp"
#include <cmath>
#include <iostream>
#include <set>
#include <stdexcept>

namespace {
using namespace dnf;
struct RecordedLayer {
    std::string path, image;
    double elapsed = 0, x = 0, y = 0;
    int direction = 1, frame = -1;
    bool loop = false;
    std::optional<ani_clock::Snapshot> clock;
    double scaleX = 1, scaleY = 1;
};
class RecordingSink final : public ICharacterDrawSink {
  public:
    std::vector<RecordedLayer> layers;
    Json errors = Json::array(), unsupported = Json::array();
    std::set<std::string> issueKeys;
    std::string failPath;
    void drawCharacterAnimation(const CharacterAnimationRequest &request) override {
        if (request.path == failPath) throw std::runtime_error("fixture backend rejection");
        layers.push_back({request.path, request.imageOverride, request.elapsedMs,
            request.x, request.y, request.direction, request.frameOverride,
            request.loop, request.clock, request.scaleX, request.scaleY});
    }
    void reportCharacterIssue(const std::string &key, const Json &issue,
                              bool isUnsupported) override {
        if (!issueKeys.insert(key).second) return;
        if (isUnsupported) unsupported.push_back(issue);
        else errors.push_back(issue);
    }
};
bool approximatelyEqual(double a, double b) { return std::abs(a - b) < 1e-9; }
bool sameClock(const ani_clock::Snapshot &a, const ani_clock::Snapshot &b) {
    return a.policy == b.policy && a.frame == b.frame && a.nextFrame == b.nextFrame &&
        a.lastTick == b.lastTick && a.elapsedMs == b.elapsedMs &&
        a.frameStartMs == b.frameStartMs && a.nextDeadlineMs == b.nextDeadlineMs &&
        a.localMs == b.localMs && a.spanMs == b.spanMs && a.visit == b.visit &&
        a.loopCount == b.loopCount && a.rateRevision == b.rateRevision &&
        a.ratePercent == b.ratePercent && a.ended == b.ended &&
        a.loop == b.loop && a.paused == b.paused;
}

int run(int argc, char **argv) {
    Json checks = Json::array();
    const auto report = std::filesystem::u8path(argc > 2 ? argv[2] :
        "reports/character-presentation-tests.json");
    const auto check = [&](bool passed, const std::string &message) {
        checks.push_back({{"passed", passed}, {"message", message}});
        if (!passed) throw std::runtime_error(message);
    };
    try {
        if (argc < 2) throw std::invalid_argument("Expected original client directory argument");
        const auto root = std::filesystem::u8path(argv[1]);
        Pvf pvf(root / "Script.pvf");
        Assets assets(root, pvf);
        CharacterCatalog catalog(pvf);
        auto appearance = defaultCharacterAppearance(pvf, catalog, {0, 0, 0});
        const auto sword = pvf.script("equipment/character/swordman/weapon/ssword/sswd_default.equ");
        const auto coat = pvf.script("equipment/character/swordman/avatar/coat/101500425.equ");
        const auto armor = pvf.script("equipment/character/common/jacket/cloth/vest_owool.equ");
        check(applyEquipmentAppearance(appearance, sword) &&
              applyEquipmentAppearance(appearance, coat), "Real sword and split-coat fixtures apply");
        bindEquipmentMotions(pvf, appearance);
        Actor actor;
        actor.px = 80; actor.x = 100; actor.py = 160; actor.y = 200;
        actor.pz = 10; actor.z = 30; actor.dir = -1; actor.animStart = 20;
        RecordingSink sink;
        CharacterPresentation presentation(assets, sink);
        const auto profile = ani_render::RenderProfile::Legacy1031;
        presentation.draw(actor, 100, .25, appearance, profile, 5, 7);
        check(sink.layers.size() == 10 && sink.errors.empty() && sink.unsupported.empty(),
              "Authored two weapon layers, seven costume layers and one body are all composed");
        check(sink.layers[0].path == "equipment/character/swordman/weapon/ssword/sswdb/stay.ani" &&
              sink.layers[1].path == "equipment/character/swordman/avatar/coat/coat_b/stay.ani" &&
              sink.layers[2].path == "character/swordman/animation/stay.ani" &&
              sink.layers.back().path == "equipment/character/swordman/weapon/ssword/sswdc/stay.ani",
              "Rear weapon 650, rear coat 900, body 1000 and front weapon 2790 retain interleaved source order");
        for (const auto &layer : sink.layers)
            check(approximatelyEqual(layer.x, 80) && approximatelyEqual(layer.y, 148) && layer.direction == -1 &&
                  layer.elapsed == 80 && layer.loop && !layer.clock,
                  "Every layer preserves interpolation, camera, Z projection, direction and elapsed milliseconds");
        check(sink.layers[2].image == "character/swordman/equipment/avatar/skin/sm_body0000.img" &&
              sink.layers[1].image == "character/swordman/equipment/avatar/coat/sm_coat3701b.img",
              "Source body skin and costume model/palette substitutions survive extraction");
        const auto originalCount = sink.layers.size();
        check(!applyEquipmentAppearance(appearance, armor), "Stat armor has no authored appearance overlay");
        sink.layers.clear(); presentation.draw(actor, 100, .25, appearance, profile, 5, 7);
        check(sink.layers.size() == originalCount,
              "A stat-only coat cannot remove an equipped costume from the composed presentation");

        const auto bodyPath = std::string("character/swordman/animation/stay.ani");
        const auto body = assets.animation(bodyPath);
        AnimationPlayback playback;
        playback.install(*body, true, 200, ani_clock::ClockPolicy::Inferred60UsPercentDeadlines, 0);
        for (uint64_t tick = 1; tick <= 7; ++tick) playback.advance(tick, false);
        actor.animationClock = playback.snapshot(); actor.animationClockSource = bodyPath;
        const auto clockBefore = *actor.animationClock;
        const auto framesBefore = body->frames.front().duration;
        FemaleGunnerSkillLayer rear;
        rear.source.memberPath = bodyPath; rear.bodyPath = bodyPath; rear.layer = -1;
        rear.synchronizedToBody = true; rear.loop = true;
        auto front = rear; front.layer = 1; front.synchronizedToBody = false;
        auto ended = front; ended.instanceClock = clockBefore; ended.instanceClock->ended = true;
        auto otherMotion = front; otherMotion.bodyPath = "fixture/unrelated-motion.ani";
        actor.skillAnimationLayers = {front, ended, otherMotion, rear};
        sink.layers.clear(); presentation.draw(actor, 100, .25, appearance, profile, 5, 7);
        check(sink.layers.size() == originalCount + 2 && sink.layers.front().image.empty() &&
              sink.layers.back().image.empty(),
              "Skill rear/front attachments surround the composed actor; ended and unrelated instances are skipped");
        check(sink.layers.front().clock && sameClock(*sink.layers.front().clock, clockBefore),
              "Synchronized source attachment borrows the body instance clock");
        check(sink.layers.back().clock && sink.layers.back().clock->ratePercent == 100 &&
              sink.layers.back().clock->policy == ani_clock::ClockPolicy::SourceDelay100,
              "Independent skill layer retains source delays instead of inheriting body speed");
        check(sink.layers[3].clock && sameClock(*sink.layers[3].clock, clockBefore),
              "Body draw request receives the exact simulation-owned clock snapshot");
        check(sameClock(*actor.animationClock, clockBefore) &&
              body->frames.front().duration == framesBefore && actor.skillAnimationLayers.size() == 4,
              "Presentation does not advance clocks, alter ANI delays or retire gameplay attachments");
        auto scaledLayer=rear;scaledLayer.scaleX=1.5;scaledLayer.scaleY=.75;
        actor.skillAnimationLayers={scaledLayer};sink.layers.clear();
        presentation.draw(actor,100,.25,appearance,profile,5,7);
        check(sink.layers.size()==originalCount+1&&approximatelyEqual(sink.layers.front().scaleX,1.5)&&
              approximatelyEqual(sink.layers.front().scaleY,.75),
              "Source cue X/Y scale reaches the character draw request independently");
        actor.skillAnimationLayers={front,ended,otherMotion,rear};
        actor.poseFrame = 0;
        sink.layers.clear(); presentation.draw(actor, 100, .25, appearance, profile, 5, 7);
        check(sink.layers[1].frame == 0 && !sink.layers[1].clock && sink.layers.front().frame == 0,
              "Explicit diagnostic pose suppresses projected clocks while preserving synchronized pose override");
        {
            const std::string coatPath = "equipment/character/swordman/avatar/coat/coat_b/stay.ani";
            const std::string weaponPath = "equipment/character/swordman/weapon/ssword/sswdb/stay.ani";
            const auto attachment = [&](int layer, const std::string &path) {
                auto value = rear; value.layer = layer; value.source.memberPath = path;
                return value;
            };
            actor.skillAnimationLayers = {attachment(30, bodyPath), attachment(-10, bodyPath),
                attachment(10, weaponPath), attachment(-30, weaponPath),
                attachment(10, coatPath), attachment(-20, coatPath)};
            sink.layers.clear(); presentation.draw(actor, 100, .25, appearance, profile, 5, 7);
            check(sink.layers.size() == originalCount + 6 &&
                  sink.layers[0].path == weaponPath && sink.layers[1].path == coatPath &&
                  sink.layers[2].path == bodyPath &&
                  sink.layers[originalCount + 3].path == weaponPath &&
                  sink.layers[originalCount + 4].path == coatPath &&
                  sink.layers[originalCount + 5].path == bodyPath,
                  "40JP attachment composition sorts each side by authored layer and retains equal-layer creation order");
            check(actor.skillAnimationLayers.front().layer == 30 &&
                  actor.skillAnimationLayers[1].layer == -10,
                  "Rendering source layer order cannot mutate gameplay or saved attachment order");
            // The inline sorting buffer is an optimization, not a layer cap.
            actor.skillAnimationLayers.clear();
            for (int layer = 39; layer >= 0; --layer)
                actor.skillAnimationLayers.push_back(attachment(layer, layer % 2 ? coatPath : weaponPath));
            sink.layers.clear(); presentation.draw(actor, 100, .25, appearance, profile, 5, 7);
            check(sink.layers.size() == originalCount + 40 &&
                  sink.layers[originalCount].path == weaponPath &&
                  sink.layers.back().path == coatPath,
                  "Attachment sets exceeding the inline buffer retain all forty ordered render instances");
        }
        actor.poseFrame = -1; actor.skillAnimationLayers.clear(); actor.animationClock.reset();
        actor.skillFailureFeedback.startedMs = 100;
        sink.layers.clear(); presentation.draw(actor, 100, .25, appearance, profile, 5, 7);
        check(approximatelyEqual(sink.layers.front().x, 82) && approximatelyEqual(actor.x, 100) && approximatelyEqual(actor.z, 30),
              "Failure cue offsets only composed pixels and leaves world position untouched");
        actor.dead = true;
        sink.layers.clear(); presentation.draw(actor, 100, .25, appearance, profile, 5, 7);
        check(approximatelyEqual(sink.layers.front().x, 80), "Dead actor does not receive the living failure cue");
        actor.dead = false; actor.skillFailureFeedback.startedMs = -1;

        RecordingSink missingSink;
        CharacterPresentation missingPresentation(assets, missingSink);
        auto unbound = appearance; unbound.bodyMotions.clear();
        for (int frame = 0; frame < 2; ++frame)
            missingPresentation.draw(actor, 100, .25, unbound, profile);
        check(missingSink.layers.empty() && missingSink.unsupported.size() == 1 &&
              missingSink.unsupported[0].at("kind") == "unbound_character_motion",
              "Unbound source motion submits no substitute and uses the backend's once-only diagnostic key");
        RecordingSink errorSink;
        errorSink.failPath = "equipment/character/swordman/weapon/ssword/sswdb/stay.ani";
        CharacterPresentation errorPresentation(assets, errorSink);
        for (int frame = 0; frame < 2; ++frame)
            errorPresentation.draw(actor, 100, .25, appearance, profile);
        check(errorSink.errors.size() == 1 && errorSink.layers.size() == 2 * (originalCount - 1),
              "One failed layer is reported once while later layers continue to draw");

        for (int job = 0; job < 10; ++job) {
            auto look = defaultCharacterAppearance(pvf, catalog, {job, 0, 0});
            RecordingSink jobSink; CharacterPresentation jobPresentation(assets, jobSink);
            const auto *registeredBody = appearanceBodyMotion(look, "stay");
            check(registeredBody != nullptr,
                  "Job " + std::to_string(job) + " has an unambiguous registered stay motion");
            jobPresentation.draw(actor, 100, .25, look,
                ani_render::RenderProfile::Inferred60Us1031);
            size_t bodies = 0;
            for (const auto &layer : jobSink.layers)
                if (layer.path == registeredBody->resource.path) ++bodies;
            check(bodies == 1, "Job " + std::to_string(job) +
                  " composes its own registered body through the shared presentation object");
        }
        writeJson(report, {{"status", "pass"}, {"checks", checks},
            {"check_count", checks.size()}, {"pvf_identity", pvf.identity()},
            {"frontend_started", false}, {"original_dynamic_comparison", "pending_user"},
            {"scope", "source composition, clocks and read-only state; no new native rendering claim"}});
        std::cout << "Character presentation: " << checks.size() << " checks passed\n";
        return 0;
    } catch (const std::exception &error) {
        writeJson(report, {{"status", "failed"}, {"error", error.what()}, {"checks", checks}});
        std::cerr << "Character presentation: " << error.what() << '\n';
        return 1;
    }
}
} // namespace
DNF_ENTRY(run)
