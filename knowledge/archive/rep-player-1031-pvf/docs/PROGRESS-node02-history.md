# 独立 1031 PVF 预览项目进度

更新时间：2026-10-19

## 当前节点

节点 01 已完成：来源边界、PVF ScriptFile 读取入口与 PVP UI/字体目标映射。节点 02a 已完成：十字斩技能效果 ANI、帧事件、PTL 被动对象的静态资源链。节点 02b 已完成：区分角色斩击视觉与被动对象攻击盒，并用 Goblin MOB 核对 damage/down 资源消费者。节点 02c 已完成：记录当前 EXE 的 ANI/ALS 播放合同，并确认 REP Player 尚无 ANI/ALS parser 或 PVF IMG provider。节点 02d 已完成：核对十字斩四个角色效果 ANI 的图集、帧事件、攻击盒和完整 ALS 语料中的关联。完整节点 02 仍在进行，其他技能依赖、受击索引选择和动态渲染均未完成；详见 [SKILL_EFFECT_RENDER_TRACE.md](SKILL_EFFECT_RENDER_TRACE.md)。后续继续建立其余技能的 NUT/ACT/ANI/ALS/ATK 依赖索引，并将录像绘制事件和 PVF/静态资源接入独立预览。

工作区：`D:\dnf-rebuild\rep-player-1031-pvf`。它是原 `rep-player` 的独立副本；没有接入或修改 `dnf-native-demo`，原始客户端/PVF只读。

## 已完成

- 原 REP 播放链已整理到 [REP_PLAYER_CALL_CHAIN.md](REP_PLAYER_CALL_CHAIN.md)，区分录像事件重放与 PVF 连招输入脚本。
- 新增 `src/pvf.hpp` / `src/pvf.cpp`：读取 PVF 头、解密目录树、保留重复路径候选、按成员读取并校验 CRC32、计算 PVF/成员 SHA-256、读取 stringtable 并解析 token5 ScriptFile。
- 新增 `src/pvf_validate.cpp` 和构建目标 `build/rep_pvf.exe`：索引 PVF `.rep`、审计连招脚本或输出单个成员的原始有序 token 证据；该入口不经过 REP 录像解码器。
- 连招分析保留成员原始路径字节、文件号、绝对偏移、原始尺寸、CRC、SHA-256、token 序号/偏移/类型/原值/解析值。
- 当前 1031 PVF 的全部 484 个 `.rep` 成员均可按 token5 ScriptFile 解析：`etc/pvppracticecombo/replay/` 为 `476/476`，`etc/linksystem/striker/` 为 `8/8`，合计 0 个拒绝、`1,817` 条 `[skill key]` 记录。后 8 个成员的独立原始 token 报告保存在 `validation/linksystem-striker/`。
- 新增 [PVP_UI_AND_FONT_SCOPE.md](PVP_UI_AND_FONT_SCOPE.md)：86JP `Replay/PVP/PracticeCombo` 的 `751/751` 个录像通过完整协议解码；确认其中的 PVP UI 是录像时间线里的 IMG/文字绘制指令，不是独立 UI 树。用户指定的“菜单”“商城”作为单独字体复刻测试字样纳入后续目标。
- 对 54 个代表 `01.rep` 扫描到 723 条文字绘制引用；样本包含韩文角色/训练提示和数值，没有发现“菜单”“商城”或其英译。这两词是用户指定的字形目标，不作为现有录像已包含这两个标签的证据。
- 节点 02b 补全技能特效引用依据：`common.nut` 注册 Slash ANI，状态 35 附加 ANI 并消费帧事件，控制器再加载 PTL 生成被动对象；`gorecross.obj` 关联对象 ANI/ATK，实际攻击盒来自对象 ANI 而非角色 Slash2 的可见斩击。增加 Goblin MOB 的 damage1/damage2/down/sit ANI 对照；原生受击索引选择仍未知。
- 节点 02c 记录 native ANI/ALS 合同：实例独立时钟、百分比速率、附层按时间取子帧、跨帧事件和 graphic-effect 证据边界；确认现有播放器没有 ANI/ALS parser 或 PVF IMG source provider，技能预览器尚未实现。
- 节点 02d 为四个 GoreCross 角色效果 slot 记录了 ANI 成员哈希、IMG 图集、帧数、时长、帧事件和攻击盒情况；扫描完整 ALS corpus 未找到对应成员或显式引用，但不排除技能控制器单独创建的被动对象。

## 验收状态

