# Workbench 3.1.1：战斗、技能与特效知识复核

本轮为用户新增资料的只读研究节点。结论是：**能补充一批通用运行语义、参数线索和排查方法，但不能仅靠这批资料补齐全部 1031 技能的原生调用者。** 当前缺失既包括执行器未实现，也包括目标版本证据未恢复；两者不能混为“PVF 没有特效”。

本轮未改游戏运行逻辑、未编译新体验版，主工程 `dnf-native-demo` 继续暂停。最新体验仍为 V3.1，入口 `Play-Latest.cmd`。未闭合调用链继续只提示；已知源程序片段、精确动作和引用资源可预览，未知条件不会被猜测执行。

## 资料覆盖和新增解压文件

来源：`D:/dnf-rebuild/dnf-部分知识库/PVF-Ai-Agent-Workbench-3.1.1`。两个 ZIP 和用户后来解压的目录均已纳入。

| 层次 | 本轮事实 | 边界 |
| --- | --- | --- |
| 最初物理文件 | 612 个，114,603,956 bytes；全部读取并记录 SHA256 | 不是 612 个文件逐条命题验真 |
| 两个 ZIP | 1,998 个文件成员，15,983,209 bytes 展开内容 | 在内存读取，没有执行其代码 |
| 文本语料 | 2,423 份文档，6,499,525 字符；文本/JSON 抽取错误 0 | 包含文档、索引和模板，不能当 2,423 条独立事实 |
| 用户新增解压 | 新增 1,998 个文件，与 ZIP 成员逐一 SHA256 一致，缺失 0 | 是相同资料的可直接访问副本，没有另增一套战斗证据 |
| 更新后物理目录 | 2,610 个文件，130,587,165 bytes；原先 612 个文件无修改、无丢失 | 源保护检查仅针对本次知识包范围 |
| 与此前知识库比较 | 1,657 份文本在去 HTML/空白归一后相同，其中 DAF 教程 1,614 份 | 重复内容不是第二份独立验证；不匹配也不自动代表新增事实 |
| 实际语义复核 | 重点复核 NUT/state、PO/AttackInfo、ANI/ALS/ACT、装备、怪物/破坏物和 UI；来源范围见 `semantic-reading.json` | 全库字节和结构覆盖、重点语义阅读、1031 对照、运行验证分别记录 |

详细收据在 `reports/workbench-311-review/`：`summary.json`、`source-manifest.json`、`current-source-manifest.json`、`extracted-update.json`、`previous-normalized-comparison.json`。附带 EXE、Node、DLL/原生扩展、BAT、JS 和 NUT 均未执行。

## 完整链路应如何拆分

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

这是一套通用解释器、宿主和生命周期接口。技能之间的不同由源程序、注册、动作槽和参数驱动。读取 SKL 预载清单或 ANI 图片后顺序播放，不等于恢复这条链路；给每个技能手写时间轴也不符合用户要求。

## 哪些未知可以得到补充

下面路径除另注外，均相对新包根。更详细逐项证据见 [战斗笔记](../reports/workbench-311-review/combat-animation-notes.md) 与 [UI 笔记](../reports/workbench-311-review/ui-package-notes.md)。

