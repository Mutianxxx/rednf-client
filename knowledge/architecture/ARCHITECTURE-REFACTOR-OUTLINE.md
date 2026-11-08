# C++ 运行时架构拆分大纲

日期：2026-11-02（Asia/Shanghai）。状态：**架构提案；尚未执行运行代码拆分，未编译或发布新体验版。**

用户本轮要求：继续 C++，以已有实现和补充 PVF 资料为依据，先确定后续填充的模块框架；人物身体/装备/时装、动作技能、怪物显示/AI、地图、弹窗 UI 和 HUD 必须有明确边界，同时控制版本迭代中的卡顿。

## 1. 范围与基线

- 复用 `dnf-native-demo` 已有解析、动作、战斗、成长、业务和存档，不重新制造一套并行游戏实现。
- 当前正式源码与最新验证候选必须分开：`mage-upper457` 是已验证体验基线；equipment458/459 输入节点仍记录未解决的堆异常，不因本次规划称为已修复。
- Godot 体验暂停。当前只新增架构和核查记录，不移动源码、不改变存档格式、不重跑旧节点。
- 本大纲是本项目的工程设计建议，不把设计模式、目录划分或推理策略说成 PVF 原生事实。
- 原始客户端、知识库、历史候选、失败证据及用户存档保持只读或既有保护；构建/缓存/备份继续在 D 盘。

## 2. 总体结构

```text
app/                  启动、模块装配、游戏会话、输入路由、固定步调度
foundation/           强类型 ID、EntityHandle、时间、数学、错误与来源标识
content/              PVF/NPK/IMG 读取、无损来源、类型化定义、引用与能力索引
resources/            按需加载、预取、缓存预算、资源句柄、加载任务生命周期
simulation/
  actors/             角色运行状态、移动、跳跃、动作实例、动作时钟
  actions/            普攻/技能通用执行、阶段、输入窗口、持续/松键、中断
  jobs/               职业入口与动作/参数适配，提供源驱动描述和宿主扩展
  animation/          ANI/ALS 实例时序与事件、动作/装备轨道选择
  combat/             攻击实例、攻击框/受击框、命中账本、伤害与受击反应
  entities/           弹丸、PO、附加对象、纯视觉实例、破坏物生命周期
  monsters/           怪物状态与 AI 决策，调用公共动作/战斗/实体服务
  world/              区域、房间、门、障碍、出生点、副本运行与结算
  progression/        等级、属性、装备实例、技能学习与职业身份
  business/           NPC、商店、维修、背包、任务、交易命令
  scripting/          ACT/NUT 解释执行、宿主 API、预算、故障与恢复
presentation/
  animation/          从实例快照取帧/插值，生成显示姿态，不推进游戏状态
  characters/         身体、装备、时装和临时技能武器的显示组合
  monsters/           怪物身体/装备、受击/死亡姿态与装饰表现
  maps/               地图图块、远/中/近景、镜头、遮挡与地图物件显示
  effects/            实例特效、命中特效、粒子及混合显示
  ui/                 源 UI 树、布局/状态、命中测试、弹窗与 HUD
  audio/              消费声音事件、混音、语音、BGM 与缓存
render/               渲染命令、稳定排序、纹理资源、SDL 后端
persistence/          同代事务、保存/恢复、迁移、奖励账本与回滚
diagnostics/          性能采样、来源链追踪、有界事件/错误记录
tools/                导出、审计、测试场景、候选与检查点工具
```

这是目标逻辑结构，不要求第一步搬动所有文件，也不要求每项先创建空类或独立 DLL。先建立命名空间、职责和可测试接口；依赖稳定后再拆 CMake 库目标。

依赖方向：`app` 负责装配；`simulation` 读取内容/资源句柄，不依赖 SDL 或 UI；`presentation` 消费只读快照和类型化事件；`render` 只接绘制请求；`persistence` 通过明确的状态导出/恢复接口工作。UI 经应用命令请求业务，不能直接改 World。

## 3. 用户指定模块及其职责

### 3.1 人物渲染：身体、装备、时装

