# ReleaseWave 标量进入原生伤害数值的消费者

`5C77B0` 写入的是生成物的 **template ATK `entity+5DC.damage`**。原生取当前攻击信息时使用的是另一个结构 `entity+260`，两者之间已经找到实际安装链。当前 ReleaseWave 的标量进入 **base damage**，没有写入武器百分比字段。经过后续数值计算与收击处理，才可能形成最终 HP 变化。

本目录复用 `combat_attackinfo`、`combat_hit_lifecycle`、`combat_native_collision` 的证据，并逐项回查当前 EXE 字节。REA 058 的构造函数、070 的安装函数及 094 的数值函数用于交叉核对。原 EXE/PVF 只读，全部文件新增于 `scalar/consumer/`；没有改父合同、主预览或 `dnf-native-demo`。

## 已闭合的安装桥

```text
5CE740 构造 ReleaseWave
  →490720 通用 PassiveObject 构造
    →437D30 构造 template ATK+5DC，内部435430 reset
    →4A0DA0→49F4D0 加载当前 OBJ
      →49FB01 复制当前 PVF ATK 至 template+5DC
  →5CE77D→5C77B0
    →signed int dynamicScalar 转float32
    →写 protected(template+5DC.damage)

opcode21 case8C438C
  →8C43B2 entity.slot344=49DD10(owner)
    →entity+530=owner
    →复制 owner 的属性 getter 结果到 entity+798..7B8
  →8C43CA→50DD70 正常场景注册分支
    →50DFF3 entity.slot10=49F010
      →49F023 entity.slot198=4EDCD0(template+5DC)
        →4A27E0 复制至 current ATK+260
        →slot1A0 重置命中历史

命中数值入口4EB780
  →4EB798 attacker.slot19C=438650
    →返回 current ATK+260
  →4EB974 protectedFloat(ATK+0)
    →numeric+0
  →4EC9F4→8B8650(numeric,victim,attacker)
```

`50DD70` 存在早退/排队分支，上图限定实际到达 `50DFF3` 的注册路径。`49F010` 安装 template 后还检查 `entity+148`：若有 action，且它的 ATK（action `+B0`）满足 `weaponApply!=0 OR damage>0 OR absoluteDamage>0`，会再次调用 `+198`，以 action ATK 覆盖 current ATK。当前 OBJ 没有声明 ACT 不能单独证明任意运行时 action 指针始终为空，模型因此要求显式提供这一输入条件。

## 标量的具体数值身份

当前 `passiveobject/character/swordman/attackinfo/releasewave.atk` 没有 `[damage]`、`[absolute damage]`、`[damage bonus]`、`[weapon damage apply]`。原生 `435430` reset 将这些字段置 0；随后 `5C77B0` 仅覆写 damage。没有 action 覆盖或后续修改时，安装结果如下。

| current ATK 字段 | 值 | numeric 位置 |
|---|---|---|
| `+0 damage` | `float32(dynamicScalar)` | `+0 float32` |
| `+8 absolute damage` | 0 | `+F float32` |
| `+10 damage bonus` | 0 | `+6 float32` |
| `+18 attack type` | magic=1 | `+5 byte` |
| `+1C weapon damage apply` | 0 | `+4 byte` |

`8B79C8..8B7A02` 的第一段计算为：

```text
B = numeric.baseDamage
if weaponApply:
    type1:   B += numeric+33
    type0/2: B += numeric+2F
B = float32(B * (1 + numeric.damageBonus * float32(0.01)))
```

因此当前 ReleaseWave 在这段的输出仍为 `float32(dynamicScalar)`。在父目录声明的无修正查询基线下，Level1 对应 552，Level30 表探针对应 5158。这些值都不是武器伤害百分比系数。Level30 仍不表示当前技能可以学习到 30 级。

这也与普通鬼斩的已知写入不同：鬼斩控制器将 `S-100` 写在 damage bonus，且 ATK 的 weapon apply=1；不能将那条公式套到当前 ReleaseWave。

## 普通 base 分支如何继续使用它

