# 04 十职业、技能、转职觉醒与脚本宿主

版本：v1.1；日期：2026-10-18；状态：**技术设计，待实施**。本章要求完整实现十职业及当前版本实际开放的技能，不代表已有源码已达到此门槛。Creator 仅延期运行时，全部来源仍保留。

## 1. 当前基线与范围

`CharacterCatalog` 已按 `character/character.lst`、`skill/skilllist.lst`、各 CHR/SKL/ETC/SD 建立来源。`CharacterIdentity(jobId,growtype,awakening)` 与 `SkillKey(jobId,skillId)` 已存在。现有可执行工厂仍只有基础鬼剑士；13 主动与6被动为局部实现。其余职业不允许借用该工厂。来源解析、执行实现、自动验证和用户试玩分别登记。

| jobId | 角色 | 当前注册技能行 |
|---:|---|---:|
| 0 | 男鬼剑士 | 175 |
| 1 | 女格斗家 | 163 |
| 2 | 男神枪手 | 167 |
| 3 | 女魔法师 | 207 |
| 4 | 男圣职者 | 195 |
| 5 | 女神枪手 | 167 |
| 6 | 暗夜使者 | 120 |
| 7 | 男格斗家 | 178 |
| 8 | 男魔法师 | 104 |
| 9 | 黑暗武士 | 201 |

十职业共1677注册行；包括系统／内部／共用／生活技能，不是1677个可施放技能。含 Creator 为1734行、1711独立SKL。全局249份未注册SKL保存但不因目录存在开放。分支名称、SKL fitness 与可玩分支不是同一事实；暗夜忍者／影武者、男法战法／魔道、黑暗武士复制名称等必须核对真实开放机制。

## 2. 注册、能力与证据接口

沿用现有 `CharacterControllerRegistry`，拆分以下维度：

```cpp
enum class RuntimeSupport { Unsupported, Partial, Complete };
enum class ValidationState { Untested, AutomatedPassed, UserVerified };
enum class EvidenceClass { Confirmed, Inferred, Unknown, UserTuning };
struct RuntimeCapability {
    CapabilityId id;
    RuntimeSupport implementation;
    std::vector<CapabilityId> dependencies;
    EvidenceRef evidence;
    std::vector<StrategyId> strategies;
    ReasonCode missingReason;
};
struct SkillRuntimeBinding {
    SkillKey key;
    ControllerKey controller;
    SkillSourceKind kind;
    std::vector<CapabilityId> requirements;
    std::vector<PassiveConsumerId> passiveConsumers;
    SourceRef bindingSource;
};
```

当前 `NativeChainClosed` 强制所有环节 confirmed，需保留为证据等级而不是唯一执行许可。增加 `ReconstructedBeta` 或等价状态：完整生命周期、清楚推理、通过逻辑测试的实现可以进入 beta；不能伪造 confirmed 记录。最终全技能交付不允许尚缺实际行为的 `Partial` 项混入“完成”，但可包含明确标注、可切换验证的完整推理实现。

`RuntimeSupport` 必须由工厂、依赖能力和实际消费者共同决定，不能通过文档标签开启功能。未支持工厂创建返回包含身份、源、缺失能力和诊断链的失败；不得生成空对象、回退鬼剑士或吞掉缺失资源。

按每个 `SkillKey` 记录：来源身份、玩家可学／内部／系统分类、分支资格、动作绑定、主动／被动消费者、依赖、实现状态、证据等级、测试状态及未决项。相同SKL路径跨职业仍保留不同局部身份。

## 3. 技能参数与学习事务

`SkillSourceData` 继续保存 common／dungeon／pvp 等作用域、重复项、未知项与偏移。模式显式空值与缺失不同；重复字段默认无隐式 winner。需要采用特定重复项时必须提供版本绑定的选择规则及依据，不能修改原解析数据。

参数分三层：`RawSkillFields → SelectedSourceParameters → EvaluatedSkillParameters`。等级表按源列宽精确读取，列语义由控制器或脚本消费者声明；不能把某列普遍命名为伤害。已知 modifier 顺序及 float32 边界保存，未恢复步骤交给策略模块。

学习接口：

```cpp
LearningQuote quoteLearn(CharacterState&, SkillKey, int targetLevel);
LearningResult commitLearn(const LearningQuote&, StateRevision expected);
SkillUseCheck checkUse(const SkillUseRequest&, const SkillUseContext&);
UseTransaction commitUse(const SkillUseRequest&, const SkillUseContext&);
```

学习条件完整包括职业／成长／觉醒、人物等级、起学等级与间隔、前置技能、购买上限、SP/TP或源规定资源、任务与特殊资格、技能是否已有执行消费者。`quote` 无副作用；提交重新检查状态版本，扣点与升级原子发生。重置技能同样是事务，按实际购买等级和成本历史返还；装备附加等级不计入退款。

