# PVF AI Agent Workbench 3.1.1：技能、战斗、渲染补充参考

本参考汇总用户提供的 Workbench 3.1.1 及其解压副本。本地逐文件 SHA256 对照确认两份 ZIP 的 1,998 个成员与解压文件完全一致。原始资料保持只读；本项目没有执行其中的 exe、dll、Node 扩展、bat、js 或 nut。

研究记录与本 Godot demo 的具体对照见 [Workbench 3.1.1 审查](../../../dnf-godot-skill-demo/docs/WORKBENCH-311-REVIEW.md)。资料版本、原始清单、解压一致性和语义覆盖边界见 `dnf-godot-skill-demo/reports/workbench-311-review/`。

## 可用于通用实现设计的内容

按 `knowledge-pack/indexes/knowledge-index.json` 进入对应主题，并将任务卡/词典作为语义索引：

- `skill-state-nut-runtime`、`nut-api`、`nut-runtime-callback-data-ui-act`：入口注册、state/substate、skill 等级数据、输入、回调、timer、动画帧及 UI/ACT 的职责边界。
- `passiveobject-attackinfo-hitbox`：PO 注册、创建包的类型/顺序、目标对象、AttackInfo、帧级攻击框、direct-hit、命中列表和生命周期。
- `monster-action-animation`、`monster-ai-action-attack-cross-layer`：MOB 动作槽、AI 返回、ACT、ANI/ATK/PO 与实际命中分别闭合。
- `passiveobject-nonmonster` 及 ActionObject/MapObject/BreakableObject/SPC 词条：非怪物地图对象与怪物实体分开审计；按真实 placement、受击/破坏动作、HP、粒子、声音和销毁链追踪。
- `client-ui-layout-pos-lay`、`client-assets-imagepacks-ui`：UI 控件关系、资源身份和 ACT 引用的读取线索；静态布局不证明 native 行为或字体。
- `外置知识库/GiteeNut注释/04-动画系统.md`：可用于发现跳跃攻击、受击槽、动作取消帧、图层和图形效果 API 家族；该社区示例不是本客户端运行时事实。
- `外置知识库/GiteeNut注释/09-数据传输.md`：可用于定位状态包和 PO 收发包字段；数据宽度、顺序、读写双方必须回到目标脚本闭合。
- `外置知识库/Xiti Fox注释/Xiti Fox字段注释词典.zh-CN.md`：可用于找到 ATTACK BOX、DELAY、IMAGE POS、hit info 和怪物动作字段的候选解释；逐字段以本项目现有 ANI/ATK 证据及目标字节为准。
- `外置知识库/牧野技能注释/职业动静态参数词典.zh-CN.md`：可以帮助定位社区归纳的技能名和参数候选；作者已标明“需验证”，且会包含其它版本内容。

## 必须区分的链路

```text
职业/技能注册 + CHR + 学习/输入资格
  -> NUT / ACT / 职业 native 入口
  -> state/substate + 动画实例 + 原始毫秒时钟 + flag/timer
  -> 身体动作 + 装备/技能武器层 + ALS + draw-only + PO + appendage + PTL
  -> 每个对象独立的局部/跟随/世界坐标、图像偏移、缩放、图层和寿命
  -> 当前 AttackInfo + 帧级三维攻击框 / 明确的 direct-hit 请求
  -> 目标过滤 + 接受命中 + 去重/多段计数
  -> 伤害/异常 + 受击状态 + 命中特效/音效
  -> 击退/浮空/倒地/起身/死亡 + 中断/离场/故障清理
```

ANI 图片、图像偏移、碰撞盒、攻击框、AttackInfo payload 和技能创建者属于不同层。draw-only/ALS 不自动是攻击；攻击框存在也不证明目标接受了命中。角色附着坐标、局部偏移和已生成对象的世界坐标应分别保留。不能从一个技能的参数/回调推广所有技能。

## 证据和版本边界

- Workbench 中的“默认可用/需验证”和覆盖率数字是该知识产品自身状态；不等于 DNF 1031 PVF caller 或运行行为已通过。
- API 声明、社区教程、字典列候选、资源名和 PVF 静态引用可用于定位；不能独立证明入口可达、参数语义、特效时机、碰撞结果、伤害公式、怪物反应、图层和资源包存在。
- 技能 ID 必须从当前 PVF 对应职业 registry 解析；NUT/PO 路径必须从当前职业入口和创建关系闭合。
- 1031 专有行为必须绑定当前来源身份并读目标文件/运行消费者；不同版本、后期职业和工具示例不能混用。
- 社区注释存在误注：`GiteeNut注释/04-动画系统.md:106-110` 将 `getSitAni` 标成死亡；`05-UI绘制.md:198-201` 的“帧率”标题实际使用 `setImageRate`。不把这些当死亡动画映射或时间语义。
- `06-附加对象(Appendage).md` 对附加 API 最后一个布尔参数的解释内部冲突；`09-数据传输.md` 与 `03-状态系统.md` 对状态包布尔参数的标签也不一致。需要看目标 writer/reader/callback，不能用示例注释消除冲突。
- UI 自绘函数、ACT 事件和 CALL/CHECK FUNC 需要实际注册者、时钟、行为队列与 native 消费者；控件名或资源路径不能替代业务处理。新包没有提供“菜单”“商城”字形来源证据。

## 对当前 Godot 技能预览的影响

当前目录 compiler audit 仍是 **2 executable / 52 partial**；本参考不提高任何完成计数。已导出的 1,734 技能记录、1,430 动作和各项静态资源覆盖是索引/调用图覆盖，不等于技能可执行率。

新资料可以指导以下通用缺口：完整 Squirrel callback/状态参数/对象变量；timer、输入和生命周期；类型化 PO 数据包与 PO 子程序；视觉/攻击分离；动态 AttackInfo/攻击盒/命中账本；角色、装备和技能对象的独立坐标；UI ACT 事件执行器。每项必须由源编译/解释器消费并有跨源形状测试，未知调用仍显示诊断，不按技能 ID 写专用分支。

资料没有补齐 1031 缺失的 native caller、最终伤害/防御/抗性与 hitstop 公式、所有技能特效出生条件、装备层攻击框资格、完整怪物 AI/受击动态或 UI native 业务回调。这些仍须从当前源或明确标成推理的可比较策略解决。
