# P0-2 首个消费者接线：ACT CREATE PASSIVEOBJECT 真实 World 工厂（2026-11-12）

按任务计划进入 P0-2，完成第一项「CREATE PASSIVEOBJECT 工厂」，**未**宣称 P0-2 整体完成。

**实现**（真实 World 实体，不是预览器能力）：`ActWorldHost` 新增 `ObjectSystem spawned_` 与 `ObjectCatalog catalog_`；`spawnPassiveObject()` 按 `[INDEX]` 经 `passiveobject.lst` 解析 `.obj`，生成带 `act-runtime` 身份的 `ObjectInstance`，记录 owner/instance 归属与 `act_spawn_passive_object` 事件；`retireSpawns()` 在 `cleanup` / `cancel` / `cancelAll` 时按 `instanceId:actionId` 前缀回收并记录 `act_spawn_retired`；`commit` / prepared restore / `resetCancelledClock` 均纳入该容器（ACT-owned 实体是 transient，不进持久化快照）。`hasCommandConsumer` 在消费者真实存在后才承认 `spawn_passive_object`。`ActWorldResources::resolve` 新增 PassiveObject 受控依赖闭包：只接受已有真实消费者的 `.ani` / `.atk` / `.img` 叶子，含 `.ptl`、`[basic action]` 等 ACT 递归的对象给精确阻塞原因，不伪造闭包。

**按 1031 PVF 字节修正一个真实解析缺口**：全包 19,087 个 ACT 中 303 个文件的 1,580 处 `[CREATE PASSIVEOBJECT] [WARNING MARK]` 带 **2 或 4 个整数操作数**（4：1,418；2：162），旧 `parseSpawn` 的兜底 `count(i, 0)` 把它们误判为 `operand_count` 语法错误。现按字节接受 2/4，操作数保留在 `ActSpawn::warningMark` 并进入 `payloadJson`，同时发**非阻塞**诊断 `warning_mark_consumer_unregistered`（预警贴花 World 消费者仍未注册），不把标签读取冒充语义实现。

**准入增量**（`dnf_inspect --act-coverage-prefix`，仅静态准入）：`passiveobject/` 5,638 个 ACT 的整体 `ok` 由 1,596 → 1,597，syntax +8、source +12、runtime +9；新增的唯一整体准入 spawn ACT 是 `passiveobject/actionobject/common/action/flamestrike_item.act`。首次纳入 `monster/` 13,118 个 ACT 后，账本覆盖 4,244 个含被动对象的 ACT、2,365 个唯一对象 ID；其中 C++ 侧 `ok=true` 的只有 4 个（3 个 monster 动作 + flamestrike），`warning_mark_consumer_unregistered` 出现在 214 个文件。OBJ 字面依赖分桶 `admissible` 46 个 ≠ C++ 整体准入 4 个，两者不可混用。剩余阻塞：OBJ→ACT 通用递归 2,385、PTL 解释器 1,657、ACT opcode 115、注册表 38。

**真实 World fixture 验收**：`runActWorldHostTests` 共 81 项全通过。样本 `monster/newmonsters/queen_rosi/action/attack2.act` 的 BASE ANI 无 type15 攻击盒、整体静态准入通过，其 4 条 `CREATE PASSIVEOBJECT`（对象 30059 → `passiveobject/monster/soceress/iceniddlegroup.obj`）经 `bind` + 固定步进生成实体，断言定义源路径、`act-runtime` 身份、`instanceId:actionId` 归属、z 坐标、World 事件，并在 `cancelAll` 后断言实体全部 `Removed` 且有 `act_spawn_retired`。另外断言：WARNING MARK 操作数保留且缺口诊断存在、`flamestrike_item.act` 因 BASE ANI 有 4 个未配对 type15 被 `bind` 精确阻塞（不静默丢失攻击身份）、PTL 与全透明占位 ANI 样本继续显式阻塞。

**证据边界**：预警贴花消费者、PTL 粒子工厂、OBJ→ACT 通用递归、type15 攻击身份/配对 ATK 均**未**恢复；ACT-owned 对象已按固定仿真步进推进其动画时钟，但接触判定、命中与伤害结算尚未接到 World（属 P0-3）。`ok` / `runtime_ready` 只是静态准入，不等于 World 执行或 1031 原版等价。group 3 整体仍为 `failed`，但失败点是仓库中**已入库的既存基线问题**（`project/reports/core-group-3-result.json` 同错误："Event.ai World: Diagnostic damage draws only its hurt-presentation stream…"），不是本轮改动引入；本轮 World host 专项报告为 `pass`。用户反馈的剑阵错位/跟随、移动路径攻击判定、狂战觉醒缺半、冰弓无箭、枪手投射物仍未实机修复或验收。

新增工具 `project/tools/act_spawn_admission.py`（纯函数自测通过），产物 `checkpoints/tests/pvf-audit/act-spawn-admission.json` 不入库；批量准入报告位于 `checkpoints/tests/p0-2-spawn/`，同样可重建、不入库。上一提交 `2584ad1d1` 因本地代理 `502 CONNECT tunnel failed` 与直连不通尚未推送成功，本轮改动一并待推。

---

# P0-1 技能入口定位与消费者账本验收（2026-11-12）

按计划推进 P0-1。新增 `project/tools/skill_entry_ledger.py`，产出 `checkpoints/tests/pvf-audit/skill-entry-ledger.json`（产物不入库）；纯函数自测、作用域隔离、诊断完整性、全量计数一致性与重跑哈希一致（复现）均通过。

**为什么 V3 技能图 ACT ID 边为 0，已查明两个独立原因：**

1. V3 的种子是全部 `.skl`，只沿字面路径递归。全 2008 个 SKL 的字面路径只有图标 `.img`、`[pre/post teleport]` 的 `.ani`、少量 `[start/end/loop addtional animation]` 的 `.ani` 和一个 `.ptl`；技能执行入口根本不在 SKL 字面引用里，而是「`skill/*.lst` 整数 id → SKL → NUT `SKILL_`/`STATE_` 常量 → `*_load_state.nut` 注册表 → `passiveobject.lst` 整数 id → OBJ」，以及 exe `setState` 表派发。
2. 补上整数注册链后，**已闭合的 NUT 脚本技能对象也没有 `[basic action]` → ACT**：它们用 `[basic motion]` / `[etc motion]` / `[attack info]` 的 ANI/ATK 加 NUT 宿主 API。全包 6,378 条 OBJ→ACT 引用集中在 `passiveobject/actionobject/monster`（3,509）、`.../map`（1,571）、`.../spc`（336）等怪物/地图对象；玩家职业目录只有 `character/common` 1 条。因此全包 ACT 标签频率不能推断某 PC 技能必经 ACT。此结论限定在已闭合链，不覆盖未恢复的 exe 派发职业。

账本实测：13 个技能注册表、1743 个注册技能身份（全包 2008 SKL，288 未注册）；3 个 `*_load_state.nut`（atmage / creatormage / priest-avenger，作用域按职业隔离，冲突常量 `STATE_VIRTUAL_ATTACK=32/19` 不任选）；58 个 NUT 技能入口、8 个 `-1` 通用动作单独归类；104 条 `pushPassiveObj` 经注册表解析；95 条 NUT 对象创建 API（62 解析、33 为变量/表达式动态 ID）；1700 个 exe setState 绑定；共 3726 条入口边，每条带源文件/行号/offset 与状态诊断。30 个技能闭合到对象，124 条 ANI/ATK 资源引用；ACT 准入结果为 0 是实测结构而非解析失败。

