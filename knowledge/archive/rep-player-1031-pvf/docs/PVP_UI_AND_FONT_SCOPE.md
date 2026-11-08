# 86JP PVP UI 与字体目标映射

更新时间：2026-10-19

## 目标

最终独立预览纳入 86JP `Replay/PVP` 可观察到的非文字界面绘制逻辑：资源与帧选择、绘制顺序、位置、图层、混合、裁剪和时间变化。用户另指定“菜单”“商城”两个文字作为字体复刻的验收样本；其他文字暂不作为目标。

这项工作只扩展 `rep-player-1031-pvf` 的研究与独立预览范围，不接入 `dnf-native-demo`。PVP REP 用于理解表现层与渲染命令；当前清风 1031 PVF 的 `.rep` 是练习输入脚本，不是同协议录像。

## 来源身份与批量验证

86JP 客户端根：`D:\game\DNF1031客户端-20260708\DNF\DNF`

- `DNF.exe` SHA-256：`1f8244d3f7309bbe2fde4299e1863a894f6b28d5707bf01732980585b20b00dd`
- `Script.pvf` SHA-256：`1cd52a54358738dbfea309f15ee861386f0b32e30f59e58fb4c41d73b911314a`
- PVP 样本：`Replay\PVP\PracticeCombo\Swordman\0\01.rep`
- 样本长度：28,478 bytes
- 样本 SHA-256：`8c25b8d7554bdfe6ff8a78580c585cba3ddcc1ee56b1da0cc252e4ff24851b51`
- REP 校验器 SHA-256：`9aa2a4adb097da13e06e15c07d9ed849ab7333a540d0be8fecc5e755b4af6bd9`

`Replay\PVP\PracticeCombo` 共 751 个 REP 文件、95,577,966 bytes，分布在 13 个职业目录。使用只读校验器及 CP949 字符集对 751 项完整解码：REP 1.0 为 656 项，REP 1.1 为 95 项，全部 minor 0，零错误。校验器来自现有只读分析缓存，不成为本项目运行时依赖。

代表样本为 REP 1.0、800×600、render mode 0，266 个场景、63,463 次命令引用、1,479 个字典命令，时间戳至 4,692 ms。其 opcode 计数：IMG draw 3 为 53,336；文字 draw 5 为 2,385；批量 draw 10 为 101；混合 push/pop 0/1 各 17,960；裁剪 2 为 5,482；音频 6/7 分别 21/2,058。计数来自该条样本，不推广为所有录像的命令合同。

另对 54 个 `01.rep` 代表文件运行完整 dump，统计到 723 条文字绘制引用和 76 种不同文字资源。它们包含韩文角色名、训练提示、频道/延迟数值等；未发现“菜单”“商城”及其英文对应词。这个结果只限定于代表样本，不代表整个 PVP 目录不存在其他文字。

## PVP 绘制证据

REP 时间线中没有独立 UI 节点或专属 UI opcode。录像记录的 IMG 绘制指令与地图、角色和特效指令共用同一条有序命令流；文字另走字体指令。渲染时序为：

```text
REP header / command dictionary / resource strings
    -> timestamped scene + command IDs + auxiliary coordinates
    -> ordered opcode dispatch
    -> IMG resource + frame + position/layer + blend/clip/effect state
    -> text resource + font parameters -> glyph rasterizer/atlas -> draw
    -> D3D render target and presentation
```

代表样本的字典里，以下 PVP/HUD 资源具有绘制模板。模板计数来自解压后的命令字典，不能代替时间线上的实际出现频率：

| 资源路径 | 字典模板数 | 用途判断 |
| --- | ---: | --- |
| `Sprite/Interface/PVP.img` | 2 | PvP 界面 |
| `Sprite/interface2/HUD/HUD.img` | 175 | 通用 HUD |
| `Sprite/Interface/SkillBuyWindow.img` | 18 | 技能购买窗口 |
| `Sprite/Interface/keyshortcut.img` | 18 | 快捷键提示 |
| `Sprite/Interface2/PVP/PVP_Tournament02/pvp_tournament02.img` | 9 | PvP 赛事界面 |
| `Sprite/Interface2/PvP02/PvpRank_Icon/PvPRank_Icon.img` | 1 | PvP 段位图标 |
| `Sprite/Interface2/UI/SkillShop/SkillShop.img` | 1 | 技能商城界面 |
| `Sprite/Interface2/pvp/pvp_practice/PVP_Combo.img` | 24 | 连招练习界面 |
| `Sprite/Interface2/pvp/pvp_practice/PVP_Practice_New.img` | 1 | 连招练习界面 |
| `Sprite/Interface2/PvP/pvp_practice/PvP_practice.img` | 11 | 连招练习界面 |

