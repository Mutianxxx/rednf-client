# 清风 1031 Script.pvf 全量文件类型与技能依赖审计

审计对象：`D:\dnf-rebuild\DNF1031客户端\Script.pvf`

- PVF SHA-256：`d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`
- 条目数：`334,927`
- 机器报告：`checkpoints/tests/pvf-audit/1031-pvf-audit.json`
- 审计脚本：`project/tools/pvf_audit.py`
- 技能闭包脚本：`project/tools/skill_closure.py`
- 技能闭包产物（本地可重建，不入库）：`checkpoints/tests/pvf-audit/skill-closure.json`
- 重建命令：`python project/tools/skill_closure.py --out checkpoints/tests/pvf-audit/skill-closure.json`
- 技能入口与消费者账本脚本：`project/tools/skill_entry_ledger.py`
- 账本产物（本地可重建，不入库）：`checkpoints/tests/pvf-audit/skill-entry-ledger.json`
- 账本重建命令：`python project/tools/skill_entry_ledger.py --out checkpoints/tests/pvf-audit/skill-entry-ledger.json`（依赖同目录的 `act-prefix-coverage.json`、`act-audit.json`、`skill-closure-v3.json`）
- P0-2 被动对象工厂准入账本脚本：`project/tools/act_spawn_admission.py`
- P0-2 账本产物（本地可重建，不入库）：`checkpoints/tests/pvf-audit/act-spawn-admission.json`
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

批量入口 `dnf_inspect CLIENT --act-coverage-prefix PREFIX _ OUTPUT` 复用同一 World host，稳定排序并保留每个文件的完整准入与异常。三阶段状态独立，整体准入须三项同时通过（`coverage.ok`）；命令退出成功只表示报告已生成。

基座 `passiveobject/` 首次批量报告含 5,638 个 ACT：syntax 通过 2,420、source 通过 3,378、runtime 通过 2,969，三项同时通过 1,596；5 个文件抛出 `Not token5`，路径与异常保留在报告。阻塞诊断按出现次数计，不能当作受影响文件数。报告保存在 `checkpoints/tests/pvf-audit/act-prefix-coverage.json`，属于可重建产物，不入库。

`skill_closure.py` V3 新增 ACT 明确 `[CREATE PASSIVEOBJECT]` 块内 `[INDEX]` 整数经对象注册表的引用边；保留偏移、ID、注册表路径，未知/重复 ID 不递归，缺失或损坏注册表、未闭合块留诊断。基座注册表为 6,477 个唯一 ID。

全 ACT 独立验证得到 13,150 条 resolved ID 引用和 109 条 unresolved 引用（按引用次数计）。但全 2,008 SKL 的 V3 图仍是 10,740 节点、16,747 边，ACT ID 边为 0。这个 0 不是解析失败，原因已由下节技能入口账本查明；全包对象引用不能误算为技能链已补全。

## 6.1 技能入口与消费者账本（P0-1）

`project/tools/skill_entry_ledger.py` 补 V3 字面闭包到不了的整数注册链。技能身份来自 `skill/*.lst`，**不是**全部 `.skl`；账本因此是注册表作用域，不是全 SKL 账本。

**实际入口链**（每层都留下来源路径、行号或偏移）：

```
skill/*.lst 整数 id → .skl
sqr/character/*_load_state.nut 的 SKILL_/STATE_ 常量 → IRDSQRCharacter/CNAvenger.pushState
                                 → pushPassiveObj(path, 整数 id)
exe setState 绑定 → 技能状态入口候选
NUT 明确对象创建 API（sq_SendCreatePassiveObjectPacket 等）
passiveobject/passiveobject.lst 整数 id → .obj → [basic motion]/[etc motion]/[attack info] → .ani/.atk
```

`SKILL_` / `STATE_` 常量按 `*_load_state.nut` 的职业 header 作用域解析；状态号是职业局部编号，不跨职业 join；冲突定义（如 `STATE_VIRTUAL_ATTACK` 的 32/19）保留而不任选。整数只在明确语境中解释为对象 ID：ACT `[CREATE PASSIVEOBJECT]` 块内 `[INDEX]`、NUT 创建 API、`pushPassiveObj`。普通整数、变量、表达式不猜。NUT 只解析字面字符串与简单的先前局部字符串赋值，不执行 Squirrel。