**有证据的未恢复边**：1642 个只有 exe 绑定、无 NUT 注册表的技能（ATK selector `0x70213F` 在未恢复 exe VM 区）；33 条动态对象 ID；288 个未注册 SKL；状态触发条件与时序（未定量，需实机对照）。均写入账本 `explanation.v3ActEdgeZero.unrecovered`，不冒充已闭合。

消费者账本：记录 `ActWorldHost::hasCommandConsumer` 的 10 个已注册 kind、ACT 标签族/计划族、逐 ACT 静态准入与阻塞码、4 类缺口。静态准入不是 World 执行，更不是原版等价。

已完成前置 git 同步并独立核验：远端 `refs/heads/main` 更新到 `016847cc5f0dcf5784ff5e6c38f85127454725b9`（含此前积压 `099bdb9c4`）。

P0-1 按计划门槛 2 验收：技能级边与消费者账本已交付、ACT 边为 0 已解释、动态 NUT/exe 入口已定位并有证据的未恢复边清单。**下一步才进入 P0-2 新增运行时接线**；用户反馈的剑阵、觉醒、投射物缺陷仍未做实机验收。

---

# 技能计划逐功能验收核查（2026-11-12）

已核查源码、测试代码与既有报告，将前置、P0/P1/P2及持续节点细化为“功能—任务—验收标准—状态”，见 `SKILL-RUNTIME-PLAN.md`。已有通用能力、实际技能接线、历史专项和原版等价分开记录；本轮仅更新文档，未构建、重跑专项或联网核验远端。

（本节为核查当时的历史状态，最新状态以本文顶部 P0-1 验收章节为准。）核查时阶段为 P0-1：技能图尚未到达 ACT ID 边，动态 NUT/exe 入口及技能级消费者账本未闭合；ACT 准入工具作为 P0-1 覆盖基线。该阶段现已按门槛 2 验收。P0-2 以后仍均仅有既有能力子集，未整体完成；用户反馈的剑阵、觉醒、投射物缺陷仍未最终验收。

---

# 技能运行时补全：计划状态与真实准入（2026-11-11）

执行清单见 `SKILL-RUNTIME-PLAN.md`，完成的独立子项使用 `[x]`；整体闭包和 ACT/OBJ 消费者任务仍进行中。

已完成：全 2008 SKL 静态候选闭包口径修正、ANI sidecar 递归、ACT 精确标签词族审计、单文件 `--act-coverage` 真实 World 编译准入导出与成功/拒绝样本验证。静态关联率不等于运行消费率。

核查纠正：已有 ACT 编译/调度/World 子集与 PTL 解析/预览；当前重点是 ACT spawn/particle 工厂、动态对象/命中/生命周期及技能接线，而非重写已有模块。全包 ACT 标签不能证明具体 PC 技能调用 ACT。

本轮完成：`--act-coverage-prefix` 批量准入（passiveobject/ 5638 ACT，1596 整体准入，5 异常）；ACT CREATE PASSIVEOBJECT/INDEX 经 6477 唯一注册 ID 建立整数引用边，全 ACT 独立验证 13150 条解析、109 条未解析，边界自测通过。V3 全 2008 SKL 图统计未增长、尚未到达这些 ACT 边，说明技能到 ACT 的入口仍需补全。对象/粒子 World 工厂和技能表现尚未验收。

Git：2026-11-11 恢复后重试成功，四个积压提交 `4d2a2bad7`、`69e2f5509`、`ca87cbe71`、`c16361750` 均已推送。独立 `ls-remote` 确认远端 main 为 `c163617506a9e30f503c0f447e0126ec07c82ef4`；此前网络错误已解除，本轮新增改动继续独立提交与同步。

---

# 技能判定/投掷物/剑阵的根因修复（2026-11-11 第九轮）

用户报的现象：极·鬼剑术「渲染的剑和实际对不上」「角色移动时剑跟着动」「经过处没有攻击判定」；
狂战士觉醒「特效只有一半」；男法/枪手「脱手投掷物没有射出」；并要求继续从 exe/PVF 找证据、
判断调用链是否还缺文件。

## 1. 根因：盒子类型搞反（最关键）

逐帧解码 1031 的 ANI 后确认：

| 文件 | 盒子 | 判定含义 |
| --- | --- | --- |
| `character/swordman/animation/attack1.ani` | 3–4 个 type **14** | 受击盒 |
| `character/swordman/animation/hardattack.ani` | 2–3 个 type **14** | 受击盒 |
| `passiveobject/.../hundredswordhit.ani` f1 | 3 个 type **15**，最大 532×62×200 | **攻击盒** |
| `passiveobject/.../atbrokenarrow/00_arrow_normal.ani` | 1 个 type **15**，81×20×32 | **攻击盒** |

即：**角色 body 动作在 1031 里不写攻击盒，攻击盒只存在于被动对象动画**。此前映射层把被动对象
当成「纯视觉」，`damageEnabled=false` 一路传下去，判定循环又只放行 4 个硬编码技能
（`skill != 20/58/64/65` 直接 `continue`），所以剑气落到怪身上也不掉血。

## 2. 修复：被动对象层带判定入场

- `EffectLayerPlan` 新增 `attack` / `attackInfo`；映射层把对象的 `[basic motion]`（有 `[attack info]` 时）
  收进 `effectLayers`，并沿 body 的**挥砍阶段**展开（每次挥砍一个实例，`birthMs` = 该 stage 的
  `startMs`）——「谁生成对象」这条命令仍未恢复，这一层是重建，已在 `evidence` 写明。
- 对象的 `[etc motion]`（`hundredswordhitlayer`、`hundredswordhitdisappear1/2`）作为**纯视觉**同批展开，
  这修掉了「觉醒只画一半」：此前一次性 motion 被 `else return; // one-shot impact` 整段丢掉。
- `combat.cpp`：`damageEnabled = layer.attack`；判定循环去掉技能白名单，改由 `damageEnabled` 单独把关。
- 实测极·鬼剑术：68 层（48 原有 + 20 对象），其中 **5 个 `hundredswordhit` 判定层**分别落在
  4250/4310/4370/4430/4480ms（对应 moveslash1..5），15 个视觉层同源。

## 3. 修复：剑阵双重偏移

`swordair1.ani` 首帧自带 `y = -102`（悬空高度已写在帧里），映射层又给 persistent 加了
`offsetY = -160`，两者叠加导致剑阵浮在角色头顶之外。改为 `offsetY = 0`，高度交回 ANI 帧。
对象层同理：`source == "object"` 时不再把帧的 XY 二次加到世界坐标上。

## 4. 投掷物：证据在 nut 脚本，不在 exe

`sqr/character/atmage/brokenarrow/po_atbrokenarrow.nut` 完整给出运动模型：

```squirrel
local v  = sq_GetUniformVelocity(0, dis_x_len, currentT, fireT);
local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
sq_setCurrentAxisPos(obj, 0, dstX); ...
if (currentT >= fireT) sq_SendDestroyPacketPassiveObject(obj);
```

`brokenarrow.nut` 给出炮口偏移 `(65, 0, 73)`、无锁定目标时 `xLen = 400`、
`fireT = sq_GetIntData(SKILL_BROKENARROW, 0)`（= `brokenarrow.skl` 的 `[static data][0] = 4`）。

实现：映射层把「循环 + 单帧 + 有 `[attack info]`」的对象识别为投掷物，`spawnSkillVisuals` 用
`trajectoryMs` 直线推进 `400px / fireT`，到期销毁，子弹自身的 type-15 盒负责命中。
`job 8 / skill 16`（冰魄之弓）已验证解析出 `00_arrow_normal.ani`、`loop=true`、`attack=true`。

