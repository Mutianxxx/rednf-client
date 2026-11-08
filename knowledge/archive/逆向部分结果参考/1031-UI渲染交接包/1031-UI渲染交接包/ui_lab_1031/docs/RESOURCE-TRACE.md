# 1031 通用 PVF / 静态资源调用链采集（revision 3）

本模块与原 UI 观察器放在同一个 `zz_ui_lab_1031.dll`，独立核验、独立安装，不依赖 UI 十一个入口全部就绪。采集全部通用资源路径，外部程序按全量清单识别待研究内容，包含 ANI、ACT、MAP、DAT、AI、粒子、指南及保留后缀；不会仅监听 `.ui`。EXE/PVF 身份沿用 README 中的 1031 SHA256，不能移植地址到其他客户端。

全部 68 个 PVF 扩展名及用途候选/未完成契约同时编译在 `src/watch_profile.hpp` 中。通用事件附带 `pvf_extension_candidate`，它只是按 PVF 后缀推得的候选用途；归档外同后缀文件仍以外部精确路径清单为准。

## 加载和观察

安装位置：`DNF1031客户端/plugins/zz_ui_lab_1031.dll`。已有 ijl15 插件加载器会在正常启动时加载。若用已有的运行时加载工具加载同一 DLL，DllMain 也会启动工作线程；`ClientPatchPluginInit` 与 DllMain 使用同一次启动保护。此工程未新增远程注入器，也未验证此前被 Windows 拒绝的远程注入路径。插件已加载后不要重复加载另一份副本。

工作线程验证 EXE 后尝试安装三组独立观察：UI、通用资源、主 EXE 的归档 I/O API 槽位。尚未解包的代码每秒重查，字节不匹配时拒绝该组；不能将“DLL 连接”当作全部入口可用。启动/运行时加载之前的资源读取不会被回补，已缓存数据也可能跳过读取入口。要观察进入城镇之前的调用，应使用正常启动加载，并查看日志中最早观察时间。

外部监听器新增“PVF / 未知资源”页。它在后台增量读取专用 `resources.jsonl`，展示原始调用、候选资源及未完成项；完整关联结果写入 `ui_lab_1031/reports/runtime-resources/<session>/correlated.jsonl`。新资源按批次发送系统通知，入口失败和损失计数留在诊断页。Windows 是否实际展示通知取决于系统通知设置。

## 静态证据和调用链

以下地址均为该 1031 内存基线首选 VA，实际目标为 `module_base + VA - 0x400000`。基线含 0725.dll / stringtable.dll；每个入口使用 32 字节守卫，全部字节与指令边界验证后才提交补丁。`reports/static/resource-profile.json` 和 `src/resource_profile.hpp` 保存证据；原反汇编位于 `reports/ui-layout-code/`。

```text
UI loader 01067EC0（以及其他脚本调用者）
  → 01223620(root/type, UTF16 path)
  → 011A68C0(ECX parser, root/type, path, optional stream)
      → parser callback [parser+6104]
          基线全局 parser 01D27360 的该指针 = 01227920
      → 01227920 拼接/处理路径（存在其他 stream 分支）
      → 011ACB40(ECX manager, UTF16 path, &data, &length)
          → 011AC570 后端查找/缓冲区读取
      → 按 B0 D0 头选择 token 二进制 / 文本解析
          011A9690 二进制，011A8740 文本
      → 各类型解释器 / UI 配置与运行时控件
          → 已有 UI traversal / IMG 查询 / draw wrappers / D3D9
```

`01225210` 是 token/tag 读取器，`01225150` 是字符串/本地化读取器，均不应当当作资源打开入口。本次没有将任意 token 字符串全部采集，避免把输入框等用户文本混入资源日志。

| site | VA | 采集含义 |
| --- | --- | --- |
| 21 | 011ACB40 | 缓冲区读取开始，ECX manager；栈参数 path、输出指针地址、输出长度地址 |
| 22 / 23 | 011ACC0D / 011ACC51 | 普通返回，EAX 原值；静态正常分支为 0，错误分支为 1 |
| 24 | 011A68C0 | 通用解析开始，ECX parser；root/type、path、可选 stream |
| 25 | 011A696F | 失败返回路径 |
| 26 / 27 / 28 | 011A69DD / 011A6A32 / 011A6A7F | 文本 / stream / buffer 普通返回路径；采集 AL 原值与 parser+14 模式 |

通用入口的返回关联使用有界线程局部栈和原入口 ESP，与返回处 EBP+4 匹配；没有替换返回地址。深度最多 16，异常展开/不匹配计入 `resource_unmatched`，不会用邻近时间强行拼接。所有指针读取均先检查页状态，不消费 PAGE_GUARD。

## 事件契约

