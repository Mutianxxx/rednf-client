# R60-05 受击、死亡与场景破坏接入准备

本文件是 R60-05 的差异分析和实施方案，尚未实施 R60-05、构建或验证新候选。只新增本文件和 [机器清单](R60-05-REACTION-PLAN.json)；不修改生产代码、冻结 release、历史候选或存档。源代码与证据的 52 项 SHA256 快照在机器清单中，捕获于 2026-10-20 01:59:29（UTC+08）。实施前必须核对 R60-03、R60-04 整合后的实际文件，不能将此处行号或哈希冒充后续候选身份。

顺序为先完成 R60-03，再实施 R60-04，随后按本方案推进 R60-05。本次准备不计 R60-05 完成，也不增加已完成原生技能或职业数量。完整伤害公式仍属于后置 R60-06；已有统一属性、伤害、异常与奖励消费者继续使用。

## 1. 来源与版本边界

| 来源 | 固定身份 | 本方案允许的用途 |
|---|---|---|
| 60US EXE 静态证据 | `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b` | 已冻结的几何、接受命中、资源路由、死亡片段、场景控制器合同 |
| 60US PVF | `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98` | 所选桶、树、草及 PTL/ANI 的有序文本来源 |
| 1031 EXE | `246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264` | 已有独立几何、资格/Packet、物件构造片段与 PTL 位移合同 |
| 1031 PVF | `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d` | 当前 OBJ/MOB/ANI/ACT/ATK/PTL 的实际内容与成员身份 |

60US 使用 `reverse-60us/releases/20261020-01/analysis/`，保持冻结。1031 使用 `dnf-native-demo/reports/combat-native-reverse/` 中现有证据；本次没有重新运行逆向脚本或原客户端。表中哈希来自这些已存证据，本次未重新读取大型 EXE/PVF 计算包哈希。

1031 自身已经证实的几何/HP 端点保留自己的地址与证据。60US 的地址、虚表偏移、状态号、opcode、时间单位、文本 token 和工厂编号不能直接成为 1031 运行时常量。借用其可执行算法或控制流时登记 `cross_version_inference`、适用成员 hash 和具体未知条件，不设置 `native_controller_verified=true`。

## 2. 已有消费者与需要补齐的行为

