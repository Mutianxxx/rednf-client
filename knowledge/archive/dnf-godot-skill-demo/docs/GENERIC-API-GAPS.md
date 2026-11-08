# 通用源程序编译与宿主 API：第一轮缺口及扩展顺序

交付更新：本轮已通过通用旧API别名、AttackInfo赋值、声音与震屏消费者闭合第二条真实程序；最终是2 executable、52 partial。下面保留第一轮审计快照与扩展依据，最终数字以 `reports/DELIVERY-V2.json` 为准。目录和编译器也已共用旧API别名，补齐精确动作映射，没有按技能逐项适配。

2026-10-21，只读分析。本文件依据已导出的当前1031注册调用图、`reports/catalog-v2/compiler-audit.json` 和新增 `pvf-utils-info` 文档；没有运行PVF导出器或Godot，没有修改主工程。审核快照 SHA256：`e4773ec8a2b754a564a81134a9f9b1d8c44c2cf64d3d4ade4c8223f79b7ca764`。后续编译器会更新，下面数量只对应此第一轮快照。

核心判断：当前1项 executable 主要受有限编译器及宿主能力限制，不能归因于PVF只定义了1项技能。扩展应按状态参数、对象变量、动画、数据、包、PO、事件等通用API组推进。不得按技能ID、名称或资源stem分派，也不能跳过未知控制流来提高数字。

## 第一轮缺口归组

第一轮54条已注册脚本技能中，53 partial、1 executable。每个函数目前通常只记录遇到的第一个阻挡，因此下面不是完整所需API数，也不能将同组计数相加当作技能数量。

| 首次阻挡/类别 | 快照出现数 | 实际含义 |
| --- | ---: | --- |
| getSkillSubState | 49条诊断 | 多阶段状态读取；一些是未使用局部变量，但不能一律替成0 |
| datas 未绑定 | 25条诊断 | 缺当前state packet的int-vector参数载体 |
| onEndState | 37条诊断 | 缺退出/中断消费者，可能负责缩放、装备、appendage等恢复 |
| onProc / onProcCon | 36 / 24条诊断 | 缺固定模拟tick回调和输入控制回调 |
| prepareDraw | 27条诊断 | 不能按函数名直接判不支持；有空实现，也有真实绘制 |
| getVar | 11条首诊断 | 缺对象归属的类型化变量容器，后面往往还有vector/timer/object引用 |
| onTimeEvent | 8条诊断 | 缺定时事件参数和回调返回语义 |
| sq_PlaySound | 5条首诊断 | 当前完整调用图44条技能有此API；必须有实际音频消费者 |
| 旧拼写API | 多条 | sq_stopMove / sq_setCurrentAnimation / sq_addSetStatePacket等，不能只支持一种大小写 |
| tofloat / 嵌套接收者 | 多条 | 缺普通Squirrel数值转换/方法调用表达式解析，非技能专用能力 |
| for、分支变量、helper | 多条 | 编译器控制流边界，不能忽略循环体或调用helper |
| 缺body / 缺end | 52 / 43条 | 多数是前述编译失败的派生诊断；另有真实空脚本，必须区分 |

已导出的这批注册图共有386种API/方法名；其中包括不同宿主类同名方法及多个注册上下文，不能简单按字符串全部统一。常用家族出现于多条技能：getVar41、setSkillSubState38、tofloat36、sq_GetLevelData34、sq_GetVectorData31、sq_GetCurrentFrameIndex20、sq_GetCastTime17、setTimeEvent7。这里是源调用出现数，非已实现数。

## 首先修正共同取数合同

当前源图中全局形态 `sq_GetLevelData(obj, skillId, column, level)` 的末参是技能等级，倒数第二参才是列。第一轮编译器曾用 `args[-1]` 取列；扩展前应修正，并分别验证method/global签名。`sq_GetIntData`、`sq_GetStaticData`、`sq_GetSkillLevel` 也必须验证请求的skillId、scope和level，不可跨技能时仍读当前选中技能。

技能存在同名多段 `[static data]` / `[level info]`，例如Hedgehog的普通副本Lv1是1020，PVP段是213。保留嵌套作用域；不能最后一段覆盖第一段，也不能因教程称默认地下城就删除PVP段。`level_data`如果已经是当前等级的一行，读取只再按column索引，不重新把level当column。

