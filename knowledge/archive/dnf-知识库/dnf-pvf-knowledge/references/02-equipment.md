# 装备修改 知识精华

> 提炼自 dnf-pvf-tutorial【02】装备修改（382 篇）：全部标题通读 + 系统整理型课程深读
> 60+ 篇，其余按目录聚类抽样验证。（源:编号）=课程编号，原文在
> `pvfCourse/【02】装备修改/` 下按编号检索（全量索引见 09-course-index.md）。

## 一、装备 PVF 文件结构与核心标签

**关键文件路径**
- 装备主文件：`equipment/character/…`（.equ）；装备文字（名称/描述/喊话）：
  `equipment/equipment.kor(.str)`；装备列表：`equipment/equipment.lst`（源:10280/10278）
- 套装列表：`etc/equipmentpartset.etc`；套装属性：`equipment/character/partset/*.equ`
  （源:10345/11654）
- 装备词典：`etc/itemdictionary/(r)itemdictionary.etc`（源:10363）
- 强化：`etc/upgrade(.etc)`；增幅：`etc/amplifyitem.etc`；锻造：`etc/upgrade_separate.etc`；
  服务器参数：`etc/serverparameter.etc`（源:10303/10364/11782/11550）
- 魔法封印：`etc/randomoption/*`（源:10108）

**头部结构（源:10347/10025/10343）**
```
[icon]      `Item/xxx.img` 49        // 图标：img路径+帧号
[field image] `Item/field_equip.img` 3  // 掉落地面图
[icon mark] `Item/IconMark.img` 45   // 边框
[name] <3::name_410642``>             // 名字引用 kor.str（``内可直接写文字）
[basic explain]/[detail explain]/[flavor text]  // 基本信息/F4详情/灰字
[name2]/[grade]/[durability]/[minimum level]/[weight]
```
- `[rarity]`：0白 1蓝 2紫 3粉 4史诗 5勇者（grade 影响强化伤害，填100强化无伤害，90有）
  （源:10026/10312）
- `[attach type]`：sealing封装 free无限制 trade不可交易 account账号绑定
  trade delete无法删除（源:10029）
- `[usable job]`：swordman/demonic swordman/gunner/atgunner/fighter/atfighter/mage/
  atmage/priest/thief/creator mage；`[routing priority]` 显示优先级（源:10026）
- `[creation rate] 500` 掉落权重；`[usable world] `[fair]`` 公平决斗场专用；
  `[possible kiri protect]` 可用强化/增幅保护券；`[need material] 3037 100` 兑换材料
  （源:10029/10343）
- `[impossible contents]`：disjoint分解 upgrade强化 amplify upgrade增幅 gift赠送
  separate upgrade锻造 charac cargo仓库（源:10040）
- `[equipment type] `[weapon]`` 22 + `[sub type]`；EQU指向性参数：1-25武器
  （1 ssword短剑 2 katana太刀 3 club钝器 4 lswd光剑 5 beamswd…）26-50防具外观
  （cl布/lt轻/la重/ha板/mt+coat/pants/shoulder/waist/shoes）51-58首饰左右槽
  （51 amulet 52 wrist 53 ring 57 support 58 magic stone）（源:10299）
- 外观系（源:10029/10343）：`[animation job] `[mage]``；`[variation] 1 4`（npk编号0104）；
  `[layer variation] 2790 `broomc`` + `[equipment ani script] `equipment/character/mage.lay``；
  图层优先级数值越小越靠前
- 时限：`[usable period] 3`（任意装备N天）；`[usable period after unsealing] 1`
  （解封后N天，仅封装装备）；`[expiration date] 1356966000`（Unix时间戳）（源:11592/10354）
- 隐藏（源:10137）：`[hide equipment] `[hat avatar]`…`；`[hide layer] 2880 2870 …`；
  `[hide grow avatar] `Soul Bringer Aura``（职业特征：鬼泣光环/红眼/香烟/念气光环等全职业枚举）
- 成长型武器（源:10312/10272）：
```
[level linear ability]
1 70
[grade] 5 71
[repair price] 6700 100000
[equipment physical attack] 103 65 1309 749
[separate attack] 56 32 401 272
[physical attack] 8 47
[/level linear ability]   // 第4、5行数据调大→面板高
```

