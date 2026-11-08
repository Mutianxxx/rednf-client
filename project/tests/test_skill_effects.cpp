#ifndef DNF_EFFECT_EVENTS_STANDALONE
#include "dnf/combat.hpp"
#endif
#include "dnf/content_profile.hpp"
#include "dnf/effect_plan.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
namespace dnf {
namespace {
void fixture16(Bytes &out, uint16_t value) {
    out.push_back(uint8_t(value)); out.push_back(uint8_t(value >> 8));
}
void fixture32(Bytes &out, uint32_t value) {
    for (int i = 0; i < 4; ++i) out.push_back(uint8_t(value >> (8 * i)));
}
Bytes fixtureEncrypt(Bytes raw) {
    raw.resize((raw.size() + 3) & ~size_t(3), 0);
    for (size_t i = 0; i < raw.size(); i += 4) {
        uint32_t value = uint32_t(raw[i]) | uint32_t(raw[i + 1]) << 8 |
            uint32_t(raw[i + 2]) << 16 | uint32_t(raw[i + 3]) << 24;
        value = ((value << 6) | (value >> 26)) ^ 0x81a79011u;
        for (int j = 0; j < 4; ++j) raw[i + j] = uint8_t(value >> (8 * j));
    }
    return raw;
}
Bytes logicalAni(int frameCount) {
    Bytes raw;
    fixture16(raw, uint16_t(frameCount)); fixture16(raw, 0); fixture16(raw, 0);
    for (int frame = 0; frame < frameCount; ++frame) {
        fixture16(raw, 0); // No boxes.
        fixture16(raw, 0xffff); // A valid logical frame with no drawable image.
        fixture32(raw, 0); fixture32(raw, 0);
        fixture16(raw, 1); fixture16(raw, 12); fixture32(raw, 50);
    }
    return raw;
}
std::filesystem::path alsFixtureArchive() {
    // A tiny independent ASCII ScriptFile/PVF fixture exercises actual Pvf
    // reading without injecting private caches or touching the source archive.
    const auto root = std::filesystem::absolute("cache/als-frame-event-fixtures");
#ifdef _WIN32
    if (root.root_name() != "D:" && root.root_name() != "d:")
        throw std::runtime_error("ALS fixture artifacts must stay on D:");
#endif
    std::filesystem::create_directories(root);
    std::filesystem::path directory;
    const auto stamp = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    for (int attempt = 0; attempt < 100; ++attempt) {
        directory = root / (std::to_string(stamp) + "-" + std::to_string(attempt));
        if (std::filesystem::create_directory(directory)) break;
        if (attempt == 99) throw std::runtime_error("Cannot allocate independent ALS fixture directory");
    }
    std::vector<std::string> strings;
    const auto stringId = [&](const std::string &text) {
        const auto found = std::find(strings.begin(), strings.end(), text);
        if (found != strings.end()) return uint32_t(found - strings.begin());
        strings.push_back(text);
        return uint32_t(strings.size() - 1);
    };
    const auto script = [&](const std::vector<Field> &fields) {
        Bytes raw{0xb0, 0xd0};
        for (const auto &field : fields) {
            raw.push_back(5); fixture32(raw, stringId(field.tag));
            for (const auto &value : field.values) {
                if (value.is_string()) {
                    raw.push_back(7); fixture32(raw, stringId(value.get<std::string>()));
                } else if (value.is_number_integer()) {
                    raw.push_back(2); fixture32(raw, uint32_t(value.get<int32_t>()));
                } else {
                    const auto number = value.get<float>();
                    uint32_t bits = 0; std::memcpy(&bits, &number, sizeof(bits));
                    raw.push_back(4); fixture32(raw, bits);
                }
            }
        }
        return raw;
    };
    std::map<std::string, Bytes> files;
    files["fixture/root.ani"] = logicalAni(2);
    files["fixture/child.ani"] = logicalAni(1);
    files["fixture/leaf.ani"] = logicalAni(1);
    files["fixture/empty.ani"] = logicalAni(0);
    files["fixture/duplicate.ani"] = logicalAni(2);
    files["fixture/empty-child.ani"] = logicalAni(2);
    files["fixture/missing-child.ani"] = logicalAni(2);
    files["fixture/malformed.ani"] = logicalAni(2);
    files["fixture/invalid-type.ani"] = logicalAni(2);
    files["fixture/root.ani.als"] = script({
        {"[remove]", {0, -2, "FX"}, 0},
        {"[add]", {0, 3, "FX"}, 0},
        {"[add]", {1, 4, "fx"}, 0},
        {"[remove]", {1, 4, "Missing"}, 0},
        {"[use animation]", {"child.ani", "FX"}, 0},
        {"[use animation]", {"child.ani", "fx"}, 0},
        {"[add]", {2, 0, "FX"}, 0},
        {"[add]", {0, 0, "FX", "extra"}, 0},
        {"[none effect add]", {0, 0, "FX"}, 0},
        {"[add]", {-1, 0, "FX"}, 0},
        {"[add]", {0, 1.5, "FX"}, 0},
        {"[add]", {32768, 0, "FX"}, 0}});
    files["fixture/child.ani.als"] = script({
        {"[use animation]", {"leaf.ani", "Nested"}, 0}, {"[add]", {0, -1, "Nested"}, 0}});
    files["fixture/empty.ani.als"] = script({
        {"[use animation]", {"child.ani", "FX"}, 0}, {"[add]", {0, 0, "FX"}, 0}});
    files["fixture/duplicate.ani.als"] = script({
        {"[use animation]", {"child.ani", "FX"}, 0},
        {"[use animation]", {"child.ani", "FX"}, 0}, {"[add]", {0, 0, "FX"}, 0}});
    files["fixture/empty-child.ani.als"] = script({
        {"[use animation]", {"empty.ani", "Empty"}, 0},
        {"[add]", {0, 0, "Empty"}, 0}, {"[remove]", {1, 0, "Empty"}, 0}});
    files["fixture/missing-child.ani.als"] = script({
        {"[use animation]", {"absent.ani", "Absent"}, 0}, {"[add]", {0, 0, "Absent"}, 0}});
    files["fixture/malformed.ani.als"] = {0xb0, 0xd0, 5};
    files["fixture/invalid-type.ani.als"] = script({
        {"[use animation]", {"child.ani", "FX"}, 0}, {"[add]", {0, 0, "FX"}, 0}});
    // Token 6 resolves to the same JSON string, but the recovered ALS grammar
    // requires token 7 for uniqueName. Do not accept it by value alone.
    files["fixture/invalid-type.ani.als"][32] = 6;
    Bytes table;
    fixture32(table, uint32_t(strings.size()));
    size_t offset = 4 * (strings.size() + 1);
    for (const auto &text : strings) { fixture32(table, uint32_t(offset)); offset += text.size(); }
    fixture32(table, uint32_t(offset));
    for (const auto &text : strings) table.insert(table.end(), text.begin(), text.end());
    files["stringtable.bin"] = std::move(table);
    Bytes tree, payload;
    uint32_t number = 0;
    for (const auto &[path, raw] : files) {
        fixture32(tree, ++number); fixture32(tree, uint32_t(path.size()));
        tree.insert(tree.end(), path.begin(), path.end());
        fixture32(tree, uint32_t(raw.size())); fixture32(tree, 0);
        fixture32(tree, uint32_t(payload.size()));
        const auto encrypted = fixtureEncrypt(raw);
        payload.insert(payload.end(), encrypted.begin(), encrypted.end());
    }
    tree = fixtureEncrypt(std::move(tree));
    Bytes archive;
    fixture32(archive, 36);
    const std::string guid = "00000000-0000-0000-0000-000000000003";
    archive.insert(archive.end(), guid.begin(), guid.end());
    fixture32(archive, 1); fixture32(archive, uint32_t(tree.size()));
    fixture32(archive, 0); fixture32(archive, uint32_t(files.size()));
    archive.insert(archive.end(), tree.begin(), tree.end());
    archive.insert(archive.end(), payload.begin(), payload.end());
    const auto path = directory / "synthetic-als-events.pvf";
    std::ofstream file(path, std::ios::binary);
    file.write(reinterpret_cast<const char *>(archive.data()), std::streamsize(archive.size()));
    if (!file) throw std::runtime_error("Cannot write synthetic ALS archive");
    return path;
}
} // namespace

Json runAnimationEffectEventsTests(Pvf &p, Assets &a) {
    Json checks = Json::array();
    const auto require = [&](bool passed, const char *reason) {
        if (!passed) throw std::runtime_error(reason);
        checks.push_back(reason);
    };
    {
        const std::string parent =
            "character/swordman/effect/animation/ashenfork_ds/ashenfork_back_normal.ani";
        const auto plan = animationEffectEvents(p, a, parent);
        const auto original = p.script(parent + ".als");
        require(plan.diagnostics.empty() && plan.events.size() == 3 &&
            plan.frameCount == a.animation(parent)->frames.size(),
            "ALS frame plan reads three direct source commands without precomputing time");
        require(plan.alsSource.rawBytes == original.rawBytes && plan.alsSource.tokens == original.tokens &&
            plan.alsSource.source == original.source,
            "ALS frame plan preserves exact source bytes ordered tokens and package identity");
        size_t previous = 0;
        for (size_t index = 0; index < plan.events.size(); ++index) {
            const auto &event = plan.events[index];
            const auto &field = original.fields.at(event.sourceOrder);
            require(event.kind == EffectEventKind::Add && (index == 0 || event.sourceOrder > previous) &&
                event.frame == field.values[0].get<int>() && event.layer == field.values[1].get<int>() &&
                event.instance == field.values[2].get<std::string>(),
                "ALS frame event preserves parent source frame layer exact name and record order");
            require(event.source == parent + ".als" && event.sourceOffset == field.offset &&
                event.sourceHash == sha256(original.rawBytes) && !event.animation.empty() &&
                event.declarationOffset < original.rawBytes.size(),
                "ALS frame event includes source path hash command and declaration offsets");
            previous = event.sourceOrder;
        }
        const auto legacy = animationEffectPlan(p, a, parent);
        require(legacy.diagnostics.empty() && legacy.tracks.size() == 4 &&
            legacy.tracks[1].layer == -2 && legacy.tracks[2].layer == -1 && legacy.tracks[3].layer == 1,
            "ALS precompiled legacy track behavior remains available and unchanged");
        const auto unsupported = animationEffectEvents(p, a,
            "character/common/animation/aura/chn_2020_children_package/blue_00_back_normal.ani");
        require(std::any_of(unsupported.diagnostics.begin(), unsupported.diagnostics.end(),
            [](const auto &issue) { return issue.value("code", "") == "unsupported_als_command" &&
                issue.value("tag", "") == "[none effect add]" && issue.contains("values") &&
                issue.contains("offset") && issue.contains("source_order"); }),
            "ALS unsupported live commands retain original values offsets order and identity");
    }
    const auto archivePath = alsFixtureArchive();
    Pvf fixture(archivePath);
    Assets assets(archivePath.parent_path(), fixture);
    const auto plan = animationEffectEvents(fixture, assets, "fixture/root.ani");
    require(plan.events.size() == 3 && plan.events[0].kind == EffectEventKind::Remove &&
        plan.events[1].kind == EffectEventKind::Add && plan.events[0].frame == 0 &&
        plan.events[1].frame == 0 && plan.events[0].sourceOrder == 0 && plan.events[1].sourceOrder == 1,
        "ALS same-frame remove then add remains in source order with forward declarations");
    require(plan.events[1].instance == "FX" && plan.events[2].instance == "fx" &&
        plan.events[1].declarationOffset != plan.events[2].declarationOffset,
        "ALS uniqueName binding preserves case-sensitive identities");
    require(plan.events[1].animation == "fixture/child.ani" &&
        assets.animation(plan.events[1].animation)->frames.front().image.empty(),
        "ALS image-less logical child frames remain valid add instances");
    require(plan.events.size() == 3 &&
        animationEffectEvents(fixture, assets, "fixture/child.ani").events.size() == 1,
        "ALS frame plans do not recursively flatten child events or convert their clocks");
    const auto has = [](const EffectEventPlan &value, const std::string &code) {
        return std::any_of(value.diagnostics.begin(), value.diagnostics.end(),
            [&](const auto &issue) { return issue.value("code", "") == code; });
    };
    require(has(plan, "unresolved_als_name") && has(plan, "unsupported_als_frame") &&
        has(plan, "invalid_als_event") && has(plan, "unsupported_als_command") &&
        plan.alsSource.rawBytes == fixture.read("fixture/root.ani.als"),
        "ALS undeclared remove invalid payload range and unsupported kind remain diagnostic with raw source");
    const auto duplicate = animationEffectEvents(fixture, assets, "fixture/duplicate.ani");
    require(duplicate.events.empty() && has(duplicate, "duplicate_als_name") &&
        has(duplicate, "unresolved_als_name"),
        "ALS duplicate declarations never silently choose first or last binding");
    const auto noSidecar = animationEffectEvents(fixture, assets, "fixture/leaf.ani");
    require(noSidecar.events.empty() && noSidecar.diagnostics.empty() && noSidecar.frameCount == 1,
        "ALS absent optional sidecar is a valid leaf animation");
    const auto emptyParent = animationEffectEvents(fixture, assets, "fixture/empty.ani");
    require(emptyParent.events.empty() && has(emptyParent, "empty_parent_animation") &&
        !emptyParent.alsSource.rawBytes.empty(), "ALS empty parent retains sidecar and has explicit diagnostic");
    const auto emptyChild = animationEffectEvents(fixture, assets, "fixture/empty-child.ani");
    require(emptyChild.events.size() == 1 && emptyChild.events[0].kind == EffectEventKind::Remove &&
        has(emptyChild, "empty_als_animation"),
        "ALS empty child blocks add while a source-bound remove stays an independent event");
    const auto missingChild = animationEffectEvents(fixture, assets, "fixture/missing-child.ani");
    require(missingChild.events.empty() && has(missingChild, "unresolved_als_animation"),
        "ALS missing declared child never emits a placeholder add");
    const auto malformed = animationEffectEvents(fixture, assets, "fixture/malformed.ani");
    require(malformed.events.empty() && has(malformed, "invalid_als_script") &&
        malformed.alsSource.rawBytes == fixture.read("fixture/malformed.ani.als"),
        "ALS malformed ScriptFile remains preserved instead of throwing away source bytes");
    const auto missingParent = animationEffectEvents(fixture, assets, "fixture/absent.ani");
    require(missingParent.events.empty() && has(missingParent, "missing_parent_animation"),
        "ALS missing parent has an explicit non-executable plan");
    const auto invalidType = animationEffectEvents(fixture, assets, "fixture/invalid-type.ani");
    require(invalidType.events.empty() && has(invalidType, "invalid_als_event"),
        "ALS resolved strings with a non-native token kind do not become executable commands");
    require(plan.alsSource.source.value("member_sha256", "") == sha256(plan.alsSource.rawBytes) &&
        assets.animation("fixture/root.ani")->duration == 100,
        "ALS event extraction preserves source ANI timing and source document identity");
    return {{"status", "pass"}, {"checks", checks}, {"fixture", archivePath.u8string()},
        {"fixture_sha256", fixture.identity()},
        {"scope", "direct parent-frame ALS source contract; runtime visit/lifetime consumer verified separately"}};
}

#ifndef DNF_EFFECT_EVENTS_STANDALONE
Json runSkillEffectsTests(Pvf &p, Assets &a) {
    Json checks = Json::array();
    const auto frameEvents = runAnimationEffectEventsTests(p, a);
    for (const auto &check : frameEvents.at("checks")) checks.push_back(check);
    auto require = [](bool pass, const char *reason) { if (!pass) throw std::runtime_error(reason); };
    auto step = [](World &w, int frames) { for (int n = 0; n < frames; ++n) w.advance(16666667); };
    {
        World w(p,a);
        Effect wave;
        wave.id = 777; wave.skill = 58;
        wave.animation = "passiveobject/character/swordman/animation/normalwavefire.ani";
        wave.born = 0; wave.expires = 300;
        wave.firstPulse = 100; wave.interval = 50; wave.maxPulses = 2; wave.pulseWindow = 200;
        w.effects.push_back(wave);
        int exposed = 0;
        for (int frame = 0; frame < 18; ++frame) {
            step(w,1);
            bool accepted = false;
            for (const auto &event : w.events)
                if (event.tick == w.tick && event.kind == "pulse" && event.source == 777) accepted = true;
            for (const auto &volume : w.attackVolumes) if (volume.serial == ((uint64_t(1)<<63)|777)) {
                require(accepted && volume.pulse >= 1 && volume.pulse <= 2,
                    "Object attack volumes may exist only on accepted periodic effect pulses");
                ++exposed;
            }
        }
        require(exposed > 0, "Source attack boxes exercise the periodic object-contact gate");
        checks.push_back("periodic object contact follows accepted pulses and the first-pulse delay");
    }
    {
        const auto cross = objectEffectPlan(p, a, "passiveobject/character/swordman/gorecross.obj");
        require(cross.diagnostics.empty() && cross.tracks.size() == 2, "Blood cross source object composition");
        require(cross.tracks[0].primary && !cross.tracks[1].primary && cross.tracks[1].layer == -1 &&
                cross.tracks[1].sourceOffset == 77, "Blood cross original add-object layer and offset");
        const auto wave = objectEffectPlan(p, a, "passiveobject/character/swordman/normalwave.obj");
        require(wave.tracks.size() == 1 && wave.tracks[0].animation.find("normalwavefire.ani") != std::string::npos &&
                wave.tracks[0].end == 325, "Wave must use source OBJ Fire motion and complete-once duration");
        const auto als = animationEffectPlan(p, a,
            "character/swordman/effect/animation/ashenfork_ds/ashenfork_back_normal.ani");
        require(als.diagnostics.empty() && als.tracks.size() == 4, "Source ALS must preserve all three named layers");
        require(als.tracks[1].layer == -2 && als.tracks[2].layer == -1 && als.tracks[3].layer == 1,
                "Source ALS child layer offsets");
        checks.push_back("source OBJ primary/extra tracks, source offsets and named ALS instances");
        const auto unsupported = animationEffectPlan(p, a,
            "character/common/animation/aura/chn_2020_children_package/blue_00_back_normal.ani");
        bool noneEffect = false;
        for (const auto &issue : unsupported.diagnostics)
            noneEffect |= issue.value("tag", "") == "[none effect add]" && issue.contains("values") && issue.contains("offset");
        require(noneEffect, "Native ALS kinds requiring live semantics must retain field/offset diagnostics instead of vanishing");
        checks.push_back("unsupported native ALS command remains explicit with original values and field offset");
    }
    {
        World w(p, a); w.activate(6);
        bool found = false, slash = false;
        for (int i = 0; i < 100; ++i) {
            step(w, 1);
            for (const auto &e : w.effects) slash |= e.animation.find("normalwaveslash.ani") != std::string::npos;
            for (const auto &e : w.effects) if (e.phase == "normalwave:projectile") {
                require(w.player.poseFrame >= 4 && e.expires - e.born == 325, "Wave source controller trigger frame/lifetime");
                found = true;
            }
        }
        require(found && slash && w.activeSkill() < 0, "Wave casts through sentinel, preserves slash, and releases actor");
        checks.push_back("wave begins on release frame and uses a single source Fire cycle");
    }
    {
        // Real source boxes extend well beyond the old hardcoded center range;
        // transparent/box-free cross frames must not cause invisible damage.
        for (int facing : {-1, 1}) {
            World w(p, a); w.freezeAi = true;
            Actor target; target.id = 1; target.x = target.px = 500 + facing * 205;
            target.y = target.py = 260; target.hp = target.maxHp = 10000;
            target.monsterPath = "monster/goblin/goblin.mob"; w.monsters.push_back(target);
            Effect wave; wave.skill = 20; wave.animation = "passiveobject/character/swordman/animation/normalwavefire.ani";
            wave.x = wave.px = 500; wave.y = wave.py = 260; wave.dir = facing;
            wave.expires = 325; wave.interval = 100000; w.effects.push_back(wave);
            step(w, 1);
            require(w.monsters.front().hp < 10000, "Both-facing wave authored reach cannot be truncated by a center-distance filter");
        }
        World w(p, a); w.freezeAi = true;
        Actor target; target.id = 1; target.x = target.px = 500; target.y = target.py = 260;
        target.hp = target.maxHp = 10000; target.monsterPath = "monster/goblin/goblin.mob";
        w.monsters.push_back(target);
        Effect cross; cross.skill = 64; cross.animation = "passiveobject/character/swordman/animation/gorecross1.ani";
        cross.x = cross.px = 500; cross.y = cross.py = 260; cross.z = 82;
        cross.expires = a.animation(cross.animation)->duration; cross.interval = 100000;
        w.effects.push_back(cross); step(w, 2);
        require(w.monsters.front().hp == 10000, "Blank initial blood cross frames have no hit volume");
        step(w, 2);
        require(w.monsters.front().hp < 10000, "Floating blood cross authored Z volume still intersects grounded hurtboxes");
        checks.push_back("source projectile reach and blank-frame timing; both-facing wave and floating cross hit volumes");
    }
    {
        for (int facing : {-1, 1}) {
            World w(p, a); w.player.dir = facing; w.player.x = w.player.px = 500; w.activate(9);
            step(w, 22);
            int attached = 0;
            for (const auto &e : w.effects) {
                require(e.phase != "gorecross:projectile", "Body frame7 must not create the blood cross before the layer event");
                if (e.attached && e.skill == 64) ++attached;
            }
            require(attached == 4, "Native setState35 attaches all four skill64 animation slots");
            step(w, 10);
            const Effect *primary = nullptr, *extra = nullptr;
            for (const auto &e : w.effects) {
                if (e.phase == "gorecross:projectile") primary = &e;
                if (e.phase == "gorecross:normal-layer") extra = &e;
            }
            require(primary && extra && primary->damageEnabled && !extra->damageEnabled,
                    "Blood cross must keep source pair but only primary causes damage");
            require(primary->born >= 500 && primary->born < 550,
                    "Blood cross waits for source layer event and the next controller phase");
            require(primary->dir == facing && primary->z == 82 && primary->x == extra->x &&
                    primary->y == extra->y && primary->z == extra->z && extra->layer == primary->layer - 1,
                    "Blood cross source pair must share transformed floating anchor/trajectory");
            step(w, 15);
            require(w.activeSkill() < 0 && w.player.animation == "stay",
                    "Ordinary GoreCross releases actor at source body frame10 instead of the full ANI tail");
            int movingLayers = 0;
            for (const auto &e : w.effects) {
                require(!(e.attached && e.skill == 64 && e.animation.find("/gorecross/slash") != std::string::npos),
                        "Blood cross attached slash pair must not linger in source placeholder frames");
                if (e.phase == "gorecross:projectile" || e.phase == "gorecross:normal-layer") ++movingLayers;
            }
            require(movingLayers == 2 &&
                    a.animation("character/swordman/effect/animation/gorecross/slash2.ani")->duration == 1500,
                    "Attached lifetime does not truncate moving source pair or mutate original ANI duration");
        }
        checks.push_back("both-facing blood cross: floating anchor, source normal/additive pair, no duplicate damage");
        checks.push_back("native layer event/phase trigger; four source slots; bodyframe10 release and independent projectile lifetime");
    }
    {
        World w(p, a); w.freezeAi = true; w.combat = true;
        w.player.x = w.player.px = 500; w.player.y = w.player.py = 260;
        Actor target; target.id = 1; target.x = target.px = 580; target.y = target.py = 260;
        target.hp = target.maxHp = 100000; target.monsterPath = "monster/goblin/goblin.mob";
        w.monsters.push_back(target);
        w.activate(9);
        bool resetAtFrameSix = false;
        uint64_t beforeReset = 0, afterReset = 0;
        std::set<uint64_t> swingSerials;
        for (int frame = 0; frame < 55; ++frame) {
            // Hold only the diagnostic target's ground position so knockback
            // cannot move it out of the second slash. Real source hurt poses,
            // local pauses, collision boxes and accepted-hit handling still run.
            auto &heldTarget = w.monsters.front();
            heldTarget.x = heldTarget.px = 580;
            heldTarget.y = heldTarget.py = 260;
            heldTarget.vx = heldTarget.vy = 0;
            step(w, 1);
            for (const auto &volume : w.attackVolumes) swingSerials.insert(volume.serial);
            for (const auto &event : w.events) if (event.kind == "attack_reset" &&
                event.name == "gorecross:selector24-body-frame6") {
                resetAtFrameSix = true;
                beforeReset = event.tick ? event.tick - 1 : 0;
                afterReset = event.tick;
            }
        }
        Json bodyHits = Json::array();
        for (const auto &event : w.events)
            if (event.kind == "hit" && event.name == "gorecross" && event.target == 1)
                bodyHits.push_back({{"tick", event.tick}, {"damage", event.value}});
        writeJson("reports/combat-native-reverse/gorecross-body-hit-test.json",
                  {{"body_hits", bodyHits}, {"reset_tick", afterReset}, {"state", w.snapshot()},
                   {"scope", "Controlled fixture, authored body/weapon boxes and local hit list; ATK translation remains reconstruction"}});
        require(resetAtFrameSix && afterReset > beforeReset && swingSerials.size() >= 2,
                "Native selector24 setter resets per-target attack registration at body frame6");
        require(!swingSerials.empty() && *swingSerials.begin() < *swingSerials.rbegin(),
                "Body attack frames continue under a new local serial after the frame6 reset boundary");
        require(bodyHits.size() == 2 && bodyHits[0]["tick"].get<int64_t>() < int64_t(afterReset) &&
                bodyHits[1]["tick"].get<int64_t>() >= int64_t(afterReset),
                "Source body/weapon collision hits a stationary target once per GoreCross slash, not once for the entire cast");
        checks.push_back("body frame6 selector24 reset boundary advances local target-registration serial");
    }
    {
        for (double height : {20.0, 100.0}) {
            World w(p, a); w.player.z = w.player.pz = height; w.activate(4);
            bool dust = false, flash = false, ring = false;
            for (int i = 0; i < 60; ++i) {
                step(w, 1);
                for (const auto &e : w.effects) {
                    dust |= e.animation.find("ashenforksubdust") != std::string::npos;
                    flash |= e.animation.find("ashenforksubflash") != std::string::npos;
                    ring |= e.phase == "ashenfork:impact";
                }
            }
            require(height >= 50 ? dust && flash && ring : !dust && !flash && !ring,
                    "Silver falling blade source minimum height gates ring/dust/flash");
            require(w.activeSkill() < 0 && w.player.z == 0, "Falling blade must unlock after landing");
        }
        checks.push_back("falling blade minimum height; ring/dust/flash; landing always releases movement");
    }
    {
        World w(p, a); w.freezeAi = true;
        Actor target; target.id = 1; target.x = target.px = w.player.x + 45;
        target.y = target.py = w.player.y; target.hp = target.maxHp = 10000;
        target.monsterPath = "monster/goblin/goblin.mob"; w.monsters.push_back(target);
        w.activate(8); std::set<int> normalInstances;
        for (int i = 0; i < 150; ++i) {
            step(w, 1);
            for (const auto &e : w.effects) if (e.phase == "vaneslash:pulse-normal-layer") {
                require(!e.damageEnabled, "Pulse normal layer is visual-only");
                normalInstances.insert(e.id);
            }
        }
        require(normalInstances.size() == 3, "All three wave pulses retain their normal-blend companion");
        checks.push_back("vane slash normal blend follows all three pulse events without duplicate damage");
    }
    {
        double shortTravel = 0, heldTravel = 0;
        for (bool held : {false, true}) {
            World w(p, a); w.player.x = w.player.px = 300;
            if (held) w.enqueue({0, 30, true}); else w.activate(10);
            bool sword = false, dust = false, wrongShock = false, airborne = false;
            for (int i = 0; i < 100; ++i) {
                step(w, 1); airborne |= w.player.z > 10;
                for (const auto &e : w.effects) {
                    if (e.attached) require(e.x == w.player.x + w.player.dir * e.offsetX && e.z == w.player.z,
                                             "Moving sword effects cannot lag a simulation tick behind actor");
                    sword |= e.animation.find("hopsmash/sword") != std::string::npos;
                    dust |= e.animation.find("hopsmash/smash") != std::string::npos;
                    wrongShock |= e.phase == "hopsmash:impact";
                }
            }
            require(sword && dust && airborne && !wrongShock && w.activeSkill() < 0 && w.player.z == 0,
                    "Unadvanced hop smash preserves jump and sword/smash without advanced passive wave");
            (held ? heldTravel : shortTravel) = w.player.x - 300;
        }
        require(heldTravel > shortTravel + 100, "Hop smash held input must travel farther using source endpoints");
        World advanced(p, a); advanced.bloodVigorousLevel = 1; advanced.activate(10);
        bool shock = false, sourceExtra = false;
        for (int i = 0; i < 100; ++i) {
            step(advanced, 1);
            for (const auto &e : advanced.effects) {
                shock |= e.phase == "hopsmash:impact";
                sourceExtra |= e.animation.find("hopsmashsubfront2") != std::string::npos && !e.damageEnabled;
            }
        }
        require(shock && sourceExtra, "Explicit learned advanced passive enables source front/additive wave");
        checks.push_back("hop smash source passive gate, hold-dependent smooth jump, four-layer advanced impact");
    }
    {
        World w(p, a); w.walkRects = {{0, 185, 800, 155}};
        w.blockedRects = {{200, 240, 80, 80}, {260, 230, 70, 70}};
        const auto pos = w.nearestWalkable(260, 270);
        require(w.canWalk(pos[0], pos[1]), "Spawn recovery must subtract overlapping blockers");
        w.walkRects = {{0, 185, 24, 10}}; w.blockedRects = {{0, 180, 40, 30}};
        require(!w.canWalk(12, 190), "Covered source ground cannot become a fabricated valid cell");
        checks.push_back("safe spawn projection subtracts overlapping blockers; no fabricated free ground");
    }
    return {{"status", "pass"}, {"checks", checks},
            {"scope", "source composition and controller regression; original PC visual parity not claimed"}};
}
#endif
} // namespace dnf

#ifdef DNF_EFFECT_EVENTS_STANDALONE
int wmain(int argc, wchar_t **argv) {
    if (argc != 3) {
        std::cerr << "Usage: effect_events_test CLIENT_ROOT REPORT.json\n";
        return 2;
    }
    try {
        const std::filesystem::path client(argv[1]);
        dnf::Pvf pvf(client / "Script.pvf");
        dnf::Assets assets(client, pvf);
        const auto report = dnf::runAnimationEffectEventsTests(pvf, assets);
        dnf::writeJson(argv[2], report);
        std::cout << report.at("checks").size() << " ALS frame-event checks; PASS\n";
        return 0;
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
#endif
