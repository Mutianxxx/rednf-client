# 服务端源码与安卓后续研究合并

本轮在全量 PC／PVF、Lua、Android 审计之上，加入用户提供的 `rednf-master`。本目录交付研究资料、规则模型和验证工具，没有启动服务端、修改 APK 或制作新游戏客户端。

## 来源固定与裁决

`imports/rednf/` 按原路径保留全部 **36,439 个文件、219,672,886 字节**，清单为 [rednf-import-manifest.jsonl](../inventory/rednf-import-manifest.jsonl)。其中项目 C/C++ 22,833 个文件、构建／文档／数据 112 个、三方库 13,494 个；三方库不计为游戏规则恢复。原仓库的 CC BY-NC-SA 4.0 声明和各三方许可原样保存，不能将此前解析器的 MIT 许可推广到这些源码或游戏素材。

`.origin_1031/` 在这份输入中为空。README 声称的原运行时 ELF、服务器 PVF、SQL 子模块没有包含在当前文件树。仓库 `remake/README.md` 还保留“game 不在目标中”的旧状态，而当前根 CMake 确实包含 game。已有二进制比较报告作为历史来源声明保留，本次没有原 ELF 可以独立重做该比较。**服务端规则采用 `rednf-server` 命名空间，尚不视为本地 PC 的默认实现。**

Android 外部分析目录在首次导入后增加 **2,432 个文件**，修改 **9 个文件**。旧 `imports/android/` 的 55,850 个文件保持原字节，新旧不同内容及新增文件共 2,441 个保存在 `imports/android-revision-20261016/`。当前完整 58,282 文件视图由 [android-current-source-manifest.jsonl](../inventory/android-current-source-manifest.jsonl) 指向对应快照；[修订记录](../inventory/android-revision-summary.json) 保留双方哈希。校验器同时检查历史快照、本次修订和外部当前来源，没有通过忽略输入变化来消除错误。

新安卓研究中的 **1,257 份 PC 原字节样例**全部重新对照本包 PVF，12 条实现结论中的 24 处 PC 证据哈希也已重核。其 117,062 条扫描是本包 334,927 条全量审计的子集，数量不相加。完整规则及其未知项在 [android-revision-findings.json](../research/android-revision-findings.json)，核验见 [合并报告](../research/android-revision-merge-report.json)。

## 可直接复用的新增成果

| 内容 | 产物与含义 |
|---|---|
| 项目源代码 | SQLite `server_files` 为全部文件给出处置，`server_search` 全文检索项目文本；原文可下载 |
| 函数与调用 | 36,269 个 C/C++ 词法函数候选；保留调用位置、命名空间、源文件哈希；不是 AST 或语义完成数 |
| 聚合器展开 | 198 个聚合器中 820 个跨文件函数候选；每行映射回原 `.cpp`／`.inc`，见 [展开索引](../research/server-expanded-functions.json) |
| PVF 消费者导航 | 5,681 处标签字符串，涉及 2,363 种当前 PC 标签；[候选表](../research/server-PC-tag-candidates.jsonl) 不自动关闭字段语义缺口 |
| 消息处理 | [428 条字面注册](../research/server-packet-dispatch.json)，保留顺序、槽号、类名、源行和方法候选；槽号尚未与当前 PC 线协议实测对应 |
| 任务类型 | [27 种服务端枚举候选](../research/server-PC-quest-type-candidates.json)，覆盖当前 PVF 出现的全部 20 种类型字符串；同标签不等于跨版本身份已证明 |
| 具体规则 | [16 条规则及证据](../research/server-rule-findings.json)与[统一行为契约](../research/server-behavior-contracts.json)；含任务、技能资格、伤害管线、修理、强化读取与消息分发 |
| 安卓任务方案 | [全部 3,222 份任务的扩展列表](../adapters/android-quests/pc-server-semantics.jsonl)，保留 PC 有序字段及服务端类型候选，仍标注 `Android_execution_ready=false` |
| PC 宿主接口 | [全部可读 Squirrel 的 sq_ 调用](../research/pc-native-host-api.json)，5,828 个调用点、446 个名称，其中 445 个未发现脚本定义的宿主候选；剔除函数声明，保留接收者上下文及脚本同名定义；原生内建技能控制器仍需另外恢复 |

