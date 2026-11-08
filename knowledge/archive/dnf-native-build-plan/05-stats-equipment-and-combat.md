# 05 属性成长、装备与战斗结算

版本：v1.1；日期：2026-10-18；状态：**技术设计，待实施**。所有推荐公式均属于明确标注的 beta 候选，不是宣称已恢复原版；已证实当前来源消费者优先于本章重建默认。

## 1. 当前基线与目标

已有 `Progression` 支持经验、背包、买卖、装备、耐久、修理和消耗品，但 `ItemDefinition` 仍只有少量物攻／物防等字段及鬼剑士兼容分类。`World` 仍有演示HP/MP、固定武器伤害和不完整属性公式。MP/CD只消费首端点，武器攻速没有完整进入最终动画倍率。装备外观已按 CHR/default EQU→job作用域→LAY标签／重复序号／原槽→ANI 建立，不应重新以文件名猜测替换。

目标是一个可解释、可追溯、可版本切换的属性与战斗服务，供人物、怪物、召唤物及脚本共用；正常模式不依赖演示怪物65/240HP和固定伤害表。历史测试倍率与用户指定碎片期限保存在测试策略，不混入来源平衡。

## 2. 数据与接口

```cpp
struct StatValue { StatId id; NumericValue value; Unit unit; SourceRef source; };
struct Modifier {
    ModifierId id; OwnerHandle owner;
    StatId target; ModifierOperation operation;
    NumericValue operand;
    ModifierGroup group; int priority;
    ConditionRef condition; Lifetime lifetime;
    StackingRule stacking; SourceRef source;
};
struct AttributeSnapshot {
    uint64_t revision;
    CharacterIdentity identity; int level;
    StatMap base, derived;
    RuleProfileId rules;
    std::vector<StatTrace> traces;
};
struct ItemInstance {
    ItemInstanceId instance; int sourceItemId;
    int quantity, durability;
    ItemRolls rolls; UpgradeState upgrades;
    Json preservedUnknown;
};
```

不可变 `ItemDefinition` 完整保存 EQU/STK 定义、顺序字段、原字节与偏移；实例只保存随机品质、耐久、强化／增幅／附魔等会变数据。字段未明确时保存原形，不为凑齐界面编造属性。`CharacterState` 保存基础身份、等级、经验、装备实例引用、技能账本及持续效果；派生属性由服务重算，不把多份缓存当不同权威。

接口建议：

```cpp
BaseStats buildBaseStats(CharacterIdentity, int level, const ContentContext&);
ModifierSet collectModifiers(const CharacterState&, const CombatContext&);
AttributeSnapshot evaluateStats(const BaseStats&, const ModifierSet&, const RuleProfile&);
StatTrace explainStat(StatId, const AttributeSnapshot&);
EquipmentQuote quoteEquip(ItemInstanceId, EquipmentSlot, const CharacterState&);
EquipmentResult commitEquip(const EquipmentQuote&, uint64_t expectedRevision);
DamageResult resolveHit(const HitContext&, const AttributeSnapshot&, const AttributeSnapshot&);
```

属性至少包括：HP/MP及恢复、力量／智力／体力／精神、物理／魔法攻击、防御、源支持的独立攻击、命中／回避、暴击、元素强化／抗性、异常等级／抗性、攻击／施放／移动速度、跳跃、负重与负重状态。属性使用明确单位，CHR千分基准、ANI百分数、概率、毫秒、像素／秒不得混用。

## 3. 等级、成长、转职及SP/TP

CHR `[initial value]`、`[growtype N]`、分支内重复 `[awakening N]` 按作用域和ordinal保存。成长块编号与显示名称索引需独立映射，不能直接相等。经验阈值、等级上限、技能点来源均从当前配置读取；一次获得大量经验允许连续升级，每跨一级按同一事务产生事件。

默认成长候选：有逐级增量时，从初始值累计至目标等级；有完整等级表时精确查表。转职／觉醒调整按消费者定义的加算／替换／分支基线处理，不同时套两种。缺少明确取整证据时默认保留源float32计算中间值，在消费者需要整数时向零转换；若来源／服务端显示每级截断则逐级截断。两种模式作为有依据的候选保存，不任意混用。

