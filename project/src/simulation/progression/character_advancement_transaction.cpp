#include "dnf/character_advancement.hpp"
#include "dnf/storage.hpp"
#include "dnf/scene.hpp"
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
CharacterAdvancementResult rejected(const std::string &message,const std::string &error={}) {
    CharacterAdvancementResult r;r.message=message;r.error=error;return r;
}
bool requestIdValid(const std::string &s) {
    if(s.empty()||s.size()>200)return false;
    for(unsigned char c:s)if(c<33||c>126)return false;
    return true;
}
}
Json CharacterAdvancementRequest::payload() const {
    return {{"kind","user-gsd-identity"},{"before",expectedIdentity.json()},{"target",target.json()},
        {"expected_generation",expectedGeneration},{"npc_id",npcId},{"policy","user-gsd-source-level-v1"}};
}
Json CharacterAdvancementResult::json() const {
    const char *s=state==CharacterAdvancementState::Committed?"committed":
        state==CharacterAdvancementState::Replayed?"replayed":state==CharacterAdvancementState::Pending?"pending":"rejected";
    return {{"state",s},{"ok",ok},{"message",message},{"error",error},{"receipt",receipt},{"trace",trace}};
}
Json CharacterAdvancementTransaction::pendingSnapshot() const {
    if(!pending_)return nullptr;
    return {{"request_id",pending_->requestId},{"simulation_ms",pending_->simulationMs},{"identity",pending_->before.json()},
        {"durable",pending_->durable},{"receipt",pending_->receipt}};
}
void CharacterAdvancementTransaction::validateFrozen() const {
    if(!pending_)throw std::invalid_argument("No pending identity generation");
    const auto &p=*pending_;
    if(!(p.world->identity()==p.before)||p.world->nowMs()!=p.simulationMs||
       p.world->simulationCheckpoint()!=p.expectedSimulation||
       p.world->skillState().snapshot(p.simulationMs)!=p.expectedSkills||p.progression->state!=p.expectedProgression)
        throw std::invalid_argument("World/progression advanced while identity commit was pending");
}
CharacterAdvancementResult CharacterAdvancementTransaction::publish() {
    if(!pending_)return rejected("没有待处理的转职或觉醒");
    CharacterAdvancementResult r;r.receipt=pending_->receipt;r.trace=pending_->prepared->diagnostics();
    try {
        validateFrozen();
        if(!pending_->durable)throw std::invalid_argument("Identity generation is not durable");
        pending_->world->publishCharacterAdvancement(*pending_->prepared);
        pending_.reset();r.ok=true;r.state=CharacterAdvancementState::Committed;r.message="转职或觉醒已设置并保存";
    }catch(const std::exception &e){r.state=CharacterAdvancementState::Pending;r.message="身份已保存，等待恢复运行状态";r.error=e.what();}
    return r;
}
CharacterAdvancementResult CharacterAdvancementTransaction::submit(CharacterStore &store,int slot,World &world,
    const Progression &progression,const Scene &scene,const CharacterAdvancementRequest &request,const Json &regionSessionSnapshot) {
    if(pending_)return rejected("请先重试当前身份保存");
    if(store.hasPendingCommit())return rejected("请先重试当前存档");
    try {
        if(!requestIdValid(request.requestId))return rejected("身份请求编号无效");
        if(slot<0||!store.data.contains("characters")||!store.data.at("characters").is_array()||
           size_t(slot)>=store.data.at("characters").size()||!store.data.at("characters").at(slot).is_object())
            return rejected("角色存档槽无效");
        const auto &character=store.data.at("characters").at(slot);
        const auto durable=store.receipt(request.requestId);
        if(!durable.is_null()) {
            if(!character.contains("identity_changes")||!character.at("identity_changes").is_object()||
               !character.at("identity_changes").contains(request.requestId)||
               character.at("identity_changes").at(request.requestId).at("payload")!=request.payload())
                return rejected("身份请求编号冲突","Durable request belongs to another command/character");
            CharacterAdvancementResult r;r.state=CharacterAdvancementState::Replayed;r.ok=true;
            r.message="该转职或觉醒已经保存";r.receipt=durable;return r;
        }
        if(store.generation()!=request.expectedGeneration)return rejected("存档代已变化，请重新选择");
        if(!(world.identity()==request.expectedIdentity)||!character.contains("identity")||
           !(CharacterIdentity::fromJson(character.at("identity"))==request.expectedIdentity))return rejected("角色身份已变化，请重新选择");
        if(!world.advancementCatalog().isTrainer(request.npcId))return rejected("请与G.S.D交谈");
        bool nearby=false;
        for(const auto &npc:scene.npcs)if(npc.id==request.npcId&&npc.visible&&
            normalize(npc.source)==world.advancementCatalog().trainerPath()&&
            std::abs(npc.x-world.player.x)+std::abs(npc.y-world.player.y)<180)nearby=true;
        if(!nearby||world.combat)return rejected("请靠近城镇中的G.S.D");
        if(!regionSessionSnapshot.is_object())return rejected("区域保存快照无效");
        auto prepared=world.prepareCharacterAdvancement(request.target,progression);
        auto pending=std::make_unique<Pending>();pending->store=&store;pending->world=&world;pending->progression=&progression;
        pending->before=world.identity();pending->simulationMs=world.nowMs();pending->requestId=request.requestId;
        pending->expectedProgression=progression.state;pending->expectedSkills=world.skillState().snapshot(world.nowMs());
        pending->expectedSimulation=world.simulationCheckpoint();pending->prepared=std::move(prepared);
        const auto before=store.data;
        try {
            store.capture(slot,world,progression);
            auto &candidate=store.data.at("characters").at(slot);
            candidate["region_session"]=regionSessionSnapshot;
            candidate=pending->prepared->writeCharacter(std::move(candidate));
            if(!candidate.contains("identity_changes"))candidate["identity_changes"]=Json::object();
            if(!candidate.at("identity_changes").is_object())throw std::invalid_argument("Invalid stored identity history");
            candidate["identity_changes"][request.requestId]={{"payload",request.payload()},
                {"normal_level",progression.level()},{"simulation_ms",world.nowMs()},
                {"source",pending->prepared->diagnostics()},{"quest_rewards_granted",false},{"cost",0}};
            pending_=std::move(pending);
            pending_->receipt=store.commit(request.requestId);pending_->durable=true;
        }catch(const std::exception &e) {
            if(!store.hasPendingCommit()){store.data=before;pending_.reset();return rejected("身份设置未保存",e.what());}
            if(!pending_)pending_=std::move(pending);
            CharacterAdvancementResult r;r.state=CharacterAdvancementState::Pending;r.message="身份保存待重试";r.error=e.what();return r;
        }
        return publish();
    }catch(const std::exception &e){return rejected("无法设置该转职或觉醒",e.what());}
}
CharacterAdvancementResult CharacterAdvancementTransaction::retry(CharacterStore &store,World &world) {
    if(!pending_)return rejected("没有待处理的身份设置");
    if(pending_->store!=&store||pending_->world!=&world)return rejected("待处理身份属于其他世界或存档");
    try {
        validateFrozen();
        if(!pending_->durable) {
            pending_->receipt=store.hasPendingCommit()?store.retryPending():store.receipt(pending_->requestId);
            if(pending_->receipt.is_null()||pending_->receipt.at("request_id")!=pending_->requestId)
                throw std::invalid_argument("Pending identity receipt is missing or foreign");
            pending_->durable=true;
        }
        return publish();
    }catch(const std::exception &e){CharacterAdvancementResult r;r.state=CharacterAdvancementState::Pending;r.message="身份保存待重试";r.error=e.what();return r;}
}
} // namespace dnf
