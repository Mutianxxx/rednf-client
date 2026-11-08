#include "dnf/debug.hpp"
#include "dnf/combat.hpp"
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
bool boundedText(const std::string &value, bool required) {
    return (!required || !value.empty()) && value.size() <= 512 &&
        value.find_first_of(std::string("\0\r\n", 3)) == std::string::npos;
}
std::string validatePayload(const DebugCommand &command) {
    switch (command.kind) {
    case DebugCommandKind::SetEnabled:
    case DebugCommandKind::SetHpLock:
    case DebugCommandKind::SetMpLock:
    case DebugCommandKind::SetNoCooldown:
    case DebugCommandKind::SetAiPaused:
    case DebugCommandKind::SetSimulationPaused:
        return command.payload.is_boolean() ? "" : "payload_must_be_boolean";
    case DebugCommandKind::SetLevelOverride:
        if (!command.payload.is_number_integer()) return "level_must_be_integer";
        if (command.payload.is_number_unsigned()) {
            const auto level = command.payload.get<uint64_t>();
            if (!level || level > uint64_t(std::numeric_limits<int>::max())) return "level_outside_integer_range";
        } else {
            const auto level = command.payload.get<int64_t>();
            if (level < 1 || level > std::numeric_limits<int>::max()) return "level_outside_integer_range";
        }
        return "";
    case DebugCommandKind::ClearLevelOverride:
    case DebugCommandKind::Reset:
    case DebugCommandKind::SingleStep:
    case DebugCommandKind::UnlockExecutableSkills:
        return command.payload.is_null() ? "" : "payload_must_be_null";
    case DebugCommandKind::SetTestIdentity:
        if(!command.payload.is_object()||!command.payload.contains("job_id")||
            !command.payload.contains("growtype")||!command.payload.contains("awakening"))
            return "identity_requires_job_growtype_awakening";
        try { (void)CharacterIdentity::fromJson(command.payload);return ""; }
        catch(const std::exception &) { return "invalid_character_identity"; }
    case DebugCommandKind::SetMonsterAiDifficulty:
        if (!command.payload.is_string()) return "monster_ai_difficulty_must_be_string";
        {
            const auto value = command.payload.get<std::string>();
            return value.size() <= 64 && value.find_first_not_of("abcdefghijklmnopqrstuvwxyz_") == std::string::npos ?
                "" : "monster_ai_difficulty_must_be_exact_source_name_or_empty";
        }
    }
    return "unknown_command";
}
Json identityCandidates(const World &world) {
    Json rows=Json::array();
    for(const auto &definition:world.characterCatalog().definitions) {
        const int job=definition.registration.id;
        const std::string jobName=!definition.growtypeNames.empty()&&definition.growtypeNames[0].is_string()?
            definition.growtypeNames[0].get<std::string>():definition.job;
        // Exact1031 loader maps runtime growtype g to source [growtype g+1].
        // A source name/stat span alone does not establish a playable branch.
        for(size_t g=0;g<definition.growtypeNames.size()&&g<6;++g) {
            if(!definition.growtypeNames[g].is_string()||definition.growtypeNames[g].get<std::string>().empty())continue;
            const auto branchName=definition.growtypeNames[g].get<std::string>();
            const CharacterStatBlock *growth=nullptr;size_t growthCount=0;
            for(const auto &block:definition.stats)
                if(block.growtype==int(g)+1&&!block.awakening&&normalize(block.tag)=="[growtype "+std::to_string(g+1)+"]")
                    {growth=&block;++growthCount;}
            for(int awakening=0;awakening<=2;++awakening) {
                const CharacterStatBlock *awakened=nullptr;size_t awakeningCount=0;
                if(awakening)for(const auto &block:definition.stats)
                    if(block.growtype==int(g)+1&&block.awakening==awakening&&normalize(block.tag)=="[awakening "+std::to_string(awakening)+"]")
                        {awakened=&block;++awakeningCount;}
                if(awakening&&!awakeningCount)continue;
                const CharacterIdentity identity{job,int(g),awakening};
                const bool legal=growthCount==1&&(!awakening||awakeningCount==1);
                const bool executable=legal&&!definition.runtimeDeferredByUser&&world.supportsCharacter(identity);
                const auto reason=!legal?"source_identity_blocks_missing_or_ambiguous":definition.runtimeDeferredByUser?
                    "runtime_deferred_by_user":!executable?"no_executable_controller_for_exact_identity":"";
                rows.push_back({{"identity",identity.json()},{"job_name",jobName},{"branch_name",branchName},
                    {"label",branchName+(awakening?" / 觉醒"+std::to_string(awakening):std::string())},
                    {"source_legal",legal},{"executable",executable},{"reason",reason},
                    {"source",{{"path",definition.source.script.path},
                        {"member_sha256",definition.source.provenance.value("member_sha256",std::string())},
                        {"growth_tag",growth?growth->tag:std::string()}, {"growth_offset",growth?Json(growth->offset):Json()},
                        {"awakening_tag",awakened?awakened->tag:std::string()},
                        {"awakening_offset",awakened?Json(awakened->offset):Json()}}},
                    {"classification","source identity mapped by exact1031 loader; executable only when registered controller supports exact identity"}});
            }
        }
    }
    return rows;
}
Json actualState(const World &world) {
    const auto candidates=identityCandidates(world);Json executable=Json::array();
    for(const auto &row:candidates)if(row.at("executable").get<bool>())executable.push_back(row);
    return {{"hp",world.player.hp},{"mp",world.player.mp},
        {"max_hp",world.player.maxHp},{"max_mp",world.player.maxMp},
        {"dead",world.player.dead},{"life",int(world.player.life)},
        {"character_level",world.characterLevel},{"active_skill",world.activeSkill()},
        {"world_ms",world.nowMs()},{"pending_ticks",world.pendingTicks()},
        {"monster_event_ai_test",world.monsterEventAiTestPolicy()},
        {"identity",world.identity().json()},{"identity_candidates",candidates},{"executable_identities",executable}};
}
} // namespace

