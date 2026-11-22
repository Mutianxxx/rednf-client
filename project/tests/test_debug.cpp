#include "dnf/debug.hpp"
#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/storage.hpp"
#include <chrono>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
DebugContext debugContext() { return {{"isolated-test-content","debug-test-character","debug-test-run",1},1,true}; }
void debugFloor(World &world) {
    world.combat = true;
    world.mapWidth = 1200;
    world.walkRects = {{0,240,1200,240}};
    world.player.x = world.player.px = 560;
    world.player.y = world.player.py = 344;
}
DebugResult debugApply(DebugService &service, World &world, const DebugContext &context,
                       DebugCommandKind kind, Json payload = Json()) {
    const auto id = service.nextRequestId();
    const auto accepted = service.submit({id,context.target,kind,std::move(payload)});
    if (accepted.state != DebugResultState::Accepted) return accepted;
    service.applyAtBoundary(world,context);
    for (const auto &result : service.snapshot().recentResults) if (result.requestId == id) return result;
    throw std::runtime_error("Debug test lost its command receipt");
}
bool debugAwaitPlayerHit(World &world) {
    for (int frame = 0; frame < 240; ++frame) {
        world.advance(16666667);
        for (const auto &event : world.events) if (event.kind == "player_hit") return true;
    }
    return false;
}
void debugAttacker(World &world) {
    Actor attacker;
    attacker.id = 1; attacker.hp = attacker.maxHp = 10000;
    attacker.x = attacker.px = world.player.x + 45;
    attacker.y = attacker.py = world.player.y;
    attacker.dir = -1;
    attacker.monsterPath = "monster/goblin/goblin.mob";
    world.monsters.push_back(attacker);
}
Json debugSkillState(const World &world) {
    Json active = Json::array(), passive = Json::array();
    for (const auto &skill : world.skills) active.push_back({{"key",skill.identity().json()},{"level",skill.level}});
    for (const auto &skill : world.passives) passive.push_back({{"key",skill.key},{"level",skill.level}});
    return {{"active",active},{"passive",passive},{"ledger",world.skillState().snapshot(world.nowMs())},{"bindings",world.bindings}};
}
} // namespace

