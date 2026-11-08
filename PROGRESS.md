# 编译产物集中到 checkpoints/（2026-11-09）

节点 `checkpoints-20261109`。所有编译产物统一输出到仓库根 `checkpoints/`，并排除入库。

- **目录**：`checkpoints/build`（CMake/Ninja 构建目录，含全部 exe/dll/静态库/`build-verification.json`）、
  `checkpoints/tests`（回归测试输出）。仓库根新增 `.gitignore` 条目 `checkpoints/`，产物不入库。
- **工具默认值**：`project/tools/build.py` 的 `--build-dir/--test-dir` 默认改为 `../checkpoints/build`
  与 `../checkpoints/tests`；`verify_architecture.py` 与 `checkpoint_refactor.py` 同步指向新位置。
  输出目录约束从「必须在 `project/` 内」放宽为「必须在仓库内」，因此 `project/build.cmd`、
  `Build-And-Test.cmd` 不带参数即按新路径构建。
- **启动入口**：新增仓库根 `Play-Skill-Preview.cmd`（转发到 `project/Play-Skill-Preview.cmd`）；
  `tools/play_skill_preview.py` 与 `Play.cmd` 优先查 `checkpoints/build`，找不到再回退旧的
  `project/cache/*-build`。
- **本次构建**：全量构建 + 12 项任务回归。编译成功（12 个二进制，`verify_architecture` pass，139 单元）；
  技能预览器测试 **37/37 通过**，截图确认鬼斩播放正常（横幅 `hardattack -> hardattackchargeafter`、分级 A）。
  12 个 core 组中 9 组失败，属既有缺口：2 组因 Windows 260 字符路径限制写不出暂存文件
  （旧路径 294 字符、新路径 283 字符，均超限），其余为未完成功能的内容断言
  （Event.ai、Fighter 源动作、空中反应 RVO 等）。明细见
  `checkpoints/tests/runs/20261108T165710083780Z/FAILURES.md`。测试临时数据已清理，
  `checkpoints/` 合计 222 MB。

---

# 入库整理：技能绑定归档 + 缓存清理（2026-11-08）

节点 `repo-cleanup-20261108`。为提交 git，把上一轮 1031 exe 技能绑定成果从工作区
`work/dnf1031-skill-binding-extract/` 收进主线，并清掉可重建的缓存/快照。

- **成果入库**：新增 `project/tools/skill-bindings/`（1.7 MB）——10 职业绑定 JSON、
  提取脚本、证据 JSON、REPORT/scope/README。生成器改为按自身路径解析输入输出，
  重跑 `python -X utf8 -B tools/skill-bindings/src/gen_exe_bindings_header.py`
  产出 `include/dnf/skill_exe_bindings.hpp`，与归档前逐字节比对**只差生成器路径注释一行**，
  8 职业 298 技能完全一致。
- **删除**（可重建，共约 12.8 GB）：`project/checkpoints/` 7 个节点快照 3.0G；
  `project/cache/` 12 个构建/测试目录 6.1G（保留当前可运行的 `cache/refactor-build` 225M）；
  `project/reports/` 的 seven-job-world / 40jp-deep-merge / knowledge-base / 40jp-review / runs 1.06G；
  29 个只含 `.characters.writer.lock` 的测试漏建目录；`project/saves/refactor` 30M；
  `tools/**/__pycache__`；`delivery/` 2.0G 协作交付包（含 690M rar）。
  工程总体积 14.4G → 1.6G（其中 `knowledge/` 1.3G 保留）。
- **入口调整**：`Play-Latest-Verified.cmd`、`Play-40JP-Merge-Candidate.cmd`、
  `LATEST_CHECKPOINT.json`、`LATEST_40JP_CANDIDATE.json` 随快照一并删除；
  体验入口为 `project/Play-Skill-Preview.cmd`（预览器）与 `project/Play.cmd`（游戏）。
  节点备份改为按需用 `checkpoint_refactor.py` 重新封存。
- 新增 `.gitignore`（cache/ reports/ saves/ checkpoints/ delivery/ 等），构建产物不再入库。

---

# 技能演示 Demo 已按 40JP 口径完成（2026-11-03）

节点 `skill-previewer-40jp-20261103`：`dnf_skill_previewer` 只含渲染与判定，时间轴为毫秒
累加、默认循环回卷；判定（攻击盒/受击盒/命中去重/闪烁）、ALS 特效子链、`.ptl` 粒子
（passive object → `.lst` → `.obj` → `[basic motion]` 可解析）、帧音效全部落地；映射新增
`auto_directory` 来源，全量 A/B/C/D = 42/133/114/1445。文档：`project/docs/SKILL-DEMO-40JP-SPEC.md`
（直证/推断/待验证逐条标注）、`project/docs/SKILL-PREVIEWER-ACCEPTANCE.md`（重写）。
测试 30 项全绿，`verify_architecture.py` 通过。截图取证在
`project/reports/skill-previewer/captures/`。入口 `project/Play-Skill-Preview.cmd`。

