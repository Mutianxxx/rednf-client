#include "dnf/monster_effects.hpp"
#include "dnf/monster_equipment.hpp"
#include "dnf/combat.hpp"
#include "dnf/geometry.hpp"
#include <cmath>
#include <cstdio>
#include <map>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
std::string canonical(std::string path) {
    return normalize(std::filesystem::u8path(normalize(std::move(path))).lexically_normal().generic_u8string());
}
bool resource(const Json &value) {
    if (!value.is_string()) return false;
    const auto path = normalize(value.get<std::string>());
    return path.size() > 4 && (path.substr(path.size() - 4) == ".ani" || path.substr(path.size() - 4) == ".act");
}
std::string reference(Pvf &pvf, const std::string &source, const std::string &child) {
    const auto parent = std::filesystem::u8path(source).parent_path();
    std::set<std::string> existing;
    for (auto candidate : {canonical((parent / std::filesystem::u8path(child)).generic_u8string()),
                           canonical(child), canonical("monster/" + child)})
        if (pvf.has(candidate)) existing.insert(candidate);
    if (existing.size() != 1)
        throw std::runtime_error((existing.empty() ? "Missing reference: " : "Ambiguous reference: ") + source + " -> " + child);
    return *existing.begin();
}
double boundary(const Animation &animation, int frame) {
    if (frame < 0 || frame >= int(animation.frames.size()))
        throw std::runtime_error("Frame outside parent ANI: " + animation.path);
    double time = 0;
    for (int i = 0; i < frame; ++i) time += animation.frames[i].duration;
    return time;
}
std::vector<std::string> stateTags(const std::string &state) {
    if (state == "stay" || state == "idle") return {"[waiting motion]", "[waiting action]", "[basic action]"};
    if (state == "damage1") return {"[damage motion 1]", "[damage action 1]"};
    if (state == "damage2") return {"[damage motion 2]", "[damage action 2]"};
    if (state == "down") return {"[down motion]", "[down action]"};
    if (state == "sit") return {"[sit motion]", "[sit action]"};
    if (state == "overturn") return {"[overturn motion]", "[overturn action]"};
    if (state == "move") return {"[move motion]", "[move action]"};
    if (state == "attack1") return {"[attack motion]", "[attack action]"};
    if (state == "death") return {"[last action]"};
    return {normalize(state)};
}
void addTrack(Pvf &pvf, Assets &assets, MonsterMotion &motion, const std::string &path,
              double start, int layer, double x, double y, bool hold, double limit,
              std::set<std::string> stack = {}, int depth = 0,
              std::vector<std::pair<int, size_t>> drawOrder = {}) {
    if (depth > 12 || stack.count(path)) throw std::runtime_error("Recursive ANI/ALS: " + path);
    if (motion.tracks.size() >= 256) throw std::runtime_error("Monster animation instance limit exceeded");
    stack.insert(path);
    auto animation = assets.animation(path);
    if (animation->frames.empty()) throw std::runtime_error("Empty ANI: " + path);
    const auto sourceLoop = animation->globals.find("0");
    const bool loop = !hold && sourceLoop != animation->globals.end() && sourceLoop->get<bool>();
    // Animation completion freezes a child on its last frame (40JP
    // sub_493840); only the attachment's remove/owner boundary removes it.
    const double end = !hold ? limit : std::min(limit, start + std::max(1, animation->duration));
    motion.tracks.push_back({animation, start, end, x, y, layer, hold,
                             depth ? "als" : hold ? "base" : "sub", loop, drawOrder});
    if (!pvf.has(path + ".als")) return;
    const auto script = pvf.script(path + ".als");
    std::map<std::string, std::string> declarations;
    struct Event { int frame, layer; std::string name; bool add; size_t offset; };
    std::vector<Event> events;
    for (const auto &field : script.fields) {
        const auto tag = normalize(field.tag);
        const auto &v = field.values;
        motion.references.push_back({{"source", script.path}, {"offset", field.offset},
                                     {"tag", field.tag}, {"values", v}});
        if (tag == "[use animation]" && v.size() == 2 && v[0].is_string() && v[1].is_string())
            declarations[v[1].get<std::string>()] = reference(pvf, path, v[0].get<std::string>());
        else if ((tag == "[add]" || tag == "[remove]") && v.size() == 3 &&
                 v[0].is_number_integer() && v[1].is_number_integer() && v[2].is_string())
            events.push_back({v[0], v[1], v[2], tag == "[add]", field.offset});
        else motion.issues.push_back({{"resource", script.path}, {"offset", field.offset}, {"unsupported", field.tag}});
    }
    std::stable_sort(events.begin(), events.end(), [](const Event &a, const Event &b) { return a.frame < b.frame; });
    for (size_t i = 0; i < events.size(); ++i) if (events[i].add) {
        const auto &event = events[i];
        try {
            if (!declarations.count(event.name)) throw std::runtime_error("Undeclared ALS instance: " + event.name);
            const double childStart = start + boundary(*animation, event.frame);
            double childEnd = end;
            for (size_t j = i + 1; j < events.size(); ++j) if (events[j].name == event.name) {
                childEnd = std::min(childEnd, start + boundary(*animation, events[j].frame)); break;
            }
            if (childEnd > childStart) {
                auto childOrder = drawOrder;
                childOrder.emplace_back(event.layer, motion.tracks.size());
                addTrack(pvf, assets, motion, declarations.at(event.name), childStart,
                         layer + event.layer, x, y, false, childEnd, stack, depth + 1,
                         std::move(childOrder));
            }
        } catch (const std::exception &e) {
            motion.issues.push_back({{"resource", script.path}, {"offset", event.offset}, {"error", e.what()}});
        }
    }
}
void finishMotion(Assets &assets, MonsterMotion &motion) {
    bool visible = false;
    std::set<std::pair<std::string, int>> checked;
    for (const auto &track : motion.tracks) {
        motion.duration = std::max(motion.duration, track.end);
        for (const auto &frame : track.animation->frames) if (!frame.image.empty()) {
            if (!checked.emplace(frame.image, frame.imageFrame).second) continue;
            auto image = assets.pixels(frame.image, frame.imageFrame);
            for (size_t i = 3; i < image.rgba.size(); i += 4) if (image.rgba[i]) { visible = true; break; }
        }
    }
    if (!visible) throw std::runtime_error("Monster motion contains only transparent image placeholders: " + motion.entry);
    std::stable_sort(motion.tracks.begin(), motion.tracks.end(), monsterTrackBefore);
}
void compileEntry(Pvf &pvf, Assets &assets, MonsterMotion &motion) {
    if (motion.entry.size() >= 4 && motion.entry.substr(motion.entry.size() - 4) == ".ani") {
        motion.base = assets.animation(motion.entry);
        addTrack(pvf, assets, motion, motion.entry, 0, 0, 0, 0, true, 1e12);
    } else {
        auto action = pvf.script(motion.entry);
        bool inside = false;
        int bases = 0;
        struct Sub { std::string path; int frame, layer; double x, y; };
        std::vector<Sub> subs;
        for (const auto &field : action.fields) {
            const auto tag = normalize(field.tag);
            const auto &v = field.values;
            motion.references.push_back({{"source", action.path}, {"offset", field.offset},
                                         {"tag", field.tag}, {"values", v}});
            if (tag == "[motion]") inside = true;
            else if (tag == "[/motion]") inside = false;
            else if (inside && tag == "[base ani]") {
                if (v.size() != 1 || !v[0].is_string()) throw std::runtime_error("Malformed ACT BASE ANI: " + action.path);
                motion.base = assets.animation(reference(pvf, action.path, v[0].get<std::string>()));
                ++bases;
            } else if (inside && (tag == "[sub ani]" || tag == "[sub ani with xy]")) {
                const size_t stride = tag == "[sub ani]" ? 3 : 5;
                if (v.size() % stride) throw std::runtime_error("Malformed ACT SUB ANI tuple: " + action.path);
                for (size_t i = 0; i < v.size(); i += stride) {
                    if (!v[i].is_string() || !v[i + 1].is_number_integer() || !v[i + 2].is_number_integer() ||
                        (stride == 5 && (!v[i + 3].is_number() || !v[i + 4].is_number())))
                        throw std::runtime_error("Malformed ACT SUB ANI types: " + action.path);
                    subs.push_back({reference(pvf, action.path, v[i].get<std::string>()), v[i + 1], v[i + 2],
                                    stride == 5 ? v[i + 3].get<double>() : 0, stride == 5 ? v[i + 4].get<double>() : 0});
                }
            } else if (!tag.empty() && tag.substr(0, 2) != "[/")
                motion.issues.push_back({{"resource", action.path}, {"offset", field.offset},
                                         {inside ? "unexecuted_motion_tag" : "unexecuted_act_tag", field.tag}});
        }
        if (bases != 1) throw std::runtime_error("ACT requires exactly one MOTION BASE ANI: " + action.path);
        addTrack(pvf, assets, motion, motion.base->path, 0, 0, 0, 0, true, 1e12);
        for (const auto &sub : subs) {
            const auto animation = assets.animation(sub.path);
            const auto sourceLoop = animation->globals.find("0");
            const bool loops = sourceLoop != animation->globals.end() && sourceLoop->get<bool>();
            const auto start = boundary(*motion.base, sub.frame);
            const auto end = std::max(double(std::max(1, motion.base->duration)),
                start + (loops ? 0 : std::max(1, animation->duration)));
            addTrack(pvf, assets, motion, sub.path, start,
                     sub.layer, sub.x, sub.y, false, end, {}, 0,
                     {{sub.layer, motion.tracks.size()}});
        }
    }
    finishMotion(assets, motion);
}
} // namespace

