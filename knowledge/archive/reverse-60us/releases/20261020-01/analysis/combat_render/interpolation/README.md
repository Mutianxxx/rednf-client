# 60US ANI 连续插值消费链

本次将工作集中到当前客户端渲染。已恢复并接入连续位置、缩放、旋转和 RGBA 插值；伤害公式未扩展。
实现位于 [renderer.js](../../../combat-preview/web/renderer.js) 的 `sampleSpriteStyle`，播放界面可用“ANI 插值”开关对照离散帧。

## 当前客户端证据

原 v3 SHA256 为 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`，原件路径为 `analysis/unpack_attempts/001/launcher_test/DFO_fixed_v3.original.exe`。
当前安装 v4 的下列静态范围均与原件一致。原字节、VA、文件偏移和 SHA256 见 [evidence-index.json](evidence-index.json)。

```text
ANI [INTERPOLATION]
  A29191 reads integer → keyframe+20 boolean
  A27870 installs frame / frame start and next deadline
  66F900 copies frame+20 → ANI current snapshot+A8+20 = ANI+C8
  A27F60 calls frame advance A27DC0, then pose updater A24950
  A24950 updates snapshot position/rate/angle/RGBA
  A26990 draws snapshot+A8 through A23D60
```

`A24950` 先检查当前 snapshot 的 `+20` 开关、`ANI+13A` ended 和非空帧表。
当前索引 `ANI+124` 决定来源帧；目标通常为下一帧。最后一帧在 `ANI+130` 为零时保持原样，非零时选择第0帧作为目标。

实际时间输入为：

```text
current = parent ? parent selected clock (4CAA00) : ANI+8C
t = current - ANI+128
d = ANI+12C - ANI+128
```

| 连续量 | 写入 snapshot | 当前原程序行为 |
|---|---|---|
| IMAGE POS x/y | `ANI+B0/B4` | 分别调用 `473F20`，对完整插值结果向零截断 |
| IMAGE RATE x/y | protected `ANI+B8/BC` | 解码两端值，调用 `B099B0`，落栈为 float32，再按保护格式写回 |
| IMAGE ROTATE | `ANI+C0` | 原角度直接数值插值，落栈 float32，不走最短角、不归一化 |
| RGBA | `ANI+C4` | 四个独立字节调用 `473F20`，取结果低8位重新打包 |

`B099B0` 的分支顺序为：

```text
t >= d : target
t <= 0 : source
otherwise : source + (target-source)*t/d
```

`473F20` 将两端整数转 float 后调用上述 helper，再调用 `C01544` 截断。
因此负坐标 `-3→0` 在四分之一进度的结果是 `-2`，不能保留 `-2.25`，也不能简单对增量先截断。
透明度 `0→255` 在一半进度是 `127`，不是四舍五入后的128。

这一更新器不对图片指针/图片帧号、GRAPHIC EFFECT、ATTACK/DAMAGE BOX 插值。预览仍以来源关键帧读取这些离散资源和碰撞盒。
默认字段及 snapshot 拷贝另保留 `46E390`、`66F900` 的原字节；没有用前一帧的任意属性填补当前帧缺项。

## REA 复核

本轮实际通过 REA 的 Ghidra provider 对原 v3 备份调用了 `open_binary` 和三次 `analyze_function`，完整返回已保存，分析会话已关闭：

| 函数 | 完整 Evidence | 导出的反编译文本 | Evidence ID |
|---|---|---|---|
| `A24950` 当前姿态更新 | [002-current-pose.json](002-current-pose.json) | [002-current-pose.c](002-current-pose.c) | `ev_3ffcf83d3186fc6604fc0875302c104b32e7bdc08b8526c04bf2efce617a7f71` |
| `473F20` 整数插值包装 | [003-integer-lerp.json](003-integer-lerp.json) | [003-integer-lerp.c](003-integer-lerp.c) | `ev_be0751c3ea40e8f82eb388c82a49c0e09455628824714bd49160a78f9e89e194` |
| `B099B0` 浮点插值 | [004-float-lerp.json](004-float-lerp.json) | [004-float-lerp.c](004-float-lerp.c) | `ev_660c8d1343152f17a854226f940dba06271ccccbdf35b49ada97793a9a5c3aa3` |

反编译中 `A24950` 的保护浮点参数仍显示为原始整数异或表达式，`473F20` 也没有恢复正确的整数返回类型；这些类型以原汇编和下述原指令执行核对为准。导出的 `.c` 是分析器生成的伪代码。
REA 当前使用已记录的 Ghidra 分析配置，禁用了 `Reference`、`Decompiler Parameter ID`、`Decompiler Switch Analysis`；本次三函数的局部结论由原字节补证，不以调用引用列表证明全程序覆盖。

## 原指令执行核对

[verify_interpolation_native.py](../verify_interpolation_native.py) 将完整原始 `A24950`、`473F20`、`B099B0`、`C01544` 保留在原 VA 的独立 PE32 中执行。
仅构造输入帧、保护 key、时钟、输出缓冲和标准输出；没有启动/附加 DFO，也没有修改用户游戏。

[native-vectors.json](native-vectors.json) 保存 12 组输入在 x87 64/53位两种精度下的24个输出，均与模型一致。
覆盖开始前/开始/中途/末端/结束后、关闭插值、ended、非循环末帧、循环末帧，以及负坐标和整圈角度。
检查了 image pointer 和 effect 在更新后保持原值。该验证采用合成 key 和时钟，不是原游戏运行记录，也不穷尽极端浮点输入。

浏览器 [check_interpolation.mjs](../../../combat-preview/tests/check_interpolation.mjs) 又将同24个原指令输出与 JavaScript 采样逐项比较，并实际加载：

- `character/swordman/effect/animation/soulbringer1.ani`：前500源DELAY单位的缩放/淡入；250时 alpha127。
- `passiveobject/monster/goblin/animation/flybomb.ani`：150源DELAY单位内由0转到6.28；75时约3.14，不丢失整圈。

浏览器来源、参数和图像身份见 [interpolation-browser.json](../../preview-validation/interpolation-browser.json)。

## dnf-rebuild 的参考范围

已只读检查 `rep-player-1031-pvf/src/pvf_script_preview.cpp` 的名称读取、`pvf_preview_scene.cpp` 的插值诊断，以及1031交接包 `monster_demo/src/resources.cpp` 的采样实现。
精确文件身份保存在 index 的 `references`，没有修改这些项目。

参考实现让位置、RGBA 保持 double 混合值；当前60US原指令在这两处调用整数截断 helper。
本次采用当前60US字节和原指令执行结果，没有直接移植1031的浮点结果。整圈旋转保留这一行为在当前客户端也得到了独立核实。

## 时钟与覆盖边界

预览在现有 source-DELAY、rate100 的资源时钟上应用上述局部插值。它尚未绑定原角色有效速率、游戏时钟通道、暂停、hit pause 或技能阶段调度。
“循环末帧目标为第0帧”已核对，但完整实体的自动循环、生成、解绑和移除时序仍由外层执行器决定。
装备层沿用已核对的身体帧/延时；冻结参考主体不执行时间插值。

本次不增加完整技能控制器数量，不声称恢复了原始C++源码或完成原游戏视觉验收。剩余优先项是实际播放时序、其他图形效果和原点模式、视觉生成物生命周期、怪物受击死亡及场景粒子。

复验：

```powershell
python -X utf8 analysis/combat_render/verify_interpolation_native.py
python -X utf8 analysis/combat_render/build_interpolation_evidence.py
node combat-preview/tests/check_interpolation.mjs
```
