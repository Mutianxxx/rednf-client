# DNF C++ 重构工作区

仅用于 dnf 客户端复刻尝试，不提供任何客户端资源，基于清风 1031 版本，可自行下载查看。

创建日期：2026-11-02。按用户授权，在独立目录实施面向对象架构重构。

本目录只有两个业务子目录：

- `knowledge/`：客户端/PVF、逆向、安卓与历次运行验证成果；保留来源身份、版本、证据级别、已知冲突和未完成项。
- `project/`：独立 C++ 工程、测试、构建缓存、产物和逐节点备份。

当前阶段和恢复入口见 [PROGRESS.md](PROGRESS.md)。原始 `dnf-native-demo`、客户端、知识库、用户存档和历史候选保持原位。

资料入口：[knowledge/INDEX.md](knowledge/INDEX.md)。体验入口：`project/Play-Skill-Preview.cmd`（技能预览器）；
源码增量构建入口：`project/Run-From-Source.cmd`。构建缓存、测试报告与节点检查点均为可重建产物，
2026-11-08 入库整理时已清理且不再入库。

技能行为族和 40JP 复用实现思路见 [交接说明](project/docs/SKILL-BEHAVIOR-FAMILIES-40JP.md)。

资料归档不等于原生语义或游戏功能已经验收；代码迁入不等于架构重构已经完成。以实际编译、自动检查与用户体验记录分别说明状态。