bool DebugTarget::valid() const {
    return generation && boundedText(contentId,true) && boundedText(characterUuid,true) && boundedText(runToken,false);
}
bool DebugTarget::operator==(const DebugTarget &other) const {
    return contentId == other.contentId && characterUuid == other.characterUuid &&
        runToken == other.runToken && generation == other.generation;
}
Json DebugTarget::json() const {
    return {{"content_id",contentId},{"character_uuid",characterUuid},{"run_token",runToken},{"generation",generation}};
}
Json DebugOverrides::json() const {
    return {{"enabled",enabled},{"hp_lock",hpLock},{"mp_lock",mpLock},{"no_cooldown",noCooldown},
        {"pause_ai",pauseAi},{"level_override",level ? Json(*level) : Json()},
        {"monster_ai_difficulty",monsterAiDifficulty}};
}
bool DebugOverrides::operator==(const DebugOverrides &other) const {
    return enabled == other.enabled && hpLock == other.hpLock && mpLock == other.mpLock &&
        noCooldown == other.noCooldown && pauseAi == other.pauseAi && level == other.level &&
        monsterAiDifficulty == other.monsterAiDifficulty;
}
const char *debugCommandName(DebugCommandKind kind) {
    switch (kind) {
    case DebugCommandKind::SetEnabled: return "set_enabled";
    case DebugCommandKind::SetHpLock: return "set_hp_lock";
    case DebugCommandKind::SetMpLock: return "set_mp_lock";
    case DebugCommandKind::SetNoCooldown: return "set_no_cooldown";
    case DebugCommandKind::SetAiPaused: return "set_ai_paused";
    case DebugCommandKind::SetLevelOverride: return "set_level_override";
    case DebugCommandKind::ClearLevelOverride: return "clear_level_override";
    case DebugCommandKind::Reset: return "reset";
    case DebugCommandKind::SetSimulationPaused: return "set_simulation_paused";
    case DebugCommandKind::SingleStep: return "single_step";
    case DebugCommandKind::SetMonsterAiDifficulty: return "set_monster_ai_difficulty";
    case DebugCommandKind::SetTestIdentity: return "set_test_identity";
    case DebugCommandKind::UnlockExecutableSkills: return "unlock_executable_skills";
    }
    return "unknown";
}
const char *debugResultName(DebugResultState state) {
    switch (state) {
    case DebugResultState::Accepted: return "accepted";
    case DebugResultState::Applied: return "applied";
    case DebugResultState::Rejected: return "rejected";
    }
    return "unknown";
}
Json DebugCommand::json() const {
    return {{"request_id",requestId},{"target",target.json()},{"kind",debugCommandName(kind)},{"payload",payload}};
}
Json DebugResult::json() const {
    return {{"request_id",requestId},{"state",debugResultName(state)},{"reason",reason},
        {"applied_tick",appliedTick},{"actual",actual}};
}
Json DebugSnapshot::json() const {
    Json results = Json::array();
    for (const auto &result : recentResults) results.push_back(result.json());
    return {{"schema",1},{"target",target.json()},{"selected",selected.json()},{"effective",effective.json()},
        {"normal_level",normalLevel},{"tick",tick},{"simulation_paused",simulationPaused},
        {"pause_requested",pauseRequested},{"pending_count",pendingCount},{"revision",revision},
        {"single_step_requests",singleStepRequests},
        {"actual",actual},{"recent_results",results},
        {"persistence_scope","temporary overrides; normal progression/learning and test save isolation are owned by the application"}};
}