| 主题 | 新资料能补充什么 | 对现有工程的实际含义 | 仍不能确认什么 |
| --- | --- | --- | --- |
| 状态/输入/取消 | `knowledge-pack/dictionaries/nut-runtime-api-boundary.zh-CN.md:33–62` 与 `indexes/nut-runtime-callback-data-ui-act-boundary.zh-CN.md:7–27` 区分入口、state 包、substate、timer、skill-load | 补动态状态参数、对象变量、输入/持续/退出回调，不能只支持进入/flag/动画结束 | 抢占优先级、按住/松开窗口、冷却起点和所有 native 状态行为 |
| 特效由谁创建 | 同 API 词典 `:122–148,190–209` 区分 PO、draw-only、动画层、appendage、粒子、父对象和销毁 | 缺特效要沿实际创建调用、接收数据和对象生命周期查，不从资源名猜出生帧 | 每个旧职业内置技能的全部 caller、粒子完整物理和图形公式 |
| PO 数据包 | 同词典 `:128–137,217–218`；解压 `GiteeNut注释/09-数据传输.md:9–48,72–99` | 按实例记录 writer/reader 类型、宽度、顺序；各 PO 独立状态、回调、命中账本 | 不能用全局变量或一张 ANI 代替 PO 子程序；不证明联机协议 |
| 时长和动画速度 | `外置知识库/Xiti Fox注释/Xiti Fox字段注释词典.zh-CN.md:4333–4347` 明写 DELAY 1000=1 秒；API 词典 `:68–82,145–148` 列帧/时间/速度/回卷 | 保留 ANI 原始毫秒，播放速度 API、图像缩放和技能说明单位分别消费 | 不能把所有 100 都统一当 1.0，或全局裁掉看起来偏长的帧 |
| 特效脚底错位 | 同 Xiti 词典 `:4392–4402` 的 IMAGE POS 为图像 XY；API 词典 `:81,125,127,143,148–155` 区分对象 XYZ、图像和攻击框缩放 | 保留 IMG 裁剪偏移、ANI 图片偏移、对象局部/世界位置和方向，逐通道合成 | 没有支持“所有特效统一加一个 Z”的证据；地图地砖 120px 调整也不能套给角色/技能 |
| 攻击与视觉 | `knowledge-pack/encyclopedia/pvf-file-types/passiveobject-attackinfo-hitbox.zh-CN.md:60`；API 词典 `:158–195` | ATK 是攻击数据；ANI 框给几何；draw-only 是视觉；direct-hit 另走明确命中入口 | 有碰撞盒不代表造成伤害；视觉缩放不证明攻击范围同时缩放 |
| 命中与受击 | API 词典 `:168–195`；`dictionaries/monster-ai-action-attack-cross-layer-fields.zh-CN.md:40` | 动态 AttackInfo、显式命中列表重置、接受命中后的回调、异常和受击状态应分别消费 | 最终伤害、防御、抗性、卡肉/硬直、浮空力公式和随机受击选择不由文档自动恢复 |
| 装备和技能武器 | `knowledge-pack/indexes/equipment-avatar-motion-fields.zh-CN.md:37,88–95` | 使用 CHR/EQU/LAY 源动作绑定；身体/装备/技能武器层保持独立 | `[expand ani]` 结构不能证明所有装备框均可和身体框合并；当前合并资格仍属试验策略 |
| 怪物 AI/破坏物 | `dictionaries/monster-ai-action-attack-cross-layer-fields.zh-CN.md`；`dictionaries/actionobject-mapobject-breakable-spc-fields.zh-CN.md` | MOB 动作槽→AI→ACT→ANI/ATK/PO；木桶/草树/宝箱需辨认对象家族和地图放置 | 不能把一类哥布林策略当全部 AI，不能给所有破坏物套怪物死亡动画 |
| UI | `dictionaries/client-ui-layout-pos-lay-fields.zh-CN.md:15–59`；回调边界索引 `:29–40` | 现有父子/tab/radio/图片/ANI 可保留；下步补通用 UI ACT 事件、条件、行为和插值 | native CALL/CHECK FUNC、完整业务和“菜单/商城”字体来源仍未补出 |

## 与当前 1031 对照的具体结果

