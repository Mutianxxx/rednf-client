# C++ 工程模块地图

本文描述当前源码的真实职责、模块边界和仍在迁移中的部分。目录已经按职责分组，但当前 `dnf_core` 仍是一个链接归档；目录分开不代表依赖已经完全解耦。

## 运行入口

```text
src/app/main.cpp
  -> app::GameApplication
  -> World / 内容与资源服务 / Renderer
  -> 固定步模拟
  -> 只读表现采样
  -> SDL 绘制与音频
```

角色表现路径为 `Renderer::player()` → `CharacterPresentation` → `ICharacterDrawSink` → SDL 后端。`CharacterPresentation` 已把身体、装备、时装和技能附层组合从 SDL 绘制中分开；其它表现路径仍有部分高层逻辑留在 `Renderer`。

## 当前模块

| 模块 | 当前目录 | 当前拥有/消费的职责 | 不应接管 | 状态 |
|---|---|---|---|---|
| 应用装配 | `src/app/` | 进程入口、会话路径、输入接入、启动配置 | 技能规则、商店业务和绘制细节 | `GameApplication` 已接入；装配与 `main` 仍有迁移空间 |
| 内容定义 | `src/content/` | 角色、技能、音频、UI、区域和内容 profile 的来源模型 | 每帧业务状态和 SDL 纹理 | 有类型化 catalog；部分历史 `Json` 模型保留 |
| 资源 | `src/resources/` | PVF/NPK/IMG 访问、来源缓存、图片与动画资源对象 | 战斗状态和 UI 账本 | 已实际消费；缓存预算/异步准备仍待完善 |
| 角色与动作 | `src/simulation/actors/`, `actions/`, `animation/` | 移动、动作实例、技能阶段、输入窗口、动画时钟和帧事件 | 绘制伤害和纹理 | 公共执行器与多条历史职业路径并存，正在收敛 |
| 职业适配 | `src/simulation/jobs/` | 职业身份、动作注册、职业特有的控制器入口和源行为适配 | 复制公共碰撞/伤害/渲染系统 | 多种实现并存；女格斗的 40JP 适配属于实验/推理边界 |
| 战斗 | `src/simulation/combat/` | 攻击归属、攻击/受击几何、命中去重、伤害、异常、受击和死亡反应 | 看到特效就直接扣血 | 共用链已落地；部分公式、保护和跨版本行为仍未闭合 |
| 实体 | `src/simulation/entities/` | PO、弹丸、可破坏对象及对象生命周期 | 把所有可攻击对象伪装成怪物 | 基础对象和多种来源消费者已接入 |
| 怪物与 AI | `src/simulation/monsters/`, `src/simulation/jobs/` | AI 决策/意图、移动、动作选择和战斗服务调用 | 直接绘制、结算奖励或任意改玩家状态 | Event/Action/ACT 覆盖是部分实现，不等同全部副本 AI |
| 世界与成长 | `src/simulation/world/`, `progression/` | 区域、场景、房间、门、地图访问、等级、属性、装备和技能学习 | 由窗口直接修改状态 | 可玩流程组件存在；World 可写状态仍较宽 |
| 脚本宿主 | `src/simulation/scripting/` | ACT/Squirrel 运行时、预算、类型化宿主桥接 | 未知调用默认成功或越过世界事务 | 宿主和部分消费者已接入，未声明完整脚本兼容 |
| 持久化 | `src/persistence/` | 角色保存、奖励恢复、待提交奖励和恢复事务 | 绘制时提交业务 | 现有格式继续兼容；统一 session/事务接口尚在演进 |
| 人物表现 | `src/presentation/characters/` | 只读人物姿态，身体/装备/时装/技能层序组合 | 推进时钟、改属性或产生命中 | `CharacterPresentation` 与最小 sink 已运行 |
| 怪物/地图/效果表现 | `src/presentation/monsters/`, `maps/`, `effects/` | 怪物装备/附层、地图相机与图块、门/物件/效果显示 | AI 决策和伤害结算 | 已有职责分组；还未从 Renderer 完整抽离 |
| UI 与 HUD | `src/presentation/ui/` | `windows/` 弹窗和 `hud/` 常驻显示，呈现来源 UI 与交互 | 另存一份等级/装备/技能账本 | 窗口可用；统一布局引擎、读模型和命令边界未完成 |
| 音频 | `src/presentation/audio/`, `src/content/audio_catalog.cpp` | 声音事件消费、音频资源解码与播放 | 决定命中结果 | SDL dummy 有自动检查；听感仍需真实体验 |
| 绘制后端 | `src/render/` | SDL 绘制、字体、纹理/帧呈现 | 解释职业行为或改模拟状态 | 当前 Renderer 仍包含若干高层职责，后续继续收窄 |
| 诊断 | `src/diagnostics/` | 有界帧统计、来源追踪和运行诊断 | 无界保存每帧全量世界 | `FrameStatistics` 已使用预分配环形缓冲 |
| 开发工具 | `tools/` | 构建、架构审计、来源检查和检查点生成 | 把历史旧工程脚本当成新入口 | `tools/legacy/` 只保留构建调用的进程检查依赖；其它旧脚本不作新入口 |

