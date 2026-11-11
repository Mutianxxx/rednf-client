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

## 当前状态（2026-11-11）

- 既有审计提交 `1488f9852` 已在上一阶段成功推送。
- 初版候选扫描 `4d2a2bad7`、ACT 标签词族审计 `69e2f5509` 已本地提交；最近 push 报 schannel missing close_notify，待重新核对远端。
- [x] 计划入库、README 入口：提交 `ca87cbe71`。
- [x] 修正静态候选扫描口径并重跑：全 2008 SKL、1132 仅 SKL、853 关联 ANI、641 条 ANI sidecar；字面闭包与候选分开，未截断清单。静态关联不代表运行消费率。
- [x] ACT 词族审计改精确匹配：672 标签、98 归族、574 待归族；归族不等于解析或执行支持。
- [x] 单文件真实 World 准入导出 `--act-coverage`；定向构建与基座一成功/一拒绝样本验证。
- [ ] 批量 ACT 准入与逐文件阻塞统计（进行中）。
- [ ] 整数对象 ID、动态名称、exe 派发闭包；整体任务 1 仍进行中。
- [ ] ACT 对象/粒子实际 World 消费者接通；整体任务 2 进行中，未验收。
- [ ] 后续 OBJ/NUT、ALS、ATK、PTL、SKL 与跨系统消费者依照上表推进。
- [x] git 同步：2026-11-11 重试成功，`4d2a2bad7`、`69e2f5509`、`ca87cbe71`、`c16361750` 已推送；独立读取远端 `refs/heads/main` 确认为 `c163617506a9e30f503c0f447e0126ec07c82ef4`。后续增量另行提交与推送。
