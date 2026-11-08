# 运行协议、资源和离线调用

## 输出位置

真实客户端写到 `DNF1031客户端/trace-ui-lab-1031/<UTC时间-PID>/`，`latest-session.txt` 指向最新目录。测试宿主写在 `ui_lab_1031/bin/trace-ui-lab-1031/`；两者必须区分。`events.jsonl` 是 append-only 原始记录，`state.json` 由工作线程写临时文件再原子替换。

命名管道为 `\\.\pipe\dnf-ui-1031-<PID>`，仅允许本机连接。请求 `snapshot` 得到完整当前状态；响应过大时返回本次状态文件路径。请求 `stop` 停止采集并恢复自有补丁。UI 线程不直接等待 IPC；外部工作线程读消息并支持断开重连。回连获得全部当前绑定和最近完整的 UI 遍历，不依赖曾收到过创建事件。

管道停止或进程退出后可查看离线快照。外部工具按 PID 和确切 EXE 路径检测退出，不把上次缓存的 `running:true` 当作活进程。权限不足时 liveness 为 unknown；文件超过 3 秒未更新时标 stale，不能宣称仍实时连接。

## 事件与关联

Revision 3 新增 `resource_open/resource_end/parse_open/parse_end/archive_io`、`resource_ready/resource_diagnostics/archive_slots`、资源独立日志和损失计数。完整字段、调用链、返回值及范围语义以 [RESOURCE-TRACE.md](RESOURCE-TRACE.md) 为准。资源 payload 为最多 128 字节缓冲区头部，不能套用 UP 几何解释。revision 3 的 `resources.jsonl` 为独立 128 MiB 单文件；revision 4 起为 8×16 MiB 分段。revision 5 不再将资源事件重复写进 `events.jsonl`。

| 事件 | 用途 |
| --- | --- |
| attach / code_ready / first_observation | DLL 工作线程、代码解包、首次加载/绘制/API 的时间证据 |
| load / load_end | 加载 span、加载器、路径、参数、成功/失败 |
| factory / lookup | span 内的配置类型、IMG 查询；不是创建或 draw 成功证明 |
| bind | UI 文件、控件名、配置地址与运行时实例地址的直接关联 |
| control / image / clip_raw / tree_end | 一次递归 UI 绘制遍历及有限图像请求 |
| device / reset / present / draw / texture | 独立图形 API 回退证据 |
| auto_throttle / stopped | 自动降频及恢复结果 |
| guard_check / hook_rejected / hooks_unavailable | 固定入口的实际字节、差异或安装失败 |
| reviewed_profile_loaded / reviewed_profile_rejected | 显式审阅配置重试的结果 |

事件带 QPC、线程、site、原始指针、span/frame、原始参数。`payload_hex`须按事件解释：draw为有限UP几何，resource为有界缓冲头，revision6的image/clip为上下文快照；均不是截图。16个args的未使用部分为零，不能额外赋予语义。

D3D 设备在观察器接入前设置过的 FVF、texture、shader 状态可能未知；状态跟踪字段的初始零值不能当作已确认的 null。完整初态与 state block 恢复属于未完成项。PNG 预览不使用这些缺失状态宣称 GPU 精确回放。

每次已观察绑定建立保守的 observation generation。外部身份为 `session:control:pointer:generation`；这是“观察到的绑定代次”，不是完整构造/析构生命周期。隐藏、离开本次遍历、释放是不同状态。没有析构证据时只显示 `absent_from_this_traversal`，不宣布销毁。完整帧中的 control 行固定保存当时的 binding（路径、span、revision、generation），后续相同地址的新绑定不改变旧帧归属。

UI 遍历的首 control 带 flags `0x100`；tree_end args[0]/args[1] 是开始/结束丢失计数，args[2] 是期望事件数量。要求首事件存在、数量一致、丢失计数一致，外部才接收。结束记录缺失、队列溢出、截断、深度超限均不得拼成“成功窗口”。这里的完整只指已布置 hook 的 UI 请求遍历，不代表所有专用绘制或 GPU 提交已覆盖。

