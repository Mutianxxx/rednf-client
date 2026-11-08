
function ProcFindKeyBoard(obj)
{
	if(!IsTrainSelect[0])
		return;
	if(sq_IsKeyDown(OPTION_HOTKEY_ITEM_QUICKSLOT7 , ENUM_SUBKEY_TYPE_ALL))
	{
		++PushDownCount3;
		if(PushDownCount3<2)
			TraniningSumMons(obj);
	}

	if(sq_IsKeyDown(OPTION_HOTKEY_ITEM_QUICKSLOT8 , ENUM_SUBKEY_TYPE_ALL))
	{
		killMonsters(obj);
		if(IsTrainStartTimeFight == true)
			IsTrainFighterPrepEnd = true;
	}
	if(sq_IsKeyDown(OPTION_HOTKEY_ITEM_QUICKSLOT9 , ENUM_SUBKEY_TYPE_ALL))
	{
		ClearSkillsCooltime(obj);
	}
	if(sq_IsKeyDown(OPTION_HOTKEY_ITEM_QUICKSLOT10 , ENUM_SUBKEY_TYPE_ALL))
	{
		++PushDownCount4;
		if(PushDownCount4<2)
		{
			if(IsShowMainUI == true)
				IsShowMainUI = false;
			else
				IsShowMainUI = true;
		}
	}
	if(sq_IsKeyDown(OPTION_HOTKEY_MENU_SYSTEM__CLOSE_ALL_WINDOW , ENUM_SUBKEY_TYPE_ALL))
	{
		++PushDownCount4;
		if(PushDownCount4<2)
		{
			if(IsShowMainUI == true)
				IsShowMainUI = false;
		}
	}
	return;
}



function OpenMainUI(obj,areainfo,isClick)
{
	local mousArea = [areainfo[10], areainfo[11], areainfo[12], areainfo[13]];
	if(isLeftMouseInAreaClick(obj,mousArea) && !isClick)
		IsShowMainUI = true;
	return;
}

function CloseMainUI(obj,areainfo,isClick)
{
	local mousArea = [areainfo[10], areainfo[11], areainfo[12], areainfo[13]];
	if(isLeftMouseInAreaClick(obj,mousArea) && isClick)
		IsShowMainUI = false;
	return;
}

function DrawTrainRoomAniUI(obj,aniName,AniPath,Xrate,Yrate,R,G,B,alpaha,FramIndex,Xpos,Ypos)
{
	local sq_var = obj.getVar();
	local AniObj2 = sq_var.GetAnimationMap( aniName , AniPath );
	sq_AnimationProc(AniObj2);
	AniObj2.setImageRate(Xrate,Yrate);
	AniObj2.setRGBA(R, G, B, alpaha);
	sq_SetAnimationFrameIndex( AniObj2, FramIndex);
	sq_drawCurrentFrame(AniObj2, Xpos,Ypos, false);
}


function GetPassiveObjCount(obj,PassiveID)
{
	return;
}

function isLeftMouseInAreaClick(obj,areainfo)
{
	if(isMouseInScreenArea(obj,areainfo) && isMousClick(obj))
		return true;
	return false;
}

function isLeftMouseInAreaDown(obj,areainfo)
{
	if(isMouseInScreenArea(obj,areainfo) && isLeftMouse(obj))
		return true;
	return false;
}

function CloseAllDropLists(obj)
{
	foreach(arr in ButtonsFunctions)
	{
		arr[0] = false;
	}
}

function IsLightWidgets(obj)
{
	foreach(arr in ButtonsFunctions)
	{
		if(arr[0] == true)
			return true;
	}
	return false;
}

function CloseAllLightWidgets(obj)
{
	local area = [357,800,53,303];
	if(!isMouseInScreenArea(obj,area))
	{
		if(isMousClick(obj))
		{
			foreach(arr in ButtonsFunctions)
			{
				arr[0] = false;
				
			}
		}
	}
	return;
}

function setOppositeBool(isTreu)
{
	if(isTreu)
		isTreu = false;
	else
		isTreu = true;
}

function isMouseInScreenArea(obj,areainfo)
{
	local mouseX = sq_GetMouseXPos() - CFG_UI_TRAINROOM_MENU_OFFSETX;
	local mouseY = sq_GetMouseYPos();
	if ( mouseX > areainfo[0] && mouseX < areainfo[1] && mouseY > areainfo[2] && mouseY < areainfo[3] )
	{
		return true;
	}
	return false;
}

