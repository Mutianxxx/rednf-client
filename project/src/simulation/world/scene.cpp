#include "dnf/scene.hpp"
#include "dnf/scene_tiles.hpp"
#include "dnf/combat.hpp"
#include <cmath>
namespace dnf {
static std::string relativePath(const std::string &parent, const std::string &child) {
    return normalize((std::filesystem::u8path(parent).parent_path() / std::filesystem::u8path(child)).generic_u8string());
}
int mapLayerOrder(const std::string &layer) {
    if (layer == "[distantback]") return -60;
    if (layer == "[middleback]") return -50;
    if (layer == "[closeback]") return -40;
    if (layer == "[bottom]") return -20;
    if (layer == "[normal]") return 0;
    if (layer == "[close]") return 100;
    throw std::runtime_error("Unknown source animation layer: " + layer);
}
bool mapBackgroundUpper(const std::string &order) {
    if (order == "[upper]" || order == "upper") return true;
    if (order == "[below]") return false;
    throw std::runtime_error("Unknown source background order: " + order);
}
void configureMapBackground(MapLayer &layer, const Script &map) {
    layer.order = mapLayerOrder(layer.sourceLayer) + (mapBackgroundUpper(layer.sourceOrder) ? 1 : -1);
    const auto tag = layer.sourceLayer == "[distantback]" ? "[far sight scroll]" :
                     layer.sourceLayer == "[close]" ? "[near sight scroll]" : "[middle sight scroll]";
    // closeback/bottom retain the previous middle-scroll policy. Their native
    // independent scroll selection is not established by the annotated sample.
    layer.scroll = map.number(tag, 100) / 100.0;
}
std::vector<MapDrawCommand> sceneDrawCommands(const Scene &scene, bool front) {
    std::vector<size_t> beforeTiles, afterTiles;
    for (size_t i = 0; i < scene.layers.size(); ++i) {
        const auto &layer = scene.layers[i];
        if (front) {
            if (layer.order > 0 && !(layer.background && layer.sourceLayer == "[close]" &&
                                    !mapBackgroundUpper(layer.sourceOrder))) afterTiles.push_back(i);
        } else if (layer.order <= -49 || (layer.background && layer.sourceLayer == "[close]" &&
                                         !mapBackgroundUpper(layer.sourceOrder))) {
            beforeTiles.push_back(i);
        } else if (layer.order < 0) afterTiles.push_back(i);
    }
    const auto byOrder = [&](size_t a, size_t b) { return scene.layers[a].order < scene.layers[b].order; };
    std::stable_sort(beforeTiles.begin(), beforeTiles.end(), byOrder);
    std::stable_sort(afterTiles.begin(), afterTiles.end(), byOrder);
    std::vector<MapDrawCommand> result;
    for (auto index : beforeTiles) result.push_back({MapDrawCommand::Kind::Animation, index});
    if (!front) for (size_t i = 0; i < scene.tiles.size(); ++i) result.push_back({MapDrawCommand::Kind::Tile, i});
    for (auto index : afterTiles) result.push_back({MapDrawCommand::Kind::Animation, index});
    return result;
}
void Scene::load(Pvf &p, Assets &assets, const std::string &name_, const std::string &run, const std::string &room) {
    path = name_;
    script = p.script(path);
    name = script.text("[map name]", path);
    bg = int(script.number("[background pos]", 80));
    layers.clear();
    npcs.clear();
    townExits.clear();
    objects.clear();
    objectSystem.clear();
    objectClockTick = -1;
    blockedRects.clear();
    tiles.clear();
    sourceTileVisuals.clear();
    walkRects.clear();
    issues = Json::array();
    tileGrids = Json::array();
    auto tileReceipt=loadSceneSourceTiles(p,assets,*this);
    for(auto &diagnostic:tileReceipt.diagnostics)issues.push_back(std::move(diagnostic));
    issues.push_back({{"kind","source_tile_load_receipt"},{"complete",tileReceipt.complete},
        {"columns_resolved",tileReceipt.columnsResolved},{"records",std::move(tileReceipt.records)}});
    if(!tileReceipt.complete)throw std::runtime_error("Source MAP tile dependency/placement unavailable: "+path+": "+issues.dump());
    if (width == 0)
        width = 896;
    auto vr = script.values("[virtual movable area]");
    if (vr.size() >= 4) {
        walkRects.clear();
        for (size_t i = 0; i + 3 < vr.size(); i += 4)
            walkRects.push_back({vr[i].get<double>(), vr[i + 1].get<double>() + bg, vr[i + 2].get<double>(),
                                 vr[i + 3].get<double>()});
    }
    for (const auto &field : script.fields) if (field.tag == "[town movable area]") {
        if (field.values.size() % 6 != 0)
            throw std::runtime_error("Malformed MAP town movable area: " + path);
        for (size_t i = 0; i < field.values.size(); i += 6) {
            TownExit exit;
            for (size_t k = 0; k < 6; ++k) {
                if (!field.values[i + k].is_number()) throw std::runtime_error("Invalid MAP town movable area: " + path);
                exit.raw.push_back(field.values[i + k]);
            }
            exit.x = field.values[i]; exit.y = field.values[i + 1].get<double>() + bg;
            exit.width = field.values[i + 2]; exit.height = field.values[i + 3];
            exit.town = field.values[i + 4]; exit.area = field.values[i + 5]; exit.offset = field.offset;
            if (exit.width <= 0 || exit.height <= 0) throw std::runtime_error("Empty MAP town transition: " + path);
            if (std::none_of(townExits.begin(), townExits.end(), [&](const TownExit &old) { return old.raw == exit.raw; }))
                townExits.push_back(std::move(exit));
        }
    }
    auto values = script.values("[animation]");
    for (size_t i = 0; i + 4 < values.size(); i += 5) {
        if (!values[i].is_string() || !values[i + 1].is_string())
            continue;
        auto layer = values[i + 1].get<std::string>();
        int order = mapLayerOrder(layer);
        layers.push_back({relativePath(path, values[i]), values[i + 2].get<double>(),
                          values[i + 3].get<double>() + bg - values[i + 4].get<double>(), order, 1});
        layers.back().depthY = values[i + 3].get<double>() + bg;
        layers.back().sourceLayer = layer;
    }
    MapLayer background;
    for (auto &f : script.fields) {
        if (f.tag == "[ani info]") {
            background = MapLayer{};
            background.background = true;
            background.y = bg;
        }
        if (f.tag == "[filename]" && !f.values.empty())
            background.animation = relativePath(path, f.values[0]);
        if (f.tag == "[layer]" && !f.values.empty())
            background.sourceLayer = f.values[0];
        if (f.tag == "[order]" && !f.values.empty())
            background.sourceOrder = f.values[0];
        if (f.tag == "[loop y axis]" && !f.values.empty())
            background.loopY = f.values[0] == 1;
        if (f.tag == "[screen pos]" && f.values.size() >= 2) {
            background.screenPosition = true;
            background.x = f.values[0].get<double>();
            background.y = f.values[1].get<double>();
        }
        if (f.tag == "[/ani info]" && !background.animation.empty()) {
            configureMapBackground(background, script);
            auto ani = assets.animation(background.animation);
            if (!ani->frames.empty()) {
                auto &frame = ani->frames.front();
                auto image = assets.pixels(frame.image, frame.imageFrame);
                background.repeatWidth = image.logicalWidth;
                background.repeatHeight = image.logicalHeight;
            }
            layers.push_back(background);
        }
    }
    // Resolve every source NPC through its original ID list. Deduplicate only
    // exact repeated placements, not all instances sharing an NPC ID.
    auto npcList = p.script("npc/npc.lst").tokens;
    auto placements = script.values("[NPC]");
    std::vector<Json> seen;
    for (size_t i = 0; i + 4 < placements.size(); i += 5) {
        Json placement = Json::array();
        for (size_t k = 0; k < 5; ++k) placement.push_back(placements[i + k]);
        if (std::find(seen.begin(), seen.end(), placement) != seen.end()) continue;
        seen.push_back(placement);
        MapNpc npc;
        npc.id = placements[i];
        npc.direction = placements[i + 1] == "[left]" ? -1 : 1;
        npc.x = placements[i + 2];
        npc.y = placements[i + 3].get<double>() + bg;
        npc.z = placements[i + 4];
        for (size_t k = 0; k + 1 < npcList.size(); k += 2)
            if (npcList[k]["value"] == npc.id) {
                npc.source = relativePath("npc/npc.lst", npcList[k + 1]["value"]);
                break;
            }
        if (npc.source.empty()) {
            issues.push_back({{"kind", "unresolved NPC ID"}, {"id", npc.id}});
            continue;
        }
        auto data = p.script(npc.source);
        auto animation = data.text("[field animation]");
        if (!animation.empty()) npc.animation = relativePath(npc.source, animation);
        // A decoration ANI can be a grade sheet instead of a motion: one IMG,
        // uniform frame delays, sequential image frames and no source loop
        // global. Storage.ani is the reviewed case; its seven frames are iron
        // through gold storage tiers. Looping that sheet made the chest flicker
        // across every tier, so bind one stable frame and keep the unresolved
        // native grade selection as a diagnostic instead of inventing a mapping.
        if (!npc.animation.empty()) {
            try {
                const auto clip = assets.animation(npc.animation);
                const auto &first = clip->frames.front();
                bool gradeSheet = clip->frames.size() > 1 && !clip->globals.value("0", false);
                for (size_t f = 0; gradeSheet && f < clip->frames.size(); ++f)
                    gradeSheet = clip->frames[f].image == first.image &&
                                 clip->frames[f].duration == first.duration &&
                                 clip->frames[f].imageFrame == int(f);
                if (gradeSheet) {
                    npc.staticFrame = 0;
                    issues.push_back({{"kind", "npc_grade_sheet_animation"}, {"id", npc.id},
                        {"source", npc.animation}, {"frames", clip->frames.size()},
                        {"policy", "hold frame 0; the native grade-to-frame selection is unrecovered"}});
                }
            } catch (const std::exception &) {
                // Renderer keeps ownership of animation load diagnostics.
            }
        }
        npc.name = data.text("[field name]", data.text("[name]"));
        // Storage's source field-name is an ANI used as a dynamic plaque, not
        // display text. Its full grade-dependent plaque controller is separate.
        auto fieldName = npc.name;
        std::transform(fieldName.begin(), fieldName.end(), fieldName.begin(),
                       [](unsigned char c) { return c >= 'A' && c <= 'Z' ? char(c + 32) : char(c); });
        if (fieldName.size() >= 4 && fieldName.substr(fieldName.size() - 4) == ".ani") npc.name = data.text("[name]");
        if (npc.name == "[storage]") npc.name = "金库";
        npc.voice = data.text("[field wav]");
        npc.visibleOnDungeonClear = data.number("[visible on dungeon clear]", 0) != 0;
        npc.visible = !npc.visibleOnDungeonClear;
        npc.sourcePosition = {placements[i + 2].get<double>(), placements[i + 3].get<double>(), placements[i + 4].get<double>()};
        if (npc.visibleOnDungeonClear && npc.x == 0 && npc.y == bg)
            issues.push_back({{"kind", "clear NPC uses placeholder placement; exact PC spawn rule unverified"},
                              {"id", npc.id}, {"source", npc.source}, {"source_xyz", {0, 0, npc.z}},
                              {"native_policy", "after dungeon completion, once near the defeated boss on safe walkable ground"}});
        npcs.push_back(npc);
    }
    ObjectCatalog objectCatalog(p, assets);
    const auto mapRaw = p.read(path);
    for (auto placement : objectPlacements(script, run, room, bg, &issues, &mapRaw)) {
        auto definition = objectCatalog.definition(placement.id);
        objectSystem.add(std::move(placement), definition, currentObjectBehavior(*definition));
    }
    refreshObjectViews();
    std::stable_sort(layers.begin(), layers.end(), [](auto &a, auto &b) { return a.order < b.order; });
}
const TownExit *Scene::townExitAt(double x, double y) const {
    for (const auto &exit : townExits) if (exit.contains(x, y)) return &exit;
    return nullptr;
}
std::array<double, 2> Scene::townArrivalFrom(int town, int area) const {
    for (const auto &exit : townExits) if (exit.town == town && exit.area == area) {
        double x = exit.x + exit.width / 2, y = exit.y + exit.height / 2;
        // Re-entry sits just inside the reciprocal source rectangle. This margin
        // is native input policy, not a modification to the MAP transition data.
        if (exit.width < exit.height) x += (x < width / 2.0 ? 1 : -1) * (exit.width / 2 + 32);
        else {
            double top = 1e9, bottom = -1e9;
            for (const auto &r : walkRects) { top = std::min(top, r[1]); bottom = std::max(bottom, r[1] + r[3]); }
            y += (y < (top + bottom) / 2 ? 1 : -1) * (exit.height / 2 + 32);
        }
        return {x, y};
    }
    return {80, 340};
}
void Scene::updateNpcs(const World &world, bool dungeonCleared) {
    for (auto &npc : npcs) if (npc.visibleOnDungeonClear) {
        npc.visible = dungeonCleared;
        if (!npc.visible || npc.generatedPlacement || npc.sourcePosition[0] != 0 || npc.sourcePosition[1] != 0) continue;
        double x = world.player.x + 100 * world.player.dir, y = world.player.y;
        for (const auto &actor : world.monsters) if (actor.boss && actor.dead) { x = actor.x + 100; y = actor.y; break; }
        const auto point = world.nearestWalkable(x, y);
        npc.x = point[0]; npc.y = point[1]; npc.generatedPlacement = true; npc.appearedAt = world.nowMs();
    }
}
void Scene::rebuildObstacles(World &world) const {
    world.blockedRects.clear();
    for (const auto &o : objectSystem.activeObstacles())
        world.blockedRects.push_back({o.x, o.y, o.width, o.height});
}
void Scene::updateObjects(World &world, Pvf &p, Assets &assets) {
    (void)p; (void)assets;
    // World invokes this after every fixed 60 Hz tick. Derive microseconds
    // from tick boundaries so render cadence and millisecond truncation cannot
    // alter object animation or reaction lifetimes.
    const auto previousTick = objectClockTick < 0 ? std::max<int64_t>(0, world.tick - 1) : objectClockTick;
    if (world.tick > previousTick) {
        const auto previousUs = previousTick * 1000000 / 60;
        const auto currentUs = world.tick * 1000000 / 60;
        objectSystem.advance(currentUs - previousUs);
        objectClockTick = world.tick;
    }
    for (const auto &volume : world.attackVolumes) {
        ObjectAttack attack;
        attack.owner = 0; attack.serial = volume.serial; attack.pulse = volume.pulse;
        attack.volume = combatBox(volume.box, volume.x, volume.y, volume.z, volume.direction);
        // Damage amounts and native acceptance remain class/factory contracts.
        // The scoped legacy candidate policy counts distinct contacts only.
        attack.direction = volume.direction;
        for (const auto &object : objectSystem.instances()) {
            attack.missed=false; attack.damageTrace=Json::object();
            if (!objectSystem.acceptsContact(object.placement.identity,attack)) continue;
            attack.damage = object.definition->explicitHpMax ? volume.damage : 1;
            if (world.usesSourceGrowth() && object.definition->explicitHpMax) {
                const auto result=world.resolveObjectContact(volume,object);
                if (!result.usable()) {
                    objectSystem.diagnostics.push_back({{"kind","object_damage_blocked"},
                        {"object",object.placement.identity.json()},{"result",result.snapshot()}});
                    continue;
                }
                attack.damage=*result.hpDamage;
                attack.missed=result.missed;
                attack.damageTrace=result.snapshot();
            }
            objectSystem.contact(object.placement.identity, attack);
        }
    }
    // Presentation events have no reward side effects. Payload events remain
    // durable in the object system until a real payload consumer acknowledges.
    std::vector<std::string> acknowledged;
    for (const auto &event : objectSystem.pendingEvents()) {
        if (event.kind == "payload" || event.kind == "drop" || event.kind == "spawn" || event.kind == "trap") continue;
        const auto *instance = objectSystem.find(event.object);
        if (!instance) continue;
        if(event.kind=="hit" && !instance->definition->hitSound.empty())
            world.events.push_back({world.tick,"sound",instance->definition->hitSound,instance->placement.id});
        if(event.kind=="destroyed" && !instance->definition->destroySound.empty())
            world.events.push_back({world.tick,"sound",instance->definition->destroySound,instance->placement.id});
        world.events.push_back({world.tick, "object_" + event.kind, instance->definition->name,
                                instance->placement.id, 0, 0});
        acknowledged.push_back(event.key);
    }
    for (const auto &key : acknowledged) objectSystem.acknowledge(key);
    refreshObjectViews();
    rebuildObstacles(world);
}
Json Scene::saveObjects(int64_t now) const {
    (void)now;
    return objectSystem.save();
}
void Scene::restoreObjects(const Json &saved, int64_t now) {
    if (saved.is_object()) objectSystem.restore(saved);
    else if (saved.is_array()) {
        // Old records had no stable source identity. Only an unambiguous full
        // position match is migrated; raw legacy HP is retained as unknown.
        std::set<std::string> restored;
        for (const auto &entry : saved) {
            if (!entry.is_object()) continue;
            std::vector<ObjectIdentity> matches;
            for (const auto &object : objectSystem.instances()) {
                const auto &placement = object.placement;
                if (placement.id == entry.value("id", -1) &&
                    std::abs(placement.x - entry.value("x", 0.0)) < .01 &&
                    std::abs(placement.y - entry.value("y", 0.0)) < .01 &&
                    std::abs(placement.z - entry.value("z", 0.0)) < .01)
                    matches.push_back(placement.identity);
            }
            if (matches.size() != 1 || !restored.insert(matches.front().key()).second) {
                issues.push_back({{"kind", "ambiguous legacy object migration"}, {"record", entry}});
                continue;
            }
            auto &instance = *objectSystem.find(matches.front());
            instance.unknown["legacy_save"] = entry;
            if (entry.value("destroyed", false)) {
                // Preserve removal already accepted by an older candidate;
                // migration never dispatches payloads or repeats rewards.
                instance.state = ObjectState::Destroyed;
                instance.collisionEnabled = false;
                instance.actionAgeUs = std::max<int64_t>(0, entry.value("age", int64_t(0))) * 1000;
            }
        }
    }
    // Player attacks and effects have already ended in World::changeScene.
    // Their old serials can be reused in a fresh process; they no longer
    // suppress new contacts. Payload transactions stay independent.
    objectSystem.retireOwnerAttacks(0);
    objectClockTick = std::max<int64_t>(0, (now * 60 + 500) / 1000);
    refreshObjectViews();
}
void Scene::refreshObjectViews() {
    // Scene preparation uses this same obstacle list before publishing World.
    // Restored destroyed objects must not retain their old blocking footprint.
    blockedRects.clear();
    for (const auto &obstacle : objectSystem.activeObstacles())
        blockedRects.push_back({obstacle.x, obstacle.y, obstacle.width, obstacle.height});
    objects.clear();
    for (const auto &instance : objectSystem.instances()) {
        const auto &placement = instance.placement;
        const auto &definition = *instance.definition;
        MapObject view;
        view.identity = placement.identity; view.id = placement.id;
        view.x = placement.x; view.y = placement.y; view.z = placement.z;
        view.special = placement.special; view.raw = placement.raw; view.payload = placement.payload;
        view.source = definition.source; view.name = definition.name; view.layer = definition.layer;
        view.passType = definition.passType; view.width = int(definition.width); view.height = int(definition.height);
        view.destroyed = instance.state == ObjectState::Destroyed || instance.state == ObjectState::Removed;
        view.breakable = instance.durability.has_value();
        if (const auto motion = instance.motion()) view.animation = motion->path;
        view.animationMs = instance.actionAgeUs / 1000; view.direction = instance.direction;
        view.loop = instance.state == ObjectState::Intact;
        objects.push_back(std::move(view));
        for(const auto &particle:instance.visualParticles) {
            MapObject visual;
            visual.identity=placement.identity;visual.id=placement.id;
            visual.x=particle.position[0];visual.y=particle.position[1];visual.z=particle.position[2];
            visual.source=particle.source;visual.animation=particle.animation;visual.name="source particle";
            visual.layer=definition.layer;visual.loop=false;visual.direction=1;visual.animationMs=particle.ageUs/1000;
            objects.push_back(std::move(visual));
        }
    }
}
} // namespace dnf
