# 1031 剩余缺项定向补齐

日期：2026-10-18。继续离线；不启动客户端、不注入、不修改或重新部署 DLL，不改 `archive` 或 `resource-audit`。**本轮没有补齐全部未知行为**；以下区分实际实现、静态契约和仍需新增证据的内容。原 revision6 几何证据保留，不改写当时的未知列表。

## 进入实际工具的修复

1. **2^32 次级中心的零旋转分支**：`011DB510` 在旋转与 `015661B0` 的零值相等时，分别检查两个中心是否等于 `015661B4` 的 `4294967296.0`；命中轴取**源 IMG** `+1C/+1E` unsigned WORD 的整数半值。`011B41E0` 先将入口上下文保存到EDX，再把ECX改成源IMG；虚调用仍保留此ECX，并把目的上下文压为第三参数。`011DB510` 的ESI保存源IMG，EBX保存目的上下文。两个尺寸getter都以ESI为this。不能把包装器入口ECX与图像虚函数ECX混为同一对象；已撤去复核前误用上下文尺寸的草稿实现。
2. 中心沿用已有 `image_dimensions`，缺采集值时保留资源逻辑尺寸回退；不读取上下文尺寸。约1e38哨兵仍在包装器先替换，2^32只在零旋转分支替换，各轴独立，负零同样适用。非零旋转下原生保留2^32字面值，外部明确拒绝超界预览，不猜半尺寸。
3. **目的type8/14/15/16的具体拒绝原因**：`011DB180` 先以第三参数的目的上下文调用 `005B9080(+8)`，并非检查采集事件的源 `image_type`。复用 `payload_hex` 的目的上下文 `+8` DWORD，要求 `draw_state.context == args[15]`，仅在副本操作中补充可选 `context_type`。简单入口site7的目的类型8/14/15/16按 `011DB180 → 011DADE0` 报目的面/格式缺项；site8直接调变换虚函数，不误报这条路由。即使源type7，已捕获的非type7目的也不再误画；源type8不冒充目的type8。原始 `source_event`、旧 `images/clips` 和版本1包不变；旧包缺类型时保留原部分能力并明确提示证据不足，不补造状态。

实现：[native_geometry.py](../tools/native_geometry.py)、[image_contract.py](../tools/image_contract.py)、[model.py](../tools/model.py)、[preview.py](../tools/preview.py)、[config_preview.py](../tools/config_preview.py)。数字IMG缺图诊断也已在配置预览/导出中附上受保护入口和索引未知原因，不靠替换候选图掩盖缺项。新增字段可选，旧包缺少数据时保留原能力及缺项说明。

## 新增静态契约，不冒充运行支持

[evidence.json](remaining-followup/evidence.json)记录29段主模块代码、45个CALL、6个虚表槽、18处对象/分支指令探针和2个浮点常量。选定主模块字节逐项与固定磁盘 EXE、只读快照及保存的 `.bin` 对应；含文件偏移、长度与SHA256。初始化/构造的前缀和受保护基本块明确标明，不冒充完整函数。插件代码另有4段独立磁盘范围，**不声称它们存在于主模块快照或已被转储完整保存**。

| 缺口 | 本轮可证结论 | 尚不能据此做什么 |
| --- | --- | --- |
| R05 基类释放 | 虚表 `0185A614+0 → 011BF4E0`；thiscall、一个flags参数、`ret 4`；先调 `011BF1A0`，flags bit0非零再经 `011B03C0` 释放 | 不能证明全部派生对象都走此入口；未安装生命周期hook |
| R05 可见门控 | 虚表 `+10 → 011BE610` 写 `+0C`；存在 `+60` 回调时状态转换分别发 `10/11`，最终才写门控字节 | 门控不等于从父链移除或销毁；不能从遍历缺席判定hide/destroy |
| R05 子链清理 | 基类析构经 `+1C → 011BE880` 清空列表节点和计数 | 本函数未逐个销毁子对象，不能伪报所有子UI销毁 |
| A01 数字IMG | `011BB1B0(index)` 以 manager `+24/+28` 作为4字节指针向量边界，无符号越界返回0；新增工厂/初始向量/注册请求证据，见下节 | 注册顺序还不是已证运行索引，index16仍缺图，不猜路径 |
| R04 文字/字体 | `011BF510` 的 `+48` 文本有 `011C8C70` 与字体虚表分支；本轮保存直接CALL | 不是通用标题getter；未采输入文本、未猜字体字形 |
| R06 替代图像 | `011DADE0` 的EBX是源IMG、ESI是目的上下文；先取源crop/尺寸、与目的矩形相交；目的type14/15另有格式及像素转换分支 | 目的surface、格式与运行状态不完整，仍不输出近似像素 |

### CBT 全局分支与数字 IMG 初始化已缩小

