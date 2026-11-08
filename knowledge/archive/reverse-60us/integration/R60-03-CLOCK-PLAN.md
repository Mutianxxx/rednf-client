# R60-03 时钟与附层接入差异审查

当前实现范围和恢复入口见 [R60-03-PROGRESS.md](R60-03-PROGRESS.md)，最终构建与自动状态见 `R60-03-VERIFICATION.json`。下文及配套JSON保留实施前的只读审查身份；“没有修改或构建”仅描述该历史审查，不代表后续候选状态。

审查日期：2026-10-20。机器记录为 [R60-03-CLOCK-PLAN.json](R60-03-CLOCK-PLAN.json)，含本次只读输入的 SHA256。本文是可实施方案，**没有修改或构建 R60-03 生产代码**。R60-02 的插值/变换核对只消费传入的资源时间；它没有恢复原生角色时钟、有效攻速绑定、hit pause 或 ANI 树调度。R60-02 的 24 组原指令向量与本项的时钟验证是两件事。

## 1. 建议结论

保留现有 60 Hz 模拟和 16/17 ms 整数边界，以一次模拟 tick 产生的动画播放快照统一驱动身体、装备、攻击盒、声音及附层事件。新增独立于渲染 profile 的具名时钟策略；旧 `ScaledLocalAge` 和资源 DELAY=rate100 模式继续可比较。60US 的百分速率/deadline 算术可以复用为 **1031 跨版本推断策略**，不能把它的 timer 通道、地址、状态号或属性布局当作 1031 事实。

最小可见闭环应在普通攻击上完成：同一个时钟决定身体帧和帧内插值、同 motion 武器图层、攻击盒、声音、连击/结束边界；hit pause 恢复后只推进一次。只有 portable helper、播放器倍率或诊断字段不算运行时接入完成。技能专用 movement、cast-speed 分派及完整技能阶段仍留在 R60-04/原工作包，不借本项声称全职业恢复。

## 2. 固定证据与适用范围

