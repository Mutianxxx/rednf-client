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

**特效时间轴。** 父动画带 `.als` 旁挂脚本时，层由 `[add] <帧> <层号> <实例名>` 在源帧出生、
`[remove]` 收回，`[create draw only object]` 还带显式 XYZ 偏移——这是源数据而不是推断。旁挂脚本
只覆盖男法、男格斗等一部分职业；女格斗、剑士的技能没有旁挂脚本，此时层按文件名词里的释放阶段
（ready / throw / blast / ground / light / tail / finish / disappear）排序，并按动作链的段数分摊到
时间轴上，行内 `evidence` 写明「no ALS sidecar」。

**脱手技能。** 施放后留在场上的实体（念气环绕的球、千莲怒放的花、极·鬼剑术悬空的剑）单独成层：
念气环绕按职业给 2 球（女）/ 4 球（男）绕角色旋转，千莲怒放把 `NenFlower/Ground.ani` 作为地面
放置物留在场上，极·鬼剑术按 `HundredSwordMoveReady1..5` 的段数给出 5 把悬剑。球心半径、转速、
剑的间距在任何 PVF 文件里都没有，属于重建参数，`evidence` 逐条标注；实体数量则来自资源结构
（尾巴动画数、move 段数）。

已知限制：ALS 只覆盖带旁挂脚本的职业，其余职业的阶段时序是基于文件名的重建；层没有源绘制层号
（`layer` 为 0），只能整体放在角色前或后。逐项状态见 [PROGRESS.md](PROGRESS.md)。

**主线接入。** `src/tools/skill_preview_mapping.cpp` 已编入 `dnf_core`，`World` 在技能起手时用同一张
表补出特效层与驻留实体（`manualVisuals` 标记的手工分支除外），因此预览器与可游玩主游戏不再各自
维护一份技能特效清单。逐项状态见 [PROGRESS.md](PROGRESS.md)。

技能行为族和 40JP 复用实现思路见 [交接说明](project/docs/SKILL-BEHAVIOR-FAMILIES-40JP.md)。

资料归档不等于原生语义或游戏功能已经验收；代码迁入不等于架构重构已经完成。以实际编译、自动检查与用户体验记录分别说明状态。
