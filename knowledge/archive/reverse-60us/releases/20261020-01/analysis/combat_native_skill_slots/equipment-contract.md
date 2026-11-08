# 60US ordinary HardAttack：装备同动作附层与播放合同

本报告只使用当前 EXE/PVF 的静态字节和已通过 CRC 的解密脚本。EXE/PVF
SHA256 与 `README.md`、`hardattack-equipment-contract.json` 一致。
所有地址均为当前 x86 ImageBase 0x400000 下的 VA；原代码片段、文件偏移、
片段 SHA256 在 `evidence-index.json`。函数名为分析标签，不是原始符号。

## 可复验的武器选择

`equipment/character/swordman/weapon/club/n_club_axshauta.equ` 的 SHA256：
`54a3bda415f2a5f202290887c90adae9d8aa64816f3ee22cc9b0e4f24039d8c4`。
其原始声明是 `[variation] 2 6`，随后按以下原顺序出现两层：

| 原序 | `[layer variation]` 数字 | 字符串 | include |
|---|---:|---|---|
| 0 | 2600 | `clubc` | `equipment/character/swordman.lay` |
| 1 | 650 | `clubb` | `equipment/character/swordman.lay` |

这两个 tag 的解密字节 offset 分别为 868、946。include 是当前 EQU 的显式声明，
不能把文件名相似当成 include。原 CP949 字节与 UTF8 阅读副本均保存在本目录。

LAY SHA256 为 `c52092f1c4990844da35030102b96fe98ca82cefa3e3ed0aa6f646a035ff312f`。
其 `[LAYER] 0` 在 `[layer variation]` 非零数字存在时被数字覆盖。
该 LAY 有 **97** 个有序 `[etc motion]` 字符串；索引 1 的字符串为
`%s/HardAttack.ani`，token 解密字节 offset 为 770。索引 17 则为
`%s/HardAttackChargeAfter.ani`，这里只实现普通分支。

`0x866600..0x866735` 读取 layer variation 的数字和字符串；`0x8666a7..`
在 override 非零时仍消费 `[LAYER]` 的数字，但将 override 数字写入 layer key。
`0x8679d5..0x867b85` 读取 `[etc motion]` 字符串，并把 layer variation 字符串
作为宽字符格式化参数传给 `0xc0227f`。格式化后的字符串按原序追加，未排序槽号。
同一装备目录加格式化相对路径产生以下两个已存在资源：

| 排序键 | ANI | 图片模板 |
|---:|---|---|
| 2600 | `equipment/character/swordman/weapon/club/clubc/hardattack.ani` | `Character/Swordman/Equipment/Weapon/club/club%02d%02dc.img` |
| 650 | `equipment/character/swordman/weapon/club/clubb/hardattack.ani` | `Character/Swordman/Equipment/Weapon/club/club%02d%02db.img` |

## 图片模板的整数参数顺序

EQU `[variation]` 的两个整数在 `0x867cea..0x867d45` 被读取：普通分支写解析
记录 `+0x10/+0x14`，另一分支写 `+0x34/+0x38`，保留读取顺序。
`0x4b2650` 的延迟加载记录每项 0x40 字节，记录首两个整数直接作为
`0x472b80` 的前两参数。该构造器在 `0x472c74..0x472c8d` 把它们按序转交
`0xa29ad0` 最后两参数，后者交给 `0xa60940` → `0xa60810`。

`0xa608af..0xa608c4` 的实际 push 顺序是 second、first、imageTemplate、512、buffer，
随后调用 varargs 宽字符格式化包装 `0x401df0`。这个顺序对应
`format(buffer, 512, imageTemplate, first, second)`，故当前 `[variation] 2 6`
得到 `club0206c.img` 与 `club0206b.img`。文本 ANI `[IMAGE]` 的即时加载路径
同样在 `0xa28ff2..0xa29004` 将第二、第一整数压栈后调用 `0xa52aa0`。
本结果来自调用参数；没有从 `%02d` 文件名模板反猜参数。

## 同 motion 绑定和排序

普通 HardAttack 选身体 motion[1] 和 ATK[0] 的地址见主 README。
`0x4d3ce0` 与 `0x4b4da0` 都调用 `0x4b4a80(type=0x13)`，后者先在身体
motion table `+0x38..+0x3c` 查同一个 ANI 的槽号，type 0x13 遍历装备槽 0..9。

装备每个 layer record 的宽度是 0x8c，首 dword 是排序键，`+4` 开始是 motion table。
`0x455dd0`（装备 virtual+0x138）在 `equipment+0x7a0` 非空时返回 override vector，
否则返回 `equipment+0x758` 原 layer vector。不要把有效层和原层永久合并为一个结构。

CNSwordman vtable+0x3bc 的指针位于 0xd81350，目标为 `0x4b8690`。
`0x4b82dd..0x4b82f9` 读 layerRecord[0] 为 key，连同 bodyMotionTable 与
layerRecord+4 交给这个方法。它在 `0x4b8a00..0x4b8a20` 对身体与装备
motion table 的 `+0x38[index]` 使用同一索引，调用 `0xa29d70(bodyANI,key,childANI)`。

`0xa29d70` 将子 ANI 挂入 bodyANI+0x180 的双向链表；节点+8 为排序键、
节点+0xc 为子 ANI。遍历时使用有符号比较，遇到 existingKey > newKey 则插前；
相等 key 放到已有相等项之后。子 ANI+0x188 被写为 bodyANI。