## 5. 仍未完成

- **角色 body 技能的攻击盒几何**：1031 的 body ANI 没有 type-15，攻击盒尺寸只可能来自 exe 的攻击盒
  构造点（`.atk` 只有伤害反应，无几何）。ATK 选择器 `0x70213F` 的立即数翻译仍未恢复。
- 剑阵的**横向间距**（当前 `56px`）与「哪一把先落」仍无源数据，需要 AVI 或 exe 逐帧证据。
- 投掷物的射程/时间只对 atmage 逐个核对过；其它职业（枪手子弹等）按通用规则处理，属重建。

---

# 技能判定与指令的 exe/PVF 证据补全 + 开源 README（2026-11-11 第八轮）

节点 `skill-evidence-judgment-command-20261111`。

用户要求：继续补全缺口，并且**技能的判定、指令逐渐去 exe 找证据**，同时把 `README.md`
维护成能让外部贡献者看懂的开源说明。本轮聚焦「证据入库 + 接入映射层」，不伪造运行时等价。

## 1. 判定（攻击）—— exe ATK 选择器直证

- 技能 setState handler 内调用攻击判定选择器 `0x70213F`，首参即 `.atk` 里的攻击序号。
- 新增 `project/tools/skill-bindings/src/extract_judgment.py`：按 `(handler, state)` **双键**
  把 `state-handler-events.json` 的调用精确关联到技能（仅剑士族；handler 是跨职业共享的通用
  代码地址，单键会过度扇出到其它职业）。
- 产物 `evidence/judgment-events.json`：73 个技能，42 个 state 带 ATK 调用，34 个 state 带
  效果附加调用（`0x690210/0x690420`）。共享 handler 标 `shared_handler=true`（运行时靠
  skill_id 选 `.atk`）。
- 实测：鬼斩 state20 → atk 0/20（`0xccf619/0xccf8d7`）；三段斩 atk 7；裂波斩 atk 16/17/24；
  极·鬼剑术（暴风式）atk 62。
- 边界：立即数 → `.atk` 文件名仍在 Themida VM 区，未翻译；判定框几何仍取 PVF/ANI。

## 2. 指令（操作指令）—— PVF 源数据 + exe 消费链

- `.skl` 的 `[command]` / `[command key explain]` 是按键序列权威来源。
- 新增 `extract_commands.py`：从 1031 `Script.pvf` 抽取 2008 个 `.skl` 中 **781 个带指令**，
  产出 `evidence/skill-commands.json`（token + 中文说明）。
- 实测：鬼斩 `↑(按住)+Z`；极·鬼剑术 `↑↑↓↓+Z`；裂波斩 `→↑+Z`；三段斩 `→(按住)+Z`。
- 边界：exe 侧消费该字段的输入解析器**尚未解码**，故指令证据标注「PVF 源数据，exe 由
  state-handler 关联校验」，不冒充 exe 运行时直证。

## 3. 接入映射层（数据模型 + 审计）

- `skill_preview_mapping.hpp` 新增 `ExeJudgment` / `SkillCommand`，`SkillVisualMapping` 增
  `exeJudgments` / `command`。
- `skill_preview_mapping.cpp` 新增 `loadEvidence()`（按 cwd 候选定位证据目录，缺失即空、不
  影响解析）与 `applyEvidence()`（按技能 stem 注入），`audit()` 输出二者。
- 验证：`dnf_inspect --skill-chain 0 5/8/86/58` 的 `mapping.command` / `exeJudgments` 均正确；
  编译 23 目标全过，`verify_architecture pass`；回归 **48/48 通过**。

## 4. README 开源化

- `README.md` 重写：项目定位（clean-room 复刻、不提供资源）、证据等级、目录结构、构建/运行
  快速开始、技能预览与主游戏、判定与指令的 exe 证据链、重新提取命令、已知边界、贡献约定。

## 5. 仍未完成（下一轮）

- 17/21 无源时间轴层仍按 `birthRatio` 挤在 nominal 时钟尾部；需 exe 特效派发证据才能正确定位。
  **本轮已查证**：`0x690210` 的效果附加调用是 4 参样板（如 `[0,2,17,-1]`），且 state 5/6/7/9… 落在
  **同一调用点地址**（0x00cdcf55 等），是通用注册而非逐帧触发，**不足以重排层时序**；需要的是
  ANI 帧触发的特效派发，当前 handler 事件快照没有该信息。
- `ratePercent`/delayed-add 未恢复，绝对 ms 不等价。
- exe 输入指令解析器未解码（当前只能给到 PVF 源数据）。

---

# 技能链状态机补全与 AVI 交叉验证（2026-11-11 第七轮）

节点 `skill-chain-state-machine-20261111`。

用户纠正了 AVI 对照的方法：**不是照着视频画面盲猜复刻参数**，而是先补全技能链
解析中逆向未完成的部分，再从视频提取独立观测，与补全后的链解析预测做交叉验证，
用差额反推链解析哪里仍不准确。本轮严格按此执行；视频没有写回任何映射参数。

## 0. 证据边界不变

基座仍是清风 1031：`Script.pvf` identity `d13ce454567197bb4617...`，
`DNF.exe` sha256 `246b838163fa7c71aa...`。`rep-player-1031-pvf/docs/native-evidence/
animation-render.json` 仍是唯一一级运行时直证；40JP / 60US / handoff 参考实现
只作机制蓝本。跨版本推断一律标注。

## 1. 源侧核对发现的三个链解析缺陷（都由 PVF / exe 字节直接支持）

1. **exe setState 的 state 入口被当成播放阶段。** `skill_exe_bindings.hpp:327-334`
   给出技能 86 的 3 个 state（47/48/49）入口 `hundredswordready / guard /
   hundredswordfinish`，原映射把它们作为链的第 0/1/2 段前置，再用名称扫描补
   10 段，导致 `finish` 排在 5 次斩击之前。`skill_preview_motion_pool.hpp:122-133`
   给出的 CHR 运动池顺序是 `ready -> moveready1..5 -> moveslash1..5 -> finish`。
2. **输入等待态被摊进动作时钟。** `guard.ani` 是 2 帧、每帧 `[DELAY]=10000`、
   通用人体贴图（`sm_body%04d.img` 帧 123/124），是驻留哨兵而不是 20 秒动画。
   原 `actionDurationMs = 25810`，其中 20000ms 来自这一状态。
3. **效果家族文件名自带的阶段编号未被消费。** `weaponready3normal.ani`、
   `weaponslash2normal.ani`、`finishcircle1.ani` 与 body 阶段同源，但
   `effectStageOrder()` 把它们都归到同一个 stage 值，48 层按列表下标均匀摊到
   25.8 秒上，且 ALS sidecar 数为 0。

## 2. 本轮补全（均为源侧规则，可跨职业复用）

- `SkillVisualMapping` 新增 `ChainSlot / ChainSlotRole / chainSlots /
  externalSlots / nominalActionMs`；`EffectLayerPlan` 新增 `stageBound`。
- exe override 改为以 CHR 运动池顺序为骨架，pool 未登记的 state 入口按其
  exe 前驱锚定插入；`finish` 回到链尾。
- 新增通用 hold 识别：帧数 <= 3 且最大 `[DELAY] >= 5000` 的 body 段分离为
  `ExternalHold`，不推进动作时钟，其真实时长保持**未定量**（由输入驱动）。
- 新增 `matchEffectBodyStage()`：按「阶段词 + 编号」同源字符串把 untimed 层
  绑定到 body slot 的 `startMs`。全职业命中 786 层，技能 86 命中 27/48 层。
