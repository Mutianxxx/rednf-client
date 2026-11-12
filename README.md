# DNF 1031 客户端复刻研究（dnf-c++-project）

一个**独立、干净室（clean-room）**的 C++ 工程，用来研究并复刻《地下城与勇士》（Dungeon & Fighter / DNF）
**清风 1031** 客户端的行为——不是重打包、不分发游戏资源，而是把客户端的**数据格式、状态机、动画链、技能特效、
判定与输入指令**用可复现的代码重新表达出来，并逐条标注证据来源。

> 本仓库**不包含**任何客户端资源（`.pvf`、`.npk`、贴图、音频、可执行文件）。运行前请自备你有权使用的
> 清风 1031 客户端。仓库只保存解析器、行为模型、逆向证据与测试。

---

## 这是什么 / 为什么

官方客户端的行为大量藏在**闭源可执行文件 + 加密资源包**里，没有公开的语义文档。本项目把这条链路拆开：

- **PVF 资源包**：格式解析（字符串表、脚本 token、`.ani` / `.skl` / `.chr` / `.obj` / `.als`），
  还原每个技能的**身体动画链、特效层、粒子、攻击框、输入指令**。
- **`DNF.exe` 静态逆向**：从磁盘明文代码段提取 `setState` 分发表、`skill_id → state → 动画索引` 的绑定，
  以及技能 handler 里**攻击判定选择器**（ATK selector）的调用——这是 PVF 里没有、只能从 exe 拿到的信息。
- **可游玩复刻**：一个原生 C++ 世界，按解析出的数据播放技能动作、特效与判定，供逐帧核对。

一句话：**让「这个技能为什么长这样、判定在哪里、怎么按出来」变成可读、可测、可复现的代码，而不是口口相传的玄学。**

## 证据等级（本项目最重要的约定）

任何结论都按下列顺序取信，低等级**不能**覆盖高等级：

1. **基座 PVF 字节 + 实机效果** —— 清风 1031 的一级证据。
2. **exe / 运行时直证** —— 静态扫描或运行期 dump 得到的分发表、调用点、立即数。
3. **40JP / 60US 等逆向源码、社区格式文档** —— 只用于解释机制，不作为本客户端的结论。
4. **重建参数** —— 资源里根本没有的数值（球心半径、转速），由代码给出并**逐条标注 `reconstructed`**。

代码中每个技能映射都带 `evidence` / `confidence` 字段说明它属于哪一级；缺证据就留空，**不拿相似名字硬猜**。
已知冲突、未恢复项集中记录在 [`PROGRESS.md`](PROGRESS.md) 与 [`knowledge/INDEX.md`](knowledge/INDEX.md)。

## 目录结构

| 路径 | 内容 |
| --- | --- |
| `project/` | 独立 C++ 工程：`include/dnf/`、`src/`、`tests/`、`tools/` |
| `project/tools/skill-bindings/` | exe 技能绑定提取器 + 证据 JSON（见下） |
| `knowledge/` | 客户端/PVF、逆向、安卓与历次验证成果；带来源、版本、证据级别与已知冲突 |
| `checkpoints/` | **全部编译产物**（`build/`、`tests/`），已 `.gitignore`，可随时重建 |

## 快速开始

**构建**（需要 CMake + Ninja；Python 3 跑构建脚本）：

```bash
cd project
python -X utf8 -B tools/build.py --build-dir ../checkpoints/build --test-dir ../checkpoints/tests
```

产物写入 `checkpoints/build`，回归输出写入 `checkpoints/tests`（均在仓库内，已被忽略）。

**技能预览器**（逐个技能播放身体动作 + 特效 + 攻击框）：

```
Play-Skill-Preview.cmd            # 仓库根
project/Play-Skill-Preview.cmd    # 或这里
```

**可游玩主游戏**（默认带 `--unlock-all-skills`，方便一次放完所有技能）：

```
project/Play.cmd
```

需要本机已配置清风 1031 客户端路径（`project/content-profile.json` / `toolchain.local.json` 绑定）。

## 技能预览与主游戏

预览器按 1031 的**三类来源**还原每个技能：

- **本体动作** —— CHR `[etc motion]` / `[buff|back|jump motion]` / `animation/*.ani` 按阶段拼链；
- **特效** —— `sqr` 脚本声明、`effect/animation/<skill>/` 技能目录、`passiveobject/.../<skill>.obj`
  的 `[etc motion]` / `[basic motion]` / `[string data]` 粒子；
- **攻击框** —— ANI 内盒，加上 exe 攻击判定选择器证据（见下）。

