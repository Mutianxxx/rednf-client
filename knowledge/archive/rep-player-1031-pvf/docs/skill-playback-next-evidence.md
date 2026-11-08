# 当前 1031 PVF 技能播放：实际控制器证据与接入

更新：2026-10-19。范围为独立工程 `rep-player-1031-pvf`，原客户端、PVF、既有逆向报告只读。本节点新增 `src/pvf_script_preview.hpp/.cpp`，由主流程调用 `appendScriptPreviews` 并统一构建；没有把注册特效组当作完整技能。

## 来源与证据等级

| 来源 | 身份 |
| --- | --- |
| `D:/dnf-rebuild/DNF1031客户端/Script.pvf` | SHA256 `d13ce454567197bb4617cad4d0e472f609a1ec5cf2256462d780547be878607d` |
| 同目录 `DNF.exe` | SHA256 `246b838163fa7c71aa0445fa4aafde04e7ac72aa72855a4b2a7eaeed5eeae264` |
| 当前实现 | 读取上述 PVF 的真实 NUT、CHR、SKL、OBJ、ATK、ANI、字符串表；平台无关的原资源不写回、不裁剪 |
| 既有原生证据 | `dnf-native-demo/reports/combat-native-reverse/skill-controllers/swordman/`；只有连突刺、十字斩的局部控制器合同，不能据此声称其他职业原生控制器已恢复 |

当前归档包含 **189 个 `.nut`、0 个 `.c`、0 个 `.cnut`、6867 个 `.obj`**。NUT 是可读原始 Squirrel 源文本，包含 `function`、条件分支、方法调用和注释，不是本次发现的预编译字节码。所查脚本代码和路径为 ASCII，韩文注释可按 CP949 解码；中文 token/STR 仍使用当前 PVF 的 CP936，不混用编码。没有 `.c` 成员只说明这份归档的成员清单；不说明 EXE 没有 C/C++ 硬编码。

“已证实”在本文指当前源字节/有序字段或现有有界原生指令支持；“重建”指独立播放器将这些回调编译为确定性可见时序；“未知”包括原客户端宿主调度、伤害结算、动态一致性等未闭合项目。源码可执行不等于当前播放器已经实现全部战斗消费者。

## 实际加载与分派

`sqr/loadstate.nut:3–9` 先执行 `dnf_enum_header.nut`、`common.nut`，再执行 `Character/avenger_load_state.nut`、`Character/atmage_load_state.nut`、`Character/CreatorMage_load_state.nut`。男魔法师状态并不依赖 `sq_LoadSkillEffect_*` 是否出现在 common 中。

`sqr/character/atmage_load_state.nut:6–9` 加载 `atmage_header.nut`、`atmage_common.nut`、`passive_skill_ATMage.nut`。本次三条状态分别在第15、24、34行由 `IRDSQRCharacter.pushState(job,path,prefix,state,skill)` 注册。`sqr/dnf_enum_header.nut:1164` 声明 `ENUM_CHARACTERJOB_AT_MAGE=8`。`character/character.lst` 的8实际指向 `Mage/ATMage.chr`，`skill/skilllist.lst` 的8实际指向 `ATMageSkill.lst`，由该表再解析技能ID与SKL。对象ID来自 `passiveobject/passiveobject.lst`，脚本来自 `pushPassiveObj`，未按文件名相似度建立绑定。

`sq_AddFunctionName` 则出现在附加状态脚本中，例如 `sqr/character/atmage/icecrash/ap_icecrash.nut:2–6` 显式绑定 `proc/onStart/onEnd`，`sqr/character/atmage/magicshield/ap_magicshield.nut:9–16` 还绑定 `onDamageParent/drawAppend/getImmuneTypeDamageRate`。它与 `pushState`、`pushPassiveObj` 是不同注册层，不应把全部 NUT 统一解释成特效清单。

既有通用状态宿主逆向窗口位于 `state-attack/code-0060da30-state-api-registration.*`、`code-0060c3f0-state-packet-registration.*`、`code-00685700-state-script-wrapper.*`、`code-006835c0-add-state-script-wrapper.*`；它们是一般宿主证据，**不提供本次三条技能专用原生函数地址**。本次没有虚构每技能C++地址。

## 本节点接入的三条可执行空放流程

播放环境明确为视觉 fixture：技能Lv1、EX=0、攻速1000、无方向键；空放与可选固定测试靶几何接触分开。NUT 可见调用语义被编译成配方；动画源时长保留，回调在60Hz首次跨过来源时刻的tick派发。结束后人物切换到本职业CHR的 `[waiting motion]`，持续实体单独退出；角色结束不会提前抹掉仍存活的独立对象。