被动倍率暂以identity演示必须显式记录。EX技能等级查询不能自动返回主技能Lv1；需要真实测试配置或明确EX=0策略，无法闭合则partial。类型转换 `tofloat` / `tointeger` 应按receiver求值；不把方法名当无参全局函数，也不丢失嵌套 `obj.sq_GetCurrentAni()`。

## 可立即完成的通用API家族

| API组 | 当前证据 | 通用实现建议 | 必须验证 |
| --- | --- | --- | --- |
| 已见旧API别名 | 当前1031 priest脚本中大小写不同，操作序列和CHR槽可闭合 | 显式同语义别名表；按receiver/API家族映射，不对整个语言盲目lowercase | 未知近似拼写仍拒绝；参数数量和类型保留 |
| actor AttackInfo setter | 当前1031多技能调用与SKL列说明互证 | 当前动作的AttackInfo实例副本上设置percent/fixed分量，不修改共享源descriptor | 新动作重置、owner死亡/中断清理、不同技能互不污染 |
| sound | 当前1031 sq_PlaySound字符串；知识包audio词典 | 从当前客户端音频tag注册解析实际声音资源并播放，保留源tag/path/hash | 缺音频不假称完整；静音/音频设备策略明示；声效启动时刻按源事件 |
| shake | 当前1031帧flag内sq_setShake；runtime词典179行 | 通用camera shake操作，源power/time进入消费者；波形和像素解释标演示推断 | flag只触发一次、150ms结束、暂停/重置/中断不遗留 |
| 空或只读callback | 当前prepareDraw/onProc/onEndState中有仅null guard或读取未使用变量的实现 | 解析函数AST及纯查询；确认为空效果才可接受，不按名字忽略 | 空函数与同名有副作用函数分别测试；异常和未知调用仍拒绝 |

### 最短真实闭包：使用复仇之刺验证API，而不是给它写专用执行器

`sqr/character/priest/hedgehog.nut`，SHA256 `785588ad5884600326f6b469cfceb521e4b7957ca330152b40c62885d7acb630`，只有onSetState/onEndCurrentAni/onKeyFrameFlag三个行为callback，无helper、循环或多substate：

```text
stopMove
→ setCurrentAnimation(CHR etc slot90)
→ setCurrentAttackInfo(CHR etc ATK slot72)
→ setAttackPowerWithPassive(skill,state,-1,0,1.0)
→ PlaySound(PR_HEDGEHOG)
flag2 → shake(owner,3,150)
ANI end → stand
```

slot90是 `character/priest/animation/hedgehog.ani`，slot72是 `character/priest/attackinfo/hedgehog.atk`，均由当前CHR顺序读取。技能源 `skill/priest/hedgehog.skl` SHA256 `748b492fe1931c70e0a5607ee5c4346994261353476eed56cce5b953effbe720`，`[level property]` offset1092为 `[1,99,"魔法攻击力 : <int>%%",-1,0,1.0]`，地下城Lv1列0=1020。

这条链适合验证旧API别名、通用AttackInfo赋值、身体攻击框、ALS、帧flag、音频和震动的共同消费者。其技能ID只作为数据定位和验收样本，不能出现在执行分派条件中。

`sq_setAttackPowerWithPassive(skill,state,fixedColumn,percentColumn,scale)` 的参数归纳有跨技能源证据：Hedgehog/FastMove/Ripper/HighSpeedSlash/PowerOfDarkness/Disaster的第三参-1、第四参0或1，对应SKL百分比列；Execution第三参0/1/2/5/6、第四参-1，对应独立攻击列。-1表示不取该分量。**新资料未提供此setter完整原生签名**，所以这个映射标 `current1031-cross-skill-inference`，不是完整原生伤害公式。可执行推断允许进入demo，但应保留倍率/防御/TP/被动identity等策略。

## 优先扩展状态包、变量和callback

新增runtime词典39–42行确认：IntVectClear/Push写角色状态参数；AddSetStatePacket第三参true时读取该参数；GetVectorData从datas按索引取；get/setSkillSubState保存当前技能阶段。这里足够实现通用通道，阶段数字含义仍由源程序决定。

