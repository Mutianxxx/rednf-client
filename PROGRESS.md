# 技能时间轴 / 脱手实体 / 坐标原点 / 主线接入（2026-11-10 第四轮）

节点 `skill-timeline-persistent-20261110`。用户反馈四件事：**特效没有源时间轴**（所有层同时播）、
**脱手技能缺失**（念气环绕的球、千莲怒放的花、极·鬼剑术悬空的剑）、**特效位置/原点不对**、
以及**成果没有落到可游玩主游戏**。

## 1. 源时间轴：`.als` 旁挂脚本

父动画的 `.als` 才是客户端真正的层时间轴，语法在 `effect_plan.cpp` 里早已实现，只是预览器没用：

```
[use animation]  "Animation/xxx.ani"   instanceName
[add]      <帧号> <层号> instanceName
[remove]   <帧号> <层号> instanceName
[create draw only object] <帧号> instanceName <x> <y> <z>    // 唯一带源偏移的写法
```

`SkillVisualMapping::effectLayers` 现在为每一层记录 `timed / alsFrame / alsLayer / instance /
offsetX/Y/Z`：有旁挂脚本的层由源帧出生（`evidence = "ALS [add] frame N"`），没有旁挂脚本的层按
文件名词里的释放阶段序（`effectStageOrder`）排序，再按动作链段数分摊，`evidence` 写
「no ALS sidecar」。**旁观事实**：1031 只给男法、男格斗、圣职等职业配了 `.als`，女格斗与剑士
的 `character/fighter/animation/nenflower.ani`、`character/swordman/animation/hundredswordready.ani`
都没有旁挂脚本，所以那一半只能是重建。

同时修掉一个真 bug：`PreviewLayer::visible()` 原先只看自身时钟，层在出生前就被绘制（时钟停在 0），
48 层的剑术家族因此变成一整片白光。现在 `visible(actionMs)` 同时判断出生与存活。

## 2. 脱手技能：`persistents`

`passiveobject/character/<job>/<skill>.obj` 的动作表里，**长循环**（60 秒）与**单帧地面贴花**就是
「施放后留在场上」的实体信号：

| 技能 | 实体来源 | 判定 |
| --- | --- | --- |
| 念气环绕 `spiralnen` | `SpiralNen.ani`（200ms 循环） | 名字含 spiralnen；球数按职业 2（女）/4（男） |
| 千莲怒放 `nenflower` | `NenFlower/Ground.ani`（1 帧） | 单帧 + 名字含 ground，地面放置物 |
| 极·鬼剑术 `hundredsword` | `HundredSword/swordair1.ani`（60050ms 循环） | 循环长度 > 动作时长，悬空剑 |

球心半径 62px、转速 72°/s、垂直压扁 0.32、悬剑间距 56px、高度 -160px 全部**不在任何 PVF 文件里**，
属于重建参数，`PersistentPlan::evidence` 逐条写明；数量来自资源结构（`SpiralNenTail1..4` 的尾巴数、
`HundredSwordMoveReady1..5` 的 move 段数）。`_ds`/`at` 变体按职业去重（`spiralnen` 与 `atspiralnen`
只取一个），避免同一把剑画两遍。

千莲怒放的动作只有 700ms，放置物需要更长时间才成立：存在驻留实体时动作窗口扩到 2600ms，
层出生时刻按比例缩放，身体播完后停在末帧。

## 3. 坐标原点

- 帧级偏移本来就由 `Renderer::animation(pose.x, pose.y)` 应用，问题不在这里。
- 真正错的是**层锚点**：特效层全部画在角色脚底原点，而 `passiveobject` 的动画锚点是对象生成点
  （`.obj` 的 `[floating height]` 表示悬浮格数）。驻留实体改为按类型给锚点（球 -78px、悬剑 -160px、
  地面 0），并且**不再重复当作普通层播放**（此前 `spiralnen.ani` 既当层又当实体，闪一下）。
- ALS 的 `[create draw only object]` 带 XYZ，已作为 `offsetX/Y/Z` 原样传递；普通 `[add]` 没有偏移，
  保持 0，不做假。

## 4. 主线接入（native）

