# 清风 1031 Script.pvf 全量文件类型与技能依赖审计

审计对象：`D:\dnf-rebuild\DNF1031客户端\Script.pvf`

- PVF SHA-256：`d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`
- 条目数：`334,927`
- 机器报告：`checkpoints/tests/pvf-audit/1031-pvf-audit.json`
- 审计脚本：`project/tools/pvf_audit.py`
- 技能闭包脚本：`project/tools/skill_closure.py`
- 技能闭包产物（本地可重建，不入库）：`checkpoints/tests/pvf-audit/skill-closure.json`
- 重建命令：`python project/tools/skill_closure.py --out checkpoints/tests/pvf-audit/skill-closure.json`
- 本文只描述静态字节/标签事实；“已解析”不等于“运行时语义已实现”。

## 1. PVF 实际文件类别

| 扩展名 | 数量 | 当前判断 |
|---|---:|---|
| `.ani` | 187,396 | 二进制动画；项目已能读帧、图片、帧时长、位置、盒子、属性，但 property ID 仍有未覆盖项 |
| `.equ` | 68,499 | 装备/外观配置；token 语法可读，完整字段消费者未闭合 |
| `.act` | 19,087 | 动作/行为时间轴；token 语法可读，标签 672 种，当前技能执行器只消费小子集 |
| `.stk` | 10,346 | 技能/状态/装备相关表族；token 语法可读，语义消费者未全建模 |
| `.ai` | 7,105 | AI 行为/决策表；token 语法大体可读，AI runtime 只消费部分 |
| `.obj` | 6,867 | 被动对象/动作对象定义；字段可读，但对象创建、脚本和生命周期未全执行 |
| `.atk` | 6,394 | AttackInfo 伤害/反应 payload；字段可读，但不能单独证明命中，必须结合对象 ANI type-15 盒 |
| `.key` | 5,864 | 按键/输入/绑定表族；token 可读，exe 输入消费链尚未闭合 |
| `.ptl` | 4,438 | 粒子资源/字节数据；当前只保留原始字节，未建立通用粒子解释器 |
| `.til` | 3,561 | 地砖/地图图层资源；token 可读，运行时地图消费部分已实现 |
| `.qst` | 3,222 | 任务定义；token 可读，任务消费者未全闭合 |
| `.map` | 2,948 | 地图布局/对象放置；token 可读，需继续闭合 passive object、ACT、门和碰撞 |
| `.mob` | 2,070 | 怪物定义；字段可读，AI/动作/攻击引用仍有未闭合部分 |
| `.skl` | 2,008 | 技能主定义；字段可读，技能主字段覆盖较好，但其引用的 CHR/ACT/ALS/OBJ/NUT 不是全部在 SKL 内 |
| `.als` | 1,179 | ANI 层/特效事件；已识别 `[use animation]`、`[add]`、`[remove]`、draw-only 三族；`[none effect add]` 仍未实现 |
| `.ui` | 322 | UI 布局/控件；token 可读但存在 1 个空/异常文件，完整 UI 标签消费者未闭合 |
| `.nut` | 189 | Squirrel 源脚本；文本可读，但当前没有完整 Squirrel VM/游戏宿主执行器 |
| 其余 | 约 1.3 万 | `.cre/.npc/.etc/.evt/.aic/.apd/.rep/.dgn/.gdata/.wrd/.shp/.vm/.cbt...`，大多可读 token，但语义按家族分散，不能声称全部理解 |

顶层路径最多的是 `equipment/182,503`、`monster/58,102`、`passiveobject/36,340`、`stackable/14,512`、`map/13,911`、`aicharacter/9,272`、`character/7,700`、`skill/1,976`、`sqr/189`。
因此不能只审计 `skill/`：技能实际大量依赖 `character/`、`passiveobject/`、`sqr/`、`common/` 和 `equipment/`。

## 2. 技能相关依赖闭包

对当前 1031 技能，至少必须读取以下文件族：

1. **技能入口**：`skill/<job>/*.skl`（名称、命令、等级、CD、静态参数、技能类型、状态/追加动作）。
2. **角色动作注册**：`character/<job>/*.chr`、`character/<job>/**/animation/*.ani`、`[base motion]`/动作池/装备动作。
3. **技能层特效**：`character/<job>/effect/**.als`、`character/<job>/effect/animation/**/*.ani`。
4. **脱手与被动对象**：`passiveobject/**.obj`，其 `[basic motion]`、`[etc motion]`、`[basic action]`、`[etc action]`、`[attack info]`、`[string data]`、粒子和对象注册表。
5. **攻击 payload**：对象或角色引用的 `.atk`，包含伤害反应、属性、击退、浮空、状态等；几何命中盒仍需回到 ANI 帧 type-15。
6. **行为时间轴**：`.act`，包含 `CREATE PASSIVEOBJECT`、`SUB ANI`、`PARTICLE`、速度/重力/位移、触发/条件、攻击开关、行为状态等。这是当前技能链最大的未闭合族。
7. **脚本行为**：`sqr/character/**`、`sqr/passiveobject/**` 的 `.nut`，负责对象生成参数、目标选择、移动轨迹、销毁、状态切换、攻击信息修改和自定义效果。
8. **粒子与图像资源**：`.ptl` 和 NPK/IMG。PTL 当前没有通用解释器，属于明确漏项。
9. **声音/文本/公共表**：`.etc`、`.str`、`.tbl`、`n_string.lst`、`stringtable.bin`，影响名称、音效、说明、公共枚举和脚本参数解释。

