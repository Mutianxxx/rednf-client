# 技能战斗实现交付包 V1

本包可以独立运行并从源码重建**当前鬼剑士系技能战斗演示**，包含移动、太刀普攻、狂暴开关、八项技能链、人物/武器/特效分层、攻击框判定、怪物受击和死亡。它同时交付产生当前结果的原始资源成员、实机调用证据摘录、推导规则、源码与验证工具。

这是当前实现的完整交接，能力范围见 [边界](docs/LIMITS.md)。八项“实测链”仍存在未恢复的控制器；其他角色大类和所有技能的原生条件并未全部恢复。

## 立即运行

在 Windows x64 解压整个目录，双击 `run.cmd`，或运行 `demo/battle_demo.exe`。无需启动原客户端、注入 DLL、安装 Python，资源全部在包内。不要只复制 EXE。

方向键移动，X 普攻，A 崩山击，S 十字斩，D 怒气爆发，G 崩山裂地斩，H 血气爆发，Q 血气之刃，E 浴血之怒，W 血之狂暴。Q 需要先开 W；W 开启后10秒才能关闭。R 重置，M 切换怪物，B 判定框，F1 技能库，Tab 职业分类，Enter 释放，Space 暂停，F5 导出反馈。

建议先靠近第一只怪物按 X/S，查看扣血及受击；按 A 查看人物位移和前方落点；再开 W 测 Q/E/G。每种怪物有三个独立实例。怪物是被动靶子。

## 接手阅读顺序

1. [复现、构建与验收](docs/REPRODUCE.md)：运行、数据再生成、源码构建及检查命令。
2. [完整实现流程](docs/IMPLEMENTATION.md)：输入→施法→动作/附层→资源→渲染→命中→受击/死亡。
3. [数据契约](docs/DATA_CONTRACT.md)：时间单位、锚点、字段含义和实例管理。
4. [逐技能证据与推导索引](docs/SKILLS.md)：逐项链接源文件、创建链和演示结果。
5. [证据核对指南](docs/EVIDENCE_GUIDE.md)与[调用链原报告](evidence/skill-chain-analysis/README.md)：真实采集样本的资格及具体边。
6. [源码导航](docs/CODE_INDEX.md)与[适配接口](docs/PORTING.md)：接入其他工程或扩展职业。

## 包内容

| 目录 | 用途 |
| --- | --- |
| `demo/` | 独立 EXE、运行库、C++17源码、当前内容和包内 NPK 子集 |
| `derivation/raw/` | 当前缓存全部源成员的原始 token5 字节、目录身份与字符串引用 |
| `derivation/seed/` | 已冻结的职业目录/外观/字符串与缓存布局输入；二进制缓存可从 raw 再生成 |
| `derivation/lib/` | 原始成员解析、ANI归一化和 seed 再生成代码 |
| `evidence/skill-chain-analysis/` | 原分析报告、157个源节点、机器码区段、13次已核验创建调用、逐技能观察 |
| `reference/upstream/` | 当前工作区实现原版源码及脚本，便携改动另附 patch |
| `reference/catalog-rules/` | 上游目录关联及 packed PVF 读取器参考源码 |
| `reference/monster-original/` | 用户提供的另一版本怪物文档/契约/参考源码摘录 |
| `vendor/`、`licenses/` | SDL2头/导入库、zlib静态库、JSON/PNG头、运行库和许可 |
| `validation/` | 当前基线及本包重建/迁移验收结果 |
| `tools/`、`manifest.json` | 独立哈希、资源、证据检查工具及文件清单 |

`manifest.json` 记录交付文件 SHA256 和长度。重建/再生成会产生或更新 `demo/build/`、`demo/reports/`、`derivation/seed/cache/resources.bin`；这些是输出。你修改源码或换编译器后，交付原哈希不应继续相等，需另存自己的构建指纹。

交付中保留预编译程序的 `demo/reports/build-manifest.json`，F5反馈可附带该指纹；其他运行报告作为输出，原验收附件放在 `validation/`。

原始 IMG 成员逐字节保留，仅重新封装了较小 NPK 的目录和偏移；`demo/client-assets/asset-manifest.json` 保留原档名、原偏移、目录哈希、成员哈希和包内位置。演示使用源 ANI/IMG 逐帧绘制，验收 PNG 不参与运行。

调用链原报告中的工作区绝对路径和日志范围是**历史来源标识**。相应完整进程日志和整份模块镜像未装入本包；交付内的源成员、代码区段及逐事件观察足以核对已保留证据和再现当前实现，但不能用本包重跑原采集的全量审计。REP 在本轮链中的作用未闭合，不作为已实现解释器交付。

字段解释参考本地 [dnf-pvf-reference SKILL.md](C:/Users/16908/.codex/skills/dnf-pvf-reference/SKILL.md)。跨机器不需要这个技能文件；所有影响本包行为的规则、原值和代码均在本包中明确保存。官方注释样例中的空 ANI 文件没有被用作二进制语义证据。