function isLeftMouse(obj)
{
	local stage = sq_GetObjectManagerStage(obj);
	local control = stage.getMainControl();

	if (control.IsLBDown())
		return true;
	return false;
}

function isLeftMouseUp(obj)
{
	local stage = sq_GetObjectManagerStage(obj);
	local control = stage.getMainControl();

	if (control.IsLBUp())
		return true;
	return false;
}

function isMousClick(obj)
{
	local stage = sq_GetObjectManagerStage(obj);
	local control = stage.getMainControl();
	local IsMclick = false;


	if (control.IsLBDown() && PushDownCount < 1)
		PushDownCount++;
	else if(PushDownCount > 0 && control.IsLBUp())
	{
		PushDownCount = 0;
		return true;
	}

	return false;
}



function InitializeMyCharacter(obj)
{
	local stage = sq_GetGlobaludpModuleStage();
	if(!stage) return;
	local dungeon = sq_GetDungeonByStage(stage);
	local dungeonIndex = sq_GetDuegonIndex(dungeon);
	local isDgn = checkModuleType(MODULE_TYPE_MAIN_GAME);
	if(dungeonIndex != 6000)
		return;
	obj.sendSetMpPacket( obj.getMpMax() );
	obj.setHp(obj.getHpMax() , null, true);
	ClearSkillsCooltime(obj);
	killMonsters(obj);
	InitializeSet(obj);
	InitializeChrAbility(obj);
	TrainningAddAppend(obj);
	return;
}
function InitializeSet(obj)
{
	ButtonsFunctions	=
	{
		["SelectTip1"] = [false,-1,"aniname","aniPath",1],
		["SelectTip6"] = [false,-1,"aniname","aniPath",1],
		["SelectTip2"] = [false,-1,"aniname","aniPath",1],
		["SelectTip3"] = [false,-1,"aniname","aniPath",1],
		["SelectTip4"] = [false,-1,"aniname","aniPath",1],
		["SelectTip5"] = [false,-1,"aniname","aniPath",1],
		["SelectTip7"] = [false,-1,"aniname","aniPath",1],
		["SelectTip8"] = [false,-1,"aniname","aniPath",1],
		["SelectTip9"] = [false,-1,"aniname","aniPath",1],
		["SelectTip10"] = [false,-1,"aniname","aniPath",1],
		["SelectTip11"] = [false,-1,"aniname","aniPath",1]
	}
	TrainStartTime = -1;
	TrainEndTime = -1;
	IsTrainStartTimeFight = false;
	ButtonsFunctions["SelectTip6"][1] = -1;
	IsTrainFighterPrepEnd = false;
	TrainSetHitCondition = [false,false,false];
	IsTrainSetHitCondition = false;
	TraniningSummInfo = [-1,-1,-1,-1]
}

function InitializeChrAbility(obj)
{
	TrainningRoomAbilityValue = [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
	return;
}

function ClearSkillsCooltime(obj)
{
	for (local i = 0; i < 255; ++i)
		obj.endSkillCoolTime(i);
	return;
}

function killMonsters(obj)
{
	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); ++i)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) )
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
			sq_IntVectorClear(sq_GetGlobalIntVector());
			sq_IntVectorPush(sq_GetGlobalIntVector(),0);
			sq_AddSetStatePacketActiveObject(activeObj, STATE_DIE, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);

		}
	}
}

function TraniningSumMons(obj)
{
	local Xpos = obj.getXPos();
	local Ypos = obj.getYPos();
	local MonsterInde = SumMonstersId[ButtonsFunctions["SelectTip1"][1]];
	local MonsterHpId = ButtonsFunctions["SelectTip2"][1];
	if(MonsterHpId == -1 || MonsterHpId > 9)
		MonsterHpId == 9;
	local MonHpRate = (MonsterHpId+1)*10;

	local MonStatusId = ButtonsFunctions["SelectTip3"][1];
	if(MonStatusId > 11)
		MonStatusId = MonStatusId + 3;

	TraniningSetMonInfo = [MonsterInde,MonHpRate,MonStatusId];

	local temp = ButtonsFunctions["SelectTip4"][1];
	local MonLv = temp*5;
	if(MonLv < 0)
		MonLv = 120;
	SummonMonsterPacketWithFriend(obj,MonsterInde,MonLv,9999999,Xpos,Ypos,0);
	return;
}

