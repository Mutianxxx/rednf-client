# 10 存档、角色管理、事务与版本迁移

版本：v1.1；日期：2026-10-18；状态：设计待实施。

## 1. 当前基线

[storage.cpp](../dnf-native-demo/src/storage.cpp) 已支持20角色槽、schema1..4身份迁移、备份恢复、Windows写入flush和原子替换；[storage.hpp](../dnf-native-demo/include/dnf/storage.hpp) 保留未知字段。[session.cpp](../dnf-native-demo/src/session.cpp) 保存相对动画时间、怪物死亡姿态/碎片，当前副本schema3以seed重新生成再比较布局。需要补全内容版本身份、统一事务提交、多文件一致性、完整实体图恢复和跨PVF隔离，不能把已有原子单文件写入当完整跨状态事务。

## 2. 存档边界与结构

推荐新快照schema5（实际落地前检查当前最高schema，保证单调升级）：账号拥有20个兼容槽位，每个角色有稳定UUID；槽位不是角色身份，删除后复用槽位不复用UUID。新增结构保存 `schemaVersion/buildVersion/contentProfileId/pvfHash/resourceManifestHash/ruleSet/generatorVersion/commitId/previousCommit/checksum`。

```text
SaveRoot
  account: slots[20], sharedStorage, localCalendar, settingsReferences
  characters[uuid]: identity, name, progression, inventory, equipment,
                    quests, skills, location, lifecycle, testProfileReference
  sessions[uuid]: layout, worldSnapshot, entityGraph, RNG,
                  pendingEvents, ledger, resultReceipts
  migrationHistory, unknownFields
```

原始来源数据不复制进每个存档，但保存来源身份、版本及必要恢复参数。测试覆盖值独立命名空间并在候选界面显示；正常数据不被临时锁HP/无CD覆盖。旧缺字段使用明确迁移默认，不将显式0技能等级改1。

20槽维持现有兼容，不把历史GBA实现当迁移依据。旧档按已识别schema逐步迁移到新临时副本，校验成功再保存，原文件与备份保留。未知字段保留，未知职业/道具/任务作为隔离记录诊断，禁止删除或冒充鬼剑士。

## 3. 创建、命名与删除

创建流程使用注册职业/成长身份、可执行控制器资格、源初始属性/装备/技能/起点，事务内分配UUID和槽位。未达运行能力的职业在阶段候选中不可创建；最终十职业门槛仍必须完成。

命名默认UTF-8，验证有效Unicode、去除首尾空白后保存显示串，拒绝控制字符和路径分隔符。来源明确限制优先；源限制未确认时推荐1..12个Unicode标量且UTF-8不超过48字节，明确这是本地候选规则。唯一性键使用NFC规范化＋Unicode 15.1 casefold，同一账号内不得重复；显示串保留大小写，规范化库版本随规则记录。显示名绝不拼接成文件路径。重命名保留UUID与引用，使用同一唯一性检查。输入法文本编辑与键盘战斗输入分别处理。

删除只作用用户明确选定的UUID：二次显示姓名/职业/等级确认，处于运行会话时先退出该角色。提交删除墓碑并释放槽位，旧角色快照进入本地恢复归档；不递归清理未知目录。删除/恢复与账号仓库引用检查同事务，测试候选不得默认删除用户角色。归档清理作为后续显式维护操作。

## 4. 单写者事务与磁盘失败

每个saveDir由一个 `SaveCoordinator`拥有写锁，第二进程只读或提示改用独立saveDir，不能两个进程同时原子覆盖同一主文件。测试进程默认独立目录。所有会改变游戏事实的命令进入单写者队列；请求ID及结果收据用于UI重试幂等。

```cpp
struct CommitEnvelope {
  CommitId id, parent; RequestId request;
  GameSnapshot candidate; PendingEvents pending;
  EventLedger ledger; RandomStates random; ResultReceipt result;
};
CommitResult submit(GameCommand);
CommitResult retry(CommitId); // 重用原候选，不能重执行随机计划
```

```text
submit(command):
  若请求收据已存在：返回相同结果
  串行读取当前单写者内存权威代（含尚未落盘的模拟进展），验证命令
  复制/写时复制为candidate，在其中执行状态与RNG变化
  将此前未落盘批次与本命令合并形成envelope，包含同一时点世界快照、世界事件、库存、任务、ledger、pending和RNG
  将envelope写到唯一临时文件，flush，校验，原子发布manifest/快照
  成功：发布commit并返回收据，再发UI/声音等表现通知
  失败：保留该envelope和commitId，暂停依赖它的后续变更并允许重试
```

