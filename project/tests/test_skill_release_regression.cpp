#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include <stdexcept>

namespace dnf {
Json runSkillReleaseRegressionTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), casts = Json::array();
    const auto require = [&](bool ok, const char *message) {
        if (!ok) throw std::runtime_error(std::string("Skill release regression: ") + message);
        checks.push_back(message);
    };
    // Reproduce a real character, source learning, test overlay and World
    // cooldown consumer. No monster/contact is needed to trigger the old exit.
    for (const auto policy : {std::optional<ani_clock::ClockPolicy>{},
            std::optional<ani_clock::ClockPolicy>{ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}}) {
        for (const int skillId : {8, 20, 64}) {
            RegionCatalog regions(pvf, assets);
            Progression progression(regions); progression.initialize(4);
            World world(pvf, assets, WorldRules::BetaFoundationV1);
            world.applyEquipment(progression);
            world.configureAnimationClock(policy);
            const auto initialized = world.skillLearning().prepareInitialization(
                CharacterSkillState(world.identity()), 4, SkillInitializationMode::NewCharacter, world.nowMs());
            require(initialized.ok, "real source initialization succeeds");
            world.publishSkillLedger(initialized.state);
            world.freezeAi = true; world.combat = false;
            DebugOverrides debug; debug.enabled = true; debug.level = 30; debug.mpLock = true;
            world.applyDebugOverrides(debug, 4);
            int skillIndex = -1;
            for (size_t i = 0; i < world.skills.size(); ++i)
                if (world.skills[i].id == skillId) skillIndex = int(i);
            require(skillIndex >= 0, "source skill has an actual World controller");
            const auto normalBefore = world.skillState().snapshot(world.nowMs());
            require(world.skillState().learnedLevel({0, skillId}) == 0,
                "test purchase begins with the skill absent from normal learning");
            const auto quote = world.quoteTestSkillLearning({0, skillId});
            require(quote.accepted(), "test level opens a source-qualified isolated purchase");
            require(world.learnTestSkill({"crash-regression-purchase", {0, skillId}, quote.revision, quote.targetLevel}).ok,
                "test skill is learned through the real test learning service");
            const auto overlay = world.skillTestOverlay().snapshot();
            // All three use actual activation. Skill8 starts CD on exit,
            // whereas 20/64 start CD before their first attack frame.
            for (int repetition = 0; repetition < 3; ++repetition) {
                while (world.remainingCd(skillIndex) > 0) {
                    world.advanceSingleTick();
                    require(world.skillUseEligibility({0, skillId}).allowed(),
                        "cooldown passage retains the learned test skill");
                }
                world.activate(skillIndex);
                require(world.activeSkill() == skillIndex, "empty cast reaches its real controller");
                for (int step = 0; step < 180 && world.activeSkill() >= 0; ++step) {
                    world.advanceSingleTick();
                    (void)world.snapshot(); // HUD/diagnostic passive consumers.
                }
                require(world.activeSkill() < 0, "empty cast naturally ends without an exception");
                require(world.skillUseEligibility({0, skillId}).allowed(),
                    "new cooldown-only normal row does not invalidate the test overlay");
                require(world.skillState().learnedLevel({0, skillId}) == 0 &&
                    world.skillState().snapshot(world.nowMs()).at("learning") == normalBefore.at("learning") &&
                    world.skillTestOverlay().snapshot() == overlay,
                    "casting changes neither normal purchases/points nor isolated learning receipts");
            }
            // Exercise the real serialized test overlay + skill ledger route.
            const auto saved = world.skillState().snapshot(world.nowMs());
            CharacterSkillState restored(world.identity()); restored.restore(saved, world.nowMs());
            SkillLearningTestOverlay restoredOverlay; restoredOverlay.restore(overlay);
            require(restoredOverlay.effectiveState(restored, world.nowMs()).learnedLevel({0, skillId}) == 1,
                "ledger and overlay restore after casting remains usable");
            world.idle(); world.applyDebugOverrides({}, 4);
            require(world.skills[size_t(skillIndex)].level == 0 && world.skillState().learnedLevel({0, skillId}) == 0,
                "leaving test mode removes test learning from the active projection");
            world.applyDebugOverrides(debug, 4);
            require(world.skills[size_t(skillIndex)].level == 1,
                "reentering test mode preserves the independent purchased level");
            casts.push_back({{"skill_id", skillId}, {"clock", policy ? "inferred60us" : "legacy"},
                {"empty_casts", 3}, {"normal_ledger_unchanged", true}});
        }
    }
    for(const int direction:{-1,1}) {
        World world(pvf,assets);world.god=world.freeCd=world.freezeAi=true;
        world.mapWidth=2200;world.walkRects={{0,180,2200,300}};
        world.player.x=world.player.px=1000;world.player.y=world.player.py=300;world.player.dir=direction;
        int triple=-1,hop=-1;
        for(size_t i=0;i<world.skills.size();++i){if(world.skills[i].id==8)triple=int(i);if(world.skills[i].id==65)hop=int(i);}
        require(triple>=0&&hop>=0,"Response fixtures use registered source skill controllers");
        world.activate(triple);world.activate(triple);
        for(int tick=0;tick<13;++tick)world.advanceSingleTick();
        require(world.activeSkill()==triple&&world.stage()==1,
            "Queued Triple Slash advances after consuming body frame3, without waiting the source tail hold");
        const auto secondStart=world.nowMs();world.activate(triple);
        for(int tick=0;tick<13;++tick)world.advanceSingleTick();
        require(world.activeSkill()==triple&&world.stage()==2&&world.nowMs()-secondStart<300,
            "The second queued Triple Slash boundary advances with no intervening idle tick");
        int costs=0;for(const auto &event:world.events)if(event.kind=="skill_cost"&&event.name==world.skills[triple].key)++costs;
        require(costs==1,"Triple Slash continuation spends MP only in the initial skill transaction");
        world.idle();world.bindings[0]=hop;
        world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        require(world.activeSkill()==hop&&world.stage()==0&&world.player.poseFrame==0,
            "Hop Smash input starts its real preparation first frame in the admission tick");
        world.enqueue({world.simulationNanoseconds(),20,false});world.advanceSingleTick();
        require(world.activeSkill()==hop&&world.stage()==1,
            "Hop Smash command release exits preparation at the next tick instead of waiting400ms");
        world.idle();world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        for(int tick=0;tick<10;++tick)world.advanceSingleTick();
        require(world.activeSkill()==hop&&world.stage()==0,
            "Holding Hop Smash preserves the authored preparation and charge behavior");
        for(int tick=0;tick<16;++tick)world.advanceSingleTick();
        require(world.activeSkill()==hop&&world.stage()==1,
            "Held Hop Smash leaves preparation at its finite source ANI deadline");
    }
    return {{"status", "pass"}, {"checks", checks}, {"count", checks.size()}, {"cases", casts},
        {"scope", "Actual source-learned test skills, empty casts, cooldown insertion/expiry, ledger restore and debug toggles"}};
}
} // namespace dnf