`.inc` 展开只处理可唯一解析的引入，保留宏与 `remake_verify` 两个分支，不假装执行了完整预处理。`importQuestScript` 的函数签名在 `.inc`、函数体在 `.cpp`；现在可在 `rednf-expanded` 中检索，不能因单文件函数识别不到而判为空桩。

## 已明确的规则与差异

任务奖励表按 `vector.at(level)` 直接用等级作索引，不先减一；越界路径会抛异常。难度字符映射未命中时权重为 100。等级差不大于 6 时惩罚倍率为 100，7–11 取 green 参数，大于 11 取 grey 参数。经验先乘难度权重再乘等级惩罚，每次整数除法都保留截断；premium 与成长奖励另外计算。金币还要求对应奖励类型及 itemID=0 的奖励条目，并应用 `[gold multiple]`。事件标志、忽略任务等级标志对索引选择和惩罚的影响不同，不能合成一个“奖励倍率”。

`[grade]` 对应任务类别 `QuestScript.m_questType → Quest.m_type`，`[type]` 对应条件类型 `m_triggerType`。前者的 `[normaly repeat] = 4` 令该经验函数返回 0；后者的 `[meet npc] = 4` 不能据此判为无经验。这两个枚举及原始标签已在任务导出中分开，[类别候选](../research/server-PC-quest-category-candidates.json)保留直接字面分支，嵌套分支仍需看原源码。

技能学习资格同时检查分支上限、目标技能等级、角色等级、等级门槛与升级间隔。第二成长分支上限为 0 时回退基础分支上限；无效分支、间隔为 0、数组越界等需要调用者契约，不能把当前函数单独当作完整学习流程。

修理费先做 `(grade+5)*base/10` 的整数除法，再进入浮点运算；把这一步改成浮点会改变低价格结果。精确表达式及 binary32 模型见 [server_rule_models.py](../tools/server_rule_models.py)。

伤害常量发现**版本／消费者差异**：当前 PVF `[damage fomula constant]` 有 27 个值，而这份服务端读取 26 个 float。[逐位置候选表](../research/server-PC-damage-constant-candidates.json)保留偏移、值、候选字段名与未消费尾值，未给第 27 项编造用途。完整伤害函数、结构与调用者在源码和数据库中，不把其中一段乘法当作完整伤害公式。

另有需要保留的源码行为：`UserQuest::check_quest_subtype_condition` 的 subtype 7 比较通过后仍落入 default false；`finish_quest` 在某个未找到定义的路径仍可能解引用空指针。它们应通过原 ELF／调用者确认，研究合并时没有悄悄修正为“理想规则”。

## 实际验证范围

[服务端规则验证](../research/server-rule-verification.json)将六份原 `.inc` 原样包含到隔离字段视图，用已有 GCC 15.2.1 编译为 ARM7TDMI，再由 Unicorn 执行：

- `can_learn`：6,000 组输入，覆盖允许与拒绝。
- `getMaxSkillLevel`：6,000 组输入。
- 等级差惩罚：201 组，含阈值两侧。
- 修理费用：3,000 组，含零耐久上限、满耐久和不同倍率。

15,201 组全部通过。这是**提供的 C++ 源码与整理模型的交叉验证**；未覆盖未定义输入、原 x86/x87 精度、网络包、完整调用者和实际游戏。历史 Android 原指令隔离验证仍独立保留，不能与此混称原 PC 游戏验证。

复现顺序和查询命令见 [补充验证与新版本入口](13-readiness-and-supplement-validation.md)。
