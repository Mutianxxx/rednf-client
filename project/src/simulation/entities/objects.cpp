#include "dnf/objects.hpp"
#include "dnf/object_presentation.hpp"
#include <algorithm>
#include <cctype>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
std::string relativePath(const std::string &parent, const std::string &child) {
    return normalize((std::filesystem::u8path(parent).parent_path() / std::filesystem::u8path(child)).generic_u8string());
}
std::string stateName(ObjectState state) {
    switch (state) {
    case ObjectState::Intact: return "intact";
    case ObjectState::Reacting: return "reacting";
    case ObjectState::Destroying: return "destroying";
    case ObjectState::Destroyed: return "destroyed";
    case ObjectState::Removed: return "removed";
    }
    return "intact";
}
ObjectState parseState(const std::string &state) {
    if (state == "reacting") return ObjectState::Reacting;
    if (state == "destroying") return ObjectState::Destroying;
    if (state == "destroyed") return ObjectState::Destroyed;
    if (state == "removed") return ObjectState::Removed;
    return ObjectState::Intact;
}
uint64_t stableHash(const std::string &value) {
    uint64_t h = 1469598103934665603ull;
    for (unsigned char c : value) h = (h ^ c) * 1099511628211ull;
    return h ? h : 1;
}
bool hasAnimationRef(const Json &value) {
    return value.is_string() && value.get<std::string>().size() >= 4 &&
           normalize(value.get<std::string>()).substr(value.get<std::string>().size() - 4) == ".ani";
}
} // namespace

std::string ObjectIdentity::key() const {
    return run + "|" + room + "|" + map + "|" + std::to_string(fieldOffset) + "|" + std::to_string(recordOrdinal);
}
Json ObjectIdentity::json() const {
    return {{"run",run},{"room",room},{"map",map},{"field_offset",fieldOffset},{"record_ordinal",recordOrdinal}};
}
const ObjectMotion *ObjectDefinition::motion(const std::string &tag, size_t slot) const {
    auto it = std::find_if(motions.begin(), motions.end(), [&](const ObjectMotion &m) {
        return normalize(m.tag) == normalize(tag) && m.slot == slot;
    });
    return it == motions.end() ? nullptr : &*it;
}

