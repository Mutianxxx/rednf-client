#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/swordman_stage_plan.hpp"
#include <stdexcept>
#include <set>
#include <algorithm>
#include <random>
namespace dnf {
Json runNativeAttackTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), samples = Json::array();
    auto check = [&](bool ok, const std::string &message) {
        if (!ok) throw std::runtime_error("Native ordinary attack: " + message);
        checks.push_back(message);
    };
    auto step = [](World &world) { world.advance(16666667); };
    for (bool lab : {false, true}) for (int direction : {-1, 1}) {
        World world(pvf, assets, WorldRules::BetaFoundationV1);
        world.enableExperimentalCharacters(); world.unlockAllSkills(lab);
        world.monsters.clear(); world.freezeAi = true; world.combat = true;
        world.player.dir = direction;
        const auto press = [&](int key, bool down) {
            world.enqueue({world.simulationNanoseconds(), key, down}); step(world);
        };
        press(4, true); press(4, false);
        check(world.activeSkill() < 0 && world.player.animation == "attack1",
              "Actual Beta X starts ordinary attack with lab=" + std::to_string(lab));
        press(4, true); press(4, false);
        bool second = false, third = false;
        for (int tick = 0; tick < 180; ++tick) {
            step(world);
            if (!second && world.player.animation == "attack2") {
                second = true; press(4, true); press(4, false);
            }
            third |= world.player.animation == "attack3";
            check(world.activeSkill() < 0, "Context-only bare ATTACK cannot hijack the real X combo");
            if (third && world.player.animation == "stay") break;
        }
        check(second && third && world.player.animation == "stay", "Actual Beta X finishes all three swings");
        // Uninterpreted tokens must not silently collapse a command into X.
        world.skills.front().command = Json::array({"(UNSUPPORTED_CONTEXT)", "(ATTACK)"});
        press(4, true); press(4, false);
        check(world.activeSkill() < 0 && world.player.animation == "attack1", "Unsupported command semantics fail closed");
    }
    for (int weapon = 0; weapon < 4; ++weapon) for (int direction : {-1, 1}) {
        World world(pvf, assets);
        world.weapon = weapon; world.freezeAi = true;
        world.player.x = world.player.px = 500;
        world.player.y = world.player.py = 260;
        world.player.dir = direction;
        world.normalAttack(); world.normalAttack();
        int64_t first = -1, second = -1, ended = -1;
        for (int tick = 0; tick < 120; ++tick) {
            step(world);
            if (first < 0 && world.player.animation == "attack2") {
                first = world.nowMs();
                check(world.player.poseFrame == 0, "First native chain begins at pose0, weapon " + std::to_string(weapon));
                world.normalAttack();
            }
            if (second < 0 && world.player.animation == "attack3") {
                second = world.nowMs(); world.normalAttack(); // Third swing must not wrap into attack1.
            }
            if (second >= 0 && world.player.animation == "stay") { ended = world.nowMs(); break; }
        }
        check(first == 250 && second == 450 && ended == 1000,
              "Both-facing three-swing queue uses native frame5/4 (250/200ms source at current 100% clock), weapon " + std::to_string(weapon));
        int transitions = 0;
        for (const auto &event : world.events) if (event.kind == "basic_chain") {
            check(event.source == transitions && event.target == transitions + 1 && event.value == (transitions == 0 ? 5 : 4),
                  "Native cancel table is zero-indexed and exhausts after the second transition");
            ++transitions;
        }
        check(transitions == 2, "Final swing cannot gain an invented third cancel threshold");
        samples.push_back({{"weapon", weapon}, {"direction", direction}, {"second_swing_ms", first},
                           {"third_swing_ms", second}, {"finished_ms", ended}});
    }
    {
        World world(pvf, assets); world.normalAttack();
        for (int tick = 0; tick < 25; ++tick) step(world);
        check(world.nowMs() == 416 && world.player.animation == "attack1", "Without queued input the native cancel window does not cut off recovery");
        world.normalAttack(); step(world);
        check(world.player.animation == "attack2" && world.player.poseFrame == 0,
              "A new attack after the threshold chains on the next eligible tick without waiting for ANI end");
    }
    {
        World world(pvf, assets); world.normalAttack();
        for (int tick = 0; tick < 36; ++tick) step(world);
        check(world.player.animation == "stay" && world.nowMs() == 600,
              "An unqueued first swing still plays its complete 600ms source animation");
    }
    {
        World world(pvf, assets); world.normalAttack(); world.normalAttack();
        for (int tick = 0; tick < 14; ++tick) step(world);
        check(world.player.animation == "attack1", "Queued first swing cannot chain before source frame5");
        world.player.hitStopTicks = 5;
        for (int tick = 0; tick < 5; ++tick) {
            step(world);
            check(world.player.animation == "attack1" && world.player.hitStopped,
                  "Local hit pause rejects next-swing transition and freezes the current cancel-frame clock");
        }
        step(world);
        check(world.player.animation == "attack2" && world.player.poseFrame == 0,
              "Queued native transition resumes at its threshold on the first unfrozen tick");
    }
    for (int direction : {-1, 1}) {
        World world(pvf, assets, WorldRules::BetaFoundationV1);
        world.freezeAi = true; world.monsters.clear(); world.player.dir = direction;
        world.player.x = world.player.px = 500;
        int skillIndex = -1;
        for (size_t i = 0; i < world.skills.size(); ++i)
            if (world.skills[i].identity() == SkillKey{0,8}) skillIndex = int(i);
        check(skillIndex >= 0, "Triple Slash resolves the actual job-local source skill");
        const auto *finish = world.characterCatalog().at(0).resource("[etc attack info]", 7);
        check(finish && finish->exists, "Current CHR supplies a dedicated three-slash finisher attack");
        world.activate(skillIndex);
        std::set<int> phases, visualPhases;
        for (int tick = 0; tick < 120; ++tick) {
            if (world.activeSkill() == skillIndex) world.activate(skillIndex);
            step(world);
            for (const auto &volume : world.attackVolumes) if (volume.skillId == 8) {
                phases.insert(volume.skillPhase);
                const size_t slot = volume.skillPhase == 2 ? 7 : size_t(2 + volume.skillPhase);
                const auto *binding = world.characterCatalog().at(0).resource("[etc attack info]", slot);
                check(binding && volume.sourceAttack && volume.sourceAttack->source.path == binding->path,
                    "Actual World collision volume consumes its current CHR phase attack binding");
            }
            for (const auto &event : world.events) if (event.kind == "stage" && event.value == 8 &&
                !visualPhases.count(event.name.back() - '0')) {
                const int phase = event.name.back() - '0';
                const auto expected = "character/swordman/effect/animation/tripleslash/move" + std::to_string(phase % 2 + 1) + ".ani";
                bool found = false;
                for (const auto &effect : world.effects) if (effect.animation == expected && world.nowMs() - effect.born <= 17) {
                    found = true;
                    check(effect.offsetX == -70 && effect.offsetY == -25 &&
                        !effect.damageEnabled && effect.layer == 0,
                        "Triple Slash shared stage table preserves the existing World movement visual policy");
                }
                if (found) visualPhases.insert(phase);
            }
            if (world.activeSkill() < 0) break;
        }
        check(visualPhases == std::set<int>{0,1,2}, "Each real stage installs Move1/Move2/Move1 from the reconstructed stage binding");
        check(phases == std::set<int>{0,1,2} && world.activeSkill() < 0,
            "Both-facing Triple Slash reaches each source attack phase and releases the actor");
        RegionCatalog regions(pvf, assets); Progression progression(regions);
        World contact(pvf, assets, WorldRules::BetaFoundationV1);
        contact.applyEquipment(progression);
        contact.freezeAi = true; contact.combat = true; contact.monsters.clear();
        contact.player.x = contact.player.px = 500; contact.player.dir = direction;
        contact.activate(skillIndex);
        bool spawned = false, hit = false;
        for (int tick = 0; tick < 120 && contact.activeSkill() >= 0; ++tick) {
            if (contact.stage() < 2) contact.activate(skillIndex);
            if (contact.stage() == 2 && !spawned) {
                Actor target; target.id = 1; target.monsterPath = "monster/goblin/goblin.mob";
                contact.initializeMonsterAttributes(target, 1, "inferred-mob-table-hp-v1", "inferred-mob-combat-table-v1");
                target.hp = target.maxHp = 100000;
                contact.monsters.push_back(std::move(target)); spawned = true;
            }
            int before = 0;
            if (spawned) {
                auto &target = contact.monsters.front();
                target.x = target.px = contact.player.x + direction * 50;
                target.y = target.py = contact.player.y; target.z = target.pz = 0;
                target.vx = target.vy = target.vz = 0; before = target.hp;
            }
            step(contact);
            if (spawned && contact.monsters.front().hp < before) {
                const auto damage = contact.statReport().at("last_damage");
                const auto &source = damage.at("sources").at("skill");
                check(damage.at("usable").get<bool>() && damage.at("hp_damage").get<int>() == before - contact.monsters.front().hp &&
                    source.at("percent") == float(contact.skills[skillIndex].parameter(1)) &&
                    source.at("fixed_damage") == float(contact.skills[skillIndex].parameter(4)),
                    "Both-facing finisher accepted contact uses source final coefficient columns and commits the resolved HP amount");
                hit = true; break;
            }
        }
        check(hit, "A real target is hit by the final Triple Slash in each facing");
        samples.push_back({{"kind", "triple-slash-source-binding"}, {"direction", direction},
            {"finisher_attack", finish->path}, {"accepted_damage", contact.statReport().at("last_damage")}});
    }
    for (bool lab : {false, true}) for (int direction : {-1, 1}) {
        World world(pvf, assets, WorldRules::BetaFoundationV1);
        world.unlockAllSkills(lab); world.freezeAi = true; world.monsters.clear();
        world.player.x = world.player.px = 500; world.player.dir = direction;
        int index = -1;
        for (size_t i = 0; i < world.skills.size(); ++i)
            if (world.skills[i].identity() == SkillKey{0,5}) index = int(i);
        check(index >= 0, "Ghost Slash resolves its own registered skill");
        world.activate(index);
        check(world.activeSkill() == index, "Ghost Slash starts through the actual World with lab=" + std::to_string(lab));
        int layers = 0;
        for (const auto &effect : world.effects) if (effect.skill == 5 && effect.attached) {
            check(effect.x == world.player.x && effect.offsetX == 0 && effect.offsetY == 0 &&
                !effect.damageEnabled && effect.layer == 0,
                "Ghost Slash shared stage table preserves the existing World visual policy");
            ++layers;
        }
        check(layers == 2, "Ghost Slash installs exactly its two existing World visual roots");
        const auto *body = world.characterCatalog().at(0).resource("[etc motion]", 1);
        check(body && world.actorAni() == body->path, "Ghost Slash body consumes the current CHR phase slot");
        for (int tick = 0; tick < 180 && world.activeSkill() >= 0; ++tick) step(world);
        check(world.activeSkill() < 0 && !world.armor() && !world.invincible(), "Ghost Slash releases action and protection");
        samples.push_back({{"kind", "ghost-slash-stage-binding"}, {"direction", direction}, {"lab", lab}, {"visual_offset_x", 0}});
    }
    check(!swordmanStageBinding({1,5}, 1, 0) && !swordmanStageBinding({0,8}, 3, 3),
        "Stage lookup rejects other jobs and out-of-range phases without a fallback");
    for (int direction : {-1, 1}) {
        World world(pvf, assets, WorldRules::BetaFoundationV1);
        world.unlockAllSkills(); world.freezeAi = true; world.monsters.clear(); world.player.dir = direction;
        int guard = -1;
        for (size_t i = 0; i < world.skills.size(); ++i)
            if (world.skills[i].identity() == SkillKey{0,1}) guard = int(i);
        check(guard >= 0, "Guard input fixture resolves its job-local controller");
        world.bindings.fill(-1);
        world.bindings[0] = guard; world.bindings[1] = guard;
        const auto input = [&](int key, bool down) {
            world.enqueue({world.simulationNanoseconds(), key, down}); step(world);
        };
        input(20, true);
        check(world.activeSkill() == guard, "Rebound Guard starts through actual input");
        for (int key : {4, 6, 7, 32}) {
            input(key, true); input(key, false);
            check(world.activeSkill() == guard, "Unrelated key release preserves held rebound Guard");
        }
        input(21, true); input(20, false);
        check(world.activeSkill() == guard, "Another held Guard binding preserves the action");
        input(21, false);
        check(world.activeSkill() < 0,
            "Final Guard binding release finishes on the next simulation tick; active=" + std::to_string(world.activeSkill()));
        int costs = 0;
        for (const auto &event : world.events) if (event.kind == "skill_cost" && event.name == world.skills[guard].key) ++costs;
        check(costs == 1, "Held Guard and alternate binding do not repeat the skill cost transaction");
        samples.push_back({{"kind", "rebound-guard-key-release"}, {"direction", direction}});
    }
    {
        World catalog(pvf, assets, WorldRules::BetaFoundationV1);
        catalog.unlockAllSkills();
        const auto &reflect = catalog.characterCatalog().skillDefinition({0,2});
        const auto types = reflect.fieldsInScope("[type]");
        check(types.size() == 1 && types.front()->field.values == Json::array({"[active]"}) &&
            reflect.kind == SkillSourceKind::Active, "Current reflectguard unique common type is ACTIVE, not an imported passive assumption");
        samples.push_back({{"kind", "reflectguard-source-type"}, {"source", reflect.source.script.path},
            {"type", types.front()->field.values}, {"field_offset", types.front()->field.offset}});
        for (const auto &skill : catalog.skills) {
            if (skill.manualVisuals) continue;
            World world(pvf, assets, WorldRules::BetaFoundationV1);
            world.unlockAllSkills(); world.freezeAi = true; world.monsters.clear();
            int index = -1;
            for (size_t i = 0; i < world.skills.size(); ++i)
                if (world.skills[i].identity() == skill.identity()) index = int(i);
            try {
                world.activate(index);
                for (int tick = 0; tick < 600 && world.activeSkill() >= 0; ++tick) step(world);
            } catch (const std::exception &error) {
                throw std::runtime_error("Mapped Swordman skill " + std::to_string(skill.id) + " (" + skill.key + "): " + error.what());
            }
            check(world.attackVolumes.empty(), "Mapped Swordman preview cannot publish unbound body damage: " + skill.key);
            for (const auto &effect : world.effects)
                check(!effect.damageEnabled, "Mapped Swordman preview cannot publish unbound object damage: " + skill.key);
            check(std::any_of(world.events.begin(), world.events.end(), [&](const auto &event) {
                return event.kind == "skill_damage_unavailable" && event.value == skill.id;
            }), "Mapped Swordman preview explicitly reports missing attack controller: " + skill.key);
            samples.push_back({{"kind", "mapped-swordman-lab-action"}, {"skill", skill.id}, {"key", skill.key},
                {"active_after_600_ticks", world.activeSkill() >= 0}});
            world.changeScene();
            check(world.activeSkill() < 0 && world.effects.empty(), "Scene transition cancels mapped action and its effects: " + skill.key);
            world.enqueue({world.simulationNanoseconds(), 4, true}); step(world);
            check(world.activeSkill() < 0 && world.player.animation == "attack1", "Actual X input works after mapped preview scene cancellation: " + skill.key);
            bool normalVolumes = false;
            for (int tick = 0; tick < 60; ++tick) { step(world); normalVolumes |= !world.attackVolumes.empty(); }
            check(normalVolumes, "Normal source attack volumes remain available after mapped preview: " + skill.key);
        }
    }
    std::vector<int> candidates{46,5,20,64,77};
    std::mt19937 random(20261121); std::shuffle(candidates.begin(), candidates.end(), random);
    for (int sample = 0; sample < 3; ++sample) {
        World world(pvf, assets, WorldRules::BetaFoundationV1);
        world.unlockAllSkills(); world.freezeAi = true; world.monsters.clear();
        int index = -1;
        for (size_t i = 0; i < world.skills.size(); ++i) if (world.skills[i].id == candidates[sample]) index = int(i);
        check(index >= 0, "Seeded smoke sample resolves an existing source skill");
        world.activate(index);
        check(world.activeSkill() == index, "Seeded smoke sample enters its actual skill controller");
        for (int tick = 0; tick < 240 && world.activeSkill() >= 0; ++tick) {
            if (world.skills[index].continuation) world.activate(index);
            step(world);
        }
        check(world.activeSkill() < 0 && !world.armor() && !world.invincible(),
            "Seeded other-skill lab smoke releases action and protection without changing normal qualification");
        samples.push_back({{"kind", "seeded-other-skill-smoke"}, {"seed", 20261121}, {"skill", candidates[sample]}});
    }
    return {{"status", "pass"}, {"checks", checks}, {"check_count", checks.size()}, {"samples", samples},
        {"scope", "Default unadvanced Swordman source-frame chain and local pause; native +1A4 semantics, attack speed, skill cancels and other playable jobs remain pending"}};
}
} // namespace dnf