| 主题 | 冻结证据与版本 | 当前真实消费者 | 实施缺口与处理 |
|---|---|---|---|
| XYZ 几何 | 1031 `876C00/1090040` 与 60US `4E9B10/A244E0` 分别成立；镜像为 `-x-width`；严格分离，边接触可命中 | `collision.hpp` 使用 XYZ、double、非零 extent、包含边界；可输出 overlap | 保留两版本来源；明确 double 旧策略与 60US f32 比较策略，不能悄悄改变全部碰撞 |
| 输入有效域 | 原检查拒绝零 extent；负数不在此前置检查统一归一化；NaN/Inf/控制字未知 | 当前安全检查拒绝非有限值，接受有限负 extent | 记录安全域与原生域差异；正尺寸作为新适配策略的明确域，负/非有限样本给诊断，保留原字节 |
| 主体与子 ANI | 两版本均有主体失败后检查 attacker child ANI 的局部证据 | 普通 strike 从传入攻击盒对怪物 base ANI 查询；效果有独立查询；物件用当前 type14 框 | 由 R60-04 的实际身体/武器/附层消费者枚举攻击候选，保留 child 来源和命中世界目标盒，不用渲染偏移代替 XYZ |
| 接触与接受 | 60US `4EDF70` 资格后走 opcode 0x13；1031 `87EB50/875DE0` 存在保护缺口 | strike/effect 各自先记历史再调用 damage；damage 有死活、探索能力、数值 miss/阻断和 Event.ai 预备 | 统一观察 trace：几何、资格、历史登记、miss、HP、反应、事件分开；保留策略原有登记时机，不能仅在 HP 成功后登记 |
| 历史重置 | 60US 安装 ATK（同指针或 null 也包括）重置两张历史表；ANI 换帧本身不重置；归属代理和移除清键另有链 | 身体 `hits_/hitCounts_`；效果 `hits/counts`；物件 `owner/serial/pulse` 各自管理 | R60-04 稳定 attack instance/安装事件后接入明确历史区间；模式2的1000原生计时单位未知，禁止变成所有技能1秒 |
| 怪物 ACT 资源路由 | 60US damage state 需要有效反应 ANI 后偏好 ACT；down ACT → down ANI → sit ANI | `selectMonsterAction` 有源 ACT 路由；`compileMonsterMotion` motion-first 提取视觉轨；damage 没有请求受击 ACT | 实际状态/行为与视觉编译共用选择结果；区分有效 ANI 门槛和 ACT 优先，补 down→sit；不能只改标签列表 |
| ACT 宿主能力 | 60US ACT 切换消费者不是仅提取 base ANI | `ActWorldHost::hasCommandConsumer` 仅支持 set_speed/teleport/set_direction/destroy/sound/cleanup_owned，speech 按配置；其他依赖编译可拒绝 | 所选受击 ACT 逐项列标签/行为、解析支持与宿主消费者；未支持时按版本策略给显式诊断，不静默把有行为 ACT 降为 ANI 后宣称完成 |
| 受击物理 | 60US state3/4 与 pending state 有证据，完整力/时长单位未恢复 | ATK push/lift/down/none 有消费者；重量缩放、350ms硬直、.93/.86阻尼、恢复钳制等为重建 | 保留源值，集中命名反应策略；地面/空中/倒地/坐起/抓取/保护分别 trace；不把现有校准写成原版公式 |
| 死亡与 last ACT | 60US Monster last ACT 已预载，实际执行未闭合；state5 冻结当前 ANI 并进入淡出/灰化片段 | `beginDeath` 将可编译 `[last action]` 当独立死亡路线；否则共享 palette/PTL 或 diagnostic fade | 明确旧路线为重建；新策略独立登记，不用 scene 的 last ACT 执行链补 Monster。保存所选策略，避免读档时改路由 |
| 死亡请求与实际移除 | 60US opcode 0x17 请求、pending 标记、接收与实际 deactivate 分开；死亡回调有保护跳转 | ActorLife Dying→DeathEffect→Removed，计时后设置；没有对应原生请求/移除全链证明 | 增加逻辑请求/确认/呈现退出的生命周期记录；离线模拟调度标推断。保留当前 once-only killed，不把视觉移除当再次击杀 |
| 通用物件破坏 | 60US ANI结束、z=0、严格 elapsed>limit、z=0但保留四种来源条件，来源有序生成列表 | `ObjectSystem::advance` 对 Reacting 统一恢复 basic；Destroying 动画结束后移除/Destroyed | 接通来源 destroy condition、创建动作和单次标记；条件3保持本体；超时记录 GetTickCount ms 与32位差值，不能套未知 Monster 计时 |
| 桶 221 | 60US specialized counter/HP reset/限次/偏移/PTL/音效；1031 仅实例向量若干消费者已核对 | 当前桶 durability=2，明确 local test；没有 specialized counter/HP reset | 新增 profile/成员闭包匹配的可执行推断控制器；保留 legacy 候选与旧存档，不从 int[5]=30 推 HP |
| 树 224 | 60US int=[1,2,0,0,0,100,1]；HP耗尽计数上限2，destroyflag0不移除；etcANI0不设恢复标记 | 当前仅 first etc motion 做受击；动画结束统一回 basic | 计数、HP reset、trigger equality、etcANI1恢复标记分开；不能每次命中都重播摇树或自动移除 |
| 草 244 | 60US first contact→etcANI0，second→request remove；PTL Z为绝对int0；左右是临近弯折 | 当前根据攻击方向选etcANI1/2，统一结束恢复；没有独立剪断计数 | 剪断与弯折拆开；先补可执行两次接受接触与 PTL；临近扫描资格完整性另列能力，不能当已原生恢复 |
| 场景 last ACT | 60US self removal 从保存路径构建临时 pooled ACT，继承XYZ/方向；普通tick至ANI结束 | OBJ actions 保留但没有这一完整消费者 | 单独的 scene 移除通知/临时实体消费者；与 Monster last ACT 严格分开，取消/失败清理与 pending 一次性通知必须实际验证 |
| PTL 与声音 | 60US scene已证实 creator→position→emit→submit，但分布/运动/渲染仍有缺口；1031仅局部 keep-last f32运动合同 | ObjectCatalog保存 particleReferences/sounds；Scene将呈现事件改名转发；main只处理 kind=sound。独立 particleStraightKeepLast 无生产调用 | 真实派发对象音效和 PTL 实例；接解析、生成、时钟、运动、画面、结束/退出清理；单函数/文件存在不算接入 |
| 攻击清理与持久化 | 原生移除通知清历史；用户要求重载不重抽/不重复奖励 | ObjectSystem::retireAttack 无生产调用点；Scene恢复只 retireOwnerAttacks(0)；payload tokens/pending 已持久 | 把 attack 生命周期结束接到清键，避免活跃房间无限积累；整代保存 controller counter、随机、pending与ack，保持旧字段/未知字段 |

