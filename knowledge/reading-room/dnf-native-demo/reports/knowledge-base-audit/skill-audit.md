# 技能、NUT、ACT、ANI、ATK知识库审计

日期：2026-10-20。任务：读取用户新增 `dnf-部分知识库`，对照主工程和当前1031来源。本文是只读审计；本子任务未改生产代码、构建、启动前台或读取/写入用户存档。原始知识库、PVF、历史候选保持只读。

## 1. 已读取范围与准确边界

已读根 `agent.md`、主工程 `AGENTS.md` / `CURRENT_TASK.md`，既有 `dnf-pvf-reference/SKILL.md` 及其技能参考，并读取新增 `dnf-pvf-knowledge/SKILL.md`、`dfo-pvf-skill-main/skills/dfo-pvf/SKILL.md`。新增skill作为资料定位方法，不将其“必须使用”或示例模板当作1031引擎事实。

根已建立全库字节/hash/文本索引：`corpus/source-manifest.json`、`corpus/reading-corpus.jsonl`。本域在其上再次进行全文结构扫描，结果 `skill-corpus-index.json`：**3229份独立提取文本、14,185,780字符**，含技能、NUT脚本、ANI/ACT/ATK文档及相关课程。逐条保存路径、内容hash、字符数、标题、章节、标签、回调名和作者的“未知/推测/测试”语句。此数是去重文本结构扫描，**不是3229份逐行语义理解或原生行为验收**。

语义阅读集中在两份新增skill、`03-skills.md` / `07-advanced-act-ani-nut.md`、dfo-pvf四种格式说明、技能系统概述/标签参考、ANI/ATK标签参考、NUT两篇引擎调用说明，以及原课10527/10528/10530—10533/10536/10538/10544/10584/10598/10612、11413/11414/11580/11665/11724/11730/11750/11773/11805/11901/11910/11919/11925/12051—12058。其他数百篇逐技能参数与2058份新NUT脚本已做结构、标签及回调扫描；未逐个技能执行和验证，不把索引存在计作恢复完成。

全库摘要声称技能课程913篇，当前独立tutorial目录实际**946 JSON**；其中“全职业技能全解”814篇、约662KB。`dnf-nut-script-main`实际2058份NUT，约13.4MB整库。两份课程镜像按提取正文hash去重。不能因摘要写“全部读过”就继承其覆盖声明。

## 2. 来源身份与可重复采集

当前1031 PVF固定SHA256：

`d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d`

原始1031成员、字节数、hash、SKL字段offset/作用域/首行、189份NUT函数索引、关键原文逐行和全ALS标签计数见 `skill-source-evidence.json`。可重新执行只读采集器：

```powershell
D:\ProgramData\anaconda3\python.exe -X utf8 dnf-native-demo/reports/knowledge-base-audit/collect_skill_source_evidence.py
```

该采集器仅导入工程既有PVF读取器；不执行知识库脚本、NUT或工具。采集结果是内容事实，不是客户端回调已经动态执行的证明。

核心资料的原文件SHA256（完整根清单另存）：