**基座实测**：13 个技能注册表 / 1,743 个注册技能身份（另有 288 个未被任何 lst 引用的 SKL）、3 个 `*_load_state.nut`（atmage / creatormage / priest-avenger）、617 个常量、1 处冲突；1,762 条 exe binding 中 1,700 个技能命中 setState 入口；账本共 3,726 条入口边（`skill-registry` 1743、`exe-state-binding` 1700、`nut-push-passive-object` 104、`nut-create-object-api` 95、`nut-push-state` 66、`nut-push-script-file` 18），其中 3,685 resolved、8 条 `-1` 通用动作、33 条动态对象 ID。58 个技能有 NUT 状态入口，30 个闭合到被动对象，共 124 条 ANI/ATK 资源引用。消费者账本登记 `act_world_host.cpp` 现有 10 个已注册 World kind、ACT 标签族与计划族、逐 ACT 静态准入及阻塞码，以及 4 类缺口（对象/粒子工厂、exe 原生派发、NUT 动态路径、SKL 字段消费者）。

**V3 的 ACT ID 边为 0 由两层原因造成**：

1. V3 以全部 `.skl` 为种子，只沿字面路径递归；SKL 里的路径主要是图标 `.img`（4,642）、传送/追加动画 `.ani`（53）和一个 `.ptl`，没有通往 ACT/OBJ 的字面链。真实入口是整数注册表 + NUT 常量 + exe 派发。
2. 补上注册链后，已闭合的 NUT 脚本技能对象仍不使用 `[basic action]` / `[etc action]` / `[last action]`，而是用 `[basic motion]` / `[etc motion]` 的 ANI、`[attack info]` 的 ATK 和 NUT 宿主 API。全包 6,378 条 OBJ→ACT 引用集中在 `passiveobject/actionobject/monster`(3,509)、`map`(1,571)、`spc`(336) 等；玩家职业目录仅 `passiveobject/character/common` 有 1 条。

所以结论是**有作用域的**：对账本已闭合的 NUT 脚本技能对象，ACT 不是入口；exe 派发职业的对象链尚未恢复，不能证明 1031 每个 PC 技能都不用 ACT，也不能把全包 ACT 标签频率当作某个技能（剑阵／觉醒／冰弓）的修复依据。P0-2 的通用对象消费者仍服务于怪物/地图对象，但本账本不把它们确立为这些技能缺陷的成因。

**有证据的未恢复边**：1,642 个只有 exe 绑定、无 NUT 注册表的技能（`0x70213F` ATK 选择器位于未恢复 exe VM 区）；33 条动态对象 ID；288 个未注册 SKL；状态触发条件与时序（账本只记录入口身份，不证明哪个 state 实际触发、按什么顺序播放）。

产物 `checkpoints/tests/pvf-audit/skill-entry-ledger.json` 可重建、不入库。已通过纯函数自测、作用域隔离、诊断完整性、全量计数一致性和重跑哈希一致检查。**静态准入不等于 World 执行，也不等于 1031 实机等价**；用户反馈的剑阵错位、觉醒缺半、冰弓无箭等缺陷仍未据此修复或验收。

## 6.2 ACT 被动对象工厂准入基线（P0-2，2026-11-12）

P0-2 首项把 `CREATE PASSIVEOBJECT` 接到真实 `ActWorldHost` / `ObjectSystem`。准入账本 `project/tools/act_spawn_admission.py` 只做静态证据：对象 ID 取自 ACT 依赖表里显式 `passive_object` 索引，经 `passiveobject/passiveobject.lst` 解析到 `.obj`；OBJ 字面依赖按扩展名分桶，`bucket=admissible` 只表示叶子全是 `.ani` / `.atk` / `.img`，**不等于** C++ 侧整体准入 `ok=true`。账本同时并列记录 `dnf_inspect --act-coverage-prefix` 的三阶段与整体旗标。

