# 当前 60US：ATK → 鬼斩倍率 → 共同伤害消费链

这里保存当前 `DFO_fixed_v3.exe` 和 `Script.pvf` 的静态证据。已恢复文本字段、运行期 ATK 偏移、`[level info]` 的解析与复制、普通鬼斩的倍率写入，以及共同数值函数的第一段倍率消费。没有恢复或宣称完整最终伤害公式，也没有把这一个技能的结论推广到全角色控制器。

机器可读交付是 `hardattack-attackinfo-contract.json`，原始指令及字节清单是 `evidence.json`。每段 `.bin` 都按 VA 从 EXE 原文件提取；`.asm` 是同一字节段的 x86 Capstone 解码。复制在本目录的 `hardattack.atk`、`hardattack.skl` 保留原始 CP949 字节和换行；JSON 中保留 PVF 条目、CRC 验证、解密后条目 SHA-256 与 token 字节偏移。

## 来源

| 文件 | SHA-256 |
| --- | --- |
| `DFO/DFO_fixed_v3.exe` | `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b` |
| `DFO/Script.pvf` | `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98` |

本轮没有读取 `dnf-rebuild` 来定义语义。当前 EXE/PVF 为裁决来源。

## ATK 文本字段及安装

ATK parser 入口为 **`0x836C20`**，目标地址通过第一个栈参数取得。它先调用 `0x435430` 重置对象。这个 ATK 结构在角色 etc-ATK 数组中的步长为 `0x1B8`；这一点与已有 `combat_native_skill_slots` 的数组物化证据相接。

下表中的偏移均相对 ATK 起点。带 protected 标记的 8 字节成员存句柄/索引；不能将该地址直接当作明文 int/float。`0x404560` 写入受保护数值，`0x402060` 返回 int，`0x4333B0` 返回 float。

| PVF 字段 | ATK 偏移 | 存储/转换 | 当前鬼斩 |
| --- | --- | --- | --- |
| `[damage]` | `+0x0` | protected float | 未提供，reset 为 0 |
| `[absolute damage]` | `+0x8` | protected int | 未提供，reset 为 0 |
| `[damage bonus]` | `+0x10` | protected int | ATK 未提供；技能控制器稍后写入 |
| `[attack type]` | `+0x18` | int：physic=0、magic=1、ignore defense=2 | magic=1 |
| `[weapon damage apply]` | `+0x1C` | protected int，输入先做 `!= 0` | 1 |
| `[elemental property]` | `+0x3C` | 树/集合容器；sentinel 指针在 `+0x40` | dark=2 |
| `[damage reaction]` | `+0xEC` | int：none=0、damage=1、down=2、damage except human=3 | down=2 |
| `[push aside]` | `+0xF0` | protected int | 300 |
| `[lift up]` | `+0xF8` | protected int | 300 |

注意原字段名是 **`[elemental property]`**。`[element]` 是其他语法中的标签，不能替换这里的字段名。`0x82FC70` 映射 fire=0、water=1、dark=2、light=3，其余返回 4。`0x46D830` 在输入 4 时清空集合，其他值插入元素集合。共同数值打包函数会遍历该集合，把值 0～3 变为各自的布尔标志。

普通鬼斩在 `0x731FBE` 取 etc-ATK **索引 0**，于 `0x731FCA` 经 virtual `+0x198` 安装。已恢复的安装链是：

```text
0x5270F0(index 0)
  → Swordman virtual+0x198 / 0x746C30
  → 0x4CF680（临时规范化其他 ATK 成员）
  → 0x4AFA10
  → 0x4EDCD0
  → 0x4A27E0（按字段复制）
  → actor+0x260 的当前 AttackInfo
```

当前 ATK getter virtual `+0x19C` 对应 `0x438650`，直接返回 `actor+0x260`。复制函数 `0x4A27E0` 同样保留 type、element 集合、reaction、push、lift；例如 `0x4A2D01` 开始复制 reaction 与 push，`0x4A2D59` 开始复制 lift。下游受击状态及 HP 处理由碰撞分支独立交付，这里不重述。

## SKL 表确实被原生客户端消费

当前 `skill/swordmanskill.lst` 的 **ID 5** 注册 `Swordman/HardAttack.skl`，对应 state 20 中传给技能查询的 5。`[dungeon]/[level info]` 第一项为列数 **1**，后面 30 项依次是等级 1～30 的第 0 列：250、263、……、618、632。原文件注释将该列标为魔法武器百分比。

这不是只根据注释命名：EXE 数据链也已连接。

1. 技能加载函数 `0x551AD0` 在 `ebp-0x370` 构造 script 对象，于 `0x551B6F` 调用 `0x8A0DA0(script, path, ...)`。
2. parser 的 `0x8A1E5B` 分支识别 `[level info]`，先读列数 N，再按 `token_index % N` 分列，追加 protected int。列容器位于 script `+0x268`、begin `+0x26C`；外层每列 16 字节，内层每值 8 字节。
3. 在加载函数中，这一容器相当于局部 `ebp-0x108`、begin `ebp-0x104`。`0x55326C` 开始把它逐列复制到 runtime skill `+0x23C` 的容器、begin `+0x240`。`0x55340B` 经 `0x4045B0` 复制每个 protected int。
4. state 20 调用 `0x4CAA20`，再转至 `0x550150`、`0x550080`。最后者从 `runtime.begin + col*16` 取列，再从 `column.begin + (level-1)*8` 读取。列或等级越界会返回 0。