| 文件，相对知识库根 | SHA256 |
|---|---|
| `dnf-pvf-knowledge/references/03-skills.md` | `801b08518c66be34b97d9288d33d618f75178ff3abe2ea97f2b6e0257e90bd7b` |
| `dnf-pvf-knowledge/references/07-advanced-act-ani-nut.md` | `38d26f57d55044c23ad0a8c0e8cd555e275bb7ca1d2c5657b5bf5b91f1cd5fce` |
| `dfo-pvf-skill-main/skills/dfo-pvf/references/skl_format.md` | `3943357aff8eb93691db14eef1b4e50f9bed1a1a0f21487a25734693e26e8b9e` |
| `dfo-pvf-skill-main/skills/dfo-pvf/references/als_format.md` | `c517736321d425ee211cdb624e616111dd659f3371e67738bd821339abafcfd6` |
| `DNF-PVF-file-Reference-main/技能文件知识库/标签参考.md` | `bad463871cd25b49360bf36854880a84c7e430c8ebbd9f79b48f01b90d796e49` |
| `DNF-PVF-file-Reference-main/ANI文件知识库/标签参考.md` | `eb06e315976e3e4e18558ebb7619d5ed39c1de8a70ea0ce8b648be26c2884c55` |
| `DNF-PVF-file-Reference-main/NUT文件知识库/高级示例/DNF引擎调用机制深度解析.md` | `b3e6fca0e8892567cc356c097826024a9cb93bfc48aad64c66b3e7c965ecdf80` |
| 原课 `10528_8三段斩.json`，两镜像原字节一致 | `ddbe7e3c06619b13ae85ca9e89af9957ccfebe16cc41cf34b2db2a27d1dbdf7f` |

## 3. 对照结论

| 机制 | 知识库依据 | 当前主工程与1031 | 判定/处理 |
|---|---|---|---|
| SKL场景作用域、等级表宽度 | `03-skills.md:27-33`、原课11324/11337 | `src/skill_data.cpp:21`选择common和dungeon/pvp；`:87`以首个整数为列数后按等级寻址；保留源定义、重复字段歧义 | 主方向一致。逐技能列的用途不能由通用表形状推定 |
| 主动/被动、购买、消耗字段 | 同摘要`:15-28` vs Reference技能标签`:40-50,77` | 1031 `hardattack.skl` `[type]` active offset77、`[purchase cost]`15 offset62、`[consume MP]`17/196 offset297 | 使用当前真实标签正确；不要改成Reference模板的`[skill type]`、`[required sp]`、`[mp]` |
| skill class与职业身份 | dfo `skl_format.md:19,27-40`将其写成职业编号 | 同一鬼剑士注册下 HardAttack=3、TripleSlash=1、ReleaseWave=0；工程SkillKey由职业/技能注册取得 | 文档冲突，当前身份设计应保留；不能用skill class选职业 |
| 三/五段技能系数 | 原课10528逐段文字、六列数表；见下节反证 | 当前1031六列首行与课程一致，但level property明确3段映射0/3、0/3、1/4；当前两伤害消费者同此映射；60US合同也同 | 撤销“3段应依次三列”的初步建议；无生产修改，当前保持。展示映射本身也不等于原生setter已证实 |
| ANI身体/装备/附层、延时 | 原课11413/11414/11580/11665及`07` | `resources.cpp:334`解当前二进制，保留源框和属性；实际渲染/时钟02/03已接。当前原生1031与60US推断profile分开 | 框架一致。新增文本例子不能直接替换当前二进制读取 |
| ANI框六数 | dfoANI说明使用起点+宽高深；ReferenceANI`:258,278`写两个端点 | `resources.cpp:348-355`读x/y/z/w/h/d；原课11413提供0xF+6个i32字节例子，但未证明端点语义 | 资料内部冲突。不能依Reference端点描述重写碰撞 |
| ALS触发单位 | dfoALS`:37`写开始时间/毫秒；原课11665明确帧号 | 1031原生合同为frame:i16；`effect_plan.cpp:120-123`验证源帧；旧静态计划`:184`求此前DELAY和转换时间 | 当前使用帧号正确，不改成毫秒。CDO第1字段同样是源帧，非draw layer |
| NUT注册 | `07:157-170`、原课11910/11919；Reference深度解析`:81`把第5参写优先级 | 1031 `sqr/character/atmage_load_state.nut:15`是job/path/suffix/STATE/SKILL，普通Attack为STATE_ATTACK,-1 | 以真实pushState为准；该高级说明的第5参解释错误 |
| 状态生命周期 | 原课11724/11750列checkExecutable/checkCommand/onSetState/onProc/onEndCurrentAni/onEndState/onKeyFrameFlag | 1031IceCrash完整存在同族；Reference深度解析`:89-92`泛化为onStart/proc/onEnd，混入AP风格 | 通用宿主接口与技能/AP/PO回调要分族，不能盲目统一回调名 |
| NUT执行能力 | 原课11724展示定时、攻击信息、强控、PTL、退出清理 | `squirrel_host.cpp:211-212,273`仅真实注册getBuffSkillIndex与sq_PlaySound；`squirrel_action_service.cpp:135,232`仅ATMage Buff路径实际invoke；`:251`无循环invoke | 是实质未完成项，当前明确unsupported正确。VM能编译≠技能链已恢复 |
| 其他职业模板 | 完整NUT例子包含每技能分支/子状态 | `experimental_character.cpp:159-165`主动声明用户临时普攻模板；SKL身份、MP/CD真实，不具有全部技能机制 | 不能把新增脚本库直接标为全部10角色完成。共享宿主可复用，内容仍需逐技能控制器/脚本 |
| 怪物受击链 | 原课11724的onAttack/强控/AP；ATK push/lift/reaction说明 | `combat.cpp:1410`读ATK响应、源damage动画；统一伤害和StatusHost已有消费者；抓取/AP/PO完整源回调仍不具备 | 需要04的阶段/命中事务与05的反应/死亡生命周期继续接，不能只增加特效图像 |

