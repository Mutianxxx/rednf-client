# 当前 M1.1 原版窗口布局体验节点（2026-11-02）

状态：本轮已编译并完成自动验证，备份由 `port_m1/checkpoints/LATEST.json`
选定。**后续移植暂停，等待用户体验反馈；不得自动开始下一节点。**

入口：`D:\dnf-rebuild\dnf-godot-skill-demo\port_m1\Play-UI-Trial.cmd`。
候选：`port_m1/cache/releases/20261101T220952979789Z-m1-ui-trial`。
源码入口：`port_m1/Play-Source.cmd`。说明：`port_m1/docs/M1-UI-TRIAL.md`。
报告：`port_m1/reports/m1-ui-validation.json`；26 份证据按哈希随检查点保存。

本轮优先当前 PVF 原版窗口布局及图片，完成 CMD 可见加载/错误窗口、1..99
隔离测试等级、测试学习/绑定、F1 按键说明、HUD、装备背包、技能、NPC/商店/
任务/副本操作面板。桥接 11、源码 UI 32、冻结 UI 34、启动契约 5、最终启动器
5、源码 CMD 3、最终 CMD 4 项通过。修复扫描码误用导致键盘不生效、默认诊断
窗口遮挡、测试栏溢出，以及源码启动器编译成功误报失败。

实际冻结 Godot/bridge 退出 0；最终 CMD 真实启动到窗口就绪并保存退出 0。
PowerShell 无法读取 GUI 进程码的情况保留 null，以世界/事件/隔离存档收据
记录关闭。原版动态、听音和手感仍待用户，不将自动截图当作用户验收。

完整技能树位置、装备纸娃娃、未知 UI ACT、原始数字字体、副本气泡仍有缺口；
普通 NPC/商店/任务源布局缺失或为空的部分明确重建。仍为 Godot 前端与冻结
Mage457 C++ 规则核心，不声称全部职业技能/副本或独立 Godot 全移植完成。
恢复先核验 LATEST 中的 MANIFEST 哈希和备份 PROGRESS；只按用户反馈继续。

# 历史：Godot / C++ 移植 M1 体验节点（2026-11-02）

状态：M1 独立体验版已完成自动验证，当前暂停后续移植，等待用户前台确认。
候选：`D:\dnf-rebuild\dnf-godot-skill-demo\port_m1\cache\releases\20261101T211445787722Z-m1-beta-ready`。
体验说明：`dnf-godot-skill-demo\port_m1\docs\M1-DELIVERY.md`。
验证报告：`dnf-godot-skill-demo\port_m1\reports\m1-beta-validation.json`。
检查点：`D:\dnf-rebuild\dnf-godot-skill-demo\port_m1\checkpoints\20261101T212330532318Z-m1-beta-final`；恢复前核对 `port_m1\checkpoints\LATEST.json` 中的清单哈希。

最终 EXE 已从发行目录启动 Godot 4.7.2，PVF/静态资源加载到 100%，C++ 核心连接就绪；关闭主窗口后启动器退出码为 0，世界、事件和独立角色存档收据齐全。桥接集成 8 项通过，包括技能命中造成怪物 HP 下降及客户端资源哨兵未变化。自动截图接口在本执行会话不可用，画面、音频和手感仍待用户体验。

用户补充的 NPK 文件名线索已实现为 `npk-skill-name-hypotheses.json` 推测清单：346 个技能候选、293 个唯一 NPK 名称候选，依据为 SKL 路径 stem 与 NPK basename 的精确词元匹配。没有证实的 PVF 引用不会绑定进运行时，UI 提示和报告均标记为启发式，不能据此宣称资源链闭合。

M1 只验证 Godot UI/绘制/音频前端与冻结 Mage457 C++ 核心之间的集成片段；职业、技能、副本和业务功能仍受该核心的真实能力限制，不是完整移植。后续动作须等用户提供视觉/音频/操作反馈后再开始。独立子项目缓存和检查点在 D 盘；主 `dnf-native-demo`、原客户端、知识库和用户存档未改。

# 最新知识审查节点（2026-11-02）

Workbench 3.1.1 与用户解压的两个外置知识库已完成全量文件/ZIP成员读取和哈希核对；相关语义复核见 `docs/WORKBENCH-311-REVIEW.md`、`reports/workbench-311-review/semantic-reading.json`，项目通用知识入口见 `../skills/dnf-pvf-knowledge/references/11-pvf-ai-agent-workbench-3.1.1.md`。节点备份以 `checkpoints/LATEST-REVIEW.json` 为入口。

本节点只更新知识审查记录，未改 Godot 战斗/UI运行逻辑、未重新编译。完整来源调用者与伤害/受击公式未因此闭合；技能数仍 2 executable / 52 partial。V3.1 体验继续等待用户前台确认，体验入口仍为 `Play-Latest.cmd`；正式原生工程 `dnf-native-demo` 保持暂停。

# Godot V3.1 按需加载与资源锁提示修复

状态：已修复、编译并完成实际界面调用链及冻结包渲染检查，等待用户体验。
启动：`D:\dnf-rebuild\dnf-godot-skill-demo\checkpoints\20261021T135632Z-godot-lazy-export-v31\runtime\Play.cmd`；通用入口：`Play-Latest.cmd`。
备份：`D:\dnf-rebuild\dnf-godot-skill-demo\checkpoints\20261021T135632Z-godot-lazy-export-v31`；源码入口仍为 `Play-Catalog-V2.cmd`。

本次用户报告“等待资源锁释放”，现场检查锁文件不存在。旧运行日志实际为
`argument --job: invalid int value: '8.0'` 或 `'0.0'`：Godot读取JSON后职业ID是float，
旧代码直接str()传CLI，Python要求int。旧wrapper又在尝试锁之前写等待状态，
参数失败只报Exporter exit 2，导致等待提示与实际错误混淆。

- 三个职业导出入口显式转为整数，技能、动作、独立ANI资源共用正确职业ID。
- 收据名包含进程ID和微秒，避免多个窗口覆写同名收据。
- 只有真正遇到锁存在才显示等待，并列持有者、PID、路径；拿到锁立即换阶段。
- 等待最多120秒，超时显示错误并允许重试；不删除他人或未知残留锁。
- 解析器stderr错误及日志路径进入主窗口/F3，失败时清理加载遮罩。
- 完成收据须等wrapper退出、释放自己的锁后才交给UI，避免连续请求交叉。

验证：Python锁/错误测试6项；实际源码UI请求26项；冻结包实际UI请求26项；
实际冻结PCK OpenGL渲染35项，全部通过。
UI请求覆盖男法技能、动作、独立资源、鬼剑士job0、真实参数错误及重试。
首轮新增测试曾暴露typed Array fixture错误及收据早于锁释放的竞态，日志已保留；
修正fixture并修复竞态后通过。没有绕过lazy_export直接调用底层导出器验收。

本次没有新增完整技能，仍为2 executable、52 partial；未闭合调用链继续只提示。
前序V3核心/来源证据保留，未因本次启动修复重复宣称全技能或全UI完成。
根证书/源OGG metadata等已知引擎消息不算用户画面或声音验收；前台体验待用户。
主dnf-native-demo工程保持暂停，原客户端/知识库/历史候选/用户存档不改。

恢复先读AGENTS.md、本文件、CURRENT_TASK.md与本节点MANIFEST.json。
检查LATEST的manifest哈希后从固定入口重现；本节点后等待用户反馈。
