#include "dnf/skill_learning.hpp"
#include <limits>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
struct LearningFailure : std::runtime_error {
    SkillLearningGate gate;
    LearningFailure(SkillLearningGate g, const std::string &text) : std::runtime_error(text), gate(g) {}
};
[[noreturn]] void fail(SkillLearningGate gate, const std::string &text) { throw LearningFailure(gate,text); }
int64_t integer(const Json &value, const std::string &name, int64_t maximum = std::numeric_limits<int64_t>::max()) {
    if (!value.is_number_integer() || (value.is_number_unsigned() && value.get<uint64_t>() > uint64_t(maximum)))
        fail(SkillLearningGate::InvalidLedger,"Invalid integer: " + name);
    const int64_t result = value.get<int64_t>();
    if (result < 0 || result > maximum) fail(SkillLearningGate::InvalidLedger,"Out-of-range integer: " + name);
    return result;
}
int intValue(const Json &value, const std::string &name) {
    return int(integer(value,name,std::numeric_limits<int>::max()));
}
int64_t add(int64_t a, int64_t b) {
    if (a < 0 || b < 0 || a > std::numeric_limits<int64_t>::max()-b)
        fail(SkillLearningGate::InvalidLedger,"Skill point overflow");
    return a+b;
}
SkillKey keyValue(const Json &value) {
    if (!value.is_object()) fail(SkillLearningGate::InvalidLedger,"Skill key is not an object");
    return {intValue(value.at("job_id"),"job_id"),intValue(value.at("skill_id"),"skill_id")};
}
std::string textValue(const Json &value, const std::string &name) {
    if (!value.is_string()) fail(SkillLearningGate::InvalidLedger,"Invalid text: " + name);
    return value.get<std::string>();
}
bool validId(const std::string &id) {
    if (id.empty() || id.size()>160) return false;
    for (unsigned char c : id) if (c<32 || c==127) return false;
    return true;
}
const char *message(SkillLearningGate gate) {
    switch (gate) {
    case SkillLearningGate::Accepted:return "学习成功";
    case SkillLearningGate::Uninitialized:return "技能账本尚未初始化";
    case SkillLearningGate::WrongCharacter:return "技能不属于当前职业";
    case SkillLearningGate::MissingImplementation:return "技能行为尚未接入";
    case SkillLearningGate::PassiveHasNoConsumer:return "被动效果尚未接入";
    case SkillLearningGate::UnknownKind:return "技能类型尚未确定";
    case SkillLearningGate::SourceExcluded:return "当前转职或觉醒不能学习";
    case SkillLearningGate::InvalidLevel:return "技能等级已达上限或目标无效";
    case SkillLearningGate::CharacterLevel:return "人物等级不足";
    case SkillLearningGate::Prerequisite:return "前置技能等级不足";
    case SkillLearningGate::SpecialQualification:return "特殊学习条件未满足";
    case SkillLearningGate::InsufficientPoints:return "技能点不足";
    case SkillLearningGate::BudgetConflict:return "技能点账本存在冲突";
    case SkillLearningGate::StaleRevision:return "技能配置已变化，请重新选择";
    case SkillLearningGate::InvalidRequest:return "学习请求无效";
    case SkillLearningGate::RequestConflict:return "学习请求编号冲突";
    case SkillLearningGate::NotLearned:return "技能尚未学习";
    case SkillLearningGate::TemporaryLevelIneligible:return "当前有效人物等级不能使用此技能";
    case SkillLearningGate::SourceMismatch:return "技能来源与存档不匹配";
    case SkillLearningGate::InvalidLedger:return "技能账本无法安全恢复";
    case SkillLearningGate::SourceInvalid:return "技能来源无法计算学习条件";
    }
    return "技能学习失败";
}
void reject(SkillLearningQuote &quote, SkillLearningGate gate, const std::string &error = {}) {
    quote.gate=gate; quote.message=message(gate); quote.error=error;
}
Json scriptRef(const Script &script, const std::string &package, const Field *field = nullptr) {
    return {{"package_identity",package},{"member_path",script.path},{"member_sha256",sha256(script.rawBytes)},
        {"byte_offset",field?field->offset:0},{"text_encoding","CP936"}};
}
Json definitionRef(const CharacterSkillDefinition &definition, const ScopedSkillField *field = nullptr) {
    Json ref=definition.source.provenance;
    if (!ref.is_object()) ref=Json::object();
    ref["member_path"]=definition.source.script.path; ref["member_sha256"]=sha256(definition.source.bytes);
    if (field) { ref["byte_offset"]=field->field.offset; ref["ordinal"]=field->ordinal; ref["scope"]=field->scope; }
    return ref;
}
const ScopedSkillField *field(const CharacterSkillDefinition &definition, const std::string &tag, Json &trace,
    bool required = false) {
    const auto values=definition.fieldsInScope(tag,"common");
    if (values.size()>1) fail(SkillLearningGate::SourceInvalid,"Ambiguous common learning field: " + tag);
    if (values.empty()) {
        trace.push_back({{"tag",tag},{"selection","absent"}});
        if (required) fail(SkillLearningGate::SourceInvalid,"Missing common learning field: " + tag);
        return nullptr;
    }
    trace.push_back({{"tag",tag},{"values",values.front()->field.values},{"source",definitionRef(definition,values.front())}});
    return values.front();
}
std::vector<int> numbers(const ScopedSkillField *selected, const std::string &name, bool allowEmpty = false) {
    if (!selected) return {};
    const auto &values=selected->field.values;
    if (!values.is_array() || (!allowEmpty && values.empty())) fail(SkillLearningGate::SourceInvalid,"Empty learning field: " + name);
    std::vector<int> result;
    for (const auto &value:values) {
        try { result.push_back(intValue(value,name)); }
        catch (const std::exception &) { fail(SkillLearningGate::SourceInvalid,"Malformed learning field: " + name); }
    }
    return result;
}
int scalar(const ScopedSkillField *selected, const std::string &name) {
    const auto values=numbers(selected,name);
    if (values.size()!=1) fail(SkillLearningGate::SourceInvalid,"Learning field is not scalar: " + name);
    return values.front();
}
struct SourceRules {
    int maximum=0, purchaseMaximum=0, requiredLevel=0, discount=0;
    int64_t cost=0;
    std::string currency;
    std::vector<std::pair<SkillKey,int>> prerequisites;
};
SourceRules rules(const CharacterSkillDefinition &definition, CharacterIdentity identity, int target,
    const SkillLearningPolicy &policy, Json &trace, bool purchasing) {
    if (identity.jobId!=definition.key.jobId) fail(SkillLearningGate::WrongCharacter,"Source job mismatch");
    if (target<1) fail(SkillLearningGate::InvalidLevel,"Nonpositive target level");
    SourceRules result;
    result.maximum=scalar(field(definition,"[maximum level]",trace,true),"maximum level");
    if (target>result.maximum) fail(SkillLearningGate::InvalidLevel,"Target exceeds all-means maximum");
    const int base=scalar(field(definition,"[required level]",trace,true),"required level");
    const auto *rangeField=field(definition,"[required level range]",trace,target>1);
    const int range=rangeField?scalar(rangeField,"required level range"):0;
    const int64_t required=int64_t(base)+int64_t(range)*(target-1);
    if (required>std::numeric_limits<int>::max()) fail(SkillLearningGate::SourceInvalid,"Required character level overflow");
    result.requiredLevel=int(required);
    trace.push_back({{"policy","inferred-server-required-level-v1"},{"classification","inferred"},
        {"formula","required + range * (target - 1)"},{"target",target},{"required_character_level",result.requiredLevel}});
    // Current1031 authors independent ordinary/awakening eligibility.
    // Ordinary fitness can be empty or absent in awakening-only entries. The two tables are separate source
    // admission dimensions; a normal-table rejection must not preempt the
    // authored second-growtype branch. This is an inferred beta selection
    // policy, not a claim to have recovered native server qualification.
    if (identity.growtype<0 || identity.awakening<0)
        fail(SkillLearningGate::SourceExcluded,"Negative source identity index");
    // Actual Mage WallOfIceEx authors only the secondary fitness dimension.
    // Absent ordinary fitness grants no ordinary eligibility; preserve its
    // absent trace and evaluate a complete explicit secondary pair separately.
    const auto *ordinaryFit=field(definition,"[skill fitness growtype]",trace);
    const auto fitness=numbers(ordinaryFit,"skill fitness growtype",true);
    const auto maxima=numbers(field(definition,"[growtype maximum level]",trace,true),"growtype maximum level");
    std::set<int> seen;
    for (int value:fitness) if (!seen.insert(value).second) fail(SkillLearningGate::SourceInvalid,"Repeated growtype fitness entry");
    if (size_t(identity.growtype)>=maxima.size())
        fail(SkillLearningGate::SourceInvalid,"Missing growtype purchase maximum");
    const int normalMaximum=maxima[size_t(identity.growtype)];
    const bool normalAllowed=ordinaryFit && seen.count(identity.growtype) && normalMaximum>0;
    const auto *secondMax=field(definition,"[second growtype maximum level]",trace);
    const auto *secondFit=field(definition,"[skill fitness second growtype]",trace);
    bool secondAllowed=false;
    int secondMaximum=0;
    if (!ordinaryFit && !secondMax && !secondFit)
        fail(SkillLearningGate::SourceInvalid,"Missing ordinary fitness without an explicit secondary qualification pair");
    if ((secondMax!=nullptr)!=(secondFit!=nullptr))
        fail(SkillLearningGate::SourceInvalid,"Unknown incomplete second-growtype qualification pair");
    if (secondMax) {
        const auto maxima2=numbers(secondMax,"second growtype maximum level");
        const auto fits=numbers(secondFit,"skill fitness second growtype",true);
        // Two columns per ordinary branch are the current1031 contract.
        // A different shape remains unknown instead of truncating/falling back.
        if (maxima2.size()%2 || maxima2.size()/2!=maxima.size())
            fail(SkillLearningGate::SourceInvalid,"Unknown second-growtype row-major table shape");
        std::set<int> stages;
        for (int value:fits) {
            if (value<1 || value>2)
                fail(SkillLearningGate::SourceInvalid,"Unknown source awakening fitness stage");
            if (!stages.insert(value).second)
                fail(SkillLearningGate::SourceInvalid,"Repeated awakening fitness entry");
        }
        if (identity.awakening>2)
            fail(SkillLearningGate::SourceExcluded,"Unsupported source awakening index");
        if (identity.awakening>0) {
            const size_t index=size_t(identity.growtype)*2+size_t(identity.awakening-1);
            if (index>=maxima2.size())
                fail(SkillLearningGate::SourceInvalid,"Missing second-growtype purchase maximum");
            secondMaximum=maxima2[index];
            secondAllowed=stages.count(identity.awakening) && secondMaximum>0;
            trace.push_back({{"row_major_index",index},{"second_purchase_maximum",secondMaximum},
                {"second_fitness_matches",stages.count(identity.awakening)>0}});
        }
    }
    trace.push_back({{"policy","inferred-current1031-independent-learning-dimensions-v1"},{"classification","inferred"},
        {"normal_dimension_allowed",normalAllowed},{"normal_purchase_maximum",normalMaximum},
        {"second_dimension_allowed",secondAllowed},{"selected_dimension",secondAllowed?"second":normalAllowed?"normal":"excluded"},
        {"zero_second_falls_back_only_to_independently_qualified_normal",true},{"native_server_parity",false}});
    if (!normalAllowed && !secondAllowed)
        fail(SkillLearningGate::SourceExcluded,"Neither source learning dimension admits this exact identity");
    result.purchaseMaximum=secondAllowed?secondMaximum:normalMaximum;
    if (purchasing && target>result.purchaseMaximum) fail(SkillLearningGate::InvalidLevel,"Target exceeds purchase ceiling");
    if (!purchasing) return result;
    for (const char *tag:{"[purchase gold]","[purchase gsp]","[purchase item]","[required quest]","[quest]"}) {
        const auto *special=field(definition,tag,trace);
        if (special && !special->field.values.empty())
            fail(SkillLearningGate::SpecialQualification,std::string("Separate source qualification required: ")+tag);
    }
    const auto *sp=field(definition,"[purchase cost]",trace);
    const auto *tp=field(definition,"[special purchase cost]",trace);
    if ((sp!=nullptr)==(tp!=nullptr)) fail(SkillLearningGate::SourceInvalid,"Exactly one SP/TP purchase cost is required");
    const auto costs=numbers(tp?tp:sp,tp?"special purchase cost":"purchase cost");
    result.currency=tp?"TP":"SP";
    result.cost=costs[std::min(size_t(target-1),costs.size()-1)];
    const auto *discount=field(definition,"[growtype fitness]",trace);
    const auto *discount2=field(definition,"[second growtype fitness]",trace);
    if (discount) {
        const auto discounts=numbers(discount,"growtype fitness");
        if (size_t(identity.growtype)>=discounts.size()) fail(SkillLearningGate::SourceInvalid,"Missing fitness discount");
        result.discount=discounts[size_t(identity.growtype)];
    }
    if (discount2 && identity.awakening>0) {
        const auto discounts=numbers(discount2,"second growtype fitness");
        const size_t index=size_t(identity.growtype)*2+size_t(identity.awakening-1);
        if (identity.awakening>2 || index>=discounts.size()) fail(SkillLearningGate::SourceInvalid,"Missing awakening fitness discount");
        result.discount=discounts[index];
    }
    if (result.discount>100) fail(SkillLearningGate::SourceInvalid,"Fitness discount exceeds 100 percent");
    const int64_t authoredCost=result.cost;
    if (result.currency=="SP" && policy.applyGrowtypeFitnessDiscount) result.cost=result.cost*(100-result.discount)/100;
    trace.push_back({{"policy",policy.id},{"classification","inferred"},{"source_cost",authoredCost},
        {"cost_vector_index",std::min(size_t(target-1),costs.size()-1)},{"repeat_last_cost",true},
        {"fitness_discount_percent",result.discount},{"discount_applied",result.currency=="SP"&&policy.applyGrowtypeFitnessDiscount},
        {"currency",result.currency},{"cost",result.cost},{"evidence","official skillsample.skl:14-37; server master_new_skill candidate"}});
    const auto *prerequisite=field(definition,"[pre required skill]",trace);
    const auto values=numbers(prerequisite,"pre required skill",true);
    if (values.size()%2) fail(SkillLearningGate::SourceInvalid,"Prerequisite skills must be ID/level pairs");
    std::set<int> prerequisiteIds;
    for (size_t i=0;i<values.size();i+=2) {
        if (!prerequisiteIds.insert(values[i]).second) fail(SkillLearningGate::SourceInvalid,"Duplicate prerequisite skill");
        result.prerequisites.push_back({{identity.jobId,values[i]},values[i+1]});
    }
    return result;
}
Json ledger(const CharacterSkillState &state, int64_t nowMs, const std::string &package, const SkillLearningPolicy &policy) {
    const auto root=state.snapshot(nowMs);
    if (!root.contains("learning")) fail(SkillLearningGate::Uninitialized,"Missing learning metadata");
    const auto &value=root.at("learning");
    if (!value.is_object() || integer(value.at("schema"),"learning.schema")!=1 ||
        !value.at("initialized").is_boolean() || !value.at("initialized").get<bool>())
        fail(SkillLearningGate::InvalidLedger,"Invalid learning initialization");
    if (textValue(value.at("package_identity"),"package_identity")!=package ||
        textValue(value.at("policy"),"policy")!=policy.id || textValue(value.at("tp_policy"),"tp_policy")!=policy.tpPolicy)
        fail(SkillLearningGate::SourceMismatch,"Learning source/policy identity differs");
    integer(value.at("revision"),"learning.revision");
    if (!value.at("grants").is_array() || !value.at("purchases").is_array() ||
        !value.at("rewards").is_array() || !value.at("receipts").is_object())
        fail(SkillLearningGate::InvalidLedger,"Invalid learning arrays");
    std::map<SkillKey,int> levels;
    for (const auto &grant:value.at("grants")) {
        const auto key=keyValue(grant.at("key")); const int level=intValue(grant.at("level"),"grant level");
        const auto kind=textValue(grant.at("kind"),"grant kind");
        if (kind!="source_initial" && kind!="legacy_grant") fail(SkillLearningGate::InvalidLedger,"Unknown grant kind");
        if (!levels.emplace(key,level).second) fail(SkillLearningGate::InvalidLedger,"Duplicate skill grant");
    }
    std::set<std::string> ids;
    for (const auto &purchase:value.at("purchases")) {
        const auto id=textValue(purchase.at("request_id"),"purchase request");
        if (!validId(id)||!ids.insert(id).second) fail(SkillLearningGate::InvalidLedger,"Duplicate purchase request");
        const auto key=keyValue(purchase.at("key"));
        const int from=intValue(purchase.at("from_level"),"from_level"), target=intValue(purchase.at("target_level"),"target_level");
        if (int64_t(from)+1!=target) fail(SkillLearningGate::InvalidLedger,"Invalid purchase increment");
        const auto currency=textValue(purchase.at("currency"),"currency");
        if (currency!="SP" && currency!="TP") fail(SkillLearningGate::InvalidLedger,"Unknown purchase currency");
        integer(purchase.at("cost"),"purchase cost");
        if (!purchase.at("refunded").is_boolean()) fail(SkillLearningGate::InvalidLedger,"Invalid purchase refund flag");
        if (!purchase.at("refunded").get<bool>()) {
            if (levels[key]!=from) fail(SkillLearningGate::InvalidLedger,"Purchase history has a level gap");
            levels[key]=target;
        }
        if (!value.at("receipts").contains(id)) fail(SkillLearningGate::InvalidLedger,"Purchase lacks durable receipt");
    }
    for (const auto &reward:value.at("rewards")) {
        const auto id=textValue(reward.at("request_id"),"reward request");
        if (!validId(id)||!ids.insert(id).second) fail(SkillLearningGate::InvalidLedger,"Duplicate reward request");
        integer(reward.at("sp"),"reward.sp"); integer(reward.at("tp"),"reward.tp");
        if (!value.at("receipts").contains(id)) fail(SkillLearningGate::InvalidLedger,"Reward lacks durable receipt");
    }
    for (const auto &record:root.at("skills")) {
        const auto key=keyValue(record.at("key"));
        if (levels[key]!=intValue(record.at("level"),"learned level"))
            fail(SkillLearningGate::InvalidLedger,"Learned levels disagree with learning history");
        levels.erase(key);
    }
    for (const auto &[key,level]:levels) if (level!=0) fail(SkillLearningGate::InvalidLedger,"Learning history lacks learned skill");
    return value;
}
uint64_t nextRevision(Json &metadata) {
    const auto revision=integer(metadata.at("revision"),"revision");
    if (revision==std::numeric_limits<int64_t>::max()) fail(SkillLearningGate::InvalidLedger,"Learning revision exhausted");
    metadata["revision"]=revision+1; return uint64_t(revision+1);
}
void attach(CharacterSkillState &state, Json metadata, int64_t nowMs) {
    auto root=state.snapshot(nowMs); root["learning"]=std::move(metadata); state.restore(root,nowMs);
}
PreparedSkillLearning pending(const CharacterSkillState &state) { PreparedSkillLearning result; result.state=state; return result; }
bool replay(PreparedSkillLearning &result, const Json &metadata, const std::string &id, const Json &payload) {
    if (!validId(id)) fail(SkillLearningGate::InvalidRequest,"Empty/oversized/control-character request ID");
    const auto &receipts=metadata.at("receipts");
    if (!receipts.contains(id)) return false;
    const auto &existing=receipts.at(id);
    if (existing.at("payload")!=payload) fail(SkillLearningGate::RequestConflict,"Request ID was used with a different operation");
    result.ok=true; result.replayed=true; result.receipt=existing;
    reject(result.quote,SkillLearningGate::Accepted); return true;
}
void receipt(PreparedSkillLearning &result, Json &metadata, const std::string &id, const Json &payload, Json detail) {
    detail["request_id"]=id; detail["payload"]=payload; detail["revision"]=nextRevision(metadata);
    result.receipt=std::move(detail); metadata["receipts"][id]=result.receipt;
}
void caught(SkillLearningQuote &quote, const std::exception &error) {
    const auto *known=dynamic_cast<const LearningFailure *>(&error);
    reject(quote,known?known->gate:SkillLearningGate::InvalidLedger,error.what());
}
std::string learningFingerprint(const CharacterSkillState &normal, int64_t nowMs, bool legacy = false) {
    auto root=normal.snapshot(nowMs);
    for (auto &record:root["skills"]) record.erase("remaining_cooldown_ms");
    if (!legacy) {
        // startCooldown may materialize a previously absent, unlearned skill.
        // Only its exact runtime-only row is irrelevant to a learning binding.
        // Unknown record/key fields still participate, even for level zero.
        auto &rows=root["skills"];
        rows.erase(std::remove_if(rows.begin(),rows.end(),[](const Json &record) {
            return record.size()==2 && record.contains("level") && record.at("level")==0 &&
                record.contains("key") && record.at("key").is_object() && record.at("key").size()==2 &&
                record.at("key").contains("job_id") && record.at("key").contains("skill_id");
        }),rows.end());
    }
    const auto bytes=root.dump();
    const auto hash=sha256(Bytes(bytes.begin(),bytes.end()));
    return legacy ? hash : "learning-v2:"+hash;
}
void validateOverlay(const SkillLearningTestOverlay &overlay) {
    if (overlay.spentSp<0 || overlay.spentTp<0 || !overlay.purchases.is_array() || !overlay.receipts.is_object() ||
        overlay.revision>uint64_t(std::numeric_limits<int64_t>::max()))
        fail(SkillLearningGate::InvalidLedger,"Invalid test learning pool");
    int64_t sp=0,tp=0; std::set<std::string> ids;
    std::map<SkillKey,int> purchasedLevels;
    for (const auto &purchase:overlay.purchases) {
        const auto id=textValue(purchase.at("request_id"),"test.request_id");
        if (!validId(id) || !ids.insert(id).second || !overlay.receipts.contains(id))
            fail(SkillLearningGate::InvalidLedger,"Invalid test purchase receipt");
        const auto currency=textValue(purchase.at("currency"),"test.currency");
        if (currency!="SP" && currency!="TP") fail(SkillLearningGate::InvalidLedger,"Unknown test point currency");
        auto &total=currency=="SP"?sp:tp; total=add(total,integer(purchase.at("cost"),"test.cost"));
        const auto key=keyValue(purchase.at("key"));
        const int from=intValue(purchase.at("from_level"),"test.from_level");
        const int target=intValue(purchase.at("target_level"),"test.target_level");
        if (int64_t(from)+1!=target || (purchasedLevels.count(key) && purchasedLevels.at(key)!=from))
            fail(SkillLearningGate::InvalidLedger,"Test purchase history has an invalid level increment");
        purchasedLevels[key]=target;
    }
    if (sp!=overlay.spentSp || tp!=overlay.spentTp)
        fail(SkillLearningGate::InvalidLedger,"Test point counters disagree with test purchase history");
    for (const auto &[key,level]:purchasedLevels)
        if (!overlay.levels.count(key) || overlay.levels.at(key)!=level)
            fail(SkillLearningGate::InvalidLedger,"Test levels disagree with purchase history");
    if (!overlay.purchases.empty() && overlay.normalFingerprint.empty())
        fail(SkillLearningGate::InvalidLedger,"Purchased test overlay lacks normal ledger binding");
}
} // namespace