`CharacterSkillState` 是等级和CD的唯一运行时账本；迁移旧存档／UI数组时取消双份权威。分别保存 `learnedLevel`、附加等级、有效等级、消费点数及来历。显式0级必须保持0，旧缺失字段只按明确旧schema迁移，不能每次加载自动赋1级。未知技能键保留但不执行；重复键或不明确身份拒绝整次恢复并输出诊断。

正常earnedSP/TP总额由正常等级／任务／源规则计算；当前尚无完整PC规则时使用独立版本策略，并记录服务端候选差异。不得硬编码每升一级固定赠点后称原版；正常学习禁止透支。调试设级只更新独立 `levelOverride`，测试学习使用独立测试点池及学习覆盖层，不修改正常earnedSP/TP和购买历史。关闭测试覆盖恢复正常权威等级／技能。有效等级下降后仍保留正常购买记录，但不满足当前等级门槛的技能标记 `TemporaryLevelIneligible` 并禁止使用；无CD不能绕过此门槛。测试覆盖、余额冲突和重置操作须明确显示，禁止静默丢技能或发负余额。

## 4. 施放、续段与被动

```text
requestSkill(key)
  读取真实身份、已学等级、源参数和实现依赖
  区分新施放与当前 actionId 的合法续段
  校验当前有效人物等级/状态/武器/目标/地空/MP/CD/道具条件
  创建无副作用动作草案、预备资源
  到提交相位再次校验
  原子提交必要消耗及动作状态
  按控制器声明的时点启动CD（入场/阶段/退出）
  响应动作、ATK、附层、生成、保护与续段事件
  自然结束或取消：注销本动作拥有的资源和修改器
```

被动必须绑定至少一个真实消费者：属性修饰、武器资格、动作替换、取消条件、触发行为、资源上限等。未绑定消费者的被动不能显示“已生效”。被动更新采用带来源ID的增删或全量重建，禁止重复学习／重载叠加多次。

特殊机制按可复用能力实现：蓄力、引导、抓取、召唤、自动追踪、地面场、持续弹药、切换姿态、变身、计数／连击资源、追加攻击、复活／恢复及队伍效果。单机队伍缺少其他队员时按目标规则处理，不把队友技能强改成攻击。职业原生差异允许独立控制器，但必须记录为何通用能力组合不足。

## 5. Squirrel 接入设计

事实：当前189份NUT，显式加载图可达145份，44份可能由appendage／原生回调等使用，不能删除。66次 `pushState` 中男法43、圣职者15、Creator8，另有104次 `pushPassiveObj`。现有工程未集成完整Squirrel VM。脚本宿主候选索引有5828调用点、446名称，并非已实现API清单。

推荐采用嵌入式Squirrel VM执行源NUT，**先完成兼容性探针再冻结版本**：语法、整数宽度、float、数组／table、闭包、弱引用、异常、标准库及回调约定。不能声称任意最新版天然兼容1031。PC可以执行VM；受限平台以后可以编译已支持脚本子集或离线产出等价行为，但必须共享语义测试，不能重新发明内容。

加载器按真实 `sqr/loadstate.nut` 的顺序与 `RunScript` 调用执行；脚本身份与PVF哈希绑定，注册得到状态／被动物件／appendage工厂。未从入口直接可达的脚本保留并依据真实回调入口加载。

宿主分层：

1. 注册与枚举：脚本加载、状态/对象/附加状态登记。
2. 实体与状态：稳定句柄、位置、方向、状态请求、变量。
3. 技能与属性：等级、参数、MP/CD资格与事务、最终属性。
4. 资源与动画：ANI/ATK/ALS绑定、局部时钟、事件、附层。
5. 战斗与对象：攻击登记、目标查询、被动物件、抓取、modifier。
6. 表现：声音、粒子、镜头等请求；绘制不直接回写战斗。

每个宿主API记录签名、接收者类型、单位、返回值、错误、副作用、证据与测试。脚本和原生控制器使用相同底层服务；`sq_IsUseSkill` 等可能含副作用，不能直接别名为纯检查。先在契约中明确检查与提交语义，再映射到事务服务。

缺失API不返回虚假的成功／0：能力审计报告脚本、函数、位置、依赖技能，并禁用依赖项。运行异常／执行预算超限时安全结束动作，清理拥有的资源并保留调用栈；不让单技能阻塞整个模拟。资源路径限制于当前内容配置，不能让脚本任意访问用户文件。

VM对象引用使用 `(entityId,generation)`，销毁后解引用显式失效。脚本保存采用已注册可序列化状态，不写VM堆／原指针；持续实体保存控制器类型、逻辑变量、相对时间及一次性事件记录。无安全恢复契约的活动脚本必须先实现恢复或在明确安全点保存，不能重载时从头重复执行奖励。

## 6. 十职业与转职实施顺序

下列为依赖驱动顺序，不缩减最终范围：