- 自动构建：`build/rep_pvf.exe` 已编译，SHA-256 `c649767f03d641b8ceea551e3583343a351345cba7ddb505f8d4813640bcd7bf`。
- PVF ScriptFile 审计：484/484 token5 成功，0 拒绝，共 1,817 条 `[skill key]` 记录；PVF SHA-256 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`。`combo67.rep` 成员 SHA-256 为 `40b37bea3e9427f11a528a7b7ad40eb3a3bab7a3700f4d6630e0b47ec20193b0`，其中有 4 条记录。
- 86JP PVP 录像审计：751/751 成功，0 错误；REP 1.0 为656条、REP 1.1为95条，全部 minor 0。使用的现成 `rep_validate.exe` 仅用于只读分析，没有作为本独立项目的运行时依赖。
- 独立 GUI/D3D 预览：未实现。
- PVP UI 资源到当前 1031 PVF/静态资源的逐帧映射：未实现；目前只有 86JP 时间线和资源路径证据。
- 字体来源核验：1031 `Gasinamu.ttf`、`msjh.ttf` 与 86JP `Gasinamu.ttf`、`GasinamuNew.ttf` 的 SHA-256 已记入 [PVP_UI_AND_FONT_SCOPE.md](PVP_UI_AND_FONT_SCOPE.md)。现有 `fontPath` 未查找这些名称，当前会回退到系统 Tahoma；“菜单”“商城”作为独立字形复刻目标，原版调用参数和像素效果仍待后续验证。
- NUT 技能调用链：未完成。需要将每个技能控制器、NUT 宿主函数和 ACT/ANI/ATK 消费者逐项关联。
- 攻击判定与怪物响应：未完成。当前既有静态证据只闭合几何接触及 HP 写入端点；接触至攻击接受/伤害中间链仍有缺口。
- 技能特效代表追踪：十字斩技能64/状态35已完成当前 PVF 与 EXE 的静态来源串接，并确认视觉 Slash ANI 与对象攻击盒分属两条链；Goblin 的 MOB 动作资源和原生 damage/down getter 已对应。未完成全部角色技能覆盖、怪物受击索引选择器闭合、动态画面核验或预览器接入。
- 渲染实现基础：已找到 1031 ANI/ALS 通用静态合同；rep-player 现有 IMG decoder 面向 NPK，PVF 读取器仅提供原始成员/ScriptFile。将 ANI/ALS 和 PVF-backed IMG provider 接入播放器仍未实现。
- 用户画面/声音/手感测试：待用户。原版动态对照：待用户及后续证据。

## 运行方式

构建后在工程根目录运行：

```powershell
.\build\rep_pvf.exe --pvf 'D:\dnf-rebuild\DNF1031客户端\Script.pvf' --audit-combos --output .\validation\pvf-combos.json
.\build\rep_pvf.exe --pvf 'D:\dnf-rebuild\DNF1031客户端\Script.pvf' --combo 'etc/pvppracticecombo/replay/swordman/combo67.rep'
```

如暂停后恢复，先阅读本文件、[REP_PLAYER_CALL_CHAIN.md](REP_PLAYER_CALL_CHAIN.md)、[SKILL_EFFECT_RENDER_TRACE.md](SKILL_EFFECT_RENDER_TRACE.md) 与 [PVP_UI_AND_FONT_SCOPE.md](PVP_UI_AND_FONT_SCOPE.md)，核对 PVF、86JP DNF.exe、样本 REP 与字体 SHA-256。节点 02 接着扩展到其他技能的 NUT/ACT/ANI/ALS/ATK 依赖索引并填充每技能证据矩阵；同时导出 REP 场景绘制事件，映射 1031 PVF/静态资源，并验证用户指定的“菜单”“商城”字形。

## 节点备份

节点 01 检查点：`D:\dnf-rebuild\rep-player-1031-pvf-checkpoints\node-01-20261019-061329`。该目录包含独立项目完整副本、根目录进度文档和逐文件 SHA-256 清单；保留已生成的 `rep_pvf.exe` 与 PVF/PVP 验证报告。没有生成的 GUI 预览不会写成已备份产物。

节点 02a（技能特效静态追踪）检查点：`D:\dnf-rebuild\rep-player-1031-pvf-checkpoints\node-02a-20261019-skill-effect-render`。包含更新后的完整独立项目、`build/rep_pvf.exe` 和逐文件 SHA-256 清单。本子节点只新增分析文档，没有 C++ 改动或重编译；EXE 沿用节点 01 哈希 `c649767f03d641b8ceea551e3583343a351345cba7ddb505f8d4813640bcd7bf`。GUI 技能预览尚未生成。完整节点 02 的其他职业/技能依赖索引继续进行。

节点 02b（视觉特效与怪物受击资源补全）检查点：`D:\dnf-rebuild\rep-player-1031-pvf-checkpoints\node-02b-20261019-monster-hit-effect-render`。包含本次完整独立项目副本、当前 `build/rep_pvf.exe`、进度文档和逐文件 SHA-256 清单。本节点只新增静态分析文档，没有 C++ 改动或重编译；EXE 沿用哈希 `c649767f03d641b8ceea551e3583343a351345cba7ddb505f8d4813640bcd7bf`。GUI/原版动态效果尚未生成或验证；节点 02 继续进行。

节点 02c（ANI/ALS 播放合同与实现差距）检查点：`D:\dnf-rebuild\rep-player-1031-pvf-checkpoints\node-02c-20261019-animation-render-contract`。包含本次完整独立项目副本、当前 `build/rep_pvf.exe`、进度文档和逐文件 SHA-256 清单。本节点仅补充静态分析文档，没有 C++ 改动或重编译；EXE 沿用哈希 `c649767f03d641b8ceea551e3583343a351345cba7ddb505f8d4813640bcd7bf`。尚未生成 PVF 技能画面或 GUI demo。

节点 02d（GoreCross 效果 ANI/ALS 依赖审计）检查点：`D:\dnf-rebuild\rep-player-1031-pvf-checkpoints\node-02d-20261019-gorecross-ani-als`。包含本次完整独立项目副本、当前 `build/rep_pvf.exe`、进度文档和逐文件 SHA-256 清单。本节点只新增静态证据摘要，没有 C++ 改动或重编译；EXE 哈希仍为 `c649767f03d641b8ceea551e3583343a351345cba7ddb505f8d4813640bcd7bf`。