所有证据从 `../releases/20261020-01` 只读，不重跑 REA、不改历史 release。原 60US 静态 EXE SHA256 为 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`；1031 当前 EXE/PVF 身份由现有 content profile 另行绑定。地址仅作为证据索引。

| 固定来源 | 可复用结论 | 边界 |
|---|---|---|
| `analysis/combat_motion/motion-contract.json` 的 `clock` / `ani`，`README.md` | 毫秒源经过选通道、百分比缩放及 timer 启用/暂停/偏移门；ANI rate 是百分比。安装和刷新是不同的 float32 表达式；deadline 向零截断。 | 实际角色使用的通道、运行期速率和暂停策略未捕获；没有证明 timer 保留小数余量。 |
| `analysis/combat_motion/native-ani-vectors.json` | 46 个已捕获输出（x87 两种精度）验证给定 decoded delay/rate 的 deadline 算术。 | 不覆盖完整 parser、安装函数、树调度或实际角色运行。本文没有重新执行原指令。 |
| `analysis/combat_timeline/{README.md,evidence-index.json,frame_advance.asm}` | `A27DC0` 使用根 ANI 时间；`now >= deadline` 进入帧推进；非循环结束置 ended 并保留末帧。大步路径也先选末帧后 ended。 | 结束不等于隐藏、detach 或奖励。原生 ANI 回调/ACT 事件与全局调度未全闭合。 |
| `analysis/combat_native_skill_slots/equipment-contract.md` | 同 motion 的装备子 ANI 挂身体树；复制 `min(bodyFrameCount, childFrameCount)` 个 decoded delay；继承 rate，取 root 时间；有符号 key 稳定排序，负 key→身体→非负 key。 | 子层仍保留自己的图像/框和帧集合；不能修改共享原资源或把所有装备层当同一武器。1031 适用性仍需单独记录。 |
| `analysis/combat_hardattack/README.md` | 角色效果层在挂载时独立 reset；指定继承速率 flag 时调用 rate setter；跟随角色位置是另一参数。 | 跟随位置、跟随速率、共享 root clock 是三个不同关系；不能由 `attached=true` 推出全部相同。 |
| `analysis/combat_timeline/README.md` 的 release-wave ended consumer | 纯 ANI 留末帧；特定外层对象检查 ended 后请求移除。 | 不能给所有生成物统一设 `ANI ended -> delete`。消息完成/场景移除时序未实机观测。 |
| `combat-preview/web/timeline.js`、`controllers.py`、`spawned.py` | 交接预览明确区分 body / elapsed / frozen；装备按身体帧，效果按自身 elapsed。 | 这是 rate100/source DELAY 预览消费者，不能升级为完整 native clock。 |

应原样保留的算术：

```text
刷新 rate = f32(Sani * f32(0.1))
安装 rate = f32(f32(Sani) * G * f32(0.001))，60US 初始化 G=100
nextDeadline -= trunc(decodedDelay / rate * f32(-100))
总时长 helper = sum(trunc(decodedDelay * (1/rate) * f32(100)))
root 改速恢复 elapsed = trunc(oldElapsed / newRate * oldRate)
```

不能合并安装/刷新表达式，不能用 `sum(delay)/speed` 代替逐帧 deadline，也不能把总时长 helper 当逐帧增量的等价算法。示例 `Sani=1000,G=100` 的安装 rate 为 `100.00000762939453`，delay70 的 deadline 增量是69；刷新 rate100 则为70。这是固定输入算术证据，不是实际角色属性采样。正常候选只接受已界定的有限正速率、非负 decoded delay；原 native 零率替换规则在 helper 单测保留，未知负率/负 delay 不静默归一化。

## 3. 现有实际消费者与差异

代码位置基于本次只读身份；正在构建的 R60-02 只改渲染 profile，不代表下表缺口已补齐。

| 目标位置 | 现有实际行为 | 采纳/保留/待补 |
|---|---|---|
| `dnf-native-demo/src/simulation.cpp::FixedStepClock` | nanoseconds 乘60的整数累积；tick 毫秒为 `floor(tick*1000/60)`；不足8个等预算时 backlog 留存；序列化保留 debt。 | 保留。不能改成渲染 delta 驱动，不能每帧丢 tick。它是项目重建时基，不是60US原调度证明。 |
| `src/combat.cpp::World::advance` / `src/main.cpp` | 每 pop 一 tick 顺序执行输入/World、物件、ACT；UI 暂停不提交墙钟 dt；单步只执行一固定 tick，已有 debt 不丢。 | 保留。新 ANI clock 每实体每 tick 只写一次；presentation 读取，不反向推进。 |
| `src/resources.cpp::Animation::frameAt/samplePose` | 原 DELAY 总和查帧、循环 modulo、非循环末帧；R60-02 仅对给定时间做数值采样。frameOverride 把帧内时间设0并冻结 tween。 | 加接 runtime `frame/start/deadline/ended` 输入；源 DELAY/raw/properties 不改。不能用 frameOverride 代替正常时钟。 |
| `src/combat.cpp::simulateTick/attackFrames` | source-growth 普攻用 `basicLocalAge += delta*attackPerMille/1000`；技能用 `ms-stageStart` 和源 DELAY；`attackFrames` 设 `player.poseFrame`、发一次声音/生成附层并抽攻击盒。 | 当前有真实攻速消费者，但不是 native deadline。将普通攻击的当前帧/跨帧区间/结束迁到同一 cursor，去掉正常模式中用 poseFrame 冻结插值的做法；保留诊断冻结。 |
| `src/experimental_character.cpp` / `experimental_world_adapter.cpp` | 实验普攻自身 `age_` 乘有效攻速，hitStopped/blocked 时不增；输出 poseFrame，adapter 由 age 反写 animStart。声音/盒已有持帧去重。 | 需同一 cursor 接入；不要迁独立播放器的技能模板/配方。实验职业仍按原分类，不变成已完成原生职业。 |
| `src/renderer.cpp::player` / `src/character_attack.cpp` | 碰撞武器使用 body frame index；渲染各装备 ANI 接收相同 elapsed / poseFrame。非战斗 poseFrame=-1 时各层仍用自己的 DELAY，未建立复制后的 effective delay 视图。 | 建立身体根+装备子 binding，读同一 root clock；子层每索引 effective delay 覆盖最小帧数；不把子资源的 delay 永久覆盖。图层排序沿用现有装备身份/有效层。 |
| `src/combat.cpp::requestHitStop/advanceHitStop` | hitPause 按毫秒推断并 ceil 到 tick、上限500；移后 actor.animStart/stageStart、命中时间与 attached effect born/expires；世界/CD/输入继续。 | 保留已有具名推断；新 cursor 用 pause mask 得 delta0，不能再移后同一游标或重复补时。原生 hitPause 单位与双方拆分仍未知。 |
| `src/combat.cpp` 的 Effect / `src/renderer.cpp::effect` | `born/expires/animationOffset` 是独立 elapsed；attached 用玩家位置，玩家 hitstop 时移后 born/expires；所有 attached 默认挂玩家。到 expires 统一清除。 | 拆开位置跟随、时钟来源、速率继承、生命周期。已存在 source offset/parentId/EntityHandle 模式可复用，不能把 bool attached 升格为原生共享钟。 |
| `src/effect_plan.cpp::animationEffectPlan` | 预编译 `[add]/[remove]` 为源父帧 DELAY 求和后的 begin/end，子实例出生起钟且受父区间截断；其他 ALS 命令诊断。 | 普通静态预览继续；运行时改为游标跨父帧发 add/remove，按 source record order，只执行一次。add-time child clock 是具名推断，不是60US完整 ALS 证明。 |
| `src/act_runtime.cpp` / `act_service.cpp` / `act_world_host.cpp` | SourceMilliseconds / ExternalAnimationDelta 已互斥。World 绑定 external；hitStopped/stun/AI暂停供0，否则16/17ms×1000。事件按 animationUs，pending 按 elapsedMs；host 把 animationUs 反写 animStart。 | 复用互斥接口，保留 world age 与 animation age 分离。截止算术模式不能再乘 actor rate。外部 ACT age 若仍是 source-age，须显式桥接 frame cursor，不把百分deadline elapsed直接当未缩放ANI时间。 |
| `src/objects.cpp` / `src/monster_effects.cpp` | 物件 actionAgeUs 选择帧/碰撞/结束；怪物motion与死亡轨根据自己的 elapsed 和区间播放。 | 首批保持独立source钟，诊断标明。后续逐对象接同一接口；不因玩家hitstop冻结所有场景物件/尸体。 |
| `src/combat.cpp::idle/clearSceneTransients/restoreSimulationCheckpoint` | idle清attached效果/动作状态；换场清所有effect/pending/input/保护；普通checkpoint明确 `cancel-transient-actions-input-and-effect-instances-v1`，不续演动作。ACT typed continuation有另一套已验证导入门。 | 新clock属于动作/视觉实例，跟其owner一起取消。首批不把普通存档偷偷改成动作续演；若续演，必须另做同代graph、source hash、pending和owner重映射事务。 |
| `rep-player-1031-pvf/src/pvf_preview.cpp` / `pvf_preview_scene.cpp` | UI `time += wallDt*previewSpeed`，可scrub；各track `(time-birth)*animationRate`；ALS child继承rate，从add时开始；源delay决定end。 | 这是资源检查时钟。提供独立选择的deadline/60Hz审查模式，UI倍速只加速向固定时钟提交时间；播放速率不能和ANI rate共乘。scrub通过重建cursor求状态，不当原生连续录制。 |

现有自动测试源码已覆盖渲染30/60/120/144/240Hz的固定时间序列、backlog补tick、真实武器持帧接触/声音，以及 external ACT 在hitstop供0并恢复一次。这里**只审查测试实现，未重跑生产测试**；下一节点应复用并扩大这些测试，而非把它们列成R60-03新增通过。

## 4. 下一节点可实施接口

建议新增 `reverse-60us/integration/include/dnf_ani_clock.hpp`，只含 C++17 portable 算术/值类型，和现有 render header 分开。生产文件接入须由整合方另分写范围；本文不新增这个头文件。

1. `ClockPolicy {SourceDelay100, Inferred60UsPercentDeadlines}` 与 `RatePath {Installation, Refresh, ExplicitPercent}`。clock policy 和 render profile 独立；切换策略在新动作/重新加载场景边界生效，不能中途切成双时钟。
2. `AniClockState` 持有 owner `EntityHandle`/动作实例ID、source/policy身份、rootId、currentFrame、frameStartMs、nextDeadlineMs、rootElapsedMs、storedRate(float32)、ended、loop、loop/visit计数、lastSimulationTick。平台无关部分可用数值owner ID，完整来源绑定放宿主adapter。
3. `AniClockSnapshot` 为只读结果，包含 current/next frame、current visit、elapsed-in-frame、实际 deadline span、ended、loop；跨帧结果按稳定顺序交给声音/ALS/攻击帧消费者。R60-02 `SampleContext` 应使用此**运行时帧区间**，不能用缩放后elapsed却仍除原DELAY。图像、框、效果等离散字段照取当前来源帧。
4. 装备 binding 指向身体 root，具有自身 source clip + effective delays视图；同 motion 子层读取根elapsed/rate，保留自身图像/框。min之外的原子层帧/延时不抹掉；帧数不等时必须有明确轨迹测试和诊断，不能隐式越界或给层补图片。
5. 角色效果、ALS实例、独立物件各自显式声明 `clockBinding`、`rateBinding`、`positionBinding`、`endBehavior`。例：`IndependentElapsed + InheritActorRate + FollowActorPosition + HoldUntilDetach`。这是宿主适配字段，不是60US结构布局。仅已明确来源的scope可启用；未知 flag保持诊断。
6. 一固定tick内先确定输入/动作替换，再为活跃owner选一次delta/暂停mask，推进cursor并处理跨帧事件；渲染和碰撞都消费同一发布结果。现有World对象/ACT顺序不得无说明重排；新phase需避免动作首帧在bind与tick各发一次。

对 native frame advance：边界 `now == deadline` 前进；非循环最后帧到期只设ended；循环一帧需单独处理，不能无限while；零DELAY可跨多个帧但有预算且无声丢弃。全零时长/溢出/非有限率应明确拒绝。原生大步路径可跳到末帧/按总时长回绕，但其回调跳过语义未闭合：首批宿主继续“固定tick跨帧事件有序且每visit一次”的现有重建合同，记录这与完整native调度尚未等价。不要用优化偷偷丢声音/ALS/攻击事件。

## 5. 最小补丁分组与顺序

| 批次 | 最小实际文件范围 | 可审查结果 |
|---|---|---|
| 03A 算术/游标合同 | 新共享 `dnf_ani_clock.hpp`；独立 `integration/tests/clock-contract-test.cpp` 与 `integration/tools/verify_clock_contract.py` | 读固定46向量验证安装/刷新/逐帧deadline/改速；合成root/child/结束边界。此时不得标运行时完成。 |
| 03B 主程序普攻闭环 | `resources.hpp/cpp`、`combat.hpp/cpp`、`renderer.hpp/cpp`、`experimental_character.hpp/cpp`、`experimental_world_adapter.cpp`；`character_attack.cpp`视需要只改快照输入 | 普通/冲刺/跳跃攻击同一帧/区间驱动渲染、装备、盒、声音、连击；正常poseFrame不再冻结tween。新策略具名选择，旧策略可回归。 |
| 03C 暂停/附层/ACT桥接 | `effect_plan.hpp/cpp`、`act_service.cpp`、`act_world_host.cpp`；`act_runtime.hpp/cpp`仅在新增frame-cursor bridge确有必要时改；生产clock adapter可独立成文件 | hitstop只选0一次；位置/速率/时钟继承独立；ALS add/remove消费父frame visit；ACT只选一推进模式。03B若新增可继承附层，必须与此批共同交付，不留双计时。 |
| 03D 独立播放器可比较入口 | `pvf_animation.hpp/cpp`、`pvf_preview_scene.hpp/cpp`、`pvf_preview.cpp`和独立验证工具 | 同一clock header；source-delay与inferred-deadline可切；scrub/暂停/单步确定；不能导入旧技能模板到主程序。 |
| 03E 身份/恢复/交付 | 两工程CMake/构建及manifest工具、相关测试与渲染/移植文档；普通存档保持取消瞬态则不必扩schema | 新头文件进入依赖/hash/打包闭包；正常存档/旧候选保护；实际编译/候选步骤区分auto/user/native状态。若启用动作续演，必须另做storage/ACT同代恢复。 |

首次可交付节点至少包含03A+03B及所触及的03C暂停/清理路径，不能只交helper。完整R60-03还需附层/对象clock绑定和生命周期验收；03D可并行，但共享头冻结、入口与构建串行。当前R60-02整合期间不改上述生产输入。

## 6. 验证建议与退出门槛

| 验证 | 必须观察的实际结果 |
|---|---|
| 原算术fixture | 从immutable `native-ani-vectors.json`逐条读取46个native输出；rate float32位值、delay/percent截断结果精确；禁止用被测算法生成期望。覆盖两条rate路径及1000安装69/299边界。 |
| 帧边界/末帧/循环 | before/start/DEADLINE-1/DEADLINE/after；DELAY0前缀、全零拒绝、单帧循环、多帧循环、非循环ended保留；末帧角度插值与ended gate仍沿R60-02合同。 |
| 身体/武器 | 人造不同DELAY和不同帧数的body/child检测共享root及min覆盖；真实1031 CHR/EQU/LAY绑定逐帧比较渲染frame、碰撞frame、声音frame。不改raw bytes和全局缓存clip。 |
| 时间与补tick | 30/60/120/144/240渲染Hz、一次大墙钟dt分8 tick补完、暂停恢复、单步、速率中途刷新；同一模拟输入得到同一cursor/帧visit/命中去重/声音计数。 |
| 暂停矩阵 | UI暂停：不提交world dt；玩家hitstop：自身/声明跟随钟者delta0，独立弹丸/物件按策略继续；ACT AI暂停：external0但world elapsed与pending保持既有合同；stun/死亡：按既有取消策略，不能复活旧实例。 |
| 费用/事件/攻击 | 跨多个短帧不能漏声或重复spawn；持续帧接触仍允许新目标进入，既有攻击实例去重保留；clock策略切换不重付MP/CD、不重抽RNG，不重发历史帧事件。 |
| ALS/生命周期 | 同帧多条source顺序；同名add替换/remove一次；父动作中断/死亡/切角色/换图/脚本故障清理root和child；非循环ended和外层remove分开。 |
| ACT互斥 | source模式拒绝external delta；external模式拒绝缺delta；百分deadline时不再乘第二遍攻速。ACT frame event与presentation快照一致；取消不能清 unrelated hitstop。 |
| 恢复/身份 | 普通save继续取消瞬态且旧schema可读；任何续演需同代clock/source/pending/owner映射验证，坏source/owner/epoch先拒绝后不变更现场；保护旧存档与候选。 |

最终报告分别写：算术fixtures通过、实际main/player消费者通过、独立播放器通过、待用户画面/声音/手感测试、未做原版动态对照。用户步骤用隔离候选与独立存档：普通攻击→不同源攻速装备→hitstop→暂停/单步→ALS附层中断→切图/切角色→重载。未知真实timer通道、hitPause单位、完整技能clock/运动与特殊控制器仍保留，不将partial接入写成原生时钟全面恢复。