1734 行技能里 A 264 / B 287 / C 170 / D 1013；D 全部是被动技能，主动技能没有「无资源」项。

**特效时间轴。** 父动画带 `.als` 旁挂脚本时，层由 `[add] <帧> <层号> <实例名>` 在源帧出生、
`[remove]` 收回，`[create draw only object]` 还带显式 XYZ 偏移——这是源数据而非推断。无旁挂脚本的职业
按文件名词里的释放阶段（ready / throw / blast / light / tail / finish …）与动作链段数分摊，`evidence` 写入
「no ALS sidecar」。技能释放链是**状态机不是一条带子**：exe 的 `setState` 表给出各 state 的入口 motion，
CHR motion pool 给出玩家输入驱动的子动作；输入等待态（如 `guard.ani` 两帧各 10000ms）是 hold 哨兵，
不计入动作时钟（见 `ChainSlotRole::ExternalHold`）。

**脱手技能。** 施放后留在场上的实体（念气环绕的球、千莲怒放的花、极·鬼剑术悬空的剑）单独成层；
实体数量来自资源结构，球心半径/转速/剑间距这类资源里没有的参数标注为重建。

## 判定与指令：从 exe 找证据

技能的「打哪儿、什么时候打」和「怎么按出来」在 PVF 里只有半份答案，剩下要从 `DNF.exe` 补。

- **判定（攻击）** —— 每个技能的 `setState` handler 会调用攻击判定选择器 `0x70213F`，其第一个立即数是
  该技能 `.atk` 里的攻击序号。`project/tools/skill-bindings/src/extract_judgment.py` 扫描
  `evidence/state-handler-events.json`，把 `state → handler → 攻击序号 + 调用点地址` 关联到具体技能，
  产出 `evidence/judgment-events.json`。共享 handler 的条目标 `shared_handler`（运行时靠 skill_id 选 `.atk`）。
- **指令（操作指令）** —— `.skl` 的 `[command]` / `[command key explain]` 是按键序列的权威来源
  （如鬼斩 `↑(按住)+Z`、极·鬼剑术 `↑↑↓↓+Z`）。`extract_commands.py` 从 1031 `Script.pvf` 抽取全部
  781 个带指令的技能，产出 `evidence/skill-commands.json`。exe 侧消费该字段的解析器**尚未解码**，
  因此指令证据标注为「PVF 源数据 + exe 由 state-handler 关联校验」。

两者在解析时按**技能 stem** 并入 `SkillVisualMapping`（`exeJudgments` / `command`），
并写入 `audit()` 输出，供核对与后续渲染消费。

### 盒子类型：14 是受击，15 才是攻击

当前解码样本中，角色 `attack1.ani`、`hardattack.ani` 含 type-14（受击）盒，未见 type-15；
被动对象剑气 `hundredswordhit.ani` 含 type-15（攻击）盒（3 个 532×62 大盒），
冰箭 `00_arrow_normal.ani` 也含 type-15（81×20×32）。这些样本尚不能证明全包角色动画都没有攻击盒。

这些对象的攻击体积需要通过对象动画与 ATK 接入判定；只检查 body 动画会遗漏相应攻击。
具体技能的对象生成时机、攻击身份与生命周期仍需沿 PVF 引用和 exe 派发逐项核对。

映射层因此把被动对象的一次性 motion（`[basic motion]` + `[attack info]`）也收进
`effectLayers`，并标 `attack` / `attackInfo`：这些层按 body 的挥砍阶段展开（每次挥砍一个对象实例，
这是对未恢复的「生成对象」命令的**重建**），其 type-15 盒就是判定体积。

### 投掷物：先核对 NUT 明示的运动，再补宿主派发

男法冰魄之弓的 NUT 脚本提供了运动与销毁参数。以下是该技能的局部证据；
对象创建、宿主 API 和状态派发仍需要运行时及 exe 证据核对，不能推广为全部投掷技能的完整实现：

```squirrel
// sqr/character/atmage/brokenarrow/po_atbrokenarrow.nut
local v  = sq_GetUniformVelocity(0, dis_x_len, currentT, fireT);  // 匀速直线
local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);      // 按朝向推进
sq_setCurrentAxisPos(obj, 0, dstX); ...
if (currentT >= fireT) sq_SendDestroyPacketPassiveObject(obj);    // 到点销毁
// sqr/character/atmage/brokenarrow/brokenarrow.nut
// 炮口偏移 (65, 0, 73)，无锁定目标时 xLen = 400，fireT = [static data][0]
```