源文件唯一归属登记在 `cmake/source-ownership.json`。新增或移动 `.cpp` 必须同步登记，并通过 `tools/verify_architecture.py`；只有被实际目标编译且有运行消费者的代码才算接入。

## 关键所有权边界

- `simulation` 以固定 60 Hz 运行，不包含 SDL include。模拟状态由相应对象/World 服务拥有；跨边界传递类型化请求、ID/句柄、来源定义或只读视图。
- `content` 保留原始 PVF/NPK 字段、来源路径、顺序、时间、坐标和版本身份。解析成功只说明数据可读，不说明游戏行为已执行。
- `presentation` 和 `render` 读取模拟结果；重复绘制不得重放帧事件、随机抽样、伤害或奖励。
- 战斗几何、攻击载荷、攻击归属、纯视觉 ANI 和接受命中是不同概念。特效不能自行造成伤害。
- UI 输入应该变成业务命令，经验证后提交；窗口不直接修改正常成长账本。该边界仍在逐步落实。
- 存档/奖励以相同提交代恢复；测试预览覆盖必须与正常角色技能、成长和存档隔离。

## 目标结构与差距

完整目标设计见 `../../knowledge/architecture/ARCHITECTURE-REFACTOR-OUTLINE.md`。目前优先继续收窄 `World` 的可写状态、把地图/怪物/效果表现从 `Renderer` 移出、建立 UI 命令/只读模型、统一技能动作执行和缩小构建目标。不要为每个目标目录先创建空类，也不要为逐个技能复制一套实现。

技能适配采用共用行为族执行器和来源绑定的动作计划，不按技能复制渲染/战斗引擎。40JP 的运行时状态分支、特效附着和对象生成线索及其推测边界见[技能行为族说明](SKILL-BEHAVIOR-FAMILIES-40JP.md)。

## 推荐改动归属

| 工作内容 | 先查模块 | 必须一起检查 |
|---|---|---|
| 新技能动作或普攻阶段 | `simulation/actions/`, `simulation/jobs/` | 来源注册、MP/CD、攻击归属、动画/声音事件、退出清理、动作专项测试 |
| 攻击框/伤害/浮空 | `simulation/combat/` | ANI/ATK 原始来源、坐标域、目标去重、存档与固定 tick |
| 新人物/怪物图层 | `presentation/characters/`, `presentation/monsters/` | 原层序、EQU/ALS 依赖、局部 XYZ、镜像和 Renderer 参考像素测试 |
| 地图/门/镜头 | `simulation/world/`, `presentation/maps/` | MAP/TIL 坐标、可行走几何、房间连通和多分辨率裁切 |
| 弹窗/HUD | `presentation/ui/windows/`, `hud/` | 源 UI 布局、绘制/命中同一变换、只读业务状态和输入事务 |
| 新资源解析 | `content/`, `resources/` | 原字节、字段顺序、来源身份、缓存策略、来源/解码测试 |