## 3. 必须保留的已有合同

`beginDeath` 在 Alive 入口只发布一次 killed；`main.cpp` 使用 run token、房间与 target 构成键调用 `Progression::recordKill`。recordKill 先准备私有状态与随机流，再一次发布账本、掉落与随机；重复键拒绝。main 在奖励变化后同时 `session.remember(world)`、`persist()`。这些是工程重建的事务保证，不能写成60US原生奖励证明，也不能为恢复死亡表现而删除。

`saveActor/loadActor/restoreMonsterVisuals` 已保存死亡年龄、锚点、源动作身份、fragment初始条件；恢复表现不再 beginDeath、不重新消费随机。新增死亡策略和阶段需兼容这些版本，旧存档保留原来的已选路线。CharacterStore 使用提交代与不可变 pending 重试，模拟时钟/随机/世界/奖励继续进入同一候选。

物件保留完整 run/room/MAP记录身份、原字节偏移、actionAge、命中键、随机状态、payload token、pending事件及未知字段。恢复对象后清理 owner0 的瞬态攻击键是现有外层 World 已取消动作的约定，不得扩大成无条件清除持久 payload。现有通行宽高只用于移动障碍；不能再次拿它扩充原 ANI 伤害盒。

60Hz 固定模拟、R60-03 的时钟互斥和共享root合同继续有效。普通模拟不由渲染FPS决定。源毫秒、raw nativecount、相对微秒、tick、显示寿命分别表示；用户要求碎片最多700ms、末150ms淡出继续作为用户显示策略，不改源PTL寿命。

## 4. 所选1031物件的版本核对入口

已有1031 definitions.json 中以下内容与60US所选记录相符，但内容相同只能支持迁移推断，不能越过1031受保护loader证明完整消费者：

- barrel.obj ID221：int offset57，`[1,1,1,0,0,30,1]`；string offset102，`["","","Particle/BarrelDestroy.ptl","","WOOD_HIT","WOOD_CRASH"]`。
- actiontree2lorien.obj ID224：etc motion offset57只有一个本地源槽；int offset72，`[1,2,0,0,0,100,1]`；string offset117包含 damage PTL 和 TREE_SHAKE。不能为1031凭空创建缺失的etcANI1。
- smallgrasslorien.obj ID244：etc motion offset57有 destroy/left/right三个槽；int offset82，`[32,1]`；string offset102为GrassDestroy.ptl；pass all。

1031已有 native-int-data-consumers.md 明确：实例向量entry5→第三坐标偏移已核对，源 `[int data]` →实例向量复制仍跨保护边界；entry6写两字段的完整HP/生命周期含义未闭合。安全适配要求至少7个 MapObject 整数才能读取0..6；60US检查>=6却读取第7项的原生越界风险不在重建中仿真。不同ID/path/hash不得只因同名或相似数组自动套用。

## 5. 可串行交付的实施子项

