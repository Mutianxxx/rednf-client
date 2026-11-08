# 任务·地图·时装 知识精华

> 提炼自 dnf-pvf-tutorial【07】任务 28 篇、【08】地图城镇 91 篇（约 80 篇已深读/抽样）、
> 【09】时装 17 篇（上下文受限未深读，仅标题索引）。（源:编号）=课程编号
> （全量索引见 09-course-index.md）。

## 一、任务修改（路径/结构/标签）

**文件路径**
- 任务正文：`n_quest/<地区>/<副本>/<任务名>.qst`；地区子目录：hell深渊、job转职、
  epicjob觉醒、common普通、event/twdf活动、title称号、towers刷塔、pvp、
  requiem时空之门、value勇者、urgent紧急、expertjob副职业、time_piece时空碎片、
  gent根特、blackhall异界等（源:11399）
- 任务描述文本：`n_quest/quest.kor.str`——改完[int data]必须同步改这里，
  否则数量显示不变（源:11400）
- 奖励参数：`n_quest/questparameter.etc`（源:11566）；
  任务清单目录：`n_quest/epicquest.lst`（源:11832）；
  完成播视频：`etc/questmovielist.etc`（源:11830）；
  挂机文案：`etc/onlinequest.etc`（源:11574）；
  林纳斯40/60级奖励：`etc/growthpowerrewardbuff.etc`（源:11544）

**任务主结构**（源:11397/11563/11568）
```
#PVF_File
[grade] `[daily]`/`[normaly repeat]`/`[common unique]`/`[achievement]`/`[special daily]`
[npc index] 接取NPC代码      [complete npc index] -1（重复任务用）
[job] `[all]`                [grow type] -1
[level] 85 99                [quest point] QP点数（只能加给普通/重复任务）
[pre required quest] 前置任务ID
[type] 完成类型              [sub type] 附加类型
[int data] 完成需求数据
[reward type] `[item]`
[reward int data] 必得奖励代码 数量
[reward selection int data] 任选奖励代码 数量
[difficulty] `G`（任务名颜色）  [gold multiple] 金币倍数  [event] 1（活动置顶）
[name] / [depend message] / [condition message] / [solve message]  四段文案
```

**完成类型[type]与[int data]配方**（源:11568-11577）
- 找NPC对话：`[meet npc]` + NPC代码
- 击杀怪物：`[hunt monster]` + 副本 难度 怪物代码 数量；配 `[dungeon info] 副本 难度`
- 收集物品：`[seeking]` + 材料代码 数量
- 通关副本：`[condition under clear]` sub -1 + 副本 难度（-1/1/2/3难度）
- 限时通关：sub 0 + 副本 难度 时间(秒)；通关全房间：sub 11 + 副本 难度 房间数；
  组队人数：sub 5 + 副本 难度 人数
- 通关某房间：`[clear map]` + map房间代码
- 站街挂机：`[custom quest]` sub 4 + `-1 1`，配 `[online] 分钟数`；文案在 etc/onlinequest.etc
- 宠物进化：`[seeking]`材料 + `[reward type]` `[event creature evolution]` +
  `[reward selection int data] 宠物代码 302`；完成后取下宠物重戴才显示外观
  （源:11577/11831）

**任务内掉落标签**（源:11562/11565/12088）
- `[clear reward item]`：副本索引 难度 道具 最大数 概率% 上限
  （难度-1全部 0普通1冒险2王者3地狱）
- `[monster reward item]`：怪物 副本(-1) 难度(-1) 物品 最大数 概率% 上限；
  商业服防外挂每日任务必须让掉落物=任务材料
- `[enemy reward item]`：敌方索引 敌方类型(1怪2APC 3obj) 副本 难度 物品 最大数 概率% 上限
- `[PVP RANK]`：0-29=10级→至尊10，30达人31名人32小霸王33霸王34斗神

**questparameter.etc**（源:11566）：`[difficulty]`奖励倍率
S110 A90 B70 C50 M10 O10 E40 F60 G80 D200 U250 Z400 Y370 X340 W300；
`[piece reward table]` 1 6 / 2 12 / 3 18 + `[piece reward]` QP点属性行；
`[exp reward table]`/`[gold reward table]` 按等级的经验/金币表。