CBT的两条ID比较现已和预览分支对应：`[01A424F0]`在`011BE020`先受控件`+0D`门控，再比较控件`+34`；`[01A42500]`由`011BE490`的单参数setter写入，并由`011BE2B0`与控件`+34`比较。`011BF96E`的一条dispatch路径把`[EBX+34]`写入active-id；状态reset路径将它置`-1`。因此“active id”和“forced id”分开保留；具体输入调用者和运行时生命周期仍缺。

`[01B5650C]`的`011C7E20` getter只原样返回DWORD。`011C8810`的一条事件处理路径从manager `+18`的bit7变化计算值`1/8`，事件`0x201`清零，另有分支写`0x40`或`8`。这证明可配置预览的`input_1b5650c`不是任意图像序号，但还不能命名为鼠标、键盘、焦点或业务状态；代码调用来源和各事件含义仍未知。配置预览继续要求手动传入条件，不把推断值伪装成当前运行状态。

### 数字 IMG 初始化已缩小，但不伪造索引映射

`00759780` 在全局 `[01A6A870]` 为空时调用 `011BC880`，后者返回单例 `01B563B8`；`011BC290` 的选定构造前缀把 `+20` 向量的begin/end/capacity（`+24/+28/+2C`）清零。随后逐条解码路径并经 `011BC900` 创建pack、保存路径，调用 `00493770`。

已逐字节核对前17条注册请求及字面量。请求序号15是 `Sprite/Interface/common/digit/white_stroke_small02.img`，序号16是 `Sprite/common/digit/DungeonCount.img`。这里的0起序号**只表示调用顺序**：`00493770` 的真实入口先跳 `020EF8B2 → 02C93FBF → 02C963A1`，包含尚未闭合的栈/标志变换；不能跳过受保护路径、仅凭后半段像vector append就认定完整语义。`011BC900` 还有分配失败提前返回，初始化块也可能带入已有列表或被重复调用。因此没有把第17条请求直接当成CBT的index16，没有替换预览缺图；下一步应闭合此helper和初始化时机，再核对同manager向量实例。

## 两份退出转储新增结论

- 原始两份dump和既有分析JSON均只读，重新核对dump SHA256；磁盘 `stringtable.dll` SHA256为 `9d218abc3e9a3f12b9b5ae2f5c27d58b03a07faf1d2079ab095b1ec11aca4cc1`，PE时间戳 `1663253240`、SizeOfImage `2D000` 与两份模块记录一致。这是元数据一致，不是完整加载代码哈希一致。
- 两份dump都实际保存 `ESI=7C88F23C`、`[ESI+BC]=61636F4C`（原始字节 `4c6f6361`）、`EAX=EIP=61636F4C`，以及栈顶返回 `7C88690B`。`ESI+BC` 对应模块RVA `1F2F8`；磁盘同位置也为这四字节。这里不是只看地址“像ASCII”的猜测。
- 用preferred base `10000000` 加RVA反汇编：`+16909` 为 `FF D0 / call eax`，`+1690B` 是其后继；之前读取 `[ESI+BC]`。共同失败的调用/数据关系已显著缩小。`+4FBB` 及 `+5A04/+5AAC` 与退出分发、虚表调用返回路径相容。
- **仍未归因**：两份dump没有保存 `+16909` 处的代码页；EBP链不是可靠符号unwind，未恢复该字段最后写入者、ESI为何指到此处及插件对照基线。不能认定唯一责任模块，更不能靠将槽位清零、替换/删除插件“修好退出”。下一观察点为该对象构造/销毁与 `+BC` 写入；实机对照先停采再退出，另做无采集插件受控基线。

实现：[crash_followup.py](../tools/crash_followup.py)。只读取有界原始地址；缺页明确记录，不用磁盘代码补成转储内存。

## 每项仍缺什么、怎样补

