# 60US 普通鬼斩：身体、ATK 与生成特效

分析对象为 `DFO_fixed_v3.exe`，SHA256 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`。
这是磁盘字节与 Capstone 静态证据，尚无原客户端运行画面对照，不是原 C++ 源码。

## 有条件的执行范围

本合同仅覆盖 Swordman 技能 5 在未学习蓄力被动（技能 6 等级为 0）时请求 state 20、substate 0 的分支。
技能命令和 pending-state 请求证据见 `../combat_skill_dispatch/`；状态提交仍由该处追查。
状态 20 的其他 substate 及蓄力路径不能使用这个预览冒充完整实现。

`0x731FA9→0x731FAD→0x731FB6` 选择 CHR etc motion[1] 并安装身体 ANI；
`0x731FBE→0x731FC2→0x731FCA` 选择 etc attack info[0] 并安装 ATK。
CHR 的保序、空槽和运行期布局证据见 `../combat_native_skill_slots/`。

## 特效生成与绘制参数

`0x7326F0..0x7327EB` 中，substate 0 或 2 使用 `0x472A60` 构造两个动画：

| 层编号 | 原生字符串 VA | 相对当前角色根路径 | 创建结果保存位置 |
|---|---|---|---|
| 1 | `0xD7F6C0` | `Effect/Animation/HardAttack1.ani` | `this+0x2EFC` |
| 2 | `0xD7F678` | `Effect/Animation/HardAttack2.ani` | `this+0x2F00` |

`0x732791..0x7327BF` 取技能 5 static data[0]，乘以 `0xCC10AC` 的 float32 0.01，
通过 `0xA25900` **覆盖**特效各帧 IMAGE RATE 的两个分量。当前 dungeon 值是 100，结果为 1。
SKL 原注释明确这只扩大特效，实际范围不扩大，不能把此数值乘进攻击盒。

`0x7327C8..0x7327DD` 调用虚表 `+0xF8`，10 个参数依次为
`(1或2, ANI, 40, 0, 0, 0, 0, 0, 0, 1)`。
`0x4ACF80→0x49B7B0` 将它们写入独立绘制层链表 `this+0x10C`，按层编号递增插入。
node `+0x08` 是编号，`+0x0C` 是 ANI，`+0x10/+0x14` 是坐标偏移。
插入后 `0x49B84E→0xA27360` 重置计时，再 `0x49B857→0xA27F60` 刷新帧。

绘制消费者 `0x49A359..0x49A3DB` 先画负编号层，再画身体；
`0x49A5B7..0x49A62F` 画剩余非负编号层。
该处明确将 node+0x10 加到或减离 actor screen X，把 node+0x14 加到 screen Y，
然后调用 `0xA26990`；因此这里的 40 是跟随方向的 X 偏移，不是帧号或绘制层号。
两个鬼斩特效顺序为身体之后的 layer 1、layer 2，原点为角色 X+40、Y+0（朝右时）。
身体装备子 ANI 的内部排序是另一套链表，不能与此层链表混淆。

最后参数为真时 wrapper 还按角色运行期播放速率调用 `0xA29C70`。
预览在基准速率 1 下重建公共时间轴；角色属性/装备的最终速度计算尚未移植。
LINEARDODGE 等实际渲染混合仍需继续核对，不能把浏览器普通 alpha 当原生等效结果。

## 几何与后续命中

身体与两张特效 ANI 均没有 ATTACK BOX。攻击范围来自装备层，见装备合同。
技能 ATK 是 magic、dark element、weapon damage apply=1、damage reaction=down，
push aside=300、lift up=300。这里没有把这些字段简化成完整伤害或击飞公式。
几何、命中接受、消息接收、HP 链见 `../combat_native_collision/`。

复验：`python -X utf8 analysis/combat_hardattack/build_evidence.py`。