- 预览器 `seedLayers()` 与 native `spawnSkillVisuals()` 统一消费同一 nominal
  时钟；native 补齐预览器已有的 persistent 层过滤，修复悬剑重复绘制。
- `dnf_inspect --skill-chain` 扩展 `predictedTimeline`：`fixedSlots /
  externalSlots / phaseWindows / layerBirths`，并标注每条 birth 的时钟来源
  （`als / stage_bound / stem_order`）。

技能 86 结果：`bodyChain` 13 -> 12 段，`actionDurationMs` 25810 -> **5810ms**，
窗口为 `entry 0-3000`、`triggered 3000-4540`、`finish 4540-5810`。

## 3. AVI 独立观测与交叉验证

工具 `project/tools/legacy/avi_chain_crosscheck.py` 可复现：ffmpeg 解码清风 1031
自带 `Video/Swordman/HundredSword.avi`（Neople wrapper 解出的标准 AVI，160x90、
29.97fps、363 帧、12.1121s），逐帧灰度差按 0.1s 分桶，阈值只由视频自身中位数
导出，全程不读 PVF / 链数据。

观测：16 个活动窗口、17 个局部峰；全局最大在 **10.01s**（avg 61.97）；
中段 5.4-9.4s 为连续离散峰，10.2s 之后静止。预测：固定段共 5.810s，顺序为
`entry -> 5 组触发 -> finish`，终结为最后一个 slot。6 项顺序 / 数量 / 比例
验证全部通过；差额 **6302.1ms** 正是链解析明确留白、任何 PVF 文件都不计时的
「输入等待 + 触发间隙」，报告标注为 observed，未写回映射。

## 4. 差额反推出的待补项（本轮明确**不**用文件名启发式硬猜）

- 21/48 层仍无源时间轴；其中 **17 层被 birthRatio 挤在 nominal 时钟最后 20%**
  （4865-4924ms），而观测的中段峰分布在 5.4-9.4s。`flash / light / dust /
  lighttail` 应随触发节拍出现，当前链解析仍不准确。
- 真正补完需要恢复 1031 exe state handler 的特效派发（或家族 ANI 自身
  sidecar），不是再叠一层字符串规则；后者会降低证据等级。
- `triggeredSlots=10` 对 `midBandPeaks=14`：一次触发可能产生多个可见事件
  （武器、地面剑阵、闪光、伤害数字），视频无元素级标注，不能强行 1:1。
- nominal 时钟仍是裸 `[DELAY]` 累加；`effectiveDelay = trunc(rawFrameDelay *
  100/ratePercent)` 与 delayed-add net birth-offset 未恢复，绝对 ms 比较仍带
  未知比例因子。
- 本 AVI 仍无法判定 `[IMAGE ROTATE]` 正负、逐层 XYZ / 层序、cast 局部偏移。

## 5. 验证与产物

- 回归 45 -> **48 项全部通过**（9j 拆为三类时钟断言，新增 9k hold 分离 /
  slot 对齐断言），`checkpoints/tests/chain-v2/skill-preview-tests.json`。
- 链解析：`checkpoints/tests/avi-probe/chain_hundredsword_v2.json`；
  交叉验证：`checkpoints/tests/avi-probe/avi_cross_validation.json`。
- 增量编译 `dnf_inspect / dnf_skill_preview_tests / dnf_native.exe /
  dnf_skill_preview.exe` 到 `checkpoints/build`；未重启此前被取消的全量测试编译。
- 行为提示：`guard` 输入等待态已从自动播放链分离，主游戏不再出现 20 秒静止
  驻留；悬剑由 persistent 实体表现。逐技能体验时请以这一版为准。

---

# 清风 1031 基座核对：ALS 源时间轴与坐标投影（2026-11-11 第六轮）

节点 `baseline-1031-als-20261111`。

## 0. 先纠正一个术语偏差

用户澄清：**「70端」就是清风 1031，是基座版本**，不是另一个客户端源码工程。所有内容
的核对与实现都要对比这个端的效果。此前按「70端源码」去检索 40JP / 60US 之外的
第三个客户端工程，方向是错的。

- 基座：`D:\dnf-rebuild\DNF1031客户端\Script.pvf`，177,617,021 B，
  md5 `7df482690cd4e6cc95aee9ec5b46703b`；`DNF.exe` 41,978,368 B。
  `project/content-profile.json` 与 `project/toolchain.local.json` 绑定的正是这一份。
- 易混淆：`/d/game/DNF1031客户端-20260708/...` 是**另一份** PVF（md5 `e2f36595…`），
  `70不悔PVF完美精修2.0客户端（Final）` 只有登录器/GM 工具，两者都不是基座。
- **证据等级**：清风 1031 的 PVF 字节 + 该端实机效果 > 1031 exe/dump 直证 >
  40JP / 60US 机制解释 > 社区格式文档。跨版本推断必须显式标注，不得当作 1031 事实。

### 0.1 直证核对后的四处更正

1. **handoff 参考实现不是基座 PVF**。`逆向部分结果参考/…/dnf-skill-combat-handoff-v1/
   derivation/raw/index.json:5-6` 的 `source_pvf_sha256=1cd52a54…`、
   `source_exe_sha256=1f8244d3…`，都不等于 1031 的 `d13ce454…` / `246b8381…`；其 sources
   里的 `character/swordman/effect/animation/bloodboom/finish_bloodboom_finish1.ani`
   在基座 PVF 实测 Missing。因此 `reference/upstream/src/main.cpp:82/86/194` 的
   `point()` / `boundary()` / 排序只是**机制蓝本**，不是 1031 直证；代码注释已更正。
2. **真正的 1031 一级证据**是 `rep-player-1031-pvf/docs/native-evidence/animation-render.json`
   （`exe_sha256=246b8381…`、`pvf_sha256=d13ce454…`，与实测基座一致）。它确认 `[add]`
   首参是父动画帧下标（`:176-178,328-337`）、层按 layer 升序插入且负值排前（`:66`）、
   `[remove]` 按 uniqueName detach（`:340-349`）。基座 ALS 实测样本：
   `[add] 1 -9999 "b"`、`[add] 0 10000 "charge"` → `[remove] 1 10000 "charge"`、
   `flowmindone.ani` 9 帧 × 80ms。当前实现保留负 layer 并按升序排序，符合该直证。
3. **三处仍不闭合，不冒充已还原**：`effectiveDelay=trunc(rawDelay*100/ratePercent)`（`:36`）、
   `delayed-add net birth-offset policy` 在 `unrecovered` 里（`:130,:518`）、
   `none-effect flag renderer consumer` 同样未恢复。所以 `birthMs` 是**名义 boundary**；
   `triplestab.ani.als` 的 `[none effect add] 0 10000/10001 "normal"/"dodge"` 目前报
   `unsupported_als_command` 是诚实边界，不应臆造它的混合模式去画。
4. **旋转确认不改**：从基座 PVF 直取槽 8（`[IMAGE ROTATE]`）得到 -2.443461 / -1.745329 /
   -0.523599 / +6.28 等，量纲为弧度、正负都有；1031 唯一一级运行时证据全文无
   rotate/angle/fchs/变换矩阵，`CURRENT_TASK.md:31` 说明 1031 EXE 加壳。60US 的
   `rotate(-angle)` 来自其 EXE 的 `fchs`，`dnf_ani_render.hpp:10-12` 自己已标为跨版本推断，
   且 60US `transform/README.md:72` 自承未做原游戏逐帧对照。社区 `标签参考.md:159`
   的「正值顺时针」与 y 向下坐标系的 `R(+angle)` 自洽，但不是运行时直证。
   **结论：`makeQuad()` 保持不动。**

