#include "dnf/combat.hpp"
#include "dnf/collision.hpp"
#include "dnf/session.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
constexpr int64_t feedbackStepNs = 16666667;
void feedbackStep(World &world) { world.advance(feedbackStepNs); }
void feedbackPress(World &world, int key) {
    const auto when = world.tick * 1000000000ll / 60;
    world.enqueue({when, key, true});
    world.enqueue({when + 40000000, key, false});
}
void feedbackFloor(World &world, int direction = 1) {
    world.combat = true;
    world.freezeAi = true;
    world.mapWidth = 1200;
    world.walkRects = {{0, 240, 1200, 240}};
    world.player.x = world.player.px = 560;
    world.player.y = world.player.py = 344;
    world.player.dir = direction;
}
void feedbackTarget(World &world, int id = 1, int hp = 100000) {
    Actor target;
    target.id = id;
    target.x = target.px = world.player.x + world.player.dir * 80;
    target.y = target.py = world.player.y;
    target.dir = -world.player.dir;
    target.hp = target.maxHp = hp;
    target.monsterPath = "monster/goblin/goblin.mob";
    world.monsters.push_back(target);
}
int feedbackHits(const World &world, int target = 1) {
    int result = 0;
    for (const auto &event : world.events)
        if (event.kind == "hit" && event.target == target) ++result;
    return result;
}
bool feedbackAwaitHit(World &world, int maxTicks = 180) {
    for (int frame = 0; frame < maxTicks; ++frame) {
        feedbackStep(world);
        if (feedbackHits(world)) return true;
    }
    return false;
}
Json feedbackPose(const Actor &actor, int64_t now) {
    return {{"animation", actor.animation}, {"animation_ms", now - actor.animStart},
            {"position", {actor.x, actor.y, actor.z}}, {"frame", actor.poseFrame}};
}
Json feedbackAttachments(const World &world) {
    Json result = Json::array();
    for (const auto &effect : world.effects) if (effect.attached)
        result.push_back({{"id", effect.id}, {"animation", effect.animation},
            {"animation_ms", world.nowMs() - effect.born + effect.animationOffset},
            {"remaining_ms", effect.expires - world.nowMs()},
            {"position", {effect.x, effect.y, effect.z}}, {"direction", effect.dir}});
    return result;
}
} // namespace

