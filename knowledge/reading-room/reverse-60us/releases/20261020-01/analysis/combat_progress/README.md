# 60US 战斗逆向与 PVF 预览进展

> 2026-10-20 最新进展：继续以客户端逆向为主、伤害后置。已恢复 `A24950` 的位置/缩放/角度/RGBA插值，独立执行完整原函数与helper的24个结果与预览一致，已接入现有资源时钟。688条技能名称由当前PVF解析，界面增加原图标和筛选；skill32按原表显示“波动爆发”。见 [插值证据](../combat_render/interpolation/README.md)、[名称来源](../combat_catalog/SKILL_NAMES.md)。仍无原游戏逐帧画面对照，原角色时钟和完整技能调度尚未接入。
>
> 导入修复 v4 已按授权安装为 D 盘 `DFO/DFO_fixed_v3.exe`，当前哈希 `bdd14a558658dd0b20def0aa9fa4b355b98855075a05ba6de7f60c4da695495e`。用户已确认正常。原 v3 身份对应备份；预览核对原七节全部字节后复用静态合同，同时保留实际文件哈希。运行时补丁来源已另行记录，保护仍未全部解除。正常运行不代表完整脱壳，用户反馈不代表逐调用动态验证。见 [启动验证记录](../unpack_attempts/001/launcher_test/README.md) 与 [补丁来源](../unpack_attempts/001/patcher-source/README.md)。

当前交付是可继续修改的独立预览源码和可复核的逆向证据。全职业完整战斗仍未恢复，不能据“688 条技能可选”宣称 688 条技能均可执行。`dnf-native-demo` 尚未改动。

## 当前入口

- 本地预览：`http://127.0.0.1:8760`，或双击 [Start.cmd](../../combat-preview/Start.cmd)。
- 使用说明：[combat-preview/README.md](../../combat-preview/README.md)。
- 688 行逐技能矩阵：[coverage.csv](coverage.csv)、[coverage.json](coverage.json)，由 [build_combat_coverage.py](../build_combat_coverage.py) 从已有证据生成。
- REA 完整返回与身份：[rea/README.md](../rea/README.md)、[evidence-index.json](../rea/evidence-index.json)。反编译文本是伪代码，没有声称恢复原始 C++ 源码。

## 证据优先级和版本

所有可执行绑定首先核对 EXE/PVF 的 SHA256。`dnf-rebuild`、原 DFO.exe 和 PVF 保持只读；fixed_v3 已按后续授权备份并替换为导入修复 v4，下列旧静态结果的原件身份对应备份。
`dnf-rebuild` 提供线索，冲突时采用当前 60US 原字节和原 PVF；其他版本的对象偏移、状态枚举、现代 PVF token 和 Squirrel 控制器均不直接套用。

| 原件 | SHA256 |
|---|---|
| `DFO/DFO.exe` | `583928ddc0391396401440bd76391521b138c616b235ed18e615d5ab7333960a` |
| 原 v3：`analysis/unpack_attempts/001/launcher_test/DFO_fixed_v3.original.exe` | `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b` |
| 当前 v4：`DFO/DFO_fixed_v3.exe` | `bdd14a558658dd0b20def0aa9fa4b355b98855075a05ba6de7f60c4da695495e` |
| `DFO/Script.pvf` | `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98` |

本轮以已有的 `DFO_fixed_v3.exe` 展开文件为静态目标，没有独立完成原 EXE 的 Themida 脱壳。死亡 callback 等处仍见保护/解释器跳转；不能把展开文件可反编译等同于全部保护已解除。

## 各层覆盖