## 4. 三段斩候选差异撤回的完整记录

最初看到课程10528叙述第一/二/三段各用一组系数，以及当前 `level info` 首行为：

```
6 158 198 198 47 138 158
```

曾提出当前消费者三段`0/3,0/3,1/4`可能应改成`0/3,1/4,2/5`。这一建议**已撤回，根未进行生产修改**。原因是继续核对当前1031 `skill/swordman/tripleslash.skl`（SHA256 `031c2f0741efaf4783f7200da634c05de810a3844099b3f94956089231cd5e1c`）offset4637的`[level property]`，实际三段展示操作数为：

```
3连斩：(-1,0),(-2,3)；(-1,0),(-2,3)；(-1,1),(-2,4)
5连斩：(-1,0),(-2,3) 重复三次；(-1,1),(-2,4)；(-1,2),(-2,5)
```

现有 `damage_runtime.cpp:324` / `combat.cpp:2860` 与三段源展示相符。60US冻结合同和既有 `R60-04-STAGE-PLAN.md:52` 也是普通前三段0/3、0/3、1/4。课程叙述交错编号与表内“先三项百分比、再三项固伤”不能证明原生普通分支应逐列推进。

`[level property]`仅为展示也意味着它不能单独证明原生伤害setter；但它足以推翻“数表首行看起来有三组，所以现实现必错”的说法。当前1031原生setter与用户动态比较未闭合前，保持已有分类和实现。五段资格、ATK末段、阶段时钟仍按04独立接入。

## 5. 新资料确实补充的知识

