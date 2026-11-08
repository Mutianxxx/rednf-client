# DNF 跨平台制作资料与合并结果

本目录汇总 GBA 制作中可复用的资源解析、原版数据、地图与动作研究、编译/验证流程，并合入 `D:\dnf安卓优化\android-dnf-result` 的完整分析结果。后续 PSP、Android 或其他端的内容定义，以本地 **PC 客户端及其 PVF** 为基准。合并过程中保留两份研究的原貌，在统一层更正冲突与过时结论。

本次交付是资料库、可复现工具和数据转换结果。原 GBA 工程与启动入口继续保留。本目录没有选择后续游戏引擎，也没有修改或运行安卓 APK。

**新增女枪手安卓与 DFQ 机制分析：**[完整说明](docs/14-android-gunner-and-dfq-mechanics.md)、[独立补充资料](supplements/android-gunner-dfq-20261017/README.md)。女枪手新增 3,418 个资源、9,573 个动作及 22,614 个位图片段；2,773 份实际加载器隔离读取中 2,772 份通过，1 份 DAT 变体保留未决。DFQ 只研究碰撞、人物动作和技能控制，严禁参考其 UI。22 条源码／原生结论已加入主数据库和系统契约，PC/PVF 继续作为内容基准。

**全量补全入口：**[本轮遗漏审计与结果](docs/09-full-sample-audit.md)、[数据模型和工具](docs/10-models-and-tools.md)、[完整复现顺序](docs/11-full-audit-reproduction.md)。本轮已将全部 **334,927 个 PC PVF 条目**的解密原字节及模型归档到 `research/dnf-evidence.sqlite3`，覆盖 11 个角色定义、2,008 个技能文件、全部地图／城镇／任务／装备／AI／UI／活动等内容；同时重读全部 NPK 资源和三方代码。此前四职业／GBA 区域子集继续保留，规划新版本应优先使用全量入口。

**新增服务端与后续研究：**已保留并索引 `rednf-master` 全部 36,439 文件，合入安卓目录新增 2,432 文件和 9 份修订，保留双方历史。新增 16 条服务端规则契约、428 条消息注册、27 种任务类型候选、全部 3,222 任务的扩展列表，以及 PC 原生宿主接口台账。4 条规则经过原 C++ 函数隔离编译／执行，共 15,201 用例通过。阅读 [服务端与修订合并](docs/12-server-and-revised-android.md) 和 [新版本资料入口及未决项](docs/13-readiness-and-supplement-validation.md)。服务端原 ELF 子模块为空、伤害常量 26／27 项不同，尚不宣称同版本或原版运行一致。

[25 类系统契约](research/system-contracts.json)和[逐项未解台账](research/gap-ledger.jsonl)区分结构、规则、平台策略和运行验证。可以运行 `browse.cmd`，再在浏览器打开 `http://127.0.0.1:8765` 查看源文件、代码、未解项和原尺寸 ANI／IMG。图片仍从哈希绑定的外部 PC NPK 读取。

| 阅读顺序 | 文件 | 用途 |
|---|---|---|
| 1 | [基准、冲突与裁决](docs/01-authority-and-conflicts.md) | 确认什么取 PC，什么只是另一种实现 |
| 2 | [完整制作流程与工具](docs/02-production-workflow.md) | 从只读提取到跨端实现和验收 |
| 3 | [地图、城镇、碰撞与门](docs/03-world-and-maps.md) | 原版地图组织与已查明的合成问题 |
| 4 | [动作、战斗、特效与声音](docs/04-actions-combat-audio.md) | 可复用事实、控制器缺口与验证方法 |
| 5 | [PVF → 安卓任务列表](docs/05-quest-conversion.md) | 数据格式、真实导出结果与现有 APK 的限制 |
| 6 | [平台边界和存档](docs/06-platform-boundaries.md) | PC / GBA / 当前安卓样本的差异 |
| 7 | [后续端口清单](docs/07-port-checklist.md) | 可直接用来拆分开发任务 |
| 8 | [复现与校验](docs/08-reproduction-validation.md) | 命令、哈希、实际验证范围 |