```text
rebuildCharacter(reason, newLevel, newIdentity)
  old = 当前属性与HP/MP
  base = 按来源初始/等级/成长/觉醒生成
  modifiers = 装备 + 套装 + 已学被动 + 持续状态 + 测试覆盖
  derived = 按规则组和顺序计算，生成trace
  if life != Alive:
      hp = 0                       // 普通重算不得复活
      mp = clamp(oldMp, 0, newMaxMp)
  else if reason == NormalLevelUp:
      hp = clamp(newMaxHp - (oldMaxHp - oldHp), 0, newMaxHp)
      mp = clamp(newMaxMp - (oldMaxMp - oldMp), 0, newMaxMp)
  else if reason == DebugSetLevel:
      hp = clamp(oldHp, 0, newMaxHp)
      mp = clamp(oldMp, 0, newMaxMp)
  else:
      使用该变更原因的规则，默认夹紧当前值
  if reason == DebugSetLevel:
      仅更新levelOverride及独立测试点池；保留正常earnedSP/TP账本
  else if 正常等级或任务奖励变更:
      重算来源规定earnedSP/TP总额，保留正常消费记录并校验
  原子提交；发出一次属性变更事件
```

**正常升级默认保留已损失HP/MP；调试设级只夹紧当前值**，二者不能混同。正常升级回满／按比例保留可作为用户对照候选，默认不开启；死亡状态不会因属性重算自动复活。减上限导致HP为0时由明确生命规则处理，不能绕过死亡事件。

正常SP/TP分为earned总额、已消费、附加／返还记录。正常等级／任务奖励来源独立；重载不重复发点，正常学习不透支。调试设级通过独立 `levelOverride` 求有效等级，测试点池和学习覆盖层与正常账本隔离，不改正常earnedSP/TP或购买历史；关闭覆盖恢复正常权威状态。有效等级下降导致原已学技能不满足资格时保留购买记录，标记 `TemporaryLevelIneligible` 并禁止使用；无CD不能旁路此门。测试冲突保留并报告，用户可明确重置测试覆盖，不静默清正常技能或产生负数消费。角色正常转职、觉醒和洗点调用同一服务，任务完成与身份变更原子关联。

## 4. 装备属性、外观与强化

穿戴资格至少检查真实job/growtype/awakening、人物等级、装备槽、武器子类型、性别／职业外观作用域、源附加限制、互斥和重量。`swordman` 布尔及legacy武器0..3仅保留旧档迁移边界，不再定义新装备资格。

装备事务：校验库存与槽位→验证定义及资源能力→准备替换→同时更新穿戴与库存→重算属性／被动条件／套装→更新外观绑定→提交。失败保留原库存和穿戴；满背包换装、双手武器互斥等必须显式处理，不能先移除再失败丢物品。

套装由源集合／计数／条件解释，套装效果使用独立modifier来源，件数变化做差量注销／安装或确定性全量重建；不能重复换装累加。附魔、强化、增幅、锻造等只按当前源实际支持机制建模。基础攻击与品质端点、强化附加攻击、无视防御部分、附魔元素、装备等级与成长属性分别保留，不压成单一attackBonus。

强化等高级操作若本轮无完整交互来源，仍须正确读取已存在装备实例及其战斗效果；是否提供玩家强化服务应在能力清单列出。不能把“入口暂未做”误当作无需实现该属性的理由。算法不明时提供规则候选及风险标记；随机结果由事务随机流产生且保存，重载不能重抽。

耐久保存当前／最大值和磨损事件身份；攻击／受击磨损时点从来源解释。耐久归零影响资格、属性或外观必须单列策略，不能自行删除物品。维修报价绑定实例、旧耐久、规则版本、金币和状态revision，提交重算并原子扣金修复。服务端已知修理 `(grade+5)*base/10` 先整数除法再浮点，采用该候选时必须保留此顺序。

