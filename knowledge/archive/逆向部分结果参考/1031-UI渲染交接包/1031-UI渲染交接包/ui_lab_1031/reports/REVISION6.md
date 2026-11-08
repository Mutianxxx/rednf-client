# 1031 revision 6：预览修复与定向短测准备

更新：2026-10-18。仅适用于本工作区固定 EXE/PVF，不启动客户端、不远程注入、不要求重新打副本。此交付是可追溯的部分预览和采集候选版，不是全窗口复刻或客户端验收。

## 版本、证据和部署

- EXE SHA256：`246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264`。
- PVF SHA256：`ca756b7103a91628cffdf42fb745e9185fd5937deb229289a74831aa30500e1f`。
- 保存的内存基线 SHA256：`ab950286ad291236086beae21ef75b1732d4cd5e52db482e261f4c548969ea44`，含原有插件，不是无插件基线。
- revision 6 DLL SHA256：`bbb78bd3ff282eb64ae3b27cefa85b63a69e04b8b9bc17e7af0aec6875fe0dfa`；合成宿主 SHA256：`505ff8c3c16f675b260bdb6cde49c9334d5ef9243b705807f3cc0175f432347b`。
- [几何证据](geometry-revision6/evidence.json) SHA256：`f5987846674b0cc23b25614109321667a624c747056cbc668eab4501fac99c6a`，16 段有界代码、8 个 CALL、图像虚表及中心常量均逐字节核对磁盘 EXE/快照；不推广为整个快照一致。
- 正常部署由 `tools/stage.py` 执行：先核对 DLL 绑定的检查及客户端退出，再备份旧插件。最终状态与备份位置以 [staged.json](staged.json) 为准，不在游戏运行时替换文件。
- [封存会话清单](../archive/20261018T071256-61396/manifest.json)与静态审计不改写，最终检查见 [closeout.json](followup-20261018/closeout.json)。历史真实会话使用 revision 3，不证明 revision 6 实机通过。

## 原生规则进入工具

| 范围 | 证据与实际实现 | 明确保留的边界 |
| --- | --- | --- |
| 坐标 | `011BEAD0` 更新绝对位置并传播子控件 delta；实时请求直接使用已给出的 x/y，不再次累加父坐标 | 静态 PVF 布局仍是资源候选，不套用实时绝对坐标规则猜业务布局 |
| 矩形 | `011B4710` 写目标 ECX 的 `+28/+2A/+2C/+2E`，signed DWORD 非正值转0、正值截低16位；DLL 分开保存目标与控件归属、写前快照及原始参数 | 不是全局裁剪命令，没有构造推测裁剪栈 |
| 裁剪恢复 | `011BF510` 设置控件矩形后明确写回 `0,0,800,600`；每次图像请求保存自己的上下文 WORDs | 仅已核验 type7、虚表 `0185C76C` 的单位变换软件消费者应用有符号屏幕矩形；变换/D3DX 裁剪继续诊断 |
| 层序与实例 | `draw_ops` 按采集顺序混排 image/clip_raw，保存源事件、帧、捕获的实例代次/绑定版本；图片按原序渲染 | 保留旧 images/clips；无关联的操作保留原因，不按最近时间猜所有者 |
| 图像几何 | `011B3D80..B0` 确认 unsigned WORD 逻辑宽高、signed WORD crop；裁剪原点是局部偏移 | 九宫格保留透明逻辑边距，重复子 UI 与条件继续独立 |
| 变换 | `011B41E0→011DB510→011DB390`：负旋转后屏幕轴非等比缩放，pivot 相对逻辑图；约1e38中心哨兵取整数半宽/半高；颜色低字节为R | 次级中心哨兵2^32、类型8/14/15/16、draw by loop、特殊渲染模式不补近似公式 |

新消费者的六段完整代码 SHA256、图像虚表、type getter 和常量由 DLL 工作线程核验，结果在 `geometry_diagnostics`。核验失败仍保留原始请求，但不启用新增确认规则。新增快照为有界复制，JSON、哈希和统计不在图像回调计算。详见[原生契约](../docs/NATIVE-CONTRACT.md)。

标题/字体/生命周期同步静态定位：`011D0F90` 仅是提示文字 setter，`011BE350` 仅写 enabled byte，不能改称通用 title/hide。`011BF1A0` 有析构候选行为：重置虚表、释放 `+74/+2AC`、清理字符串并调用基类清理；已核对 `011908F4` 的 CALL，但全部构造/释放调用者、并发所有权和隐藏协议未闭合，未增生命周期 hook。控件 `+48` 的绘制文字不作为通用标题，也不复制 editbox 内容。

## 配置预览入口

监听器新增“配置预览”，使用已有严格解析器和哈希核验的专题证据，共36条入口。详情保留原始配置、证据来源、手动条件、物理 NPK/IMG 来源和歧义。

| 类型 | 可使用功能 | 未完成项 |
| --- | --- | --- |
| CBT（8） | 原生组号1..N，初始第1组标候选；按原始分支条件选主图，独立手动高亮 | 数字 IMG 管理器映射、真实组号及输入命名、alternate分支；-1不作为有效帧，实时仍跟随真实图像请求 |
| EVN（1） | 60条记录单选、四输入帧、双IMG分支、独立高亮、两个STR提示来源；12列总览按已确认公式 | 总览是配置示意，k是选中列表序号，不代表60项实际都可见；ID24、业务条件、动态文字与ANI时钟未知 |
| WDM（26） | 按配置路径加载区域UI与独立Common.ui实例；展示216地下城条目、100内部标记和资源上下文 | balloon/switchbox、ACT、业务条件未知；两条地图缺图保持缺图，不替换近似名称 |
| STM（1） | 主图及所选district追加帧；五列slot、四列stage和district内从1起的ID索引 | 状态列、stage坐标消费者未恢复，保留原始数组；主/追加图原点对齐仅为配置示意 |

