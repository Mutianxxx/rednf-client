#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/effect_plan.hpp"
#include "dnf/equipment_motion.hpp"
#include "dnf/renderer.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <cmath>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
struct EffectDummyVideo {
    bool owns = false;
    EffectDummyVideo() {
        const auto *configured = SDL_getenv("SDL_VIDEODRIVER");
        if (!configured || std::string(configured) != "dummy")
            throw std::runtime_error("Effect pixel regression requires SDL_VIDEODRIVER=dummy; no frontend was opened");
        if (!(SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO)) {
            if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) throw std::runtime_error(SDL_GetError());
            owns = true;
        }
        if (!SDL_GetCurrentVideoDriver() || std::string(SDL_GetCurrentVideoDriver()) != "dummy")
            throw std::runtime_error("Effect pixel regression refuses an existing visible video driver");
    }
    ~EffectDummyVideo() { if (owns) SDL_QuitSubSystem(SDL_INIT_VIDEO); }
};
Bytes effectPixels(Renderer &renderer) {
    const auto size = renderer.outputSize();
    Bytes pixels(size_t(size[0]) * size[1] * 4);
    if (SDL_RenderReadPixels(renderer.raw(), nullptr, SDL_PIXELFORMAT_RGBA32,
            pixels.data(), size[0] * 4) != 0) throw std::runtime_error(SDL_GetError());
    return pixels;
}
void effectFloor(World &world) {
    world.freezeAi = true; world.combat = true; world.freeCd = true;
    world.monsters.clear(); world.mapWidth = 2000; world.walkRects = {{0, 150, 2000, 600}};
    world.player.x = world.player.px = 500; world.player.y = world.player.py = 350;
    world.player.z = world.player.pz = 0; world.player.mp = INT32_MAX;
}
void effectSkill(World &world, int id) {
    auto &runtime = *world.experimentalRuntime(); const auto &plan = runtime.plan();
    runtime.configuration() = ExperimentalSkillConfiguration(plan);
    runtime.configuration().configureFemaleGunnerSourceSkill({5,id}, 1, plan);
    runtime.configuration().assignSlot(0, SkillKey{5,id}, plan);
    world.enqueue({world.simulationNanoseconds(),20,true});
}
size_t alsEvents(const World &world, int parent = -1) {
    return std::count_if(world.events.begin(), world.events.end(), [&](const auto &event) {
        return event.kind == "als_event" && (parent < 0 || parent == event.source);
    });
}
} // namespace

