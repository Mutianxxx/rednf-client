# V3：从当前原生工程迁移的通用接触与受击合同

本节点只修改独立 Godot 工程的 `scripts/combat_world.gd`、`tests/runtime_suite.gd` 和本说明。原生主工程、原始客户端、PVF、知识库及历史候选均只读。没有按角色、技能 ID 或文件名增加执行分支；没有更改运动策略或动画时钟。

## 几何接触：当前 1031 证据

来源是 `dnf-native-demo/reports/combat-native-reverse/collision/README.md` 及该目录保存的机器字节／反汇编，公共参考实现为 `dnf-native-demo/include/dnf/collision.hpp`。

- 当前客户端 EXE SHA256：`246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264`。
- 当前 PVF SHA256：`d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`。
- 1031 helper `1090040` 对有效正尺寸盒使用严格分离条件。X 为 `10902D7 / 1090305`，Y 为 `109033D / 109036C`，Z 为 `10903A4 / 10903D3`；六处均为严格 `ja`。因此面、边和角点相接均算接触。
- `876F47..876F95` 的左右镜像为 `-x-width`，再加实体世界 XYZ。ANI 图片偏移、IMG 裁剪原点和屏幕投影不进入这个盒。

Godot 继续使用 `[minX,minY,minZ,maxX,maxY,maxZ]` 的世界盒表示，但将重叠判断由严格 `< >` 改为包含边界的 `<= >=`。左右朝向、实体平移和正比例缩放共用同一转换。

**重建安全约束单独列明：** 转换入口要求六个源数为有限数，三个尺寸严格大于零，实体 XYZ 有限且 scale 有限并严格大于零。变换后端点必须有限且保持正尺寸。无效盒跳过并给出一次诊断，不修改源数组，也不将负尺寸归一成可攻击盒。`boxes_overlap` 同样验证有限端点和正尺寸。原生报告只证明有限非零输入尺寸的判零和分离路径，没有证明负尺寸、NaN、Infinity 的正确通用语义；这里更严格的入口约束不能写成原版负尺寸处理公式。

盒接触仅是几何端点，不自动证明团队、无敌、霸体、攻击接受、伤害、防御、异常、同步或整个原生调用链已经恢复。原生特殊 Y/Z 分支也仍在报告的未恢复范围。

## ATK 反应：来源语义与宿主消费

先读本地知识规则和 `skills/dfo-pvf/SKILL.md`。本轮具体核读：

| 依据 | 内容与边界 |
|---|---|
| `dnf-部分知识库/pvf-utils-info/Resources/OfficialAnnotationTranslation/attackinfosample.atk.txt:13` | `[damage reaction]` 的枚举含 `[none] [damage] [down] [damage except human]`。样例是字段说明，不等于当前客户端控制器源码。 |
| 同目录 `attackinfosamplebytool.atk.txt:55` | 明确解释 `[none]` 为无任何反应，`[damage]` 为伤害动作，`[down]` 为使其倒地。 |
| `dnf-native-demo/src/combat.cpp:1619` | 已有重建实现分别记录 `knockDown` 与 `noReaction`；后续 `1808..1853` 区分普通受击、浮空、已倒地和起身。该段自身保留恢复时长、力到速度和动作选择的推断说明。 |
| `content/catalog-v2/packs/0/bootstrap.json` | 当前 1031 的第三段普通攻击实际导出 `reaction_type:"[down]"`，源为 `character/swordman/attackinfo/attack3.atk`，原始来源哈希 `a434ce131b1cfa0566b0a6e59704af7b2965a9aaf28fb560ead8b55b1172b6b7`。示例只用于取证，执行器没有技能／角色分支。 |

原 Godot 导出器已经保存 `reaction_type`，但宿主所有非致死命中最终进入普通 hurt／air_hurt，导致字段没有实际消费者。本次补齐：

1. `[none]` 非致死命中仍提交现有 HP 伤害、命中账本、非穿透投射物销毁与 impact 动画；不强制结束目标动作，不重新设置受击动画、等待或传入击退／浮空。目标自身的正常动作推进和既有运动仍继续。致死命中始终进入死亡和 owner 清理。
2. `[down]` 对地面目标选用其来源 down 动画；有正 `launch_z` 时沿用现有 air_hurt、落地 down 的公共生命周期。对已经在空中的目标，`[down]` 保持空中受击入口，等待现有落地逻辑。
3. 地面 down 目标受到不带正浮空量的后续命中，保持现有 down clip 和本地动画进度，延长等待时不缩短原有剩余等待，不切回站立 hurt 或重新播放 down 的飞行等待帧。正浮空量仍可走既有重新浮空路径。

以上是按字段语义补齐通用宿主消费，并复用原生重建工程已经明确记录的 beta 反应策略。`hitstun_ms`、击退／浮空速度、down 恢复、训练伤害仍为演示策略；没有恢复原生完整伤害、质量、保护、硬直或命中暂停公式。`[damage except human]`、特殊目标类别规则和其他未解释枚举没有在本节点补齐，不能算已支持。`[none]` 的测试是合成合同；不能把它写成已完成所有实际来源技能的释放验收。

## 验证与交接

`tests/runtime_suite.gd` 新增／调整：XYZ 三轴面接触、边与角点、严格分离、零／负／非有限／非数值盒、原始数组不变、命名字典、镜像及缩放、实际攻击实例边界接触；以及 `[none]` 普通／致死／非穿透投射物、`[down]` 地面／浮空、倒地追加命中与正浮空再起。

本代理仅编写并静态核读，**尚未运行本节点引擎测试**。由父代理持锁串行运行完整公共运行时和来源程序集成，实际结果以新日志／JSON 收据为准；旧的 154 项通过记录属于 V2，不能当作 V3 已通过。前台画面、声音、攻击手感与原版动态比较仍待用户体验。

本次未将原生的逐技能 timing family 复制进 Godot。10000 ms 等待帧不能全局裁短，枪手抬枪 final-frame gate 与完整五阶段 GunInfo 调度仍须单独数据化后接入；跑攻滑行、空攻移动和其它时钟能力不在此节点修改范围。
