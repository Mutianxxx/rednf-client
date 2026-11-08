# 当前任务：独立 1031 PVF 技能预览

## R60-03 最终候选已通过自动验证

入口 `Start-R60-03.cmd` 指向 `candidate-r60-03-final2/build/rep_pvf_preview.exe`，SHA256 `d87406f0b25fa7a1cc303816ba9df71aa6025f68a4905ba46016ff2c91df69f3`。新独立clock选择、60Hz时间线/暂停/单步/拖动重建、主/ALS/怪物/命中特效时钟已实施。复制轨道显式重定时的回归已修复，20项合同、72项D3D、78帧隐藏GUI、184四流程及24104全模板检查通过。旧final与183/184失败报告保留。

统一主工程最终核心/音频也已通过，准确身份见 [R60-03-VERIFICATION](../reverse-60us/integration/R60-03-VERIFICATION.json)。节点备份/后续进度见 [统一接手点](../reverse-60us/CURRENT_TASK.md) 和 [R60-03-PROGRESS](../reverse-60us/integration/R60-03-PROGRESS.md)。配方阶段/位移/命中特效出生位置仍是推断；没有以模板计完整技能，没有将播放器模板迁到主客户端。前台效果/听音/手感及原版动态待用户。

## R60-02 已验证的新候选，继续R60-03

启动 `Start-R60-02.cmd`，运行隔离 `candidate-r60-02-final/build/rep_pvf_preview.exe`，SHA256 `5ce28085505260006a2d5664920e681109b6d7818ac74ceccaac8540ea647ea7`。原 `Start-1031.cmd` / node05不覆盖。新增两渲染策略、源INTERPOLATION采样和模板SKL原图标；60US算法用于1031标跨版本推断，导出保留策略。48项D3D、78帧隐藏GUI、184四流程、24104全模板回归通过；用户画面/听音/手感及原版动态仍待验证。

实际范围/备份/重建闭包见 [R60-02进度](../reverse-60us/integration/R60-02-PROGRESS.md) 与 [统一接手点](../reverse-60us/CURRENT_TASK.md)。R60-03时钟/附层正在推进，当前资源DELAY检查时钟未被认定原生。十角色1677模板仍不计完整技能控制器；PVP非文字UI和【菜单】【商城】字体目标保留。独立播放器的模板未迁到主工程。

## 2026-10-20：60US成果接入优先补充

用户要求并行推进接入侧，已新增 [reverse-60us](../reverse-60us/README.md)。先读其 [接手点](../reverse-60us/CURRENT_TASK.md)、[模块位置](../reverse-60us/MODULE_MAP.md) 与 [接入计划](../reverse-60us/PORTING_PLAN.md)，执行R60-01→R60-02：复用现有名称接口，核查 `pvf_preview_scene.cpp` 中保留INTERPOLATION但离散采样的路径，接通可核对的位置/缩放/旋转/RGBA采样和混合，再推进原生clock与视觉对象生命周期；伤害后置。

本包来源为60US六职业文本PVF，当前工程仍为1031十职业与二进制PVF，不能直接复制注册格式、状态号和地址。60US位置/颜色向零截断与现有参考double mix有差异；迁往1031须核对该版本或明确标注跨版本推断。已有模板、普攻回退与四来源流程保留各自证据状态，不将同名资源绑定批量标为原生控制器。

本次没有修改本工程C++、EXE或节点05备份。现在可以直接开展新授权的审查与隔离渲染候选，旧的“先等模板体验”不阻止这两项；未经核实的旧模板不因此自动迁入主运行时。双方写入分工与后续任务见reverse-60us，当前源目录继续作为本工程实现位置，历史60US快照只读。

## 原任务与历史恢复记录

用户要求先分析 rep-player 的完整绘制链，解释 86JP/1031 REP 差异，再直接修改独立播放器，用 1031 PVF 驱动技能特效预览。重点包括技能可见特效的来源、攻击几何、怪物动作及 PVP UI 渲染；“菜单”“商城”是字体目标。此前 P01–P19 主项目实施已按用户指示记录并暂停，未经用户看本 demo 确认，不向主项目迁移本逻辑。

最新授权顺序：先完成跨角色通用模板套用，编译独立预览供用户查看，再逐角色专用适配。节点05在节点04四条来源技能流程之上增加十角色模板体验，共用事件、人物/特效/对象独立时间线、附层、返站和清理。使用每个角色自己的CHR与技能表；匹配、歧义和临时普攻回退显式标记，不能把模板当作对应技能的原生控制器或完整实现。来源四流程和原注册资源检查仍独立保留。细项与验收见 `docs/PROGRESS.md`，使用见 `README-1031.md`。

恢复时：

1. 阅读工作区 `agent.md`、本文件、`docs/PROGRESS.md`、`docs/SKILL_EFFECT_RENDER_TRACE.md` 和 `docs/REP_PLAYER_CALL_CHAIN.md`。
2. 核对当前 PVF SHA256 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`；EXE 身份见最新构建 manifest 与 `validation/latest-checkpoint.json`。
3. 启动 `Start-1031.cmd`。若要重建，运行 `build-preview.ps1`；完整 backup 的 `source` 本身就是项目根。
4. 先收集用户对模板预览的角色、技能名、时间点、特效/对象开关与画面差异反馈，再按角色适配消费者、资格、调度、对象生命周期及命中因果；不要把模板、NUT注册列表、同播资源或CHR动作浏览记作全部技能完成。
5. 独立验证后再由用户确认迁移。主项目和原客户端仍保持隔离；历史备份不覆盖。

后续实现重点：用户查看模板效果后再逐角色扩展实际NUT/ACT/native技能消费者、完整装备/武器、ATK命中接受/受击选择及音效、ALS未支持命令和原生时钟；PVP UI和目标字体继续在范围内。读 `docs/template-preview-bindings.md` 和 `docs/skill-playback-next-evidence.md`，不要重复只查common注册。原始bytes、有序字段、偏移、哈希、坐标和时间必须继续保留，以供其他平台移植。