Json runEffectCoordinatesTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), sources = Json::array(), consumers = Json::array();
    const auto check = [&](bool valid, const std::string &message) {
        if (!valid) throw std::runtime_error("Effect coordinates: " + message);
        checks.push_back(message);
    };
    const std::string spin = "character/fighter/animation/suplexcycloneexspin.ani";
    const auto spinPlan = animationEffectEvents(pvf,assets,spin);
    check(spinPlan.events.size() == 2 && spinPlan.diagnostics.empty(),
        "Current1031 ordinary draw-only ALS commands have a live, strictly parsed event plan");
    check(spinPlan.alsSource.rawBytes == pvf.read(spin + ".als") &&
        spinPlan.events[0].sourceOffset == 17 && spinPlan.events[1].sourceOffset == 47 &&
        spinPlan.events[0].sourceOrder < spinPlan.events[1].sourceOrder &&
        spinPlan.events[0].frame == 0 && spinPlan.events[1].frame == 2 &&
        spinPlan.events[0].instance == "spectrum" && spinPlan.events[1].instance == "spectrum" &&
        spinPlan.events[0].offsetX == 0 && spinPlan.events[0].offsetY == 1 && spinPlan.events[0].offsetZ == 50,
        "Original frame, repeated uniqueName, XYZ, source offsets, order, tokens and bytes are retained");
    sources.push_back(spinPlan.alsSource.source);
    {
        const auto sentinel = animationEffectEvents(pvf,assets,"character/fighter/animation/groundkickkick.ani");
        bool diagnosed = false;
        for (const auto &issue : sentinel.diagnostics)
            diagnosed |= issue.value("code",std::string()) == "unsupported_als_ground_layer" &&
                issue.at("values").back() == -1000;
        check(diagnosed && std::none_of(sentinel.events.begin(),sentinel.events.end(),[](const auto &event) {
            return event.kind == EffectEventKind::DrawOnly;
        }), "Native ground-layer Z sentinel remains a specific diagnostic, without a guessed layer alias");
        sources.push_back(sentinel.alsSource.source);
    }
    for (const auto policy : {ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        World world(pvf,assets); world.freezeAi = true; world.configureAnimationClock(policy);
        Effect root; root.id = 700001; root.animation = spin; root.born = 0; root.expires = 5000;
        root.x = root.px = 600; root.y = root.py = 340; root.z = 40; root.damageEnabled = false;
        root.groundRender = true;
        world.effects.push_back(root); world.advanceSingleTick();
        auto first = std::find_if(world.effects.begin(),world.effects.end(),[](const auto &effect) {
            return effect.phase == "als-draw-only:inferred-single-source-clip-lifetime";
        });
        check(first != world.effects.end(),"A real source ALS frame creates an independent world object at runtime");
        const int firstId = first->id;
        check(first->x == 600 && first->y == 341 && first->z == 90 && first->pz == 90 &&
            !first->attached && first->parentId == -1 && first->alsParentId == -1 && !first->damageEnabled && !first->groundRender &&
            first->animationClock && first->animationClock->policy == ani_clock::ClockPolicy::SourceDelay100 &&
            first->resourceSource == spin + ".als" && first->sourceOffset == 17,
            "Draw-only samples parent world XYZ once, starts at birth height and owns a source100 visual clock");
        const auto firstExpiry = first->expires;
        world.effects.front().x = 655; world.effects.front().y = 360; world.effects.front().z = 70;
        bool second = false, overlapping = false;
        for (int tick = 0; tick < 90 && !second; ++tick) {
            world.advanceSingleTick();
            size_t simultaneous = 0;
            for (const auto &effect : world.effects) if (effect.phase == "als-draw-only:inferred-single-source-clip-lifetime") {
                ++simultaneous;
                if (effect.id == firstId) check(effect.x == 600 && effect.y == 341 && effect.z == 90,
                    "Previously created draw-only object stays at its world position after parent movement");
                if (effect.sourceOffset == 47) {
                    second = true;
                    check(effect.x == 655 && effect.y == 361 && effect.z == 120,
                        "Repeated name creates the second independent object at the second parent sample");
                }
            }
            overlapping |= simultaneous == 2;
        }
        check(second && alsEvents(world,700001) == 2,"Ordered frame visits dispatch both repeated draw-only commands exactly once");
        check(overlapping,"Same-name draw-only instances overlap instead of replacing one another");
        const auto current = world.nowMs(); world.effects.front().expires = current;
        world.advanceSingleTick();
        check(std::any_of(world.effects.begin(),world.effects.end(),[](const auto &effect) {
            return effect.phase == "als-draw-only:inferred-single-source-clip-lifetime";
        }),"Independent draw-only survives its parent's removal");
        consumers.push_back({{"clock_policy",ani_clock::policyName(policy)},{"source",spin},
            {"first_expiry_ms",firstExpiry},{"events",alsEvents(world,700001)},
            {"lifecycle_classification","inferred-one-source-clip; native retirement pending"}});
        for (int tick = 0; tick < 180; ++tick) world.advanceSingleTick();
        check(world.effects.empty(),"Independent draw-only releases after its documented single-clip beta lifetime");
    }
    for (int direction : {-1,1}) {
        World world(pvf,assets);world.freezeAi = true;
        world.configureAnimationClock(ani_clock::ClockPolicy::SourceDelay100);
        Effect root; root.id = 710000; root.animation = "character/mage/atanimation/darkchangestart.ani";
        root.born = 0; root.expires = 1500; root.x = root.px = 400; root.y = root.py = 350;
        root.z = 30; root.dir = direction; root.damageEnabled = false;
        world.effects.push_back(root);world.advanceSingleTick();
        const auto child = std::find_if(world.effects.begin(),world.effects.end(),[](const auto &effect) {
            return effect.alsInstance == "-2";
        });
        check(child != world.effects.end() && child->x == 400 + direction * 8 && child->y == 348 && child->z == 104,
            "Current1031 draw-only transforms source X by facing and preserves independent Y/Z");
    }
    for (const auto &example : {std::pair<const char *,int>{
            "character/gunner/atanimation/multiheadshotextract.ani",-10000},
            {"character/swordman/animation/momentaryslashex.ani",-9999}}) {
        const auto plan = animationEffectEvents(pvf,assets,example.first);
        const auto source = std::find_if(plan.events.begin(),plan.events.end(),[&](const auto &event) {
            return event.kind == EffectEventKind::Add && event.layer == example.second;
        });
        check(source != plan.events.end(),"Real source ALS retains its large negative local layer number");
        const auto sourceAnimation = assets.animation(example.first);
        int64_t eventTime = 0;
        for (int frame = 0; frame < source->frame; ++frame)
            eventTime += sourceAnimation->frames.at(size_t(frame)).duration;
        // MomentarySlashEx deliberately holds its first source frame for
        // 100000ms. This fixture has no charge controller; consume that exact
        // source clock rather than expire the root before its frame-1 event.
        const auto waitTicks = int((eventTime + 1000) * 60 / 1000 + 2);
        World world(pvf,assets);world.freezeAi = true;
        world.configureAnimationClock(ani_clock::ClockPolicy::SourceDelay100);
        Effect root;root.id = 720000;root.animation = example.first;root.born = 0;root.expires = eventTime + 2000;
        root.x = root.px = 400;root.y = root.py = 350;root.damageEnabled = false;root.layer = 0;
        root.groundRender = true;world.effects.push_back(root);
        bool found = false;
        for (int tick = 0;tick < waitTicks && !found;++tick) {
            world.advanceSingleTick();
            for (const auto &effect : world.effects) if (effect.alsParentId == 720000 && effect.alsInstance == source->instance) {
                check(effect.layer == example.second && !effect.groundRender && effect.y == 350,
                    "Raw -10000/-9999 ALS child sorts locally without inheriting the legacy ground plane");
                found = true;
            }
        }
        check(found,"Real negative-layer source command reaches the live world consumer");
    }
    for (const auto policy : {ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
        World world(pvf,assets);world.enableExperimentalCharacters();world.configureAnimationClock(policy);
        world.selectCharacter({5,0,0});dnf::enterExplicitSkillPreviewFixture(world);world.setCharacterAppearance(defaultCharacterAppearance(pvf,world.characterCatalog(),{5,0,0}));
        effectFloor(world);effectSkill(world,101);world.advanceSingleTick();
        check(world.experimentalRuntime()->attacking() &&
            world.actorAni() == "character/gunner/atanimation/airraidex.ani",
            "Actual female Gunner source skill-slot input selects its authored CHR motion");
        const auto host = std::find_if(world.effects.begin(),world.effects.end(),[](const auto &effect) {
            return effect.actorAnimationHost && effect.actorHostKey == "body";
        });
        check(host != world.effects.end() && !host->drawSelf && host->animationClock &&
            host->animationClock->elapsedMs == world.player.animationClock->elapsedMs &&
            host->animationClock->visit == world.player.animationClock->visit,
            "Actual character body supplies an invisible ALS host using the already advanced root clock");
        const int hostId = host->id;
        check(alsEvents(world,hostId) >= 2 && std::any_of(world.effects.begin(),world.effects.end(),[&](const auto &effect) {
            return effect.alsParentId == hostId && effect.alsInstance == "burn" && effect.drawSelf;
        }) && std::any_of(world.effects.begin(),world.effects.end(),[](const auto &effect) {
            return effect.alsInstance == "smoke" && !effect.attached && effect.drawSelf;
        }), "Normal skill release creates body-attached burn and independent draw-only smoke through actual ALS consumers");
        const auto burn = std::find_if(world.effects.begin(),world.effects.end(),[&](const auto &effect) {
            return effect.alsParentId == hostId && effect.alsInstance == "burn";
        });
        check(burn != world.effects.end() && burn->loop && burn->animationClock && burn->animationClock->loop,
            "Source ANI global-loop flag is consumed by an actual body ALS attached child");
        const int burnId = burn->id;const auto burnVisit = burn->animationClock->visit;
        const auto eventCount = alsEvents(world,hostId), elapsed = world.player.animationClock->elapsedMs;
        world.player.hitStopTicks = 3;
        for (int tick = 0; tick < 3; ++tick) world.advanceSingleTick();
        check(world.player.animationClock->elapsedMs == elapsed && alsEvents(world,hostId) == eventCount &&
            std::count_if(world.effects.begin(),world.effects.end(),[](const auto &effect) {
                return effect.actorAnimationHost;
            }) == 1 && std::any_of(world.effects.begin(),world.effects.end(),[&](const auto &effect) {
                return effect.id == hostId && effect.expires == INT64_MAX;
            }) && std::any_of(world.effects.begin(),world.effects.end(),[&](const auto &effect) {
                return effect.id == burnId && effect.expires == INT64_MAX;
            }) && std::count_if(world.effects.begin(),world.effects.end(),[](const auto &effect) {
                return effect.alsInstance == "smoke" && effect.alsParentId == -1;
            }) == 1,
            "Hitstop neither advances the body twice nor repeats installed ALS frame events");
        Json loopTrace = Json::array();
        for (int tick = 0;tick < 8;++tick) {
            world.advanceSingleTick();Json trace = {{"ms",world.nowMs()},{"effects",Json::array()}};
            for (const auto &effect : world.effects) trace["effects"].push_back({
                {"id",effect.id},{"parent",effect.alsParentId},{"host",effect.actorAnimationHost},
                {"phase",effect.phase},{"instance",effect.alsInstance},{"expires",effect.expires},
                {"elapsed",effect.animationClock ? double(effect.animationClock->elapsedMs) : -1}});
            loopTrace.push_back(std::move(trace));
        }
        const auto repeatedBurn = std::find_if(world.effects.begin(),world.effects.end(),[&](const auto &effect) {
            return effect.id == burnId;
        });
        Json burnState = {{"policy",ani_clock::policyName(policy)},{"world_ms",world.nowMs()},
            {"burn_id",burnId},{"host_id",hostId},{"trace",loopTrace},
            {"exists",repeatedBurn != world.effects.end()},{"body",world.actorAni()},
            {"body_clock_ms",world.player.animationClock ? double(world.player.animationClock->elapsedMs) : -1}};
        if (repeatedBurn != world.effects.end()) {
            burnState["animation"] = repeatedBurn->animation;
            burnState["source_duration_ms"] = assets.animation(repeatedBurn->animation)->duration;
            if (repeatedBurn->animationClock) burnState["clock"] = {
                {"elapsed_ms",repeatedBurn->animationClock->elapsedMs},{"loop_count",repeatedBurn->animationClock->loopCount},
                {"visit",repeatedBurn->animationClock->visit},{"loop",repeatedBurn->animationClock->loop}};
        }
        check(repeatedBurn != world.effects.end() && repeatedBurn->animationClock &&
            repeatedBurn->animationClock->loopCount > 0 && repeatedBurn->animationClock->visit > burnVisit,
            "Attached source-loop child repeats real frames instead of holding its last pose after 90ms: " + burnState.dump());
        world.player.dead = true;world.player.life = ActorLife::Dying;world.advanceSingleTick();
        check(std::none_of(world.effects.begin(),world.effects.end(),[&](const auto &effect) {
            return effect.actorAnimationHost || effect.alsParentId == hostId;
        }),"Death retires the body ALS host and its attached descendants during the same world tick");
        world.changeScene();check(world.effects.empty(),"Scene transition clears all character ALS and independent world effects");
        world.player.dead = false;world.player.life = ActorLife::Alive;effectFloor(world);
        effectSkill(world,101);world.advanceSingleTick();
        check(std::any_of(world.effects.begin(),world.effects.end(),[](const auto &effect) { return effect.actorAnimationHost; }),
            "A later real skill action installs a fresh body ALS host");
        std::set<int> attachedIds;
        for (const auto &effect : world.effects) if (effect.actorAnimationHost) attachedIds.insert(effect.id);
        bool more = true;
        while (more) {
            more = false;
            for (const auto &effect : world.effects) if (attachedIds.count(effect.alsParentId) && attachedIds.insert(effect.id).second)
                more = true;
        }
        world.idle();world.advanceSingleTick();
        check(std::none_of(world.effects.begin(),world.effects.end(),[&](const auto &effect) {
            return effect.actorAnimationHost || attachedIds.count(effect.id);
        }),"Action interruption removes character hosts and their live attached descendants");
        world.changeScene();effectFloor(world);effectSkill(world,101);world.advanceSingleTick();
        world.selectCharacter({0,0,0});
        check(world.effects.empty() && !world.player.animationControllerDelays,
            "Character switching cannot retain a previous character's ALS hosts or controller-delay view");
    }
    {
        // Explicit binding fixture exercises the equipment consumer without
        // claiming this title/weapon is a native skill costume qualification.
        World world(pvf,assets);world.enableExperimentalCharacters();
        world.configureAnimationClock(ani_clock::ClockPolicy::SourceDelay100);world.selectCharacter({5,0,0});dnf::enterExplicitSkillPreviewFixture(world);
        auto look = defaultCharacterAppearance(pvf,world.characterCatalog(),{5,0,0});
        const std::string path = "character/gunner/atanimation/airraidex.ani";
        const auto *body = appearanceBodyMotion(look,path);
        check(body != nullptr,"Equipment host fixture uses an actual, registered female Gunner body motion identity");
        auto definition = std::make_shared<EquipmentMotionDefinition>();
        EquipmentMotionBinding motion;motion.tag = body->resource.tag;motion.slot = body->resource.valueIndex;
        motion.occurrence = body->occurrence;motion.path = path;motion.status = EquipmentMotionStatus::Resolved;
        definition->bindings.push_back(motion);
        AppearancePart part;part.slot = "diagnostic-als-consumer";part.job = look.job;
        AppearanceLayer layer;layer.slot = part.slot;layer.order = 2500;layer.sourcePath = "diagnostic-injected-equipment-binding";
        layer.motionDefinition = definition;part.layers.push_back(layer);look.parts[part.slot] = part;
        world.setCharacterAppearance(std::move(look));effectFloor(world);effectSkill(world,101);world.advanceSingleTick();
        std::set<int> hosts;
        for (const auto &effect : world.effects) if (effect.actorAnimationHost) hosts.insert(effect.id);
        check(hosts.size() == 2,"Actual rendered equipment selection receives its own ALS host alongside the body host");
        for (const auto id : hosts) check(alsEvents(world,id) >= 2,
            "Each actual body/equipment host independently consumes its first source frame once");
        world.changeScene();check(world.effects.empty(),"Equipment-host fixture leaves no instances after scene cleanup");
        consumers.push_back({{"classification","diagnostic-injected-equipment-binding-to-real-ANI"},
            {"native-equipment-qualification-verified",false},{"host_count",hosts.size()}});
    }
    {
        EffectDummyVideo video;RendererOptions options;options.shown = false;options.vsync = false;
        Renderer renderer(assets,options);renderer.setRenderProfile(ani_render::RenderProfile::Inferred60Us1031);
        Effect effect;effect.animation = "character/swordman/effect/animation/hardattack1.ani";
        effect.born = 0;effect.expires = 1000;effect.x = 420;effect.px = 400;
        effect.y = 360;effect.py = 300;effect.z = 120;effect.pz = 80;
        renderer.begin();const auto blank = effectPixels(renderer);
        renderer.effect(effect,160,.5,12,9);const auto actual = effectPixels(renderer);
        renderer.begin();renderer.animation(effect.animation,160,398,221,effect.dir,effect.loop);
        const auto expected = effectPixels(renderer);
        check(actual == expected && actual != blank && renderer.errors.empty(),
            "Hidden SDL pixels prove effect X/Y/Z use the same interpolation phase and apply ANI/IMG offsets only once");
        renderer.begin();renderer.animation(effect.animation,160,398,231,effect.dir,effect.loop);
        check(effectPixels(renderer) != actual,"Pixel regression distinguishes the old current-tick Y/Z projection");
        effect.pz.reset();renderer.begin();renderer.effect(effect,160,.5,12,9);const auto born = effectPixels(renderer);
        renderer.begin();renderer.animation(effect.animation,160,398,201,effect.dir,effect.loop);
        check(effectPixels(renderer) == born,"A newly created effect without previous Z renders at current height");
        effect.drawSelf = false;renderer.begin();renderer.effect(effect,160,.5,12,9);
        check(effectPixels(renderer) == blank,"Invisible character ALS hosts never redraw body pixels in the world effect pass");
        RegionCatalog regions(pvf,assets);
        for (const auto policy : {ani_clock::ClockPolicy::SourceDelay100,ani_clock::ClockPolicy::Inferred60UsPercentDeadlines}) {
            Progression progression(regions);
            World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
            CharacterStore store(std::filesystem::absolute("cache/effect-coordinate-world-fixtures"));
            store.data["characters"][0] = {{"name","EffectCoordinateRegression"},{"class","atgunner"},
                {"identity",CharacterIdentity{5,0,0}.json()},{"level",1},{"skill_initialization","source-v1"}};
            store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);world.configureAnimationClock(policy);
            for (int id : {9,13,39}) {
                world.changeScene();world.releaseInputs();effectFloor(world);effectSkill(world,id);
                if(id==13)world.enqueue({world.simulationNanoseconds(),4,true});
                bool started = false, ended = false, layerPixels = false, independentPixels = false;
                size_t maximumEntities = 0;std::set<std::string> layerSources,independentSources;
                Json independentTrace = Json::array();
                for (int tick = 0; tick < 720; ++tick) {
                    world.advanceSingleTick();started |= world.experimentalRuntime()->attacking();
                    maximumEntities = std::max(maximumEntities,world.femaleGunnerDiagnostics().at("entities").size());
                    if (!world.player.skillAnimationLayers.empty()) {
                        for (const auto &layer : world.player.skillAnimationLayers) {
                            check(layer.bodyPath == world.actorAni() && !layer.source.memberSha256.empty(),
                                "Published skill appearance layer has the actual current CHR body and content identity");
                            layerSources.insert(layer.source.memberPath);
                            if (layer.synchronizedToBody && world.player.animationClock) {
                                const auto projection = assets.animation(layer.source.memberPath)->followClock(
                                    *assets.animation(world.actorAni()),*world.player.animationClock,
                                    world.player.animationClock->loop,world.player.animationControllerDelays.get());
                                check(projection.frame == world.player.animationClock->frame,
                                    "Synchronized skill appearance samples the current controller frame, preserving source long waits");
                            }
                        }
                        if (!layerPixels) {
                            renderer.begin();renderer.player(world.player,world.nowMs(),1,world.characterAppearance(),0,0,world.actorAni());
                            const auto with = effectPixels(renderer);auto without = world.player;without.skillAnimationLayers.clear();
                            renderer.begin();renderer.player(without,world.nowMs(),1,world.characterAppearance(),0,0,world.actorAni());
                            layerPixels = with != effectPixels(renderer);
                        }
                    }
                    for (const auto &visual : world.effects) if (visual.phase.rfind("female-gunner:",0) == 0 &&
                            !visual.attached && world.nowMs() >= visual.born && world.nowMs() < visual.expires) {
                        independentSources.insert(visual.resourceSource);
                        if (independentTrace.size() < 8) independentTrace.push_back({{"ms",world.nowMs()},
                            {"animation",visual.animation},{"source",visual.resourceSource},
                            {"phase",visual.phase},{"xyz",{visual.x,visual.y,visual.z}},
                            {"born",visual.born},{"expires",visual.expires},{"draw",visual.drawSelf},
                            {"elapsed",visual.animationClock ? double(visual.animationClock->elapsedMs) : -1}});
                        if (!independentPixels) {
                            renderer.begin();const auto empty = effectPixels(renderer);
                            renderer.effect(visual,world.nowMs(),1);
                            independentPixels = effectPixels(renderer) != empty;
                        }
                    }
                    if (started && !world.experimentalRuntime()->attacking()) { ended = true;break; }
                }
                check(started && ended && layerPixels && !layerSources.empty(),
                    "Actual skill-slot release draws source weapon/blade layers and naturally finishes: " + Json{
                        {"skill",id},{"policy",ani_clock::policyName(policy)},{"started",started},{"ended",ended},
                        {"layer_pixels",layerPixels},{"layer_sources",layerSources},{"ms",world.nowMs()},
                        {"actor_animation",world.actorAni()},{"renderer_errors",renderer.errors},
                        {"runtime",world.experimentalRuntime()->snapshotDiagnostics()}}.dump());
                check(maximumEntities > 0,"Actual skill release publishes gameplay entities in addition to character pixels: " + std::to_string(id));
                check(independentPixels && !independentSources.empty(),
                    "Actual release renders its independent source muzzle/OBJ visuals: " + Json{
                        {"skill",id},{"policy",ani_clock::policyName(policy)},{"pixels",independentPixels},
                        {"sources",independentSources},{"trace",independentTrace},{"maximum_entities",maximumEntities},
                        {"renderer_errors",renderer.errors},{"female_world",world.femaleGunnerDiagnostics()}}.dump());
                const auto finalState=id==13?"female_gunner_channel_recovery":"experimental_attack";
                check(world.player.animation == finalState && !world.player.skillAnimationLayers.empty(),
                    "Completed action preserves its source final/recovery pose and appearance for the completion tick: " + Json{
                        {"skill",id},{"state",world.player.animation},{"expected",finalState},
                        {"layer_count",world.player.skillAnimationLayers.size()},{"body",world.actorAni()},
                        {"runtime",world.experimentalRuntime()->snapshotDiagnostics()}}.dump());
                world.advanceSingleTick();
                check(world.player.skillAnimationLayers.empty() && renderer.errors.empty(),
                    "Following idle tick clears action-specific skill layers without removing the completion pose");
                consumers.push_back({{"classification","actual-slot-input-world-and-hidden-SDL-skill-layers"},
                    {"skill",SkillKey{5,id}.json()},{"clock_policy",ani_clock::policyName(policy)},
                    {"layer_sources",layerSources},{"independent_visual_sources",independentSources},
                    {"maximum_gameplay_entities",maximumEntities},{"character_layer_pixels",layerPixels},
                    {"independent_visual_pixels",independentPixels},
                    {"randomshoot_fire_spawn_verified",id == 9 && independentPixels},{"native_attachment_order_verified",false}});
                world.changeScene();check(world.effects.empty() && world.player.skillAnimationLayers.empty(),
                    "Scene cleanup removes actual skill appearance and independent visual instances");
            }
        }
    }
    return {{"status","pass"},{"check_count",checks.size()},{"checks",checks},{"sources",sources},{"consumers",consumers},
        {"classification","actual-world-ALS-dispatch-and-hidden-SDL-coordinate-regression"},
        {"native_1031_draw_only_coordinates","source-exe-contract"},
        {"native_1031_draw_only_retirement","unverified; inferred-single-source-clip"},
        {"original_dynamic_comparison","pending_user"}};
}
} // namespace dnf
