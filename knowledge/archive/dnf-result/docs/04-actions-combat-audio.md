# 动作、战斗、特效和声音

共同职业数据来自CHR/SKL，动作和判定来自ANI/ATK及关联OBJ/MOB。四个CHR在 [player-classes.json](../canonical/pc/player-classes.json)，712条技能在 [player-skills.json](../canonical/pc/player-skills.json)。这些包含被动、内部项、特殊成长分支，不等于712个可选主动技能。原技能依赖可从 [技能manifest](../imports/gba-workspace/dnf-gba/content/source/skills/manifest.json)追到原路径与未解项。

## 动作和图像

ANI须保留全部帧、原毫秒delay、循环、IMG/帧、位置、旋转、颜色/混合、判定框、事件和声音。状态保持帧（例如10000ms）与普通逐帧动画分开解释；角色方向、身体/武器/时装层序不能凭合成图推断。

IMG保留逻辑尺寸、trim原点、链接帧与像素通道。未经缩放的六类角色/怪物导出样例在 `imports/gba-workspace/gba-research/artifacts/source/`，原IMG样本在 `imports/android/pc-reference/npk-samples/`。完整素材仍从来源NPK按目录提取。

GBA遇到的黑色技能块问题需要区分真实黑色像素、透明、普通alpha与加色。不能全局把黑色设为透明。源颜色整数按小端RGBA解释的依据和GBA近似在 [portability.md](../imports/gba-workspace/dnf-gba/docs/portability.md)；未来渲染器仍需验证原枢轴、混合、插值和裁剪。普通子弹取原IMG，重火器取独立武器层，不能用光点替代原资源并称为完整。

## 技能控制器和战斗规则

技能不能仅用“播放一段ANI并造成一次伤害”表示。每技至少分别建模：资格/学习、输入序列、动作阶段、取消窗口、位移与速度、MP扣除、CD起点、连续输入、多次命中与各目标间隔、持续实体、抓取命中/空放、保护状态、结束/死亡/换场清理。SKL/ANI给出部分参数，控制器仍需恢复。

霸体保持动作但仍受伤；无敌拒绝对应阶段伤害。原ANI的damageType和控制器动态赋予的保护分开记录，不能由一帧保护推广整技。连续技的后续输入也不能被普通CD入口拒绝。怪物MOB的可用动作/条件须单独实现，例如牛头怪不能只保留冲撞。

GBA的84个已接入动作、调整后的范围/攻速/CD和七类AI属于其实现范围。完整PC公式、原生全部技能控制器/觉醒/被动/AI尚未恢复；源路径匹配和图像导出不构成行为证据。

## Android执行参考

当前APK可定位heroProcess、monsterProcess、heroToMonHitCheck、保护/抓取、skill注册和CD等函数。它们是恢复运行时组织的参考，完整物魔伤害、截断、等级差、强化/掉落公式未全部解出，不能用来直接宣布PC公式相同。附加执行段改变部分入口，必须追踪wrapper、跳转目标和回写。见[安卓战斗说明](../imports/android/docs/03-gameplay-logic.md)和[函数索引](../imports/android/inventory/native-function-index.json)。

ACT384个结构解析完成；FRA393个完成、另1个有未消费尾部。它们的动作身份、部件与PC ANI未完整映射。初始显示回调33ms和按调用计数的动作推进，不能简单乘除为“固定30fps全部逻辑”。多帧率端口应分开模拟时钟、内容毫秒和显示插值，并验证定时行为等长。

## 音频

[原audio.xml](../sources/pc/audio.xml)绑定声音ID、路径及属性，ANI提供声音时间事件。NPC接近/对话、角色施放/受击/死亡、怪物动作/受击/死亡分别关联原ID。女格斗家FT声组、枪手GN声组、怪物族别名需要带证据，不以文件名相似代替确认。

GBA13379Hz语音、7500Hz音乐、IMA ADPCM和世界角色选声在其manifest和gba-world-audio.json中；它们是平台采样与调度，不覆盖原OGG或原ANI时间。PC全部NPK/音乐原文件哈希已登记，派生音频未在共同层冒充原始声音。

迁移验收针对每技记录原动作与目标端动作的阶段/时间/命中/声音对照。普通伤害、霸体仍扣血、无敌不扣血、空抓、死亡清理、多段重复输入和武器遮挡均需要实际运行证据。
