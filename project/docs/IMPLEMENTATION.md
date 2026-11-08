# 实现与恢复入口

当前节点见 `../../PROGRESS.md`；实际构建/测试身份见
`../checkpoints/build/build-verification.json`。节点备份不随源码入库，
需要时用 `../../checkpoint_refactor.py` 封存后再核对 manifest。
完整设计见 `../../knowledge/architecture/ARCHITECTURE-REFACTOR-OUTLINE.md`。

## 当前运行路径

`src/app/main.cpp` → `app::GameApplication::run` → 现有 World/内容/业务装配。
人物绘制经 `Renderer::player` → `CharacterPresentation` → `ICharacterDrawSink` → SDL 后端。
主循环使用有界 `FrameStatistics`，不改变既有固定模拟步调和游戏时钟。

## 模块约束

- `content/resources` 保存来源定义与资源服务，运行实例状态属于模拟。
- `simulation/actions/jobs` 保留公共执行与职业入口区别；普攻也属动作执行，不在渲染实现伤害。
- `simulation/combat` 统一攻击归属、几何、payload、命中与反应；纯视觉不自动造成伤害。
- 怪物 AI 决策与怪物表现分目录；全部所有权接口收窄仍按后续节点推进。
- 弹窗/HUD 分目录，共享既有源UI资源；完整 WindowManager/命令读模型迁移尚未完成。
- `persistence` 保留同代事务、奖励恢复和现有存档格式。新工程使用独立存档。

当前 `dnf_core` 仍是共同链接归档；源码分组不表示所有依赖已经解耦。
参考 `REFACTOR-NODE-A0-A2a.md` 的实际完成/剩余边界。

## 验证原则

源码/构建身份、自动运行、前台体验和原版动态比较分别记录。单独类、空接口、静态索引
或演示通过都不能算完整内容验收。原资料、旧工程、历史候选和正常用户存档保持原位。

## 40JP 公共战斗与职业执行

ATK 响应读取在 `simulation/combat/attack_response.cpp`，命中反馈与受击执行在
`monster_hit_response.cpp`。普通硬直、浮空倒地、hit stop 和纯视觉反馈分别消费，
源 ANI 毫秒与原字段保留。四条伤害路径共用响应与反馈消费者。

女格斗家的冲突行为按用户要求优先采用 40JP；1031 资源绑定与版本差异单独登记。
技能由职业描述组合公共阶段、身体攻击、投射物、抓取与附层，禁止逐技能复制执行器。
UI 外观保持当前版本；源 AI 移动与怪物 ALS 生命周期独立于 UI。

当前进度与实际验证状态见 `../CURRENT_TASK.md`、`../reports/40jp-deep-merge/`。
未构建代码、编译候选、专项检查、完整回归和用户体验分别记录。