function SummonMonsterPacketWithFriend( obj, monsterID, level, summonTime, posx, posy, posz )
{
	this.sq_BinaryStartWrite();
	this.sq_BinaryWriteByte(0);
	this.sq_BinaryWriteDword(monsterID);
	this.sq_BinaryWriteWord(1);
	this.sq_BinaryWriteByte(level);
	this.sq_BinaryWriteWord(-1);
	this.sq_BinaryWriteWord(0);
	this.sq_BinaryWriteByte(1);
	this.sq_BinaryWriteByte(2);
	this.sq_BinaryWriteByte(0);
	this.sq_BinaryWriteDword(summonTime);
	this.sq_BinaryWriteDword(-1);
	this.sq_BinaryWriteByte(1);
	obj.sq_SendCreatePassiveObjectPacket(48024, 0, 180, 0, 0);
}

function TrainningAddAppend(obj)
{
	local appendPath = "functions/trainingroom/ap_chrval.nut";
	local APBuff = obj.GetSquirrelAppendage(appendPath); 
	local isAppend = CNSquirrelAppendage.sq_IsAppendAppendage(obj , appendPath );
	if(!isAppend)
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, appendPath, true);
	else
	{
		if(!APBuff.isValid())
			APBuff.setValid(true);
	}
	return;
}

function proc_chrval(appendage)
{
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local UniMonIdCount = obj.getVar("TraniUniMonId").size_vector();
	if(UniMonIdCount ==0)
		obj.getVar("TraniTempCout").clear_vector();
	TrainChrCurSkillId = sqrChr.getCurrentSkillIndex();
	if(TrainChrCurSkillId!=-1)
		TrainTempOldSkillId = sqrChr.getCurrentSkillIndex();
	procTraniningSetMonInfos(obj);
	local change_appendage = appendage.sq_getChangeStatus("traniElements");
	if(!change_appendage)
	{
		change_appendage = appendage.sq_AddChangeStatus("traniElements",sqrChr, sqrChr, 0, CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE  , false, TrainningRoomAbilityValue[0] );
	}
	else if(change_appendage)
	{
		change_appendage.clearParameter();
		local ability = [
		                    CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE,
		                    CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_HIT_RATE,
		                    CHANGE_STATUS_TYPE_PHYSICAL_ATTACK,
		                    CHANGE_STATUS_TYPE_MAGICAL_ATTACK,
		                    CHANGE_STATUS_TYPE_MAGICAL_DEFENSE,
		                    CHANGE_STATUS_TYPE_PHYSICAL_DEFENSE,
		                    CHANGE_STATUS_TYPE_ELEMENT_ATTACK_FIRE,
		                    CHANGE_STATUS_TYPE_ELEMENT_ATTACK_WATER,
		                    CHANGE_STATUS_TYPE_ELEMENT_ATTACK_DARK,
		                    CHANGE_STATUS_TYPE_ELEMENT_ATTACK_LIGHT,
		                    CHANGE_STATUS_TYPE_ATTACK_SPEED,
		                    CHANGE_STATUS_TYPE_CAST_SPEED,
		                    CHANGE_STATUS_TYPE_STUCK
		                ]
		                foreach(key,val in ability)
		{
			change_appendage.addParameter(val, false, TrainningRoomAbilityValue[key].tofloat());
		}

	}
	return;
}


function procTraniningSetMonInfos(obj)
{
	local objectManager = obj.getObjectManager();
	local objectNum = objectManager.getCollisionObjectNumber();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	for(local i=0; i<objectNum; i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if(object && object.isObjectType(OBJECTTYPE_ACTIVE))
		{
			local MonUid = sq_GetObjectId(object);

			if(!proc_IsNewMonster(obj,MonUid))
			{
				local MonIndex1 = -1;
				local HpRate = 0;
				local MonStatus = -1;
				
				try{
					MonIndex1 = TraniningSetMonInfo[0];
					HpRate = TraniningSetMonInfo[1];
					MonStatus = TraniningSetMonInfo[2];
				}
				catch(ex)
				{
				}
				
				local activeObj = sq_GetCNRDObjectToActiveObject(object);
				activeObj.getVar("TraniIsAllHp").clear_vector();
				
				if(HpRate == 110)
				{
					activeObj.getVar("TraniIsAllHp").push_vector(1);
				}

				if(HpRate == 0)
					HpRate = 100;
				activeObj.getVar("TrainStatus").clear_vector();
				activeObj.getVar("TrainStatus").push_vector(MonStatus);
				
				activeObj.getVar("TrainMonIndex").clear_vector();
				activeObj.getVar("TrainMonIndex").push_vector(MonIndex1);
				
				local AppendPath = "functions/trainingroom/ap_status.nut";
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, sqrChr, -1, false, AppendPath, true);
				TrainningSetChrHp(activeObj,HpRate);
				
			}
		}
	}

	return;
}