装备外观继续使用对应job的EQU/LAY。保留空槽、重复标签、隐藏层、变体和武器／身体层序；无外观的普通防具不能自动删除时装。身体、武器、附层各有时钟和碰撞职责；武器换装后安全边界更新，当前动作绑定是否即时变化由策略明确。`bodyOrder=1000` 为已有重建默认，应放到渲染兼容策略并等待原生层序证据。

## 5. MP、CD与攻速推荐策略

### 5.1 MP/CD端点

保留源两个端点及声明范围。只有 **N的语义明确**（该端点对应的源等级范围，而不是随意取购买上限或表长度）时启用线性候选：

```text
t = clamp((effectiveLevel - firstLevel) / (lastLevel - firstLevel), 0, 1)
base = low + (high - low) * t
若 firstLevel == lastLevel：用唯一端点并诊断冲突的另一端点
result = 来源指定的模式、武器物理/魔法MP或CD倍率、技能/装备modifier链(base)
最终按各消费者约定转换整数；未证时非负值向零转换，标注推理
```

源已证实直接等级表消费者时优先查表，不使用插值。N不明时不得猜最大级；首端点仅用于标注清楚的诊断fixture，不能算作最终完整技能参数实现。最终交付前须给出有依据、可解释并通过端点／中间等级检查的适配或公式；存在合理候选时允许用户切换比较。源单位到毫秒的转换仅做一次；保留转换前值。MP消耗默认在动作提交发生，CD时点由控制器声明，不能由 `[cool time]` 字段单独推断。

CHR武器技能信息含物理MP/CD与魔法MP/CD倍率，应用哪个分类由实际技能消费者决定；混合技能不得只按图标或名称归类。调试无CD仅绕过冷却资格门，正常CD仍按控制器时点启动并推进，关闭开关后使用剩余正常CD；清空CD是独立显式命令。无CD不绕过未学、当前等级、职业、地空和资源能力；锁MP与无消耗语义分开记录。

### 5.2 攻速

已知ANI rate=100为正常、CHR常见1000基准、局部 `n*g*.001` 路径及g静态初始化100；未证明最终n的全链。

推荐候选：基础类别速度→来源装备固定增量→同组加算倍率→不同已分类组倍率→技能/状态速度选择→换算ANI百分数。精确分组以源消费者为准；未知组采用明确规则配置，不统一将所有百分比相乘。攻击、施放、移动和投掷速度分别计算。普通攻击与施法动作分别选用其速度；纯视觉附层是否继承由源绑定声明。

若当前候选将最终千分值n转换为百分数，使用 `rate=n/10` 并记录g=100假设。不得把CHR850直接宣称最终85%。每个动画实例仅使用一种 `ClockMode`：已证实 `trunc(delay*100/rate)` 的消费者使用 `NativeIntegerFrameDelay`，有效delay保存在实例且年龄按普通时间推进；采用 `ScaledLocalAge` 的其他明确适配器保持源delay，仅缩放局部年龄。两者不可同时使用，不能双乘倍率，也不能认为截断后始终等价。倍率变化保留已消耗帧相位，按所选模式转换剩余时长／年龄并保持事件消费记录。零rate/非法值不用于除法，生成诊断并按已定义冻结或拒绝策略处理。不能一律对全部动作设置同一速度，也不能重写源帧时长。

## 6. 伤害、命中与响应

```cpp
struct HitContext {
    AttackInstanceId attack;
    uint64_t epoch, pulse;
    EntityHandle owner, target;
    SkillKey skill; int effectiveLevel;
    SourceRef attackInfo;
    ContactGeometry contact;
    DamageSnapshotPolicy snapshotPolicy;
    RandomStreamId random;
    RuleProfileId rules;
};
struct DamageResult {
    HitAcceptance acceptance;
    std::vector<CalculationStage> trace;
    int hpDamage, mpDamage;
    ReactionRequest reaction;
    std::vector<StatusRequest> statuses;
    bool lethal;
};
```

**pulse由攻击自己的时钟、发射阶段或epoch产生，绝不能每次接触产生新pulse**。命中登记键为 `(attackInstance, epoch, target)`，周期攻击再包含源规定pulse或目标间隔。`resetHitObjectList` 增加epoch并显式清理对应登记；其他攻击接触不能影响该登记。

