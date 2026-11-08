# 60US 三段斩：原生状态 22、PVF 槽、分段输入与武器攻击框

已将当前客户端 Swordman 技能 ID 8 的局部合同写成
[`tripleslash-contract.json`](tripleslash-contract.json)。它可以直接为独立预览提供
三段的主体 ANI、武器附层、Slash/Move 特效、ATK、等级列以及接续帧门槛。
这是有边界的静态恢复，尚未达到原客户端逐帧运动和完整命中规则复现。
没有改动 `combat-preview`、原客户端、PVF、`dnf-rebuild` 或旧分析目录。

本目录仅使用当前来源：

- EXE：`DFO/DFO_fixed_v3.exe`，SHA256
  `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`。
- PVF：`DFO/Script.pvf`，SHA256
  `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98`。
- REA 辅助：`../rea/015-state-function.c`、
  `../rea/049-swordman-command-pseudocode.c`，字节片段见本目录
  [`evidence.json`](evidence.json)。伪代码中的参数/浮点类型以实际 x86 栈和字节为准。

## 可直接用于普通三段预览的资源合同

`skill/swordmanskill.lst` 的 ID 8 指向 `Swordman/TripleSlash.skl`。
`0x7307b0` 的状态 22 入口在 `0x7329cf`，段号为零基
`actor+0x2f1c`，段数为 `actor+0x2f20`。

`0x732b19..0x732b65` 明确选取 motion `segment+3`；ATK 通常为
`segment+2`，但三段版本的末段改取 ATK 7。
下表同时受到当前 CHR 的有序 token 和原生索引算式约束，不按同名资源猜配。

| 段号 | CHR etc motion | 主体 | CHR etc ATK | 攻击参数 | 等级列 |
|---:|---:|---|---:|---|---:|
| 0 | 3 | TripleSlash1.ani | 2 | TripleSlash1.atk | 0 |
| 1 | 4 | TripleSlash2.ani | 3 | TripleSlash2.atk | 0 |
| 2 | 5 | TripleSlash3.ani | **7** | **TripleSlash3Down.atk** | 1 |

主体路径位于 `character/swordman/animation/`；ATK 位于同角色
`attackinfo/`。三个主体均为 5 帧，零基 0..4，原始 delay 为
`70,70,70,70,300`，`LOOP=0`。每段可从逻辑帧 0 建立独立预览。
主体状态切换函数中的 reset 路径确实调用 `0xa27360`，但本轮尚未闭合
pending state 请求最终应用时的 reset flag；因此合同将**身体起始帧 0**标为
独立预览选择，并单列原生调用闭环缺口。

每段同时挂接以下两个效果：

- `Effect/Animation/TripleSlash/Slash{segment+1}.ani`，attach key 2。
- `Effect/Animation/TripleSlash/Move{segment%2+1}.ani`，attach key 1。

这些格式串来自 EXE 的 UTF16 `0xd7f5c0`、`0xd7f570`，资源根由角色目录
取得，当前 PVF 中实际存在于 `character/swordman/effect/animation/tripleslash/`。
效果均有 5 帧，每帧原始 delay 70。
`0x732e41..0x732e9b` 通过虚方法 `+0xf8` 挂接，实际为
`0x4acf80 -> 0x49b7b0`；`0x49b84b..0x49b857` 无条件 reset 后更新 ANI。
`0xa27360` 将当前帧标为 -1，`0xa27f60 -> 0xa27dc0` 从首帧推进。
该效果起始 reset 链是已证实事实。末参数 1 还使 `0x4acf80` 应用角色攻击速率，
预览不能无条件以固定墙钟速度播放全部效果。

末段声音为 `SM_TRIPLE3`；其余偶数段号为 `SM_TRIPLE1`，奇数段号为
`SM_TRIPLE2`；每段还播放 `R_TSLASH`。

## 攻击框来自选中的装备附层

5 个主体、5 个 Slash、2 个 Move ANI **都没有 ATTACK BOX**。
不能为主体凭空补一个矩形，也不能由特效像素轮廓推出判定框。