function GetTraniMonCount(obj)
{
	local objectManager = obj.getObjectManager();
	local objectNum = objectManager.getCollisionObjectNumber();
	local MonCount = 0;
	for(local i=0; i<objectNum; i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if(object && object.isObjectType(OBJECTTYPE_ACTIVE))
			++MonCount;
	}
	
	return MonCount;
}

function proc_IsChange(obj,value)
{
	local VectorSize = obj.getVar("TraniTempCout").size_vector();
	local LastValue = null;
	if(VectorSize == 0)
	{
		obj.getVar("TraniTempCout").clear_vector();
		obj.getVar("TraniTempCout").push_vector(value);
	}
	else
	{
		LastValue = obj.getVar("TraniTempCout").get_vector(0);
	}
	if(LastValue == value)
		return true;
	return false;
}

function proc_IsNewMonster(obj,value)
{
	local MonUIdCount = obj.getVar("TraniUniMonId").size_vector();
	local IsSame = false;
	
	if(MonUIdCount<1)
	{
		obj.getVar("TraniUniMonId").push_vector(value);
		return false;
	}
	else
	{
		for(local i=0; i<MonUIdCount; ++i)
		{
			local CurMonUid = obj.getVar("TraniUniMonId").get_vector(i);
			if(CurMonUid == value)
				IsSame = true;
		}
		if(IsSame)
			return true;
		else
		{
			obj.getVar("TraniUniMonId").push_vector(value);
			
			return false;
		}

	}

}


function TrainningBuffSet(obj)
{
	local BuffAdd =
	{
		["SelectTip5"] = [10,20,30,40,50,60,70,80,90,100],
		["SelectTip7"] = [300,600,900,1200,1500,1800,2100,2400,2700,3000],
		["SelectTip8"] = [25,50,75,100,125,150,200,250,300],
		["SelectTip9"] = [100,200,300,400,500,600,700,800,900,1000],
		["SelectTip10"] = [10,20,30,40,50,60,70,80,90,100],
		["SelectTip11"] = [10,20,30,40,50,60,70,80,90]
	}
	if(ButtonsFunctions["SelectTip5"][1] > -1) 
	{
		TrainningRoomAbilityValue[0] = BuffAdd["SelectTip5"][ButtonsFunctions["SelectTip5"][1]];
		TrainningRoomAbilityValue[1] = BuffAdd["SelectTip5"][ButtonsFunctions["SelectTip5"][1]];
	}
	if(ButtonsFunctions["SelectTip7"][1] > -1)
	{
		for(local i=0; i<4; ++i)
		{
			TrainningRoomAbilityValue[2+i] = BuffAdd["SelectTip7"][ButtonsFunctions["SelectTip7"][1]];
		}
	}
	if(ButtonsFunctions["SelectTip8"][1] > -1)
	{
		for(local i=0; i<4; ++i)
		{
			TrainningRoomAbilityValue[6+i] = BuffAdd["SelectTip8"][ButtonsFunctions["SelectTip8"][1]];
		}
	}
	if(ButtonsFunctions["SelectTip9"][1] > -1) 
	{
		TrainningRoomAbilityValue[10] = BuffAdd["SelectTip9"][ButtonsFunctions["SelectTip9"][1]];
		TrainningRoomAbilityValue[11] = BuffAdd["SelectTip9"][ButtonsFunctions["SelectTip9"][1]];
	}

	return;
}

function TrainningSetChrHp(obj,HpPercent)
{
	local MyHpMax = obj.getHpMax();
	local HpValue = MyHpMax*HpPercent/100.0;
	obj.setHp( HpValue.tointeger()+2 , null, true);
	return;
}
function TrainningSetChrMp(obj,MpPercent)
{
	local MyMpMax = obj.getMpMax();
	local MpValue = MyMpMax*MpPercent/100.0;
	obj.sendSetMpPacket( MpValue.tointeger()+2 );
	return;
}