Json runDebugTests(Pvf &pvf, Assets &assets) {
    Json checks = Json::array(), samples = Json::object();
    const auto check = [&](bool condition, const char *message) {
        if (!condition) throw std::runtime_error(std::string("Beta debug: ") + message);
        checks.push_back(message);
    };
    auto context = debugContext();
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service;
        service.refresh(world,context);
        const auto before = world.snapshot();
        check(!service.snapshot().effective.enabled && !service.pauseRequested(),
            "New service and actual World start with every test override disabled");
        const auto disabled = debugApply(service,world,context,DebugCommandKind::SetHpLock,true);
        check(disabled.state == DebugResultState::Rejected && world.snapshot() == before,
            "Independent overrides cannot mutate World while the test master switch is disabled");
        auto unbound = context.target; unbound.characterUuid.clear();
        check(service.submit({service.nextRequestId(),unbound,DebugCommandKind::SetEnabled,true}).state == DebugResultState::Rejected,
            "An unbound character cannot enable test mode");
        for (const auto payload : {Json(1),Json("true"),Json(),Json::array()})
            check(service.submit({service.nextRequestId(),context.target,DebugCommandKind::SetEnabled,payload}).state == DebugResultState::Rejected,
                "Boolean commands reject coercion from numeric, string, null or array payloads");
        for (const auto payload : {Json(0),Json(-1),Json(1.5),Json(std::numeric_limits<uint64_t>::max())})
            check(service.submit({service.nextRequestId(),context.target,DebugCommandKind::SetLevelOverride,payload}).state == DebugResultState::Rejected,
                "Level command rejects nonpositive, fractional or overflowing JSON integers before narrowing");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service(1,2);
        const DebugCommand enable{service.nextRequestId(),context.target,DebugCommandKind::SetEnabled,true};
        check(service.submit(enable).state == DebugResultState::Accepted && !world.debugOverrides().enabled &&
              service.hasEnableRequest(context.target),
            "Submission queues enable without mutating World and exposes the pre-consumption save-fork requirement");
        check(service.submit(enable).state == DebugResultState::Accepted,
            "A duplicate pending request reuses its receipt rather than enqueueing again");
        auto conflict = enable; conflict.payload = false;
        check(service.submit(conflict).reason == "request_id_conflict",
            "The same request ID cannot be reused with another payload");
        check(service.submit({service.nextRequestId(),context.target,DebugCommandKind::SetMpLock,true}).reason == "command_queue_full",
            "A full bounded command queue returns an explicit rejection");
        const auto tick = world.tick;
        service.applyAtBoundary(world,context);
        const auto once = world.snapshot();
        const auto revision = service.snapshot().revision;
        check(world.debugOverrides().enabled && world.tick == tick && revision == 1 &&
              service.submit(enable).state == DebugResultState::Applied,
            "One accepted request applies once at the current paused boundary and returns its applied receipt");
        service.applyAtBoundary(world,context);
        check(world.snapshot() == once && service.snapshot().revision == revision,
            "Replaying an applied request does not repeat attribute rebuilds or resource side effects");
        for (int i = 0; i < 4; ++i) debugApply(service,world,context,DebugCommandKind::Reset);
        const auto afterEviction = world.snapshot();
        check(service.submit(enable).reason == "request_id_stale_or_zero" && world.snapshot() == afterEviction,
            "Evicted receipts remain protected by the request watermark and cannot reapply old commands");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service;
        const auto before = world.snapshot();
        service.submit({service.nextRequestId(),context.target,DebugCommandKind::SetEnabled,true});
        auto next = context; ++next.target.generation;
        service.applyAtBoundary(world,next);
        check(world.snapshot() == before && service.snapshot().recentResults.back().reason == "target_generation_changed",
            "An accepted command for a previous room generation is rejected before live mutation");
        for (int field = 0; field < 3; ++field) {
            auto foreign = next.target;
            if (field == 0) foreign.contentId = "foreign-content";
            if (field == 1) foreign.characterUuid = "other-character";
            if (field == 2) foreign.runToken = "other-run";
            service.submit({service.nextRequestId(),foreign,DebugCommandKind::SetEnabled,true});
            service.applyAtBoundary(world,next);
            check(world.snapshot() == before && service.snapshot().recentResults.back().state == DebugResultState::Rejected,
                "Content, character and run identities independently protect against cross-target debug requests");
        }
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service;
        debugFloor(world); debugAttacker(world);
        world.player.hp -= 41; world.player.mp -= 17;
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        debugApply(service,world,context,DebugCommandKind::SetHpLock,true);
        const int mp = world.player.mp;
        check(world.player.hp == world.player.maxHp && mp == world.player.maxMp - 17,
            "Enabling HP lock fills HP without changing independent MP loss");
        check(debugAwaitPlayerHit(world) && world.player.hp == world.player.maxHp &&
              world.player.mp == mp && world.player.animation == "damage1",
            "Actual source monster contact still produces the hurt response while HP lock prevents resource loss");
        // The normal hurt response grants its own brief guardUntil interval;
        // inspect damage1, not an assumption that no such protection exists.
        samples["hp_lock_contact"] = world.snapshot();
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service;
        debugFloor(world); debugAttacker(world);
        world.player.hp -= 31; world.player.mp -= 23;
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        debugApply(service,world,context,DebugCommandKind::SetMpLock,true);
        const int hp = world.player.hp;
        check(world.player.mp == world.player.maxMp && hp == world.player.maxHp - 31,
            "Enabling MP lock fills MP without changing independent HP loss");
        check(debugAwaitPlayerHit(world) && world.player.hp < hp && world.player.mp == world.player.maxMp,
            "An MP-only lock leaves actual source monster damage to HP enabled");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service;
        world.player.dead = true; world.player.life = ActorLife::Dying; world.player.hp = 0;
        const auto life = world.player.life;
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        debugApply(service,world,context,DebugCommandKind::SetHpLock,true);
        debugApply(service,world,context,DebugCommandKind::SetMpLock,true);
        debugApply(service,world,context,DebugCommandKind::SetLevelOverride,8);
        check(world.player.dead && world.player.life == life && world.player.hp == 0,
            "Resource locks and debug growth never implicitly revive or replace a dead actor lifecycle");
        const auto mp = world.player.mp;
        world.activate(1);
        check(world.activeSkill() < 0 && world.player.mp == mp && world.remainingCd(1) == 0,
            "Test resource locks do not permit a dead character to activate skills");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service;
        debugFloor(world);
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        debugApply(service,world,context,DebugCommandKind::SetMpLock,true);
        const auto expected = world.skillCosts(1);
        check(expected.consumeMp().has_value() && *expected.consumeMp() > 1,"Capacity fixture uses a real positive source skill cost");
        const int cost = *expected.consumeMp();
        // Isolated capacity boundary fixture, not an authored growth claim.
        world.player.maxMp = world.player.mp = cost - 1;
        world.activate(1);
        check(world.activeSkill() < 0 && world.player.mp == cost - 1 && world.remainingCd(1) == 0,
            "MP lock rejects a real source skill whose single cost exceeds maximum resource capacity");
        world.player.maxMp = world.player.mp = cost;
        world.activate(1);
        check(world.activeSkill() == 1 && world.player.mp == cost && world.remainingCd(1) > 0,
            "MP lock accepts an exactly affordable source cost and preserves full MP while committing normal cooldown");
        samples["capacity_source_cost"] = expected.json();
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service;
        debugFloor(world);
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        const auto cost = world.skillCosts(1);
        check(cost.consumeMp().has_value() && cost.cooldownMs().has_value() && *cost.cooldownMs() > 100,
            "Cooldown fixture resolves ordinary source MP and positive cooldown");
        world.activate(1);
        check(world.activeSkill() == 1 && world.remainingCd(1) == int(std::ceil(*cost.cooldownMs())),
            "Normal activation starts the actual source cooldown before any no-CD override");
        world.idle();
        const int mp = world.player.mp;
        world.activate(1);
        check(world.activeSkill() < 0 && world.player.mp == mp,"Normal cooldown still rejects an immediate second cast");
        debugApply(service,world,context,DebugCommandKind::SetNoCooldown,true);
        world.activate(1);
        const auto start = world.nowMs(); const int remaining = world.remainingCd(1);
        check(world.activeSkill() == 1 && world.player.mp == mp - *cost.consumeMp() && remaining > 0,
            "No-CD bypass permits another cast but retains one MP charge and its real cooldown commit");
        world.advance(16666667);
        check(remaining - world.remainingCd(1) == world.nowMs() - start,
            "Normal cooldown time advances while the no-CD override is active");
        const int cd = world.remainingCd(1); const auto tick = world.tick;
        debugApply(service,world,context,DebugCommandKind::SetNoCooldown,false);
        check(world.tick == tick && world.remainingCd(1) == cd,
            "Disabling no-CD while paused preserves the precise existing cooldown without advancing time");
        world.idle(); world.activate(1);
        check(world.activeSkill() < 0,"Disabling no-CD immediately restores the remaining normal cooldown gate");
        debugApply(service,world,context,DebugCommandKind::SetNoCooldown,true);
        world.skills[1].level = 0; world.skillState().setLearnedLevel(world.skills[1].identity(),0);
        const auto noLearnedMp = world.player.mp; const auto noLearnedCd = world.remainingCd(1);
        world.activate(1);
        check(world.activeSkill() < 0 && world.player.mp == noLearnedMp && world.remainingCd(1) == noLearnedCd,
            "No-CD never grants an unlearned skill or spends resources for its rejected request");
    }
    {
        RegionCatalog catalog(pvf,assets);
        Progression normal(catalog);
        normal.state["future_points"] = {{"earned_sp",37},{"spent_sp",11},{"earned_tp",4}};
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        world.applyEquipment(normal);
        DebugService service;
        const auto normalBefore = normal.state, skillsBefore = debugSkillState(world);
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        debugApply(service,world,context,DebugCommandKind::SetLevelOverride,10);
        check(world.characterLevel == 10 && normal.state == normalBefore && debugSkillState(world) == skillsBefore,
            "Debug set-level changes actual source attributes without touching normal XP, point fields, learned skills or bindings");
        world.applyEquipment(normal);
        check(world.characterLevel == 10,"Real equipment synchronization retains the selected effective debug level");
        world.player.hp = world.player.maxHp; world.player.mp = world.player.maxMp;
        debugApply(service,world,context,DebugCommandKind::ClearLevelOverride);
        check(world.characterLevel == normal.level() && world.player.hp == world.player.maxHp &&
              world.player.mp == world.player.maxMp && normal.state == normalBefore,
            "Clearing the override restores normal source limits and clamps resources without issuing progression rewards");
        const auto beforeInvalid = world.snapshot(); const auto revision = service.snapshot().revision;
        const auto rejected = debugApply(service,world,context,DebugCommandKind::SetLevelOverride,100);
        check(rejected.state == DebugResultState::Rejected && world.snapshot() == beforeInvalid &&
              service.snapshot().revision == revision,
            "A level outside the supported growth policy fails all preflight before publishing resources, flags or revision");
        debugApply(service,world,context,DebugCommandKind::SetLevelOverride,8);
        const auto directory = std::filesystem::path("cache/tests/beta-debug") /
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
        CharacterStore store(directory);
        store.data["characters"][0] = {{"name","DebugLedgerIsolation"},{"class","swordman"},{"level",normal.level()},{"weapon",0}};
        store.capture(0,world,normal);
        check(store.data["characters"][0]["level"] == normal.level() &&
              store.data["characters"][0]["progression"] == normalBefore,
            "Character capture keeps normal progression authority instead of writing the effective debug level");
        check(debugSkillState(world) == skillsBefore,"Debug growth and capture leave the normal learned-skill ledger untouched");
        samples["normal_progression_before"] = normalBefore;
        samples["debug_level_snapshot"] = service.snapshot().json();
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service;
        debugFloor(world); debugAttacker(world);
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        debugApply(service,world,context,DebugCommandKind::SetAiPaused,true);
        const auto start = world.monsters.front().x;
        for (int i = 0; i < 30; ++i) world.advance(16666667);
        check(world.monsters.front().x == start && world.monsters.front().animation == "stay" && world.tick == 30,
            "AI pause suppresses decisions while the fixed world simulation continues");
        world.diagnosticHit(1,1,0,0,1,{world.player.x,world.player.y,50});
        const int hurtHp = world.monsters.front().hp;
        for (int i = 0; i < 30; ++i) world.advance(16666667);
        check(hurtHp < 10000 && world.monsters.front().hp == hurtHp && world.tick == 60,
            "Paused AI remains a valid damage target and continues its regular world lifecycle");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        DebugService service;
        debugFloor(world);
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        world.activate(1); world.idle();
        const auto tick = world.tick; const int cd = world.remainingCd(1);
        const auto random = world.randomStreams().snapshot();
        debugApply(service,world,context,DebugCommandKind::SetSimulationPaused,true);
        debugApply(service,world,context,DebugCommandKind::SetAiPaused,true);
        debugApply(service,world,context,DebugCommandKind::SetLevelOverride,2);
        check(service.pauseRequested() && world.tick == tick && world.remainingCd(1) == cd &&
              world.randomStreams().snapshot() == random,
            "Paused management can change settings and source growth without ticking cooldown, world or random streams");
        auto running = context; running.simulationPaused = false;
        check(debugApply(service,world,running,DebugCommandKind::SingleStep).state == DebugResultState::Rejected,
            "Single-step is rejected while the supplied simulation boundary is running");
        check(debugApply(service,world,context,DebugCommandKind::SingleStep).state == DebugResultState::Applied && world.tick == tick,
            "Single-step management records one request without advancing simulation inside the service");
        check(service.takeSingleStepRequest() && !service.takeSingleStepRequest(),
            "One accepted single-step request can be consumed exactly once");
        world.advanceSingleTick();
        check(world.tick == tick + 1 && cd - world.remainingCd(1) == world.nowMs(),
            "The application-facing single-tick API advances exactly one ordinary tick and its normal cooldown");
        for (int i = 0; i < 8; ++i)
            check(debugApply(service,world,context,DebugCommandKind::SingleStep).state == DebugResultState::Applied,
                "Paused single-step requests are accepted up to their explicit small bound");
        check(debugApply(service,world,context,DebugCommandKind::SingleStep).reason == "single_step_request_limit",
            "Single-step request overflow is rejected instead of growing an unbounded backlog");
        auto next = context; ++next.target.generation; service.refresh(world,next);
        check(!service.takeSingleStepRequest(),"A target generation change cancels old unconsumed single-step requests");
    }
    {
        DebugService service;
        const Json saved = {{"schema",1},{"enabled",true},{"simulation_paused",true},{"future_setting",{{"value",71}}},
            {"selected",{{"enabled",true},{"hp_lock",true},{"mp_lock",true},{"no_cooldown",true},
                         {"pause_ai",true},{"level_override",9},{"future_selection","retain"}}}};
        service.loadConfiguration(saved);
        World world(pvf,assets,WorldRules::BetaFoundationV1);
        auto selection = context; selection.target.characterUuid.clear();
        service.refresh(world,selection);
        service.refresh(world,context);
        check(!service.snapshot().selected.enabled && !service.snapshot().effective.enabled && !service.pauseRequested() &&
              !world.debugOverrides().hpLock && world.characterLevel == 1,
            "Reloading beta settings through selection/character binding retains choices but never silently enables cheats, level override or world pause");
        const auto roundTrip = service.configuration();
        check(roundTrip["enabled"] == false && roundTrip["selected"]["enabled"] == false &&
              roundTrip["simulation_paused"] == false && roundTrip["future_setting"] == saved["future_setting"] &&
              roundTrip["selected"]["future_selection"] == "retain",
            "Independent beta-settings serialization forces disabled startup and preserves unknown future fields");
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        check(world.debugOverrides().enabled && world.debugOverrides().hpLock && world.characterLevel == 9,
            "Only an explicit queued enable applies previously selected beta settings to the actual World");
        const auto before = service.configuration();
        bool rejected = false;
        try { service.loadConfiguration(saved); } catch (const std::exception &) { rejected = true; }
        check(rejected && service.configuration() == before,"Settings cannot be reloaded underneath active test overrides");
        debugApply(service,world,context,DebugCommandKind::SetEnabled,false);
        check(!service.snapshot().effective.hpLock && !service.snapshot().effective.level &&
              service.snapshot().selected.hpLock && service.snapshot().selected.level == 9 && world.characterLevel == 1,
            "Disabling the master switch removes effective overrides while retaining separately selected settings");
        debugApply(service,world,context,DebugCommandKind::Reset);
        check(world.debugOverrides() == DebugOverrides{} && !service.pauseRequested(),
            "Reset removes all effective overrides and pause requests through the same confirmed command boundary");
        auto malformed = saved; malformed["selected"]["hp_lock"] = 1;
        const auto disabledSettings = service.configuration(); rejected = false;
        try { service.loadConfiguration(malformed); } catch (const std::exception &) { rejected = true; }
        check(rejected && service.configuration() == disabledSettings,"Malformed saved settings fail before replacing retained selections");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);DebugService service;
        service.refresh(world,context);
        const auto disabled=debugApply(service,world,context,DebugCommandKind::SetMonsterAiDifficulty,"easy");
        check(disabled.reason=="test_mode_disabled" && world.debugOverrides().monsterAiDifficulty.empty(),
            "Source monster AI selection requires the explicit test master switch");
        for(const auto &payload:{Json(1),Json(),Json("Normal"),Json("../easy"),Json(std::string(65,'a'))})
            check(service.submit({service.nextRequestId(),context.target,DebugCommandKind::SetMonsterAiDifficulty,payload}).state==DebugResultState::Rejected,
                "Exact source difficulty commands reject coercion, aliases, paths and excessive strings");
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        const auto selection=debugApply(service,world,context,DebugCommandKind::SetMonsterAiDifficulty,"easy");
        world.refreshExplorationMonsterEventAiTestPolicy();
        check(selection.state==DebugResultState::Applied && world.debugOverrides().monsterAiDifficulty=="easy" &&
            world.monsterEventAiState().at("bindings").empty() &&
            world.monsterEventAiTestPolicy().at("state")=="ordinary_scene_policy_disabled",
            "An exact accepted difficulty remains disabled in ordinary scenes without inferring a dungeon difficulty");
        const auto saved=service.configuration();DebugService loaded;World restarted(pvf,assets,WorldRules::BetaFoundationV1);
        loaded.loadConfiguration(saved);loaded.refresh(restarted,context);
        check(!loaded.snapshot().selected.enabled && loaded.snapshot().selected.monsterAiDifficulty=="easy" &&
            saved.at("selected").at("enabled")==false,
            "Saved difficulty selection is retained with disabled startup and cannot activate Event.ai by loading settings");
        auto bad=saved;bad["selected"]["monster_ai_difficulty"]=false;
        const auto before=loaded.configuration();bool rejected=false;
        try {loaded.loadConfiguration(bad);}catch(const std::exception &) {rejected=true;}
        check(rejected && loaded.configuration()==before,"Malformed saved AI selection fails before replacing disabled configuration");
        auto invalid=world.debugOverrides();invalid.monsterAiDifficulty="../easy";
        const auto old=world.debugOverrides();rejected=false;
        try {world.applyDebugOverrides(invalid,context.normalLevel);}catch(const std::exception &) {rejected=true;}
        check(rejected && world.debugOverrides()==old,"Direct World debug application also validates exact difficulty names before publishing overrides");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);DebugService service;
        service.refresh(world,context);
        const auto initialCandidates=service.snapshot().actual.at("identity_candidates");
        const auto unchanged=service.snapshot().json();
        service.refresh(world,context);
        check(service.snapshot().json()==unchanged,"Repeated diagnostics preserve identical values and command receipts");
        world.enableExperimentalCharacters();service.refresh(world,context);
        check(service.snapshot().actual.at("identity_candidates")!=initialCandidates,
            "Enabling registered controllers invalidates cached source identity rows on the same World and target");
        world.player.hp-=1;service.refresh(world,context);
        check(service.snapshot().actual.at("hp")==world.player.hp,
            "A paused resource change remains visible while immutable identity rows are cached");
        const auto &state=service.snapshot().actual;
        check(state.at("identity")==world.identity().json()&&!state.at("executable_identities").empty(),
            "Debug actual state publishes current identity and source-legal executable identities");
        bool sawSourceOnly=false,sawGunner=false;
        for(const auto &row:state.at("identity_candidates")) {
            const auto identity=CharacterIdentity::fromJson(row.at("identity"));
            if(row.at("executable").get<bool>())
                check(row.at("source_legal").get<bool>()&&world.supportsCharacter(identity),
                    "Every executable UI identity is source-legal and has its exact registered runtime controller");
            else sawSourceOnly|=!row.at("reason").get<std::string>().empty();
            sawGunner|=identity==CharacterIdentity{5,0,0}&&row.at("executable").get<bool>();
        }
        check(sawSourceOnly&&sawGunner,"Source-only branches retain diagnostics while the actual base female Gunner is selectable");
        for(const auto &payload:{Json(),Json::array(),Json::object(),Json{{"job_id",0},{"growtype",-1},{"awakening",0}},
                                 Json{{"job_id",0},{"growtype",1.5},{"awakening",0}},
                                 Json{{"job_id",std::numeric_limits<uint64_t>::max()},{"growtype",0},{"awakening",0}}})
            check(service.submit({service.nextRequestId(),context.target,DebugCommandKind::SetTestIdentity,payload}).state==DebugResultState::Rejected,
                "Test identity commands require all three valid integral source identity fields before queueing");
        check(service.submit({service.nextRequestId(),context.target,DebugCommandKind::UnlockExecutableSkills,true}).state==DebugResultState::Rejected,
            "Executable-skill unlock accepts only a null command payload");
        const auto initial=world.snapshot();
        auto result=debugApply(service,world,context,DebugCommandKind::SetTestIdentity,CharacterIdentity{5,0,0}.json());
        check(result.reason=="test_mode_disabled"&&world.snapshot()==initial,
            "Identity switching cannot run while the explicit test master switch is disabled");
        debugApply(service,world,context,DebugCommandKind::SetEnabled,true);
        result=debugApply(service,world,context,DebugCommandKind::UnlockExecutableSkills);
        check(result.reason=="application_command_handler_unavailable",
            "An enabled test command explicitly rejects a missing application isolation handler");
        int calls=0;Json received;
        service.setApplicationCommandHandler([&](World &actual,const DebugCommand &command) {
            ++calls;received=command.json();
            if(command.kind==DebugCommandKind::SetTestIdentity) {
                const auto flags=actual.debugOverrides();
                actual.selectCharacter(CharacterIdentity::fromJson(command.payload));
                actual.applyDebugOverrides(flags,context.normalLevel);
            }
            return Json{{"receipt_kind",debugCommandName(command.kind)},{"actual_identity",actual.identity().json()},{"callback_count",calls}};
        });
        const auto applyId=service.nextRequestId();
        const DebugCommand apply{applyId,context.target,DebugCommandKind::SetTestIdentity,CharacterIdentity{5,0,0}.json()};
        check(service.submit(apply).state==DebugResultState::Accepted&&calls==0&&world.identity()==CharacterIdentity{},
            "Selecting a valid test identity only queues the application callback until a confirmed boundary");
        const auto pendingId=service.nextRequestId();
        service.submit({pendingId,context.target,DebugCommandKind::UnlockExecutableSkills,Json()});
        service.applyAtBoundary(world,context);
        check(calls==1&&world.identity()==CharacterIdentity{5,0,0}&&service.snapshot().pendingCount==1&&
              service.snapshot().actual.at("identity")==world.identity().json()&&world.debugOverrides().enabled,
            "Identity callback commits actual World state and yields before later commands can use an old application generation");
        const auto applied=service.submit(apply);
        check(applied.state==DebugResultState::Applied&&calls==1&&
              applied.actual.at("application").at("actual_identity")==world.identity().json()&&received.at("payload")==apply.payload,
            "Application receipt is preserved verbatim and replay cannot repeat identity mutations");
        auto changed=context;++changed.target.generation;service.applyAtBoundary(world,changed);
        check(calls==1&&service.snapshot().recentResults.back().reason=="target_generation_changed",
            "Commands behind a successful identity switch revalidate the application target before executing");
        result=debugApply(service,world,changed,DebugCommandKind::UnlockExecutableSkills);
        check(result.state==DebugResultState::Applied&&calls==2&&
              result.actual.at("application").at("receipt_kind")=="unlock_executable_skills",
            "Executable-skill unlock is dispatched once and reports the application's actual receipt");
        bool userPartialBranch=false;
        for(const auto &row:world.controllerCoverage())
            if(row.at("identity")==CharacterIdentity{0,1,0}.json())
                userPartialBranch=row.at("readiness")=="user_advancement_partial"&&
                    row.at("executable").get<bool>()&&!row.at("execution_complete").get<bool>()&&
                    !row.at("native_confirmed").get<bool>();
        check(userPartialBranch&&world.supportsCharacter({0,1,0}),
            "The user GSD source branch has an explicit partial adapter and retains incomplete/native-unverified status");
        result=debugApply(service,world,changed,DebugCommandKind::SetTestIdentity,CharacterIdentity{0,1,2}.json());
        check(result.state==DebugResultState::Rejected&&calls==2,
            "An unsupported second awakening cannot reach the application callback even when a first-stage user adapter exists");
        debugApply(service,world,changed,DebugCommandKind::SetHpLock,true);
        check(calls==2&&world.debugOverrides().hpLock,"Ordinary override commands retain the existing World transaction and bypass application callbacks");
        service.setApplicationCommandHandler([](World &,const DebugCommand &)->Json {throw std::runtime_error("isolated branch preflight failed");});
        result=debugApply(service,world,changed,DebugCommandKind::UnlockExecutableSkills);
        check(result.state==DebugResultState::Rejected&&result.reason.find("isolated branch preflight failed")!=std::string::npos,
            "Application preflight failures remain rejected receipts with a concrete diagnostic");
        samples["application_commands"]=service.snapshot().json();
    }
    return {{"status","pass"},{"checks",checks},{"count",checks.size()},{"samples",samples},
        {"scope","Actual command/World/resource/cooldown/growth consumers; no SDL window creation, frontend play or original-client parity claim"},
        {"application_checks_remaining",{"dual-window focus/DPI and hide routing", "normal/test store branch lifecycle and reward isolation"}}};
}
} // namespace dnf
