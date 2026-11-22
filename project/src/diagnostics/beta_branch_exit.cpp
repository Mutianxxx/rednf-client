#include "dnf/beta_branch_exit.hpp"
#include "dnf/beta_branch.hpp"
#include "dnf/pending_rewards.hpp"
#include <limits>
#include <stdexcept>

namespace dnf {
Json BetaBranchExitResult::json() const {
    return {{"ok",ok},{"stage",stage},{"error",error},
        {"reset_request_id",resetRequestId},{"reset_receipt",resetReceipt}};
}
BetaBranchExitResult leaveBetaSaveBranch(BetaSaveBranch &branch,CharacterStore &normal,
    PendingRewardService &rewards,Progression &progress,World &world,DebugService &debug,
    DebugContext context,uint64_t &debugGeneration,int slot,const std::function<bool()> &persist) {
    BetaBranchExitResult result;
    try {
        result.stage="precondition";
        if(!branch.active())throw std::runtime_error("No active beta branch to leave");
        if(branch.select(normal).hasPendingCommit()||rewards.blocked(progress))
            throw std::runtime_error("Complete the pending beta save and rewards before leaving");
        if(!context.target.valid()||context.target.generation!=debugGeneration||context.normalLevel<1)
            throw std::runtime_error("Leaving beta requires the application's current valid debug target");
        if(debugGeneration==std::numeric_limits<uint64_t>::max())
            throw std::overflow_error("Debug target generation exhausted");
        if(!persist)throw std::invalid_argument("Beta exit requires the application's persist consumer");

        // Leaving cancels queued management intent instead of executing a
        // queued identity/unlock handler which could save or yield before Reset.
        // This consumes normal Rejected receipts, including a full old queue.
        ++debugGeneration;context.target.generation=debugGeneration;context.simulationPaused=true;
        auto obsolete=context;obsolete.target=DebugTarget{};
        result.stage="reject_old_commands";
        debug.applyAtBoundary(world,obsolete);
        if(debug.snapshot().pendingCount!=0)
            throw std::runtime_error("Old debug commands remain queued while leaving beta");

        result.stage="reset";
        const DebugCommand reset{debug.nextRequestId(),context.target,DebugCommandKind::Reset,Json()};
        result.resetRequestId=reset.requestId;
        const auto submitted=debug.submit(reset);
        if(submitted.state!=DebugResultState::Accepted) {
            result.resetReceipt=submitted.json();
            throw std::runtime_error("Beta reset was not accepted: "+submitted.reason);
        }
        debug.applyAtBoundary(world,context);
        const auto applied=debug.submit(reset); // Read the exact receipt; never re-executes.
        result.resetReceipt=applied.json();
        if(applied.state!=DebugResultState::Applied||debug.snapshot().pendingCount!=0||
            !(world.debugOverrides()==DebugOverrides{})||debug.pauseRequested()||debug.snapshot().singleStepRequests!=0)
            throw std::runtime_error("Beta reset did not complete: "+applied.reason);
        world.refreshExplorationMonsterEventAiTestPolicy();debug.refresh(world,context);

        result.stage="checkpoint";
        if(!persist())throw std::runtime_error("Beta checkpoint did not complete; retain and retry the current save");
        auto &writer=branch.select(normal);
        if(writer.hasPendingCommit()||!rewards.acknowledgeCheckpoint(progress,world,writer,slot))
            throw std::runtime_error("Beta checkpoint proof failed: "+rewards.diagnostic().dump());

        result.stage="release_writer";
        if(!rewards.releaseCheckpointWriter(progress,writer,slot))
            throw std::runtime_error("Beta writer release failed: "+rewards.diagnostic().dump());
        result.stage="close_branch";
        branch.close();
        result.ok=true;result.stage="completed";
    }catch(const std::exception &error) {result.error=error.what();}
    catch(...) {result.error="Unknown beta-exit failure; current branch retained";}
    return result;
}
} // namespace dnf
