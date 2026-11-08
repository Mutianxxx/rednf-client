# R60-03 主运行时独立审查与修复复核

审查日期：2026-10-20。范围是主 World、资源 clock/pose 适配、Renderer、装备攻击盒、动态 ALS，以及与实验角色的接口。初审及 R1–R3 复审为只读；R4 经整合者确认构建结束后，仅修改 `combat.cpp::advanceLocomotionPlayback`、`test_animation_clock.cpp` 和本文。其后按整合者授权，以独立小 harness 链接已编核心库诊断新回归的时间预算，没有重建或覆盖主程序／正在运行的 EXE，也没有启动原客户端。整合者首轮主程序构建、核心及音频检查已通过，记录保留于 `dnf-native-demo/reports/r60-03/first-pass`；R1–R3 修复后的第二轮检查也由整合者确认 exit0，日志是 `dnf-native-demo/reports/r60-03-build-final.log`。该轮通过不能覆盖随后新增的 R4 改动。

当前结论：**automated pass / user pending。R1/R2/R3/R4 均已修复并随正式完整回归通过。** [R60-03-VERIFICATION.json](R60-03-VERIFICATION.json) 已绑定主工程285份输入、84份报告、完整核心和音频30项、同EXE来源审计及 SDL dummy 局部 smoke。正式测试目录是 `dnf-native-demo/cache/r60-03-tests-final-r4-checked`，其 [clock报告](../../dnf-native-demo/cache/r60-03-tests-final-r4-checked/reports/animation-clock-tests.json) 为1541项通过，包含九个实验职业完整待机往返；结果与隔离诊断一致。Renderer 来源匹配和 animation-offset 永久回退也已确认。用户画面、听音、手感及原版动态比较仍待执行；自动检查不证明完整原生 timer、1031跨版本等价或全技能完成。

## R1：暂停期间的攻速变化会重投影根时钟（P1）

复审状态：**已修复，正式回归通过。** `advanceBasicPlayback` 的 Refresh 和 `basicSpeedStat_` 更新现均受 `!paused` 门控制；暂停 tick 仍连续消费 tick 身份但不重投影，恢复首 tick 才采用待变速率。新增真实 World 回归在暂停前保存快照、把攻速从1000改为1500并暂停3 tick，检查 elapsed/frame/rate 不变，恢复后检查 rate150。自动结果绑定最终1541项clock报告；下述保留原发现及当时建议。

位置：`dnf-native-demo/src/combat.cpp::World::advanceBasicPlayback`，审查版本约 600–611 行。

`paused` 仅传给最后的 `basicPlayback_.advance`；前面的有效攻速比较和 `setRate` 不受暂停门控制。`setRate` 会按比例重写 elapsed，并重新选择 frame/local/span。因此在 hitstop、stun 等暂停 tick 中更新装备/Buff/等级后，只要有效整数攻速改变，即便本 tick 给动画的 delta 是 0，已经发布的姿态仍可能改变。这与实验角色的 `!paused` 才刷新路径不一致。

建议：暂停期间保留旧 rate/stat；恢复后的首个有效 tick 再执行一次 Refresh，随后只推进一次该 tick。不要在暂停 tick 提前更新 `basicSpeedStat_`，否则恢复时无法识别待刷新的速率。

缺失回归：在暂停前保存 frame、elapsed、local、span、rateRevision，暂停过程中改变实际有效攻速；所有暂停快照保持上述值，恢复首 tick 才出现一次 rateRevision 增长且没有历史声音重发。现有 `test_animation_clock.cpp` 只测试速率不变时的暂停。

## R2：主普攻连击的新动作首帧事件晚一 tick（P1）

复审状态：**已修复，正式回归通过。** 连击安装新游标、重置 `lastAttackFrame_` 和命中账本后，当前 tick 直接执行 `attackFrames(-1,0)`，消费新动作 initial visits；该路径不额外 `advance`。新回归在真实源取消帧进入 attack2 的 tick 检查 `last_attack_frame == animationClock.frame`，已随最终1541项clock报告通过。零前缀与声音次数的完整边界由共享游标合同及实验侧测试补充，不外推为原游戏调度证明。