### 1. 魔法旋风 WindStrike：skill1 / state20

- 注册：`atmage_load_state.nut:15`。控制器：`sqr/character/atmage/windstrike/wind_strike.nut`。
- `onSetState:38–45` 停止移动，选择 `CUSTOM_ANI_WIND_STRIKE=0`，使用源攻速接口；CHR etc-motion0 为 `character/mage/atanimation/windstrike.ani`。
- ANI6帧，总长650ms。FLAG1在零基帧2、源时刻160ms、属性字节255；独立播放器在tick10，即166.666…ms调用 `onKeyFrameFlag:53–79`。
- 该回调从SKL等级列取得bonus/power/upForce，创建对象 **24201**，相对坐标 **(120,1,0)**。源静态 `[80,150]` 虽被读取进局部变量，但本回调没有用它们替代创建坐标，不能擅自把120改成80或150。
- ID24201明确绑定 `passiveobject/character/mage/atwindstrike.obj`，basic-motion为 `passiveobject/character/mage/animation/atwindstrike/00_wind_dodge.ani`，ATK为 `passiveobject/character/mage/attackinfo/atwindstrike.atk`。
- 对象脚本 `sqr/character/atmage/windstrike/po_wind_strike.nut` 在 `setCustomData:3–16` 接收Dword bonus、Dword power、Word upForce，在 `onEndCurrentAni:20–28` 销毁。对象ANI8帧640ms，独立时钟跨过640ms后销毁，绝对时刻816.666…ms。
- 人物650ms返站。对象ALS `00_wind_dodge.ani.als` 声明 `guard_attack_none.ani`，第0帧add到layer−1，由通用ALS模块展开。此链没有活动PTL调用。

当前默认dungeon Lv1等级行三列为144、36、350；当前播放器只把它们作为来源trace，不冒充已执行被动倍率、伤害或浮空结果。源SKL可执行状态0/14/8、MP端点6/40、CD2000ms继续保留，视觉播放不因未实现资格账本而被挡住。正常输入、命中判定、原客户端攻速精确取整待后续验证。

### 2. 冰魄剑 IceSword：skill8 / state27

- 注册：`atmage_load_state.nut:24`。控制器：`sqr/character/atmage/icesword/ice_sword.nut`。
- `onSetState:26–62` 停止移动，选择 `CUSTOM_ANI_ICE_SWORD=10`；CHR明确映射 `character/mage/atanimation/icesword.ani`。ATK索引来自同一CHR的 etc-attack，不与原生受保护选择器混为一个空间。
- 正常攻击 `CUSTOM_ATTACK_INFO_ICE_SWORD=1` -> `character/mage/atattackinfo/icesword.atk`；末击 `CUSTOM_ATTACK_INFO_ICE_SWORD_LAST=2` -> `character/mage/atattackinfo/iceswordlast.atk`。
- 攻速额外倍率在源码中明确为 `SKL static[0]/100`，当前为100/100=1。源ANI25帧1350ms，不用猜测技能总长。
- 初始设置ATK1；FLAG1在帧7@280ms（tick283.333…ms）重新设置ATK1、应用conversion并重取等级列0倍率。FLAG2在帧12@480ms（tick483.333…ms）设置ATK2、等级列1倍率，并将等级列2/3/4的减速参数写入攻击信息。FLAG3在帧14@600ms仅进入EX条件分支。
- `SKILL_ICE_SWORD_EX=218`。EX>0且非PvP时，FLAG3第一次回到源帧0，第二次返站；本fixture EX=0，因此**不重放、不提前结束**，按1350ms ANI完成回调 `onEndCurrentAni:65–70` 返站。
- 人物ANI ALS显式声明五层 `01_light_dodge.ani`、`02_ice_normal.ani`、`03_ice_dodge.ani`、`04_iceline_dodge.ani`、`05_smoke_dodge .ani`（末路径在扩展名前有空格，必须保留），均在 `character/mage/effect/animation/aticesword/`。`[none effect add]` 的源order、unique name和层保留；该标签的特殊native flag语义仍独立标未知，不等同于所有附层通用规则。
- 自定义命中特效为 `character/mage/effect/animation/aticesword/05_2_smoke_dodge .ani`；`onAttack:72–77` 还有目标染色。无实际命中不播放命中特效，不染色。该控制器没有生成OBJ/PTL。

当前dungeon Lv1等级行 `[223,268,22,20,1500]`、MP30/280、CD4000ms；sourceDocuments保留完整SKL重复模式作用域，未把PvP行覆盖到默认行。ATK切换、被动与异常在trace中说明，完整战斗消费者仍待接入。

