# 60US：CHR 有序槽至运行时 ANI/ATK 消费链

结论来自当前 `DFO_fixed_v3.exe` 静态字节，SHA256
`a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`。
PVF 为 `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98`。
没有运行原游戏，没有将重建项目的类布局当作当前 EXE 证据。

## 已闭合的数据链

`0x88b2d0` 从 `0x82f790` 打开 CHR 文本，并由 `0x8307e0` 读取标签。
当标签为 UTF16 `[etc motion]`（`0xe1e88c`）时，`0x88c13f` 比较后清空
CHR 对象 `+0xbbc` 的字符串指针容器，调用 `0x8304e0` 按脚本顺序读字符串，
经 `0x403be0` 逐条追加。该容器的 begin/end 位于 CHR `+0xbc0/+0xbc4`。
`[etc attack info]`（`0xe233ec`）由 `0x88c241` 识别，采用相同模式收集至
CHR `+0xbe4`，begin/end 为 `+0xbe8/+0xbec`。

角色资源物化函数 `0x4da140` 先通过 `0xb7ce30` 获取解析对象。
`0x4db255` 至 `0x4db406` 遍历 CHR `+0xbc0..+0xbc4`，按原序创建 ANI
实例并追加到运行时 `this+0x1274` 容器，其 begin/end 为 `+0x1278/+0x127c`，
元素宽 4 字节。原串为空时跳转 `0x4db39c`，**追加 NULL 并保持槽索引**。
非空路径拼接使用 CHR `+0xc04` 的目录字符串，并由 `0x472b80` 构建实例。

`0x4db594` 至 `0x4db674` 按原序读取 CHR `+0xbe8..+0xbec`。
每个非空路径经 `0xb7d230` 获取 ATK 后，通过 `0x4a3630` 追加到运行时
`this+0x444`。容器 begin/end 为 `+0x448/+0x44c`，每个 ATK 元素
**0x1b8 字节**。空串分支 `0x4db633` 创建默认 ATK 记录并追加，仍保持索引。

## Getter 与虚方法绑定

MSVC RTTI `CNSwordman` 的 TypeDescriptor 位于 `0xf6740c`，
COL 为 `0xebb354`，vtable 为 `0xd80f94`；构造函数 `0x7469b0`
在 `0x7469e8` 将 vtable 写入对象。原先给出的 `0xf67410` 位于描述符内部，
不是 TypeDescriptor 起始地址。

| vtable 槽 | 当前 EXE 目标 | 字节行为 |
|---|---|---|
| `+0x38c` | `0x4d3ce0` | 检查 index `< (end-begin)/4`，读取 `this+0x1278 + index*4`；先调用装备附层钩子 `0x4b4a80(type=0x13)`，再返回 ANI |
| `+0xf0` | `0x4b4da0` | 再调用附层钩子，之后 `0x49b250` 将当前 ANI 指针写入 `this+0x104`，并应用播放速率 |
| `+0x198` | `0x746c30` | 调用 `0x4cf680` 处理 ATK，随后清除 `this+0x2b5f` |

直接 getter `0x5270f0(index)` 检查 `this+0x448..+0x44c` 的元素数，
再调用 `0x527090` 返回 `begin + index*0x1b8`；越界返回 NULL。
`0x4cf680` 对 ATK 部分字段作运行期规范化后，进入 `0x4afa10` →
`0x4edcd0`，将记录复制至当前攻击对象 `this+0x260`，并通知相关附层。
因此 `+0x198` 的含义有直接安装 ATK 字节链支撑，不再只是“可能设置ATK”。

## 实际 Swordman 槽值与选择点

来自当前 `character/swordman/swordman.chr` 的原 token：

| 字段 | 零基索引 | 资源 | 解密脚本字节 offset |
|---|---:|---|---:|
| etc motion | 0 | Animation/Guard.ani | 7326 |
| etc motion | 1 | Animation/HardAttack.ani | 7349 |
| etc motion | 17 | Animation/HardAttackChargeAfter.ani | 7825 |
| etc attack info | 0 | AttackInfo/HardAttack.atk | 10780 |
| etc attack info | 20 | AttackInfo/HardAttackChargeAfter.atk | 11399 |

`0x731fa9` 压入 motion 索引 1，`0x731fad` 调用 `+0x38c`，
`0x731fb6` 调用 `+0xf0` 安装；`0x731fbe` 压入 ATK 索引 0，
`0x731fc2` 调用 `0x5270f0`，`0x731fca` 调用 `+0x198` 安装。
因此这个分支是 **motion[1] / ATK[0]**，不能混为同一槽号。

另一个控制器分支在 `0x73219f` 选择 motion[17]，`0x7321b7` 选择 ATK[20]。
这证明存在 ChargeAfter 分支，不能将整个技能所有状态简化成 1/0。
本子任务不声明已完成条件输入、状态转换、时间事件或全技能调用恢复。

## 装备附层边界

`0x4b4a80` 在 type `0x13` 下按身体 ANI 查 motion index，然后遍历
`this+0x14ec` 的前 10 个装备附层。它从装备资源帧容器取同一 motion index，
对延迟加载占位 ANI，先由 `0xa24dc0` 查现有绑定和排序键，调用
**`0xa277c0` 移除旧附层**，再由 **`0x4b2650` 创建真实 ANI**。
之后 `0xa29d70` 依原排序键重新挂接，`0x4ccdb0` 将身体帧 delay 复制至附层。
旧版笔记将 `0xa277c0` 写成“取/构造 ANI”有误；本段已按字节链纠正。

普通 HardAttack 已补出一个明确 EQU → LAY → 同 motion[1] 的实例，
见 `hardattack-equipment-contract.json` 及 `equipment-contract.md`。
`n_club_axshauta.equ` 的两层按键值绘制为身体、650/clubb、2600/clubc，
图片模板 `[variation] 2 6` 格式化为 `club0206b.img`、`club0206c.img`。
clubc 的 frame 3/4/5/6 各有一个攻击框；clubb 和身体均无攻击框。
没有为身体补框，没有把任意同名武器配对作为证据。

装备 ANI 挂入的正是身体 ANI `+0x180` 链表、节点 `+0xc`；
该容器由碰撞分支 `0x4aef80` 按序访问，因此装备绑定与主线恢复的几何接触消费链
可以直接衔接。坐标变换与 AABB 的另支证据见
`../combat_native_collision/geometry-contract.json`，命中接受仍需独立恢复。

完整 RVA、文件 offset、片段 SHA256、原始 `.bin` 和反汇编 `.asm`
见 `evidence-index.json`；供主程序使用的来源与槽位数据见 `slot-contract.json`。
复现 `python -X utf8 analysis/combat_native_skill_slots/build_evidence.py`。
装备实例复现 `python -X utf8 analysis/combat_native_skill_slots/build_equipment_contract.py`。
