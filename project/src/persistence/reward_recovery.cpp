#include "dnf/reward_recovery.hpp"
#include <exception>
#include <iostream>
#include <limits>
#include <utility>

namespace dnf {
RewardRecoveryReporter::RewardRecoveryReporter(std::filesystem::path path,
    std::function<void(const std::string &)> fallback)
    : path_(std::move(path)), fallback_(std::move(fallback)) {}
void RewardRecoveryReporter::fallback(const Json &diagnostic,const char *error) const noexcept {
    try {
        const std::string text=std::string("Reward diagnostic report unavailable: ")+error+
            "; original diagnostic: "+diagnostic.dump();
        if(fallback_) { try {fallback_(text);return;}catch(...) {} }
        try {std::cerr<<text<<std::endl;}catch(...) {}
    }catch(...) {
        try {std::cerr<<"Reward diagnostic report unavailable; pending reward state retained"<<std::endl;}catch(...) {}
    }
}
RewardDiagnosticResult RewardRecoveryReporter::publish(const Json &diagnostic) noexcept {
    try {
        auto serialized=diagnostic.dump();
        if(serialized==lastSuccessful_)return RewardDiagnosticResult::Unchanged;
        writeJson(path_,diagnostic);
        // Swapping cannot throw after a successful write. A failed report is
        // never marked successful, so later retries can repair report output.
        lastSuccessful_.swap(serialized);
        return RewardDiagnosticResult::Written;
    }catch(const std::exception &error) {lastSuccessful_.clear();fallback(diagnostic,error.what());}
    catch(...) {lastSuccessful_.clear();fallback(diagnostic,"unknown report output failure");}
    return RewardDiagnosticResult::Unavailable;
}

RewardRecoveryFlow::RewardRecoveryFlow(PendingRewardService &service,Progression &progress,
    World &world,RegionCatalog &catalog)
    : service_(service),progress_(progress),world_(world),catalog_(catalog) {}
void RewardRecoveryFlow::notify(const RewardRecoveryHooks &hooks,const char *error) noexcept {
    try {if(hooks.failure){hooks.failure(error);return;}}catch(...) {}
    try {std::cerr<<"Reward recovery remains blocked: "<<error<<std::endl;}catch(...) {}
}
bool RewardRecoveryFlow::pump(const RewardRecoveryHooks &hooks) {
    try {
        if(hooks.savePending()||!hooks.capture())return false;
        // Intent and the pre-reward RNG must be durable before any draw.
        if(service_.needsCheckpoint()&&!hooks.persist())return false;
        if(service_.hasPending(progress_)) {
            if(!service_.prepareAndPublish(progress_,world_,catalog_)) {notify(hooks,"");return false;}
            if(hooks.afterPublish)hooks.afterPublish();
            if(service_.needsCheckpoint()&&!hooks.persist())return false;
        }
        return !service_.blocked(progress_);
    }catch(const std::exception &error) {notify(hooks,error.what());return false;}
    catch(...) {notify(hooks,"unknown recovery failure");return false;}
}
void RewardRecoveryFlow::deferRetry(uint64_t wallMs) noexcept {
    retryAfter_=wallMs>std::numeric_limits<uint64_t>::max()-1000?
        std::numeric_limits<uint64_t>::max():wallMs+1000;
}
bool RewardRecoveryFlow::tryAutomaticRetry(uint64_t wallMs,bool enabled,const RewardRecoveryHooks &hooks) {
    if(!enabled||!service_.blocked(progress_)||hooks.savePending()||wallMs<retryAfter_)return false;
    deferRetry(wallMs);(void)pump(hooks);return true;
}
bool RewardRecoveryFlow::resultsReady(bool pumpSucceeded,bool savePending,const RegionSession &session) {
    return pumpSucceeded&&!savePending&&!service_.blocked(progress_)&&service_.clearReceipt(progress_,session);
}
bool RewardRecoveryFlow::allowControlledExit(bool autoRun,bool inGame,const RewardRecoveryHooks &hooks) {
    if(autoRun)return true;
    try {
        if(hooks.savePending())return false;
        if(!inGame)return true;
        return hooks.capture()&&hooks.persist();
    }catch(const std::exception &error) {notify(hooks,error.what());return false;}
    catch(...) {notify(hooks,"unknown exit checkpoint failure");return false;}
}
} // namespace dnf