- `CharacterPresentation` 组合 `BodyLayer`、`EquipmentLayer`、`CostumeLayer`，保留来源图层顺序、遮盖/替换关系、方向和混合模式。
- `MotionResolver` 从当前 CHR、职业入口、装备/时装配置解析站立、行走、奔跑、跳跃、普攻与技能所需动作。
- 行走/跑步的动作加载与显示属于本模块；位移、奔跑触发、速度、碰撞属于 `actors/actions`，渲染器不能移动人物。
- 使用动作实例与各动画轨道的真实时序同步；不能要求身体、武器、时装全部套相同帧号。原始 ANI 毫秒不丢弃。
- 技能临时武器可复用装备图层组合器，但由动作/技能实体指定生命周期。装备提供的攻击框资格交战斗服务处理，显示模块不自行造成伤害。

### 3.2 弹窗 UI

- `UiDocument/UiLayoutEngine` 处理 `.ui` 父子组、相对坐标、锚点、裁剪、状态、九宫格和动画；`UiRenderer` 只显示解析结果。
- `InventoryWindow`、`ShopWindow`、`SkillLearningWindow` 各有自己的只读模型和交互控制器；任务、NPC 对话、角色选择、系统菜单后续沿用这一结构。
- UI 绘制和鼠标命中必须使用同一变换及其逆变换，避免原图、可点击区域与窗口缩放分别计算。
- 缺失/未知的源字段集中记录；明确的重建布局放在独立配置，不散落屏幕坐标补丁。
- 状态显示依据业务版本号增量更新；不因渲染一帧就重新解析 UI、重建物品表、重算全部学习资格。

### 3.3 职业动作与技能（包含普通攻击）

- 共用 `ActionRuntime/SkillRuntime`：输入接纳、动作阶段、MP/CD、取消窗口、连段、按住/松开、移动策略、效果创建与退出清理。
- `jobs/<职业>/` 提供本职业 CHR 动作入口、普通攻击段数/分段、武器姿态、源参数访问、state/PO 注册和确有差异的宿主扩展。
- **职业差异集中适配；动画、创建实体、计时、碰撞、伤害与受击不能按职业再复制一份。**
- 优先执行当前来源 ACT/NUT/定义可表达的行为；SKL 本身不是所有技能完整的时间轴。缺失 native caller 时，新增有证据分类的通用语义或职业策略，不铺开 `switch(skillId)` 补丁。
- “一个通用运行时”不等于“所有技能套同一动作”。技能应由数据/脚本组合公共能力。

### 3.4 怪物渲染

- `MonsterPresentation` 消费 MOB 动作状态、装备、受击/倒地/死亡姿态，复用公共动画/图层/绘制能力。
- 背篓等装备由当前 MOB/EQU/关联动作链解析，不按怪物名字补图。
- 多受击动作的随机选择由模拟层和可保存随机流决定；渲染不能每帧重新抽取。
- Boss 光环属于实体/特效显示，Boss 血条/头像属于 HUD；不混入 AI。

### 3.5 怪物 AI

- `MonsterAiRuntime` 读取 MOB/Event.ai/Action.ai/ACT 可支持部分，输出移动、攻击、召唤等类型化意图。
- 通过公共动作和战斗服务执行；不直接画特效、修改玩家血量或发放奖励。
- 接受命中、受击反应、死亡与中断由公共战斗状态处理，AI 可在合法回调中响应。
- 有源计时语义的动作/判定继续按原时序执行；只有经验证允许的高层寻路/目标选择才可分频，不能用降低全部 AI 更新频率换帧率。

### 3.6 常驻 HUD

- 独立 `HudPresenter/HudRenderer`：HP/MP、技能栏/CD、经验、怪物/Boss 血条、头像、副本小地图、提示。
- 与弹窗共享 UI 资源、字体、坐标和控件机制；不与弹窗混为一个巨大页面控制器。
- `HudReadModel` 是显示状态，不是第二份属性或技能账本；HUD 不执行伤害、扣蓝、学习和奖励。

### 3.7 地图渲染与世界运行

- `MapPresentation` 负责 TIL、背景层、前景、视差、门与物件的显示；`CameraSystem` 负责视口、场景边界和分辨率映射。
- `WorldRuntime` 负责可走区域、房间连接、地图切换、门状态、出生与副本生命周期；不可从贴图透明度推测可走区域。
- 120 像素等既有适配必须保留来源/版本与画布依据，集中到坐标策略；不能全局追加一个偏移修所有地图。
- 门的开关和破坏物受击/死亡是实例状态；显示其状态，不在渲染中反复触发状态切换。

