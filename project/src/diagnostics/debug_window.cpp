#include "dnf/debug_window.hpp"
#include "dnf/renderer.hpp"
#include <algorithm>
#include <iterator>
#include <limits>

namespace dnf {
namespace {
uint32_t eventWindow(const SDL_Event &event) {
    switch (event.type) {
    case SDL_WINDOWEVENT: return event.window.windowID;
    case SDL_KEYDOWN: case SDL_KEYUP: return event.key.windowID;
    case SDL_TEXTINPUT: return event.text.windowID;
    case SDL_TEXTEDITING: return event.edit.windowID;
    case SDL_MOUSEMOTION: return event.motion.windowID;
    case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP: return event.button.windowID;
    case SDL_MOUSEWHEEL: return event.wheel.windowID;
    default: return 0;
    }
}
std::string toggleLabel(const char *label, bool value) { return std::string(label) + (value ? "：开" : "：关"); }
std::string clipped(const std::string &text, size_t maximum = 88) {
    // Diagnostic identifiers/reasons are ASCII, while user-facing labels are
    // drawn separately. Avoid splitting arbitrary UTF-8 exception messages.
    if (text.size() <= maximum) return text;
    size_t end = maximum;
    while (end && (uint8_t(text[end]) & 0xc0) == 0x80) --end;
    return text.substr(0,end) + "...";
}
} // namespace

DebugWindow::DebugWindow(Assets &assets, DebugService &service) : service_(service) {
    RendererOptions options;
    options.title = "DNF v0.1 beta - Test Tools";
    options.width = 800; options.height = 900;
    options.vsync = false; options.shown = false; options.resizable = true;
    renderer_ = std::make_unique<Renderer>(assets,options);
}
DebugWindow::~DebugWindow() = default;
uint32_t DebugWindow::windowId() const { return SDL_GetWindowID(renderer_->window()); }
bool DebugWindow::hasFocus() const {
    return visible_ && (SDL_GetWindowFlags(renderer_->window()) & SDL_WINDOW_INPUT_FOCUS) != 0;
}
void DebugWindow::show() {
    SDL_ShowWindow(renderer_->window());
    SDL_RaiseWindow(renderer_->window());
    visible_ = true; dirty_ = true; nextDraw_ = 0;
}
void DebugWindow::hide() {
    SDL_HideWindow(renderer_->window());
    visible_ = false; mouseX_ = mouseY_ = -100;
    controls_.clear(); dirty_ = true;
}
void DebugWindow::submit(const Control &control) {
    if(control.selectIdentity) {draftIdentity_=control.payload;dirty_=true;return;}
    try {
        submitted_ = service_.submit({service_.nextRequestId(),displayedTarget_,control.kind,control.payload});
    } catch (const std::exception &error) {
        submitted_ = DebugResult{0,DebugResultState::Rejected,error.what(),-1,Json::object()};
    }
    dirty_ = true;
}
bool DebugWindow::handleEvent(const SDL_Event &event) {
    if (!eventWindow(event) || eventWindow(event) != windowId()) return false;
    if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) hide();
        if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST || event.window.event == SDL_WINDOWEVENT_LEAVE)
            mouseX_ = mouseY_ = -100;
        if (event.window.event == SDL_WINDOWEVENT_EXPOSED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            dirty_ = true;
    }
    if (event.type == SDL_KEYDOWN && !event.key.repeat &&
        (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_F9)) hide();
    if (!visible_) return true;
    if (event.type == SDL_MOUSEMOTION) {
        mouseX_ = event.motion.x; mouseY_ = event.motion.y;
        renderer_->mouse(mouseX_,mouseY_,800,900);
    }
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        mouseX_ = event.button.x; mouseY_ = event.button.y;
        renderer_->mouse(mouseX_,mouseY_,800,900);
        for (const auto &control : controls_)
            if (control.enabled && mouseX_ >= control.rect.x && mouseX_ < control.rect.x + control.rect.w &&
                mouseY_ >= control.rect.y && mouseY_ < control.rect.y + control.rect.h) {
                submit(control);
                break;
            }
    }
    return true;
}
void DebugWindow::draw(const DebugSnapshot &snapshot, uint64_t uiTimeMs) {
    if (!visible_) return;
    if (!dirty_ && uiTimeMs < nextDraw_) return;
    // UI time remains independent of simulation/menu pause. Only the game
    // window uses the user's vsync policy; this renderer never waits for it.
    nextDraw_ = uiTimeMs > std::numeric_limits<uint64_t>::max() - 33 ? uiTimeMs : uiTimeMs + 33;
    dirty_ = false;
    if(displayedTarget_!=snapshot.target)draftIdentity_=snapshot.actual.value("identity",Json());
    displayedTarget_ = snapshot.target;
    controls_.clear();
    auto &render = *renderer_;
    render.begin(); render.ui(800,900);
    render.text("Beta 独立测试工具",22,15,24);
    render.text("F9 显示；Esc / 关闭窗口只隐藏。命令在模拟边界确认。",22,48,14);
    const bool bound = snapshot.target.valid();
    render.text(bound ? "角色 " + clipped(snapshot.target.characterUuid,40) + "  目标代 " +
        std::to_string(snapshot.target.generation) : "尚未选择角色：测试命令不可用",22,76,14);
    const auto &state = snapshot.actual;
    render.text("正常等级 " + std::to_string(snapshot.normalLevel) + "   有效等级 " +
        std::to_string(state.value("character_level",snapshot.normalLevel)) + "   Tick " + std::to_string(snapshot.tick),22,101,16);
    render.text("HP " + std::to_string(state.value("hp",0)) + "/" + std::to_string(state.value("max_hp",0)) +
        "       MP " + std::to_string(state.value("mp",0)) + "/" + std::to_string(state.value("max_mp",0)) +
        (state.value("dead",false) ? "   已死亡（资源锁不会复活）" : ""),22,129,16);
    const auto button = [&](const std::string &label, int x, int y, int width, DebugCommandKind kind,
                            Json payload, bool enabled = true, bool selectIdentity = false) {
        controls_.push_back({{x,y,width,34},kind,std::move(payload),enabled,selectIdentity});
        render.button(label,x,y,width,34,mouseX_,mouseY_,false,enabled);
    };
    const auto &effective = snapshot.effective;
    button(toggleLabel("测试总开关",effective.enabled),22,165,360,DebugCommandKind::SetEnabled,!effective.enabled,bound);
    render.text("开启后使用独立测试存档分支",405,173,15,{235,190,108,255});
    const bool enabled = bound && effective.enabled;
    button(toggleLabel("HP 独立锁定",effective.hpLock),22,207,360,DebugCommandKind::SetHpLock,!effective.hpLock,enabled);
    button(toggleLabel("MP 独立锁定",effective.mpLock),405,207,370,DebugCommandKind::SetMpLock,!effective.mpLock,enabled);
    button(toggleLabel("无 CD（仍提交正常冷却）",effective.noCooldown),22,249,360,DebugCommandKind::SetNoCooldown,!effective.noCooldown,enabled);
    button(toggleLabel("暂停 AI",effective.pauseAi),405,249,370,DebugCommandKind::SetAiPaused,!effective.pauseAi,enabled);
    render.text("测试等级覆盖：" + (effective.level ? std::to_string(*effective.level) : std::string("关闭")),22,300,18);
    const int level = effective.level.value_or(state.value("character_level",snapshot.normalLevel));
    button("-10",22,331,95,DebugCommandKind::SetLevelOverride,std::max(1,level - 10),enabled);
    button("-1",125,331,95,DebugCommandKind::SetLevelOverride,std::max(1,level - 1),enabled);
    button("+1",228,331,95,DebugCommandKind::SetLevelOverride,int64_t(level) + 1,enabled);
    button("+10",331,331,95,DebugCommandKind::SetLevelOverride,int64_t(level) + 10,enabled);
    button("恢复正常等级",441,331,334,DebugCommandKind::ClearLevelOverride,Json(),enabled);
    render.text("只重算属性；不发 SP/TP、经验、技能、任务或转职奖励。",22,374,14);
    button(snapshot.pauseRequested ? "继续模拟" : "暂停模拟",22,405,235,
        DebugCommandKind::SetSimulationPaused,!snapshot.pauseRequested,bound);
    button("单步：一个正常 tick",275,405,245,DebugCommandKind::SingleStep,Json(),enabled && snapshot.simulationPaused);
    button("重置测试设置",538,405,237,DebugCommandKind::Reset,Json(),bound);
    render.text(std::string("模拟状态：") + (snapshot.simulationPaused ? "暂停" : "运行") +
        "   待处理命令 " + std::to_string(snapshot.pendingCount) + "   单步请求 " +
        std::to_string(snapshot.singleStepRequests),22,450,15);
    std::optional<DebugResult> last;
    if (!snapshot.recentResults.empty()) last = snapshot.recentResults.back();
    if (submitted_ && (!last || submitted_->requestId > last->requestId)) last = submitted_;
    if (last) {
        render.text("请求 #" + std::to_string(last->requestId) + "  " + debugResultName(last->state) +
            "  tick " + std::to_string(last->appliedTick),22,480,14);
        render.text(clipped(last->reason),22,505,13,
            last->state == DebugResultState::Rejected ? SDL_Color{255,143,129,255} : SDL_Color{195,225,195,255});
    }
    render.text("HP 锁保留受击；MP 锁不越过容量；无 CD 不授予未学技能。",22,541,14);
    render.text("关闭子开关仍在测试分支；返回选角后恢复正常分支。主窗 F8 导出反馈。",22,566,13);
    const auto ai=state.value("monster_event_ai_test",Json::object());
    const auto available=ai.value("available_difficulties",Json::array());
    const auto selected=snapshot.selected.monsterAiDifficulty;
    const bool exploration=ai.value("map_exploration_active",false);
    std::string next;
    if(available.is_array() && !available.empty()) {
        const auto found=std::find(available.begin(),available.end(),Json(selected));
        if(found==available.end()) next=available.front().get<std::string>();
        else if(std::next(found)!=available.end()) next=std::next(found)->get<std::string>();
    }
    render.text("F7 怪物 Event.ai：明确选择 MOB 原始难度；默认关闭，按命中触发。",22,592,14);
    button("源难度："+(selected.empty()?std::string("关闭"):selected)+" → "+
        (next.empty()?std::string("关闭"):next),22,620,548,DebugCommandKind::SetMonsterAiDifficulty,next,
        enabled && exploration && !available.empty());
    button("关闭 Event.ai",586,620,189,DebugCommandKind::SetMonsterAiDifficulty,"",
        enabled && !selected.empty());
    render.text(exploration ? "已安装 "+std::to_string(ai.value("installed",0))+"  拒绝 "+
        std::to_string(ai.value("rejected",0))+"  "+ai.value("state",std::string()) :
        "仅 F7 探索可用；普通副本未启用此推理策略。",22,664,13);
    std::string aiReason;
    const auto actors=ai.value("actors",Json::array());
    for(const auto &actor:actors) if(actor.contains("reason") && actor.value("reason",std::string())!="selection_disabled") {
        aiReason=actor.value("reason",std::string());break;
    }
    if(available.empty() && exploration) aiReason="当前场景没有可选择的源 AI 难度；F8 保留逐怪诊断。";
    if(!aiReason.empty()) render.text(clipped(aiReason),22,690,12,{235,190,108,255});
    const auto identities=state.value("identity_candidates",Json::array());
    const auto actualIdentity=state.value("identity",Json());
    std::string actualName="未知来源身份";
    for(const auto &row:identities)if(row.value("identity",Json())==actualIdentity){actualName=row.value("label",std::string());break;}
    render.text("当前身份："+actualName+"；先选职业、分支，再点应用。",22,719,14);
    const Json *draft=nullptr;
    for(const auto &row:identities)if(row.value("identity",Json())==draftIdentity_){draft=&row;break;}
    if(!draft)for(const auto &row:identities)if(row.value("identity",Json())==actualIdentity){draft=&row;draftIdentity_=actualIdentity;break;}
    if(!draft&&!identities.empty()){draft=&identities.front();draftIdentity_=draft->value("identity",Json());}
    std::vector<const Json *> jobs,branches;
    int draftJob=-1;
    if(draft)draftJob=draft->at("identity").value("job_id",-1);
    for(const auto &row:identities) {
        const int job=row.at("identity").value("job_id",-1);
        if(job<0)continue;
        if(std::none_of(jobs.begin(),jobs.end(),[&](const auto *entry){return entry->at("identity").value("job_id",-1)==job;}))jobs.push_back(&row);
        if(job==draftJob)branches.push_back(&row);
    }
    const Json *nextJob=nullptr,*nextBranch=nullptr;
    for(size_t i=0;i<jobs.size();++i)if(jobs[i]->at("identity").value("job_id",-1)==draftJob)nextJob=jobs[(i+1)%jobs.size()];
    for(size_t i=0;i<branches.size();++i)if(branches[i]->at("identity")==draftIdentity_)nextBranch=branches[(i+1)%branches.size()];
    button("职业："+(draft?draft->value("job_name",std::string()):std::string("无来源"))+" →",22,748,360,
        DebugCommandKind::SetTestIdentity,nextJob?nextJob->at("identity"):Json(),enabled&&jobs.size()>1,true);
    button("分支："+(draft?draft->value("label",std::string()):std::string("无来源"))+" →",405,748,370,
        DebugCommandKind::SetTestIdentity,nextBranch?nextBranch->at("identity"):Json(),enabled&&branches.size()>1,true);
    const bool executable=draft&&draft->value("executable",false);
    const auto reason=draft?draft->value("reason",std::string()):std::string("identity_source_unavailable");
    render.text(executable?"选中身份已有可执行控制器；技能范围以实际回执为准。":
        "源分支未开放："+clipped(reason,72),22,791,13,executable?SDL_Color{195,225,195,255}:SDL_Color{235,190,108,255});
    button("应用所选测试身份",22,820,360,DebugCommandKind::SetTestIdentity,draftIdentity_,enabled&&executable);
    button("开放当前可执行技能",405,820,370,DebugCommandKind::UnlockExecutableSkills,Json(),enabled);
    render.text("仅在城镇应用；测试分支独立保存。K 打开技能界面，F8 导出实际回执。",22,864,13);
    if(last&&last->state==DebugResultState::Applied&&last->actual.contains("application")) {
        const auto &receipt=last->actual.at("application");
        if(receipt.is_object()&&receipt.contains("opened")&&receipt.at("opened").is_array()&&
            receipt.contains("blocked")&&receipt.at("blocked").is_array())
            render.text("本次已开放 "+std::to_string(receipt.at("opened").size())+" 项；保留缺口 "+
                std::to_string(receipt.at("blocked").size())+" 项。完整清单见 F8 反馈。",22,885,12,{195,225,195,255});
    }
    render.present();
}
} // namespace dnf
