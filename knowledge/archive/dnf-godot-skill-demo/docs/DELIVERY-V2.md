# Godot 来源目录与通用执行器 V2 交付及恢复记录

状态：`runnable-review-build`。可交互版本和自动验证完成；全角色全技能目标仍未完成。

冻结体验：`D:\dnf-rebuild\dnf-godot-skill-demo\checkpoints\20261021T123458Z-godot-source-catalog-v2/runtime/Play.cmd`。
备份根：`D:\dnf-rebuild\dnf-godot-skill-demo\checkpoints\20261021T123458Z-godot-source-catalog-v2`。
其中 `source-assets-evidence.zip` 包含源码、资源、来源原字节、知识复核、报告及项目本地skills；`MANIFEST.json` 保存成员与产物哈希。
`runtime/` 包含独立Godot、编译PCK、冻结目录资源包和启动器；可变资源只写 `runtime/cache/`，日志写 `runtime/logs/`。

已完成：全库复检；完整注册目录；通用ANI/装备/ALS/世界特效/XYZ判定与反应；有界源程序VM；两条源脚本完整闭包；声音/震屏消费者；按需动作/资源/UI；源布局和radio；实际编译与渲染；冻结启动和深层工具导出。

验证：来源23,395/0；战斗78/0，VM35/0，ALS16/0，帧声音11/0，实际源程序14/0；UI8/0；目录渲染83/0；PCK19/0；实际编译画面9/0；冻结启动8/0；独立按需导出成功。
构建/测试日志保留环境根证书读取错误、原OGG注释格式警告及部分快速headless退出清理警告，不能只用外层PowerShell退出码代替收据。
原测试准备失败与修正日志也保留：不把固定6秒上限推广到原ANI等待帧，不把headless尝试当作画面验收。

真实范围：11角色、1,430动作、1,734技能登记；2 executable、52 partial、665 active缺native caller、1,015 passive缺消费者；322UI目录。
圣职旧API别名现由目录和编译器共用，恢复10条有精确常量动作调用的注册技能映射；两条动态/无同类调用仍不猜测。

未完成：全部技能闭合、原生普攻等待/取消/续段规则、所有复杂PO/APD/PTL、完整公式/被动/装备消费者、全怪物AI装备与UI业务、字体复刻，以及用户视觉/听音/手感/原版对照。

恢复顺序：
1. 先读本项目AGENTS、上级agent.md、CURRENT_TASK、README及 `reports/DELIVERY-V2.json`，核本checkpoint MANIFEST。
2. 依据用户体验反馈扩展通用typed状态包/子状态/变量/helper和受限控制流，接每PO同一VM、动态运动/目标/命中回调和appendage。
3. 原生职业入口从当前版本证据恢复后进入同一IR；禁止按技能名/ID猜动作或手写专用控制器。
4. 每个能力组做实际消费者和相关测试后再增加executable；UI native调用和完整被动保持具体缺口。
5. 主C++项目继续暂停只读，不自动迁移。前台体验后由用户决定是否继续。

原客户端、知识源、历史候选和用户存档未修改。共享串行锁仅由持有者释放；恢复前检查实际进程和锁，不删除他人token。
