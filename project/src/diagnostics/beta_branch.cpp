#include "dnf/beta_branch.hpp"
namespace dnf {
void BetaSaveBranch::fork(CharacterStore &normal, const std::filesystem::path &directory, Json metadata) {
    if (active()) return;
    if (normal.hasPendingCommit()) throw std::runtime_error("Retry the normal checkpoint before forking a beta test");
    if (std::filesystem::exists(directory)) throw std::runtime_error("A beta test branch must use a fresh directory");
    if (!metadata.is_object()) throw std::invalid_argument("Beta test branch metadata must be an object");
    // Publish normal state first. Failure leaves no test writer and never
    // silently redirects a pending normal transaction into the test branch.
    normal.save();
    metadata["normal_generation"] = normal.generation();
    metadata["content_identity"] = normal.contentIdentity();
    metadata["kind"] = "isolated-beta-test";
    metadata["merge_into_normal"] = false;
    auto prepared = std::make_unique<CharacterStore>(directory,normal.contentIdentity());
    prepared->data = normal.data;
    prepared->data["beta_branch"] = std::move(metadata);
    prepared->save();
    directory_ = directory;
    store_ = std::move(prepared);
}
void BetaSaveBranch::close() {
    if (store_) store_->close();
    store_.reset();
    directory_.clear();
}
} // namespace dnf