附带排除：`pvfUtility_BackUpPvf/script_2026_11_05_04_40_02.pvf` 与基座同哈希；
`/d/game/DNF1031客户端-20260708/…` 对应 `PVP_UI_AND_FONT_SCOPE.md:13` 的 **86JP**
客户端根，不是「另一份 1031」。

## 1. 本轮修的四个偏差（全部是 1031 源数据可直证）

1. **ALS 帧号没有编译成时间**：`.als` 的 `[add] <frame>` 是父动画的**帧下标**
   （1031 原生证据 `animation-render.json:176-178,328-337`）。映射层按父 ANI 前序
   `[DELAY]` 累加出**名义 boundary**（机制蓝本见 handoff `main.cpp:86`，跨版本，见 0.1）；
   `ratePercent` 缩放与 delayed-add birth-offset 仍未恢复。映射层过去只存 `alsFrame`，
   `birthRatio` 留 0，
   于是 native 的 `born = start + 0` 让所有 ALS 层第 0 帧齐发。现在按每个
   `bodyChain` stage 各自解析 sidecar，用 stage 起点 + DELAY 累加算出
   `birthMs`，并接上同名 `[remove]` 的 `endMs`（68 处声明中 17 处有终点）。
2. **offsetZ 被丢弃**：`spawnSkillVisuals()` 里 `e.z = player.z`，而
   `Renderer::effect` 投影 `screenY = y - z`。源端是
   `castY + localY - localZ - motionZ`，draw-only 对象的高度全丢。现在
   `e.z = castZ + layer.offsetZ`，并把 cast 位置/朝向冻结在局部变量里
   （`motionZ` 仍未恢复，保持 0，代码中注明）。
3. **预览器有 ALS 就丢掉全部非 ALS 层**：`seedLayers()` 的 `if (hasAls) return;`
   让目录族 / 被动对象层在有 sidecar 的职业上整个消失。改成只在
   `effectLayers` 为空且确实有 ALS 时早退，其余照常 seed。
4. **多段链永远派发第一段的 ALS**：`dispatchFrame()` 读的是
   `timeline_->bodyPath`，且 `span.startMs` 是 stage 局部时间。现在按传入的
   `body.path` 取 sidecar，并从 `timeline_->stages` 查出 stage 起点，把层时钟
   统一到共享 action clock（含 `[remove]` 的 volume 截止时刻）。

## 2. 两项核对后**不改**代码

- **旋转符号**（原清单第 1 项）：直证核对完成，结论是**保持不动**，理由见 0.1 第 4 条。
  该端没有能判定旋转方向的一级证据，60US 的 `rotate(-angle)` 不能覆盖基座表现，
  `third_party/native-contracts/include/dnf_ani_render.hpp` 不改。
- **depth + layer 排序**（原清单第 5 项）：预览器 `sortLayerIndices()` 本来就是
  按 attachment key 稳定排序（负值自然在前），主游戏 `game_application.cpp`
  的 `depth` 再 `layer` 稳定排序与 handoff `main.cpp:194` 一致。上一轮把这一行
  列为偏差是误判，本轮确认无需改动。

## 3. 验证

- 增量编译 `dnf_native` / `dnf_skill_preview` / `dnf_skill_preview_tests`：10 秒，
  只重编 6 个 `.cpp`（没有重启此前被取消的全量测试编译）。
- 预览器回归 **45/45 通过**（原 42 条 + 本轮 3 条）。新增断言直接核对清风 1031：
  `timed=688`、`positiveBirth=535`、`withRemove=17`，抽样重算父 ANI 的
  `[DELAY]` 名义累加与 `birthMs` 完全一致；10370 个无 sidecar 层仍走 `birthRatio`。
- 主游戏 `--skill-lab-sweep` 回归：见本轮运行目录 `checkpoints/tests/sweep-20261111/`。

## 4. 仍未做（不冒充已修）

`motionOffset` / `motionZ` 的身体帧位移、千莲怒放「催熟花色 + 再点逐个引爆」
状态机、非剑士 experimental runtime 接映射表、65 条新注册技能的伤害表、
8 个 0 层特效技能，以及 `[none effect add]` 的渲染语义。这些都要按该端
实机逐技能对照后再动，不能靠 40JP/60US 猜。旋转方向若日后要改，须先补
「1031 自带 AVI 逐帧解码 + 同一 ANI 槽 8 对齐」或 1031 渲染变换链反汇编直证。

---

# 技能实验室：全技能注册 / 映射接管主线（2026-11-11 第五轮）

节点 `skill-lab-unlock-20261111`。用户要求把 skill-preview 的成果**真正套到主线游戏**，并把
**所有技能解锁**以便逐个体验。

## 1. 先承认上一轮接了个空

上一轮写了 `World::spawnSkillVisuals()`，看起来"已接入主线"，实际没有一行代码会执行：
`combat.cpp` 的 `add()` 给每个手工技能设了 `s.manualVisuals = true`，而 `spawnSkillVisuals()`
第一行就是 `if (skill.manualVisuals) return;`。主游戏一共只手工注册了 9 个剑士技能，全部命中
这个 early return。更要紧的是主游戏**根本没有**念气环绕、千莲怒放、极鬼剑术——它们不在那 9 条
硬编码里，非剑士职业走的 `experimental_character.cpp` 那套运行时又完全没有引用映射表。

结论：映射层是死代码。这一轮把它接活。

## 2. 按 SKL 全量注册（`registerMappedSkills`）

遍历 `characterSource().skills.entries`，对每个 `SkillSourceKind::Active` 且尚未手工注册的技能：

- 技能数据（名字、MP、CD、cast、`[level info]`、`[command]`、`purchaseMaximum`）走 `readSkillSourceData`，
  和手工分支同一套读取，不臆造缺省值；
- 动作阶段取映射的 `bodyChain`（多段释放链），退 `bodyAni`，再退 `fallbackPose`；
- `manualVisuals = false`，于是 `spawnSkillVisuals()` 真的会跑，特效层与驻留实体由映射产出；
- 映射拿不到任何可播放动作的行**不注册**——一个按了没反应的按钮比没有更糟。

剑士 SKL 共 74 个主动技能，其中 9 个是手工链，剩 65 个由映射注册，合计 74 条。

## 3. 解锁与分页

`unlockAllSkills()`：

- 每行 `level = maxLevel`（越过 `skill+59C` 的 `unlearned_skill` 闸门）；
- `requestSkill` 里跳过 `skillUseEligibility`（学习账本的前置/等级/SP 校验）；
- MP 与冷却不再拦截：`skillLabUnlocked_` 让扣蓝后立即回满、CD 检查短路。

十二个源版快捷栏放不下 74 条，所以热键栏分页：`bindings[i] = page * 13 + i`，
**F1/F2 翻页**（新键位 40/41，走 `applyInput` 的视图分支，不受眩晕/动作阻塞），
HUD 画 `技能页 n/N` 与当前技能名。`selectCharacter` 末尾会重新应用一次，否则切角色/读档时
`skills = swordmanSkills_` 会把解锁悄悄冲掉。

## 4. 撞出一个真实崩溃

扫射第 13 步就挂：`Unbound CHR motion: character/swordman/swordman.chr: guard.ani`。
这不是映射引入的——手工分支的 `add(1, {{"guard"}})` 一直引用一个 CHR 上**没有绑定**的动作，
只是以前没人把 13 个槽全按一遍。修法放在解析处而不是绕开：