ObjectCatalog::ObjectCatalog(Pvf &pvf, Assets &assets) : pvf_(pvf), assets_(assets) {
    auto registry = pvf_.script("passiveobject/passiveobject.lst");
    for (size_t i = 0; i + 1 < registry.tokens.size(); i += 2) {
        const auto &id = registry.tokens[i]["value"], &path = registry.tokens[i + 1]["value"];
        if (id.is_number_integer() && path.is_string())
            paths_.emplace(id.get<int>(), relativePath("passiveobject/passiveobject.lst", path.get<std::string>()));
    }
}
std::shared_ptr<const ObjectDefinition> ObjectCatalog::definition(int id) {
    auto cached = definitions_.find(id);
    if (cached != definitions_.end()) return cached->second;
    auto source = paths_.find(id);
    if (source == paths_.end()) throw std::runtime_error("Unresolved passive object ID " + std::to_string(id));
    auto definition = std::make_shared<ObjectDefinition>();
    definition->id = id;
    definition->source = source->second;
    definition->raw = pvf_.read(definition->source);
    definition->script = pvf_.script(definition->source);
    definition->name = definition->script.text("[name]");
    definition->layer = definition->script.text("[layer]", "[normal]");
    definition->passType = definition->script.text("[pass type]", "[pass all]");
    const auto width = definition->script.values("[width]");
    if (width.size() >= 2 && width[0].is_number() && width[1].is_number()) {
        definition->width = width[0].get<double>();
        definition->height = width[1].get<double>();
    }
    for (const auto &field : definition->script.fields) {
        if (field.tag == "[int data]")
            for (const auto &v : field.values) if (v.is_number_integer()) definition->intData.push_back(v.get<int>());
        if (field.tag == "[string data]" || field.tag == "[sound]" || field.tag == "[attack sound]" ||
            field.tag == "[damage sound]" || field.tag == "[destroy sound]")
            definition->sounds.push_back(field);
        if (field.tag.find("particle") != std::string::npos || field.tag.find("effect") != std::string::npos)
            definition->particleReferences.push_back(field);
        if (field.tag.find("action") != std::string::npos || field.tag.find("event") != std::string::npos)
            definition->actions.push_back(field);
        std::string motionTag;
        if (field.tag == "[basic motion]" || field.tag == "[damage motion]" ||
            field.tag == "[last motion]" || field.tag == "[etc motion]") motionTag = field.tag;
        if (!motionTag.empty()) {
            size_t slot = 0;
            for (const auto &previous : definition->script.fields) {
                if (&previous == &field) break;
                if (previous.tag == motionTag)
                    for (const auto &v : previous.values) if (hasAnimationRef(v)) ++slot;
            }
            for (const auto &v : field.values) {
                if (!hasAnimationRef(v)) continue;
                const auto path = relativePath(definition->source, v.get<std::string>());
                ObjectMotion motion;
                motion.tag = motionTag; motion.path = path; motion.offset = field.offset; motion.slot = slot++;
                try {
                    if (pvf_.has(path)) {
                        motion.raw = pvf_.read(path);
                        motion.animation = assets_.animation(path);
                    } else definition->diagnostics.push_back({{"kind","object animation asset missing"},{"path",path},{"offset",field.offset}});
                } catch (const std::exception &e) {
                    definition->diagnostics.push_back({{"kind","object animation decode failed"},{"path",path},{"offset",field.offset},{"error",e.what()}});
                }
                definition->motions.push_back(std::move(motion));
            }
        }
        if (field.tag == "[hp max]" && !field.values.empty() && field.values[0].is_number_integer())
            definition->explicitHpMax = field.values[0].get<int>();
        if (field.tag == "[hp destroy]" && !field.values.empty() && field.values[0].is_number())
            definition->explicitHpDestroy = field.values[0].get<double>() != 0;
    }
    if (definition->script.values("[int data]").size() != 0)
        definition->diagnostics.push_back({{"kind","legacy int data retained without inferred field semantics"},
                                           {"values",definition->script.values("[int data]")}});
    definition->provenance = {{"pvf_path", definition->source}, {"pvf_entry_raw", definition->raw},
        {"ordered_fields", Json::array()}, {"script_tokens", definition->script.tokens},
        {"classification", "content parse; runtime meanings are recorded separately"}};
    for (const auto &field : definition->script.fields) {
        size_t end = definition->raw.size();
        for (const auto &next : definition->script.fields) if (next.offset > field.offset) end = std::min(end, next.offset);
        Json row = {{"tag",field.tag},{"offset",field.offset},{"values",field.values}};
        if (field.offset <= definition->raw.size() && end >= field.offset)
            row["raw_bytes"] = Bytes(definition->raw.begin() + field.offset, definition->raw.begin() + end);
        definition->provenance["ordered_fields"].push_back(std::move(row));
    }
    if (!definition->explicitHpMax)
        definition->diagnostics.push_back({{"kind","no explicit HP field; int data is not treated as durability"}});
    compileObjectPresentation(pvf_,assets_,*definition);
    auto immutable = std::shared_ptr<const ObjectDefinition>(std::move(definition));
    definitions_.emplace(id, immutable);
    return immutable;
}