**定时任务**（源:11567/11510）：`[grade]` `[special daily]` + `[schedule]`段：
`0 / 起始时间 / 结束时间 / `SAT` / `16:10:00` / `16:40:00``，可写多段；
副本主文件同样可加[schedule]。

**批量与杂项**：批量改"对话即完成"=PVFtool+Notepad++正则，
查找`\[type\]\r\n.*\r\n\[/int data\]`替换为`[meet npc]`结构，选"文件查找"批处理（源:11396）；
单人过多人任务=[int data]两个2改两个1（源:11395）；
删除主线=事件簿里替换/删除代码，只对主线有效（源:11398）；
视频条件`[clear]`/`[on accept]`/`[clear_nonplay]`，[file path]指向`video/xxx.avi`（源:11830）；
任务清单`[episode] 等级 0`+`[episode_name]`+`[epic_index]`任务代码（源:11832）。

## 二、地图与城镇（路径/结构/参数）

**六大目录**（源:11401）：region(大区.rgn)→town(城镇.twn)→worldmap(选图.wdm+UI.ui)→
dungeon(副本接口.dgn)→map(城镇地图+副本房间.map)→npc(.npc)；n_quest任务。

**lst登记规则**（源:11403）：格式`ID '路径' `（路径用两个单引号包住、行末留空格）；
同类ID唯一、不同类可重复；**只有town.lst必须连续编号，跳号直接炸五国**
（源:11711/11447/11861）。

**rgn大区**（源:11404）：`[towns]` 城镇ID列表；
`[name] Type:9 Str:'name_xxx>中文名'`；`[minimap] 'MiniMap/xx.mm'`。
mm小地图的index必须与town.lst城镇号一致，否则看不了N地图/乱入；
mm里`world (index 副本接口代码) (Level 90 95)`等级限制（源:11711）。

**twn城镇**（源:11405/11428）：`[area] 序号 'Town/xxx.map' '[normal]'`（普通）/
`'[dungeon gate]' wdm编号`（连选图）/`'[gate]' 参数`；
`[limit level]`等级（老版`[need quest]`/`[need level]`删除即解锁）；
`[dungeon what must be cleared] -1`；0号区域一般=赛利亚房间（源:12021）。
`'[dungeon gate]'`区域不能摆摊，改成`'[normal]'`即可摆摊（源:11436）。

**wdm选图**（源:11406/11764）：`[ui path] 'WorldMap/UI/xx.ui'`；
`[dungeon]`"副本ID 前置任务(-1)"两个一组；`[hell dungeon] 1`（点亮深渊按钮）+
`[hell quest]`深渊前置任务+`[item condition] 3330`门票+
`[hell freepass item]`物品 数量（免票道具）。

**ui控件**（源:11406/11764/11851/11836）：`[ui controls]` `[balloon]`
`IDC_WORLDMAP_BUTTONn` x y 1 `'WorldMap/selectdungeon02.img'` 3 1 朝向 **副本ID** +
`[common action] 'Action/worldmap_balloon.act'`；x y=副本图标坐标；
BUTTON编号延顺不重复；选图界面崩溃先查这里；
新加副本=wdm加编号+ui加坐标，缺一就不显示（源:11711）。

**dgn副本接口**（源:11407/11448/11503/11764/11508）：`[minimum required level]`进图等级；
`[basis level]`基础等级（=怪物等级+掉落装备等级区间）；
`[experience increasing point]`经验倍率；`[size] 横 纵`（0起）；
`[greed]`走向字母阵；`[map specification] x y 房间ID`固定房间（可写多个=随机）；
`[boss map specification]`（写两个ID=随机boss）；`[start map]`/`[boss map]`
（两个坐标=随机）；`[required item] 物品 数量 数量`门票；
`[limit party count]`/`[limit inout count]`；`[necessary party]`最低进图人数；
`[designate dungeon difficulty]`锁难度；`[champion]`五难度精英概率0-100；
`[coin limit]`+`[coin info] `[easy]` -1 0`复活币限制（-1 0不限）；
`[pathgate object]`门obj10个数据(-1无门)；`[hit count]`/`[seal door appear rate]`深渊；
`[impossible skills] `职业代码` 技能号`禁技能（源:11946）。

