#include "dnf/act_world_host.hpp"
#include "dnf/axis_motion.hpp"
#include "dnf/collision.hpp"
#include "dnf/female_gunner_world.hpp"
#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace dnf {
namespace {
constexpr const char *worldHostLegacyPolicy="inferred-act-world-host-v2-status-lifecycle";
constexpr const char *worldHostPolicy="inferred-act-world-host-v3-continuation-receipts";
std::string canonical(std::string value) {
    return normalize(std::filesystem::u8path(normalize(std::move(value))).lexically_normal().generic_u8string());
}
uint64_t number(const Json &v) {
    if (!v.is_number_unsigned() && (!v.is_number_integer() || v.get<int64_t>() < 0))
        throw std::invalid_argument("ACT World checkpoint requires an unsigned integer");
    return v.get<uint64_t>();
}
double finite(const Json &v) {
    if (!v.is_number() || !std::isfinite(v.get<double>())) throw std::invalid_argument("Non-finite ACT World coordinate");
    return v.get<double>();
}
Json vectorJson(ActVec3 v) { return Json::array({v.x,v.y,v.z}); }
ActVec3 vectorValue(const Json &v) {
    if (!v.is_array() || v.size()!=3) throw std::invalid_argument("Invalid ACT World vector");
    return {finite(v[0]),finite(v[1]),finite(v[2])};
}
Json relationsJson(const ActEntityRelations &r) {
    Json hits=Json::array(); for (auto h:r.lastAttackSuccesses) hits.push_back(h.json());
    return {{"target",r.target.json()},{"last_attacker",r.lastAttacker.json()},
        {"last_success",r.lastAttackSuccess.json()},{"summon_master",r.summonMaster.json()},{"successes",hits}};
}
ActEntityRelations relationsValue(const Json &v) {
    ActEntityRelations r; r.target=EntityHandle::fromJson(v.at("target"));
    r.lastAttacker=EntityHandle::fromJson(v.at("last_attacker"));
    r.lastAttackSuccess=EntityHandle::fromJson(v.at("last_success"));
    r.summonMaster=EntityHandle::fromJson(v.at("summon_master"));
    if (!v.at("successes").is_array() || v.at("successes").size()>1024) throw std::invalid_argument("Invalid ACT hit-target list");
    for (const auto &h:v.at("successes")) r.lastAttackSuccesses.push_back(EntityHandle::fromJson(h));
    return r;
}
Json actorReceipt(const Actor &a) {
    return {{"handle",a.handle.json()},{"actor_id",a.id},{"monster_path",normalize(a.monsterPath)},
        {"position",Json::array({a.x,a.y,a.z})},{"direction",a.dir},{"hp",a.hp},{"mp",a.mp},
        {"dead",a.dead},{"life",int(a.life)},{"animation",a.animation},{"animation_path",a.animationPath},
        {"anim_start",a.animStart},{"pose_frame",a.poseFrame},{"source_stats",a.sourceStats},
        {"hit_stop_ticks",a.hitStopTicks},{"hit_stopped",a.hitStopped},{"captured_by",a.capturedBy},
        {"legacy_velocity",Json::array({a.vx,a.vy,a.vz})},{"stun_until",a.stunUntil}};
}
class RestoreGraphView final : public ActWorldView {
    const ActWorldRestoreGraph &graph_;
    const std::map<EntityHandle, ActEntityRelations> &relations_;
  public:
    RestoreGraphView(const ActWorldRestoreGraph &g, const std::map<EntityHandle, ActEntityRelations> &r)
        : graph_(g), relations_(r) {}
    const Actor *actor(EntityHandle h) const {
        if (!graph_.entities.valid(h)) return nullptr;
        if (graph_.player.handle == h && graph_.player.life != ActorLife::Removed) return &graph_.player;
        for (const auto &a : graph_.monsters) if (a.handle == h && a.life != ActorLife::Removed) return &a;
        return nullptr;
    }
    std::optional<ActEntityView> entity(EntityHandle h) const override {
        const auto *a = actor(h); if (!a) return std::nullopt;
        ActEntityView e; e.handle = h; e.position = {a->x, a->y, a->z}; e.direction = a->dir; e.hp = a->hp; e.mp = a->mp;
        e.alive = !a->dead && a->life == ActorLife::Alive;
        e.kind = h == graph_.player.handle ? ActEntityKind::Character : ActEntityKind::Monster;
        e.team = e.kind == ActEntityKind::Character ? 1 : 2;
        e.level = e.kind == ActEntityKind::Character ? graph_.characterLevel : a->sourceStats.value("level", 1);
        const auto found = relations_.find(h);
        if (found != relations_.end()) {
            const auto &r = found->second; e.target = r.target; e.lastAttacker = r.lastAttacker;
            e.lastAttackSuccess = r.lastAttackSuccess; e.lastAttackSuccesses = r.lastAttackSuccesses; e.summonMaster = r.summonMaster;
        }
        if (!e.target && e.kind == ActEntityKind::Monster) e.target = graph_.player.handle;
        return e;
    }
    std::vector<EntityHandle> entities() const override {
        std::vector<EntityHandle> out;
        if (actor(graph_.player.handle)) out.push_back(graph_.player.handle);
        for (const auto &a : graph_.monsters) if (actor(a.handle)) out.push_back(a.handle);
        std::sort(out.begin(), out.end()); return out;
    }
};
void hostJsonBounds(const Json &value, size_t depth, size_t &bytes) {
    if (depth > ActWorldRestoreBudget::maximumJsonDepth) throw std::invalid_argument("ACT host JSON depth budget exceeded");
    auto charge = [&](size_t count) {
        if (count > ActWorldRestoreBudget::maximumSnapshotBytes - bytes) throw std::invalid_argument("ACT host JSON byte/node budget exceeded");
        bytes += count;
    };
    charge(1);
    if (value.is_object()) for (auto it = value.begin(); it != value.end(); ++it) {
        charge(it.key().size()); hostJsonBounds(it.value(), depth + 1, bytes);
    }
    else if (value.is_array()) for (const auto &child : value) hostJsonBounds(child, depth + 1, bytes);
    else if (value.is_string()) charge(value.get_ref<const std::string &>().size());
    else if (value.is_number_float() && !std::isfinite(value.get<double>())) throw std::invalid_argument("ACT host JSON has a non-finite value");
    else if (value.is_binary() || value.is_discarded()) throw std::invalid_argument("ACT host JSON has a nonportable value");
}
void checkHostJson(const Json &value) {
    size_t bytes = 0; hostJsonBounds(value, 0, bytes);
    if (value.dump().size() > ActWorldRestoreBudget::maximumSnapshotBytes) throw std::invalid_argument("ACT host encoded snapshot byte budget exceeded");
}
int64_t signedValue(const Json &v) {
    if (!v.is_number_integer() || (v.is_number_unsigned() && v.get<uint64_t>() > uint64_t(INT64_MAX)))
        throw std::invalid_argument("ACT host signed integer is invalid");
    return v.get<int64_t>();
}
void sortStatusContacts(Json &status) {
    auto &contacts = status.at("contacts");
    std::sort(contacts.begin(), contacts.end(), [](const auto &a, const auto &b) { return a.at("identity").dump() < b.at("identity").dump(); });
}
bool sameSource(const SourceRef &a,const SourceRef &b) {
    return a.packageIdentity==b.packageIdentity && a.memberPath==b.memberPath && a.memberSha256==b.memberSha256;
}
ActSemanticPolicy policyValue(const Json &v) {
    ActSemanticPolicy p;p.id=v.at("id").get<std::string>();p.defaultLimit=number(v.at("default_limit"));
    if(!v.at("default_enabled").is_boolean())throw std::invalid_argument("Invalid ACT policy flag");
    p.defaultEnabled=v.at("default_enabled").get<bool>();p.defaultCheckTimeMs=number(v.at("default_check_time_ms"));
    const auto frames=number(v.at("frame_evaluation"));if(frames>1)throw std::invalid_argument("Invalid ACT frame policy");p.frameEvaluation=ActFrameEvaluation(frames);
    p.maximumInstructions=number(v.at("maximum_instructions"));p.maximumCommands=number(v.at("maximum_commands"));
    p.maximumPending=number(v.at("maximum_pending"));p.maximumRememberedEvents=number(v.at("maximum_remembered_events"));
    p.maximumFrameBoundaries=number(v.at("maximum_frame_boundaries"));
    if(p.json()!=v)throw std::invalid_argument("Saved ACT semantic contract does not match this host");return p;
}
ActCompileContext context(const Pvf &p,const ActResourceResolver &r,ActSemanticPolicy policy,
                          std::function<bool(const std::string &)> consumer) {
    ActCompileContext c; c.packageIdentity=p.identity(); c.resources=&r; c.policy=std::move(policy);
    c.hasCommandConsumer=std::move(consumer); return c;
}
} // namespace

