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
