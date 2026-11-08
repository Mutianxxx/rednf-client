# 1031 PVF 预览修复与剩余缺项

本轮修复的是外部资源预览器。它从 1031 PVF 和 NPK 读取资源，不执行客户端业务函数。候选图像不等于原生窗口已完整复刻。

## revision 6 增量

[本轮交付报告](REVISION6.md)及[几何证据](geometry-revision6/evidence.json)记录新增范围与限制。`011B4710`已确认为目标对象成员写入，DLL补记目标ECX和图像请求时上下文，不建立推测全局裁剪栈。`draw_ops`保持图片/矩形顺序与实例代次；type7且新消费者核验通过的单位变换软件分支使用每次请求自身的屏幕矩形。`011BF510`显式恢复800×600，不伪装成恢复父裁剪。

新增负crop、逻辑中心哨兵、负旋转后屏幕轴非等比缩放、颜色转换，以及避免实时父坐标重复累加。变换/D3DX裁剪、次级中心哨兵、type8/14/15/16仍列出原因，不用近似公式补齐；revision6发布时保留的draw by loop缺项已由下述离线增量闭合。旧包缺新状态时按原能力展示，标记未知。

“配置预览”已接入8 CBT、1 EVN、26 WDM、1 STM，支持原生组号/单条记录/district与手动分支/高亮；区域UI和Common.ui实例独立。配置总览不等于运行可见状态；数字IMG映射、状态列和两条未定位地图IMG明确缺项。六类诊断摘要显示在界面，详细证据和物理来源进入version1离线包，资源歧义不自动择优。

[49项增量回归](revision6-verification/verification.json)覆盖配置、精确矩阵、像素裁剪/遮挡、实例独立、旧数据与GUI入口；新增CBT/EVN/STM/WDM合成图和离线包。既有16项资源回归继续覆盖背包、选择与结果图，报告增加物理来源及相对上次诊断摘要差异，见[验证输出](preview-verification/verification.json)。合成图检查不计作客户端同帧对照通过。以下表格保留此前修复依据。

## 已定位并修复

### 剩余项定向增量

[新报告](REMAINING-FOLLOWUP.md)实现零旋转2^32中心：虚函数ECX是源IMG，不是包装器入口的目的上下文，取已有图像逻辑尺寸的整数半值；非零旋转超界仍拒绝。`draw_ops`仅可选补充从同请求payload `+8`恢复的目的`context_type`，旧`images/clips/source_event`不改。简单入口按目的type8/14/15/16的`011DB180→011DADE0`报告surface/格式缺项；不按源`image_type`误分派，不套用到变换入口，不冒充新增像素支持。原revision6未知列表为历史状态，以增量报告说明当前支持范围。

### board 后续增量

[原生契约与本轮报告](BOARD-FOLLOWUP.md)恢复 `01072820 → 011EA1D0 → 011E9C30/011E9E20`，16段磁盘/快照代码及31个CALL一致。loop前两整数是重复次数（可为0），按原生行优先提交，不当作像素尺寸、不裁余边。普通stretch使用侧边尺寸计算缩放、左上角尺寸计算内锚点，保留float32和绝对坐标下的向零取整；不再用最大列宽/行高或逐格裁剪。

可选 `board_previews` 保留原始字段、逐实例状态、有序操作和证据；缺图/歧义拒绝部分合成，负crop和越出名义控件矩形的像素保留。79项专项检查、10条真实配置及9张合成图见[验证](board-followup/verification.json)，其中测试UI的42,735次提交因16,384操作安全上限明确拒绝。旧version1包仍兼容；没有修改DLL或进行客户端画面对照。

