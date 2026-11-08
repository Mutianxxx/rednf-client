# 07 怪物、物件、粒子与世界实体

版本：v1.1；日期：2026-10-18；状态：设计待实施。

## 1. 可复用代码与证据边界

[objects.hpp](../dnf-native-demo/include/dnf/objects.hpp) 已有 `ObjectDefinition/ObjectInstance/ObjectSystem`、稳定身份、独立时钟、攻击去重、pending事件和保存恢复；继续补齐，不重新另造物件系统。[scene.cpp](../dnf-native-demo/src/scene.cpp) 对drop/spawn/trap/payload尚没有完整消费。[objects.cpp](../dnf-native-demo/src/objects.cpp) 木桶等行为仍是明确标记的候选。

[combat.cpp](../dnf-native-demo/src/combat.cpp) 怪物AI目前按`thrower`、`/tau/`路径分支，投石资源和HP仍含demo假设。[monster_effects.hpp](../dnf-native-demo/include/dnf/monster_effects.hpp)、[session.cpp](../dnf-native-demo/src/session.cpp) 已有受击/死亡和死亡中间态恢复。

[怪物交接包](../逆向部分结果参考/1031怪物受击死亡效果实现文档/dnf1031-monster-effects/README.md) 包含2070个MOB绑定，但其PVF `ca756b…`与当前`d13ce…`不同。必须重读当前MOB、核对引用和hash后复用机制，不能直接信任全量目录映射。包中静态状态数量不等于全部怪物AI/ACT可执行，也不代表逐一视觉验收。

## 2. 实体和行为执行契约

```cpp
struct EntityHandle { uint64_t id; uint32_t generation; };
struct BehaviorState { ProgramId program; uint32_t pc; SimTime age; LocalVariables locals; };
struct EntityInstance {
  EntityHandle self, owner, target;
  SourceRef definition; Transform transform; AttributeState attributes;
  BehaviorState behavior; ActionInstance action; RandomStream random;
};
SpawnResult spawnEntity(const SpawnRequest&, WorldCommandBuffer&);
void advanceBehavior(EntityInstance&, SimDelta, const WorldView&, WorldCommandBuffer&);
```

不可变定义与实例分离。定义保留MOB/OBJ有序字段、原始字节、条件、动作、ATK列表、AI与脚本引用。实例保存owner/target、属性、程序计数器、局部时钟、动作阶段、命中登记、RNG和待执行事件。生成/移除通过命令缓冲在确定tick阶段提交，遍历中不直接改容器。

ACT通用执行器逐类实现条件、跳转、等待、动作/ATK切换、位移、属性修改、声音、附层、粒子、实体生成与销毁。每个opcode记录支持、参数单位、失败策略和证据；未知执行指令阻断相关行为，未知纯元数据只保留。NUT或原生宿主调用需能力登记；不能把资源预加载表当行为执行列表。

未明确AI默认推荐“源动作集合＋来源距离/概率/冷却＋通用追踪/选招”策略，命名`inferred-source-ai-v1`。数据缺失时的距离/冷却默认值必须位于版本策略中可查看，不按怪物名分支。复杂首领缺失必要阶段时明确阻止相关内容，不能改普通怪后宣称完整。

## 3. 怪物出生、战斗与死亡

MAP出生记录保留autoLevel、原等级、冠军属性、指定/随机掉落、死亡NPC及未知扩展。属性经统一成长/装备/难度管线计算；正常模式移除65/240HP基数，测试倍率作为实例初始化覆盖且随run冻结。

受击先判接触与资格，再按ATK决定伤害、硬直、浮空、倒地、抓取、霸体/无敌和受击动作。保护状态有来源与有效期，不能将霸体当无敌。攻击instance/pulse命中表独立于动画图层，同攻击身体与武器不意外双击；明确重置事件开启新命中段。

MOB状态绑定按源字段优先级编译；明确但错误的高优先入口应报告错误，不能偷偷跳到低优先入口掩盖。独立死亡使用明确`[last action]`，不因文件名含die而绑定。通用死亡保存冻结姿态、白轮廓、碎片、烟雾与移除各阶段。

