# 1031 技能特效与怪物响应渲染追踪

状态：已建立十字斩（技能 64 / 状态 35）的静态来源到表现对象链；不是全技能完成，也没有原客户端动态画面验收。

## 结论

从当前 1031 PVF 与 DNF.exe 的现有证据，可以还原一条有实证支撑的技能表现结构：技能脚本按技能身份登记数个效果 ANI；状态机在施放阶段把这些 ANI 作为角色附加动画播放；ANI 的帧数据决定图集、帧、偏移、时长和事件；帧事件推进后续状态或生成独立被动对象；被动对象再通过 OBJ 绑定自身动画、攻击信息、附加效果和销毁条件。命中判定与视觉绘制是相关联但分开的两条链。

代表技能十字斩的脚本、控制器、ANI 事件和 OBJ/PTL 依赖已能互相印证。怪物受击和死亡也有当前 EXE 的动画选择器与特效生成路径证据。但“特定攻击被接受后，哪个逻辑选取哪个 damage index、何时切换受击动作、何时播放硬直/浮空动作”仍未闭合，所以目前能说明完整渲染模型应如何组织，不能宣称已恢复每项技能到每种怪物的完整原生因果链。

当前 `rep-player` 的 GUI 仍是 REP 时间线播放器：它重放录像已经记录的绘制命令，不执行 1031 的 SKL/NUT/ACT 控制器。因此 REP 画面可用于核对序列帧与叠层外观，不能单独证明技能资源为何被加载、是否命中或怪物为何受击。

## 十字斩的文件依据

所有当前客户端证据绑定到 `DNF.exe` SHA-256 `246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264` 和 `Script.pvf` SHA-256 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`。

| 文件 | 它在这条链中的作用 | 已能确认的具体内容 |
|---|---|---|
| `sqr/common.nut` | 技能专用效果动画的登记入口 | `SKILL_GORE_CROSS=64`；`sq_LoadSkillEffect_Swordman` 按顺序登记 `Slash1.ani` 至 `Slash4.ani`。这些不是按文件名猜出的效果列表。 |
| `swordman.chr` 与 DNF.exe 技能控制器 | 把技能状态、人物 ACT/ANI、技能效果 ANI 索引接起来 | 状态 35 设置人物 `etcmotion 25`，附加效果动画索引 0..3；相关 native loader 将动画按 skill ID 保存，并由同一映射查找和附加。 |
| `character/swordman/effect/animation/gorecross/slash*.ani` | 定义人物身上的四路技能斩击视觉 | 四个 slot 分别引用 `gorecross_slash.img`、`gorecross_cross.img`、`gorecross_3cross.img`、`gorecross_3slash_dodge.img`；均没有攻击盒。Slash2 第 10 帧从源时钟 500 ms 开始，帧属性 23 值为 1。 |
| `character/swordman/animation/gorecross.ani` | 人物身体动作和身体帧事件 | 身体 ANI 第 10 帧从 730 ms 开始；其帧时钟和 Slash2 的 500 ms 事件不同。身体 ANI 本身含逐帧几何盒。 |
| `passiveobject/character/swordman/gorecross.obj` | 定义斩击生成的独立被动对象 | `[basic motion]` 指向 `GoreCross1.ani`；`[attack info]` 指向 `GoreCross.atk`；另有 `GoreCross2.ani`、`GoreCross3/4.ani`、`GoreCrossAdd.atk` 和动画结束销毁条件。 |
| `character/swordman/particle/gorecross.ptl` | 描述生成对象的运动参数 | 控制器在后续 phase 加载该 PTL，并以 `(85,0,82)` 为生成偏移。它不是画面贴图，也不替代被动对象 ANI。 |
| `passiveobject/character/swordman/animation/gorecross1.ani` | 被动对象的基础绘制和攻击盒来源 | 它引用 `gorecross_obj_cross_ldodge.img`；第 1、2 帧各有 type-15 攻击盒。它与角色身上的 Slash ANI 是不同实例。 |
| 对应 `.atk` 文件 | 攻击属性及命中反应数据 | 包含攻击类型/伤害相关字段、击退/浮空、命中音效、出血等参数；它不是渲染图像。phase 所用具体 ATK 映射仍未完全恢复。 |
| `.ani` 中引用的 `.img` | 实际像素帧图集 | ANI 帧记录选择 IMG 资源与帧号、局部位置和时长；例如斩击使用 `Character/Swordman/Effect/GoreCross/gorecross_cross.img`。IMG 提供像素，ANI 决定何时及在哪里绘制。 |

最直接的逐段说明和静态指令范围见 `dnf-native-demo/reports/combat-native-reverse/skill-controllers/swordman/README.md`；原始 PVF 导出在该目录下的 `raw/`，保留顺序字段与成员哈希。`gorecross.obj`、ANI 和 PTL 的解码模型位于同目录的 `models/`。这些报告只读用于取证，不是本播放器的运行时依赖。

### 四个角色效果 ANI 的实际帧资源

以下成员 SHA-256 来自本次调查导出的当前 PVF 原始成员；图集、帧数、时长和几何盒来自同一成员的 ANI 结构解析。帧数和时长不能替代逐帧运行时画面检查。

| Skill effect slot | ANI member SHA-256 | IMG 图集 | 帧数 / 时长 | 帧事件与几何 |
|---:|---|---|---|---|
| 0 | `Slash1.ani` `94bf35b7b5743457a7126fc0beb9a6da4c0595f2574fcb27b6e2abd02acd6ef9` | `gorecross_slash.img` | 11 / 1500 ms | 无几何盒；含 ANI property 11(effect 2)，该 property 的最终混合语义不在此处猜定。 |
| 1 | `Slash2.ani` `e607e144abb68fc7a373a8660a99100605936d1b5c9abcd601325805315b4fea` | `gorecross_cross.img` | 12 / 1500 ms | 无几何盒；第 10 帧图集帧 8，500 ms 触发 property 23 值 1。 |
| 2 | `Slash3.ani` `64403f6f05678eff0c26f5d0573fe7fe118877116e044b582981e6601eb00a42` | `gorecross_3cross.img` | 4 / 1080 ms | 无几何盒；没有非 delay 帧事件。 |
| 3 | `Slash4.ani` `c01b894310bcd3ae6f28d98fc6fab5113fc8ffe0d4da8140cb0a6078bd03a214` | `gorecross_3slash_dodge.img` | 6 / 1320 ms | 无几何盒；含 ANI property 11(effect 2)，最终混合语义仍待原生 renderer 动态验证。 |

当前 PVF 的完整 1,179 个 ALS 成员中，没有成员路径或解析后的 token/value 提到 `GoreCross` 或 `Slash1..4.ani`。因此这四个角色效果 ANI 在当前 PVF 中没有找到自动 ALS 子层；这项阴性结果不排除 NUT/状态控制器另外创建的被动对象，而这条被动对象链已由 PTL/OBJ 单独确认。

## 为什么这些文件会进入渲染链

这组关联来自显式消费者，不是从 `GoreCross` 文件名联想出来的：

```text
sqr/common.nut: SKILL_GORE_CROSS = 64
  -> sq_LoadSkillEffect_Swordman 将 Slash1..4.ani 按顺序登记到技能 64
  -> 当前 DNF.exe 的 sq_LoadSkillEffectAni loader 按 skill ID 保存 ANI
  -> 状态 35 按索引 0..3 将它们附加到人物动画层
  -> Slash2.ani 的帧 10 将事件值 1 写入动画实例事件槽
  -> 状态控制器消费事件 1，进入后续 phase
  -> phase 2 显式加载 GoreCross.ptl 并创建被动对象
  -> GoreCross.obj 指定被动对象 ANI、攻击信息、附加动画和销毁条件
