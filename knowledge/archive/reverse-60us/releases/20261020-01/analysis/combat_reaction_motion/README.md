# 60US 受击运动：参数到算术与持续时间

此目录使用当前 `DFO_fixed_v3.exe` 原字节及 REA088..091，恢复 Active state3 的水平运动配置和两个纵向算术函数。它提供可移植的局部源码，不执行命中接受、HP 计算、ACT、完整倒地或死亡。未采用 `dnf-rebuild` 的公式。

`evidence-index.json` 包含 8 个原字节片段、10 个虚表槽、5 个 float32 常量和 REA Evidence ID。`reaction_model.py` 是明确输入边界的实现；`native_verify.py` 将原函数指令放入独立 PE32，用声明过的明文 getter fixture 提供已解码参数，与模型比较。未启动 DFO，也未修改原件。

## state3 参数及调用

`4BB091` 开始读取状态 payload：`[direction, scaleInteger, damageVariant, optional3, optional4]`。前3项由调用方提供，后两项缺省0。`scaleInteger` 经整数转 x87、乘源 float32 `.01`、写回 float32，随后作为第五个参数传给 `virtual+518`。Monster 和 Swordman 当前虚表的该槽都为 `4BA620`。Ghidra 伪代码漏了这个 float 参数；原字节访问 `[ebp+18]`，并 `ret 14h`，应使用五参数签名：

```text
4BA620(&speed, &acceleration, optional4, optional3==2, scaleFloat)
  → EAX duration → protected actor+16C0
  → +488(0, speed, speed, 0, acceleration, 1)
  → +488(1, 0, 0, 0, 0, 0)
  → +494(0, 0, 1000, 1000, 1.0f, 1.0f)
  → movement511040(2, 0)              Z速度清零
  → 447960(direction) → +49C(...,4,0) 水平朝向另设
  → 4BA0C0(2,0)                     安装动态重力
  → +374(damageVariant)              资源选择前置条件
```

朝向还受 `CNMonster` RTTI / `+2770` 分支影响。此目录不会仅凭 ATK 的方向字样推断最终朝向。`damageVariant` 的 ANI/ACT 优先级见 `../combat_native_collision/monster-reaction-contract.json`。

## 水平函数 4BA620

`kind` 就是上述 `optional4`，尚未用未核对的业务名字替换其数值。

| kind / flag | 初速度 | 减速时间的选择 | 返回的受击持续时间 |
|---|---:|---|---|
| kind=1，任意 flag | 800 | 同持续时间 | `trunc(scale*333.0f)` |
| kind=2，任意 flag | 400 | 同持续时间 | `trunc(scale*333.0f)` |
| 其他，flag=true | 0 | `min(0,duration)` | 使用下方 stats 公式 |
| kind=-1，flag=false | 0 | `min(30,duration)` | 使用下方 stats 公式 |
| 其他，flag=false | 400 | `min(150,duration)` | 使用下方 stats 公式 |

普通分支的 stats 来自 `actor.virtual+344(3)`：

```text
p = trunc(float32(decoded stats+218) * decoded_float32(stats+220))
diff = signed_int32(2000-p)
base = trunc(max(diff,0) * .25f)
duration = trunc(base * scaleFloat)
```

diff 正时函数重新取得 stats 并调用 `4BDD40` 做同一次计算。模型要求两次读取期间 stats 不变；真实并发/回调变化未模拟。

若解码的 `actor+18D8==0`，输出 speed/acceleration 均0，**返回的 duration 仍保留**。其他情况下减速时间非0才计算 `acceleration=idiv(int32(speed*-1000),decelerationDuration)`，否则 acceleration 为0。这是整数除法，向零截断。

例如显式输入 `kind=0, flag=false, scaleInteger=100, stats218=1000, stats220=1, actor18D8=1`，得到 `speed=400, acceleration=-2666, duration=250, decelerationDuration=150`。不能将150当成250，也不能因减速倒计时结束而强制速度清零；后续积分遵循 `../combat_motion/motion_model.py` 的残余速度规则。

`4BD06A` 比较 `timer(actor+1564)>=decoded actor+16C0` 后，若 `virtual+410(3)` 真，请求 state9，否则经 `4BD9F2` 请求 state0。状态请求走 `virtual+28C`，不是本地无条件立即应用。此处没有等待受击 ANI 播完的门；真实时钟、hit pause 和状态接受条件仍由外层控制。

## 纵向算术及边界

`4B9FA0(true)` 使用-1500；地图数据指针存在时加 `map+9DC` 和 `actor+1660`，然后直接返回。`4B9FA0(false)` 使用 protected `actor+163C`；只有这个 base 非0时才加地图偏移，再乘 `trunc(float32(stats+238)*stats+240)`，对32位乘积做向零 `/100`。base为0时地图偏移被跳过。常量-1500并非所有实体的统一重力。

`4BA0C0(mode,explicit)` 把 mode 写 `actor+1638`：mode1用上述true，mode2用false，其余用explicit；向 movement axis2 写加速度并设倒计时-1。

`4B98F0(a,b,c)` 的整数乘/除先于浮点运算：

```text
float(int32(a*4000)) /
  (int32(idiv(int32(b*100),c)-10000) * float32(.0121) + float32(2100))
```

函数返回 x87 值；模型的 `impulse()` 表示调用者写入 float32 后的值。state4 会分别使用该函数换算 payload 参数，还含重入、二次击倒、随机化、落地与状态恢复分支。完整 state4 未接入；不能将 `[lift] 400` 直接填入 Z 初速度。

## 验证与使用

```powershell
& G:\ProgramData\miniconda3\python.exe analysis/combat_reaction_motion/build_evidence.py
& G:\ProgramData\miniconda3\python.exe analysis/combat_reaction_motion/native_verify.py
& G:\ProgramData\miniconda3\python.exe analysis/combat_reaction_motion/build_contract.py
```

原指令比较 **126/126** 通过，分别覆盖 53-bit 和64-bit x87 fixture：水平 kind/flag、gate0、scale0及正值、stats边界，重力base0/地图偏移/比例，冲量符号、除法截断和32位乘积溢出。`native-vectors.json` 保留全部输入/输出及测试 PE/代码哈希；这两种控制字是测试设置，未声称观察到原客户端控制字。

`sample_horizontal()` 可用明确的 stats、方向、初始XYZ与dt列表采样自由水平轴；它保留Z坐标，未模拟完整state3重力，不代表角色实际运行值。未验证的 float溢出、除零、未知输入域会拒绝处理。地图碰撞可参考 `../combat_motion/owner/`，不能因为局部数值相同就省略 owner 回调、时钟或状态请求。