`src/tools/skill_preview_mapping.cpp` 编入 `dnf_core`，`World` 新增 `spawnSkillVisuals()`：
技能起手时用同一张表生成 `Effect` 层（`born` 按 `birthRatio` 偏移动作时长），驻留实体生成
`Effect` 并新增 `orbitRadius / orbitSpeedDeg / orbitPhaseDeg / orbitCenterY` 四个字段，由 `update()`
每帧按角度重算位置。手工登记视觉的技能（`Skill::manualVisuals`）跳过，避免重叠。

## 结果

- 映射评级不变：A 264 / B 287 / C 170 / D 1013（1734 行），预览器回归 37/37。
- 点名技能：念气环绕 2 球（女）/ 4 球（男）绕身旋转；千莲怒放地面花 + 15 层阶段特效；
  极·鬼剑术 5 把悬剑 + 48 层（ready → swordair → slash → light → tail → finish）按阶段出生。
- 截图核验：`checkpoints/analysis/fx-nen-orbit3.png`、`fx-nenflower.png`、`fx-hundredsword*.png`。

## 已知边界

- 女格斗 / 剑士没有 `.als` 与 `sqr` 脚本（PVF 里只有 atmage/creatormage/priest 三个职业有），
  阶段时序与球体运动全是重建；exe 里那段共享施法 state 的 `Sprintf(加密段模板)` 仍未恢复。
- 千莲怒放「再次点击引爆、念气技能催熟」是游戏内交互，预览器只呈现「放置 → 引爆」两段；
  主游戏需要技能状态机，本轮没有做。
- 主游戏端到端截图核验未完成（`dnf_native --smoke` 可启动但本环境未产出逐技能画面），
  接入正确性目前由编译 + `dnf_tests` + 映射表一致性支撑。
- `dnf_tests` 的 `Airborne reaction preserves current recovery route without hurt RNG` 为**既有失败**：
  用 `git stash` 回到本轮改动前重编仍失败，与本轮无关。

# 全职业技能特效补全（2026-11-10 第三轮）

节点 `skill-effect-families-20261110`。用户反馈：格斗家「念气罩 / 雷龙出海 / 千莲怒放」仍丢特效，
男魔法师动作很全但**特效几乎全缺**（冰魄剑、魔法炮、破冰飞刃等），要求全职业复查并补全。

**根因：特效按「技能目录」组织，原实现只按「文件名前缀」找**

1031 把技能特效放在以技能命名的目录里，目录内的文件名是描述性的、**不含技能名**：

```
character/fighter/effect/animation/atnenflower/start_line_dodge/start_line_06_dodge.ani
character/mage/effect/animation/aticesword/01_light_dodge.ani
passiveobject/character/mage/animation/atmagiccannon/00_magiccannon_fire_dodge.ani
```

原实现要求「文件名以技能 stem 开头」，因此这些目录一个都进不来——男法师 38 个主动技能只有 2 个
有特效，格斗家高等级技能也大面积空白。目录匹配同时解决了男法、格斗、剑士和枪手的一批缺口。

**修复（`skill_preview_mapping.cpp/.hpp`）**

1. `JobIndex.effectFamilies`：把 `character/<job>/effect/animation/` 与
   `passiveobject/<job>/animation/` 下的 `.ani` 按**第一级目录**分组（根目录下的文件自成一族）。
2. 技能 → 族匹配：`stem` / `at+stem`（男法、男格斗）/ `stem+阶段词`；EX 技能回退到去掉 `ex` 的
   基础 stem（权重更低）；`at*` 族对非 `at` 职业降权，只有没有本职业族时才借用。
3. 命名对不上的显式别名：`nenguard→nenshield`（念气罩）、`sajahu→roarstun`、`sajahuex→roarstunex`、
   `kikouken→atspiralnen`、`nenmonsterwhitetiger→nenmonster`、`pushout→atpush`。
4. 一个族里的文件按子目录轮转取样（上限 12 层），避免 `atnenflower` 的 142 个文件只播第一段。
5. 被动对象补两处：`[basic motion]`（弹道/爆炸类对象用单条基本动作，而不是 `[etc motion]` 表）与
   `[string data]`（对象声明的 `.ptl` 粒子，枪手子弹的可见爆炸全在这里）；相对路径按对象所在
   职业目录解析（`../../Common/...`）。