## 4. 必须独立的公共模块

| 模块 | 负责 | 禁止承担 |
|---|---|---|
| 来源/内容定义 | 读取当前 PVF/NPK，保留原字节、顺序、未知字段、哈希与引用 | 把教程示例常量当成本地事实 |
| 资源服务 | 按需加载、预取、内存/GPU缓存、取消与失效 | 热路径同步解压/上传全部资源 |
| 动画时序 | 实例时钟、ANI/ALS有序事件、轨道与hitstop协调 | 因同一对象画两次而触发两次事件 |
| 战斗判定/受击 | AttackInfo、三维几何、命中去重、伤害/异常/击退/死亡 | 根据“看到特效”自动扣血 |
| 实体生命周期 | 弹丸/PO/视觉对象/破坏物创建、句柄、销毁与清理 | 裸指针跨房间或复用已销毁对象 |
| 成长/装备/学习 | 唯一正常账本、属性汇总、源资格、隔离测试覆盖 | UI和职业控制器各存一份等级/装备 |
| 业务/持久化 | 商店/NPC/任务/掉落事务，同代保存与恢复 | 用渲染/音效回调提交奖励 |
| 脚本宿主 | 有预算的ACT/NUT执行和类型化宿主API | 未知调用默认为成功或任意线程直接写World |
| 诊断/性能 | 采样、计数、可选trace、故障上下文 | 无限保存每帧JSON/完整世界历史 |

## 5. 关键执行链

```text
物理输入 → 逻辑命令 → 职业入口/资格 → ActionInstance
  → 动作阶段与动画轨道 → 帧事件/脚本 → 创建视觉或攻击实体
  → AttackInstance + AttackInfo + 几何/明确direct-hit
  → 目标过滤/去重/接受命中 → 伤害/异常/受击反应/死亡
  → 类型化显示/声音事件 → 人物/怪物/地图/特效/HUD显示
```

纯视觉层、ANI 攻击框、ATK payload、攻击归属和已接受命中分别建模。身体/武器存在攻击框不等于它们应当全部同时参与此次攻击。

```text
窗口输入 → UiController → 应用业务命令 → 准备/验证/提交事务
  → 正常账本变更 → ReadModel版本变更 → 相关窗口/HUD更新
```

固定 60 Hz 模拟保持原有算术合同；高/低渲染帧率只影响采样和插值。补 tick 必须遍历经过的帧事件，渲染不补发游戏事件。UI 装饰动画可使用独立 UI 时钟；不能借用 UI 时间推进战斗。

坐标必须区分 `EntityLocal`、`WorldXYZ`、`Camera/View`、`UiLocal`、`UiCanvas`、`Framebuffer`。来源偏移、IMG裁剪原点、镜像/缩放、局部附着和世界生成各有明确步骤，禁止统一脚底对齐或全职业共享一个补偿 Z 值。

## 6. 面向对象：封装、组合、接口与所有权

用户追加要求（2026-11-02）：整理源码必须充分考虑面向对象。这里的拆分以**对象责任和状态所有权**为准，目录和文件是实现结果。

### 6.1 核心对象