位置：`dnf-native-demo/src/combat.cpp::simulateTick` 普攻连击分支，审查版本约 2313–2339 行。

本 tick 先调用旧动作的 `attackFrames`，之后满足 `chainReady` 才切换新 ANI 并调用 `installBasicPlayback`。安装会立即发布新动作快照及 `basicFrameVisits_`，但该分支结束前没有再次消费新动作的初始帧访问。渲染已显示新动作的安装姿态，ANI 首帧声音和装备/身体盒要等下一 tick 的 `attackFrames` 才生效。若有 DELAY=0 前缀，前缀事件也一起延后。

这不要求修改 legacy 路径。新时钟路径应在安装的同 tick 消费新动作 initial visits，使用安装快照做盒采样，不再调用 `advance`，不再重复消费旧动作事件。实验角色已经在结束/连击边界这样处理。

缺失回归：观察发生 `basic_chain` 的那个 tick，检查新 ANI 安装帧和零延时前缀对应声音、攻击盒、动作身份都已发布；下一 tick 不重发安装事件。当前跨渲染帧率轨迹只比较同一实现自身输出，不能发现这类稳定的一 tick 延迟。

## R3：动态 ALS 子层继承旧轨迹起点后可能回跳（P2）

复审状态：**已修复，正式回归通过。** Add 时为非 attached 的有限轨迹子层设置 `trajectoryStartX=child.x`，从父轨迹扣除已行进毫秒；剩余时间为0时同时令 `speed=0`，避免进入不限时速度分支。新增真实 ALS 来源测试以 root born=-200、origin100、speed400、trajectoryMs280 触发 Add，检查子层出生起点连续、下一 tick 不回跳，以及后续不越过父轨迹终点212；已随最终1541项clock报告通过。

位置：`dnf-native-demo/src/combat.cpp::World::advanceEffectClocks` Add 分支，审查版本约 2134–2143 行；运动消费者约 2189–2192 行。

Add 通过 `Effect child = root` 复制根，然后把 `child.born` 改为当前时间并保留当前 `child.x`。对于 `!attached && trajectoryMs > 0` 的根，复制同时保留了根出生时的 `trajectoryStartX` 和原始 `trajectoryMs`。下个 tick，运动消费者按“旧起点 + speed × 子实例出生后时间”重算子层位置，导致刚在父实例当前位置出生的子层回到父实例旧起点附近。

例：根起点 100、速度 400、已运动 200 ms 时在 x=180 触发 Add。子层出生位置为180，但下一 tick 使用起点100和约17 ms年龄得到106.8，出现约73单位回跳。这是代码字段合同的静态结果，本文没有执行该数值场景，也尚未证明当前 PVF 的限时轨迹根一定有正帧 ALS Add。现有 GoreCross 路径会创建 `trajectoryMs` 根，动态 Add 是通用消费者，应明确处理该组合。

建议明确位置/运动绑定。如果采用从出生位置延续独立运动，应重置 `trajectoryStartX=child.x` 并处理父轨迹剩余时间；如跟随父实例位置，应使用独立的 parent position binding。旧 `expandEffectLayers` 已在正 begin 的轨迹子层上重设起点和剩余时间，但还需避免“剩余时间0”落入不限时速度分支继续移动。

缺失回归：私有测试实例使用非零出生年龄、有限轨迹和正帧 Add，检查出生位置与后续位置连续，并测试父轨迹已完成时子层不会重新开始运动。

## R4：实验职业返回同一待机动作时复用跳 tick 的旧游标（P1）

