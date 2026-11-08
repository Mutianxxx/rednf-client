# 跨平台 DNF 制作资料约定

本目录用于规划与实现后续端口。内容基准是哈希固定的本地 PC 客户端与 PVF；具体平台和开发优先级由后续用户任务决定。

- 先读 `README.md`、`docs/01-authority-and-conflicts.md`、`catalog/conflicts.json`。`imports/` 是保留原貌的历史证据，其中旧结论的修正在合并层说明。
- PC/PVF 的脚本、图片、声音、条件、原坐标、毫秒时序优先。PC 未恢复的执行规则记录为未知，不用 Android 或 GBA 近似值填补后宣称原版一致。
- 来源、平台无关模型、平台编译与运行分层；保留原字节、哈希、路径、列表命名空间、重复字段、顺序 token、IMG 帧及逻辑尺寸、ANI 全帧和依赖。
- GBA 的按键、240×160、缩放、量化、CD、简化任务/AI、测试模式和 SRAM 是平台策略；Android 的固定任务槽、触控、辅助功能和本地编号同样是平台实现。
- 同名只建立候选。PC LST ID、文件序号、Android 数组位置、物品 category/id 不可直接互换；任何正式映射都要给证据与版本。
- 任务列表 JSON 可以承载 PC 完整字段。现有 APK 的 225 字节任务定义需要另外实现条件/编号/编码映射和运行时扩展；没有完成这些步骤不得声称可以直接注入或正常执行。
- 原客户端、原 APK 与外部分析目录只读。重新生成写入新输出或明确的派生文件；导入证据不可无声覆盖。输入变更后先检查哈希，再重新建立基准。
- 区分原始数据覆盖、解析、编译、运行接入、实际测试。静态分析与源图预览不能替代游戏行为验收。

## 全量审计后的新增约定

- 新版本规划先读 `docs/09-full-sample-audit.md`、`research/system-contracts.json` 和 `research/gap-ledger.jsonl`。`canonical/pc/player-skills.json` 的 712 条是四职业历史子集；全量 2,008 个 SKL 在 `research/all-skill-files.jsonl`，全部 PC 原字节／模型在主 SQLite。注册不代表正式开放，内部／测试文件不得混作可选技能或副本。
- 全部 PC 原始数据、GBA 适配、Lua 实现、Android 原生规则保持不同命名空间。Android 的隔离 ARM 验证不构成 PC 等价性；未恢复的服务端、内建控制器和公式不得用三方近似拼成“原版规则”。
- 本地旧 IMG 的 136 个 version 1 文件使用 17 字节签名及交错帧记录／像素布局。使用 `tools/pc_assets.py` 的原字节读取结果；历史 GBA 改头连续索引方案不能用于这些文件。原字节、偏移、链接帧和异常载荷均须保留。
- `audio.xml` 的 RANDOM／GROUP 子 ITEM、TAG 关系和 PROB 原值必须保留，不能只导出顶层 ID／FILE。全部辅助任务列表保留容器结构，不能强行套 ID／路径配对。
- 未解项记录对象、偏移／行号、证据、影响／阻塞类型及验收条件；动态资源绑定、源码词法索引和行为恢复采用不同状态。函数名关键词分组不能当作语义验证。
- 研究数据库写入结束后 checkpoint；迁移只携带正式数据库，不使用 `-wal`／`-shm` 协调文件作为交付资料。外部 NPK 仍须匹配来源哈希。

## 服务端与后续修订

- 新版本先读 `docs/12-server-and-revised-android.md`、`docs/13-readiness-and-supplement-validation.md` 和 `research/new-version-readiness.json`。服务端快照为 `imports/rednf`，单独使用 `rednf-server`／`rednf-expanded` 命名空间。
- rednf 是源码重建，当前 `.origin_1031` 为空；不能把仓库旧比较报告视为本机已重跑。PC 的 27 项伤害常量与服务端读取 26 项保持差异台账，版本／舍入／协议未匹配前不能覆盖当前 PC 基准。
- 原 `.inc` 隔离编译的 15,201 用例只验证所给源码与模型，不能称原 x86 ELF 或完整游戏验证。展开 `.inc` 需保留原路径／行号、未处理的宏和不明确 include。
- Android 第一次快照原字节不变；当前外部源视图用 `inventory/android-current-source-manifest.jsonl`。来源变化另建版本，不覆盖历史导入或通过跳过哈希消除差异。
- 服务端和安卓补充分析通过 `publish_research_supplement.py` 汇入系统契约／台账；重建基础审计后再执行补充链，避免遗漏后加入的证据与计数。


## 女枪手与 DFQ 研究边界（2026-10-17）

- 先读 `docs/14-android-gunner-and-dfq-mechanics.md`；新 APK 在 `supplements/android-gunner-dfq-20261017`，与鬼剑士历史来源分开。使用新的 ACT/LZMA/292 字节任务解析，不覆盖旧解析与原字节。
- `dfq-mechanics` 仅限碰撞检测、人物动作、技能释放和相关配置；严禁引用 DFQ 的 UI 布局、交互界面设计或 UI 资源。配置中的图标路径只保留为未跟随的原文本。
- PC `atgunner.chr`、ATAnimation/ATEquipment 与 SKL/ANI/NUT/audio.xml 为女枪手内容基准；安卓局部 ID、修改菜单、DFQ 连招参数和公式均不是 PC 权威值。
- 新的 `data/portable-action-contract.json` 用于规划坐标层、武器/特效/弹丸、续段、独立多段命中与保护清理。数据解析、原生隔离读取和实际游戏验证保持分级，不把补充研究视为游戏已修复。
- 重建基础资料及既有服务端补充后，再执行 `tools/publish_gunner_dfq.py` 与 `tools/verify_gunner_dfq.py`；旧发布脚本不会自动合入本次来源。