初次合并直接核对当前 `Script.pvf` 的 334,927 个目录项，对旧归档中的 19,646 份脚本逐一核验，均与当前 PVF 一致；当时独立归档的 21,228 个 PVF 内文件继续保留，当前 SQLite 已扩至全量。全部 3,222 份任务已解析并转换成保留有序字段的安卓可读列表；45 组同名候选涉及 44 条安卓记录，尚未正式确认跨端身份映射。初次记录见[合并统计](inventory/pc-consolidation-summary.json)和[转换报告](adapters/android-quests/conversion-report.json)，全量结果见[覆盖统计](research/coverage-summary.json)。

特别修正：旧成长索引的 `sha256=4e6b…` 实际是鬼剑士 CHR 文件哈希。安卓旧报告将其视作整包 PVF 哈希并推断版本不一致，这个推断已撤回。当前整包 PVF 哈希为 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`，详见[对象哈希核验](catalog/provenance-correction.json)。历史文件按原字节保留，请通过合并文档阅读其更正。

| 目录 | 内容和权威程度 |
|---|---|
| `sources/pc/` | 当前完整 `Script.pvf`、`audio.xml` 的原字节副本 |
| `research/` | 全量源数据 SQLite、所有技能／角色／世界模型、代码／资源索引、原生执行证据、系统契约及逐项台账 |
| `schemas/` | 带来源、单位、规则状态和未知项的跨平台行为契约 schema |
| `canonical/pc/pvf/` | 当前 PVF 直接解密的原字节；不包含 GBA 缩放或规则 |
| `canonical/pc/quests.jsonl` | 全部任务的有序字段、完整 token、偏移、字符串链接与原始哈希 |
| `canonical/pc/player-skills.json` | 四职业 712 条源技能的原字段与来源；包含内部项、被动和特殊分支 |
| `canonical/pc/player-classes.json` | 四个原 CHR 的全部字段/token；不强制删成四转职模板 |
| `canonical/pc/entities.jsonl` | 已选择区域/装备等 token 脚本字段；范围见覆盖报告 |
| `catalog/` | 全 PVF 目录、原 PC 文件哈希、证据索引、系统索引、冲突裁决 |
| `adapters/android-quests/` | JSON/JSONL 任务列表、样例、同名候选、225 字节目标的阻塞原因 |
| `imports/android/` | 安卓结果包完整文件快照，原相对路径和字节不变 |
| `imports/android-revision-20261016/` | 后续新增／修改的安卓研究；当前完整视图见修订清单，旧快照不覆盖 |
| `imports/rednf/` | 用户提供服务端完整源码／构建／文档／三方许可快照；与 PC 的版本关系单独验证 |
| `imports/gba-workspace/` | GBA 源数据、分析工具/文档、原尺寸六类角色示例、生成元数据、运行代码、测试与历史报告；解析器代码和 Lua 参考脚本 |
| `tools/`、`tests/` | 本次新增的导入、PC 核对、任务转换、查询与校验工具 |
| `inventory/` | 导入来源、哈希清单和本轮验证报告 |

PC 的 NPK、音乐等大资源保持在外部只读来源。每个文件的当前哈希在 [PC 来源文件清单](catalog/pc-source-files.jsonl) 中；完整 NPK/IMG 目录保存在 [NPK 索引](imports/gba-workspace/gba-research/reports/npk-catalog.json)。本资料包未重复拷贝整个 PC 客户端，也未拷贝 GBA 的全部派生图片/二进制，使用源尺寸图像时需携带匹配哈希的客户端。安卓包里的 APK、解包数据、图片、汇编和 Java 则完整保留。

**原始资源存在、解析成功，不等于对应玩法已经完整实现。** PC 伤害／奖励默认公式、全部技能控制器及服务端行为仍有待恢复；Android FIE／DS 现已全部经过实际加载器隔离读取追踪，部分字段意义和消费者仍未知。GBA 的既有验收不能证明未来端口与 PC 完全一致。具体对象、证据和验收条件见[全量审计](docs/09-full-sample-audit.md)及[系统契约](research/system-contracts.json)。

后续协作请遵循 [agent.md](agent.md)。本包用于本地研究和端口规划，解析器/Lua 代码许可与原游戏素材权利分别记录，不能将 MIT 代码许可扩展为素材许可。