| 对象/接口（目标名称） | 持有或提供的内容 | 交互边界 |
|---|---|---|
| `GameApplication` | 平台入口、服务装配、主循环 | 只编排，不实现具体技能/商店/角色绘制 |
| `GameSession` | 本次运行的World、命令队列、随机流、提交代 | 唯一会话生命周期；可导出/恢复一致状态 |
| `EntityStore` | 实体实例及generation句柄 | 创建、查询、撤销，禁止跨房间保留悬空指针 |
| `PlayerCharacter` | 身份、ActorState、正常成长引用、动作/外观状态 | 方法维护角色不变量；不持SDL/UI对象 |
| `Monster` | ActorState、MOB定义句柄、AI/装备状态 | 复用公共动作/受击服务，独立AI决策 |
| `WorldObject` | 按需组合门、可破坏、碰撞、弹丸等状态 | 不为了可被攻击就伪装成Monster |
| `ActionRuntime` | 动作实例、阶段、时序、资源费用与清理 | 通过受限服务调用实体/战斗，不能任意写所有World成员 |
| `IJobActionAdapter` | 本职业源动作/参数/状态注册的适配接口 | 复用已有Controller Registry/Factory，按职业注入 |
| `CombatSystem` | 攻击实例、命中账本、伤害与反应发布 | 输入有攻击归属的请求；统一接受/拒绝结果 |
| `CharacterPresentation` | 身体/装备/时装的解析结果与显示组合 | 消费只读CharacterView，不写动作/属性/存档 |
| `MonsterPresentation` | 怪物各层显示与受击/死亡姿态组合 | 消费只读MonsterView，不决策AI或奖励 |
| `WindowManager` | 窗口实例、层级、焦点、模态及输入捕获 | 通过窗口接口管理，不了解每件装备/每个技能 |
| `IWindowPresenter` | 单个窗口的状态、读模型和输入到命令绑定 | 背包/商店/技能各自实现；共享UiLayout/控件 |
| `HudPresenter` | 常驻HUD读模型与局部失效 | 共享UI内核，独立于弹窗开关生命周期 |
| `ResourceManager` / `RenderDevice` | 资源准备/预算与设备绘制分别管理 | 资源句柄跨模块，SDL指针留在后端 |

这些名称表示职责，不要求无条件再包一层同名类。已有对象责任正确的保留并收窄接口；过大的类才逐步拆出服务。具体字段以迁移时的依赖/性能验证为准。

### 6.2 组合优先，继承用于可替换接口

```text
PlayerCharacter ─组合→ ActorState / ActionState / AppearanceState
Monster         ─组合→ ActorState / ActionState / AiState / AppearanceState

CharacterPresentation ─组合→ BodyLayer + EquipmentLayer + CostumeLayer
CharacterPresentation / MonsterPresentation ─复用→ AnimationSampler + LayerComposer

IJobActionAdapter ← 职业源入口适配器
IWindowPresenter ← Inventory / Shop / SkillLearning / Quest / Dialogue
RenderDevice ← SDL Render Backend
```

- 角色和怪物复用同一套移动/动作/攻击/受击能力，不通过“Monster继承Player”取得代码。
- 不建立`人物→职业→转职→武器→技能`的深层继承树。职业、转职、武器和动作采用身份数据与可组合策略。
- 共同的`ActorState`是实例数据，不要求创建一个包含全部角色/怪物特殊逻辑的万能`Actor`基类。
- 虚接口用于子系统/策略的替换；动画逐帧采样、碰撞盒遍历和RenderItem提交可使用具体类型/批量接口。面向对象不等于每个像素或帧事件都分配对象和虚调用。

### 6.3 封装和唯一写入者

- HP/MP、动作阶段、装备、技能账本、奖励和存档提交代不能继续由UI、渲染与任意辅助函数直接修改。
- 角色/实体对外提供只读View或句柄；改变状态通过所属对象/服务的明确方法或命令完成，验证失败不半提交。
- 不能把全部public成员机械改private再为每个字段补可写getter/setter。接口应表达业务行为，例如请求动作、提交学习、穿戴装备、接受命中。
- 不建立全局ServiceLocator/全局事件总线；由构造函数注入所需最小接口，避免把整份可写World传给所有模块。
- 单线程模拟阶段持有运行状态的唯一写入权。异步任务准备不可变结果，通过明确的加载代/提交点发布，不能绕过对象封装。

### 6.4 生命周期与内存

- `GameApplication`拥有设备/资源服务；`GameSession`拥有World与实体；窗口拥有自身交互状态，不拥有正常业务账本。
- 定义数据可共享为`shared_ptr<const Definition>`或内容句柄；运行实体以EntityHandle查找，不到处共享可写对象。
- 独占对象与SDL/文件资源使用RAII；销毁顺序明确：停止/回收异步任务，释放依赖资源，再关闭设备/会话。
- 保持连续存储与可复用缓冲，热点经测量后采用句柄池；不要给每个对象/组件无条件单独heap分配。
- 动作取消、死亡、离场、脚本异常和读档均执行同一生命周期清理合同，避免特效/霸体/抓取/回调遗留。

## 7. 设计模式使用位置