**greed方向码**（源:11424/11502/11508）：AA不通 BB右 CC上 DD右上 EE左 FF左右 GG左上
HH左上右 II下 JJ右下 KK上下 LL上下右 MM左下 NN左下右 PP十字。
dgn的greed与各房间map的greed必须对应，如悲鸣6列1行：start 5 0、boss 0 0、
走向`BBFFFFFFFFEE`。

**城镇map**（源:11408/11822/11711）：
- `[town movable area]`传送门6数一组=x y 宽 高 目标城镇 目标区域(-1副本接口)；
  **必须两区域互相添加**，单向=卡左上角/回不来
- `[virtual movable area]`4数一组=x y 宽 高（可移动区）
- `[NPC] 编号 '[left]'/'[right]' x y z`
- `[tile]`长地板+`[extended tile]`宽地板（数量必须一致）
- `[animation] 'Animation/gateall_02.ani' '[normal]'/'[bottom]'/'[closeback]' x y z`
  ——光圈(带gate字样)/装饰，图层normal靠前、closeback底层
- `[passive object] 特效编号 x y z`
- `[quest condition] 任务ID`——开通该坐标传送（如素喃4117/4540开时间门与镇魂曲）
- `[sound] M_背景 AMB_脚步`（编号查客户端audio.xml→.ogg）
- `[map dialog] '文字'`进图弹框（源:11794）；`[necessary party] 3`组队进图（源:11794）
- `[block use stackable item]+[exceptions] 物品`禁消耗品（写map最底）（源:11506）
- `[visible minimap] 0 [visible town minimap] 0`关N键地图（源:11922）；
  `[player number] 2 8`街头争霸人数