## 二、装备属性代码对照（数值→含义）

**四维陷阱**（源:10027/10312）：`[physical attack]`=力量、`[physical defense]`=体力、
`[magical attack]`=智力、`[magical defense]`=精神。

**攻击面板**（源:10028）：`[equipment physical attack] 214 198`（最大值 最小值）、
`[equipment magical attack]`、`[equipment physical defense]`、`[equipment magical defense]`、
`[separate attack] 108 70`（独立）、`[anti evil]`（抗魔）。

**常用属性（源:11850/10346/10034-10039/10349/10353）**
- 速度类数值÷10=百分比：`[attack speed] 80`→8%（源:10347/11850/10039）
- `[stuck] -100`＝命中率100%（负数显示为正）；`[stuck resistance] 10`→回避1%（÷10）；
  `[hit recovery]`硬直；`[physical/magical critical hit] 5` 暴击率
- 属强：`[light/water/fire/dark attack]`；全属强 `[all elemental attack]`；
  属抗 `[light resistance]` 等；属性攻击 `[elemental property] '[fire element]'`
  （fire/dark/light/water）
- `[HP MAX]/[MP MAX]/[HP regen speed]/[MP regen speed]/[inventory limit]`
  （负重1000=1kg）；`[jump power]`；`[room list move speed rate] 0.1`=城镇移速+10%；
  三轴 `[x move dash speed] 0.50`
- 异常抗性：`[blind resistance]` 等12种 + `[all activestatus resistance]`（源:10346）
- 异常状态增益：`[active status control info] 'stone' 1 6 10000 40`＝石化几率+1%、
  等级+6、持续+10秒、伤害+40%（源:10038/11850）
