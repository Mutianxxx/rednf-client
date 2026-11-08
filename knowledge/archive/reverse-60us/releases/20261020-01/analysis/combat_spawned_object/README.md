# Swordman skill32：当前 60US 的技能生成对象链

本目录闭合了一个明确的技能实例：当前 `skill/swordmanskill.lst` 的 **32 → Swordman/ReleaseWave.skl**，通过当前客户端的成功消费分支请求 state10，并在 **mode0、phase0** 生成 **passiveobject 20018 / 0x4E32**。这是角色周围的波动攻击对象；不能因为公共状态使用 throw motion，就把它重写成向前移动的投射物。

目标 EXE 为 `DFO/DFO_fixed_v3.exe`，SHA256：`a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`。当前 PVF 为 `DFO/Script.pvf`，SHA256：`23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98`。原文件只读。结论来自当前 PE 字节、REA/Ghidra 和当前 PVF，不使用 `dnf-rebuild` 的猜测补齐。这里没有恢复原始 C++ 源码，也没有声称运行时观察或完整脱壳。

机器可读及可执行入口：

- `preview-contract.json`：技能 ID、请求向量、phase0 触发、生成对象参数、工厂/注册/加载链、三个独立 ANI 时间轨。
- `resources.json`：11 份当前 PVF 资源的源哈希、CRC 校验、注册行及字节范围、字段原序和完整帧字段。
- `pvf/`：对应解密后原始 CP949 字节和单独 UTF-8 阅读副本。
- `evidence-index.json`：48 段 PE 原始切片、对应 SHA256、已保存的 REA Evidence ID，以及原先验证过的成功请求路径。切片范围不是函数大小证明。
- `preview_contract.py`：运行有限范围的资源时间轨和世界攻击盒采样，不合成接受命中、扣血或怪物状态。
- `verify.py` / `verification.json`：当前 **125/125** 复验通过，覆盖源哈希、切片、虚表、原生跳表/字面量、当前数值注册、ANI 时间边界和门控分离。它不证明实机画面相同。

```powershell
G:\ProgramData\miniconda3\python.exe analysis\combat_spawned_object\preview_contract.py --time 0 80 399 400 490 --xyz 100 200 10 --direction 1
G:\ProgramData\miniconda3\python.exe analysis\combat_spawned_object\verify.py
```

`time=0` 定义为已应用 state10.phase0 的本地预览原点。时间值采用当前 ANI 的 DELAY 累加；目标客户端的实际时钟、传输和 tick 对齐仍需运行验证。`--spawn-gate-failed` 保留两个角色视觉轨，停止生成攻击实体，这对应原生视觉调用位于生成对象归属门之前的事实。

## 成功技能请求与准确触发阶段

`0x72B7C6` 调用角色 `+0x768` 消费技能 32，检查 AL，失败跳 `0x72B8C8`，成功分支才在 `0x72B8B0` 调用 `+0x28C` 请求 state10。向量为：

```text
[0, 0, 32, 0, return(54FF60@72B849), 1, 4, 4]
 phase mode skill duration0 duration1 throw-index controls
```

原先完整 state10 的字段/阶段合同在相邻 `combat_cast_state/`。本技能通过 throw index1 选择 CHR 的 Summon1/Summon2 阶段资源；这不等于应该把视觉波动或攻击生成延迟到 phase1。

```text
Swordman handler7307B0
  -> state10共享apply 4C5730 ->4DE370
  -> post-shared state10 branch73B42C: mode(this+2428)==0
  ->73C147: protected(this+242C)==32
  ->73C15B: protected(this+2420)==0
  ->角色+558，懒加载并挂载两个视觉ANI
  ->73C245: 49C090归属比较通过
  ->73C2C0: virtual+2B8(20018,dynamicScalar,0,0,0,0,0,4,0,0,0,0,0)
```

`49C090` 的精确已知条件是 `actor.virtual+160() == global[104F1D4]` 且该全局非空。生成包装 `4EA4D0` 还检查 `+168==false`、`+64==true`，并再次检查归属。这里不擅自把未命名 gate 写成无敌或霸体。

`4EA4D0` 的 `ret 0x34` 证明有 13 个栈参数，不能采用反编译器漏掉尾参数的推断签名。direction 参数 4 在包装中替换为角色 `+C0()`；本技能 dx/dy/dz 全为 0，因此请求位置来自角色当前 XYZ，没有投射速度字段。OBJ 的 `[floating height] 1` 按原字段保留，不能无证据加成 `spawnZ+1`。

## 从生成请求到当前 OBJ 注册

```text
Swordman virtual+2B8 =4EA4D0
  ->空结构路径4EA601 ->4E9EA0
  ->writer opcode0x15(十进制21)
  ->8C1A30: table8C5E64[21]=8C4248
  ->8C4395:5E8500(objectID,dynamicScalar)
  ->5EA005 ->5EA482 ->5EA79A
  ->5F1F54[(20018-0x4E2F)==3]=5EA85E
  ->alloc0x870 ->5CE740
  ->490720 ->4A0DA0(id,dynamicScalar)
  ->map10BE3E8[id]取确切注册路径 ->49F4D0(path,dynamicScalar)
```

这是静态的消息写入/接收字段链，不代表已观测到数据包。工厂很大，最初 provider 对 `5E8500` 的请求失败；本目录的选择分支由实际 PE 字节和跳表复验。不得引用那个失败请求作为成功反编译证据。

