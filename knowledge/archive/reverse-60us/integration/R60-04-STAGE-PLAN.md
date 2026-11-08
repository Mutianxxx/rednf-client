# R60-04 技能阶段与视觉实体接入准备

日期：2026-10-20。范围为 **鬼斩 → 三段斩 → 波动爆发** 的 CHR/SKL/EQU/LAY/ANI/ATK 与实际视觉、命中消费者。机器记录见 [R60-04-STAGE-PLAN.json](R60-04-STAGE-PLAN.json)。这是在 R60-03 整合期间完成的只读差异核对与下一节点安排；本次只新增这两份文档，没有修改生产代码、构建游戏或运行原客户端，也没有新增 REA 调查。

建议保留已经接入的来源身份、学习/费用事务、真实装备图层、60 Hz 模拟与 R60-03 动画游标，在主战斗增加技能阶段消费者，再依次补普通鬼斩、三/五段斩及波动爆发。不能以通用单动作预览或资源路径匹配代替控制器。**1031 十个非缔造者角色、实际转职/觉醒及完整主动/被动最终门槛不变。**

## 1. 来源身份与证据边界

| 来源 | 固定身份 | 本次用途 |
|---|---|---|
| 60US 冻结 release | `releases/20261020-01`；EXE `a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b`；PVF `23538ef1967baec4947c89ea0363cdce66230a3949b662faf54f7558673d7a98` | 只读 `combat_hardattack`、`combat_tripleslash`、`combat_cast_state`、`combat_spawned_object` 的合同、资源与静态字节证据。 |
| 当前 1031 | PVF `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`；既有 inventory 记录 EXE `246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264` | 使用现有 hash-bound 注册/CHR/SKL/ANI 报告；另外直接只读 PVF 核对波动爆发六项资源与 OBJ 注册。本次重新计算 PVF hash，未重新扫描 EXE。 |
| 当前 C++ | JSON 逐文件记录 `src`、`include`、相关测试和报告 SHA256 | R60-03 正在整合的源码审查快照，不代表已构建候选。后续开工须复核文件身份，不能用旧源码覆盖根任务整合。 |

四个冻结目录共 **468 份文件**逐项与原 `package-manifest.json` 的 SHA256、长度相符；没有刷新 manifest，也没有重跑冻结目录的生成/验证脚本。该结果只证明交接字节完整，不是技能运行通过。冻结目录中历史检查计数仍是历史结果。

收尾复核30份输入时，28份身份不变；根任务的R60-03/R4整合改变了 `combat.cpp` 和 `R60-03-REVIEW.md`。本次已重读新 `combat.cpp` 中技能安装、游标选择、附层生成与效果时钟入口，本文三技能差异仍成立；新combat身份为 `0e26569175685f6d43cea0d28c8dc90f45dc9a3d743227b970ac58b0668feb90`。前后身份及复核时间都保留在JSON，不把其他代理的修复算成本次实现或测试。

60US 的控制器分支和算法迁入 1031 时继续标 `cross_version_inference`。只有当前 PVF 的注册、字段、逐帧数据等直接来源事实可以标 `1031_source_verified`；后续自动游戏检查、用户画面/听音/手感和原版动态对照分别记录。不得移植 60US 地址、对象偏移、状态号、技能号枚举或文本 PVF 语法。本计划使用的 1031 技能号已从当前注册重新核对。

## 2. 应保留的实际消费者

