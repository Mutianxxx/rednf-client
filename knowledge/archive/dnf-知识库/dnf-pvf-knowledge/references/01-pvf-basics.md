# 基础·杂项·模板 知识精华

> 提炼自 dnf-pvf-tutorial【01】PVF文件解读(16) +【16】常用模板(28) +【17】自学模式(2) +
> 【13】obj(7) +【11】其他杂项(88)，共 141 篇全部读完（含 3 篇空壳/网盘链接课已标注）。
> （源:编号）=课程编号（全量索引见 09-course-index.md）。

## 一、PVF 核心概念与文件体系

- **Script.pvf 是游戏灵魂**，客户端与服务端都读取校验：服务端管数据库相关
  （购买扣D点/金币、商城价格在pvf里）；客户端存动画/图片/声音路径，
  路径缺失→红叉甚至闪退（源:10017）。
- **修改总流程**：Decrypt解压pvf → Notepad++查找修改 → 工具写回 →
  服务端+客户端同时替换 → 服务端 ./run 跑五国（CN/HK/KR/MO/TW）→
  出现Time字样可登录（源:10016、11899）。
  服务端替换必须用**未加密pvf**，用客户端加密pvf替换服务端跑不出五国（源:12019）。
  测试技巧：建1级小号发邮件自测，点开邮件瞬间未响应=代码写错（源:10016）。
- **目录中文翻译**：aicharacter=APC人偶、appendage=附加状态(APD)、aura=光环、
  cashshop=商城、character=角色含副职业、chatemoticon=聊天表情、clientonly=客户端专用、
  common=通用调用(地图传送)、creature=宠物、data=技能/UI数据、dungeon=地下城、
  equipment=装备、etc=配置(商城/爆率)、event=活动、itemshop=NPC商店、map=地图、
  monster=怪物、n_quest=任务、passiveobject=被动对象、region=区域(阿拉德/天界/素喃)、
  skill=技能、sqr=脚本、stackable=可堆叠消耗品、town=城镇、ui=界面、
  worldmap=世界地图（源:10013、10017）。
- **文件类型**：.lst=列表索引（物品代码→文件路径，新增物品必须登记）；
  .kor.str=语言文字文件（国服是.chn.str），改文字都在这里；
  每个文件夹基本都有.lst+.kor.str；有哪些kor.str看 n_string.lst。
  物品分两类：可穿戴 /equipment、不可穿戴 /stackable（源:10017、10015）。
- **查找装备**：equipment.kor.str搜名字（繁体）→物品代码→equipment.lst搜代码→路径，
  如 28265 'character/swordman/weapon/beamsword/n_beamswd_hellohella.equ'（源:10016）。
- **装备字段**：name物品名、name2代码名(不改)、basic explain基础描述、
  detail explain详细描述、flavor text灰字(不能自行添加)、grade掉落区域等级、
  稀有度3粉/4橙/5勇者；物攻魔攻"高的写前面低的在后"，独立攻击写法相同；
  stuck -12=命中率+12（写12=命中率-12）；速度类写40实际+4（实际=数值/10）（源:10016）。
- **map目录**：map下每个文件夹=一个副本；map后缀=小格地图；
  E=easy H=hard N=normal B=boss S=star，S为进本第一张图B为BOSS图；
  怪物段 251=怪物代码，normal可改BOSS（源:10011）。
- **APC(aicharacter)**：一文件夹一APC，28.aic第二行=人偶等级；
  含攻速/技能代码/发呆时间(200=2秒)/好战度/视野等（源:10004）。
- **暴击公式**：暴击伤害=非暴击最终伤害×[150%×(1+装备爆伤)×(1+防具精通爆伤总和)×
  (1+爆伤BUFF)+加算类爆伤BUFF]；系统暴击基数1.5倍；
  多件爆伤装备只取最高（源:10003）。
- **四围特殊映射**（卡片/装备/APD通用）：力量=[physical attack]、智力=[magical attack]、
  体力=[physical defense]、精神=[magical defense]（源:10394、10406、11583）。
- **PVF参数对照**：[weight]重量(千分位)、[inventory limit]负重(/1000)、
  [stuck]命中(负数)、[stuck resistance]回避(/10)、[hit recovery]僵直、[jump power]跳跃、
  [move/attack/cast speed]速度(/10)、[HP/MP MAX]、[HP/MP regen speed]每分钟恢复、
  [physical/magical critical hit]暴击、[upgrade prob increase]强化成功率、
  [upgrade cost discount]强化费折扣、[room list move speed rate]城镇移速（源:10020）。
- **面板中英**：力量#Strength 智力#Intelligence 体力#Vitality 精神#Spirit；
  独立#Base Attack Strength；抗魔#Exorcism；属强#Fire/Water/Light/Shodow Dmg；
  属抗#* Resist（源:10021）。