6. 剑士/暗黑武士共用 `character/swordman`：`_ds` 孪生优先，没有孪生时才用普通文件。
   原实现把普通文件对暗黑武士一律过滤，导致「杀意波动」这类**暗黑武士专属技能**反而拿不到
   `dotarea*.ani`。

**结果（1734 行，`--audit-map`）**

| | A | B | C | D |
| --- | --- | --- | --- | --- |
| 本轮前 | 116 | 492 | 113 | 1013 |
| 本轮后 | 264 | 287 | 170 | 1013 |

- 主动技能里「有动作但零特效」从 **409 → 187**；D 级 1013 条**全部是被动技能**，无主动技能无资源。
- 各职业零特效主动技能：剑士 31→14、格斗 37→14、枪手 31→20、法师 47→29、圣职 45→7、
  男枪 30→19、盗贼 35→22、男格 44→15、**男法 38→5**、暗黑武士 61→34、缔造者 10→8。
- 用户点名：念气罩 3 层、千莲怒放 12 层、雷龙出海 12 层、冰魄剑 6 层、魔法炮 14 层、破冰飞刃 16 层。
- 截图复核：`checkpoints/analysis/fx-{icesword,magiccannon,nenflower,lightningdragon,nenguard,poi2,ld2}.png`。
- 回归 37/37 通过；`verify_architecture` pass（139 单元）。

**已知边界**

- 特效层没有源时间轴（`.als` 只覆盖 81 个技能），预览器把所有层从第 0 帧同时播放；
  千莲怒放这类含全屏闪白的技能在起始帧会盖住角色。这是回放策略限制，不是缺文件。
- 剩余零特效主动技能集中在：女法全部是召唤类（召唤物是 `monster/*` 实体，不是特效 ANI）、
  盗贼/枪手多为平砍与 Buff、暗黑武士多为无特效的普通斩击；5 个通用技能（后跳/跃翔/远古记忆/
  不屈意志/受身蹲伏）本来就没有特效。
- `sq_SendCreatePassiveObjectPacket(id)` 的 id→`.obj` 反查仍未做，实体仍靠技能名匹配。

---

# 高等级技能链补全（2026-11-10 第二轮）

节点 `skill-high-tier-20261110`。用户反馈：低等级普攻类技能正常，**高等级技能基本无法使用**，
表现是「特效不全」或「人物动作不全」。逐条核对后确认四个独立缺口，全部已修。

**缺口与证据**

1. **被动对象视觉从未接入**。高等级技能的主视觉不是 `effect/animation`，而是
   `passiveobject/character/<job>/<skill>.obj` 的 `[etc motion]`：
   `khazan.obj` → Khazan1/2 + KhazanAreaAppear1/2/Stay/Disappear，`saya.obj`、`bremen.obj`、
   `tombstone.obj`、`blache.obj`、`epidemicrasa.obj`、`icewave1..6.obj`、`firewavebig.obj` 同理。
   这些路径既不在 CHR 的 etc_motion 里，也不在 effect 目录下，原实现完全看不到。
2. **CHR 基础动作槽没被当作技能动作**。`[buff motion]`（= `Summon2.ani`）、`[back motion]`、
   `[jump motion]` 是具名槽，`BackStep` 本身就是 `[back motion]`，buff 技能则直接播通用施法姿势。
3. **生成器门槛过严**。`gen_exe_bindings_header.py` 原先只收「资格代码对」或「动作名以 SKL 前 8
   字符开头」的 state，把同一职业内**独占 state**（资格代码已唯一绑定该技能）的 30 条证据全部丢弃。
   另把 SKL 名截成 8 字符，`ashenfork`→`ashenfor` 这类边界直接失配。
4. **exe 覆盖会丢掉同名后续阶段**。exe 绑定只给释放入口动作，`KallaFinish1..3`、
   `HundredSwordMoveReady1..5`、`HundredSwordMoveSlash1..5` 靠 CHR 名字匹配才拿到，
   覆盖时被整体替换掉。

**修复**