### 3. 魔法冰球 WaterCannon：skill26 / state43

- 注册：`atmage_load_state.nut:34`。控制器：`sqr/character/atmage/watercannon/watercannon.nut`。
- `onSetState:45–57` 停移，选择 `CUSTOM_ANI_WATER_CANNON=47` -> `character/mage/atanimation/watercannon.ani`，播放 `MW_WCANNON_READY` 并尝试元素链被动。人物ANI12帧960ms，完成回调74–82返站，固定tick时刻966.666…ms。
- `onKeyFrameFlag:84–124` 没有flagIndex过滤，因此应对实际来源flag执行，而不是硬猜1。当前ANI仅一条FLAG1，帧5@400ms，属性偏移404。回调写入Dword bonus、Word size、Word speed、Word distance，创建 **24217** 于 **(68,1,70)**。
- ID24217 -> `passiveobject/character/mage/atwatercannon.obj`，ANI `.../animation/atwatercannon/water_normal.ani`，ATK `.../attackinfo/atwatercannon.atk`。弹体ANI3帧580ms且源loop=1；它自己的生命周期不是“播一遍580ms销毁”。
- `po_atwatercannon.nut:1–66` 读入数据。`sizeRate=SKL Lv1 column1=125`，将125/100=**1.25**同时应用于 `setImageRateFromOriginal`、`setAutoLayerWorkAnimationAddSizeRate` 与 `sq_SetAttackBoundingBoxSizeRate`。图像缩放和判定缩放用独立字段，分别有真实消费者；不能假定所有技能图像缩放都自动改变攻击框。
- `procAppend:74–122` 的source时间 `fireT=(distance*800)/xVelocity`。当前SKL静态前两项400、425，因此 **850ms**。`sq_GetUniformVelocity(0,distance,currentT,fireT)` 沿方向移动；无命中到时销毁，绝对时刻1250ms。父对象丢失时也销毁。当前轨使用源loop，850ms显式终点，不在最后帧无限悬挂。
- 人物flag后坐由静态列2/3取得 **−450、1500**；反向键使用列4/5的−225、1000。本fixture无方向键，重建为初速−450、正加速度1500，到0停止：300ms、位移−67.5。动作返站后继承该位置。`motionDelayMs=400` 保持人物ANI从0开始，避免为延迟移动重置动画。原native移动helper/地图碰撞/浮点取整尚未动态验证。
- 人物ALS两层start_normal/start_dodge；弹体ALS add water_dodge并创建follow-parent `particle_normal2.ani`。这里的particle是ANI名字，**不能当作活动PTL**。源NUT中 `ATWaterCannonMove.ptl`、`ATWaterCannonTail.ptl` 均在注释，不执行。
- 首次实际命中时 `po_atwatercannon.nut:146–188` 只生成一次 **24256**，坐标为弹体当前位置y+1，发送bonus、目标group/id、sizeRate−30；`onAfterAttack:218–228` 销毁弹体。24256绑定 `atwatercannonexp.obj`、`.../atwatercannon/explode_normal.ani` 与同ATK；`po_atwatercannonexp.nut:2–46` 缩放并 `sq_AddHitObject` 排除原命中者，82–89动画结束销毁。无命中空放不虚构爆炸。
- `contactResponses` 另外保留可选固定测试靶的首次几何接触响应。主scene按实际来源攻击框/受击框接触派发，使用碰撞时弹体位置+(0,1,0)，停止弹体、生成爆炸与其ALS，再按爆炸ANI完成清理；不预设必定命中。爆炸主体图像/攻击框倍率从源表达式 `(Lv1Size−30)/100` 得到0.95。其NUT未调用 `setAutoLayerWorkAnimationAddSizeRate`，因此不能自动把0.95施加到ALS附层。原目标排除与测试靶反应保留fixture身份，不宣称原生命中接受或伤害已实现。

当前dungeon Lv1等级行 `[174,125]`，MP10/84，CD2000ms。独立播放器提供完整空放可见生命周期和可选几何接触响应；正常战斗命中接受、被动元素链、奖励和伤害属于明确未完成项。

## 下一批两个候选：不冒充本节点已接入

### 4. 连突刺 DashAttackMultiHit：skill11 / native state29

