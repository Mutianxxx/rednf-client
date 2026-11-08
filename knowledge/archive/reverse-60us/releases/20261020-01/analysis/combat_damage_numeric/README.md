# 60US 共用伤害链：防御、绝对伤害、暴击

本目录延续 `combat_spawned_object/scalar/consumer/` 已确认的 ReleaseWave 技能数值消费链，只解释并实现 **8B8808 至 8B8B41** 的数值阶段，以及它调用的完整 `8B7C90`、`8B7AB0`。源文件是当前 `DFO/DFO_fixed_v3.exe`，SHA256 为 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`。本阶段没有采用 dnf-rebuild 中的公式。

`numeric_model.py` 提供独立的防御、攻击方属性加项、绝对伤害、暴击、暴击后比例函数。组合入口 `bounded(B, numeric, external)` 的 B 必须是客户端在 8B8808 的值；更早的属性、元素、随机浮动阶段已经影响过它。输出保留扩展精度值与最后一次 float32 写回值，并固定 `final_victim_damage=null`。这方便以后将原客户端分段快照接入预览，定位第一处不一致。

## 本次确认的执行顺序

```text
8B8650 早期属性/元素/随机浮动（此目录的显式输入 B）
  → 8B8808 防御与额外减免资格
      → 8B7C90 防御比例、额外百分比
      → 比例减免，再扣目标属性/保护全局除数
  → 8B88BF 加攻击方属性/另一保护全局除数
  → 8B893A 加绝对伤害部分，再扣目标绝对减项
      → victim.slot320(attacker)
  → 8B8A62 非负钳制
  → 8B7AB0 暴击资格与暴击倍率
  → 8B8A87 附加倍率、分类倍率、一次最小值 1
  → 8B8B41 本目录停止
  → 仍有倍率数组、模式/HP 分支及最后截断整数
  → 4B28D0 仍可更改该整数，才进入普通 HP 扣减
```

组合函数要求显式声明 `victim_slot320_does_not_mutate_numeric_snapshot=true`。该虚调用发生在绝对伤害算术之后；若真实对象会修改后续数值，应该分段使用函数并提供调用后的快照。

## 防御并非单一减伤率

攻击类型 0/1 分别取不同的目标防御整数、百分比增量、额外减免浮点数和保护全局系数。先得到 `D = f32(base*(1+bonus*f32(.01)))`，再乘 `448C10(victim,1)` 并写回 float32。

普通防御比例为 `f32(D/max(1,K*level+D))`；`numeric+1BC` 为真时先将 K 加倍。等级来自攻击方 `slot1D0` 的低字节，并按有符号 int8 使用；模式 4 固定 50，模式 6/7 改读对应运行时表中的有符号 int16。不能将其替换成无条件的怪物等级或技能等级。

**负防御且有效等级小于 10** 时，比例改为 `f32(D*f32(.0025))`。原指令比较的常量是 0；不存在“低等级正防御直接线性化”的结论。夹具包含负等级、负防御与边界等级 9/10 的对照。

调用方随后计算 `(1-ratio)-extraPercent*numeric5F`，乘 B 写回 float32，再减去另一目标属性/保护全局除数。后一减项与比例分母属于不同字段。

## 两种 ignore defense，以及绝对伤害

| PVF / 字段 | 当前客户端消费方式 |
|---|---|
| `[attack type]` 中的 `[ignore defense]` | ATK+18 枚举 2；跳过防御阶段，也跳过本函数的绝对伤害加项 |
| 独立 `[ignore defense]` 标签 | 837961 解析为 ATK+138 的布尔，打包为 numeric+E；关闭防御阶段与目标绝对减项 |
| `[absolute damage]` | ATK+8 整数转 float32 为 numeric+F；类型 0/1 的独立加项 |
| `[critical hit]` | 837800 解析至 ATK+100 浮点，打包为 numeric+13，进入暴击概率 |

绝对伤害的算术是：`absolute + (weaponApply ? weaponAbsolute*numericAB : 0)`，再乘伤害 bonus 和对应攻击方比例，写回 float32；乘攻击方 context 7/9 后加入 B。它绕过前面的百分比防御，但仍会受此处的 bonus、目标绝对减项、暴击和之后的倍率影响。不能把标签理解成最终无条件扣除相同 HP。

当前 ReleaseWave ATK 的 `damage`、`absolute damage`、`damage bonus`、`weapon damage apply`、`critical hit`、独立 `ignore defense` 标签都缺失。已有 consumer 证据将技能标量写入模板伤害，经注册安装到 current ATK；这里不据此假设角色暴击、目标防御或运行时保护全局为某个值。

## 暴击及写回精度

8B7AB0 首先将 ATK 的暴击参数加 **3.0**。随后按攻击方 type mask、攻击类型、numeric18E、numeric1B5 加上不同属性，再按目标 mask 减去 numericBF。`numeric1B5` 由 4E90F0 的方向比较路径提供；ATK+1A4/+1AC 在本目录只保留已确认的偏移，未补猜 PVF 标签名。

随机比较使用 **有符号 IDIV** 的余数：`rate*100 > RNGReturn % 10000` 才暴击，等号不暴击。默认 ATK 参数为 0、其他贡献为 0 的夹具中，随机余数 299 会暴击，300 不会。概率没有在此函数中钳制为 0～100。成功后读取保护全局 10BFE90；攻击方 mask 命中时还乘 numeric6F。函数返回值与 numeric1A5 都记录这次是否暴击。

暴击之后，numeric1A6 控制的字面常量位于 DF5190，实际 float32 为 **1.100000023841858**；差值截断整数记录到 numeric1A7。之后还有百分比和分类倍率。这里的若干指令是 `FST`，只将 float32 写入内存，**不会把留在 x87 栈上的值舍入成 float32**。模型分别保留扩展值与写回值，避免把所有中间结果都强行变成 float32。客户端真实控制字尚未观测。

## 验证与使用

```powershell
G:\ProgramData\miniconda3\python.exe analysis\combat_damage_numeric\capture.py
G:\ProgramData\miniconda3\python.exe analysis\combat_damage_numeric\native_verify.py
G:\ProgramData\miniconda3\python.exe analysis\combat_damage_numeric\build_contract.py
```

`native_verify.py` 生成独立 PE32 算术夹具，复制原始函数及调用方指令到原地址执行。它不启动 DFO。保护浮点 getter、448C10 因子、RNG 返回值、slot320 副作用都由声明的样本替代；原始防御、暴击及所覆盖调用方算术指令保留。284 组对照在显式选择的 x87 53/64 位有效精度下全部一致。`native-vectors.json` 保留每组完整输入、原指令输出、模型输出与匹配结果。

`declared-examples.json` 的数据都是人为声明的数值上下文，适合说明分支与调用 API，不是原客户端实测伤害。`numeric-contract.json` 记录字段来源、阶段边界、当前 PVF 身份和仍未闭合的部分；`evidence.json`、`.bin`、`.asm` 及 REA095/096 的 C 伪代码提供逐项复核材料。C 伪代码用于交叉阅读，浮点栈与操作顺序以原始指令为准。

本目录在 284 组对照通过后保存为检查点，随主任务切换到 DFO.exe / DFO_fixed_v3.exe 脱壳完整性核查而停止扩展；尚未增加独立的合同/字段来源总验证脚本。
