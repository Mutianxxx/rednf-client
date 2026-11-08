# V3：精确 LAY 绑定与动作组合身份

本次只补通用来源合同。主工程只读；未添加逐职业或逐技能适配器，未改客户端、原始知识库、历史 V2 checkpoint。V2 的全技能缺口及训练数值边界继续保留。

## 问题与依据

旧导出器把装备层直接追加到以人物 ANI 路径缓存的 clip，并用 `equipment_bound` 跳过后续绑定。如果多个 CHR 槽引用相同人物 ANI，但 LAY 对应槽、重复字段、人物身份或装备组合不同，后一次会复用第一次的装备。人物 ANI 路径只表示源动画字节，不能独自表示动作及外观组合。

当前依据为主工程的 `include/dnf/equipment_motion.hpp`、`src/equipment_motion.cpp` 及 `tests/test_equipment_motion.cpp`。这些合同又用当前 1031 的 CHR/LAY 保存模型交叉核对：

- 盗贼 `[etc motion]` 槽 42 的人物动画为 `Shuriken.ani`，LAY 对应装备动画为 `ThrowKnife.ani`，不能按文件 stem 猜测。
- 圣职者槽 119、120 在 LAY 中明确为空。空槽不是邻槽或同名动画的搜索指令。
- 女神枪手槽 6、7 虽都指向装备 `JumpAttackShoot.ani`，仍是两个原始动作槽，不能在描述层合并其身份。

采用的 LAY 子集是恰好一个 `[LAYER]`、且只有整数 `0`。该 marker 是绑定范围，不是 EQU 绘制深度。按标准化 tag、该 tag 的重复出现序号和 CHR 原值槽索引精确匹配。非空模板必须恰好含一个 `%s` 且没有其他 `%`，替换后核对精确 PVF 成员存在。空、缺失和不支持分别记录，未知字段、顺序、原始槽位及源模型保持不变。

## 导出模型

`tools/catalog_pipeline.py` 新增纯函数 `equipment_motion_binding()`，返回 `resolved`、`empty`、`absent` 或 `unsupported`。记录 LAY 路径、tag/occurrence/slot、字段序号与字节 offset、原值、字段副本、layer 范围及精确目标存在性。`empty` 正常不绘制该装备；其余未解析项进入 `equipment_unresolved`，使完整程序闭包不能无声跳过装备错误。

clip 字典中的三种身份为：

1. 源 ANI：默认渲染变体继续用原 PVF 路径作 key，保留帧、毫秒时间、判定框、偏移和源 ALS 层。它不追加动作装备。
2. 非零纹理变体：`source-variant/<hash>`，hash 包含 ANI 路径、variation 与 body 纹理模式。避免同一个装备 ANI 的第一次纹理变体污染其他变体。导入失败会回滚部分缓存并恢复已存在源 clip。
3. 动作组合：`action-composition/<hash>`。hash 包含人物/CHR 来源身份、原 body 来源、tag/occurrence/slot/field ordinal，以及有序装备描述和 EQU/LAY SourceRef。组合深拷贝源 clip，再只向组合追加解析成功的装备层，保留 `composition.source_clip` 和完整身份。不同槽或外观不能串用装备。

组合的 `path` 与 `source.path` 仍保留原 ANI 路径；`id` 和字典 key 是组合身份。原始 SourceRef 不改写为虚构 PVF 路径，原字节及 hash 继续可追溯。新增字段属于现有 `catalog_schema: 2` 的兼容扩展。

运行时当前通过 `world.data.clips[clip_id]`、`_has_clip()` 和程序 `play.clip` 作不透明字典查询，不要求 key 是 `.ani` 路径。公共执行器不需分支或修改。两条既有实际源程序将由测试核对组合 key、原始 SourceRef、帧序、偏移与毫秒时间不变；实际引擎测试由父级统一串行执行。

`verify()` 改用 `clip.source.path` 查保存的 decoded ANI，不把组合 key 当 PVF 路径。bootstrap 资源验证同时核查组合 hash、原 clip 存在、SourceRef/帧/时长一致、源 clip 无装备污染、源 ALS 不变，以及 CHR/EQU/LAY 保存源 hash。它不把新增组合数量计为新增技能闭包。

## 最小缓存刷新

新增命令仅刷新已经存在的包，使用保存的 actor 索引，不重跑全量 `index`：

```powershell
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tools\catalog_pipeline.py refresh-cached --progress-file reports\native-binding-v3\refresh.json
```

刷新前快照并核对现存包的类型、来源身份及登记 ID/输出路径。bootstrap 使用 actor 描述生成；已缓存 action、skill、resource 分别调用既有按需导出。skill 仍通过当前源程序编译器重新核闭包；不扩展尚未缓存技能。当前预期 16 包：11 bootstrap、2 executable 技能、2 action、1 resource。若用户之后新增缓存，命令会按实际缓存快照刷新，不能把 16 当硬编码限制。

导出、引擎和打包由父级持串行锁执行。此子任务没有执行导出器、Godot 或构建。新导出写当前工作目录；冻结 checkpoint 保持不变。

## 验证入口与边界

父级执行纯 Python 合同测试：

```powershell
& 'D:\ProgramData\anaconda3\python.exe' -X utf8 -B tests\test_equipment_binding_v3.py --report reports\native-binding-v3\python-contract.json
```

测试覆盖重复 tag 与原槽、空槽拒绝 fallback、非法模板/layer/directory、目标缺失、原模型及未知字段不变、同 ANI 不同组合隔离、装备 variation 隔离及失败回滚，并核当前 1031 三类反例与两条实际程序。测试替换低层 I/O，不解包 PVF、不启动引擎。实际通过数以父级产生的报告为准；本文不提前声明通过。

随后父级运行缓存刷新、来源验证、现有程序测试及实际 Godot 集成/编译测试。装备展开攻击资格、完整成长/伤害公式、其他技能 native caller、怪物全部 AI 和用户画面听音手感验收未因本次缓存修复完成。