ActWorldResources::ActWorldResources(Pvf &p,Assets &a,std::string staticIdentity)
    :pvf_(p),assets_(a),staticIdentity_(std::move(staticIdentity)) {
    if (staticIdentity_.empty()) throw std::invalid_argument("ACT resolver requires static-content identity");
    try {
        auto bytes=a.staticBytes("audio.xml"); audioSource_=staticSource("audio.xml",bytes);
        audio_=AudioCatalog(std::move(bytes),"audio.xml");
    } catch (const std::exception &) { /* Resolve(Sound) reports the missing source. */ }
    const auto list=p.script("passiveobject/passiveobject.lst");
    for (size_t i=0;i+1<list.tokens.size();i+=2) {
        const auto &id=list.tokens[i].at("value"),&name=list.tokens[i+1].at("value");
        if (id.is_number_integer() && name.is_string()) objects_[id.get<int>()]=canonical("passiveobject/"+name.get<std::string>());
    }
}
std::string ActWorldResources::path(const std::string &parent,const std::string &literal) const {
    std::set<std::string> found;
    const auto rel=std::filesystem::u8path(canonical(literal));
    if (rel.is_absolute() || rel.has_root_name()) throw std::invalid_argument("Absolute ACT resource reference");
    const auto dir=std::filesystem::u8path(parent).parent_path();
    for (auto candidate:{canonical((dir/rel).generic_u8string()),canonical(literal),canonical("monster/"+literal)})
        if (candidate!=".." && candidate.rfind("../",0)!=0 && pvf_.has(candidate)) found.insert(candidate);
    if (found.size()!=1) throw std::invalid_argument((found.empty()?"Missing":"Ambiguous")+std::string(" ACT reference: ")+parent+" -> "+literal);
    return *found.begin();
}
SourceRef ActWorldResources::staticSource(const std::string &path,const Bytes &bytes) const {
    SourceRef s; s.packageIdentity=staticIdentity_;s.memberPath=normalize(path);s.memberSha256=sha256(bytes);
    s.byteLength=bytes.size();s.textEncoding="binary";return s;
}
void ActWorldResources::sound(const std::string &id,std::set<std::string> &stack,std::vector<ActDependency> &out) const {
    if (stack.size()>=16 || !stack.insert(id).second) throw std::invalid_argument("Cyclic or deep audio random group: "+id);
    const auto declarations=audio_.find(id);
    if (declarations.empty()) throw std::invalid_argument("ACT SOUND has no audio.xml declaration: "+id);
    for (const auto *declaration:declarations) {
        ActDependency entry;entry.request={ActResourceKind::Sound,audioSource_,id,-1};entry.resolved=audioSource_;
        entry.resolved.byteOffset=declaration->offset;entry.resolved.byteLength=declaration->endOffset-declaration->offset;
        entry.found=entry.runtimeSupported=true;entry.diagnostic="audio.xml declaration consumed by Audio::play";out.push_back(entry);
        if (declaration->kind==AudioKind::Random) {
            bool selectable=false;
            for (const auto &item:declaration->items) if(item.weight>0) {
                selectable=true;sound(item.id,stack,out);
            }
            if (!selectable) throw std::invalid_argument("Empty audio random group: "+id);
        } else {
            if (declaration->kind!=AudioKind::Effect || declaration->file.empty()) throw std::invalid_argument("ACT SOUND is not an effect: "+id);
            const auto file=canonical(declaration->file);
            const auto bytes=assets_.has(file)?assets_.blob(file):assets_.staticBytes(std::filesystem::u8path(file));
            const bool wav=bytes.size()>=12 && std::memcmp(bytes.data(),"RIFF",4)==0 && std::memcmp(bytes.data()+8,"WAVE",4)==0;
            const bool ogg=bytes.size()>=4 && std::memcmp(bytes.data(),"OggS",4)==0;
            if (!wav && !ogg) throw std::invalid_argument("Unsupported ACT audio container: "+file);
            entry.resolved=staticSource(file,bytes);entry.request.literal=file;
            entry.diagnostic="source audio bytes; existing WAV/Vorbis decoder, device playback remains user verification";out.push_back(std::move(entry));
        }
    }
    stack.erase(id);
}
void ActWorldResources::animation(const std::string &name,std::set<std::string> &visited,
                                  std::vector<ActDependency> &out,size_t depth) const {
    if (!visited.insert(name).second) return;
    if(depth>12 || visited.size()>256) throw std::invalid_argument("ACT animation closure budget exceeded");
    const auto a=assets_.animation(name);
    if(a->frames.empty()) throw std::invalid_argument("Empty ACT animation: "+name);
    auto presentation=compileMonsterAnimation(pvf_,assets_,name,"act");
    if(!presentation->valid()) throw std::invalid_argument(presentation->error);
    // Native ANI sound/event scheduling has its own contract. This first host
    // executes ACT authored SOUND and never silently swallows ANI event nodes.
    if(a->globals.contains("16") || a->globals.contains("18") || a->globals.contains("23"))
        throw std::invalid_argument("ANI global event needs a registered ACT World consumer: "+name);
    std::set<std::pair<std::string,int>> images;
    for(const auto &f:a->frames) {
        for(const auto &box:f.boxes)if(box.type==15) {
            if(depth)throw std::invalid_argument("ALS attack box needs independent ACT collision host binding: "+name);
        }
        if(f.properties.contains("16") || f.properties.contains("18") || f.properties.contains("23"))
            throw std::invalid_argument("ANI event needs a registered ACT World consumer: "+name);
        if(!f.image.empty() && images.emplace(f.image,f.imageFrame).second) {
            const auto pixels=assets_.pixels(f.image,f.imageFrame);
            if(pixels.width<=0 || pixels.height<=0) throw std::invalid_argument("Invalid ACT IMG frame: "+f.image);
            ActDependency d;d.request={ActResourceKind::Animation,makeSourceRef(pvf_,name),f.image,f.imageFrame};
            d.resolved=staticSource(f.image,assets_.blob(f.image));d.found=d.runtimeSupported=true;
            d.diagnostic="IMG frame decoded by existing MonsterMotion renderer";out.push_back(std::move(d));
        }
    }
    if(!pvf_.has(name+".als")) return;
    const auto als=pvf_.script(name+".als");
    ActDependency layers;layers.request={ActResourceKind::Animation,makeSourceRef(pvf_,name),als.path,-1};
    layers.resolved=makeSourceRef(pvf_,als.path);layers.found=layers.runtimeSupported=true;
    layers.diagnostic="ALS composed by existing MonsterMotion renderer";out.push_back(layers);
    for(const auto &field:als.fields) {
        const auto tag=normalize(field.tag);
        if(tag=="[use animation]" && field.values.size()==2 && field.values[0].is_string() && field.values[1].is_string()) {
            const auto child=path(name,field.values[0].get<std::string>());
            ActDependency d;d.request={ActResourceKind::Animation,makeSourceRef(pvf_,als.path,field.offset),field.values[0].get<std::string>(),-1};
            d.resolved=makeSourceRef(pvf_,child);d.found=d.runtimeSupported=true;d.diagnostic="ALS child animation";out.push_back(d);
            animation(child,visited,out,depth+1);
        } else if((tag!="[add]" && tag!="[remove]") || field.values.size()!=3 || !field.values[0].is_number_integer() ||
                  !field.values[1].is_number_integer() || !field.values[2].is_string())
            throw std::invalid_argument("Unsupported mandatory ALS field: "+als.path+" "+field.tag);
    }
    if(!presentation->issues.empty()) throw std::invalid_argument("ALS composition diagnostic: "+presentation->issues.dump());
}
ActResolvedResource ActWorldResources::resolve(const ActResourceRequest &r) const {
    const auto key=std::to_string(int(r.kind))+":"+r.origin.memberPath+":"+r.literal+":"+std::to_string(r.index);
    const auto cached=cache_.find(key);if(cached!=cache_.end())return cached->second;
    ActResolvedResource result;
    try {
        if(r.kind==ActResourceKind::Sound) {
            std::set<std::string> stack;sound(r.literal,stack,result.transitive);
            result.source=audioSource_;result.found=result.runtimeSupported=true;result.transitiveClosureKnown=true;
            result.diagnostic="World sound event reaches the existing main-loop Audio::play consumer";
        } else {
            std::string member;
            if(r.kind==ActResourceKind::PassiveObject) {
                const auto i=objects_.find(r.index);if(i==objects_.end())throw std::invalid_argument("Unregistered passive-object index");member=i->second;
            } else member=path(r.origin.memberPath,r.literal);
            result.source=makeSourceRef(pvf_,member);result.found=true;
            if(r.kind==ActResourceKind::Animation) {
                const auto a=assets_.animation(member);
                for(const auto &f:a->frames)result.frameDurationsMs.push_back(f.duration);
                // One action visit is non-looping in inferred-act-world-host-v1.
                // A future explicit source/controller loop policy needs its own capability.
                result.animationLoops=false;
                std::set<std::string> visited;animation(member,visited,result.transitive,0);
                result.transitiveClosureKnown=result.runtimeSupported=true;
                result.diagnostic="ANI/ALS/IMG closure validated for existing MonsterMotion composition";
            } else if(r.kind==ActResourceKind::AttackInfo) {
                const auto attack=readActCollisionAttack(pvf_.script(member));
                result.runtimeSupported=attack.sourceReady;result.transitiveClosureKnown=true;
                if(!attack.sourceReady)throw std::invalid_argument("ACT ATK source damage/status inputs are unsupported: "+member);
                if(!attack.sound.empty()) {std::set<std::string> stack;sound(attack.sound,stack,result.transitive);}
                result.diagnostic=attack.reactionReady?"ATK consumed by private ACT damage/status/RNG/HP transaction":
                    "ATK damage source retained; authored reaction has a precise contact-time consumer gate";
            } else result.diagnostic="Resource retained, but ACT/PTL/object factory consumer is not registered";
        }
    } catch(const std::exception &e) {result.runtimeSupported=false;result.diagnostic=e.what();}
    cache_[key]=result;return result;
}

ActWorldActorView::ActWorldActorView(const World &w,const std::map<EntityHandle,ActEntityRelations> &r):world_(w),relations_(r){}
std::optional<ActEntityView> ActWorldActorView::entity(EntityHandle h) const {
    const auto *a=world_.resolveActor(h);if(!a)return std::nullopt;
    ActEntityView e;e.handle=h;e.position={a->x,a->y,a->z};e.direction=a->dir;e.hp=a->hp;e.mp=a->mp;
    e.alive=!a->dead && a->life==ActorLife::Alive;e.kind=h==world_.player.handle?ActEntityKind::Character:ActEntityKind::Monster;
    e.team=e.kind==ActEntityKind::Character?1:2;e.level=e.kind==ActEntityKind::Character?world_.characterLevel:a->sourceStats.value("level",1);
    const auto found=relations_.find(h);
    if(found!=relations_.end()) {const auto &r=found->second;e.target=r.target;e.lastAttacker=r.lastAttacker;
        e.lastAttackSuccess=r.lastAttackSuccess;e.lastAttackSuccesses=r.lastAttackSuccesses;e.summonMaster=r.summonMaster;}
    // Default monster aggro is the real player. Player target selection must be
    // provided by the controller; the host never invents a hidden nearest target.
    if(!e.target && e.kind==ActEntityKind::Monster)e.target=world_.player.handle;
    return e;
}
std::vector<EntityHandle> ActWorldActorView::entities() const {
    std::vector<EntityHandle> out;if(world_.resolveActor(world_.player.handle))out.push_back(world_.player.handle);
    for(const auto &a:world_.monsters)if(world_.resolveActor(a.handle))out.push_back(a.handle);
    std::sort(out.begin(),out.end());out.erase(std::unique(out.begin(),out.end()),out.end());return out;
}
Json ActSpeechBubble::json() const {return {{"instance_id",instanceId},{"speaker",speaker.json()},{"text",text},{"event_key",eventKey},{"expires_ms",expiresMs}};}

