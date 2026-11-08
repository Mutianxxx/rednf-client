# 11 独立 Beta 测试窗口与推理策略

版本：v1.1；日期：2026-10-18；状态：设计待实施；对应 P17。测试功能属于 beta 辅助工具，不作为原版 UI 复刻成果。

## 1. 现状与目标

[主入口](../dnf-native-demo/src/main.cpp)已有游戏内设置、god/freeCd/freezeAi 和诊断 fixture；[World](../dnf-native-demo/include/dnf/combat.hpp)承载这些运行状态；[设置模型](../dnf-native-demo/include/dnf/demo_settings.hpp)保留历史血量倍率及音量。当前没有完整独立测试窗口，god 合并 HP/MP 恢复，历史倍率仍相对 demo 基数，不能作为正式属性来源。

本轮提供同进程第二个 SDL_Window/SDL_Renderer。不引入 Qt/Python 作为用户启动依赖。首轮独立窗口关闭时隐藏且保留本次配置，整个游戏退出才销毁；新进程测试总开关默认关闭，危险/作弊状态不因 settings 自动开启。普通角色数据与测试覆盖值分开保存。

## 2. 接口、线程与双窗口事件

建议新增平台无关 `DebugSettings`、`DebugCommand`、`DebugResult`、`DebugSnapshot`、`RuleStrategyRegistry`；SDL 层仅实现 `DebugWindow`。命令包含 requestId、目标角色/副本身份、目标 generation、类型及参数。结果含 accepted/applied/rejected、原因、应用 tick 与实际值。UI 显示服务确认值，不乐观伪装已成功。

```cpp
struct DebugCommand { RequestId id; TargetIdentity target; Generation generation;
                      DebugCommandKind kind; Json payload; };
void DebugService::submit(DebugCommand command);
void DebugService::applyAtBoundary(World&, bool simulationPaused);
DebugSnapshot DebugService::snapshot() const;
```

SDL 事件先按 windowID 分流。主窗失焦时 releaseInputs，子窗键盘/鼠标不进入战斗；关闭子窗不转成全局 quit；主窗关闭按正常存档流程退出。各窗口持独立 renderer、texture cache 和 viewport/DPI，SDL_Texture 不跨 renderer 共享，仅共享 Pixels。初始化第二窗口失败须返回诊断，不能破坏已运行主窗。

仅两窗均失焦时默认暂停，切到测试窗只清主窗按键，不自动暂停；测试窗提供显式Pause。本轮窗口事件处理完再计算聚合焦点，避免失焦/获焦事件顺序产生伪暂停。仅主窗启用用户选择的vsync；测试窗无vsync、默认30Hz刷新且可配置，界面刷新不得阻塞主窗事件与模拟。

所有 SDL 窗口/GPU操作在主线程。管理命令在模拟状态的串行边界消费，不直接从 UI callback 修改 World。暂停时允许处理等级、锁定、策略选择等管理事务，但不调用 World::step，不增加 tick，不推进 CD、AI、粒子或奖励；处理完重新生成快照。菜单暂停和测试窗刷新采用独立 UI 时间。

```text
pump events → route by windowID → submit debug commands
if paused: apply management commands at current boundary; refresh snapshot
else: before each fixed tick apply commands; simulate tick; publish snapshot
draw game(snapshot,interpolation); draw debug(snapshot,uiTime)
```

requestId 去重；generation 已变化则拒绝旧命令，不把对旧副本的请求应用到新副本。队列容量有上限，满时显示失败而不默默丢弃。属性变化/技能 CD 改动通过正式服务，避免形成第二套战斗实现。

## 3. 测试功能的精确定义

| 功能 | 默认 | 执行语义 |
| --- | --- | --- |
| 测试总开关 | 每次启动关闭 | 开启后才允许测试覆盖；普通存档显示测试标记 |
| HP 锁定 | 关闭 | 开启时仅存活角色补到maxHP，伤害结算保留受击但阻止HP损失；死亡不复活 |
| MP 锁定 | 关闭 | 开启补到maxMP，消耗提交保留maxMP；资格仍按maxMP正常比较，单次花费超过maxMP仍拒绝 |
| 无 CD | 关闭 | 仅旁路CD门槛，正常CD仍提交并按模拟时间推进；未学/死亡/装备/状态条件仍有效 |
| 设置等级 | 不自动执行 | 独立debug等级override经成长服务重算，当前HP/MP夹紧至新上限；不改earned SP/TP、不发任务奖励、不自动转职 |
| 暂停 AI | 关闭 | 停AI决策，实体受击/生命周期仍按正常模拟；与暂停整个世界分开 |
| 单步 | 仅世界暂停时 | 明确一次正常tick；不和普通管理命令混合 |
| 显示碰撞/属性来源 | 关闭 | 只读调试绘制，不改变实际碰撞或数值 |

