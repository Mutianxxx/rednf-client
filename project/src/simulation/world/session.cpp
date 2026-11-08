#include "dnf/session.hpp"
#include "dnf/monster_attributes.hpp"
#include <set>
#include <queue>
#include <limits>
#include <cmath>
namespace dnf {
namespace {
uint64_t savedUnsigned(const Json &value, uint64_t maximum, const std::string &name) {
    uint64_t number;
    if (value.is_number_unsigned()) number = value.get<uint64_t>();
    else if (value.is_number_integer() && value.get<int64_t>() >= 0) number = uint64_t(value.get<int64_t>());
    else throw std::runtime_error("Saved " + name + " must be a non-negative integer");
    if (number > maximum) throw std::runtime_error("Saved " + name + " exceeds supported range");
    return number;
}
int savedInt(const Json &object, const char *key, int minimum, int maximum) {
    const auto number = savedUnsigned(object.at(key), uint64_t(maximum), key);
    if (number < uint64_t(minimum)) throw std::runtime_error(std::string("Saved ") + key + " is below supported range");
    return int(number);
}
bool savedBool(const Json &object, const char *key, bool fallback = false) {
    if (!object.contains(key)) return fallback;
    if (!object.at(key).is_boolean()) throw std::runtime_error(std::string("Saved ") + key + " must be boolean");
    return object.at(key).get<bool>();
}
std::string savedString(const Json &object, const char *key) {
    if (!object.at(key).is_string()) throw std::runtime_error(std::string("Saved ") + key + " must be a string");
    return object.at(key).get<std::string>();
}
void overlay(Json &target, const Json &known) {
    if (!target.is_object()) target = Json::object();
    for (auto field = known.begin(); field != known.end(); ++field) target[field.key()] = field.value();
}
void validateMazeSource(const DungeonRun &run, const RegionCatalog &catalog) {
    const auto &start = run.rooms.at(run.start), &boss = run.rooms.at(run.boss);
    for (const auto &maze : catalog.dungeons.at(run.dungeonId).mazes) {
        if (maze.width != run.width || maze.height != run.height ||
            maze.doorMasks.size() != size_t(run.width * run.height) ||
            std::find(maze.starts.begin(), maze.starts.end(), std::array<int,2>{start.x,start.y}) == maze.starts.end() ||
            std::find(maze.bosses.begin(), maze.bosses.end(), std::array<int,2>{boss.x,boss.y}) == maze.bosses.end()) continue;
        bool matches = true;
        for (const auto &room : run.rooms) {
            const int cell = room.y * run.width + room.x;
            const auto expected = dungeonRoomCandidates(catalog, run.dungeonId, maze, cell, room.doors, room.boss,run.generatorVersion);
            std::set<int> expectedSet(expected.begin(), expected.end()), savedSet(room.candidates.begin(), room.candidates.end());
            const auto map = catalog.maps.find(room.mapId);
            if ((room.doors & ~maze.doorMasks.at(cell)) || expectedSet != savedSet ||
                (run.generatorVersion=="pcg32-source-topology-v2"&&expected!=room.candidates) ||
                map == catalog.maps.end() || map->second.path != room.path ||
                !expectedSet.count(room.mapId)) {
                matches = false; break;
            }
        }
        if (matches) return;
    }
    throw std::runtime_error("Saved topology, endpoints or complete ordered candidate set no longer matches any source DGN maze");
}
}
Json saveActor(const Actor &a, int64_t now) {
    Json out = {{"id", a.id}, {"source_id", a.sourceId}, {"path", a.monsterPath}, {"source_stats",a.sourceStats},
        {"x", a.x}, {"y", a.y}, {"z", a.z}, {"vz", a.vz}, {"vx", a.vx}, {"vy", a.vy},
        {"dir", a.dir}, {"hp", a.hp}, {"max_hp", a.maxHp}, {"mp", a.mp}, {"max_mp", a.maxMp},
        {"boss", a.boss}, {"dead", a.dead}, {"animation", a.animation}, {"animation_path", a.animationPath},
        {"anim_age", now-a.animStart}, {"stun_remaining", std::max<int64_t>(0,a.stunUntil-now)},
        {"hit_stop_ticks", a.hitStopTicks},
        {"recovery", a.recovery}, {"life", int(a.life)}, {"death_age", now-a.deathStart},
        {"life_age", now-a.lifeStart}, {"death_pose_time", a.deathPoseTime},
        {"next_attack", std::max<int64_t>(0,a.nextAttack-now)}, {"attack_variant",a.attackVariant},
        {"attack_serial",a.attackSerial}, {"attack_hit",a.attackHit}};
    const auto &reaction=a.hitReaction;
    out["hit_reaction"]={{"version",1},{"state",reaction.state},{"substate",reaction.substate},
        {"direction",reaction.direction},{"acceleration_x",reaction.accelerationX},
        {"acceleration_remaining_ms",reaction.accelerationRemainingMs},{"gravity",reaction.gravity},
        {"remaining_ms",reaction.remainingMs},{"peak_height",reaction.peakHeight},
        {"launch_height",reaction.launchHeight},{"push_speed",reaction.pushSpeed},{"weight",reaction.weight}};
    // Persist initial particle conditions and source identity, never a sampled
    // screen-space pose or SDL pointer. Ages are rebased by loadActor.
    out["death_visual_version"] = 1;
    out["entity_handle"]=a.handle.json();
    out["death_route"] = a.deathRoute;
    out["independent_death"] = a.independentDeath;
    out["death_duration"] = a.deathDuration;
    out["death_loop"] = a.deathLoop;
    out["death_anchor"] = {a.deathAnchorX, a.deathAnchorY, a.deathHeight};
    out["death_bounds"] = a.deathBounds;
    out["death_motion"] = a.deathMotion ? Json{{"entry", a.deathMotion->entry},
        {"state", a.deathMotion->state}, {"monster", a.deathMotion->monster},
        {"binding_tag", a.deathMotion->bindingTag}, {"binding_offset", a.deathMotion->bindingOffset},
        {"base", a.deathMotion->base ? a.deathMotion->base->path : ""}} : Json(nullptr);
    const auto &p = a.deathProfile;
    out["death_profile"] = {{"configured", p.configured}, {"valid", p.valid},
        {"pieces", p.pieces}, {"smoke", p.smoke}, {"flash", p.flash},
        {"selector", p.selector}, {"palette", p.palette}, {"omit", p.omit},
        {"count", p.count}, {"life_ms", p.lifeMs}, {"gravity", p.gravity}, {"speed", p.speed},
        {"image", p.image}, {"piece_animation", p.pieceAnimation},
        {"flash_animation", p.flashAnimation}, {"smoke_animation", p.smokeAnimation},
        {"raw", p.raw}, {"issues", p.issues}};
    const auto &i = a.lastImpact;
    out["last_impact"] = {{"x", i.x}, {"y", i.y}, {"speed_scale", i.speedScale},
        {"attack_speed", i.attackSpeed}, {"damage_fraction", i.damageFraction},
        {"push", i.push}, {"lift", i.lift}};
    out["death_fragments"] = Json::array();
    for (const auto &f : a.deathFragments)
        out["death_fragments"].push_back({{"x", f.x}, {"y", f.y}, {"z", f.z},
            {"vx", f.vx}, {"vy", f.vy}, {"vz", f.vz}, {"spin", f.spin},
            {"angle", f.angle}, {"size", f.size}, {"frame", f.frame}});
    return out;
}
Actor loadActor(const Json &j, int64_t now) {
    Actor a; a.id=j.at("id"); a.sourceId=j.value("source_id",0); a.monsterPath=j.value("path",std::string());
    a.sourceStats=j.value("source_stats",Json::object());
    if(!a.sourceStats.is_object()) throw std::runtime_error("Invalid saved actor source-stat trace");
    a.x=a.px=j.at("x"); a.y=a.py=j.at("y"); a.z=a.pz=j.value("z",0.0); a.vz=j.value("vz",0.0);
    a.vx=j.value("vx",0.0); a.vy=j.value("vy",0.0); a.dir=j.value("dir",1);
    if(j.contains("hit_reaction")) {
        const auto &saved=j.at("hit_reaction");
        if(!saved.is_object()||savedInt(saved,"version",1,1)!=1)
            throw std::runtime_error("Invalid saved monster hit reaction version");
        auto signedInt=[&](const char *key,int minimum,int maximum) {
            const auto &value=saved.at(key);
            if(!value.is_number_integer()||
               (value.is_number_unsigned()&&value.get<uint64_t>()>uint64_t(INT64_MAX)))
                throw std::runtime_error(std::string("Invalid saved hit reaction ")+key);
            const auto number=value.get<int64_t>();
            if(number<minimum||number>maximum)
                throw std::runtime_error(std::string("Invalid saved hit reaction ")+key);
            return int(number);
        };
        auto finite=[&](const char *key,double minimum,double maximum) {
            const auto &value=saved.at(key);
            if(!value.is_number())throw std::runtime_error(std::string("Invalid saved hit reaction ")+key);
            const double number=value.get<double>();
            if(!std::isfinite(number)||number<minimum||number>maximum)
                throw std::runtime_error(std::string("Invalid saved hit reaction ")+key);
            return number;
        };
        auto &reaction=a.hitReaction;
        reaction.state=signedInt("state",0,4);
        if(reaction.state!=0&&reaction.state!=3&&reaction.state!=4)
            throw std::runtime_error("Invalid saved hit reaction state");
        reaction.substate=signedInt("substate",0,1);
        reaction.direction=signedInt("direction",-1,1);
        if(!reaction.direction)throw std::runtime_error("Invalid saved hit reaction direction");
        reaction.accelerationX=signedInt("acceleration_x",INT32_MIN,INT32_MAX);
        reaction.accelerationRemainingMs=signedInt("acceleration_remaining_ms",0,INT32_MAX);
        reaction.gravity=signedInt("gravity",-1000000,-1);
        reaction.remainingMs=int64_t(savedUnsigned(saved.at("remaining_ms"),uint64_t(INT32_MAX),"hit reaction remaining_ms"));
        reaction.peakHeight=finite("peak_height",0,INT32_MAX);
        reaction.launchHeight=finite("launch_height",INT32_MIN,INT32_MAX);
        reaction.pushSpeed=finite("push_speed",0,INT32_MAX);
        reaction.weight=finite("weight",0,INT32_MAX);
        for(const auto value:{a.x,a.y,a.z,a.vx,a.vy,a.vz})
            if(!std::isfinite(value))throw std::runtime_error("Saved reaction position/velocity must be finite");
        if(reaction.state==3&&reaction.remainingMs<=0)
            throw std::runtime_error("Active standing hit reaction must retain positive time");
    }
    a.maxHp=std::max(1,j.value("max_hp",180)); a.hp=std::clamp(j.value("hp",a.maxHp),0,a.maxHp);
    a.maxMp=std::max(1,j.value("max_mp",140)); a.mp=std::clamp(j.value("mp",a.maxMp),0,a.maxMp);
    a.boss=j.value("boss",false); a.dead=j.value("dead",false); a.animation=j.value("animation",std::string("stay"));
    if(a.dead&&a.hitReaction.state!=0)
        throw std::runtime_error("Dead actor cannot restore an active living hit reaction");
    a.animationPath=j.value("animation_path",std::string()); a.animStart=now-j.value("anim_age",int64_t(0));
    a.stunUntil=now+j.value("stun_remaining",int64_t(0)); a.recovery=j.value("recovery",0);
    a.hitStopTicks=std::clamp(j.value("hit_stop_ticks",0),0,30);
    a.life=ActorLife(std::clamp(j.value("life",0),0,3)); a.deathStart=now-j.value("death_age",int64_t(0));
    a.lifeStart=now-j.value("life_age",int64_t(0)); a.deathPoseTime=j.value("death_pose_time",int64_t(0));
    a.nextAttack=now+j.value("next_attack",int64_t(0)); a.attackVariant=j.value("attack_variant",0);
    a.attackSerial=j.value("attack_serial",0); a.attackHit=j.value("attack_hit",false);
    a.deathRoute=j.value("death_route",std::string());
    a.independentDeath=j.value("independent_death",false);
    a.deathDuration=std::max(1,j.value("death_duration",500));
    a.deathLoop=j.value("death_loop",a.animation=="stay"||a.animation=="move");
    // Legacy deaths had no anchor. The already-saved world position is the
    // safe anchor; using Actor's zero default would teleport corpses to (0,0).
    a.deathAnchorX=a.x; a.deathAnchorY=a.y; a.deathHeight=a.z;
    if(j.contains("death_anchor")) {
        const auto &v=j.at("death_anchor");
        if(!v.is_array()||v.size()!=3)throw std::runtime_error("Invalid saved death anchor");
        a.deathAnchorX=v[0];a.deathAnchorY=v[1];a.deathHeight=v[2];
    }
    if(j.contains("death_bounds"))a.deathBounds=j.at("death_bounds").get<std::array<double,4>>();
    if(j.contains("death_motion")&&j.at("death_motion").is_object()) {
        const auto &v=j.at("death_motion");
        auto identity=std::make_shared<MonsterMotion>();
        identity->entry=v.value("entry",std::string());identity->state=v.value("state",a.animation);
        identity->monster=v.value("monster",a.monsterPath);identity->bindingTag=v.value("binding_tag",std::string());
        identity->bindingOffset=v.value("binding_offset",size_t(0));
        const auto base=v.value("base",std::string());
        if(!base.empty()){identity->base=std::make_shared<Animation>();identity->base->path=base;}
        identity->configured=!identity->entry.empty();
        identity->error="Saved source identity; resource plan has not been recompiled";
        a.deathMotion=std::move(identity);
    }
    if(j.contains("death_profile")) {
        const auto &v=j.at("death_profile");auto &p=a.deathProfile;
        p.configured=v.value("configured",false);p.valid=v.value("valid",false);
        p.pieces=v.value("pieces",false);p.smoke=v.value("smoke",false);p.flash=v.value("flash",false);
        p.selector=v.value("selector",0);p.palette=v.value("palette",0);p.omit=v.value("omit",0);
        p.count=v.value("count",0);p.lifeMs=v.value("life_ms",0);
        p.gravity=v.value("gravity",0.0);p.speed=v.value("speed",0.0);
        p.image=v.value("image",std::string());p.pieceAnimation=v.value("piece_animation",std::string());
        p.flashAnimation=v.value("flash_animation",std::string());p.smokeAnimation=v.value("smoke_animation",std::string());
        p.raw=v.value("raw",Json::array());p.issues=v.value("issues",Json::array());
    }
    if(j.contains("last_impact")) {
        const auto &v=j.at("last_impact");auto &i=a.lastImpact;
        i.x=v.value("x",1.0);i.y=v.value("y",0.0);i.speedScale=v.value("speed_scale",1.0);
        i.attackSpeed=v.value("attack_speed",0.0);i.damageFraction=v.value("damage_fraction",0.0);
        i.push=v.value("push",0.0);i.lift=v.value("lift",0.0);
    }
    if(j.contains("death_fragments")) {
        const auto &fragments=j.at("death_fragments");
        if(!fragments.is_array()||fragments.size()>128)throw std::runtime_error("Invalid saved death fragments");
        for(const auto &v:fragments) {
            MonsterFragment f;
            f.x=v.at("x");f.y=v.at("y");f.z=v.at("z");
            f.vx=v.at("vx");f.vy=v.at("vy");f.vz=v.at("vz");
            f.spin=v.at("spin");f.angle=v.at("angle");f.size=v.at("size");f.frame=v.at("frame");
            if(f.frame<0||f.frame>3||f.size<=0)throw std::runtime_error("Invalid saved death fragment frame/size");
            a.deathFragments.push_back(f);
        }
    }
    // Restored actors are never captured by an unsaved transient controller.
    a.capturedBy=-1;
    return a;
}
void restoreSessionPlayer(World &world, const Json &snapshot) {
    if (!snapshot.is_object()) throw std::runtime_error("Saved player must be an object");
    // Application input timestamps are signed nanoseconds. Saved millisecond
    // ages cannot exceed that same simulation horizon. Validate before the
    // generic decoder performs now +/- age, and allow a rebased start below
    // zero when an old session resumes on a younger World clock.
    constexpr int64_t maximumTimeMs = std::numeric_limits<int64_t>::max() / 1000000;
    (void)world.simulationNanoseconds();
    const int64_t now = world.nowMs();
    if (now > maximumTimeMs) throw std::runtime_error("World time exceeds session restore horizon");
    for (const char *key : {"anim_age","death_age","life_age","death_pose_time","stun_remaining","next_attack"}) {
        if (!snapshot.contains(key)) continue;
        const uint64_t maximum = std::string(key) == "stun_remaining" || std::string(key) == "next_attack" ?
            uint64_t(maximumTimeMs - now) : uint64_t(maximumTimeMs);
        savedUnsigned(snapshot.at(key),maximum,key);
    }
    // JSON numeric conversions must not narrow an oversized integer or turn a
    // fractional direction/life code into an apparently valid enum.
    for (const char *key : {"id","source_id","dir","hp","max_hp","mp","max_mp","life", "hit_stop_ticks",
                            "recovery","attack_variant","attack_serial","death_duration"}) {
        if (!snapshot.contains(key)) continue;
        const auto &value = snapshot.at(key);
        if (!value.is_number_integer() ||
            (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(std::numeric_limits<int>::max())) ||
            (!value.is_number_unsigned() && (value.get<int64_t>() < std::numeric_limits<int>::min() ||
                                           value.get<int64_t>() > std::numeric_limits<int>::max())))
            throw std::runtime_error(std::string("Saved player ") + key + " exceeds integer storage");
    }
    if (snapshot.contains("life") && (snapshot.at("life").get<int>() < int(ActorLife::Alive) ||
                                       snapshot.at("life").get<int>() > int(ActorLife::Removed)))
        throw std::runtime_error("Invalid saved player life phase");
    const Actor decoded = loadActor(snapshot,now);
    for (const double value : {decoded.x,decoded.y,decoded.z,decoded.vx,decoded.vy,decoded.vz,
                              decoded.deathAnchorX,decoded.deathAnchorY,decoded.deathHeight})
        if (!std::isfinite(value)) throw std::runtime_error("Saved player position/motion must be finite");
    for (const double value : decoded.deathBounds)
        if (!std::isfinite(value)) throw std::runtime_error("Saved player death bounds must be finite");
    if (decoded.z < 0 || (decoded.dir != -1 && decoded.dir != 1))
        throw std::runtime_error("Invalid saved player height/direction");
    if (world.player.maxHp <= 0 || world.player.maxMp < 0)
        throw std::runtime_error("Current player resource limits are unavailable");
    const bool dead = decoded.dead || decoded.life != ActorLife::Alive || decoded.hp == 0;
    if (dead && decoded.lifeStart < decoded.deathStart)
        throw std::runtime_error("Saved player phase starts before death");

    Actor next = world.player;
    next.x = next.px = decoded.x; next.y = next.py = decoded.y; next.dir = decoded.dir;
    if (!world.canWalk(next.x,next.y)) {
        const auto point = world.nearestWalkable(next.x,next.y);
        if (!world.canWalk(point[0],point[1])) throw std::runtime_error("Saved player position cannot recover to current source map");
        next.x = next.px = point[0]; next.y = next.py = point[1];
    }
    next.hp = dead ? 0 : std::clamp(decoded.hp,0,next.maxHp);
    next.mp = std::clamp(decoded.mp,0,next.maxMp);
    next.dead = dead;
    next.life = dead ? (decoded.life == ActorLife::Alive ? ActorLife::Dying : decoded.life) : ActorLife::Alive;
    next.z = next.pz = dead ? decoded.z : 0; next.vz = dead ? decoded.vz : 0;
    next.vx = next.vy = 0; next.stunUntil = 0; next.hitStopTicks = 0; next.hitStopped = false;
    next.hitReaction={};
    next.capturedBy = -1; next.recovery = 0; next.attackHit = false;
    next.attackVariant = next.attackSerial = 0; next.nextAttack = 0;
    next.poseFrame = -1; next.hitFlashUntil = 0;
    next.animation = dead ? decoded.animation : "stay";
    next.animationPath = dead ? decoded.animationPath : std::string();
    next.animStart = dead ? decoded.animStart : now;
    next.deathStart = dead ? decoded.deathStart : now;
    next.lifeStart = dead ? decoded.lifeStart : now;
    next.deathPoseTime = dead ? decoded.deathPoseTime : 0;
    next.deathDuration = dead ? decoded.deathDuration : 500;
    next.deathLoop = dead && decoded.deathLoop;
    next.deathAnchorX = next.x; next.deathAnchorY = next.y; next.deathHeight = next.z;
    next.deathMotion.reset(); next.deathFragments.clear(); next.deathProfile = {};
    next.independentDeath = false; next.deathRoute.clear(); next.deathBounds = {};

    // The session's World checkpoint already cancels effect instances. These
    // calls also make standalone player restoration cancel its active action
    // and held input without changing the entity registry/handle.
    if(snapshot.contains("status_state")) {
        if(next.dead) throw std::invalid_argument("A dead player cannot restore a live stun bundle");
        const auto &bundle=snapshot.at("status_state");
        world.restoreStatusCheckpoint(bundle,EntityHandle::fromJson(snapshot.at("entity_handle")),next.handle,
            bundle.at("commit_generation").get<uint64_t>());
    } else world.clearRestoredPlayerStatus();
    world.idle();
    world.releaseInputs();
    world.attackVolumes.clear();
    world.player = std::move(next);
}
void RegionSession::clear() { run= DungeonRun{}; roomStates.clear(); objects=Json::object(); drops=Json::object(); balance={}; monsterLevelPolicy={}; dungeonDifficulty=0; difficultyPolicy="legacy-exact-easy-v1"; monsterStatPolicy="legacy-demo-v1"; monsterCombatPolicy="legacy-snapshot-damage-v1"; preserved_=Json::object(); }
void RegionSession::begin(const RegionCatalog &c,int dungeon,uint64_t seed,DemoBalance requestedBalance,std::string monsterPolicy,std::string combatPolicy,MonsterLevelPolicy levelPolicy,int difficulty) {
    if (monsterPolicy != "legacy-demo-v1" && monsterPolicy != MonsterHpPolicy::inferredMobTableHpV1().id)
        throw std::runtime_error("Unsupported dungeon monster-stat policy: " + monsterPolicy);
    RegionSession next;
    dungeonDifficultyRequest(difficulty);
    next.dungeonDifficulty=difficulty;next.difficultyPolicy=dungeonDifficultyPolicy;
    if(combatPolicy!="legacy-snapshot-damage-v1" && combatPolicy!=MonsterCombatAttributePolicy::inferredMobCombatTableV1().id)
        throw std::runtime_error("Unsupported dungeon monster combat policy: "+combatPolicy);
    next.monsterLevelPolicy=std::move(levelPolicy);
    next.monsterCombatPolicy=std::move(combatPolicy);
    next.balance=DemoBalance::fromJson(requestedBalance.describe());
    next.monsterStatPolicy=std::move(monsterPolicy);
    next.run=DungeonRun::generate(c,dungeon,seed,(dungeon==1||dungeon==2)?"pcg32-world-v1":"pcg32-source-topology-v2"); next.roomStates.resize(next.run.rooms.size());
    *this=std::move(next);
}
void RegionSession::remember(const World &w) {
    if (!active()) return;
    auto &state=roomStates.at(run.current); state=Json::array();
    for (const auto &a:w.monsters) {
        auto saved=saveActor(a,w.nowMs());
        auto eventState=w.monsterEventActorCheckpoint(a.handle);
        if(!eventState.is_null())saved["monster_event_ai_state"]=std::move(eventState);
        auto sourceCooldowns=w.sourceMonsterCooldownCheckpoint(a.handle);
        if(!sourceCooldowns.is_null())saved["source_action_cooldowns"]=std::move(sourceCooldowns);
        if(a.handle && !a.dead && a.life!=ActorLife::Removed) {
            auto status=w.statusCheckpoint(a.handle);
            if(!status.at("contacts").empty() || !status.at("active").empty()) saved["status_state"]=std::move(status);
        }
        state.push_back(std::move(saved));
    }
    run.room().visited=true;
    // A prepared empty ordinary corridor may clear. An empty boss room is a
    // missing-mechanism/source diagnostic, never proof that a boss was killed.
    run.room().cleared=(!run.room().boss || !w.monsters.empty()) &&
        std::all_of(w.monsters.begin(),w.monsters.end(),[](const Actor &a){return a.dead;});
}
bool RegionSession::restore(World &w) const {
    if (!active() || roomStates.at(run.current).is_null()) return false;
    std::vector<Actor> restored;
    for (const auto &j:roomStates.at(run.current)) {
        auto actor=loadActor(j,w.nowMs());
        w.restoreMonsterAttributes(actor);
        w.restoreMonsterVisuals(actor);
        restored.push_back(std::move(actor));
    }
    w.restoreRoomActors(std::move(restored),roomStates.at(run.current));
    return true;
}
Json RegionSession::save(const World &w,const std::string &location) const {
    Json j=preserved_;
    j["version"]=4;j["location"]=location;
    overlay(j["player"],saveActor(w.player,w.nowMs()));
    j["player"].erase("status_state");
    if(w.player.handle && !w.player.dead) {
        auto status=w.statusCheckpoint(w.player.handle);
        if(!status.at("contacts").empty() || !status.at("active").empty()) j["player"]["status_state"]=std::move(status);
    }
    if (!active() || location!="dungeon") {
        for(const char *key:{"run","demo_balance","monster_stat_policy","monster_combat_policy","monster_level_policy","dungeon_difficulty","room_states","objects","drops"})j.erase(key);
        return j;
    }
    auto copy=*this; copy.remember(w);
    auto described=run.describe();
    auto oldRooms=j.contains("run")&&j["run"].is_object()?j["run"].value("rooms",Json::array()):Json::array();
    for(size_t i=0;i<described["rooms"].size();++i) {
        Json room=oldRooms.is_array()&&i<oldRooms.size()?oldRooms[i]:Json::object();
        overlay(room,described["rooms"][i]);described["rooms"][i]=std::move(room);
    }
    overlay(j["run"],described);j["run"]["current"]=run.current;
    j["demo_balance"]=balance.describe();
    j["monster_stat_policy"]=monsterStatPolicy;
    j["monster_combat_policy"]=monsterCombatPolicy;
    j["monster_level_policy"]=monsterLevelPolicy.json();
    overlay(j["dungeon_difficulty"],Json{{"policy",difficultyPolicy},{"tier",dungeonDifficulty}});
    j["room_states"]=copy.roomStates; j["objects"]=objects; j["drops"]=drops;
    for(size_t i=0;i<copy.run.rooms.size();++i){
        j["run"]["rooms"][i]["visited"]=copy.run.rooms[i].visited;
        j["run"]["rooms"][i]["cleared"]=copy.run.rooms[i].cleared;
    }
    return j;
}
bool RegionSession::load(const Json &j,const RegionCatalog &c) {
    if(j.is_null()) {clear();return false;}
    if(!j.is_object())throw std::runtime_error("Saved session must be an object");
    const int version=j.contains("version")?savedInt(j,"version",1,4):1;
    RegionSession next;
    next.preserved_=j;
    next.monsterLevelPolicy=MonsterLevelPolicy::fromJson(j.value("monster_level_policy",Json()));
    if(!j.contains("run")) {*this=std::move(next);return false;}
    if(j.contains("dungeon_difficulty")) {
        const auto &difficulty=j.at("dungeon_difficulty");
        if(!difficulty.is_object())throw std::runtime_error("Saved dungeon difficulty must be an object");
        next.dungeonDifficulty=savedInt(difficulty,"tier",0,dungeonDifficultyCount-1);
        next.difficultyPolicy=savedString(difficulty,"policy");
        next.monsterAiDifficulty();
        if(next.difficultyPolicy=="legacy-exact-easy-v1"&&next.dungeonDifficulty!=0)
            throw std::runtime_error("Legacy exact easy policy cannot restore another tier");
    }
    // Old sessions retain the previous 65/240 demo HP in unvisited rooms too.
    next.balance=DemoBalance::fromJson(j.value("demo_balance",Json()),1,1);
    next.monsterStatPolicy=j.value("monster_stat_policy",std::string("legacy-demo-v1"));
    next.monsterCombatPolicy=j.value("monster_combat_policy",std::string("legacy-snapshot-damage-v1"));
    if(next.monsterCombatPolicy!="legacy-snapshot-damage-v1" && next.monsterCombatPolicy!=MonsterCombatAttributePolicy::inferredMobCombatTableV1().id)
        throw std::runtime_error("Saved dungeon monster combat policy is unavailable: "+next.monsterCombatPolicy);
    if (next.monsterStatPolicy != "legacy-demo-v1" && next.monsterStatPolicy != MonsterHpPolicy::inferredMobTableHpV1().id)
        throw std::runtime_error("Saved dungeon monster-stat policy is unavailable: " + next.monsterStatPolicy);
    const auto &s=j.at("run");
    if(!s.is_object())throw std::runtime_error("Saved run must be an object");
    const int dungeon=savedInt(s,"dungeon",0,std::numeric_limits<int>::max());
    const auto seed=savedUnsigned(s.at("seed"),std::numeric_limits<uint64_t>::max(),"seed");
    if(!s.at("rooms").is_array()||s.at("rooms").empty()||s.at("rooms").size()>16384)
        throw std::runtime_error("Invalid saved dungeon room list");
    if (!c.dungeons.count(dungeon) || !c.dungeons.at(dungeon).enabled)
        throw std::runtime_error("Saved dungeon is unavailable; preserve snapshot and select a compatible content profile");
    auto &run=next.run;
    if(version<4) {
        // Explicit legacy migration only. New snapshots restore selected layout
        // directly and never consume the current generator or random stream.
        run=DungeonRun::generate(c,dungeon,seed,s.value("generator_version",std::string("legacy-mt19937_64-v1")));
        if(run.rooms.size()!=s.at("rooms").size()) throw std::runtime_error("Saved dungeon topology changed");
        for(size_t i=0;i<run.rooms.size();++i)
            if(run.rooms[i].mapId!=savedInt(s["rooms"][i],"map",0,std::numeric_limits<int>::max()) ||
               run.rooms[i].doors!=savedInt(s["rooms"][i],"doors",1,15))
                throw std::runtime_error("Saved dungeon source mismatch");
    } else {
        run.dungeonId=dungeon;run.seed=seed;run.width=savedInt(s,"width",1,128);run.height=savedInt(s,"height",1,128);
        run.start=savedInt(s,"start",0,int(s.at("rooms").size())-1);
        run.boss=savedInt(s,"boss",0,int(s.at("rooms").size())-1);run.token=savedString(s,"token");
        run.generatorVersion=savedString(s,"generator_version");run.randomState=s.at("random_state");
        if(s.at("rooms").size()>size_t(run.width*run.height)||
            run.token!=std::to_string(dungeon)+":"+std::to_string(seed))
            throw std::runtime_error("Invalid saved dungeon layout dimensions");
        if(run.generatorVersion=="pcg32-world-v1"||run.generatorVersion=="pcg32-source-topology-v2") {
            RandomStreams state;state.restore(run.randomState);
            if(state.runSeed()!=run.seed) throw std::runtime_error("Saved generator RNG belongs to a different run");
        } else if(run.generatorVersion=="legacy-mt19937_64-v1") {
            if(!run.randomState.is_object()||run.randomState.value("algorithm",std::string())!="legacy-mt19937_64-v1"||
               savedUnsigned(run.randomState.at("seed"),std::numeric_limits<uint64_t>::max(),"legacy RNG seed")!=seed)
                throw std::runtime_error("Invalid saved legacy generator identity");
        } else throw std::runtime_error("Unsupported saved dungeon generator");
        std::set<std::pair<int,int>> positions;
        for(const auto &r:s.at("rooms")) {
            RunRoom room;room.x=savedInt(r,"x",0,run.width-1);room.y=savedInt(r,"y",0,run.height-1);
            room.mapId=savedInt(r,"map",0,std::numeric_limits<int>::max());room.path=savedString(r,"path");
            room.doors=savedInt(r,"doors",run.generatorVersion=="pcg32-source-topology-v2"?0:1,15);room.boss=savedBool(r,"boss");
            if(!r.at("candidates").is_array()||r.at("candidates").empty())throw std::runtime_error("Invalid saved candidates");
            std::set<int> candidateIds;
            for(const auto &candidate:r.at("candidates")) {
                const int id=int(savedUnsigned(candidate,std::numeric_limits<int>::max(),"candidate"));
                if(!candidateIds.insert(id).second)throw std::runtime_error("Duplicate saved candidate");
                room.candidates.push_back(id);
            }
            const auto map=c.maps.find(room.mapId);
            if(room.x<0||room.x>=run.width||room.y<0||room.y>=run.height||(room.doors<=0&&run.generatorVersion!="pcg32-source-topology-v2")||room.doors>15||
                !positions.insert({room.x,room.y}).second||map==c.maps.end()||(run.generatorVersion!="pcg32-source-topology-v2"&&map->second.dungeon!=dungeon)||
                map->second.path!=room.path||(run.generatorVersion!="pcg32-source-topology-v2"&&(map->second.special||map->second.boss!=room.boss||
                (room.doors&~map->second.allowedDoors)||(room.doors&map->second.requiredDoors)!=map->second.requiredDoors)))
                throw std::runtime_error("Saved dungeon MAP identity, topology or capability changed");
            if(room.candidates.empty()||std::find(room.candidates.begin(),room.candidates.end(),room.mapId)==room.candidates.end())
                throw std::runtime_error("Saved selected room is not in its preserved candidate set");
            for(int candidate:room.candidates) {
                const auto definition=c.maps.find(candidate);
                if(definition==c.maps.end()||(run.generatorVersion!="pcg32-source-topology-v2"&&(definition->second.dungeon!=dungeon||definition->second.special||
                    definition->second.boss!=room.boss||(room.doors&~definition->second.allowedDoors)||
                    (room.doors&definition->second.requiredDoors)!=definition->second.requiredDoors)))
                    throw std::runtime_error("Saved dungeon candidate dependency is incompatible");
            }
            run.rooms.push_back(std::move(room));
        }
    }
    if(run.start<0||run.start>=int(run.rooms.size())||run.boss<0||run.boss>=int(run.rooms.size())||
        (run.start==run.boss&&!(run.generatorVersion=="pcg32-source-topology-v2"&&run.rooms.size()==1))||!run.rooms[run.boss].boss||
        std::count_if(run.rooms.begin(),run.rooms.end(),[](const auto &r){return r.boss;})!=1)
        throw std::runtime_error("Invalid saved dungeon endpoints");
    std::set<int> reached{run.start};std::queue<int> queue;queue.push(run.start);
    while(!queue.empty()) {
        const int room=queue.front();queue.pop();run.current=room;
        for(int d=0;d<4;++d) if(run.room().doors&directionBit(Direction(d))) {
            const int target=run.destination(Direction(d));
            if(target<0) throw std::runtime_error("Saved dungeon contains a non-reciprocal door");
            if(reached.insert(target).second)queue.push(target);
        }
    }
    if(reached.size()!=run.rooms.size())throw std::runtime_error("Saved dungeon contains disconnected rooms");
    for(size_t i=0;i<run.rooms.size();++i) {
        run.rooms[i].visited=savedBool(s["rooms"][i],"visited");
        run.rooms[i].cleared=savedBool(s["rooms"][i],"cleared");
    }
    validateMazeSource(run,c);
    run.current=savedInt(s,"current",0,int(run.rooms.size())-1);
    if(!j.at("room_states").is_array())throw std::runtime_error("Invalid saved room states");
    next.roomStates=j.at("room_states").get<std::vector<Json>>();
    if(next.roomStates.size()!=run.rooms.size())throw std::runtime_error("Invalid saved room states");
    for(const auto &state:next.roomStates) {
        if(!state.is_null()&&!state.is_array())throw std::runtime_error("Saved room state must be null or an actor array");
        if(state.is_array())for(const auto &actor:state)if(!actor.is_object())throw std::runtime_error("Saved room actor must be an object");
    }
    next.objects=j.value("objects",Json::object()); next.drops=j.value("drops",Json::object());
    if(!next.objects.is_object()||!next.drops.is_object())throw std::runtime_error("Invalid saved object or drop ledger");
    *this=std::move(next);return true;
}
} // namespace dnf
