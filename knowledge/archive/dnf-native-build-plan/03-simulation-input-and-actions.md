# 03 固定模拟、输入、动作与实体生命周期

版本：v1.1；日期：2026-10-18；状态：**技术设计，待实施**。本章不是运行时完成声明。数值、字段与步骤中标为“推荐”的内容属于 beta 重建策略，后续原生证据可替换；不得将推荐值写回 PVF。

## 1. 当前基线与目标

现有 `World` 使用独立模拟时钟和输入队列；已有 `CharacterController::request/tick/cancel`、`AnimationEventCursor`、XYZ 接触、`axis_motion`、`static_motion`、`particle_motion`。分轴算术已接入部分跳跃／浮空；水平运动及粒子部分算术仍是独立模块。`World` 仍混合鬼剑士阶段、十字附层、抓取、运动、命中及表现管理，身体帧与武器碰撞仍未完全解耦。

目标是建立跨职业、怪物、被动物件和地图物件共享的执行内核；SDL 只负责输入、窗口和绘制。任何技能特例保存在独立控制器及其证据登记中，不进入全局 tick 的职业名分支。原生状态请求不必立即提交，不能把“请求成功”解释成已完成动作切换。

## 2. 时钟与输入接口

沿用 **60 Hz，整数纳秒×60** 的累计形式：`accumulator += elapsedNanoseconds * 60`，每累计 `1,000,000,000` 单位执行一次 tick。tick 序号是唯一模拟排序依据；`simulationMs = floor(tick * 1000 / 60)`，相邻整数毫秒步长为 16/17ms。长时间乘法使用带溢出检查的整数；渲染插值不能反向写入模拟位置。禁止因显示器刷新率改变 tick、攻击次数、CD 或动画事件次数。

来源算术按其实际边界保留 i32 回绕、float32 存储、截断和运算顺序；源要求的位置不能升级 double 后称为等价。编译相关核心禁用 fast-math／重关联／未证明的融合运算，固定浮点测试记录编译器与选项。采用 double 的现有位置需要逐模块迁移及差分测试，不能一次全局替换。

```cpp
struct InputCommand {
    uint64_t sequence, targetTick;
    DeviceId device;
    LogicalAction action;
    InputEdge edge;                 // Down / Up / Axis
    int horizontal, vertical;
    std::optional<SkillKey> skill;
};
struct ActionRequest {
    RequestId id;
    ActorHandle actor;              // id + generation
    LogicalAction action;
    std::optional<SkillKey> skill;
    uint64_t receivedTick, expiresTick;
    ActionInstanceId continuationOf;
    DirectionSample direction;
};
struct RequestResult {
    RequestStatus status;          // Rejected / Buffered / PendingCommit
    ReasonCode reason;
    SourceRef policySource;
};
```

输入适配器将键盘、手柄、触屏、其他平台按键转换为逻辑动作。记录原始设备事件和归一化事件，保留 sequence；同一 tick 按 sequence 处理。系统自动重复键不产生新的 Down 边。释放窗口焦点、切换输入模式、加载场景时生成受控释放事件，防止持续跑动／攻击；输入清理原因进入诊断。

命令输入保留方向相对朝向、按下／松开、组合键及超时语义，不用屏幕上的键名字符串直接判定。源有命令数据时从源读取；双击跑间隔、缓冲时长若缺少证据，放入有依据的 `InputPolicy`，可由测试设置切换并记录，不能散落于控制器。

## 3. 动作与状态模型

```cpp
struct ActionInstance {
    ActionInstanceId id;
    ActorHandle owner;
    ControllerKey controller;
    uint64_t startedTick;
    int phase;
    ActionLocalState locals;
    std::vector<AnimationHandle> animations;
    CleanupLedger ownedResources;
    ResourceTransactionId consumption;
};
struct PendingTransition {
    ActorHandle actor;
    StateId from, to;
    RequestId request;
    TransitionPayload payload;
    CommitPhase phase;
};
```

状态机接口为 `request → validate → queueTransition → exitOld → enterNew → tick → onEvent → cancel`。进入失败必须给出来源及依赖能力诊断；不能创建空控制器并返回成功。动作创建前准备所需资源和资格，扣费与状态提交组成原子边界；如果资源在提交后发生不可恢复错误，按事务记录回滚尚未产生外部效果的消耗，避免“扣蓝但没动作”。已经造成伤害／奖励的动作不能简单回滚世界，改为安全退出并记录故障。

每个动作分别声明：地面／空中条件、转向策略、移动策略、前置状态、取消窗口、打断优先级、结束条件、死亡及离场行为。推荐通用移动模式包含锁定、受输入控制、惯性、源速度曲线、追踪目标、抓取约束；模式参数仍由源或独立适配描述提供。