现有原生证据最强的非十字斩候选。`skill-controllers/swordman/README.md` 与 `contract.json` 记录：proc slot+1F0=`0xCB9980`；资格窗口 `0xCC52CB..0xCC5419`，只接受当前state15或62；技能等级>0、角色body帧>=源SD **3**、有效skill11输入，随后成功执行有MP/CD副作用的virtual+864(11,1,1,1)。成功排state29、空向量、priority1。仅state62另有直接attack-descriptor分支，外层还受authority及actor+1A4!=3约束。

`CE1998[29−3] -> 0xCD9FE7` 选择CHR etc-motion11，即 `character/swordman/animation/dashattackmultihit.ani`（8帧500ms），并向受保护ATK选择器传14。**这个14不是已证明的CHR etc-attack索引14**，尽管源CHR那里确有 `attackinfo/dashattackmultihit.atk`；具体protected转换仍未知。

proc表 `CCA368[29]=13`、`CCA2DC[13]=0xCC0881`，body帧>=1附加两条储存效果；源存在 `character/swordman/effect/animation/dashattackmultihit1.ani`、`dashattackmultihit2.ani`。`0xCC541B..0xCC5460` 检测ANI complete bit8后返idle0。初始化窗口 `0xCAE8D0`、消费窗口 `0xCDA170` 的原字节已有保存，但字符串解码及完整运动helper仍需继续闭合。本地SKL `[300,-1000,500,-1000,1]` 不赋予猜测单位；不自动重用先前双击或自动重进dash。当前没有证明必须生成OBJ/PTL，不凭资源名追加。

### 5. 魔法炮 MagicCannon：skill18 / source state37

`atmage_load_state.nut:32` 注册 `sqr/character/atmage/magiccannon/magiccannon.nut`。地面substate4使用CHR etc-motion78 `character/mage/atanimation/magiccannon4.ani`；空中substate0先用etc46 `magiccannonready.ani`，结束读方向键进入水平sub1/etc34 `magiccannon1.ani`、垂直sub2/etc42 `magiccannon3.ani`、斜向sub3/etc41 `magiccannon2.ani`。地面结束返站，空中射击结束返jump，不能统一返站。

人物FLAG1写Word substate/element并创建24227：地面(43,1,70)、水平(54,1,82)、斜向(40,1,40)，垂直默认x/z=0。FLAG2与3另有后坐/竖直速度/落地尘效果。24227 -> `passiveobject/character/mage/atmagiccannon.obj`，默认ANI `.../atmagiccannon/00_magiccannon_none_dodge.ani`，ATK `.../attackinfo/atmagiccannonshoot.atk`，OBJ etc-motion保留四种元素蓄势及四种发射ANI。

`po_magiccannon.nut` 的object FLAG1进入state3，按发射方向旋转、启用实际PTL `passiveobject/character/mage/particle/atmagiccannon.ptl`、添加 `.../atmagiccannon/01_{fire|water|dark|light}_dodge.ani`；2000ms定时销毁，落地或非暗属性命中可触发 `sq_createCommonElementalAttack` 后销毁。暗属性没有同样爆炸。当前尚未闭合通用元素爆炸的全部对象/宿主行为与空中运动，因此不把它塞成“一个动作+全部元素同时出现”的完成技能。没有恢复其专用C++地址；源分支完整可读，可作为下一批有界编译对象。

## 源码修订校验与验证状态

新增模块对本次支持的**实际执行NUT**检查以下SHA256，并验证注册语法、状态/技能符号、回调、数值表达式、单一事件布局和唯一资源绑定。CHR/SKL/OBJ及数值实时读取，不复制到另一份职业常量表。NUT修订不匹配或表达式未支持时，条目保留为 `unsupported-script-controller`、清空半成品轨并给出具体诊断。

| 当前源NUT | SHA256 |
| --- | --- |
| `windstrike/wind_strike.nut` | `d4b8e155427ef7522b1236397edfc78f66851635aa9688cc8220d3aa7991a0c6` |
| `windstrike/po_wind_strike.nut` | `8ac9189d9f725058dfee4a54bf0655a39b4d8912085bb7b7d8f92b7a7299758d` |
| `icesword/ice_sword.nut` | `99a0db006ca2d35a38eb698f955022ab58aa1e2d7f9279255c91676c7470ce1e` |
| `watercannon/watercannon.nut` | `6538c9a61c1f52567cac3bd84af028401e471bcf23281b13c9f8a948cd6e491b` |
| `watercannon/po_atwatercannon.nut` | `6c61c0ae07333cfdf05a073f0cb48c07956f3464f22ff1ae5321a637a9b8540c` |
| `watercannon/po_atwatercannonexp.nut` | `dc5e9331b08f84ae5b67f95b142ab809aed3bc6b500e5cfed80549b9fcabd2a8` |