- `actorAni()` 的 `motionByStem` 包 try，失败退回 `[waiting motion]`；
- `overlaps()` 里同一处解析同样兜底（碰撞采样也是解析点，不然换个位置照样崩）；
- 注册时用 `CharacterDefinition::motionByStem` 把映射给的动作回查成 CHR 真实绑定的路径，
  查不到的行不注册。

## 5. 验证

- `--skill-lab-sweep`（配 `--smoke 115`）自动把 6 页 74 个槽逐个释放，事件流里
  `stage` 覆盖 **74 个不同技能 id**，`skill_page` 走过 `2/6…6/6→1/6`，无 `fatal.json`；
- `skill_visuals` 诊断事件给出每行实际生成的层数：`ghoststep` 30、`icewave` 20、`firewave` 17、
  `momentaryslash` 14、`saya` 14、`grabblastblood` 13、`wavemark` 13、`reflectguard` 9、
  `bremen` 6、`tombstonerain` 4；**8 个技能为 0 层**（`hitback`、`sacrifice`、`bloodblast`、
  `darktoleranceup`、`diehard`、`overdrive`、`reckless`、`backstepcutter`），映射本身没有可画资源，
  如实留空；
- 截图 `checkpoints/tests/skill-sweep3/last-frame.png`、`captures/detail-*-phase-*.png` 画面正常，
  HUD 技能名与页码可见。

## 6. 角色进入失败（`Prepared compatibility shape differs`）

体验版第一次点「进入角色」就失败，运行日志
`project/reports/runs/<id>/character-entry-error.json`：

```json
{"slot":0,"error":"Prepared compatibility shape differs"}
```

抛出点在 `skill_runtime.cpp` 的 `publishPreparedSkillRuntime`：`skills.size() != activeLevels.size()`。
形状来自 `compatibilitySkillView()`，它**写死返回** `swordmanSkills_`（9 条手工链）；而实验室解锁
之后 `skills` 是 74 条。投影按 9 条算、世界表是 74 条，任何一次发布（读档、切角色、学技能）
都会拒绝。扫射测试没抓到，是因为 `--smoke`/`--skill-lab-sweep` 的自动路径根本不经过
`resumeCharacter()`，只有人手按 Enter 才走。

两处修：

- `compatibilitySkillView()`：实验室开启且身份就是当前角色时返回活的 `skills`。它是技能投影、
  存档白名单、形状闸门三处共用的唯一视图，留着旧前缀就必然和 `skills` 打架；
- `publishPreparedSkillRuntime()`：映射行没有持久账本记录，序列化状态合法地把它们投影成 0。
  实验室模式下 `projected == 0` 不再回写，否则每经过一次存档，74 条里 65 条会被重新打成"未学"。

顺带补了回归入口 `--enter-first-character`：在选人界面自动按一次 Enter 走真实的
`prepare → store.apply → publish` 全链，不再依赖键盘。

验证（存档副本 `saves/entrytest`，不动用户存档）：`character-entry.json` 落地
`status=entered`、`checkpoint_saved=true`、`town.ok=true`，无 error 文件；随后
`--skill-lab-sweep --smoke 70` 覆盖 49 个技能、无崩溃、8 个 0 层技能仍是那 8 个。

## 已知边界（技能实验室）

- 技能**伤害**仍走 `legacySkillDamage(id, phase)` 的旧表，映射新增的 65 条不在表里，多半是 0 伤害；
  这一轮只解决"动作 + 特效能不能出来"。
- `[level info]` 的连招/多段参数没有接进阶段推进，除手工 9 条外都是单一动作链按 ANI 时长播放。
- 被动技能（D 级 1302 行）不注册，`passives` 仍是手工那 6 条剑士被动。
- 主线仍是剑士；切非剑士走实验运行时，那里只调了它自己的 `setExperimentalSkillPreviewEnabled`，
  没有接映射表（`registerMappedSkills` 见到 `experimentalRuntime_` 直接返回）。

---

# 技能时间轴 / 脱手实体 / 坐标原点 / 主线接入（2026-11-10 第四轮）

节点 `skill-timeline-persistent-20261110`。用户反馈四件事：**特效没有源时间轴**（所有层同时播）、
**脱手技能缺失**（念气环绕的球、千莲怒放的花、极·鬼剑术悬空的剑）、**特效位置/原点不对**、
以及**成果没有落到可游玩主游戏**。

## 1. 源时间轴：`.als` 旁挂脚本

父动画的 `.als` 才是客户端真正的层时间轴，语法在 `effect_plan.cpp` 里早已实现，只是预览器没用：

```
[use animation]  "Animation/xxx.ani"   instanceName
[add]      <帧号> <层号> instanceName
[remove]   <帧号> <层号> instanceName
[create draw only object] <帧号> instanceName <x> <y> <z>    // 唯一带源偏移的写法
```

`SkillVisualMapping::effectLayers` 现在为每一层记录 `timed / alsFrame / alsLayer / instance /
offsetX/Y/Z`：有旁挂脚本的层由源帧出生（`evidence = "ALS [add] frame N"`），没有旁挂脚本的层按
文件名词里的释放阶段序（`effectStageOrder`）排序，再按动作链段数分摊，`evidence` 写
「no ALS sidecar」。**旁观事实**：1031 只给男法、男格斗、圣职等职业配了 `.als`，女格斗与剑士
的 `character/fighter/animation/nenflower.ani`、`character/swordman/animation/hundredswordready.ani`
都没有旁挂脚本，所以那一半只能是重建。

同时修掉一个真 bug：`PreviewLayer::visible()` 原先只看自身时钟，层在出生前就被绘制（时钟停在 0），
48 层的剑术家族因此变成一整片白光。现在 `visible(actionMs)` 同时判断出生与存活。

## 2. 脱手技能：`persistents`

`passiveobject/character/<job>/<skill>.obj` 的动作表里，**长循环**（60 秒）与**单帧地面贴花**就是
「施放后留在场上」的实体信号：

| 技能 | 实体来源 | 判定 |
| --- | --- | --- |
| 念气环绕 `spiralnen` | `SpiralNen.ani`（200ms 循环） | 名字含 spiralnen；球数按职业 2（女）/4（男） |
| 千莲怒放 `nenflower` | `NenFlower/Ground.ani`（1 帧） | 单帧 + 名字含 ground，地面放置物 |
| 极·鬼剑术 `hundredsword` | `HundredSword/swordair1.ani`（60050ms 循环） | 循环长度 > 动作时长，悬空剑 |

球心半径 62px、转速 72°/s、垂直压扁 0.32、悬剑间距 56px、高度 -160px 全部**不在任何 PVF 文件里**，
属于重建参数，`PersistentPlan::evidence` 逐条写明；数量来自资源结构（`SpiralNenTail1..4` 的尾巴数、
`HundredSwordMoveReady1..5` 的 move 段数）。`_ds`/`at` 变体按职业去重（`spiralnen` 与 `atspiralnen`
只取一个），避免同一把剑画两遍。

千莲怒放的动作只有 700ms，放置物需要更长时间才成立：存在驻留实体时动作窗口扩到 2600ms，
层出生时刻按比例缩放，身体播完后停在末帧。

## 3. 坐标原点

- 帧级偏移本来就由 `Renderer::animation(pose.x, pose.y)` 应用，问题不在这里。
- 真正错的是**层锚点**：特效层全部画在角色脚底原点，而 `passiveobject` 的动画锚点是对象生成点
  （`.obj` 的 `[floating height]` 表示悬浮格数）。驻留实体改为按类型给锚点（球 -78px、悬剑 -160px、
  地面 0），并且**不再重复当作普通层播放**（此前 `spiralnen.ani` 既当层又当实体，闪一下）。