## 二、常用文件路径速查

**kor.str文字文件**（源:10014）：event/event.kor.str流动广告；equipment.kor.str物品名；
npc/npc.kor.str人物名；etc.kor.str物品活动介绍；aicharacter.kor.str人物对话；
character.kor.str职业介绍；creature.kor.str宠物；dungeon.kor.str地点；
itemshop.kor.str商店对话；monster.kor.str怪物信息；quest.kor.str转职觉醒对话；
passiveobject.kor.str技能信息；mission.kor.str PK场；skill.kor.str技能介绍；
stackable.kor.str物品技能介绍；ui.kor.str活动商城。

**etc核心文件**：

| 路径 | 用途（源） |
|---|---|
| etc/accountcargo.etc | 账号金库（源:10022/11536） |
| etc/pvpchannellist.etc | PK频道段位/等级限制（源:11462） |
| etc/channel_info.etc+etc.kor.str | 频道名称（源:11463） |
| etc/upgrade.etc | 强化/增幅/无视攻击6数值（源:12018/12000） |
| etc/upgrade_separate.etc | 锻造（[separate upgrade max]上限7，拍卖行输入127）（源:11523/11933） |
| etc/amplifyupgrade.etc+chronicle.etc | 高级强化机（源:12000） |
| etc/goldlimitbylevel.etc | 金币上限，2数字一组=等级/上限（源:11548） |
| etc/itemdictionary/(r)itemdictionary.etc | 装备词典（源:11466） |
| etc/independent_drop.etc+independentdropinfo.etc+dungeon_name.etc | 领主粉独立掉落三件套（源:11716） |
| etc/worlddrop.etc | 世界掉落（源:11467） |
| etc/itemdropinfo_clearreward.etc | 翻牌爆率[basis of rarity dicision]（源:11804/11524） |
| etc/itemdropinfo_monster_hell.etc | 深渊怪物爆率（源:11804） |
| etc/worlddroppcroom(.2).etc | 黑钻掉落（源:11524） |
| etc/serverparameter.etc | [drop upgrade rarity]掉落随机强化(品质 等级 权重)、[light server no]（源:12035/11932） |
| etc/ranksysteminfo.etc | [rank grade]评分 99 97 95…（源:12037） |
| etc/disjoint.etc | 系统分解机（源:11818） |
| etc/chn_server_limititemusageinfo.etc | 每日发放/重置[refill item]（源:11800） |
| etc/etcparameter.etc | [skill damage base parameter dungeon/pvp]100级独立变0修复（源:11801） |
| etc/skillpreload.etc | 技能预读防卡顿（源:11816） |
| etc/premiumlist_new.etc+premiumserviceeffect.etc+newcashshop.etc | 契约三件套（源:11535） |
| etc/linksystem/characlinksystem.etc / charactermanage.etc / striker.etc | 冒险团加成/冒险团/支援兵（源:10023/10024/11980） |
| etc/titlebook.etc | 称号簿+心情发放（源:11538/12036） |
| etc/tw_deleteinvaliditem.etc | 骨戒回收[delete item]（源:11467） |
| etc/secretshop.etc / compoundavatar.etc / randomoption / hellparty.etc / amplifyitem.etc / equipmenteffectset.etc / chn_equipmentsockettypelist.etc(徽章) / emotionexpressiondata.etc(心情) / questshop.etc(QP) / sptable.etc(SP) / equipmentpartset.etc(套装) | 见11523书签课 |
| etc/parameter | 独立攻击（慎改，可能技能伤害无效）（源:11817） |

**其他**：character/exptable.tbl经验表(≤21亿)；
character/character.lst角色参数(新职业加 11 'Knight/Knight.chr')；
character/character.kor.str转职觉醒二觉副职名；
character/expertjob/disjointer.exj分解师；stackable/monstercard宝珠；
equipment/character/partset/rareset.equ天空套属性；
event/levelupreward.evt升级邮件；n_quest/job/cc_start.qst转职任务；
dungeon/towers/towerofillusion.dgn迷惘之塔；
ui/optionwindow/optionsystem.ui扩展技能栏；
ui/common/randomimagelist.ui+randomimagewindow.ui登录公告框；
event/event.kor.str+eventlistwindow+eventnotice滚动广告。
服务端：/home/dxf/game/cfg/cainXX.cfg频道、/home/dxf/game/cfg_siroco原始频道端口、
/home/neople/auction/iteminfo.dat拍卖行上架（源:11461、12006、11467、11468）。

## 三、附魔与宝珠

- **卡片可附魔位置**：[weapon]武器 [coat]上衣 [pants]下装 [shoulder]头肩 [waist]腰带
  [shoes]鞋子 [amulet]项链 [wrist]手镯 [ring]戒指 [support]辅助装备 [title name]称号
  [magic stone]魔法石（位置表见卡片[string data]）
  （源:10406；10394称未找到魔法石附魔法）。