修复状态：**已修复，隔离消费者及正式完整回归通过。** 所有非 locomotion owner、非支持姿态和空 source 的提前返回，现均释放专用 `locomotionPlayback_`／source／start；没有清除 Actor 战斗快照。新增真实 World 回归逐个遍历九个已开放实验职业，交替使用 source-delay 与 inferred-deadline 政策：先自然待机3 tick，再发普通攻击，走到动作自然结束并回到相同 source、相同 `animStart=0` 的 waiting，检查该 tick 安装新根且 elapsed0，然后继续推进3 tick。攻击期间逐 tick 检查其来源匹配的战斗快照仍存在。测试不通过调用 idle/reset 绕开原触发条件，没有修改来源 ANI 或缓存。

首轮 R4 回归失败是新增测试将动作等待上限固定为240 tick（4秒），未覆盖源长尾。隔离诊断定位为 job2 `[gunner]`：实际状态名就是 `experimental_attack`，运行4000ms时仍在 attack1.ani 的第2帧，span9999ms、deadline10197ms、ended=false。男女神枪手的源 ANI 总时长均10200ms，不能因测试超时而截短。修正测试以实际攻击 ANI 的完整 DELAY 数组、实际安装 rate 和所选 policy 调用 `deadlineCycle`，按其截止时间换算 tick 预算，再给 ended／待机发布3 tick有限余量。保留全部原往返与快照断言，并输出逐职业源时长、政策时长及往返 tick。

隔离 harness 使用未变化的生产核心库，编译和运行均 exit0；完整 `runAnimationClockTests` 为1541项通过，九职业均自然结束后回到原 waiting 并继续推进3 tick。男神枪手 inferred deadline10197ms，女神枪手 source deadline10200ms。失败 JSON、前后编译／运行日志、修正测试源副本和逐职业结果位于 [R4诊断目录](../../dnf-native-demo/reports/r60-03/r4-diagnostic-20261020-015339-9817654/checked-manifest.json)。其后整合者正式重编测试，最终完整核心／音频通过；正式clock报告与隔离报告同为1541项，SHA256均为 `888ef569012f9746e2893216c440b171d136c39bc2bdd4f168714538671df455`。两种执行范围和原始失败证据分别保留。

位置：`dnf-native-demo/src/combat.cpp::World::advanceLocomotionPlayback` 约616–633行；`normalAttack` 实验分支约1064–1067行；`experimental_character.cpp` 约563–569行；`experimental_world_adapter.cpp` 约228–230行。

新移动时钟只在允许的 locomotion 状态推进。实验 runtime 正在攻击时，函数直接返回且保留 `locomotionPlayback_`。实验职业的普通攻击入口也只发送 request，不清理该专用时钟。实验 idle 输出的 `animationAgeMs` 等于绝对模拟毫秒，因此 adapter 每次都设置 `player.animStart=0`。

触发顺序：先待机至少一 tick 安装 waiting 游标；发出一次实验普通攻击，持续数 tick；动作结束后回到原 waiting source 和 `animStart=0`。原游标身份仍匹配，安装条件不会触发，而 `advance(tick)` 收到的 tick 大于其 lastTick+1，必然触发共享游标的 `ANI cursor requires one consecutive 60 Hz tick` 异常。这是源代码与游标前置条件的静态结果，本文没有另跑生产程序。

原建议是在 locomotion 不再拥有姿态时，清理专用 `locomotionPlayback_`／source／start，保留战斗 Actor 快照；也可在重入时检测 tick gap 并重新安装。不要调用会清理 Actor 战斗快照的 `clearBasicPlayback` 作为该 early-return 的替代。原九职业测试在初始化后立即 normalAttack，并在 runtime 首次不 attacking 时退出，没有覆盖旧 waiting 游标的往返；新增回归专门闭合这一遗漏。

## 已核对且未发现阻断的问题