function TrainningStartFighter(obj)
{
	if(!IsTrainStartTimeFight)
		return;
	local CutTime = obj.getVar("TrainRoomTimeGet").get_vector(0);
	local StartTime = TrainStartTime;
	local EndTime = TrainEndTime + 4000;
	local InterTinme = CutTime - StartTime;
	local TimeCount = (InterTinme/1000.0).tointeger();
	
	local aniName = "TrainStartFightShow";
	local AniPath = "map/trainingroom/trainingroomfighttime.ani";
	local Xrate = 1.0;
	local Yrate = 1.0;
	local FramIndex = TimeCount;

	if(CutTime < EndTime && InterTinme>4000)
		TrainningDrawTimeCount(obj,EndTime - CutTime,1.0,255,255,255,255,10,300,260);

	
	if( CutTime >= EndTime || IsTrainFighterPrepEnd == true)
	{
		IsTrainStartTimeFight = false;
		TrainStartTime = -1;
		TrainEndTime = -1;
		ButtonsFunctions["SelectTip6"][1] = -1;
		PushDownCount5 = 0;
		killMonsters(obj);
		IsTrainFighterSettlement = true;
		TrainSettlementMovePos[0] = 170;
		TrainSettlementMovePos[1] = 264;
		IsTrainFighterPrepEnd = false;
		
		return;
	}

	if(FramIndex < 4) 
	{
		
		DrawTrainRoomAniUI(obj,aniName,AniPath,Xrate,Yrate,255,255,255,255,FramIndex,80,100)
	}

	if(InterTinme > 2100) 
	{
		
		
		if(PushDownCount5<1)
		{
			++PushDownCount5;
			TraniningSumMons(obj);
		}
	}
	return;
}

function TrainningDrawTimeCount(obj,Time,rate,R,G,B,Alpha,space,Xpos,Ypos)
{
	local aniName = "TrainNumber";
	local AniPath = "map/trainingroom/trainingroomfighttime.ani";

	
	local Ms = (Time/10)%100;
	local TimeS = Time/1000;
	local h = 0;
	local m = 0;
	local s = 0;
	h = TimeS/3600;
	m = (TimeS%3600)/60;
	s = TimeS%3600%60;

	DrawTrainRoomNumber(obj,Ms,rate,R,G,B,Alpha,space, Xpos + 414 + space*6,Ypos+180);
	DrawTrainRoomAniUI2(obj,aniName,AniPath,rate,rate,R,G,B,Alpha,16, Xpos + 414 + space*5 + space/5,Ypos+180);
	DrawTrainRoomNumber(obj,s,rate,R,G,B,Alpha,space,Xpos + 414 + space*3 ,Ypos+180);
	DrawTrainRoomAniUI2(obj,aniName,AniPath,rate,rate,R,G,B,Alpha,15,Xpos + 414 + space*2 + space/2 ,Ypos+180);
	DrawTrainRoomNumber(obj,m,rate,R,G,B,Alpha,space,Xpos + 414,Ypos+180);
	return;
}

function DrawTrainRoomNumber(obj,Value,rate,R,G,B,Alpha,space,Xpos,Ypos)
{
	local str = "";
	if(Value.tostring().len()<2)
		str = "0" + Value.tostring()
		      else
			      str = Value.tostring();
	local NumLeng = str.len();
	
	local aniName = "TrainNumber";
	local AniPath = "map/trainingroom/trainingroomfighttime.ani";
	local FramIndex = 0;
	

	for(local i = 0; i < NumLeng; i++)
	{
		local SingleNum = str.slice(i , i + 1);
		FramIndex = SingleNum.tointeger() + 5;
		DrawTrainRoomAniUI2(obj,aniName,AniPath,rate,rate,R,G,B,Alpha,FramIndex,Xpos + space*i,Ypos)
	}
}


function DrawTrainRoomAniUI2(obj,aniName,AniPath,Xrate,Yrate,R,G,B,alpaha,FramIndex,Xpos,Ypos)
{
	local sq_var = obj.getVar();
	local AniObj2 = sq_var.GetAnimationMap( aniName , AniPath );
	sq_AnimationProc(AniObj2);
	AniObj2.setImageRate(Xrate,Yrate);
	AniObj2.setRGBA(R, G, B, alpaha);
	sq_SetAnimationFrameIndex( AniObj2, FramIndex);
	sq_drawCurrentFrame(AniObj2, Xpos,Ypos, false);
}


function TrainTestFighterEnd(obj)
{
	if(obj.getVar("TrainTestHitDamage").size_vector()<1)
		return;

	local CurDamageVal = obj.getVar("TrainTestHitDamage").get_vector(0);
	
	IsTrainFighterSettlement = true;

	return;
}


