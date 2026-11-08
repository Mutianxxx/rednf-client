#include "explicit_skill_preview_fixture.hpp"
#include "dnf/squirrel_action_service.hpp"
#include <algorithm>
#include <stdexcept>
#include <thread>

namespace dnf {
namespace {
size_t ancientSounds(const World &world) {
    return size_t(std::count_if(world.events.begin(),world.events.end(),[](const Event &event){return event.kind=="sound"&&event.name=="MW_ANCIENT";}));
}
void setup(World &world,const std::string &staticIdentity) {
    world.configureSquirrelActions(staticIdentity);world.enableExperimentalCharacters();world.selectCharacter({8,0,0});dnf::enterExplicitSkillPreviewFixture(world);
    world.combat=false;world.freezeAi=true;world.mapWidth=1200;world.walkRects={{0,185,1200,240}};
    world.player.x=world.player.px=560;world.player.y=world.player.py=300;world.player.dir=1;world.player.mp=100000;
    auto &runtime=*world.experimentalRuntime();
    runtime.configuration().configureBasicAttackTemplate({8,176},1,runtime.plan());
    runtime.configuration().assignSlot(0,SkillKey{8,176},runtime.plan());
}
ExperimentalSkillActionRequest request(const World &world,uint64_t attempt=1,uint64_t sequence=1) {
    const auto &runtime=*world.experimentalRuntime();const auto &row=runtime.plan().skills.at({8,176});
    return {{8,176},row.source,runtime.configuration().binding({8,176})->motion.source,uint64_t(world.tick),sequence,attempt};
}
} // namespace

// DRAFT: no compilation or execution has been performed in this child scope.
// These are World/value transaction checks, not native Buff stat or audio/device
// comparison. Literal IDs here are hash-bound source fixtures only.
Json runSquirrelActionServiceTests(Pvf &pvf,Assets &assets,const std::string &staticIdentity) {
    Json checks=Json::array(),samples=Json::object();
    const auto check=[&](bool okay,const std::string &name){if(!okay)throw std::runtime_error("Squirrel action service: "+name);checks.push_back(name);};
    const auto rejects=[](auto callback){try{callback();}catch(const std::exception &){return true;}return false;};
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);setup(world,staticIdentity);
        SquirrelActionService service(world,pvf,assets,staticIdentity);
        const auto before=world.eventLog();const auto resources=world.player.mp;
        auto token=service.prepare(request(world));
        check(bool(token)&&world.eventLog()==before&&world.player.mp==resources,
            "Actual Buff VM source callback prepares its complete audio batch without World event/resource publication");
        check(rejects([&]{service.prepare(request(world));})&&world.eventLog()==before,
            "The same fixed-tick/attempt pair is rejected without replaying the callback sound");
        token.reset();
        check(!service.diagnostics().at("active").get<bool>()&&world.eventLog()==before,
            "Discarding an unaccepted prepared action closes the VM and drops every staged sound");
        auto foreign=request(world,2);foreign.skillSource.memberSha256=std::string(64,'0');
        check(rejects([&]{service.prepare(foreign);})&&world.eventLog()==before,
            "Changed SKL receipt rejects before callback/resource publication");
        foreign=request(world,3);foreign.motionSource.packageIdentity="foreign-pvf";
        check(rejects([&]{service.prepare(foreign);})&&world.eventLog()==before,
            "Foreign CHR motion identity rejects before callback/resource publication");
        auto later=service.prepare(request(world,4));service.cancel("scene_change");later->publish();later->publish();
        check(world.eventLog()==before&&!service.diagnostics().at("active").get<bool>()&&service.diagnostics().at("discarded_preparations")==1,
            "Lifecycle cancellation invalidates even an unpublished token; late/repeated publish cannot resurrect it");
        bool wrongThreadRejected=false;std::thread worker([&]{wrongThreadRejected=rejects([&]{service.prepare(request(world,5));});});worker.join();
        check(wrongThreadRejected&&world.eventLog()==before,"Foreign simulation thread cannot prepare a live World callback");
        samples["deferred"]=service.diagnostics();
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);setup(world,staticIdentity);
        auto &runtime=*world.experimentalRuntime();
        const auto good=world.characterAppearance();auto broken=good;broken.bodyMotions.clear();world.setCharacterAppearance(std::move(broken));
        const auto mp=world.player.mp;const auto events=world.events.size();const auto rng=world.randomStreams().snapshot();
        world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        check(world.player.mp==mp&&runtime.remainingCooldown({8,176},world.nowMs())==0&&!runtime.attacking()&&
              std::none_of(world.events.begin()+std::ptrdiff_t(events),world.events.end(),[](const Event &event){return event.kind=="sound";})&&
              world.randomStreams().snapshot()==rng&&world.squirrelActionDiagnostics().at("commits")==0,
            "Late CHR/EQU preflight failure discards an already prepared real Buff callback without cost, cooldown, RNG or audio publication");
        world.setCharacterAppearance(good);world.releaseInputs();world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        check(world.player.mp<mp&&ancientSounds(world)==1&&world.squirrelActionDiagnostics().at("commits")==1,
            "After late source failure, a new explicit request on a later tick executes once; discarded candidate attempt counters do not poison recovery");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);setup(world,staticIdentity);
        const auto learning=world.skillState().snapshot(world.nowMs()),overlay=world.skillTestOverlay().snapshot();
        const auto mp=world.player.mp;world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        const auto accepted=world.squirrelActionDiagnostics();
        check(ancientSounds(world)==1&&accepted.at("commits")==1&&accepted.at("active").get<bool>()&&world.player.mp<mp,
            "Real World input->experimental start->source Buff callback publishes exactly one audio event with MP/CD transaction");
        check(world.skillState().snapshot(world.nowMs())==learning&&world.skillTestOverlay().snapshot()==overlay,
            "User experiment callback never purchases or grants normal learned levels/test overlays");
        check(accepted.at("route").at("job_id")==8&&accepted.at("route").at("state")==17&&
              accepted.at("active_receipt").at("vm_policy")==squirrel_stage::vmPolicyId&&
              accepted.at("active_receipt").at("static_identity")==staticIdentity&&
              !accepted.at("full_skill_complete").get<bool>(),
            "Live receipt retains source registration/enum/policy/static identity and explicit incomplete Buff semantics");
        const auto sounds=ancientSounds(world);world.advance(0);
        check(ancientSounds(world)==sounds&&world.squirrelActionDiagnostics().at("commits")==1,
            "A zero-time/paused boundary does not invoke the source state callback again");
        world.player.hitStopTicks=3;world.advanceSingleTick();
        check(ancientSounds(world)==sounds&&world.squirrelActionDiagnostics().at("active").get<bool>(),
            "Hitstop keeps the accepted instance without advancing/replaying its source callback");
        world.player.hitStopTicks=0;world.player.hitStopped=false;world.player.stunUntil=world.nowMs()+1000;world.advanceSingleTick();
        check(!world.squirrelActionDiagnostics().at("active").get<bool>()&&ancientSounds(world)==sounds,
            "The runtime's actual blocked/reaction transition cleans the owning callback without retracting committed sounds");
        samples["accepted"]=accepted;
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);setup(world,staticIdentity);
        world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        const auto sounds=ancientSounds(world);world.changeScene();
        check(!world.squirrelActionDiagnostics().at("active").get<bool>()&&ancientSounds(world)==sounds,
            "Real scene change clears callback VM/owned pending work while retaining already committed events");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);setup(world,staticIdentity);
        world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();
        world.player.dead=true;world.player.life=ActorLife::Dying;world.advanceSingleTick();
        check(!world.squirrelActionDiagnostics().at("active").get<bool>(),
            "Death lifecycle fixture cleans the active callback and cannot replay it on the next tick");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);setup(world,staticIdentity);
        world.enqueue({world.simulationNanoseconds(),20,true});world.advanceSingleTick();world.selectCharacter({});
        check(!world.squirrelActionDiagnostics().at("active").get<bool>(),"Real character selection cleans the previous callback owner");
    }
    {
        World world(pvf,assets,WorldRules::BetaFoundationV1);setup(world,staticIdentity);
        auto plan=std::make_shared<ExperimentalCharacterPlan>(world.experimentalRuntime()->plan());
        ExperimentalCharacterRuntime runtime(plan);runtime.configuration()=world.experimentalRuntime()->configuration();
        CharacterActionRequest input;input.action=CharacterAction::Skill;input.skill=SkillKey{8,176};input.inputDown=true;runtime.request(input);
        ExperimentalActorState actor;actor.mp=100000;
        const auto out=runtime.advance(1,actor,[](double,double){return true;},[](const ExperimentalSkillActionRequest &)->std::unique_ptr<PreparedExperimentalSkillAction>{
            throw std::runtime_error("fixture source callback/native API unavailable");
        });
        check(out.actor.mp==actor.mp&&runtime.remainingCooldown({8,176},16)==0&&!runtime.attacking()&&!out.preparedSkillAction,
            "Source gate rejection at the actual start boundary spends no MP, starts no cooldown and publishes no action");
        check(std::any_of(out.diagnostics.begin(),out.diagnostics.end(),[](const Json &d){return d.value("code",std::string())=="experimental_skill_source_blocked";}),
            "Missing/faulting source callback is visible as a specific skill-start diagnostic");
    }
    return {{"passed",true},{"checks",checks},{"samples",samples},{"full_skill_complete",false},
        {"native_dispatch_proven",false},{"frontend_started",false},{"audio_device_tested",false}};
}
} // namespace dnf