按[推荐决策 D18](appendices/recommended-decisions.md)，HP锁定不是无敌：霸体、击退和受击状态仍按规则执行，死亡角色不因开启锁定而复活；复活必须独立命令。MP锁不绕过最大资源容量、职业、等级、死亡及动作资格。若要免受击须另列明确测试策略。按D19，无CD期间每次施法仍提交正常冷却，既有冷却按模拟时间推进；关闭后直接恢复该正常剩余状态，不清空或延长。测试设级与正常升级区分：正常升级的“保留损失”由数值模块定义，本文只规定调试设级夹紧。

debug等级override与正常等级、经验、earned SP/TP账本分开；关闭override后按正常等级重算并再次夹紧，不能把测试升级写成正常奖励。学习测试如需额外点数，必须另启明确标记的测试点池，消费与正常earned/spent账本分开，关闭后重新校验技能资格，不默默退款或改写购买历史。

测试等级的可选范围从当前内容的等级支持范围取值，源缺失则拒绝超出已支持区间。历史怪物倍率作为用户指定测试项保留标签，正常模式必须读取正式 MOB/成长公式；倍率在下一次新副本生效，旧副本保留已实例化 HP。

## 4. 未知规则与可切换方案

每条策略登记稳定 ID、ruleId、名称、证据类别、源profile适用条件、参数、推荐依据、未决条件、可切换时点和存档影响。策略只能选择已经真实实现的候选，不显示虚假可用选项。默认采用当前版本证据最贴近的方案；来自其他版本/服务器/安卓的公式必须标明差异。

候选对象优先包括：MP/CD端点插值与取整、属性/伤害修正顺序、攻速组合、未知受击暂停分配、NPC语音冷却、物件旧payload生命周期、未知UI布局。每项提供相同输入下的中间结果差异，便于用户识别；不将所有未知都强制泛化成可组合开关，非法组合由兼容条件拒绝。

策略字段引用[统一推荐决策](appendices/recommended-decisions.md)中的稳定ID，例如D06/D07等级与学习、D18双窗口和锁定、D19冷却、D20历史倍率。存在多种有依据的解法时分别描述；只有一个可行解法时标为单一推荐并列未知条件，不凑造替代方案。

切换分三类：纯显示下帧生效；局部可重算数值在下个边界生效；影响技能阶段、实体出生、拓扑或存档解释的方案仅新会话/新副本生效。界面同时显示 selected 与 effective，禁止在半次攻击中更换伤害公式。切换方案不改 PVF 原字节，不覆写证据分类。

## 5. 保存、反馈和诊断

保存测试配置到独立 beta-settings，包含 schemaVersion、选定profile及策略；载入后总开关仍关闭。存档记录实际生效策略版本与测试污染标记；跨profile迁移必须验证，不将未知字段丢弃。关闭测试不删除正常角色进度，也不把测试等级伪装成正常升级奖励。

反馈包包括 build/version/hash、PVF/静态资源身份、有效策略/待生效策略、设置、实体与副本身份、随机状态、最近输入/命令/事件环形缓冲、属性流水和诊断。用户主动截图时保存真实主窗画面，截图失败单独报告。报告落项目 D 盘，运行日志有大小与数量上限；源数据、用户存档和既有失败证据不自动清理。

调试数值可导出计算明细但不输出无关环境变量或本机敏感文件。界面应提供“恢复默认测试设置”与“复制本次反馈编号”；后者只复制本地文字，不自动向外发消息。

## 6. P17 子任务及验收

P17.1 管理命令与结果、测试设置schema；P17.2 双窗口事件/renderer/焦点；P17.3 正式属性与技能接口接入；P17.4 策略注册和生效时点；P17.5 反馈导出、自动测试及用户操作说明。

自动测试：默认关闭、HP/MP各自独立、HP锁仅存活者补满且死亡不复活、MP锁补满但单次花费>maxMP仍拒绝、未学技能在无CD下仍拒绝、无CD期间仍记录/推进正常CD且关闭恢复剩余值、锁HP仍受击、等级下降夹紧、debug等级不改变earned SP/TP且测试点池分账、等级设置不发奖励、重复requestId仅一次、过期generation拒绝、暂停管理不增加tick或推进CD、单步恰一tick、策略延迟生效、窗口关闭不退出主游戏、主窗失焦清键/两窗均失焦才暂停、重载不默开测试。人工由用户检查双窗口DPI、输入法、可读性、策略差异及实际手感；交付报告明确区分未测试项。
