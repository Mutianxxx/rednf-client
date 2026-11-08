#include "dnf/combat.hpp"
#include "dnf/female_gunner_world.hpp"
#include "dnf/effect_plan.hpp"
#include <algorithm>
#include <set>
#include <stdexcept>
#include <type_traits>

namespace dnf {
std::string World::neutralPlayerReactionGate(const Actor &actor) const {
    const int job=identity_.jobId;
    if(job!=0&&job!=1&&job!=2&&job!=3&&job!=4&&job!=5&&job!=8)
        return "player_reaction_job_consumer_unavailable";
    if(active_>=0||basicAttacking()||actor.recovery||actor.z!=0||actor.vz!=0||actor.capturedBy>=0||captured_>=0)
        return "act_player_prepared_action_interruption_consumer_missing";
    // Source BodyAttack owns one cancellable value action. Spawned entities,
    // basic attacks and foreign controllers still need their own consumers.
    if(experimentalRuntime_&&(!experimentalAdapter_||
       ((!experimentalRuntime_->neutralReactionReady()&&!experimentalRuntime_->sourceBodyReactionReady())||
        !experimentalAdapter_->neutralReactionReady())&&!experimentalAdapter_->movingReactionReady(*experimentalRuntime_)))
        return "act_player_experimental_action_entity_interruption_consumer_missing";
    if(squirrelActions_&&squirrelActionDiagnostics().value("active",false))
        return "act_player_squirrel_prepared_cleanup_missing";
    if(femaleGunnerWorld_&&!femaleGunnerWorld_->neutralReactionReady())
        return "act_player_gunner_entity_capture_prepared_cleanup_missing";
    return {};
}
World::PreparedPlayerDefense World::preparePlayerDefense(DamageRequest request) const {
    PreparedPlayerDefense candidate;candidate.request=std::move(request);
    candidate.receipt={{"policy","inferred-player-neutral-ground-reaction-v1"},{"classification","inferred_beta"},
        {"character",identity_.json()},{"no_live_publication",true}};
    if(experimentalRuntime_&&experimentalRuntime_->sourceBodyReactionReady()) {
        candidate.superArmor=experimentalRuntime_->sourceFrameSuperArmor();
        candidate.receipt["source_body_protection"]={{"policy","reviewed-source-action-explicit-frame-protection-v1"},
            {"classification","inferred_beta"},{"super_armor",candidate.superArmor},{"invincibility",false},
            {"action_sequence",*experimentalRuntime_->activeActionSequence()},
            {"semantics","HP, source statuses and hit-pause resolve; ordinary reaction suppressed only on the reviewed armor frame; death always interrupts"}};
    }
    if(femaleGunnerWorld_&&identity_.jobId==5) {
        candidate.immune=femaleGunnerWorld_->invulnerable();
        candidate.receipt["quick_standing_immune"]=candidate.immune;
        if(!candidate.immune)femaleGunnerWorld_->applyDefense(candidate.request);
        candidate.receipt["defense_consumer"]="actual FemaleGunnerWorld::applyDefense on private DamageRequest";
    }
    return candidate;
}
World::PreparedPlayerReaction World::prepareNeutralPlayerReaction(const Actor &actor) const {
    const auto gate=neutralPlayerReactionGate(actor);if(!gate.empty())throw std::invalid_argument(gate);
    PreparedPlayerReaction prepared;prepared.skills=skillState_;prepared.inputs=inputs_;
    prepared.effects=effects;prepared.pendingEffects=pendingEffects_;
    const bool sourceBody=experimentalRuntime_&&experimentalRuntime_->sourceBodyReactionReady();
    const bool sourceMoving=experimentalRuntime_&&experimentalRuntime_->sourceMovingReactionReady();
    if(experimentalRuntime_)prepared.runtime=sourceMoving?experimentalRuntime_->prepareSourceMovingReaction():
        sourceBody?experimentalRuntime_->prepareSourceBodyReaction():experimentalRuntime_->prepareNeutralReaction();
    if(sourceMoving)prepared.movingDeathRuntime=experimentalRuntime_->prepareSourceMovingReaction(true);
    auto queue=prepared.inputs.snapshot([](const Input &in){return Json{{"ns",in.ns},{"key",in.key},{"down",in.down}};});
    auto &rows=queue.at("pending");
    rows.erase(std::remove_if(rows.begin(),rows.end(),[](const Json &row){
        const auto &in=row.at("payload");const int key=in.at("key");return in.at("down").get<bool>()&&(key<0||key>3);
    }),rows.end());
    prepared.inputs.restore(queue,[](const Json &in){return Input{in.at("ns").get<int64_t>(),in.at("key").get<int>(),in.at("down").get<bool>()};});
    // Remove owned attached layers and their detached ALS descendants as one
    // private graph. Unrelated projectiles/objects remain live and unchanged.
    std::set<int> removed;
    for(const auto &effect:prepared.effects)if(effect.attached)removed.insert(effect.id);
    for(const auto &effect:prepared.pendingEffects)if(effect.attached)removed.insert(effect.id);
    bool more=true;while(more){more=false;
        for(const auto *list:{&prepared.effects,&prepared.pendingEffects})for(const auto &effect:*list)
            if(effect.alsParentId>=0&&removed.count(effect.alsParentId))more|=removed.insert(effect.id).second;
    }
    const auto erase=[&](std::vector<Effect> &list){list.erase(std::remove_if(list.begin(),list.end(),[&](const Effect &effect){return removed.count(effect.id);}),list.end());};
    erase(prepared.effects);erase(prepared.pendingEffects);
    if(sourceMoving) {
        prepared.movingDeathEffects=prepared.effects;prepared.movingDeathPendingEffects=prepared.pendingEffects;
        const auto removeOwned=[](std::vector<Effect> &list) {
            list.erase(std::remove_if(list.begin(),list.end(),[](const auto &fx){return fx.sourceTreePolicy=="inferred-current1031-watercannon-tree-v1";}),list.end());
        };
        removeOwned(*prepared.movingDeathEffects);removeOwned(*prepared.movingDeathPendingEffects);
    }

    const auto &appearance=characterAppearance();Json sources=Json::array();std::set<std::tuple<std::string,std::array<int,2>,bool>> visited;
    const auto validate=[&](const auto &self,const std::string &path,std::array<int,2> variation,bool body,size_t depth)->void {
        if(depth>12||visited.size()>=4096)throw std::length_error("Player reaction visual closure budget exhausted");
        if(!visited.emplace(path,variation,body).second)return;
        const auto animation=assets_.animation(path);if(animation->frames.empty())throw std::invalid_argument("Empty player reaction animation: "+path);
        size_t transparentFrames=0;
        for(const auto &frame:animation->frames)if(!frame.image.empty()) {
            const auto image=appearanceImage(frame.image,variation,body);
            if(image.find('%')!=std::string::npos)throw std::invalid_argument("Unresolved player reaction image pattern: "+image);
            const auto pixels=assets_.pixels(image,frame.imageFrame);
            // IMG explicitly admits zero-area frames for hidden equipment
            // layers. Successful decode still validates archive/member/frame
            // bounds, link chains and encoded data; absence is an exception.
            if(!pixels.width||!pixels.height)++transparentFrames;
        }
        const auto events=animationEffectEvents(pvf_,assets_,path);
        sources.push_back({{"animation",makeSourceRef(pvf_,path).json()},{"transparent_img_frames",transparentFrames},{"als_diagnostics",events.diagnostics}});
        for(const auto &event:events.events)if(event.kind!=EffectEventKind::Remove)self(self,event.animation,{0,0},false,depth+1);
    };
    // Validate both accepted nonlethal and lethal presentation before damage
    // randomness; a lethal roll must never discover a missing down resource.
    for(const char *tag:{"[damage motion 1]","[down motion]"}) {
        const auto path=characterSource().motion(tag);const auto *binding=appearanceBodyMotion(appearance,path);
        if(path.empty()||!binding)throw std::invalid_argument("Player reaction lacks exact CHR/appearance binding: "+std::string(tag));
        validate(validate,path,{appearance.bodyVariation(),appearance.bodyVariation()},true,0);
        for(const auto &layer:appearance.orderedLayers()) {
            const auto child=appearanceLayerMotion(layer,*binding);if(child.empty())continue;
            validate(validate,child,layer.variation,false,0);
        }
    }
    prepared.receipt={{"policy","inferred-player-neutral-ground-reaction-v1"},{"classification","inferred_beta"},
        {"identity",identity_.json()},{"sources",sources},{"removed_attached_graph",removed.size()},
        {"input_policy","cancel action DOWN; preserve movement, KEYUP and queue sequence watermark"},
        {"mp_policy","accepted MP unchanged; no refund"},{"cooldown_policy","copied unchanged; active exit-CD remains gated"},
        {"reaction_base_ms",250},{"guard_ms",180},{"native_1031_controller_verified",false}};
    if(sourceBody) {
        prepared.receipt["policy"]="inferred-player-source-body-ground-reaction-v1";
        prepared.receipt["action_sequence"]=*experimentalRuntime_->activeActionSequence();
        prepared.receipt["source_action_cleanup"]="private runtime cancel + noexcept adapter body-ledger reset + Actor clock/layers/camera + owned attached effect graph";
        prepared.receipt["action_state"]="prepared cancellation; discarded unless ordinary reaction, control status or lethal damage requires interruption";
    }
    if(sourceMoving) {
        prepared.receipt["policy"]="inferred-player-source-moving-ground-reaction-v1";
        prepared.receipt["source_moving_cleanup"]="private body/recoil cancellation; independent source PO/ledger survive ordinary reaction; lethal publication retires runtime, roots and all source-tree children together";
        prepared.receipt["source_parent_semantics"]="NUT parent is character identity, not current action; this ground host policy remains inferred_beta";
    }
    return prepared;
}
void World::publishNeutralPlayerReaction(PreparedPlayerReaction &prepared) noexcept {
    static_assert(std::is_nothrow_swappable<CharacterSkillState>::value,"Skill ledger publication must not throw");
    static_assert(std::is_nothrow_swappable<SequencedCommandQueue<Input>>::value,"Input publication must not throw");
    static_assert(std::is_nothrow_move_assignable<ExperimentalCharacterRuntime>::value,"Controller publication must not throw");
    using std::swap;swap(skillState_,prepared.skills);swap(inputs_,prepared.inputs);
    if(player.dead&&prepared.movingDeathRuntime) {
        assert(prepared.movingDeathEffects&&prepared.movingDeathPendingEffects&&experimentalRuntime_&&experimentalAdapter_);
        effects.swap(*prepared.movingDeathEffects);pendingEffects_.swap(*prepared.movingDeathPendingEffects);
        *experimentalRuntime_=std::move(*prepared.movingDeathRuntime);experimentalAdapter_->publishMovingDeathReaction();
    } else {
        effects.swap(prepared.effects);pendingEffects_.swap(prepared.pendingEffects);
        if(prepared.runtime){assert(experimentalRuntime_);*experimentalRuntime_=std::move(*prepared.runtime);experimentalAdapter_->publishNeutralReaction();}
    }
    if(prepared.femaleDeath){assert(femaleGunnerWorld_);femaleGunnerWorld_->publishNeutralDeath(std::move(prepared.femaleDeath));}
    clearPickupAction();clearBasicPlayback();clearSkillInputTransients();dashAttackGlide_.reset();
    for(size_t i=4;i<held_.size();++i)held_[i]=false;
    commandHistory_.clear();running_=false;lastLeft_=lastRight_=-100000;
    bufferedSkill_=-1;bufferedSkillCommand_=false;bufferedSkillUntil_=0;queued_=false;
    active_=-1;stage_=0;activeCooldownMs_=0;actionInstance_=0;captured_=-1;
    goreCrossPhase_=0;goreCrossPhaseTick_=-1;goreCrossEventEffect_=-1;goreCrossEvents_.reset();
    hits_.clear();hitCounts_.clear();hopFinalHits_.clear();attackVolumes.clear();
}
} // namespace dnf
