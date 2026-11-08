#include "dnf/combat.hpp"
#include "dnf/collision.hpp"
#include "dnf/session.hpp"
#include <cmath>
#include <stdexcept>

namespace dnf {
Json runMonsterEffectsTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), motions = Json::array();
    auto require = [&](bool value, const std::string &name) {
        if (!value) throw std::runtime_error(std::string("Monster effects: ") + name);
        checks.push_back(name);
    };
    const std::string goblin = "monster/goblin/goblin.mob";
    const std::string cat = "monster/lugaru/lugaru.mob";
    const std::string ghost = "monster/act8/ghost_flu/ghost_flu.mob";
    const std::string chief = "monster/act8/chiefsars/chiefsars.mob";
    auto one = compileMonsterMotion(pvf, assets, goblin, "damage1");
    auto two = compileMonsterMotion(pvf, assets, goblin, "damage2");
    require(one->valid() && two->valid() && one->base->path != two->base->path,
            "MOB damage1 and damage2 select distinct actual resources");
    require(!compileMonsterMotion(pvf, assets, goblin, "death")->configured,
            "no independent death invented for a MOB without last action");
    auto death = compileMonsterMotion(pvf, assets, chief, "death");
    require(death->valid() && death->bindingTag == "[last action]" && death->tracks.size() >= 4,
            "last-action ACT composes its base and all configured sub animations");
    auto ghostDeath = compileMonsterMotion(pvf, assets, ghost, "death");
    require(ghostDeath->valid() && ghostDeath->entry.find(".act") != std::string::npos,
            "ACT-backed independent death is playable");
    require(death->issues.empty(), "a source MOTION-only death does not invent unexecuted behavior");
    const auto ghostDamage = compileMonsterMotion(pvf, assets, ghost, "damage1");
    require(ghostDamage->valid() && !ghostDamage->issues.empty(),
            "actual ghost damage ACT TRIGGER/BEHAVIOR remains diagnostic");
    for (const auto &path : {goblin, cat, ghost, chief,
            std::string("monster/act8/wooden_doll/wooden_doll.mob"),
            std::string("monster/event/bluemarble/dendroid_disguise/dendroid_disguise.mob")}) {
        for (const auto &state : {"idle", "damage1", "damage2"}) {
            const auto plan = compileMonsterMotion(pvf, assets, path, state);
            require(plan->valid(), "six supplied example MOBs resolve current-PVF living motion plans");
            motions.push_back({{"monster", path}, {"state", state}, {"entry", plan->entry},
                               {"duration_ms", plan->duration}, {"tracks", plan->tracks.size()},
                               {"references", plan->references}, {"issues", plan->issues}});
        }
    }
    const auto profile = readMonsterDeathProfile(pvf, assets, goblin);
    const auto catProfile = readMonsterDeathProfile(pvf, assets, cat);
    const auto omitted = readMonsterDeathProfile(pvf, assets, ghost);
    require(profile.valid && profile.pieces && profile.palette == 1 && profile.count == 10 &&
            profile.lifeMs == 3000 && profile.gravity == 1500 && profile.speed == 400,
            "current PTL count, gravity, lifetime and speed are consumed without replacing source data");
    require(catProfile.valid && catProfile.palette == 9 && catProfile.image != profile.image,
            "MOB palettes select different original stone IMG resources");
    require(omitted.valid && !omitted.pieces && omitted.smoke && omitted.flash,
            "MOB omit bit1 suppresses stones while preserving smoke and flash");
    require(monsterDeathFragments(1, omitted, {-20, -60, 40, 60}, 0, {}).empty(),
            "an omitted stone branch emits no derived particles");
    const auto idle = compileMonsterMotion(pvf, assets, goblin, "idle");
    {
        auto longDecoration = *idle;
        longDecoration.duration = idle->base->duration + 1000;
        const auto bodyDuration = double(idle->base->duration);
        require(bodyDuration > 0 && monsterMotionTime(longDecoration, bodyDuration + 30, true) ==
                    std::fmod(30.0, bodyDuration),
                "A longer attachment cannot lengthen the live body movement or hurtbox cycle");
        require(monsterMotionTime(longDecoration, bodyDuration + 30, false) == bodyDuration + 30,
                "One-shot composed death keeps its full child lifetime rather than wrapping the body");
        MonsterTrack base, rear, nestedFront, front;
        base.role = "base"; rear.role = "rear"; nestedFront.role = "nested-front"; front.role = "front";
        rear.layer = -10; rear.drawOrder = {{-10, 1}};
        nestedFront.layer = 990; nestedFront.drawOrder = {{-10, 1}, {1000, 2}};
        front.layer = 1; front.drawOrder = {{1, 3}};
        std::vector<MonsterTrack> ordered{front, nestedFront, base, rear};
        std::stable_sort(ordered.begin(), ordered.end(), monsterTrackBefore);
        require(ordered[0].role == "rear" && ordered[1].role == "nested-front" &&
                    ordered[2].role == "base" && ordered[3].role == "front",
                "Recursive 40JP draw groups keep a rear parent's positive child behind the actor body");
    }
    const auto rightBounds = monsterMotionBounds(assets, *idle, 30, true, 1);
    const auto leftBounds = monsterMotionBounds(assets, *idle, 30, true, -1);
    require(std::abs(rightBounds[0] + rightBounds[2] + leftBounds[0]) < .001 &&
            std::abs(rightBounds[2] - leftBounds[2]) < .001,
            "frozen crop/ANI bounds reflect facing once");
    const auto seed = monsterDeathSeed(goblin, 1, 123);
    require(seed != monsterDeathSeed(goblin, 2, 123), "same-MOB instances have independent stable particle seeds");
    for (const auto &direction : std::array<std::array<double, 2>, 4>{{{{1, 0}}, {{-1, 0}}, {{0, 1}}, {{0, -1}}}}) {
        const auto weak = monsterDeathImpulse(direction[0], direction[1], -1, 40, 5, 100, 30, 0);
        const auto strong = monsterDeathImpulse(direction[0], direction[1], -1, 600, 100, 100, 300, 250);
        const auto first = monsterDeathFragments(seed, profile, rightBounds, 0, weak);
        const auto second = monsterDeathFragments(seed, profile, rightBounds, 0, strong);
        require(first.size() == 10 && first.size() == second.size(), "source PTL particle count is stable");
        for (size_t i = 0; i < first.size(); ++i) {
            const double a = first[i].vx * direction[0] + first[i].vy * direction[1];
            const double b = second[i].vx * direction[0] + second[i].vy * direction[1];
            require(a > 0 && b > a, "stones travel away from the attack on either ground-plane axis; stronger faster hits travel faster");
        }
        const auto pose = monsterFragmentPose(second[0], .2, profile.gravity);
        const auto repeated = monsterFragmentPose(second[0], .2, profile.gravity);
        const auto landed = monsterFragmentPose(second[0], 30, profile.gravity);
        const auto held = monsterFragmentPose(second[0], 60, profile.gravity);
        require(pose.x == repeated.x && pose.y == repeated.y && pose.z == repeated.z &&
                landed.z == 0 && held.z == 0 && landed.x == held.x && landed.y == held.y,
                "absolute-time particle sampling is seek deterministic and stops after landing");
    }
    auto fixture = [&](World &world, const std::string &path) {
        world.freezeAi = true; world.combat = true;
        world.player.x = world.player.px = 300; world.player.y = world.player.py = 300;
        Actor target; target.id = 1; target.monsterPath = path;
        target.x = target.px = 350; target.y = target.py = 300;
        world.monsters.push_back(target);
    };
    for(int direction:{-1,1}) {
        World world(pvf,assets);fixture(world,goblin);
        auto &target=world.monsters.front();target.dir=direction;
        const auto motion=compileMonsterMotion(pvf,assets,goblin,target.animation);
        require(motion->valid(),"Contact-output fixture has a real current-MOB base motion");
        const auto elapsed=monsterMotionTime(*motion,world.nowMs()-target.animStart,true);
        const auto &frame=motion->base->frames[motion->base->frameAt(elapsed,false)];
        const Box *hurt=nullptr;for(const auto &box:frame.boxes)if(box.type==14&&box.w&&box.h&&box.d){hurt=&box;break;}
        require(hurt!=nullptr,"Contact-output fixture uses the MOB's actual nonzero type14 hurtbox");
        const auto expected=combatBox(*hurt,target.x,target.y,target.z,target.dir);
        Actor origin;origin.x=target.x;origin.y=target.y;origin.z=target.z;origin.dir=direction;
        CombatBox overlap;
        require(world.overlaps(origin,Box{15,-1000,-1000,-1000,2000,2000,2000},target,&overlap)&&
                overlap.x==expected.x&&overlap.y==expected.y&&overlap.z==expected.z&&
                overlap.w==expected.w&&overlap.h==expected.h&&overlap.d==expected.d,
                "Live World contact returns the actual mirrored XYZ intersection without changing boolean contact eligibility");
    }
    {
        World world(pvf, assets); fixture(world, goblin);
        auto &target = world.monsters[0];
        target.animation = "move"; target.animStart = -130; target.hp = 0; target.dead = true;
        world.advance(16666667);
        require(target.deathRoute == "shared-source-palette" && target.deathMotion &&
                target.deathMotion->state == "move" && target.deathPoseTime > 130 &&
                target.deathFragments.size() == 10,
                "explicit death freezes the current moving pose before common white/stone sequence");
        world.advance(250000000);
        require(target.life == ActorLife::DeathEffect, "shared death enters its effect phase at reconstructed burst clock");
        world.advance(3200000000ll);
        require(target.life == ActorLife::Removed, "shared particles complete and dying actor is removed");
    }
    {
        World world(pvf, assets); fixture(world, ghost);
        auto &target = world.monsters[0]; target.hp = 0; target.dead = true;
        world.advance(16666667);
        require(target.independentDeath && target.deathRoute == "last-action" &&
                target.deathFragments.empty() && target.deathPoseTime == 0,
                "an explicit playable last action chooses independent death without synthetic stones");
        world.advance(int64_t(target.deathDuration + 100) * 1000000);
        require(target.life == ActorLife::Removed, "independent composed death completes its source plan before removal");
    }
    {
        World world(pvf, assets); fixture(world, goblin);
        auto &target = world.monsters[0]; target.hp = target.maxHp = 100000;
        target.z = target.pz = 55; target.vz = -30; target.recovery = 1;
        target.animation = "damage2";
        world.normalAttack();
        for (int i = 0; i < 30 && target.hp == target.maxHp; ++i) world.advance(16666667);
        require(target.hp < target.maxHp && target.vz > 0 && target.recovery == 1 &&
                target.hitReaction.state == 4 && target.animation == "down",
                "ordinary accepted sword hit applies damage and binds the 40JP state4 airborne/down pose");
        bool feedback = false;
        for (const auto &fx : world.effects) if (fx.phase == "hit-feedback") feedback = !fx.damageEnabled;
        require(feedback, "accepted airborne hit stages a real non-damaging common hit ANI safely");
    }
    {
        World world(pvf, assets); fixture(world, goblin);
        auto &target = world.monsters[0];
        target.z = target.pz = 1; target.vz = -60; target.recovery = 1;
        target.animation = "damage2"; target.animationPath = two->base->path;
        const auto down = compileMonsterMotion(pvf, assets, goblin, "down");
        const auto up = compileMonsterMotion(pvf, assets, goblin, "sit");
        require(down->valid() && up->valid() && down->base->path != two->base->path &&
                up->base->path != down->base->path,
                "source goblin down and sit bindings differ from airborne damage2");
        world.advance(16666667);
        require(target.recovery == 2 && target.animation == "down" &&
                target.animationPath == down->base->path &&
                world.nowMs() - target.animStart >= down->base->duration - down->base->frames.back().duration &&
                target.stunUntil - world.nowMs() <= 500,
                "landing selects actual down binding without inheriting airborne override");
        for (int i = 0; i < 300 && target.recovery == 2; ++i) world.advance(16666667);
        require(target.recovery == 3 && target.animation == "sit" &&
                target.animationPath == up->base->path,
                "getting up selects actual sit binding without inheriting down override");
        for (int i = 0; i < 300 && target.recovery == 3; ++i) world.advance(16666667);
        require(target.recovery == 0 && target.animation == "stay" && target.animationPath.empty(),
                "source grounded pose and sit recovery complete and clear their explicit path");
    }
    for (const auto &path : {goblin, ghost, chief}) {
        World original(pvf, assets); fixture(original, path);
        original.monsters[0].hp = 1;
        original.diagnosticHit(1, 100, 0, 0, 1, {250, 300, 440});
        original.advance(400000000);
        const auto before = saveActor(original.monsters[0], original.nowMs());
        // An isolated single-room session exercises the real remember/restore
        // path. Dungeon generation is orthogonal to actor rehydration here.
        RegionSession session;
        session.run.rooms.resize(1); session.roomStates.resize(1);
        session.remember(original);
        session.roomStates[0] = Json::parse(session.roomStates[0].dump());
        World restored(pvf, assets); restored.freezeAi = true;
        restored.advance(5000000000ll);
        require(session.restore(restored), "remembered death restores through RegionSession");
        const auto &actor = restored.monsters[0];
        require(saveActor(actor, restored.nowMs()) == before,
                "cross-clock JSON reload preserves complete death source identity, ages, anchors, impulse and initial fragments");
        require(actor.deathMotion && actor.deathMotion->valid() &&
                restored.nowMs() - actor.deathStart == original.nowMs() - original.monsters[0].deathStart,
                "restored source motion is recompiled without restarting its death clock");
        if (!actor.deathFragments.empty()) {
            const double seconds = (restored.nowMs() - actor.deathStart - monsterDeathBurstMs) / 1000.0;
            const auto a = monsterFragmentPose(actor.deathFragments[0], seconds, actor.deathProfile.gravity);
            const auto b = monsterFragmentPose(original.monsters[0].deathFragments[0], seconds,
                                                original.monsters[0].deathProfile.gravity);
            require(a.x == b.x && a.y == b.y && a.z == b.z && a.angle == b.angle,
                    "a saved moving stone keeps the exact sampled trajectory after restore");
        }
        restored.advance(int64_t(actor.deathDuration + 100) * 1000000);
        require(restored.monsters[0].life == ActorLife::Removed,
                "restored independent/shared deaths finish and remain removed");
        bool rewarded = false;
        for (const auto &event : restored.events) if (event.kind == "killed") rewarded = true;
        require(!rewarded, "restoring and completing death never emits duplicate killed/reward events");
        session.remember(restored);
        World removed(pvf, assets); removed.advance(9000000000ll);
        require(session.restore(removed) && removed.monsters[0].life == ActorLife::Removed,
                "removed actors stay removed on another room revisit");
    }
    {
        World original(pvf, assets); fixture(original, goblin);
        original.monsters[0].animation = "move";
        original.monsters[0].animStart = -125;
        original.monsters[0].hp = 1;
        original.diagnosticHit(1, 100, 0, 0, 1, {250, 300, 440});
        original.advance(450000000);
        auto legacy = saveActor(original.monsters[0], original.nowMs());
        for (const auto *key : {"death_visual_version", "death_route", "independent_death", "death_duration",
                "death_loop", "death_anchor", "death_bounds", "death_motion", "death_profile", "last_impact", "death_fragments"})
            legacy.erase(key);
        World restored(pvf, assets); restored.advance(4000000000ll);
        auto actor = loadActor(legacy, restored.nowMs());
        restored.restoreMonsterVisuals(actor);
        require(actor.dead && actor.life != ActorLife::Alive && actor.deathMotion && actor.deathMotion->valid() &&
                actor.deathAnchorX == legacy["x"].get<double>() && actor.deathAnchorY == legacy["y"].get<double>() &&
                actor.deathPoseTime == legacy["death_pose_time"].get<int64_t>() &&
                restored.nowMs() - actor.deathStart == legacy["death_age"].get<int64_t>(),
                "legacy dead actor rebuilds from its saved position/pose/age instead of zero anchor or replay");
        require(restored.events.empty(), "legacy visual rehydration does not synthesize a second death event");
    }
    return {{"status", "pass"}, {"checks", checks}, {"motion_samples", motions},
            {"scope", "current-PVF resource plans, explicit lifecycle and actual accepted sword-hit physics; no native timing/formula or SDL visual parity claim"}};
}
} // namespace dnf