| 模块 | 已有实际行为 | 下一节点边界 |
|---|---|---|
| `combat.cpp::sourceSkill/requestSkill` | 从当前职业注册和 SKL 取得名称、模式、等级数据、指令；正常释放检查学习资格、地面/空中、MP/CD，使用 `skillCosts` 提交。续段不再次扣 MP；三段斩当前在控制器退出起 CD。 | 不把构造器中 first endpoint 字段误当费用服务全部行为。保留正常学习账本和测试覆盖分离；新增绑定预检必须在 MP/CD 提交前完成。三段斩原生退出函数确切 CD 副作用仍未恢复，现有起点是具名重建。 |
| `appearance.cpp/equipment_motion.cpp` | 读取当前实际 EQU 的 variation、signed layer order、LAY 模板及 CHR tag/slot/occurrence；来源、空值和未知项保留。 | 复用当前装备解析，不安装冻结 club 预览夹具作为玩家武器。当前 LAY 支持范围仍有明确限制，缺层不得用自制攻击盒补洞。 |
| `character_attack.cpp` | `readCharacterAttackMotion` 只接受当前 CHR 绑定的身体 ANI，并读取真实武器层；已有 `boxesAt(Snapshot)` 用 `followClock` 投影武器。 | 这是技能可复用的真实盒消费者。下一节点让技能也传快照；现有 `boxesAt(frame)` 仍是按帧索引路径。其 JSON 中临时分类不自动变成完整技能原生恢复。 |
| R60-03 身体/装备/效果 | 普攻和实验选定动作已接游标；渲染可消费快照；装备具备 root 与 min DELAY 投影；效果有独立播放与 ALS 父帧 add/remove。 | 主技能仍未接身体游标；效果目前固定 `SourceDelay100`、rate100，并没有恢复指定角色速率继承。位置跟随、暂停跟随、速率继承和同根时钟继续分开。 |
| `damage_runtime.cpp` | 普通模式由统一伤害链在目标接触时计算；鬼斩当前读 SKL 百分/固定列 0/1，三段斩读 0/3、0/3、1/4，并保留推理 trace。 | 完整伤害公式后置不等于新实体可伪造成功。现有三段列可复用到普通三段；五段列、精通浮空和波动爆发 scalar 必须单列策略，不能从 ATK 或原版 helper 名称推定已闭合。 |
| 退出和恢复 | 死亡/切图/换角色等有瞬态清理；普通 checkpoint 明确取消动作、输入与视觉实例。 | 本批继续取消瞬态，不暗改为动作续演。新游标、pending、附层、攻击账本按同一 owner 清理；独立攻击实体的存续与取消规则必须显式定义。 |

`Stage` 的第二个聚合字段是 **moveSpeed**，不是 duration。因此 `{"tripleslash1",360}`、`{"tripleslash2",360}`、`{"tripleslash3",300}` 是当前重建的移动峰值；正常阶段结束仍取 ANI duration。当前 1031 每个 TripleSlash 身体都是 `70,70,70,70,300`，共 580 ms，不能误写为 360/360/300 ms。

## 3. 逐技能差异

### 3.1 普通鬼斩

当前 1031 注册为 job0/skill5 `skill/swordman/hardattack.skl`；CHR `[etc motion]` slot1 指向 HardAttack，`[etc attack info]` slot0 指向 HardAttack.atk，与冻结合同选择形状一致。这是资源绑定一致，不证明 1031 本机控制器调用已还原。

| 项目 | 60US 有界合同 | 当前实际消费者 | 最小修改 |
|---|---|---|---|
| 适用分支 | skill6 等级0的普通分支；其他 substate/蓄力不在合同内。 | 主技能仅一个 hardattack 阶段；passive6 噬灵鬼斩没有完整控制器。 | 在版本适配登记普通分支范围和排除条件；读取当前账本的 skill6 身份，不能将蓄力分支追认为完成。 |
| 身体时钟 | 安装来源身体；原生时钟/阶段应用仍有独立边界。 | `startStage` 清普攻游标，设置 `poseFrame=0`；`attackFrames` 仅在 `active_<0` 时走游标，技能按 elapsed 抽帧并强制 pose。 | 安装技能阶段游标；同快照驱动身体、武器、声音、帧事件与结束；首帧发布一次。 |
| 两个视觉实例 | HardAttack1/2，独立 attach reset，key1/2，方向镜像的 actor X+40/Y0；继承指定角色播放率，位置跟随独立。 | 两张 ANI 已真实生成，但偏移均0、默认 layer1、source-rate100，生存期用源时长。 | 适配项登记 +40、key1/2、独立重置与显式速率继承；不共用身体 frame index。角色效果链和身体装备链分开排序。退出清理采用可追溯宿主规则。 |
| IMAGE RATE | SKL static[0]×f32(0.01) **覆盖**每帧两个 IMAGE RATE 分量；仅视觉。 | 未见运行时该覆盖消费者。 | 增加实例级 pose rate override，采样时替换源 rate，再进入既有变换；不改缓存 ANI，不额外乘原 rate，不缩放攻击盒。当前 dungeon static100 得1。 |
| 攻击几何 | 身体与 HardAttack1/2 都无 ATTACK BOX；使用所选装备层。 | 当前1031这三张 ANI 也无攻击框；已读真实武器框，同时在身体3..5帧额外 `strike(160×40×110)`。 | 在新具名策略关闭这项旧重建补框，以当前 EQU/LAY 武器框为唯一此分支几何来源；旧策略可比较并如实诊断。源层缺失不能换成补框成功。 |