function DrawTrainRoomSmallNumber(obj,Value,Xsize,Ysize,R,G,B,ALPHA,space,Xpos,Ypos)
{
	if(Value<0)
		Value = 0;
	local str = Value.tostring();
	local Arr = [];
	local Count = Value.tostring().len();
	for(local i=0; i<Count; ++i)
	{
		Arr.push(str.slice(i,i+1));
		
		
	}
	local ArrL = Arr.len();
	local Tcount = ArrL/3;
	for(local i=0; i<Tcount; ++i)
	{
		Arr.insert(ArrL-(i+1)*3,".");
	}
	local Num =
	{
		["0"] = 5,
		["1"] = 6,
		["2"] = 7,
		["3"] = 8,
		["4"] = 9,
		["5"] = 10,
		["6"] = 11,
		["7"] = 12,
		["8"] = 13,
		["9"] = 14,
		["."] = 15
	}
	local aniName = "TrainSmallNumber";
	local AniPath = "map/trainingroom/trainingroomfighttime.ani";
	local FramIndex = 0;
	
	if(Arr[0] == ".")
		Arr.remove(0);
	
	local spec = (Arr.len()/2.0*space).tointeger()
	Xpos = Xpos - spec;
	
	foreach(key,val in Arr)
	{
		if(key == 0 && val==".")
			continue;
		local Y = 0;
		if(val == ".")
			Y = Ypos + (12*space/7).tointeger();
		else
			Y = Ypos;
		DrawTrainRoomAniUI2(obj,aniName,AniPath,Xsize,Ysize,R,G,B,ALPHA,Num[val],Xpos + space*key,Y)
	}

}

function TrainDrawNum(obj , str , Xpos , Ypos ,Justify)
{
	if(str<0)
		str = 0;
	local Strin = {
		["0"] = 60,
		["1"] = 61,
		["2"] = 62,
		["3"] = 63,
		["4"] = 64,
		["5"] = 65,
		["6"] = 66,
		["7"] = 67,
		["8"] = 68,
		["9"] = 69,
		["."] = 71
	}
	
	local FramIndex = str + 60;
	local str = str.tostring();
	local NumLeng = str.len();
	local Space = 8;
	local aniName = "TrainTuenPageNum";
	local AniPath = "map/trainingroom/damage_analyse.ani";
	local rate = 1.0;
	if(Justify == 0)
		Xpos = Xpos
	else if(Justify == 1)
		Xpos = Xpos - NumLeng*Space;
	else if(Justify == 2)
		Xpos = Xpos - NumLeng*Space/2;
	for(local i = 0; i < NumLeng; i++)
	{
		local SingleNum = str.slice(i , i + 1);
		DrawTrainRoomAniUI2(obj,aniName,AniPath,rate,rate,255,255,255,255,Strin[SingleNum],Xpos + i*Space,Ypos);
	}
	return ;
}


function ApplyHpDamage_appendage_status(appendage, newHpDamage, attacker)
{
	local SourceObj = appendage.getSource();
	local obj = appendage.getParent();
	local MaxHp = obj.getHpMax();
/* 	local attackInfo = sq_GetCurrentAttackInfo(attacker);
	local AtkType = sq_GetAttackType(attackInfo);
	local TempDamage = newHpDamage;
	local OldTotle = 0;
	local ExtraD = 0;
	for(local i=0;i<3;++i)
		OldTotle = OldTotle + SourceObj.getVar("TrainTestHitDamage").get_vector(i);

	if(newHpDamage > MaxHp)
		return newHpDamage;
	
	if(OldTotle + newHpDamage > MaxHp)
	{
		TempDamage = MaxHp - OldTotle;
	}

	local OldDamege = SourceObj.getVar("TrainTestHitDamage").get_vector(AtkType);
	local NewDamage = OldDamege + TempDamage;
	SourceObj.getVar("TrainTestHitDamage").set_vector(AtkType,NewDamage);
	 */

/* 	local TestOldTotal = obj.getVar("TrainTotalDamage").get_vector(0);
	local NewDamageTest = newHpDamage;
	if(TestOldTotal+newHpDamage>MaxHp)
		NewDamageTest = MaxHp;
	obj.getVar("TrainTotalDamage").set_vector(0,NewDamageTest); */
	
	return newHpDamage;
}