struct ActWorldHost::Batch {
    Actor player;
    std::vector<Actor> monsters;
    std::vector<Event> events;
    EntityRegistry entities;
    SimulationIdSources ids;
    StatusHost statuses;
    std::map<EntityHandle,MonsterDamageWindow> damageWindows;
    State host;
    RandomStreams random;
    Json lastDamage;
    int64_t playerGuardUntil = 0;
    bool playerInterrupted = false, controlInterrupted = false;
    std::optional<World::PreparedPlayerReaction> playerReaction;
    std::set<uint64_t> collisionChanged;
    explicit Batch(const ActWorldHost &h):player(h.world_.player),monsters(h.world_.monsters),events(h.world_.events),
        entities(h.world_.entities_),ids(h.world_.ids_),statuses(h.world_.statuses_),damageWindows(h.world_.monsterDamageWindows_),host(h.state_),
        random(h.world_.random_),lastDamage(h.world_.lastDamageTrace_),playerGuardUntil(h.world_.guardUntil_){
        if(h.publicationEpoch_==UINT64_MAX)throw std::overflow_error("ACT host publication epoch exhausted");
    }
    Actor *actor(EntityHandle h) {
        if(!entities.valid(h))return nullptr;
        if(player.handle==h && player.life!=ActorLife::Removed)return &player;
        for(auto &a:monsters)if(a.handle==h && a.life!=ActorLife::Removed)return &a;return nullptr;
    }
};
void ActWorldHost::bindCollision(Batch &b,uint64_t id,const MonsterActionRoute *route) {
    const auto &instance=b.host.instances.at(id);const auto &program=*instance.program;
    auto *owner=b.actor(instance.owner);if(!owner)throw std::invalid_argument("ACT collision owner is retired");
    ActCollisionState state;bool boxes=false,controls=false;
    if(program.motion) {
        const auto animation=resources_.resolve({ActResourceKind::Animation,program.source,program.motion->base,-1});
        if(!animation.runtimeSupported)throw std::invalid_argument(animation.diagnostic);
        state.baseAnimation=animation.source.memberPath;
        for(const auto &frame:assets_.animation(state.baseAnimation)->frames)for(const auto &box:frame.boxes)boxes|=box.type==15;
    }
    for(const auto &behavior:program.behaviors)for(const auto &instruction:behavior.instructions)
        controls|=std::holds_alternative<ActAttackRect>(instruction.payload)||std::holds_alternative<ActChangeAttackInfo>(instruction.payload);
    if(route) {
        if(owner->monsterPath.empty())throw std::invalid_argument("MOB paired ATK has no source monster binding");
        const auto verified=selectMonsterAction(pvf_,pvf_.script(owner->monsterPath),route->state,route->sourceActionIndex);
        if(!verified.ok||verified.engine!=MonsterActionEngine::Act||verified.json()!=route->json()||
           verified.resolvedPath!=program.source.memberPath)throw std::invalid_argument("ACT paired MOB route/source operand mismatch");
        state.route=verified.json();state.defaultAttack=verified.attackInfoResolvedPath;
    }
    if(!program.defaultAttackInfo.empty()) {
        const auto attack=resources_.resolve({ActResourceKind::AttackInfo,program.source,program.defaultAttackInfo,-1});
        if(!attack.runtimeSupported)throw std::invalid_argument(attack.diagnostic);
        state.defaultAttack=attack.source.memberPath;
    }
    if(!boxes&&!controls&&state.defaultAttack.empty())return;
    if(owner==&b.player)throw std::invalid_argument("ACT character collision ownership binding is not registered");
    if(!state.defaultAttack.empty()) {
        const auto attack=resources_.resolve({ActResourceKind::AttackInfo,makeSourceRef(pvf_,state.defaultAttack),state.defaultAttack,-1});
        if(!attack.runtimeSupported)throw std::invalid_argument(attack.diagnostic);
    }
    if(boxes&&state.defaultAttack.empty()&&!controls)throw std::invalid_argument("ACT type15 has no default or exact paired MOB active ATK");
    state.currentAttack=state.defaultAttack;state.attackInstance=b.ids.attacks.next();
    b.host.collisions.emplace(id,std::move(state));
}
void ActWorldHost::interruptNeutralPlayer(Batch &b) {
    if(b.playerInterrupted)return;
    if(!b.playerReaction)b.playerReaction=world_.prepareNeutralPlayerReaction(b.player);
    b.playerInterrupted=true;
    b.player.animationClock.reset();b.player.animationClockSource.clear();
    b.player.animationControllerDelays.reset();b.player.skillAnimationLayers.clear();
    b.player.sourceSkillCameraFeedback={};
    b.player.poseFrame=-1;b.player.animationPath.clear();b.player.vx=b.player.vy=0;
}
void ActWorldHost::collide(Batch &b,uint64_t id,uint64_t beforeUs,bool first) {
    auto found=b.host.collisions.find(id);if(found==b.host.collisions.end())return;
    const auto instance=b.host.instances.find(id);
    if(instance==b.host.instances.end()||instance->second.status!=ActInstanceStatus::Running)return;
    auto &collision=found->second;auto *owner=b.actor(instance->second.owner);
    if(!owner||owner->dead||owner->hitStopped||b.statuses.stunned(owner->handle,uint64_t(world_.nowMs()))||
       !collision.enabled||collision.baseAnimation.empty()||
       b.player.dead||b.player.life!=ActorLife::Alive||collision.acceptedTargets.count(b.player.handle))return;
    const auto frames=actCollisionFrames(*assets_.animation(collision.baseAnimation),beforeUs,instance->second.animationUs,first);
    const auto blocked=[&](const std::string &why,const Json &details=Json::object()) {
        if(collision.lastBlockedReason==why)return;
        collision.lastBlockedReason=why;
        b.host.diagnostics.push_back({{"code",why},{"source",collision.currentAttack.empty()?instance->second.program->source.json():makeSourceRef(pvf_,collision.currentAttack).json()},
            {"instance_id",id},{"target",b.player.handle.json()},{"details",details},{"whole_monster_complete",false}});
        if(b.host.diagnostics.size()>256)b.host.diagnostics.erase(b.host.diagnostics.begin());
    };
    if(collision.currentAttack.empty()){blocked("act_active_attack_info_is_empty");return;}
    if(frames.size()>1&&b.collisionChanged.count(id)) {
        blocked("act_multiple_crossed_frames_need_ordered_attack_control_binding");return;
    }
    const auto attack=readActCollisionAttack(pvf_.script(collision.currentAttack));
    if(!attack.enemy)return;
    const auto path=b.player.animationPath.empty()?world_.characterSource().motionByStem(b.player.animation):b.player.animationPath;
    const auto targetAnimation=assets_.animation(path);
    if(targetAnimation->frames.empty())return;
    const auto targetFrame=b.player.animationClock&&b.player.animationClockSource==path?b.player.animationClock->frame:
        targetAnimation->frameAt(std::max<int64_t>(0,world_.nowMs()-b.player.animStart),false);
    if(targetFrame>=targetAnimation->frames.size())throw std::invalid_argument("ACT target published ANI frame is outside its source");
    bool contact=false;const auto sourceAnimation=assets_.animation(collision.baseAnimation);
    for(const auto frame:frames)for(const auto &box:sourceAnimation->frames.at(frame).boxes)if(box.type==15)
        for(const auto &hurt:targetAnimation->frames.at(targetFrame).boxes)if(hurt.type==14)
            contact|=intersectCombatBoxes(combatBox(box,owner->x,owner->y,owner->z,owner->dir),
                combatBox(hurt,b.player.x,b.player.y,b.player.z,b.player.dir));
    if(!contact)return;
    if(world_.nowMs()<b.playerGuardUntil||world_.captured_>=0||
       (world_.active_>=0&&world_.skills.at(size_t(world_.active_)).stages.at(size_t(world_.stage_)).invincible))return;
    if(!attack.reactionReady){blocked("act_attack_reaction_consumer_unavailable",attack.diagnostics);return;}
    if(!world_.usesSourceGrowth()||!world_.combatAttributes_||!owner->combatAttributes) {
        blocked("act_source_damage_combatant_binding_missing");return;
    }
    const auto reactionGate=world_.neutralPlayerReactionGate(b.player);
    if(!reactionGate.empty()) {
        blocked(reactionGate,{{"experimental",bool(world_.experimentalRuntime_)},
            {"active_skill",world_.active_},{"animation",b.player.animation},{"recovery",b.player.recovery},{"z",b.player.z}});return;
    }
    // Validate the actual source reaction animation before any damage/status
    // candidate is published. The renderer consumes this same CHR motion.
    if(attack.reaction!="[none]") {
        const auto reaction=world_.characterSource().motionByStem("damage1");
        if(reaction.empty()||assets_.animation(reaction)->frames.empty()){blocked("act_player_damage_animation_missing");return;}
    }
    const auto policy=DamageResolutionPolicy::inferredPveDamageV1(world_.combatAttributes_->damageConstants);
    DamageRequest request;request.attacker=owner->handle;request.target=b.player.handle;
    request.attackInstance=collision.attackInstance;request.hitIndex=collision.hitIndex;
    request.attackerStats=makeDamageCombatant(*owner->combatAttributes,policy);
    request.targetStats=makeDamageCombatant(*world_.combatAttributes_);request.attack=attack.damage;
    auto defense=world_.preparePlayerDefense(std::move(request));
    // A preceding contact may already have retired the live action in this
    // private batch. Do not sample its not-yet-published armor a second time.
    if(b.playerInterrupted) {
        defense.receipt["sampled_super_armor_before_prior_contact"]=defense.superArmor;
        defense.superArmor=false;
        defense.receipt["prior_contact_interrupted_action"]=true;
        if(defense.receipt.contains("source_body_protection"))
            defense.receipt["source_body_protection"]["super_armor"]=false;
    }
    if(defense.immune){blocked("act_player_source_quick_standing_immunity",defense.receipt);return;}
    request=std::move(defense.request);
    // Prepare resources/controller/queue/effect/ledger before randomness;
    // discard on MISS or on any subsequent command/resource fault.
    if(!b.playerReaction)b.playerReaction=world_.prepareNeutralPlayerReaction(b.player);
    request.contactRange=DamageContactRange::Melee;
    request.contactRangeSource={{"policy","inferred-act-root-body-contact-range-v1"},
        {"classification","inferred_beta"},{"motion_source",makeSourceRef(pvf_,collision.baseAnimation).json()},
        {"basis","root ANI type15 body contact against current CHR type14"}};
    const auto resistance=evaluateCharacterStatusResistances(world_.combatAttributes_->pureChr,world_.characterSource(),
        world_.combatAttributes_->equipmentSources,world_.combatAttributes_->qualificationLevel);
    auto prepared=prepareDamageContact(request,policy,resistance,b.statuses,b.random,uint64_t(world_.nowMs()));
    b.lastDamage=prepared.resolution.snapshot();
    if(!prepared.ready()){blocked("act_source_damage_status_transaction_blocked",b.lastDamage);return;}
    const auto result=prepared.resolution;const auto now=world_.nowMs();
    const auto ownerHandle=owner->handle;const auto ownerId=owner->id;
    publishDamageContact(std::move(prepared),b.statuses,b.random);
    collision.lastBlockedReason.clear();
    collision.acceptedTargets.emplace(b.player.handle,Json{{"target",b.player.handle.json()},{"tick",world_.tick},
        {"hit_index",collision.hitIndex},{"attack_source",makeSourceRef(pvf_,collision.currentAttack).json()},
        {"damage",result.snapshot()},{"damage_handles_are_historical_evidence",true}});
    if(result.missed)b.events.push_back({world_.tick,"player_miss",collision.currentAttack,ownerId});
    else {
        if(!(world_.debugOverrides_.enabled&&world_.debugOverrides_.hpLock))b.player.hp=std::max(0,b.player.hp-*result.hpDamage);
        b.events.push_back({world_.tick,"player_hit","act_source",ownerId,b.player.id,*result.hpDamage});
        if(!attack.sound.empty())b.events.push_back({world_.tick,"sound",attack.sound,b.player.id});
        if(attack.reaction!="[none]"&&!defense.superArmor) {
            interruptNeutralPlayer(b);b.player.animation="damage1";
            b.player.animationPath=world_.characterSource().motion("[damage motion 1]");b.player.animStart=now;
            b.player.stunUntil=now+int64_t(std::llround(250*attack.delayRate));b.playerGuardUntil=now+180;
        }
        if(attack.pauseMs>0) {
            const auto ticks=int(std::ceil(attack.pauseMs*60/1000));
            b.player.hitStopTicks=std::max(b.player.hitStopTicks,ticks);b.player.hitStopped=true;
            owner->hitStopTicks=std::max(owner->hitStopTicks,ticks);owner->hitStopped=true;
        }
        if(b.statuses.controlRemaining(b.player.handle,uint64_t(now))) {
            interruptNeutralPlayer(b);b.controlInterrupted=true;
            // Armor or [none] can suppress the ordinary damage pose, but
            // control status still retires the action. Publish an exact
            // validated CHR pose, never a source action with its path removed.
            if(defense.superArmor||attack.reaction=="[none]") {
                b.player.animation="damage1";b.player.animStart=now;
                b.player.animationPath=world_.characterSource().motion("[damage motion 1]");
            }
            b.events.push_back({world_.tick,b.statuses.frozen(b.player.handle,uint64_t(now))?"status_freeze":"status_stun",
                "inferred-1031-active-status-v1",ownerId,b.player.id});
        }
        if(!b.player.hp) {
            interruptNeutralPlayer(b);b.statuses.clearTarget(b.player.handle,uint64_t(now),"death");
            if(world_.femaleGunnerWorld_) {
                b.playerReaction->femaleDeath=world_.femaleGunnerWorld_->prepareNeutralDeath();
                b.playerReaction->receipt["female_buff_death_cleanup"]="prepared private state; same noexcept publication";
            }
            b.player.dead=true;b.player.life=ActorLife::Dying;b.player.deathStart=b.player.lifeStart=now;
            b.player.deathPoseTime=std::max<int64_t>(0,now-b.player.animStart);
            b.player.deathAnchorX=b.player.x;b.player.deathAnchorY=b.player.y;b.player.deathHeight=b.player.z;
            b.player.deathLoop=false;b.player.independentDeath=false;b.player.deathFragments.clear();
            b.player.capturedBy=-1;b.player.hitStopTicks=0;b.player.hitStopped=false;b.player.animation="down";b.player.animStart=now;
            b.player.animationPath=world_.characterSource().motion("[down motion]");
            b.playerGuardUntil=0;b.events.push_back({world_.tick,"death_phase","dying",b.player.id});
        }
    }
    b.lastDamage["act_collision"]={{"policy","inferred-act-collision-v1"},{"classification","inferred_beta"},
        {"geometry","actual root ANI type15 against actual current CHR type14 in XYZ at fixed-tick endpoint"},
        {"motion_source",makeSourceRef(pvf_,collision.baseAnimation).json()},{"paired_route",collision.route},
        {"sampled_frames",frames},{"reaction_base_ms",250},{"guard_ms",180},{"hit_visual_diagnostics",attack.diagnostics}};
    b.lastDamage["player_defense"]=defense.receipt;
    b.lastDamage["player_reaction_outcome"]={{"super_armor",defense.superArmor},{"invincibility",false},
        {"interrupted",b.playerInterrupted},{"ordinary_reaction_suppressed",!result.missed&&defense.superArmor&&attack.reaction!="[none]"},
        {"control_status_interrupt",b.controlInterrupted},{"lethal",b.player.dead},
        {"policy","inferred-source-body-armor-preserves-action-not-hp-v1"}};
    if(b.playerInterrupted&&b.playerReaction)b.lastDamage["player_reaction"]=b.playerReaction->receipt;
    if(!result.missed) {
        auto &relations=b.host.relations[ownerHandle];relations.lastAttackSuccess=b.player.handle;relations.lastAttackSuccesses={b.player.handle};
    }
    ActWorldRestoreGraph graph{b.player,b.monsters,b.entities,b.ids.snapshot(),
        b.statuses.snapshot(uint64_t(now),1),uint64_t(world_.tick),world_.characterLevel,b.random.snapshot(),b.playerGuardUntil};
    RestoreGraphView view(graph,b.host.relations);
    ActEventContext event;event.eventId=b.ids.events.next();event.kind=ActEventKind::AttackSuccess;
    event.subject=ownerHandle;event.other=b.player.handle;event.stuck=result.missed;
    // Attack source/instance/cycle and frozen damage remain in the typed host
    // collision receipt and trace above. ACT only consumes subject/other/stuck;
    // do not hide redundant identities in opaque metadata that cannot remap.
    apply(b,id,prepareActEvent(b.host.instances.at(id),event,view));
}
Json ActWorldHost::collisionSnapshot(const State &state) const {
    Json out=Json::array();for(const auto &[id,collision]:state.collisions) {
        Json targets=Json::array();for(const auto &[handle,receipt]:collision.acceptedTargets)targets.push_back({{"target",handle.json()},{"receipt",receipt}});
        out.push_back({{"instance_id",id},{"attack_instance",collision.attackInstance},{"hit_index",collision.hitIndex},
            {"enabled",collision.enabled},{"base_animation",collision.baseAnimation},
            {"animation_source",collision.baseAnimation.empty()?Json():makeSourceRef(pvf_,collision.baseAnimation).json()},
            {"default_attack",collision.defaultAttack},{"current_attack",collision.currentAttack},
            {"default_source",collision.defaultAttack.empty()?Json():makeSourceRef(pvf_,collision.defaultAttack).json()},
            {"current_source",collision.currentAttack.empty()?Json():makeSourceRef(pvf_,collision.currentAttack).json()},
            {"route",collision.route},{"accepted_targets",targets},{"last_blocked_reason",collision.lastBlockedReason}});
    }
    return out;
}
void ActWorldHost::restoreCollisions(State &candidate,const Json &value,const ActWorldRestoreGraph &graph) const {
    std::set<uint64_t> required;
    for(const auto &[id,instance]:candidate.instances)if(instance.status==ActInstanceStatus::Running) {
        bool needs=!instance.program->defaultAttackInfo.empty();
        if(instance.program->motion) {
            const auto resource=resources_.resolve({ActResourceKind::Animation,instance.program->source,instance.program->motion->base,-1});
            for(const auto &frame:assets_.animation(resource.source.memberPath)->frames)for(const auto &box:frame.boxes)needs|=box.type==15;
        }
        for(const auto &behavior:instance.program->behaviors)for(const auto &instruction:behavior.instructions)
            needs|=std::holds_alternative<ActAttackRect>(instruction.payload)||std::holds_alternative<ActChangeAttackInfo>(instruction.payload);
        if(needs)required.insert(id);
    }
    if(!value.contains("collisions")) {
        if(!required.empty())throw std::invalid_argument("ACT collision checkpoint deleted required source attack state");
        return;
    }
    if(value.at("collision_policy")!="inferred-act-collision-v1"||!value.at("collisions").is_array()||value.at("collisions").size()>1024)
        throw std::invalid_argument("ACT collision checkpoint policy/collection mismatch");
    if(!value.at("collisions").empty()&&(graph.combatRandom.is_null()||value.at("collision_random_receipt")!=graph.combatRandom||
       signedValue(value.at("collision_player_guard_until"))!=graph.playerGuardUntil))
        throw std::invalid_argument("ACT collision continuation requires exact same-generation combat RNG and player protection");
    SimulationIdSources ids;ids.restore(graph.worldIds);std::set<uint64_t> attacks;
    const std::map<EntityHandle,ActEntityRelations> none;RestoreGraphView view(graph,none);
    for(const auto &row:value.at("collisions")) {
        const auto id=number(row.at("instance_id"));const auto instance=candidate.instances.find(id);
        if(instance==candidate.instances.end()||instance->second.status!=ActInstanceStatus::Running)throw std::invalid_argument("ACT collision has no running owner");
        ActCollisionState collision;collision.attackInstance=number(row.at("attack_instance"));const auto index=number(row.at("hit_index"));
        if(!collision.attackInstance||collision.attackInstance>=ids.attacks.nextValue()||index>UINT32_MAX||
           !attacks.insert(collision.attackInstance).second||!row.at("enabled").is_boolean())throw std::invalid_argument("ACT collision ID/reset watermark conflict");
        collision.hitIndex=uint32_t(index);collision.enabled=row.at("enabled").get<bool>();
        collision.baseAnimation=row.at("base_animation").get<std::string>();
        collision.defaultAttack=row.at("default_attack").get<std::string>();collision.currentAttack=row.at("current_attack").get<std::string>();
        collision.route=row.at("route");collision.lastBlockedReason=row.at("last_blocked_reason").get<std::string>();
        if(collision.lastBlockedReason.size()>4096)throw std::invalid_argument("ACT collision diagnostic budget exceeded");
        for(const auto &[path,source]:std::vector<std::pair<std::string,Json>>{{collision.baseAnimation,row.at("animation_source")},
            {collision.defaultAttack,row.at("default_source")},{collision.currentAttack,row.at("current_source")}})
            if(path.empty()?!source.is_null():makeSourceRef(pvf_,path).json()!=source)throw std::invalid_argument("ACT collision source changed");
        const auto *owner=view.actor(instance->second.owner);if(!owner||owner==&graph.player)throw std::invalid_argument("ACT collision owner kind is unsupported");
        std::string expectedDefault;
        if(!collision.route.empty()) {
            const auto fresh=selectMonsterAction(pvf_,pvf_.script(owner->monsterPath),collision.route.at("state").get<std::string>(),
                collision.route.at("source_action_index").get<int>());
            if(!fresh.ok||fresh.json()!=collision.route||fresh.resolvedPath!=instance->second.program->source.memberPath)
                throw std::invalid_argument("ACT saved paired source action/ATK binding changed");
            expectedDefault=fresh.attackInfoResolvedPath;
        }
        if(!instance->second.program->defaultAttackInfo.empty()) {
            const auto source=resources_.resolve({ActResourceKind::AttackInfo,instance->second.program->source,instance->second.program->defaultAttackInfo,-1});
            if(!source.runtimeSupported)throw std::invalid_argument(source.diagnostic);
            expectedDefault=source.source.memberPath;
        }
        if(expectedDefault!=collision.defaultAttack)throw std::invalid_argument("ACT saved default ATK is not its source ACT/MOB binding");
        std::set<std::string> permitted{expectedDefault};
        for(const auto &behavior:instance->second.program->behaviors)for(const auto &instruction:behavior.instructions)
            if(const auto *change=std::get_if<ActChangeAttackInfo>(&instruction.payload))if(!change->useDefault) {
                const auto source=resources_.resolve({ActResourceKind::AttackInfo,instruction.source,change->path,-1});
                if(!source.runtimeSupported)throw std::invalid_argument(source.diagnostic);
                permitted.insert(source.source.memberPath);
            }
        if(!permitted.count(collision.currentAttack))throw std::invalid_argument("ACT saved current ATK is absent from its source CHANGE ATTACKINFO program");
        if(instance->second.program->motion) {
            const auto resource=resources_.resolve({ActResourceKind::Animation,instance->second.program->source,instance->second.program->motion->base,-1});
            if(resource.source.memberPath!=collision.baseAnimation)throw std::invalid_argument("ACT saved collision base animation differs");
        }else if(!collision.baseAnimation.empty())throw std::invalid_argument("ACT collision invents a source motion");
        if(!row.at("accepted_targets").is_array()||row.at("accepted_targets").size()>1024)throw std::invalid_argument("ACT accepted contact budget exceeded");
        for(const auto &target:row.at("accepted_targets")) {
            const auto handle=EntityHandle::fromJson(target.at("target"));const auto &receipt=target.at("receipt");
            if(!handle||handle!=graph.player.handle||receipt.at("target")!=handle.json()||number(receipt.at("tick"))>graph.tick||number(receipt.at("hit_index"))!=collision.hitIndex||
               !collision.acceptedTargets.emplace(handle,receipt).second)throw std::invalid_argument("ACT collision contact identity mismatch");
            const auto source=receipt.at("attack_source");
            if(!permitted.count(source.at("member_path").get<std::string>())||makeSourceRef(pvf_,source.at("member_path").get<std::string>()).json()!=source)
                throw std::invalid_argument("ACT collision frozen attack source changed");
            if(number(receipt.at("damage").at("attack_instance"))!=collision.attackInstance||
               number(receipt.at("damage").at("hit_index"))!=collision.hitIndex||!receipt.at("damage").at("usable").get<bool>())
                throw std::invalid_argument("ACT frozen damage result identity differs from accepted contact");
        }
        if(!candidate.collisions.emplace(id,std::move(collision)).second)throw std::invalid_argument("Duplicate ACT collision owner");
    }
    for(const auto id:required)if(!candidate.collisions.count(id))throw std::invalid_argument("ACT collision checkpoint omitted a source attack instance");
}

