# 60US ANI 旋转、缩放和颜色调制

本次按用户要求优先处理渲染，暂停扩展伤害计算。新增实现位于 [renderer.js](../../../combat-preview/web/renderer.js)。
这里的结论来自原 v3 静态程序字节、REA/Ghidra 反编译与当前 Script.pvf；未采用 `dnf-rebuild` 的推测实现。

## 原件和验证方式

- 分析原件是 `analysis/unpack_attempts/001/launcher_test/DFO_fixed_v3.original.exe`，SHA256 为 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`。
- 当前安装的同名 EXE 是导入修复 v4，SHA256 为 `bdd14a558658dd0b20def0aa9fa4b355b98855075a05ba6de7f60c4da695495e`。预览通过精确哈希、入口、image base 和原七节元数据/全部 raw bytes 核对派生关系，分别保留实际文件身份与历史静态证据身份。
- [evidence-index.json](evidence-index.json) 保存原字节范围、位置、哈希、与 v4 的静态比较、虚表绑定及 PVF 样本身份。可用 `python -X utf8 analysis/combat_render/build_transform_evidence.py` 重建。
- 字节相等仅支持复用这些静态合同；启动器对受保护战斗入口的替换另见 [patcher-source](../../unpack_attempts/001/patcher-source/README.md)。这里没有录制原游戏绘制调用，也没有宣称完整脱壳。

## 已追到的消费链

```text
ANI parser A2912B / A29144
  → keyframe+18 rotation / +1C RGBA
  → A23D60
  → 5383D0
  → B0E050
  → texture vtable+A0 = ADD3D0
  → rotation matrix / rate / pivot
  → B08D30 four vertices
  → B08200 D3D8 texture-stage setup
```

| 项目 | 原程序证据 | 已接入预览的行为 |
|---|---|---|
| 旋转单位 | `A29133→82F860` 直接读 float 写 `frame+18`；`ADD3F6..ADD402` 对原值 `fchs` 后送旋转矩阵 | 原值为弧度；Canvas 使用其负值，删除原先的度转弧度 |
| 矩阵分派 | `C35536→[FFB100]`；静态值为首次调用包装器 `C3551A`；`C3788E` 将 `FFB168` 基准表复制到 `FFB080`，对应槽为 `C3553C` | 基准矩阵 `C3553C` 直接 `fsincos`；未采样运行时 CPU 优化分支指针 |
| 非均匀缩放 | `ADD46D..ADD494` 对矩阵输出 X 分量乘 rateX、输出 Y 分量乘 rateY | 先设置输出轴缩放，再应用旋转；左右朝向体现在 rateX 符号 |
| 正常原点 | `A23D60` 传 position=`actor+IMAGE POS`、pivot=`-IMAGE POS`；`ADD497..ADD4D6` 先作 `crop-pivot`，变换后加 `position+pivot` | IMAGE POS 与 IMG 裁剪偏移一同参与变换 |
| RGBA 字节 | `A29144..A29189` 读取四个整数，取低 8 位打包 `AABBGGRR`；`B0E0BC..B0E0EE` 交换 R/B 成 `AARRGGBB` | RGB 分别调制源纹理通道，frame alpha 在合成时只乘一次 |
| 顶点颜色 | `B0912B/ B09166/ B091A1/ B091D6` 将同一颜色写入四顶点 diffuse | 全部纹理像素接受一致帧颜色调制 |
| 设备状态 | `B083AF/B083C0` 设置 stage0 ALPHAOP/COLOROP=4（MODULATE）；同段设置 TEXTURE/DIFFUSE 参数，COLORARG1 使用 D3D8 默认 TEXTURE | RGB=`texture.rgb*frame.rgb/255`，alpha=`texture.alpha*frame.alpha/255` |

`CND3DBaseTexture` 的 RTTI / 虚表为 `FF2664 / E6A074`，`CND3DTexture32` 为 `FF268C / E6A12C`。
两张虚表的 `+A0` 均为 `ADD3D0`；相关 COL 和虚表原数据已保留。

正常 IMAGE POS 原点的 Canvas 等价顺序为：

```text
translate(actorX, actorY - actorZ)
scale(directionSign * rateX, rateY)
rotate(-sourceRotationRadians)
translate(imagePosX, imagePosY)
drawImage(croppedImage, cropX, cropY)
```

这里未实现 `A23D60` 的另一个居中原点模式。`5383D0` 的其他参数模式、全局缩放/裁剪分支不能据此宣称全部闭合。

## REA 和样本

本次实际通过 REA 调用了 `open_binary`、`analyze_function(0xADD3D0)` 与 `close_binary`，完整返回保存在本目录。
纹理绘制 Evidence ID 为 `ev_d7062f931a7f0b1868e46746fc93b88b6e853b7425cc61669a2f0dfa0f2a7aad`，伪代码见 [002-texture-quad.c](002-texture-quad.c)。
复用了已有 `A23D60`、`5383D0`、`B08200` 的 REA 返回，ID 见 index。

`003-profile-helper.json/.c` 是额外查询的 `B09FB0`，结果证明它记录 RDTSC 性能计数，**不是纹理 stage 设置器**，不用于支持颜色运算结论。

当前 PVF 的真实样本：

- `soulbringer2.ani`：RGBA=`60,0,255,255`，rate=`0.4,0.2`，LINEARDODGE；源 ANI SHA256=`74cd53b285afd7946faebd943df54b85c88b49ac11c8f4a12e62cc6e4d5743a4`。
- `hundredsword/finishcircle1.ani`：rotation=`-2.443461`，rate=`-1.4,1.4`。第0帧是 DELAY=0 的空图帧，时间0的基准资源播放器显示第1帧。
- `hundredsword/flash1.ani`：rotation=`-0.157000`。

样本保留原 CP949 字节；完整来源、CRC 与每帧字段见 index。PVF 参考 skill 的 ANI 样例为空，未作为这些二进制行为的证据。

## 验证与未恢复项

[check_renderer.mjs](../../../combat-preview/tests/check_renderer.mjs) 验证 RGB 调制、alpha 只乘一次、加色、负弧度旋转、非均匀缩放、偏移和左右朝向，并实际加载上述两种 PVF/NPK 样本。
结果保存在 [renderer-browser.json](../../preview-validation/renderer-browser.json)，截图见 [finishcircle1-render.png](../../preview-validation/finishcircle1-render.png)。
鬼斩合成、怪物资源选择、场景动画切换另有浏览器回归记录。这些属于预览实现验证，**尚未进行原游戏逐帧/逐像素对照**。

后续已补上 [ANI 连续插值](../interpolation/README.md)。当前仍缺原生时钟/动作速率接入、其他图形效果、居中原点模式、完整生成物和粒子生命周期、世界排序，以及完整怪物反应/死亡执行。全职业技能控制器没有因本次通用渲染修复而增加。