- `skill_preview_mapping.cpp/.hpp`
  - `JobIndex` 新增 `passiveObjects`（`_ds` 孪生按 CHR 归属过滤）与 `passiveAnimations`；
    实体候选按「精确 stem → 逐级前缀（tombstonerainex→tombstonerain→tombstone）」依次尝试，
    没有 `[etc motion]` 的对象不算视觉本体，继续下一个候选。
  - 新增 `baseMotions`（具名槽 → `.ani`）与两张显式表：基础动作别名（backstep/jump/dashattack…）、
    动作别名（`reckless → frenzy1..4`，暴走；Frenzy 槽无其它技能认领）。
  - `chainOrder` 重写：阶段词支持多词组合（`hundredswordmoveready2`、`weaponcomboshort1`），
    武器/形态词（short/light/heavy/blunt/blade/spear/claw/pick/shoulder）入表；新增
    「阶段词在前」（`staysacrifice`）与「升级词在后」（`flowmindpowerup → FlowMindStart`）两支。
  - exe 绑定改为**入口动作 + 同名后续阶段合并**（上限 12 段），不再整体替换。
  - `[pvp]` 变体与 `_ds` 孪生双向过滤，swordman / demonicswordman 不再互借动作。
- `gen_exe_bindings_header.py`：采信条件扩为「资格对 / 动作名吻合（完整 stem 双向）/ 本职业独占
  state」，产物记 `basis`；未采信的共享 state 单独计数（本轮 185 条）。

**结果（1734 行技能映射，`--audit-map`）**

| | A | B | C | D |
| --- | --- | --- | --- | --- |
| 修复前 | 47 | 322 | 62 | 1303 |
| 修复后 | 116 | 492 | 113 | 1013 |

- 剑士（job 0）：A 9→18、B 29→40、C 6→16、D 131→101，**剩余 101 条全部是被动技能**
  （`[type] [passive]`，本来没有释放动作）；74 个主动技能全部为 A/B/C。
- 里·鬼剑术拿到 15 段武器区分动作，极·鬼剑术 13 段，暗天波动眼 8 段，冥炎之卡洛 6 段（含 Finish1..3），
  暴走 4 段 Frenzy；卡赞/萨亚/普戾蒙/罗刹/银光落刃从「无资源」到有实体特效。
- 回归 `dnf_skill_preview_tests` 37/37 通过，`verify_architecture` pass（139 单元）。

**仍未闭合（已确认边界，不是解析遗漏）**

- 剩 16 个剑士主动技能只有特效没有身体动作（卡赞/萨亚/萨亚EX/普戾蒙/罗刹/银光落刃/嗜魂之手/
  冰刃·波动剑/爆炎·波动剑/邪光斩/波动爆发/杀意波动/不动明王阵/极冰·裂波剑/死亡墓碑/墓碑三绝阵）。
  根因：这些技能走**共享施法 state**（state 75/13 等），handler 内按 skill id 分支后不是用
  `vtable+0x49C` 立即数，而是 `Sprintf` 拼动画名后 `vtable+0x154`——模板串在 1031 exe 的加密数据段
  （段 2 的 raw 只有 460 KB / 虚拟 4 MB，文件与旧内存 dump 里都读不到明文），静态拿不到。
- `sq_SendCreatePassiveObjectPacket(id)` 的 id → `.obj` 反查仍未做；实体目前靠技能名匹配。
- 其余职业（格斗/枪手/法师/圣职/盗贼）同样受益，但未逐技能人工复核。

---

# 技能链解析核对与修复（2026-11-10）

节点 `skill-chain-audit-20261110`。核对预览器的技能/特效链文件解析，确认并修掉三类漏解析。

**核对结论（1734 行技能映射）**

- 本体动作缺失是主因：只有 406 行（23%）定位到 `bodyAni`，1320 行（77%）连动作都没有，
  自然没有特效；本体+特效+攻击框齐全仅 52 行。
- 特效声明有三层来源，原实现只用了最弱的一层：
  1. `sqr/common.nut` 的 `sq_LoadSkillEffect_<Job>`——**只有 Swordman / DemonicSwordman 两个函数**，
     其余职业根本没有（不是解析漏，是文件里不存在）。
  2. `sqr/character/<chr>/<skill>/<skill>.nut` 的 per-skill 脚本（160 个文件）：
     `sq_CreateCNRDAnimation` 62 处、`sq_AddStateLayerAnimation` 62 处、
     `sq_SendCreatePassiveObjectPacket` 81 处、`sq_SetCurrentAnimation` 106 处。原实现完全没读。
  3. `character/<job>/effect/animation/` 的文件名前缀匹配（原实现主路径，且上限 6）。