未定位的 `sprite/worldmap/selectdungeon02_cn.img`、`sprite/worldmap/timegate.img` 明确列为缺图。物理成员歧义在缓存命中前也拒绝隐式优先级，并用现有限频通知提示。

`preview_diagnostics` 汇总六类：未知结构、未知状态、缺图、物理歧义、未确认几何、运行证据不足。界面显示摘要，全部原始证据进离线包。包版本仍为1，新增字段可选；旧 images-only 包按原能力读取，不补造对象、矩形或业务状态。

## Present 统计和停止

revision 6 按设备保存所有有效前台成功 Present 完成间隔，与详细API抽样独立。每设备固定4096项缓冲，回调只保存QPC差值、epoch和计数；工作线程每秒计算median、nearest-rank p95和样本数，公布QPC频率、周期和全部epoch窗口。顶层摘要仅是最近窗口，不混合边界两侧的样本。

Reset、设备释放/丢失、失败提交、前后台切换、并发冲突及溢出切断窗口。工作线程 WinEvent 观察前后台转换，每次 Present 还核对前台进程；观察入口不可用时明确标统计缺口。设备池/共享表未跟踪提交计入 `untracked_present_total`，不并入别的设备。缓冲溢出量、失败/后台Present数和边界数均输出；停止时保留 `final_present_statistics`。

统计入口、工作线程前后台通知延迟和真实性能开销仍须实机验证；Present完成间隔不是GPU耗时。短会话只做功能检查，不用于宣称≤5%性能验收。旧会话只有抽样Present，不回填完整统计。

日志分流、分段容量、断点/半行/span恢复、文件停止和现有限频通知保留。新增消费者守卫失败、帧时长缺口、资源歧义及停止恢复通知，不逐帧弹窗。停止最终状态需同时检查 `running=false`、`code_restored=true`、`archive_restored=true`、`graphics_restored=true`；DLL驻留至正常退出，不热卸载。

## 验证结果和输出

| 检查 | 结果 / 输出 |
| --- | --- |
| 原生宿主/协议/离线集成 | 41项通过；[verification.json](verification.json)，含寄存器/清栈宿主、ECX目标、矩形快照、Present边界/溢出、停止恢复 |
| 新配置/几何/兼容/监听器入口 | 49项通过；[revision6-verification/verification.json](revision6-verification/verification.json)，绑定DLL与几何证据哈希 |
| 资源入口与分段流 | 15项、16项通过；[资源关联](resource-verification.json)、[资源分段](resource-stream-verification.json) |
| 恢复、GUI交付及通知 | 10项恢复、单批交付/最终保存、15项通知策略通过；[恢复](trace-recovery-verification.json)、[GUI](monitor-delivery-verification.json)、[通知](notification-verification.json)；Windows实际显示未验 |
| 既有真实资源预览 | 16项通过；[preview-verification](preview-verification/verification.json)保留背包/选择/结果合成图、物理来源及对上次报告的诊断数量差异；旧报告单独保存，不能称为revision5基线 |
| 专题配置证据 | CBT114、EVN193、STM/WDM239项通过；不增加历史已观察成员数 |

新增[CBT合成图](revision6-verification/cbt.png)、[EVN配置总览](revision6-verification/evn.png)、[STM追加图](revision6-verification/stm.png)、[WDM配置候选](revision6-verification/wdm.png)及各自离线包，均含来源和缺项。几何测试覆盖负crop、非等比/反射缩放、旋转、中心哨兵、屏幕像素裁剪/恢复、遮挡顺序、同资源不同实例；既有嵌套/条件子UI回归保留。合成图通过不是客户端同帧画面对照通过。

实际HAL/NULLREF环境不可用；完整GPU回放、字体/标题/hide/destroy、所有专用控件、退出异常归因和≤5%开销均未完成。最新封存核验、文档链接和部署一致性见[收尾检查](followup-20261018/closeout.json)。

复查命令（工作区根目录，均不启动客户端）：

```powershell
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031\tools\analyze_geometry_chain.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031\tools\verify.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031\tools\verify_revision6.py
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B ui_lab_1031\tools\verify_followup.py
```

## 之后一次60–90秒定向功能短测

本轮不执行；后续由用户正常启动，不需副本或逐窗口反馈。性能对照另行安排。

1. 先开 `1031界面UI分析.cmd`，正常启动1031、选角进城；在正常经过的选角界面停留约10秒。不要修改跳过服务器选择的配置。
2. 同一城镇待机约10秒，打开一个代表窗口（如背包），切页/滚动一次，关闭再打开；观察资源预览、诊断及Present样本是否增长。只操作一个窗口即可。
3. 保持游戏运行，正常关闭再打开外部监听器一次；核对断点续读、来源实例及诊断，没有从startup反复重读。
4. 运行 `1031停止UI资源采集.cmd`，等待最终状态中running为false、三项restored均为true，再正常退出游戏。关闭监听器不等于停止DLL。
5. 留存该会话和退出结果，由工具核对revision/哈希、守卫、日志缺口及按设备/epoch统计。明显卡顿、持续丢失、所有权变化或写入失败即停采；恢复不完整时保留证据并正常退出，不远程注入。

这次只能验采集与部分状态转换。严谨性能对照需另用同场景、同设备/前台状态和足够时长的受控基线，对median/p95/缺口及观察器各部分开销分别分析。