- **附魔写法**（源:10406）：
```
[enchant]
	[equipment physical attack]
		 5 5
	//两个值=范围，写成一样防BUG；力量写[physical attack]、智力[magical attack]、
	//体力[magical defense]可并列双写、独立[separate attack]、全属强[all elemental attack]、
	//全属抗[all elemental resistance]、跳跃[jump power]、移速[move speed]、攻速[attack speed]、僵直[rigidity]
[/enchant]
```
- **卡片属性速查**（源:10394）：物暴/魔暴[physical/magical critical hit]数值=百分比；
  攻速释放=千分比(30=3%)；[stuck]命中率负值；
  武器属攻[elemental property]+[fire/dark/light/water element]；属强[fire attack]等；
  全职业加技能：
```
[skill levelup]
	[all]	186	6
	//职业 技能ID 提升级数；[all]=全职业，例186物理暴击+6级
[/skill levelup]
```
- **触发型附魔**（源:10406）：[enchant]内直接写
  [if][cooltime]90000[attack success]1[/if][then][target]`myself` -1
  [equipment duration]30000 [probability]1
  [active status]`bless` 1 300 300 300 300 [/then]，配[stat desc]写蓝字描述。
- **侍魂宝珠（附魔加技能参数）**（源:10408）：宝珠文件+卡片文件+APD文件三件套；
  卡片触发APD：
```
[enchant]
[if]
[change status]
`hp`
`>`
`%`
0 `end`
[/if]
[then]
[target]
`myself`
-1
[appendage]
51
//APD编号
[/then]
[/enchant]
```
  APD文件：#PVF_File [type]`skill data up` [duration]20000 [buff]0 [icon image]`` 0
  [max overlap]1(最大叠加次数) [string data]技能提升参数[/string data]；
  新APD必须登记列表并查代码重复。
- **PVP限属性宝珠**（源:10357）：[pvp] [HP MAX]100000 [MP MAX]100000 [attack speed]100
  [move speed]100 [cast speed]100 [equipment physical defense]20000 20000
  [equipment magical defense]20000 20000 [/pvp]。
- **经典附魂数值**（源:10378）：物攻宝珠5~45(魂·虫王戮蛊45,武器上下衣)；魔攻5~25；
  力量4~38 智力4~65(魂·纳扎罗65上衣)；四属强首饰3~20(魂·牛头械王火20)；
  武器属攻四系(烈焰彼诺修火/光之城主光/狄瑞吉暗/年轻时斯卡萨冰)；
  物暴头肩2~10%(魂·长枪麦斯10)；移速鞋0.9%(犬人哈多)；独立首饰11/23；
  称号珠：史莱姆王僵直硬直+20、泽忒斯物魔攻+7、卡姆拉HP/MP+105、阿加雷斯力智+15。

## 四、obj 被动对象 / 频道整合

- **obj三层结构**（源:12059）：obj（[name]名字、[pass type]`[pass all]`可穿行/
  `do not pass`门禁、[layer]图层、[piercing power]穿刺力、[basic action]调act、
  [attack info]调atk、[object destroy condition]`[on end of animation]`播完销毁）→
  act（[MOTION][BASE ANI]调ani）→ atk（[damage bonus]伤害%、[attack type][magic]/[physical]、
  [weapon damage apply]1吃武器、[attack enemy]1（[attack friend]无视敌我/
  [attack myself]打自己）、[elemental property]属攻、[push aside]击退、[lift up]浮空、
  [hit wav]音效）。ani无[ATTACK BOX]则无伤害判定。装备触发obj：
```
[if]
	[attack success]
		1
[/if]
[then]
	[target]
		`enemy`	-1
	[probability]
		100
	[passive object]
		35881	0	0	0	99	-1	``
	[/passive object]
[/then]
```
  obj需登记列表：35881 `tq_obj/tq_obj.obj`。
- **act条件对象[TRIGGER]**（源:11612、11614、12086）：[LIMIT]次数(0无限)、
  [CHECK TIME]毫秒、[FRAME]起止帧、[ON DAMAGE]被击、[ON ATTACKSUCCESS]攻击成功、
  [ON CREATE/DESTROY OBJECT]、[IF]变量[/IF]；
  [WHICH]目标：[ME][PLAYER][SUMMON MASTER][TARGET][LAST ATTACKER][ALL ENEMY]
  [ALL OUR TEAM][CHARACTER][MONSTER][PASSIVE]等；
  行为[BEHAVIOR]：[RESTORE][HP]回血（如被水属性攻击回血：[ON DAMAGE]+[IS WATER DAMAGE]）、
  [VIRTUALHP APPENDAGE] 699 99999999 2 10（血量≤阈值触发699连击破防）、
  [COLOR CHANGE EFFECT]变大小。