---

# C++ 协作交付包已生成（2026-11-03）

已整理源码模块职责、贡献流程、共享构建步骤、来源证据边界、当前能力状态和许可状态，并生成源码/文档交付包：`delivery/dnf-cpp-collaboration-20261103/` 与 `delivery/dnf-cpp-collaboration-20261103.zip`（交付物已于 2026-11-08 删除，可用 `project/tools/package_collaboration.py` 重新打包）。ZIP SHA256：`e96a2a3a54232ac845d3aaea80f6a1e68e42dd0471f0d2ae983a0aee246890e2`；包内 859 项，858 项文件哈希与 ZIP 内容复核一致，CRC 正常。

- 模块说明：`project/docs/MODULE-MAP.md`；贡献规则：`project/docs/CONTRIBUTING.md`；构建：`project/docs/BUILDING-SHARED.md`；来源边界：`project/docs/REFERENCE-BOUNDARIES.md`；能力状态：`project/docs/PROJECT-STATUS.md`。
- 打包脚本：`project/tools/package_collaboration.py`。交付包只含 C++ 源码、测试、依赖、精选分析文档及架构提案；未含客户端/PVF/NPK、ARAD.exe、完整 40JP 原始逆向工程、缓存、存档、历史候选和本机配置。包内未发现本机工作区绝对路径。
- 未运行游戏构建或测试；这是源码交付包，不是可玩版本。项目级许可证仍未指定，公开托管/再分发前需维护者确定授权。当前 40JP 女格斗体验节点仍按 `project/CURRENT_TASK.md` 等待用户反馈；本交付任务未更改游戏运行代码或该节点状态。

---

# 当前：女格斗条件特效体验候选已封存

节点 `40jp-fighter-effect-cues-20261103` 已完成实现、独立构建、变更路径专项验证和两遍哈希封存。构建收据 `project/cache/40jp-fighter-effect-cues-build-20261103/build-verification.json` 为 `build-only`；专项收据 `project/reports/40jp-deep-merge/verification/20261102T231406088866Z/execution-receipt.json` 的 core、人物表现、UI、application-profile 检查均通过。

- 本节点加入 EnergyBall 子状态/样式分支、Spire 持有目标缩放、Shoulder Tackle 命中特效，并修复目标缩放传到本帧新发布 cue 的问题。
- 专项证明当前 1031 ANI/ATK 和 World 接触适配器下 ShoulderTackleHit 有效命中只发布一次；完整回归和前台体验未执行/待用户。
- 候选 `project/checkpoints/20261102T233130091229Z-40jp-fighter-effect-cues-20261103`：3,025 个文件、509,056,490 字节、两遍哈希通过；manifest SHA256 `32612e9a6774e369d3451cc771cf64554cc7f3cb62d3e0d453fbad1450a801d6`，主程序 SHA256 `bbb049fd995b5211c5767dfcc2ca0e77dfe692bceb1a3df0576626e2719bcbdc`。当前指针见 `project/LATEST_40JP_CANDIDATE.json`，入口 `project/Play-40JP-Merge-Candidate.cmd`（两者已于 2026-11-08 随快照清理）。用户体验确认前不迁移其他职业。
- 这是 40JP 行为结构与 1031 资源的跨版本适配。45JP 资料未找到，1031 无 Fighter 专属 NUT 子树，SKL 不直接绑定 ANI；技能映射仍未完整恢复。

节点报告和恢复细节：`project/reports/40jp-deep-merge/fighter-effect-cues-20261103/PROGRESS.md`。原客户端、资料、历史候选及用户存档保护继续有效；完整技能与最终 beta 未完成。

---

# 重构进度与恢复

更新：2026-11-02。状态：独立迁入与首批面向对象重构完成，编译、自动回归和无窗口启动身份审计通过。节点封存不随源码入库（2026-11-08 已清理历史快照，需要时用 `checkpoint_refactor.py` 重新封存）；前台体验与原版动态比较待用户。

## 已完成

- 创建 `dnf-c++-project` 与 `knowledge/`、`project/` 两个业务子目录。
- 登记对象职责、来源保真、原工程保护和逐节点备份规则。
- 从已验证 457 节点按哈希迁入 816 个文件（约 33.4 MB）；125 个原实现单元按职责物理分组。
- ANI 原生合同内置到工程，不再通过相对 include 编译旧逆向目录。
- 当前未验证原工程差异 23 份归档到 `knowledge/unvalidated-native-delta/`，未应用。
- 人物表现组合对象、最小绘制接口、运行会话路径状态对象和有界帧统计已接入实际消费者。
- 新 CMD 入口、独立内容配置、构建/测试/存档路径已写入。

