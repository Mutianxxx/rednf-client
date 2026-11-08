# 独立工程迁移记录

2026-11-02：独立目录、资料归档、457 源码迁入及首批 OO 提取完成，所有目标已编译。
FrameStatistics、人物表现 46 项、完整核心、音频 57 项和隐藏 UI 39 项自动检查通过；
源码归属与无窗口启动身份审计通过。实际身份见 `cache/refactor-build/build-verification.json`。
封存清单原通过 `LATEST_CHECKPOINT.json` 定位，前台画面、听音、手感和原版动态比较仍待确认。

首节点：`checkpoints/20261102T001149792676Z-architecture-A0-A2a/`，1,113 文件、
988,972,582 字节，两遍哈希通过。2026-11-08 整理入库时该检查点及其 `LATEST_CHECKPOINT.json`
入口已删除（3.0G 历史节点快照），需要时用 `../checkpoint_refactor.py` 重新封存生成。

后续所有运行代码仅在本目录修改。原始工程保持只读。

## 实际迁入

- 816 个文件按原始清单/哈希迁入；125 个原实现单元按职责分组。
- 811 个导入文件维持原字节，5 个登记修改是原生合同 include、人物表现委托和应用入口。
- 新增 GameApplication、CharacterPresentation/ICharacterDrawSink、FrameStatistics，并接入实际运行。
- 457 原始修改锚点和 459 未验证差异分别保存于资料目录，后者没有应用。
- 构建/测试/资源配置与用户存档隔离；具体路径和当前会话见 `../PROGRESS.md`。

## 尚未完成

完整公共接口收敛、其他表现对象、UI命令/读模型、World 状态所有权及同机渲染性能基线
仍按总体方案推进。当前代码重组不代表完整 A0–A6 或全职业游戏内容已经完成。