默认结构观察 5 Hz，详细请求在加载后约 3 秒内 5 Hz，稳定后 1 Hz；UI callback 墙钟占比超过 5% 时降低详细频率，最高 8 秒一次。这只是自动减负指标，不能替代“相同场景 median 帧时长增幅 ≤5%”的实测验收。回调仅复制有限 POD 入队，不写文件、不做 JSON、不等待管道。默认事件日志上限 256 MiB，超出记录 `disk_omitted`，状态采集继续；不能将此后的文件当作完整历史。控件绑定快照上限 8,192 项，超限计入损失。

## 外部资源调用

`bin/ui_assets.exe <1031客户端目录> <输出目录>` 启动独立解码进程。启动返回一行 ready JSON；后续每行请求对应一行响应。

```json
{"op":"catalog"}
{"op":"image","path":"Sprite/Interface/WindowCommon.img","frame":0,"key":"0123456789abcdef"}
{"op":"animation","path":"UI/BloodDungeon/ExpFX.ani"}
{"op":"quit"}
```

调用者通常使用 `tools/assets.py` 的 Assets 类，自动生成由版本、路径、帧号组成的缓存 key。输出 PNG 同时提供裁剪 x/y、像素尺寸、逻辑尺寸、源 NPK 成员偏移/长度与 SHA256。NPK 重复成员不擅自选择；未知 IMG 类型报错并保留缺项。

animation 响应保留 globals、duration、每帧 duration/interpolate/properties 及 native sampler 给出的 pose。Python Assets 层补 PVF 成员 SHA256；外部播放遵循已实现的帧时间与插值，不执行 UI ACT。逻辑坐标与 IMG crop 分开，crop 随图像参与变换。

## 离线包与本地交互

包根为 `window.json` 和 `images/*.png`。manifest 保存 EXE/PVF 哈希、原始调用 view、控件定义、图片元数据、成员来源、缺项和 capability。`load_bundle` 校验版本、资源哈希和路径边界后才打开。

扩展字段 `animations` 保存本窗口使用的 ANI 元数据与来源，`unresolved_animations` 明确缺项；全部所需 ANI 图像也进入图片清单。静态 view 保留 `instances`、原始 root window_fields、每条子 UI 的独立 key、条件和 `preview_diagnostics`。布局候选详情可带 `resource_contexts`，来源于本版 WDM 的明确 `[ui path]`；它不能当作运行时加载证明。

后续可选 `view.board_previews` 以控件实例 key 索引，保存原始参数/字符串、loop或stretch模式、逻辑尺寸、绝对锚点、像素并集、有序 `draw_ops`、消费者/证据和支持状态。每项操作含slot、frame、IMG路径、实例、源配置offset、crop、缩放及已确认状态边界；这是离线配置提交，不是DLL事件。缺任一图、歧义、未知参数或安全上限保留明确原因。旧version1包没有该字段时按原控件和资源重建，不补造实时状态。详见[board补充契约](../reports/BOARD-FOLLOWUP.md)。

运行时图片按照捕获请求的路径、帧、顺序和坐标绘制。PVF 目录则是另一个明确标注的布局候选模式。按钮状态帧、页签和滚动在本地实现；没有 verified 原生参数时只能标交互示意。运行时本地页签尚未完整绑定全部子 UI 和皮肤状态，因此不能标“完整可交互”。按钮事件不发送游戏输入、网络请求，不调用客户端内部函数。

## revision 2 入口诊断与审阅后重试

attach/state 带 `observer_revision:2`，attach 还记录 DLL 文件哈希和主模块基址。`guard_diagnostics.sites` 含 11 个固定点的 expected_hex、actual_hex、different_offsets、页属性、是否可读和已有入口 JMP 目标。变化时保存 `guard-windows/index.json` 和每点 640 字节的固定代码窗口；这些均由工作线程读取，不在 draw callback 中读取磁盘或反汇编。

`self_readback` 每秒核对本 DLL 的 11 处补丁。这是进程内自证；外部模块枚举/ReadProcessMemory 被拒绝时，不能把它升级为独立外部回读通过。

