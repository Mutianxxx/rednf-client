#include "dnf/swordman_stage_plan.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
const char *variantName(SwordmanStageVariant variant) {
    switch (variant) {
    case SwordmanStageVariant::OrdinaryGhostSlash: return "ordinary-ghost-slash";
    case SwordmanStageVariant::TripleSlash: return "triple-slash";
    case SwordmanStageVariant::FiveSlash: return "five-slash-candidate";
    }
    return "invalid";
}
void error(SwordmanStagePlan &plan, const std::string &code, const std::string &detail) {
    plan.diagnostics.push_back({{"severity", "error"}, {"code", code}, {"detail", detail}});
}
Json scriptSnapshot(const Script &script) {
    Json fields = Json::array();
    for (const auto &field : script.fields)
        fields.push_back({{"tag", field.tag}, {"offset", field.offset}, {"values", field.values}});
    return {{"path", script.path}, {"source", script.source}, {"fields", fields}, {"tokens", script.tokens}};
}
// A structural walk independent of the flattened Animation maps. Each token
// owns an exact, contiguous source byte span; repeated nodes remain ordered.
class AniTokens {
    Cursor cursor_;
    Json tokens_ = Json::array();
    template<class T> T scalar(const std::string &kind) {
        const auto start = cursor_.at;
        const auto value = cursor_.get<T>();
        tokens_.push_back({{"kind", kind}, {"offset", start}, {"length", sizeof(T)}, {"value", value}});
        return value;
    }
    void bytes(const std::string &kind, size_t count) {
        cursor_.need(count);
        const auto start = cursor_.at;
        cursor_.at += count;
        tokens_.push_back({{"kind", kind}, {"offset", start}, {"length", count},
            {"raw", Bytes(cursor_.b.begin() + start, cursor_.b.begin() + cursor_.at)}});
    }
    void text(const std::string &kind) {
        const auto size = scalar<uint32_t>(kind + ".byte-count");
        bytes(kind + ".cp936-bytes", size);
    }
    void property(bool global) {
        const auto node = scalar<uint16_t>(global ? "global.node" : "frame.node");
        size_t size = 0;
        switch (node) {
        case 0: case 1: case 10: size = 1; break;
        case 3: case 13: case 24: case 28: size = 2; break;
        case 7: case 27: size = 8; break;
        case 8: case 9: case 12: case 23: case 26: size = 4; break;
        case 11: {
            const auto effect = scalar<uint16_t>("graphic-effect.kind");
            if (effect > 6) throw std::runtime_error("Unsupported ANI graphic effect");
            size = effect == 5 ? 3 : effect == 6 ? 4 : 0;
            break;
        }
        case 16: text("sound-id"); return;
        case 17: case 25: return;
        case 18:
            if (!global) throw std::runtime_error("Unsupported frame ANI node18");
            size = 15;
            break;
        default: throw std::runtime_error("Unsupported ANI node " + std::to_string(node));
        }
        if (size) bytes("node" + std::to_string(node) + ".payload", size);
    }
  public:
    explicit AniTokens(const Bytes &raw) : cursor_{raw} {}
    Json read() {
        const auto frames = scalar<uint16_t>("frame-count");
        const auto names = scalar<uint16_t>("image-name-count");
        for (size_t i = 0; i < names; ++i) text("image-name");
        const auto globals = scalar<uint16_t>("global-node-count");
        for (size_t i = 0; i < globals; ++i) property(true);
        for (size_t frame = 0; frame < frames; ++frame) {
            const auto count = scalar<uint16_t>("frame.box-count");
            for (size_t i = 0; i < count; ++i) {
                scalar<uint16_t>("box.type");
                for (const char *axis : {"x", "y", "z", "w", "h", "d"}) scalar<int32_t>(axis);
            }
            if (scalar<int16_t>("frame.image-name-index") >= 0) scalar<uint16_t>("frame.image-index");
            scalar<int32_t>("frame.x"); scalar<int32_t>("frame.y");
            const auto properties = scalar<uint16_t>("frame.node-count");
            for (size_t i = 0; i < properties; ++i) property(false);
        }
        if (cursor_.at != cursor_.b.size()) throw std::runtime_error("ANI token walk has trailing bytes");
        return tokens_;
    }
};
size_t valueOffset(const Script &script, size_t fieldOffset, size_t index) {
    bool active = false;
    for (const auto &token : script.tokens) {
        if (token.at("offset").get<size_t>() == fieldOffset) { active = true; continue; }
        if (!active) continue;
        const int type = token.at("type").get<int>();
        if (type == 5) break;
        if (type == 9) continue;
        if (!index--) return token.at("offset").get<size_t>();
    }
    throw std::runtime_error("Missing exact source value token");
}
SourceRef selectedValueSource(Pvf &pvf, const SkillSourceData &data, const std::string &tag, size_t index) {
    const auto &field = data.selected.at(normalize(tag));
    return makeSourceRef(pvf, data.definition.source.script.path,
        valueOffset(data.definition.source.script, field.field.offset, index), 5, index, field.scope + ":" + tag);
}
SwordmanBoundResource resource(Pvf &pvf, Assets &assets, const std::string &path, bool animation, bool visual) {
    SwordmanBoundResource result;
    result.path = normalize(path);
    if (!pvf.has(result.path)) throw std::runtime_error("Missing PVF member: " + result.path);
    result.rawBytes = pvf.read(result.path);
    result.source = makeSourceRef(pvf, result.path);
    if (animation) {
        result.source.textEncoding = "binary-ANI;CP936-image-names";
        const auto decoded = std::make_shared<const Animation>(decodeAni(result.rawBytes, result.path));
        result.binaryTokens = AniTokens(result.rawBytes).read();
        if (decoded->frames.empty() || decoded->duration <= 0) throw std::runtime_error("Empty/nonprogressing ANI: " + result.path);
        for (const auto &frame : decoded->frames) {
            if (frame.duration < 0) throw std::runtime_error("Negative source delay: " + result.path);
            // Body templates need the caller's selected appearance/equipment.
            // Effect images are literal and can be preflighted here.
            if (visual && !frame.image.empty()) {
                if (frame.image.find('%') != std::string::npos)
                    throw std::runtime_error("Unresolved effect image template: " + frame.image);
                if (!assets.has(frame.image)) throw std::runtime_error("Missing effect IMG: " + frame.image);
                const auto pixels = assets.pixels(frame.image, frame.imageFrame);
                if (pixels.width <= 0 || pixels.height <= 0) throw std::runtime_error("Empty effect IMG: " + frame.image);
            }
        }
        result.animation = decoded;
    } else result.script = pvf.script(result.path);
    return result;
}
SwordmanBoundResource chrResource(Pvf &pvf, Assets &assets, const CharacterDefinition &character,
                                  const std::string &tag, size_t slot, bool animation) {
    size_t matches = 0;
    for (const auto &field : character.source.script.fields) if (normalize(field.tag) == normalize(tag)) ++matches;
    if (matches != 1) throw std::runtime_error("Missing/ambiguous CHR field: " + tag);
    const auto *binding = character.resource(tag, slot);
    if (!binding || binding->literal.empty() || !binding->exists)
        throw std::runtime_error("Missing/empty CHR slot: " + tag + ":" + std::to_string(slot));
    auto result = resource(pvf, assets, binding->path, animation, false);
    result.chrTag = tag; result.chrSlot = slot;
    result.declaration = makeSourceRef(pvf, character.source.script.path,
        valueOffset(character.source.script, binding->fieldOffset, slot), 5, slot, tag);
    result.declaration.literalPath = binding->literal;
    return result;
}
double staticValue(const SkillSourceData &data, size_t index) {
    const auto values = data.values("[static data]");
    if (values.size() <= index || !values[index].is_number()) throw std::runtime_error("Missing numeric SKL static[" + std::to_string(index) + "]");
    const double value = values[index].get<double>();
    if (!std::isfinite(value)) throw std::runtime_error("Nonfinite SKL static value");
    return value;
}
void validateColumns(const SkillSourceData &data, const std::vector<SwordmanSkillStage> &stages) {
    const auto table = data.values("[level info]");
    if (table.empty() || !table[0].is_number_integer()) throw std::runtime_error("Missing SKL level-info column count");
    const auto width = table[0].get<int64_t>();
    if (width <= 0 || width > std::numeric_limits<int>::max() || table.size() < size_t(width) + 1 ||
        (table.size() - 1) % size_t(width)) throw std::runtime_error("Malformed SKL level-info dimensions");
    const size_t rows = (table.size() - 1) / size_t(width);
    for (size_t i = 1; i < table.size(); ++i)
        if (!table[i].is_number() || !std::isfinite(table[i].get<double>())) throw std::runtime_error("Nonnumeric/nonfinite SKL level-info cell");
    for (const auto &stage : stages) for (size_t level = 1; level <= rows; ++level) {
        const auto percent = skillLevelValue(table, int(level), stage.percentColumn);
        if (!percent || *percent <= 0) throw std::runtime_error("Missing/nonpositive required percent column " + std::to_string(stage.percentColumn));
        if (stage.fixedColumn < width && !skillLevelValue(table, int(level), stage.fixedColumn))
            throw std::runtime_error("Invalid authored fixed column");
    }
}
} // namespace

