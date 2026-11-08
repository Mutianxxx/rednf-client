# 60US ANI 渲染证据

新增旋转、非均匀缩放、正常原点和 RGBA→顶点颜色→纹理调制消费链，详见 [transform/README.md](transform/README.md)。
2026-10-20另补齐 `A24950` 的连续插值消费者并接入预览，含原指令独立执行核对；详见 [interpolation/README.md](interpolation/README.md)。原角色时钟与完整技能调度仍未闭合。
预览已按原字节修正旋转单位、符号和变换顺序，并执行 RGB 调制。以下保留已有 LINEARDODGE 证据。

当前客户端的文本 ANI 并非只含透明度。此处已沿解析器、当前帧绘制、批次缓存和设备状态消费者追到混合因子。
原 EXE SHA256、8 个原字节片段、外部 API 头文件身份见 `evidence-index.json`。

1. `0xA291D0..0xA29303` 读取 `[GRAPHIC EFFECT]`，`LINEARDODGE` 字符串在 `0xE44E6C`。
   比较成功后 `0xA29244` 写当前 keyframe+0x28 = 2。NONE 写 0。
2. `0xA26990` 绘制当前 ANI 时调用 `0xA23D60`，传入 current frame snapshot `ANI+0xA8`。
   `0xA23D60` 用 frame+0x28 调 `0x401020`，再经过 `0x5383D0` 绘图，最后 `0x4010B0` 恢复。
3. `0x401020` 的 switch[2] 到 `0x401050`，以 2 调 `0xB084B0`，后者写 renderer+0x50348 的 word。
   批次路径 `0xB09205` 将该状态保存在 draw record+0x2140，另一条路径直接送往 `0xB084F0`。
4. `0xB084F0` 的 switch[2] 由表 `0xB08630` 指向 `0xB0853D`：设备虚表+0xC8 收到 `(19,5)`，再收到 `(20,2)`。
   default/NONE 分支则为 `(19,5)`、`(20,6)`。
5. 这是 D3D8 设备接口：+0xC8 是 SetRenderState，+0xFC 是 SetTextureStageState；同一对象还通过 +0x5C/+0x60 建立 vertex/index buffers。
   对应外部 API 常量为 SRCBLEND=19、DESTBLEND=20；5=SRCALPHA、2=ONE、6=INVSRCALPHA。
   初始化 `0xB08200` 开启 ALPHABLENDENABLE=27，默认 SRCALPHA/INVSRCALPHA。

所以 `LINEARDODGE` 的 RGB 运算为 `src.rgb * src.alpha + dst.rgb`（饱和到设备格式范围），
普通 NONE 为 `src.rgb * src.alpha + dst.rgb * (1-src.alpha)`。
预览采用 Canvas `lighter` 重建前一种 RGB 运算。浏览器 premultiplication、取整、色彩空间、过滤和旧 GPU 光栅规则仍可能不同，
这不构成原游戏像素等效性证据。其他效果枚举暂不推广为完整支持。

API 名称来自单独保留的 mingw-w64 `d3d8.h`、`d3d8types.h`，URL 和内容 SHA256 已记录。
这些头文件用于解释标准接口数值；客户端选择数值的结论来自 EXE 字节，而不是外部代码。

REA/Ghidra 证据包括：

- `032-function.json` / `ev_9f2dc5bde894b9592c30b1abdc470d98945f00059383e3a715de9dad92b24a20`：`0xA23D60`。
- `039-function.json` / `ev_7a6f17a3eedff96bbbdf6e7c3189856e6770fd99208a7777178d9bb46ea0790e`：`0xB084F0`。
- `040-function.json` / `ev_4e8256395d0ddabfdbf0a9055c0a47e5dacd6d9d9f0932e93e92e6d19df9e3f0`：`0xB08200`。

完整返回保存在 `../rea/results/`，不是原源代码。复验：`python -X utf8 analysis/combat_render/build_evidence.py`。