1031 HardAttack 身体为18帧/950ms，两张效果各8帧/550ms；按当前文件读取，不复制冻结 ANI 的帧表或总时长。完整命中资格、蓄力、精通/被动与最终伤害仍不是本有界分支的原生完成证明。

### 3.2 三段斩与有资格的五段分支

当前 1031 skill8、CHR 身体 slot3..7、ATK slot2..7 均存在；SKL 为六列等级表，与冻结60US当前表三列的内容差异保留。当前普通三段技能列选择 0/3、0/3、1/4 与合同算法对应；冻结表固定列越界返回0的结论不能套在1031六列表上。

| 项目 | 合同/当前来源 | 当前实际差异 | 最小修改 |
|---|---|---|---|
| 普通三段 ATK | motion3/4/5，ATK2/3/**7 TripleSlash3Down**。当前1031 slot7存在，带 down、push300、lift200。 | `attackResponse` 按 `tripleslash{phase+1}.atk` 拼路径，末段实际选择 TripleSlash3，未选择3Down。 | 分支登记中绑定 CHR 有序 ATK slot；不靠文件名拼接；断言普通末段使用当前slot7。 |
| 五段资格 | 60US：skill27>0，且武器type5/skill4≥static[1]或type1/skill13≥static[0]，对应精通>0。当前1031注册仍有4光剑精通、13太刀精通、27武器奥义，阈值来源均5。 | 只有三段 Stage；四武器显示/`weapon%4`及现有被动列表不能充当完整五段资格消费者。 | 从实际 EQU/CHR/SD subtype 与正常技能账本核对类型映射，具名推理实现资格；不因换显示武器/测试等级自动授予精通。五段用motion3..7、ATK2..6，百分列0/0/0/1/2，固定列3/3/3/4/5。精通末段浮空的1031列映射须另核对，不能抄60US列号。 |
| 续段窗口 | 当前 ANI 0..4；60US门是当前帧≥3，随后请求下一段。 | 同技能请求和 key6 都直接 `queued_=true`；只有 ANI结束才消费 queued。早按是否缓存属于当前重建，未证明原生。 | 门以技能游标 frame≥3 表达，禁止写死210ms。早按丢弃或缓冲须具名选择；新恢复策略遵循可用门与实时输入，不把旧无限期 queued 当原生事实。 |
| pending 优先级 | 合同中下一段priority1，结束idle priority0，后发idle不能覆盖已接受续段。 | bool queued + duration结束选择，未表达同tick候选优先级。 | 每tick收集有owner/phase的候选，稳定比较优先级后提交一次；续段与ended同时出现时下一段胜出。每段新攻击ID/去重表，MP只在首次扣；最终退出CD只提交一次，仍标推理。 |
| Slash/Move | 每段 Slash{n+1} key2；Move{n%2+1} key1；attach独立reset、指定角色速率；每段退出detach二者。 | Slash实例已生成但用人工不同XY；永远Move1并偏移(-70,-25)，两个默认layer1；续段并未按owner/段清理旧二层。 | 参数和偏移集中登记；新profile按冻结已证实字段适配，未知flag保留；按段生成/重置，明确1/2顺序、交替Move并在段退出detach。不能删无关持续实体。 |
| 声音 | 非末段交替SM_TRIPLE1/2，末段SM_TRIPLE3；每段另有R_TSLASH。 | 当前普通三段SM_TRIPLE1/2/3已发；当前身体与选定Slash/Move ANI无源声音，分支中未发R_TSLASH。 | 保留普通已对部分，补每段一次R_TSLASH；五段用交替规则，声音跟阶段提交而非渲染调用。 |
| 装备与攻击框 | 身体、Slash、Move均无攻击框；当前1031数据一致。装备同motion用身体root时间，复制min帧数DELAY，保留子层自身图像/框。 | 已有真实武器框；另在第二段1..2帧加入 `130×40×70` 重建框。技能未传新快照。 | 新策略禁用该补框；复用快照投影；验证身体末帧300ms与子层不同源延时不会分离。冻结club只是来源夹具，不能替换实际武器。 |
| 位移/方向/粒子 | static[600,-1000]的setter已恢复；完整积分/障碍规则未知；方向setter还有门；200ms生成index2的实际粒子资源未知。 | 使用360/360/300峰值和通用90/110ms缓动；左右按键在技能期间直接改方向，hitstop后还应用held转向。 | 保留为可比较命名重建，集中登记来源和影响；源码中不能声称其为原生轨迹。方向增加适配门，待1031核对；不捏造index2资源或混同现有Move效果。 |

三/五段计数在动作开始以经资格核对的装备/账本确定，不能因过程中更换测试覆盖产生多扣MP、重复CD或遗留旧段。五段能力不具备时给出具体原因，不把必要分支永久隐藏来降低beta门槛。

### 3.3 波动爆发：不能拿地裂波动剑替代

当前注册已重新核对：**skill20 是地裂·波动剑 NormalWave；skill32 才是波动爆发 ReleaseWave。** 当前主技能表没有32。`stageEffects(frame4)`创建的 `normalwave.obj`、X+30、speed500以及 `normalwave:projectile` 都属于20，应继续回归；不能改名后当作32实现。

| 项目 | 冻结合同与1031来源 | 当前差异/最小接入 |
|---|---|---|
| 学习资格 | 1031 ReleaseWave SKL required level25、fitness growtype[4]；有源MP/CD/指令与完整等级表。 | 新注册走现有学习、normal/test ledger和费用服务；未转职基础鬼剑士不因F6配置或默认列表增加而取得普通释放资格。 |
| 两阶段身体 | 60US共享cast phase0→phase1保留skill/index，分别用throw pair2-1/2-2；当前1031 CHR这两个tag确为Summon1/Summon2（150/600ms源动画）。 | 新适配保留phase与motion identity、单独phase clock及duration参数。60US请求duration0=0、duration1来自运行时helper，不能拿150/600源动画总和直接冒充施法阶段时长，也不能将所有参数称为攻速。可先给出可执行命名推理策略与trace。 |
| 生成时点/门 | 60US是**phase0 apply**先生成两个视觉，再检查ownership gate生成逻辑对象；不是所有cast phase1统一spawn。 | 事务提交点与生成门分开。离线本地owner gate的替代规则明确标推理，使用有效EntityHandle/owner；门失败可保留两视觉但不得产生逻辑伤害实体。源/资源预检失败则整个技能启动无MP/CD/实例半提交。 |
| 两个视觉 | 当前ReleaseWave1为7×70ms、ReleaseWave2为6×70ms，末帧均空图、全程无攻击框。60US attach参数分别+1/-1；其全部语义并未独立闭合。 | 生成两个独立视觉实例，从当前源ANI读图/时间；不让其进入伤害消费者。signed attachment key的宿主映射需标推理，保留原参数证据；不把同根位置跟随等同同根时钟。 |
| 逻辑攻击实体 | 当前注册20018→ReleaseWave.obj；OBJ basic motion和attack info确指ReleaseWave ANI/ATK，无ACT字段。逻辑ANI五帧全空图、5×80ms。 | 独立工厂从当前注册解析，保存source/owner/action/attack ID；起点actorXYZ、无请求位移，speed0。没有图片仍必须进行攻击框采样；不能因throw命名赋投射速度。`floating height=1`保留，不未经消费证据就给Z加1。 |
| **版本差异** | 60US五帧框均 `[-84,-50,0,168,100,234]`；**1031帧0..3同前，帧4为 `[-84,-50,0,168,100,200]`**。 | 直接逐帧读当前ANI攻击框；禁止把60US框常量复制进新对象。源码消费者和自动用例必须能观察末帧变化。 |
| 命中/伤害 | 60US该对象ANI更新不逐帧reset hit list；完整accepted-hit历史仍未知。dynamic scalar经运行时helper，不等于原始level列。 | 当前效果伤害白名单只有20/64/58/65，不能只加32白名单就算完成。建立具名攻击实体消费者与跨帧账本；单实体/目标去重是首版显式推理，新的进入目标仍可命中。scalar先实现有依据的可切换策略并输出trace，未知原公式保持未知。 |
| 结束 | 60US ANI ended保留尾帧，该特定对象外层tick检查ended后请求remove；两视觉资源末帧为空图。 | 只给ReleaseWave逻辑对象选择ended→remove；不能给所有视觉/OBJ普遍套此规则。视觉、逻辑对象、cast owner可分别到期；死亡/切图等按宿主取消策略清理，无幽灵判定/重复奖励。 |

直接读取的当前六项资源均存在，三个ANI完整解码且结构问题列表为空；SHA256、源偏移和逐帧框记录在JSON。这是资源闭包核对，**不是32已可释放/命中或用户画面通过**。

## 4. experimental 的定位

`experimental_character.cpp` 已真实使用所选职业自己的 CHR/ANI/ATK、技能源级别和MP/CD；R60-03选定动作游标可输出帧visit/声音，`experimental_world_adapter.cpp`再读取实际EQU/LAY武器框，私有candidate通过预检后提交。应保留这些消费者和故障不扣费能力。

它仍执行一次手选motion/ATK；`sourceModifiers`明确采用命名的100%实验ATK策略，缺少SKL专用列、阶段/续段、HardAttack视觉覆盖及ReleaseWave实体工厂。普通job0走专用World控制器，九个实验职业仍是用户指定测试模板。不要把三项Swordman适配复制给其他角色，或仅改变诊断中的 `runtime_complete/native_confirmed`。公共阶段/附层/实体接口可供后续职业专用控制器使用，十职业的独立覆盖记录继续保留。

## 5. 串行最小实施安排

R60-03统一候选、审查修复、自动验证与节点备份由根任务先收口。本计划不改共享入口/构建目录；后续每批开工先核对JSON中的源码hash，适配最新整合结果，不还原历史副本。

| 批次 | 建议写入范围 | 可审查运行结果和退出条件 |
|---|---|---|
| **04A 当前版本绑定** | 新版本适配登记/数据；`combat.cpp/.hpp`小范围绑定入口；相关来源检查 | 以当前job/skill注册、CHR tag/slot/occurrence/SourceRef描述5/8/32及必要6/4/13/27资格；来源hash变化明确拒绝或重建。解析motion、ATK、效果、OBJ及实际装备依赖，资源预检先于费用提交。阶段控制规则放适配层，源路径/数值从当前文件取得。 |
| **04B 技能阶段时钟** | `combat.cpp/.hpp`、`resources.*`必要adapter；复用R60-03共享游标；`renderer.*`只在现有快照接口不够时修改 | 当前普通鬼斩/三段技能身体、装备、盒、声音与帧事件同一snapshot；首帧/补tick不丢不重；hitstop delta0，不双移stageStart再推进游标。owner/phase/action ID、pending优先级、取消原因可诊断。source-delay和inferred-deadline可比较，独立于render profile。 |
| **04C 普通鬼斩闭环** | 适配登记、视觉实例pose override/速率/位置字段及消费者；`combat/renderer`有界修改 | +40镜像锚点、key1/2、独立reset及指定速率实际生效；static仅覆盖视觉IMAGE RATE；新策略只有真实武器攻击框；中断/死亡/切图可清理。蓄力6分支单列未完成，不扩大证据范围。 |
| **04D 三/五段闭环** | 适配登记、技能阶段pending、资格/ATK/技能列及按段视觉清理；现有统一伤害接口必要列映射 | frame3续段、priority1胜idle、无重复MP/CD；普通末段3Down；有资格五段/精通消费者有具体来源或命名推理；Slash/Move、交替音、R_TSLASH、每段detach和武器root帧全部实际执行。位移/方向/未知粒子保持分类。 |
| **04E 波动爆发闭环** | cast阶段adapter、统一视觉/攻击实体工厂/生命周期服务；学习/normal输入登记 | 源资格正常可用；phase0两视觉、gate后逻辑实体；正确当前ANI/ATK、无凭空速度；空图命中、跨帧账本和特定ended移除实际运行。保留NormalWave20独立回归；动态scalar与phase duration的推理规则可比较且可追溯。 |
| **04F 候选与备份** | 根任务串行维护构建、覆盖报告/用户步骤、相关移植说明、checkpoint工具输入 | 新独立D盘候选/存档；自动结果绑定源码/EXE/来源hash；失败证据保留。记录每项implemented/auto/user/native状态，不计全职业或完整beta通过。 |

适配层建议使用语义名（如普通鬼斩、三段斩segment、cast phase、ReleaseWave攻击实体），而不是60US state20/22/10作为本项目状态枚举。通用层只执行阶段/时钟/绑定/事务/清理语义；数值或控制器专用分派集中登记来源、版本、证据等级与未验证影响。

## 6. 下一节点必须新增的有效检查

以下为**待实施/待执行**，本次没有构建或重跑游戏测试；已有测试源码只作为复用入口。

| 检查组 | 实际断言 |
|---|---|
| 来源与变更检测 | 当前5/8/20/32身份不可互换；3Down slot7、throw2 pair和20018 OBJ绑定；原始token/SourceRef、重复模式保留；坏/缺资源在扣费前失败，现场MP/CD/实例/事件/RNG不发生半提交。 |
| 技能游标 | 30/60/144Hz与大dt分tick补完得到同样的阶段、帧visit、声音/实例计数和命中；不同攻速用frame3而非210ms；首帧声音/盒同tick消费一次；暂停改速不重投影冻结姿态，恢复只推进一次。 |
| 鬼斩视觉/几何 | 双朝向+40、key1/2顺序；非1源IMAGE RATE夹具检查覆盖而非相乘，缓存不变、攻击框不缩放；裸/有武器使用各自来源，不出现旧补框；普通与skill6分支清楚分开。 |
| 三段分支 | 帧2拒绝续段/帧3允许；早输入按具名策略处理；续段和ended同tick优先级；三段slot2/3/7及五段2..6；资格在门槛两侧与非对应武器拒绝；MP首次一次、退出CD一次、每段新攻击ID；旧段两层清理、Move1/2交替和R_TSLASH计数。 |
| 真实装备根 | 身体末帧300ms和子层源70ms的有界夹具；当前1031真实EQU/LAY body/weapon collision/render frame一致；不同帧数仍保留源数据，未支持图层明确诊断。 |
| 波动爆发实体 | phase0先两视觉再gate；门失败只两视觉；门成功一个实体且speed0/当前XYZ；三视觉/逻辑轨独立；空图ANI确有伤害消费者；frame4高度200断言；对象跨帧不重置账本、新目标进入能命中；expired只移除该对象，不广播删除全部效果。 |
| 退出与故障 | hitstop、阶段结束、受击中断、死亡、切图、换角色、脚本/资源异常后不遗留保护、pending、附层或攻击框；普通重载取消瞬态并保留正常成长/学习/费用与奖励账本，不重放技能/奖励。 |
| 原功能回归 | NormalWave20仍按自身源路径/投射物规则；普通普攻新游标、九实验职业自身武器与故障事务、ALS动态子层及现有合法房间业务继续通过相应检查。 |

建议扩展现有 `test_native_attack.cpp`、`test_character_attack.cpp`、`test_skill_effects.cpp`、`test_skill_eligibility.cpp` 及统一伤害/恢复测试；不要把新策略期望从被测代码生成。现有NativeAttack测试主要是普攻；SkillEffects重点包含20、64、58、65和ALS，并未覆盖本计划的完整5/8/32合同。

交付步骤须使用新候选/独立存档：正常角色验证鬼斩与三段学习和装备→双朝向/不同攻速/续段→有资格分支验证五段→源资格允许的角色释放波动爆发→NormalWave20区分回归→中断/死亡/切图/重载。画面、听音、手感与原客户端动态逐项比较继续由用户执行，不能以静态图、结构检查或本计划替代。

## 7. 仍未恢复的边界

完整1031专用控制器调用、阶段transport/reset flag、真正actor时钟通道和速率类别、TripleSlash精确运动/方向门/200ms粒子资源、精通最终列与浮空单位、cast duration运行时helper、ReleaseWave ownership的原生环境语义与dynamic scalar、accepted-hit/reset和完整伤害公式仍需分别推进。允许明确、有依据且可执行的推理实现进入beta；未实现实质消费者的字段或未知占位不能通过最终门槛。本节点只准备这三个技能的后续接入，不改变P01–P19、完整十职业及世界业务范围。
