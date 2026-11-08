# DNF C++ 重构工程

本项目以已验证 `mage-upper457` 源码为行为基线，在独立目录进行面向对象重构。
总体架构见 `../knowledge/architecture/ARCHITECTURE-REFACTOR-OUTLINE.md`，当前恢复状态见 `../PROGRESS.md`。

## 入口

- `Play-Skill-Preview.cmd`：启动技能预览器（1031 exe 技能绑定 + PVF 动作/特效链回放），可加 `--job N --skill ID`；需先有一次构建。
- `Play.cmd`：启动本目录最近一次编译产物，不编译。
- `Run-From-Source.cmd`：从本目录源码增量构建后启动。
- `Build-And-Test.cmd`：构建并运行核心、音频、隐藏 UI 及新对象检查；不启动前台游戏。
- `build.cmd`：仅构建，可传 `--test`、`--client`、`--build-dir`、`--test-dir`。

默认内容由 `content-profile.json` 指向原始 1031 客户端，只读使用。工具链由
`toolchain.local.json` / `DNF_TOOLCHAIN_ROOT` 指定，当前复用原工程第三方编译工具；
游戏源码、SDL、zlib、patched Squirrel、ANI 原生合同均在本工程内，不编译旧项目源码。

`Play.cmd` 使用独立 `saves/refactor/`，不导入或覆盖旧用户存档。构建、临时文件、测试和
运行日志留在本目录（`cache/`、`reports/`，均不入库）；节点检查点在需要时用
`../checkpoint_refactor.py` 重新生成。切换资源可编辑独立 `content-profile.json`，或向启动脚本
追加 `--pvf`/`--resource-root` 覆盖配置；来源兼容程度以实际诊断为准。

## 当前实际拆分

- `src/app/`：入口和拥有本次运行路径/诊断身份的 `GameApplication`。
- `src/content/`、`src/resources/`：内容定义及来源资源。
- `src/simulation/`：人物/动作/职业/动画/战斗/实体/怪物/世界/成长/脚本。
- `src/presentation/`：人物、怪物、地图、特效、弹窗、HUD、声音。
- `src/render/`：SDL 绘制、纹理和字体后端。
- `src/persistence/`：保存、奖励恢复与提交。
- `src/diagnostics/`：调试与有界性能采样。

`CharacterPresentation` 已通过最小绘制接口与 SDL 分离，保留源身体、装备、时装和技能
附属层的交织顺序、时钟和偏移。`FrameStatistics` 使用预分配环形缓冲，报告明确区分
全程峰值/计数与最近窗口分位。`cmake/source-ownership.json` 记录所有实现文件的归属。

## 迁移边界

这是渐进重构：旧 `include/dnf/` 名称暂作兼容接口；`dnf_core` 暂保一个链接归档，
World 的全部公开可写状态和业务命令/只读视图尚未迁移完。目录划分和首次对象提取不代表
全部 A0–A6 或完整七/十职业内容完成。

旧工程 equipment458/459 的 23 份未验证源码差异归档在
`../knowledge/unvalidated-native-delta/`，未混入本次已验证基线。技能/UI/地图现有缺口和
旧失败继续保留；本次主要验证重构行为不退步，原版画面、声音和手感仍由用户确认。
