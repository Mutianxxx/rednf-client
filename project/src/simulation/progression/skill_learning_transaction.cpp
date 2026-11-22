#include "dnf/skill_learning_transaction.hpp"
#include <stdexcept>

namespace dnf {
namespace {
SkillLearningTransactionResult rejected(const std::string &message,const std::string &error = {}) {
    SkillLearningTransactionResult result; result.message=message; result.error=error; return result;
}
Json payloadFor(const SkillLearningRequest &request) {
    return {{"kind","purchase"},{"key",request.key.json()},{"target_level",request.targetLevel}};
}
const Json *learningReceipt(const Json &character,const SkillLearningRequest &request) {
    if (!character.is_object() || !character.contains("skill_state") ||
        !character.at("skill_state").is_object() || !character.at("skill_state").contains("learning")) return nullptr;
    const auto &learning=character.at("skill_state").at("learning");
    if (!learning.is_object() || !learning.contains("receipts") || !learning.at("receipts").is_object() ||
        !learning.at("receipts").contains(request.requestId)) return nullptr;
    return &learning.at("receipts").at(request.requestId);
}
void writePreparedCharacter(Json &character,const World &world,const CharacterSkillState &prepared) {
    character["skill_state"]=prepared.snapshot(world.nowMs());
    if (!character.contains("skills") || !character.at("skills").is_object()) character["skills"]=Json::object();
    for (const auto &skill:world.skills) character["skills"][std::to_string(skill.id)]=prepared.learnedLevel(skill.identity());
    if (!character.contains("passives") || !character.at("passives").is_object()) character["passives"]=Json::object();
    for (const auto &skill:world.passives) character["passives"][skill.key]=prepared.learnedLevel(skill.identity());
}
} // namespace

Json SkillLearningTransactionResult::json() const {
    const char *name=state==SkillLearningTransactionState::Committed?"committed":
        state==SkillLearningTransactionState::Replayed?"replayed":state==SkillLearningTransactionState::Pending?"pending":"rejected";
    return {{"state",name},{"ok",ok},{"message",message},{"error",error},{"quote",quote.json()},{"receipt",receipt}};
}
Json SkillLearningTransaction::pendingSnapshot() const {
    if (!pending_) return nullptr;
    return {{"slot",pending_->slot},{"identity",pending_->identity.json()},{"simulation_ms",pending_->simulationMs},
        {"request_id",pending_->requestId},{"durable",pending_->durable},{"receipt",pending_->receipt},
        {"quote",pending_->prepared.quote.json()}};
}
SkillLearningTransactionResult SkillLearningTransaction::publish() {
    if (!pending_) return rejected("没有待处理的技能学习");
    auto &pending=*pending_;
    SkillLearningTransactionResult result; result.quote=pending.prepared.quote; result.receipt=pending.receipt;
    try {
        if (!pending.durable) throw std::runtime_error("Learning generation is not durable");
        if (!(pending.world->identity()==pending.identity) || pending.world->nowMs()!=pending.simulationMs)
            throw std::runtime_error("World advanced or changed while learning publication was pending");
        // A retained test overlay is invalid after normal purchases. It stays
        // available in the separately persisted test field for diagnostics;
        // normal requests require disabled debug and publish only normal levels.
        if(!pending.runtime)throw std::runtime_error("Prepared learning runtime is missing");
        pending.world->publishPreparedSkillRuntime(*pending.runtime);
        result.state=SkillLearningTransactionState::Committed; result.ok=true; result.message="学习成功";
        pending_.reset();
    } catch (const std::exception &error) {
        result.state=SkillLearningTransactionState::Pending; result.message="学习已保存，等待恢复运行状态"; result.error=error.what();
    }
    return result;
}
SkillLearningTransactionResult SkillLearningTransaction::submit(CharacterStore &store,int slot,World &world,
    const Progression &progression,const SkillLearningRequest &request,const Json &regionSessionSnapshot) {
    if (pending_) return rejected("请先重试待保存的技能学习");
    if (store.hasPendingCommit()) return rejected("请先重试待处理的存档");
    try {
        if (!world.usesSourceGrowth()) return rejected("当前规则未启用正常技能学习");
        if (world.debugOverrides().enabled || world.experimentalSkillPreviewEnabled())
            return rejected("请先退出独立测试/手动技能预览再进行正常学习");
        if (world.combat || world.player.dead || world.player.hp<=0 || world.activeSkill()>=0 || !world.skillLearningProjectionReady())
            return rejected("请在城镇静止时学习技能");
        if (slot<0 || !store.data.contains("characters") || !store.data.at("characters").is_array() ||
            size_t(slot)>=store.data.at("characters").size() || store.data.at("characters").at(size_t(slot)).is_null())
            return rejected("角色存档槽无效");
        auto &character=store.data.at("characters").at(size_t(slot));
        if (!character.contains("identity") || !(CharacterIdentity::fromJson(character.at("identity"))==world.identity()))
            return rejected("角色身份与存档槽不一致");
        const auto durable=store.receipt(request.requestId);
        if (!durable.is_null()) {
            const auto *saved=learningReceipt(character,request);
            if (!saved || saved->at("payload")!=payloadFor(request))
                return rejected("学习请求编号冲突","Durable receipt is not this character's exact skill purchase");
            SkillLearningTransactionResult result; result.ok=true; result.state=SkillLearningTransactionState::Replayed;
            result.message="该技能学习已保存"; result.receipt=durable; return result;
        }
        const auto prepared=world.skillLearning().prepare(world.skillState(),progression.level(),
            world.runtimeSkillPolicy(request.key),request,world.nowMs());
        if (!prepared.ok) { auto result=rejected(prepared.quote.message,prepared.quote.error); result.quote=prepared.quote; return result; }
        if (prepared.replayed) return rejected("技能账本与持久回执不一致","In-memory learning receipt has no durable store receipt");
        if (!regionSessionSnapshot.is_object()) return rejected("区域存档快照无效");
        // All preparation and allocation which can fail before publication is
        // private. Disk failure retains the exact CharacterStore pending root.
        auto preparedRuntime=world.prepareSkillLedger(prepared.state);
        const auto before=store.data;
        Pending pending; pending.store=&store; pending.world=&world; pending.slot=slot; pending.identity=world.identity();
        pending.simulationMs=world.nowMs(); pending.requestId=request.requestId; pending.prepared=prepared;
        pending.runtime=std::move(preparedRuntime);
        try {
            store.capture(slot,world,progression);
            auto &candidate=store.data.at("characters").at(size_t(slot));
            candidate["region_session"]=regionSessionSnapshot;
            writePreparedCharacter(candidate,world,prepared.state);
            candidate=pending.runtime->writeCharacter(std::move(candidate));
            pending_=std::move(pending);
            pending_->receipt=store.commit(request.requestId); pending_->durable=true;
        } catch (const std::exception &error) {
            if (!store.hasPendingCommit()) {
                store.data=before; pending_.reset(); return rejected("技能学习未保存",error.what());
            }
            if (!pending_) pending_=std::move(pending);
            SkillLearningTransactionResult result; result.state=SkillLearningTransactionState::Pending;
            result.message="技能学习保存待重试"; result.error=error.what(); result.quote=prepared.quote; return result;
        }
        return publish();
    } catch (const std::exception &error) { return rejected("技能学习失败",error.what()); }
}
SkillLearningTransactionResult SkillLearningTransaction::retry(CharacterStore &store,World &world) {
    if (!pending_) return rejected("没有待处理的技能学习");
    if (pending_->store!=&store || pending_->world!=&world)
        return rejected("待处理学习属于另一个角色存档或世界");
    if (!(world.identity()==pending_->identity) || world.nowMs()!=pending_->simulationMs)
        return rejected("待处理期间世界已变化，请恢复该提交代","Simulation must remain stopped while a learning transaction is pending");
    try {
        if (!pending_->durable) {
            if (store.hasPendingCommit()) pending_->receipt=store.retryPending();
            else {
                const auto existing=store.receipt(pending_->requestId);
                if (existing.is_null()) throw std::runtime_error("Prepared pending generation is missing");
                pending_->receipt=existing;
            }
            if (pending_->receipt.at("request_id")!=pending_->requestId)
                throw std::runtime_error("Retried save receipt does not belong to the retained learning request");
            pending_->durable=true;
        }
        return publish();
    } catch (const std::exception &error) {
        SkillLearningTransactionResult result; result.state=SkillLearningTransactionState::Pending;
        result.message="技能学习保存待重试"; result.error=error.what(); result.quote=pending_->prepared.quote; return result;
    }
}
} // namespace dnf
