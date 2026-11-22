#pragma once
#include "storage.hpp"
namespace dnf {
// A test run forks a complete durable normal checkpoint. All later gameplay
// writes go to this independent writer until the application returns to normal
// character selection. Turning an individual override off never merges rewards.
class BetaSaveBranch {
    std::unique_ptr<CharacterStore> store_;
    std::filesystem::path directory_;
  public:
    bool active() const { return bool(store_); }
    CharacterStore &select(CharacterStore &normal) { return store_ ? *store_ : normal; }
    const std::filesystem::path &directory() const { return directory_; }
    void fork(CharacterStore &normal, const std::filesystem::path &directory, Json metadata);
    void close();
};
} // namespace dnf