| 子项 | 具体改动 | 完成所需实际消费者 |
|---|---|---|
| 05A 接触/接受/历史 | 接 R60-04 attack install/instance/ownership；独立 ContactResult、AcceptedHitTrace 与profile历史策略；保留 source ANI/框与 overlap/targetWorldBox | 普通输入身体、武器/子ANI、生成攻击及Scene物件都调用；记录阻断与miss，清理挂到动作退出/移除 |
| 05B 怪物反应 | 统一版本化 reaction resource selection，明确 ANI有效性门槛、ACT优先、down→sit；实际 ACT宿主与动作时钟接入 | damage→pending/boundary→反应动作/位移/声音→落地/坐起/恢复；死亡/抓取/霸体/无敌分开 |
| 05C 死亡 | 保存选中策略与生命周期；区分冻结身体、死亡效果、请求移除、实际移除；Monster lastACT保留推断边界 | normal kill、取消、读档/换房、旧死体恢复；只发布一次奖励事件 |
| 05D 桶/树/草与通用OBJ | 专用控制器登记在版本配置；counter/HP reset/animation restoreflag/剪断与弯折分开；接四类destroy condition、scene lastACT | 实际攻击、对象tick、通行障碍刷新、移除通知、临时ACT与保存恢复 |
| 05E PTL/声音 | 解析原来源与有序参数；真实creator/emit和拥有者生命周期，支持子集列能力；接现有f32 sampler实际调用 | 桶hit/destroy、树PTL、草绝对Z、ACT声音；故障清理、暂停/结束、切场/读档 |
| 05F 验证与节点备份 | 执行下表定向和既有回归，隔离候选/存档；清单闭合源码、EXE、报告、source profile | 正常按键路径与诊断路径各自报告；成功后在D盘新checkpoint保存源码与产物，并给用户步骤 |

05B需要改造当前 `prepareSourceActionBoundary` 对 recovery/stun 的一刀切延期：受击反应不是普通攻击AI请求，不能排队到硬直结束才执行。ACT bind会替换 Actor 存储，保持现有“先收集handle，发布时不持有Actor引用”的事务约束。反应、Event.ai反击、普通AI的先后顺序必须显式且可检查；AI暂停、动画暂停、hitstop不能被混成一个开关。

05D必须接统一数值链。当前 `objectDamageTarget` 仅允许唯一显式 `[hp max]`，Scene也只对显式HP走 `resolveObjectContact`，legacy桶仍按1 contact计数。选择constructor-derived maxHP的新策略需要可追溯输入并扩展该检查，不能只修改桶durability后绕开统一伤害或把grass剪断计数当HP。

05E不能以调用 `particleStraightKeepLast` 就宣称完整PTL。现有1031合同要求底层axis位置刷新descriptor原点、float32积分、投影/重力/限制分别处理；全局[100,29,100]仅磁盘值，运行时常量未证实。未知PTL生成分布/类型/轴模式应给具体资源与字段缺口。为beta实现可比较推断策略时必须完整可执行、可退出，不以空特效成功代替。

## 6. 需要新增或扩展的有意义检查

以下均为后续实施验收要求，本次没有执行这些新测试。优先扩展现有核心测试入口，必要时增加独立小合同检查；数量不是退出目标。