function pro_append_status(appendage)
{
	local obj = appendage.getParent();
	local sourceObj = appendage.getSource();
	
	if(sq_IsMyCharacter(obj))
	{
		appendage.setValid(false);
		return;
	}
	
	local activeObj = sq_GetCNRDObjectToActiveObject(obj);

	local Status = activeObj.getVar("TrainStatus").get_vector(0);

	if(!sq_IsValidActiveStatus(activeObj, Status))
		sq_sendSetActiveStatusPacket(activeObj, activeObj, Status, 200.0, 200, false, 9999999);
	
	
	if(obj.getState() == STATE_DIE)
		TrainMonHpPer = -1;


	
	if(obj.getVar("TrainTempState").getBool(0))
		sq_SetGrabable(activeObj, false);
	
	if(obj.getVar("TrainTempState").getBool(1))
	{
		local CurTime = appendage.getTimer().Get();
		if(CurTime>200 && obj.getState()==STATE_DOWN && obj.getZPos() ==0)
			sq_SetPause(obj, PAUSETYPE_OBJECT, 200);
		if(activeObj.getState()!=STATE_DOWN && obj.getZPos() == 0)
		{
			sq_IntVectorClear(sq_GetGlobalIntVector());
			sq_IntVectorPush(sq_GetGlobalIntVector(), 1);
			sq_IntVectorPush(sq_GetGlobalIntVector(), 0);
			sq_IntVectorPush(sq_GetGlobalIntVector(), DOWN_PARAM_TYPE_FORCE);
			sq_IntVectorPush(sq_GetGlobalIntVector(), 0);
			sq_IntVectorPush(sq_GetGlobalIntVector(), 10);
			sq_AddSetStatePacketActiveObject(activeObj,STATE_DOWN, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);
		}
	}
	if(obj.getVar("TrainTempState").getBool(2))
	{
		local CurAni = obj.getCurrentAnimation();
		sq_SetCustomDamageType(obj, true, 1);
		
		
	}

	if(obj.getHp()<1 && IsTrainStartTimeFight)
		IsTrainFighterPrepEnd = true;
				
	
	return;
}

function Start_appendage_status(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local activeObj = sq_GetCNRDObjectToActiveObject(obj);
	obj.getVar("TrainTempState").clear_vector();
	for(local i = 0;i<3;++i)
	{
		obj.getVar("TrainTempState").push_vector(0);
		obj.getVar("TrainTempState").setBool(i,TrainSetHitCondition[i]);
	}
	obj.getVar("TrainTotalDamage").clear_vector();
	obj.getVar("TrainTotalDamage").push_vector(0);
	TrainReset();
	TrainChrOldSkillId = -1;
	TrainChrCurSkillId = -1;
	TrainTempOldSkillId = -1;
}

function SetHp_appendage_status(appendage, hp, attacker)
{
	if(!appendage)
		return;
	local obj = appendage.getParent();
	if(!obj)
		return;
	local sourceObj = appendage.sq_GetSourceChrTarget();
	local curHp = obj.getHp();
	local SourceObj = appendage.getSource();
	local obj = appendage.getParent();
	local MaxHp = obj.getHpMax();
	local attackInfo = sq_GetCurrentAttackInfo(attacker);
	local AtkType = sq_GetAttackType(attackInfo);
	local damageVal = curHp - hp ;
	local TotalDamage = 0;
	for(local i=0;i<3;++i)
		TotalDamage = TotalDamage + SourceObj.getVar("TrainTestHitDamage").get_vector(i);
	

	

	local LineData = [];
	local MonsId = obj.getVar("TrainMonIndex").get_vector(0);
	SourceObj.getVar("TrainTestHitDamage").set_vector(3,MonsId);
	

	local OldDamege = SourceObj.getVar("TrainTestHitDamage").get_vector(AtkType);
	if(TotalDamage+damageVal>MaxHp)
		damageVal = MaxHp-TotalDamage;
	local NewDamage = damageVal + OldDamege; 
	SourceObj.getVar("TrainTestHitDamage").set_vector(AtkType,NewDamage);
	
	

	local OldSkillId = TrainChrOldSkillId;
	local OldSkillCount = TrainSkillDamage[OldSkillId][0];
	local CurState = SourceObj.getState();

	local CurskillIndex = TrainChrCurSkillId;

	if(CurskillIndex != OldSkillId)
	{
		if(CurskillIndex == -1)
		{
			if(CurState == 7 || CurState == 8|| CurState == 15)
			{
				OldSkillId = 174;
				local OldSkillCount = TrainSkillDamage[OldSkillId][0];
				local OldSkillDamage = TrainSkillDamage[OldSkillId][1];
				TrainSkillDamage[OldSkillId][0] = 1;
				TrainSkillDamage[OldSkillId][1] = OldSkillDamage + damageVal;
			}
			else
			{
				local OldSkillCount = TrainSkillDamage[OldSkillId][0];
				local OldSkillDamage = TrainSkillDamage[OldSkillId][1];

				TrainSkillDamage[OldSkillId][1] = OldSkillDamage + damageVal;
			}
		}
		else
		{
			TrainChrOldSkillId = CurskillIndex;
			if(CurskillIndex!=TrainTempOldSkillId)
				CurskillIndex = TrainTempOldSkillId;
			local OldSkillCount = TrainSkillDamage[CurskillIndex][0];
			local OldSkillDamage = TrainSkillDamage[CurskillIndex][1];
			TrainSkillDamage[CurskillIndex][0] = OldSkillCount + 1;
			TrainSkillDamage[CurskillIndex][1] = OldSkillDamage + damageVal;
		}
	}
	else
	{
		if(OldSkillId == -1)
		{
			if(TrainTempOldSkillId==-1)
			{
				local TempId = 197;
				if(CurState == 7 || CurState == 8|| CurState == 15)
					TempId = 174;
				local OldSkillDamage = TrainSkillDamage[TempId][1];
				TrainSkillDamage[TempId][0] = 1;
				TrainSkillDamage[TempId][1] = OldSkillDamage + damageVal;
				
			}
			else
			{
				local TempId = TrainTempOldSkillId;
				if(CurState == 7 || CurState == 8|| CurState == 15)
					TempId = 174;
				local OldSkillDamage = TrainSkillDamage[TempId][1];
				TrainSkillDamage[TempId][0] = 1;
				TrainSkillDamage[TempId][1] = OldSkillDamage + damageVal;
			}
			
		}
		else
		{
			local OldSkillDamage = TrainSkillDamage[CurskillIndex][1];
			TrainSkillDamage[CurskillIndex][1] = OldSkillDamage + damageVal;
		}

	}

	local VecSize = obj.getVar("TraniIsAllHp").size_vector();
	if(VecSize < 1)
		return hp;
	local Hpmax = obj.getHpMax();
	return Hpmax;
}