ActWorldHost::ActWorldHost(World &w,Pvf &p,Assets &a,std::string staticIdentity,ActWorldHostOptions options)
    :world_(w),pvf_(p),assets_(a),resources_(p,a,std::move(staticIdentity)),options_(options) {
    if(!options.speechDurationMs || options.speechDurationMs>60000)throw std::invalid_argument("Invalid ACT speech lifetime policy");
    if(w.tick<0)throw std::invalid_argument("Negative World tick");state_.lastTick=uint64_t(w.tick);
}
bool ActWorldHost::hasCommandConsumer(const std::string &kind) const {
    return kind=="set_speed" || kind=="teleport" || kind=="set_direction" || kind=="destroy" || kind=="sound" ||
           kind=="cleanup_owned" || kind=="set_damage_check" || kind=="attack_rect" || kind=="change_attack_info" || (kind=="speech" && options_.enableSpeechPresentation);
}
ActCompileResult ActWorldHost::compile(const std::string &path,ActSemanticPolicy policy) const {
    auto result=compileActProgram(pvf_.script(path),context(pvf_,resources_,std::move(policy),[this](const std::string &s){return hasCommandConsumer(s);}));
    if(result.ok && result.program->motion)for(const auto &track:result.program->motion->tracks) {
        const auto resource=resources_.resolve({ActResourceKind::Animation,result.program->source,track.path,-1});
        if(!resource.found)continue;
        bool attack=false;for(const auto &frame:assets_.animation(resource.source.memberPath)->frames)for(const auto &box:frame.boxes)attack|=box.type==15;
        if(attack) {
            auto program=std::make_shared<ActProgram>(*result.program);program->runtimeReady=false;
            program->diagnostics.push_back({"act_sub_animation_collision_binding_missing","SUB ANI type15 needs its own attack identity/clock binding",track.source,true});
            result.program=program;result.ok=false;
        }
    }
    return result;
}
ActWorldHostResult ActWorldHost::failure(const std::exception &e) const {return {false,e.what(),Json::array({{{"code","act_world_batch_rejected"},{"message",e.what()}}})};}
void ActWorldHost::commit(Batch &b) noexcept {
    static_assert(std::is_nothrow_swappable<Actor>::value,"Actor publication must not throw");
    static_assert(std::is_nothrow_swappable<State>::value,"ACT state publication must not throw");
    static_assert(std::is_nothrow_swappable<EntityRegistry>::value,"Registry publication must not throw");
    static_assert(std::is_nothrow_swappable<StatusHost>::value,"Status publication must not throw");
    using std::swap;swap(world_.player,b.player);world_.monsters.swap(b.monsters);world_.events.swap(b.events);
    swap(world_.entities_,b.entities);swap(world_.ids_,b.ids);swap(world_.statuses_,b.statuses);world_.monsterDamageWindows_.swap(b.damageWindows);swap(state_,b.host);
    static_assert(std::is_nothrow_swappable<RandomStreams>::value,"ACT combat random publication must not throw");
    swap(world_.random_,b.random);world_.lastDamageTrace_.swap(b.lastDamage);world_.guardUntil_=b.playerGuardUntil;
    if(b.playerInterrupted) {
        assert(b.playerReaction);world_.publishNeutralPlayerReaction(*b.playerReaction);
    }
    assert(publicationEpoch_!=UINT64_MAX);++publicationEpoch_;
}
void ActWorldHost::cleanup(Batch &b,uint64_t id) {
    for(auto i=b.host.velocities.begin();i!=b.host.velocities.end();)if(i->second.instanceId==id)i=b.host.velocities.erase(i);else ++i;
    auto &speech=b.host.speech;speech.erase(std::remove_if(speech.begin(),speech.end(),[&](const auto &s){return s.instanceId==id;}),speech.end());
    const auto instance=b.host.instances.find(id);
    const auto prior=b.host.presentation.find(id);
    if(instance!=b.host.instances.end() && prior!=b.host.presentation.end())if(auto *actor=b.actor(instance->second.owner)) {
        if(actor->animation=="act" && actor->animationPath==instance->second.program->source.memberPath) {
            actor->animation=prior->second.animation;actor->animationPath=prior->second.animationPath;
            actor->animStart=prior->second.animStart;actor->poseFrame=prior->second.poseFrame;
        }
    }
    b.host.presentation.erase(id);b.host.collisions.erase(id);
}
void ActWorldHost::apply(Batch &b,uint64_t id,const ActPreparedStep &step) {
    const auto found=b.host.instances.find(id);
    if(found==b.host.instances.end() || found->second.revision!=step.expectedRevision || step.expectedInstanceId!=id || (!step.ok && !step.faulted))
        throw std::invalid_argument("ACT World prepared revision mismatch");
    Batch candidate=b;SourceRef location=found->second.program->source;
    try {
        applyCommands(candidate,id,step,&location);
        (void)eventReceiptBytes(candidate.host);
        static_assert(std::is_nothrow_move_assignable<Batch>::value,"ACT batch publication must not throw");
        b=std::move(candidate);
    }catch(const std::exception &e) {
        // Failed World consumers cannot leave an instance one tick behind and
        // permanently poison subsequent ticks. Discard every partial effect,
        // fault the pre-batch instance and publish only its ownership cleanup.
        auto fault=prepareActCancel(found->second,"world_consumer_fault");
        if(!fault.ok)throw;
        fault.candidate.status=ActInstanceStatus::Faulted;fault.faulted=true;
        fault.diagnostics.push_back({"act_world_consumer_fault",e.what(),location,true});
        applyCommands(b,id,fault,nullptr);
    }
}
void ActWorldHost::applyCommands(Batch &b,uint64_t id,const ActPreparedStep &step,SourceRef *failureLocation) {
    auto it=b.host.instances.find(id);
    if(it==b.host.instances.end() || it->second.revision!=step.expectedRevision || step.expectedInstanceId!=id || (!step.ok && !step.faulted))
        throw std::invalid_argument("ACT World prepared revision mismatch");
    for(const auto &command:step.commands) {
        if(failureLocation)*failureLocation=command.source;
        if(command.instanceId!=id || command.owner!=it->second.owner || command.actionId!=it->second.actionId)
            throw std::invalid_argument("ACT command ownership mismatch");
        if(std::holds_alternative<ActCleanup>(command.payload)){cleanup(b,id);continue;}
        auto *owner=b.actor(command.owner),*recipient=b.actor(command.recipient);
        if(!owner || !recipient)continue; // Retired generation is never retargeted.
        if(!command.ownerSnapshot || !command.recipientSnapshot)throw std::invalid_argument("ACT command has no immutable coordinate receipt");
        const auto &os=*command.ownerSnapshot,&rs=*command.recipientSnapshot;
        if(const auto *speed=std::get_if<ActSetSpeed>(&command.payload)) {
            auto found=b.host.velocities.find(command.recipient);
            if(found!=b.host.velocities.end() && found->second.instanceId!=id)throw std::invalid_argument("ACT velocity ownership conflict");
            auto &v=b.host.velocities[command.recipient];v.instanceId=id;
            const int dir=speed->direction==ActDirectionBasis::Ignore?1:speed->direction==ActDirectionBasis::Owner?os.direction:rs.direction;
            auto axis=[](double value){if(!std::isfinite(value) || std::abs(value)>std::numeric_limits<float>::max())throw std::invalid_argument("Invalid ACT speed");return double(float(value));};
            if(speed->x)v.value.x=axis(*speed->x*dir);if(speed->y)v.value.y=axis(*speed->y);if(speed->z)v.value.z=axis(*speed->z);
        } else if(const auto *teleport=std::get_if<ActTeleport>(&command.payload)) {
            Actor *moved=teleport->moveOwner?owner:recipient;const auto &p=teleport->position;
            const auto &base=p.useOwnerBase?os:rs;const int direction=p.useOwnerDirection?os.direction:rs.direction;
            const double x=(p.useMapPosition?0:base.position.x)+p.value.x*(p.useMapPosition?1:direction);
            const double y=(p.useMapPosition?0:base.position.y)+p.value.y,z=(p.useMapPosition?0:base.position.z)+p.value.z;
            if(!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z) || z<0)throw std::invalid_argument("Invalid ACT teleport destination");
            if(!world_.canWalk(x,y))throw std::invalid_argument("ACT teleport destination is outside current World collision");
            moved->x=moved->px=x;moved->y=moved->py=y;moved->z=moved->pz=z;
        } else if(const auto *direction=std::get_if<ActSetDirection>(&command.payload)) {
            int value=recipient->dir;
            switch(direction->value) {
            case ActDirectionKind::Left:value=-1;break;case ActDirectionKind::Right:value=1;break;
            case ActDirectionKind::Reverse:value=-rs.direction;break;
            case ActDirectionKind::Owner:value=os.direction;break;case ActDirectionKind::OppositeOwner:value=-os.direction;break;
            case ActDirectionKind::CurrentOwner:value=owner->dir;break;
            case ActDirectionKind::ToTarget:{
                const auto *actor=static_cast<const World &>(world_).resolveActor(rs.target);
                if(actor && actor->x!=rs.position.x)value=actor->x<rs.position.x?-1:1;
                break;}
            case ActDirectionKind::Random:throw std::invalid_argument("Unresolved ACT random direction");
            }
            recipient->dir=value<0?-1:1;
        } else if(const auto *check=std::get_if<ActSetDamageCheck>(&command.payload)) {
            if(recipient==&b.player || recipient->monsterPath.empty() || recipient->dead)
                throw std::invalid_argument("ACT SET DAMAGE CHECK requires live source monster recipient");
            auto window=b.damageWindows.find(recipient->handle);
            if(window==b.damageWindows.end()) {
                if(b.damageWindows.size()>=1024)throw std::overflow_error("ACT damage-window owner budget exceeded");
                window=b.damageWindows.emplace(recipient->handle,
                    initialMonsterDamageWindow(pvf_,pvf_.script(recipient->monsterPath),uint64_t(world_.nowMs()))).first;
            }
            configureMonsterDamageWindow(window->second,check->enabled,check->intervalMs,uint64_t(world_.nowMs()),command.source);
            b.events.push_back({world_.tick,"act_damage_check",command.source.memberPath,recipient->id,int(check->intervalMs),int(check->enabled)});
        } else if(const auto *destroy=std::get_if<ActDestroy>(&command.payload)) {
            if(recipient==&b.player)throw std::invalid_argument("ACT DESTROY character controller cleanup is not registered");
            const auto handle=recipient->handle;recipient->dead=true;recipient->life=ActorLife::Removed;recipient->capturedBy=-1;
            recipient->vx=recipient->vy=recipient->vz=0;recipient->hitStopTicks=0;recipient->hitStopped=false;
            // The target's active state and contact ledger retire in the same
            // private batch as its actor and generation. Other targets may
            // retain this removed actor as their historical status attacker.
            b.statuses.retireTarget(handle,uint64_t(world_.nowMs()),"act_destroy");
            b.entities.retire(handle);b.host.velocities.erase(handle);b.damageWindows.erase(handle);
            b.events.push_back({world_.tick,"act_destroy",destroy->force?"force":"normal",recipient->id});
            // DESTROY is removal, not an accepted lethal attack; no killed event/reward.
        } else if(const auto *sound=std::get_if<ActSound>(&command.payload))
            b.events.push_back({world_.tick,"sound",sound->tag,recipient->id});
        else if(const auto *speech=std::get_if<ActSpeech>(&command.payload)) {
            if(!options_.enableSpeechPresentation)throw std::invalid_argument("ACT speech presentation is not attached");
            const auto now=uint64_t(world_.nowMs());
            if(now>std::numeric_limits<uint64_t>::max()-options_.speechDurationMs)throw std::overflow_error("ACT speech time overflow");
            b.host.speech.push_back({id,now+options_.speechDurationMs,command.recipient,speech->text,command.stableKey()});
        } else if(const auto *rect=std::get_if<ActAttackRect>(&command.payload)) {
            if(command.recipient!=command.owner)throw std::invalid_argument("ACT foreign ATTACKRECT binding is not registered");
            auto collision=b.host.collisions.find(id);if(collision==b.host.collisions.end())throw std::invalid_argument("ACT attack control has no source collision binding");
            b.collisionChanged.insert(id);
            if(rect->mode==ActAttackRectMode::Reset) {
                if(collision->second.hitIndex==UINT32_MAX)throw std::overflow_error("ACT attack reset watermark exhausted");
                ++collision->second.hitIndex;collision->second.acceptedTargets.clear();
            } else collision->second.enabled=rect->mode==ActAttackRectMode::On;
        } else if(const auto *change=std::get_if<ActChangeAttackInfo>(&command.payload)) {
            if(command.recipient!=command.owner)throw std::invalid_argument("ACT foreign CHANGE ATTACKINFO binding is not registered");
            auto collision=b.host.collisions.find(id);if(collision==b.host.collisions.end())throw std::invalid_argument("ACT attack change has no source collision binding");
            std::string path=collision->second.defaultAttack;
            if(!change->useDefault) {
                const auto resource=resources_.resolve({ActResourceKind::AttackInfo,command.source,change->path,-1});
                if(!resource.runtimeSupported)throw std::invalid_argument(resource.diagnostic);path=resource.source.memberPath;
            }
            collision->second.currentAttack=std::move(path);b.collisionChanged.insert(id);
        } else throw std::invalid_argument("ACT emitted a command without a real World consumer");
    }
    for(const auto &d:step.diagnostics)b.host.diagnostics.push_back(d.json());
    if(b.host.diagnostics.size()>256)b.host.diagnostics.erase(b.host.diagnostics.begin(),b.host.diagnostics.begin()+std::ptrdiff_t(b.host.diagnostics.size()-256));
    if(!publishActStep(it->second,step))throw std::invalid_argument("ACT candidate publication rejected");
}
ActWorldHostResult ActWorldHost::bind(std::shared_ptr<const ActProgram> program,const ActBindRequest &r,ActEntityRelations relations,bool replaceOwner,const MonsterActionRoute *attackRoute) {
    try {
        if(!program || !program->executable() || !pvf_.has(program->source.memberPath) ||
           sha256(pvf_.read(program->source.memberPath))!=program->source.memberSha256)
            throw std::invalid_argument("ACT bind requires unchanged current PVF source");
        const auto verified=compile(program->source.memberPath,program->policy);
        if(!verified.ok || !sameSource(program->source,verified.program->source))throw std::invalid_argument("ACT bind failed production-consumer preflight");
        if(r.tick!=uint64_t(world_.tick) || r.tick!=state_.lastTick || r.simulationMs!=uint64_t(world_.nowMs()))throw std::invalid_argument("ACT bind World clock mismatch");
        if(r.instanceId<=state_.instanceWatermark || state_.instances.count(r.instanceId) || (ownsActor(r.owner) && !replaceOwner))throw std::invalid_argument("ACT owner/instance is already bound or instance ID was reused");
        for(const auto &i:state_.instances)if(i.second.actionId==r.actionId)throw std::invalid_argument("ACT action ID was reused");
        ActWorldActorView view(world_,state_.relations);auto bound=bindActProgram(verified.program,r,view);
        if(!bound.ok)throw std::invalid_argument(bound.error);
        Batch b(*this);
        if(replaceOwner) {
            std::vector<uint64_t> old;
            for(const auto &entry:b.host.instances)
                if(entry.second.owner==r.owner && entry.second.status==ActInstanceStatus::Running) old.push_back(entry.first);
            for(auto id:old) apply(b,id,prepareActCancel(b.host.instances.at(id),"source_action_replaced"));
        }
        if(b.host.instances.size()>=1024) {
            for(auto i=b.host.instances.begin();i!=b.host.instances.end();) {
                if(i->second.status!=ActInstanceStatus::Running)i=b.host.instances.erase(i);else ++i;
            }
        }
        if(b.host.instances.size()>=1024)throw std::invalid_argument("ACT active-instance budget exceeded");
        b.host.instances.emplace(r.instanceId,std::move(bound.state));b.host.instanceWatermark=r.instanceId;b.host.relations[r.owner]=std::move(relations);
        b.ids.actions.reserveThrough(r.actionId);
        auto *owner=b.actor(r.owner);if(!owner)throw std::invalid_argument("ACT owner retired during bind");
        if(verified.program->motion) {
            if(owner==&b.player)throw std::invalid_argument("ACT character-body presentation adapter is not registered");
            const auto motion=compileMonsterAnimation(pvf_,assets_,program->source.memberPath,"act");
            if(!motion->valid())throw std::invalid_argument(motion->error);
            b.host.presentation.emplace(r.instanceId,Presentation{owner->animation,owner->animationPath,owner->animStart,owner->poseFrame});
            owner->animation="act";owner->animationPath=program->source.memberPath;owner->animStart=world_.nowMs();owner->poseFrame=-1;
        }
        bindCollision(b,r.instanceId,attackRoute);
        ActWorldActorView bindView(world_,b.host.relations);
        ActEventContext event;event.eventId=b.ids.events.next();event.kind=ActEventKind::SetAction;event.subject=r.owner;
        apply(b,r.instanceId,prepareActEvent(b.host.instances.at(r.instanceId),event,bindView));
        if(b.host.instances.at(r.instanceId).status==ActInstanceStatus::Faulted)throw std::invalid_argument("ACT SetAction World consumer failed; bind was not published");
        commit(b);return {true,{},{}};
    }catch(const std::exception &e){return failure(e);}
}
ActWorldHostResult ActWorldHost::advance(const SimulationStep &step,const std::map<uint64_t,uint64_t> &deltas) {
    try {
        if(state_.lastTick==std::numeric_limits<uint64_t>::max() || step.tick!=state_.lastTick+1 || step.tick!=uint64_t(world_.tick) ||
           step.milliseconds!=uint64_t(world_.nowMs()) || step.deltaMilliseconds!=step.milliseconds-FixedStepClock::millisecondsAtTick(step.tick-1))
            throw std::invalid_argument("ACT World host requires one consecutive 60 Hz World tick");
        // An unused host has no actor/status/event changes to transact. Keep
        // its exact clock and publication epoch without copying every actor's
        // immutable source/stat traces on every world tick. Once any instance
        // or owned state exists the normal atomic Batch remains authoritative.
        if (state_.instances.empty() && state_.velocities.empty() && state_.relations.empty() &&
            state_.presentation.empty() && state_.speech.empty() && state_.collisions.empty()) {
            if (!deltas.empty()) throw std::invalid_argument("Unexpected external ACT animation delta");
            if (publicationEpoch_==UINT64_MAX) throw std::overflow_error("ACT host publication epoch exhausted");
            state_.lastTick=step.tick; ++publicationEpoch_;
            return {true,{},{}};
        }
        Batch b(*this);ActWorldActorView view(world_,state_.relations);std::vector<uint64_t> instanceIds;
        for(const auto &entry:b.host.instances)instanceIds.push_back(entry.first);
        for(const auto &delta:deltas) {
            const auto found=b.host.instances.find(delta.first);
            if(found==b.host.instances.end() || found->second.status!=ActInstanceStatus::Running || found->second.clockMode!=ActClockMode::ExternalAnimationDelta)
                throw std::invalid_argument("Unexpected external ACT animation delta");
        }
        std::map<uint64_t,std::pair<uint64_t,bool>> collisionIntervals;
        for(const auto id:instanceIds) {
            const auto &instance=b.host.instances.at(id);if(instance.status!=ActInstanceStatus::Running)continue;
            collisionIntervals[id]={instance.animationUs,instance.firstAdvance};
            if(!b.actor(instance.owner) || !view.entity(instance.owner)->alive) {apply(b,id,prepareActCancel(instance,"owner_lifecycle_exit"));continue;}
            const auto *owner=b.actor(instance.owner);
            if(owner->capturedBy>=0 || owner->recovery!=0 || world_.nowMs()<owner->stunUntil) {
                apply(b,id,prepareActCancel(instance,"owner_reaction_interrupt"));continue;
            }
            if(instance.program->motion && (owner->animation!="act" || owner->animationPath!=instance.program->source.memberPath)) {
                apply(b,id,prepareActCancel(instance,"actor_action_replaced"));continue;
            }
            ActAdvanceInput input;input.step=step;const auto delta=deltas.find(id);if(delta!=deltas.end())input.animationDeltaUs=delta->second;
            apply(b,id,prepareActAdvance(instance,input,view));
            const auto &advanced=b.host.instances.at(id);
            if(advanced.status==ActInstanceStatus::Running && advanced.program->motion)if(auto *actor=b.actor(advanced.owner))
                actor->animStart=world_.nowMs()-int64_t(advanced.animationUs/1000);
        }
        // One native arithmetic integration per source tick. Event crossings
        // never subdivide movement; dt remains the recovered 16/17ms contract.
        for(auto i=b.host.velocities.begin();i!=b.host.velocities.end();) {
            auto *a=b.actor(i->first);if(!a || a->dead){i=b.host.velocities.erase(i);continue;}
            const auto animationDelta=deltas.find(i->second.instanceId);
            const bool paused=animationDelta!=deltas.end() && animationDelta->second==0;
            if(!paused && !a->hitStopped && !b.statuses.stunned(a->handle,step.milliseconds)) {
                auto displacement=[&](double v){AxisMotion axis{float(v),0,-1};return double(advanceAxisMotion(axis,int32_t(step.deltaMilliseconds)));};
                const auto &v=i->second.value;const double x=a->x+displacement(v.x),y=a->y+displacement(v.y),z=std::max(0.0,a->z+displacement(v.z));
                if(world_.canWalk(x,a->y))a->x=x;if(world_.canWalk(a->x,y))a->y=y;a->z=z;
            }
            ++i;
        }
        for(const auto &[id,interval]:collisionIntervals) {
            const auto found=b.host.instances.find(id);if(found==b.host.instances.end()||found->second.status!=ActInstanceStatus::Running)continue;
            const auto delta=deltas.find(id);if(delta!=deltas.end()&&delta->second==0)continue;
            Batch contact=b;
            try {
                collide(contact,id,interval.first,interval.second);
                if(contact.host.instances.at(id).status==ActInstanceStatus::Faulted)
                    throw std::invalid_argument("ACT attack-success consumer fault; contact discarded");
                (void)eventReceiptBytes(contact.host);b=std::move(contact);
            }catch(const std::exception &error) {
                auto fault=prepareActCancel(b.host.instances.at(id),"collision_consumer_fault");
                if(!fault.ok)throw;
                fault.candidate.status=ActInstanceStatus::Faulted;fault.faulted=true;
                const auto collision=b.host.collisions.find(id);
                auto source=b.host.instances.at(id).program->source;
                if(collision!=b.host.collisions.end()&&!collision->second.currentAttack.empty()) {
                    if(pvf_.has(collision->second.currentAttack))source=makeSourceRef(pvf_,collision->second.currentAttack);
                    else source.literalPath=collision->second.currentAttack;
                }
                fault.diagnostics.push_back({"act_collision_consumer_fault",error.what(),source,true});
                applyCommands(b,id,fault,nullptr);
            }
        }
        for(const auto id:instanceIds) {
            const auto &instance=b.host.instances.at(id);if(instance.status!=ActInstanceStatus::Running)continue;
            if(!b.actor(instance.owner)){apply(b,id,prepareActCancel(instance,"destroyed_owner"));continue;}
            if(instance.program->motion && !instance.program->motion->loop) {
                uint64_t duration=0;for(auto ms:instance.program->motion->frameDurationsMs)duration+=uint64_t(ms);
                if(instance.animationUs/1000>=duration)apply(b,id,prepareActCancel(instance,"source_motion_complete"));
            }
        }
        auto &speech=b.host.speech;speech.erase(std::remove_if(speech.begin(),speech.end(),[&](const auto &s){return s.expiresMs<=step.milliseconds || !b.actor(s.speaker);}),speech.end());
        for(auto i=b.host.relations.begin();i!=b.host.relations.end();)if(!b.actor(i->first))i=b.host.relations.erase(i);else ++i;
        b.host.lastTick=step.tick;commit(b);return {true,{},{}};
    }catch(const std::exception &e){return failure(e);}
}
ActWorldHostResult ActWorldHost::dispatch(uint64_t id,const ActEventContext &event) {
    try {
        Batch b(*this);const auto found=b.host.instances.find(id);if(found==b.host.instances.end())throw std::invalid_argument("Unknown ACT instance");
        if(event.subject!=found->second.owner || uint64_t(world_.tick)!=state_.lastTick)throw std::invalid_argument("ACT World event subject/clock mismatch");
        auto &relations=b.host.relations[event.subject];
        if(event.kind==ActEventKind::Damage)relations.lastAttacker=event.other;
        else if(event.kind==ActEventKind::AttackSuccess){relations.lastAttackSuccess=event.other;relations.lastAttackSuccesses={event.other};}
        // Event-local attacker/target links are visible to this accepted event;
        // replay returns without publishing its historical links over newer ones.
        ActWorldActorView view(world_,b.host.relations);const auto prepared=prepareActEvent(found->second,event,view);
        if(prepared.replayed)return {true,{},{}};
        b.ids.events.reserveThrough(event.eventId);
        apply(b,id,prepared);commit(b);return {true,{},{}};
    }catch(const std::exception &e){return failure(e);}
}
ActWorldHostResult ActWorldHost::cancel(uint64_t id,const std::string &reason) {
    try {Batch b(*this);auto found=b.host.instances.find(id);if(found==b.host.instances.end())throw std::invalid_argument("Unknown ACT cancellation instance");
        if(found->second.status!=ActInstanceStatus::Running)return {true,{},{}};
        apply(b,id,prepareActCancel(found->second,reason));commit(b);return {true,{},{}};
    }catch(const std::exception &e){return failure(e);}
}
ActWorldHostResult ActWorldHost::cancelAll(const std::string &reason) {
    try {Batch b(*this);std::vector<uint64_t> ids;for(const auto &entry:b.host.instances)ids.push_back(entry.first);
        for(auto id:ids)if(b.host.instances.at(id).status==ActInstanceStatus::Running)apply(b,id,prepareActCancel(b.host.instances.at(id),reason));
        commit(b);return {true,{},{}};
    }catch(const std::exception &e){return failure(e);}
}
bool ActWorldHost::ownsActor(EntityHandle h) const {for(const auto &i:state_.instances)if(i.second.owner==h && i.second.status==ActInstanceStatus::Running)return true;return false;}
bool ActWorldHost::controlsMovement(EntityHandle h) const {return state_.velocities.count(h)!=0;}
void ActWorldHost::resetCancelledClock() {
    for(const auto &entry:state_.instances) if(entry.second.status==ActInstanceStatus::Running)
        throw std::logic_error("Cannot reset the clock of a running ACT host");
    if(!state_.velocities.empty() || !state_.speech.empty())
        throw std::logic_error("Cancelled ACT host retains owned effects");
    if(publicationEpoch_==UINT64_MAX)throw std::overflow_error("ACT host publication epoch exhausted");
    state_.instances.clear();state_.relations.clear();state_.presentation.clear();
    state_.lastTick=uint64_t(world_.tick);++publicationEpoch_;
}