仅在审阅了代码窗口、确认函数契约未改变后，开发者可在当前会话放置 `reviewed-profile.json`，再请求 `reload_profile`。schema 必须包含本次 `session`、确切 `exe_sha256`、至少 12 字符的 `review_note`、按固定顺序排列的 11 个 `sites`（id、name、64 字符十六进制字符串 guard，即完整 32 字节）。地址、覆盖长度与回调不可由文件指定；覆盖前缀还须通过保守可搬移指令检查；已有活跃补丁时拒绝重试。

此命令不会自动生成可信字节，也不是绕过守卫的开关。成功载入审阅配置后，仍须等安装事务、`code_ready` 与真实事件/回读证据。

## 外部通知与日志

监听器使用 Windows/Qt 系统托盘通知，日志为 `reports/notifications.jsonl`，开关为 `reports/monitor-settings.ini`。日志保存 queued/requested/disabled/rate_limited/system_unavailable 等投递状态。全局至少间隔 6 秒，同一类至少间隔 45 秒；新增 UI 来源合并提示，避免逐 draw 弹窗。日志为诊断依据，是否真正显示由 Windows 决定。

## revision 4 资源续写与停止

资源分段、容量、显式缺口、快照回退及路径汇总以 [RESOURCE-TRACE.md](RESOURCE-TRACE.md) 为准。状态增加 `resource_journal`、`archive_throttled`、`archive_handle_overflow`。`resource_log_bytes` 为累计成功写入量，当前磁盘保留量另见 `resource_journal.retained_bytes`。

`tools/ipc.py state()` 默认读取未过期的原子状态文件，不主动占用控制管道；显式 `request()` 仍可使用命名管道。文件超过 3 秒未更新时不能当作实时状态。当前会话目录中的固定名称 `stop.request` 是 revision 4 的停止命令，工作线程每约 200 ms 检查；调用方须继续核对 `running=false` 和恢复结果，创建文件不等于停止已完成。旧版 DLL 不支持此命令。

GUI 通过确认信号限制为一批未处理的数据。显示摘要的行数限制不改变原始采集计数，文件滚动和快照遗漏必须分别报告。

## revision 5 UI 生命周期与外部恢复

attach/state 使用 `observer_revision:5`。`events.jsonl` 继续保存 UI 遍历/GPU 详细事件及诊断，上限 256 MiB，资源事件改由 `resource_journal` 独立保存。`event_log_scope` 说明此变化；旧消费者需要适配，不能认为新版总文件也包含资源事件。

`ui-lifecycle.jsonl` 保留首个 4 MiB，另滚动最新三个 4 MiB 段 `ui-lifecycle-000001.jsonl` 等，总计最多 16 MiB。记录 load/load_end/bind/factory/lookup、设备创建/释放/Reset 及采集诊断，不包含 control/image/tree_end、周期设备采样、GPU draw/texture/present 和原始资源事件。它保存可复盘的加载/绑定线索，不代表完整隐藏/销毁或完整画面历史。

`ui_lifecycle_journal` 与 `resource_journal` 的 parts/total_written_bytes/retained_bytes/retired_bytes/retired_events/write_failed 含义相同，首段保留也仅限该段大小。`ui_lifecycle_disk_omitted` 记录写入失败；`disk_omitted` 仍针对总详细文件。绑定的 `binding_revision/observation_generation` 在两种日志和状态里一致。最终状态另存 `archive_restored`；停止成功需要结合 running/code_restored/archive_restored 核对。

外部 `observed-paths.json` version 2 保存 native_directory、reader_checkpoint（含 JSONL 半行）、未结束 parser/buffer span 和发现汇总。每约 10 秒更新，正常关闭/切会话再保存一次；同会话重开后继续读取。旧版汇总没有可信游标时保留发现并明确完整重读。回收段会报告 gap_segments，异常关闭可能重放最后未提交批次；计数不是严格 exactly-once 的全程调用数。

外部 `parser_context` / `buffer_children` 是明确 span 关联的补充字段，`resolved_buffer_members` 保存相对 parser 路径对应的成功读取成员证据。原始 path、直接候选和原始 flags 不改写；没有配对记录时不猜根目录。`resource_end.flags` 表示头部读取状态，不能当父解析 span。

