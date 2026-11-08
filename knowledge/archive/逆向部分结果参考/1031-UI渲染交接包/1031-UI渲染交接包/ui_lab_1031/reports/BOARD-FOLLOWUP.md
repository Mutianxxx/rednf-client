# 1031 board / draw by loop 离线闭合增量

日期：2026-10-18。仅修改外部预览器；不启动客户端、不注入、不修改或重新部署 DLL。已部署 revision 6 保持原哈希。本报告补充此前报告中的 `draw by loop` 缺项，不覆盖或改写 revision 6 的原始几何证据、静态审计及封存会话。

## 完成内容

- 恢复 `[board image]` 的类型注册、配置工厂、实例构造、九图设置、模式和绘制分派，所有实现依据来自固定版磁盘 EXE 与只读快照相同字节。
- `draw by loop` 前两个整数是中间列数、行数，不是像素宽高；允许零列、零行。按原生行优先顺序提交完整图块，无缩放、无余边裁切或补齐。
- 普通 board 改为原生 stretch 公式，不再用各列/行最大尺寸拟合，也不逐格裁剪。负 crop、逻辑透明边距及超出名义控件大小的像素保持独立。
- 导出可选 `view.board_previews[key]`：原始参数、模式、逻辑尺寸、绝对锚点、消费者、证据引用、有序 `draw_ops`、状态或拒绝原因。旧 version1 包无需该字段，仍能按原静态控件和资源重建；实时 `images/clips/draw_ops` 格式不变。
- 缺任意图像、资源歧义、未确认字符串或越界参数不画部分/近似 board。安全限制独立标明，不冒充原生报错；未解码资源记录具体帧号与原因。

实现：[board_layout.py](../tools/board_layout.py)、[preview_layout.py](../tools/preview_layout.py)、[preview.py](../tools/preview.py)。监听器现有“PVF 目录”及引用区域 UI 的“配置预览”自动使用，无需增加游戏侧入口。

## 原生调用契约

证据：[evidence.json](board-followup/evidence.json)，SHA256 `772440b810a2741ae5337780fdc878d765c73b586335c1423014b2bdead61a15`。保留 16 个完整函数或明确标注的工厂片段、各自磁盘 offset/size、二进制文件、哈希、反汇编，以及 31 个 CALL、3 项虚表、2 个字面量和常量。证据身份仍为原固定版 EXE/PVF/快照，不继承其他版本地址。

| 环节 | 已核对规则 |
| --- | --- |
| 注册与工厂 | `[board image]` 字面量 `0182F71C` 注册 ID `223`；两级 switch 到 `010754D6`，分配分支 `01075F03` 写配置虚表 `0182F49C`，虚表 `+4 → 01072820` |
| 配置 | 原生至少 11 整数和 1 字符串；本工具仅支持已确认的恰好 11 整数布局。字符串第 0 项为 IMG，后续识别字面量 `0182F22C → draw by loop`。多余参数/未知选项保留为不支持 |
| 实例 | `01072B8E → 011E98E0` 分配 `2BC` 实例；`+2B8` 指向 `30` 字节私有数据，`+00..20` 为九图、`+24` 为模式、`+28/+2C` 为重复次数 |
| 尺寸 | `01072D4A → 011E99A0` 设置 loop 次数及逻辑尺寸；普通模式 `01072D6D → 011BE370` 直接设像素尺寸。parent/config 坐标经过 `011BEAD0`，预览不再二次叠加 |
| 分派 | 实例虚表 `0185ECBC +24 → 00FD50A0 → +28 → 011EA1D0`；mode 1 调 `011E9C30`，mode 0 调 `011E9E20` |
| loop | `width = W4 * countX + W3 + W5`，`height = H4 * countY + H1 + H7`；横向首段偏移使用 `W3`，纵向使用 `H1`，中间按 `W4/H4` 步进；所有提交为 `011B3950` |
| stretch | `sx = float32((width-W3-W5)/W4)`，`sy = float32((height-H1-H7)/H4)`；内锚点却使用 `x+W0,y+H0`，不能混同边框扣除值。右/下锚点是 `trunc(绝对内锚点 + W4/H4 * sx/sy + 0.5)`；`01562184` 的字节为 `0000003f`，`013D83E0` 为向零截断转换 |
| 提交与空画 | stretch 四角 `011B3950`、五个边/中间 `011B41E0`（零旋转、中心 0、白色）；均行优先。两种模式要求全部九图及非零中心逻辑尺寸；stretch 任一内缩放 ≤0 则整板不画 |