- `.ani` 内部没有 effect 段（实测 HardAttack1.ani 只有 img/坐标/damageBox），
  特效时间轴来自同名 `.als` 侧车：PVF 共 1179 个，1173 个与 ani 配对，但只有 81 个技能本体 ani 带 als。

**修复（`skill_preview_mapping.cpp` / `.hpp`）**

- 新增 per-skill 脚本索引：`sqr/character/<chrStem>/<skill>/`（嵌套）与 `<skill>.nut`（扁平），
  含 `po_*.nut`；脚本里的 `sq_CreateCNRDAnimation` / `sq_LoadSkillEffectAni` 字面量按
  `character/<baseJob>/` 解析成 effect ani。
- 新增 `CUSTOM_ANI_*` → CHR `[etc motion]` 索引 → `.ani` 链路：job `*_header.nut` 常量表 +
  CHR 资源按 `(fieldOffset, valueIndex)` 排序。已用 97 个常量/97 条 etc_motion 逐一验证
  （`CUSTOM_ANI_FIREPILLAR1=55 → ATAnimation/FirePillar1.ani`）。
- 特效来源改为**权威优先**：common.nut 声明 > per-skill 脚本 > 前缀兜底；上限 6 → 24。
  前缀兜底收紧为「直接位于 effect/animation 下」或「父目录名等于技能名」，排除
  `chillingpowder/upperswing1.ani` 这类别的技能分支。
- 结果：鬼斩从 6 个（混入 4 个 `*_ds`/`*_fullcharge`）修正为 common.nut 声明的 2 个；
  总特效条目 673 → 706（更准，不是更多）；本体 406 → 414（缔造者 6 → 13）；
  5 个技能（复仇者/元素师）首次拿到脚本声明的特效链。回归 37/37 通过，架构检查 pass。

**仍未闭合**：`sq_SendCreatePassiveObjectPacket(id)` 的 id → `.obj` 需要数据流与 `.lst` 反查；
`.als` 覆盖仅 81 个技能；1320 行技能仍无本体动作（state→motion 未恢复的职业）。

---

# 编译产物集中到 checkpoints/（2026-11-09）

节点 `checkpoints-20261109`。所有编译产物统一输出到仓库根 `checkpoints/`，并排除入库。

- **目录**：`checkpoints/build`（CMake/Ninja 构建目录，含全部 exe/dll/静态库/`build-verification.json`）、
  `checkpoints/tests`（回归测试输出）。仓库根新增 `.gitignore` 条目 `checkpoints/`，产物不入库。
- **工具默认值**：`project/tools/build.py` 的 `--build-dir/--test-dir` 默认改为 `../checkpoints/build`
  与 `../checkpoints/tests`；`verify_architecture.py` 与 `checkpoint_refactor.py` 同步指向新位置。
  输出目录约束从「必须在 `project/` 内」放宽为「必须在仓库内」，因此 `project/build.cmd`、
  `Build-And-Test.cmd` 不带参数即按新路径构建。
- **启动入口**：新增仓库根 `Play-Skill-Preview.cmd`（转发到 `project/Play-Skill-Preview.cmd`）；
  `tools/play_skill_preview.py` 与 `Play.cmd` 优先查 `checkpoints/build`，找不到再回退旧的
  `project/cache/*-build`。
- **本次构建**：全量构建 + 12 项任务回归。编译成功（12 个二进制，`verify_architecture` pass，139 单元）；
  技能预览器测试 **37/37 通过**，截图确认鬼斩播放正常（横幅 `hardattack -> hardattackchargeafter`、分级 A）。
  12 个 core 组中 9 组失败，属既有缺口：2 组因 Windows 260 字符路径限制写不出暂存文件
  （旧路径 294 字符、新路径 283 字符，均超限），其余为未完成功能的内容断言
  （Event.ai、Fighter 源动作、空中反应 RVO 等）。明细见
  `checkpoints/tests/runs/20261108T165710083780Z/FAILURES.md`。测试临时数据已清理，
  `checkpoints/` 合计 222 MB。