ActWorldRestoreGraph ActWorldHost::liveGraph(uint64_t generation) const {
    if(world_.tick<0)throw std::invalid_argument("Negative ACT World tick");
    return {world_.player,world_.monsters,world_.entities_,world_.ids_.snapshot(),
        world_.statuses_.snapshot(uint64_t(world_.nowMs()),generation),uint64_t(world_.tick),world_.characterLevel,
        world_.random_.snapshot(),world_.guardUntil_};
}
size_t ActWorldHost::eventReceiptBytes(const State &state) {
    size_t total=0;
    for(const auto &entry:state.instances) {
        if(entry.second.acceptedEventReceiptBytes>ActWorldRestoreBudget::maximumEventReceiptBytes-total)
            throw std::invalid_argument("ACT host typed event receipt aggregate byte budget exceeded");
        total+=entry.second.acceptedEventReceiptBytes;
    }
    return total;
}
void ActWorldHost::validateGraph(const ActWorldRestoreGraph &g,uint64_t generation) const {
    if(!generation || g.characterLevel<1 || g.monsters.size()>4096 || g.tick>uint64_t(INT64_MAX))
        throw std::invalid_argument("Invalid ACT outer graph clock/level/roster budget");
    const auto now=FixedStepClock::millisecondsAtTick(g.tick);
    if(now>uint64_t(INT64_MAX))throw std::invalid_argument("ACT outer graph time exceeds World range");
    const std::map<EntityHandle,ActEntityRelations> none;
    RestoreGraphView view(g,none);std::set<EntityHandle> roster;
    if(g.player.life==ActorLife::Removed || !view.actor(g.player.handle))throw std::invalid_argument("ACT outer graph has no registered player");
    roster.insert(g.player.handle);
    std::set<int> actorIds;
    for(const auto &a:g.monsters) {
        if(a.life==ActorLife::Removed) {
            if(g.entities.valid(a.handle))throw std::invalid_argument("Removed ACT outer actor remains registered");
            continue;
        }
        if(!view.actor(a.handle) || !roster.insert(a.handle).second || !actorIds.insert(a.id).second)
            throw std::invalid_argument("ACT outer graph has duplicate/unregistered actors");
    }
    const auto active=g.entities.active();
    if(roster!=std::set<EntityHandle>(active.begin(),active.end()))
        throw std::invalid_argument("ACT actor-only continuation has an unrepresented registered entity");
    SimulationIdSources ids;ids.restore(g.worldIds);
    checkHostJson(g.statusReceipt);
    if(g.statusReceipt.at("saved_at_ms")!=now || number(g.statusReceipt.at("commit_generation"))!=generation ||
       g.statusReceipt.contains("target_bundle"))throw std::invalid_argument("ACT full status receipt boundary mismatch");
    const auto &policy=g.statusReceipt.at("policy");
    if(!policy.at("infer_resistance_as_percent").is_boolean())throw std::invalid_argument("Invalid ACT status policy");
    StatusHost verifier(pvf_.identity(),StunStatusPolicy::inferredFlatChanceStunV1(policy.at("infer_resistance_as_percent").get<bool>()));
    verifier.restore(g.statusReceipt,now,generation,[this](const std::string &path){return pvf_.script(path);},
        [&](EntityHandle h){return bool(view.entity(h));});
    for(auto h:roster) {
        const auto *a=view.actor(h);
        if(a->hp<0 || a->mp<0 || (a->dir!=1 && a->dir!=-1) || int(a->life)<int(ActorLife::Alive) || int(a->life)>=int(ActorLife::Removed))
            throw std::invalid_argument("Invalid ACT outer actor resources/lifecycle/direction");
        checkHostJson(actorReceipt(*a));
    }
}
Json ActWorldHost::snapshotState(const State &state,const ActWorldRestoreGraph &g,uint64_t generation) const {
    if(!generation || state.lastTick!=g.tick)throw std::invalid_argument("ACT host snapshot requires same World commit generation/tick");
    (void)eventReceiptBytes(state);
    Json out=state.unknown;out["schema"]=3;out["commit_generation"]=generation;out["pvf_identity"]=pvf_.identity();
    out["static_identity"]=resources_.staticIdentity();out["policy"]=worldHostPolicy;
    out["entity_registry"]=g.entities.snapshot();out["world_ids"]=g.worldIds;out["status_receipt"]=g.statusReceipt;
    out["character_level"]=g.characterLevel;
    out["speech_enabled"]=options_.enableSpeechPresentation;out["speech_duration_ms"]=options_.speechDurationMs;
    out["last_tick"]=state.lastTick;out["instance_watermark"]=state.instanceWatermark;out["instances"]=Json::array();
    for(const auto &i:state.instances)out["instances"].push_back(snapshotActInstance(i.second,generation));
    out["velocities"]=Json::array();for(const auto &v:state.velocities)out["velocities"].push_back({{"handle",v.first.json()},{"instance_id",v.second.instanceId},{"value",vectorJson(v.second.value)}});
    out["relations"]=Json::array();for(const auto &r:state.relations)out["relations"].push_back({{"handle",r.first.json()},{"value",relationsJson(r.second)}});
    out["presentation"]=Json::array();for(const auto &p:state.presentation)out["presentation"].push_back({{"instance_id",p.first},{"animation",p.second.animation},
        {"animation_path",p.second.animationPath},{"anim_start",p.second.animStart},{"pose_frame",p.second.poseFrame}});
    out["speech"]=Json::array();for(const auto &s:state.speech)out["speech"].push_back(s.json());out["diagnostics"]=state.diagnostics;
    out["actor_receipts"]=Json::array();RestoreGraphView view(g,state.relations);
    for(auto handle:view.entities())out["actor_receipts"].push_back(actorReceipt(*view.actor(handle)));
    out["collision_policy"]="inferred-act-collision-v1";out["collisions"]=collisionSnapshot(state);
    if(!state.collisions.empty()) {
        if(g.combatRandom.is_null())throw std::invalid_argument("ACT collision continuation needs same-generation combat random receipt");
        out["collision_random_receipt"]=g.combatRandom;out["collision_player_guard_until"]=g.playerGuardUntil;
    }
    checkHostJson(out);
    return out;
}
Json ActWorldHost::snapshot(uint64_t generation) const {return snapshotState(state_,liveGraph(generation),generation);}
ActWorldHost::State ActWorldHost::prepareState(const Json &value,const ActWorldRestoreGraph &g,uint64_t generation) const {
        checkHostJson(value);validateGraph(g,generation);
        const auto schema=number(value.at("schema"));
        if(!generation || (schema!=2 && schema!=3) || number(value.at("commit_generation"))!=generation || value.at("pvf_identity")!=pvf_.identity() ||
           value.at("static_identity")!=resources_.staticIdentity() || value.at("policy")!=(schema==2?worldHostLegacyPolicy:worldHostPolicy) ||
           value.at("speech_enabled")!=options_.enableSpeechPresentation || value.at("entity_registry")!=g.entities.snapshot() || value.at("world_ids")!=g.worldIds ||
           value.at("status_receipt")!=g.statusReceipt || (schema==3 && value.at("character_level")!=g.characterLevel) ||
           number(value.at("speech_duration_ms"))!=options_.speechDurationMs || number(value.at("last_tick"))!=g.tick)
            throw std::invalid_argument("ACT host source/policy/commit/World clock or status receipt mismatch");
        if(!value.at("instances").is_array() || value.at("instances").size()>1024 || !value.at("actor_receipts").is_array())throw std::invalid_argument("Invalid ACT host checkpoint arrays");
        for(const char *key:{"relations","velocities","presentation","speech"})
            if(!value.at(key).is_array() || value.at(key).size()>4096)throw std::invalid_argument("ACT host collection budget exceeded");
        const std::map<EntityHandle,ActEntityRelations> none;RestoreGraphView oldView(g,none);
        Json receipts=Json::array();for(auto h:oldView.entities())receipts.push_back(actorReceipt(*oldView.actor(h)));
        if(receipts!=value.at("actor_receipts"))throw std::invalid_argument("ACT host requires exact actor identity/source/pose/resource receipts from the same outer generation");
        State candidate;candidate.lastTick=g.tick;candidate.instanceWatermark=number(value.at("instance_watermark"));candidate.unknown=value;
        for(const auto &r:value.at("relations")) {
            const auto h=EntityHandle::fromJson(r.at("handle"));
            if((schema==3 && !oldView.actor(h)) || !candidate.relations.emplace(h,relationsValue(r.at("value"))).second)throw std::invalid_argument("Duplicate/stale ACT entity relation owner");
        }
        RestoreGraphView view(g,candidate.relations);std::set<EntityHandle> owners;std::set<uint64_t> actions;
        for(const auto &i:value.at("instances")) {
            const auto &source=i.at("program");const auto compiled=compile(source.at("member_path").get<std::string>(),policyValue(i.at("policy")));
            if(!compiled.ok)throw std::invalid_argument("Saved ACT source is no longer executable under World consumers");
            const auto restored=restoreActInstance(compiled.program,i,view,generation);if(!restored.ok)throw std::invalid_argument(restored.error);
            if(restored.state.instanceId>candidate.instanceWatermark || restored.state.lastTick>candidate.lastTick || (restored.state.status==ActInstanceStatus::Running && restored.state.lastTick!=candidate.lastTick) ||
               !candidate.instances.emplace(restored.state.instanceId,restored.state).second || !actions.insert(restored.state.actionId).second ||
               (restored.state.status==ActInstanceStatus::Running && !owners.insert(restored.state.owner).second))throw std::invalid_argument("Saved ACT clock/owner/instance conflict");
        }
        for(const auto &v:value.at("velocities")) {
            const auto h=EntityHandle::fromJson(v.at("handle"));const auto id=number(v.at("instance_id"));
            const auto found=candidate.instances.find(id);const auto vector=vectorValue(v.at("value"));
            if(found==candidate.instances.end() || found->second.status!=ActInstanceStatus::Running || !view.actor(h) ||
               std::abs(vector.x)>std::numeric_limits<float>::max() || std::abs(vector.y)>std::numeric_limits<float>::max() || std::abs(vector.z)>std::numeric_limits<float>::max() ||
               !candidate.velocities.emplace(h,Velocity{id,vector}).second)throw std::invalid_argument("Invalid ACT velocity owner/generation");
        }
        for(const auto &p:value.at("presentation")) {
            const auto id=number(p.at("instance_id"));const auto i=candidate.instances.find(id);
            const auto *actor=i==candidate.instances.end()?nullptr:view.actor(i->second.owner);
            const auto pose=signedValue(p.at("pose_frame"));
            if(i==candidate.instances.end() || i->second.status!=ActInstanceStatus::Running || !i->second.program->motion || !actor || pose < -1 || pose > std::numeric_limits<int>::max() ||
               actor->animation!="act" || actor->animationPath!=i->second.program->source.memberPath ||
               !candidate.presentation.emplace(id,Presentation{p.at("animation").get<std::string>(),p.at("animation_path").get<std::string>(),signedValue(p.at("anim_start")),int(pose)}).second)
                throw std::invalid_argument("Invalid ACT presentation owner");
        }
        for(const auto &i:candidate.instances)if(i.second.status==ActInstanceStatus::Running && i.second.program->motion && !candidate.presentation.count(i.first))throw std::invalid_argument("Missing ACT presentation cleanup receipt");
        std::set<std::string> speechKeys;for(const auto &s:value.at("speech")) {
            ActSpeechBubble bubble{number(s.at("instance_id")),number(s.at("expires_ms")),EntityHandle::fromJson(s.at("speaker")),s.at("text").get<std::string>(),s.at("event_key").get<std::string>()};
            const auto owner=candidate.instances.find(bubble.instanceId);const auto now=FixedStepClock::millisecondsAtTick(g.tick);
            if(!options_.enableSpeechPresentation || !view.actor(bubble.speaker) || owner==candidate.instances.end() || owner->second.status!=ActInstanceStatus::Running || bubble.expiresMs<=now ||
               bubble.expiresMs-now>options_.speechDurationMs || !speechKeys.insert(bubble.eventKey).second)throw std::invalid_argument("Invalid ACT speech receipt");
            const std::string prefix="act:"+std::to_string(bubble.instanceId)+":"+std::to_string(owner->second.actionId)+":";
            if(bubble.eventKey.rfind(prefix,0)!=0)throw std::invalid_argument("ACT speech occurrence belongs to another action");
            const auto tail=bubble.eventKey.substr(prefix.size());
            if(tail.empty() || tail[0]=='0' || tail.find_first_not_of("0123456789")!=std::string::npos)throw std::invalid_argument("Invalid ACT speech command sequence");
            const auto sequence=std::stoull(tail);
            if(sequence>=owner->second.commandIds.nextValue())throw std::invalid_argument("ACT speech command sequence was never issued");
            candidate.speech.push_back(std::move(bubble));
        }
        candidate.diagnostics=value.at("diagnostics");if(!candidate.diagnostics.is_array() || candidate.diagnostics.size()>256)throw std::invalid_argument("Invalid ACT diagnostics history");
        for(const char *key:{"schema","commit_generation","pvf_identity","static_identity","entity_registry","world_ids","status_receipt","policy","speech_enabled","speech_duration_ms","last_tick","instance_watermark","instances","velocities","relations","presentation","speech","diagnostics","actor_receipts"})candidate.unknown.erase(key);
        if(schema==3)candidate.unknown.erase("character_level");
        else if(candidate.unknown.contains("character_level")) {
            Json preserved={{"character_level",candidate.unknown.at("character_level")}};
            if(candidate.unknown.contains("legacy_host_extension_fields"))preserved["previous_value"]=candidate.unknown.at("legacy_host_extension_fields");
            candidate.unknown["legacy_host_extension_fields"]=std::move(preserved);candidate.unknown.erase("character_level");
        }
        restoreCollisions(candidate,value,g);
        for(const char *key:{"collision_policy","collisions","collision_random_receipt","collision_player_guard_until"})candidate.unknown.erase(key);
        (void)eventReceiptBytes(candidate);return candidate;
}
ActWorldHost::PreparedRestore ActWorldHost::prepareRestore(const Json &value,uint64_t generation,const ActWorldRestoreGraph &graph) const {
    PreparedRestore result;
    try {
        if(publicationEpoch_==UINT64_MAX)throw std::overflow_error("ACT host publication epoch exhausted");
        result.originReceipt_=snapshot(generation);
        auto candidate=prepareState(value,graph,generation);
        result.candidateReceipt_=snapshotState(candidate,graph,generation);
        result.state_=std::make_unique<State>(std::move(candidate));
        result.origin_=this;result.expectedEpoch_=publicationEpoch_;result.generation_=generation;
        result.diagnostics.push_back({{"code","act_host_restore_prepared"},{"world_published",false},{"callbacks_dispatched",false}});
    }catch(const std::exception &e){result.state_.reset();result.error=e.what();}
    catch(...){result.state_.reset();result.error="ACT candidate preparation raised a non-standard exception";}
    return result;
}
ActWorldHost::PreparedRestore ActWorldHost::prepareRemappedRestore(const Json &value,uint64_t generation,
    const ActWorldRestoreGraph &saved,const ActWorldRestoreGraph &prepared,const std::map<EntityHandle,EntityHandle> &mapping) const {
    PreparedRestore result;
    try {
        if(publicationEpoch_==UINT64_MAX)throw std::overflow_error("ACT host publication epoch exhausted");
        result.originReceipt_=snapshot(generation);
        if(number(value.at("schema"))!=3 || value.at("policy")!=worldHostPolicy)
            throw std::invalid_argument("Legacy ACT host lacks typed continuation receipts; remap cannot use a cancel fallback");
        // The unmodified saved actor/registry/ID/status receipts and every old
        // event digest are checked BEFORE generating any remapped receipt.
        auto original=prepareState(value,saved,generation);validateGraph(prepared,generation);
        if(saved.tick!=prepared.tick || saved.characterLevel!=prepared.characterLevel || saved.worldIds!=prepared.worldIds)
            throw std::invalid_argument("ACT candidate changed saved logical clock/IDs or character level");
        const std::map<EntityHandle,ActEntityRelations> none;
        RestoreGraphView preparedView(prepared,none),savedView(saved,none);
        ActEntityHandleRemapper remap(saved.entities,mapping,prepared.entities,preparedView);
        const auto liveNext=number(world_.entities_.snapshot().at("ids").at("next"));
        for(const auto &entry:mapping) {
            if(!liveNext || entry.second.id<liveNext)throw std::invalid_argument("ACT fresh registry did not merge current live allocation history");
            const auto *oldActor=savedView.actor(entry.first),*newActor=preparedView.actor(entry.second);
            if(!oldActor || !newActor || oldActor->capturedBy>=0 || newActor->capturedBy>=0)
                throw std::invalid_argument("ACT continuation capture serializer is not registered");
            auto oldReceipt=actorReceipt(*oldActor);oldReceipt["handle"]=entry.second.json();
            if(oldReceipt!=actorReceipt(*newActor))throw std::invalid_argument("ACT remap changed source actor state beyond its typed identity");
        }
        // Status attackers and diagnostic traces remain historical evidence.
        // Only registered active/contact TARGET fields change. Unknown JSON is
        // compared unchanged; no shape-based recursion or attacker aliasing.
        auto expectedStatus=saved.statusReceipt,actualStatus=prepared.statusReceipt;
        for(auto &active:expectedStatus.at("active")) {
            (void)remap.handle(EntityHandle::fromJson(active.at("attacker")));
            active["target"]=remap.handle(EntityHandle::fromJson(active.at("target")),true).json();
        }
        for(auto &contact:expectedStatus.at("contacts")) {
            auto &identity=contact.at("identity");(void)remap.handle(EntityHandle::fromJson(identity.at("attacker")));
            identity["target"]=remap.handle(EntityHandle::fromJson(identity.at("target"))).json();
        }
        const auto savedRevision=number(expectedStatus.at("revision")),preparedRevision=number(actualStatus.at("revision"));
        const auto liveRevision=number(result.originReceipt_.at("status_receipt").at("revision"));
        if(preparedRevision<=savedRevision || preparedRevision<=liveRevision)
            throw std::invalid_argument("ACT candidate status revision must exceed saved and current runtime revisions");
        MonotonicIds statusFloor;statusFloor.restore(expectedStatus.at("instance_ids"));
        MonotonicIds currentFloor;currentFloor.restore(result.originReceipt_.at("status_receipt").at("instance_ids"));statusFloor.merge(currentFloor);
        MonotonicIds candidateFloor;candidateFloor.restore(actualStatus.at("instance_ids"));
        auto merged=statusFloor;merged.merge(candidateFloor);
        if(merged.snapshot()!=candidateFloor.snapshot())throw std::invalid_argument("ACT candidate status watermark lost saved/live allocation history");
        expectedStatus.erase("revision");actualStatus.erase("revision");expectedStatus.erase("instance_ids");actualStatus.erase("instance_ids");
        sortStatusContacts(expectedStatus);sortStatusContacts(actualStatus);
        if(expectedStatus!=actualStatus)throw std::invalid_argument("ACT remapped status receipt changed frozen outcomes, source, lifetime or historical evidence");
        State candidate;candidate.lastTick=original.lastTick;candidate.instanceWatermark=original.instanceWatermark;
        candidate.unknown=original.unknown;candidate.diagnostics=original.diagnostics;candidate.presentation=original.presentation;
        candidate.collisions=original.collisions;
        for(auto &[id,collision]:candidate.collisions) {
            std::map<EntityHandle,Json> hits;
            for(const auto &[handle,receipt]:collision.acceptedTargets) {
                auto transformed=receipt;const auto mapped=remap.handle(handle);
                transformed["target"]=mapped.json();hits.emplace(mapped,std::move(transformed));
            }
            collision.acceptedTargets=std::move(hits);
        }
        for(const auto &relation:original.relations) {
            auto r=relation.second;r.target=remap.handle(r.target);r.lastAttacker=remap.handle(r.lastAttacker);
            r.lastAttackSuccess=remap.handle(r.lastAttackSuccess);r.summonMaster=remap.handle(r.summonMaster);
            for(auto &hit:r.lastAttackSuccesses)hit=remap.handle(hit);
            if(!candidate.relations.emplace(remap.handle(relation.first,true),std::move(r)).second)
                throw std::invalid_argument("ACT remapped relation owner collision");
        }
        RestoreGraphView candidateView(prepared,candidate.relations);
        for(const auto &instance:original.instances) {
            const auto restored=restoreRemappedActInstance(instance.second.program,snapshotActInstance(instance.second,generation),
                saved.entities,mapping,prepared.entities,candidateView,generation);
            if(!restored.ok)throw std::invalid_argument(restored.error);
            candidate.instances.emplace(instance.first,restored.state);
        }
        for(const auto &velocity:original.velocities)
            if(!candidate.velocities.emplace(remap.handle(velocity.first,true),velocity.second).second)
                throw std::invalid_argument("ACT remapped velocity owner collision");
        for(auto bubble:original.speech){bubble.speaker=remap.handle(bubble.speaker,true);candidate.speech.push_back(std::move(bubble));}
        const auto transformed=snapshotState(candidate,prepared,generation);
        // Run the strict ordinary decoder again over the complete transformed
        // graph, now checking new ownership, speech keys and cleanup receipts.
        candidate=prepareState(transformed,prepared,generation);
        result.candidateReceipt_=snapshotState(candidate,prepared,generation);
        result.state_=std::make_unique<State>(std::move(candidate));result.origin_=this;
        result.expectedEpoch_=publicationEpoch_;result.generation_=generation;
        result.diagnostics.push_back({{"code","act_host_typed_restore_prepared"},{"instances",result.state_->instances.size()},
            {"old_handle_aliases_installed",false},{"world_published",false},{"callbacks_dispatched",false}});
    }catch(const std::exception &e){result.state_.reset();result.error=e.what();}
    catch(...){result.state_.reset();result.error="ACT typed host preparation raised a non-standard exception";}
    return result;
}
bool ActWorldHost::canPublish(const PreparedRestore &prepared) const {
    if(!prepared.ready() || prepared.origin_!=this || prepared.expectedEpoch_!=publicationEpoch_ || publicationEpoch_==UINT64_MAX)return false;
    try{return prepared.originReceipt_==snapshot(prepared.generation_);}catch(...){return false;}
}
void ActWorldHost::publishAfterOuterCommit(PreparedRestore &&prepared) noexcept {
    // Private coordinator precondition: canPublish was checked before the
    // first authoritative swap and no other writer may interleave that section.
    assert(prepared.ready() && prepared.origin_==this && prepared.expectedEpoch_==publicationEpoch_ && publicationEpoch_!=UINT64_MAX);
    static_assert(std::is_nothrow_swappable<State>::value,"ACT continuation publication must not throw");
    using std::swap;swap(state_,*prepared.state_);++publicationEpoch_;prepared.state_.reset();prepared.origin_=nullptr;
}
ActWorldHostResult ActWorldHost::publish(PreparedRestore &&prepared) {
    try {
        if(!canPublish(prepared))throw std::invalid_argument("Stale, foreign or consumed ACT host restore candidate");
        if(snapshotState(*prepared.state_,liveGraph(prepared.generation_),prepared.generation_)!=prepared.candidateReceipt_)
            throw std::invalid_argument("World has not published the ACT candidate's exact graph; use the single outer coordinator");
        ActWorldHostResult result{true,{},prepared.diagnostics}; // Allocate before first mutation.
        static_assert(std::is_nothrow_move_constructible<ActWorldHostResult>::value,"ACT publication result must return without throwing");
        publishAfterOuterCommit(std::move(prepared));return result;
    }catch(const std::exception &e){return failure(e);}
}
ActWorldHostResult ActWorldHost::restore(const Json &value,uint64_t generation) {
    try {
        auto prepared=prepareRestore(value,generation,liveGraph(generation));
        if(!prepared.ready())throw std::invalid_argument(prepared.error);
        return publish(std::move(prepared));
    }catch(const std::exception &e){return failure(e);}
}
} // namespace dnf
