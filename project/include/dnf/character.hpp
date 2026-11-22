#pragma once
#include "resources.hpp"
#include <map>
#include <tuple>
namespace dnf {
// jobId is the character.lst registration ID. Growtype/awakening remain
// explicit source identities; a name alone never authorizes a native branch.
struct CharacterIdentity {
    int jobId = 0, growtype = 0, awakening = 0;
    bool operator==(const CharacterIdentity &other) const {
        return std::tie(jobId, growtype, awakening) == std::tie(other.jobId, other.growtype, other.awakening);
    }
    bool operator<(const CharacterIdentity &other) const {
        return std::tie(jobId, growtype, awakening) < std::tie(other.jobId, other.growtype, other.awakening);
    }
    Json json() const;
    static CharacterIdentity fromJson(const Json &value);
};
// Skill IDs are local to a job's registered skill list, not global IDs.
struct SkillKey {
    int jobId = 0, skillId = -1;
    bool operator==(const SkillKey &other) const {
        return jobId == other.jobId && skillId == other.skillId;
    }
    bool operator<(const SkillKey &other) const {
        return std::tie(jobId, skillId) < std::tie(other.jobId, other.skillId);
    }
    Json json() const;
    static SkillKey fromJson(const Json &value);
};
// Lossless source storage is separate from executable combat controllers.
// Source identifiers/ordinals are not runtime skill or state implementations.
struct CharacterScript {
    Script script;
    Bytes bytes;
    Json provenance = Json::object();
};
struct CharacterRegistration {
    int id = -1;
    size_t ordinal = 0, offset = 0, pathOffset = 0;
    std::string literal, path;
    bool exists = false;
};
struct CharacterList {
    CharacterScript source;
    std::vector<CharacterRegistration> entries;
    Json issues = Json::array();
    const CharacterRegistration *unique(int id) const;
};
struct CharacterResource {
    std::string tag, literal, path;
    size_t fieldOffset = 0, valueIndex = 0;
    bool exists = false;
};
struct ScopedSkillField {
    Field field;
    std::string scope = "common";
    size_t ordinal = 0;
};
enum class SkillSourceKind { Unknown, Active, Passive };
struct CharacterSkillDefinition {
    SkillKey key;
    CharacterRegistration registration;
    CharacterScript source;
    std::vector<ScopedSkillField> fields;
    SkillSourceKind kind = SkillSourceKind::Unknown;
    // [type] distinguishes active/passive, not player/internal/system roles.
    // [skill class], path names and fitness do not establish that boundary.
    std::string runtimeRole = "unresolved";
    Json issues = Json::array();
    std::vector<const ScopedSkillField *> fieldsInScope(const std::string &tag,
                                                       const std::string &scope = "common") const;
    // Exact scope, no implicit dungeon/common overlay; repeated fields throw.
    Json values(const std::string &tag, const std::string &scope = "common") const;
    Json snapshot(bool includeSource = false) const;
};
// An explicit SKL learning candidate is not a command/use-skill transaction.
// Native state, awakening, cooldown, resources and branch gates remain separate.
enum class SourceLearningState { Unresolved, ExplicitlyExcluded, ExplicitLearningCandidate };
struct SkillLearningEvidence {
    SourceLearningState state = SourceLearningState::Unresolved;
    int purchaseCeiling = -1;
    bool hasFitness = false, fitnessIncludesGrowtype = false;
    bool grantsRuntimeUse = false;
    Json evidence = Json::array();
    Json snapshot() const;
};
CharacterSkillDefinition parseCharacterSkillSource(SkillKey key,
    CharacterRegistration registration, CharacterScript source);
struct DefaultEquipmentSource {
    size_t fieldOffset = 0, valueIndex = 0;
    int equipmentId = -1;
    std::string path;
    bool registered = false, exists = false, hasAnimationJob = false;
    CharacterScript source;
};
struct DefaultAppearanceSources {
    int jobId = 0;
    std::string job;
    Json bodyImageTemplates = Json::array();
    CharacterScript settings;
    // Retains -1 and unresolved numeric entries, never assigns slot semantics
    // from array position. Actual EQU type and animation-job scope are authority.
    std::vector<DefaultEquipmentSource> equipment;
    Json issues = Json::array();
    Json snapshot(bool includeSource = false) const;
};
// These are source spans, not evaluated stat inheritance or skill eligibility.
// Keep each growth/awakening's repeated fields and empty blocks independent.
struct CharacterStatBlock {
    std::string tag;
    int growtype = 0, awakening = 0;
    size_t offset = 0, endOffset = 0;
    std::vector<Field> fields;
    Json values(const std::string &tag) const;
};
struct CharacterDefinition {
    CharacterRegistration registration;
    CharacterScript source;
    CharacterScript settings;
    CharacterList skills;
    std::string job;
    Json growtypeNames = Json::array(), bodyImageTemplates = Json::array(), issues = Json::array();
    std::vector<CharacterResource> resources;
    std::vector<CharacterStatBlock> stats;
    bool runtimeDeferredByUser = false;
    // Native default branches only. Advancement/skill overrides require their
    // own controller. Missing/last entries do not imply end-of-ANI eligibility.
    std::vector<int> basicAttackCancelFrames;
    std::string basicAttackCancelEvidence;
    std::vector<const CharacterResource *> motions(const std::string &tag) const;
    // slot is the original value index; occurrence selects repeated fields.
    // Empty slots are returned by resource(), and rejected by path accessors.
    const CharacterResource *resource(const std::string &tag, size_t slot = 0, size_t occurrence = 0) const;
    std::string motion(const std::string &tag, size_t slot = 0, size_t occurrence = 0) const;
    std::string attackInfo(const std::string &tag, size_t slot = 0, size_t occurrence = 0) const;
    // Source-only, explicit compatibility lookup for the existing controller.
    // Ambiguous stems or absent bindings fail; never manufacture a job folder.
    std::string motionByStem(const std::string &stem) const;
};
CharacterList loadCharacterList(Pvf &pvf, const std::string &path, const std::string &base);
class CharacterCatalog {
    Pvf &pvf_;
    mutable std::map<SkillKey, CharacterSkillDefinition> skillDefinitions_;
    mutable CharacterList equipmentRegistry_;
  public:
    CharacterList characters, skillLists;
    CharacterScript defaultSettings;
    // Keep all native parameter scripts. Associating a file with an EXE
    // controller requires its loader evidence, not a similar filename.
    std::vector<CharacterScript> nativeSkillData;
    std::vector<CharacterDefinition> definitions;
    Json issues = Json::array();
    explicit CharacterCatalog(Pvf &pvf);
    // Borrowed immutable source owner; cache factories must not combine this
    // interpreted view with a different Pvf, even when package hashes match.
    const Pvf &sourcePvf() const noexcept { return pvf_; }
    const CharacterDefinition &at(int id) const;
    CharacterScript skill(int characterId, int skillId) const;
    CharacterScript equipment(int equipmentId) const;
    const CharacterSkillDefinition &skillDefinition(SkillKey key) const;
    SkillLearningEvidence skillEligibility(CharacterIdentity identity, SkillKey key,
                                           const std::string &scope = "common") const;
    // Source facts only. Does not claim a named growtype is a playable branch.
    Json identityEvidence(CharacterIdentity identity) const;
    DefaultAppearanceSources defaultAppearanceSources(int jobId) const;
    // Explicit, potentially large enumeration. No source-exists => implemented.
    Json skillSourceSnapshot(bool includeSource = false) const;
    Json snapshot(bool includeSource = false) const;
};
} // namespace dnf
