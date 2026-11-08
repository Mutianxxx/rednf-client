# 本项目知识库使用规则

## 2026-10-21 新资料优先级与通用实现要求

用户新增 `dnf-部分知识库/pvf-utils-info/`，指定本次技能、人物、动画、判定、UI 复核优先参考其 `Resources/AgentKnowledge/`、`Resources/OfficialAnnotationTranslation/` 和 `Options/PvfComments/`。项目参考入口见 [新增资料与通用运行时](dnf-pvf-knowledge/references/10-pvf-utils-info-runtime.md)。原始资料、工具 EXE/DLL、客户端和 PVF 保持只读，不执行知识包附带程序。

此包的“默认可用”“100%高覆盖”“已完成静态封存”是文档自身的分类和静态研究口径，不代表本项目运行验收。文档自己的“主目标”含 `qf_*` 定制脚本，尚不能自动等同于本项目 SHA256 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d` 的 1031 PVF。具体数字、常量、注册入口、资源路径、native caller 必须回到当前源字节和运行消费者核对；文档标记的“需验证”和已知冲突保留。

旧官方样例目录的 `animation.ani` 等为空；**新增包的翻译 `animation.ani.txt` 与 `animationsamplebytool.ani.txt` 非空**。不能再把旧空样例结论推广到新增包。新文本确认 IMAGE RATE 1.0 原大小、CLIP 以动画基准点为坐标、RGBA/位置/缩放/角度/CLIP 可插值、ALS 按父动画帧 add/remove。文本没有提供 1031 二进制 property 25/26 的原生枚举证明；不可仅按段落顺序定性。bytool 的六列攻击盒注释有二维误标，不能覆盖本项目经当前数据核对的 XYZ 起点与三轴尺寸。

用户要求执行通用逻辑，禁止靠逐技能专用代码/手写模板补丁扩展。以通用 animation/layer/entity/AttackInfo/hit/reaction、NUT/ACT宿主 API 为实现单位；职业入口/动作槽允许按职业数据适配。缺失原生 caller 直接列为缺口，不把 SKL preload、资源名相似、ANI 有攻击框或一次演示通过冒充全技能恢复。

本次 v2 全库字节/文本结构复核与实际语义阅读分别记录于 `dnf-godot-skill-demo/reports/knowledge-v2/`；结论见 `dnf-godot-skill-demo/docs/KNOWLEDGE-V2.md`。主原生工程仍按当前暂停要求保持只读。

用户于2026-10-20要求先遍历新增知识库，再核对主工程技能与UI，并允许在本项目加载其中的skill。项目入口为根目录AGENTS.md；本轮直接读取了两个SKILL.md及相关references。下列副本供后续会话按任务读取，不要求安装到系统目录。

| 项目入口 | 原始来源 | 内容 |
|---|---|---|
| [dnf-pvf-knowledge](dnf-pvf-knowledge/SKILL.md) | `dnf-部分知识库/dnf-pvf-knowledge/` | 两份摘要与课程索引以外还包括装备、地图、经济和二进制格式等9篇reference |
| [dfo-pvf](dfo-pvf/SKILL.md) | `dnf-部分知识库/dfo-pvf-skill-main/skills/dfo-pvf/` | ANI/ALS/ATK/SKL/MOB的5份格式说明 |
| [dnf-pvf-reference](dnf-pvf-reference/SKILL.md) | 项目既有官方注释样例skill | 以原文行号、编码、原字节和来源身份交叉核对 |

新加入的两份skill与全部reference按原字节复制，未执行知识库中的代码。原文提到的`dnf-pvf-tutorial/pvfCourse`在本项目实际位于`dnf-部分知识库/dnf-pvf-tutorial-master/pvfCourse`；另有重复教程位于`DNF-PVF-file-Reference-main/参考资料/DAF学院PVF教程文本`。以审计中的SHA256和精确路径定位，不能只靠课程总数或编号推断版本。

当前1031 PVF SHA256为`d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`。新资料的教程、后期NUT改版代码、格式模板和推测解释均作为参考线索，需要与这个来源及实际运行消费者核对。具体编码取自当前文件，保留源字节和token；不能按模板统一转成UTF-8、改写路径大小写、替换职业ID或状态编号。

已发现的冲突包括：把`[skill class]`误当职业身份；把转职分支误当觉醒阶段；将工具导出的文本格式当所有原始PVF文件格式；将`pushState`第五参误释为优先级；将ALS的帧号误作毫秒；将后期UI NUT目录中的伤害改写逻辑当纯UI表现。详细路径、适用版本及核对结果见[知识库审计](../dnf-native-demo/reports/knowledge-base-audit/README.md)。不能据此批量改游戏实现。

全库哈希/全文抽取是机器覆盖，按领域通读、具体语义核对和原版动态验收分别记录。图片、二进制、外链及未恢复调用保持具体边界；不把索引数量或课程作者的阅读声明当成本项目已验证数量。

## 2026-11-02 Workbench 3.1.1 战斗/渲染补充

用户提供 `dnf-部分知识库/PVF-Ai-Agent-Workbench-3.1.1/`，并随后解压其中的 DAF 与 GiteeNut 两个 ZIP。全量物理清单、文本抽取、ZIP 对照与当前 1031/Godot 差距见 `dnf-godot-skill-demo/reports/workbench-311-review/`；语义分析见 `dnf-godot-skill-demo/docs/WORKBENCH-311-REVIEW.md` 和新参考 [Workbench 3.1.1 通用战斗与渲染边界](dnf-pvf-knowledge/references/11-pvf-ai-agent-workbench-3.1.1.md)。

新增资料可补充通用 NUT 回调、state/PO 数据通道、AttackInfo/命中账本、视觉对象/粒子、怪物与破坏物跨层审计、UI ACT 能力分类。它没有补齐本项目 1031 的所有技能 native caller 或完整伤害/受击公式；外置知识库含社区示例和跨版本结论，必须按新参考记录的边界与当前源、实际消费者核对。新增解压文件和对应 ZIP 成员 1,998 项哈希一致；原资料只读，附带程序未执行。