## 3.1 技能闭包扫描结果

闭包脚本不把 SKL 中不存在的 ANI/OBJ/ACT 路径伪装成直接引用，而是按以下证据合并：

- `skill/<job>/*.skl`：技能入口、命令与等级字段；
- `skill-bindings/bindings/*.json`：1031 DNF.exe setState handler 与 entry motion；
- `character/<job>`、`effect/animation`、`passiveobject`、`sqr` 的同 stem 资源族；
- NUT 源文本中的字面资源路径。

修订扫描覆盖全部 2008 个 SKL：1132 个目前仅有 SKL，876 个具其他静态资源关联，853 个关联 ANI。只有 20 个具 SKL 字面引用闭包证据（19 个具 ANI）；860 个具绑定或目录族候选。1762 条 bindings 中 1677 条匹配到本包 SKL；绑定关系仍作为独立候选，不代表已核验 state 执行顺序。

图中有 10740 个节点、16747 条边，其中 4671 条字面/sidecar 引用解析成功、121 条未解析、11955 条 IMG 引用标记 external-image（尚未证明 NPK 成员存在）。641 条 ANI→ANI.als sidecar 已递归；13692 个限定职业资源候选中 5027 个未归属。没有把全包怪物 ANI 算作技能缺失。

报告为 `checkpoints/tests/pvf-audit/skill-closure-v2.json`；内容保留全部未知/未归属清单，不截断。该结果仍是静态候选闭包，未解析数、资源关联率都不等于运行时消费覆盖率。整数对象 ID、动态名称、回调分派及 exe VM 的派发关系仍需继续取证。旧版的 1752/55365 统计口径已撤回。

## 3.2 标签审计结果

### 已能读取但只代表 token 语法

机器审计成功解析：`.skl 2,008`、`.als 1,179`、`.atk 6,394`、`.obj 6,867`、`.act 19,079/19,087`、`.ani` 使用专用二进制解码器、`.nut 189` 为源码文本。

### SKL：125 个不同标签

已观察到 `[command]`、`[command key explain]`、`[static data]`、`[level info]`、`[level property]`、`[skill class]`、`[type]`、`[required level]`、`[purchase cost]`、`[cool time]`、`[casting time]`、`[pre required skill]`、`[additional animation]`、`[executable states]`、`[pvp]`、`[active status]`、`[buff]`、`[passive]` 等。

当前已消费的主要字段是名称、命令、CD、施法时间、MP、等级信息、技能类型和部分静态数据。明显仍需逐字段核对的标签包括：`[additional animation]` 全链、`[executable states]`、`[command customizing]`、`[skill command advantage]`、`[start/end/loop addtional animation]`、`[active status buff event type]`、`[post/pre teleport]`、`[shake screen]`、`[weapon effect type]`、`[maintain MP]`、`[duration]`、`[interval level]`。

### ALS：7 个标签族

`[use animation]`、`[add]`、`[remove]`、`[none effect add]`、`[create draw only object]`、`[create draw only object random]`、`[create draw only object follow parent]`。

当前 `[add]/[remove]/draw-only` 已有部分事件链；**`[none effect add]` 仍明确未支持**，而且 delayed-add 的出生偏移、rate 继承、完整随机对象语义尚未恢复。这可以直接解释部分特效“缺半段”或时间不对。

### OBJ：115 个标签族

技能对象最关键的漏读候选是：`[basic action]`、`[etc action]`、`[basic motion]`、`[etc motion]`、`[attack info]`、`[string data]`、`[int data]`、`[add particles]`、`[add object effect]`、`[homing]`、`[homing velocity]`、`[homing follow]`、`[straight homing]`、`[sync target move]`、`[sync animation rotation]`、`[speed control passive objects]`、`[apply physics]`、`[under gravity]`、`[vanish on move collision]`、`[object destroy condition]`。

当前映射主要读取 motion、attack info、部分 string data；对象 action、homing、物理、粒子、销毁条件仍未形成通用执行链。这正是冰箭、枪手子弹和部分脱手技能不能泛化的主要原因。

### ATK：106 个标签族

已能读取 payload，但标签存在历史拼写变体：`[damage bouns]`、`[damge]`、`[hit horiozn]`、`[hit horizono]`、`[hit horizoon]`、`[warter element]` 等。若只按标准拼写读取，会漏掉这些实例。

当前必须增加别名归一化，并审计 `[active status]`、`[pvp]`、`[damage bonus]`、`[max target hit number]`、`[force hit stun time]`、`[hit check by screen pos]`、`[catch monster]`、`[ignore super armor]` 等对判定/反应有影响的字段。