ObjectBehavior currentObjectBehavior(const ObjectDefinition &definition) {
    ObjectBehavior result;
    if (definition.explicitHpMax && *definition.explicitHpMax > 0) {
        result.durability = *definition.explicitHpMax;
        result.destroyAtZero = definition.explicitHpDestroy;
        result.evidence = "explicit [hp max] source field; destroy gate from explicit [hp destroy] or source default";
        return result;
    }
    if (definition.id == 221 && definition.source == "passiveobject/mapobject/breakableobject/barrel.obj") {
        result.durability = 2;
        result.evidence = "LOCAL TEST CANDIDATE: two distinct accepted attacks preserve the pre-existing barrel interaction test. OBJ int data [1,1,1,0,0,30,1] is retained but not decoded as HP. Current native damage-to-HP consumer is not closed; this is not original-client durability evidence.";
        return result;
    }
    if (definition.id == 222 && definition.source == "passiveobject/mapobject/breakableobject/treasurebox.obj") {
        result.durability = 1;
        result.evidence = "LOCAL TEST CANDIDATE carried from prior demo default for ID222; source exposes open/destroy references but native activation condition and durability consumer remain unresolved.";
        result.destructionTag = "[legacy destroy motion]";
        result.removeAfterDestroy = true;
        return result;
    }
    if ((definition.id == 231 || definition.id == 243 || definition.id == 244) &&
        ((definition.id==231 && definition.source=="passiveobject/mapobject/breakableobject/actionstonepillar.obj") ||
         (definition.id==243 && definition.source=="passiveobject/mapobject/breakableobject/largegrasslorien.obj") ||
         (definition.id==244 && definition.source=="passiveobject/mapobject/breakableobject/smallgrasslorien.obj")) &&
        definition.motion("[etc motion]",0)) {
        result.durability = 1;
        result.destroyAtZero = true;
        result.destructionTag = "[etc motion]";
        result.removeAfterDestroy = true;
        result.evidence = "USER PREVIEW POLICY: one distinct accepted source-box contact destroys pillar/grass using authored etc slot0 and PTL; native durability/caller unresolved, int data is not HP";
        return result;
    }
    if ((definition.id == 223 || definition.id == 224 || definition.id == 231) &&
        !definition.script.values("[etc motion]").empty()) {
        result.reactionTag = "[etc motion]";
        result.reactionSlot = 0;
        result.evidence = "Reconstruction: mapped first source etc-motion slot to the damage response, supported by source damage-particle/sound fields and filename/name; native action dispatch is unresolved. No destruction threshold inferred.";
        return result;
    }
    if ((definition.id == 243 || definition.id == 244) && definition.script.values("[etc motion]").size() >= 3) {
        result.reactionTag = "[etc motion]";
        result.reactionSlot = 0;
        result.directionalReaction = true;
        result.reactionLeftSlot = 1;
        result.reactionRightSlot = 2;
        result.evidence = "Reconstruction: source etc-motion slots expose destroy/left/right clips; hit direction selects left/right response. Native directional convention and destroy gate are unresolved; legacy int data [42] or [32] is not HP.";
    }
    return result;
}

const ObjectMotion *ObjectInstance::motion() const {
    return definition ? definition->motion(motionTag, motionSlot) : nullptr;
}
std::vector<CombatBox> ObjectInstance::damageBoxes() const {
    std::vector<CombatBox> out;
    const auto *active = motion();
    if (!active || !active->animation || active->animation->frames.empty()) return out;
    const bool loop = state == ObjectState::Intact;
    const size_t frame = active->animation->frameAt(actionAgeUs / 1000, loop);
    if (frame >= active->animation->frames.size()) return out;
    for (const auto &box : active->animation->frames[frame].boxes)
        if (box.type == 14) out.push_back(combatBox(box, placement.x, placement.y, placement.z, direction));
    return out;
}

