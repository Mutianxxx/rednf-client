# 60US 客户端逆向成果交接

2026-10-20 从 `D:/dnf/60US` 发布到本目录，供 `dnf-rebuild` 侧独立开发使用。快照保留原有 `combat-preview/`、`analysis/` 相对结构，代码与原工作区逐文件核对 SHA256；索引见 [package-manifest.json](package-manifest.json)。固定release保持只读。接入侧已完成R60-01/02/03的差异审查及隔离渲染/时钟候选，范围与证据等级见 [R60-03进度](integration/R60-03-PROGRESS.md) 和 [验证身份](integration/R60-03-VERIFICATION.json)，继续R60-04技能阶段与视觉实体。节点源码/产物/证据/SHA备份入口为 `checkpoints/LATEST.json`；1031算法复用仍是跨版本推断，完整原生技能新增0，用户画面/声音/手感与原版动态待测。

接手先读 [CURRENT_TASK.md](CURRENT_TASK.md)，再按 [PORTING_PLAN.md](PORTING_PLAN.md) 和 [MODULE_MAP.md](MODULE_MAP.md) 找到对应模块。原 P01–P19 的本轮优先级补充见 [执行计划](../dnf-native-build-plan/13-execution-plan-and-acceptance.md)，机器清单见 [60us-integration-tasks.json](../dnf-native-build-plan/appendices/60us-integration-tasks.json)。

## 已交付内容与边界

| 内容 | 实际交付 | 不能据此认定 |
|---|---|---|
| PVF 与资源 | 解密/CRC/完整路径消费、无损有序脚本、CHR/SKL/ANI/ATK、当前NPK/IMG解码 | 1031格式与60US相同 |
| 技能目录 | 六职业688条注册技能名称全部解析；原图标、中英文检索和筛选 | 688条技能完整释放 |
| 渲染 | 负弧度旋转、非均匀缩放、正常原点、RGBA调制、NONE/LINEARDODGE、连续插值 | 其他图形效果、居中原点和原GPU像素完全一致 |
| 技能片段 | 鬼斩1、三段斩手动单段3、波动爆发效果轨1 | 完整技能控制器；当前完整数仍为0 |
| 判定与运动 | XYZ几何、命中记录局部模型、自由运动/受击水平算术及原指令核对 | 几何相交等于已接受命中或真实扣血 |
| 怪物与物件 | 状态0/3/4资源选择、ACT初始BASE ANI；桶/树/草的明确事件模型；部分死亡链 | 完整受击、倒地、死亡、ACT/PTL执行器 |
| REA 与原字节 | 完整工具返回、伪代码、局部bin/asm、地址/偏移/hash、失败与限制 | 原始C++源码恢复、完整脱壳或全程序动态跟踪 |

详细实际进度见 [60US统一进度](releases/20261020-01/analysis/combat_progress/README.md)。技能32的当前PVF名称是“波动爆发”；历史报告的“裂波斩”标签仍指向同一 `class0/skill32/releasewave`，不能按显示名重新绑定。

## 运行交接预览

双击根目录的 [Start-60US.cmd](Start-60US.cmd)，默认打开 `http://127.0.0.1:8761`，与原工作区的8760端口分开。默认只读使用 `D:/dnf/60US/DFO` 中的 PVF、NPK 和当前 EXE。快照内部原 `Start.cmd` 仍保留原相对路径，不用于直接启动本交接；使用根目录包装入口。客户端及整包资源没有重复复制；移动客户端后可执行：

```powershell
.\Start-60US.cmd --client "D:\其他目录\DFO" --port 8762
```

也可以直接审计而不启动窗口：

```powershell
& 'G:\ProgramData\miniconda3\python.exe' -B -X utf8 releases/20261020-01/combat-preview/server.py --client 'D:\dnf\60US\DFO' --audit
```

预览核心只依赖Python标准库。历史静态合同会验证当前EXE/PVF身份；不能通过改hash绕过版本限制。用于导入修复版关系校验的原v3备份已包含在快照的 `analysis/unpack_attempts/001/launcher_test/`，该EXE只作为静态证据输入。不要执行其中的历史客户端恢复脚本。

## 来源、验证与复用

- 当前60US PVF：`23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98`。
- 原v3静态证据：`a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`。
- 当前导入修复v4：`bdd14a558658dd0b20def0aa9fa4b355b98855075a05ba6de7f60c4da695495e`；静态原七节一致不证明启动器替换逻辑已完全恢复。
- 1031 PVF另为 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`，六职业与十职业矩阵分别保留。

名称来自当前PVF；插值等行为来自当前EXE；预览工具界面为自写检查界面，原游戏UI绘制尚未恢复。插值原指令24组局部计算与预览一致，完整真实角色clock、hit pause和技能阶段调度尚未接入，也没有原游戏逐帧像素对照。

运行 [tools/verify_handoff.py](tools/verify_handoff.py) 可核对快照、依赖闭包、交接任务图和复制后预览API，报告输出至 `handoff/`。复制前的计划文件和原hash在 [workspace-before-manifest.json](handoff/workspace-before-manifest.json)，历史计划的既有hash差异单独记录，不把刷新基线作为验证。

未复制Ghidra/JDK、`analysis/deps`、`angr_deps`、临时分析工程和大体积内存dump。复验反汇编构建脚本需要原工作区已有的capstone/pefile及工具；日常预览、名称解析和本包API审计不需要它们。历史报告中的原绝对路径用于保留来源，不会自动改写。
