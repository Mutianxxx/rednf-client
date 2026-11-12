# 清风 1031 技能调用链补全计划

执行基座：清风 1031 Script.pvf SHA-256 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`。

## 执行原则

- PVF 字节和基座实机为一级证据，exe 调用点补足状态、派发、参数消费关系；40JP/60US 仅辅助解释。
- 文件存在、标签被读出、编译为命令、World 实际执行、原版表现核对分别验收。
- 字面引用与 exe 绑定候选、同名目录候选分别记录；未知参数保持未恢复。
- ACT 在怪物/被动对象中大量存在；只有技能闭包真实引用 ACT，才接入该技能。不能由全包 ACT 标签频率推断某个 PC 技能必须调用 ACT。
- 复用现有 `act_runtime`、`act_world_host`、Squirrel bridge 和粒子模块，补消费者或接线，不建立重复运行时。
- 每一阶段更新 README/PROGRESS、针对性测试、提交并推送；推送失败明确保留待推提交。
- 自动检查不替代基座逐帧和实际手感验收。AVI 仅作独立观测，不回填猜测参数。

## 顺序与修改范围

| 顺序 | 优先级 | 工作 | 主要修改位置 | 验收 |
|---|---|---|---|---|
| 0 | 前置 | 计划与既有提交同步 git | 本文件、README | 计划已提交；记录远端同步状态 |
| 1 | P0 | 技能资源闭包、标签消费者覆盖基线 | `project/tools/skill_closure.py`、`act_audit.py`、现有 inspect | 全 SKL 入表；相对引用/注册表 ID/ANI sidecar；明确候选、未知、未解析；不以资源存在率冒充消费率 |
| 2 | P0 | ACT 结构与实际消费者补全 | `src/simulation/scripting/act_runtime.cpp`、`act_world_host.cpp`、`act_service.cpp`、`include/dnf/act_runtime.hpp` | 保留嵌套、offset、原 token；CREATE PASSIVEOBJECT、SUB ANI、PARTICLE、移动/速度/重力、攻击开关、触发、ON ATTACKSUCCESS 有真实命令/实体/碰撞测试；未知显式诊断 |
| 3 | P0 | OBJ 生命周期与 NUT 宿主 | 现有 scripting、combat、source_skill_action、mapping | basic/etc action 与 motion 按状态选择；生成→移动→命中→销毁；投掷/追踪/重力/目标选择/动态 ATK；冰弓、枪手投掷和召唤实体各有来源与测试 |
| 4 | P1 | ALS 事件与依附关系 | `effect_plan.cpp`、preview session、combat | none-effect、delayed birth、rate、random/follow-parent 逐项证据；世界锚定与跟随行为同步；未恢复不伪装支持 |
| 5 | P1 | ATK 别名与反应字段 | 现有 attack/damage/status 解析消费者 | 校验原生拼写是否真的别名；状态/PVP/目标上限/硬直/霸体/重量分字段验证 |
| 6 | P1 | PTL 解析、粒子调度与播放 | 现有 particle 模块、对象/ACT host、renderer | 先审计既有解析覆盖；保留未知原字节；实际对象/技能发射、纹理与生命周期测试 |
| 7 | P2 | SKL 追加动画及输入/状态/BUFF | skill_data、source_skill_action、skill input、mapping | additional/start/end/loop（含原生拼写）、executable states、command customizing、active status buff、pre/post teleport 分项接入 |
| 8 | P2 | 跨系统资源消费者 | EQU/STK/KEY/AI/AIC/EVT/GDATA 既有模块 | 按技能引用闭包逐族补，分别登记标签、运行消费者与缺口；不声称一次覆盖全包 |
| 每步 | 持续 | 回归、文档、git | README、PROGRESS、tests | 合适专项通过后提交；有运行时修改才编译相关目标；每阶段记录 commit 与 push 状态 |

阶段 4/5/6 可在独立源码范围内并行调查，正式构建与集成串行；整体按表顺序交付。

## 逐功能验收清单（2026-11-12 核查）

本表核对源码、测试代码及既有报告；本轮未重跑构建/测试或联网核验远端。已完成仅限该行范围；“已有子集”不代表全部技能接入或1031原版等价。待验证不等于功能不存在。

| 节点 | 核心功能／对应任务 | 验收标准 | 状态及缺口 |
|---|---|---|---|
| 前置 | 计划及开源说明 | 顺序、构建入口、证据边界已入库 | 已完成 |
| 前置 | git阶段同步 | commit、push回执及远端HEAD可核对 | 部分完成；当前远端未重新核验 |
| P0-1 | 全SKL静态候选闭包 | 全SKL入表，证据/候选/未知分开且不截断 | 已完成工具范围：2008 SKL，仅20有字面资源证据 |
| P0-1 | 相对路径及ANI sidecar | 保留来源，歧义不任选，sidecar不提升为直证 | 已完成：641 sidecar；外部IMG未据此验证NPK存在性 |
| P0-1 | ACT显式INDEX注册引用 | 闭合CREATE块内整数经注册表解析，未知/重复/损坏保留诊断 | 已完成解析范围：6477唯一ID；全ACT检查13150 resolved、109 unresolved（既有记录） |
| P0-1 | 标签与真实准入工具 | 分类与执行支持分开；逐文件诊断、异常及整体ok可追溯 | 已完成工具范围：5638 ACT，整体ok1596，异常5；无模拟推进 |
| P0-1 | 技能→ACT/OBJ/NUT真实入口 | 每边有技能身份、调用点/offset与条件；未恢复边有调查证据和阻塞点 | 未完成：V3技能图ACT ID边为0，动态NUT/exe入口未闭合 |
| P0-1 | 技能标签→消费者账本 | 技能/资源/标签对应消费者、专项证据与缺口 | 部分完成：标签/准入报告已有，技能级账本未齐 |
| P0-2 | ACT结构及源保真 | 嵌套、原token/offset保留；未知显式诊断 | 部分完成：编译器已有子集，大量opcode/selector仍阻塞 |
| P0-2 | CREATE PASSIVEOBJECT工厂 | 真实实体生成、归属、参数、碰撞及取消/换图清理 | 部分完成：命令解析已有，World工厂未完成 |
| P0-2 | PARTICLE工厂 | ACT实际发射PTL，验证纹理、时钟及回收 | 部分完成：命令捕获已有，World消费者未完成 |
| P0-2 | SUB ANI及攻击身份 | 源帧/层/偏移正确，XYZ及攻击子动画独立碰撞身份/时钟 | 部分完成：组合子集已有，XYZ/攻击身份仍缺 |
| P0-2 | 位移/速度/重力 | 各标签改变真实位置，暂停/取消/恢复一致 | 部分完成：速度/传送/方向已有，通用运动和重力未齐 |
| P0-2 | 触发/延迟/命中事件 | 实际事件→调度→消费；去重、预算、恢复及跨程序边界可测 | 部分完成：调度/怪物命中子集已有，控制/跨程序接线缺 |
| P0-3 | OBJ状态与action选择 | 按状态选择源ACT/ANI，保留引用及未知字段 | 部分完成：元数据已有，通用状态派发未闭合 |
| P0-3 | 对象完整生命周期 | 生成→运动→命中→销毁；追踪/重力/目标/动态ATK可消费 | 部分完成：有限表现和投射已有，通用闭环未完成 |
| P0-3 | NUT宿主与动态攻击API | 真实回调驱动PO/状态/攻击；预算、回滚和销毁可测 | 部分完成：VM/伤害桥已有，通用PO宿主API未齐 |
| P0-3 | 冰弓/枪手投掷/召唤 | 三类各有源入口、World测试与基座对照 | 部分完成：局部重建已有，完整链及等价未验收 |
| P1 ALS | add/remove/draw-only事件 | 源帧/同帧顺序、层/实例名/偏移及回收正确 | 已完成既有子集；全部基座表现等价待验证 |
| P1 ALS | 通用none-effect | 源标志到渲染消费者有证据，不直接别名普通add | 部分完成：仅限定专用策略 |
| P1 ALS | delayed birth/rate | 源延迟/速率实际消费，跨帧/暂停/恢复一致 | 部分完成：名义birthMs及部分时钟已有，原生语义未恢复 |
| P1 ALS | random/follow-parent/世界锚定 | 随机可复现；父体移动/死亡/移除行为正确 | 部分完成：有限跟随/独立已有，通用语义未齐 |
| P1 ATK | 原生拼写别名 | 每别名有目标字节/消费者证据及独测 | 待验证 |
| P1 ATK | 统一伤害及异常状态 | 统一事务、去重、随机流、回滚和生命周期 | 已完成既有子集：六类状态；技能接入及原版公式另验 |
| P1 ATK | PVP/模式作用域 | 模式不串值，PVP有实际消费者测试 | 部分完成：隔离已有，完整PVP未验收 |
| P1 ATK | 硬直/霸体/重量/目标上限 | 源字段逐项驱动反应，目标上限单独验证 | 部分完成：通用消费者已有，逐字段覆盖未齐 |
| P1 PTL | 解析与未知保留 | 字段→解析器→消费者可查，未消费原数据和诊断保留 | 部分完成：读取子集已有，诊断未齐 |
| P1 PTL | burst与持续发射 | 频率、预算、停止、归属及取消清理可测 | 部分完成：burst已有，持续发射未完成 |
| P1 PTL | 运动/纹理/寿命 | 源解析→实际绘制→回收，不支持分支明确拒绝 | 部分完成：直线/重力/透明度/ANI已有，波形等缺 |
| P1 PTL | ACT/OBJ/技能发射 | 源命令发射，World/renderer一致，脱手/换图无残留 | 部分完成：预览已有，ACT工厂/通用对象链缺 |
| P2 SKL | additional/start/end/loop | 原生字段驱动阶段，结束/中断路径正确 | 部分完成：动作链已有，指定字段通用接入待确认 |
| P2 SKL | executable states | 源状态限制真实释放，校验资格/MP/CD | 部分完成：少数技能读取，未覆盖全部支持入口 |
| P2 SKL | command customizing | 源定义驱动识别，按住/松开/方向/冲突可测 | 未完成：本次未定位到通用消费者 |
| P2 SKL | buff及pre/post teleport | 字段驱动生效/失效、传送前后阶段及中断清理 | 部分完成：基础能力已有，指定字段接线未完成 |
| P2 跨系统 | EQU技能引用/触发 | 每闭包引用对应条件、消费者与测试 | 部分完成：装备基础已有，技能闭包未齐 |
| P2 跨系统 | STK技能效果事务 | 使用效果与扣除原子提交，可恢复 | 部分完成：物品基础已有，完整技能触发待验证 |
| P2 跨系统 | AI/AIC/EVT | 分族登记入口、归属、ACT接线及拒绝边界 | 部分完成：Action/Event AI子集已有，AIC/EVT整族待验证 |
| P2 跨系统 | KEY/GDATA跨族账本 | 来源边→标签→消费者→测试逐项可追溯 | 待验证：输入/能力索引不证明该闭包完成 |
| 持续 | 回归/基座对照/文档/git | 当前版本专项可追溯；AVI独立交叉验证；文档与提交一致 | 部分完成：历史专项/文档存在，本轮未重跑；用户反馈缺陷未最终验收 |

### 阶段门槛

1. 当前主线停留P0-1。已完成ACT准入工具归入其覆盖基线，不计作P0-2整体交付。
2. P0-1关闭必须交付技能级边与消费者账本：解释ACT边为0，定位动态NUT/exe入口或列出有证据的未恢复边；不得凭同名候选关闭，不要求凭空填满所有链。
3. P0-1验收后依次推进P0-2消费者、P0-3生命周期。后续已有能力保留，新增运行时接线在前置验收前暂停。
4. P1各项可独立调查，正式集成按ALS→ATK→PTL，再P2。每节点分开验收源解析、命令编译、World执行与原版等价。
5. 测试源码只证明测试存在；历史报告不证明当前版本重跑通过。整体ok与syntax/source/runtime独立旗标不可混用。

主要核查位置：`project/tools/{skill_closure.py,act_audit.py,inspect.cpp}`、`project/src/simulation/scripting/`、`simulation/entities/objects.cpp`、`simulation/actions/source_skill_action.cpp`、`simulation/combat/`、`presentation/effects/effect_plan.cpp`、`tools/skill_preview_particles.cpp`、`content/skill_data.cpp`及相应`project/tests/`。既有审计产物位于`checkpoints/tests/pvf-audit/`，不入库。

## 历史状态（2026-11-11；细化状态以上表为准）

- 既有审计提交 `1488f9852` 已在上一阶段成功推送。
- 初版候选扫描 `4d2a2bad7`、ACT 标签词族审计 `69e2f5509` 已本地提交；最近 push 报 schannel missing close_notify，待重新核对远端。
- [x] 计划入库、README 入口：提交 `ca87cbe71`。
- [x] 修正静态候选扫描口径并重跑：全 2008 SKL、1132 仅 SKL、853 关联 ANI、641 条 ANI sidecar；字面闭包与候选分开，未截断清单。静态关联不代表运行消费率。
- [x] ACT 词族审计改精确匹配：672 标签、98 归族、574 待归族；归族不等于解析或执行支持。
- [x] 单文件真实 World 准入导出 `--act-coverage`；定向构建与基座一成功/一拒绝样本验证。
- [x] 批量 ACT 准入与逐文件阻塞统计：`--act-coverage-prefix`；基座 passiveobject/ 共 5638 文件、1596 整体准入、5 异常；定向构建、计数一致性、空范围及参数错误验证通过。仅静态准入。
- [x] ACT 明确 CREATE PASSIVEOBJECT/INDEX 注册表整数引用解析：6477 唯一注册 ID；正常、未知、重复同/异路径、缺失/损坏注册表、块外及未闭合块验证通过；全 ACT 独立验证解析 13150 条、未解析 109 条。
- [ ] 技能到 ACT 的入口、动态名称、exe 派发闭包；V3 技能图尚未到达这些 ACT ID 边，整体任务 1 仍进行中。
- [ ] ACT 对象/粒子实际 World 消费者接通；整体任务 2 进行中，未验收。
- [ ] 后续 OBJ/NUT、ALS、ATK、PTL、SKL 与跨系统消费者依照上表推进。
- [x] git 同步：2026-11-11 重试成功，`4d2a2bad7`、`69e2f5509`、`ca87cbe71`、`c16361750` 已推送；独立读取远端 `refs/heads/main` 确认为 `c163617506a9e30f503c0f447e0126ec07c82ef4`。后续增量另行提交与推送。
