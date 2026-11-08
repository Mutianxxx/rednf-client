# 逐技能实现与依据

每项链接分别对应运行规格、实机观察和源文件；表中时间表为当前重建结果。调用链缺口不得用校准时间表替代。

| 技能 / key / 键 | 当前身体阶段 / 效果实例 | 实机创建ID | 实现依据与推导 |
| --- | --- | --- | --- |
| [崩山击](../evidence/skill-chain-analysis/skills/hopsmash.json) / `hopsmash` / A | 2 / 6 | 20050 | 帧4、20050与(123,1,0)、Front/Back层有源/调用依据；水平参数27→90；高度68/抛物线为推导。 |
| [十字斩](../evidence/skill-chain-analysis/skills/gorecross.json) / `gorecross` / S | 1 / 3 | 20028 | 20028与(85,0,82)，单次分支；不执行仅构造而未绘制的追加分支。 |
| [怒气爆发](../evidence/skill-chain-analysis/skills/bloodblast.json) / `bloodblast` / D | 1 / 15 | 20120, 20121, 20122 | 20122/20120/20121，source图+实际绘制时序；身体用CHR buff motion演示回退。 |
| [崩山裂地斩](../evidence/skill-chain-analysis/skills/outragebreak.json) / `outragebreak` / G | 2 / 94 | 20043, 20044 | 20043相对(150,0,0)，20044世界直建；94实例不去重；未解轨迹采用投影锚点。 |
| [血气爆发](../evidence/skill-chain-analysis/skills/bloodblastex.json) / `bloodblastex` / H | 1 / 24 | 20102, 20103, 20104 | 20103/20102/20104，保留结束动画实绘时序，固定持续；CHR身体回退；失效ALS引用保留。 |
| [血气之刃](../evidence/skill-chain-analysis/skills/bloodsword.json) / `bloodsword` / Q | 2 / 8 | 20066 | 20066绝对XYZ、Z60；狂暴前置实测；SKL static[2]前冲为推导。 |
| [浴血之怒](../evidence/skill-chain-analysis/skills/bloodboom.json) / `bloodboom` / E | 1 / 24 | 38002 | 38002相对(0,0,70)，多层爆炸实际绘制；负帧事件不改0帧；身体对齐有推导。 |
| [血之狂暴](../evidence/skill-chain-analysis/skills/frenzy.json) / `frenzy` / W | 1 / 5 | 无新增创建证明 | cast/blast/endofcasting/buff实绘，持久绘制与停止分开；10秒关闭限制为用户实测。 |

## 逐技能机器索引

[skills-index.json](skills-index.json)汇总当前身体、时长、效果实例、source、basis和源证据节点。完整运行数据在 [battle.json](../demo/content/battle.json)，原事件观察在对应技能JSON。

其他主动技能的覆盖状态与分类依据见 [capabilities.json](../validation/upstream/capabilities.json)。目录源规则参考 [build_catalog.py](../reference/catalog-rules/build_catalog.py)，固定结果在 [skills.json](../demo/content/skills.json)。

状态统计：`{"inferred_resource_preview": 46, "unmapped": 33, "non_active": 143, "observed_chain_partial_controller": 8, "excluded": 1}`。

八技能合计179效果实例。嗜魂封魔斩按用户反馈排除，其采集报告留存但不用于正常技能推导。