原生生命周期分段、正常关闭/半行恢复、跨关闭 span 关联有回归检查；实际 1031 的新版运行仍待验证，见[未完成清单](../reports/1031-未完成清单与补采计划.md)。

## revision 6 可选绘制状态与配置

attach/state现为`observer_revision:6`，继承revision5日志/绑定/停止协议。旧会话和version1离线包继续读取；缺新字段保留旧能力，不推导新状态。

- `clip_raw.object`现在为目标ECX，`parent`仍是实际遍历控件。旧记录object为0时不能与任意全局上下文关联。`args[0:4]`为原始输入，`args[15]`为上下文，`callers`保留返回地址。
- image的`args[11]`是图像type，`vtable`是图像虚表。flags按位：1为帧表反指核验，2为上下文快照复制成功，4为新增消费者守卫通过；不能把flags当布尔值。
- image/clip的`payload_hex`前0x30字节为ECX上下文快照，image可再含0x08字节图像`+1C..+23`。工作线程输出可选`draw_state`：context、context_vtable、rectangle_words、image_type/vtable、consumer_verified；image_dimensions/crop仅在成功复制时有值。clip的capture_phase为写前，written_rectangle_words是已确认转换值而非写后读取。
- view可选`draw_ops`按采集顺序保存image/clip_raw，含order、source_event、instance（pointer/generation/binding_revision/span）和traversal_frame。旧images/clips不删除；无可靠上下文或绑定的原因保留。只使用每次图像自身已确认的矩形，不构造全局clip栈。
- 外部有序操作可选补充`draw_state.context_type`：仅从同请求且context匹配`args[15]`的payload `+8` DWORD恢复目的类型；源`image_type`保持原义。site7的8/14/15/16目的走替代surface消费者，不冒充type7；site8不套用site7分派。旧包无此字段和payload时保留原部分预览并提示目的消费者缺证。2^32零旋转中心取源`image_dimensions`或资源逻辑尺寸，不引入上下文尺寸字段；详见[增量契约](../reports/REMAINING-FOLLOWUP.md)。
- 配置view的`mode=config`、`config_type`、`configuration`、`selection`、`evidence`和`config_image`操作是离线示意，不冒充DLL事件。WDM区域/Common实例分开，STM未知列保留原数组，EVN总览标示意、CBT初始第1组标候选。
- `preview_diagnostics`增加可选support、summary及六类issues：unknown_structure/unknown_state/missing_resource/resource_ambiguity/unconfirmed_geometry/runtime_evidence。详细配置、物理候选和缺项进入包，旧无分类issues兼容归为unknown_structure。

## revision 6 帧时长和停止结果

独立`present_statistics`每秒输出statistics，状态保存最近一次，停止保存`final_present_statistics`。字段包括collected_qpc、qpc_frequency、aggregation_period_ms（周期事件）、buffer_capacity_per_device=4096、foreground_hook_ready、untracked_present_total。devices每项包含device、released、windows以及累计overflow_total/boundary_total/intervals_total/failed_present_total/background_present_total。

windows按epoch分别给sample_count、median_ms、p95_ms；设备顶层三项摘要仅取最后一个窗口，无样本时为0/null/null。不跨Reset、失败提交/设备丢失、释放、前后台转换、溢出/并发冲突边界拼接。p95为排序后nearest-rank；callback只入队，工作线程排样本。foreground_observation说明WinEvent+Present核验或退化状态；新入口失败和缺口有限频通知。旧抽样Present不能推算成完整分布；此统计不是GPU耗时，也不证明≤5%开销通过。

状态增加`geometry_diagnostics`，记录六段新消费者范围、哈希/可读性、虚表及常量核验；失败保留原事件并禁用新增确认规则。`geometry_guard_check`记录核验变化。

停止最终状态新增`graphics_restored`；确认成功需`running=false`且code_restored/archive_restored/graphics_restored均true。旧记录缺项仅表示无证据，不自动等同成功。通知补充几何守卫失败、统计缺口、资源歧义及停止结果，不逐帧推送；配置和回归范围见[本轮报告](../reports/REVISION6.md)。
