# 物品·商店·掉落·活动 知识精华

> 提炼自 dnf-pvf-tutorial【06】NPC-商店 51 篇、【10】物品修改 48 篇、【18】掉落 21 篇、
> 【19】活动 17 篇，共 137 篇：全部标题通读，核心解析/模板/代码类课程逐篇深读。
> （源:编号）=课程编号，原文在 `pvfCourse/` 对应分类下检索（全量索引见 09-course-index.md）。

## 一、道具与材料（分类/路径/标签）

**道具通用标签**（.stk/.equ 文件头，源:10401）：
- `[name]`/`[explain]`/`[grade]`（物品等级）/`[minimum level]`（最低使用等级）
- `[rarity]` 稀有度：0白 1蓝 2紫 3粉 4橙(史诗) 5勇者红
- `[usable job]`：`[all]`/swordman/fighter/at fighter/mage/at mage/gunner/at gunner/priest/thief
- `[attach type]` 交易属性：`[account]`账号绑定 /`[trade]`无法交易 /`[free]`可交易 /
  `[sealing]`封装 /trade delete
- `[stack limit]`携带上限、`[cool time]`冷却(毫秒)、`[weight]`、`[price]`、
  `[need material]`（代码+数量）
- `[stackable type]` 类型：`[material]`材料 /`[material expert job]`副职材料 /
  `[quest]`任务 /`[waste]`消耗品 /`[etc]`
- `[exp bonus rate]` 1.000000=双倍（6位小数）；`[icon]`+帧号；
  `[move wav]`：POTION_TOUCH药水/BONE_TOUCH材料/PAPER_TOUCH卡片/FOOD_TOUCH食品
- `[package data]`礼包内容、`[sealing removal item]`开启所需钥匙、
  `[npc gift disallowance]`1=不可作NPC礼物

**分类写法**：
- 消耗品（源:10420）：`[stackable type]` `[waste]` 0 + `[item group name]` `potion`；
  回复 `[hp recovery]` `+` 70 1000 `myself`（总量/所需时间/对象）；
  自身异常 `[my status]` `sleep` 100 5000 25（状态/几率/持续ms/等级）；
  改属性 `[stat change]` `+` 40 `physical attack` …+`[stat change duration]` 180000 `myself`；
  解异常 `[active status recovery]` `freeze` 20 `myself`。
  状态码：blind/lightning/burn/freeze/hold/sleep/bleeding/confuse/curse/stone/stun/posion/all/any
- **无限消耗**：把 `[waste]` 改成 `[unlimited waste]` 0（源:10371、10407）
- 材料（源:10419）：`[material expert job]` 0 或 `[quest]`
- 卡片（源:10416）：`[material expert job]` 1 + `[string data]`（MonsterCard_image.img +
  适用部位 `[amulet]`/`[wrist]`/`[ring]`…）+ `[int data]` 贴图编号 怪物ID + `[enchant]`
  内附魔如 `[separate attack]` 46 23 + `[item category]` `monster card`。
  宝珠：`[enchant waste]` 0 + `[expert type]` `[enchanter]` + `[monster card id]`。
  部位对照：coat上衣/pants下装/shoulder护肩/waist腰带/shoes鞋/weapon/title/support辅助/
  magic stone魔法石/hat~skin avatar时装9件/aurora avatar光环/creature宠物/
  artifact blue绿红宠物装备
- 变身药（源:10417）：`[disguise]` 0 + `[string data]` `monster`(可移动)/`npc` +
  `[int data]` 怪物ID 持续秒
- 召唤（源:10418）：`[waste]`+`[expert type]` `[doll_controller]` + `[summon apc]`
  APC编号 等级(-1=同召唤者) 等级 存在时间 召唤只数
- 经验类（源:10422）：胶囊 `[etc]` 0 + `[increase status type]` `[expUp]` 20000 +
  `[maximum level]`；公会经验书 `[guild power war point]` 500；
  成长秘药 `[waste]`+`[cool time]`1800000+`[cooltime group]`99+`[exp bonus rate]`+
  `[usable period]`3+`[stat change duration]`
