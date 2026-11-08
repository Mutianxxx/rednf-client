#include "dnf/experimental_character.hpp"
#include "dnf/static_motion.hpp"
#include "dnf/character_advancement.hpp"
#include "dnf/skill_learning.hpp"
#include "dnf/female_gunner_modifiers.hpp"
#include "dnf/female_gunner_entities.hpp"
#include "dnf/simulation.hpp"
#include "dnf/axis_motion.hpp"
#include "dnf/skill_input_policy.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *configurationPolicy = "inferred-source-character-experiment-v1";
const ExperimentalSourceBinding *femaleBasicJumpMotion(const ExperimentalCharacterPlan &plan,int stage) {
    // 1031 CHR retains a duplicate shoot binding at slot7. Do not renumber it.
    static constexpr size_t slots[]={5,6,8};
    return stage>=0&&stage<3?plan.motion("[etc motion]",slots[stage]):nullptr;
}
Json issue(const std::string &code, const std::string &message) {
    return {{"code",code},{"message",message},{"readiness","experimental_user_test"},{"runtime_complete",false}};
}
void appendPending(Json &pending, Json diagnostic) {
    // Repeated unassigned-key input cannot grow an unbounded transient queue.
    if(pending.size()<64)pending.push_back(std::move(diagnostic));
}
int nonnegativeInt(const Json &value, const char *name) {
    if (!value.is_number_integer() || (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(INT32_MAX)))
        throw std::invalid_argument(std::string("Invalid experimental integer: ")+name);
    const auto number=value.get<int64_t>();
    if(number<0 || number>INT32_MAX)throw std::invalid_argument(std::string("Out-of-range experimental integer: ")+name);
    return int(number);
}
const ExperimentalSourceBinding *lookup(const std::vector<ExperimentalSourceBinding> &bindings,
    const std::string &tag,size_t slot,size_t occurrence) {
    const ExperimentalSourceBinding *result=nullptr;
    for(const auto &binding:bindings) if(normalize(binding.tag)==normalize(tag) && binding.slot==slot && binding.occurrence==occurrence) {
        if(result)throw std::runtime_error("Ambiguous experimental CHR source binding");result=&binding;
    }
    return result;
}
const ExperimentalSourceBinding &checkedBinding(const ExperimentalSourceBinding &binding,const ExperimentalCharacterPlan &plan,bool attack) {
    const auto *known=attack?plan.attack(binding.tag,binding.slot,binding.occurrence):plan.motion(binding.tag,binding.slot,binding.occurrence);
    if(!known || known->json()!=binding.json())throw std::invalid_argument("Experimental binding is not an exact source binding of this job/PVF");
    if(!attack && !plan.animations.count(known->source.memberPath))throw std::invalid_argument("Experimental source animation could not be decoded");
    if(attack && (!plan.attackDefinitions.count(known->source.memberPath) || !plan.attackDefinitions.at(known->source.memberPath).usable()))
        throw std::invalid_argument("Experimental source ATK has unsupported required behavior");
    return *known;
}
ExperimentalSourceBinding decodeBinding(const Json &value,const ExperimentalCharacterPlan &plan,bool attack) {
    const auto tag=value.at("tag").get<std::string>();
    const auto slot=nonnegativeInt(value.at("slot"),"slot"), occurrence=nonnegativeInt(value.at("occurrence"),"occurrence");
    const auto *known=attack?plan.attack(tag,size_t(slot),size_t(occurrence)):plan.motion(tag,size_t(slot),size_t(occurrence));
    if(!known || known->json()!=value)throw std::invalid_argument("Saved experimental source path/hash/slot differs from selected job/PVF");
    return checkedBinding(*known,plan,attack);
}
const ExperimentalSkillRow &activeSkill(SkillKey key,const ExperimentalCharacterPlan &plan) {
    const auto found=plan.skills.find(key);
    if(key.jobId!=plan.identity.jobId || found==plan.skills.end())throw std::invalid_argument("Experimental skill does not belong to this job");
    if(found->second.kind!=SkillSourceKind::Active)throw std::invalid_argument("Passive/unknown source skill has no experimental active consumer");
    return found->second;
}
int32_t animationSpeedStat(double value) {
    // 1031 adaptation policy, not a recovered 1031 protected-stat layout.
    // Keep the positive integer Sani input and the two native rate paths
    // separate from the existing floating-point legacy local-age strategy.
    if(!std::isfinite(value)||value<1||value>INT32_MAX)
        throw std::invalid_argument("Experimental deadline clock requires a positive int32 effective attack stat");
    return int32_t(std::trunc(value));
}
class SourceExperimentalController final : public CharacterController {
    CharacterIdentity identity_;
    CharacterControllerServices services_;
    int64_t lastMs_=-1;
  public:
    SourceExperimentalController(CharacterIdentity identity,CharacterControllerServices services)
        :identity_(identity),services_(std::move(services)) {
        if(!services_.request||!services_.tick||!services_.cancel)throw std::invalid_argument("Experimental controller needs actual World callbacks");
    }
    CharacterIdentity identity() const override{return identity_;}
    bool request(const CharacterActionRequest &request) override {
        if(request.simulationMs<0 || (request.skill && request.skill->jobId!=identity_.jobId))return false;
        return services_.request(request);
    }
    void tick(int64_t ms) override {
        if(ms<0||ms<lastMs_)throw std::invalid_argument("Experimental controller clock moved backwards");
        if(ms==lastMs_)return;services_.tick(ms);lastMs_=ms;
    }
    void cancel(ControllerCancelReason reason) override{services_.cancel(reason);lastMs_=-1;}
};
}
Json ExperimentalSourceBinding::json() const {
    return {{"tag",tag},{"slot",slot},{"occurrence",occurrence},{"source",source.json()}};
}
Json ExperimentalSkillRow::json() const {
    return {{"key",key.json()},{"kind",kind==SkillSourceKind::Active?"active":kind==SkillSourceKind::Passive?"passive":"unknown"},
        {"name",name},{"source",source.json()},{"native_controller_restored",false},{"diagnostics",diagnostics},
        {"purchase_maximum",data?Json(data->purchaseMaximum(0).value_or(0)):Json(0)}};
}
const ExperimentalSourceBinding *ExperimentalCharacterPlan::motion(const std::string &tag,size_t slot,size_t occurrence) const {
    return lookup(motions,tag,slot,occurrence);
}
const ExperimentalSourceBinding *ExperimentalCharacterPlan::attack(const std::string &tag,size_t slot,size_t occurrence) const {
    return lookup(attacks,tag,slot,occurrence);
}
Json ExperimentalCharacterPlan::snapshot() const {
    Json motionRows=Json::array(),attackRows=Json::array(),skillRows=Json::array(),sourceActions=Json::array();
    for(const auto &m:motions)motionRows.push_back(m.json());for(const auto &a:attacks)attackRows.push_back(a.json());
    for(const auto &skill:skills)skillRows.push_back(skill.second.json());
    for(const auto &action:sourceSkillActions)sourceActions.push_back(action.second.snapshot());
    return {{"identity",identity.json()},{"pvf_identity",pvfIdentity},{"job",job},{"readiness","experimental_user_test"},
        {"runtime_complete",false},{"native_confirmed",false},{"character_source",characterSource.json()},
        {"motions",motionRows},{"attacks",attackRows},{"skills",skillRows},{"source_skill_actions",sourceActions},{"diagnostics",diagnostics}};
}
ExperimentalCharacterPlan loadExperimentalCharacterPlan(Pvf &pvf,Assets &assets,const CharacterCatalog &catalog,CharacterIdentity identity,
    const CharacterAdvancementCatalog *explicitAdvancementAdmission) {
    const auto &definition=catalog.at(identity.jobId);
    if(definition.runtimeDeferredByUser || ((identity.growtype||identity.awakening) &&
        (!explicitAdvancementAdmission||!explicitAdvancementAdmission->supports(identity))))
        throw std::invalid_argument("Nonbase experimental identity requires explicit source advancement admission");
    ExperimentalCharacterPlan out;out.identity=identity;out.pvfIdentity=pvf.identity();out.job=definition.job;
    out.characterSource=makeSourceRef(pvf,definition.source.script.path);
    out.characterDefinition=definition;
    if(out.pvfIdentity.empty())throw std::invalid_argument("Experimental plan requires fingerprinted PVF identity");
    for(const auto &ordered:orderedCharacterBindings(definition)) {
        const auto &resource=ordered.resource;const auto tag=normalize(resource.tag);
        const bool attack=tag=="[attack info]"||tag=="[etc attack info]"||tag=="[jumpattack info]"||tag=="[dashattack info]";
        const bool motion=(tag.size()>=8 && tag.substr(tag.size()-8)==" motion]")||tag.rfind("[throw motion ",0)==0;
        if(!attack&&!motion)continue;
        if(resource.path.empty()||!resource.exists||!pvf.has(resource.path)) {
            out.diagnostics.push_back(issue("missing_chr_binding",resource.tag+" slot "+std::to_string(resource.valueIndex)));continue;
        }
        ExperimentalSourceBinding binding{resource.tag,resource.valueIndex,ordered.occurrence,makeSourceRef(pvf,resource.path)};
        if(attack) {
            out.attacks.push_back(binding);
            auto parsed=readAttackDamage(pvf.script(resource.path),AttackStatusConsumer::StunHostV1);
            if(!parsed.usable())out.diagnostics.push_back({{"code","unsupported_atk_mechanism"},{"binding",binding.json()},{"details",parsed.diagnostics}});
            out.attackDefinitions.emplace(resource.path,std::move(parsed));
        } else {
            out.motions.push_back(binding);
            try {
                auto animation=assets.animation(resource.path);
                if(animation->frames.empty()||animation->duration<=0)throw std::runtime_error("Empty/nonpositive source animation");
                out.animations.emplace(resource.path,std::move(animation));
            } catch(const std::exception &error) {out.diagnostics.push_back(issue("unsupported_animation",resource.path+": "+error.what()));}
        }
    }
    for(const auto &registration:definition.skills.entries) {
        const SkillKey key{identity.jobId,registration.id};
        if(out.skills.count(key)) {out.skills.at(key).kind=SkillSourceKind::Unknown;out.skills.at(key).diagnostics.push_back(issue("ambiguous_skill_registration",registration.path));continue;}
        ExperimentalSkillRow row;row.key=key;row.name=registration.literal;
        try {
            const auto &skill=catalog.skillDefinition(key);row.kind=skill.kind;row.source=makeSourceRef(pvf,skill.source.script.path);
            row.data=std::make_shared<SkillSourceData>(readSkillSourceData(skill,"dungeon"));row.name=row.data->name();
            row.diagnostics.push_back(issue(row.kind==SkillSourceKind::Active?"manual_source_binding_required":"no_passive_or_internal_consumer",
                "Source registration is preserved; native skill state, passive, projectile and special mechanisms remain incomplete"));
        } catch(const std::exception &error) {row.kind=SkillSourceKind::Unknown;row.diagnostics.push_back(issue("skill_source_unavailable",error.what()));}
        out.skills.emplace(key,std::move(row));
    }
    if(identity.jobId==5)for(auto &entry:out.skills)if(entry.second.data) {
        try {
            auto descriptor=describeFemaleGunnerSkill(*entry.second.data,entry.second.source);
            if(descriptor.kind==SkillSourceKind::Active) {
                loadFemaleGunnerResources(pvf,assets,descriptor);
                for(const auto &stage:descriptor.stages) {
                    const auto *motion=out.motion(stage.motionTag,stage.motionSlot);
                    const auto *attack=stage.hasAttack?out.attack(stage.attackTag,stage.attackSlot):nullptr;
                    if(!motion||!out.animations.count(motion->source.memberPath)||(stage.hasAttack&&!attack)) {
                        descriptor.dedicatedRuntime=false;
                        descriptor.diagnostics.push_back({{"code","female_gunner_chr_stage_unavailable"},
                            {"motion_tag",stage.motionTag},{"motion_slot",stage.motionSlot},
                            {"attack_tag",stage.attackTag},{"attack_slot",stage.hasAttack?Json(stage.attackSlot):Json()}});
                    }
                    if(motion&&out.animations.count(motion->source.memberPath)) {
                        const auto layers=buildFemaleGunnerSkillLayers(pvf,assets,descriptor,motion->source.memberPath);
                        if(!layers.empty())out.femaleGunnerSkillLayers[entry.first][motion->source.memberPath]=layers;
                    }
                }
            }
            entry.second.diagnostics.push_back({{"code","female_gunner_source_descriptor"},{"descriptor",descriptor.snapshot()}});
            out.femaleGunnerSkills.emplace(entry.first,std::move(descriptor));
        }catch(const std::exception &error){entry.second.diagnostics.push_back(issue("female_gunner_descriptor_blocked",error.what()));}
    }
    if(identity.jobId==2)try {out.gunnerBasicSources=readGunnerBasicSources(pvf);}
    catch(const std::exception &error){out.diagnostics.push_back(issue("gunner_default_info_blocked",error.what()));}
    out.sourceSkillActions=loadSourceSkillActions(pvf,assets,catalog,identity,out.diagnostics);
    if(identity.jobId==1)if(const auto *jump=out.motion("[jump motion]")) {
        const auto found=out.animations.find(jump->source.memberPath);
        if(found!=out.animations.end()&&found->second->frames.size()==15&&found->second->frames[6].duration==100000&&found->second->frames[12].duration==10000)
            out.nativeJump=ExperimentalCharacterPlan::NativeJumpStages{1,7,13,
                {{"classification","40jp-CNFighter-native-stage-boundaries-current1031-ANI"},
                 {"native_source","fighter_skills.cpp sub_5E5F30 presets +6864=1/+6868=7/+6872=13; char_server_info.cpp sub_58E920/state6, sub_58FC30/state6"},
                 {"animation",jump->source.json()},{"timing","source delays within phase; vz<=0 enters fall, ground contact enters landing; no long-frame truncation"}}};
    }
    for(const auto &entry:out.sourceSkillActions) {
        if(entry.second.objectAnimation)out.animations.emplace(entry.second.animation.memberPath,entry.second.objectAnimation);
        if(!entry.second.attack.memberPath.empty())out.attackDefinitions.emplace(entry.second.attack.memberPath,entry.second.attackDefinition);
        for(const auto &stage:entry.second.nativeStages)for(const auto &layer:stage.layers)
            out.animations.emplace(layer.source.memberPath,assets.animation(layer.source.memberPath));
        for(const auto &layer:entry.second.bodyLayers)
            out.animations.emplace(layer.source.memberPath,assets.animation(layer.source.memberPath));
        if(entry.second.movingImpact) {const auto &impact=*entry.second.movingImpact;
            out.animations.emplace(impact.impactAnimation.memberPath,impact.impactClip);
            out.attackDefinitions.emplace(impact.impactAttack.memberPath,impact.impactAttackDefinition);}
    }
    out.diagnostics.push_back(issue("experimental_incomplete","Generic source ANI/ATK experiment; OBJ/PTL, scripts, grabs, transforms and skill-specific coefficients require their actual consumers"));
    return out;
}
const std::array<const char *,13> &ExperimentalSkillConfiguration::slotLabels() {
    static const std::array<const char *,13> labels{{"A","S","D","F","G","H","Q","W","E","R","T","Y","Space"}};return labels;
}
ExperimentalSkillConfiguration::ExperimentalSkillConfiguration(const ExperimentalCharacterPlan &plan)
    :identity_(plan.identity),pvfIdentity_(plan.pvfIdentity) {}
