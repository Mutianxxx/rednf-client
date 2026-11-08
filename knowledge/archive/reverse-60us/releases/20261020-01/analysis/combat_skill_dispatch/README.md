# 60US 技能分派：当前 EXE 的静态合同

> 2026-10-19 运行现场补充：旧 v3 现保存在 `analysis/unpack_attempts/001/launcher_test/DFO_fixed_v3.original.exe`，当前同名 EXE 为导入修复 v4。D 盘正常启动后 `13B37C2` 已由随附的 `5h0w4ll_0v3r.exe` 替换为 `call A5F4A0; jmp 4D9758`；此前的消费保护缺口不能写成“原 VM 逻辑已恢复”。六段选定消费链字节与旧版相同，但不是技能逐调用跟踪。见 [补丁来源与消费尾部](../unpack_attempts/001/patcher-source/README.md)。下文保留旧静态分析记录。

当前已从指令证明 **Swordman 注册技能 5（HardAttack）通过命令资格和技能消费后请求 native state 20**，并定位了六个职业索引对应的构造函数、虚表、职业处理与状态应用入口。Gunner 与 ATGunner 在本版本共用 `CNGunner` 控制器，由构造参数区分职业索引 2 / 5。

证据来自 `DFO/DFO_fixed_v3.exe`，SHA-256 为 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`，image base 为 `0x400000`。这是现有修复版二进制的静态结果；没有执行游戏，没有声称恢复原始源码。未从 `dnf-rebuild` 引入战斗规则。

## Skill 5 → pending state 20

| 阶段 | 真实指令位置与行为 |
|---|---|
| 职业处理 | Swordman vtable `D80F94 +188` = `726150`。该函数先按当前 state 分支，后有顺序的命令/技能检查，不能描述为单纯 skill-ID switch。 |
| 当前状态 | `72AB4D` 建立 `EDI=&this+155C`；`72AC9D..72ACBE` 只允许状态 0、11、8 进入此技能块。 |
| 命令资格 | `72ACCC` push `this+25E4`，`72ACCD` push `5`；`72ACD1` 调 `+73C` getter 返回命令对象，`72ACD9` 调 `559140`，`72ACDE` 检查返回值不是 `-1`。 |
| 释放/消费 | `72ACE9..72ACEF` push `1,1,1,5`，`72ACF3` 调 `+768` = `4C1D30`，成功要求 `AL != 0`。`4C1DA9` 将四参数原样传给 `4D9040`。 |
| MP 条件 | `4D91E3` 读取 `this+1238`，`4D91EF` 调 `550E10(skill,this,-1)`，`4D91F4` 比较当前 MP 与消费值。 |
| MP 提交 | `4D9554` 再读消费 MP；`4D9565` 取当前 MP；`4D956A sub eax,edi`；`4D956F` 经虚槽 `+3F4` 提交。是否实际走到这条分支仍受通用资格与参数控制。 |
| 状态参数 | `72AD11` push 技能 6；`72AD1C` 经 `+64C` 取等级；`72AD24..26` 生成 `level > 0`；两个 `407120` 构造整数 vector `[(skill6_level>0),0]`。当前 PVF 注册技能 6 为 `HardAttackCharge.skl`。 |
| 状态请求 | `72AD5A` push `0x14`；`72AD5E` 调 `+28C` = `4ED1D0(20,&vector,1,0,0)`。 |
| 挂起请求 | `4ED297..4ED2BA` 在开关和优先级条件允许时写 `this+4A0=state`，复制 vector 至 `this+4A4`，`this+4B4=priority`。这一步不直接调用 state handler。 |

`4CC270` 是无参 getter，函数末尾为 `ret`，返回 `this+26A0` 的对象（空时走 fallback）；技能 ID 5 和上下文仍留在栈上，交给随后 `559140` 的两个参数。`5591D0..5591D8` 读取条目受保护 ID 并与 `[ebp+8]` 比较，失败分支返回 `-1`，函数使用 `ret 8`。这一区别对正确还原调用合同很重要。

PVF 名称只用于把已证明的数值 ID 5 / 6 绑定当前注册文件：`skill/swordmanskill.lst` SHA-256 `36e7c46b3ea3e62b212f06ce81f8dcc21ef7dab08fa916cfaebe78ad0b8a6f0e`。HardAttack 的脚本 SHA-256 为 `1cc0c639f70efab493d8d9d38ebb438c21c6132a5f6b3ff3e7e8d38b88e7f846`，HardAttackCharge 为 `d02e1f362600a692998b426e5b86505ab655c5764ba0c7ff7fba6000dff6de8d`。完整路径、PVF CRC、archive hash、文件位置保存在 `dispatch-chain.json`。

## 六职业控制器

`748C40` 按输入索引 `0..5` 分派，表位于 `748DB4`。每个构造函数的虚表写入与 MSVC RTTI TypeDescriptor → COL → vtable 交叉核对。

| 职业索引 | 构造函数 / 参数 | 虚表 | `+188` 职业处理 | `+22C` 状态应用 | `+768` 技能消费 |
|---|---|---|---|---|---|
| 0 Swordman | `7469B0(0)` | `D80F94` | `726150` | `7307B0` | `4C1D30` |
| 1 Fighter | `746F50(0)` | `D81774` | `69D4F0` | `6A72A0` | `693960` |
| 2 Gunner | `747510(0)` | `D81F54` | `6CFC30` | `6C3FB0` | `4C1D30` |
| 3 Mage | `747B70(0)` | `D82734` | `6EBC60` | `6F3E90` | `4C1D30` |
| 4 Priest | `7488E0(0)` | `D82F64` | `70D7D0` | `712390` | `4C1D30` |
| 5 ATGunner | `747510(1)` | `D81F54` | `6CFC30` | `6C3FB0` | `4C1D30` |

六行共同的 `+28C=4ED1D0`，`+290=4EDAC0`，`+294=438700`（取 `+4A0`），`+298=438710`（清为 `-1`）。`693960` 的 Fighter 覆盖先将四参数原样交给 `4C1D30`，之后存在技能 33 相关额外分支，因此不能忽略该覆盖。

Gunner/ATGunner factory 分支分别为 `748CD7` / `748D71`，同分配 `0x32BC` 字节，然后 push 0 / 1 调 `747510`。其 `747529..74753C` 将 bool 转换为 job 2 / 5，经过 `746670 → 7456C0` 传给资源注册加载 `4E1E80`；`747550` 安装同一虚表。共享控制器不代表技能行为相同，仍必须逐一保留该函数中的职业变体条件。

## 挂起请求、序列化与状态应用

`4EDAC0` 要求 `this+49D==0` 且 pending `this+4A0!=-1`。它在 writer `+8` 传 `(5,2)`，随后依次写两个对象 ID word（对象 `+3C` / `+40` 返回值）、state byte、编码后的 vector 长度 word、payload bytes。`4EDBC8` 调 manager global `10C0790` 的 `+44(1,-1,this,3)`，然后设置 `+49D=1`。未进一步确认该 manager 的完整运输行为，不将这次静态调用当作实际发包观察。

`8C1A30` 从 packet `+1` 读取 word opcode，以 `8C5E64` 为 switch 表；**表项 5 指向 `8C2162`**。该分支读取同样的 body 顺序，通过 `8C6600 → 4ED490` 解码 vector，`50B820` 查对象并转换为 `IRDCollisionObject`，随后：

```text
8C2395: object.vslot_22C(decoded_state, &decoded_vector, 1, 1)
8C23E4: pending = object.vslot_294()
8C23EE: compare pending against decoded_state
8C23F6: if equal, object.vslot_298()   // pending=-1
```

`4EDA70 → 4ED2E0` 的整数编码与 `4ED490` 的反向读取互相吻合：每组 7 bits，高位为继续标志，解码每字节先 `acc <<= 7` 再加 `byte & 0x7F`。这里是大端组顺序，不能误写为常见的 LEB128。当前 HardAttack 的两个 vector 值都是 0/1，编码无符号/负数边界不会影响这条已证明实例。

静态上能确认请求格式与 opcode-5 应用路径对应，且状态应用后清同值 pending。**实际本地预测、服务器权威处理、同一包是否经回环或远端返回、游戏运行中的先后时序仍未观察。** 不把 `4ED1D0 → 8C2395` 描述为直接 C++ 调用边。

## 证据与复验

- `dispatch-chain.json`：机器可读的合同、六职业表、当前 PVF ID 5 / 6 身份、尚未解决项。
- `controllers.json`：五种 native RTTI、COL、虚表原始字节及 hash；六职业映射在前一文件。
- `evidence-index.json`：选定片段的源 EXE hash、VA、RVA、文件偏移、片段长度与 hash。
- `verification.json`：已将 35 个选定 `.bin` 片段与源 EXE 逐字节核对，同时核对 10 个关键指令、六个构造函数虚表写入、factory 表与 opcode 表；另核对下述 130 条局部路径的原始字节。无游戏运行验证。

```powershell
G:\ProgramData\miniconda3\python.exe -X utf8 analysis\combat_skill_dispatch\discover_controllers.py
G:\ProgramData\miniconda3\python.exe -X utf8 analysis\combat_skill_dispatch\build_report.py
G:\ProgramData\miniconda3\python.exe -X utf8 analysis\combat_skill_dispatch\find_dispatch_candidates.py
G:\ProgramData\miniconda3\python.exe -X utf8 analysis\combat_skill_dispatch\review_local_paths.py
```

只有 `evidence-index.json` 选定的区域用于当前结论。目录保留其他探索性片段，部分起点在指令中间；这些首行解码不得引用。两个 jump-table 片段是数据，附带 `.asm` 的线性输出没有指令含义。现有修复 EXE 仍有保护片段，特别 `4D96F1` 跳入 `13B37C2`，不能把保护区域线性解码解释成原始逻辑。

## 扩展筛选与逐条证明的边界

`find_dispatch_candidates.py` 对五个 native `+188` 入口先收集字面 skill ID 与 state 的邻近调用，得到 275 条候选，保存为 `dispatch-candidates.json`。**顺序邻近不证明两个调用属于同一释放路径**，此文件不能直接用于播放器绑定。

随后使用更严格的局部检查：技能消费后必须立刻 `test al,al`，失败 `je` 必须跳到状态请求之后，成功至第一次 state 请求之间不得存在其他跳转；两个调用的 ECX 必须显式赋予同一非易失寄存器，段内不得修改该寄存器（遵循标准 MSVC x86 被调用者保存约定）。字面 skill-ID/state 参数与原始指令完整保留，并要求该段落在已观察到的 Ghidra procedure body 中。得到 `local-dispatch-paths.json` 中 **130 条成功直达路径，126 个去重后的 native-class/skill-ID/state 组合**：

| native 控制器 | 局部路径数 | 去重 ID/state 对数 |
|---|---:|---:|
| Swordman | 42 | 40 |
| Fighter | 29 | 28 |
| CNGunner（2 / 5 变体未细分） | 25 | 24 |
| Mage | 16 | 16 |
| Priest | 18 | 18 |

每条记录包含真实四个参数的 push 表达式、失败分支位置/目标、成功段 raw bytes/hash/file offset、反汇编以及 Ghidra Evidence ID。局部检查**没有证明上游职业变体条件、全部输入状态、vector 每项意义、技能动作完成过程或运行可达性**。Gunner/ATGunner 不会仅因共享类就各自计为一套已实现技能。

`local-dispatch-paths.csv` 提供同一批 130 条的筛选表，附当前 PVF 注册路径候选。Gunner 的两份职业注册只作为名称候选保留；表中没有将其提升为两套行为绑定。

在此基础上人工阅读并保存了 `reviewed-local-paths.json` 的九条局部合同：

| native 类 | skill ID | 请求 state | 消费调用 | 状态请求调用 | 参数/条件摘要 |
|---|---:|---:|---|---|---|
| Swordman | 5 | 20 | `72ACF3` | `72AD5E` | `[(skill6 level>0),0]`，完整前文链路 |
| Fighter | 1 | 47 | `6A371F` | `6A3734` | 命令资格、消费成功；vector 为 null |
| Fighter | 5 | 30 | `6A3CBA` | `6A3CCF` | 命令资格、消费成功；上游还有 `6B5CD0` 条件 |
| CNGunner | 3 | 19 | `6D5683` | `6D56CD` | vector `[3]`；命令资格失败时，state12/4 下另有命令对象 `+48` 路径 |
| CNGunner | 4 | 20 | `6D5731` | `6D577B` | vector `[4]`；state0/11/8 与命令资格 |
| Mage | 4 | 22 | `6F0C65` | `6F0CAF` | vector `[4]`；state0/11/8 与命令资格 |
| Mage | 12 | 23 | `6F2A1B` | `6F2A65` | vector `[12]`；上游 state0/11/8/22 gate 另保留 |
| Priest | 1 | 20 | `7103C1` | `7103D8` | state0/11/8、命令资格、null vector |
| Priest | 11 | 26 | `71042A` | `71043F` | state0/11/8、命令资格、null vector |

很多技能汇入通用 state10（例如 Swordman23/24/32 等），必须继续解释 vector 和后续状态控制，不能将 state10 当成单个技能或动画。

Ghidra 所观察的函数 body 来自 `analysis/rea/results/027..031-procedure.json`，Evidence ID 与 inclusive ranges 在 `local-dispatch-paths.json` 中保留。其分析配置禁用 `Reference`、`Decompiler Parameter ID`、`Decompiler Switch Analysis`，body 为不连续地址集合。当前筛选只使用已观察范围限制正面关联；未包含的 switch case 不视为“不属于该函数”。

完整全技能映射、技能 state/substate → ANI/ATK、实际命中接受、怪物反应与死亡、破坏物和 UI 仍需由后续独立证据补全。