本轮对照的是工程已保全的 1031 解密源码镜像、注册图和目录编译审计，非重新启动原客户端。目录绑定的 PVF SHA256 是 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`；镜像文件本轮重新计算哈希并与自身来源 metadata 核对。本轮未重新导出 PVF，不把旧运行验收当新测试。

### 冰晶坠：缺的是持续回调和 PO 宿主，不是没有特效路径

新包 `knowledge-pack/indexes/skill-atmage-crystalattack-native-chain.zh-CN.md:8,30–53` 给出了检查方向。当前镜像 `content/catalog-v2/source/sqr/character/atmage/crystalattack/crystalattack.nut`：

- `:54–66` 在人物动画帧 `>1` 后设一次 50ms timer；不是把注释掉的 keyframe 分支当实际创建者。
- `:21–51` timer 读取源数组和 SKL，写入 Dword/Float/Word/Word，创建 PO 24221。
- PO 镜像 `po_crystalcore.nut:2–26` 按相同顺序读四项数据，选动画、存攻击倍率、设置角度/速度。`:30–58` 在回调中设置当前攻击信息，动画结束销毁。
- 当前 actor 目录仍报 `sq_SetAnimationSpeedRate`、`onProc`、`onTimeEvent` 等未支持；所以这条链仍是 partial。

可复用成果是类型化数据通道、对象变量、数组、timer、动画实例与 PO 回调能力。这个样本用于验证共同能力，不新增按技能 ID 分派的实现。

### 冰魄剑：不能只播身体 ANI 和 ALS

新包 `indexes/skill-atmage-icesword-state-attackinfo-ex-rewind-chain.zh-CN.md` 与当前镜像 `icesword/ice_sword.nut` 可对照：`:26–61` 切身体/ATK、读速度、设置自定义命中特效并调用元素链；`:72–77` 命中后给目标附颜色层；`:80–162` 按 flag 切攻击信息、写异常，并在 EX/PVP 条件下回卷。当前编译器尚不完整支持数值转换、跨技能源等级、该 callback/helper 和转换/视觉 API。不能用一次动画播放替代上述行为。

### 暗域扩张：范围变化和退出还原同等必要

新包 `indexes/skill-atmage-darkchange-state-blind-attackinfo-chain.zh-CN.md:32–53` 指向的当前镜像 `darkchange/dark_change.nut:52–94` 有 state 参数、分阶段动作和攻击盒缩放；`:121–136` 有退出缩放还原；`:163–178` 有 PVP onAttack 分支。删除不支持的退出回调会造成下一动作范围/状态污染，不能用忽略未知回调提升可执行数量。

## 女枪手反馈能得到哪些线索

`外置知识库/牧野技能注释/职业动静态参数词典.zh-CN.md:27601–27661` 给出 M-3/聚焦喷火器的持续、间隔、拔出和结束时间候选列；聚焦还列出释放时移动速度，时间说明缩放为 `0.001`。这支持区分“原始毫秒”和“说明面板的秒”，并分开处理拔出、持续、结束阶段。

但该词典自身 `:3–11` 标“需验证”，收录多个晚期职业；它没有给出女枪 1031 的完整按住/松开 caller、技能武器/子弹出生坐标和所有特效触发时序。应先核本地 atgunner SKL/CHR/EQU/ANI、ACT/PO 和职业 native 入口，不能直接照抄候选列数或给每个技能补一个模板。枪舞、激光炮、子弹脚底和技能武器层仍需这些实际消费者闭合。

## 已排除的误注和冲突

1. `外置知识库/GiteeNut注释/05-UI绘制.md:198–201` 小标题写“设置动画帧率”，代码却是 `setImageRate`，注释/声明说明图像比例。不能据此改帧时钟。
2. `GiteeNut注释/04-动画系统.md:106–110` 把 `getSitAni` 注为死亡动画。不能据此改 CHR/MOB 的坐下、拾取、倒地、死亡映射。
3. `GiteeNut注释/06-附加对象(Appendage).md:16,28–30` 对第六参分别写“buff/跨图”和“自动附加”，同文冲突。不采用其布尔常量推导跨图清理。
4. `GiteeNut注释/09-数据传输.md:67` 把 state 包第三参命名 `isResetTimer`，而 `03-状态系统.md:63–72` 说明为是否携带数据。回调的 resetTimer 和状态包数据标志不能因同一个参数名就等同，需核实际 writer/reader。
5. `GiteeNut注释/10-攻击系统.md:178–182` 将 force 直注为推开距离/高度，Xiti `hit info` 注释还给出硬直乘法例子。只能保留为社区解释，不能当当前 native 力学/硬直公式。
6. 解压的声明文件标注 Squirrel 3.0.7，这是声明库自身版本。`dnf/squirrel/frontend/tooling` 要隔离，不能将 frontend API、空函数体声明或目录命中当 DNF 1031 已执行事实。
7. 新包的 `action-combat-cross-version-porting` 卡主要讨论拼刀、顶招等额外改造；不是本项目全战斗复刻的既定规则，不据此加入用户未要求的机制。

旧 `pvf-utils-info` 的内部快照冲突不自动传给新包。例如新包 learnability 词典第 59 行将 startSkillCoolTime 标为跨版本候选，不能继续复述旧包“未命中”作为新包内容。

## 现有实现还差什么

当前 `reports/catalog-v2/compiler-audit.json` 的实际统计：54 条注册脚本技能中 **2 executable、52 partial**；其余 1,680 条是依赖预览分类，来源类别含 665 条 missing-native-caller 和 1,015 条 passive。后两类不是“665 个特效缺图”和“1015 个被动已完成”。11 个角色和 1,734 条注册技能记录是源目录覆盖，不等于完整可玩覆盖。

`tools/catalog_pipeline.py:1115–1147` 只接受进入、动画结束、关键帧三类 callback，且使用入口无条件动画/结束转换门。48 条“无入口动画”和42条“无结束转换”是当前编译诊断，许多是前置语法/API失败的派生结果，不证明 PVF 真缺动作。本轮无增减此统计。

`scripts/skill_program.gd` 的通用 IR 已有 timer/input/变量/状态等部分原语；这不代表源编译器已能把真实 NUT 的对象引用、动态数组、helper、循环和全部回调编译进去。`scripts/program_host.gd:220–302` 的 play/attack/spawn 等消费者也不等于完整 Squirrel 宿主。人工 IR 能跑不能替代源程序验证。

补全顺序应按共同能力推进：

1. **源程序和状态通道**：AST/动态表达式、state 入参、对象变量/句柄、helper/有预算的循环，正确区分运行值与编译常量。
2. **持续和退出回调**：onProc/onProcCon/onTimeEvent/onEndState、state generation、输入维持/释放、中断/死亡/换图/脚本故障清理。
3. **PO/AP/视觉实例**：类型化收发包、子程序宿主、源生命周期；draw-only/图层/粒子和伤害分离；原始毫秒、速度、偏移和三个坐标空间。
4. **战斗事务**：动态 AttackInfo/盒、明确 direct-hit、去重/次数/周期、接受命中后的 callback、反应和声音，验证装备攻击框资格。
5. **native 职业入口及 UI ACT**：旧职业内置 caller 按职业恢复；UI 按事件/条件/行为扩展。未知规则保留具体诊断，不用一个技能或窗口成功替代全量完成。

每类能力至少用两种真实源形状或有意义负例验证：包宽度/顺序不匹配、draw-only 不攻击、显式 reset 后复击、同 tick 切状态后的旧 flag、源 timer 与动画结束次序、独立 PO 清理、失效 owner、中断范围还原和 UI 事件锚点。通过自动检查后仍由用户验画面、声音、手感及原版差异。

## 节点产物与恢复

本轮报告及通用缺口矩阵放在 `reports/workbench-311-review/`；节点源码、同一 V3.1 编译产物副本、来源清单和进度文档保存在新的独立 checkpoint，具体见本目录 `NODE-RECEIPT.json`。**旧编译产物备份不代表新技能修复版。** `checkpoints/LATEST.json` 和原 V3.1 入口保持原指向，研究节点另记 `LATEST-REVIEW.json`。

恢复先读本报告、当前任务与研究 checkpoint 的 `PROGRESS.md`/`MANIFEST.json`。继续实现时从通用能力矩阵开始，不能把本轮文档归纳直接提升为全部技能、完整 UI 或最终 beta 验收。
