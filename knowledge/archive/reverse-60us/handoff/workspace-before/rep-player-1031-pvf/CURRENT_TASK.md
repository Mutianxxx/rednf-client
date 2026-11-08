# 当前任务：独立 1031 PVF 技能预览

用户要求先分析 rep-player 的完整绘制链，解释 86JP/1031 REP 差异，再直接修改独立播放器，用 1031 PVF 驱动技能特效预览。重点包括技能可见特效的来源、攻击几何、怪物动作及 PVP UI 渲染；“菜单”“商城”是字体目标。此前 P01–P19 主项目实施已按用户指示记录并暂停，未经用户看本 demo 确认，不向主项目迁移本逻辑。

最新授权顺序：先完成跨角色通用模板套用，编译独立预览供用户查看，再逐角色专用适配。节点05在节点04四条来源技能流程之上增加十角色模板体验，共用事件、人物/特效/对象独立时间线、附层、返站和清理。使用每个角色自己的CHR与技能表；匹配、歧义和临时普攻回退显式标记，不能把模板当作对应技能的原生控制器或完整实现。来源四流程和原注册资源检查仍独立保留。细项与验收见 `docs/PROGRESS.md`，使用见 `README-1031.md`。

恢复时：

1. 阅读工作区 `agent.md`、本文件、`docs/PROGRESS.md`、`docs/SKILL_EFFECT_RENDER_TRACE.md` 和 `docs/REP_PLAYER_CALL_CHAIN.md`。
2. 核对当前 PVF SHA256 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`；EXE 身份见最新构建 manifest 与 `validation/latest-checkpoint.json`。
3. 启动 `Start-1031.cmd`。若要重建，运行 `build-preview.ps1`；完整 backup 的 `source` 本身就是项目根。
4. 先收集用户对模板预览的角色、技能名、时间点、特效/对象开关与画面差异反馈，再按角色适配消费者、资格、调度、对象生命周期及命中因果；不要把模板、NUT注册列表、同播资源或CHR动作浏览记作全部技能完成。
5. 独立验证后再由用户确认迁移。主项目和原客户端仍保持隔离；历史备份不覆盖。

后续实现重点：用户查看模板效果后再逐角色扩展实际NUT/ACT/native技能消费者、完整装备/武器、ATK命中接受/受击选择及音效、ALS未支持命令和原生时钟；PVP UI和目标字体继续在范围内。读 `docs/template-preview-bindings.md` 和 `docs/skill-playback-next-evidence.md`，不要重复只查common注册。原始bytes、有序字段、偏移、哈希、坐标和时间必须继续保留，以供其他平台移植。
