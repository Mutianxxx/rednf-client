# 男法（atmage）技能脚本 API 证据矩阵

来源：86JP 分享包（`G:/BaiduNetdiskDownload/新建文件夹/分享包`）。**全部为跨版本参考，不是 1031 事实**；
本表只用于"某个 sq_ 名字在 86 侧对应什么"，实现语义仍以 1031 PVF 字节与实机表现为准。

## 数据来源

| 文件 | 行数 | 提供什么 |
|---|---|---|
| `rev/work/exports/research-generated/api-evidence/*.md` | 208 | 对象方法：`声明`（所属类+参数）、`70 uses`、`86 handler` 函数名 |
| `docs/research/native-nut-api-map.tsv` | 297 | 全局函数：`86 VA` + 签名 + 70 调用点证据 |
| `rev/work/exports/research-generated/nut86-func-to-api.tsv` | 300 | 反查：API → 86 函数地址 + callers 频次 |
| `temp-project-dir/nut-dump/*.nut`（本地，1031 PVF 导出） | 114 个 atmage 脚本 | 真实调用点与调用次数 |

产物：`atmage-api-demand.tsv`（280 行，按调用次数降序）、`api-class-index.tsv`（合并索引）。

## 规模

- atmage 脚本 114 个（角色 83 / 被动对象 22 / appendage 9），distinct `sq_` 名 **280**。
- 证据覆盖：`method` 74 + `global` 62 + `freq` 3 + `property` 1 = **140（50%）**；`none` 140。

## 四个必须先修正的认知

1. **`obj.sq_var` 是属性，不是 API（234 次，最高频）。**
   脚本写法是 `obj.sq_var.GetparticleCreaterMap(...)`、`obj.getVar().clear_vector()`。
   它是 `CSQCommonVarlist` 类型的**脚本侧状态容器**，需要按对象挂一个 table，方法来自
   `api-evidence` 的 `CSQCommonVarlist.*`：`clear_vector / push_vector / get_vector / set_vector /
   clear_ani_vector / clear_obj_vector / clear_timer_vector / clear_ct_vector / GetAnimationMap /
   GetparticleCreaterMap`。把它当 API 统计会虚高 234 次。

2. **存在拼写别名，两套都要注册。**
   `IntVectPush`(146) 与 `IntVectorPush`(65)；`IntVectClear`(82) 与 `IntVectorClear`(54)；
   `GetCurrentFrameIndex` 与 `GetAnimationFrameIndex`；`CreateCNRDAnimation` 与 `CreateAnimation`。
   只实现一种会有一半脚本过不了 `inspect()`。

3. **`api-evidence` 的 `声明` 列类归属不可信，不能当类型系统用。**
   实例：`PlaySound`(99) 被标成 `CNFlashScreen`、`GetYPos` 标 `CNFlashScreen`、
   `SetCurrentAnimation`(94)/`GetState`(40)/`GetXPos` 标 `CNRDItemObject`。
   实际这些都是 **SQR 游戏对象的公共方法集**（`obj.sq_XXX` / `obj.getXPos`）。
   唯一可信的两处是写得最具体的：`CSQCommonVarlist.clear_vector()`、`CNRDPassiveObject.addSetStatePacket()`。
   → 实现结论：**不需要按类分表**，一个统一的 handle delegate 挂全部方法 + `sq_var` 属性即可。

4. **同名 API 既有全局调用也有成员调用。**
   `sq_GetIntData` 在 `native-nut-api-map.tsv` 是全局 `0x01560f40`，
   但脚本里普遍写 `obj.sq_GetIntData(...)`。所以同一批函数要同时注册到 root table 和对象 delegate。

## 单技能最小集（实证：chainlightning.nut，384 行）

一次完整施放（`checkExecutableSkill → onSetState → onProc → onEndCurrentAni`）只用 **30 个** API：