void ExperimentalSkillConfiguration::configureBasicAttackTemplate(SkillKey key,int level,const ExperimentalCharacterPlan &plan) {
    if(plan.identity.jobId==5) {configureFemaleGunnerSourceSkill(key,level,plan);return;}
    if(plan.sourceSkillActions.count(key)){configureSourceSkillAction(key,level,plan);return;}
    if(plan.identity.jobId==1)throw std::invalid_argument("Fighter source action caller is unresolved; choose an explicit source ANI/ATK, never Upper/basic fallback");
    const auto *motion=plan.motion("[attack motion]"),*attack=plan.attack("[attack info]");
    if(!motion||!attack)throw std::invalid_argument("This job has no exact basic CHR motion/ATK for the temporary release template");
    configureSkill(key,*motion,*attack,level,plan);
    bindings_.at(key).unknown["user_requested_temporary_template"]={{"policy","shared-swordman-basic-release-v1"},
        {"classification","user_requested_temporary"},{"native_skill_controller_restored",false},
        {"source_job",plan.identity.jobId},{"skill_source",activeSkill(key,plan).source.json()},
        {"motion_source",motion->json()},{"attack_source",attack->json()}};
}
void ExperimentalSkillConfiguration::configureSourceSkillAction(SkillKey key,int level,const ExperimentalCharacterPlan &plan) {
    const auto found=plan.sourceSkillActions.find(key);
    if(found==plan.sourceSkillActions.end())throw std::invalid_argument("No reviewed source action consumer for this skill");
    const auto &descriptor=found->second;
    const auto *motion=plan.motion(descriptor.nativeStages.empty()?"[etc motion]":descriptor.nativeStages.front().motionTag,size_t(descriptor.motionSlot));
    if(!motion||motion->source.json()!=found->second.motion.json())throw std::invalid_argument("Source NUT action CHR binding differs");
    evaluateSourceSkillAction(found->second,*activeSkill(key,plan).data,level);
    std::optional<ExperimentalSourceBinding> attack;
    int maximum=activeSkill(key,plan).data->purchaseMaximum(plan.identity.growtype).value_or(1);
    if(descriptor.kind==SourceSkillActionKind::BodyAttack) {
        if(descriptor.nativeStages.empty()||descriptor.nativeStages.front().attackSlot>=0) {
            const auto &stage=descriptor.nativeStages;
            const auto *sourceAttack=plan.attack(stage.empty()?"[etc attack info]":stage.front().attackTag,
                size_t(stage.empty()?descriptor.attackSlot:stage.front().attackSlot));
            if(!sourceAttack||sourceAttack->source.json()!=(stage.empty()?descriptor.attack:stage.front().attack).json())throw std::invalid_argument("Source body NUT CHR attack binding differs");
            attack=*sourceAttack;
        }
        for(const auto &value:activeSkill(key,plan).data->values("[growtype maximum level]"))
            if(value.is_number_integer())maximum=std::max(maximum,value.get<int>());
    }
    if(key.jobId==1)for(const auto &tag:{"[growtype maximum level]","[second growtype maximum level]"})
        for(const auto &v:activeSkill(key,plan).data->values(tag))if(v.is_number_integer())maximum=std::max(maximum,v.get<int>());
    for(const auto &stage:descriptor.nativeStages) {
        const auto *m=plan.motion(stage.motionTag,size_t(stage.motionSlot));
        if(!m||m->source.json()!=stage.motion.json())throw std::invalid_argument("Source native stage motion binding changed");
        checkedBinding(*m,plan,false);
        if(stage.attackSlot>=0) {const auto *a=plan.attack(stage.attackTag,size_t(stage.attackSlot));
            if(!a||a->source.json()!=stage.attack.json())throw std::invalid_argument("Source native stage attack binding changed");
            if(!descriptor.nativeGrab||&stage!=&descriptor.nativeStages[descriptor.nativeGrab->tryStage])checkedBinding(*a,plan,true);
        }
    }
    if(level<1||level>std::max(1,maximum))throw std::invalid_argument("Source NUT level exceeds source branch maximum");
    // Explicit test configuration may choose a source advancement's skill;
    // regular progression/learning and character identity remain untouched.
    configureSkill(key,*motion,attack,1,plan);bindings_.at(key).level=level;
    bindings_.at(key).unknown[found->second.controllerKey()]=found->second.snapshot();
}
void ExperimentalSkillConfiguration::setSourceBodyRecoveryPolicy(const std::string &value) {
    if(value!="after_animation"&&value!="since_activation")throw std::invalid_argument("Unknown inferred body recovery policy");
    unknown_["source_body_recovery_policy"]=value;
}
std::string ExperimentalSkillConfiguration::sourceBodyRecoveryPolicy() const {
    return unknown_.value("source_body_recovery_policy",std::string("after_animation"));
}
void ExperimentalSkillConfiguration::configureSourceActionPassive(SkillKey key,int level,const ExperimentalCharacterPlan &plan) {
    if(!(identity_==plan.identity)||pvfIdentity_!=plan.pvfIdentity||!(key==SkillKey{2,168})||identity_.jobId!=2)
        throw std::invalid_argument("Unreviewed source-action passive configuration");
    const auto row=plan.skills.find(key),base=plan.skills.find({key.jobId,4});
    const auto action=plan.sourceSkillActions.find({key.jobId,4});
    if(row==plan.skills.end()||!row->second.data||base==plan.skills.end()||!base->second.data||action==plan.sourceSkillActions.end())
        throw std::invalid_argument("Source-action passive dependency unavailable");
    // Source prerequisite10 is validated again by the selected-row evaluator.
    (void)evaluateSourceSkillActionTp(action->second,*base->second.data,10,key,row->second.source,*row->second.data,level);
    auto updated=unknown_;auto rows=updated.value("source_action_passives",Json::array());
    rows.erase(std::remove_if(rows.begin(),rows.end(),[&](const Json &r){return SkillKey::fromJson(r.at("key"))==key;}),rows.end());
    if(level>0)rows.push_back({{"key",key.json()},{"source",row->second.source.json()},{"level",level}});
    if(rows.empty()){updated.erase("source_action_passives");updated.erase("source_action_passive_policy");}
    else {updated["source_action_passives"]=std::move(rows);updated["source_action_passive_policy"]="reviewed-source-action-passive-levels-v1";}
    unknown_=std::move(updated);
}
int ExperimentalSkillConfiguration::sourceActionPassiveLevel(SkillKey key) const {
    if(key.jobId!=identity_.jobId||!unknown_.contains("source_action_passives"))return 0;
    for(const auto &row:unknown_.at("source_action_passives"))if(SkillKey::fromJson(row.at("key"))==key)
        return nonnegativeInt(row.at("level"),"source_action_passive_level");
    return 0;
}
void ExperimentalSkillConfiguration::setSourceActionAudioPolicy(const std::string &policy,const ExperimentalCharacterPlan &plan) {
    if(!(identity_==plan.identity)||pvfIdentity_!=plan.pvfIdentity||
       (policy!="disabled"&&(policy!="inferred-current1031-knee-cast-audio-v1"||identity_.jobId!=2||!plan.sourceSkillActions.count({2,4}))))
        throw std::invalid_argument("Unknown/foreign source action audio policy");
    if(policy=="disabled")unknown_.erase("source_action_audio_policy");else unknown_["source_action_audio_policy"]=policy;
}
std::string ExperimentalSkillConfiguration::sourceActionAudioPolicy() const {
    return unknown_.value("source_action_audio_policy",std::string("disabled"));
}
int ExperimentalSkillConfiguration::femaleGunnerPassiveLevel(SkillKey key) const {
    if(key.jobId!=5||identity_.jobId!=5||!unknown_.contains("female_gunner_passive_levels"))return 0;
    const auto &levels=unknown_.at("female_gunner_passive_levels");const auto name=std::to_string(key.skillId);
    return levels.is_object()&&levels.contains(name)?nonnegativeInt(levels.at(name),"female_gunner_passive_level"):0;
}
std::map<SkillKey,int> ExperimentalSkillConfiguration::femaleGunnerLevels() const {
    std::map<SkillKey,int> out;if(identity_.jobId!=5)return out;
    for(const auto &entry:bindings_)out.emplace(entry.first,entry.second.level);
    if(unknown_.contains("female_gunner_passive_levels")) {
        const auto &levels=unknown_.at("female_gunner_passive_levels");
        for(auto i=levels.begin();i!=levels.end();++i)out[{5,std::stoi(i.key())}]=nonnegativeInt(i.value(),"female_gunner_passive_level");
    }
    return out;
}
void ExperimentalSkillConfiguration::configureFemaleGunnerSourceSkill(SkillKey key,int level,const ExperimentalCharacterPlan &plan) {
    if(!(identity_==plan.identity)||pvfIdentity_!=plan.pvfIdentity||identity_.jobId!=5||key.jobId!=5)
        throw std::invalid_argument("Female Gunner configuration requires the exact selected source identity");
    const auto known=plan.skills.find(key);const auto descriptor=plan.femaleGunnerSkills.find(key);
    if(known==plan.skills.end()||descriptor==plan.femaleGunnerSkills.end()||!known->second.data)
        throw std::invalid_argument("Female Gunner source descriptor unavailable");
    const auto &row=known->second;
    int maximum=0;
    for(const auto *tag:{"[growtype maximum level]","[second growtype maximum level]"})
        for(const auto &v:row.data->values(tag))if(v.is_number_integer())maximum=std::max(maximum,v.get<int>());
    if(level<1||level>std::max(1,maximum))throw std::invalid_argument("Female Gunner experimental level exceeds all source purchase ceilings");
    if(row.kind==SkillSourceKind::Passive) {
        // Separate explicit test overlay. Never writes the normal skill ledger.
        auto updated=unknown_;updated["female_gunner_passive_levels"][std::to_string(key.skillId)]=level;
        updated["female_gunner_passive_policy"]="user-test-source-passive-overlay-v1";unknown_=std::move(updated);return;
    }
    if(!descriptor->second.dedicatedRuntime||descriptor->second.stages.empty())
        throw std::invalid_argument("Female Gunner dedicated source stage/resource dispatch is unavailable");
    const auto &first=descriptor->second.stages.front();
    const auto *motion=plan.motion(first.motionTag,first.motionSlot);
    if(!motion)throw std::invalid_argument("Female Gunner initial source motion unavailable");
    ExperimentalSkillBinding candidate;candidate.key=key;candidate.level=level;candidate.skillSource=row.source;
    candidate.motion=checkedBinding(*motion,plan,false);
    if(first.hasAttack) {
        const auto *attack=plan.attack(first.attackTag,first.attackSlot);
        if(!attack)throw std::invalid_argument("Female Gunner initial source ATK unavailable");
        // Keep exact source binding even when a status requires the dedicated
        // World consumer. That consumer preflights before cost publication.
        candidate.attack=*attack;
    }
    const auto old=bindings_.find(key);if(old!=bindings_.end())candidate.unknown=old->second.unknown;
    candidate.unknown.erase("user_requested_temporary_template");
    candidate.unknown["female_gunner_source_controller"]={{"policy","inferred-1031-female-gunner-source-families-v1"},
        {"classification","inferred"},{"native_confirmed",false},{"descriptor",descriptor->second.snapshot()},
        {"qualification_policy","explicit-experimental-all-source-branches; normal-learning-ledger-unchanged"}};
    bindings_[key]=std::move(candidate);
}
void ExperimentalSkillConfiguration::setWeaponTypePolicy(const std::string &policy) {
    if(policy!="physical"&&policy!="magical"&&policy!="blocked")throw std::invalid_argument("Unknown experimental weapon type policy");
    weaponTypePolicy_=policy;
}
const ExperimentalSkillBinding *ExperimentalSkillConfiguration::binding(SkillKey key) const {
    const auto found=bindings_.find(key);return found==bindings_.end()?nullptr:&found->second;
}
void ExperimentalSkillConfiguration::assignSlot(size_t slot,std::optional<SkillKey> key,const ExperimentalCharacterPlan &plan) {
    if(!(identity_==plan.identity)||pvfIdentity_!=plan.pvfIdentity||slot>=slots_.size())throw std::invalid_argument("Experimental slot/profile mismatch");
    if(key)activeSkill(*key,plan);slots_[slot]=key;
}
void ExperimentalSkillConfiguration::configureSkill(SkillKey key,const ExperimentalSourceBinding &motion,
    std::optional<ExperimentalSourceBinding> attack,int level,const ExperimentalCharacterPlan &plan) {
    if(!(identity_==plan.identity)||pvfIdentity_!=plan.pvfIdentity)throw std::invalid_argument("Experimental configuration/profile mismatch");
    const auto &row=activeSkill(key,plan);
    int maximum=row.data?row.data->purchaseMaximum(identity_.growtype).value_or(1):1;
    if(identity_.jobId==1&&row.data)for(const auto &tag:{"[growtype maximum level]","[second growtype maximum level]"})
        for(const auto &v:row.data->values(tag))if(v.is_number_integer())maximum=std::max(maximum,v.get<int>());
    if(level<1||level>std::max(1,maximum))throw std::invalid_argument("Experimental skill level exceeds selected source purchase range");
    ExperimentalSkillBinding candidate;candidate.key=key;candidate.skillSource=row.source;candidate.level=level;candidate.motion=checkedBinding(motion,plan,false);
    if(attack) {
        const auto source=plan.sourceSkillActions.find(key);
        const bool exactGrabTry=source!=plan.sourceSkillActions.end()&&source->second.nativeGrab&&
            !source->second.nativeStages.empty()&&source->second.nativeStages.front().attack.json()==attack->source.json();
        if(exactGrabTry) {
            const auto *known=plan.attack(attack->tag,attack->slot,attack->occurrence);
            if(!known||known->json()!=attack->json())throw std::invalid_argument("Fighter grab try source binding changed");
            candidate.attack=*known;
        } else candidate.attack=checkedBinding(*attack,plan,true);
    }
    const auto old=bindings_.find(key);if(old!=bindings_.end())candidate.unknown=old->second.unknown;
    candidate.unknown.erase("user_requested_temporary_template");
    candidate.unknown.erase("source_nut_action_controller");
    candidate.unknown.erase("source_body_action_controller");
    bindings_[key]=std::move(candidate);
}
void ExperimentalSkillConfiguration::clearSkillBinding(SkillKey key){
    bindings_.erase(key);
    if(unknown_.contains("source_action_passives")) {
        auto &rows=unknown_["source_action_passives"];
        rows.erase(std::remove_if(rows.begin(),rows.end(),[&](const Json &r){return SkillKey::fromJson(r.at("key"))==key;}),rows.end());
        if(rows.empty()){unknown_.erase("source_action_passives");unknown_.erase("source_action_passive_policy");}
    }
    if(key.jobId==5&&unknown_.contains("female_gunner_passive_levels")&&unknown_.at("female_gunner_passive_levels").is_object())
        unknown_["female_gunner_passive_levels"].erase(std::to_string(key.skillId));
}
bool ExperimentalSkillConfiguration::sameConfiguration(const ExperimentalSkillConfiguration &other) const {
    const auto sourceEqual=[](const SourceRef &a,const SourceRef &b) {
        return a.packageIdentity==b.packageIdentity&&a.memberPath==b.memberPath&&a.memberSha256==b.memberSha256&&
            a.textEncoding==b.textEncoding&&a.byteOffset==b.byteOffset&&a.byteLength==b.byteLength&&
            a.ordinal==b.ordinal&&a.scope==b.scope&&a.literalPath==b.literalPath;
    };
    const auto bindingEqual=[&](const ExperimentalSourceBinding &a,const ExperimentalSourceBinding &b) {
        return a.tag==b.tag&&a.slot==b.slot&&a.occurrence==b.occurrence&&sourceEqual(a.source,b.source);
    };
    if(!(identity_==other.identity_)||pvfIdentity_!=other.pvfIdentity_||weaponTypePolicy_!=other.weaponTypePolicy_||
        !(slots_==other.slots_)||unknown_!=other.unknown_||bindings_.size()!=other.bindings_.size())return false;
    auto a=bindings_.begin(),b=other.bindings_.begin();
    for(;a!=bindings_.end();++a,++b) {
        const auto &x=a->second,&y=b->second;
        if(!(a->first==b->first)||x.level!=y.level||!sourceEqual(x.skillSource,y.skillSource)||
            !bindingEqual(x.motion,y.motion)||bool(x.attack)!=bool(y.attack)||x.unknown!=y.unknown)return false;
        if(x.attack&&!bindingEqual(*x.attack,*y.attack))return false;
    }
    return true;
}
Json ExperimentalSkillConfiguration::snapshot() const {
    Json out=unknown_,slots=Json::array(),bindings=Json::array();
    for(const auto &key:slots_)slots.push_back(key?key->json():Json());
    for(const auto &entry:bindings_) {
        const auto &b=entry.second;Json row=b.unknown;row["key"]=b.key.json();row["skill_source"]=b.skillSource.json();row["level"]=b.level;row["motion"]=b.motion.json();
        row["attack"]=b.attack?b.attack->json():Json();bindings.push_back(std::move(row));
    }
    out["schema"]=1;out["policy"]=configurationPolicy;out["identity"]=identity_.json();out["pvf_identity"]=pvfIdentity_;
    out["weapon_type_policy"]=weaponTypePolicy_;
    out["slots"]=std::move(slots);out["skill_bindings"]=std::move(bindings);return out;
}
void ExperimentalSkillConfiguration::restore(const Json &value,const ExperimentalCharacterPlan &plan) {
    if(!value.is_object()||nonnegativeInt(value.at("schema"),"schema")!=1||value.at("policy")!=configurationPolicy||
        !(CharacterIdentity::fromJson(value.at("identity"))==identity_)||value.at("pvf_identity")!=pvfIdentity_||
        !(identity_==plan.identity)||pvfIdentity_!=plan.pvfIdentity)
        throw std::invalid_argument("Experimental saved configuration identity/source/policy differs");
    if(!value.at("slots").is_array()||value.at("slots").size()!=13||!value.at("skill_bindings").is_array()||value.at("skill_bindings").size()>plan.skills.size())
        throw std::invalid_argument("Invalid experimental slot/binding count");
    ExperimentalSkillConfiguration candidate(plan);
    candidate.setWeaponTypePolicy(value.at("weapon_type_policy").get<std::string>());
    for(size_t slot=0;slot<13;++slot)if(!value.at("slots")[slot].is_null())candidate.assignSlot(slot,SkillKey::fromJson(value.at("slots")[slot]),plan);
    for(const auto &row:value.at("skill_bindings")) {
        const auto key=SkillKey::fromJson(row.at("key"));if(candidate.bindings_.count(key))throw std::invalid_argument("Duplicate experimental skill binding");
        if(row.at("skill_source")!=activeSkill(key,plan).source.json())throw std::invalid_argument("Saved experimental SKL source path/hash differs");
        if(row.contains("source_nut_action_controller")||row.contains("source_body_action_controller")) {
            candidate.configureSourceSkillAction(key,nonnegativeInt(row.at("level"),"level"),plan);
            const auto *expected=candidate.binding(key);
            const auto controller=plan.sourceSkillActions.at(key).controllerKey();
            if(row.contains("source_nut_action_controller")==row.contains("source_body_action_controller")||
               !expected||!row.contains(controller)||row.at("motion")!=expected->motion.json()||row.at("attack")!=(expected->attack?expected->attack->json():Json())||
               row.at(controller)!=expected->unknown.at(controller))
                throw std::invalid_argument("Saved source action controller dispatch differs");
        } else if(row.contains("female_gunner_source_controller")) {
            candidate.configureFemaleGunnerSourceSkill(key,nonnegativeInt(row.at("level"),"level"),plan);
            const auto *expected=candidate.binding(key);
            if(!expected||row.at("motion")!=expected->motion.json()||row.at("attack")!=(expected->attack?expected->attack->json():Json())||
                row.at("female_gunner_source_controller")!=expected->unknown.at("female_gunner_source_controller"))
                throw std::invalid_argument("Saved female Gunner controller source dispatch differs");
        } else {
            std::optional<ExperimentalSourceBinding> attack;if(!row.at("attack").is_null())attack=decodeBinding(row.at("attack"),plan,true);
            candidate.configureSkill(key,decodeBinding(row.at("motion"),plan,false),std::move(attack),nonnegativeInt(row.at("level"),"level"),plan);
        }
        candidate.bindings_.at(key).unknown=row;
    }
    // Keep the complete ordered object as a template. snapshot overwrites
    // recognized values in place, preserving unknown fields and their order.
    candidate.unknown_=value;
    if(value.contains("source_body_recovery_policy")) {
        if(!value.at("source_body_recovery_policy").is_string())throw std::invalid_argument("Body recovery policy must be a named comparison");
        candidate.setSourceBodyRecoveryPolicy(value.at("source_body_recovery_policy").get<std::string>());
        candidate.unknown_=value;
    }
    if(value.contains("female_gunner_passive_levels")) {
        if(plan.identity.jobId!=5||!value.at("female_gunner_passive_levels").is_object()||
            value.value("female_gunner_passive_policy",std::string())!="user-test-source-passive-overlay-v1")
            throw std::invalid_argument("Invalid female Gunner passive overlay identity/policy");
        candidate.unknown_.erase("female_gunner_passive_levels");
        for(auto it=value.at("female_gunner_passive_levels").begin();it!=value.at("female_gunner_passive_levels").end();++it) {
            size_t parsed=0;const auto id=std::stoi(it.key(),&parsed);
            if(parsed!=it.key().size()||std::to_string(id)!=it.key()||plan.skills.find({5,id})==plan.skills.end()||plan.skills.at({5,id}).kind!=SkillSourceKind::Passive)
                throw std::invalid_argument("Invalid saved female Gunner passive key");
            candidate.configureFemaleGunnerSourceSkill({5,id},nonnegativeInt(it.value(),"female_gunner_passive_level"),plan);
        }
        // Validation above used a private overlay. Retain the exact saved
        // ordered root rather than moving its passive member to the end.
        candidate.unknown_=value;
    }
    if(value.contains("source_action_audio_policy")) {
        candidate.setSourceActionAudioPolicy(value.at("source_action_audio_policy").get<std::string>(),plan);
        candidate.unknown_=value;
    }
    if(value.contains("source_action_passives")||value.contains("source_action_passive_policy")) {
        if(!value.contains("source_action_passives")||!value.at("source_action_passives").is_array()||
           value.at("source_action_passives").size()>plan.skills.size()||
           value.value("source_action_passive_policy",std::string())!="reviewed-source-action-passive-levels-v1")
            throw std::invalid_argument("Malformed source-action passive projection");
        candidate.unknown_.erase("source_action_passives");candidate.unknown_.erase("source_action_passive_policy");
        std::set<SkillKey> seen;
        for(const auto &row:value.at("source_action_passives")) {
            const auto key=SkillKey::fromJson(row.at("key"));const auto found=plan.skills.find(key);
            const int level=nonnegativeInt(row.at("level"),"source_action_passive_level");
            if(!seen.insert(key).second||found==plan.skills.end()||row.at("source")!=found->second.source.json()||level<1)
                throw std::invalid_argument("Source-action passive duplicate/key/source/level differs");
            candidate.configureSourceActionPassive(key,level,plan);
        }
        candidate.unknown_=value;
    }
    *this=std::move(candidate);
}
Json ExperimentalSkillConfiguration::rows(const ExperimentalCharacterPlan &plan) const {
    if(!(identity_==plan.identity)||pvfIdentity_!=plan.pvfIdentity)throw std::invalid_argument("Experimental row/profile mismatch");
    Json out=Json::array();for(const auto &entry:plan.skills) {
        Json row=entry.second.json(),slots=Json::array();for(size_t i=0;i<slots_.size();++i)if(slots_[i]&&*slots_[i]==entry.first)slots.push_back(i);
        const auto *configured=binding(entry.first);row["assigned_slots"]=slots;row["configured"]=bool(configured);
        row["selected_motion"]=configured?configured->motion.json():Json();row["selected_attack"]=configured&&configured->attack?configured->attack->json():Json();
        row["level"]=configured?configured->level:std::max(femaleGunnerPassiveLevel(entry.first),sourceActionPassiveLevel(entry.first));
        const auto sourceController=plan.femaleGunnerSkills.find(entry.first);
        if(sourceController!=plan.femaleGunnerSkills.end())row["female_gunner_controller"]=sourceController->second.snapshot();
        out.push_back(std::move(row));
    }return out;
}
ExperimentalCharacterRuntime::ExperimentalCharacterRuntime(std::shared_ptr<const ExperimentalCharacterPlan> plan,ExperimentalMovementPolicy policy)
    :plan_(std::move(plan)),configuration_(plan_?*plan_:throw std::invalid_argument("Missing experimental source plan")),policy_(std::move(policy)) {
    const auto *idle=plan_->motion("[waiting motion]");
    if(!idle||!plan_->animations.count(idle->source.memberPath))throw std::invalid_argument("Experimental character has no usable source waiting motion");
    for(const double value:{policy_.walkSpeed,policy_.runSpeed,policy_.verticalRatio,policy_.jumpVelocity,policy_.gravity})
        if(!std::isfinite(value)||value<0)throw std::invalid_argument("Invalid experimental movement policy");
    if(policy_.gravity<=0||policy_.gravity>INT32_MAX||std::floor(policy_.gravity)!=policy_.gravity||policy_.doubleTapMs<0)
        throw std::invalid_argument("Invalid experimental jump/input policy");
}
void ExperimentalCharacterRuntime::setBasicAttackMovementEnabled(bool enabled) {
    if(attacking())throw std::logic_error("Basic attack movement policy changes require an idle action boundary");
    basicMovementPolicy_.enabled=enabled;dashAttackGlide_.reset();
}
void ExperimentalCharacterRuntime::setAnimationClockPolicy(std::optional<ani_clock::ClockPolicy> policy) {
    if(policy&&*policy!=ani_clock::ClockPolicy::SourceDelay100&&*policy!=ani_clock::ClockPolicy::Inferred60UsPercentDeadlines)
        throw std::invalid_argument("Unknown experimental animation clock policy");
    animationClockPolicy_=policy;
}
bool ExperimentalCharacterRuntime::begin(const ExperimentalSourceBinding &motion,std::optional<ExperimentalSourceBinding> attack,std::optional<SkillKey> skill,
    uint64_t lastClockTick,double attackPerMille,const FemaleGunnerStageTiming *timing) {
    if(!plan_->animations.count(motion.source.memberPath))return false;
    if(actionSequence_==UINT64_MAX)throw std::overflow_error("Experimental action identity exhausted");
    // Allocate/copy source bindings before changing the active action. Swaps
    // below are no-throw for these value types; a gate rejection never leaves
    // a partial motion or consumes cost.
    std::optional<ExperimentalSourceBinding> preparedMotion(motion);
    std::shared_ptr<const std::vector<int32_t>> delays;
    std::optional<ani_clock::Cursor> cursor;
    std::vector<ani_clock::FrameVisit> initialVisits;
    int32_t speedStat=0;
    std::optional<FemaleGunnerStageTiming> preparedTiming;
    if(timing)preparedTiming=*timing;
    if(animationClockPolicy_||(timing&&timing->controlled)) {
        auto owned=std::make_shared<std::vector<int32_t>>();
        const auto animation=plan_->animations.at(motion.source.memberPath);
        owned->reserve(animation->frames.size());
        if(timing&&timing->controlled) {
            if(timing->runtimeDelays.size()!=animation->frames.size())throw std::invalid_argument("Controller timing/source frame count differs");
            *owned=timing->runtimeDelays;
        } else for(const auto &frame:animation->frames)owned->push_back(frame.duration);
        delays=std::move(owned);cursor.emplace();
        float rate=100;
        // A controller timeline and its entity pulses share unpaused wall
        // milliseconds. Reapplying attack-speed deadlines to this resolved
        // schedule would shorten the body while its last projectile still
        // waits on the original command. Uncontrolled clips retain the user's
        // selected clock policy and speed mapping.
        const auto clockPolicy=timing&&timing->controlled?ani_clock::ClockPolicy::SourceDelay100:
            animationClockPolicy_.value_or(ani_clock::ClockPolicy::SourceDelay100);
        if(clockPolicy==ani_clock::ClockPolicy::Inferred60UsPercentDeadlines) {
            speedStat=animationSpeedStat(attackPerMille);
            rate=ani_clock::resolveRate(speedStat,ani_clock::RatePath::Installation);
        }
        initialVisits=cursor->install({delays->data(),delays->size(),timing&&timing->repeatAnimation},rate,clockPolicy,lastClockTick).visits;
    }
    bufferedDefaultSkill_.reset();
    activeMotion_.swap(preparedMotion);activeAttack_.swap(attack);activeSkill_=skill;age_=0;lastFrame_=-1;
    femaleGunnerBasicJumpStage_=-1;dashAttackGlide_.reset();gunnerGround_.reset();
    animationDelays_=std::move(delays);animationCursor_=std::move(cursor);initialClockVisits_=std::move(initialVisits);
    actionTiming_=std::move(preparedTiming);
    animationSpeedStat_=speedStat;++actionSequence_;return true;
}
void ExperimentalCharacterRuntime::beginGunnerGroundPhase(int phase,int subtype,uint64_t tick,double speed,bool down) {
    const auto found=plan_->gunnerBasicSources.find(subtype);
    if(found==plan_->gunnerBasicSources.end())throw std::invalid_argument("Source GunInfo is unavailable for equipped subtype");
    const uint32_t shots=gunnerGround_?gunnerGround_->shots:0;
    const auto buffered=bufferedDefaultSkill_&&bufferedDefaultSkill_->ownerActionSequence==actionSequence_?bufferedDefaultSkill_:std::nullopt;
    const auto *motion=phase==0?plan_->motion("[attack motion]",0):phase==2?plan_->motion("[attack motion]",1):
        plan_->motion("[etc motion]",phase==1?(down?1:0):phase==3?(down?3:2):4);
    if(!motion)throw std::invalid_argument("Source Gunner phase binding is unavailable");
    const auto deadlines=gunnerBasicDeadlines(found->second,speed,phase==3);
    const auto timing=gunnerBasicStageTiming(*plan_->animations.at(motion->source.memberPath),phase,deadlines);
    if(!begin(*motion,std::nullopt,std::nullopt,tick,speed,&timing))throw std::invalid_argument("Source Gunner phase could not begin");
    gunnerGround_=GunnerGroundState{subtype,phase,shots,0,false,deadlines,down};
    if(buffered)bufferedDefaultSkill_=BufferedDefaultSkill{buffered->skill,actionSequence_};
}
bool ExperimentalCharacterRuntime::request(const CharacterActionRequest &request) {
    if(request.simulationMs<0)return false;
    const bool skillKey=request.inputKey==6||request.inputKey==7||(request.inputKey>=20&&request.inputKey<33)||
        (request.action==CharacterAction::Skill&&request.skill);
    if(skillKey) {
        const bool repeat=request.inputDown&&!heldSkillKeys_.insert(request.inputKey).second;
        if(!request.inputDown)heldSkillKeys_.erase(request.inputKey);
        const auto heldSkill=skillRequested_?skillRequested_:activeSkill_;
        if(repeat&&heldSkill&&heldSkill->jobId==5&&(heldSkill->skillId==36||heldSkill->skillId==107)&&
           requestedReleaseKey_==request.inputKey)return true;
        if(request.inputDown)requestedReleaseKey_=request.inputKey;
    }
    // Keep source ATTACK/JUMP edges and releases independently of command
    // recognition. OS key repeat is not another attack press.
    if(request.inputKey==4) {
        if(plan_->identity.jobId==2&&request.inputDown&&attackHeld_)return true;
        attackEdge_=attackEdge_||(request.inputDown&&!attackHeld_);
        attackHeld_=request.inputDown;
    }
    if(request.inputKey==5) {
        jumpEdge_=jumpEdge_||(request.inputDown&&!jumpHeld_);
        jumpHeld_=request.inputDown;
    }
    if(request.inputKey>=0&&request.inputKey<4) {
        const auto key=size_t(request.inputKey);const bool wasHeld=held_[key];held_[key]=request.inputDown;
        if(request.inputDown&&!wasHeld&&(key==0||key==1)) {
            auto &previous=key==0?lastLeft_:lastRight_;
            if(previous>=0&&request.simulationMs>=previous&&request.simulationMs-previous<=policy_.doubleTapMs)running_=true;previous=request.simulationMs;
        }return true;
    }
    if(!request.inputDown)return true;
    if(request.inputKey==6) {
        const ExperimentalSkillRow *selected=nullptr;
        for(const auto &entry:plan_->skills)if(entry.second.data&&sourceBaseDefaultSkillCommand(*entry.second.data,plan_->identity.growtype)) {
            if(selected){auto diagnostic=issue("ambiguous_source_default_z","Multiple unconditional base source commands; no implicit key assignment");
                diagnostic["skill_failure"]=true;appendPending(pendingDiagnostics_,std::move(diagnostic));return false;}
            selected=&entry.second;
        }
        if(!selected){auto diagnostic=issue("source_default_z_unavailable","This job has no unique supported base default Z source command");
            diagnostic["skill_failure"]=true;appendPending(pendingDiagnostics_,std::move(diagnostic));return false;}
        defaultSkillRequested_=BufferedDefaultSkill{selected->key,activeMotion_?actionSequence_:0};return true;
    }
    if((request.inputKey>=20&&request.inputKey<33)||request.inputKey==7) {
        const auto slot=request.inputKey==7?size_t(12):size_t(request.inputKey-20);
        const auto key=configuration_.slots()[slot];
        if(!key){appendPending(pendingDiagnostics_,issue("unassigned_experimental_slot",std::to_string(slot)));return false;}
        skillRequested_=key;return true;
    }
    if(request.action==CharacterAction::Skill) {
        if(!request.skill||request.skill->jobId!=plan_->identity.jobId)return false;
        try{activeSkill(*request.skill,*plan_);}catch(...){return false;}skillRequested_=request.skill;return true;
    }
    if(request.action==CharacterAction::Jump){jumpRequested_=true;return true;}
    if(request.action==CharacterAction::BasicAttack||request.action==CharacterAction::DashAttack||request.action==CharacterAction::JumpAttack) {
        femaleGunnerModeBlade_=false;
        if(activeMotion_&&(!activeSkill_||femaleGunnerModeAttack_))comboQueued_=true;else attackRequested_=true;return true;
    }
    appendPending(pendingDiagnostics_,issue("unsupported_experimental_input","Command recognition and native special inputs are not restored"));return false;
}
void ExperimentalCharacterRuntime::releaseInputs(){held_.fill(false);lastLeft_=lastRight_=-100000;heldSkillKeys_.clear();requestedReleaseKey_=activeReleaseKey_=-1;attackHeld_=jumpHeld_=attackEdge_=jumpEdge_=false;jumpRequested_=attackRequested_=running_=comboQueued_=false;skillRequested_.reset();defaultSkillRequested_.reset();bufferedDefaultSkill_.reset();}
void ExperimentalCharacterRuntime::cancel(ControllerCancelReason) {
    releaseInputs();activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();age_=0;lastFrame_=-1;combo_=0;lastMs_=-1;lastTick_=0;
    femaleGunnerBasicJumpStage_=-1;dashAttackGlide_.reset();
    animationCursor_.reset();animationDelays_.reset();initialClockVisits_.clear();animationSpeedStat_=0;actionTiming_.reset();
    femaleGunnerAction_.reset();femaleGunnerStage_=0;femaleGunnerRepeat_=0;femaleGunnerEmissionPending_=false;femaleGunnerStageElapsedMs_=0;
    channelContract_.reset();channelState_.reset();
    channelRecoveryRemainingMs_=0;
    femaleGunnerModeAttack_=femaleGunnerModeBlade_=false;
    femaleGunnerOverrideStages_.clear();femaleGunnerOverrideDamageColumns_.clear();femaleGunnerFinishMode_=false;
    sourceActions_.clear();sourceEntities_.clear();sourceRecoil_.reset();sourceBodyRecoveryRemainingMs_=0;
    jumpLocomotion_.reset();nativeJump_.reset();gunnerGround_.reset();
}
void ExperimentalCharacterRuntime::interruptActionPreservingMovement() {
    const auto heldMovement=held_;
    cancel(ControllerCancelReason::ExplicitReset);
    // Reconstructed host policy: cancelling an action is not a physical
    // direction KEYUP. Keep accepted cooldowns/configuration and monotonic
    // counters, but discard every action/transient request through cancel.
    held_=heldMovement;lastLeft_=lastRight_=-100000;
}
bool ExperimentalCharacterRuntime::neutralReactionReady() const noexcept {
    return !activeMotion_&&!activeSkill_&&!channelState_&&channelRecoveryRemainingMs_==0&&
        sourceBodyRecoveryRemainingMs_==0&&sourceActions_.empty()&&sourceEntities_.empty()&&!dashAttackGlide_&&!gunnerGround_&&
        femaleGunnerBasicJumpStage_<0;
}
ExperimentalCharacterRuntime ExperimentalCharacterRuntime::prepareNeutralReaction() const {
    if(!neutralReactionReady())throw std::invalid_argument("Prepared neutral reaction cannot cancel an active experimental action/entity");
    auto candidate=*this;const auto heldMovement=held_;
    candidate.cancel(ControllerCancelReason::ExplicitReset);
    // Retain physical movement ownership; action DOWN requests and release
    // keys are transient. CD, configuration, monotonic action/entity counters
    // and plan identity remain the copied, already accepted values.
    candidate.held_=heldMovement;candidate.lastLeft_=candidate.lastRight_=-100000;
    return candidate;
}
bool ExperimentalCharacterRuntime::sourceBodyReactionReady() const noexcept {
    if(!activeMotion_||!activeSkill_||!activeAttack_||sourceActions_.size()!=1||
       !sourceEntities_.empty()||channelContract_||channelState_||channelRecoveryRemainingMs_!=0||
       femaleGunnerAction_||femaleGunnerModeAttack_||femaleGunnerModeBlade_||femaleGunnerFinishMode_||
       !femaleGunnerOverrideStages_.empty()||dashAttackGlide_||gunnerGround_||jumpLocomotion_||nativeJump_||
       femaleGunnerBasicJumpStage_>=0)return false;
    const auto action=sourceActions_.find(actionSequence_);
    const auto descriptor=plan_->sourceSkillActions.find(*activeSkill_);
    return action!=sourceActions_.end()&&action->second.key==*activeSkill_&&
        descriptor!=plan_->sourceSkillActions.end()&&descriptor->second.kind==SourceSkillActionKind::BodyAttack&&
        !descriptor->second.nativeGrab&&
        activeMotion_->source.memberPath==descriptor->second.motion.memberPath&&
        activeMotion_->source.memberSha256==descriptor->second.motion.memberSha256&&
        activeAttack_->source.memberPath==descriptor->second.attack.memberPath&&
        activeAttack_->source.memberSha256==descriptor->second.attack.memberSha256;
}
ExperimentalCharacterRuntime ExperimentalCharacterRuntime::prepareSourceBodyReaction() const {
    if(!sourceBodyReactionReady())throw std::invalid_argument("Active source-body reaction lacks its exact action or has unsupported owned state");
    auto candidate=*this;const auto heldMovement=held_;
    candidate.cancel(ControllerCancelReason::ExplicitReset);
    // The copy retains accepted cooldowns, source/configuration identities,
    // last cost and monotonic counters. Only publishing this candidate cancels
    // the action; an armored nonlethal hit or MISS discards it unchanged.
    candidate.held_=heldMovement;candidate.lastLeft_=candidate.lastRight_=-100000;
    return candidate;
}
bool ExperimentalCharacterRuntime::sourceMovingReactionReady() const noexcept {
    if(channelContract_||channelState_||channelRecoveryRemainingMs_||sourceBodyRecoveryRemainingMs_||femaleGunnerAction_||
       femaleGunnerModeAttack_||femaleGunnerModeBlade_||femaleGunnerFinishMode_||!femaleGunnerOverrideStages_.empty()||
       dashAttackGlide_||gunnerGround_||jumpLocomotion_||femaleGunnerBasicJumpStage_>=0)return false;
    if(!activeMotion_&&sourceEntities_.empty())return false;
    const auto moving=[&](SkillKey key) {const auto i=plan_->sourceSkillActions.find(key);return i!=plan_->sourceSkillActions.end()&&bool(i->second.movingImpact);};
    for(const auto &entity:sourceEntities_)if(!moving(entity.key))return false;
    for(const auto &entry:sourceActions_)if(!moving(entry.second.key))return false;
    if(activeMotion_) {
        // A moving PO skill has no body ATK binding. Its independent entity
        // owns the descriptor's attack; requiring that ATK on the body rejects
        // the exact configuration created by configureSourceSkillAction.
        if(!activeSkill_||activeAttack_||!moving(*activeSkill_)||sourceActions_.size()!=1)return false;
        const auto &descriptor=plan_->sourceSkillActions.at(*activeSkill_);const auto action=sourceActions_.find(actionSequence_);
        if(action==sourceActions_.end()||!(action->second.key==*activeSkill_)||
           activeMotion_->source.memberPath!=descriptor.motion.memberPath||activeMotion_->source.memberSha256!=descriptor.motion.memberSha256)return false;
    } else if(activeSkill_||!sourceActions_.empty())return false;
    return true;
}
ExperimentalCharacterRuntime ExperimentalCharacterRuntime::prepareSourceMovingReaction(bool death) const {
    if(!sourceMovingReactionReady())throw std::invalid_argument("Source moving reaction has foreign action/entity state");
    auto candidate=*this;const auto movement=held_;
    auto entities=std::move(candidate.sourceEntities_);
    candidate.cancel(death?ControllerCancelReason::Death:ControllerCancelReason::ExplicitReset);
    if(!death)candidate.sourceEntities_=std::move(entities);
    candidate.held_=movement;candidate.lastLeft_=candidate.lastRight_=-100000;
    return candidate;
}
int64_t ExperimentalCharacterRuntime::remainingCooldown(SkillKey key,int64_t ms) const {
    if(ms<0)throw std::invalid_argument("Negative experimental cooldown time");
    const auto found=cooldowns_.find(key);return found==cooldowns_.end()?0:std::max<int64_t>(0,found->second-ms);
}
Json ExperimentalCharacterRuntime::cooldownSnapshot(int64_t nowMs) const {
    if(nowMs<0)throw std::invalid_argument("Negative experimental cooldown snapshot time");
    Json rows=Json::array();
    for(const auto &entry:cooldowns_) {
        const auto remaining=std::max<int64_t>(0,entry.second-nowMs);if(!remaining)continue;
        const auto found=plan_->skills.find(entry.first);
        if(found==plan_->skills.end()||!found->second.source.memberSha256.size())
            throw std::runtime_error("Experimental cooldown lost its typed source skill");
        rows.push_back({{"key",entry.first.json()},{"skill_source",found->second.source.json()},{"remaining_ms",remaining}});
    }
    return {{"schema",1},{"identity",plan_->identity.json()},{"pvf_identity",plan_->pvfIdentity},{"captured_ms",nowMs},
        {"policy",configurationPolicy},{"skills",rows}};
}
std::map<SkillKey,int64_t> ExperimentalCharacterRuntime::prepareCooldownRestore(
    const Json &saved,const ExperimentalCharacterPlan &plan,int64_t restoredNowMs) {
    if(restoredNowMs<0||!saved.is_object()||nonnegativeInt(saved.at("schema"),"cooldown_schema")!=1||
       saved.at("identity")!=plan.identity.json()||saved.at("pvf_identity")!=plan.pvfIdentity||
       saved.at("policy")!=configurationPolicy||!saved.at("captured_ms").is_number_integer()||saved.at("captured_ms")!=restoredNowMs||
       !saved.at("skills").is_array()||saved.at("skills").size()>plan.skills.size())
        throw std::invalid_argument("Experimental cooldown identity/source/policy differs");
    std::map<SkillKey,int64_t> candidate;
    for(const auto &row:saved.at("skills")) {
        const auto key=SkillKey::fromJson(row.at("key"));const auto found=plan.skills.find(key);
        if(key.jobId!=plan.identity.jobId||found==plan.skills.end()||found->second.kind!=SkillSourceKind::Active||
           row.at("skill_source")!=found->second.source.json()||candidate.count(key))
            throw std::invalid_argument("Experimental cooldown key/source is foreign or duplicated");
        const auto remaining=nonnegativeInt(row.at("remaining_ms"),"cooldown_remaining");
        if(!remaining)throw std::invalid_argument("Expired experimental cooldown must be omitted");
        if(int64_t(remaining)>INT64_MAX-restoredNowMs)throw std::overflow_error("Experimental cooldown restore deadline overflow");
        candidate.emplace(key,restoredNowMs+remaining);
    }
    return candidate;
}
ExperimentalTickResult ExperimentalCharacterRuntime::advance(uint64_t fixedTick,const ExperimentalActorState &state,
    const std::function<bool(double,double)> &canWalk,const ExperimentalSkillActionGate &skillGate) {
    if(!fixedTick||fixedTick>uint64_t(INT64_MAX)||!canWalk)throw std::invalid_argument("Experimental tick/geometry unavailable");
    const auto ms=FixedStepClock::millisecondsAtTick(fixedTick),previous=FixedStepClock::millisecondsAtTick(fixedTick-1);
    if(ms>uint64_t(INT64_MAX)||(lastMs_>=0&&(fixedTick!=lastTick_+1||int64_t(previous)!=lastMs_)))
        throw std::invalid_argument("Experimental runtime requires consecutive fixed ticks");
    for(const double value:{state.x,state.y,state.z,state.vx,state.vy,state.vz,state.movePerMille,state.attackPerMille,state.dashXRatio,state.dashYRatio})
        if(!std::isfinite(value))throw std::invalid_argument("Non-finite experimental actor state");
    if((state.direction!=-1&&state.direction!=1)||state.mp<0||state.movePerMille<0||state.attackPerMille<0||state.dashXRatio<0||state.dashYRatio<0)
        throw std::invalid_argument("Invalid experimental actor resources/direction/speeds");
    const auto dt=uint32_t(ms-previous);lastTick_=fixedTick;lastMs_=int64_t(ms);
    ExperimentalTickResult out;out.actor=state;out.diagnostics.swap(pendingDiagnostics_);
    const auto liveMode=[&](int id)->const FemaleGunnerSkillCommand * {
        for(auto i=state.femaleGunnerBuffs.rbegin();i!=state.femaleGunnerBuffs.rend();++i)if(i->key==SkillKey{5,id})return &*i;
        return nullptr;
    };
    const auto sourceJumpPower=[&] {
        double jump=policy_.jumpVelocity;
        for(const auto &f:plan_->characterDefinition.source.script.fields)
            if(normalize(f.tag)=="[jump power]"&&f.values.size()==1&&f.values[0].is_number()) {jump=f.values[0].get<double>();break;}
        if(const auto leap=liveMode(175)) {
            const auto table=leap->rawTables.value("static_data",Json::array());
            if(!table.empty()&&table[0].is_number())jump*=1+table[0].get<double>()/1000.0;
        }
        return jump;
    };
    const auto endMode=[&](const FemaleGunnerSkillCommand &mode) {
        auto ended=mode;ended.kind=FemaleGunnerCommandKind::Clear;ended.effectRole="end_mode";ended.preflightOnly=false;
        ended.evidence.push_back({{"policy","current1031-mode-input-explain"},{"classification","inferred-source-input-consumer"},
            {"basis",mode.key.skillId==100?"Twin Gunblade source explain: its finisher ends this mode":"Mobile shooting source explain: pressing skill again or Jump ends this mode"}});
        out.femaleGunnerCommands.push_back(std::move(ended));
    };
    const auto transformedStages=[&](int id) {
        std::vector<FemaleGunnerStage> stages;
        const auto add=[&](size_t motion,std::optional<size_t> attack,bool emit=false) {
            FemaleGunnerStage s;s.motionSlot=motion;s.emitCommand=emit;
            if(attack){s.hasAttack=true;s.attackSlot=*attack;}stages.push_back(std::move(s));
        };
        if(id==3){add(86,17);add(87,17);}
        else if(id==6){add(88,18);add(89,19);}
        else if(id==7)add(90,{},true);
        else if(id==100){add(91,{});add(92,20);add(93,21);}
        return stages;
    };
    const auto selectModeObject=[&](FemaleGunnerSkillCommand &command,const std::string &stem) {
        const auto &bindings=plan_->femaleGunnerSkills.at({5,100}).objectBindings;
        const std::string member="passiveobject/character/gunner/"+stem+".obj";
        const auto found=bindings.find(member);
        if(found==bindings.end())throw std::logic_error("Twin Gunblade source object binding unavailable: "+member);
        command.objectSource=found->second.source;command.animationSource.reset();command.attackSource.reset();
        for(const auto &ani:found->second.animations)if(!command.animationSource||ani.first=="[basic motion]#0")command.animationSource=ani.second;
        for(const auto &atk:found->second.attacks)if(!command.attackSource||atk.first=="[attack info]#0")command.attackSource=atk.second;
    };
    const auto setStageDamage=[&](FemaleGunnerSkillCommand &command,size_t index,const std::vector<int> &columns) {
        if(columns.empty())return;
        if(index>=columns.size())throw std::logic_error("Twin Gunblade source stage operand missing");
        const auto value=skillLevelValue(command.rawTables.at("level_info"),command.level,columns[index]);
        if(!value)throw std::logic_error("Twin Gunblade source coefficient unavailable");
        command.damage={};command.damage.replacesAttackCoefficients=true;command.damage.percent=float(*value);
        command.damage.sources.push_back({{"policy","inferred-1031-twingunblade-alternate-actions-v1"},{"classification","inferred"},
            {"mode_source",plan_->skills.at({5,100}).source.json()},{"mode_level",command.level},{"source_column",columns[index]},
            {"basis","Current1031 skill100 explain, ordered CHR actions/ATK and source level table; perstage native setters remain unverified"}});
    };
    const auto fail=[&](const char *code,const std::string &message) {
        auto diagnostic=issue(code,message);diagnostic["skill_failure"]=true;out.diagnostics.push_back(std::move(diagnostic));
    };
    const auto sourceActionAttackSpeed=[&]() {
        const auto action=sourceActions_.find(actionSequence_);
        return out.actor.attackPerMille+(action!=sourceActions_.end()?action->second.operands.attackSpeedBonusPermille:0);
    };
    const auto publishSourceBodyRecovery=[&]() {
        out.state="inferred_source_body_recovery";out.actor.vx=out.actor.vy=0;
        out.animationPath=activeMotion_->source.memberPath;out.animationAgeMs=age_;out.poseFrame=std::max(0,lastFrame_);
        out.animationControllerDelays=animationDelays_;if(animationCursor_)out.animationClock=animationCursor_->snapshot();
        if(skillRequested_||defaultSkillRequested_)fail("source_body_recovery_blocked","Source static recovery is live under the selected inferred comparison policy");
        skillRequested_.reset();defaultSkillRequested_.reset();bufferedDefaultSkill_.reset();
        attackRequested_=jumpRequested_=comboQueued_=attackEdge_=jumpEdge_=false;
        if(!state.hitStopped)sourceBodyRecoveryRemainingMs_=std::max<int64_t>(0,sourceBodyRecoveryRemainingMs_-dt);
        if(!sourceBodyRecoveryRemainingMs_) {
            activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();animationCursor_.reset();animationDelays_.reset();
            initialClockVisits_.clear();actionTiming_.reset();sourceActions_.clear();
        }
    };
    const auto publishChannelRecovery=[&]() {
        out.state="female_gunner_channel_recovery";out.actor.vx=out.actor.vy=0;
        out.animationPath=activeMotion_->source.memberPath;out.animationAgeMs=age_;
        out.poseFrame=std::max(0,lastFrame_);out.animationControllerDelays=animationDelays_;
        if(animationCursor_)out.animationClock=animationCursor_->snapshot();
        if(activeSkill_) {
            const auto skillLayers=plan_->femaleGunnerSkillLayers.find(*activeSkill_);
            if(skillLayers!=plan_->femaleGunnerSkillLayers.end()) {
                const auto layers=skillLayers->second.find(out.animationPath);
                if(layers!=skillLayers->second.end())out.skillAnimationLayers=layers->second;
            }
        }
        if(skillRequested_||defaultSkillRequested_)fail("female_gunner_channel_recovery","Source explain requires post-spray action recovery; static400..800ms mapping is inferred");
        skillRequested_.reset();defaultSkillRequested_.reset();attackRequested_=jumpRequested_=comboQueued_=false;
        if(!state.hitStopped) {
            attackEdge_=jumpEdge_=false;
            channelRecoveryRemainingMs_=std::max<int64_t>(0,channelRecoveryRemainingMs_-dt);
        }
        if(channelRecoveryRemainingMs_==0) {
            activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();animationCursor_.reset();animationDelays_.reset();
            initialClockVisits_.clear();actionTiming_.reset();
        }
    };
    const auto trySkill=[&](SkillKey key,bool defaultZ,uint64_t requestOwner=0,bool completedBoundary=false) {
        const auto *binding=configuration_.binding(key);
        const auto twin=liveMode(100);
        const bool transformed=twin&&key.jobId==5&&(key.skillId==3||key.skillId==6||key.skillId==7||key.skillId==100);
        const bool finisher=transformed&&key.skillId==100;
        const bool modeCancel=transformed&&femaleGunnerModeAttack_;
        if(key==SkillKey{5,15})if(const auto mode=liveMode(15)) {
            endMode(*mode);if(activeSkill_==std::optional<SkillKey>(key)) {activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();femaleGunnerAction_.reset();femaleGunnerModeAttack_=false;}
            return;
        }
        const bool learnedCancel=key==SkillKey{5,73}&&configuration_.femaleGunnerPassiveLevel({5,74})>0&&activeMotion_&&!activeSkill_;
        if(activeMotion_&&!defaultZ&&!learnedCancel&&!modeCancel){fail("experimental_action_busy","Wait for the current source motion to finish");return;}
        if(key==SkillKey{5,169}&&out.actor.z>0){fail("female_gunner_backstep_requires_ground","Source backstep is a ground short jump");return;}
        if(!binding){fail("manual_source_binding_required","Choose this job's CHR motion for the skill before use");return;}
        const bool fighterFreedom=plan_->identity.jobId==1&&state.fighter40JpTestFreedom;
        if(!fighterFreedom&&!finisher&&!state.noCooldown&&remainingCooldown(key,int64_t(ms))){fail("experimental_cooldown","Source evaluated cooldown is active");return;}
        try {
            const auto &row=activeSkill(key,*plan_);
            if(!row.data||binding->level<=0)throw std::invalid_argument("Experimental source/selected skill level unavailable");
            if(key==SkillKey{5,73}) {
                const auto explanation=row.data->definition.values("[explain]");
                if(explanation.size()!=1||!explanation.front().is_string()||
                   explanation.front().get<std::string>().find("只能在装备手炮") == std::string::npos)
                    throw std::invalid_argument("CannonBall weapon source requirement changed; re-audit current explain before release");
                if(state.weaponSubtype!=3) {
                    fail("female_gunner_requires_handcannon","加农炮只能在装备手炮的状态下施放");
                    out.diagnostics.push_back({{"code","female_gunner_source_weapon_requirement"},{"skill",key.json()},
                        {"source",row.source.json()},{"source_tag","[explain]"},{"required_source_weapon_subtype",3},
                        {"actual_source_weapon_subtype",state.weaponSubtype},
                        {"policy","current1031-cannonball-handcannon-gate-v1"},{"normal_costs_uncommitted",true}});
                    return;
                }
            }
            if(defaultZ&&(!sourceBaseDefaultSkillCommand(*row.data,plan_->identity.growtype)||out.actor.z>0)) {
                fail("experimental_default_z_ground_qualification","Default base source Z requires a grounded matching identity");return;
            }
            auto costData=*row.data;
            const auto femaleLevels=configuration_.femaleGunnerLevels();
            const int effectiveLevel=key.jobId==5?femaleGunnerEffectiveSkillLevel(key,binding->level,femaleLevels,*plan_):binding->level;
            const bool turningShoot=(key.jobId==2||key.jobId==5)&&key.skillId==20;
            const SkillKey headshotKey{key.jobId,5};
            if(turningShoot&&costData.values("[consume MP]").empty()) {
                const auto headshot=plan_->skills.find(headshotKey);
                if(headshot==plan_->skills.end()||!headshot->second.data)throw std::invalid_argument("TurningShoot requires current1031 HeadShot cost source");
                const auto selected=headshot->second.data->selected.find(normalize("[consume MP]"));
                if(selected==headshot->second.data->selected.end())throw std::invalid_argument("HeadShot source MP unavailable for TurningShoot inherited release");
                costData.selected[normalize("[consume MP]")]=selected->second;
            }
            const auto femaleCost=key.jobId==5?femaleGunnerCostModifiers(key,state.femaleGunnerBuffs,
                femaleLevels,*plan_,state.weaponSubtype):FemaleGunnerCostModifiers{};
            auto cost=fighterFreedom?SkillCostResult{}:evaluateCharacterSkillCosts(costData,effectiveLevel,plan_->characterDefinition,state.weaponSubtype,
                false,femaleCost.mp,femaleCost.cooldown,inferred1031SkillCostAbsencePolicy());
            if(turningShoot) {
                const auto head=femaleLevels.find(headshotKey);
                const auto *headBinding=configuration_.binding(headshotKey);
                const int headLevel=key.jobId==5?(head==femaleLevels.end()?1:std::max(1,head->second)):
                    headBinding?std::max(1,headBinding->level):1;
                const auto inherited=evaluateCharacterSkillCosts(*plan_->skills.at(headshotKey).data,headLevel,
                    plan_->characterDefinition,state.weaponSubtype,false,{}, {},inferred1031SkillCostAbsencePolicy());
                cost.mp=inherited.mp;
                cost.consumerDiagnostics.push_back({{"consumer","turning_shoot_current_headshot_mp"},{"headshot_level",headLevel},
                    {"source",plan_->skills.at(headshotKey).source.json()},{"classification","current1031-explain-with-inferred-consumption-chain"}});
            }
            lastCost_=cost.json();
            if(turningShoot)lastCost_["inferred_turning_shoot_mp_inheritance"]={{"source",plan_->skills.at(headshotKey).source.json()},
                {"basis","TurningShoot is the source HeadShot follow-up, source SKL omits consume MP; use referenced HeadShot source MP"},{"classification","inferred"}};
            if(!fighterFreedom&&(!cost.consumeMp()||!cost.cooldownMs()))throw std::invalid_argument("Source MP/CD evaluation blocked; inspect last_cost diagnostics");
            const int mp=(finisher||fighterFreedom)?0:*cost.consumeMp();double rawCd=(finisher||fighterFreedom)?0:*cost.cooldownMs();
            if(fighterFreedom)lastCost_["explicit_fighter40jp_test_freedom"]={{"mp",0},{"cooldown_ms",0},{"normal_ledger_unchanged",true}};
            if(transformed&&!finisher) {
                const auto table=twin->rawTables.at("static_data");const size_t column=key.skillId==3?2:key.skillId==6?3:4;
                if(column>=table.size()||!table[column].is_number())throw std::invalid_argument("Twin Gunblade source special cooldown missing");
                rawCd=table[column].get<double>();
                lastCost_["mode_special_cooldown"]={{"source",twin->skillSource.json()},{"static_column",column},{"milliseconds",rawCd},
                    {"classification","current1031-source-explain-with-inferred-special-cost-chain"},{"normal_skill_mp",mp}};
            }
            if(!std::isfinite(rawCd)||rawCd<0||rawCd>double(INT32_MAX))throw std::invalid_argument("Experimental cooldown exceeds supported simulation duration");
            const auto cd=int64_t(std::ceil(rawCd));
            if(out.actor.mp<mp){fail("experimental_insufficient_mp",row.name);return;}
            if(cd>INT64_MAX-int64_t(ms)){fail("experimental_cooldown_overflow",row.name);return;}
            if(defaultZ&&activeMotion_) {
                if(!requestOwner||requestOwner!=actionSequence_){fail("experimental_default_z_owner_replaced","The requested source action was replaced before queue admission");return;}
                bufferedDefaultSkill_=BufferedDefaultSkill{key,actionSequence_};
                out.diagnostics.push_back(issue("experimental_skill_buffered",UserRequestedSkillFeedbackV1::bufferPolicy));return;
            }
            if(actionSequence_==UINT64_MAX||skillAttemptSequence_==UINT64_MAX)
                throw std::overflow_error("Experimental skill event identity exhausted");
            std::optional<FemaleGunnerSkillCommand> femalePrepared;
            std::optional<SourceSkillOperands> sourcePrepared;
            if(binding->unknown.contains("source_nut_action_controller")||binding->unknown.contains("source_body_action_controller")) {
                const auto &descriptor=plan_->sourceSkillActions.at(key);
                if(descriptor.kind!=SourceSkillActionKind::BodyAttack&&(sourceEntities_.size()>=128||sourceEntitySequence_==UINT64_MAX))
                    throw std::length_error("Source NUT passive entity budget exhausted before skill admission");
                if(descriptor.movingImpact&&sourceEntitySequence_>=UINT64_MAX-1)
                    throw std::overflow_error("Moving source cannot allocate both flight and impact identities before admission");
                if(!binding->unknown.contains(descriptor.controllerKey())||binding->unknown.at(descriptor.controllerKey())!=descriptor.snapshot())
                    throw std::invalid_argument("Stale source NUT skill action binding");
                const int sourceState=out.actor.z>0?descriptor.jumpState:activeMotion_?descriptor.attackState:
                    running_?descriptor.dashState:descriptor.standState;
                if(!descriptor.executableStates.count(sourceState)) {
                    fail(descriptor.inferredNativeBody?"inferred_source_body_state_rejected":"source_nut_executable_state_rejected",
                        descriptor.inferredNativeBody?"Named inferred ground stand/dash admission rejects this actor state":"Current source SKL does not admit this actor state");return;
                }
                sourcePrepared=evaluateSourceSkillAction(descriptor,*row.data,effectiveLevel);
                if(key==SkillKey{2,4}) {
                    const SkillKey tp{key.jobId,168};const int tpLevel=configuration_.sourceActionPassiveLevel(tp);
                    if(tpLevel>0) {
                        const auto &passive=plan_->skills.at(tp);
                        if(!passive.data)throw std::invalid_argument("Configured source-action TP lost source data");
                        sourcePrepared=evaluateSourceSkillActionTp(descriptor,*row.data,effectiveLevel,tp,passive.source,*passive.data,tpLevel);
                    }
                }
            }
            std::vector<FemaleGunnerStage> overrideStages;
            std::vector<int> overrideColumns;
            auto releaseMotion=binding->motion;auto releaseAttack=binding->attack;
            if(binding->unknown.contains("female_gunner_source_controller")) {
                const auto descriptor=plan_->femaleGunnerSkills.find(key);
                if(descriptor==plan_->femaleGunnerSkills.end()||!descriptor->second.dedicatedRuntime)
                    throw std::invalid_argument("Female Gunner dedicated descriptor unavailable");
                femalePrepared=evaluateFemaleGunnerSkill(descriptor->second,*row.data,effectiveLevel,state.weaponSubtype);
                applyFemaleGunnerTpOperands(*femalePrepared,femaleLevels,*plan_,state.weaponSubtype);
                applyFemaleGunnerAmmoCapacity(*femalePrepared,femaleLevels,*plan_);
                femalePrepared->motionSource=binding->motion.source;
                if(binding->attack)femalePrepared->attackSource=binding->attack->source;
                femalePrepared->x=out.actor.x;femalePrepared->y=out.actor.y;femalePrepared->z=out.actor.z;femalePrepared->direction=out.actor.direction;
                femalePrepared->actionSequence=actionSequence_+1;
                if(femalePrepared->lifetimeMs==0&&
                    (femalePrepared->family=="ranged_guard"||femalePrepared->family=="backstep"||
                     femalePrepared->family=="timed_buff"||femalePrepared->family=="awakening_twingunblade")) {
                    const auto &descriptor=plan_->femaleGunnerSkills.at(key);
                    int64_t sourceDuration=0;
                    for(const auto &stage:descriptor.stages)if(const auto *motion=plan_->motion(stage.motionTag,stage.motionSlot))
                        sourceDuration+=plan_->animations.at(motion->source.memberPath)->duration;
                    femalePrepared->lifetimeMs=sourceDuration;
                    femalePrepared->evidence.push_back({{"policy","inferred-action-bound-source-duration-v1"},
                        {"classification","inferred"},{"duration_ms",sourceDuration},
                        {"basis","No persistent SKL duration; action-bound effect uses total selected source ANI duration"}});
                }
            }
            if(transformed) {
                overrideStages=transformedStages(key.skillId);
                if(key.skillId==3)overrideColumns={3,3};
                else if(key.skillId==6)overrideColumns={4,5};
                else if(key.skillId==7)overrideColumns={6};
                else overrideColumns={17,18,19};
                for(const auto &s:overrideStages) {
                    const auto *motion=plan_->motion(s.motionTag,s.motionSlot);
                    if(!motion)throw std::invalid_argument("Twin Gunblade alternate CHR motion missing");
                    checkedBinding(*motion,*plan_,false);
                    if(s.hasAttack){const auto *attack=plan_->attack(s.attackTag,s.attackSlot);
                        if(!attack)throw std::invalid_argument("Twin Gunblade alternate CHR ATK missing");checkedBinding(*attack,*plan_,true);}
                }
                const auto &first=overrideStages.front();releaseMotion=*plan_->motion(first.motionTag,first.motionSlot);
                releaseAttack=first.hasAttack?std::optional<ExperimentalSourceBinding>(*plan_->attack(first.attackTag,first.attackSlot)):std::nullopt;
                femalePrepared=*twin;femalePrepared->key=key;femalePrepared->skillSource=row.source;
                femalePrepared->family=key.skillId==3?"twingunblade_somersault":key.skillId==6?"twingunblade_chain_cut":
                    key.skillId==7?"twingunblade_spinning_blade":"twingunblade_finisher";
                femalePrepared->kind=key.skillId==7?FemaleGunnerCommandKind::Launch:FemaleGunnerCommandKind::Stage;
                femalePrepared->effectRole="transformed_mode_action";femalePrepared->motionSource=releaseMotion.source;
                femalePrepared->count=1;femalePrepared->intervalMs=0;femalePrepared->lifetimeMs=750;
                femalePrepared->speed=key.skillId==7?450:0;femalePrepared->range=900;femalePrepared->followCaster=false;
                femalePrepared->animationSource.reset();femalePrepared->attackSource.reset();femalePrepared->objectSource.reset();
                if(key.skillId==7)selectModeObject(*femalePrepared,"twingunbladegunhawk");
                else if(releaseAttack)femalePrepared->attackSource=releaseAttack->source;
                femalePrepared->evidence.push_back({{"policy","inferred-1031-twingunblade-alternate-actions-v1"},{"classification","inferred"},
                    {"mode_source",twin->skillSource.json()},{"requested_skill",key.json()},
                    {"basis","Source100 explain names Windmill3/UpperSpinningKick, Punisher6 and FastKnee7; repeated100 uses authored finisher actions"},
                    {"unverified_conditions",key.skillId==6?"Chain second input is reconstructed as an automatic second source stage; native followup window and pull distance remain unverified":
                        finisher?"Finisher level columns17/18/19 are inferred from the ordered source ATK; native rapid shot count remains unverified":
                        "Native projectile origin, gravity and perframe attack scheduling remain unverified"}});
                setStageDamage(*femalePrepared,0,overrideColumns);
            }
            // Same transactional source callback and commit point as ordinary
            // slot input: admission and deferred release share one consumer.
            auto nextCooldowns=cooldowns_;if(!finisher)nextCooldowns[key]=int64_t(ms)+cd;
            std::optional<FemaleGunnerStageTiming> timing;
            if(sourcePrepared) {
                const auto &descriptor=plan_->sourceSkillActions.at(key);
                if(!descriptor.nativeStages.empty()) {
                    const auto &first=descriptor.nativeStages.front();
                    // Preflight every stage and repetition operand before the
                    // cast transaction; failure never pays a partial MP/CD.
                    for(const auto &stage:descriptor.nativeStages) {
                        const auto *m=plan_->motion(stage.motionTag,size_t(stage.motionSlot));
                        if(!m||!plan_->animations.count(m->source.memberPath))throw std::invalid_argument("Fighter source stage motion unavailable");
                        int repeats=stage.repeat;
                        if(stage.repeatColumn>=0) {const auto n=skillLevelValue(row.data->values("[level info]"),effectiveLevel,stage.repeatColumn);
                            if(!n||*n<1||*n>128)throw std::invalid_argument("Fighter stage repeat level operand unavailable");repeats=int(*n);}
                        if(stage.repeatStatic>=0) {const auto values=row.data->values("[static data]");
                            if(size_t(stage.repeatStatic)>=values.size()||!values[stage.repeatStatic].is_number())throw std::invalid_argument("Fighter stage repeat static operand unavailable");
                            repeats=values[stage.repeatStatic].get<int>();}
                        if(repeats<1||repeats>128)throw std::invalid_argument("Fighter stage repeat exceeds bounded source count");
                    }
                    if(state.fighter40JpTestFreedom&&!first.runtimeDelays.empty()) {FemaleGunnerStageTiming t;t.controlled=true;t.runtimeDelays=first.runtimeDelays;timing=std::move(t);}
                }
            }
            if(sourcePrepared&&sourcePrepared->movingImpact) {
                FemaleGunnerStageTiming fixed;fixed.controlled=true;
                for(const auto &frame:plan_->animations.at(releaseMotion.source.memberPath)->frames)fixed.runtimeDelays.push_back(frame.duration);
                timing=std::move(fixed);
            }
            if(femalePrepared) {
                const auto &stages=overrideStages.empty()?plan_->femaleGunnerSkills.at(key).stages:overrideStages;
                for(size_t index=0;index<stages.size();++index) {
                    const auto &stage=stages[index];const auto *stageMotion=plan_->motion(stage.motionTag,stage.motionSlot);
                    if(!stageMotion)throw std::invalid_argument("Female Gunner source stage timing is unbound");
                    auto candidate=buildFemaleGunnerStageTiming(*femalePrepared,stage,*plan_->animations.at(stageMotion->source.memberPath));
                    if(!index){timing=std::move(candidate);applyFemaleGunnerStageTiming(*femalePrepared,*timing);}
                }
            }
            std::unique_ptr<PreparedExperimentalSkillAction> prepared;
            if(skillGate)prepared=skillGate({key,row.source,releaseMotion.source,fixedTick,actionSequence_+1,++skillAttemptSequence_});
            const auto sourceAttackSpeed=out.actor.attackPerMille+(sourcePrepared?sourcePrepared->attackSpeedBonusPermille:0);
            if(begin(releaseMotion,releaseAttack,key,completedBoundary?fixedTick:fixedTick-1,sourceAttackSpeed,timing?&*timing:nullptr)) {
                out.actor.mp-=mp;cooldowns_.swap(nextCooldowns);out.preparedSkillAction=std::move(prepared);
                if(sourcePrepared) {
                    SourceActionState sourceAction{key,*sourcePrepared,false};
                    sourceAction.ownerAction=actionSequence_;
                    sourceAction.recoveryPolicy=configuration_.sourceBodyRecoveryPolicy();
                    const auto &movement=plan_->sourceSkillActions.at(key).bodySidestep;
                    if(movement)sourceAction.sidestep=SourceBodySidestepState{out.actor.y,int(held_[3])-int(held_[2])};
                    sourceActions_.emplace(actionSequence_,std::move(sourceAction));
                    ExperimentalSourceVisual preflight;preflight.key=key;preflight.actionSequence=actionSequence_;
                    preflight.evidence=sourcePrepared->evidence;out.sourceSkillVisuals.push_back(std::move(preflight));
                    const auto &descriptor=plan_->sourceSkillActions.at(key);
                    if(!descriptor.castSound.empty())out.sounds.push_back(descriptor.castSound);
                    out.actor.vx=out.actor.vy=0;
                    out.diagnostics.push_back({{"code",descriptor.inferredNativeBody?"inferred_native_body_skill_started":"source_nut_action_started"},
                        {"source",descriptor.snapshot()},{"operands",sourcePrepared->evidence}});
                }
                femaleGunnerAction_=std::move(femalePrepared);femaleGunnerStage_=0;femaleGunnerRepeat_=0;femaleGunnerStageElapsedMs_=0;
                activeReleaseKey_=requestedReleaseKey_;
                femaleGunnerModeAttack_=femaleGunnerModeBlade_=false;
                femaleGunnerOverrideStages_=std::move(overrideStages);femaleGunnerOverrideDamageColumns_=std::move(overrideColumns);
                femaleGunnerFinishMode_=finisher;
                if(key==SkillKey{5,169}) {
                    const auto table=row.data->values("[static data]");
                    const double jump=!table.empty()&&table[0].is_number()?table[0].get<double>():sourceJumpPower()/2;
                    out.actor.z=1;out.actor.vz=jump;
                    out.diagnostics.push_back({{"policy","inferred-1031-backstep-short-jump-v1"},{"classification","inferred"},
                        {"initial_vertical_velocity",jump},{"backward_horizontal_speed",policy_.walkSpeed},
                        {"basis","Backstep source static first operand and CHR Jump ANI; horizontal speed reuses explicit experimental walk policy"}});
                }
                if(key==SkillKey{5,20}) {out.actor.direction*=-1;if(femaleGunnerAction_)femaleGunnerAction_->direction=out.actor.direction;}
                femaleGunnerEmissionPending_=femaleGunnerAction_&&(femaleGunnerOverrideStages_.empty()?plan_->femaleGunnerSkills.at(key).stages.front():femaleGunnerOverrideStages_.front()).emitCommand;
                if(femaleGunnerAction_) {auto preflight=*femaleGunnerAction_;preflight.preflightOnly=true;out.femaleGunnerCommands.push_back(std::move(preflight));}
                if(femaleGunnerAction_)if(auto stageVisual=femaleGunnerHeavyStageVisualReceipt(*femaleGunnerAction_,releaseMotion.source,0)) {
                    stageVisual->actionSequence=actionSequence_;out.femaleGunnerCommands.push_back(std::move(*stageVisual));
                }
                if(key==SkillKey{5,97})out.diagnostics.push_back({{"code","female_gunner_particle_charge_input_unverified"},
                    {"source",row.source.json()},{"current_branch","normal"},
                    {"message","Source rapid ATTACK full-charge input and Lv3/Lv6/Lv9 controller differences remain unimplemented; full visual resources are a separately preflightable candidate branch"}});
                out.diagnostics.push_back(issue(femaleGunnerAction_?"female_gunner_source_skill_started":"user_selected_skill_motion",
                    femaleGunnerAction_?"Dedicated source CHR stages and evaluated skill commands; native comparison remains pending":"Configured CHR ANI/ATK executes; native special mechanisms and SKL coefficient mapping remain incomplete"));
            } else fail("experimental_skill_motion_unavailable",row.name);
        }catch(const std::exception &error){fail("experimental_skill_source_blocked",error.what());}
    };
    if(!state.alive) {cancel(ControllerCancelReason::Death);out.state="dead";return out;}
    if(sourceBodyRecoveryRemainingMs_>0&&!state.blocked) {publishSourceBodyRecovery();return out;}
    if(channelRecoveryRemainingMs_>0&&!state.blocked) {publishChannelRecovery();return out;}
    if(state.blocked) {
        if(channelState_&&femaleGunnerAction_)
            out.femaleGunnerCommands.push_back(stopFemaleGunnerChannel(*femaleGunnerAction_,"actor_blocked"));
        channelContract_.reset();channelState_.reset();
        channelRecoveryRemainingMs_=0;sourceBodyRecoveryRemainingMs_=0;sourceActions_.clear();sourceRecoil_.reset();
        if(skillRequested_||defaultSkillRequested_)fail("experimental_actor_blocked","Current recovery/stun does not permit a skill request");
        activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();attackRequested_=jumpRequested_=comboQueued_=false;skillRequested_.reset();
        femaleGunnerBasicJumpStage_=-1;dashAttackGlide_.reset();gunnerGround_.reset();nativeJump_.reset();
        animationCursor_.reset();animationDelays_.reset();initialClockVisits_.clear();actionTiming_.reset();
        defaultSkillRequested_.reset();bufferedDefaultSkill_.reset();
        femaleGunnerAction_.reset();femaleGunnerStage_=0;femaleGunnerRepeat_=0;femaleGunnerEmissionPending_=false;
        femaleGunnerModeAttack_=femaleGunnerModeBlade_=false;
        femaleGunnerOverrideStages_.clear();femaleGunnerOverrideDamageColumns_.clear();femaleGunnerFinishMode_=false;
        out.actor.vx=out.actor.vy=0;
    } else if(!state.hitStopped) {
        if(channelState_&&channelContract_&&femaleGunnerAction_) {
            advanceFemaleGunnerChannel(*channelContract_,*channelState_,femaleGunnerStageElapsedMs_,
                channelContract_->mode==FemaleGunnerChannelInputMode::HoldReleaseKey?heldSkillKeys_.count(activeReleaseKey_)!=0:attackHeld_,
                attackEdge_,jumpEdge_);
            attackRequested_=comboQueued_=false;
            if(channelState_->stopped) {
                channelRecoveryRemainingMs_=femaleGunnerChannelRecoveryMs(*channelContract_,femaleGunnerStageElapsedMs_);
                out.femaleGunnerCommands.push_back(stopFemaleGunnerChannel(*femaleGunnerAction_,channelState_->reason));
                out.diagnostics.push_back({{"code","female_gunner_channel_stopped"},{"reason",channelState_->reason},
                    {"skill",femaleGunnerAction_->key.json()},{"elapsed_ms",femaleGunnerStageElapsedMs_}});
                femaleGunnerAction_.reset();femaleGunnerEmissionPending_=false;femaleGunnerStage_=0;femaleGunnerRepeat_=0;
                channelState_.reset();channelContract_.reset();jumpRequested_=false;
                out.actor.vx=out.actor.vy=0;
                if(channelRecoveryRemainingMs_>0){publishChannelRecovery();return out;}
                activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();animationCursor_.reset();
                animationDelays_.reset();initialClockVisits_.clear();actionTiming_.reset();
            }
        }
        attackEdge_=jumpEdge_=false;
        if(jumpRequested_)if(const auto mode=liveMode(15)) {
            endMode(*mode);if(femaleGunnerModeAttack_){activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();femaleGunnerAction_.reset();femaleGunnerModeAttack_=false;}
        }
        if(jumpRequested_&&out.actor.z==0&&!activeMotion_&&!nativeJump_){
            if(plan_->nativeJump)nativeJump_=NativeJumpState{};
            else {out.actor.vz=sourceJumpPower();out.actor.z=1;}
            if(plan_->identity.jobId==5)out.diagnostics.push_back({{"policy","inferred-1031-jump-power-as-initial-velocity-v1"},
                {"classification","inferred"},{"character_source",plan_->characterSource.json()},
                {"initial_velocity",out.actor.vz},{"leap_live",bool(liveMode(175))},
                {"basis","Current CHR jump-power mapped to initial velocity; live Leap explain20percent and static200 imply +200/1000. Original trajectory comparison remains pending"}});
        }
        jumpRequested_=false;
        if(skillRequested_) {
            const auto key=*skillRequested_;skillRequested_.reset();trySkill(key,false);
        }
        bool bladeRequested=false;
        if(defaultSkillRequested_&&liveMode(100)) {
            defaultSkillRequested_.reset();bladeRequested=true;femaleGunnerModeBlade_=true;
            if(activeMotion_&&femaleGunnerModeAttack_)comboQueued_=true;else attackRequested_=true;
        } else if(defaultSkillRequested_&&liveMode(15)) {defaultSkillRequested_.reset();out.actor.direction*=-1;}
        if(defaultSkillRequested_) {
            const auto requested=*defaultSkillRequested_;defaultSkillRequested_.reset();
            trySkill(requested.skill,true,requested.ownerActionSequence);
        }
        if(attackRequested_&&!activeMotion_) {
            const auto mode=liveMode(100)?liveMode(100):liveMode(15);
            if(mode) {
                const bool twin=mode->key.skillId==100;
                const bool blade=twin&&(bladeRequested||femaleGunnerModeBlade_);
                const size_t slot=twin?(blade?(out.actor.z>0?73:running_?72:68+combo_%4):(out.actor.z>0?85:running_?84:77+3*(combo_%2))):28+3*(combo_%2);
                const auto *motion=plan_->motion("[etc motion]",slot);
                const auto *attack=blade?plan_->attack("[etc attack info]",out.actor.z>0?16:running_?15:10+combo_%4):nullptr;
                if(!motion)throw std::logic_error("Female Gunner live mode lost its preloaded source motion");
                auto command=*mode;command.effectRole=blade?"mode_blade":"mode_shot";command.kind=blade?FemaleGunnerCommandKind::Stage:FemaleGunnerCommandKind::Launch;
                command.family=blade?"twingunblade_basic_blade":twin?"twingunblade_basic_shoot":"mobile_basic_shoot";
                command.lifetimeMs=750;command.intervalMs=0;command.count=1;command.speed=blade?0:1200;command.range=900;
                command.followCaster=false;command.preflightOnly=false;command.motionSource=motion->source;
                const int damageColumn=twin?(blade?10:13):0;
                const auto percent=skillLevelValue(mode->rawTables.at("level_info"),mode->level,damageColumn);
                if(!percent)throw std::logic_error("Female Gunner mode source damage operand unavailable");
                command.damage={};command.damage.replacesAttackCoefficients=true;command.damage.percent=float(*percent);
                if(!twin) {
                    const auto &bulletDescriptor=plan_->femaleGunnerSkills.at({5,5});const auto &bulletSource=*plan_->skills.at({5,5}).data;
                    const auto sourceBullet=evaluateFemaleGunnerSkill(bulletDescriptor,bulletSource,1,state.weaponSubtype);
                    command.objectSource=sourceBullet.objectSource;command.animationSource=sourceBullet.animationSource;command.attackSource=sourceBullet.attackSource;
                    command.rawTables["object_bindings"]=sourceBullet.rawTables.at("object_bindings");
                }else if(!blade)selectModeObject(command,out.actor.z>0?"twingunbladebulletjumpattack":running_?"twingunbladebulletdashattack":"twingunbladebulletattack");
                command.damage.sources.push_back({{"policy","inferred-1031-female-gunner-mode-input-v1"},{"source",mode->skillSource.json()},
                    {"base_level",mode->level},{"damage_column",damageColumn},{"motion_slot",slot},{"blade",blade},
                    {"basis","Source mode explain defines X shooting/Z blade; CHR preserves individual mode actions and ATK slots"},
                    {"unverified_conditions","Native gun offsets and individual blade combo multipliers require original comparison"}});
                if(begin(*motion,attack?std::optional<ExperimentalSourceBinding>(*attack):std::nullopt,mode->key,fixedTick-1,out.actor.attackPerMille)) {
                    attackRequested_=false;femaleGunnerModeAttack_=true;femaleGunnerModeBlade_=blade;
                    command.actionSequence=actionSequence_;command.x=out.actor.x;command.y=out.actor.y;command.z=out.actor.z;command.direction=out.actor.direction;
                    femaleGunnerAction_=command;femaleGunnerStage_=0;femaleGunnerRepeat_=0;femaleGunnerStageElapsedMs_=0;
                    femaleGunnerOverrideStages_.clear();femaleGunnerOverrideDamageColumns_.clear();femaleGunnerFinishMode_=false;
                    femaleGunnerEmissionPending_=!blade;
                }
            } else {
            const bool dashAttack=running_&&out.actor.z==0&&(held_[0]!=held_[1]);
            attackRequested_=false;combo_=0;const auto motionTag=out.actor.z>0?"[jumpattack motion]":dashAttack?"[dashattack motion]":"[attack motion]";
            const auto attackTag=out.actor.z>0?"[jumpattack info]":dashAttack?"[dashattack info]":"[attack info]";
            const bool femaleAir=plan_->identity.jobId==5&&out.actor.z>0;
            const auto *motion=femaleAir?femaleBasicJumpMotion(*plan_,0):plan_->motion(motionTag);
            const auto *attack=femaleAir?nullptr:plan_->attack(attackTag);
            try {
                bool stagesReady=true;
                if(femaleAir)for(int stage=0;stage<3;++stage) {
                    const auto *binding=femaleBasicJumpMotion(*plan_,stage);
                    if(!binding||!plan_->animations.count(binding->source.memberPath))stagesReady=false;
                }
                std::optional<BasicAttackGlide> preparedGlide;
                if(motion&&stagesReady&&dashAttack&&basicMovementPolicy_.enabled) {
                    const auto source=plan_->animations.at(motion->source.memberPath);
                    const auto span=basicAttackMovementClipMs(*source,out.actor.attackPerMille,animationClockPolicy_);
                    const int dx=int(held_[1])-int(held_[0]),dy=int(held_[3])-int(held_[2]);
                    const auto speed=policy_.runSpeed*out.actor.movePerMille/1000.0;
                    preparedGlide=BasicAttackGlide::begin(dx*speed*out.actor.dashXRatio,
                        dy*speed*policy_.verticalRatio*out.actor.dashYRatio,span,basicMovementPolicy_);
                    out.diagnostics.push_back({{"code","basic_dash_glide_started"},{"motion",motion->source.json()},
                        {"movement_policy",basicMovementPolicy_.json()},{"source_span_ms",span},{"glide",preparedGlide->json()}});
                }
                const bool maleGround=plan_->identity.jobId==2&&out.actor.z==0&&!dashAttack;
                if(maleGround) {
                    // Preflight the complete finite phase set before publishing initial raise.
                    for(int phase=0;phase<5;++phase) {
                        const auto *part=phase==0?plan_->motion("[attack motion]",0):phase==2?plan_->motion("[attack motion]",1):
                            plan_->motion("[etc motion]",phase==1?0:phase==3?2:4);
                        if(!part||!plan_->animations.count(part->source.memberPath))throw std::invalid_argument("Source Gunner phase set incomplete");
                    }
                    beginGunnerGroundPhase(0,state.weaponSubtype,fixedTick-1,out.actor.attackPerMille,
                        held_[3]||(!state.gunnerAimTarget.is_null()&&state.gunnerAimTarget.value("prefer_down",false)));
                    out.diagnostics.push_back({{"code","gunner_source_five_phase_started"},{"classification","inferred_host"},
                        {"source",plan_->gunnerBasicSources.at(state.weaponSubtype).snapshot()},
                        {"basis","1031 source Raise/Shoot/final Raise/final Shoot/Reload; default GunInfo scheduledShot consumer"}});
                } else if(!motion||!stagesReady||!begin(*motion,attack?std::optional<ExperimentalSourceBinding>(*attack):std::nullopt,std::nullopt,
                    fixedTick-1,out.actor.attackPerMille))out.diagnostics.push_back(issue("missing_source_attack_motion",motionTag));
                else if(dashAttack&&basicMovementPolicy_.enabled) {
                    const int dx=int(held_[1])-int(held_[0]),dy=int(held_[3])-int(held_[2]);
                    (void)dy;dashAttackGlide_.swap(preparedGlide);
                    out.actor.direction=dx;
                }
                else if(femaleAir) {
                    femaleGunnerBasicJumpStage_=0;
                    out.diagnostics.push_back({{"code","female_gunner_source_jump_stages"},{"classification","inferred"},
                        {"character_source",plan_->characterSource.json()},{"source_slots",{5,6,8}},{"duplicate_shoot_slot_preserved",7},
                        {"basis","Current CHR separately binds JumpAttackReady, JumpAttackShoot and JumpAttackEnd. Consume those finite stages in order; only shoot emits a projectile"},
                        {"native_stage_setter_verified",false}});
                }
            } catch(const std::exception &error) {out.diagnostics.push_back(issue("experimental_attack_clock_blocked",error.what()));}
            if(activeMotion_){running_=false;lastLeft_=lastRight_=-100000;}
            }
        }
        if(!activeMotion_) {
            const int dx=int(held_[1])-int(held_[0]),dy=int(held_[3])-int(held_[2]);if(!dx)running_=false;
            const double speed=(running_?policy_.runSpeed:policy_.walkSpeed)*out.actor.movePerMille/1000.0;
            out.actor.vx=dx*speed*(running_?out.actor.dashXRatio:1);
            out.actor.vy=dy*speed*policy_.verticalRatio*(running_?out.actor.dashYRatio:1);
            const double x=out.actor.x+out.actor.vx*dt/1000.0,y=out.actor.y+out.actor.vy*dt/1000.0;
            if(canWalk(x,out.actor.y))out.actor.x=x;if(canWalk(out.actor.x,y))out.actor.y=y;if(dx)out.actor.direction=dx;
        } else {
            out.actor.vx=out.actor.vy=0;
            if(femaleGunnerAction_) {
                const auto &command=*femaleGunnerAction_;const int dx=int(held_[1])-int(held_[0]),dy=int(held_[3])-int(held_[2]);
                if(command.family=="backstep")out.actor.vx=-out.actor.direction*policy_.walkSpeed;
                else if(command.family=="moving_melee"||command.family=="moving_melee_burn") {
                    const auto &table=command.rawTables.at("level_info");
                    out.actor.vx=double(dx?dx:out.actor.direction)*skillLevelValue(table,command.level,0).value_or(0);
                    out.actor.vy=dy*skillLevelValue(table,command.level,1).value_or(0);
                } else if(command.family=="mobile_basic_shoot"||command.family=="twingunblade_basic_shoot") {
                    out.actor.vx=dx*policy_.walkSpeed*out.actor.movePerMille/1000.0;
                    out.actor.vy=dy*policy_.walkSpeed*policy_.verticalRatio*out.actor.movePerMille/1000.0;
                } else if(channelState_&&channelContract_&&channelContract_->mode==FemaleGunnerChannelInputMode::HoldReleaseKey) {
                    std::optional<double> ratio;
                    for(const auto &parameter:command.parameters)if(parameter.at("label").get<std::string>().find("喷射时移动速度比率")!=std::string::npos) {
                        if(ratio)throw std::invalid_argument("Ambiguous source spraying movement ratio");ratio=parameter.at("value").get<double>()/100.0;
                    }
                    if(!ratio||!std::isfinite(*ratio)||*ratio<0)throw std::invalid_argument("Source spraying movement ratio unavailable");
                    const auto speed=policy_.walkSpeed*out.actor.movePerMille/1000.0* *ratio;
                    out.actor.vx=dx*speed;out.actor.vy=dy*speed*policy_.verticalRatio;
                }
                const auto x=out.actor.x+out.actor.vx*dt/1000.0,y=out.actor.y+out.actor.vy*dt/1000.0;
                if(canWalk(x,out.actor.y))out.actor.x=x;else out.actor.vx=0;
                if(canWalk(out.actor.x,y))out.actor.y=y;else out.actor.vy=0;
            } else if(!activeSkill_&&basicMovementPolicy_.enabled&&out.actor.z>0&&
                (femaleGunnerBasicJumpStage_>=0||normalize(activeMotion_->tag)=="[jumpattack motion]")) {
                const int dx=int(held_[1])-int(held_[0]),dy=int(held_[3])-int(held_[2]);
                const auto speed=policy_.walkSpeed*out.actor.movePerMille/1000.0;
                out.actor.vx=dx*speed;out.actor.vy=dy*speed*policy_.verticalRatio;
                const auto x=out.actor.x+out.actor.vx*dt/1000.0,y=out.actor.y+out.actor.vy*dt/1000.0;
                if(canWalk(x,out.actor.y))out.actor.x=x;else out.actor.vx=0;
                if(canWalk(out.actor.x,y))out.actor.y=y;else out.actor.vy=0;
            } else if(!activeSkill_&&dashAttackGlide_&&normalize(activeMotion_->tag)=="[dashattack motion]") {
                const auto movement=dashAttackGlide_->advance(int32_t(dt));
                if(canWalk(out.actor.x+movement[0],out.actor.y))out.actor.x+=movement[0];else dashAttackGlide_->blockX();
                if(canWalk(out.actor.x,out.actor.y+movement[1]))out.actor.y+=movement[1];else dashAttackGlide_->blockY();
                out.actor.vx=dashAttackGlide_->x.velocity;out.actor.vy=dashAttackGlide_->y.velocity;
            }
        }
    }
    if(!state.hitStopped&&!state.blocked&&state.alive) {
        const auto owner=sourceActions_.find(actionSequence_);
        if(owner!=sourceActions_.end()) {
            const auto &descriptor=plan_->sourceSkillActions.at(owner->second.key);
            if(!descriptor.nativeStages.empty()) {
                const auto &stage=descriptor.nativeStages.at(owner->second.nativeStage);
                if(!owner->second.movementStarted&&stage.movementStartMs>=0&&owner->second.unpausedMs+dt>=stage.movementStartMs) {
                    const auto &data=*plan_->skills.at(owner->second.key).data;const auto values=data.values("[static data]");
                    const auto operand=[&](int column,double fallback)->double {
                        if(column<0)return fallback;
                        if(size_t(column)>=values.size()||!values[column].is_number())throw std::invalid_argument("Fighter source axis operand unavailable");
                        return values[column].get<double>();
                    };
                    const double speed=operand(stage.speedStatic,stage.speed),accel=operand(stage.accelerationStatic,stage.acceleration);
                    if(!std::isfinite(speed)||!std::isfinite(accel)||std::abs(speed)>10000||std::abs(accel)>100000)
                        throw std::invalid_argument("Fighter source axis payload out of range");
                    const int duration=accel!=0&&speed*accel<0?int(std::ceil(std::abs(speed/accel)*1000)):-1;
                    sourceRecoil_=AxisMotion{float(speed*out.actor.direction),int32_t(accel*out.actor.direction),duration};
                    owner->second.movementStarted=true;
                    out.diagnostics.push_back({{"code","fighter40jp_native_axis_started"},{"skill",owner->second.key.json()},
                        {"stage",owner->second.nativeStage},{"speed",speed},{"acceleration",accel},{"start_ms",stage.movementStartMs}});
                }
            }
        }
    }
    if(sourceRecoil_&&!state.hitStopped&&!state.blocked&&state.alive) {
        const auto displacement=advanceAxisMotion(*sourceRecoil_,int32_t(dt));
        if(canWalk(out.actor.x+displacement,out.actor.y))out.actor.x+=displacement;
        else {sourceRecoil_.reset();out.actor.vx=0;}
        if(sourceRecoil_) {out.actor.vx=sourceRecoil_->velocity;
            if(sourceRecoil_->accelerationRemainingMs==0) {sourceRecoil_.reset();out.actor.vx=0;}}
    }
    if(nativeJump_&&!state.hitStopped&&!state.blocked&&nativeJump_->phase==0) {
        nativeJump_->ageMs+=dt;const auto &clip=*plan_->animations.at(plan_->motion("[jump motion]")->source.memberPath);
        int64_t ready=0;for(size_t i=0;i<plan_->nativeJump->takeoff;++i)ready+=clip.frames[i].duration;
        if(nativeJump_->ageMs>=ready) {
            nativeJump_->phase=1;nativeJump_->ageMs=0;out.actor.vz=sourceJumpPower();out.actor.z=1;
            out.sounds.push_back("JUMP_START");out.diagnostics.push_back({{"code","fighter40jp_jump_takeoff"},{"source",plan_->nativeJump->evidence}});
        }
    }
    const bool wasAirborne=out.actor.z>0;
    if(!state.hitStopped&&(out.actor.z>0||out.actor.vz>0)) {
        AxisMotion vertical{float(out.actor.vz),-int32_t(policy_.gravity),-1};
        out.actor.z+=advanceAxisMotion(vertical,int32_t(dt));out.actor.vz=vertical.velocity;
        if(out.actor.z<=0)out.actor.z=out.actor.vz=0;
    }
    if(nativeJump_&&!state.hitStopped&&!state.blocked) {
        if(nativeJump_->phase==1&&out.actor.vz<=0&&out.actor.z>0){nativeJump_->phase=2;nativeJump_->ageMs=0;}
        else if(nativeJump_->phase>0)nativeJump_->ageMs+=dt;
        if(wasAirborne&&out.actor.z==0) {
            nativeJump_->phase=3;nativeJump_->ageMs=0;out.sounds.push_back("JUMP_END");
            if(activeMotion_&&!activeSkill_&&normalize(activeMotion_->tag)=="[jumpattack motion]") {
                activeMotion_.reset();activeAttack_.reset();animationCursor_.reset();animationDelays_.reset();initialClockVisits_.clear();actionTiming_.reset();
            }
        }
        if(nativeJump_->phase==3) {
            const auto &clip=*plan_->animations.at(plan_->motion("[jump motion]")->source.memberPath);
            int64_t tail=0;for(size_t i=plan_->nativeJump->landing;i<clip.frames.size();++i)tail+=clip.frames[i].duration;
            if(nativeJump_->ageMs>=tail)nativeJump_.reset();
        }
    }
    // Jump is a finite source clip whose age belongs to this jump, not the
    // global simulation clock. The same borrowed snapshot drives equipment.
    if(out.actor.z>0) {
        if(const auto *jump=plan_->motion("[jump motion]")) {
            if(!jumpLocomotion_) {
                jumpLocomotion_.emplace();
                jumpLocomotion_->install(*plan_->animations.at(jump->source.memberPath),false,100,
                    ani_clock::ClockPolicy::SourceDelay100,fixedTick);
            } else if(jumpLocomotion_->snapshot().lastTick<fixedTick)
                jumpLocomotion_->advance(fixedTick,state.hitStopped);
        }
    } else jumpLocomotion_.reset();
    if(femaleGunnerBasicJumpStage_>=0&&!state.hitStopped&&out.actor.z==0) {
        // Landing cancels pending aerial shots; a ready pose must never fire
        // later from the ground. Source clips and their loop flags stay intact.
        femaleGunnerBasicJumpStage_=-1;activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();
        animationCursor_.reset();animationDelays_.reset();initialClockVisits_.clear();actionTiming_.reset();
        comboQueued_=attackRequested_=false;
    }
    const auto emitFemaleGunnerCommand=[&]() {
        if(!femaleGunnerAction_||!femaleGunnerEmissionPending_)return;
        femaleGunnerAction_->actionSequence=actionSequence_;
        auto command=*femaleGunnerAction_;command.preflightOnly=false;command.stage=femaleGunnerStage_;
        command.actionSequence=actionSequence_;command.pulseId=uint64_t(femaleGunnerRepeat_);
        command.x=out.actor.x;command.y=out.actor.y;command.z=out.actor.z;command.direction=out.actor.direction;
        command.motionSource=activeMotion_->source;
        if(activeAttack_)command.attackSource=activeAttack_->source;
        out.femaleGunnerCommands.push_back(std::move(command));femaleGunnerEmissionPending_=false;
    };
    if(!state.hitStopped&&!state.blocked)emitFemaleGunnerCommand();
    const auto fighterBasicSound=[&]() {
        if(plan_->identity.jobId!=1||activeSkill_||!activeMotion_)return;
        const auto tag=normalize(activeMotion_->tag);
        if(tag=="[jumpattack motion]"){out.sounds.push_back("JUMP_KICK");out.sounds.push_back("R_FT_KICK_JUMP");}
        else if(tag=="[attack motion]"&&combo_==3){out.sounds.push_back("R_FT_KICK_AX");out.sounds.push_back("KICK_AX");}
        else if(tag=="[attack motion]"||tag=="[dashattack motion]")out.sounds.push_back("R_FT_ATK");
    };
    const auto publishClockAction=[&]() {
        const auto animation=plan_->animations.at(activeMotion_->source.memberPath);
        const bool paused=state.hitStopped||state.blocked;
        if(!paused&&animationCursor_->snapshot().policy==ani_clock::ClockPolicy::Inferred60UsPercentDeadlines) {
            const auto speed=animationSpeedStat(sourceActionAttackSpeed());
            if(speed!=animationSpeedStat_) {
                animationCursor_->setRate(ani_clock::resolveRate(speed,ani_clock::RatePath::Refresh));
                animationSpeedStat_=speed;
            }
        }
        const auto before=animationCursor_->snapshot();
        ani_clock::Advance advanced;
        if(before.lastTick<fixedTick)advanced=animationCursor_->advance({fixedTick,dt,paused});
        else if(before.lastTick!=fixedTick)throw std::logic_error("Experimental ANI clock advanced beyond its owner tick");
        const auto current=animationCursor_->snapshot();
        age_=double(current.elapsedMs);lastFrame_=int(current.frame);
        out.animationPath=activeMotion_->source.memberPath;out.animationAgeMs=age_;out.poseFrame=-1;
        out.animationClock=current;out.state="experimental_attack";
        if(activeSkill_&&activeSkill_->jobId==5) {
            const auto skillLayers=plan_->femaleGunnerSkillLayers.find(*activeSkill_);
            if(skillLayers!=plan_->femaleGunnerSkillLayers.end()) {
                const auto layers=skillLayers->second.find(activeMotion_->source.memberPath);
                if(layers!=skillLayers->second.end())out.skillAnimationLayers=layers->second;
            }
        }
        out.animationControllerDelays=animationDelays_;
        if(paused)return;
        size_t lastSample=out.attacks.size();
        const auto emit=[&](size_t frame,ani_clock::Snapshot sample) {
            sample.lastTick=fixedTick;
            if(lastSample<out.attacks.size()&&out.attacks[lastSample].sourceFrame==frame) {
                out.attacks[lastSample].animationClock=sample;return;
            }
            ExperimentalAttackFrame attack;attack.actionSequence=actionSequence_;attack.sourceFrame=frame;
            attack.animationControllerDelays=animationDelays_;
            attack.animationClock=sample;attack.skill=activeSkill_;attack.motion=*activeMotion_;attack.attack=activeAttack_;
            for(const auto &box:animation->frames.at(frame).boxes)if(box.type==15)attack.boxes.push_back(box);
            out.attacks.push_back(std::move(attack));lastSample=out.attacks.size()-1;
        };
        const auto visit=[&](const ani_clock::FrameVisit &entry) {
            if(entry.frame==0&&entry.loopCount==0&&entry.startMs==0)fighterBasicSound();
            auto sample=current;sample.frame=entry.frame;
            sample.nextFrame=entry.frame+1<animation->frames.size()?entry.frame+1:entry.frame;
            sample.elapsedMs=sample.frameStartMs=entry.startMs;sample.nextDeadlineMs=entry.deadlineMs;
            sample.localMs=0;sample.spanMs=entry.deadlineMs-entry.startMs;sample.visit=entry.visit;
            sample.loopCount=entry.loopCount;sample.ended=false;
            emit(entry.frame,sample);
            const auto &properties=animation->frames.at(entry.frame).properties;
            if(properties.contains("16")) {
                const auto &sound=properties.at("16");
                if(sound.is_string()&&!sound.get<std::string>().empty())out.sounds.push_back(sound.get<std::string>());
            }
        };
        // A held interval still accepts a newly entering target. New frame
        // visits, including zero-delay prefixes, emit their source sounds once.
        if(initialClockVisits_.empty()) {if(!before.ended)emit(before.frame,before);}
        else for(const auto &entry:initialClockVisits_)visit(entry);
        initialClockVisits_.clear();
        for(const auto &entry:advanced.visits)visit(entry);
        if(lastSample<out.attacks.size())emit(current.frame,current);
    };
    if(activeMotion_) {
        const auto source=sourceActions_.find(actionSequence_);
        if(source!=sourceActions_.end()&&!state.hitStopped&&!state.blocked)source->second.unpausedMs+=dt;
        const auto selected=*activeMotion_;const auto animation=plan_->animations.at(selected.source.memberPath);
        const auto firstAttack=out.attacks.size();
        if(animationCursor_)publishClockAction();
        else {
        const double previousAge=lastFrame_<0?-1:age_;
        if(previousAge<0&&!state.hitStopped&&!state.blocked)fighterBasicSound();
        if(!state.hitStopped&&!state.blocked)age_+=dt*sourceActionAttackSpeed()/1000.0;
        const int frame=int(animation->frameAt(int64_t(age_),false));
        double elapsed=0;
        if(!state.hitStopped&&!state.blocked)for(size_t index=0;index<animation->frames.size();++index) {
            const auto end=elapsed+animation->frames[index].duration;
            const bool overlaps=age_>=elapsed&&previousAge<end;elapsed=end;
            if(!overlaps)continue;
            ExperimentalAttackFrame attack;attack.actionSequence=actionSequence_;attack.sourceFrame=size_t(index);attack.skill=activeSkill_;
            attack.motion=selected;attack.attack=activeAttack_;
            if(int(index)>lastFrame_&&animation->frames[index].properties.contains("16")) {
                const auto &sound=animation->frames[index].properties["16"];
                if(sound.is_string()&&!sound.get<std::string>().empty())out.sounds.push_back(sound.get<std::string>());
            }
            for(const auto &box:animation->frames.at(size_t(index)).boxes)if(box.type==15)attack.boxes.push_back(box);
            // Include empty body frames: the common Swordman reader also
            // consumes exact equipped weapon layers. Active intervals repeat
            // until they end; the World keeps one accepted hit per swing/target.
            out.attacks.push_back(std::move(attack));
        }
        lastFrame_=frame;out.animationPath=selected.source.memberPath;out.animationAgeMs=age_;out.poseFrame=frame;out.state="experimental_attack";
        if(activeSkill_&&activeSkill_->jobId==5) {
            const auto skillLayers=plan_->femaleGunnerSkillLayers.find(*activeSkill_);
            if(skillLayers!=plan_->femaleGunnerSkillLayers.end()) {
                const auto layers=skillLayers->second.find(selected.source.memberPath);
                if(layers!=skillLayers->second.end())out.skillAnimationLayers=layers->second;
            }
        }
        }
        // Body-local source progress drives the out/return trajectory under
        // both clocks. Hitstop pauses it; actor/source cancel owns its lifetime.
        if(source!=sourceActions_.end()&&source->second.sidestep&&!state.hitStopped&&!state.blocked) {
            const auto &movement=*plan_->sourceSkillActions.at(source->second.key).bodySidestep;
            const auto progress=animationCursor_?sourceBodyElapsedMs(*animation,animationCursor_->snapshot()):age_;
            const auto beforeY=out.actor.y;
            out.actor.y=advanceSourceBodySidestep(movement,*source->second.sidestep,progress,out.actor.x,out.actor.y,canWalk);
            out.actor.vy=(out.actor.y-beforeY)*1000.0/dt;
        }
        if(gunnerGround_) {
            if(!state.hitStopped&&!state.blocked)gunnerGround_->elapsed+=dt;
            for(size_t i=firstAttack;i<out.attacks.size();++i) {
                out.attacks[i].sourceFamily="gunner_ground_pose";out.attacks[i].suppressBodyDamage=true;
            }
            if(!state.hitStopped&&!state.blocked&&(gunnerGround_->phase==1||gunnerGround_->phase==3)&&
                !gunnerGround_->emitted&&gunnerGround_->elapsed>=gunnerGround_->deadlines.shot) {
                if(firstAttack==out.attacks.size())throw std::logic_error("Source Gunner shot has no body pose");
                auto &frame=out.attacks.back();frame.gunnerScheduledShot=true;frame.sourceFamily="gunner_ground_shoot";
                frame.gunnerDownShot=gunnerGround_->down;
                gunnerGround_->emitted=true;++gunnerGround_->shots;
            }
        }
        if(femaleGunnerBasicJumpStage_>=0)for(size_t i=firstAttack;i<out.attacks.size();++i)
            out.attacks[i].sourceFamily=femaleGunnerBasicJumpStage_==1?"female_gunner_basic_jump_shoot":"female_gunner_basic_jump_pose";
        if(femaleGunnerAction_)for(size_t i=firstAttack;i<out.attacks.size();++i) {
            out.attacks[i].sourceFamily=femaleGunnerAction_->family;
            auto frozen=*femaleGunnerAction_;frozen.preflightOnly=false;
            frozen.actionSequence=out.attacks[i].actionSequence;frozen.stage=femaleGunnerStage_;frozen.pulseId=uint64_t(femaleGunnerRepeat_);
            frozen.x=out.actor.x;frozen.y=out.actor.y;frozen.z=out.actor.z;frozen.direction=out.actor.direction;
            frozen.motionSource=out.attacks[i].motion.source;
            if(out.attacks[i].attack)frozen.attackSource=out.attacks[i].attack->source;
            out.attacks[i].femaleGunnerCommand=std::move(frozen);
            out.attacks[i].skillModifiers=femaleGunnerAction_->damage;
            out.attacks[i].pulseId=uint32_t(femaleGunnerRepeat_);
        }
        if(femaleGunnerAction_&&!state.hitStopped&&!state.blocked)femaleGunnerStageElapsedMs_+=dt;
        bool ended=animationCursor_?animationCursor_->snapshot().ended:age_>=animation->duration;
        // Controller completion is distinct from ANI DELAY. In the current
        // 1031 Gunner proc (C1199C..C11A4B), raise phases advance on entering
        // the final frame, whose 9999/10000ms delay is a held pose. Preserve
        // the source clip and clock; release the experimental ordinary action
        // at that boundary instead of locking input for the entire hold.
        const bool ordinary=!activeSkill_&&!femaleGunnerAction_&&!gunnerGround_;
        if(gunnerGround_) {
            const auto &ground=*gunnerGround_;
            if(ground.phase==0||ground.phase==2)ended=lastFrame_==int(animation->frames.size()-1);
            else if(ground.phase==1||ground.phase==3)ended=ground.elapsed>=ground.deadlines.recovery;
        }
        const bool gunnerRaise=ordinary&&(plan_->identity.jobId==2||plan_->identity.jobId==5)&&
            normalize(selected.tag)=="[attack motion]"&&animation->frames.size()>1;
        if(gunnerRaise&&animation->frames.back().duration>=9999&&lastFrame_==int(animation->frames.size()-1))ended=true;
        // Other jobs already carry their own native/source cancel tables.
        // Consume those tables only for queued grounded ordinary combos, as
        // Swordman's controller does; an unqueued finite recovery stays intact.
        const auto &cancelFrames=plan_->characterDefinition.basicAttackCancelFrames;
        const bool chainReady=ordinary&&comboQueued_&&out.actor.z==0&&normalize(selected.tag)=="[attack motion]"&&
            combo_<cancelFrames.size()&&lastFrame_>=cancelFrames[combo_]&&
            plan_->motion("[attack motion]",combo_+1,selected.occurrence);
        if(chainReady)ended=true;
        if(femaleGunnerAction_&&!femaleGunnerModeAttack_) {
            const auto &stages=femaleGunnerOverrideStages_.empty()?plan_->femaleGunnerSkills.at(femaleGunnerAction_->key).stages:femaleGunnerOverrideStages_;
            const auto &stage=stages.at(femaleGunnerStage_);
            if(actionTiming_)ended=femaleGunnerStageTimingComplete(*actionTiming_,femaleGunnerStageElapsedMs_,ended);
            else if(stage.holdForCommandLifetime&&femaleGunnerAction_->lifetimeMs>femaleGunnerStageElapsedMs_)ended=false;
        }
        if(!state.hitStopped&&!state.blocked&&gunnerGround_) {
            const auto ground=*gunnerGround_;
            int next=-1;
            if(ground.phase==0&&ended)next=plan_->gunnerBasicSources.at(ground.subtype).values[0]==1?3:1;
            else if(ground.phase==2&&ended)next=3;
            else if(ground.phase==1&&ground.emitted&&comboQueued_&&ground.elapsed>=ground.deadlines.continuation) {
                comboQueued_=false;
                const auto maximum=plan_->gunnerBasicSources.at(ground.subtype).values[0];
                next=ground.shots>=uint32_t(maximum-1)?2:1;
            } else if(ground.phase==3&&ended)next=4;
            if(next>=0) {
                beginGunnerGroundPhase(next,ground.subtype,fixedTick,out.actor.attackPerMille,
                    held_[3]||(!state.gunnerAimTarget.is_null()&&state.gunnerAimTarget.value("prefer_down",false)));
                return out;
            }
            if(ended)gunnerGround_.reset();
        }
        if(!state.hitStopped&&!state.blocked&&ended) {
            if(femaleGunnerBasicJumpStage_>=0) {
                const auto nextStage=femaleGunnerBasicJumpStage_+1;
                if(nextStage<3&&out.actor.z>0) {
                    const auto *next=femaleBasicJumpMotion(*plan_,nextStage);
                    const auto *attack=nextStage==1?plan_->attack("[jumpattack info]"):nullptr;
                    if(!next||!begin(*next,attack?std::optional<ExperimentalSourceBinding>(*attack):std::nullopt,std::nullopt,
                        fixedTick,out.actor.attackPerMille))throw std::logic_error("Preflighted female jump stage disappeared");
                    femaleGunnerBasicJumpStage_=nextStage;return out;
                }
                femaleGunnerBasicJumpStage_=-1;comboQueued_=false;
            }
            if(channelState_&&channelContract_&&femaleGunnerAction_) {
                channelRecoveryRemainingMs_=femaleGunnerChannelRecoveryMs(*channelContract_,femaleGunnerStageElapsedMs_);
                out.femaleGunnerCommands.push_back(stopFemaleGunnerChannel(*femaleGunnerAction_,"source_maximum"));
                femaleGunnerAction_.reset();femaleGunnerEmissionPending_=false;femaleGunnerStage_=0;femaleGunnerRepeat_=0;
                channelState_.reset();channelContract_.reset();attackRequested_=comboQueued_=false;
                if(channelRecoveryRemainingMs_>0){publishChannelRecovery();return out;}
            }
            if(femaleGunnerAction_&&!femaleGunnerModeAttack_) {
                const auto &descriptor=plan_->femaleGunnerSkills.at(femaleGunnerAction_->key);
                const auto &stages=femaleGunnerOverrideStages_.empty()?descriptor.stages:femaleGunnerOverrideStages_;
                const auto &currentStage=stages.at(femaleGunnerStage_);
                int repetitions=currentStage.repeat;
                if(femaleGunnerOverrideStages_.empty()&&descriptor.family=="melee_multihit"&&femaleGunnerStage_==0)repetitions=int(std::max<uint32_t>(1,femaleGunnerAction_->count));
                const bool repeat=femaleGunnerRepeat_+1<repetitions;
                const auto nextIndex=repeat?femaleGunnerStage_:femaleGunnerStage_+1;
                if(nextIndex<stages.size()) {
                    const auto &nextStage=stages.at(nextIndex);
                    const auto *motion=plan_->motion(nextStage.motionTag,nextStage.motionSlot);
                    const auto *attack=nextStage.hasAttack?plan_->attack(nextStage.attackTag,nextStage.attackSlot):nullptr;
                    if(!motion)throw std::logic_error("Preflighted female Gunner stage lost source motion");
                    const auto key=femaleGunnerAction_->key;
                    auto nextTiming=buildFemaleGunnerStageTiming(*femaleGunnerAction_,nextStage,*plan_->animations.at(motion->source.memberPath));
                    applyFemaleGunnerStageTiming(*femaleGunnerAction_,nextTiming);
                    if(!begin(*motion,attack?std::optional<ExperimentalSourceBinding>(*attack):std::nullopt,key,fixedTick,out.actor.attackPerMille,&nextTiming))
                        throw std::logic_error("Preflighted female Gunner stage could not start");
                    femaleGunnerRepeat_=repeat?femaleGunnerRepeat_+1:0;femaleGunnerStage_=nextIndex;femaleGunnerStageElapsedMs_=0;
                    channelContract_.reset();channelState_.reset();
                    if(nextStage.holdForCommandLifetime) {
                        auto contract=femaleGunnerChannelContract(*femaleGunnerAction_);
                        for(const auto &diagnostic:contract.diagnostics)out.diagnostics.push_back(diagnostic);
                        if(contract.mode!=FemaleGunnerChannelInputMode::None) {
                            channelState_=beginFemaleGunnerChannel(contract);channelContract_=std::move(contract);
                        }
                    }
                    setStageDamage(*femaleGunnerAction_,nextIndex,femaleGunnerOverrideDamageColumns_);
                    if(channelContract_&&channelContract_->mode==FemaleGunnerChannelInputMode::HoldReleaseKey&&
                       !heldSkillKeys_.count(activeReleaseKey_)) {
                        out.diagnostics.push_back({{"code","female_gunner_release_key_before_spray"},{"skill",key.json()},
                            {"release_key",activeReleaseKey_},{"damage_emission",false}});
                        femaleGunnerAction_.reset();femaleGunnerEmissionPending_=false;femaleGunnerStage_=0;femaleGunnerRepeat_=0;
                        channelState_.reset();channelContract_.reset();activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();
                        animationCursor_.reset();animationDelays_.reset();initialClockVisits_.clear();actionTiming_.reset();return out;
                    }
                    if(auto stageVisual=femaleGunnerHeavyStageVisualReceipt(*femaleGunnerAction_,motion->source,nextIndex)) {
                        stageVisual->actionSequence=actionSequence_;out.femaleGunnerCommands.push_back(std::move(*stageVisual));
                    }
                    femaleGunnerEmissionPending_=nextStage.emitCommand;
                    emitFemaleGunnerCommand();
                    // The preceding final pose remains visible for this tick;
                    // next tick visits the new source stage without extra dt.
                    return out;
                }
                if(femaleGunnerFinishMode_)if(const auto mode=liveMode(100))endMode(*mode);
                femaleGunnerAction_.reset();femaleGunnerStage_=0;femaleGunnerRepeat_=0;femaleGunnerEmissionPending_=false;
                channelContract_.reset();channelState_.reset();
                femaleGunnerOverrideStages_.clear();femaleGunnerOverrideDamageColumns_.clear();femaleGunnerFinishMode_=false;
            }
            if(femaleGunnerModeAttack_) {
                const bool queue=comboQueued_;comboQueued_=false;femaleGunnerAction_.reset();femaleGunnerModeAttack_=false;femaleGunnerEmissionPending_=false;
                activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();animationCursor_.reset();animationDelays_.reset();initialClockVisits_.clear();
                ++combo_;if(queue)attackRequested_=true;
                return out;
            }
            const auto source=sourceActions_.find(actionSequence_);
            if(source!=sourceActions_.end()) {
                const auto &descriptor=plan_->sourceSkillActions.at(source->second.key);
                if(!descriptor.nativeStages.empty()) {
                    const auto current=source->second;
                    const auto &stage=descriptor.nativeStages.at(current.nativeStage);
                    const auto *binding=configuration_.binding(current.key);
                    if(!binding)throw std::logic_error("Active Fighter action lost configuration");
                    const auto &data=*plan_->skills.at(current.key).data;
                    int repetitions=stage.repeat;
                    if(stage.repeatColumn>=0)repetitions=int(*skillLevelValue(data.values("[level info]"),binding->level,stage.repeatColumn));
                    if(stage.repeatStatic>=0)repetitions=data.values("[static data]").at(size_t(stage.repeatStatic)).get<int>();
                    const bool repeat=current.nativeRepeat+1<repetitions;
                    const auto nextIndex=repeat?current.nativeStage:current.nativeStage+1;
                    const bool missedGrab=descriptor.nativeGrab&&current.nativeStage==descriptor.nativeGrab->tryStage&&!current.grabAccepted;
                    // Publish source frames while their original stage ledger
                    // is still live; then replace the action clock exactly once.
                    if(!missedGrab&&nextIndex<descriptor.nativeStages.size()) {
                        publishSourceSkillEntities(out,fixedTick);
                        out.skillAnimationLayers.clear();
                        for(const auto &cue:stage.layers)
                            if(sourceSkillVisualCueMatches(cue,stage.controllerSubstate,stage.controllerStyle))
                                out.skillAnimationLayers.push_back(cue);
                        const auto &next=descriptor.nativeStages[nextIndex];
                        const auto *m=plan_->motion(next.motionTag,size_t(next.motionSlot));
                        const auto *a=next.attackSlot>=0?plan_->attack(next.attackTag,size_t(next.attackSlot)):nullptr;
                        std::optional<FemaleGunnerStageTiming> t;
                        if(state.fighter40JpTestFreedom&&!next.runtimeDelays.empty()){FemaleGunnerStageTiming value;value.controlled=true;value.runtimeDelays=next.runtimeDelays;t=std::move(value);}
                        if(!m||!begin(*m,a?std::optional<ExperimentalSourceBinding>(*a):std::nullopt,current.key,
                            fixedTick,out.actor.attackPerMille+current.operands.attackSpeedBonusPermille,t?&*t:nullptr))
                            throw std::logic_error("Preflighted Fighter native stage could not start");
                        auto following=current;following.nativeStage=nextIndex;following.nativeRepeat=repeat?current.nativeRepeat+1:0;
                        following.unpausedMs=0;following.emitted=false;following.attackSoundEmitted=false;following.movementStarted=false;following.grabDirectHitEmitted=false;
                        sourceActions_.clear();sourceActions_.emplace(actionSequence_,std::move(following));
                        if(!next.sound.empty())out.sounds.push_back(next.sound);
                        out.diagnostics.push_back({{"code","fighter40jp_native_stage"},{"skill",current.key.json()},
                            {"stage",nextIndex},{"repeat",repeat?current.nativeRepeat+1:0},{"owner_action",current.ownerAction},
                            {"attack_ledger",actionSequence_},{"cost_repeated",false}});
                        return out;
                    }
                    if(missedGrab)out.diagnostics.push_back({{"code","fighter40jp_grab_missed"},{"skill",current.key.json()},{"followup",false}});
                }
            }
            if(source!=sourceActions_.end()&&source->second.operands.recoveryMs>0) {
                const auto &action=source->second;
                sourceBodyRecoveryRemainingMs_=action.recoveryPolicy=="since_activation"?
                    std::max<int64_t>(0,int64_t(action.operands.recoveryMs)-action.unpausedMs):action.operands.recoveryMs;
                if(sourceBodyRecoveryRemainingMs_>0) {
                    out.state="inferred_source_body_recovery";out.actor.vx=out.actor.vy=0;
                    bufferedDefaultSkill_.reset();comboQueued_=attackRequested_=jumpRequested_=false;
                    out.diagnostics.push_back({{"code","inferred_source_body_recovery_started"},{"policy",action.recoveryPolicy},
                        {"remaining_ms",sourceBodyRecoveryRemainingMs_},{"source_ms",action.operands.recoveryMs},
                        {"unpaused_action_ms",action.unpausedMs},{"skill",action.key.json()}});
                    publishSourceSkillEntities(out,fixedTick);return out;
                }
            }
            const auto buffered=bufferedDefaultSkill_&&bufferedDefaultSkill_->ownerActionSequence==actionSequence_?bufferedDefaultSkill_:std::nullopt;
            bufferedDefaultSkill_.reset();
            const bool chain=comboQueued_&&!activeSkill_&&normalize(selected.tag)=="[attack motion]";comboQueued_=false;
            activeMotion_.reset();activeAttack_.reset();activeSkill_.reset();dashAttackGlide_.reset();
            animationCursor_.reset();animationDelays_.reset();initialClockVisits_.clear();
            if(buffered&&!chain) {
                trySkill(buffered->skill,true,0,true);
                if(activeMotion_) {
                    // Release at this completed source boundary, with a real
                    // first pose and source frame0 event in the same tick.
                    if(animationCursor_)publishClockAction();
                    else {
                    const auto next=plan_->animations.at(activeMotion_->source.memberPath);
                    out.animationPath=activeMotion_->source.memberPath;out.animationAgeMs=0;out.poseFrame=0;out.state="experimental_attack";
                    ExperimentalAttackFrame first;first.actionSequence=actionSequence_;first.sourceFrame=0;first.skill=activeSkill_;
                    first.motion=*activeMotion_;first.attack=activeAttack_;
                    for(const auto &box:next->frames.front().boxes)if(box.type==15)first.boxes.push_back(box);
                    out.attacks.push_back(std::move(first));
                    if(next->frames.front().properties.contains("16")) {
                        const auto &sound=next->frames.front().properties.at("16");
                        if(sound.is_string()&&!sound.get<std::string>().empty())out.sounds.push_back(sound.get<std::string>());
                    }
                    lastFrame_=0;
                    out.animationClock.reset();
                    }
                }
            } else if(chain) {
                const auto *next=plan_->motion("[attack motion]",++combo_,selected.occurrence);
                const auto *attack=plan_->attack("[attack info]",combo_,selected.occurrence);
                if(next)try {
                    if(begin(*next,attack?std::optional<ExperimentalSourceBinding>(*attack):std::nullopt,std::nullopt,
                        fixedTick,out.actor.attackPerMille)&&animationCursor_)publishClockAction();
                } catch(const std::exception &error) {out.diagnostics.push_back(issue("experimental_combo_clock_blocked",error.what()));}
            }
        }
    } else {
        out.state=(out.actor.z>0||nativeJump_)?"jump":out.actor.vx||out.actor.vy?running_?"dash":"move":"stay";
        const char *tag=out.state=="jump"?"[jump motion]":out.state=="dash"?"[dash motion]":out.state=="move"?"[move motion]":"[waiting motion]";
        auto *motion=plan_->motion(tag);if(!motion||!plan_->animations.count(motion->source.memberPath)) {
            out.diagnostics.push_back(issue("missing_source_locomotion",tag));motion=plan_->motion("[waiting motion]");
        }
        out.animationPath=motion->source.memberPath;out.animationAgeMs=double(ms);out.poseFrame=-1;
        if(out.state=="jump"&&jumpLocomotion_) {
            out.animationClock=jumpLocomotion_->snapshot();
            out.animationAgeMs=double(out.animationClock->elapsedMs);
        }
        if(out.state=="jump"&&nativeJump_&&plan_->nativeJump) {
            const auto &spec=*plan_->nativeJump;const auto &clip=*plan_->animations.at(motion->source.memberPath);
            const size_t begin=nativeJump_->phase==0?0:nativeJump_->phase==1?spec.takeoff:nativeJump_->phase==2?spec.fall:spec.landing;
            const size_t end=nativeJump_->phase==0?spec.takeoff:nativeJump_->phase==1?spec.fall:nativeJump_->phase==2?spec.landing:clip.frames.size();
            int64_t age=nativeJump_->ageMs;size_t frame=begin;
            while(frame+1<end&&age>=clip.frames[frame].duration){age-=clip.frames[frame].duration;++frame;}
            out.poseFrame=int(frame);out.animationClock.reset();out.animationAgeMs=double(nativeJump_->ageMs);
        }
    }
    publishSourceSkillEntities(out,fixedTick);
    if(activeSkill_) {
        const auto source=plan_->sourceSkillActions.find(*activeSkill_);
        if(source!=plan_->sourceSkillActions.end()&&(source->second.kind==SourceSkillActionKind::BodyAttack||source->second.movingImpact)) {
            const auto &descriptor=source->second;
            if(!descriptor.nativeStages.empty()) {
                const auto action=sourceActions_.find(actionSequence_);
                if(action!=sourceActions_.end()) {
                    const auto &stage=descriptor.nativeStages.at(action->second.nativeStage);
                    for(const auto &cue:stage.layers)
                        if(sourceSkillVisualCueMatches(cue,stage.controllerSubstate,stage.controllerStyle))
                            out.skillAnimationLayers.push_back(cue);
                }
            } else if(descriptor.bodyLayerBirthFrame<0)out.skillAnimationLayers=descriptor.bodyLayers;
            else {
                const auto action=sourceActions_.find(actionSequence_);
                if(action!=sourceActions_.end()&&action->second.layerBirthUnpausedMs>=0) {
                    const auto age=uint64_t(std::max<int64_t>(0,action->second.unpausedMs-action->second.layerBirthUnpausedMs));
                    for(auto layer:descriptor.bodyLayers) {
                        const auto &clip=*plan_->animations.at(layer.source.memberPath);
                        ani_clock::Snapshot clock;clock.elapsedMs=age;clock.lastTick=fixedTick;
                        clock.paused=state.hitStopped||state.blocked;
                        layer.instanceClock=clip.followClock(clip,clock,false);
                        if(!layer.instanceClock->ended)out.skillAnimationLayers.push_back(std::move(layer));
                    }
                }
            }
        }
    }
    return out;
}
void ExperimentalCharacterRuntime::publishSourceSkillEntities(ExperimentalTickResult &out,uint64_t fixedTick) {
    // Consume actual crossed body frames, including zero-delay flags. A held
    // frame cannot recreate a PO; its action owns one source callback receipt.
    for(auto &frame:out.attacks) {
        const auto action=sourceActions_.find(frame.actionSequence);
        if(action==sourceActions_.end())continue;
        const auto &descriptor=plan_->sourceSkillActions.at(action->second.key);
        const auto &properties=plan_->animations.at(frame.motion.source.memberPath)->frames.at(frame.sourceFrame).properties;
        if(descriptor.kind==SourceSkillActionKind::BodyAttack) {
            frame.sourceFamily=descriptor.inferredNativeBody?"inferred_current1031_body_skill":"reviewed_nut_body_attack";
            frame.skillModifiers=action->second.operands.damage;
            if(!descriptor.nativeStages.empty()) {
                const auto &stage=descriptor.nativeStages.at(action->second.nativeStage);
                frame.contactEffects=stage.contactEffects;
                const auto *binding=configuration_.binding(action->second.key);
                const auto &data=*plan_->skills.at(action->second.key).data;
                const auto coefficient=[&](int column)->float {
                    if(column<0)return 0;const auto value=skillLevelValue(data.values("[level info]"),binding->level,column);
                    if(!value||*value<0||*value>INT32_MAX)throw std::invalid_argument("Fighter stage coefficient changed after admission");return float(*value);
                };
                frame.skillModifiers->percent=coefficient(stage.percentColumn);
                frame.skillModifiers->independentPercent=coefficient(stage.independentColumn);
                frame.suppressBodyDamage=stage.suppressBodyDamage;
                frame.sourceFamily="40jp_fighter_"+descriptor.nativeFamily;
                if(descriptor.nativeGrab) {
                    frame.sourceGrabOwner=action->second.ownerAction;
                    frame.sourceGrabTry=action->second.nativeStage==descriptor.nativeGrab->tryStage;
                    frame.sourceGrabRelease=action->second.grabAccepted&&action->second.nativeStage>=descriptor.nativeGrab->releaseStage;
                    if(frame.sourceGrabTry)frame.suppressBodyDamage=true;
                    if(frame.sourceGrabRelease&&action->second.nativeStage==descriptor.nativeGrab->releaseStage&&
                       descriptor.nativeGrab->directHitFrame>=0&&frame.sourceFrame==size_t(descriptor.nativeGrab->directHitFrame)&&
                       !action->second.grabDirectHitEmitted) {
                        // 40JP sub_5E78C0 case19 directly calls sub_4E5F70 on
                        // the captured target at frame4. Current Suplex ANI
                        // has no attack box: do not invent one for this event.
                        frame.sourceGrabDirectHit=true;frame.suppressBodyDamage=false;
                        action->second.grabDirectHitEmitted=true;
                    }
                }
            }
            if(action->second.operands.bodyLift)frame.sourceLift=action->second.operands.bodyLift;
            if(!descriptor.attackSound.empty()&&!action->second.attackSoundEmitted) {
                const auto &bodyFrame=plan_->animations.at(frame.motion.source.memberPath)->frames.at(frame.sourceFrame);
                const bool bodyAttack=std::any_of(bodyFrame.boxes.begin(),bodyFrame.boxes.end(),[](const auto &box){
                    return box.type==15&&box.w>0&&box.h>0&&box.d>0;
                });
                if(bodyAttack) {out.sounds.push_back(descriptor.attackSound);action->second.attackSoundEmitted=true;}
            }
            if(descriptor.bodyLayerBirthFrame>=0&&action->second.layerBirthUnpausedMs<0&&
               frame.sourceFrame>=size_t(descriptor.bodyLayerBirthFrame)) {
                // Use the real crossed-frame deadline, including any excess
                // within this fixed tick. Do not restart a held frame or
                // rescale past visual age when actor attack speed changes.
                const auto elapsed=animationCursor_?animationCursor_->snapshot().elapsedMs:uint64_t(std::max(0.0,age_));
                // emit(current.frame,current) may replace the last visit's
                // elapsed sample; frameStartMs still retains its real entry
                // deadline. Using sample.elapsedMs here would lose overshoot.
                const auto sample=frame.animationClock?frame.animationClock->frameStartMs:elapsed;
                const auto overshoot=elapsed>sample?elapsed-sample:0;
                action->second.layerBirthUnpausedMs=std::max<int64_t>(0,action->second.unpausedMs-int64_t(overshoot));
                if(!action->second.emitted) {
                    out.sourceCameraShakes.push_back({-1,descriptor.shakeAmplitude,descriptor.shakeDurationMs,frame.actionSequence});
                    action->second.emitted=true;
                }
            }
            if(descriptor.bodyLayerBirthFrame<0&&!action->second.emitted&&properties.contains("23")&&properties.at("23").is_number_integer()&&
                uint16_t(properties.at("23").get<int32_t>())==descriptor.flag) {
                out.sourceCameraShakes.push_back({-1,descriptor.shakeAmplitude,descriptor.shakeDurationMs,frame.actionSequence});
                action->second.emitted=true;
            }
            if(!descriptor.nativeProjectile)continue;
        }
        frame.suppressBodyDamage=true;frame.sourceFamily="reviewed_nut_action_body";
        if(descriptor.nativeProjectile) {
            if(action->second.emitted||frame.sourceFrame<size_t(descriptor.nativeProjectile->birthFrame))continue;
        } else if(action->second.emitted||!properties.contains("23")||!properties.at("23").is_number_integer()||
           (!descriptor.movingImpact&&uint16_t(properties.at("23").get<int32_t>())!=descriptor.flag))continue;
        if(sourceEntities_.size()>=128||sourceEntitySequence_==UINT64_MAX)throw std::length_error("Source NUT passive entity budget exhausted");
        SourceEntity entity;entity.instance=++sourceEntitySequence_;entity.actionSequence=frame.actionSequence;
        entity.key=action->second.key;entity.operands=action->second.operands;entity.direction=out.actor.direction;
        entity.position={out.actor.x+entity.direction*descriptor.offset[0],out.actor.y+descriptor.offset[1],out.actor.z+descriptor.offset[2]};
        entity.origin=entity.position;
        entity.initialVisits=entity.playback.install(*descriptor.objectAnimation,
            (descriptor.movingImpact||bool(descriptor.nativeProjectile&&descriptor.nativeProjectile->speedColumn>=0))&&descriptor.objectAnimation->globals.value("0",false),
            100,ani_clock::ClockPolicy::SourceDelay100,fixedTick).visits;
        if(descriptor.movingImpact) {
            const auto &moving=*entity.operands.movingImpact;const int dx=int(held_[1])-int(held_[0]);
            const bool alternate=dx==-out.actor.direction;
            const int velocity=alternate?moving.alternateRecoilVelocity:moving.recoilVelocity;
            const int acceleration=alternate?moving.alternateRecoilAcceleration:moving.recoilAcceleration;
            AxisMotion recoil;applyStaticAxisOperands(recoil,{float(velocity*out.actor.direction),acceleration*out.actor.direction},AxisWritePath::Direct,true);
            sourceRecoil_=recoil;
            out.diagnostics.push_back({{"code","source_watercannon_recoil"},{"policy","inferred-source-static-axis-recoil-v1"},
                {"opposite_input",alternate},{"source_velocity",velocity},{"source_acceleration",acceleration},{"source",descriptor.callback.json()}});
        }
        ExperimentalSourceVisual visual;visual.kind=ExperimentalSourceVisual::Kind::Spawn;
        visual.key=entity.key;visual.entity=entity.instance;visual.actionSequence=entity.actionSequence;
        visual.position=entity.position;visual.direction=entity.direction;visual.evidence=entity.operands.evidence;
        if(descriptor.movingImpact) {visual.loop=true;visual.lifetimeMs=entity.operands.movingImpact->travelMs;
            visual.imageScale=visual.autoLayerScale=entity.operands.movingImpact->sizePercent/100.0;}
        out.sourceSkillVisuals.push_back(std::move(visual));sourceEntities_.push_back(std::move(entity));action->second.emitted=true;
    }
    for(auto &entity:sourceEntities_) {
        const auto &descriptor=plan_->sourceSkillActions.at(entity.key);
        const auto &animation=entity.impact?*descriptor.movingImpact->impactClip:*descriptor.objectAnimation;
        const auto before=entity.playback.snapshot();auto visits=std::move(entity.initialVisits);entity.initialVisits.clear();
        if(before.lastTick<fixedTick) {
            auto advanced=entity.playback.advance(fixedTick,false);visits.insert(visits.end(),advanced.visits.begin(),advanced.visits.end());
        }
        const auto current=entity.playback.snapshot();
        bool travelEnded=false;
        if(descriptor.movingImpact&&!entity.impact) {
            const auto &moving=*entity.operands.movingImpact;const auto elapsed=std::min<uint64_t>(current.elapsedMs,uint64_t(moving.travelMs));
            entity.position[0]=entity.origin[0]+entity.direction*double(moving.distance)*double(elapsed)/moving.travelMs;
            travelEnded=current.elapsedMs>=uint64_t(moving.travelMs);
            ExperimentalSourceVisual update;update.kind=ExperimentalSourceVisual::Kind::Update;update.key=entity.key;
            update.entity=entity.instance;update.actionSequence=entity.actionSequence;update.position=entity.position;update.direction=entity.direction;
            out.sourceSkillVisuals.push_back(std::move(update));
        }
        if(descriptor.nativeProjectile) {
            const auto &p=*descriptor.nativeProjectile;const auto &data=*plan_->skills.at(entity.key).data;
            const auto *binding=configuration_.binding(entity.key);
            const double speed=p.speedColumn>=0?skillLevelValue(data.values("[level info]"),binding?binding->level:1,p.speedColumn).value_or(0):p.speed;
            double range=p.range;const auto statics=data.values("[static data]");
            if(p.rangeStatic>=0&&size_t(p.rangeStatic)<statics.size()&&statics[p.rangeStatic].is_number())range=statics[p.rangeStatic].get<double>();
            if(speed>0) {
                const double distance=speed*double(current.elapsedMs)/1000;
                entity.position[0]=entity.origin[0]+entity.direction*std::min(distance,range>0?range:distance);
                travelEnded=range>0&&distance>=range;
                ExperimentalSourceVisual update;update.kind=ExperimentalSourceVisual::Kind::Update;update.key=entity.key;
                update.entity=entity.instance;update.actionSequence=entity.actionSequence;update.position=entity.position;update.direction=entity.direction;
                out.sourceSkillVisuals.push_back(std::move(update));
            }
        }
        const auto emit=[&](size_t index) {
            ExperimentalAttackFrame frame;frame.sourceEntity=true;frame.sourceEntityInstance=entity.instance;
            frame.sourceOrigin=entity.position;frame.sourceDirection=entity.direction;frame.sourceImpact=entity.impact;
            if(!descriptor.movingImpact)frame.sourceLift=entity.operands.lift;
            frame.actionSequence=entity.actionSequence;frame.sourceFrame=index;frame.skill=entity.key;
            frame.sourceFamily=descriptor.movingImpact?entity.impact?"source_watercannon_impact":"source_watercannon_flight":"reviewed_nut_passive_object";frame.skillModifiers=entity.operands.damage;
            const auto &motion=entity.impact?descriptor.movingImpact->impactAnimation:descriptor.animation;
            const auto &attack=entity.impact?descriptor.movingImpact->impactAttack:descriptor.attack;
            frame.motion={"[basic motion]",0,0,motion};frame.attack=ExperimentalSourceBinding{"[attack info]",0,0,attack};
            for(auto box:animation.frames.at(index).boxes)if(box.type==15) {
                if(descriptor.movingImpact) {const auto rate=double(entity.operands.movingImpact->sizePercent-
                    (entity.impact?descriptor.movingImpact->impactSizeSubtract:0))/100.0;
                    // Source setters scale XYZ origin and extent. Integer
                    // truncation is a named host inference, not a native proof.
                    box.x=int(box.x*rate);box.y=int(box.y*rate);box.z=int(box.z*rate);
                    box.w=int(box.w*rate);box.h=int(box.h*rate);box.d=int(box.d*rate);}
                frame.boxes.push_back(box);}
            out.attacks.push_back(std::move(frame));
        };
        if(!travelEnded&&visits.empty()&&!before.ended)emit(before.frame);
        for(const auto &visit:visits) {
            if(!travelEnded)emit(visit.frame);
            const auto &properties=animation.frames.at(visit.frame).properties;
            if(properties.contains("16")&&properties.at("16").is_string())out.sounds.push_back(properties.at("16").get<std::string>());
        }
        if(current.ended||travelEnded) {
            ExperimentalSourceVisual retired;retired.kind=ExperimentalSourceVisual::Kind::Retire;
            retired.key=entity.key;retired.entity=entity.instance;out.sourceSkillVisuals.push_back(std::move(retired));
        }
    }
    std::set<uint64_t> retired;
    for(const auto &v:out.sourceSkillVisuals)if(v.kind==ExperimentalSourceVisual::Kind::Retire)retired.insert(v.entity);
    sourceEntities_.erase(std::remove_if(sourceEntities_.begin(),sourceEntities_.end(),[&](const SourceEntity &e){
        return e.playback.snapshot().ended||retired.count(e.instance);}),sourceEntities_.end());
    for(auto i=sourceActions_.begin();i!=sourceActions_.end();)if(!activeMotion_||i->first!=actionSequence_)i=sourceActions_.erase(i);else ++i;
}
std::optional<SourceGrabRuntimeState> ExperimentalCharacterRuntime::sourceGrabState() const {
    if(!activeMotion_)return std::nullopt;
    const auto action=sourceActions_.find(actionSequence_);if(action==sourceActions_.end())return std::nullopt;
    const auto &descriptor=plan_->sourceSkillActions.at(action->second.key);if(!descriptor.nativeGrab)return std::nullopt;
    SourceGrabRuntimeState out;out.key=action->second.key;out.ownerAction=action->second.ownerAction;
    out.holding=action->second.grabAccepted;out.stage=action->second.nativeStage;
    out.release=out.holding&&out.stage>=descriptor.nativeGrab->releaseStage;
    out.offset=descriptor.nativeGrab->holdOffset;if(out.release)out.offset={30,0,0};return out;
}
bool ExperimentalCharacterRuntime::acceptSourceGrabHit(uint64_t ownerAction) {
    if(!activeMotion_)return false;
    const auto action=sourceActions_.find(actionSequence_);if(action==sourceActions_.end())return false;
    const auto &descriptor=plan_->sourceSkillActions.at(action->second.key);
    if(!descriptor.nativeGrab||action->second.ownerAction!=ownerAction||action->second.grabAccepted||
       action->second.nativeStage!=descriptor.nativeGrab->tryStage)return false;
    action->second.grabAccepted=true;return true;
}
bool ExperimentalCharacterRuntime::sourceEntityIsMovingFlight(uint64_t id) const {
    for(const auto &entity:sourceEntities_)if(entity.instance==id)
        return !entity.impact&&bool(plan_->sourceSkillActions.at(entity.key).movingImpact);
    return false;
}
ExperimentalSourceVisual ExperimentalCharacterRuntime::acceptSourceMovingHit(uint64_t id,uint64_t fixedTick) {
    const auto found=std::find_if(sourceEntities_.begin(),sourceEntities_.end(),[&](const auto &e){return e.instance==id;});
    if(found==sourceEntities_.end()||found->impact||!plan_->sourceSkillActions.at(found->key).movingImpact)
        throw std::invalid_argument("Moving source contact owner is stale or already retired");
    if(sourceEntitySequence_==UINT64_MAX)throw std::overflow_error("Moving impact entity identity exhausted");
    SourceEntity impact=*found;const auto &descriptor=plan_->sourceSkillActions.at(impact.key);const auto &program=*descriptor.movingImpact;
    impact.instance=++sourceEntitySequence_;impact.impact=true;
    for(size_t axis=0;axis<3;++axis)impact.position[axis]+=program.impactOffset[axis]*(axis==0?impact.direction:1);
    impact.origin=impact.position;impact.playback.clear();
    impact.initialVisits=impact.playback.install(*program.impactClip,false,100,ani_clock::ClockPolicy::SourceDelay100,fixedTick).visits;
    ExperimentalSourceVisual visual;visual.kind=ExperimentalSourceVisual::Kind::Spawn;visual.key=impact.key;
    visual.entity=impact.instance;visual.actionSequence=impact.actionSequence;visual.impact=true;
    visual.position=impact.position;visual.direction=impact.direction;visual.lifetimeMs=program.impactClip->duration;
    visual.imageScale=(impact.operands.movingImpact->sizePercent-program.impactSizeSubtract)/100.0;
    visual.autoLayerScale=1;visual.evidence=impact.operands.evidence;
    // Replacing an existing vector element avoids changing capacity after
    // retirement. Caller performs this on a private runtime candidate only.
    *found=std::move(impact);return visual;
}
bool ExperimentalCharacterRuntime::sourceFrameSuperArmor() const {
    if(!activeMotion_||!activeSkill_)return false;
    const auto descriptor=plan_->sourceSkillActions.find(*activeSkill_);
    if(descriptor==plan_->sourceSkillActions.end()||!descriptor->second.sourceFrameSuperArmor||
       !sourceActions_.count(actionSequence_)||sourceBodyRecoveryRemainingMs_>0)return false;
    const auto &animation=*plan_->animations.at(activeMotion_->source.memberPath);
    const auto frame=animationCursor_?animationCursor_->snapshot().frame:
        lastFrame_>=0?size_t(lastFrame_):size_t(0);
    if(frame>=animation.frames.size())return false;
    const auto &properties=animation.frames[frame].properties;
    return properties.contains("13")&&properties.at("13").is_number_integer()&&properties.at("13")==1;
}
Json ExperimentalCharacterRuntime::snapshotDiagnostics() const {
    size_t sourceBodyActions=0;
    for(const auto &action:sourceActions_)
        if(plan_->sourceSkillActions.at(action.second.key).inferredNativeBody)++sourceBodyActions;
    const auto buffered=[](const std::optional<BufferedDefaultSkill> &value)->Json {
        return value?Json{{"skill",value->skill.json()},{"owner_action_sequence",value->ownerActionSequence}}:Json();
    };
    Json sidesteps=Json::array();
    for(const auto &[sequence,action]:sourceActions_)if(action.sidestep)
        sidesteps.push_back({{"owner",sequence},{"skill",action.key.json()},{"state",action.sidestep->snapshot()}});
    Json clock;
    if(animationCursor_) {
        const auto &state=animationCursor_->snapshot();
        clock={{"policy",ani_clock::policyName(state.policy)},{"arithmetic",ani_clock::arithmeticProfileName()},
            {"frame",state.frame},{"elapsed_ms",state.elapsedMs},{"local_ms",state.localMs},{"span_ms",state.spanMs},
            {"deadline_ms",state.nextDeadlineMs},{"rate_percent",state.ratePercent},{"rate_revision",state.rateRevision},
            {"last_tick",state.lastTick},{"paused",state.paused},{"ended",state.ended},
            {"classification","inferred_1031_clock_adaptation"},{"native_verified",false},
            {"speed_mapping","truncate-positive-effective-attack-stat-v1"}};
    }
    return {{"identity",plan_->identity.json()},{"readiness","experimental_user_test"},{"runtime_complete",false},
        {"policy",policy_.id},{"action_sequence",actionSequence_},{"last_cost",lastCost_},
        {"source_nut_actions",sourceActions_.size()-sourceBodyActions},{"source_body_actions",sourceBodyActions},{"source_nut_entities",sourceEntities_.size()},
        {"source_nut_entity_sequence",sourceEntitySequence_},{"source_body_sidesteps",sidesteps},
        {"source_body_recovery",{{"remaining_ms",sourceBodyRecoveryRemainingMs_},{"policy",configuration_.sourceBodyRecoveryPolicy()}}},
        {"requested_animation_clock",animationClockPolicy_?Json(ani_clock::policyName(*animationClockPolicy_)):Json("legacy-scaled-local-age")},
        {"animation_clock",clock},
        {"gunner_ground",gunnerGround_?Json{{"phase",gunnerGround_->phase},{"subtype",gunnerGround_->subtype},
            {"shots",gunnerGround_->shots},{"elapsed_ms",gunnerGround_->elapsed},{"emitted",gunnerGround_->emitted},{"down",gunnerGround_->down},
            {"deadlines",gunnerGround_->deadlines.snapshot()}}:Json()},
        {"gunner_target_aim",{{"enabled",gunnerTargetAimEnabled_},{"policy","inferred-nearest-forward-source-hurtbox-aim-v1"},{"native_BF9060_equality",false}}},
        {"jump_locomotion_clock",jumpLocomotion_?Json{{"elapsed_ms",jumpLocomotion_->snapshot().elapsedMs},
            {"frame",jumpLocomotion_->snapshot().frame},{"ended",jumpLocomotion_->snapshot().ended}}:Json()},
        {"fighter40jp_jump",nativeJump_?Json{{"phase",nativeJump_->phase},{"age_ms",nativeJump_->ageMs},
            {"source",plan_->nativeJump->evidence}}:Json()},
        {"female_gunner_basic_jump_stage",femaleGunnerBasicJumpStage_},
        {"basic_attack_movement",basicMovementPolicy_.json()},{"dash_attack_glide",dashAttackGlide_?dashAttackGlide_->json():Json()},
        {"action_timing",actionTiming_?actionTiming_->snapshot():Json()},
        {"channel_input",{{"attack_held",attackHeld_},{"attack_edge",attackEdge_},{"jump_edge",jumpEdge_},
            {"contract",channelContract_?channelContract_->snapshot():Json()},
            {"deadline_ms",channelState_?Json(channelState_->deadlineMs):Json()},
            {"recovery_remaining_ms",channelRecoveryRemainingMs_}}},
        {"default_skill_requested",buffered(defaultSkillRequested_)},{"buffered_default_skill",buffered(bufferedDefaultSkill_)},
        {"pending",pendingDiagnostics_},{"source_diagnostics",plan_->diagnostics}};
}
void registerExperimentalControllers(CharacterControllerRegistry &registry,const CharacterCatalog &catalog,const std::string &pvfIdentity) {
    for(const auto &definition:catalog.definitions) {
        if(definition.registration.id==0||definition.runtimeDeferredByUser)continue;
        CharacterControllerInfo info;info.identity={definition.registration.id,0,0};info.name=definition.job;
        info.implementation="source-character-experimental-v1";info.readiness=ControllerReadiness::ExperimentalUserTest;info.pvfSha256=pvfIdentity;
        info.limitation="User-authorized incomplete experiment: source CHR basic actions/ATK and manual same-job skill bindings; special/passive mechanisms unresolved";
        const auto identity=info.identity;
        registry.registerController(std::move(info),[identity](CharacterControllerServices services){return std::make_unique<SourceExperimentalController>(identity,std::move(services));});
    }
}
} // namespace dnf