### ACT：672 个标签族

这是当前最大缺口。已经观察到大量与技能直接相关的命令：`[CREATE PASSIVEOBJECT]`、`[PARTICLE FILENAME]`、`[SUB ANI]`、`[SUB ANI WITH XY/XYZ]`、`[ATTACK]`、`[ATTACKRECT]`、`[SET DAMAGE BOX]`、`[SET DAMAGE CHECK]`、`[CHANGE ATTACKINFO]`、`[MOVE UNIFORM]`、`[STRAIGHT MOVE]`、`[GRAVITY]`、`[SET SPEED]`、`[SET POS FORCE]`、`[FOLLOWING TARGET]`、`[HOMING]`、`[TRIGGER]`、`[CHECK TIME]`、`[ON ATTACKSUCCESS]`、`[DAMAGE]`、`[SUMMON MONSTER]`、`[SUMMON APC]`。

已有消费者覆盖子集，具体准入情况由下述真实 World host 报告核验。token 可读不能证明 ACT 调用链已恢复；狂战觉醒等技能是否依赖这些 ACT 命令，仍需技能引用或 exe 派发证据。

## 4. 解析失败与异常文件

全量 token 尝试发现：

- `.str` 有 23 个失败：多为纯文本/字符串表，不是 5-byte token 脚本；应走文本解码器，不应当作损坏。
- `.etc` 有 18 个空或非 token 文件；需要按空文件/文本/二进制分类。
- `.act` 有 8 个空文件、`.ui` 1 个空文件、`.ai` 1 个空文件；这些是合法空占位的候选，不应直接判成解析器缺陷。
- `.chr` 11 个、`.ptl` 4,438 个、`.nut` 189 个等不是 token 脚本，应走各自专用读取/保留原文路径。

因此“所有文件都可以被同一个标签解析器完整理解”这个前提不成立：PVF 至少同时包含 token 脚本、ANI 二进制、PTL 二进制、NUT 源文本、字符串表和空占位文件。

## 5. 明确的遗漏优先级

**P0：**复用现有 `.act` 编译/调度与 World host，按真实依赖补对象创建、SUB ANI、位移及事件消费者。

**P0：**通用 `.obj` + `.nut` 被动对象运行时（投掷、追踪、重力、目标选择、销毁、攻击信息修改）。

**P1：**ALS `[none effect add]`、delayed-add、随机 draw-only、rate 继承和 layer/parent 生命周期。

**P1：**ATK 标签别名与完整 reaction/status/target 语义。

**P1：**复用已有 PTL 解析/预览和直线运动子集，补 ACT/对象发射接线、未支持字段及生命周期。

**P2：**SKL 的追加动作、executable states、command customizing、buff/status、传送和持续消耗字段。

**P2：**`.equ/.stk/.key/.ai/.aic/.evt/.gdata` 等跨系统表族的完整消费者。

## 6. 现有消费者校正与真实准入导出

之前“没有 ACT 执行器”“PTL 仅保留原字节”的描述不准确：

- `act_runtime.cpp` 已有结构编译、触发/行为调度与源偏移诊断；`act_service.cpp` 已有固定步进，`act_world_host.cpp` 已消费速度、传送、方向、销毁、声音、攻击开关、ATK 切换和伤害检查子集。
- `skill_preview_particles.cpp` 已有 PTL 字段读取、粒子生成与预览；`particle_motion.cpp` 已实现受限直线运动。未接通的是 ACT 对象/粒子工厂与其他未支持语义。
- 全包出现某个 ACT 标签不能证明狂战觉醒等 PC 技能必然依赖 ACT，必须先找到该技能的真实引用或 exe 派发证据。

新增 `dnf_inspect CLIENT --act-coverage PATH _ OUTPUT`，直接调用现有 World host 编译准入，保留 syntax/source/runtime 三种状态、依赖和 blocking diagnostics。退出 0 仅表示报告生成成功；不执行绑定、派发或模拟推进。

已用基座验证：`assault_missile0.act` 的 syntax/source/runtime 均 true；`kaizen/action/teleport.act` 的 syntax/source 为 true、runtime 为 false。报告位于 `checkpoints/tests/pvf-audit/act-coverage-{success,rejected}.json`。

`act_audit.py` 仅为平面标签清单，已把子串匹配改为精确标签匹配；其分类数量不等于结构或运行支持数量。

## 7. 历史结论（以下链为待验证模型）

你的判断是对的：之前的技能链审计主要覆盖了 `SKL → CHR ANI → ALS → 部分 OBJ/ATK`，但没有把 **ACT、OBJ action、NUT、PTL、ATK 变体标签**作为完整闭包处理。当前缺陷不是单纯“某个坐标错了”，而是调用链缺失：

`SKL → state/exe → CHR motion → ACT/ALS → OBJ → NUT/ACT motion → ANI/PTL → ATK + type-15 hitbox → damage/reaction`

下一步应先针对技能相关文件建立“引用闭包 + 未消费标签清单”，优先实现通用 ACT/OBJ/NUT 宿主，而不是继续为单个技能添加硬编码补丁。
