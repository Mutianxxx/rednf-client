# 60US 战斗与技能预览：工作记录

## 用户约束

- 当前 `DFO/DFO_fixed_v3.exe` 与 `DFO/Script.pvf` 的逆向证据优先；`D:/dnf-rebuild` 仅作线索，发生冲突时不能覆盖当前版本。
- 保持原客户端、PVF、参考项目只读；独立实现放在当前工作区。暂不修改 `dnf-native-demo`。
- 目标为当前 PVF 注册职业和技能的释放动画、特效、攻击判定、怪物受击/死亡、场景破坏；先恢复战斗调用链，后处理 UI。
- 反编译伪代码不等于原源码；资源同名不等于控制器映射；必须区分已确认、推断与未知。

## 已完成的基础

- `PVF消费链分析.md`：档案解密、索引/CRC/路径冲突及技能 MP 部分调用链。
- `pvf60.py` 与 `pvf60_verify.cpp`：独立校验 99,501 个 payload。
- 仅使用现有展开版本，尚未独立脱壳原始 Themida 文件。

## 本阶段顺序

1. 使用 REA skill，准备可调用的 native 引擎，保留返回 Evidence。
2. 导出当前 CHR/SKL/ANI/ATK/ALS/MOB/OBJ 有序数据与来源，建立覆盖矩阵。
3. 恢复技能控制器的状态入口、ANI/ATK 槽选择、特效生成和帧事件。
4. 恢复碰撞到命中接受、受击/死亡/破坏状态的调用链。
5. 独立预览加载原 PVF/NPK，播放与逐帧检查；未经恢复的技能不假装完整支持。
6. 固化可移植源码、证据、测试与未知项，再开展 UI 链路。

## 工具状态

- REA 6.7.0 / skill v42 / Ghidra 12.1.4 已成功运行并返回当前 EXE 的 native Evidence。
- 用户 Codex MCP 注册未改；工作区 `rea_session.mjs` 自建 MCP stdio client，复用单一 Ghidra 会话。
- 完整工具返回在 `analysis/rea/results/`；`evidence-index.json` 与 `.c` 是索引和文本投影，不能当原源码。
- Ghidra 禁用了 Reference、Decompiler Parameter ID、Decompiler Switch Analysis；部分 case 不在数据库 body 范围，须补原字节和显式跳表。
- `analysis/angr_deps` 的 angr 与 `analysis/deps` 的 capstone/pefile 可用。

## 当前可核对结果

- 6 职业、688 注册技能；PVF 全 99,501 payload CRC 校验，54,531 ANI 已严格 CP949 解析。
- 130 条局部成功请求路径（126 个去重 native-class/skill/state 组合），不等于完整技能。
- 18 条 state10 请求闭合两个主体阶段；21 个已注册职业 variant、42 个阶段资源；2 个未注册候选排除。
- 普通鬼斩部分预览：身体、真实 EQU 的两层武器、两张独立特效、原始 XYZ 框和含边界相交。
- 三段斩3个手动单段片段；裂波斩phase0两视觉与20018无图攻击实体的独立资源轨。技能部分片段合计5，完整控制器仍为0。
- SKL 等级表→runtime skill→ATK bonus→早期伤害倍率消费已闭合；最终伤害仍未完整恢复。
- 怪物状态0/3/4资源优先级和ACT BASE ANI目录消费已定位，预览可以手动选择并独立逐帧检查。
- 命中 opcode0x13、HP绝对值更新链、部分状态5/移除链已定位；ATK安装/重装、实体reset清历史、canonical归属与mode2间隔门已单独固化，完整命中资格仍未执行。
- 自由运动积分与ANI速率算术已有50/46组原指令向量；owner位置阻挡/地形/通知已有74组fixture。未把它们当成完整技能物理。
- state3受击水平参数、持续时间、重力与纵向冲量已有126组原指令核对；预览可用明确stats与dt显示水平推退，未执行完整state3/4。
- Generic PassiveObject销毁后last ACT新实体/粒子提交已定位；木桶/树/草计数、HP回满、原ANI切换与移除请求已接入明确事件预览，PTL内部未执行。
- 裂波斩SKL动态scalar的环境/修正/表消费已有独立合同；不把该scalar当最终伤害。
- Monster死亡回调仍有残余保护。全职业控制器、完整命中/最终伤害、ACT事件、hit pause、倒地/死亡、PTL与UI仍需继续。

统一入口见 `combat_progress/README.md`，覆盖表由 `build_combat_coverage.py` 生成。

## 版本边界

当前注册可玩职业为 Swordman、Fighter、Gunner、Mage、Priest、ATGunner 六类。690 个 SKL 是档案文件数，不能当作 690 个已实现主动技能。1031 参考中的 SQR、SD、十职业注册与 VA 均不能直接移植。
