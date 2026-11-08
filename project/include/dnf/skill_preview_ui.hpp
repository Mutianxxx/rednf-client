#pragma once
#include "dnf/skill_preview.hpp"
#include "dnf/skill_preview_mapping.hpp"
#include <string>

namespace dnf {
class Renderer;
class Pvf;

// Viewer chrome: job column, skills table with icons and grade marks, and the
// demonstration viewport on the right.
class SkillPreviewUi {
  public:
    struct Request {
        int jobId = -1;      // >=0: user picked a job
        int skillIndex = -1; // >=0: row index inside SkillMappingTable::rows()
        bool cast = false;   // explicit replay (double click)
        bool filterChanged = false;
    };
    struct InputState {
        int mx = 0, my = 0;           // hover pointer, in UI space
        int clickX = 0, clickY = 0;   // press coordinates, in UI space
        bool click = false, doubleClick = false;
    };

    explicit SkillPreviewUi(int width = 1280, int height = 720)
        : width_(width), height_(height) {}

    Request draw(Renderer &, Pvf &, const SkillMappingTable &, SkillPreviewSession &,
                 int selectedJob, int selectedSkill, const InputState &);
    // Wheel only scrolls the panel under the pointer.
    void scroll(int delta, int mouseX);
    void setGradeFilter(int grade) { gradeFilter_ = grade; }
    int gradeFilter() const { return gradeFilter_; }
    int visibleRows() const { return visible_; }

    int width() const { return width_; }
    int height() const { return height_; }

  private:
    // Row geometry is shared by the background, the hover band and the hit
    // test; three different paddings is what made clicks land on the next row.
    static constexpr int jobPanelW = 236;
    static constexpr int skillPanelW = 400;
    static constexpr int headerH = 36;
    static constexpr int footerH = 30;
    static constexpr int rowH = 24;
    static constexpr int listTop = headerH + 26;
    static constexpr int textDy = 5;
    static constexpr int iconSize = 20;

    int width_, height_;
    int jobScroll_ = 0, skillScroll_ = 0;
    int gradeFilter_ = -1; // -1 = all, otherwise SkillGrade value
    int visible_ = 0;
    int cachedJob_ = -2;
};
} // namespace dnf
