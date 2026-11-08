# 当前 60US 战斗接触与怪物反应证据

目标为 `DFO/DFO_fixed_v3.exe`，SHA256 为 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`，ImageBase 为 `0x400000`。原始 EXE/PVF 均只读。本目录使用本版本 PE 字节、Capstone 反汇编，以及父代理保存的 REA/Ghidra 反编译交叉核对；本目录的 Capstone 文件自身不冒充 REA provider Evidence，亦不代表运行时观察。与 `dnf-rebuild` 冲突时采用当前目标证据。

机器可读成果：

- `geometry-contract.json`：ANI 攻击盒/受击盒、方向镜像、XYZ 平移、三轴 AABB 的已确认规则。
- `hit-contract.json`：接触资格、消息 `0x13`、Monster 收击、数值计算入口、绝对 HP、死亡标记及状态请求链。
- `monster-reaction-contract.json`：MOB motion/ACT 资源加载、state 0/3/4 的实际资源选择、ACT `[BASE ANI]` 路径消费、死亡链尚未闭合的部分。
- `death-lifecycle-contract.json`：Monster state 5 tick、颜色渐变、特殊模式缩放、`0x17` 移除消息及保护解释器造成的证据边界。
- `scene-destruction-contract.json`、`scene_contract.py`：Generic PassiveObject 的 HP 销毁、ANI/Z/超时条件、移除通知、临时 last ACT 实体和 destroy particle 实际提交链。
- `scene-specialized-contract.json`、`scene_specialized_contract.py`：木桶、洛兰树、洛兰小草三个精确子类的 ID 工厂分派、int/string 消费、计数、HP 重置、动画选择、粒子/音效请求及移除请求。`scene_state_model.py` 是可执行的原生事件输入模型；`scene-model-cases.json` 给出四个确定性输入轨迹。
- `scene-resources.json`、`scene-pvf/`、`extract_scene_resources.py`：当前 PVF 的木桶、洛兰树、洛兰小草和电话亭四个选中实例及其 45 个资源、44 条路径依赖；保留原始字节、CRC、哈希、有序字段、行号和原始路径。资源路径解析是报告工具策略，不能充当原生执行证据。
- `scene_preview_loader.py`、`SCENE_PREVIEW_API.md`：独立预览的只读 OBJ/ANI/参数加载接口与原生事件采样示例；不修改主预览项目。
- `capture-manifest.json`：113 段明确起止的权威静态切片，记录 VA/RVA/文件偏移/字节 hash；其余旧 captures 为探索材料，其文件名或长度不证明函数身份和大小。
- `verify_contract.py`、`verification-result.json`：只读复验入口及结果。目前 364/364 项通过，覆盖 EXE/PVF hash、切片、虚表、关键 rel32、分派表、字面量、时钟导入、45 个 PVF 原始导出、七份 REA 身份及场景计数模型/加载接口的实质分支；不等价于运行时伤害公式或视觉验证。

```powershell
python D:\dnf\60US\analysis\combat_native_collision\verify_contract.py
```

已确认的主链如下。这里命中消息是十六进制 `0x13`，即十进制 `19`；`8C5E64[19] = 8C39B0`，不能误写成十进制 13。

```text
ANI 当前攻击/受击盒
  4AEF80 主 ANI 与攻击方 child ANI
  -> 4E9B10 变换 -> A244E0 AABB 接触
  -> 4EDF70 接触资格/历史/节流
  -> 4EABF0 发送 opcode 0x13
  -> 8C1A30 -> 8C39B0 -> target.slot260
  -> Monster 4F8A30 -> 4B28D0
  -> slot2F8: 4F5C20 -> 4EB780 -> 8B8650 数值计算
  -> HP - 计算结果 -> slot3E8 传入新的绝对 HP
  -> 4AF140 -> slot3EC: 4F58C0 -> 4B4E00
  -> clamp 0..maxHP -> protected(this+1230)
  -> HP<=0: slot3D8 -> 4AD960 -> death flag protected(this+1554)
  -> slot3E0: 4AF540 -> state 3/4/5/-1
  -> 4ED1D0 仅排队 pending state，未立即应用/序列化
  -> 消息5接收路径 -> Monster.slot22C: 4FE290 -> 4BAD60
  -> actual state protected(this+155C)
