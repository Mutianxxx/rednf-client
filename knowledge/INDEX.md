# 资料入口与证据边界

本库保存源资料的原字节和 SHA256。相同内容仅保留一份，大型文本使用可逆 gzip 压缩；所有原路径与实际归档路径的对应关系在 `catalog/source-manifest.json`。需要正常文本文件时，用 `tools/read_evidence.py --extract 原路径` 还原到 `reading-room/`，还原前后均校验 SHA256。

## 按领域查找

| 领域 | 原路径入口 | 使用边界 |
|---|---|---|
| 架构与迁移 | `architecture/ARCHITECTURE-REFACTOR-OUTLINE.md` | 本次 OO 设计，不是 PVF 原生格式声明 |
| 当前客户端与 PVF | `dnf-result/catalog/`、`dnf-result/inventory/` | 来源成员、哈希、编码、未知字段；静态存在不等于行为执行 |
| 技能/动画/判定/UI | `逆向部分结果参考/`、`dnf-result/research/` | 1031 静态、运行、推理分别保留，未知 caller 不自动闭合 |
| 60US 逆向 | `reverse-60us/releases/20261020-01/analysis/`、`reverse-60us/handoff/` | 跨版本参考，不能当作 1031 动态验证 |
| **40JP 逆向源码（引擎/战斗首要结构参考）** | `archive/40jp-reverse-source/`、`project/reports/40jp-review/` | 200606130k0515 日服早期客户端；用于时间域、ANI 递归、AABB、命中处理和 D3D/UI 调用结构。不能单独证明 1031 的技能数值、资源绑定或运行资格 |
| 安卓端 | `dnf-result/research/android-*`、`dnf-result/docs/12-server-and-revised-android.md` | APK 与 PC 的坐标、数值、状态编号和资源布局分别核对；APK 导入源已移出本库 |
| REP 研究 | `rep-player/rep-player-main/`、`rep-player-1031-pvf/docs/`、`rep-player-1031-pvf/validation/` | REP 渲染记录与 PVF 执行语义有区别，预览不能替代完整技能验证 |
| **PVF最高优先级知识源** | `archive/dnf-知识库/PVF-Ai-Agent-Workbench-3.1.1/knowledge-pack/indexes/knowledge-index.json` | 所有PVF任务先查索引并按主题阅读；Workbench是知识/流程首要参考，目标客户端事实仍绑定当前字节与运行消费者 |
| 其他补充资料 | `archive/dnf-知识库/pvf-utils-info/`、`archive/dnf-知识库/dnf-pvf-knowledge/`、`archive/dnf-知识库/dfo-pvf-skill-main/`、`archive/dnf-知识库/pvf官方文档/` | 作为次级参考；社区/跨版本、需验证项和冲突继续保留 |
| 项目本地知识规则 | `skills/KNOWLEDGE_POLICY.md`、`skills/*/SKILL.md` | 当前源字节及可执行消费者优先；禁止逐技能复制、DFQ UI 和旧 GBA 派生实现 |
| 历次实现与测试 | `dnf-native-demo/docs/`、`dnf-godot-skill-demo/docs/`、`dnf-result/research/` | 结论性文档与统计保留；原始 pass/fail 运行产物已按 2026-11-09 精简撤出本库 |
| 原实施范围 | `dnf-native-build-plan/` | 最终范围、公共合同与 P01–P19，不是已完成功能清单 |

## 读取示例

```powershell
& 'D:\ProgramData\anaconda3\python.exe' .\tools\read_evidence.py --find 'knowledge-base-audit/skill-audit'
& 'D:\ProgramData\anaconda3\python.exe' .\tools\read_evidence.py --extract 'skills/KNOWLEDGE_POLICY.md'
& 'D:\ProgramData\anaconda3\python.exe' .\tools\read_evidence.py --extract 'dnf-native-demo/CURRENT_TASK.md'
```

工具仅访问本资料目录，归档还原后不依赖原始工程路径。恢复出的历史脚本/配置仍为证据，不应直接执行；历史脚本可能包含原路径或固定客户端身份。

## 保留的关键事实与冲突

- 1031 PVF 的既有来源记录为 SHA256 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`；60US 记录为 `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98`。本次归档没有重新散列整份大型 PVF。
- ALS 首字段是父动画帧事件，不能当作毫秒。ANI 原始延迟、IMG 原点、局部/跟随/世界坐标分别保留。
- ATK payload、ANI 几何、攻击身份与接受命中分别建模；可视特效不是自动伤害来源。
- 40JP 资料的结构证据见 `project/reports/40jp-review/README.md`：0x4052D0/0x699000–0x699070 是 16 域积分与对象可暂停时钟，0x4938F0 递归推进 ANI 子链，0x4E62B0 以朝向镜像和 XYZ 世界坐标逐盒做 AABB，0x4D71B0 将表现/卡肉、伤害、HP、受击反应和通知串成一条命中入口。以上仅作为跨版本调用结构，参数与资格仍回到 1031 消费者。
- EQU `expand ani` 第三参数涉及攻击框选择，不能把全部身体和武器框无条件合并。
- 已有来源指出 `pushState` 第五参数、`getSitAni`、`setImageRate` 等社区解释存在冲突；按原知识审计及当前消费者核对。
- 已验证旧 C++ 体验基线仍是 `mage-upper457`。equipment458/459 的 `PAUSE-RECEIPT.json` 明确保留 `original_o3_heap_failure_resolved: false`、`formal_consumers_passed: false`、`equipment_node_complete: false`。

## 2026-11-09 归档精简

本库原样归档了四个工程的完整工作目录，其中大量内容是可重跑的运行产物和客户端资源派生文件。为控制仓库体积并避免分发客户端资源，做了以下撤出（原工程目录仍在开发机原位，可随时重新归档）：

| 撤出内容 | 规模 | 原因 |
|---|---|---|
| `dnf-native-demo/reports/`、`dnf-godot-skill-demo/reports/` | 526 MB | staging 构建树、test-attempts、截图与逐次运行产物，全部可按原工程重跑 |
| `dnf-result/imports/`（rednf / android 导入源） | 205 MB | 第三方与安卓端客户端源码导入副本 |
| 各目录内 `.skl/.ani/.nut/.aic/.equ/.lst` 等 PVF 派生文件 | 1.3 MB | 客户端资源派生内容，不在公开仓库分发 |
| `archive/40jp-reverse-source/ARAD.exe` | 3.8 MB | 客户端可执行文件，已移出仓库 |

保留的是文档、清单与统计（`catalog/`、`inventory/`、`research/` 的路径+哈希+标签元数据、各 `docs/`、`dnf-native-build-plan/`），合计约 44 MB。`catalog/source-manifest.json` 与 `archive-summary.json` 未回改，仍记录精简前的完整归档清单，按其中路径取文件时可能不存在——这是预期行为，不代表文件从未归档。

## 归档覆盖和不复制内容

最终字节数、唯一文件数及去重数量见 `catalog/archive-summary.json`；逐份 SHA256 见 `catalog/source-manifest.json`；机器可读排除清单见 `catalog/excluded-files.json`。

大型客户端/PVF/NPK、APK、用户存档、构建缓存、历史可执行候选与重复源封包保持原位。旧 GBA 实现/派生资源和 DFQ UI 禁止导入。排除目录只登记边界，不声称逐文件扫描过。图像/二进制和超限资料以清单中的具体原因说明；没有将未复制内容称为已归档。

全量文件索引、原字节保存、语义阅读、运行验收和用户画面/声音/手感验证是不同状态。新归档不会提升历史结论的证据等级。
