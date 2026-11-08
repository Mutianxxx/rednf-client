# 60US state 10：施法阶段、主体 ANI 与职业效果分派

此目录回答一个限定问题：输入处理请求 `state 10` 后，原客户端如何解释整数向量、选择施法动画、等待读条、切换到释放阶段，并把具体效果交还职业代码。这里确认了 **18 条本地请求路径的阶段主体 ANI**，没有把这些路径标为 18 个完整技能控制器。

唯一二进制来源是 `D:/dnf/60US/DFO/DFO_fixed_v3.exe`，SHA-256 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`；PVF SHA-256 `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98`。这是静态反编译和原字节证据，未观察原客户端执行，未恢复原始源码，也未借用其他版本枚举或 `dnf-rebuild` 推测。

## 给预览使用的文件

- `phase-animation-contract.json`：18 条条件绑定，含 phase 0/1、技能 ID、动画索引、CHR 标签、源 token、资源路径和来源哈希。Gunner 的 5 条路径给出 job 2/5 两种条件候选，不能算作两个职业均已验证技能控制器。23 个 variant 中 21 个在当前 PVF 有注册、对应 42 个阶段资源；另外 class 5/skill 54、70 没有当前注册，显式 `registered=false`，其 4 个资源仅是共享控制器候选，不能加入可选技能。
- `state10-request-vectors.json`：18 条向量构造，保留 append 顺序、写入 VA 和动态函数返回值表达式，不用猜测数值填补动态字段。
- `evidence-index.json`：48 个原字节摘录、地址/文件偏移/哈希，以及 REA Evidence ID。
- `verification.json`：48 个摘录、16 个指令锚点、40 个虚表槽、8 个原生标签、18 个向量、46 个资源候选行的来源一致性验证通过；其中只有 21 个当前注册 variant、42 个阶段资源，2 个未注册 variant 必须排除。

预览允许展示“施法阶段资源”；不能根据此合同推导技能伤害、命中范围、发射物、效果附层、CD 或真实可释放条件。原来的 `combat_skill_dispatch` 130 条结果保持不变。

## 调用链与 phase 切换

Swordman 的职业 state handler 是 `0x7307B0`。第二个 switch 在 `0x7318D5` 使用表 `0x73D504`，`state 10 - 8 = index 2` 指向共享处理入口 `0x73A168`。`0x73A17A` 调用 `0x4C5730(state, vec, apply_flag_3, apply_flag_4)`，后者在 `0x4C579B` 调用 `0x4DE370`。因此职业代码会先把 `state 10` 交给共享 character 处理器安装 phase ANI，再执行后置职业效果。

共享 tick 链为 `Swordman 0x726150 → 0x4BF9D0 → 0x4DC220`。`0x4DC92F` 的 state switch 使用 byte 表 `0x4DE334` 和 DWORD 表 `0x4DE314`；state 10 的 byte 为 2，目标 `0x4DCCE4`。

1. Phase 0 等待状态计时器 `this+0x1564` 的 elapsed 达到 `this+0x2434`。`0x49C090` 必须返回真，duration 不能为 -1。默认目标选择限制为 -1 时，`0x4DCD52` 调用虚函数 `+0x784(1, 0)`；有目标限制时，先执行 `0x4D5EB0` 的目标集合与交互分支。
2. 基础 callback `0x4D80F0` 把下一 phase 写为新向量的第 0 项；有目标则把 `target.+0x44()` 返回值附为第 1 项。`0x4D81E1` 再请求 `state 10`，并非把 state 10 替换成另一个技能动作号。
3. 再次应用 state 10/phase 1 时，共享处理器保留上次 phase 0 存下的技能与索引，选择另一张 ANI，然后进入职业 handler 的后置效果分支。
4. Phase 1 的限时结束在 `0x4DCF6C..0x4DD00F`，最终调用 `+0x784(-1,0)`；mode 1/2 还要求 `this+0x246C` 已置位。基础 callback 结束时，地面请求 state 0，空中请求 state 6、向量 `[1,0,0]`。Swordman mode 0/skill 74 是明确例外：`0x71CAF0` 请求 state 41。

应用时的计时重置由 `0x4BAD60` 第 3 个参数控制，`0x4BC64C..0x4BC65F` 重置 `this+0x1564`；不能让独立预览把 phase 0 的累计时间直接带入 phase 1。以上是静态调用条件，未确认本地预测和实际网络往返。

## state 10 向量的原生解释

Phase 0 至少读取 8 项；原生没有为这 8 项逐项提供长度检查。这里的 18 条请求为 8 项，只有 Swordman skill 23 为 11 项。Phase 1 的短向量只携带下一 phase 和可选目标 ID，其他字段复用已存状态。

| 下标 | 原生存储 | 已证实用途 |
|---:|---|---|
| 0 | protected `this+2420` | phase：0 初始、1 释放、2 目标选择 |
| 1 | `this+2428` | mode；0 走职业效果，1/2 有通用配置对象分支；枚举名称尚未恢复 |
| 2 | protected `this+242C` | 技能 ID |
| 3 | protected `this+2434` | phase 0 duration，入场后按 `value*1000 / protected(this+1620)` 缩放 |
| 4 | protected `this+243C` | phase 1 duration，-1 跳过此限时退出，否则同样缩放 |
| 5 | `this+2444` | 两阶段动画表索引；mode 2 改用虚函数 +36C |
| 6 | 局部值 | phase 0 调用 +494 时重复传入的控制参数；值 4 另触发 +554 |
| 7 | `this+2448` | phase 1 的 +494 控制参数，确切枚举待查 |
| 8 | 局部值 | 可选、默认 1000，phase 0 的 +494 第 3/4 参数 |
| 9 | `this+244C` | 可选、默认 1000，phase 1 的 +494 第 3/4 参数 |
| 10 | protected `this+2450` | 可选、默认 -1，控制是否参与目标搜索/距离检查 |

`this+1620` 的业务含义以及 +494 参数完整语义未在此阶段命名；不能把所有整数都直接称为速度/帧数。初始时长常见来源 `0x468430`，该 helper 读取 `skill.+0x1A4[(level-1)*8]` 的 protected 值；其他请求使用 `0x54FF60` 或 `0x550080` 的参数读取结果。此处保存实际调用地址，尚未把所有动态来源映射为 SKL 标签。

例如 Swordman skill 32 的本地请求是 `[0,0,32,0,return(0x54FF60@0x72B849),1,4,4]`；skill 23 是 `[0,0,23,return(0x468430),return(0x54FF60),0,4,4,1000,1000,截断除2(return(0x54FF60))]`。这些值说明同为 state 10 仍有不同读条与目标选择语义。

## CHR throw motion 的确切绑定

原生解析器 `0x88BE23..0x88BF6B` 逐一比较 UTF-16 标签，交给 `0x8304E0` 写入对应模板字段。构造链 `0x4DAAF0..0x4DACF1` 循环 4 次，通过 `0x472B80` 装载对应 ANI；资源根来自模板 `+0xC04`。

| 阶段 | CHR 标签 | 模板字段 | runtime | 选择器 |
|---|---|---|---|---|
| phase 0 | `[throw motion N-1]` | `+B68+4*(N-1)` | `+1BE0+4*(N-1)` | virtual +5E0 |
| phase 1 | `[throw motion N-2]` | `+B78+4*(N-1)` | `+1BF0+4*(N-1)` | virtual +5E4 |

N 为 1 到 4，向量里的索引是 N-1。常规选择器分别为 `0x745B80`、`0x745BA0`，后续由虚函数 +F0 安装当前 ANI。Mage 有 override：`0x747FD0/0x748010` 会先调用 `0x6DE720`；条件成立时两阶段均返回 `this+2DE8`，不能盲用表格覆盖所有 Mage 形态。

| 原生控制器 | 技能 ID | vec[5] | phase 0 → phase 1 |
|---|---|---:|---|
| Swordman | 23、18、84、76 | 0 | Throw1.ani → Throw2.ani |
| Swordman | 24、32、74、47、30、34、44、85 | 1 | Summon1.ani → Summon2.ani |
| Fighter | 13 | 0 | Throw1.ani → Throw2.ani |
| CNGunner，job 2/5 条件候选 | 45、70、54 | 1 | Command1.ani → Command2.ani |
| CNGunner，job 2/5 条件候选 | 76、78 | 3 | SetRobot.ani → SetRobot.ani |

表中所有本地请求的 vec[0]/vec[1] 为 0。常量零寄存器来源见 `0x72617E` 的 Swordman EBX、`0x6A373C` 的 Fighter EDI、Gunner `0x6D50AB/0x6D511B` 的 EDI；推导遵循 MSVC x86 的非易失寄存器约定。入口前的输入、学习等级、当前状态、职业变体、装备等门控不在此表中，不能据此宣称某技能必然可用。

## 具体技能效果仍在职业代码

虚表 +784 是“请求下一 phase”的 callback。五种原生类分别为 `71CAB0 / 693F60 / 6BA9E0 / 6E4FA0 / 4D80F0`。Swordman 只有 skill 74 的结束行为在 +784 特殊处理，其余委托基础 callback。

真正的 Swordman state 10 效果分派位于 `0x7307B0` 共享调用之后，表 `0x73D5C0` 的 index 4 指向 `0x73B42C`。这里先要求 mode 0，再读已存技能 ID 和 phase；不同分支分别创建附层、声音、被动对象或修改角色状态。例如可见 skill 24、phase 0 调用 +2B8 传入对象常量 `0x4E2A/0x4E29/0x4E3F`，skill 32 分支传入 `0x4E32`。这些只是原生调用锚点，尚未把对象资源、ATK、ANI 和命中接受者闭合为可用技能实现。

Shared tick 中的 +718=`0x4D2150` 是 mode 1/2 的配置对象创建路径，mode 0 跳过该段；+670=`0x745E40` 是把字符串交给 +10C 的分支。二者不能被命名成通用“所有技能最终派发器”。

## REA Evidence 与复核

| 函数 | Evidence ID |
|---|---|
| 7307B0 | `ev_d5a20a9df4046515d44da1f508ada209e46fd5798039b1fb62ac4f22db98f062` |
| 4C5730 | `ev_eb508c34fb20c62826fd2e7b252f6b7ff6ca7c7a04025423619b9da299e157a2` |
| 4DE370 | `ev_984cb665f4adb41b74d74e7c6e5b1d30d340889d101b71d0cc0122a62deca8fd` |
| 4DC220 | `ev_304c3d88552b5c37ce9a1896b74a63f1a97e94d5c3f9ab875350d79dac71df2e` |
| 4D80F0 | `ev_1add8e59be3b70beac6bb4e144c3e0fa5724db100fff84f34ece3ac741f10c6e` |
| 71CAB0 | `ev_8ce0997b353f590b30a2d6c85997ef85e514551a97c6b0fabdcf64b8fead2b9b` |

重新生成/验证：依次运行 `extract_vectors.py`、`build_contract.py`、`verify.py`，Python 为 `G:/ProgramData/miniconda3/python.exe`。脚本只读客户端和之前目录，只写本目录。验证仅证明保存的静态字节和机器合同一致；原客户端对照、phase 时间参数完整解释、各职业附层/被动对象分派与碰撞链仍待继续。