`resource_open/resource_end`、`parse_open/parse_end` 共用原事件基础字段：QPC、tid、site、object、span、path、args、flags。开始/结束通过 span 关联。调用栈为最多 12 个地址，属于有限栈链或 Windows 栈回溯，不能视作完整无遗漏的 unwind；`caller_rvas` 只为落在主 EXE 范围内的地址提供 RVA，其余为 null。

| 事件 | args / 其他字段 |
| --- | --- |
| resource_open | args[0..2] 为入口栈参数；flags 为当前解析 span（0 表示未关联）；parent 为直接返回地址 |
| resource_end | args[0] 为 EAX 原值；为 0 时尝试读取 args[1]=data、args[2]=length；payload_hex 最多 128 字节，flags=1 表示头部读取成功 |
| parse_open | args[0..2] 为 root/type、path、stream 原指针；name 为有限 root/type 字符串；flags 为父解析 span |
| parse_end | args[0] 为 AL 原值；args[1] 为 parser+14 的原始模式，尚不凭此推断全部业务成功 |

缓冲区有内容、解析返回成功、图像查询及 draw 是不同证据。本模块没有将缓冲区读取直接绑定到某个 UI 控件，只有已有 UI 专用 span 和树证据才能建立该关联。

## 归档 I/O 回退

观察 CreateFileW/A、ReadFile、SetFilePointer、CreateFileMappingW/A、MapViewOfFile、CloseHandle。共 13 个固定主模块槽位，位于两套已发现的导入区域；每个槽位要求存在实际 `FF 15 <slot>` 调用指令，并且当前值等于系统导出地址。对已被其他模块修改的槽位不接管。安装和恢复均使用原子比较交换；停止时仅恢复仍由本 DLL 占有的槽位。

`src/archive_io.hpp` 的表给出全部 VA 和调用证据，`reports/resource-verification.json` 已与 1031 基线逐一复核。覆盖不包括其他 DLL 自有的 I/O 表、其他文件 API 和绕过这些槽位的代码。文件句柄可在晚加载时由 GetFinalPathNameByHandle 识别，仍不能恢复过去的读取历史。

`archive_io` 的 site：1=CreateFileW，2=CreateFileA，3=ReadFile，4=SetFilePointer，5/6=CreateFileMappingW/A，7=MapViewOfFile，8=CloseHandle。object 为句柄，span 为观察器分配的句柄代次；flags 语义依操作而定。

| 字段 | 含义 |
| --- | --- |
| args[0] | API 原始返回值（指针/句柄/BOOL/DWORD） |
| args[1] | API 调用后的 LastError 原值；成功时可能是此前残留值，不能单独判断成功 |
| args[2]/[3] | 64 位文件偏移或 mapping 参数（低/高） |
| args[4]/[5] | ReadFile：请求 / 实际字节数；mapping/view：相应长度/权限原参数；open：access/create |
| ReadFile flags bit0 | 使用 OVERLAPPED；只记录提交，异步完成需要进一步观察 |
| ReadFile flags bit1 | 获得偏移；同步位置查询与真实读取不是原子操作，共享句柄并发仍有竞争 |

映射日志只证明映射的范围，不能证明其中每个成员被访问。读取范围跨多个成员、归档重名、不同物理包同路径都保留候选。成功零字节读取不会误判成读取到文件末尾。PVF 存储范围按四字节对齐，索引同时保留真实内容长度。API 包装器保留输入/输出 LastError，不改原始返回值、数据缓冲区或文件位置。

## 清单、限制和验证

完整入口为 `reports/resource-audit/1031-未明确内容完整清单.md`，同目录含全 PVF/NPK/散装文件 CSV、异常、重复内容、全部 token 标签及 ANI 结果。`watch-targets.json` 包含全部 68 个 PVF 后缀组的用途和未完成项。监听器按扩展名和精确路径关联；静态失败和模板路径继续作为研究目标，不将未观察到的资源判作无用。

原始总事件日志仍为单文件，上限 256 MiB。revision 5 起资源事件不再重复写入该文件，低频加载/绑定等还独立保存在 `ui_lifecycle_journal`（4×4 MiB），详见 [PROTOCOL.md](PROTOCOL.md)。Revision 3 的资源专用单文件上限为 128 MiB，真实会话证实约三分钟即写满，之后只有最近 128 个资源事件的快照。此时外部监听器会继续保存快照中未见过的事件，并标记 `observation_source=recent-snapshot-after-log-cap`、`history_complete=false`；采样间隔内经过的其他事件不能恢复，不能称为完整历史。

Revision 4 的资源日志改为最多 8 段、每段 16 MiB：`resources.jsonl` 是保留的第一段，后续 `resources-000001.jsonl` 等滚动保留最新 7 段。保留首段只保证最早的 16 MiB，不等于保留全部进城前事件。`state.resource_journal.parts` 提供 ordinal/file/bytes/events，工作线程先 flush 再发布状态。`resource_log_bytes` 在新版表示累计成功写入字节，`retained_bytes` 表示当前保留量；`retired_bytes/events` 表示已经回收的历史。磁盘写入/回收失败计入 `resource_disk_omitted`，不会默默越过容量。