// These tests exercise accepted source-box contacts and the public input queue.
// A passing result establishes the reconstructed local-pause contract, never
// the original executable's complete attack-speed/hit-delay formula or feel.
Json runCombatFeedbackTests(Pvf &pvf, Assets &assets) {
    Json report = {{"status", "running"},
        {"scope", "60 Hz actor-local hit feedback, ordinary X input, source-box contacts, isolated projectile/accepted-hit fixtures and save compatibility; no original-client parity claim"},
        {"checks", Json::array()}, {"weapon_combos", Json::array()}};
    std::string checkpoint = "source weapon feedback";
    auto require = [&](bool condition, const std::string &message) {
        report["checks"].push_back({{"name", message}, {"pass", condition}});
        if (!condition) throw std::runtime_error("Combat feedback: " + message);
    };
    try {
        checkpoint = "shared AttackInfo response reader";
        {
            // Synthetic format fixtures exercise scope and token semantics;
            // these operands are not claimed to be native 1031 skill data.
            Script source; source.path="fixture/shared-response.atk";
            const auto token=[&](Json value){source.tokens.push_back({{"value",std::move(value)}});};
            source.fields={{"[push aside]",Json::array({30})},{"[pvp]",Json::array()},
                {"[push aside]",Json::array({900})},{"[/pvp]",Json::array()},
                {"[dungeon]",Json::array()},{"[push aside]",Json::array({12})},
                {"[hit wav]",Json::array({"DUNGEON_HIT"})},{"[/dungeon]",Json::array()}};
            token("[damage reaction]");token("[down]");
            token("[hit info]");token("[cut]");token("[blood]");token(40);token(1.0);
            token("[pvp]");token("[damage reaction]");token("[down]");token("[/pvp]");
            token("[dungeon]");token("[damage reaction]");token("[none]");
            token("[hit info]");token("[blow]");token("[no blood]");token(0);token(0.0);token("[/dungeon]");
            const auto explicitZero=readAttackResponse(source);
            require(explicitZero.push==12 && explicitZero.sound=="DUNGEON_HIT" &&
                    explicitZero.noReaction && !explicitZero.knockDown &&
                    explicitZero.hitPause==0 && explicitZero.hitDelayRate==0 && explicitZero.hitInfo[0]=="[blow]",
                    "Common reader selects dungeon operands, type-5 hit-info tokens and explicit zero; PvP cannot leak into PvE");
            source.tokens=Json::array();
            token("[hit info]");token("[cut]");token("[blood]");token(-1);token(-1.0);
            const auto inherited=readAttackResponse(source);
            require(inherited.hitInfo[2]==-1 && inherited.hitInfo[3]==-1.0,
                    "Common reader preserves negative timing operands for qualified caller inheritance");
            source.fields={{"[lift up]",Json::array({std::numeric_limits<double>::infinity()})}};
            bool rejected=false;try{readAttackResponse(source);}catch(const std::invalid_argument&){rejected=true;}
            require(rejected,"Nonfinite response impulse is rejected before a caller can publish HP or physics");
        }
        checkpoint = "40JP owner hit-info inheritance";
        {
            World world(pvf,assets);world.identity_={1,0,0};
            const auto attack=pvf.script("character/fighter/attackinfo/attack1.atk");
            const auto bare=world.characterAttackResponse(attack);
            require(bare.hitPause==0&&bare.hitDelayRate==0&&bare.hitInfo[0]=="[none]",
                    "Unarmed Fighter uses 40JP no-equipment getters, never an invented final CHR row or Swordman data");
            world.combatAttributes_=CombatAttributeSnapshot{};
            EquippedAttributeSource equipped;equipped.equippedSlot="[weapon]";
            equipped.source.path="fixture/owned-fighter-weapon.equ";
            equipped.source.fields={{"[sub type]",Json::array({0})}};
            world.combatAttributes_->equipmentSources.push_back(equipped);
            const auto row=world.characterSource().source.script.values("[weapon hit info]");
            const auto inherited=world.characterAttackResponse(attack);
            require(inherited.hitPause==row[2].get<double>()&&inherited.hitDelayRate==row[3].get<double>()&&
                    inherited.hitInfo[0]==row[0]&&inherited.hitInfo.size()==6&&inherited.hitInfo[4]==row[4],
                    "Owned EQU subtype selects this job's six-component CHR hit-info row and preserves its extra operands");
            Script explicitInfo;explicitInfo.path="fixture/owner-inheritance.atk";
            explicitInfo.tokens=Json::array({Json{{"value","[hit info]"}},Json{{"value","[cut]"}},
                Json{{"value","[blood]"}},Json{{"value",0}},Json{{"value",-1.0}}});
            const auto mixed=world.characterAttackResponse(explicitInfo);
            require(mixed.hitPause==0&&mixed.hitDelayRate==row[3].get<double>()&&mixed.hitInfo[0]=="[cut]",
                    "Explicit zero pause and explicit hit category survive independent negative rate inheritance");
            explicitInfo.tokens[3]["value"]=-1;explicitInfo.tokens[4]["value"]=0.0;
            const auto other=world.characterAttackResponse(explicitInfo);
            require(other.hitPause==row[2].get<double>()&&other.hitDelayRate==0,
                    "Negative pause inherits without replacing an explicitly disabled reaction rate");
        }
        checkpoint = "40JP directional accepted-hit presentation";
        {
            World world(pvf,assets);Actor target;target.id=1;target.x=560;target.y=344;
            AttackResponse response;response.source="fixture/hit-direction.atk";
            response.hitInfo=Json::array({"[cut]","[no blood]",0,1.0});
            const CombatBox contact{510,330,30,20,20,40};
            for(const auto &direction:std::array<std::pair<const char *,int>,3>{{
                    {"[hit lift up]",3},{"[hit horizon]",2},{"[hit down]",1}}}) {
                world.pendingEffects_.clear();response.attackDirection=direction.first;
                world.publishMonsterHitFeedback(target,response,1,1,false,&contact,true);
                require(world.pendingEffects_.size()==1&&
                    world.pendingEffects_.front().animation.find(std::to_string(direction.second)+".ani")!=std::string::npos&&
                    world.pendingEffects_.front().x==520&&world.pendingEffects_.front().y==344&&
                    world.pendingEffects_.front().z==50&&world.pendingEffects_.front().imageScale==1.5,
                    std::string("40JP cut spark uses contact X/Z, target ground Y, critical scale and source direction ")+direction.first);
            }
        }
        checkpoint = "40JP standing reaction arithmetic";
        {
            World world(pvf,assets);
            feedbackFloor(world);
            Actor target;target.id=1;target.x=560;target.y=344;
            // No MOB path deliberately selects the documented bridge defaults
            // rather than substituting a community template for current data.
            AttackResponse response;response.hitDelayRate=1;
            world.applyResponse(target,response,1);
            require(target.hitReaction.state==3&&target.hitReaction.remainingMs==375&&target.vx==400&&target.vy==0,
                    "40JP standing hit uses default hit recovery 500, duration 375ms and 400px/s linear slide");
            world.advanceMonsterHitReaction(target,150);
            require(std::abs(target.x-590.0075)<.001&&target.y==344&&target.z==0&&target.vx==0&&
                    target.hitReaction.remainingMs==225,
                    "Standing slide uses integer acceleration -2666 and stops at 150ms without radial Y or lift impulses");
            world.advanceMonsterHitReaction(target,225);
            require(target.hitReaction.state==0&&target.vx==0,
                    "Standing reaction releases ownership after its remaining source-derived duration");
            Actor magic;magic.x=560;magic.y=344;response.attackType="[magic]";
            world.applyResponse(magic,response,-1);
            require(magic.hitReaction.remainingMs==262&&magic.vx==-400,
                    "Magical standing reaction applies the native 70 percent delay before integer duration scaling");
            response.attackType="";response.hitDelayRate=0;
            world.applyResponse(magic,response,1);
            require(magic.hitReaction.remainingMs==1&&magic.hitReaction.accelerationRemainingMs==1,
                    "Explicit zero delay reaches the native one millisecond minimum rather than a guessed fixed stun");
            const auto before=saveActor(magic,world.nowMs());
            response.noReaction=true;world.applyResponse(magic,response,-1);
            require(saveActor(magic,world.nowMs())==before,
                    "No-reaction attack leaves a living target's existing reaction and motion intact");
        }
        checkpoint = "40JP flight weight conversion and saved randomness";
        {
            World world(pvf,assets);
            feedbackFloor(world);
            Actor target;target.id=1;target.x=560;target.y=344;
            AttackResponse response;response.knockDown=true;response.push=300;response.lift=500;
            const auto initial=world.random_.snapshot();
            auto predicted=world.random_;
            auto &rng=predicted.stream(RandomDomain::HitReaction,0);
            const double denominator=(45000-10000)*double(.0121f)+double(2100.f);
            const int push=int(4000*response.push/denominator)/2;
            const int lift=int(4000*response.lift/denominator);
            const int height=int(double(lift)*lift/3000);
            const auto sample=[&](int low,int high){return low+int(int64_t(high-low)*rng.bounded(1000)/999);};
            const int expectedPush=sample(int(push*.8),int(push*1.2));
            const int expectedHeight=sample(int(height*.9),int(height*1.1));
            world.applyResponse(target,response,1);
            require(target.hitReaction.state==4&&target.hitReaction.substate==0&&target.recovery==1&&
                    target.hitReaction.gravity==-1500&&target.hitReaction.pushSpeed==expectedPush&&
                    target.hitReaction.launchHeight==expectedHeight&&target.vx==expectedPush&&target.vy==0&&
                    std::abs(target.vz-std::sqrt(3000.0*expectedHeight))<1e-9&&target.dir==-1,
                    "Flight converts ATK push/lift by weight, halves integer push and derives launch from randomized height under gravity -1500");
            require(world.random_.snapshot()==predicted.snapshot(),
                    "Flight consumes exactly its two saved HitReaction-domain draws");
            World mirrored(pvf,assets);feedbackFloor(mirrored);
            // Reset both banks to the same pre-contact state for a mirrored
            // comparison; this is fixture setup, never a production reseed.
            world.random_.restore(initial);mirrored.random_.restore(initial);
            Actor positive;positive.x=560;positive.y=344;
            Actor negative=positive;
            world.applyResponse(positive,response,1);
            response.push=-response.push;
            mirrored.applyResponse(negative,response,1);
            require(positive.vx==-negative.vx&&positive.vz==negative.vz&&positive.dir==-negative.dir&&
                    positive.hitReaction.direction==-negative.hitReaction.direction,
                    "Signed ATK push mirrors direction after integer conversion without changing launch height");
            // Negative height is gated out by native sub_4A0550(h*a<=0).
            response.lift=-500;negative.vz=123;
            mirrored.applyResponse(negative,response,1);
            require(negative.hitReaction.launchHeight<0&&negative.vz==123,
                    "Negative lift preserves existing vertical speed under the recovered native launch gate");
            report["reaction_flight"]={{"weight",45000},{"denominator",denominator},
                {"converted_push_before_random",push},{"converted_lift",lift},
                {"height_before_random",height},{"expected_push",expectedPush},{"expected_height",expectedHeight}};
        }
        checkpoint = "40JP reaction integration partition";
        {
            World world(pvf,assets);feedbackFloor(world);
            Actor whole;whole.x=560;whole.y=344;
            Actor split=whole;
            AttackResponse response;response.hitDelayRate=1;
            world.applyResponse(whole,response,1);world.applyResponse(split,response,1);
            world.advanceMonsterHitReaction(whole,150);
            for(int step=0;step<15;++step)world.advanceMonsterHitReaction(split,10);
            require(std::abs(whole.x-split.x)<.001&&whole.y==split.y&&whole.vx==0&&split.vx==0&&
                    whole.hitReaction.remainingMs==split.hitReaction.remainingMs,
                    "Splitting a standing slide across ticks preserves its stop position, duration and final velocity");
            whole.x=1199;whole.y=344;whole.vx=400;whole.hitReaction.state=4;
            whole.hitReaction.substate=1;whole.hitReaction.accelerationX=0;
            whole.hitReaction.accelerationRemainingMs=0;whole.z=100;whole.vz=100;
            world.advanceMonsterHitReaction(whole,16);
            require(whole.x<1200&&whole.vx==0,
                    "Reaction movement checks intermediate map pixels and stops at a source walk boundary");
        }
        checkpoint = "40JP reaction save continuation and validation";
        {
            World world(pvf,assets);feedbackFloor(world);
            Actor target;target.id=1;target.x=560;target.y=344;
            AttackResponse response;response.knockDown=true;response.push=300;response.lift=500;
            world.applyResponse(target,response,1);world.advanceMonsterHitReaction(target,80);
            const auto saved=saveActor(target,world.nowMs());
            auto loaded=loadActor(saved,world.nowMs()+9000);
            World restored(pvf,assets);feedbackFloor(restored);
            restored.random_.restore(world.random_.snapshot());
            const auto rngBefore=restored.random_.snapshot();
            world.advanceMonsterHitReaction(target,80);restored.advanceMonsterHitReaction(loaded,80);
            require(std::abs(target.x-loaded.x)<1e-9&&std::abs(target.z-loaded.z)<1e-9&&
                    target.vx==loaded.vx&&target.vz==loaded.vz&&
                    saveActor(target,world.nowMs()).at("hit_reaction")==saveActor(loaded,restored.nowMs()).at("hit_reaction")&&
                    restored.random_.snapshot()==rngBefore,
                    "Saving a flight stores coefficients and timers so restore continues without redrawing impulse randomness");
            const auto rejected=[&](const char *key,Json bad){
                auto invalid=saved;invalid["hit_reaction"][key]=std::move(bad);
                try{loadActor(invalid,0);}catch(const std::exception&){return true;}return false;
            };
            require(rejected("substate",2)&&rejected("remaining_ms",-1)&&
                    rejected("gravity",uint64_t(1))&&rejected("direction",0)&&
                    rejected("peak_height",std::numeric_limits<double>::infinity()),
                    "Reaction restore rejects invalid substate, negative time, positive unsigned gravity, zero direction and nonfinite height");
            auto legacy=saved;legacy.erase("hit_reaction");
            require(loadActor(legacy,0).hitReaction.state==0,
                    "Legacy actor checkpoints without reaction coefficients remain loadable");
        }
        checkpoint = "40JP floor bounce and reaction ownership";
        {
            World world(pvf,assets);feedbackFloor(world);
            Actor target;target.id=1;target.x=560;target.y=344;target.z=.1;target.vz=-200;target.vx=200;
            target.monsterPath="monster/goblin/goblin.mob";
            target.hitReaction.state=4;target.hitReaction.direction=1;
            target.hitReaction.peakHeight=100;target.hitReaction.pushSpeed=200;target.recovery=1;
            auto predicted=world.random_;
            auto &rng=predicted.stream(RandomDomain::HitReaction,0);
            const int expectedPush=80+int(40*rng.bounded(1000)/999);
            const int expectedHeight=18+int(4*rng.bounded(1000)/999);
            world.advanceMonsterHitReaction(target,16);
            require(target.hitReaction.state==4&&target.hitReaction.substate==1&&
                    target.hitReaction.launchHeight==expectedHeight&&target.vx==expectedPush&&target.vx>0&&target.vz>0&&
                    world.random_.snapshot()==predicted.snapshot(),
                    "First floor bounce retains direction, halves push, uses peak/5 height and performs two shared random interpolations");
            target.z=.1;target.vz=-200;
            world.advanceMonsterHitReaction(target,16);
            require(target.hitReaction.state==0&&target.recovery==2&&target.animation=="down"&&
                    target.z==0&&target.vx==0&&target.vz==0,
                    "Final landing releases reaction ownership into existing source down/get-up animation lifecycle");
            AttackResponse response;
            target.recovery=0;
            response.knockDown=true;response.lift=500;
            world.applyResponse(target,response,1);world.applyMonsterHurtMotion(target,response);
            require(target.hitReaction.state==4&&target.animation=="down"&&!target.animationPath.empty(),
                    "Flying reaction binds current MOB down motion rather than replaying a standing damage pose");
            target.hitReaction.state=4;target.vx=20;target.vy=10;target.vz=30;target.capturedBy=1;
            world.applyResponse(target,response,1);
            require(target.hitReaction.state==0&&target.vx==0&&target.vy==0&&target.vz==0,
                    "Capture owns position and clears latent reaction impulse before another hit can relaunch the captive");
            target.capturedBy=-1;target.dead=true;target.hitReaction.state=3;target.vx=20;
            world.advanceMonsterHitReaction(target,16);
            require(target.hitReaction.state==0&&target.vx==0,
                    "Dead actors cannot retain an active living reaction controller");
        }
        checkpoint = "source weapon feedback";
        const auto chr = pvf.script("character/swordman/swordman.chr");
        const auto weaponInfo = chr.values("[weapon hit info]");
        // CHR order is short sword, katana, club, heavy sword, light sword,
        // gauntlet. The playable selector's four entries have a different order.
        const std::array<int, 4> sourceRows{0, 1, 3, 2};
        const std::array<int, 4> knownSourcePause{90, 70, 120, 100};
        require(weaponInfo.size() >= 24, "current CHR retains complete first four weapon feedback records");
        report["source"] = {{"path", chr.path}, {"tag", "[weapon hit info]"}, {"raw", weaponInfo},
            {"duration_units", "milliseconds interpreted by reconstruction; native allocation remains unproved"}};
        for (int weapon = 0; weapon < 4; ++weapon) {
            const int pauseMs = weaponInfo.at(sourceRows[weapon] * 6 + 2).get<int>();
            require(pauseMs == knownSourcePause[weapon], "current source weapon " + std::to_string(weapon) + " pause record is the expected 1031 value");
            for (int direction : {-1, 1}) {
                checkpoint = "weapon " + std::to_string(weapon) + " facing " + std::to_string(direction);
                World world(pvf, assets);
                feedbackFloor(world, direction);
                world.weapon = weapon;
                feedbackTarget(world);
                feedbackPress(world, 4);
                std::array<int, 3> hits{}, pauses{}, targetPauses{};
                Json contacts = Json::array();
                size_t cursor = 0;
                int frozenPlayerTicks = 0, frozenTargetTicks = 0;
                bool frozenPlayer = true, frozenTarget = true, finished = false;
                for (int frame = 0; frame < 360; ++frame) {
                    const auto beforePlayer = feedbackPose(world.player, world.nowMs());
                    const auto beforeTarget = feedbackPose(world.monsters.front(), world.nowMs());
                    const bool playerWasPaused = world.player.hitStopTicks > 0;
                    const bool targetWasPaused = world.monsters.front().hitStopTicks > 0;
                    feedbackStep(world);
                    if (playerWasPaused && world.player.hitStopped) {
                        ++frozenPlayerTicks;
                        frozenPlayer &= feedbackPose(world.player, world.nowMs()) == beforePlayer;
                    }
                    if (targetWasPaused && world.monsters.front().hitStopped) {
                        ++frozenTargetTicks;
                        frozenTarget &= feedbackPose(world.monsters.front(), world.nowMs()) == beforeTarget;
                    }
                    while (cursor < world.events.size()) {
                        const auto event = world.events[cursor++];
                        if (event.kind != "hit" || event.target != 1) continue;
                        int swing = -1;
                        for (int n = 0; n < 3; ++n)
                            if (event.name == "attack" + std::to_string(n + 1)) swing = n;
                        if (swing < 0) continue;
                        ++hits[swing];
                        pauses[swing] = world.player.hitStopTicks;
                        targetPauses[swing] = world.monsters.front().hitStopTicks;
                        contacts.push_back({{"swing", swing + 1}, {"tick", event.tick},
                            {"owner_pause_ticks", pauses[swing]}, {"target_pause_ticks", targetPauses[swing]},
                            {"damage", event.value}});
                        // Press the next X during the actual contact pause,
                        // rather than guessing a wall-clock combo deadline.
                        if (swing < 2 && hits[swing] == 1) feedbackPress(world, 4);
                    }
                    if (hits[2] && world.player.animation == "stay" && !world.player.hitStopTicks) {
                        finished = true;
                        break;
                    }
                }
                report["weapon_combos"].push_back({{"weapon", weapon}, {"direction", direction},
                    {"source_pause_ms", pauseMs}, {"hit_counts", hits}, {"contacts", contacts},
                    {"frozen_player_ticks", frozenPlayerTicks}, {"frozen_target_ticks", frozenTargetTicks},
                    {"player_pose_frozen", frozenPlayer}, {"target_pose_frozen", frozenTarget}, {"finished", finished}});
                const std::string label = "weapon " + std::to_string(weapon) + ", facing " + std::to_string(direction) + ": ";
                require(hits == std::array<int, 3>{1, 1, 1}, label + "three queued swings each damage once across stopped source frames and weapon layers");
                require(finished, label + "X pressed during contact pause advances all three swings and releases actor");
                require(frozenPlayer && frozenTarget && frozenPlayerTicks > 0 && frozenTargetTicks > 0,
                    label + "contact freezes both actors' actual pose clocks and XYZ positions");
                bool inherited = true;
                for (int n = 0; n < 3; ++n)
                    inherited &= pauses[n] > 0 && std::abs(pauses[n] * 1000.0 / 60 - pauseMs) <= 17.01 && targetPauses[n] > 0;
                require(inherited, label + "all three ordinary swings inherit source weapon pause within one simulation tick");
                require(targetPauses[0] == pauses[0], label + "40JP pause consumes hit-info milliseconds independently of reaction rate for both actors");
            }
        }
        checkpoint = "empty swing and attack direction";
        for (int direction : {-1, 1}) {
            World world(pvf, assets);
            feedbackFloor(world, direction);
            feedbackPress(world, 4);
            for (int frame = 0; frame < 5; ++frame) feedbackStep(world);
            require(world.player.animation == "attack1", "direction test reaches ordinary attack before completion");
            const double x = world.player.x;
            const int oppositeKey = direction > 0 ? 0 : 1;
            const auto when = world.tick * 1000000000ll / 60;
            world.enqueue({when, oppositeKey, true});
            feedbackPress(world, 5);
            feedbackStep(world);
            require(world.player.dir == direction && world.player.animation == "attack1" &&
                    world.player.z == 0 && world.player.x == x,
                    "half-finished ordinary attack keeps facing and cannot be cancelled by direction plus C");
            bool stopped = world.player.hitStopTicks > 0 || world.player.hitStopped;
            for (int frame = 0; frame < 120; ++frame) {
                feedbackStep(world);
                stopped |= world.player.hitStopTicks > 0 || world.player.hitStopped;
            }
            require(!stopped && feedbackHits(world) == 0, "an empty swing never causes contact pause");
            require(world.player.dir == -direction && (world.player.x - x) * -direction > 40 && world.player.z == 0,
                    "held direction turns and moves after the ordinary attack ends");
        }
        checkpoint = "held direction at ordinary continuation boundary";
        report["continuation_direction"] = Json::array();
        for (int direction : {-1, 1}) {
            World world(pvf, assets);
            feedbackFloor(world, direction);
            feedbackPress(world, 4);
            for (int frame = 0; frame < 5; ++frame) feedbackStep(world);
            require(world.player.animation == "attack1", "continuation direction fixture begins inside first ordinary swing");
            const auto when = world.tick * 1000000000ll / 60;
            world.enqueue({when, direction > 0 ? 0 : 1, true});
            feedbackPress(world, 4);
            bool firstLocked = true, secondObserved = false;
            int64_t boundary = -1;
            for (int frame = 0; frame < 180; ++frame) {
                feedbackStep(world);
                if (world.player.animation == "attack1") firstLocked &= world.player.dir == direction;
                if (world.player.animation == "attack2") {
                    secondObserved = true;
                    boundary = world.tick;
                    break;
                }
            }
            report["continuation_direction"].push_back({{"initial_direction", direction},
                {"first_swing_locked", firstLocked}, {"second_swing_observed", secondObserved},
                {"second_swing_direction", world.player.dir}, {"boundary_tick", boundary}});
            require(firstLocked && secondObserved && world.player.dir == -direction && world.player.poseFrame == 0,
                    "held opposite direction leaves first swing unchanged and starts queued attack2 facing back at its first pose");
        }
        checkpoint = "triple slash facing and attachments during pause";
        report["triple_slash_pause"] = Json::array();
        for (int direction : {-1, 1}) {
            World world(pvf, assets);
            feedbackFloor(world, direction);
            feedbackTarget(world);
            feedbackPress(world, 22); // Default binding 2: Triple Slash.
            require(feedbackAwaitHit(world) && world.activeSkill() == 2 && world.player.hitStopTicks > 0,
                    "ordinary bound Triple Slash reaches a genuine melee contact pause");
            const auto pose = feedbackPose(world.player, world.nowMs());
            const auto attached = feedbackAttachments(world);
            require(!attached.empty(), "Triple Slash contact has attached slash and motion source layers");
            const auto when = world.tick * 1000000000ll / 60;
            world.enqueue({when, direction > 0 ? 0 : 1, true});
            int paused = 0;
            bool frozen = true;
            while (world.player.hitStopTicks > 0 && paused < 60) {
                feedbackStep(world);
                if (!world.player.hitStopped) break;
                ++paused;
                frozen &= world.player.dir == direction && feedbackPose(world.player, world.nowMs()) == pose &&
                          feedbackAttachments(world) == attached;
            }
            report["triple_slash_pause"].push_back({{"direction", direction}, {"paused_ticks", paused},
                {"facing_pose_and_attachments_frozen", frozen}, {"attached_layers", attached.size()}});
            require(paused > 0 && frozen,
                    "opposite direction during Triple Slash pause cannot flip actor or attached anchors, phases and lifetimes");
            feedbackStep(world);
            const bool turnedAfterPause = !world.player.hitStopped && world.activeSkill() == 2 &&
                                          world.player.dir == -direction;
            bool anchorsFollow = true, phaseResumed = false;
            int activeAttachments = 0;
            for (const auto &effect : world.effects) if (effect.attached) {
                ++activeAttachments;
                anchorsFollow &= effect.dir == -direction &&
                    effect.x == world.player.x + world.player.dir * effect.offsetX &&
                    effect.y == world.player.y + effect.offsetY && effect.z == world.player.z;
                for (const auto &saved : attached) if (saved.at("id").get<int>() == effect.id)
                    phaseResumed |= world.nowMs() - effect.born + effect.animationOffset >
                                    saved.at("animation_ms").get<int64_t>();
            }
            report["triple_slash_pause"].back()["turned_on_first_released_tick"] = turnedAfterPause;
            report["triple_slash_pause"].back()["released_attachments_follow_facing"] = anchorsFollow;
            report["triple_slash_pause"].back()["attachment_phase_resumed"] = phaseResumed;
            require(turnedAfterPause && activeAttachments > 0 && anchorsFollow && phaseResumed,
                    "held opposite direction turns Triple Slash on the first released tick and its resumed attachments follow the new facing");
        }
        checkpoint = "ordinary contact hotkey buffer";
        {
            World world(pvf, assets);
            feedbackFloor(world);
            feedbackTarget(world);
            feedbackPress(world, 4);
            require(feedbackAwaitHit(world) && world.player.animation == "attack1" && world.player.hitStopTicks > 0,
                    "hotkey-buffer fixture begins during an ordinary melee contact pause");
            const auto pressedAt = world.nowMs();
            const auto pose = feedbackPose(world.player, world.nowMs());
            const int mp = world.player.mp;
            const auto expectedCosts = world.skillCosts(1);
            require(expectedCosts.consumeMp().has_value() && expectedCosts.cooldownMs().has_value(),
                    "hotkey-buffer fixture has source-calculated MP and cooldown costs");
            const int cost = *expectedCosts.consumeMp();
            const int cooldownMs = int(std::ceil(*expectedCosts.cooldownMs()));
            feedbackPress(world, 21); // The existing ordinary-attack -> Ghost Slash permission.
            bool heldDuringPause = true;
            int paused = 0;
            while (world.player.hitStopTicks > 0 && paused < 60) {
                feedbackStep(world);
                if (!world.player.hitStopped) break;
                ++paused;
                heldDuringPause &= world.activeSkill() < 0 && world.player.mp == mp &&
                                   feedbackPose(world.player, world.nowMs()) == pose;
            }
            require(paused > 0 && heldDuringPause,
                    "skill hotkey received during ordinary contact pause neither replaces the pose nor spends MP early");
            feedbackStep(world);
            const auto activatedAt = world.nowMs();
            require(!world.player.hitStopped && world.activeSkill() == 1 && world.player.animation == "hardattack" &&
                    world.player.mp == mp - cost && world.remainingCd(1) > 0 && activatedAt - pressedAt <= 200,
                    "buffered Ghost Slash starts on the first released tick and charges one source-calculated MP cost within the 200ms reconstruction window");
            // Observe beyond the real skill cooldown as well as its animation:
            // one buffered press must not silently recast after cooldown expiry.
            const int observeMs = std::max(cooldownMs,
                assets.animation("character/swordman/animation/hardattack.ani")->duration) + 300;
            for (int frame = 0; frame < (observeMs * 60 + 999) / 1000; ++frame) feedbackStep(world);
            int starts = 0;
            for (const auto &event : world.events)
                if (event.kind == "stage" && event.name == "hardattack:0") ++starts;
            report["hotkey_buffer"] = {{"pressed_at_ms", pressedAt}, {"activated_at_ms", activatedAt},
                {"paused_ticks", paused}, {"mp_before", mp}, {"skill_mp_cost", cost},
                {"skill_cooldown_ms", cooldownMs}, {"expected_skill_costs", expectedCosts.json()},
                {"mp_after", world.player.mp}, {"skill_starts", starts}, {"observation_ms", observeMs}};
            require(starts == 1 && world.player.mp == mp - cost && world.activeSkill() < 0,
                    "one paused hotkey is consumed once, without repeated casts after cooldown expiry");
        }
        checkpoint = "buffer does not grant new skill cancellation";
        {
            World world(pvf, assets);
            feedbackFloor(world);
            feedbackTarget(world);
            feedbackPress(world, 21);
            require(feedbackAwaitHit(world) && world.activeSkill() == 1 && world.player.hitStopTicks > 0,
                    "cancel-permission fixture starts during active Ghost Slash contact pause");
            const int mp = world.player.mp;
            feedbackPress(world, 22); // Triple Slash cannot cancel this active skill.
            bool interrupted = false;
            for (int frame = 0; frame < 360; ++frame) {
                feedbackStep(world);
                interrupted |= world.activeSkill() == 2;
            }
            for (const auto &event : world.events)
                if (event.kind == "stage" && event.name.rfind("tripleslash:", 0) == 0) interrupted = true;
            require(!interrupted && world.player.mp == mp && world.activeSkill() < 0,
                    "contact hotkey buffer does not grant an unrelated active skill a new cancellation permission or delayed cast");
        }
        checkpoint = "local skill and attached clocks";
        {
            World world(pvf, assets);
            feedbackFloor(world);
            feedbackTarget(world);
            feedbackPress(world, 21); // Default binding 1: Ghost Slash.
            require(feedbackAwaitHit(world), "ordinary bound Ghost Slash makes an accepted source-box hit");
            require(world.activeSkill() == 1 && world.player.hitStopTicks > 0 && world.remainingCd(1) > 0,
                    "melee skill contact pauses owner with cooldown already running");
            const auto started = world.nowMs();
            const int cooldown = world.remainingCd(1);
            const auto pose = feedbackPose(world.player, world.nowMs());
            struct AttachmentClock { int id; int64_t age, remaining; double x, y, z; };
            std::vector<AttachmentClock> attached;
            for (const auto &effect : world.effects) if (effect.attached)
                attached.push_back({effect.id, world.nowMs() - effect.born + effect.animationOffset,
                    effect.expires - world.nowMs(), effect.x, effect.y, effect.z});
            require(!attached.empty(), "Ghost Slash contact retains real attached source ANI layers");
            bool attachmentsFrozen = true;
            int pausedTicks = 0;
            while (world.player.hitStopTicks > 0 && pausedTicks < 60) {
                feedbackStep(world);
                if (!world.player.hitStopped) break;
                ++pausedTicks;
                require(feedbackPose(world.player, world.nowMs()) == pose,
                        "skill owner pose remains frozen during local contact pause");
                for (const auto &saved : attached) {
                    bool found = false;
                    for (const auto &effect : world.effects) if (effect.id == saved.id) {
                        found = true;
                        attachmentsFrozen &= world.nowMs() - effect.born + effect.animationOffset == saved.age &&
                            effect.expires - world.nowMs() == saved.remaining &&
                            effect.x == saved.x && effect.y == saved.y && effect.z == saved.z;
                    }
                    attachmentsFrozen &= found;
                }
            }
            report["skill_clock"] = {{"paused_ticks", pausedTicks}, {"world_elapsed_ms", world.nowMs() - started},
                {"cooldown_before_ms", cooldown}, {"cooldown_after_ms", world.remainingCd(1)},
                {"attached_layers", attached.size()}, {"attachments_frozen", attachmentsFrozen}};
            require(pausedTicks > 0 && attachmentsFrozen, "attached effect lifetime and animation phase share owner-local pause");
            require(world.nowMs() > started && cooldown - world.remainingCd(1) == world.nowMs() - started,
                    "world clock and cooldown continue while actor and attached layers stop");
        }
        checkpoint = "Hop Smash normal and final contacts under pause";
        report["hop_smash_contacts"] = Json::array();
        for (int weapon = 0; weapon < 4; ++weapon) for (int direction : {-1, 1}) {
            World world(pvf, assets);
            feedbackFloor(world, direction);
            world.weapon = weapon;
            const auto source = pvf.script(world.skills[10].source);
            const auto staticData = source.values("[static data]");
            // Match the ordinary three-target effect fixture. Placement is
            // initial setup only: all push, lift and subsequent separation are
            // left to actual authored contacts and the live controller.
            for (int target = 0; target < 3; ++target) {
                feedbackTarget(world, target + 1);
                auto &actor = world.monsters.back();
                actor.x = actor.px = world.player.x + direction * (90 + target * 80);
            }
            world.enqueue({0, 30, true});
            world.enqueue({220000000, 30, false});
            bool advancedWave = false;
            for (int frame = 0; frame < 360; ++frame) {
                feedbackStep(world);
                for (const auto &effect : world.effects)
                    advancedWave |= effect.phase == "hopsmash:impact" ||
                        effect.animation.find("hopsmashsub") != std::string::npos;
                if (world.activeSkill() < 0 && world.player.hitStopTicks == 0 && frame > 30) break;
            }
            std::array<int, 3> normal{}, final{}, total{};
            Json contacts = Json::array();
            for (const auto &event : world.events) {
                if (event.target < 1 || event.target > 3) continue;
                const int target = event.target - 1;
                if (event.kind == "hit") ++total[target];
                if (event.kind != "hit_feedback") continue;
                if (event.name == "character/swordman/attackinfo/hopsmash.atk") ++normal[target];
                if (event.name == "character/swordman/attackinfo/hopsmashfinal.atk") ++final[target];
                advancedWave |= event.name.find("hopsmashsub.atk") != std::string::npos;
                contacts.push_back({{"tick", event.tick}, {"target", event.target}, {"source", event.name}});
            }
            report["hop_smash_contacts"].push_back({{"weapon", weapon}, {"direction", direction},
                {"held_ms", 220}, {"source", source.path}, {"source_static_data", staticData},
                {"normal_hits", normal}, {"final_hits", final}, {"total_hits", total},
                {"advanced_wave", advancedWave}, {"contacts", contacts}, {"finished", world.activeSkill() < 0}});
            const std::string label = "Hop Smash weapon " + std::to_string(weapon) + ", facing " + std::to_string(direction) + ": ";
            require(normal[0] + normal[1] + normal[2] > 0 && final[0] + final[1] + final[2] > 0,
                    label + "normal source contacts do not consume the later authored final slash under hit pause");
            require(!advancedWave && world.bloodVigorousLevel == 0,
                    label + "base character has no unqualified hopsmashsub attack or shockwave");
            bool bounded = true;
            for (int target = 0; target < 3; ++target)
                bounded &= total[target] <= 3 && final[target] <= 1 &&
                           normal[target] + final[target] == total[target];
            require(bounded && world.activeSkill() < 0,
                    label + "each target receives at most three authored contacts and one final slash before actor release");
        }
        checkpoint = "group contact duration";
        {
            std::array<int, 2> ownerPauses{}, frozenTicks{};
            for (int group = 0; group < 2; ++group) {
                World world(pvf, assets);
                feedbackFloor(world);
                for (int id = 1; id <= (group ? 3 : 1); ++id) feedbackTarget(world, id);
                feedbackPress(world, 4);
                require(feedbackAwaitHit(world), "group-contact fixture makes actual ordinary melee contact");
                ownerPauses[group] = world.player.hitStopTicks;
                int accepted = 0;
                for (int id = 1; id <= (group ? 3 : 1); ++id) accepted += feedbackHits(world, id);
                require(accepted == (group ? 3 : 1), "coincident living targets accept one hit each in the same swing tick");
                while (world.player.hitStopTicks > 0 && frozenTicks[group] < 60) {
                    feedbackStep(world);
                    if (world.player.hitStopped) ++frozenTicks[group];
                }
            }
            report["group_contact"] = {{"one_target_pause_ticks", ownerPauses[0]}, {"three_target_pause_ticks", ownerPauses[1]},
                {"one_target_frozen_ticks", frozenTicks[0]}, {"three_target_frozen_ticks", frozenTicks[1]}};
            require(ownerPauses[0] > 0 && ownerPauses[0] == ownerPauses[1] && frozenTicks[0] == frozenTicks[1],
                    "same-tick group contact does not multiply owner pause by target count");
        }
        checkpoint = "independent projectile owner";
        {
            World world(pvf, assets);
            feedbackFloor(world);
            feedbackTarget(world);
            world.player.x = world.player.px = 300;
            world.monsters.front().x = world.monsters.front().px = 705;
            Effect wave;
            wave.skill = 20;
            wave.animation = "passiveobject/character/swordman/animation/normalwavefire.ani";
            wave.x = wave.px = 500;
            wave.y = wave.py = world.player.y;
            wave.expires = 325;
            wave.interval = 100000;
            world.effects.push_back(wave);
            require(feedbackAwaitHit(world, 10), "independent source Fire projectile hits by authored reach");
            require(world.player.hitStopTicks == 0 && !world.player.hitStopped && world.monsters.front().hitStopTicks > 0,
                    "independent projectile pauses target without freezing distant owner");
            const double x = world.player.x;
            const auto when = world.tick * 1000000000ll / 60;
            world.enqueue({when, 1, true});
            for (int frame = 0; frame < 3; ++frame) feedbackStep(world);
            require(world.player.x > x && !world.player.hitStopped,
                    "projectile owner can immediately move during target-only pause");
        }
        checkpoint = "diagnostic ownership and pause persistence";
        {
            World world(pvf, assets);
            feedbackFloor(world);
            feedbackTarget(world);
            // Use a registered current-source response. Legacy diagnostic IDs
            // 0/1 have no AttackInfo binding and therefore author no hit pause.
            world.diagnosticHit(1, 1, 46, 0, 1, {world.player.x, world.player.y, 200});
            require(world.player.hitStopTicks == 0 && world.monsters.front().hitStopTicks > 0,
                    "accepted-hit diagnostic fixture has no implicit melee owner freeze");
            feedbackStep(world);
            const auto saved = saveActor(world.monsters.front(), world.nowMs());
            World restored(pvf, assets);
            feedbackFloor(restored);
            restored.tick = 900;
            restored.monsters.push_back(loadActor(saved, restored.nowMs()));
            require(restored.monsters.front().hitStopTicks == world.monsters.front().hitStopTicks &&
                    restored.monsters.front().hitStopTicks > 0,
                    "actor save/load preserves remaining contact ticks across a different world clock");
            const auto pose = feedbackPose(restored.monsters.front(), restored.nowMs());
            const int remaining = restored.monsters.front().hitStopTicks;
            for (int frame = 0; frame < remaining; ++frame) feedbackStep(restored);
            require(restored.monsters.front().hitStopTicks == 0 && feedbackPose(restored.monsters.front(), restored.nowMs()) == pose,
                    "restored target consumes only its remaining pause while preserving the saved pose");
            feedbackStep(restored);
            require(!restored.monsters.front().hitStopped && restored.nowMs() - restored.monsters.front().animStart > pose["animation_ms"].get<int64_t>(),
                    "restored target animation resumes on the tick after saved pause expires");
            auto legacy = saved;
            legacy.erase("hit_stop_ticks");
            require(loadActor(legacy, restored.nowMs()).hitStopTicks == 0,
                    "legacy actor saves without contact ticks load unpaused");
            require(feedbackHits(restored) == 0, "restoring contact pause does not replay damage events");
            report["save_pause"] = {{"original_world_ms", world.nowMs()}, {"restored_world_ms", 15000},
                {"remaining_ticks", remaining}, {"saved", saved}};
        }
        checkpoint = "scene transition and lethal contact";
        {
            World world(pvf, assets);
            feedbackFloor(world);
            feedbackTarget(world);
            feedbackPress(world, 4);
            require(feedbackAwaitHit(world) && world.player.hitStopTicks > 0 && world.monsters.front().hitStopTicks > 0,
                    "scene-transition fixture begins during a real two-actor contact pause");
            world.changeScene();
            require(world.player.hitStopTicks == 0 && !world.player.hitStopped &&
                    world.monsters.front().hitStopTicks == 0 && !world.monsters.front().hitStopped,
                    "scene change clears transient pause for both owner and current targets");
            World lethal(pvf, assets);
            feedbackFloor(lethal);
            feedbackTarget(lethal, 1, 1);
            feedbackPress(lethal, 4);
            require(feedbackAwaitHit(lethal), "lethal ordinary contact reaches original monster hurtbox");
            const auto response=readAttackResponse(pvf.script("character/swordman/attackinfo/attack1.atk"));
            const auto soundCount=std::count_if(lethal.events.begin(),lethal.events.end(),[&](const Event &event){
                return event.kind=="sound" && event.name==response.sound && event.target==1;
            });
            require(response.sound.empty() || soundCount==1,
                    "Accepted lethal contact publishes its authored ATK hit sound once through common feedback");
            require(lethal.monsters.front().dead && lethal.monsters.front().hitStopTicks == 0 && lethal.player.hitStopTicks > 0,
                    "lethal contact keeps owner feedback without freezing the monster death sequence");
            World followup(pvf, assets);
            feedbackFloor(followup);
            feedbackTarget(followup);
            followup.diagnosticHit(1, 1, 46, 0, 1, {followup.player.x, followup.player.y, 200});
            require(followup.monsters.front().hitStopTicks > 0 && followup.monsters.front().hitStopped,
                    "lethal-followup fixture starts with an already-paused live target");
            followup.diagnosticHit(1, 100000, 46, 0, 1, {followup.player.x, followup.player.y, 200});
            require(followup.monsters.front().dead && followup.monsters.front().hitStopTicks == 0 &&
                    !followup.monsters.front().hitStopped &&
                    saveActor(followup.monsters.front(), followup.nowMs()).at("hit_stop_ticks").get<int>() == 0,
                    "additional lethal contact immediately clears an existing target pause before any later tick or save");
        }
        report["status"] = "pass";
        writeJson("reports/combat-feel/tests.json", report);
        return report;
    } catch (const std::exception &error) {
        report["status"] = "fail";
        report["checkpoint"] = checkpoint;
        report["error"] = error.what();
        writeJson("reports/combat-feel/tests.json", report);
        throw;
    }
}
} // namespace dnf
