#include "dnf/combat.hpp"
#include "dnf/act_world_host.hpp"
#include <algorithm>
#include <set>
#include <stdexcept>

namespace dnf {
namespace {
constexpr const char *testPolicy="inferred-f7-authored-monster-event-ai-test-v1";
// Discover names only inside the actual MOB AI block. In particular, a later
// [level of difficulty] block cannot introduce or replace an AI route.
std::vector<std::string> sourceDifficulties(const Script &source) {
    size_t begin=source.fields.size(),end=source.fields.size();
    for(size_t i=0;i<source.fields.size();++i) if(normalize(source.fields[i].tag)=="[ai pattern]") {
        if(begin!=source.fields.size() || !source.fields[i].values.empty())
            throw std::runtime_error("Repeated or operand-bearing MOB AI block");
        begin=i;
    }
    if(begin==source.fields.size()) return {};
    for(size_t i=begin+1;i<source.fields.size();++i) if(normalize(source.fields[i].tag)=="[/ai pattern]") {end=i;break;}
    if(end==source.fields.size() || !source.fields[end].values.empty())
        throw std::runtime_error("MOB AI block is unterminated or malformed");
    std::vector<std::string> names;
    for(size_t i=begin+1;i<end;++i) {
        const auto tag=normalize(source.fields[i].tag);
        if(tag.size()<3 || tag.front()!='[' || tag.back()!=']' || tag[1]=='/') continue;
        const auto name=tag.substr(1,tag.size()-2);
        if(name.size()>64 || name.find_first_not_of("abcdefghijklmnopqrstuvwxyz_")!=std::string::npos)
            throw std::runtime_error("MOB AI has a difficulty name unsupported by the exact-name test command");
        if(std::find(names.begin(),names.end(),name)!=names.end())
            throw std::runtime_error("MOB AI has repeated difficulty names");
        names.push_back(name);
    }
    return names;
}
} // namespace

void World::refreshExplorationMonsterEventAiTestPolicy() {
    // Only low-cost live identities enter this cache key. Source packages are
    // immutable for a World session; source routing/compilation is done once
    // per changed selection or actor incarnation, never every simulation tick.
    Json identities=Json::array();
    for(const auto &actor:monsters) identities.push_back({actor.handle.json(),actor.sourceId,
        actor.monsterPath,actor.dead,int(actor.life)});
    const auto selection=Json::array({mapExplorationActive_,debugOverrides_.enabled,
        debugOverrides_.monsterAiDifficulty}).dump();
    const auto signature=Json::array({selection,std::move(identities)}).dump();
    if(signature==monsterEventAiTestSignature_) return;
    Json receipt={{"policy",testPolicy},{"classification","inferred_beta"},
        {"exploration_only",true},{"map_exploration_active",mapExplorationActive_},
        {"test_mode_enabled",debugOverrides_.enabled},{"selected_difficulty",debugOverrides_.monsterAiDifficulty},
        {"available_difficulties",Json::array()},{"actors",Json::array()},
        {"installed",0},{"rejected",0},{"diagnostics",Json::array()},
        {"whole_ai_complete",false},{"persistent_continuation",false}};
    std::set<EntityHandle> cleanup;
    for(const auto owner:monsterEventAiTestOwners_) {
        const auto *actor=static_cast<const World *>(this)->resolveActor(owner);
        const auto found=monsterEventAiBindings_.find(owner);
        if(selection!=monsterEventAiTestSelection_ || !actor || actor->dead || actor->life!=ActorLife::Alive ||
            found==monsterEventAiBindings_.end() || normalize(actor->monsterPath)!=found->second.memberPath ||
            actor->sourceId!=found->second.sourceId) cleanup.insert(owner);
    }
    // Cancel only exact actions produced by this test policy. Other explicit
    // bindings, source stay actions and their clocks are left with their owner.
    for(const auto &[owner,id]:monsterEventAiTestInstances_) if(actHost_ && cleanup.count(owner)) {
        const auto found=actHost_->instances().find(id);
        if(found!=actHost_->instances().end() && found->second.owner==owner &&
            found->second.status==ActInstanceStatus::Running) {
            const auto cancelled=actHost_->cancel(id,"event_ai_test_policy_changed");
            if(!cancelled.ok) {
                receipt["diagnostics"].push_back({{"reason","test_action_cancellation_failed"},
                    {"owner",owner.json()},{"instance",id},{"details",cancelled.diagnostics}});
                receipt["state"]="cleanup_blocked";
                // Match World::cancelSourceActions: fail the boundary instead
                // of continuing with a supposedly disabled moving action.
                // Ownership is retained and the blocked receipt is inspectable.
                monsterEventAiTestReceipt_=std::move(receipt);
                throw std::runtime_error("Event.ai test action cancellation failed: "+cancelled.error);
            }
        }
    }
    // Stage all pending-outcome allocations before dropping registrations.
    auto pending=monsterEventAiPending_;auto diagnostics=monsterEventAiDiagnostics_;
    pending.erase(std::remove_if(pending.begin(),pending.end(),[&](const PendingMonsterEventHit &event) {
        if(!cleanup.count(event.target)) return false;
        diagnostics.push_back({{"kind","monster_event_ai_outcome"},{"owner",event.target.json()},
            {"accepted_event",event.hit.eventId},{"accepted_tick",event.acceptedTick},{"evaluation_tick",tick},
            {"ok",false},{"result","cancelled"},{"reason","event_ai_test_policy_changed"},
            {"classification","transient_cancel"},{"whole_monster_complete",false}});
        return true;
    }),pending.end());
    if(diagnostics.size()>256) diagnostics.erase(diagnostics.begin(),diagnostics.begin()+std::ptrdiff_t(diagnostics.size()-256));
    auto bindings=monsterEventAiBindings_;auto windows=monsterDamageWindows_;
    for(const auto owner:cleanup) {
        bindings.erase(owner);
        const auto window=windows.find(owner);
        // This test registration owns its initial MOB window. Preserve later
        // explicit ACT configuration, whose private batch has separate origin.
        if(window!=windows.end()&&window->second.receipt.value("origin",std::string())=="source MOB consumer install")windows.erase(window);
    }
    monsterEventAiPending_=std::move(pending);monsterEventAiDiagnostics_=std::move(diagnostics);
    monsterEventAiBindings_=std::move(bindings);monsterDamageWindows_=std::move(windows);
    // An actor that had its test action cancelled returns through the existing
    // source stay queue, preserving all authored action cooldowns.
    std::vector<EntityHandle> resume;
    for(const auto &[owner,id]:monsterEventAiTestInstances_) if(cleanup.count(owner)) {
        const auto *actor=static_cast<const World *>(this)->resolveActor(owner);
        if(actor && !actor->dead && actor->life==ActorLife::Alive && explorationAllowsSourceActions(*actor)) resume.push_back(owner);
    }
    for(const auto owner:cleanup) {monsterEventAiTestOwners_.erase(owner);monsterEventAiTestInstances_.erase(owner);}
    for(const auto owner:resume) {
        try {requestSourceMonsterAction(owner,"stay");}
        catch(const std::exception &error) {receipt["diagnostics"].push_back({{"reason","source_stay_resume_rejected"},{"owner",owner.json()},{"details",error.what()}});}
    }
    const bool enabled=mapExplorationActive_ && debugOverrides_.enabled && !debugOverrides_.monsterAiDifficulty.empty();
    receipt["state"]=!mapExplorationActive_?"ordinary_scene_policy_disabled":
        !debugOverrides_.enabled?"test_mode_disabled":debugOverrides_.monsterAiDifficulty.empty()?"selection_disabled":"selected";
    std::set<std::string> names;
    std::vector<EntityHandle> owners;
    if(mapExplorationActive_) for(const auto &actor:monsters) if(actor.handle && !actor.dead && actor.life==ActorLife::Alive) owners.push_back(actor.handle);
    for(const auto owner:owners) {
        Json row={{"owner",owner.json()},{"installed",false}};
        try {
            const auto *actor=static_cast<const World *>(this)->resolveActor(owner);
            if(!actor || actor->monsterPath.empty()) throw std::runtime_error("Current source MOB is unavailable");
            const auto source=pvf_.script(actor->monsterPath);
            row["source"]=makeSourceRef(pvf_,source.path).json();
            const auto available=sourceDifficulties(source);row["available_difficulties"]=available;
            names.insert(available.begin(),available.end());
            if(!enabled) row["reason"]=receipt["state"];
            else if(monsterEventAiTestOwners_.count(owner) && monsterEventAiBindings_.count(owner)) {
                row["installed"]=true;row["route"]=monsterEventAiBindings_.at(owner).route.json();
            }
            else if(monsterEventAiBindings_.count(owner)) row["reason"]="explicit_external_binding_preserved";
            else {
                const auto route=selectMonsterEventAi(pvf_,source,debugOverrides_.monsterAiDifficulty);
                row["route"]=route.json();
                if(!route.configured) row["reason"]="source_mob_has_no_ai_pattern";
                else if(!route.ok) row["reason"]="selected_source_difficulty_route_unavailable";
                else if(!explorationAllowsSourceActions(*actor)) row["reason"]="exploration_source_action_consumer_unavailable";
                else {
                    auto testOwners=monsterEventAiTestOwners_;testOwners.insert(owner);
                    row["installed"]=configureMonsterEventAi(owner,debugOverrides_.monsterAiDifficulty,
                        MonsterEventAiPolicy::inferredIntegralChanceV1());
                    if(row["installed"]==true) monsterEventAiTestOwners_=std::move(testOwners);
                    else {
                        row["reason"]="source_event_ai_install_rejected";
                        // The service's exact route/compile diagnostic is
                        // retained for feedback, rather than a success marker.
                        if(!monsterEventAiDiagnostics_.empty()) row["details"]=monsterEventAiDiagnostics_.back();
                    }
                }
            }
        } catch(const std::exception &error) {row["reason"]="source_ai_catalog_rejected";row["details"]=error.what();}
        if(row["installed"]==true) receipt["installed"]=receipt["installed"].get<int>()+1;
        else if(enabled) receipt["rejected"]=receipt["rejected"].get<int>()+1;
        receipt["actors"].push_back(std::move(row));
    }
    for(const auto &name:names) receipt["available_difficulties"].push_back(name);
    monsterEventAiTestReceipt_=std::move(receipt);monsterEventAiTestSignature_=signature;
    monsterEventAiTestSelection_=selection;
}

Json World::monsterEventAiTestPolicy() const {
    if(!monsterEventAiTestReceipt_.empty()) return monsterEventAiTestReceipt_;
    return {{"policy",testPolicy},{"classification","inferred_beta"},{"exploration_only",true},
        {"map_exploration_active",mapExplorationActive_},{"test_mode_enabled",debugOverrides_.enabled},
        {"selected_difficulty",debugOverrides_.monsterAiDifficulty},{"state","not_prepared"},
        {"available_difficulties",Json::array()},{"actors",Json::array()},
        {"installed",0},{"rejected",0},{"whole_ai_complete",false},{"persistent_continuation",false}};
}
} // namespace dnf