**副本房间map**（源:11448/11764）：`[dungeon] 副本编号`房间归属
（提取副本=正则搜此标签）；`[type]` `[normal]`/`[boss]`/`[dummy]`假boss房
（杀完仍可走，老鼠图）；`[greed] 'FF EE'`可随机落点；
`[pathgate pos]`门xy按左/右/上/下固定顺序；
`[monster] 怪物编号 等级(1 0=随副本 / 1 10=+10级 / 0 60=自定义60) x y z 1 1 `[fixed]`
`[normal]`/`[boss]`/`[champion]` 0-100``；`[monster specific AI]`；
`[special passive object]` obj代码 x y z 数量 `[item]`/`[trap]`/`[monster]` 组号
（打爆掉物/陷阱/出怪，组号对应dgn `[special passive object item]`分组的第几组，
几率满分10000）。

**精英怪**（源:11512）：紫名`[champion]`/粉名`[super champion]`。
指定属性法：`[champion] 4 `[Immune-Physic]` `[Immune-Fire]` ...`
（champion必生效，super受权重影响未必出）；系统分配法：`[champion] 0`。
属性：Immune-Physic/Magic/Fire/Water/Light/Dark免疫、
Enhance-Physicaldefense/Magicaldefense（四免疫四选一）、Enchant-四属性攻击（四选一）、
Speedup-Move/Attack/Hitrecovery/Wakeup/Hpregen、
Etc-Neverfly不浮空/Etc-Reserrection复活、Immune-ActiveStatus免异常、
onAttack-stun/bleeding/confuse/slow/lightning/poison/blind攻击附带。

**mm世界地图**（源:11864/11511）：`[image] 'Interface2/arad_worldmap.img' 0`+背景；
`[town][index][area][index] 区域号 [real rect]`地图内可行走范围
`[project rect]`大地图区块范围`[npc] 编号 x y``[grid map][level][image number]`；
`[world][index]副本接口号 [level]显示等级 [point] x y（两把剑图标中心）[grid map]`
——大地图红叉没显示就补这段（源:11511）；
NPC详情`[role] `[item shop]`/`[repair item]`/`[disjoint item]``+`[shop]`；
NPC大地图头像=npc.lst编号对应的npk贴图编号，不对应显示红D。
minimap里登记NPC头像后，任何世界地图出现同名NPC会破坏光环传送，
建议不登记（源:11425）。

**NPC功能**（源:11409/11428/11446）：`[role] '[item shop]' 商店ID '[move town]' 目标NPC编号`
（传送以目标NPC原始位置为准）；传送进不去删`[move town limit str]`；
城镇添加总流程（提取→导入→town.lst连续编号→npc/shop→map坐标→mm注册→wdm/ui→
瞬移药剂[int data]加城镇号→npk入ImagePacks2→五国）见11446/11861/11711。
国服[extended tile]是"til编号+排序"格式，需展开成台服逐行格式（源:11444）。

## 三、副本修改（进入条件/怪物/奖励）

**添加副本完整链**（源:11448/11851/11402/11428）：dungeon新建.dgn→
dungeon.lst注册ID（可随便取不重复）→抄现成dgn改[size]/[greed]/[map specification]→
准备map房间+map.lst→worldmap对应.wdm的[dungeon]加`ID -1`→
worldmap/ui加[balloon]按钮→房间map的[dungeon]指向改新副本ID→
客户端+服务端同步→跑五国。
**map编号≤65535**，超过则五国正常但读不到文件、进图闪退（源:11771）。

**开启城镇/地图12步自查**（源:11402）：dgn最低等级→map.lst房间ID存在→
wdm副本ID+前置任务→dungeon.lst ID→ui控件→twn等级→twn调用的map→worldmap.lst→
rgn城镇ID→town.lst→传送方式（NPC `[move town]`或`[animation]`光圈）→
深渊（hell quest+深渊boss房间ID）。

**进入条件**：`[required item]`门票；`[necessary party]`人数
（异界6图在dungeon/impossible/，编号后就是次数，人数3改1单人，源:11421/11434）；
`[ancient dungeon] 1`=远古图吃门票+出图不虚弱，
加门票无效就补这段（源:11509/11430）；
镇魂组队修复=改[basis level]到90或图挪区/藏一个低级图（源:11437/11443）。

**难度**：删`[designate dungeon difficulty]`解锁难度选择（源:11505）；
开地狱级=`etc/ultimatedungeonlist.etc`加`[apply ultimate] 副本代码`（源:11450/11945）；
单副本加强=dgn底部加`[monster difficulty bonus]`数值块
（原属性倍数，第一图无效，不用跑五国）（源:11847）。

**怪物与掉落**：房间map [monster]行复制加怪（怪物编号开头`[normal]`结尾）（源:11505）；
全局怪物强度=`monster/monsterapcdifficultybonus.tbl`第2行起一行表值，
每属性5数对应普通/冒险/王者/地狱/未知，21-25 HP、26-30攻速、31-35移速、41-45攻击、
46-50防御、51-55硬直（倍数制）（源:11505）；
单怪`[vision]视野/[warlike]好战度/[cooltime]技能CD(ms)`在mob文件，
Notepad++正则`\[warlike\]\r\n\d+\t\r\n`批量改；
独立掉落=`etc/independent_drop.etc`（源:11505）；
死亡之塔=`dungeon/towers/table/towerofdeath.tbl`：
0伤害1防御2HP 3力量4体力5智力6精神7物理绝对8物理9魔法绝对10魔法11异常12MP，
分character/apc/monster三张[Revision Table]（源:11513）。

**通关给材料**（源:12088）：任务配
`[monster reward item] 怪物 副本 -1 材料代码 数量 概率 上限`+
`[type] `[seeking]``材料+`[dungeon info] 副本 -1`
（12088"秘密之森"为完整可用范例）。

**深渊系统**（源:11764/11504/11771/11452）四步：
1. wdm：`[hell dungeon] 1`+`[hell quest]`前置+`[item condition] 3330`+`[hell freepass item]`
2. dgn：`[hell dungeon] 1`+`[seal door map index]`深渊房间ID+`[seal door pos] x y`+
   `[hit count] 50 50 50 50 50`+`[seal door appear rate] 10`
3. 深渊房间map：`[special passive object] 30528(柱子) x y 0 1 `[hellparty]` 组号 几率%
   波次(三数一组)... `[/hellparty]``
4. `etc/hellparty.etc`：`[group index] 组号`+
   `[group] `A` APC编号 数量 APC编号 数量...`
   （大写字母=难度：A非常困难 B困难；APC列表查`aicharacter/aicharacter.lst`）
- 一个副本只有一根柱子出APC；柱子无APC=组合在etc未定义或ABCD与难度不符；
  进深渊闪退=map没注册map.lst；
  低级深渊缺票=把3330邀请函写进[hell freepass item]；
  换深渊APC=直接改hellparty.etc组内容（源:11504/11771）

**抗魔[evil rate]**（源:11498/11944/11948）：`[evil]`/`[evil high level]`五难度基准；
`[evil rate] a b c d`：b=抗魔极低最低保留比率(30→最多-70%)；
c=满增益所需抗魔/门槛比率(110→门槛×110%)；d=满增益比率(120→+20%)；
门槛到满值线性增长（增长率×a≈8000/门槛值）；
官方默认未达标最高-70%、达标最高+20%，改第二词条可调起点。

**塔/PKC**：迷惘之塔恢复25层=towerofillusion.dgn首个数字=总层数、
其后"层 map号"逐层列、`11 15`(11-15层通关恢复50%状态)改`11 25`、
每层剧情对话写满（源:11947）；
绝望之塔单机9进10卡死=每10层取玩家数据变APC，
改etc/towerofdespair.etc每10层NPC编号（11017→11016），
底部10~90数值全改0（源:11427）；
无限进塔=cfg频道`fatigue_time = 06`改6000（源:11451）；
一天一次=服务端1线频道未开，run加`./df_game_r cain02 start`（源:11422）；
PKC地图=`etc/pvpmapbasicdata.etc`的`[pvp map order]`+
`[pvp map basic data] 编号 索引 索引 0 1 1 1`（源:11432/11539）。

**定时副本**：dgn加`[schedule]`段+`etc/chn_schedule.etc`登记`[dungeon]/[quest]`标志行
（第一位副本/任务号，第二位0看不见1看得见…）+
`[dungeon minimap] 副本 1 x y 图索引`显示在城镇小地图（源:11510/11815/11567）。

**修复配方速查**：野猪进不去=r_noirpera.dgn [greed]下`0 0`改`'BBMMDDGGJJFFEE'`（源:11420）；
巨龙怪挡门=怪物代码全改1哥布林（源:11439）；
SAO塔随机化=100个map全挂一个dgn、start/boss房全设0（源:11439）；
虚无之境走格子=passiveobject/actionobject/monster/dimensiongate/cosmofiend/gaunis/_namgyu/
下start_tile_red01.obj与red_master_01.act（源:11920）；
下线卡左上角=twn补对应赛利亚门代码（源:11449）；
巴卡尔金龙=搜怪物代码56448定位bakalcastle/15077nmaug.map换怪（源:11416）；
南部溪谷=加可移动区域+改城镇副本接口+换NPK（源:11878）。

**国服→台服移植**（源:11766/11441）：能转的转、不能转的用台服标签实现同功能、
再不行删除；判断是否支持=在台服原版pvf里搜该标签
（部分标签只在特定编号范围生效）；map指向代码改台服格式；ani需编辑器转码；
act编号由ai文件return值调用（-1不动作），每个act=怪物一个技能带冷却；
proc.act被mob声明则trigger持续运行（无ai也有机制的来源）。

## 四、时装修改（外观/属性/共存关系）

**本分类17篇均未深读**（上下文不足，仅标题索引，待后续补课）：
10134_时装购买消费时代码｜10135_时装文件格式｜10136_光环｜
10301_非常麻烦的时装三件垃圾教程｜10302_神龙光环超详细教程｜10311_时装教程｜
10314_副本试触发时装变身｜10361_时装套装实现额外翅膀特效｜11531_时装调整箱｜
11537_时装合成器解读｜11593_部分天空黑点修复方法｜11598_时装散件教程｜
11885_时装潜能属性调整箱｜11886_时装潜能开启方法｜11950_简单时装写法教程｜
11991_男格斗脸部时装闪退修复｜11992_男女鬼武器外观同步
（关联线索：时装散件上架商城见【06】11557/11896；光环/时装自选礼盒模板见【16】11619
——均未深读。）

## 五、常见坑

1. town.lst必须连续编号，跳号=炸五国；其它lst无此硬性规定（源:11711/11447/11861）
2. map编号>65535：lst正常五国，进深渊/该房间才闪退（源:11771）
3. 提取城镇/副本文件不全、rgn与mm的town index不一致→看不了N地图/乱入/进不去
   （源:11714/11711）
4. map引用的NPC不在npc.lst→进图闪退；提取副本先搜[NPC]词条清理；
   赛利亚房间没NPC→清空[guild agit entrance info]与[pvp channel limit npc]
   （源:11447/11711）
5. wdm引用的dgn编号不存在、ui按钮编号重复、国服xui后缀未改→选图界面崩溃；
   服务端gameworld fail=城镇编号断档（源:11447）
6. 国服pvf不认识的新标签删干净；[extended tile]编号格式要展开；ani要转码
   （源:11447/11444/11441）
7. 改完必须客户端+服务端同步PVF；改lst要重新写bin，失败pvf弃用换备份
   （源:11428/11421）
8. 城镇传送门必须双向成对，单向=卡门口左上角/回不来（源:11822/11711）
9. [int data]改了还要改quest.kor.str描述，否则数量显示不更新（源:11400）
10. 怪物血量倍数过高会自杀；技能CD改太低怪物抽风甩技能（源:11505）
11. 深渊不出APC=查hellparty组合与ABCD难度；
    深渊不爆装=看basis level与掉落等级区间（源:11771）
12. 绝望之塔单机卡死=每10层取玩家数据变APC（源:11427）；
    一天一次=服务端1线频道未开（源:11422）
13. minimap登记NPC头像后，世界地图出现同名NPC破坏光环传送（源:11425）
14. twn里'[dungeon gate]'区域不能摆摊，改'[normal]'（源:11436）
15. 下线不在原区域/卡左上角：服务端df_game_r二进制补丁或twn补赛利亚门代码
    （源:11445/11449）
16. 宠物进化任务完成后需取下宠物重戴才刷新外观（源:11577）

## 六、深读课程索引

- **【07】任务（27/28深读）**：11397/11563/11568-11577=任务结构与10类写法模板；
  11399=路径+深渊6任务；11395/11396/11398=单人/批量/删主线；11400=int data与描述；
  11544=林纳斯奖励；11562/11565=掉落标签；11566=questparameter.etc；11567=定时；
  11830/11831/11832/12066=视频/宠物进化/任务清单/添加任务。仅图片：11394。
- **【08】地图篇（10/10深读）**：11401-11409=六目录+lst+rgn/twn/wdm+UI+dgn+map+npc
  体系总纲（最核心）；11711/12021=城镇副本提取添加全流程（两篇同文）。
- **【08】城镇（10/11深读）**：11446/11861=添加流程；11822=区域.map全标签；
  11864=mm全标签；11447/11714=排错；11444=tile格式；11511=大地图红叉；
  11425=minimap坑；11922=关N地图。仅链接/图：11985。
- **【08】副本（67/69深读或抽样）**：11448/11503/11508/11764=wdm/dgn/map三文件
  全标签详解（最核心）；11417/11418/11500=地图编号对照表；11424/11502=greed方向码；
  11505=难度/怪物/掉落/怪物表；11512=精英怪；11504/11771/11452=深渊四件套；
  11498/11944/11948=[evil rate]抗魔；11513=死亡之塔tbl；11946=[impossible skills]封技能；
  11847=单副本难度；11851=DIY地图；11766/11441=国服移植；12088=通关给材料范例；
  11416/11420/11421/11422/11426/11427/11430-11443/11445/11449-11452/11506/11507/11509/
  11510/11539/11770/11794/11815/11878/11892/11920/11944-11947=修复与机制杂项。
  仅图片：11419/11426/11429/11501/11924/11713；
  抽样未全读：11813、11453、11513(头部)/11418(头部)/11836(坐标表)/11946(头部)。
- **【09】时装（0/17）**：未深读，见第四节标题索引。