| 问题 | 当前结果 | 证据与实际限制 |
|---|---|---|
| PVF 档案消费 | 已建立 | key=0，解密/CRC/路径 hash、完整路径查找；99,501 payload 全 CRC；[基础报告](../PVF消费链分析.md) |
| CHR/SKL/ANI/ATK 原数据 | 已建立目录 | 6 职业、688 注册技能（362 active/326 passive）；690 SKL 含2个未注册样例；保留重复字段、空槽、CP949和字节偏移；[catalog](../combat_catalog/README.md) |
| NPK/IMG 图像 | 当前包可读 | 原像素、链接帧、位置和来源；同路径冲突显式选源；[npk60](../npk60/README.md) |
| 输入命令到请求状态 | 局部闭合 | 130 条局部成功路径、126 个去重 native-class/skill/state 组合；上游学习、输入、变体等条件未全部恢复；[dispatch](../combat_skill_dispatch/README.md) |
| 通用施法 state10 | 阶段动画闭合 | 18 条请求路径；21 个当前注册职业 variant、42 个阶段主体资源；2 个未注册候选排除；时长和职业效果另追；[cast_state](../combat_cast_state/README.md) |
| 普通鬼斩 | 部分执行预览 | skill5→state20→motion1/ATK0；真实武器两层与两张独立特效；技能6未学、基准速度1；[HardAttack](../combat_hardattack/README.md) |
| 三段斩 | 3个手动单段片段 | 各自身体/装备/特效/ATK及等级列；第三段ATK7；运动和接续未自动执行；[tripleslash](../combat_tripleslash/README.md) |
| 波动爆发生成物 | 单个效果资源轨可检查 | skill32/state10phase0→20018→USA LST→OBJ/ANI/ATK；两个actor视觉与无图攻击对象独立；[spawn](../combat_spawned_object/README.md) |
| 波动爆发动态scalar | 明确输入的局部数值模型 | SKL表→550150/550080→54FC40顺序修正→5C77B0；环境、modifier与cap需明确输入；[scalar](../combat_spawned_object/scalar/README.md) |
| 装备附层与判定盒 | 具体装备闭合 | EQU→LAY同动作槽→IMG variation→body延时同步→ANI child list；不能把特效同名或其他武器盒直接泛化；[装备合同](../combat_native_skill_slots/hardattack-equipment-contract.json) |
| 技能等级消费 | 鬼斩早期阶段闭合 | SKL level info→runtime→col0→ATK+10→numeric倍率；250/632安装bonus150/532；非完整最终伤害；[ATK报告](../combat_attackinfo/README.md) |
| XYZ 几何相交 | 当前预览已实现 | dir0镜像、float32平移、含边界AABB、主ANI和武器child盒；资格门控和接受命中分开；[geometry](../combat_native_collision/geometry-contract.json) |
| 接受命中到HP | 静态链部分闭合 | 资格/已命中过滤→opcode0x13(19)→接收回调→计算→绝对HP更新；完整资格与最终伤害仍待执行；[hit](../combat_native_collision/hit-contract.json) |
| 命中记录生命周期 | 局部合同已建立 | ATK安装/重装和reset清两表；canonical归属共享；mode2间隔门；emit前登记；完整周期尚未集成；[history](../combat_hit_lifecycle/README.md) |
| 怪物受击/倒地 | 资源路由可检查 | state3/4 ACT优先；down无资源回退sit；ACT取其目录下BASE ANI；只手动播放，未执行ACT事件/物理/状态退出；[reaction](../combat_native_collision/monster-reaction-contract.json) |
| 受击水平运动 | 明确输入的局部预览 | state3参数到推退/持续时间、重力/冲量算术；126组原指令fixture；自由水平采样已接入，完整state3/4未执行；[reaction motion](../combat_reaction_motion/README.md) |
| 自由运动与动作速率 | 有界模型 | 50组运动/46组ANI算术原指令核对；安装和刷新速率不同、可留残速；[motion](../combat_motion/README.md) |
| 移动位置阻挡 | 有界模型 | Z门、XY物件/地形、通知顺序、临时位置副作用；74组原指令fixture，未集成全场景；[owner](../combat_motion/owner/README.md) |
| 怪物死亡/移除 | 部分静态证据 | state5并非统一death ANI；渐变、运动复位、opcode0x17移除链；slot654残余保护；Monster last action执行仍未闭合；[death](../combat_native_collision/death-lifecycle-contract.json) |
| 场景物件破坏 | 3个明确事件模型可检查 | Generic销毁/last ACT新实体/PTL提交；桶树草独立计数/HP/ANI/请求与实际移除；未模拟PTL内部；[scene](../combat_native_collision/SCENE_PREVIEW_API.md) |
| ANI 图像变换与混合 | 通用渲染局部已接入 | 正常原点、负弧度旋转、输出轴缩放、RGBA→diffuse→MODULATE、连续插值、NONE/LINEARDODGE；角色时钟/其他效果未闭合，尚无原游戏像素对照；[render](../combat_render/interpolation/README.md) |
| 全职业控制器/生成物 | 未完整 | 动作、其他生成物、帧事件、物理、重复命中与实际反应需逐技能闭合 |
| UI绘制 | 待继续 | 当前预览界面为检查工具；原客户端UI消费/布局/绘制尚未移植 |

