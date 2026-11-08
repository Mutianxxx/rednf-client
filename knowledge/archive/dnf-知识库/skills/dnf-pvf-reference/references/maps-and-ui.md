# MAP / TIL / UI

本文件引用的路径均相对官方样例目录；行号来自原字节按指定编码解码后的 `splitlines()`。表中为中文释义。

## 地图原点、层和视差

| 来源 | 样例明确说明 | 对实现的约束或尚未定义部分 |
| --- | --- | --- |
| `mapsample.map:35` | 扩展到 800×600 后，`[background pos]` 使原先背景绘制位置向上移动指定数值，通常为 80。 | 只说明“向上移动”；没有完整相机/世界/屏幕变换公式。不得把单个 80 或推测出的 120 全局应用到全部层。 |
| `mapsample.map:11` | `[sort bottom] 1` 启用普通层以外其他层的排序；其他值不使用。 | 保留该开关；注释没有给出具体排序比较器。 |
| `mapsample.map:40` | 基础 `[tile]` 画在近景层。 | 与远景、背景动画的前后关系一起核对；不能只按贴图透明像素判断地面。 |
| `mapsample.map:47`–`58` | 扩展地砖贴在主地砖下方；每行数目等于 `[tile]` 数量，剩余项排到下一行。 | 保留原列表和排布，不能把所有扩展项横向铺开。此样例没有给出每块像素尺寸。 |
| `mapsample.map:62`–`65` | 远/中/近景滚动速度为相对地砖滚动速度的百分比，默认 100；100 同速，0 不滚动。 | 不能统一相机倍率或把百分比误作绝对速度。 |
| `mapsample.map:67`–`80` | 背景动画默认从 (0,0) 自动重复；可选六类层。`below` 在同层动画及物件之前，`upper` 在之后；`close + below` 在地砖之前。`loop y axis=1` 向下重复；`screen pos` 是屏幕坐标的起点。 | 保留 layer、order、loop Y、screen pos；从实际资源逻辑宽度核对水平重复步长，不能一律硬编码 640。 |
| `mapsample.map:120`–`129` | 动画记录为路径、layer、x/y/z；物件记录为ID、x/y/z。 | 原 z 不能默默丢弃；实体高度和深度另行解释。 |
| `mapsample.map:201`–`204` | NPC 示例为ID、left/right、x/y。 | 当前客户端若有额外 z，应保留版本差异，不能从此四项示例断言所有版本无 z。 |
| `passiveobjectsample.obj:6`–`7` | 层名可为 close/normal/bottom/closeback/middleback/distantback；layer level 越高越靠前、越低越被其他对象遮挡。 | 层内 level 与世界坐标都要保留。六类层的完整数值映射不是此注释给出的。 |

定位错位时分别记录：源 MAP 坐标、ANI 局部位移、IMG 裁剪/逻辑尺寸、实体 z、镜头变换、视差、UI 视口。一次只验证一个环节；在已知参考尺寸下比对原客户端与实际运行截图，合成预览另标。

## 可走区域、入口和音频

- `mapsample.map:83`–`91`：城镇跳转矩形为 x/y/宽/高/城镇ID/区域ID；目标 `-1 -1` 表示地下城起始。虚拟可走矩形取各矩形的并集，不能把列表压成一个包围矩形。
- `mapsample.map:98`–`111`：通道坐标顺序左、右、上、下；地下城开始区域为矩形；固定玩家出生点包括 x/y/z。
- `mapsample.map:113`–`118`：opening BGM 可指定播放时长，之后主 BGM；sound 列表是进入地图时输出的声音标签。这里没有完整混音优先级或淡入淡出规则。
- `mapsample.map:228`–`232`：该版本加载图说明为 800×640，frame1背景、frame0正文，按1→0绘制；缺frame1只画正文。这不是所有 UI 的画布尺寸。

## TIL 碰撞

`tilesample.til:3`–`7`：可有重复 `[IMAGE]`，每项为 IMG 路径和帧号；类型 basic / extended，默认 basic。`pass type`：0全部可通行、1仅浮空类型可通行、2全部不可通行；basic 为14列×30行，extended 为14列×10行。

样例只给网格数，未给通用像素步长；必须以当前资源的逻辑尺寸、裁剪和地图实例核对。不能把14×30都视为16像素格，也不能丢掉重复 IMAGE。

## UI 控件与 UI 动作

- `dungeonselect_uisample.ui:7`–`17` / `22`–`34`：`[ui controls]` 可以重复，包含类型、唯一控件名、x/y、字符串计数及内容、整数计数及内容、可选 `[common action]`。整数参数含义随控件类型变化，不是统一固定数组。
- `dungeonselect_uisample.ui:68`–`85`：balloon 控件坐标、图案、地下城ID和动作引用；名字不能重复。`103`–`125`：switchbox 有一般/悬停/按下/禁用状态帧。不要从普通image控件推断所有控件布局。
- `uiactionsample.act:2`–`42`：TRIGGER 根据帧、时间、鼠标和控件条件执行 BEHAVIOR；LIMIT=0无限。ON TIMING 的起止相同为单时点，第二项 -1 为按周期；时间起点可为 SET ACTION / START MAP / ENTER MOUSE / LEAVE MOUSE / SET VISIBLE。
- `uiactionsample.act:45`–`70`：移动/缩放/旋转/alpha插值具有持续时间；同类型插值在一个BEHAVIOR内按声明顺序执行。`FIRST ARG=-1` 在样例说明的对应分量取当前值，不能无限推广到其他字段。
- `uiactionsample.act:72`–`85`：图形效果 NONE/DODGE/LINEARDODGE，触发计数重置、控件重置、动画rewind、对象跟踪偏移、RETURN结束动作、变换中心（默认中心）。
- `manual for adding ui action system.doc` 第4节说明 `[common action]` 绑定动作，第5节解释控件TRIGGER/BEHAVIOR。提取正文只保留文本、没有截图和原页码；手册并未定义 HUD 的具体像素布局。

UI ACT 与怪物/物件 ACT 共享部分标签名称但对象系统不同。解析或实现前先确定上下文，不能把两者合并为一张无作用域字典。