本目录复用已经闭合的具体 EQU/LAY 来源作为预览装备选择：
`equipment/character/swordman/weapon/club/n_club_axshauta.equ`。
该 EQU 的 `[variation] 2 6`，两层分别为 order 650 的 `clubb` 和
order 2600 的 `clubc`；共同 include 当前 `equipment/character/swordman.lay`。
LAY 的 `etc motion[3..7]` 逐项就是 `%s/TripleSlash1.ani` 至 5。
因此这里是实际 EQU → LAY → 同一槽的路径解析，有原始 token；没有将任意
同名武器文件绑定到身体。

该装备普通三段的攻击帧如下，帧号均为零基：

| 段号 | clubb 攻击帧 | clubc 攻击帧 |
|---:|---|---|
| 0 | 2、3 | 1 |
| 1 | 无 | 1、2、3 |
| 2 | 1、2、3 | 无 |

每个盒子的原始六个值、图像模板、格式化后的 IMG 路径、源 offset、CRC/hash
均保存在合同各段 `selected_club_layers`。装备附层通过 `0x4b4a80` 挂入
身体 ANI `+0x180` 链表，`0x4ccdb0` 复制身体同帧 delay，所以装备原文件帧 4
的 70 会在运行时同步为身体的 300。附层使用身体时钟，不能独立累计原文件
delay 后提前结束。排序和 native 几何消费见：

- `../combat_native_skill_slots/hardattack-equipment-contract.json` 中通用装备绑定证据。
- `../combat_native_collision/geometry-contract.json` 中盒子变换与 AABB 证据。

这件 club 是可复现的**预览配置**，不声称为原玩家实际装备。
它也不满足下述五段武器分支，不能把它的五段资源展示称为有效五段原生配置。

## 输入接续、结束与清理

REA `049` 将命令代码归入 `0x726150`。实际字节：

- `0x72af0c`：当前状态 0、11 或 8 时，通过技能 8 的输入对象及
  `0x559140` 取得输入选择。返回 -1 则拒绝；虚方法 `+0x768(8,1,1,1)`
  成功后，请求状态 22，参数 `[0,input_selection]`，priority 1。
- `0x72afd8..0x72b0a9`：状态 22 下，要求 `segment<count-1` 且当前身体帧
  `ANI+0x124 >= gate[segment]`。`0xd79744` 的四个 int 为 `[3,3,3,3]`。
  接续输入通过后请求同状态，参数 `[segment+1,input_selection]`。
  因此第 0..3 段均从帧 3 起允许请求后续段，不能自行写成固定 210 ms；
  动画速率、暂停及帧跳转会影响墙钟时间。
- `0x72b0bb`：当前 ANI 的 finished byte `+0x13a` 非零时请求状态 0、priority 0。
  接续请求后同样会检查 finished。`0x4ed283..0x4ed295` 保留较高 priority 的
  pending 请求，因此已有 priority 1 时不会被后来的 0 覆盖。
- `+0x28c=0x4ed1d0` 是请求队列写入函数，不直接调用入态函数。
  队列参数有明确字段 `actor+0x4a0/+0x4a4/+0x4b4`。
- 旧状态 22 清理位于 `0x730b30..0x730b83`：每段退出都 detach 当前
  Slash 与 Move。只有目标状态不再为 22 时，还调用技能 8 的 `+0x72c`。
  此调用以及接续前 `+0x67c -> 0x54f270` 的具体冷却副作用未在本轮命名。

`0x4990c0 -> 0x511110` 的方向写入只接受值 0/1；入口参数第二项被送入
这个方向 setter。但前置控制/对象条件可能阻止写入，不能把任何输入返回值
无条件解释为左右。

## PVF 等级列与可选五段

SKL dungeon `[static data]` 是 `[600,-1000]`。
dungeon 和 PvP 的 `[level info]` 均为 3 列 × 30 行；表已分别导出，未混用。
dungeon 第一/末行分别为 `[100,150,200]`、`[253,379,505]`；PvP 为
`[60,90,120]`、`[152,227,303]`。