以上相对路径根为 `sqr/character/atmage/`。另外sourceDocuments登记当前加载器、enum/header、CHR、全部相关list/SKL/STR、OBJ/ATK/ANI/ALS，主流程报告记录每份原始字节、偏移与hash。

- 已自动通过：新模块C++20 `-Wall -Wextra -fsyntax-only`；当前PVF唯一注册映射及上述7份ANI完整字节消费、frame/event/loop/duration独立只读核查。
- 统一构建/主播放器配方执行/通用ALS渲染验证：由主流程执行并记录在其本节点验证结果中；本文不先计通过。
- 待用户测试：选择三条“脚本技能播放”条目，观察人物、附层、空放实体与返站，左右方向切换及独立对象清理；不要把资源注册条目当技能播放。
- 原版动态对照：三条均待用户验证。没有宣称十职业、MP/CD、伤害、被动、正常游戏流程或最终v0.1 beta验收已完成。

## ??????/???????CP949??????????

?? `sqr/character/atmage/watercannon/po_atwatercannon.nut`??????? 3575 ? 4675?????? 146?189?

```squirrel
function onAttack_po_ATWaterCannon(obj, damager, boundingBox, isStuck)
{
	if (!obj)
		return 0;
		
	if(!damager)
		return 0;
		
	// PassiveObject/Character/Mage/Animation/ATWaterCannon/explode_normal.ani	

	local attackRate = obj.getVar("attack").get_vector(0);
	local sizeRate = obj.getVar("rate").get_vector(0) - 30;
	local group = sq_GetGroup(damager);
	local id = sq_GetUniqueId(damager);
	
	
	//local x = sq_GetCenterXPos(boundingBox);
	//local y = damager.getYPos() + 1;
	//local z = sq_GetCenterZPos(boundingBox);
	
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj) + 1;
	local z = sq_GetZPos(obj);
	
	local parentObj = obj.getParent();

	if(obj.isMyControlObject())
	{
		local cnt = obj.getVar().get_vector(0);
		
		if(!cnt)
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(attackRate);
			sq_BinaryWriteDword(group);
			sq_BinaryWriteDword(id);
			sq_BinaryWriteDword(sizeRate);
			
			print(" exp create:" + cnt);
			
			obj.getVar().set_vector(0, cnt + 1);
			sq_SendCreatePassiveObjectPacketPos(parentObj, 24256, 0, x, y, z);
		}		
	}
```

?? `sqr/character/atmage/watercannon/po_atwatercannon.nut`??????? 5486 ? 5695?????? 218?229?

```squirrel
function onAfterAttack_po_ATWaterCannon(obj, damager, boundingBox, isStuck)
{
	if (!obj)
		return 0;
		
	if(obj.isMyControlObject())
	{
		sq_SendDestroyPacketPassiveObject(obj);	
	}
	
	return 0;
}
```

?? `sqr/character/atmage/watercannon/po_atwatercannonexp.nut`??????? 2 ? 1237?????? 2?46?

```squirrel
function setCustomData_po_ATWaterCannonExp(obj, receiveData)
{
	if(!obj) return;
	
	local attackBonusRate = receiveData.readDword();
	local group = receiveData.readDword();
	local id = receiveData.readDword();
	local sizeRate = receiveData.readDword();
	
	
	print( " attackrate:" + attackBonusRate + " sizeRate:" + sizeRate + " id:" + id);
	// 패킷으로 받은 공격력 셋팅	
	
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	
	print( " x:" + x + " y:" + y + " z:" + z);
	
	
	local attackInfo = sq_GetCurrentAttackInfo(obj);
	if (attackInfo)
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

	// 물대포의 크기를 조절함.
	local currentAni = sq_GetCurrentAnimation(obj);
	
	print(" currentAni:" + currentAni);
	
	sizeRate = sizeRate.tofloat() / 100.0;
	currentAni.Proc();
	currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
	
	sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);
	
	local parentObj = obj.getParent();
		
	if(parentObj)
	{	
		local damager = sq_GetObject(parentObj, group, id);
		local colObj = sq_GetCNRDObjectToCollisionObject(damager);
		if(colObj && parentObj) 
			sq_AddHitObject(obj, colObj);
	}
}
```

?? `sqr/character/atmage/watercannon/po_atwatercannonexp.nut`??????? 1679 ? 1843?????? 82?92?

```squirrel
function onEndCurrentAni_po_ATWaterCannonExp(obj)
{
	if(!obj) return;

	if(obj.isMyControlObject())
	{
		sq_SendDestroyPacketPassiveObject(obj);
	}
	

}
```
