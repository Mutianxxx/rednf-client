#include "dnf/character_advancement.hpp"
#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/female_gunner_world.hpp"
#include <climits>
#include <type_traits>

namespace dnf {
struct PreparedCharacterAdvancement::Data {
    World *owner=nullptr;
    CharacterIdentity before,target;
    int64_t nowMs=0;
    uint64_t attributeRevision=0;
    Json originalSkills, originalSimulation, originalProgression;
    CharacterSkillState skills;
    std::vector<Skill> active,passive;
    std::unique_ptr<CharacterController> controller;
    std::unique_ptr<ExperimentalCharacterRuntime> runtime;
    std::unique_ptr<ExperimentalWorldAdapter> adapter;
    std::unique_ptr<PreparedSkillRuntime> learningRuntime;
    std::optional<CharacterBaseAttributes> attributes;
    std::optional<CharacterSpeeds> speeds;
    std::optional<EquipmentResourceAttributes> resources;
    std::optional<CombatAttributeSnapshot> combat;
    std::optional<CharacterAppearance> appearance;
    int hp=0,mp=0;
    Json change, trace;
};
PreparedCharacterAdvancement::PreparedCharacterAdvancement(std::unique_ptr<Data> data):data_(std::move(data)){}
PreparedCharacterAdvancement::~PreparedCharacterAdvancement()=default;
PreparedCharacterAdvancement::PreparedCharacterAdvancement(PreparedCharacterAdvancement &&) noexcept=default;
PreparedCharacterAdvancement &PreparedCharacterAdvancement::operator=(PreparedCharacterAdvancement &&) noexcept=default;
Json PreparedCharacterAdvancement::writeCharacter(Json character) const {
    if(!data_)throw std::invalid_argument("Advancement candidate has already been published");
    const auto &p=*data_;
    if(!character.contains("identity")||!(CharacterIdentity::fromJson(character.at("identity"))==p.before))
        throw std::invalid_argument("Prepared character patch belongs to another starting identity");
    const auto identity=p.target.json();
    for(auto it=identity.begin();it!=identity.end();++it)character["identity"][it.key()]=it.value();
    character["skill_state"]=p.skills.snapshot(p.nowMs);
    if(character.contains("region_session")&&character.at("region_session").is_object()&&
       character.at("region_session").contains("player")&&character.at("region_session").at("player").is_object()) {
        auto &actor=character["region_session"]["player"];
        actor["hp"]=p.hp;actor["mp"]=p.mp;
        actor["max_hp"]=p.attributes->integer(ChrAttribute::HpMax);
        actor["max_mp"]=p.attributes->integer(ChrAttribute::MpMax);
    }
    if(p.runtime) {
        if(character.contains("experimental_manual_preview_configuration")&&!character.at("experimental_manual_preview_configuration").is_null()) {
            if(!character.contains("experimental_manual_preview_archive"))character["experimental_manual_preview_archive"]=Json::array();
            if(!character.at("experimental_manual_preview_archive").is_array())throw std::invalid_argument("Invalid manual preview archive");
            character["experimental_manual_preview_archive"].push_back({{"identity",p.before.json()},
                {"configuration",character.at("experimental_manual_preview_configuration")},
                {"reason","identity change preserves prior explicit preview without admitting it as learned"}});
        }
        character["experimental_skill_configuration"]=p.runtime->configuration().snapshot();
        character["experimental_cooldowns"]=p.runtime->cooldownSnapshot(p.nowMs);
    }
    for(const auto &skill:p.active)character["skills"][std::to_string(skill.id)]=p.skills.learnedLevel(skill.identity());
    for(const auto &skill:p.passive)character["passives"][skill.key]=p.skills.learnedLevel(skill.identity());
    if(p.learningRuntime)character=p.learningRuntime->writeCharacter(std::move(character));
    return character;
}
Json PreparedCharacterAdvancement::diagnostics() const { return data_?data_->trace:Json(); }

ExperimentalCharacterRuntime ExperimentalCharacterRuntime::rebasedForIdentity(
    std::shared_ptr<const ExperimentalCharacterPlan> plan,const SkillLearningService &learning,int normalLevel) const {
    if(!plan||plan->identity.jobId!=plan_->identity.jobId||plan->pvfIdentity!=plan_->pvfIdentity)
        throw std::invalid_argument("Identity rebase must keep the same source job/PVF");
    if(activeMotion_||!sourceActions_.empty()||!sourceEntities_.empty())
        throw std::invalid_argument("Finish the active action and its source objects before changing identity");
    auto saved=configuration_.snapshot();saved["identity"]=plan->identity.json();
    Json usable=Json::array(),disabled=saved.value("advancement_disabled_bindings",Json::array());
    for(const auto &binding:saved.at("skill_bindings")) {
        const auto key=SkillKey::fromJson(binding.at("key"));
        const auto eligibility=learning.sourceUseEligibility(plan->identity,key,binding.at("level").get<int>(),normalLevel);
        if(eligibility.allowed())usable.push_back(binding);
        else disabled.push_back({{"identity",plan->identity.json()},{"binding",binding},{"error",eligibility.error}});
    }
    saved["skill_bindings"]=std::move(usable);
    if(saved.contains("female_gunner_passive_levels")) {
        auto passives=saved.at("female_gunner_passive_levels");
        for(auto it=passives.begin();it!=passives.end();) {
            const SkillKey key{plan->identity.jobId,std::stoi(it.key())};
            const auto eligibility=learning.sourceUseEligibility(plan->identity,key,it.value().get<int>(),normalLevel);
            if(eligibility.allowed())++it;
            else {disabled.push_back({{"identity",plan->identity.json()},{"passive_key",key.json()},
                {"level",it.value()},{"error",eligibility.error}});it=passives.erase(it);}
        }
        saved["female_gunner_passive_levels"]=std::move(passives);
    }
    saved["advancement_disabled_bindings"]=std::move(disabled);
    ExperimentalSkillConfiguration configuration(*plan);configuration.restore(saved,*plan);
    auto result=*this;result.plan_=std::move(plan);result.configuration_=std::move(configuration);result.releaseInputs();
    // Reuse the local sequence/cooldown watermarks. Re-entering another branch
    // cannot replay an old source object, reset its CD or rewind a local clock.
    return result;
}
const CharacterAdvancementCatalog &World::advancementCatalog() const {
    if(!advancementCatalog_)advancementCatalog_=sharedCharacterAdvancementCatalog(pvf_,characters_);
    return *advancementCatalog_;
}
std::unique_ptr<PreparedCharacterAdvancement> World::prepareCharacterAdvancement(CharacterIdentity target,const Progression &progression) {
    if(!usesSourceGrowth()||debugOverrides_.enabled||experimentalSkillPreviewEnabled_||combat||player.dead||player.hp<=0||active_>=0||
       player.animation!="stay"||player.z!=0||player.vx!=0||player.vy!=0||player.vz!=0)
        throw std::invalid_argument("GSD identity changes require an alive idle normal character in town");
    const auto *option=advancementCatalog().find(target);
    if(target.jobId!=identity_.jobId||target==identity_||!option||!supportsCharacter(target))
        throw std::invalid_argument("Target is not an admitted different identity of the current source job");
    if(normalCharacterLevel()!=progression.level()||progression.level()<option->requiredLevel)
        throw std::invalid_argument("Normal source level has not reached the target identity requirement");
    if(attributeRevision_==UINT64_MAX)throw std::overflow_error("Attribute revision exhausted");
    if(skillProjectionRevision_==UINT64_MAX)throw std::overflow_error("Skill projection revision exhausted");
    auto p=std::make_unique<PreparedCharacterAdvancement::Data>();
    p->owner=this;p->before=identity_;p->target=target;p->nowMs=nowMs();p->attributeRevision=attributeRevision_;
    p->originalSkills=skillState_.snapshot(nowMs());p->originalSimulation=simulationCheckpoint();p->originalProgression=progression.state;
    const auto budgetBefore=skillLearning().budget(skillState_,progression.level(),nowMs());
    auto ledger=p->originalSkills;
    const auto identity=target.json();for(auto it=identity.begin();it!=identity.end();++it)ledger["identity"][it.key()]=it.value();
    p->skills=CharacterSkillState(target);p->skills.restore(ledger,nowMs());
    const auto budgetAfter=skillLearning().budget(p->skills,progression.level(),nowMs());
    if(budgetBefore.json()!=budgetAfter.json())throw std::invalid_argument("Identity rebase changed the normal point ledger");
    const EquipmentSkillContext equipmentSkills{&skillLearning(),&p->skills,p->nowMs};
    validateEquipmentSkills(progression,target,&equipmentSkills);
    p->controller=controllers_.create(target,controllerServices());
    p->appearance=prepareEquipmentAppearance(progression,target,&equipmentSkills);
    if(experimentalRuntime_) {
        auto plan=std::make_shared<ExperimentalCharacterPlan>(loadExperimentalCharacterPlan(pvf_,assets_,characters_,target,&advancementCatalog()));
        p->runtime=std::make_unique<ExperimentalCharacterRuntime>(experimentalRuntime_->rebasedForIdentity(plan,skillLearning(),progression.level()));
        SkillRuntimeProjectionContext context;
        context.normalLevel=context.effectiveLevel=progression.level();context.nowMs=nowMs();
        context.runtime=p->runtime.get();context.normalPreferences=&p->runtime->configuration();context.restoring=true;
        context.appearance=&*p->appearance;
        p->learningRuntime=prepareSkillRuntime(p->skills,skillTestOverlay_,context);
        p->adapter=std::make_unique<ExperimentalWorldAdapter>(*this);
    }else {p->active=skills;p->passive=passives;}
    Json disabled=Json::array();
    const auto project=[&](std::vector<Skill> &list) {
        for(auto &skill:list) {
            skill.level=p->skills.learnedLevel(skill.identity());
            if(skill.sourceData)skill.maxLevel=skill.sourceData->purchaseMaximum(target.growtype).value_or(0);
            if(skill.level&&!skillLearning().useEligibility(p->skills,skill.identity(),progression.level()).allowed()) {
                disabled.push_back(skill.identity().json());skill.level=0;
            }
        }
    };
    project(p->active);project(p->passive);
    const auto base=prepareBaseAttributes(target,progression.level());
    p->speeds=prepareCharacterSpeeds(base,progression,&equipmentSkills);p->resources=prepareEquipmentResources(base,progression,&equipmentSkills);
    p->attributes=p->resources->adjusted;p->combat=prepareCombatAttributes(base,progression,&equipmentSkills);
    p->hp=std::clamp(player.hp,0,p->attributes->integer(ChrAttribute::HpMax));
    p->mp=std::clamp(player.mp,0,p->attributes->integer(ChrAttribute::MpMax));
    p->change={{"reason","user_gsd_identity_change"},{"before_identity",identity_.json()},{"identity",target.json()},
        {"tick",tick},{"revision",attributeRevision_+1},{"classification","user_requested_rule"}};
    p->trace={{"source_option",option->snapshot()},{"normal_level",progression.level()},
        {"budget_before",budgetBefore.json()},{"budget_after",budgetAfter.json()},{"disabled_runtime_skills",disabled},
        {"skill_implementation_gate","independent; unsupported skill does not prevent identity commit"},
        {"normal_non_swordman_learning","prepared effective-ledger projection; only reviewed actual consumers"},
        {"old_test_overlay","preserved dormant; explicit reset/rebind required before testing"}};
    return std::unique_ptr<PreparedCharacterAdvancement>(new PreparedCharacterAdvancement(std::move(p)));
}
void World::publishCharacterAdvancement(PreparedCharacterAdvancement &prepared) {
    if(!prepared.data_)throw std::invalid_argument("Advancement candidate already consumed");
    auto &p=*prepared.data_;
    if(p.owner!=this||!(identity_==p.before)||nowMs()!=p.nowMs||attributeRevision_!=p.attributeRevision||
       debugOverrides_.enabled||combat||player.dead||active_>=0||skillState_.snapshot(nowMs())!=p.originalSkills||
       simulationCheckpoint()!=p.originalSimulation)
        throw std::invalid_argument("World changed while the durable identity generation awaited publication");
    static_assert(std::is_nothrow_move_assignable_v<CharacterSkillState>);
    static_assert(std::is_nothrow_move_assignable_v<std::optional<CharacterAppearance>>);
    static_assert(std::is_nothrow_move_assignable_v<std::optional<CharacterBaseAttributes>>);
    static_assert(std::is_nothrow_move_assignable_v<std::optional<CharacterSpeeds>>);
    static_assert(std::is_nothrow_move_assignable_v<std::optional<EquipmentResourceAttributes>>);
    static_assert(std::is_nothrow_move_assignable_v<std::optional<CombatAttributeSnapshot>>);
    // All fallible source work is complete. These moves/clears keep the world
    // clock, actor handles, RNG, reward/event ledgers and inventory untouched.
    releaseInputs();cancelSquirrelActions("identity_change");
    if(femaleGunnerWorld_)femaleGunnerWorld_->clear("identity_change");
    identity_=p.target;controller_=std::move(p.controller);skillState_=std::move(p.skills);
    experimentalRuntime_=std::move(p.runtime);experimentalAdapter_=std::move(p.adapter);
    skills=std::move(p.active);passives=std::move(p.passive);
    if(p.learningRuntime)publishPreparedSkillRuntime(*p.learningRuntime);else ++skillProjectionRevision_;
    baseAttributes_=std::move(p.attributes);speedAttributes_=std::move(p.speeds);
    equipmentResources_=std::move(p.resources);combatAttributes_=std::move(p.combat);equippedAppearance_=std::move(p.appearance);
    player.maxHp=baseAttributes_->integer(ChrAttribute::HpMax);player.maxMp=baseAttributes_->integer(ChrAttribute::MpMax);
    player.hp=p.hp;player.mp=p.mp;++attributeRevision_;lastAttributeChange_=std::move(p.change);
    diagnosticAppearances_.clear();skillCostCache_.clear();
    prepared.data_.reset();
}
} // namespace dnf