```

消息接收之外还存在直接 `target.slot260` 调用点 `0x5F36CD`，因此不能把所有收击都描述为网络消息唯一驱动。消息5的完整序列化及接收证据由同级代理保存在其所属目录，不在本目录重复修改。

ATK 安装、命中历史 reset、对象归属的局部生命周期现已由同级 `../combat_hit_lifecycle/history-contract.json` 与 `../combat_hit_lifecycle/README.md` 闭合。本目录 hit 合同引用该结果；仍未证明每个技能何时主动调用这些入口，不能将局部生命周期覆盖范围扩大为全技能。

本版 Monster 资源由 `887E60` 的 MOB parser 读入模板，再经 `500530` 创建运行时资源。受击 motion 1/2 为 `+124C/+1250`，down 为 `+1254`，overturn 为 `+1258`；对应 ACT 为 `+12EC/+12F0/+12F4/+12F8`。ANI getter 的“motion 非空则返回 motion，否则返回 ACT.currentANI”不等于执行时总是优先 ANI：

- state 3：先要求 slot374(variant) 可得到 ANI，再选择存在的 damage ACT；不存在 ACT 时设置 damage ANI。
- state 4：优先 down ACT，然后 down ANI，最后 fallback 为 **sit ANI**（slot36C/`+1248`），不是 waiting。
- state 0：waiting ACT 可用时使用 ACT，否则使用 waiting ANI。

ACT 的 `[MOTION]/[BASE ANI]` 已闭合至当前 ANI：`A3F0E0` 使用 `830590("%s%s", base, actPath)` 得到 ACT 所在目录前缀；`A3F267` 读 BASE ANI 字符串，`778880` 进行目录前缀与原字符串的拼接，写 parsed `+4` 的 wstring；`A321B0` 经 `4936D0 -> A29AD0` 创建 ANI，写入 ACT `+20`。这两个路径 helper 本身未执行 `..` 折叠；后续打开资源时的规范化位置仍待确认。

Monster 的 `[last action]` 已确认预载：模板 `+748` -> `501C99` ACT 构造 -> entity `+150`，ACT 类型 `+2CC = 11`，并挂 owner。**Monster 预载尚未证明实际执行。** state 5 当前看到的是归属回调、声音、关闭攻击/受击 gate、暂停当前 ANI及运动复位，不能直接把它叫作 death ANI 播放，也不能把 `4AC500` 误称死亡动画选择器（它是归属对象解析器）。下文 PassiveObject 的 stored-path 执行链另有证据，不能反推所有 Monster 使用同样机制。

死亡状态的后续链已收紧至以下范围：

```text
49C046 -> Monster.slot188 -> 4FB720
  protected(this+155C) == 5
  -> byte remap4FCE84[5] == 1 -> table4FCE68[1] == 4FCB2A
  -> 4FCB2A..4FCD6C: 按 slot5A0 / mode19A8 渐变颜色，特殊模式可缩放当前动画
  -> elapsed >= this+1E18 且 byte(this+1E8)==0
  -> slot654 -> 4FA1D0
  -> 4FA1F0 -> 13BAA5F -> 12EE7C9 保护解释器（尚未解码）

独立可见的移除请求 / 接收链：
499120 (Monster.slot164)
  -> message 0x17 (=十进制23)，携带slot3C/slot40对象标识
  -> byte(this+1E8)=1
8C1A30 -> 8C5E64[23] == 8C4D73
  -> 50B820解析对象 -> object.slot60(0)
  -> Monster4EFC80 -> AuraMaster分支或byte(this+184)=0
