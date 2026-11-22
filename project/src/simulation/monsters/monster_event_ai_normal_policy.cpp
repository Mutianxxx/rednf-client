#include "dnf/combat.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *normalPolicy="inferred-normal-source-monster-event-ai-install-v1";
constexpr size_t diagnosticLimit=256;
void appendNormal(Json &rows,Json row) {
    rows.push_back(std::move(row));
    if(rows.size()>diagnosticLimit)
        rows.erase(rows.begin(),rows.begin()+std::ptrdiff_t(rows.size()-diagnosticLimit));
}
} // namespace

void World::prepareNormalMonsterEventAiBoundary() {
    // Source think is configured by the application for the frozen run tier.
    // Install before the AI-pause gate: real player contacts while paused must
    // still enter the same accepted-hit/window/pending transaction.
    if(!actHost_ || !monsterActionAiEnabled_ || !combat || mapExplorationActive_) return;
    std::set<EntityHandle> live;
    for(const auto &actor:monsters) if(actor.handle && !actor.dead && actor.life==ActorLife::Alive &&
        actor.sourceStats.contains("spawn") && explorationAllowsSourceActions(actor)) live.insert(actor.handle);
    for(auto at=monsterEventAiNormalAttempts_.begin();at!=monsterEventAiNormalAttempts_.end();)
        if(!live.count(at->first)) at=monsterEventAiNormalAttempts_.erase(at); else ++at;
    // Keep handles/copies only. Future service implementations may replace
    // actor storage on publication just as the existing ACT consumer does.
    for(const auto owner:live) {
        const auto *actor=static_cast<const World *>(this)->resolveActor(owner);
        if(!actor || actor==&player) continue;
        MonsterEventAiNormalAttempt attempt;
        attempt.sourceId=actor->sourceId;attempt.memberPath=normalize(actor->monsterPath);
        attempt.difficulty=monsterActionAiDifficulty_;
        auto existing=monsterEventAiBindings_.find(owner);
        attempt.bound=existing!=monsterEventAiBindings_.end();
        if(attempt.bound)attempt.boundDifficulty=existing->second.route.difficulty;
        const auto previous=monsterEventAiNormalAttempts_.find(owner);
        if(previous!=monsterEventAiNormalAttempts_.end()) {
            const auto &old=previous->second;
            if(old.sourceId==attempt.sourceId && old.memberPath==attempt.memberPath &&
               old.difficulty==attempt.difficulty && old.bound==attempt.bound && old.boundDifficulty==attempt.boundDifficulty) continue;
        }
        Json receipt={{"kind","normal_monster_event_ai_install"},{"policy",normalPolicy},
            {"classification","inferred_beta"},{"tick",tick},{"owner",owner.json()},
            {"source_id",attempt.sourceId},{"member_path",attempt.memberPath},{"requested_difficulty",attempt.difficulty},
            {"installed",false},{"existing_binding_preserved",false},{"whole_ai_complete",false}};
        if(attempt.bound) {
            // This includes explicit/F7 bindings and same-generation room
            // continuation. Never replace its source, pending, window or RNG
            // key, and never claim it as an F7-owned registration.
            receipt["reason"]="existing_binding_preserved";receipt["existing_binding_preserved"]=true;
            receipt["route"]=existing->second.route.json();
            const bool sameSource=existing->second.sourceId==attempt.sourceId && existing->second.memberPath==attempt.memberPath;
            receipt["requested_source_matches_existing"]=sameSource;
            receipt["requested_difficulty_matches_existing"]=attempt.difficulty==attempt.boundDifficulty;
            if(!sameSource || attempt.difficulty!=attempt.boundDifficulty)
                receipt["diagnostic"]="existing_binding_differs_from_request; preserve pending and prepare a new scene before changing source/difficulty";
        } else {
            try {
                const auto mob=pvf_.script(attempt.memberPath);
                // Share the source-action discovery boundary. An ANI-only
                // legacy actor must not lose its existing autonomous behavior
                // solely because a no-action Event script can be parsed.
                const bool sourceAct=std::any_of(mob.fields.begin(),mob.fields.end(),[](const Field &field) {
                    const auto tag=normalize(field.tag);
                    return tag=="[basic action]" || tag=="[waiting action]" || tag=="[action list]" || tag=="[attack action]";
                });
                const auto route=selectMonsterEventAi(pvf_,mob,attempt.difficulty);
                receipt["route"]=route.json();
                if(!route.configured) receipt["reason"]="source_mob_has_no_ai_pattern";
                else if(!route.ok) receipt["reason"]="selected_source_difficulty_route_unavailable";
                else if(!sourceAct) receipt["reason"]="source_act_routes_unavailable; legacy_controller_preserved";
                else if(configureMonsterEventAi(owner,attempt.difficulty,MonsterEventAiPolicy::inferredIntegralChanceV1())) {
                    receipt["installed"]=true;receipt["reason"]="source_event_ai_installed";
                    // Cache the published state immediately. Next tick must
                    // not append a second 'preserved' record for our own bind.
                    attempt.bound=true;attempt.boundDifficulty=attempt.difficulty;
                } else {
                    receipt["reason"]="source_event_ai_install_rejected";
                    if(!monsterEventAiDiagnostics_.empty())receipt["details"]=monsterEventAiDiagnostics_.back();
                }
            } catch(const std::exception &error) {
                receipt["reason"]="source_event_ai_preparation_rejected";receipt["details"]=error.what();
            }
        }
        // Rejections are cached too. The immutable source package, typed
        // incarnation or explicit request must change before another attempt.
        // This operation does not allocate any game identity or draw RNG.
        appendNormal(monsterEventAiNormalDiagnostics_,std::move(receipt));
        monsterEventAiNormalAttempts_[owner]=std::move(attempt);
    }
}
} // namespace dnf
