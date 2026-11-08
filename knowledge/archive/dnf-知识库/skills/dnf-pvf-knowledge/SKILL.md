---
name: dnf-pvf-knowledge
description: DNF PVF 修改知识库（炼化自 dnf-pvf-tutorial 的 1912 篇社区教程 + PVFTools 对 PVF/NPK/IMG 二进制格式的逆向）。Use when the user asks how to modify DNF game content via PVF files — equipment attributes/triggers/effects, skills/CD/damage, monsters/APC/pets, items/shop/drop/activities, tasks/maps/fashion, ACT/ANI/NUT/UI formats — or asks about PVF/NPK/IMG binary format details.
---

# DNF PVF 修改知识库

本项目新增 `pvf-utils-info` 与 `PVF-Ai-Agent-Workbench-3.1.1` 为补充参考来源。先读 [pvf-utils-info 通用运行时](references/10-pvf-utils-info-runtime.md)、[Workbench 3.1.1 战斗与渲染边界](references/11-pvf-ai-agent-workbench-3.1.1.md) 和上级 `KNOWLEDGE_POLICY.md`。原教程配方只作索引线索；当前1031字节与可执行消费者核对结果优先，文档“主目标”与本项目内容身份不得混淆。用户要求通用执行链，不能按技能逐一硬编码或手写动作/特效模板来宣称全技能实现。

本知识库由两个项目"炼化"而来：
1. **dnf-pvf-tutorial** 的 1912 篇社区教程（`pvfCourse/`）——玩家社区多年 PVF
   修改经验的文本沉淀（每篇是一个 JSON，`content` 字段为 HTML 正文）；
2. **DNF-Porting (PVFTools)** 源码逆向——PVF/NPK/IMG 二进制格式的字节级知识。

## 回答 PVF 修改问题的工作流

1. **按领域定位 reference**：装备 → `02`；技能 → `03`；怪物/APC/宠物 → `04`；
   物品/商店/掉落/活动 → `05`；任务/地图/时装 → `06`；ACT/ANI/NUT/UI 高级格式 → `07`；
   字节级二进制格式/写解析器 → `08`。基础知识/目录翻译/附魔宝珠 → `01`。
2. **找"修改配方"**：各 reference 都有步骤化配方（要实现 X → 改哪个文件 → 加什么
   标签）。配方结论带（源:课程编号），可用 `09-course-index.md` 查到课程原文件路径，
   需要细节时去 `dnf-pvf-tutorial/pvfCourse/<分类>/<编号_标题>.json` 读原文
   （`content` 字段是 HTML 正文）。
3. **实操提醒**：
   - 修改 .pvf 需要 PVF 编辑器工具（教程默认读者具备 .pvf 编辑环境）；
   - 改完跑不出游戏（"五国"问题）见 `01` 的常见坑；
   - 教程沉淀自社区历史版本，个别标签/数值可能随客户端版本变化——给答案时
     注明来源课程编号，方便用户回溯原文核对。

## 知识地图

| Reference | 领域 | 干货要点 |
|---|---|---|
| `01-pvf-basics.md` | 基础·杂项·模板 | PVF 概念、目录中文翻译、常用路径、附魔宝珠、频道整合、可复制模板 |
| `02-equipment.md` | 装备修改 | 属性代码、触发条件/内容枚举、特效代码、套装/异界/封印、强化增幅 |
| `03-skills.md` | 技能修改 | 技能脚本骨架、路径规律、CD/伤害参数、中英对照、全职业技能解模式 |
| `04-units.md` | 怪物·APC·宠物 | 怪物/APC/宠物路径与标签、属性参数 |
| `05-items-economy.md` | 物品·商店·掉落·活动 | 道具材料、商店商城、爆率、礼包活动 |
| `06-world.md` | 任务·地图·时装 | 任务结构、地图城镇副本、时装外观属性 |
| `07-advanced-act-ani-nut.md` | 高级格式 | ACT/ANI/NUT 结构与编辑工具、UI 界面 |
| `08-binary-format.md` | 二进制格式 | PVF 容器/加密、stringtable 索引、NPK/IMG 结构（源自 PVFTools 逆向） |
| `09-course-index.md` | 课程总索引 | 1912 篇教程标题全表，按题索课定位原文 |

## 高频问题速查

- 装备加属性 / 加触发 / 加特效 → `02-equipment.md`（触发条件枚举源:11589、触发内容源:11590）
- 技能 CD / 伤害 / 新技能 → `03-skills.md`
- 爆率 / 商店价格 → `05-items-economy.md`
- 地图 / 副本进入条件 → `06-world.md`
- "改完跑不出五国" / 换客户端兼容 → `01-pvf-basics.md` 常见坑
- 想知道某标签在文件里的字节排布 → `08-binary-format.md`

## 知识边界（诚实声明）

- 本库提炼自教程文本，侧重"怎么改"；未覆盖的知识（如未收录的私有工具用法）
  不要编造——回退到 09 索引找原文，或明确告知未收录。
- 与两个源项目的工程规范（另见 `pvftools-cpp-standard` / `pvf-tutorial-web-standard`
  两个 skill）互不重复：这里只放"内容知识"。