| 编号 | 当前确切缺口 | 下一闭合入口 / 验收条件 |
| --- | --- | --- |
| A01 | CBT输入全局量的上游调用/事件名、数字向量运行索引、专用模式 | active/forced control-ID比较与input全局的有限写入来源已定位；工厂/构造前缀及前17条注册已定位；继续追`00493770`受保护入口、向量填充和初始化次数、`011C3180`及同实例选组/选帧 |
| A02 | EVN业务列表/点击、ID24、ANI时钟附着 | 从 `004E9520/004E9770` 到实际业务调用者及动画实例，不能按60配置推60可见项 |
| A03 | STM stage坐标/槽位状态、WDM balloon/switchbox、MM/MAP投影 | 从 `00575EA0` 索引消费者及专用控件虚表继续；保留五列/四列和两条缺图 |
| A04/A05 | 68类的全部schema/执行用途、GDATA/GLIST/POS/REP/HSP | 按既有类型矩阵追特定读取器/消费者；42类观察不扩成68类运行覆盖 |
| A06 | 两条地图路径、49组重名物理优先级、ANI模板引用 | 追真实重定向/格式参数及物理读取，不选近似资源或猜归档顺序 |
| A07 | Tenparty/TenSLX、RTF/空ANI/空成员用途 | 需要明确引用或容器读者；空字节不能靠增加解析公式补出行为 |
| R01 | revision6真实启动/续读/重开/停止 | 一次60–90秒代表窗口短测；检查19处入口、13槽、三项restored及队列/日志边界 |
| R02 | ≤5% median开销对照 | 另做同场景启停/基线，按设备/epoch看median/p95及统计缺口；不能用宿主或抽样替代 |
| R03 | 退出责任与字段写入者 | 共同间接调用候选已定位；缺加载代码页、可靠unwind及受控插件基线 |
| R04 | 通用标题/动态文字/字形 | 字体/标题专用消费者及有界采集契约闭合后实现，再代表窗口对照 |
| R05 | 派生生命周期、父链移除/复用、真实hide | 基类删除/门控已定位；需派生调用与异常/并发所有权核验，不能提前记作销毁通知 |
| R06 | 非零旋转裁剪/渲染状态、专用图像、board动态resize | 新增零旋转次级中心已实现；其余沿目的面/像素消费者与动态布局继续 |
| R07 | ANI/ACT/HSP专用加载→实例→时钟→提交 | 现有ANI资源解码不等于原生调度；需要专用链证据，不要求重打副本 |
| R08 | packet生命周期/flush、纹理身份、完整GPU状态 | 不按时间邻近拼UI归属；字体/shader/state block和独立原生帧对照仍缺 |
| R09 | 全窗口行为与像素验收 | 复用已证控件链并长期低负载积累；322个目录不是322个已验窗口 |

离线静态项仍可继续逆向；它们不是全部都被实机环境阻塞。但当前缺少消费者或参数关系，不能本轮凭近似公式补造完成。R01/R02/R03的实机/性能对照按原计划不在本轮执行。

## 验证与复查

[专项验证](remaining-followup/verification.json)核对字节/直接CALL/虚表、源IMG/目的上下文寄存器流、每轴中心、目的类型与旧数据兼容、原始事件不变、17条注册请求/密文字面量/受保护跳转、实际转储槽位与缺页，以及有界minidump读取。集成/board/资源回归分别见 [revision6](revision6-verification/verification.json)、[board](board-followup/verification.json)、[preview](preview-verification/verification.json)；总关联见 [closeout](followup-20261018/closeout.json)。资源合成仍不计作客户端画面对照。

重新运行通用原生宿主时，离线包旧断言暴露了宿主的目的context `+8=0`，而非type7。新分派核对正确地拒绝该绘制，因此宿主验收改为检查“源事件/归属仍保留、目的类型0诊断明确、无伪造资源绘制”；不为通过测试弱化消费者守卫，也未修改/重建原生DLL或fixture。合法type7绘制、真实IMG解码/导出和旧包兼容分别继续由revision6与资源专项回归覆盖。

本轮实际复跑结果如下，不把同一证据的多项断言累计成窗口覆盖率：

| 检查 | 结果与范围 |
| --- | --- |
| 剩余项专项 | 63项通过；29段范围、45个CALL、18处指令探针、中心/分派、CBT注册/状态写入及dump有界读取 |
| revision6配置/几何/兼容 | 55项通过；新增正向目的type7、反向替代类型、数字IMG精确缺项与实际监听器配置入口 |
| board专项 | 79项通过，9张真实资源合成图；原有布局未改 |
| 原生宿主/协议/停止 | 41项通过；使用已有fixture和revision6 DLL，非客户端验收 |
| 既有资源预览 | 16项通过，保留背包/选择/结果合成及来源/诊断 |
| CBT/EVN/STM-WDM专题 | 分别114/193/239项通过；既有配置证据和原始字段未改 |
| 总关联/封存/部署 | 36项通过；主归档清单、静态审计封存、原生源清单与部署DLL一致，文档链接无缺失 |

仍未验证真实GPU：宿主HAL/NULLREF不可用，COM回退覆盖API采集，不代表GPU画面重放。客户端始终未启动，未要求重打副本，未重部署插件；稳定性、退出责任和≤5%性能对照继续为pending。

```powershell
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/analyze_remaining.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/verify_remaining.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/analyze_board_chain.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/verify_board.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/verify.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/verify_cbt_chain.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/verify_evn_chain.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/verify_spatial_chain.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/verify_revision6.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/verify_preview.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031/tools/verify_followup.py
```

后续一次短测仍按 [revision6步骤](REVISION6.md)操作：正常启动、代表窗口开关/切页、重开监听器、文件停采并确认三项恢复后退出。无需逐窗口反馈或重打副本。性能对照另行安排。
