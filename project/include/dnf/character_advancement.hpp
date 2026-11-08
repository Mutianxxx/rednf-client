#pragma once
#include "character_controller.hpp"
#include "content_profile.hpp"

namespace dnf {
class World;
class Progression;
class CharacterStore;
struct Scene;

// User policy: the current source's legal identity rewards and level floors,
// without executing their task/material/trainer conditions. This does not
// classify any advancement skill or original controller as complete.
struct CharacterAdvancementOption {
    CharacterIdentity identity;
    int requiredLevel = 0;
    std::string name;
    std::vector<SourceRef> sources;
    Json snapshot() const;
};
class CharacterAdvancementCatalog {
    std::string pvfIdentity_;
    int trainerId_ = -1;
    std::string trainerPath_;
    SourceRef trainerSource_, questRegistry_;
    std::map<CharacterIdentity,CharacterAdvancementOption> options_;
    std::vector<Script> evidence_;
    Json diagnostics_ = Json::array();
    size_t scanned_ = 0;
  public:
    CharacterAdvancementCatalog(Pvf &, const CharacterCatalog &);
    const CharacterAdvancementOption *find(CharacterIdentity) const;
    bool supports(CharacterIdentity) const;
    bool isTrainer(int npcId) const { return trainerId_ >= 0 && npcId == trainerId_; }
    int trainerId() const { return trainerId_; }
    const std::string &trainerPath() const { return trainerPath_; }
    const std::map<CharacterIdentity,CharacterAdvancementOption> &options() const { return options_; }
    Json snapshot() const;
};
void registerSourceAdvancementAdapters(CharacterControllerRegistry &, const CharacterCatalog &,
    const CharacterAdvancementCatalog &, const std::string &pvfIdentity);

// Single-threaded owner-bound source reuse. This ordered context contains only
// already loaded CharacterCatalog inputs, never mutable World or skill state.
Json characterAdvancementSourceContext(const Pvf &,const CharacterCatalog &);
std::shared_ptr<const CharacterAdvancementCatalog> sharedCharacterAdvancementCatalog(Pvf &,const CharacterCatalog &);
Json characterAdvancementCacheSnapshot(const Pvf &);

// All parsing, allocations, cooldown/configuration migration and attribute
// evaluation finish privately. Publication never reconstructs resources or
// resets the world's simulation, RNG, actors, inventory or reward ledger.
class PreparedCharacterAdvancement {
    struct Data;
    std::unique_ptr<Data> data_;
    explicit PreparedCharacterAdvancement(std::unique_ptr<Data>);
    friend class World;
  public:
    ~PreparedCharacterAdvancement();
    PreparedCharacterAdvancement(PreparedCharacterAdvancement &&) noexcept;
    PreparedCharacterAdvancement &operator=(PreparedCharacterAdvancement &&) noexcept;
    Json writeCharacter(Json character) const;
    Json diagnostics() const;
};

struct CharacterAdvancementRequest {
    std::string requestId;
    CharacterIdentity expectedIdentity, target;
    uint64_t expectedGeneration = 0;
    int npcId = -1;
    Json payload() const;
};
enum class CharacterAdvancementState { Rejected, Committed, Replayed, Pending };
struct CharacterAdvancementResult {
    CharacterAdvancementState state = CharacterAdvancementState::Rejected;
    bool ok = false;
    std::string message, error;
    Json receipt = Json::object(), trace = Json::object();
    Json json() const;
};
class CharacterAdvancementTransaction {
    struct Pending {
        CharacterStore *store = nullptr;
        World *world = nullptr;
        const Progression *progression = nullptr;
        CharacterIdentity before;
        int64_t simulationMs = 0;
        Json expectedProgression, expectedSimulation, expectedSkills;
        std::string requestId;
        std::unique_ptr<PreparedCharacterAdvancement> prepared;
        bool durable = false;
        Json receipt = Json::object();
    };
    std::unique_ptr<Pending> pending_;
    CharacterAdvancementResult publish();
    void validateFrozen() const;
  public:
    bool pending() const { return bool(pending_); }
    Json pendingSnapshot() const;
    CharacterAdvancementResult submit(CharacterStore &, int slot, World &, const Progression &,
        const Scene &, const CharacterAdvancementRequest &, const Json &regionSessionSnapshot);
    CharacterAdvancementResult retry(CharacterStore &, World &);
};
} // namespace dnf