取消与缓冲必须区分：

- 未到取消窗的输入可进入有期限队列；队列容量、覆盖规则来自策略。默认同一动作槽保留最新一次，方向输入独立处理，避免无限排队。
- 到期消费时重查学会等级、MP、CD、角色状态、武器、目标及资源能力。先前校验成功不是永久许可证。
- 续段绑定当前 `ActionInstanceId`；旧动作结束后不能将旧续段请求重新解释为新施放。
- 取消依据源帧／事件与状态条件，不把当前 100% 时钟下的毫秒数固化为所有攻速通用窗口。
- 技能结束后方向仍按住时默认恢复步行；重新冲刺需要新的合法跑动请求，除非对应控制器明确允许保留冲刺。
- 受击、抓取、死亡、换房、角色切换和重载的优先级单列；死亡必须能终止霸体动作。

## 4. 推荐 tick 管线与补 tick

以下顺序是可验证的重建默认，已证实原生消费者有不同相位时按版本策略调整：

```text
固定 tick 开始
  1. 消费到期输入和调试命令；更新持续时间、CD及条件状态
  2. 验证动作请求，提交本相位允许的状态转换
  3. 推进角色/怪物/物件控制器与各自局部时钟
  4. 分轴运动积分、地图约束、落地与抓取约束
  5. 推进 ANI/ACT/ALS/PTL，消费所属语义的事件
  6. 形成有效攻击体，广相筛选、XYZ窄相接触
  7. 接受命中、伤害事务、状态响应和命中停顿
  8. 提交生成/销毁/死亡/奖励事件；清理失效句柄
  9. 输出只读 RenderSnapshot 与诊断摘要
```

同 tick 新生成实体是否立刻参与碰撞由创建事件语义声明；缺少证据默认下一 tick 激活，避免容器迭代顺序决定结果，并标为推理。实体遍历按稳定身份排序；随机流按子系统／实例独立派生，不因绘制跳帧消耗随机数。

积压时连续补真实 tick，不采用一次超大 delta 跳过中间判定。每轮循环可限制处理数量以维持窗口响应，但保留剩余积压，不静默丢模拟时间。失焦暂停、用户暂停和系统长休眠由会话策略明确处理；恢复时重设墙钟基准，不能把睡眠数小时作为战斗补 tick。暂停期间输入和调试命令的处理策略需要固定并记录。

已恢复的离散运动模块每个原tick只积分一次，沿用16/17ms及原截断／float32边界。动画在同tick内跨多个事件，不代表可把运动delta拆成若干段；拆分可能改变已证实结果。仅声明并验证了子步合同的执行器可按事件边界细分运动，其他执行器独立推进事件游标而不重复积分。扫掠也仅在已启用的明确接触策略下执行，不能作为所有实体的默认替代。

## 5. 动画、事件与独立时钟

`AnimationDefinition` 不可变，保存源帧时长、框、事件、坐标、混合参数和未知属性；`AnimationInstance` 保存局部年龄、倍率、帧索引、事件游标、循环次数与父对象关系。身体、武器、附层、弹丸各有实例；源明确同步时建立同步关系，不能默认用身体帧索引访问武器。

**原生单 pending ANI 事件** 与 **通用 authored 事件时间线** 必须使用不同模式：

- `NativeSinglePending` 保留当前已恢复的 producer／consumer、pending 槽和消费阶段；多个事件覆盖、保留或合并行为按原证据执行，不擅自改成无损队列。
- `TimelineAllCrossings` 用于已明确可枚举的 ACT/ALS 或新建兼容时间线；每个补 tick 中逐边界消费，使用 `(instance, loop, eventOrdinal)` 去重，不因帧跳跃漏播。
- 不能为了保证“事件不丢”而改变原生单 pending 语义；也不能将其推广到所有资源。能力清单记录每种消费者的模式。
- 保留零时长、超长保持帧和循环标志。对零时长循环设置执行预算与诊断，生命周期由控制器解释，不能擅改源帧时长。

动画倍率：来源 ANI 百分数 100 为正常；CHR 常见 1000 基准是另一单位。两者在明确适配边界换算。源 `n*g*.001` 局部证据不能证明所有职业最终 `n` 的生成。每个实例只能选择一种 `ClockMode`：`NativeIntegerFrameDelay` 按原生整数规则重算各帧有效delay并推进普通时间；`ScaledLocalAge` 保持源帧时长并按倍率推进局部年龄。禁止同时缩短delay和加速局部年龄而双乘倍率，两种模式在截断边界不保证等价。变速保留已消耗的当前帧相位，按所选模式及来源规则转换剩余时长／局部年龄，不能重播已消费事件；已证实原生时钟重设行为以显式策略覆盖。

