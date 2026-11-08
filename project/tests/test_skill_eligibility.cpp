#include "dnf/combat.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <chrono>

namespace dnf {
namespace {
bool onlyUnlearnedFeedback(const World &world) {
    return std::all_of(world.events.begin(), world.events.end(), [](const Event &event) {
        return event.kind == "skill_rejected" && event.name == "unlearned_skill";
    });
}
Json eligibilityState(const World &world, int index) {
    return {{"active_skill", world.activeSkill()}, {"stage", world.stage()},
            {"mp", world.player.mp}, {"cooldown_ms", world.remainingCd(index)},
            {"animation", world.player.animation}, {"anim_start", world.player.animStart},
            {"pose", world.player.poseFrame}, {"x", world.player.x}, {"y", world.player.y},
            {"z", world.player.z}, {"vx", world.player.vx}, {"vy", world.player.vy},
            {"vz", world.player.vz}, {"effect_count", world.effects.size()},
            {"gameplay_event_count", std::count_if(world.events.begin(), world.events.end(),
                [](const Event &event) { return event.kind != "skill_rejected"; })}};
}
void eligiblePose(World &world, Assets &assets, const Skill &skill) {
    world.freezeAi = true;
    world.player.x = 400;
    if (skill.airOnly) {
        world.player.z = 100;
        world.player.animation = "jumpattack";
    }
    if (skill.id == 11) {
        world.player.animation = "dashattack";
        const auto animation = assets.animation(world.actorAni());
        int frame3Ms = 0;
        for (size_t frame = 0; frame < 3; ++frame)
            frame3Ms += animation->frames.at(frame).duration;
        world.player.animStart = world.nowMs() - frame3Ms;
    }
}
}

Json runSkillEligibilityTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), zeroLevel = Json::array();
    bool passed = true;
    auto check = [&](bool ok, const std::string &message) {
        passed &= ok;
        checks.push_back({{"passed", ok}, {"check", message}});
    };
    const World catalog(pvf, assets);
    for (size_t index = 0; index < catalog.skills.size(); ++index) {
        World world(pvf, assets);
        auto &skill = world.skills[index];
        eligiblePose(world, assets, skill);
        skill.level = 0;
        const auto before = eligibilityState(world, int(index));
        world.activate(int(index));
        const auto rejected = eligibilityState(world, int(index));
        const bool rejectionOnly = world.events.size() == 1 && onlyUnlearnedFeedback(world) &&
            world.player.skillFailureFeedback.startedMs == world.nowMs() &&
            world.player.skillFailureFeedback.reason == "unlearned_skill";
        // The paired positive control ensures the zero-level test did not just
        // hit an unrelated air/dash/state/MP gate in its fixture.
        skill.level = 1;
        world.activate(int(index));
        const bool learnedStarts = world.activeSkill() == int(index) &&
            world.player.mp == before.at("mp").get<int>() - world.skillCosts(int(index)).consumeMp().value_or(-1);
        zeroLevel.push_back({{"skill_id", skill.id}, {"before", before}, {"after_zero", rejected},
                             {"after_learned", eligibilityState(world, int(index))}});
        check(before == rejected && rejectionOnly && learnedStarts,
              "Skill " + std::to_string(skill.id) + ": zero emits only failure feedback without gameplay effects; learned control starts");
    }
    {
        World world(pvf, assets);
        world.god = world.freeCd = true;
        world.skills[9].level = 0; // Gore Cross, even in diagnostic modes.
        const auto before = eligibilityState(world, 9);
        world.activate(9);
        check(eligibilityState(world, 9) == before && world.events.size() == 1 && onlyUnlearnedFeedback(world),
              "Free cooldown and god settings do not grant an unlearned skill");
    }
    Json buffers = Json::array();
    for (const bool learnedAtPress : {false, true}) {
        World world(pvf, assets);
        world.freezeAi = true;
        world.player.animation = "attack1";
        world.player.hitStopTicks = 3;
        world.player.hitStopped = true;
        auto &skill = world.skills[1];
        skill.level = learnedAtPress ? 1 : 0;
        const int mp = world.player.mp;
        world.enqueue({0, 21, true}); // One Ghost Slash shortcut during pause.
        world.advance(16666667);
        const bool noEarlyCommit = world.activeSkill() < 0 && world.player.mp == mp &&
            world.remainingCd(1) == 0 && world.effects.empty() && onlyUnlearnedFeedback(world) &&
            world.events.size() == (learnedAtPress ? 0u : 1u);
        // Exercise both buffer admission and revalidation at consumption. This
        // field change is a core fixture, not an in-game unlearning mechanism.
        skill.level = learnedAtPress ? 0 : 1;
        for (int tick = 0; tick < 20; ++tick) world.advance(16666667);
        const bool noLateCommit = world.activeSkill() < 0 && world.player.mp == mp &&
            world.remainingCd(1) == 0 && world.effects.empty() && world.events.size() == 1 && onlyUnlearnedFeedback(world);
        buffers.push_back({{"learned_at_press", learnedAtPress},
                           {"level_after_press", skill.level}, {"no_early_commit", noEarlyCommit},
                           {"no_late_commit", noLateCommit}});
        check(noEarlyCommit && noLateCommit, learnedAtPress
            ? "A buffered learned skill rechecks zero level when the pause releases"
            : "A rejected unlearned shortcut is not retained and cast after learning");
    }
    {
        World world(pvf, assets);
        world.freezeAi = true;
        const int mp = world.player.mp;
        world.enqueue({0, 21, true});
        world.advance(16666667);
        const bool started = world.tick == 1 && world.activeSkill() == 1 &&
            world.player.mp == mp - world.skillCosts(1).consumeMp().value_or(-1);
        world.enqueue({world.nowMs() * 1000000, 21, true});
        world.advance(16666667);
        check(started && world.player.mp == mp - world.skillCosts(1).consumeMp().value_or(-1),
              "A learned shortcut still starts on its first simulation tick and pays once");
    }
    {
        World world(pvf, assets);
        world.freezeAi = true;
        for (auto &skill : world.skills) skill.level = 0;
        const int mp = world.player.mp;
        world.normalAttack();
        check(world.player.animation == "attack1" && world.activeSkill() < 0 && world.player.mp == mp,
              "Unlearned active skills do not disable ordinary attacks");
    }
    {
        const auto directory = std::filesystem::path("reports/test-saves/skill-eligibility") /
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
        CharacterStore store(directory);
        store.data["characters"][0] = {{"name", "ZeroLevel"}, {"class", "swordman"},
                                        {"future_skill_data", 83}, {"skills", Json::object()}};
        for (const auto &skill : catalog.skills)
            store.data["characters"][0]["skills"][std::to_string(skill.id)] = 0;
        World world(pvf, assets);
        store.apply(0, world);
        const bool applied = std::all_of(world.skills.begin(), world.skills.end(),
                                        [](const Skill &skill) { return skill.level == 0; });
        store.capture(0, world);
        store.save();
        store.close();
        CharacterStore reloaded(directory);
        World restored(pvf, assets);
        reloaded.apply(0, restored);
        check(applied && std::all_of(restored.skills.begin(), restored.skills.end(),
                                    [](const Skill &skill) { return skill.level == 0; }) &&
                  reloaded.data["characters"][0]["future_skill_data"] == 83,
              "All explicit zero active levels survive apply, capture, disk reload and unknown-field preservation");
        store.data["characters"][0].erase("skills");
        store.apply(0, world);
        check(std::all_of(world.skills.begin(), world.skills.end(),
                          [](const Skill &skill) { return skill.level == 1; }),
              "Legacy absent active levels retain the existing demo defaults");
    }
    return {{"status", passed ? "pass" : "fail"}, {"checks", checks}, {"check_count", checks.size()},
            {"zero_level_cases", zeroLevel}, {"buffer_cases", buffers},
            {"native_evidence", "skill-eligibility/code-0086d8a0-use-skill-base-consumer.asm:86D9D5..86D9F4"},
            {"scope", "Zero-level start rejection in the existing Swordman controller, paired learned controls and local input-buffer policy; not full native qualification or original-client parity"}};
}
} // namespace dnf