- **P08 男鬼剑士**：先迁移现有技能与普攻，清除World专用字段；完成四个实际分支及觉醒。现有十字、血十字与转职附加效果分别绑定资格。内含“来源→控制器→装备→学习→存档→测试”子任务。
- **P09 女格斗家＋男魔法师**：女格斗已有原生普攻／默认附层／退出证据；男法大量脚本用于验证另一执行路径。分别补抓取、念气／近身机制和法术／冰系持续对象、分支及觉醒。
- **P10 男女枪手**：共同建设弹丸、枪械子类型、连射、装填、重火器附层、机器人与弹药机制；分别消费男女动作、声音、参数和状态链，不因局部技能ID相同而合并身份。
- **P11 女魔法师＋圣职者**：召唤AI、目标筛选、地面场、变身、buff、图腾／姿态等通用能力；复仇者脚本接入同一宿主。实际分支／觉醒均闭合。
- **P12 暗夜使者＋男格斗家＋黑暗武士**：空中连段、抓取／投掷、资源计数及特殊连段编辑／冷却。黑暗武士独立控制器，不借鬼剑士分支资格。最后完成全职业系统项分类和矩阵收口。

每个职业开始时读取其真实 CHR/SD/NUT；ATFighter取消帧2/4/4、Thief4/3/3、ATMage脚本3/3/3等只适用其已证明消费者。不能将任何一套取消帧推广全职业。

转职／觉醒服务使用任务和来源资格，事务更新身份、解锁、属性、技能上限与动作绑定；失败原状态完整保留。名称存在不产生分支工厂。未明确分支依据服务能力与诊断保留为未开放，最终交付前必须解决实际开放分支，不得靠禁用规避范围。

## 7. 未决项与推荐

| 问题 | 推荐解法 |
|---|---|
| 原生链未全部恢复 | 允许有依据的完整重建控制器，证据与可执行状态分开；禁止空占位 |
| SKL端点／列意义 | 已证消费者优先；候选语义放RuleProfile，不在解析器猜名 |
| 仅存在预加载资源 | 只登记依赖，不据此推定释放时点／攻击效果 |
| 新PVF脚本调用未知API | 加载时诊断依赖并阻止受影响技能；保留其他可执行内容 |
| 当前技能类别不明确 | 源注册行保留，列入待分类；不能全部当玩家主动或全部隐藏 |
| 变身／切换装备期间动作更新 | 默认在安全状态提交新动作绑定，当前实例保有资源引用；特殊即时更新由控制器声明 |

## 8. 任务与正反验收

- **P06.1** 扩展能力／证据模型，解除confirmed-only执行门槛；生成真实逐技能依赖表。
- **P06.2** 来源参数访问、控制器／被动消费者接口和通用行为骨架；依赖P02/P03，向P05/P07提供接口，不等待完整战斗实现。
- **P06.3** VM兼容探针、宿主API清单、加载与工厂注册、异常和恢复契约；需要战斗的宿主调用通过服务接口在P07整合。
- **P06.4** 为P08..P12提供模板、回放与矩阵生成；逐职业实现，不按文件数量标完成。
- **P07-S** 统一学习／等级／SP/TP／快捷栏账本和迁移，接入被动消费者、施放与技能消费事务；依赖P05的属性／资源服务和P06的控制器／参数接口。P06不依赖本项完成，避免循环依赖。

正例：创建十职业、装备合法武器、技能学习／升级／快捷栏、基础动作、主动与被动、转职觉醒、死亡换房重载。每个可学技能验证完整行为，不能用抽样替代全部执行覆盖；原版动态对照由用户按候选包执行。

反例：错误职业局部ID、未学0级、MP/CD不足、错误地空状态、前置／分支不符、无被动消费者、缺脚本API、失效实体句柄、重复请求、旧续段、未实现工厂。均拒绝且不扣点／扣蓝／错误启动CD。

存档测试：零级、未知键、旧缺失字段、附加等级、旧快捷槽、重复键拒绝、CD相对时间、变身与持续脚本恢复、不同内容配置映射冲突。脚本测试必须涵盖实源回调和错误路径，不只验证VM可启动。

## 9. 证据入口

- [职业完整来源](../dnf-native-demo/reports/combat-native-reverse/all-characters/README.md)
- [现有控制器接口](../dnf-native-demo/include/dnf/character_controller.hpp)
- [现有技能读取接口](../dnf-native-demo/include/dnf/skill_data.hpp)
- [覆盖矩阵及身份边界](../dnf-native-demo/reports/combat-native-reverse/coverage/README.md)
- [女格斗证据](../dnf-native-demo/reports/combat-native-reverse/fighter-attack/README.md)
- [枪手证据](../dnf-native-demo/reports/combat-native-reverse/gunner-attack/)
- [技能参数消费者](../dnf-native-demo/reports/combat-native-reverse/skill-parameters/README.md)
- [宿主API导航](../dnf-result/research/pc-native-host-api.json)
- [服务端及安卓规则边界](../dnf-result/docs/12-server-and-revised-android.md)
- [用户技能交接包](../逆向部分结果参考/技能调用效果实现文档/dnf-skill-combat-handoff-v1/README.md)
