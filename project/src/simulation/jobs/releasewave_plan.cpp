#include "dnf/releasewave_plan.hpp"
#include <cmath>
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr int releaseWaveObjectId = 20018;
int integer(const Json &v, const std::string &what, int minimum = 0) {
    if (!v.is_number_integer() || (v.is_number_unsigned() &&
        v.get<uint64_t>() > uint64_t(std::numeric_limits<int>::max())))
        throw std::runtime_error("ReleaseWave invalid integer: " + what);
    const auto n = v.get<int64_t>();
    if (n < minimum || n > std::numeric_limits<int>::max())
        throw std::runtime_error("ReleaseWave integer out of range: " + what);
    return int(n);
}
const Field &uniqueField(const Script &script, const std::string &tag) {
    const Field *found = nullptr;
    for (const auto &field : script.fields) if (normalize(field.tag) == normalize(tag)) {
        if (found) throw std::runtime_error("ReleaseWave repeated field: " + script.path + ":" + tag);
        found = &field;
    }
    if (!found) throw std::runtime_error("ReleaseWave missing field: " + script.path + ":" + tag);
    return *found;
}
const SkillDataField &skillField(const SkillSourceData &data, const std::string &tag) {
    const auto key = normalize(tag);
    if (data.ambiguousFields.count(key) || !data.selected.count(key))
        throw std::runtime_error("ReleaseWave missing/ambiguous SKL field: " + tag);
    return data.selected.at(key);
}
int skillInteger(const SkillSourceData &data, const std::string &tag, int minimum = 0) {
    const auto &v = skillField(data, tag).field.values;
    if (v.size() != 1) throw std::runtime_error("ReleaseWave SKL scalar arity: " + tag);
    return integer(v.at(0), tag, minimum);
}
SourceRef span(SourceRef source, uint64_t offset, uint64_t length, size_t ordinal,
               const std::string &scope) {
    if (offset > source.byteLength || length > source.byteLength - offset)
        throw std::runtime_error("ReleaseWave source span out of range");
    source.byteOffset = offset; source.byteLength = length;
    source.ordinal = ordinal; source.scope = scope;
    return source;
}
SourceRef fieldRef(const ReleaseWaveResource &resource, const Field &field, size_t ordinal = 0) {
    size_t end = resource.raw.size();
    for (const auto &next : resource.script.fields)
        if (next.offset > field.offset) end = std::min(end, next.offset);
    return span(resource.source, field.offset, end - field.offset, ordinal, field.tag);
}
ReleaseWaveResource resource(Pvf &pvf, const std::string &path, bool script) {
    ReleaseWaveResource out;
    out.raw = pvf.read(path);
    const auto &read = pvf.reads().at(normalize(path));
    out.source = {pvf.identity(), normalize(path), sha256(out.raw), "CP936", 0,
        uint64_t(out.raw.size()), 0, "whole_member", read.value("literal_path", path)};
    if (script) out.script = pvf.script(path);
    return out;
}
void skip(Cursor &cursor, size_t count) { cursor.need(count); cursor.at += count; }
// Only records byte extents for the grammar already accepted by decodeAni.
// No independent interpretation of enums, visual transforms or attack units.
void skipProperty(Cursor &cursor, uint16_t code, bool global) {
    switch (code) {
    case 0: case 1: case 10: skip(cursor, 1); return;
    case 3: case 13: case 24: case 28: skip(cursor, 2); return;
    case 7: case 27: skip(cursor, 8); return;
    case 8: case 9: case 12: case 23: case 26: skip(cursor, 4); return;
    case 11: {
        const auto effect = cursor.get<uint16_t>();
        if (effect == 5) skip(cursor, 3);
        else if (effect == 6) skip(cursor, 4);
        else if (effect > 6) throw std::runtime_error("ReleaseWave unknown ANI graphic effect");
        return;
    }
    case 16: cursor.sizedText(); return;
    case 17: case 25: return;
    case 18: if (global) { skip(cursor, 15); return; } break;
    }
    throw std::runtime_error("ReleaseWave unknown ANI span property");
}
void decodeResource(ReleaseWaveResource &out) {
    Cursor cursor{out.raw};
    const auto count = cursor.get<uint16_t>(), names = cursor.get<uint16_t>();
    for (unsigned i = 0; i < names; ++i) cursor.sizedText();
    const auto globals = cursor.get<uint16_t>();
    const auto property = [&](int frame, bool global) {
        const auto begin = cursor.at;
        const auto code = cursor.get<uint16_t>();
        skipProperty(cursor, code, global);
        out.byteSpans.push_back({{"kind", "property"}, {"frame", frame}, {"code", code},
            {"source", span(out.source, begin, cursor.at - begin, out.byteSpans.size(),
                global ? "global_property" : "frame_property").json()}});
    };
    for (unsigned i = 0; i < globals; ++i) property(-1, true);
    for (unsigned frame = 0; frame < count; ++frame) {
        const auto begin = cursor.at;
        const auto boxes = cursor.get<uint16_t>();
        for (unsigned box = 0; box < boxes; ++box) {
            const auto offset = cursor.at;
            const auto type = cursor.get<uint16_t>(); skip(cursor, 24);
            out.byteSpans.push_back({{"kind", "box"}, {"frame", frame}, {"type", type},
                {"source", span(out.source, offset, cursor.at - offset, box, "frame_box").json()}});
        }
        if (cursor.get<int16_t>() >= 0) skip(cursor, 2);
        skip(cursor, 8);
        const auto properties = cursor.get<uint16_t>();
        for (unsigned i = 0; i < properties; ++i) property(int(frame), false);
        out.byteSpans.push_back({{"kind", "frame"}, {"frame", frame},
            {"source", span(out.source, begin, cursor.at - begin, frame, "frame").json()}});
    }
    if (cursor.at != out.raw.size()) throw std::runtime_error("ReleaseWave ANI span trailing bytes");
    auto decoded = decodeAni(out.raw, out.source.memberPath);
    int64_t duration = 0;
    for (const auto &frame : decoded.frames) duration += frame.duration;
    if (decoded.frames.empty() || duration <= 0 || duration > std::numeric_limits<int>::max())
        throw std::runtime_error("ReleaseWave empty/invalid ANI duration");
    out.animation = std::make_shared<const Animation>(std::move(decoded));
}
std::string childPath(const ReleaseWaveResource &parent, const Field &field) {
    if (field.values.size() != 1 || !field.values[0].is_string())
        throw std::runtime_error("ReleaseWave expected one resource binding: " + field.tag);
    const auto literal = field.values[0].get<std::string>();
    if (literal.empty() || literal.find('\0') != std::string::npos)
        throw std::runtime_error("ReleaseWave empty resource binding");
    const auto relative = std::filesystem::u8path(literal);
    if (relative.is_absolute() || relative.has_root_name())
        throw std::runtime_error("ReleaseWave absolute source child path");
    for (const auto &part : relative) if (part == "..")
        throw std::runtime_error("ReleaseWave source child escapes its namespace");
    return normalize((std::filesystem::u8path(parent.source.memberPath).parent_path() /
        relative).lexically_normal().generic_u8string());
}
Json diagnostic(const char *code, const char *policy, const char *basis, const char *unknown,
                const char *impact) {
    return {{"code", code}, {"policy", policy}, {"classification", "inferred"},
        {"basis", basis}, {"unverified_conditions", unknown}, {"impact", impact}};
}
void validate(const ReleaseWaveSourceContract &source) {
    if (source.packageIdentity.empty() || !(source.skill == SkillKey{0,32}) ||
        !(source.skillData.definition.key == source.skill) ||
        source.skillData.definition.kind != SkillSourceKind::Active ||
        source.objectRegistration.id != releaseWaveObjectId)
        throw std::runtime_error("ReleaseWave source/skill/object identity mismatch");
    const auto checkResource = [&](const ReleaseWaveResource &r, bool animation) {
        if (r.source.packageIdentity != source.packageIdentity || r.source.memberPath.empty() ||
            r.source.memberSha256.empty() || r.raw.empty() || (animation && !r.animation))
            throw std::runtime_error("ReleaseWave incomplete or mixed-package source");
        if (animation && (r.animation->path != r.source.memberPath || r.animation->frames.empty() ||
            r.animation->duration <= 0)) throw std::runtime_error("ReleaseWave invalid animation source");
    };
    checkResource(source.characterSource, false); checkResource(source.objectRegistry, false);
    checkResource(source.objectSource, false); checkResource(source.attackInfo, false);
    for (const auto &r : source.phaseMotions) checkResource(r, true);
    for (const auto &r : source.visuals) {
        checkResource(r, true);
        for (const auto &frame : r.animation->frames) for (const auto &box : frame.boxes)
            if (box.type == 15) throw std::runtime_error("ReleaseWave visual has an attack box outside this adapter scope");
    }
    checkResource(source.attackAnimation, true);
    for (const auto &frame : source.attackAnimation.animation->frames) {
        if (!frame.image.empty()) throw std::runtime_error("ReleaseWave logical attack unexpectedly has an image");
        if (std::none_of(frame.boxes.begin(), frame.boxes.end(), [](const Box &b) { return b.type == 15; }))
            throw std::runtime_error("ReleaseWave logical attack has a frame with no source attack box");
    }
}
const char *durationName(ReleaseWaveDurationPolicy policy) {
    switch (policy) {
    case ReleaseWaveDurationPolicy::InferredZeroThenSourceStaticV1: return "inferred-1031-releasewave-zero-then-static-v1";
    case ReleaseWaveDurationPolicy::InferredSourceMotionDurationsV1: return "inferred-1031-releasewave-motion-duration-v1";
    }
    throw std::invalid_argument("ReleaseWave unknown duration policy");
}
} // namespace