---

# 入库整理：技能绑定归档 + 缓存清理（2026-11-08）

节点 `repo-cleanup-20261108`。为提交 git，把上一轮 1031 exe 技能绑定成果从工作区
`work/dnf1031-skill-binding-extract/` 收进主线，并清掉可重建的缓存/快照。

- **成果入库**：新增 `project/tools/skill-bindings/`（1.7 MB）——10 职业绑定 JSON、
  提取脚本、证据 JSON、REPORT/scope/README。生成器改为按自身路径解析输入输出，
  重跑 `python -X utf8 -B tools/skill-bindings/src/gen_exe_bindings_header.py`
  产出 `include/dnf/skill_exe_bindings.hpp`，与归档前逐字节比对**只差生成器路径注释一行**，
  8 职业 298 技能完全一致。
- **删除**（可重建，共约 12.8 GB）：`project/checkpoints/` 7 个节点快照 3.0G；
  `project/cache/` 12 个构建/测试目录 6.1G（保留当前可运行的 `cache/refactor-build` 225M）；
  `project/reports/` 的 seven-job-world / 40jp-deep-merge / knowledge-base / 40jp-review / runs 1.06G；
  29 个只含 `.characters.writer.lock` 的测试漏建目录；`project/saves/refactor` 30M；
  `tools/**/__pycache__`；`delivery/` 2.0G 协作交付包（含 690M rar）。
  工程总体积 14.4G → 1.6G（其中 `knowledge/` 1.3G 保留）。
- **入口调整**：`Play-Latest-Verified.cmd`、`Play-40JP-Merge-Candidate.cmd`、
  `LATEST_CHECKPOINT.json`、`LATEST_40JP_CANDIDATE.json` 随快照一并删除；
  体验入口为 `project/Play-Skill-Preview.cmd`（预览器）与 `project/Play.cmd`（游戏）。
  节点备份改为按需用 `checkpoint_refactor.py` 重新封存。
- 新增 `.gitignore`（cache/ reports/ saves/ checkpoints/ delivery/ 等），构建产物不再入库。

---

# 技能演示 Demo 已按 40JP 口径完成（2026-11-03）

节点 `skill-previewer-40jp-20261103`：`dnf_skill_previewer` 只含渲染与判定，时间轴为毫秒
累加、默认循环回卷；判定（攻击盒/受击盒/命中去重/闪烁）、ALS 特效子链、`.ptl` 粒子
（passive object → `.lst` → `.obj` → `[basic motion]` 可解析）、帧音效全部落地；映射新增
`auto_directory` 来源，全量 A/B/C/D = 42/133/114/1445。文档：`project/docs/SKILL-DEMO-40JP-SPEC.md`
（直证/推断/待验证逐条标注）、`project/docs/SKILL-PREVIEWER-ACCEPTANCE.md`（重写）。
测试 30 项全绿，`verify_architecture.py` 通过。截图取证在
`project/reports/skill-previewer/captures/`。入口 `project/Play-Skill-Preview.cmd`。

---

# C++ 协作交付包已生成（2026-11-03）

已整理源码模块职责、贡献流程、共享构建步骤、来源证据边界、当前能力状态和许可状态，并生成源码/文档交付包：`delivery/dnf-cpp-collaboration-20261103/` 与 `delivery/dnf-cpp-collaboration-20261103.zip`（交付物已于 2026-11-08 删除，可用 `project/tools/package_collaboration.py` 重新打包）。ZIP SHA256：`e96a2a3a54232ac845d3aaea80f6a1e68e42dd0471f0d2ae983a0aee246890e2`；包内 859 项，858 项文件哈希与 ZIP 内容复核一致，CRC 正常。

