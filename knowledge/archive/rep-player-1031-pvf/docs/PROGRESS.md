# 1031 PVF 独立预览进度 · R60-03

状态：**automated pass / user pending**。[R60-03-VERIFICATION.json](../../reverse-60us/integration/R60-03-VERIFICATION.json) 已绑定最终 `candidate-r60-03-final2`、EXE及报告身份，播放器 EXE SHA256 为 `d87406f0b25fa7a1cc303816ba9df71aa6025f68a4905ba46016ff2c91df69f3`。实际D3D读回72项、隐藏UI78帧、四来源流程184项、十角色模板24104项／1677条源记录、clock adapter20项均通过；共享合同46个原生输出／157项与ALS24项通过。主工程R4的正式 `cache/r60-03-tests-final-r4-checked` 另有1541项clock检查及九职业完整待机往返通过，完整核心／音频也通过。入口、备份和用户步骤统一见 [R60-03-PROGRESS.md](../../reverse-60us/integration/R60-03-PROGRESS.md)。用户画面、听音、手感及原版动态比较待执行，历史R60-02与节点05仍只对应各自原身份。

播放器新增独立时钟下拉：“来源 delay / 旧 ratio 时钟”（默认，`source-delay-rate100`）与“60US percent deadlines → 1031（推断）”（`inferred60us-percent-deadlines`）。渲染下拉的 `inferred60us1031`／`legacy1031` 可另行选择。共享 Cursor 使用60Hz整数毫秒，source age 与 ratio、deadline百分速率各在选定路径转换一次；播放倍率只改变墙钟提交。渲染 tween 使用实际 frame/local/span，离散图片和框取源帧。暂停不推进，右箭头单步提交一个16／17ms tick，拖动按所选政策确定性重建。

主轨、ALS、怪物反应与命中特效均有实际 clock 消费者；ALS 按父帧期限处理 add/remove，子实例保留自己的延时。两政策分别计算几何接触时间。重定出生时刻或速率时复制私有 clock binding，避免污染共享场景；该修复后的最终D3D清单为72项，包含新增的共享绑定隔离检查。独立 clock 合同20项及候选D3D、隐藏UI、四来源流程和十角色模板结果均由上述统一清单绑定，未借用旧候选通过记录。

配方阶段／位移时刻、接触出生位置仍是来源时间和几何夹具推断；尚无完整装备层生成器。原生命中接受、伤害、完整技能调度及1031对60US算法的原生等价性仍未证实。现有十角色模板与临时普攻回退分类保持，未迁入主World为专用技能控制器；资源存在、可播和完整技能实现分别记录。用户画面、听音、手感及原版动态对照待执行，十个非缔造者职业的最终要求不变。

# 历史 1031 PVF 独立预览进度 · R60-02

2026-10-20新候选：`Start-R60-02.cmd`；隔离EXE SHA256 `5ce28085505260006a2d5664920e681109b6d7818ac74ceccaac8540ea647ea7`。R60-01/02实施和验证完成，新增共享采样/矩阵/RGBA/混合、可切策略和模板原图标。48项D3D、78帧隐藏GUI、184四流程、24104模板回归通过；跨版本原生确认、用户画面/听音/手感待完成。详细实现、备份和下一R60-03恢复点见 [统一节点进度](../../reverse-60us/integration/R60-02-PROGRESS.md)。以下节点05记录保留为历史，旧EXE和备份未覆盖。

# 历史进度 · 节点 05

> 2026-10-20新增接入任务：用户已要求读取独立 [60US逆向交接](../../reverse-60us/README.md)，按 [R60接入计划](../../reverse-60us/PORTING_PLAN.md) 先审查并补通用渲染、名称与时间轴，伤害后置。该授权允许直接开展审查和隔离候选；下文节点05“等待模板体验/主线暂停”保留为历史，不阻止上述新工作。本次未改本工程代码和EXE，1031版本、模板推断与原生证据边界不变。