```

`4FA1D0` 的可见原生片段 `4FA222..4FA2E2` 在局部 gate 通过时优先 down ACT，否则 down ANI，并使用 `protected(this+1704)` 设置索引；可见尾部 `4FA7FD..4FA83D` 在本地归属条件成立时调用 `slot164(0)`。但入口经过未解码的保护解释器，尚未证明正常入口可达这些片段，不能画成一条无条件闭合路径。REA `ev_f12cbd9cf3515a2bd49d1d6be29f521879abba0515f70fd6f70e9aa6d0681ace` 的 `analysis/rea/050-monster-death-callback.c` 同样只反编译出入口调用 `FUN_013baa5f`。

`B099B0` 已确认是带边界的线性插值。普通 state 5 分支在寿命尾部使用 `lerp(255,0,elapsed+100-lifetime,100)` 计算 alpha；slot5A0 为真时使用 `lerp(255,100,...)` 填充 RGB 并保留 alpha。特殊 mode 2 分支还使用 float32 的 `1.05` 增量因子和 `1.2` 上限控制动画缩放。这里的时间仍记为原生计数，转换仍经过 x87 / `C01544`；尚未建立 web 毫秒、`Math.round` 与客户端数值完全相同。

精确 Monster 虚表的 `slot38=8E49B0` 是 `xor al,al;ret`，所以 `4F2A40` 中 `slot38 && last action路径非空` 的早退在该虚表本身不会成立；派生类型覆盖应另查。对象 `+150` 的已确认读点 `49BB48` 是 ACT 析构，不能当成动画播放。清零 `+148/+14C/+150/+154` 的初始化函数为 **498EC0**；前邻 **498E60** 是颜色 mask helper。

切片范围与 Ghidra 函数体成员不是同一个概念。`4BAD60`、`4BC7D0` 的 Ghidra body ranges 不连续且省略 switch case 成员；manifest 所保留的是包含 case 的外包字节区域，不能把其长度直接称为 Ghidra function body 大小。旧捕获可能跨函数或从指令中间开始；引用结论优先使用 manifest 中的明确切片。

几何合同的关键边界：盒子结构为六个受保护 float32 槽，每槽物理 8 字节；direction==0 镜像 `x=f32(f32(-x)-width)`。AABB 分离使用严格 `>`，因此边缘接触计为相交。`CAB8E8` 的 float64 epsilon 是 `2^-23`。零 extent 拒绝，非零负 extent 不会在该前置判断自动排除，也没有 min/max 归一化。预览可限制有限正 extent，但应标注为预览端输入校验。x87 控制字未运行时核对，默认 nearest-even 仍是重建假设。

Generic PassiveObject 的场景销毁链已闭合至如下范围。精确 RTTI 为 `.?AVCNRDPassiveObject@@`，虚表 `CBB7D4`；不能把所有按 `int data/string data` 配置的场景子类归入同一行为。

```text
[hp max] -> parser884E7C -> protected(template+AC)
[hp destroy] -> parser884EAA -> byte(template+61)=(integer==1)
49F4D0 -> maxHP+528、HP+524、hp_destroy byte+558

accepted hit -> slot260=49F310
  -> local49C090 -> slot2F8=4EB780 -> oldHP-damage
  ->49F090 int vector [damage,newHP,x,y,z,attackerID1,attackerID2]
  ->slot28C(state1) ->slot290 立即提交
  ->slot22C=49D7D0 state1 ->直接写newHP至+524（该写点不clamp）
  ->slot348=49D0E0
  ->hp_destroy && maxHP>0 && HP<=0 ->slot164(0)=49E840
  ->499120 ->message0x17 ->receiver.slot60(0)=5E14E0 ->byte184=0
  ->50CA50 检查slot64=407BB0读取byte184，false进入清理分支
  ->50C6F0 ->50C765 removed.slot15C(removed)
  ->4A0840 自身移除通知
```

这里的 HP 条件与 REA065 `ev_71073ca6199bb66f0592e1439ec6181103c2825af0ce7bbc77ce93f50e88d673` 一致。网络消息是一个确认入口，其他直接调用移除或 active setter 的路径仍存在，不能描述成所有清理都必须联网。`50C6F0` 还会向其余对象发 `other.slot15C(removed)`，但下面的 last ACT／particle 发射要求回调参数等于自身。

`[object destroy condition]` 的当前枚举已由 parser 与消费者逐项对应：

| 源字符串 | enum | `49D960` 条件 | 原物件 |
| --- | --- | --- | --- |
| `[on end of animation]` | 0 | 当前 ANI `+13A!=0` | 发移除请求 |
| `[z pos equal zero]` | 1 | `slot9C()==0` | 发移除请求 |
| `[time limite]` | 2 | `int32(now-start)>int32(limit)` | 发移除请求 |
| `[not destroy and z pos equal zero]` | 3 | `slot9C()==0` | 保留 |
| 未识别值 | -1 | 跳过该函数剩余处理 | 此函数不移除 |

所有触发还要求 `byte+5A4==0`。枚举由 template `+E0/+E4` 复制至 runtime `+55C/+560`；限时整数 template `+12C` 复制至 `+5BC`，`+5C0` 为创建时刻，`+5C4` 为本次时刻。这里 IAT `140F05C` 已在 PE 导入表确认是 **kernel32!GetTickCount**，因此这条场景限时链的单位可确认是 Windows 毫秒；需保留 32 位差值和有符号严格 `>`，不混同前述 Monster `B06F00` 尚未确认的计时缩放。REA064 `ev_6b3f2403afd092bb7e58538736203da2adeea8d193e3c83b0d87a107f8b99fb6` 的完整 body 为 `49D960..49DC6A`。

`[destroy action]` 的 enum 0 是 `[only destroy]`，1 是 `[object create after destroy]`。本地归属判定通过且未标记时，enum 1 按 `[add object index]` 的顺序，通过 `4E9EA0` 创建各 ID；enum 0 只设置标记。之后调用移除的代码位于该本地归属分支之外，enum 3 例外。自身移除通知中还有一次受相同 `+5A4` 标记保护的生成兜底，不能把条件触发与移除通知各算一次独立生成。

PassiveObject 的 `[last action]` 执行已确认，但实现不同于“在当前实体直接选择预载 `+150`”：

```text
884B16 解析 [last action] ->template+5C
49F9C2..49FA73 预载ACT至+150，同时把原始路径保存在+7F4
4A0840 self通知 && storedpath+7F4非空
  ->4A08DC/F1 重新4A3900(basepath,storedpath,0)创建ACT
  ->A2D020挂owner
  ->4A0935 ->4A3820(ACT,1,0) 创建0x870临时实体
  ->虚表CCEC5C，RTTI .?AVCNRDPooledObjectAddAction@@
  ->49F240 ->slot70=407BF0 ->defaultACT+14C
  ->currentACT为空时 slot100=4E9480 ->499F10 ->currentACT+148
  ->50DD70加入场景，复制原物件XYZ与方向
  ->常规49BE80/A31240推进ACT
  ->该临时实体slot20=49D220，ANI ended后slot60(0)