std::shared_ptr<const MonsterMotion> compileMonsterMotion(Pvf &pvf, Assets &assets,
    const std::string &monster, const std::string &state) {
    auto motion = std::make_shared<MonsterMotion>();
    motion->monster = canonical(monster); motion->state = state;
    try {
        auto source = pvf.script(motion->monster);
        for (const auto &tag : stateTags(state)) {
            std::vector<std::pair<const Field *, std::string>> candidates;
            for (const auto &field : source.fields) if (normalize(field.tag) == tag)
                for (const auto &v : field.values) if (resource(v)) candidates.emplace_back(&field, v.get<std::string>());
            if (candidates.empty()) continue;
            motion->configured = true; motion->bindingTag = tag; motion->bindingOffset = candidates[0].first->offset;
            if (candidates.size() != 1 && state != "attack1" && tag != "[attack motion]" && tag != "[attack action]")
                throw std::runtime_error("Multiple state resources: " + motion->monster + " " + tag);
            const auto &field = *candidates[0].first;
            motion->references.push_back({{"source", source.path}, {"offset", field.offset},
                                          {"tag", field.tag}, {"values", field.values}});
            motion->entry = reference(pvf, source.path, candidates[0].second);
            compileEntry(pvf, assets, *motion);
            appendMonsterEquipment(pvf, assets, *motion, motion->monster);
            break;
        }
    } catch (const std::exception &e) { motion->error = e.what(); motion->tracks.clear(); }
    return motion;
}
std::shared_ptr<const MonsterMotion> compileMonsterAnimation(Pvf &pvf, Assets &assets,
    const std::string &animation, const std::string &state) {
    auto motion = std::make_shared<MonsterMotion>();
    motion->state = state; motion->entry = canonical(animation); motion->configured = true;
    try { compileEntry(pvf, assets, *motion); }
    catch (const std::exception &e) { motion->error = e.what(); motion->tracks.clear(); }
    return motion;
}
std::shared_ptr<const MonsterMotion> compileMonsterAnimationForMob(Pvf &pvf, Assets &assets,
    const std::string &monster, const std::string &animation, const std::string &state) {
    auto motion=std::make_shared<MonsterMotion>();motion->monster=canonical(monster);
    motion->state=state;motion->entry=canonical(animation);motion->configured=true;
    try{compileEntry(pvf,assets,*motion);appendMonsterEquipment(pvf,assets,*motion,motion->monster);}
    catch(const std::exception &error){motion->error=error.what();motion->tracks.clear();}
    return motion;
}
double monsterMotionTime(const MonsterMotion &motion, double elapsed, bool loop) {
    // 40JP sub_493840 wraps each animation at its own last frame. A long
    // decoration must not freeze the body on its final move/stay frame. This
    // function also drives the live body's collision sampling.
    const double duration = loop && motion.base ? motion.base->duration : motion.duration;
    if (duration <= 0) return 0;
    return loop ? std::fmod(std::max(0.0, elapsed), duration) : std::clamp(elapsed, 0.0, duration);
}
std::array<double, 4> monsterMotionBounds(Assets &assets, const MonsterMotion &motion,
    double elapsed, bool loop, int facing) {
    const double time = monsterMotionTime(motion, elapsed, loop);
    double left = 1e12, top = 1e12, right = -1e12, bottom = -1e12;
    for (const auto &track : motion.tracks) {
        if (time < track.start || (!track.hold && time >= track.end)) continue;
        const auto clock=monsterTrackClock(motion,track,time);
        auto pose = track.animation->samplePose(time - track.start, track.loop, -1,
            ani_render::RenderProfile::Legacy1031,clock?&*clock:nullptr);
        if (pose.image.empty()) continue;
        const auto image = assets.pixels(pose.image, pose.imageFrame);
        const auto quad = imageQuad(facing * track.x, track.y, pose.x, pose.y, image.x, image.y,
            image.width, image.height, facing, pose.scaleX * (pose.flip & 1 ? -1 : 1),
            pose.scaleY * (pose.flip & 2 ? -1 : 1), radiansToDegrees(pose.rotationRadians));
        for (const auto &p : quad) {
            left = std::min(left, p.x); top = std::min(top, p.y);
            right = std::max(right, p.x); bottom = std::max(bottom, p.y);
        }
    }
    if (left >= right || top >= bottom) throw std::runtime_error("No frozen monster sprite bounds: " + motion.entry);
    return {left, top, right - left, bottom - top};
}
DeathImpulse monsterDeathImpulse(double dx, double dy, int facing, double attackSpeed,
    int damage, int maxHp, double push, double lift) {
    DeathImpulse out;
    double magnitude = std::hypot(dx, dy);
    out.x = magnitude > .01 ? dx / magnitude : facing < 0 ? -1 : 1;
    out.y = magnitude > .01 ? dy / magnitude : 0;
    out.attackSpeed = std::max(0.0, attackSpeed);
    out.damageFraction = std::clamp(double(std::max(0, damage)) / std::max(1, maxHp), 0.0, 2.0);
    out.push = std::max(0.0, push); out.lift = std::max(0.0, lift);
    // Empirical controller policy: source PTL speed remains unchanged. Attack
    // travel speed / impulse / damage only scale the derived fragment velocity.
    out.speedScale = std::clamp(.55 + out.damageFraction * .55 + out.attackSpeed / 1200 +
                                out.push / 1200 + out.lift / 2400, .55, 2.3);
    return out;
}
MonsterDeathProfile readMonsterDeathProfile(Pvf &pvf, Assets &assets, const std::string &monster) {
    MonsterDeathProfile out;
    try {
        const auto script = pvf.script(monster);
        for (const auto &field : script.fields) if (normalize(field.tag) == "[die effect]") out.raw.push_back(field.values);
        if (out.raw.size() != 1 || out.raw[0].size() != 3) throw std::runtime_error("Missing or repeated MOB die effect");
        for (const auto &v : out.raw[0]) if (!v.is_number_integer()) throw std::runtime_error("Noninteger MOB die effect");
        out.selector = out.raw[0][0]; out.palette = out.raw[0][1]; out.omit = out.raw[0][2];
        if (out.selector < 0 || out.palette < 0 || out.palette > 9999 || out.omit < 0)
            throw std::runtime_error("Unsupported MOB die effect values");
        out.configured = true;
        out.pieces = out.palette > 0 && !(out.omit & 1);
        out.smoke = !(out.omit & 4); out.flash = !(out.omit & 8);
        char image[80]; std::snprintf(image, sizeof(image), "monster/common/m%04d.img", out.palette); out.image = image;
        const auto ptl = pvf.script("monster/common/particle/monsterdiepiece.ptl");
        out.count = int(ptl.number("[maximum create number]", -1));
        out.gravity = ptl.number("[gravity]", -1); out.lifeMs = int(ptl.number("[life time]", -1));
        out.speed = ptl.number("[move variable 1]", -1);
        if (out.count < 0 || out.count > 128 || out.gravity <= 0 || out.lifeMs <= 0 || out.speed < 0)
            throw std::runtime_error("Unsupported death PTL parameters");
        out.pieceAnimation = reference(pvf, ptl.path, ptl.text("[object]"));
        out.flashAnimation = "monster/common/animation/monsterdieflash.ani";
        out.smokeAnimation = "monster/common/animation/monsterdiesmoke.ani";
        if (out.pieces) {
            assets.animation(out.pieceAnimation);
            for (int frame = 0; frame < 4; ++frame) {
                auto pixels = assets.pixels(out.image, frame);
                if (pixels.width <= 0 || pixels.height <= 0) throw std::runtime_error("Empty death palette frame");
            }
        }
        if (out.flash) assets.animation(out.flashAnimation);
        if (out.smoke) assets.animation(out.smokeAnimation);
        out.valid = true;
    } catch (const std::exception &e) { out.issues.push_back({{"resource", monster}, {"error", e.what()}}); }
    return out;
}
uint32_t monsterDeathSeed(const std::string &path, int instance, int64_t tick) {
    uint32_t seed = 2166136261u;
    for (auto c : path) { seed ^= uint8_t(c); seed *= 16777619u; }
    seed ^= uint32_t(instance) * 0x9e3779b9u; seed ^= uint32_t(tick) * 0x85ebca6bu;
    return seed ? seed : 1;
}
std::vector<MonsterFragment> monsterDeathFragments(uint32_t seed, const MonsterDeathProfile &profile,
    const std::array<double, 4> &b, double height, const DeathImpulse &impulse) {
    if (!profile.valid || !profile.pieces) return {};
    auto random = [&]() { seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5; return double(seed & 0xffffff) / 0x1000000; };
    std::vector<MonsterFragment> result;
    const double speed = profile.speed * impulse.speedScale;
    for (int i = 0; i < profile.count; ++i) {
        MonsterFragment p;
        p.x = b[0] + b[2] * (.15 + random() * .7);
        // Use a separate z axis so hits from above can travel down the ground
        // plane while every stone still follows an independent vertical arc.
        p.y = 0; p.z = std::max(0.0, height - b[1] - b[3] * (.15 + random() * .7));
        const double directed = speed * (.55 + random() * .35);
        const double spread = speed * (random() * 2 - 1) * .22;
        p.vx = impulse.x * directed - impulse.y * spread;
        p.vy = impulse.y * directed + impulse.x * spread;
        p.vz = speed * (.42 + random() * .38);
        p.spin = (random() * 2 - 1) * 360; p.angle = random() * 360;
        p.frame = int(random() * 4); p.size = .5 + random() * .5;
        result.push_back(p);
    }
    return result;
}
MonsterFragmentPose monsterFragmentPose(const MonsterFragment &p, double seconds, double gravity) {
    const double impact = gravity > 0 ? (p.vz + std::sqrt(p.vz * p.vz + 2 * gravity * std::max(0.0, p.z))) / gravity : std::max(0.0, seconds);
    const double t = std::clamp(seconds, 0.0, impact);
    return {p.x + p.vx * t, p.y + p.vy * t,
            std::max(0.0, p.z + p.vz * t - .5 * gravity * t * t), p.angle + p.spin * t};
}
void World::restoreMonsterVisuals(Actor &actor) {
    // Rehydration is deliberately separate from beginDeath: no HP mutation,
    // killed/drop/XP events, new death clock or random restart is allowed here.
    if (!actor.dead || actor.monsterPath.empty() || actor.life == ActorLife::Removed) return;
    const bool legacy = actor.deathRoute.empty();
    const auto identity = actor.deathMotion;
    const std::string savedEntry = identity ? identity->entry : "";
    const auto elapsed = std::max<int64_t>(0, nowMs() - actor.deathStart);
    const auto independent = compileMonsterMotion(pvf_, assets_, actor.monsterPath, "death");
    auto diagnostic = [&](const std::string &reason) {
        events.push_back({tick, "monster_visual_issue", "restore: " + reason, actor.id});
    };
    auto frozen = [&]() {
        const auto state = identity && !identity->state.empty() ? identity->state : actor.animation;
        auto motion = compileMonsterMotion(pvf_, assets_, actor.monsterPath, state);
        if (!savedEntry.empty()) {
            // Preserve the MOB binding provenance when it still selects the
            // saved entry; explicit attack variants retain their exact entry.
            if (motion->valid() && motion->entry == normalize(savedEntry)) return motion;
            return compileMonsterAnimationForMob(pvf_, assets_, actor.monsterPath, savedEntry, state);
        }
        if (!actor.animationPath.empty() &&
            (!motion->valid() || motion->base->path != normalize(actor.animationPath)))
            motion = compileMonsterAnimationForMob(pvf_, assets_, actor.monsterPath, actor.animationPath, state);
        return motion;
    };
    if (legacy) {
        actor.independentDeath = independent->valid();
        actor.deathMotion = actor.independentDeath ? independent : frozen();
        if (actor.independentDeath) {
            actor.deathRoute = "last-action";
            actor.deathLoop = false;
            actor.deathDuration = int(std::ceil(independent->duration));
        } else {
            actor.deathRoute = "diagnostic-fade";
            actor.deathDuration = 450;
            actor.deathProfile = readMonsterDeathProfile(pvf_, assets_, actor.monsterPath);
            if (!independent->configured && actor.deathMotion->valid() && actor.deathProfile.valid) {
                try {
                    actor.deathBounds = monsterMotionBounds(assets_, *actor.deathMotion,
                        actor.deathPoseTime, actor.deathLoop, actor.dir);
                    // Old saves had no random initial conditions. The fallback
                    // seed uses stable saved state, not the new world clock.
                    actor.deathFragments = monsterDeathFragments(
                        monsterDeathSeed(actor.monsterPath, actor.id, actor.deathPoseTime),
                        actor.deathProfile, actor.deathBounds, actor.deathHeight, actor.lastImpact);
                    actor.deathRoute = "shared-source-palette";
                    actor.deathDuration = monsterDeathBurstMs + monsterFragmentDisplayMs(actor.deathProfile);
                } catch (const std::exception &e) { diagnostic(e.what()); }
            }
        }
    } else if (actor.deathRoute == "last-action") {
        actor.independentDeath = true;
        actor.deathMotion = independent;
        if (!independent->valid() || (!savedEntry.empty() && normalize(savedEntry) != independent->entry)) {
            diagnostic("saved last action is missing, invalid or no longer bound by the MOB");
            actor.independentDeath = false;
            actor.deathRoute = "diagnostic-fade";
            actor.deathMotion = frozen();
        }
        actor.deathFragments.clear();
    } else {
        actor.independentDeath = false;
        actor.deathMotion = frozen();
        if (actor.deathRoute == "shared-source-palette") {
            const auto old = actor.deathProfile;
            auto current = readMonsterDeathProfile(pvf_, assets_, actor.monsterPath);
            const bool same = old.configured && old.raw == current.raw && old.image == current.image &&
                old.count == current.count && old.lifeMs == current.lifeMs && old.gravity == current.gravity &&
                old.speed == current.speed && old.pieceAnimation == current.pieceAnimation &&
                old.flashAnimation == current.flashAnimation && old.smokeAnimation == current.smokeAnimation;
            if (!current.valid || !same || (current.pieces && int(actor.deathFragments.size()) != current.count)) {
                diagnostic("saved shared-death source profile/particle count no longer matches current resources");
                actor.deathRoute = "diagnostic-fade";
            }
            actor.deathProfile = std::move(current);
            if (actor.deathRoute == "shared-source-palette")
                actor.deathDuration = monsterDeathBurstMs + monsterFragmentDisplayMs(actor.deathProfile);
        }
    }
    if (!actor.deathMotion || !actor.deathMotion->valid()) {
        diagnostic(actor.deathMotion ? actor.deathMotion->error : "missing frozen source identity");
        // Invalid plans remain diagnosed, but no actor may re-enter Alive and
        // accidentally issue a second death/reward event on its next tick.
        actor.deathRoute = "diagnostic-fade";
        actor.independentDeath = false;
    }
    actor.capturedBy = -1;
    actor.vx = actor.vy = 0;
    if (elapsed >= actor.deathDuration) actor.life = ActorLife::Removed;
    else if (actor.deathRoute == "shared-source-palette" && elapsed >= monsterDeathBurstMs)
        actor.life = ActorLife::DeathEffect;
    else actor.life = ActorLife::Dying;
}
} // namespace dnf
