#include "dnf/squirrel_action_service.hpp"
#include <algorithm>
#include <cctype>
#include <climits>
#include <map>
#include <stdexcept>
#include <thread>

namespace dnf {
namespace {
// A deliberately narrow lexer for source registration/constant receipts. All
// original bytes remain in SourceUnit; offsets are original byte positions.
// No comments/string contents are scanned as registration code.
struct Token { std::string text; size_t offset = 0, end = 0; bool quoted = false; };
std::vector<Token> lex(const Bytes &bytes) {
    std::vector<Token> out;
    for(size_t i=0;i<bytes.size();) {
        const auto c=bytes[i];if(std::isspace(static_cast<unsigned char>(c))){++i;continue;}
        if(c=='/'&&i+1<bytes.size()&&bytes[i+1]=='/') {while(i<bytes.size()&&bytes[i]!='\n')++i;continue;}
        if(c=='/'&&i+1<bytes.size()&&bytes[i+1]=='*') {
            i+=2;while(i+1<bytes.size()&&!(bytes[i]=='*'&&bytes[i+1]=='/'))++i;
            if(i+1==bytes.size())throw std::invalid_argument("Unclosed source registration comment");i+=2;continue;
        }
        Token token;token.offset=i;
        if(c=='"'||c=='\'') {
            token.quoted=true;const auto quote=c;++i;bool done=false;
            while(i<bytes.size()) {
                const auto v=bytes[i++];if(v==quote){done=true;break;}
                if(v=='\\') {
                    if(i==bytes.size())throw std::invalid_argument("Truncated registration string");
                    const auto escaped=bytes[i++];
                    if(escaped!=quote&&escaped!='\\')throw std::invalid_argument("Unsupported escape in source registration");
                    token.text.push_back(char(escaped));
                } else token.text.push_back(char(v));
            }
            if(!done)throw std::invalid_argument("Unclosed source registration string");
        } else if(std::isalnum(static_cast<unsigned char>(c))||c=='_') {
            while(i<bytes.size()&&(std::isalnum(static_cast<unsigned char>(bytes[i]))||bytes[i]=='_'))token.text.push_back(char(bytes[i++]));
        } else if(i+1<bytes.size()&&((c=='<'&&bytes[i+1]=='-')||(c=='='&&bytes[i+1]=='='))) {
            token.text=std::string(1,char(c))+char(bytes[i+1]);i+=2;
        } else token.text.push_back(char(bytes[i++]));
        token.end=i;out.push_back(std::move(token));
    }
    return out;
}
int constant(const std::vector<Token> &tokens,const std::string &name) {
    std::optional<int> result;
    for(size_t i=0;i+2<tokens.size();++i)if(!tokens[i].quoted&&tokens[i].text==name&&tokens[i+1].text=="<-") {
        if(result)throw std::invalid_argument("Ambiguous source constant: "+name);
        size_t n=i+2;int sign=1;if(tokens[n].text=="-"){sign=-1;++n;}
        if(n>=tokens.size()||tokens[n].text.empty()||tokens[n].quoted||
           !std::all_of(tokens[n].text.begin(),tokens[n].text.end(),[](unsigned char c){return c>='0'&&c<='9';}))
            throw std::invalid_argument("Source constant is not an admitted integer literal: "+name);
        const auto value=std::stoll(tokens[n].text)*sign;if(value<INT32_MIN||value>INT32_MAX)throw std::out_of_range("Source constant outside int32");
        result=int(value);
    }
    if(!result)throw std::invalid_argument("Missing source constant: "+name);return *result;
}
Json resultJson(const squirrel_stage::Result &result) {
    Json diagnostics=Json::array();for(const auto &d:result.diagnostics)diagnostics.push_back({{"code",d.code},{"message",d.message},
        {"source",d.source.json()},{"line",d.line},{"column",d.column}});
    return {{"ok",result.ok},{"closed",result.closed},{"arena_released",result.arenaReleased},
        {"instructions",result.instructions},{"staged_commands",result.stagedCommands},{"diagnostics",diagnostics}};
}
// The VM's commit parks an already prepared World batch. This is still a
// synchronous single-writer transaction: publication follows accepted begin
// in the SAME call, before any other World event producer runs.
class DeferredBridge final : public squirrel_stage::Bridge {
  public:
    SquirrelWorldBridge world;
    std::unique_ptr<squirrel_stage::PreparedSoundBatch> pending;
    bool parked=false;
    DeferredBridge(World &w,Pvf &p,Assets &a,const std::string &identity,SquirrelInvocationContext context)
        :world(w,p,a,identity,std::move(context)){}
    bool valid(EntityHandle h)const noexcept override{return world.valid(h);}
    bool hasBuffSkillIndex()const noexcept override{return world.hasBuffSkillIndex();}
    bool hasSoundConsumer()const noexcept override{return world.hasSoundConsumer();}
    int buffSkillIndex(EntityHandle h)const override{return world.buffSkillIndex(h);}
    std::optional<SourceRef> resolveSound(const std::string &s,const SourceRef &r)const override{return world.resolveSound(s,r);}
    std::unique_ptr<squirrel_stage::PreparedSoundBatch> prepare(const std::vector<squirrel_stage::SoundCommand> &commands)override {
        if(parked)throw std::invalid_argument("More than one callback batch in one action preparation");return world.prepare(commands);
    }
    void commit(std::unique_ptr<squirrel_stage::PreparedSoundBatch> batch)noexcept override {pending=std::move(batch);parked=true;}
    void cleanup(uint64_t id,const std::string &reason)noexcept override {pending.reset();world.cleanup(id,reason);}
    void publish()noexcept {if(pending)world.commit(std::move(pending));}
};
} // namespace

struct SquirrelActionService::Impl {
    struct Action {
        uint64_t instance=0,action=0,sequence=0,attempt=0;
        EntityHandle owner;
        SkillKey skill;
        std::unique_ptr<DeferredBridge> bridge;
        std::unique_ptr<squirrel_stage::Instance> vm;
        Json receipt=Json::object(),archiveReceipt=Json::object();
        ~Action(){if(vm)vm->close("action_owner_release");}
    };
    struct Prepared final : PreparedExperimentalSkillAction {
        Impl &service;std::unique_ptr<Action> action;bool published=false;
        uint64_t epoch=0;int64_t tick=0;size_t eventCount=0;
        Prepared(Impl &s,std::unique_ptr<Action> a):service(s),action(std::move(a)),epoch(s.epoch),tick(s.world.tick),eventCount(s.world.events.size()){}
        void publish()noexcept override {
            if(published||!action)return;published=true;
            if(service.thread!=std::this_thread::get_id()||!epoch||service.epoch!=epoch||service.world.tick!=tick||
               service.world.events.size()!=eventCount||!action->bridge->valid(action->owner)) {
                if(action->vm)action->vm->close("prepared_action_invalidated");action.reset();++service.discards;return;
            }
            // The gate and publish are private synchronous runtime operations;
            // no external reentry or scene switch may occur between them.
            service.cancel("replaced_by_accepted_action");
            action->bridge->publish();service.acceptedSequence=action->sequence;
            service.lastAccepted.swap(action->archiveReceipt);
            service.active=std::move(action);++service.commits;
        }
    };
    World &world;Pvf &pvf;Assets &assets;
    std::string staticIdentity,pvfIdentity;
    std::thread::id thread=std::this_thread::get_id();
    std::unique_ptr<squirrel_stage::SourceServices> sources=squirrel_stage::windowsSourceServices();
    std::unique_ptr<Action> active;
    SourceRef registration,enumSource,callbackSource;
    Json route=Json::object(),last=Json::object(),lastAccepted=Json::object(),lastClosedBridge=Json::object();
    std::map<int,std::string> buffSkills;
    int job=-1,state=-1;
    bool routeAvailable=false;
    EntityHandle owner;CharacterIdentity character;
    uint64_t attemptWatermark=0,attemptTick=0,acceptedSequence=0,commits=0,cleanups=0,epoch=1,discards=0;
    std::string lastCleanup;
    Impl(World &w,Pvf &p,Assets &a,std::string identity):world(w),pvf(p),assets(a),staticIdentity(std::move(identity)),pvfIdentity(p.identity()) {
        if(staticIdentity.empty())throw std::invalid_argument("Squirrel service needs fingerprinted static identity");
        try {
        // Adapter paths identify source registration semantics, never skill
        // numeric values or visual resources. Unknown versions reject here.
        const auto registrationPath="sqr/character/atmage_load_state.nut";
        const auto callbackPath="sqr/character/atmage/atmage_buff.nut";
        registration=makeSourceRef(pvf,registrationPath);enumSource=makeSourceRef(pvf,"sqr/dnf_enum_header.nut");
        callbackSource=makeSourceRef(pvf,callbackPath);
        const auto registrations=lex(pvf.read(registrationPath)),enums=lex(pvf.read(enumSource.memberPath)),callbacks=lex(pvf.read(callbackPath));
        size_t matches=0;
        for(size_t i=0;i+14<registrations.size();++i) {
            const auto &t=registrations;
            if(t[i].text!="IRDSQRCharacter"||t[i].quoted||t[i+1].text!="."||t[i+2].text!="pushState"||t[i+3].text!="("||
               !t[i+6].quoted||!t[i+8].quoted||t[i+8].text!="Buff")continue;
            if(t[i+5].text!=","||t[i+7].text!=","||t[i+9].text!=","||t[i+11].text!=","||t[i+12].text!="-"||
               t[i+13].text!="1"||t[i+14].text!=")"||normalize("sqr/"+t[i+6].text)!=callbackPath)
                throw std::invalid_argument("Unsupported source Buff pushState signature");
            job=constant(enums,t[i+4].text);state=constant(enums,t[i+10].text);++matches;
            auto span=registration;span.byteOffset=t[i].offset;span.byteLength=t[i+14].end-t[i].offset;
            route={{"registration",span.json()},{"job_symbol",t[i+4].text},{"job_id",job},{"state_symbol",t[i+10].text},
                {"state",state},{"suffix",t[i+8].text},{"source_skill_operand",-1},{"callback","onAfterSetState_Buff"},
                {"dispatch_policy",squirrelActionPolicy},{"native_dispatch_proven",false}};
        }
        if(matches!=1)throw std::invalid_argument("Expected one unambiguous source Buff registration");
        bool hasCallback=false;
        for(size_t i=0;i+2<callbacks.size();++i) {
            if(callbacks[i].text=="function"&&callbacks[i+1].text=="onAfterSetState_Buff"&&callbacks[i+2].text=="(")hasCallback=true;
            if(callbacks[i].text=="buffSkillIndex"&&callbacks[i+1].text=="==") {
                const auto symbol=callbacks[i+2].text;const auto key=constant(enums,symbol);
                if(!buffSkills.emplace(key,symbol).second)throw std::invalid_argument("Duplicate source Buff skill branch");
            }
        }
        if(!hasCallback||buffSkills.empty())throw std::invalid_argument("No source Buff callback/skill branches");
        route["callback_source"]=callbackSource.json();route["enum_source"]=enumSource.json();
        route["buff_attributes_complete"]=false;route["full_skill_complete"]=false;
        routeAvailable=true;
        } catch(const std::exception &error) {
            route={{"available",false},{"code","squirrel_source_route_unavailable"},{"message",error.what()},
                {"full_skill_complete",false},{"native_dispatch_proven",false}};
        }
    }
    void cancel(const std::string &reason)noexcept {
        if(thread!=std::this_thread::get_id())return;
        if(epoch)epoch=epoch==UINT64_MAX?0:epoch+1;
        if(active){
            try{auto receipt=active->bridge->world.diagnostics();lastClosedBridge.swap(receipt);}catch(...){}
            if(active->vm)active->vm->close(reason);active.reset();++cleanups;
        }
        // Reasons supplied by serialized World call sites are short literals.
        try{lastCleanup=reason;}catch(...){}
    }
};
SquirrelActionService::SquirrelActionService(World &w,Pvf &p,Assets &a,std::string identity)
    :impl_(std::make_unique<Impl>(w,p,a,std::move(identity))){}
SquirrelActionService::~SquirrelActionService()=default;
std::unique_ptr<PreparedExperimentalSkillAction> SquirrelActionService::prepare(const ExperimentalSkillActionRequest &request) {
    auto &s=*impl_;
    if(s.thread!=std::this_thread::get_id()||!s.epoch)throw std::invalid_argument("Squirrel action requires its simulation writer and an unexhausted lifecycle epoch");
    if(!s.routeAvailable||request.key.jobId!=s.job||!s.buffSkills.count(request.key.skillId)) {
        s.last={{"ok",false},{"code",s.routeAvailable?"squirrel_callback_not_routed":"squirrel_source_route_unavailable"},
            {"skill",request.key.json()},{"skill_source",request.skillSource.json()},
            {"message","Only the separately identified user experimental motion executes; no Squirrel skill behavior is claimed"},
            {"missing_native_api_policy","Unadmitted source callbacks remain disabled; see per-source NUT dependency matrix"},
            {"full_skill_complete",false}};
        return nullptr;
    }
    const auto &world=s.world;const auto *actor=static_cast<const World &>(world).resolveActor(world.player.handle);
    if(s.pvf.identity()!=s.pvfIdentity||!world.usesSourceGrowth()||!world.isExperimentalCharacter()||request.key.jobId!=world.identity().jobId||
       !actor||actor->dead||actor->life!=ActorLife::Alive||request.fixedTick!=uint64_t(world.tick)||!request.attemptSequence||!request.actionSequence)
        throw std::invalid_argument("Squirrel action World/content/owner/tick identity differs");
    if(!(s.owner==actor->handle)||!(s.character==world.identity())) {
        s.cancel("owner_incarnation_changed");s.owner=actor->handle;s.character=world.identity();s.attemptWatermark=0;s.attemptTick=0;s.acceptedSequence=0;
    }
    if(request.fixedTick<s.attemptTick||(request.fixedTick==s.attemptTick&&request.attemptSequence<=s.attemptWatermark)||
       request.actionSequence<=s.acceptedSequence)
        throw std::invalid_argument("Squirrel action event replay rejected");
    // The outer World adapter may discard a runtime candidate after its own
    // late source preflight. The live attempt counter then correctly stays
    // unchanged; a new input on a later tick is a distinct attempt. The pair
    // (fixedTick,attemptSequence) still rejects reentry/replay of this attempt.
    s.attemptTick=request.fixedTick;s.attemptWatermark=request.attemptSequence;
    const auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
    const auto row=plan.skills.find(request.key);
    const auto *binding=runtime.configuration().binding(request.key);
    if(row==plan.skills.end()||row->second.kind!=SkillSourceKind::Active||!binding||request.skillSource.json()!=row->second.source.json()||
       request.motionSource.json()!=binding->motion.source.json()||plan.pvfIdentity!=s.pvfIdentity)
        throw std::invalid_argument("Squirrel action skill/motion binding is stale or foreign");
    auto action=std::make_unique<Impl::Action>();
    // A failed preparation burns issued monotonic IDs; it does not spend MP,
    // start CD, change RNG or publish events. Never rewind World ID sources.
    action->instance=s.world.idSources().requests.next();action->action=s.world.idSources().actions.next();
    action->owner=actor->handle;action->skill=request.key;action->sequence=request.actionSequence;action->attempt=request.attemptSequence;
    action->bridge=std::make_unique<DeferredBridge>(s.world,s.pvf,s.assets,s.staticIdentity,
        SquirrelInvocationContext{action->instance,action->action,action->owner,request.key});
    action->vm=std::make_unique<squirrel_stage::Instance>(*s.sources,*action->bridge,action->instance);
    const auto load=[&](const SourceRef &expected) {
        const auto source=action->bridge->world.source(expected.memberPath);
        if(source.source.json()!=expected.json())throw std::invalid_argument("Squirrel route source changed during bound session");
        const auto result=action->vm->load(source);if(!result.ok){s.last=resultJson(result);throw std::runtime_error("Squirrel source admission failed: "+s.last.dump());}
    };
    load(s.enumSource);load(s.callbackSource);
    const auto result=action->vm->invoke("onAfterSetState_Buff",action->owner,action->action,{s.state,Json::array(),true});
    s.last=resultJson(result);
    if(!result.ok||!action->bridge->parked)throw std::runtime_error("Squirrel callback preparation failed: "+s.last.dump());
    action->receipt={{"route",s.route},{"skill",request.key.json()},{"skill_source",request.skillSource.json()},
        {"motion_source",request.motionSource.json()},{"owner",action->owner.json()},{"instance",action->instance},
        {"action",action->action},{"action_sequence",action->sequence},{"attempt_sequence",action->attempt},
        {"vm_policy",squirrel_stage::vmPolicyId},{"static_identity",s.staticIdentity},{"callback",resultJson(result)},
        {"dispatch_classification","inferred event attached to an accepted user-configured experimental motion"},
        {"buff_attributes_complete",false},{"native_dispatch_proven",false}};
    action->archiveReceipt=action->receipt; // Allocate before no-throw publication.
    return std::make_unique<Impl::Prepared>(s,std::move(action));
}
void SquirrelActionService::observe(std::optional<uint64_t> sequence)noexcept {
    auto &s=*impl_;if(s.thread!=std::this_thread::get_id())return;
    if(!s.active)return;
    const auto *actor=static_cast<const World &>(s.world).resolveActor(s.active->owner);
    if(!actor||actor->dead||actor->life!=ActorLife::Alive)s.cancel("death_or_retired_owner");
    else if(!(s.character==s.world.identity())||s.world.player.handle!=s.active->owner)s.cancel("character_changed");
    else if(!sequence||*sequence!=s.active->sequence)s.cancel("motion_complete_or_interrupted");
    // No invoke here: paused/hitstop ticks retain the instance without replay.
}
void SquirrelActionService::cancel(const std::string &reason)noexcept {impl_->cancel(reason);}
Json SquirrelActionService::diagnostics()const {
    const auto &s=*impl_;if(s.thread!=std::this_thread::get_id())throw std::invalid_argument("Squirrel diagnostics require simulation thread");
    return {{"policy",squirrelActionPolicy},{"vm_policy",squirrel_stage::vmPolicyId},{"pvf_identity",s.pvfIdentity},
        {"static_identity",s.staticIdentity},{"route",s.route},{"route_available",s.routeAvailable},{"active",bool(s.active)},
        {"active_receipt",s.active?s.active->receipt:Json()},
        {"world_bridge",s.active?s.active->bridge->world.diagnostics():Json()},
        {"last_accepted_receipt",s.lastAccepted},{"last_closed_bridge",s.lastClosedBridge},
        {"commits",s.commits},{"cleanups",s.cleanups},{"discarded_preparations",s.discards},{"lifecycle_epoch",s.epoch},{"last_cleanup",s.lastCleanup},
        {"last_result",s.last},{"attempt_tick",s.attemptTick},{"attempt_watermark",s.attemptWatermark},{"accepted_sequence",s.acceptedSequence},
        {"full_skill_complete",false},{"native_2_1_1_parity",false},{"persistent_entities_supported",false}};
}
} // namespace dnf