- 绝对伤害系（源:11594/11850）：`[physical/magical absolute damage]`（强化后生效，
  替换原始强化数据）、`[physical/magical damage reduce]`（减伤）、
  `[physical/magical absolute defense] 20.0`（百分比绝对防御）、
  `[ignore defense] 1`（无视防御，需写描述）；
  `[limit upgradable level] `[all upgrade` 1 31`（强化/增幅/洗炼等级限制）
- 未明词条（源:11594）：`[HP drain]/[MP drain]/[human damage rate]/[fort damage rate]/
  [monster damage rate]`
- 伤害机制总表（源:11850）：增加伤害`[increase damage]`与暴伤`[increase critical damage]`
  不叠加取最高；力智百分率可叠加；白字`[add absolute damage]`可叠加；减防依次叠乘；
  削血`[weakness]`按当前血量比例（精英怪1/3、领主/深渊1/6）（源:10113）
- 状态枚举（源:10114/11850）：blind失明 lightning感电 burn灼伤 freeze冰冻 hold束缚
  sleep睡眠 bleeding出血 confuse混乱 curse诅咒 stone石化 stun眩晕 +
  weapon break/armor break + all activestatus/any
- `[active status]`参数结构（源:10114/10116）：`'haste' 40 16 16`（Lv/攻速%/移速%）；
  `'slow' 55 14 14`；`'bless' 22 13 13 13 13`（Lv/力/体/智/神）；
  `'burn' 60 750 35 1 2000`（Lv/总伤/周围伤/未知/间隔ms）；`'bleeding' 65 1500`；
  `'lightning' 30 105`；`'stone' 24 450`；`'curse' 62 45 45 45 45`；`'poison' 40 1800`
- APD/appendage 模块（源:10138-10146/12071）：apd是宏模块，装备用 `[appendage] 编号` 调用；
  类型 `skill data up`（`[string data]`：`'[swordman]' 174 '[all]' '[level]' 0 '%' 300`
  ＝鬼剑士174号技能第一参数增至300%）、`change status`（`[int data]`个数+[float data]数值，
  如 `equipment physical attack` +15）、`skill level`（`[int data] 0 27 9`＝职业0鬼剑士、
  技能27、+9级；职业ID按 character/character.lst）、`change weapon color`
  （`linear dodge white gray`，浅色加light暗色加dark）、`super armor`；
  ani调用路径 `pvf\appendage\animation`；装备侧触发 `[equipment duration] 60000` +
  `[appendage] 32`

## 三、触发条件枚举（源:11589）与触发内容枚举（源:11590）

**触发条件 [if] 清单**（源:11589/11850）
- `[attack success] 1` 攻击成功；`[hit] 1` 被攻击；`[attacker] 'character' -1` 近身攻击
- `[module] `[dungeon]``：dungeon普通 / dungeon type地下城类型 / tournament dungeon锦标赛 /
  dead tower死亡之塔 / war room战场 / blood system无尽的祭坛 / assault怪物攻城 / pvp竞技场
- `[target grade] 'common'`：common普通 champion精英 named深渊 boss领主
- `[target type] 'beast'`：beast兽 plant植物 insect昆虫 undead不死 devil恶魔 spirit精灵
  dragon龙 hybrid组合 human人型 machine机械 fort armor建筑 goblin哥布林 angel天使
- `[dungeon check] 1500 1501…` + `[target check] 'monster' 62121`（指定副本+指定怪物）
- `[combo] 10`（连击，需 `[after attack] 1`）；`[overkill] 1`（额外杀伤）；
  `[element] 'water'`（受到某属性攻击）；`[party death] 1`（队友死亡）；
  `[check damage] '%' 10`（单次受伤≥10%血）；`[use skill] 'demonic swordman' 180`
  （施放某技能）；`[casting] 1`（施放成功）；`[event use skill]`；
  `[target active status] 'bleeding'`（攻击异常状态敌人）；`[party count] '=' 1`
  （队友数，最大4）；`[attack condition] 'counter'`（counter破招/back attack背击/
  critical暴击）；`[any body equipped]…[indexes] 11534`（队友穿戴指定装备）；
  `[change status] 'hp' '>' '%' 0 'end'`（常驻判定）；`[my state]/[set my state] 'attack'`
  （自身状态）；`[my appendage] 205`；`[remove equip]`（卸装）；`[event attack success]`
- `[cooltime] 5000`（冷却ms）；`[time] 20000 1 0`（周期触发）；组合键：
  `[command] {6=`(UP)`}{8=`,`}…` + `[use command] 1`，
  键位 UP/DOWN/LEFT/RIGHT/CREATURE宠物键/ATTACK(X)/SKILL(Z)/BUFF(空格)
- **规则：if里写了[cooltime]，then里必须有持续时间；then不需要持续时间就删掉冷却**（源:11589）

**触发内容 [then] 清单**（源:11590/10100-10120/11850）
- `[target] 'myself' -1`：myself/enemy/enemy near/all enemy/party/party exclude self
  （数值=范围px，-1不限）
- `[probability] 30`（%几率，删掉或100=必发）；`[duration] 5000`；`[equipment duration]`
  （跟随装备）；`[then probability] 25`（配合 `[multiple then]` 多分支随机）；`[start cooltime]`
- `[stat] 'attack speed' '+' 30`；`[stat by condition] 'skill cool time' '%' -10`
  （全局CD-10%，不重复叠加）；`[add stat at once]`（野猪套式减CD）
- `[restore] 'hp' '%' 20`（20%血，第二参数0=立即）；`[consume item] 3037 1`；
  `[speech on] 0 2000 `台词``（语句写 kor.str 的 speech_）
- `[summon monster] 56123 -1 90000 1` / `[summon apc] 11128 …`
  （代码 等级-1跟随 时长 数量）
- `[buff] 'superarmor'`：superarmor霸体 unbreakable无敌 camoflage伪装
- `[elemental weapon] 'light'`（武器附光）；
  `[perform skill] 'fighter' 69 30 10`（施放技能：职业 技能 等级 数量——气功分身等）
- `[reduce probability to human armor at pvp module] 90`（PVP减几率）
- `[aura active] 'physical attack' '+' 45 300`（光环，直接写不用if/then；
  每件不能写太多、属性不能过高）
- `[stat change by stat] 'myself' -1 'dark resistance' 6 'dark attack' '+' 2 50`
  （每6暗抗→+2暗强，上限50）；`[stat]`不写CD会无限叠加，`[stat by condition]`不会
  （源:10103/10104）
- `[skill cooltime reset] 0 `` 1`（重置剩余CD最短的技能；剩60秒以上无效、决斗场无效）；
  `[end skill] 'priest' 119`（卸装解除魔化）
- `[add absolute damage] 'all' '%' 45`（附加白字，可选fire/light/dark/water/all）；
  `[increase damage] '%' 10`；`[increase critical damage] '%' 10`；`[weakness] 10`（削血10%）
- `[knockback] 1`（击退）；`[thorn] 30`（反伤30%）；`[add absolute defense percent] 'all' 50`
  （减伤50）
- `[replace avatar ani]`（变装/内衣：`'[coat avatar]' 106500008`，-1=隐藏部位）
- `[passive object] 48150 0 0 0 0 0 `` `（特效，见第四节）

## 四、攻击特效/装备特效代码大全

**[passive object] 参数**（源:10121/10098/10055）：
`特效编号 X Y Z 特效等级 出现方式 'ptl文件'`；出现方式 -1跟随人物 / 0正常 / 1流星落出场 /
3垂直出场；ptl 后可带 `Type:7 Str:587` 参数；坐标只有调用 ptl 才可用。

**四大触发模板**（源:10156/10312）
```
攻击直接触发: [if][set my state]1[my state]`attack`[cooltime]100[/if]
击中敌人触发: [if][cooltime]100[attack success]1[/if]
每秒自动触发: [if][time]1000 2 1000[/if] 或 [time]180000 1 5000
被攻击触发:   [if][cooltime]100[hit]1[/if]
```

**61篇特效系列（10156-10218）核心编号**（源:10157/10218/10312）：
剑舞20065`'Straight3.ptl'`；冰龙吐息48159；无头骑士幻影48190；火箭侠导弹48142；飓风48117；
里昂斧之怒48102；电力爆发48185；爆发念力48161；血之爆发48302；黑色火花48304；布鲁怨灵9104；
次元斩9385；火屏障48312/绿屏障(感电)48221/水屏障(冰冻)48222；魔法剑48214(满屏)/48213；
落雷48232；小落雷48506；炮击48537（可一行写6组坐标多方位）。
结尾篇列表（源:10218）：60024四叔`Satelaser.ptl`卫星射线；11133快速剑舞（无伤害）；
417/419/410阿甘左剑气（8888/400/500伤害）；60018闪电连；60021-60023黑属性雾/圈/技；
60025黑烟召唤；60027黑暗炼狱；60030-33落石；8022冻伤；8024/8025绿色念气波；8026球；
8617新风；8937哥布林；8125班图战士；8581秒杀追击者；30523小火爆炸；30524脚下小刀；
30526盗贼划刀；30528深渊柱子；30536石像炸弹；30544大毛雷浮空爆；30541/30542老鼠召唤等。
好看代码速查（源:10312）：60022自身暗黑六边形(暗属性伤害)；10491/10490紫色拔刀剑气(反向/正向)；
10497/10498拔刀剑气；11010御剑之魂剑气；48214满屏魔法剑。

**78种火焰特效（源:10267）**，格式 `[passive object] xxxxx 0 0 0 85 0 Type:7 Str:587`：
9007/10459紫黑火球；50755/50756燃烧瓶黑油；9350/35066烧尸火；
地上燃烧8176/9213/9315/9922/9923/40001/40003/40006/48178/30403/30046…；
9436陨石墙；51331/8677/8679…火条；48311/48251/11157时空门火(11157有吸附力)；
23016/25201/48088/8557/9899无形伤害；8089/48121/48122/10026巨大陨石爆炸；
9437/9859/10322陨石爆炸；11243/24212/24213/11123/11247/48231喷火柱；8211炽白小火球；
8085/8996/8869光炎剑火球(前2带追踪)；火焰爆炸1070/22213/22218/48077/48146…；
8175火焰大爆炸；23071/25207紫焰爆炸；2302冰焰爆炸；10042/10043火焰地带；
11188/11187/11183/11189火地带系列；13024/24290/48312/48524火焰罩；48105/8078/8094大型喷火；
60038火龙吐息；60039/60040喷冰；8723黑炎；8720/16053/16031…黑炎系；16054追踪黑炎；
48224/11209火球爆火圈；24203/24208…(需ptl)小火球；24291大火圈；8086火箭；8090火精灵自爆；
8214石头堆；8694小光柱；8770天上炸弹；8885黄球爆炸；9858旋转陨石；9883陨石之火；
9884人影爆炸；10041火焰箭头；10160环绕火球；10687蓝火地带；11164冰霜地带；
11197追踪火魔法阵；46003光之城主激光；20024爆炎波动剑。
持续触发配方（源:10267）：`[if][change status] 'hp' '>' '%' 0 'end' [cool time] 10[/if]`
（注意此帖写 `[cool time]` 带空格）——"连着触发直到怪物死"，慎选特效防卡死。

**49篇装备特效成品代码（源:10219-10266）**：每篇含完整可粘贴配方，代表：
- 出血：`[attacker] 'character' -1 + [active status] 'bleeding' 84 500`
  （近身3%几率，1秒，每0.5秒500攻击力）
- 附加30%白字：`[add absolute damage] 'all' '%' 30`；暴伤+20%：
  `[increase critical damage] '%' 20`；Y轴移速+50%
- 属性强化+10（10秒）：`[appendage] 19/20/21/22`（四属强apd）
- 附加1200伤害；减敌30%HP；驱散buff；[疾影手]CD-50%；冰霜萨亚范围+30px；
  物暴+20%魔暴+10%（10%几率）；全员伪装；召唤Lv50邪龙牺牲者/Lv55精灵系；
  死亡时火焰爆炸；施放10%霸体；反伤10%（`[thorn]`）；
  消耗无色触发系列（`[consume item]`+特效/增益）

**28篇"使敌人/自己/队员"配方模板（源:11952-11979）**：统一结构＝`[basic explain]`+
`[detail explain]`+`[if][cooltime]+触发[/if]`+`[then][target][duration][probability]
[active status/buff/knockback][/then]`。覆盖：减速`'slow' 25 10 10`、失明`'blind' 74 90 20`、
诅咒、感电、石化、眩晕、破甲、中毒`'poison' 40 1500`、混乱、灼烧、睡眠、冰冻、随机异常、
驱散buff、防御减少、属抗减少、耐久减少、回HP/MP、四维、三速暴击、祝福、霸体、伪装、无敌、
减伤、队员三攻、击退`[knockback] 1`。

**appendage 霸体/增伤模板（源:10312）**：`[appendage] 205/207`＝霸体
（施放5%/被击10%/攻击3%）；`[my appendage] 205`+攻击成功→
`[add absolute damage] 'all' '%' 20`（霸体时增伤）。
自然恩赐巨剑配方：`[multiple then]`四分支25%各附 fire/water/light/dark +
`[elemental weapon]` + appendage 142-145，再用 `[my appendage]` 联动
burn/freeze/lightning/blind。

## 五、套装 / 异界 / 魔法封印 / 传承残影

**套装写法一（分散式，源:11793/10345/11654）**：每件写 `[part set index] 180101` →
`etc/equipmentpartset.etc`：`[equipment part set] 180101 `character/partset2/180101.equ`
`名称` `[coat]` 2 0 …`（部位枚举：amulet/wrist/ring、coat/pants/shoulder/waist/shoes、
weapon、title、support/agic stone、hat/hair/face/breast/coat/pants/waist/shoes/skin/
aurora avatar、creature、artifact blue/green/red；最后数字=图层优先级0普通1高级时装2稀有…）
→ 属性文件：`[piece set ability] 3`（3件触发）+属性+[parameter basic explain]。
**写法二（集中式，源:11793/10345）**：主件写 `[set item master] 代码` + `[set name]` +
`[set item] 各件代码` + `[set ability]`（内可放全部属性与if/then触发）。
**套装技能+1**：`[set ability]`内放 `[skill levelup] `[swordman]` 82 1 …`（源:10359）。

**异界套**（源:10274/10281/10150/10270）：远二2choroset*/远三3choroset*，
属性文件在 `equipment/character/partset/`；把 `[piece set ability]` 后的 3/6/9 改成
1/2/3 即 1/2/3件触发全套（工具改int即可）；删除后续 `[skill data up]…[/skill data up]`
分段可并段；缺陷：`[parameter basic explain]` 的 [@09] 行数改动会导致描述错乱。

**异界气息**（源:10344/12065/10308）：可打气息部位
`[character item check] 职业 部位 `weapon``（职业0鬼剑/1格斗/2枪/3女法/4圣职/5女枪/
6暗夜/7男格斗/8男法×等级1-4；防具/首饰把 weapon 换 shoulder/amulet/wrist/ring）；
气息属性在 `consumption_1254/1255/1256.stk`，
`[skill] `[swordman]` 108 [dungeon type] [level] 0 '%' 12`＝鬼剑士第108技能+12%，
可改任意技能与数值；散件附魔成功率：stk里 11→100 即100%成功（源:10308）。

**魔法封印**（源:10367/11797/11862/10107/10108）
- 开关：装备写 `[random option] 1` + `[Force Result Item Rule] 1 0`
- 数值文件：`etc/randomoption/options/randomoptions_15_physicalattack.etc`：
  `[level] 1 [physical attack] 8 45`（8=最低45=最高，写一样则全级别同值）
- 名称：`randomizedoptionoverall2.etc` `[postfix] 41`[失明 : C]``（41=数值文件编号）；
  权重/金币：`[break seal cost]`、`[option modification] 1 50 100`、
  `[postfix grade modification]`（品级 C/B/A/S 权重，数值大几率大）
- 属性随机：`optiongrouping.etc`（`[option group] 6011401000000`＝项目601+文件140+
  权重1000000）；`optiongroupselection.etc`（装备项目分组）；数量：`optionquantity.etc`
  （如SS必3属、粉必2属：第5/6栏写3-3/2-2）
- 署名与目录：`auctionrandomcategory.etc`（`41570100140`=4种类目+15武器/70防具/100首饰/
  140特殊装备的文件编号）、`randomoption.lst`
- 新增封印装备9步：装备加[random option]→建属性文件→lst编号→auction署名→
  optiongrouping建组→optiongroupselection写项目名（`4 -1 `club` 1 60 3 201 202 203 0 0 300`）
  →optionquantity写数量→partselection写等级+项目→overall1/2写金钱与品级

**传承残影**（源:10271/10362）：`[spectrum] 255 0 0 200 500`（前3位RGB取色器数值，
后2位间隔/残留）；时装/皮肤用 `[spectrum avatar] 255 255 255 120 500 0`；
人物拼合在武器上残影会覆盖全身。

## 六、强化/增幅/锻造相关

**强化 etc/upgrade(.etc)**（源:10303/11900/12074）：每级行5段＝
`成功率X 模式 掉级数 材料ID 材料数量`；成功率=(100000-X)/100000；
模式1维持/2降级/3损坏（②③组合决定失败行为）；3037=无色小晶块。
品级强化权重 `[drop upgrade rarity]`（common/uncommon/rare…各等级数值）；
金币权重行在上方；成功率建议改10000左右保持低级几率（源:10303）。
**强化/增幅100%**（源:11806）：`[upgrade prob increase] 5000000`
（称号凯丽的最爱26699/破碎的心26698）；`[amplify upgrade prob increase] 5000000`
（赫尔德春节版400990169/一决胜负400330110）。
**装备自带强化几率**：`[upgrade prob increase] 1000`（原版约=1%，源:10042）。
**增幅**（源:10364/11785）：`etc/amplifyitem.etc` `[equip level const] 55`（限制等级）；
`[rarity weight]` 各品级增幅加成（改epic 1.6→数值更高，实测只改这里即可）；
`etc/upgrade.etc` 的 `[upgrade failed bonus weight by rarity]` 为冗余第二路径。
**增幅保护**（源:11529/11550/10348）：`etc/serverparameter.etc`
`[protect of upgrade down] 保护券代码 保护最低 保护最高 失效掉级数`
（如 `8239 4 11 0`；`20181267 12 17 0`）；`[get reward count] 24 70/90` 保护装备等级；
保护卷文件 `stackable/event/tcg/event_8240.stk`（12~14），
卷内 `[equipment reinforcement ticket] 10 15` 强化、`[equipment amplify reinforcement ticket] 12 10`
增幅、`[check usable itemlevel] 1 40` 限制等级；武器必须写 `[possible kiri protect]`。
**强化增幅速度**（源:10368）：`etc/upgrade.etc`
`[upgrade machine frame base time] 4000 100 300 1500`→改 `1000 100 300 500`。
**锻造 etc/upgrade_separate.etc**（源:10305/11782）：`[separate upgrade max]`上限≤30
（31成功后归零）；`[table]`每组ABCD：锻造值=锻造基数×A/2、成功率=C/10000、D=材料系数；
`[level]`决定锻造基数（越小基数越大）；`[item weights by grade]`每组EFG：
装备grade/材料代码/材料基数，消耗=基数×稀有度系数×D；
`[separate upgrade effect]`外观颜色渐变（6个一组，需≥上限-1组）。
**还原蓝白装+8破坏**（源:12048）：`etc/upgrade.etc [destroy level by rarity] `[common]`
`[uncommon]`` 10改8。
**掉落爆率**（源:10300）：`tc/itemdropinfo_clearreward.etc`翻牌、
`etc/itemdropinfo_monseter(.extra/_hell).etc`白图/深渊；
`[basis of rarity dicision] 800000 989900 999900 1000000 1000001 1000002`
＝随机数区间判品级（白/蓝/紫/粉/史诗）；1:1:1:1:1 即 `200000 400000 600000 800000
1000001 1000002`。

## 七、典型修改配方（要实现X→改哪→加什么）

1. **加触发特效**：Decrypt解包→找到装备.equ→删除原`[if]…[/then]`→粘贴第四节模板→
   每行末尾留一个空格、`[/if]`与`[then]`之间空行→写回pvf；文字改 kor.str
   （源:10275/10280）
2. **加技能等级**：`[skill levelup] '[priest]' 35 2`；技能编号在 `skill/priestskill.lst`
   按英文名搜（幻影化身=Shadow Boxer→35），插在`[icon]`之前（源:10278/10352）
3. **全技能+1（1-70）**：`[all skill item]`＋`[skill apply condition]`
   （group [all]、lower 1、upper 70、value 1、`'[except for ex skill]'`）＋
   `[skill phase] '[all]'`（源:10312/10044）
4. **特定技能数据**：`[skill data up] '[swordman]' 21 '[dungeon type]' '[level]' 3 '%' 18`
   （职业/技能编号/地图模块/属性模块[static|level|cooltime|mp|maintain mp]/序号/运算符/数值）
   （源:10349/10046-10050）
5. **减全局CD**：`[stat by condition] 'skill cool time' '%' -10`；100%CD：`'%' -100`
   （源:10307/10360/11814）。七类CD叠乘公式：
   真实CD=(原始-第五类)×(1-一类-二类-三类-七类)×(1-四类)×(1-六类)；
   同类词条覆盖不叠加（防具覆盖宠物装备）（源:11814/11949）
6. **随机四属性附魔**：`[start cooltime] 30000`+`[multiple then]`四分支25%→
   `[elemental weapon]`+appendage 600-603，再用`[my appendage] 600…`联动
   `[add absolute damage] 'water' '%' 12`与属强属抗（源:10366）
7. **副职业词条**：`[expertjob only] 'disjointer' 9`＋`[prof disjoint result variation] 10`
   （分解+10%）/`[prof result variation] 5 200`（炼金/控偶5%双倍）/
   `[prof compound rate] 5`（炼金成功率）/`[prof additional gain exp] 10 1`（分解经验）/
   `[prof material variation] -10`（附魔省料）；职业码
   disjointer/alchemist/enchanter/doll_controller（源:10051-10054/10351/11600-11607）
8. **指定副本触发**：`[if][dungeon check] 101 102 103 104[/dungeon check]…`，
   **必须写在套装属性上，单件会BUG**（源:10365/11905/11906）
9. **称号簿**：`etc/titlebook` 直接加 `[all activestatus resistance] '+' 1888`；
   时限 `[usable period]`/`[expiration date] Unix时间戳`（源:10304/10354）
10. **领主粉**：词典文件（代码 品级5或神器 最小/最大等级 分类代码…）＋
    `etc/independent_drop.etc`独立掉落＋
    `etc/itemdictionary/(r)independentdropinfo.etc`（[item table]+[monster table]
    怪物列表按行号引用）＋`dungeon_name.etc`副本提示（源:11595）
11. **骨戒破招+50%物攻修复**：`[attack type] 'physical'`+`[attack condition] 'counter'`+
    `[appendage] 334`→`[my appendage] 334`→`[stat] 'equipment physical attack' '%' 50`
    （源:11994）
12. **防具精通百分比对技能**：改技能文件 `[static data]` 静态数值（源:11880）
13. **攻击换装/变装**：`[use command] 1`+`[replace avatar ani]`（部位+时装编号），
    可配喊话+特效+消耗品（源:10358/10105）
14. **触发喊话**：`[speech on] 0 2000 `台词``；台词加在 equipment.kor 的 speech_ 段
    （源:10356/10100）
15. **地图/城镇挂特效**：equ内 `[particle] `same position`
    `Character/Common/Particle/rare5.ptl` 0 0 100`；ani跟随用
    `[effect] [type] animation [attach pos] top [index] 1 [file name] …ani`
    （[index] -1身后/1身前）（源:11903）
16. **武器四属性共存**：rareset.equ稀有装扮套/称号/宝珠/契约各附一属，
    或攻击时100%赋予属性攻击（源:10295）
17. **DIY神器思路**（源:10268）：无敌霸体抄无轩系列、附属性用"攻击100%赋予"不冲突、
    全技能提升抄百战老将、削血抄裂创、范围异常抄天霜。

## 八、常见坑

1. **每行命令末尾必须有一个空格**，否则出错；`[/if]`与`[then]`之间即使无参数也要空一行；
   一次if只对应一次then（源:10275/10280）
2. **PVF中间某段写错→其后全部代码不生效**（独立掉落末尾不生效多半是中间写错）（源:10348）
3. 减CD同值**不叠加是覆盖**；100%与5%同戴只生效5%（有优先级），想叠加用进图buff式词条
   （源:11949/11814）
4. if里写`[cooltime]`则then必须有持续时间（源:11589）
5. `[grade]`填100强化无伤害，90有效（源:10312）
6. 词典参数：NPC/罐子即使没有也要补0，任务无则只写一个0（源:10363）
7. 异界套改件数后 `[parameter basic explain]` 行数（[@09]）改错会显示乱码；
   多段描述引用只显示一段（源:10274）
8. 打气息部位词：weapon/shoulder/amulet/wrist/ring（源:12065）
9. 魔法封印改名全S级只是文字，实际数值UI不变，须每个类别都改（源:10367）
10. 增幅不受保护：缺`[possible kiri protect]`、中间写法错、或保护卷只保护+13以上（源:10348）
11. 锻造31级成功后归零→上限设30（源:10305）
12. 领主粉品级必须神器/领主神器才显示；词典与副本UI品级不一致会串类，
    可在冷门职业词典塞第二份（源:11595）
13. 速度类数值÷10；城镇移速0.1=10%（源:10039）
14. `[aura active]`每件不能写太多、属性不能过高；被击出气功分身并非每技能可用（源:11590）
15. 落雷/布鲁等强特效冷却要调高否则卡顿/卡死；连发特效慎选防卡死（源:10312/10267）
16. 武器装扮不显示强化特效→调低图层优先级（武器651→装扮650），过低会被时装挡（源:11591）
17. 没有装备描述的老装备别自己加描述项会出错；尽量挑有描述的改（源:10280）

## 九、深读课程索引

- **系统整理型**：11850装备属性（伤害机制+全词条）、11589触发条件、11590触发内容、
  10363装备词典、11873装备词典更改模板、11814减CD七类整理、11594无视防御/绝对伤害、
  10347装备所有标签、10312装备属性整理（最全配方合集）、10343装备基础属性、
  10346装备基础词条、10025-10030基础组成、10121/10055/10098特效说明
- **特效大全**：10156前言+10157-10218（61种）、10219-10266（49种成品）、10267（78种火焰）、
  11952-11979（28种标准配方）、10088-10095攻击相关、10110-10120触发内容分类
- **套装/异界/封印**：10345/10359/11654/11793套装、10150/10270/10274/10281/10344/12065/10308异界、
  10367/11797/11862/10107/10108魔法封印、10271/10362残影
- **强化增幅锻造**：10303/10305/11782/11785/11806/11900/12048/10348/10364/10368/11529/11550/
  12074/10300/10042
- **技能/副职/其他**：10349/10352/12071/10138-10146 appendage、10043-10050技能、
  10051-10054/10351/11600-11607副职、10137隐藏、11592时限、10365/11905/11906副本、
  11595领主粉、11994骨戒、11880防具精通、10272成长武器、10268DIY思路、10299/10350 EQU参数、
  10304/10354称号、10278/10275/10280实操流程、11903特效挂载