| 模式/方法 | 本项目用途 | 性能/复杂度约束 |
|---|---|---|
| 组合 | 身体/装备/时装/临时武器；动作能力组合 | 不建立人物→职业→每技能的深继承树 |
| Strategy + Registry | 职业适配、坐标/推理/版本策略 | 按入口选策略；不对每个像素/碰撞盒多层虚调用 |
| 状态机/数据化阶段 | 普攻/技能、怪物受击、门/物件状态 | 有实例、转移条件与退出清理，不复制巨型switch |
| Command | 输入、技能请求、UI业务、调试覆盖 | 有序、可记录、可重放；业务提交与战斗tick区分 |
| Factory + 句柄池 | 角色/怪物/PO/弹丸创建 | 保存generation，明确回收；先测量再池化热点 |
| Flyweight/不可变定义 | 多实例共享ANI/ATK/MOB/技能定义 | 只共享定义，不共享实例时钟/血量/随机流 |
| 类型化事件/Observer | 接受命中后的表现、音效、UI脏标记 | 限定阶段和生命周期，无全局隐式广播链 |
| Adapter/Repository/事务 | 来源解析、SDL后端、保存与业务边界 | 接口放在子系统边界，保留现有事务保证 |

优先采用已有 EntityHandle、模块服务和连续数据容器。暂不为了架构重做通用 ECS 引擎、插件系统或跨进程通信；有数据和性能证据后再局部调整。

## 8. 性能是验收项

以下是拟采用的工程约束，**不是本轮已测得的优化结果**：

1. 先记录同机、同资源、同职业、同副本/seed、同输入的基线；区分首次加载、预热后、战斗和UI开关。
2. 分别采样输入等待、模拟/脚本/AI/碰撞、资源读取/解码/上传、绘制/提交、文字布局与UI更新、保存。
3. 报告帧时间中位数/P95/P99、长卡顿、tick积压、内存/显存估算、纹理/实体/队列数量、缓存命中、每帧分配和磁盘I/O；不用平均FPS掩盖尖峰。
4. 渲染热路径不解析PVF、不解压NPK、不重建全目录索引、不做同步完整哈希，不重新构造所有装备/技能模型。资源首次未就绪通过可追踪准备阶段解决。
5. CPU读取/解码可在受限工作队列并行；保留当前文件访问线程安全边界。GPU上传/SDL操作集中设备所属线程，模拟和提交保持明确所有权。
6. 地图/纹理/动画/文字缓存分别设预算；按profile/版本失效，引用固定的活跃资源不能被淘汰。跨地图异步结果按加载代校验，避免旧结果污染新场景。
7. 使用可复用命令缓冲、容量预留、必要的空间索引和可见性裁剪；保留稳定的Y/层序/透明混合顺序，不能为了批处理破坏显示。
8. 只裁剪不影响游戏语义的绘制；不能因为离屏就跳过必须执行的AI、碰撞、计时、掉落或持久化事件。
9. UI按版本/脏区域更新，文字测量与布局缓存；日志/trace按级别、去重、限量，完整快照仅用于保存/诊断/验收。
10. 每个拆分节点对照基线。建议把可重复的P95帧时间退步超过5%作为调查/暂缓合并线；实际噪声、场景和预算测定后登记。任何新增长卡顿/持续内存增长也须解释，不能只看此阈值。

不同硬件未实测前，不承诺固定帧率或优化百分比。模拟60Hz不等于把绘制锁到60FPS；现有垂直同步/可调分辨率策略继续保留。

## 9. 迁移顺序与每节点交付

| 节点 | 内容 | 验收产物 |
|---|---|---|
| A0 | 锁定已验证基线和未验证delta，建立固定场景/输入与性能采样 | 基线清单、失败保留、性能表；不混用未解决堆异常节点 |
| A1 | 统一ID/坐标/内容定义/资源接口，资源按需加载边界 | 来源一致性、坐标组合、缓存/加载代验证 |
| A2 | 提取底层绘制和共享动画，再拆人物/怪物/地图/特效显示 | 同输入时序/绘制命令/事件比较；用户看实际画面 |
| A3 | 提取UI文档/坐标/命中测试，拆弹窗和HUD | 源布局与缩放/点击一致性、实际业务命令不变 |
| A4 | 将普攻/技能收敛到公共动作执行器，建立职业适配注册 | 已有职业动作/MP/CD/命中/清理不退步；不新增假技能 |
| A5 | 分离怪物AI、战斗判定、PO/破坏物与地图运行 | AI意图→动作→命中→反应；实体释放/切房恢复 |
| A6 | 收敛成长/业务/持久化接口和应用装配，形成构建依赖门 | 正常流程、事务恢复、性能对照、用户体验候选 |

