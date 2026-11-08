# 制作流程与工具入口

统一流水线为：只读来源 → 带来源的无损解析 → 平台无关内容模型 → 平台编译器 → 运行时 → 行为验收。每一步输出版本、输入哈希、支持状态和缺失依赖。`imports/` 内工具按原样归档；原路径依赖和历史平台策略保留，不能未经检查就批量重跑。

## 1. 固定来源

PC 全文件清单见 [pc-source-files.jsonl](../catalog/pc-source-files.jsonl)，2,732个文件共5,295,581,144字节，含1,654个NPK；PVF和audio.xml在本包内。Android来源APK及完整分析在 [imports/android](../imports/android/README.md)，样本哈希 `ce97f050e1d9a956cd83d56fa19a9196c6a1619c5294f768291c4bfea83ff3a6`。Lua/GGE 是实现参考，不能覆盖PC参数。

首次处理任一新客户端，记录来源路径、大小、SHA-256、容器版本和语言；索引数字属于该样本。PC格式文档中的通用Big5说明不适用于本简体GBK样本。

## 2. 解析容器与脚本

| 任务 | 已有工具/证据 | 输出注意事项 |
|---|---|---|
| PVF目录、解密、字符串 | [pvf_reader.py](../tools/pvf_reader.py)、[原解析器](../imports/gba-workspace/npk-pvf解析器/README.md) | 当前头56字节；逐32位异或再右旋6位；按条目实际长度裁掉对齐；保留checksum字段，不把未验证的校验算法当作已校验 |
| 脚本标签与翻译 | [consolidate_pc.py](../tools/consolidate_pc.py) | GBK字符串池；type9+10按listId/key解析，保留原整数、字节、偏移；重复标签与结束标签保持顺序 |
| NPK/IMG图像 | [packed.ts](../imports/gba-workspace/dnf-gba/tools/packed.ts)、解析器src/npk与src/img | 保留NPK路径/偏移、IMG逻辑尺寸、trim、链接帧；旧`Neople Image File`头仅在内存适配，不改原文件；type15通道交换在派生解码层 |
| 区域依赖 | [audit_region.ts](../imports/gba-workspace/dnf-gba/tools/audit_region.ts)、extract_world.ts、extract_town_links.ts | 从DGN/TWN根递归MAP/MOB/OBJ/ANI/ATK/TIL；保存未解依赖，不由文件夹名称扩充正式副本 |
| 职业、成长 | [audit_progression.ts](../imports/gba-workspace/dnf-gba/tools/audit_progression.ts)、audit_skill_effects.ts、catalog_player_skills.py | CHR/SKL/QST/EQU原字段；武器候选等级过滤属于当时选取范围；不要重跑旧plan_progression.py覆盖后续稳定ID |
| 门、选关图、召唤 | extract_portals.ts、extract_dungeon_ui.ts、extract_summons.ts | 原门参数对、方向/首领状态、DGN明确选关IMG、MOB召唤依赖 |
| PC声音 | audio.xml、prepare_world_audio.py、prepare_skill_visuals.py | audio.xml和ANI提供原ID/时间；手选音组是GBA映射候选 |
| 安卓容器/动作/代码 | [安卓复现流程](../imports/android/docs/08-reproduction-and-open-questions.md)及scripts/ | BNV、ACT/FRA原字节、Java/native指令和附加段均保留；无完整开发工程 |

当一个文件还不支持解析时，保存原字节和准确偏移/错误。不能用空数组代表它没有内容。`n_quest/dailyrandomquest.lst`、`epicquest.lst`、`trainingquest.lst` 不符合普通ID/路径成对读取器的要求；原字节已保存，记录在任务分析的list_errors中，不影响3222个QST的结构解析。正式注册ID来自可读的 `n_quest/quest.lst`。

## 3. 建立共同模型

对象身份至少为 `(源样本哈希, 内容命名空间, 原路径或原列表ID)`。任务原序、ANI毫秒、原始坐标和IMG尺寸是共同数据。派生模型增加独立字段，不覆盖来源值。参考 [catalog-index.json](../catalog/catalog-index.json)、[统一系统索引](../catalog/unified-systems.json)和[任务列表格式](05-quest-conversion.md)。

角色控制器、AI、伤害/奖励公式必须与资源参数分开。每条规则记录“数据事实/推导/执行证据/未知”，并附原路径或函数地址。以后确认PC行为时增加证据版本，不通过悄悄修改旧快照来清理冲突。

## 4. 编译与运行

PSP或其他高保真端从原图/原毫秒/原判定框编译；GBA的图块、调色板、短CD、输入组合属于单独配置。Android可选择新运行时读取共同模型，或给现APK编译其原格式；第二条路线涉及硬编码容量和native扩展，不能只替换图片。

GBA现有工具把Python/Pillow/NumPy图像编译、ARM链接和mGBA验证分开。对应 [GBA工具链](../imports/gba-workspace/dnf-gba/docs/toolchain.md)、[工具锁](../imports/gba-workspace/dnf-gba/docs/toolchain-lock.json)、tools/build.py、tests/。归档未带完整编译器/模拟器与全部派生图；可在原工作区运行，搬迁后按来源重导出、配置工具位置。

## 5. 验收

先核对原始哈希/依赖/单位，再测逐动作阶段、命中次数/间隔、受击/保护、声音时间、地图所有候选门、NPC交互、奖励和存档。使用真实按键/触控运行；合成预览、注入房间夹具和自然通关分别记录。最终报告绑定实际二进制哈希。GBA测试报告只对其32MiB ROM和既定适配范围有效。

本次资料库的复现命令见 [08-reproduction-validation.md](08-reproduction-validation.md)。
