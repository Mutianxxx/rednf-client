# 60US：x32dbg、Scylla 与 ScyllaHide 动态尝试结果

日期：2026-10-19。此前的独立调试测试已结束，本轮自建调试器均已停止；用户通过 D 盘正常启动器运行的游戏仍在使用。

后续更新：已按授权备份原件并把导入修复 v4 同名安装到 D 盘 `DFO_fixed_v3.exe`，用户重新配置启动器后确认 D 盘版运行正常，见 [启动器测试与恢复说明](launcher_test/README.md)。真实进程与哈希已核对，现场只读采集；另已使用 REA 追明启动门闩、技能消费跳板和怪物入口的[补丁来源](patcher-source/README.md)。下文的原件哈希与独立启动记录描述替换前的历史状态。

**已得到原版展开内存和 fixed_v3 导入修复 v4，D 盘正常启动运行验证已获用户确认。完整脱壳、原 VM 语义恢复与原始源码恢复仍未完成；游戏正常运行与这些完成条件分别记录。**

## 可用产物与验证范围

| 产物 | 来源与实际状态 |
| --- | --- |
| [client/DFO_imports_v4.exe](client/DFO_imports_v4.exe) | 建议检查的修复副本。代码、资源与已有保护段均保留自 fixed_v3；根据原版运行时证据增补导入。独立启动能创建 DFO 窗口，停在 HackShield 错误。 |
| [DFO_fixed_v3_imports_v4.exe](DFO_fixed_v3_imports_v4.exe) | 上述文件的相同字节副本，SHA256 `bdd14a558658dd0b20def0aa9fa4b355b98855075a05ba6de7f60c4da695495e`。 |
| [original-expanded-image.bin](original-expanded-image.bin) | 原版动态展开后的连续映像，VA `0x400000` 起、长 `0x100F000`。这是内存布局，不能当作普通 PE 文件直接运行。SHA256 `d63385139ee9cc491d107696b9be1cea71d16f237694fb92d0390ee6c630babe`。 |
| [original-expanded-scylla-dump.exe](original-expanded-scylla-dump.exe) | Scylla 从原版实际进程转储。指定的 `0xC05078` 是从 fixed_v3 得到的入口候选，并未认证为原版 OEP。 |
| [original-expanded-scylla-fixed.exe](original-expanded-scylla-fixed.exe) | Scylla 按原版实际 IAT 重建出的中间文件，29 个描述符、525 个槽位。一个壳内包装函数未识别；入口头部也未恢复。未验证该文件可独立运行。 |
| [fixed-v4-import-manifest.json](fixed-v4-import-manifest.json) | 524 个新增导入绑定的完整逐项来源、保留的未识别槽位、输入/输出哈希与验证边界。 |
| [repair_fixed_imports.py](repair_fixed_imports.py) | 生成修复副本的脚本；只操作本 attempt 下明确指定的输入与新输出。 |
| [validation.json](validation.json) | 原件哈希、各原有节逐字节一致性、独立进程无调试器检查。 |
| [standalone-v4-window-evidence.json](standalone-v4-window-evidence.json) | 独立启动的窗口标题、控件文本、PID。 |

## 实际观察

1. **原版可动态展开。** 最初的普通调试运行到 `0x12E6014` 第一层解密入口，但主体入口候选仍全零；另一次设置退出 API 软件断点的运行发生栈溢出。这些尝试不足以断言原版无法脱壳。
2. 加载官方 ScyllaHide v1.4，选择 `Themida x86/x64` 配置；日志确认 hook 注入成功，PEB 调试标记已清。把壳内 first-chance 异常交给程序处理后，主体代码、原始 IAT 展开，D3D8、FMOD、IJL15 等模块加载，并创建 DFO 主窗口。
3. 原版到达错误对话框：`AHNHS HSUpdate Fail - UNKnwon 3000ffff,805371903`。已实际读取控件文本。没有确认 HackShield 成功初始化，也没有证明已消费 Script.pvf 或进入战斗。第二次原版对照运行后来发生访问异常并退出，见 `041`、`042` 日志；没有把它记作成功游戏运行。
4. 原版展开后，Scylla 搜索得到 IAT：VA `0xCAB000`、大小 `0x890`。真实调用其 dump 与 IAT fix API，均返回成功状态。解析结果 525 个槽位，其中 `0xCAB634 → 0x13810F6` 是壳内代码，不能直接替换成猜测的 API。
5. **fixed_v3 的启动失败包含漏修的导入地址。** 未修复版本在 CRT 的 `0xC12E48` 间接调用后进入 Shell32，于 `0x75F4D7CF` 非法写入。`0xCAB284` 磁盘遗留值为 `0x75F4D7B0`，未由其现有导入表绑定。
6. 从原版实际 IAT 复核：`0xCAB284 = GetCommandLineW`，`0xCAB27C = GetEnvironmentStringsW`，`0xCAB578` 是 User32 导出，Scylla 命名 `RegisterClipboardFormatW`；本机 `RegisterWindowMessageW` 与它同址，存在导出别名。试验中曾把第三项临时标成 `LoadLibraryA`，参数字符串核对后纠正；**最终修复使用原版运行时导入证据，没有使用该错误推断。**
7. 根据原版 IAT 在 fixed_v3 的新副本上增补 524 个绑定，保留原有 441 个绑定，共 965 个导入符号、189 个描述符。这些数量包括不同槽位的重复 API，不表示 965 种不同 API。`*invalid*` 分组中受未识别槽位影响的后续 User32 名称，逐一核对了本机 User32 导出后重新分组。
8. **最终修复副本在卸载 ScyllaHide 后的 x32dbg 内，以及完全脱离调试器的独立进程内，均创建了 DFO 窗口，到达上述相同 HackShield 错误。** 独立进程还调用 `CheckRemoteDebuggerPresent` 确认没有调试器。