## 6. 运动、接触、停顿与生命周期

位置以地面 XY 与高度 Z 分开，渲染投影不能参与物理。所有碰撞保留完整 XYZ；左向盒变换按源边界 `-x-width`，不只反转中心。接触、接受攻击、扣血、打断是不同步骤。扫掠检测若原生未证实，应标为推理策略，不能无条件替换离散接触。

`axis_motion` 与 `static_motion` 接入前必须补齐最终属性、方向、碰撞、加速度到期、动作退出和所有者生命周期。粒子纯算术不等于被动物件控制器；PTL owner modifier 和持续生成分别建模。

hitstop 分攻击者、目标及可选附层局部时间域。世界时钟、CD、输入默认继续；是否冻结弹丸、角色位移及 buff 时间由来源策略指定，不能停止整个 `World`。动画坐标插值只用于绘制，不能改变碰撞采样。

生命周期为 `Created → Active → Dying/Terminating → Removed`，不得仅凭 ANI 最后一帧删除需要后续事件的实体。`CleanupLedger` 登记本动作拥有的附层、攻击体、modifier、抓取关系、声音循环和脚本引用；退出按所有权释放，不能清除角色的全部 buff。父实体死亡后的子实体采用源声明的独立存活／随父销毁策略。销毁采用稳定句柄及 generation，延后统一提交，避免悬空引用。

## 7. 未决项与推荐处理

| 未决项 | 当前推荐 | 替换条件 |
|---|---|---|
| 最终移动／跳跃属性修饰 | 接来源可解释属性；暂时缺口放入版本化 motion 策略并暴露诊断 | 闭合原生属性消费者后替换 |
| 双击／缓冲／转向采样 | 单独 InputPolicy；不得沿用鬼剑士值给全部职业 | 脚本或原生输入链证明 |
| tick 内新实体激活 | 默认下一 tick，记录推理 | 已知创建调用相位 |
| 各实体 hitstop 域 | 默认只冻结明确绑定的动作域 | 原生／用户对照证明 |
| 原生异常浮点行为 | 非有限数据拒绝并保留源诊断 | 有必要且可安全复现的格式合同 |

## 8. 实施任务

- **P03.1** 固定时钟、输入序号、逻辑输入与重放接口；保留现有整数纳秒×60。
- **P03.2** 动作实例、状态请求／提交、取消／缓冲和消费事务接口；先迁移现有鬼剑士行为以回归。
- **P03.3** 动画实例与时钟解耦；实现两种事件消费者及补 tick 规则。
- **P03.4** 运动模块接入、XYZ约束、抓取和 hitstop 域；逐项保留推理策略。
- **P03.5** 稳定实体句柄、事件队列、所有权清理、故障诊断和重放摘要。
- **P03.6** 将通用内核暴露给 P05 属性装备、P06 行为／脚本与 P07 战斗；禁止新增职业专用 World 分支。

## 9. 正反验收

正例：30/60/144/240 渲染频率相同输入与 seed 产生相同模拟摘要；一次补多个 tick 仍遵守原事件模式；普通三连、冲刺退出、空中恢复、变速动画与独立弹丸按所属时钟执行。

反例：旧续段不能触发新动作；缓冲期间卸武器／耗尽MP后提交必须失败且无扣费；丢焦点不遗留按下；死亡／换房不留抓取和无敌；多个攻击交替接触不重置对方登记；未知资源与工厂创建失败必须有可定位诊断。

专项覆盖：单 pending 多事件边界、零时长循环、超长保持帧、倍率变更、暂停与恢复、时间回退拒绝、溢出边界、对象 generation 重用、父子不同生命周期、hitstop 时 CD 和输入推进。

## 10. 来源与关联

- [现有交接](../dnf-native-demo/CURRENT_TASK.md)
- [控制器接口](../dnf-native-demo/include/dnf/character_controller.hpp)
- [战斗现状](../dnf-native-demo/include/dnf/combat.hpp)
- [状态与攻击证据](../dnf-native-demo/reports/combat-native-reverse/state-attack/findings.md)
- [动画事件](../dnf-native-demo/reports/combat-native-reverse/animation-events/)
- [水平运动](../dnf-native-demo/reports/combat-native-reverse/horizontal-motion/)
- [跳跃与分轴](../dnf-native-demo/reports/combat-native-reverse/jump-physics/)
- [动画与渲染实例](../dnf-native-demo/reports/combat-native-reverse/resource-render/README.md)
- 后续接口：[人物与脚本](04-characters-skills-and-script-host.md)、[属性和战斗](05-stats-equipment-and-combat.md)。