- 罐子/礼盒（源:10423、10412）：`[booster]` 0 + `[booster info]` 内子标题
  `[avatar]`/`[equipment]`/`[cera]`(复活币契约类)/`[creature]`/`[etc]`/`[stackable]`，
  条目"必得标记 物品ID 几率权重 数量"。随机罐用 `[int data]`：ID 几率 1 三字一组，
  总池约10万，**首个ID不写几率=吃掉剩余几率**（源:10375）
- **魔盒**（源:10400）：路径 stackable/cash/randomcerabox_1、2、_event1/2.stk 与
  stackable/event/atmage/randomcerabox_event3.stk；
  可用代码 896/992/8289/2660169/2660397/2660419/690000280（ID绑死DNF.EXE）。
  `[stackable type]` `[multi upgradable legacy]`；`[random]`→`[default list]`→多个
  `[random list]`：首数字=本次抽取个数，其后4字一组 物品ID 概率 数量 公告(0/1)；
  **最多3栏**，加栏=再加一组`[random list]`；`[sealing removal item]` 900 3=钥匙
- 礼包（源:10421/10405/10414）：`[usable cera package]`=手动开启；
  `[cera package]`=商城购买自动打开；`[package data]` ID 数量 成对；
  `[package data selection]`块=可选内容；`[booster equipment upgrade]` 13=开出装备直接+13；
  `[trade limit max]` 1
- 任选礼盒（源:10410/10411）：`[booster selection]` 0 + `[booster selection num]` +
  多个 `[booster select category]` 序号(从0) 0 + 子表 `[stackable]`/`[equipment]` +
  `[booster category name]` 选项名
- 可重复开盒（源:10413）：`[stack limit]`1+`[do not delete]`+`[cool time]`86400000+
  `[cooltime maintenance]` 1 1 1（下线不重置冷却）；加前先删原冷却防冲突
- 定时删除（源:10396）：`[expiration date]` 1356966000（Unix时间戳）；
  每日6点删除用 `[daily delete item]` 1；
  **卖店后不可回购**：`[impossible contents]` `ban redeemitem`（源:10409、10404）
- 设计图（源:10415/10424）：`[stackable type]` `[recipe]` 1；
  `[int data]`：材料种数→N对(代码 数量)→生成种数→(产出代码 数量 未知)；
  `[string data]` `[craftmanship]`(炼金人偶)/machinary/weaving；
  `[minimum itemmaking level]` `harmor` 5；`[success rate]`、
  `[maintain ability]`1继承强化增幅锻造、`[broadcast type]`1成功公告、
  `[fail output]` 失败产出、`[use upgrade table]`；
  追加掉落 `[special monster drop]`1+`[difficulty for extra drop]` `[hero]`
  (easy/medium/hard/ultimate/hero)。**游戏内GM工具取不到设计图代码**
- 关键路径：称号 equipment/character/common/title（源:12017）；
  升级券 stackable/twdf/event/130321_CreatDNF/tw_create_levelupticket5.stk（源:10372）；
  CD药 stackable/event/comeback/event_7823.stk（-10改-100=无CD；
  霸体药 ptn_superarmor.stk 两个60000=冷却/持续，源:10369）；
  背包扩展券 2660296~2660298（源:10380）
- **契约**（源:10398）：etc/premiumlist_new.etc（`[type]`79类型 + `[target item]`礼包 +
  `[item]`+[term]天数 + `[attr]`内 [bonus exp]20/[quest item drop rate]20/
  [independent drop rate]）→ etc/premiumserviceeffect.etc（同[type]被调用：
  `[add equipment list]`装备代码=自带特效如天域套；
  `[add selectAble equipment list]` 消耗品+装备配对=晶体契约，**固定不可新增**）→
  etc/timelimiteditemslist.etc（[entry] 代码 `名称串`，仅10个契约能显示剩余天数）
- 强化/增幅/锻造：凯丽最爱称号 tecipient_ofthe_faveo_kiri.equ 尾部
  `[upgrade prob increase]` 1000→1000000=必成；加 `[upgrade cost discount]` 99.000000
  =省99%费用（源:11389、11376）；
  锻造在 etc/upgrade_separate.etc：`[table]` 每组4数（曲线1属性/曲线2/成功率万分比/
  曲线3材料倍率），`[separate upgrade max]` 9 开锻9，`[item weights by grade]`
  按等级配材料，`[separate upgrade effect]` 特效RGB；70版本锻8+曲线残留旧版（源:11381）；
  etc/serverparameter.etc `[protect of upgrade down]` 8239 12 15 0 …=
  道具保护增幅等级区间（源:10374）