`Wi/Hi` 均指槽位 i 的 unsigned WORD 逻辑尺寸，不是裁剪 PNG 尺寸。crop 是每图局部偏移；本链未创建逐 cell 裁剪。合成图扩展到逻辑矩形与全部真实像素的并集，并保持原绝对锚点，不能把负 crop 裁掉。负世界坐标先参与原生取整，再换算合成局部坐标。

## 验证结果

[79 项专项检查](board-followup/verification.json)通过，另有现有 [49 项集成回归](revision6-verification/verification.json)与 [16 项资源预览回归](preview-verification/verification.json)通过。检查项目包括：

- 对 16 个范围再次逐字节比较磁盘、快照和输出 `.bin`；核对 CALL、虚表、类型 switch、解密字面量、常量及源代码哈希。
- 零/单位/N×M 重复、行优先遮挡、非对称九图、float32、负绝对锚点取整、非等比缩放、负 crop、透明逻辑边及非正缩放整板空画。
- 同资源多实例独立、条件隐藏/恢复、原始配置不变、全图依赖、歧义拒绝、操作/像素分配上界和旧包缺少新增字段的兼容。
- 读取 9 个 UI 中的 10 条真实配置：9 条 loop 和 232×231 的 WindowCommon 213–221 stretch 参照，严格 CP936 token 往返、PVF 成员哈希及 IMG 物理来源全部保留；不重做全资源扫描。

生成 9 张合成图（8 条 loop + 1 条 stretch），每张附原点/尺寸/操作数、物理来源、哈希和诊断差异。示例：[商城颜色面板](board-followup/1-selectavatarcolorwindow.ui.png)、[选择角色底板](board-followup/5-selectcharacterunder.ui.png)、[零中间行面板](board-followup/4-compoundmonstercardresult.ui.png)。已检查商城/选角底板合成图；没有启动客户端或做同帧截图对照，不能据此宣称原生像素验收。

第 9 条 loop（`ui/test/testbutton.ui`，229×183 次数）需要 42,735 次提交，超过外部预览的 16,384 操作限制，明确拒绝而不截断显示；这不是原生规则未知。逻辑及实际像素范围均限制为 4,096×4,096。负次数、额外整数和未知字符串也保持明确拒绝，不猜测原生无效配置的最终行为。

复查命令（工作区根目录）：

```powershell
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031\tools\analyze_board_chain.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031\tools\verify_board.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031\tools\verify_revision6.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031\tools\verify_preview.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031\tools\verify_followup.py
```

## 仍差什么

1. **离线消费者**：变换/D3DX 裁剪、2^32 次级中心、type8/14/15/16、标题/字体、hide/destroy 与地址复用、ANI/ACT/HSP 调度及延迟 packet/GPU 归属。board 的运行时动态 resize 与业务可见性也没有由静态配置推定。
2. **配置业务**：CBT 输入/数字 IMG 映射，EVN 业务条件/点击和通知 ANI，STM stage 坐标/状态列，WDM balloon/switchbox/ACT 和两条缺图的原生路径转换；仍逐项保留原始数据。
3. **实际验收**：revision6 的 60–90 秒功能短测（监听器重开、日志续写、统计边界、停止三项恢复）、退出异常归因，以及另外安排的 ≤5% 受控性能对照；不能在离线环境宣布通过。

完整编号/后续观察点见[未完成清单](1031-未完成清单与补采计划.md)。本轮不新增 DLL hook、不重部署；[revision6 短测步骤](REVISION6.md)仍适用，无需重打副本或逐窗口反馈。

后续[剩余项增量](REMAINING-FOLLOWUP.md)已实现零旋转2^32源图中心，区分源IMG与目的上下文寄存器流，补充按目的类型的替代图像路由、基类删除/门控、数字IMG注册入口及退出dump调用/数据关系；本报告的其他未知项并未因此全部验收。board原生布局规则不变。
