# 通用技能程序与运行宿主 V2

本轮新增独立 `skill_program.gd` 与 `program_host.gd`，不向公共执行器增加职业、技能 ID 或技能文件名分支。来源编译器把当前 PVF 已注册的 NUT 回调编译为数据 IR；同一个解释器执行这些数据，宿主将操作接到现有动画、特效、攻击与受击系统。

## 新知识库提供的内容与边界

读取入口为 `dnf-部分知识库/pvf-utils-info/Resources/AgentKnowledge/`。本轮重点读取 runtime 参数流程、派生与取消流程、NUT API 快速入口、load_state 覆盖、高覆盖矩阵、API 分组、静态边界、CrystalAttack 时序案例与 PassiveObject/AttackInfo/Hitbox 说明，并对照官方 `animation.ani.txt`。

知识库提供可检索的入口链、参数线索、格式说明与 API 边界，**没有提供整个客户端的原生技能硬编码控制器源码**。高覆盖矩阵中的“100%”指该知识主线的入口/代表模式/边界收口，不等于本项目全部技能可执行。文档明确要求 `load_state -> pushState -> registeredName -> callback` 闭合，并指出静态链不能证明最终命中、伤害、同步或资源完整。

当前 1031 的实际注册及调用优先于知识库其它版本的样本。特别保留：`at` 是角色身份差异；`pushState` 最后参数是 skill index；PO ID 查 passiveobject registry；ANI flag 是帧事件；ALS frame 不是毫秒；预加载资源不证明实际调用与顺序；注释中的旧回调不会编译为有效执行。

## 数据合同

```json
{
  "schema": 1,
  "status": "executable",
  "entry": "state/substate",
  "unresolved": [],
  "source": {"path": "...", "sha256": "..."},
  "registration": {"source": "...", "state": 0, "skill_index": 0},
  "states": {
    "state/substate": {
      "enter": [{"op": "play", "clip": "source/path.ani"}],
      "events": [
        {"on": "flag", "flag": 1, "ops": [{"op": "spawn", "po_id": 123, "offset": [0, 0, 0], "definition": {"clip": "source/po.ani"}}]},
        {"on": "animation_end", "ops": [{"op": "end"}]}
      ],
      "exit": []
    }
  }
}
```

`executable` 仅用于来源编译器已闭合且当前解释器可以执行的程序；`partial` 保存已解析片段与具体 unresolved；`dependency_preview` 仅资源依赖浏览。后两者不能通过程序释放入口，不会将 preload ANI 连播当完整技能。

事件支持 `flag`、`animation_end`、`time`、`timer`、`input`。时间事件用 `at_ms`；timer 由 `interval_ms/count/immediate` 创建，补 tick 会逐次处理已跨越的事件。每次进入状态重置状态计时器和一次事件账本。`when` 支持表达式条件。

操作支持 `play`、`attack`、`spawn`、`set`、`if`、`state`、`timer`、`cancel_timer`、`end`、`move`、`scale`、`set_frame`、`reset_hits`、`sound`。`play` 优先用已解析 `clip`，可回退角色 `motions` 索引；`attack` 优先用 `descriptor`，可回退角色 `attack_infos`；`spawn` 优先用已闭合 `definition`，可回退 `catalog.passiveobjects`。这不是 Squirrel 全语言虚拟机，未编译的 NUT 特性必须保留 unresolved。

表达式是数据 AST：`{"var":"event.count"}`、`{"expr":"+","args":[1,2]}`，支持基础算术、比较、短路 and/or/not、min/max 和数组 index。无字符串 eval。状态、计时、条件共用指令预算与深度限制；非法操作、越界变量、除零或缺资源进入故障清理。

## 实际运行路径

```text
character registry / skill registry / load_state
    -> source NUT compiler -> program IR
    -> DnfSkillProgram enter / events / exit
    -> DnfProgramHost operation adapter
    -> DnfCombatWorld animation / layers / PO / attack instance
    -> source ANI ATTACK BOX intersects target DAMAGE BOX in ground XY + height Z
    -> shared damage / hurt / launch / down / death lifecycle
```

主窗口选择源技能后调用：

```gdscript
var host = preload("res://scripts/program_host.gd").new()
host.configure(world)
var accepted = host.start(skill)
# 每个 60 Hz tick；此处内部已经调用 world.step()，不要再重复调用。
host.step()
host.notify("input", {"key": "release"})
host.cancel("focus_lost")
```

`start` 检查可执行资格、角色状态、MP、冷却后提交。程序首次执行若缺动画或 PO，回滚 MP/冷却并清理当前动作和 owner 实体。运行期间 owner 死亡、切换或被攻击打断会终止程序。源动画 flag 只在进入对应帧时派发，跨短帧也不遗漏；停留同一帧不重复出生 PO。`animation_end` 只派发一次，阶段改变后重置。