```text
acceptDamage(hit):
  校验attack登记、目标生命状态与保护
  在world候选状态应用伤害和反应
  若首次Alive→Dead：emit DeathAccepted(stableEventId)
  奖励处理和死亡视觉分别订阅，不由尸体移除触发奖励
  与本批世界状态、随机状态、pending奖励同代提交
```

碎片700ms上限/末150ms渐隐是历史用户指定测试调整，应作为独立可见策略保留，不能当源PTL公式。死亡中换房/重载恢复相对时间、源姿态和随机状态，不重新随机碎片或再次奖励。

## 4. 物件受击与生命周期

复用 `ObjectIdentity(run, room, map, fieldOffset, recordOrdinal)`，禁止以坐标+OBJ ID代替；相同放置可以重复。`ObjectDefinition`保留通行、ANI受击框、动作/PTL/声音、旧intData和special payload；第六整数在消费者确认前仍叫原始intData，不命名HP。

`ObjectBehaviorRegistry`按源工厂/语义类型提供反应、耐久、破坏、碰撞释放和移除策略。确需单对象适配时绑定资源hash并说明原因。树/柱摇动、草左右反应、木桶碎片、箱子开启通过类型化行为执行。源超长保持帧原样保留，由行为生命周期退出，禁止裁短ANI伪装解决。

通行footprint与ANI XYZ受击框分开。未知Z阻挡默认仅约束贴地移动，记录空中跨越未证实；已知Z才参加高度重叠。每实例命中登记使用 `(owner, serial, pulse)`；攻击结束才retire该攻击，两个持续攻击交替不会互相清表。

状态建议沿用 `Intact→Reacting→Intact`、`Intact/Reacting→Destroying→Destroyed/Removed`；碰撞释放点是行为参数，分别覆盖破坏开始/动作事件/结束，不统一立即消失。

## 5. PTL、声音与payload

新增/补齐 `ParticleDefinition/ParticleEmitter/ParticleInstance/ParticleSystem`，采用统一仿真时钟推进发射周期、持续生成、位置/方向、速度/加速度、颜色alpha、缩放旋转、生命周期和子生成。保留原单位及已证实float32计算边界；现有 [particle_motion.hpp](../dnf-native-demo/include/dnf/particle_motion.hpp) 仅算术子集，接入前需闭合owner修饰与实际消费者。

每个发射器保存RNG、累计时间、下一发射序号和已存活粒子；环境光采用PTL时钟和渐变，不图片闪烁。视觉预算可以减少呈现，但不能删除伤害弹丸或改变游戏随机流。战斗弹丸与纯装饰粒子必须明确分类。

对象事件路由使用 `DropRequested/TrapTriggered/EntitySpawnRequested/SoundRequested`。奖励交 [08](08-npc-quests-economy-and-services.md)，声音交音频总线；不得调用怪物击杀接口伪造物件奖励。

```text
dispatch(event):
  若ledger已有event.id：返回保存的结果
  在候选事务解释已支持payload并生成奖励/实体请求
  同时写入消费记录、结果、RNG、pending变化和世界快照
  持久化成功后ack并发布外部表现
  失败保留同一候选事件和roll，重试不重新抽奖
```

声音已发出而提交失败等外部效果不能保证物理意义恰好一次：持久化游戏结果优先，恢复时只重放未提交游戏事件，不重播历史已过的音效。与奖励“恰好一次提交”分别描述。

## 6. P13/P14子任务、依赖与验收

- **P13-E1**：将P03实体句柄和P06工厂/ACT执行器接入AI能力表；依赖P02来源、P06行为、P07战斗。
- **P13-E2**：MOB属性/出生/AI与死亡；依赖P13-E1、P05属性管线、P13-W地图。
- **P14-E1**：补齐已有物件行为与PTL；依赖P13-E1、P13-W碰撞、P06行为、资源/音频。
- **P14-E2**：payload事件与持久化；依赖P13-E2/P14-E1、P04提交；通过P15奖励接口联动，在P18完成真实奖励整合验收。

验收包括当前全部合法放置与全源类型覆盖报告、多攻击去重、左右反应、XYZ边界、破坏前后阻挡、长保持帧、持续光效、缺资源诊断、死亡/破坏中换房、待ack事件重载、粒子和奖励随机流分离。30/60/144/240渲染率和补tick结果相同。报告分别记录source-ready、runtime-complete、自动检查与用户试玩，不合并为一个完成数。