结算阶段：

1. 阵营、目标种类、XYZ、死亡／不可选、抓取、保护等接触接受资格。
2. 去重／间隔；命中回避、暴击及概率效果使用独立随机流，顺序固定。
3. 选择伤害类型（物理／魔法、固定／百分比、独立／无视等），求技能与ATK参数、攻击者属性和快照。
4. 按候选合同执行主属性、武器、技能倍率、防御、等级、元素、暴击、减伤、附加伤害、转换及异常等阶段；每个阶段保留中间值和舍入。
5. 提交HP/MP变更及状态响应；伤害与硬直／浮空／击退／抓取／命中停顿分别决定。
6. 发出已接受命中、伤害、死亡和奖励事件；死亡奖励只从一次性生命状态转换产生。

上列第4项的排列是模块清单，**不是宣称原生最终顺序**。具体可执行顺序写入每个 `DamageRuleProfile`，默认优先当前PC已证实消费者；其余采用服务端完整候选并保留差异。不得随意拼接不同版本最方便的局部乘法。当前PVF `[damage fomula constant]` 有27值，服务端读26float，第27项保留为未解释，不能猜用途。

服务端候选应移植完整依赖数据流，而不只摘一行伤害函数。没有相符字段布局时先建立有类型适配视图和测试，拒绝按偏移盲读。现代版本公式、安卓精简公式或250属性分母不得默认为1031已证实值。

固定伤害与百分比伤害分别解释。快照时点优先按源调用者；未知时采用D10重建默认：技能有效等级在释放时固定，普通即时攻击在命中时读取双方属性，持续实体在生成时快照攻击方属性、命中时读取目标防御。已证实的动态读取或阶段快照覆盖默认，不能在同技能各段随意混合。召唤物继承属性／等级／技能增幅应显式列出，owner离场后按生命周期继续或退出。

## 7. 异常、保护、抓取及恢复

`StatusDefinition` 保存异常类型、等级、时长、叠加／刷新策略、周期、免疫条件、属性及行为影响；`StatusInstance` 保存施加者、来源攻击、剩余相对时间、下次tick、强度快照和随机状态。

至少实现当前内容真实依赖的中毒／出血／灼烧等持续伤害、眩晕／冰冻／睡眠／石化等控制、减速及属性变化、解除与恢复。具体支持项从源和能力依赖表决定，不能只画图标。异常概率、等级压制与抗性采用独立规则；来源没定义时不默认100%成功。重复施加可能独立叠层、取强、刷新或拒绝，按类型/源规则执行。

霸体仍扣HP但保持允许的动作；无敌按阶段拒绝对应接受命中／伤害；二者不能合并为god标志。死亡可终止霸体。抓取记录双方关系、命中／空放、锚点、位移约束、释放和不可抓目标。净化、角色死亡、换房、重载按各状态生命周期清理；buff不能因退出一个技能被全删。

恢复、药剂、吸血、反伤和复活都通过同一数值提交入口；治疗不得触发击杀奖励，反伤采用递归／事件链限制避免无限互反。消耗品CD与技能CD分组独立，使用物品扣数量、恢复和CD事务一致。生命为0不能因普通HP锁定或上限重算隐式复活，测试复活使用明确命令。

## 8. 未决策略表

| 未决内容 | 默认推荐与边界 | 可供用户比较的候选 |
|---|---|---|
| MP/CD端点 | N明确时线性，源查表优先；N未知首端点仅供诊断fixture，不算最终完整实现 | 来源支持的等级范围、阶段舍入差异 |
| 等级成长取整 | 保留源精度至消费者转换 | 每级截断与累计后截断 |
| 正常升级HP/MP | 保留已损失绝对值 | 回满、按比例；默认禁用 |
| 调试设级HP/MP | 夹紧当前值 | 另设明确回满按钮，不改变设级语义 |
| 攻速组合 | 已知分组顺序；未知版本化重建 | 同组加算与已证明独立组乘算 |
| 完整伤害 | 当前PC局部证据＋有类型的完整服务端候选 | 整套规则选择，不混搭不明阶段 |
| 快照时点 | 技能等级释放固定；即时攻击命中读属性；持续实体生成快照攻击方、目标命中实时 | 源指定动态读取／阶段快照 |
| 耐久归零／强化效果 | 来源可解释部分执行，未知显式诊断 | 有依据的版本候选 |