- 模块说明：`project/docs/MODULE-MAP.md`；贡献规则：`project/docs/CONTRIBUTING.md`；构建：`project/docs/BUILDING-SHARED.md`；来源边界：`project/docs/REFERENCE-BOUNDARIES.md`；能力状态：`project/docs/PROJECT-STATUS.md`。
- 打包脚本：`project/tools/package_collaboration.py`。交付包只含 C++ 源码、测试、依赖、精选分析文档及架构提案；未含客户端/PVF/NPK、ARAD.exe、完整 40JP 原始逆向工程、缓存、存档、历史候选和本机配置。包内未发现本机工作区绝对路径。
- 未运行游戏构建或测试；这是源码交付包，不是可玩版本。项目级许可证仍未指定，公开托管/再分发前需维护者确定授权。当前 40JP 女格斗体验节点仍按 `project/CURRENT_TASK.md` 等待用户反馈；本交付任务未更改游戏运行代码或该节点状态。

---

# 当前：女格斗条件特效体验候选已封存

节点 `40jp-fighter-effect-cues-20261103` 已完成实现、独立构建、变更路径专项验证和两遍哈希封存。构建收据 `project/cache/40jp-fighter-effect-cues-build-20261103/build-verification.json` 为 `build-only`；专项收据 `project/reports/40jp-deep-merge/verification/20261102T231406088866Z/execution-receipt.json` 的 core、人物表现、UI、application-profile 检查均通过。

- 本节点加入 EnergyBall 子状态/样式分支、Spire 持有目标缩放、Shoulder Tackle 命中特效，并修复目标缩放传到本帧新发布 cue 的问题。
- 专项证明当前 1031 ANI/ATK 和 World 接触适配器下 ShoulderTackleHit 有效命中只发布一次；完整回归和前台体验未执行/待用户。
- 候选 `project/checkpoints/20261102T233130091229Z-40jp-fighter-effect-cues-20261103`：3,025 个文件、509,056,490 字节、两遍哈希通过；manifest SHA256 `32612e9a6774e369d3451cc771cf64554cc7f3cb62d3e0d453fbad1450a801d6`，主程序 SHA256 `bbb049fd995b5211c5767dfcc2ca0e77dfe692bceb1a3df0576626e2719bcbdc`。当前指针见 `project/LATEST_40JP_CANDIDATE.json`，入口 `project/Play-40JP-Merge-Candidate.cmd`（两者已于 2026-11-08 随快照清理）。用户体验确认前不迁移其他职业。
- 这是 40JP 行为结构与 1031 资源的跨版本适配。45JP 资料未找到，1031 无 Fighter 专属 NUT 子树，SKL 不直接绑定 ANI；技能映射仍未完整恢复。

节点报告和恢复细节：`project/reports/40jp-deep-merge/fighter-effect-cues-20261103/PROGRESS.md`。原客户端、资料、历史候选及用户存档保护继续有效；完整技能与最终 beta 未完成。

---

# 重构进度与恢复

更新：2026-11-02。状态：独立迁入与首批面向对象重构完成，编译、自动回归和无窗口启动身份审计通过。节点封存不随源码入库（2026-11-08 已清理历史快照，需要时用 `checkpoint_refactor.py` 重新封存）；前台体验与原版动态比较待用户。

## 已完成

- 创建 `dnf-c++-project` 与 `knowledge/`、`project/` 两个业务子目录。
- 登记对象职责、来源保真、原工程保护和逐节点备份规则。
- 从已验证 457 节点按哈希迁入 816 个文件（约 33.4 MB）；125 个原实现单元按职责物理分组。
- ANI 原生合同内置到工程，不再通过相对 include 编译旧逆向目录。
- 当前未验证原工程差异 23 份归档到 `knowledge/unvalidated-native-delta/`，未应用。
- 人物表现组合对象、最小绘制接口、运行会话路径状态对象和有界帧统计已接入实际消费者。
- 新 CMD 入口、独立内容配置、构建/测试/存档路径已写入。

## 验证结果