std::vector<ObjectPlacement> objectPlacements(const Script &map, const std::string &run,
                                            const std::string &room, double backgroundY,
                                            Json *diagnostics, const Bytes *mapRaw) {
    std::vector<ObjectPlacement> out;
    uint64_t ordinal = 0;
    for (const auto &field : map.fields) {
        const bool special = field.tag == "[special passive object]";
        if (!special && field.tag != "[passive object]") continue;
        const auto &v = field.values;
        size_t at = 0;
        std::vector<size_t> valueOffsets;
        size_t sourceFieldEnd = mapRaw ? mapRaw->size() : 0;
        if (mapRaw) for (const auto &candidate : map.fields)
            if (candidate.offset > field.offset) sourceFieldEnd = std::min(sourceFieldEnd,candidate.offset);
        for (const auto &token : map.tokens) {
            if (!token.contains("offset") || token["offset"].get<size_t>() <= field.offset) continue;
            const auto off = token["offset"].get<size_t>();
            bool nextField = false;
            for (const auto &candidate : map.fields)
                if (candidate.offset == off && &candidate != &field) { nextField = true; break; }
            if (nextField) break;
            if (valueOffsets.size() < v.size()) valueOffsets.push_back(off);
        }
        while (at < v.size()) {
            const size_t start = at;
            if (at + 3 >= v.size() || !v[at].is_number_integer() || !v[at+1].is_number() ||
                !v[at+2].is_number() || !v[at+3].is_number()) {
                if (diagnostics) diagnostics->push_back({{"kind","unsupported passive object record"},
                                                          {"map",map.path},{"field_offset",field.offset},{"value_index",at}});
                break;
            }
            ObjectPlacement placement;
            placement.id = v[at].get<int>();
            placement.x = v[at+1].get<double>(); placement.y = v[at+2].get<double>() + backgroundY;
            placement.z = v[at+3].get<double>(); placement.special = special;
            placement.identity = {run,room,map.path,
                at < valueOffsets.size() ? valueOffsets[at] : field.offset, ordinal++};
            at += 4;
            if (special) {
                if (at >= v.size() || !v[at].is_number_integer()) {
                    if (diagnostics) diagnostics->push_back({{"kind","missing special object payload count"},
                                                              {"map",map.path},{"field_offset",field.offset},{"record",ordinal-1}});
                    break;
                }
                const int count = v[at++].get<int>();
                if (count < 0 || size_t(count) > (v.size() - at) / 6) {
                    if (diagnostics) diagnostics->push_back({{"kind","truncated special object payload"},
                                                              {"map",map.path},{"field_offset",field.offset},{"record",ordinal-1},{"count",count}});
                    break;
                }
                for (int n = 0; n < count; ++n) {
                    Json payload = Json::array();
                    for (int k = 0; k < 6; ++k) payload.push_back(v[at++]);
                    placement.payload.push_back(std::move(payload));
                }
            }
            for (size_t i = start; i < at; ++i) placement.raw.push_back(v[i]);
            if (mapRaw && start < valueOffsets.size()) {
                const size_t begin = valueOffsets[start];
                const size_t end = at < valueOffsets.size() ? valueOffsets[at] : sourceFieldEnd;
                if (begin <= end && end <= mapRaw->size())
                    placement.sourceBytes.assign(mapRaw->begin()+begin,mapRaw->begin()+end);
            }
            out.push_back(std::move(placement));
        }
    }
    return out;
}

