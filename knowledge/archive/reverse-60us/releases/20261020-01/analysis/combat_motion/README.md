# 60US 三段斩：运动消费者与 ANI 速率合同

当前客户端的三段斩运动链已追到逐轴积分和碰撞接口，并提供可运行的 Python 实现。可以计算给定攻速与游戏时钟增量序列下的 `x(t)`，并与动画的逐帧 deadline 放在同一输入时钟上。地图的可通行策略、碰撞响应以及外部运动控制器的具体类型尚未闭合，不能将这个结果称为完整原客户端战斗复刻。

证据来自 `DFO/DFO_fixed_v3.exe`，SHA256 为 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`，PVF 对应 SHA256 为 `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98`。本目录没有采用 `dnf-rebuild` 中的猜测；全部写入限制在本目录，没有修改客户端、PVF、预览或 native demo。

[motion-contract.json](motion-contract.json) 是机器可读合同，[evidence.json](evidence.json) 列出 38 段原字节及其 VA、文件偏移、SHA256、13 项常量、虚表槽和 `timeGetTime` 的导入身份。每段同时保存 `.bin` 和 Capstone `.asm`。REA 伪代码作为辅助证据引用；尤其 `50FDE0` 的两个参数应读为 `int32 axis, int32 dt`，不能沿用反编译器的 `int*`、`float` 类型。

三段斩的入口设置位于 `0x732C63..0x732CDA`：

```text
actor virtual+488(0, 600, 600, 0, -1000, 1)
actor virtual+488(1,   0,   0, 0,     0, 0)
actor virtual+494(2, 2, 1000, 1000, 1.0f, 1.0f)
actor virtual+49C(current_direction, 4, 0)
```

这里只设置 x、y；z 轴既有状态必须保留。`motion_model.tripleslash_axes()` 为单独预览创建的 z 是静止占位，不能原样当成状态22的 z 重置行为。`600`、`-1000` 由原生技能状态硬编码，不能把它们误归为 SKL 直接提供的数据。PVF 仍提供动作、效果、ATK 和层动画等资源，详见相邻的 [三段斩合同](../combat_tripleslash/tripleslash-contract.json)。

| 原生位置 | 已核对职责 |
|---|---|
| `4B9D80`，virtual `+488` | 写入 actor 的轴配置；非零加速度强制关闭该轴的实时方向输入门 |
| `4B9C60`，virtual `+494` | 写移动/动画模式；模式2读取有效攻速值，分别设置移动和 ANI 缩放 |
| `4B99C0`，virtual `+498` | 方向符号 × 移动缩放 → 速度和加速度 |
| `511040` / `511DD0` | 通过本地 owner 身份门后写 provider；加速度变化重置 countdown 为 `-1` |
| `510D70` | 当速度与加速度反向，写 `remaining=trunc(V*(-1000)/A)` |
| `49BEC5` → `511400` | actor 每次更新进入运动 tick，取时钟差并依次更新 x、y、z |
| `50FDE0` | 积分、每次位移限幅、普通 owner 逐点碰撞、位置写回 |
| `4B9EB0` / `4B4DA0` / `4ACF80` | ANI 当前速率刷新 / 身体动画安装 / 效果安装 |
| `A27870`、`A2792F..4A` | 解码后的 delay 和百分速率消费到下一帧 deadline |

移动模式2的缩放值记作 `S`：`4B55A0` 从 stats 的 protected `+1F8` 整数和 `+200` 浮点乘数求 `max(1,trunc(float32(base)*multiplier))`。当前没有实际运行角色的 stats 捕获，所以 `850` 或 `1000` 均只能作为示例输入。方向码 `0/2` 取 `-1`，`1/3` 取 `+1`，`4` 及其他码取 `0`；本报告不把这些数值额外命名成未经验证的世界方位。

令 `k=float32(0.001)=0.0010000000474974513`，`F=sign`（当 `S==1000`），否则 `F=float32(S*sign*k)`。原生末次方向应用的输入是 `V0=float32(600*F)`，`A0=trunc(-1000*F)`；若 `V0*A0<0`，倒计时为 `R0=trunc(V0*(-1000)/A0)`。它是带整数截断和浮点落栈的合同，不能普遍改写成“严格600毫秒后归零”。普通 setter 路径还要求 `49C090(owner)` 为真；远端/其他 owner 数据不能自动套成本地写入成功。

`M=actor+F8` 指向运动对象。活动 provider 为 `[M]`，为空则回退到 `M+8`；其 `+4+axis*4` 是 float32 位置，`+10+axis*4` 是 float32 速度，`+1C+axis*4` 是 int32 加速度，`+28+axis*4` 是 int32 加速剩余时间，`-1` 表示不设倒计时。`M+74` 是 owner，`M+78/+7C` 是外部控制器和启用字节，`M+A0` 是 timer，`M+E0` 暂停，`M+E4` 保存上次 elapsed。

`511400` 先检查暂停，然后 `dt=elapsed-M+E4`，再次读取 elapsed 写回 `M+E4`。`B06F00 → B12A80 → B12AB0` 已追到 `winmm.dll!timeGetTime`。时钟通道按整数百分比速率缩放、timer 有启用/暂停/偏移门，因此 `dt` 是**来自毫秒源的、已选通道并可缩放/暂停的游戏时钟整数增量**。不是未经绑定即可直接传入的墙钟时间；这个角色当时使用的具体通道与速率未捕获。此报告也不声称 `B12AB0` 保留小数余量。

逐轴积分的行为如下，所有 `Vn`、位移、最终位置均按已识别的 float32 内存写入取值：

```text
V==0 且 A==0：返回0，不动位置
A==0：mean=V
A!=0 且 (R==-1 或 dt<=R)：
    Vn=f32(V+int32(A*dt)*k)
    mean=(V+Vn)*0.5
    若R!=-1：R-=dt；若R==0：A=0