- ALS 的 `[create draw only object]` 带 XYZ，已作为 `offsetX/Y/Z` 原样传递；普通 `[add]` 没有偏移，
  保持 0，不做假。

## 4. 主线接入（native）

`src/tools/skill_preview_mapping.cpp` 编入 `dnf_core`，`World` 新增 `spawnSkillVisuals()`：
技能起手时用同一张表生成 `Effect` 层（`born` 按 `birthRatio` 偏移动作时长），驻留实体生成
`Effect` 并新增 `orbitRadius / orbitSpeedDeg / orbitPhaseDeg / orbitCenterY` 四个字段，由 `update()`
每帧按角度重算位置。手工登记视觉的技能（`Skill::manualVisuals`）跳过，避免重叠。

## 结果

- 映射评级不变：A 264 / B 287 / C 170 / D 1013（1734 行），预览器回归 37/37。
- 点名技能：念气环绕 2 球（女）/ 4 球（男）绕身旋转；千莲怒放地面花 + 15 层阶段特效；
  极·鬼剑术 5 把悬剑 + 48 层（ready → swordair → slash → light → tail → finish）按阶段出生。
- 截图核验：`checkpoints/analysis/fx-nen-orbit3.png`、`fx-nenflower.png`、`fx-hundredsword*.png`。

## 已知边界

- 女格斗 / 剑士没有 `.als` 与 `sqr` 脚本（PVF 里只有 atmage/creatormage/priest 三个职业有），
  阶段时序与球体运动全是重建；exe 里那段共享施法 state 的 `Sprintf(加密段模板)` 仍未恢复。
- 千莲怒放「再次点击引爆、念气技能催熟」是游戏内交互，预览器只呈现「放置 → 引爆」两段；
  主游戏需要技能状态机，本轮没有做。
- 主游戏端到端截图核验未完成（`dnf_native --smoke` 可启动但本环境未产出逐技能画面），
  接入正确性目前由编译 + `dnf_tests` + 映射表一致性支撑。
- `dnf_tests` 的 `Airborne reaction preserves current recovery route without hurt RNG` 为**既有失败**：
  用 `git stash` 回到本轮改动前重编仍失败，与本轮无关。

# 全职业技能特效补全（2026-11-10 第三轮）

节点 `skill-effect-families-20261110`。用户反馈：格斗家「念气罩 / 雷龙出海 / 千莲怒放」仍丢特效，
男魔法师动作很全但**特效几乎全缺**（冰魄剑、魔法炮、破冰飞刃等），要求全职业复查并补全。

**根因：特效按「技能目录」组织，原实现只按「文件名前缀」找**

1031 把技能特效放在以技能命名的目录里，目录内的文件名是描述性的、**不含技能名**：

```
character/fighter/effect/animation/atnenflower/start_line_dodge/start_line_06_dodge.ani
character/mage/effect/animation/aticesword/01_light_dodge.ani
passiveobject/character/mage/animation/atmagiccannon/00_magiccannon_fire_dodge.ani
```

原实现要求「文件名以技能 stem 开头」，因此这些目录一个都进不来——男法师 38 个主动技能只有 2 个
有特效，格斗家高等级技能也大面积空白。目录匹配同时解决了男法、格斗、剑士和枪手的一批缺口。

**修复（`skill_preview_mapping.cpp/.hpp`）**

1. `JobIndex.effectFamilies`：把 `character/<job>/effect/animation/` 与
   `passiveobject/<job>/animation/` 下的 `.ani` 按**第一级目录**分组（根目录下的文件自成一族）。
2. 技能 → 族匹配：`stem` / `at+stem`（男法、男格斗）/ `stem+阶段词`；EX 技能回退到去掉 `ex` 的
   基础 stem（权重更低）；`at*` 族对非 `at` 职业降权，只有没有本职业族时才借用。
3. 命名对不上的显式别名：`nenguard→nenshield`（念气罩）、`sajahu→roarstun`、`sajahuex→roarstunex`、
   `kikouken→atspiralnen`、`nenmonsterwhitetiger→nenmonster`、`pushout→atpush`。
4. 一个族里的文件按子目录轮转取样（上限 12 层），避免 `atnenflower` 的 142 个文件只播第一段。
5. 被动对象补两处：`[basic motion]`（弹道/爆炸类对象用单条基本动作，而不是 `[etc motion]` 表）与
   `[string data]`（对象声明的 `.ptl` 粒子，枪手子弹的可见爆炸全在这里）；相对路径按对象所在
   职业目录解析（`../../Common/...`）。
6. 剑士/暗黑武士共用 `character/swordman`：`_ds` 孪生优先，没有孪生时才用普通文件。
   原实现把普通文件对暗黑武士一律过滤，导致「杀意波动」这类**暗黑武士专属技能**反而拿不到
   `dotarea*.ani`。

**结果（1734 行，`--audit-map`）**

| | A | B | C | D |
| --- | --- | --- | --- | --- |
| 本轮前 | 116 | 492 | 113 | 1013 |
| 本轮后 | 264 | 287 | 170 | 1013 |

- 主动技能里「有动作但零特效」从 **409 → 187**；D 级 1013 条**全部是被动技能**，无主动技能无资源。
- 各职业零特效主动技能：剑士 31→14、格斗 37→14、枪手 31→20、法师 47→29、圣职 45→7、
  男枪 30→19、盗贼 35→22、男格 44→15、**男法 38→5**、暗黑武士 61→34、缔造者 10→8。
- 用户点名：念气罩 3 层、千莲怒放 12 层、雷龙出海 12 层、冰魄剑 6 层、魔法炮 14 层、破冰飞刃 16 层。
- 截图复核：`checkpoints/analysis/fx-{icesword,magiccannon,nenflower,lightningdragon,nenguard,poi2,ld2}.png`。
- 回归 37/37 通过；`verify_architecture` pass（139 单元）。

**已知边界**

- 特效层没有源时间轴（`.als` 只覆盖 81 个技能），预览器把所有层从第 0 帧同时播放；
  千莲怒放这类含全屏闪白的技能在起始帧会盖住角色。这是回放策略限制，不是缺文件。
- 剩余零特效主动技能集中在：女法全部是召唤类（召唤物是 `monster/*` 实体，不是特效 ANI）、
  盗贼/枪手多为平砍与 Buff、暗黑武士多为无特效的普通斩击；5 个通用技能（后跳/跃翔/远古记忆/
  不屈意志/受身蹲伏）本来就没有特效。
- `sq_SendCreatePassiveObjectPacket(id)` 的 id→`.obj` 反查仍未做，实体仍靠技能名匹配。

---

# 高等级技能链补全（2026-11-10 第二轮）

节点 `skill-high-tier-20261110`。用户反馈：低等级普攻类技能正常，**高等级技能基本无法使用**，
表现是「特效不全」或「人物动作不全」。逐条核对后确认四个独立缺口，全部已修。

**缺口与证据**

1. **被动对象视觉从未接入**。高等级技能的主视觉不是 `effect/animation`，而是
   `passiveobject/character/<job>/<skill>.obj` 的 `[etc motion]`：
   `khazan.obj` → Khazan1/2 + KhazanAreaAppear1/2/Stay/Disappear，`saya.obj`、`bremen.obj`、
   `tombstone.obj`、`blache.obj`、`epidemicrasa.obj`、`icewave1..6.obj`、`firewavebig.obj` 同理。
   这些路径既不在 CHR 的 etc_motion 里，也不在 effect 目录下，原实现完全看不到。