映射层把「单帧循环 + 有 `[attack info]`」的对象识别为投掷物，按 `fireT` 匀速推进
`xLen` 距离并用子弹自己的 type-15 盒判定。参数来自该技能脚本；**其他职业的投掷参数尚未逐个核对**。

## 重新提取 exe 绑定

```bash
python -X utf8 -B tools/skill-bindings/src/gen_exe_bindings_header.py   # 生成 include/dnf/skill_exe_bindings.hpp
python -X utf8 -B tools/skill-bindings/src/extract_judgment.py          # 判定证据
python -X utf8 -B tools/skill-bindings/src/extract_commands.py          # 指令证据（需 1031 Script.pvf）
```

需要：清风 1031 `DNF.exe`（只读）、1031 `Script.pvf`、Python 3 + capstone 5.0.7、Node 22。
详见 [`project/tools/skill-bindings/README.md`](project/tools/skill-bindings/README.md) 与 `REPORT.md`。

## 技能调用链补全计划

执行顺序与修改范围见 [SKILL-RUNTIME-PLAN.md](SKILL-RUNTIME-PLAN.md)：
P0 引用闭包与现有 ACT 消费者 → OBJ/NUT 生命周期；P1 ALS、ATK、PTL；P2 SKL 与跨系统表族。
每步区分静态候选、编译准入、实际 World 执行与基座实机核对，分别记录测试和 git 同步状态。
现有工程已包含 ACT 编译/调度/部分 World 消费者及 PTL 解析/预览子集；P0-2 已接通 `CREATE PASSIVEOBJECT` 的受控 World 对象工厂（仅在 OBJ 依赖闭包含已消费的 ANI/ATK 叶子时），粒子派发、预警贴花与技能调用链仍缺。

## 已知边界（不要当成已完成）

- **ACT 对象工厂是受控子集**：`CREATE PASSIVEOBJECT` 已能在真实 World 生成/回收实体，
  但只有当 OBJ 的字面依赖闭包含已消费的 ANI/ATK/IMG 叶子时才准入。含 `.ptl`、
  `[basic action]` ACT 递归、注册表缺失的对象继续显式阻塞；预警贴花
  （`[WARNING MARK]`）、PTL 粒子工厂、type15 攻击身份/配对 ATK 与对象的
  运动/命中/伤害闭环**未**恢复。静态 `ok` / `runtime_ready` 只是准入旗标，
  不等于 World 执行或 1031 原版表现一致。详见
  [`project/reports/pvf-audit/README.md`](project/reports/pvf-audit/README.md) 第 6.2 节。
- 攻击判定选择器 `0x70213F` 位于 Themida VM 区，**立即数 → `.atk` 文件名的翻译未恢复**；
  exe 目前只提供「哪个 state 打、打第几个攻击」。角色 body 技能的攻击盒几何在 1031 里
  **不在 PVF**（body ANI 只有 type-14 受击盒），需要继续从 exe 的攻击盒构造点取证；
  依赖被动对象的技能（剑气、冰箭、投掷物）已能靠对象自身的 type-15 盒判定。
- 投掷物的射程/时间取自**该技能自己的 nut 脚本**；其他职业（枪手子弹、男法其他投掷）尚未逐个核对，
  未核对的一律按「单帧循环对象 + `[static data][0]`」的通用规则处理，属重建。
- `ratePercent` 帧延时缩放、`delayed-add` 出生偏移策略未恢复，预览器时间轴是**名义时钟**（裸 `[DELAY]` 累加），
  只在相对顺序上等价，绝对毫秒不保证与原游戏一致。
- 盗贼区动作索引映射未闭合；创造者（creatormage）无原生 setState 控制器。
- 非剑士系 `common.nut` 无 `sq_LoadSkillEffect_*`，效果链只对剑士系成立。

## 贡献

欢迎提交可复现的解析/证据/测试。约定：

- 新结论必须标注**证据等级**（`evidence` / `confidence`），不得用相似文件名推断冒充源数据。
- 缺证据就留空并写进 `missing`，不要「看起来对」地填充。
- 涉及本客户端的事实，以**清风 1031 PVF 字节 + 实机**为准；跨版本推断必须显式标注版本。
- 编译产物、客户端资源、`.pvf/.npk` 一律不入库。

## 许可与免责

仅用于**个人学习与互操作研究**。不提供、不分发任何客户端资源；请自备合法客户端。
资料归档不等于原生语义或游戏功能已验收；代码迁入不等于架构重构已完成——以实际编译、自动检查与体验记录分别说明状态。
当前阶段与恢复入口见 [`PROGRESS.md`](PROGRESS.md)。