- **变大/缩小**（源:11775、12060、11984）：自带变大obj=16047（改atk为[attack myself]
  打自己变大）；自写obj：[BEHAVIOR][COLOR CHANGE EFFECT][CHANGE SIZE START]100
  [CHANGE SIZE END]200/800 [CHANGE TIME]2000 [LIFE TIME]0(无限)[/COLOR CHANGE EFFECT]；
  角色调用[WHICH][SUMMON MASTER]支持继承；缩小END写50。
- **常用obj特效代码**（源:11611）：21090倒地无伤害、21062击飞、21099念气罩、
  22262火焰爆炸、20111激光炮、22228盖波加之拳、23025黑洞多段、24013闪电、
  20041嗜魂封魔斩、30567剑阵、48238空投秒怪、48800吸怪、48225喷火器、48517回血、
  8580核弹秒杀(8607弱化1w)、9419高伤阵法、48200恶魔之手束缚、9179血球回血、
  8614跟踪导弹。
- **APD七种用途**（源:11583、11584）：
  ①[type]`skill data up`：[string data]`` `[swordman]` `174` `[all]` `[level]` `0` `%` `300` ``
  （职业 技能号 场景 参数 值 运算 值；场景[all]/[dungeon]/[tournament dungeon]/
  [dead tower]/[war room]/[blood system]；MP消耗`` `[mp]` `100` `+` `100` ``）
  ②[type]`change status`：[string data]属性名+[int data]参数个数+[float data]数值
  （属性攻击与三增益不加浮点）
  ③外观[effect animation]'../animation/xxx.ani'（APD的ani在pvf\appendage\animation）
  ④[type]`change weapon color`：[string data]`linear dodge` `white` `gray`
  （颜色light/dark前缀）
  ⑤[type]`skill level`：[int data]追加值 技能编号 职业编号
  ⑥[type]`super armor`/`unbreakable`/`camoflage`霸体无敌伪装
  ⑦减CD：[type]`change status` [duration]0 [string data]`skill cool time` [int data]1
  [float data]10.0。
- **频道cfg**（服务端cfg，非pvf）（源:11644、11457）：channel_no=频道编号、
  channel_name=ch.11显示名、tcp_port/udp_port、max_user_num=分流人数、
  fatigue_time=06疲劳重置、server_group=大区(3=希洛克)、script_dir=./Script/。
  开新频道（源:11461）：从/home/dxf/game/cfg_siroco/sirocoXX复制正确端口覆盖cain文件头部
  （gc_no/channel_no/channel_name/ip/tcp_port/udp_port须对应），底部Service group改3，
  run文件加 `sleep X` + `./df_game_r cainXX start &`；每开一频道多跑一次五国；
  可开频道编号有限制（源:11456）。
- **PK限制**（源:11458、11462、11555）：etc/pvpchannellist.etc；
  条目开头52=52频道自由练习场；【0 34】=段位范围(0~34全段位可进)；
  【99】=等级上限(85/86改99)；56频道第2个数字20改0=取消最低等级限制。
- **频道名**：etc/channel_info.etc + etc/etc.kor.str（源:11463）。

## 五、可直接复用的模板

### 5.1 礼包类模板
**自选礼盒**（源:11615，selection num 1=选1个/0=全给；avatar版源:11619）：
```
[stackable type]
	`[booster selection]`	0
[booster category num]
	0
[booster selection num]
	1
[booster select category]
	0	0
	[stackable]
		20190533	1
		20190534	1
		//代码	数量，顺序往下写
	[/stackable]
[/booster select category]
```
**随机礼盒**（源:11621）：
```
[stackable type]
	`[booster]`	0
[cool time]
	1000
[booster info]
	[etc]
		1
		1108	60000	2
		//物品代码	概率	数量
	[/etc]
[/booster info]
```
**可重复打开**（源:11617、11909）：[stack limit]1 + [do not delete] +
[cool time]1800000(毫秒，600000=10分钟) + [cooltime maintenance]1 1 1；
[booster info]内多个[etc]组=每组随机取一；[impossible contents]`charac cargo`禁入账号金库。
**职业任选**（源:11616）：[booster category num] 1 9（9=职业数）；
每职业一个[booster select category] n 0 内放[avatar] 代码 1 3 0；
结尾[booster category name]列"请选择奖励"+各职业名。
**商城自动打开**（源:11618）：[stackable type]`[usable cera package]`0 +
[package data]代码 数量…；[suitable job]按职业分类(可删)。
**宠物自选**（源:11620）：[booster select category]内用[creature] 400990233 1。