A!=0 且 0<=R<dt：
    Vn=f32(V+int32(A*R)*k)
    earlymean=f32((V+Vn)*0.5)
    mean=(R*earlymean+(dt-R)*Vn)/dt
    R=0；A=0
d=f32(dt*mean*k)，每次调用限制到[-2000,+2000]
自由路径：position=f32(position+d)
```

`int32(A*dt)` 对应原生32位乘法，包含溢出回绕。返回码为 `0` 静止、`1` 速度与加速度反向、`2` 非零速度且无加速度、`3` 速度与加速度同向或零速度仍在加速、`4` 普通 owner 碰撞拒绝。倒计时到期只清 `A`，没有“把速度强制设零”的指令。抽取原指令的核对向量中，`V=600,A=-1000,R=600,dt=600` 得 `x=180`、`V=-2.8498470783233643e-05`、`A=0`、`R=0`、返回2。这个残值不应在实现时擅自消掉。

在忽略浮点落栈、整数乘法溢出、限幅和碰撞时，可以用分段抛物线帮助理解：`t=累计dt*k`，`T=min(t,R0*k)`，`x=x0+V0*T+A0*T²/2+(t-T)*(V0+A0*R0*k)`。实际预览应调用离散实现并保留真实 `dt` 序列；大步与小步的浮点结果并不保证相同。

碰撞必须分三种情况。没有 owner、外部控制器不启用时，直接积分。没有启用外部控制器但有 owner 时，`50FDE0` 使用 `447FF0` 的正负半值远离零取整，将当前/目标坐标化为整数，每次只走一个坐标单位，x/y 调 `owner virtual+AC(x,y,&object)`，z 调 `owner virtual+A8(z)`；第一个拒绝点将位置写为上一个通过的整数点，返回4。此时 `V/A/R` 已更新，helper 本身不清它们；后续 `owner virtual+274(axis,V,object)` 可能有额外副作用，需要另追其具体实现。这里的坐标单位没有擅自改名为像素或米。

当 `M+78` 非空且 `M+7C` 为真时，逐轴函数会跳过普通 owner 探测，`511400` 把 provider 坐标截断后写入控制器的 `virtual+10` 缓冲，调用其 `virtual+8`，再依据模式、碰撞字节、轴锁定和 owner 回调处理结果。这个类与实例没有闭合；模型在 `external_controller=True` 时主动抛 `NotImplementedError`。普通回调可以通过 `can_move(axis, integer_xyz)` 接入，但真实地图策略和 `+274` 副作用仍需提供。

ANI 的 `+134` 是百分速率，`100` 才是名义正常速率。当前动画速率刷新和动画安装的浮点表达式必须分开保存：

```text
4B9EB0 刷新：rate=f32(Sani*float32(0.1))
4B4DA0 / 4ACF80 安装：rate=f32(f32(Sani)*G*float32(0.001))
G=protected global float at1003404；CA1C00初始化为100.0
帧设置 A2792F..4A：deadline -= trunc(decodedSignedDelay/rate*float32(-100))
```

`A27943` 确实是 `sub edi,eax`，但前面的乘数 `DF053C` 原字节是 `0000c8c2`，即 `-100.0`。给定正的已解码 delay，结果就是推进 deadline。总时长 helper `A24BB0` 则先算 `1/rate` 再累加 `trunc(delay*reciprocal*100)`，不能假设所有精度边缘与逐帧式一致。该目录尚未独立闭合 parser 写入 delay 的正负；正值例子沿用 PVF ANI 产物，原指令核对报告明确将 delay 作为已解码输入。

这两个速率表达式会因 float32 常量和落栈而不同。例子只作为固定输入说明，均未声称是实际角色运行值：

| 输入 Sani | 速率路径 | 落栈后的百分速率 | delay70 的 deadline 增量 | delay300 的 deadline 增量 |
|---:|---|---:|---:|---:|
| 850 | 刷新 | 85 | 82 | 352 |
| 1000 | 刷新 | 100 | 70 | 300 |
| 1000 | 安装，G=100 | 100.00000762939453 | 69 | 299 |

不能直接把三段斩身体 `70,70,70,70,300` 的资源 delay 相加当成实际运行时长。速率来源、安装/刷新路径、途中速率改变、父子 ANI 的 elapsed 及帧推进边界均会影响它。`A29C70` 在 root 速率改变时还会重置树，并用 `trunc(oldElapsed/newRate*oldRate)` 恢复 elapsed；本目录的固定速率示例不实现完整动画树生命周期。动画结束与帧边界以父任务的 ANI 合同为准。

运行与重建均在当前工作区：

```powershell
python -X utf8 analysis/combat_motion/motion_model.py --scale 1000 --direction 1 --dt 100 100 100 100 100 100 100
python -X utf8 analysis/combat_motion/build_evidence.py
python -X utf8 analysis/combat_motion/native_verify.py
python -X utf8 analysis/combat_motion/native_ani_verify.py
python -X utf8 analysis/combat_motion/verify_contract.py
python -X utf8 analysis/combat_motion/build_contract.py
```

`native_verify.py` 生成一个独立的最小 PE32 程序，将 `50FDE0` 原字节和原常量放回原 VA，provider 的四个位置/速度方法使用最小 getter/setter 替身，owner/controller 设空。它不启动 DFO。显式 x87 control word `037F`（64位尾数精度）和 `027F`（53位尾数精度）下，25组自由轴分支向量共 **50/50** 个位置、速度、加速度、倒计时、返回码内存结果与 Python 一致，见 [native-vectors.json](native-vectors.json)。这不证明客户端实际运行时的 control word，也不证明所有极端输入均逐位相同。

`native_ani_verify.py` 在相同独立环境运行未改动的 `A2792F..A2794A` 算术切片和完整 `C01544` 截断 helper，两种精度的 **46/46** 组结果一致，见 [native-ani-vectors.json](native-ani-vectors.json)。它验证“给定已解码 delay 和 rate”的原生消费公式，不声称执行过 ANI parser 或完整安装函数。[contract-checks.json](contract-checks.json) 另记录普通回调正/负探测、xyz 顺序、未闭合控制器拒绝和四组固定输入合成时间线；该碰撞策略是合成示例。全部都是可复核的局部验证，尚无原客户端实战录制证据。

后续接入预览需要传入实际有效攻速、游戏时钟 delta、既有 z 状态、真实地图回调和碰撞响应；若该 actor 使用外部控制器，还需继续恢复该类。完整角色更新中，状态切换、攻速刷新、ANI推进、移动和命中调用的先后顺序也需要与父任务链路合并后核对。此结果已经消除了“速度参数是什么单位”“随意匀速冲刺”“按资源 delay 固定播放”的猜测，但保留了未闭合环节。
