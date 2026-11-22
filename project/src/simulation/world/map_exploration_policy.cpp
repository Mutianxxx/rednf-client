#include "dnf/combat.hpp"
#include "dnf/act_world_host.hpp"
#include "dnf/monster_behavior.hpp"
#include <algorithm>
#include <stdexcept>

namespace dnf {
namespace {
enum class LegacyOutgoingRoute { DirectContact, SourceProjectile };
// These are the three source-qualified adapters exercised by the existing
// damage/status World tests. Their approach/calibration remains inferred beta
// behavior. Resource names alone never opt another MOB into this controller.
struct LegacyExplorationAdapter {
    int id;
    const char *path, *hash, *controller, *hurtSound, *deathSound;
    size_t attackVariantCount;
    LegacyOutgoingRoute outgoingRoute;
};
constexpr const char *legacyPackage = "d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d";
constexpr LegacyExplorationAdapter legacyAdapters[] = {
    {1,"monster/goblin/goblin.mob","a90a25f8ab3d6fb132d0ce29b5b378fbc4c9800ad8b2b87a6c91405706822d89",
        "inferred-goblin-melee-v1","R_GOBLIN_DMG","R_GOBLIN_DIE",1,LegacyOutgoingRoute::DirectContact},
    {2,"monster/goblin/goblinthrower.mob","c9fc414e1c3f2459743076e67c23fe820ace4ba890707ddbb78d5efd9aee6304",
        "inferred-goblin-source-projectile-v1","R_GOBLIN_DMG","R_GOBLIN_DIE",1,LegacyOutgoingRoute::SourceProjectile},
    {11,"monster/tau/tauarmy.mob","91a01470124caba58bb181a57bdd708857f27d1f8d8185108c562b0ac8cd8970",
        "inferred-source-heading-approach-v1","R_TAU_DMG","TAU_DIE",2,LegacyOutgoingRoute::DirectContact}
};
bool hasActFields(const Script &source) {
    return std::any_of(source.fields.begin(),source.fields.end(),[](const Field &field) {
        const auto tag=normalize(field.tag);
        return tag=="[basic action]" || tag=="[waiting action]" || tag=="[action list]" || tag=="[attack action]";
    });
}
void preflightMotion(Assets &assets,const MonsterMotion &motion,bool needHurtBox=false) {
    if(!motion.valid()) throw std::runtime_error(motion.error.empty()?"Missing source motion: "+motion.state:motion.error);
    bool hurt=false;
    const auto animation=[&](const Animation &value) {
        for(const auto &frame:value.frames) {
            if(!frame.image.empty()) {
                const auto image=assets.pixels(frame.image,frame.imageFrame);
                if(image.width<=0 || image.height<=0) throw std::runtime_error("Empty source motion image: "+frame.image);
            }
        }
    };
    animation(*motion.base);
    for(const auto &frame:motion.base->frames) for(const auto &box:frame.boxes) if(box.type==14) hurt=true;
    for(const auto &track:motion.tracks) if(track.animation) animation(*track.animation);
    if(needHurtBox && !hurt) throw std::runtime_error("Source stay motion has no type14 hurt volume");
}
} // namespace

void World::validateSceneActorCapacity(size_t count) const {
    auto prepared=entities_;
    prepared.retireAll();
    prepared.create();
    for(size_t i=0;i<count;++i) prepared.create();
}

bool World::explorationConsumerBound(const Actor &actor) const {
    if(!mapExplorationActive_) return true;
    const auto found=explorationConsumers_.find(actor.handle);
    if(found==explorationConsumers_.end()) return false;
    const auto &cap=found->second;
    return actor.handle && normalize(actor.monsterPath)==cap.memberPath && actor.sourceId==cap.sourceId;
}
bool World::explorationAllowsIncoming(const Actor &actor) const {
    if(!mapExplorationActive_) return true;
    if(!explorationConsumerBound(actor)) return false;
    const auto &cap=explorationConsumers_.at(actor.handle);
    // No snapshot or legacy damage fallback may be introduced after preflight.
    return mapExplorationGeometryAvailable_ && !walkRects.empty() && cap.incomingDamage &&
        actor.combatAttributes && actor.combatAttributes->usable() &&
        actor.combatAttributes->sources==cap.combatSources;
}
bool World::explorationAllowsLegacyAi(const Actor &actor) const {
    return !mapExplorationActive_ || (explorationConsumerBound(actor) && mapExplorationGeometryAvailable_ &&
        !walkRects.empty() && explorationConsumers_.at(actor.handle).legacyAutonomousController);
}
bool World::explorationAllowsSourceActions(const Actor &actor) const {
    return !mapExplorationActive_ || (explorationConsumerBound(actor) && mapExplorationGeometryAvailable_ &&
        !walkRects.empty() && explorationConsumers_.at(actor.handle).sourceActions);
}
std::string World::explorationMonsterSound(const Actor &actor,bool dead) const {
    if(!explorationConsumerBound(actor)) return {};
    const auto &cap=explorationConsumers_.at(actor.handle);
    return cap.receipt.value(dead?"death_sound":"hurt_sound",std::string());
}

void World::setMapExplorationPolicy(bool geometryAvailable) {
    // The application publishes a prepared scene and synchronizes handles
    // before this call. Preparation here cannot allocate entities, attacks,
    // effects, statuses, random streams, source actions or live actor changes.
    if(mapExplorationActive_) throw std::logic_error("Map exploration policy is already installed; change scene first");
    std::map<EntityHandle,ExplorationMonsterConsumers> prepared;
    const bool geometry=geometryAvailable && !walkRects.empty();
    for(const auto &actor:monsters) {
        if(!actor.handle || static_cast<const World *>(this)->resolveActor(actor.handle)!=&actor)
            throw std::invalid_argument("Map exploration requires synchronized current actor handles");
        ExplorationMonsterConsumers cap;
        cap.memberPath=normalize(actor.monsterPath);cap.sourceId=actor.sourceId;
        cap.receipt={{"owner",actor.handle.json()},{"source_id",actor.sourceId},
            {"classification","inferred_beta"},{"whole_monster_complete",false},
            {"diagnostics",Json::array()},{"motions",Json::array()}};
        const auto blocked=[&](const std::string &consumer,const std::string &reason,const Json &details=Json::object()) {
            // ordered_json object insertion can relocate its child values.
            // Reacquire the array after other receipt fields have been added.
            cap.receipt["diagnostics"].push_back({{"consumer",consumer},{"reason",reason},{"details",details}});
        };
        if(!geometry) blocked("movement","source_walk_geometry_unavailable");
        try {
            if(cap.memberPath.empty()) throw std::runtime_error("Explicit source MOB path is required");
            const auto source=pvf_.script(cap.memberPath);
            const auto ref=makeSourceRef(pvf_,source.path);
            cap.receipt["source"]=ref.json();
            const auto sourceHash=sha256(source.rawBytes);
            const LegacyExplorationAdapter *adapter=nullptr;
            for(const auto &candidate:legacyAdapters) if(actor.sourceId==candidate.id && cap.memberPath==candidate.path &&
                pvf_.identity()==legacyPackage && sourceHash==candidate.hash) adapter=&candidate;
            if(adapter) {
                cap.receipt["controller_policy"]=adapter->controller;
                cap.receipt["hurt_sound"]=adapter->hurtSound;cap.receipt["death_sound"]=adapter->deathSound;
                cap.receipt["evidence"]="source-qualified existing World damage/projectile/Tau status regression adapters";
            } else {
                blocked("legacy_autonomous_controller","no_source_qualified_controller_registration");
                blocked("monster_audio","no_source_qualified_monster_sound_dispatch");
            }
            bool attributes=false;
            try {
                if(!usesSourceGrowth() || !actor.combatAttributes || !actor.combatAttributes->usable() ||
                    actor.hp<=0 || actor.maxHp<=0 || !actor.sourceStats.contains("combat") ||
                    actor.sourceStats.at("combat")!=actor.combatAttributes->snapshot())
                    throw std::runtime_error("Usable source combat and matching frozen attribute receipt are required");
                const auto &bound=actor.combatAttributes->source.monster;
                if(normalize(bound.path)!=source.path || sha256(bound.rawBytes)!=sourceHash ||
                    bound.source.value("package_identity",std::string())!=pvf_.identity())
                    throw std::runtime_error("Frozen combat attributes do not match the selected source MOB identity");
                attributes=true;cap.combatSources=actor.combatAttributes->sources;
            } catch(const std::exception &error) { blocked("incoming_damage","source_combat_attributes_unavailable",{{"error",error.what()}}); }
            bool response=true;
            cap.captureAllowed=true; // Explicit inferred default for old MOBs without a grab field.
            cap.receipt["capture_policy"]="source-is-grabable-or-inferred-legacy-absent-allows-v1";
            Json protectionFields=Json::array();
            size_t grabFields=0;
            for(size_t ordinal=0;ordinal<source.fields.size();++ordinal) {
                const auto &field=source.fields[ordinal];const auto tag=normalize(field.tag);
                const bool grab=tag=="[is grabable]";
                const bool protection=tag=="[event super]" || tag=="[event super armor]" || tag=="[event superarmor]" ||
                    tag=="[super armor]" || tag=="[superarmor]" || tag=="[unbreakable]" ||
                    tag=="[invincible]" || tag=="[invincibility]" || tag=="[is invincible]" ||
                    tag=="[damage immunity]" || tag=="[ghost]" || tag=="[is ghost]";
                if(!grab && !protection) continue;
                const auto end=ordinal+1<source.fields.size()?source.fields[ordinal+1].offset:source.rawBytes.size();
                const Json entry={{"tag",field.tag},{"values",field.values},
                    {"source",makeSourceRef(pvf_,source.path,field.offset,end-field.offset,ordinal,"exploration/protection").json()}};
                protectionFields.push_back(entry);
                if(grab) {
                    ++grabFields;
                    if(grabFields!=1 || field.values.size()!=1 || !field.values[0].is_number_integer() ||
                        (field.values[0]!=0 && field.values[0]!=1)) {
                        cap.captureAllowed=false;blocked("capture","source_grab_flag_ambiguous",entry);
                    } else if(field.values[0]==0) cap.captureAllowed=false;
                } else {
                    // A whole source protection program cannot be discarded
                    // while accepting ordinary contacts. Its exact field and
                    // bytes stay inspectable until a real consumer is added.
                    response=false;blocked("incoming_damage","source_protection_consumer_unavailable",entry);
                }
            }
            cap.receipt["protection_fields"]=std::move(protectionFields);
            // These are all generic recovery states currently consumed by
            // damage/knockdown/get-up. None may acquire a Goblin fallback.
            for(const auto *state:{"stay","damage1","damage2","down","sit"}) {
                const auto motion=compileMonsterMotion(pvf_,assets_,source.path,state);
                try {
                    preflightMotion(assets_,*motion,std::string(state)=="stay");
                    cap.receipt["motions"].push_back({{"state",state},{"entry",motion->entry},{"references",motion->references}});
                } catch(const std::exception &error) {
                    response=false;blocked("incoming_damage","source_response_motion_unavailable",{{"state",state},{"error",error.what()},{"issues",motion->issues}});
                }
            }
            try {
                const auto death=compileMonsterMotion(pvf_,assets_,source.path,"death");
                if(death->configured) {
                    preflightMotion(assets_,*death);
                    cap.receipt["death"]={{"route","last-action"},{"entry",death->entry},{"references",death->references}};
                } else {
                    const auto profile=readMonsterDeathProfile(pvf_,assets_,source.path);
                    if(!profile.valid) throw std::runtime_error(profile.issues.dump());
                    for(const auto &path:{profile.flash?profile.flashAnimation:"",profile.smoke?profile.smokeAnimation:""})
                        if(!path.empty()) preflightMotion(assets_,*compileMonsterAnimation(pvf_,assets_,path,"death-component"));
                    cap.receipt["death"]={{"route","shared-source-palette"},{"raw",profile.raw},{"classification","inferred_beta_lifecycle"}};
                }
            } catch(const std::exception &error) {
                response=false;blocked("incoming_damage","source_death_consumer_unavailable",{{"error",error.what()}});
            }
            cap.incomingDamage=geometry && attributes && response;
            const bool sourceAct=hasActFields(source);
            // The service owns exact per-action dependency compilation/bind
            // transactions. Eligibility does not claim all ACT programs work.
            cap.sourceActions=geometry && sourceAct && bool(actHost_);
            if(sourceAct) {
                cap.receipt["source_action_route"]=selectMonsterAction(pvf_,source,"stay").json();
                cap.receipt["source_action_policy"]="per-request-source-route-compile-bind";
                if(!actHost_) blocked("source_actions","source_action_host_unconfigured");
            }
            if(adapter && !sourceAct && attributes && geometry) {
                try {
                    preflightMotion(assets_,*compileMonsterMotion(pvf_,assets_,source.path,"move"));
                    const auto attacks=source.values("[attack motion]");
                    // The registered Goblin/thrower controllers select slot 0;
                    // Tau alternates slots 0 and 1. Preserve every authored
                    // slot, but preflight the ones this controller consumes.
                    // Extra motion slots need their own future consumers.
                    cap.receipt["authored_attack_motions"]=attacks;
                    cap.receipt["controller_attack_slots"]=Json::array();
                    if(attacks.size()<adapter->attackVariantCount)
                        throw std::runtime_error("Missing attack motion slot required by the registered controller");
                    for(size_t index=0;index<adapter->attackVariantCount;++index) {
                        cap.receipt["controller_attack_slots"].push_back(index);
                        if(!attacks[index].is_string() || attacks[index].get<std::string>().empty())
                            throw std::runtime_error("Empty or non-string source attack motion operand");
                        Actor candidate=actor;candidate.attackVariant=int(index);
                        candidate.animation="attack1";
                        candidate.animationPath=normalize((std::filesystem::u8path(source.path).parent_path()/
                            std::filesystem::u8path(attacks[index].get<std::string>())).generic_u8string());
                        preflightMotion(assets_,*compileMonsterAnimation(pvf_,assets_,candidate.animationPath,"attack1"));
                        if(adapter->outgoingRoute==LegacyOutgoingRoute::DirectContact) {
                            const auto path=monsterAttackPath(candidate);
                            const auto attack=readAttackDamage(pvf_.script(path),AttackStatusConsumer::StunHostV1);
                            if(!attack.usable()) throw std::runtime_error("Source outgoing ATK unavailable: "+path);
                        }
                    }
                    cap.receipt["outgoing_route"]=adapter->outgoingRoute==LegacyOutgoingRoute::SourceProjectile?
                        "source-passive-object-projectile":"source-direct-contact";
                    if(adapter->outgoingRoute==LegacyOutgoingRoute::SourceProjectile) {
                        const auto projectile=prepareMonsterProjectile(actor);
                        if(!projectile.usable()) throw std::runtime_error(projectile.snapshot().dump());
                        cap.receipt["projectile"]=projectile.snapshot();
                    }
                    cap.legacyAutonomousController=true;
                } catch(const std::exception &error) { blocked("legacy_autonomous_controller","source_controller_dependencies_unavailable",{{"error",error.what()}}); }
            }
        } catch(const std::exception &error) { blocked("source_identity","source_member_unavailable",{{"error",error.what()}}); }
        cap.receipt["incoming_damage"]=cap.incomingDamage;
        cap.receipt["capture_allowed"]=cap.incomingDamage && cap.captureAllowed;
        cap.receipt["legacy_autonomous_controller"]=cap.legacyAutonomousController;
        cap.receipt["source_actions"]=cap.sourceActions;
        if(!prepared.emplace(actor.handle,std::move(cap)).second)
            throw std::invalid_argument("Repeated entity handle in exploration actors");
    }
    explorationConsumers_=std::move(prepared);
    mapExplorationGeometryAvailable_=geometry;mapExplorationActive_=true;
}
Json World::mapExplorationPolicy() const {
    Json actors=Json::array();
    for(const auto &[owner,cap]:explorationConsumers_) actors.push_back(cap.receipt);
    return {{"active",mapExplorationActive_},{"policy","source-consumer-map-exploration-v1"},
        {"geometry_available",mapExplorationGeometryAvailable_},{"missing_geometry_movement","blocked"},
        {"persistent",false},{"whole_map_complete",false},{"actors",actors}};
}
} // namespace dnf