- 副职：character/expert/ 下各副职脚本（经验列+升级费用列）；
  分解出货=物品ID+小数关键值，**小数越小出货越多**（源:11356、11357）；
  分解机出货 etc/disjiont "additional result const"
  （白装后每4数一组：蓝紫粉史异界，源:11372）；
  金库 etc/accountcargo.etc（required level / required item 默认虚空魔石3299 /
  upgrade info 4数一组：格数、存钱上限、道具数、金币，源:10381）
- 人偶商店格子：character/expertjob/doll_controller.exj `[shop doll info]` 0 3 1 6 2 9
  （等级0/1/2对应格子数）（源:11585）

## 二、NPC 商店与商城（商品结构/价格/货架）

**NPC商店（itemshop/*.shp）**（源:11877、11382、11374）：
- `[sell item]`…`[/sell item]` 内为物品代码序列，7个一行；`-1`=空位；
  `-2`=分页符（前面=上页，后面=下页）
- 页签名必须写：`[tab name]` `商店` `異界寶珠` `[/tab name]`，不写进店就炸；
  页签文本在 itemshop/itemshop.kor.str（tab_name_weapon>武器…，可新增 tab_name_xxx）
- 商店↔NPC对照（源:11391）：赛丽亚=equipmentshop7.shp(Seria.npc)、林纳斯=1、辛达=2、
  卡坤=3、凯莉=5(shp序号)、加百利=equipmentshop_dungeon2~4.shp(Gabriel/材料/武器)、
  德利拉=equipmentshop_dungeon1.shp；
  NPC代码（源:11377/11387）：1林纳斯 2赛利亚 3卡妮娜 4辛达 7GSD 8土罐 9夏洛克 10罗莉安
  11卡坤 12莎兰 13诺顿 17凯莉 19奥菲利亚 20/21/38/44四罐 26克伦特 28艾丽丝 45歌兰蒂斯
  57沙影 58泽丁 64米内特

**NPC文件（npc/*.npc）`[role]` 功能标签**（源:11608）：
`[secret shop]`1002加百利 /`[recover stamina]`恢复虚弱 /`[sera shop]`跳商城 /
`[upgrade item]`强化 /`[amplify item]`增幅 /`[disjoint item]`分解 /`[product item]`17生产 /
`[item storage]`仓库 /`[post box]`邮箱 /`[move town]`2传送 /`[convert avatar]`33时装分解 /
`[genuine damage upgrade]`锻造 /`[one a day shop]`49每日商店 /`[automat]`1弹商城页 /
`[compound emblem]`徽章合成 /`[random option operate]`魔法封印 /`[power war]`势力 /
`[event message board]`留言

**新增NPC流程**（源:11369、11371、11387）：
1. itemshop.lst 底部加 商店编号+文件名（如 1005 petshop.shp）→ 建 .shp
2. npc.lst 加 NPC编号+文件名（3002 Oran2.npc）→ NPC 文件内 `[item shop]` 指向商店编号；
   `[name]` name_5001、`[field name]` field_name_5001
3. npc.kor.str 赋值 `name_5001>宠物`、`field_name_5001>宠物商店`（**末行要回车**）
4. 地图显示：map 对应 .map 文件 `[NPC]` 段加 `ID [left/right] X Y 0`
   （[left]正向/[right]反向；约300数值≈8cm）；
   **twn/map 底部还有一个NPC参数块必须同步改，否则不出五国**；
   只换客户端封包即可先测试
- NPC对话立绘：etc/dialogwindowimageindex.etc（NPC编号+img帧号），编号超4位会异常（源:11542）
- NPC喊话：`[balloon message]` `文本` 7000 3000（源:11807）；
  随机气泡：`[random message balloon]`（animation/probability 20/list 4条）（源:11609）
- 字符串全在 .str 文件：装备改字→equipment/equipment.kor.str；
  NPC对话→npc/npc.kor.str（dialog_Lin_ALL_数字>文本，数字=随机第几句）；
  任务→n_quest/quest.kor.str；直接改装备文件无效（源:11390）

**商城 etc/newcashshop.etc + etc/newcashshop_restrict.etc**（源:11525、11526、11378）：
- 分类标签成对：`[coin]`复活币 `[item]`道具 `[premium]`时效道具 `[creature]`宠物
  `[package]`礼包/时装
- 行格式10行一组：排序号(大者在前) 物品代码 数量 保留 保留 点券价 保留 `name_物品ID`
  (kor串) new标记(1=加NEW图标) 保留
- 复活币行例：9000 排序 1 代码 10 数量 …500 点券价 `復活幣`
- 限制标签（填**商城排序号**不是物品代码）：`[cart disallowance]`不可重复入购物车 /
  `[gift disallowance]`不可赠送 /`[gift only]`仅赠送 /`[max gift count]` /
  `[not stackable buy]`不可叠加购买 /`[cerapoint disallowance]`**禁止代币券(D点)购买**
  （源:11379）；`[category event tag]` 0 1 0 1=分类旁NEW标
- 限购：newcashshop_restrict.etc `[account restrict]`账号级/`[character restrict]`角色级，
  每12数一组：商城排序号 限购次数 保留 年 月 日(起) 保留 年 月 日(止) 保留 保留
  （源:11527、10388）；重复购买在数据库删对应 ipg_no 记录，
  可写触发器每日重置（源:12001）
- 时装散件编号：首位职业 1鬼剑2女格斗3男格斗4男枪5女枪6女法7圣职8暗夜9男法；
  次段10XXXX帽 11XXXX发型；末位部位 0帽1发2脸3胸4衣5腰6裤7鞋8皮肤（源:11557）
- 商城排序：顺序号大者靠前，批量排序可用WPS表格（源:11392）
- 上架注意：编辑明文后多出的 0d 0a 换行符要删（Windows回车≠Linux 0d），
  否则加不上（源:11375）

**加百利（神秘商店）etc/secretshop.etc**（源:11876、11370、11532）：
- `[eplp wait time]`3、`[price random]`10（价格浮动）
- `[dungeon npc]`：地下城ID → 行"商店代码 概率…"，10000=100%；
  商店代码 1000=德利拉(修理)、1002=加百利卖装备、1003=卖材料、1004=远古加百利
  (远古设计图)；[level section] 0 1 18 = 1-18级段；
  **德利拉+加百利概率和须=10000且保留德利拉段**；乱改结构 ./run 会出错
- 货物：`[secret shop]`→`[npc]`商店代码→`[dungeon]`地下城ID 组别 →
  条目：物品ID 类型(0/1) 价格 0 数量 权重；`[event item]` 附加；`[secret shop end]` 结尾

**售卖机/抽奖机**（源:11983、11384、11385、11533、11383、11558）：
- 文件 etc/pcroom.etc（卡妮娜）/pcroom3.etc（阿加雷斯宝箱，NPC81）/pcroom4.etc
  （赛丽亚售货机，NPC83）；抽奖机为 .vm：etc/pcroom.vm/pcroom3.vm/pcroom4.vm；
  对应NPC：Vendingmachine_pc.npc黑钻/Vendingmachine_5event.npc周年/SeriaVending.npc赛丽亚
- `[material]` 硬币ID+数量；`[output]` 4数一组：道具ID 抽中几率 数量 公告(0/1)；
  几率不能为0（展示写1），总和算百分比，建议≤100W
- 娃娃机 etc/craneminigameitem.etc：`[viewCnt]`6每组个数；
  `[item]` `[cnt]`数量 `[viewRatio]`出现率% `[pickRatio]`抓取率% `[/item]`；
  `[need material]`=买硬币额外材料（**必须写在娃娃机块内，写进硬币块会出BUG**）；
  UI ui/craneminigame/craneminigamewin.ui [variable] 100/101/102 控制抓钩速度、
  滚动速度、间隙
- **抽奖机物品数量>1时不能开全服公告，会卡死**（源:11983）

**每日/限时商店**：
- 每日商店：NPC 加 `[one a day shop]` 49 → itemshop/itemshop.lst 49 →
  itemshop/oneadayitemshop.shp；`[one a day start time]` 年月日时；
  `[one a day item]` 每行=一天货单，卖完循环回头一天（源:11803、11929）
- 每日自动发门票：etc/chn_server_limititemusageinfo.etc `[refill item]`
  物品代码→数量 结束时间 2030-01-01.06:00:00（源:11528）

## 三、掉落与爆率（参数含义/改法）

**四个全局爆率文件（etc/）**（源:10384）：
- itemdropinfo_clearreward.etc=通关翻牌；itemdropinfo_monseter.etc=普通怪爆率(全局1)；
  itemdropinfo_monseter_extra.etc=强化怪爆率(全局2)；itemdropinfo_monster_hell.etc=深渊爆率
- 格式：最前数字=组数；每组6数：A B C D E（白/蓝/紫/粉/史诗累计参数）+ X=基数(E+1)；
  随机 n∈(0,X-1]，n≤A白、A<n≤B蓝、…、D<n≤E史诗；
  各品质爆率=(后参数-前参数)/(X-1)；**参数必须≥前一个，相等则该品质爆率为0**
- 非常困难深渊出9件：把该组改成 `0 0 0 0 1000000 1000001` = 9件全史诗；
  白蓝紫粉SS按 30W/60W/90W/95W/100W 改 = 单怪掉率30%/30%/30%/5%/5%（源:10390）
- 翻牌：clearreward.etc 找 800000/989900/999900/1000000/1000001/1000002 六行改，
  算法同深渊（源:11543、10383、10392）
- 金币爆率：etc/itemdropinfo_common.etc，3数一组改掉落金币（源:10393）
- **改完PVF须同步服务端+客户端，并重启服务器程序**（源:10384）

**独立掉落 etc/independent_drop.etc**（源:11768、11534、10373、11355、11354）：
- 行格式：`0 怪物ID 物品ID 普通几率 冒险几率 勇士几率 王者几率 地狱几率 数量×5 0 0 -1 1`；
  **1000000=100%**
- 物品ID=0 时走 `[list]`：`物品ID 权重`…（权重管"掉了出什么"，几率管"掉不掉"）；
  单一写法=物品ID直接写行内（绿名怪必掉材料适用），多写几组=掉多个
- 末尾4数照抄别改；**新增行插到 [/independent drop] 前；一组写错，
  其后所有独立掉落失效（五国正常但就是不掉）**；行尾不能多TAB，否则跑五国出错（源:11534）
- 单件SS爆率：装备 .equ 内 `[creation rate]` 500（删=取消该SS掉落，调小=降爆率）（源:11597）
- 深渊固定掉落：etc/hellparty.etc `[group index]`深渊组（X-0怪物 X-1APC）；
  `[difficulty]` A~D 行4列即固定掉落件数（源:11982）
- 建筑物掉落：`[special passive object item]`（参考格蓝迪魔刹石写法）（源:11499）
- 世界掉落 etc/worlddrop.etc：`-1`分段，段首=等级，其后"物品代码 掉率"成对（源:10326）；
  D点物品代码在 stackable/twdf/cash/goldtradeauction/gold_trade_voucher1_10~1000
- 掉落装备强化等级与等级差：etc/serverparameter.etc `[drop upgrade rarity]` 内
  `[common]`~`[chronicle]`（掉落强化等级,权重 两位一组）；
  `[drop bonus of dungeon level increase]`（角色与地图等级差→掉率倍率）；
  仅普通图有效，深渊/异界不共享（源:11454）
- SS落地闪光：passiveobject/actionobject/monster/monster/action/angeleffect.act+ani
  指向 Common/CommonEffect/ItemdropEffect/lightbar.img、drop_after_loop.img
  （[IMAGE POS]/[IMAGE RATE]/[DELAY]），
  配合国服 sprite_common_commoneffect_itemdropeffect.NPK；
  静态闪光=PS合图替换NPK贴图+改PVF装备图标路径（源:11907、10382）

## 四、活动与礼包

**活动框架**（源:11520、11811）：
- 总表 event/ingameeventlist.evt：`[event]` `[idx]`86 `Attendance.evt` `[record type]`1
  `[start]`20191221 `[end]`20200319 `[state]`1 `[/event]`——活动ID+起止日期+开关
- 活动开关在数据库（GM命令 //startevent ID 参数；部分工具写不进参数2时直接改
  dnf_event_log 表）；**加完活动要重跑五国**（源:11918）
- 活动有效期词条 `[expiration date]` 时间戳要删掉才不会过期消失（源:11521、11929、11930、10379）

**各活动写法**：
- 出席/签到（活动86）：event/attendance.evt：
  `[db table]`event_1202_fatigue_attendance `[fatigue]`30；
  `[reward]` "代码 数量"成对，30天要填满90组；`[send mail]`+`[inven]`（源:11520）
- 夏日勇者（活动164）：event/heromissionevent.evt `[hero event]` 多个 `[mission]`：
  `[type]`payment/normal/final、`[repeat]`true/false、
  `[item]`首数=物品种数+成对、`[condition]`：通关副本次数(1 100)/消耗疲劳(1 500)/
  消耗无色(1 500)/每升1级(1 35)/累积登录(3 3 5 20)/final完成5项(5 1 2 3 4 5)；
  UI ui/event/heromission/heromissionwindow.ui（源:11522）
- 成长武器（活动100）：event/growthweapon.evt：`[gift growth weapon box]`690000003、
  `[growth material item]`690000002、`[growth material item max]`110、
  `[event bubble max]`10阶、`[event sand max]`10次/阶、
  `[growth equipment reward list]`最终装备；
  界面 ui/event/growthitempopupwindow/growthitemwindow.ui（源:11521、11930）
- 林纳斯的礼物：etc/growthpowerrewardbuff.etc：
  `[breakaway section]`0 1 59 1 60 70（阶段:第N次+等级段）；`[exp reward]`；
  `[package reward]`→`[group]`职业 阶段→`[package selection]`代码 数量；
  说明文件 etc/growthpowernpcdialog.etc；
  **点了就掉线=奖励里含不存在的物品代码**（源:11928、10397）
- 赛丽亚的祝福：event/seriablessing.evt `[Seria Blessing]` 6数一组：
  编号 最小等级 最大等级 3个未实测+经验加成%（源:11897）
- 一次性消费送礼（活动17）：DB活动参数1=1000则必得（权重区间1-1000对应100%）；
  PVF `[bonus item info]` 每组：消费区间→物品，权重和=1000；
  是**单次消费**非累计（源:11931）
- 中秋每日商店（活动109）= `[one a day shop]` 商店49（见第二节）
- 冒险家回归：event/returnuserreward.evt 后门直接填（账号Uid、到期时间、是否首次）；
  官方7天未上线计时用 DB 触发器同步 charac_stat.last_play_time→charac_info；
  新角色特权 EventNewCharacterReward 活动162（参数1角色id、参数2经验倍率）（源:11819）
- 创世纪（活动160）：参数1=时段编码（19=19点-0点，4864=0-19点）、
  参数2=刷新间隔（60→3600秒）；奖励 event/tw_creatednf.evt；
  DB表 event_create_charac/event_create_dnf_info/event_create_dnf_user，
  event_day 可加行自定义刷新（源:11918）
- 异界四件事：event/dimensionactivationevent.evt：`[play day count]`进图次数、
  `[coin info]`复活币限制、`[select group]`职业选包、`[give group]`+`[grow type]`
  成长武器（源:11433）
- 活动公告带链接：event/eventlistwindow.evt `[entry]`→`[event info]` -1 2 序号 名称
  描述 起止日期 URL + `[popupwindow design]`（`[url hyperlink]` `[文本]` `网址`）
  （源:11820）；隐藏活动图标编号=information_button_tw.img 帧号（源:11821）
- 周末加成：etc/serverparameter.etc `[weekend bonus fatigue]`20 `[weekend bonus exp]`20
  （源:11551）

## 五、常见坑

1. **同步与重启**：PVF 改完必须同时替换客户端+服务端并重启服务端/虚拟机，
   只换一端轻则不生效重则崩溃（源:10384、10389、11374）。
2. **换行符**：SuperPVF 导出明文用 Windows 0d0a，PVF 要 0d，多出的 0a 必须删（源:11375）；
   独立爆率行尾多 TAB 跑五国报错（源:11534）。
3. **独立掉落连锁失效**：一组格式错→其后所有独立掉落读不出，"五国能跑就是不掉"（源:11768）；
   加百利概率三商店和=10000 且不可乱改结构，否则 ./run 出错（源:11370）。
4. **商城不发货/不显示**：物品本身写法不允许上商城（[npc info][avatar]表勿动）（源:11526）；
   礼包分类代码不全或英拼错（Prist→priest）会强制顶在第一页（源:10387）。
5. **魔盒逻辑**：概率不能大面积相同数字（只出默认）、不能写满顶（必出该物品）、
   不能全写太小（只出默认）；单件数量>1 时不能开全服公告（源:10400、11983）。
6. **页签与货架**：.shp 里加了 -2 分页但没写 `[tab name]` → 打开商店炸客户端
   （源:11877、11374）。
7. **地图 NPC 两处参数**：.map 内上方与底部两个 NPC 参数块必须一致，否则不出五国（源:11371）；
   NPC 编号超四位→对话立绘异常（源:11542）。
8. **活动奖励引用不存在物品**→点领取直接掉线（源:11928）；
   GM 邮件发活动物品不勾"封装"收不到（源:10369）。
9. **GM 发单件时装必崩**：把时装代码写进礼包 `[package data]` 再发礼包
   （PVF编辑器不能增删条目数，替换数≤原数量；DEC 编辑器可）；
   不存在的物品发出去取不出（源:10389）。
10. **娃娃机**：need material 必须写在娃娃机块，写进硬币块出 BUG（源:11386）。
11. **客户端版本落后**：商城图标不显示=客户端缺文件，用全量客户端补 sprite 资源；
    进图红叉=缺红叉补丁，放目录即可不用重启（源:12024、12023）。
12. **时间戳残留**：活动/礼包/成长武器类改完要删 `[expiration date]`，
    否则到期自动消失（源:11521、11930、10379）。
13. 晶体契约 `[add selectAble equipment list]` 写死不可扩展，复制到别的契约无效（源:10398）；
    游戏内 GM 工具取不到设计图代码（源:10415）。
14. 精神刺激灵药(2600021)无可改属性，改CD要用替代药如 event_7823.stk（源:10369）。

## 六、深读课程索引

| 主题 | 课程编号 |
|---|---|
| 爆率文件总解析/算法 | 10384（四大文件+算法）、10390（权威数值）、10391（全局/深渊/世界/异界掉率汇总）、11995 |
| 独立掉落 | 11768（两种写法）、11534、10373、11354/11355、11518（三套模板） |
| 翻牌/金币/固定掉落 | 11543、10383、10392、10393、11982、11499 |
| 掉落强化/等级差/单件SS/闪光 | 11454（serverparameter）、11597、11907、10382 |
| 商城结构 | 11525/11526（解读1/2）、11378（10行一组详解）、11527（限购12数组）、11379（禁D点）、12001（DB限购） |
| NPC商店/货架 | 11877（上架）、11382（分页+kor.str）、11391（商店NPC对照大全）、11377（NPC代码表）、11374（赛丽亚+菜单） |
| 加百利 | 11876（secretshop.etc几率）、11370（1000/1002/1003/1004代码）、11532（货物结构） |
| 售卖机/娃娃机/抽奖机 | 11983、11384、11385/11533、11383/11386/11558 |
| 特色商店/强化锻造 | 11803（每日商店）、11528（发门票）、11389/11376（称号强化）、11381（upgrade_separate.etc）、11372（分解商店）、11585（人偶格子）、10381（金库） |
| NPC添加/位置/表现 | 11369（完整流程）、11371/11387/11833（map坐标）、11807/11609（喊话）、11542（立绘）、11608（role功能表）、11390（字符串.str） |
| 道具标签/分类 | 10401（标签大全）、10420（消耗品）、10416（卡片宝珠）、10417/10418（变身召唤）、10419、10422（经验）、10423/10375（罐子） |
| 魔盒/礼包/礼盒 | 10400（魔盒详解）、10415/10424（设计图）、10421/10405（礼包）、10410/10411/10412/10413/10414（五型礼盒）、12087（回收箱）、10377/10379 |
| 契约/系统道具 | 10398（三文件）、10374（增幅保护）、10396（到期删除）、10404/10409（控制标签）、10369/10372/10380（CD药/升级券/背包）、11356/11357（副职）、10402/10403、10386（觉醒代码）、10399（任务道具代码表）、10397/11928（林纳斯奖励） |
| 活动 | 11520（ingameeventlist+签到）、11522（勇者任务）、11521/11930（成长武器）、11931（消费送礼）、11929（活动109）、11897/11923（赛丽亚祝福）、11819（回归/新角色）、11918（创世纪160）、11433（异界四件事）、11820（公告链接）、11551（周末）、11811（签到合集） |