const char *skillLearningGateName(SkillLearningGate gate) {
    switch (gate) {
#define DNF_LEARNING_GATE(x,text) case SkillLearningGate::x:return text
    DNF_LEARNING_GATE(Accepted,"accepted"); DNF_LEARNING_GATE(Uninitialized,"uninitialized");
    DNF_LEARNING_GATE(InvalidLedger,"invalid_ledger"); DNF_LEARNING_GATE(SourceMismatch,"source_mismatch");
    DNF_LEARNING_GATE(SourceInvalid,"source_invalid"); DNF_LEARNING_GATE(WrongCharacter,"wrong_character");
    DNF_LEARNING_GATE(MissingImplementation,"missing_implementation"); DNF_LEARNING_GATE(PassiveHasNoConsumer,"passive_has_no_consumer");
    DNF_LEARNING_GATE(UnknownKind,"unknown_kind"); DNF_LEARNING_GATE(SourceExcluded,"source_excluded");
    DNF_LEARNING_GATE(InvalidLevel,"invalid_level"); DNF_LEARNING_GATE(CharacterLevel,"character_level");
    DNF_LEARNING_GATE(Prerequisite,"prerequisite"); DNF_LEARNING_GATE(SpecialQualification,"special_qualification");
    DNF_LEARNING_GATE(InsufficientPoints,"insufficient_points"); DNF_LEARNING_GATE(BudgetConflict,"budget_conflict");
    DNF_LEARNING_GATE(StaleRevision,"stale_revision"); DNF_LEARNING_GATE(InvalidRequest,"invalid_request");
    DNF_LEARNING_GATE(RequestConflict,"request_conflict"); DNF_LEARNING_GATE(NotLearned,"not_learned");
    DNF_LEARNING_GATE(TemporaryLevelIneligible,"temporary_level_ineligible");
#undef DNF_LEARNING_GATE
    }
    return "unknown";
}
Json SkillLearningBudget::json() const {
    return {{"earned_sp",earnedSp},{"earned_tp",earnedTp},{"spent_sp",spentSp},{"spent_tp",spentTp},
        {"remaining_sp",remainingSp},{"remaining_tp",remainingTp},{"revision",revision},{"trace",trace}};
}
Json SkillLearningQuote::json() const {
    return {{"gate",skillLearningGateName(gate)},{"message",message},{"error",error},{"key",key.json()},
        {"current_level",currentLevel},{"target_level",targetLevel},{"required_character_level",requiredCharacterLevel},
        {"purchase_maximum",purchaseMaximum},{"currency",currency},{"cost",cost},{"revision",revision},
        {"budget",budget.json()},{"trace",trace}};
}
Json SkillLearningUseEligibility::json() const {
    return {{"gate",skillLearningGateName(gate)},{"learned_level",learnedLevel},
        {"required_character_level",requiredCharacterLevel},{"trace",trace},{"error",error}};
}
SkillLearningService::SkillLearningService(Pvf &pvf, const CharacterCatalog &catalog, SkillLearningPolicy policy)
    : SkillLearningService(catalog,pvf.script("etc/sptable.etc"),pvf.identity(),std::move(policy)) {}