### 5.2 任务类模板
**通用骨架**（源:11622~11630）：
```
[grade]	`[daily]`
[npc index]	2
[complete npc index]	-1
[job]	`[all]`
[grow type]	-1
[level]	1	99
[type]	`…`
[sub type]	…
[int data]	…
[reward type]	`[item]`
[reward int data]	3037	1
[name]	`任务名`
[depend message]	`接受对话`
[condition message]	`任务提示`
[solve message]	`完成对话`
```
九类任务参数表（源:11622~11630）：

| 类型 | [type] | [sub type] | [int data] |
|---|---|---|---|
| 副本通关 | [condition under clear] | 6 | 副本代码 难度(-1/1/2/3) |
| 击杀怪物 | [hunt monster] | -1 | 副本 难度 怪物代码 数量（+[dungeon info]副本 难度） |
| 收集物品 | [seeking] | -1 | 物品代码 数量 |
| 通关某房间 | [clear map] | -1 | 房间编号 |
| 通关全房间 | [condition under clear] | 11 | 副本 难度 房间数量 |
| 限时通关 | [condition under clear] | 0 | 副本 难度 时间(秒) |
| 限制组队 | [condition under clear] | 5 | 副本 难度 组队人数 |
| 找NPC对话 | [meet npc] | -1 | NPC代码 |
| 在线挂机 | [custom quest] | 4 | -1 1（另加[difficulty]`D`、[event]1绿色任务、[online]分钟数） |

### 5.3 装备特效类模板
**攻击时召唤怪物**（源:11635；被击触发源:11636把[attack success]换[hit]）：
```
[if]
	[cooltime]
		78000
	[attack success]
		1
[/if]
[then]
	[target]
		`myself`	-1
	[duration]
		60000
	[reduce duration at pvp module]
		75
	[probability]
		1
	[summon monster]
		1	10	1
		//怪物代码 怪物等级 数量
[/then]
```
**消耗物品定时召唤**（源:11637）：[if][time]120000 1 1000 [my state]`stand`[/if]
[then][consume item]3033 10 [target]`myself` -1 [duration]60000
[summon monster]1000 50 1。
**血量触发召唤**（源:11638）：[if][time]1000 1 1000 [stat change]`hp` `<` `%` 20
[cooltime]10000[/if][then]…[summon monster]60112 49 1。
**10%无敌10秒**（源:11639）：[if][change status]`hp` `>` `%` 0 `end`
[cooltime]50000[/if][then][target]`myself` -1 [probability]10 [duration]10000
[buff]`unbreakable`。
**全职业技能攻击力**（源:11633）：[skill data up]…[/skill data up]大块，
每行`` `[职业]` 技能号 `[all]` `[level]` 等级 `%` 数值``；
职业标签10种：at fighter/at gunner/at mage/demonic swordman/fighter/gunner/mage/
priest/swordman/thief；模板1330行、值15/25，批量改值用正则替换`` `%` 数字``。
**称号技能无CD**（源:11808、11791）：
```
[if]
	[module]
		`[dead tower]`	`[dungeon]`	`[tournament dungeon]`	`[war room]`	`[blood system]`
	[/module]
	[change status]
		`hp`	`>`	`%`	0	`end`
	[time]
		500	1	500
[/if]
[then]
	[target]
		`myself`	-1
	[probability]
		100
	[add stat at once]
		`skill cool time`	`%`	-100
[/then]
```
**称号全属性**（源:11634）要点：全属性标签（[equipment physical attack] 100 100、
[separate attack]、[all elemental attack]等）+[active status control info]`freeze` 0 100 0
（异常免疫）+[all skill item container]全技能+10（[skill apply condition][skill group]`[all]`
[lower bound level]1 [upper bound level]70 [value]10 [extra condition]`[except for ex skill]`）
+[custom animation]`TitleAnimation/xxx.ani`称号动画+[command]{6=`(CREATURE)`}+
[use command]按键召唤obj+[restore]`hp``%`100 0回血+[speech on]说话特效+
[replace avatar ani]换时装动画。
**秒杀/削血**（源:11792）：写法1 [restore]`hp` `%` -200 0
（直接减血不受怪类削减，0=0毫秒掉完/1000=1秒）；
写法2 [weakness]600（削血，精英1/3、深渊领主1/6）；
写法3 [add absolute damage]`all` `+` 999999999。
**按键触发技能**（源:11802）：[command]{6=`(DOWN)`} {8=`,`} {6=`(DOWN)`} {8=`,`}
{6=`(CREATURE)`}[/command] + [if][use command]1 [cooltime]60000[/if]
[then][passive object]4803 0 0 0 99 0 ``[/then]。
**ACT怪物锁血破防**（源:11614）：[TRIGGER][LIMIT]1 [WHICH][ME]
[CHECKUP][HP][<=]99999999 [POINT][/CHECKUP][ DO BEHAVIOR][ME]0[/TRIGGER]
[BEHAVIOR][VIRTUALHP APPENDAGE] 699 99999999 2 10[/BEHAVIOR]。

