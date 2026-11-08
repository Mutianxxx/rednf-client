# 资料与证据归档

2026-11-02：客户端/PVF、1031/60US 逆向、安卓参考、REP 研究、知识审计、两大补充知识包和 native-demo 历次运行成果已按来源归档。

2026-11-09 精简：撤出 `dnf-native-demo/reports/`、`dnf-godot-skill-demo/reports/`、`dnf-result/imports/`、各目录内 PVF 派生文件（`.skl/.ani/.nut/.aic/.equ/.lst`）与 `40jp-reverse-source/ARAD.exe`，共约 690 MB；保留文档、清单与统计（约 44 MB）。下方「归档结果」中的 92,141 别名 / 910,942,508 字节是精简前的完整归档口径，清单未回改，明细见 [INDEX.md](INDEX.md#2026-11-09-归档精简)。

从 [领域索引](INDEX.md) 进入；本次重构依据为 [架构大纲](architecture/ARCHITECTURE-REFACTOR-OUTLINE.md)，资料裁决规则为 [知识规则](policy/KNOWLEDGE_POLICY.md)。

## 归档结果

- 92,141 个来源路径别名，对应 59,613 份唯一 payload；32,528 个重复别名共享资料。
- 来源逻辑字节 8,252,302,155；去重和可逆压缩后 payload 为 910,942,508 字节。目录额外包含清单、索引、工具和少量还原样例。
- 每份保存来源路径、原始大小/SHA256、存储大小/SHA256 和 codec。大文本 gzip 还原后与原始字节完全一致，小文档可直接阅读。
- 以上是文件保存和字节校验覆盖，**不是全部资料已语义通读、全部技能实现或原版动态验收**。

## 核验与读取

- [实际归档清单](catalog/source-manifest.json)、[归档统计](catalog/archive-summary.json)。
- [11 项代表还原核验](catalog/restore-verification.json)，覆盖主要来源、压缩和重复别名。
- [最终 payload 全量核验](catalog/full-payload-verification.json)记录最终 manifest 对应的存在性、解压、长度和 SHA256。
- 读取命令见 [INDEX.md](INDEX.md)；`tools/read_evidence.py --extract 原路径` 只在本资料目录还原，不依赖原工程。

## 明确保留的边界

大型原始客户端/PVF/NPK/APK、用户存档、构建缓存、历史候选与重复生成截图/资源帧保持原位，按 [排除清单](catalog/excluded-files.json) 和 [范围摘要](catalog/exclusion-summary.json)追溯。小型逆向原始 `.bin`、参考图示和原文档已按限定规则补存。旧 GBA 实现/派生数据与 DFQ UI 不导入。

归档工具首次代表还原暴露的共享 canonical 清理问题及修复分别保留在 [初次失败](catalog/restore-verification-initial-failure.json)、[修复收据](catalog/canonical-storage-repair.json)，最终验证以本目录最新核验报告为准。原资料、原工程和用户存档未修改。

证据区分：当前源字节、原生静态/动态证据、自动运行验证、明确推理、用户测试和未知项。equipment458/459 的失败收据继续保留，归档不会把它提升为已完成节点。父流程另保存在 `unvalidated-native-delta/` 的源码差异也不会自动应用。