不是等A4才发现战斗边界：A1即冻结公共接口，A2/A3只移动表现所有权，A4/A5再迁移实际执行器。每步先用适配器沿用旧实现，再小范围替换；保持唯一权威运行路径。

每节点保留源码、编译产物、验证报告、来源/推理说明、性能对照、迁移清单和`PROGRESS.md`。构建/运行/打包串行，备份使用独立目录和哈希，保护旧候选/原资料/用户存档。对受影响模块做必要检查，阶段结束再做集成；不把全部项目的反复全量构建当作日常编辑流程。

## 10. 后续填充规则

- 新内容先确定归属模块、SourceRef、依赖、生命周期、测试与性能代价；不继续把功能堆进main/World/Renderer。
- 运行时跨模块使用类型化ID/句柄/数据，JSON保留给来源原始记录、存档边界和诊断，不作为所有热路径的通用对象。
- 每项推理具有策略ID、版本/来源、依据、适用条件和可替换配置；明确记录未知项。通用执行器支持已说明的推理beta，但不得假报原生恢复。
- 检查是否已有通用能力再新增实现。重复的第二个职业/怪物/窗口案例，应先判断可否复用或补全同一公共能力。
- 以角色创建/恢复→穿戴→学习/释放→进图战斗→掉落/结算→返城/保存的实际链路衡量完成度；目录拆完或自动检查数量不等于游玩完成。

## 11. 来源与当前事实边界

所有 PVF 主题先依据用户指定的最高优先级 Workbench 3.1.1 知识包索引 `archive/dnf-知识库/PVF-Ai-Agent-Workbench-3.1.1/knowledge-pack/indexes/knowledge-index.json` 查找主题，再应用 `skills/KNOWLEDGE_POLICY.md` 与 `dnf-pvf-knowledge`、`dfo-pvf`、`dnf-pvf-reference` 的版本/证据边界。

Workbench 3.1.1 是 PVF 知识查找与流程选择的首要资料；`archive/dnf-知识库/pvf-utils-info/Resources/AgentKnowledge`、`Resources/OfficialAnnotationTranslation` 是补充参考。针对当前客户端的事实仍以已识别的1031字节和可执行消费者核对；这些资料未提供所有native caller、最终伤害公式或完整UI回调。

本轮只读源码统计：`main.cpp` 2300行，`combat.cpp` 3416行，`renderer.cpp` 819行，`experimental_character.cpp` 1872行。行数只是定位集中职责的线索，不是性能测量或质量评分。

### 11.1 补充资料对应的边界

以下相对路径前缀：`P = archive/dnf-知识库/pvf-utils-info/Resources`，`W = archive/dnf-知识库/PVF-Ai-Agent-Workbench-3.1.1/knowledge-pack`。

| 原文位置 | 对本架构的约束 |
|---|---|
| `P/OfficialAnnotationTranslation/charactersample.chr.txt:285–322` | 动作槽、普攻/特殊动作、ATK另表；解析动作入口与攻击信息分开 |
| `P/OfficialAnnotationTranslation/equipmentsample.equ.txt:127–141,264–268,320–328` | 装备/时装隐藏与图层替换，expand ani攻击框选择；外观/属性/判定分开 |
| `P/OfficialAnnotationTranslation/animation.ani.txt:23–33,58–88` | 图片/变换/延迟/裁剪；共享原始时间和坐标解释 |
| `P/OfficialAnnotationTranslation/sample.ani.als.txt:27–35` | add/remove按父动画帧事件，不按毫秒或绘制次数触发 |
| `P/OfficialAnnotationTranslation/passiveobjectsample.obj.txt:12–14,29–66,126–130` | 对象受击/销毁/动作/跟随；组合能力与生命周期独立 |
| `P/OfficialAnnotationTranslation/newmonstersample.mob.txt:221–281,305–340` | 动作、攻击、AI分别登记；MonsterAI不等同MonsterRenderer |
| `P/AgentKnowledge/dictionaries/client-ui-layout-pos-lay-fields.zh-CN.md:21–26,53–60,74–81` | UI相对/父子/状态/子UI；LAY动作模板不等同UI布局 |
| `P/OfficialAnnotationTranslation/uiactionsample.act.txt:19–21,31–34,81–85` | ALL CONTROLS有性能提示；CHECK/CALL FUNC仍需宿主ABI与业务消费者 |
| `W/dictionaries/nut-runtime-api-boundary-quick.zh-CN.md:11–22` | 注册/定义/参数/调用链共同决定可执行语义 |
| `W/encyclopedia/pvf-file-types/passiveobject-attackinfo-hitbox.zh-CN.md:26–66` | 视觉、攻击归属、几何、payload和接受命中独立 |