DebugService::DebugService(size_t queueCapacity, size_t resultCapacity)
    : queueCapacity_(queueCapacity), resultCapacity_(resultCapacity) {
    if (!queueCapacity || !resultCapacity || queueCapacity > 4096 || resultCapacity > 4096)
        throw std::invalid_argument("Invalid debug queue/result capacity");
}
uint64_t DebugService::nextRequestId() {
    issuedId_ = std::max(issuedId_,seenId_);
    if (issuedId_ == std::numeric_limits<uint64_t>::max()) throw std::overflow_error("Debug request IDs exhausted");
    return ++issuedId_;
}
void DebugService::finish(const DebugCommand &command, DebugResult result) {
    auto found = receipts_.find(command.requestId);
    if (found == receipts_.end()) receipts_.emplace(command.requestId,Receipt{command.json(),std::move(result)});
    else found->second.result = std::move(result);
    completed_.push_back(command.requestId);
    while (completed_.size() > resultCapacity_) {
        receipts_.erase(completed_.front());
        completed_.pop_front();
    }
    resultsDirty_ = true;
}
DebugResult DebugService::submit(DebugCommand command) {
    const auto existing = receipts_.find(command.requestId);
    if (existing != receipts_.end()) {
        if (existing->second.command != command.json())
            return {command.requestId,DebugResultState::Rejected,"request_id_conflict",-1,Json::object()};
        return existing->second.result;
    }
    if (!command.requestId || command.requestId <= seenId_)
        return {command.requestId,DebugResultState::Rejected,"request_id_stale_or_zero",-1,Json::object()};
    seenId_ = command.requestId;
    std::string problem = !command.target.valid() ? "invalid_target" : validatePayload(command);
    if (problem.empty() && pending_.size() >= queueCapacity_) problem = "command_queue_full";
    if (!problem.empty()) {
        DebugResult result{command.requestId,DebugResultState::Rejected,problem,-1,Json::object()};
        finish(command,result);
        return result;
    }
    DebugResult result{command.requestId,DebugResultState::Accepted,"queued_for_boundary",-1,Json::object()};
    receipts_.emplace(command.requestId,Receipt{command.json(),result});
    pending_.push_back(std::move(command));
    return result;
}
void DebugService::bindTarget(const World &world, const DebugContext &context) {
    // On a new target, retain only the overrides that World actually carried
    // across that boundary. Initial saved selections remain disabled until an
    // explicit enable request; publishing alone never activates them.
    if (bound_ && snapshot_.target != context.target) {
        if (selected_.enabled || world.debugOverrides().enabled) selected_ = world.debugOverrides();
        singleStepRequests_ = 0;
    }
    bound_ = true;
    snapshot_.target = context.target;
}
void DebugService::refreshActual(const World &world, const DebugContext &context) {
    bool changed = identityWorld_ != &world || identityCatalog_ != &world.characterCatalog() ||
        identityContent_ != context.target.contentId || !snapshot_.actual.contains("identity_candidates");
    if (!changed) for (const auto &[identity,supported] : identitySupport_)
        if (world.supportsCharacter(identity) != supported) { changed = true; break; }
    auto &actual = snapshot_.actual;
    if (changed) {
        auto candidates = identityCandidates(world);
        Json executable = Json::array();
        std::vector<std::pair<CharacterIdentity,bool>> support;
        for (const auto &row : candidates) {
            const auto identity = CharacterIdentity::fromJson(row.at("identity"));
            support.emplace_back(identity,world.supportsCharacter(identity));
            if (row.at("executable").get<bool>()) executable.push_back(row);
        }
        actual["identity_candidates"] = std::move(candidates);
        actual["executable_identities"] = std::move(executable);
        identitySupport_ = std::move(support);
        identityWorld_ = &world; identityCatalog_ = &world.characterCatalog();
        identityContent_ = context.target.contentId;
    }
    // Update live values on every requested boundary, including paused
    // commands and pending tick accumulation. Do not cache mutable world state.
    actual["hp"] = world.player.hp; actual["mp"] = world.player.mp;
    actual["max_hp"] = world.player.maxHp; actual["max_mp"] = world.player.maxMp;
    actual["dead"] = world.player.dead; actual["life"] = int(world.player.life);
    actual["character_level"] = world.characterLevel; actual["active_skill"] = world.activeSkill();
    actual["world_ms"] = world.nowMs(); actual["pending_ticks"] = world.pendingTicks();
    actual["monster_event_ai_test"] = world.monsterEventAiTestPolicy();
    actual["identity"] = world.identity().json();
}
void DebugService::publish(const World &world, const DebugContext &context) {
    bindTarget(world,context);
    snapshot_.selected = selected_;
    snapshot_.effective = world.debugOverrides();
    if (!snapshot_.effective.enabled) snapshot_.effective = {};
    snapshot_.normalLevel = context.normalLevel;
    snapshot_.tick = world.tick;
    snapshot_.simulationPaused = context.simulationPaused;
    snapshot_.pauseRequested = pauseRequested_;
    snapshot_.pendingCount = pending_.size();
    snapshot_.singleStepRequests = singleStepRequests_;
    refreshActual(world,context);
    if (resultsDirty_) {
        snapshot_.recentResults.clear();
        const size_t begin = completed_.size() > 12 ? completed_.size() - 12 : 0;
        for (size_t i = begin; i < completed_.size(); ++i)
            snapshot_.recentResults.push_back(receipts_.at(completed_[i]).result);
        resultsDirty_ = false;
    }
}
void DebugService::refresh(const World &world, const DebugContext &context) { publish(world,context); }
bool DebugService::hasEnableRequest(const DebugTarget &target) const {
    for (const auto &command : pending_)
        if (command.target == target && command.kind == DebugCommandKind::SetEnabled && command.payload == true)
            return true;
    return false;
}
bool DebugService::takeSingleStepRequest() {
    if (!singleStepRequests_) return false;
    --singleStepRequests_;
    snapshot_.singleStepRequests = singleStepRequests_;
    return true;
}
void DebugService::applyAtBoundary(World &world, const DebugContext &context) {
    // Binding/queue validation needs no full diagnostic serialization. The
    // final publish below exposes the command outcomes and current live state.
    bindTarget(world,context);
    while (!pending_.empty()) {
        const auto command = std::move(pending_.front());
        pending_.pop_front();
        DebugResult result{command.requestId,DebugResultState::Rejected,"",world.tick,Json::object()};
        const bool applicationCommand=command.kind==DebugCommandKind::SetTestIdentity||command.kind==DebugCommandKind::UnlockExecutableSkills;
        Json applicationReceipt;
        if (!context.target.valid() || command.target != context.target) result.reason = "target_generation_changed";
        else if (context.normalLevel < 1) result.reason = "normal_level_unavailable";
        else if (snapshot_.revision == std::numeric_limits<uint64_t>::max()) result.reason = "debug_revision_exhausted";
        else {
            auto candidate = selected_;
            auto pause = pauseRequested_;
            if (!candidate.enabled && command.kind != DebugCommandKind::SetEnabled &&
                command.kind != DebugCommandKind::Reset && command.kind != DebugCommandKind::SetSimulationPaused)
                result.reason = "test_mode_disabled";
            else if (command.kind == DebugCommandKind::SingleStep && !context.simulationPaused)
                result.reason = "single_step_requires_paused_simulation";
            else if (command.kind == DebugCommandKind::SingleStep && singleStepRequests_ >= 8)
                result.reason = "single_step_request_limit";
            else if(applicationCommand&&!applicationCommandHandler_)
                result.reason = "application_command_handler_unavailable";
            else {
                switch (command.kind) {
                case DebugCommandKind::SetEnabled: candidate.enabled = command.payload.get<bool>(); break;
                case DebugCommandKind::SetHpLock: candidate.hpLock = command.payload.get<bool>(); break;
                case DebugCommandKind::SetMpLock: candidate.mpLock = command.payload.get<bool>(); break;
                case DebugCommandKind::SetNoCooldown: candidate.noCooldown = command.payload.get<bool>(); break;
                case DebugCommandKind::SetAiPaused: candidate.pauseAi = command.payload.get<bool>(); break;
                case DebugCommandKind::SetLevelOverride: candidate.level = command.payload.get<int>(); break;
                case DebugCommandKind::ClearLevelOverride: candidate.level.reset(); break;
                case DebugCommandKind::SetMonsterAiDifficulty: candidate.monsterAiDifficulty = command.payload.get<std::string>(); break;
                case DebugCommandKind::SetSimulationPaused: pause = command.payload.get<bool>(); break;
                case DebugCommandKind::SingleStep: break;
                case DebugCommandKind::SetTestIdentity:
                case DebugCommandKind::UnlockExecutableSkills: break;
                case DebugCommandKind::Reset: candidate = {}; pause = false; break;
                }
                try {
                    // World preflights source growth before publishing any
                    // flags/resources. This service never steps simulation.
                    if(applicationCommand) {
                        if(command.kind==DebugCommandKind::SetTestIdentity) {
                            const auto requested=CharacterIdentity::fromJson(command.payload);
                            bool executable=false;
                            for(const auto &row:identityCandidates(world))
                                if(row.at("identity")==requested.json()&&row.at("executable").get<bool>()) {executable=true;break;}
                            if(!executable)throw std::invalid_argument("No source-legal executable controller for requested identity");
                        }
                        applicationReceipt=applicationCommandHandler_(world,command);
                    } else if (command.kind != DebugCommandKind::SetSimulationPaused && command.kind != DebugCommandKind::SingleStep)
                        world.applyDebugOverrides(candidate,context.normalLevel);
                    selected_ = candidate;
                    pauseRequested_ = pause;
                    if (!candidate.enabled || (command.kind == DebugCommandKind::SetSimulationPaused && !pause) ||
                        command.kind == DebugCommandKind::Reset) singleStepRequests_ = 0;
                    else if (command.kind == DebugCommandKind::SingleStep) ++singleStepRequests_;
                    ++snapshot_.revision;
                    result.state = DebugResultState::Applied;
                    result.reason = command.kind == DebugCommandKind::SingleStep ? "single_step_requested" : "applied_at_boundary";
                } catch (const std::exception &error) {
                    result.reason = std::string("world_rejected: ") + error.what();
                    if (result.reason.size() > 2048) result.reason.resize(2048);
                }
            }
        }
        result.actual = {{"overrides",world.debugOverrides().json()},{"pause_requested",pauseRequested_},
            {"resources",actualState(world)}};
        if(applicationCommand)result.actual["application"]=std::move(applicationReceipt);
        const bool yieldForApplication=applicationCommand&&result.state==DebugResultState::Applied;
        finish(command,std::move(result));
        // Switching the isolated identity may advance the application's target
        // generation. Re-read its context before executing any later command.
        if(yieldForApplication)break;
    }
    publish(world,context);
}
void DebugService::loadConfiguration(const Json &configuration) {
    if (!pending_.empty() || selected_.enabled || (bound_ && snapshot_.effective.enabled))
        throw std::logic_error("Load beta settings only while test mode is disabled and the queue is empty");
    if (!configuration.is_object() || !configuration.contains("schema") ||
        !configuration.at("schema").is_number_integer() || configuration.at("schema") != 1)
        throw std::invalid_argument("Unsupported beta-settings schema");
    const auto values = configuration.value("selected",Json::object());
    if (!values.is_object()) throw std::invalid_argument("Malformed beta-settings selections");
    DebugOverrides prepared;
    const auto flag = [&](const char *name) {
        if (!values.contains(name)) return false;
        if (!values.at(name).is_boolean()) throw std::invalid_argument(std::string("Invalid beta setting: ") + name);
        return values.at(name).get<bool>();
    };
    prepared.hpLock = flag("hp_lock"); prepared.mpLock = flag("mp_lock");
    prepared.noCooldown = flag("no_cooldown"); prepared.pauseAi = flag("pause_ai");
    if (values.contains("monster_ai_difficulty")) {
        DebugCommand command; command.kind = DebugCommandKind::SetMonsterAiDifficulty;
        command.payload = values.at("monster_ai_difficulty");
        if (!validatePayload(command).empty()) throw std::invalid_argument("Invalid saved monster AI difficulty");
        prepared.monsterAiDifficulty = command.payload.get<std::string>();
    }
    if (values.contains("level_override") && !values.at("level_override").is_null()) {
        DebugCommand command; command.kind = DebugCommandKind::SetLevelOverride; command.payload = values.at("level_override");
        if (!validatePayload(command).empty()) throw std::invalid_argument("Invalid saved debug level override");
        prepared.level = command.payload.get<int>();
    }
    auto preserved = configuration;
    preservedConfiguration_ = std::move(preserved);
    selected_ = prepared;
    pauseRequested_ = false;
    singleStepRequests_ = 0;
    snapshot_.selected = selected_;
    snapshot_.pauseRequested = false;
}
Json DebugService::configuration() const {
    auto result = preservedConfiguration_;
    result["schema"] = 1;
    if (!result.contains("selected") || !result["selected"].is_object()) result["selected"] = Json::object();
    auto stored = selected_; stored.enabled = false;
    result["selected"].update(stored.json());
    result["enabled"] = false;
    result["simulation_paused"] = false;
    return result;
}
} // namespace dnf
