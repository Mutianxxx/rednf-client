#include "dnf/storage.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/source_weapon_qualification.hpp"
#include "dnf/session.hpp"
#include "dnf/experimental_character.hpp"
#include <set>
#include <thread>
#include <chrono>
#include <iomanip>
#include <limits>
#include <random>
#include <sstream>
#include <charconv>
#include <zlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#endif
namespace dnf {
namespace fs = std::filesystem;
namespace {
const std::array<std::string, 11> characterClasses = {"swordman", "fighter", "gunner", "mage", "priest",
    "atgunner", "thief", "atfighter", "atmage", "demonicswordman", "creatormage"};
CharacterIdentity savedIdentity(const Json &character) {
    const auto job = character.at("class").get<std::string>();
    const auto found = std::find(characterClasses.begin(), characterClasses.end(), job);
    if (found == characterClasses.end()) throw std::runtime_error("Unregistered saved character class: " + job);
    const int jobId = int(found - characterClasses.begin());
    auto identity = character.contains("identity") ? CharacterIdentity::fromJson(character.at("identity"))
                                                  : CharacterIdentity{jobId, 0, 0};
    if (identity.jobId != jobId) throw std::runtime_error("Saved class and explicit identity disagree");
    return identity;
}
std::string uuid() {
    // Identity allocation is separate from gameplay RNG: allocating a save
    // receipt or character cannot alter future loot or combat random streams.
    std::random_device random;
    std::array<unsigned char, 16> bytes{};
    for (auto &byte : bytes) byte = static_cast<unsigned char>(random());
    bytes[6] = (bytes[6] & 15) | 64;
    bytes[8] = (bytes[8] & 63) | 128;
    std::ostringstream out;
    out << std::hex << std::setfill('0');
    for (size_t i = 0; i < bytes.size(); ++i) {
        if (i == 4 || i == 6 || i == 8 || i == 10) out << '-';
        out << std::setw(2) << unsigned(bytes[i]);
    }
    return out.str();
}
bool validUuid(const std::string &value) {
    if (value.size() != 36) return false;
    for (size_t i = 0; i < value.size(); ++i) {
        if (i == 8 || i == 13 || i == 18 || i == 23) { if (value[i] != '-') return false; }
        else if (!((value[i] >= '0' && value[i] <= '9') || (value[i] >= 'a' && value[i] <= 'f'))) return false;
    }
    return true;
}
void migrateIdentities(Json &data) {
    const int previous = data.at("schema").get<int>();
    for (auto &character : data.at("characters")) if (!character.is_null()) {
        const auto known = savedIdentity(character).json();
        if (!character.contains("identity")) character["identity"] = Json::object();
        for (auto field = known.begin(); field != known.end(); ++field) character["identity"][field.key()] = field.value();
        if (!character.contains("uuid")) character["uuid"] = uuid();
    }
    if (previous < 5) {
        if (!data.contains("migration_history")) data["migration_history"] = Json::array();
        if (!data["migration_history"].is_array()) throw std::runtime_error("Invalid migration history; original preserved");
        data["migration_history"].push_back({{"from_schema", previous}, {"to_schema", 5},
            {"policy", "identity-and-uuid-v1; source binding requires explicit legacy import"}});
    }
    data["schema"] = 5;
}
bool valid(const Json &j) {
    if (!j.is_object() || !j.contains("schema") || !j["schema"].is_number_integer() ||
        (j["schema"] < 1 || j["schema"] > 5) || !j.contains("characters") ||
        !j["characters"].is_array() || j["characters"].size() != 20)
        return false;
    std::set<std::string> identities;
    for (const auto &c : j["characters"]) {
        if (!c.is_null() && (!c.is_object() || !c.contains("name") || !c["name"].is_string() ||
                            !c.contains("class") || !c["class"].is_string()))
            return false;
        if (!c.is_null()) { try { savedIdentity(c); } catch (...) { return false; } }
        if (!c.is_null() && c.contains("uuid")) {
            if (!c["uuid"].is_string() || !validUuid(c["uuid"].get<std::string>()) ||
                !identities.insert(c["uuid"].get<std::string>()).second) return false;
        }
    }
    return true;
}
// CRC32 is an accidental-corruption checksum, not an authenticity guarantee.
// Ordered JSON round-trips preserve the serialization used by this contract.
std::string checksum(Json value) {
    value["_storage"].erase("checksum");
    const auto serialized = value.dump();
    uLong crc = crc32(0L, Z_NULL, 0);
    size_t offset = 0;
    while (offset < serialized.size()) {
        const auto count = static_cast<uInt>(std::min<size_t>(serialized.size() - offset, std::numeric_limits<uInt>::max()));
        crc = crc32(crc, reinterpret_cast<const Bytef *>(serialized.data() + offset), count);
        offset += count;
    }
    std::ostringstream out; out << std::hex << std::setfill('0') << std::setw(8) << crc;
    return out.str();
}
bool validSnapshot(const Json &j) {
    if (!valid(j)) return false;
    if (j.at("schema") != 5) return true;
    if (!j.contains("_storage") || !j["_storage"].is_object()) return false;
    const auto &s = j["_storage"];
    if (!s.contains("format") || !s["format"].is_number_integer() || (s["format"] != 1 && s["format"] != 2) || !s.contains("generation") ||
        !s["generation"].is_number_unsigned() || !s.contains("commit_id") || !s["commit_id"].is_string() ||
        !s.contains("parent_commit") || !s["parent_commit"].is_string() ||
        !s.contains("request_id") ||
        !s.contains("content_identity") || !s["content_identity"].is_string() ||
        !s.contains("receipts") || !s["receipts"].is_object() ||
        !s.contains("checksum_kind") || s["checksum_kind"] != "crc32-json-utf8-v1" ||
        !s.contains("checksum") || !s["checksum"].is_string()) return false;
    const auto generation=s["generation"].get<uint64_t>();
    const auto id=s["commit_id"].get<std::string>(), parent=s["parent_commit"].get<std::string>();
    if(!generation||!validUuid(id)||
       (generation==1?!parent.empty():!validUuid(parent)))return false;
    const auto &receipts=s["receipts"];
    for(auto entry=receipts.begin();entry!=receipts.end();++entry) {
        const auto &receipt=entry.value();
        if(entry.key().empty()||entry.key().size()>512||!receipt.is_object()||
            !receipt.contains("request_id")||receipt["request_id"]!=entry.key()||
            !receipt.contains("commit_id")||!receipt["commit_id"].is_string()||!validUuid(receipt["commit_id"].get<std::string>())||
            !receipt.contains("generation")||!receipt["generation"].is_number_unsigned()||receipt["generation"]==0||receipt["generation"]>generation||
            !receipt.contains("content_identity")||receipt["content_identity"]!=s["content_identity"])return false;
    }
    if (s["format"] == 1) {
        if (!s["request_id"].is_string()) return false;
        const auto request = s["request_id"].get<std::string>();
        if (request.empty() || request.size() > 512 || !receipts.contains(request) ||
            receipts[request]["commit_id"] != id || receipts[request]["generation"] != generation) return false;
    } else {
        if (!s.contains("kind") || !s["kind"].is_string() || !s.contains("result") || !s["result"].is_object()) return false;
        const auto &result = s["result"];
        if (!result.contains("kind") || result["kind"] != s["kind"] ||
            !result.contains("request_id") || result["request_id"] != s["request_id"] ||
            !result.contains("commit_id") || result["commit_id"] != id ||
            !result.contains("generation") || !result["generation"].is_number_unsigned() || result["generation"] != generation ||
            !result.contains("content_identity") || result["content_identity"] != s["content_identity"]) return false;
        if (s["kind"] == "checkpoint") {
            if (!s["request_id"].is_null()) return false;
        } else if (s["kind"] == "business") {
            if (!s["request_id"].is_string()) return false;
            const auto request = s["request_id"].get<std::string>();
            if (request.empty() || request.size() > 512 || !receipts.contains(request) || receipts[request] != result) return false;
        } else return false;
    }
    for (const auto &c : j["characters"]) if (!c.is_null() && !c.contains("uuid")) return false;
    return s["checksum"] == checksum(j);
}
class CompatibilityError : public std::runtime_error { public: using std::runtime_error::runtime_error; };
void checkVersion(const Json &j) {
    if (j.is_object() && j.contains("schema") && j["schema"].is_number_integer() && j["schema"] > 5)
        throw CompatibilityError("Save schema is newer than supported schema 5; refusing backup downgrade");
    if (j.is_object() && j.contains("_storage") && j["_storage"].is_object() &&
        j["_storage"].contains("format") && j["_storage"]["format"].is_number_integer() && j["_storage"]["format"] > 2)
        throw CompatibilityError("Save envelope is newer than supported format 2; refusing backup downgrade");
    if (j.is_object() && j.contains("_storage") && j["_storage"].is_object()) {
        const auto &metadata = j["_storage"];
        if (metadata.value("format", Json()) == 2 && metadata.contains("kind") && metadata["kind"].is_string() &&
            metadata["kind"] != "checkpoint" && metadata["kind"] != "business")
            throw CompatibilityError("Unsupported save commit kind; refusing backup downgrade");
    }
}
void checkContentIdentity(const Json &j, const std::string &expected) {
    // A parseable foreign identity must never be treated as local corruption
    // and bypassed through an older backup, even if other fields were damaged.
    if (j.is_object() && j.contains("_storage") && j["_storage"].is_object() &&
        j["_storage"].contains("content_identity") && j["_storage"]["content_identity"].is_string()) {
        const auto saved = j["_storage"]["content_identity"].get<std::string>();
        if (!saved.empty() && saved != expected)
            throw CompatibilityError("Saved content identity differs from selected ContentProfile; originals preserved");
    }
}
void checkSupportedCharacters(const Json &j) {
    if(!j.is_object()||!j.contains("characters")||!j["characters"].is_array())return;
    for(const auto &character:j["characters"])if(character.is_object()&&character.contains("class")&&character["class"].is_string()) {
        const auto job=character["class"].get<std::string>();
        if(std::find(characterClasses.begin(),characterClasses.end(),job)==characterClasses.end())
            throw CompatibilityError("Unknown saved character class must remain quarantined; refusing backup downgrade: "+job);
    }
}
void writeBytes(const fs::path &path, const Bytes &bytes) {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out) throw std::runtime_error("Cannot create save staging file " + path.u8string());
    out.write(reinterpret_cast<const char *>(bytes.data()), std::streamsize(bytes.size()));
    out.flush();
    if (!out) throw std::runtime_error("Cannot write save staging file " + path.u8string());
    out.close();
    if (!out) throw std::runtime_error("Cannot close save staging file " + path.u8string());
}
void writeSnapshot(const fs::path &path, const Json &value) {
    const auto serialized = value.dump(2);
    writeBytes(path, Bytes(serialized.begin(), serialized.end()));
}
void durableFlush(const fs::path &path) {
#ifdef _WIN32
    HANDLE h = CreateFileW(path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE)
        throw std::runtime_error("Cannot flush save " + path.u8string());
    BOOL flushed = FlushFileBuffers(h);
    CloseHandle(h);
    if (!flushed) throw std::runtime_error("Save flush failed: " + path.u8string());
#else
    const int descriptor = ::open(path.c_str(), O_WRONLY);
    if (descriptor < 0) throw std::runtime_error("Cannot open save for fsync " + path.u8string());
    const int result = ::fsync(descriptor); ::close(descriptor);
    if (result != 0) throw std::runtime_error("Save fsync failed: " + path.u8string());
#endif
}
void durableReplace(const fs::path &tmp, const fs::path &p) {
#ifdef _WIN32
    for (int attempt = 0; ; attempt++) {
        if (MoveFileExW(tmp.c_str(), p.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) break;
        DWORD error = GetLastError();
        if (attempt >= 20 || (error != ERROR_SHARING_VIOLATION && error != ERROR_LOCK_VIOLATION && error != ERROR_ACCESS_DENIED))
            throw std::runtime_error("Atomic save failed: " + p.u8string() + " win32=" + std::to_string(error));
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
#else
    fs::rename(tmp, p);
    const auto parent = p.parent_path().empty() ? fs::path(".") : p.parent_path();
    const int descriptor = ::open(parent.c_str(), O_RDONLY);
    if (descriptor < 0) throw std::runtime_error("Cannot open save directory for fsync");
    const int result = ::fsync(descriptor); ::close(descriptor);
    if (result != 0) throw std::runtime_error("Save directory fsync failed");
#endif
}
void durableCopy(const fs::path &target, const Bytes &bytes) {
    auto staged = target; staged += ".tmp." + uuid();
    writeBytes(staged, bytes); durableFlush(staged); durableReplace(staged, target);
}
int64_t validateSimulationRestore(const Json &checkpoint) {
    // Validate using the same resource-free checkpoint types consumed by
    // World::restoreSimulationCheckpoint. No controller, entity in the live
    // World, callback or gameplay stream is touched by this preflight.
    if(!checkpoint.is_object()||!checkpoint.at("schema").is_number_integer()||checkpoint.at("schema")!=1||
       checkpoint.at("restore_policy")!="cancel-transient-actions-input-and-effect-instances-v1")
        throw std::invalid_argument("Unsupported World simulation checkpoint");
    FixedStepClock clock;clock.restore(checkpoint.at("clock"));
    if(clock.tick()>uint64_t(std::numeric_limits<int64_t>::max())||clock.milliseconds()>uint64_t(std::numeric_limits<int64_t>::max()))
        throw std::invalid_argument("World checkpoint time exceeds signed storage");
    SimulationIdSources ids;ids.restore(checkpoint.at("ids"));
    if(checkpoint.contains("status_instance_ids")) {
        MonotonicIds statusIds;statusIds.restore(checkpoint.at("status_instance_ids"));
    }
    MonotonicIds effects;effects.restore(checkpoint.at("effects"));
    if(!effects.nextValue()||effects.nextValue()>uint64_t(std::numeric_limits<int>::max())+1)
        throw std::invalid_argument("World checkpoint effect ID exceeds legacy storage");
    SequencedCommandQueue<Input> inputs;
    inputs.restore(checkpoint.at("inputs"),[](const Json &value) {
        const auto integer=[](const Json &number,uint64_t maximum)->uint64_t {
            if(!number.is_number_integer()||(!number.is_number_unsigned()&&number.get<int64_t>()<0))
                throw std::invalid_argument("Invalid saved input integer");
            const auto parsed=number.get<uint64_t>();
            if(parsed>maximum)throw std::invalid_argument("Saved input integer exceeds supported range");
            return parsed;
        };
        if(!value.at("down").is_boolean())throw std::invalid_argument("Invalid saved input state");
        return Input{int64_t(integer(value.at("ns"),std::numeric_limits<int64_t>::max())),
            int(integer(value.at("key"),511)),value.at("down").get<bool>()};
    });
    RandomStreams random;random.restore(checkpoint.at("random"));
    EntityRegistry entities;entities.restore(checkpoint.at("entities"));
    // Selecting a character clears monsters; restoring then needs one fresh
    // player handle after retiring saved incarnations. Reject exhaustion now.
    entities.retireAll();entities.create();
    return int64_t(clock.milliseconds());
}
int64_t restoreInteger(const Json &value, int64_t minimum, int64_t maximum, const std::string &field) {
    if (!value.is_number_integer() ||
        (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(maximum)))
        throw std::invalid_argument("Invalid saved integer: " + field);
    const auto number = value.get<int64_t>();
    if (number < minimum || number > maximum)
        throw std::invalid_argument("Saved integer is out of range: " + field);
    return number;
}
int legacyClampedInteger(const Json &character, const char *field, int fallback, int minimum, int maximum) {
    const auto value = character.find(field);
    if (value == character.end() || !value->is_number_integer()) return fallback;
    // Compare before narrowing so a corrupt wide JSON integer cannot wrap into
    // a seemingly valid legacy level or weapon category.
    if (value->is_number_unsigned()) {
        const auto number = value->get<uint64_t>();
        if (number > uint64_t(maximum)) return maximum;
        return std::max(minimum, int(number));
    }
    return int(std::clamp<int64_t>(value->get<int64_t>(), minimum, maximum));
}
void validateCharacterFields(const Json &character, const World &world, bool authoritativeLearning = false,
                             bool experimentalTarget = false) {
    const auto knownInteger = [&](const char *container, const std::string &key) {
        if (!character.contains(container)) return;
        const auto &values = character.at(container);
        if (!values.is_object())
            throw std::invalid_argument(std::string("Invalid saved character object: ") + container);
        if (values.contains(key))
            restoreInteger(values.at(key), std::numeric_limits<int>::min(), std::numeric_limits<int>::max(),
                           std::string(container) + "." + key);
    };
    // Only this controller's consumed values have an int32 contract. Future
    // skill keys and their metadata are retained without guessing their type.
    if (!authoritativeLearning && !experimentalTarget) {
        const auto target=savedIdentity(character);
        for (const auto &skill : world.compatibilitySkillView(target)) knownInteger("skills", std::to_string(skill.id));
        for (const auto &passive : world.compatibilitySkillView(target,true)) knownInteger("passives", passive.key);
        knownInteger("passives", "bloodyvigorous");
    }
    if (!experimentalTarget && character.contains("bindings") && character.at("bindings").is_array() &&
        character.at("bindings").size() == world.bindings.size())
        for (const auto &binding : character.at("bindings"))
            restoreInteger(binding, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), "bindings.skill_id");
    if (character.contains("skill_state") && !character.at("skill_state").is_object())
        throw std::invalid_argument("Saved skill_state is not an object");
}
int normalCharacterLevel(const Json &character) {
    const auto progression=character.find("progression");
    if (progression!=character.end() && progression->is_object() && progression->contains("level"))
        return int(restoreInteger(progression->at("level"),1,99,"progression.level"));
    return legacyClampedInteger(character,"level",1,1,99);
}
void migrateLegacyLearning(const Json &character, const World &world, CharacterSkillState &skills, int64_t nowMs) {
    std::set<SkillKey> explicitKeys;
    const auto oldSnapshot=skills.snapshot(nowMs);
    for (const auto &record:oldSnapshot.at("skills")) explicitKeys.insert(SkillKey::fromJson(record.at("key")));
    const auto oldLevel=[&](const char *container,const std::string &key,SkillKey identity,int maximum) {
        const auto values=character.find(container);
        if (values!=character.end() && values->is_object() && values->contains(key))
            return std::clamp(values->at(key).get<int>(),0,std::max(1,maximum));
        return explicitKeys.count(identity)?skills.learnedLevel(identity):1;
    };
    for (const auto &skill:world.compatibilitySkillView(skills.identity())) skills.setLearnedLevel(skill.identity(),
        oldLevel("skills",std::to_string(skill.id),skill.identity(),skill.maxLevel));
    for (const auto &passive:world.compatibilitySkillView(skills.identity(),true)) skills.setLearnedLevel(passive.identity(),
        oldLevel("passives",passive.key,passive.identity(),passive.maxLevel));
    // Future numeric active IDs with a valid nonnegative level remain normal
    // legacy grants, even though no executable consumer is available yet.
    const auto active=character.find("skills");
    if (active!=character.end() && active->is_object()) for (auto value=active->begin();value!=active->end();++value) {
        int id=-1; const auto &name=value.key();
        const auto parsed=std::from_chars(name.data(),name.data()+name.size(),id);
        if (parsed.ec!=std::errc() || parsed.ptr!=name.data()+name.size() || id<0 || !value->is_number_integer()) continue;
        const SkillKey key{skills.identity().jobId,id};
        bool known=false; for (const auto &skill:world.compatibilitySkillView(skills.identity())) if (skill.identity()==key) known=true;
        if (known) continue;
        if (value->is_number_unsigned() && value->get<uint64_t>()>uint64_t(std::numeric_limits<int>::max())) continue;
        const auto level=value->get<int64_t>();
        if (level>=0 && level<=std::numeric_limits<int>::max()) skills.setLearnedLevel(key,int(level));
    }
}
void validateProgressionRestore(const Json &saved) {
    if (saved.is_null()) return; // Explicit legacy migration default.
    if (!saved.is_object()) throw std::invalid_argument("Saved progression is not an object");
    const auto intMaximum = std::numeric_limits<int>::max();
    const auto counter = [&](const char *field, int64_t minimum, int64_t maximum) {
        const auto value = saved.find(field);
        if (value != saved.end()) restoreInteger(*value, minimum, maximum, field);
    };
    counter("level", 1, 99);
    counter("gold", 0, intMaximum);
    counter("xp", 0, std::numeric_limits<int64_t>::max());
    counter("next_uid", 1, intMaximum - 1);
    for (const char *field : {"equipped", "quests", "events", "drops", "clears", "cooldowns", "cooldown_wall"})
        if (saved.contains(field) && !saved.at(field).is_object())
            throw std::invalid_argument(std::string("Invalid saved progression object: ") + field);
    if (saved.contains("inventory")) {
        const auto &inventory = saved.at("inventory");
        if (!inventory.is_array() || inventory.size() > Progression::inventoryCapacity)
            throw std::invalid_argument("Invalid saved progression inventory");
        for (const auto &entry : inventory) {
            if (!entry.is_object()) throw std::invalid_argument("Invalid saved progression inventory entry");
            // load() derives maximum UID + 1 in signed int arithmetic. Keep a
            // usable next UID and reject exhaustion before invoking that code.
            restoreInteger(entry.at("uid"), 1, intMaximum - 2, "inventory.uid");
            restoreInteger(entry.at("id"), 1, intMaximum, "inventory.id");
            restoreInteger(entry.at("count"), 1, intMaximum, "inventory.count");
            if (entry.contains("durability")) restoreInteger(entry.at("durability"), 0, intMaximum, "inventory.durability");
        }
    }
    if (saved.contains("equipped"))
        for (const auto &uid : saved.at("equipped")) restoreInteger(uid, 1, intMaximum - 2, "equipped.uid");
    if (saved.contains("cooldown_wall"))
        for (const auto &deadline : saved.at("cooldown_wall"))
            restoreInteger(deadline, 0, std::numeric_limits<int64_t>::max(), "cooldown_wall.deadline");
}
void validatePreparedEquipment(const Progression &candidate, const CharacterDefinition &character) {
    const auto &inventory = candidate.state.at("inventory");
    for (auto equipped = candidate.state.at("equipped").begin(); equipped != candidate.state.at("equipped").end(); ++equipped) {
        const auto found = std::find_if(inventory.begin(), inventory.end(), [&](const Json &entry) {
            return entry.at("uid") == equipped.value();
        });
        if (found == inventory.end()) throw std::invalid_argument("Saved equipped item UID is missing");
        const auto *definition = candidate.item(found->at("id").get<int>());
        if (!definition) throw std::invalid_argument("Saved equipped item has no source definition; unequipped unknown items are preserved");
        if (!definition->equipment || definition->slot.empty() || definition->slot != equipped.key())
            throw std::invalid_argument("Saved equipped item does not match its source equipment slot");
        if (!equipmentAllowsJob(character, definition->source) ||
            (definition->slot == "[weapon]" && !characterWeaponSourceSupported(character,definition->source,definition->weapon)))
            throw std::invalid_argument("Saved equipped item is not supported by this character");
        if (candidate.level() < definition->minimumLevel)
            throw std::invalid_argument("Saved equipped item requires a higher character level");
    }
}
SourceRef experimentalEquipmentSource(const Script &source,const std::string &scope) {
    SourceRef ref;ref.packageIdentity=source.source.value("package_identity",std::string());
    ref.memberPath=source.path;ref.memberSha256=sha256(source.rawBytes);ref.byteLength=source.rawBytes.size();
    ref.literalPath=source.source.value("literal_path",source.path);ref.scope=scope;return ref;
}
void initializeExperimentalWeapon(Progression &candidate,const CharacterCatalog &catalog,CharacterIdentity identity) {
    const auto &character=catalog.at(identity.jobId);const auto defaults=catalog.defaultAppearanceSources(identity.jobId);
    const DefaultEquipmentSource *selected=nullptr;const ItemDefinition *definition=nullptr;
    for(const auto &entry:defaults.equipment) {
        if(!entry.registered || !entry.exists)continue;
        const auto &source=entry.source.script;size_t typeFields=0;bool weapon=false;
        for(const auto &field:source.fields)if(normalize(field.tag)=="[equipment type]") {
            ++typeFields;weapon=!field.values.empty() && field.values[0]=="[weapon]";
        }
        if(typeFields!=1 || !weapon || !equipmentAllowsJob(character,source))continue;
        const auto *item=candidate.item(entry.equipmentId);
        if(!item || !item->equipment || item->slot!="[weapon]" ||
           !characterWeaponSourceSupported(character,item->source,item->weapon) || candidate.level()<item->minimumLevel)continue;
        if(selected)throw std::invalid_argument("Experimental defaultEquipment has multiple qualified weapon entries");
        selected=&entry;definition=item;
    }
    if(!selected || !definition)throw std::invalid_argument("Experimental defaultEquipment has no unique qualified source weapon");
    if(!candidate.state.at("inventory").empty() || !candidate.state.at("equipped").empty())
        throw std::invalid_argument("Experimental starter can only initialize an absent saved inventory");
    const auto uid=int(restoreInteger(candidate.state.at("next_uid"),1,std::numeric_limits<int>::max()-2,"experimental_starter.uid"));
    // Explicit user experiment, using the same source-backed inventory instance
    // shape as Progression::grant. Qualification and all source attribute work
    // still run on this private candidate before World/Progression publication.
    candidate.state["inventory"].push_back({{"uid",uid},{"id",selected->equipmentId},{"count",1},{"durability",definition->durability}});
    candidate.state["next_uid"]=uid+1;candidate.state["equipped"]["[weapon]"]=uid;
    candidate.state["experimental_starter"]={{"schema",1},{"policy","user-experimental-sd-default-weapon-v1"},
        {"classification","user_requested_experiment"},{"native_creation_gift_confirmed",false},
        {"identity",identity.json()},{"equipment_id",selected->equipmentId},{"instance_uid",uid},
        {"source",experimentalEquipmentSource(selected->source.script,"experimental-starter-equipment").json()},
        {"settings_source",experimentalEquipmentSource(defaults.settings.script,"experimental-starter-defaultEquipment").json()},
        {"default_equipment_field_offset",selected->fieldOffset},{"default_equipment_value_index",selected->valueIndex},
        {"selection","unique registered readable EQU [weapon] in own SD defaultEquipment with job and level qualification"},
        {"repeat_policy","saved inventory, including an explicit empty array, is never refilled or rerolled"}};
}
}
struct CharacterStore::WriterLock {
#ifdef _WIN32
    HANDLE handle = INVALID_HANDLE_VALUE;
    explicit WriterLock(const fs::path &directory) {
        const auto path = directory / ".characters.writer.lock";
        handle = CreateFileW(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
                             nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (handle == INVALID_HANDLE_VALUE)
            throw std::runtime_error("Save directory already has a writer or is unwritable; use an independent --save-dir: " + directory.u8string());
    }
    ~WriterLock() { if (handle != INVALID_HANDLE_VALUE) CloseHandle(handle); }
#else
    int descriptor = -1;
    explicit WriterLock(const fs::path &directory) {
        const auto path = directory / ".characters.writer.lock";
        descriptor = ::open(path.c_str(), O_CREAT | O_RDWR, 0600);
        if (descriptor < 0 || ::flock(descriptor, LOCK_EX | LOCK_NB) != 0) {
            if (descriptor >= 0) ::close(descriptor);
            throw std::runtime_error("Save directory already has a writer or is unwritable; use an independent --save-dir: " + directory.u8string());
        }
    }
    ~WriterLock() { if (descriptor >= 0) { ::flock(descriptor, LOCK_UN); ::close(descriptor); } }
#endif
};
void atomicJson(const fs::path &p, const Json &j) {
    if (!p.parent_path().empty()) fs::create_directories(p.parent_path());
    auto staged = p; staged += ".tmp." + uuid();
    writeSnapshot(staged, j); durableFlush(staged); durableReplace(staged, p);
}
CharacterStore::CharacterStore(fs::path dir, std::string identity, bool allowLegacyImport)
    : directory_(fs::absolute(std::move(dir)).lexically_normal()), contentIdentity_(std::move(identity)) {
    fs::create_directories(directory_);
    writer_ = std::make_unique<WriterLock>(directory_);
    bool found = false;
    for (const char *name : {"characters.json", "characters.bak.json"}) {
        auto p = directory_ / name;
        if (!fs::exists(p))
            continue;
        found = true;
        try {
            auto j = Json::parse(readFile(p));
            checkVersion(j);
            checkContentIdentity(j, contentIdentity_);
            checkSupportedCharacters(j);
            if (!validSnapshot(j)) throw std::runtime_error("Invalid character slots, metadata or snapshot checksum");
            const auto savedContent = j.at("schema") == 5 ? j.at("_storage").at("content_identity").get<std::string>() : std::string();
            if (!savedContent.empty() && savedContent != contentIdentity_)
                throw CompatibilityError("Saved content identity differs from selected ContentProfile; originals preserved");
            if ((j.at("schema") != 5 || (savedContent.empty() && !contentIdentity_.empty())) && !allowLegacyImport)
                throw CompatibilityError("Unbound legacy save requires explicit --import-legacy-save into an isolated save directory");
            data = std::move(j);
            migrateIdentities(data);
            if (data.contains("_storage")) generation_ = data["_storage"].value("generation", uint64_t(0));
            if (savedContent.empty() && !contentIdentity_.empty())
                warnings.push_back({{"path", p.u8string()}, {"migration", "Explicit legacy import binds the next committed copy to selected content"}});
            committed_ = data;
            return;
        } catch (const CompatibilityError &) {
            // Falling back to another source identity or older schema could
            // silently rewrite a valid save. Such failures are never recovery.
            throw;
        } catch (const std::exception &e) {
            warnings.push_back({{"path", p.u8string()}, {"error", e.what()}});
        }
    }
    if (found)
        throw std::runtime_error("No valid character save or backup; originals preserved at " + directory_.u8string());
    data = {{"schema", 5}, {"characters", std::vector<Json>(20, nullptr)}};
    committed_ = data;
}
CharacterStore::~CharacterStore() = default;
void CharacterStore::requireWriter() const {
    if (closed_ || !writer_) throw std::runtime_error("Character store writer is closed");
}
void CharacterStore::close() {
    if (hasPendingCommit()) throw std::runtime_error("Retry the pending save before closing its writer");
    writer_.reset(); closed_ = true;
}
Json CharacterStore::checkpoint() {
    requireWriter();
    if (hasPendingCommit()) {
        if (pending_.at("_storage").at("kind") != "checkpoint")
            throw std::runtime_error("A failed business commit is pending; retry its request before checkpointing");
        return publishPending();
    }
    return prepareCommit(CommitKind::Checkpoint, {});
}
void CharacterStore::save() {
    (void)checkpoint();
}
Json CharacterStore::receipt(const std::string &requestId) const {
    if (committed_.contains("_storage") && committed_["_storage"].is_object()) {
        const auto &metadata = committed_["_storage"];
        if (metadata.contains("receipts") && metadata["receipts"].is_object() && metadata["receipts"].contains(requestId))
            return metadata["receipts"].at(requestId);
    }
    return nullptr;
}
Json CharacterStore::commit(const std::string &requestId) {
    requireWriter();
    if (requestId.empty() || requestId.size() > 512) throw std::runtime_error("Invalid save request identity");
    if (hasPendingCommit()) {
        if (pending_.at("_storage").at("kind") != "business" || pending_.at("_storage").at("request_id") != requestId)
            throw std::runtime_error("A failed commit is pending; retry it before accepting another command");
        return publishPending();
    }
    if (const auto previous = receipt(requestId); !previous.is_null()) return previous;
    return prepareCommit(CommitKind::Business, requestId);
}
Json CharacterStore::prepareCommit(CommitKind kind, const std::string &requestId) {
    if (!valid(data)) throw std::runtime_error("Refusing invalid character save");
    if (generation_ == std::numeric_limits<uint64_t>::max()) throw std::runtime_error("Save generation overflow");
    auto candidate = data;
    migrateIdentities(candidate);
    if (!valid(candidate)) throw std::runtime_error("Refusing duplicate or invalid character UUIDs");
    if (!candidate.contains("_storage")) candidate["_storage"] = Json::object();
    if (!candidate["_storage"].is_object()) throw std::runtime_error("Reserved storage metadata is malformed; originals preserved");
    const auto previousMetadata = committed_.value("_storage", Json::object());
    if (previousMetadata.value("format", Json()) == 1) {
        if (!candidate.contains("migration_history")) candidate["migration_history"] = Json::array();
        if (!candidate["migration_history"].is_array()) throw std::runtime_error("Invalid migration history; original preserved");
        Json migration = {{"from_envelope_format", 1}, {"to_envelope_format", 2},
            {"policy", "checkpoint-business-receipt-separation-v1; all historical receipts retained"}};
        // These names were unknown in format 1. Preserve any historical
        // extension before format 2 assigns their new defined meaning.
        for (const char *field : {"kind", "result"})
            if (candidate.at("_storage").contains(field)) migration["preserved_metadata"][field] = candidate.at("_storage").at(field);
        candidate["migration_history"].push_back(std::move(migration));
    }
    auto &metadata = candidate["_storage"];
    metadata["format"] = 2;
    metadata["generation"] = generation_ + 1;
    metadata["commit_id"] = uuid();
    metadata["parent_commit"] = previousMetadata.value("commit_id", std::string());
    metadata["kind"] = kind == CommitKind::Checkpoint ? "checkpoint" : "business";
    metadata["request_id"] = kind == CommitKind::Checkpoint ? Json() : Json(requestId);
    metadata["content_identity"] = contentIdentity_;
    metadata["checksum_kind"] = "crc32-json-utf8-v1";
    metadata["receipts"] = previousMetadata.value("receipts", Json::object());
    if(previousMetadata.value("content_identity",std::string()).empty()&&!contentIdentity_.empty()) {
        // Explicit legacy binding covers the full imported snapshot. Retain
        // prior receipt provenance while binding its idempotency namespace.
        for(auto &receipt:metadata["receipts"]) {
            receipt["legacy_content_identity"]=receipt.value("content_identity",std::string());
            receipt["content_identity"]=contentIdentity_;
        }
    }
    const Json result = {{"kind", metadata["kind"]}, {"request_id", metadata["request_id"]}, {"commit_id", metadata["commit_id"]},
        {"generation", generation_ + 1}, {"content_identity", contentIdentity_}};
    metadata["result"] = result;
    if (kind == CommitKind::Business) metadata["receipts"][requestId] = result;
    // Region captures can be made before the disk writer chooses its next
    // generation. Bind every known status bundle to this exact prepared root;
    // pending retry reuses this immutable candidate without recapturing rolls.
    for(auto &character:candidate.at("characters")) if(character.is_object()) {
        if(character.contains("simulation") && character["simulation"].contains("player_status"))
            character["simulation"]["player_status"]["commit_generation"]=generation_+1;
        if(character.contains("region_session") && character["region_session"].is_object()) {
            auto &region=character["region_session"];
            if(region.contains("player") && region["player"].contains("status_state"))
                region["player"]["status_state"]["commit_generation"]=generation_+1;
            if(region.contains("room_states") && region["room_states"].is_array())
                for(auto &room:region["room_states"]) if(room.is_array())
                    for(auto &actor:room) if(actor.is_object()) {
                        if(actor.contains("status_state"))actor["status_state"]["commit_generation"]=generation_+1;
                        if(actor.contains("source_action_cooldowns"))actor["source_action_cooldowns"]["commit_generation"]=generation_+1;
                        if(actor.contains("monster_event_ai_state"))actor["monster_event_ai_state"]["commit_generation"]=generation_+1;
                    }
        }
    }
    metadata["checksum"] = checksum(candidate);
    pending_ = std::move(candidate);
    return publishPending();
}
Json CharacterStore::retryPending() {
    requireWriter();
    if (!hasPendingCommit()) throw std::runtime_error("There is no pending save to retry");
    return publishPending();
}
Json CharacterStore::publishPending() {
    const auto point = [&](SaveFailurePoint value) { if (failureInjector_) failureInjector_(value); };
    const auto primary = directory_ / "characters.json";
    const auto id = pending_.at("_storage").at("commit_id").get<std::string>();
    bool alreadyPublished = false;
    if (fs::exists(primary)) {
        try {
            const auto existing = Json::parse(readFile(primary));
            checkVersion(existing);
            checkContentIdentity(existing, contentIdentity_);
            checkSupportedCharacters(existing);
            if (validSnapshot(existing) && existing.at("schema") == 5 &&
                existing.at("_storage").at("content_identity") != contentIdentity_ &&
                existing.at("_storage").at("content_identity") != "")
                throw CompatibilityError("Saved content identity changed since writer opened; refusing overwrite");
            alreadyPublished = validSnapshot(existing) && existing.at("schema") == 5 &&
                existing.at("_storage").at("commit_id") == id && existing == pending_;
        } catch (const CompatibilityError &) { throw; } catch (...) {}
    }
    if (!alreadyPublished) {
        const auto staged = directory_ / ("characters.pending." + id + ".json");
        point(SaveFailurePoint::BeforeWrite);
        writeSnapshot(staged, pending_);
        point(SaveFailurePoint::AfterWrite);
        durableFlush(staged);
        point(SaveFailurePoint::AfterFlush);
        if (Json::parse(readFile(staged)) != pending_ || !validSnapshot(pending_))
            throw std::runtime_error("Save staging validation failed; previous generation preserved");
        point(SaveFailurePoint::AfterValidation);
        if (fs::exists(primary)) {
            const auto bytes = readFile(primary);
            Json previous;
            try { previous = Json::parse(bytes); } catch (...) {}
            checkVersion(previous);
            if (validSnapshot(previous)) {
                // Binding an imported legacy file keeps an immutable original
                // as well as the rolling last-good backup.
                if (previous.at("schema") != 5 || previous.at("_storage").at("format") == 1 ||
                    (!contentIdentity_.empty() && previous.at("_storage").at("content_identity") == "")) {
                    const auto archive = directory_ / ("characters.legacy." + id + ".json");
                    if (!fs::exists(archive)) durableCopy(archive, bytes);
                }
                durableCopy(directory_ / "characters.bak.json", bytes);
            } else {
                const auto rejected = directory_ / ("characters.rejected." + id + ".json");
                if (!fs::exists(rejected)) durableCopy(rejected, bytes);
            }
        }
        point(SaveFailurePoint::AfterBackup);
        point(SaveFailurePoint::BeforePublish);
        durableReplace(staged, primary);
        point(SaveFailurePoint::AfterPublish);
    }
    data = pending_;
    committed_ = pending_;
    generation_ = committed_.at("_storage").at("generation").get<uint64_t>();
    const auto result = committed_.at("_storage").at("result");
    pending_ = nullptr;
    return result;
}
void CharacterStore::apply(int slot, World &w) const {
    applyPreparedAppearance(slot,w,nullptr);
}
void CharacterStore::applyPreparedAppearance(int slot, World &w,const CharacterAppearance *appearance,
    const std::function<void(const CharacterSkillState &,int,int64_t)> &equipmentPreflight) const {
    const auto &c = data.at("characters").at(slot);
    const auto identity=savedIdentity(c);
    w.characterCatalog().at(identity.jobId);
    if(!w.supportsCharacter(identity))throw std::runtime_error("Saved character controller is unavailable");
    const bool experimentalTarget=identity.jobId!=0;
    std::unique_ptr<ExperimentalCharacterRuntime> preparedExperimentalRuntime;
    std::optional<ExperimentalSkillConfiguration> manualPreview,testPreferences;
    const auto executionMode=c.value("experimental_skill_execution_mode",std::string("learned"));
    if(executionMode!="learned"&&executionMode!="manual_preview")
        throw std::invalid_argument("Unknown explicit skill execution mode");
    if(experimentalTarget) {
        preparedExperimentalRuntime=w.prepareExperimentalRuntime(identity,c.value("experimental_skill_configuration",Json()));
        // Old raw values are retained for explicit user preview, never imported
        // as learned levels. New saves have a separate preview field.
        const auto preview=c.value("experimental_manual_preview_configuration",
            c.contains("experimental_skill_execution_mode")?Json():c.value("experimental_skill_configuration",Json()));
        if(!preview.is_null()) {
            manualPreview.emplace(preparedExperimentalRuntime->plan());
            manualPreview->restore(preview,preparedExperimentalRuntime->plan());
        }
        if(executionMode=="manual_preview"&&!manualPreview)
            throw std::invalid_argument("Explicit manual preview requires its isolated saved configuration");
        if(c.contains("experimental_test_skill_configuration")&&!c.at("experimental_test_skill_configuration").is_null()) {
            testPreferences.emplace(preparedExperimentalRuntime->plan());
            testPreferences->restore(c.at("experimental_test_skill_configuration"),preparedExperimentalRuntime->plan());
        }
    }
    else if(c.contains("experimental_skill_configuration") || c.contains("experimental_cooldowns") ||
        c.contains("experimental_skill_execution_mode") || c.contains("experimental_manual_preview_configuration") ||
        c.contains("experimental_test_skill_configuration"))
        throw std::invalid_argument("Experimental skill state is not valid for this normal controller");
    const bool sourceLearning=w.usesSourceGrowth();
    const bool authoritativeLearning=sourceLearning && c.contains("skill_state") && c.at("skill_state").is_object() &&
        c.at("skill_state").contains("learning");
    validateCharacterFields(c, w, authoritativeLearning, experimentalTarget);
    const auto restoredNow=c.contains("simulation")?validateSimulationRestore(c.at("simulation")):w.nowMs();
    if(c.contains("simulation"))w.validateMonsterActionAiCheckpoint(c.at("simulation").value("source_monster_think",Json()));
    std::map<SkillKey,int64_t> experimentalCooldowns;
    if(experimentalTarget && c.contains("experimental_cooldowns")) {
        if(!c.contains("simulation"))throw std::invalid_argument("Experimental cooldowns require their saved simulation checkpoint");
        experimentalCooldowns=ExperimentalCharacterRuntime::prepareCooldownRestore(
            c.at("experimental_cooldowns"),preparedExperimentalRuntime->plan(),restoredNow);
    }
    w.validateCharacterRestoreCapacity(c.value("simulation",Json()));
    std::map<uint64_t,Json> statusApplications;
    const auto validateStatus=[&](const Json &bundle,EntityHandle oldTarget,const std::string &owner) {
        const auto generation=bundle.at("commit_generation").get<uint64_t>();
        if(!generation || (data.contains("_storage") && generation!=data.at("_storage").at("generation").get<uint64_t>()))
            throw std::invalid_argument("Saved status belongs to a different outer commit generation");
        if(c.contains("simulation") && c.at("simulation").contains("status_instance_ids")) {
            MonotonicIds global,local;
            global.restore(c.at("simulation").at("status_instance_ids"));local.restore(bundle.at("instance_ids"));
            if(global.nextValue() && (!local.nextValue() || global.nextValue()<local.nextValue()))
                throw std::invalid_argument("Global status watermark is behind a saved actor bundle");
        }
        w.validateStatusCheckpoint(bundle,oldTarget,generation,uint64_t(restoredNow));
        for(const auto &contact:bundle.at("contacts")) for(const auto &outcome:contact.at("outcomes"))
            if(outcome.at("procced").get<bool>()) {
                auto identity=contact.at("identity");identity["target"]=owner;
                const Json application={{"contact",identity},{"status_ordinal",outcome.at("status").at("ordinal")}};
                const auto id=outcome.at("instance_id").get<uint64_t>();
                const auto [entry,inserted]=statusApplications.emplace(id,application);
                if(!inserted && entry->second!=application)
                    throw std::invalid_argument("Saved actors reuse a status instance ID for different applications");
            }
    };
    if(c.contains("simulation") && c.at("simulation").contains("player_status")) {
        if(c.at("simulation").at("status_restore_policy")!="explicit-target-remap-stun-v1")
            throw std::invalid_argument("Unknown status restoration policy");
        validateStatus(c.at("simulation").at("player_status"),EntityHandle::fromJson(c.at("simulation").at("status_owner")),"player");
    }
    if(c.contains("region_session") && c.at("region_session").is_object()) {
        const auto &region=c.at("region_session");
        const auto actorStatus=[&](const Json &actor,const std::string &owner) {
            if(actor.is_object()&&actor.contains("monster_event_ai_state")) {
                const auto decoded=loadActor(actor,restoredNow);const auto &bundle=actor.at("monster_event_ai_state");
                if(region.contains("player") && region.at("player").contains("entity_handle") &&
                   bundle.at("player_owner")!=region.at("player").at("entity_handle"))
                    throw std::invalid_argument("Saved monster Event.ai attacker role differs from explicit region player");
                const auto generation=bundle.at("commit_generation").get<uint64_t>();
                if(!generation||(data.contains("_storage")&&generation!=data.at("_storage").at("generation").get<uint64_t>()))
                    throw std::invalid_argument("Saved monster Event.ai belongs to a different outer commit generation");
                w.validateMonsterEventActorCheckpoint(decoded,bundle,uint64_t(restoredNow),generation);
            }
            if(actor.is_object()&&actor.contains("source_action_cooldowns")) {
                const auto decoded=loadActor(actor,restoredNow);
                const auto &bundle=actor.at("source_action_cooldowns");
                w.prepareSourceMonsterCooldownRestore(decoded,bundle,restoredNow);
                const auto generation=bundle.at("commit_generation").get<uint64_t>();
                if(!generation||(data.contains("_storage")&&generation!=data.at("_storage").at("generation").get<uint64_t>()))
                    throw std::invalid_argument("Saved monster cooldown belongs to a different outer commit generation");
            }
            if(actor.is_object() && actor.contains("status_state")) {
                const auto decoded=loadActor(actor,restoredNow);
                if(decoded.dead || decoded.life!=ActorLife::Alive || decoded.hp==0)
                    throw std::invalid_argument("Dead or removed actor cannot own a saved live status bundle");
                validateStatus(actor.at("status_state"),EntityHandle::fromJson(actor.at("entity_handle")),owner);
            }
        };
        if(region.contains("player")) actorStatus(region.at("player"),"player");
        if(region.contains("room_states") && region.at("room_states").is_array())
            for(size_t room=0;room<region.at("room_states").size();++room) {
                const auto &actors=region.at("room_states")[room];
                if(actors.is_array()) for(size_t actor=0;actor<actors.size();++actor)
                    actorStatus(actors[actor],"room/"+std::to_string(room)+"/actor/"+std::to_string(actor));
            }
    }
    CharacterSkillState skills(identity);
    if(c.contains("skill_state")&&c["skill_state"].is_object())skills.restore(c.at("skill_state"),restoredNow);
    SkillLearningTestOverlay testOverlay;
    const int normalLevel=sourceLearning?normalCharacterLevel(c):legacyClampedInteger(c,"level",1,1,99);
    if(sourceLearning&&(identity.growtype||identity.awakening)) {
        const auto *option=w.advancementCatalog().find(identity);
        if(!option||normalLevel<option->requiredLevel)
            throw std::invalid_argument("Saved identity is below its source advancement level or has no source reward");
    }
    if (sourceLearning) {
        bool newCharacter=false;
        if (c.contains("skill_initialization")) {
            if (!c.at("skill_initialization").is_string() || c.at("skill_initialization")!="source-v1")
                throw std::invalid_argument("Unknown saved source skill initialization policy");
            newCharacter=true;
        }
        // Experimental choices are a separate source configuration. Neither
        // the previous live controller's compatibility arrays nor this saved
        // configuration can manufacture normal learned levels or purchases.
        if (!authoritativeLearning && !newCharacter && !experimentalTarget) migrateLegacyLearning(c,w,skills,restoredNow);
        const auto prepared=w.skillLearning().prepareInitialization(skills,normalLevel,
            newCharacter?SkillInitializationMode::NewCharacter:SkillInitializationMode::LegacyImport,restoredNow);
        if (!prepared.ok) throw std::invalid_argument("Saved learning preflight: " + prepared.quote.error);
        skills=prepared.state;
        if (c.contains("skill_test_overlay")) testOverlay.restore(c.at("skill_test_overlay"));
        // A normal purchase can make a dormant test overlay's binding stale.
        // Preserve that explicit conflict for the test UI instead of blocking
        // normal reload or silently deleting overrides. Structural/identity
        // failures still reject before cancelling live play.
        for (const auto &[key,level]:testOverlay.levels)
            if (key.jobId!=identity.jobId || key.skillId<0 || level<0)
                throw std::invalid_argument("Saved test learning override identity/level mismatch");
    }
    if(equipmentPreflight)equipmentPreflight(skills,normalLevel,restoredNow);
    // All learned binding, source and overlay preparation is private BEFORE
    // selectCharacter. Reuse that same runtime/plan, no second source load.
    std::unique_ptr<PreparedSkillRuntime> preparedLearningRuntime;
    if(sourceLearning) {
        SkillRuntimeProjectionContext context;
        context.normalLevel=context.effectiveLevel=normalLevel;
        context.nowMs=restoredNow;context.restoring=true;
        context.runtime=preparedExperimentalRuntime.get();
        context.appearance=appearance;
        context.normalPreferences=context.runtime?&context.runtime->configuration():nullptr;
        context.testPreferences=testPreferences?&*testPreferences:nullptr;
        context.previewPreferences=manualPreview?&*manualPreview:nullptr;
        context.previewEnabled=executionMode=="manual_preview";
        preparedLearningRuntime=w.prepareSkillRuntime(skills,testOverlay,context);
    }
    w.selectCharacter(identity,std::move(preparedExperimentalRuntime));
    if (c.contains("simulation")) w.restoreSimulationCheckpoint(c.at("simulation"));
    if(experimentalTarget)
        w.experimentalRuntime()->publishCooldownRestore(std::move(experimentalCooldowns));
    if (!sourceLearning && c.contains("skill_state") && c["skill_state"].is_object())
        w.skillState()=std::move(skills);
    w.characterLevel = normalLevel;
    w.weapon = legacyClampedInteger(c, "weapon", 0, 0, 3);
    if (sourceLearning) {
        w.publishPreparedSkillRuntime(*preparedLearningRuntime);
    } else for (auto &s : w.skills) {
        s.level = 1;
        auto id = std::to_string(s.id);
        if (c.contains("skills") && c["skills"].is_object() && c["skills"].contains(id) && c["skills"][id].is_number_integer())
            // An explicit zero is an unlearned active skill. Preserve it so
            // save/reload cannot grant a skill that activate() must reject.
            // Missing legacy entries keep the existing demo default above.
            s.level = std::clamp(c["skills"][id].get<int>(), 0, std::max(1, s.maxLevel));
        w.skillState().setLearnedLevel(s.identity(), s.level);
    }
    if(experimentalTarget)w.bindings.fill(-1);else w.resetBindings();
    if (!sourceLearning) for (auto &s : w.passives) {
        s.level = 1;
        if (c.contains("passives") && c["passives"].is_object() && c["passives"].contains(s.key) && c["passives"][s.key].is_number_integer())
            s.level = std::clamp(c["passives"][s.key].get<int>(), 0, std::max(1, s.maxLevel));
        w.skillState().setLearnedLevel(s.identity(), s.level);
    }
    if (!sourceLearning && !experimentalTarget && c.contains("passives") && c["passives"].is_object() &&
        c["passives"].contains("bloodyvigorous") && c["passives"]["bloodyvigorous"].is_number_integer())
        w.bloodVigorousLevel = std::clamp(c["passives"]["bloodyvigorous"].get<int>(), 0, 1);
    if (!experimentalTarget && c.contains("bindings") && c["bindings"].is_array() && c["bindings"].size() == w.bindings.size()) {
        std::array<int, 13> candidate{};
        bool ok = true;
        std::set<int> used;
        for (size_t i = 0; i < candidate.size(); i++) {
            const auto &v = c["bindings"][i];
            if (!v.is_number_integer()) { ok = false; break; }
            candidate[i] = -1;
            if (v == -1) continue; // Explicit unbound hotbar slot.
            for (int n = 0; n < int(w.skills.size()); n++)
                if (w.skills[n].id == v.get<int>()) candidate[i] = n;
            if (candidate[i] < 0 || !used.insert(candidate[i]).second) ok = false;
        }
        if (ok) w.bindings = candidate;
    }
}
void CharacterStore::capture(int slot, const World &w) {
    requireWriter();
    if (hasPendingCommit()) throw std::runtime_error("Retry the pending save before capturing further gameplay changes");
    auto &c = data.at("characters").at(slot);
    if (c.is_null()) return;
    if (!c.contains("identity") || !c["identity"].is_object()) c["identity"] = Json::object();
    const auto identity = w.identity().json();
    for (auto field = identity.begin(); field != identity.end(); ++field) c["identity"][field.key()] = field.value();
    c["class"] = characterClasses.at(size_t(w.identity().jobId));
    c["simulation"] = w.simulationCheckpoint();
    c["level"] = w.normalCharacterLevel();
    c["weapon"] = w.weapon;
    if(const auto *experimental=w.experimentalRuntime()) {
        c["experimental_skill_configuration"]=w.normalSkillConfigurationSnapshot();
        c["experimental_test_skill_configuration"]=w.testSkillConfigurationSnapshot();
        c["experimental_manual_preview_configuration"]=w.manualSkillPreviewSnapshot();
        c["experimental_skill_execution_mode"]=w.experimentalSkillPreviewEnabled()?"manual_preview":"learned";
        c["experimental_cooldowns"]=experimental->cooldownSnapshot(w.nowMs());
    } else {
        c.erase("experimental_skill_configuration");c.erase("experimental_cooldowns");
        c.erase("experimental_manual_preview_configuration");c.erase("experimental_skill_execution_mode");
        c.erase("experimental_test_skill_configuration");
    }
    if (!c.contains("skills") || !c["skills"].is_object()) c["skills"] = Json::object();
    const bool sourceLearning=w.usesSourceGrowth() && w.hasLearningLedger();
    for (const auto &s : w.skills) c["skills"][std::to_string(s.id)] =
        sourceLearning?w.skillState().learnedLevel(s.identity()):s.level;
    c["skill_state"] = w.skillState().snapshot(w.nowMs());
    if (sourceLearning) c["skill_test_overlay"]=w.skillTestOverlay().snapshot();
    c["bindings"] = Json::array();
    for (int i : w.bindings) c["bindings"].push_back(i >= 0 && i < int(w.skills.size()) ? w.skills.at(i).id : -1);
    if (!c.contains("passives") || !c["passives"].is_object()) c["passives"] = Json::object();
    for (const auto &s : w.passives) c["passives"][s.key] =
        sourceLearning?w.skillState().learnedLevel(s.identity()):s.level;
    if (!sourceLearning && (w.bloodVigorousLevel > 0 || c["passives"].contains("bloodyvigorous")))
        c["passives"]["bloodyvigorous"] = w.bloodVigorousLevel;
}
void CharacterStore::apply(int slot, World &w, Progression &progression) const {
    const auto &c = data.at("characters").at(slot);
    const auto identity = savedIdentity(c);
    const auto &character = w.characterCatalog().at(identity.jobId);
    if (!w.supportsCharacter(identity)) throw std::runtime_error("Saved character controller is unavailable");
    auto saved = c.value("progression", Json());
    validateProgressionRestore(saved);
    const bool initializeExperimental=identity.jobId!=0 && (saved.is_null() || !saved.contains("inventory"));
    if(identity.jobId!=0) {
        // Progression's legacy initializer grants a Swordman weapon. Supply
        // explicit empty containers only where a non-Sword save has no source
        // inventory/equipment; authored saved entries are never discarded.
        if(saved.is_null())saved=Json::object();
        if(!saved.contains("inventory"))saved["inventory"]=Json::array();
        if(!saved.contains("equipped"))saved["equipped"]=Json::object();
        if(!saved.contains("next_uid"))saved["next_uid"]=1;
        if(initializeExperimental && saved.contains("experimental_starter"))
            throw std::invalid_argument("Initialized experimental save is missing its inventory; refusing to repeat the starter grant");
    }
    Progression candidate(progression);
    candidate.load(saved, legacyClampedInteger(c, "level", 1, 1, 99),
                   legacyClampedInteger(c, "weapon", 0, 0, 3));
    if(initializeExperimental)initializeExperimentalWeapon(candidate,w.characterCatalog(),identity);
    validatePreparedEquipment(candidate, character);
    std::optional<CharacterBaseAttributes> attributes;
    std::optional<CharacterSpeeds> speeds;
    std::optional<EquipmentResourceAttributes> resources;
    std::optional<CombatAttributeSnapshot> combatAttributes;
    CharacterAppearance appearance;
    const auto equipmentPreflight=[&](const CharacterSkillState &normalSkills,int normalLevel,int64_t restoredNow) {
        if(normalLevel!=candidate.level())throw std::invalid_argument("Saved normal learning/equipment levels disagree");
        const EquipmentSkillContext authority{w.usesSourceGrowth()?&w.skillLearning():nullptr,&normalSkills,restoredNow};
        w.validateEquipmentSkills(candidate,identity,&authority);
        if (w.usesSourceGrowth()) attributes = w.prepareBaseAttributes(identity, candidate.level());
        if (attributes) speeds = w.prepareCharacterSpeeds(*attributes,candidate,&authority);
        if (attributes) resources = w.prepareEquipmentResources(*attributes,candidate,&authority);
        if (attributes) combatAttributes = w.prepareCombatAttributes(*attributes,candidate,&authority);
        appearance = w.prepareEquipmentAppearance(candidate,identity,&authority);
    };
    const auto level = candidate.level(), weapon = candidate.equippedWeapon();
    const auto attack = candidate.attackBonus(), defense = candidate.defenseBonus();
    // All malformed-save and equipment/source work completes privately before
    // apply() may cancel the active controller. Publishing uses prepared values
    // and does not repeat resource reads. Allocation/controller failures are not
    // advertised as rollback-safe.
    applyPreparedAppearance(slot,w,&appearance,equipmentPreflight);
    if (resources) w.applyEquipmentResources(std::move(*resources), AttributeRebuildReason::CharacterRestore);
    w.setCharacterAppearance(std::move(appearance));
    w.characterLevel = level;
    w.weapon = weapon;
    w.equipmentAttack = attack;
    w.equipmentDefense = defense;
    if (speeds) w.applyCharacterSpeeds(std::move(*speeds));
    if (combatAttributes) w.applyCombatAttributes(std::move(*combatAttributes));
    progression.commitPrepared(std::move(candidate));
}
void CharacterStore::capture(int slot, const World &w, const Progression &progression) {
    capture(slot, w);
    auto &c = data.at("characters").at(slot);
    if (c.is_null()) return;
    c["progression"] = progression.state;
    c["level"] = progression.level();
}
} // namespace dnf