`0x732b66..0x732bb8` 对普通三段选列 `[0,0,1]`，五段选列
`[0,0,0,1,2]`。`0x732bbe` 经过 `0x4caa20 -> 0x550150 -> 0x550080`
查等级值，减 100 写当前 ATK `+0x10` 的 protected damage bonus。
随后查询 column+3 的固定伤害，按当前百分比规范化后写 ATK `+0x0`。
当前原始表只有 3 列，因此 3..5 列在基础取表阶段越界为 0；运行时属性修正
和环境修正仍是独立因素。这里不宣称完整最终伤害、取整或命中结果。

五段只在以下原生条件成立时启用：技能 27 `WeaponMasteryUp` level>0，且
武器类型 5 + 技能 4 `LightSwordMastery` level≥static[1]，或者武器类型 1 +
技能 13 `BladeMastery` level≥static[0]；相应精通等级还要求正值。
当前 PVF 阈值两者都为 5。此处保留原生类型整数，不仅凭名称为枚举赋语义。
五段 motion 槽为 3..7，ATK 槽为 2..6；末段不使用 TripleSlash3Down。
第五段还将相应精通等级列（技能 4 column3 / 技能 13 column2）写 ATK lift
`+0xf8`。相关三个 SKL 及所有列原值已纳入合同。

## 运动与定时视觉

`0x732c63..0x732cda` 的调用参数已经恢复：

1. `virtual+0x488(0,600,600,0,-1000,1)`。
2. `virtual+0x488(1,0,0,0,0,0)`。
3. `virtual+0x494(2,2,1000,1000,1.0,1.0)`。
4. `virtual+0x49c(current_direction,4,0)`。

`+0x488=0x4b9d80` 写 axis 对应的 protected velocity/acceleration 数值和标志；
`+0x494=0x4b9c60` 写运动模式和比例。尚未恢复积分器、速度归零/限速、时间
单位、障碍碰撞约束，因此不能将这些参数直接写成已证实的抛物线公式。

状态 22 的视觉 tick 可由原始 switch 表闭合：`0x7261d4` 读取 state，
`byte[0x730304+22]=7`，`dword[0x730280+7*4]=0x726c9e`。
入态把 `actor+0x2f40` 置 -200；tick 若 state elapsed≥last+200，则取全局
对象索引 2，放到 actor x±20、相同 y/z，继承方向并生成，更新 last。
因此第一轮即可触发，随后间隔 200；具体粒子资源和寿命尚未识别。
Ghidra 曾遗漏该 switch case 的函数 body，并不代表该原生分支不存在。

## 产物与复现

- `tripleslash-contract.json`：可移植局部合同。`segments_by_count["3"]` 为本轮
  普通三段；`["5"]` 仅提供已证实的选槽/列映射及资源，保留装备资格限制。
- `animations.json`：22 个选中 ANI 的完整有序字段，包括重复框、未知字段与源 offset。
- `pvf-sources.json`：36 个解密来源及 CRC/hash；旁边 `.cp949` 为原始字节，
  `.utf8.txt` 为可读副本。
- `tripleslash-animation-box-catalog.json`：限定搜索当前 PVF 路径含 tripleslash
  且后缀 `.ani` 的全部 464 个资源，其中 66 个有 ATTACK BOX。这是候选清单，
  没有把所有候选绑定到运行时。
- `evidence.json` 及 `.bin/.asm`：31 个当前 EXE 字节片段，包含字符串、vtable、
  接续门槛及 state switch 的 file offset/hash。

执行：

```powershell
python -X utf8 analysis/combat_tripleslash/build_evidence.py
python -X utf8 analysis/combat_tripleslash/build_contract.py
```

本轮验证通过 31/31 原生字节重读、36/36 PVF 源 CRC/hash、22 个 ANI 帧数和
delay 断言、dungeon/PvP 各 30 行以及 464 个候选扫描。原客户端实际输入、
最终精灵像素、完整受击/死亡和技能运动轨迹尚未运行对比，不能用这些静态检查
替代画面验收。