Json ReleaseWaveResource::snapshot(bool includeRaw) const {
    Json out = {{"source", source.json()}, {"byte_spans", byteSpans}};
    if (!script.path.empty()) {
        out["script_source"] = script.source; out["fields"] = Json::array();
        for (const auto &f : script.fields)
            out["fields"].push_back({{"tag", f.tag}, {"offset", f.offset}, {"values", f.values}});
        if (includeRaw) out["tokens"] = script.tokens;
    }
    if (animation) {
        out["duration_ms"] = animation->duration; out["globals"] = animation->globals;
        out["frames"] = Json::array();
        for (const auto &f : animation->frames) {
            Json boxes = Json::array();
            for (const auto &b : f.boxes) boxes.push_back({b.type,b.x,b.y,b.z,b.w,b.h,b.d});
            out["frames"].push_back({{"image", f.image}, {"image_frame", f.imageFrame},
                {"delay_ms", f.duration}, {"x", f.x}, {"y", f.y}, {"boxes", boxes}, {"properties", f.properties}});
        }
    }
    if (includeRaw) out["raw_bytes"] = raw;
    return out;
}
std::vector<Box> ReleaseWaveSourceContract::attackBoxesAt(size_t frame) const {
    if (!attackAnimation.animation || frame >= attackAnimation.animation->frames.size())
        throw std::out_of_range("ReleaseWave source attack frame unavailable");
    std::vector<Box> out;
    for (const auto &box : attackAnimation.animation->frames[frame].boxes)
        if (box.type == 15) out.push_back(box);
    return out;
}
Json ReleaseWaveSourceContract::snapshot(bool includeRaw) const {
    Json phases = Json::array(), effects = Json::array();
    for (size_t i = 0; i < 2; ++i) {
        phases.push_back({{"binding", phaseBindings[i].json()}, {"resource", phaseMotions[i].snapshot(includeRaw)}});
        effects.push_back(visuals[i].snapshot(includeRaw));
    }
    return {{"adapter", "1031-releasewave-source-plan-v1"}, {"package_identity", packageIdentity},
        {"skill", skill.json()}, {"skill_data", skillData.snapshot(includeRaw)},
        {"character", characterSource.snapshot(includeRaw)}, {"phases", phases}, {"visuals", effects},
        {"object_registry", objectRegistry.snapshot(includeRaw)}, {"object_id", objectRegistration.id},
        {"object_registration", {{"ordinal", objectRegistration.ordinal}, {"offset", objectRegistration.offset},
            {"path_offset", objectRegistration.pathOffset}, {"literal", objectRegistration.literal},
            {"path", objectRegistration.path}}},
        {"object", objectSource.snapshot(includeRaw)}, {"object_motion_binding", objectMotionBinding.json()},
        {"object_attack_binding", objectAttackBinding.json()}, {"attack_info", attackInfo.snapshot(includeRaw)},
        {"attack_animation", attackAnimation.snapshot(includeRaw)}, {"floating_height_metadata", floatingHeight},
        {"diagnostics", diagnostics}, {"skill_runtime_complete", false}, {"native_controller_restored", false}};
}
ReleaseWaveSourceContract readReleaseWaveSourceContract(Pvf &pvf, const CharacterCatalog &catalog,
                                                       const std::string &mode) {
    ReleaseWaveSourceContract out; out.packageIdentity = pvf.identity();
    out.skillData = readSkillSourceData(catalog.skillDefinition(out.skill), mode);
    if (out.skillData.definition.source.bytes != pvf.read(out.skillData.definition.source.script.path))
        throw std::runtime_error("ReleaseWave skill catalog belongs to different source bytes");
    const auto &character = catalog.at(out.skill.jobId);
    out.characterSource = resource(pvf, character.source.script.path, true);
    if (out.characterSource.raw != character.source.bytes)
        throw std::runtime_error("ReleaseWave CHR catalog belongs to different source bytes");
    const std::array<std::string,2> tags{"[throw motion 2-1]", "[throw motion 2-2]"};
    for (size_t i = 0; i < tags.size(); ++i) {
        const auto &f = uniqueField(out.characterSource.script, tags[i]);
        const auto *binding = character.resource(tags[i]);
        if (!binding || !binding->exists || binding->fieldOffset != f.offset || binding->valueIndex != 0 ||
            f.values.size() != 1) throw std::runtime_error("ReleaseWave missing exact CHR throw2 binding");
        out.phaseBindings[i] = fieldRef(out.characterSource, f);
        out.phaseMotions[i] = resource(pvf, binding->path, false); decodeResource(out.phaseMotions[i]);
    }
    auto objects = loadCharacterList(pvf, "passiveobject/passiveobject.lst", "passiveobject");
    const auto *registered = objects.unique(releaseWaveObjectId);
    if (!registered || !registered->exists) throw std::runtime_error("ReleaseWave object20018 missing/ambiguous");
    out.objectRegistration = *registered;
    out.objectRegistry = resource(pvf, objects.source.script.path, true);
    out.objectSource = resource(pvf, registered->path, true);
    for (const auto &f : out.objectSource.script.fields) {
        const auto tag = normalize(f.tag);
        if (tag.find("action]") != std::string::npos && !f.values.empty())
            throw std::runtime_error("ReleaseWave object ACT requires a separate executable consumer");
    }
    const auto &motion = uniqueField(out.objectSource.script, "[basic motion]");
    const auto &attack = uniqueField(out.objectSource.script, "[attack info]");
    out.objectMotionBinding = fieldRef(out.objectSource, motion);
    out.objectAttackBinding = fieldRef(out.objectSource, attack);
    out.attackAnimation = resource(pvf, childPath(out.objectSource, motion), false);
    decodeResource(out.attackAnimation);
    out.attackInfo = resource(pvf, childPath(out.objectSource, attack), true);
    const auto &height = uniqueField(out.objectSource.script, "[floating height]").values;
    if (height.size() != 1) throw std::runtime_error("ReleaseWave floating-height arity");
    out.floatingHeight = integer(height[0], "floating height");
    // Versioned controller literals, not paths guessed from SKL preload images.
    const std::array<std::string,2> visuals{
        "character/swordman/effect/animation/releasewave1.ani",
        "character/swordman/effect/animation/releasewave2.ani"};
    for (size_t i = 0; i < visuals.size(); ++i) {
        out.visuals[i] = resource(pvf, visuals[i], false); decodeResource(out.visuals[i]);
    }
    out.diagnostics.push_back(diagnostic("versioned_visual_and_phase_binding", "inferred-60us-to1031-releasewave-bindings-v1",
        "60US combat_cast_state and combat_spawned_object; current1031 CHR/SKL/OBJ/ANI read independently",
        "1031 native phase dispatcher and signed attachment semantics not recovered",
        "phase0 visuals use +1/-1 literal arguments; they are not declared render layers"));
    out.diagnostics.push_back(diagnostic("independent_lifecycle", "inferred-1031-releasewave-instance-lifecycle-v1",
        "separate source visual durations and no-image attack ANI; 60US object tick removes on ended",
        "1031 accepted-hit history, network ownership and exact cancellation not observed",
        "host owns independent clocks, single attack ledger and explicit death/room/reload cleanup"));
    validate(out);
    // Fail essential malformed/ambiguous source before the activation/cost boundary.
    skillInteger(out.skillData, "[maximum level]", 1);
    skillInteger(out.skillData, "[required level]", 1);
    skillInteger(out.skillData, "[required level range]");
    skillField(out.skillData, "[skill fitness growtype]");
    skillField(out.skillData, "[growtype maximum level]");
    skillField(out.skillData, "[level info]"); skillField(out.skillData, "[static data]");
    return out;
}
Json ReleaseWaveQualification::json() const { return {{"ok",ok},{"reason",reason},{"trace",trace}}; }
ReleaseWaveQualification evaluateReleaseWaveQualification(const ReleaseWaveSourceContract &source,
    CharacterIdentity identity, int learnedLevel, int characterLevel) {
    ReleaseWaveQualification out;
    try {
        validate(source);
        if (identity.jobId != source.skill.jobId) throw std::runtime_error("wrong_job");
        if (identity.growtype < 0 || identity.awakening < 0) throw std::runtime_error("invalid_identity");
        if (learnedLevel <= 0) throw std::runtime_error("unlearned_skill");
        if (learnedLevel > skillInteger(source.skillData, "[maximum level]", 1))
            throw std::runtime_error("above_source_all_means_maximum");
        const auto &fitness = skillField(source.skillData, "[skill fitness growtype]");
        std::set<int> fits;
        for (const auto &v : fitness.field.values)
            if (!fits.insert(integer(v,"fitness")).second) throw std::runtime_error("repeated_fitness");
        out.trace.push_back({{"tag",fitness.field.tag},{"offset",fitness.field.offset},
            {"scope",fitness.scope},{"values",fitness.field.values},{"identity",identity.json()}});
        if (!fits.count(identity.growtype)) throw std::runtime_error("source_growtype_excluded");
        const auto maximum = source.skillData.purchaseMaximum(identity.growtype);
        if (!maximum || *maximum <= 0) throw std::runtime_error("source_growtype_ceiling_missing_or_zero");
        // This bounded adapter does not guess future second-growth table semantics.
        if (source.skillData.selected.count("[skill fitness second growtype]") ||
            source.skillData.selected.count("[second growtype maximum level]") ||
            source.skillData.ambiguousFields.count("[skill fitness second growtype]") ||
            source.skillData.ambiguousFields.count("[second growtype maximum level]"))
            throw std::runtime_error("additional_second_growth_source_requires_adapter");
        const int base = skillInteger(source.skillData, "[required level]", 1);
        const int range = skillInteger(source.skillData, "[required level range]");
        const int64_t required = int64_t(base) + int64_t(range) * (learnedLevel - 1);
        if (required > std::numeric_limits<int>::max()) throw std::runtime_error("source_required_level_overflow");
        out.trace.push_back({{"policy","inferred-server-required-level-v1"},{"classification","inferred"},
            {"formula","required + range * (learned - 1)"},{"learned",learnedLevel},
            {"required_character_level",required},{"character_level",characterLevel},
            {"purchase_maximum",*maximum},{"purchase_ceiling_is_not_all_means_ceiling",true},
            {"normal_ledger_validation_required_in_host",true}});
        if (characterLevel < required) throw std::runtime_error("below_source_required_level");
        if (!skillLevelValue(source.skillData.values("[level info]"), learnedLevel, 0))
            throw std::runtime_error("source_level_row_unavailable");
        out.ok = true; out.reason = "source_qualified_only";
    } catch (const std::exception &e) { out.reason = e.what(); }
    return out;
}
Json ReleaseWavePolicies::json() const {
    if (owner != ReleaseWaveOwnerPolicy::InferredLiveLocalOwnerV1 ||
        scalar != ReleaseWaveScalarPolicy::InferredUnmodifiedSourceColumn0V1)
        throw std::invalid_argument("ReleaseWave unknown owner/scalar policy");
    return {{"owner","inferred-1031-releasewave-live-local-owner-v1"},
        {"scalar","inferred-1031-releasewave-unmodified-column0-v1"},
        {"duration",durationName(duration)}, {"classification","inferred"}};
}
Json ReleaseWaveSpawn::json() const {
    return {{"kind",kind == ReleaseWaveSpawnKind::Visual ? "visual" : "attack_entity"},
        {"source",source.json()},{"attack_info_source",attackInfoSource.json()},
        {"animation",animation ? animation->path : std::string()},{"owner",owner.json()},
        {"action_id",actionId},{"attack_id",attackId},{"position",position},{"direction",direction},
        {"signed_attachment_argument",signedAttachmentArgument},{"object_id",objectId},
        {"speed",speed},{"scalar",scalar},{"follows_owner_position",followsOwnerPosition},
        {"remove_on_animation_end",removeOnAnimationEnd}};
}
Json ReleaseWaveActivationPlan::json() const {
    Json operations = Json::array(); for (const auto &spawn : spawns) operations.push_back(spawn.json());
    return {{"ok",ok},{"reason",reason},{"phase",phase},{"owner_gate_passed",ownerGatePassed},
        {"phase_duration_ms",phaseDurationMs},{"spawns",operations},{"trace",trace},{"diagnostics",diagnostics}};
}
ReleaseWaveActivationPlan planReleaseWavePhaseEvent(const ReleaseWaveSourceContract &source,
    const ReleaseWaveActivationRequest &request, const ReleaseWavePolicies &policies) {
    ReleaseWaveActivationPlan out; out.phase = request.phase;
    try {
        validate(source); const auto selected = policies.json();
        if (request.phase != 0 && request.phase != 1) throw std::runtime_error("invalid_cast_phase");
        if (!request.owner || !request.actionId) throw std::runtime_error("invalid_owner_or_action_identity");
        if (request.direction != -1 && request.direction != 1) throw std::runtime_error("invalid_direction");
        for (const auto coordinate : request.position)
            if (!std::isfinite(coordinate)) throw std::runtime_error("nonfinite_spawn_position");
        const auto eligibility = evaluateReleaseWaveQualification(source, request.identity,
            request.learnedLevel, request.characterLevel);
        out.trace.push_back({{"source_qualification",eligibility.json()}});
        if (!eligibility.ok) throw std::runtime_error(eligibility.reason);
        if (policies.duration == ReleaseWaveDurationPolicy::InferredZeroThenSourceStaticV1) {
            const auto &values = skillField(source.skillData, "[static data]").field.values;
            if (values.empty()) throw std::runtime_error("missing_phase1_static_duration");
            out.phaseDurationMs = {0, integer(values[0], "static phase1 duration")};
        } else {
            out.phaseDurationMs = {source.phaseMotions[0].animation->duration, source.phaseMotions[1].animation->duration};
        }
        out.trace.push_back({{"policies",selected},{"phase_duration_ms",out.phaseDurationMs},
            {"native60us_requested_phase0_duration",0},{"native60us_phase1_helper","54FF60 dynamic; not executed"},
            {"source_motion_duration_ms",{source.phaseMotions[0].animation->duration,source.phaseMotions[1].animation->duration}},
            {"duration_unit","simulation milliseconds; host schedules phase transitions separately from ANI clock"}});
        out.diagnostics = source.diagnostics;
        out.diagnostics.push_back(diagnostic("phase_duration_inference",durationName(policies.duration),
            "60US request0=0, dynamic phase1 helper; current1031 SKL static[0] and CHR phase ANI are retained",
            "1031 helper mapping and timer scaling not recovered",
            "selected duration is an explicit beta policy; source ANI150/600 is not native duration proof"));
        out.ownerGatePassed = request.ownerLive && bool(request.localOwner) && request.owner == request.localOwner;
        out.trace.push_back({{"policy",selected.at("owner")},{"owner",request.owner.json()},
            {"local_owner",request.localOwner.json()},{"owner_live",request.ownerLive},
            {"passed",out.ownerGatePassed},{"native_network_semantics_restored",false}});
        const auto scalarValue = skillLevelValue(source.skillData.values("[level info]"), request.learnedLevel, 0);
        if (!scalarValue || !std::isfinite(*scalarValue) || *scalarValue < 0 ||
            *scalarValue > std::numeric_limits<int32_t>::max()) throw std::runtime_error("invalid_source_damage_scalar");
        const float scalar = float(*scalarValue);
        const auto &column = skillField(source.skillData, "[level info]");
        out.trace.push_back({{"policy",selected.at("scalar")},{"classification","inferred"},
            {"mode",source.skillData.mode},{"column",0},{"level",request.learnedLevel},
            {"source_offset",column.field.offset},{"source_scope",column.scope},{"scalar",scalar},
            {"modifier_snapshot","explicit empty beta baseline"},{"native_dynamic_scalar_restored",false}});
        out.diagnostics.push_back(diagnostic("scalar_baseline_inference", "inferred-1031-releasewave-unmodified-column0-v1",
            "60US scalar chain consumes level-info column0; current1031 source magic-attack display and column0",
            "1031 modifier/environment chain and full final damage formula not recovered",
            "unmodified source value is an instance fixed scalar, not final HP loss or weapon percent"));
        if (request.phase == 0) {
            if (out.ownerGatePassed && !request.attackId) throw std::runtime_error("invalid_attack_identity");
            for (size_t i = 0; i < source.visuals.size(); ++i) {
                ReleaseWaveSpawn spawn; spawn.source = source.visuals[i].source;
                spawn.animation = source.visuals[i].animation; spawn.owner = request.owner;
                spawn.actionId = request.actionId; spawn.position = request.position; spawn.direction = request.direction;
                spawn.signedAttachmentArgument = i == 0 ? 1 : -1; spawn.followsOwnerPosition = true;
                out.spawns.push_back(std::move(spawn));
            }
            if (out.ownerGatePassed) {
                ReleaseWaveSpawn spawn; spawn.kind = ReleaseWaveSpawnKind::AttackEntity;
                spawn.source = source.objectSource.source; spawn.attackInfoSource = source.attackInfo.source;
                spawn.animation = source.attackAnimation.animation; spawn.owner = request.owner;
                spawn.actionId = request.actionId; spawn.attackId = request.attackId;
                spawn.position = request.position; spawn.direction = request.direction;
                spawn.objectId = source.objectRegistration.id; spawn.scalar = scalar;
                out.spawns.push_back(std::move(spawn));
            } else out.diagnostics.push_back({{"code","owner_gate_rejected_attack_only"},
                {"visual_count",2},{"attack_count",0},{"source_order","two visuals precede conditional spawn"}});
        }
        out.ok = true; out.reason = "planned_only_host_must_commit";
    } catch (const std::exception &error) {
        out.ok = false; out.spawns.clear(); out.reason = error.what();
        out.diagnostics.push_back({{"code","activation_rejected"},{"reason",out.reason},{"no_host_mutation",true}});
    }
    return out;
}
} // namespace dnf
