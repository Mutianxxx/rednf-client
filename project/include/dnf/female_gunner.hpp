#pragma once
#include "skill_data.hpp"
#include "content_profile.hpp"
#include "damage_resolution.hpp"

namespace dnf {
// 1031 source operands plus explicitly inferred controller dispatch. These are
// portable values; no addresses, object offsets or Squirrel code are executed.
enum class FemaleGunnerCommandKind { Launch, Strike, Spawn, Buff, Clear, Stage };
const char *femaleGunnerCommandKindName(FemaleGunnerCommandKind);
struct FemaleGunnerStage {
    std::string motionTag = "[etc motion]", attackTag = "[etc attack info]";
    size_t motionSlot = 0, attackSlot = 0;
    bool hasAttack = false;
    bool emitCommand = false;
    bool holdForCommandLifetime = false;
    // Explicit inferred repetition; source delay is always read from the ANI.
    int repeat = 1;
    Json evidence = Json::array();
};
struct FemaleGunnerObjectBinding {
    SourceRef source;
    std::vector<std::pair<std::string,SourceRef>> animations, attacks, particles;
};
struct FemaleGunnerSkillDescriptor {
    SkillKey key;
    SourceRef source;
    std::string stem, family;
    SkillSourceKind kind = SkillSourceKind::Unknown;
    std::vector<FemaleGunnerStage> stages;
    std::vector<SourceRef> effectSources, objectSources, attackSources;
    Json propertySchema = Json::array(), diagnostics = Json::array();
    bool dedicatedRuntime = false;
    std::vector<std::string> inferredObjectMembers;
    std::map<std::string,FemaleGunnerObjectBinding> objectBindings;
    Json snapshot() const;
};
struct FemaleGunnerSkillCommand {
    FemaleGunnerCommandKind kind = FemaleGunnerCommandKind::Stage;
    SkillKey key;
    SourceRef skillSource;
    std::optional<SourceRef> motionSource, animationSource, attackSource, objectSource;
    uint64_t actionSequence = 0, pulseId = 0;
    size_t stage = 0;
    int level = 1, direction = 1;
    std::string family, effectRole;
    // World-space origin is sampled at publication. A spawned entity retains
    // this origin unless followCaster is explicitly requested.
    double x = 0, y = 0, z = 0, offsetX = 0, offsetY = 0, offsetZ = 0;
    double speed = 0, range = 0;
    int64_t lifetimeMs = 0, intervalMs = 0;
    uint32_t count = 1;
    bool followCaster = false;
    bool preflightOnly = false;
    int64_t releaseDelayMs = 0;
    std::optional<Box> box;
    DamageSkillModifiers damage;
    // Ordered evaluated display operands and original selected table data are
    // preserved separately. Display fields are evidence, not native setters.
    Json parameters = Json::array(), rawTables = Json::object();
    Json evidence = Json::array(), diagnostics = Json::array();
    Json snapshot() const;
};
FemaleGunnerSkillDescriptor describeFemaleGunnerSkill(const SkillSourceData &, const SourceRef &);
void loadFemaleGunnerResources(Pvf &, Assets &, FemaleGunnerSkillDescriptor &);
// Resolves every value from the selected current SKL row/static data. Throws
// for malformed/truncated source tables rather than inventing a coefficient.
FemaleGunnerSkillCommand evaluateFemaleGunnerSkill(const FemaleGunnerSkillDescriptor &,
    const SkillSourceData &, int level, int weaponSubtype = -1);
Json runFemaleGunnerSourceTests(Pvf &, Assets &);
} // namespace dnf
