#include "dnf/act_runtime.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <tuple>

namespace dnf {
namespace {
template<class... T> struct Overload : T... { using T::operator()...; };
template<class... T> Overload(T...) -> Overload<T...>;
uint64_t addChecked(uint64_t a, uint64_t b, const char *what) {
    if (b > std::numeric_limits<uint64_t>::max() - a) throw std::runtime_error(what);
    return a + b;
}
uint64_t multiplyChecked(uint64_t a, uint64_t b, const char *what) {
    if (a && b > std::numeric_limits<uint64_t>::max() / a) throw std::runtime_error(what);
    return a * b;
}
uint64_t unsignedNumber(const Json &value, const char *what) {
    if ((!value.is_number_integer() && !value.is_number_unsigned()) ||
        (value.is_number_integer() && !value.is_number_unsigned() && value.get<int64_t>() < 0))
        throw std::invalid_argument(what);
    return value.get<uint64_t>();
}
int integerNumber(const Json &value, const char *what) {
    if (!value.is_number_integer()) throw std::invalid_argument(what);
    if (value.is_number_unsigned()) {
        const auto number = value.get<uint64_t>();
        if (number > uint64_t(std::numeric_limits<int>::max())) throw std::invalid_argument(what);
        return int(number);
    }
    const auto number = value.get<int64_t>();
    if (number < std::numeric_limits<int>::min() || number > std::numeric_limits<int>::max())
        throw std::invalid_argument(what);
    return int(number);
}
double finiteNumber(const Json &value, const char *what) {
    if (!value.is_number()) throw std::invalid_argument(what);
    const double number = value.get<double>();
    if (!std::isfinite(number)) throw std::invalid_argument(what);
    return number;
}
std::string stringValue(const Json &value, const char *what, bool allowEmpty = false) {
    if (!value.is_string()) throw std::invalid_argument(what);
    auto text = value.get<std::string>();
    if (!allowEmpty && text.empty()) throw std::invalid_argument(what);
    return text;
}
std::string digestJson(const Json &value) {
    const auto text = value.dump();
    return sha256(Bytes(text.begin(), text.end()));
}
Json vectorJson(ActVec3 value) { return Json::array({value.x, value.y, value.z}); }
Json coordinatesJson(const ActCoordinates &value) {
    return {{"position", vectorJson(value.value)}, {"use_owner_base", value.useOwnerBase},
            {"use_map_position", value.useMapPosition}, {"use_owner_direction", value.useOwnerDirection}};
}
Json selectorJson(const ActSelector &value) {
    return {{"kind", int(value.kind)}, {"saved_slot", value.savedSlot}};
}
Json callJson(const ActBehaviorCall &call) {
    return {{"kind", int(call.kind)}, {"recipient", int(call.recipient)},
            {"saved_slot", call.savedSlot}, {"behavior", call.behavior}, {"delay_ms", call.delayMs},
            {"source_offset", call.source.byteOffset}, {"source_length", call.source.byteLength},
            {"source_ordinal", call.source.ordinal}, {"source_scope", call.source.scope}};
}
Json entityJson(const ActEntityView &entity) {
    Json successes = Json::array();
    for (auto handle : entity.lastAttackSuccesses) successes.push_back(handle.json());
    return {{"handle", entity.handle.json()}, {"target", entity.target.json()},
            {"last_attacker", entity.lastAttacker.json()}, {"last_attack_success", entity.lastAttackSuccess.json()},
            {"summon_master", entity.summonMaster.json()}, {"last_attack_successes", successes},
            {"kind", int(entity.kind)}, {"position", vectorJson(entity.position)},
            {"team", entity.team}, {"direction", entity.direction}, {"hp", entity.hp},
            {"mp", entity.mp}, {"level", entity.level}, {"alive", entity.alive}};
}
void receiptJsonBounds(const Json &value, size_t depth, size_t &nodes, size_t &bytes) {
    if (depth > ActEventReceiptBudget::maximumJsonDepth ||
        ++nodes > ActEventReceiptBudget::maximumReceiptBytes)
        throw std::invalid_argument("ACT event receipt JSON depth/node budget exceeded");
    const auto charge = [&](size_t count) {
        if (count > ActEventReceiptBudget::maximumReceiptBytes - bytes)
            throw std::invalid_argument("ACT event receipt JSON byte budget exceeded");
        bytes += count;
    };
    charge(1);
    if (value.is_string()) charge(value.get_ref<const std::string &>().size());
    else if (value.is_object()) {
        for (auto it = value.begin(); it != value.end(); ++it) {
            charge(it.key().size()); receiptJsonBounds(it.value(), depth + 1, nodes, bytes);
        }
    } else if (value.is_array()) {
        for (const auto &child : value) receiptJsonBounds(child, depth + 1, nodes, bytes);
    } else if (value.is_number_float()) {
        if (!std::isfinite(value.get<double>())) throw std::invalid_argument("Non-finite ACT event receipt number");
    } else if (!value.is_null() && !value.is_boolean() && !value.is_number_integer() && !value.is_number_unsigned())
        throw std::invalid_argument("Unsupported ACT event receipt JSON value");
}
size_t receiptBytes(const Json &value) {
    size_t nodes = 0, bytes = 0;
    receiptJsonBounds(value, 0, nodes, bytes);
    const auto encoded = value.dump(); // Bounded preflight runs before escaping/encoding.
    if (encoded.size() > ActEventReceiptBudget::maximumReceiptBytes)
        throw std::invalid_argument("ACT event receipt encoded byte budget exceeded");
    return encoded.size();
}
bool receiptBool(const Json &value) {
    if (!value.is_boolean()) throw std::invalid_argument("Invalid ACT event receipt boolean");
    return value.get<bool>();
}
ActEntityView receiptEntity(const Json &value) {
    ActEntityView out;
    out.handle = EntityHandle::fromJson(value.at("handle"));
    out.target = EntityHandle::fromJson(value.at("target"));
    out.lastAttacker = EntityHandle::fromJson(value.at("last_attacker"));
    out.lastAttackSuccess = EntityHandle::fromJson(value.at("last_attack_success"));
    out.summonMaster = EntityHandle::fromJson(value.at("summon_master"));
    const auto kind = integerNumber(value.at("kind"), "Invalid ACT event entity kind");
    if (!out.handle || kind < 0 || kind > int(ActEntityKind::Passive))
        throw std::invalid_argument("Invalid ACT event snapshot entity identity/kind");
    out.kind = ActEntityKind(kind);
    const auto &position = value.at("position");
    if (!position.is_array() || position.size() != 3) throw std::invalid_argument("Invalid ACT event snapshot position");
    out.position = {finiteNumber(position[0], "Invalid ACT event X"), finiteNumber(position[1], "Invalid ACT event Y"),
                    finiteNumber(position[2], "Invalid ACT event Z")};
    out.team = integerNumber(value.at("team"), "Invalid ACT event team");
    out.direction = integerNumber(value.at("direction"), "Invalid ACT event direction");
    out.hp = integerNumber(value.at("hp"), "Invalid ACT event HP");
    out.mp = integerNumber(value.at("mp"), "Invalid ACT event MP");
    out.level = integerNumber(value.at("level"), "Invalid ACT event level");
    out.alive = receiptBool(value.at("alive"));
    if ((out.direction != -1 && out.direction != 1) || out.hp < 0 || out.mp < 0 || out.level < 0)
        throw std::invalid_argument("Invalid ACT event entity direction/resources/level");
    const auto &successes = value.at("last_attack_successes");
    if (!successes.is_array() || successes.size() > ActEventReceiptBudget::maximumSnapshotSuccesses)
        throw std::invalid_argument("ACT event snapshot success-list budget exceeded");
    for (const auto &handle : successes) out.lastAttackSuccesses.push_back(EntityHandle::fromJson(handle));
    if (entityJson(out).dump() != value.dump())
        throw std::invalid_argument("Unknown or noncanonical ACT event entity payload fields");
    return out;
}
ActEventContext receiptEvent(const Json &payload, uint64_t id) {
    receiptBytes(payload);
    ActEventContext out; out.eventId = id;
    const auto kind = integerNumber(payload.at("kind"), "Invalid ACT event receipt kind");
    if (!id || kind < 0 || kind > int(ActEventKind::MoveCollision))
        throw std::invalid_argument("Invalid ACT event receipt identity/kind");
    out.kind = ActEventKind(kind);
    out.subject = EntityHandle::fromJson(payload.at("subject"));
    out.other = EntityHandle::fromJson(payload.at("other"));
    out.stuck = receiptBool(payload.at("stuck")); out.metadata = payload.at("metadata");
    if (payload.contains("subject_snapshot")) out.subjectSnapshot = receiptEntity(payload.at("subject_snapshot"));
    if (!out.subject || (out.subjectSnapshot && out.subjectSnapshot->handle != out.subject))
        throw std::invalid_argument("ACT event receipt subject/snapshot identity differs");
    return out;
}
Json payloadJson(const ActCommandPayload &payload) {
    return std::visit(Overload{
        [](const ActSetSpeed &v) -> Json {
            Json result = {{"kind", "set_speed"}, {"direction_basis", int(v.direction)}};
            if (v.x) result["x"] = *v.x;
            if (v.y) result["y"] = *v.y;
            if (v.z) result["z"] = *v.z;
            return result;
        },
        [](const ActSpawn &v) -> Json {
            return {{"kind", "spawn_passive_object"}, {"index", v.objectIndex}, {"level", v.level},
                    {"particle", v.particle}, {"coordinates", coordinatesJson(v.position)},
                    {"following_target", v.followingTarget}, {"movable_position_only", v.movablePositionOnly},
                    {"no_effect", v.noEffect}};
        },
        [](const ActParticle &v) -> Json { return {{"kind", "particle"}, {"path", v.path}, {"offset", vectorJson(v.offset)}}; },
        [](const ActTeleport &v) -> Json { return {{"kind", "teleport"}, {"coordinates", coordinatesJson(v.position)}, {"move_owner", v.moveOwner}}; },
        [](const ActSetDirection &v) -> Json { return {{"kind", "set_direction"}, {"value", int(v.value)}}; },
        [](const ActDestroy &v) -> Json { return {{"kind", "destroy"}, {"force", v.force}}; },
        [](const ActSound &v) -> Json { return {{"kind", "sound"}, {"tag", v.tag}}; },
        [](const ActSpeech &v) -> Json { return {{"kind", "speech"}, {"text", v.text}}; },
        [](const ActAttackRect &v) -> Json { return {{"kind", "attack_rect"}, {"mode", int(v.mode)}}; },
        [](const ActChangeAttackInfo &v) -> Json { return {{"kind", "change_attack_info"}, {"path", v.path}, {"default", v.useDefault}}; },
        [](const ActTriggerControl &v) -> Json { return {{"kind", "trigger_control"}, {"trigger", v.trigger}, {"mode", int(v.mode)}}; },
        [](const ActDeferredCall &v) -> Json { return {{"kind", "deferred_call"}, {"target_program", v.targetProgram}, {"call", callJson(v.call)}}; },
        [](const ActCleanup &v) -> Json { return {{"kind", "cleanup_owned"}, {"reason", v.reason}}; },
        [](const ActSetDamageCheck &v) -> Json { return {{"kind","set_damage_check"},{"enabled",v.enabled},{"interval_ms",v.intervalMs}}; }
    }, payload);
}
bool validPolicy(const ActSemanticPolicy &policy) {
    return !policy.id.empty() && policy.maximumInstructions && policy.maximumCommands &&
           policy.maximumPending && policy.maximumRememberedEvents && policy.maximumFrameBoundaries &&
           (policy.frameEvaluation == ActFrameEvaluation::OncePerRangeVisit || policy.frameEvaluation == ActFrameEvaluation::EverySimulationStep);
}
struct CompileFailure : std::runtime_error {
    size_t field;
    std::string code;
    CompileFailure(size_t index, std::string reason, std::string detail)
        : std::runtime_error(std::move(detail)), field(index), code(std::move(reason)) {}
};

class Compiler {
    const Script &script_;
    const ActCompileContext &context_;
    std::shared_ptr<ActProgram> program_ = std::make_shared<ActProgram>();
    size_t syntaxErrors_ = 0;
    bool closureKnown_ = true;
    std::map<size_t, ActResolvedResource> animations_;
    std::string tag(size_t at) const { return normalize(script_.fields.at(at).tag); }
    SourceRef source(size_t at, const std::string &scope = "") const {
        auto ref = program_->source;
        if (at < script_.fields.size()) {
            ref.byteOffset = script_.fields[at].offset;
            const auto end = at + 1 < script_.fields.size() ? script_.fields[at + 1].offset : script_.rawBytes.size();
            ref.byteLength = end >= ref.byteOffset ? end - ref.byteOffset : 0;
            ref.ordinal = at;
        }
        ref.scope = scope;
        return ref;
    }
    [[noreturn]] void fail(size_t at, const std::string &code, const std::string &detail) const {
        throw CompileFailure(at, code, detail);
    }
    void require(bool condition, size_t at, const std::string &code, const std::string &message) const {
        if (!condition) fail(at, code, message);
    }
    void count(size_t at, size_t expected) const {
        require(script_.fields.at(at).values.size() == expected, at, "operand_count",
                script_.fields.at(at).tag + " requires " + std::to_string(expected) + " operands");
    }
    void report(size_t at, const std::string &code, const std::string &message, bool syntax = true) {
        program_->diagnostics.push_back({code, message, source(at), true});
        if (syntax) ++syntaxErrors_;
    }
    template<class F> void checked(size_t at, F function) {
        try { function(); }
        catch (const CompileFailure &error) { report(error.field, error.code, error.what()); }
        catch (const std::exception &error) { report(at, "invalid_operand", error.what()); }
    }
    ActResolvedResource dependency(size_t at, ActResourceKind kind, std::string literal, int index = -1) {
        ActResourceRequest request{kind, source(at), std::move(literal), index};
        ActResolvedResource resolved;
        if (!context_.resources) resolved.diagnostic = "No ACT resource resolver installed";
        else {
            try { resolved = context_.resources->resolve(request); }
            catch (const std::exception &error) { resolved.diagnostic = error.what(); }
            catch (...) { resolved.diagnostic = "ACT resource resolver raised a non-standard exception"; }
        }
        if (kind != ActResourceKind::Sound && !resolved.transitiveClosureKnown) {
            closureKnown_ = false;
            resolved.runtimeSupported = false;
            if (!resolved.diagnostic.empty()) resolved.diagnostic += "; ";
            resolved.diagnostic += "Resource's transitive ACT/ANI/ALS/ATK/PTL/audio closure was not declared";
        }
        program_->dependencies.push_back({request, resolved.source, resolved.found,
                                         resolved.runtimeSupported, resolved.diagnostic});
        if (!resolved.found || !resolved.runtimeSupported)
            program_->diagnostics.push_back({!resolved.found ? "missing_resource" : "missing_resource_consumer",
                std::string(actResourceKindName(kind)) + ": " +
                (index >= 0 ? std::to_string(index) : request.literal) + ": " + resolved.diagnostic,
                request.origin, true});
        for (auto nested : resolved.transitive) {
            if (nested.request.origin.memberPath.empty()) nested.request.origin = request.origin;
            if (!nested.found || !nested.runtimeSupported)
                program_->diagnostics.push_back({"missing_transitive_dependency",
                    std::string(actResourceKindName(nested.request.kind)) + ": " + nested.request.literal +
                    ": " + nested.diagnostic, nested.request.origin, true});
            program_->dependencies.push_back(std::move(nested));
        }
        return resolved;
    }
    // Independent source sweep keeps known SOUND/PTL/spawn references visible
    // even if an earlier unknown instruction prevents a block from compiling.
    void collectDependencies() {
        bool spawn = false;
        for (size_t i = 0; i < script_.fields.size(); ++i) {
            const auto name = tag(i);
            const auto &values = script_.fields[i].values;
            checked(i, [&] {
                if (name == "[create passiveobject]") spawn = true;
                else if (name == "[/create passiveobject]") spawn = false;
                else if (name == "[base ani]") {
                    count(i, 1); animations_[i] = dependency(i, ActResourceKind::Animation,
                        stringValue(values[0], "BASE ANI path must be a nonempty string"));
                } else if (name == "[sub ani]" || name == "[sub ani with xy]") {
                    const size_t stride = name == "[sub ani]" ? 3 : 5;
                    require(values.size() % stride == 0, i, "sub_ani_tuple", "Incomplete SUB ANI tuple");
                    for (size_t k = 0; k < values.size(); k += stride)
                        dependency(i, ActResourceKind::Animation, stringValue(values[k], "Invalid SUB ANI path"));
                } else if (name == "[sound]" || name == "[sound probability]") {
                    // Behavior SOUND has only a tag; MOTION SOUND has tag/frame tuples.
                    const size_t stride = name == "[sound probability]" ? 3 : values.size() == 1 ? 1 : 2;
                    require(!values.empty() && values.size() % stride == 0, i, "sound_tuple", "Incomplete SOUND tuple");
                    for (size_t k = 0; k < values.size(); k += stride)
                        dependency(i, ActResourceKind::Sound, stringValue(values[k], "Invalid SOUND tag"));
                } else if (name == "[particle]") {
                    require(!values.empty(), i, "particle_path", "PARTICLE has no resource path");
                    dependency(i, ActResourceKind::Particle, stringValue(values[0], "Invalid PARTICLE path"));
                } else if (spawn && name == "[index]") {
                    count(i, 1);
                    const int index = integerNumber(values[0], "Invalid passive object index");
                    require(index >= 0, i, "object_index", "Negative passive object index");
                    dependency(i, ActResourceKind::PassiveObject, "", index);
                } else if (spawn && name == "[particle filename]") {
                    count(i, 1);
                    const auto path = stringValue(values[0], "Invalid spawn particle path", true);
                    if (!path.empty()) dependency(i, ActResourceKind::Particle, path);
                } else if (name == "[default attackinfo]" || name == "[change attackinfo]") {
                    if (values.size() == 1 && values[0].is_string() && normalize(values[0].get<std::string>()) != "[default]")
                        dependency(i, ActResourceKind::AttackInfo, stringValue(values[0], "Invalid ATK path"));
                }
            });
        }
    }
    std::string marker(size_t &i) const {
        const auto at = i;
        const auto &values = script_.fields.at(i).values;
        if (values.size() == 1 && values[0].is_string()) return normalize(values[0].get<std::string>());
        require(values.empty() && i + 1 < script_.fields.size(), at, "marker_operand", "Missing enum marker");
        ++i;
        count(i, 0);
        return tag(i);
    }
    ActSelector selector(const std::string &name, const Json &arguments, size_t at) const {
        const std::map<std::string, ActSelectorKind> kinds = {
            {"[me]", ActSelectorKind::Me}, {"[target]", ActSelectorKind::Target},
            {"[last attacker]", ActSelectorKind::LastAttacker}, {"[last attacksuccess]", ActSelectorKind::LastAttackSuccess},
            {"[last attacksuccesses]", ActSelectorKind::LastAttackSuccesses}, {"[summon master]", ActSelectorKind::SummonMaster},
            {"[character]", ActSelectorKind::Character}, {"[monster]", ActSelectorKind::Monster},
            {"[passive]", ActSelectorKind::Passive}, {"[all our team]", ActSelectorKind::AllOurTeam},
            {"[all enemy]", ActSelectorKind::AllEnemy}, {"[create object]", ActSelectorKind::CreatedObject},
            {"[destroy object]", ActSelectorKind::DestroyedObject}, {"[load target]", ActSelectorKind::SavedTarget}};
        const auto found = kinds.find(name);
        require(found != kinds.end(), at, "unsupported_selector", "Unsupported ACT selector " + name);
        ActSelector result; result.kind = found->second;
        if (result.kind == ActSelectorKind::SavedTarget) {
            require(arguments.size() == 1, at, "saved_target_slot", "LOAD TARGET requires one slot");
            const auto slot = unsignedNumber(arguments[0], "Invalid saved target slot");
            require(slot <= std::numeric_limits<uint32_t>::max(), at, "saved_target_slot", "Saved target slot too large");
            result.savedSlot = uint32_t(slot);
        } else require(arguments.empty(), at, "selector_operands", "Unexpected selector operands");
        return result;
    }
    ActBehaviorCall call(size_t &i, ActCallKind kind, const std::string &scope) const {
        const auto at = i;
        ActBehaviorCall result; result.kind = kind; result.source = source(at, scope);
        Json arguments;
        std::string name;
        const auto &own = script_.fields[i].values;
        if (!own.empty() && own[0].is_string()) {
            name = normalize(own[0].get<std::string>());
            arguments = Json::array();
            for (size_t k = 1; k < own.size(); ++k) arguments.push_back(own[k]);
        } else {
            require(own.empty() && i + 1 < script_.fields.size(), at, "behavior_recipient", "Missing behavior recipient");
            ++i; name = tag(i); arguments = script_.fields[i].values;
        }
        const std::map<std::string, ActRecipientKind> recipients = {
            {"[me]", ActRecipientKind::Me}, {"[checkup object]", ActRecipientKind::CheckupObject},
            {"[dropout object]", ActRecipientKind::DropoutObject}, {"[target]", ActRecipientKind::Target},
            {"[last attacker]", ActRecipientKind::LastAttacker}, {"[last attacksuccess]", ActRecipientKind::LastAttackSuccess},
            {"[summon master]", ActRecipientKind::SummonMaster},
            {"[last attacksuccesses]", ActRecipientKind::LastAttackSuccesses}, {"[load target]", ActRecipientKind::SavedTarget}};
        const auto recipient = recipients.find(name);
        require(recipient != recipients.end(), i, "unsupported_recipient", "Unsupported behavior recipient " + name);
        result.recipient = recipient->second;
        const size_t slotOperands = result.recipient == ActRecipientKind::SavedTarget ? 1 : 0;
        const size_t expected = slotOperands + (kind == ActCallKind::Delayed ? 2 : 1);
        require(arguments.size() == expected, i, "behavior_call_operands", "Invalid behavior index/delay operands");
        if (slotOperands) {
            const auto slot = unsignedNumber(arguments[0], "Invalid saved target slot");
            require(slot <= std::numeric_limits<uint32_t>::max(), i, "saved_target_slot", "Saved target slot too large");
            result.savedSlot = uint32_t(slot);
        }
        result.behavior = size_t(unsignedNumber(arguments[slotOperands], "Invalid behavior index"));
        if (kind == ActCallKind::Delayed)
            result.delayMs = unsignedNumber(arguments[slotOperands + 1], "Invalid behavior delay");
        return result;
    }
    void parseMotion(size_t &i) {
        const auto begin = i;
        require(!program_->motion, i, "repeated_motion", "Multiple MOTION blocks require an explicit version adapter");
        count(i, 0);
        ActMotion motion; motion.source = source(i, "MOTION");
        size_t bases = 0;
        bool closed = false;
        for (++i; i < script_.fields.size(); ++i) {
            const auto at = i;
            const auto name = tag(i);
            const auto &values = script_.fields[i].values;
            if (name == "[/motion]") { count(i, 0); closed = true; break; }
            checked(at, [&] {
                if (name == "[base ani]") {
                    count(i, 1); motion.base = stringValue(values[0], "Invalid BASE ANI"); ++bases;
                    if (animations_.count(i)) {
                        motion.frameDurationsMs = animations_.at(i).frameDurationsMs;
                        motion.loop = animations_.at(i).animationLoops;
                    }
                } else if (name == "[sub ani]" || name == "[sub ani with xy]") {
                    const size_t stride = name == "[sub ani]" ? 3 : 5;
                    require(values.size() % stride == 0, at, "sub_ani_tuple", "Incomplete SUB ANI tuple");
                    for (size_t k = 0; k < values.size(); k += stride) {
                        ActMotionTrack track; track.source = source(at, "MOTION");
                        track.path = stringValue(values[k], "Invalid SUB ANI path");
                        track.frame = size_t(unsignedNumber(values[k + 1], "Invalid SUB ANI frame"));
                        track.layer = integerNumber(values[k + 2], "Invalid SUB ANI layer");
                        if (stride == 5) { track.x = finiteNumber(values[k + 3], "Invalid SUB ANI X"); track.y = finiteNumber(values[k + 4], "Invalid SUB ANI Y"); }
                        motion.tracks.push_back(std::move(track));
                    }
                } else if (name == "[sound]" || name == "[sound probability]" || name == "[speech]") {
                    const size_t stride = name == "[sound]" ? 2 : 3;
                    require(!values.empty() && values.size() % stride == 0, at, "motion_event_tuple", "Incomplete MOTION event tuple");
                    for (size_t k = 0; k < values.size(); k += stride) {
                        ActMotionEvent event; event.source = source(at, "MOTION");
                        event.frame = size_t(unsignedNumber(values[k + 1], "Invalid MOTION event frame"));
                        const auto text = stringValue(values[k], "Invalid MOTION event text");
                        if (name == "[speech]") event.payload = ActSpeech{text}; else event.payload = ActSound{text};
                        if (stride == 3) {
                            const auto probability = unsignedNumber(values[k + 2], "Invalid MOTION event probability");
                            require(probability <= 100, at, "probability_range", "MOTION probability must be 0..100");
                            event.probability = {uint32_t(probability), 100};
                        }
                        motion.events.push_back(std::move(event));
                    }
                } else if (name == "[/sub ani]" || name == "[/sub ani with xy]" || name == "[/sound]" ||
                           name == "[/sound probability]" || name == "[/speech]") count(i, 0);
                else fail(at, "unsupported_motion_opcode", "Unexecuted MOTION tag " + script_.fields[at].tag);
            });
        }
        if (!closed) report(begin, "unclosed_motion", "MOTION is not closed");
        if (bases != 1) report(begin, "motion_base_count", "MOTION requires exactly one BASE ANI");
        uint64_t duration = 0;
        for (const auto ms : motion.frameDurationsMs) {
            if (ms < 0) { report(begin, "negative_frame_duration", "Negative ANI frame duration"); continue; }
            try { duration = addChecked(duration, uint64_t(ms), "ANI duration overflow"); }
            catch (const std::exception &error) { report(begin, "animation_duration_overflow", error.what()); }
        }
        if (motion.frameDurationsMs.empty() || !duration)
            report(begin, "animation_timing_missing", "MOTION needs source ANI frame durations and nonzero total duration");
        for (const auto &track : motion.tracks) if (track.frame >= motion.frameDurationsMs.size())
            report(track.source.ordinal, "sub_frame_bounds", "SUB ANI starts outside BASE ANI");
        for (const auto &event : motion.events) if (event.frame >= motion.frameDurationsMs.size())
            report(event.source.ordinal, "motion_event_frame_bounds", "MOTION event frame is outside BASE ANI");
        program_->motion = std::move(motion);
    }
    void parseTrigger(size_t &i) {
        const auto begin = i;
        count(i, 0);
        ActTrigger trigger; trigger.source = source(i, "TRIGGER[" + std::to_string(program_->triggers.size()) + "]");
        trigger.limit = context_.policy.defaultLimit; trigger.enabled = context_.policy.defaultEnabled;
        trigger.checkTimeMs = context_.policy.defaultCheckTimeMs;
        const auto scope = trigger.source.scope;
        std::set<std::string> seen;
        bool closed = false;
        for (++i; i < script_.fields.size(); ++i) {
            const auto at = i;
            const auto name = tag(i);
            const auto &values = script_.fields[i].values;
            if (name == "[/trigger]") { count(i, 0); closed = true; break; }
            checked(at, [&] {
                const bool repeatedAllowed = name == "[do behavior]" || name == "[do proc behavior]" ||
                    name == "[direct do behavior]" || name == "[delay do behavior]";
                require(repeatedAllowed || seen.insert(name).second, at, "repeated_trigger_field", "Repeated trigger field needs a version rule: " + name);
                if (name == "[limit]") { count(i, 1); trigger.limit = unsignedNumber(values[0], "Invalid LIMIT"); }
                else if (name == "[enable]") {
                    const auto value = marker(i);
                    require(value == "[on]" || value == "[off]", at, "enable_value", "ENABLE accepts ON/OFF");
                    trigger.enabled = value == "[on]";
                } else if (name == "[check time]") { count(i, 1); trigger.checkTimeMs = unsignedNumber(values[0], "Invalid CHECK TIME"); }
                else if (name == "[frame]") {
                    count(i, 2);
                    ActFrameRange range{size_t(unsignedNumber(values[0], "Invalid FRAME start")), size_t(unsignedNumber(values[1], "Invalid FRAME end"))};
                    require(range.first <= range.last, at, "frame_range", "FRAME start exceeds end"); trigger.frames = range;
                } else if (name == "[which]") {
                    count(i, 0); require(i + 1 < script_.fields.size(), at, "missing_selector", "WHICH requires selector");
                    ++i; trigger.query.which = selector(tag(i), script_.fields[i].values, i);
                } else if (name == "[get target]") {
                    require(!values.empty(), at, "get_target_count", "GET TARGET requires count");
                    trigger.query.count = size_t(unsignedNumber(values[0], "Invalid GET TARGET count"));
                    require(trigger.query.count > 0, at, "get_target_count", "GET TARGET count must be positive");
                    std::vector<std::string> modes;
                    for (size_t k = 1; k < values.size(); ++k) modes.push_back(normalize(stringValue(values[k], "Invalid GET TARGET mode")));
                    if (modes.empty()) {
                        require(i + 1 < script_.fields.size(), at, "get_target_order", "GET TARGET requires explicit ordering");
                        ++i; count(i, 0); modes.push_back(tag(i));
                        if (modes[0] != "[random]") {
                            require(i + 1 < script_.fields.size(), at, "get_target_order", "GET TARGET ordering requires HIGH/LOW");
                            ++i; count(i, 0); modes.push_back(tag(i));
                        }
                    }
                    if (modes == std::vector<std::string>{"[random]"}) trigger.query.order = ActTargetOrder::Random;
                    else {
                        require(modes.size() == 2 && (modes[1] == "[high]" || modes[1] == "[low]"), at, "get_target_order", "Invalid GET TARGET order");
                        const bool high = modes[1] == "[high]";
                        if (modes[0] == "[distance]") trigger.query.order = high ? ActTargetOrder::DistanceHigh : ActTargetOrder::DistanceLow;
                        else if (modes[0] == "[hp]") trigger.query.order = high ? ActTargetOrder::HpHigh : ActTargetOrder::HpLow;
                        else if (modes[0] == "[mp]") trigger.query.order = high ? ActTargetOrder::MpHigh : ActTargetOrder::MpLow;
                        else if (modes[0] == "[level]") trigger.query.order = high ? ActTargetOrder::LevelHigh : ActTargetOrder::LevelLow;
                        else fail(at, "unsupported_target_order", "Unsupported GET TARGET sort " + modes[0]);
                    }
                } else if (name == "[is meet prob]" || name == "[random check]") {
                    require(seen.count(name == "[is meet prob]" ? "[random check]" : "[is meet prob]") == 0,
                            at, "repeated_probability", "Multiple probability conditions need an explicit rule");
                    count(i, name == "[is meet prob]" ? 1 : 2);
                    const auto numerator = unsignedNumber(values[0], "Invalid probability numerator");
                    const auto denominator = name == "[is meet prob]" ? 100 : unsignedNumber(values[1], "Invalid probability denominator");
                    require(denominator && denominator <= std::numeric_limits<uint32_t>::max() && numerator <= denominator,
                            at, "probability_range", "Probability must satisfy 0 <= numerator <= denominator <= UINT32_MAX");
                    trigger.probability = {uint32_t(numerator), uint32_t(denominator)};
                } else if (name == "[check stuck]") {
                    count(i, 1); const auto value = integerNumber(values[0], "Invalid CHECK STUCK");
                    require(value == 0 || value == 1, at, "stuck_value", "CHECK STUCK must be 0 or 1"); trigger.stuck = value == 1;
                } else if (name == "[do behavior]" || name == "[do proc behavior]" || name == "[direct do behavior]" || name == "[delay do behavior]") {
                    const auto kind = name == "[do behavior]" ? ActCallKind::Normal : name == "[do proc behavior]" ? ActCallKind::Proc :
                        name == "[direct do behavior]" ? ActCallKind::Direct : ActCallKind::Delayed;
                    trigger.calls.push_back(call(i, kind, scope));
                } else {
                    const std::map<std::string, ActEventKind> events = {
                        {"[on set action]", ActEventKind::SetAction}, {"[on remove action]", ActEventKind::RemoveAction},
                        {"[on damage]", ActEventKind::Damage}, {"[on attacksuccess]", ActEventKind::AttackSuccess},
                        {"[on create object]", ActEventKind::CreateObject}, {"[on destroy object]", ActEventKind::DestroyObject},
                        {"[on destroy me]", ActEventKind::DestroyMe}, {"[on move collision]", ActEventKind::MoveCollision}};
                    const auto event = events.find(name);
                    require(event != events.end(), at, "unsupported_trigger_opcode", "Unexecuted TRIGGER tag " + script_.fields[at].tag);
                    count(i, 0); require(!trigger.event, at, "multiple_on_events", "ON events cannot be combined"); trigger.event = event->second;
                }
            });
        }
        if (!closed) report(begin, "unclosed_trigger", "TRIGGER is not closed");
        if (trigger.calls.empty()) report(begin, "missing_behavior_dispatch", "TRIGGER has no explicit behavior dispatch");
        if (trigger.stuck && (!trigger.event || (*trigger.event != ActEventKind::Damage && *trigger.event != ActEventKind::AttackSuccess)))
            report(begin, "stuck_without_hit_event", "CHECK STUCK requires ON DAMAGE or ON ATTACKSUCCESS");
        program_->triggers.push_back(std::move(trigger));
    }
    ActCoordinates coordinates(size_t at) const {
        count(at, 3); const auto &v = script_.fields[at].values;
        ActCoordinates result;
        result.value = {finiteNumber(v[0], "Invalid position X"), finiteNumber(v[1], "Invalid position Y"), finiteNumber(v[2], "Invalid position Z")};
        return result;
    }
    ActInstruction parseSpeed(size_t &i, const std::string &scope) {
        const auto begin = i; count(i, 0);
        ActSetSpeed speed;
        std::set<std::string> fields;
        bool closed = false;
        for (++i; i < script_.fields.size(); ++i) {
            const auto name = tag(i);
            if (name == "[/set speed]") { count(i, 0); closed = true; break; }
            require(fields.insert(name).second, i, "repeated_speed_field", "Repeated SET SPEED field");
            if (name == "[x axis]" || name == "[y axis]" || name == "[z axis]") {
                count(i, 1); const double value = finiteNumber(script_.fields[i].values[0], "Invalid speed");
                if (name == "[x axis]") speed.x = value;
                else if (name == "[y axis]") speed.y = value;
                else speed.z = value;
            } else if (name == "[use my direction]" || name == "[not use direction]") {
                count(i, 0);
                require(fields.count(name == "[use my direction]" ? "[not use direction]" : "[use my direction]") == 0,
                        i, "conflicting_direction_flags", "SET SPEED direction flags conflict");
                speed.direction = name == "[use my direction]" ? ActDirectionBasis::Owner : ActDirectionBasis::Ignore;
            } else fail(i, "unsupported_speed_opcode", "Unexecuted SET SPEED tag " + script_.fields[i].tag);
        }
        require(closed, begin, "unclosed_set_speed", "SET SPEED is not closed");
        require(speed.x || speed.y || speed.z, begin, "empty_set_speed", "SET SPEED has no axis");
        return {source(begin, scope), speed};
    }
    ActInstruction parseSpawn(size_t &i, const std::string &scope) {
        const auto begin = i; count(i, 0);
        ActSpawn spawn;
        size_t required = 0;
        bool closed = false;
        std::set<std::string> fields;
        const std::array<std::string, 4> requiredTags = {"[index]", "[particle filename]", "[level]", "[pos]"};
        for (++i; i < script_.fields.size(); ++i) {
            const auto name = tag(i);
            if (name == "[/create passiveobject]") { count(i, 0); closed = true; break; }
            require(fields.insert(name).second, i, "repeated_spawn_field", "Repeated CREATE PASSIVEOBJECT field");
            if (std::find(requiredTags.begin(), requiredTags.end(), name) != requiredTags.end()) {
                require(required < requiredTags.size() && name == requiredTags[required], i, "spawn_field_order",
                        "CREATE PASSIVEOBJECT requires INDEX, PARTICLE FILENAME, LEVEL, POS in that order");
                ++required;
                if (name == "[index]") {
                    count(i, 1); spawn.objectIndex = integerNumber(script_.fields[i].values[0], "Invalid object index");
                    require(spawn.objectIndex >= 0, i, "object_index", "Negative object index");
                } else if (name == "[particle filename]") { count(i, 1); spawn.particle = stringValue(script_.fields[i].values[0], "Invalid spawn particle", true); }
                else if (name == "[level]") {
                    count(i, 1); spawn.level = integerNumber(script_.fields[i].values[0], "Invalid spawn level");
                    require(spawn.level >= 0, i, "spawn_level", "Negative spawn level");
                } else {
                    const auto previous = spawn.position;
                    spawn.position = coordinates(i);
                    spawn.position.useOwnerBase = previous.useOwnerBase;
                    spawn.position.useMapPosition = previous.useMapPosition;
                    spawn.position.useOwnerDirection = previous.useOwnerDirection;
                }
            } else {
                count(i, 0);
                if (name == "[use my basepos]") spawn.position.useOwnerBase = true;
                else if (name == "[use map pos]") spawn.position.useMapPosition = true;
                else if (name == "[use my direction]") spawn.position.useOwnerDirection = true;
                else if (name == "[following target]") spawn.followingTarget = true;
                else if (name == "[movable pos only]") spawn.movablePositionOnly = true;
                else if (name == "[no effect]") spawn.noEffect = true;
                else fail(i, "unsupported_spawn_opcode", "Unexecuted CREATE PASSIVEOBJECT tag " + script_.fields[i].tag);
            }
        }
        require(closed, begin, "unclosed_spawn", "CREATE PASSIVEOBJECT is not closed");
        require(required == requiredTags.size(), begin, "missing_spawn_field", "CREATE PASSIVEOBJECT is missing a mandatory field");
        require(!(spawn.position.useMapPosition && spawn.position.useOwnerBase), begin,
                "conflicting_coordinate_flags", "Map absolute position and owner-relative position conflict");
        return {source(begin, scope), spawn};
    }
    ActInstruction parseTeleport(size_t &i, const std::string &scope) {
        const auto begin = i; count(i, 0);
        ActTeleport teleport;
        bool closed = false, position = false;
        std::set<std::string> fields;
        for (++i; i < script_.fields.size(); ++i) {
            const auto name = tag(i);
            if (name == "[/teleport]") { count(i, 0); closed = true; break; }
            require(fields.insert(name).second, i, "repeated_teleport_field", "Repeated TELEPORT field");
            if (name == "[pos]") {
                const auto old = teleport.position;
                teleport.position = coordinates(i);
                teleport.position.useOwnerBase = old.useOwnerBase;
                teleport.position.useMapPosition = old.useMapPosition;
                teleport.position.useOwnerDirection = old.useOwnerDirection;
                position = true;
            } else {
                count(i, 0);
                if (name == "[move me]" || name == "[move target]") {
                    require(fields.count(name == "[move me]" ? "[move target]" : "[move me]") == 0,
                            i, "conflicting_move_flags", "TELEPORT MOVE ME/MOVE TARGET conflict");
                    teleport.moveOwner = name == "[move me]";
                } else if (name == "[use my basepos]") teleport.position.useOwnerBase = true;
                else if (name == "[use map pos]") teleport.position.useMapPosition = true;
                else if (name == "[use my direction]") teleport.position.useOwnerDirection = true;
                else fail(i, "unsupported_teleport_opcode", "Unexecuted TELEPORT tag " + script_.fields[i].tag);
            }
        }
        require(closed && position, begin, "incomplete_teleport", "TELEPORT requires POS and closing tag");
        require(!(teleport.position.useMapPosition && teleport.position.useOwnerBase), begin,
                "conflicting_coordinate_flags", "Map absolute position and owner-relative position conflict");
        return {source(begin, scope), teleport};
    }
    void parseBehavior(size_t &i) {
        const auto begin = i; count(i, 0);
        ActBehavior behavior; behavior.source = source(i, "BEHAVIOR[" + std::to_string(program_->behaviors.size()) + "]");
        const auto scope = behavior.source.scope;
        bool closed = false;
        for (++i; i < script_.fields.size(); ++i) {
            const auto at = i;
            const auto name = tag(i);
            const auto &values = script_.fields[i].values;
            if (name == "[/behavior]") { count(i, 0); closed = true; break; }
            // Structural failures in a nested command recover at its closing
            // tag, retaining subsequent behavior declarations and diagnostics.
            const auto nestedClose = name == "[set speed]" ? "[/set speed]" :
                name == "[create passiveobject]" ? "[/create passiveobject]" : name == "[teleport]" ? "[/teleport]" : "";
            try {
                if (name == "[set speed]") behavior.instructions.push_back(parseSpeed(i, scope));
                else if (name == "[create passiveobject]") behavior.instructions.push_back(parseSpawn(i, scope));
                else if (name == "[teleport]") behavior.instructions.push_back(parseTeleport(i, scope));
                else if (name == "[particle]") {
                    count(i, 4);
                    behavior.instructions.push_back({source(at, scope), ActParticle{stringValue(values[0], "Invalid PARTICLE path"),
                        {finiteNumber(values[1], "Invalid particle X"), finiteNumber(values[2], "Invalid particle Y"), finiteNumber(values[3], "Invalid particle Z")}}});
                } else if (name == "[destroy]" || name == "[destroy by force]") {
                    count(i, 0); behavior.instructions.push_back({source(at, scope), ActDestroy{name == "[destroy by force]"}});
                } else if (name == "[set direction]") {
                    const auto value = marker(i);
                    const std::map<std::string, ActDirectionKind> directions = {
                        {"[left]", ActDirectionKind::Left}, {"[right]", ActDirectionKind::Right},
                        {"[to target]", ActDirectionKind::ToTarget}, {"[random]", ActDirectionKind::Random},
                        {"[reverse]", ActDirectionKind::Reverse}, {"[my direction]", ActDirectionKind::Owner},
                        {"[my opposite direction]", ActDirectionKind::OppositeOwner}, {"[my current direction]", ActDirectionKind::CurrentOwner}};
                    const auto direction = directions.find(value);
                    require(direction != directions.end(), at, "unsupported_direction", "Unsupported SET DIRECTION " + value);
                    behavior.instructions.push_back({source(at, scope), ActSetDirection{direction->second}});
                } else if (name == "[attackrect]") {
                    const auto mode = marker(i);
                    require(mode == "[reset]" || mode == "[on]" || mode == "[off]", at, "attack_rect_mode", "Invalid ATTACKRECT mode");
                    behavior.instructions.push_back({source(at, scope), ActAttackRect{mode == "[reset]" ? ActAttackRectMode::Reset : mode == "[on]" ? ActAttackRectMode::On : ActAttackRectMode::Off}});
                } else if(name=="[set damage check]") {
                    count(i,2);const auto enabled=unsignedNumber(values[0],"Invalid SET DAMAGE CHECK switch");
                    const auto interval=unsignedNumber(values[1],"Invalid SET DAMAGE CHECK interval");
                    require(enabled<=1 && interval<=INT32_MAX,at,"invalid_damage_check_configuration","SET DAMAGE CHECK needs switch0/1 and int32 nonnegative interval");
                    behavior.instructions.push_back({source(at,scope),ActSetDamageCheck{enabled!=0,interval}});
                } else if (name == "[change attackinfo]") {
                    ActChangeAttackInfo command;
                    if (values.size() == 1 && values[0].is_string()) {
                        command.path = stringValue(values[0], "Invalid CHANGE ATTACKINFO");
                        command.useDefault = normalize(command.path) == "[default]";
                    } else { command.useDefault = marker(i) == "[default]"; require(command.useDefault, at, "attack_info_operand", "Expected ATK path or DEFAULT"); }
                    if (command.useDefault) command.path.clear();
                    behavior.instructions.push_back({source(at, scope), command});
                } else if (name == "[trigger]") {
                    count(i, 1); ActTriggerControl control;
                    control.trigger = size_t(unsignedNumber(values[0], "Scoped TRIGGER control is not supported; expected local numeric index"));
                    require(i + 1 < script_.fields.size(), at, "trigger_control_mode", "TRIGGER control requires mode");
                    ++i; count(i, 0); const auto mode = tag(i);
                    require(mode == "[on]" || mode == "[off]" || mode == "[reset]", at, "trigger_control_mode", "Invalid TRIGGER control mode");
                    control.mode = mode == "[on]" ? ActTriggerMode::On : mode == "[off]" ? ActTriggerMode::Off : ActTriggerMode::Reset;
                    behavior.instructions.push_back({source(at, scope), control});
                } else if (name == "[sound]" || name == "[speech]" || name == "[say speech]") {
                    count(i, 1); const auto text = stringValue(values[0], "Invalid behavior sound/speech");
                    if (name == "[sound]") behavior.instructions.push_back({source(at, scope), ActSound{text}});
                    else behavior.instructions.push_back({source(at, scope), ActSpeech{text}});
                } else if (name == "[send do behavior]" || name == "[delay do behavior]") {
                    auto request = call(i, name == "[delay do behavior]" ? ActCallKind::Delayed : ActCallKind::Normal, scope);
                    behavior.instructions.push_back({source(at, scope), ActDeferredCall{request, name == "[send do behavior]"}});
                } else fail(at, "unsupported_behavior_opcode", "Unexecuted BEHAVIOR tag " + script_.fields[at].tag);
            } catch (const CompileFailure &error) {
                report(error.field, error.code, error.what());
                if (*nestedClose) while (i + 1 < script_.fields.size() && tag(i) != nestedClose && tag(i) != "[/behavior]") ++i;
            } catch (const std::exception &error) {
                report(at, "invalid_behavior_operand", error.what());
                if (*nestedClose) while (i + 1 < script_.fields.size() && tag(i) != nestedClose && tag(i) != "[/behavior]") ++i;
            }
            if (i < script_.fields.size() && tag(i) == "[/behavior]") { closed = true; break; }
        }
        if (!closed) report(begin, "unclosed_behavior", "BEHAVIOR is not closed; no implicit end-of-file shorthand");
        program_->behaviors.push_back(std::move(behavior));
    }
  public:
    Compiler(const Script &script, const ActCompileContext &context) : script_(script), context_(context) {
        program_->original = script;
        program_->policy = context.policy;
        program_->source.packageIdentity = context.packageIdentity;
        program_->source.memberPath = script.path;
        program_->source.literalPath = script.path;
        program_->source.memberSha256 = sha256(script.rawBytes);
        program_->source.byteLength = script.rawBytes.size();
        program_->source.scope = "ACT";
    }
    ActCompileResult run() {
        if (script_.path.empty() || script_.rawBytes.empty() || script_.tokens.empty())
            report(0, "missing_lossless_source", "ACT compilation requires source path, raw bytes and ordered tokens");
        if (context_.packageIdentity.empty()) report(0, "missing_package_identity", "ACT requires a content package identity");
        if (!validPolicy(context_.policy)) report(0, "invalid_semantic_policy", "ACT semantic policy identity/budgets are invalid");
        checked(0, [&] {
            require(script_.rawBytes.size() >= 2 && (script_.rawBytes.size() - 2) % 5 == 0 &&
                    script_.tokens.size() == (script_.rawBytes.size() - 2) / 5,
                    0, "lossless_token_count", "ACT raw bytes and ordered token count disagree");
            size_t field = 0;
            for (size_t k = 0; k < script_.tokens.size(); ++k) {
                const auto &token = script_.tokens[k];
                const auto offset = unsignedNumber(token.at("offset"), "Invalid token offset");
                require(offset == 2 + k * 5 && offset + 5 <= script_.rawBytes.size(), 0, "lossless_token_offset", "ACT token offset differs from raw byte order");
                const auto kind = unsignedNumber(token.at("type"), "Invalid token type");
                require(kind == script_.rawBytes[size_t(offset)], 0, "lossless_token_type", "ACT token type differs from raw bytes");
                int32_t raw = 0;
                std::memcpy(&raw, script_.rawBytes.data() + size_t(offset) + 1, sizeof(raw));
                const auto &stored = token.contains("raw") ? token.at("raw") : token.at("raw_int");
                require(stored.is_number_integer() && stored.get<int64_t>() == raw, 0, "lossless_token_raw", "ACT token raw integer differs from source bytes");
                if (kind == 5) {
                    require(field < script_.fields.size() && script_.fields[field].offset == offset &&
                            token.at("value").is_string() && token.at("value") == script_.fields[field].tag,
                            field, "lossless_field_offset", "ACT field tags/offsets differ from ordered tokens");
                    ++field;
                }
            }
            require(field == script_.fields.size(), 0, "lossless_field_count", "ACT field count differs from ordered tokens");
        });
        collectDependencies();
        bool defaultAttack = false;
        for (size_t i = 0; i < script_.fields.size(); ++i) {
            const auto at = i;
            checked(at, [&] {
                const auto name = tag(i);
                if (name == "[motion]") parseMotion(i);
                else if (name == "[trigger]" && script_.fields[i].values.empty()) parseTrigger(i);
                else if (name == "[behavior]") parseBehavior(i);
                else if (name == "[default attackinfo]") {
                    require(!defaultAttack, i, "repeated_default_attack_info", "Repeated DEFAULT ATTACKINFO");
                    count(i, 1); defaultAttack = true;
                    program_->defaultAttackInfo = stringValue(script_.fields[i].values[0], "Invalid DEFAULT ATTACKINFO");
                } else fail(i, "unsupported_top_level_opcode", "Unexecuted top-level ACT tag " + script_.fields[i].tag);
            });
        }
        for (const auto &trigger : program_->triggers) {
            if (trigger.frames && (!program_->motion || trigger.frames->last >= program_->motion->frameDurationsMs.size()))
                report(trigger.source.ordinal, "trigger_frame_bounds", "FRAME condition requires an existing BASE ANI frame range");
            for (const auto &request : trigger.calls) if (request.behavior >= program_->behaviors.size())
                report(request.source.ordinal, "behavior_index_bounds", "Trigger references missing BEHAVIOR " + std::to_string(request.behavior));
        }
        for (const auto &behavior : program_->behaviors) for (const auto &instruction : behavior.instructions) {
            if (const auto *control = std::get_if<ActTriggerControl>(&instruction.payload)) {
                if (control->trigger >= program_->triggers.size()) report(instruction.source.ordinal, "trigger_index_bounds", "TRIGGER control references missing trigger");
            } else if (const auto *deferred = std::get_if<ActDeferredCall>(&instruction.payload)) {
                if (!deferred->targetProgram && deferred->call.behavior >= program_->behaviors.size())
                    report(instruction.source.ordinal, "behavior_index_bounds", "Delayed call references missing behavior");
            }
        }
        if (!program_->motion && program_->triggers.empty() && program_->behaviors.empty())
            report(0, "empty_program", "ACT contains no motion or executable program");
        bool commandConsumers = true;
        std::map<std::string, SourceRef> commands;
        commands.emplace("cleanup_owned", program_->source);
        for (const auto &behavior : program_->behaviors) for (const auto &instruction : behavior.instructions)
            commands.emplace(payloadJson(instruction.payload).at("kind").get<std::string>(), instruction.source);
        if (program_->motion) for (const auto &event : program_->motion->events)
            commands.emplace(payloadJson(event.payload).at("kind").get<std::string>(), event.source);
        for (const auto &command : commands) {
            bool supported = false;
            try { supported = context_.hasCommandConsumer && context_.hasCommandConsumer(command.first); }
            catch (...) { supported = false; }
            if (!supported) {
                commandConsumers = false;
                program_->diagnostics.push_back({"missing_command_consumer", "ACT World command consumer is unavailable: " + command.first, command.second, true});
            }
        }
        program_->syntaxComplete = syntaxErrors_ == 0;
        program_->sourceReady = closureKnown_ && std::all_of(program_->dependencies.begin(), program_->dependencies.end(),
            [](const ActDependency &dependency) { return dependency.found; });
        program_->runtimeReady = commandConsumers && std::all_of(program_->dependencies.begin(), program_->dependencies.end(),
            [](const ActDependency &dependency) { return dependency.runtimeSupported; });
        return {program_, program_->executable()};
    }
};
} // namespace

Json actEventIdentityJson(const ActEventContext &event) {
    Json payload = {{"kind", int(event.kind)}, {"subject", event.subject.json()}, {"other", event.other.json()},
                    {"stuck", event.stuck}, {"metadata", event.metadata}};
    if (event.subjectSnapshot) payload["subject_snapshot"] = entityJson(*event.subjectSnapshot);
    // Validate the same typed recipe used by restore, without hashing any new
    // receipt/ID/version fields into the historical digest contract.
    (void)receiptEvent(payload, event.eventId);
    return payload;
}
std::string actEventFingerprint(const ActEventContext &event) { return digestJson(actEventIdentityJson(event)); }
Json snapshotActEventReceipt(const ActAcceptedEventReceipt &receipt) {
    if (!receipt.unknown.is_object()) throw std::invalid_argument("ACT event receipt extensions must be an object");
    Json out = receipt.unknown;
    out["schema"] = 1; out["event_id"] = receipt.event.eventId;
    out["payload"] = actEventIdentityJson(receipt.event);
    out["fingerprint"] = digestJson(out.at("payload"));
    out["metadata_schema"] = receipt.event.metadata.is_object() && receipt.event.metadata.empty() ?
        "empty-object-v1" : "opaque-json-v1";
    receiptBytes(out);
    return out;
}
ActAcceptedEventReceipt restoreActEventReceipt(const Json &value) {
    receiptBytes(value);
    if (!value.is_object() || integerNumber(value.at("schema"), "Invalid ACT event receipt schema") != 1)
        throw std::invalid_argument("Unsupported ACT typed event receipt schema");
    ActAcceptedEventReceipt out;
    out.event = receiptEvent(value.at("payload"), unsignedNumber(value.at("event_id"), "Invalid ACT event receipt ID"));
    if (actEventIdentityJson(out.event).dump() != value.at("payload").dump() ||
        actEventFingerprint(out.event) != stringValue(value.at("fingerprint"), "Invalid ACT event receipt fingerprint"))
        throw std::invalid_argument("ACT event receipt original typed payload/fingerprint mismatch");
    const std::string expected = out.event.metadata.is_object() && out.event.metadata.empty() ? "empty-object-v1" : "opaque-json-v1";
    if (value.at("metadata_schema") != expected) throw std::invalid_argument("Unsupported or inconsistent ACT event metadata schema");
    // Keep the complete ordered root template. snapshot overlays known
    // values in place, including after typed handle remapping, so an
    // extension inserted between/after known fields keeps its position.
    out.unknown = value;
    return out;
}
namespace {
size_t checkedEventReceiptBytes(const ActInstanceState &state) {
    if (state.acceptedEventReceipts.size() > state.rememberedEvents.size() ||
        (state.eventReceiptsComplete && state.acceptedEventReceipts.size() != state.rememberedEvents.size()))
        throw std::invalid_argument("ACT typed receipt coverage differs from remembered event ledger");
    size_t total = 0;
    for (const auto &entry : state.acceptedEventReceipts) {
        const auto remembered = state.rememberedEvents.find(entry.first);
        const auto encoded = snapshotActEventReceipt(entry.second);
        const auto size = receiptBytes(encoded);
        if (entry.first != entry.second.event.eventId || entry.second.event.subject != state.owner ||
            remembered == state.rememberedEvents.end() || remembered->second != encoded.at("fingerprint"))
            throw std::invalid_argument("ACT typed receipt does not match its original event ledger/owner");
        if (size > ActEventReceiptBudget::maximumInstanceBytes - total)
            throw std::invalid_argument("ACT typed event receipt instance byte budget exceeded");
        total += size;
    }
    return total;
}
} // namespace

const char *actResourceKindName(ActResourceKind kind) {
    switch (kind) {
    case ActResourceKind::Animation: return "animation";
    case ActResourceKind::Particle: return "particle";
    case ActResourceKind::PassiveObject: return "passive_object";
    case ActResourceKind::Sound: return "sound";
    case ActResourceKind::AttackInfo: return "attack_info";
    case ActResourceKind::Action: return "action";
    case ActResourceKind::Monster: return "monster";
    }
    return "invalid";
}
Json ActDiagnostic::json() const { return {{"code", code}, {"message", message}, {"source", source.json()}, {"blocking", blocking}}; }
Json ActDependency::json() const {
    return {{"kind", actResourceKindName(request.kind)}, {"literal", request.literal}, {"index", request.index},
            {"origin", request.origin.json()}, {"resolved", resolved.json()}, {"found", found},
            {"runtime_supported", runtimeSupported}, {"diagnostic", diagnostic}};
}
Json ActSemanticPolicy::json() const {
    return {{"id", id}, {"evidence", "inferred"}, {"default_limit", defaultLimit}, {"default_enabled", defaultEnabled},
            {"default_check_time_ms", defaultCheckTimeMs}, {"frame_evaluation", int(frameEvaluation)},
            {"normal_and_direct_schedule", "declaration_order_current_prepared_batch"},
            {"probability", "PCG32 bounded denominator; numerator 0/full do not draw; probability before target query"},
            {"target_order", "stable ascending handles; stable metric ties; Fisher-Yates random without replacement"},
            {"check_time", "one evaluation per fixed tick; missed periods advance the check deadline without replaying the same World snapshot"},
            {"limit_consumption", "successful trigger conditions consume a fire even when the selected set is empty"},
            {"batch_snapshot", "query and coordinate bases use the immutable pre-commit World snapshot"},
            {"batch_order", "due continuations; crossed MOTION events by frame/declaration; triggers by declaration"},
            {"maximum_instructions", maximumInstructions}, {"maximum_commands", maximumCommands},
            {"maximum_pending", maximumPending}, {"maximum_remembered_events", maximumRememberedEvents},
            {"maximum_frame_boundaries", maximumFrameBoundaries}};
}
Json ActCompileResult::json() const {
    if (!program) return {{"ok", false}, {"error", "No compiled ACT program"}};
    Json dependencies = Json::array(), diagnostics = Json::array();
    for (const auto &dependency : program->dependencies) dependencies.push_back(dependency.json());
    for (const auto &diagnostic : program->diagnostics) diagnostics.push_back(diagnostic.json());
    return {{"ok", ok}, {"source", program->source.json()}, {"policy", program->policy.json()},
            {"syntax_complete", program->syntaxComplete}, {"source_ready", program->sourceReady},
            {"runtime_ready", program->runtimeReady}, {"has_motion", bool(program->motion)},
            {"triggers", program->triggers.size()}, {"behaviors", program->behaviors.size()},
            {"dependencies", dependencies}, {"diagnostics", diagnostics}};
}
ActCompileResult compileActProgram(const Script &script, const ActCompileContext &context) {
    return Compiler(script, context).run();
}
std::string ActEmittedCommand::stableKey() const {
    return "act:" + std::to_string(instanceId) + ":" + std::to_string(actionId) + ":" + std::to_string(sequence);
}
Json ActEmittedCommand::json() const {
    Json value = {{"key", stableKey()}, {"instance_id", instanceId}, {"action_id", actionId},
                  {"sequence", sequence}, {"owner", owner.json()}, {"recipient", recipient.json()},
                  {"source", source.json()}, {"payload", payloadJson(payload)}};
    if (ownerSnapshot) value["owner_snapshot"] = entityJson(*ownerSnapshot);
    if (recipientSnapshot) value["recipient_snapshot"] = entityJson(*recipientSnapshot);
    return value;
}

namespace {
bool live(const ActWorldView &world, EntityHandle handle) {
    const auto value = handle ? world.entity(handle) : std::nullopt;
    return value && value->handle == handle;
}
std::vector<EntityHandle> stableHandles(std::vector<EntityHandle> values, const ActWorldView &world) {
    values.erase(std::remove_if(values.begin(), values.end(), [&](EntityHandle value) { return !live(world, value); }), values.end());
    std::sort(values.begin(), values.end()); values.erase(std::unique(values.begin(), values.end()), values.end());
    return values;
}
bool probabilityPass(Pcg32 &random, ActProbability probability) {
    if (!probability.denominator || probability.numerator > probability.denominator) throw std::runtime_error("Invalid ACT probability");
    if (!probability.numerator) return false;
    if (probability.numerator == probability.denominator) return true;
    return random.bounded(probability.denominator) < probability.numerator;
}
std::vector<EntityHandle> selectEntities(const ActSelector &selector, const ActInstanceState &state,
                                       const ActWorldView &world, const ActEventContext *event) {
    const auto owner = world.entity(state.owner);
    if (!owner) return {};
    std::vector<EntityHandle> result;
    auto one = [&](EntityHandle handle) { if (handle) result.push_back(handle); };
    switch (selector.kind) {
    case ActSelectorKind::Me: one(state.owner); break;
    case ActSelectorKind::Target: one(owner->target); break;
    case ActSelectorKind::LastAttacker:
        one(event && event->kind == ActEventKind::Damage ? event->other : owner->lastAttacker); break;
    case ActSelectorKind::LastAttackSuccess:
        one(event && event->kind == ActEventKind::AttackSuccess ? event->other : owner->lastAttackSuccess); break;
    case ActSelectorKind::LastAttackSuccesses:
        if (event && event->kind == ActEventKind::AttackSuccess) one(event->other);
        else result = owner->lastAttackSuccesses;
        break;
    case ActSelectorKind::SummonMaster: one(owner->summonMaster); break;
    case ActSelectorKind::CreatedObject:
        if (event && event->kind == ActEventKind::CreateObject) one(event->other); break;
    case ActSelectorKind::DestroyedObject:
        if (event && event->kind == ActEventKind::DestroyObject) one(event->other); break;
    case ActSelectorKind::SavedTarget: {
        const auto saved = state.savedTargets.find(selector.savedSlot);
        if (saved != state.savedTargets.end()) one(saved->second);
        break;
    }
    default:
        for (const auto handle : world.entities()) {
            const auto entity = world.entity(handle);
            if (!entity || entity->handle != handle) continue;
            const bool matches = selector.kind == ActSelectorKind::Character ? entity->kind == ActEntityKind::Character :
                selector.kind == ActSelectorKind::Monster ? entity->kind == ActEntityKind::Monster :
                selector.kind == ActSelectorKind::Passive ? entity->kind == ActEntityKind::Passive :
                selector.kind == ActSelectorKind::AllOurTeam ? entity->team == owner->team :
                selector.kind == ActSelectorKind::AllEnemy ? entity->team != owner->team : false;
            if (matches) result.push_back(handle);
        }
        break;
    }
    return stableHandles(std::move(result), world);
}
struct QueryResult { std::vector<EntityHandle> checkup, dropout; };
QueryResult evaluateQuery(const ActTargetQuery &query, ActInstanceState &state,
                          const ActWorldView &world, const ActEventContext *event) {
    auto candidates = selectEntities(query.which, state, world, event);
    const auto original = candidates;
    const auto owner = world.entity(state.owner);
    if (!owner) throw std::runtime_error("ACT owner handle became invalid during query");
    if (query.order == ActTargetOrder::Random) {
        for (size_t k = candidates.size(); k > 1; --k) {
            if (k > std::numeric_limits<uint32_t>::max()) throw std::runtime_error("ACT target set exceeds RNG bound");
            std::swap(candidates[k - 1], candidates[state.random.bounded(uint32_t(k))]);
        }
    } else if (query.order != ActTargetOrder::StableIdentity) {
        auto metric = [&](EntityHandle handle) {
            const auto value = world.entity(handle);
            if (!value) throw std::runtime_error("ACT target handle changed during immutable query");
            switch (query.order) {
            case ActTargetOrder::DistanceLow: case ActTargetOrder::DistanceHigh: {
                const double dx = value->position.x - owner->position.x;
                const double dy = value->position.y - owner->position.y;
                const double dz = value->position.z - owner->position.z;
                return dx * dx + dy * dy + dz * dz;
            }
            case ActTargetOrder::HpLow: case ActTargetOrder::HpHigh: return double(value->hp);
            case ActTargetOrder::MpLow: case ActTargetOrder::MpHigh: return double(value->mp);
            case ActTargetOrder::LevelLow: case ActTargetOrder::LevelHigh: return double(value->level);
            default: return 0.0;
            }
        };
        const bool descending = query.order == ActTargetOrder::DistanceHigh || query.order == ActTargetOrder::HpHigh ||
                                query.order == ActTargetOrder::MpHigh || query.order == ActTargetOrder::LevelHigh;
        std::stable_sort(candidates.begin(), candidates.end(), [&](EntityHandle a, EntityHandle b) {
            const auto av = metric(a), bv = metric(b);
            if (!std::isfinite(av) || !std::isfinite(bv)) throw std::runtime_error("Nonfinite ACT target metric");
            return descending ? av > bv : av < bv;
        });
    }
    if (query.count && candidates.size() > query.count) candidates.resize(query.count);
    QueryResult result; result.checkup = std::move(candidates);
    for (auto handle : original) if (std::find(result.checkup.begin(), result.checkup.end(), handle) == result.checkup.end()) result.dropout.push_back(handle);
    return result;
}
std::vector<EntityHandle> recipients(const ActBehaviorCall &call, const QueryResult &query,
                                      const ActInstanceState &state, const ActWorldView &world) {
    if (call.recipient == ActRecipientKind::Me) return live(world, state.owner) ? std::vector<EntityHandle>{state.owner} : std::vector<EntityHandle>{};
    if (call.recipient == ActRecipientKind::CheckupObject) return query.checkup;
    if (call.recipient == ActRecipientKind::DropoutObject) return query.dropout;
    if (call.recipient == ActRecipientKind::SavedTarget) {
        const auto saved = state.savedTargets.find(call.savedSlot);
        return saved != state.savedTargets.end() && live(world, saved->second) ? std::vector<EntityHandle>{saved->second} : std::vector<EntityHandle>{};
    }
    std::vector<EntityHandle> result;
    for (const auto handle : query.checkup) {
        const auto entity = world.entity(handle);
        if (!entity) continue;
        switch (call.recipient) {
        case ActRecipientKind::Target: result.push_back(entity->target); break;
        case ActRecipientKind::LastAttacker: result.push_back(entity->lastAttacker); break;
        case ActRecipientKind::LastAttackSuccess: result.push_back(entity->lastAttackSuccess); break;
        case ActRecipientKind::SummonMaster: result.push_back(entity->summonMaster); break;
        case ActRecipientKind::LastAttackSuccesses: result.insert(result.end(), entity->lastAttackSuccesses.begin(), entity->lastAttackSuccesses.end()); break;
        default: break;
        }
    }
    return stableHandles(std::move(result), world);
}
struct FrameVisit { uint64_t ordinal = 0, absoluteUs = 0; size_t frame = 0; };
struct Timeline {
    std::vector<uint64_t> starts;
    uint64_t duration = 0;
    bool loop = false;
    explicit Timeline(const ActMotion &motion) : loop(motion.loop) {
        for (auto ms : motion.frameDurationsMs) {
            if (ms < 0) throw std::runtime_error("Negative ACT ANI duration");
            starts.push_back(duration);
            duration = addChecked(duration, multiplyChecked(uint64_t(ms), 1000, "ACT frame duration overflow"), "ACT ANI duration overflow");
        }
        if (!duration || starts.empty()) throw std::runtime_error("ACT ANI timing is empty");
    }
    FrameVisit current(uint64_t time) const {
        const auto cycle = loop ? time / duration : 0;
        const auto local = loop ? time % duration : std::min(time, duration - 1);
        auto it = std::upper_bound(starts.begin(), starts.end(), local);
        const auto frame = it == starts.begin() ? size_t(0) : size_t(it - starts.begin() - 1);
        return {addChecked(multiplyChecked(cycle, starts.size(), "ACT frame visit overflow"), frame, "ACT frame visit overflow"),
                addChecked(multiplyChecked(cycle, duration, "ACT timeline overflow"), starts[frame], "ACT timeline overflow"), frame};
    }
    std::vector<FrameVisit> crossed(uint64_t oldTime, uint64_t newTime, bool first, uint64_t budget) const {
        std::vector<FrameVisit> result;
        if (newTime < oldTime) throw std::runtime_error("ACT animation time moved backwards");
        const auto firstCycle = loop ? oldTime / duration : 0;
        const auto lastCycle = loop ? newTime / duration : 0;
        if (lastCycle - firstCycle > budget) throw std::runtime_error("ACT frame boundary budget exceeded");
        for (uint64_t cycle = firstCycle;; ++cycle) {
            for (size_t frame = 0; frame < starts.size(); ++frame) {
                const auto absolute = addChecked(multiplyChecked(cycle, duration, "ACT timeline overflow"), starts[frame], "ACT timeline overflow");
                if ((absolute > oldTime || (first && absolute == 0)) && absolute <= newTime) {
                    if (result.size() >= budget) throw std::runtime_error("ACT frame boundary budget exceeded");
                    result.push_back({addChecked(multiplyChecked(cycle, starts.size(), "ACT visit overflow"), frame, "ACT visit overflow"), absolute, frame});
                }
            }
            if (cycle == lastCycle) break;
        }
        return result;
    }
    uint64_t rangeVisit(const FrameVisit &visit, const ActFrameRange &) const {
        // A whole-range visit is identified by loop number, not individual
        // frames, so [FRAME 4 8] fires once while entering that contiguous range.
        return visit.ordinal / starts.size();
    }
};
struct Runner {
    ActPreparedStep &prepared;
    const ActWorldView &world;
    uint64_t instructions = 0;
    size_t behaviorDepth = 0;
    std::optional<ActEntityView> ownerSnapshot;
    Runner(ActPreparedStep &value, const ActWorldView &view) : prepared(value), world(view) {
        ownerSnapshot = world.entity(prepared.candidate.owner);
    }
    ActInstanceState &state() { return prepared.candidate; }
    const ActSemanticPolicy &policy() const { return prepared.candidate.program->policy; }
    void spend() {
        if (++instructions > policy().maximumInstructions) throw std::runtime_error("ACT instruction budget exceeded");
    }
    void emit(EntityHandle recipient, const SourceRef &source, ActCommandPayload payload) {
        prepared.failureSource = source;
        spend();
        if (prepared.commands.size() >= policy().maximumCommands) throw std::runtime_error("ACT command budget exceeded");
        if (!live(world, recipient)) return;
        if (!state().commandIds.nextValue() || state().commandIds.nextValue() == std::numeric_limits<uint64_t>::max())
            throw std::runtime_error("ACT command identities exhausted; final identity is reserved for cleanup");
        if (auto *direction = std::get_if<ActSetDirection>(&payload)) {
            if (direction->value == ActDirectionKind::Random)
                direction->value = state().random.bounded(2) ? ActDirectionKind::Right : ActDirectionKind::Left;
        }
        ActEmittedCommand command;
        command.instanceId = state().instanceId; command.actionId = state().actionId;
        command.sequence = state().commandIds.next(); command.owner = state().owner; command.recipient = recipient;
        command.source = source; command.payload = std::move(payload);
        command.ownerSnapshot = ownerSnapshot; command.recipientSnapshot = world.entity(recipient);
        prepared.commands.push_back(std::move(command));
    }
    void execute(size_t index, const std::vector<EntityHandle> &targets) {
        spend();
        struct DepthGuard { size_t &value; explicit DepthGuard(size_t &ref) : value(ref) { ++value; } ~DepthGuard() { --value; } } depth(behaviorDepth);
        if (behaviorDepth > 64) throw std::runtime_error("ACT behavior recursion budget exceeded");
        if (index >= state().program->behaviors.size()) throw std::runtime_error("ACT behavior index is invalid");
        const auto &behavior = state().program->behaviors[index];
        for (auto target : targets) {
            if (!live(world, target)) continue;
            for (const auto &instruction : behavior.instructions) {
                prepared.failureSource = instruction.source;
                spend();
                if (const auto *control = std::get_if<ActTriggerControl>(&instruction.payload)) {
                    // TRIGGER targets the behavior recipient's action. Only ME
                    // can be changed locally; other recipients use a World command.
                    if (target == state().owner) {
                        if (control->trigger >= state().triggers.size()) throw std::runtime_error("ACT trigger control index is invalid");
                        auto &trigger = state().triggers[control->trigger];
                        if (control->mode == ActTriggerMode::On) trigger.enabled = true;
                        else if (control->mode == ActTriggerMode::Off) trigger.enabled = false;
                        else { trigger.fires = 0; trigger.lastRangeVisit.reset(); trigger.nextCheckMs = state().elapsedMs; }
                    }
                    emit(target, instruction.source, instruction.payload);
                } else if (const auto *deferred = std::get_if<ActDeferredCall>(&instruction.payload)) {
                    if (deferred->targetProgram) {
                        // SEND calls the recipient's program, not this program.
                        // World must enqueue it, preserve this key and check the
                        // receiving program/action identity at delivery.
                        QueryResult query; query.checkup.push_back(target);
                        for (auto recipient : recipients(deferred->call, query, state(), world))
                            emit(recipient, instruction.source, *deferred);
                    } else {
                        QueryResult query; query.checkup.push_back(target);
                        schedule(deferred->call, recipients(deferred->call, query, state(), world));
                    }
                } else emit(target, instruction.source, instruction.payload);
            }
        }
    }
    void schedule(const ActBehaviorCall &call, std::vector<EntityHandle> targets) {
        spend();
        if (call.kind != ActCallKind::Delayed || !call.delayMs) {
            execute(call.behavior, targets); return;
        }
        if (state().pending.size() >= policy().maximumPending) throw std::runtime_error("ACT pending call budget exceeded");
        ActPendingCall pending;
        pending.sequence = state().pendingIds.next();
        pending.dueMs = addChecked(state().elapsedMs, call.delayMs, "ACT delayed call deadline overflow");
        pending.expectedActionId = state().actionId; pending.call = call;
        pending.recipients = std::move(targets);
        state().pending.push_back(std::move(pending));
        std::stable_sort(state().pending.begin(), state().pending.end(), [](const auto &a, const auto &b) {
            return std::tie(a.dueMs, a.sequence) < std::tie(b.dueMs, b.sequence);
        });
    }
    bool checkDeadline(ActTriggerState &runtime, const ActTrigger &trigger) {
        if (state().elapsedMs < runtime.nextCheckMs) return false;
        if (trigger.checkTimeMs) {
            const auto overdue = state().elapsedMs - runtime.nextCheckMs;
            const auto periods = overdue / trigger.checkTimeMs + 1;
            runtime.nextCheckMs = addChecked(runtime.nextCheckMs,
                multiplyChecked(periods, trigger.checkTimeMs, "ACT check deadline overflow"), "ACT check deadline overflow");
        }
        return true;
    }
    void trigger(size_t index, const ActEventContext *event, std::optional<uint64_t> visit = std::nullopt) {
        prepared.failureSource = state().program->triggers[index].source;
        spend();
        const auto &definition = state().program->triggers[index];
        auto &runtime = state().triggers[index];
        if (!runtime.enabled || (definition.limit && runtime.fires >= definition.limit)) return;
        if (definition.event) {
            if (!event || *definition.event != event->kind) return;
        } else if (event) return;
        if (definition.stuck && (!event || event->stuck != *definition.stuck)) return;
        if (visit && policy().frameEvaluation == ActFrameEvaluation::OncePerRangeVisit && runtime.lastRangeVisit == visit) return;
        if (!checkDeadline(runtime, definition)) return;
        if (visit && policy().frameEvaluation == ActFrameEvaluation::OncePerRangeVisit) runtime.lastRangeVisit = visit;
        if (!probabilityPass(state().random, definition.probability)) return;
        auto query = evaluateQuery(definition.query, state(), world, event);
        runtime.fires = addChecked(runtime.fires, 1, "ACT trigger fire counter overflow");
        for (const auto &call : definition.calls) schedule(call, recipients(call, query, state(), world));
    }
    void advance(const ActAdvanceInput &input) {
        auto &current = state();
        if (!live(world, current.owner)) throw std::runtime_error("ACT owner handle is stale");
        if (current.lastTick == std::numeric_limits<uint64_t>::max() || input.step.tick != current.lastTick + 1 || input.step.milliseconds != addChecked(current.lastSimulationMs,
                input.step.deltaMilliseconds, "ACT simulation timestamp overflow"))
            throw std::runtime_error("ACT expects exactly one consecutive fixed simulation tick");
        if (input.step.milliseconds != FixedStepClock::millisecondsAtTick(input.step.tick) ||
            input.step.deltaMilliseconds != FixedStepClock::millisecondsAtTick(input.step.tick) - FixedStepClock::millisecondsAtTick(input.step.tick - 1))
            throw std::runtime_error("ACT time input violates the fixed 60 Hz boundary");
        const auto oldAnimation = current.animationUs;
        uint64_t deltaUs = 0;
        if (current.clockMode == ActClockMode::SourceMilliseconds) {
            if (input.animationDeltaUs) throw std::runtime_error("Source ACT clock rejects a second animation delta");
            deltaUs = multiplyChecked(input.step.deltaMilliseconds, 1000, "ACT animation delta overflow");
        } else {
            if (!input.animationDeltaUs) throw std::runtime_error("External ACT clock requires one animation delta");
            deltaUs = *input.animationDeltaUs;
        }
        current.elapsedMs = addChecked(current.elapsedMs, input.step.deltaMilliseconds, "ACT age overflow");
        current.animationUs = addChecked(current.animationUs, deltaUs, "ACT animation time overflow");
        current.lastTick = input.step.tick; current.lastSimulationMs = input.step.milliseconds;
        const auto pending = current.pending;
        current.pending.clear();
        for (const auto &call : pending) {
            if (call.dueMs > current.elapsedMs) current.pending.push_back(call);
            else if (call.expectedActionId == current.actionId) execute(call.call.behavior, call.recipients);
        }
        std::stable_sort(current.pending.begin(), current.pending.end(), [](const auto &a, const auto &b) {
            return std::tie(a.dueMs, a.sequence) < std::tie(b.dueMs, b.sequence);
        });
        if (current.program->motion) {
            const Timeline timeline(*current.program->motion);
            const auto visits = timeline.crossed(oldAnimation, current.animationUs, current.firstAdvance, policy().maximumFrameBoundaries);
            const auto now = timeline.current(current.animationUs);
            // MOTION effects are ordered by crossed source frame, then original
            // declaration order; event emission is independent from rendering.
            for (const auto &visit : visits) for (const auto &event : current.program->motion->events) {
                if (event.frame == visit.frame && probabilityPass(current.random, event.probability))
                    emit(current.owner, event.source, event.payload);
            }
            for (size_t index = 0; index < current.program->triggers.size(); ++index) {
                const auto &definition = current.program->triggers[index];
                if (definition.event) continue;
                if (!definition.frames) { trigger(index, nullptr); continue; }
                const auto range = *definition.frames;
                if (policy().frameEvaluation == ActFrameEvaluation::EverySimulationStep) {
                    if (now.frame >= range.first && now.frame <= range.last) trigger(index, nullptr);
                } else {
                    std::set<uint64_t> considered;
                    for (const auto &visit : visits) if (visit.frame >= range.first && visit.frame <= range.last) {
                        const auto rangeId = timeline.rangeVisit(visit, range);
                        if (considered.insert(rangeId).second) trigger(index, nullptr, rangeId);
                    }
                    if (now.frame >= range.first && now.frame <= range.last) {
                        const auto rangeId = timeline.rangeVisit(now, range);
                        if (considered.insert(rangeId).second) trigger(index, nullptr, rangeId);
                    }
                }
            }
        } else {
            for (size_t index = 0; index < current.program->triggers.size(); ++index)
                if (!current.program->triggers[index].event) trigger(index, nullptr);
        }
        current.firstAdvance = false;
    }
};

ActPreparedStep preparedFor(const ActInstanceState &state) {
    ActPreparedStep prepared;
    prepared.expectedRevision = state.revision; prepared.expectedInstanceId = state.instanceId;
    prepared.candidate = state;
    return prepared;
}
void faultStep(ActPreparedStep &prepared, const ActInstanceState &before, const std::string &message) {
    // A failed behavior discards all candidate mutation and all commands. Its
    // only publishable result is explicit ownership cleanup plus Faulted state.
    prepared.candidate = before; prepared.commands.clear();
    prepared.candidate.status = ActInstanceStatus::Faulted;
    prepared.candidate.pending.clear();
    prepared.candidate.revision = addChecked(before.revision, 1, "ACT revision overflow");
    prepared.ok = false; prepared.faulted = true; prepared.error = message;
    const auto location = prepared.failureSource.value_or(before.program ? before.program->source : SourceRef{});
    prepared.diagnostics.push_back({"act_runtime_fault", message, location, true});
    ActEmittedCommand cleanup;
    cleanup.instanceId = before.instanceId; cleanup.actionId = before.actionId;
    cleanup.sequence = prepared.candidate.commandIds.next(); cleanup.owner = before.owner; cleanup.recipient = before.owner;
    cleanup.source = location;
    cleanup.payload = ActCleanup{message}; prepared.commands.push_back(std::move(cleanup));
}
bool validInstance(const ActInstanceState &state) {
    return state.program && state.program->executable() && state.instanceId && state.actionId && state.owner &&
           state.triggers.size() == state.program->triggers.size() &&
           state.rememberedEvents.size() <= state.program->policy.maximumRememberedEvents &&
           state.acceptedEventReceipts.size() <= state.rememberedEvents.size() &&
           (!state.eventReceiptsComplete || state.acceptedEventReceipts.size() == state.rememberedEvents.size()) &&
           state.acceptedEventReceiptBytes <= ActEventReceiptBudget::maximumInstanceBytes;
}
} // namespace

ActBindResult bindActProgram(std::shared_ptr<const ActProgram> program, const ActBindRequest &request,
                            const ActWorldView &world) {
    ActBindResult result;
    try {
        if (!program || !program->executable()) throw std::invalid_argument("ACT program has blocking source/runtime diagnostics");
        if (!request.instanceId || !request.actionId || !request.owner || !live(world, request.owner))
            throw std::invalid_argument("ACT bind requires live owner and nonzero instance/action identities");
        if (request.clockMode != ActClockMode::SourceMilliseconds && request.clockMode != ActClockMode::ExternalAnimationDelta)
            throw std::invalid_argument("Invalid ACT clock mode");
        if (request.simulationMs != FixedStepClock::millisecondsAtTick(request.tick))
            throw std::invalid_argument("ACT bind timestamp violates fixed simulation boundary");
        auto &state = result.state;
        state.program = std::move(program); state.instanceId = request.instanceId; state.actionId = request.actionId;
        state.owner = request.owner; state.clockMode = request.clockMode;
        state.lastTick = request.tick; state.lastSimulationMs = request.simulationMs;
        state.random = Pcg32(request.randomSeed, request.randomSequence);
        for (const auto &trigger : state.program->triggers) state.triggers.push_back({trigger.enabled, 0, 0, std::nullopt});
        result.ok = true;
    } catch (const std::exception &error) { result.error = error.what(); }
    return result;
}
ActPreparedStep prepareActAdvance(const ActInstanceState &state, const ActAdvanceInput &input,
                                 const ActWorldView &world) {
    auto prepared = preparedFor(state);
    if (!validInstance(state) || state.status != ActInstanceStatus::Running) { prepared.error = "ACT instance is not running or structurally valid"; return prepared; }
    if (state.revision == std::numeric_limits<uint64_t>::max()) { prepared.error = "ACT revision exhausted"; return prepared; }
    try {
        Runner runner(prepared, world); runner.advance(input);
        prepared.candidate.revision = addChecked(state.revision, 1, "ACT revision overflow"); prepared.ok = true; prepared.failureSource.reset();
    } catch (const std::exception &error) { faultStep(prepared, state, error.what()); }
    catch (...) { faultStep(prepared, state, "ACT runtime raised a non-standard exception"); }
    return prepared;
}
ActPreparedStep prepareActEvent(const ActInstanceState &state, const ActEventContext &event,
                               const ActWorldView &world) {
    auto prepared = preparedFor(state);
    if (!validInstance(state) || state.status != ActInstanceStatus::Running) { prepared.error = "ACT instance is not running or structurally valid"; return prepared; }
    if (state.revision == std::numeric_limits<uint64_t>::max()) { prepared.error = "ACT revision exhausted"; return prepared; }
    if (!event.eventId || event.subject != state.owner) { prepared.error = "ACT event requires stable identity and matching subject generation"; return prepared; }
    ActAcceptedEventReceipt receipt;
    std::string digest;
    size_t receiptSize = 0;
    try {
        receipt.event = event;
        const auto encoded = snapshotActEventReceipt(receipt);
        digest = encoded.at("fingerprint").get<std::string>(); receiptSize = receiptBytes(encoded);
    } catch (const std::exception &error) { prepared.error = error.what(); return prepared; }
    const auto remembered = state.rememberedEvents.find(event.eventId);
    if (remembered != state.rememberedEvents.end()) {
        if (remembered->second != digest) prepared.error = "ACT event identity was reused with conflicting payload";
        else { prepared.ok = true; prepared.replayed = true; }
        return prepared;
    }
    try {
        if (!live(world, state.owner)) throw std::runtime_error("ACT event owner is stale; destroy notification must dispatch before entity retirement");
        if (state.rememberedEvents.size() >= state.program->policy.maximumRememberedEvents)
            throw std::runtime_error("ACT remembered event budget exceeded; running ledgers cannot be evicted by checkpointing");
        if (state.acceptedEventReceiptBytes > ActEventReceiptBudget::maximumInstanceBytes ||
            receiptSize > ActEventReceiptBudget::maximumInstanceBytes - state.acceptedEventReceiptBytes)
            throw std::runtime_error("ACT typed event receipt instance byte budget exceeded");
        Runner runner(prepared, world);
        for (size_t index = 0; index < state.program->triggers.size(); ++index) {
            const auto &definition = state.program->triggers[index];
            if (!definition.event || *definition.event != event.kind) continue;
            if (definition.frames) {
                if (!state.program->motion) throw std::runtime_error("ACT event FRAME condition lacks MOTION");
                const Timeline timeline(*state.program->motion);
                const auto frame = timeline.current(state.animationUs);
                if (frame.frame < definition.frames->first || frame.frame > definition.frames->last) continue;
            }
            runner.trigger(index, &event);
        }
        prepared.candidate.rememberedEvents.emplace(event.eventId, digest);
        if (!prepared.candidate.acceptedEventReceipts.emplace(event.eventId, std::move(receipt)).second)
            throw std::runtime_error("ACT typed event receipt ID is already present without its remembered event");
        prepared.candidate.acceptedEventReceiptBytes += receiptSize;
        prepared.candidate.revision = addChecked(state.revision, 1, "ACT revision overflow"); prepared.ok = true; prepared.failureSource.reset();
    } catch (const std::exception &error) { faultStep(prepared, state, error.what()); }
    catch (...) { faultStep(prepared, state, "ACT event dispatch raised a non-standard exception"); }
    return prepared;
}
ActPreparedStep prepareActCancel(const ActInstanceState &state, const std::string &reason) {
    auto prepared = preparedFor(state);
    if (!validInstance(state)) { prepared.error = "Cannot cancel invalid ACT instance"; return prepared; }
    if (state.status != ActInstanceStatus::Running) { prepared.ok = true; prepared.replayed = true; return prepared; }
    if (state.revision == std::numeric_limits<uint64_t>::max() || !state.commandIds.nextValue()) { prepared.error = "ACT cleanup identity exhausted"; return prepared; }
    prepared.candidate.status = ActInstanceStatus::Cancelled; prepared.candidate.pending.clear();
    prepared.candidate.revision = addChecked(state.revision, 1, "ACT revision overflow");
    ActEmittedCommand command;
    command.instanceId = state.instanceId; command.actionId = state.actionId; command.sequence = prepared.candidate.commandIds.next();
    command.owner = state.owner; command.recipient = state.owner; command.source = state.program->source;
    command.payload = ActCleanup{reason}; prepared.commands.push_back(std::move(command)); prepared.ok = true;
    return prepared;
}
bool publishActStep(ActInstanceState &state, const ActPreparedStep &prepared) {
    if ((!prepared.ok && !prepared.faulted) || prepared.expectedRevision != state.revision ||
        prepared.expectedInstanceId != state.instanceId || prepared.candidate.actionId != state.actionId ||
        prepared.candidate.owner != state.owner || prepared.candidate.program != state.program) return false;
    if (prepared.replayed) return true;
    if (prepared.candidate.revision != state.revision + 1) return false;
    state = prepared.candidate;
    return true;
}

Json snapshotActInstance(const ActInstanceState &state, uint64_t commitGeneration) {
    if (!validInstance(state)) throw std::invalid_argument("Cannot snapshot invalid ACT instance");
    if (!commitGeneration) throw std::invalid_argument("ACT snapshot requires the outer World's nonzero commit generation");
    Json result = state.unknown.is_object() ? state.unknown : Json::object();
    if (state.acceptedEventReceiptBytes != checkedEventReceiptBytes(state))
        throw std::invalid_argument("ACT typed event receipt cached byte budget differs from payload");
    result["schema"] = 2;
    result["commit_generation"] = commitGeneration;
    result["program"] = {{"package_identity", state.program->source.packageIdentity},
        {"member_path", state.program->source.memberPath}, {"member_sha256", state.program->source.memberSha256}};
    result["policy"] = state.program->policy.json();
    result["instance_id"] = state.instanceId; result["action_id"] = state.actionId; result["revision"] = state.revision;
    result["owner"] = state.owner.json(); result["clock_mode"] = int(state.clockMode); result["status"] = int(state.status);
    result["last_tick"] = state.lastTick; result["last_simulation_ms"] = state.lastSimulationMs;
    result["elapsed_ms"] = state.elapsedMs; result["animation_us"] = state.animationUs; result["first_advance"] = state.firstAdvance;
    result["command_ids"] = state.commandIds.snapshot(); result["pending_ids"] = state.pendingIds.snapshot();
    result["random"] = state.random.snapshot(); result["variables"] = state.variables;
    result["triggers"] = Json::array();
    for (const auto &trigger : state.triggers) {
        Json value = {{"enabled", trigger.enabled}, {"fires", trigger.fires}, {"next_check_ms", trigger.nextCheckMs}};
        value["last_range_visit"] = trigger.lastRangeVisit ? Json(*trigger.lastRangeVisit) : Json();
        result["triggers"].push_back(std::move(value));
    }
    result["pending"] = Json::array();
    for (const auto &call : state.pending) {
        Json targets = Json::array();
        for (auto target : call.recipients) targets.push_back(target.json());
        result["pending"].push_back({{"sequence", call.sequence}, {"due_ms", call.dueMs},
            {"expected_action_id", call.expectedActionId}, {"call", callJson(call.call)}, {"recipients", targets}});
    }
    result["saved_targets"] = Json::array();
    for (const auto &target : state.savedTargets) result["saved_targets"].push_back({{"slot", target.first}, {"handle", target.second.json()}});
    result["remembered_events"] = Json::array();
    for (const auto &event : state.rememberedEvents) result["remembered_events"].push_back({{"id", event.first}, {"fingerprint", event.second}});
    result["event_receipt_coverage"] = state.eventReceiptsComplete ? "complete-typed-v1" : "legacy-digest-only";
    result["accepted_event_receipts"] = Json::array();
    for (const auto &event : state.acceptedEventReceipts)
        result["accepted_event_receipts"].push_back(snapshotActEventReceipt(event.second));
    return result;
}
namespace {
bool booleanValue(const Json &value, const char *message) {
    if (!value.is_boolean()) throw std::invalid_argument(message);
    return value.get<bool>();
}
ActBehaviorCall restoreCall(const ActProgram &program, const Json &value) {
    const auto kind = integerNumber(value.at("kind"), "Invalid saved ACT call kind");
    const auto recipient = integerNumber(value.at("recipient"), "Invalid saved ACT call recipient");
    if (kind < 0 || kind > int(ActCallKind::Delayed) || recipient < 0 || recipient > int(ActRecipientKind::SavedTarget))
        throw std::invalid_argument("Saved ACT call enum is outside supported range");
    ActBehaviorCall call;
    call.kind = ActCallKind(kind); call.recipient = ActRecipientKind(recipient);
    const auto slot = unsignedNumber(value.at("saved_slot"), "Invalid saved ACT target slot");
    if (slot > std::numeric_limits<uint32_t>::max()) throw std::invalid_argument("Saved ACT target slot too large");
    call.savedSlot = uint32_t(slot); call.behavior = size_t(unsignedNumber(value.at("behavior"), "Invalid saved ACT behavior index"));
    call.delayMs = unsignedNumber(value.at("delay_ms"), "Invalid saved ACT delay");
    call.source = program.source;
    call.source.byteOffset = unsignedNumber(value.at("source_offset"), "Invalid saved ACT call offset");
    call.source.byteLength = unsignedNumber(value.at("source_length"), "Invalid saved ACT call length");
    call.source.ordinal = size_t(unsignedNumber(value.at("source_ordinal"), "Invalid saved ACT call ordinal"));
    call.source.scope = stringValue(value.at("source_scope"), "Invalid saved ACT call scope");
    bool declared = false;
    for (const auto &trigger : program.triggers) for (const auto &sourceCall : trigger.calls)
        if (callJson(sourceCall) == callJson(call)) declared = true;
    for (const auto &behavior : program.behaviors) for (const auto &instruction : behavior.instructions)
        if (const auto *deferred = std::get_if<ActDeferredCall>(&instruction.payload))
            if (!deferred->targetProgram && callJson(deferred->call) == callJson(call)) declared = true;
    if (!declared || call.kind != ActCallKind::Delayed || call.behavior >= program.behaviors.size() || !call.delayMs)
        throw std::invalid_argument("Saved ACT continuation is not declared by the source program");
    return call;
}
bool hexDigest(const std::string &value) {
    return value.size() == 64 && std::all_of(value.begin(), value.end(), [](char c) { return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'); });
}
} // namespace
ActBindResult restoreActInstance(std::shared_ptr<const ActProgram> program, const Json &snapshot,
                                const ActWorldView &world, uint64_t expectedCommitGeneration) {
    ActBindResult result;
    try {
        if (!program || !program->executable()) throw std::invalid_argument("Cannot restore an unavailable ACT program");
        if (!snapshot.is_object()) throw std::invalid_argument("Invalid ACT snapshot shape");
        const auto schema = integerNumber(snapshot.at("schema"), "Invalid ACT snapshot schema");
        if (schema != 1 && schema != 2)
            throw std::invalid_argument("Unsupported ACT snapshot schema");
        if (!expectedCommitGeneration || unsignedNumber(snapshot.at("commit_generation"), "Invalid ACT commit generation") != expectedCommitGeneration)
            throw std::invalid_argument("ACT checkpoint generation differs from the outer World transaction");
        const auto &identity = snapshot.at("program");
        if (identity.at("package_identity") != program->source.packageIdentity || identity.at("member_path") != program->source.memberPath ||
            identity.at("member_sha256") != program->source.memberSha256 || snapshot.at("policy") != program->policy.json())
            throw std::invalid_argument("ACT snapshot content/program/policy identity differs");
        ActInstanceState candidate;
        candidate.program = std::move(program);
        candidate.instanceId = unsignedNumber(snapshot.at("instance_id"), "Invalid ACT instance identity");
        candidate.actionId = unsignedNumber(snapshot.at("action_id"), "Invalid ACT action identity");
        candidate.revision = unsignedNumber(snapshot.at("revision"), "Invalid ACT revision");
        candidate.owner = EntityHandle::fromJson(snapshot.at("owner"));
        if (!candidate.instanceId || !candidate.actionId || !candidate.owner) throw std::invalid_argument("Zero ACT identity or owner");
        const auto clock = integerNumber(snapshot.at("clock_mode"), "Invalid ACT clock mode");
        const auto status = integerNumber(snapshot.at("status"), "Invalid ACT status");
        if (clock < 0 || clock > int(ActClockMode::ExternalAnimationDelta) || status < 0 || status > int(ActInstanceStatus::Faulted))
            throw std::invalid_argument("Invalid ACT clock/status enum");
        candidate.clockMode = ActClockMode(clock); candidate.status = ActInstanceStatus(status);
        if (candidate.status == ActInstanceStatus::Running && !live(world, candidate.owner))
            throw std::invalid_argument("ACT running snapshot owner generation is stale");
        candidate.lastTick = unsignedNumber(snapshot.at("last_tick"), "Invalid ACT saved tick");
        candidate.lastSimulationMs = unsignedNumber(snapshot.at("last_simulation_ms"), "Invalid ACT saved simulation time");
        candidate.elapsedMs = unsignedNumber(snapshot.at("elapsed_ms"), "Invalid ACT saved age");
        candidate.animationUs = unsignedNumber(snapshot.at("animation_us"), "Invalid ACT saved animation time");
        candidate.firstAdvance = booleanValue(snapshot.at("first_advance"), "Invalid ACT first-advance flag");
        if (candidate.lastSimulationMs != FixedStepClock::millisecondsAtTick(candidate.lastTick) ||
            candidate.elapsedMs > candidate.lastSimulationMs || (candidate.firstAdvance && (candidate.elapsedMs || candidate.animationUs)))
            throw std::invalid_argument("ACT snapshot time fields disagree");
        if (candidate.clockMode == ActClockMode::SourceMilliseconds && candidate.animationUs != multiplyChecked(candidate.elapsedMs, 1000, "ACT snapshot time overflow"))
            throw std::invalid_argument("ACT source animation clock differs from saved simulation age");
        candidate.commandIds.restore(snapshot.at("command_ids")); candidate.pendingIds.restore(snapshot.at("pending_ids"));
        if (candidate.status == ActInstanceStatus::Running && !candidate.commandIds.nextValue())
            throw std::invalid_argument("Running ACT snapshot has no cleanup command identity");
        candidate.random.restore(snapshot.at("random"));
        candidate.variables = snapshot.at("variables");
        if (!candidate.variables.is_object()) throw std::invalid_argument("ACT variables must be an object");
        const auto &triggers = snapshot.at("triggers");
        if (!triggers.is_array() || triggers.size() != candidate.program->triggers.size()) throw std::invalid_argument("ACT trigger checkpoint size differs from source");
        for (size_t index = 0; index < triggers.size(); ++index) {
            const auto &value = triggers[index]; const auto &definition = candidate.program->triggers[index];
            ActTriggerState trigger;
            trigger.enabled = booleanValue(value.at("enabled"), "Invalid ACT trigger enabled flag");
            trigger.fires = unsignedNumber(value.at("fires"), "Invalid ACT trigger fire count");
            trigger.nextCheckMs = unsignedNumber(value.at("next_check_ms"), "Invalid ACT trigger next-check time");
            if (!value.at("last_range_visit").is_null()) trigger.lastRangeVisit = unsignedNumber(value.at("last_range_visit"), "Invalid ACT range visit");
            if (definition.limit && trigger.fires > definition.limit) throw std::invalid_argument("ACT fire count exceeds source limit");
            if (trigger.lastRangeVisit) {
                if (!definition.frames || !candidate.program->motion) throw std::invalid_argument("ACT saved range visit lacks a FRAME condition");
                const Timeline timeline(*candidate.program->motion);
                if (*trigger.lastRangeVisit > timeline.current(candidate.animationUs).ordinal / timeline.starts.size())
                    throw std::invalid_argument("ACT saved range visit lies in a future animation loop");
            }
            candidate.triggers.push_back(std::move(trigger));
        }
        const auto &pending = snapshot.at("pending");
        if (!pending.is_array() || pending.size() > candidate.program->policy.maximumPending ||
            (candidate.status != ActInstanceStatus::Running && !pending.empty())) throw std::invalid_argument("Invalid ACT pending call checkpoint");
        std::set<uint64_t> sequences;
        for (const auto &value : pending) {
            ActPendingCall call;
            call.sequence = unsignedNumber(value.at("sequence"), "Invalid ACT pending sequence");
            call.dueMs = unsignedNumber(value.at("due_ms"), "Invalid ACT pending deadline");
            call.expectedActionId = unsignedNumber(value.at("expected_action_id"), "Invalid ACT pending action identity");
            if (!call.sequence || (candidate.pendingIds.nextValue() && call.sequence >= candidate.pendingIds.nextValue()) ||
                !sequences.insert(call.sequence).second || call.expectedActionId != candidate.actionId || call.dueMs <= candidate.elapsedMs)
                throw std::invalid_argument("ACT pending sequence/action/deadline is inconsistent");
            call.call = restoreCall(*candidate.program, value.at("call"));
            if (!value.at("recipients").is_array()) throw std::invalid_argument("Invalid ACT pending recipients");
            std::set<EntityHandle> unique;
            for (const auto &target : value.at("recipients")) {
                const auto handle = EntityHandle::fromJson(target);
                if (!handle || !unique.insert(handle).second) throw std::invalid_argument("Invalid or duplicate ACT pending recipient");
                // A retained stale target is valid serialized state. Delivery
                // filters it by generation; it never retargets a replacement.
                call.recipients.push_back(handle);
            }
            candidate.pending.push_back(std::move(call));
        }
        if (!std::is_sorted(candidate.pending.begin(), candidate.pending.end(), [](const auto &a, const auto &b) {
                return std::tie(a.dueMs, a.sequence) < std::tie(b.dueMs, b.sequence); }))
            throw std::invalid_argument("ACT pending calls are not in stable deadline/sequence order");
        if (!snapshot.at("saved_targets").is_array()) throw std::invalid_argument("Invalid ACT saved targets");
        for (const auto &target : snapshot.at("saved_targets")) {
            const auto slot = unsignedNumber(target.at("slot"), "Invalid ACT saved target slot");
            const auto handle = EntityHandle::fromJson(target.at("handle"));
            if (slot > std::numeric_limits<uint32_t>::max() || !handle || !candidate.savedTargets.emplace(uint32_t(slot), handle).second)
                throw std::invalid_argument("Invalid or duplicate ACT saved target slot");
        }
        const auto &events = snapshot.at("remembered_events");
        if (!events.is_array() || events.size() > candidate.program->policy.maximumRememberedEvents)
            throw std::invalid_argument("ACT remembered event checkpoint exceeds budget");
        for (const auto &event : events) {
            const auto id = unsignedNumber(event.at("id"), "Invalid ACT remembered event id");
            const auto fingerprint = stringValue(event.at("fingerprint"), "Invalid ACT event fingerprint");
            if (!id || !hexDigest(fingerprint) || !candidate.rememberedEvents.emplace(id, fingerprint).second)
                throw std::invalid_argument("Invalid or duplicate ACT remembered event");
        }
        candidate.eventReceiptsComplete = false;
        if (schema == 2) {
            const auto coverage = stringValue(snapshot.at("event_receipt_coverage"), "Missing ACT receipt coverage");
            if (coverage != "complete-typed-v1" && coverage != "legacy-digest-only")
                throw std::invalid_argument("Unsupported ACT typed receipt coverage policy");
            candidate.eventReceiptsComplete = coverage == "complete-typed-v1";
            const auto &receipts = snapshot.at("accepted_event_receipts");
            if (!receipts.is_array() || receipts.size() > candidate.program->policy.maximumRememberedEvents)
                throw std::invalid_argument("ACT typed event receipt count budget exceeded");
            size_t encodedTotal = 0;
            for (const auto &value : receipts) {
                const auto bytes = receiptBytes(value);
                if (bytes > ActEventReceiptBudget::maximumInstanceBytes - encodedTotal)
                    throw std::invalid_argument("ACT typed event receipt instance byte budget exceeded");
                encodedTotal += bytes;
                auto receipt = restoreActEventReceipt(value);
                const auto id = receipt.event.eventId;
                if (!candidate.acceptedEventReceipts.emplace(id, std::move(receipt)).second)
                    throw std::invalid_argument("Duplicate ACT typed event receipt");
            }
        }
        candidate.acceptedEventReceiptBytes = checkedEventReceiptBytes(candidate);
        if (!candidate.eventReceiptsComplete)
            result.diagnostics.push_back({{"code", "legacy_digest_only_events"}, {"remappable", false},
                {"message", "Historical event digests are readable for diagnosis/same-handle compatibility; typed provenance is incomplete"}});
        candidate.unknown = snapshot;
        for (const auto *key : {"schema", "commit_generation", "program", "policy", "instance_id", "action_id", "revision", "owner", "clock_mode", "status",
                "last_tick", "last_simulation_ms", "elapsed_ms", "animation_us", "first_advance", "command_ids", "pending_ids", "random",
                "variables", "triggers", "pending", "saved_targets", "remembered_events"}) candidate.unknown.erase(key);
        if (schema == 2) {
            candidate.unknown.erase("accepted_event_receipts"); candidate.unknown.erase("event_receipt_coverage");
        } else {
            Json collisions = Json::object();
            for (const char *key : {"accepted_event_receipts", "event_receipt_coverage"})
                if (candidate.unknown.contains(key)) { collisions[key] = candidate.unknown.at(key); candidate.unknown.erase(key); }
            if (!collisions.empty()) {
                Json preserved = {{"fields", std::move(collisions)}};
                if (candidate.unknown.contains("legacy_event_receipt_extension_fields"))
                    preserved["previous_value"] = candidate.unknown.at("legacy_event_receipt_extension_fields");
                candidate.unknown["legacy_event_receipt_extension_fields"] = std::move(preserved);
            }
        }
        result.state = std::move(candidate); result.ok = true;
    } catch (const std::exception &error) { result.error = error.what(); }
    catch (...) { result.error = "ACT restore raised a non-standard exception"; }
    return result;
}
namespace {
class ReceiptRegistryView final : public ActWorldView {
    const EntityRegistry &registry_;
  public:
    explicit ReceiptRegistryView(const EntityRegistry &registry) : registry_(registry) {}
    std::optional<ActEntityView> entity(EntityHandle handle) const override {
        if (!registry_.valid(handle)) return std::nullopt;
        ActEntityView entity; entity.handle = handle; return entity;
    }
    std::vector<EntityHandle> entities() const override { return registry_.active(); }
};
} // namespace
    ActEntityHandleRemapper::ActEntityHandleRemapper(const EntityRegistry &saved, const std::map<EntityHandle, EntityHandle> &mapping,
                          const EntityRegistry &prepared, const ActWorldView &view)
        : saved_(saved), prepared_(prepared), mapping_(mapping), view_(view) {
        savedNext_ = unsignedNumber(saved.snapshot().at("ids").at("next"), "Invalid ACT remap saved ID ceiling");
        const auto active = saved.active();
        if (mapping.size() != active.size() || prepared.active().size() != mapping.size())
            throw std::invalid_argument("ACT remap requires the complete saved-live/fresh registry bijection");
        std::set<EntityHandle> fresh;
        std::optional<EntityHandle> previous;
        for (auto old : active) {
            const auto entry = mapping.find(old);
            if (entry == mapping.end() || !savedNext_ || entry->second.id < savedNext_ ||
                !prepared.valid(entry->second) || !live(view, entry->second) || !fresh.insert(entry->second).second)
                throw std::invalid_argument("ACT remap missing live endpoint, non-fresh ID or duplicate new handle");
            // Query tie breaks are stable handle order. Preserve that order
            // when allocating a resumed actor graph, not arbitrary map order.
            if (previous && !(previous.value() < entry->second))
                throw std::invalid_argument("ACT remap changes deterministic saved-live handle order");
            previous = entry->second;
        }
        std::set<EntityHandle> visible;
        for (auto handle : view.entities()) if (!visible.insert(handle).second || !fresh.count(handle))
            throw std::invalid_argument("ACT remap prepared World exposes unbound or duplicate live actors");
        if (visible != fresh) throw std::invalid_argument("ACT remap prepared World omits a continued live actor");
    }
    EntityHandle ActEntityHandleRemapper::handle(EntityHandle old, bool requiredLive) const {
        old = EntityHandle::fromJson(old.json());
        if (!old) {
            if (requiredLive) throw std::invalid_argument("ACT remap missing required live handle");
            return old;
        }
        if (savedNext_ && old.id >= savedNext_)
            throw std::invalid_argument("ACT remap refuses an unknown future handle above the saved issued-ID ceiling");
        if (saved_.valid(old)) return mapping_.at(old);
        if (requiredLive) throw std::invalid_argument("ACT remap required endpoint was not live in the saved registry");
        if (prepared_.valid(old) || live(view_, old))
            throw std::invalid_argument("ACT remap would resurrect a preserved stale/tombstone reference");
        return old;
    }
    void ActEntityHandleRemapper::entity(ActEntityView &value) const {
        value.handle = handle(value.handle); value.target = handle(value.target);
        value.lastAttacker = handle(value.lastAttacker); value.lastAttackSuccess = handle(value.lastAttackSuccess);
        value.summonMaster = handle(value.summonMaster);
        for (auto &success : value.lastAttackSuccesses) success = handle(success);
    }
    void ActEntityHandleRemapper::event(ActEventContext &value) const {
        if (!value.metadata.is_object() || !value.metadata.empty())
            throw std::invalid_argument("ACT remap requires registered metadata semantics; opaque JSON is diagnostic-only");
        value.subject = handle(value.subject); value.other = handle(value.other);
        if (value.subjectSnapshot) entity(*value.subjectSnapshot);
    }
ActBindResult restoreRemappedActInstance(std::shared_ptr<const ActProgram> program, const Json &snapshot,
    const EntityRegistry &savedRegistry, const std::map<EntityHandle, EntityHandle> &savedToNew,
    const EntityRegistry &preparedRegistry, const ActWorldView &preparedWorld, uint64_t expectedCommitGeneration) {
    ActBindResult result;
    try {
        ReceiptRegistryView originalView(savedRegistry);
        // Ordinary restore verifies every original typed receipt against the
        // original core digest before any handle or fingerprint is changed.
        auto original = restoreActInstance(program, snapshot, originalView, expectedCommitGeneration);
        result.diagnostics = original.diagnostics;
        if (!original.ok) throw std::invalid_argument(original.error);
        if (!original.state.eventReceiptsComplete)
            throw std::invalid_argument("Legacy ACT digest-only history cannot be remapped; original typed event provenance is unavailable");
        ActEntityHandleRemapper remap(savedRegistry, savedToNew, preparedRegistry, preparedWorld);
        auto candidate = std::move(original.state);
        candidate.owner = remap.handle(candidate.owner, candidate.status == ActInstanceStatus::Running);
        for (auto &call : candidate.pending) for (auto &recipient : call.recipients) recipient = remap.handle(recipient);
        for (auto &target : candidate.savedTargets) target.second = remap.handle(target.second);
        for (auto &receipt : candidate.acceptedEventReceipts) {
            remap.event(receipt.second.event);
            candidate.rememberedEvents.at(receipt.first) = actEventFingerprint(receipt.second.event);
        }
        candidate.acceptedEventReceiptBytes = checkedEventReceiptBytes(candidate);
        const auto transformed = snapshotActInstance(candidate, expectedCommitGeneration);
        result = restoreActInstance(std::move(program), transformed, preparedWorld, expectedCommitGeneration);
        if (result.ok) result.diagnostics.push_back({{"code", "typed_event_handles_remapped"},
            {"event_receipts", result.state.acceptedEventReceipts.size()},
            {"old_handle_aliases_installed", false}, {"world_published", false}});
    } catch (const std::exception &error) { result.ok = false; result.error = error.what(); result.state = ActInstanceState{}; }
    catch (...) { result.ok = false; result.error = "ACT typed event remap raised a non-standard exception"; result.state = ActInstanceState{}; }
    return result;
}
} // namespace dnf