## 失败与未完成部分

- 对 fixed_v3 的首次 Scylla 自动搜索误覆盖约 7.4 MiB，重建文件出现无效导入。实际重新启动后以 `0xC0000135` 退出，见 `022`、`023`。文件 `fixed-v3-scylla-auto.exe` 是失败样本，不是最终产物。
- 手工增补导入脚本的首个单槽位描述符布局未通过 PE 解析校验，保留为 `fixed-v4-rejected-import-layout.exe`；最终版本按连续 DLL 槽位分组，并通过全部新增项回读校验。失败布局未作为最终修复交付。
- 原版转储中的 `0xC05078` 头部仍呈现无效入口字节。对该地址设置硬件执行断点的后续原版运行没有命中，不能声称抓到了原版 OEP。最终 v4 使用的是用户已有 fixed_v3 的启动代码，来源明确，不是新恢复的原版入口。
- `0x4FA1F0 → 0x13BAA5F → 0x12EE7C9` 保护路径在原版已展开现场仍存在。没有验证它的完整语义，也没有消除这类保护路径。
- `0xCAB634` 对应的壳内包装函数仍未识别或去除。它的保留不能证明后续所有调用正常。
- 尚未通过 PVF 实际加载、技能释放、攻击判定或原客户端战斗的动态对照。
- 这些结果支持继续进行入口/保护调用恢复与实际 PVF 消费链跟踪，不支持宣称完整脱壳或还原原始 C++。

## 记录索引

- `001`—`010`：原版第一层解密、壳异常、TLS 停点与提前退出。
- `011`—`014`：原版退出观察对照；软件 API 断点条件下的栈溢出。
- `016`—`021`：fixed_v3 入口、首个启动异常及两个旧指针的动态绑定验证。
- `022`—`023`：Scylla 过宽范围重建文件的实际启动失败。
- `024`—`025`：第三项旧导入参数核对与纠正；随后遇到另一处旧地址。
- `026`—`032`：实际加载 ScyllaHide、选择 Themida 配置，原版完成主体展开。
- `033`—`036`：原版展开现场、内存映像与原始 IAT、残余保护路径。
- `037`—`042`：原版入口候选硬件断点对照，未捕获候选 OEP；后续退出，卸载 ScyllaHide。
- `043`—`047`：最终 v4 在没有 ScyllaHide 时的启动验证与停止。
- `standalone-v4-launch.json`、`standalone-v4-window-evidence.json`、`validation.json`：独立启动证据。

JSON 中 `running=true` 时的寄存器与内存读取不是原子快照。标记 `paused` 的记录才用于现场对应；`033` 最后的首次超范围内存读取失败，`034` 已按正确映像长度完成保存。

## REA 是否真正调用过

之前确实执行过 REA `analyze_function`，不是只有读取 skill 文件：

- `analysis/rea/results/015-state-function.json`，函数 `0x7307B0`，Evidence `ev_d5a20a9df4046515d44da1f508ada209e46fd5798039b1fb62ac4f22db98f062`。
- `analysis/rea/results/104-reaction-state-select.json`，函数 `0x4AF540`，Evidence `ev_c58eb7b8697adee3a3871eae2e1bf94071195fd6a8057810ec9e5acae5776b97`。

这些是之前的局部静态逆向记录，不能当作完整技能、完整源码或脱壳成功证明。本次动态工作实际使用 x32dbg、Scylla 和 ScyllaHide，没有重新启动战斗模型扩展。

## 原件与工具

原件 `DFO/DFO.exe`、`DFO/DFO_fixed_v3.exe`、`DFO/Script.pvf` 均重新校验，哈希与尝试前一致，详见 `validation.json`。没有修改 dnf-native-demo。

工具均在 `analysis/tools/x64dbg` 下，使用独立客户端副本。Scylla DLL 实际版本为 `Scylla x86 v0.9.8`。x32dbg 官方包与 automate 插件核对了 GitHub release 的官方 SHA256；ScyllaHide release 未提供官方 digest，保留官方资产来源、大小检查与本地 SHA256，未把它标成官方摘要验证。

本轮只验证至客户端初始化阶段。原始内存转储、导入修复以及残余保护处理是不同的完成条件。
