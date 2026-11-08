# 06 世界、城镇、副本、相机与碰撞

版本：v1.1；日期：2026-10-18；状态：设计待实施。本文是后续实现约束，不代表当前客户端已支持全区域。

## 1. 当前基线与来源

- 可复用 [region.hpp](../dnf-native-demo/include/dnf/region.hpp) 的 `RegionCatalog`、`DungeonRun`、`MazeDefinition`、`MonsterSpawn`；[scene.hpp](../dnf-native-demo/include/dnf/scene.hpp) 已有原图层、视差系数、背景原点、TIL网格、NPC、出口与对象视图。
- [region.cpp](../dnf-native-demo/src/region.cpp) 目前固定艾尔文TWN、洛兰WDM、DGN 1/2、两目录MAP和少量NPC/任务。固定源路径alias、按文件名首字母判断起始图均不能作为全版本通用规则。
- [CURRENT_TASK.md](../dnf-native-demo/CURRENT_TASK.md) 的33份合法MAP、682个物件放置、198个光效工厂仅为当前洛兰回归基线，不是全区域覆盖数。
- [世界研究](../dnf-result/docs/03-world-and-maps.md) 提供源字段解释；其中链接到旧GBA派生实现的内容不可复用。只采用可从当前PVF重新核验的原始语义，重新计算平台无关模型。

## 2. 来源目录、链接与能力闭包

保留 `RegionCatalog` facade，内部拆为 `WorldCatalog`、`WorldLinker`、`MapCompiler`、`DungeonGenerator`、`AdmissionService`。注册身份采用 `ContentProfileId + ResourceKind + sourceId`，资源路径作为来源属性。完整保留列表顺序、重复记录、源偏移、字节、未知字段；同一路径多ID仍保留独立注册身份。

```cpp
struct CapabilityIssue { SourceRef source; Severity severity; std::string feature, reason; };
struct AdmissionResult { bool allowed; std::vector<CapabilityIssue> issues; CostPlan cost; };
AdmissionResult evaluateAdmission(const ContentProfile&, DungeonKey, const CharacterState&, Difficulty);
CompiledMap compileMap(const SourceMap&, const ResourceResolver&, const BehaviorRegistry&);
RunLayout generateRun(const DungeonDefinition&, const QuestContext&, RandomStream&);
```

`WorldLinker`建立TWN区域/出口→WDM→DGN→maze/MAP→MOB/OBJ/NPC/任务/动作/资源依赖图。边包含引用字段、偏移、必要性与行为用途。对静态引用做循环检测；运行时递归生成通过执行预算控制，不能把合法循环资源一概拒绝。

能力状态为 `SourceReady / Executable / ExecutableWithInference / Blocked`。解析成功不等于可执行。必要依赖闭包必须包含地图碰撞、出口、首领判死、所需任务事件、攻击行为、必需物件payload；装饰图片缺失作为警告而非封锁整个资源包。缺失影响玩法的依赖仅阻止对应内容入口，并显示原因链。全十职业转职/觉醒必需区域和任务链属于最终交付门槛，不能通过禁用将其算作达标。

未知区域不回退洛兰、不按目录名自动纳入随机池。兼容alias必须放版本绑定适配表，保留原路径、目标路径、依据和有效源哈希；只有唯一验证通过的映射才生效。

## 3. 拓扑与入口事务

DGN保留多个maze、完整地图规格候选、首领规格、普通/特殊路线、门方向与必需/允许门型。首先按任务和模式选择合法maze，随后在源拓扑上求解房间候选、对向门一致和起点至首领可达。起始图优先使用DGN坐标约束；旧文件名推断降为显式候选策略。合法来源不足时返回可定位失败，不强行补边。

随机源按run/子系统分流，避免粒子随机数改变地图。保存 `generatorVersion`、maze、完整选中布局、所有候选、入口和seed；读档恢复保存布局，不重新抽图。源更新时交由迁移服务处理。

```text
Enter(requestId, character, dungeon, difficulty):
  在单写者队列中重新检查资格和能力闭包
  在事务候选状态中生成完整layout并预载必需资源
  编制材料/疲劳等CostPlan（未确认规则使用标明版本的候选策略）
  同一提交写入成本、run、RNG、任务入场事件、返回位置
  提交成功后切场；失败保留待重试的同一请求与layout
```