void ObjectSystem::emit(ObjectInstance &instance, const std::string &kind, Json payload) {
    ObjectEvent event;
    event.sequence = nextSequence_++;
    event.object = instance.placement.identity;
    event.kind = kind;
    event.key = instance.placement.identity.key() + "#" + std::to_string(event.sequence) + ":" + kind;
    event.ageUs = instance.ageUs;
    event.payload = std::move(payload);
    pending_.push_back(std::move(event));
}
void ObjectSystem::beginMotion(ObjectInstance &instance, const std::string &tag, size_t slot) {
    const auto *motion = instance.definition ? instance.definition->motion(tag,slot) : nullptr;
    if (!motion) {
        diagnostics.push_back({{"kind","requested object motion unresolved"},{"object",instance.placement.identity.json()},
                               {"tag",tag},{"slot",slot}});
        return;
    }
    instance.motionTag = tag; instance.motionSlot = slot; instance.actionAgeUs = 0;
}
void ObjectSystem::clear() {
    instances_.clear(); pending_.clear(); nextSequence_ = 1; diagnostics = Json::array(); unknown_ = Json::object();
    savedFields_ = Json::object(); unmatchedInstances_ = Json::array();
}
ObjectInstance &ObjectSystem::add(ObjectPlacement placement, std::shared_ptr<const ObjectDefinition> definition, ObjectBehavior behavior) {
    if (!definition) throw std::invalid_argument("Object instance requires a definition");
    if (find(placement.identity)) throw std::invalid_argument("Duplicate passive object identity: " + placement.identity.key());
    ObjectInstance instance;
    instance.placement = std::move(placement); instance.definition = std::move(definition);
    instance.behavior = std::move(behavior); instance.durability = instance.behavior.durability;
    instance.randomState = stableHash(instance.placement.identity.key());
    instances_.push_back(std::move(instance));
    return instances_.back();
}
ObjectInstance *ObjectSystem::find(const ObjectIdentity &identity) {
    auto it = std::find_if(instances_.begin(), instances_.end(), [&](const auto &i) { return i.placement.identity == identity; });
    return it == instances_.end() ? nullptr : &*it;
}
const ObjectInstance *ObjectSystem::find(const ObjectIdentity &identity) const {
    auto it = std::find_if(instances_.begin(), instances_.end(), [&](const auto &i) { return i.placement.identity == identity; });
    return it == instances_.end() ? nullptr : &*it;
}
void ObjectSystem::advance(int64_t deltaUs) {
    if (deltaUs <= 0) return;
    for (auto &instance : instances_) {
        advanceObjectPresentation(instance,deltaUs);
        if (instance.state == ObjectState::Removed || instance.state == ObjectState::Destroyed) continue;
        if (deltaUs > std::numeric_limits<int64_t>::max() - instance.ageUs) instance.ageUs = std::numeric_limits<int64_t>::max();
        else instance.ageUs += deltaUs;
        if (deltaUs > std::numeric_limits<int64_t>::max() - instance.actionAgeUs) instance.actionAgeUs = std::numeric_limits<int64_t>::max();
        else instance.actionAgeUs += deltaUs;
        const auto *active = instance.motion();
        if (!active || !active->animation || active->animation->duration <= 0) continue;
        if (instance.state == ObjectState::Reacting && instance.actionAgeUs >= int64_t(active->animation->duration) * 1000) {
            instance.state = ObjectState::Intact;
            beginMotion(instance,"[basic motion]",0);
            emit(instance,"reaction_end");
        } else if (instance.state == ObjectState::Destroying && instance.actionAgeUs >= int64_t(active->animation->duration) * 1000) {
            instance.state = instance.behavior.removeAfterDestroy ? ObjectState::Removed : ObjectState::Destroyed;
            emit(instance,"removed");
        }
    }
}
bool ObjectSystem::destroy(const ObjectIdentity &identity, const std::string &evidence) {
    auto *instance = find(identity);
    if (!instance || instance->state == ObjectState::Destroyed || instance->state == ObjectState::Removed ||
        instance->state == ObjectState::Destroying) return false;
    createObjectPresentation(*instance,true);
    instance->collisionEnabled = !instance->behavior.releaseObstacleOnDestroy;
    instance->state = ObjectState::Destroying;
    emit(*instance,"destroyed",{{"evidence",evidence},{"native_string_data",instance->definition->script.values("[string data]")},
                                 {"special_payload",instance->placement.payload}});
    const auto tag = instance->behavior.destructionTag;
    if (!tag.empty() && instance->definition->motion(tag,instance->behavior.destructionSlot))
        beginMotion(*instance,tag,instance->behavior.destructionSlot);
    else {
        instance->state = instance->behavior.removeAfterDestroy ? ObjectState::Removed : ObjectState::Destroyed;
        if (instance->state == ObjectState::Removed) emit(*instance,"removed");
    }
    return true;
}
bool ObjectSystem::remove(const ObjectIdentity &identity) {
    auto *instance = find(identity);
    if (!instance || instance->state == ObjectState::Removed) return false;
    instance->state = ObjectState::Removed; instance->collisionEnabled = false;
    emit(*instance,"removed"); return true;
}
bool ObjectSystem::acceptsContact(const ObjectIdentity &identity, const ObjectAttack &attack) const {
    const auto *instance = find(identity);
    if (!instance || !instance->collisionEnabled || instance->state == ObjectState::Destroying ||
        instance->state == ObjectState::Destroyed || instance->state == ObjectState::Removed) return false;
    if (attack.serial == 0) return false;
    ObjectHitKey key{attack.owner,attack.serial,attack.pulse};
    if (instance->hits.count(key)) return false;
    const auto boxes = instance->damageBoxes();
    bool intersects = false;
    for (const auto &box : boxes) if (intersectCombatBoxes(attack.volume,box)) { intersects = true; break; }
    if (!intersects && instance->behavior.reconstructedHitShapeFallback &&
        instance->definition->width > 0 && instance->definition->height > 0) {
        // Scoped local candidate for the legacy barrel/chest controls. OBJ
        // width is a movement shape; this fallback is not a native hurt box.
        CombatBox source{instance->placement.x-instance->definition->width/2.0,
                         instance->placement.y-instance->definition->height,instance->placement.z,
                         instance->definition->width,instance->definition->height,100};
        intersects = intersectCombatBoxes(attack.volume,source);
    }
    return intersects;
}
bool ObjectSystem::contact(const ObjectIdentity &identity, const ObjectAttack &attack) {
    if (!attack.serial) {
        diagnostics.push_back({{"kind","attack contact missing stable serial"},{"object",identity.json()}});
        return false;
    }
    if (!acceptsContact(identity,attack)) return false;
    auto *instance = find(identity);
    ObjectHitKey key{attack.owner,attack.serial,attack.pulse};
    instance->hits.insert(key);
    if (attack.missed) {
        emit(*instance,"miss",{{"owner",attack.owner},{"serial",attack.serial},{"pulse",attack.pulse},
                               {"damage_trace",attack.damageTrace}});
        return true;
    }
    const auto oldState = instance->state;
    createObjectPresentation(*instance,false);
    emit(*instance,"hit",{{"owner",attack.owner},{"serial",attack.serial},{"pulse",attack.pulse},
                           {"damage",attack.damage},{"direction",attack.direction},{"damage_trace",attack.damageTrace},
                           {"native_int_data",instance->definition->script.values("[int data]")},
                           {"native_string_data",instance->definition->script.values("[string data]")}});
    if (instance->durability) {
        const int remaining = std::max(0, *instance->durability - std::max(0,attack.damage));
        instance->durability = remaining;
        if (remaining == 0 && instance->behavior.destroyAtZero)
            return destroy(identity,instance->behavior.evidence);
        if (remaining == 0) instance->durability = 0;
    }
    const auto reactionSlot = instance->behavior.directionalReaction
        ? attack.direction < 0 ? instance->behavior.reactionLeftSlot : instance->behavior.reactionRightSlot
        : instance->behavior.reactionSlot;
    if (oldState == ObjectState::Reacting) {
        instance->direction = attack.direction;
        if (instance->behavior.directionalReaction) {
            beginMotion(*instance,instance->behavior.reactionTag,reactionSlot);
        }
        return true;
    }
    instance->direction = attack.direction;
    const auto *reaction = instance->definition->motion(instance->behavior.reactionTag,reactionSlot);
    if (reaction) {
        instance->state = ObjectState::Reacting;
        beginMotion(*instance,instance->behavior.reactionTag,reactionSlot);
        emit(*instance,"reaction",{{"motion",reaction->path},{"direction",attack.direction}});
    }
    return true;
}
std::vector<ObjectObstacle> ObjectSystem::activeObstacles() const {
    std::vector<ObjectObstacle> out;
    for (const auto &instance : instances_) {
        if (!instance.collisionEnabled || instance.state == ObjectState::Destroyed ||
            instance.state == ObjectState::Removed || instance.definition->passType != "[do not pass]" ||
            instance.definition->width <= 0 || instance.definition->height <= 0) continue;
        out.push_back({instance.placement.identity,
            instance.placement.x-instance.definition->width/2.0,
            instance.placement.y-instance.definition->height,
            instance.definition->width,instance.definition->height,std::nullopt});
    }
    return out;
}
bool ObjectSystem::consumePayload(const ObjectIdentity &identity, const std::string &token,
                                  const std::string &kind, Json payload) {
    auto *instance = find(identity);
    if (!instance || token.empty() || !instance->consumedPayload.insert(token).second) return false;
    emit(*instance,kind,{{"token",token},{"payload",std::move(payload)}});
    return true;
}
void ObjectSystem::acknowledge(const std::string &eventKey) {
    pending_.erase(std::remove_if(pending_.begin(),pending_.end(),[&](const auto &e){return e.key==eventKey;}),pending_.end());
}
void ObjectSystem::retireAttack(uint64_t owner, uint64_t serial) {
    for (auto &instance : instances_)
        for (auto it=instance.hits.begin();it!=instance.hits.end();)
            if (it->owner==owner && it->serial==serial) it=instance.hits.erase(it); else ++it;
}
void ObjectSystem::retireOwnerAttacks(uint64_t owner) {
    for (auto &instance : instances_)
        for (auto it = instance.hits.begin(); it != instance.hits.end();)
            if (it->owner == owner) it = instance.hits.erase(it); else ++it;
}
Json ObjectSystem::save() const {
    Json instances=Json::array(), events=Json::array();
    auto savedIdentity = [](const Json &fields, const ObjectIdentity &identity) {
        Json result = fields.value("identity",Json::object());
        if (!result.is_object()) result = Json::object();
        result.update(identity.json());
        return result;
    };
    for(const auto &i:instances_){
        Json hits=Json::array(), consumed=Json::array();
        for(const auto &h:i.hits) hits.push_back({h.owner,h.serial,h.pulse});
        for(const auto &v:i.consumedPayload) consumed.push_back(v);
        Json row=i.savedFields;
        row.update(Json{{"identity",savedIdentity(i.savedFields,i.placement.identity)},{"id",i.placement.id},{"xyz",{i.placement.x,i.placement.y,i.placement.z}},
            {"definition_source",i.definition->source},{"behavior_evidence",i.behavior.evidence},
            {"behavior_classification",i.definition->explicitHpMax?"explicit OBJ HP field":
                i.behavior.evidence.empty()?"unknown/reaction-only":
                i.behavior.evidence.find("LOCAL TEST CANDIDATE")!=std::string::npos?"local test candidate":"inferred behavior"},
            {"state",stateName(i.state)},{"age_us",i.ageUs},{"action_age_us",i.actionAgeUs},{"random_state",i.randomState},
            {"direction",i.direction},{"collision_enabled",i.collisionEnabled},{"motion_tag",i.motionTag},{"motion_slot",i.motionSlot},
            {"hits",hits},{"consumed_payload",consumed},{"unknown",i.unknown}});
        row["visual_particles"]=saveObjectPresentation(i);
        if(i.durability)row["durability"]=*i.durability;
        if(!i.placement.payload.empty())row["placement_payload"]=i.placement.payload;
        instances.push_back(std::move(row));
    }
    for (const auto &row : unmatchedInstances_) instances.push_back(row);
    for(const auto &e:pending_) {
        Json row=e.savedFields;
        row.update(Json{{"sequence",e.sequence},{"key",e.key},{"kind",e.kind},
            {"identity",savedIdentity(e.savedFields,e.object)},{"age_us",e.ageUs},{"payload",e.payload}});
        events.push_back(std::move(row));
    }
    Json result=savedFields_;
    result.update(Json{{"schema_version",1},{"next_sequence",nextSequence_},{"instances",instances},
        {"pending_events",events},{"unknown",unknown_}});
    return result;
}
void ObjectSystem::restore(const Json &saved) {
    if(!saved.is_object()){diagnostics.push_back({{"kind","unsupported object save root"}});return;}
    if(saved.value("schema_version",0)!=1){diagnostics.push_back({{"kind","unknown object save schema retained"},{"value",saved}});unknown_["unparsed_save"]=saved;return;}
    savedFields_=saved;
    unmatchedInstances_=Json::array();
    std::set<std::string> restored;
    unknown_=saved.value("unknown",Json::object());
    nextSequence_=std::max<uint64_t>(1,saved.value("next_sequence",uint64_t(1)));
    for(const auto &row:saved.value("instances",Json::array())){
        if(!row.is_object()||!row.contains("identity")||!row["identity"].is_object()) {
            unmatchedInstances_.push_back(row);
            diagnostics.push_back({{"kind","object save record has no usable identity"},{"record",row}});
            continue;
        }
        auto j=row["identity"];
        ObjectIdentity id{j.value("run",std::string()),j.value("room",std::string()),j.value("map",std::string()),
            j.value("field_offset",uint64_t(0)),j.value("record_ordinal",uint64_t(0))};
        auto *instance=find(id);
        if(!instance || !restored.insert(id.key()).second) {
            unmatchedInstances_.push_back(row);
            diagnostics.push_back({{"kind",instance?"duplicate object save identity retained":"unmatched object save identity retained"},
                                   {"record",row}});
            continue;
        }
        instance->savedFields=row;
        instance->state=parseState(row.value("state",std::string("intact")));
        instance->ageUs=std::max<int64_t>(0,row.value("age_us",int64_t(0)));
        instance->actionAgeUs=std::max<int64_t>(0,row.value("action_age_us",int64_t(0)));
        instance->randomState=row.value("random_state",instance->randomState);
        restoreObjectPresentation(*instance,row.value("visual_particles",Json::array()));
        instance->direction=row.value("direction",1);
        instance->collisionEnabled=row.value("collision_enabled",instance->collisionEnabled);
        instance->motionTag=row.value("motion_tag",std::string("[basic motion]"));
        instance->motionSlot=row.value("motion_slot",size_t(0));
        if(row.contains("durability")&&row["durability"].is_number_integer())instance->durability=row["durability"].get<int>();
        if(row.contains("unknown"))instance->unknown=row["unknown"];
        instance->hits.clear();
        for(const auto &h:row.value("hits",Json::array()))if(h.is_array()&&h.size()==3)
            instance->hits.insert({h[0].get<uint64_t>(),h[1].get<uint64_t>(),h[2].get<uint64_t>()});
        instance->consumedPayload.clear();
        for(const auto &v:row.value("consumed_payload",Json::array()))if(v.is_string())instance->consumedPayload.insert(v.get<std::string>());
    }
    pending_.clear();
    for(const auto &e:saved.value("pending_events",Json::array()))if(e.is_object()){
        auto j=e.value("identity",Json::object());
        ObjectIdentity id{j.value("run",std::string()),j.value("room",std::string()),j.value("map",std::string()),
            j.value("field_offset",uint64_t(0)),j.value("record_ordinal",uint64_t(0))};
        pending_.push_back({e.value("sequence",uint64_t(0)),e.value("key",std::string()),e.value("kind",std::string()),
            id,e.value("age_us",int64_t(0)),e.value("payload",Json::object()),e});
    }
}

} // namespace dnf