`0xa26220` 在 `0xa26244..0xa26249` 先递归绘制负 key 节点，然后于 0xa26309
绘制身体当前帧，随后在 0xa26320..0xa263ca 依链表顺序绘制剩余非负 key。
所以本 EQU 的实际绘制次序为 **body → 650/clubb → 2600/clubc**。
原声明顺序仍保留在输出合同中，不能将绘制排序反写为脚本顺序。

## 延迟加载与时间同步

`0x4af8d0` 识别“恰好一帧且该帧 +8/+0xc 都为 0xffff”的延迟加载占位。
`0x4b4a80` 先用 `0xa24dc0` 从 bodyANI+0x180 中找到旧节点并保存 key，
由 `0xa277c0` 将旧节点摘除并清旧 child+0x188，再调用 `0x4b2650` 创建真实 ANI，
最后按保存的 key 调用 `0xa29d70` 和 `0x4ccdb0`。
**`0xa277c0` 是摘除，不是构造器；构造器路径由 `0x4b2650` 发起。**

ANI keyframe stride 为 0x7c。`[DELAY]` 先映射为本地 tag id 13，再在
`0xa29308` 读取整数，通过 `0x455c10` 存到 frame+0x30。
`0x4ccdb0` 遍历 `min(bodyFrameCount, childFrameCount)`，将身体 frame+0x30
的逻辑值复制给子 ANI 同索引 frame+0x30，处理了包装值相对地址的存储差异。
预览应复制解码后的 delay 数值，不能直接复制原 EXE 的保护存储整数。

`0xa29d70` 设置 child+0x188 后调用 `0xa27360` 重置播放状态，并将身体+0x134
播放速率传给 `0xa29c70(child,rate)`。后续 `0xa29c70` 对 child list 递归传播速率。
`0xa27dc0` 的帧推进在 child+0x188 非空时调用 `0x4caa00(parent)`，
该函数递归走+0x188直到根 ANI 并读取根+0x8c 时间，因此不是每层独立起钟。
`0xa27870` 安装当前帧并由 delay / speed 更新下一帧时刻，current index 位于 ANI+0x124。
据此可实现：共用根时钟、同序 delay、继承播放速率，每个子层保留自己的帧图像及框。

## 攻击框来源和覆盖分支

解析器的当前文本 tag 表把 `[ATTACK BOX]` 映射为本地 id 16；switch[16]
指向 `0xa294aa`，读取六个脚本整数转 float 后，最终在 0xa2957f 将 frame+0x38
交给 `0x65ccc0` 追加。`[DAMAGE BOX]` 是 id 15 → 0xa293c8 → frame+0x48。
每个框 0x30 字节，由六个 8 字节 float 包装值组成。

当前身体 HardAttack.ani 和两个技能特效 HardAttack1/2.ani 都没有 ATTACK BOX。
当前武器同名 HardAttack.ani 有 33 份，其中 13 份带框、20 份无框；扫描的完整
来源与原框保存在 `weapon-hardattack-boxes.json`。本 EQU 的 clubc 框为：

| frame | 原始六值 |
|---:|---|
| 3 | `26 -30 8 171 60 133` |
| 4 | `54 -25 8 141 50 123` |
| 5 | `43 -20 8 151 40 111` |
| 6 | `41 -15 8 154 30 82` |

clubb 无框。不要给身体补一个猜测框，也不要将 clubc 的框套用到所有武器。

另有条件性的装备覆盖/时装分支：`0x4acd30` 会按 equipment+0x790 的目标槽和
+0x794 优先级选择替代来源，设置+0x78c/+0x78d，以及有效 vector override+0x7a0。
`0x4b4ce0..0x4b4d88` 的第二轮检查这些标志及+0x798，满足条件才进入
`0x4b4960` → `0x456770(destEffectiveVector,sourceOriginalVector,motionIndex)`。
它先经 `0x4ae9a0` → `0xa27690` 清 dest[0] 所选 ANI 各帧攻击框，然后经
`0x4aeb90` → `0xa27500` 按同帧追加 source 每一层的攻击框，帧数取最小值。
这是 override 的合并路径，**不能无条件对同一组普通武器层执行“清第一层再合并”**。
普通未覆盖装备保留原 clubc/clubb 的资源框即可展示；完整替代装备场景需恢复这些 gate。

## 与几何接触消费者衔接

装备附层挂接的 bodyANI+0x180 / node+0xc 正是另支 `0x4aef80` 的子 ANI 遍历容器。
它先检查 primary ANI 接触，再按该链表访问攻击方子 ANI，对目标当前 ANI 调用
`0x4e9b10` → `0xa244e0`。原 ANI 中身体无攻击框并不会阻止子 ANI 被检查。
详见 `../combat_native_collision/geometry-contract.json`；该报告还恢复了镜像、
XYZ 平移和 AABB 边界语义。本报告不重复声明坐标或把几何接触等同命中接受。

本分支闭合普通武器同 motion 绑定、图片格式化、层排序、共享时间及攻击框来源。
仍未证明命中资格、重复命中计数、伤害公式、怪物状态转换，也没有原游戏运行截图验收。
技能目录的全职业 controller/命中覆盖保持 unknown。