SkillLearningService::SkillLearningService(const CharacterCatalog &catalog, Script spTable,
    std::string packageIdentity, SkillLearningPolicy policy)
    : catalog_(catalog),spTable_(std::move(spTable)),packageIdentity_(std::move(packageIdentity)),policy_(std::move(policy)) { loadSpTable(); }
void SkillLearningService::loadSpTable() {
    if (policy_.id!="inferred-1031-learning-v1" || policy_.tpPolicy!="inferred-server-tp-v1" ||
        policy_.maximumNormalLevel<1 || packageIdentity_.empty())
        throw std::invalid_argument("Invalid skill learning source/policy");
    const Field *selected=nullptr;
    for (const auto &candidate:spTable_.fields) if (normalize(candidate.tag)=="[sp table]") {
        if (selected) throw std::invalid_argument("Repeated SP table"); selected=&candidate;
    }
    if (!selected || !selected->values.is_array() || selected->values.empty() || selected->values.size()%2)
        throw std::invalid_argument("Missing/odd SP table");
    int expected=1;
    for (size_t i=0;i<selected->values.size();i+=2) {
        const int level=intValue(selected->values[i],"SP table level");
        const int64_t points=integer(selected->values[i+1],"SP table points");
        if (level!=expected++) throw std::invalid_argument("SP table levels must be contiguous and unique from one");
        spAtLevel_.emplace(level,points);
    }
    if (!spAtLevel_.count(policy_.maximumNormalLevel)) throw std::invalid_argument("SP table does not cover normal level policy");
}
PreparedSkillLearning SkillLearningService::prepareInitialization(const CharacterSkillState &state, int normalLevel,
    SkillInitializationMode mode, int64_t nowMs) const {
    auto result=pending(state);
    try {
        if (normalLevel<1 || normalLevel>policy_.maximumNormalLevel) fail(SkillLearningGate::InvalidLevel,"Invalid normal character level");
        auto snapshot=state.snapshot(nowMs);
        if (snapshot.contains("learning")) {
            budget(state,normalLevel,nowMs); result.ok=true; result.replayed=true;
            reject(result.quote,SkillLearningGate::Accepted); return result;
        }
        Json metadata={{"schema",1},{"initialized",true},{"policy",policy_.id},{"tp_policy",policy_.tpPolicy},
            {"package_identity",packageIdentity_},{"revision",0},{"mode",mode==SkillInitializationMode::NewCharacter?"new":"legacy"},
            {"sp_table",scriptRef(spTable_,packageIdentity_)},{"grants",Json::array()},{"purchases",Json::array()},
            {"rewards",Json::array()},{"receipts",Json::object()}};
        std::map<SkillKey,int> granted;
        if (mode==SkillInitializationMode::NewCharacter) {
            if (state.identity().growtype!=0 || state.identity().awakening!=0)
                fail(SkillLearningGate::SpecialQualification,"New creation requires a base identity");
            for (const auto &record:snapshot.at("skills")) if (intValue(record.at("level"),"initial level")!=0)
                fail(SkillLearningGate::InvalidLedger,"New initialization cannot replace already learned skills");
            const auto &character=catalog_.at(state.identity().jobId);
            const CharacterStatBlock *initial=nullptr;
            for (const auto &block:character.stats) if (normalize(block.tag)=="[initial value]") {
                if (initial) fail(SkillLearningGate::SourceInvalid,"Repeated CHR initial block"); initial=&block;
            }
            if (!initial) fail(SkillLearningGate::SourceInvalid,"Missing CHR initial skill block");
            const Field *skills=nullptr;
            for (const auto &candidate:initial->fields) if (normalize(candidate.tag)=="[skill]") {
                if (skills) fail(SkillLearningGate::SourceInvalid,"Repeated CHR initial skill field"); skills=&candidate;
            }
            if (skills) {
                if (!skills->values.is_array() || skills->values.size()%2) fail(SkillLearningGate::SourceInvalid,"Odd initial skill pairs");
                for (size_t i=0;i<skills->values.size();i+=2) {
                    const SkillKey key{state.identity().jobId,intValue(skills->values[i],"initial skill ID")};
                    const int level=intValue(skills->values[i+1],"initial skill level");
                    if (!granted.emplace(key,level).second) fail(SkillLearningGate::SourceInvalid,"Duplicate initial skill ID");
                    metadata["grants"].push_back({{"key",key.json()},{"level",level},{"kind","source_initial"},
                        {"source",scriptRef(character.source.script,packageIdentity_,skills)}});
                    result.state.setLearnedLevel(key,level);
                }
            }
        } else {
            for (const auto &record:snapshot.at("skills")) metadata["grants"].push_back({{"key",record.at("key")},
                {"level",record.at("level")},{"kind","legacy_grant"},{"source",{{"classification","legacy_import"},
                    {"cost_history","unknown_no_refund"}}}});
        }
        attach(result.state,std::move(metadata),nowMs);
        result.quote.budget=budget(result.state,normalLevel,nowMs);
        reject(result.quote,SkillLearningGate::Accepted); result.ok=true;
    } catch (const std::exception &error) { result.state=state; caught(result.quote,error); }
    return result;
}
SkillLearningBudget SkillLearningService::baseBudget(int normalLevel) const {
    if (normalLevel<1 || normalLevel>policy_.maximumNormalLevel) fail(SkillLearningGate::InvalidLevel,"Invalid normal character level");
    SkillLearningBudget result;
    for (int level=1;level<=normalLevel;++level) result.earnedSp=add(result.earnedSp,spAtLevel_.at(level));
    result.earnedTp=std::max(0,normalLevel-49);
    result.remainingSp=result.earnedSp; result.remainingTp=result.earnedTp;
    result.trace.push_back({{"policy","inferred-server-sp-cumulative-v1"},{"classification","inferred"},
        {"normal_level",normalLevel},{"sum_levels",Json::array({1,normalLevel})},{"source",scriptRef(spTable_,packageIdentity_)}});
    result.trace.push_back({{"policy",policy_.tpPolicy},{"classification","inferred"},{"formula","max(0, normalLevel - 49)"},
        {"evidence","server CUserCheckLevel/_check_level_up and SkillSlot/_ResetSFPoint; current PC grant chain unclosed"}});
    return result;
}
SkillLearningBudget SkillLearningService::budget(const CharacterSkillState &state, int normalLevel, int64_t nowMs) const {
    auto result=baseBudget(normalLevel);
    const auto metadata=ledger(state,nowMs,packageIdentity_,policy_);
    if (metadata.at("sp_table").at("member_sha256")!=sha256(spTable_.rawBytes))
        fail(SkillLearningGate::SourceMismatch,"SP table bytes differ from initialized ledger");
    result.revision=uint64_t(integer(metadata.at("revision"),"revision"));
    for (const auto &reward:metadata.at("rewards")) {
        result.earnedSp=add(result.earnedSp,integer(reward.at("sp"),"reward.sp"));
        result.earnedTp=add(result.earnedTp,integer(reward.at("tp"),"reward.tp"));
    }
    for (const auto &purchase:metadata.at("purchases")) if (!purchase.at("refunded").get<bool>()) {
        auto &spent=purchase.at("currency")=="TP"?result.spentTp:result.spentSp;
        spent=add(spent,integer(purchase.at("cost"),"purchase.cost"));
    }
    result.remainingSp=result.earnedSp-result.spentSp; result.remainingTp=result.earnedTp-result.spentTp;
    return result;
}
SkillLearningQuote SkillLearningService::quote(const CharacterSkillState &state, int normalLevel,
    const RuntimeSkillPolicy &runtime, int targetLevel, int64_t nowMs) const {
    try { return quoteDefinition(state,normalLevel,runtime,catalog_.skillDefinition(runtime.key),targetLevel,nowMs); }
    catch (const std::exception &error) { SkillLearningQuote result; result.key=runtime.key;
        reject(result,SkillLearningGate::SourceInvalid,error.what()); return result; }
}
SkillLearningQuote SkillLearningService::quoteDefinition(const CharacterSkillState &state, int normalLevel,
    const RuntimeSkillPolicy &runtime, const CharacterSkillDefinition &definition, int targetLevel, int64_t nowMs) const {
    try { return quoteWithBudget(state,normalLevel,runtime,definition,targetLevel,budget(state,normalLevel,nowMs)); }
    catch (const std::exception &error) { SkillLearningQuote result; result.key=runtime.key; caught(result,error); return result; }
}
SkillLearningQuote SkillLearningService::quoteWithBudget(const CharacterSkillState &state, int normalLevel,
    const RuntimeSkillPolicy &runtime, const CharacterSkillDefinition &definition, int targetLevel,
    const SkillLearningBudget &available, bool allowTestVisualOnly) const {
    SkillLearningQuote result; result.key=runtime.key; result.currentLevel=state.learnedLevel(runtime.key);
    try {
        if (targetLevel==0) {
            if (result.currentLevel==std::numeric_limits<int>::max()) fail(SkillLearningGate::InvalidLevel,"Skill level overflow");
            targetLevel=result.currentLevel+1;
        }
        result.targetLevel=targetLevel; result.budget=available; result.revision=result.budget.revision;
        if (!(runtime.key==definition.key) || runtime.key.jobId!=state.identity().jobId)
            fail(SkillLearningGate::WrongCharacter,"Runtime/source/ledger skill identities differ");
        const bool visualOnlyCandidate=allowTestVisualOnly&&!runtime.implemented&&
            (runtime.kind==SkillSourceKind::Active||runtime.kind==SkillSourceKind::Passive);
        if (!runtime.implemented&&!visualOnlyCandidate)
            fail(SkillLearningGate::MissingImplementation,"No executable skill consumer");
        if (runtime.kind==SkillSourceKind::Unknown || runtime.kind!=definition.kind)
            fail(SkillLearningGate::UnknownKind,"Unknown or mismatched source/runtime skill kind");
        if (runtime.kind==SkillSourceKind::Passive && !runtime.passiveConsumerBound&&!visualOnlyCandidate)
            fail(SkillLearningGate::PassiveHasNoConsumer,"Passive has no bound consumer");
        if (visualOnlyCandidate) result.trace.push_back({
            {"policy","test-visual-only-source-fallback-v1"},
            {"classification","inferred"},
            {"visual_only",true},
            {"combat_consumer",false},
            {"passive_consumer_bound",runtime.passiveConsumerBound},
            {"normal_learning_unchanged",true}});
        if (targetLevel<1 || int64_t(result.currentLevel)+1!=targetLevel || targetLevel>runtime.maximumLevel)
            fail(SkillLearningGate::InvalidLevel,"Purchase must increment one level within runtime ceiling");
        const auto source=rules(definition,state.identity(),targetLevel,policy_,result.trace,true);
        result.requiredCharacterLevel=source.requiredLevel; result.purchaseMaximum=source.purchaseMaximum;
        result.currency=source.currency; result.cost=source.cost;
        if (normalLevel<source.requiredLevel) fail(SkillLearningGate::CharacterLevel,"Normal character level below source requirement");
        for (const auto &[key,level]:source.prerequisites) {
            result.trace.push_back({{"prerequisite",key.json()},{"required_level",level},{"learned_level",state.learnedLevel(key)}});
            if (state.learnedLevel(key)<level) fail(SkillLearningGate::Prerequisite,"Prerequisite skill level insufficient");
        }
        if (result.budget.remainingSp<0 || result.budget.remainingTp<0)
            fail(SkillLearningGate::BudgetConflict,"Existing purchases exceed current normal point budget");
        if ((source.currency=="TP"?result.budget.remainingTp:result.budget.remainingSp)<source.cost)
            fail(SkillLearningGate::InsufficientPoints,"Insufficient source point budget");
        reject(result,SkillLearningGate::Accepted);
    } catch (const std::exception &error) { caught(result,error); }
    return result;
}
PreparedSkillLearning SkillLearningService::prepare(const CharacterSkillState &state, int normalLevel,
    const RuntimeSkillPolicy &runtime, const SkillLearningRequest &request, int64_t nowMs) const {
    auto result=pending(state); result.quote.key=request.key;
    try {
        auto metadata=ledger(state,nowMs,packageIdentity_,policy_);
        const Json payload={{"kind","purchase"},{"key",request.key.json()},{"target_level",request.targetLevel}};
        if (replay(result,metadata,request.requestId,payload)) return result;
        if (!(request.key==runtime.key)) fail(SkillLearningGate::WrongCharacter,"Request/runtime keys differ");
        if (request.expectedRevision!=uint64_t(integer(metadata.at("revision"),"revision")))
            fail(SkillLearningGate::StaleRevision,"Learning revision changed");
        result.quote=quote(state,normalLevel,runtime,request.targetLevel,nowMs);
        if (!result.quote.accepted()) return result;
        if (request.targetLevel<1) fail(SkillLearningGate::InvalidRequest,"Purchase request requires explicit positive target");
        const auto &definition=catalog_.skillDefinition(request.key);
        Json purchase={{"request_id",request.requestId},{"key",request.key.json()},{"from_level",result.quote.currentLevel},
            {"target_level",request.targetLevel},{"currency",result.quote.currency},{"cost",result.quote.cost},
            {"refunded",false},{"source",definitionRef(definition)},{"qualification_trace",result.quote.trace}};
        result.state.setLearnedLevel(request.key,request.targetLevel);
        metadata["purchases"].push_back(std::move(purchase));
        receipt(result,metadata,request.requestId,payload,{{"quote",result.quote.json()}});
        attach(result.state,std::move(metadata),nowMs);
        result.quote.budget=budget(result.state,normalLevel,nowMs); result.ok=true;
    } catch (const std::exception &error) { result.state=state; caught(result.quote,error); }
    return result;
}
PreparedSkillLearning SkillLearningService::prepareReset(const CharacterSkillState &state, int normalLevel,
    const std::string &requestId, uint64_t expectedRevision, int64_t nowMs) const {
    auto result=pending(state);
    try {
        auto metadata=ledger(state,nowMs,packageIdentity_,policy_); const Json payload={{"kind","reset"}};
        if (replay(result,metadata,requestId,payload)) return result;
        if (expectedRevision!=uint64_t(integer(metadata.at("revision"),"revision")))
            fail(SkillLearningGate::StaleRevision,"Learning revision changed");
        std::map<SkillKey,int> grants;
        for (const auto &grant:metadata.at("grants")) grants.emplace(keyValue(grant.at("key")),intValue(grant.at("level"),"grant.level"));
        int64_t sp=0,tp=0;
        for (auto &purchase:metadata["purchases"]) if (!purchase.at("refunded").get<bool>()) {
            auto &refund=purchase.at("currency")=="TP"?tp:sp;
            refund=add(refund,integer(purchase.at("cost"),"purchase.cost"));
            purchase["refunded"]=true; purchase["refund_request_id"]=requestId;
            const auto key=keyValue(purchase.at("key")); result.state.setLearnedLevel(key,grants[key]);
        }
        receipt(result,metadata,requestId,payload,{{"refunded_sp",sp},{"refunded_tp",tp}});
        attach(result.state,std::move(metadata),nowMs); result.quote.budget=budget(result.state,normalLevel,nowMs);
        reject(result.quote,SkillLearningGate::Accepted); result.ok=true;
    } catch (const std::exception &error) { result.state=state; caught(result.quote,error); }
    return result;
}
PreparedSkillLearning SkillLearningService::preparePointReward(const CharacterSkillState &state, int normalLevel,
    const std::string &requestId, uint64_t expectedRevision, int64_t sp, int64_t tp, const Json &source, int64_t nowMs) const {
    auto result=pending(state);
    try {
        auto metadata=ledger(state,nowMs,packageIdentity_,policy_);
        if (sp<0 || tp<0 || (!sp&&!tp) || !source.is_object() || source.empty())
            fail(SkillLearningGate::InvalidRequest,"Point rewards need a positive amount and explicit source");
        const Json payload={{"kind","point_reward"},{"sp",sp},{"tp",tp},{"source",source}};
        if (replay(result,metadata,requestId,payload)) return result;
        if (expectedRevision!=uint64_t(integer(metadata.at("revision"),"revision")))
            fail(SkillLearningGate::StaleRevision,"Learning revision changed");
        metadata["rewards"].push_back({{"request_id",requestId},{"sp",sp},{"tp",tp},{"source",source}});
        receipt(result,metadata,requestId,payload,{{"granted_sp",sp},{"granted_tp",tp}});
        attach(result.state,std::move(metadata),nowMs); result.quote.budget=budget(result.state,normalLevel,nowMs);
        reject(result.quote,SkillLearningGate::Accepted); result.ok=true;
    } catch (const std::exception &error) { result.state=state; caught(result.quote,error); }
    return result;
}
SkillLearningUseEligibility SkillLearningService::useEligibility(const CharacterSkillState &state, SkillKey key,
    int effectiveCharacterLevel) const {
    return sourceUseEligibility(state.identity(),key,state.learnedLevel(key),effectiveCharacterLevel);
}
SkillLearningUseEligibility SkillLearningService::sourceUseEligibility(CharacterIdentity identity, SkillKey key,
    int configuredLevel, int effectiveCharacterLevel) const {
    SkillLearningUseEligibility result; result.learnedLevel=configuredLevel;
    try {
        if (key.jobId!=identity.jobId) fail(SkillLearningGate::WrongCharacter,"Use skill belongs to another job");
        if (result.learnedLevel==0) fail(SkillLearningGate::NotLearned,"Skill is not learned");
        if (effectiveCharacterLevel<1) fail(SkillLearningGate::TemporaryLevelIneligible,"Nonpositive effective character level");
        const auto source=rules(catalog_.skillDefinition(key),identity,result.learnedLevel,policy_,result.trace,false);
        result.requiredCharacterLevel=source.requiredLevel;
        if (effectiveCharacterLevel<source.requiredLevel)
            fail(SkillLearningGate::TemporaryLevelIneligible,"Effective character level below learned skill requirement");
        result.gate=SkillLearningGate::Accepted;
    } catch (const std::exception &error) {
        const auto *known=dynamic_cast<const LearningFailure *>(&error);
        result.gate=known?known->gate:SkillLearningGate::SourceInvalid; result.error=error.what();
    }
    return result;
}
Json SkillLearningTestOverlay::snapshot() const {
    validateOverlay(*this);
    Json records=Json::array();
    for (const auto &[key,level]:levels) records.push_back({{"key",key.json()},{"level",level}});
    return {{"schema",1},{"levels",records},{"spent_sp",spentSp},{"spent_tp",spentTp},{"revision",revision},
        {"normal_fingerprint",normalFingerprint},{"purchases",purchases},{"receipts",receipts}};
}
void SkillLearningTestOverlay::restore(const Json &value) {
    if (!value.is_object() || integer(value.at("schema"),"test.schema")!=1 || !value.at("levels").is_array())
        throw std::invalid_argument("Invalid test learning overlay");
    SkillLearningTestOverlay candidate;
    candidate.spentSp=integer(value.at("spent_sp"),"test.spent_sp"); candidate.spentTp=integer(value.at("spent_tp"),"test.spent_tp");
    candidate.revision=uint64_t(integer(value.at("revision"),"test.revision"));
    candidate.normalFingerprint=textValue(value.at("normal_fingerprint"),"normal_fingerprint");
    candidate.purchases=value.at("purchases"); candidate.receipts=value.at("receipts");
    for (const auto &record:value.at("levels")) if (!candidate.levels.emplace(keyValue(record.at("key")),
        intValue(record.at("level"),"test.level")).second) throw std::invalid_argument("Duplicate test override skill");
    validateOverlay(candidate); *this=std::move(candidate);
}
CharacterSkillState SkillLearningTestOverlay::effectiveState(const CharacterSkillState &normal, int64_t nowMs) const {
    validateOverlay(*this);
    const auto canonical=learningFingerprint(normal,nowMs);
    // An old binding without empty runtime rows has the same digest payload.
    // Otherwise only an exact old-algorithm match authorizes migration.
    if (!normalFingerprint.empty() && normalFingerprint!=canonical &&
            (normalFingerprint.rfind("learning-v2:",0)==0 ||
             (normalFingerprint!=canonical.substr(12) && normalFingerprint!=learningFingerprint(normal,nowMs,true))))
        fail(SkillLearningGate::StaleRevision,"Normal learning state changed; reset the test overlay explicitly");
    CharacterSkillState result=normal;
    for (const auto &[key,level]:levels) {
        if (key.jobId!=normal.identity().jobId || key.skillId<0 || level<0) throw std::invalid_argument("Invalid test override identity/level");
        result.setLearnedLevel(key,level);
    }
    // This view is never a normal learning ledger. Remove metadata so a caller
    // cannot accidentally purchase against normal history using overridden levels.
    auto root=result.snapshot(nowMs); root.erase("learning"); root["test_learning_overlay"]=snapshot(); result.restore(root,nowMs);
    return result;
}
void SkillLearningTestOverlay::upgradeNormalBinding(const CharacterSkillState &normal, int64_t nowMs) {
    if (normalFingerprint.empty()) { validateOverlay(*this); return; }
    // Validate before replacing the hash; never rebind a stale/foreign ledger.
    (void)effectiveState(normal,nowMs);
    normalFingerprint=learningFingerprint(normal,nowMs);
}
SkillLearningQuote SkillLearningService::quoteTest(const CharacterSkillState &normal, const SkillLearningTestOverlay &overlay,
    int effectiveCharacterLevel, const RuntimeSkillPolicy &runtime, int targetLevel, int64_t nowMs) const {
    try {
        ledger(normal,nowMs,packageIdentity_,policy_); validateOverlay(overlay);
        auto available=baseBudget(effectiveCharacterLevel); available.revision=overlay.revision;
        available.spentSp=overlay.spentSp; available.spentTp=overlay.spentTp;
        available.remainingSp=available.earnedSp-available.spentSp; available.remainingTp=available.earnedTp-available.spentTp;
        available.trace.push_back({{"pool","isolated_test_learning"},{"normal_budget_unchanged",true}});
        return quoteWithBudget(overlay.effectiveState(normal,nowMs),effectiveCharacterLevel,runtime,
            catalog_.skillDefinition(runtime.key),targetLevel,available,true);
    } catch (const std::exception &error) { SkillLearningQuote result; result.key=runtime.key; caught(result,error); return result; }
}
PreparedTestSkillLearning SkillLearningService::prepareTest(const CharacterSkillState &normal,
    const SkillLearningTestOverlay &overlay, int effectiveCharacterLevel, const RuntimeSkillPolicy &runtime,
    const SkillLearningRequest &request, int64_t nowMs) const {
    PreparedTestSkillLearning result; result.overlay=overlay; result.quote.key=request.key;
    try {
        ledger(normal,nowMs,packageIdentity_,policy_); validateOverlay(overlay);
        overlay.effectiveState(normal,nowMs);
        if (!validId(request.requestId) || request.targetLevel<1)
            fail(SkillLearningGate::InvalidRequest,"Test purchase requires stable ID and explicit positive target");
        const Json payload={{"kind","test_purchase"},{"key",request.key.json()},{"target_level",request.targetLevel}};
        if (overlay.receipts.contains(request.requestId)) {
            const auto &saved=overlay.receipts.at(request.requestId);
            if (saved.at("payload")!=payload) fail(SkillLearningGate::RequestConflict,"Test request ID changed payload");
            result.ok=true; result.replayed=true; result.receipt=saved; reject(result.quote,SkillLearningGate::Accepted); return result;
        }
        if (!(runtime.key==request.key)) fail(SkillLearningGate::WrongCharacter,"Test request/runtime keys differ");
        if (request.expectedRevision!=overlay.revision) fail(SkillLearningGate::StaleRevision,"Test learning revision changed");
        result.quote=quoteTest(normal,overlay,effectiveCharacterLevel,runtime,request.targetLevel,nowMs);
        if (!result.quote.accepted()) return result;
        if (overlay.revision==uint64_t(std::numeric_limits<int64_t>::max()))
            fail(SkillLearningGate::InvalidLedger,"Test learning revision exhausted");
        result.overlay.normalFingerprint=learningFingerprint(normal,nowMs);
        result.overlay.levels[request.key]=request.targetLevel;
        auto &spent=result.quote.currency=="SP"?result.overlay.spentSp:result.overlay.spentTp;
        spent=add(spent,result.quote.cost); ++result.overlay.revision;
        result.receipt={{"request_id",request.requestId},{"payload",payload},{"revision",result.overlay.revision},
            {"quote",result.quote.json()}};
        result.overlay.purchases.push_back({{"request_id",request.requestId},{"key",request.key.json()},
            {"from_level",result.quote.currentLevel},{"target_level",request.targetLevel},
            {"currency",result.quote.currency},{"cost",result.quote.cost}});
        result.overlay.receipts[request.requestId]=result.receipt; validateOverlay(result.overlay); result.ok=true;
    } catch (const std::exception &error) { result.overlay=overlay; caught(result.quote,error); }
    return result;
}
} // namespace dnf