选图UI和最终入场使用同一 `AdmissionService`；难度、等级、开放任务、材料、疲劳、队伍模式都在最终提交前再检查。取消后入口门闩直到离开触发区域才重置；重复输入按请求ID幂等。房门开启由清场与源机关条件决定，不能只检查当前可见怪物数量。

## 4. 源图层、坐标与相机

`MapCompiler`输出源单位的 `RenderLayer`、`TilePlacement`、`WalkMesh`、`ExitVolume`、`SpawnPlacement`，渲染器不反向修改模型。明确区分MAP世界坐标、背景原点、ANI局部偏移、IMG裁切原点、相机偏移和平台缩放；背景原点只能转换一次。

- 保留远景、中景、主地砖、扩展地砖、实体、前景源顺序。实体排序由源层与地面Y组成，稳定序号作为相等时tie-break；视觉高度Z不直接替代地面深度。
- 图块步长来自对应TIL类型的网格/逻辑尺寸，不能统一套16×16。扩展地砖按主网格列数换行，起点按源背景原点转换。
- 重复背景以IMG逻辑画布尺寸为周期，不使用裁切后像素宽度；保留X/Y重复、屏幕锚定与视差。已知字段按源执行，未明字段采用可切换 `source-parallax`/`fixed-background`候选并记录，不按区域打补丁。
- 相机默认跟随角色地面位置、限制在可呈现场景边界；屏幕比场景大时居中留边，不扩张碰撞。震屏作为展示偏移，不影响世界坐标和输入判定。镜头边界优先源值；缺失时使用地图编译范围，此为标注的通用推理。
- 800×600是UI参照，宽屏/高DPI经同一Viewport变换计算绘制和点击；不缩改源坐标。

## 5. 碰撞与换房

统一 `CollisionWorld`支持通行网格/多边形、实体footprint、受击XYZ盒、出口触发体。移动采用连续扫掠或足够的分段，先候选位置、后阻挡裁决、再提交；高速冲刺不穿过薄墙。地面XY与高度Z分别处理，沿墙滑动规则独立登记。攻击接触不复用通行框。

物件缺失Z范围时默认采用**地面footprint阻挡策略**：参与贴地行走与地面移动约束，不凭空声明无限高墙；空中能否跨越为策略边界，未获高度证据时测试窗口标记该对象。禁止把未知当零高受击框。详见 [07](07-monsters-objects-and-particles.md)。

换房按冻结输入→形成旧房快照→提交目标房及入场点→恢复实体→发布呈现事件顺序执行。出口使用TWN/MAP方向/目标区域，出生点优先对应入口；无对应点时采用源声明spawn，否则诊断阻止，不能固定出生坐标。

撤退、死亡、复活、结算分别为显式流程状态。撤退保存已取得且规则允许保留的奖励，执行源疲劳/耐久/失败惩罚，再返回保存的城镇入口。死亡不自动当通关；复活消耗/次数/恢复比例走独立策略。疲劳扣除时机未确认时推荐入房首次提交扣除、同房重进不重扣，并标记推理；不得使用旧GBA宽免规则。

## 6. 子任务与验收

- **P13-W1**：来源全注册、链接和能力报告；依赖来源解析/ContentProfile。产物含全部TWN/WDM/DGN/MAP状态与阻断链。
- **P13-W2**：MapCompiler、相机、通行/出口；依赖W1和资源渲染契约。
- **P13-W3**：多maze与任务变体求解、存储布局；依赖W1、P04事务；任务条件使用P15共享查询合同，最终真实任务联动由P18验收。
- **P13-W4**：入场/换房/撤退/失败/结算；依赖W2/W3、P13实体生命周期、P04快照；成本奖励先绑定P15接口，最终集成由P18验收，避免P13与P15形成构建依赖环。

验收遍历每个DGN全部合法候选，检查门互通、可达性、特殊图排除、确定随机结果；测试跨渲染帧率和补tick的一致性、高速移动、未知Z边界、重复入场、材料不足、磁盘失败、取消门闩、场景较小/宽屏/高DPI换算。最终用户试玩完整城镇→副本→结算/失败→返城→重载；逻辑检查不能替代真实画面验收。
