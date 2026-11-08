# 当前 V3.1 按需加载修复

运行 `Play-Latest.cmd`。修复了职业ID小数参数与资源锁误提示，详见 [当前进度](CURRENT_TASK.md) 和 [修复交付](docs/DELIVERY-V31.md)。

# Godot 1031 技能与动作试验 V3

本轮已从主工程补入通用判定、事件和装备绑定能力，并按最新要求将“调用链未闭合”改为提示式预览。
已解析的程序、精确CHR动作和独立引用资源可以继续展示。**完整源程序仍为2条，其他预览不代表技能完整实现。**

- 冻结体验：`D:\dnf-rebuild\dnf-godot-skill-demo\checkpoints\20261021T133304Z-godot-native-contracts-v3\runtime\Play.cmd`
- 快捷入口：`Play-Latest.cmd`
- 当前源码：`Play-Catalog-V2.cmd`，无需C++编译
- 当前编译：`Play-Compiled-V3.cmd`
- 源码／产物／资料备份：`D:\dnf-rebuild\dnf-godot-skill-demo\checkpoints\20261021T133304Z-godot-native-contracts-v3`

F3选角色技能，点“加载并展示选中技能调用链”；Z再次请求。F2判定框，F4源UI，R重置，方向键移动，空格跳跃。
右下旗标策略用于比较，下次施放生效。男法“魔法冰球”可测试未闭合提示与当前链预览；
男法“魔法旋风”、圣职“复仇之刺”是两条实际完整源程序。

未恢复caller的动作／引用资源分别展示并明确标注，不会猜测未知控制块或伪造出生位置和攻击资格。
引用资源轮播使用试验查看原点，不等于原技能出生点；原源程序与独立对象保持各自坐标。
未缓存内容通过只读1031客户端按需导出，需要本机Python和原客户端。
首次冻结启动解压资源到自己的D盘cache，后续运行不依赖live源码变化。

本轮来源24,492项、Python 28项、源码引擎361项、编译34项及冻结35项均通过。
冻结目录内按需导出6项通过，未闭合提示预览可在冻结包中继续生成。
用户视觉、声音、手感与原版动态比较待确认；完整技能／普通攻击控制器／公式／PO及UI业务仍有缺口。
详细进度、验证边界、恢复步骤见 [CURRENT_TASK.md](CURRENT_TASK.md)；
本轮改动见 [DELIVERY-V3.md](docs/DELIVERY-V3.md)，原知识结论见 [KNOWLEDGE-V2.md](docs/KNOWLEDGE-V2.md)。
主原生工程保持暂停只读，历史V2冻结候选保留。
