# DNF 独立客户端技术方案与执行计划

方案版本：**v1.1**。整理日期：**2026-10-18**。目标客户端：**v0.1 beta**。

本目录是后续编码的技术与执行依据，已将会话中的完整方案按模块落盘并补充接口、生命周期、伪代码、错误处理、任务依赖和验收。**文档完成不代表功能已经实现**；当前游戏基线仍以 [CURRENT_TASK](../dnf-native-demo/CURRENT_TASK.md) 的实际构建记录为准。本轮只制作和核验方案，不启动前台试玩。

用户已确认：十个非缔造者职业及当前1031实际开放的转职、觉醒、主动／被动技能作为最终交付门槛；区域按运行能力开放，不再固定洛兰白名单。技能与装备优先，必要业务UI可用，精细UI图层复现暂缓。允许明确标注的经验推理和可切换候选策略。前台效果、手感与原版动态比较由用户执行。

## 阅读顺序与模块导航

| 文档 | 内容 |
|---|---|
| [00 范围、基线与证据](00-scope-baseline-and-evidence.md) | 十一条用户原则、来源优先级、旧约定覆盖、当前实现与门槛 |
| [01 架构与公共契约](01-architecture-and-contracts.md) | 层次、身份、公共接口、线程、错误模型、25类系统边界 |
| [02 内容加载与版本](02-content-loading-and-versioning.md) | PVF／静态资源分离、无损解析、缓存、能力图、版本切换 |
| [03 模拟、输入与动作](03-simulation-input-and-actions.md) | 固定tick、状态提交、独立时钟、事件、运动及生命周期 |
| [04 职业、技能与脚本](04-characters-skills-and-script-host.md) | 十职业、学习／释放、Squirrel宿主、ACT与原生控制器 |
| [05 属性、装备与战斗](05-stats-equipment-and-combat.md) | 成长、modifier、武器攻速、装备实例、伤害和受击 |
| [06 世界、副本与碰撞](06-world-dungeons-and-collision.md) | 全域索引、准入、拓扑、地图层、XYZ与通行 |
| [07 怪物、物件与粒子](07-monsters-objects-and-particles.md) | AI、召唤、物件工厂、PTL、死亡和payload |
| [08 NPC、任务与经济](08-npc-quests-economy-and-services.md) | 对话、任务、商店、维修、加工、掉落及本地服务 |
| [09 渲染、UI与声音](09-rendering-ui-and-audio.md) | DrawCommand、布局／点击、文字、中文输入及音频事件 |
| [10 存档与迁移](10-persistence-and-migration.md) | 原子事务、幂等、故障恢复、内容隔离与多角色 |
| [11 Beta工具与策略](11-beta-tools-and-rule-strategies.md) | 独立窗口、测试命令、候选切换、反馈与诊断 |
| [12 平台、构建与发布](12-platform-build-and-release.md) | 端口接口、预算、D盘构建、隔离发布和manifest |
| [13 执行与验收](13-execution-plan-and-acceptance.md) | P00–P19工作包、依赖、阶段门槛、完整验证矩阵 |
| [核心伪代码](appendices/core-pseudocode.md) | 来源编译、能力传播、模拟、技能提交、命中、事务及恢复 |
| [推荐决策](appendices/recommended-decisions.md) | 当前未知点的默认方案、替代项、生效边界和验证方法 |
| [完整性核对](appendices/completeness-review.md) | 对上一方案的补足、审阅结果和未消除的研究缺口 |

机器清单：[证据索引](appendices/evidence-index.json)、[模块覆盖](appendices/module-coverage.json)、[用户要求映射](appendices/requirements-traceability.json)、[任务图](appendices/task-graph.json)、[技能覆盖schema](appendices/skill-coverage.schema.json)、[文档验证报告](verification/plan-validation.json)。这些是方案清单，不是游戏已实现报告。

## 使用规则

1. 先读00、01、02与对应模块，再按13领取任务；共享接口先落实，不能为每个职业复制整套世界和伤害系统。
2. 来源字段从当前PVF／资源读取，代码执行通用语义；必要的专用行为集中在有依据的适配层，不把大量源值搬到JSON后冒称通用。
3. 事实、推荐设计、推理和用户测试调整分别记录。代码实现状态、自动测试、用户试玩和原版一致性分别记录。
4. 不以禁用必需技能或任务链通过最终十职业门槛。可选区域受能力限制时公开完整原因及后续任务。
5. 旧GBA实现及派生资产禁止参考／复用；DFQ仅机制参考，禁止UI；原资料、原客户端和用户存档保持保护。
6. 本目录术语定义与跨模块默认策略以01及推荐决策为准；模块正文给出具体实现合同。修改默认方案时同步任务、覆盖和验收记录。

## 方案验证

在项目根运行以下命令，只检查文档、机器清单、依赖和来源定位，不运行游戏：

```powershell
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B dnf-native-build-plan/tools/verify_plan.py
```

验证产物位于本目录 `verification/`。自动检查覆盖文件链接、JSON结构、十一条原则与25类系统映射、任务图无环及来源文档哈希；语义完整性另外记在完整性核对文档中。自动通过不表示所有原版算法已经查明。
