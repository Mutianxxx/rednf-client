#pragma once
#include "combat.hpp"
#include "progression.hpp"
#include <functional>
namespace dnf {
// Injection points surround actual disk operations. Intended for isolated
// storage tests; throwing retains the exact pending candidate for retry.
enum class SaveFailurePoint { BeforeWrite, AfterWrite, AfterFlush, AfterValidation, AfterBackup, BeforePublish, AfterPublish };
// Unknown JSON fields survive upgrades. Paths are explicit so tests never use player saves.
class CharacterStore {
    struct WriterLock;
    enum class CommitKind { Checkpoint, Business };
    std::filesystem::path directory_;
    std::unique_ptr<WriterLock> writer_;
    std::string contentIdentity_;
    uint64_t generation_ = 0;
    Json committed_, pending_;
    std::function<void(SaveFailurePoint)> failureInjector_;
    bool closed_ = false;
    void requireWriter() const;
    Json prepareCommit(CommitKind kind, const std::string &requestId);
    Json publishPending();
    void applyPreparedAppearance(int slot, World &, const CharacterAppearance *) const;
  public:
    Json data, warnings = Json::array();
    explicit CharacterStore(std::filesystem::path directory, std::string contentIdentity = {},
                            bool allowLegacyImport = false);
    ~CharacterStore();
    CharacterStore(const CharacterStore &) = delete;
    CharacterStore &operator=(const CharacterStore &) = delete;
    // Releasing a writer is explicit. A closed store remains readable; it
    // cannot capture or save. Pending failed commits must be retried first.
    void close();
    // Full atomic snapshot without allocating a permanent business receipt.
    // A failed checkpoint can be retried here or through retryPending().
    Json checkpoint();
    void save();
    // The caller must check receipt() before executing a retried command.
    // commit() freezes the whole root, including progression, region_session,
    // simulation/RNG/pending fields, and records the receipt in that same root.
    // Stable business receipts are retained across checkpoints and restarts.
    // Neither this API nor save() executes or rolls back the caller's command.
    Json commit(const std::string &requestId);
    Json retryPending();
    Json receipt(const std::string &requestId) const;
    bool hasPendingCommit() const { return !pending_.is_null(); }
    uint64_t generation() const { return generation_; }
    const std::string &contentIdentity() const { return contentIdentity_; }
    // Durable writer provenance. These never expose the mutable candidate root.
    const std::filesystem::path &directory() const noexcept { return directory_; }
    const Json &committedSnapshot() const noexcept { return committed_; }
    void setFailureInjector(std::function<void(SaveFailurePoint)> injector) { failureInjector_ = std::move(injector); }
    void apply(int slot, World &world) const;
    void capture(int slot, const World &world);
    void apply(int slot, World &world, Progression &progression) const;
    void capture(int slot, const World &world, const Progression &progression);
};
void atomicJson(const std::filesystem::path &path, const Json &data);
} // namespace dnf
