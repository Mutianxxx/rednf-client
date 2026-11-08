#include "dnf/beta_branch_exit.hpp"
#include "dnf/beta_branch.hpp"
#include "dnf/pending_rewards.hpp"
#include <array>
#include <chrono>
#include <limits>
#include <stdexcept>

namespace dnf {
namespace {
namespace fs=std::filesystem;
Json initialCharacter() {
    Json root={{"schema",5},{"characters",std::vector<Json>(20,nullptr)}};
    root["characters"][0]={{"name","Beta exit source fixture"},{"class","swordman"},
        {"identity",CharacterIdentity{}.json()},{"level",15},{"weapon",0},
        {"skill_initialization","source-v1"},{"future_character",{{"keep",71}}}};
    return root;
}
}
Json runBetaBranchExitTests(Pvf &pvf,Assets &assets) {
    Json checks=Json::array(),samples=Json::array();
    const auto check=[&](bool okay,const std::string &message) {
        if(!okay)throw std::runtime_error("Beta exit: "+message);checks.push_back(message);
    };
    const auto root=fs::absolute(fs::path("cache/beta-branch-exit-tests")/
        std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    if(normalize(root.root_name().u8string())!="d:")
        throw std::runtime_error("Beta exit tests require a D: working directory");
    RegionCatalog catalog(pvf,assets);
    const std::array<SaveFailurePoint,4> faults={SaveFailurePoint::BeforeWrite,SaveFailurePoint::AfterWrite,
        SaveFailurePoint::BeforePublish,SaveFailurePoint::AfterPublish};
    for(size_t index=0;index<9;++index) {
        const auto directory=root/("case-"+std::to_string(index));
        CharacterStore normal(directory/"normal",pvf.identity());normal.data=initialCharacter();
        World world(pvf,assets,WorldRules::BetaFoundationV1);world.enableExperimentalCharacters();
        Progression progress(catalog);normal.apply(0,world,progress);world.combat=false;world.releaseInputs();
        PendingRewardService rewards;rewards.characterBoundary(world);
        const auto save=[&](CharacterStore &writer) {
            writer.capture(0,world,progress);
            writer.data["characters"][0]["region_session"]=RegionSession{}.save(world,"town");
            writer.save();return rewards.acknowledgeCheckpoint(progress,world,writer,0);
        };
        check(save(normal),"Normal source writer acknowledged before beta fork "+std::to_string(index));
        BetaSaveBranch branch;branch.fork(normal,directory/"beta",{{"run_id","beta-exit-fixture"}});
        check(rewards.switchCheckpointWriter(progress,world,branch.select(normal),0),
            "Actual beta writer handover before leave "+std::to_string(index));
        const auto normalBytes=readFile(directory/"normal/characters.json");const auto normalData=normal.data;
        auto &writer=branch.select(normal);
        // Concrete branch-only extension represents earned/unknown business
        // state. Exit must preserve this along with real progression/RNG and
        // the actual normal paid-skill ledger; it may only disable overrides.
        progress.state["beta_exit_preserved"]={{"value",71},{"reward_extension",Json::array({2,5,9})}};
        const SkillLearningRequest request{"beta-exit-paid-upper",{0,46},0,2};
        const auto bought=world.skillLearning().prepare(world.skillState(),15,
            world.runtimeSkillPolicy(request.key),request,world.nowMs());
        check(bought.ok,"Actual source learning prepared in isolated beta "+std::to_string(index));
        world.publishSkillLedger(bought.state);world.skillState().startCooldown({0,46},world.nowMs(),1700);
        world.randomStreams().stream(RandomDomain::Loot,811).next();
        uint64_t generation=1;
        DebugContext context{{pvf.identity(),writer.data.at("characters")[0].at("uuid").get<std::string>(),"town",generation},15,true};
        DebugService debug;debug.refresh(world,context);
        const auto apply=[&](DebugCommandKind kind,Json payload=Json()) {
            const DebugCommand command{debug.nextRequestId(),context.target,kind,std::move(payload)};
            debug.submit(command);debug.applyAtBoundary(world,context);return debug.submit(command);
        };
        check(apply(DebugCommandKind::SetEnabled,true).state==DebugResultState::Applied&&
              apply(DebugCommandKind::SetHpLock,true).state==DebugResultState::Applied&&
              apply(DebugCommandKind::SetLevelOverride,2).state==DebugResultState::Applied&&
              apply(DebugCommandKind::SetSimulationPaused,true).state==DebugResultState::Applied&&
              apply(DebugCommandKind::SingleStep).state==DebugResultState::Applied,
            "Real debug overrides pause and unconsumed step exist before leave "+std::to_string(index));
        world.enqueue({world.simulationNanoseconds(),0,true});
        check(save(writer),"Beta mutable progression and input snapshot durably saved before leave "+std::to_string(index));
        const auto betaGeneration=writer.generation();
        const auto frozenSimulation=world.simulationCheckpoint();
        const auto frozenSkills=world.skillState().snapshot(world.nowMs());
        const auto frozenTest=world.testSkillConfigurationSnapshot(),frozenManual=world.manualSkillPreviewSnapshot();
        int applicationCalls=0,persistCalls=0;
        debug.setApplicationCommandHandler([&](World &,const DebugCommand &) -> Json {
            ++applicationCalls;
            throw std::runtime_error("Queued application handler must never execute while leaving beta");
        });
        const DebugCommand queuedOne{debug.nextRequestId(),context.target,DebugCommandKind::UnlockExecutableSkills,Json()};
        const DebugCommand queuedTwo{debug.nextRequestId(),context.target,DebugCommandKind::UnlockExecutableSkills,Json()};
        debug.submit(queuedOne);debug.submit(queuedTwo);
        // The full-queue case specifically proves Reset is accepted only after
        // old commands have actual Rejected receipts, not blindly appended.
        if(index==5)for(size_t i=0;i<126;++i)
            debug.submit({debug.nextRequestId(),context.target,DebugCommandKind::SetHpLock,true});
        const auto persist=[&] {
            ++persistCalls;
            if(index==6)throw std::runtime_error("Injected application persist exception");
            if(index==7)return true; // Deliberate dishonest hook: actual proof must reject it below.
            return save(branch.select(normal));
        };
        if(index<4)writer.setFailureInjector([point=faults[index]](SaveFailurePoint at) {
            if(at==point)throw std::runtime_error("Injected beta leave checkpoint fault");
        });
        if(index==7)progress.state["post_checkpoint_mutation"]=71;
        const auto expectedProgress=progress.state;
        if(index==8)rewards.captureFailure("Injected pending uncaptured reward before leave");
        bool selected=false;
        const auto result=leaveBetaSaveBranch(branch,normal,rewards,progress,world,debug,context,generation,0,persist);
        if(result.ok)selected=true; // Same conditional transition as main; not a full SDL main-loop test.
        if(index<4) {
            check(!selected&&!result.ok&&result.stage=="checkpoint"&&branch.active()&&writer.hasPendingCommit()&&
                  writer.generation()==betaGeneration&&rewards.durableGeneration()==betaGeneration,
                "Actual save fault retains branch writer generation and original pending candidate "+std::to_string(index));
            const auto pending=writer.data;
            check(applicationCalls==0&&persistCalls==1&&debug.submit(queuedOne).state==DebugResultState::Rejected&&
                  debug.submit(queuedTwo).reason=="target_generation_changed"&&debug.snapshot().pendingCount==0&&
                  world.debugOverrides()==DebugOverrides{}&&!debug.pauseRequested()&&!debug.takeSingleStepRequest(),
                "Failed leave still confirms Reset and cancels stale application requests without callback "+std::to_string(index));
            context.target.generation=generation;
            const auto noRecapture=leaveBetaSaveBranch(branch,normal,rewards,progress,world,debug,context,generation,0,persist);
            check(!noRecapture.ok&&noRecapture.stage=="precondition"&&persistCalls==1&&writer.data==pending,
                "Repeated leave refuses an exact pending candidate without capture or generation change "+std::to_string(index));
            writer.setFailureInjector({});writer.retryPending();
            check(rewards.acknowledgeCheckpoint(progress,world,writer,0),
                "Existing real save retry acknowledges original beta exit candidate "+std::to_string(index));
            const auto retried=leaveBetaSaveBranch(branch,normal,rewards,progress,world,debug,context,generation,0,persist);
            check(retried.ok&&!branch.active()&&rewards.durableGeneration()==0&&persistCalls==2,
                "Explicit second leave after retry resets checkpoints and closes once "+std::to_string(index));
            samples.push_back({{"case",index},{"first",result.json()},{"retry",retried.json()}});
        } else if(index==6||index==7||index==8) {
            check(!selected&&!result.ok&&branch.active(),"Application/proof/reward fault never switches to selection "+std::to_string(index));
            if(index==6) {
                check(result.stage=="checkpoint"&&applicationCalls==0&&persistCalls==1&&!writer.hasPendingCommit()&&
                      world.debugOverrides()==DebugOverrides{},"Throwing persist retains clean active beta and disabled overrides");
            } else if(index==7) {
                check(result.stage=="checkpoint"&&applicationCalls==0&&persistCalls==1&&rewards.durableGeneration()==betaGeneration,
                    "True persist return cannot replace actual matching writer checkpoint proof");
            } else {
                check(result.stage=="precondition"&&persistCalls==0&&applicationCalls==0&&world.debugOverrides().enabled&&
                      generation==1,"Pending uncaptured rewards reject leave before reset queue or generation change");
                rewards.characterBoundary(world); // Fixture teardown only, after preserved-state checks.
            }
            writer.setFailureInjector({});check(save(writer),"Retained fixture can explicitly checkpoint for teardown "+std::to_string(index));
            check(rewards.releaseCheckpointWriter(progress,writer,0),"Retained fixture releases only its clean writer "+std::to_string(index));
            branch.close();samples.push_back({{"case",index},{"result",result.json()}});
        } else {
            check(selected&&result.ok&&!branch.active()&&rewards.durableGeneration()==0&&applicationCalls==0&&persistCalls==1,
                "Actual shared leave consumer succeeds with queued application and full-queue cases "+std::to_string(index));
            samples.push_back({{"case",index},{"result",result.json()}});
        }
        check(progress.state==expectedProgress&&world.simulationCheckpoint()==frozenSimulation&&
              world.skillState().snapshot(world.nowMs())==frozenSkills&&
              world.testSkillConfigurationSnapshot()==frozenTest&&world.manualSkillPreviewSnapshot()==frozenManual,
            "Leaving never clears paid ledger progression RNG input sequence or test/manual configuration "+std::to_string(index));
        check(normal.data==normalData&&readFile(directory/"normal/characters.json")==normalBytes,
            "Leave and retry never write isolated beta state to normal memory or disk "+std::to_string(index));
        CharacterStore evidence(directory/"beta",pvf.identity());
        check(evidence.data.at("characters")[0].at("progression")==expectedProgress&&
              evidence.data.at("characters")[0].at("future_character").at("keep")==71,
            "Closed beta checkpoint remains inspectable with preserved progression and extensions "+std::to_string(index));
        evidence.close();normal.close();
    }
    return {{"status","passed"},{"count",checks.size()},{"checks",checks},{"samples",samples},
        {"fixture_directory",root.u8string()},
        {"scope","Actual shared main leave consumer with World/DebugService/BetaSaveBranch/PendingRewardService/CharacterStore and four disk fault points; no SDL main-loop, map traversal or original-client coverage"}};
}
} // namespace dnf