`49EE85` 将 PassiveObject type mask `entity+E4` 初始化为 `0x21`，`slot30=407B60` 读取它，`4EB7F0` 将其放入 `numeric+191`。生成物 `slot1BC=439090` 转发 owner 的同一 getter；当前 Swordman 虚表 `D80F94+1BC=8E49B0` 返回 false，因此 `numeric+18E` 保留初始化值 0。对应当前已绑定的 Swordman owner 与未修改 type mask，`8B85F0` 选普通 `8B79C0`。另一条 `8B8560` 分支保留在合同中，没有用普通公式替代。

`8B79C0` 在前述第一段之后仍然执行：

1. 对 type0/type1，以 `1 + numeric+37/+3B * f32(.01)` 再乘一次并存 float32。
2. 读取 `numeric+3F/+43`，根据 `numeric+18A` 决定是否先乘 `448C10(attacker,3/5)`，再用独立 protected global 作分母，乘 `1 + stat/global` 并存 float32。
3. 乘 `448C10(attacker,0)` 及 `1 + numeric+47`，由外层 `8B866F` 存 float32。

即使 weapon apply=0，base damage 仍会经过这些属性/环境因子。这里只按实际偏移命名未知操作数，没有未经验证地把所有偏移命名成力量、智力或技能倍率。

`consumer_model.normal_base()` 实现上述有界片段。调用者需要提供实际 numeric 操作数、protected global 和 `448C10` 返回值样本。缺少输入不会默认填 1。比如显式输入 `numeric43=250`、分母 250、其他因子为单位值时，552 变成 1104；这是验证公式的人工样例，没有宣称原客户端角色恰好有这些属性。

注意不同阶段有不同转换：父目录技能查询的 percentage 修正会经 `C01544` 截断，因此 552 加 10% 得 607；这里 base 数值的第一段只存 float32，同样 bonus10 得 `607.2000122070312`，不会在这里截断成整数。

## 最终 HP 仍在更下游

完整 `8B8650` 已捕获到 `8B8E9C`，合同列出各有界处理区段：可选元素处理、`8AE160`/`8ADCB0` 随机变化、`8B7C90` 输出的减免项、absolute damage 分量、`8B7AB0`、倍率数组、mode4 的目标 HP 范围修正及末尾附加项。最终在 `8B8E8B` 调 `C01544`，结果同时返回 EAX 并写 `numeric+1BD`。这些分支的全部语义、运行时数值与保护全局状态尚未闭合成一个完整公式。

返回整数后，Monster 包装器 `4F5C20` 继续通知相关回调；`4B28D0` 又可能添加 ATK `+128` 相关的 HP 项，或经 `4B6C90` 修改该值。ATK `+178==2/4` 还选择其他效果路径。普通扣血分支才在 `4B312F` 计算 `oldHP - downstreamDamage`，于 `4B3135` 向 `slot3E8` 传入**新的绝对 HP**。完整命中资格、受击状态与 HP 写入边界继续引用 `combat_native_collision/hit-contract.json`。

所以可执行模型始终保留 `final_victim_damage: null`；不能把 SKL 原值、生成物 base damage、第一段输出或 common 返回值直接当作完整最终扣血公式。

## 入口与复验

- `consumer-contract.json`：安装次序、字段、普通/替代分支和后续数值路径。
- `consumer_model.py`：有界安装模型、第一段计算及完整普通 base 片段。
- `declared-template-context.json`：明确声明成功安装、无 action 覆盖、快照未再修改且普通 base 路径已建立；它不是内存观测。
- `endpoints.json`：552/5158 两个输入的安装结果及第一段输出。
- `evidence.json`：18 个新增源码绑定片段、15 个复用片段、5 份 REA 身份与相关合同哈希。
- `verification.json`：**146/146 项通过**，包含当前文件身份、关键调用/字段/虚表、覆盖行为与数值边界。

```powershell
& 'G:\ProgramData\miniconda3\python.exe' 'analysis\combat_spawned_object\scalar\consumer\consumer_model.py' --scalar 552 5158
& 'G:\ProgramData\miniconda3\python.exe' 'analysis\combat_spawned_object\scalar\consumer\verify.py'
```

验证只读当前源文件并执行重建模型，没有运行原客户端。浮点运算沿用父目录声明的 x87 64 位有效数、nearest-even 与显式 binary32 存储假设；运行时控制字仍未观测，异常值/溢出支持边界未扩大。