外部 `resource_stream.ResourceTail` 根据分段编号续读，跨批保留 JSONL 半行。若活跃段在两次读取间被回收，其未读尾部也保守计入 `gap_segments`，因此它是可能缺失分段数，不是精确丢失事件数。外部关联日志同样按 8×16 MiB 严格分段，索引为 `reports/runtime-resources/<session>/correlated-journal.json`，成员为 `correlated-v2-*.jsonl`。旧版 `correlated.jsonl` 原样保留为旧证据，不在新分段容量中。`observed-paths.json` 另存已读到的路径发现；历史回收不会删除这些发现。新版 version 2 同时保存游标、半行和未结束 span，正常关闭和切会话最终保存；同会话重开直接续读。旧版无断点时保留发现、重新计数；异常关闭仍可能重放最后未保存批次，不当作精确全程调用次数。

同线程 `resource_open.flags == parse_open.span` 建立 parser→buffer 父子关联，buffer 返回按自己的 span 匹配；新版外部记录 `parser_context`、`buffer_children` 和相对路径的 `resolved_buffer_members`。不能按时间距离猜测、不能将 resource_end 的头部成功 flags 当父 span。首次时间取已读证据的最小 QPC，不能用后期快照覆盖更早的读取时间。

`losses`、`archive_omitted`、`resource_disk_omitted`、`resource_unmatched` 分别表示队列/遍历丢失、归档预算或句柄表限制、资源写入失败、资源返回不匹配。Revision 4 另列 `archive_throttled`、`archive_handle_overflow`，不再将两种归档缺口混为一种原因。每线程归档事件预算仍为每秒 300 条。资源头部截断不改变完整 length；所有磁盘写入由工作线程处理。

外部显示线程最多挂起一批数据，主界面确认处理后才继续采集下一批。资源页每批只显示末尾 100 条摘要，完整关联仍由日志保留规则管理。普通状态读取优先使用每 200 ms 原子发布的文件，命名管道用于显式控制，避免状态轮询争抢单实例管道。Revision 4 支持在当前会话目录创建 `stop.request` 请求工作线程停止并恢复仍归自己所有的补丁；根目录 `1031停止UI资源采集.cmd` 提供该操作。关闭监听器本身不会停止 DLL。

`tools/verify.py` 验证原生回调、缓冲区返回、解析成功/失败、LastError、真实文件读取、映射、异步提交、文件停止命令和既有 UI/图形机制；宿主明确标为 fixture。`tools/verify_resource_trace.py` 核对版本守卫、13 个导入引用和保守范围关联；`verify_resource_stream.py` 核对原生分段、首段保留、回收、慢读取和容量；`verify_monitor_delivery.py` 验证 GUI 阻塞时后台仅挂起一批数据。

真实revision3会话`20261018T071256-61396`确认19处代码/13个I/O槽的进程内所有权、45次加载、37个明确来源、7个部分图片链；初始7,431个精确成员/42类及111样本核对，合并后期保留快照为7,481成员，120条样本与前组重叠不相加。最早Intro_18为attach后8.344秒，含频道/角色。详见[实测报告](../reports/LIVE-TEST-20261018.md)。当前revision6候选保留资源协议，配置整合/几何与Present统计见[本轮报告](../reports/REVISION6.md)，部署以staged.json为准。实机待验，不能用revision3会话替代；HAL/NULLREF、完整画面与median开销仍未验收。

本轮新增 [未完成清单与补采计划](../reports/1031-未完成清单与补采计划.md)及[全部 68 类的运行证据矩阵](../reports/followup-20261018/1031-全类型运行证据矩阵.md)。继续离线分析即可，不需要再次进行整轮副本捕获。可见标题、生命周期、ANI 专用入口和延迟 GPU 归属等要先完成代码定位，不能靠延长记录补齐。

复核命令（从工作区根目录执行，Python 环境见启动器）：

```text
python -X utf8 -B ui_lab_1031/tools/resource_profile.py
cmd /c ui_lab_1031\build_native.cmd
python -X utf8 -B ui_lab_1031/tools/build.py --assets-only
python -X utf8 -B ui_lab_1031/tools/resource_audit.py
python -X utf8 -B ui_lab_1031/tools/verify.py
python -X utf8 -B ui_lab_1031/tools/verify_resource_trace.py
```

`--reuse-scans` 仅重分类既有扫描结果并重查散装文件；不能用它宣称重新扫描了被改动的 PVF/NPK。本次原始全量扫描及其哈希已经保存。