| 类别 | API | 次数 |
|---|---|---|
| state/输入 | `IsUseSkill` `IsCommandEnable` `GetState` `AddSetStatePacket` | 1/2/1/7 |
| 向量（substate 传参） | `IntVectClear` `IntVectPush` `GetVectorData` | 4/4/1 |
| 取表 | `GetIntData` `GetLevelData` `GetSkillLevel` `GetBonusRateWithPassive` `GetCastTime` | 5/5/3/1/1 |
| 动画 | `SetCurrentAnimation` `GetCurrentAnimation` `GetCurrentAni` `GetCurrentFrameIndex` `GetFrameStartTime` `GetCurrentTime` | 3/1/2/1/1/1 |
| 位置/朝向 | `GetXPos` `GetYPos` `GetZPos` `GetDistancePos` `StopMove` `SetShake` | 由 getXPos 系列 |
| 速度 | `SetStaticSpeedInfo` | 1 |
| 表现 | `PlaySound` `StartDrawCastGauge` `EndDrawCastGauge` | 2/1/1 |
| 被动对象 | `SendCreatePassiveObjectPacket` `GetPassiveObject` | 1/3 |
| 序列化 | `BinaryStartWrite` `BinaryWriteWord` `BinaryWriteDword` | 1/9/1 |

`sq_var` 属性用到 2 次（`clear_vector` / `push_vector` / `get_vector` / `set_vector`）。
→ **30 个 API 就能让一个技能脚本真正执行**，不是 280。

## 实现顺序（按"能否看到效果"排序）

1. **handle delegate 统一化**：所有 `sq_*` 注册到 root + 对象 delegate，并把 `sq_var` 挂成
   `CSQCommonVarlist` 风格 table（纯脚本侧状态，不碰 World，零风险）。
2. **序列化组**：`BinaryStartWrite/BinaryWriteWord/BinaryWriteDword/BinaryWriteFloat/BinaryGetReadSize`
   —— 纯内存 buffer，与 World 无关，最简单。
3. **取数组**：`GetIntData/GetLevelData/GetSkillLevel/GetBonusRateWithPassive/GetCastTime`
   —— 数据源已在（`.skl` 等级表、`int data`、`bonus rate`），只需 bridge 暴露静态查询。
4. **动画组**：`SetCurrentAnimation/GetCurrentAni/GetCurrentFrameIndex/GetFrameStartTime/GetCurrentTime`
   —— 已解析 ANI，只需让脚本能选动画、读时钟。
5. **state 组**：`AddSetStatePacket/GetState/IsUseSkill/IsCommandEnable/IntVect*`
   —— 依赖已有 692 条 state-skill 对，接上即可。
6. **被动对象**：`SendCreatePassiveObjectPacket/GetPassiveObject/SendDestroyPacketPassiveObject`
   —— 需要被动对象管理器（当前 `objects.hpp` 是呈现层，需扩成可查询实体）。

## 未覆盖清单（140 个，需另行确定语义）

高频且必须有的（86 包无证据，只能从 1031 脚本调用点反推）：

| API | 次数 | 推断依据 |
|---|---|---|
| `AddFunctionName` | 139 | 回调注册名，顶层调用；语义由引擎决定，无需 86 |
| `GetGlobalIntVector` | 57 | 全局向量容器，与 `IntVect*` 同族的全局版 |
| `CreateAnimation` / `CreateCNRDAnimation` | 26 / 62 | 由路径创建 ANI 对象，`skill_preview_mapping.cpp` 已有字符串识别 |
| `AddEffect` / `AddObject` / `AddParticleObject` | 22 / 15 / 15 | 特效/对象挂载，与 `object_presentation.hpp` 对接 |
| `GetCNRDObjectToSQRCharacter` | 22 | 被动对象 → 主人的桥，需要对象双向引用 |
| `RGB` / `SetMoveParticle` / `SetMyShake` | 38 / 26 / 23 | 纯表现参数 |

这批不阻塞"技能能出招"，只影响观感，放在第 5 步之后。

## 第 3 步实测纠正（已落地，commit 随本轮）

**`sq_GetIntData` 读的不是 `[int data]`，是 `[static data]`。**