`0x550080` 读取数值后还经过 `0x54FC40` 的修改处理；`0x550150` 也包含环境调整。下面的 250、632 示例以未被这些分支修改的当前 PVF 原值为基准。

## 普通鬼斩写入当前 ATK

在 `this+0x2EEC` 为 0 或 2 的分支，`0x732041` 开始取得 skill 5 和技能等级。`0x732074` 的第 0 列查询结果记为 S：

```text
0x73207C: S -= 100
0x73207F: ECX = actor+0x270 = current_ATK+0x10
0x732089: protectedIntSet(ECX, S)
```

因此当前 ATK 存的是 150～532。它不是把 250 当作明文直接写在 ATK 内部。

控制器随后还查询第 1 列，在 `0x7320B1..0x7320D6` 计算并写入：

```text
current_ATK.damage = float32(
    signedIntDivide(query_col1 * 100, current_ATK.damage_bonus + 100)
)
```

这里的 `idiv` 是有符号整数除法。当前 HardAttack 表只有 1 列，所以第 1 列在直接 getter 中越界返回 0，普通无修改的样本写入 base damage 0。不能为当前表凭空补一列独立固定伤害。

`this+0x2EEC == 2` 还会进入 `0x7320DB..0x732176` 的蓄力比例改写。该分支不包含在本报告的“普通、无修改”倍率样本里。

## 共同数值打包和第一段倍率

`0x4EB780` 从攻击者 virtual `+0x19C` 取得当前 ATK。它在 `ebp-0x1D8` 组装连续且未按 4 字节对齐的 numeric 结构：

| 来源 | numeric 偏移 | 读取点 |
| --- | --- | --- |
| ATK protected float `+0` | float `+0` | `0x4EB974` |
| ATK protected int `+0x1C` | byte `+4` | `0x4EB982` |
| ATK type `+0x18` | byte `+5` | `0x4EB98D` |
| ATK protected int `+0x10` | 转成 float 后写 `+6` | `0x4EB999` |
| ATK 元素集合 | byte `+0xA+元素编号` | `0x4EB9AA` 起 |
| 攻击者 virtual `+0x1D8` | float `+0x2F` | `0x4EBC3A` |
| 攻击者 virtual `+0x1E8` | float `+0x33` | `0x4EBC50` |

Swordman vtable 中，上述两个属性 operand 分别经 `0x744A90 → 0x4B5610` 和 `0x744B10 → 0x4B56F0` 获得。后一个从 virtual `+0x344(3)` 返回的 statObject，读取 protected int `+0x278` 与 protected float `+0x280` 相乘，再调用 `0xC01544` 转换；两个 getter 都有 -1500 的下界。上游属性构造和该转换 helper 的最终取整语义尚未在这里恢复。

`0x4EC9F4` 调用共同函数 **`0x8B8650`**，它先经 `0x8B85F0` 选择 base 路径。当前普通武器百分比路径为 **`0x8B79C0`**。其 `0x8B79C8..0x8B7A02` 等价于：

```text
B = numeric.base_damage
if numeric.weapon_damage_apply:
    if numeric.type == 1: B += numeric.type1_weapon_operand  // +0x33
    if numeric.type == 0 or numeric.type == 2:
        B += numeric.type0_weapon_operand                   // +0x2F
B *= 1.0 + numeric.damage_bonus * float32(0.01)
```

当前鬼斩的 base=0、weapon apply=1、type=1，故这一阶段在数学说明上是：

```text
B = type1_weapon_operand × S / 100
等级 1：S=250 → 2.5 倍
等级 30：S=632 → 6.32 倍
```

EXE 中的 0.01 常量位于 `0xCC10AC`，字节 `0A D7 23 3C`，精确 float32 值为 `0.009999999776482582`；1.0 位于 `0xCC1F58`。指令使用 x87 并多次显式写回 float32，因此十进制 `S/100` 是用于说明的数学关系，不能声称是逐位一致的模拟器。

这只是第一段倍率。`0x8B79C0` 后续还继续消费其他百分比、属性和上下文；`0x8B8650` 继续处理元素、防御、随机及其他分支。当前未给出完整最终公式、最终取整、暴击/随机分布或抗性公式。

## 再现与验证

在工作区根目录运行：

```powershell
python -X utf8 analysis/combat_attackinfo/build_evidence.py
python -X utf8 analysis/combat_attackinfo/build_contract.py
```

第一个脚本验证每个导出字节段与指定 EXE 的对应 VA 完全一致并记录 SHA-256；第二个脚本对 PVF 条目做 CRC 验证，并断言当前 ATK 字段、SKL 一列 30 级及 ID 5 注册匹配。没有运行客户端，也没有动态内存快照；所有本轮结论的证据等级均为当前文件的静态数据与代码。