最新用户顺序：先完成十角色通用模板套用，编译独立预览供用户看效果，再逐角色专用适配。项目为 `D:\dnf-rebuild\rep-player-1031-pvf`，尚未迁移至 `dnf-native-demo`。主项目 P01–P19 保持此前暂停记录；原客户端、原始 rep-player 及历史备份保留。节点04进度另存 `docs/PROGRESS-node04.md`。

## 实际实现

双击项目根 `Start-1031.cmd`。默认“十角色模板体验（推断 / 含回退）”，第二个下拉框按职业筛选，文本框按技能名、ID或策略名称筛选。全部源技能列表行保留，包括被动、内部、重复记录和NotApplicable；缔造者仅延期本次运行时条目，原始资料不删除。

新增 `pvf_template_preview.cpp` 从当前PVF读取职业总表、技能总表、对应CHR/技能列表/SKL。人物动作优先同名，再按阶段后缀组合；无法绑定时使用本角色自己的临时普攻，显著标识回退。共享流程包括有限人物阶段、源FLAG与攻击框、ALS附层、特效/对象实例、独立时钟、返站及清理。定位和重播查询不可变场景，不累积重复实例。

人物和返站来自所选角色自身CHR，AT/DS分区保持来源隔离。补充OBJ/effect按自身分区同族候选推断，仅选择有限主候选，保存歧义。没有已恢复控制器时，实例零偏移、静止轨迹、一轮ANI寿命、FLAG/首攻击框/动作结束触发明确是模板策略。被动展示不伪造主动攻击实体。

每个模板的结构化 `templateBinding` 包含角色/技能ID、CHR/SKL/action/idle路径、policy和fallback。界面及导出显示绑定与 `native_controller_verified=false`，保存来源原bytes、hash、偏移和依赖。部分候选失败显示具体路径，不以“有画面”宣称完整。

原十字斩、魔法旋风、冰魄剑、魔法冰球在“来源技能流程（已接入四项）”中保持节点04流程。原49组注册效果检查、1388条CHR动作记录和全ANI浏览仍保留。

## 构建与自动验证

EXE：`build/rep_pvf_preview.exe`，SHA256 `a10b6fad96bb334610820dbe4895ff830c29f8d39a4889267eae618d36a8f1c4`。最终构建日志与manifest：`tools/dependency-build/preview-20261019-171245-507-43732/`。`validation/node05-build-identity.json` 已逐项核对构建输入与当前源码一致。

PVF SHA256：`d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`。模板每次按所选PVF重新匹配，该hash不代表其他版本原生行为已经验证。

- 整合构建通过，新增模块C++20检查零警告。
- 最终EXE主预览42/42通过：`validation/latest-preview.json`。
- 四来源流程184/184通过：`validation/latest-skill-flows.json`。
- 最终EXE隐藏界面78帧通过，包括默认模板、十角色筛选及实际选择、四来源流程、接触开关、定位、步进、朝向：`validation/ui-check-node05-final.json`。
- 十角色全量模板审计结果见本文末尾最终记录，不能把源记录数当完整技能数。

全量入口 `tools/verify-template-flows.ps1` 从当前源码独立编译，逐行检查源表multiset、场景实际加载、自身CHR动作、原bytes、ALS附层、事件、有限边界、返站、清理及纯查询；代表场景验证左右渲染和body/effect/object像素消费者。首次脚本遇到PowerShell5默认中文路径编码问题，已加UTF8 BOM修正，失败记录保留。

## 用户预览步骤

1. 关闭旧窗口，双击 `Start-1031.cmd`，等待加载完成。默认模板模式，职业下拉应有十角色。
2. 选择职业，再选列表中的“同名动作推断”或“阶段动作推断”；可搜索这两个词减少回退条目。切职业前清空搜索词；无结果时状态栏说明仍显示上次场景。
3. 开关身体、技能特效、被动对象；切左右、拖时间条，检查人物、附层、独立实例、返站和结束。右侧列出绑定与缺口。
4. “临时普攻回退”或“被动展示/普攻回退”用于检查共用流程，不表示对应技能已适配。
5. 切“来源技能流程（已接入四项）”比较原四项。接触受击开关仍为几何测试策略，未恢复原版命中接受与伤害。
6. “导出来源 / 反馈”后提供职业、技能名/ID、时间点及差异。报告在 `validation/runtime/<会话>/`。

