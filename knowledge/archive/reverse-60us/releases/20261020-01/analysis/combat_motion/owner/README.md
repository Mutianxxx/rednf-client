# 60US 普通 owner 的位置碰撞回调

当前 Swordman 的 `virtual+A8`、`virtual+AC`、`virtual+274` 已从虚表追到实际函数，并恢复了普通 owner 路径中的 Z 门、活动状态包装、首个阻挡对象、包围框、层与地形格判定。这里分析的是**移动位置能否通过以及碰撞通知**；这些函数不能直接充当攻击命中、伤害、受击或死亡合同。

依据为当前 `DFO/DFO_fixed_v3.exe`，SHA256：`a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`。本目录未采用 `dnf-rebuild` 的猜测。所有生成与修改均限制在本目录；上层 `motion_model.py` 和 `motion-contract.json` 保持原有范围，尤其 `M+78` 外部运动控制器仍未闭合。

[owner-contract.json](owner-contract.json) 提供机器可读合同，[evidence.json](evidence.json) 记录 30 段原字节、文件偏移、SHA256、Swordman 虚表槽、三个跳表、RTTI 描述与八份 REA 伪代码来源。`.bin` 是客户端原字节，`.asm` 是 Capstone 输出，REA 伪代码只作为辅助证据。`class mask`、活动状态槽 `16`、`scalar21c` 和格子数值保留数值身份；尚未确认的名称没有补成业务含义。

| Swordman 虚表槽 | 当前目标 | 职责 |
|---|---|---|
| `+A8` | `4AC100` | 只检查有符号整数 `z >= 0`，没有地图、层或活动状态门 |
| `+AC` | `4B00F0` | appendage / 活动状态包装，通过后委托 `4E7DD0` |
| `+244` | `4EB600` | 两对象是否构成位置阻挡，调用包围框与类型分支 |
| `+248` | `4E81D0` | XY 包围框相交，边缘接触也算相交，不检查 Z |
| `+274` | `4B97B0` | 依次转发附件碰撞通知，再按实时输入门决定是否探测绕障 |

`4B00F0` 的活动状态提前返回需要保留一个容易误读的指针细节。包装先将 `retainedCast` 设空；若 actor `+184` 字节为真且 `virtual+3C4()` 返回 appendage list，就顺序遍历其 `[+4,+8)` vector。只有条目 `+4` 的 owner 指针等于当前 actor 时，才做 `IRDAppendage → CNThrowWebPullAppendage` RTTI 转换，并将结果覆盖到 `retainedCast`。非空转换结果的 `virtual+60()` 为真时停止扫描。

成功转换但 `virtual+60()` 为假的指针仍然保留；后续同 owner 的失败转换才会将它清空，其他 owner 条目不会清空它。因此不能将此逻辑简化成“是否存在 active web-pull”。扫描后，若 `owner.virtual+410(16)` 为真且最终指针为空，包装直接返回 `owner.virtual+230()==5`；否则委托位置探测。当前 `+410=4AC020` 读取 `actor[0x1294+index*4]` 并调用非空对象的 `virtual+8()`，槽 `16` 的具体语义名称仍未确认；当前 `+230=744C30` 返回 protected `actor+155C` 原生状态。三段斩 state `22` 在这个提前返回条件下会被拒绝。提前返回既不清空也不填写调用方的 `out` 指针。

`4E7DD0` 才在入口清空非空 `out`。没有 `actor+100` manager 时直接允许；否则保存当前 provider 的 float32 xyz，取 `virtual+9C()` 的整数 z，再经 `virtual+88(x,y,z) → 499050 → 510F50` 临时写入候选位置，关闭 `M+7C` 后查询 `50B240`。若返回 blocker，转换为 `CNRDPassiveObject` 成功且其 `virtual+33C()` 数据 `+8==0` 时允许，并跳过地形；其他 blocker 拒绝，并通过 `out` 返回。只有没有 blocker 且 `manager+114` 与 `[manager+114]+50` 均非空时，才调用 `485950` 地形回退。

探测结束恢复原 provider float xyz，随后**强制 `M+7C=1`**，不会恢复进入前的字节。候选位置 setter `510F50` 会置 `M+8C=1`，恢复位置绕过该 setter，所以此标志也保留。这个探测不能作为无副作用的纯函数处理。这些已导出的函数体没有直接清零速度、加速度、倒计时，也没有直接写 HP 或原生状态；多态 getter / setter 与后续附件回调的其他效果仍是边界。`owner_model.py` 没有假装完整实现 `4E7DD0` 的临时写回过程。

`50B240` 首先要求 actor 按指针身份存在于 manager `[+10,+14)` 注册 vector，且 `actor.virtual+1FC()` 或 `virtual+200()` 至少一个非零；随后顺序遍历 `[+90,+94)` 候选 vector，跳过自己，返回第一个使 `actor.virtual+244(other)` 为真的对象。候选表如何构造、刷新和排序，以及实际场景内容尚未追到。

`4EB600` 的共同前置条件是至少一方满足 class mask `0x21`、双方各自的 `virtual+1FC/+200` 都非零，并且 XY 包围框相交。当前 Swordman 的宽高来自 protected `actor+20C/+214`，边界为 `left=x-trunc(width/2)`、`right=left+width`，Y 同理。层来自 `actor+498`；`virtual+204/+208` 均读取 `actor+21C`，本目录称其为 `scalar21c`，没有将它等同于当前 Z。

只在各对象自身满足 mask `0x21` 的分支，才把它的 `virtual+33C()` 返回值解释为带 `+8` 类型的结构：

