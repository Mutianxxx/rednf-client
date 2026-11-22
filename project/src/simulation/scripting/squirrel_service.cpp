#include "dnf/squirrel_action_service.hpp"
#include <stdexcept>

namespace dnf {
void World::configureSquirrelActions(std::string staticIdentity) {
    if(squirrelActions_)throw std::logic_error("World Squirrel actions already configured");
    squirrelActions_=std::make_unique<SquirrelActionService>(*this,pvf_,assets_,std::move(staticIdentity));
}
std::unique_ptr<PreparedExperimentalSkillAction> World::prepareSquirrelAction(const ExperimentalSkillActionRequest &request) {
    return squirrelActions_?squirrelActions_->prepare(request):nullptr;
}
void World::observeSquirrelAction(std::optional<uint64_t> sequence)noexcept {
    if(squirrelActions_)squirrelActions_->observe(sequence);
}
void World::cancelSquirrelActions(const std::string &reason)noexcept {
    if(squirrelActions_)squirrelActions_->cancel(reason);
}
Json World::squirrelActionDiagnostics()const {
    return squirrelActions_?squirrelActions_->diagnostics():Json({{"configured",false},{"full_skill_complete",false}});
}
} // namespace dnf
