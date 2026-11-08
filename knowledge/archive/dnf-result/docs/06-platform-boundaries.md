# 平台策略、输入、界面和持久化

| 领域 | PC共同内容基准 | GBA现有策略 | 当前Android样本 |
|---|---|---|---|
| 显示 | 原IMG逻辑尺寸、trim、层序、颜色与混合 | 240×160、1/3地图、16色/图块/OBJ预算 | 原PAK/FRA/ACT、软件画布/GLES2；没有完整PC资源映射 |
| 输入/UI | 原动作/技能输入语义和原UI图像依据；完整PC交互仍需核实 | 六快捷槽、Z组合键、下+跳后跳、可交换Z/跳；START菜单、SELECT地图 | 触控、多指、浮层与附加编辑器 |
| 任务成长 | PC原条件/材料/奖励与正式职业资格 | 免材料、主要刷图升级、转职后开放已实现技能 | 固定任务槽、独立本地条件类型；附加可交付标记 |
| 战斗 | PC SKL/ANI/ATK参数，控制器另恢复 | 调整CD/攻速/范围、有限动作与AI、保护配方 | 鬼剑士体系、native控制器及附加段；全公式未恢复 |
| 声音 | audio.xml/ANI事件、原OGG | 13379Hz语音、7500Hz音乐、IMA ADPCM | Java/native音频桥 |
| 场景 | 原TWN/DGN/MAP/TIL/OBJ与动态事件 | 共享图块/流式加载、部分静态合成、门省略外围装饰 | ZON/FIE/DS/FOB/BAC；部分未解 |
| 存档 | 稳定内容身份；PVF不能定义PC服务器持久化 | 20角色槽、旧4槽迁移、CRC/双副本/断电恢复 | Hero/Quest/Slot、本地设备标识、仓库与兼容迁移路径 |
| 容量 | 平台无关逻辑与原素材 | 当前单32MiB，Matrix为实验 | APK/BNV与平台存储 |

GBA的政策原件位于 `imports/gba-workspace/dnf-gba/content/gba-*.json`；生成world.json、runtime-model.json带GBA坐标，不能作为PSP的世界源数据。`player-skill-catalog.json`包含GBA接入状态；共同技能目录已单独导出原字段以免继承平台标记。

Android附加功能、动作、时钟、存储和native桥详见[原结果入口](../imports/android/README.md)。其中官方来源、实际运行和PC等价性各有边界。它是本次静态分析的样本，不能把辅助覆盖功能带入PC原规则。

## 多端存档建议

使用独立schema/version、角色UUID、原职业/成长身份、原物品ID、任务状态与计数、区域/任务准入、装备实例和设置。将内容包哈希与内容ID记录在存档头，通过显式迁移表处理版本差异，不用某平台当前数组位置当作永久ID。

GBA SRAM与Android本地文件的现有事务方案可以参考，但不能直接互读。跨端转换器需逐字段检查映射、范围、任务计数和物品实例，不支持的内容明确列出并保留来源存档。写盘用原子替换/双副本和损坏回退，实际测试中断、截断、旧版和跨区域恢复。依据分别见 [GBA存档](../imports/gba-workspace/dnf-gba/docs/save-format.md)、[安卓存档](../imports/android/docs/07-save-and-extension-bridge.md)。

## GBA容量结论

当前发布范围统一装入32MiB，实际使用33,538,916字节、剩余15,516字节，对应ROM SHA-256 `d9af5d14ffc8b632d1f4dfdbf77ab47a359622a8bdc7d39515f6bb41aec879fa`。压缩/翻转/共享图块与音频策略是可参考的工程方案。

普通64MiB拼接失败；mGBA Matrix A→B→A映射探针通过，提供8KiB映射孔径，完整游戏未改为此布局，实体烧录卡未验证。当前结论是“有特定映射实验”，不能称“完整64MiB卡带已兼容”。屏幕固定240×160。见[原容量报告说明](../imports/gba-workspace/dnf-gba/docs/rom-capacity.md)。