function TrainReset()
{
	TrainSkillDamage = {}
	for(local i=-1; i<255; ++i)
	{
		local TempArr = [0,0]
		TrainSkillDamage.rawset(i, TempArr)
	}
}
function DamageParent_appendage_status(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.sq_GetSourceChrTarget();
	local CurskillIndex = sourceObj.getCurrentSkillIndex();
	TrainChrCurSkillId = CurskillIndex;
	local object = sq_GetCNRDObjectToActiveObject(parentObj);
	local MonUid = sq_GetObjectId(object);
	TrainMonHpPer = MonUid;

	return;
}

function TrainDrawMonHpPer(obj)
{
	if(!IsTrainSelect[1] || TrainMonHpPer==-1)
		return;
	local object = sq_GetObjectByObjectId(obj, TrainMonHpPer);
	if(!object) return;
	object = sq_GetCNRDObjectToActiveObject(object);
	local maxhp = object.getHpMax();
	local currhp = object.getHp();
	
	local HpPer = (currhp*1000.0/maxhp).tointeger()/10.0;
	TrainDrawNum(obj, HpPer ,293,107,2);
	
	return;
}


function TrainPrintTxtMain(obj,NewDatas)
{
	local chrJob = sq_getJob(obj);
	TrainPrintTxtEx("SKILLID" + "\t" + "Usagetimes" + "\t" + "Totaldamage" + "\t" + "Averageinjury" + "\t" + "Proportionofinjury" + "\n");
	foreach(key ,DataArr in NewDatas)
	{
		foreach(key,val in DataArr)
		{
			if(key == 0)
			{
				local IsName = false;
				foreach(key2,skilldi in TrainAllChrSkillIndex[chrJob])
				{
					if(key2 == val)
						IsName = true;
				}
				if(IsName)
					TrainPrintTxtEx(TrainAllChrSkillIndex[chrJob][val] + "\t");
				else
				{
					if(val == 197)
						TrainPrintTxtEx("unknown" + "\t");
					else
						TrainPrintTxtEx(val + "\t");
				}
					
			}
			else
				TrainPrintTxtEx(val + "\t");
		}
		TrainPrintTxtEx("\n");
	}
}

function TrainPrintTxtEx(String)
{
	local FilePath = "training_analyse.txt";
	local file = file(FilePath,"a+");
	local string = String.tostring();
	local len = string.len();
	for(local i=0;i<len;++i)
	{
		local ascii = string[i];
		file.seek(0, 'e');
		file.writen(ascii,'c');
	}
}