## 边界、下一步与恢复

本节点目标是模板执行链和可运行预览。名字/路径绑定仍是推断，分支/循环只走有限观察周期，部分技能只能普攻回退；不计全职业技能或v0.1 beta完成。装备/武器、音效、资格/MP/CD、伤害/被动数值、怪物反应因果、完整Squirrel、精确混合和原生ALS时钟仍待专用适配。PVP UI及“菜单”“商城”字体继续在最终目标内。

用户画面/声音/手感验收、原版动态对照均待执行。先由用户查看，再逐角色适配，未经确认不迁移主项目。细节见 `docs/template-preview-bindings.md` 和 `docs/skill-playback-next-evidence.md`。

`tools/checkpoint-preview.ps1 -Node node-05-cross-character-templates` 新建完整备份，位置写入 `validation/latest-checkpoint.json`。备份根包含PROGRESS、CHECKPOINT和逐文件SHA256；`source/`是完整项目根，里面的Start-1031.cmd可启动。历史节点不覆盖。恢复先读根agent.md、CURRENT_TASK、本文件及模板绑定文档，再核对身份并启动。

## 最终覆盖记录

全量审计 **24104/24104通过**，实际运行99.39秒；来源1677行与模板1677行multiset一致，十角色均有自身动作和返站可播，无加载异常。64个代表场景、左右128组画面比较通过；有图对象验证sprite像素，无图逻辑对象验证零sprite及来源判定框像素，所有实例保留有限生命周期。来源缔造者57行仍保留在Archive，未混入本次十角色模板。

| 模板策略 | 数量 | 含义 |
| --- | ---: | --- |
| exact-motion | 171 | 自身CHR同名动作，仍属绑定推断 |
| phase-motion | 107 | 自身CHR阶段动作，单轮组合策略 |
| fallback-basic | 431 | 临时普攻回退，不代表该技能表现 |
| passive-basic | 968 | 源被动条目的动作展示，未执行被动加成 |

117条模板展开ALS，143条保留源事件。1667条请求资源完整，另10条部分资源或机制缺口，人物模板仍可播；这些条目不计视觉完整：

| 角色/技能 | 具体缺口 |
| --- | --- |
| 鬼剑士86 极·鬼剑术(暴风式) | 武器图像含未支持的 `%02d` 装备模板 |
| 女格斗家63 末日风暴 | `Character/Fighter/Effect/Typhoon/gt_fail.img`缺失 |
| 圣职者26 圣愈之风 | `Character/Priest/Effect/HealWind/d-back.img`缺失 |
| 圣职者106 朱雀符 | ALS重复uniqueName `con`绑定歧义 |
| 女神枪手101 炽焰劫击 | ALS `draw-only-random` 未执行 |
| 暗夜使者75 陨落螺旋刺 | ALS特殊z-layer sentinel未执行 |
| 男格斗家41 烈焰焚步、105 天崩地裂、106 螺旋滑铲 | ALS特殊z-layer sentinel等未执行 |
| 男魔法师3 冰晶坠 | ALS特殊z-layer sentinel未执行 |

擒月炎/猛毒擒月炎的Fire/DarkExplosion基本ANI、男格斗家抛沙的对象ANI无IMG、有攻击框，已显式标为不可视逻辑对象。其框的左右像素检查通过；擒月炎PTL可视粒子未执行，仍列gap，不算爆炸特效完成。首轮六项像素失败及修正依据全部保留。

最终全量报告：`validation/template-flows-20261019-171245-972-b4286b40/template-flow-audit-1792401189451-0/report.json`；路径及hash见 `validation/latest-template-flows.json`。最终EXE主42项、GUI78帧已重跑通过；原四流程184项回归通过。本节点下一步由用户查看模板效果，再逐角色专用适配。