建议把 `datas` 表示为不可变state入参快照，`isResetTimer` 为该包的真实布尔值，`state`为当前源state编号；IntVect写入暂存和state请求一次提交。getter不能静态折0。same-state reentry必须重跑onSetState，按源重置动画/计时；动画结束、flag、输入回调必须绑定状态generation，切换后旧信号不能再落到新阶段。

`getVar()` 返回对象自身变量容器的引用；bool/int/float/vector/object/timer不同存储保留，不与全局编译器env混合。参数为名称时应区分不同变量域。写操作编译为VM操作，查询编译为运行表达式；动态分支赋值不可在编译时混成一个值。边界检查和失效EntityHandle不能省略。

callback按共同生命周期绑定：

- onProc：每模拟tick执行；onProcCon：同tick输入状态；不要绑定渲染帧率。
- onTimeEvent：定时器id/count，immediate、limit、回调停止与取消语义需显式实现；离场、死亡和中断清理。
- onEndState：在离开当前源state前执行，newState为目标源编号；不可无条件在每个substate变更时假造不同state。
- onAttack/onDamage：由真实接受命中事务触发，携带damager/boundingBox/isStuck；不在仅矩形接触或被拒伤害时假触发。
- prepareDraw：保留绘制消费者；确认为空可以编译为空，真实draw/FX调用不能静默略过。

helper函数以完整调用图和实参绑定通用编译，递归/循环设置预算。不能将所有非标准callback名一概视为执行入口，也不能跳过从callback可达的helper。`startSkillCoolTime_*`等返回值还可能由native host查询，不能仅因为它不在当前callback白名单就认为永远不可达。

## 动画/空间/PO组的后续收益和边界

新的runtime词典53、73–80、120–148、179行足以确定取施放时间、当前ANI/帧时间、创建PO、包宽度、移动坐标、视觉缩放等最低语义，但并不证明所有native算术和动态时序。

1. ANI句柄和 `GetFrameStartTime` 读取当前clip的原始毫秒和frame index；索引越界必须具体诊断。知识包IceRoad记录本体仅1帧却查询frame16，是已知不能随意clamp的例子。速度100是否原速需结合当前脚本和ANI rate consumer，不对所有API统一当1.0。
2. `getXPos/YPos/ZPos`、方向和输入是运行值。`GetDistancePos`必须保留方向符号与源距离；局部/世界坐标区分，不统一Z补偿。
3. PO的receiveData必须按writer/reader顺序与Byte/Word/Dword/Float宽度闭合；全局BinaryWriter和角色writer是API家族，确认包归属再复用。未知读写或剩余字节拒绝。
4. PO脚本往往有独立state/timer/onAttack/销毁行为，不能把完整PO简化成一个ANI寿命。缺这些消费者时主技能仍partial；独立program host可复用同一VM，而不是为每个PO写控制器。
5. 动态分支、数组索引、有限for及局部变量都需要真实解释。可先支持已界定上限的整型循环和数组，迭代预算耗尽为故障，并回滚/清理所属实体；不能在导出时删除循环或固定取第一条。

冰晶之浴、冰凌破、千里冰封的actor链比复杂抓取链短，可作为状态/取数/数值转换/PO家族的下一组验收样本。但只有所有可达callback、创建PO和依赖能力闭合后才增加executable计数。属性变换当前主体行为被源注释，魔力燃烧注册文件无函数，这两项不能靠允许空callback就标完整技能。

## 编译和宿主共同的完成门

编译器生成 `required_capabilities`，宿主声明并实证能力集合；两者一致才允许启动。sound/shake/appendage/粒子等只产生日志不等于实际消费。每项executable应同时绑定：精确注册、完整可达AST、源数据scope、资源闭包、PO子程序、宿主能力、实际按键释放、接受命中与反应、中断/死亡清理。

每新增API族，测试应覆盖两个或更多不同源形状或有意义的负例，例如大小写别名与未知拼写、GetLevelData的column≠level、普通/PVP重复段、typed packet宽度不匹配、flag与ANI end同tick切state、受击中断退出恢复、PO源回调出现未知操作时父技能拒绝。不得把人工IR样本通过当源编译器覆盖证明。

原生职业没有NUT注册仍是caller缺口。职业入口适配要恢复该职业的通用原生状态机/API语义；角色/动作/技能目录完整性与完整技能执行率分别报告。更多CHR动作能预览是有用交付，但不替代源技能调用链。