1. **逐技能参数索引**。814篇技能解释能帮助把static/level列与次数、持续时间、范围、百分比/独立系数、分支阈值建立待核候选。例10527鬼斩static[0]视觉大小100、10536 NormalWave的level[1]大小、10584 ReleaseWave固定系数。1031这些首行/形状可核实；参数文字仍可能错，需要源控制器setter验证。不能以`[level property]`文本代替执行逻辑。
2. **可读的完整脚本案例**。原课11724对应当前1031IceCrash，确切展示输入资格→状态→ANI/ATK→定时事件→碰撞onAttack→AP强控→重复直接命中→关键帧移动/PTL→EndState清理链。当前源 `icecrash.nut` SHA256 `8ccd4ed59b2d8ea5dfee5844803a03ae955a665b2ba5f0e9329ae064d67cca86`；`ap_icecrash.nut` SHA256 `f0dc8f3e2e101bb851e94f0d41116d0d226c1ad7a6deda9c56adb369c82fb0db`。该例比目录/特效文件名匹配提供更强的列和调用依据。
3. **技能、PO、AP回调分工**。技能对象负责状态与输入；PO有自己的生成/攻击/销毁；AP附着在目标上控制受击、状态、移动与退出。原课11730提供回调家族和合并冲突线索，后续须与当前每个`sq_AddFunctionName`注册对应。其“固定串行顺序”等描述仍是社区观察，不能当已恢复调用顺序。
4. **ANI flag连接行为**。原课11750与当前IceCrash `onKeyFrameFlag` 对应源`SET FLAG`驱动移动启动、PTL和抓取清理。主工程现有`AnimationEventCursor`只在已接技能中使用，不能只采到flag却不派发对应技能/AP回调。
5. **新脚本库的特效构造例子**。2058个NUT可以用来定位`CreateAnimation/PooledObject/SetImageRate/Appendage/SendHitObjectPacket`模式及现代UI扩展，但该库包含Anton、扩展UI和其他年代自定义内容；不是当前1031的升级包，也不能直接覆盖189个原生源文件。
6. **ALS通用旁车和缺失指令**。原课11665和dfoALS说明促使重新全量核对当前来源。当前PVF确有4637次`use animation`、2869次`add`、1288次`none effect add`、490次`create draw only object`、52次`remove`、18次random、16次follow-parent。当前消费者只支持add/remove，是大量特效不完整的具体来源之一；不再以“ANI都能解析”概括完整效果。

## 6. 接入04/05的具体建议及边界

- **04阶段/特效消费者**：先闭合现有鬼斩/三段/ReleaseWave阶段与来源绑定，继续真实body/weapon/visual/attack实例。对照当前SKL映射，保留三段现列；五段分支按装备/skill27和精通门槛。技能资源依赖预检在MP/CD提交前完成，关键帧/定时/阶段结束互斥发布，不把父动画全长当所有子效果寿命。
- **04共享ALS扩展**：为none-effect和draw-only建立独立命令变体、完整SourceRef、owner/action、once-fired/loop-rearm、出生坐标与清理语义。旧1031 `reports/combat-native-reverse/resource-render/contract.json` 已确认none-effect相当kind0附层并写child首dword=1，**renderer含义UNKNOWN**；不可直接别名add并声称正确。draw-only的源字段为frame/name/x/y/z，需独立世界实体；random和follow-parent有额外RNG/owner限制，不能压平成普通附层。当前unsupported诊断应保持直至有可执行、具名推理消费者。
- **04/后续职业脚本宿主**：建立数据getter、状态请求、当前ANI/ATK、效果构造/缩放、实体和时间事件最小纵向闭环，先用当前1031WindStrike/IceCrash来源验证。每接一API必须有真实消费者、事务和失败清理；不要批量空注册返回成功。社区所谓“全部职业一套逻辑”应解释为共享引擎API+不同脚本/原生控制器，不能共享一段动作替代技能。
- **05怪物/物件反应**：将accepted-hit、目标AP/抓取、damage/down/overturn、死亡/碎片和场景OBJ破坏分开。当前ATK的lift/push/reaction、ANI damage boxes和逻辑状态各保留来源；“关闭破坏框=所有伤害无敌”等社区说法需区分普通碰撞和直接HP/packet路径。坏脚本、目标死亡、切图、换角色时清理AP/PO/定时/保护。
- **验证**：缺失指令报告要绑定当前PVF hash并给到具体路径/offset；技能分支需实际World输入、空放/命中、正常/测试账本、退出/保存重载和不同补tick验证。没有前台动态对照时仅记自动逻辑通过。

本域没有发现可以仅凭本次社区资料就安全替换的、已证实的1031窄行为bug。已发现的具体缺口按上述04/05接入；保持当前运行版本的来源正确项。此结论不表示技能已完整，也不表示全部知识库声明均正确。
