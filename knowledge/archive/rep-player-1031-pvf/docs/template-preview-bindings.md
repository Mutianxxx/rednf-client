# 十职业通用模板绑定与范围

本节点为用户授权的“先统一套用模板预览，再做专用适配”，不改变完整职业与v0.1 beta验收门槛。新增文件只含 `src/pvf_template_preview.hpp/.cpp` 与本文；职业筛选、通用场景、整合构建与检查由主流程处理。

接口为 `pvf::appendTemplatePreviews(const Archive&, std::vector<PreviewRecipe>&)`。每条新增记录使用 `playback="template-reconstruction"`，并填写 `templateBinding`；与十字斩和三条实际NUT空放流程、CHR动作浏览、注册特效检查分别显示。模板不能记成原生控制器已恢复或技能玩法完成。

## 当前来源与覆盖清单

当前来源 `D:/dnf-rebuild/DNF1031客户端/Script.pvf`，SHA256为 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`。通用模板不依赖这个固定hash才能加载；每次从所选PVF读取源表、资源和数值，scene导出记录实际hash、原字节与偏移。因绑定是通用推断算法而非某个native版本控制器，更新PVF时重新匹配并给出歧义/缺失诊断。

| character ID | 显示职业 | CHR | 源技能表行数 |
| --- | --- | --- | ---: |
| 0 | 鬼剑士 | `character/swordman/swordman.chr` | 175 |
| 1 | 女格斗家 | `character/fighter/fighter.chr` | 163 |
| 2 | 男神枪手 | `character/gunner/gunner.chr` | 167 |
| 3 | 女魔法师 | `character/mage/mage.chr` | 207 |
| 4 | 圣职者 | `character/priest/priest.chr` | 195 |
| 5 | 女神枪手 | `character/gunner/atgunner.chr` | 167 |
| 6 | 暗夜使者 | `character/thief/thief.chr` | 120 |
| 7 | 男格斗家 | `character/fighter/atfighter.chr` | 178 |
| 8 | 男魔法师 | `character/mage/atmage.chr` | 104 |
| 9 | 黑暗武士 | `character/swordman/demonicswordman.chr` | 201 |
| 合计 | 十个非缔造者角色 | 每个技能表原始行各保留一条 | **1677** |

角色/技能身份先从 `character/character.lst` 与 `skill/skilllist.lst` 解析，再读对应CHR、职业技能列表和SKL。重复技能ID或路径仍按源行保留，不去重、不把被动/内部/NotApplicable条目删掉。缔造者仅跳过本次模板运行时条目，Archive中的源记录与原资源完整保留。

每条 `templateBinding` 记录 `characterId/skillId/characterName/chrPath/skillPath/actionPath/idlePath/policy/fallback`。其中actionPath是首个人物phase，所有phase仍可从轨道与 `template:body-phase` marker追踪到CHR tag、原slot、token及ANI。名称包含中文角色名、源skill ID、源SKL名称和绑定策略。中文角色显示名是工具界面标签；技能名由SKL `[name]` 与 `n_string.lst` 对应STR解析，缺失时保留源key或文件名，不伪造中文技能名。

## 人物动作选择

所有人物body与idle只从**该角色CHR自己的motion字段**取值。女枪手使用自身ATAnimation，男格斗家和男魔法师同理；黑暗武士body/ATK来自自身CHR明确声明的DSAnimation/DSAttackInfo，不用普通鬼剑士动作替代它。

动作匹配从SKL文件stem建立ASCII字母/数字小写key，用本CHR的 `[etc motion]` 候选匹配，不跨角色目录搜索动作。

1. `exact-motion`：有完全同key的动作，取原CHR首slot。若有重复同名slot，显示具体数量与首项策略；不把重复项同时播放。该绑定仍是名字推断，不升级为原生调用证据。
2. `phase-motion`：只有动作key以完整技能key开头且剩余为明确phase后缀时才匹配。Ready/Start/Try/Cast/Charge为准备类；数字、Loop/Attack/Shoot/Smash/Hit/Spin/Move为主阶段；End/Finish/Final/After/Return为结束类。每类选原CHR第一个候选，依准备→主阶段→结束顺序串接；loop只一轮。数字或方向/武器变体之间的真实选择仍未知，不把全部候选串成原生技能。
3. `fallback-basic`：没有可用专用动作时，选择本CHR首个可解码 `[attack motion]`，显著标记“临时普攻回退”。保留源技能身份和SKL，动作不代表该技能机制。
4. `passive-basic`：SKL明确 `[type]=[passive]` 时，用本角色普攻作被动条目的动作/装备展示，不创建额外攻击实体、不声称主动释放被动或执行加成。未开放路径 `NotApplicable` 另有显式gap，模板存在不授权正常学习。
5. `source-unavailable`：技能/CHR/动作/idle等必需来源不足时保留记录、元数据和具体异常，清空半成品轨。单个失败不删其余技能；最外层注册表提取失败也显示模板诊断，不阻断原四条专用流程。

匹配拒绝任意子串：例如短词ice不会因为出现在sacrifice中而创建绑定。路径逐段解析 `.`/`..`，不因ANI/ALS相对路径出现 `..` 就误判缺失；越过归档根的引用被拒绝。

## 事件、ATK、实例与清理

每个人物phase从自己的源ANI读取完整帧、时长、flags与框，运行一个源周期。边界用 `sourceFrameTick` / `playbackTickMs` 的60Hz整数tick转换，phase区间为半开 `[birthMs,endMs)`，后一段birth等于前一段end，最终 `releaseMs` 等于自身CHR `[waiting motion]` 的idle出生。idle也有有限end：最后一个独立实体退出后再保留一轮idle源时长，避免循环ANI无限占用实例。

所有source FLAG在对应源帧首次到达时生成 `source:flag` marker，保留ANI路径、frame、flag、原frame字节偏移；没有猜测其原生含义。额外对象/特效触发模板依次选：首个来源FLAG、没有FLAG时首个攻击框帧、两者皆无则人物完成时刻。采用哪条规则写在gap；不以任意“动画进行50%”替代来源节点。

ATK候选来自本CHR `[etc attack info]` 的同key/phase族；普攻回退才使用本CHR `[attack info]`。记录 `template:attack-binding` 及原ATK文件，不把源表下标等同于受保护native选择器，不据模板算伤害、命中去重或MP/CD。找不到ATK仍可展示原ANI框，明确诊断缺失绑定。

额外OBJ仅查 `passiveobject/passiveobject.lst` 已注册记录，并限定角色所属根目录。共享的fighter/gunner/mage目录再按AT前缀区分性别；女魔法师排除Creator与AT资源；黑暗武士只考虑DS后缀，普通鬼剑士排除DS。精确同keyOBJ才产生候选，一组候选只选源注册表首条，歧义数量明确显示。读取选中OBJ的 `[basic motion]`、ATK与直接PTL/ACT/OBJ/NUT引用并保存来源；**未执行的依赖逐项标注**。

没有已恢复的创建控制器时，OBJ局部位置(0,0,0)、静止轨迹与单轮ANI寿命均明示为模板策略，不伪造弹道/跟随/爆炸/落地行为。源OBJ/PTL/ACT/NUT仍完整保留。只有专用适配后才能按真实运动与destroy条件升级。

人物ANI已有ALS时，交给通用scene展开真实附层，不再从目录叠加另一条猜测特效。没有ALS时，只在自己的effect/animation分区选同技能folder或同stem候选，按Normal、Start、稳定路径顺序取一条，写出总候选数与推断身份；不把整目录特效同时播放。effect/object各有独立有限区间，角色返站后仍可继续存在至各自end。

约定marker包括 `template:begin`、`template:body-phase`、`source:flag`、`template:spawn-effect`、`template:destroy-effect`、`template:spawn-object`、`template:destroy-object`、`template:return-idle`、`template:stop-idle`。模板重新播放由scene重建实例，未来专用输入/切图/死亡生命周期仍须另行验收。

## 证据与验证

每条源文档至少包括角色总表、技能总表、对应职业列表、CHR、SKL；另加被消费的STR、ANI/ALS、ATK、选中OBJ及其直接PTL/ACT/OBJ/NUT依赖。报告保存源原字节、归档偏移与hash，保留未来平台复用需要的信息。直接保存依赖不表示已执行它的行为。

最终整合构建与C++20检查通过。全量审计24104/24104通过，十列表1677行全部保留且人物模板可播：exact-motion171、phase-motion107、fallback-basic431、passive-basic968。64个代表场景左右渲染、图像/逻辑框消费者和清理检查通过；1667条请求资源完整，10条部分缺口保留具体诊断，不能把模板可播放记为完整技能。最终来源、hash、数量和已知缺口见 `PROGRESS.md` 与 `validation/latest-template-flows.json`。

## 首轮审计发现：不可视逻辑对象

首轮全量报告保留于 `validation/template-flows-20261019-170808-297-59ea1ca6/template-flow-audit-1792400910424-0/report.json`，1677条均可构建场景且无异常；其中下列3条在左右方向的对象sprite像素检查为0。这个结果来自源ANI本身没有任何IMG帧，不能用随意替换特效掩盖。

| record / 技能 | 实际OBJ与基本ANI | 来源事实与后续视觉依赖 |
| --- | --- | --- |
| 177 / 女格斗家skill3 擒月炎 | `passiveobject/character/fighter/grabexplosion.obj` → `passiveobject/common/animation/fireexplosion.ani` | 1帧400ms、无IMG、有来源框；OBJ `[string data]` 明确列出 `passiveobject/common/particle/fireexplosionparticle1.ptl` 至4。PTL中的 `[object type]=[animation]` 与 `[object]` 指向对应FireExplosionParticle ANI，但源发射调度、粒子数量与native调用尚未执行。 |
| 257 / 女格斗家skill99 猛毒擒月炎 | `passiveobject/character/fighter/grabexplosionex.obj` → `passiveobject/common/animation/darkexplosion.ani` | 同为1帧400ms、无IMG、有来源框；OBJ直接列出DarkExplosionParticle1–4 PTL。保留来源，专用粒子行为待后续适配。 |
| 1206 / 男格斗家skill13 抛沙 | `passiveobject/character/fighter/atthrowsand.obj` → `passiveobject/character/fighter/animation/throwsand.ani` | 4帧，每帧90ms，共360ms；全无IMG，每帧有来源框。人物自己的 `character/fighter/atanimation/throwsand.ani.als` 显式引用ThrowSandAdd00/01，可见沙尘属于该人物ALS，而不要求逻辑OBJ自己有图。 |

模板现在识别“全部帧无drawable image”的逻辑对象，新增 `template:logic-object` marker、完整path/hash/frame/box数诊断与明确gap。仍保留原实例、判定框和有限寿命，不删对象、不改来源、不生成假图像。这类实例应分别验生命周期/来源框；只要存在任一source IMG引用，像素可见性检查仍应要求可见，不因一个全局豁免而跳过。

源PTL存在说明有明确的后续实现入口，但本节点没有执行它的发射频率、粒子随机分布或native绑定。因此两种擒月炎的逻辑helper不计作已实现可见爆炸。此次最小patch C++20语法检查零警告通过；重建和审计最终状态由主流程另记，首轮失败记录保留。

用户可在“通用模板”中筛选十职业，分别选择同名动作、阶段动作、临时普攻回退及含OBJ条目，检查源角色模型、方向、附层、事件、返站和退出。画面、声音、手感及原版动态对照由用户执行。被动/NotApplicable条目是来源覆盖和模板展示，不代表正常成长学习流程、全职业技能或最终beta已完成。
