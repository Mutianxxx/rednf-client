#pragma once
#include "renderer.hpp"
#include <optional>

namespace dnf {
// UI selections are transient. Published bindings live in World/CharacterStore.
class SkillConfigurationUi {
    std::optional<CharacterIdentity> identity_;
    std::optional<SkillKey> selected_;
    size_t page_ = 0, slot_ = 0, motion_ = 0;
    int attack_ = -1, level_ = 1;
    size_t visibleCount_ = 0, sourceCount_ = 0;
    bool activeOnly_ = true;
    bool preview_ = false;
    bool fighterSource_ = false;
    Json view_=Json::object();
    std::string message_;
  public:
    void reset();
    bool draw(Renderer &, World &, int mx, int my, bool click, bool allowManualPreview = false);
    Json snapshot() const { return {{"page",page_},{"slot",slot_},{"active_only",activeOnly_},
        {"selected",selected_?selected_->json():Json()},{"level",level_},{"message",message_},
        {"visible_count",visibleCount_},{"source_count",sourceCount_},{"preview",preview_},{"fighter_source",fighterSource_},{"view",view_}}; }
};
} // namespace dnf
