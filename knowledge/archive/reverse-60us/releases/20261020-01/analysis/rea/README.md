# REA 实际执行与证据

本工作区以 REA skill v42 / rea-agents 6.7.0 调用 Ghidra 12.1.4，目标为现有 `DFO_fixed_v3.exe`，
SHA256 `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`。
没有修改用户 Codex MCP 注册；`rea_session.mjs` 通过工作区自建 MCP stdio client 保持一个 provider session。
原件只读导入到 REA 的临时分析工程，没有执行游戏。

`results/` 保留完整工具回应，包括失败；`combat-evidence-bundle.json` 为 REA 导出的完整记录，
`evidence-index.json` 提供 Evidence ID、请求、来源、provider、函数 body 范围与局限。
`index_evidence.py` 将记录中的伪代码另存 `.c` 方便检索；这些文本不是可直接编译的原源代码。

001..012 是修复 MCP timeout 参数、引擎依赖与启动选项过程中的失败诊断，不能当成功反编译证据。
014 打开当前固定版目标，015 起才有成功 native Evidence。
018 的计算成功，但完整 stdio 回应超预算；工具明确记录 retained Evidence ID，完整记录已在 bundle，
不能因外层 `isError` 就误称反编译未执行，也不能丢弃该运输层错误。

本次 Ghidra 禁用了 `Reference`、`Decompiler Parameter ID`、`Decompiler Switch Analysis`，
避免展开客户端的全局分析在特定分析器中耗尽启动期限。
必须保留这一分析配置：部分 switch 的 FunctionManager body AddressSet 只包含入口与少数块，
伪代码可能包含更广的分支；callers/callees 的 complete 状态只针对 **Ghidra 已识别 body 内已解析引用**。
它不能证明整个技能/协议 case 都已覆盖，也不能证明 body 外的 case 不属于此函数。
本任务以另存原始字节、显式跳表和逐指令检查补充，而非把工具函数边界当真值。

反编译器对 protected float/int 和特殊调用约定会推错参数类型；
例如 AABB 参数或受保护 float 的 bit pattern 可能被显示为普通 float/int cast。
实现中的字段解释和算术必须回查指令与数据布局，不能照抄这些类型。

Ghidra 官方发行包与下载哈希在 `../tools/ghidra12-source.json`，Java 使用机器已有 JDK21。
当前 REA 配置和下载只在工作区范围，不需要改用户全局注册。
