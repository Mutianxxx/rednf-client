# 当前 60US：NPK 注册顺序与重名路径选择

**已恢复的 packed NPK 分支按 Windows 文件枚举顺序注册包，向链表尾追加；读取时从链表头开始，遇到第一个包含该 IMG 逻辑路径的包即停止。**
当前目录的只读 Win32 枚举观察中，`skin.npk` 排在 `skin1.NPK` 之前，因此这条分支在当前目录条件下预计选 `skin.npk`。
这是当前 EXE 静态控制流与当前文件系统观察共同支持的推导；没有运行游戏，也没有捕获游戏进程内最终 IMG 对象。

所有地址限定于：

```
D:\dnf\60US\DFO\DFO_fixed_v3.exe
SHA256 a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
ImageBase 00400000, x86
```

未使用 rep-player 的排序、overlay、ETC 或 fallback 规则作为证据，也未修改资源读取器或原文件。

## 函数调用与字段证据

| 地址 | 字节与控制流所支持的行为 |
| --- | --- |
| `0040C8FA` / `0040C922` | 构造 `ImagePacks2/` 字符串并调用 `00B0D3A0`。 |
| `00B0D3BE` / `00B0D3D3` | 同一路径分别以注册组 `0`、`2` 调用 `00ACA380`。 |
| `00ACA380` | 组号乘 `0x10`，加全局 `010DAB60`，交给 `00ACA0C0`。 |
| `00ACA0C0` | 规范目录尾斜杠，保存并切换当前目录，以 `*.npk` 枚举；结束后恢复原当前目录。 |
| `00ACA16A` | 调用 `00C04322`，其 `00C0433F` 直接调用 IAT `0140F064`，为 `FindFirstFileW`。 |
| `00ACA320` | 调用 `00C043FF`，其 `00C0441B` 直接调用 IAT `0140F074`，为 `FindNextFileW`。原扫描函数没有额外排序步骤。 |
| `00ACA1A2` | 每个候选包先调用 `00AC8E00` 校验目录摘要；失败分支记录错误并进入下一个枚举项。 |
| `00ACA1F7` | 对通过摘要检查的包调用 `00AC9E30` 读取 NPK 目录。 |
| `00AC9E83` / `00AC9F10` | 比较 `NeoplePack_Bill\0`，读取条目数；使用全局 `00FF1980` 指向的 `puchikon@neople ...` 宽字符串低字节解名称。 |
| `00ACA273–00ACA299` | 取 `sentinel.prev`，调用 `00ACB540` 创建 `next=sentinel, prev=old_tail` 的节点，再写 `sentinel.prev=new`、`old_tail.next=new`；即追加到链表尾。 |
| `00ACB582–00ACB594` | 新节点 `+4=prev`、`+0=next`，`+8` 开始复制包内容，支持上述链表解释。 |
| `00AF20E0` / `00AF2116` | IMG 读取函数在 packed 标记分支调用 `00AC9C10`，组号为 `0`；随后读取 32 字节 IMG 头并分支比较 v1 / v2 签名。 |
| `00AC9C82–00AC9C91` | packed 普通查找桥，按组号选择全局 registry 并调用 `00AC95B0`。 |
| `00AC95E6–00AC9609` | 从 `sentinel.next` 开始，对每个包调用 `00AC9220`；找到非空条目即跳至 `00AC9616`，否则 `node=node.next`。因此较早注册的包先命中。 |
| `00AC9616–00AC967C` | 返回命中条目的偏移/长度，打开该节点所记录的 NPK，定位 payload；无后续同名包覆盖步骤。 |
| `00AC9220` | 包内逻辑名称查找，返回条目字段地址 `node+0x28`，未命中返回零。 |

辅助读取函数 `00AC92F0`、`00AC9450`、`00AC9690` 同样从包链表头依次查找并在首个命中处退出，可在探索性整段汇编中复核。

`evidence-index.json` 列出 13 份整理过的 `.bin` / `.asm` 片段，每份都有 VA、RVA、文件偏移、片段 SHA256 与 EXE SHA256。
其他整段汇编为定位时使用的探索材料；以索引中从明确函数起点开始的片段为优先核验入口。

## NPK 目录摘要的独立验证

`00AC8E00` 先读取 `+16` 的条目数 `n`，计算：

```
directory_end = 20 + n * 264
hashed_length = floor(directory_end / 17) * 17
expected_digest = file[directory_end:directory_end + 32]
accepted = SHA256(file[0:hashed_length]) == expected_digest
```

SHA256 初始化函数为 `008AEBB0`，其中常数是标准 SHA256 初始状态，更新与最终输出为 `008B26E0`、`008B27B0`。
`validate-directory-digests.py` 用 Python 标准库 `hashlib.sha256` 独立重算当前 708 包：**708 全部通过**。
因此两份 skin 包都不会因这层摘要检查被排除。

| 包 | 目录末尾 | 实际哈希长度 | 验证 |
| --- | ---: | ---: | --- |
| `sprite_character_swordman_equipment_avatar_skin.npk` | 3,716 | 3,706 | 通过 |
| `sprite_character_swordman_equipment_avatar_skin1.NPK` | 19,556 | 19,550 | 通过 |

原始 IMG 条目偏移因此常见为 `20 + n*264 + 32` 或更大；这 32 字节摘要此前仅体现在 NPK 条目范围检查内，现在有原生消费者与独立计算支持。

## 当前目录的枚举观察

`observe-enumeration.py` 仅调用 Win32 `FindFirstFileW/FindNextFileW` 读取 `D:\dnf\60US\DFO\ImagePacks2\*.npk`，未启动 DFO。
`filesystem-enumeration.json` 保留全部 708 个返回项、时间、平台和结束错误码 `18`。

零起始序号：

| 顺序 | 包 | 文件大小 |
| ---: | --- | ---: |
| 305 | `sprite_character_swordman_equipment_avatar_skin.npk` | 4,280,119 |
| 306 | `sprite_character_swordman_equipment_avatar_skin1.NPK` | 29,001,478 |

若 IMG 通过上面的 packed 注册组读取、目录内容及枚举顺序维持此次观察条件，`sm_body0000.img` 会先在 `skin.npk` 命中。
`observed-conflict-choices.json` 对全部 360 个冲突路径记录同样推导及候选枚举顺序，供预览配置审阅；它没有自行修改 `Assets` 的显式选源规则。

**不能把上述结果概括为“编号小的包永远优先”或“字典序固定优先”。** Windows 文件枚举结果并不由此 EXE 的算法保证。若目录、文件系统、补丁集合、注册先后或 packed 模式变化，应重新取证。

## localpackage.lst 与当前未知

`DFO/localpackage.lst` 是二进制内容，长度 72,038，SHA256 为：

```
ea73f65a8108119d319b32659facead78901938443eeb9bb9f666ed38e87c99e
```

文件中可定位 `ImagePacks2` 与基础 `skin.npk` 名称，未找到 `skin1.NPK` 名称。这里只保留原始偏移和上下文，未将其当成运行时加载清单。
当前 EXE 对 `localpackage.lst`、`NpkIndex.etc` 的 ASCII / UTF16 完整名称检索均未命中；**名称未命中不能证明不存在动态拼接或外部模块路径**。
已定位 NPK 扫描及查找路径不读取这份 manifest，也不使用本任务以外来源项目的 NpkIndex 算法。

仍待游戏运行时核对：图像对象 packed 标记的最终值、其他目录是否在此之前注册、选中人物及装备最终请求的逻辑路径，以及进程实际持有哪份 IMG。
