# 60US skill32 动态标量消费链

当前客户端的 `0x73C2B3 → 0x4CAA20 → 0x550150 → 0x550080 → 0x54FC40` 已整理为可执行的保守模型。输入列固定为当前 `ReleaseWave.skl` 的 `[level info]` 第 0 列；结果作为生成物 `20018` 的构造参数，后续转为 float32 并写入实例 `ATK.damage`。这里的输出范围到该标量为止，受击者防御、属性、最终扣血仍属于后续链路。

此目录仅使用 `DFO_fixed_v3.exe`、当前 `Script.pvf`、本地留存的 REA 074–076 证据及 `combat_attackinfo` 的源码绑定片段。原 EXE、PVF 均保持只读，没有使用 `dnf-rebuild` 的猜测公式。全部结果属于静态反汇编与重建模型，尚无原客户端运行时数值观测。

## 可复现端点

`unmodified-baseline-context.json` 明确声明 mode3、secondary predicate 为 false、修正来源完整且为空。它是一组输入条件，没有宣称是已读取到的原客户端内存。

| 显式选择的 SKL 区段 | 表内行数 | Level1 | Level20 | Level30 |
|---|---:|---:|---:|---:|
| dungeon | 30 | 552 | 3056 | 5158 |
| pvp | 20 | 172 | 1954 | 0，索引越界 |

调用点只做 `max(learnedLevel, 1)`，没有在此处按 maximum level 截断。当前 PVF `[maximum level]` 是 20，growtype 上限另有约束；Level30 是验证表/getter 的探针，不能据此认定技能可学习到 30 级。区段由模型调用者显式选择，尚未把它绑定到某次原客户端运行状态。

```powershell
& 'G:\ProgramData\miniconda3\python.exe' 'analysis\combat_spawned_object\scalar\scalar_model.py' --level 1 20 30
& 'G:\ProgramData\miniconda3\python.exe' 'analysis\combat_spawned_object\scalar\scalar_model.py' --section pvp --level 1 20 30
& 'G:\ProgramData\miniconda3\python.exe' 'analysis\combat_spawned_object\scalar\verify_scalar.py'
```

`verification.json` 记录 187/187 项通过：17 个新捕获片段、对应反汇编、8 个复用片段、3 个 REA 证据的身份，当前 PVF/SKL 哈希与每个 level-info 原始字节 token，以及关键分支、修正顺序、越界与环境投影的边界样例。它验证本地证据与模型，未执行原客户端。

## 已闭合的字段与分支

1. `8A1E5B` 解析 `[level info]` 至脚本对象 header `+268` / begin `+26C`；`55326C..55340B` 将所选数据物化为运行时 header `+23C` / begin `+240`。外层列记录跨度 16，内层受保护整数跨度 8。`550080` 对列与 `level-1` 作 unsigned 边界检查，越界在修正处理之前直接返回 0。
2. `4CAA20` 将调用者的 context 参数复制两次。`550080@550117` 比较这两个值，因此本次调用跳过该函数自己的 `448150` 比率分支。`550150` 后续仍有独立的环境投影与比率分支。
3. `54FC40` 依次读取 actor virtual `+428(slot)` 的 0..22 共 23 个来源，每个来源先 primary `virtual+E4()` 的 `+2A0/+2A4` 行向量，再 secondary `virtual+11C()` 的同偏移向量，行跨度 40。queryKind 必须为 1，列必须为 0，skill key 必须匹配 `protected(skill+8)`。actor filter 的 6 为通配；primary mode filter 恰为 2 时要求 `43ABF0(-1)` 成立。secondary 没有这一 mode filter 检查，但每行前要求 source virtual `+12C()`、`+118()` 两个 gate 成立。
4. additive 行按 int32 相加并回绕；percentage 行先把旧值存成 float32，再按 `amount * f32(0.01) * old + old` 经 x87 运算，调用 `C01544` 截断。当前 `CC10AC` 字节为 `0a d7 23 3c`，小于精确的 0.01。因此对 552 加 10% 得 607；加 10 再加 10% 得 618，反序得 617。不能将各行合并为一个总百分比。
5. `550150` 的环境分支要求 `(43ABF0 OR 43A310)`、运行时 maximum `>1`、required range `!=0`、context `!=-1`。`43ABF0` 的 true 模式集合经跳表确认为 `{4,6,7,9}`；`43A310` 来自另一运行时对象状态。
6. 环境分支使用独立的 `protected(skill+178)` 作 reference cap。effective level 为 `min(trunc((context-required)/range)+1, cap)`，没有下限截断。top 在 cap 级并携带 actor 修正；slope 使用 actor=null 的原始列值，cap=1 时采用 row2-row1，其他情况采用截断整数斜率。投影经过显式 float32 存储与 `447FF0`；按需要再应用 `448150` 比率及 `F5E954/F5E958`，保留原生运算顺序与每次 float32 存储。

## 运行时输入边界

`scalar-contract.json` 给出详细字段偏移、公式与证据；`scalar_model.py` 的 `evaluate()` 在必要输入缺失时返回 `status: needs_explicit_runtime_input`、`scalar: null`。调用者需要明确提供以下内容：

- `mode_id`、`secondary_mode_gate`，以及 `modifier_snapshot_complete: true` 和按 slot 升序排列的 `modifier_sources`。明确提供空数组表示无修正来源；每个列出的来源必须提供 `primary`、`secondary` 两个数组。省略的 slot 表示 null 或空来源。
- 有候选修正行时，提供实际 `runtime_skill_key`；有非通配 actor filter 时，提供实际 `actor_filter`。没有把 protected(skill+8) 的赋值来源直接认定为 32。行字段为 `actor_filter, skill_key, column, percent_mode, amount, query_kind, mode_filter`；secondary 有行时还需来源的 `secondary_gate_12c`、`secondary_gate_118`。
- 环境分支可能进入时，提供 `actor_context_stat`；进入后提供独立 `runtime_reference_cap_178`、`rounding_half_global`、被选择的 `environment_global_f5e954` 或 `environment_global_f5e958`。需要比率时提供 `context_factor_448150`，键为被查询 context 的十进制字符串。`448150` 内按模式选择的进一步函数尚未完整重建，因此模型要求因子样本，不默认成 1。
- maximum、required、required range 默认使用已经闭合的当前 PVF 装载值 20、20、3；若运行时有改变，可用 `runtime_maximum_level`、`runtime_required_level`、`runtime_required_level_range` 显式覆盖。reference cap 的完整构造/修改链尚未闭合，不能用 maximum20 或表行数30替代它。

模型把输入视为整个调用期间稳定的快照。原生会多次读取虚函数 gate 和全局状态，调用中的变化尚未建模。浮点实现声明使用 x87 64 位有效数、nearest-even 中间舍入及精确 binary32 存储，`C01544` 在有限 int32 支持范围内建模为向零截断。原客户端 x87 控制字尚未观测；NaN/Infinity、整型除法故障与转换溢出不在支持域内。

## 文件入口

- `scalar-contract.json`：机器可读的当前技能标量消费契约。
- `scalar_model.py`：保守可执行模型，可通过 `--context <json>` 注入明确的运行时快照。
- `endpoints.json`：两区段 Level1/20/30 的完整基线结果与 trace。
- `native-evidence.json`、`rea-evidence.json`：来源身份与可定位证据。
- `static_scalar.py`、`build_scalar_contract.py`、`verify_scalar.py`：分别重新捕获、构建与验证；输出均限制在本目录。
