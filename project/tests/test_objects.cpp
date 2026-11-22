#include "dnf/objects.hpp"
#include "dnf/combat.hpp"
#include "dnf/region.hpp"
#include "dnf/scene.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
Json runObjectSystemTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array();
    auto check = [&](bool condition, const std::string &name) {
        if (!condition) throw std::runtime_error("Object system: " + name);
        checks.push_back(name);
    };
    ObjectCatalog catalog(pvf, assets);
    const auto barrel = catalog.definition(221);
    const auto tree = catalog.definition(223);
    const auto grass = catalog.definition(243);
    const auto light = catalog.definition(5);
    const auto barrelBehavior = currentObjectBehavior(*barrel);
    check(barrel->intData.size() == 7 && barrel->intData[5] == 30,
          "OBJ int-data order is retained without assigning index 5 to HP");
    check(!barrel->explicitHpMax && barrelBehavior.durability == 2 && !barrelBehavior.reconstructedHitShapeFallback,
          "Barrel two-hit durability remains a local candidate while contact uses the actual source hurt box");
    check(tree->motion("[etc motion]", 0) && !currentObjectBehavior(*tree).durability,
          "Tree reaction animation is independent from an unknown destruction threshold");
    check(grass->motion("[etc motion]", 1) && grass->motion("[etc motion]", 2),
          "Grass source keeps its separate directional motion slots");
    check(currentObjectBehavior(*grass).durability == 1 &&
          currentObjectBehavior(*grass).destructionTag == "[etc motion]" &&
          currentObjectBehavior(*grass).removeAfterDestroy,
          "User preview grass policy destroys on one source-box contact and retains source motion slots");
    check(light->script.values("[string data]").size() == 1 &&
          light->script.values("[string data]")[0] == "Particle/rayGround.ptl",
          "Light factory retains the original PTL source reference");

    ObjectDefinition grassFixture = *grass;
    auto hitAnimation = std::make_shared<Animation>();
    AniFrame hitFrame;
    hitFrame.boxes.push_back({14, 0, 0, 0, 10, 10, 10});
    hitAnimation->frames.push_back(hitFrame);
    hitAnimation->duration = 100;
    grassFixture.motions.erase(std::remove_if(grassFixture.motions.begin(), grassFixture.motions.end(),
        [](const ObjectMotion &motion) { return motion.tag == "[basic motion]" && motion.slot == 0; }),
        grassFixture.motions.end());
    grassFixture.motions.push_back({"[basic motion]", "test/grass-hit.ani", 0, 0, hitAnimation, {}});
    ObjectPlacement grassPlacement;
    grassPlacement.id = grass->id;
    grassPlacement.identity = {"unit-run", "grass-room", "fixture.map", 0, 0};
    auto grassBehavior = currentObjectBehavior(*grass);
    // Keep coverage of the source directional consumer independently from the
    // user preview's one-hit destruction policy.
    grassBehavior.durability.reset();
    grassBehavior.directionalReaction = true;
    grassBehavior.reactionTag = "[etc motion]";
    grassBehavior.reactionLeftSlot = 1;
    grassBehavior.reactionRightSlot = 2;
    grassBehavior.evidence = "directional source-motion consumer fixture";
    ObjectSystem grassSystem;
    grassSystem.add(grassPlacement, std::make_shared<ObjectDefinition>(grassFixture), grassBehavior);
    ObjectAttack grassAttack;
    grassAttack.owner = 1; grassAttack.serial = 1; grassAttack.direction = -1;
    grassAttack.volume = {-5, -5, 0, 10, 10, 10};
    check(grassSystem.contact(grassPlacement.identity, grassAttack) &&
          grassSystem.find(grassPlacement.identity)->motionSlot == 1,
          "Leftward contact chooses the preserved left-reaction source slot");
    grassSystem.clear();
    grassSystem.add(grassPlacement, std::make_shared<ObjectDefinition>(grassFixture), grassBehavior);
    grassAttack.serial = 2; grassAttack.direction = 1;
    check(grassSystem.contact(grassPlacement.identity, grassAttack) &&
          grassSystem.find(grassPlacement.identity)->motionSlot == 2,
          "Rightward contact chooses the preserved right-reaction source slot");

    const auto map = pvf.script("map/lorien/6.map");
    const auto mapRaw = pvf.read("map/lorien/6.map");
    Json parseDiagnostics = Json::array();
    const auto placements = objectPlacements(map, "unit-run", "room-0", 80, &parseDiagnostics, &mapRaw);
    check(parseDiagnostics.empty(), "MAP passive-object records parse without shape loss");
    check(placements.size() > 8 && !placements.front().sourceBytes.empty(),
          "MAP record count and exact record source bytes are retained");
    const auto sourceBarrel = std::find_if(placements.begin(), placements.end(),
        [](const ObjectPlacement &p) { return p.id == 221; });
    check(sourceBarrel != placements.end(), "Lorien source MAP contains its registered barrel");
    const auto first = *sourceBarrel;

    ObjectSystem sourceContact;
    for (const auto id : {221, 222, 223, 224, 243, 244}) {
        const auto definition = catalog.definition(id);
        ObjectPlacement placement;
        placement.id = id;
        placement.identity = {"source-hurtbox-run", "room", "fixture.map", uint64_t(id), 0};
        placement.x = 500; placement.y = 300; placement.z = 40;
        auto &instance = sourceContact.add(placement, definition, currentObjectBehavior(*definition));
        const auto *motion = instance.motion();
        check(motion && motion->animation && !motion->animation->frames.empty(),
              "Source object has a decoded idle animation: " + std::to_string(id));
        const auto &frame = motion->animation->frames.front();
        const auto hurt = std::find_if(frame.boxes.begin(),frame.boxes.end(),
            [](const Box &box) { return box.type == 14; });
        check(hurt != frame.boxes.end() && instance.damageBoxes().size() > 0,
              "Source type-14 hurt boxes reach object contacts: " + std::to_string(id));
        ObjectAttack sourceAttack;
        sourceAttack.owner = 4; sourceAttack.serial = 1;
        sourceAttack.volume = combatBox(*hurt, placement.x, placement.y, placement.z, 1);
        auto displaced = sourceAttack;
        displaced.volume.z += sourceAttack.volume.d + 1;
        check(!sourceContact.contact(placement.identity,displaced),
              "Source object rejects attack above its full Z extent: " + std::to_string(id));
        check(sourceContact.contact(placement.identity,sourceAttack),
              "Actual source hurt box accepts a matching attack volume: " + std::to_string(id));
    }

    RegionCatalog regions(pvf, assets);
    size_t legalPlacementCount = 0, legalLightCount = 0;
    Json legalMapCounts = Json::array();
    std::set<std::string> mapPaths;
    ObjectSystem allLegalObjects;
    for (const auto &[id, mapDefinition] : regions.maps) {
        if (mapDefinition.special || mapDefinition.path == "map/lorien/7.map" ||
            (mapDefinition.dungeon != 1 && mapDefinition.dungeon != 2)) continue;
        check(mapPaths.insert(mapDefinition.path).second, "Legal MAP paths are unique in the source registry");
        const auto raw = pvf.read(mapDefinition.path);
        Json diagnostics = Json::array();
        const auto mapPlacements = objectPlacements(mapDefinition.source, "baseline-run", std::to_string(id),
            mapDefinition.source.number("[background pos]", 80), &diagnostics, &raw);
        check(diagnostics.empty(), "Legal MAP object records parse without loss: " + mapDefinition.path);
        for (const auto &placement : mapPlacements) {
            if (placement.sourceBytes.empty())
                throw std::runtime_error("Object system: missing MAP record bytes in " + mapDefinition.path);
            const auto definition = catalog.definition(placement.id);
            if (definition->raw.empty())
                throw std::runtime_error("Object system: empty OBJ source bytes for ID " + std::to_string(placement.id));
            const auto offset = size_t(placement.identity.fieldOffset);
            if (offset > raw.size() || placement.sourceBytes.size() > raw.size() - offset ||
                !std::equal(placement.sourceBytes.begin(), placement.sourceBytes.end(), raw.begin() + offset))
                throw std::runtime_error("Object system: retained MAP record bytes differ from source in " + mapDefinition.path);
            allLegalObjects.add(placement, definition, currentObjectBehavior(*definition));
            ++legalPlacementCount;
            if (placement.id == 5 || placement.id == 6) ++legalLightCount;
        }
        legalMapCounts.push_back({{"id", id}, {"path", mapDefinition.path}, {"placements", mapPlacements.size()}});
    }
    check(mapPaths.size() == 33, "All 33 DGN-legal ordinary Lorien MAP variants are enumerated");
    check(legalPlacementCount == 682, "All 682 DGN-legal MAP object placements are retained");
    check(legalLightCount == 198, "All 198 DGN-legal light factory placements are retained");
    allLegalObjects.advance(433333);
    const auto allLegalSave = Json::parse(allLegalObjects.save().dump());
    ObjectSystem allLegalReload;
    for (const auto &object : allLegalObjects.instances())
        allLegalReload.add(object.placement, object.definition, object.behavior);
    allLegalReload.restore(allLegalSave);
    check(allLegalReload.save() == allLegalSave,
          "All 682 legal placements survive a JSON roundtrip with source identity, relative clocks and random state");
    check(allLegalReload.activeObstacles().size() == allLegalObjects.activeObstacles().size(),
          "All legal-map movement obstacles survive source reconstruction and reload");

    ObjectSystem system;
    auto &added = system.add(first, barrel, barrelBehavior);
    check(added.placement.identity == first.identity, "Instance identity retains room, MAP record offset and ordinal");
    auto duplicate = first;
    duplicate.identity.recordOrdinal += 1;
    system.add(duplicate, barrel, barrelBehavior);
    check(system.instances().size() == 2 && system.instances()[0].placement.identity != system.instances()[1].placement.identity,
          "Identical OBJ IDs and positions do not alias instance identity");
    system.clear();
    system.add(first, barrel, barrelBehavior);
    check(system.activeObstacles().size() == 1, "Source pass type produces an independent active obstacle");

    ObjectAttack attack;
    attack.owner = 7; attack.serial = 10; attack.damage = 1;
    attack.volume = {first.x - 1, first.y - 2, first.z, 4, 4, 100};
    check(system.contact(first.identity, attack) && system.find(first.identity)->durability == 1,
          "First distinct attack reaches the scoped barrel candidate");
    check(!system.contact(first.identity, attack) && system.find(first.identity)->durability == 1,
          "One attack identity cannot damage the same object more than once");

    auto pulsePlacement = first;
    pulsePlacement.identity.recordOrdinal += 2000;
    ObjectSystem pulseSystem;
    pulseSystem.add(pulsePlacement, barrel, barrelBehavior);
    ObjectAttack pulseAttack = attack;
    pulseAttack.serial = 12;
    pulseAttack.pulse = 0;
    check(pulseSystem.contact(pulsePlacement.identity, pulseAttack),
          "First pulse of a persistent attack contacts once");
    pulseAttack.pulse = 1;
    check(pulseSystem.contact(pulsePlacement.identity, pulseAttack),
          "A later pulse has a distinct deduplication identity");

    auto saveAfterHit = system.save();
    ObjectSystem restored;
    restored.add(first, barrel, barrelBehavior);
    restored.restore(saveAfterHit);
    check(restored.find(first.identity)->durability == 1 && !restored.find(first.identity)->hits.empty(),
          "Reload preserves the current candidate state and dedup registration");
    attack.serial = 11;
    check(restored.contact(first.identity, attack) && restored.find(first.identity)->state == ObjectState::Destroyed,
          "A later distinct barrel hit finishes the candidate state");
    check(restored.activeObstacles().empty(), "Destroying a source barrel removes its movement obstacle");

    auto fixtureDefinition = std::make_shared<ObjectDefinition>(*barrel);
    auto animation = std::make_shared<Animation>();
    AniFrame frame;
    frame.boxes.push_back({14, 0, 0, 0, 10, 10, 10});
    animation->frames.push_back(frame);
    animation->duration = 100;
    fixtureDefinition->motions.erase(std::remove_if(fixtureDefinition->motions.begin(),fixtureDefinition->motions.end(),
        [](const ObjectMotion &motion){return motion.tag=="[basic motion]"&&motion.slot==0;}),fixtureDefinition->motions.end());
    fixtureDefinition->motions.push_back({"[basic motion]", "test/source-box.ani", 0, 0, animation, {}});
    auto reactionAnimation = std::make_shared<Animation>();
    reactionAnimation->frames.push_back(frame);
    reactionAnimation->duration = 125;
    fixtureDefinition->motions.erase(std::remove_if(fixtureDefinition->motions.begin(),fixtureDefinition->motions.end(),
        [](const ObjectMotion &motion){return motion.tag=="[damage motion]"&&motion.slot==0;}),fixtureDefinition->motions.end());
    fixtureDefinition->motions.push_back({"[damage motion]", "test/reaction.ani", 0, 0, reactionAnimation, {}});
    auto fixturePlacement = first;
    fixturePlacement.identity.recordOrdinal += 1000;
    ObjectBehavior fixtureBehavior;
    fixtureBehavior.reactionTag = "[damage motion]";
    fixtureBehavior.durability = 2;
    fixtureBehavior.evidence = "test fixture only";
    ObjectSystem collision;
    collision.add(fixturePlacement, fixtureDefinition, fixtureBehavior);
    ObjectAttack edge = attack;
    edge.owner = 9; edge.serial = 20;
    edge.volume = {first.x - 11, first.y - 5, first.z, 10, 10, 10};
    check(!collision.contact(fixturePlacement.identity, edge), "Separated X ANI attack and object hurt boxes do not contact");
    edge.volume = {first.x - 5, first.y - 11, first.z, 10, 10, 10};
    check(!collision.contact(fixturePlacement.identity, edge), "Separated Y ANI attack and object hurt boxes do not contact");
    edge.volume = {first.x - 5, first.y - 5, first.z + 11, 10, 10, 10};
    check(!collision.contact(fixturePlacement.identity, edge), "Separated Z ANI attack and object hurt boxes do not contact");
    edge.volume = {first.x - 10, first.y - 5, first.z, 10, 10, 10};
    check(collision.contact(fixturePlacement.identity, edge), "Current ANI type-14 XYZ box accepts an edge contact");
    check(collision.pendingEvents().front().kind == "hit", "Object hit is emitted as an isolated event, not a monster reward");
    collision.find(fixturePlacement.identity)->unknown["future_field"] = Json::array({1, 2, 3});
    const auto collisionSave = collision.save();
    ObjectSystem collisionReload;
    collisionReload.add(fixturePlacement, fixtureDefinition, fixtureBehavior);
    collisionReload.restore(collisionSave);
    check(collisionReload.find(fixturePlacement.identity)->unknown["future_field"] == Json::array({1, 2, 3}),
          "Unknown per-instance fields survive serialization");

    auto futureSave = collisionSave;
    futureSave["future_root"] = {{"version", 7}, {"bytes", {0, 255, 14}}};
    futureSave["instances"][0]["future_instance"] = {"preserve", 91};
    futureSave["instances"][0]["identity"]["future_identity"] = "original-literal";
    futureSave["pending_events"][0]["future_event"] = {{"source_offset", 99}};
    futureSave["pending_events"][0]["identity"]["future_identity"] = "event-identity";
    auto unmatched = futureSave["instances"][0];
    unmatched["identity"]["record_ordinal"] = 999999;
    futureSave["instances"].push_back(unmatched);
    ObjectSystem futureReload;
    futureReload.add(fixturePlacement, fixtureDefinition, fixtureBehavior);
    futureReload.restore(futureSave);
    check(futureReload.save() == futureSave,
          "Unknown root, instance, identity and event fields plus unmatched source records roundtrip without loss");
    check(futureReload.instances().size() == 1 && !futureReload.diagnostics.empty(),
          "Unmatched save records stay archived with a diagnostic and cannot create runtime objects");
    futureReload.clear();
    futureReload.add(fixturePlacement, fixtureDefinition, fixtureBehavior);
    check(!futureReload.save().contains("future_root") && futureReload.save()["instances"].size() == 1,
          "Clearing a room drops retained save fields before a distinct room is loaded");

    check(collision.consumePayload(fixturePlacement.identity, "map-payload:0", "payload", {{"raw", {3, 4, 5}}}),
          "Explicit payload scheduling emits an object event");
    const auto payloadSave = collision.save();
    ObjectSystem payloadReload;
    payloadReload.add(fixturePlacement, fixtureDefinition, fixtureBehavior);
    payloadReload.restore(payloadSave);
    check(!payloadReload.consumePayload(fixturePlacement.identity, "map-payload:0", "payload", {{"raw", {3, 4, 5}}}),
          "Consumed payload token cannot be scheduled twice after reload");
    const auto before = payloadReload.find(fixturePlacement.identity)->ageUs;
    payloadReload.advance(16667);
    check(payloadReload.find(fixturePlacement.identity)->ageUs == before + 16667,
          "Instance clock advances in fixed-tick microseconds");
    check(payloadReload.pendingEvents().size() == collision.pendingEvents().size(),
          "Unacknowledged object events survive a save and restore");

    ObjectBehavior reactionBehavior;
    reactionBehavior.reactionTag = "[damage motion]";
    reactionBehavior.destructionTag.clear();
    auto fixedTickTrace = [&](const std::vector<int64_t> &renderDeltas) {
        Scene scene;
        World world(pvf, assets);
        world.freezeAi = true;
        auto placement = fixturePlacement;
        placement.identity.run = "render-cadence-run";
        placement.identity.recordOrdinal += 4000;
        scene.objectSystem.add(placement, fixtureDefinition, reactionBehavior);
        bool exactRoundtrip = false, preservedPayload = false;
        Json stateTrace = Json::array(), checkpoint = Json::object();
        world.setObjectTick([&](World &simulation) {
            // Two sustained attacks alternate in the same overlap. Neither may
            // cause repeated damage by evicting the other's hit registration.
            AttackVolume firstVolume;
            firstVolume.serial = 700;
            firstVolume.x = placement.x; firstVolume.y = placement.y; firstVolume.z = placement.z;
            firstVolume.direction = 1; firstVolume.damage = 1;
            firstVolume.box = {15, -5, -5, 0, 10, 10, 10};
            simulation.attackVolumes = {firstVolume};
            if (simulation.tick >= 2) {
                firstVolume.serial = 701;
                simulation.attackVolumes.push_back(firstVolume);
            }
            scene.updateObjects(simulation, pvf, assets);
            if (simulation.tick == 73)
                scene.objectSystem.consumePayload(placement.identity, "fixture:drop0", "drop", {{"item", 10}});
            if (simulation.tick == 90) {
                const auto saved = Json::parse(scene.saveObjects(simulation.nowMs()).dump());
                ObjectSystem reloaded;
                reloaded.add(placement, fixtureDefinition, reactionBehavior);
                reloaded.restore(saved);
                exactRoundtrip = reloaded.save() == saved;
                preservedPayload = !reloaded.consumePayload(placement.identity, "fixture:drop0", "drop", {{"item", 10}});
                scene.objectSystem = std::move(reloaded);
                checkpoint = saved;
            }
            const auto &instance = scene.objectSystem.instances().front();
            stateTrace.push_back({{"tick", simulation.tick}, {"age_us", instance.ageUs},
                {"action_age_us", instance.actionAgeUs}, {"state", int(instance.state)},
                {"hits", instance.hits.size()}, {"pending_events", scene.objectSystem.pendingEvents().size()},
                {"obstacles", scene.objectSystem.activeObstacles().size()}});
        });
        for (const auto elapsedNs : renderDeltas) world.advance(elapsedNs);
        const auto acceptedHits = std::count_if(world.events.begin(), world.events.end(),
            [](const Event &event) { return event.kind == "object_hit"; });
        check(world.tick == 300 && world.alpha() == 0,
              "World render cadence scenario advances the full five simulated seconds");
        check(acceptedHits == 2, "Alternating persistent attack serials each contact once through reaction completion");
        check(scene.objectSystem.instances().front().ageUs == 5000000, "Object age equals exact fixed-tick duration");
        check(exactRoundtrip && preservedPayload,
              "JSON roundtrip preserves live object timing, hits and unacknowledged one-time payload");
        return Json{{"final", scene.objectSystem.save()}, {"checkpoint", checkpoint}, {"trace", stateTrace}};
    };
    auto renderDeltas = [](int fps) {
        std::vector<int64_t> deltas;
        int64_t previous = 0;
        for (int frame = 1; frame <= fps * 5; ++frame) {
            const auto current = int64_t(frame) * 5000000000ll / (fps * 5);
            deltas.push_back(current - previous);
            previous = current;
        }
        return deltas;
    };
    const auto cadenceReference = fixedTickTrace(renderDeltas(60));
    Json cadenceRuns = Json::array({{{"fps", 60}, {"ticks", 300},
                                    {"final", cadenceReference["final"]}, {"checkpoint", cadenceReference["checkpoint"]},
                                    {"tick_trace", cadenceReference["trace"]}}});
    for (const int fps : {30, 144, 240}) {
        const auto result = fixedTickTrace(renderDeltas(fps));
        check(result == cadenceReference, "Object state is render-rate independent at " + std::to_string(fps) + " FPS");
        cadenceRuns.push_back({{"fps", fps}, {"ticks", 300}, {"equals_60_fps_every_tick", true},
                               {"final", result["final"]}});
    }
    const auto stalledResult = fixedTickTrace({750000000, 250000000, 2000000000, 500000000, 1500000000});
    check(stalledResult == cadenceReference, "Two-second render stall catch-up preserves fixed-tick object state");
    cadenceRuns.push_back({{"fps", "stall-catch-up"}, {"ticks", 300},
                          {"equals_60_fps_every_tick", true}, {"final", stalledResult["final"]}});

    Scene beforeRestore;
    beforeRestore.load(pvf, assets, "map/lorien/6.map", "restore-run", "0");
    const auto restoreObject = std::find_if(beforeRestore.objects.begin(), beforeRestore.objects.end(),
        [](const MapObject &object) { return object.id == 221; });
    check(restoreObject != beforeRestore.objects.end(), "Room restore fixture has a source barrel");
    ObjectAttack savedAttack;
    savedAttack.owner = 0; savedAttack.serial = 9001; savedAttack.damage = 1;
    savedAttack.volume = {restoreObject->x - 1, restoreObject->y - 2, restoreObject->z, 4, 4, 100};
    check(beforeRestore.objectSystem.contact(restoreObject->identity, savedAttack),
          "Pre-save World owner attack is accepted once");
    check(beforeRestore.objectSystem.consumePayload(restoreObject->identity, "reward-once", "drop", {{"item", 10}}),
          "Restore fixture schedules its one-time payload");
    const auto savedObjects = beforeRestore.saveObjects(0);
    const auto restoredIdentity = restoreObject->identity;
    Scene afterRestore;
    afterRestore.load(pvf, assets, "map/lorien/6.map", "restore-run", "0");
    afterRestore.restoreObjects(savedObjects, 0);
    auto *restoredBarrel = afterRestore.objectSystem.find(restoredIdentity);
    check(restoredBarrel && restoredBarrel->durability == 1,
          "Room restore retains partial candidate state");
    check(restoredBarrel && std::any_of(restoredBarrel->hits.begin(), restoredBarrel->hits.end(),
          [](const ObjectHitKey &hit) { return hit.owner == 0; }) == false,
          "Restored room retires transient World owner hit serials");
    check(!afterRestore.objectSystem.consumePayload(restoredIdentity, "reward-once", "drop", {{"item", 10}}),
          "Room restore preserves one-time payload consumption");
    check(std::count_if(afterRestore.objectSystem.pendingEvents().begin(), afterRestore.objectSystem.pendingEvents().end(),
          [](const ObjectEvent &event) { return event.kind == "drop"; }) == 1,
          "Room restore cannot duplicate the pending reward event");
    savedAttack.serial = 9001;
    check(afterRestore.objectSystem.contact(restoredIdentity, savedAttack) &&
          afterRestore.objectSystem.find(restoredIdentity)->state != ObjectState::Intact,
          "Fresh World may reuse a serial after scene reset without being rejected by stale hit state");

    Scene reactionSource;
    auto resumedPlacement = fixturePlacement;
    resumedPlacement.identity.run = "relative-clock-run";
    resumedPlacement.identity.recordOrdinal += 5000;
    reactionSource.objectSystem.add(resumedPlacement, fixtureDefinition, reactionBehavior);
    ObjectAttack reactionAttack;
    reactionAttack.owner = 0; reactionAttack.serial = 1;
    reactionAttack.volume = {resumedPlacement.x - 5, resumedPlacement.y - 5, resumedPlacement.z, 10, 10, 10};
    check(reactionSource.objectSystem.contact(resumedPlacement.identity, reactionAttack),
          "Relative-clock fixture starts a source-box damage reaction");
    reactionSource.objectSystem.advance(33333);
    const auto relativeClockSave = Json::parse(reactionSource.saveObjects(1683).dump());
    Json restoredClocks = Json::array();
    for (const int64_t initialTick : {int64_t(0), int64_t(5399)}) {
        Scene resumedScene;
        World resumedWorld(pvf, assets);
        resumedWorld.freezeAi = true;
        resumedWorld.tick = initialTick;
        resumedScene.objectSystem.add(resumedPlacement, fixtureDefinition, reactionBehavior);
        resumedScene.restoreObjects(relativeClockSave, resumedWorld.nowMs());
        auto *resumed = resumedScene.objectSystem.find(resumedPlacement.identity);
        check(resumed->ageUs == 33333 && resumed->actionAgeUs == 33333 &&
              resumed->state == ObjectState::Reacting,
              "Room restore retains relative reaction age at World tick " + std::to_string(initialTick));
        resumedWorld.setObjectTick([&](World &simulation) { resumedScene.updateObjects(simulation, pvf, assets); });
        resumedWorld.advance(83333334);
        const auto expectedElapsed = (initialTick + 5) * 1000000 / 60 - initialTick * 1000000 / 60;
        check(resumedWorld.tick == initialTick + 5 && resumed->ageUs == 33333 + expectedElapsed &&
              resumed->actionAgeUs == 33333 + expectedElapsed && resumed->state == ObjectState::Reacting,
              "Restored reaction advances only five current World ticks without counting absent-room time");
        resumedWorld.advance(16666666);
        check(resumedWorld.tick == initialTick + 6 && resumed->state == ObjectState::Intact &&
              resumed->motionTag == "[basic motion]" && resumed->actionAgeUs == 0,
              "Restored reaction exits once its relative animation duration completes");
        check(std::count_if(resumedWorld.events.begin(), resumedWorld.events.end(),
              [](const Event &event) { return event.kind == "object_reaction_end"; }) == 1,
              "Restored reaction emits exactly one completion event");
        restoredClocks.push_back({{"initial_world_tick", initialTick}, {"final", resumedScene.saveObjects(resumedWorld.nowMs())}});
    }

    return {{"status", "pass"}, {"count", checks.size()}, {"checks", checks},
        {"source_baseline", {{"legal_maps", mapPaths.size()}, {"placements", legalPlacementCount},
                             {"light_factories", legalLightCount}, {"maps", legalMapCounts}}},
        {"clock_cadence", cadenceRuns},
        {"restored_relative_clocks", restoredClocks},
        {"limitations", {"candidate hit acceptance is caller supplied", "native damage-to-object HP consumer remains unresolved",
                          "payload events require a separate idempotent reward or trap consumer"}}};
}
} // namespace dnf
