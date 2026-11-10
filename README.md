# DNF C++ 重构工作区

仅用于 dnf 客户端复刻尝试，不提供任何客户端资源，基于清风 1031 版本，可自行下载查看。

创建日期：2026-11-02。按用户授权，在独立目录实施面向对象架构重构。

本目录只有两个业务子目录，外加一个编译产物目录：

- `knowledge/`：客户端/PVF、逆向、安卓与历次运行验证成果；保留来源身份、版本、证据级别、已知冲突和未完成项。
- `project/`：独立 C++ 工程、测试与源码。
- `checkpoints/`：**全部编译产物**（`build/` 构建目录、`tests/` 回归输出）。已被 `.gitignore` 排除，可随时重建。

当前阶段和恢复入口见 [PROGRESS.md](PROGRESS.md)。原始 `dnf-native-demo`、客户端、知识库、用户存档和历史候选保持原位。

资料入口：[knowledge/INDEX.md](knowledge/INDEX.md)。体验入口：根目录 `Play-Skill-Preview.cmd`
（或 `project/Play-Skill-Preview.cmd`，技能预览器）；源码增量构建入口：`project/Run-From-Source.cmd`。
构建命令：`cd project && python -X utf8 -B tools/build.py --build-dir ..\checkpoints\build --test-dir ..\checkpoints\tests`。

## 技能预览覆盖

预览器按 1031 客户端的三类来源还原每个技能：**本体动作**（CHR `[etc motion]` / `[buff|back|jump motion]`
/ `animation/*.ani` 按阶段拼链）、**特效**（`sqr` 脚本声明、`effect/animation/<skill>/` 技能目录、
`passiveobject/character/<job>/<skill>.obj` 的 `[etc motion]`/`[basic motion]`/`[string data]` 粒子）、
**攻击框**（ANI 内盒 + 少量手工重建）。1734 行技能里 A 264 / B 287 / C 170 / D 1013；D 全部是
被动技能，主动技能没有「无资源」项，仍有 187 个主动技能只有动作、没有特效（召唤物、平砍、Buff 为主）。

已知限制：特效层没有源时间轴，预览器把所有层从第 0 帧同时播放；部分技能的特效名与技能名不同，
靠显式别名表（如 念气罩 `nenguard→nenshield`）兜底。逐项状态见 [PROGRESS.md](PROGRESS.md)。

技能行为族和 40JP 复用实现思路见 [交接说明](project/docs/SKILL-BEHAVIOR-FAMILIES-40JP.md)。

资料归档不等于原生语义或游戏功能已经验收；代码迁入不等于架构重构已经完成。以实际编译、自动检查与用户体验记录分别说明状态。