内存模拟提交与磁盘持久提交分别编号；业务命令不得从磁盘lastCommit另建分支而丢弃期间进展。强制提交合并当前内存代全部相关pending批次，磁盘lastCommit仅用于崩溃恢复和备份。

磁盘失败不能重新roll：同一进程重试同一envelope；进程崩溃后恢复最后完整提交代，未提交命令连同其世界事件和RNG一起回退。不能保留新的击杀世界状态却回退掉落账本，也不能恢复新背包配旧“未领取”标志。游戏结果不依赖声音是否已播放；音频等外部副作用不声称严格恰好一次。

默认完整快照原子替换＋上一有效备份。若为性能分块，分块文件以内容hash/commitId命名，全部写完并校验后原子更新根manifest，读档只读该代引用；不能分别覆盖characters/session/progression三个活文件。Windows使用文件flush和原子替换，其他平台抽象 `StorageBackend::durableCommit`，说明平台实际耐断电能力。

无需每tick写盘：固定tick维护内存候选代；击杀/掉落等世界事件按短批次合并，购物/任务/入场/退出等明确事务边界强制提交。推荐初期批次上限1秒或64个持久事件，以先到者为准，性能测量后可调；完整批次包含世界快照、RNG、事件与经济状态。异常退出最多回退至上一完整批次，界面/文档说明这一边界，不承诺每帧保存。磁盘故障时停止继续累积不可提交的经济操作，提供重试/保留当前内存候选提示。

## 5. 实体图与副本恢复

保存已选maze与完整房间布局、生成器版本、visited/cleared、实例身份、物件状态、怪物动作、相对时钟、技能/弹丸/召唤实体、owner/target、命中登记、RNG及pending事件。读档不能再次调用当前生成器重抽房间。

恢复顺序：

1. 校验schema/checksum/内容身份，选择最后完整代。
2. 加载不可变定义和必需资源，校验能力。
3. 分配所有实体新运行句柄，建立保存ID→句柄映射，暂不执行回调。
4. 恢复状态、相对时间、随机流和动作program counter。
5. 重映射owner/target/抓取/附层/发射器等关系，检测悬空引用。
6. 完整图验证后执行`onRestore`，注册碰撞/事件，再投递未完成pending。

仅无持久影响的短暂动作允许在读档时按明确契约安全取消，并清理其抓取/无敌/临时增益；持续召唤、变身、DOT、任务及机关脚本必须实现状态恢复，或只在已定义安全点形成可恢复检查点，不能以“安全退出”抹掉持久玩法状态。不能遗留半图或把来源缺失视为已死亡。死亡/破坏中的奖励已在ledger存在则不重发，动作继续相对时钟。超长保持帧保留。

## 6. 跨PVF、策略与旧版本迁移

不同ContentProfile默认不同存档命名空间。用户切换PVF不静默重新解释旧物品ID、重新抽副本或重新计算已经发放的随机奖励。可见列出兼容性和显式迁移入口；迁移计划先在副本计算并报告变化，再建立新档，原档保留。

迁移依据注册身份、路径/源hash及明确映射，不能单凭同名。缺失物品/任务保存隔离项，缺失地图保留旧run快照并提示不能继续；只有用户选择终止旧run时按迁移策略回安全城镇，不默认吞奖励。公式/成长策略更新区分“未来计算变化”和“重算已有属性”；实例随机属性不得重roll。

旧Session版本转换记录原始未识别字段和推理默认；历史对象缺稳定身份时按原记录来源匹配，存在歧义保留诊断不派发payload。存档schema高于程序支持时只读拒绝写入，不能自动降级覆盖。

## 7. P04任务DAG与验收

- **P04-D1**：schema、来源身份、20槽UUID与迁移器；依赖来源/角色目录。
- **P04-D2**：单写者队列、锁、事务envelope和提交后收据；依赖D1，提供P15服务基础。
- **P04-D3**：世界批次与实体图恢复；依赖D2、P03实体合同；预先定义布局/实体序列化接口，P13世界及P14物件接入后由P18完成真实快照验收，不反向要求基础P04依赖P13。
- **P04-D4**：创建/命名/删除/恢复、跨PVF副本迁移、备份工具；依赖D1-D3。

验收：旧schema逐级迁移、显式0级保留、未知字段存活、20槽满槽/删除复用UUID不复用、Unicode命名与重名、损坏主档备份恢复、前后版本拒绝写入、两个进程写锁。对临时写入/flush/原子替换/manifest发布每个边界注入故障，验证库存/任务/掉落/ledger/RNG/世界同代；磁盘失败重试不重抽；实体循环引用先映射后回调；跨PVF不静默重抽地图。测试目录独立，用户原存档只读备份，不以前台试玩冒充这些故障测试。