Json SwordmanBoundResource::snapshot(bool includeRaw) const {
    Json result = {{"path", path}, {"chr_tag", chrTag}, {"chr_slot", chrSlot},
        {"source", source.json()}, {"declaration", declaration.json()}, {"byte_count", rawBytes.size()}};
    if (animation) {
        result["frames"] = Json::array(); result["globals"] = animation->globals;
        for (const auto &frame : animation->frames) {
            Json boxes = Json::array();
            for (const auto &box : frame.boxes) boxes.push_back({{"type", box.type}, {"x", box.x}, {"y", box.y},
                {"z", box.z}, {"w", box.w}, {"h", box.h}, {"d", box.d}});
            result["frames"].push_back({{"image", frame.image}, {"image_frame", frame.imageFrame},
                {"x", frame.x}, {"y", frame.y}, {"delay", frame.duration}, {"boxes", boxes}, {"properties", frame.properties}});
        }
    }
    if (includeRaw) {
        result["raw_bytes"] = rawBytes;
        result["binary_tokens"] = binaryTokens;
        if (!animation) result["script"] = scriptSnapshot(script);
    }
    return result;
}
Json SwordmanStageVisual::snapshot(bool includeRaw) const {
    Json result = {{"resource", resource.snapshot(includeRaw)}, {"attach_key", attachKey},
        {"offset", Json::array({offsetX, offsetY, offsetZ})}, {"mirror_offset_x", mirrorOffsetX},
        {"follow_actor", followActor}, {"independent_clock", independentClock}, {"inherit_actor_rate", inheritActorRate}};
    result["image_rate_override"] = imageRateOverride ? Json(*imageRateOverride) : Json();
    result["image_rate_source"] = imageRateSource ? imageRateSource->json() : Json();
    return result;
}
Json SwordmanSkillStage::snapshot(bool includeRaw) const {
    Json result = {{"index", index}, {"body", body.snapshot(includeRaw)}, {"attack", attack.snapshot(includeRaw)},
        {"percent_column", percentColumn}, {"fixed_column", fixedColumn},
        {"fixed_column_policy", fixedColumnZeroWhenAbsent ? "native-getter-zero-if-column-absent-inferred" : "required-source-column"},
        {"sounds", sounds}, {"visuals", Json::array()}};
    result["next_input_frame"] = nextInputFrame ? Json(*nextInputFrame) : Json();
    for (const auto &visual : visuals) result["visuals"].push_back(visual.snapshot(includeRaw));
    return result;
}
bool SwordmanStagePlan::usable() const {
    if (stages.empty()) return false;
    for (const auto &diagnostic : diagnostics) if (diagnostic.value("severity", "error") == "error") return false;
    return true;
}
Json SwordmanStagePlan::snapshot(bool includeRaw) const {
    Json result = {{"key", key.json()}, {"variant", variantName(variant)}, {"mode", mode},
        {"classification", classification}, {"usable", usable()}, {"skill_source", skillSource.snapshot(includeRaw)},
        {"character_source", characterSource.provenance}, {"diagnostics", diagnostics},
        {"evidence", evidence}, {"stages", Json::array()}};
    if (includeRaw) {
        result["character_source"]["raw_bytes"] = characterSource.bytes;
        result["character_source"]["script"] = scriptSnapshot(characterSource.script);
    }
    result["movement_speed_setter_input"] = movementSpeed ? Json(*movementSpeed) : Json();
    result["movement_acceleration_setter_input"] = movementAcceleration ? Json(*movementAcceleration) : Json();
    for (const auto &stage : stages) result["stages"].push_back(stage.snapshot(includeRaw));
    return result;
}
SwordmanStagePlan loadSwordmanStagePlan(Pvf &pvf, Assets &assets, const CharacterCatalog &catalog,
    SkillKey key, int segments, const std::string &mode) {
    SwordmanStagePlan plan;
    plan.key = key; plan.mode = normalize(mode);
    if (key.jobId != 0 || !((key.skillId == 5 && segments == 1) || (key.skillId == 8 && (segments == 3 || segments == 5)))) {
        error(plan, "unsupported-request", "Expected job0/skill5/1, job0/skill8/3 or job0/skill8/5");
        return plan;
    }
    plan.variant = key.skillId == 5 ? SwordmanStageVariant::OrdinaryGhostSlash :
        segments == 3 ? SwordmanStageVariant::TripleSlash : SwordmanStageVariant::FiveSlash;
    plan.evidence = {{"native_exe_sha256", "a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b"},
        {"native_pvf_sha256", "23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98"},
        {"target_pvf_sha256", pvf.identity()}, {"original_runtime_observation", false},
        {"binding_policy", "60US static control flow applied to current registered CHR/SKL/ANI/ATK; cross-version inference"},
        {"qualification_owner", "caller: ordinary uncharged branch or explicit five-slash mastery/weapon admission"},
        {"geometry_owner", "source body boxes and caller-selected EQU/LAY; no synthesized hit boxes"},
        {"runtime_owner", "caller: movement integration, input, clocks, MP/CD, damage modifiers, transactions and cleanup"},
        {"native_contract", key.skillId == 5 ?
            "reverse-60us/releases/20261020-01/analysis/combat_hardattack/README.md" :
            "reverse-60us/releases/20261020-01/analysis/combat_tripleslash/tripleslash-contract.json"}};
    try {
        if (plan.mode != "dungeon" && plan.mode != "pvp") throw std::runtime_error("Stage bindings support explicit dungeon/pvp only");
        const auto &character = catalog.at(key.jobId);
        if (normalize(character.registration.path) != "character/swordman/swordman.chr")
            throw std::runtime_error("Job0 registration is not the supported Swordman source");
        plan.characterSource = character.source;
        plan.skillSource = readSkillSourceData(catalog.skillDefinition(key), plan.mode);
        if (!plan.skillSource.ambiguousFields.empty()) throw std::runtime_error("Ambiguous selected SKL field");
        if (character.source.bytes != pvf.read(character.source.script.path) ||
            plan.skillSource.definition.source.bytes != pvf.read(plan.skillSource.definition.source.script.path))
            throw std::runtime_error("Catalog source bytes differ from the selected PVF");
        const auto root = std::filesystem::u8path(character.registration.path).parent_path();
        const auto expectedSkl = key.skillId == 5 ? "hardattack.skl" : "tripleslash.skl";
        if (std::filesystem::u8path(plan.skillSource.definition.registration.path).filename().u8string() != expectedSkl)
            throw std::runtime_error("Skill registration is outside the supported source policy");
        std::optional<float> imageRate;
        if (key.skillId == 5) {
            const auto value = staticValue(plan.skillSource, 0);
            if (value <= 0 || value > std::numeric_limits<float>::max()) throw std::runtime_error("Invalid Ghost Slash visual rate");
            imageRate = float(value) * 0.01f;
            if (!std::isfinite(*imageRate) || *imageRate <= 0) throw std::runtime_error("Invalid converted visual rate");
            plan.evidence["body_install"] = "0x731fa9..0x731fca";
            plan.evidence["effect_attach"] = "0x7326f0..0x7327eb; key1/key2; mirrored +40; inherit actor rate";
            plan.evidence["image_rate"] = "0x732791..0x7327bf: static[0] * float32(0.01) overwrites both frame components";
        } else {
            plan.movementSpeed = staticValue(plan.skillSource, 0);
            plan.movementAcceleration = staticValue(plan.skillSource, 1);
            plan.evidence["input_gate"] = "0x00d79744: frame indices [3,3,3,3]; not a millisecond gate";
            plan.evidence["movement"] = "0x732c63..0x732cda setter inputs; integrator/clamp/obstacle rules unresolved";
            plan.evidence["particle_gap"] = "global object2 every200ms at actor x+/-20; resource/type/lifetime unresolved, no placeholder spawned";
        }
        for (int i = 0; i < segments; ++i) {
            SwordmanSkillStage stage;
            stage.index = size_t(i);
            const size_t bodySlot = key.skillId == 5 ? 1 : size_t(3 + i);
            const size_t attackSlot = key.skillId == 5 ? 0 : segments == 3 && i == 2 ? 7 : size_t(2 + i);
            stage.body = chrResource(pvf, assets, character, "[etc motion]", bodySlot, true);
            stage.attack = chrResource(pvf, assets, character, "[etc attack info]", attackSlot, false);
            if (i + 1 < segments) {
                stage.nextInputFrame = 3;
                if (stage.body.animation->frames.size() <= *stage.nextInputFrame)
                    throw std::runtime_error("Body cannot reach source continuation frame3");
            }
            stage.percentColumn = key.skillId == 5 ? 0 : segments == 3 ? (i == 2 ? 1 : 0) : std::max(0, i - 2);
            stage.fixedColumn = key.skillId == 5 ? 1 : stage.percentColumn + 3;
            auto visual = [&](int attachKey, const std::string &relative) {
                SwordmanStageVisual result;
                result.resource = resource(pvf, assets, (root / relative).generic_u8string(), true, true);
                result.attachKey = attachKey;
                if (key.skillId == 5) {
                    result.offsetX = 40; result.imageRateOverride = imageRate;
                    result.imageRateSource = selectedValueSource(pvf, plan.skillSource, "[static data]", 0);
                }
                return result;
            };
            if (key.skillId == 5) {
                stage.visuals.push_back(visual(1, "Effect/Animation/HardAttack1.ani"));
                stage.visuals.push_back(visual(2, "Effect/Animation/HardAttack2.ani"));
            } else {
                stage.visuals.push_back(visual(1, "Effect/Animation/TripleSlash/Move" + std::to_string(i % 2 + 1) + ".ani"));
                stage.visuals.push_back(visual(2, "Effect/Animation/TripleSlash/Slash" + std::to_string(i + 1) + ".ani"));
                stage.sounds = {i + 1 == segments ? "SM_TRIPLE3" : i % 2 == 0 ? "SM_TRIPLE1" : "SM_TRIPLE2", "R_TSLASH"};
            }
            plan.stages.push_back(std::move(stage));
        }
        validateColumns(plan.skillSource, plan.stages);
    } catch (const std::exception &exception) { error(plan, "source-preflight-failed", exception.what()); }
    return plan;
}
SwordmanStagePlan loadSwordmanStagePlan(Pvf &pvf, Assets &assets, const CharacterCatalog &catalog,
    SwordmanStageVariant variant, const std::string &mode) {
    switch (variant) {
    case SwordmanStageVariant::OrdinaryGhostSlash: return loadSwordmanStagePlan(pvf, assets, catalog, {0,5}, 1, mode);
    case SwordmanStageVariant::TripleSlash: return loadSwordmanStagePlan(pvf, assets, catalog, {0,8}, 3, mode);
    case SwordmanStageVariant::FiveSlash: return loadSwordmanStagePlan(pvf, assets, catalog, {0,8}, 5, mode);
    }
    return loadSwordmanStagePlan(pvf, assets, catalog, {-1,-1}, 0, mode);
}
} // namespace dnf