2. **CHR 基础动作槽没被当作技能动作**。`[buff motion]`（= `Summon2.ani`）、`[back motion]`、
   `[jump motion]` 是具名槽，`BackStep` 本身就是 `[back motion]`，buff 技能则直接播通用施法姿势。
3. **生成器门槛过严**。`gen_exe_bindings_header.py` 原先只收「资格代码对」或「动作名以 SKL 前 8
   字符开头」的 state，把同一职业内**独占 state**（资格代码已唯一绑定该技能）的 30 条证据全部丢弃。
   另把 SKL 名截成 8 字符，`ashenfork`→`ashenfor` 这类边界直接失配。
4. **exe 覆盖会丢掉同名后续阶段**。exe 绑定只给释放入口动作，`KallaFinish1..3`、
   `HundredSwordMoveReady1..5`、`HundredSwordMoveSlash1..5` 靠 CHR 名字匹配才拿到，
   覆盖时被整体替换掉。

**修复**

- `skill_preview_mapping.cpp/.hpp`
  - `JobIndex` 新增 `passiveObjects`（`_ds` 孪生按 CHR 归属过滤）与 `passiveAnimations`；
    实体候选按「精确 stem → 逐级前缀（tombstonerainex→tombstonerain→tombstone）」依次尝试，
    没有 `[etc motion]` 的对象不算视觉本体，继续下一个候选。
  - 新增 `baseMotions`（具名槽 → `.ani`）与两张显式表：基础动作别名（backstep/jump/dashattack…）、
    动作别名（`reckless → frenzy1..4`，暴走；Frenzy 槽无其它技能认领）。
  - `chainOrder` 重写：阶段词支持多词组合（`hundredswordmoveready2`、`weaponcomboshort1`），
    武器/形态词（short/light/heavy/blunt/blade/spear/claw/pick/shoulder）入表；新增
    「阶段词在前」（`staysacrifice`）与「升级词在后」（`flowmindpowerup → FlowMindStart`）两支。
  - exe 绑定改为**入口动作 + 同名后续阶段合并**（上限 12 段），不再整体替换。
  - `[pvp]` 变体与 `_ds` 孪生双向过滤，swordman / demonicswordman 不再互借动作。
- `gen_exe_bindings_header.py`：采信条件扩为「资格对 / 动作名吻合（完整 stem 双向）/ 本职业独占
  state」，产物记 `basis`；未采信的共享 state 单独计数（本轮 185 条）。

**结果（1734 行技能映射，`--audit-map`）**

| | A | B | C | D |
| --- | --- | --- | --- | --- |
| 修复前 | 47 | 322 | 62 | 1303 |
| 修复后 | 116 | 492 | 113 | 1013 |

- 剑士（job 0）：A 9→18、B 29→40、C 6→16、D 131→101，**剩余 101 条全部是被动技能**
  （`[type] [passive]`，本来没有释放动作）；74 个主动技能全部为 A/B/C。
- 里·鬼剑术拿到 15 段武器区分动作，极·鬼剑术 13 段，暗天波动眼 8 段，冥炎之卡洛 6 段（含 Finish1..3），
  暴走 4 段 Frenzy；卡赞/萨亚/普戾蒙/罗刹/银光落刃从「无资源」到有实体特效。
- 回归 `dnf_skill_preview_tests` 37/37 通过，`verify_architecture` pass（139 单元）。

**仍未闭合（已确认边界，不是解析遗漏）**

- 剩 16 个剑士主动技能只有特效没有身体动作（卡赞/萨亚/萨亚EX/普戾蒙/罗刹/银光落刃/嗜魂之手/
  冰刃·波动剑/爆炎·波动剑/邪光斩/波动爆发/杀意波动/不动明王阵/极冰·裂波剑/死亡墓碑/墓碑三绝阵）。
  根因：这些技能走**共享施法 state**（state 75/13 等），handler 内按 skill id 分支后不是用
  `vtable+0x49C` 立即数，而是 `Sprintf` 拼动画名后 `vtable+0x154`——模板串在 1031 exe 的加密数据段
  （段 2 的 raw 只有 460 KB / 虚拟 4 MB，文件与旧内存 dump 里都读不到明文），静态拿不到。
- `sq_SendCreatePassiveObjectPacket(id)` 的 id → `.obj` 反查仍未做；实体目前靠技能名匹配。
- 其余职业（格斗/枪手/法师/圣职/盗贼）同样受益，但未逐技能人工复核。

---

# 技能链解析核对与修复（2026-11-10）

节点 `skill-chain-audit-20261110`。核对预览器的技能/特效链文件解析，确认并修掉三类漏解析。

**核对结论（1734 行技能映射）**

- 本体动作缺失是主因：只有 406 行（23%）定位到 `bodyAni`，1320 行（77%）连动作都没有，
  自然没有特效；本体+特效+攻击框齐全仅 52 行。
- 特效声明有三层来源，原实现只用了最弱的一层：
  1. `sqr/common.nut` 的 `sq_LoadSkillEffect_<Job>`——**只有 Swordman / DemonicSwordman 两个函数**，
     其余职业根本没有（不是解析漏，是文件里不存在）。
  2. `sqr/character/<chr>/<skill>/<skill>.nut` 的 per-skill 脚本（160 个文件）：
     `sq_CreateCNRDAnimation` 62 处、`sq_AddStateLayerAnimation` 62 处、
     `sq_SendCreatePassiveObjectPacket` 81 处、`sq_SetCurrentAnimation` 106 处。原实现完全没读。
  3. `character/<job>/effect/animation/` 的文件名前缀匹配（原实现主路径，且上限 6）。
- `.ani` 内部没有 effect 段（实测 HardAttack1.ani 只有 img/坐标/damageBox），
  特效时间轴来自同名 `.als` 侧车：PVF 共 1179 个，1173 个与 ani 配对，但只有 81 个技能本体 ani 带 als。

**修复（`skill_preview_mapping.cpp` / `.hpp`）**

- 新增 per-skill 脚本索引：`sqr/character/<chrStem>/<skill>/`（嵌套）与 `<skill>.nut`（扁平），
  含 `po_*.nut`；脚本里的 `sq_CreateCNRDAnimation` / `sq_LoadSkillEffectAni` 字面量按
  `character/<baseJob>/` 解析成 effect ani。
- 新增 `CUSTOM_ANI_*` → CHR `[etc motion]` 索引 → `.ani` 链路：job `*_header.nut` 常量表 +
  CHR 资源按 `(fieldOffset, valueIndex)` 排序。已用 97 个常量/97 条 etc_motion 逐一验证
  （`CUSTOM_ANI_FIREPILLAR1=55 → ATAnimation/FirePillar1.ani`）。
- 特效来源改为**权威优先**：common.nut 声明 > per-skill 脚本 > 前缀兜底；上限 6 → 24。
  前缀兜底收紧为「直接位于 effect/animation 下」或「父目录名等于技能名」，排除
  `chillingpowder/upperswing1.ani` 这类别的技能分支。
- 结果：鬼斩从 6 个（混入 4 个 `*_ds`/`*_fullcharge`）修正为 common.nut 声明的 2 个；
  总特效条目 673 → 706（更准，不是更多）；本体 406 → 414（缔造者 6 → 13）；
  5 个技能（复仇者/元素师）首次拿到脚本声明的特效链。回归 37/37 通过，架构检查 pass。

**仍未闭合**：`sq_SendCreatePassiveObjectPacket(id)` 的 id → `.obj` 需要数据流与 `.lst` 反查；
`.als` 覆盖仅 81 个技能；1320 行技能仍无本体动作（state→motion 未恢复的职业）。

---

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