- `AnimationPlayback` 的延时由 `shared_ptr<const vector<int32_t>>` 持有；Cursor 借用同一堆数组。复制运行时/Effect 后 state 独立，数组寿命由共享引用保持；安装先准备私有游标再发布。`Animation::followClock` 中的临时数组仅在同步无副作用投影调用期间借用，不逃出函数。
- 根/子动画的 min 解码 DELAY 覆盖保留原子动画多余帧与延时；碰撞的 `boxesAt(snapshot)` 与 Renderer 均调用 `followClock`。源 ANI/cached duration 没有被改写。短子层保留自己的 ended；长子层不凭空补图。
- `samplePose` 使用运行时 frame/local/span/ended，不再用已缩放 elapsed 除原始 DELAY；明确 frameOverride 仍冻结插值。
- 主普攻持帧样本继续检测进入范围的新目标，既有 action hit ledger 保留。帧索引单调门防止同一非循环动作重复发声音；跨帧样本携带对应根帧/区间供装备盒投影。
- ALS 在 append 前复制 root，append 后只使用副本；没有看到 `effects` 引用/iterator 跨 vector 重新分配后被使用。Add/Remove 按 visit、源事件顺序处理，同名替换递归截止旧后代；父过期/移除后的后代清理由最后清理循环闭合。
- `startStage`、`idle`、换场、死亡与普通 checkpoint 恢复经过根 clock 清理；实验 adapter 在死亡、blocked、预检拒绝时清理 Actor snapshot/source。普通存档仍取消瞬态动作，没有暗改成动作续演。
- 实验侧初始与跨帧声音按 visit 一次消费，暂停只推进 tick 身份；状态复制后没有自指针或存储回调，新测试覆盖复制/移动后原实例取消。

## 额外修复复审与有界限制

- **animation-offset 回退已修复。** 同实例第一次进入非零 offset 后锁定 `clockOffsetFallback=true`，清理 snapshot/playback 并只发一次诊断；以后即使 offset 归0也持续使用具名 legacy 路径，不尝试恢复跳 tick 的旧游标。新 ALS 子实例重置该 latch。
- **Renderer 来源匹配已修复。** 只有当前 `appearanceBodyMotion` 的 resource path 与 `animationClockSource` 规范化后相等，才加载 root 并把快照用于身体／子层；明确 poseFrame 仍冻结采样。碰撞侧已有对应来源匹配。
- 新 `advanceLocomotionPlayback` 为 stay/move/dash/jump/damage/down/sit 提供独立 source-rate100 根；stay/move/dash 循环，其余非循环。主普攻／skill 的安装及 idle 清理会清专用 locomotion 实例。主职业 hitstop 对 legacy animStart 的平移由身份补偿处理，新增待机暂停回归检查 elapsed 不变。实验职业所有权重入已按 R4 修复，并随最终1541项clock回归通过。
- 动态 ALS 的 add-time 独立 source-rate100 时钟、父外部寿命边界与暂停绑定均是具名宿主推断，不能当完整原生调度证明。当前 native 46 输出覆盖和1031跨版本推断分类仍应分别保留。
- 当前目标测试只在一处时刻检查三帧子层；应保留便携合同的短/长子层、末帧、零前缀边界，并扩大生产消费者测试到根 ended 后的长子层和短子层保持行为。

## 本次读取身份

下表是 R4 修复及测试预算纠正后，提交整合者最终完整回归的输入身份。生产文件没有因诊断而再次改动；测试文件新增来源期限预算和失败诊断／逐职业收据。隔离 harness 的1541项通过绑定该测试及已编核心库，完整主程序检查不能由此代替。

```text
dnf-native-demo/src/combat.cpp 0e26569175685f6d43cea0d28c8dc90f45dc9a3d743227b970ac58b0668feb90
dnf-native-demo/tests/test_animation_clock.cpp 5dc09a1691db9834e00c3af2840f466aad9d303063996dd47650fda3797fcede
dnf-native-demo/cache/r60-03-build/libdnf_core.a 7f6531ac4145a4b7ae110b4b6e8e6d865e3535d121f6547989004cc837bfb269
dnf-native-demo/reports/r60-03/r4-diagnostic-20261020-015339-9817654/checked-manifest.json 6a499842e173ce05b4b7a708dde9a55d742253646734ff0cc8032461ed9b1b06
dnf-native-demo/reports/r60-03/r4-diagnostic-20261020-015339-9817654/checked-run/clock-consumer-result.json 888ef569012f9746e2893216c440b171d136c39bc2bdd4f168714538671df455
```