| 原因 | 本轮处理 | 复查依据 |
| --- | --- | --- |
| 所有图片控件都用首个整数当帧号 | 按类型分派；未知类型单独列出，不再画一个猜测帧 | `tools/preview.py`、`preview_layout.py` |
| board image 的宽高被当帧号 | 读取宽、高、九个帧号，按 3×3 合成；保留逻辑透明边距 | 实际 WindowCommon.img 213–221，232×231 背景 |
| radiobutton 的数量被当帧号 | 读取数量、每项四个状态帧和 x/y、末尾初始选择 | inventory_item.ui 的两项数据；本地选择为候选状态 |
| 切换帧只换 PNG，沿用旧裁剪偏移 | `setOffset(crop_x,crop_y)`、`setPos(logical_x,logical_y)`；状态切换同时更新 offset | 不同 crop 的几何回归 |
| 裁剪偏移放到世界坐标后再变换 | 将裁剪置于局部坐标，使其参与缩放/旋转 | 2× 缩放下固定逻辑锚点检查 |
| 相同子 UI 多次加载时 key 重合 | 为每条子 UI 加载边生成实例命名空间 | 重复 child.ui 的独立 key 与条件检查 |
| 父坐标、父条件可能重复继承 | 父锚点去重；保留 tab/radio/page 条件和递归诊断 | 合成嵌套控件几何检查 |
| Qt 文本额外引入 4 像素 margin | 文档 margin 设为 0；直接字符串保留宽度和 RGB 候选 | margin 与位置检查 |
| animation 控件全部跳过 | 资源 helper 复用 1031 ANI 解码器；外部时钟播放、重播及显式循环 | 真实 UI/BloodDungeon/ExpFX.ani、时间边界/插值检查 |
| 明确写出的 LINEARDODGE 图片按普通 alpha 绘制 | 按该字符串启用 Qt 加法合成近似；仍保留原生 shader 差异 | blooddungeon/result.ui 的 Exp BG |
| 预览切换时嵌入控件销毁发出状态变化 | 清空 scene 前屏蔽控件信号，避免销毁回调访问半清空场景 | 重复重建库存页签，原生/离线检查通过 |
| 未支持控件直接消失 | `preview_diagnostics` 给出名称、类型、原因；可勾选虚线定位 | 未知类型和真实窗口缺项报告 |

九宫格的实际资源元数据：213–218 的角/边/中心按 3×3 顺序排列；219–221 的像素高为 12、逻辑高为 13。合成时底部定位使用逻辑高 13，不能把裁剪掉的透明行也压掉。`draw by loop` 已按后续原生证据实现；静态默认配置仍不等于原生运行可见状态。

ANI 输出每帧的 duration、image/frame、x/y、scale、radians、RGBA、flip、blend、原始 properties 和未知属性。缺失属性按全局值/默认值重置；插值仅作用于位置、缩放、角度和 RGBA，图片/帧号/混合模式不插值。Qt 的加法混合用于预览；完整 DODGE shader、部分效果 RGB 和其他专用属性仍未验收。窗口 ACT、初始可见性和播放触发不由外部计时器代替。

## 仍会造成不完整或差异的因素

1. 根窗口 `[tile type]`、`[size]`、标题栏及边框由客户端专用代码生成；不能把 size 中的格子数当像素。原始字段现保存在 `instances[].window_fields`。
2. 原生数值字符串 ID 未建立完整字典；不会拿 PVF stringtable 的相同数字冒充客户端文字。Qt 字体、文字对齐枚举和真实字形仍有差异。
3. pattern image、grid、gauge、numberset、time、tree、switchbox、balloon、专用窗口等尚未全部恢复。未知 schema 会显示原因，原始参数保留。
4. `.ui` 的默认资源还会被 UI ACT、客户端代码、数据列表及游戏状态修改。将资源候选同时画出可能与实际可见状态不同；应由 DLL 的真实控件遍历和图像请求校准。
5. 裁剪与嵌套变换、延迟 GPU 提交、材质/字体和专用 shader 尚未全部串通。外部候选可以帮助定位缺项，不能标为所有窗口均已复刻。

`[control]`、`[control group]` 是非绘制锚点；`[tooltips]` 是悬停元数据，不把它们当作永久缺失的背景图。

## 操作与验证

监听器工具栏新增“重播 ANI”“循环预览 ANI”“标出未解析控件”。选择“PVF 目录”后，详情的 `preview_diagnostics` 包含未支持控件、资源失败、待解码资源及播放范围说明。“独立本地交互”只改变外部副本。

运行 `D:/ProgramData/anaconda3/python.exe -X utf8 -B ui_lab_1031/tools/verify_preview.py` 可重新做几何及实际资源检查。报告位于 `preview-verification/verification.json`；示例图为 `board-corrected.png`、`boosterselectpass.png`、`iteminventorywindow.png`、`result.png`。图像来自资源合成，已人工查看，未与同场景客户端截图做精确对照。

原生补丁/管道/资源/离线集成检查见 `verification.json`，通知策略及 Windows 投递检查见 `notification-verification.json`。HAL/NULLREF 测试宿主不可用、实际通知是否被 Windows 展示、真实客户端窗口布局和性能基线均保留为单独验收项。
