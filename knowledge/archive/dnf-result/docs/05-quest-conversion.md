# PVF 到安卓任务列表

本轮已提供真正的数据转换器 [convert_quests.py](../tools/convert_quests.py)，输入是当前PC PVF解出的全部任务IR。输出为 [quest-list.json](../adapters/android-quests/quest-list.json)（`quests`数组）及 [quest-list.jsonl](../adapters/android-quests/quest-list.jsonl)（逐行对象），均为UTF-8。共3222条；原有字段、重复项与顺序保留，原始token和字节另外保存在PC共同层。

这是供Android代码读取/显示的PC任务列表。目标客户端需要实现PC条件解释器和奖励默认规则，才能执行任务。它不能直接作为当前APK的 `quests.bin` 使用；两种目标的差异如下。

| 目标 | 可行实现 | 本次状态 |
|---|---|---|
| 新Android/其他端 | JSON任务列表 + PC规则解释器，保留全部PC字段 | 列表已生成、可查询；解释器和PC运行行为尚待实现 |
| 保留现有APK | 将PC规则编译到原225字节记录，或扩展native任务系统 | 已输出逐条阻塞原因；没有生成猜测的二进制，没有改APK |
| 任务编辑器检索 | 从PC列表导出名称目录并在UI按名称/ID检索 | 可直接读取display与pc_ids；不能把编辑器索引当作执行定义 |

## 列表字段

机器格式约束见 [quest-list.schema.json](../schemas/quest-list.schema.json)。JSON与JSONL每条任务使用相同对象结构；JSON外层包含`schema`和`quests`。

| 字段 | 定义 |
|---|---|
| `id` | `pc:<整包PVF SHA-256>:<原QST路径>`，不与APK下标混用 |
| `pc_ids` | 原LST路径与注册ID数组；缺失/多重注册不捏造唯一ID |
| `source` | 原路径、整包和QST哈希、原字节路径、canonical行号 |
| `display` | 名称、接取/条件/完成/失败文本；保持原文本内容，不擅自把字面`\n`换成脚本语义 |
| `pc_descriptors` | 等级/职业/成长、前置/互斥/关联、NPC、目标与奖励、地下城、接取道具、完成效果等的原字段摘要 |
| `original_fields` | 全部有序标签、值、token_index与offset；包括未知标签和结束标签 |
| `unresolved_string_links` | 未解析的listId/key；本轮0项 |
| `execution` | 需要PC任务解释器，当前`ready=false`；防止把列表可读误当成任务已可玩 |

摘要不定义多个条件之间的AND/OR、缺省、参数单位或最终奖励公式；解释器必须回到原字段和执行证据。未命名任务保持空名称，仍以路径/ID可检索，不自动判为正式开放任务。全任务导出也包含测试/事件/内部定义，正式内容范围需要注册与准入审核。

脚本解析保留5字节token的类型、原32位整数、原字节与偏移；type9+10按n_string.lst的listId和key解析。原始字符串池及STR文件已保存。`n_quest/dailyrandomquest.lst`、`epicquest.lst`、`trainingquest.lst` 未被普通ID/路径读取器解释，单独留在分析报告；其原字节不丢失。当前注册ID来自 `n_quest/quest.lst`，共有3015条列表记录；3222是QST文件数，不能将二者混为正式开放任务数量。

## 已有APK格式与阻塞项

APK任务定义是2字节数量后接530条225字节记录；运行时268字节、任务状态区530字节、任务存档790字节均是不同布局。每条有3个前置、3个完成条件、2个固定奖励、4个选择奖励；名称32字节、描述128字节使用未完全恢复的自定义字形编码。

当前已确认部分类型消费者：完成要求type1查询物品、type5读取金币、type12查询任务状态；不得把其余类型统一解释成杀怪。PC NPC/物品/任务ID也没有到APK本地编号的已确认全量映射。PC `[gold multiple]` 与奖励参数还依赖执行默认计算，不能从`[reward int data]=0,100`写出最终100金币。

因此每条225字节目标均标为blocked，具体见 [legacy-225-assessment.json](../adapters/android-quests/legacy-225-assessment.json)：条件/ID映射、文字编码、默认奖励计算、硬编码数量和存档迁移需要解决。UTF-8长度检查仅是预警，不作为自定义字库编码后的长度。没有采取截断条件、删除奖励或猜类型编号的办法。

扩展现APK时，应先把530条原定义无损解码/重组并做实际回归，再逐项确认native消费者、构建PC→APK的任务/NPC/物品/地下城映射，输出逐条可表达性报告；处理槽位超限、状态区、NPC任务列表和存档后才允许注入。

## 真实对照与运行命令

[name-candidates.json](../adapters/android-quests/name-candidates.json)包含45组同名候选（44条APK记录），保留双方条件与奖励表达。规范化仅供检索，未确认身份映射。铁匠林纳斯例子见 [冲突C04](01-authority-and-conflicts.md)及 [examples.json](../adapters/android-quests/examples.json)。

在本目录运行：

```powershell
python -X utf8 -B tools/convert_quests.py
python -X utf8 -B tools/query.py quest --name 铁匠林纳斯
python -X utf8 -B tools/query.py quest --path n_quest/elvengard/lorien/epic_1_lorien_1.qst --full
```

重新导出会更新 `adapters/android-quests/` 内派生文件；原PC字节和安卓快照保持只读。全量数量、未解链接、候选与二进制写入数见 [conversion-report.json](../adapters/android-quests/conversion-report.json)。
