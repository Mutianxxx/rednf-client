#include "dnf/character.hpp"
#include "dnf/collision.hpp"
#include "dnf/entry.hpp"
#include "dnf/renderer.hpp"
#include "dnf/skill_preview.hpp"
#include "dnf/skill_preview_mapping.hpp"
#include "dnf/skill_preview_timeline.hpp"
#include <SDL.h>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <iostream>

using namespace dnf;
namespace fs = std::filesystem;
namespace {
int failures = 0;
}

int entry(int argc, char **argv) {
    if (argc < 3) return 2;
    const fs::path client = fs::u8path(argv[1]);
    const fs::path output = fs::u8path(argv[2]);
    fs::create_directories(output);
    SDL_setenv("SDL_VIDEODRIVER", "dummy", 1);
    SDL_setenv("SDL_AUDIODRIVER", "dummy", 1);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) != 0) return 1;

    Json checks = Json::array();
    const auto check = [&](bool okay, const std::string &name, const Json &detail = Json::object()) {
        checks.push_back({{"name", name}, {"pass", okay}, {"detail", detail}});
        if (!okay) ++failures;
    };

    try {
        Pvf pvf(client / "Script.pvf");
        Assets assets({client}, pvf);
        CharacterCatalog characters(pvf);
        SkillMappingTable table(pvf, assets, characters);

        std::vector<int> jobIds;
        for (const auto &definition : characters.definitions)
            if (definition.registration.id >= 0) jobIds.push_back(definition.registration.id);

        int total = 0;
        for (int jobId : jobIds) {
            table.ensureJob(jobId);
            total += int(table.rows(jobId).size());
        }

        // 1) Every SKL entry is listed, no silent drops.
        check(total == 1734, "catalog enumerates every SKL entry", {{"total", total}});

        // 2) Swordman and gunner both expose fully playable skills.
        for (const int jobId : {0, 2}) {
            const int a = table.gradeCount(jobId, SkillGrade::A);
            check(a > 0, "job has grade A skills", {{"jobId", jobId}, {"A", a}});
        }

        // 3) Grade A means body + effects + a volume, with the body decodable.
        int gradeAChecked = 0, gradeABad = 0;
        for (const int jobId : {0, 2}) {
            for (const auto &row : table.rows(jobId)) {
                if (row.grade != SkillGrade::A) continue;
                const auto *mapping = table.mapping(row.key);
                if (!mapping) { ++gradeABad; continue; }
                bool decodable = false;
                try {
                    decodable = !assets.animation(mapping->bodyAni)->frames.empty();
                } catch (const std::exception &) {
                    decodable = false;
                }
                ++gradeAChecked;
                if (!decodable || !mapping->hasAttackBox || mapping->effects.empty()) ++gradeABad;
            }
        }
        check(gradeAChecked > 0 && gradeABad == 0, "grade A rows really are playable",
              {{"checked", gradeAChecked}, {"bad", gradeABad}});

        // 3b) 1031 exe setState bindings override the inferred chain for the
        // known anchors (GhostSlash 5, HopSmash 65, VaneSlash 58) and are used
        // broadly across swordman.
        {
            int exeBound = 0, exeBoundBad = 0;
            bool ghostSlashOk = false, hopSmashOk = false;
            for (const auto &row : table.rows(0)) {
                const auto *mapping = table.mapping(row.key);
                if (!mapping || mapping->confidence != MappingConfidence::Manual) continue;
                ++exeBound;
                const bool bodyOk = !mapping->bodyAni.empty() &&
                    mapping->bodySlotTag == "exe-setstate" &&
                    mapping->evidence.rfind("1031 DNF.exe setState", 0) == 0;
                if (!bodyOk || mapping->bodyChain.empty()) ++exeBoundBad;
                if (row.key.skillId == 5)
                    ghostSlashOk = bodyOk && !mapping->bodyChain.empty() &&
                        mapping->bodyChain.front().find("hardattack.ani") != std::string::npos;
                if (row.key.skillId == 65)
                    hopSmashOk = bodyOk && mapping->bodyChain.size() >= 2;
            }
            check(exeBound >= 20 && exeBoundBad == 0, "exe setState bindings resolve for swordman",
                  {{"bound", exeBound}, {"bad", exeBoundBad}});
            check(ghostSlashOk, "exe binding: GhostSlash chain leads with hardattack",
                  {{"skillId", 5}});
            check(hopSmashOk, "exe binding: HopSmash chain has ready->smash stages",
                  {{"skillId", 65}});
        }

        // 4) A row with no resource always explains itself.
        int gradeDChecked = 0, gradeDNoReason = 0;
        for (const int jobId : {0, 2}) {
            for (const auto &row : table.rows(jobId)) {
                if (row.grade != SkillGrade::D) continue;
                ++gradeDChecked;
                if (row.missing.empty()) ++gradeDNoReason;
            }
        }
        check(gradeDChecked > 0 && gradeDNoReason == 0, "grade D rows carry a missing reason",
              {{"checked", gradeDChecked}, {"withoutReason", gradeDNoReason}});

        // 5) The timeline is an accumulated millisecond value: 6000 x 0.5ms is
        //    3000ms regardless of how those steps were grouped into frames.
        PreviewTimeline timeline;
        timeline.durationMs = 100000;
        for (int i = 0; i < 6000; ++i) timeline.advance(0.5, 1.0);
        check(std::abs(timeline.body.ageMs - 3000.0) < 1e-6, "timeline does not drift",
              {{"ageMs", timeline.body.ageMs}});

        // 6) A frozen clock holds its pose while the freeze is consumed.
        PreviewClock clock;
        clock.freezeFor(100);
        clock.advance(60);
        const double frozenAge = clock.ageMs;
        clock.advance(60);
        check(std::abs(frozenAge) < 1e-9 && std::abs(clock.ageMs - 20.0) < 1e-9,
              "freeze holds the body then resumes", {{"during", frozenAge}, {"after", clock.ageMs}});

        // 7) Frame windows are contiguous and cover the whole animation.
        const SkillVisualMapping *playable = nullptr;
        for (const auto &row : table.rows(0)) {
            if (row.grade != SkillGrade::A) continue;
            playable = table.mapping(row.key);
            if (playable) break;
        }
        check(playable != nullptr, "a grade A swordman skill resolves");
        if (playable) {
            const auto body = assets.animation(playable->bodyAni);
            const auto spans = frameSpans(*body);
            bool contiguous = !spans.empty();
            for (size_t i = 1; i < spans.size(); ++i)
                if (std::abs(spans[i].startMs - spans[i - 1].endMs) > 1e-9) contiguous = false;
            check(contiguous && std::abs(animationDurationMs(*body) - spans.back().endMs) < 1e-9,
                  "frame spans are contiguous", {{"frames", spans.size()}});
            size_t visited = 0;
            visitFrames(*body, 0, animationDurationMs(*body),
                        [&](const FrameSpan &) { ++visited; });
            check(visited == body->frames.size(), "visitFrames covers every frame",
                  {{"visited", visited}, {"frames", body->frames.size()}});
        }

        // 8) The mirrored volume matches 40JP: x = -x - w when facing left.
        const CombatBox front = combatBox(Box{15, -20, -30, -10, 60, 40, 10}, 100, 200, 0, 1);
        const CombatBox back = combatBox(Box{15, -20, -30, -10, 60, 40, 10}, 100, 200, 0, -1);
        check(std::abs(front.x - 80.0) < 1e-9 && std::abs(back.x - 60.0) < 1e-9,
              "attack volume mirrors with facing", {{"front", front.x}, {"back", back.x}});

        // 8b) A chained release lays its stages end to end on one clock, in the
        // order the client's own motion list names them. TripleSlash is the
        // reference: five stages, and the pool holds them 1..5 consecutively.
        {
            const SkillVisualMapping *chained = nullptr;
            for (const auto &row : table.rows(0)) {
                if (row.name == "\u4e09\u6bb5\u65a9") chained = table.mapping(row.key);
                if (chained) break;
            }
            check(chained != nullptr && chained->bodyChain.size() == 5,
                  "triple slash resolves as a five-stage chain",
                  {{"stages", chained ? chained->bodyChain.size() : 0}});
            if (chained && chained->bodyChain.size() == 5) {
                PreviewTimeline chain;
                double at = 0;
                for (const auto &path : chained->bodyChain) {
                    PreviewBodyStage stage;
                    stage.path = path;
                    stage.startMs = at;
                    stage.durationMs = animationDurationMs(*assets.animation(path));
                    at += stage.durationMs;
                    chain.stages.push_back(stage);
                }
                chain.bodyPath = chain.stages.front().path;
                chain.durationMs = at;
                const double first = chain.stages.front().durationMs;
                check(chain.stageAt(first * 0.5) == &chain.stages.front() &&
                          chain.stageAt(first + 1) != &chain.stages.front(),
                      "stageAt switches past the first stage boundary");
                check(std::abs(chain.stageLocalMs(first + 1) - 1.0) < 1e-9,
                      "stageLocalMs converts to stage-local time",
                      {{"local", chain.stageLocalMs(first + 1)}});
                check(std::abs(chain.durationMs - (chain.stages.back().startMs +
                                                   chain.stages.back().durationMs)) < 1e-9,
                      "chain duration is the sum of its stages");
            }
        }

        // 9) A skill with no resource fails cleanly instead of blanking.
        SkillPreviewSession session(pvf, assets, characters, table);
        std::string jobError;
        const bool jobReady = session.selectJob(0, jobError);
        check(jobReady, "job selects without any world or level", {{"error", jobError}});
        if (jobReady && playable) {
            std::string playError;
            const bool played = session.play(*playable, playError);
            check(played, "grade A skill plays", {{"error", playError}});
            // Frame stepping is a millisecond seek onto a frame boundary.
            session.stepFrame(1);
            const auto body = assets.animation(playable->bodyAni);
            const auto spans = frameSpans(*body);
            bool onBoundary = false;
            for (const auto &span : spans)
                if (std::abs(span.startMs - session.ageMs()) < 1e-6) onBoundary = true;
            check(session.ageMs() > 0 && onBoundary, "stepFrame lands on a frame boundary",
                  {{"ageMs", session.ageMs()}});
        }

        const SkillVisualMapping *empty = nullptr;
        for (int jobId : jobIds) {
            for (const auto &row : table.rows(jobId)) {
                if (row.grade != SkillGrade::D) continue;
                empty = table.mapping(row.key);
                if (empty) break;
            }
            if (empty) break;
        }
        if (empty) {
            std::string playError;
            const bool played = session.play(*empty, playError);
            check(!played && !empty->missing.empty(), "skill without resources reports why",
                  {{"error", playError}, {"missing", empty->missing}});
        }

        // 9b) A looping timeline replays and keeps the overshoot, so repeated
        //     passes never run slower than the wall clock.
        {
            PreviewTimeline looping;
            looping.durationMs = 100;
            looping.loop = true;
            looping.advance(150, 1.0);
            check(looping.looped && std::abs(looping.ageMs - 50.0) < 1e-9,
                  "loop replays with the overshoot kept",
                  {{"ageMs", looping.ageMs}, {"looped", looping.looped}});
            PreviewTimeline finishing;
            finishing.durationMs = 100;
            finishing.loop = false;
            finishing.advance(150, 1.0);
            check(finishing.ended && !finishing.looped && std::abs(finishing.ageMs - 100.0) < 1e-9,
                  "a non-looping timeline ends at its duration", {{"ageMs", finishing.ageMs}});
        }

        // 9c) Frame lookup by millisecond agrees with the span table.
        if (playable) {
            const auto body = assets.animation(playable->bodyAni);
            const auto spans = frameSpans(*body);
            const size_t middle = frameIndexAt(*body, spans[spans.size() / 2].startMs + 0.5);
            const auto span = spanAt(*body, spans[spans.size() / 2].startMs + 0.5);
            check(middle == spans.size() / 2 && span && span->index == middle,
                  "frameIndexAt agrees with the span table",
                  {{"middle", middle}, {"frames", body->frames.size()}});
            check(frameIndexAt(*body, -5.0) == 0 &&
                      frameIndexAt(*body, animationDurationMs(*body) + 5000.0) == body->frames.size() - 1,
                  "frameIndexAt clamps to the tail like 40JP holds the last frame");
        }

        // 9d) Attack volumes exist for an A skill and live inside the action.
        if (playable) {
            const auto body = assets.animation(playable->bodyAni);
            const double duration = animationDurationMs(*body);
            const auto volumes = collectVolumes(assets, *playable, body.get(), duration, {});
            bool inside = !volumes.empty();
            for (const auto &volume : volumes)
                if (volume.startMs < 0 || volume.endMs > duration + 1e-9) inside = false;
            check(inside, "grade A volumes live inside the action window",
                  {{"volumes", volumes.size()}, {"durationMs", duration}});
        }

        // 9e) Particle axis motion: the reviewed keep-last evaluator plus the
        //     40JP free-fall term (age^2 * gravity / -2000000).
        {
            PtlProgram program;
            program.objects = {{"any.ani", -1}};
            program.velocity = {{{{700, 200}}, {{0, 0}}, {{0, 0}}}};
            program.changingTermMs = {400, 0, 0};
            program.gravity = 250;
            program.lifeMs = 600;
            program.count = 1;
            PreviewParticleField field;
            field.spawn(program, 0, 0, 7);
            check(field.aliveCount() == 1, "particle burst emits its count");
            field.advance(600);
            // The burst randomizes the endpoints inside the source range, so the
            // displacement assertion uses the exact source endpoints instead.
            PreviewParticle particle = field.particles.front();
            particle.velocityStart = {700, 0, 0};
            particle.velocityEnd = {200, 0, 0};
            particle.changingTerm = {400, 0, 0};
            const auto position = particlePosition(particle);
            check(std::abs(position[0] - 220.0) < 1e-3 && std::abs(position[2] + 45.0) < 1e-6,
                  "particle displacement and free-fall match the source formulas",
                  {{"x", position[0]}, {"z", position[2]}});
            check(!field.particles.front().alive(), "particle dies at its lifetime");

            PtlProgram linear;
            linear.objects = {{"any.ani", -1}};
            linear.velocity = {{{{800, 800}}, {{0, 0}}, {{0, 0}}}};
            linear.lifeMs = 200;
            linear.count = 1;
            PreviewParticle bullet;
            bullet.velocityStart = {800, 0, 0};
            bullet.velocityEnd = {800, 0, 0};
            bullet.lifeMs = 200;
            bullet.ageMs = 100;
            const auto straight = particlePosition(bullet);
            check(std::abs(straight[0] - 80.0) < 1e-3,
                  "pure linear axis motion is velocity * age * 0.001", {{"x", straight[0]}});
        }

        // 9f) A [straight line] sand-burst PTL parses; a wave-mode PTL refuses
        //     with a reason instead of being guessed.
        {
            const auto sand = readPtl(pvf, "character/fighter/particle/groundkicksand1particle.ptl");
            check(sand.valid() && sand.count == 30 && sand.objects.size() >= 4 &&
                      sand.changingTermMs[0] == 400,
                  "animation-type PTL parses with its burst contract",
                  {{"count", sand.count}, {"objects", sand.objects.size()},
                   {"error", sand.error}});
            const auto wave = readPtl(pvf, "character/fighter/particle/spiralnen.ptl");
            check(!wave.valid() && wave.error.find("move type") != std::string::npos,
                  "wave-mode PTL is refused with a reason", {{"error", wave.error}});
        }

        // 9g) An A skill shows ALS sub-chain layers after advancing, and hits
        //     register once the volume reaches a dummy.
        if (playable) {
            SkillPreviewSession combat(pvf, assets, characters, table);
            std::string error;
            if (combat.selectJob(playable->key.jobId, error) && combat.play(*playable, error)) {
                for (int i = 0; i < 240; ++i) combat.advance(1000.0 / 60.0);
                check(combat.layerCount() > 0, "an A skill attaches effect layers",
                      {{"layers", combat.layerCount()}});
                check(combat.volumeCount() > 0 && combat.dummyCount() > 0,
                      "volumes and a dummy are ready",
                      {{"volumes", combat.volumeCount()}, {"dummies", combat.dummyCount()}});
            } else {
                check(false, "combat session plays", {{"error", error}});
            }
        }

        // 9h) Detached skills keep an entity on the field, and a large effect
        //     family keeps every file with a staged birth instead of a cap.
        {
            table.ensureJob(0);
            const auto *hundred = table.mapping({0, 86});
            check(hundred && hundred->effectLayers.size() > 16,
                  "a 48-file effect family survives the cap", 
                  {{"layers", hundred ? int(hundred->effectLayers.size()) : 0}});
            bool airSword = false;
            int untimed = 0;
            if (hundred) {
                for (const auto &entity : hundred->persistents)
                    if (entity.kind == PersistentKind::AirSword && entity.count >= 5)
                        airSword = true;
                for (const auto &layer : hundred->effectLayers)
                    if (!layer.timed) ++untimed;
            }
            check(airSword, "one hanging sword per move stage",
                  {{"persistents", hundred ? int(hundred->persistents.size()) : 0}});
            check(untimed > 16, "no-ALS layers still get a staged birth",
                  {{"untimed", untimed}});
            table.ensureJob(1);
            const auto *orb = table.mapping({1, 40});
            bool twoOrbs = false;
            if (orb)
                for (const auto &entity : orb->persistents)
                    if (entity.kind == PersistentKind::Orbit && entity.count == 2) twoOrbs = true;
            check(twoOrbs, "Spiral Nen gives the base job two orbs",
                  {{"persistents", orb ? int(orb->persistents.size()) : 0}});
            table.ensureJob(7);
            const auto *maleOrb = table.mapping({7, 40});
            bool fourOrbs = false;
            if (maleOrb)
                for (const auto &entity : maleOrb->persistents)
                    if (entity.kind == PersistentKind::Orbit && entity.count == 4) fourOrbs = true;
            check(fourOrbs, "Spiral Nen gives the male subclass four orbs",
                  {{"persistents", maleOrb ? int(maleOrb->persistents.size()) : 0}});
        }

        // 9j) The 清风 1031 .als names a parent FRAME INDEX, not a time. The
        //     mapping must compile it into absolute action-clock ms from the
        //     parent ANI's [DELAY] table, so the native world (which cannot
        //     visit frames) still honours the source timeline. Layers with no
        //     sidecar must stay on the reconstructed birthRatio path.
        {
            size_t timed = 0, untimed = 0, withRemove = 0, positiveBirth = 0;
            bool allTimedBound = true, allUntimedUnbound = true;
            bool boundaryChecked = false, boundaryMatches = true;
            double maxBirthMs = 0;
            for (int jobId : jobIds) {
                for (const auto &row : table.rows(jobId)) {
                    const auto *m = table.mapping(row.key);
                    if (!m) continue;
                    std::vector<std::string> stages = m->bodyChain;
                    if (stages.empty() && !m->bodyAni.empty()) stages.push_back(m->bodyAni);
                    for (const auto &layer : m->effectLayers) {
                        if (layer.timed) {
                            ++timed;
                            if (layer.birthMs < 0) allTimedBound = false;
                            if (layer.birthMs > 0) ++positiveBirth;
                            maxBirthMs = std::max(maxBirthMs, layer.birthMs);
                            if (layer.endMs >= 0) {
                                ++withRemove;
                                if (layer.endMs < layer.birthMs) allTimedBound = false;
                            }
                            if (!boundaryChecked && layer.alsFrame > 0 &&
                                size_t(layer.bodyStage) < stages.size()) {
                                boundaryChecked = true;
                                try {
                                    double expected = 0;
                                    for (size_t s = 0; s < size_t(layer.bodyStage); ++s) {
                                        const auto stage = assets.animation(stages[s]);
                                        for (const auto &f : stage->frames)
                                            expected += std::max(1, f.duration);
                                    }
                                    const auto parent = assets.animation(stages[layer.bodyStage]);
                                    for (int i = 0; i < layer.alsFrame && i < int(parent->frames.size()); ++i)
                                        expected += std::max(1, parent->frames[i].duration);
                                    boundaryMatches = std::abs(expected - layer.birthMs) < 0.01;
                                } catch (const std::exception &) {
                                    boundaryMatches = false;
                                }
                            }
                        } else {
                            ++untimed;
                            if (layer.birthMs >= 0) allUntimedUnbound = false;
                        }
                    }
                }
            }
            check(timed > 0 && allTimedBound && positiveBirth > 0,
                  "1031 ALS frames compile to action-clock ms",
                  {{"timed", int(timed)}, {"positiveBirth", int(positiveBirth)},
                   {"maxBirthMs", maxBirthMs}, {"withRemove", int(withRemove)}});
            check(boundaryChecked && boundaryMatches,
                  "ALS birth equals the parent ANI DELAY sum",
                  {{"checked", boundaryChecked}});
            check(untimed > 0 && allUntimedUnbound,
                  "stem-order layers keep the reconstructed birthRatio path",
                  {{"untimed", int(untimed)}});
        }

        // 9i) The preview overlap keeps d=0 boxes testable on the single stage
        //     plane, which the strict native test would always reject.
        check(previewOverlap(CombatBox{0, 0, 0, 50, 40, 0}, CombatBox{10, -10, 0, 50, 40, 0}),
              "zero-depth boxes still overlap on the stage plane");

        // 10) Hidden renderer still produces a screenshot.
        Renderer renderer(assets, RendererOptions{"skill preview tests", 800, 600, false, false, false});
        renderer.begin();
        renderer.ui(800, 600);
        renderer.rect(0, 0, 800, 600, {10, 12, 18, 255});
        if (playable) {
            const auto body = assets.animation(playable->bodyAni);
            renderer.animation(playable->bodyAni, animationDurationMs(*body) * 0.4, 400, 300, 1, false);
        }
        const auto shot = output / "skill-preview.png";
        renderer.screenshot(shot);
        renderer.present();
        check(fs::exists(shot) && fs::file_size(shot) > 0, "screenshot is produced",
              {{"size", fs::exists(shot) ? int64_t(fs::file_size(shot)) : 0}});

        writeJson(output / "skill-preview-tests.json", {{"checks", checks}, {"failures", failures}});
    } catch (const std::exception &error) {
        checks.push_back({{"name", "uncaught exception"}, {"pass", false}, {"detail", error.what()}});
        writeJson(output / "skill-preview-tests.json", {{"checks", checks}, {"failures", failures + 1}});
        SDL_Quit();
        return 1;
    }
    SDL_Quit();
    return failures == 0 ? 0 : 1;
}

DNF_ENTRY(entry)