```

`[destroy particle]` 的 parser `884C73` 读路径至 template `+6C`；`49FD8E..49FDFE` 构造 `CNRDObjectParticleCreater` 至 runtime `+794`。`4A0840` 的 self 分支调用 creater `slotC(0)`、`slot28(sourceXYZ)`、`slot5C(outvector)`，在 `4A0A6A` 通过 `50E060(source,2,0,outvector,0)` 提交。这个分派闭合并不证明粒子的速度、发射分布、碰撞、寿命或渲染已经恢复。REA069 `ev_d522e10c7b5fd580a6d75359efba9bdbfc800ded43c81783074f5565ea944821` 的完整 body `4A0840..4A0D94` 与本地切片相符。

当前 PVF 中，电话亭声明 `basic action`、5000 HP、`hp destroy=1`、`TelephoneDestroy.ptl`；`last action` 行实际已注释，报告不将其视作有效依赖。木桶、洛兰树、洛兰小草则声明 basic/etc ANI、按顺序的 int/string data 和 PTL，未声明通用 HP。专用控制器会从 int data 补充 HP 或计数，具体如下。`scene-resources.json` 保留这四个实例及全部已解析依赖，不能据资源齐全声称运行时破坏效果已验证。

Monster 的 `slot15C=4F4440`，与上述 `4A0840` 不同；其受保护死亡入口和 last action 执行缺口继续保留。REA053 `ev_2a43bf6ec4f4c0448af3cf08236d51460c7335b467bb6ee529e628ccb6a2e260` 现已独立反编译出 Monster state 5 tick 的消费者，但 FunctionManager 的 body ranges 省略 switch case 区域，须与本地表分派/切片分开理解。

尚未建立：完整 `8B8650` 伤害公式、所有 ATK 字段单位、全技能主动安装 ATK/重置历史入口、state 4 完整运动/落地/起身积分、overturn 的实际执行跳转、Monster last action 的实际分派、选定场景计数子集以外的延迟控制/附加输出与 PTL 内部、完整清理/奖励事务，以及客户端运行时视觉一致性。预览应分别显示几何接触、接受命中、扣血与状态选择，不能用碰撞盒相交替代后续全部判定。

## 木桶、树、草的专用消费链与可执行模型

`5E8500` 按 OBJ ID 分派。ID 221 的木桶走 `5E904D -> 490830`，RTTI 为 `CNMapObject`，虚表 `CCC88C`；ID 224 的树走 `5E85F6 -> 5E70C0`，RTTI 为 `CNActionTree`，虚表 `D4D26C`；ID 244 的草走 241..250 分支 `5E8685 -> 5C8660`，RTTI 为 `CNCutableGrass`，虚表 `CF10F4`。两个低 ID case 的 byte/target 表为 `5F1620/5F1604`，均已复验。本目录的精确类名来自当前二进制 RTTI。

OBJ parser 在 `884D12/884D76` 将 `[int data]`、`[string data]` 按顺序存入 template `+84/+94`。`49FC38..49FC57` 分别拷贝至实体 `+230/+548` 向量，实际元素 begin 为 `+234/+54C`。木桶/树共有的 `5F6640` 将 int[0] 设为计数相等触发值、int[1] 为计数上限、int[2] 为到达上限后销毁开关、int[3..5] 为粒子 XYZ 偏移、int[6] 同时写入 HP 与 maxHP。原生 size guard 是 `>=6`，但随后读第七项；所选当前 PVF 都有七项，模型拒绝短向量，未补写其越界语义。string[0..2] 构造三个 PTL creator，string[3..5] 为三个字符串槽；已确认 hit 使用第 1/4 项、destroy 使用第 2/5 项（均从 0 开始），第 0 项的发射不在本子集覆盖范围。

木桶/树的 `slot260=5F5FB0` 可先按攻击方 ATK 的明确 gate 派发受击 PTL/音效，再调用通用 `49F310`。state 1 写入新的绝对 HP 后调用 `slot348=5F5B40`：当 HP<=0 且 count<limit，count 加一，调用 `slot388=5F5AE0`，随后 HP 恢复到 maxHP。counter 等于 int[0] 时触发 `slot394` 并可选 etcANI0；否则调用本次两个精确虚表上的空 stub。最后 count>=limit 且 int[2] 非零时进入 `5F5E80`，派发 destroy PTL、播放销毁声音，local authority 再调用 `slot164(0)`。请求移除不等同于已经接收到移除/清理事件。

当前木桶 int data 为 `[1,1,1,0,0,30,1]`：一次明确的原生 HP<=0 写入会把 count 变为 1、HP 重置到 1、派发 `BarrelDestroy.ptl`（Z+30）、请求 `WOOD_CRASH` 并请求移除。当前树为 `[1,2,0,0,0,100,1]`：第一次 HP 耗尽使 count=1，选择 etcANI0 `ActionTree2-1.ani`；该当前 ANI 声明 `LOOP=1`。第二次使 count=2，之后不再增加；销毁开关为 0，因此本控制器不请求移除。不能将此概括为“每击重新播放树摇动”。

只有 `5F5B40` 的另一分支选 etcANI1 时才设置 `+93C=1` 并 reset ANI。tick `5F6C42..5F6C8C` 在该标记存在且当前 ANI `+13A==1` 时清除标记、reset 并恢复 basic ANI。counter 分支选择 etcANI0 不设置该标记。当前树的 etc 列表只有一项，所以模型不会给这棵树额外补上结束恢复。

草的计数不依赖通用 maxHP。`5F33C0` 先调用 `49F310`，无论其返回值都会经 `5C86F0` 给 `+874` 加一。有 etcANI0 时阈值为 2，否则为 1。阈值前选 etcANI0，达到阈值调用 `slot164(pass_all_flag)`；两种分支都可发射 string[0] PTL。当前草第一次明确 accepted contact 选 `SmallGrassDestroyLorien.ani`（LOOP=0），第二次请求移除。这个 destroy ANI 结束本身不会让该控制器移除物件。PTL 的 Z 是 int[0]=32 的**绝对值**，不是加到草的现有 Z；本模型专门覆盖了非零源 Z 的用例。

草的 etcANI1/2 用于靠近对象时的弯折；`5F3300` 接受原生方向结果，4 选 basic，0 选 etcANI1，其他值选 etcANI2，并 reset 所选 ANI。受击后关闭自动弯折标记。pass all 的草在 `5F3500` 内还会临时启用受击盒，扫描对象，调用攻击方 `slot240` 接触判断；成功后注册对象并直接调用自身 `slot260`（`5F36CD`）。该局部路径未显式调用 `4EDF70`，因此不能直接把网络命中资格模型套到这个循环上。

REA077..080 分别独立核对 `5F6640`、`5F5FB0`、`5F5B40`、`5F3500`，Evidence ID、来源 digest 与原生 body ranges 都绑定在专用合同内。草 tick 的 REA ranges 在 `5F3636..5F363F` 有 alignment gap，本地 enclosing 切片单独保留。

模型入口如下，均要求外部已经提供原生事件；它既不计算伤害，也不把 AABB 相交自动升级成 accepted contact：

```python
from scene_state_model import SceneState, selected_config

barrel = SceneState(selected_config(221), xyz=(100, 200, 0))
barrel.on_native_hp_write(0)      # 明确传入新的绝对 HP，不能传 damage delta
barrel.on_native_removed()       # 后续真正收到自身移除通知

grass = SceneState(selected_config(244))
grass.on_native_accepted_contact()
grass.on_native_frame_ended()    # 草不因此自动销毁
grass.on_native_accepted_contact()
```

运行 `python -X utf8 scene_state_model.py` 可生成四份确定性输入轨迹：木桶、树计数上限、草两次接触、非 local 木桶。验证还用一个明确标记为合成配置的例子覆盖 etcANI1 结束恢复分支，不冒称为额外当前资源。模型只输出 ANI 选择、原生 HP 重置、counter trigger、PTL 派发请求、音效请求和移除请求；PTL 内部发射分布、粒子运动、碰撞、寿命和渲染继续为 unknown，不绘制替代粒子。