`chainlightning.skl` 里根本没有 `[int data]` 段（`--skill-sources source` 的 46 个字段中不存在）。而脚本里
五个 `sq_GetIntData` 的常量名是 `SKL_CL_SD_0..4`（SD = **static data**），且该技能的
`[static data]`（common）恰为 `[500, 0, 650, 400, 300]`，与五个访问点的注释
（Y 轴范围 / X 起点 / X 终点 / 链式最大距离 / 目标最大高度）一一对应。
`[level info]` 首元素是列宽 4，level 1 行为 `[7, 1200, 276, 4]`（链数 / 攻击时间 / 攻击力% / 多段次数），
脚本的 `SKL_CL_LI_0..3` 正好是列下标。

因此 `.skl` 侧映射为：
| 脚本访问 | 数据源 |
|---|---|
| `sq_GetIntData(skill, i)` | `[static data][i]` |
| `sq_GetLevelData(skill, col, level)` | `[level info]` 第 level 行第 col 列（首元素为列宽） |
| `sq_GetSkillLevel(skill)` | 角色技能账本 `learnedLevel` |
| `sq_GetCastTime(skill, level)` | `[casting time]`（按 level 取；无等级结构时取首值） |
| `sq_GetBonusRateWithPassive(skill, state, col, ratio)` | `[level info]` 同列值 × ratio（被动加成链未重建，值取自源表） |

**两种调用形态的参数偏移不同（实测，非猜测）**：
- `obj.sq_GetSkillLevel(2)` → 栈 `[this=obj(userdata), 2]`
- `sq_GetSkillLevel(obj, 2)` → 栈 `[this=roottable(table), obj(userdata), 2]`

全局形态把 root table 绑成 `this`，所以真正的参数整体后移 1。宿主必须按"handle 出现在 index 1 还是 2"
判定形态，不能假设统一偏移。

实测锚点（`dnf_tests` group 4，真实 1031 PVF，`{8,2}` 等级 1）：
`GetSkillLevel=1`、`GetIntData(0)=500`、`GetLevelData(0,1)=7`、
`GetBonusRateWithPassive(2,25,2,1.0)=276`、`GetCastTime(1)=600`，两种形态结果一致。

## 第 5 步：把源注册路由接进动作服务（已实现，2026-11-23）

- `SquirrelActionService` 现在从 `sqr/character/atmage_load_state.nut` 读取全部 43 条
  `pushState`：其中 **38 条带 `SKILL_*` 操作数**，5 条是普通攻击/投掷/Buff 等非技能入口。
- `SKILL_`/`STATE_` 数字来自 `sqr/character/atmage/atmage_header.nut`（`dnf_enum_header.nut`
  只含全局枚举，没有男法技能号）。注册行字节区间、技能号、state、脚本路径、回调名一起进收据。
- 38 条里 37 条脚本定义 `onSetState_<Suffix>`；`ManaBurst` 只有 `checkExecutableSkill` /
  `checkCommandEnable`，标记 `source_callback_missing`，不冒充可执行回调。
- 施放时按 `skillId` 选路，VM 载入 `dnf_enum_header` → `atmage_header` → 该技能 NUT，
  以注册 state 调用 `onSetState_<Suffix>`。脚本准入失败/运行时失败只把该次降级为
  「仅动画」并记 `squirrel_skill_source_skipped`，**不阻断**手工配置的 CHR 动作。
- `dnf_tests --group 4`（跳过基线 storage 失败）通过；新增用例验证 `{8,2}` 的路由、
  真实 `chainlightning.nut` 回调执行与收据中的源引用。
- 补充的源码别名：`sq_StartWrite/sq_WriteWord/sq_WriteDword/sq_WriteFloat/sq_WriteByte/
  sq_WriteBool`、`sq_IsMyControlObject`、`sq_GetPowerWithPassive`。这些是 VM 本地序列化
  与**记录式 no-op**，不改变 World，不声称被动对象/伤害原生行为；`WindStrike` 因此从
  「整脚本拒收」变为「准入但 `source_damage_native_api_registered=false`」。

**仍未闭合**：`onSetState` 只是入口回调；`onProc`/`onEndCurrentAni` 的逐帧驱动、被动对象
实体化、`SendCreatePassiveObjectPacket` 的真实消费者仍未接上，所以画面里仍不会出现脚本
生成的ChainLightning电链。技能 MP/CD 评估在链雷上还报 `[weapon skill info]` 行缺失
（状态 `Malformed`），需单独处理，不能与脚本路由混为一谈。