### 5.4 强化_增幅类模板
**强化券**（源:11632）：
```
[equipment reinforcement ticket]	10	15
[equipment amplify reinforcement ticket]	12	10
[check usable itemlevel]	1	40
```
**强化/增幅等级触发属性**（源:12050）：
```
[if]
	[change status]
		`hp`	`>`	`%`	0	`end`
	[equipment upgrade]
		`upgrade`	`=`	1	0
		`amplify`	`=`	1	0
	[/equipment upgrade]
	[cooltime]
		5000
[/if]
[then]
	[target]
		`myself`	-1
	[equipment duration]
		5000
	[stat]
		`physical attack`	`%`	1
	[stat]
		`magical attack`	`%`	1
[/then]
```
**高级强化机**（源:12000）：NPC加[upgrade item event] 0；
强化材料2670203高级炉岩炭（[stackable type]`[material]`1 [item group name]`mineral stuff`）；
2670204一次性强化券/2670205一次性强化机；控制文件etc/upgrade.etc、amplifyupgrade.etc、
chronicle.etc，支持[amplification const][max upgrade level by rarity]
[destroy level by rarity][destruction result]等词条。
**禁止操作**（源:11645）：[impossible contents] `upgrade`强化 `amplify upgrade`增幅
`disjoint`分解 `gift`送礼 `separate upgrade`锻造 `charac cargo`仓库存储
`ban redeemitem`售出不可回购 [/impossible contents]。

### 5.5 其他可复制块
- 每日自动发放/6点重置（源:11800、11981、11545）：etc/chn_server_limititemusageinfo.etc →
  [refill item] 3037 5 `2030-10-17 06:00:00`（物品 数量 到期=刷新时间）。
- 时装限交易次数（源:11996）：[trade limit max]1 [stack limit]1。
- 时限道具（源:11541）：装备[usable period after unsealing]1；道具[usable period]1。
- 技能预读防卡顿（源:11816）：etc/skillpreload.etc → [character]角色编码 + [skill]技能号
  （如男柔道觉醒63）+ 该技能全部ani路径（character/atfighter/effect/animation/、
  passiveobject/character/fighter/animation/下找）。
- GM命令（源:11648）：//lv等级 //item刷物 //itemseed 3037 9999补齐 //mailitem
  //dropitem //avatar刷时装 //dirty红字 //pd删契约 //q完任务 //durable 10 30耐久
  (10武器11称号12上衣13肩膀14下衣15鞋16腰17项链18手镯19戒指20左槽21魔法石)
  //fatigue set 1000 //cargo delete //dimen max //ulti max //ac all称号簿
  //pcroom on黑钻 //startevent 1 1活动(ID在d_taiwan.dnf_event_info表)；命令均带空格。
- 契约（源:11535、11524）：premiumlist_new.etc定义+[type]基础类型
  (17~22霸王/23~27达人/79成长/88魔王/92晶体等)+附加效果[unlimit fatigue][fatigue][exp]
  [inventory limit][coin][gold bonus]；premiumserviceeffect.etc关联图片/BUFF装备
  ([add equipment list])；newcashshop.etc的premium里上架才大退不消失
  （期限道具末两位99、50016+）。
- 黑钻全套（源:11524）：stackable.lst加3017950~54 heizuan/0~15.stk；
  equipment.lst加99440451 character/common/etc/9944451.equ；
  premiumlist_new.etc底部[fatigue]1000 [inventory limit]20；
  商城时效道具行 30080 3017951 1 0 0 0 <13::name_10000387`晶之契约 `> 99 50023；
  GM开22/29/48号活动；翻牌物品在itemdropinfo_clearreward.etc搜"pcroom card blank item"
  （几率/道具/数量三数一组，几率总和1万）。
- Light Server（源:11932）：etc/serverparameter.etc [light server no]3[/light server no]
  （频道id），run后打印"Light Server Mode start!"；多频道写 1 2 3 4 5 6 7 8；
  etcparameter.etc下[light server monster move speed/attack speed/hitrecovery/hpmax/
  physical attack/physical defence/magical attack/magical defence]倍率1.0→5.0。
- 公会告示栏（源:11998、11999）：sqr/extend_function/onopenpopupwindow.nut 合并函数，
  popupType==42时 sq_OpenPopupWindow(217,0,0,0)（0627窗口id217/0725为219）；
  红叉修复 npk对应 27074>Interface/newstyle/windows/community/guild_ver02.img。
- 跃级转职/觉醒券（源:11887）：参考stackable/consumption_1252.stk，
  stackable.lst登记2675816(转职升20)/2675817(觉醒升55需账号60+)；
  补NPK(select_class.img等)和exe字符串50537~50566。
- 迷惘之塔25层（源:11781）：dungeon/towers/towerofillusion.dgn；
  首数字15=总层数改25；"11 15"=11~15层通关回血50%一并改；每层对话写满。
