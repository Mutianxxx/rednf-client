#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/female_gunner_world.hpp"
#include "dnf/effect_plan.hpp"
#include <algorithm>
#include <climits>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <tuple>

namespace dnf {
namespace {
bool sameOverlay(const SkillLearningTestOverlay &a,const SkillLearningTestOverlay &b) {
    return a.levels==b.levels&&a.spentSp==b.spentSp&&a.spentTp==b.spentTp&&a.revision==b.revision&&
        a.normalFingerprint==b.normalFingerprint&&a.purchases==b.purchases&&a.receipts==b.receipts;
}
int sourceMaximum(const ExperimentalSkillRow &row) {
    int maximum=0;
    if(row.data)for(const auto *tag:{"[growtype maximum level]","[second growtype maximum level]"})
        for(const auto &v:row.data->values(tag))if(v.is_number_integer())maximum=std::max(maximum,v.get<int>());
    return maximum;
}
RuntimeSkillPolicy reviewedPolicy(const ExperimentalCharacterPlan &plan,SkillKey key) {
    const auto found=plan.skills.find(key);
    if(key.jobId!=plan.identity.jobId||found==plan.skills.end())return {key,SkillSourceKind::Unknown,false,false,0};
    const auto &row=found->second;
    // Actual reviewed execution entry points, not descriptor/template counts.
    static const std::set<SkillKey> actions{{1,5},{1,6},{2,4},{3,4},{3,12},{4,1},{4,116},{8,1},{8,26}};
    bool implemented=actions.count(key)&&plan.sourceSkillActions.count(key)&&row.kind==SkillSourceKind::Active;
    if(implemented&&key==SkillKey{1,5}) {
        const auto &action=plan.sourceSkillActions.at(key);
        const auto policy=action.evidence.value("policy",std::string());
        const bool reviewedExecution=action.native40Jp?
            policy=="40jp-fighter-shared-native-stages-v1"&&action.nativeFamily=="upper"&&
                action.nativeStages.size()==1&&action.nativeStages.front().motion.json()==action.motion.json()&&
                action.nativeStages.front().attack.json()==action.attack.json()&&!action.nativeStages.front().suppressBodyDamage:
            policy=="inferred-current1031-fighter-upper-body-v1";
        implemented=action.kind==SourceSkillActionKind::BodyAttack&&action.inferredNativeBody&&
            action.skill.memberSha256=="a40014b6ebfa77185903856fdfc7d3a08b7d3bed59e823a7a5e17bfe3caa0c83"&&
            action.motion.memberSha256=="aa91dc98611f24133e0bcd7715708bef9edf2287dc4c511663631324b054dd13"&&
            action.attack.memberSha256=="472b1c3deb7b321f49fd0f8da471b4976910c203d9ceb46c4d2d5766fa03b9db"&&
            reviewedExecution;
    }
    if(implemented&&key==SkillKey{8,26}) {
        const auto &action=plan.sourceSkillActions.at(key);
        implemented=action.kind==SourceSkillActionKind::MovingImpactObject&&bool(action.movingImpact)&&
            action.skill.memberSha256=="298bfd4d93d24560ad4ecaf9350835aaaab0102aa1113f6aaaa39b87f11bf552"&&
            action.callback.memberSha256=="6538c9a61c1f52567cac3bd84af028401e471bcf23281b13c9f8a948cd6e491b"&&
            std::string(action.movingImpact->visualPolicy)=="inferred-current1031-watercannon-tree-v1";
    }
    if(implemented&&key==SkillKey{4,1}) {
        const auto &action=plan.sourceSkillActions.at(key);
        implemented=action.kind==SourceSkillActionKind::BodyAttack&&action.inferredNativeBody&&action.actorAttackSpeedOnly&&
            action.requiresEquippedAttackVolume&&action.bodyLayerBirthFrame>=0&&action.bodyLayers.size()==2&&
            action.skill.memberSha256=="d8a660636603db3ff2e331558df8344cd6729bb319f9ed7ae8231f3cf5c325c3"&&
            action.evidence.value("policy","")=="inferred-current1031-priest-upper-body-v1";
    }
    if(implemented&&key==SkillKey{3,12}) {
        const auto &action=plan.sourceSkillActions.at(key);
        implemented=action.kind==SourceSkillActionKind::BodyAttack&&action.inferredNativeBody&&
            action.requiresEquippedAttackVolume&&action.bodySidestep&&action.liftColumn==2&&
            action.skill.memberSha256=="9e3c527a1979ed30f2a4f898e3bf13ef76ff101ad7a5dc0716ca5f80856b654b"&&
            action.motion.memberSha256=="1349ee90f25019124d9278496426e67744cfa5199869b36b978238f652bde9a2"&&
            action.attack.memberSha256=="0c9f28c39ef0bf211961cdc1e1e83709a9e32fa4a60874986b7e7f536efe878a"&&
            action.evidence.value("policy",std::string())=="inferred-current1031-mage-upper-body-v1";
    }
    bool passive=false;
    if(key.jobId==5) {
        // Narrow first normal bridge; other source families remain diagnosed.
        static const std::set<int> active{1,2,3,4,5,7,12,13,14,20,30,36,38,39,40,47,52,73,107};
        static const std::set<int> passiveConsumers{21,32,44,49,74,93,110,174,178,186,188,189};
        const auto descriptor=plan.femaleGunnerSkills.find(key);
        if(row.kind==SkillSourceKind::Active&&active.count(key.skillId))
            implemented=descriptor!=plan.femaleGunnerSkills.end()&&descriptor->second.dedicatedRuntime&&
                !descriptor->second.stages.empty();
        if(row.kind==SkillSourceKind::Passive&&passiveConsumers.count(key.skillId)) {
            implemented=descriptor!=plan.femaleGunnerSkills.end()&&bool(row.data);passive=implemented;
        }
        // 195/200 retain actual experimental modifiers but their system/guild
        // entitlement consumer is not closed, so normal learning stays shut.
        // 8 and 41 have no reviewed qualification/charge consumers. Their
        // 35/45 chains do not gain admission through legacy manual preview.
    }
    return {key,row.kind,implemented,passive,sourceMaximum(row)};
}
std::string fighterUpperNormalBlocker(const CharacterSkillState &effective) {
    if(effective.identity().jobId!=1||effective.learnedLevel({1,163})<=0)return {};
    return "上勾拳 {1,5} 暂不能按完整已学配置释放：强化 - 上勾拳 {1,163} 已学等级 "+
        std::to_string(effective.learnedLevel({1,163}))+" 的实际增益消费者尚未实现";
}
std::string waterCannonNormalBlocker(const CharacterSkillState &effective) {
    if(effective.identity().jobId!=8)return {};
    std::string blocker;
    for(const auto key:{SkillKey{8,236},SkillKey{8,51}})if(effective.learnedLevel(key)>0) {
        if(!blocker.empty())blocker+="; ";
        blocker+=(key.skillId==236?"强化 - 魔法冰球 {8,236}":"元素唤醒 {8,51}");
        blocker+=" 已学等级 "+std::to_string(effective.learnedLevel(key))+" 的实际增益消费者尚未实现";
    }
    return blocker.empty()?blocker:"魔法冰球 {8,26} 暂不能按完整已学配置释放："+blocker;
}
std::string priestUpperNormalBlocker(const CharacterSkillState &effective) {
    if(effective.identity().jobId!=4)return {};
    std::string blocker;
    for(const auto key:{SkillKey{4,210},SkillKey{4,123}})if(effective.learnedLevel(key)>0&&
        (key.skillId==210||effective.identity().growtype==4)) {
        if(!blocker.empty())blocker+="; ";
        blocker+=(key.skillId==210?"强化 - 空斩打 {4,210}":"恶魔之力 {4,123}");
        blocker+=" 已学等级 "+std::to_string(effective.learnedLevel(key))+" 的实际增益消费者尚未实现";
    }
    return blocker.empty()?blocker:"空斩打 {4,1} 暂不能按完整已学配置释放："+blocker;
}
std::string mageBodyNormalBlocker(const CharacterSkillState &effective,SkillKey base) {
    if(effective.identity().jobId!=3)return {};
    const SkillKey tp{3,base.skillId==12?210:212};
    if(effective.learnedLevel(tp)<=0)return {};
    return std::string(base.skillId==12?"天击 {3,12}":"龙牙 {3,4}")+" 暂不能按完整已学配置释放：强化技能 {3,"+
        std::to_string(tp.skillId)+"} 已学等级 "+std::to_string(effective.learnedLevel(tp))+" 的实际增益消费者尚未实现";
}
ExperimentalSkillConfiguration learnedConfiguration(const ExperimentalCharacterPlan &plan,
    const ExperimentalSkillConfiguration *preferences,const CharacterSkillState &effective,
    const SkillLearningService &learning,int effectiveLevel) {
    ExperimentalSkillConfiguration result(plan);
    auto saved=preferences?preferences->snapshot():result.snapshot();
    // Carry user slots/comparison preferences, never their stale manual levels.
    saved["skill_bindings"]=Json::array();
    saved.erase("female_gunner_passive_levels");saved.erase("female_gunner_passive_policy");
    saved.erase("source_action_passives");saved.erase("source_action_passive_policy");
    // This proposal permits an explicit manual caller/timing comparison.
    // A reviewed normal policy must set its own canonical projection after
    // normal admission checks; it must never inherit manual preferences.
    saved.erase("source_action_audio_policy");
    saved["learning_projection_policy"]="reviewed-effective-ledger-v1";
    result.restore(saved,plan);
    for(const auto &[key,row]:plan.skills) {
        const auto policy=reviewedPolicy(plan,key);const int level=effective.learnedLevel(key);
        if(!policy.implemented||level<=0||!learning.useEligibility(effective,key,effectiveLevel).allowed())continue;
        if(key.jobId==5) {
            result.configureFemaleGunnerSourceSkill(key,level,plan);
            // Passive tables require real numeric consumers as well as a
            // registration. Fail privately if that selected source row breaks.
            if(row.kind==SkillSourceKind::Passive)
                (void)evaluateFemaleGunnerSkill(plan.femaleGunnerSkills.at(key),*row.data,level,-1);
        }
        else if(row.kind==SkillSourceKind::Passive)result.configureSourceActionPassive(key,level,plan);
        else {
            result.configureSourceSkillAction(key,level,plan);
            // This exact own-source descriptor has reviewed SKL/CHR/ANI/ATK
            // hashes and an explicit inferred-beta cast-audio policy. Derive
            // it from the effective learned ledger, never manual preferences.
            if(key==SkillKey{2,4})result.setSourceActionAudioPolicy("inferred-current1031-knee-cast-audio-v1",plan);
        }
    }
    return result;
}
}

bool CharacterSkillState::sameRuntimeState(const CharacterSkillState &other) const {
    if(!(identity_==other.identity_)||preserved_!=other.preserved_||states_.size()!=other.states_.size())return false;
    auto a=states_.begin(),b=other.states_.begin();
    for(;a!=states_.end();++a,++b)
        if(!(a->first==b->first)||a->second.level!=b->second.level||
            a->second.cooldownUntilMs!=b->second.cooldownUntilMs||a->second.preserved!=b->second.preserved)return false;
    return true;
}
struct PreparedSkillRuntime::Data {
    const World *owner=nullptr;
    CharacterIdentity identity,beforeIdentity;
    int64_t nowMs=0,beforeNowMs=0;
    uint64_t beforeRevision=0,beforeAttributeRevision=0;
    int normalLevel=1,effectiveLevel=1;
    bool testLearning=false,previewEnabled=false,restoring=false,beforePreview=false,beforeDebug=false;
    std::optional<int> beforeDebugLevel;
    CharacterSkillState normal,beforeNormal;
    SkillLearningTestOverlay overlay,beforeOverlay;
    std::vector<int> activeLevels,passiveLevels;
    const ExperimentalCharacterPlan *plan=nullptr;
    std::optional<ExperimentalSkillConfiguration> normalConfiguration,testConfiguration,previewConfiguration,currentConfiguration;
    std::optional<ExperimentalSkillConfiguration> beforeConfiguration;
};
PreparedSkillRuntime::PreparedSkillRuntime(std::unique_ptr<Data> data):data_(std::move(data)){}
PreparedSkillRuntime::~PreparedSkillRuntime()=default;
PreparedSkillRuntime::PreparedSkillRuntime(PreparedSkillRuntime &&) noexcept=default;
PreparedSkillRuntime &PreparedSkillRuntime::operator=(PreparedSkillRuntime &&) noexcept=default;
Json PreparedSkillRuntime::writeCharacter(Json character) const {
    if(!data_)throw std::invalid_argument("Prepared skill runtime has already been published");
    const auto &p=*data_;
    if(!character.is_object()||!character.contains("identity")||
        !(CharacterIdentity::fromJson(character.at("identity"))==p.identity))
        throw std::invalid_argument("Prepared skill runtime save identity differs");
    character["skill_state"]=p.normal.snapshot(p.nowMs);character["skill_test_overlay"]=p.overlay.snapshot();
    if(p.normalConfiguration) {
        character["experimental_skill_configuration"]=p.normalConfiguration->snapshot();
        character["experimental_test_skill_configuration"]=p.testConfiguration?p.testConfiguration->snapshot():Json();
        character["experimental_manual_preview_configuration"]=p.previewConfiguration?p.previewConfiguration->snapshot():Json();
        character["experimental_skill_execution_mode"]=p.previewEnabled?"manual_preview":"learned";
    }
    return character;
}
const SkillLearningService &World::skillLearning() const {
    if(!skillLearningService_)skillLearningService_=std::make_unique<SkillLearningService>(pvf_,characters_);
    return *skillLearningService_;
}
bool World::hasLearningLedger() const {return skillState_.snapshot(nowMs()).contains("learning");}
RuntimeSkillPolicy World::runtimeSkillPolicy(SkillKey key) const {
    if(experimentalRuntime_)return reviewedPolicy(experimentalRuntime_->plan(),key);
    for(const auto &s:skills)if(s.identity()==key)return {key,SkillSourceKind::Active,true,false,s.maxLevel};
    for(const auto &s:passives)if(s.identity()==key)return {key,SkillSourceKind::Passive,true,s.key!="armormasterylight",s.maxLevel};
    return {key,SkillSourceKind::Unknown,false,false,0};
}
std::vector<SkillKey> World::learningSkillKeys() const {
    std::vector<SkillKey> result;
    if(experimentalRuntime_)for(const auto &[key,row]:experimentalRuntime_->plan().skills)result.push_back(key);
    else {
        const auto add=[&](SkillKey key){if(std::find(result.begin(),result.end(),key)==result.end())result.push_back(key);};
        for(const auto &s:skills)add(s.identity());for(const auto &s:passives)add(s.identity());
    }
    return result;
}
Json World::skillLearningConsumerMetadata(SkillKey key) const {
    const auto policy=runtimeSkillPolicy(key);
    Json result={{"key",key.json()},{"implemented",policy.implemented},{"passive_consumer",policy.passiveConsumerBound},
        {"runtime_maximum",policy.maximumLevel},{"classification","inferred-current1031-existing-consumer-bridge"},
        {"native_controller_complete",false},{"learning_authority","SkillLearningService + normal/test-effective ledger"},
        {"mp_cd_authority",experimentalRuntime_?"ExperimentalCharacterRuntime":"existing Swordman controller"}};
    if(experimentalRuntime_) {
        const auto &plan=experimentalRuntime_->plan();const auto row=plan.skills.find(key);
        if(row!=plan.skills.end())result["source"]=row->second.source.json();
        const auto action=plan.sourceSkillActions.find(key);
        if(policy.implemented&&action!=plan.sourceSkillActions.end()) {
            result["consumer"]="SourceSkillAction -> ExperimentalCharacterRuntime -> ExperimentalWorldAdapter";
            result["source_action"]=action->second.snapshot();
            if(key==SkillKey{1,5}) {
                result["normal_learning_consumer_bound"]=true;
                result["normal_policy"]="reviewed-current1031-fighter-upper-normal-base-inferred-beta-v1";
                result["audio_policy"]="inferred-current1031-fighter-upper-two-phase-audio-v1";
                result["source_descriptor_evidence_scope"]="immutable initial reconstruction; current normal admission is this enclosing metadata";
                result["source_initial_level"]=1;result["tp_163_normal_admitted"]=false;
                result["normal_optional_modifier_policy"]="preserve learned163; deny base release before cost until actual TP consumers close";
                const auto effective=debugOverrides_.enabled?skillTestOverlay_.effectiveState(skillState_,nowMs()):skillState_;
                result["normal_release_blocker"]=fighterUpperNormalBlocker(effective);
                result["native_caller_protection_carry_and_formula_verified"]=false;
            }
            if(key==SkillKey{2,4}) {
                // The saved source descriptor is deliberately immutable. Its
                // historic evidence is not a current admission flag.
                result["normal_learning_consumer_bound"]=true;
                result["normal_policy"]="reviewed-current1031-knee-normal-inferred-beta-v1";
                result["cast_audio_policy"]="inferred-current1031-knee-cast-audio-v1";
                result["source_descriptor_evidence_scope"]="immutable initial source reconstruction; current execution/admission is this enclosing metadata";
                result["tp_168_normal_admitted"]=false;
                result["native_cast_caller_and_phase_verified"]=false;
            }
            if(key==SkillKey{3,12}||key==SkillKey{3,4}) {
                result["normal_learning_consumer_bound"]=true;
                result["source_descriptor_evidence_scope"]="immutable source reconstruction; normal admission is this metadata";
                result["normal_policy"]="reviewed-current1031-mage-body-normal-inferred-beta-v1";
                result["normal_optional_modifier_policy"]="preserve learned210/212; diagnose each unsupported own TP before its base fee";
                result["tp_normal_admitted"]=false;
                const auto effective=debugOverrides_.enabled?skillTestOverlay_.effectiveState(skillState_,nowMs()):skillState_;
                result["normal_release_blocker"]=mageBodyNormalBlocker(effective,key);
                if(key.skillId==12) {
                    result["source_initial_level"]=1;
                    result["sidestep_policy"]=action->second.bodySidestep->snapshot();
                    result["native_state_distance_speed_and_lift_formula_verified"]=false;
                }
            }
            if(key==SkillKey{4,1}) {
                result["normal_learning_consumer_bound"]=true;
                result["normal_policy"]="reviewed-current1031-priest-upper-normal-inferred-beta-v1";
                result["source_initial_level"]=1;result["tp_210_normal_admitted"]=false;
                result["normal_optional_modifier_policy"]="preserve learned TP210 and Avenger123; diagnose unsupported modifier before cost";
                const auto effective=debugOverrides_.enabled?skillTestOverlay_.effectiveState(skillState_,nowMs()):skillState_;
                result["normal_release_blocker"]=priestUpperNormalBlocker(effective);
                result["willdriver_policy"]="No normal mode13 consumer can deploy; learned13/Blue Monk identity alone does not deny Upper";
            }
            if(key==SkillKey{8,26}) {
                result["normal_learning_consumer_bound"]=true;
                result["normal_policy"]="reviewed-current1031-watercannon-normal-base-inferred-beta-v1";
                result["source_descriptor_evidence_scope"]="immutable source reconstruction; current normal admission is this enclosing metadata";
                result["tp_236_normal_admitted"]=false;result["elemental_chain_51_normal_admitted"]=false;
                result["source_initial_level"]=1;
                result["normal_optional_modifier_policy"]="preserve learned 236/51; deny base release with a concrete diagnostic until their consumers close";
                const auto effective=debugOverrides_.enabled?skillTestOverlay_.effectiveState(skillState_,nowMs()):skillState_;
                result["normal_release_blocker"]=waterCannonNormalBlocker(effective);
                result["native_cancel_and_full_modifier_chain_verified"]=false;
            }
        }else if(policy.implemented&&key.jobId==5) {
            result["consumer"]=policy.kind==SkillSourceKind::Passive?"female_gunner_modifiers.cpp / actual runtime cancel consumer":
                "experimental_character.cpp -> female_gunner_world.cpp dedicated admitted entrypoint";
        }else if(key==SkillKey{1,5})result["blocker"]="Exact reviewed current1031 female Upper own body descriptor unavailable";
        else if(key==SkillKey{1,163})result["blocker"]="Upper TP163 speed/damage consumers remain unsupported; source requirement5/10 retained";
        else if(key==SkillKey{2,4})result["blocker"]="Exact reviewed current1031 Knee source descriptor is unavailable";
        else if(key==SkillKey{3,12})result["blocker"]="Exact current1031 Mage Upper source body/equipment/movement descriptor unavailable";
        else if(key==SkillKey{3,210}||key==SkillKey{3,212})result["blocker"]="Own Mage TP speed/damage consumers remain unsupported; source requirements and legacy learned ledger retained";
        else if(key==SkillKey{4,1})result["blocker"]="Exact reviewed current1031 Priest Upper source descriptor unavailable";
        else if(key==SkillKey{4,210})result["blocker"]="Upper TP damage columns0/2 actual normal consumer remains unsupported";
        else if(key==SkillKey{8,26})result["blocker"]="Exact reviewed current1031 WaterCannon moving/impact source descriptor is unavailable";
        else if(key==SkillKey{8,236})result["blocker"]="WaterCannon TP damage/size actual consumer remains unsupported; source prerequisite26/10 is retained";
        else if(key==SkillKey{8,51})result["blocker"]="Elemental Chain nonstacking three-element timed status consumer remains unsupported; source awakening qualification is retained";
        else if(key==SkillKey{2,168})result["blocker"]="Own source TP preview consumer remains separate; normal TP purchase/use admission has not been accepted";
        else if(key==SkillKey{5,8}||key==SkillKey{5,41})result["blocker"]="Required qualification/charging passive has no reviewed actual consumer";
        else result["blocker"]="Source row retained; this family is outside the explicitly reviewed normal bridge admission set";
    }
    return result;
}
// This definition avoids touching parent's independently owned service source.
SkillLearningBudget SkillLearningService::testBudget(const CharacterSkillState &normal,
    const SkillLearningTestOverlay &overlay,int effectiveCharacterLevel,int64_t nowMs) const {
    (void)budget(normal,effectiveCharacterLevel,nowMs);(void)overlay.effectiveState(normal,nowMs);
    auto result=baseBudget(effectiveCharacterLevel);
    result.revision=overlay.revision;result.spentSp=overlay.spentSp;result.spentTp=overlay.spentTp;
    result.remainingSp=result.earnedSp-result.spentSp;result.remainingTp=result.earnedTp-result.spentTp;
    result.trace.push_back({{"pool","isolated_test_learning"},{"normal_budget_unchanged",true}});return result;
}
SkillLearningBudget World::skillLearningBudget(bool testLearning,int normalLevel) const {
    return testLearning?skillLearning().testBudget(skillState_,skillTestOverlay_,characterLevel,nowMs()):
        skillLearning().budget(skillState_,normalLevel,nowMs());
}
SkillLearningBatch SkillLearningService::quoteBatch(const CharacterSkillState &normal,const SkillLearningTestOverlay *overlay,
    int characterLevel,const std::vector<RuntimeSkillPolicy> &policies,int64_t nowMs) const {
    SkillLearningBatch result;
    result.budget=budget(normal,characterLevel,nowMs);
    auto effective=normal;
    if(overlay) {
        effective=overlay->effectiveState(normal,nowMs);
        result.budget=baseBudget(characterLevel);result.budget.revision=overlay->revision;
        result.budget.spentSp=overlay->spentSp;result.budget.spentTp=overlay->spentTp;
        result.budget.remainingSp=result.budget.earnedSp-result.budget.spentSp;
        result.budget.remainingTp=result.budget.earnedTp-result.budget.spentTp;
        result.budget.trace.push_back({{"pool","isolated_test_learning"},{"normal_budget_unchanged",true}});
    }
    result.quotes.reserve(policies.size());
    for(const auto &policy:policies) {
        // quoteWithBudget owns the existing precise learning gate/error logic.
        // Catalog lookup failure is isolated to this source row.
        try {result.quotes.push_back(quoteWithBudget(effective,characterLevel,policy,
            catalog_.skillDefinition(policy.key),0,result.budget));}
        catch(const std::exception &e) {
            SkillLearningQuote rejected;rejected.key=policy.key;rejected.gate=SkillLearningGate::SourceInvalid;
            rejected.message="技能来源无效";rejected.error=e.what();rejected.budget=result.budget;
            result.quotes.push_back(std::move(rejected));
        }
    }
    return result;
}
SkillLearningBatch World::quoteSkillLearningBatch(bool testLearning,int normalLevel) const {
    std::vector<RuntimeSkillPolicy> policies;
    for(const auto key:learningSkillKeys())policies.push_back(runtimeSkillPolicy(key));
    return skillLearning().quoteBatch(skillState_,testLearning?&skillTestOverlay_:nullptr,
        testLearning?characterLevel:normalLevel,policies,nowMs());
}
SkillRuntimeProjectionContext World::currentSkillProjectionContext(bool test,int normalLevel,int effectiveLevel) const {
    SkillRuntimeProjectionContext context;
    context.normalLevel=normalLevel;context.effectiveLevel=effectiveLevel;context.testLearning=test;
    context.previewEnabled=experimentalSkillPreviewEnabled_;context.nowMs=nowMs();context.runtime=experimentalRuntime_.get();
    if(normalSkillConfiguration_)context.normalPreferences=&*normalSkillConfiguration_;
    else if(experimentalRuntime_)context.normalPreferences=&experimentalRuntime_->configuration();
    if(testSkillConfiguration_)context.testPreferences=&*testSkillConfiguration_;
    if(experimentalSkillPreviewEnabled_&&experimentalRuntime_)context.previewPreferences=&experimentalRuntime_->configuration();
    else if(previewSkillConfiguration_)context.previewPreferences=&*previewSkillConfiguration_;
    if(experimentalRuntime_)context.appearance=&characterAppearance();
    return context;
}
std::unique_ptr<PreparedSkillRuntime> World::prepareSkillRuntime(CharacterSkillState normal,
    SkillLearningTestOverlay overlay,SkillRuntimeProjectionContext context) const {
    if(skillProjectionRevision_==UINT64_MAX)throw std::overflow_error("Skill projection revision exhausted");
    if(context.nowMs<0)context.nowMs=nowMs();
    if(context.normalLevel<1||context.normalLevel>99||context.effectiveLevel<1||context.effectiveLevel>99)
        throw std::invalid_argument("Skill projection level outside source growth policy");
    if(!context.restoring&&experimentalRuntime_&&
        (context.previewEnabled!=experimentalSkillPreviewEnabled_||context.testLearning!=debugOverrides_.enabled||
         context.effectiveLevel!=characterLevel)&&!skillLearningProjectionReady())
        throw std::invalid_argument("Finish active source effects or change room before switching skill projections");
    auto p=std::make_unique<PreparedSkillRuntime::Data>();p->owner=this;p->identity=normal.identity();p->beforeIdentity=identity_;
    p->nowMs=context.nowMs;p->beforeNowMs=nowMs();p->beforeRevision=skillProjectionRevision_;
    p->beforeAttributeRevision=attributeRevision_;
    p->normalLevel=context.normalLevel;p->effectiveLevel=context.effectiveLevel;
    p->testLearning=context.testLearning;p->previewEnabled=context.previewEnabled;p->restoring=context.restoring;
    p->beforePreview=experimentalSkillPreviewEnabled_;p->beforeDebug=debugOverrides_.enabled;p->beforeDebugLevel=debugOverrides_.level;
    p->beforeNormal=skillState_;p->beforeOverlay=skillTestOverlay_;
    if(experimentalRuntime_)p->beforeConfiguration=experimentalRuntime_->configuration();
    const bool ledger=normal.snapshot(context.nowMs).contains("learning");
    if(usesSourceGrowth()&&!ledger)throw std::invalid_argument("Normal skill runtime requires initialized source learning ledger");
    if(ledger)(void)skillLearning().budget(normal,context.normalLevel,context.nowMs);
    if(context.testLearning)overlay.upgradeNormalBinding(normal,context.nowMs);
    const auto effective=context.testLearning?overlay.effectiveState(normal,context.nowMs):normal;
    p->normal=std::move(normal);p->overlay=std::move(overlay);
    if(p->identity.jobId!=0) {
        const auto *runtime=context.runtime;
        if(!runtime||!(runtime->plan().identity==p->identity))throw std::invalid_argument("Skill projection requires exact target runtime");
        const auto &plan=runtime->plan();p->plan=&plan;
        p->normalConfiguration=learnedConfiguration(plan,context.normalPreferences,p->normal,skillLearning(),context.normalLevel);
        p->testConfiguration=learnedConfiguration(plan,context.testPreferences?context.testPreferences:&*p->normalConfiguration,
            context.testLearning?effective:p->normal,skillLearning(),context.testLearning?context.effectiveLevel:context.normalLevel);
        if(context.previewPreferences)p->previewConfiguration=*context.previewPreferences;
        if(context.previewEnabled&&!p->previewConfiguration)p->previewConfiguration=runtime->configuration();
        if(context.previewEnabled&&context.testLearning&&plan.identity.jobId==1) {
            // Explicit isolated fighter preview. Source-action registration is
            // the only automatic caller: never turn an unknown skill into an
            // Upper/basic template just because it has a name or icon.
            size_t nextSlot=0;
            for(const auto &[key,row]:plan.skills)if(row.kind==SkillSourceKind::Active&&plan.sourceSkillActions.count(key)&&
                !p->previewConfiguration->binding(key)) {
                try {
                    p->previewConfiguration->configureSourceSkillAction(key,1,plan);
                    const auto &slots=p->previewConfiguration->slots();
                    if(std::find(slots.begin(),slots.end(),std::optional<SkillKey>(key))==slots.end()) {
                        while(nextSlot<slots.size()&&slots[nextSlot])++nextSlot;
                        if(nextSlot<slots.size())p->previewConfiguration->assignSlot(nextSlot++,key,plan);
                    }
                }catch(const std::exception &){/* Per-row gap remains visible in the preview UI. */}
            }
        }
        p->currentConfiguration=context.previewEnabled?*p->previewConfiguration:
            context.testLearning?*p->testConfiguration:*p->normalConfiguration;
        // Read/decode selected ANI/effect images before save. Equipped volumes
        // and target-dependent script admission keep the per-release preflight.
        const auto fallbackAppearance=context.appearance?std::optional<CharacterAppearance>{}:
            std::optional<CharacterAppearance>{defaultCharacterAppearance(pvf_,characters_,p->identity)};
        const auto &appearance=context.appearance?*context.appearance:*fallbackAppearance;
        if(!(appearance.identity==p->identity))throw std::invalid_argument("Prepared learned appearance identity differs");
        std::set<std::tuple<std::string,std::array<int,2>,bool,std::string>> visited;
        const auto preflight=[&](const auto &self,const std::string &path,std::array<int,2> variation,bool body,size_t depth,const std::string &treePolicy)->void {
            if(path.empty()||!visited.emplace(path,variation,body,treePolicy).second)return;
            if(depth>12||visited.size()>4096)throw std::length_error("Learned skill visual closure budget exhausted");
            const auto animation=assets_.animation(path);
            if(animation->frames.empty())throw std::invalid_argument("Empty learned skill animation: "+path);
            for(const auto &frame:animation->frames)if(!frame.image.empty()) {
                const auto image=appearanceImage(frame.image,variation,body);
                if(image.find('%')!=std::string::npos)throw std::invalid_argument("Unresolved learned skill image pattern: "+image);
                assets_.pixels(image,frame.imageFrame);
            }
            const auto events=animationEffectEvents(pvf_,assets_,path,treePolicy);
            if(!treePolicy.empty()&&!events.diagnostics.empty())
                throw std::invalid_argument("Learned WaterCannon exact source-tree preflight failed: "+path+": "+events.diagnostics.dump());
            for(const auto &event:events.events)if(event.kind!=EffectEventKind::Remove)self(self,event.animation,{0,0},false,depth+1,treePolicy);
        };
        const auto preflightBody=[&](const std::string &path) {
            const auto *motion=appearanceBodyMotion(appearance,path);
            if(!motion)throw std::invalid_argument("Learned skill lacks exact CHR/appearance binding: "+path);
            preflight(preflight,path,{appearance.bodyVariation(),appearance.bodyVariation()},true,0,{});
            for(const auto &layer:appearance.orderedLayers()) {
                const auto child=appearanceLayerMotion(layer,*motion);if(child.empty())continue;
                preflight(preflight,child,layer.variation,false,0,{});
            }
        };
        for(const auto &[key,row]:plan.skills) {
            const auto *binding=p->currentConfiguration->binding(key);if(!binding)continue;
            // Fighter source previews defer visual closure to the actual
            // release/diagnostic path. One missing image must not prevent
            // switching into the whole skill test catalog.
            if(context.previewEnabled&&context.testLearning&&plan.identity.jobId==1)continue;
            preflightBody(binding->motion.source.memberPath);
            const auto source=plan.sourceSkillActions.find(key);
            if(source!=plan.sourceSkillActions.end()) {
                if(source->second.kind==SourceSkillActionKind::BodyAttack)preflightBody(source->second.animation.memberPath);
                else if(source->second.movingImpact) {
                    if(!(key==SkillKey{8,26})||std::string(source->second.movingImpact->visualPolicy)!="inferred-current1031-watercannon-tree-v1")
                        throw std::invalid_argument("Unreviewed learned moving-impact source-tree policy");
                    const auto &moving=*source->second.movingImpact;
                    preflight(preflight,source->second.animation.memberPath,{0,0},false,0,moving.visualPolicy);
                    preflight(preflight,moving.impactAnimation.memberPath,{0,0},false,0,moving.visualPolicy);
                }
                else preflight(preflight,source->second.animation.memberPath,{0,0},false,0,{});
                for(const auto &layer:source->second.bodyLayers)preflight(preflight,layer.source.memberPath,{0,0},false,0,{});
            }
            const auto female=plan.femaleGunnerSkills.find(key);
            if(female!=plan.femaleGunnerSkills.end()) {
                for(const auto &stage:female->second.stages) {
                    const auto *motion=plan.motion(stage.motionTag,stage.motionSlot);
                    if(!motion)throw std::invalid_argument("Learned female source stage is missing");
                    preflightBody(motion->source.memberPath);
                }
                for(const auto &effect:female->second.effectSources)preflight(preflight,effect.memberPath,{0,0},false,0,{});
            }
        }
    }else {
        for(const auto &s:compatibilitySkillView(p->identity,false))p->activeLevels.push_back(effective.learnedLevel(s.identity()));
        for(const auto &s:compatibilitySkillView(p->identity,true))p->passiveLevels.push_back(effective.learnedLevel(s.identity()));
    }
    return std::unique_ptr<PreparedSkillRuntime>(new PreparedSkillRuntime(std::move(p)));
}
std::unique_ptr<PreparedSkillRuntime> World::prepareSkillLedger(CharacterSkillState normal) const {
    auto context=currentSkillProjectionContext(debugOverrides_.enabled,normalCharacterLevel(),characterLevel);
    return prepareSkillRuntime(std::move(normal),skillTestOverlay_,context);
}
void World::publishPreparedSkillRuntime(PreparedSkillRuntime &prepared) {
    if(!prepared.data_)throw std::invalid_argument("Prepared skill runtime already consumed");auto &p=*prepared.data_;
    if(p.owner!=this||!(identity_==p.identity)||nowMs()!=p.nowMs||
        (p.plan&&(!experimentalRuntime_||&experimentalRuntime_->plan()!=p.plan)))
        throw std::invalid_argument("Prepared skill runtime world identity/time/source plan differs");
    if(!p.restoring&&(skillProjectionRevision_!=p.beforeRevision||attributeRevision_!=p.beforeAttributeRevision||!(identity_==p.beforeIdentity)||nowMs()!=p.beforeNowMs||
        experimentalSkillPreviewEnabled_!=p.beforePreview||debugOverrides_.enabled!=p.beforeDebug||debugOverrides_.level!=p.beforeDebugLevel||
        !skillState_.sameRuntimeState(p.beforeNormal)||!sameOverlay(skillTestOverlay_,p.beforeOverlay)||
        (p.beforeConfiguration&&(!experimentalRuntime_||!experimentalRuntime_->configuration().sameConfiguration(*p.beforeConfiguration)))))
        throw std::invalid_argument("World skill view changed while its durable generation awaited publication");
    if(skills.size()!=p.activeLevels.size()||passives.size()!=p.passiveLevels.size())throw std::invalid_argument("Prepared compatibility shape differs");
    static_assert(std::is_nothrow_move_assignable_v<CharacterSkillState>);
    static_assert(std::is_nothrow_move_assignable_v<SkillLearningTestOverlay>);
    static_assert(std::is_nothrow_move_assignable_v<ExperimentalSkillConfiguration>);
    static_assert(std::is_nothrow_move_assignable_v<std::optional<ExperimentalSkillConfiguration>>);
    // Only frozen value moves/clears after this line: no source I/O, JSON
    // serialization, vector growth, source callbacks or binding reconstruction.
    skillState_=std::move(p.normal);skillTestOverlay_=std::move(p.overlay);
    normalSkillConfiguration_=std::move(p.normalConfiguration);testSkillConfiguration_=std::move(p.testConfiguration);
    previewSkillConfiguration_=std::move(p.previewConfiguration);experimentalSkillPreviewEnabled_=p.previewEnabled;
    if(p.currentConfiguration)experimentalRuntime_->configuration()=std::move(*p.currentConfiguration);
    for(size_t i=0;i<skills.size();++i) {
        const int projected=p.activeLevels[i];
        // Skill Lab rows are appended by the mapping table and have no durable
        // ledger record, so a serialized state legitimately projects them as
        // zero. Keep the lab's unlocked level rather than turning every mapped
        // skill back into "unlearned" on the next publication.
        if(skillLabUnlocked_&&projected==0)continue;
        skills[i].level=projected;
    }
    for(size_t i=0;i<passives.size();++i)passives[i].level=p.passiveLevels[i];
    normalCharacterLevel_=p.normalLevel;++skillProjectionRevision_;skillCostCache_.clear();prepared.data_.reset();
}
void World::projectSkillLevels(){if(hasLearningLedger()){auto p=prepareSkillLedger(skillState_);publishPreparedSkillRuntime(*p);}}
void World::publishSkillLedger(CharacterSkillState normal){auto p=prepareSkillLedger(std::move(normal));publishPreparedSkillRuntime(*p);}
void World::enforceLearnedSkillProjection() {
    if(experimentalSkillPreviewEnabled_||!experimentalRuntime_)return;
    const auto &canonical=debugOverrides_.enabled?testSkillConfiguration_:normalSkillConfiguration_;
    if(canonical&&!experimentalRuntime_->configuration().sameConfiguration(*canonical)) {
        auto frozen=*canonical;experimentalRuntime_->configuration()=std::move(frozen);
    }
}
bool World::skillLearningProjectionReady() const noexcept {
    return (!experimentalRuntime_||experimentalRuntime_->neutralReactionReady())&&
        (!femaleGunnerWorld_||femaleGunnerWorld_->skillProjectionReady());
}
Operation World::assignLearnedSkillSlot(size_t slot,std::optional<SkillKey> key) {
    try {
        if(experimentalSkillPreviewEnabled_||!hasLearningLedger()||combat||player.dead||player.hp<=0||
            active_>=0||(experimentalRuntime_&&experimentalRuntime_->attacking()))return {false,"请在正常/测试学习模式的城镇静止时配置快捷键",0,0};
        if(key) {
            const auto policy=runtimeSkillPolicy(*key);const auto gate=skillUseEligibility(*key);
            if(!policy.implemented||policy.kind!=SkillSourceKind::Active||!gate.allowed())return {false,"技能没有有效已学习的实际释放消费者",0,0};
        }
        if(!experimentalRuntime_) {
            if(skillProjectionRevision_==UINT64_MAX)return {false,"技能投影修订号已耗尽",0,0};
            if(slot>=bindings.size())return {false,"快捷键槽超出范围",0,0};
            int index=-1;
            if(key)for(size_t i=0;i<skills.size();++i)if(skills[i].identity()==*key){index=int(i);break;}
            if(key&&index<0)return {false,"技能不属于当前实际控制器",0,0};
            auto candidate=bindings;
            if(index>=0)for(auto &bound:candidate)if(bound==index)bound=-1;
            candidate[slot]=index;bindings=candidate;++skillProjectionRevision_;return {true,"快捷键已配置",0,0};
        }
        auto context=currentSkillProjectionContext(debugOverrides_.enabled,normalCharacterLevel(),characterLevel);
        auto preferences=debugOverrides_.enabled&&testSkillConfiguration_?*testSkillConfiguration_:
            normalSkillConfiguration_?*normalSkillConfiguration_:experimentalRuntime_->configuration();
        if(key)for(size_t i=0;i<preferences.slots().size();++i)
            if(preferences.slots()[i]&&*preferences.slots()[i]==*key)preferences.assignSlot(i,std::nullopt,experimentalRuntime_->plan());
        preferences.assignSlot(slot,key,experimentalRuntime_->plan());
        if(debugOverrides_.enabled)context.testPreferences=&preferences;else context.normalPreferences=&preferences;
        auto p=prepareSkillRuntime(skillState_,skillTestOverlay_,context);publishPreparedSkillRuntime(*p);return {true,"快捷键已配置",0,0};
    }catch(const std::exception &e){return {false,std::string("快捷键配置失败: ")+e.what(),0,0};}
}
Operation World::setExperimentalSkillPreviewEnabled(bool enabled) {
    try {
        if(!experimentalRuntime_||combat||player.dead||player.hp<=0||active_>=0||!skillLearningProjectionReady())
            return {false,"请在城镇静止且技能/持续效果结束后切换预览；换图可清理当前效果",0,0};
        if(enabled==experimentalSkillPreviewEnabled_)return {true,"技能模式未变化",0,0};
        if(!hasLearningLedger()) {
            if(skillProjectionRevision_==UINT64_MAX)return {false,"技能投影修订号已耗尽",0,0};
            if(!enabled){ExperimentalSkillConfiguration blank(experimentalRuntime_->plan());experimentalRuntime_->configuration()=std::move(blank);}
            experimentalSkillPreviewEnabled_=enabled;++skillProjectionRevision_;return {true,"显式无账本预览fixture模式已切换",0,0};
        }
        auto context=currentSkillProjectionContext(debugOverrides_.enabled,normalCharacterLevel(),characterLevel);context.previewEnabled=enabled;
        auto p=prepareSkillRuntime(skillState_,skillTestOverlay_,context);publishPreparedSkillRuntime(*p);
        return {true,enabled?(identity_.jobId==1&&debugOverrides_.enabled?
            "女格斗全源技能测试已开启；可用源动作已配置，缺失链可手动选择。正常账本未变":
            "已进入独立手动技能预览，正常学习账本保持不变"):"已恢复有效已学习技能",0,0};
    }catch(const std::exception &e){return {false,std::string("技能模式切换失败: ")+e.what(),0,0};}
}
Json World::normalSkillConfigurationSnapshot() const {
    if(normalSkillConfiguration_)return normalSkillConfiguration_->snapshot();
    return experimentalRuntime_?ExperimentalSkillConfiguration(experimentalRuntime_->plan()).snapshot():Json();
}
Json World::manualSkillPreviewSnapshot() const {
    if(experimentalSkillPreviewEnabled_&&experimentalRuntime_)return experimentalRuntime_->configuration().snapshot();
    return previewSkillConfiguration_?previewSkillConfiguration_->snapshot():Json();
}
Json World::testSkillConfigurationSnapshot() const {
    return testSkillConfiguration_?testSkillConfiguration_->snapshot():Json();
}
std::map<SkillKey,int> World::effectiveFemaleGunnerLevels() const {
    if(!experimentalRuntime_||identity_.jobId!=5)return {};
    if(experimentalSkillPreviewEnabled_)return experimentalRuntime_->configuration().femaleGunnerLevels();
    const auto &configuration=debugOverrides_.enabled?testSkillConfiguration_:normalSkillConfiguration_;
    return configuration?configuration->femaleGunnerLevels():std::map<SkillKey,int>{};
}
SkillLearningQuote World::quoteSkillLearning(SkillKey key,int normalLevel) const {
    return skillLearning().quote(skillState_,normalLevel,runtimeSkillPolicy(key),0,nowMs());
}
SkillLearningQuote World::quoteTestSkillLearning(SkillKey key) const {
    return skillLearning().quoteTest(skillState_,skillTestOverlay_,characterLevel,runtimeSkillPolicy(key),0,nowMs());
}
Operation World::learnTestSkill(const SkillLearningRequest &request) {
    if(!usesSourceGrowth()||!debugOverrides_.enabled||experimentalSkillPreviewEnabled_||combat||player.dead||active_>=0||
        (experimentalRuntime_&&experimentalRuntime_->attacking()))return {false,"请在隔离测试学习模式的城镇静止时学习测试技能",0,0};
    auto p=skillLearning().prepareTest(skillState_,skillTestOverlay_,characterLevel,runtimeSkillPolicy(request.key),request,nowMs());
    lastSkillLearningTrace_=p.quote.json();lastSkillLearningTrace_["receipt"]=p.receipt;lastSkillLearningTrace_["replayed"]=p.replayed;
    if(!p.ok)return {false,p.quote.message,0,0};
    try {restoreSkillTestOverlay(std::move(p.overlay));}catch(const std::exception &e){return {false,std::string("测试技能来源准备失败: ")+e.what(),0,0};}
    return {true,p.replayed?"测试技能学习已提交":"测试技能学习成功",0,0};
}
void World::resetTestSkillLearning(){restoreSkillTestOverlay({});}
void World::restoreSkillTestOverlay(SkillLearningTestOverlay overlay) {
    auto context=currentSkillProjectionContext(debugOverrides_.enabled,normalCharacterLevel(),characterLevel);
    auto p=prepareSkillRuntime(skillState_,std::move(overlay),context);publishPreparedSkillRuntime(*p);
}
SkillLearningUseEligibility World::skillUseEligibility(SkillKey key) const {
    const auto effective=debugOverrides_.enabled?skillTestOverlay_.effectiveState(skillState_,nowMs()):skillState_;
    auto result=skillLearning().useEligibility(effective,key,characterLevel);
    if(result.allowed()&&key==SkillKey{1,5}&&!experimentalSkillPreviewEnabled_) {
        const auto blocker=fighterUpperNormalBlocker(effective);
        if(!blocker.empty()) {
            result.gate=SkillLearningGate::SpecialQualification;result.error=blocker;
            result.trace.push_back({{"policy","reviewed-current1031-fighter-upper-normal-base-inferred-beta-v1"},
                {"unsupported_learned_tp_163",effective.learnedLevel({1,163})},
                {"normal_ledger_preserved",true},{"base_release_blocked_before_cost",true}});
        }
    }
    if(result.allowed()&&key==SkillKey{8,26}&&!experimentalSkillPreviewEnabled_) {
        const auto blocker=waterCannonNormalBlocker(effective);
        if(!blocker.empty()) {
            result.gate=SkillLearningGate::SpecialQualification;result.error=blocker;
            result.trace.push_back({{"policy","reviewed-current1031-watercannon-normal-base-inferred-beta-v1"},
                {"unsupported_learned_tp_236",effective.learnedLevel({8,236})},
                {"unsupported_learned_elemental_51",effective.learnedLevel({8,51})},
                {"normal_ledger_preserved",true},{"base_release_blocked_before_cost",true}});
        }
    }
    if(result.allowed()&&(key==SkillKey{3,12}||key==SkillKey{3,4})&&!experimentalSkillPreviewEnabled_) {
        const auto blocker=mageBodyNormalBlocker(effective,key);
        if(!blocker.empty()) {
            const SkillKey tp{3,key.skillId==12?210:212};
            result.gate=SkillLearningGate::SpecialQualification;result.error=blocker;
            result.trace.push_back({{"policy","reviewed-current1031-mage-body-normal-inferred-beta-v1"},
                {"unsupported_learned_tp",tp.json()},{"learned_level",effective.learnedLevel(tp)},
                {"normal_ledger_preserved",true},{"base_release_blocked_before_cost",true}});
        }
    }
    if(result.allowed()&&key==SkillKey{4,1}&&!experimentalSkillPreviewEnabled_) {
        const auto blocker=priestUpperNormalBlocker(effective);
        if(!blocker.empty()) {
            result.gate=SkillLearningGate::SpecialQualification;result.error=blocker;
            result.trace.push_back({{"policy","reviewed-current1031-priest-upper-normal-inferred-beta-v1"},
                {"unsupported_learned_tp_210",effective.learnedLevel({4,210})},
                {"unsupported_avenger_123",effective.identity().growtype==4?effective.learnedLevel({4,123}):0},
                {"normal_ledger_preserved",true},{"base_release_blocked_before_cost",true}});
        }
    }
    return result;
}
Skill World::effectivePassive(const Skill &skill) const {
    Skill effective=skill;if(usesSourceGrowth()&&hasLearningLedger()&&!skillUseEligibility(skill.identity()).allowed())effective.level=0;return effective;
}
} // namespace dnf