样例和社区注释的版本限制继续适用。ALS帧/毫秒、pushState第五参、getSitAni和setImageRate误注等已知冲突，按`skills/KNOWLEDGE_POLICY.md`及知识审计保留，不导入为1031事实。

### 11.2 现有实现迁移映射

| 当前实现 | 目标职责 |
|---|---|
| `character_controller.*`, `character_attack.*`, `skill_runtime.*`, `experimental_character.*`, `female_gunner_world.*` | ActionRuntime、职业适配注册、源行为执行；逐步消除重复执行链 |
| `appearance.*`, `equipment_motion.*`, `renderer.cpp:545` | AppearanceResolver/CharacterPresentation，保留装备与时装遮盖规则 |
| `monster_equipment.*`, `monster_effects.*`, `renderer.cpp:654` | MonsterPresentation，复用公共动画/图层 |
| `monster_action_ai.*`, `monster_event_ai*`, `monster_behavior.*` | MonsterAiRuntime/动作意图，保留现有解释器 |
| `business_ui_source/render.*`, `equipment_ui.*`, `skill_learning_ui.*`, `region_ui.*` | UiDocument/Layout、独立窗口Presenter/View |
| `hud.*`, `target_hud.*`, `boss_aura_ui.*` | 常驻HUD、目标状态；光环实例显示与血条分开 |
| `scene.*`, `scene_tiles.*`, `scene_camera.*`, `walk_geometry.*` | SceneDefinition/SceneRuntime/MapPresentation/Camera |
| `main.cpp`, `combat.hpp`, `renderer.hpp` | 应用装配、只读视图、受限服务、轻量绘制后端 |

可复用现有`CharacterControllerRegistry/Factory`（`character_controller.hpp:76–100`）；`appearance.hpp:12–61`已保留图层/来源偏移，不能为了重新分层丢失这些信息。`renderer.hpp:2–7`的高层依赖和`combat.hpp:531`起的公开可写集合，是后续收窄的边界。

### 11.3 必须先测量的性能候选

| 当前代码 | 候选成本 | 拟验证/改进方向 |
|---|---|---|
| `main.cpp:1714–1854` | 每帧draw闭包/值捕获，Effect拷贝与多次排序 | 复用RenderItem缓冲、轻量句柄、保持层序的稳定排序 |
| `scene.cpp:31–50`, `renderer.cpp:796` | 静态地图每次重建分组/排序 | 准备场景时编译静态显示顺序 |
| `renderer.cpp:204–230` | 绘制时cache miss同步解码/上传 | CPU预准备、设备线程上传预算和资源就绪边界 |
| `renderer.cpp:373–484` | 全字符串文字纹理缓存无明确淘汰 | 动态/静态文字分离、字节预算和失效策略 |
| `renderer.cpp:654–673` | 怪物首次状态显示时编译动作 | 房间依赖预准备与缺口诊断 |
| `combat.cpp:3089–3101` | 效果×怪物×判定框遍历 | 测量规模，空间索引过滤，保留源命中次序/去重 |
| `main.cpp:2174` | 所有帧时长期累积 | 有界统计/采样；完整原始trace只在诊断场景开启 |

上述是静态候选，尚未证明哪项造成用户当前卡顿，也未承诺重构本身提升多少FPS。
