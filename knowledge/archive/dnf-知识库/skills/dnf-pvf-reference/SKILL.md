---
name: dnf-pvf-reference
description: 阅读本地 DNF PVF 官方注释样例，核对 MAP/TIL 图层坐标、SKL 技能参数、ACT/ALS 动作和实体配置，并保留编码、版本与来源证据。用于 PVF 逆向和原客户端重制中的格式解释；不提供未经核对的 ANI 二进制或完整战斗公式。
---

# DNF PVF 官方注释参考

用样例的注释解释字段，再与当前客户端 PVF、资源及实际画面交叉核对。这里的“官方”指用户提供的 `pvf官方文档/sample(官方注释)`，尚无外部发行版本证明；样例包含不同年代和工具版本，不能把示例值直接写成游戏常量。

先读项目自己的 `agent.md` / `AGENTS.md`。当前工作区默认是 `D:/dnf-rebuild`；换机器时查找用户提供的文档根，保持原文件只读。

- 查编码、来源、缺失章节、工具用法：[corpus.md](references/corpus.md)。
- 修地图原点、视差、背景重复、遮挡、地砖和 UI 动作：[maps-and-ui.md](references/maps-and-ui.md)。
- 查技能等级端点、CD、输入、ACT 条件/行为、ALS 附层和受击参数：[skills-and-actions.md](references/skills-and-actions.md)。
- 查角色/怪物/物件、迷宫候选、门、城镇区域：[entities-and-dungeons.md](references/entities-and-dungeons.md)。

根据任务只读相关参考。需要精确语义时，用 `scripts/read_source.py --root <样例目录> show <文件> --start N --end M` 读原文，引用原文件及从 1 开始的行号；摘要是中文释义，不取代原文。

保留原字段次序、重复标签、嵌套作用域、原始字节和来源哈希。将结论分清为样例明确说明、当前客户端实例、重建实现；未知规则保持未知。地图数据坐标、镜头、分辨率适配和 UI 坐标分别记录。

旧 `pvf官方文档/sample(官方注释)` 套的 `animation.ani`、`animationsamplebytool.ani`、`actionlibrary/guide.txt` 是空文件；此结论仅指旧目录。用户新增 `dnf-部分知识库/pvf-utils-info/Resources/OfficialAnnotationTranslation/animation.ani.txt` 与 `animationsamplebytool.ani.txt` 非空，应优先参考其文本字段语义，再核当前1031。详见 [新增资料与通用运行时](../dnf-pvf-knowledge/references/10-pvf-utils-info-runtime.md)。新文本也未给 property 25/26 等1031二进制枚举独立证据，不能按文字排列推断；bytool 的攻击盒六字段注释有二维误标，保留冲突并核实。运行日志正常和结构解析通过都不能代替原客户端画面与真实输入验收。