所有策略保存ID、版本、依据、影响和生效边界。会改变实体初始化／随机／伤害含义的切换在新副本生效；当前运行只显示待应用。测试报告必须列实际策略，不靠用户回忆。

## 9. 实施任务

- **P05.1** 解析CHR成长／属性与装备完整数值来源；建立单位和modifier分类。
- **P05.2** 属性重算、解释trace、升级／转职／SP/TP资源账本，接入正常与调试两条设级语义。
- **P05.3** ItemInstance、资格、套装、耐久、强化等数据与效果，迁移legacy字段。
- **P05.4** 身体／武器／时装外观和动画时钟整合；换装同时更新属性与表现。
- **P05.5** MP/CD／攻速策略、配置冻结与测试窗口解释接口；实际技能消费由P07整合。
- **P07.1** AttackInstance／epoch／pulse／目标登记，统一近战、弹丸、持续场和物件受击入口。
- **P07.2** HitContext／DamageResult、完整候选公式与精度边界、HP事务。
- **P07.3** 状态异常、抓取、霸体／无敌、恢复／反伤和一次性死亡事件。
- **P07.4** 原生局部差分、服务端候选差分、属性及战斗回放，提供用户比较方案。

P05依赖P02来源和P04事务基础，建立属性／装备／资源接口；P06依赖P02/P03建立行为／脚本／参数接口。P07依赖P05/P06整合命中、伤害与P07-S学习／施放事务；不能倒置为P06依赖完整P07。它们完成后支撑P08..P12全职业，不允许每职业复制一套属性公式。

## 10. 正反验收

正例：十职业多个等级、转职／觉醒前后，装备／卸装／套装变更、学习被动和buff到期能产生可解释属性；升级保留已损失HP/MP，调试设级夹紧值；换武器同时改变合法攻击速度、伤害和外观；固定／百分比／元素／暴击／异常各有真实效果。

反例：满背包失败不丢装备、跨职业不可穿、零耐久不重复磨损、同modifier不重复叠加、异常控制清理不遗留、无敌不扣血／霸体仍扣血、同攻击重复接触不重复伤害、两个持续攻击交替接触不互相清去重、死亡奖励不重发、源字段歧义不静默取首值。

边界：level0/1/上限、端点范围N=1或未知、负／非有限数值、概率0和100%、零CD／零消耗、MP恰等成本、逐级与批量升级、不同取整点、快照后换装、owner销毁、回避是否消费登记、反伤链、DOT致死、保存重载后的异常剩余时间／奖励。

测试证据区分：源字段保真、纯公式差分、整合行为、用户试玩。服务端模型与其C++一致不等于当前PC原版一致；静态成功不等于伤害平衡已经验收。

## 11. 来源

- [Progression接口](../dnf-native-demo/include/dnf/progression.hpp)
- [外观接口](../dnf-native-demo/include/dnf/appearance.hpp)
- [技能参数](../dnf-native-demo/reports/combat-native-reverse/skill-parameters/README.md)
- [攻速证据及单位](../dnf-native-demo/reports/combat-native-reverse/attack-speed/README.md)
- [职业／装备来源说明](../dnf-native-demo/reports/combat-native-reverse/all-characters/README.md)
- [碰撞证据](../dnf-native-demo/reports/combat-native-reverse/collision/README.md)
- [服务端及安卓版本边界](../dnf-result/docs/12-server-and-revised-android.md)
- [规则及来源索引](../dnf-result/research/server-rule-findings.json)
- [服务端行为合同](../dnf-result/research/server-behavior-contracts.json)
- [伤害常量候选映射](../dnf-result/research/server-PC-damage-constant-candidates.json)
- [已有源规则模型](../dnf-result/tools/server_rule_models.py)