```

上述注册和消费由当前 `sqr/common.nut`、状态 35 控制器以及当前 `DNF.exe` 的 loader/lookup/attach 调用共同确认；特效 ANI 的实际像素图由其帧记录引用的 `.img` 决定。`Slash2.ani` 的帧 10 在自身时钟 500 ms 开始，显示图集帧 8 并带事件值 1；但它没有攻击盒。角色特效先展示技能的斩击外观，不能据此认为这条斩击像素本身做了命中。

实际攻击体是另一条资源边：`GoreCross.ptl` 是控制器明确加载的运动配置，随后 native 创建对象 20028，出生偏移为 `(85,0,82)`；对象通过 `GoreCross.obj` 取基础动画 `GoreCross1.ani` 和 `GoreCross.atk`。基础动画帧 1、2 带 type-15 攻击盒，且引用另一张 IMG `gorecross_obj_cross_ldodge.img`。因此可见的角色斩击 ANI 和参与攻击盒检测的被动对象可能同时渲染，但来源、时钟、图集和生命周期分别管理。

`GoreCross.obj` 还登记 `GoreCross2.ani` 作为附加对象效果、`GoreCross3/4.ani` 作为额外动作，并登记 `GoreCrossAdd.atk`。字段能证明这些是对象可用的资源；现有窗口没有闭合它们在全部条件下的触发时机，也没有闭合每一帧的混合、遮挡和最终屏幕像素。`GoreCross.atk` 则提供攻击属性和命中反应参数，例如击退/浮空、命中音效及出血配置，不是特效图片。

所以“为什么引用某个特效文件”应按来源链回答：`common.nut` 说明哪个技能注册哪个角色附加 ANI；技能控制器和 native API 说明何时取出并附加该 ANI，或何时加载 PTL/生成对象；OBJ/ACT 说明对象或动作包含哪些 ANI/ATK；ANI 帧记录说明实际用哪个 IMG 帧、位置、时长、帧事件及几何盒。单独看到 IMG 或文件路径只能证明资源存在，不能证明它被该技能消费。

## 通用 ANI/ALS 播放合同与播放器差距

通用合同取自 `dnf-native-demo/reports/combat-native-reverse/resource-render/README.md` 和 `animation-events/README.md`，来源绑定到上文同一 DNF.exe/PVF 哈希；这些是只读静态分析，不是本播放器已实现的功能：

- 加载 ANI 成功后，当前 EXE 会从 ANI 完整路径自动查找 `.ani.als` / `.als` 并解析。ANI 源数据应保持只读；每次播放有独立实例状态，不能让两个对象共用当前帧、速率、事件和子层列表。
- native 速率单位为百分比，帧延时为 `trunc(rawFrameDelay * 100 / ratePercent)`；`100` 是正常播放速率。运行中变速要按旧/新倍率重算本地时间，不能只改总时长或帧号。
- `addLayerAnimation` 按 layer 升序插入，子 ANI 关联 parent 并继承速率。定位附层时按时间映射到子 ANI 自己的帧延时，不能复制父 ANI 的帧号。延迟附层的双重 reset 使净出生时钟仍未闭合。
- ALS 命令可声明、添加/移除附层，或创建普通、随机、跟随父对象的 draw-only 对象。事件越过多帧时按经过帧的顺序派发，并按命令身份记录 fired；循环只重置部分 draw-only 命令，不能一概重播全部事件。
- 当前 EXE 可解析的 graphic effect 枚举为 NONE、DODGE、LINEARDODGE、DARK、XOR、MONOCHROME；具体 DODGE / LINEARDODGE 的 Direct3D 混合公式未恢复。文本 `SPACEDISTORT` 有降级写 effect2 的路径，binary effect6 在本 EXE 的相关 parser 中被拒绝。预览应保留来源值并给未实现分支诊断，不能把 86JP REP 的 shader 或 SDL ADD 近似当作 1031 原生公式。

这些合同能描述技能特效播放器应具有的实例、时钟、层和事件模型，但不证明十字斩或其他技能会使用每一种 ALS 命令，也不能代替具体技能控制器的 phase 调度。

独立项目当前只有 REP 时间线播放器、NPK IMG 解码器和 PVF ScriptFile/token5 读取器：`src/resources.cpp` 的 `Assets` 从 NPK/NpkIndex 取 IMG；`src/pvf.cpp` 能从 PVF 读取原始成员，但没有 ANI/ALS parser，也没有将 PVF 的 IMG 成员接到 `Assets` 的 provider。故现有 REP GUI 重放的是录像已记录的 draw 命令，不会执行这些 ANI/ALS 合同。技能 demo 需要新增 PVF member-backed IMG provider、ANI/ALS 源数据 parser 和独立动画实例/事件调度，再复用可验证的图像解码与 GPU 绘制路径；目前并未实现这部分。

## 应采用的表现流程

1. **建立资源身份。** 从当前 PVF 解析职业/技能身份、CHR 的动作与攻击信息序号、SQR/NUT 逻辑及 OBJ/ACT 依赖。路径存在只表示候选依赖；必须确认某技能控制器真的通过加载 API 登记并消费它。
2. **进入技能动作。** 资格检查通过后提交技能状态，选取身体 ACT/ANI；同一技能可将若干 skill-effect ANI 附加在角色上。每个 ANI 播放实例需要自己的帧、局部时钟、速率、方向、偏移和事件状态，不能只换一张贴图，也不能把子动画帧号强制同步为身体帧号。
3. **绘制每个动画实例。** 按实例时钟选当前 ANI 帧；用该帧的 IMG 路径/帧号、原点偏移、翻转、缩放、层、混合和透明度生成图元。装备/身体、技能附加 ANI、ALS 子 ANI 和被动对象分别保留身份和层序。具体技能混合公式、特定装备层序和渲染器所有边界仍须继续查证。
4. **按模拟帧派发事件。** ANI/ALS 的帧事件按跨过的源帧顺序派发且每个一次性事件有 fired 身份；渲染帧率不能决定技能事件是否触发。事件可添加/移除子 ANI、生成 draw-only 对象或推动技能 phase。ALS 的通用加载和事件合同见 `dnf-native-demo/reports/combat-native-reverse/resource-render/README.md`；合同中的通用能力不等于每个技能都实际调用。
5. **创建独立攻击实体。** 如果控制器创建 passive object，先用 OBJ 确定基础动画、附加动画、攻击信息和生命周期，再用 PTL/对象控制逻辑推进其位置；按其当前 ANI/帧绘制像素并取当前帧攻击盒。对象存在不等于它已命中。
6. **独立处理碰撞与伤害。** 当前帧攻击 ANI 的 type-15 盒，与目标当前帧 ANI 的 type-14 受击盒做方向和 XYZ 变换后测试。通过接触几何后，还必须经过资格、目标去重/间隔、攻击接受、ATK/防御/异常和 HP 写入。可见特效和命中事件不能互相代替。
7. **在目标实体上播放反应。** 命中被接受后，目标进入相应状态并更换/附加动作表现；受击、倒地、翻转、死亡分别走其数据入口，死亡效果还可能创建独立 ANI/PTL 对象并按来源条件清理。

步骤 1–5 在十字斩代表链上有较强的当前 PVF/EXE 静态证据；步骤 6 只闭合当前帧几何接触端点及部分接触资格/目标登记，接触到完整伤害仍有缺口；步骤 7 已找到动画 getter 和死亡特效生成局部路径，选择器上游仍未知。

## 怪物受击表现的已知边界

当前 EXE 的 `818BF0`（虚方法槽 `+480`）可取得两个 damage ANI：优先读实体 `+2C34+index*4`；缺省时从 ACT `+2CF0+index*4` 取得 ACT，再取 `[ACT+24]`。`818C20`（槽 `+484`）取得 down ANI：实体 `+2C3C` 或 ACT `+2CF8`。这说明受击/倒地画面由动作资源消费者选择，不是绘制“红圈”或仅改变血量。

死亡视觉有另一条独立链：`899C00` 所在流程进入 `E3C420` 特效对象；`E3B100` 有闪光、碎片和烟雾分支，`E3B892` 形成 `m%04d.img` 资源名，`E3C4AD` 引用 `MonsterDieSmoke.ptl`，且 EXE 登记了 `[die effect]`。这不能推出所有怪物死亡都碎裂；单个 MOB 的 `[last action]`、死亡 ACT/ANI 和对象清理仍需按具体怪物核查。

依据与缺口见 `dnf-native-demo/reports/combat-native-reverse/entry-audit.md` 第 5 节、`collision/README.md` 和 `hit-acceptance/README.md`。当前已知缺口包括：攻击接受到伤害/HP 的完整中间逻辑、受击 index 生产者、硬直时长、某个 MOB 选用哪个 damage ACT、受击暂停，以及死亡视觉选择和碎片速度公式。

### Goblin 的当前 PVF 资源映射样本

`monster/goblin/goblin.mob`（原始成员 SHA-256 `a90a25f8ab3d6fb132d0ce29b5b378fbc4c9800ad8b2b87a6c91405706822d89`，917 bytes）给出互不相同的 `[damage motion 1] = Animation_Goblin2/Damage1.ani`、`[damage motion 2] = Animation_Goblin2/Damage2.ani`、`[down motion] = Animation_Goblin2/Down.ani` 和 `[sit motion] = Animation_Goblin2/Sit.ani`。当前 DNF.exe 的 `818BF0` 消费 damage ANI 索引 0/1，`818C20` 消费 down ANI；故可确认 MOB 确实提供不同受击/倒地资源，且有原生 getter 可消费这两类数据。`sit motion` 的状态消费者尚未在本窗口确认。

这仍不能回答一次十字斩命中最终选择 Damage1 还是 Damage2：索引生产者、命中类别到索引的映射、何时切动作和硬直时间仍未知。Goblin MOB 没有 `[last action]` 字段；它的 `[die effect]` 是 `0,1,0`，但当前证据还不能把这三个值逐项映射到 EXE 的闪光/碎片/烟雾分支。因此受击 ANI、倒地 ANI、独立死亡动作和通用死亡特效必须分开追踪。

## 证据等级与后续

- `confirmed-static`：PVF 原始成员/顺序字段，脚本中的明确资源路径，ANI 帧数据，EXE 注册/API/调用者/分支的逐字节核对。
- `inferred`：依据 ACT/MOB/OBJ 结构和相邻消费者推得的时序、锚点或动作意图；必须同时保留替代解释。
- `unknown`：命中接受后的伤害和怪物状态选择、完整渲染层序/混合参数、所有职业/技能的 NUT 执行路径，以及屏幕输出和原版动态是否一致。
- `user-test-only`：预览画面、声音、手感和原版实时对照；静态结构审计不能替代。

下一步按代表技能继续做依赖图：为每一项记录 PVF 成员路径/hash、实际加载 API、注册索引、帧事件、OBJ/PTL/ATK、怪物 damage/down/death 消费者和清理条件；随后制作当前 PVF 驱动的隔离预览。未闭合命中因果之前，预览只声称重放来源动作和特效，不声称复现攻击判定或伤害。