## 验证结果

- 资料归档完成：92,141 条来源映射，59,613 份唯一资料，去重压缩约 911 MB；全量存在性、存储/原字节 SHA256、解压与长度核验通过，11 项代表还原通过。首次共享副本清理错误及 763 份允许来源恢复证据完整保留。
- 父流程独立复核四份交接收据哈希一致；816 份导入文件中 811 份保持原字节，另 5 份为明确登记的 include/入口/人物表现委托修改。
- 构建/回归会话 `26756` 已退出 0；日志：`project/cache/refactor-build-attempt2.log`（PowerShell UTF-16LE）。
- 首次编译失败于新增测试辅助函数名与 Windows `near` 宏冲突；已改名，运行代码未为此改动。原失败保留于 `project/reports/migration/attempts/` 与 attempt1 日志。
- 主程序及全部继承测试目标编译成功；FrameStatistics、人物表现 46 项、原核心、音频 57 项与隐藏 UI 39 项检查通过。构建收据登记 181 份输出文件，不把文件数当作游戏完成度。
- 归属检查通过：128 个实现单元有明确归属，126 个接入编译；另 2 个原基线闲置单元保留并明确登记，未计为运行实现。
- 构建状态、精确源码/产物/静态库/报告哈希及同一内容身份：`project/cache/refactor-build/build-verification.json`，状态 `pass`。
- 无窗口 `--profile-audit` 已退出 0：`project/reports/migration/application-audit/run.json`；同一 EXE、PVF 和静态资源身份与自动回归一致。此模式不启动前台，也不验证实际游玩。
- 主程序 SHA256：`de5929b9377b2bcb265065174e6a72e9b534604a89f080e19473f19b7ffce687`。
- 音频检查使用 SDL dummy，不代替听音；隐藏 UI 检查不代替原版布局、画面、操作与手感确认。

## 本轮执行顺序

1. A0：归档跨来源成果，记录已验证代码基线和未验证差异。
2. A1：独立构建路径、源码职责分组、依赖与来源映射。
3. A2：提取实际运行的对象边界和组合组件，保持现有行为。
4. 编译和对应自动检查，保存节点源码/产物备份并更新恢复文档。

## 启动与恢复

- 曾封存（2026-11-08 清理，哈希留档）：`project/checkpoints/20261102T001149792676Z-architecture-A0-A2a/`；1,113 个文件，988,972,582 字节，两遍 SHA256 检查通过，封存后再次核对清单、9 个关键文件和私有启动参数通过。
- manifest SHA256：`087aaa1bc6b43c024f7707d57fb0f56e106d819f908210b6705c71fbcd323222`。备份为开发节点，`full_beta_gate_passed=false`，前台体验状态 `pending`。
- 体验入口：`project/Play-Skill-Preview.cmd`（技能预览器，需一次构建）与 `project/Play.cmd`（游戏）。
- 源码增量构建后启动：`project/Run-From-Source.cmd`；此入口使用工作源码，后续修改不自动成为已验证候选。
- 每节点备份（按需生成，不入库）：`project/checkpoints/<UTC时间>-architecture-A0-A2a/`；用 `checkpoint_refactor.py` 封存并校验 manifest。
- 节点含源码、EXE/DLL、静态库、自动报告、日志、来源收据、迁移清单和 `PROGRESS.md`。两遍 SHA256 检查后才更新已验证入口。
- 资料包独立保存在 `knowledge/`；每节点保存其清单/验证收据，不重复复制约 911 MB 的资料 payload。原客户端大文件、历史候选等按资料索引只读引用。
- 工作源码和检查点各使用私有存档。原工程、原资料、原用户存档与历史候选未覆盖。

## 后续工作

1. A0：补齐同机、同场景、同输入的真实渲染性能基线；本次有界帧统计只消除一处无界增长，不声称 FPS 已改善。
2. A1：收敛公共 ID、只读内容/资源接口、坐标和资源准备边界。
3. A2：继续提取怪物、地图、独立特效表现对象；人物表现已有真实消费者，但其他模块目前主要完成职责分组。
4. A3：共享 UI 布局/命中、独立窗口与 HUD、业务命令和只读模型。
5. A4–A6：公共动作执行/职业策略、AI意图、战斗/实体生命周期、成长/存档所有权与应用装配。

当前 `dnf_core` 仍为共同链接归档，旧 `include/dnf` 兼容接口和 World 公开可写状态尚未全部收窄。本轮不是完整 A0–A6 或全部职业/技能完成。equipment458/459 的旧堆异常仍未解决，23 份差异只归档未合入。

恢复时先读本文、`project/CURRENT_TASK.md`、节点 `manifest.json` 与验证收据，按 `project/docs/USER-TEST-CHECKLIST.md` 区分自动通过、待体验与原版对照状态；不重跑已结束构建，不把 459 差异直接合入。