首次 R4 回归仍有固定240 tick测试上限时的测试输入身份，保留作为失败记录：

```text
dnf-native-demo/tests/test_animation_clock.cpp 28056597f5e09d0fc41c7e413bdad4504b6312036a40e47b59d5853436e44da7
```

以下是 R1–R3 修复及新增 locomotion 复审时的变化文件身份，对应本报告中的 R4 发现。其余输入与后附初审列表一致。不能把后来源码改动算入已有通过清单。本文没有修改或刷新历史 release/package manifest。

```text
dnf-native-demo/include/dnf/combat.hpp 42a06b169402613b9e94f73b1d00239bda09b137ce6f3d35cb89e4d9b0260331
dnf-native-demo/src/combat.cpp 7fea526719afa03e37cdee1d06b442fa52db407290db8722755e185e860aa3e3
dnf-native-demo/src/renderer.cpp 5e1364f19564c87a212d7b9fb3f08618797a98619552ca3d8e25fc43e066f165
dnf-native-demo/tests/test_animation_clock.cpp fe4b73f177da840403228c686e0b8c8033ada87d0bfd2e2cc58dd45363e4a58d
```

以下 SHA256 保留初次发现 R1/R2/R3 时的源状态：

```text
dnf-native-demo/include/dnf/resources.hpp bbfd5aef70c8b836a8685ebfe1c2cedeba58b0c7575d8d7ff4641c7a06f73ada
dnf-native-demo/src/resources.cpp e52d817354514be7d8bf31e606c56b58ef53ce2d44d974e4b52aa634f5014978
dnf-native-demo/include/dnf/combat.hpp 9a3752d5cc8a68cea7145a9061fe64f7e517c67daabebcb76b071e680f8db459
dnf-native-demo/src/combat.cpp 1c172772e8f6edc7ed50a966a2d5705fe177ab54e8264eee9f7b44b6ae13591e
dnf-native-demo/include/dnf/renderer.hpp 6b518f4f53ac51cfce8edf62b3002688815a4134f6d272282d714c9fed903224
dnf-native-demo/src/renderer.cpp 947a6f3e222e8cf0c30f62578880793c579bb70be0c14981e6567c9226fb9eeb
dnf-native-demo/include/dnf/character_attack.hpp 49e6c5e942fde0d0ee17fb22fa939dda1ed6ea8297b04c71d47bab7ffff2d0d4
dnf-native-demo/src/character_attack.cpp 9946a88dc04cf4ca280d99ac36f05c70118df64ba6971170cd498eeb1996a41f
dnf-native-demo/include/dnf/effect_plan.hpp 8a9426d3cd58697cc03a35a488d8c4d2a394e98c85b63e45cf7a9c4b4d36471b
dnf-native-demo/src/effect_plan.cpp 078d39f35b9a129965402f164be7474995133f2ead292b4c44f28db10f30d956
dnf-native-demo/tests/test_animation_clock.cpp 2197525099fb452430d866ffb215fead3b4034eed5a9c4646c091dc9647e4cca
dnf-native-demo/include/dnf/experimental_character.hpp 795b780ff0d84087b581d52aebecffd53bc564a8a84e418a1c2a5f67a81d9772
dnf-native-demo/src/experimental_character.cpp 4ab44bc3db99a9f8672e2e0004cf5a560acc9a0ee28602e0f35fff3f1bee576e
dnf-native-demo/src/experimental_world_adapter.cpp dbcff9e45e86f3d173e82d9dded621da8ef00c3f0b2082d3f9c3420872d8493a
dnf-native-demo/tests/test_experimental_character.cpp d82b62de9b31794af04c3495d602060ff4c4c9cf783a916b5430daffe9bdae5a
reverse-60us/integration/include/dnf_ani_clock.hpp 93563eec417aac04e6511c155b40d8f143cfaa695bb7b0813a543504fb527b60
```