战斗层保留 `program_controlled` 开关：由程序接管动作终止，避免世界先结束身体动作、移除附层后才执行 NUT 子状态切换。普通旧动作继续由 ANI duration 正常结束。程序解释器不复制攻击／受击算法。

## 当前限制

- 源编译器只可声明其实际覆盖的 NUT 子集。复杂 appendage、召唤 AI、粒子轨迹、鼠标控制、网络包与原生专用 API 不因 VM 有通用操作就算完成。
- `sound` 在此宿主输出带来源和已解析资源路径的 `program_sound`；`shake` 输出 `program_shake` 幅度／毫秒参数。主窗口音频和画面适配器负责实际消费，宿主合同测试本身不能代替播放验证。
- 原生硬编码技能若没有可恢复的程序入口，只能预览其明确资源；还需要客户端证据恢复行为。角色外观配置可以按角色独立，公共执行器不按技能文件名猜动作。
- 伤害与力到速度的转换仍沿用 demo 明示策略；源 ATK/盒消费不代表原版完整公式、保护、异常和 PVP 已还原。
- 自动检查覆盖通用解释器与宿主合同；实际来源编译覆盖需单独统计，不能把合成 fixture 数量当成可玩技能数量。

测试入口 `tests/skill_program_suite.gd`，报告 `reports/skill-program-tests.json`。引擎由父代理持锁串行运行；本节点源码编写不自行运行引擎。前台画面、声音和手感由用户验证。

## ALS world 对象

`clip.layers` 中 `space=world` 表示按源帧时间创建独立 draw-only 对象。战斗层消费 `start_ms/end_ms`，保存创建时的 XYZ、朝向与大小；之后人物或 PO 移动不再带动该对象。它可以继续拥有 follow 子层与 world 子层，递归有深度限制。动作结束／被打断、PO 销毁、source remove、自身动画结束以及换场都会清理对应对象。回卷动画会重新建立源事件账本。

普通 follow 层仍由渲染器组合；渲染器跳过 world 侧车条目，因为它已经成为 `effects` 中的独立实体。world draw-only 不继承攻击资格，不能因为动画有 type15 或身体在攻击，就擅自对怪物扣血。真正攻击 PO 必须由程序 `spawn` 提供闭合的 OBJ/ATK/ANI 描述器。`tests/als_world_suite.gd` 单独验证创建时机、局部偏移、朝向、固定位置、父子生命周期及无伤害边界。

`tests/source_program_suite.gd` 与合成合同测试分开，扫描实际已导出的可执行源程序，检查注册／来源、实际 flag 出生、宿主结束和原始盒命中；没有任何可执行源程序时会失败，不会将目录存在计为成功。

## ANI 帧声音

源帧 `sounds` 是声音标签数组；`pack.sounds` 将标签闭合到 `audio.xml`／SoundPacks 中的实际 OGG/WAV，随机标签保留带权 variants。战斗层在 60 Hz 扫描进入的源帧、跨过的短帧与零 delay 帧，对动作实例／帧／循环分别记账，输出 `ani_sound`。身体、受击、装备、follow 侧车与独立 PO 共用扫描；world 侧车已经成为独立实体，不再从父动画重复派声音。

所有事件有单调 `sequence`，即使超过 256 条的事件环移除了旧条目，表现消费者仍可按序号可靠去重。`setup` 新世界后序号归零，消费者同步重置。音频随机选择应使用独立的表现随机流，不改变战斗命中与伤害随机结果。`tests/frame_sound_suite.gd` 验证派发与去重，真实声音解码与用户听音单列。

## 本轮实际自动验证

父代理串行运行的当前收据：原战斗合同 78 项、程序 VM/宿主合同 35 项、ALS world 生命周期 16 项、帧声音派发 11 项、真实源程序集成 14 项，均 0 失败。共 154 项行为检查，与来源静态审计数量分开。

源程序集成只覆盖已实际编译导出的 2 个完整闭包：

| 注册身份 | 真实运行链 | 实际结果 |
|---|---|---|
| `4:116:98` | NUT 进入身体 ANI 与 ATK、声音、flag 震屏、结束回调 | 距离 25，63 tick 完成；源训练伤害 1020 |
| `8:1:0` | NUT 进入 ANI、flag 创建注册 PO、PO ANI/ATK、结束回调 | 距离 45，49 tick 完成；实际创建 1 个 PO，源训练伤害 180 |

身份仅用于记录测试内容，公共执行代码没有这些 ID 分支。前者 setter 列映射仍保存跨脚本推断说明；两者均不声称被动／装备成长／防御完整公式恢复。

首次源程序测试遍历 bootstrap 包时遇到 `selected_skill:null` 导致测试准备错误，真实日志 `v2-source_program_suite.gd.log` 保留；只修复测试枚举的类型判断后，完整门在 `v2-final-source_program_suite.gd.log` 与 `source-program-tests.json` 通过，没有把 partial 或 dependency_preview 改成 executable。以上不等于全角色全部技能已经可执行。