| 组 | 正反例与可观察结果 |
|---|---|
| A 几何数值 | XYZ每轴分离、边/角接触、零输入extent、零overlap输出、非零偏移及反向减width；比较double/f32边界样本；NaN/Inf/负域输出明确诊断而不改原数据；不以屏幕偏移参与判定 |
| B 实际查询 | 主体无攻击框、weapon/child有框可产生contact；错误slot/已移除child不接触；返回命中的世界targetBox与overlap不同；目标缺ANI不造默认大框；瞬时与已有X sweep策略分开 |
| C 接受/历史 | 几何接触但资格拒绝、source输入失败或miss时，分别确认历史与RNG合同；同ATK重新安装、null安装、仅换帧、owner共享/target代理、主动reset、场景移除分开；1000rawcount不推ms |
| D 反应ACT | 同时有ANI/ACT、仅ANI、缺基础反应ANI、坏ACT依赖、down缺失但sit存在、两者皆缺；实际宿主执行一个有源声音/移动的反应ACT，确认bodyclock和附层、动作结束/取消都清理；unsupported标签可见 |
| E 反应状态 | 站立受击、空中追加、倒地追击、坐起、无反应ATK、重量差异、抓取释放、无敌拒绝与霸体扣HP不打断分别检查；硬直计时与动画时钟互斥，AI反击事件每次接受最多一个 |
| F 死亡/事务 | 同tick多次beginDeath、fragment阶段读档、请求前后/确认前后移除、缺/坏lastACT、旧死亡快照；killed/XP/drop/随机next均不重复；存档失败后重试与重启只看到完整旧代或新代 |
| G 桶 | profile/source hash匹配才启用；显式HP耗尽→counter1→HPreset→PTL XYZ+offset→WOOD_CRASH→requestremove有序；同攻击重复框不重复；int不足/字段冲突诊断，未知payload保留 |
| H 树 | 第一次耗尽counter1启动etcANI0；第二次counter2、不超过limit；destroyflag0保留；etcANI0结束不由统一Reacting规则恢复；只有来源存在etcANI1的非计数分支设置恢复标记；局部1031缺槽不补 |
| I 草 | 第一接触剪断动画/输出，ANI结束本身不移除；第二接触请求移除；PTL高度用绝对int0，输入对象Z非0作反例；临近弯折与受击方向分离；直接contact路径不被臆造全局资格污染 |
| J 通用OBJ/通知 | 四类destroy条件、严格>超时与32位wrap、ordered spawn IDs、condition3保留；请求/实际退出/self/peer通知各一次；scene lastACT临时实体持原XYZ/方向，结束/故障取消均无悬挂 |
| K 实际PTL/声音 | 源particle path解析不唯一/缺失、未知模式、creator失败、子ANI透明/缺IMG、音效缺ID各给具体诊断；成功路径产生真实实例/drawcall/sound事件，ownercleanup取消；不重复ack丢事件 |
| L 时间/恢复 | 30/60/144/240渲染FPS与2秒卡顿补tick，逐tickcontact/反应/counter/PTL/randomtrace一致；AI暂停、hitstop、单步和切场各有预期；活跃房间攻击结束键回收有界；跨process相对年龄不漂移 |

既有 `test_objects.cpp` 的合法房间、682放置记录/相对时钟/交替攻击/持久payload基线继续回归；其170条历史报告属于当时输入和二进制，本次不重新声明通过。既有 `test_object_damage_world.cpp` 的真实explicit-HP drum统一伤害、miss及RNG反例、`test_monster_event_ai_world.cpp` 的接受事件和宿主事务、`monster_effects_tests.cpp` 的死亡恢复、`test_transaction_storage.cpp` 的各存储失败边界继续保留。只在变更影响处扩展，不能删旧断言换取绿色。

## 7. 用户体验与交付

候选需提供可复现的普通输入步骤：进入具有源桶/树/草的地图；分别普通攻击、带附层/生成物技能、空中/地面追击怪物；观察受击→倒地→恢复和死亡；保存、重载、返城后确认不重复掉落。诊断显示profile、动作/攻击/效果实例、source路径、accept/reject原因和推断策略，反馈导出保存这些身份。

自动结果、待用户画面/听音/手感测试、原版动态对照分别记录；本次没有用户体验或原版对照通过结论。PVP非文字UI渲染仍在最终范围，字体复刻只以用户指定【菜单】【商城】两处为目标，本节点不修改文字系统。

每个实际完成节点使用独立D盘候选与checkpoint，包含源码、EXE/依赖、编译日志、实际选定验证报告、源码/二进制/内容hash、进度和恢复入口。不得覆盖既有R60-02/R60-03历史、原客户端/参考项目和用户存档。本准备文档无需新编译产物，不新建假“完成节点”备份。

## 8. 明确保留的未知与退出判定

仍未知：1031接受命中保护段与全链、60US模式2计时单位/全部主动reset及ownership生产者、原生完整反应力/硬直公式、Monster lastACT执行和死亡保护回调可达性、完整PTL分布/限制/渲染、草临近扫描资格以及未覆盖场景子类。每项在候选清单绑定具体消费者和支持范围。可执行推断允许进入beta，未知处不能标占位成功或原生确认。

R60-05退出需要05A–05F的真实消费者、相关自动检查、普通输入入口、独立候选/节点备份和用户步骤齐全。只完成模型/解析/动画预览/测试fixture或本方案不满足退出；本节点也不代表十职业及全部主动/被动技能、世界业务或v0.1 beta总验收完成。
