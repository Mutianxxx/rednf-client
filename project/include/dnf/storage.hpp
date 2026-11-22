#pragma once
#include "combat.hpp"
#include "progression.hpp"
#include <functional>
#include <future>
#include <memory>
#include <mutex>
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
    std::future<void> checkpointWrite_;
    // 后台检查点在飞行期间冻结的唯一输入。候选根的校验/迁移/序列化/校验和
    // 全部在写线程完成，主线程只付出一次深拷贝。
    struct FrozenCheckpoint {
        Json base;
        Json previousMetadata;
        uint64_t generation = 0;
    };
    // 上一代已发布根与飞行中的冻结根都由写线程释放，避免 accept 帧回收
    // 整棵 JSON 树（真实存档可达数 MB）。
    Json retired_;
    std::mutex handoffMutex_;
    Json preparedHandoff_;
    void requireWriter() const;
    static Json buildCandidate(const Json &base, const Json &previousMetadata, uint64_t generation,
                               CommitKind kind, const std::string &requestId,
                               const std::string &contentIdentity);
    bool completeCheckpoint();
    Json acceptPreparedSnapshot(Json prepared);
    Json prepareCommit(CommitKind kind, const std::string &requestId);
    Json publishPending();
    static void writePendingSnapshot(const Json &pending_, const std::filesystem::path &directory_,
                                     const std::string &contentIdentity_,
                                     const std::function<void(SaveFailurePoint)> &failureInjector_);
    Json acceptPendingSnapshot();
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
    // 后台只写冻结快照；候选构建/校验/序列化都在写线程完成。主线程轮询
    // 只做 accept 发布与失败上报。
    bool pollCheckpoint();
    // 退出边界等待磁盘结果，失败向调用方传播，成功才发布代次。
    void finishCheckpoint();
    bool checkpointInFlight() const noexcept { return checkpointWrite_.valid(); }
    // 冻结当前根并启动一次后台 checkpoint（候选构建也在写线程）。已有飞行中的
    // 写入或失败候选时返回 false，且完全不改动 data。
    bool beginCheckpoint();
    void save();
    // The caller must check receipt() before executing a retried command.
    // commit() freezes the whole root, including progression, region_session,
    // simulation/RNG/pending fields, and records the receipt in that same root.
    // Stable business receipts are retained across checkpoints and restarts.
    // Neither this API nor save() executes or rolls back the caller's command.
    Json commit(const std::string &requestId);
    Json retryPending();
    Json receipt(const std::string &requestId) const;
    // 后台写入进行中也算“未完成的提交”：业务/关闭/换 writer 一律拒绝，
    // 但候选尚未冻结完成，不能当作可重试候选。
    bool hasPendingCommit() const { return !pending_.is_null() || checkpointWrite_.valid(); }
    uint64_t generation() const { return generation_; }
    const std::string &contentIdentity() const { return contentIdentity_; }
    // Durable writer provenance. These never expose the mutable candidate root.
    const std::filesystem::path &directory() const noexcept { return directory_; }
    const Json &committedSnapshot() const noexcept { return committed_; }
    void setFailureInjector(std::function<void(SaveFailurePoint)> injector) {
        if (checkpointInFlight()) throw std::runtime_error("Checkpoint disk write is still active");
        failureInjector_ = std::move(injector);
    }
    void apply(int slot, World &world) const;
    void capture(int slot, const World &world);
    void apply(int slot, World &world, Progression &progression) const;
    void capture(int slot, const World &world, const Progression &progression);
};
void atomicJson(const std::filesystem::path &path, const Json &data);
} // namespace dnf