- 升级邮件（源:11790）：event/levelupreward.evt（同一等级只能送一件，多件需套盒）。
- 外观类（源:11586、11471、11596、11780、11469）：
  奔跑残影=[SPECTRUM]1 [SPECTRUM TERM]100 [SPECTRUM LIFE TIME]500
  [SPECTRUM COLOR]255 255 255 255 [SPECTRUM EFFECT]`NONE` 写入 dash.ani/move.ani；
  梁月残影=用其移动/跑步 ANI 替换鬼剑士对应 ani；
  蓝拳插地=equipment/character/priest/weapon/ 下 willdriver.ani img调用192改197；
  称号图标=[icon]指向npk贴图号、动画=[custom animation]改名指向；
  隐藏=[hide equipment]/[hide layer]/[hide grow avatar]。
- 100级修复八点（源:11801）：exptable.tbl≤21亿且新等级经验追加在尾部不改旧值；
  etcparameter.etc两标签补到101级；cc_start.qst [level]101 102；
  所有*.qst/*.npc改满等级上限；goldlimitbylevel/sptable/pvpchannellist配套。

## 六、常见坑

1. **.lst结尾**：关联不存在路径、结尾没回车或多加回车→服务端无法启动；
   改完必查.lst结尾（源:10015）。
2. **空格**：grade起每行要含一个空格否则写不进工具；
   数值后多打0会写坏（如`'[water element]' 0`须删0且行尾留空格再回车）（源:10016）。
3. **不备份/复用pvf**：应写一段导入导出验证、对比文件大小（kb骤变=写错）；
   反复改同一pvf体积会膨胀，尽量用原版pvf重复导入（源:10016、11898）。
4. **加密pvf进服务端**→跑不出五国（源:12019）。
5. **金库**：金币上限勿超21亿，格子数最好8的倍数（源:11536）。
6. **100级全红**：exptable超限/改旧等级经验→旧账号封号限制交易；
   etcparameter缺参数→100级独立变0（源:11801）。
7. **pvpchannellist乱改会炸PVF**；GM工具改的PK等级进PK场会出错，
   应改经验倍数或进入门槛（源:11462、11461）。
8. **etc/parameter改独立**可能导致技能伤害无效（源:11817）。
9. **契约只改一处**→大退消失，三文件必须配套（源:11535）。
10. **APD/新道具**必须登记.lst列表并查代码重复，否则不显示名字/图标
    （源:10408、10015、12000）。
11. **[inventory limit]倍数过大**→负重显示复数（源:11524）。
12. **领主粉**：independent_drop.etc里黄金哥布林61726掉落代码有异常，
    须补全或把掉落加在它之上；dungeon_name.etc怪物ID后两位要写0 0
    否则副本无小图标（源:11716）。
13. **改黑色瘟疫/骨戒类被删效果**：参考雪之荣誉(dragon龙)/嗜灵之戒(devil恶魔)
    等自带词条改，flavor text不能凭空添加（源:10016）。
14. **重复课**：11464=11462、11465=11463、11767=11530/12068（分解师）、
    11981=11800/11545（每日发放），内容一致。

## 七、深读课程索引

【01】PVF文件解读（16篇全读）
10003_暴击率的计算方式以及公式
10004_PVF aicharacter目录分析
10011_PVF map目录解析
10013_PVF中所有文件目录中文翻译
10014_PVF 物品-人物-对话-职业-宠物对应位置
10015_PVF 粗谈
10016_PVF经常修改的文件路径
10017_了解PVF给修改指个路
10018_装备对应翻译
10019_PVF里各项数据翻译对照表
10020_PVF参数对照表
10021_面板中英文对照表
10022_PVF ect解析
10023_冒险团buff
10024_冒险团详细
12019_关于PVF修改替换后跑不出五国解决办法

【16】常用模板（28篇全读）
11615_【模板】打开后礼盒多个道具选择其中一个
11616_【模板】打开后任选职业接受全部道具
11617_【模板】可重复打开的礼盒不消失
11618_【模板】商场购买后自动打开获得全部
11619_【模板】光环_时装自选礼盒
11620_【模板】宠物自选礼盒
11621_【模板】随机礼盒(打开后随机获得其中一个)
11909_十分钟开一次礼盒
11622_【模板】副本通关类任务
11623_【模板】击杀怪物类任务
11624_【模板】收集物品类任务
11625_【模板】通关某房间任务
11626_【模板】通关全房间任务
11627_【模板】限时通关类任务
11628_【模板】在线挂机类任务
11629_【模板】找NPC对话任务
11630_【模板】限制组队类任务
11632_【模板】增幅强化限制等级使用写法
11633_【模板】全职业技能攻击力
11634_【模板】称号全属性
11635_【模板】攻击时召唤怪物
11636_【模板】挨打时召唤物品
11637_【模板】消耗物品召唤怪物
11638_【模板】血量掉到多少召唤召唤物
11639_【模板】特效写法，10%无敌持续10秒
12018_强化无视攻击
12050_【模版】增幅_强化达到相应的等级，提升物理攻击，独立攻击
12078_游戏设置缺少开启扩展技能栏或技能栏上不显示快捷键名解决方法

【13】obj（7篇全读）
11611_收集部分obj特效
11612_Obj关于ACT的部分进阶文档 — 条件对象
11614_act怪物锁血连击破防
11775_人物模型变大教程
11984_缩小act
12059_obj解析
12060_角色 怪物变大教程

【17】小白玖仙的自学模式（2篇全读）
11898_初学注意事项
11899_【JX】从零开始的学习之路第一篇

【11】其他PVF杂项（88篇全读）
10357_角斗场宝珠
10378_附魔宝珠
10394_宝珠怪物卡片属性参考
10406_卡片宝珠解读
10408_实现宝珠附魔增加技能具体参数
11455_让4g内存当8g玩教程让电脑不在卡顿（正文仅链接）
11456_PKCK开启多个频道的方法
11457_多频道修改教程
11458_关于53频道的一些小改，让53频道不限制段位
11459_增开频道详细说明（正文为空）
11460_85级后无法进入pkc的问题（正文仅引言）
11461_开56频道很吊，我给大家带个更屌的
11462_自己发一个设置56登记限制和经验的教学
11463_修改频道名称
11464_设置56登记和经验教学（与11462相同）
11465_修改频道名称（与11463相同）
11466_装备词典修改
11467_PVF小修改整合
11468_角色，职业
11469_隐藏写法
11470_剑魂太刀里鬼动作修改
11471_梁月的残影特效
11523_一些etc书签
11524_黑钻
11530_分解师详细解读
11535_契约修复指导
11536_修改账号金库详解
11538_称号簿
11540_pkc限制进入段位，等级
11541_时限代码
11545_每天6点自动重置背包内部分物品
11547_佣兵系统
11548_金币上限
11549_创建角色页面修改五角色或还原
11552_游戏滚动条文字修改
11554_登录游戏弹出的公告框如何调出和删除
11555_至尊决斗场不限制pk等级
11556_账号金库
11583_APD详解：装备、技能、状态、外观及增益效果
11584_减CD-APD写法
11586_让人物奔跑与移动时出现残影
11596_蓝拳插地不显示武器
11644_频道文件(cfg)详细翻译解读
11645_禁止执行类操作
11646_分享如何刷深渊不用每次点挑战深渊派对
11647_等级补丁修改教程
11648_GM模式大部分命令
11649_自定义技能索引avi视频播放
11716_领主粉添加
11740_200种特殊宝珠模板（正文仅网盘链接）
11767_解读的副职业文件（@梦太晓）
11769_ahk连发源码（@梦太晓）
11780_简单四步教你DIY称号图标和动画效果（@绮陌敛香尘）
11781_迷惘之塔恢复25层的方法
11790_升级邮件奖励
11791_称号20220611秒杀
11792_秒杀 削血词条
11800_每日刷新赠送
11801_修复100全红
11802_按键触发技能代码
11804_白图深渊翻牌都是史诗
11808_哥特綺夢称号技能无CD
11810_力量、属强、独立对应伤害表（正文为空）
11816_解决技能释放卡顿的方法
11817_独立攻击力修改路径
11818_系统分解机详细说明
11887_角色跃级转职_觉醒券（@小葵花蛐蛐）
11891_修复血槽空格buff（@小葵花蛐蛐）
11911_血条震动和伤害字体配置插件
11912_autio修改教程
11926_镶嵌徽章的另类玩法（@希尔的守护）
11927_适合小白的最简单的预读技能（@希尔的守护）
11932_开启特殊服务器(Light Server)
11933_修复拍卖行锻造等级8以上BUG
11980_冒险团和支援兵
11981_每日自动发放物品
11986_周常时刻表个人使用情况chn_schedule.etc&南部溪谷 领主之塔
11996_拍卖行文件解析图与时装限制交易次数的方法（@我是六娃）
11998_[教程]开启公会告示栏
11999_[exe]还原公会告示栏
12000_高级强化机
12006_关于拍卖行上架修改
12035_修改或删除副本掉落装备赋予的随机强化等级（@红枫百科）
12036_花里胡哨关于制作心悦VIP等级显示（@一袋米抗100楼）
12037_修改评分要求（@红枫百科）
12068_分解机说明
12073_黑钻显示在契约面板里的方法（@贝拉贝拉的头巾）
12086_ACT被攻击（属性检测）回血

附魔、宝珠/与频道整合修改/子目录课程已并入上方编号列表（10357~10408、11740、11644）。