上述数字属于不同证据层次，不能相加成“已实现技能数”。当前技能部分片段为 **5**（鬼斩1、三段斩手动单段3、波动爆发效果轨1），完整技能控制器仍为 **0**。3个场景事件模型和受击水平采样不计入技能完成数。688条注册技能包括362条active与326条passive。skill32在历史报告中的“裂波斩”标签按当前PVF原名更正为“波动爆发”，绑定ID和路径不变。

## 主调用链

```text
PVF open A570D0 → decrypt/CRC A54E70 → tree A55FA0 → full-path lookup A56000
  → reader B8BA50/B8B5C0 → text 8316F0
  → SKL register 8A0AE0 → parse 8A0DA0 → runtime skill 551AD0

职业 command +188 → qualification/consume +768 → pending request +28C (4ED1D0)
  → opcode5 → 8C1A30 / 8C2162 → virtual+22C 应用状态
  → 职业 state controller → CHR motion/ATK、生成特效/对象

ANI ATTACK/DAMAGE BOX parser A28410 → current-frame cache A27F60
  → primary/child ANI 4AEF80 → world boxes 4E9B10 → AABB A244E0
  → qualification/dedup → 4EABF0 opcode0x13
  → receiver8C39B0 → Monster4F8A30 → Active4B28D0
  → compute4EB780 / 8B8650 → requested absoluteHP4AF140
  → Monster4F58C0 / Active4B4E00 → reaction/death branches
```

这张链展示已识别入口与消费者，不能把中间缺失条件视为已经模拟。protected int/float 是包装存储，文档偏移不等于可直接读写的明文值。

## 下一阶段的具体缺口

1. 连续插值已接入；继续原生帧推进/动作速率和附层绘制，逐帧核对普通鬼斩身体、武器与特效；不继续扩展伤害公式。
2. 扩展波动爆发以外的视觉生成物及其生命周期，逐技能恢复释放顺序和动作事件，随后扩展全职业覆盖。
3. 怪物受击/倒地的完整运动、重入、落地与恢复，以及死亡显示、last action 和实际移除；状态5的剩余保护继续保留为缺口。
4. 扩展场景破坏 PTL 内部和 ACT 视觉执行，恢复原 UI 绘制；与原客户端同装备/同技能等级画面逐帧对照。
5. 伤害/完整命中资格数值链后置；已有静态证据保留，但不将几何接触当作实际接受命中或自动扣血。

## 验证边界

解析、原指令fixture和浏览器交互分别保留。浏览器记录位于 [preview-validation](../preview-validation/)，包括鬼斩、三段斩单段、裂波斩独立时间轨、怪物路由、ACT BASE ANI、职业阶段资源、受击水平推退和桶树草事件检查。50/46/74/126组数值验证在独立合成PE32中使用提取指令和明确fixture；没有启动DFO。浏览器无异常只能证明当前预览可操作；原客户端视觉和战斗行为等效性尚未验证。

REA 使用禁用部分分析器的 Ghidra 配置，有些 switch case 不在 FunctionManager body AddressSet 中。局部反汇编与显式跳表负责补证；不能把数据库 body长度当整个控制器长度。失败的查询同样保留，避免后续重复推断。
