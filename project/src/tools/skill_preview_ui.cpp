#include "dnf/skill_preview_ui.hpp"
#include "dnf/renderer.hpp"
#include <algorithm>
#include <cstdio>

namespace dnf {
namespace {
SDL_Color gradeColor(SkillGrade grade) {
    switch (grade) {
        case SkillGrade::A: return {96, 200, 126, 255};
        case SkillGrade::B: return {96, 156, 232, 255};
        case SkillGrade::C: return {226, 176, 84, 255};
        default: return {122, 96, 96, 255};
    }
}
const char *gradeText(SkillGrade grade) {
    switch (grade) {
        case SkillGrade::A: return "A";
        case SkillGrade::B: return "B";
        case SkillGrade::C: return "C";
        default: return "D";
    }
}
const char *gradeHint(SkillGrade grade) {
    switch (grade) {
        case SkillGrade::A: return "动作+判定+特效";
        case SkillGrade::B: return "仅动作";
        case SkillGrade::C: return "仅特效";
        default: return "无资源";
    }
}
const char *attackSourceText(AttackBoxSource source) {
    switch (source) {
        case AttackBoxSource::AniBody: return "源 ANI 攻击盒";
        case AttackBoxSource::AniWeapon: return "源 ANI 武器盒";
        case AttackBoxSource::Reconstructed40Jp: return "重建（40JP 常量）";
        default: return "无";
    }
}
} // namespace

void SkillPreviewUi::scroll(int delta, int mouseX) {
    if (mouseX < jobPanelW) jobScroll_ = std::max(0, jobScroll_ + delta);
    else skillScroll_ = std::max(0, skillScroll_ + delta);
}

SkillPreviewUi::Request SkillPreviewUi::draw(Renderer &render, Pvf &pvf,
                                             const SkillMappingTable &table,
                                             SkillPreviewSession &session,
                                             int selectedJob, int selectedSkill,
                                             const InputState &input) {
    (void)pvf;
    Request request;
    render.rect(0, 0, float(width_), float(height_), {14, 16, 22, 255});

    // ---- header -----------------------------------------------------------
    render.rect(0, 0, float(width_), float(headerH), {24, 27, 36, 255});
    render.text("DNF 40JP 技能演示", 12, 9, 17, {232, 216, 176, 255});
    render.text("点击即播 · 仅渲染与判定 · 无等级/MP/CD", 210, 12, 12, {140, 140, 152, 255});

    // Grade filter buttons.
    const char *filterLabels[] = {"全部", "A", "B", "C", "D"};
    int filterX = width_ - 250;
    for (int i = 0; i < 5; ++i) {
        const int grade = i == 0 ? -1 : i - 1;
        const bool active = gradeFilter_ == grade;
        const int buttonW = i == 0 ? 42 : 28;
        const bool hover = input.mx >= filterX && input.mx < filterX + buttonW &&
                           input.my >= 6 && input.my < headerH - 6;
        render.rect(float(filterX), 6, float(buttonW), float(headerH - 12),
                    active ? SDL_Color{70, 60, 38, 255}
                           : hover ? SDL_Color{44, 47, 58, 255} : SDL_Color{32, 35, 46, 255});
        render.text(filterLabels[i], float(filterX + 6), 10, 12,
                    active ? SDL_Color{246, 222, 160, 255} : SDL_Color{180, 180, 190, 255});
        if (input.click && input.clickX >= filterX && input.clickX < filterX + buttonW &&
            input.clickY >= 6 && input.clickY < headerH - 6) {
            gradeFilter_ = grade;
            skillScroll_ = 0;
            request.filterChanged = true;
        }
        filterX += buttonW + 6;
    }

    const int listHeight = height_ - headerH - footerH;
    const int visibleRows = std::max(1, (listHeight - 26) / rowH);

    // ---- job column -------------------------------------------------------
    render.rect(0, float(headerH), float(jobPanelW), float(listHeight), {20, 22, 30, 255});
    render.text("职业", 10, float(headerH + 4), 12, {180, 180, 190, 255});
    const auto &jobs = table.jobs();
    const int maxJobScroll = std::max(0, int(jobs.size()) - visibleRows);
    jobScroll_ = std::clamp(jobScroll_, 0, maxJobScroll);
    for (int row = 0; row < visibleRows && jobScroll_ + row < int(jobs.size()); ++row) {
        const auto &job = jobs[size_t(jobScroll_ + row)];
        const float y = float(listTop + row * rowH);
        const bool hover = input.mx >= 4 && input.mx < jobPanelW - 4 &&
                           input.my >= y && input.my < y + rowH;
        const bool hit = input.click && input.clickX >= 4 && input.clickX < jobPanelW - 4 &&
                         input.clickY >= y && input.clickY < y + rowH;
        const bool chosen = job.jobId == selectedJob;
        if (chosen || hover)
            render.rect(4, y, float(jobPanelW - 8), float(rowH),
                        chosen ? SDL_Color{52, 46, 30, 255} : SDL_Color{30, 33, 44, 255});
        render.text(job.name, 10, y + float(textDy), 13,
                    chosen ? SDL_Color{246, 222, 160, 255} : SDL_Color{206, 206, 214, 255});
        char counts[32];
        if (job.skillCount == 0) std::snprintf(counts, sizeof(counts), "—");
        else std::snprintf(counts, sizeof(counts), "A%d/%d", job.gradeA, job.skillCount);
        render.text(counts, float(jobPanelW - 62), y + float(textDy), 11,
                    job.gradeA > 0 ? SDL_Color{140, 190, 150, 255} : SDL_Color{120, 120, 130, 255});
        if (hit) request.jobId = job.jobId;
    }

    // ---- skill column -----------------------------------------------------
    const auto &rows = table.rows(selectedJob);
    std::vector<int> visibleIndices;
    visibleIndices.reserve(rows.size());
    for (int i = 0; i < int(rows.size()); ++i)
        if (gradeFilter_ < 0 || int(rows[size_t(i)].grade) == gradeFilter_)
            visibleIndices.push_back(i);
    visible_ = int(visibleIndices.size());

    const float skillX = float(jobPanelW);
    render.rect(skillX, float(headerH), float(skillPanelW), float(listHeight), {24, 26, 34, 255});
    {
        char title[64];
        std::snprintf(title, sizeof(title), "技能 %d/%d", visible_, int(rows.size()));
        render.text(title, skillX + 10, float(headerH + 4), 12, {180, 180, 190, 255});
    }
    const int maxSkillScroll = std::max(0, visible_ - visibleRows);
    skillScroll_ = std::clamp(skillScroll_, 0, maxSkillScroll);
    for (int row = 0; row < visibleRows && skillScroll_ + row < visible_; ++row) {
        const int index = visibleIndices[size_t(skillScroll_ + row)];
        const auto &skill = rows[size_t(index)];
        const float y = float(listTop + row * rowH);
        const bool hover = input.mx >= skillX + 4 && input.mx < skillX + skillPanelW - 4 &&
                           input.my >= y && input.my < y + rowH;
        const bool hit = input.click && input.clickX >= skillX + 4 &&
                         input.clickX < skillX + skillPanelW - 4 &&
                         input.clickY >= y && input.clickY < y + rowH;
        // selectedSkill is a row index, never a skill id.
        const bool chosen = index == selectedSkill;
        if (chosen || hover)
            render.rect(skillX + 4, y, float(skillPanelW - 8), float(rowH),
                        chosen ? SDL_Color{52, 46, 30, 255} : SDL_Color{32, 35, 46, 255});
        render.rect(skillX + 6, y + 3, 3, float(rowH - 6), gradeColor(skill.grade));
        const bool hasIcon = !skill.iconPath.empty() && skill.iconFrame >= 0;
        if (hasIcon) {
            const double scale = double(iconSize) / 28.0;
            render.sprite(skill.iconPath, skill.iconFrame, skillX + 14,
                          y + (rowH - iconSize) * 0.5, 1, scale);
        } else {
            // A missing icon keeps its slot so the name column never shifts.
            render.rect(skillX + 14, y + (rowH - iconSize) * 0.5f, float(iconSize),
                        float(iconSize), {30, 33, 44, 255});
        }
        const float textX = skillX + 14 + iconSize + 6;
        render.text(skill.name, textX, y + float(textDy), 13,
                    chosen ? SDL_Color{246, 222, 160, 255} : SDL_Color{206, 206, 214, 255});
        render.text(gradeText(skill.grade), skillX + skillPanelW - 54, y + float(textDy), 11,
                    gradeColor(skill.grade));
        render.text(std::to_string(skill.key.skillId), skillX + skillPanelW - 34,
                    y + float(textDy), 11, {120, 120, 130, 255});
        if (hit) {
            request.skillIndex = index;
            if (input.doubleClick) request.cast = true;
        }
    }

    // ---- viewport ---------------------------------------------------------
    const float viewX = skillX + float(skillPanelW);
    const float viewW = float(width_) - viewX;
    const float viewY = float(headerH);
    const float viewH = float(listHeight);
    render.rect(viewX, viewY, viewW, viewH, {9, 11, 16, 255});
    for (float gx = viewX; gx < viewX + viewW; gx += 40)
        render.rect(gx, viewY, 1, viewH, {18, 21, 28, 255});
    for (float gy = viewY; gy < viewY + viewH; gy += 40)
        render.rect(viewX, gy, viewW, 1, {18, 21, 28, 255});

    const double cameraX = session.stageX() - (double(viewX) + double(viewW) * 0.5);
    const double cameraY = session.stageY() - (double(viewY) + double(viewH) * 0.62);
    session.draw(render, cameraX, cameraY);

    if (!session.hasJob())
        render.text("先在左侧选择职业", viewX + 16, viewY + 16, 14, {200, 200, 208, 255});
    else if (const auto *current = session.current(); !current) {
        render.text("在中间选择技能", viewX + 16, viewY + 16, 14, {200, 200, 208, 255});
    } else {
        render.rect(viewX, viewY, viewW, 22,
                    current->grade == SkillGrade::A ? SDL_Color{20, 46, 28, 235}
                    : current->grade == SkillGrade::C ? SDL_Color{58, 34, 12, 235}
                    : current->grade == SkillGrade::D ? SDL_Color{46, 20, 20, 235}
                                                      : SDL_Color{24, 32, 48, 235});
        char banner[200];
        std::snprintf(banner, sizeof(banner), "分级 %s · %s · 动作%s 特效%zu 粒子%zu · 判定 %s",
                      gradeText(current->grade), gradeHint(current->grade),
                      current->bodyAni.empty() ? "无" : "有", current->effects.size(),
                      current->particles.size(), attackSourceText(current->attackSource));
        render.text(banner, viewX + 8, viewY + 4, 12, gradeColor(current->grade));
        // A chained release is the headline fact: the client plays several ANIs
        // back to back, and the stage names are the evidence for the order.
        if (!current->chainEvidence.empty())
            render.text(current->chainEvidence, viewX + 8, viewY + 24, 11, {190, 200, 160, 255});
        if (!current->missing.empty())
            render.text(current->missing, viewX + 8,
                        viewY + (current->chainEvidence.empty() ? 24.0f : 40.0f), 11,
                        {200, 160, 150, 255});
        else if (current->grade == SkillGrade::D)
            render.text("无可用资源（不是绘制失败）", viewX + 8, viewY + 24, 11, {200, 160, 150, 255});
    }

    // ---- footer -----------------------------------------------------------
    const float footerY = float(height_ - footerH);
    render.rect(0, footerY, float(width_), float(footerH), {24, 27, 36, 255});
    render.text("空格 暂停 · ←/→ 逐帧 · 1/2/3/4 速度 · R 重放 · F 翻转 · B 判定框 · H 木桩 · L 循环 · F12 截图",
                12, footerY + 8, 12, {150, 150, 160, 255});
    if (const auto *current = session.current()) {
        char state[160];
        std::snprintf(state, sizeof(state), "%s%s  %.0f/%.0fms  %.1fx  层%zu 命中%zu 粒子%zu",
                      session.paused() ? "暂停" : "播放", session.loop() ? "·循环" : "",
                      session.ageMs(), session.durationMs(), session.speed(),
                      session.layerCount(), session.hitCount(), session.particleCount());
        render.text(state, float(width_) - render.textWidth(state, 12) - 12, footerY + 8, 12,
                    {200, 190, 150, 255});
    } else {
        render.text("未选择", float(width_) - 60, footerY + 8, 12, {150, 150, 160, 255});
    }
    return request;
}
} // namespace dnf