重建顺序（报告均可重建、不入库）：

```bash
# 1) 用同一 World host 生成两份修正后的批量准入报告
dnf_inspect CLIENT --act-coverage-prefix passiveobject/ _ checkpoints/tests/p0-2-spawn/act-coverage-final.json
dnf_inspect CLIENT --act-coverage-prefix monster/       _ checkpoints/tests/p0-2-spawn/monster-act-coverage.json
# 2) 生成账本；--before 传入修正前的旧报告以计算准入增量
python project/tools/act_spawn_admission.py \
  --coverage checkpoints/tests/p0-2-spawn/act-coverage-final.json \
  --coverage checkpoints/tests/p0-2-spawn/monster-act-coverage.json \
  --before checkpoints/tests/pvf-audit/act-prefix-coverage.json \
  --out checkpoints/tests/pvf-audit/act-spawn-admission.json
```

**1031 字节事实**：全包 19,087 个 ACT 中，303 个文件的 1,580 处 `[CREATE PASSIVEOBJECT] [WARNING MARK]` 带 2 或 4 个整数操作数（4：1,418；2：162）。旧编译器兜底按 0 操作数处理，把它们误判为 `operand_count` 语法错误。修正后操作数保留在 `ActSpawn::warningMark`，并发**非阻塞**诊断 `warning_mark_consumer_unregistered`：预警贴花的 World 消费者仍未注册，标签读取不等于语义实现。

**修正后的准入增量**：`passiveobject/` 5,638 个 ACT 的整体 `ok` 从 1,596 增至 1,597，syntax +8、source +12、runtime +9；唯一新增整体准入的 spawn ACT 是 `passiveobject/actionobject/common/action/flamestrike_item.act`。合并 `monster/` 13,118 个 ACT 后，账本共 4,244 个含被动对象的 ACT、2,365 个唯一对象 ID；C++ 侧整体 `ok=true` 的只有 4 个（3 个 monster 动作 + flamestrike），214 个文件带预警贴花缺口诊断。剩余阻塞按 OBJ 字面依赖分桶：OBJ→ACT 通用递归 2,385、PTL 解释器 1,657、ACT opcode 115、注册表 38、未知依赖 3。

**真实 World fixture 证据**：`monster/newmonsters/queen_rosi/action/attack2.act` 的 BASE ANI 无 type15 攻击盒、整体静态准入通过，4 条 `CREATE PASSIVEOBJECT`（对象 30059）经 `bind` + 固定步进生成 `ObjectInstance`，验证定义源路径、`act-runtime` 身份、owner/instance 归属、坐标与 World 事件，`cancelAll` 后实体全部回收。`flamestrike_item.act` 的 BASE ANI 有 4 个未配对 type15，`bind` 被精确阻塞；PTL 与全透明占位 ANI 样本继续显式阻塞。`runActWorldHostTests` 专项 81 项通过。

**边界**：预警贴花、PTL 粒子工厂、OBJ→ACT 通用递归、type15 攻击身份/配对 ATK、对象运动/命中/伤害闭环均未恢复。静态 `ok` / `runtime_ready` 不代表 World 执行或 1031 原版等价；group 3 整体仍因既存 Event.ai 基线问题失败（见 `project/reports/core-group-3-result.json`），不是本项回归。用户反馈的剑阵、觉醒、冰弓、枪手投射物缺陷未据此修复或验收。

## 7. 历史结论（以下链为待验证模型）

你的判断是对的：之前的技能链审计主要覆盖了 `SKL → CHR ANI → ALS → 部分 OBJ/ATK`，但没有把 **ACT、OBJ action、NUT、PTL、ATK 变体标签**作为完整闭包处理。当前缺陷不是单纯“某个坐标错了”，而是调用链缺失：

`SKL → state/exe → CHR motion → ACT/ALS → OBJ → NUT/ACT motion → ANI/PTL → ATK + type-15 hitbox → damage/reaction`

下一步应先针对技能相关文件建立“引用闭包 + 未消费标签清单”，优先实现通用 ACT/OBJ/NUT 宿主，而不是继续为单个技能添加硬编码补丁。
