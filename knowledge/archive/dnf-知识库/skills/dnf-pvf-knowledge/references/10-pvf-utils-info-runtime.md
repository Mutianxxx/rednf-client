# 新增 pvf-utils-info 与通用技能/渲染/判定运行时

2026-10-21。用户指定新增 `D:/dnf-rebuild/dnf-部分知识库/pvf-utils-info` 为本轮优先文档来源。原始资料保持只读，不运行附带 `pvfUtility.exe`、DLL、脚本；项目可参考其文档，不能把 .NET 库名当 DNF native caller 源码。

## 入口

- `Resources/AgentKnowledge/README.zh-CN.md`、`safety/README.zh-CN.md`：事实/边界分类。
- `indexes/skill-state-nut-runtime-high-coverage-matrix.zh-CN.md`：按入口API族和运行模式分类，明确停止默认逐技能深拆。
- `indexes/skill-state-nut-runtime-api-group-boundary.zh-CN.md`、`dictionaries/nut-runtime-api-boundary*.zh-CN.md`：入口、state、PO、AttackInfo、appendage、timer、运动、视觉、对象生命周期的宿主API组。
- `Resources/OfficialAnnotationTranslation/animation.ani.txt`、`sample.ani.als.txt`、`charactersample.chr.txt`、`equipmentsample.equ.txt`、`actionsample.act.txt`、`attackinfosample.atk.txt`、`passiveobjectsample.obj.txt`：新非空翻译样例。
- `dictionaries/client-ui-layout-pos-lay-fields.zh-CN.md`、`indexes/client-ui-layout-pos-lay-boundary.zh-CN.md`、翻译 `uiactionsample.act.txt`：UI描述、资源、事件和native CALL FUNC边界。
- `Options/PvfComments/*.json`：社区 Comment 与翻译样例 OfficialDescription 分开看；`Defaults/Options/` 镜像需按哈希辨别，不假设一致。

## 采用与证据

先依本项目 `skills/KNOWLEDGE_POLICY.md`。文档“默认可用”是静态解释状态；“高覆盖100%”是模式/API研究覆盖，非游戏技能完成率。其“主目标”出现 qf 定制脚本，必须重新核本项目1031 PVF身份，不能照抄state/substate、技能ID或注册数量为本地事实。文档内部也有快照冲突：learnability词典称 startSkillCoolTime未命中，而runtime词典/链索引记录HolongLight调用；只按当前PVF实读裁决。

新 animation 文本明示 IMAGE RATE 原大小1.0；CLIP坐标相对动画基准点；INTERPOLATION影响RGBA/IMAGE POS/IMAGE RATE/IMAGE ROTATE/CLIP；LOOP START/END文本语义明确，但不证明二进制25/26枚举。ALS `add/remove` 首参数是父动画帧，不是毫秒。EQU expand ani 第三参数控制是否使用替换动画攻击框，不能无条件合并所有身体/武器框。官方bytool六字段攻击框注释有二维误标，保留当前XYZ+extent证据。

ATK提供攻击payload/目标/反应，不提供帧级几何。DRAWONLY/ALS/appendage视觉层不自动具有攻击身份；源可能由独立PO攻击，也可能用hit packet直接命中选定目标。受击状态、hitstop、浮空、倒地、死亡、清理需要运行消费者。不同技能参数表列义不可全局相同化，通用的是解释器/宿主API。

## 实现要求

统一 input/skill资格 → state/动作 → ANI帧/flag → EQU/LAY/ALS/PO/AP/PTL → AttackInfo + 攻击盒/直接命中 → 接受命中事务 → 受击状态/视觉/声音 → 清理。NUT脚本充足时由宿主执行源程序；原生技能缺调用者时按职业恢复入口或明确缺口，不通过资源名和preload清单猜特效播放顺序。补实现以API组/通用行为为单位，禁止新增逐技能专用执行分支和手写模板补丁。

UI统一 `.ui` 的父子/图层/类型/选项 → 当前NPK/IMG/ANI/ACT → Godot控件/绘制 → 鼠标/键盘/trigger/behavior → 业务native caller。`CALL FUNC`只给函数索引和参数，需要本机host绑定，不能凭控件名猜业务成功。`.lay`在此为人物motion层模板，不能误作UI布局表。

本轮机器全扫与实际语义阅读分别见 `dnf-godot-skill-demo/reports/knowledge-v2`，详细总结见 `docs/KNOWLEDGE-V2.md`。原始知识库、客户端、主原生工程、历史候选和存档保持原样。
