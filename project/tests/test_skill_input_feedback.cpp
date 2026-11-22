#include "explicit_skill_preview_fixture.hpp"
#include "dnf/combat.hpp"
#include "dnf/progression.hpp"
#include "dnf/storage.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdexcept>

namespace dnf {
namespace {
int defaultIndex(const World &world) {
    int result=-1;
    for(size_t index=0;index<world.skills.size();++index)if(world.skills[index].sourceData&&
        sourceBaseDefaultSkillCommand(*world.skills[index].sourceData,world.identity().growtype)) {
        if(result>=0)throw std::runtime_error("Ambiguous default source Z fixture");result=int(index);
    }
    if(result<0)throw std::runtime_error("Missing default source Z fixture");return result;
}
void ground(World &world) {
    world.combat=true;world.freezeAi=true;world.mapWidth=1600;world.walkRects={{0,185,1600,240}};
    world.player.x=world.player.px=560;world.player.y=world.player.py=300;world.player.dir=1;
    world.player.mp=world.player.maxMp;
}
void press(World &world,int key) {world.enqueue({world.simulationNanoseconds(),key,true});world.advanceSingleTick();}
void queueZ(World &world) {press(world,4);press(world,6);}
size_t costsFor(const World &world,int skillId) {
    size_t result=0;for(const auto &event:world.events)if(event.kind=="skill_cost"&&event.name==
        world.skills[size_t(defaultIndex(world))].key&&skillId==world.skills[size_t(defaultIndex(world))].id)++result;return result;
}
Json eventSignature(const World &world) {
    Json out=Json::array();for(const auto &event:world.events)if(event.kind=="skill_cost"||event.kind=="stage"||
        event.kind=="skill_buffered"||event.kind=="skill_buffer_released"||event.kind=="skill_rejected")
        out.push_back({{"tick",event.tick},{"kind",event.kind},{"name",event.name},{"value",event.value}});
    return out;
}
Json scheduled(Pvf &pvf,Assets &assets,int fps,bool catchup=false) {
    World world(pvf,assets,WorldRules::BetaFoundationV1);ground(world);
    world.enqueue({0,4,true});world.enqueue({50000000,6,true});world.enqueue({70000000,6,false});world.enqueue({80000000,4,false});
    const int64_t duration=2000000000;int64_t elapsed=0;size_t step=0;
    const std::vector<int64_t> debt={17000000,610000000,1000000,17000000,350000000,25000000};
    while(elapsed<duration) {
        const int64_t next=catchup?std::min(duration,elapsed+debt[step++%debt.size()]):
            std::min(duration,int64_t(++step)*1000000000/fps);
        world.advance(next-elapsed);elapsed=next;
    }
    const int index=defaultIndex(world);
    return {{"events",eventSignature(world)},{"mp",world.player.mp},{"cooldown",world.remainingCd(index)},
        {"tick",world.tick},{"x",world.player.x},{"y",world.player.y},{"animation",world.player.animation},
        {"buffer",world.skillInputDiagnostics().at("buffered_default_skill")}};
}
} // namespace

Json runSkillInputFeedbackTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool okay,const std::string &message) {
        if(!okay)throw std::runtime_error("Skill input feedback: "+message);checks.push_back(message);
    };
    {
        World baseline(pvf,assets,WorldRules::BetaFoundationV1),world(pvf,assets,WorldRules::BetaFoundationV1);
        ground(baseline);ground(world);const int index=defaultIndex(world);const int mp=world.player.mp;
        const auto cost=world.skillCosts(index,true);
        check(cost.consumeMp()&&cost.cooldownMs(),"Default Z uses the actual selected source command cost");
        press(baseline,4);press(world,4);baseline.advanceSingleTick();press(world,6);
        check(world.activeSkill()<0&&world.hasBufferedDefaultSkill()&&world.player.mp==mp&&world.remainingCd(index)==0,
            "Default Z during a real ordinary action queues without cancel, payment or cooldown");
        int64_t completed=-1,released=-1;
        for(size_t tick=0;tick<240;++tick) {
            baseline.advanceSingleTick();world.advanceSingleTick();
            if(completed<0&&baseline.player.animation=="stay")completed=baseline.tick;
            if(released<0&&world.activeSkill()==index)released=world.tick;
            if(completed>=0&&released>=0)break;
        }
        check(completed>0&&released==completed,"Buffered Z starts in the same fixed tick as unmodified source ordinary action completion");
        check(world.player.mp==mp-*cost.consumeMp()&&world.remainingCd(index)==int64_t(std::ceil(*cost.cooldownMs()))&&
            !world.hasBufferedDefaultSkill(),"Owned action completion consumes the queue once and commits exact source MP/CD once");
        samples["ordinary_completion"]={{"completion_tick",completed},{"release_tick",released},{"cost",cost.json()},{"events",eventSignature(world)}};
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);ground(world);const int index=defaultIndex(world);
        int other=-1;for(size_t n=0;n<world.skills.size();++n)if(int(n)!=index&&!world.skills[n].airOnly&&!world.skills[n].continuation) {other=int(n);break;}
        check(other>=0,"A distinct implemented source skill supplies the active-action completion fixture");
        press(world,20+other);const int mp=world.player.mp;press(world,6);
        check(world.activeSkill()==other&&world.hasBufferedDefaultSkill()&&world.player.mp==mp,
            "Default Z also waits for a different live skill instead of cancelling its action");
        for(size_t tick=0;tick<240&&world.activeSkill()!=index;++tick)world.advanceSingleTick();
        check(world.activeSkill()==index&&!world.hasBufferedDefaultSkill(),"Natural skill completion releases the owned default Z request");
        samples["skill_completion"]=eventSignature(world);
    }
    for(const auto &reason:{std::string("mp"),std::string("cooldown"),std::string("level")}) {
        World reference(pvf,assets,WorldRules::BetaFoundationV1),world(pvf,assets,WorldRules::BetaFoundationV1);
        ground(reference);ground(world);const int index=defaultIndex(world);press(reference,4);press(world,4);
        if(reason=="mp")world.player.mp=0;
        if(reason=="cooldown")world.skillState().startCooldown(world.skills[index].identity(),world.nowMs(),60000);
        if(reason=="level")world.skills[index].level=0;
        const int mp=world.player.mp;const auto animation=world.player.animation;const auto start=world.player.animStart;
        reference.advanceSingleTick();press(world,6);
        check(!world.hasBufferedDefaultSkill()&&world.activeSkill()<0&&world.player.mp==mp&&
            world.player.skillFailureFeedback.startedMs==world.nowMs(),"Ineligible default Z rejects at admission and creates presentation feedback: "+reason);
        check(world.player.x==reference.player.x&&world.player.y==reference.player.y&&world.player.z==reference.player.z&&
            world.player.animation==animation&&world.player.animStart==start&&
            world.snapshot().at("player_animation_ms")==reference.snapshot().at("player_animation_ms"),
            "Failure feedback changes neither world position nor the advancing source animation clock: "+reason);
        check(world.player.skillFailureFeedback.offsetX(world.nowMs())==2&&world.player.skillFailureFeedback.offsetX(world.nowMs()+20)==-2&&
            world.player.skillFailureFeedback.offsetX(world.nowMs()+120)==0,"The named 2-pixel/120-ms presentation policy has bounded deterministic expiry: "+reason);
        samples["admission_rejection"][reason]=world.skillInputDiagnostics();
    }
    for(const auto &reason:{std::string("mp"),std::string("cooldown"),std::string("level"),std::string("air")}) {
        World world(pvf,assets,WorldRules::BetaFoundationV1);ground(world);const int index=defaultIndex(world);queueZ(world);
        check(world.hasBufferedDefaultSkill(),"Release qualification fixture admitted a legal owned request: "+reason);
        if(reason=="mp")world.player.mp=0;
        if(reason=="cooldown")world.skillState().startCooldown(world.skills[index].identity(),world.nowMs(),60000);
        if(reason=="level")world.skills[index].level=0;
        if(reason=="air")world.player.z=world.player.pz=1000;
        const int mp=world.player.mp;
        for(size_t tick=0;tick<240&&world.hasBufferedDefaultSkill();++tick)world.advanceSingleTick();
        check(!world.hasBufferedDefaultSkill()&&world.activeSkill()!=index&&world.player.mp==mp&&
            world.player.skillFailureFeedback.startedMs>=0,"Actual release checks current MP/CD/level/air and consumes a rejected queue once: "+reason);
        samples["release_rejection"][reason]=world.skillInputDiagnostics();
    }
    for(const auto &cleanup:{std::string("release_inputs"),std::string("scene"),std::string("identity"),std::string("cancel"),std::string("stun")}) {
        World world(pvf,assets,WorldRules::BetaFoundationV1);ground(world);const int index=defaultIndex(world);queueZ(world);
        if(cleanup=="release_inputs")world.releaseInputs();
        if(cleanup=="scene")world.changeScene();
        if(cleanup=="identity")world.selectCharacter({});
        if(cleanup=="cancel")world.idle();
        if(cleanup=="stun"){world.player.stunUntil=world.nowMs()+100;world.advanceSingleTick();}
        const auto mark=world.events.size();
        check(!world.hasBufferedDefaultSkill(),"Transient Z ownership is cleared at cleanup: "+cleanup);
        for(size_t tick=0;tick<120;++tick)world.advanceSingleTick();
        bool replay=false;for(size_t n=mark;n<world.events.size();++n)replay|=world.events[n].kind=="skill_cost"&&world.events[n].name==world.skills[index].key;
        check(!replay,"Cancelled default Z cannot replay after its old animation or recovery finishes: "+cleanup);
    }
    {
        World world(pvf,assets);ground(world);queueZ(world);
        Effect stone;stone.hostile=true;stone.x=stone.px=world.player.x;stone.y=stone.py=world.player.y;stone.z=50;stone.dir=-1;stone.expires=world.nowMs()+1000;
        world.effects.push_back(stone);const int hp=world.player.hp;world.advanceSingleTick();
        check(world.player.hp<hp&&!world.hasBufferedDefaultSkill()&&world.player.animation=="damage1",
            "An accepted hostile hit really interrupts the ordinary action and cancels the queued Z");
        World death(pvf,assets);ground(death);queueZ(death);death.player.hp=1;
        stone.x=stone.px=death.player.x;stone.y=stone.py=death.player.y;stone.expires=death.nowMs()+1000;death.effects.push_back(stone);death.advanceSingleTick();
        check(death.player.dead&&!death.hasBufferedDefaultSkill()&&death.player.skillFailureFeedback.startedMs<0,
            "Lethal incoming contact clears buffered Z and transient failure presentation");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);ground(world);const int index=defaultIndex(world);queueZ(world);
        int other=-1;for(size_t n=0;n<world.skills.size();++n)if(int(n)!=index&&!world.skills[n].airOnly&&!world.skills[n].continuation) {other=int(n);break;}
        press(world,20+other);
        check(world.activeSkill()==other&&!world.hasBufferedDefaultSkill(),"A newly accepted replacement action retires the old action's default Z queue");
        for(size_t tick=0;tick<240;++tick)world.advanceSingleTick();
        check(costsFor(world,world.skills[index].id)==0,"Old Z never crosses into replacement action completion");
    }
    {
        const auto reference=scheduled(pvf,assets,60);
        check(scheduled(pvf,assets,30)==reference&&scheduled(pvf,assets,144)==reference&&scheduled(pvf,assets,60,true)==reference,
            "Real scheduled X/Z input produces identical action/payment/cooldown results at 30/60/144 rendering partitions and catch-up debt");
        samples["render_partition_equivalence"]=reference;
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);ground(world);queueZ(world);
        const auto saved=world.simulationCheckpoint();
        check(saved.dump().find(UserRequestedSkillFeedbackV1::bufferPolicy)==std::string::npos&&
            saved.dump().find("skillFailureFeedback")==std::string::npos,"Z and presentation fields are absent from the persistent simulation codec");
        world.restoreSimulationCheckpoint(saved);
        check(!world.hasBufferedDefaultSkill()&&world.player.skillFailureFeedback.startedMs<0,
            "Actual checkpoint restore clears transient Z and presentation rather than replaying them");
    }
    {
        CharacterCatalog catalog(pvf);RegionCatalog regions(pvf,assets);World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        const auto root=std::filesystem::absolute(std::filesystem::path("cache")/"skill-input-feedback-tests"/
            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        CharacterStore store(root);Progression progression(regions);const int job=1;
        store.data["characters"][0]={{"name","SourceZBufferTest"},{"class",std::filesystem::u8path(catalog.at(job).registration.path).stem().u8string()},
            {"identity",CharacterIdentity{job,0,0}.json()},{"level",1},{"skill_initialization","source-v1"}};
        store.apply(0,world,progression);dnf::enterExplicitSkillPreviewFixture(world);ground(world);auto &runtime=*world.experimentalRuntime();const auto &plan=runtime.plan();
        const ExperimentalSkillRow *selected=nullptr;
        for(const auto &row:plan.skills)if(row.second.data&&sourceBaseDefaultSkillCommand(*row.second.data,0))selected=&row.second;
        check(selected!=nullptr,"Actual created Fighter has a source-defined unconditional default Z skill");
        runtime.configuration().clearSkillBinding(selected->key);
        press(world,6);
        check(!runtime.attacking()&&world.player.skillFailureFeedback.startedMs>=0,"Experimental default Z retains the manual source-binding gate and shows a real failure cue");
        const auto slots=runtime.configuration().slots();runtime.configuration().configureBasicAttackTemplate(selected->key,1,plan);
        world.releaseInputs();const int mp=world.player.mp;queueZ(world);
        check(!runtime.snapshotDiagnostics().at("buffered_default_skill").is_null()&&world.player.mp==mp,
            "Actual experimental World input queues source default Z behind its live same-job action without payment");
        const auto sequence=runtime.snapshotDiagnostics().at("action_sequence").get<uint64_t>();
        for(size_t tick=0;tick<180&&runtime.snapshotDiagnostics().at("action_sequence")==sequence;++tick)world.advanceSingleTick();
        check(runtime.snapshotDiagnostics().at("action_sequence").get<uint64_t>()==sequence+1&&runtime.attacking()&&world.player.mp<mp&&
            runtime.remainingCooldown(selected->key,world.nowMs())>0&&runtime.configuration().slots()==slots,
            "Experimental completion releases once through source MP/CD and starts a real new pose without assigning a user slot");
        check(world.player.poseFrame==0&&world.player.animStart==world.nowMs(),"Experimental source completion publishes the new skill's first pose in the same tick");
        samples["experimental_completion"]={{"diagnostics",world.experimentalDiagnostics()},{"feedback",world.skillInputDiagnostics()}};
        // External prepare/publish counters prove the shared Squirrel gate is
        // reached at actual release, never speculative buffer admission.
        struct CounterAction final:PreparedExperimentalSkillAction {
            int &counter;explicit CounterAction(int &value):counter(value){}void publish() noexcept override{++counter;}
        };
        const auto planCopy=std::make_shared<ExperimentalCharacterPlan>(plan);ExperimentalCharacterRuntime probe(planCopy);
        probe.configuration().configureBasicAttackTemplate(selected->key,1,*planCopy);
        ExperimentalActorState actor;actor.mp=world.player.maxMp;
        const auto *weapon=progression.item(progression.state.at("experimental_starter").at("equipment_id").get<int>());
        check(weapon!=nullptr,"Shared release gate test keeps the actual qualified source weapon subtype");
        actor.weaponSubtype=int(weapon->source.number("[sub type]",-1));int prepares=0,publishes=0;
        const ExperimentalSkillActionGate gate=[&](const ExperimentalSkillActionRequest &request)->std::unique_ptr<PreparedExperimentalSkillAction> {
            check(request.key==selected->key&&request.actionSequence==2,"Deferred source callback owns the new action identity");
            ++prepares;return std::make_unique<CounterAction>(publishes);
        };
        CharacterActionRequest basic;basic.action=CharacterAction::BasicAttack;basic.inputKey=4;basic.inputDown=true;
        probe.request(basic);actor=probe.advance(1,actor,[](double,double){return true;},gate).actor;
        CharacterActionRequest z;z.action=CharacterAction::CommandInput;z.inputKey=6;z.inputDown=true;
        probe.request(z);actor=probe.advance(2,actor,[](double,double){return true;},gate).actor;
        check(prepares==0&&publishes==0&&!probe.snapshotDiagnostics().at("buffered_default_skill").is_null(),
            "Owned source queue admission neither prepares nor publishes a script callback");
        for(uint64_t tick=3;tick<180&&!prepares;++tick) {
            auto out=probe.advance(tick,actor,[](double,double){return true;},gate);actor=out.actor;
            if(out.preparedSkillAction)out.preparedSkillAction->publish();
        }
        check(prepares==1&&publishes==1,"Natural completion reaches the shared source script gate exactly once before external publication");
        ExperimentalCharacterRuntime revoked(planCopy);revoked.configuration().configureBasicAttackTemplate(selected->key,1,*planCopy);
        actor={};actor.mp=world.player.maxMp;actor.weaponSubtype=int(weapon->source.number("[sub type]",-1));const int revocationMp=actor.mp;
        revoked.request(basic);actor=revoked.advance(1,actor,[](double,double){return true;}).actor;
        revoked.request(z);actor=revoked.advance(2,actor,[](double,double){return true;}).actor;
        revoked.configuration().clearSkillBinding(selected->key);bool rejection=false;
        for(uint64_t tick=3;tick<180&&revoked.attacking();++tick) {
            const auto out=revoked.advance(tick,actor,[](double,double){return true;});actor=out.actor;
            for(const auto &diagnostic:out.diagnostics)rejection|=diagnostic.at("code")=="manual_source_binding_required";
        }
        check(rejection&&actor.mp==revocationMp&&revoked.remainingCooldown(selected->key,3000)==0&&
            revoked.snapshotDiagnostics().at("buffered_default_skill").is_null(),
            "Experimental release rechecks the selected source binding and consumes a revoked request without payment");
    }
    return {{"status","pass"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"scope","Actual World queued input, source action completion, MP/CD/level/air rejection and lifecycle; renderer offset is a user-requested presentation policy"},
        {"frontend_started",false},{"native_dynamic_comparison","pending_user"}};
}
} // namespace dnf