其他 opcode 3 还绘制地图、角色、武器和特效；仅靠 opcode 分类无法把 UI 与世界对象分离。实现映射时必须保留源路径、帧号、重复绘制、绘制顺序、位置坐标、层、混合/裁剪和有效时间，不可把一次录像中的帧序列写死为普遍 UI 状态机。

## 字体样本边界

`src/protocol.cpp` 解码旧格式 opcode 5 与较新格式 opcode 48 的文字指令。`src/engine.cpp` 在场景预处理阶段根据资源表文字和字体参数生成字形，再在实际指令顺序处绘制；opcode 5/48 的位置也可能来自场景 auxiliary 坐标流。`src/fonts.cpp` 根据字体类型、字号、粗细、字间距、颜色、描边和样式生成 glyph，并放进 atlas。字形来源读取所选客户端的 `Fonts` 目录。

代表 `Swordman\0\01.rep` 中的文本按 CP949 解码为韩文；未经指定代码页的默认解码会产生乱码。这是明确的格式/来源问题，不是 PVF 或 REP 时间线损坏。目标文字“菜单”和“商城”应以 Unicode 简体中文 glyph 输入到独立字形验证，不得将其当作 CP949 录像原文。

已核对的客户端字体文件：

| 客户端 | 字体 | SHA-256 |
| --- | --- | --- |
| 清风 1031：`D:\dnf-rebuild\DNF1031客户端\Fonts` | `Gasinamu.ttf` | `75a428a924ee8c1f469b136138b5004ace21e1f5243119ec2ae26cd34f158c4d` |
| 清风 1031：`D:\dnf-rebuild\DNF1031客户端\Fonts` | `msjh.ttf` | `3e2d44b01c9a248a61bedae4f15c8aae501328b1f7adfe6e111a5da5aa5c5104` |
| 86JP：`D:\game\DNF1031客户端-20260708\DNF\DNF\Fonts` | `Gasinamu.ttf` | `75a428a924ee8c1f469b136138b5004ace21e1f5243119ec2ae26cd34f158c4d` |
| 86JP：`D:\game\DNF1031客户端-20260708\DNF\DNF\Fonts` | `GasinamuNew.ttf` | `2f6d3cd7369b273a06ede4a945cb40c366c444785f34a52b9cfb7c6c1a884a4f` |

`src/fonts.cpp` 当前查找 `DNFForgedBlade`、`NotoSansSC`、`NotoSansCJKsc`、`gulim.ttc` 和 `tahoma.ttf`，没有显式查找 `msjh.ttf` 或 `Gasinamu*.ttf`。已检查的两个 `Fonts` 目录均不含上述候选文件，因此现有解析会落到 Windows 系统 Tahoma；这不是“菜单”“商城”原版字形已复刻的证据。后续字形验证需先将来源字体选择与 Unicode 简体中文目标正确关联，再确认字号、字重、基线、字距、描边/颜色和像素效果。

验收拆成两项：

- 字形：分别渲染“菜单”“商城”，作为用户明确指定的字体复刻目标；保留实际来源字体、字号/粗细、基线、advance、描边/颜色和实际像素。字体文件身份已记录，但原版 UI 的字体调用、字号和样式参数尚未确认。
- 界面渲染：能从来源绘制命令恢复界面图片、帧、坐标、图层、裁剪/混合及顺序，并在 1031 资源侧验证每项映射；此节点尚未做逐帧 1031 资源映射或用户画面对照。

## 调用链定位

- `src/protocol.cpp`：REP header、命令字典、资源表和时间线解析；opcode 3/4 图像、opcode 5/48 文字载荷。
- `src/engine.cpp`：按场景顺序派发图像/文字绘制、相机、图层、裁剪、混合和特效。
- `src/fonts.cpp`：字体参数解释、字形定位和 atlas 生成。
- `src/resources.cpp`：从所选客户端 NPK 取 IMG/帧资源。
- `src/gpu.cpp`：纹理上传、D3D 渲染和目标提交。

这些调用关系证明 REP Player 如何重放已记录的界面表现，不证明菜单/商城业务行为、鼠标/按键交互、技能释放或怪物攻击因果。相关原生技能链结论仍见 [REP_PLAYER_CALL_CHAIN.md](REP_PLAYER_CALL_CHAIN.md)。

## 复现与下一步

在工程目录运行 PVF 连招审计：

```powershell
.\build\rep_pvf.exe --pvf 'D:\dnf-rebuild\DNF1031客户端\Script.pvf' --audit-combos --output .\validation\pvf-combos.json
```

86JP PVP 批量验证由独立分析工具完成，完整结果见本节点备份的 `validation\pvp-audit.jsonl`；代表字典 dump 见 `validation\pvp-swordman-01-dump.json`。下一节点建立 PVF/静态资源的 UI 资源存在性映射，补时间线绘制命令导出，再在独立 GUI/D3D 预览中逐项验证字体和 PVP 界面；不把录像协议直接替换为 PVF 动作语义。