原生启动处 `44ADDB` 明确压入 **`PassiveObject.usa.lst`**，`44ADE0` 压入 **`PassiveObject/`**，然后调用 `882A50`。该函数经 `831AD0` 读取数字/路径行到 `10BE3E8`。所以不是按相似文件名猜注册表。当前 USA/general/jpn 列表的第 976 行和 old 列表第 500 行一致映射：

```text
20018 `Character/Swordman/ReleaseWave.obj`
```

当前 OBJ 无 ACT 标签。其初始资源是直接 ANI 和 ATK：

```text
[basic motion] `Animation/ReleaseWave.ani`
[attack info] `AttackInfo/ReleaseWave.atk`
```

加载管理器实例 `10030E4` 在 `44B159` 通过 `A614D0(type2)` 创建。`B7CE30` 的 load slot+8 经 `E4C4F4+8=A618E0`，type2 跳到 `A619C2`，在 `A619F8` 调用 OBJ parser `884720`。该 parser 将 basic motion 写模板 `+34`，attack info 写 `+70`。`82F710("%s%s",base,objPath)` 保留最后目录分隔符之前的路径为模板 `+A4`，相对 ANI/ATK 由该目录消费；这里没有额外宣称 `..` 归一化。

运行时 `49F4D0` 使用 `+A4/+34` 调 `472A60→A29AD0` 创建初始 ANI；`+6C=407BC0` 写 basic 指针 `entity+118`，current 指针为空时调用 `+F0=49D070→49B250` 写 `entity+104`。`+A4/+70` 经 `B7D230` 取得 ATK，并用 `4A27E0` 复制到 `entity+5DC`。

动态 scalar 不是无条件复制 SKL 第一列。原生调用为 `skill32.4CAA20(0,max(level32,1),actor,actor.virtual+1D0(),0)`，再转给 `550150`；完整计算仍待解释。接收值由 `5C77B0` 转为 float32，写受保护的 `entity+5DC`。当前 SKL 的 dungeon `[static data] 600`、level-info 每等级一列及其数值已原样导出，不借注释替代完整 native 公式。

## 视觉轨和攻击轨必须分开

| 轨道 | 准确资源 | 当前帧与 DELAY | 图像/判定 |
|---|---|---|---|
| actor 附加视觉1 | `character/swordman/effect/animation/releasewave1.ani` | 7×70，累加490 | 前6帧图像 ReleaseWave1.img，末帧 IMAGE 为空 |
| actor 附加视觉2 | `character/swordman/effect/animation/releasewave2.ani` | 6×70，累加420 | 前5帧图像 ReleaseWave2.img，末帧 IMAGE 为空 |
| passiveobject20018 | `passiveobject/character/swordman/animation/releasewave.ani` | 5×80，累加400 | **每帧 IMAGE 路径为空；每帧有 ATTACK BOX** |

两个视觉路径是原生 UTF-16 字面量 `D7C750`、`D7C708`，分别由 `73C197`、`73C1D9` 传给加载器。加载基目录来自角色 `+244` 的字符串；`4334B0` 是字符串访问器，不应误称其本身打开资源。加载结果存 `actor+2FB8/+2FBC`，通过 `+F8` 附加；第一个调用首参数 +1，第二个 -1，其完整参数已保留，未给这两个数编造层级名称。

不能把对象 ANI 的空 IMAGE 字段自动改成 `ReleaseWave.img`，也不能把角色视觉 ANI 当作攻击对象的 ANI。两者具有不同持续时间和不同调用链。对象的每帧攻击盒均为：

```text
x y z width height depth = -84 -50 0 168 100 234
```

当前 ANI parser `A28410` 把帧攻击盒写 keyframe+38；`A27F60` 更新当前 ANI+E0；`4AEF80→4E9B10→A244E0` 执行主/child ANI、方向镜像、XYZ 平移与 3D 相交。具体 float32 和接触边界规则引用相邻 `combat_native_collision/geometry-contract.json`。

当前 ATK 明确为 magic、攻击敌人、无元素、damage reaction down、push aside400、lift up400、hit wav `R_SHOCKWAVE_HIT`。这些字段是攻击请求参数，不能只凭盒子相交就立即等价成怪物倒地或最终数值伤害。命中资格、目标历史、消息0x13、HP及反应链引用 `combat_native_collision/hit-contract.json`。

尤其不能在每个 ANI 帧自动清空“已命中目标”。父分析正在固化的历史链显示，历史可能通过 canonical owner 共享；原生清空入口是 ATK 安装和显式 reset 等控制点，帧变更本身不是本合同确认的 reset 事件。

## 生命周期与证据边界

最终对象 vtable 为 `D057D4`，tick+188 为 `5CE7A0`。它先调用通用 `49DC70`，再读 current ANI+13A；该字节非零且对象+1E8尚未设置时，调用+164=`49E840`，后者入口调用 `499120` 发出移除消息0x17（十进制23）。

REA060 的 `A27DC0` 已确认：非循环 ANI 在末帧到期后写 ended+13A=1，保留最后一帧。故本预览可以在攻击 ANI 的归一化400期限后停止攻击对象；两个视觉轨保留最终空图帧。具体原生时钟、速度修正、tick 调度和数据包到达顺序仍没有实机验证，不能把本地 DELAY 采样结果称为逐帧还原。

这个实例可以用于预览中的三个轨道和几何接触验证。尚未完成 `550150` 的完整 scalar 公式、所有 native 命中 gate/目标历史、怪物移动积分、死亡/破坏和 UI；这些未知项不会用同名技能、现代格式或重建项目的猜测填充。