| `data+8` | self 满足 mask 的分支 | other 满足 mask 的分支 |
|---|---|---|
| `1` | self 的 `virtual+208<=0` 时阻挡 | 当前 owner 的 `virtual+204<=0` 时阻挡 |
| `2` | other 不在 self `[+4D4,+4D8)` ignore vector 时阻挡 | owner 不在 other 的 ignore vector 时阻挡 |
| `3` / `4` | 双方 `virtual+1C4` 层不同时阻挡 | 双方层不同时阻挡 |
| 其他 | 本分支不阻挡 | 本分支不阻挡 |

ignore vector 只比较指针身份。Swordman 自身的 `virtual+33C=4AD690` **不是通用 passive data pointer getter**；不能把 Swordman 虚表直接用于合成 mask `0x21` 对象并按上述数据结构解引用。原生验证使用显式构造的 fixture 虚表。

地形检查 `485950` 的 context 是 `[manager+114]+50`。只有 owner 满足 mask `0x11`、mask `0x81`，或同时满足 mask `0x21` 且 `data+1D` 字节非零时，才先要求中心位于 `0<=x<baseColumnRecords*224`、`0<=y<baseRows*12+extensionRowBlocks*120`。随后宽高都零直接允许。若 context `[+174,+178)` 矩形 vector 非空，则只要求中心属于任意一个半开矩形 `x0<=x<x0+w && y0<=y<y0+h`，并跳过格子。

无矩形时，footprint 采样区间为 `max(0,trunc(left/16))..min(trunc(right/16),columns-1)` 与 `max(0,trunc(top/12))..min(trunc(bottom/12),rows-1)`，**都包含端点**，x 外层、y 内层。这里的 `16×12` 是原生坐标单位，未赋予像素或米的解释。

| 格子整数值 | 允许条件 |
|---|---|
| `1` | owner `virtual+208>0` |
| `2` | 拒绝 |
| `3` | owner 层为 `0` |
| `4` | owner 层为 `1` |
| 其他 | 不增加限制 |

`485580` 从 context `[+218,+21C)` 的 stride `36` 基础列记录读取格子；每记录包含 stride `16` 的行 vector。`xCell/14` 选列记录，`xCell%14` 选行内 int32。超出基础行后，以 `(yCell-baseRows)/10`、`%10` 选扩展块和块内行，经 `486B80` 找记录；无效扩展记录返回数值 `2`。总列数为 `baseColumnRecords*14`，扩展块行数为 `extensionRecordCount/baseColumnRecords` 的无符号除法，总行数为 `baseRows+extensionRowBlocks*10`。本轮没有追到将 PVF 标签写入这些结构的 loader，因此没有给这些整数猜测枚举名。

碰撞通知 `4B97B0 → 4E8A30` 先调用非空 `actor+148` 的 `virtual+1C(axis,velocity,collisionObject)`，再调用非空 `actor+154` 的同一槽。之后仅在 `actor+1606 && actor+1607 && actor+1678==-1 && axis∈{0,1}` 时调用 owner `virtual+57C=4B9560`。后者沿当前轴前进一步，并试探横轴正负距离，写 `1678/167C/1680/1684` 后调用 `virtual+49C` 应用方向；没有直接清零速度。

三段斩的非零加速度轴配置已使两个实时方向输入门为假，因此不会从此包装进入绕障。`actor+148/+154` 的具体动态类及 `virtual+1C` 函数体仍未闭合；附件可能修改战斗状态，不能根据包装本身没有写 HP / V / A 就推断所有碰撞响应无副作用。

[owner_model.py](owner_model.py) 提供有界的 `z_allowed`、`terrain_allowed`、`pair_blocks`、`first_blocker`、`wrapper_branch` 与 `response_effects`。`wrapper_branch` 返回 `None` 表示应委托 `4E7DD0`，不是“允许”；`response_effects` 仅记录通知调用与顺序，不执行未知附件或完整绕障。地形格子读取由调用方提供，未模拟 PVF loader 和原生扩展存储。

[native-owner-vectors.json](native-owner-vectors.json) 记录 **74/74** 原生指令向量匹配、零不匹配：地形 `33`、pair `22`、活动状态包装 `8`、碰撞通知 `6`、Z `5`。[native_owner_verify.py](native_owner_verify.py) 将相应原函数指令重定位到独立 PE32，修复 rel32 与跳表后执行；虚拟 getter、RTTI、活动状态、地图形状和格子查找是显式 fixture，附件与绕障只记录调用。它没有启动 DFO，也没有执行整个 `4E7DD0`、原生 `485580` 存储读取或原场景。

[contract-checks.json](contract-checks.json) 另记录八项合成组合检查，覆盖注册门、首个 blocker 与 ignore 的指针身份、保留 inactive RTTI 指针、后续失败 cast 清空、state `5` 提前返回、附件顺序和包含末端格的遍历。它不是额外的原客户端实战证据。现有验证支持已列出的分支和输入，不意味着所有极端整数输入或所有动态类均已恢复。

从工作区根目录重建：

```powershell
python -X utf8 analysis/combat_motion/owner/build_evidence.py
python -X utf8 analysis/combat_motion/owner/native_owner_verify.py
python -X utf8 analysis/combat_motion/owner/verify_contract.py
python -X utf8 analysis/combat_motion/owner/build_contract.py
```

后续仍需追：manager 注册/候选表更新、运行时真实 footprint / layer / `scalar21c` / 矩形与地图格、PVF 到阻挡格结构的 loader、活动状态 `16` 的名称及实际 appendage、附件 `+148/+154` 的通知体，以及外部运动控制器。接入技能预览时应将这些作为显式输入或未实现边界，不能由本目录结果推断完整攻击、受击、死亡或场景破坏消费链已经闭合。