- 资料归档完成：92,141 条来源映射，59,613 份唯一资料，去重压缩约 911 MB；全量存在性、存储/原字节 SHA256、解压与长度核验通过，11 项代表还原通过。首次共享副本清理错误及 763 份允许来源恢复证据完整保留。
- 父流程独立复核四份交接收据哈希一致；816 份导入文件中 811 份保持原字节，另 5 份为明确登记的 include/入口/人物表现委托修改。
- 构建/回归会话 `26756` 已退出 0；日志：`project/cache/refactor-build-attempt2.log`（PowerShell UTF-16LE）。
- 首次编译失败于新增测试辅助函数名与 Windows `near` 宏冲突；已改名，运行代码未为此改动。原失败保留于 `project/reports/migration/attempts/` 与 attempt1 日志。
- 主程序及全部继承测试目标编译成功；FrameStatistics、人物表现 46 项、原核心、音频 57 项与隐藏 UI 39 项检查通过。构建收据登记 181 份输出文件，不把文件数当作游戏完成度。
- 归属检查通过：128 个实现单元有明确归属，126 个接入编译；另 2 个原基线闲置单元保留并明确登记，未计为运行实现。
- 构建状态、精确源码/产物/静态库/报告哈希及同一内容身份：`project/cache/refactor-build/build-verification.json`，状态 `pass`。
- 无窗口 `--profile-audit` 已退出 0：`project/reports/migration/application-audit/run.json`；同一 EXE、PVF 和静态资源身份与自动回归一致。此模式不启动前台，也不验证实际游玩。
- 主程序 SHA256：`de5929b9377b2bcb265065174e6a72e9b534604a89f080e19473f19b7ffce687`。
- 音频检查使用 SDL dummy，不代替听音；隐藏 UI 检查不代替原版布局、画面、操作与手感确认。

## 本轮执行顺序

1. A0：归档跨来源成果，记录已验证代码基线和未验证差异。
2. A1：独立构建路径、源码职责分组、依赖与来源映射。
3. A2：提取实际运行的对象边界和组合组件，保持现有行为。
4. 编译和对应自动检查，保存节点源码/产物备份并更新恢复文档。

## 启动与恢复

- 曾封存（2026-11-08 清理，哈希留档）：`project/checkpoints/20261102T001149792676Z-architecture-A0-A2a/`；1,113 个文件，988,972,582 字节，两遍 SHA256 检查通过，封存后再次核对清单、9 个关键文件和私有启动参数通过。
- manifest SHA256：`087aaa1bc6b43c024f7707d57fb0f56e106d819f908210b6705c71fbcd323222`。备份为开发节点，`full_beta_gate_passed=false`，前台体验状态 `pending`。
- 体验入口：`project/Play-Skill-Preview.cmd`（技能预览器，需一次构建）与 `project/Play.cmd`（游戏）。
- 源码增量构建后启动：`project/Run-From-Source.cmd`；此入口使用工作源码，后续修改不自动成为已验证候选。
- 每节点备份（按需生成，不入库）：`project/checkpoints/<UTC时间>-architecture-A0-A2a/`；用 `checkpoint_refactor.py` 封存并校验 manifest。
- 节点含源码、EXE/DLL、静态库、自动报告、日志、来源收据、迁移清单和 `PROGRESS.md`。两遍 SHA256 检查后才更新已验证入口。
- 资料包独立保存在 `knowledge/`；每节点保存其清单/验证收据，不重复复制约 911 MB 的资料 payload。原客户端大文件、历史候选等按资料索引只读引用。
- 工作源码和检查点各使用私有存档。原工程、原资料、原用户存档与历史候选未覆盖。

## 后续工作

1. A0：补齐同机、同场景、同输入的真实渲染性能基线；本次有界帧统计只消除一处无界增长，不声称 FPS 已改善。
2. A1：收敛公共 ID、只读内容/资源接口、坐标和资源准备边界。
3. A2：继续提取怪物、地图、独立特效表现对象；人物表现已有真实消费者，但其他模块目前主要完成职责分组。
4. A3：共享 UI 布局/命中、独立窗口与 HUD、业务命令和只读模型。
5. A4–A6：公共动作执行/职业策略、AI意图、战斗/实体生命周期、成长/存档所有权与应用装配。

当前 `dnf_core` 仍为共同链接归档，旧 `include/dnf` 兼容接口和 World 公开可写状态尚未全部收窄。本轮不是完整 A0–A6 或全部职业/技能完成。equipment458/459 的旧堆异常仍未解决，23 份差异只归档未合入。

恢复时先读本文、`project/CURRENT_TASK.md`、节点 `manifest.json` 与验证收据，按 `project/docs/USER-TEST-CHECKLIST.md` 区分自动通过、待体验与原版对照状态；不重跑已结束构建，不把 459 差异直接合入。
